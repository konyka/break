/* break_prediction wire messages and the server-side input inbox: exact
 * encodings, strict decoders, exactly-once in-order application, and an
 * end-to-end lossy loop between a predicting client and a server. */
#include "test_framework.h"

#include <network/break_prediction_wire.h>

#include <stdlib.h>
#include <string.h>

typedef struct {
    i32 pos;
    i32 vel;
} Body;

typedef struct {
    i32 accel;
} Push;

static bool body_step(void *user, const void *state, const void *input, void *out_state) {
    const i32 *drag = (const i32 *)user;
    Body s, next;
    Push in;
    memcpy(&s, state, sizeof s);
    memcpy(&in, input, sizeof in);
    next.vel = s.vel + in.accel - (drag ? *drag : 0);
    next.pos = s.pos + next.vel;
    memcpy(out_state, &next, sizeof next);
    return true;
}

static BreakPrediction *make(u32 capacity) {
    static const Body start = {0, 0};
    BreakPredictionConfig cfg;
    BreakPrediction *p = NULL;
    memset(&cfg, 0, sizeof cfg);
    cfg.state_size = (u32)sizeof(Body);
    cfg.input_size = (u32)sizeof(Push);
    cfg.capacity = capacity;
    cfg.step = body_step;
    cfg.initial_tick = 0u;
    cfg.initial_state = &start;
    return break_prediction_create(&cfg, &p) == BREAK_PREDICTION_OK ? p : NULL;
}

static void push_inputs(BreakPrediction *p, u64 first, const i32 *accels, u32 n) {
    for (u32 i = 0u; i < n; ++i) {
        Push in = {accels[i]};
        (void)break_prediction_apply_input(p, first + i, &in);
    }
}

TEST(an_input_batch_has_the_documented_layout) {
    BreakPrediction *p = make(8u);
    const i32 accels[] = {1, -2, 3};
    u8 buf[64];
    usize len = 0u;
    ASSERT_NOT_NULL(p);
    push_inputs(p, 1u, accels, 3u);
    ASSERT_EQ(break_prediction_wire_encode_inputs(p, buf, sizeof buf, &len), BREAK_PREDICTION_OK);
    ASSERT_EQ(len, (usize)BREAK_PREDICTION_WIRE_INPUT_SIZE(3u, 4u));
    ASSERT_EQ(memcmp(buf, "BRPI", 4u), 0);
    ASSERT_EQ(buf[4], 1u);
    ASSERT_EQ(buf[5], 3u);
    ASSERT_EQ(buf[6], 4u);
    ASSERT_EQ(buf[7], 0u);
    ASSERT_EQ(buf[8], 1u); /* first tick 1, little-endian u64 */
    for (u32 k = 9u; k < 16u; ++k) ASSERT_EQ(buf[k], 0u);
    {
        Push second;
        memcpy(&second, buf + 16u + 4u, sizeof second);
        ASSERT_EQ(second.accel, -2);
    }
    break_prediction_destroy(p);
}

TEST(a_batch_round_trips_and_sends_the_oldest_when_many_are_pending) {
    BreakPrediction *p = make(64u);
    i32 accels[40];
    u8 buf[BREAK_PREDICTION_WIRE_INPUT_SIZE(BREAK_PREDICTION_WIRE_MAX_BATCH, 4u)];
    usize len = 0u;
    BreakPredictionInputBatch b;
    ASSERT_NOT_NULL(p);
    for (u32 i = 0u; i < 40u; ++i) accels[i] = (i32)i;
    push_inputs(p, 1u, accels, 40u);
    ASSERT_EQ(break_prediction_wire_encode_inputs(p, buf, sizeof buf, &len), BREAK_PREDICTION_OK);
    ASSERT_EQ(len, sizeof buf);
    ASSERT_EQ(break_prediction_wire_decode_inputs(buf, len, 4u, &b), BREAK_PREDICTION_OK);
    ASSERT_EQ(b.first_tick, 1u);
    ASSERT_EQ(b.count, BREAK_PREDICTION_WIRE_MAX_BATCH);
    ASSERT_EQ(b.input_size, 4u);
    for (u32 i = 0u; i < b.count; ++i) {
        Push in;
        memcpy(&in, b.inputs + i * 4u, sizeof in);
        ASSERT_EQ(in.accel, (i32)i);
    }
    break_prediction_destroy(p);
}

