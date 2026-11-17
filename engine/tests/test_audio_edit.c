/* audio_edit: validation, stereo trim/cut, fades, normalization and mixing. */
#include "test_framework.h"

#include <audio/audio_edit.h>
#include <audio/audio_edit_internal.h>

#include <math.h>
#include <string.h>

static void assert_invalid_range(i16 *samples, u32 frames, u32 channels,
                                 u32 begin, u32 end) {
    u32 out = 99u;
    ASSERT_EQ(audio_edit_trim_i16(samples, frames, channels, begin, end, &out), AUDIO_INVALID);
    ASSERT_EQ(out, 99u);
    ASSERT_EQ(audio_edit_cut_i16(samples, frames, channels, begin, end, &out), AUDIO_INVALID);
    ASSERT_EQ(out, 99u);
}

TEST(validation_and_zero_length_behavior)
{
    i16 samples[8] = {0};
    assert_invalid_range(samples, 4u, 1u, 3u, 2u);
    assert_invalid_range(samples, 4u, 1u, 0u, 5u);
    assert_invalid_range(samples, 4u, 0u, 0u, 1u);
    assert_invalid_range(samples, 4u, 3u, 0u, 1u);
    assert_invalid_range(NULL, 1u, 1u, 0u, 1u);
    ASSERT_EQ(audio_edit_trim_i16(samples, 1u, 1u, 0u, 1u, NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_cut_i16(samples, 1u, 1u, 0u, 1u, NULL), AUDIO_INVALID);
    u32 out = 99u;
    ASSERT_EQ(audio_edit_trim_i16(NULL, 0u, 1u, 0u, 0u, &out), AUDIO_OK);
    ASSERT_EQ(out, 0u);
    ASSERT_EQ(audio_edit_cut_i16(NULL, 0u, 1u, 0u, 0u, &out), AUDIO_OK);
    ASSERT_EQ(out, 0u);
    ASSERT_EQ(audio_edit_fade_i16(samples, 4u, 1u, 16000u, 0.0, 0.0), AUDIO_OK);
    ASSERT_EQ(audio_edit_fade_i16(samples, 4u, 0u, 16000u, 1.0, 1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_fade_i16(samples, 4u, 1u, 7999u, 1.0, 1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_fade_i16(samples, 4u, 1u, 192001u, 1.0, 1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_fade_i16(samples, 4u, 1u, 16000u, -1.0, 1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_fade_i16(samples, 4u, 1u, 16000u, 1.0, -1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_fade_i16(samples, 4u, 1u, 16000u, NAN, 1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_fade_i16(samples, 4u, 1u, 16000u, 1.0, NAN), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_fade_i16(NULL, 1u, 1u, 16000u, 1.0, 1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_normalize_i16(samples, 4u, 1u, -120.1), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_normalize_i16(samples, 4u, 1u, 0.1), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_normalize_i16(samples, 4u, 1u, NAN), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_normalize_i16(NULL, 1u, 1u, 0.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_mix_i16(samples, 4u, samples, 4u, 1u, 8.1), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_mix_i16(samples, 4u, samples, 4u, 1u, -8.1), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_mix_i16(samples, 4u, samples, 4u, 1u, NAN), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_mix_i16(NULL, 1u, samples, 1u, 1u, 1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_mix_i16(samples, 1u, NULL, 1u, 1u, 1.0), AUDIO_INVALID);
    ASSERT_EQ(audio_edit_mix_i16(NULL, 0u, NULL, 0u, 1u, 1.0), AUDIO_OK);
}

TEST(trim_and_cut_are_interleaved_range_operations)
{
    i16 original[16], work[16];
    for (u32 i = 0; i < 16u; ++i) original[i] = (i16)(i * 100);
    memcpy(work, original, sizeof(work));
    u32 out = 0u;
    ASSERT_EQ(audio_edit_trim_i16(work, 8u, 2u, 2u, 5u, &out), AUDIO_OK);
    ASSERT_EQ(out, 3u);
    for (u32 i = 0; i < 6u; ++i) ASSERT_EQ(work[i], original[i + 4u]);
    memcpy(work, original, sizeof(work));
    ASSERT_EQ(audio_edit_cut_i16(work, 8u, 2u, 2u, 5u, &out), AUDIO_OK);
    ASSERT_EQ(out, 5u);
    const i16 expected[] = {0,100,200,300,1000,1100,1200,1300,1400,1500};
    for (u32 i = 0; i < 10u; ++i) ASSERT_EQ(work[i], expected[i]);
    memcpy(work, original, sizeof(work));
    ASSERT_EQ(audio_edit_trim_i16(work, 8u, 2u, 3u, 3u, &out), AUDIO_OK);
    ASSERT_EQ(out, 0u);
    ASSERT_EQ(audio_edit_cut_i16(work, 8u, 2u, 3u, 3u, &out), AUDIO_OK);
    ASSERT_EQ(out, 8u);
    ASSERT_EQ(memcmp(work, original, sizeof(work)), 0);
    out = 99u;
    ASSERT_EQ(audio_edit_cut_i16(work, 8u, 2u, 4u, 3u, &out), AUDIO_INVALID);
    ASSERT_EQ(out, 99u);
    ASSERT_EQ(memcmp(work, original, sizeof(work)), 0);
    ASSERT_EQ(audio_edit_trim_i16(work, 8u, 2u, 0u, 8u, &out), AUDIO_OK);
    ASSERT_EQ(out, 8u);
    ASSERT_EQ(memcmp(work, original, sizeof(work)), 0);
    ASSERT_EQ(audio_edit_cut_i16(work, 8u, 2u, 0u, 8u, &out), AUDIO_OK);
    ASSERT_EQ(out, 0u);
}

TEST(linear_fades_have_known_endpoints_and_stereo_gain)
{
    i16 samples[8], stereo[16];
    for (u32 i = 0; i < 8u; ++i) samples[i] = 1000;
    ASSERT_EQ(audio_edit_fade_i16(samples, 8u, 1u, 16000u, 0.25, 0.25), AUDIO_OK);
    const i16 expected[] = {0,333,667,1000,1000,667,333,0};
    for (u32 i = 0; i < 8u; ++i) ASSERT_EQ(samples[i], expected[i]);
    for (u32 i = 0; i < 16u; ++i) stereo[i] = 1000;
    ASSERT_EQ(audio_edit_fade_i16(stereo, 8u, 2u, 16000u, 0.25, 0.25), AUDIO_OK);
    for (u32 i = 0; i < 8u; ++i) {
        ASSERT_EQ(stereo[2u * i], samples[i]);
        ASSERT_EQ(stereo[2u * i + 1u], samples[i]);
    }
    memcpy(samples, expected, sizeof(samples));
    ASSERT_EQ(audio_edit_fade_i16(samples, 8u, 1u, 16000u, 0.0, 0.0), AUDIO_OK);
    ASSERT_EQ(memcmp(samples, expected, sizeof(samples)), 0);
    for (u32 i = 0; i < 8u; ++i) samples[i] = 1000;
    ASSERT_EQ(audio_edit_fade_i16(samples, 8u, 1u, 16000u, 0.25, 0.0), AUDIO_OK);
    const i16 fade_in[] = {0,333,667,1000,1000,1000,1000,1000};
    for (u32 i = 0; i < 8u; ++i) ASSERT_EQ(samples[i], fade_in[i]);
    for (u32 i = 0; i < 8u; ++i) samples[i] = 1000;
    ASSERT_EQ(audio_edit_fade_i16(samples, 8u, 1u, 16000u, 0.0, 0.25), AUDIO_OK);
    const i16 fade_out[] = {1000,1000,1000,1000,1000,667,333,0};
    for (u32 i = 0; i < 8u; ++i) ASSERT_EQ(samples[i], fade_out[i]);
    ASSERT_EQ(audio_edit_fade_i16(NULL, 0u, 1u, 16000u, 1.0, 1.0), AUDIO_OK);
    for (u32 i = 0; i < 8u; ++i) samples[i] = 1000;
    ASSERT_EQ(audio_edit_fade_i16(samples, 8u, 1u, 16000u, 1000.0, 1000.0), AUDIO_OK);
    ASSERT_EQ(samples[0], 0);
    ASSERT_EQ(samples[7], 0);
    ASSERT_EQ(audio_edit_fade_i16(samples, 1u, 1u, 16000u, 1.0, 1.0), AUDIO_OK);
}

TEST(normalize_uses_peak_without_wrapping)
{
    i16 silence[4] = {0};
    ASSERT_EQ(audio_edit_normalize_i16(silence, 4u, 1u, 0.0), AUDIO_OK);
    for (u32 i = 0; i < 4u; ++i) ASSERT_EQ(silence[i], 0);
    i16 samples[] = {1000,500,-1000,200};
    ASSERT_EQ(audio_edit_normalize_i16(samples, 4u, 1u, 0.0), AUDIO_OK);
    i32 peak = 0;
    for (u32 i = 0; i < 4u; ++i) {
        const i32 magnitude = samples[i] < 0 ? -samples[i] : samples[i];
        if (magnitude > peak) peak = magnitude;
    }
    ASSERT_TRUE(peak == 32767 || peak == 32768);
    ASSERT_EQ(samples[0], 32767);
    ASSERT_EQ(samples[1], 16384);
    ASSERT_EQ(samples[2], -32768);
    i16 negative[] = {100,500,-1000,200};
    ASSERT_EQ(audio_edit_normalize_i16(negative, 4u, 1u, 0.0), AUDIO_OK);
    ASSERT_EQ(negative[0], 3277);
    ASSERT_EQ(negative[1], 16384);
    ASSERT_EQ(negative[2], -32768);
    ASSERT_EQ(audio_edit_normalize_i16(samples, 4u, 1u, -20.0), AUDIO_OK);
    peak = 0;
    for (u32 i = 0; i < 4u; ++i) {
        const i32 magnitude = samples[i] < 0 ? -samples[i] : samples[i];
        if (magnitude > peak) peak = magnitude;
    }
    const double target = pow(10.0, -20.0 / 20.0) * 32768.0;
    ASSERT_TRUE(fabs((double)peak - target) <= 1.0);
    i16 mono[] = {1000,-500,500,-1000};
    i16 stereo[] = {1000,-500,500,-1000};
    ASSERT_EQ(audio_edit_normalize_i16(mono, 4u, 1u, -20.0), AUDIO_OK);
    ASSERT_EQ(audio_edit_normalize_i16(stereo, 2u, 2u, -20.0), AUDIO_OK);
    ASSERT_EQ(memcmp(mono, stereo, sizeof(mono)), 0);
    ASSERT_EQ(audio_edit_normalize_i16(NULL, 0u, 1u, 0.0), AUDIO_OK);
}

TEST(mix_is_gain_scaled_clamped_and_limited_to_the_prefix)
{
    i16 dst[] = {1000,1000,1000,-1000,777};
    const i16 src[] = {100,200,300,-400};
    ASSERT_EQ(audio_edit_mix_i16(dst, 5u, src, 4u, 1u, 2.0), AUDIO_OK);
    const i16 expected[] = {1200,1400,1600,-1800,777};
    ASSERT_EQ(memcmp(dst, expected, sizeof(dst)), 0);
    dst[0] = 20000;
    ASSERT_EQ(audio_edit_mix_i16(dst, 1u, (i16[]){20000}, 1u, 1u, 2.0), AUDIO_OK);
    ASSERT_EQ(dst[0], 32767);
    dst[0] = -20000;
    ASSERT_EQ(audio_edit_mix_i16(dst, 1u, (i16[]){20000}, 1u, 1u, -2.0), AUDIO_OK);
    ASSERT_EQ(dst[0], -32768);
    dst[0] = 1001;
    ASSERT_EQ(audio_edit_mix_i16(dst, 1u, (i16[]){1}, 1u, 1u, 0.5), AUDIO_OK);
    ASSERT_EQ(dst[0], 1002);
    i16 dst_stereo[] = {100,200,300,400};
    const i16 src_stereo[] = {10,20,30,40};
    ASSERT_EQ(audio_edit_mix_i16(dst_stereo, 2u, src_stereo, 2u, 2u, 2.0), AUDIO_OK);
    const i16 stereo_expected[] = {120,240,360,480};
    ASSERT_EQ(memcmp(dst_stereo, stereo_expected, sizeof(dst_stereo)), 0);
    ASSERT_EQ(audio_edit_mix_i16(dst, 1u, NULL, 0u, 1u, 1.0), AUDIO_OK);
}

TEST(buffer_spans_are_checked_without_overflow)
{
    usize samples = 0u, bytes = 0u;
    ASSERT_TRUE(audio_edit_buffer_span(4u, 2u, &samples, &bytes));
    ASSERT_EQ(samples, 8u);
    ASSERT_EQ(bytes, 16u);
    ASSERT_TRUE(audio_edit_buffer_span(0u, 1u, &samples, &bytes));
    ASSERT_EQ(samples, 0u);
    ASSERT_EQ(bytes, 0u);
    ASSERT_TRUE(!audio_edit_buffer_span(1u, 0u, &samples, &bytes));
    ASSERT_TRUE(!audio_edit_buffer_span(1u, 1u, NULL, &bytes));
    ASSERT_TRUE(!audio_edit_buffer_span(1u, 1u, &samples, NULL));
    const bool fits = SIZE_MAX / 2u >= UINT32_MAX && SIZE_MAX / 4u >= UINT32_MAX;
    ASSERT_EQ(audio_edit_buffer_span(UINT32_MAX, 2u, &samples, &bytes), fits);
    if (fits) {
        ASSERT_EQ(samples, (usize)UINT32_MAX * 2u);
        ASSERT_EQ(bytes, (usize)UINT32_MAX * 4u);
    }
}

TEST_MAIN_BEGIN()
    RUN_TEST(buffer_spans_are_checked_without_overflow);
    RUN_TEST(validation_and_zero_length_behavior);
    RUN_TEST(trim_and_cut_are_interleaved_range_operations);
    RUN_TEST(linear_fades_have_known_endpoints_and_stereo_gain);
    RUN_TEST(normalize_uses_peak_without_wrapping);
    RUN_TEST(mix_is_gain_scaled_clamped_and_limited_to_the_prefix);
TEST_MAIN_END()
