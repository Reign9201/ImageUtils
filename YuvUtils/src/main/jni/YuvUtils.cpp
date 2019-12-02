//# pragma once


#include "YuvUtils.h"
#include "head/cppToJavaHelper.hpp"
#include <string.h>
#include <libyuv.h>
#include <libyuv/rotate.h>

static JNINativeMethod gMethods[] = {
        // NV21 转换成其他格式
        {"nv21ToRgba",           "([BII)[B",                                                   (void *) nv21ToRgba},
        {"nv21ToRgb",            "([BII)[B",                                                   (void *) nv21ToRgb565},
        {"nv21ToI420",           "([BII)[B",                                                   (void *) nv21ToI420},
        {"nv21ToBitmap8888",     "([BII)Landroid/graphics/Bitmap;",                            (void *) nv21ToBitmap8888},
        {"nv21ToBitmap565",      "([BII)Landroid/graphics/Bitmap;",                            (void *) nv21ToBitmap565},

        // I420 转换成其他格式
        {"i420ToNV21",           "([BII)[B",                                                   (void *) i420ToNV21},
        {"i420ToRgba",           "([BII)[B",                                                   (void *) i420ToRgba},
        {"i420ToRgb",            "([BII)[B",                                                   (void *) i420ToRgb},
        {"i420ToBitmap8888",     "([BII)Landroid/graphics/Bitmap;",                            (void *) i420ToBitmap8888},
        {"i420ToBitmap565",      "([BII)Landroid/graphics/Bitmap;",                            (void *) i420ToBitmap565},

        // RGBA 转换成其他格式
        {"rgbaToNV21",           "([BII)[B",                                                   (void *) rgbaToNV21},
        {"rgbaToI420",           "([BII)[B",                                                   (void *) rgbaToI420},
        {"rgbaToRgb",            "([BII)[B",                                                   (void *) rgbaToRgb},
        {"rgbaToBitmap8888",     "([BII)Landroid/graphics/Bitmap;",                            (void *) rgbaToBitmap8888},
        {"rgbaToBitmap565",      "([BII)Landroid/graphics/Bitmap;",                            (void *) rgbaToBitmap565},

        // RGB 转换成其他格式
        {"rgbToNV21",            "([BII)[B",                                                   (void *) rgbToNV21},
        {"rgbToI420",            "([BII)[B",                                                   (void *) rgbToI420},
        {"rgbToRgba",            "([BII)[B",                                                   (void *) rgbToRgba},
        {"rgbToBitmap8888",      "([BII)Landroid/graphics/Bitmap;",                            (void *) rgbToBitmap8888},
        {"rgbToBitmap565",       "([BII)Landroid/graphics/Bitmap;",                            (void *) rgbToBitmap565},

        // Bitmap 转换成其他格式
        {"bitmapToNV21",         "(Landroid/graphics/Bitmap;)[B",                              (void *) bitmapToNV21},
        {"bitmapToRgb",          "(Landroid/graphics/Bitmap;)[B",                              (void *) bitmapToRgb},
        {"bitmapToRgba",         "(Landroid/graphics/Bitmap;)[B",                              (void *) bitmapToRgba},
        {"bitmap2Rgba",          "(Landroid/graphics/Bitmap;)[I",                              (void *) bitmap2Rgba},
        {"bitmapToI420",         "(Landroid/graphics/Bitmap;)[B",                              (void *) bitmapToI420},

        {"intToByte",            "([I)[B",                                                     (void *) intToByte},
        {"byteToInt",            "([B)[I",                                                     (void *) byteToInt},

        {"multiMixDataToBitmap", "([BIIIILandroid/graphics/Rect;IZ)Landroid/graphics/Bitmap;", (void *) multiMixDataToBitmap},

};

const char *JNI_NATIVE_INTERFACE_CLASS = "com/yancy/yuvutils/YuvUtils";


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
    jbyte *src_data = checkDataAndConvert(env, nv21Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return NV21ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, nv21Data, src_data, width * height * 4, callback);

}

jbyteArray nv21ToRgb565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, nv21Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return NV21ToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, nv21Data, src_data, width * height * 2, callback);
}

jbyteArray nv21ToI420(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, nv21Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return NV21ToI420(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, nv21Data, src_data, width * height * 3 / 2, callback);
}

jobject nv21ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, nv21Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](unsigned char *pixel) -> int {
        return NV21ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };

    return createBitmap(env, nv21Data, src_data, width, height, callback);
}

jobject nv21ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, nv21Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](unsigned char *pixel) -> void {
        NV21ToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, nv21Data, src_data, width, height, callback, RGB_565);
}


jbyteArray i420ToNV21(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return I420ToNV21(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, i420Data, src_data, width * height * 3 / 2, callback);
}

