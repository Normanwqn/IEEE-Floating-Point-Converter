cmake_minimum_required(VERSION 3.16)
project(floatingConverter)

set(CMAKE_CXX_STANDARD 20)

add_executable(floatingConverter Converter.h Converter.cpp main.cpp)