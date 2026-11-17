/* audio_noise_gate: learning the noise floor, closing on steady noise,
 * opening for a tone, silence, and a reference model across stereo and
 * chunking. */
#include "test_framework.h"

#include <audio/audio_noise_gate.h>

#include <math.h>
#include <string.h>

#define RATE 48000u

static const double kPi = 3.14159265358979323846;
static u32 g_seed = 0x1234567u;

static AudioNoiseGateConfig gate_config(u32 channels) {
    AudioNoiseGateConfig config;
    memset(&config, 0, sizeof(config));
    config.sample_rate = RATE;
    config.channels = channels;
    config.threshold_db = 10.0f;
    config.reduction_db = 30.0f;
    config.attack_ms = 1.0f;
    config.release_ms = 20.0f;
    config.floor_rise_db_per_s = 20.0f;
    config.initial_floor_dbfs = -45.0f;
    return config;
}

/* uniform noise with RMS `dbfs` (uniform in [-a, a] has RMS a / sqrt(3)) */
static i16 noise(double dbfs) {
    g_seed = g_seed * 1664525u + 1013904223u;
    double u = (double)(g_seed >> 8) / 8388608.0 - 1.0;
    return (i16)lrint(u * sqrt(3.0) * pow(10.0, dbfs / 20.0) * 32767.0);
}

static double rms_dbfs(const i16 *x, u32 n, u32 stride) {
    double sum = 0.0;
    for (u32 i = 0; i < n; ++i) {
        double v = (double)x[i * stride] / 32768.0;
        sum += v * v;
    }
    return 10.0 * log10(sum / n);
}

/* `frames` mono frames of noise at `noise_db`, plus a 440 Hz tone with RMS
 * `tone_db` when it is above -200, starting at frame `start` */
static void fill(i16 *x, u32 frames, u32 start, double noise_db, double tone_db) {
    for (u32 i = 0; i < frames; ++i) {
        double v = noise(noise_db);
        if (tone_db > -200.0) {
            v += sqrt(2.0) * pow(10.0, tone_db / 20.0) * 32767.0 *
                 sin(2.0 * kPi * 440.0 * (double)(start + i) / RATE);
        }
        x[i] = (i16)lrint(v);
    }
}

TEST(init_refuses_every_invalid_config)
{
    AudioNoiseGate gate;
    AudioNoiseGateConfig config = gate_config(1u);
    memset(&gate, 0x5A, sizeof(gate));
    ASSERT_EQ(audio_noise_gate_init(NULL, &config), AUDIO_INVALID);
    ASSERT_EQ(audio_noise_gate_init(&gate, NULL), AUDIO_INVALID);
    const struct { u32 field; f32 value; } bad[] = {
        {0u, 7999.0f}, {0u, 192001.0f}, {1u, 0.0f}, {1u, 3.0f},
        {2u, 2.9f}, {2u, 40.5f}, {2u, NAN}, {3u, -0.5f}, {3u, 80.5f}, {3u, NAN},
        {4u, 0.05f}, {4u, 1001.0f}, {4u, NAN}, {5u, 0.5f}, {5u, 10001.0f}, {5u, NAN},
        {6u, 0.05f}, {6u, 60.5f}, {6u, INFINITY}, {7u, -120.5f}, {7u, 0.5f}, {7u, NAN}};
    for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        config = gate_config(1u);
        switch (bad[i].field) {
        case 0u: config.sample_rate = (u32)bad[i].value; break;
        case 1u: config.channels = (u32)bad[i].value; break;
        case 2u: config.threshold_db = bad[i].value; break;
        case 3u: config.reduction_db = bad[i].value; break;
        case 4u: config.attack_ms = bad[i].value; break;
        case 5u: config.release_ms = bad[i].value; break;
        case 6u: config.floor_rise_db_per_s = bad[i].value; break;
        default: config.initial_floor_dbfs = bad[i].value; break;
        }
        ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_INVALID);
        ASSERT_EQ(((const u8 *)&gate)[0], 0x5Au);
    }
    /* the limits are accepted; the gate starts open at the initial floor */
    config = gate_config(2u);
    config.sample_rate = 8000u;
    config.threshold_db = 3.0f;
    config.reduction_db = 0.0f;
    config.attack_ms = 0.1f;
    config.release_ms = 10000.0f;
    config.floor_rise_db_per_s = 0.1f;
    config.initial_floor_dbfs = -120.0f;
    ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
    ASSERT_FLOAT_EQ(audio_noise_gate_gain_db(&gate), 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(audio_noise_gate_floor_dbfs(&gate), -120.0f, 0.0f);
    config = gate_config(1u);
    config.sample_rate = 192000u;
    config.threshold_db = 40.0f;
    config.reduction_db = 80.0f;
    config.attack_ms = 1000.0f;
    config.release_ms = 1.0f;
    config.floor_rise_db_per_s = 60.0f;
    config.initial_floor_dbfs = 0.0f;
    ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
    ASSERT_FLOAT_EQ(audio_noise_gate_floor_dbfs(&gate), 0.0f, 0.0f);
}

