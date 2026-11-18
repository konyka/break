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
 * Must precede all system includes. On macOS the engine does not pin
 * _POSIX_C_SOURCE (Linux-only, see CMakeLists), and defining it there hides
 * snprintf/vsnprintf from the SDK headers under strict c11. */
#if !defined(__APPLE__)
#define _POSIX_C_SOURCE 199309L
#endif

#include "test_framework.h"
#include <stdatomic.h>
#include <time.h>
#include <audio/audio.h>
#include <audio/audio_extended.h>
#include <core/platform_thread.h>

static atomic_bool reference_hook_armed;
static atomic_bool reference_hook_entered;
static atomic_bool reference_hook_release;

static void reference_test_hook(void *opaque)
{
    (void)opaque;
    if (!atomic_load_explicit(&reference_hook_armed, memory_order_acquire)) return;
    atomic_store_explicit(&reference_hook_entered, true, memory_order_release);
    while (!atomic_load_explicit(&reference_hook_release, memory_order_acquire)) {
        platform_thread_yield();
    }
}

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
    f32 far_gain = audio_attenuation_gain(1000.0f, 2.0f, 40.0f, 1.0f);
    ASSERT_FLOAT_EQ(at_max, far_gain, 1e-5);
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

/* The backend name is the evidence that a device run actually reached a
 * playback backend; a null or fake system must never report a device one. */
TEST(backend_name_reports_null_backend)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_NULL);
    ASSERT_NOT_NULL(as);
    ASSERT_STR_EQ(audio_system_backend_name(as), "Null");
    audio_system_destroy(as);
}

TEST(backend_name_reports_fake_without_device)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_STR_EQ(audio_system_backend_name(as), "fake");
    audio_system_destroy(as);
}

TEST(backend_name_of_missing_system_is_none)
{
    ASSERT_STR_EQ(audio_system_backend_name(NULL), "none");
}

TEST(device_name_reports_the_null_playback_device)
{
    char name[128];
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_NULL);
    ASSERT_NOT_NULL(as);
    ASSERT_TRUE(audio_system_device_name(as, name, sizeof(name)));
    ASSERT_TRUE(name[0] != '\0');
    audio_system_destroy(as);
}

TEST(device_name_is_absent_without_a_device)
{
    char name[128] = "unchanged";
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_FALSE(audio_system_device_name(as, name, sizeof(name)));
    ASSERT_STR_EQ(name, "none");
    audio_system_destroy(as);
    ASSERT_FALSE(audio_system_device_name(NULL, name, sizeof(name)));
    ASSERT_FALSE(audio_system_device_name(NULL, NULL, 0u));
}

/* Writes a 0.1 s mono 16-bit 48 kHz square wave so the play tests do not
 * depend on an asset directory. Returns false if the file cannot be written. */
static bool write_test_wav(const char *path)
{
    const u32 frames = 4800u;
    const u32 data_bytes = frames * 2u;
    u8 header[44] = {
        'R','I','F','F', 0,0,0,0, 'W','A','V','E', 'f','m','t',' ',
        16,0,0,0, 1,0, 1,0, 0x80,0xBB,0,0, 0,0x77,1,0, 2,0, 16,0,
        'd','a','t','a', 0,0,0,0 };
    u32 riff = 36u + data_bytes;
    memcpy(header + 4, &riff, 4);
    memcpy(header + 40, &data_bytes, 4);
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    bool ok = fwrite(header, 1, sizeof(header), f) == sizeof(header);
    for (u32 i = 0; ok && i < frames; ++i) {
        i16 sample = (i / 50u) % 2u ? 4000 : -4000;
        ok = fwrite(&sample, 1, 2, f) == 2;
    }
    return fclose(f) == 0 && ok;
}

