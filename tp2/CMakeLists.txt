cmake_minimum_required (VERSION 2.6)
project (tp2)


find_package( Threads )   
add_definitions(-std=c++11 -pthread)

add_executable(tp2_1 exo1.cpp)
target_link_libraries( tp2_1 ${CMAKE_THREAD_LIBS_INIT} )

add_executable(tp2_2 exo2.cpp)
target_link_libraries( tp2_2 ${CMAKE_THREAD_LIBS_INIT} )

add_executable(tp2_3 exo3.cpp)
target_link_libraries( tp2_3 ${CMAKE_THREAD_LIBS_INIT} )

add_executable(tp2_4 exo4.cpp)
target_link_libraries( tp2_4 ${CMAKE_THREAD_LIBS_INIT} )
