cmake_minimum_required(VERSION 3.4.1)

include_directories(libyuv/include)

add_subdirectory(libyuv)

add_library( YuvUtils
        SHARED
        YuvUtils.cpp)


find_library(log-lib
        log )

target_link_libraries( YuvUtils
        ${log-lib}
        yuv)