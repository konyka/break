#pragma once
#include <physics/physics.h>

/* Desync detection between peers that step the same physics world. Each peer
 * records its local state hash per tick and checks hashes reported by the
 * other side. Nothing here moves state; it only finds the first tick where
 * the worlds differ.
 *
 * Report layout, little-endian, 16 bytes:
 *   magic u32 = 0x4e595350 ("PSYN"), tick u32, hash u64 */

#define PHYSICS_SYNC_REPORT_BYTES 16u
#define PHYSICS_SYNC_HISTORY 64u

typedef enum PhysicsSyncVerdict {
    PHYSICS_SYNC_MATCH = 0,
    PHYSICS_SYNC_DESYNC,
    PHYSICS_SYNC_UNKNOWN
} PhysicsSyncVerdict;

typedef struct PhysicsSyncTracker {
    u32 ticks[PHYSICS_SYNC_HISTORY];
    u64 hashes[PHYSICS_SYNC_HISTORY];
    bool valid[PHYSICS_SYNC_HISTORY];
    u32 last_tick;
    u32 first_desync_tick;
    bool has_record;
    bool desynced;
} PhysicsSyncTracker;

bool physics_sync_encode_report(u32 tick, u64 hash, u8 *buffer, usize capacity);
/* Requires exactly PHYSICS_SYNC_REPORT_BYTES and the magic. Outputs are
 * untouched on failure. */
bool physics_sync_decode_report(const u8 *data, usize size, u32 *out_tick, u64 *out_hash);

void physics_sync_init(PhysicsSyncTracker *tracker);
/* Ticks must strictly increase; returns false and records nothing otherwise.
 * Only the newest PHYSICS_SYNC_HISTORY ticks are kept. */
bool physics_sync_record(PhysicsSyncTracker *tracker, u32 tick, u64 hash);
/* UNKNOWN when the tick is not in the local window. A DESYNC latches the
 * lowest desync tick seen until physics_sync_init. */
PhysicsSyncVerdict physics_sync_check(PhysicsSyncTracker *tracker, u32 tick, u64 remote_hash);
/* *out_first_tick is written only when a desync has been seen. */
bool physics_sync_desynced(const PhysicsSyncTracker *tracker, u32 *out_first_tick);
