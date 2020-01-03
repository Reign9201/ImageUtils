# ImageUtils库接口说明文档

[toc]

---

## 写在前面
> 这篇文章主要是针对 `ImageUtils` 库中的API接口进行说明，关于 `ImageUtils` 的使用，请 [点击此处](https://github.com/Reign9201/ImageUtils)。

---

## <div id="format">ImageFormat枚举类</div>
这个类主要用于说明目前支持的数据转换的格式，具体如下：
```Kotlin
enum class ImageFormat(var format: Int) {
    NV21(1),
    I420(2),
    RGB_565(3),
    RGB_888(4),
    ARGB_8888(5)
}
```
关于以上数据格式详细说明，请参见：[TODO记得补充]()

---

## 枚举类FilterMode
这个枚举类，主要说明对图像进行缩放的时候支持的过滤模式，具体如下：
```Kotlin
enum class FilterMode(var filter: Int) {
    FilterNone(0),
    FilterLinear(1),
    FilterBilinear(2),
    FilterBox(3)
}
```
关于过滤模式的说明，请参见：[filtering.md](https://github.com/Reign9201/ImageUtils/blob/master/libyuv/jni/docs/filtering.md)

---
## ImageInfo
这个类主要用于辅助图像数据进行旋转裁剪，具体如下：
```Kotlin
class ImageInfo(
    val data: ByteArray,
    val dataFormat: ImageFormat,
    val width: Int,
    val height: Int,
    @RotateDegree val degree: Int = 0,
    val rect: Rect? = null,
    val targetFormat: ImageFormat,
    val priorityClip: Boolean = true
)
```
具体参数说明如下：
- `data`：源图像数据
- `dataFormat`：源图像数据格式，支持的格式参见 [ImageFormat](#format)
- `width`：源图像的宽
- `height`：源图像的高
- `degree`：需要旋转的角度
- `rect`：需要裁剪的矩形坐标 `Rect`，可以为 `null` ，表示不进行裁剪
- `targetFormat`：处理后的图像格式，支持的格式参见 [ImageFormat](#format)
- `priorityClip`：使用优先裁剪，默认为 `ture`，这个参数很重要，后面会说

---
## YuvUtils类
### 2.1 Bitmap转换成其他图像格式
主要有5个接口：

```Kotlin
external fun bitmapToNV21(bitmap: Bitmap?): ByteArray?
external fun bitmapToRgb565(bitmap: Bitmap?): ByteArray?
external fun bitmapToRgb24(bitmap: Bitmap?): ByteArray?
external fun bitmapToRgba(bitmap: Bitmap?): ByteArray?
external fun bitmapToI420(bitmap: Bitmap?): ByteArray?
```
- 关于参数 `bitmap` ，目前仅支持 `RGB_565` 和 `RGBA_8888` 两种类型的位图转换

### 2.2 各种格式的图像之间互相转换
```Kotlin
external fun imageFormatConvert(
    data: ByteArray,
    width: Int,
    height: Int,
    @SupportFormat dataFormat: Int,
    @SupportFormat targetFormat: Int
): ByteArray?
```
参数说明：
- `data`：源图像数据
- `width`：图像的宽
- `height`：图像的高
- `dataFormat`：源图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类
- `targetFormat`：需要转换成的图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类
- `返回值`：返回转换后的数据

 例如一个分辨率为 `640 * 480` 的 `NV21` 格式的数据，现在需要将它转换成 `RGB24` 格式，我们可以这么调用：
```Kotlin
YuvUtils.imageFormatConvert(data, 640, 480, 1, 4)
```

### 2.3 各种格式的图像转换成Bitmap
```Kotlin
external fun imageToBitmap(
    data: ByteArray,
    width: Int,
    height: Int,
    @SupportFormat dataFormat: Int,
    bitmapConfig: Int
):Bitmap?
```
参数说明：
- `data`：源图像数据
- `width`：图像的宽
- `height`：图像的高
- `dataFormat`：源图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类
- `bitmapConfig`：需要转换成的Bitmap格式，目前仅支持 `RGB565` 和 `ARGB_8888` 两种格式的 `Bitmap`
- `返回值`：返回转换后的 `Bitmap`

### 2.4 各种格式图像的旋转和裁剪操作
```Kotlin
external fun dataClipRotate(
    data: ByteArray,
    @SupportFormat dataFormat: Int,
    width: Int,
    height: Int,
    @RotateDegree degree: Int,
    rect: Rect?,
    targetFormat: Int,
    priorityClip: Boolean
): ByteArray?
```
参数说明：
- `data`：源图像数据
- `dataFormat`：源图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类
- `width`：图像的宽
- `height`：图像的高
- `degree`：图像旋转的角度，仅支持 `0`、`90`、`180`、`270` 四个角度
- `rect`：裁剪的矩形坐标，可以为 `null`，表示不进行裁剪操作
- `targetFormat`：需要转换成的目标图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类
- `priorityClip`：是否进行优先裁剪操作，先裁剪再旋转和先旋转再裁剪是两种不同的操作
- `返回值`：返回转换后的数据

例如：
```Kotlin
YuvUtils.dataClipRotate(
            rgba_data, 5, width, height, 90,
            Rect(100, 0, 300, 300), 5, false
        )
```

![image](https://user-gold-cdn.xitu.io/2020/1/3/16f6973d5f386659?w=1133&h=653&f=png&s=456021)

从上面的操作可以看出，`priorityClip`的选择其实还是很重要的！


### 2.5 各种格式图像经过旋转和裁剪转换成相关Bitmap
```Kotlin
external fun dataClipRotateToBitmap(
    data: ByteArray,
    @SupportFormat dataFormat: Int,
    width: Int,
    height: Int,
    @RotateDegree degree: Int,
    rect: Rect?,
    bitmapConfig: Int,
    priorityClip: Boolean
): Bitmap?
```

参数说明：
- `data`：源图像数据
- `dataFormat`：源图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类
- `width`：图像的宽
- `height`：图像的高
- `degree`：图像旋转的角度，仅支持 `0`、`90`、`180`、`270` 四个角度
- `rect`：裁剪的矩形坐标，可以为 `null`，表示不进行裁剪操作
- `bitmapConfig`：需要转换成的 `Bitmap` 格式，目前仅支持 `RGB565` 和 `ARGB_8888` 两种格式的 `Bitmap`
- `priorityClip`：是否进行优先裁剪操作，先裁剪再旋转和先旋转再裁剪是两种不同的操作
- `返回值`：返回转换后的 `Bitmap`

### 2.6 各种格式图像的镜面翻转操作
```
external fun dataMirror(
    data: ByteArray,
    width: Int,
    height: Int,
    @SupportFormat dataFormat: Int,
    @SupportFormat targetFormat: Int,
    isVerticalMirror: Boolean = false
): ByteArray?
```
参数说明：
- `data`：源图像数据
- `width`：图像的宽
- `height`：图像的高
- `dataFormat`：源图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类
- `targetFormat`：需要转换成的图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类
- `isVerticalMirror`：是否执行垂直镜像操作，默认`false`，即水平翻转，若为`true`，即对图像进行了 `180` 旋转，而并非真正的垂直镜像
- `返回值`：返回转换后的数据

关于 `isVerticalMirror` 区别，请看下图：

![image](https://user-gold-cdn.xitu.io/2020/1/3/16f69749ec485289?w=1123&h=253&f=png&s=308042)


### 2.7 各种格式图像的缩放操作
```
external fun dataScale(
    data: ByteArray,
    width: Int,
    height: Int,
    dstWidth: Int,
    dstHeight: Int,
    @SupportFormat dataFormat: Int,
    @SupportFormat targetFormat: Int,
    @SupportFilter filterMode: Int = 0
): ByteArray?
```
参数说明：
- `data`：源图像数据
- `width`：图像的宽
- `height`：图像的高
- `dstWidth`：目标图像的宽
- `dstHeight`：目标图像的高
- `dataFormat`：源图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类
- `targetFormat`：需要转换成的图像格式，支持的图像格式，可参见 `ImageFormat` 枚举类