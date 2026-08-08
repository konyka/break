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

/* ----------------------------------------------------------------------- */
/*  R435: mixing buses (headless — table logic + pure gain composition)     */
/* ----------------------------------------------------------------------- */

/* Zeroed AudioSystem with the bus table reset the way audio_system_create
 * does (headless tests can't call create — no audio device). */
static void test_sys_init(AudioSystem *as, AudioSource *srcs, u32 cap) {
    memset(as, 0, sizeof(*as));
    if (srcs) memset(srcs, 0, sizeof(*srcs) * cap);
    as->sources     = srcs;
    as->source_cap  = cap;
    as->source_count = 0;
    audio_bus_table_reset(as);
}

TEST(bus_master_always_present)
{
    /* The master bus (id 0) exists from reset with unity gain. */
    AudioSystem as;
    test_sys_init(&as, NULL, 0);
    ASSERT_EQ(as.bus_count, 1u);
    ASSERT_EQ(AUDIO_BUS_MASTER, 0u);
    ASSERT_FLOAT_EQ(audio_bus_gain(&as, AUDIO_BUS_MASTER), 1.0f, 1e-6);
    ASSERT_STR_EQ(as.buses[AUDIO_BUS_MASTER].name, "master");
}

TEST(bus_create_assigns_sequential_ids)
{
    AudioSystem as;
    test_sys_init(&as, NULL, 0);
    u32 sfx   = audio_bus_create(&as, "sfx");
    u32 music = audio_bus_create(&as, "music");
    ASSERT_EQ(sfx, 1u);
    ASSERT_EQ(music, 2u);
    ASSERT_EQ(as.bus_count, 3u);
    /* New buses start at unity gain, master untouched */
    ASSERT_FLOAT_EQ(audio_bus_gain(&as, sfx), 1.0f, 1e-6);
    ASSERT_FLOAT_EQ(audio_bus_gain(&as, music), 1.0f, 1e-6);
    ASSERT_FLOAT_EQ(audio_bus_gain(&as, AUDIO_BUS_MASTER), 1.0f, 1e-6);
}

TEST(bus_create_full_table_returns_invalid)
{
    AudioSystem as;
    test_sys_init(&as, NULL, 0);
    for (u32 i = 1; i < AUDIO_MAX_BUSES; i++) {
        ASSERT_EQ(audio_bus_create(&as, "x"), i);
    }
    ASSERT_EQ(as.bus_count, (u32)AUDIO_MAX_BUSES);
    /* Table full: error sentinel follows the UINT32_MAX convention. */
    ASSERT_EQ(audio_bus_create(&as, "overflow"), AUDIO_BUS_INVALID);
    ASSERT_EQ(as.bus_count, (u32)AUDIO_MAX_BUSES);
    ASSERT_EQ(audio_bus_create(NULL, "x"), AUDIO_BUS_INVALID);
    ASSERT_EQ(audio_bus_create(&as, NULL), AUDIO_BUS_INVALID);
}

TEST(bus_set_gain_clamps_negative)
{
    AudioSystem as;
    test_sys_init(&as, NULL, 0);
    u32 sfx = audio_bus_create(&as, "sfx");
    audio_bus_set_gain(&as, sfx, 0.5f);
    ASSERT_FLOAT_EQ(audio_bus_gain(&as, sfx), 0.5f, 1e-6);
    /* R435: gains clamp to non-negative (mute at 0, never phase-flip). */
    audio_bus_set_gain(&as, sfx, -2.0f);
    ASSERT_FLOAT_EQ(audio_bus_gain(&as, sfx), 0.0f, 1e-6);
    /* Unity restore; >1 amplification allowed (matches volume policy). */
    audio_bus_set_gain(&as, sfx, 2.0f);
    ASSERT_FLOAT_EQ(audio_bus_gain(&as, sfx), 2.0f, 1e-6);
}

TEST(bus_invalid_id_rejected_falls_back_master)
{
    AudioSystem as;
    test_sys_init(&as, NULL, 0);
    audio_bus_set_gain(&as, AUDIO_BUS_MASTER, 0.7f);
    /* set on an invalid id is a no-op: nothing changes. */
    audio_bus_set_gain(&as, 999u, 0.1f);
    ASSERT_FLOAT_EQ(audio_bus_gain(&as, AUDIO_BUS_MASTER), 0.7f, 1e-6);
    ASSERT_EQ(as.bus_count, 1u);
    /* query on an invalid id falls back to the master gain. */
    ASSERT_FLOAT_EQ(audio_bus_gain(&as, 999u), 0.7f, 1e-6);
    ASSERT_FLOAT_EQ(audio_bus_gain(NULL, 999u), 1.0f, 1e-6);
}

