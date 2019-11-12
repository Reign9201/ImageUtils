//
// Created by 18081333 on 2019/11/12.
//

#ifndef IMAGEUTILS_YUVUTILS_H
#define IMAGEUTILS_YUVUTILS_H

#include <libyuv.h>
#include <jni.h>
#include <android/bitmap.h>
#include "logger.hpp"

using namespace libyuv;

class YuvUtils {
public:
    void nv21ToArgb(jbyte *nv21data, jint width, jint height, uint8 *argbData);
};

#endif //IMAGEUTILS_YUVUTILS_H
