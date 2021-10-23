cmake_minimum_required(VERSION 2.8.12)

cmake_policy(SET CMP0015 NEW)

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
	pray_client
	${src}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

target_link_libraries(pray_client m rt SDL common pthread tinyxml)
