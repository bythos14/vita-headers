/**
 * \usergroup{SceJpegEncArm}
 * \internalusage{psp2/jpegencarm.h,SceJpegEncArm_stub,SCE_SYSMODULE_INTERNAL_JPEG_ENC_ARM}
 *
 * \note The maximum supported image width and height is 65520 for YCbCr420,
 *       and 65528 for YCbCr422.\n\n
 *       The width and height of YCbCr422 images must be a multiple of 8.
 *       The width and height of YCbCr420 images must be a multiple of 16.
 */

#ifndef _PSP2_JPEGENCARM_H_
#define _PSP2_JPEGENCARM_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_JPEGENCARM_MIN_COMP_RATIO     1   //!< Lowest compression ratio, best quality.
#define SCE_JPEGENCARM_DEFAULT_COMP_RATIO 64  //!< Default compression ratio.
#define SCE_JPEGENCARM_MAX_COMP_RATIO     255 //!< Highest compression ratio, lowest quality.

/**
 * Dynamically allocated encoder context.
 *
 * See @ref sceJpegArmEncoderGetContextSize() for required allocation size.
 * The address must be 4 byte aligned.
 */
typedef void* SceJpegArmEncoderContext;

/**
 * Error Codes
 */
typedef enum SceJpegEncArmErrorCode {
	/**
	 * The image dimensions given are not supported, or are larger
	 * than those set at initialization.
	 */
	SCE_JPEGENCARM_ERROR_IMAGE_SIZE                = 0x80650300,
	/**
	 * The output buffer provided is not of sufficient size.
	 */
	SCE_JPEGENCARM_ERROR_INSUFFICIENT_BUFFER       = 0x80650301,
	/**
	 * The compression ratio given is not within the valid range.
	 */
	SCE_JPEGENCARM_ERROR_INVALID_COMP_RATIO        = 0x80650302,
	/**
	 * The pixelformat given is not one of ::SceJpegArmEncoderPixelFormat.
	 */
	SCE_JPEGENCARM_ERROR_INVALID_PIXELFORMAT       = 0x80650303,
	/**
	 * The headerMode given is not one of ::SceJpegArmEncoderHeaderMode.
	 */
	SCE_JPEGENCARM_ERROR_INVALID_HEADER_MODE       = 0x80650304,
	/**
	 * A null or badly aligned pointer was given.
	 */
	SCE_JPEGENCARM_ERROR_INVALID_POINTER           = 0x80650305
} SceJpegEncArmErrorCode;

/**
 * Pixel Formats
 */
typedef enum SceJpegArmEncoderPixelFormat {
	SCE_JPEGENCARM_PIXELFORMAT_YCBCR420 = 8, //!< YCbCr420 format
	SCE_JPEGENCARM_PIXELFORMAT_YCBCR422 = 9	 //!< YCbCr422 format
} SceJpegArmEncoderPixelFormat;

/**
 * JPEG Header Modes
 */
typedef enum SceJpegArmEncoderHeaderMode {
	SCE_JPEGENCARM_HEADER_MODE_JPEG  = 0,  //!< JPEG header mode
	SCE_JPEGENCARM_HEADER_MODE_MJPEG = 1   //!< MJPEG header mode
} SceJpegArmEncoderHeaderMode;

typedef enum SceJpegArmEncoderSplitEncodeFlags {
	SCE_JPEGENCARM_SPLIT_ENCODE_WRITE_DATA  = 1, //!< Write JPEG data. Exclude this flag to initiate a split encode.
	SCE_JPEGENCARM_SPLIT_ENCODE_PER_PIXEL   = 2, //!< Encode JPEG data per pixel. Default is per row of pixels.
} SceJpegArmEncoderSplitDecodeFlags;

/**
 * Get required size of context memory.
 *
 * @return Required size of allocated memory.
 */
SceSize sceJpegArmEncoderGetContextSize(void);

/**
 * Initialize a JPEG encoder.
 *
 * @param[in] context     - An allocated encoder context of appropriate size.
 * @param[in] inWidth     - Input width in pixels.
 * @param[in] inHeight    - Input height in pixels.
 * @param[in] pixelformat - One of ::SceJpegArmEncoderPixelFormat.
 * @param[in] outBuffer   - A sufficiently sized 8 byte aligned output buffer.
 * @param[in] outSize     - Output buffer size in bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderInit(SceJpegArmEncoderContext context, SceUInt16 inWidth, SceUInt16 inHeight, SceJpegArmEncoderPixelFormat pixelformat, void *outBuffer, SceSize outSize);

/**
 * Terminate a JPEG encoder.
 *
 * @param[in] context - An already initialized ::SceJpegArmEncoderContext.
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderEnd(SceJpegArmEncoderContext context);

/**
 * Execute a JPEG encode.
 *
 * @param[in] context  - An already initialized ::SceJpegArmEncoderContext.
 * @param[in] inBuffer - An 8 byte aligned memory block of planar YCbCr color data.
 *
 * @return Encoded JPEG size on success, < 0 on error.
 */
int sceJpegArmEncoderEncode(SceJpegArmEncoderContext context, const void *inBuffer);

