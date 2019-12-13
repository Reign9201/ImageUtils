//
// Created by XuYanjun on 2019/11/20.
//
#include <string.h>
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


int yancy::NV21ToI420(const uint8 *src_nv21_data, int width, int height, uint8 *dst_i420) {
    return libyuv::NV21ToI420(src_nv21_data, width,
                              src_nv21_data + width * height, width,
                              dst_i420, width,
                              dst_i420 + width * height, width >> 1,
                              dst_i420 + width * height + (width >> 1) * (height >> 1), width >> 1,
                              width, height);
}

int yancy::NV21ToRGB24(const uint8 *src_nv21_data, int width, int height, uint8 *dst_rgb24) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (NV21ToI420(src_nv21_data, width, height, i420_data) != 0) {
        delete[] i420_data;
        return -1;
    }
    int resCode = I420ToRGB24(i420_data, width, height, dst_rgb24);
    delete[] i420_data;

    return resCode;
}

int yancy::I420ToRGB24(const uint8 *src_i420_data, int width, int height, uint8 *dst_rgb24) {
    return libyuv::I420ToRGB24(src_i420_data, width,
                               src_i420_data + width * height, width >> 1,
                               src_i420_data + width * height + (width >> 1) * (height >> 1), width >> 1,
                               dst_rgb24, width * 3, width, height);
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

int yancy::RGBAToRGB24(const uint8 *src_rgba_data, int width, int height, uint8 *dst_rgb24_data) {
    uint8 *argb = new uint8[width * height * 4];
    if (libyuv::ABGRToARGB(src_rgba_data, width * 4,
                           argb, width * 4,
                           width, height) != 0) {
        delete[] argb;
        return -1;
    }
    int resCode = libyuv::ARGBToRGB24(argb, width * 4, dst_rgb24_data, width * 3, width, height);
    delete[] argb;
    return resCode;
}

int yancy::RGB24ToNV21(const uint8 *src_rgb24_data, int width, int height, uint8 *dst_nv21_data) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (RGB24ToI420(src_rgb24_data, width, height, i420_data)) {
        delete[] i420_data;
        return -1;
    }
    int resCode = I420ToNV21(i420_data, width, height, dst_nv21_data);
    delete[] i420_data;
    return resCode;
}

int yancy::RGB24ToI420(const uint8 *src_rgb24_data, int width, int height, uint8 *dst_i420_data) {
    return libyuv::RGB24ToI420(src_rgb24_data, width * 3,
                               dst_i420_data, width,
                               dst_i420_data + width * height, width >> 1,
                               dst_i420_data + width * height + (width >> 1) * (height >> 1),
                               width >> 1,
                               width, height);
}

int yancy::RGB24ToRGB565(const uint8 *src_rgb24_data, int width, int height, uint8 *dst_rgb_data) {
    uint8 *i420_data = new uint8[width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2];
    if (RGB24ToI420(src_rgb24_data, width, height, i420_data)) {
        delete[] i420_data;
        return -1;
    }
    int resCode = I420ToRGB565(i420_data, width, height, dst_rgb_data);
    delete[] i420_data;
    return resCode;
}

