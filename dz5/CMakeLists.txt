cmake_minimum_required(VERSION 3.5)
project(dz5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp Worker.cpp Worker.h)
add_executable(dz5 ${SOURCE_FILES} Worker.cpp Worker.h)