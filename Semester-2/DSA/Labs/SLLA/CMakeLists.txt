cmake_minimum_required(VERSION 3.21)
project(SLLA)

set(CMAKE_CXX_STANDARD 14)

include_directories("SLLA example")

add_executable(SLLA
        "SLLA example/App.cpp"
        "SLLA example/Iterator.cpp"
        "SLLA example/Iterator.h"
        "SLLA example/SLLArr.cpp"
        "SLLA example/SLLArr.h")
