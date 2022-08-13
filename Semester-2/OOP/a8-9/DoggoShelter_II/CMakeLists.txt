cmake_minimum_required(VERSION 3.21)
project(DoggoShelter_II)

set(CMAKE_CXX_STANDARD 14)

add_executable(DoggoShelter_II
        domain.cpp domain.h exception.h
        repository.cpp repository.h
        service.cpp service.h
        ui.h ui.cpp file.cpp file.h
        main.cpp)
