# ImageUtils

## 写在前面
该图像处理库底层依赖的是 Google 开源的 `libyuv` 框架，因该框架功能之强大，支持图像格式之繁多，目前这里只针对 Android 中常用的图像格式之间互相操作进行了相关封装操作，方便 `Java` / `Kotlin` 进行无缝调用。

## 功能说明
- [x] 支持 `RGB_565`、`ARGB_8888`、`RGB24`、`I420`、`NV21` 5中格式图像之间互相转换操作
- [x] 支持将 `Bitmap` 转换成以上五种图像格式操作
- [x] 支持将以上格式的图像转换成 `Bitmap` 操作
- [x] 支持以上格式图像之间互相旋转、裁剪操作
- [x] 支持以上格式图像之间缩放操作
- [x] 支持以上格式图像之间镜像操作
- [x] 底层依赖 `libyuv` 框架，安全、稳定、高效

关于具体接口说明，请 [点击此处](https://github.com/Reign9201/ImageUtils/blob/master/doc/ImageUtils%E5%BA%93%E6%8E%A5%E5%8F%A3%E8%AF%B4%E6%98%8E%E6%96%87%E6%A1%A3.md)

关于图像格式说明，请 [点击此处](https://github.com/Reign9201/ImageUtils/blob/master/doc/Android%E4%B8%AD%E5%B8%B8%E7%94%A8%E5%9B%BE%E5%83%8F%E6%A0%BC%E5%BC%8F%E8%AF%B4%E6%98%8E.md)

---

## 使用说明
### Gradle 依赖
-  **Step 1**. Add the JitPack repository to your build file

    Add it in your root build.gradle at the end of repositories:
    ```
    allprojects {
    	repositories {
    		...
    		maven { url 'https://jitpack.io' }
    	}
    }
    ```
- **Step 2**. Add the dependency
    ```
    dependencies {
	        implementation 'com.github.Reign9201:ImageUtils:v0.1-alpha'
	}
    ```

### 简单使用

例如，我们将相机采集的预览流转换成Android手机能显示的 Bitmap:
```Kotlin
// 一般相机预览流为 NV21格式，而且是旋转了270的
val bitmap:Bitmap? = ImageUtils.nv21ToBitmap8888(data, width, height, 270)
```


例如，我们从手机相机中采集了一段人脸预览流，经过人脸识别采集到了人脸框，此时我们需要根据识别后的人脸框将人脸从整个预览流中抠下来，我们可以这么操作：

```Kotlin
fun onPreviewFrame(data: ByteArray, width: Int, height: Int, faceRect: Rect) {
    // 返回值为人脸识别后抠出的脸图
    val faceBitmap: Bitmap? = YuvUtils.dataClipRotateToBitmap(
        data,       // 采集的原始预览流
        1,          // Android 相机一般采集的是 NV21 格式的，因此是 1
        width,      // 原始图像宽
        height,     // 原始图像高
        270,        // Android设备一般是 270 ，当然可以自己改，此处只是演示
        faceRect,   // 人脸识别后的人脸框数据
        5,          // 生成Bitmap格式，5表示 ARGB_8888
        false       // 不进行优先裁剪
    )
}
```

更多其他操作，请参见 [文档说明](https://github.com/Reign9201/ImageUtils/blob/master/doc/ImageUtils%E5%BA%93%E6%8E%A5%E5%8F%A3%E8%AF%B4%E6%98%8E%E6%96%87%E6%A1%A3.md)。

---

## License
```
Copyright 2020 Yanjun Xu

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```