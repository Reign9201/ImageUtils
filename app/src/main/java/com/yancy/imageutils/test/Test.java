package com.yancy.imageutils.test;

import android.content.Context;
import android.graphics.Bitmap;
import android.renderscript.Allocation;
import android.renderscript.Element;
import android.renderscript.RenderScript;
import android.renderscript.ScriptIntrinsicYuvToRGB;
import android.renderscript.Type;


/**
 * 说明：
 *
 * @author Yancy
 * @date 2019/11/11
 */
public class Test {

    public static void main(String[] args) {
        Bitmap bitmap = Bitmap.createBitmap(1,1,Bitmap.Config.ARGB_8888);


    }

    public static Bitmap nv21BytesToBitmap(Context context, byte[] data, int width, int height) {
        if (data.length != height * 3 / 2 * width) {
            return null;
        }
        RenderScript rs = RenderScript.create(context);
        ScriptIntrinsicYuvToRGB yuvToRgbIntrinsic = ScriptIntrinsicYuvToRGB.create(rs,
                Element.U8_4(rs));
        Type.Builder yuvBuilder = new Type.Builder(rs, Element.U8(rs)).setX(data.length);
        Type t1 = yuvBuilder.create();
        Allocation in = Allocation.createTyped(rs, t1, Allocation.USAGE_SCRIPT);
        Type.Builder rgbaBuilder = new Type.Builder(rs, Element.RGBA_8888(rs)).setX(width)
                .setY(height);
        Type t2 = rgbaBuilder.create();
        Allocation out = Allocation.createTyped(rs, t2, Allocation.USAGE_SCRIPT);
        in.copyFrom(data);
        yuvToRgbIntrinsic.setInput(in);
        yuvToRgbIntrinsic.forEach(out);
        Bitmap bmpout = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        out.copyTo(bmpout);
        rs.destroy();
        yuvToRgbIntrinsic.destroy();
        t1.destroy();
        t2.destroy();
        in.destroy();
        out.destroy();

        return bmpout;
    }
}
