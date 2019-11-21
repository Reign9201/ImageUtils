//# pragma once


#include "YuvUtils.h"
#include "head/cppToJavaHelper.hpp"
#include <string.h>

static JNINativeMethod gMethods[] = {
        // NV21 转换成其他格式
        {"nv21ToRgba",       "([BII)[B",                        (void *) nv21ToRgba},
        {"nv21ToRgb",        "([BII)[B",                        (void *) nv21ToRgb565},
        {"nv21ToI420",       "([BII)[B",                        (void *) nv21ToI420},
        {"nv21ToBitmap8888", "([BII)Landroid/graphics/Bitmap;", (void *) nv21ToBitmap8888},
        {"nv21ToBitmap565",  "([BII)Landroid/graphics/Bitmap;", (void *) nv21ToBitmap565},

        // I420 转换成其他格式
        {"i420ToNV21",       "([BII)[B",                        (void *) i420ToNV21},
        {"i420ToRgba",       "([BII)[B",                        (void *) i420ToRgba},
        {"i420ToRgb",        "([BII)[B",                        (void *) i420ToRgb},
        {"i420ToBitmap8888", "([BII)Landroid/graphics/Bitmap;", (void *) i420ToBitmap8888},
        {"i420ToBitmap565",  "([BII)Landroid/graphics/Bitmap;", (void *) i420ToBitmap565},

        // RGBA 转换成其他格式
        {"rgbaToNV21",       "([BII)[B",                        (void *) rgbaToNV21},
        {"rgbaToI420",       "([BII)[B",                        (void *) rgbaToI420},
        {"rgbaToRgb",        "([BII)[B",                        (void *) rgbaToRgb},
        {"rgbaToBitmap8888", "([BII)Landroid/graphics/Bitmap;", (void *) rgbaToBitmap8888},
        {"rgbaToBitmap565",  "([BII)Landroid/graphics/Bitmap;", (void *) rgbaToBitmap565},

        // RGB 转换成其他格式
        {"rgbToNV21",        "([BII)[B",                        (void *) rgbToNV21},
        {"rgbToI420",        "([BII)[B",                        (void *) rgbToI420},
        {"rgbToRgba",        "([BII)[B",                        (void *) rgbToRgba},
        {"rgbToBitmap8888",  "([BII)Landroid/graphics/Bitmap;", (void *) rgbToBitmap8888},
        {"rgbToBitmap565",   "([BII)Landroid/graphics/Bitmap;", (void *) rgbToBitmap565},

        // Bitmap 转换成其他格式
        {"bitmapToNV21",     "(Landroid/graphics/Bitmap;)[B",   (void *) bitmapToNV21},
        {"bitmapToRgb",      "(Landroid/graphics/Bitmap;)[B",   (void *) bitmapToRgb},
        {"bitmapToRgba",     "(Landroid/graphics/Bitmap;)[B",   (void *) bitmapToRgba},
        {"bitmapToI420",     "(Landroid/graphics/Bitmap;)[B",   (void *) bitmapToI420},

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


jbyteArray nv21ToRgba(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, nv21Data, width, height);
    auto callback = [=](uint8 *dst_data) -> int {
        return NV21ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, nv21Data, src_data, width * height * 4, callback);

}

jbyteArray nv21ToRgb565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, nv21Data, width, height);
    auto callback = [=](uint8 *dst_data) -> int {
        return NV21ToRGB(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, nv21Data, src_data, width * height * 2, callback);
}

jbyteArray nv21ToI420(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, nv21Data, width, height);
    auto callback = [=](uint8 *dst_data) -> int {
        return NV21ToI420(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, nv21Data, src_data, width * height * 3 / 2, callback);
}

jobject nv21ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, nv21Data, width, height);
    auto callback = [=](unsigned char *pixel) -> int {
        return NV21ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };

    return createBitmap(env, nv21Data, src_data, width, height, callback);
}

jobject nv21ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, nv21Data, width, height);
    auto callback = [=](unsigned char *pixel) -> void {
        NV21ToRGB(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, nv21Data, src_data, width, height, callback, RGB_565);
}


jbyteArray i420ToNV21(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, i420Data, width, height);
    auto callback = [=](uint8 *dst_data) -> int {
        return I420ToNV21(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, i420Data, src_data, width * height * 3 / 2, callback);
}

