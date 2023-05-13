cmake_minimum_required(VERSION 3.21)
project(refrigerator C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable( refrigerator
        main_f.c
        DynamicArrayOperation.c
        DynamicArrayOperation.h
        DynamicArrayProduct.c
        DynamicArrayProduct.h
        product.c product.h
        Operation.h Operation.c
        repository.c repository.h
        service.c service.h
        tests.c tests.h
        ui.c ui.h)