#include "core_app_network.h"

#include <string.h>

/* All integers are little-endian on the wire regardless of host byte order,
 * because a snapshot crosses a network boundary where the peer's order is
 * unknown. Encoding and decoding are the only places that touch byte order. */

static void put_u16(u8 *out, u16 value) {
    out[0] = (u8)(value & 0xFFu);
    out[1] = (u8)((value >> 8) & 0xFFu);
}

static void put_u32(u8 *out, u32 value) {
    out[0] = (u8)(value & 0xFFu);
    out[1] = (u8)((value >> 8) & 0xFFu);
    out[2] = (u8)((value >> 16) & 0xFFu);
    out[3] = (u8)((value >> 24) & 0xFFu);
}

static void put_u64(u8 *out, u64 value) {
    for (u32 i = 0u; i < 8u; ++i) out[i] = (u8)((value >> (8u * i)) & 0xFFu);
}

static u16 get_u16(const u8 *in) {
    return (u16)((u16)in[0] | ((u16)in[1] << 8));
}

static u32 get_u32(const u8 *in) {
    return (u32)in[0] | ((u32)in[1] << 8) | ((u32)in[2] << 16) | ((u32)in[3] << 24);
}

static u64 get_u64(const u8 *in) {
    u64 value = 0u;
    for (u32 i = 0u; i < 8u; ++i) value |= (u64)in[i] << (8u * i);
    return value;
}

static void put_f32(u8 *out, f32 value) {
    u32 bits;
    memcpy(&bits, &value, sizeof(bits));
    put_u32(out, bits);
}

