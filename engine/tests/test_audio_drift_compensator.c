#include "test_framework.h"

#include <audio/audio_delay_estimator.h>
#include <audio/audio_drift_compensator.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define COMP_STEP_FRAMES 4800u

static AudioDriftCompensatorConfig comp_config(void) {
    AudioDriftCompensatorConfig config;
    config.estimator.window_size = 16u;
    config.estimator.min_abs_correlation = 0.5f;
    config.estimator.max_abs_drift_ppm = 1000.0f;
    config.min_samples = 4u;
    config.max_correction_ppm = 300.0f;
    config.gain = 1.0f;
    config.robust = false;
    return config;
}

static AudioDriftCompensator *make_comp(const AudioDriftCompensatorConfig *config) {
    AudioDriftCompensator *comp = NULL;
    if (audio_drift_compensator_create(config, &comp) != AUDIO_OK) return NULL;
    return comp;
}

/* Delay of the reference resampled with `ratio` against a capture whose
 * clock drifts by `drift` frames per frame: slope 1 - (1 - drift) / ratio. */
static u64 g_frame;

static u32 feed(AudioDriftCompensator *comp, double drift, u32 count, double correlation) {
    const double slope = 1.0 - (1.0 - drift) / audio_drift_compensator_ratio(comp);
    const u64 start = g_frame;
    u32 accepted = 0u;
    for (u32 i = 0u; i < count; ++i) {
        g_frame += COMP_STEP_FRAMES;
        const double delay = 12.0 + slope * (double)(g_frame - start);
        if (audio_drift_compensator_observe(comp, g_frame, delay, correlation)) ++accepted;
    }
    return accepted;
}

TEST(compensator_validates_configuration)
{
    const AudioDriftCompensatorConfig good = comp_config();
    AudioDriftCompensator *comp = (AudioDriftCompensator *)(uintptr_t)1u;
    ASSERT_EQ(audio_drift_compensator_create(NULL, &comp), AUDIO_INVALID);
    ASSERT_EQ(audio_drift_compensator_create(&good, NULL), AUDIO_INVALID);
    AudioDriftCompensatorConfig bad = good;
    bad.min_samples = 1u;
    ASSERT_EQ(audio_drift_compensator_create(&bad, &comp), AUDIO_INVALID);
    bad = good;
    bad.min_samples = good.estimator.window_size + 1u;
    ASSERT_EQ(audio_drift_compensator_create(&bad, &comp), AUDIO_INVALID);
    bad = good;
    bad.max_correction_ppm = 0.5f;
    ASSERT_EQ(audio_drift_compensator_create(&bad, &comp), AUDIO_INVALID);
    bad = good;
    bad.max_correction_ppm = good.estimator.max_abs_drift_ppm + 1.0f;
    ASSERT_EQ(audio_drift_compensator_create(&bad, &comp), AUDIO_INVALID);
    bad = good;
    bad.gain = 0.0f;
    ASSERT_EQ(audio_drift_compensator_create(&bad, &comp), AUDIO_INVALID);
    bad.gain = 1.5f;
    ASSERT_EQ(audio_drift_compensator_create(&bad, &comp), AUDIO_INVALID);
    bad.gain = NAN;
    ASSERT_EQ(audio_drift_compensator_create(&bad, &comp), AUDIO_INVALID);
    bad = good;
    bad.max_correction_ppm = NAN;
    ASSERT_EQ(audio_drift_compensator_create(&bad, &comp), AUDIO_INVALID);
    bad = good;
    bad.estimator.window_size = 1u;
    ASSERT_EQ(audio_drift_compensator_create(&bad, &comp), AUDIO_INVALID);
    ASSERT_TRUE(comp == (AudioDriftCompensator *)(uintptr_t)1u);

    ASSERT_EQ(audio_drift_compensator_ratio(NULL), 0.0);
    ASSERT_EQ(audio_drift_compensator_correction_ppm(NULL), 0.0);
    ASSERT_EQ(audio_drift_compensator_corrections(NULL), 0u);
    ASSERT_EQ(audio_drift_compensator_clamped(NULL), 0u);
    ASSERT_EQ(audio_drift_compensator_output_capacity(NULL, 10u), 0u);
    ASSERT_FALSE(audio_drift_compensator_update(NULL));
    ASSERT_FALSE(audio_drift_compensator_observe(NULL, 1u, 1.0, 1.0));
    u32 frames = 0u;
    i16 sample = 0;
    ASSERT_EQ(audio_drift_compensator_process_i16(NULL, &sample, 1u, &sample, 4u, &frames),
              AUDIO_INVALID);
    audio_drift_compensator_destroy(NULL);
    audio_drift_compensator_reset(NULL);

    comp = make_comp(&good);
    ASSERT_NOT_NULL(comp);
    ASSERT_EQ(audio_drift_compensator_ratio(comp), 1.0);
    ASSERT_EQ(audio_drift_compensator_correction_ppm(comp), 0.0);
    ASSERT_EQ(audio_drift_compensator_corrections(comp), 0u);
    ASSERT_FALSE(audio_drift_compensator_update(comp));
    audio_drift_compensator_destroy(comp);
}

