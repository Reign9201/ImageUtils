package com.yancy.imageutils

import android.Manifest
import android.graphics.*
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.yancy.yuvutils.YuvUtils
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*

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
        val width = bitmap.width
        val height = bitmap.height

//        nv21Convert(bitmap, width, height)
//        i420Convert(bitmap, width, height)
//        rgbaConvert(bitmap, width, height)

        rgbConvert(bitmap, width, height)



    }



    private fun rgbConvert(bitmap: Bitmap, width: Int, height: Int) {
        LogUtils.e("config = ${bitmap.config}")
        val bitmapToRgb = YuvUtils.bitmapToRgb(bitmap)
        if (bitmapToRgb == null) {
            LogUtils.e("Bitmap 转 RGB 失败")
            return
        }
        LogUtils.e("bitmapToRgb.size = ${bitmapToRgb.size}")
        /**************************************************************************************/
        val rgbToBitmap8888 = YuvUtils.rgbToBitmap8888(bitmapToRgb, width, height)
        if (rgbToBitmap8888 == null) {
            LogUtils.e("RGB 转 Bitmap8888 失败")
            return
        }
        LogUtils.w("rgbToBitmap8888 format = " + rgbToBitmap8888.config)
        //imageView.setImageBitmap(rgbToBitmap8888)

        /**************************************************************************************/
        val rgbToBitmap565 = YuvUtils.rgbToBitmap565(bitmapToRgb, width, height)
        if (rgbToBitmap565 == null) {
            LogUtils.e("RGBA 转 Bitmap565 失败")
            return
        }
        LogUtils.w("rgbToBitmap565 format = " + rgbToBitmap565.config)
        //imageView.setImageBitmap(rgbToBitmap565)

        /**************************************************************************************/

        val rgbToNV21 = YuvUtils.rgbToNV21(bitmapToRgb, width, height)
        if (rgbToNV21 == null) {
            LogUtils.e("RGBA 转 NV21失败")
            return
        }

        /**************************************************************************************/
        val nv21ToBitmap8888 = YuvUtils.nv21ToBitmap8888(rgbToNV21, width, height)
        if (nv21ToBitmap8888 == null) {
            LogUtils.e("NV21 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("nv21ToBitmap8888 format = ${nv21ToBitmap8888.config}")
       // imageView.setImageBitmap(nv21ToBitmap8888)

        /**************************************************************************************/
        val nv21ToBitmap565 = YuvUtils.nv21ToBitmap565(rgbToNV21, width, height)
        if (nv21ToBitmap565 == null) {
            LogUtils.e("NV21 转 Bitmap565 失败")
            return
        }
        LogUtils.d("nv21ToBitmap565 format = ${nv21ToBitmap565.config}")
       // imageView.setImageBitmap(nv21ToBitmap565)


        val bitmap565ToI420 = YuvUtils.bitmapToI420(nv21ToBitmap565)


        /****************************************************************************************/
        // TODO 转换有问题
        val rgbToI420 = YuvUtils.rgbToI420(bitmapToRgb, width, height)
        if (rgbToI420 == null) {
            LogUtils.e("RGB 转 I420 失败")
            return
        }


        /**************************************************************************************/
        val i420ToBitmap8888 = YuvUtils.i420ToBitmap8888(rgbToI420, width, height)
        if (i420ToBitmap8888 == null) {
            LogUtils.e("I420 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("i420ToBitmap8888 format = ${i420ToBitmap8888.config}")
        imageView.setImageBitmap(i420ToBitmap8888)

        /**************************************************************************************/
        val i420ToBitmap565 = YuvUtils.i420ToBitmap565(rgbToI420, width, height)
        if (i420ToBitmap565 == null) {
            LogUtils.e("I420 转 Bitmap565 失败")
            return
        }
        LogUtils.d("i420ToBitmap565 format = ${i420ToBitmap565.config}")

        //imageView.setImageBitmap(i420ToBitmap565)

        /****************************************************************************************/
        val rgbToRgba = YuvUtils.rgbToRgba(bitmapToRgb, width, height)
        if (rgbToRgba == null) {
            LogUtils.e("RGB 转 RGBA 失败")
            return
        }
        //LogUtils.e("==================${rgbToRgba.size}")

        /****************************************************************************************/
        val rgbaToBitmap8888 = YuvUtils.rgbaToBitmap8888(rgbToRgba, width, height)
        if (rgbaToBitmap8888 == null) {
            LogUtils.e("RGBA 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("rgbaToBitmap8888 format = ${rgbaToBitmap8888.config}")

        //imageView.setImageBitmap(rgbaToBitmap8888)

        /****************************************************************************************/
        val rgbaToBitmap565 = YuvUtils.rgbaToBitmap565(rgbToRgba, width, height)
        if (rgbaToBitmap565 == null) {
            LogUtils.e("RGBA 转 Bitmap565 失败")
            return
        }
        LogUtils.d("rgbaToBitmap565 format = ${rgbaToBitmap565.config}")
        //imageView.setImageBitmap(rgbaToBitmap565)
    }

    private fun rgbaConvert(bitmap: Bitmap, width: Int, height: Int) {
        LogUtils.e("config = ${bitmap.config}")
        val bitmapToRgba = YuvUtils.bitmapToRgba(bitmap)
        if (bitmapToRgba == null) {
            LogUtils.e("Bitmap 转 RGBA 失败")
            return
        }
        LogUtils.e("bitmapToRgba.size = ${bitmapToRgba.size}")
        /****************************************************************************************/
        val rgbaToBitmap8888 = YuvUtils.rgbaToBitmap8888(bitmapToRgba, width, height)
        if (rgbaToBitmap8888 == null) {
            LogUtils.e("RGBA 转 Bitmap8888 失败")
            return
        }
        LogUtils.w("rgbaToBitmap8888 format = " + rgbaToBitmap8888.config)
        //imageView.setImageBitmap(rgbaToBitmap8888)

        /****************************************************************************************/
        val rgbaToBitmap565 = YuvUtils.rgbaToBitmap565(bitmapToRgba, width, height)
        if (rgbaToBitmap565 == null) {
            LogUtils.e("RGBA 转 Bitmap565 失败")
            return
        }
        LogUtils.w("rgbaToBitmap565 format = " + rgbaToBitmap565.config)
        //imageView.setImageBitmap(rgbaToBitmap565)

        /****************************************************************************************/

        val rgbaToNV21 = YuvUtils.rgbaToNV21(bitmapToRgba, width, height)
        if (rgbaToNV21 == null) {
            LogUtils.e("RGBA 转 NV21失败")
            return
        }

        /****************************************************************************************/
        val nv21ToBitmap8888 = YuvUtils.nv21ToBitmap8888(rgbaToNV21, width, height)
        if (nv21ToBitmap8888 == null) {
            LogUtils.e("NV21 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("nv21ToBitmap8888 format = ${nv21ToBitmap8888.config}")
        imageView.setImageBitmap(nv21ToBitmap8888)

        /****************************************************************************************/
        val nv21ToBitmap565 = YuvUtils.nv21ToBitmap565(rgbaToNV21, width, height)
        if (nv21ToBitmap565 == null) {
            LogUtils.e("NV21 转 Bitmap565 失败")
            return
        }
        LogUtils.d("nv21ToBitmap565 format = ${nv21ToBitmap565.config}")
        //imageView.setImageBitmap(nv21ToBitmap565)

        /****************************************************************************************/
        val rgbaToI420 = YuvUtils.rgbaToI420(bitmapToRgba, width, height)
        if (rgbaToI420 == null) {
            LogUtils.e("RGBA 转 I420 失败")
            return
        }

        /****************************************************************************************/
        val i420ToBitmap8888 = YuvUtils.i420ToBitmap8888(rgbaToI420, width, height)
        if (i420ToBitmap8888 == null) {
            LogUtils.e("I420 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("i420ToBitmap8888 format = ${i420ToBitmap8888.config}")
       // imageView.setImageBitmap(i420ToBitmap8888)

        /****************************************************************************************/
        val i420ToBitmap565 = YuvUtils.i420ToBitmap565(rgbaToI420, width, height)
        if (i420ToBitmap565 == null) {
            LogUtils.e("I420 转 Bitmap565 失败")
            return
        }
        LogUtils.d("i420ToBitmap565 format = ${i420ToBitmap565.config}")

       // imageView.setImageBitmap(i420ToBitmap565)

        /****************************************************************************************/
        val rgbaToRgb = YuvUtils.rgbaToRgb(bitmapToRgba, width, height)
        if (rgbaToRgb == null) {
            LogUtils.e("RGBA 转 RGB 失败")
            return
        }

        /****************************************************************************************/
        val rgbToBitmap8888 = YuvUtils.rgbToBitmap8888(rgbaToRgb, width, height)
        if (rgbToBitmap8888 == null) {
            LogUtils.e("RGB 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("rgbToBitmap8888 format = ${rgbToBitmap8888.config}")

       // imageView.setImageBitmap(rgbToBitmap8888)

        /****************************************************************************************/
        val rgbToBitmap565 = YuvUtils.rgbToBitmap565(rgbaToRgb, width, height)
        if (rgbToBitmap565 == null) {
            LogUtils.e("RGB 转 Bitmap565 失败")
            return
        }
        LogUtils.d("rgbToBitmap565 format = ${rgbToBitmap565.config}")
        //imageView.setImageBitmap(rgbToBitmap565)
    }

    private fun i420Convert(bitmap: Bitmap, width: Int, height: Int){
        val bitmapToI420 = YuvUtils.bitmapToI420(bitmap)
        if (bitmapToI420 == null) {
            LogUtils.e("Bitmap 转 I420 失败")
            return
        }
        /****************************************************************************************/
        val i420ToBitmap8888 = YuvUtils.i420ToBitmap8888(bitmapToI420, width, height)
        if (i420ToBitmap8888 == null) {
            LogUtils.e("I420 转 Bitmap8888 失败")
            return
        }
        LogUtils.w("i420ToBitmap8888 format = " + i420ToBitmap8888.config)
        //imageView.setImageBitmap(i420ToBitmap8888)

        /****************************************************************************************/
        val i420ToBitmap565 = YuvUtils.i420ToBitmap565(bitmapToI420, width, height)
        if (i420ToBitmap565 == null) {
            LogUtils.e("I420 转 Bitmap565 失败")
            return
        }
        LogUtils.w("i420ToBitmap565 format = " + i420ToBitmap565.config)
        //imageView.setImageBitmap(i420ToBitmap565)

        /****************************************************************************************/
        val i420ToNV21 = YuvUtils.i420ToNV21(bitmapToI420, width, height)
        if (i420ToNV21 == null) {
            LogUtils.e("I420 转 NV21失败")
            return
        }

        /****************************************************************************************/
        val nv21ToBitmap8888 = YuvUtils.nv21ToBitmap8888(i420ToNV21, width, height)
        if (nv21ToBitmap8888 == null) {
            LogUtils.e("NV21 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("nv21ToBitmap8888 format = ${nv21ToBitmap8888.config}")
        //imageView.setImageBitmap(nv21ToBitmap8888)

        /****************************************************************************************/
        val nv21ToBitmap565 = YuvUtils.nv21ToBitmap565(i420ToNV21, width, height)
        if (nv21ToBitmap565 == null) {
            LogUtils.e("NV21 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("nv21ToBitmap565 format = ${nv21ToBitmap565.config}")
        //imageView.setImageBitmap(nv21ToBitmap565)

        /****************************************************************************************/
        val i420ToRgba = YuvUtils.i420ToRgba(bitmapToI420, width, height)
        if (i420ToRgba == null) {
            LogUtils.e("I420 转 RGBA失败")
            return
        }

        /****************************************************************************************/
        val rgbaToBitmap8888 = YuvUtils.rgbaToBitmap8888(i420ToRgba, width, height)
        if (rgbaToBitmap8888 == null) {
            LogUtils.e("RGBA 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("rgbaToBitmap8888 format = ${rgbaToBitmap8888.config}")
        //imageView.setImageBitmap(rgbaToBitmap8888)

        /****************************************************************************************/
        val rgbaToBitmap565 = YuvUtils.rgbaToBitmap565(i420ToRgba, width, height)
        if (rgbaToBitmap565 == null) {
            LogUtils.e("RGBA 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("rgbaToBitmap565 format = ${rgbaToBitmap565.config}")
       // imageView.setImageBitmap(rgbaToBitmap565)

        /****************************************************************************************/
        val i420ToRgb = YuvUtils.i420ToRgb(bitmapToI420, width, height)
        if (i420ToRgb == null) {
            LogUtils.e("I420 转 RGB失败")
            return
        }

        /****************************************************************************************/
        val rgbToBitmap8888 = YuvUtils.rgbToBitmap8888(i420ToRgb, width, height)
        if (rgbToBitmap8888 == null) {
            LogUtils.e("RGBA 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("rgbToBitmap8888 format = ${rgbToBitmap8888.config}")
        //imageView.setImageBitmap(rgbToBitmap8888)

        /****************************************************************************************/
        val rgbToBitmap565 = YuvUtils.rgbToBitmap565(i420ToRgb, width, height)
        if (rgbToBitmap565 == null) {
            LogUtils.e("RGBA 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("rgbToBitmap565 format = ${rgbToBitmap565.config}")
        //imageView.setImageBitmap(rgbToBitmap565)
    }

    private fun nv21Convert(bitmap: Bitmap, width: Int, height: Int) {
        val bitmapToNV21 = YuvUtils.bitmapToNV21(bitmap)
        if (bitmapToNV21 == null) {
            LogUtils.e("Bitmap 转 NV21 失败")
            return
        }

        /****************************************************************************************/
        val nv21ToBitmap565 = YuvUtils.nv21ToBitmap565(bitmapToNV21, width, height)
        if (nv21ToBitmap565 == null) {
            LogUtils.e("NV21 转 Bitmap565 失败")
            return
        }
        LogUtils.w("nv21ToBitmap565 format = " + nv21ToBitmap565.config)
        //imageView.setImageBitmap(nv21ToBitmap565)

        /****************************************************************************************/
        val nv21ToBitmap8888 = YuvUtils.nv21ToBitmap8888(bitmapToNV21, width, height)
        if (nv21ToBitmap8888 == null) {
            LogUtils.e("NV21 转 Bitmap8888 失败")
            return
        }
        LogUtils.w("nv21ToBitmap8888 format = " + nv21ToBitmap8888.config)
        //imageView.setImageBitmap(nv21ToBitmap8888)

        /****************************************************************************************/
        val nv21ToI420 = YuvUtils.nv21ToI420(bitmapToNV21, width, height)
        if (nv21ToI420 == null) {
            LogUtils.e("NV21 转 I420 失败")
            return
        }

        /****************************************************************************************/
        val i420ToBitmap8888 = YuvUtils.i420ToBitmap8888(nv21ToI420, width, height)
        if (i420ToBitmap8888 == null) {
            LogUtils.e("I420 转 Bitmap8888 失败")
            return
        }
        LogUtils.w("i420ToBitmap8888 format = " + i420ToBitmap8888.config)
        //imageView.setImageBitmap(i420ToBitmap8888)

        /****************************************************************************************/
        val i420ToBitmap565 = YuvUtils.i420ToBitmap565(nv21ToI420, width, height)
        if (i420ToBitmap565 == null) {
            LogUtils.e("I420 转 Bitmap565 失败")
            return
        }
        LogUtils.w("i420ToBitmap565 format = " + i420ToBitmap565.config)
        //imageView.setImageBitmap(i420ToBitmap565)

        /****************************************************************************************/
        val nv21ToRgb = YuvUtils.nv21ToRgb(bitmapToNV21, width, height)
        if (nv21ToRgb == null) {
            LogUtils.e("NV21 转 RGB 失败")
            return
        }

        /****************************************************************************************/
        val rgbToBitmap565 = YuvUtils.rgbToBitmap565(nv21ToRgb, width, height)
        if (rgbToBitmap565 == null) {
            LogUtils.e("RGB 转 Bitmap565 失败")
            return
        }
        LogUtils.d("rgbToBitmap565 format = " + rgbToBitmap565.config)
        // imageView.setImageBitmap(rgbToBitmap565)

        /****************************************************************************************/
        val rgbToBitmap8888 = YuvUtils.rgbToBitmap8888(nv21ToRgb, width, height)
        if (rgbToBitmap8888 == null) {
            LogUtils.e("RGB 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("rgbToBitmap8888 format = " + rgbToBitmap8888.config)
        //  imageView.setImageBitmap(rgbToBitmap8888)

        /****************************************************************************************/
        val nv21ToRgba = YuvUtils.nv21ToRgba(bitmapToNV21, width, height)
        if (nv21ToRgba == null) {
            LogUtils.e("NV21 转 RGBA 失败")
            return
        }

        /****************************************************************************************/
        val rgbaToBitmap8888 = YuvUtils.rgbaToBitmap8888(nv21ToRgba, width, height)
        if (rgbaToBitmap8888 == null) {
            LogUtils.e("RGBA 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("rgbaToBitmap8888 format = " + rgbaToBitmap8888.config)
        // imageView.setImageBitmap(rgbaToBitmap8888)

        /****************************************************************************************/
        val rgbaToBitmap565 = YuvUtils.rgbaToBitmap565(nv21ToRgba, width, height)
        if (rgbaToBitmap565 == null) {
            LogUtils.e("RGBA 转 Bitmap8888 失败")
            return
        }
        LogUtils.d("rgbaToBitmap565 format = " + rgbaToBitmap565.config)
        //imageView.setImageBitmap(rgbaToBitmap565)
    }

    override fun onResume() {
        super.onResume()


    }
}
