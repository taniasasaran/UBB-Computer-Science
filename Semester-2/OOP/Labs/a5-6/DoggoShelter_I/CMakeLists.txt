cmake_minimum_required(VERSION 3.21)
project(DoggoShelter_I)

set(CMAKE_CXX_STANDARD 14)

add_executable(DoggoShelter_I main.cpp
        domain.h domain.cpp repository.h repository.cpp
        service.h service.cpp ui.cpp ui.h)