TEST(effective_gain_pure_composition)
{
    /* effective = volume x bus gain x master gain */
    ASSERT_FLOAT_EQ(audio_effective_gain(0.8f, 0.5f, 1.0f), 0.4f, 1e-6);
    ASSERT_FLOAT_EQ(audio_effective_gain(1.0f, 1.0f, 1.0f), 1.0f, 1e-6);
    ASSERT_FLOAT_EQ(audio_effective_gain(0.5f, 0.5f, 0.5f), 0.125f, 1e-6);
    /* any negative factor clamps to 0 (mute) */
    ASSERT_FLOAT_EQ(audio_effective_gain(-1.0f, 1.0f, 1.0f), 0.0f, 1e-6);
    ASSERT_FLOAT_EQ(audio_effective_gain(1.0f, -1.0f, 1.0f), 0.0f, 1e-6);
    ASSERT_FLOAT_EQ(audio_effective_gain(1.0f, 1.0f, -1.0f), 0.0f, 1e-6);
    /* no upper clamp — amplification is allowed, matching volume policy */
    ASSERT_FLOAT_EQ(audio_effective_gain(2.0f, 1.0f, 1.0f), 2.0f, 1e-6);
}

TEST(source_bus_volume_compose_and_fallback)
{
    /* Source routed through a bus: set_volume / set_bus / set_gain all
     * re-compose volume x bus x master. Sources stay inactive so no
     * miniaudio call happens (headless). */
    AudioSystem as;
    AudioSource srcs[1];
    test_sys_init(&as, srcs, 1);
    as.source_count = 1;

    u32 sfx = audio_bus_create(&as, "sfx");
    u32 h = audio_make_handle(&as.sources[0], 0);

    audio_source_set_volume(&as, h, 0.8f);
    audio_source_set_bus(&as, h, sfx);
    ASSERT_EQ(as.sources[0].bus, sfx);
    ASSERT_FLOAT_EQ(audio_source_effective_gain(&as, &as.sources[0]), 0.8f, 1e-6);

    /* Bus fader moves the composed gain... */
    audio_bus_set_gain(&as, sfx, 0.5f);
    ASSERT_FLOAT_EQ(audio_source_effective_gain(&as, &as.sources[0]), 0.4f, 1e-6);
    /* ...and so does the master fader. */
    audio_bus_set_gain(&as, AUDIO_BUS_MASTER, 0.5f);
    ASSERT_FLOAT_EQ(audio_source_effective_gain(&as, &as.sources[0]), 0.2f, 1e-6);

    /* Invalid bus id in set_bus falls back to master routing. */
    audio_source_set_bus(&as, h, 999u);
    ASSERT_EQ(as.sources[0].bus, AUDIO_BUS_MASTER);
    ASSERT_FLOAT_EQ(audio_source_effective_gain(&as, &as.sources[0]), 0.4f, 1e-6);
}

TEST(master_gain_reapplies_to_sub_bus_sources)
{
    /* R462: changing the master fader must also update sources routed through
     * a non-master bus. applied_gain mirrors the value sent to miniaudio. */
    AudioSystem as;
    AudioSource srcs[1];
    test_sys_init(&as, srcs, 1);
    as.source_count = 1;

    u32 music = audio_bus_create(&as, "music");
    u32 h = audio_make_handle(&as.sources[0], 0);
    audio_source_set_volume(&as, h, 0.8f);
    audio_source_set_bus(&as, h, music);
    ASSERT_FLOAT_EQ(as.sources[0].applied_gain, 0.8f, 1e-6);

    audio_bus_set_gain(&as, AUDIO_BUS_MASTER, 0.5f);
    ASSERT_FLOAT_EQ(as.sources[0].applied_gain, 0.4f, 1e-6);
}

TEST(source_on_master_bus_not_double_counted)
{
    /* The master bus IS the master fader: a source routed to bus 0 must get
     * volume x master, NOT volume x master x master. */
    AudioSystem as;
    AudioSource srcs[1];
    test_sys_init(&as, srcs, 1);
    as.source_count = 1;

    u32 h = audio_make_handle(&as.sources[0], 0);
    audio_source_set_volume(&as, h, 1.0f);
    audio_source_set_bus(&as, h, AUDIO_BUS_MASTER);
    audio_bus_set_gain(&as, AUDIO_BUS_MASTER, 0.5f);
    ASSERT_FLOAT_EQ(audio_source_effective_gain(&as, &as.sources[0]), 0.5f, 1e-6);
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
    RUN_TEST(bus_master_always_present);
    RUN_TEST(bus_create_assigns_sequential_ids);
    RUN_TEST(bus_create_full_table_returns_invalid);
    RUN_TEST(bus_set_gain_clamps_negative);
    RUN_TEST(bus_invalid_id_rejected_falls_back_master);
    RUN_TEST(effective_gain_pure_composition);
    RUN_TEST(source_bus_volume_compose_and_fallback);
    RUN_TEST(master_gain_reapplies_to_sub_bus_sources);
    RUN_TEST(source_on_master_bus_not_double_counted);
TEST_MAIN_END()
