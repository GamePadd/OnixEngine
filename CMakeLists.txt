cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 23)

project (Imp3D)

set(GLAD_DIR ${CMAKE_SOURCE_DIR}/thirdparty/GLAD)
set(STB_DIR ${CMAKE_SOURCE_DIR}/thirdparty/STB)
set(TINYOBJ_DIR ${CMAKE_SOURCE_DIR}/thirdparty/TinyObj)

add_subdirectory("thirdparty/GLFW")
add_subdirectory("thirdparty/GLM")
add_subdirectory ("Imp3D")

