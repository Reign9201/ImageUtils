package com.yancy.yuvutils.annotation;

import androidx.annotation.IntDef;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * 说明：角度限制
 *
 * @author Yancy
 * @date 2019/12/4
 */
@IntDef({-90, 0, 90, 180, 270})
@Retention(RetentionPolicy.SOURCE)
public @interface RotateDegree {
}
