package com.yancy.yuvutils.entry


import android.graphics.Bitmap
import android.graphics.Rect
import com.yancy.yuvutils.annotation.RotateDegree

/**
 * 说明：图像数据data
 * @author  Yancy
 * @date 2019/11/29
 */
class ImageData(
    val data: ByteArray,
    val dataFormat: ImageFormat,
    val width: Int,
    val height: Int,
    @RotateDegree val degree: Int = 0,
    val rect: Rect? = null,
    val bitmapConfig: Bitmap.Config = Bitmap.Config.ARGB_8888,
    val priorityClip: Boolean = true
)

@Suppress("UNUSED")
enum class ImageFormat(var format: Int) {
    NV21(1),
    I420(2),
    RGB_565(3),
    RGB_888(4),
    ARGB_8888(5)
}

/**
 * libyuv做图像缩放时候的过滤模式
 */
@Suppress("UNUSED")
enum class FilterMode(var filter: Int) {
    /**
     * Point sample; Fastest.
     */
    FilterNone(0),

    /**
     * Filter horizontally only.
     */
    FilterLinear(1),

    /**
     *  Faster than box, but lower quality scaling down.
     */
    FilterBilinear(2),

    /**
     * Highest quality.
     */
    FilterBox(3)
}