static bool big_step(void *user, const void *state, const void *input, void *out_state) {
    (void)user;
    (void)input;
    memcpy(out_state, state, 8u);
    return true;
}

/* Large inputs: a batch stays within one 64 KiB envelope payload, so it holds
 * fewer than BREAK_PREDICTION_WIRE_MAX_BATCH inputs, and the decoder refuses
 * a longer batch even when its count and length agree. */
TEST(a_batch_of_large_inputs_fits_one_envelope_payload) {
    static u8 input[BREAK_PREDICTION_MAX_INPUT_BYTES];
    static u8 buf[BREAK_PREDICTION_WIRE_INPUT_SIZE(16u, BREAK_PREDICTION_MAX_INPUT_BYTES)];
    static const u8 start[8] = {0};
    BreakPredictionConfig cfg;
    BreakPrediction *p = NULL;
    BreakPredictionInputBatch b;
    usize len = 0u;
    memset(&cfg, 0, sizeof cfg);
    cfg.state_size = 8u;
    cfg.input_size = BREAK_PREDICTION_MAX_INPUT_BYTES;
    cfg.capacity = 40u;
    cfg.step = big_step;
    cfg.initial_state = start;
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_OK);
    for (u32 i = 0u; i < 20u; ++i) {
        memset(input, (int)i, sizeof input);
        ASSERT_EQ(break_prediction_apply_input(p, 1u + i, input), BREAK_PREDICTION_OK);
    }
    ASSERT_EQ(break_prediction_wire_encode_inputs(p, buf, sizeof buf, &len), BREAK_PREDICTION_OK);
    ASSERT_EQ(len, (usize)BREAK_PREDICTION_WIRE_INPUT_SIZE(15u, BREAK_PREDICTION_MAX_INPUT_BYTES));
    ASSERT_TRUE(len <= BREAK_PREDICTION_WIRE_MAX_INPUT_MESSAGE);
    ASSERT_EQ(buf[5], 15u);
    ASSERT_EQ(break_prediction_wire_decode_inputs(buf, len, BREAK_PREDICTION_MAX_INPUT_BYTES, &b),
              BREAK_PREDICTION_OK);
    ASSERT_EQ(b.inputs[14u * BREAK_PREDICTION_MAX_INPUT_BYTES], 14u);
    /* 16 such inputs: count and length agree, but the batch is over 64 KiB */
    memset(buf + len, 15, BREAK_PREDICTION_MAX_INPUT_BYTES);
    buf[5] = 16u;
    ASSERT_EQ(break_prediction_wire_decode_inputs(buf, sizeof buf, BREAK_PREDICTION_MAX_INPUT_BYTES,
                                                  &b),
              BREAK_PREDICTION_INVALID);
    ASSERT_TRUE(b.count == 0u && b.inputs == NULL);
    break_prediction_destroy(p);
}

