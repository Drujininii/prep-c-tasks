cmake_minimum_required(VERSION 3.5)
project(dz6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Volume_Figure.cpp Volume_Figure.h Ball.cpp Ball.h Cylinder.cpp Cylinder.h Circle.cpp Circle.h Enter_Data.cpp Enter_Data.h)
add_executable(dz6 ${SOURCE_FILES} Volume_Figure.cpp Volume_Figure.h Ball.cpp Ball.h Cylinder.cpp Cylinder.h)