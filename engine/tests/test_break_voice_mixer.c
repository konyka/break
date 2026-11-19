#include "test_framework.h"
#include <network/break_voice_mixer.h>

#include <core/platform_thread.h>

#include <stdint.h>
#include <string.h>

/* 1000 Hz mono, 10 samples: one frame every 10 ms, no jitter delay. */
static BreakVoiceMixerConfig mixer_config(u32 max_sources, u32 idle_timeout_ms)
{
    BreakVoiceMixerConfig config;
    memset(&config, 0, sizeof(config));
    config.stream.sample_rate = 1000u;
    config.stream.channels = 1u;
    config.stream.sample_count = 10u;
    config.stream.jitter_delay_ms = 0u;
    config.stream.jitter_capacity = 8u;
    config.stream.queue_capacity = 8u;
    config.max_sources = max_sources;
    config.idle_timeout_ms = idle_timeout_ms;
    return config;
}

static BreakVoiceMixer *make_mixer(u32 max_sources, u32 idle_timeout_ms)
{
    const BreakVoiceMixerConfig config = mixer_config(max_sources, idle_timeout_ms);
    BreakVoiceMixer *mixer = NULL;
    if (break_voice_mixer_create(&config, &mixer) != BREAK_RUNTIME_OK) return NULL;
    return mixer;
}

static BreakRuntimeError push_tone(BreakVoiceMixer *mixer, u64 source, u32 sequence,
                                   i16 first, u64 now_ms)
{
    BreakVoiceFrame frame;
    memset(&frame, 0, sizeof(frame));
    frame.sequence = sequence;
    frame.sample_rate = 1000u;
    frame.channels = 1u;
    frame.sample_count = 10u;
    for (u32 i = 0u; i < 10u; ++i) frame.samples[i] = (i16)(first + (i16)i);
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    BreakRuntimeError result = break_voice_encode(&frame, packet, sizeof(packet), &size);
    if (result != BREAK_RUNTIME_OK) return result;
    return break_voice_mixer_push(mixer, source, packet, size, now_ms);
}

static BreakVoiceMixerStats mixer_stats(BreakVoiceMixer *mixer)
{
    BreakVoiceMixerStats stats;
    memset(&stats, 0, sizeof(stats));
    if (break_voice_mixer_stats(mixer, &stats) != BREAK_RUNTIME_OK) stats.sources = UINT32_MAX;
    return stats;
}

TEST(mixer_sums_two_sources_exactly)
{
    BreakVoiceMixer *mixer = make_mixer(4u, 0u);
    ASSERT_NOT_NULL(mixer);
    ASSERT_EQ(push_tone(mixer, 11u, 0u, 1000, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 22u, 0u, 2000, 0u), BREAK_RUNTIME_OK);
    BreakVoicePlayback out;
    bool ready = false;
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(out.sequence, 0u);
    ASSERT_EQ(out.sample_count, 10u);
    ASSERT_FALSE(out.concealed);
    for (u32 i = 0u; i < 10u; ++i) ASSERT_EQ(out.samples[i], (i16)(3000 + 2 * (i32)i));
    /* the next frame is not due yet */
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ready);
    const BreakVoiceMixerStats stats = mixer_stats(mixer);
    ASSERT_EQ(stats.sources, 2u);
    ASSERT_EQ(stats.sources_created, 2u);
    ASSERT_EQ(stats.mixed_frames, 1u);
    ASSERT_EQ(stats.clipped_samples, 0u);
    ASSERT_EQ(stats.accepted, 2u);
    ASSERT_EQ(stats.played, 2u);
    break_voice_mixer_destroy(mixer);
}

