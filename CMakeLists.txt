cmake_minimum_required(VERSION 3.10)
project(mash)

set(CMAKE_CXX_STANDARD 17)
add_executable(mash src/main.cpp src/main.h src/Lexer.cpp src/Lexer.h src/Parser.cpp src/Parser.h src/Interpreter.cpp src/Interpreter.h src/Nodes.cpp src/Nodes.h)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(src)
add_executable(test tests/TestMain.cpp tests/TestOperators.cpp src/Lexer.cpp src/Lexer.h src/Parser.cpp src/Parser.h src/Interpreter.cpp src/Interpreter.h src/Nodes.cpp src/Nodes.h)
target_link_libraries(test gtest_main)
include(GoogleTest)
gtest_discover_tests(test)



