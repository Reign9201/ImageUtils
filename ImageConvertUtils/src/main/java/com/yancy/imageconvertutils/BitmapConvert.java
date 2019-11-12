package com.yancy.imageconvertutils;

import android.graphics.Bitmap;

/**
 * 说明：
 *
 * @author Yancy
 * @date 2018/8/28
 */
public class BitmapConvert {

    protected final static int CP_MJPEG = 0xA000;
    protected final static int CP_PNG = 0xB000;
    protected final static int CP_RGBA8888 = 1;
    protected final static int CP_RGB565 = 4;
    protected final static int CP_RGBA4444 = 7;
    protected final static int CP_PAF_NV21 = 0x802;
    protected final static int CP_PAF_NV12 = 0x801;
    protected final static int CP_PAF_YUYV = 0x501;
    protected final static int CP_PAF_I420 = 0x601;
    protected final static int CP_PAF_BGR24 = 0x201;


    private native int bitmapInit(int width, int height, int format);

    private native int bitmapConvert(Bitmap bitmap, byte[] data);

    private native int bitmapUnInit();

    public native Bitmap nv21ToARGB(byte[] nv21Data, int width, int height);

    private int handle;

    static {
        System.loadLibrary("bitmapConvert");
    }

    public BitmapConvert() {
        handle = -1;
    }

    /**
     * @param width  convert image width
     * @param height convert image height
     * @param format target to convert.
     * @return success is true.
     */
    boolean initial(int width, int height, int format) {
        handle = bitmapInit(width, height, format);
        return handle != -1;
    }

    boolean convert(Bitmap src, byte[] data) {
        return 0 == bitmapConvert(src, data);
    }

    void destroy() {
        if (handle != -1) {
            bitmapUnInit();
        }
    }


    public byte[] bitmapToNV21Bytes(Bitmap bitmap) {
        if (bitmap != null) {
            int width = bitmap.getWidth();
            int height = bitmap.getHeight();
            int length = (int) (width * height * 3.0 / 2.0);
            byte[] data = new byte[length];
            try {
                initial(width, height, BitmapConvert.CP_PAF_NV21);
                if (convert(bitmap, data)) {
                    destroy();
                    return data;
                }

            } catch (Exception ignored) {
                destroy();
            }
        }
        return null;
    }

    private  byte[] argbToNv21Bytes(int[] argb, int width, int height) {
        int frameSize = width * height;
        int yIndex = 0;
        int uvIndex = frameSize;
        int index = 0;
        byte[] nv21 = new byte[width * height * 3 / 2];
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                int R = (argb[index] & 0xFF0000) >> 16;
                int G = (argb[index] & 0x00FF00) >> 8;
                int B = argb[index] & 0x0000FF;
                int Y = (66 * R + 129 * G + 25 * B + 128 >> 8) + 16;
                int U = (-38 * R - 74 * G + 112 * B + 128 >> 8) + 128;
                int V = (112 * R - 94 * G - 18 * B + 128 >> 8) + 128;
                nv21[yIndex++] = (byte) (Y < 0 ? 0 : (Y > 255 ? 255 : Y));
                if (j % 2 == 0 && index % 2 == 0 && uvIndex < nv21.length - 2) {
                    nv21[uvIndex++] = (byte) (V < 0 ? 0 : (V > 255 ? 255 : V));
                    nv21[uvIndex++] = (byte) (U < 0 ? 0 : (U > 255 ? 255 : U));
                }

                ++index;
            }
        }
        return nv21;
    }

    public   byte[] bitmapToNv21(Bitmap src, int width, int height) {
        if (src != null && src.getWidth() >= width && src.getHeight() >=
                height) {
            int[] argb = new int[width * height];
            src.getPixels(argb, 0, width, 0, 0, width, height);
            return argbToNv21Bytes(argb, width, height);
        } else {
            return null;
        }
    }

}