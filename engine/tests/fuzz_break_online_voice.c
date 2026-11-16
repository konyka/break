/* Mutation fuzzer for the network voice receiver (BRV1 PCM and BRV2 IMA
 * ADPCM frames).
 *
 * Every iteration encodes a valid frame, mutates the bytes (byte writes,
 * bit flips, header boundary values, magic swaps, ADPCM step index and
 * reserved byte, truncation, one extra byte) and pushes it through the
 * receiver. The harness keeps its own model of the receiver:
 *
 *  - an independent wire decoder (its own PCM and IMA ADPCM code, with the
 *    standard 16-entry index table) decides whether the bytes are a valid
 *    frame for the receiver's format and what samples they carry;
 *  - a shadow jitter buffer predicts which counter (accepted, invalid,
 *    duplicate, stale, overload) the frame must bump;
 *  - playout is checked against the shadow: the sequence must be the
 *    expected one, played samples must equal the reference decode of the
 *    accepted datagram, and concealed frames must be silent.
 *
 * The receiver lives for 64 iterations before it is recreated with a new
 * format, so jitter buffer state builds up across many datagrams.
 *
 * Usage: fuzz_break_online_voice [iterations] [seed] */

#include <network/break_online_voice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0x5EEDFACEULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

typedef struct Format {
    u32 sample_rate;
    u16 channels;
    u16 sample_count;
} Format;

static const Format k_formats[] = {
    {8000u, 1u, 8u},     {8000u, 1u, 160u},   {8000u, 2u, 16u},
    {16000u, 1u, 320u},  {16000u, 2u, 320u},  {44100u, 1u, 441u},
    {48000u, 2u, 480u},  {48000u, 1u, 48u},
};
#define FORMAT_COUNT (sizeof(k_formats) / sizeof(k_formats[0]))

static const u32 k_boundary_u32[] = {
    0u, 1u, 2u, 7999u, 8000u, 16000u, 48000u, 192000u, 192001u,
    0x7FFFFFFFu, 0x80000000u, 0xFFFFFFFEu, 0xFFFFFFFFu,
    0x00010000u, 0x00020001u, 0x01E00002u, 0x01E00001u,
};

static const i16 k_ref_step[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 130, 143, 157, 173, 190, 209, 230,
    253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658, 724, 796, 876, 963,
    1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499, 2749, 3024, 3327,
    3660, 4026, 4428, 4871, 5358, 5894, 6484, 7132, 7845, 8630, 9493, 10442,
    11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794,
    32767};
static const int k_ref_index[16] = {-1, -1, -1, -1, 2, 4, 6, 8,
                                    -1, -1, -1, -1, 2, 4, 6, 8};

static unsigned rd16(const u8 *p) { return (unsigned)p[0] | ((unsigned)p[1] << 8); }
static u32 rd32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}
static int as_i16(unsigned bits) { return bits < 32768u ? (int)bits : (int)bits - 65536; }

/* Reference wire decoder. Returns 1 and fills seq/samples if the bytes are a
 * frame the receiver configured with `fmt` must accept as well-formed. */
static int ref_decode(const u8 *b, u32 len, const Format *fmt, u32 *seq, i16 *samples) {
    int adpcm;
    u32 n, c, k;
    if (len < 16u) return 0;
    if (memcmp(b, "BRV1", 4) == 0) adpcm = 0;
    else if (memcmp(b, "BRV2", 4) == 0) adpcm = 1;
    else return 0;
    if (rd32(b + 8) != fmt->sample_rate || rd16(b + 12) != fmt->channels ||
        rd16(b + 14) != fmt->sample_count) return 0;
    n = fmt->sample_count;
    c = fmt->channels;
    *seq = rd32(b + 4);
    if (!adpcm) {
        if (len != 16u + 2u * n) return 0;
        for (k = 0; k < n; k++) samples[k] = (i16)as_i16(rd16(b + 16u + 2u * k));
        return 1;
    }
    if (len != 16u + 4u * c + (n - c + 1u) / 2u) return 0;
    {
        int pred[2], idx[2];
        const u8 *codes = b + 16u + 4u * c;
        for (k = 0; k < c; k++) {
            const u8 *st = b + 16u + 4u * k;
            if (st[2] > 88u || st[3] != 0u) return 0;
            pred[k] = as_i16(rd16(st));
            idx[k] = st[2];
            samples[k] = (i16)pred[k];
        }
        for (k = c; k < n; k++) {
            u32 nib = k - c;
            u32 ch = k % c;
            unsigned code = (codes[nib / 2u] >> ((nib % 2u) * 4u)) & 0xFu;
            int step = k_ref_step[idx[ch]];
            int diff = step >> 3;
            if (code & 4u) diff += step;
            if (code & 2u) diff += step >> 1;
            if (code & 1u) diff += step >> 2;
            pred[ch] += (code & 8u) ? -diff : diff;
            if (pred[ch] > 32767) pred[ch] = 32767;
            if (pred[ch] < -32768) pred[ch] = -32768;
            idx[ch] += k_ref_index[code];
            if (idx[ch] < 0) idx[ch] = 0;
            if (idx[ch] > 88) idx[ch] = 88;
            samples[k] = (i16)pred[ch];
        }
    }
    return 1;
}
typedef struct ShadowSlot {
    int used;
    u32 seq;
    i16 samples[BREAK_VOICE_MAX_SAMPLES];
} ShadowSlot;

