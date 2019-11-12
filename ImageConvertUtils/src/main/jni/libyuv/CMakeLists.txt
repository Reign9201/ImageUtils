
cmake_minimum_required(VERSION 3.4.1)
set(APP_PLATFORM android-16)

set(LIBS_DIRECTORY ${CMAKE_SOURCE_DIR}/../jniLibs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        include
        source
)

add_library(
        libyuv

        STATIC

        YuvUtils.cpp
        source/compare.cc
        source/compare_common.cc
        source/compare_neon64.cc
        source/compare_gcc.cc
        source/convert.cc
        source/convert_argb.cc
        source/convert_from.cc
        source/convert_from_argb.cc
        source/convert_to_argb.cc
        source/convert_to_i420.cc
        source/cpu_id.cc
        source/planar_functions.cc
        source/rotate.cc
        source/rotate_argb.cc
        source/rotate_mips.cc
        source/rotate_neon64.cc
        source/row_any.cc
        source/row_common.cc
        source/row_mips.cc
        source/row_neon64.cc
        source/row_gcc.cc
        source/scale.cc
        source/scale_any.cc
        source/scale_argb.cc
        source/scale_common.cc
        source/scale_mips.cc
        source/scale_neon64.cc
        source/scale_gcc.cc
        source/video_common.cc
)

set_target_properties(libyuv PROPERTIES OUTPUT_NAME "yuv")

GET_TARGET_PROPERTY(OUTPUT_VALUE libyuv OUTPUT_NAME)

target_link_libraries(
        libyuv
)