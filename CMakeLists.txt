cmake_minimum_required(VERSION 2.6.0)

project(PRay)

add_subdirectory("common")
include_directories("common")

add_subdirectory("client")

add_subdirectory("server")
