#include "test_framework.h"
#include <network/break_online_voice.h>

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
    BreakVoicePlayback playback;
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

TEST_MAIN_BEGIN()
    RUN_TEST(voice_network_subsystem_initializes);
    RUN_TEST(voice_encode_is_exact_little_endian_and_plays_stereo_pcm);
    RUN_TEST(voice_rejects_bad_stream_and_trailing_bytes_without_playback);
    RUN_TEST(voice_jitter_delays_and_reorders_frames);
    RUN_TEST(voice_missing_sequence_emits_zero_concealment_and_rejects_late_copy);
    RUN_TEST(voice_duplicate_and_wraparound_sequences_follow_serial_order);
    RUN_TEST(voice_network_input_queue_is_bounded);
    RUN_TEST(voice_real_udp_loopback_preserves_pcm);
    net_shutdown();
TEST_MAIN_END()
