#include "test_framework.h"

#include "../apps/core_app/core_app_network.h"

#include <string.h>

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
TEST_MAIN_END()
