#ifndef CONNECTED_COMPONENTS_HEADER
#define CONNECTED_COMPONENTS_HEADER

#include <vector>



namespace gcl {
// Computes weakly connected components using max-propagation.
// N: number of nodes
// edges: flat vector of size 2*num_edges (edges[2*i]=src, edges[2*i+1]=dst)
// Returns: labels vector of size N, where labels[i] is the component index of node i
std::vector<int> connected_components(int N, const std::vector<int>& edges);
}

#endif