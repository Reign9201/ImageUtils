package com.yancy.imageutils

import android.Manifest
import android.graphics.*
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.yancy.imageutils.test.Test
import com.yancy.yuvutils.YuvUtils
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        PermissionUtil.addPermission(
            this,
            android.Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.CAMERA

        )
            .request(this)

        val bitmap = BitmapFactory.decodeFile("/sdcard/test.png")

        //  LogUtils.e("---${bitmap.getPixel(bitmap.width, bitmap.height)}")
        Bitmap.Config.ARGB_8888


        val bitmapToNV21 = YuvUtils.bitmapToNV21(bitmap)
//        bitmapToNV21?.apply {
//            LogUtils.d("size = $size")
//            LogUtils.d("0 = ${this[0]}")
//            LogUtils.d("100 = ${this[100]}")
//            LogUtils.d("1000 = ${this[1000]}")
//            LogUtils.d("10000 = ${this[10000]}")
//            LogUtils.d("130000 = ${this[130000]}")


//            val toBitmap =
//                Test.nv21BytesToBitmap(this@MainActivity, this, bitmap.width, bitmap.height)
//            if (toBitmap != null) {
//                imageView.setImageBitmap(toBitmap)
//            } else {
//                LogUtils.e("llllllllllllllll")
//            }
//        } ?: LogUtils.e("数据空啦！")

        bitmapToNV21?.apply {
           /* val rgba8888 = YuvUtils.NV21ToRGBA_8888(bitmapToNV21!!, bitmap.width, bitmap.height)
            LogUtils.e("rgba8888 == null? ${rgba8888 == null}")

            if (rgba8888 != null) {
                val b = BitmapFactory.decodeByteArray(rgba8888,0,rgba8888.size)
                imageView.setImageBitmap(b)
            } else {
                LogUtils.e("is null.")
            }*/

            val b = YuvUtils.NV21ToBitmap8888(bitmapToNV21, bitmap.width, bitmap.height)
            b?.apply { imageView.setImageBitmap(b) }?:LogUtils.e("kong le o ...")


        }?: LogUtils.e("数据空啦！")



    }

    override fun onResume() {
        super.onResume()


    }
}
