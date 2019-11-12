
cmake_minimum_required(VERSION 3.4.1)

set(APP_PLATFORM android-16)

set(LIBS_DIRECTORY ${CMAKE_SOURCE_DIR}/../../../libs)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        ../libyuv/include
)

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
        libyuv
        -ljnigraphics
        ${log-lib}
)