//
// Created by XuYanjun on 2019/11/19.
//

#ifndef IMAGEUTILS_BITMAPHELPER_HPP
#define IMAGEUTILS_BITMAPHELPER_HPP

#include <jni.h>
#include <android/bitmap.h>

enum BitmapFormat {
    ARGB_8888,
    RGB_565
};

const char* formatToStr(BitmapFormat format) {
    switch (format) {
        case RGB_565:
            return "RGB_565";
        case ARGB_8888:
        default:
            return "ARGB_8888";
    }
}

template<typename Func>
jobject createBitmap(JNIEnv *env, int width, int height, Func callback,
                     BitmapFormat format = ARGB_8888);

#endif //IMAGEUTILS_BITMAPHELPER_HPP
