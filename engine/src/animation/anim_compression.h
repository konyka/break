#pragma once

#include <animation/skeleton.h>

#define ANIM_CODEC_VERSION 1u
#define ANIM_CODEC_QUANT_STEPS 65535u
#define ANIM_CODEC_HEADER_BYTES 32u
#define ANIM_CODEC_CHANNEL_HEADER_BYTES 40u
#define ANIM_CODEC_MAX_BYTES (ANIM_CODEC_HEADER_BYTES + \
    SKELETON_MAX_CHANNELS * (ANIM_CODEC_CHANNEL_HEADER_BYTES + \
    SKELETON_MAX_KEYFRAMES * 10u))
#define ANIM_CODEC_ROTATION_ERROR_BOUND 0.0001f

typedef enum {
    ANIM_CODEC_OK = 0,
    ANIM_CODEC_INVALID,
    ANIM_CODEC_CAPACITY,
    ANIM_CODEC_CORRUPT,
    ANIM_CODEC_VERSION_UNSUPPORTED
} AnimCodecResult;

AnimCodecResult anim_codec_encoded_size(const AnimClip *clip, u32 joint_count,
                                        usize *out_size);
AnimCodecResult anim_codec_encode(const AnimClip *clip, u32 joint_count,
                                  u8 *out, usize out_capacity, usize *out_size);
AnimCodecResult anim_codec_decode(const void *data, usize size, AnimClip *out);
f32 anim_codec_time_error_bound(f32 duration);
f32 anim_codec_scalar_error_bound(f32 min_value, f32 max_value);
