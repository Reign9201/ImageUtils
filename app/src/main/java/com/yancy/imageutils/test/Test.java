package com.yancy.imageutils.test;

import android.content.Context;
import android.graphics.Bitmap;
import android.renderscript.Allocation;
import android.renderscript.Element;
import android.renderscript.RenderScript;
import android.renderscript.ScriptIntrinsicYuvToRGB;
import android.renderscript.Type;
import android.text.TextUtils;

import com.yancy.yuvutils.ImageUtils;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;


/**
 * 说明：
 *
 * @author Yancy
 * @date 2019/11/11
 */
public class Test {

    public static String convert(byte data){
        return Integer.toHexString(data & 0xff);
    }


    public static String convert01(int data) {
        return Integer.toHexString(data);
    }
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

    public static void saveBitmapToPNG(Bitmap bitmap, String imagePath, String imageName) {
        if (TextUtils.isEmpty(imageName)) {
            return;
        }
        String png = ".png";
        String fileName = imageName.toLowerCase().endsWith(png) ? imageName : imageName + png;
        saveBitmapToLocal(bitmap, imagePath, fileName, Bitmap.CompressFormat.PNG);
    }

    /**
     * 保存图片到本地
     *
     * @param bitmap    图像源bitmap
     * @param imagePath 保存图片的路径
     * @param imageName 保存图片的名称
     * @param format    保存文件的格式{@link Bitmap.CompressFormat}
     */
    public static void saveBitmapToLocal(Bitmap bitmap, String imagePath, String imageName, Bitmap.CompressFormat format) {
        if (bitmap == null || TextUtils.isEmpty(imagePath) || TextUtils.isEmpty(imageName)) {
            return;
        }
        File dir = new File(imagePath);
        if (!dir.exists()) {
            dir.mkdirs();
        }
        byte[] bytes = bitmap2Bytes(bitmap, format);
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(new File(dir, imageName));
            fos.write(bytes);
            fos.flush();
        } catch (IOException ignore) {

        } finally {
            if (fos != null) {
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static byte[] bitmap2Bytes(final Bitmap bitmap, final Bitmap.CompressFormat format) {
        if (bitmap == null) {
            return null;
        }
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bitmap.compress(format, 100, baos);
        return baos.toByteArray();
    }
}
