#include <physics/physics_sync.h>
#include <string.h>

#define PHYSICS_SYNC_MAGIC 0x4e595350u
#define PHYSICS_SYNC_CORRECTION_MAGIC 0x504e5350u

static void put_u32(u8 *p, u32 v)
{
    for (u32 i = 0; i < 4u; i++) {
        p[i] = (u8)(v >> (8u * i));
    }
}

static u32 get_u32(const u8 *p)
{
    u32 v = 0;
    for (u32 i = 0; i < 4u; i++) {
        v |= (u32)p[i] << (8u * i);
    }
    return v;
}

bool physics_sync_encode_report(u32 tick, u64 hash, u8 *buffer, usize capacity)
{
    if (!buffer || capacity < PHYSICS_SYNC_REPORT_BYTES) {
        return false;
    }
    put_u32(buffer, PHYSICS_SYNC_MAGIC);
    put_u32(buffer + 4, tick);
    put_u32(buffer + 8, (u32)hash);
    put_u32(buffer + 12, (u32)(hash >> 32));
    return true;
}

bool physics_sync_decode_report(const u8 *data, usize size, u32 *out_tick, u64 *out_hash)
{
    if (!data || size != PHYSICS_SYNC_REPORT_BYTES || get_u32(data) != PHYSICS_SYNC_MAGIC) {
        return false;
    }
    if (out_tick) {
        *out_tick = get_u32(data + 4);
    }
    if (out_hash) {
        *out_hash = (u64)get_u32(data + 8) | ((u64)get_u32(data + 12) << 32);
    }
    return true;
}

void physics_sync_init(PhysicsSyncTracker *tracker)
{
    memset(tracker, 0, sizeof(*tracker));
}

bool physics_sync_record(PhysicsSyncTracker *tracker, u32 tick, u64 hash)
{
    if (tracker->has_record && tick <= tracker->last_tick) {
        return false;
    }
    u32 slot = tick % PHYSICS_SYNC_HISTORY;
    tracker->ticks[slot] = tick;
    tracker->hashes[slot] = hash;
    tracker->valid[slot] = true;
    tracker->last_tick = tick;
    tracker->has_record = true;
    return true;
}

PhysicsSyncVerdict physics_sync_check(PhysicsSyncTracker *tracker, u32 tick, u64 remote_hash)
{
    u32 slot = tick % PHYSICS_SYNC_HISTORY;
    if (!tracker->valid[slot] || tracker->ticks[slot] != tick) {
        return PHYSICS_SYNC_UNKNOWN;
    }
    if (tracker->hashes[slot] == remote_hash) {
        return PHYSICS_SYNC_MATCH;
    }
    if (!tracker->desynced || tick < tracker->first_desync_tick) {
        tracker->first_desync_tick = tick;
    }
    tracker->desynced = true;
    return PHYSICS_SYNC_DESYNC;
}

bool physics_sync_desynced(const PhysicsSyncTracker *tracker, u32 *out_first_tick)
{
    if (tracker->desynced && out_first_tick) {
        *out_first_tick = tracker->first_desync_tick;
    }
    return tracker->desynced;
}

static u32 payload_checksum(const u8 *data, usize size)
{
    u32 h = 2166136261u;
    for (usize i = 0; i < size; i++) {
        h ^= data[i];
        h *= 16777619u;
    }
    return h;
}

usize physics_sync_correction_size(const PhysicsWorld *pw)
{
    return PHYSICS_SYNC_CORRECTION_HEADER_BYTES + physics_snapshot_size(pw);
}

bool physics_sync_encode_correction(PhysicsWorld *pw, u32 tick, u8 *buffer, usize capacity,
                                    usize *out_size)
{
    usize payload = physics_snapshot_size(pw);
    usize need = PHYSICS_SYNC_CORRECTION_HEADER_BYTES + payload;
    if (out_size) {
        *out_size = need;
    }
    if (!buffer || capacity < need) {
        return false;
    }
    u8 *body = buffer + PHYSICS_SYNC_CORRECTION_HEADER_BYTES;
    (void)physics_snapshot_save(pw, body, payload, NULL);
    put_u32(buffer, PHYSICS_SYNC_CORRECTION_MAGIC);
    put_u32(buffer + 4, tick);
    put_u32(buffer + 8, (u32)payload);
    put_u32(buffer + 12, payload_checksum(body, payload));
    return true;
}

bool physics_sync_apply_correction(PhysicsSyncTracker *tracker, PhysicsWorld *pw, const u8 *data,
                                   usize size, u32 *out_tick)
{
    if (!data || size < PHYSICS_SYNC_CORRECTION_HEADER_BYTES ||
        get_u32(data) != PHYSICS_SYNC_CORRECTION_MAGIC) {
        return false;
    }
    usize payload = size - PHYSICS_SYNC_CORRECTION_HEADER_BYTES;
    const u8 *body = data + PHYSICS_SYNC_CORRECTION_HEADER_BYTES;
    if (get_u32(data + 8) != payload || get_u32(data + 12) != payload_checksum(body, payload)) {
        return false;
    }
    if (!physics_snapshot_restore(pw, body, payload)) {
        return false;
    }
    u32 tick = get_u32(data + 4);
    physics_sync_init(tracker);
    (void)physics_sync_record(tracker, tick, physics_state_hash(pw));
    if (out_tick) {
        *out_tick = tick;
    }
    return true;
}