TEST(encoding_reports_sizes_and_sends_nothing_without_pending_input) {
    BreakPrediction *p = make(8u);
    const i32 accels[] = {1, 1};
    u8 buf[64];
    usize len = 99u;
    ASSERT_NOT_NULL(p);
    ASSERT_EQ(break_prediction_wire_encode_inputs(p, buf, sizeof buf, &len), BREAK_PREDICTION_OK);
    ASSERT_EQ(len, 0u);
    push_inputs(p, 1u, accels, 2u);
    memset(buf, 0xEE, sizeof buf);
    ASSERT_EQ(break_prediction_wire_encode_inputs(p, buf, BREAK_PREDICTION_WIRE_INPUT_SIZE(2u, 4u) - 1u,
                                                  &len),
              BREAK_PREDICTION_FULL);
    ASSERT_EQ(buf[0], 0xEEu);
    ASSERT_EQ(break_prediction_wire_encode_inputs(p, buf, 10u, &len), BREAK_PREDICTION_FULL);
    ASSERT_EQ(len, (usize)BREAK_PREDICTION_WIRE_INPUT_SIZE(2u, 4u));
    ASSERT_EQ(buf[0], 0xEEu);
    ASSERT_EQ(break_prediction_wire_encode_inputs(NULL, buf, sizeof buf, &len),
              BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_wire_encode_inputs(p, buf, sizeof buf, NULL),
              BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_wire_encode_snapshot(5u, accels, 8u, buf, 27u, &len),
              BREAK_PREDICTION_FULL);
    ASSERT_EQ(len, 28u);
    ASSERT_EQ(break_prediction_wire_encode_snapshot(5u, NULL, 8u, buf, sizeof buf, &len),
              BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_wire_encode_snapshot(5u, accels, 0u, buf, sizeof buf, &len),
              BREAK_PREDICTION_INVALID);
    break_prediction_destroy(p);
}

TEST(a_snapshot_has_the_documented_layout_and_round_trips) {
    Body s = {0x01020304, -1};
    u8 buf[64];
    usize len = 0u;
    BreakPredictionSnapshot snap;
    ASSERT_EQ(break_prediction_wire_encode_snapshot(0x1122334455667788ull, &s, (u32)sizeof s, buf,
                                                    sizeof buf, &len),
              BREAK_PREDICTION_OK);
    ASSERT_EQ(len, (usize)BREAK_PREDICTION_WIRE_SNAPSHOT_SIZE(8u));
    ASSERT_EQ(memcmp(buf, "BRPS", 4u), 0);
    ASSERT_EQ(buf[4], 1u);
    ASSERT_EQ(buf[5], 0u);
    ASSERT_EQ(buf[6], 0u);
    ASSERT_EQ(buf[7], 0u);
    ASSERT_EQ(buf[8], 0x88u);
    ASSERT_EQ(buf[15], 0x11u);
    ASSERT_EQ(buf[16], 8u);
    ASSERT_EQ(buf[19], 0u);
    ASSERT_EQ(break_prediction_wire_decode_snapshot(buf, len, 8u, &snap), BREAK_PREDICTION_OK);
    ASSERT_EQ(snap.tick, 0x1122334455667788ull);
    ASSERT_EQ(snap.state_size, 8u);
    ASSERT_EQ(memcmp(snap.state, &s, sizeof s), 0);
    ASSERT_TRUE(snap.state == buf + 20u);
}

static bool batch_is_zero(const BreakPredictionInputBatch *b) {
    return b->first_tick == 0u && b->count == 0u && b->input_size == 0u && b->inputs == NULL;
}

