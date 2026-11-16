#include <network/break_online_voice.h>

#include <network/break_online_inbox.h>
#include <core/platform_thread.h>

#include <stdlib.h>
#include <string.h>

#define BREAK_VOICE_MAX_SAMPLE_RATE 192000u
#define BREAK_VOICE_MAX_JITTER_FRAMES 64u

typedef struct VoiceSlot {
    bool used;
    BreakVoiceFrame frame;
} VoiceSlot;

struct BreakVoiceReceiver {
    PlatformThreadId owner;
    NetSocket *socket;
    BreakVoiceStreamConfig config;
    BreakOnlineInbox *inbox;
    VoiceSlot *slots;
    u32 jitter_capacity;
    u32 frame_duration_ms;
    u32 expected_sequence;
    bool have_expected;
    bool started;
    u64 playout_at;
    BreakVoiceReceiverStats stats;
};

static bool receiver_owner(const BreakVoiceReceiver *receiver)
{
    return receiver && platform_thread_id_equal(receiver->owner,
                                                 platform_thread_current_id());
}

static void put_u16(u8 *out, u16 value)
{
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void put_u32(u8 *out, u32 value)
{
    u32 i;
    for (i = 0u; i < 4u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static u16 get_u16(const u8 *in)
{
    return (u16)((u16)in[0] | ((u16)in[1] << 8u));
}

static u32 get_u32(const u8 *in)
{
    u32 value = 0u;
    u32 i;
    for (i = 0u; i < 4u; ++i) value |= (u32)in[i] << (i * 8u);
    return value;
}

static bool valid_format(u32 sample_rate, u16 channels, u16 sample_count)
{
    return sample_rate != 0u && sample_rate <= BREAK_VOICE_MAX_SAMPLE_RATE &&
           (channels == 1u || channels == 2u) && sample_count != 0u &&
           sample_count <= BREAK_VOICE_MAX_SAMPLES && sample_count % channels == 0u;
}

static bool voice_seq_before(u32 a, u32 b)
{
    return a != b && (u32)(b - a) <= UINT32_C(0x7fffffff);
}

static u64 add_duration(u64 time, u32 duration)
{
    return time > UINT64_MAX - duration ? UINT64_MAX : time + duration;
}

BreakRuntimeError break_voice_encode(const BreakVoiceFrame *frame,
                                     u8 *out, u32 capacity, u32 *out_size)
{
    u32 required;
    u32 i;
    if (!frame || !out || !out_size ||
        !valid_format(frame->sample_rate, frame->channels, frame->sample_count)) {
        return BREAK_RUNTIME_INVALID;
    }
    required = BREAK_VOICE_WIRE_HEADER_SIZE + (u32)frame->sample_count * 2u;
    if (capacity < required) return BREAK_RUNTIME_OVERLOAD;
    memcpy(out, "BRV1", 4u);
    put_u32(out + 4u, frame->sequence);
    put_u32(out + 8u, frame->sample_rate);
    put_u16(out + 12u, frame->channels);
    put_u16(out + 14u, frame->sample_count);
    for (i = 0u; i < frame->sample_count; ++i) {
        put_u16(out + BREAK_VOICE_WIRE_HEADER_SIZE + i * 2u,
                (u16)frame->samples[i]);
    }
    *out_size = required;
    return BREAK_RUNTIME_OK;
}

/* Standard IMA ADPCM step and index tables. */
static const i16 k_ima_step[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 130, 143, 157, 173, 190, 209, 230,
    253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658, 724, 796, 876, 963,
    1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499, 2749, 3024, 3327,
    3660, 4026, 4428, 4871, 5358, 5894, 6484, 7132, 7845, 8630, 9493, 10442,
    11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794,
    32767};
/* Index change by the code's magnitude bits; the sign bit does not matter
 * (the standard 16-entry table repeats these eight). */
static const i8 k_ima_index[8] = {-1, -1, -1, -1, 2, 4, 6, 8};
#define IMA_MAX_INDEX 88

/* Applies one 4-bit code to (predictor, index); returns the new sample. */
static i16 ima_step(i32 *predictor, i32 *index, u32 code)
{
    i32 step = k_ima_step[*index];
    i32 diff = step >> 3;
    if (code & 4u) diff += step;
    if (code & 2u) diff += step >> 1;
    if (code & 1u) diff += step >> 2;
    *predictor += (code & 8u) ? -diff : diff;
    if (*predictor > INT16_MAX) *predictor = INT16_MAX;
    if (*predictor < INT16_MIN) *predictor = INT16_MIN;
    *index += k_ima_index[code & 7u];
    if (*index < 0) *index = 0;
    if (*index > IMA_MAX_INDEX) *index = IMA_MAX_INDEX;
    return (i16)*predictor;
}

/* The code whose step lands closest below the target, per the standard
 * encoder. */
static u32 ima_code(i32 predictor, i32 index, i32 sample)
{
    i32 step = k_ima_step[index];
    i32 diff = sample - predictor;
    u32 code = 0u;
    if (diff < 0) {
        code = 8u;
        diff = -diff;
    }
    if (diff >= step) {
        code |= 4u;
        diff -= step;
    }
    if (diff >= step >> 1) {
        code |= 2u;
        diff -= step >> 1;
    }
    if (diff >= step >> 2) code |= 1u;
    return code;
}

/* Smallest step not below |difference|, so the first code can follow it. */
static i32 ima_start_index(i32 difference)
{
    i32 magnitude = difference < 0 ? -difference : difference;
    for (i32 i = 0; i <= IMA_MAX_INDEX; ++i) {
        if (k_ima_step[i] >= magnitude) return i;
    }
    return IMA_MAX_INDEX;
}

BreakRuntimeError break_voice_encode_adpcm(const BreakVoiceFrame *frame,
                                           u8 *out, u32 capacity, u32 *out_size)
{
    i32 predictor[2];
    i32 index[2];
    u32 required;
    u32 c;
    if (!frame || !out || !out_size ||
        !valid_format(frame->sample_rate, frame->channels, frame->sample_count)) {
        return BREAK_RUNTIME_INVALID;
    }
    required = BREAK_VOICE_ADPCM_SIZE((u32)frame->channels, (u32)frame->sample_count);
    if (capacity < required) return BREAK_RUNTIME_OVERLOAD;
    memset(out, 0, required);
    memcpy(out, "BRV2", 4u);
    put_u32(out + 4u, frame->sequence);
    put_u32(out + 8u, frame->sample_rate);
    put_u16(out + 12u, frame->channels);
    put_u16(out + 14u, frame->sample_count);
    for (c = 0u; c < frame->channels; ++c) {
        u8 *state = out + BREAK_VOICE_WIRE_HEADER_SIZE + c * BREAK_VOICE_ADPCM_STATE_SIZE;
        i32 first = frame->samples[c];
        i32 second = frame->sample_count > frame->channels
                         ? frame->samples[frame->channels + c] : first;
        predictor[c] = first;
        index[c] = ima_start_index(second - first);
        put_u16(state, (u16)(i16)first);
        state[2] = (u8)index[c];
        state[3] = 0u;
    }
    {
        u8 *codes = out + BREAK_VOICE_WIRE_HEADER_SIZE +
                    (u32)frame->channels * BREAK_VOICE_ADPCM_STATE_SIZE;
        u32 n = 0u;
        for (u32 k = frame->channels; k < frame->sample_count; ++k, ++n) {
            u32 ch = k % frame->channels;
            u32 code = ima_code(predictor[ch], index[ch], frame->samples[k]);
            (void)ima_step(&predictor[ch], &index[ch], code);
            codes[n / 2u] |= (u8)(code << ((n % 2u) * 4u));
        }
    }
    *out_size = required;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_voice_receiver_create(
    NetSocket *socket, const BreakVoiceStreamConfig *config,
    BreakVoiceReceiver **out)
{
    BreakVoiceReceiver *receiver;
    BreakRuntimeError result;
    u32 frames_per_second;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!config || !valid_format(config->sample_rate, config->channels,
                                 config->sample_count) ||
        !config->jitter_capacity ||
        config->jitter_capacity > BREAK_VOICE_MAX_JITTER_FRAMES ||
        config->jitter_delay_ms > 10000u) return BREAK_RUNTIME_INVALID;
    frames_per_second = (u32)(config->sample_count / config->channels) * 1000u;
    if (frames_per_second < config->sample_rate) return BREAK_RUNTIME_INVALID;
    receiver = (BreakVoiceReceiver *)calloc(1u, sizeof(*receiver));
    if (!receiver) return BREAK_RUNTIME_OOM;
    receiver->slots = (VoiceSlot *)calloc(config->jitter_capacity,
                                          sizeof(*receiver->slots));
    if (!receiver->slots) {
        free(receiver);
        return BREAK_RUNTIME_OOM;
    }
    result = break_online_inbox_create(config->queue_capacity, &receiver->inbox);
    if (result != BREAK_RUNTIME_OK) {
        free(receiver->slots);
        free(receiver);
        return result;
    }
    receiver->owner = platform_thread_current_id();
    receiver->socket = socket;
    receiver->config = *config;
    receiver->jitter_capacity = config->jitter_capacity;
    receiver->frame_duration_ms = frames_per_second / config->sample_rate;
    *out = receiver;
    return BREAK_RUNTIME_OK;
}

void break_voice_receiver_destroy(BreakVoiceReceiver *receiver)
{
    if (!receiver_owner(receiver)) return;
    break_online_inbox_destroy(receiver->inbox);
    free(receiver->slots);
    free(receiver);
}

BreakRuntimeError break_voice_receiver_push(BreakVoiceReceiver *receiver,
                                            const void *data, u32 size)
{
    NetAddress source;
    if (!receiver) return BREAK_RUNTIME_INVALID;
    memset(&source, 0, sizeof(source));
    return break_online_inbox_push(receiver->inbox, &source, data, size);
}

BreakRuntimeError break_voice_receiver_receive_socket(BreakVoiceReceiver *receiver,
                                                      u32 max_datagrams)
{
    u32 i;
    if (!receiver || !receiver->socket || !max_datagrams) return BREAK_RUNTIME_INVALID;
    for (i = 0u; i < max_datagrams; ++i) {
        u8 bytes[BREAK_VOICE_MAX_DATAGRAM_SIZE + 1u];
        NetAddress source;
        i32 size = net_recvfrom(receiver->socket, bytes, sizeof(bytes), &source);
        if (size == NET_WOULD_BLOCK) return BREAK_RUNTIME_OK;
        if (size <= 0) return BREAK_RUNTIME_FAILED;
        if ((u32)size > BREAK_VOICE_MAX_DATAGRAM_SIZE) return BREAK_RUNTIME_INVALID;
        {
            BreakRuntimeError result = break_online_inbox_push(
                receiver->inbox, &source, bytes, (u32)size);
            if (result != BREAK_RUNTIME_OK) return result;
        }
    }
    return BREAK_RUNTIME_OK;
}

/* BRV2 payload after the header; the format fields are already checked. */
static bool decode_adpcm(const BreakOnlineDatagram *datagram, BreakVoiceFrame *frame)
{
    i32 predictor[2];
    i32 index[2];
    const u8 *codes;
    u32 c;
    if (datagram->size != BREAK_VOICE_ADPCM_SIZE((u32)frame->channels,
                                                 (u32)frame->sample_count)) {
        return false;
    }
    for (c = 0u; c < frame->channels; ++c) {
        const u8 *state =
            datagram->bytes + BREAK_VOICE_WIRE_HEADER_SIZE + c * BREAK_VOICE_ADPCM_STATE_SIZE;
        u16 bits = get_u16(state);
        if (state[2] > IMA_MAX_INDEX || state[3] != 0u) return false;
        predictor[c] = bits <= INT16_MAX ? (i32)bits : (i32)bits - 65536;
        index[c] = state[2];
        frame->samples[c] = (i16)predictor[c];
    }
    codes = datagram->bytes + BREAK_VOICE_WIRE_HEADER_SIZE +
            (u32)frame->channels * BREAK_VOICE_ADPCM_STATE_SIZE;
    for (u32 k = frame->channels, n = 0u; k < frame->sample_count; ++k, ++n) {
        u32 ch = k % frame->channels;
        u32 code = (codes[n / 2u] >> ((n % 2u) * 4u)) & 0x0fu;
        frame->samples[k] = ima_step(&predictor[ch], &index[ch], code);
    }
    return true;
}

static bool decode_frame(const BreakVoiceReceiver *receiver,
                         const BreakOnlineDatagram *datagram,
                         BreakVoiceFrame *out)
{
    u32 expected_size;
    u32 i;
    bool adpcm;
    BreakVoiceFrame frame;
    if (datagram->size < BREAK_VOICE_WIRE_HEADER_SIZE) return false;
    adpcm = memcmp(datagram->bytes, "BRV2", 4u) == 0;
    if (!adpcm && memcmp(datagram->bytes, "BRV1", 4u) != 0) return false;
    memset(&frame, 0, sizeof(frame));
    frame.sequence = get_u32(datagram->bytes + 4u);
    frame.sample_rate = get_u32(datagram->bytes + 8u);
    frame.channels = get_u16(datagram->bytes + 12u);
    frame.sample_count = get_u16(datagram->bytes + 14u);
    if (frame.sample_rate != receiver->config.sample_rate ||
        frame.channels != receiver->config.channels ||
        frame.sample_count != receiver->config.sample_count) return false;
    if (adpcm) {
        if (!decode_adpcm(datagram, &frame)) return false;
        *out = frame;
        return true;
    }
    expected_size = BREAK_VOICE_WIRE_HEADER_SIZE + (u32)frame.sample_count * 2u;
    if (datagram->size != expected_size) return false;
    for (i = 0u; i < frame.sample_count; ++i) {
        u16 bits = get_u16(datagram->bytes + BREAK_VOICE_WIRE_HEADER_SIZE + i * 2u);
        frame.samples[i] = bits <= INT16_MAX
            ? (i16)bits : (i16)(-1 - (i32)(UINT16_MAX - bits));
    }
    *out = frame;
    return true;
}

static void accept_frame(BreakVoiceReceiver *receiver,
                         const BreakVoiceFrame *frame, u64 now_ms)
{
    u32 i;
    u32 free_slot = UINT32_MAX;
    if (receiver->have_expected && receiver->started &&
        voice_seq_before(frame->sequence, receiver->expected_sequence)) {
        receiver->stats.stale++;
        return;
    }
    for (i = 0u; i < receiver->jitter_capacity; ++i) {
        if (receiver->slots[i].used &&
            receiver->slots[i].frame.sequence == frame->sequence) {
            receiver->stats.duplicate++;
            return;
        }
        if (!receiver->slots[i].used && free_slot == UINT32_MAX) free_slot = i;
    }
    if (free_slot == UINT32_MAX) {
        receiver->stats.overload++;
        return;
    }
    if (!receiver->have_expected) {
        receiver->have_expected = true;
        receiver->expected_sequence = frame->sequence;
        receiver->playout_at = add_duration(now_ms, receiver->config.jitter_delay_ms);
    } else if (!receiver->started &&
               voice_seq_before(frame->sequence, receiver->expected_sequence)) {
        receiver->expected_sequence = frame->sequence;
    }
    receiver->slots[free_slot].used = true;
    receiver->slots[free_slot].frame = *frame;
    receiver->stats.accepted++;
}

BreakRuntimeError break_voice_receiver_pump(BreakVoiceReceiver *receiver,
                                            u32 max_frames, u64 now_ms)
{
    u32 processed = 0u;
    if (!receiver_owner(receiver)) return BREAK_RUNTIME_REJECTED;
    while (processed < max_frames) {
        BreakOnlineDatagram datagram;
        BreakVoiceFrame frame;
        bool ready = false;
        BreakRuntimeError result = break_online_inbox_poll(receiver->inbox,
                                                            &datagram, &ready);
        if (result != BREAK_RUNTIME_OK) return result;
        if (!ready) break;
        processed++;
        if (!decode_frame(receiver, &datagram, &frame)) {
            receiver->stats.invalid++;
            continue;
        }
        accept_frame(receiver, &frame, now_ms);
    }
    return BREAK_RUNTIME_OK;
}

static i32 find_sequence(const BreakVoiceReceiver *receiver, u32 sequence)
{
    u32 i;
    for (i = 0u; i < receiver->jitter_capacity; ++i) {
        if (receiver->slots[i].used &&
            receiver->slots[i].frame.sequence == sequence) return (i32)i;
    }
    return -1;
}

static bool has_later_sequence(const BreakVoiceReceiver *receiver)
{
    u32 i;
    for (i = 0u; i < receiver->jitter_capacity; ++i) {
        if (receiver->slots[i].used &&
            voice_seq_before(receiver->expected_sequence,
                             receiver->slots[i].frame.sequence)) return true;
    }
    return false;
}

BreakRuntimeError break_voice_receiver_pop(BreakVoiceReceiver *receiver,
                                           u64 now_ms, BreakVoicePlayback *out,
                                           bool *out_ready)
{
    BreakVoicePlayback playback;
    i32 slot;
    if (!receiver_owner(receiver)) return BREAK_RUNTIME_REJECTED;
    if (!out || !out_ready) return BREAK_RUNTIME_INVALID;
    *out_ready = false;
    if (!receiver->have_expected || now_ms < receiver->playout_at) {
        return BREAK_RUNTIME_OK;
    }
    memset(&playback, 0, sizeof(playback));
    playback.sequence = receiver->expected_sequence;
    playback.sample_count = receiver->config.sample_count;
    slot = find_sequence(receiver, receiver->expected_sequence);
    if (slot >= 0) {
        u32 i;
        const BreakVoiceFrame *frame = &receiver->slots[(u32)slot].frame;
        for (i = 0u; i < frame->sample_count; ++i) {
            playback.samples[i] = frame->samples[i];
        }
        receiver->slots[(u32)slot].used = false;
        receiver->stats.played++;
    } else {
        if (!has_later_sequence(receiver)) return BREAK_RUNTIME_OK;
        playback.concealed = true;
        receiver->stats.concealed++;
    }
    receiver->started = true;
    receiver->expected_sequence++;
    receiver->playout_at = add_duration(receiver->playout_at,
                                        receiver->frame_duration_ms);
    *out = playback;
    *out_ready = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_voice_receiver_stats(BreakVoiceReceiver *receiver,
                                             BreakVoiceReceiverStats *out)
{
    if (!receiver_owner(receiver)) return BREAK_RUNTIME_REJECTED;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = receiver->stats;
    return BREAK_RUNTIME_OK;
}
