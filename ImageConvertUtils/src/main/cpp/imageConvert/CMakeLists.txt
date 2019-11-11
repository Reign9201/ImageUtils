
cmake_minimum_required(VERSION 3.4.1)

add_library(
        bitmapConvert

        SHARED

        bitmapConvert.cpp
        image.c
)


find_library(
        log-lib

        log
)


target_link_libraries(
        bitmapConvert
        -ljnigraphics
        ${log-lib}
)