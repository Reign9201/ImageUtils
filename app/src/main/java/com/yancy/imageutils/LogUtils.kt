package com.yancy.imageutils

import android.util.Log

/**
 * 说明：日志打印类
 *
 * @author Yancy
 * @date 2018/9/20
 */
object LogUtils {
    private var TAG = "YuvUtils"
    private var openLog = true
    @JvmStatic
    fun setTag(tag: String) {
        TAG = tag
    }

    @JvmStatic
    fun closeLog() {
        openLog = false
    }

    @JvmStatic
    fun v(tag: String, msg: String) {
        if (openLog) {
            Log.v(tag, msg)
        }
    }

    @JvmStatic
    fun v(msg: String) {
        v(TAG, msg)
    }

    @JvmStatic
    fun d(tag: String, msg: String) {
        if (openLog) {
            Log.d(tag, msg)
        }
    }

    @JvmStatic
    fun d(msg: String) {
        d(TAG, msg)
    }

    @JvmStatic
    fun i(tag: String, msg: String) {
        if (openLog) {
            Log.i(tag, msg)
        }
    }

    @JvmStatic
    fun i(msg: String) {
        i(TAG, msg)
    }

    @JvmStatic
    fun w(tag: String, msg: String) {
        if (openLog) {
            Log.w(tag, msg)
        }
    }

    @JvmStatic
    fun w(msg: String) {
        w(TAG, msg)
    }

    @JvmStatic
    fun e(msg: String) {
        e(TAG, msg)
    }

    @JvmStatic
    fun e(tag: String, msg: String) {
        if (openLog) {
            Log.e(tag, msg)
        }
    }
}