TEST(compensator_converges_on_the_drift)
{
    AudioDriftCompensatorConfig config = comp_config();
    config.gain = 0.5f;
    AudioDriftCompensator *comp = make_comp(&config);
    ASSERT_NOT_NULL(comp);
    g_frame = 0u;
    const double drift = 100e-6;
    for (u32 round = 0u; round < 24u; ++round) {
        ASSERT_EQ(feed(comp, drift, 8u, 0.9), 8u);
        ASSERT_TRUE(audio_drift_compensator_update(comp));
    }
    ASSERT_TRUE(fabs(audio_drift_compensator_ratio(comp) - (1.0 - drift)) < 1e-7);
    ASSERT_TRUE(fabs(audio_drift_compensator_correction_ppm(comp) - 100.0) < 0.1);
    ASSERT_EQ(audio_drift_compensator_corrections(comp), 24u);
    ASSERT_EQ(audio_drift_compensator_clamped(comp), 0u);
    audio_drift_compensator_destroy(comp);

    /* the opposite sign converges the other way, here in one full-gain step */
    config.gain = 1.0f;
    config.robust = true;
    comp = make_comp(&config);
    ASSERT_NOT_NULL(comp);
    ASSERT_EQ(feed(comp, -150e-6, 8u, -0.9), 8u);
    ASSERT_TRUE(audio_drift_compensator_update(comp));
    ASSERT_TRUE(fabs(audio_drift_compensator_ratio(comp) - (1.0 + 150e-6)) < 1e-9);
    ASSERT_TRUE(fabs(audio_drift_compensator_correction_ppm(comp) + 150.0) < 1e-3);
    audio_drift_compensator_destroy(comp);
}

TEST(compensator_limits_the_correction)
{
    const AudioDriftCompensatorConfig config = comp_config();
    AudioDriftCompensator *comp = make_comp(&config);
    ASSERT_NOT_NULL(comp);
    g_frame = 0u;
    for (u32 round = 0u; round < 3u; ++round) {
        ASSERT_EQ(feed(comp, 500e-6, 8u, 0.9), 8u);
        ASSERT_TRUE(audio_drift_compensator_update(comp));
        ASSERT_TRUE(fabs(audio_drift_compensator_ratio(comp) - (1.0 - 300e-6)) < 1e-12);
    }
    ASSERT_EQ(audio_drift_compensator_clamped(comp), 3u);
    ASSERT_EQ(audio_drift_compensator_corrections(comp), 3u);
    audio_drift_compensator_destroy(comp);

    /* a negative drift past the limit stops at the upper bound */
    comp = make_comp(&config);
    ASSERT_NOT_NULL(comp);
    ASSERT_EQ(feed(comp, -500e-6, 8u, 0.9), 8u);
    ASSERT_TRUE(audio_drift_compensator_update(comp));
    ASSERT_TRUE(fabs(audio_drift_compensator_ratio(comp) - (1.0 + 300e-6)) < 1e-12);
    ASSERT_EQ(audio_drift_compensator_clamped(comp), 1u);
    audio_drift_compensator_destroy(comp);
}

TEST(compensator_needs_enough_confident_measurements)
{
    const AudioDriftCompensatorConfig config = comp_config();
    AudioDriftCompensator *comp = make_comp(&config);
    ASSERT_NOT_NULL(comp);
    g_frame = 0u;
    ASSERT_EQ(feed(comp, 100e-6, 6u, 0.2), 0u);
    ASSERT_FALSE(audio_drift_compensator_update(comp));
    ASSERT_EQ(feed(comp, 100e-6, 3u, 0.9), 3u);
    ASSERT_FALSE(audio_drift_compensator_update(comp));
    ASSERT_EQ(audio_drift_compensator_ratio(comp), 1.0);
    ASSERT_EQ(audio_drift_compensator_corrections(comp), 0u);
    /* the fourth makes min_samples; a correction then empties the window */
    ASSERT_EQ(feed(comp, 100e-6, 1u, 0.9), 1u);
    ASSERT_TRUE(audio_drift_compensator_update(comp));
    ASSERT_FALSE(audio_drift_compensator_update(comp));
    ASSERT_EQ(feed(comp, 100e-6, 3u, 0.9), 3u);
    ASSERT_FALSE(audio_drift_compensator_update(comp));
    ASSERT_EQ(audio_drift_compensator_corrections(comp), 1u);
    audio_drift_compensator_destroy(comp);
}

