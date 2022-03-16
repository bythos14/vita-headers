/**
 * \usergroup{SceG729}
 * \internalusage{psp2/g729.h,SceLibG729_stub,SCE_SYSMODULE_INTERNAL_G729}
 */

#ifndef _PSP2_G729_H_
#define _PSP2_G729_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Error Codes
 */
typedef enum SceG729ErrorCode {
    SCE_G729_ERROR_INVALID_ARG             = 0x80680001,
    SCE_G729_ERROR_CONTEXT_NOT_INITIALIZED = 0x80680002
} SceG729ErrorCode;

/**
 * Opaque Decode Context
 * 
 * @note Memory for the context must be 4 byte aligned
 */
typedef void *SceG729DecodeContext;
/**
 * Opaque Encode Context
 * 
 * @note Memory for the context must be 4 byte aligned
 */
typedef void* SceG729EncodeContext;

typedef enum SceG729EncodeMode {
    SCE_G729_ENCODE_MODE_G729D,  //!< Low bitrate (6.4kbps/G.729 Annex D)
    SCE_G729_ENCODE_MODE_G729,   //!< Normal bitrate (8.0kbps/G.729)
    SCE_G729_ENCODE_MODE_G729E,  //!< High bitrate (11.8kbps/G.729 Annex E)
} SceG729EncodeMode;

/**
 * DTX Modes for the encoder.
 */
typedef enum SceG729DTXMode {
    SCE_G729_DTX_DISABLE, //!< No DTX.
    SCE_G729_DTX_ENABLE   //!< DTX active, SID and DTX frames(0kbps) can be generated.
} SceG729DTXMode;

/**
 * Defines the possible sizes of a 10ms G.729 frame in bits.
 * 
 * Is output by the encoder, and used as input by the decoder.
 */
typedef enum SceG729Rate {
    SCE_G729_RATE_0     = 0,   //!< DTX eliminated frame
    SCE_G729_RATE_SID   = 15,  //!< SID frame (1.6kbps)
    SCE_G729_RATE_6400  = 64,  //!< Low bitrate frame(6.4kbps/G.729 Annex D)
    SCE_G729_RATE_8000  = 80,  //!< Normal bitrate frame(8.0kbps/G.729)
    SCE_G729_RATE_11800 = 118, //!< High bitrate frame(11.8kbps/G.729 Annex E)
} SceG729Rate;

/**
 * State of an input frame to the decoder.
 */
typedef enum SceG729FrameState {
    SCE_G729_FRAME_ACTIVE, //!< The frame is active and will be processed as normal.
    SCE_G729_FRAME_ERASED  //!< The frame is erased.
} SceG729FrameState;

/**
 * Get the required size of an decode context.
 *
 * @return Size in bytes.
 */
SceSize sceG729DecodeGetContextSize();
/**
 * Initialise a decode context.
 * 
 * @param[in] context    - Context to initialize
 * 
 * @return 0 on success, <0 on error 
 */
int sceG729DecodeInit(SceG729DecodeContext context);
/**
 * Reset a decode context.
 * 
 * @param context - Context to reset.
 * 
 * @return 0 on success, <0 on error
 */
int sceG729DecodeReset(SceG729DecodeContext context);
/**
 * Decode a G.729 bitstream to output PCM.
 * 
 * @param[in]  context    - Decode context.
 * @param[in]  rate       - One of ::SceG729Rate.
 * @param[in]  frameState - One of ::SceG729FrameState.
 * @param[in]  bitstream  - Input G.729 bitstream.
 * @param[out] speech     - Output 10ms 8kHz PCM frame.
 * 
 * @return rate on success, <0 on error
 */
int sceG729DecodeCore(SceG729DecodeContext context, SceG729Rate rate, SceG729FrameState frameState, SceUInt8 *bitstream, SceUInt16 *speech);

/**
 * Get the required size of an encode context.
 *
 * @return Size in bytes.
 */
SceSize sceG729EncodeGetContextSize();
/**
 * Initialise an encode context.
 * 
 * @param[in] context    - Context to initialize.
 * @param[in] encodeMode - One of ::SceG729EncodeMode
 * @param[in] dtxMode    - One of ::SceG729DTXMode.
 * 
 * @return 0 on success, <0 on error 
 */
int sceG729EncodeInit(SceG729EncodeContext context, SceG729EncodeMode encodeMode, SceG729DTXMode dtxMode);
/**
 * Reset an encode context.
 * 
 * @param context - Context to reset.
 * 
 * @return 0 on success, <0 on error
 */
int sceG729EncodeReset(SceG729EncodeContext context);
/**
 * Encode a G.729 bitstream from an input PCM.
 * 
 * @param[in]  context   - Encode context.
 * @param[in]  speech    - Input 10ms 8kHz PCM frame.
 * @param[out] bitstream - Output G.729 bitsream.
 * 
 * @return One of ::SceG729Rate on success, <0 on error
 */
int sceG729EncodeCore(SceG729EncodeContext context, SceUInt16 *speech, SceUInt8 *bitstream);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PSP2_JPEGENCARM_H_ */