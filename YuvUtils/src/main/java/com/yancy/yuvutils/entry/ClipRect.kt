package com.yancy.yuvutils.entry

import android.graphics.Rect

/**
 * 说明：
 * @author  Yancy
 * @date 2020/1/15
 */
data class ClipRect(val left: Int, val top: Int, val width: Int, val height: Int) {

    fun convert(): Rect {
        return Rect(left, top, left + width, top + height)
    }
}