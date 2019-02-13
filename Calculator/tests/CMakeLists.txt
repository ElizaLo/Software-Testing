cmake_minimum_required(VERSION 3.13)
project(tests)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

include_directories(lib/googletest/include)
add_executable(tests main.cpp
        ../Calculator_src/Calculator.cpp
        ../Calculator_src/Calculator.h
        ../Calculator_src/Lexeme.cpp
        ../Calculator_src/Lexeme.h
        ../Calculator_src/List.cpp
        ../Calculator_src/Test.cpp
        ../Calculator_src/Test.h)
        #../Calculator_src/main.cpp)
target_link_libraries(tests gtest gtest_main)