/* one second of noise at -50 dBFS through `gate`; the last 100 ms' level */
static double settle_on_noise(AudioNoiseGate *gate) {
    static i16 x[RATE / 10u];
    double level = 0.0;
    for (u32 b = 0; b < 10u; ++b) {
        fill(x, RATE / 10u, b * (RATE / 10u), -50.0, -300.0);
        audio_noise_gate_process_i16(gate, x, RATE / 10u);
        level = rms_dbfs(x, RATE / 10u, 1u);
    }
    return level;
}

TEST(steady_noise_teaches_the_floor_and_closes_the_gate)
{
    AudioNoiseGate gate;
    AudioNoiseGateConfig config = gate_config(1u);
    ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
    double out = settle_on_noise(&gate);
    f32 floor_db = audio_noise_gate_floor_dbfs(&gate);
    ASSERT_TRUE(floor_db > -53.0f && floor_db <= -49.0f);
    ASSERT_TRUE(audio_noise_gate_gain_db(&gate) < -29.5f);
    ASSERT_TRUE(fabs(out - -80.0) < 1.0);
}

TEST(a_tone_well_above_the_floor_opens_the_gate)
{
    AudioNoiseGate gate;
    AudioNoiseGateConfig config = gate_config(1u);
    static i16 x[RATE / 10u];
    ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
    (void)settle_on_noise(&gate);
    fill(x, RATE / 10u, RATE, -50.0, -20.0);
    audio_noise_gate_process_i16(&gate, x, RATE / 10u);
    ASSERT_TRUE(audio_noise_gate_gain_db(&gate) > -0.01f);
    /* the last 50 ms: the tone at its own level */
    ASSERT_TRUE(fabs(rms_dbfs(x + RATE / 20u, RATE / 20u, 1u) - -20.0) < 0.5);
    /* the floor creeps up at 20 dB/s: about 2 dB in 100 ms */
    f32 floor_db = audio_noise_gate_floor_dbfs(&gate);
    ASSERT_TRUE(floor_db > -53.0f && floor_db < -46.0f);
}

TEST(long_steady_speech_eventually_closes_the_gate)
{
    AudioNoiseGate gate;
    AudioNoiseGateConfig config = gate_config(1u);
    static i16 x[RATE / 10u];
    config.floor_rise_db_per_s = 60.0f;
    ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
    (void)settle_on_noise(&gate);
    /* -50 to -30 at 60 dB/s takes a third of a second */
    for (u32 b = 0; b < 3u; ++b) {
        fill(x, RATE / 10u, RATE + b * (RATE / 10u), -50.0, -20.0);
        audio_noise_gate_process_i16(&gate, x, RATE / 10u);
    }
    ASSERT_TRUE(audio_noise_gate_gain_db(&gate) > -0.01f);
    for (u32 b = 3u; b < 10u; ++b) {
        fill(x, RATE / 10u, RATE + b * (RATE / 10u), -50.0, -20.0);
        audio_noise_gate_process_i16(&gate, x, RATE / 10u);
    }
    ASSERT_TRUE(audio_noise_gate_gain_db(&gate) < -29.5f);
    ASSERT_TRUE(audio_noise_gate_floor_dbfs(&gate) > -21.0f);
}

