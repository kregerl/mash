cmake_minimum_required(VERSION 3.10)
project(mash)

set(CMAKE_CXX_STANDARD 17)

add_executable(mash src/main.cpp src/main.h src/Operations.cpp src/Operations.h src/Value.cpp src/Value.h src/Collection1D.h src/Collection1D.cpp src/Vector.cpp src/Vector.h src/Set.cpp src/Set.h src/Number.cpp src/Number.h src/Lexer.cpp src/Lexer.h src/Parser.cpp src/Parser.h src/Interpreter.cpp src/Interpreter.h src/Nodes.cpp src/Nodes.h)
