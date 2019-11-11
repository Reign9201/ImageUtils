package com.yancy.imageutils

import android.content.res.Resources
import android.graphics.*
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.yancy.imageconvertutils.ImageConvertUtils
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val bitmap = BitmapFactory.decodeResource(Resources.getSystem(), R.mipmap.test)
        imageView.setImageBitmap(bitmap)

        ImageConvertUtils.bitmap2Drawable(bitmap)

        val bitmap2CompressBytes = ImageConvertUtils.bitmap2CompressBytes(bitmap)


    }
}
