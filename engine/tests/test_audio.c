/* ==========================================================================
 *  test_audio.c — 3D distance attenuation model (headless).
 *
 *  Exercises the pure inverse-distance gain function used by the streaming
 *  audio system for spatialization. The actual playback path needs an audio
 *  device + miniaudio and is validated by the demo build, not here.
 * ========================================================================== */

/* R419: this target does not link audio.c (headless, no device), so the
 * source-handle generation guard is tested by including the TU directly.
 * Mirror the POSIX feature level the engine target compiles audio.c with.
 * Must precede all system includes. */
#define _POSIX_C_SOURCE 199309L

#include "test_framework.h"
#include <audio/audio.h>

#include "../src/audio/audio.c"

/* core/log.c is not linked into this target — stub log_write for audio.c. */
void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    (void)level; (void)file; (void)line; (void)fmt;
}

TEST(atten_inside_min_is_full)
{
    /* At or below min distance the sound plays at full gain. */
    ASSERT_FLOAT_EQ(audio_attenuation_gain(0.0f, 1.0f, 100.0f, 1.0f), 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(audio_attenuation_gain(1.0f, 1.0f, 100.0f, 1.0f), 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(audio_attenuation_gain(0.5f, 1.0f, 100.0f, 1.0f), 1.0f, 1e-5);
}

TEST(atten_inverse_known_values)
{
    /* g = min / (min + rolloff*(d-min)) */
    ASSERT_FLOAT_EQ(audio_attenuation_gain(2.0f, 1.0f, 100.0f, 1.0f), 0.5f, 1e-5);
    ASSERT_FLOAT_EQ(audio_attenuation_gain(3.0f, 1.0f, 100.0f, 1.0f), 1.0f / 3.0f, 1e-5);
    /* higher rolloff drops faster: d=2,rolloff=2 -> 1/(1+2)=1/3 */
    ASSERT_FLOAT_EQ(audio_attenuation_gain(2.0f, 1.0f, 100.0f, 2.0f), 1.0f / 3.0f, 1e-5);
}

TEST(atten_monotonic_decreasing)
{
    f32 prev = 2.0f;
    for (f32 d = 1.0f; d <= 40.0f; d += 1.0f) {
        f32 g = audio_attenuation_gain(d, 2.0f, 40.0f, 1.0f);
        ASSERT_TRUE(g <= prev + 1e-6f);
        ASSERT_TRUE(g >= 0.0f && g <= 1.0f);
        prev = g;
    }
}

TEST(atten_clamped_beyond_max)
{
    /* Past max distance the gain is clamped to the value at max distance. */
    f32 at_max = audio_attenuation_gain(40.0f, 2.0f, 40.0f, 1.0f);
    f32 far    = audio_attenuation_gain(1000.0f, 2.0f, 40.0f, 1.0f);
    ASSERT_FLOAT_EQ(at_max, far, 1e-5);
}

TEST(atten_zero_rolloff_is_full)
{
    /* No rolloff => no attenuation regardless of distance (within max). */
    ASSERT_FLOAT_EQ(audio_attenuation_gain(50.0f, 1.0f, 100.0f, 0.0f), 1.0f, 1e-5);
}

/* ----------------------------------------------------------------------- */
/*  R419: source-handle generation guard (ABA)                              */
/* ----------------------------------------------------------------------- */

TEST(handle_first_generation_matches_legacy_scheme)
{
    /* Generation 0 keeps handles numerically identical to the old id+1
     * scheme, so first-use callers see no change. */
    AudioSource src;
    memset(&src, 0, sizeof(src));
    ASSERT_EQ(audio_make_handle(&src, 0), 1u);
    ASSERT_EQ(audio_make_handle(&src, 7), 8u);
}

TEST(handle_generation_rejects_stale)
{
    /* R419: after a slot is stopped (generation bumped) and reused by a new
     * sound, the stale handle must NOT resolve to the new sound. */
    AudioSystem as;
    AudioSource srcs[2];
    memset(&as, 0, sizeof(as));
    memset(srcs, 0, sizeof(srcs));
    as.sources      = srcs;
    as.source_count = 1;
    as.source_cap   = 2;

    u32 h1 = audio_make_handle(&as.sources[0], 0);
    ASSERT_TRUE(audio_resolve(&as, h1) == &as.sources[0]);

    /* Slot freed (audio_stop bumps generation) then reused for a new sound */
    as.sources[0].generation++;
    u32 h2 = audio_make_handle(&as.sources[0], 0);
    ASSERT_TRUE(h1 != h2);
    ASSERT_TRUE(audio_resolve(&as, h2) == &as.sources[0]);
    ASSERT_TRUE(audio_resolve(&as, h1) == NULL); /* stale — no aliasing */

    /* Zero and out-of-range handles are rejected */
    ASSERT_TRUE(audio_resolve(&as, 0) == NULL);
    ASSERT_TRUE(audio_resolve(&as,
        (as.sources[0].generation << AUDIO_HANDLE_GEN_SHIFT) | 5u) == NULL);
}

TEST(handle_generation_wraps_at_24_bits)
{
    /* R423: audio_stop bumps the generation with & 0xFFFFFFu. Pre-fix, the
     * raw increment let generation reach 2^24, where audio_make_handle's
     * generation<<8 truncated to 0 — audio_resolve then rejected the very
     * next handle issued for the slot (sound unstoppable, slot leaked).
     * At the wrap boundary a freshly issued handle must resolve. */
    AudioSystem as;
    AudioSource srcs[1];
    memset(&as, 0, sizeof(as));
    memset(srcs, 0, sizeof(srcs));
    as.sources      = srcs;
    as.source_count = 1;
    as.source_cap   = 1;

    srcs[0].generation = 0xFFFFFFu;
    u32 h_old = audio_make_handle(&srcs[0], 0);

    /* The audio_stop bump ((gen + 1) & 0xFFFFFFu) wraps to 0. */
    srcs[0].generation = (srcs[0].generation + 1u) & 0xFFFFFFu;
    ASSERT_EQ(srcs[0].generation, 0u);

    u32 h_new = audio_make_handle(&srcs[0], 0);
    ASSERT_TRUE(audio_resolve(&as, h_new) == &srcs[0]); /* pre-fix: NULL */
    ASSERT_TRUE(audio_resolve(&as, h_old) == NULL);     /* stale stays stale */
}

TEST_MAIN_BEGIN()
    RUN_TEST(atten_inside_min_is_full);
    RUN_TEST(atten_inverse_known_values);
    RUN_TEST(atten_monotonic_decreasing);
    RUN_TEST(atten_clamped_beyond_max);
    RUN_TEST(atten_zero_rolloff_is_full);
    RUN_TEST(handle_first_generation_matches_legacy_scheme);
    RUN_TEST(handle_generation_rejects_stale);
    RUN_TEST(handle_generation_wraps_at_24_bits);
TEST_MAIN_END()