TEST(compensator_resamples_with_the_ratio)
{
    const AudioDriftCompensatorConfig config = comp_config();
    AudioDriftCompensator *comp = make_comp(&config);
    ASSERT_NOT_NULL(comp);
    enum { kInput = 100000 };
    i16 *in = (i16 *)malloc(kInput * sizeof(i16));
    i16 *out = (i16 *)malloc((kInput + 64) * sizeof(i16));
    ASSERT_NOT_NULL(in);
    ASSERT_NOT_NULL(out);
    for (u32 i = 0u; i < (u32)kInput; ++i) in[i] = (i16)((i * 37u) % 2000u) - 1000;
    u32 frames = 0u;
    ASSERT_EQ(audio_drift_compensator_process_i16(comp, in, 1000u, out, kInput + 64u,
                                                  &frames), AUDIO_OK);
    ASSERT_EQ(frames, 1000u);
    for (u32 i = 0u; i < 1000u; ++i) ASSERT_EQ(out[i], in[i]);
    ASSERT_EQ(audio_drift_compensator_process_i16(comp, in, 10u, out, 1u, &frames),
              AUDIO_INVALID);

    g_frame = 0u;
    ASSERT_EQ(feed(comp, 200e-6, 8u, 0.9), 8u);
    ASSERT_TRUE(audio_drift_compensator_update(comp));
    const double ratio = audio_drift_compensator_ratio(comp);
    ASSERT_TRUE(fabs(ratio - (1.0 - 200e-6)) < 1e-9);
    audio_drift_compensator_reset(comp);
    ASSERT_EQ(audio_drift_compensator_ratio(comp), 1.0);
    ASSERT_EQ(feed(comp, 200e-6, 8u, 0.9), 8u);
    ASSERT_TRUE(audio_drift_compensator_update(comp));
    const u32 capacity = audio_drift_compensator_output_capacity(comp, kInput);
    ASSERT_TRUE(capacity >= (u32)ceil(kInput / ratio));
    ASSERT_TRUE(capacity <= (u32)kInput + 64u);
    ASSERT_EQ(audio_drift_compensator_process_i16(comp, in, kInput, out, capacity, &frames),
              AUDIO_OK);
    const double expected = kInput / ratio;
    ASSERT_TRUE(fabs((double)frames - expected) <= 2.0);
    ASSERT_TRUE(frames > (u32)kInput);
    free(in);
    free(out);
    audio_drift_compensator_destroy(comp);
}

TEST(compensator_reset_restores_unit_ratio_and_keeps_counters)
{
    const AudioDriftCompensatorConfig config = comp_config();
    AudioDriftCompensator *comp = make_comp(&config);
    ASSERT_NOT_NULL(comp);
    g_frame = 0u;
    ASSERT_EQ(feed(comp, 500e-6, 8u, 0.9), 8u);
    ASSERT_TRUE(audio_drift_compensator_update(comp));
    ASSERT_EQ(feed(comp, 100e-6, 3u, 0.9), 3u);
    audio_drift_compensator_reset(comp);
    ASSERT_EQ(audio_drift_compensator_ratio(comp), 1.0);
    ASSERT_EQ(audio_drift_compensator_correction_ppm(comp), 0.0);
    ASSERT_EQ(audio_drift_compensator_corrections(comp), 1u);
    ASSERT_EQ(audio_drift_compensator_clamped(comp), 1u);
    /* the window is empty and frame indexes may start over */
    ASSERT_TRUE(audio_drift_compensator_observe(comp, 1u, 0.0, 0.9));
    ASSERT_FALSE(audio_drift_compensator_update(comp));
    audio_drift_compensator_destroy(comp);
}

TEST(compensator_keeps_the_ratio_when_the_estimate_fails)
{
    const AudioDriftCompensatorConfig config = comp_config();
    AudioDriftCompensator *comp = make_comp(&config);
    ASSERT_NOT_NULL(comp);
    g_frame = 0u;
    /* 2000 ppm is beyond the estimator's 1000 ppm limit */
    ASSERT_EQ(feed(comp, 2000e-6, 8u, 0.9), 8u);
    ASSERT_FALSE(audio_drift_compensator_update(comp));
    ASSERT_EQ(audio_drift_compensator_ratio(comp), 1.0);
    ASSERT_EQ(audio_drift_compensator_corrections(comp), 0u);
    ASSERT_EQ(audio_drift_compensator_clamped(comp), 0u);
    audio_drift_compensator_destroy(comp);
}

/* End to end, without the residual-slope model of feed(): a noise reference
 * goes through the compensator, the capture is that reference on a clock
 * drifting by `drift`, and the real delay estimator measures the delay of
 * the resampled reference against the capture. */
#define LOOP_BLOCK 480u
#define LOOP_MEASURE_BLOCKS 10u
#define LOOP_SECONDS 40u
#define LOOP_FRAMES (48000u * LOOP_SECONDS)

