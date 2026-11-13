#pragma once

/* Optional, default-off snapshot channel for the real application.
 *
 * The application never trusts a network peer with authority over its
 * simulation. This module therefore has two halves and no shared mutable
 * state with the level: a fixed, versioned, little-endian snapshot the
 * application publishes, and a decoder that turns a peer message into at
 * most diagnostic data. The decoder cannot produce a level mutation, which
 * is why the outbound and inbound paths are separate types instead of one
 * bidirectional session handle.
 */

#include <core/types.h>
#include <runtime/runtime_types.h>

#include <stddef.h>

#define CORE_APP_SNAPSHOT_MAGIC 0x43534e50u /* "CSNP" */
#define CORE_APP_SNAPSHOT_VERSION 1u
/* Wire layout, all little-endian, 32-byte header:
 *   [0]  u32 magic "CSNP"
 *   [4]  u16 version
 *   [6]  u16 header_bytes
 *   [8]  u64 frame_id
 *   [16] u64 level_generation
 *   [24] u32 schema_hash
 *   [28] u32 entity_count
 * then entity_count * 24 bytes of (u32 index, u32 generation, f32 x, f32 y,
 * f32 z, u32 flags). */
#define CORE_APP_SNAPSHOT_HEADER_BYTES 32u
#define CORE_APP_SNAPSHOT_ENTITY_BYTES 24u
#define CORE_APP_SNAPSHOT_MAX_ENTITIES 64u
#define CORE_APP_SNAPSHOT_MAX_BYTES \
    (CORE_APP_SNAPSHOT_HEADER_BYTES + \
     CORE_APP_SNAPSHOT_MAX_ENTITIES * CORE_APP_SNAPSHOT_ENTITY_BYTES)

#define CORE_APP_SNAPSHOT_MESSAGE_ID 0x4001u
#define CORE_APP_SNAPSHOT_PROTOCOL_VERSION 1u

typedef enum CoreAppSnapshotOutcome {
    CORE_APP_SNAPSHOT_OK = 0,
    CORE_APP_SNAPSHOT_INVALID,
    CORE_APP_SNAPSHOT_BAD_MAGIC,
    CORE_APP_SNAPSHOT_BAD_VERSION,
    CORE_APP_SNAPSHOT_TRUNCATED,
    CORE_APP_SNAPSHOT_OVER_LIMIT
} CoreAppSnapshotOutcome;

/* One entity as published. index and generation together identify an entity
 * across levels; a stale pair never matches the live level. */
typedef struct CoreAppSnapshotEntity {
    u32 index;
    u32 generation;
    f32 x;
    f32 y;
    f32 z;
    u32 flags;
} CoreAppSnapshotEntity;

typedef struct CoreAppSnapshot {
    u32 schema_hash;
    u64 frame_id;
    u64 level_generation;
    u32 entity_count;
    CoreAppSnapshotEntity entities[CORE_APP_SNAPSHOT_MAX_ENTITIES];
} CoreAppSnapshot;

/* Fills a snapshot from POD values only. Returns INVALID when the entity
 * count exceeds the fixed capacity; the caller keeps the previous snapshot. */
CoreAppSnapshotOutcome core_app_snapshot_build(CoreAppSnapshot *out, u64 frame_id,
                                               u64 level_generation, u32 schema_hash,
                                               const CoreAppSnapshotEntity *entities,
                                               u32 entity_count);

/* Encodes into a caller buffer. Sets *out_size to the exact byte count on OK
 * and leaves the buffer untouched on failure. */
CoreAppSnapshotOutcome core_app_snapshot_encode(const CoreAppSnapshot *snapshot,
                                                u8 *out_buffer, size_t capacity,
                                                size_t *out_size);

/* Decodes a peer payload. Never writes outside `out`, never allocates, and
 * reports TRUNCATED/OVER_LIMIT instead of trusting a declared count. */
CoreAppSnapshotOutcome core_app_snapshot_decode(const u8 *payload, size_t size,
                                                CoreAppSnapshot *out);

/* Schema hash over the payload field layout, so a peer with a different
 * layout is rejected before any field is interpreted. */
u32 core_app_snapshot_schema_hash(void);

/* Inbound authority firewall.
 *
 * A decoded peer snapshot is diagnostic data. Feeding it to this function is
 * the only way the application consumes it, and the function counts what it
 * rejected. It never returns a value the simulation applies. */
typedef struct CoreAppSnapshotInbox {
    u64 accepted_snapshots;
    u64 rejected_unknown_message;
    u64 rejected_unauthenticated;
    u64 rejected_schema;
    u64 rejected_stale_level;
    u64 overloads;
    bool authenticated;
    u16 admission_message_id;
    u32 peer_schema_hash;
} CoreAppSnapshotInbox;

void core_app_snapshot_inbox_init(CoreAppSnapshotInbox *inbox, bool authenticated,
                                  u16 admission_message_id, u32 peer_schema_hash);

typedef enum CoreAppSnapshotAdmission {
    CORE_APP_SNAPSHOT_ADMITTED = 0,
    CORE_APP_SNAPSHOT_REJECTED_UNKNOWN_MESSAGE,
    CORE_APP_SNAPSHOT_REJECTED_UNAUTHENTICATED,
    CORE_APP_SNAPSHOT_REJECTED_SCHEMA,
    CORE_APP_SNAPSHOT_REJECTED_STALE_LEVEL
} CoreAppSnapshotAdmission;

/* Admits a peer message for diagnostics only. level_generation is the live
 * value the application owns; a snapshot naming any other generation is
 * stale and dropped. */
CoreAppSnapshotAdmission core_app_snapshot_admit(CoreAppSnapshotInbox *inbox,
                                                 u16 message_id,
                                                 const CoreAppSnapshot *snapshot,
                                                 u64 live_level_generation);

/* Records one outbound enqueue attempt. Over capacity is counted and the
 * snapshot is dropped; the caller's frame is never blocked or rolled back. */
#define CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY 8u
typedef struct CoreAppSnapshotOutbox {
    CoreAppSnapshot pending[CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY];
    u64 enqueued;
    u64 dropped;
    u32 head;
    u32 count;
} CoreAppSnapshotOutbox;

void core_app_snapshot_outbox_init(CoreAppSnapshotOutbox *outbox);
CoreAppSnapshotOutcome core_app_snapshot_outbox_push(CoreAppSnapshotOutbox *outbox,
                                                     const CoreAppSnapshot *snapshot);
/* Pops the oldest snapshot. Returns false when the outbox is empty. */
bool core_app_snapshot_outbox_pop(CoreAppSnapshotOutbox *outbox, CoreAppSnapshot *out);
