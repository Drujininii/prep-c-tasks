cmake_minimum_required(VERSION 3.5)
project(labirint)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Field.cpp Field.h utils.h algorithm.cpp algorithm.h test_txt.cpp test_txt.h)
add_executable(labirint ${SOURCE_FILES})