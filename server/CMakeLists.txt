cmake_minimum_required(VERSION 2.6)

#find_package(Threads)
		
#Configuration du projet
project(server)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

include_directories(inc/ ../common/inc)
link_directories(../common/${CMAKE_BUILD_TYPE})


#Génération de la liste des fichiers sources
file(GLOB_RECURSE src src/*.cpp)


#Déclaration de l'exécutable
add_executable(
	server
	${src}
)

set(CMAKE_CXX_FLAGS "-g -Wall -ggdb -std=c++11")

target_link_libraries(server -lm -lrt -lcurses -lSDL common pthread tinyxml)
