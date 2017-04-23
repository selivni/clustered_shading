cmake_minimum_required (VERSION 2.6)

project (clustered_shading)


set (CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")

set (SOURCE_ROOT "${PROJECT_SOURCE_DIR}/source")
set (INCLUDE_ROOT "${PROJECT_SOURCE_DIR}/include")
set (SO_ROOT "${PROJECT_SOURCE_DIR}/shared")
set (ASSIMP_ROOT "${SO_ROOT}/assimp")
set (MODEL_ROOT "${PROJECT_SOURCE_DIR}/model")
set (UTILITY_ROOT "${PROJECT_SOURCE_DIR}/lib/Utility")
set (SOIL_ROOT "${PROJECT_SOURCE_DIR}/lib/SOIL")

if (NOT EXISTS "${SOIL_ROOT}/build")
file(MAKE_DIRECTORY "${SOIL_ROOT}/build")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} ..
				WORKING_DIRECTORY "${SOIL_ROOT}/build")
execute_process(COMMAND "make"
				WORKING_DIRECTORY "${SOIL_ROOT}/build")

if (NOT EXISTS "${UTILITY_ROOT}/build")
file(MAKE_DIRECTORY "${UTILITY_ROOT}/build")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} ..
				WORKING_DIRECTORY "${UTILITY_ROOT}/build")
execute_process(COMMAND "make"
				WORKING_DIRECTORY "${UTILITY_ROOT}/build")
if (NOT EXISTS "${ASSIMP_ROOT}/build")
file(MAKE_DIRECTORY "${ASSIMP_ROOT}/build")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
				WORKING_DIRECTORY "${ASSIMP_ROOT}/build")
execute_process(COMMAND "make"
				WORKING_DIRECTORY "${ASSIMP_ROOT}/build")

link_directories(${ASSIMP_ROOT})
file (GLOB SOURCES "${SOURCE_ROOT}/*.cpp")
file (GLOB UTILITY_LIBRARIES
	"${UTILITY_ROOT}/build/CMakeFiles/UtilityLib.dir/src/*.o*")
file (GLOB SOIL_LIBRARIES
	"${SOIL_ROOT}/build/CMakeFiles/SOILLib.dir/src/*.o*")
file (GLOB ASSIMP_LIBRARIES
	"${ASSIMP_ROOT}/build/code/*.so*" "${ASSIMP_ROOT}/build/code/*.dll*")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -std=c++11")
add_definitions(-DSPONZA_OBJ="${MODEL_ROOT}/sponza.obj")
add_definitions(-DSPONZA_MTL="${MODEL_ROOT}/sponza.mtl")
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
add_definitions(-DWINDOWWIDTH_DEFAULT=800)
add_definitions(-DWINDOWHEIGHT_DEFAULT=600)
add_definitions(-DMODEL_PATH="${MODEL_ROOT}")

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${INCLUDE_ROOT} 
					"${ASSIMP_ROOT}/include/assimp"
					"${UTILITY_ROOT}/include"
					"${UTILITY_ROOT}/include/GL"
					"${UTILITY_ROOT}/include/VM"
					"${SOIL_ROOT}/include"
					${GLEW_INCLUDE_DIRS}
					${GLUT_INCLUDE_DIR}
					${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${UTILITY_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SOIL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLUT_glut_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

