package com.yancy.imageutils

import android.Manifest
import android.graphics.*
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.yancy.imageutils.test.Test
import com.yancy.yuvutils.ImageUtils
import com.yancy.yuvutils.YuvUtils
import kotlinx.android.synthetic.main.activity_main.*
import java.nio.ByteBuffer
import java.nio.IntBuffer

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        PermissionUtil.addPermission(
            this,
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.CAMERA,
            Manifest.permission.READ_PHONE_STATE
        )
            .request(this)

        val bitmap = BitmapFactory.decodeFile("/sdcard/test.png")
        val width = bitmap.width
        val height = bitmap.height
        if (bitmap == null) {
            LogUtils.e("bitmap is null.")
            return
        }
        LogUtils.d("width = $width, height = $height")

//        test()

        //rgbaConvert(bitmap, width, height)
        //rgb24Convert(bitmap, width, height)

        val rgba = ImageUtils.bitmapToRgba(bitmap)

        /*val rotateToBitmap =
            YuvUtils.dataClipRotateToBitmap(
                rgba!!, 5, width, height, 90,
                Rect(100, 0, 300, 300), 5, false
            )*/

        val dataMirror = YuvUtils.dataMirror(rgba!!, width, height, 5, 5,true)
        val bitmap8888 = ImageUtils.rgbaToBitmap8888(dataMirror!!, width, height)

        imageView.setImageBitmap(bitmap8888)
        Test.saveBitmapToPNG(bitmap8888, "sdcard/ABCD/", "" + System.nanoTime())

    }


    private fun test() {

        val bitmap = Bitmap.createBitmap(1, 1, Bitmap.Config.ARGB_8888)
        bitmap.eraseColor(Color.parseColor("#336699"))
        // imageView.setImageBitmap(bitmap)
        val rgba = IntArray(1 * 1)
        bitmap.getPixels(rgba, 0, 1, 0, 0, 1, 1)

        LogUtils.e("rgba = ${Test.convert01(rgba[0])}")
        val byteArray = ByteArray(1 * 1 * 4)
        val byteBuffer = ByteBuffer.wrap(byteArray)
        bitmap.copyPixelsToBuffer(byteBuffer)

        LogUtils.e(Test.convert(byteArray[0]))
        LogUtils.e(Test.convert(byteArray[1]))
        LogUtils.e(Test.convert(byteArray[2]))
        LogUtils.e(Test.convert(byteArray[3]))
    }


    private fun rgb24Convert(bitmap: Bitmap, width: Int, height: Int) {

        ImageUtils.apply {
            val rgb24Bytes = bitmapToRgb24(bitmap)
            //val rgb24Clip = rgb24Clip(rgb24Bytes!!, width, height, Rect(100, 100, 300, 300))
            //imageView.setImageBitmap(rgb24ToBitmap8888(rgb24Clip!!,200,200))

            val rgb24Scale = rgb24Scale(rgb24Bytes!!, width, height, 800, 800)
            imageView.setImageBitmap(rgb24ToBitmap8888(rgb24Scale!!, 800, 800))

            imageView.setImageBitmap(rgb24ToBitmap565(rgb24Rotate(rgb24Bytes, width, height, 90)!!, height, width))

            imageView.setImageBitmap(rgb24ToBitmap565(rgb24Mirror(rgb24Bytes, width, height)!!, width, height))

            imageView.setImageBitmap(i420ToBitmap8888(rgb24ToI420(rgb24Bytes, width, height)!!, width, height))
            imageView.setImageBitmap(nv21ToBitmap8888(rgb24ToNV21(rgb24Bytes, width, height)!!, width, height))
            imageView.setImageBitmap(rgbaToBitmap8888(rgb24ToRgba(rgb24Bytes, width, height)!!, width, height))
            imageView.setImageBitmap(rgb565ToBitmap8888(rgb24ToRgb565(rgb24Bytes, width, height)!!, width, height))
        }


    }


    private fun rgbaConvert(bitmap: Bitmap, width: Int, height: Int) {
        //提取Bitmap数据
        val rgbaBytes = ByteArray(width * height * 4)
        val dst = ByteBuffer.wrap(rgbaBytes)
        bitmap.copyPixelsToBuffer(dst)

        ImageUtils.apply {
            //imageView.setImageBitmap(rgbaToBitmap8888(rgbaBytes,width,height))
            //imageView.setImageBitmap(rgbaToBitmap565(rgbaBytes,width,height))

            val i420Bytes = rgbaToI420(rgbaBytes, width, height)
            //imageView.setImageBitmap(i420ToBitmap8888(i420Bytes!!,width,height))
            //imageView.setImageBitmap(i420ToBitmap565(i420Bytes!!,width,height))

            val nv21Bytes = rgbaToNV21(rgbaBytes, width, height)
            //imageView.setImageBitmap(nv21ToBitmap8888(nv21Bytes!!,width,height))
            //imageView.setImageBitmap(nv21ToBitmap565(nv21Bytes!!,width,height))

            val rgb24Bytes = rgbaToRgb24(rgbaBytes, width, height)
            //imageView.setImageBitmap(rgb24ToBitmap8888(rgb24Bytes!!,width,height))
            //imageView.setImageBitmap(rgb24ToBitmap565(rgb24Bytes!!,width,height))

            val rgb565Bytes = rgbaToRgb565(rgbaBytes, width, height)
            //imageView.setImageBitmap(rgb565ToBitmap8888(rgb565Bytes!!,width,height))
            imageView.setImageBitmap(rgb565ToBitmap565(rgb565Bytes!!, width, height))
        }


    }

}
