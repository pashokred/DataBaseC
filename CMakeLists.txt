cmake_minimum_required(VERSION 3.17)
project(Test C)

set(CMAKE_C_STANDARD 11)

add_executable(Test main.c read.h interface.h structures.h functions.h)