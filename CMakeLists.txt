cmake_minimum_required(VERSION 3.10)
project(mash)

set(CMAKE_CXX_STANDARD 17)

add_executable(mash src/main.cpp src/main.h src/Lexer.cpp src/Lexer.h src/Parser.cpp src/Parser.h src/Interpreter.cpp src/Interpreter.h src/Nodes.cpp src/Nodes.h)
