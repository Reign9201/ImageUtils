package com.yancy.yuvutils


import android.graphics.Bitmap
import android.graphics.Rect

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
    val degree: Int = 0,
    val rect: Rect? = null,
    val bitmapConfig: Bitmap.Config = Bitmap.Config.ARGB_8888,
    val priorityClip: Boolean = true
)

enum class ImageFormat(var format: Int) {
    NV21(1),
    I420(2),
    RGB_565(3),
    ARGB_8888(5)
}