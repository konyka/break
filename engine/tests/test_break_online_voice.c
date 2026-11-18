#include "test_framework.h"
#include <network/break_online_voice.h>

#include <math.h>
#include <stdint.h>
#include <string.h>

static BreakVoiceStreamConfig voice_config(u32 sample_rate, u16 channels,
                                           u16 sample_count, u32 delay_ms)
{
    BreakVoiceStreamConfig config;
    memset(&config, 0, sizeof(config));
    config.sample_rate = sample_rate;
    config.channels = channels;
    config.sample_count = sample_count;
    config.jitter_delay_ms = delay_ms;
    config.jitter_capacity = 8u;
    config.queue_capacity = 8u;
    return config;
}

static BreakVoiceReceiver *make_receiver(BreakVoiceStreamConfig config)
{
    BreakVoiceReceiver *receiver = NULL;
    if (break_voice_receiver_create(NULL, &config, &receiver) != BREAK_RUNTIME_OK) return NULL;
    return receiver;
}

static BreakVoiceFrame make_frame(u32 sequence, u32 sample_rate, u16 channels,
                                  u16 sample_count, i16 first)
{
    BreakVoiceFrame frame;
    u32 i;
    memset(&frame, 0, sizeof(frame));
    frame.sequence = sequence;
    frame.sample_rate = sample_rate;
    frame.channels = channels;
    frame.sample_count = sample_count;
    for (i = 0u; i < sample_count; ++i) frame.samples[i] = (i16)(first + (i16)i);
    return frame;
}

static BreakRuntimeError push_frame(BreakVoiceReceiver *receiver,
                                    BreakVoiceFrame frame)
{
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    BreakRuntimeError result = break_voice_encode(&frame, packet, sizeof(packet), &size);
    if (result != BREAK_RUNTIME_OK) return result;
    return break_voice_receiver_push(receiver, packet, size);
}

