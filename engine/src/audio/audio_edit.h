#pragma once
/* Offline mono/stereo i16 editing: trim, cut, linear fades, peak normalization
 * and clamped prefix mixing (docs/design/audio_extended.md, "Offline editing").
 * In place, no allocation, file I/O or editor-state dependency. */

#include <audio/audio.h>

/* Keep [begin,end) at the buffer start and set *out_frames to its length. */
AudioResult audio_edit_trim_i16(i16 *samples, u32 frames, u32 channels,
                                u32 begin, u32 end, u32 *out_frames);
/* Remove [begin,end), close the gap and set *out_frames to the new length. */
AudioResult audio_edit_cut_i16(i16 *samples, u32 frames, u32 channels,
                               u32 begin, u32 end, u32 *out_frames);
/* Linear fades at both ends. Multi-frame ramps reach zero at the outer
 * endpoint; zero-duration ramps are no-ops. sample_rate is 8000..192000. */
AudioResult audio_edit_fade_i16(i16 *samples, u32 frames, u32 channels,
                                u32 sample_rate, double fade_in_ms,
                                double fade_out_ms);
/* Scale to target peak in [-120,0] dBFS; silence is unchanged. */
AudioResult audio_edit_normalize_i16(i16 *samples, u32 frames, u32 channels,
                                     double target_dbfs);
/* Add gain-scaled source to the common prefix. Gain is finite and in [-8,8];
 * destination samples beyond the prefix are unchanged. dst and src buffers
 * must not overlap. */
AudioResult audio_edit_mix_i16(i16 *dst, u32 dst_frames, const i16 *src,
                               u32 src_frames, u32 channels, double gain);
