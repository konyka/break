/* audio_echo_canceller: validation, convergence on a known echo path,
 * silent reference, double talk, path change, reset, chunking and an
 * independent reference model. */
#include "test_framework.h"

#include <audio/audio_echo_canceller.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define RATE 48000u
#define TAPS 32u
#define FRAMES RATE

static const double kPi = 3.14159265358979323846;
static u32 g_seed = 0x2468ACEu;

static AudioEchoCancellerConfig aec_config(void) {
    AudioEchoCancellerConfig config;
    memset(&config, 0, sizeof(config));
    config.sample_rate = RATE;
    config.taps = TAPS;
    config.step_size = 0.5f;
    config.double_talk_threshold = 0.5f;
    config.hangover_ms = 20.0f;
    return config;
}

/* uniform noise with RMS `dbfs` */
static i16 noise(double dbfs) {
    g_seed = g_seed * 1664525u + 1013904223u;
    double u = (double)(g_seed >> 8) / 8388608.0 - 1.0;
    return (i16)lrint(u * sqrt(3.0) * pow(10.0, dbfs / 20.0) * 32767.0);
}

/* echo of `ref` through taps (delay, gain) pairs, plus a near-side 440 Hz
 * tone with RMS `tone_db` when it is above -200 */
typedef struct { u32 delay; double gain; } Tap;

static void make_capture(const i16 *ref, i16 *cap, u32 frames, const Tap *path, u32 count,
                         double tone_db) {
    for (u32 n = 0; n < frames; ++n) {
        double v = 0.0;
        for (u32 i = 0; i < count; ++i) {
            if (n >= path[i].delay) v += path[i].gain * ref[n - path[i].delay];
        }
        if (tone_db > -200.0) {
            v += sqrt(2.0) * pow(10.0, tone_db / 20.0) * 32767.0 *
                 sin(2.0 * kPi * 440.0 * (double)n / RATE);
        }
        cap[n] = (i16)lrint(v);
    }
}

static double power_db(const i16 *x, u32 n) {
    double sum = 0.0;
    for (u32 i = 0; i < n; ++i) sum += ((double)x[i] / 32768.0) * ((double)x[i] / 32768.0);
    return 10.0 * log10(sum / n + 1e-30);
}

static i16 g_ref[2u * FRAMES], g_cap[2u * FRAMES], g_out[2u * FRAMES];

static void fill_reference(u32 frames) {
    for (u32 i = 0; i < frames; ++i) g_ref[i] = noise(-10.0);
}

TEST(create_refuses_every_invalid_config)
{
    AudioEchoCanceller *sentinel = (AudioEchoCanceller *)&g_seed;
    AudioEchoCanceller *aec = sentinel;
    AudioEchoCancellerConfig config = aec_config();
    ASSERT_EQ(audio_echo_canceller_create(NULL, &aec), AUDIO_INVALID);
    ASSERT_EQ(audio_echo_canceller_create(&config, NULL), AUDIO_INVALID);
    const struct { u32 field; f32 value; } bad[] = {
        {0u, 7999.0f}, {0u, 192001.0f}, {1u, 0.0f}, {1u, 8193.0f},
        {2u, 0.0005f}, {2u, 1.01f}, {2u, NAN}, {3u, -0.1f}, {3u, 1.1f}, {3u, NAN},
        {4u, -1.0f}, {4u, 1001.0f}, {4u, NAN}};
    for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        config = aec_config();
        switch (bad[i].field) {
        case 0u: config.sample_rate = (u32)bad[i].value; break;
        case 1u: config.taps = (u32)bad[i].value; break;
        case 2u: config.step_size = bad[i].value; break;
        case 3u: config.double_talk_threshold = bad[i].value; break;
        default: config.hangover_ms = bad[i].value; break;
        }
        ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_INVALID);
        ASSERT_TRUE(aec == sentinel);
    }
    const AudioEchoCancellerConfig limits[2] = {
        {8000u, 1u, 0.001f, 0.0f, 0.0f},
        {192000u, AUDIO_ECHO_CANCELLER_MAX_TAPS, 1.0f, 1.0f, 1000.0f}};
    for (u32 i = 0; i < 2u; ++i) {
        ASSERT_EQ(audio_echo_canceller_create(&limits[i], &aec), AUDIO_OK);
        ASSERT_TRUE(aec != NULL && aec != sentinel);
        for (u32 k = 0; k < limits[i].taps; k += 97u) {
            ASSERT_FLOAT_EQ(audio_echo_canceller_weight(aec, k), 0.0, 0.0);
        }
        ASSERT_FLOAT_EQ(audio_echo_canceller_weight(aec, limits[i].taps), 0.0, 0.0);
        audio_echo_canceller_destroy(aec);
    }
    audio_echo_canceller_destroy(NULL);
    ASSERT_FLOAT_EQ(audio_echo_canceller_weight(NULL, 0u), 0.0, 0.0);
}

