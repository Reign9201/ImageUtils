//
// Created by XuYanjun on 2019/11/20.
//

#ifndef IMAGEUTILS_COLORCONVERT_HPP
#define IMAGEUTILS_COLORCONVERT_HPP

#include <libyuv.h>
#include <vector>

namespace yancy {
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


    int NV21Rotate(const uint8 *src_nv21_data, int width, int height, uint8 *dst_nv21_rotate);

    ///////////////////////////////////////////////////////////////////////////////////

    int DataConvert(uint8 *src_data, uint8 *dst_data,int width, int height, int degree, std::vector<int> rect, int src_format, int dst_format,
                    bool priorityClip);


    int DataMirror(const uint8 *src_data, int width, int height, uint8 **dst_data, int src_format,
                   int dst_format,
                   bool vertical_mirror = false);


    ///////////////////////////////////////////////////////////////////////////////////
    int __NV21MirrorToNV21__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __NV21MirrorToI420__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __NV21MirrorToABGR__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __NV21MirrorToRGB565__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);


    int __I420MirrorToNV21__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __I420MirrorToI420__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __I420MirrorToABGR__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __I420MirrorToRGB565__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);


    int __ABGRMirrorToNV21__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __ABGRMirrorToI420__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __ABGRMirrorToABGR__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __ABGRMirrorToRGB565__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);


    int __RGB565MirrorToNV21__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __RGB565MirrorToI420__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __RGB565MirrorToABGR__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);

    int __RGB565MirrorToRGB565__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror = false);
}


#endif //IMAGEUTILS_COLORCONVERT_HPP
