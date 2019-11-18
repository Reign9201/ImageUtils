//
// Created by 18081333 on 2019/11/12.
//

#ifndef IMAGEUTILS_YUVUTILS_H
#define IMAGEUTILS_YUVUTILS_H

#include <libyuv.h>
#include <jni.h>
#include <android/bitmap.h>
#include "logger.hpp"

//using namespace libyuv;

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT int test(JNIEnv *env, jclass clazz);

JNIEXPORT jbyteArray bitmapToNV21(JNIEnv *env, jclass clazz, jobject jbitmap);


JNIEXPORT jbyteArray
NV21ToRGBA_8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

JNIEXPORT jobject
NV21ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

int NV21ToRGBA(uint8 *src_nv21_data, int width, int height, uint8 *dst_rgba);


#ifdef __cplusplus
}
#endif

#endif //IMAGEUTILS_YUVUTILS_H
