# This creates a python module named 'pygcl' from the C++ code in 'binding.cpp'
pybind11_add_module(pygcl 
    binding.cpp
)

# Link it to your core C++ logic
target_link_libraries(pygcl PRIVATE GRAPH_CLUSTERING_LIB)

# Match the name used in 'import pygcl' in Python
set_target_properties(pygcl PROPERTIES OUTPUT_NAME "pygcl")

# CRITICAL: Tell CMake where to put the module so Python finds it
install(TARGETS pygcl LIBRARY DESTINATION pygcl)