/* Picks a writable scratch directory on POSIX and Windows hosts alike. */
static const char *test_temp_dir(void)
{
    static const char *const kVars[] = {"TMPDIR", "TEMP", "TMP"};
    for (size_t i = 0; i < sizeof(kVars) / sizeof(kVars[0]); ++i) {
        const char *dir = getenv(kVars[i]);
        if (dir && dir[0]) return dir;
    }
    return ".";
}

TEST(play_3d_source_returns_a_stoppable_handle)
{
    char path[512];
    snprintf(path, sizeof(path), "%s/break_test_audio_%ld.wav", test_temp_dir(),
             (long)clock());
    ASSERT_TRUE(write_test_wav(path));
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    u32 handle = audio_play_3d_source(as, path, vec3(1.0f, 0.0f, 0.0f), 0.5f, false);
    ASSERT_TRUE(handle != 0u);
    ASSERT_FALSE(audio_source_at_end(as, handle));
    audio_source_set_position(as, handle, vec3(2.0f, 0.0f, 0.0f));
    audio_stop(as, handle);
    /* After stop the handle is stale: queries treat it as ended. */
    ASSERT_TRUE(audio_source_at_end(as, handle));
    audio_system_destroy(as);
    remove(path);
}

TEST(play_3d_source_reports_failure_as_zero)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_EQ(audio_play_3d_source(as, "/nonexistent/break.wav", vec3(0, 0, 0), 1.0f, false),
              0u);
    ASSERT_EQ(audio_play_3d_source(as, NULL, vec3(0, 0, 0), 1.0f, false), 0u);
    ASSERT_EQ(audio_play_3d_source(NULL, "x.wav", vec3(0, 0, 0), 1.0f, false), 0u);
    audio_system_destroy(as);
}

static AudioResult reference_render_silence(AudioSystem *as, u32 frames)
{
    f32 output[510] = {0};
    while (frames > 0u) {
        const u32 block = frames < 255u ? frames : 255u;
        const AudioResult result = audio_system_render(as, output, block);
        if (result != AUDIO_OK) return result;
        frames -= block;
    }
    return AUDIO_OK;
}