/* What the receiver's jitter buffer must hold, kept independently. */
typedef struct Shadow {
    Format fmt;
    u32 capacity;
    u32 delay_ms;
    u32 frame_ms;
    int have_expected;
    int started;
    u32 expected;
    u64 playout_at;
    ShadowSlot slots[64];
} Shadow;

static int seq_before(u32 a, u32 b) { return a != b && (u32)(b - a) <= 0x7FFFFFFFu; }

enum { OUT_ACCEPTED, OUT_INVALID, OUT_DUPLICATE, OUT_STALE, OUT_OVERLOAD };

static int shadow_accept(Shadow *s, u32 seq, const i16 *samples, u64 now) {
    u32 i, free_slot = 0xFFFFFFFFu;
    if (s->have_expected && s->started && seq_before(seq, s->expected)) return OUT_STALE;
    for (i = 0; i < s->capacity; i++) {
        if (s->slots[i].used && s->slots[i].seq == seq) return OUT_DUPLICATE;
        if (!s->slots[i].used && free_slot == 0xFFFFFFFFu) free_slot = i;
    }
    if (free_slot == 0xFFFFFFFFu) return OUT_OVERLOAD;
    if (!s->have_expected) {
        s->have_expected = 1;
        s->expected = seq;
        s->playout_at = now + s->delay_ms;
    } else if (!s->started && seq_before(seq, s->expected)) {
        s->expected = seq;
    }
    s->slots[free_slot].used = 1;
    s->slots[free_slot].seq = seq;
    memcpy(s->slots[free_slot].samples, samples,
           sizeof(i16) * s->fmt.sample_count);
    return OUT_ACCEPTED;
}

/* Returns 0 (nothing ready), 1 (played, slot index in *slot) or 2 (concealed). */
static int shadow_pop(Shadow *s, u64 now, u32 *seq, u32 *slot) {
    u32 i;
    int later = 0;
    if (!s->have_expected || now < s->playout_at) return 0;
    *seq = s->expected;
    for (i = 0; i < s->capacity; i++) {
        if (s->slots[i].used && s->slots[i].seq == s->expected) {
            *slot = i;
            s->started = 1;
            s->expected++;
            s->playout_at += s->frame_ms;
            return 1;
        }
        if (s->slots[i].used && seq_before(s->expected, s->slots[i].seq)) later = 1;
    }
    if (!later) return 0;
    s->started = 1;
    s->expected++;
    s->playout_at += s->frame_ms;
    return 2;
}

static int fail(unsigned it, const char *what) {
    fprintf(stderr, "INVARIANT VIOLATION iter %u: %s\n", it, what);
    return 3;
}

static i16 random_sample(void) {
    switch (rnd() % 6u) {
    case 0: return 32767;
    case 1: return -32768;
    case 2: return 0;
    case 3: return (i16)((int)(rnd() % 201u) - 100);
    default: return (i16)(rnd() & 0xFFFFu);
    }
}

