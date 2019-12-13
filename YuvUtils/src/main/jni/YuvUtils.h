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
typedef struct ConvertData {
    int dataSize;
    libyuv::RotationMode rotateMode;
    uint32 format;
    int targetWidth;
    int targetHeight;
    int crop_x = 0;
    int crop_y = 0;
} ConvertData;


#ifdef __cplusplus
extern "C" {
#endif



///////////////////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jbyteArray bitmapToNV21(JNIEnv *env, jclass clazz, jobject jbitmap);

JNIEXPORT jbyteArray bitmapToRgb565(JNIEnv *env, jclass clazz, jobject jbitmap);

JNIEXPORT jbyteArray bitmapToRgb24(JNIEnv *env, jclass clazz, jobject jbitmap);

JNIEXPORT jbyteArray bitmapToRgba(JNIEnv *env, jclass clazz, jobject jbitmap);

JNIEXPORT jbyteArray bitmapToI420(JNIEnv *env, jclass clazz, jobject jbitmap);



///////////////////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jbyteArray intArrayToByteArray(JNIEnv *env, jclass clazz, jintArray intArray);
JNIEXPORT jintArray byteArrayToIntArray(JNIEnv *env, jclass clazz, jbyteArray byteArray);


///////////////////////////////////////////////////////////////////////////////////////////////
JNIEXPORT jbyteArray imageFormatConvert(JNIEnv *env, jclass clazz,
                                        jbyteArray src_data, jint width, jint height,
                                        jint dataFormat, jint targetFormat);

JNIEXPORT jobject imageToBitmap(JNIEnv *env, jclass clazz,
                                jbyteArray src_data, jint width, jint height,
                                jint dataFormat, jint bitmapConfig);

JNIEXPORT jobject dataClipRotateToBitmap(JNIEnv *env, jclass clazz,
                                         jbyteArray byteArray, jint dataFormat,
                                         jint width, jint height, jint degree,
                                         jobject rect, jint bitmapConfig,
                                         jboolean priorityClip);

JNIEXPORT jbyteArray dataClipRotate(JNIEnv *env, jclass clazz,
                                    jbyteArray byteArray, jint dataFormat,
                                    jint width, jint height, jint degree,
                                    jobject rect, jint targetFormat,
                                    jboolean priorityClip);

///////////////////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jbyteArray dataMirror(JNIEnv *env, jclass clazz,
                                jbyteArray byteArray, jint width, jint height,
                                jint dataFormat, jint targetFormat,
                                jboolean isVerticalMirror);

JNIEXPORT jbyteArray dataScale(JNIEnv *env, jclass clazz,
                               jbyteArray byteArray, jint width, jint height,
                               jint dstWidth, jint dstHeight,
                               jint dataFormat, jint targetFormat,
                               jint filterMode);
///////////////////////////////////////////////////////////////////////////////////////////////

jbyte *checkDataAndConvert(JNIEnv *env, jbyteArray yuv420Data, int dataSize);

int convertDataHandle(JNIEnv *env, jint dataFormat,
                      jint width, jint height,
                      jint degree, jobject rect, jboolean priorityClip,
                      ConvertData *convertData);

jbyteArray
__ImageConvert__(JNIEnv *env, jbyteArray src_data, jint width, jint height, jint dataFormat, jint targetFormat, __convert__ convert);

jobject
__ImageToBitmap__(JNIEnv *env, jbyteArray src_data, jint width, jint height, jint dataFormat, jint targetFormat, __convert__ convert);


#ifdef __cplusplus
}
#endif

#endif //IMAGEUTILS_YUVUTILS_H
