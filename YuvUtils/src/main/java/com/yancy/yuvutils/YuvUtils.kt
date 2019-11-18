package com.yancy.yuvutils

import android.graphics.Bitmap

/**
 * 说明：
 *
 * @author Yancy
 * @date 2019/11/13
 */
object YuvUtils {
    init {
        System.loadLibrary("YuvUtils")
    }

    external fun test(): Int

    @JvmStatic
    external fun bitmapToNV21(bitmap: Bitmap?): ByteArray?

    @JvmStatic
    external fun NV21ToRGBA_8888(nv21Data: ByteArray, width: Int, height: Int): ByteArray?

    @JvmStatic
    external fun NV21ToBitmap8888(nv21Data: ByteArray, width: Int, height: Int): Bitmap?
}
