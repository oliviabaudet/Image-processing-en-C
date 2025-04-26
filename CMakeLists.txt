cmake_minimum_required(VERSION 3.31)
project(Image_processing_en_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Image_processing_en_C
        bmp8.c
        bmp8.h
        kernels.c
        kernels.h
        main.c)

add_executable(test_image
        test/bmp8_test.c
        kernels.c
        kernels.h
        bmp8.c
        bmp8.h)
