package com.yancy.yuvutils

import android.graphics.Bitmap
import android.graphics.Rect
import com.yancy.yuvutils.annotation.RotateDegree
import com.yancy.yuvutils.entry.FilterMode
import com.yancy.yuvutils.entry.ImageInfo
import com.yancy.yuvutils.entry.ImageFormat

/**
 * 说明：
 * @author  Yancy
 * @date 2019/12/13
 */
@Suppress("UNUSED")
object ImageUtils {

    /***************************** Bitmap转为其他各种图像格式数据 ***********************************************/
    fun bitmapToNV21(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToNV21(bitmap)
    }

    fun bitmapToRgb565(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToRgb565(bitmap)
    }

    fun bitmapToRgb24(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToRgb24(bitmap)
    }

    fun bitmapToRgba(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToRgba(bitmap)
    }

    fun bitmapToI420(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToI420(bitmap)
    }

    /************************************ NV21格式的数据转换操作 *******************************************/

    fun nv21ToI420(nv21Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(nv21Data, width, height, 1, 2)
    }

    fun nv21ToRgb565(nv21Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(nv21Data, width, height, 1, 3)
    }

    fun nv21ToRgb24(nv21Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(nv21Data, width, height, 1, 4)
    }

    fun nv21ToRgba(nv21Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(nv21Data, width, height, 1, 5)
    }

    fun nv21ToBitmap8888(nv21Data: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(nv21Data, width, height, 1, 5)
    }

    fun nv21ToBitmap565(nv21Data: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(nv21Data, width, height, 1, 3)
    }

    fun nv21Rotate(nv21Data: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(nv21Data, 1, width, height, degree, null, 1, false)
    }

    fun nv21Clip(nv21Data: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(nv21Data, 1, width, height, 0, rect, 1, false)
    }

    fun nv21Mirror(nv21Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(nv21Data, width, height, 1, 1)
    }

    fun nv21Scale(nv21Data: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(nv21Data, width, height, dstWidth, dstHeight, 1, 1)
    }

    /************************************ I420格式的数据转换操作 ********************************************/

    fun i420ToNV21(i420Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(i420Data, width, height, 2, 1)
    }

    fun i420ToRgb565(i420Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(i420Data, width, height, 2, 3)
    }

    fun i420ToRgb24(i420Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(i420Data, width, height, 2, 4)
    }

    fun i420ToRgba(i420Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(i420Data, width, height, 2, 5)
    }

    fun i420ToBitmap565(i420Data: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(i420Data, width, height, 2, 3)
    }

    fun i420ToBitmap8888(i420Data: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(i420Data, width, height, 2, 5)
    }

    fun i420Rotate(i420Data: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(i420Data, 2, width, height, degree, null, 2, false)
    }

    fun i420Clip(i420Data: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(i420Data, 2, width, height, 0, rect, 2, false)
    }

    fun i420Mirror(i420Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(i420Data, width, height, 2, 2)
    }

    fun i420Scale(i420Data: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(i420Data, width, height, dstWidth, dstHeight, 2, 2)
    }


    /************************************ RGBA格式的数据转换操作 ********************************************/