static const Tap kPath[2] = {{3u, 0.3}, {10u, -0.15}};

static bool weights_near(const AudioEchoCanceller *aec, const Tap *path, u32 count, double tol) {
    for (u32 k = 0; k < TAPS; ++k) {
        double want = 0.0;
        for (u32 i = 0; i < count; ++i) {
            if (path[i].delay == k) want = path[i].gain;
        }
        if (fabs(audio_echo_canceller_weight(aec, k) - want) > tol) return false;
    }
    return true;
}

TEST(white_noise_echo_is_cancelled_and_the_path_is_learned)
{
    AudioEchoCanceller *aec = NULL;
    AudioEchoCancellerConfig config = aec_config();
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    fill_reference(FRAMES);
    make_capture(g_ref, g_cap, FRAMES, kPath, 2u, -300.0);
    memcpy(g_out, g_cap, sizeof(i16) * FRAMES);
    audio_echo_canceller_process_i16(aec, g_ref, g_out, FRAMES);
    const u32 last = RATE / 10u;
    double erle = power_db(g_cap + FRAMES - last, last) - power_db(g_out + FRAMES - last, last);
    ASSERT_TRUE(erle > 40.0);
    ASSERT_TRUE(weights_near(aec, kPath, 2u, 1e-3));
    /* weights past the end read as 0 even though weight 0 has moved */
    ASSERT_TRUE(audio_echo_canceller_weight(aec, 0u) != 0.0);
    ASSERT_FLOAT_EQ(audio_echo_canceller_weight(aec, TAPS), 0.0, 0.0);
    ASSERT_FLOAT_EQ(audio_echo_canceller_weight(aec, UINT32_MAX), 0.0, 0.0);
    audio_echo_canceller_destroy(aec);
    /* a threshold of 0 turns detection off: the filter still learns */
    config.double_talk_threshold = 0.0f;
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    memcpy(g_out, g_cap, sizeof(i16) * FRAMES);
    audio_echo_canceller_process_i16(aec, g_ref, g_out, FRAMES);
    ASSERT_TRUE(weights_near(aec, kPath, 2u, 1e-3));
    audio_echo_canceller_destroy(aec);
}

TEST(a_silent_reference_passes_the_capture_unchanged)
{
    AudioEchoCanceller *aec = NULL;
    AudioEchoCancellerConfig config = aec_config();
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    memset(g_ref, 0, sizeof(g_ref));
    make_capture(g_ref, g_cap, FRAMES, kPath, 2u, -6.0);
    g_cap[100] = 32767;
    g_cap[101] = -32768;
    memcpy(g_out, g_cap, sizeof(i16) * FRAMES);
    audio_echo_canceller_process_i16(aec, g_ref, g_out, FRAMES);
    ASSERT_EQ(memcmp(g_out, g_cap, sizeof(i16) * FRAMES), 0);
    ASSERT_TRUE(weights_near(aec, NULL, 0u, 0.0));
    audio_echo_canceller_process_i16(NULL, g_ref, g_out, 1u);
    audio_echo_canceller_process_i16(aec, NULL, g_out, 1u);
    audio_echo_canceller_process_i16(aec, g_ref, NULL, 1u);
    audio_echo_canceller_destroy(aec);
}

