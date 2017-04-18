cmake_minimum_required(VERSION 2.6)
project(SOIL C)

file (GLOB SOIL_SRC "${PROJECT_SOURCE_DIR}/src/*.c")

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -s -Wall")

add_library(SOILLib OBJECT ${SOIL_SRC})

include_directories("${PROJECT_SOURCE_DIR}/include")
