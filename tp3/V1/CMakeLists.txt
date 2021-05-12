cmake_minimum_required (VERSION 3.1)
project (lr)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(SRCS
    ./src/lr.cpp


    ./src/Plan.cpp
    ./src/Scene.cpp
    ./src/Source.cpp
    ./src/Image.cpp
    ./src/Camera.cpp

    ./src/materiel/Couleur.cpp
    ./src/materiel/Materiau.cpp

    ./src/objects/Objet.cpp
    ./src/objects/Sphere.cpp
    ./src/objects/Rayon.cpp
    ./src/objects/Triangle.cpp

    ./src/infra/Vecteur.cpp
    ./src/infra/Point.cpp
    ./src/infra/Intensite.cpp
    ./src/infra/Intersection.cpp
    )
    
set(HEADERS
    ./src/Plan.hpp
    ./src/Scene.hpp
    ./src/Source.hpp
    ./src/Image.hpp
    ./src/Camera.hpp
    
    ./src/materiel/Couleur.hpp
    ./src/materiel/Materiau.hpp

    ./src/objects/Objet.hpp
    ./src/objects/Sphere.hpp
    ./src/objects/Rayon.hpp
    ./src/objects/Triangle.hpp

    ./src/infra/Vecteur.hpp
    ./src/infra/Point.hpp
    ./src/infra/Intensite.hpp
    ./src/infra/Intersection.hpp
    )

#add_definitions(-std=c++11 -O2 -pthread -g)
add_compile_options(-std=c++11  -O2 -g)

find_package( Threads )

add_executable(lr ${SRCS} ${HEADERS})
target_link_libraries( lr ${CMAKE_THREAD_LIBS_INIT} )

