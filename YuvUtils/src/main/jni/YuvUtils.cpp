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

        // 将图像数据转换成Bitmap
        {"multiMixDataToBitmap", "([BIIIILandroid/graphics/Rect;IZ)Landroid/graphics/Bitmap;", (void *) multiMixDataToBitmap},

        {"dataMirror",           "([BIIIIZ)[B",                                                (void *) dataMirror},
        {"dataScale",            "([BII)Landroid/graphics/Bitmap;",                            (void *) dataScale},

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
        return yancy::NV21ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, nv21Data, src_data, width * height * 4, callback);

}

jbyteArray nv21ToRgb565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, nv21Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::NV21ToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, nv21Data, src_data, width * height * 2, callback);
}

jbyteArray nv21ToI420(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, nv21Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::NV21ToI420(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, nv21Data, src_data, width * height * 3 / 2, callback);
}

jobject nv21ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, nv21Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](unsigned char *pixel) -> int {
        return yancy::NV21ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };

    return createBitmap(env, nv21Data, src_data, width, height, callback);
}

jobject nv21ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray nv21Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, nv21Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](unsigned char *pixel) -> void {
        yancy::NV21ToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, nv21Data, src_data, width, height, callback, RGB_565);
}


jbyteArray i420ToNV21(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::I420ToNV21(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, i420Data, src_data, width * height * 3 / 2, callback);
}

jbyteArray i420ToRgba(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::I420ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, i420Data, src_data, width * height * 4, callback);
}

jbyteArray i420ToRgb(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::I420ToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, i420Data, src_data, width * height * 2, callback);
}

jobject
i420ToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](unsigned char *pixel) -> void {
        yancy::I420ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, i420Data, src_data, width, height, callback);
}

jobject
i420ToBitmap565(JNIEnv *env, jclass clazz, jbyteArray i420Data, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, i420Data,
                                          static_cast<int>(height * 3.0 / 2.0 * width));
    auto callback = [=](unsigned char *pixel) -> void {
        yancy::I420ToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, i420Data, src_data, width, height, callback, RGB_565);
}

jbyteArray rgbaToNV21(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbaData, width * height * 4);
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::RGBAToNV21(reinterpret_cast<uint8 *>(src_data), (width + 1) / 2 * 2, height,
                                 dst_data);
    };
    return createColorBytes(env, rgbaData, src_data,
                            width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2, callback);
}

jbyteArray rgbaToI420(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbaData, width * height * 4);
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::RGBAToI420(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, rgbaData, src_data, width * height * 3 / 2, callback);
}

jbyteArray rgbaToRgb(JNIEnv *env, jclass clazz, jbyteArray rgbaData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbaData, width * height * 4);
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::RGBAToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
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
        yancy::RGBAToRGB565(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
    };
    return createBitmap(env, rgbaData, src_data, width, height, callback, RGB_565);
}

jbyteArray rgbToNV21(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbData, width * height * 2);
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::RGB565ToNV21(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, rgbData, src_data, width * height * 3 / 2, callback);
}

jbyteArray rgbToI420(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    logger::error("len = ", env->GetArrayLength(rgbData));
    logger::error("size = ", width * height * 2);
    jbyte *src_data = checkDataAndConvert(env, rgbData, width * height * 2);
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::RGB565ToI420(reinterpret_cast<uint8 *>(src_data), (width + 1) / 2 * 2, height,
                                   dst_data);
    };
    return createColorBytes(env, rgbData, src_data,
                            width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2, callback);
}

jbyteArray rgbToRgba(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbData, width * height * 2);
    auto callback = [=](uint8 *dst_data) -> int {
        return yancy::RGB565ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, rgbData, src_data, width * height * 4, callback);
}

