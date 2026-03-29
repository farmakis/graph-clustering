#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <iostream>

#include "connected_components.h"



// Assign dense labels
std::vector<int> assign_dense_labels(const std::vector<int>& V) {
    std::unordered_map<int, int> label_map;
    int next_label = 0;
    std::vector<int> dense(V.size());
    for (size_t i = 0; i < V.size(); ++i) {
        int v = V[i];
        if (label_map.count(v) == 0)
            label_map[v] = next_label++;
        dense[i] = label_map[v];
    }
    return dense;
}

// Orient edges so that edges point from higher to lower node value
void orient_edges_wrt_max(const std::vector<int>& V, std::vector<int>& edges) {
    size_t num_edges = edges.size() / 2;
    for (size_t i = 0; i < num_edges; ++i) {
        int src = edges[2*i];
        int dst = edges[2*i+1];
        if (V[dst] > V[src]) {
            std::swap(edges[2*i], edges[2*i+1]);
        }
    }
}

// Propagate the max value within each neighborhood (from src to tgt)
std::vector<int> max_propagation(const std::vector<int>& V, const std::vector<int>& edges, int N) {
    std::vector<int> V_max(N, std::numeric_limits<int>::min());
    size_t num_edges = edges.size() / 2;
    #pragma omp parallel for
    for (size_t i = 0; i < num_edges; ++i) {
        int src = edges[2*i];
        int dst = edges[2*i+1];
        #pragma omp atomic
        V_max[dst] = std::max(V_max[dst], V[src]);
    }
    // Keep original value if it was higher
    for (int i = 0; i < N; ++i) {
        if (V_max[i] < V[i]) V_max[i] = V[i];
    }
    return V_max;
}

std::vector<int> max_of_max_propagation(const std::vector<int>& V, const std::vector<int>& V_max) {
    // For each unique value in V, find the max in V_max
    std::unordered_map<int, int> max_map;
    for (size_t i = 0; i < V.size(); ++i) {
        int v = V[i];
        int v_max = V_max[i];
        if (max_map.count(v) == 0 || v_max > max_map[v])
            max_map[v] = v_max;
    }
    std::vector<int> V_max_max(V.size());
    for (size_t i = 0; i < V.size(); ++i) {
        V_max_max[i] = max_map[V[i]];
    }
    return V_max_max;
}

std::vector<int> wcc_by_max_propagation(
    int N,
    const std::vector<int>& edges,
    bool max_max = true,
    int max_iterations = -1
) {
    // Remove self-loops
    std::vector<int> filtered_edges;
    size_t num_edges = edges.size() / 2;
    for (size_t i = 0; i < num_edges; ++i) {
        int src = edges[2*i];
        int dst = edges[2*i+1];
        if (src != dst) {
            filtered_edges.push_back(src);
            filtered_edges.push_back(dst);
        }
    }

    // Find non-isolated nodes
    std::vector<bool> mask_non_isolated(N, false);
    for (size_t i = 0; i < filtered_edges.size(); ++i)
        mask_non_isolated[filtered_edges[i]] = true;
    std::vector<int> I_sub;
    for (int i = 0; i < N; ++i)
        if (mask_non_isolated[i]) I_sub.push_back(i);

    int N_sub = I_sub.size();
    int N_isolated = N - N_sub;

    // If all nodes are isolated
    if (N_isolated == N) {
        std::vector<int> labels(N);
        std::iota(labels.begin(), labels.end(), 0);
        return labels;
    }

    // Map old indices to new
    std::vector<int> I_sub_inv(N, -1);
    for (int i = 0; i < N_sub; ++i)
        I_sub_inv[I_sub[i]] = i;

    // Build subgraph
    std::vector<int> E_sub;
    for (size_t i = 0; i < filtered_edges.size(); i += 2) {
        int src = filtered_edges[i];
        int dst = filtered_edges[i+1];
        if (I_sub_inv[src] != -1 && I_sub_inv[dst] != -1) {
            E_sub.push_back(I_sub_inv[src]);
            E_sub.push_back(I_sub_inv[dst]);
        }
    }

    // Initialize V with random permutation
    std::vector<int> V(N_sub);
    std::iota(V.begin(), V.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(V.begin(), V.end(), g);

    int max_iter = max_iterations < 1 ? std::max(1, (int)(E_sub.size() / 2)) : max_iterations;
    std::vector<int> V_prev;
    int iter = 0;
    while (iter < max_iter) {
        V_prev = V;
        orient_edges_wrt_max(V, E_sub);
        std::vector<int> V_max = max_propagation(V, E_sub, N_sub);
        if (max_max)
            V_max = max_of_max_propagation(V, V_max);
        // Check for convergence
        if (V == V_max)
            break;
        V = V_max;
        ++iter;
    }

    // Assign dense labels
    std::vector<int> labels_sub = assign_dense_labels(V);

    // Combine with isolated nodes
    std::vector<int> labels(N, -1);
    for (int i = 0; i < N_sub; ++i)
        labels[I_sub[i]] = labels_sub[i] + N_isolated;
    int iso_idx = 0;
    for (int i = 0; i < N; ++i)
        if (labels[i] == -1)
            labels[i] = iso_idx++;

    return labels;
}

namespace gcl {
std::vector<int> connected_components(int N, const std::vector<int>& edges) 
{
    return wcc_by_max_propagation(N, edges, true);
}
} // namespace gcl