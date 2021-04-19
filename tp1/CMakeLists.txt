cmake_minimum_required (VERSION 2.6)
project (ps)

add_definitions(-std=c++11 -march=native -O2)

add_executable(ps ps.cpp)
