#ifndef GRAPH_CLUSTERING_HEADER
#define GRAPH_CLUSTERING_HEADER

#include "connected_components.h"
#include "dbscan.h"

namespace gcl {
    // Re-export everything from the headers in the gcl namespace
    // connected_components.h
    using gcl::connected_components;
    // dbscan.h
    using gcl::dbscan;
    // Add more using declarations as needed for other public API
}

#endif // GRAPH_CLUSTERING_H