jbyteArray i420ToRgba(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, i420Data, width, height);
    auto callback = [=](uint8 *dst_data) -> int {
        return I420ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, i420Data, src_data, width * height * 4, callback);
}

jbyteArray i420ToRgb(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, i420Data, width, height);
    auto callback = [=](uint8 *dst_data) -> int {
        return I420ToRGB(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, i420Data, src_data, width * height * 2, callback);
}

jobject
i420ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, i420Data, width, height);
    auto callback = [=](unsigned char *pixel) -> void {
        I420ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, i420Data, src_data, width, height, callback);
}

jobject
i420ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkYuv420DataAndConvert(env, i420Data, width, height);
    auto callback = [=](unsigned char *pixel) -> void {
        I420ToRGB(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, i420Data, src_data, width, height, callback, RGB_565);
}

jbyteArray rgbaToNV21(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    return nullptr;
}

jbyteArray rgbaToI420(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    return nullptr;
}

jbyteArray rgbaToRgb(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    return nullptr;
}

jobject
rgbaToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    return nullptr;
}

jobject
rgbaToBitmap565(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    return nullptr;
}

jbyteArray rgbToNV21(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    return nullptr;
}

jbyteArray rgbToI420(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    return nullptr;
}

jbyteArray rgbToRgba(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    return nullptr;
}

jobject
rgbToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    return nullptr;
}

jobject
rgbToBitmap565(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    return nullptr;
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

jbyteArray bitmapToRgb(JNIEnv *env, jclass clazz, jobject jbitmap) {
    return nullptr;
}

jbyteArray bitmapToRgba(JNIEnv *env, jclass clazz, jobject jbitmap) {
    return nullptr;
}

jbyteArray bitmapToI420(JNIEnv *env, jclass clazz, jobject jbitmap) {
    return nullptr;
}

jbyte *checkYuv420DataAndConvert(JNIEnv *env, jbyteArray yuv420Data, jint width, jint height) {
    if (height * 3.0 / 2.0 * width != env->GetArrayLength(yuv420Data)) {
        logger::error("i420 data error, please check it.");
        return NULL;
    }
    return env->GetByteArrayElements(yuv420Data, JNI_FALSE);
}

template<typename Func>
jobject
createBitmap(JNIEnv *env, jbyteArray data, jbyte *src_data, int width, int height,
             Func callback,
             BitmapFormat format) {
    if (src_data == NULL) {
        return nullptr;
    }
    jclass bitmapClazz = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmap = env->GetStaticMethodID(bitmapClazz, "createBitmap",
                                                    "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jclass cls = env->FindClass("android/graphics/Bitmap$Config");
    jfieldID fid = env->GetStaticFieldID(cls, formatToStr(format),
                                         "Landroid/graphics/Bitmap$Config;");

    jobject config = env->GetStaticObjectField(cls, fid);
    jobject jbitmap = env->CallStaticObjectMethod(bitmapClazz, createBitmap, width, height,
                                                  config);

    AndroidBitmapInfo info;
    unsigned char *pixels = 0;
    try {
        AndroidBitmap_getInfo(env, jbitmap, &info);
        AndroidBitmap_lockPixels(env, jbitmap, reinterpret_cast<void **>(&pixels));

        callback(pixels);

        AndroidBitmap_unlockPixels(env, jbitmap);
        env->ReleaseByteArrayElements(data, src_data, 0);
    } catch (...) {
        env->ReleaseByteArrayElements(data, src_data, 0);
        return NULL;
    }
    return jbitmap;
}

template<typename Func>
jbyteArray
createColorBytes(JNIEnv *env, jbyteArray data, jbyte *src_data,
                 int dataSize, Func callback) {

    if (src_data == NULL) {
        return nullptr;
    }
    uint8 *dst_data = new uint8[dataSize];
    int res = callback(dst_data);
    if (res != 0) {
        env->ReleaseByteArrayElements(data, src_data, 0);
        delete[] dst_data;
        return nullptr;
    }
    jbyteArray targetData = env->NewByteArray(dataSize);
    env->SetByteArrayRegion(targetData, 0, dataSize, reinterpret_cast<const jbyte *>(dst_data));

    env->ReleaseByteArrayElements(data, src_data, 0);
    delete[] dst_data;


    return targetData;
}





