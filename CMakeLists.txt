cmake_minimum_required(VERSION 3.15)

project( GRAPH_CLUSTERING_LIB )

# Build the static library with -fPIC so it can be linked into shared objects
add_library( ${PROJECT_NAME} STATIC )
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# To remove very annoying "NO ARGUMENTS THAT DEPEND ON A TEMPLATE PARAMETER" errors with G++!
if( UNIX OR MINGW )
	target_compile_options( ${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive -w> )
elseif( MSVC )
	target_compile_options( ${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:/bigobj> )
endif()

# Standard C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_sources( ${PROJECT_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include/graph_clustering.h
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/connected_components.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/dbscan.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/include/connected_components.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/dbscan.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions( ${PROJECT_NAME}
	PRIVATE
		_CRT_SECURE_NO_DEPRECATE
		_CRT_SECURE_NO_WARNINGS
		NOMINMAX
)

# Option to build Python Bindings (Default: ON if pybind11 is found)
option(BUILD_PYTHON_BINDINGS "Build Python bindings using pybind11" ON)
if(BUILD_PYTHON_BINDINGS)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON) # Required for Python modules

    add_subdirectory(third_party/pybind11)
    add_subdirectory(python)
endif()