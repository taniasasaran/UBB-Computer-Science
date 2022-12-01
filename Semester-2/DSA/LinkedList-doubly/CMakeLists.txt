cmake_minimum_required(VERSION 3.21)
project(LinkedListEx)

set(CMAKE_CXX_STANDARD 14)

include_directories(LinkedListEx)

add_executable(LinkedListEx
        LinkedListEx/List.cpp
        LinkedListEx/List.h
        LinkedListEx/main.cpp)
