cmake_minimum_required(VERSION 3.3)

# set the project name
project(PointLabeler)

option(CXX "enable C++ compilation" ON)
if(CXX)
    enable_language(CXX)
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Visual Studio compiler with static runtime libraries
if(MSVC AND MT)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
endif()

find_package(GUROBI REQUIRED)
include_directories(${GUROBI_INCLUDE_DIRS})


set(POINTLABELER_SOURCES
    src/PointLabeler.cpp
    src/Map.cpp
    src/Normals.cpp
    src/SimulatedAnnealing.cpp
    src/Point.cpp src/GreedyAlgorithm.cpp src/GreedyAlgorithm.hpp src/Util.cpp src/ILPSolver.cpp)

set(ILP_SOURCES
        src/testMip.cpp)



# set compiler warnings
#set(CMAKE_CXX_FLAGS_DEBUG "-Wall")

# add the executable
add_executable(PointLabeler ${POINTLABELER_SOURCES})
add_executable(testILP ${ILP_SOURCES})

if(CXX)
    set(CMAKE_CXX_STANDARD 11)
    target_link_libraries(testILP optimized ${GUROBI_CXX_LIBRARY} debug ${GUROBI_CXX_DEBUG_LIBRARY})
    target_link_libraries(PointLabeler optimized ${GUROBI_CXX_LIBRARY} debug ${GUROBI_CXX_DEBUG_LIBRARY})
endif()

target_link_libraries(testILP ${GUROBI_LIBRARY})
target_link_libraries(PointLabeler ${GUROBI_LIBRARY})

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    include(FeatureSummary)
    feature_summary(WHAT ALL)
endif()
