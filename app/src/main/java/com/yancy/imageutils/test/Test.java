package com.yancy.imageutils.test;

import android.graphics.Bitmap;

import com.yancy.imageconvertutils.ImageConvertUtils;

/**
 * 说明：
 *
 * @author Yancy
 * @date 2019/11/11
 */
public class Test {

    public static void main(String[] args) {
        Bitmap bitmap = Bitmap.createBitmap(1,1,Bitmap.Config.ARGB_8888);

        Boolean s = ImageConvertUtils.saveBitmap2Local(bitmap,",","1");

    }
}