/* distance of the weights from `path` */
static double weight_error(const AudioEchoCanceller *aec, const Tap *path, u32 count) {
    double sum = 0.0;
    for (u32 k = 0; k < TAPS; ++k) {
        double want = 0.0;
        for (u32 i = 0; i < count; ++i) {
            if (path[i].delay == k) want = path[i].gain;
        }
        double d = audio_echo_canceller_weight(aec, k) - want;
        sum += d * d;
    }
    return sqrt(sum);
}

/* one second to converge, then half a second of a near-side tone; the SNR
 * of the output against the tone alone */
static double run_double_talk(AudioEchoCanceller *aec) {
    g_seed = 99u;
    fill_reference(FRAMES + FRAMES / 2u);
    make_capture(g_ref, g_cap, FRAMES, kPath, 2u, -300.0);
    audio_echo_canceller_process_i16(aec, g_ref, g_cap, FRAMES);
    make_capture(g_ref, g_cap, FRAMES + FRAMES / 2u, kPath, 2u, -10.0);
    memcpy(g_out, g_cap, sizeof(g_cap));
    audio_echo_canceller_process_i16(aec, g_ref + FRAMES, g_out + FRAMES, FRAMES / 2u);
    double err = 0.0, tone = 0.0;
    for (u32 n = FRAMES; n < FRAMES + FRAMES / 2u; ++n) {
        double t = sqrt(2.0) * pow(10.0, -10.0 / 20.0) * 32767.0 *
                   sin(2.0 * kPi * 440.0 * (double)n / RATE);
        err += (g_out[n] - t) * (g_out[n] - t);
        tone += t * t;
    }
    return 10.0 * log10(tone / err);
}

TEST(double_talk_detection_freezes_adaptation)
{
    AudioEchoCanceller *with = NULL, *without = NULL;
    AudioEchoCancellerConfig config = aec_config();
    /* the detector needs a few frames after the onset; a smaller step moves
     * the weights less in those frames */
    config.step_size = 0.1f;
    ASSERT_EQ(audio_echo_canceller_create(&config, &with), AUDIO_OK);
    config.double_talk_threshold = 0.0f;
    ASSERT_EQ(audio_echo_canceller_create(&config, &without), AUDIO_OK);
    double snr_with = run_double_talk(with);
    double snr_without = run_double_talk(without);
    double err_with = weight_error(with, kPath, 2u);
    double err_without = weight_error(without, kPath, 2u);
    /* the near tone comes through with the echo removed */
    ASSERT_TRUE(snr_with > 28.0);
    ASSERT_TRUE(err_with < 0.05);
    /* without detection the tone drags the weights away and leaks echo */
    ASSERT_TRUE(err_without > 5.0 * err_with);
    ASSERT_TRUE(snr_without < snr_with - 10.0);
    /* with detection the weights stay frozen once the tone is detected */
    double frozen = err_with;
    i16 ref_frames[480], cap_frames[480];
    for (u32 i = 0; i < 480u; ++i) {
        ref_frames[i] = g_ref[FRAMES + i];
        cap_frames[i] = (i16)lrint(20000.0 * sin(2.0 * kPi * 440.0 * (double)(i + 20u) / RATE));
    }
    audio_echo_canceller_process_i16(with, ref_frames, cap_frames, 480u);
    ASSERT_FLOAT_EQ(weight_error(with, kPath, 2u), frozen, 0.0);
    audio_echo_canceller_destroy(with);
    audio_echo_canceller_destroy(without);
}