TEST(malformed_input_batches_are_rejected) {
    BreakPrediction *p = make(8u);
    const i32 accels[] = {1, 2};
    u8 good[64], bad[80];
    usize len = 0u;
    BreakPredictionInputBatch b;
    ASSERT_NOT_NULL(p);
    push_inputs(p, 1u, accels, 2u);
    ASSERT_EQ(break_prediction_wire_encode_inputs(p, good, sizeof good, &len), BREAK_PREDICTION_OK);
#define REJECT(buf_, len_, size_)                                                              \
    do {                                                                                       \
        memset(&b, 0xAB, sizeof b);                                                            \
        ASSERT_EQ(break_prediction_wire_decode_inputs((buf_), (len_), (size_), &b),            \
                  BREAK_PREDICTION_INVALID);                                                   \
        ASSERT_TRUE(batch_is_zero(&b));                                                        \
    } while (0)
    for (usize cut = 0u; cut < len; ++cut) {
        u8 *heap = (u8 *)malloc(cut ? cut : 1u);
        ASSERT_NOT_NULL(heap);
        memcpy(heap, good, cut);
        REJECT(heap, cut, 4u);
        free(heap);
    }
    memcpy(bad, good, len);
    bad[len] = 0u;
    REJECT(bad, len + 1u, 4u); /* trailing byte */
    REJECT(good, len, 8u);     /* size other than the receiver's */
    memcpy(bad, good, len);
    bad[0] = 'X';
    REJECT(bad, len, 4u);
    memcpy(bad, good, len);
    bad[4] = 2u;
    REJECT(bad, len, 4u); /* version */
    memcpy(bad, good, len);
    bad[5] = 0u;
    REJECT(bad, 16u, 4u); /* count 0 */
    {
        /* one input over the batch limit, with a length that matches it */
        enum { k_over = BREAK_PREDICTION_WIRE_MAX_BATCH + 1u };
        u8 big[BREAK_PREDICTION_WIRE_INPUT_SIZE(k_over, 4u)];
        memset(big, 0, sizeof big);
        memcpy(big, good, 16u);
        big[5] = (u8)k_over;
        REJECT(big, sizeof big, 4u);
        big[5] = (u8)BREAK_PREDICTION_WIRE_MAX_BATCH;
        ASSERT_EQ(break_prediction_wire_decode_inputs(big, sizeof big - 4u, 4u, &b),
                  BREAK_PREDICTION_OK);
    }
    memcpy(bad, good, len);
    bad[6] = 2u; /* declared input size 2: 16 + 4 * 2 bytes would fit it too */
    REJECT(bad, len, 4u);
    memcpy(bad, good, len);
    memset(bad + 8u, 0xFF, 8u); /* first tick UINT64_MAX: tick + 1 overflows */
    REJECT(bad, len, 4u);
    memcpy(bad, good, len);
    memset(bad + 8u, 0x00, 8u); /* tick 0 is the initial confirmed tick, never an input */
    REJECT(bad, len, 4u);
    REJECT(NULL, len, 4u);
    REJECT(good, len, 0u);
    {
        /* a receiver configured past the input limit is refused even when the
         * buffer matches the declared size (u16 holds up to 65535) */
        u32 over = BREAK_PREDICTION_MAX_INPUT_BYTES + 1u;
        usize n = BREAK_PREDICTION_WIRE_INPUT_SIZE(1u, over);
        u8 *huge = (u8 *)calloc(1u, n);
        ASSERT_NOT_NULL(huge);
        memcpy(huge, good, 16u);
        huge[5] = 1u;
        huge[6] = (u8)over;
        huge[7] = (u8)(over >> 8);
        REJECT(huge, n, over);
        free(huge);
    }
    ASSERT_EQ(break_prediction_wire_decode_inputs(good, len, 4u, NULL), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_wire_decode_inputs(good, len, 4u, &b), BREAK_PREDICTION_OK);
#undef REJECT
    break_prediction_destroy(p);
}

TEST(malformed_snapshots_are_rejected) {
    Body s = {5, 6};
    u8 good[64], bad[64];
    usize len = 0u;
    BreakPredictionSnapshot snap;
    ASSERT_EQ(break_prediction_wire_encode_snapshot(9u, &s, (u32)sizeof s, good, sizeof good, &len),
              BREAK_PREDICTION_OK);
#define REJECT(buf_, len_, size_)                                                              \
    do {                                                                                       \
        memset(&snap, 0xAB, sizeof snap);                                                      \
        ASSERT_EQ(break_prediction_wire_decode_snapshot((buf_), (len_), (size_), &snap),       \
                  BREAK_PREDICTION_INVALID);                                                   \
        ASSERT_TRUE(snap.tick == 0u && snap.state_size == 0u && snap.state == NULL);           \
    } while (0)
    for (usize cut = 0u; cut < len; ++cut) {
        u8 *heap = (u8 *)malloc(cut ? cut : 1u);
        ASSERT_NOT_NULL(heap);
        memcpy(heap, good, cut);
        REJECT(heap, cut, 8u);
        free(heap);
    }
    memcpy(bad, good, len);
    bad[len] = 0u;
    REJECT(bad, len + 1u, 8u);
    REJECT(good, len, 4u);
    for (u32 k = 5u; k < 8u; ++k) {
        memcpy(bad, good, len);
        bad[k] = 1u; /* reserved */
        REJECT(bad, len, 8u);
    }
    memcpy(bad, good, len);
    bad[3] = 'I';
    REJECT(bad, len, 8u);
    memcpy(bad, good, len);
    bad[4] = 0u;
    REJECT(bad, len, 8u);
    memcpy(bad, good, len);
    bad[16] = 9u; /* declared size disagrees with the receiver */
    REJECT(bad, len, 8u);
    REJECT(NULL, len, 8u);
    {
        /* a receiver configured past the state limit is refused even when the
         * buffer matches the declared size */
        u32 over = BREAK_PREDICTION_MAX_STATE_BYTES + 1u;
        usize n = BREAK_PREDICTION_WIRE_SNAPSHOT_SIZE(over);
        u8 *huge = (u8 *)calloc(1u, n);
        ASSERT_NOT_NULL(huge);
        memcpy(huge, good, 16u);
        huge[16] = (u8)over;
        huge[17] = (u8)(over >> 8);
        REJECT(huge, n, over);
        free(huge);
    }
#undef REJECT
}

