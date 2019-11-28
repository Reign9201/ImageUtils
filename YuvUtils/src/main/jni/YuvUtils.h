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

JNIEXPORT jbyteArray
nv21ToRgba(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

JNIEXPORT jbyteArray
nv21ToRgb565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

JNIEXPORT jbyteArray
nv21ToI420(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

JNIEXPORT jobject
nv21ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

JNIEXPORT jobject
nv21ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height);

///////////////////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jbyteArray
i420ToNV21(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height);

JNIEXPORT jbyteArray
i420ToRgba(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height);

JNIEXPORT jbyteArray
i420ToRgb(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height);

JNIEXPORT jobject
i420ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height);

JNIEXPORT jobject
i420ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height);

///////////////////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jbyteArray
rgbaToNV21(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height);

JNIEXPORT jbyteArray
rgbaToI420(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height);

JNIEXPORT jbyteArray
rgbaToRgb(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height);

JNIEXPORT jobject
rgbaToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height);

JNIEXPORT jobject
rgbaToBitmap565(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height);

///////////////////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jbyteArray
rgbToNV21(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height);

JNIEXPORT jbyteArray
rgbToI420(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height);

JNIEXPORT jbyteArray
rgbToRgba(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height);

JNIEXPORT jobject
rgbToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height);

JNIEXPORT jobject
rgbToBitmap565(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height);

///////////////////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jbyteArray bitmapToNV21(JNIEnv *env, jclass clazz, jobject jbitmap);

JNIEXPORT jbyteArray bitmapToRgb(JNIEnv *env, jclass clazz, jobject jbitmap);

JNIEXPORT jbyteArray bitmapToRgba(JNIEnv *env, jclass clazz, jobject jbitmap);

JNIEXPORT jintArray bitmap2Rgba(JNIEnv *env, jclass clazz, jobject jbitmap);

JNIEXPORT jbyteArray bitmapToI420(JNIEnv *env, jclass clazz, jobject jbitmap);



///////////////////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jbyteArray intToByte(JNIEnv *env, jclass clazz, jintArray intArray);
JNIEXPORT jintArray byteToInt(JNIEnv *env, jclass clazz, jbyteArray byteArray);


///////////////////////////////////////////////////////////////////////////////////////////////

jbyte *checkDataAndConvert(JNIEnv *env, jbyteArray yuv420Data,int dataSize);

#ifdef __cplusplus
}
#endif

#endif //IMAGEUTILS_YUVUTILS_H
