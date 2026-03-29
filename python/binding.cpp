#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Handles conversion between std::vector and Python lists
#include "connected_components.h"
#include "dbscan.h"

namespace py = pybind11;

PYBIND11_MODULE(pygraphclustering, m) {
    m.def("connected_components", &connected_components, 
        "A function that clusters graphs using Weakly Connected Components by max propagation",
        py::arg("num_nodes"), py::arg("edges"));
}