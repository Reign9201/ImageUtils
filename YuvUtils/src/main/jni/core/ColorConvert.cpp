//
// Created by XuYanjun on 2019/11/20.
//
#include "../head/ColorConvert.hpp"
#include "../logger.hpp"

int NV21ToRGBA(const uint8 *src_nv21_data, int width, int height, uint8 *dst_rgba) {

    int res = libyuv::NV21ToARGB(src_nv21_data, width,
                                 src_nv21_data + width * height, width,
                                 dst_rgba, width * 4,
                                 width, height);

    //logger::error("res--->", res);
    if (res != 0) { return -1; }

    // 实测，libyuv中的ABGR格式对应Android Bitmap中的ARGB_8888
    res = libyuv::ARGBToABGR(dst_rgba, width * 4, dst_rgba, width * 4, width, height);

    return res;
}

int NV21ToRGB565(const uint8 *src_nv21_data, int width, int height, uint8 *dst_rgb) {

    return libyuv::NV21ToRGB565(src_nv21_data, width,
                                src_nv21_data + width * height, width,
                                dst_rgb, width * 2,
                                width, height);
}

int NV21Rotate(const uint8 *src_nv21_data, int width, int height, uint8 *dst_nv21_rotate,
               RotateAngle rotateAngle) {

    //libyuv::RotateUV90()


    return 0;
}

int NV21ToI420(const uint8 *src_nv21_data, int width, int height, uint8 *dst_i420) {
    return libyuv::NV21ToI420(src_nv21_data, width,
                              src_nv21_data + width * height, width,
                              dst_i420, width,
                              dst_i420 + width * height, width >> 1,
                              dst_i420 + width * height + (width >> 1) * (height >> 1), width >> 1,
                              width, height);
    // return 0;
}

int I420ToRGBA(const uint8 *src_i420_data, int width, int height, uint8 *dst_rgba_data) {
    return libyuv::I420ToABGR(src_i420_data, width,
                              src_i420_data + width * height, width >> 1,
                              src_i420_data + width * height + (width >> 1) * (height >> 1),
                              width >> 1,
                              dst_rgba_data, width * 4,
                              width, height);
    //return 0;
}

int I420ToRGB565(const uint8 *src_i420_data, int width, int height, uint8 *dst_rgb_data) {
    return libyuv::I420ToRGB565(src_i420_data, width,
                                src_i420_data + width * height, width >> 1,
                                src_i420_data + width * height + (width >> 1) * (height >> 1),
                                width >> 1,
                                dst_rgb_data, width * 2,
                                width, height);

    //return 0;
}

int I420ToNV21(const uint8 *src_i420_data, int width, int height, uint8 *dst_nv21_data) {

    return libyuv::I420ToNV21(src_i420_data, width,
                              src_i420_data + width * height, width >> 1,
                              src_i420_data + width * height + (width >> 1) * (height >> 1),
                              width >> 1,
                              dst_nv21_data, width,
                              dst_nv21_data + width * height, width,
                              width, height);

}

int RGBAToNV21(const uint8 *src_rgba_data, int width, int height, uint8 *dst_nv21_data) {
    uint8 *argb = new uint8[width * height * 4];

    if (libyuv::ABGRToARGB(src_rgba_data, width * 4,
                           argb, width * 4,
                           width, height) != 0) {
        delete[] argb;
        return -1;
    }

    int res =  libyuv::ARGBToNV21(argb, width * 4,
                              dst_nv21_data, width,
                              dst_nv21_data + width * height, width,
                              width, height);
    delete[] argb;
    return res;
}

int RGBAToI420(const uint8 *src_rgba_data, int width, int height, uint8 *dst_i420_data) {
    /*if (libyuv::ABGRToI420(src_rgba_data, width * 4,
                           dst_i420_data, width,
                           dst_i420_data + width * height, width >> 1,
                           dst_i420_data + width * height + (width >> 1) * (height >> 1),
                           width >> 1,
                           width, height) != 0) {
        return -1;
    }*/
    return libyuv::ABGRToI420(src_rgba_data, width * 4,
                              dst_i420_data, width,
                              dst_i420_data + width * height, width >> 1,
                              dst_i420_data + width * height + (width >> 1) * (height >> 1),
                              width >> 1,
                              width, height);

}

int RGBAToRGB565(const uint8 *src_rgba_data, int width, int height, uint8 *dst_rgb_data) {
    uint8 *argb = new uint8[width * height * 4];
    if (libyuv::ABGRToARGB(src_rgba_data, width * 4,
                           argb, width * 4,
                           width, height) != 0) {
        delete[] argb;
        return -1;
    }
    int res =  libyuv::ARGBToRGB565(argb, width * 4,
                                dst_rgb_data, width * 2,
                                width, height);
    delete[] argb;
    return res;

}

int RGB565ToNV21(const uint8 *src_rgb_data, int width, int height, uint8 *dst_nv21_data) {

    if (libyuv::RGB565ToI420(src_rgb_data, width * 2,
                             dst_nv21_data, width,
                             dst_nv21_data + width * height, width >> 1,
                             dst_nv21_data + width * height + (width >> 1) * (height >> 1),
                             width >> 1,
                             width, height) != 0) {
        return -1;
    }

    return I420ToNV21(dst_nv21_data, width, height, dst_nv21_data);
}

int RGB565ToI420(const uint8 *src_rgb_data, int width, int height, uint8 *dst_i420_data) {
    return libyuv::RGB565ToI420(src_rgb_data, width * 2,
                                dst_i420_data, width,
                                dst_i420_data + width * height, width >> 1,
                                dst_i420_data + width * height + (width >> 1) * (height >> 1),
                                width >> 1,
                                width, height);
}

int RGB565ToRGBA(const uint8 *src_rgb_data, int width, int height, uint8 *dst_rgba_data) {
    if (libyuv::RGB565ToARGB(src_rgb_data, width * 2, dst_rgba_data, width * 4, width, height) !=
        0) { return -1; }
    return libyuv::ARGBToABGR(dst_rgba_data, width * 4, dst_rgba_data, width * 4, width, height);
}