/**
 * Execute a split JPEG encode.
 *
 * @param[in] context       - An already initialized ::SceJpegArmEncoderContext.
 * @param[in] yBuffer       - An 8 byte aligned memory block of Y channel data.
 * @param[in] cbBuffer      - An 8 byte aligned memory block of Cb channel data.
 * @param[in] crBuffer      - An 8 byte aligned memory block of Cr channel data.
 * @param[in] flags         - Combination of ::SceJpegArmEncoderSplitEncodeFlags.
 * @param[in] outBuffer     - Output buffer. Will be used in place of any output buffer set by any other library functions.
 * @param[in] outSize       - Output buffer size.
 * @param[out] bytesWritten - Number of bytes written to the output buffer.
 * 
 * @par Example:
 * @code
 * EncodeJPEG(uint32_t *rgba, uint16_t width, height)
 * {
 *     SceUInt32 contextSize = sceJpegArmEncoderGetContextSize();
 *     SceJpegArmEncoderContext context = malloc(contextSize);
 *     
 *     sceJpegArmEncoderInit(context, width, height, SCE_JPEGENCARM_PIXELFORMAT_YCBCR422, NULL, 0); // Output buffer is left unset
 *     sceJpegArmEncoderSetCompressionRatio(context, 196);
 *     sceJpegArmEncoderSetHeaderMode(context, SCE_JPEGENCARM_HEADER_MODE_JPEG);
 *     
 *     SceUInt32 bytesWritten = 0;
 *     void *yBuffer, *cbBuffer, *crBuffer, *outBuffer;
 *     outBuffer = malloc(0x1000, 1);
 *     yBuffer = ALIGN(malloc(width + 7), 8);
 *     cbBuffer = ALIGN(malloc((width / 2) + 7), 8);
 *     crBuffer = ALIGN(malloc((width / 2) + 7), 8);
 *     
 *     // Initiate the split encode. The JPEG header is written
 *     sceJpegArmEncoderSplitEncode(context, yBuffer, cbBuffer, crBuffer, 0, outBuffer, 0x1000, &bytesWritten);
 *     WriteJPEGData(outBuffer, bytesWritten);
 *     
 *     for (int i = 0; i < height; i++)
 *     {
 *         // Acquire the next row of YUV data
 *         ConvertRGBAScanlineToYUV(rgba, width, i, yBuffer, cbBuffer, crBuffer);
 * 
 *         // Encode the pixel data.
 *         sceJpegArmEncoderSplitEncode(context, yBuffer, cbBuffer, crBuffer, SCE_JPEGENCARM_SPLIT_ENCODE_WRITE_DATA, outBuffer, 0x1000, &bytesWritten);
 *         WriteJPEGData(outBuffer, bytesWritten);
 *     }
 *     
 *     sceJpegArmEncoderEnd(context);
 *     
 *     // Free used buffers
 *     free(outBuffer);
 *     free(yBuffer);
 *     free(cbBuffer);
 *     free(crBuffer);
 *     
 *     FreeColorBuffers();
 * }
 * @endcode
 *
 * @return Encoded JPEG size or 0 on success, < 0 on error.
 */
int sceJpegArmEncoderSplitEncode(SceJpegArmEncoderContext context, const void *yBuffer, const void *cbBuffer, const void *crBuffer, SceUInt32 flags, void *outBuffer, SceSize outSIze, SceUInt32 *bytesWritten);

/**
 * Set the encoder compression ratio.
 *
 * @param[in] context - An already initialized ::SceJpegArmEncoderContext.
 * @param[in] ratio   - A value between 1 and 255 (higher = better compression, lower = better speed).
 *
 * See @ref SCE_JPEGENCARM_DEFAULT_COMP_RATIO for the default compression ratio.
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderSetCompressionRatio(SceJpegArmEncoderContext context, SceUInt8 ratio);

/**
 * Set encoder output address.
 *
 * @param[in] context   - An already initialized ::SceJpegArmEncoderContext.
 * @param[in] outBuffer - A sufficiently sized 8 byte aligned output buffer.
 * @param[in] outSize   - Output buffer size in bytes.
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderSetOutputAddr(SceJpegArmEncoderContext context, void *outBuffer, SceSize outSize);

/**
 * Set the region of the image to be encoded as JPEG. The encoded region starts
 * from (0,0), which is the top left of the image, and expands outward by regionWidth and regionHeight.
 *
 * @param[in] context      - An already initialized ::SceJpegArmEncoderContext.
 * @param[in] regionWidth  - Width of the region in pixels.
 * @param[in] regionHeight - Height of the region in pixels.
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderSetValidRegion(SceJpegArmEncoderContext context, SceUInt16 regionWidth, SceUInt16 regionHeight);

/**
 * Set header used for output file.
 *
 * @param[in] context - An already initialized ::SceJpegArmEncoderContext.
 * @param[in] mode    - One of ::SceJpegArmEncoderHeaderMode.
 *
 * @return 0 on success, < 0 on error.
 */
int sceJpegArmEncoderSetHeaderMode(SceJpegArmEncoderContext context, SceJpegArmEncoderHeaderMode mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_JPEGENCARM_H_ */
