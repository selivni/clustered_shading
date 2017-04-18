cmake_minimum_required(VERSION 2.6)

project(UTILITY)

file (GLOB UTILITY_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -g -std=c++11")

add_library(UtilityLib OBJECT ${UTILITY_SRC})

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/include/VM"
	"${PROJECT_SOURCE_DIR}/include/GL"
)
