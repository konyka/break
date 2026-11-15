#pragma once
#include <physics/physics.h>

/* Input recording for physics replay. A recording is the list of inputs
 * (impulses and steps) applied to a world after a snapshot, plus the state
 * hash after every step. Replaying it on a world restored from that snapshot
 * reports the first step whose hash differs. The caller owns all storage.
 *
 * Encoded layout, little-endian:
 *   header  : "PRPL" magic (u32 0x4c505250), version u32 = 1, count u32
 *   record  : op u32, body index u32, body generation u32, 3 x f32 bits,
 *             hash_after u64 (STEP only; 0 for IMPULSE)          = 32 bytes */

#define PHYSICS_REPLAY_HEADER_BYTES 12u
#define PHYSICS_REPLAY_RECORD_BYTES 32u

typedef enum PhysicsReplayOp {
    PHYSICS_REPLAY_OP_STEP = 1,
    PHYSICS_REPLAY_OP_IMPULSE = 2
} PhysicsReplayOp;

typedef struct PhysicsReplayRecord {
    u32 op;
    PhysicsBodyHandle body;
    f32 value[3]; /* STEP: value[0] = dt; IMPULSE: impulse vector */
    u64 hash_after;
} PhysicsReplayRecord;

typedef struct PhysicsReplay {
    PhysicsReplayRecord *records;
    u32 count;
    u32 capacity;
} PhysicsReplay;

typedef enum PhysicsReplayResult {
    PHYSICS_REPLAY_OK = 0,
    PHYSICS_REPLAY_DIVERGED,
    PHYSICS_REPLAY_INVALID
} PhysicsReplayResult;

bool physics_replay_init(PhysicsReplay *replay, PhysicsReplayRecord *storage, u32 capacity);
/* Applies and records. Returns false (world unchanged, nothing recorded) for
 * a full log, an unresolvable body or a non-finite impulse. */
bool physics_replay_impulse(PhysicsReplay *replay, PhysicsWorld *pw, PhysicsBodyHandle body,
                            Vec3 impulse);
/* Steps and records the state hash after the step. Returns false (no step)
 * for a full log or a non-finite or non-positive dt. */
bool physics_replay_step(PhysicsReplay *replay, PhysicsWorld *pw, f32 dt);
/* *out_size always receives the required byte count; returns false and
 * leaves the buffer untouched when capacity is too small. */
bool physics_replay_encode(const PhysicsReplay *replay, u8 *buffer, usize capacity,
                           usize *out_size);
/* Validates magic, version, exact length, count against capacity, every op
 * and every float. On failure the replay is unchanged. */
bool physics_replay_decode(PhysicsReplay *replay, const u8 *data, usize size);
/* Re-applies every record to pw. Stops at the first step whose hash differs
 * and stores its record index in *out_divergent (UINT32_MAX when none). */
PhysicsReplayResult physics_replay_run(const PhysicsReplay *replay, PhysicsWorld *pw,
                                       u32 *out_divergent);
