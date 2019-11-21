//
// Created by XuYanjun on 2019/11/19.
//

#ifndef IMAGEUTILS_CPPTOJAVAHELPER_HPP
#define IMAGEUTILS_CPPTOJAVAHELPER_HPP

#include <jni.h>
#include <android/bitmap.h>

enum BitmapFormat {
    ARGB_8888,
    RGB_565
};

const char *formatToStr(BitmapFormat format) {
    switch (format) {
        case RGB_565:
            return "RGB_565";
        case ARGB_8888:
        default:
            return "ARGB_8888";
    }
}

/**
 * 生成 Bitmap
 * @tparam  Func        数据类型转换模版
 * @param   env         jni---env
 * @param   width       图像宽
 * @param   height      图像搞
 * @param   callback    模版函数回调方法
 * @param   format      图像格式
 * @return              返回 Bitmap 对象给 Java 层
 */
template<typename Func>
jobject createBitmap(JNIEnv *env, jbyteArray data, jbyte *src_data, int width, int height, Func callback,
                     BitmapFormat format = ARGB_8888);

template<typename Func>
jbyteArray
createColorBytes(JNIEnv *env, jbyteArray data, jbyte *src_data, int dataSize, Func callback);

#endif //IMAGEUTILS_CPPTOJAVAHELPER_HPP