TEST(the_hangover_keeps_adaptation_off_after_double_talk)
{
    AudioEchoCanceller *aec = NULL;
    AudioEchoCancellerConfig config = aec_config();
    config.hangover_ms = 1000.0f;
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    /* one loud near-side frame with a silent reference starts the hangover */
    i16 r = 0, c = 20000;
    audio_echo_canceller_process_i16(aec, &r, &c, 1u);
    /* echo only: the filter must not learn for the next second */
    g_seed = 5u;
    fill_reference(RATE / 2u);
    make_capture(g_ref, g_cap, RATE / 2u, kPath, 2u, -300.0);
    memcpy(g_out, g_cap, sizeof(i16) * (RATE / 2u));
    audio_echo_canceller_process_i16(aec, g_ref, g_out, RATE / 2u);
    ASSERT_EQ(memcmp(g_out, g_cap, sizeof(i16) * (RATE / 2u)), 0);
    ASSERT_TRUE(weights_near(aec, NULL, 0u, 0.0));
    audio_echo_canceller_destroy(aec);
    /* silence on both sides is not double talk: no hangover follows it */
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    r = 0;
    i16 quiet = 0;
    audio_echo_canceller_process_i16(aec, &r, &quiet, 1u);
    memcpy(g_out, g_cap, sizeof(i16) * (RATE / 2u));
    audio_echo_canceller_process_i16(aec, g_ref, g_out, RATE / 2u);
    ASSERT_TRUE(weights_near(aec, kPath, 2u, 1e-3));
    audio_echo_canceller_destroy(aec);
    /* a 1 ms hangover is over long before that */
    config.hangover_ms = 1.0f;
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    audio_echo_canceller_process_i16(aec, &r, &c, 1u);
    memcpy(g_out, g_cap, sizeof(i16) * (RATE / 2u));
    audio_echo_canceller_process_i16(aec, g_ref, g_out, RATE / 2u);
    ASSERT_TRUE(weights_near(aec, kPath, 2u, 1e-3));
    audio_echo_canceller_destroy(aec);
}

TEST(a_changed_echo_path_is_learned_again)
{
    static const Tap moved[1] = {{5u, 0.2}};
    AudioEchoCanceller *aec = NULL;
    AudioEchoCancellerConfig config = aec_config();
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    fill_reference(FRAMES);
    make_capture(g_ref, g_cap, FRAMES, kPath, 2u, -300.0);
    audio_echo_canceller_process_i16(aec, g_ref, g_cap, FRAMES);
    fill_reference(FRAMES);
    make_capture(g_ref, g_cap, FRAMES, moved, 1u, -300.0);
    memcpy(g_out, g_cap, sizeof(i16) * FRAMES);
    audio_echo_canceller_process_i16(aec, g_ref, g_out, FRAMES);
    const u32 last = RATE / 10u;
    ASSERT_TRUE(power_db(g_cap + FRAMES - last, last) - power_db(g_out + FRAMES - last, last) >
                40.0);
    ASSERT_TRUE(weights_near(aec, moved, 1u, 1e-3));
    audio_echo_canceller_destroy(aec);
}

TEST(reset_matches_a_fresh_canceller)
{
    AudioEchoCanceller *used = NULL, *fresh = NULL;
    AudioEchoCancellerConfig config = aec_config();
    ASSERT_EQ(audio_echo_canceller_create(&config, &used), AUDIO_OK);
    ASSERT_EQ(audio_echo_canceller_create(&config, &fresh), AUDIO_OK);
    fill_reference(FRAMES);
    make_capture(g_ref, g_cap, FRAMES, kPath, 2u, -300.0);
    /* end on a loud near frame so a hangover is pending */
    g_cap[FRAMES - 1u] = 30000;
    audio_echo_canceller_process_i16(used, g_ref, g_cap, FRAMES);
    audio_echo_canceller_reset(used);
    audio_echo_canceller_reset(NULL);
    ASSERT_TRUE(weights_near(used, NULL, 0u, 0.0));
    fill_reference(RATE / 10u);
    make_capture(g_ref, g_cap, RATE / 10u, kPath, 2u, -300.0);
    memcpy(g_out, g_cap, sizeof(i16) * (RATE / 10u));
    audio_echo_canceller_process_i16(used, g_ref, g_out, RATE / 10u);
    audio_echo_canceller_process_i16(fresh, g_ref, g_cap, RATE / 10u);
    ASSERT_EQ(memcmp(g_out, g_cap, sizeof(i16) * (RATE / 10u)), 0);
    for (u32 k = 0; k < TAPS; ++k) {
        ASSERT_FLOAT_EQ(audio_echo_canceller_weight(used, k),
                        audio_echo_canceller_weight(fresh, k), 0.0);
    }
    audio_echo_canceller_destroy(used);
    audio_echo_canceller_destroy(fresh);
}