TEST(quieter_noise_pulls_the_floor_down_at_once)
{
    AudioNoiseGate gate;
    AudioNoiseGateConfig config = gate_config(1u);
    static i16 x[RATE / 10u];
    ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
    (void)settle_on_noise(&gate);
    /* the 10 ms detector falls 20 dB in about 50 ms; the floor goes with it */
    fill(x, RATE / 10u, RATE, -70.0, -300.0);
    audio_noise_gate_process_i16(&gate, x, RATE / 10u);
    f32 floor_db = audio_noise_gate_floor_dbfs(&gate);
    ASSERT_TRUE(floor_db < -67.0f && floor_db > -80.0f);
    ASSERT_TRUE(audio_noise_gate_gain_db(&gate) < -29.5f);
}

TEST(silence_stays_silent_and_finite)
{
    AudioNoiseGate gate;
    AudioNoiseGateConfig config = gate_config(2u);
    static i16 x[2u * RATE];
    config.initial_floor_dbfs = -120.0f;
    memset(x, 0, sizeof(x));
    ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
    audio_noise_gate_process_i16(&gate, x, RATE);
    for (u32 i = 0; i < 2u * RATE; ++i) ASSERT_EQ(x[i], 0);
    ASSERT_FLOAT_EQ(audio_noise_gate_floor_dbfs(&gate), -120.0f, 0.0f);
    ASSERT_TRUE(isfinite(audio_noise_gate_gain_db(&gate)));
    ASSERT_TRUE(audio_noise_gate_gain_db(&gate) < -29.5f);
    /* a louder start keeps the floor at -120, never below */
    config.initial_floor_dbfs = -30.0f;
    ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
    audio_noise_gate_process_i16(&gate, x, RATE);
    ASSERT_FLOAT_EQ(audio_noise_gate_floor_dbfs(&gate), -120.0f, 0.0f);
    audio_noise_gate_process_i16(NULL, x, 1u);
    audio_noise_gate_process_i16(&gate, NULL, 1u);
    ASSERT_FLOAT_EQ(audio_noise_gate_gain_db(NULL), 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(audio_noise_gate_floor_dbfs(NULL), (f32)AUDIO_NOISE_GATE_MIN_DBFS, 0.0f);
}

TEST(the_floor_rises_to_the_level_and_never_past_it)
{
    AudioNoiseGate gate;
    AudioNoiseGateConfig config = gate_config(1u);
    i16 x = 3277;
    const double level = 20.0 * log10(3277.0 / 32768.0);
    config.floor_rise_db_per_s = 60.0f;
    config.initial_floor_dbfs = -30.0f;
    ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
    /* a constant input: the level rises to `level` from below and stays */
    for (u32 i = 0; i < RATE; ++i) {
        x = 3277;
        audio_noise_gate_process_i16(&gate, &x, 1u);
        if (i >= RATE / 2u) {
            f32 floor_db = audio_noise_gate_floor_dbfs(&gate);
            ASSERT_TRUE(floor_db <= (f32)(level + 1e-4));
            ASSERT_TRUE(floor_db > (f32)(level - 0.01));
        }
    }
    /* an input at the floor is attenuated by the full reduction */
    ASSERT_TRUE(audio_noise_gate_gain_db(&gate) < -29.5f);
    ASSERT_TRUE(x < 3277 / 30);
}

/* The documented algorithm written out independently. */
typedef struct {
    double ms, floor_db, gain_db, gain;
} RefGate;

static void ref_process(RefGate *g, const AudioNoiseGateConfig *c, i16 *x, u32 frames) {
    double la = 1.0 - exp(-1000.0 / (10.0 * RATE));
    double aa = 1.0 - exp(-1000.0 / ((double)c->attack_ms * RATE));
    double ra = 1.0 - exp(-1000.0 / ((double)c->release_ms * RATE));
    double rise = (double)c->floor_rise_db_per_s / RATE;
    for (u32 f = 0; f < frames; ++f) {
        double p = 0.0;
        for (u32 ch = 0; ch < c->channels; ++ch) {
            double v = x[f * c->channels + ch] / 32768.0;
            p += v * v;
        }
        g->ms += la * (p / c->channels - g->ms);
        double level = g->ms > 0.0 ? 10.0 * log10(g->ms) : -120.0;
        if (level < -120.0) level = -120.0;
        if (level < g->floor_db) g->floor_db = level;
        else g->floor_db = g->floor_db + rise < level ? g->floor_db + rise : level;
        double target = level >= g->floor_db + (double)c->threshold_db ? 0.0 : -(double)c->reduction_db;
        g->gain_db += (target > g->gain_db ? aa : ra) * (target - g->gain_db);
        g->gain = pow(10.0, g->gain_db / 20.0);
        for (u32 ch = 0; ch < c->channels; ++ch) {
            double y = nearbyint(x[f * c->channels + ch] * g->gain);
            if (y > 32767.0) y = 32767.0;
            if (y < -32768.0) y = -32768.0;
            x[f * c->channels + ch] = (i16)y;
        }
    }
}

TEST(stereo_and_chunked_output_match_a_reference_model)
{
    enum { kFrames = 24000 };
    static i16 in[2u * kFrames], out[2u * kFrames], ref[2u * kFrames];
    const u32 sizes[3] = {1u, 7u, 480u};
    AudioNoiseGateConfig config = gate_config(2u);
    config.floor_rise_db_per_s = 40.0f;
    g_seed = 777u;
    for (u32 i = 0; i < kFrames; ++i) {
        /* noise, a tone burst, quieter noise, a loud burst */
        double tone = i < kFrames / 4 ? -300.0 : (i < kFrames / 2 ? -25.0 :
                      (i < 3 * kFrames / 4 ? -300.0 : -3.0));
        double floor_db = i < kFrames / 2 ? -50.0 : -65.0;
        i16 l = 0, r = 0;
        fill(&l, 1u, i, floor_db, tone);
        fill(&r, 1u, i * 3u, floor_db - 6.0, tone - 6.0);
        in[2u * i] = l;
        in[2u * i + 1u] = r;
    }
    RefGate g;
    g.ms = pow(10.0, (double)config.initial_floor_dbfs / 10.0);
    g.floor_db = config.initial_floor_dbfs;
    g.gain_db = 0.0;
    g.gain = 1.0;
    memcpy(ref, in, sizeof(in));
    ref_process(&g, &config, ref, kFrames);
    ASSERT_NEQ(memcmp(ref, in, sizeof(in)), 0);
    for (u32 s = 0; s < 3u; ++s) {
        AudioNoiseGate gate;
        memcpy(out, in, sizeof(in));
        ASSERT_EQ(audio_noise_gate_init(&gate, &config), AUDIO_OK);
        for (u32 at = 0; at < kFrames; at += sizes[s]) {
            u32 n = kFrames - at < sizes[s] ? kFrames - at : sizes[s];
            audio_noise_gate_process_i16(&gate, out + 2u * at, n);
        }
        ASSERT_EQ(memcmp(out, ref, sizeof(out)), 0);
        ASSERT_FLOAT_EQ(audio_noise_gate_gain_db(&gate), (f32)g.gain_db, 0.0f);
        ASSERT_FLOAT_EQ(audio_noise_gate_floor_dbfs(&gate), (f32)g.floor_db, 0.0f);
    }
}

TEST_MAIN_BEGIN()
    RUN_TEST(init_refuses_every_invalid_config);
    RUN_TEST(steady_noise_teaches_the_floor_and_closes_the_gate);
    RUN_TEST(a_tone_well_above_the_floor_opens_the_gate);
    RUN_TEST(long_steady_speech_eventually_closes_the_gate);
    RUN_TEST(quieter_noise_pulls_the_floor_down_at_once);
    RUN_TEST(silence_stays_silent_and_finite);
    RUN_TEST(the_floor_rises_to_the_level_and_never_past_it);
    RUN_TEST(stereo_and_chunked_output_match_a_reference_model);
TEST_MAIN_END()
