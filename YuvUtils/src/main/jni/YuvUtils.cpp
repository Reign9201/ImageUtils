//# pragma once


#include "YuvUtils.h"


void YuvUtils::nv21ToArgb(jbyte *nv21data, jint width, jint height, uint8 *argbData) {
     //将NV21(YUV420SP) 拆分成Y 和 UV 两个分量
    jint src_y_size = width * height;
    jint src_u_size = (width >> 1) * (height >> 1);
    jbyte *src_y_data = nv21data;
    jbyte *src_uv_data = nv21data + src_y_size;

    //uint8 *dst_argb_data = (uint8 *) malloc(sizeof(uint8) * width * height * 4);

    logger::error("7777777777777777777777777");
    NV21ToARGB((const uint8 *) src_y_data, width,
               (const uint8 *) src_uv_data, (width + 1) / 2 * 2,
               argbData, width * 4, width, height);
    logger::error("66666666666666666666666666666666666666");
}
