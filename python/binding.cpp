#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Handles conversion between std::vector and Python lists
#include "graph_clustering.h"

namespace py = pybind11;

PYBIND11_MODULE(pygcl, m) {
    m.def("connected_components", &gcl::connected_components, 
        "A function that clusters graphs using Weakly Connected Components by max propagation",
        py::arg("num_nodes"), py::arg("edges"));
}