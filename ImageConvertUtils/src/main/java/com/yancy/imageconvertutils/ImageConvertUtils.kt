package com.yancy.imageconvertutils

import android.content.res.Resources
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.drawable.BitmapDrawable
import android.graphics.drawable.Drawable
import java.io.*

/**
 * 说明：
 * @author  Yancy
 * @date 2019/11/11
 */
@Suppress("UNUSED")
object ImageConvertUtils {
    private const val NOT_SUPPORT = -1

    /**
     * bitmap convert into drawable
     *
     * @param bitmap    source bitmap data
     * @param resources system api,accessing an application's resources
     */
    @JvmStatic
    @JvmOverloads
    fun bitmap2Drawable(bitmap: Bitmap, resources: Resources = Resources.getSystem()): Drawable {
        return BitmapDrawable(resources, bitmap)
    }


    /**
     * bitmap compress into a new bitmap
     *
     * @param bitmap       source bitmap data
     * @param quality      Hint to the compressor, 0-100. 0 meaning compress for
     *                     small size, 100 meaning compress for max quality. Some
     *                     formats, like PNG which is lossless, will ignore the
     *                     quality setting
     * @param format       Specifies the known formats a bitmap can be compressed into
     * @param inSampleSize you can see {@link BitmapFactory.Options#inSampleSize}
     * @return a new compressed bitmap, maybe return `null`.
     */
    @Throws(Exception::class)
    fun bitmapCompress(
        bitmap: Bitmap?,
        quality: Int,
        format: Bitmap.CompressFormat = Bitmap.CompressFormat.JPEG,
        inSampleSize: Int = NOT_SUPPORT
    ): Bitmap? {
        return bitmap?.let {
            val baos = ByteArrayOutputStream()
            return if (it.compress(format, quality, baos)) {
                val bais = ByteArrayInputStream(baos.toByteArray())
                if (inSampleSize == NOT_SUPPORT) {
                    return BitmapFactory.decodeStream(bais)
                }
                val options = BitmapFactory.Options()
                options.inSampleSize = inSampleSize
                return BitmapFactory.decodeStream(bais, null, options)
            } else null

        }

    }


    /**
     * bitmap compress into a new bitmap
     *
     * @param bitmap    source bitmap data
     * @param quality   Hint to the compressor, 0-100. 0 meaning compress for
     *                  small size, 100 meaning compress for max quality. Some
     *                  formats, like PNG which is lossless, will ignore the
     *                  quality setting
     * @param format    Specifies the known formats a bitmap can be compressed into
     */
    @JvmOverloads
    @JvmStatic
    fun bitmap2CompressBytes(
        bitmap: Bitmap?,
        quality: Int = 100,
        format: Bitmap.CompressFormat = Bitmap.CompressFormat.JPEG
    ): ByteArray? {
        val baos = ByteArrayOutputStream()
        return bitmap?.let {
            return if (it.compress(format, quality, baos)) baos.toByteArray() else null
        }
    }

    @JvmStatic
    fun bitmapSave2JPEG(bitmap: Bitmap, savePath: String, saveName: String): Boolean {
        return saveBitmap2Local(bitmap, savePath, saveName)
    }

    @JvmStatic
    fun bitmapSave2PNG(bitmap: Bitmap, savePath: String, saveName: String): Boolean {
        return saveBitmap2Local(bitmap, savePath, saveName, Bitmap.CompressFormat.PNG)
    }

    @JvmStatic
    @JvmOverloads
    fun saveBitmap2Local(
        bitmap: Bitmap,
        savePath: String,
        saveName: String,
        format: Bitmap.CompressFormat = Bitmap.CompressFormat.JPEG,
        quality: Int = 100
    ): Boolean {
        if (savePath.isEmpty() || saveName.isEmpty()) return false
        val dirFile = File(savePath)
        if (!dirFile.exists()) dirFile.mkdirs()
        val compressData = bitmap2CompressBytes(bitmap, quality, format)
        return compressData?.let {
            var fos: FileOutputStream? = null
            return try {
                fos = FileOutputStream(File(dirFile, saveName))
                fos.write(compressData)
                fos.flush()
                true
            } catch (ex: IOException) {
                ex.printStackTrace()
                false
            } finally {
                fos?.apply {
                    try {
                        this.close()
                    } catch (ignored: IOException) {
                    }
                }
            }
        } ?: false

    }

}