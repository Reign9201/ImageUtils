package com.yancy.imageutils

import android.Manifest
import android.content.res.Resources
import android.graphics.*
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
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



    }
}
