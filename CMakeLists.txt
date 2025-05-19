cmake_minimum_required(VERSION 3.31)
project(Image_processing_en_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Image_processing_en_C
        bmp8.c
        bmp8.h
        bmp24.c
        bmp24.h
        kernels.c
        kernels.h
        menu.c
        menu.h
        main.c
)
target_link_libraries(Image_processing_en_C m)

add_executable(test_image8
        test/bmp8_test.c
        kernels.c
        kernels.h
        bmp8.c
        bmp8.h
)

add_executable(test_image24
        test/bmp24_test.c
        kernels.c
        kernels.h
        bmp24.c
        bmp24.h
)
target_link_libraries(test_image24 m)