int yancy::RGB24ToRGBA(const uint8 *src_rgb24_data, int width, int height, uint8 *dst_rgba_data) {
    uint8 *argb_data = new uint8[width * height * 4];
    if (libyuv::RGB24ToARGB(src_rgb24_data, width * 3, argb_data, width * 4, width, height) != 0) {
        delete[] argb_data;
        return -1;
    }
    int resCode = libyuv::ARGBToABGR(argb_data, width * 4, dst_rgba_data, width * 4, width, height);
    delete[] argb_data;
    return resCode;
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

int yancy::RGB565ToRGB24(const uint8 *src_rgb_data, int width, int height, uint8 *dst_rgb24_data) {
    uint8 *argb_data = new uint8[width * height * 4];
    if (libyuv::RGB565ToARGB(src_rgb_data, width * 2, argb_data, width * 4, width, height) != 0) {
        delete[] argb_data;
        return -1;
    }
    int resCode = libyuv::ARGBToRGB24(argb_data, width * 4, dst_rgb24_data, width * 3, width, height);
    delete[] argb_data;
    return resCode;
}

int yancy::DataMirror(const uint8 *src_data, int width, int height, uint8 **dst_data, int src_fourcc,
                      int dst_fourcc, bool vertical_mirror) {

    int resCode = -1;

    switch (src_fourcc) {
        case libyuv::FOURCC_NV21:
            switch (dst_fourcc) {
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
            switch (dst_fourcc) {
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
            switch (dst_fourcc) {
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
            switch (dst_fourcc) {
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

int yancy::DataConvert(uint8 *src_data, int src_width, int src_height, int src_data_size,
                       uint8 *dst_data, int dst_width, int dst_height, int degree,
                       uint32 src_format, int dst_format, libyuv::RotationMode rotateMode,
                       int crop_x, int crop_y) {

    uint8 *i420_data = new uint8[dst_width * dst_height +
                                 ((dst_width + 1) / 2) * ((dst_height + 1) / 2) * 2];
    int resCode = libyuv::ConvertToI420(src_data,
                                        static_cast<size_t>(src_data_size),
                                        (src_format == 2 ? dst_data : i420_data), dst_width,
                                        (src_format == 2 ? dst_data : i420_data) + dst_width * dst_height, dst_width >> 1,
                                        (src_format == 2 ? dst_data : i420_data) + dst_width * dst_height +
                                        (dst_width >> 1) * (dst_height >> 1),
                                        dst_width >> 1,
                                        crop_x, crop_y,
                                        src_width, src_height,
                                        degree % 180 == 0 ? dst_width : dst_height,
                                        degree % 180 == 0 ? dst_height : dst_width,
                                        rotateMode, src_format
    );
    if (resCode != 0) {
        delete[] i420_data;
        return resCode;
    }

    switch (getFormat(dst_format)) {
        case NV21:
            resCode = I420ToNV21(i420_data, dst_width, dst_height, dst_data);
            break;
        case I420:
            break;
        case RGB565:
            resCode = I420ToRGB565(i420_data, dst_width, dst_height, dst_data);
            break;
        case RGB24:
            resCode = I420ToRGB24(i420_data, dst_width, dst_height, dst_data);
            break;
        case ARGB_8888:
            resCode = I420ToRGBA(i420_data, dst_width, dst_height, dst_data);
            break;
        default:
            resCode = -1;
            break;
    }
    delete[] i420_data;
    return resCode;

}

int
yancy::DataScale(const uint8 *src_data, int src_width, int src_height, uint8 **dst_data, int dst_width, int dst_height, int src_format,
                 int dst_format, libyuv::FilterMode filterMode) {
    switch (getFormat(src_format)) {
        case NV21:
            switch (getFormat(dst_format)) {
                case NV21:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         NV21ToI420, I420ToNV21);
                case I420:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         NV21ToI420, nullptr);
                case RGB565:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         NV21ToI420, I420ToRGBA);
                case RGB24:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         NV21ToI420, I420ToRGB24);
                case ARGB_8888:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         NV21ToI420, I420ToRGB565);
                default:
                    return -1;
            }
        case I420:
            switch (getFormat(dst_format)) {
                case NV21:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         nullptr, I420ToNV21);
                case I420:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         nullptr, nullptr);
                case RGB565:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         nullptr, I420ToRGBA);
                case RGB24:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         nullptr, I420ToRGB24);
                case ARGB_8888:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         nullptr, I420ToRGB565);
                default:
                    return -1;
            }
        case RGB565:
            switch (getFormat(dst_format)) {
                case NV21:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB565ToI420, I420ToNV21);
                case I420:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB565ToI420, nullptr);
                case RGB565:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB565ToI420, I420ToRGBA);
                case RGB24:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB565ToI420, I420ToRGB24);
                case ARGB_8888:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB565ToI420, I420ToRGB565);
                default:
                    return -1;
            }
        case RGB24:
            switch (getFormat(dst_format)) {
                case NV21:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB24ToI420, I420ToNV21);
                case I420:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB24ToI420, nullptr);
                case RGB565:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB24ToI420, I420ToRGBA);
                case RGB24:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB24ToI420, I420ToRGB24);
                case ARGB_8888:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGB24ToI420, I420ToRGB565);
                default:
                    return -1;
            }
        case ARGB_8888:
            switch (getFormat(dst_format)) {
                case NV21:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGBAToI420, I420ToNV21);
                case I420:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGBAToI420, nullptr);
                case RGB565:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGBAToI420, I420ToRGBA);
                case RGB24:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGBAToI420, I420ToRGB24);
                case ARGB_8888:
                    return __DataScale__(src_data, src_width, src_height,
                                         dst_data, dst_width, dst_height,
                                         filterMode,
                                         RGBAToI420, I420ToRGB565);
                default:
                    return -1;
            }
        default:
            return -1;

    }

}