static u32 build_wire(const Shadow *s, u32 seq, u8 *wire) {
    BreakVoiceFrame frame;
    u32 size = 0u, k;
    BreakRuntimeError r;
    memset(&frame, 0, sizeof(frame));
    frame.sequence = seq;
    frame.sample_rate = s->fmt.sample_rate;
    frame.channels = s->fmt.channels;
    frame.sample_count = s->fmt.sample_count;
    /* Sometimes a well-formed frame whose only fault is a different sample
     * count, with the length to match, so only the count check rejects it. */
    if (rnd() % 16u == 0u) {
        u16 c = s->fmt.channels;
        frame.sample_count = (u16)(s->fmt.sample_count + c <= BREAK_VOICE_MAX_SAMPLES
                                       ? s->fmt.sample_count + c : s->fmt.sample_count - c);
    }
    for (k = 0; k < frame.sample_count; k++) frame.samples[k] = random_sample();
    r = (rnd() % 2u) ? break_voice_encode_adpcm(&frame, wire, BREAK_VOICE_MAX_DATAGRAM_SIZE + 1u, &size)
                     : break_voice_encode(&frame, wire, BREAK_VOICE_MAX_DATAGRAM_SIZE + 1u, &size);
    return r == BREAK_RUNTIME_OK ? size : 0u;
}

static u32 mutate(u8 *b, u32 len) {
    unsigned m, nmut = 1u + rnd() % 4u;
    for (m = 0; m < nmut; m++) {
        switch (rnd() % 9u) {
        case 0: b[rnd() % len] = (u8)rnd(); break;
        case 1: b[rnd() % len] ^= (u8)(1u << (rnd() % 8u)); break;
        case 2: {
            u32 v = k_boundary_u32[rnd() % (sizeof(k_boundary_u32) / sizeof(k_boundary_u32[0]))];
            u32 off = 4u * (1u + rnd() % 3u);
            b[off] = (u8)v; b[off + 1] = (u8)(v >> 8);
            b[off + 2] = (u8)(v >> 16); b[off + 3] = (u8)(v >> 24);
            break;
        }
        case 3: b[3] = (u8)(b[3] == '1' ? '2' : (b[3] == '2' ? '1' : '3')); break;
        case 4: if (len > 18u) b[18] = (u8)(rnd() % 2u ? 89u : (rnd() % 2u ? 88u : 255u)); break;
        case 5: if (len > 19u) b[19] = 1u; break;
        case 6: if (len > 22u) b[22] = (u8)(rnd() % 2u ? 89u : 88u); break;
        case 7: return 1u + rnd() % len;
        default: if (len <= BREAK_VOICE_MAX_DATAGRAM_SIZE) { b[len] = (u8)rnd(); return len + 1u; } break;
        }
    }
    return len;
}

static int make_receiver(Shadow *s, BreakVoiceReceiver **out) {
    BreakVoiceStreamConfig config;
    memset(s, 0, sizeof(*s));
    s->fmt = k_formats[rnd() % FORMAT_COUNT];
    s->capacity = (rnd() % 8u == 0u) ? 64u : 1u + rnd() % 8u;
    s->delay_ms = rnd() % 4u == 0u ? 0u : rnd() % 100u;
    s->frame_ms = (u32)(s->fmt.sample_count / s->fmt.channels) * 1000u / s->fmt.sample_rate;
    memset(&config, 0, sizeof(config));
    config.sample_rate = s->fmt.sample_rate;
    config.channels = s->fmt.channels;
    config.sample_count = s->fmt.sample_count;
    config.jitter_delay_ms = s->delay_ms;
    config.jitter_capacity = s->capacity;
    config.queue_capacity = 4u;
    return break_voice_receiver_create(NULL, &config, out) == BREAK_RUNTIME_OK;
}