TEST(reference_disabled_until_started_and_validates_calls)
{
    i16 out[8];
    u32 frames = 99u;
    ASSERT_EQ(audio_reference_start(NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_reference_stop(NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_reference_reset(NULL), AUDIO_INVALID);
    ASSERT_EQ(audio_reference_available(NULL), 0u);
    ASSERT_EQ(audio_reference_overruns(NULL), 0u);
    ASSERT_EQ(audio_reference_read_i16(NULL, out, 8u, &frames), AUDIO_INVALID);
    ASSERT_EQ(frames, 99u);

    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_EQ(audio_reference_read_i16(as, NULL, 8u, &frames), AUDIO_INVALID);
    ASSERT_EQ(frames, 99u);
    ASSERT_EQ(audio_reference_read_i16(as, out, 8u, NULL), AUDIO_INVALID);
    ASSERT_EQ(reference_render_silence(as, 4u), AUDIO_OK);
    ASSERT_EQ(audio_reference_available(as), 0u);
    ASSERT_EQ(audio_reference_read_i16(as, out, 0u, &frames), AUDIO_OK);
    ASSERT_EQ(frames, 0u);

    ASSERT_EQ(audio_reference_start(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_start(as), AUDIO_OK);
    ASSERT_EQ(reference_render_silence(as, 4u), AUDIO_OK);
    ASSERT_EQ(audio_reference_available(as), 4u);
    ASSERT_EQ(audio_reference_reset(as), AUDIO_REJECTED);
    ASSERT_EQ(audio_reference_available(as), 4u);
    ASSERT_EQ(audio_reference_stop(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_stop(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_read_i16(as, out, 8u, &frames), AUDIO_OK);
    ASSERT_EQ(frames, 4u);
    for (u32 i = 0u; i < frames; ++i) ASSERT_EQ(out[i], 0);
    ASSERT_EQ(audio_reference_reset(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_available(as), 0u);
    ASSERT_EQ(audio_reference_overruns(as), 0u);
    audio_system_destroy(as);
}

TEST(reference_tap_matches_final_stereo_mix)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_EQ(audio_reference_start(as), AUDIO_OK);
    AudioPcmStreamHandle stream = 0u;
    ASSERT_EQ(audio_pcm_stream_open(as, 2u, AUDIO_BUS_MASTER, 1.0f, &stream), AUDIO_OK);
    const i16 input[] = {1000, -1000, -2000, 2000, 3000, 1000, -4000, -2000};
    u32 written = 0u;
    ASSERT_EQ(audio_pcm_stream_write_i16(as, stream, input, 4u, &written), AUDIO_OK);
    ASSERT_EQ(written, 4u);
    f32 stereo[8];
    ASSERT_EQ(audio_system_render(as, stereo, 4u), AUDIO_OK);

    i16 reference[4];
    u32 frames = 0u;
    ASSERT_EQ(audio_reference_read_i16(as, reference, 4u, &frames), AUDIO_OK);
    ASSERT_EQ(frames, 4u);
    for (u32 i = 0u; i < 4u; ++i) {
        ASSERT_TRUE(isfinite(stereo[2u * i]));
        ASSERT_TRUE(isfinite(stereo[2u * i + 1u]));
        ASSERT_FLOAT_EQ(stereo[2u * i], (f32)input[2u * i] / 32768.0f, 1e-6f);
        ASSERT_FLOAT_EQ(stereo[2u * i + 1u], (f32)input[2u * i + 1u] / 32768.0f,
                        1e-6f);
        f32 mono = 0.5f * (stereo[2u * i] + stereo[2u * i + 1u]);
        if (!isfinite(mono)) mono = 0.0f;
        if (mono > 1.0f) mono = 1.0f;
        if (mono < -1.0f) mono = -1.0f;
        ASSERT_EQ(reference[i], (i16)lrintf(mono * 32767.0f));
    }
    ASSERT_EQ(audio_reference_stop(as), AUDIO_OK);
    ASSERT_EQ(reference_render_silence(as, 4u), AUDIO_OK);
    ASSERT_EQ(audio_reference_available(as), 0u);
    ASSERT_EQ(audio_pcm_stream_close(as, stream), AUDIO_OK);
    audio_system_destroy(as);
}

TEST(reference_ring_is_bounded_and_resettable_when_stopped)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_EQ(audio_reference_start(as), AUDIO_OK);
    AudioPcmStreamHandle stream = 0u;
    ASSERT_EQ(audio_pcm_stream_open(as, 2u, AUDIO_BUS_MASTER, 1.0f, &stream), AUDIO_OK);
    i16 expected[AUDIO_REFERENCE_RING_FRAMES];
    u32 produced = 0u;
    while (produced < AUDIO_REFERENCE_RING_FRAMES + 256u) {
        const u32 block = AUDIO_REFERENCE_RING_FRAMES + 256u - produced < 255u
                              ? AUDIO_REFERENCE_RING_FRAMES + 256u - produced
                              : 255u;
        i16 input[510];
        f32 rendered[510];
        for (u32 i = 0u; i < block; ++i) {
            const u32 index = produced + i;
            input[2u * i] = (i16)((i32)(index % 30000u) - 15000);
            input[2u * i + 1u] = (i16)(1000 - (i32)(index % 2000u));
        }
        u32 written = 0u;
        ASSERT_EQ(audio_pcm_stream_write_i16(as, stream, input, block, &written), AUDIO_OK);
        ASSERT_EQ(written, block);
        ASSERT_EQ(audio_system_render(as, rendered, block), AUDIO_OK);
        for (u32 i = 0u; i < block; ++i) {
            f32 mono = 0.5f * (rendered[2u * i] + rendered[2u * i + 1u]);
            if (!isfinite(mono)) mono = 0.0f;
            if (mono > 1.0f) mono = 1.0f;
            if (mono < -1.0f) mono = -1.0f;
            if (produced + i < AUDIO_REFERENCE_RING_FRAMES) {
                expected[produced + i] = (i16)lrintf(mono * 32767.0f);
            }
        }
        produced += block;
    }
    ASSERT_EQ(audio_reference_available(as), AUDIO_REFERENCE_RING_FRAMES);
    ASSERT_EQ(audio_reference_overruns(as), 256u);

    i16 out[256];
    u32 total = 0u;
    while (total < AUDIO_REFERENCE_RING_FRAMES) {
        u32 frames = 0u;
        ASSERT_EQ(audio_reference_read_i16(as, out, 255u, &frames), AUDIO_OK);
        ASSERT_TRUE(frames > 0u);
        for (u32 i = 0u; i < frames; ++i) ASSERT_EQ(out[i], expected[total + i]);
        total += frames;
    }
    ASSERT_EQ(total, AUDIO_REFERENCE_RING_FRAMES);
    ASSERT_EQ(audio_reference_available(as), 0u);
    ASSERT_EQ(audio_reference_stop(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_reset(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_overruns(as), 0u);

    ASSERT_EQ(audio_reference_start(as), AUDIO_OK);
    ASSERT_EQ(reference_render_silence(as, AUDIO_REFERENCE_RING_FRAMES), AUDIO_OK);
    total = 0u;
    while (total < AUDIO_REFERENCE_RING_FRAMES) {
        u32 frames = 0u;
        ASSERT_EQ(audio_reference_read_i16(as, out, 256u, &frames), AUDIO_OK);
        ASSERT_TRUE(frames > 0u);
        total += frames;
    }
    ASSERT_EQ(total, AUDIO_REFERENCE_RING_FRAMES);
    ASSERT_EQ(audio_reference_stop(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_reset(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_available(as), 0u);
    ASSERT_EQ(audio_reference_overruns(as), 0u);
    ASSERT_EQ(audio_pcm_stream_close(as, stream), AUDIO_OK);
    audio_system_destroy(as);
}

typedef struct {
    AudioSystem *system;
    u32 total;
    AudioResult result;
    atomic_bool done;
} ReferenceRenderJob;

static PLATFORM_THREAD_RET reference_render_main(PLATFORM_THREAD_ARG argument)
{
    ReferenceRenderJob *job = (ReferenceRenderJob *)argument;
    f32 output[512];
    u32 produced = 0u;
    job->result = AUDIO_OK;
    while (produced < job->total) {
        while (audio_reference_available(job->system) > AUDIO_REFERENCE_RING_FRAMES / 2u) {
            platform_thread_yield();
        }
        const u32 block = job->total - produced < 256u ? job->total - produced : 256u;
        memset(output, 0, sizeof(output));
        job->result = audio_system_render(job->system, output, block);
        if (job->result != AUDIO_OK) break;
        produced += block;
    }
    atomic_store_explicit(&job->done, true, memory_order_release);
    return PLATFORM_THREAD_RETURN;
}

TEST(reference_concurrent_render_and_read_wrap_without_overruns)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_EQ(audio_reference_start(as), AUDIO_OK);
    ReferenceRenderJob job;
    job.system = as;
    job.total = AUDIO_REFERENCE_RING_FRAMES * 2u;
    job.result = AUDIO_OK;
    atomic_init(&job.done, false);
    PlatformThread thread;
    const bool created = platform_thread_create(&thread, reference_render_main, &job);
    if (!created) audio_system_destroy(as);
    ASSERT_TRUE(created);

    i16 out[256];
    u32 received = 0u;
    AudioResult read_result = AUDIO_OK;
    while (received < job.total) {
        u32 frames = 0u;
        read_result = audio_reference_read_i16(as, out, 256u, &frames);
        if (read_result != AUDIO_OK) break;
        received += frames;
        if (frames == 0u) {
            if (atomic_load_explicit(&job.done, memory_order_acquire)) break;
            platform_thread_yield();
        }
    }
    platform_thread_join(thread);
    ASSERT_EQ(read_result, AUDIO_OK);
    ASSERT_EQ(job.result, AUDIO_OK);
    ASSERT_EQ(received, job.total);
    ASSERT_EQ(audio_reference_available(as), 0u);
    ASSERT_EQ(audio_reference_overruns(as), 0u);
    ASSERT_EQ(audio_reference_stop(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_reset(as), AUDIO_OK);
    audio_system_destroy(as);
}

TEST(reference_restart_rejects_pre_stop_callback)
{
    AudioSystem *as = audio_system_create_ex(AUDIO_BACKEND_FAKE);
    ASSERT_NOT_NULL(as);
    ASSERT_EQ(audio_reference_start(as), AUDIO_OK);
    atomic_store_explicit(&reference_hook_armed, true, memory_order_release);
    atomic_store_explicit(&reference_hook_entered, false, memory_order_relaxed);
    atomic_store_explicit(&reference_hook_release, false, memory_order_relaxed);
    ReferenceRenderJob job;
    job.system = as;
    job.total = 256u;
    job.result = AUDIO_OK;
    atomic_init(&job.done, false);
    PlatformThread thread;
    const bool created = platform_thread_create(&thread, reference_render_main, &job);
    if (!created) {
        atomic_store_explicit(&reference_hook_armed, false, memory_order_release);
        audio_system_destroy(as);
    }
    ASSERT_TRUE(created);
    while (!atomic_load_explicit(&reference_hook_entered, memory_order_acquire) &&
           !atomic_load_explicit(&job.done, memory_order_acquire)) {
        platform_thread_yield();
    }
    const bool entered = atomic_load_explicit(&reference_hook_entered, memory_order_acquire);
    if (!entered) {
        platform_thread_join(thread);
        atomic_store_explicit(&reference_hook_armed, false, memory_order_release);
        audio_system_destroy(as);
    }
    ASSERT_TRUE(entered);

    const AudioResult stop_result = audio_reference_stop(as);
    const AudioResult reset_result = audio_reference_reset(as);
    const AudioResult start_result = audio_reference_start(as);
    atomic_store_explicit(&reference_hook_release, true, memory_order_release);
    platform_thread_join(thread);
    atomic_store_explicit(&reference_hook_armed, false, memory_order_release);
    ASSERT_EQ(stop_result, AUDIO_OK);
    ASSERT_EQ(reset_result, AUDIO_OK);
    ASSERT_EQ(start_result, AUDIO_OK);
    ASSERT_EQ(job.result, AUDIO_OK);
    ASSERT_EQ(audio_reference_available(as), 0u);
    ASSERT_EQ(audio_reference_overruns(as), 0u);
    ASSERT_EQ(audio_reference_stop(as), AUDIO_OK);
    ASSERT_EQ(audio_reference_reset(as), AUDIO_OK);
    audio_system_destroy(as);
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
    RUN_TEST(backend_name_reports_null_backend);
    RUN_TEST(backend_name_reports_fake_without_device);
    RUN_TEST(backend_name_of_missing_system_is_none);
    RUN_TEST(device_name_reports_the_null_playback_device);
    RUN_TEST(device_name_is_absent_without_a_device);
    RUN_TEST(play_3d_source_returns_a_stoppable_handle);
    RUN_TEST(play_3d_source_reports_failure_as_zero);
    RUN_TEST(reference_disabled_until_started_and_validates_calls);
    RUN_TEST(reference_tap_matches_final_stereo_mix);
    RUN_TEST(reference_ring_is_bounded_and_resettable_when_stopped);
    RUN_TEST(reference_concurrent_render_and_read_wrap_without_overruns);
    RUN_TEST(reference_restart_rejects_pre_stop_callback);
TEST_MAIN_END()
