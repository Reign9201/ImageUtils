//
// Created by XuYanjun on 2019/11/20.
//
#include "../head/ColorConvert.hpp"
#include "../logger.hpp"

int yancy::NV21ToRGBA(const uint8 *src_nv21_data, int width, int height, uint8 *dst_rgba) {

    int res = libyuv::NV21ToARGB(src_nv21_data, width,
                                 src_nv21_data + width * height, width,
                                 dst_rgba, width * 4,
                                 width, height);

    if (res != 0) { return -1; }

    // 实测，libyuv中的ABGR格式对应Android Bitmap中的ARGB_8888
    res = libyuv::ARGBToABGR(dst_rgba, width * 4, dst_rgba, width * 4, width, height);

    return res;
}

int yancy::NV21ToRGB565(const uint8 *src_nv21_data, int width, int height, uint8 *dst_rgb) {

    return libyuv::NV21ToRGB565(src_nv21_data, width,
                                src_nv21_data + width * height, width,
                                dst_rgb, width * 2,
                                width, height);
}

int yancy::NV21Rotate(const uint8 *src_nv21_data, int width, int height, uint8 *dst_nv21_rotate) {

    //libyuv::RotateUV90()


    return 0;
}

int yancy::NV21ToI420(const uint8 *src_nv21_data, int width, int height, uint8 *dst_i420) {
    return libyuv::NV21ToI420(src_nv21_data, width,
                              src_nv21_data + width * height, width,
                              dst_i420, width,
                              dst_i420 + width * height, width >> 1,
                              dst_i420 + width * height + (width >> 1) * (height >> 1), width >> 1,
                              width, height);
    // return 0;
}

int yancy::I420ToRGBA(const uint8 *src_i420_data, int width, int height, uint8 *dst_rgba_data) {
    return libyuv::I420ToABGR(src_i420_data, width,
                              src_i420_data + width * height, width >> 1,
                              src_i420_data + width * height + (width >> 1) * (height >> 1), width >> 1,
                              dst_rgba_data, width * 4,
                              width, height);
    //return 0;
}

int yancy::I420ToRGB565(const uint8 *src_i420_data, int width, int height, uint8 *dst_rgb_data) {
    return libyuv::I420ToRGB565(src_i420_data, width,
                                src_i420_data + width * height, width >> 1,
                                src_i420_data + width * height + (width >> 1) * (height >> 1), width >> 1,
                                dst_rgb_data, width * 2,
                                width, height);

    //return 0;
}

int yancy::I420ToNV21(const uint8 *src_i420_data, int width, int height, uint8 *dst_nv21_data) {

    return libyuv::I420ToNV21(src_i420_data, width,
                              src_i420_data + width * height, width >> 1,
                              src_i420_data + width * height + (width >> 1) * (height >> 1), width >> 1,
                              dst_nv21_data, width,
                              dst_nv21_data + width * height, width,
                              width, height);

}

int yancy::RGBAToNV21(const uint8 *src_rgba_data, int width, int height, uint8 *dst_nv21_data) {
    uint8 *argb = new uint8[width * height * 4];

    if (libyuv::ABGRToARGB(src_rgba_data, width * 4,
                           argb, width * 4,
                           width, height) != 0) {
        delete[] argb;
        return -1;
    }

    int res = libyuv::ARGBToNV21(argb, width * 4,
                                 dst_nv21_data, width,
                                 dst_nv21_data + width * height, width,
                                 width, height);
    delete[] argb;
    return res;
}

