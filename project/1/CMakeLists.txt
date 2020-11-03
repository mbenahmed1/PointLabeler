cmake_minimum_required(VERSION 3.10)

# set the project name
project(PointLabeler)

set(POINTLABELER_SOURCES
    src/PointLabeler.cpp
    src/Map.cpp
    src/Point.cpp src/GreedyAlgorithm.cpp src/GreedyAlgorithm.hpp)

# set compiler warnings
#set(CMAKE_CXX_FLAGS_DEBUG "-Wall")

# add the executable
add_executable(PointLabeler ${POINTLABELER_SOURCES})
