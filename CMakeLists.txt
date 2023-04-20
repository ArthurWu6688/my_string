cmake_minimum_required(VERSION 3.25)
project(my_string)

set(CMAKE_CXX_STANDARD 11)

add_executable(test_cpp main.cpp my_string.h)
