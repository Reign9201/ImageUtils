package com.yancy.yuvutils.entry


import android.graphics.Bitmap
import android.graphics.Rect
import com.yancy.yuvutils.annotation.RotateDegree

/**
 * 说明：
 * @author  Yancy
 * @date 2019/11/29
 */
data class ImageData(
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
    ARGB_8888(5)
}

/**
 * libyuv做图像缩放时候的过滤模式
 */
enum class FilterMode(var fillter: Int) {
    /**
     * Point sample; Fastest.
     */
    kFilterNone(0),

    /**
     * Filter horizontally only.
     */
    kFilterLinear(1),

    /**
     *  Faster than box, but lower quality scaling down.
     */
    kFilterBilinear(2),

    /**
     * Highest quality.
     */
    kFilterBox(3)
}