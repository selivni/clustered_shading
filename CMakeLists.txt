cmake_minimum_required (VERSION 2.6)
project (clustred_shading)

set (CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")

set (SOURCE_ROOT "${PROJECT_SOURCE_DIR}/source")
set (INCLUDE_ROOT "${PROJECT_SOURCE_DIR}/include")
set (SO_ROOT "${PROJECT_SOURCE_DIR}/shared")

file (GLOB SOURCES RELATIVE "${SOURCE_ROOT}" "${SOURCE_ROOT}/*.cpp")
target_link_libraries(${PROJECT_NAME} "${SO_ROOT}/libassimp.so")
include_directories(${INCLUDE_ROOT} "${SO_ROOT}/include")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

add_executable(${PROJECT_NAME} ${SOURCES})
