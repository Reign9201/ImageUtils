cmake_minimum_required(VERSION 3.4.1)

set(APP_PLATFORM android-16)

set(LIBS_DIRECTORY ${CMAKE_SOURCE_DIR}/../../../libs)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(APP_ABI armeabi-v7a)

include_directories(
        ${ANDROID_NDK}/platforms/android-16/arch-arm/usr/include
        ${ANDROID_NDK}/platforms/android-16/arch-arm/usr/include/android
        include
)

add_library(libyuv_static SHARED IMPORTED)
set_target_properties(libyuv_static PROPERTIES IMPORTED_LOCATION ${LIBS_DIRECTORY}/${ANDROID_ABI}/libyuv_static.a)


add_library(
        YuvUtils
        SHARED
        YuvUtils.cpp
        core/BitmapHelper.cpp
)


find_library(log-lib log)
find_library(jnigraphics-lib jnigraphics)

target_link_libraries(
        YuvUtils
        libyuv_static
        ${log-lib}
        ${jnigraphics-lib}
)