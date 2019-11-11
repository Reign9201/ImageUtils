# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set(APP_PLATFORM android-21)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#set(APP_ABI armeabi armeabi-v7a x86 mips)
#set(APP_OPTIM debug)
#set (PROJ_PATH $(call my-dir))

set(APP_ABI armeabi-v7a)


#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})


ADD_SUBDIRECTORY(imageConvert)
ADD_SUBDIRECTORY(libyuv)