typedef struct {
    u64 ticks[64];
    i32 accels[64];
    u32 n;
    u32 refuse_at; /* 0: never */
} Applied;

static bool record_apply(void *user, u64 tick, const void *input) {
    Applied *a = (Applied *)user;
    Push in;
    if (a->refuse_at != 0u && a->n + 1u == a->refuse_at) return false;
    memcpy(&in, input, sizeof in);
    a->ticks[a->n] = tick;
    a->accels[a->n] = in.accel;
    a->n++;
    return true;
}

static BreakPredictionInputBatch batch_of(u64 first, const Push *inputs, u32 count) {
    BreakPredictionInputBatch b;
    b.first_tick = first;
    b.count = count;
    b.input_size = (u32)sizeof(Push);
    b.inputs = (const u8 *)inputs;
    return b;
}

TEST(the_inbox_applies_each_input_once_and_in_order) {
    BreakPredictionInbox box;
    Applied a;
    Push in[6] = {{10}, {11}, {12}, {13}, {14}, {15}};
    BreakPredictionInputBatch b;
    u32 got = 99u;
    memset(&a, 0, sizeof a);
    break_prediction_inbox_init(&box, 1u);
    ASSERT_EQ(break_prediction_inbox_last_tick(&box), 0u);
    b = batch_of(1u, in, 3u); /* ticks 1..3 */
    ASSERT_EQ(break_prediction_inbox_accept(&box, &b, record_apply, &a, &got), BREAK_PREDICTION_OK);
    ASSERT_EQ(got, 3u);
    b = batch_of(2u, in + 1, 4u); /* 2..5 overlaps: only 4 and 5 are new */
    ASSERT_EQ(break_prediction_inbox_accept(&box, &b, record_apply, &a, &got), BREAK_PREDICTION_OK);
    ASSERT_EQ(got, 2u);
    b = batch_of(1u, in, 2u); /* a stale duplicate */
    ASSERT_EQ(break_prediction_inbox_accept(&box, &b, record_apply, &a, &got), BREAK_PREDICTION_OK);
    ASSERT_EQ(got, 0u);
    ASSERT_EQ(a.n, 5u);
    for (u32 i = 0u; i < 5u; ++i) {
        ASSERT_EQ(a.ticks[i], 1u + i);
        ASSERT_EQ(a.accels[i], 10 + (i32)i);
    }
    ASSERT_EQ(break_prediction_inbox_last_tick(&box), 5u);
    ASSERT_EQ(box.applied, 5u);
    ASSERT_EQ(box.duplicates, 4u);
    ASSERT_EQ(box.gaps, 0u);
}

