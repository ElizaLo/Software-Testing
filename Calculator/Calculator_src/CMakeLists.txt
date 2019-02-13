cmake_minimum_required(VERSION 3.13)
project(Calculator_src)

set(CMAKE_CXX_STANDARD 17)

add_executable(Calculator_src main.cpp
        Calculator.cpp
        Calculator.h
        Lexeme.cpp
        Lexeme.h
        List.cpp
        Test.cpp
        Test.h)