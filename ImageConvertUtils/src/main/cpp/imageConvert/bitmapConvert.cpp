#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "image.h"

#define LOG_TAG "bitmapConvert"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

typedef struct bitmapFormat_t {
    unsigned char *pBuffer;
    int width;
    int height;
    int format;
}IMAGE_HANDLE, *LPIMAGE_HANDLE;

static jint initial(JNIEnv *env, jobject object, jint width, jint height, jint format);
static jint bitmapConvert(JNIEnv *env, jobject obj, jint handle, jobject jbitmap, jbyteArray data);
static jint unInitial(JNIEnv *env, jobject object, jint handle);


static JNINativeMethod gMethods[] = {
        {"bitmapInit", "(III)I",(void*)initial},
        {"bitmapConvert", "(ILandroid/graphics/Bitmap;[B)I",(void*)bitmapConvert},
        {"bitmapUnInit", "(I)I",(void*)unInitial},
};

const char* JNI_NATIVE_INTERFACE_CLASS = "com/yancy/imageconvert/BitmapConvert";

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved){

    JNIEnv *env = NULL;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4)){
        return JNI_ERR;
    }

    jclass cls = env->FindClass(JNI_NATIVE_INTERFACE_CLASS);
    if (cls == NULL){
        return JNI_ERR;
    }

    jint nRes = env->RegisterNatives(cls, gMethods, sizeof(gMethods)/sizeof(gMethods[0]));
    if (nRes < 0){
        return JNI_ERR;
    }

    LOGI("bitmapConvert.so JNI_OnLoad");

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved){

    JNIEnv *env = NULL;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4)){
        return;
    }

    jclass cls = env->FindClass(JNI_NATIVE_INTERFACE_CLASS);
    if (cls == NULL){
        return;
    }

    LOGI("bitmapConvert.so JNI_OnUnload");
    env->UnregisterNatives(cls);
}

jint unInitial(JNIEnv *env, jobject object, jint handle)
{
    LPIMAGE_HANDLE engine = (LPIMAGE_HANDLE)handle;
    if (engine->pBuffer != NULL) {
        free(engine->pBuffer);
    }

    free(engine);
    return 0;
}

jint initial(JNIEnv *env, jobject object, jint width, jint height, jint format)
{
    LPIMAGE_HANDLE handle = (LPIMAGE_HANDLE)malloc(sizeof(IMAGE_HANDLE));
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
                env->ThrowNew(env->FindClass("java/lang/Exception"), "FORMAT NOT SUPPORT THIS SIZE");
                return (jint)-1;
            }
            handle->pBuffer = (unsigned char *) malloc(static_cast<size_t>(width * height * 3 / 2));
            break;
        case CP_RGBA8888:
        case CP_RGB565:
        case CP_RGBA4444:
        case CP_ALPHA8:
        default :
            env->ThrowNew(env->FindClass("java/lang/Exception"), "FORMAT ERROR!");
            return (jint)-1;
    }

    return (jint)handle;
}

jint bitmapConvert(JNIEnv *env, jobject obj, jint handle, jobject jbitmap, jbyteArray data)
{
    int ret = 0;
    LPIMAGE_HANDLE engine = (LPIMAGE_HANDLE)handle;
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, jbitmap, &info) < 0) {
        return -1;
    }

    if (info.width != engine->width || info.height != engine->height || data == NULL) {
        LOGE("PARAM FAIL!");
        return -1;
    }
    int size = calcImageSize(info.width, info.height, engine->format);
    if (env->GetArrayLength(data) < size) {
        LOGE("DATA BUFFER NOT NOT ENOUGH!");
        return -1;
    }

    unsigned char* RGBAbase;
    AndroidBitmap_lockPixels(env, jbitmap, (void**) &RGBAbase);

    //convert
    if (info.format == CP_RGBA8888 && engine->format == CP_PAF_NV12) {
        convert_8888_NV12(RGBAbase, engine->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGBA8888 && engine->format == CP_PAF_NV21) {
        convert_8888_NV21(RGBAbase, engine->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGBA8888 && engine->format == CP_PAF_BGR24) {
        convert_8888_BGR888(RGBAbase, engine->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGB565 && engine->format == CP_PAF_NV12) {
        convert_565_NV12(RGBAbase, engine->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGB565 && engine->format == CP_PAF_NV21) {
        convert_565_NV21(RGBAbase, engine->pBuffer, info.width, info.height);
    } else if (info.format == CP_RGB565 && engine->format == CP_PAF_BGR24) {
        convert_565_BGR888(RGBAbase, engine->pBuffer, info.width, info.height);
    } else {
        LOGI("format = %d\n", info.format);
        ret = -1;
    }

    env->SetByteArrayRegion(data, 0, size, (const jbyte*) engine->pBuffer);

    AndroidBitmap_unlockPixels(env, jbitmap);

    return ret;
}