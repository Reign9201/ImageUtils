//
// Created by XuYanjun on 2019/11/20.
//
#include "../head/ColorConvert.hpp"

int NV21ToRGBA(uint8 *src_nv21_data, int width, int height, uint8 *dst_rgba) {

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

int NV21ToRGB(uint8 *src_nv21_data, int width, int height, uint8 *dst_rgb) {

    return libyuv::NV21ToRGB565(src_nv21_data, width,
                                src_nv21_data + width * height, width,
                                dst_rgb, width * 2,
                                width, height);
}

int NV21Rotate(uint8 *src_nv21_data, int width, int height, uint8 *dst_nv21_rotate,
               RotateAngle rotateAngle) {

    //libyuv::RotateUV90()


    return 0;
}

int NV21ToI420(uint8 *src_nv21_data, int width, int height, uint8 *dst_i420) {
    return libyuv::NV21ToI420(src_nv21_data, width,
                              src_nv21_data + width * height, width,
                              dst_i420, width,
                              dst_i420 + width * height, width >> 1,
                              dst_i420 + width * height + (width >> 1) * (height >> 1), width >> 1,
                              width, height);
    // return 0;
}

int I420ToRGBA(uint8 *src_i420_data, int width, int height, uint8 *dst_rgba_data) {
    return libyuv::I420ToABGR(src_i420_data, width,
                              src_i420_data + width * height, width >> 1,
                              src_i420_data + width * height + (width >> 1) * (height >> 1),
                              width >> 1,
                              dst_rgba_data, width * 4,
                              width, height);
    //return 0;
}

int I420ToRGB(uint8 *src_i420_data, int width, int height, uint8 *dst_rgb_data) {
    return libyuv::I420ToRGB565(src_i420_data, width,
                              src_i420_data + width * height, width >> 1,
                              src_i420_data + width * height + (width >> 1) * (height >> 1),
                              width >> 1,
                              dst_rgb_data, width * 2,
                              width, height);
    //return 0;
}

int I420ToNV21(uint8 *src_i420_data, int width, int height, uint8 *dst_nv21_data) {

    return libyuv::I420ToNV21(src_i420_data, width,
                       src_i420_data + width * height, width >> 1,
                       src_i420_data + width * height + (width >> 1) * (height >> 1), width >> 1,
                       dst_nv21_data, width,
                       dst_nv21_data + width * height, width,
                       width, height);

}

