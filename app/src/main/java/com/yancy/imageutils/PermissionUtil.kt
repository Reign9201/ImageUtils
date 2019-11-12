package com.yancy.imageutils

import android.app.Activity
import android.content.pm.PackageManager
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat

/**
 * 说明：
 * @author  Yancy
 * @date 2019/6/4
 */
object PermissionUtil {
    interface PermissionCallback {
        /**
         * 当权限被拒绝，且点了不在提示之后，再次申请权限，如果设置了回调，会执行该方法
         */
        fun callback()
    }

    private var callback: PermissionCallback? = null
    private val list = ArrayList<String>()
    private const val REQUEST_CODE = 1000


    @JvmStatic
    fun addPermission(activity: Activity, vararg permissions: String): PermissionUtil {
        permissions.forEach {
            if (ContextCompat.checkSelfPermission(activity.applicationContext, it) != PackageManager.PERMISSION_GRANTED) {
                list.add(it)
            }
        }
        return this
    }

    fun request(activity: Activity) {
        if (list.isNotEmpty()) ActivityCompat.requestPermissions(activity, list.toTypedArray(), REQUEST_CODE)
    }

    @JvmStatic
    fun onRequestPermissionsResult(activity: Activity, requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        if (requestCode == REQUEST_CODE) {
            for (index in 0..permissions.size) {
                val rationale = ActivityCompat.shouldShowRequestPermissionRationale(activity, permissions[index])
                val grant = grantResults[index]
                if (!rationale && grant == PackageManager.PERMISSION_DENIED) {
                    if (callback != null) {
                        callback!!.callback()
                    }
                }
                break
            }
            list.clear()
        }
    }

}