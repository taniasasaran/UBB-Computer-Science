cmake_minimum_required(VERSION 3.21)
project(a5_6_taniasasaran)

set(CMAKE_CXX_STANDARD 14)

add_executable(a5_6_taniasasaran
        main.cpp repository.cpp repository.h
        domain.cpp domain.h service.cpp
        service.h ui.cpp ui.h
        teste.h
        Dynamic_Vector.h)