    fun rgbaToNV21(rgbaData: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgbaData, width, height, 5, 1)
    }

    fun rgbaToI420(rgbaData: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgbaData, width, height, 5, 2)
    }

    fun rgbaToRgb565(rgbaData: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgbaData, width, height, 5, 3)
    }

    fun rgbaToRgb24(rgbaData: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgbaData, width, height, 5, 4)
    }

    fun rgbaToBitmap565(rgbaData: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(rgbaData, width, height, 5, 3)
    }

    fun rgbaToBitmap8888(rgbaData: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(rgbaData, width, height, 5, 5)
    }

    fun rgbaRotate(rgbaData: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(rgbaData, 5, width, height, degree, null, 5, false)
    }

    fun rgbaClip(rgbaData: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(rgbaData, 5, width, height, 0, rect, 5, false)
    }

    fun rgbaMirror(rgbaData: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(rgbaData, width, height, 5, 5)
    }

    fun rgbaScale(rgbaData: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(rgbaData, width, height, dstWidth, dstHeight, 5, 5)
    }


    /************************************ RGB565格式的数据转换操作 ********************************************/

    fun rgb565ToNV21(rgb565Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgb565Data, width, height, 3, 1)
    }

    fun rgb565ToI420(rgb565Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgb565Data, width, height, 3, 2)
    }

    fun rgb565ToRgb24(rgb565Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgb565Data, width, height, 3, 4)
    }

    fun rgb565ToRgba(rgb565Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgb565Data, width, height, 3, 5)
    }

    fun rgb565ToBitmap565(rgb565Data: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(rgb565Data, width, height, 3, 3)
    }

    fun rgb565ToBitmap8888(rgb565Data: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(rgb565Data, width, height, 3, 5)
    }

    fun rgb565Rotate(rgb565Data: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(rgb565Data, 3, width, height, degree, null, 3, false)
    }

    fun rgb565Clip(rgb565Data: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(rgb565Data, 3, width, height, 0, rect, 3, false)
    }

    fun rgb565Mirror(rgb565Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(rgb565Data, width, height, 3, 3)
    }

    fun rgb565Scale(rgb565Data: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(rgb565Data, width, height, dstWidth, dstHeight, 3, 3)
    }


    /************************************ RGB24【即BGR888】格式的数据转换操作 ********************************************/

    fun rgb24ToNV21(rgb24Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgb24Data, width, height, 4, 1)
    }

    fun rgb24ToI420(rgb24Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgb24Data, width, height, 4, 2)
    }

    fun rgb24ToRgb565(rgb24Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgb24Data, width, height, 4, 3)
    }

    fun rgb24ToRgba(rgb24Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.imageFormatConvert(rgb24Data, width, height, 4, 5)
    }

    fun rgb24ToBitmap565(rgb24Data: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(rgb24Data, width, height, 4, 3)
    }

    fun rgb24ToBitmap8888(rgb24Data: ByteArray, width: Int, height: Int): Bitmap? {
        return YuvUtils.imageToBitmap(rgb24Data, width, height, 4, 5)
    }

    fun rgb24Rotate(rgb24Data: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(rgb24Data, 4, width, height, degree, null, 4, false)
    }

    fun rgb24Clip(rgb24Data: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(rgb24Data, 4, width, height, 0, rect, 4, false)
    }

    fun rgb24Mirror(rgb24Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(rgb24Data, width, height, 4, 4)
    }

    fun rgb24Scale(rgb24Data: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(rgb24Data, width, height, dstWidth, dstHeight, 4, 4)
    }


    /************************************ 各种类型的图像数据裁剪和旋转操作 ********************************************/
    fun dataClipRotate(
        data: ByteArray,
        dataFormat: ImageFormat,
        width: Int,
        height: Int,
        @RotateDegree degree: Int,
        rect: Rect?,
        targetFormat: ImageFormat,
        priorityClip: Boolean
    ): ByteArray? {
        return YuvUtils.dataClipRotate(
            data, dataFormat.format,
            width, height,
            degree, rect,
            targetFormat.format, priorityClip
        )
    }

    fun dataClipRotateToBitmap(imageData: ImageInfo): Bitmap? {
        imageData.run {
            val config = when (bitmapConfig) {
                Bitmap.Config.RGB_565 -> 3
                Bitmap.Config.ARGB_8888 -> 5
                else -> throw IllegalStateException("This format is not supported yet.")
            }
            return YuvUtils.dataClipRotateToBitmap(
                data, dataFormat.format,
                width, height, degree,
                rect, config, priorityClip
            )
        }
    }


    /************************************ 图像数据镜像翻转操作 ********************************************/

    fun dataMirror(
        data: ByteArray,
        width: Int,
        height: Int,
        dataFormat: ImageFormat,
        targetFormat: ImageFormat,
        isVerticalMirror: Boolean = false
    ): ByteArray? {
        return YuvUtils.dataMirror(
            data, width, height,
            dataFormat.format, targetFormat.format,
            isVerticalMirror
        )
    }

    /************************************ 图像缩放操作 ********************************************/
    fun dataScale(
        data: ByteArray,
        width: Int,
        height: Int,
        dstWidth: Int,
        dstHeight: Int,
        dataFormat: ImageFormat,
        targetFormat: ImageFormat,
        filterMode: FilterMode = FilterMode.FilterNone
    ): ByteArray? {
        return YuvUtils.dataScale(
            data, width, height,
            dstWidth, dstHeight,
            dataFormat.format, targetFormat.format,
            filterMode.filter
        )
    }
}