int yancy::RGBAToI420(const uint8 *src_rgba_data, int width, int height, uint8 *dst_i420_data) {
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

int yancy::RGBAToRGB565(const uint8 *src_rgba_data, int width, int height, uint8 *dst_rgb_data) {
    uint8 *argb = new uint8[width * height * 4];
    if (libyuv::ABGRToARGB(src_rgba_data, width * 4,
                           argb, width * 4,
                           width, height) != 0) {
        delete[] argb;
        return -1;
    }
    int res = libyuv::ARGBToRGB565(argb, width * 4,
                                   dst_rgb_data, width * 2,
                                   width, height);
    delete[] argb;
    return res;

}

int yancy::RGB565ToNV21(const uint8 *src_rgb_data, int width, int height, uint8 *dst_nv21_data) {

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

int yancy::RGB565ToI420(const uint8 *src_rgb_data, int width, int height, uint8 *dst_i420_data) {
    return libyuv::RGB565ToI420(src_rgb_data, width * 2,
                                dst_i420_data, width,
                                dst_i420_data + width * height, width >> 1,
                                dst_i420_data + width * height + (width >> 1) * (height >> 1),
                                width >> 1,
                                width, height);
}

int yancy::RGB565ToRGBA(const uint8 *src_rgb_data, int width, int height, uint8 *dst_rgba_data) {
    if (libyuv::RGB565ToARGB(src_rgb_data, width * 2, dst_rgba_data, width * 4, width, height) !=
        0) { return -1; }
    return libyuv::ARGBToABGR(dst_rgba_data, width * 4, dst_rgba_data, width * 4, width, height);
}

int
yancy::DataMirror(const uint8 *src_data, int width, int height, uint8 **dst_data, int src_format,
                  int dst_format, bool vertical_mirror) {

    int resCode = -1;

    switch (src_format) {
        case libyuv::FOURCC_NV21:
            switch (dst_format) {
                case libyuv::FOURCC_NV21:
                    resCode = __NV21MirrorToNV21__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_I420:
                    resCode = __NV21MirrorToI420__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_ABGR:
                    resCode = __NV21MirrorToABGR__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_RGBP:
                    resCode = __NV21MirrorToRGB565__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                default:
                    break;
            }
            break;
        case libyuv::FOURCC_I420:
            switch (dst_format) {
                case libyuv::FOURCC_NV21:
                    resCode = __I420MirrorToNV21__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_I420:
                    resCode = __I420MirrorToI420__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_ABGR:
                    resCode = __I420MirrorToABGR__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_RGBP:
                    resCode = __I420MirrorToRGB565__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                default:
                    break;
            }
            break;
        case libyuv::FOURCC_ABGR:
            switch (dst_format) {
                case libyuv::FOURCC_NV21:
                    resCode = __ABGRMirrorToNV21__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_I420:
                    resCode = __ABGRMirrorToI420__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_ABGR:
                    resCode = __ABGRMirrorToABGR__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_RGBP:
                    resCode = __ABGRMirrorToRGB565__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                default:
                    break;
            }
            break;
        case libyuv::FOURCC_RGBP:
            switch (dst_format) {
                case libyuv::FOURCC_NV21:
                    resCode = __RGB565MirrorToNV21__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_I420:
                    resCode = __RGB565MirrorToI420__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_ABGR:
                    resCode = __RGB565MirrorToABGR__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                case libyuv::FOURCC_RGBP:
                    resCode = __RGB565MirrorToRGB565__(src_data, dst_data, width, height, vertical_mirror);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    return resCode;
}

int yancy::__NV21MirrorToNV21__(const uint8 *src_data, uint8 **dst_data, int width, int height,
                                bool vertical_mirror) {

    uint8 *src_data_i420 = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    uint8 *src_data_i420_mirror = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];


    if (NV21ToI420(src_data, width, height, src_data_i420) != 0) {
        delete[] src_data_i420;
        delete[] src_data_i420_mirror;
        return -1;
    }
    if (libyuv::I420Mirror(src_data_i420, width,
                           src_data_i420 + width * height, width >> 1,
                           src_data_i420 + width * height + (width >> 1) * (height >> 1), width >> 1,
                           src_data_i420_mirror, width,
                           src_data_i420_mirror + width * height, width >> 1,
                           src_data_i420_mirror + width * height + (width >> 1) * (height >> 1), width >> 1,
                           width, vertical_mirror ? -height : height) != 0) {
        delete[] src_data_i420;
        delete[] src_data_i420_mirror;
        return -1;
    }
    int code = I420ToNV21(src_data_i420_mirror, width, height, *dst_data);
    delete[] src_data_i420;
    delete[] src_data_i420_mirror;
    return code;
}

int yancy::__NV21MirrorToI420__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *src_data_i420 = new uint8[width * height +
                                     ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (NV21ToI420(src_data, width, height, src_data_i420) != 0) {
        delete[] src_data_i420;
        return -1;
    }
    int resCode = libyuv::I420Mirror(src_data_i420, width,
                                     src_data_i420 + width * height, width >> 1,
                                     src_data_i420 + width * height + (width >> 1) * (height >> 1), width >> 1,
                                     *dst_data, width,
                                     *dst_data + width * height, width >> 1,
                                     *dst_data + width * height + (width >> 1) * (height >> 1), width >> 1,
                                     width, vertical_mirror ? -height : height);
    delete[] src_data_i420;
    return resCode;

}

int yancy::__NV21MirrorToABGR__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {

    if (libyuv::NV21ToARGB(src_data, width,
                           src_data + width * height, width,
                           *dst_data, width * 4,
                           width, vertical_mirror ? -height : height) != 0) {
        return -1;
    }
    uint8 *src_argb = new uint8[width * height * 4];
    if (libyuv::ARGBMirror(*dst_data, width * 4,
                           src_argb, width * 4,
                           width, height) != 0) {
        delete[] src_argb;
        return -1;
    }

    int resCode = libyuv::ARGBToABGR(src_argb, width * 4, *dst_data, width * 4, width, height);
    delete[] src_argb;
    return resCode;
}

int yancy::__NV21MirrorToRGB565__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *src_data_i420 = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (__NV21MirrorToI420__(src_data, &src_data_i420, width, height, vertical_mirror) != 0) {
        delete[] src_data_i420;
        return -1;
    }
    int resCode = I420ToRGB565(src_data_i420, width, height, *dst_data);
    delete[] src_data_i420;
    return resCode;
}

int yancy::__I420MirrorToNV21__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data_mirror = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (__I420MirrorToI420__(src_data, &i420_data_mirror, width, height, vertical_mirror) != 0) {
        delete[] i420_data_mirror;
        return -1;
    }
    int resCode = I420ToNV21(i420_data_mirror, width, height, *dst_data);
    delete[] i420_data_mirror;
    return resCode;
}

int yancy::__I420MirrorToI420__(const uint8 *src_data, uint8 **dst_data, int width, int height,
                                bool vertical_mirror) {
    return libyuv::I420Mirror(src_data, width,
                              src_data + width * height, width >> 1,
                              src_data + width * height + (width >> 1) * (height >> 1), width >> 1,
                              *dst_data, width,
                              *dst_data + width * height, width >> 1,
                              *dst_data + width * height + (width >> 1) * (height >> 1), width >> 1,
                              width, vertical_mirror ? -height : height);
}

int yancy::__I420MirrorToABGR__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data_mirror = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (__I420MirrorToI420__(src_data, &i420_data_mirror, width, height, vertical_mirror) != 0) {
        delete[] i420_data_mirror;
        return -1;
    }
    int resCode = I420ToRGBA(i420_data_mirror, width, height, *dst_data);
    delete[] i420_data_mirror;
    return resCode;
}

