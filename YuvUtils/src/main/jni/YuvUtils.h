//
// Created by XuYanjun on 2019/11/12.
//

#ifndef IMAGEUTILS_YUVUTILS_H
#define IMAGEUTILS_YUVUTILS_H

#include "head/ColorConvert.hpp"
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

JNIEXPORT jbyteArray
NV21ToRGB_565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

JNIEXPORT jobject
NV21ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

JNIEXPORT jobject
NV21ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

JNIEXPORT jobject
I420ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height);

JNIEXPORT jbyteArray
NV21ToI420s(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);




#ifdef __cplusplus
}
#endif

#endif //IMAGEUTILS_YUVUTILS_H