jbyteArray i420ToRgba(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return I420ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, i420Data, src_data, width * height * 4, callback);
}

jbyteArray i420ToRgb(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return I420ToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, i420Data, src_data, width * height * 2, callback);
}

jobject
i420ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](unsigned char *pixel) -> void {
        I420ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, i420Data, src_data, width, height, callback);
}

jobject
i420ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](unsigned char *pixel) -> void {
        I420ToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, i420Data, src_data, width, height, callback, RGB_565);
}

jbyteArray rgbaToNV21(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbaData, width * height * 4);
    auto callback = [=](uint8 *dst_data) -> int {
        return RGBAToNV21(reinterpret_cast<uint8 *>(src_data), (width + 1) / 2 * 2, height,
                          dst_data);
    };
    return createColorBytes(env, rgbaData, src_data,
                            width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2, callback);
}

jbyteArray rgbaToI420(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbaData, width * height * 4);
    auto callback = [=](uint8 *dst_data) -> int {
        return RGBAToI420(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, rgbaData, src_data, width * height * 3 / 2, callback);
}

jbyteArray rgbaToRgb(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbaData, width * height * 4);
    auto callback = [=](uint8 *dst_data) -> int {
        return RGBAToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, rgbaData, src_data, width * height * 2, callback);
}

jobject
rgbaToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbaData, width * height * 4);
    auto callback = [=](unsigned char *pixel) -> void {
        memcpy(pixel, reinterpret_cast<unsigned char *>(src_data),
               sizeof(unsigned char) * (width * height * 4));
    };
    return createBitmap(env, rgbaData, src_data, width, height, callback);
}

jobject
rgbaToBitmap565(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbaData, width * height * 4);
    auto callback = [=](unsigned char *pixel) -> void {
        RGBAToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, rgbaData, src_data, width, height, callback, RGB_565);
}

jbyteArray rgbToNV21(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbData, width * height * 2);
    auto callback = [=](uint8 *dst_data) -> int {
        return RGB565ToNV21(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, rgbData, src_data, width * height * 3 / 2, callback);
}

jbyteArray rgbToI420(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    logger::error("len = ", env->GetArrayLength(rgbData));
    logger::error("size = ", width * height * 2);
    jbyte *src_data = checkDataAndConvert(env, rgbData, width * height * 2);
    auto callback = [=](uint8 *dst_data) -> int {
        return RGB565ToI420(reinterpret_cast<uint8 *>(src_data), (width + 1) / 2 * 2, height,
                            dst_data);
    };
    return createColorBytes(env, rgbData, src_data,
                            width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2, callback);
}

jbyteArray rgbToRgba(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbData, width * height * 2);
    auto callback = [=](uint8 *dst_data) -> int {
        return RGB565ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, rgbData, src_data, width * height * 4, callback);
}

jobject
rgbToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbData, width * height * 2);
    auto callback = [=](unsigned char *pixel) -> void {
        RGB565ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, rgbData, src_data, width, height, callback);
}

jobject
rgbToBitmap565(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbData, width * height * 2);
    auto callback = [=](unsigned char *pixel) -> void {
        memcpy(pixel, reinterpret_cast<unsigned char *>(src_data),
               sizeof(unsigned char) * (width * height * 2));
    };
    return createBitmap(env, rgbData, src_data, width, height, callback, RGB_565);
}

jbyteArray bitmapToNV21(JNIEnv *env, jclass clazz, jobject jbitmap) {

    auto callback = [](uint8 **target_data, int width, int height, int *dataSize, uint8 *pixel,
                       BitmapFormat format) -> int {
        *dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
        *target_data = new uint8[*dataSize];
        if (format == ARGB_8888) {
            return RGBAToNV21(pixel, (width + 1) / 2 * 2, height, *target_data);
        } else if (format == RGB_565) {
            return RGB565ToNV21(pixel, (width + 1) / 2 * 2, height, *target_data);
        } else {
            return -1;
        }
    };
    return bitmapToByteArray(env, jbitmap, callback);
}

jbyteArray bitmapToRgb(JNIEnv *env, jclass clazz, jobject jbitmap) {

    auto callback = [](uint8 **target_data, int width, int height, int *dataSize, uint8 *pixel,
                       BitmapFormat format) -> int {
        *dataSize = width * height * 2;
        *target_data = new uint8[*dataSize];
        if (format == ARGB_8888) {
            return RGBAToRGB565(pixel, width, height, *target_data);
        } else if (format == RGB_565) {
            memcpy(*target_data, pixel, sizeof(uint8) * width * height * 2);
            return 0;
        } else {
            return -1;
        }
    };
    return bitmapToByteArray(env, jbitmap, callback);
}

