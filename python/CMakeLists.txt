# This creates a python module named 'pygraphclustering' from the C++ code in 'binding.cpp'
pybind11_add_module(pygraphclustering 
    binding.cpp
)

# Link it to your core C++ logic
target_link_libraries(pygraphclustering PRIVATE graph_clustering)

# Match the name used in 'import pygraphclustering' in Python
set_target_properties(pygraphclustering PROPERTIES OUTPUT_NAME "pygraphclustering")

# CRITICAL: Tell CMake where to put the module so Python finds it
install(TARGETS pygraphclustering LIBRARY DESTINATION pygraphclustering)