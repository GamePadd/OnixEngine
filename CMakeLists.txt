cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 23)

project (OnixEngine)

set(GLAD_DIR ${CMAKE_SOURCE_DIR}/thirdparty/GLAD)

add_subdirectory("thirdparty/GLFW")
add_subdirectory ("OnixEngine")