static f32 get_f32(const u8 *in) {
    u32 bits = get_u32(in);
    f32 value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

u32 core_app_snapshot_schema_hash(void) {
    /* FNV-1a over the field layout. A peer built from a different layout
     * produces a different hash, so a mismatch is rejected before any field
     * is interpreted. */
    static const char k_layout[] =
        "CSNP1|frame:u64|generation:u64|schema:u32|count:u32|"
        "entity:index:u32|generation:u32|x:f32|y:f32|z:f32|flags:u32";
    u32 hash = 2166136261u;
    for (const char *p = k_layout; *p != '\0'; ++p) {
        hash ^= (u32)(u8)*p;
        hash *= 16777619u;
    }
    return hash;
}

CoreAppSnapshotOutcome core_app_snapshot_build(CoreAppSnapshot *out, u64 frame_id,
                                               u64 level_generation, u32 schema_hash,
                                               const CoreAppSnapshotEntity *entities,
                                               u32 entity_count) {
    if (!out) return CORE_APP_SNAPSHOT_INVALID;
    if (entity_count > CORE_APP_SNAPSHOT_MAX_ENTITIES) return CORE_APP_SNAPSHOT_OVER_LIMIT;
    if (entity_count != 0u && !entities) return CORE_APP_SNAPSHOT_INVALID;
    memset(out, 0, sizeof(*out));
    out->frame_id = frame_id;
    out->level_generation = level_generation;
    out->schema_hash = schema_hash;
    out->entity_count = entity_count;
    if (entity_count != 0u) {
        memcpy(out->entities, entities, (size_t)entity_count * sizeof(*entities));
    }
    return CORE_APP_SNAPSHOT_OK;
}

CoreAppSnapshotOutcome core_app_snapshot_encode(const CoreAppSnapshot *snapshot,
                                                u8 *out_buffer, size_t capacity,
                                                size_t *out_size) {
    if (!snapshot || !out_size) return CORE_APP_SNAPSHOT_INVALID;
    if (snapshot->entity_count > CORE_APP_SNAPSHOT_MAX_ENTITIES) {
        return CORE_APP_SNAPSHOT_OVER_LIMIT;
    }
    size_t needed = CORE_APP_SNAPSHOT_HEADER_BYTES +
                    (size_t)snapshot->entity_count * CORE_APP_SNAPSHOT_ENTITY_BYTES;
    if (!out_buffer || capacity < needed) return CORE_APP_SNAPSHOT_OVER_LIMIT;
    u8 *cursor = out_buffer;
    put_u32(cursor, CORE_APP_SNAPSHOT_MAGIC);
    put_u16(cursor + 4u, (u16)CORE_APP_SNAPSHOT_VERSION);
    put_u16(cursor + 6u, (u16)CORE_APP_SNAPSHOT_HEADER_BYTES);
    put_u64(cursor + 8u, snapshot->frame_id);
    put_u64(cursor + 16u, snapshot->level_generation);
    put_u32(cursor + 24u, snapshot->schema_hash);
    put_u32(cursor + 28u, snapshot->entity_count);
    cursor += CORE_APP_SNAPSHOT_HEADER_BYTES;
    for (u32 i = 0u; i < snapshot->entity_count; ++i) {
        const CoreAppSnapshotEntity *entity = &snapshot->entities[i];
        put_u32(cursor, entity->index);
        put_u32(cursor + 4u, entity->generation);
        put_f32(cursor + 8u, entity->x);
        put_f32(cursor + 12u, entity->y);
        put_f32(cursor + 16u, entity->z);
        put_u32(cursor + 20u, entity->flags);
        cursor += CORE_APP_SNAPSHOT_ENTITY_BYTES;
    }
    *out_size = needed;
    return CORE_APP_SNAPSHOT_OK;
}

CoreAppSnapshotOutcome core_app_snapshot_decode(const u8 *payload, size_t size,
                                                CoreAppSnapshot *out) {
    if (!payload || !out) return CORE_APP_SNAPSHOT_INVALID;
    if (size < CORE_APP_SNAPSHOT_HEADER_BYTES) return CORE_APP_SNAPSHOT_TRUNCATED;
    if (get_u32(payload) != CORE_APP_SNAPSHOT_MAGIC) return CORE_APP_SNAPSHOT_BAD_MAGIC;
    if (get_u16(payload + 4u) != (u16)CORE_APP_SNAPSHOT_VERSION) {
        return CORE_APP_SNAPSHOT_BAD_VERSION;
    }
    if (get_u16(payload + 6u) != (u16)CORE_APP_SNAPSHOT_HEADER_BYTES) {
        return CORE_APP_SNAPSHOT_BAD_VERSION;
    }
    u32 count = get_u32(payload + 28u);
    if (count > CORE_APP_SNAPSHOT_MAX_ENTITIES) return CORE_APP_SNAPSHOT_OVER_LIMIT;
    size_t needed = CORE_APP_SNAPSHOT_HEADER_BYTES +
                    (size_t)count * CORE_APP_SNAPSHOT_ENTITY_BYTES;
    if (size < needed) return CORE_APP_SNAPSHOT_TRUNCATED;
    memset(out, 0, sizeof(*out));
    out->frame_id = get_u64(payload + 8u);
    out->level_generation = get_u64(payload + 16u);
    out->schema_hash = get_u32(payload + 24u);
    out->entity_count = count;
    const u8 *cursor = payload + CORE_APP_SNAPSHOT_HEADER_BYTES;
    for (u32 i = 0u; i < count; ++i) {
        out->entities[i].index = get_u32(cursor);
        out->entities[i].generation = get_u32(cursor + 4u);
        out->entities[i].x = get_f32(cursor + 8u);
        out->entities[i].y = get_f32(cursor + 12u);
        out->entities[i].z = get_f32(cursor + 16u);
        out->entities[i].flags = get_u32(cursor + 20u);
        cursor += CORE_APP_SNAPSHOT_ENTITY_BYTES;
    }
    return CORE_APP_SNAPSHOT_OK;
}

void core_app_snapshot_inbox_init(CoreAppSnapshotInbox *inbox, bool authenticated,
                                  u16 admission_message_id, u32 peer_schema_hash) {
    if (!inbox) return;
    memset(inbox, 0, sizeof(*inbox));
    inbox->authenticated = authenticated;
    inbox->admission_message_id = admission_message_id;
    inbox->peer_schema_hash = peer_schema_hash;
}

CoreAppSnapshotAdmission core_app_snapshot_admit(CoreAppSnapshotInbox *inbox,
                                                 u16 message_id,
                                                 const CoreAppSnapshot *snapshot,
                                                 u64 live_level_generation) {
    if (!inbox || !snapshot) return CORE_APP_SNAPSHOT_REJECTED_UNKNOWN_MESSAGE;
    if (!inbox->authenticated) {
        inbox->rejected_unauthenticated++;
        return CORE_APP_SNAPSHOT_REJECTED_UNAUTHENTICATED;
    }
    if (message_id != inbox->admission_message_id) {
        inbox->rejected_unknown_message++;
        return CORE_APP_SNAPSHOT_REJECTED_UNKNOWN_MESSAGE;
    }
    if (snapshot->schema_hash != inbox->peer_schema_hash) {
        inbox->rejected_schema++;
        return CORE_APP_SNAPSHOT_REJECTED_SCHEMA;
    }
    if (snapshot->level_generation != live_level_generation) {
        inbox->rejected_stale_level++;
        return CORE_APP_SNAPSHOT_REJECTED_STALE_LEVEL;
    }
    inbox->accepted_snapshots++;
    return CORE_APP_SNAPSHOT_ADMITTED;
}

void core_app_snapshot_outbox_init(CoreAppSnapshotOutbox *outbox) {
    if (!outbox) return;
    memset(outbox, 0, sizeof(*outbox));
}

CoreAppSnapshotOutcome core_app_snapshot_outbox_push(CoreAppSnapshotOutbox *outbox,
                                                     const CoreAppSnapshot *snapshot) {
    if (!outbox || !snapshot) return CORE_APP_SNAPSHOT_INVALID;
    if (outbox->count >= CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY) {
        outbox->dropped++;
        return CORE_APP_SNAPSHOT_OVER_LIMIT;
    }
    u32 tail = (outbox->head + outbox->count) % CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY;
    outbox->pending[tail] = *snapshot;
    outbox->count++;
    outbox->enqueued++;
    return CORE_APP_SNAPSHOT_OK;
}

bool core_app_snapshot_outbox_pop(CoreAppSnapshotOutbox *outbox, CoreAppSnapshot *out) {
    if (!outbox || !out) return false;
    if (outbox->count == 0u) return false;
    if (out) *out = outbox->pending[outbox->head];
    outbox->head = (outbox->head + 1u) % CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY;
    outbox->count--;
    return true;
}
