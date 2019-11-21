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

int NV21ToRGBA(uint8 *src_nv21_data, int width, int height, uint8 *dst_rgba);

int NV21ToRGB(uint8 *src_nv21_data, int width, int height, uint8 *dst_rgba);

int NV21ToI420(uint8 *src_nv21_data, int width, int height, uint8 *dst_I420);


int I420ToRGBA(uint8*src_i420_data, int width,int height, uint8 *dst_rgba_data);

int I420ToRGB(uint8*src_i420_data, int width,int height, uint8 *dst_rgb_data);

int I420ToNV21(uint8*src_i420_data, int width,int height, uint8 *dst_nv21_data);







int NV21Rotate(uint8 *src_nv21_data, int width, int height, uint8 *dst_nv21_rotate,
               RotateAngle rotateAngle);

#endif //IMAGEUTILS_COLORCONVERT_HPP
