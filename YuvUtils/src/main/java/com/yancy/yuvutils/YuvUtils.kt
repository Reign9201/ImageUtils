package com.yancy.yuvutils

import android.graphics.Bitmap
import android.graphics.Rect
import com.yancy.yuvutils.annotation.RotateDegree
import com.yancy.yuvutils.annotation.SupportFilter
import com.yancy.yuvutils.annotation.SupportFormat

/**
 * 说明：基于libyuv库做的Android中常用的图像数据格式转换
 *
 * @author Yancy
 * @date 2019/11/13
 */
@Suppress("UNUSED")
object YuvUtils {
    init {
        System.loadLibrary("YuvUtils")
    }

    /**
     * bitmap 转换成其他图像格式数据
     *
     * @param bitmap 仅支持 RGB_565 和 RGBA_8888 两种类型的位图转换
     * @return 转换后的数据，转换格式异常会导致转换识别，返回为 null
     */
    external fun bitmapToNV21(bitmap: Bitmap?): ByteArray?
    external fun bitmapToRgb565(bitmap: Bitmap?): ByteArray?
    external fun bitmapToRgb24(bitmap: Bitmap?): ByteArray?
    external fun bitmapToRgba(bitmap: Bitmap?): ByteArray?
    external fun bitmapToI420(bitmap: Bitmap?): ByteArray?


    /**
     * int数组类型数据与byte数组类型数据互转操作
     */
    external fun intArrayToByteArray(intArray: IntArray): ByteArray?
    external fun byteArrayToIntArray(byteArray: ByteArray): IntArray?


    /**
     * 图像格式互相转换，支持的格式详见 ImageFormat 枚举类
     *
     * @param data          图像源数据
     * @param width         图像的宽
     * @param height        图像的高
     * @param dataFormat    源图像格式
     * @param targetFormat  目标图像格式
     *
     * @return 返回转换格式后的图像数据
     */
    external fun imageFormatConvert(
        data: ByteArray,
        width: Int,
        height: Int,
        @SupportFormat dataFormat: Int,
        @SupportFormat targetFormat: Int
    ): ByteArray?

    /**
     * 图像格式互相转换
     *
     * @param data          图像源数据
     * @param width         图像的宽
     * @param height        图像的高
     * @param dataFormat    源图像格式，源格式详见 ImageFormat 枚举类
     * @param bitmapConfig  目标位图格式，仅支持 RGB565 和 ARGB_8888 两种格式
     *
     * @return 返回转换格式后的位图 Bitmap
     */
    external fun imageToBitmap(
        data: ByteArray,
        width: Int,
        height: Int,
        @SupportFormat dataFormat: Int,
        bitmapConfig: Int
    ):Bitmap?

    /**
     * 各种类型的图像数据裁剪和旋转操作
     *
     * @param data         原始数据
     * @param dataFormat   数据格式，可参考 {@link ImageInfo # ImageFormat}
     * @param width        原始数据的宽
     * @param height       原始数据的高
     * @param rect         裁剪矩形，可为 null
     * @param targetFormat 生成的图像格式，可参考 {@link ImageInfo # ImageFormat}
     * @param priorityClip 是否优先支持裁剪操作，true 是。
     *                     需要注意的是，先裁剪再旋转和先旋转再裁剪是两种不同的操作
     */
    external fun dataClipRotate(
        data: ByteArray,
        @SupportFormat dataFormat: Int,
        width: Int,
        height: Int,
        @RotateDegree degree: Int,
        rect: Rect?,
        targetFormat: Int,
        priorityClip: Boolean = false
    ): ByteArray?

    /**
     * 各种类型的图像数据裁剪和旋转后生成位图操作
     *
     * @param data         原始数据
     * @param dataFormat   数据格式，可参考 {@link ImageInfo # ImageFormat}
     * @param width        原始数据的宽
     * @param height       原始数据的高
     * @param rect         裁剪矩形，可为 null
     * @param bitmapConfig 生成的bitmap格式，目前仅支持 RGB_565 和 ARGB_8888
     * @param priorityClip 是否优先支持裁剪操作，true 是。
     *                     需要注意的是，是先裁剪在旋转和先旋转再裁剪是两种不同的操作
     */
    external fun dataClipRotateToBitmap(
        data: ByteArray,
        @SupportFormat dataFormat: Int,
        width: Int,
        height: Int,
        @RotateDegree degree: Int,
        rect: Rect?,
        bitmapConfig: Int,
        priorityClip: Boolean = false
    ): Bitmap?

    /**
     * 图像数据镜像翻转操作
     *
     * @param data              图像原始数据
     * @param width             图像原始宽
     * @param height            图像原始高
     * @param dataFormat        源图像格式
     * @param targetFormat      缩放后的图像格式
     * @param isVerticalMirror  是否执行垂直镜像操作，默认false，即水平翻转，
     *                          若为true，即对图像进行了 180 旋转，而并非真正的垂直镜像
     *
     * @return 镜像翻转后的数据
     */
    external fun dataMirror(
        data: ByteArray,
        width: Int,
        height: Int,
        @SupportFormat dataFormat: Int,
        @SupportFormat targetFormat: Int,
        isVerticalMirror: Boolean = false
    ): ByteArray?

    /**
     * 图像缩放操作
     *
     * @param data          图像原始数据
     * @param width         图像原始宽
     * @param height        图像原始高
     * @param dstWidth      缩放后的宽
     * @param dstHeight     缩放后的高
     * @param dataFormat    源图像格式
     * @param targetFormat  缩放后的图像格式
     * @param filterMode    过滤模式
     * @return              缩放后的图像数据
     */
    external fun dataScale(
        data: ByteArray,
        width: Int,
        height: Int,
        dstWidth: Int,
        dstHeight: Int,
        @SupportFormat dataFormat: Int,
        @SupportFormat targetFormat: Int,
        @SupportFilter filterMode: Int = 0
    ): ByteArray?

}
