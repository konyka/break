# Offline PCM Editing Design

Status: Implemented and validated; remaining limits are listed below

## Purpose

Provide allocation-free, in-place mono/stereo i16 editing primitives for asset tools and future editor panels: trim, cut, fade, peak normalization and mix.

## Scope and approach

Use small deterministic buffer functions with explicit frame counts and failure-atomic outputs. No GUI, timeline, undo integration, file decoding or real-time callback is included.

## API

All functions use mono or stereo interleaved i16 buffers. Zero frames are valid with NULL samples when no data is accessed. Invalid ranges, channels, rates, gains or NULL outputs return `AUDIO_INVALID`.

- `audio_edit_trim_i16(samples,frames,channels,begin,end,&out_frames)`: keep [begin,end), moving it to the buffer start.
- `audio_edit_cut_i16(samples,frames,channels,begin,end,&out_frames)`: remove [begin,end), closing the gap.
- `audio_edit_fade_i16(samples,frames,channels,sample_rate,fade_in_ms,fade_out_ms)`: linear ramps at both ends with minimum-of-two gains. A multi-frame ramp reaches 0 at its outer endpoint and 1 at its inner endpoint; single-frame ramps use unit gain. `sample_rate` is 8000..192000.
- `audio_edit_normalize_i16(samples,frames,channels,target_dbfs)`: scale to the target peak in [-120,0] dBFS, with no wrap; digital silence is unchanged.
- `audio_edit_mix_i16(dst,dst_frames,src,src_frames,channels,gain)`: add gain-scaled source to the common prefix, clamp to i16 and leave the remaining destination unchanged. Gain is finite and in [-8,8]. Source and destination buffers must not overlap.

All arithmetic uses double for scaling; final conversion uses `nearbyint` and clamps where needed. Every buffer span is checked against `SIZE_MAX`, every interleaved index uses `usize`, and fade durations are rounded in double before conversion to a frame count, without narrowing through `long`.

## Tests

1. Every argument family, failure-atomic frame counts and zero-length behavior.
2. Trim/cut on interleaved stereo, including empty, full and interior ranges.
3. Independent fade ramps, stereo equality, zero/long durations and endpoint values.
4. Silence, negative peaks, boost/cut, 0 dBFS and clipping safety.
5. Known mono/stereo mixes, negative gain, clamping, a shorter source prefix and unchanged tails; buffer overlap is outside the contract.

Mutation, ASan+UBSan, strict warnings, independent review and three-tree verification are required before push.

## Limits

No editor UI, project history, undo, media-file parser, effects rack, automation or listening validation. These are buffer-level tools only.
