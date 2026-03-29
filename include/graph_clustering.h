#ifndef GRAPH_CLUSTERING_HEADER
#define GRAPH_CLUSTERING_HEADER

#include "connected_components.h"
#include "dbscan.h"

namespace gc {
    // Re-export everything from the headers in the gc namespace
    // connected_components.h
    using ::connected_components;
    // dbscan.h
    using ::dbscan;
    // Add more using declarations as needed for other public API
}

#endif // GRAPH_CLUSTERING_H
