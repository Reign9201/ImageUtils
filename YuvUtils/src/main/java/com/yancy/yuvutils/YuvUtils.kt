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

    external fun bitmapToNV21(bitmap: Bitmap?): ByteArray?
}
