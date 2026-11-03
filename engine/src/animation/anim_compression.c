#include <animation/anim_compression.h>
#include <math.h>
#include <string.h>

static u16 read_u16(const u8 *p) {
    return (u16)((u16)p[0] | ((u16)p[1] << 8));
}

static u32 read_u32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

static f32 read_f32(const u8 *p) {
    u32 bits = read_u32(p);
    f32 value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

static void write_u16(u8 *p, u16 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8);
}

static void write_u32(u8 *p, u32 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8);
    p[2] = (u8)(value >> 16);
    p[3] = (u8)(value >> 24);
}

static void write_f32(u8 *p, f32 value) {
    u32 bits;
    memcpy(&bits, &value, sizeof(bits));
    write_u32(p, bits);
}

static u32 codec_crc32_update(u32 crc, const u8 *data, usize size) {
    for (usize i = 0; i < size; ++i) {
        crc ^= data[i];
        for (u32 bit = 0; bit < 8u; ++bit)
            crc = (crc >> 1) ^ (0xEDB88320u & (u32)-(i32)(crc & 1u));
    }
    return crc;
}

static u32 codec_stream_crc32(const u8 *data, usize size) {
    u32 crc = codec_crc32_update(UINT32_MAX, data, 28u);
    crc = codec_crc32_update(crc, data + ANIM_CODEC_HEADER_BYTES,
                             size - ANIM_CODEC_HEADER_BYTES);
    return ~crc;
}

static u16 quantize_unit(double value) {
    if (value <= 0.0) return 0u;
    if (value >= 1.0) return ANIM_CODEC_QUANT_STEPS;
    return (u16)floor(value * (double)ANIM_CODEC_QUANT_STEPS + 0.5);
}

static double dequantize_unit(u16 value) {
    return (double)value / (double)ANIM_CODEC_QUANT_STEPS;
}

static bool normalize_quaternion(const f32 input[4], f32 output[4]) {
    f32 length_sq = input[0] * input[0] + input[1] * input[1] +
                    input[2] * input[2] + input[3] * input[3];
    if (!(length_sq > 0.0f) || !isfinite(length_sq)) return false;
    f32 inverse_length = 1.0f / sqrtf(length_sq);
    for (u32 a = 0; a < 4u; ++a) output[a] = input[a] * inverse_length;
    return true;
}

static AnimCodecResult source_layout(const AnimClip *clip, u32 joint_count,
                                     usize *out_size) {
    if (!clip || !out_size || joint_count == 0u || joint_count > SKELETON_MAX_JOINTS ||
        clip->channel_count > SKELETON_MAX_CHANNELS || clip->event_count != 0u ||
        !isfinite(clip->duration) || clip->duration < 0.0f) return ANIM_CODEC_INVALID;
    usize size = ANIM_CODEC_HEADER_BYTES;
    for (u32 c = 0; c < clip->channel_count; ++c) {
        const AnimChannel *channel = &clip->channels[c];
        bool path_valid = channel->path == ANIM_PATH_TRANSLATION ||
                          channel->path == ANIM_PATH_ROTATION ||
                          channel->path == ANIM_PATH_SCALE;
        bool interp_valid = channel->interp == ANIM_INTERP_LINEAR ||
                            channel->interp == ANIM_INTERP_STEP;
        if (channel->joint_index >= joint_count ||
            channel->keyframe_count > SKELETON_MAX_KEYFRAMES ||
            !path_valid || !interp_valid) return ANIM_CODEC_INVALID;
        u32 components = channel->path == ANIM_PATH_ROTATION ? 4u : 3u;
        f32 min_value[3] = {0.0f, 0.0f, 0.0f};
        f32 max_value[3] = {0.0f, 0.0f, 0.0f};
        for (u32 k = 0; k < channel->keyframe_count; ++k) {
            f32 time = channel->times[k];
            if (!isfinite(time) || time < 0.0f || time > clip->duration ||
                (k > 0u && time < channel->times[k - 1u])) return ANIM_CODEC_INVALID;
            if (channel->path == ANIM_PATH_ROTATION) {
                f32 normalized[4];
                if (!normalize_quaternion(channel->values[k], normalized))
                    return ANIM_CODEC_INVALID;
            } else {
                for (u32 a = 0; a < 3u; ++a) {
                    f32 value = channel->values[k][a];
                    if (!isfinite(value)) return ANIM_CODEC_INVALID;
                    if (k == 0u || value < min_value[a]) min_value[a] = value;
                    if (k == 0u || value > max_value[a]) max_value[a] = value;
                }
            }
        }
        if (channel->path != ANIM_PATH_ROTATION)
            for (u32 a = 0; a < 3u; ++a)
                if (!isfinite(max_value[a] - min_value[a])) return ANIM_CODEC_INVALID;
        size += ANIM_CODEC_CHANNEL_HEADER_BYTES +
                (usize)channel->keyframe_count * (2u + components * 2u);
    }
    *out_size = size;
    return ANIM_CODEC_OK;
}