jobject
rgbToBitmap8888(JNIEnv *env, jclass clazz, jbyteArray rgbData, jint width, jint height) {
    jbyte *src_data = checkDataAndConvert(env, rgbData, width * height * 2);
    auto callback = [=](unsigned char *pixel) -> void {
        yancy::RGB565ToRGBA(reinterpret_cast<uint8 *>(src_data), width, height, pixel);
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
            return yancy::RGBAToNV21(pixel, (width + 1) / 2 * 2, height, *target_data);
        } else if (format == RGB_565) {
            return yancy::RGB565ToNV21(pixel, (width + 1) / 2 * 2, height, *target_data);
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
            return yancy::RGBAToRGB565(pixel, width, height, *target_data);
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
            return yancy::RGB565ToRGBA(pixel, width, height, *target_data);
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
            return yancy::RGBAToI420(pixel, (width + 1) / 2 * 2, height, *target_data);
        } else if (format == RGB_565) {
            return yancy::RGB565ToI420(pixel, (width + 1) / 2 * 2, height, *target_data);
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

    if (bitmapConfig != 3 && bitmapConfig != 5) {
        logger::error("This format operation is not supported yet!");
        return nullptr;
    }
    ConvertData convertData;
    int resCode = convertDataHandle(env, dataFormat, width, height, degree, rect, priorityClip, &convertData);
    if (resCode != 0) {
        return nullptr;
    }
    logger::error("convertData.targetHeight = ", convertData.targetHeight);
    logger::error("convertData.targetWidth = ", convertData.targetWidth);
    logger::error("convertData.crop_y = ", convertData.crop_y);
    logger::error("convertData.crop_y = ", convertData.crop_y);
    logger::error("convertData.format = ", convertData.format);
    logger::error("convertData.dataSize = ", convertData.dataSize);
    logger::error("convertData.rotateMode = ", convertData.rotateMode);


    jbyte *src_data = checkDataAndConvert(env, byteArray, convertData.dataSize);
    auto callback = [=](uint8 *pixels) {
        yancy::DataConvert(reinterpret_cast<unsigned char *>(src_data), width, height, convertData.dataSize,
                           pixels, convertData.targetWidth, convertData.targetHeight,
                           degree, convertData.format, bitmapConfig, convertData.rotateMode,
                           convertData.crop_x, convertData.crop_y);

    };

    return createBitmap(env, byteArray, src_data, convertData.targetWidth, convertData.targetHeight, callback,
                        bitmapConfig == 3 ? BitmapFormat::RGB_565 : BitmapFormat::ARGB_8888);
}

jbyteArray dataMirror(JNIEnv *env, jclass clazz, jbyteArray byteArray, jint width, jint height,
                      jint dataFormat, jint targetFormat, jboolean isVerticalMirror) {
    int dataSize, src_fourcc, dst_fourcc;
    switch (dataFormat) {
        case 1:
            dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            src_fourcc = libyuv::FOURCC_NV21;
            break;
        case 2:
            dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            src_fourcc = libyuv::FOURCC_I420;
            break;
        case 3:
            dataSize = width * height * 2;
            src_fourcc = libyuv::FOURCC_RGBP;
            break;
        case 5:
            dataSize = width * height * 4;
            src_fourcc = libyuv::FOURCC_ABGR;
            break;
        default:
            logger::error("This format operation is not supported yet!");
            return nullptr;
    }
    jbyte *src_data = checkDataAndConvert(env, byteArray, dataSize);
    if (src_data == nullptr) { return nullptr; }

    int dst_data_size;
    switch (targetFormat) {
        case 1:
            dst_data_size = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            dst_fourcc = libyuv::FOURCC_NV21;
            break;
        case 2:
            dst_data_size = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            dst_fourcc = libyuv::FOURCC_I420;
            break;
        case 3:
            dst_data_size = width * height * 2;
            dst_fourcc = libyuv::FOURCC_RGBP;
            break;
        case 5:
            dst_data_size = width * height * 4;
            dst_fourcc = libyuv::FOURCC_ABGR;
            break;
        default:
            logger::error("Does not support generating data in this format.");
            return nullptr;
    }
    uint8 *dst_data = new uint8[dst_data_size];

    if (yancy::DataMirror(reinterpret_cast<const uint8 *>(src_data), width, height, &dst_data,
                          src_fourcc, dst_fourcc,
                          isVerticalMirror) != 0) {
        env->ReleaseByteArrayElements(byteArray, src_data, 0);
        delete[] dst_data;
        return nullptr;
    }
    jbyteArray dstByteArray = env->NewByteArray(dst_data_size);
    env->SetByteArrayRegion(dstByteArray, 0, dst_data_size,
                            reinterpret_cast<const jbyte *>(dst_data));
    env->ReleaseByteArrayElements(byteArray, src_data, 0);
    delete[] dst_data;

    return dstByteArray;
}

int convertDataHandle(JNIEnv *env, jint dataFormat,
                      jint width, jint height, jint degree, jobject rect,
                      jboolean priorityClip, ConvertData *convertData) {

    switch (degree) {
        case 0:
            convertData->rotateMode = libyuv::kRotate0;
            break;
        case 90:
            convertData->rotateMode = libyuv::kRotate90;
            break;
        case 180:
            convertData->rotateMode = libyuv::kRotate180;
            break;
        case -90:
        case 270:
            convertData->rotateMode = libyuv::kRotate270;
            break;
        default:
            logger::error("degree value error, please check it.");
            return -1;
    }
    switch (dataFormat) {
        case 1:
            convertData->format = libyuv::FOURCC_NV21;
            convertData->dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            break;
        case 2:
            convertData->format = libyuv::FOURCC_I420;
            convertData->dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            break;
        case 3:
            convertData->format = libyuv::FOURCC_RGBP;
            convertData->dataSize = width * height * 2;
            break;
        case 5:
            convertData->format = libyuv::FOURCC_ABGR;
            convertData->dataSize = width * height * 4;
            break;
        default:
            logger::error("dataFormat value error, please check it.");
            return -1;
    }

    convertData->targetWidth = width;
    convertData->targetHeight = height;
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
        convertData->crop_x = left;
        convertData->crop_y = top;
        if (priorityClip) {
            if ((degree == 90 || degree == -90 || degree == 270)) {
                convertData->targetWidth = bottom - top;
                convertData->targetHeight = right - left;
            } else {
                convertData->targetWidth = right - left;
                convertData->targetHeight = bottom - top;
            }
        } else {
            convertData->targetWidth = right - left;
            convertData->targetHeight = bottom - top;
            if (degree == 90) {
                convertData->crop_x = top;
                convertData->crop_y = height - right;
                if (right > convertData->targetHeight || bottom > convertData->targetWidth
                    || convertData->crop_x > convertData->targetWidth || convertData->crop_y > convertData->targetHeight) {
                    logger::error(
                            "rect width or height more than rotated image width or height, please check it.");
                    return -1;
                }
            } else if (degree == 180) {
                convertData->crop_x = width - right;
                convertData->crop_y = height - bottom;
            } else if (degree == -90 || degree == 270) {
                convertData->crop_x = width - bottom;
                convertData->crop_y = left;
                if (right > convertData->targetHeight || bottom > convertData->targetWidth
                    || convertData->crop_x > convertData->targetWidth || convertData->crop_y > convertData->targetHeight) {
                    logger::error(
                            "rect width or height more than rotated image width or height, please check it.");
                    return -1;
                }
            }

        }

    } else if (degree == 90 || degree == -90 || degree == 270) {
        convertData->targetWidth = height;
        convertData->targetHeight = width;
    }
    return 0;
}

