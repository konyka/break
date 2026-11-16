#pragma once

#include <network/network.h>
#include <runtime/runtime_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_VOICE_MAX_SAMPLES 480u
#define BREAK_VOICE_WIRE_HEADER_SIZE 16u
#define BREAK_VOICE_MAX_DATAGRAM_SIZE \
    (BREAK_VOICE_WIRE_HEADER_SIZE + BREAK_VOICE_MAX_SAMPLES * 2u)
/* BRV2 (IMA ADPCM): the BRV1 header, then per channel a 4-byte start state
 * (the channel's first sample as predictor i16 le, step index u8 0..88,
 * reserved u8 0), then one 4-bit code for every later sample, two per
 * byte, low nibble first, interleaved by channel like the PCM. */
#define BREAK_VOICE_ADPCM_STATE_SIZE 4u
#define BREAK_VOICE_ADPCM_SIZE(channels, sample_count) \
    (BREAK_VOICE_WIRE_HEADER_SIZE + BREAK_VOICE_ADPCM_STATE_SIZE * (channels) + \
     ((sample_count) - (channels) + 1u) / 2u)

typedef struct BreakVoiceReceiver BreakVoiceReceiver;

typedef struct BreakVoiceFrame {
    u32 sequence;
    u32 sample_rate;
    u16 channels;
    u16 sample_count;
    i16 samples[BREAK_VOICE_MAX_SAMPLES];
} BreakVoiceFrame;

typedef struct BreakVoicePlayback {
    u32 sequence;
    u16 sample_count;
    bool concealed;
    i16 samples[BREAK_VOICE_MAX_SAMPLES];
} BreakVoicePlayback;

typedef struct BreakVoiceStreamConfig {
    u32 sample_rate;
    u16 channels;
    u16 sample_count;
    u32 jitter_delay_ms;
    u32 jitter_capacity;
    u32 queue_capacity;
} BreakVoiceStreamConfig;

typedef struct BreakVoiceReceiverStats {
    u64 accepted;
    u64 played;
    u64 concealed;
    u64 invalid;
    u64 duplicate;
    u64 stale;
    u64 overload;
} BreakVoiceReceiverStats;

BreakRuntimeError break_voice_encode(const BreakVoiceFrame *frame,
                                     u8 *out, u32 capacity, u32 *out_size);
/* The same frame as BRV2: 4-bit IMA ADPCM, about a quarter of the BRV1
 * size and lossy. Each frame carries its own start state, so frames
 * decode independently. The receiver accepts BRV1 and BRV2 frames of its
 * configured format interchangeably. */
BreakRuntimeError break_voice_encode_adpcm(const BreakVoiceFrame *frame,
                                           u8 *out, u32 capacity, u32 *out_size);
BreakRuntimeError break_voice_receiver_create(
    NetSocket *socket, const BreakVoiceStreamConfig *config,
    BreakVoiceReceiver **out);
void break_voice_receiver_destroy(BreakVoiceReceiver *receiver);
BreakRuntimeError break_voice_receiver_push(BreakVoiceReceiver *receiver,
                                            const void *data, u32 size);
BreakRuntimeError break_voice_receiver_receive_socket(BreakVoiceReceiver *receiver,
                                                      u32 max_datagrams);
BreakRuntimeError break_voice_receiver_pump(BreakVoiceReceiver *receiver,
                                            u32 max_frames, u64 now_ms);
BreakRuntimeError break_voice_receiver_pop(BreakVoiceReceiver *receiver,
                                           u64 now_ms, BreakVoicePlayback *out,
                                           bool *out_ready);
BreakRuntimeError break_voice_receiver_stats(BreakVoiceReceiver *receiver,
                                             BreakVoiceReceiverStats *out);

#ifdef __cplusplus
}
#endif
