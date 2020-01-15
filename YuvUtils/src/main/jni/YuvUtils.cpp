
#include "YuvUtils.h"
#include "head/cppToJavaHelper.hpp"
#include <string.h>

static JNINativeMethod gMethods[] = {
        // Bitmap 转换成其他格式
        {"bitmapToNV21",           "(Landroid/graphics/Bitmap;)[B",                              (void *) bitmapToNV21},
        {"bitmapToRgb565",         "(Landroid/graphics/Bitmap;)[B",                              (void *) bitmapToRgb565},
        {"bitmapToRgb24",          "(Landroid/graphics/Bitmap;)[B",                              (void *) bitmapToRgb24},
        {"bitmapToRgba",           "(Landroid/graphics/Bitmap;)[B",                              (void *) bitmapToRgba},
        {"bitmapToI420",           "(Landroid/graphics/Bitmap;)[B",                              (void *) bitmapToI420},

        // 图像格式互相转换
        {"imageFormatConvert",     "([BIIII)[B",                                                 (void *) imageFormatConvert},

        // 各种格式图像转换成Bitmap
        {"imageToBitmap",          "([BIIII)Landroid/graphics/Bitmap;",                          (void *) imageToBitmap},

        // 图像裁剪旋转
        {"dataClipRotate",         "([BIIIILandroid/graphics/Rect;IZ)[B",                        (void *) dataClipRotate},
        {"dataClipRotateToBitmap", "([BIIIILandroid/graphics/Rect;IZ)Landroid/graphics/Bitmap;", (void *) dataClipRotateToBitmap},

        // 图像镜像操作
        {"dataMirror",             "([BIIIIZ)[B",                                                (void *) dataMirror},

        // 图像缩放操作
        {"dataScale",              "([BIIIIIII)[B",                                              (void *) dataScale},

        // int数组类型数据与byte数组类型数据互转
        {"intArrayToByteArray",    "([I)[B",                                                     (void *) intArrayToByteArray},
        {"byteArrayToIntArray",    "([B)[I",                                                     (void *) byteArrayToIntArray}

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

jbyteArray
imageFormatConvert(JNIEnv *env, jclass clazz, jbyteArray src_data, jint width, jint height, jint dataFormat, jint targetFormat) {
    switch (dataFormat) {
        case 1:
            switch (targetFormat) {
                case 1:
                    return src_data;
                case 2:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::NV21ToI420);
                case 3:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::NV21ToRGB565);
                case 4:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::NV21ToRGB24);
                case 5:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::NV21ToRGBA);
                default:
                    return nullptr;
            }
        case 2:
            switch (targetFormat) {
                case 1:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::I420ToNV21);
                case 2:
                    return src_data;
                case 3:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::I420ToRGB565);
                case 4:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::I420ToRGB24);
                case 5:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::I420ToRGBA);
                default:
                    return nullptr;
            }
        case 3:
            switch (targetFormat) {
                case 1:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGB565ToNV21);
                case 2:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGB565ToI420);
                case 3:
                    return src_data;
                case 4:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGB565ToRGB24);
                case 5:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGB565ToRGBA);
                default:
                    return nullptr;
            }
        case 4:
            switch (targetFormat) {
                case 1:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGB24ToNV21);
                case 2:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGB24ToI420);
                case 3:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGB24ToRGB565);
                case 4:
                    return src_data;
                case 5:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGB24ToRGBA);
                default:
                    return nullptr;
            }
            break;
        case 5:
            switch (targetFormat) {
                case 1:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGBAToNV21);
                case 2:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGBAToI420);
                case 3:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGBAToRGB565);
                case 4:
                    return __ImageConvert__(env, src_data, width, height, dataFormat, targetFormat, yancy::RGBAToRGB24);
                case 5:
                    return src_data;
                default:
                    return nullptr;
            }
            break;
        default:
            return nullptr;
    }
}

