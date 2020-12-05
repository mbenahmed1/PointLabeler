cmake_minimum_required(VERSION 3.10)
project(SearchTreeLayout)

set(CMAKE_CXX_STANDARD 14)

add_executable(layout main.cpp sortedLayout.cpp sortedLayout.hpp randomLayout.cpp randomLayout.hpp levelLayout.cpp levelLayout.hpp vanEmdeBoasLayout.cpp vanEmdeBoasLayout.hpp)