jbyteArray bitmapToRgba(JNIEnv *env, jclass clazz, jobject jbitmap) {
    if (jbitmap == NULL) {
        return NULL;
    }

    auto callback = [](uint8 **target_data, int width, int height, int *dataSize, uint8 *pixel,
                       BitmapFormat format) -> int {
        *dataSize = width * height * 4;
        *target_data = new uint8[*dataSize];
        if (format == ARGB_8888) {
            memcpy(*target_data, pixel, sizeof(uint8) * width * height * 4);
            return 0;
        } else if (format == RGB_565) {
            return RGB565ToRGBA(pixel, width, height, *target_data);
        } else {
            return -1;
        }
    };

    return bitmapToByteArray(env, jbitmap, callback);
}

jintArray bitmap2Rgba(JNIEnv *env, jclass clazz, jobject jbitmap) {
    if (jbitmap == NULL) {
        return NULL;
    }
    AndroidBitmapInfo info;
    uint8 *pixels;
    AndroidBitmap_getInfo(env, jbitmap, &info);
    AndroidBitmap_lockPixels(env, jbitmap, reinterpret_cast<void **>(&pixels));


    int dataSize = info.width * info.height;
    libyuv::ARGBToABGR(pixels, info.stride, pixels, info.stride, info.width, info.height);
    jintArray intRgba = env->NewIntArray(dataSize);
    env->SetIntArrayRegion(intRgba, 0, dataSize, reinterpret_cast<const jint *>(pixels));
    AndroidBitmap_unlockPixels(env, jbitmap);

    return intRgba;
}


jbyteArray bitmapToI420(JNIEnv *env, jclass clazz, jobject jbitmap) {

    auto callback = [](uint8 **target_data, int width, int height, int *dataSize, uint8 *pixel,
                       BitmapFormat format) -> int {
        *dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
        *target_data = new uint8[*dataSize];
        if (format == ARGB_8888) {
            return RGBAToI420(pixel, (width + 1) / 2 * 2, height, *target_data);
        } else if (format == RGB_565) {
            return RGB565ToI420(pixel, (width + 1) / 2 * 2, height, *target_data);
        } else {
            return -1;
        }
    };
    return bitmapToByteArray(env, jbitmap, callback);
}

jbyte *checkDataAndConvert(JNIEnv *env, jbyteArray yuv420Data, int dataSize) {
    if (dataSize != env->GetArrayLength(yuv420Data)) {
        logger::error("original data error, please check it.");
        return NULL;
    }
    return env->GetByteArrayElements(yuv420Data, JNI_FALSE);
}

jbyteArray intToByte(JNIEnv *env, jclass clazz, jintArray intArray) {
    jint *srcData = env->GetIntArrayElements(intArray, JNI_FALSE);
    int dataSize = env->GetArrayLength(intArray) * 4;
    jbyteArray dstData = env->NewByteArray(dataSize);
    env->SetByteArrayRegion(dstData, 0, dataSize, reinterpret_cast<const jbyte *>(srcData));
    return dstData;
}

jintArray byteToInt(JNIEnv *env, jclass clazz, jbyteArray byteArray) {
    jbyte *srcData = env->GetByteArrayElements(byteArray, JNI_FALSE);
    int dataSize = env->GetArrayLength(byteArray) / 4;
    jintArray dstData = env->NewIntArray(dataSize);
    env->SetIntArrayRegion(dstData, 0, dataSize, reinterpret_cast<const jint *>(srcData));
    return dstData;
}

