package com.yancy.yuvutils.annotation;

import androidx.annotation.IntDef;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * 说明：
 *
 * @author Yancy
 * @date 2019/12/4
 */
@IntDef({1, 2, 3, 5})
@Retention(RetentionPolicy.SOURCE)
public @interface SupportFormat {
}
