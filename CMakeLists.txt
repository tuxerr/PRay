cmake_minimum_required(VERSION 2.8.12)

#set(CMAKE_C_COMPILER   "/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(PRay)

set(CMAKE_CXX_FLAGS "-W -Wall -O2 -march=native -std=c++11")

add_subdirectory("common")
include_directories("common")

add_subdirectory("client")

add_subdirectory("server")
