#include <iostream>

#include "dbscan.h"


namespace gcl {
std::vector<int> dbscan(
    int N, 
    const std::vector<int>& edges, 
    const std::vector<int>& distances, 
    double eps, 
    int min_points
) {
    std::vector<int> labels(N, -1); // Initialize all nodes as noise (-1)
    std::cout << "[C++] Running DBSCAN clustering" << std::endl;

    // Filter edges by eps
    std::vector<int> edges_eps;
    size_t num_edges = distances.size();
    for (size_t i = 0; i < num_edges; ++i) {
        if (distances[i] <= eps) {
            // Each edge is represented by two consecutive ints in edges
            edges_eps.push_back(edges[2 * i]);
            edges_eps.push_back(edges[2 * i + 1]);
        }
    }

    // ... continue with Weakly Connected Components using edges_eps
    return labels;
}
} // namespace gcl