TEST(voice_encode_is_exact_little_endian_and_plays_stereo_pcm)
{
    BreakVoiceFrame frame = make_frame(0x01020304u, 1000u, 2u, 4u, 1u);
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 2u, 4u, 0u));
    BreakVoicePlayback playback;
    BreakRuntimeError result;
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    bool ready = false;
    frame.samples[0] = 1;
    frame.samples[1] = -2;
    frame.samples[2] = 300;
    frame.samples[3] = -400;
    ASSERT_NOT_NULL(receiver);
    ASSERT_EQ(break_voice_encode(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_EQ(size, 24u);
    ASSERT_TRUE(memcmp(packet, "BRV1", 4u) == 0);
    ASSERT_EQ(packet[4], 0x04u);
    ASSERT_EQ(packet[5], 0x03u);
    ASSERT_EQ(packet[6], 0x02u);
    ASSERT_EQ(packet[7], 0x01u);
    ASSERT_EQ(packet[8], 0xe8u);
    ASSERT_EQ(packet[9], 0x03u);
    ASSERT_EQ(packet[10], 0x00u);
    ASSERT_EQ(packet[11], 0x00u);
    ASSERT_EQ(packet[12], 0x02u);
    ASSERT_EQ(packet[13], 0x00u);
    ASSERT_EQ(packet[14], 0x04u);
    ASSERT_EQ(packet[15], 0x00u);
    ASSERT_EQ(packet[16], 0x01u);
    ASSERT_EQ(packet[17], 0x00u);
    ASSERT_EQ(packet[18], 0xfeu);
    ASSERT_EQ(packet[19], 0xffu);
    ASSERT_EQ(packet[20], 0x2cu);
    ASSERT_EQ(packet[21], 0x01u);
    ASSERT_EQ(packet[22], 0x70u);
    ASSERT_EQ(packet[23], 0xfeu);
    ASSERT_EQ(break_voice_receiver_push(receiver, packet, size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 1u, 0u), BREAK_RUNTIME_OK);
    memset(&playback, 0, sizeof(playback));
    result = break_voice_receiver_pop(receiver, 0u, &playback, &ready);
    ASSERT_EQ(result, BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_FALSE(playback.concealed);
    ASSERT_EQ(playback.sequence, frame.sequence);
    ASSERT_EQ(playback.sample_count, 4u);
    ASSERT_EQ(playback.samples[0], 1);
    ASSERT_EQ(playback.samples[1], -2);
    ASSERT_EQ(playback.samples[2], 300);
    ASSERT_EQ(playback.samples[3], -400);
    break_voice_receiver_destroy(receiver);
}

TEST(voice_rejects_bad_stream_and_trailing_bytes_without_playback)
{
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 1u, 2u, 0u));
    BreakVoiceStreamConfig invalid = voice_config(2000u, 1u, 1u, 0u);
    BreakVoiceReceiver *invalid_receiver = (BreakVoiceReceiver *)(uintptr_t)1u;
    BreakVoicePlayback playback;
    BreakVoiceReceiverStats stats;
    BreakVoiceFrame frame = make_frame(1u, 1000u, 1u, 2u, 10u);
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    u32 unchanged = 77u;
    bool ready = true;
    ASSERT_EQ(break_voice_receiver_create(NULL, &invalid, &invalid_receiver),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(invalid_receiver, NULL);
    frame.sample_count = 0u;
    ASSERT_EQ(break_voice_encode(&frame, packet, sizeof(packet), &unchanged),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(unchanged, 77u);
    frame = make_frame(1u, 8000u, 1u, 2u, 10u);
    ASSERT_EQ(break_voice_encode(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_push(receiver, packet, size + 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 1u, 0u), BREAK_RUNTIME_OK);
    memset(&playback, 0x5a, sizeof(playback));
    ASSERT_EQ(break_voice_receiver_pop(receiver, 0u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ready);
    ASSERT_EQ(break_voice_receiver_stats(receiver, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.invalid, 1u);
    ASSERT_EQ(stats.accepted, 0u);
    break_voice_receiver_destroy(receiver);
}

TEST(voice_jitter_delays_and_reorders_frames)
{
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 1u, 10u, 20u));
    BreakVoicePlayback playback;
    bool ready = false;
    ASSERT_NOT_NULL(receiver);
    ASSERT_EQ(push_frame(receiver, make_frame(12u, 1000u, 1u, 10u, 1200)), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_frame(receiver, make_frame(10u, 1000u, 1u, 10u, 1000)), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_frame(receiver, make_frame(11u, 1000u, 1u, 10u, 1100)), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 3u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 19u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ready);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 20u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(playback.sequence, 10u);
    ASSERT_EQ(playback.samples[0], 1000);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 30u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_EQ(playback.sequence, 11u);
    ASSERT_EQ(playback.samples[0], 1100);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 40u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_EQ(playback.sequence, 12u);
    ASSERT_EQ(playback.samples[0], 1200);
    break_voice_receiver_destroy(receiver);
}

TEST(voice_missing_sequence_emits_zero_concealment_and_rejects_late_copy)
{
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 1u, 10u, 20u));
    BreakVoiceReceiverStats stats;
    BreakVoicePlayback playback;
    bool ready = false;
    u32 i;
    ASSERT_EQ(push_frame(receiver, make_frame(10u, 1000u, 1u, 10u, 1000)), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_frame(receiver, make_frame(12u, 1000u, 1u, 10u, 1200)), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 2u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 20u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_EQ(playback.sequence, 10u);
    ASSERT_FALSE(playback.concealed);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 30u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_TRUE(playback.concealed);
    ASSERT_EQ(playback.sequence, 11u);
    ASSERT_EQ(playback.sample_count, 10u);
    for (i = 0u; i < 10u; ++i) ASSERT_EQ(playback.samples[i], 0);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 40u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_FALSE(playback.concealed);
    ASSERT_EQ(playback.sequence, 12u);
    ASSERT_EQ(playback.samples[0], 1200);
    ASSERT_EQ(push_frame(receiver, make_frame(11u, 1000u, 1u, 10u, 1100)), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 1u, 41u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_stats(receiver, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.stale, 1u);
    ASSERT_EQ(stats.played, 2u);
    ASSERT_EQ(stats.concealed, 1u);
    break_voice_receiver_destroy(receiver);
}

TEST(voice_duplicate_and_wraparound_sequences_follow_serial_order)
{
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 1u, 1u, 0u));
    BreakVoiceReceiverStats stats;
    BreakVoicePlayback playback;
    bool ready = false;
    ASSERT_EQ(push_frame(receiver, make_frame(UINT32_MAX, 1000u, 1u, 1u, 55)), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_frame(receiver, make_frame(0u, 1000u, 1u, 1u, 66)), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_frame(receiver, make_frame(UINT32_MAX, 1000u, 1u, 1u, 55)), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 3u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 0u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_EQ(playback.sequence, UINT32_MAX);
    ASSERT_EQ(playback.samples[0], 55);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 1u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_EQ(playback.sequence, 0u);
    ASSERT_EQ(playback.samples[0], 66);
    ASSERT_EQ(push_frame(receiver, make_frame(UINT32_MAX, 1000u, 1u, 1u, 55)), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 1u, 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_stats(receiver, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.duplicate, 1u);
    ASSERT_EQ(stats.stale, 1u);
    ASSERT_EQ(stats.accepted, 2u);
    break_voice_receiver_destroy(receiver);
}

TEST(voice_network_input_queue_is_bounded)
{
    BreakVoiceStreamConfig config = voice_config(1000u, 1u, 1u, 0u);
    BreakVoiceReceiver *receiver;
    config.queue_capacity = 1u;
    receiver = make_receiver(config);
    ASSERT_NOT_NULL(receiver);
    ASSERT_EQ(push_frame(receiver, make_frame(1u, 1000u, 1u, 1u, 1)), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_frame(receiver, make_frame(2u, 1000u, 1u, 1u, 2)), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 1u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_frame(receiver, make_frame(2u, 1000u, 1u, 1u, 2)), BREAK_RUNTIME_OK);
    break_voice_receiver_destroy(receiver);
}

TEST(voice_real_udp_loopback_preserves_pcm)
{
    NetSocket *receiver_socket = net_udp_create(0);
    NetSocket *sender_socket = net_udp_create(0);
    NetAddress destination;
    BreakVoiceReceiver *receiver = NULL;
    BreakVoiceStreamConfig config = voice_config(8000u, 1u, 16u, 0u);
    BreakVoiceFrame frame = make_frame(77u, 8000u, 1u, 16u, -123);
    BreakVoicePlayback playback = {0};
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    bool ready = false;
    ASSERT_NOT_NULL(receiver_socket);
    ASSERT_NOT_NULL(sender_socket);
    net_set_nonblocking(receiver_socket, true);
    net_set_nonblocking(sender_socket, true);
    ASSERT_TRUE(net_socket_get_local_address(receiver_socket, &destination));
    if (strcmp(destination.host, "0.0.0.0") == 0) strcpy(destination.host, "127.0.0.1");
    ASSERT_EQ(break_voice_receiver_create(receiver_socket, &config, &receiver), BREAK_RUNTIME_OK);
    frame.samples[1] = 456;
    ASSERT_EQ(break_voice_encode(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_EQ(net_sendto(sender_socket, packet, size, &destination), (i32)size);
    {
        u32 attempts = 0u;
        while (!ready && attempts < 500u) {
            NetPollFd pfd = {receiver_socket, NET_POLL_READ, 0};
            ASSERT_TRUE(net_poll(&pfd, 1u, 10) >= 0);
            ASSERT_EQ(break_voice_receiver_receive_socket(receiver, 1u), BREAK_RUNTIME_OK);
            ASSERT_EQ(break_voice_receiver_pump(receiver, 1u, 0u), BREAK_RUNTIME_OK);
            ASSERT_EQ(break_voice_receiver_pop(receiver, 0u, &playback, &ready),
                      BREAK_RUNTIME_OK);
            attempts++;
        }
    }
    ASSERT_TRUE(ready);
    ASSERT_EQ(playback.sequence, 77u);
    ASSERT_EQ(playback.samples[0], -123);
    ASSERT_EQ(playback.samples[1], 456);
    break_voice_receiver_destroy(receiver);
    net_close(receiver_socket);
    net_close(sender_socket);
}

TEST(voice_network_subsystem_initializes)
{
    ASSERT_TRUE(net_init());
}

/* ---- BRV2: IMA ADPCM ---- */

/* Pushes one packet and pops it. `now` advances by a second per call, well
 * past any frame's playout time, so consecutive frames are each ready. */
static bool play_one(BreakVoiceReceiver *receiver, const u8 *packet, u32 size,
                     BreakVoicePlayback *playback)
{
    static u64 now = 0u;
    bool ready = false;
    now += 1000u;
    if (break_voice_receiver_push(receiver, packet, size) != BREAK_RUNTIME_OK) return false;
    if (break_voice_receiver_pump(receiver, 1u, now) != BREAK_RUNTIME_OK) return false;
    memset(playback, 0, sizeof(*playback));
    if (break_voice_receiver_pop(receiver, now, playback, &ready) != BREAK_RUNTIME_OK) {
        return false;
    }
    return ready;
}

/* Values from a reference model of the standard IMA ADPCM step and index
 * tables (docs/superpowers/plans/2026-11-16-voice-adpcm.md): the first
 * sample is the start predictor, the start step index is the smallest
 * table step not below the first difference. */
TEST(adpcm_layout_and_known_code_sequence)
{
    BreakVoiceFrame frame = make_frame(9u, 1000u, 1u, 6u, 0);
    BreakVoicePlayback playback;
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 1u, 6u, 0u));
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    const i16 input[6] = {100, 200, -300, 1000, 1000, -2000};
    const i16 decoded[6] = {100, 192, 11, 402, 1019, -214};
    ASSERT_NOT_NULL(receiver);
    memcpy(frame.samples, input, sizeof(input));
    ASSERT_EQ(break_voice_encode_adpcm(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_EQ(size, BREAK_VOICE_ADPCM_SIZE(1u, 6u));
    ASSERT_EQ(size, 16u + 4u + 3u);
    ASSERT_TRUE(memcmp(packet, "BRV2", 4u) == 0);
    ASSERT_EQ(packet[4], 9u);
    ASSERT_EQ(packet[14], 6u);
    /* start state: predictor 100, step index 28, reserved 0 */
    ASSERT_EQ(packet[16], 100u);
    ASSERT_EQ(packet[17], 0u);
    ASSERT_EQ(packet[18], 28u);
    ASSERT_EQ(packet[19], 0u);
    /* codes 3, 15, 7, 5, 15 for samples 1..5, low nibble first */
    ASSERT_EQ(packet[20], 0xf3u);
    ASSERT_EQ(packet[21], 0x57u);
    ASSERT_EQ(packet[22], 0x0fu);
    ASSERT_TRUE(play_one(receiver, packet, size, &playback));
    ASSERT_EQ(playback.sequence, 9u);
    ASSERT_EQ(playback.sample_count, 6u);
    for (u32 i = 0; i < 6u; ++i) ASSERT_EQ(playback.samples[i], decoded[i]);
    break_voice_receiver_destroy(receiver);
}

/* Encodes, plays and compares one mono frame against reference-model
 * codes and decoded samples, computed by a reference model of the standard
 * IMA tables (see the plan file). */
static void check_adpcm_vector(u32 sequence, const i16 *input, u16 count, u8 start_index,
                               const u8 *code_bytes, u32 code_byte_count,
                               const i16 *decoded)
{
    BreakVoiceFrame frame = make_frame(sequence, 1000u, 1u, count, 0);
    BreakVoicePlayback playback;
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 1u, count, 0u));
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    ASSERT_NOT_NULL(receiver);
    memcpy(frame.samples, input, (usize)count * sizeof(i16));
    ASSERT_EQ(break_voice_encode_adpcm(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_EQ(size, 16u + 4u + code_byte_count);
    ASSERT_EQ(packet[18], start_index);
    ASSERT_EQ(memcmp(packet + 20u, code_bytes, code_byte_count), 0);
    ASSERT_TRUE(play_one(receiver, packet, size, &playback));
    for (u32 i = 0; i < count; ++i) ASSERT_EQ(playback.samples[i], decoded[i]);
    break_voice_receiver_destroy(receiver);
}

/* Each encoder comparison sits exactly on its boundary once: the first
 * difference equals a table step (start index 0), then differences of
 * exactly step, step/2, step/4 and -1. A negative first difference picks
 * its start index by magnitude. A large negative jump drives the index up
 * through codes with the sign bit set. */
TEST(adpcm_encoder_boundaries_match_the_reference_model)
{
    {
        const i16 in[7] = {0, 7, 16, 22, 25, 25, 33};
        const u8 codes[3] = {0x44u, 0x12u, 0x48u};
        const i16 out[7] = {0, 7, 17, 23, 26, 25, 34};
        check_adpcm_vector(21u, in, 7u, 0u, codes, 3u, out);
    }
    {
        const i16 in[4] = {1000, -1000, -900, -800};
        const u8 codes[2] = {0x8bu, 0x00u};
        const i16 out[4] = {1000, -807, -1041, -828};
        check_adpcm_vector(22u, in, 4u, 59u, codes, 2u, out);
    }
    {
        const i16 in[5] = {0, 0, -20000, -20000, -20000};
        const u8 codes[2] = {0xf0u, 0xffu};
        const i16 out[5] = {0, 0, -11, -41, -104};
        check_adpcm_vector(23u, in, 5u, 0u, codes, 2u, out);
    }
}

static f64 snr_db(const i16 *ref, const i16 *got, u32 n)
{
    f64 signal = 0.0;
    f64 noise = 0.0;
    for (u32 i = 0; i < n; ++i) {
        f64 d = (f64)ref[i] - (f64)got[i];
        signal += (f64)ref[i] * (f64)ref[i];
        noise += d * d;
    }
    return noise == 0.0 ? 1e9 : 10.0 * log10(signal / noise);
}

TEST(adpcm_round_trip_quality_silence_and_full_scale)
{
    BreakVoiceFrame frame = make_frame(1u, 16000u, 1u, 320u, 0);
    BreakVoicePlayback playback;
    BreakVoiceReceiver *receiver = make_receiver(voice_config(16000u, 1u, 320u, 0u));
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    ASSERT_NOT_NULL(receiver);
    /* a 440 Hz sine at -6 dBFS: the reference model gives 36 dB */
    for (u32 t = 0; t < 320u; ++t) {
        frame.samples[t] = (i16)lround(16384.0 * sin(2.0 * 3.14159265358979323846 * 440.0 *
                                                     (f64)t / 16000.0));
    }
    ASSERT_EQ(break_voice_encode_adpcm(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    /* 4:1 against BRV1 apart from the header and state */
    ASSERT_EQ(size, 16u + 4u + 160u);
    ASSERT_TRUE(play_one(receiver, packet, size, &playback));
    ASSERT_TRUE(snr_db(frame.samples, playback.samples, 320u) > 30.0);
    /* silence stays exact silence */
    frame.sequence = 2u;
    memset(frame.samples, 0, sizeof(frame.samples));
    ASSERT_EQ(break_voice_encode_adpcm(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_TRUE(play_one(receiver, packet, size, &playback));
    for (u32 i = 0; i < 320u; ++i) ASSERT_EQ(playback.samples[i], 0);
    /* a full-scale square wave never wraps around */
    frame.sequence = 3u;
    for (u32 t = 0; t < 320u; ++t) frame.samples[t] = (t / 20u) % 2u ? INT16_MIN : INT16_MAX;
    ASSERT_EQ(break_voice_encode_adpcm(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_TRUE(play_one(receiver, packet, size, &playback));
    for (u32 t = 40u; t < 320u; ++t) {
        /* settled halves keep the sign of the input */
        u32 phase = t % 40u;
        if (phase < 10u || (phase >= 20u && phase < 30u)) continue;
        if (frame.samples[t] > 0) ASSERT_TRUE(playback.samples[t] > 16000);
        else ASSERT_TRUE(playback.samples[t] < -16000);
    }
    break_voice_receiver_destroy(receiver);
}

TEST(adpcm_stereo_keeps_channels_apart_and_odd_counts_pad)
{
    BreakVoiceFrame frame = make_frame(4u, 1000u, 2u, 6u, 0);
    BreakVoicePlayback playback;
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 2u, 6u, 0u));
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    ASSERT_NOT_NULL(receiver);
    /* left 100, 200, -300; right -50, -50, -50 */
    const i16 input[6] = {100, -50, 200, -50, -300, -50};
    memcpy(frame.samples, input, sizeof(input));
    ASSERT_EQ(break_voice_encode_adpcm(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_EQ(size, BREAK_VOICE_ADPCM_SIZE(2u, 6u));
    /* the first frame lives in the two state blocks: 4 codes, 2 bytes */
    ASSERT_EQ(size, 16u + 8u + 2u);
    /* left state: predictor 100; right state: predictor -50 */
    ASSERT_EQ(packet[16], 100u);
    ASSERT_EQ(packet[17], 0u);
    ASSERT_EQ(packet[20], 0xceu);
    ASSERT_EQ(packet[21], 0xffu);
    ASSERT_TRUE(play_one(receiver, packet, size, &playback));
    ASSERT_EQ(playback.samples[0], 100);
    ASSERT_EQ(playback.samples[1], -50);
    /* the right channel is constant and the encoder tracks it exactly */
    ASSERT_EQ(playback.samples[3], -50);
    ASSERT_EQ(playback.samples[5], -50);
    /* the left channel follows the reference model: 100, 192, 11 */
    ASSERT_EQ(playback.samples[2], 192);
    ASSERT_EQ(playback.samples[4], 11);
    break_voice_receiver_destroy(receiver);

    /* three codes for four samples: the last byte's high nibble is zero */
    {
        BreakVoiceFrame odd = make_frame(5u, 1000u, 1u, 4u, 0);
        u8 odd_packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
        u32 odd_size = 0u;
        odd.samples[0] = 0;
        odd.samples[1] = 100;
        odd.samples[2] = 200;
        odd.samples[3] = 300;
        ASSERT_EQ(break_voice_encode_adpcm(&odd, odd_packet, sizeof(odd_packet), &odd_size),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(odd_size, 16u + 4u + 2u);
        ASSERT_EQ(odd_packet[21] & 0xf0u, 0u);
    }
}

TEST(adpcm_rejects_bad_state_length_and_format)
{
    BreakVoiceFrame frame = make_frame(1u, 1000u, 1u, 6u, 0);
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 1u, 6u, 0u));
    BreakVoiceReceiverStats stats;
    BreakVoicePlayback playback;
    u8 good[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u8 bad[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    u32 unchanged = 7u;
    bool ready = true;
    ASSERT_NOT_NULL(receiver);
    for (u32 i = 0; i < 6u; ++i) frame.samples[i] = (i16)(i * 100u);
    ASSERT_EQ(break_voice_encode_adpcm(NULL, good, sizeof(good), &size), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_voice_encode_adpcm(&frame, NULL, sizeof(good), &size), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_voice_encode_adpcm(&frame, good, sizeof(good), NULL), BREAK_RUNTIME_INVALID);
    /* needs 16 + 4 + 3 = 23 bytes */
    ASSERT_EQ(break_voice_encode_adpcm(&frame, good, 22u, &unchanged), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(unchanged, 7u);
    frame.channels = 3u;
    ASSERT_EQ(break_voice_encode_adpcm(&frame, good, sizeof(good), &unchanged),
              BREAK_RUNTIME_INVALID);
    frame.channels = 1u;
    ASSERT_EQ(break_voice_encode_adpcm(&frame, good, sizeof(good), &size), BREAK_RUNTIME_OK);

    /* step index above 88 */
    memcpy(bad, good, size);
    bad[18] = 89u;
    ASSERT_EQ(break_voice_receiver_push(receiver, bad, size), BREAK_RUNTIME_OK);
    /* reserved byte set */
    memcpy(bad, good, size);
    bad[19] = 1u;
    ASSERT_EQ(break_voice_receiver_push(receiver, bad, size), BREAK_RUNTIME_OK);
    /* one byte short and one byte long */
    ASSERT_EQ(break_voice_receiver_push(receiver, good, size - 1u), BREAK_RUNTIME_OK);
    memcpy(bad, good, size);
    bad[size] = 0u;
    ASSERT_EQ(break_voice_receiver_push(receiver, bad, size + 1u), BREAK_RUNTIME_OK);
    /* a stereo header for a mono stream */
    memcpy(bad, good, size);
    bad[12] = 2u;
    ASSERT_EQ(break_voice_receiver_push(receiver, bad, size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 8u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 0u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ready);
    ASSERT_EQ(break_voice_receiver_stats(receiver, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.invalid, 5u);
    ASSERT_EQ(stats.accepted, 0u);
    /* step index 88 is the last valid one */
    memcpy(bad, good, size);
    bad[18] = 88u;
    ASSERT_EQ(break_voice_receiver_push(receiver, bad, size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 1u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_stats(receiver, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.accepted, 1u);
    break_voice_receiver_destroy(receiver);
}

TEST(adpcm_and_pcm_frames_mix_in_one_stream)
{
    BreakVoiceFrame frame = make_frame(1u, 1000u, 1u, 4u, 0);
    BreakVoiceReceiver *receiver = make_receiver(voice_config(1000u, 1u, 4u, 0u));
    BreakVoicePlayback playback;
    u8 packet[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    bool ready = false;
    ASSERT_NOT_NULL(receiver);
    for (u32 i = 0; i < 4u; ++i) frame.samples[i] = 1234;
    frame.sequence = 2u;
    ASSERT_EQ(break_voice_encode_adpcm(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_push(receiver, packet, size), BREAK_RUNTIME_OK);
    frame.sequence = 1u;
    for (u32 i = 0; i < 4u; ++i) frame.samples[i] = (i16)(-7 - (i16)i);
    ASSERT_EQ(break_voice_encode(&frame, packet, sizeof(packet), &size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_push(receiver, packet, size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pump(receiver, 2u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 0u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(playback.sequence, 1u);
    ASSERT_EQ(playback.samples[3], -10);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 100u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(playback.sequence, 2u);
    /* a constant ADPCM frame decodes exactly */
    for (u32 i = 0; i < 4u; ++i) ASSERT_EQ(playback.samples[i], 1234);
    break_voice_receiver_destroy(receiver);
}

/* The core_app voice peer drives the receiver with a sequence-based
 * virtual clock (10 ms per frame since the first one, delay 0). A frame the
 * sender skipped is concealed once and the frame after it still plays. */
TEST(voice_sequence_clock_conceals_a_skipped_frame_and_plays_the_next)
{
    BreakVoiceReceiver *receiver = make_receiver(voice_config(48000u, 1u, 480u, 0u));
    const u32 sequences[] = {7u, 8u, 10u, 11u};
    u32 played = 0u;
    u32 concealed = 0u;
    u32 i;
    ASSERT_NOT_NULL(receiver);
    for (i = 0u; i < 4u; ++i) {
        const u64 now = (u64)(sequences[i] - sequences[0]) * 10u;
        ASSERT_EQ(push_frame(receiver, make_frame(sequences[i], 48000u, 1u, 480u, 1)),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_voice_receiver_pump(receiver, 8u, now), BREAK_RUNTIME_OK);
        for (;;) {
            BreakVoicePlayback playback;
            bool ready = false;
            ASSERT_EQ(break_voice_receiver_pop(receiver, now, &playback, &ready),
                      BREAK_RUNTIME_OK);
            if (!ready) break;
            if (playback.concealed) {
                ASSERT_EQ(playback.sequence, 9u);
                concealed++;
            } else {
                played++;
            }
        }
    }
    ASSERT_EQ(played, 4u);
    ASSERT_EQ(concealed, 1u);
    break_voice_receiver_destroy(receiver);
}

TEST(voice_pop_at_max_time_flushes_buffered_frames_in_order)
{
    BreakVoiceReceiver *receiver = make_receiver(voice_config(48000u, 1u, 480u, 40u));
    BreakVoicePlayback playback;
    bool ready = false;
    u32 i;
    ASSERT_NOT_NULL(receiver);
    for (i = 0u; i < 3u; ++i) {
        ASSERT_EQ(push_frame(receiver, make_frame(5u + i, 48000u, 1u, 480u, 1)),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(break_voice_receiver_pump(receiver, 8u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_voice_receiver_pop(receiver, 0u, &playback, &ready), BREAK_RUNTIME_OK);
    ASSERT_FALSE(ready);
    for (i = 0u; i < 3u; ++i) {
        ASSERT_EQ(break_voice_receiver_pop(receiver, UINT64_MAX, &playback, &ready),
                  BREAK_RUNTIME_OK);
        ASSERT_TRUE(ready);
        ASSERT_FALSE(playback.concealed);
        ASSERT_EQ(playback.sequence, 5u + i);
    }
    ASSERT_EQ(break_voice_receiver_pop(receiver, UINT64_MAX, &playback, &ready),
              BREAK_RUNTIME_OK);
    ASSERT_FALSE(ready);
    break_voice_receiver_destroy(receiver);
}

TEST_MAIN_BEGIN()
    RUN_TEST(voice_network_subsystem_initializes);
    RUN_TEST(voice_encode_is_exact_little_endian_and_plays_stereo_pcm);
    RUN_TEST(voice_rejects_bad_stream_and_trailing_bytes_without_playback);
    RUN_TEST(voice_jitter_delays_and_reorders_frames);
    RUN_TEST(voice_missing_sequence_emits_zero_concealment_and_rejects_late_copy);
    RUN_TEST(voice_duplicate_and_wraparound_sequences_follow_serial_order);
    RUN_TEST(voice_network_input_queue_is_bounded);
    RUN_TEST(voice_real_udp_loopback_preserves_pcm);
    RUN_TEST(adpcm_layout_and_known_code_sequence);
    RUN_TEST(adpcm_encoder_boundaries_match_the_reference_model);
    RUN_TEST(adpcm_round_trip_quality_silence_and_full_scale);
    RUN_TEST(adpcm_stereo_keeps_channels_apart_and_odd_counts_pad);
    RUN_TEST(adpcm_rejects_bad_state_length_and_format);
    RUN_TEST(adpcm_and_pcm_frames_mix_in_one_stream);
    RUN_TEST(voice_sequence_clock_conceals_a_skipped_frame_and_plays_the_next);
    RUN_TEST(voice_pop_at_max_time_flushes_buffered_frames_in_order);
    net_shutdown();
TEST_MAIN_END()
