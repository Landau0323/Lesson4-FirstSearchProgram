cmake_minimum_required(VERSION 3.8)
project(FirstSearchProgram)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Maze.cpp Maze.h XY.cpp XY.h GXY.cpp GXY.h Car.cpp Car.h XYtheta.cpp XYtheta.h parameter.h)
add_executable(FirstSearchProgram ${SOURCE_FILES})