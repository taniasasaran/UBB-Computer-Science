cmake_minimum_required(VERSION 3.21)
project(pharmacy C)

set(CMAKE_C_STANDARD 99)

add_executable(pharmacy main.c main.h
        Medication.c Medication.h
        repository.c repository.h
#        service.c service.h
        ui.c ui.h DynamicArray.c DynamicArray.h
        Operation.c Operation.h
        service2.c service2.h
        tests.c tests.h
        )

