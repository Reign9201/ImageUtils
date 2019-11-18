//# pragma once


#include "YuvUtils.h"
#include <string.h>

static JNINativeMethod gMethods[] = {
        {"test",             "()I",                             (void *) test},
        {"bitmapToNV21",     "(Landroid/graphics/Bitmap;)[B",   (void *) bitmapToNV21},
        {"NV21ToRGBA_8888",  "([BII)[B",                        (void *) NV21ToRGBA_8888},
        {"NV21ToBitmap8888", "([BII)Landroid/graphics/Bitmap;", (void *) NV21ToBitmap8888}

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

    //env->ReleaseByteArrayElements(nv21Data, src_data, JNI_FALSE);
    //  delete[] dst_data;


    return rgba;
}

int NV21ToRGBA(uint8 *src_nv21_data, int width, int height, uint8 *dst_rgba) {

    int res = libyuv::NV21ToARGB(src_nv21_data, width,
                                 src_nv21_data + width * height, width,
                                 dst_rgba, width * 4,
                                 width, height);

    //logger::error("res--->", res);
    if (res != 0) { return -1; }

    // 实测，libyuv中的ABGR格式对应Android Bitmap中的ARGB_8888
    res = libyuv::ARGBToABGR(dst_rgba, width * 4, dst_rgba, width * 4, width, height);

    return res;
}

jobject NV21ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = env->GetByteArrayElements(nv21Data, JNI_FALSE);

    if (height * 3.0 / 2.0 * width != env->GetArrayLength(nv21Data)) {
        logger::error("nv21 data error, please check it.");
        return NULL;
    }

    jclass bitmapClazz = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmap = env->GetStaticMethodID(bitmapClazz, "createBitmap",
                                                    "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jclass cls = env->FindClass("android/graphics/Bitmap$Config");
    jfieldID fid = env->GetStaticFieldID(cls, "ARGB_8888", "Landroid/graphics/Bitmap$Config;");
    jobject config = env->GetStaticObjectField(cls, fid);
    jobject jbitmap = env->CallStaticObjectMethod(bitmapClazz, createBitmap, width, height, config);

    AndroidBitmapInfo info;
    uint8 *pixels = 0;
    try {
        AndroidBitmap_getInfo(env, jbitmap, &info);
        AndroidBitmap_lockPixels(env, jbitmap, reinterpret_cast<void **>(&pixels));

        NV21ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixels);
        AndroidBitmap_unlockPixels(env, jbitmap);

    } catch (...) {
        return NULL;
    }

    // 释放资源
    env->ReleaseByteArrayElements(nv21Data, src_data, JNI_FALSE);


    return jbitmap;

}





