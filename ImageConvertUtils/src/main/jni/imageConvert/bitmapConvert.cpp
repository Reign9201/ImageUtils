#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "image.h"
#include "../libyuv/YuvUtils.h"
#include "logger.hpp"

#define LOG_TAG "bitmapConvert"


typedef struct bitmapFormat_t {
    unsigned char *pBuffer;
    int width;
    int height;
    int format;
} IMAGE_HANDLE, *LPIMAGE_HANDLE;

static jint initial(JNIEnv *env, jobject object, jint width, jint height, jint format);

static jint bitmapConvert(JNIEnv *env, jobject obj, jobject jbitmap, jbyteArray data);

static jint unInitial(JNIEnv *env, jobject object);

static jobject nv21ToARGB(JNIEnv *env, jobject obj, jbyte *nv21data, jint width, jint height);


static JNINativeMethod gMethods[] = {
        {"bitmapInit",    "(III)I",                          (void *) initial},
        {"bitmapConvert", "(Landroid/graphics/Bitmap;[B)I",  (void *) bitmapConvert},
        {"bitmapUnInit",  "()I",                             (void *) unInitial},
        {"nv21ToARGB",    "([BII)Landroid/graphics/Bitmap;", (void *) nv21ToARGB},
};

const char *JNI_NATIVE_INTERFACE_CLASS = "com/yancy/imageconvertutils/BitmapConvert";

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {

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

    LOGI("bitmapConvert.so JNI_OnLoad");

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

    LOGI("bitmapConvert.so JNI_OnUnload");
    env->UnregisterNatives(cls);
}

LPIMAGE_HANDLE handle;

jint unInitial(JNIEnv *env, jobject object) {
    if (handle == NULL) { return 0; }

    if (handle->pBuffer != NULL) {
        free(handle->pBuffer);
    }

    free(handle);
    return 0;
}

jint initial(JNIEnv *env, jobject object, jint width, jint height, jint format) {
    handle = (LPIMAGE_HANDLE) malloc(sizeof(IMAGE_HANDLE));
    handle->width = width;
    handle->height = height;
    handle->format = format;

    switch (format) {
        case CP_PAF_BGR24:
            handle->pBuffer = (unsigned char *) malloc(static_cast<size_t>(width * height * 3));
            break;
        case CP_PAF_I420:
        case CP_PAF_NV12:
        case CP_PAF_NV21:
            if ((width & 1) && (height & 1)) {
                env->ThrowNew(env->FindClass("java/lang/Exception"),
                              "FORMAT NOT SUPPORT THIS SIZE");
                return (jint) -1;
            }
            handle->pBuffer = (unsigned char *) malloc(static_cast<size_t>(width * height * 3 / 2));
            break;
        case CP_RGBA8888:
        case CP_RGB565:
        case CP_RGBA4444:
        case CP_ALPHA8:
        default :
            env->ThrowNew(env->FindClass("java/lang/Exception"), "FORMAT ERROR!");
            return (jint) -1;
    }

    return 0;
}

jint bitmapConvert(JNIEnv *env, jobject obj, jobject jbitmap, jbyteArray data) {
    int ret = 0;
    //LPIMAGE_HANDLE engine = (LPIMAGE_HANDLE) handle;
    if (handle == nullptr) { return -1; }
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, jbitmap, &info) < 0) {
        return -1;
    }

    if (info.width != handle->width || info.height != handle->height || data == NULL) {
        LOGE("PARAM FAIL!");
        return -1;
    }
    int size = calcImageSize(info.width, info.height, handle->format);
    if (env->GetArrayLength(data) < size) {
        LOGE("DATA BUFFER NOT NOT ENOUGH!");
        return -1;
    }

    unsigned char *RGBAbase;
    AndroidBitmap_lockPixels(env, jbitmap, (void **) &RGBAbase);

    //convert
    if (info.format == CP_RGBA8888 && handle->format == CP_PAF_NV12) {
        convert_8888_NV12(RGBAbase, handle->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGBA8888 && handle->format == CP_PAF_NV21) {
        convert_8888_NV21(RGBAbase, handle->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGBA8888 && handle->format == CP_PAF_BGR24) {
        convert_8888_BGR888(RGBAbase, handle->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGB565 && handle->format == CP_PAF_NV12) {
        convert_565_NV12(RGBAbase, handle->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGB565 && handle->format == CP_PAF_NV21) {
        convert_565_NV21(RGBAbase, handle->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGB565 && handle->format == CP_PAF_BGR24) {
        convert_565_BGR888(RGBAbase, handle->pBuffer, info.width, info.height);
    } else {
        LOGI("format = %d\n", info.format);
        ret = -1;
    }

    env->SetByteArrayRegion(data, 0, size, (const jbyte *) handle->pBuffer);

    AndroidBitmap_unlockPixels(env, jbitmap);

    return ret;
}


jobject nv21ToARGB(JNIEnv *env, jobject obj, jbyte *nv21data, jint width, jint height) {
    YuvUtils yuvUtils;
//    uint8 *dst_argb_data = (uint8 *) malloc(sizeof(uint8) * width * height * 4);
    uint8 *dst_argb_data = new uint8[sizeof(uint8) * width * height * 4];
    logger::error("------------------------------------------");
    yuvUtils.nv21ToArgb(nv21data, width, height, dst_argb_data);
    logger::error("============================================");

    jclass clazz = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmap = env->GetStaticMethodID(clazz, "createBitmap",
                                                    "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jclass cls = env->FindClass("android/graphics/Bitmap$Config");
    jfieldID fid = env->GetStaticFieldID(cls, "ARGB_8888", "Landroid/graphics/Bitmap$Config;");
    jobject config = env->GetStaticObjectField(cls, fid);
    jobject jbitmap = env->CallStaticObjectMethod(clazz, createBitmap, width, height, config);

    logger::error("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk");

    AndroidBitmapInfo info;
    void *pixels = 0;
    AndroidBitmap_getInfo(env, jbitmap, &info);
    AndroidBitmap_lockPixels(env, jbitmap, &pixels);

    memcpy(pixels, dst_argb_data, sizeof(uint8) * width * height * 4);

    logger::error("99999999999999999999999999999999");
    AndroidBitmap_unlockPixels(env, jbitmap);

    //free(dst_argb_data);
    return jbitmap;

}