# cmake_minimum_required(VERSION <specify CMake version here>)
project(first)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp library.cpp)

add_executable(first ${SOURCE_FILES})