int yancy::__I420MirrorToRGB565__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data_mirror = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (__I420MirrorToI420__(src_data, &i420_data_mirror, width, height, vertical_mirror) != 0) {
        delete[] i420_data_mirror;
        return -1;
    }
    int resCode = I420ToRGB565(i420_data_mirror, width, height, *dst_data);
    delete[] i420_data_mirror;
    return resCode;
}

int yancy::__ABGRMirrorToNV21__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (RGBAToI420(src_data, width, height, i420_data) != 0) {
        delete[] i420_data;
        return -1;
    }

    int resCode = __I420MirrorToNV21__(i420_data, dst_data, width, height, vertical_mirror);
    delete[] i420_data;
    return resCode;
}

int yancy::__ABGRMirrorToI420__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (RGBAToI420(src_data, width, height, i420_data) != 0) {
        delete[] i420_data;
        return -1;
    }

    int resCode = __I420MirrorToI420__(i420_data, dst_data, width, height, vertical_mirror);
    delete[] i420_data;
    return resCode;
}

int yancy::__ABGRMirrorToABGR__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    if (libyuv::ABGRToARGB(src_data, width * 4, *dst_data, width * 4, width, height) != 0) {
        return -1;
    }
    uint8 *argb_data = new uint8[width * height * 4];
    if (libyuv::ARGBMirror(*dst_data, width * 4,
                           argb_data, width * 4,
                           width, vertical_mirror ? -height : height) != 0) {
        delete[] argb_data;
        return -1;
    }

    int resCode = libyuv::ARGBToABGR(argb_data, width * 4, *dst_data, width * 4, width, height);
    delete[] argb_data;
    return resCode;
}

int yancy::__ABGRMirrorToRGB565__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (RGBAToI420(src_data, width, height, i420_data) != 0) {
        delete[] i420_data;
        return -1;
    }
    int resCode = __I420MirrorToRGB565__(i420_data, dst_data, width, height, vertical_mirror);
    delete[] i420_data;

    return resCode;
}

int yancy::__RGB565MirrorToNV21__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (RGB565ToI420(src_data, width, height, i420_data) != 0) {
        delete[] i420_data;
        return -1;
    }
    int resCode = __I420MirrorToNV21__(i420_data, dst_data, width, height, vertical_mirror);
    delete[] i420_data;
    return resCode;
}

int yancy::__RGB565MirrorToI420__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (RGB565ToI420(src_data, width, height, i420_data) != 0) {
        delete[] i420_data;
        return -1;
    }
    int resCode = __I420MirrorToI420__(i420_data, dst_data, width, height, vertical_mirror);
    delete[] i420_data;
    return resCode;
}

int yancy::__RGB565MirrorToABGR__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (RGB565ToI420(src_data, width, height, i420_data) != 0) {
        delete[] i420_data;
        return -1;
    }
    int resCode = __I420MirrorToABGR__(i420_data, dst_data, width, height, vertical_mirror);
    delete[] i420_data;
    return resCode;
}