int yancy::__DataScale__(const uint8 *src_data, int src_width, int src_height, uint8 **dst_data, int dst_width, int dst_height,
                         libyuv::FilterMode filterMode, __convert__ pre_convert, __convert__ next_convert) {

    int resCode;
    uint8 *i420_data = 0;
    if (pre_convert != nullptr) {
        i420_data = new uint8[src_width * src_height + ((src_width + 1) / 2) * ((src_height + 1) / 2) * 2];
        resCode = pre_convert(src_data, src_width, src_height, i420_data);
        if (resCode != 0) {
            delete[] i420_data;
            return resCode;
        }
    }

    uint8 *dst_i420_data = 0;
    if (next_convert != nullptr) {
        dst_i420_data = new uint8[dst_width * dst_height + ((dst_width + 1) / 2) * ((dst_height + 1) / 2) * 2];
        resCode = __I420ScaleToI420__((i420_data == 0 ? src_data : i420_data), src_width, src_height,
                                      &dst_i420_data, dst_width, dst_height,
                                      filterMode);
        if (resCode != 0) {
            if (i420_data) {
                delete[] i420_data;
            }
            delete[] dst_i420_data;
            return resCode;
        }
        resCode = next_convert(dst_i420_data, dst_width, dst_height, *dst_data);
        delete[] dst_i420_data;
        return resCode;
    }
    resCode = __I420ScaleToI420__((i420_data == 0 ? src_data : i420_data), src_width, src_height,
                                  dst_data, dst_width, dst_height, filterMode);
    if (i420_data) {
        delete[] i420_data;
    }
    return resCode;
}


int yancy::__I420ScaleToI420__(const uint8 *src_data, int src_width, int src_height, uint8 **dst_data, int dst_width, int dst_height,
                               libyuv::FilterMode filterMode) {
    return libyuv::I420Scale(src_data, src_width,
                             src_data + src_width * src_height, src_width >> 1,
                             src_data + src_width * src_height + (src_width >> 1) * (src_height >> 1), src_width >> 1,
                             src_width, src_height,
                             *dst_data, dst_width,
                             *dst_data + dst_width * dst_height, dst_width >> 1,
                             *dst_data + dst_width * dst_height + (dst_width >> 1) * (dst_height >> 1), dst_width >> 1,
                             dst_width, dst_height,
                             filterMode);
}


yancy::ImageFormat yancy::getFormat(int formatValue) {
    switch (formatValue) {
        case 1:
            return NV21;
        case 2:
            return I420;
        case 3:
            return RGB565;
        case 5:
            return ARGB_8888;
        default:
            return NONE;
    }
}

libyuv::FilterMode yancy::getFilterMode(int filterMode) {
    switch (filterMode) {
        case 0:
            return libyuv::kFilterNone;
        case 1:
            return libyuv::kFilterLinear;
        case 2:
            return libyuv::kFilterBilinear;
        case 3:
            return libyuv::kFilterBox;
        default:
            return libyuv::kFilterNone;
    }
}

int yancy::getDataSize(int width, int height, int dataFormat) {
    switch (dataFormat) {
        case 1:
        case 2:
            return width * height + ((width + 1) / 2) * ((height + 1) / 2) * 2;
        case 3:
            return width * height * 2;
        case 4:
            return width * height * 3;
        case 5:
            return width * height * 4;
        default:
            return 0;
    }
}








