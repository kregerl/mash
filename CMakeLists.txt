cmake_minimum_required(VERSION 3.10)
project(mash)

set(CMAKE_CXX_STANDARD 17)

add_executable(mash src/main.cpp src/main.h src/Operations.cpp src/Operations.h)
