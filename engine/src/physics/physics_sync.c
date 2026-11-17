#include <physics/physics_sync.h>
#include <stdlib.h>
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

bool physics_sync_correction_payload(const u8 *data, usize size, const u8 **out_payload,
                                     usize *out_payload_size)
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
    if (out_payload) {
        *out_payload = body;
    }
    if (out_payload_size) {
        *out_payload_size = payload;
    }
    return true;
}

bool physics_sync_apply_correction(PhysicsSyncTracker *tracker, PhysicsWorld *pw, const u8 *data,
                                   usize size, u32 *out_tick)
{
    const u8 *body = NULL;
    usize payload = 0;
    if (!physics_sync_correction_payload(data, size, &body, &payload) ||
        !physics_snapshot_restore(pw, body, payload)) {
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

#define PHYSICS_SYNC_DELTA_MAGIC 0x444e5350u
#define PHYSICS_SYNC_DELTA_RUN_HEADER_BYTES 8u

static u8 baseline_byte(const u8 *baseline, usize baseline_size, usize i)
{
    return i < baseline_size ? baseline[i] : 0u;
}

/* Walks the changed runs once. With out == NULL it only counts bytes. */
static usize delta_runs(const u8 *baseline, usize baseline_size, const u8 *target,
                        usize target_size, u8 *out)
{
    usize total = 0;
    usize i = 0;
    while (i < target_size) {
        if (target[i] == baseline_byte(baseline, baseline_size, i)) {
            i++;
            continue;
        }
        usize start = i;
        usize end = i + 1u;
        usize scan = end;
        while (scan < target_size && scan - end <= PHYSICS_SYNC_DELTA_RUN_HEADER_BYTES) {
            if (target[scan] != baseline_byte(baseline, baseline_size, scan)) {
                end = scan + 1u;
            }
            scan++;
        }
        usize len = end - start;
        if (out) {
            put_u32(out + total, (u32)start);
            put_u32(out + total + 4, (u32)len);
            memcpy(out + total + PHYSICS_SYNC_DELTA_RUN_HEADER_BYTES, target + start, len);
        }
        total += PHYSICS_SYNC_DELTA_RUN_HEADER_BYTES + len;
        i = end;
    }
    return total;
}

bool physics_sync_encode_delta(u32 tick, u32 baseline_tick, const u8 *baseline,
                               usize baseline_size, const u8 *target, usize target_size,
                               u8 *buffer, usize capacity, usize *out_size)
{
    if ((!baseline && baseline_size) || !target || baseline_size > 0xffffffffu ||
        target_size > 0xffffffffu) {
        return false;
    }
    usize need = PHYSICS_SYNC_DELTA_HEADER_BYTES +
                 delta_runs(baseline, baseline_size, target, target_size, NULL);
    if (out_size) {
        *out_size = need;
    }
    if (!buffer || capacity < need) {
        return false;
    }
    put_u32(buffer, PHYSICS_SYNC_DELTA_MAGIC);
    put_u32(buffer + 4, tick);
    put_u32(buffer + 8, baseline_tick);
    put_u32(buffer + 12, (u32)baseline_size);
    put_u32(buffer + 16, payload_checksum(baseline, baseline_size));
    put_u32(buffer + 20, (u32)target_size);
    put_u32(buffer + 24, payload_checksum(target, target_size));
    (void)delta_runs(baseline, baseline_size, target, target_size,
                     buffer + PHYSICS_SYNC_DELTA_HEADER_BYTES);
    return true;
}

bool physics_sync_delta_ticks(const u8 *data, usize size, u32 *out_tick, u32 *out_baseline_tick)
{
    if (!data || size < PHYSICS_SYNC_DELTA_HEADER_BYTES ||
        get_u32(data) != PHYSICS_SYNC_DELTA_MAGIC) {
        return false;
    }
    if (out_tick) {
        *out_tick = get_u32(data + 4);
    }
    if (out_baseline_tick) {
        *out_baseline_tick = get_u32(data + 8);
    }
    return true;
}

bool physics_sync_decode_delta(const u8 *baseline, usize baseline_size, const u8 *data,
                               usize size, u8 *target, usize target_capacity,
                               usize *out_target_size, u32 *out_tick)
{
    if (!physics_sync_delta_ticks(data, size, NULL, NULL) || !target ||
        (!baseline && baseline_size) ||
        get_u32(data + 16) != payload_checksum(baseline, baseline_size)) {
        return false;
    }
    usize target_size = get_u32(data + 20);
    if (target_size > target_capacity) {
        return false;
    }
    usize keep = baseline_size < target_size ? baseline_size : target_size;
    if (keep) {
        memcpy(target, baseline, keep);
    }
    memset(target + keep, 0, target_size - keep);
    usize at = PHYSICS_SYNC_DELTA_HEADER_BYTES;
    u64 prev_end = 0;
    while (at < size) {
        if (size - at < PHYSICS_SYNC_DELTA_RUN_HEADER_BYTES) {
            return false;
        }
        u64 offset = get_u32(data + at);
        u64 len = get_u32(data + at + 4);
        at += PHYSICS_SYNC_DELTA_RUN_HEADER_BYTES;
        if (len == 0 || offset < prev_end || offset + len > target_size || len > size - at) {
            return false;
        }
        memcpy(target + offset, data + at, (usize)len);
        at += (usize)len;
        prev_end = offset + len;
    }
    if (get_u32(data + 24) != payload_checksum(target, target_size)) {
        return false;
    }
    if (out_target_size) {
        *out_target_size = target_size;
    }
    if (out_tick) {
        *out_tick = get_u32(data + 4);
    }
    return true;
}

bool physics_sync_apply_delta(PhysicsSyncTracker *tracker, PhysicsWorld *pw, const u8 *baseline,
                              usize baseline_size, const u8 *data, usize size, u8 *scratch,
                              usize scratch_capacity, u32 *out_tick)
{
    usize target_size = 0;
    u32 tick = 0;
    if (!physics_sync_decode_delta(baseline, baseline_size, data, size, scratch, scratch_capacity,
                                   &target_size, &tick) ||
        !physics_snapshot_restore(pw, scratch, target_size)) {
        return false;
    }
    physics_sync_init(tracker);
    (void)physics_sync_record(tracker, tick, physics_state_hash(pw));
    if (out_tick) {
        *out_tick = tick;
    }
    return true;
}

void physics_sync_baseline_init(PhysicsSyncBaseline *baseline)
{
    memset(baseline, 0, sizeof(*baseline));
}

void physics_sync_baseline_release(PhysicsSyncBaseline *baseline)
{
    free(baseline->bytes);
    physics_sync_baseline_init(baseline);
}

static void baseline_take(PhysicsSyncBaseline *baseline, u32 tick, u8 *bytes, usize size)
{
    free(baseline->bytes);
    baseline->bytes = bytes;
    baseline->size = size;
    baseline->tick = tick;
    baseline->confirmed = false;
}

bool physics_sync_baseline_store(PhysicsSyncBaseline *baseline, u32 tick, const u8 *snapshot,
                                 usize size)
{
    u8 *copy = snapshot && size ? (u8 *)malloc(size) : NULL;
    if (!copy) {
        physics_sync_baseline_release(baseline);
        return false;
    }
    memcpy(copy, snapshot, size);
    baseline_take(baseline, tick, copy, size);
    return true;
}

void physics_sync_baseline_confirm(PhysicsSyncBaseline *baseline, u32 tick)
{
    if (baseline->bytes && tick >= baseline->tick) {
        baseline->confirmed = true;
    }
}

bool physics_sync_baseline_encode(const PhysicsSyncBaseline *baseline, u32 tick,
                                  const u8 *snapshot, usize size, u8 *buffer, usize capacity,
                                  usize *out_size, bool *out_delta)
{
    if (!snapshot || size > 0xffffffffu - PHYSICS_SYNC_CORRECTION_HEADER_BYTES) {
        return false;
    }
    usize full = PHYSICS_SYNC_CORRECTION_HEADER_BYTES + size;
    usize delta = full;
    bool use_delta = baseline->confirmed &&
                     !physics_sync_encode_delta(tick, baseline->tick, baseline->bytes,
                                                baseline->size, snapshot, size, NULL, 0, &delta) &&
                     delta < full;
    usize need = use_delta ? delta : full;
    if (out_size) {
        *out_size = need;
    }
    if (out_delta) {
        *out_delta = use_delta;
    }
    if (!buffer || capacity < need) {
        return false;
    }
    if (use_delta) {
        return physics_sync_encode_delta(tick, baseline->tick, baseline->bytes, baseline->size,
                                         snapshot, size, buffer, capacity, NULL);
    }
    memcpy(buffer + PHYSICS_SYNC_CORRECTION_HEADER_BYTES, snapshot, size);
    put_u32(buffer, PHYSICS_SYNC_CORRECTION_MAGIC);
    put_u32(buffer + 4, tick);
    put_u32(buffer + 8, (u32)size);
    put_u32(buffer + 12, payload_checksum(snapshot, size));
    return true;
}

bool physics_sync_apply_received(PhysicsSyncTracker *tracker, PhysicsWorld *pw,
                                 PhysicsSyncBaseline *held, const u8 *data, usize size,
                                 u32 *out_tick)
{
    u8 *target = NULL;
    usize target_size = 0;
    u32 tick = 0;
    const u8 *body = NULL;
    if (physics_sync_correction_payload(data, size, &body, &target_size)) {
        target = (u8 *)malloc(target_size);
        if (!target) {
            return false;
        }
        memcpy(target, body, target_size);
        tick = get_u32(data + 4);
    } else if (physics_sync_delta_ticks(data, size, NULL, NULL)) {
        usize limit = physics_snapshot_size(pw) + (usize)(pw->capacity - pw->count) *
                                                       sizeof(*pw->bodies);
        usize want = get_u32(data + 20);
        target = want <= limit && want ? (u8 *)malloc(want) : NULL;
        if (!target || !physics_sync_decode_delta(held->bytes, held->size, data, size, target,
                                                  want, &target_size, &tick)) {
            free(target);
            return false;
        }
    } else {
        return false;
    }
    if (!physics_snapshot_restore(pw, target, target_size)) {
        free(target);
        return false;
    }
    baseline_take(held, tick, target, target_size);
    physics_sync_init(tracker);
    (void)physics_sync_record(tracker, tick, physics_state_hash(pw));
    if (out_tick) {
        *out_tick = tick;
    }
    return true;
}
