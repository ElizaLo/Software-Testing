cmake_minimum_required(VERSION 3.13)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)

#include_directories(Calculator_src)
#include_directories(tests)
#add_subdirectory(tests/lib/googletest)
add_subdirectory(Calculator_src)
add_subdirectory(tests)

#include_directories(tests/lib/googletest/include)