static i16 loop_noise(u32 *seed) {
    *seed = *seed * 1664525u + 1013904223u;
    return (i16)((i32)(*seed >> 16) % 16000 - 8000);
}

static double loop_ratio_after(double drift, f32 gain) {
    const u32 source_frames = LOOP_FRAMES + LOOP_FRAMES / 50u;
    i16 *source = (i16 *)malloc(source_frames * sizeof(i16));
    if (!source) return 0.0;
    u32 seed = 0x2468aceu;
    for (u32 i = 0u; i < source_frames; ++i) source[i] = loop_noise(&seed);

    AudioDriftCompensatorConfig config = comp_config();
    config.min_samples = 8u;
    config.gain = gain;
    AudioDriftCompensator *comp = make_comp(&config);
    AudioDelayEstimator *delay = NULL;
    const AudioDelayEstimatorConfig delay_config = {64u, 1024u};
    if (!comp || audio_delay_estimator_create(&delay_config, &delay) != AUDIO_OK) {
        audio_drift_compensator_destroy(comp);
        free(source);
        return 0.0;
    }
    i16 pending[4096];
    u32 pending_frames = 0u;
    u32 source_used = 0u;
    u32 accepted = 0u;
    bool skip_next = false;
    double result = 0.0;
    for (u32 block = 0u; block < LOOP_FRAMES / LOOP_BLOCK; ++block) {
        while (pending_frames < LOOP_BLOCK) {
            u32 produced = 0u;
            const u32 capacity = (u32)(sizeof(pending) / sizeof(pending[0])) - pending_frames;
            if (source_used + LOOP_BLOCK > source_frames ||
                audio_drift_compensator_process_i16(comp, source + source_used, LOOP_BLOCK,
                                                    pending + pending_frames, capacity,
                                                    &produced) != AUDIO_OK) {
                goto done;
            }
            source_used += LOOP_BLOCK;
            pending_frames += produced;
        }
        i16 capture[LOOP_BLOCK];
        for (u32 i = 0u; i < LOOP_BLOCK; ++i) {
            const double n = (double)(block * LOOP_BLOCK + i);
            const double position = (1.0 - drift) * n - 20.0;
            if (position < 0.0) {
                capture[i] = 0;
                continue;
            }
            const u32 whole = (u32)position;
            const double fraction = position - (double)whole;
            capture[i] = (i16)lrint(0.5 * ((1.0 - fraction) * source[whole] +
                                           fraction * source[whole + 1u]));
        }
        audio_delay_estimator_push_i16(delay, pending, capture, LOOP_BLOCK);
        pending_frames -= LOOP_BLOCK;
        memmove(pending, pending + LOOP_BLOCK, pending_frames * sizeof(pending[0]));
        if ((block + 1u) % LOOP_MEASURE_BLOCKS != 0u) continue;
        double measured = 0.0;
        double correlation = 0.0;
        if (!audio_delay_estimator_estimate_subframe(delay, &measured, &correlation)) continue;
        /* the first window after a correction still holds the old ratio */
        if (skip_next) {
            skip_next = false;
            continue;
        }
        if (audio_drift_compensator_observe(comp, (u64)(block + 1u) * LOOP_BLOCK, measured,
                                            correlation) &&
            ++accepted == config.min_samples) {
            accepted = 0u;
            if (audio_drift_compensator_update(comp)) skip_next = true;
        }
    }
    result = audio_drift_compensator_ratio(comp);
done:
    audio_delay_estimator_destroy(delay);
    audio_drift_compensator_destroy(comp);
    free(source);
    return result;
}

TEST(compensator_cancels_drift_measured_by_the_delay_estimator)
{
    const double drifts[] = {100e-6, -150e-6};
    const f32 gains[] = {1.0f, 0.5f};
    for (u32 d = 0u; d < 2u; ++d) {
        for (u32 g = 0u; g < 2u; ++g) {
            const double ratio = loop_ratio_after(drifts[d], gains[g]);
            ASSERT_TRUE(isfinite(ratio));
            ASSERT_TRUE(fabs(ratio - (1.0 - drifts[d])) < 1e-6);
        }
    }
}

TEST_MAIN_BEGIN()
    RUN_TEST(compensator_validates_configuration);
    RUN_TEST(compensator_converges_on_the_drift);
    RUN_TEST(compensator_limits_the_correction);
    RUN_TEST(compensator_needs_enough_confident_measurements);
    RUN_TEST(compensator_resamples_with_the_ratio);
    RUN_TEST(compensator_reset_restores_unit_ratio_and_keeps_counters);
    RUN_TEST(compensator_keeps_the_ratio_when_the_estimate_fails);
    RUN_TEST(compensator_cancels_drift_measured_by_the_delay_estimator);
TEST_MAIN_END()
