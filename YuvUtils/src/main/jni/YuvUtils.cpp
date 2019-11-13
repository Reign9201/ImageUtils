//# pragma once


#include "YuvUtils.h"
#include <string.h>

static JNINativeMethod gMethods[] = {
        {"test",         "()I",                           (void *) test},
        {"bitmapToNV21", "(Landroid/graphics/Bitmap;)[B", (void *) bitmapToNV21}

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

    //delete[] dst_nv21;
    return res;
}


//void YuvUtils::nv21ToArgb(jbyte *nv21data, jint width, jint height, uint8 *argbData) {
//    //将NV21(YUV420SP) 拆分成Y 和 UV 两个分量
//    jint src_y_size = width * height;
//    jint src_u_size = (width >> 1) * (height >> 1);
//    jbyte *src_y_data = nv21data;
//    jbyte *src_uv_data = nv21data + src_y_size;
//
//    //uint8 *dst_argb_data = (uint8 *) malloc(sizeof(uint8) * width * height * 4);
//
//    logger::error("7777777777777777777777777");
//    NV21ToARGB((const uint8 *) src_y_data, width,
//               (const uint8 *) src_uv_data, (width + 1) / 2 * 2,
//               argbData, width * 4, width, height);
//    logger::error("66666666666666666666666666666666666666");
//}