jobject imageToBitmap(JNIEnv *env, jclass clazz, jbyteArray src_data, jint width, jint height, jint dataFormat, jint bitmapConfig) {
    switch (dataFormat) {
        case 1:
            switch (bitmapConfig) {
                case 3:
                    return __ImageToBitmap__(env, src_data, width, height, dataFormat, bitmapConfig, yancy::NV21ToRGB565);
                case 5:
                    return __ImageToBitmap__(env, src_data, width, height, dataFormat, bitmapConfig, yancy::NV21ToRGBA);
                default:
                    return nullptr;
            }
            break;
        case 2:
            switch (bitmapConfig) {
                case 3:
                    return __ImageToBitmap__(env, src_data, width, height, dataFormat, bitmapConfig, yancy::I420ToRGB565);
                case 5:
                    return __ImageToBitmap__(env, src_data, width, height, dataFormat, bitmapConfig, yancy::I420ToRGBA);
                default:
                    return nullptr;
            }
            break;
        case 3:
            switch (bitmapConfig) {
                case 3: {
                    jbyte *src_data_bytes = checkDataAndConvert(env, src_data, width * height * 2);
                    auto callback = [=](unsigned char *pixel) -> void {
                        memcpy(pixel, reinterpret_cast<unsigned char *>(src_data_bytes),
                               sizeof(unsigned char) * (width * height * 2));
                    };
                    return createBitmap(env, src_data, src_data_bytes, width, height, callback, RGB_565);
                }
                case 5:
                    return __ImageToBitmap__(env, src_data, width, height, dataFormat, bitmapConfig, yancy::RGB565ToRGBA);
                default:
                    return nullptr;
            }
            break;
        case 4:
            switch (bitmapConfig) {
                case 3:
                    return __ImageToBitmap__(env, src_data, width, height, dataFormat, bitmapConfig, yancy::RGB24ToRGB565);
                case 5:
                    return __ImageToBitmap__(env, src_data, width, height, dataFormat, bitmapConfig, yancy::RGB24ToRGBA);
                default:
                    return nullptr;
            }
            break;
        case 5:
            switch (bitmapConfig) {
                case 3:
                    return __ImageToBitmap__(env, src_data, width, height, dataFormat, bitmapConfig, yancy::RGBAToRGB565);
                case 5: {
                    jbyte *src_data_bytes = checkDataAndConvert(env, src_data, width * height * 4);
                    auto callback = [=](unsigned char *pixel) -> void {
                        memcpy(pixel, reinterpret_cast<unsigned char *>(src_data_bytes),
                               sizeof(unsigned char) * (width * height * 4));
                    };
                    return createBitmap(env, src_data, src_data_bytes, width, height, callback);
                }
                default:
                    return nullptr;
            }
            break;
        default:
            return nullptr;
    }
}

jbyteArray bitmapToNV21(JNIEnv *env, jclass clazz, jobject jbitmap) {

    auto callback = [](uint8 **target_data, int width, int height, int *dataSize, uint8 *pixel,
                       BitmapFormat format) -> int {
        *dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
        *target_data = new uint8[*dataSize];
        if (format == ARGB_8888) {
            return yancy::RGBAToNV21(pixel, width, height, *target_data);
        } else if (format == RGB_565) {
            return yancy::RGB565ToNV21(pixel, width, height, *target_data);
        } else {
            return -1;
        }
    };
    return bitmapToByteArray(env, jbitmap, callback);
}