AnimCodecResult anim_codec_encoded_size(const AnimClip *clip, u32 joint_count,
                                        usize *out_size) {
    return source_layout(clip, joint_count, out_size);
}

AnimCodecResult anim_codec_encode(const AnimClip *clip, u32 joint_count,
                                  u8 *out, usize out_capacity, usize *out_size) {
    if (!out_size) return ANIM_CODEC_INVALID;
    usize required = 0u;
    AnimCodecResult layout = source_layout(clip, joint_count, &required);
    if (layout != ANIM_CODEC_OK) return layout;
    *out_size = required;
    if (out_capacity < required) return ANIM_CODEC_CAPACITY;
    if (!out) return ANIM_CODEC_INVALID;

    out[0] = 'B'; out[1] = 'A'; out[2] = 'N'; out[3] = 'M';
    write_u16(out + 4, ANIM_CODEC_VERSION);
    write_u16(out + 6, ANIM_CODEC_HEADER_BYTES);
    write_u32(out + 8, (u32)required);
    write_u16(out + 12, (u16)joint_count);
    write_u16(out + 14, (u16)clip->channel_count);
    write_f32(out + 16, clip->duration);
    write_u32(out + 20, (clip->loop ? 1u : 0u) | (clip->playing ? 2u : 0u));
    write_u32(out + 24, (u32)(required - ANIM_CODEC_HEADER_BYTES));

    u8 *cursor = out + ANIM_CODEC_HEADER_BYTES;
    for (u32 c = 0; c < clip->channel_count; ++c) {
        const AnimChannel *channel = &clip->channels[c];
        f32 min_value[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        f32 max_value[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        u32 components = channel->path == ANIM_PATH_ROTATION ? 4u : 3u;
        if (channel->path == ANIM_PATH_ROTATION) {
            for (u32 a = 0; a < 4u; ++a) {
                min_value[a] = -1.0f;
                max_value[a] = 1.0f;
            }
        } else if (channel->keyframe_count > 0u) {
            for (u32 a = 0; a < 3u; ++a) {
                min_value[a] = channel->values[0][a];
                max_value[a] = channel->values[0][a];
            }
            for (u32 k = 1; k < channel->keyframe_count; ++k)
                for (u32 a = 0; a < 3u; ++a) {
                    if (channel->values[k][a] < min_value[a]) min_value[a] = channel->values[k][a];
                    if (channel->values[k][a] > max_value[a]) max_value[a] = channel->values[k][a];
                }
        }
        write_u16(cursor, (u16)channel->joint_index);
        cursor[2] = (u8)channel->path;
        cursor[3] = (u8)channel->interp;
        write_u16(cursor + 4, (u16)channel->keyframe_count);
        write_u16(cursor + 6, 0u);
        for (u32 a = 0; a < 4u; ++a) {
            write_f32(cursor + 8u + a * 4u, min_value[a]);
            write_f32(cursor + 24u + a * 4u, max_value[a]);
        }
        cursor += ANIM_CODEC_CHANNEL_HEADER_BYTES;
        for (u32 k = 0; k < channel->keyframe_count; ++k) {
            double time_unit = clip->duration > 0.0f ?
                               (double)channel->times[k] / (double)clip->duration : 0.0;
            write_u16(cursor, quantize_unit(time_unit));
            cursor += 2;
            f32 quaternion[4];
            if (channel->path == ANIM_PATH_ROTATION &&
                !normalize_quaternion(channel->values[k], quaternion)) return ANIM_CODEC_INVALID;
            for (u32 a = 0; a < components; ++a) {
                double value = channel->path == ANIM_PATH_ROTATION ?
                               (double)quaternion[a] : (double)channel->values[k][a];
                double range = (double)max_value[a] - (double)min_value[a];
                double unit = range > 0.0 ?
                              (value - (double)min_value[a]) / range : 0.0;
                write_u16(cursor, quantize_unit(unit));
                cursor += 2;
            }
        }
    }
    write_u32(out + 28, codec_stream_crc32(out, required));
    return ANIM_CODEC_OK;
}

static AnimCodecResult decode_pass(const u8 *data, usize size, AnimClip *out, bool write) {
    if (size < ANIM_CODEC_HEADER_BYTES || size > ANIM_CODEC_MAX_BYTES ||
        data[0] != 'B' || data[1] != 'A' || data[2] != 'N' || data[3] != 'M')
        return ANIM_CODEC_CORRUPT;
    if (read_u16(data + 4) != ANIM_CODEC_VERSION) return ANIM_CODEC_VERSION_UNSUPPORTED;
    if (read_u16(data + 6) != ANIM_CODEC_HEADER_BYTES ||
        read_u32(data + 8) != size ||
        read_u32(data + 24) != size - ANIM_CODEC_HEADER_BYTES)
        return ANIM_CODEC_CORRUPT;
    if (codec_stream_crc32(data, size) != read_u32(data + 28))
        return ANIM_CODEC_CORRUPT;
    u32 joint_count = read_u16(data + 12);
    u32 channel_count = read_u16(data + 14);
    u32 flags = read_u32(data + 20);
    f32 duration = read_f32(data + 16);
    if (joint_count == 0u || joint_count > SKELETON_MAX_JOINTS ||
        channel_count > SKELETON_MAX_CHANNELS || (flags & ~3u) != 0u ||
        !isfinite(duration) || duration < 0.0f) return ANIM_CODEC_CORRUPT;
    if (write) {
        memset(out, 0, sizeof(*out));
        out->duration = duration;
        out->loop = (flags & 1u) != 0u;
        out->playing = (flags & 2u) != 0u;
        out->channel_count = channel_count;
    }
    const u8 *cursor = data + ANIM_CODEC_HEADER_BYTES;
    const u8 *end = data + size;
    for (u32 c = 0; c < channel_count; ++c) {
        if ((usize)(end - cursor) < ANIM_CODEC_CHANNEL_HEADER_BYTES) return ANIM_CODEC_CORRUPT;
        u32 joint = read_u16(cursor);
        u32 path = cursor[2];
        u32 interp = cursor[3];
        u32 key_count = read_u16(cursor + 4);
        if (joint >= joint_count || path > ANIM_PATH_SCALE || interp > ANIM_INTERP_STEP ||
            key_count > SKELETON_MAX_KEYFRAMES || read_u16(cursor + 6) != 0u)
            return ANIM_CODEC_CORRUPT;
        f32 min_value[4];
        f32 max_value[4];
        for (u32 a = 0; a < 4u; ++a) {
            min_value[a] = read_f32(cursor + 8u + a * 4u);
            max_value[a] = read_f32(cursor + 24u + a * 4u);
            if (!isfinite(min_value[a]) || !isfinite(max_value[a]) ||
                min_value[a] > max_value[a] ||
                !isfinite(max_value[a] - min_value[a])) return ANIM_CODEC_CORRUPT;
            if (path == ANIM_PATH_ROTATION &&
                (min_value[a] != -1.0f || max_value[a] != 1.0f))
                return ANIM_CODEC_CORRUPT;
        }
        if (write) {
            AnimChannel *channel = &out->channels[c];
            channel->joint_index = joint;
            channel->path = (AnimPathType)path;
            channel->interp = (AnimInterp)interp;
            channel->keyframe_count = key_count;
        }
        cursor += ANIM_CODEC_CHANNEL_HEADER_BYTES;
        u32 components = path == ANIM_PATH_ROTATION ? 4u : 3u;
        usize record_bytes = (usize)key_count * (2u + components * 2u);
        if ((usize)(end - cursor) < record_bytes) return ANIM_CODEC_CORRUPT;
        u16 previous_time = 0u;
        for (u32 k = 0; k < key_count; ++k) {
            u16 quantized_time = read_u16(cursor);
            if (k > 0u && quantized_time < previous_time) return ANIM_CODEC_CORRUPT;
            previous_time = quantized_time;
            f32 time = (f32)((double)duration * dequantize_unit(quantized_time));
            cursor += 2;
            f32 values[4] = {0.0f, 0.0f, 0.0f, 0.0f};
            for (u32 a = 0; a < components; ++a) {
                values[a] = (f32)((double)min_value[a] +
                    ((double)max_value[a] - (double)min_value[a]) *
                    dequantize_unit(read_u16(cursor)));
                cursor += 2;
            }
            if (path == ANIM_PATH_ROTATION) {
                f32 normalized[4];
                if (!normalize_quaternion(values, normalized)) return ANIM_CODEC_CORRUPT;
                memcpy(values, normalized, sizeof(values));
            }
            if (!isfinite(time)) return ANIM_CODEC_CORRUPT;
            for (u32 a = 0; a < components; ++a)
                if (!isfinite(values[a])) return ANIM_CODEC_CORRUPT;
            if (write) {
                out->channels[c].times[k] = time;
                memcpy(out->channels[c].values[k], values, sizeof(values));
            }
        }
    }
    return cursor == end ? ANIM_CODEC_OK : ANIM_CODEC_CORRUPT;
}

AnimCodecResult anim_codec_decode(const void *data, usize size, AnimClip *out) {
    if (!data || !out) return ANIM_CODEC_INVALID;
    AnimCodecResult result = decode_pass((const u8 *)data, size, NULL, false);
    if (result != ANIM_CODEC_OK) return result;
    return decode_pass((const u8 *)data, size, out, true);
}

static f32 codec_error_bound(double quantization_step, double magnitude) {
    double bound = quantization_step / (2.0 * (double)ANIM_CODEC_QUANT_STEPS) +
                   fabs(magnitude) * 0x1p-23 + 0x1p-149;
    return nextafterf((f32)bound, INFINITY);
}

f32 anim_codec_time_error_bound(f32 duration) {
    return codec_error_bound(fabs((double)duration), fabs((double)duration));
}

f32 anim_codec_scalar_error_bound(f32 min_value, f32 max_value) {
    double range = fabs((double)max_value - (double)min_value);
    double magnitude = fmax(fabs((double)min_value), fabs((double)max_value));
    return codec_error_bound(range, magnitude);
}
