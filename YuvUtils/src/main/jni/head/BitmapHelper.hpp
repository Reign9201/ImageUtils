//
// Created by 18081333 on 2019/11/19.
//

#ifndef IMAGEUTILS_BITMAPHELPER_HPP
#define IMAGEUTILS_BITMAPHELPER_HPP

#include <jni.h>
#include <android/bitmap.h>

template<typename Func>
jobject createBitmap8888(JNIEnv *env, int width, int height, Func callback);

#endif //IMAGEUTILS_BITMAPHELPER_HPP
