cmake_minimum_required(VERSION 2.6)

cmake_policy(SET CMP0015 NEW)

#Configuration du projet
project(server)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

find_package(Threads)
find_package(SDL REQUIRED)

include_directories(inc/ ../common/inc)
link_directories(../common/${CMAKE_BUILD_TYPE})


#Génération de la liste des fichiers sources
file(GLOB_RECURSE src src/*.cpp)


#Déclaration de l'exécutable
add_executable(
	pray_server
	${src}
)

target_link_libraries(pray_server m rt curses SDL common pthread tinyxml)
