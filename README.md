# ImageUtils

## 写在前面
该图像处理库底层依赖的是 Google 开源的 `libyuv` 框架，因该框架功能之强大，支持图像格式之繁多，目前这里只针对 Android 中常用的图像格式之间互相操作进行了相关封装操作，方便 `Java` / `Kotlin` 进行无缝调用。

## 功能说明
- [x] 支持 `RGB_565`、`ARGB_8888`、`RGB24`、`I420`、`NV21` 5中格式图像之间互相转换操作
- [x] 支持将 `Bitmap` 转换成以上五种图像格式操作
- [x] 支持将以上格式的图像转换成 `Bitmap` 操作
- [x] 支持以上格式图像之间互相旋转裁剪操作
- [x] 支持以上格式图像之间缩放操作
- [x] 支持以上格式图像之间镜像操作
- [x] 底层依赖 `libyuv` 框架，安全、稳定、高效

具体接口说明，请 [点击此处](https://github.com/Reign9201/ImageUtils/blob/master/doc/ImageUtils%E5%BA%93%E6%8E%A5%E5%8F%A3%E8%AF%B4%E6%98%8E%E6%96%87%E6%A1%A3.md)

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