/* audio_agc: settling at the target, the gain cap, the noise gate, clipping,
 * stereo and chunking. */
#include "test_framework.h"

#include <audio/audio_agc.h>

#include <math.h>
#include <string.h>

#define RATE 48000u

static AudioAgcConfig voice_config(u32 channels) {
    AudioAgcConfig config;
    memset(&config, 0, sizeof(config));
    config.sample_rate = RATE;
    config.channels = channels;
    config.target_dbfs = -20.0f;
    config.max_gain_db = 30.0f;
    config.attack_ms = 5.0f;
    config.release_ms = 200.0f;
    config.gate_dbfs = -60.0f;
    return config;
}

/* 440 Hz at `amplitude` (of full scale), `frames` mono frames from `start` */
static void sine(i16 *out, u32 frames, u32 start, double amplitude) {
    for (u32 i = 0; i < frames; ++i) {
        out[i] = (i16)lrint(amplitude * 32767.0 *
                            sin(2.0 * 3.14159265358979323846 * 440.0 * (start + i) / RATE));
    }
}

static double rms_dbfs(const i16 *x, u32 n) {
    double sum = 0.0;
    for (u32 i = 0; i < n; ++i) sum += ((double)x[i] / 32768.0) * ((double)x[i] / 32768.0);
    return 10.0 * log10(sum / n);
}

TEST(init_refuses_every_invalid_config)
{
    AudioAgc agc;
    AudioAgcConfig config = voice_config(1u);
    memset(&agc, 0x5A, sizeof(agc));
    ASSERT_EQ(audio_agc_init(NULL, &config), AUDIO_INVALID);
    ASSERT_EQ(audio_agc_init(&agc, NULL), AUDIO_INVALID);
    const struct { u32 field; f32 value; } bad[] = {
        {0u, 7999.0f}, {0u, 192001.0f}, {1u, 0.0f}, {1u, 3.0f},
        {2u, -60.5f}, {2u, 0.5f}, {2u, NAN}, {3u, -0.5f}, {3u, 60.5f}, {3u, INFINITY},
        {4u, 0.05f}, {4u, 1001.0f}, {4u, NAN}, {5u, 0.5f}, {5u, 10001.0f},
        {6u, -121.0f}, {6u, -20.0f}, {6u, -10.0f}, {6u, NAN}};
    for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        config = voice_config(1u);
        switch (bad[i].field) {
        case 0u: config.sample_rate = (u32)bad[i].value; break;
        case 1u: config.channels = (u32)bad[i].value; break;
        case 2u: config.target_dbfs = bad[i].value; break;
        case 3u: config.max_gain_db = bad[i].value; break;
        case 4u: config.attack_ms = bad[i].value; break;
        case 5u: config.release_ms = bad[i].value; break;
        default: config.gate_dbfs = bad[i].value; break;
        }
        ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_INVALID);
        ASSERT_EQ(((const u8 *)&agc)[0], 0x5Au);
    }
    /* the limits are accepted */
    config = voice_config(2u);
    config.sample_rate = 8000u;
    config.target_dbfs = 0.0f;
    config.max_gain_db = 60.0f;
    config.attack_ms = 0.1f;
    config.release_ms = 10000.0f;
    config.gate_dbfs = -120.0f;
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
    ASSERT_FLOAT_EQ(audio_agc_gain_db(&agc), 0.0f, 0.0f);
    config = voice_config(1u);
    config.sample_rate = 192000u;
    config.target_dbfs = -60.0f;
    config.max_gain_db = 0.0f;
    config.attack_ms = 1000.0f;
    config.release_ms = 1.0f;
    config.gate_dbfs = -60.5f;
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
}

/* 2 s of sine through the AGC; the last 100 ms' level */
static double settled_level(double amplitude, AudioAgc *agc) {
    static i16 block[RATE / 10u];
    double level = 0.0;
    for (u32 b = 0; b < 20u; ++b) {
        sine(block, RATE / 10u, b * (RATE / 10u), amplitude);
        audio_agc_process_i16(agc, block, RATE / 10u);
        level = rms_dbfs(block, RATE / 10u);
    }
    return level;
}

TEST(a_quiet_and_a_loud_sine_settle_at_the_target)
{
    AudioAgc agc;
    AudioAgcConfig config = voice_config(1u);
    /* a sine of amplitude a has RMS a / sqrt(2): 0.01 is -43 dBFS, 0.9 -1.9 */
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
    ASSERT_TRUE(fabs(settled_level(0.01, &agc) - -20.0) < 1.0);
    ASSERT_TRUE(audio_agc_gain_db(&agc) > 20.0f);
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
    ASSERT_TRUE(fabs(settled_level(0.9, &agc) - -20.0) < 1.0);
    ASSERT_TRUE(audio_agc_gain_db(&agc) < -15.0f);
}