jobject
multiMixDataToBitmap(JNIEnv *env, jclass clazz, jbyteArray byteArray, jint dataFormat, jint width,
                     jint height, jint degree, jobject rect, jint bitmapConfig,
                     jboolean priorityClip) {

    int dataSize;
    uint32 format;
    libyuv::RotationMode mode;
    switch (degree) {
        case 0:
            mode = libyuv::kRotate0;
            break;
        case 90:
            mode = libyuv::kRotate90;
            break;
        case 180:
            mode = libyuv::kRotate180;
            break;
        case -90:
        case 270:
            mode = libyuv::kRotate270;
            break;
        default:
            logger::error("degree value error, please check it.");
            return nullptr;
    }
    switch (dataFormat) {
        case 1:
            format = libyuv::FOURCC_NV21;
            dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            break;
        case 2:
            format = libyuv::FOURCC_I420;
            dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            break;
        case 3:
            format = libyuv::FOURCC_RGBP; //todo 带确认
            dataSize = width * height * 2;
            break;
        case 5:
            format = libyuv::FOURCC_ABGR;
            dataSize = width * height * 4;
            break;
        default:
            logger::error("dataFormat value error, please check it.");
            return nullptr;
    }
    logger::error("size = ", dataSize);
    jbyte *src_data = checkDataAndConvert(env, byteArray, dataSize);

    int bmpWidth = width;
    int bmpHeight = height;
    int crop_x = 0, crop_y = 0;
    if (rect != nullptr) {
        jclass rectClazz = env->GetObjectClass(rect);
        jfieldID rect_left = env->GetFieldID(rectClazz, "left", "I");
        jfieldID rect_top = env->GetFieldID(rectClazz, "top", "I");
        jfieldID rect_right = env->GetFieldID(rectClazz, "right", "I");
        jfieldID rect_bottom = env->GetFieldID(rectClazz, "bottom", "I");

        int left, top, right, bottom;
        left = env->GetIntField(rect, rect_left);
        top = env->GetIntField(rect, rect_top);
        right = env->GetIntField(rect, rect_right);
        bottom = env->GetIntField(rect, rect_bottom);
        crop_x = left;
        crop_y = top;
        if (priorityClip) {
            if ((degree == 90 || degree == -90 || degree == 270)) {
                bmpWidth = bottom - top;
                bmpHeight = right - left;
            } else {
                bmpWidth = right - left;
                bmpHeight = bottom - top;
            }
        } else {
            bmpWidth = right - left;
            bmpHeight = bottom - top;
            if (degree == 90) {
                crop_x = top;
                crop_y = height - right;
                if (right > bmpHeight || bottom > bmpWidth
                    || crop_x > bmpWidth || crop_y > bmpHeight) {
                    logger::error("rect width or height more than rotated image width or height, please check it.");
                    return nullptr;
                }
            } else if (degree == 180) {
                crop_x = width - right;
                crop_y = height - bottom;
            } else if (degree == -90 || degree == 270) {
                crop_x = width - bottom;
                crop_y = left;
                if (right > bmpHeight || bottom > bmpWidth
                    || crop_x > bmpWidth || crop_y > bmpHeight) {
                    logger::error("rect width or height more than rotated image width or height, please check it.");
                    return nullptr;
                }
            }

        }

    } else if (degree == 90 || degree == -90 || degree == 270) {
        bmpWidth = height;
        bmpHeight = width;
    }

    auto callback = [=](uint8 *pixels) {
        uint8 *i420_data = new uint8[bmpWidth * bmpHeight + ((bmpWidth + 1) / 2) * ((bmpHeight + 1) / 2) * 2];
        libyuv::ConvertToI420(reinterpret_cast<unsigned char *>(src_data),
                              static_cast<size_t>(dataSize),
                              i420_data, bmpWidth,
                              i420_data + bmpWidth * bmpHeight, bmpWidth >> 1,
                              i420_data + bmpWidth * bmpHeight + (bmpWidth >> 1) * (bmpHeight >> 1),
                              bmpWidth >> 1,
                              crop_x, crop_y,
                              width, height,
                              degree % 180 == 0 ? bmpWidth : bmpHeight,
                              degree % 180 == 0 ? bmpHeight : bmpWidth,
                              mode, format
        );

        if (bitmapConfig == 3) {
            I420ToRGB565(i420_data, bmpWidth, bmpHeight, pixels);
        } else {
            I420ToRGBA(i420_data, bmpWidth, bmpHeight, pixels);
        }
    };


    return createBitmap(env, byteArray, src_data, bmpWidth, bmpHeight, callback,
                        bitmapConfig == 3 ? RGB_565 : ARGB_8888);
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
    uint8 *pixels = 0;
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


// TODO: 尝试用template inline 解决
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

template<typename Func>
jbyteArray bitmapToByteArray(JNIEnv *env, jobject jbitmap, Func callback) {
    if (jbitmap == NULL) {
        return NULL;
    }
    AndroidBitmapInfo info;
    uint8 *pixels;
    AndroidBitmap_getInfo(env, jbitmap, &info);
    AndroidBitmap_lockPixels(env, jbitmap, reinterpret_cast<void **>(&pixels));

    uint8 *target_data = NULL;
    int dataSize = 0;
    int code = -1;
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        code = callback(&target_data, info.width, info.height, &dataSize, pixels, ARGB_8888);
    } else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        code = callback(&target_data, info.width, info.height, &dataSize, pixels, RGB_565);
    }

    if (code != 0) {
        AndroidBitmap_unlockPixels(env, jbitmap);
        if (target_data != NULL) {
            delete[] target_data;
        }
        return NULL;
    }

    logger::debug("dataSize = ", dataSize);
    jbyteArray res = env->NewByteArray(dataSize);
    env->SetByteArrayRegion(res, 0, dataSize, reinterpret_cast<const jbyte *>(target_data));
    AndroidBitmap_unlockPixels(env, jbitmap);

    if (target_data != NULL) {
        delete[] target_data;
    }

    return res;
}