static u64 counter(const BreakVoiceReceiverStats *st, int which) {
    switch (which) {
    case OUT_ACCEPTED: return st->accepted;
    case OUT_INVALID: return st->invalid;
    case OUT_DUPLICATE: return st->duplicate;
    case OUT_STALE: return st->stale;
    default: return st->overload;
    }
}
static int check_pops(Shadow *s, BreakVoiceReceiver *rx, u64 now, unsigned it,
                      unsigned *played, unsigned *concealed) {
    unsigned p;
    for (p = 0; p < 3u; p++) {
        BreakVoicePlayback out;
        bool ready = true;
        u32 seq = 0u, slot = 0u, k;
        int expect = shadow_pop(s, now, &seq, &slot);
        if (break_voice_receiver_pop(rx, now, &out, &ready) != BREAK_RUNTIME_OK)
            return fail(it, "pop failed");
        if (ready != (expect != 0)) return fail(it, "pop readiness differs from model");
        if (!ready) return 0;
        if (out.sequence != seq) return fail(it, "playout sequence differs from model");
        if (out.sample_count != s->fmt.sample_count) return fail(it, "playout sample count");
        if (out.concealed != (expect == 2)) return fail(it, "concealment differs from model");
        for (k = 0; k < s->fmt.sample_count; k++) {
            i16 want = expect == 1 ? s->slots[slot].samples[k] : (i16)0;
            if (out.samples[k] != want) return fail(it, "playout samples differ from reference decode");
        }
        if (expect == 1) {
            s->slots[slot].used = 0;
            (*played)++;
        } else {
            (*concealed)++;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    unsigned iters = argc > 1 ? (unsigned)atoi(argv[1]) : 20000u;
    unsigned it, played = 0u, concealed = 0u, invalid = 0u, accepted = 0u;
    unsigned played_seen = 0u, concealed_seen = 0u;
    static u8 wire[BREAK_VOICE_MAX_DATAGRAM_SIZE + 2u];
    static i16 ref[BREAK_VOICE_MAX_SAMPLES];
    static Shadow shadow;
    BreakVoiceReceiver *rx = NULL;
    u32 base = 0u;
    u64 now = 0u;
    if (argc > 2) rng_state = (unsigned long long)atoi(argv[2]);

    for (it = 0; it < iters; it++) {
        BreakVoiceReceiverStats before, after;
        u32 len, seq = 0u;
        int valid, expect, w;
        u64 grown = 0u;
        if (it % 64u == 0u) {
            if (rx) {
                BreakVoiceReceiverStats st;
                break_voice_receiver_stats(rx, &st);
                played_seen += (unsigned)st.played;
                concealed_seen += (unsigned)st.concealed;
                break_voice_receiver_destroy(rx);
                rx = NULL;
            }
            if (!make_receiver(&shadow, &rx)) return fail(it, "receiver_create rejected a valid config");
            base = rnd() % 4u == 0u ? 0xFFFFFFF0u : rnd();
            now = rnd() % 1000u;
        }
        now += rnd() % (2u * shadow.frame_ms + 2u);
        len = build_wire(&shadow, base + (it % 64u) + rnd() % 5u - 2u, wire);
        if (!len) return fail(it, "encoder rejected a valid frame");
        if (rnd() % 4u != 0u) len = mutate(wire, len);
        valid = ref_decode(wire, len, &shadow.fmt, &seq, ref);

        if (break_voice_receiver_stats(rx, &before) != BREAK_RUNTIME_OK) return fail(it, "stats");
        if (break_voice_receiver_push(rx, wire, len) != BREAK_RUNTIME_OK) return fail(it, "push rejected");
        if (break_voice_receiver_pump(rx, 1u, now) != BREAK_RUNTIME_OK) return fail(it, "pump failed");
        if (break_voice_receiver_stats(rx, &after) != BREAK_RUNTIME_OK) return fail(it, "stats");

        expect = valid ? shadow_accept(&shadow, seq, ref, now) : OUT_INVALID;
        for (w = OUT_ACCEPTED; w <= OUT_OVERLOAD; w++) grown += counter(&after, w) - counter(&before, w);
        if (grown != 1u) return fail(it, "one datagram must move exactly one counter");
        if (counter(&after, expect) != counter(&before, expect) + 1u) {
            fprintf(stderr, "iter %u: valid=%d expected outcome %d\n", it, valid, expect);
            return fail(it, "receiver outcome differs from model");
        }
        if (expect == OUT_INVALID) invalid++;
        if (expect == OUT_ACCEPTED) accepted++;
        if (check_pops(&shadow, rx, now, it, &played, &concealed)) return 3;
    }
    if (rx) {
        BreakVoiceReceiverStats st;
        break_voice_receiver_stats(rx, &st);
        played_seen += (unsigned)st.played;
        concealed_seen += (unsigned)st.concealed;
        break_voice_receiver_destroy(rx);
    }
    if (played_seen != played || concealed_seen != concealed)
        return fail(iters, "played/concealed counters differ from model");
    printf("fuzz done: %u iters, accepted %u, invalid %u, played %u, concealed %u\n",
           iters, accepted, invalid, played, concealed);
    if (iters >= 1000u && (accepted == 0u || invalid == 0u || played == 0u || concealed == 0u))
        return fail(iters, "run did not reach every outcome");
    return 0;
}