TEST(the_maximum_gain_caps_a_very_quiet_sine)
{
    AudioAgc agc;
    AudioAgcConfig config = voice_config(1u);
    config.max_gain_db = 10.0f;
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
    /* -43 dBFS wants +23 dB; 10 dB leaves it at -33 */
    double level = settled_level(0.01, &agc);
    ASSERT_FLOAT_EQ(audio_agc_gain_db(&agc), 10.0f, 1e-3f);
    ASSERT_TRUE(fabs(level - -33.0) < 1.0);
    config.max_gain_db = 0.0f;
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
    (void)settled_level(0.9, &agc);
    ASSERT_FLOAT_EQ(audio_agc_gain_db(&agc), 0.0f, 0.0f);
}

TEST(below_the_gate_the_gain_holds)
{
    AudioAgc agc;
    AudioAgcConfig config = voice_config(1u);
    static i16 block[RATE], copy[RATE];
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
    /* 0.0005 is -69 dBFS, under the -60 gate: unity, output untouched */
    sine(block, RATE, 0u, 0.0005);
    memcpy(copy, block, sizeof(block));
    audio_agc_process_i16(&agc, block, RATE);
    ASSERT_FLOAT_EQ(audio_agc_gain_db(&agc), 0.0f, 0.0f);
    ASSERT_EQ(memcmp(block, copy, sizeof(block)), 0);
    /* after a quiet talker raised the gain, silence keeps it. The 10 ms
     * detector needs about 40 ms to fall from -43 dBFS under the gate, and
     * the gain may rise a little meanwhile; from then on it holds. */
    (void)settled_level(0.01, &agc);
    f32 raised = audio_agc_gain_db(&agc);
    memset(block, 0, sizeof(block));
    audio_agc_process_i16(&agc, block, RATE / 10u);
    f32 held = audio_agc_gain_db(&agc);
    ASSERT_TRUE(held >= raised && held - raised < 2.0f);
    audio_agc_process_i16(&agc, block, RATE);
    ASSERT_FLOAT_EQ(audio_agc_gain_db(&agc), held, 0.0f);
    for (u32 i = 0; i < RATE; ++i) ASSERT_EQ(block[i], 0);
}

TEST(a_burst_after_quiet_is_clamped_not_wrapped)
{
    AudioAgc agc;
    AudioAgcConfig config = voice_config(1u);
    static i16 block[480];
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
    (void)settled_level(0.01, &agc);
    ASSERT_TRUE(audio_agc_gain_db(&agc) > 20.0f);
    sine(block, 480u, 0u, 1.0);
    audio_agc_process_i16(&agc, block, 480u);
    bool clamped = false;
    for (u32 i = 0; i < 480u; ++i) {
        double want = sin(2.0 * 3.14159265358979323846 * 440.0 * i / RATE);
        /* the sign never flips: a wrap would */
        ASSERT_TRUE(want * block[i] >= 0.0 || fabs(want) < 1e-3);
        clamped = clamped || block[i] == 32767 || block[i] == -32768;
    }
    ASSERT_TRUE(clamped);
    /* the attack pulls the gain down within the burst */
    ASSERT_TRUE(audio_agc_gain_db(&agc) < 10.0f);
}

TEST(stereo_shares_one_gain)
{
    AudioAgc agc;
    AudioAgcConfig config = voice_config(2u);
    static i16 mono[RATE / 10u], st[2u * (RATE / 10u)];
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
    for (u32 b = 0; b < 20u; ++b) {
        sine(mono, RATE / 10u, b * (RATE / 10u), 0.02);
        for (u32 i = 0; i < RATE / 10u; ++i) {
            st[2u * i] = mono[i];
            st[2u * i + 1u] = (i16)(mono[i] / 2);
        }
        audio_agc_process_i16(&agc, st, RATE / 10u);
    }
    /* channel mean square: (a^2 + a^2/4) / 2 / 2 -> the target */
    double sum_l = 0.0, sum_r = 0.0;
    for (u32 i = 0; i < RATE / 10u; ++i) {
        sum_l += (double)st[2u * i] * st[2u * i];
        sum_r += (double)st[2u * i + 1u] * st[2u * i + 1u];
    }
    ASSERT_TRUE(fabs(sqrt(sum_r / sum_l) - 0.5) < 0.01);
    double ms = (sum_l + sum_r) / 2.0 / (RATE / 10u) / (32768.0 * 32768.0);
    ASSERT_TRUE(fabs(10.0 * log10(ms) - -20.0) < 1.0);
}

