cmake_minimum_required(VERSION 3.21)
project(a8_9_taniasasaran)

include_directories(src)

add_executable(a8_9_taniasasaran
        src/domain.cpp
        src/domain.h
        src/main.cpp
        src/repository.cpp
        src/repository.h
        src/service.cpp
        src/service.h
        src/ui.cpp
        src/ui.h src/exception.h src/file.cpp src/file.h)
