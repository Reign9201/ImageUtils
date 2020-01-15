package com.yancy.yuvutils

import android.graphics.Bitmap
import android.graphics.Rect
import android.util.Log
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
    @JvmStatic
    fun bitmapToNV21(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToNV21(bitmap)
    }

    @JvmStatic
    fun bitmapToRgb565(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToRgb565(bitmap)
    }

    @JvmStatic
    fun bitmapToRgb24(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToRgb24(bitmap)
    }

    @JvmStatic
    fun bitmapToRgba(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToRgba(bitmap)
    }

    @JvmStatic
    fun bitmapToI420(bitmap: Bitmap?): ByteArray? {
        return YuvUtils.bitmapToI420(bitmap)
    }

    /************************************ NV21格式的数据转换操作 *******************************************/

    private fun dataToData(
        data: ByteArray,
        width: Int,
        height: Int,
        degree: Int,
        srcFormat: ImageFormat,
        dstFormat: ImageFormat
    ): ByteArray? {
        return if (degree == 0) {
            YuvUtils.imageFormatConvert(data, width, height, srcFormat.format, dstFormat.format)
        } else {
            dataClipRotate(data, srcFormat, width, height, degree, null, dstFormat)
        }
    }

    private fun dataToBitmap(
        data: ByteArray,
        width: Int,
        height: Int,
        degree: Int,
        srcFormat: ImageFormat,
        dstFormat: ImageFormat
    ): Bitmap? {
        return if (degree == 0) {
            imageToBitmap(data, width, height, srcFormat, dstFormat)
        } else {
            dataClipRotateToBitmap(data, srcFormat, width, height, degree, null, dstFormat)
        }
    }

    @JvmOverloads
    @JvmStatic
    fun nv21ToI420(nv21Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(nv21Data, width, height, degree, ImageFormat.NV21, ImageFormat.I420)
    }

    @JvmOverloads
    @JvmStatic
    fun nv21ToRgb565(nv21Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(nv21Data, width, height, degree, ImageFormat.NV21, ImageFormat.RGB_565)
    }

    @JvmOverloads
    @JvmStatic
    fun nv21ToRgb24(nv21Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(nv21Data, width, height, degree, ImageFormat.NV21, ImageFormat.BGR_888)
    }

    @JvmOverloads
    @JvmStatic
    fun nv21ToRgba(nv21Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(nv21Data, width, height, degree, ImageFormat.NV21, ImageFormat.ARGB_8888)
    }

    @JvmOverloads
    @JvmStatic
    fun nv21ToBitmap8888(nv21Data: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(nv21Data, width, height, degree, ImageFormat.NV21, ImageFormat.ARGB_8888)
    }

    @JvmOverloads
    @JvmStatic
    fun nv21ToBitmap565(nv21Data: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(nv21Data, width, height, degree, ImageFormat.NV21, ImageFormat.RGB_565)
    }

    @JvmStatic
    fun nv21Rotate(nv21Data: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(nv21Data, 1, width, height, degree, null, 1, false)
    }

    @JvmStatic
    fun nv21Clip(nv21Data: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(nv21Data, 1, width, height, 0, rect, 1, false)
    }

    @JvmStatic
    fun nv21Mirror(nv21Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(nv21Data, width, height, 1, 1)
    }

    @JvmStatic
    fun nv21Scale(nv21Data: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(nv21Data, width, height, dstWidth, dstHeight, 1, 1)
    }

    /************************************ I420格式的数据转换操作 ********************************************/

    @JvmOverloads
    @JvmStatic
    fun i420ToNV21(i420Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(i420Data, width, height, degree, ImageFormat.I420, ImageFormat.NV21)
    }

    @JvmOverloads
    @JvmStatic
    fun i420ToRgb565(i420Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(i420Data, width, height, degree, ImageFormat.I420, ImageFormat.RGB_565)
    }

    @JvmOverloads
    @JvmStatic
    fun i420ToRgb24(i420Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(i420Data, width, height, degree, ImageFormat.I420, ImageFormat.BGR_888)
    }

    @JvmOverloads
    @JvmStatic
    fun i420ToRgba(i420Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(i420Data, width, height, degree, ImageFormat.I420, ImageFormat.ARGB_8888)
    }

    @JvmOverloads
    @JvmStatic
    fun i420ToBitmap565(i420Data: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(i420Data, width, height, degree, ImageFormat.I420, ImageFormat.RGB_565)
    }

    @JvmOverloads
    @JvmStatic
    fun i420ToBitmap8888(i420Data: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(i420Data, width, height, degree, ImageFormat.I420, ImageFormat.ARGB_8888)
    }

    @JvmStatic
    fun i420Rotate(i420Data: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(i420Data, 2, width, height, degree, null, 2, false)
    }

    @JvmStatic
    fun i420Clip(i420Data: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(i420Data, 2, width, height, 0, rect, 2, false)
    }

    @JvmStatic
    fun i420Mirror(i420Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(i420Data, width, height, 2, 2)
    }

    @JvmStatic
    fun i420Scale(i420Data: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(i420Data, width, height, dstWidth, dstHeight, 2, 2)
    }


    /************************************ RGBA格式的数据转换操作 ********************************************/

    @JvmOverloads
    @JvmStatic
    fun rgbaToNV21(rgbaData: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgbaData, width, height, degree, ImageFormat.ARGB_8888, ImageFormat.NV21)
    }

    @JvmOverloads
    @JvmStatic
    fun rgbaToI420(rgbaData: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgbaData, width, height, degree, ImageFormat.ARGB_8888, ImageFormat.I420)
    }

    @JvmOverloads
    @JvmStatic
    fun rgbaToRgb565(rgbaData: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgbaData, width, height, degree, ImageFormat.ARGB_8888, ImageFormat.RGB_565)
    }

    @JvmOverloads
    @JvmStatic
    fun rgbaToRgb24(rgbaData: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgbaData, width, height, degree, ImageFormat.ARGB_8888, ImageFormat.BGR_888)
    }

    @JvmOverloads
    @JvmStatic
    fun rgbaToBitmap565(rgbaData: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(rgbaData, width, height, degree, ImageFormat.ARGB_8888, ImageFormat.RGB_565)
    }

    @JvmOverloads
    @JvmStatic
    fun rgbaToBitmap8888(rgbaData: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(rgbaData, width, height, degree, ImageFormat.ARGB_8888, ImageFormat.ARGB_8888)
    }

    @JvmStatic
    fun rgbaRotate(rgbaData: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(rgbaData, 5, width, height, degree, null, 5, false)
    }

    @JvmStatic
    fun rgbaClip(rgbaData: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(rgbaData, 5, width, height, 0, rect, 5, false)
    }

    @JvmStatic
    fun rgbaMirror(rgbaData: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(rgbaData, width, height, 5, 5)
    }

    @JvmStatic
    fun rgbaScale(rgbaData: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(rgbaData, width, height, dstWidth, dstHeight, 5, 5)
    }


    /************************************ RGB565格式的数据转换操作 ********************************************/

    @JvmOverloads
    @JvmStatic
    fun rgb565ToNV21(rgb565Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgb565Data, width, height, degree, ImageFormat.RGB_565, ImageFormat.NV21)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb565ToI420(rgb565Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgb565Data, width, height, degree, ImageFormat.RGB_565, ImageFormat.I420)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb565ToRgb24(rgb565Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgb565Data, width, height, degree, ImageFormat.RGB_565, ImageFormat.BGR_888)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb565ToRgba(rgb565Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgb565Data, width, height, degree, ImageFormat.RGB_565, ImageFormat.ARGB_8888)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb565ToBitmap565(rgb565Data: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(rgb565Data, width, height, degree, ImageFormat.RGB_565, ImageFormat.RGB_565)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb565ToBitmap8888(rgb565Data: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(rgb565Data, width, height, degree, ImageFormat.RGB_565, ImageFormat.ARGB_8888)
    }

    @JvmStatic
    fun rgb565Rotate(rgb565Data: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(rgb565Data, 3, width, height, degree, null, 3, false)
    }

    @JvmStatic
    fun rgb565Clip(rgb565Data: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(rgb565Data, 3, width, height, 0, rect, 3, false)
    }

    @JvmStatic
    fun rgb565Mirror(rgb565Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(rgb565Data, width, height, 3, 3)
    }

    @JvmStatic
    fun rgb565Scale(rgb565Data: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(rgb565Data, width, height, dstWidth, dstHeight, 3, 3)
    }


    /************************************ RGB24【即BGR888】格式的数据转换操作 ********************************************/

    @JvmOverloads
    @JvmStatic
    fun rgb24ToNV21(rgb24Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgb24Data, width, height, degree, ImageFormat.BGR_888, ImageFormat.NV21)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb24ToI420(rgb24Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgb24Data, width, height, degree, ImageFormat.BGR_888, ImageFormat.I420)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb24ToRgb565(rgb24Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgb24Data, width, height, degree, ImageFormat.BGR_888, ImageFormat.RGB_565)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb24ToRgba(rgb24Data: ByteArray, width: Int, height: Int, degree: Int = 0): ByteArray? {
        return dataToData(rgb24Data, width, height, degree, ImageFormat.BGR_888, ImageFormat.ARGB_8888)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb24ToBitmap565(rgb24Data: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(rgb24Data, width, height, degree, ImageFormat.BGR_888, ImageFormat.RGB_565)
    }

    @JvmOverloads
    @JvmStatic
    fun rgb24ToBitmap8888(rgb24Data: ByteArray, width: Int, height: Int, degree: Int = 0): Bitmap? {
        return dataToBitmap(rgb24Data, width, height, degree, ImageFormat.BGR_888, ImageFormat.ARGB_8888)
    }

    @JvmStatic
    fun rgb24Rotate(rgb24Data: ByteArray, width: Int, height: Int, @RotateDegree degree: Int): ByteArray? {
        return YuvUtils.dataClipRotate(rgb24Data, 4, width, height, degree, null, 4, false)
    }

    @JvmStatic
    fun rgb24Clip(rgb24Data: ByteArray, width: Int, height: Int, rect: Rect): ByteArray? {
        return YuvUtils.dataClipRotate(rgb24Data, 4, width, height, 0, rect, 4, false)
    }

    @JvmStatic
    fun rgb24Mirror(rgb24Data: ByteArray, width: Int, height: Int): ByteArray? {
        return YuvUtils.dataMirror(rgb24Data, width, height, 4, 4)
    }

    @JvmStatic
    fun rgb24Scale(rgb24Data: ByteArray, width: Int, height: Int, dstWidth: Int, dstHeight: Int): ByteArray? {
        return YuvUtils.dataScale(rgb24Data, width, height, dstWidth, dstHeight, 4, 4)
    }

    @JvmStatic
    fun imageToBitmap(data: ByteArray, width: Int, height: Int, srcFormat: ImageFormat, dstFormat: ImageFormat): Bitmap? {
        return YuvUtils.imageToBitmap(data, width, height, srcFormat.format, dstFormat.format)
    }


    /************************************ 各种类型的图像数据裁剪和旋转操作 ********************************************/
    @JvmStatic
    fun dataClipRotate(
        data: ByteArray,
        dataFormat: ImageFormat,
        width: Int,
        height: Int,
        @RotateDegree degree: Int,
        rect: Rect?,
        targetFormat: ImageFormat,
        priorityClip: Boolean = false
    ): ByteArray? {
        return YuvUtils.dataClipRotate(
            data, dataFormat.format,
            width, height,
            degree, rect,
            targetFormat.format, priorityClip
        )
    }

    @JvmStatic
    fun dataClipRotateToBitmap(imageData: ImageInfo): Bitmap? {
        imageData.run {
            val config = when (bitmapConfig) {
                Bitmap.Config.RGB_565 -> 3
                Bitmap.Config.ARGB_8888 -> 5
                else -> throw IllegalArgumentException("This format is not supported yet.")
            }
            return YuvUtils.dataClipRotateToBitmap(
                data, dataFormat.format,
                width, height, degree,
                rect, config, priorityClip
            )
        }
    }

    @JvmStatic
    fun dataClipRotateToBitmap(
        data: ByteArray,
        srcFormat: ImageFormat,
        width: Int,
        height: Int,
        @RotateDegree degree: Int,
        rect: Rect?,
        dstFormat: ImageFormat,
        priorityClip: Boolean = false
    ): Bitmap? {
        require(!(dstFormat != ImageFormat.ARGB_8888 && dstFormat != ImageFormat.RGB_565)) { "This format is not supported yet." }
        return YuvUtils.dataClipRotateToBitmap(data, srcFormat.format, width, height, degree, rect, dstFormat.format, priorityClip)
    }


    /************************************ 图像数据镜像翻转操作 ********************************************/

    @JvmStatic
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
    @JvmStatic
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