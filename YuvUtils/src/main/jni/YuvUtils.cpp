//# pragma once


#include "YuvUtils.h"
#include "head/BitmapHelper.hpp"
#include <string.h>

static JNINativeMethod gMethods[] = {
        {"test",             "()I",                             (void *) test},
        {"bitmapToNV21",     "(Landroid/graphics/Bitmap;)[B",   (void *) bitmapToNV21},
        {"nv21ToRgba8888",   "([BII)[B",                        (void *) NV21ToRGBA_8888},
        {"nv21ToBitmap8888", "([BII)Landroid/graphics/Bitmap;", (void *) NV21ToBitmap8888},
        {"nv21ToBitmap565",  "([BII)Landroid/graphics/Bitmap;", (void *) NV21ToBitmap565},
        {"nv21ToI420",       "([BII)[B",                        (void *) NV21ToI420s},
        {"i420ToBitmap8888", "([BII)Landroid/graphics/Bitmap;", (void *) I420ToBitmap8888}

};

const char *JNI_NATIVE_INTERFACE_CLASS = "com/yancy/yuvutils/YuvUtils";


JNIEXPORT jint
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6)) {
        return JNI_ERR;
    }

    jclass cls = env->FindClass(JNI_NATIVE_INTERFACE_CLASS);
    if (cls == NULL) {
        return JNI_ERR;
    }

    jint nRes = env->RegisterNatives(cls, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
    if (nRes < 0) {
        return JNI_ERR;
    }

    LOGI("YuvUtils.so JNI_OnLoad");

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {

    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6)) {
        return;
    }

    jclass cls = env->FindClass(JNI_NATIVE_INTERFACE_CLASS);
    if (cls == NULL) {
        return;
    }

    LOGI("YuvUtils.so JNI_OnUnload");
    env->UnregisterNatives(cls);
}

int test(JNIEnv *env, jclass clazz) {
    return 100;
}

jbyteArray bitmapToNV21(JNIEnv *env, jclass clazz, jobject jbitmap) {
    if (jbitmap == NULL) {
        return NULL;
    }
    unsigned long s = logger::getTime();
    AndroidBitmapInfo info;
    uint8 *pixels;
    AndroidBitmap_getInfo(env, jbitmap, &info);
    AndroidBitmap_lockPixels(env, jbitmap, reinterpret_cast<void **>(&pixels));

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) { //其实对应的是ABGR
        logger::error("======================");
    }

    int width = info.width;
    int height = info.height;

    int dst_nv21_size = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
    logger::error("dst_nv21_size = ", dst_nv21_size);

    uint8 *dst_nv21 = new uint8[dst_nv21_size];
    uint8 *dst_y = dst_nv21;
    int dst_stride_y = width;
    uint8 *dst_vu = dst_nv21 + width * height;
    int dst_stride_uv = (width + 1) / 2 * 2;


    libyuv::ABGRToARGB(pixels, info.stride, pixels, info.stride, width, height);
    libyuv::ARGBToNV21(pixels, info.stride, dst_y, dst_stride_y, dst_vu, dst_stride_uv, width,
                       height);

    jbyteArray res = env->NewByteArray(dst_nv21_size);
    env->SetByteArrayRegion(res, 0, dst_nv21_size, reinterpret_cast<const jbyte *>(dst_nv21));
    AndroidBitmap_unlockPixels(env, jbitmap);

    logger::printTime("times = ", s);

    delete[] dst_nv21;
    return res;
}

jbyteArray
NV21ToRGBA_8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {


    jbyte *src_data = env->GetByteArrayElements(nv21Data, JNI_FALSE);

    if (height * 3.0 / 2.0 * width != env->GetArrayLength(nv21Data)) {
        logger::error("nv21 data error, please check it.");
        return NULL;
    }
    uint8 *dst_data = new uint8[width * height * 4];

    int res = NV21ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    logger::error("res = ", res);
    jbyteArray rgba = env->NewByteArray(width * height * 4);
    env->SetByteArrayRegion(rgba, 0, width * height * 4, reinterpret_cast<const jbyte *>(dst_data));

    env->ReleaseByteArrayElements(nv21Data, src_data, JNI_FALSE);
    delete[] dst_data;


    return rgba;
}

jobject NV21ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = env->GetByteArrayElements(nv21Data, JNI_FALSE);

    if (height * 3.0 / 2.0 * width != env->GetArrayLength(nv21Data)) {
        logger::error("nv21 data error, please check it.");
        return NULL;
    }
    auto callback = [=](unsigned char *pixel) -> void {
        NV21ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };

    jobject jbitmap = createBitmap(env, width, height, callback);

    // 释放资源
    env->ReleaseByteArrayElements(nv21Data, src_data, JNI_FALSE);

    return jbitmap;

}

template<typename Func>
jobject createBitmap(JNIEnv *env, int width, int height, Func callback, BitmapFormat format) {
    jclass bitmapClazz = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmap = env->GetStaticMethodID(bitmapClazz, "createBitmap",
                                                    "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jclass cls = env->FindClass("android/graphics/Bitmap$Config");
    jfieldID fid = env->GetStaticFieldID(cls, formatToStr(format),
                                         "Landroid/graphics/Bitmap$Config;");

    jobject config = env->GetStaticObjectField(cls, fid);
    jobject jbitmap = env->CallStaticObjectMethod(bitmapClazz, createBitmap, width, height, config);

    AndroidBitmapInfo info;
    unsigned char *pixels = 0;
    try {
        AndroidBitmap_getInfo(env, jbitmap, &info);
        AndroidBitmap_lockPixels(env, jbitmap, reinterpret_cast<void **>(&pixels));

        callback(pixels);

        AndroidBitmap_unlockPixels(env, jbitmap);

    } catch (...) {
        return NULL;
    }
    return jbitmap;
}


jobject NV21ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = env->GetByteArrayElements(nv21Data, JNI_FALSE);

    if (height * 3.0 / 2.0 * width != env->GetArrayLength(nv21Data)) {
        logger::error("nv21 data error, please check it.");
        return NULL;
    }
    auto callback = [=](unsigned char *pixel) -> void {
        NV21ToRGB(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };

    jobject jbitmap = createBitmap(env, width, height, callback, RGB_565);

    // 释放资源
    env->ReleaseByteArrayElements(nv21Data, src_data, JNI_FALSE);

    return jbitmap;
}

jbyteArray NV21ToI420s(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = env->GetByteArrayElements(nv21Data, JNI_FALSE);

    if (height * 3.0 / 2.0 * width != env->GetArrayLength(nv21Data)) {
        logger::error("nv21 data error, please check it.");
        return NULL;
    }
    uint8 *dst_i420_data = new uint8[height * width * 3 / 2];
    NV21ToI420(reinterpret_cast<uint8 *>(src_data), width, height, dst_i420_data);
    jbyteArray i420 = env->NewByteArray(height * width * 3 / 2);
    env->SetByteArrayRegion(i420, 0, height * width * 3 / 2,
                            reinterpret_cast<const jbyte *>(dst_i420_data));

    env->ReleaseByteArrayElements(nv21Data, src_data, 0);

    return i420;
}

jobject I420ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = env->GetByteArrayElements(i420Data, JNI_FALSE);
    if (height * 3.0 / 2.0 * width != env->GetArrayLength(i420Data)) {
        logger::error("i420 data error, please check it.");
        return NULL;
    }
    auto callback = [=](unsigned char*pixel){
        I420ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    jobject  jbitmap = createBitmap(env, width, height, callback);
    env->ReleaseByteArrayElements(i420Data, src_data, 0);
    return jbitmap;
}