TEST(chunking_does_not_change_the_output)
{
    enum { kFrames = 4800 };
    static i16 in[kFrames], whole[kFrames], parts[kFrames];
    const u32 sizes[3] = {1u, 7u, 480u};
    AudioAgc a, b;
    AudioAgcConfig config = voice_config(1u);
    for (u32 i = 0; i < kFrames; ++i) {
        in[i] = (i16)lrint((i < kFrames / 2 ? 0.01 : 0.8) * 32767.0 *
                           sin(2.0 * 3.14159265358979323846 * 300.0 * i / RATE));
    }
    memcpy(whole, in, sizeof(in));
    ASSERT_EQ(audio_agc_init(&a, &config), AUDIO_OK);
    audio_agc_process_i16(&a, whole, kFrames);
    for (u32 s = 0; s < 3u; ++s) {
        memcpy(parts, in, sizeof(in));
        ASSERT_EQ(audio_agc_init(&b, &config), AUDIO_OK);
        for (u32 at = 0; at < kFrames; at += sizes[s]) {
            u32 n = kFrames - at < sizes[s] ? kFrames - at : sizes[s];
            audio_agc_process_i16(&b, parts + at, n);
        }
        ASSERT_EQ(memcmp(whole, parts, sizeof(whole)), 0);
        ASSERT_FLOAT_EQ(audio_agc_gain_db(&a), audio_agc_gain_db(&b), 0.0f);
    }
    /* the output differs from the input: the AGC did something */
    ASSERT_NEQ(memcmp(whole, in, sizeof(in)), 0);
    audio_agc_process_i16(NULL, whole, 1u);
    audio_agc_process_i16(&a, NULL, 1u);
    ASSERT_FLOAT_EQ(audio_agc_gain_db(NULL), 0.0f, 0.0f);
}

/* The documented algorithm written out independently: 10 ms mean square of
 * the channel average, gate, cap, attack/release, round to nearest. */
TEST(stereo_output_matches_a_reference_model)
{
    enum { kFrames = 9600 };
    static i16 in[2u * kFrames], out[2u * kFrames];
    const double pi = 3.14159265358979323846;
    AudioAgc agc;
    AudioAgcConfig config = voice_config(2u);
    for (u32 i = 0; i < kFrames; ++i) {
        double env = i < kFrames / 3 ? 0.02 : (i < 2 * kFrames / 3 ? 0.6 : 0.001);
        in[2u * i] = (i16)lrint(env * 32767.0 * sin(2.0 * pi * 350.0 * i / RATE));
        /* the right channel is louder and out of phase with the left */
        in[2u * i + 1u] = (i16)lrint(env * 1.7 * 32767.0 * sin(2.0 * pi * 910.0 * i / RATE));
    }
    memcpy(out, in, sizeof(in));
    ASSERT_EQ(audio_agc_init(&agc, &config), AUDIO_OK);
    audio_agc_process_i16(&agc, out, kFrames);

    double level_a = 1.0 - exp(-1000.0 / (10.0 * RATE));
    double attack_a = 1.0 - exp(-1000.0 / ((double)config.attack_ms * RATE));
    double release_a = 1.0 - exp(-1000.0 / ((double)config.release_ms * RATE));
    double ms = 0.0, gain_db = 0.0, gain = 1.0;
    u32 mismatches = 0u;
    bool off_by_rounding = false;
    for (u32 i = 0; i < kFrames; ++i) {
        double l = in[2u * i] / 32768.0, r = in[2u * i + 1u] / 32768.0;
        ms += level_a * ((l * l + r * r) / 2.0 - ms);
        if (ms > 0.0 && 10.0 * log10(ms) >= config.gate_dbfs) {
            double want = config.target_dbfs - 10.0 * log10(ms);
            if (want > config.max_gain_db) want = config.max_gain_db;
            if (want < -config.max_gain_db) want = -config.max_gain_db;
            gain_db += (want < gain_db ? attack_a : release_a) * (want - gain_db);
            gain = pow(10.0, gain_db / 20.0);
        }
        for (u32 c = 0; c < 2u; ++c) {
            double y = nearbyint(in[2u * i + c] * gain);
            if (y > 32767.0) y = 32767.0;
            if (y < -32768.0) y = -32768.0;
            if ((i16)y != out[2u * i + c]) mismatches++;
            off_by_rounding = off_by_rounding || (in[2u * i + c] * gain - trunc(in[2u * i + c] * gain)) > 0.5;
        }
    }
    ASSERT_EQ(mismatches, 0u);
    /* the input exercises rounding up, so truncation would differ */
    ASSERT_TRUE(off_by_rounding);
    ASSERT_FLOAT_EQ(audio_agc_gain_db(&agc), (f32)gain_db, 0.0f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(init_refuses_every_invalid_config);
    RUN_TEST(a_quiet_and_a_loud_sine_settle_at_the_target);
    RUN_TEST(the_maximum_gain_caps_a_very_quiet_sine);
    RUN_TEST(below_the_gate_the_gain_holds);
    RUN_TEST(a_burst_after_quiet_is_clamped_not_wrapped);
    RUN_TEST(stereo_shares_one_gain);
    RUN_TEST(chunking_does_not_change_the_output);
    RUN_TEST(stereo_output_matches_a_reference_model);
TEST_MAIN_END()
