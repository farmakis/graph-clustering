# !/bin/bash

# Local variables
PROJECT_NAME=graph-clustering
BUILD_PYTHON_BINDINGS=OFF

# Recover the project's directory from the position of the install.sh
# script and move there. Not doing so would install some dependencies in
# the wrong place
HERE=`dirname $0`
HERE=`realpath $HERE`
cd $HERE

mkdir build
cd build
cmake -DBUILD_PYTHON_BINDINGS=$BUILD_PYTHON_BINDINGS ..
cmake --build .
cd $HERE

if [ "$BUILD_PYTHON_BINDINGS" = "ON" ]; then
    export PYTHONPATH=$(pwd)/build/python:$PYTHONPATH
    # echo "Installing Python bindings..."
    # pip install -e python
fi