TEST(the_inbox_waits_at_a_gap_and_stops_where_apply_refuses) {
    BreakPredictionInbox box;
    Applied a;
    Push in[4] = {{1}, {2}, {3}, {4}};
    BreakPredictionInputBatch b;
    u32 got = 0u;
    memset(&a, 0, sizeof a);
    break_prediction_inbox_init(&box, 1u);
    b = batch_of(3u, in + 2, 2u); /* ticks 3..4 while 1..2 are missing */
    ASSERT_EQ(break_prediction_inbox_accept(&box, &b, record_apply, &a, &got), BREAK_PREDICTION_OK);
    ASSERT_EQ(got, 0u);
    ASSERT_EQ(box.gaps, 1u);
    b = batch_of(2u, in + 1, 3u); /* ticks 2..4: tick 1 alone is missing */
    ASSERT_EQ(break_prediction_inbox_accept(&box, &b, record_apply, &a, &got), BREAK_PREDICTION_OK);
    ASSERT_EQ(got, 0u);
    ASSERT_EQ(box.gaps, 2u);
    ASSERT_EQ(a.n, 0u);
    a.refuse_at = 3u;
    b = batch_of(1u, in, 4u);
    ASSERT_EQ(break_prediction_inbox_accept(&box, &b, record_apply, &a, &got),
              BREAK_PREDICTION_FAILED);
    ASSERT_EQ(got, 2u);
    ASSERT_EQ(break_prediction_inbox_last_tick(&box), 2u);
    a.refuse_at = 0u;
    ASSERT_EQ(break_prediction_inbox_accept(&box, &b, record_apply, &a, &got), BREAK_PREDICTION_OK);
    ASSERT_EQ(got, 2u);
    ASSERT_EQ(a.ticks[2], 3u);
    ASSERT_EQ(a.ticks[3], 4u);
    ASSERT_EQ(break_prediction_inbox_accept(NULL, &b, record_apply, &a, &got),
              BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_inbox_accept(&box, NULL, record_apply, &a, &got),
              BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_inbox_accept(&box, &b, NULL, &a, &got), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_inbox_accept(&box, &b, record_apply, &a, NULL),
              BREAK_PREDICTION_INVALID);
}

/* A predicting client and an authoritative server with drag the client does
 * not model, over a channel that drops, duplicates and reorders datagrams.
 * Every tick the client sends its pending inputs; every third tick the server
 * sends a snapshot. The server must apply every input exactly once in order,
 * and once the channel drains both sides agree byte for byte. */
typedef struct {
    Body state;
    i32 drag;
    u64 last_tick;
    u32 out_of_order;
} Server;

static bool server_apply(void *user, u64 tick, const void *input) {
    Server *srv = (Server *)user;
    Body next;
    if (tick != srv->last_tick + 1u) srv->out_of_order++;
    srv->last_tick = tick;
    (void)body_step(&srv->drag, &srv->state, input, &next);
    srv->state = next;
    return true;
}