/* The documented algorithm written out independently: a shifting history. */
typedef struct {
    double w[TAPS], x[TAPS];
    i16 xi[TAPS];
    u32 hold;
} RefAec;

static void ref_process(RefAec *a, const AudioEchoCancellerConfig *c, const i16 *ref, i16 *cap,
                        u32 frames) {
    u32 hangover = (u32)lrint((double)c->hangover_ms * RATE / 1000.0);
    for (u32 n = 0; n < frames; ++n) {
        memmove(a->x + 1, a->x, sizeof(double) * (TAPS - 1u));
        memmove(a->xi + 1, a->xi, sizeof(i16) * (TAPS - 1u));
        a->x[0] = ref[n] / 32768.0;
        a->xi[0] = ref[n];
        double y = 0.0, peak = 0.0;
        u64 energy = 0u;
        for (u32 k = 0; k < TAPS; ++k) {
            y += a->w[k] * a->x[k];
            if (fabs(a->x[k]) > peak) peak = fabs(a->x[k]);
            energy += (u64)((i32)a->xi[k] * (i32)a->xi[k]);
        }
        double d = cap[n] / 32768.0;
        double e = d - y;
        double v = nearbyint(e * 32768.0);
        cap[n] = (i16)(v > 32767.0 ? 32767.0 : (v < -32768.0 ? -32768.0 : v));
        bool adapt = true;
        if (c->double_talk_threshold > 0.0f && fabs(d) > (double)c->double_talk_threshold * peak) {
            a->hold = hangover;
            adapt = false;
        } else if (a->hold > 0u) {
            --a->hold;
            adapt = false;
        }
        if (adapt) {
            double g = (double)c->step_size * e /
                       ((double)energy / 1073741824.0 + TAPS * 1e-6);
            for (u32 k = 0; k < TAPS; ++k) a->w[k] += g * a->x[k];
        }
    }
}

TEST(chunked_output_matches_a_reference_model)
{
    enum { kFrames = 24000 };
    static i16 in[kFrames], ref_out[kFrames], out[3][kFrames];
    const u32 sizes[3] = {1u, 7u, 480u};
    AudioEchoCancellerConfig config = aec_config();
    config.step_size = 0.3f;
    g_seed = 31u;
    fill_reference(kFrames);
    make_capture(g_ref, in, kFrames, kPath, 2u, -300.0);
    /* near talk in the middle quarter, a clipped burst near the end */
    for (u32 n = kFrames / 4u; n < kFrames / 2u; ++n) {
        in[n] = (i16)lrint(in[n] + 8000.0 * sin(2.0 * kPi * 300.0 * n / RATE));
    }
    for (u32 n = kFrames - 200u; n < kFrames - 100u; ++n) in[n] = (n & 1u) ? 32767 : -32768;
    RefAec model;
    memset(&model, 0, sizeof(model));
    memcpy(ref_out, in, sizeof(in));
    ref_process(&model, &config, g_ref, ref_out, kFrames);
    for (u32 s = 0; s < 3u; ++s) {
        AudioEchoCanceller *aec = NULL;
        ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
        memcpy(out[s], in, sizeof(in));
        for (u32 at = 0; at < kFrames; at += sizes[s]) {
            u32 n = kFrames - at < sizes[s] ? kFrames - at : sizes[s];
            audio_echo_canceller_process_i16(aec, g_ref + at, out[s] + at, n);
        }
        for (u32 k = 0; k < TAPS; ++k) {
            ASSERT_FLOAT_EQ(audio_echo_canceller_weight(aec, k), model.w[k], 1e-9);
        }
        audio_echo_canceller_destroy(aec);
    }
    ASSERT_EQ(memcmp(out[0], out[1], sizeof(in)), 0);
    ASSERT_EQ(memcmp(out[0], out[2], sizeof(in)), 0);
    u32 mismatches = 0u;
    for (u32 n = 0; n < kFrames; ++n) {
        ASSERT_TRUE(abs(out[0][n] - ref_out[n]) <= 1);
        mismatches += out[0][n] != ref_out[n];
    }
    ASSERT_TRUE(mismatches <= 2u);
    ASSERT_NEQ(memcmp(ref_out, in, sizeof(in)), 0);
}

