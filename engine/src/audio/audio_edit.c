#include "audio_edit.h"

#include "audio_edit_internal.h"

#include <math.h>
#include <string.h>

static bool edit_channels_valid(u32 channels) {
    return channels == 1u || channels == 2u;
}

static bool edit_range_valid(u32 frames, u32 begin, u32 end) {
    return begin <= end && end <= frames;
}

bool audio_edit_buffer_span(u32 frames, u32 channels, usize *samples, usize *bytes) {
    if (!samples || !bytes || !edit_channels_valid(channels)) return false;
    if ((usize)frames > SIZE_MAX / (usize)channels) return false;
    const usize sample_count = (usize)frames * (usize)channels;
    if (sample_count > SIZE_MAX / sizeof(i16)) return false;
    *samples = sample_count;
    *bytes = sample_count * sizeof(i16);
    return true;
}

static bool edit_input_valid(const i16 *samples, u32 frames, u32 channels) {
    usize sample_count, bytes;
    return audio_edit_buffer_span(frames, channels, &sample_count, &bytes) &&
           (samples || frames == 0u);
}

static i16 edit_scaled(i16 value, double gain) {
    double scaled = (double)value * gain;
    if (scaled > 32767.0) scaled = 32767.0;
    if (scaled < -32768.0) scaled = -32768.0;
    return (i16)nearbyint(scaled);
}

AudioResult audio_edit_trim_i16(i16 *samples, u32 frames, u32 channels,
                                u32 begin, u32 end, u32 *out_frames) {
    if (!out_frames || !edit_input_valid(samples, frames, channels) ||
        !edit_range_valid(frames, begin, end)) {
        return AUDIO_INVALID;
    }
    const u32 kept = end - begin;
    if (kept != 0u) {
        memmove(samples, samples + (usize)begin * channels,
                (usize)kept * channels * sizeof(i16));
    }
    *out_frames = kept;
    return AUDIO_OK;
}

AudioResult audio_edit_cut_i16(i16 *samples, u32 frames, u32 channels,
                               u32 begin, u32 end, u32 *out_frames) {
    if (!out_frames || !edit_input_valid(samples, frames, channels) ||
        !edit_range_valid(frames, begin, end)) {
        return AUDIO_INVALID;
    }
    const u32 tail = frames - end;
    if (tail != 0u) {
        memmove(samples + (usize)begin * channels, samples + (usize)end * channels,
                (usize)tail * channels * sizeof(i16));
    }
    *out_frames = frames - (end - begin);
    return AUDIO_OK;
}

static u32 edit_ramp_frames(double milliseconds, u32 sample_rate, u32 frames) {
    const double rounded = nearbyint(milliseconds * (double)sample_rate / 1000.0);
    if (rounded <= 0.0) return 0u;
    if (rounded >= (double)frames) return frames;
    return (u32)rounded;
}

AudioResult audio_edit_fade_i16(i16 *samples, u32 frames, u32 channels,
                                u32 sample_rate, double fade_in_ms,
                                double fade_out_ms) {
    if (!edit_input_valid(samples, frames, channels) ||
        sample_rate < 8000u || sample_rate > 192000u ||
        !isfinite(fade_in_ms) || !isfinite(fade_out_ms) ||
        fade_in_ms < 0.0 || fade_out_ms < 0.0) {
        return AUDIO_INVALID;
    }
    const u32 in_frames = edit_ramp_frames(fade_in_ms, sample_rate, frames);
    const u32 out_frames = edit_ramp_frames(fade_out_ms, sample_rate, frames);
    for (u32 frame = 0; frame < frames; ++frame) {
        double gain = 1.0;
        if (frame < in_frames && in_frames > 1u) {
            const double in_gain = (double)frame / (double)(in_frames - 1u);
            if (in_gain < gain) gain = in_gain;
        }
        if (frame >= frames - out_frames && out_frames > 1u) {
            const double out_gain = (double)(frames - 1u - frame) / (double)(out_frames - 1u);
            if (out_gain < gain) gain = out_gain;
        }
        for (u32 channel = 0; channel < channels; ++channel) {
            const usize index = (usize)frame * channels + channel;
            samples[index] = edit_scaled(samples[index], gain);
        }
    }
    return AUDIO_OK;
}

AudioResult audio_edit_normalize_i16(i16 *samples, u32 frames, u32 channels,
                                     double target_dbfs) {
    if (!edit_input_valid(samples, frames, channels) ||
        !isfinite(target_dbfs) || target_dbfs < -120.0 || target_dbfs > 0.0) {
        return AUDIO_INVALID;
    }
    usize total, bytes;
    i32 peak = 0;
    if (!audio_edit_buffer_span(frames, channels, &total, &bytes)) return AUDIO_INVALID;
    for (usize i = 0; i < total; ++i) {
        const i32 value = samples[i];
        const i32 magnitude = value < 0 ? -value : value;
        if (magnitude > peak) peak = magnitude;
    }
    if (peak == 0) return AUDIO_OK;
    const double target = pow(10.0, target_dbfs / 20.0) * 32768.0;
    const double gain = target / (double)peak;
    for (usize i = 0; i < total; ++i) samples[i] = edit_scaled(samples[i], gain);
    return AUDIO_OK;
}

AudioResult audio_edit_mix_i16(i16 *dst, u32 dst_frames, const i16 *src,
                               u32 src_frames, u32 channels, double gain) {
    usize dst_samples, dst_bytes, src_samples, src_bytes;
    if (!audio_edit_buffer_span(dst_frames, channels, &dst_samples, &dst_bytes) ||
        !audio_edit_buffer_span(src_frames, channels, &src_samples, &src_bytes) ||
        !isfinite(gain) || gain < -8.0 || gain > 8.0) {
        return AUDIO_INVALID;
    }
    const u32 frames = dst_frames < src_frames ? dst_frames : src_frames;
    if (frames != 0u && (!dst || !src)) return AUDIO_INVALID;
    for (u32 frame = 0; frame < frames; ++frame) {
        for (u32 channel = 0; channel < channels; ++channel) {
            const usize index = (usize)frame * channels + channel;
            double value = (double)dst[index] + (double)src[index] * gain;
            if (value > 32767.0) value = 32767.0;
            if (value < -32768.0) value = -32768.0;
            dst[index] = (i16)nearbyint(value);
        }
    }
    return AUDIO_OK;
}
