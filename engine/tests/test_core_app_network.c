#ifndef _WIN32
#define _POSIX_C_SOURCE 200112L
#endif
#include "test_framework.h"

#include "../apps/core_app/core_app_network.h"

#include <core/clock_offset.h>

#include <stdlib.h>
#include <string.h>

static void env_set(const char *name, const char *value) {
#ifdef _WIN32
    (void)_putenv_s(name, value);
#else
    (void)setenv(name, value, 1);
#endif
}

static void entity_fill(CoreAppSnapshotEntity *entity, u32 index, u32 generation, f32 x) {
    entity->index = index;
    entity->generation = generation;
    entity->x = x;
    entity->y = 0.5f;
    entity->z = 3.25f;
    entity->flags = 0x1u;
}

TEST(snapshot_build_rejects_entity_count_over_capacity) {
    CoreAppSnapshotEntity entities[CORE_APP_SNAPSHOT_MAX_ENTITIES + 1u];
    CoreAppSnapshot snapshot;
    memset(entities, 0, sizeof(entities));
    memset(&snapshot, 0, sizeof(snapshot));
    ASSERT_EQ(core_app_snapshot_build(&snapshot, 7u, 3u, 1u, entities,
                                      CORE_APP_SNAPSHOT_MAX_ENTITIES + 1u),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
}

TEST(snapshot_roundtrip_preserves_fields) {
    CoreAppSnapshotEntity entities[2];
    CoreAppSnapshot built;
    CoreAppSnapshot decoded;
    u8 buffer[CORE_APP_SNAPSHOT_MAX_BYTES];
    size_t size = 0u;
    memset(&built, 0, sizeof(built));
    memset(&decoded, 0, sizeof(decoded));
    entity_fill(&entities[0], 2u, 3u, 1.5f);
    entity_fill(&entities[1], 5u, 3u, -2.5f);
    ASSERT_EQ(core_app_snapshot_build(&built, 42u, 3u, core_app_snapshot_schema_hash(),
                                      entities, 2u),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_snapshot_encode(&built, buffer, sizeof(buffer), &size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(size, CORE_APP_SNAPSHOT_HEADER_BYTES + 2u * CORE_APP_SNAPSHOT_ENTITY_BYTES);
    ASSERT_EQ(core_app_snapshot_decode(buffer, size, &decoded), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(decoded.frame_id, 42u);
    ASSERT_EQ(decoded.level_generation, 3u);
    ASSERT_EQ(decoded.entity_count, 2u);
    ASSERT_EQ(decoded.entities[0].index, 2u);
    ASSERT_EQ(decoded.entities[0].generation, 3u);
    ASSERT_EQ(decoded.entities[1].index, 5u);
    ASSERT_EQ(decoded.entities[1].x, -2.5f);
    ASSERT_EQ(decoded.entities[1].flags, 0x1u);
}

TEST(snapshot_encode_rejects_small_buffer_without_writing) {
    CoreAppSnapshotEntity entities[1];
    CoreAppSnapshot built;
    u8 buffer[CORE_APP_SNAPSHOT_MAX_BYTES];
    u8 untouched[CORE_APP_SNAPSHOT_MAX_BYTES];
    size_t size = 123u;
    entity_fill(&entities[0], 1u, 1u, 0.0f);
    memset(buffer, 0xAB, sizeof(buffer));
    memcpy(untouched, buffer, sizeof(buffer));
    ASSERT_EQ(core_app_snapshot_build(&built, 1u, 1u, 1u, entities, 1u),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_snapshot_encode(&built, buffer, 8u, &size),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(size, 123u);
    ASSERT_EQ(memcmp(buffer, untouched, sizeof(buffer)), 0);
}

TEST(snapshot_decode_rejects_bad_magic) {
    CoreAppSnapshotEntity entities[1];
    CoreAppSnapshot built;
    CoreAppSnapshot decoded;
    u8 buffer[CORE_APP_SNAPSHOT_MAX_BYTES];
    size_t size = 0u;
    entity_fill(&entities[0], 1u, 1u, 0.0f);
    ASSERT_EQ(core_app_snapshot_build(&built, 1u, 1u, 1u, entities, 1u),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_snapshot_encode(&built, buffer, sizeof(buffer), &size),
              CORE_APP_SNAPSHOT_OK);
    buffer[0] ^= 0xFFu;
    ASSERT_EQ(core_app_snapshot_decode(buffer, size, &decoded), CORE_APP_SNAPSHOT_BAD_MAGIC);
}

TEST(snapshot_decode_rejects_unknown_version) {
    CoreAppSnapshotEntity entities[1];
    CoreAppSnapshot built;
    CoreAppSnapshot decoded;
    u8 buffer[CORE_APP_SNAPSHOT_MAX_BYTES];
    size_t size = 0u;
    entity_fill(&entities[0], 1u, 1u, 0.0f);
    ASSERT_EQ(core_app_snapshot_build(&built, 1u, 1u, 1u, entities, 1u),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_snapshot_encode(&built, buffer, sizeof(buffer), &size),
              CORE_APP_SNAPSHOT_OK);
    buffer[4] = 0x7Fu;
    ASSERT_EQ(core_app_snapshot_decode(buffer, size, &decoded),
              CORE_APP_SNAPSHOT_BAD_VERSION);
}

TEST(snapshot_decode_rejects_truncated_and_over_limit_payloads) {
    CoreAppSnapshotEntity entities[1];
    CoreAppSnapshot built;
    CoreAppSnapshot decoded;
    u8 buffer[CORE_APP_SNAPSHOT_MAX_BYTES];
    size_t size = 0u;
    entity_fill(&entities[0], 1u, 1u, 0.0f);
    ASSERT_EQ(core_app_snapshot_build(&built, 1u, 1u, 1u, entities, 1u),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_snapshot_encode(&built, buffer, sizeof(buffer), &size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_snapshot_decode(buffer, size - 1u, &decoded),
              CORE_APP_SNAPSHOT_TRUNCATED);
    /* A declared count beyond the fixed capacity must be rejected before the
     * decoder indexes anything. count lives at header offset 28. */
    buffer[28] = 0xFFu;
    buffer[29] = 0xFFu;
    buffer[30] = 0x00u;
    buffer[31] = 0x00u;
    ASSERT_EQ(core_app_snapshot_decode(buffer, size, &decoded),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
}

TEST(snapshot_schema_hash_is_stable_and_layout_sensitive) {
    u32 first = core_app_snapshot_schema_hash();
    u32 second = core_app_snapshot_schema_hash();
    ASSERT_EQ(first, second);
    ASSERT_NEQ(first, 0u);
}

TEST(snapshot_inbox_drops_unauthenticated_and_unknown_messages) {
    CoreAppSnapshotInbox inbox;
    CoreAppSnapshot snapshot;
    memset(&snapshot, 0, sizeof(snapshot));
    snapshot.schema_hash = core_app_snapshot_schema_hash();
    snapshot.level_generation = 2u;
    core_app_snapshot_inbox_init(&inbox, false, CORE_APP_SNAPSHOT_MESSAGE_ID,
                                 core_app_snapshot_schema_hash());
    ASSERT_EQ(core_app_snapshot_admit(&inbox, CORE_APP_SNAPSHOT_MESSAGE_ID, &snapshot, 2u),
              CORE_APP_SNAPSHOT_REJECTED_UNAUTHENTICATED);
    ASSERT_EQ(inbox.rejected_unauthenticated, 1u);
    inbox.authenticated = true;
    ASSERT_EQ(core_app_snapshot_admit(&inbox, (u16)(CORE_APP_SNAPSHOT_MESSAGE_ID + 1u),
                                      &snapshot, 2u),
              CORE_APP_SNAPSHOT_REJECTED_UNKNOWN_MESSAGE);
    ASSERT_EQ(inbox.rejected_unknown_message, 1u);
    ASSERT_EQ(inbox.accepted_snapshots, 0u);
}

TEST(snapshot_inbox_drops_schema_mismatch_and_stale_level) {
    CoreAppSnapshotInbox inbox;
    CoreAppSnapshot snapshot;
    memset(&snapshot, 0, sizeof(snapshot));
    snapshot.schema_hash = core_app_snapshot_schema_hash();
    snapshot.level_generation = 2u;
    core_app_snapshot_inbox_init(&inbox, true, CORE_APP_SNAPSHOT_MESSAGE_ID,
                                 core_app_snapshot_schema_hash());
    snapshot.schema_hash ^= 0x1u;
    ASSERT_EQ(core_app_snapshot_admit(&inbox, CORE_APP_SNAPSHOT_MESSAGE_ID, &snapshot, 2u),
              CORE_APP_SNAPSHOT_REJECTED_SCHEMA);
    ASSERT_EQ(inbox.rejected_schema, 1u);
    snapshot.schema_hash = core_app_snapshot_schema_hash();
    ASSERT_EQ(core_app_snapshot_admit(&inbox, CORE_APP_SNAPSHOT_MESSAGE_ID, &snapshot, 3u),
              CORE_APP_SNAPSHOT_REJECTED_STALE_LEVEL);
    ASSERT_EQ(inbox.rejected_stale_level, 1u);
    ASSERT_EQ(core_app_snapshot_admit(&inbox, CORE_APP_SNAPSHOT_MESSAGE_ID, &snapshot, 2u),
              CORE_APP_SNAPSHOT_ADMITTED);
    ASSERT_EQ(inbox.accepted_snapshots, 1u);
}

TEST(snapshot_outbox_is_bounded_and_counts_drops) {
    CoreAppSnapshotOutbox outbox;
    CoreAppSnapshot snapshot;
    CoreAppSnapshot popped;
    memset(&snapshot, 0, sizeof(snapshot));
    snapshot.level_generation = 1u;
    core_app_snapshot_outbox_init(&outbox);
    for (u32 i = 0u; i < CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY; ++i) {
        snapshot.frame_id = i + 1u;
        ASSERT_EQ(core_app_snapshot_outbox_push(&outbox, &snapshot), CORE_APP_SNAPSHOT_OK);
    }
    ASSERT_EQ(outbox.count, CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY);
    snapshot.frame_id = 99u;
    ASSERT_EQ(core_app_snapshot_outbox_push(&outbox, &snapshot),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(outbox.dropped, 1u);
    ASSERT_EQ(outbox.enqueued, CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY);
    ASSERT_TRUE(core_app_snapshot_outbox_pop(&outbox, &popped));
    ASSERT_EQ(popped.frame_id, 1u);
    ASSERT_EQ(outbox.count, CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY - 1u);
    ASSERT_EQ(core_app_snapshot_outbox_push(&outbox, &snapshot), CORE_APP_SNAPSHOT_OK);
    while (core_app_snapshot_outbox_pop(&outbox, &popped)) {}
    ASSERT_EQ(popped.frame_id, 99u);
    ASSERT_FALSE(core_app_snapshot_outbox_pop(&outbox, &popped));
}

TEST(secret_env_decodes_and_removes_the_variable) {
    u8 key[32];
    memset(key, 0xAA, sizeof(key));
    env_set("CORE_APP_UNIT_PSK",
            "0f1e2d3c4b5a69788796a5b4c3d2e1f000112233445566778899aabbccddeeFF");
    ASSERT_TRUE(core_app_net_take_secret_env("CORE_APP_UNIT_PSK", key, sizeof(key)));
    ASSERT_EQ(key[0], 0x0fu);
    ASSERT_EQ(key[15], 0xf0u);
    ASSERT_EQ(key[16], 0x00u);
    ASSERT_EQ(key[31], 0xffu);
    ASSERT_TRUE(getenv("CORE_APP_UNIT_PSK") == NULL);
    ASSERT_FALSE(core_app_net_take_secret_env("CORE_APP_UNIT_PSK", key, sizeof(key)));
}

TEST(secret_env_rejects_bad_values_and_still_removes_them) {
    static const char *const bad[] = {
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0f1e2d3c4b5a69788796a5b4c3d2e1f000112233445566778899aabbccddeeF",
        "0f1e2d3c4b5a69788796a5b4c3d2e1f000112233445566778899aabbccddeeFF0",
        "0f1e2d3c4b5a69788796a5b4c3d2e1f000112233445566778899aabbccddeegg",
    };
    for (usize i = 0u; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        u8 key[32];
        memset(key, 0xAA, sizeof(key));
        env_set("CORE_APP_UNIT_PSK", bad[i]);
        ASSERT_FALSE(core_app_net_take_secret_env("CORE_APP_UNIT_PSK", key, sizeof(key)));
        ASSERT_TRUE(getenv("CORE_APP_UNIT_PSK") == NULL);
        for (usize b = 0u; b < sizeof(key); ++b) ASSERT_EQ(key[b], 0u);
    }
    u8 key[32];
    ASSERT_FALSE(core_app_net_take_secret_env(NULL, key, sizeof(key)));
    ASSERT_FALSE(core_app_net_take_secret_env("", key, sizeof(key)));
    ASSERT_FALSE(core_app_net_take_secret_env("CORE_APP_UNIT_PSK", NULL, sizeof(key)));
}

static const u8 k_probe_request[CORE_APP_CLOCK_PROBE_BYTES] = {
    0x43, 0x4c, 0x4b, 0x50, 0x01, 0x00, 0x00, 0x00,
    0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0};

TEST(clock_probe_round_trips_with_golden_bytes) {
    CoreAppClockProbe probe = {CORE_APP_CLOCK_PROBE_REQUEST, 0x0102030405060708ull, 0u, 0u};
    u8 wire[CORE_APP_CLOCK_PROBE_BYTES + 4u];
    size_t size = 0u;
    memset(wire, 0xa5, sizeof(wire));
    ASSERT_EQ(core_app_clock_probe_encode(&probe, wire, sizeof(wire), &size), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(size, (size_t)CORE_APP_CLOCK_PROBE_BYTES);
    ASSERT_TRUE(memcmp(wire, k_probe_request, sizeof(k_probe_request)) == 0);

    CoreAppClockProbe decoded;
    memset(&decoded, 0xa5, sizeof(decoded));
    ASSERT_EQ(core_app_clock_probe_decode(wire, size, &decoded), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(decoded.kind, CORE_APP_CLOCK_PROBE_REQUEST);
    ASSERT_EQ(decoded.t0, 0x0102030405060708ull);
    ASSERT_EQ(decoded.t1, 0u);
    ASSERT_EQ(decoded.t2, 0u);

    CoreAppClockProbe reply;
    ASSERT_EQ(core_app_clock_probe_answer(&decoded, 0x1111ull, 0x2222ull, &reply),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(reply.kind, CORE_APP_CLOCK_PROBE_REPLY);
    ASSERT_EQ(reply.t0, 0x0102030405060708ull);
    ASSERT_EQ(core_app_clock_probe_encode(&reply, wire, sizeof(wire), &size), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(wire[4], 0x02u);
    ASSERT_EQ(wire[16], 0x11u);
    ASSERT_EQ(wire[17], 0x11u);
    ASSERT_EQ(wire[18], 0x00u);
    ASSERT_EQ(wire[24], 0x22u);
    ASSERT_EQ(wire[31], 0x00u);
    ASSERT_EQ(core_app_clock_probe_decode(wire, size, &decoded), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(decoded.kind, CORE_APP_CLOCK_PROBE_REPLY);
    ASSERT_EQ(decoded.t1, 0x1111ull);
    ASSERT_EQ(decoded.t2, 0x2222ull);
}

TEST(clock_probe_decode_rejects_every_malformed_payload) {
    u8 wire[CORE_APP_CLOCK_PROBE_BYTES + 1u];
    CoreAppClockProbe out = {CORE_APP_CLOCK_PROBE_REPLY, 7u, 8u, 9u};
    memcpy(wire, k_probe_request, sizeof(k_probe_request));
    wire[CORE_APP_CLOCK_PROBE_BYTES] = 0u;
    ASSERT_EQ(core_app_clock_probe_decode(wire, CORE_APP_CLOCK_PROBE_BYTES - 1u, &out),
              CORE_APP_SNAPSHOT_TRUNCATED);
    ASSERT_EQ(core_app_clock_probe_decode(wire, CORE_APP_CLOCK_PROBE_BYTES + 1u, &out),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(core_app_clock_probe_decode(NULL, CORE_APP_CLOCK_PROBE_BYTES, &out),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_clock_probe_decode(wire, CORE_APP_CLOCK_PROBE_BYTES, NULL),
              CORE_APP_SNAPSHOT_INVALID);
    static const struct { usize at; u8 value; CoreAppSnapshotOutcome want; } bad[] = {
        {0u, 0x00u, CORE_APP_SNAPSHOT_BAD_MAGIC},
        {3u, 0x51u, CORE_APP_SNAPSHOT_BAD_MAGIC},
        {4u, 0x00u, CORE_APP_SNAPSHOT_BAD_VERSION},
        {4u, 0x03u, CORE_APP_SNAPSHOT_BAD_VERSION},
        {5u, 0x01u, CORE_APP_SNAPSHOT_INVALID},
        {6u, 0x01u, CORE_APP_SNAPSHOT_INVALID},
        {7u, 0x80u, CORE_APP_SNAPSHOT_INVALID},
        {16u, 0x01u, CORE_APP_SNAPSHOT_INVALID}, /* request carrying t1 */
        {31u, 0x01u, CORE_APP_SNAPSHOT_INVALID}, /* request carrying t2 */
    };
    for (usize i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        memcpy(wire, k_probe_request, sizeof(k_probe_request));
        wire[bad[i].at] = bad[i].value;
        ASSERT_EQ(core_app_clock_probe_decode(wire, CORE_APP_CLOCK_PROBE_BYTES, &out), bad[i].want);
        ASSERT_EQ(out.t0, 7u);
    }
}

TEST(clock_probe_encode_and_answer_refuse_invalid_values) {
    u8 wire[CORE_APP_CLOCK_PROBE_BYTES];
    size_t size = 99u;
    memset(wire, 0x5a, sizeof(wire));
    CoreAppClockProbe bad_kind = {(CoreAppClockProbeKind)3, 1u, 0u, 0u};
    CoreAppClockProbe request_t1 = {CORE_APP_CLOCK_PROBE_REQUEST, 1u, 2u, 0u};
    CoreAppClockProbe request_t2 = {CORE_APP_CLOCK_PROBE_REQUEST, 1u, 0u, 2u};
    CoreAppClockProbe ok = {CORE_APP_CLOCK_PROBE_REQUEST, 1u, 0u, 0u};
    ASSERT_EQ(core_app_clock_probe_encode(&bad_kind, wire, sizeof(wire), &size), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_clock_probe_encode(&request_t1, wire, sizeof(wire), &size), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_clock_probe_encode(&request_t2, wire, sizeof(wire), &size), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_clock_probe_encode(&ok, wire, sizeof(wire) - 1u, &size), CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(core_app_clock_probe_encode(NULL, wire, sizeof(wire), &size), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_clock_probe_encode(&ok, NULL, sizeof(wire), &size), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_clock_probe_encode(&ok, wire, sizeof(wire), NULL), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(size, 99u);
    ASSERT_EQ(wire[0], 0x5au);

    CoreAppClockProbe reply = {CORE_APP_CLOCK_PROBE_REPLY, 1u, 5u, 6u};
    CoreAppClockProbe out = {CORE_APP_CLOCK_PROBE_REQUEST, 42u, 0u, 0u};
    ASSERT_EQ(core_app_clock_probe_answer(&reply, 1u, 2u, &out), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_clock_probe_answer(&ok, 3u, 2u, &out), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_clock_probe_answer(NULL, 1u, 2u, &out), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_clock_probe_answer(&ok, 1u, 2u, NULL), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(out.t0, 42u);
    ASSERT_EQ(core_app_clock_probe_answer(&ok, 2u, 2u, &out), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(out.t1, 2u);
    ASSERT_EQ(out.t2, 2u);
}

TEST(clock_probe_exchange_feeds_the_offset_estimator) {
    /* B's clock is 250000 us ahead of A's; 300 us each way, 20 us hold */
    CoreAppClockProbe request = {CORE_APP_CLOCK_PROBE_REQUEST, 1000000u, 0u, 0u};
    u8 wire[CORE_APP_CLOCK_PROBE_BYTES];
    size_t size = 0u;
    CoreAppClockProbe at_b, reply, at_a;
    ASSERT_EQ(core_app_clock_probe_encode(&request, wire, sizeof(wire), &size), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_clock_probe_decode(wire, size, &at_b), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_clock_probe_answer(&at_b, 1250300u, 1250320u, &reply), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_clock_probe_encode(&reply, wire, sizeof(wire), &size), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_clock_probe_decode(wire, size, &at_a), CORE_APP_SNAPSHOT_OK);
    ClockOffsetSample sample = {at_a.t0, at_a.t1, at_a.t2, 1000620u};
    ClockOffsetEstimator estimator;
    ClockOffsetEstimate estimate;
    clock_offset_init(&estimator);
    ASSERT_EQ(clock_offset_add(&estimator, &sample), CLOCK_OFFSET_OK);
    ASSERT_EQ(clock_offset_estimate(&estimator, &estimate), CLOCK_OFFSET_OK);
    ASSERT_EQ(estimate.offset_us, 250000);
    ASSERT_EQ(estimate.delay_us, 600);
}

static const u8 k_welcome[CORE_APP_SESSION_WELCOME_BYTES] = {
    0x53, 0x45, 0x53, 0x57, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};

TEST(session_welcome_round_trips_with_golden_bytes) {
    u8 wire[CORE_APP_SESSION_WELCOME_BYTES + 4u];
    size_t size = 0u;
    u64 id = 0u;
    memset(wire, 0xa5, sizeof(wire));
    ASSERT_EQ(core_app_session_welcome_encode(0x0102030405060708ull, wire, sizeof(wire), &size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(size, (size_t)CORE_APP_SESSION_WELCOME_BYTES);
    ASSERT_TRUE(memcmp(wire, k_welcome, sizeof(k_welcome)) == 0);
    ASSERT_EQ(wire[CORE_APP_SESSION_WELCOME_BYTES], 0xa5u);
    ASSERT_EQ(core_app_session_welcome_decode(wire, size, &id), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(id, 0x0102030405060708ull);
    ASSERT_EQ(core_app_session_welcome_encode(1u, wire, CORE_APP_SESSION_WELCOME_BYTES, &size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_session_welcome_decode(wire, size, &id), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(id, 1u);
}

TEST(session_welcome_decode_rejects_every_malformed_payload) {
    u8 wire[CORE_APP_SESSION_WELCOME_BYTES + 1u];
    u64 id = 77u;
    memcpy(wire, k_welcome, sizeof(k_welcome));
    wire[CORE_APP_SESSION_WELCOME_BYTES] = 0u;
    for (size_t n = 0u; n < CORE_APP_SESSION_WELCOME_BYTES; ++n) {
        ASSERT_EQ(core_app_session_welcome_decode(wire, n, &id), CORE_APP_SNAPSHOT_TRUNCATED);
    }
    ASSERT_EQ(core_app_session_welcome_decode(wire, sizeof(wire), &id), CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(core_app_session_welcome_decode(NULL, CORE_APP_SESSION_WELCOME_BYTES, &id),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_session_welcome_decode(wire, CORE_APP_SESSION_WELCOME_BYTES, NULL),
              CORE_APP_SNAPSHOT_INVALID);
    static const struct { usize at; u8 value; CoreAppSnapshotOutcome want; } bad[] = {
        {0u, 0x00u, CORE_APP_SNAPSHOT_BAD_MAGIC},
        {3u, 0x58u, CORE_APP_SNAPSHOT_BAD_MAGIC},
        {4u, 0x01u, CORE_APP_SNAPSHOT_INVALID},
        {7u, 0x80u, CORE_APP_SNAPSHOT_INVALID},
    };
    for (usize i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        memcpy(wire, k_welcome, sizeof(k_welcome));
        wire[bad[i].at] = bad[i].value;
        ASSERT_EQ(core_app_session_welcome_decode(wire, CORE_APP_SESSION_WELCOME_BYTES, &id),
                  bad[i].want);
    }
    memcpy(wire, k_welcome, sizeof(k_welcome));
    memset(wire + 8, 0, 8u); /* session id 0 */
    ASSERT_EQ(core_app_session_welcome_decode(wire, CORE_APP_SESSION_WELCOME_BYTES, &id),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(id, 77u);
}

TEST(session_welcome_encode_refuses_invalid_values_without_writing) {
    u8 wire[CORE_APP_SESSION_WELCOME_BYTES];
    size_t size = 99u;
    memset(wire, 0x5a, sizeof(wire));
    ASSERT_EQ(core_app_session_welcome_encode(0u, wire, sizeof(wire), &size), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_session_welcome_encode(1u, wire, sizeof(wire) - 1u, &size),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(core_app_session_welcome_encode(1u, NULL, sizeof(wire), &size), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_session_welcome_encode(1u, wire, sizeof(wire), NULL), CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(size, 99u);
    for (usize i = 0; i < sizeof(wire); ++i) ASSERT_EQ(wire[i], 0x5au);
}

static const u8 k_relay[CORE_APP_VOICE_RELAY_HEADER_BYTES + 3u] = {
    0x56, 0x52, 0x4c, 0x59, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
    0x42, 0x52, 0x56};

TEST(voice_relay_round_trips_with_golden_bytes) {
    static const u8 frame[3] = {0x42, 0x52, 0x56};
    u8 wire[CORE_APP_VOICE_RELAY_MAX_BYTES + 4u];
    size_t size = 0u;
    u64 source = 0u;
    const u8 *out_frame = NULL;
    size_t out_frame_size = 0u;
    ASSERT_EQ(CORE_APP_VOICE_RELAY_MESSAGE_ID, 0x4007u);
    ASSERT_EQ(CORE_APP_VOICE_RELAY_MAX_FRAME_BYTES, 976u);
    ASSERT_EQ(CORE_APP_VOICE_RELAY_MAX_BYTES, 992u);
    memset(wire, 0xa5, sizeof(wire));
    ASSERT_EQ(core_app_voice_relay_encode(0x0102030405060708ull, frame, sizeof(frame), wire,
                                          sizeof(wire), &size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(size, sizeof(k_relay));
    ASSERT_TRUE(memcmp(wire, k_relay, sizeof(k_relay)) == 0);
    ASSERT_EQ(wire[sizeof(k_relay)], 0xa5u);
    ASSERT_EQ(core_app_voice_relay_decode(wire, size, &source, &out_frame, &out_frame_size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(source, 0x0102030405060708ull);
    ASSERT_TRUE(out_frame == wire + CORE_APP_VOICE_RELAY_HEADER_BYTES);
    ASSERT_EQ(out_frame_size, sizeof(frame));
    {
        static u8 big[CORE_APP_VOICE_RELAY_MAX_FRAME_BYTES];
        memset(big, 0x11, sizeof(big));
        ASSERT_EQ(core_app_voice_relay_encode(9u, big, sizeof(big), wire,
                                              CORE_APP_VOICE_RELAY_MAX_BYTES, &size),
                  CORE_APP_SNAPSHOT_OK);
        ASSERT_EQ(size, (size_t)CORE_APP_VOICE_RELAY_MAX_BYTES);
        ASSERT_EQ(core_app_voice_relay_decode(wire, size, &source, &out_frame, &out_frame_size),
                  CORE_APP_SNAPSHOT_OK);
        ASSERT_EQ(source, 9u);
        ASSERT_EQ(out_frame_size, sizeof(big));
    }
}

TEST(voice_relay_decode_rejects_every_malformed_payload) {
    u8 wire[CORE_APP_VOICE_RELAY_MAX_BYTES + 1u];
    u64 source = 77u;
    const u8 *frame = (const u8 *)&source;
    size_t frame_size = 55u;
    memset(wire, 0, sizeof(wire));
    memcpy(wire, k_relay, sizeof(k_relay));
    for (size_t n = 0u; n <= CORE_APP_VOICE_RELAY_HEADER_BYTES; ++n) {
        ASSERT_EQ(core_app_voice_relay_decode(wire, n, &source, &frame, &frame_size),
                  CORE_APP_SNAPSHOT_TRUNCATED);
    }
    ASSERT_EQ(core_app_voice_relay_decode(wire, sizeof(wire), &source, &frame, &frame_size),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(core_app_voice_relay_decode(NULL, sizeof(k_relay), &source, &frame, &frame_size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_relay_decode(wire, sizeof(k_relay), NULL, &frame, &frame_size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_relay_decode(wire, sizeof(k_relay), &source, NULL, &frame_size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_relay_decode(wire, sizeof(k_relay), &source, &frame, NULL),
              CORE_APP_SNAPSHOT_INVALID);
    static const struct { usize at; u8 value; CoreAppSnapshotOutcome want; } bad[] = {
        {0u, 0x00u, CORE_APP_SNAPSHOT_BAD_MAGIC},
        {3u, 0x58u, CORE_APP_SNAPSHOT_BAD_MAGIC},
        {4u, 0x01u, CORE_APP_SNAPSHOT_INVALID},
        {7u, 0x80u, CORE_APP_SNAPSHOT_INVALID},
    };
    for (usize i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        memcpy(wire, k_relay, sizeof(k_relay));
        wire[bad[i].at] = bad[i].value;
        ASSERT_EQ(core_app_voice_relay_decode(wire, sizeof(k_relay), &source, &frame, &frame_size),
                  bad[i].want);
    }
    memcpy(wire, k_relay, sizeof(k_relay));
    memset(wire + 8, 0, 8u);
    ASSERT_EQ(core_app_voice_relay_decode(wire, sizeof(k_relay), &source, &frame, &frame_size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(source, 77u);
    ASSERT_TRUE(frame == (const u8 *)&source);
    ASSERT_EQ(frame_size, 55u);
}

TEST(voice_relay_encode_refuses_invalid_values_without_writing) {
    static u8 frame[CORE_APP_VOICE_RELAY_MAX_FRAME_BYTES + 1u];
    u8 wire[CORE_APP_VOICE_RELAY_MAX_BYTES + 16u];
    size_t size = 99u;
    memset(frame, 0x11, sizeof(frame));
    memset(wire, 0x5a, sizeof(wire));
    ASSERT_EQ(core_app_voice_relay_encode(0u, frame, 3u, wire, sizeof(wire), &size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_relay_encode(1u, NULL, 3u, wire, sizeof(wire), &size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_relay_encode(1u, frame, 0u, wire, sizeof(wire), &size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_relay_encode(1u, frame, sizeof(frame), wire, sizeof(wire), &size),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(core_app_voice_relay_encode(1u, frame, 3u, wire,
                                          CORE_APP_VOICE_RELAY_HEADER_BYTES + 2u, &size),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(core_app_voice_relay_encode(1u, frame, 3u, NULL, sizeof(wire), &size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_relay_encode(1u, frame, 3u, wire, sizeof(wire), NULL),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(size, 99u);
    for (usize i = 0; i < sizeof(wire); ++i) ASSERT_EQ(wire[i], 0x5au);
}

static const u8 k_mute[CORE_APP_VOICE_MUTE_BYTES] = {
    0x56, 0x4d, 0x55, 0x54, 0x01, 0x00, 0x00, 0x00,
    0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};

TEST(voice_mute_round_trips_with_golden_bytes) {
    u8 wire[CORE_APP_VOICE_MUTE_BYTES + 4u];
    size_t size = 0u;
    u64 target = 0u;
    bool muted = false;
    ASSERT_EQ(CORE_APP_VOICE_MUTE_MESSAGE_ID, 0x4008u);
    memset(wire, 0xa5, sizeof(wire));
    ASSERT_EQ(core_app_voice_mute_encode(0x0102030405060708ull, true, wire, sizeof(wire), &size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(size, (size_t)CORE_APP_VOICE_MUTE_BYTES);
    ASSERT_TRUE(memcmp(wire, k_mute, sizeof(k_mute)) == 0);
    ASSERT_EQ(wire[CORE_APP_VOICE_MUTE_BYTES], 0xa5u);
    ASSERT_EQ(core_app_voice_mute_decode(wire, size, &target, &muted), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(target, 0x0102030405060708ull);
    ASSERT_TRUE(muted);
    ASSERT_EQ(core_app_voice_mute_encode(3u, false, wire, CORE_APP_VOICE_MUTE_BYTES, &size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(wire[4], 0x00u);
    ASSERT_EQ(core_app_voice_mute_decode(wire, size, &target, &muted), CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(target, 3u);
    ASSERT_FALSE(muted);
}

TEST(voice_mute_decode_rejects_every_malformed_payload) {
    u8 wire[CORE_APP_VOICE_MUTE_BYTES + 1u];
    u64 target = 77u;
    bool muted = false;
    memcpy(wire, k_mute, sizeof(k_mute));
    wire[CORE_APP_VOICE_MUTE_BYTES] = 0u;
    for (size_t n = 0u; n < CORE_APP_VOICE_MUTE_BYTES; ++n) {
        ASSERT_EQ(core_app_voice_mute_decode(wire, n, &target, &muted),
                  CORE_APP_SNAPSHOT_TRUNCATED);
    }
    ASSERT_EQ(core_app_voice_mute_decode(wire, sizeof(wire), &target, &muted),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(core_app_voice_mute_decode(NULL, CORE_APP_VOICE_MUTE_BYTES, &target, &muted),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_mute_decode(wire, CORE_APP_VOICE_MUTE_BYTES, NULL, &muted),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_mute_decode(wire, CORE_APP_VOICE_MUTE_BYTES, &target, NULL),
              CORE_APP_SNAPSHOT_INVALID);
    static const struct { usize at; u8 value; CoreAppSnapshotOutcome want; } bad[] = {
        {0u, 0x00u, CORE_APP_SNAPSHOT_BAD_MAGIC},
        {3u, 0x55u, CORE_APP_SNAPSHOT_BAD_MAGIC},
        {4u, 0x03u, CORE_APP_SNAPSHOT_INVALID},
        {5u, 0x01u, CORE_APP_SNAPSHOT_INVALID},
        {7u, 0x80u, CORE_APP_SNAPSHOT_INVALID},
    };
    for (usize i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        memcpy(wire, k_mute, sizeof(k_mute));
        wire[bad[i].at] = bad[i].value;
        ASSERT_EQ(core_app_voice_mute_decode(wire, CORE_APP_VOICE_MUTE_BYTES, &target, &muted),
                  bad[i].want);
    }
    memcpy(wire, k_mute, sizeof(k_mute));
    memset(wire + 8, 0, 8u);
    ASSERT_EQ(core_app_voice_mute_decode(wire, CORE_APP_VOICE_MUTE_BYTES, &target, &muted),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(target, 77u);
    ASSERT_FALSE(muted);
}

TEST(voice_mute_encode_refuses_invalid_values_without_writing) {
    u8 wire[CORE_APP_VOICE_MUTE_BYTES];
    size_t size = 99u;
    memset(wire, 0x5a, sizeof(wire));
    ASSERT_EQ(core_app_voice_mute_encode(0u, true, wire, sizeof(wire), &size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_mute_encode(1u, true, wire, sizeof(wire) - 1u, &size),
              CORE_APP_SNAPSHOT_OVER_LIMIT);
    ASSERT_EQ(core_app_voice_mute_encode(1u, true, NULL, sizeof(wire), &size),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(core_app_voice_mute_encode(1u, true, wire, sizeof(wire), NULL),
              CORE_APP_SNAPSHOT_INVALID);
    ASSERT_EQ(size, 99u);
    for (usize i = 0; i < sizeof(wire); ++i) ASSERT_EQ(wire[i], 0x5au);
}

TEST_MAIN_BEGIN()
    RUN_TEST(snapshot_build_rejects_entity_count_over_capacity);
    RUN_TEST(snapshot_roundtrip_preserves_fields);
    RUN_TEST(snapshot_encode_rejects_small_buffer_without_writing);
    RUN_TEST(snapshot_decode_rejects_bad_magic);
    RUN_TEST(snapshot_decode_rejects_unknown_version);
    RUN_TEST(snapshot_decode_rejects_truncated_and_over_limit_payloads);
    RUN_TEST(snapshot_schema_hash_is_stable_and_layout_sensitive);
    RUN_TEST(snapshot_inbox_drops_unauthenticated_and_unknown_messages);
    RUN_TEST(snapshot_inbox_drops_schema_mismatch_and_stale_level);
    RUN_TEST(snapshot_outbox_is_bounded_and_counts_drops);
    RUN_TEST(secret_env_decodes_and_removes_the_variable);
    RUN_TEST(secret_env_rejects_bad_values_and_still_removes_them);
    RUN_TEST(clock_probe_round_trips_with_golden_bytes);
    RUN_TEST(clock_probe_decode_rejects_every_malformed_payload);
    RUN_TEST(clock_probe_encode_and_answer_refuse_invalid_values);
    RUN_TEST(clock_probe_exchange_feeds_the_offset_estimator);
    RUN_TEST(session_welcome_round_trips_with_golden_bytes);
    RUN_TEST(session_welcome_decode_rejects_every_malformed_payload);
    RUN_TEST(session_welcome_encode_refuses_invalid_values_without_writing);
    RUN_TEST(voice_relay_round_trips_with_golden_bytes);
    RUN_TEST(voice_relay_decode_rejects_every_malformed_payload);
    RUN_TEST(voice_relay_encode_refuses_invalid_values_without_writing);
    RUN_TEST(voice_mute_round_trips_with_golden_bytes);
    RUN_TEST(voice_mute_decode_rejects_every_malformed_payload);
    RUN_TEST(voice_mute_encode_refuses_invalid_values_without_writing);
TEST_MAIN_END()
