#ifndef DBSCAN_HEADER
#define DBSCAN_HEADER

#include <vector>

#include "connected_components.h"


namespace gcl {
std::vector<int> dbscan(
    int N, 
    const std::vector<int>& edges, 
    const std::vector<int>& distances, 
    double eps, 
    int min_points);
}

#endif