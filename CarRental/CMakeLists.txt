cmake_minimum_required(VERSION 3.21)
project(C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(C
        car.c
        car.h
        client.c
        client.h
        common.c
        common.h
        genFuncs.c
        genFuncs.h
        main.c
        supplier.c
        supplier.h)
