cmake_minimum_required(VERSION 2.6)
		
#Configuration du projet
project(common)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

include_directories(inc/)

#Génération de la liste des fichiers sources
file(GLOB_RECURSE src src/*.cpp)

#Déclaration de la lib
add_library(
    common 
    SHARED
    ${src}
)

set(CMAKE_CXX_FLAGS "-W -Wall -O2 -march=native -std=c++11")