jbyteArray
dataScale(JNIEnv *env, jclass clazz, jbyteArray byteArray, jint width, jint height, jint dstWidth, jint dstHeight, jint dataFormat,
          jint targetFormat, jint filterMode) {

    jbyte *src_data = nullptr;
    if (dataFormat == 1 || dataFormat == 2) {
        src_data = checkDataAndConvert(env, byteArray, width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2);
    } else if (dataFormat == 3) {
        src_data = checkDataAndConvert(env, byteArray, width * height * 2);
    } else if (dataFormat == 5) {
        src_data = checkDataAndConvert(env, byteArray, width * height * 4);
    }
    if (src_data == nullptr) {
        return nullptr;
    }

    int dst_data_size = 0;

    if (targetFormat == 1 || targetFormat == 2) {
        dst_data_size = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
    } else if (targetFormat == 3) {
        dst_data_size = width * height * 2;
    } else if (targetFormat == 5) {
        dst_data_size = width * height * 4;
    }
    if (dst_data_size == 0) {
        return nullptr;
    }
    uint8 *dst_data = new uint8[dst_data_size];
    int resCode = yancy::DataScale(reinterpret_cast<const uint8 *>(src_data), width, height,
                                   &dst_data, dstWidth, dstHeight,
                                   dataFormat, targetFormat,
                                   yancy::getFilterMode(filterMode));

    if (resCode != 0) {
        delete[] dst_data;
        env->ReleaseByteArrayElements(byteArray, src_data, 0);
        return nullptr;
    }
    jbyteArray dstByteArray = env->NewByteArray(dst_data_size);
    env->SetByteArrayRegion(dstByteArray, 0, dst_data_size, reinterpret_cast<const jbyte *>(dst_data));
    delete[] dst_data;
    env->ReleaseByteArrayElements(byteArray, src_data, 0);
    return dstByteArray;
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