int yancy::__RGB565MirrorToRGB565__(const uint8 *src_data, uint8 **dst_data, int width, int height, bool vertical_mirror) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (RGB565ToI420(src_data, width, height, i420_data) != 0) {
        delete[] i420_data;
        return -1;
    }
    int resCode = __I420MirrorToRGB565__(i420_data, dst_data, width, height, vertical_mirror);
    delete[] i420_data;
    return resCode;
}

int yancy::DataConvert(uint8 *src_data, uint8 *dst_data, int width, int height, int degree, std::vector<int> rect, int src_format,
                       int dst_format,
                       bool priorityClip) {
    int dataSize;
    uint32 format;
    libyuv::RotationMode mode;
    switch (degree) {
        case 0:
            mode = libyuv::kRotate0;
            break;
        case 90:
            mode = libyuv::kRotate90;
            break;
        case 180:
            mode = libyuv::kRotate180;
            break;
        case -90:
        case 270:
            mode = libyuv::kRotate270;
            break;
        default:
            logger::error("degree value error, please check it.");
            return -1;
    }
    switch (src_format) {
        case 1:
            format = libyuv::FOURCC_NV21;
            dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            break;
        case 2:
            format = libyuv::FOURCC_I420;
            dataSize = width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
            break;
        case 3:
            format = libyuv::FOURCC_RGBP;
            dataSize = width * height * 2;
            break;
        case 5:
            format = libyuv::FOURCC_ABGR;
            dataSize = width * height * 4;
            break;
        default:
            logger::error("dataFormat value error, please check it.");
            return -1;
    }
    int bmpWidth = width;
    int bmpHeight = height;
    int crop_x = 0, crop_y = 0;
    if (!rect.empty()) {
        int left = rect[0];
        int top = rect[1];
        int right = rect[2];
        int bottom = rect[3];
        crop_x = left;
        crop_y = top;
        if (priorityClip) {
            if ((degree == 90 || degree == -90 || degree == 270)) {
                bmpWidth = bottom - top;
                bmpHeight = right - left;
            } else {
                bmpWidth = right - left;
                bmpHeight = bottom - top;
            }
        } else {
            bmpWidth = right - left;
            bmpHeight = bottom - top;
            if (degree == 90) {
                crop_x = top;
                crop_y = height - right;
                if (right > bmpHeight || bottom > bmpWidth
                    || crop_x > bmpWidth || crop_y > bmpHeight) {
                    logger::error(
                            "rect width or height more than rotated image width or height, please check it.");
                    return -1;
                }
            } else if (degree == 180) {
                crop_x = width - right;
                crop_y = height - bottom;
            } else if (degree == -90 || degree == 270) {
                crop_x = width - bottom;
                crop_y = left;
                if (right > bmpHeight || bottom > bmpWidth
                    || crop_x > bmpWidth || crop_y > bmpHeight) {
                    logger::error("rect width or height more than rotated image width or height, please check it.");
                    return -1;
                }
            }

        }

    } else if (degree == 90 || degree == -90 || degree == 270) {
        bmpWidth = height;
        bmpHeight = width;
    }
    uint8 *i420_data = new uint8[bmpWidth * bmpHeight +
                                 ((bmpWidth + 1) / 2) * ((bmpHeight + 1) / 2) * 2];
    int resCode = libyuv::ConvertToI420(src_data,
                                        static_cast<size_t>(dataSize),
                                        (dst_format == 2 ? dst_data : i420_data), bmpWidth,
                                        (dst_format == 2 ? dst_data : i420_data) + bmpWidth * bmpHeight, bmpWidth >> 1,
                                        (dst_format == 2 ? dst_data : i420_data) + bmpWidth * bmpHeight +
                                        (bmpWidth >> 1) * (bmpHeight >> 1),
                                        bmpWidth >> 1,
                                        crop_x, crop_y,
                                        width, height,
                                        degree % 180 == 0 ? bmpWidth : bmpHeight,
                                        degree % 180 == 0 ? bmpHeight : bmpWidth,
                                        mode, format
    );

    if (resCode != 0) {
        delete[] i420_data;
        return resCode;
    }
    switch (dst_format) {
        case 1:
            resCode = I420ToNV21(i420_data, bmpWidth, bmpHeight, dst_data);
            break;
        case 2:
            break;
        case 3:
            resCode = I420ToRGB565(i420_data, bmpWidth, bmpHeight, dst_data);
            break;
        case 5:
            resCode = I420ToRGBA(i420_data, bmpWidth, bmpHeight, dst_data);
            break;
        default:
            resCode = -1;
            break;
    }
    delete[] i420_data;
    return resCode;
}

