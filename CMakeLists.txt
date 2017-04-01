cmake_minimum_required (VERSION 2.6)
project (clustered_shading)

set (CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")

set (SOURCE_ROOT "${PROJECT_SOURCE_DIR}/source")
set (INCLUDE_ROOT "${PROJECT_SOURCE_DIR}/include")
set (SO_ROOT "${PROJECT_SOURCE_DIR}/shared")
set (ASSIMP_ROOT "${SO_ROOT}/assimp")
set (MODEL_ROOT "${PROJECT_SOURCE_DIR}/model")
set (GLM_ROOT "${PROJECT_SOURCE_DIR}/lib/glm")
set (UTILITY_ROOT "${PROJECT_SOURCE_DIR}/lib/Utility")
set (SOIL_ROOT "${PROJECT_SOURCE_DIR}/lib/SOIL")

link_directories(${ASSIMP_ROOT})
file (GLOB SOURCES "${SOURCE_ROOT}/*.cpp")
file (GLOB UTILITY_LIBRARIES "${UTILITY_ROOT}/obj/*.o")
file (GLOB SOIL_LIBRARIES "${SOIL_ROOT}/obj/*.o")

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
					"${ASSIMP_ROOT}/include"
					"${UTILITY_ROOT}/include"
					"${UTILITY_ROOT}/include/GL"
					"${UTILITY_ROOT}/include/VM"
					"${SOIL_ROOT}/src"
					${GLEW_INCLUDE_DIRS}
					${GLUT_INCLUDE_DIR}
					${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} "${ASSIMP_ROOT}/libassimp.so")
target_link_libraries(${PROJECT_NAME} ${UTILITY_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SOIL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLUT_glut_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
#asdasdad
#adasdasda