TEST(mixer_saturates_and_counts_clipped_samples)
{
    BreakVoiceMixer *mixer = make_mixer(4u, 0u);
    ASSERT_NOT_NULL(mixer);
    ASSERT_EQ(push_tone(mixer, 1u, 0u, 20000, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 2u, 0u, 20000, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 1u, 1u, -20000, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 2u, 1u, -20000, 0u), BREAK_RUNTIME_OK);
    BreakVoicePlayback out;
    bool ready = false;
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    for (u32 i = 0u; i < 10u; ++i) ASSERT_EQ(out.samples[i], 32767);
    ASSERT_EQ(break_voice_mixer_pop(mixer, 10u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    for (u32 i = 0u; i < 10u; ++i) ASSERT_EQ(out.samples[i], -32768);
    ASSERT_EQ(mixer_stats(mixer).clipped_samples, 20u);
    break_voice_mixer_destroy(mixer);
}

TEST(mixer_output_is_concealed_only_when_every_input_is)
{
    BreakVoiceMixer *mixer = make_mixer(4u, 0u);
    ASSERT_NOT_NULL(mixer);
    /* A skips sequence 1 and 3; B stops after sequence 1 */
    ASSERT_EQ(push_tone(mixer, 1u, 0u, 100, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 2u, 0u, 1000, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 1u, 2u, 300, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 2u, 1u, 2000, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 1u, 4u, 500, 0u), BREAK_RUNTIME_OK);
    BreakVoicePlayback out;
    bool ready = false;
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(out.samples[0], 1100);
    /* A conceals, B plays: the mix is B alone and not concealed */
    ASSERT_EQ(break_voice_mixer_pop(mixer, 10u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_FALSE(out.concealed);
    ASSERT_EQ(out.samples[0], 2000);
    ASSERT_EQ(out.samples[9], 2009);
    ASSERT_EQ(break_voice_mixer_pop(mixer, 20u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_FALSE(out.concealed);
    ASSERT_EQ(out.samples[0], 300);
    /* only A contributes, and it conceals */
    ASSERT_EQ(break_voice_mixer_pop(mixer, 30u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_TRUE(out.concealed);
    ASSERT_EQ(out.sequence, 3u);
    for (u32 i = 0u; i < 10u; ++i) ASSERT_EQ(out.samples[i], 0);
    const BreakVoiceMixerStats stats = mixer_stats(mixer);
    ASSERT_EQ(stats.concealed, 2u);
    ASSERT_EQ(stats.mixed_frames, 4u);
    break_voice_mixer_destroy(mixer);
}

typedef struct OtherThread {
    BreakVoiceMixer *mixer;
    BreakRuntimeError pop;
    BreakRuntimeError push;
} OtherThread;

static PLATFORM_THREAD_RET use_elsewhere(PLATFORM_THREAD_ARG argument)
{
    OtherThread *other = (OtherThread *)argument;
    BreakVoicePlayback out;
    bool ready = false;
    other->pop = break_voice_mixer_pop(other->mixer, 0u, &out, &ready);
    other->push = push_tone(other->mixer, 9u, 0u, 1, 0u);
    return PLATFORM_THREAD_RETURN;
}

TEST(mixer_validates_arguments_and_owner)
{
    BreakVoiceMixer *mixer = NULL;
    BreakVoiceMixerConfig config = mixer_config(4u, 0u);
    ASSERT_EQ(break_voice_mixer_create(NULL, &mixer), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_voice_mixer_create(&config, NULL), BREAK_RUNTIME_INVALID);
    config.max_sources = 0u;
    ASSERT_EQ(break_voice_mixer_create(&config, &mixer), BREAK_RUNTIME_INVALID);
    config.max_sources = BREAK_VOICE_MIXER_MAX_SOURCES + 1u;
    ASSERT_EQ(break_voice_mixer_create(&config, &mixer), BREAK_RUNTIME_INVALID);
    config = mixer_config(4u, 0u);
    config.stream.sample_rate = 0u;
    ASSERT_EQ(break_voice_mixer_create(&config, &mixer), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(mixer == NULL);

    mixer = make_mixer(BREAK_VOICE_MIXER_MAX_SOURCES, 0u);
    ASSERT_NOT_NULL(mixer);
    u8 byte = 0u;
    ASSERT_EQ(break_voice_mixer_push(mixer, 0u, &byte, 1u, 0u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_voice_mixer_push(mixer, 1u, NULL, 1u, 0u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_voice_mixer_push(NULL, 1u, &byte, 1u, 0u), BREAK_RUNTIME_INVALID);
    BreakVoicePlayback out;
    bool ready = true;
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, NULL, &ready), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, &out, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ready);
    ASSERT_EQ(break_voice_mixer_stats(mixer, NULL), BREAK_RUNTIME_INVALID);

    OtherThread other = {mixer, BREAK_RUNTIME_OK, BREAK_RUNTIME_OK};
    PlatformThread thread;
    ASSERT_TRUE(platform_thread_create(&thread, use_elsewhere, &other));
    platform_thread_join(thread);
    ASSERT_EQ(other.pop, BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(other.push, BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(mixer_stats(mixer).sources, 0u);
    break_voice_mixer_destroy(mixer);
    break_voice_mixer_destroy(NULL);
}

TEST(mixer_refuses_a_source_beyond_the_limit_until_one_is_idle)
{
    BreakVoiceMixer *mixer = make_mixer(2u, 100u);
    ASSERT_NOT_NULL(mixer);
    ASSERT_EQ(push_tone(mixer, 1u, 0u, 1, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 2u, 0u, 1, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 3u, 0u, 1, 50u), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(push_tone(mixer, 2u, 1u, 1, 60u), BREAK_RUNTIME_OK);
    /* source 1 has been idle for 100 ms, source 2 for 40 ms */
    ASSERT_EQ(push_tone(mixer, 3u, 0u, 1, 100u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 1u, 1u, 1, 100u), BREAK_RUNTIME_OVERLOAD);
    BreakVoiceMixerStats stats = mixer_stats(mixer);
    ASSERT_EQ(stats.sources, 2u);
    ASSERT_EQ(stats.sources_created, 3u);
    ASSERT_EQ(stats.sources_evicted, 1u);
    ASSERT_EQ(stats.sources_refused, 2u);
    break_voice_mixer_destroy(mixer);

    /* idle_timeout_ms 0: a source is never evicted */
    mixer = make_mixer(1u, 0u);
    ASSERT_NOT_NULL(mixer);
    ASSERT_EQ(push_tone(mixer, 1u, 0u, 1, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 2u, 0u, 1, 1000000u), BREAK_RUNTIME_OVERLOAD);
    stats = mixer_stats(mixer);
    ASSERT_EQ(stats.sources_evicted, 0u);
    ASSERT_EQ(stats.sources_refused, 1u);
    break_voice_mixer_destroy(mixer);
}

TEST(mixer_ignores_a_malformed_frame_from_one_source)
{
    BreakVoiceMixer *mixer = make_mixer(4u, 0u);
    ASSERT_NOT_NULL(mixer);
    ASSERT_EQ(push_tone(mixer, 1u, 0u, 1000, 0u), BREAK_RUNTIME_OK);
    const u8 garbage[5] = {1u, 2u, 3u, 4u, 5u};
    ASSERT_EQ(break_voice_mixer_push(mixer, 2u, garbage, sizeof(garbage), 0u),
              BREAK_RUNTIME_OK);
    BreakVoicePlayback out;
    bool ready = false;
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    for (u32 i = 0u; i < 10u; ++i) ASSERT_EQ(out.samples[i], (i16)(1000 + (i32)i));
    const BreakVoiceMixerStats stats = mixer_stats(mixer);
    ASSERT_EQ(stats.invalid, 1u);
    ASSERT_EQ(stats.played, 1u);
    break_voice_mixer_destroy(mixer);
}

TEST(mixer_evicts_the_source_idle_longest)
{
    BreakVoiceMixer *mixer = make_mixer(3u, 100u);
    ASSERT_NOT_NULL(mixer);
    ASSERT_EQ(push_tone(mixer, 1u, 0u, 1, 50u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 2u, 0u, 1, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 3u, 0u, 1, 300u), BREAK_RUNTIME_OK);
    /* at 200 ms sources 1 (150 ms) and 2 (200 ms) are both idle: 2 goes */
    ASSERT_EQ(push_tone(mixer, 4u, 0u, 1, 200u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_tone(mixer, 1u, 1u, 1, 200u), BREAK_RUNTIME_OK);
    BreakVoiceMixerStats stats = mixer_stats(mixer);
    ASSERT_EQ(stats.sources, 3u);
    ASSERT_EQ(stats.sources_created, 4u);
    /* source 2 is gone, so it needs a free entry and finds none */
    ASSERT_EQ(push_tone(mixer, 2u, 1u, 1, 200u), BREAK_RUNTIME_OVERLOAD);
    break_voice_mixer_destroy(mixer);
}

TEST(mixer_receiver_counts_survive_an_eviction)
{
    BreakVoiceMixer *mixer = make_mixer(1u, 10u);
    ASSERT_NOT_NULL(mixer);
    ASSERT_EQ(push_tone(mixer, 1u, 0u, 1, 0u), BREAK_RUNTIME_OK);
    const u8 garbage[5] = {1u, 2u, 3u, 4u, 5u};
    ASSERT_EQ(break_voice_mixer_push(mixer, 1u, garbage, sizeof(garbage), 0u),
              BREAK_RUNTIME_OK);
    BreakVoicePlayback out;
    bool ready = false;
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(push_tone(mixer, 2u, 0u, 1, 50u), BREAK_RUNTIME_OK);
    const BreakVoiceMixerStats stats = mixer_stats(mixer);
    ASSERT_EQ(stats.sources_evicted, 1u);
    ASSERT_EQ(stats.accepted, 2u);
    ASSERT_EQ(stats.played, 1u);
    ASSERT_EQ(stats.invalid, 1u);
    break_voice_mixer_destroy(mixer);
}

TEST(mixer_refuses_an_oversized_frame_without_taking_an_entry)
{
    BreakVoiceMixer *mixer = make_mixer(1u, 0u);
    ASSERT_NOT_NULL(mixer);
    u8 big[BREAK_VOICE_MAX_DATAGRAM_SIZE + 1u];
    memset(big, 0, sizeof(big));
    ASSERT_EQ(break_voice_mixer_push(mixer, 7u, big, sizeof(big), 0u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_voice_mixer_push(mixer, 7u, big, 0u, 0u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(mixer_stats(mixer).sources, 0u);
    ASSERT_EQ(mixer_stats(mixer).sources_created, 0u);
    /* the single entry is still free for a well-formed frame */
    ASSERT_EQ(push_tone(mixer, 8u, 0u, 1, 0u), BREAK_RUNTIME_OK);
    break_voice_mixer_destroy(mixer);
}

typedef struct ElsewhereStats {
    BreakVoiceMixer *mixer;
    BreakRuntimeError stats;
} ElsewhereStats;

static PLATFORM_THREAD_RET stats_and_destroy_elsewhere(PLATFORM_THREAD_ARG argument)
{
    ElsewhereStats *other = (ElsewhereStats *)argument;
    BreakVoiceMixerStats stats;
    other->stats = break_voice_mixer_stats(other->mixer, &stats);
    break_voice_mixer_destroy(other->mixer);
    return PLATFORM_THREAD_RETURN;
}

TEST(mixer_stats_and_destroy_stay_on_the_owner_thread)
{
    BreakVoiceMixer *mixer = make_mixer(4u, 0u);
    ASSERT_NOT_NULL(mixer);
    ASSERT_EQ(push_tone(mixer, 1u, 0u, 1, 0u), BREAK_RUNTIME_OK);
    ElsewhereStats other = {mixer, BREAK_RUNTIME_OK};
    PlatformThread thread;
    ASSERT_TRUE(platform_thread_create(&thread, stats_and_destroy_elsewhere, &other));
    platform_thread_join(thread);
    ASSERT_EQ(other.stats, BREAK_RUNTIME_REJECTED);
    /* destroy off the owner thread is a no-op: the mixer still works */
    ASSERT_EQ(push_tone(mixer, 2u, 0u, 1, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(mixer_stats(mixer).sources, 2u);
    break_voice_mixer_destroy(mixer);
}

TEST(mixer_sums_every_source_at_the_limit)
{
    BreakVoiceMixer *mixer = make_mixer(BREAK_VOICE_MIXER_MAX_SOURCES, 0u);
    ASSERT_NOT_NULL(mixer);
    for (u32 i = 0u; i < BREAK_VOICE_MIXER_MAX_SOURCES; ++i) {
        ASSERT_EQ(push_tone(mixer, 100u + i, 0u, 1000, 0u), BREAK_RUNTIME_OK);
    }
    BreakVoicePlayback out;
    bool ready = false;
    ASSERT_EQ(break_voice_mixer_pop(mixer, 0u, &out, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    for (u32 i = 0u; i < 10u; ++i) {
        ASSERT_EQ(out.samples[i], (i16)(BREAK_VOICE_MIXER_MAX_SOURCES * (1000u + i)));
    }
    ASSERT_EQ(mixer_stats(mixer).clipped_samples, 0u);
    break_voice_mixer_destroy(mixer);
}

TEST_MAIN_BEGIN()
    RUN_TEST(mixer_evicts_the_source_idle_longest);
    RUN_TEST(mixer_receiver_counts_survive_an_eviction);
    RUN_TEST(mixer_refuses_an_oversized_frame_without_taking_an_entry);
    RUN_TEST(mixer_stats_and_destroy_stay_on_the_owner_thread);
    RUN_TEST(mixer_sums_every_source_at_the_limit);
    RUN_TEST(mixer_sums_two_sources_exactly);
    RUN_TEST(mixer_saturates_and_counts_clipped_samples);
    RUN_TEST(mixer_output_is_concealed_only_when_every_input_is);
    RUN_TEST(mixer_validates_arguments_and_owner);
    RUN_TEST(mixer_refuses_a_source_beyond_the_limit_until_one_is_idle);
    RUN_TEST(mixer_ignores_a_malformed_frame_from_one_source);
TEST_MAIN_END()