TEST(a_lossy_loop_converges_to_the_server_state) {
    enum { k_ticks = 600, k_slots = 8 };
    typedef struct {
        u8 bytes[BREAK_PREDICTION_WIRE_INPUT_SIZE(BREAK_PREDICTION_WIRE_MAX_BATCH, 4u)];
        usize len;
        u32 deliver_at;
        u32 copies; /* deliveries left: 2 means it arrives twice */
    } Datagram;
    BreakPrediction *client = make(256u);
    BreakPredictionInbox box;
    Server srv;
    Datagram up[k_slots], down[k_slots];
    u32 rng = 777u;
    u64 mispredictions = 0u;
    ASSERT_NOT_NULL(client);
    memset(&srv, 0, sizeof srv);
    srv.drag = 1;
    memset(up, 0, sizeof up);
    memset(down, 0, sizeof down);
    break_prediction_inbox_init(&box, 1u);
    for (u32 now = 1u; now <= (u32)k_ticks + 300u; ++now) {
        if (now <= (u32)k_ticks) {
            Push in;
            rng = rng * 1103515245u + 12345u;
            in.accel = (i32)((rng >> 16) % 5u) - 2;
            ASSERT_EQ(break_prediction_apply_input(
                          client, break_prediction_predicted_tick(client) + 1u, &in),
                      BREAK_PREDICTION_OK);
        }
        rng = rng * 1103515245u + 12345u;
        if ((rng >> 16) % 10u >= 3u) { /* 30% of uplink datagrams are lost */
            Datagram *d = &up[now % k_slots];
            ASSERT_EQ(break_prediction_wire_encode_inputs(client, d->bytes, sizeof d->bytes,
                                                          &d->len),
                      BREAK_PREDICTION_OK);
            d->deliver_at = now + (rng >> 8) % 4u;
            d->copies = (rng >> 4) % 5u == 0u ? 2u : 1u;
        }
        for (u32 k = 0u; k < (u32)k_slots; ++k) {
            Datagram *d = &up[(now + k) % k_slots]; /* scan order varies: reordering */
            BreakPredictionInputBatch b;
            u32 got = 0u;
            if (d->len == 0u || d->deliver_at > now) continue;
            ASSERT_EQ(break_prediction_wire_decode_inputs(d->bytes, d->len, 4u, &b),
                      BREAK_PREDICTION_OK);
            ASSERT_EQ(break_prediction_inbox_accept(&box, &b, server_apply, &srv, &got),
                      BREAK_PREDICTION_OK);
            if (--d->copies == 0u) d->len = 0u;
        }
        rng = rng * 1103515245u + 12345u;
        if (now % 3u == 0u && (rng >> 16) % 10u >= 3u) {
            Datagram *d = &down[now % k_slots];
            ASSERT_EQ(break_prediction_wire_encode_snapshot(
                          break_prediction_inbox_last_tick(&box), &srv.state,
                          (u32)sizeof srv.state, d->bytes, sizeof d->bytes, &d->len),
                      BREAK_PREDICTION_OK);
            d->deliver_at = now + (rng >> 8) % 4u;
            d->copies = 1u;
        }
        for (u32 k = 0u; k < (u32)k_slots; ++k) {
            Datagram *d = &down[(now * 3u + k) % k_slots];
            BreakPredictionSnapshot snap;
            BreakPredictionReconcile rep;
            BreakPredictionResult r;
            if (d->len == 0u || d->deliver_at > now) continue;
            ASSERT_EQ(break_prediction_wire_decode_snapshot(d->bytes, d->len, 8u, &snap),
                      BREAK_PREDICTION_OK);
            r = break_prediction_reconcile(client, snap.tick, snap.state, &rep);
            ASSERT_TRUE(r == BREAK_PREDICTION_OK || r == BREAK_PREDICTION_STALE);
            ASSERT_FALSE(rep.resync); /* the server never runs ahead of the client */
            if (rep.mispredicted) mispredictions++;
            d->len = 0u;
        }
    }
    ASSERT_EQ(srv.out_of_order, 0u);
    ASSERT_EQ(box.applied, (u64)k_ticks);
    ASSERT_TRUE(box.duplicates > 0u);
    ASSERT_TRUE(mispredictions > 0u);
    ASSERT_EQ(break_prediction_inbox_last_tick(&box), (u64)k_ticks);
    ASSERT_EQ(break_prediction_pending_count(client), 0u);
    ASSERT_EQ(break_prediction_confirmed_tick(client), (u64)k_ticks);
    ASSERT_EQ(memcmp(break_prediction_predicted_state(client), &srv.state, sizeof srv.state), 0);
    break_prediction_destroy(client);
}

TEST_MAIN_BEGIN()
    RUN_TEST(an_input_batch_has_the_documented_layout);
    RUN_TEST(a_batch_round_trips_and_sends_the_oldest_when_many_are_pending);
    RUN_TEST(a_batch_of_large_inputs_fits_one_envelope_payload);
    RUN_TEST(encoding_reports_sizes_and_sends_nothing_without_pending_input);
    RUN_TEST(a_snapshot_has_the_documented_layout_and_round_trips);
    RUN_TEST(malformed_input_batches_are_rejected);
    RUN_TEST(malformed_snapshots_are_rejected);
    RUN_TEST(the_inbox_applies_each_input_once_and_in_order);
    RUN_TEST(the_inbox_waits_at_a_gap_and_stops_where_apply_refuses);
    RUN_TEST(a_lossy_loop_converges_to_the_server_state);
TEST_MAIN_END()
