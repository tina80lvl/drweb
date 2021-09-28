cmake_minimum_required(VERSION 3.13)
project(graph)

set(CMAKE_CXX_STANDARD 17)

add_executable(graph main.cpp struct.h util.h struct.cpp)