TEST(near_end_state_tracks_detection_hangover_and_reset)
{
    ASSERT_TRUE(!audio_echo_canceller_near_end_active(NULL));
    AudioEchoCancellerConfig config = aec_config();
    config.hangover_ms = 0.0f;
    AudioEchoCanceller *aec = NULL;
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    ASSERT_TRUE(!audio_echo_canceller_near_end_active(aec));
    i16 reference = 0, capture = 20000;
    audio_echo_canceller_process_i16(aec, &reference, &capture, 1u);
    ASSERT_TRUE(audio_echo_canceller_near_end_active(aec));
    audio_echo_canceller_process_i16(aec, &reference, &capture, 0u);
    ASSERT_TRUE(audio_echo_canceller_near_end_active(aec));
    capture = 0;
    audio_echo_canceller_process_i16(aec, &reference, &capture, 1u);
    ASSERT_TRUE(!audio_echo_canceller_near_end_active(aec));
    capture = 20000;
    audio_echo_canceller_process_i16(aec, &reference, &capture, 1u);
    ASSERT_TRUE(audio_echo_canceller_near_end_active(aec));
    audio_echo_canceller_reset(aec);
    ASSERT_TRUE(!audio_echo_canceller_near_end_active(aec));
    audio_echo_canceller_destroy(aec);

    config.hangover_ms = 1.0f;
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    capture = 20000;
    audio_echo_canceller_process_i16(aec, &reference, &capture, 1u);
    ASSERT_TRUE(audio_echo_canceller_near_end_active(aec));
    capture = 0;
    audio_echo_canceller_process_i16(aec, &reference, &capture, 1u);
    ASSERT_TRUE(audio_echo_canceller_near_end_active(aec));
    i16 quiet_reference[48] = {0}, quiet_capture[48] = {0};
    audio_echo_canceller_process_i16(aec, quiet_reference, quiet_capture, 47u);
    ASSERT_TRUE(audio_echo_canceller_near_end_active(aec));
    audio_echo_canceller_process_i16(aec, quiet_reference + 47u, quiet_capture + 47u, 1u);
    ASSERT_TRUE(!audio_echo_canceller_near_end_active(aec));
    capture = 20000;
    audio_echo_canceller_process_i16(aec, &reference, &capture, 1u);
    ASSERT_TRUE(audio_echo_canceller_near_end_active(aec));
    audio_echo_canceller_reset(aec);
    ASSERT_TRUE(!audio_echo_canceller_near_end_active(aec));
    audio_echo_canceller_destroy(aec);

    config.double_talk_threshold = 0.0f;
    config.hangover_ms = 0.0f;
    ASSERT_EQ(audio_echo_canceller_create(&config, &aec), AUDIO_OK);
    capture = 20000;
    audio_echo_canceller_process_i16(aec, &reference, &capture, 1u);
    ASSERT_TRUE(!audio_echo_canceller_near_end_active(aec));
    audio_echo_canceller_destroy(aec);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_refuses_every_invalid_config);
    RUN_TEST(white_noise_echo_is_cancelled_and_the_path_is_learned);
    RUN_TEST(a_silent_reference_passes_the_capture_unchanged);
    RUN_TEST(double_talk_detection_freezes_adaptation);
    RUN_TEST(the_hangover_keeps_adaptation_off_after_double_talk);
    RUN_TEST(a_changed_echo_path_is_learned_again);
    RUN_TEST(reset_matches_a_fresh_canceller);
    RUN_TEST(chunked_output_matches_a_reference_model);
    RUN_TEST(near_end_state_tracks_detection_hangover_and_reset);
TEST_MAIN_END()
