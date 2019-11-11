
cmake_minimum_required(VERSION 3.4.1)

add_library(
        libyuv

        SHARED

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

        if (${ANDROID_ABI} == "armeabi-v7a") {
        message ("ppppppppppppppppppppppppppppppp")
        source/compare_neon.cc.neon
        source/rotate_neon.cc.neon
        source/row_neon.cc.neon
        source/scale_neon.cc.neon
        }
)


find_library(log-lib log)


target_link_libraries(
        libyuv
        -ljnigraphics
        ${log-lib}
)