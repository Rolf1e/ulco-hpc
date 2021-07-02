cmake_minimum_required (VERSION 2.6)
project (tp5)

add_definitions(-std=c++11 -march=native -O2)

add_executable(tp5_1 src/exo1.cpp)

find_package(MPI REQUIRED)
add_definitions(-DOMPI_SKIP_MPICXX)

add_executable(tp5_2 src/exo2.cpp)

target_link_libraries(tp5_2 PUBLIC MPI::MPI_CXX)
