package com.yancy.yuvutils

import android.graphics.Bitmap

/**
 * 说明：
 *
 * @author Yancy
 * @date 2019/11/13
 */
//@Suppress("UNUSED")
object YuvUtils {
    init {
        System.loadLibrary("YuvUtils")
    }

    /**
     * NV21转换成RGBA  对应 Android 中的 ARGB_8888
     * @param  nv21Data nv21数据
     * @param width 图像的宽
     * @param height 图像的高
     *
     * @return 返回 RGBA 数据，可能为 null
     */
    external fun nv21ToRgba(nv21Data: ByteArray, width: Int, height: Int): ByteArray?

    external fun nv21ToRgb(nv21Data: ByteArray, width: Int, height: Int): ByteArray?

    external fun nv21ToI420(nv21Data: ByteArray, width: Int, height: Int): ByteArray?

    external fun nv21ToBitmap8888(nv21Data: ByteArray, width: Int, height: Int): Bitmap?

    external fun nv21ToBitmap565(nv21Data: ByteArray, width: Int, height: Int): Bitmap?

    /*****************************************************************************************/

    external fun i420ToNV21(i420Data: ByteArray, width: Int, height: Int): ByteArray?

    external fun i420ToRgba(i420Data: ByteArray, width: Int, height: Int): ByteArray?

    external fun i420ToRgb(i420Data: ByteArray, width: Int, height: Int): ByteArray?

    external fun i420ToBitmap8888(i420Data: ByteArray, width: Int, height: Int): Bitmap?

    external fun i420ToBitmap565(i420Data: ByteArray, width: Int, height: Int): Bitmap?


    /*****************************************************************************************/

    external fun rgbaToNV21(rgbaData: ByteArray, width: Int, height: Int): ByteArray?

    external fun rgbaToI420(rgbaData: ByteArray, width: Int, height: Int): ByteArray?

    external fun rgbaToRgb(rgbaData: ByteArray, width: Int, height: Int): ByteArray?

    external fun rgbaToBitmap8888(rgbaData: ByteArray, width: Int, height: Int): Bitmap?

    external fun rgbaToBitmap565(rgbaData: ByteArray, width: Int, height: Int): Bitmap?

    /*****************************************************************************************/


    external fun rgbToNV21(rgbData: ByteArray, width: Int, height: Int): ByteArray?

    external fun rgbToI420(rgbData: ByteArray, width: Int, height: Int): ByteArray?

    external fun rgbToRgba(rgbData: ByteArray, width: Int, height: Int): ByteArray?

    external fun rgbToBitmap8888(rgbData: ByteArray, width: Int, height: Int): Bitmap?

    external fun rgbToBitmap565(rgbData: ByteArray, width: Int, height: Int): Bitmap?


    /*****************************************************************************************/

    external fun bitmapToNV21(bitmap: Bitmap?): ByteArray?

    external fun bitmapToRgb(bitmap: Bitmap?): ByteArray?
    external fun bitmapToRgba(bitmap: Bitmap?): ByteArray?
    external fun bitmap2Rgba(bitmap: Bitmap?): IntArray?
    external fun bitmapToI420(bitmap: Bitmap?): ByteArray?

    /*****************************************************************************************/
    external fun intToByte(intArray: IntArray): ByteArray?

    external fun byteToInt(byteArray: ByteArray): IntArray?

}
