cmake_minimum_required(VERSION 2.6)
	
#Configuration du projet
project(client)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

find_package(Threads)
find_package(SDL REQUIRED)

include_directories(inc/ ../common/inc)
link_directories(../common/${CMAKE_BUILD_TYPE})


#Génération de la liste des fichiers sources
file(GLOB_RECURSE src src/*.cpp)


#Déclaration de l'exécutable
add_executable(
	client
	${src}
)

set(CMAKE_CXX_FLAGS "-g -Wall -ggdb -std=c++11")

target_link_libraries(client m rt SDL common pthread tinyxml)