jbyteArray bitmapToRgb565(JNIEnv *env, jclass clazz, jobject jbitmap) {

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

jbyteArray bitmapToRgb24(JNIEnv *env, jclass clazz, jobject jbitmap) {
    auto callback = [](uint8 **target_data, int width, int height, int *dataSize, uint8 *pixel,
                       BitmapFormat format) -> int {
        *dataSize = width * height * 3;
        *target_data = new uint8[*dataSize];
        if (format == ARGB_8888) {
            return yancy::RGBAToRGB24(pixel, width, height, *target_data);
        } else if (format == RGB_565) {
            return yancy::RGB565ToRGB24(pixel, width, height, *target_data);
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

jbyteArray bitmapToI420(JNIEnv *env, jclass clazz, jobject jbitmap) {

    auto callback = [](uint8 **target_data, int width, int height, int *dataSize, uint8 *pixel,
                       BitmapFormat format) -> int {
        *dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
        *target_data = new uint8[*dataSize];
        if (format == ARGB_8888) {
            return yancy::RGBAToI420(pixel, width, height, *target_data);
        } else if (format == RGB_565) {
            return yancy::RGB565ToI420(pixel, width, height, *target_data);
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

jbyteArray intArrayToByteArray(JNIEnv *env, jclass clazz, jintArray intArray) {
    jint *srcData = env->GetIntArrayElements(intArray, JNI_FALSE);
    int dataSize = env->GetArrayLength(intArray) * 4;
    jbyteArray dstData = env->NewByteArray(dataSize);
    env->SetByteArrayRegion(dstData, 0, dataSize, reinterpret_cast<const jbyte *>(srcData));
    return dstData;
}

jintArray byteArrayToIntArray(JNIEnv *env, jclass clazz, jbyteArray byteArray) {
    jbyte *srcData = env->GetByteArrayElements(byteArray, JNI_FALSE);
    int dataSize = env->GetArrayLength(byteArray) / 4;
    jintArray dstData = env->NewIntArray(dataSize);
    env->SetIntArrayRegion(dstData, 0, dataSize, reinterpret_cast<const jint *>(srcData));
    return dstData;
}

jbyteArray
dataClipRotate(JNIEnv *env, jclass clazz, jbyteArray byteArray, jint dataFormat, jint width, jint height, jint degree, jobject rect,
               jint targetFormat, jboolean priorityClip) {
    ConvertData convertData;
    int resCode = convertDataHandle(env, dataFormat, width, height, degree, rect, priorityClip, &convertData);
    if (resCode != 0) {
        return nullptr;
    }
    jbyte *src_data = checkDataAndConvert(env, byteArray, convertData.dataSize);
    auto callback = [=](uint8 *pixels) -> int {
        return yancy::DataConvert(reinterpret_cast<unsigned char *>(src_data), width, height, convertData.dataSize,
                                  pixels, convertData.targetWidth, convertData.targetHeight,
                                  degree, convertData.format, targetFormat, convertData.rotateMode,
                                  convertData.crop_x, convertData.crop_y);
    };
    return createColorBytes(
            env, byteArray, src_data,
            yancy::getDataSize(convertData.targetWidth, convertData.targetHeight, targetFormat),
            callback);
}

jobject
dataClipRotateToBitmap(JNIEnv *env, jclass clazz, jbyteArray byteArray, jint dataFormat, jint width,
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
        case 4:
            dataSize = width * height * 3;
            src_fourcc = libyuv::FOURCC_BGR3;
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
        case 4:
            dst_data_size = width * height * 3;
            dst_fourcc = libyuv::FOURCC_BGR3;
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
        case 4:
            convertData->format = libyuv::FOURCC_BGR3;
            convertData->dataSize = width * height * 3;
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
                /*logger::error("x = ", convertData->crop_x, ", y = ", convertData->crop_y, ", tw = ", convertData->targetWidth,
                              ", th = ", convertData->targetHeight);*/
                if (right > height || bottom > width
                    //                    || convertData->crop_x > convertData->targetWidth || convertData->crop_y > convertData->targetHeight
                    || convertData->crop_x > height || convertData->crop_y > width
                        ) {
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
                /*logger::error("x = ", convertData->crop_x, ", y = ", convertData->crop_y, ", tw = ", convertData->targetWidth,
                              ", th = ", convertData->targetHeight);*/
                if (right > height || bottom > width
                    //                    || convertData->crop_x > convertData->targetWidth || convertData->crop_y > convertData->targetHeight
                    || convertData->crop_x > height || convertData->crop_y > width
                        ) {
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
    } else if (dataFormat == 4) {
        src_data = checkDataAndConvert(env, byteArray, width * height * 3);
    } else if (dataFormat == 5) {
        src_data = checkDataAndConvert(env, byteArray, width * height * 4);
    }
    if (src_data == nullptr) {
        return nullptr;
    }

    int dst_data_size = 0;

    if (targetFormat == 1 || targetFormat == 2) {
        dst_data_size = dstWidth * dstHeight + ((dstWidth + 1) / 2) * ((dstHeight + 1) / 2) * 2;
    } else if (targetFormat == 3) {
        dst_data_size = dstWidth * dstHeight * 2;
    } else if (targetFormat == 4) {
        dst_data_size = dstWidth * dstHeight * 3;
    } else if (targetFormat == 5) {
        dst_data_size = dstWidth * dstHeight * 4;
    }
    if (dst_data_size == 0) {
        logger::error("Not support this format!");
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

jbyteArray
__ImageConvert__(JNIEnv *env, jbyteArray dataArray, jint width, jint height, jint src_format, jint dst_format, __convert__ convert) {
    int src_data_size = yancy::getDataSize(width, height, src_format);
    int dst_data_size = yancy::getDataSize(width, height, dst_format);
    if (!src_data_size || !dst_data_size) {
        //不支持的格式转换操作
        return nullptr;
    }
    jbyte *src_data = checkDataAndConvert(env, dataArray, src_data_size);
    auto callback = [=](uint8 *dst_data) -> int {
        return convert(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    return createColorBytes(env, dataArray, src_data, dst_data_size, callback);
}

jobject
__ImageToBitmap__(JNIEnv *env, jbyteArray dataArray, jint width, jint height, jint src_format, jint dst_format, __convert__ convert) {
    int src_data_size = yancy::getDataSize(width, height, src_format);
    int dst_data_size = yancy::getDataSize(width, height, dst_format);
    if (!src_data_size || !dst_data_size) {
        logger::error("This format operation is not supported yet!");
        return nullptr;
    }
    jbyte *src_data = checkDataAndConvert(env, dataArray, src_data_size);
    auto callback = [=](uint8 *dst_data) -> int {
        return convert(reinterpret_cast<uint8 *>(src_data), width, height, dst_data);
    };
    BitmapFormat bitmapFormat;
    if (dst_format == 3) {
        bitmapFormat = RGB_565;
    } else if (dst_format == 5) {
        bitmapFormat = ARGB_8888;
    } else {
        logger::error("This format operation is not supported yet!");
        return nullptr;
    }
    return createBitmap(env, dataArray, src_data, width, height, callback, bitmapFormat);
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
    jbyteArray res = env->NewByteArray(dataSize);
    env->SetByteArrayRegion(res, 0, dataSize, reinterpret_cast<const jbyte *>(target_data));
    AndroidBitmap_unlockPixels(env, jbitmap);

    if (target_data != NULL) {
        delete[] target_data;
    }

    return res;
}




