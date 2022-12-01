cmake_minimum_required(VERSION 3.21)
project(916_2_FixedCapBiMap)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(916_2_FixedCapBiMap
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        FixedCapBiMap.cpp
        FixedCapBiMap.h
        FixedCapBiMapIterator.cpp
        FixedCapBiMapIterator.h
        ShortTest.cpp
        ShortTest.h)
