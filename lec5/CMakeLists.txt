cmake_minimum_required(VERSION 3.5)
project(lec5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp my.cpp my.h)
add_executable(lec5 ${SOURCE_FILES})