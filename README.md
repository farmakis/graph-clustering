# graph-clustering

High-performance C++ graph clustering library with Python bindings.<br>
It supports **Connected Components** and **DBSCAN** clustering.

## Installation 


```
chmod +x install.sh
./install.sh
```

It doesn't build the Python bindings by default. To build them, open the `install.sh` file and change the `BUILD_PYTHON_BINDINGS` variable to `ON`. Then run the above commands.

Alternatively,
in the root directory run:
```
mkdir build && build
cmake -DBUILD_PYTHON_BINDINGS=ON ..
cmake --build .
```

or `cmake -DBUILD_PYTHON_BINDINGS=OFF ..` for C++ only.

Python bindings are being built in the `build` directory. To make them visible, make sure you include the dir in your project root by:
```
export PYTHONPATH=$(pwd)/build/python:$PYTHONPATH
```


## Description

This package provides efficient graph clustering algorithms with Python bindings powered by pybind11 and scikit-build.<br>
The backbone of the project is a weakly connected components by max propagation method for directed graphs.

## Run tests with Python API
```
python -m unittest discover tests
```

