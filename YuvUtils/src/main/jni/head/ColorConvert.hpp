//
// Created by XuYanjun on 2019/11/20.
//

#ifndef IMAGEUTILS_COLORCONVERT_HPP
#define IMAGEUTILS_COLORCONVERT_HPP

#include <libyuv.h>

enum RotateAngle {
    Rotate_90 = 90,
    Rotate_180 = 180,
    Rotate_270 = 270,
    Rotate_90_Negative = -90
};

int NV21ToRGBA(const uint8 *src_nv21_data, int width, int height, uint8 *dst_rgba);

int NV21ToRGB565(const uint8 *src_nv21_data, int width, int height, uint8 *dst_rgba);

int NV21ToI420(const uint8 *src_nv21_data, int width, int height, uint8 *dst_I420);

///////////////////////////////////////////////////////////////////////////////////

int I420ToRGBA(const uint8 *src_i420_data, int width, int height, uint8 *dst_rgba_data);

int I420ToRGB565(const uint8 *src_i420_data, int width, int height, uint8 *dst_rgb_data);

int I420ToNV21(const uint8 *src_i420_data, int width, int height, uint8 *dst_nv21_data);

///////////////////////////////////////////////////////////////////////////////////

int RGBAToNV21(const uint8 *src_rgba_data, int width, int height, uint8 *dst_nv21_data);

int RGBAToI420(const uint8 *src_rgba_data, int width, int height, uint8 *dst_i420_data);

int RGBAToRGB565(const uint8 *src_rgba_data, int width, int height, uint8 *dst_rgb_data);

///////////////////////////////////////////////////////////////////////////////////

int RGB565ToNV21(const uint8 *src_rgb_data, int width, int height, uint8 *dst_nv21_data);

int RGB565ToI420(const uint8 *src_rgb_data, int width, int height, uint8 *dst_i420_data);

int RGB565ToRGBA(const uint8 *src_rgb_data, int width, int height, uint8 *dst_rgba_data);


int NV21Rotate(const uint8 *src_nv21_data, int width, int height, uint8 *dst_nv21_rotate,
               RotateAngle rotateAngle);

#endif //IMAGEUTILS_COLORCONVERT_HPP
