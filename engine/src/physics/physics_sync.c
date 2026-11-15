#include <physics/physics_sync.h>
#include <string.h>

#define PHYSICS_SYNC_MAGIC 0x4e595350u

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
