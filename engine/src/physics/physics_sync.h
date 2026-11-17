#pragma once
#include <physics/physics.h>

/* Desync detection between peers that step the same physics world. Each peer
 * records its local state hash per tick and checks hashes reported by the
 * other side. Nothing here moves state; it only finds the first tick where
 * the worlds differ.
 *
 * Report layout, little-endian, 16 bytes:
 *   magic u32 = 0x4e595350 ("PSYN"), tick u32, hash u64
 *
 * Correction layout, little-endian: a 16-byte header followed by a
 * physics_snapshot_save() payload taken at that tick.
 *   magic u32 = 0x504e5350 ("PSNP"), tick u32, payload bytes u32,
 *   FNV-1a 32 checksum of the payload u32
 * The authoritative peer sends a correction after a DESYNC; the other peer
 * restores it and restarts its hash history from that tick.
 *
 * Delta correction layout, little-endian: a 28-byte header followed by runs.
 *   magic u32 = 0x444e5350 ("PSND"), tick u32, baseline tick u32,
 *   baseline bytes u32, FNV-1a 32 of the baseline u32,
 *   target bytes u32, FNV-1a 32 of the target u32
 *   run: offset u32, length u32, length bytes
 * The baseline is a snapshot both peers already hold. It is read as if
 * zero-extended (or truncated) to the target size, and each run overwrites
 * target bytes. Runs are non-empty, ascending, non-overlapping and inside
 * the target. */

#define PHYSICS_SYNC_REPORT_BYTES 16u
#define PHYSICS_SYNC_HISTORY 64u
#define PHYSICS_SYNC_CORRECTION_HEADER_BYTES 16u
#define PHYSICS_SYNC_DELTA_HEADER_BYTES 28u

typedef enum PhysicsSyncVerdict {
    PHYSICS_SYNC_MATCH = 0,
    PHYSICS_SYNC_DESYNC,
    PHYSICS_SYNC_UNKNOWN
} PhysicsSyncVerdict;

/* A snapshot one peer is known to hold. The sender keeps the last snapshot
 * it put in a correction to a peer; it is confirmed once that peer reports
 * a matching hash for a tick at or after it. The receiver keeps the last
 * snapshot it restored. bytes is owned. */
typedef struct PhysicsSyncBaseline {
    u8 *bytes;
    usize size;
    u32 tick;
    bool confirmed;
} PhysicsSyncBaseline;

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
/* Header plus the world's current snapshot size. */
usize physics_sync_correction_size(const PhysicsWorld *pw);
/* *out_size always receives the required byte count when non-NULL; returns
 * false and leaves the buffer untouched when capacity is too small. */
bool physics_sync_encode_correction(PhysicsWorld *pw, u32 tick, u8 *buffer, usize capacity,
                                    usize *out_size);
/* Validates magic, exact length and checksum, then restores the snapshot.
 * On success the tracker is reset and holds (tick, restored hash), so the
 * desync latch clears. On any failure the world, the tracker and *out_tick
 * are unchanged. */
bool physics_sync_apply_correction(PhysicsSyncTracker *tracker, PhysicsWorld *pw, const u8 *data,
                                   usize size, u32 *out_tick);
/* Byte-level delta between two snapshots. baseline may be NULL only when
 * baseline_size is 0. *out_size receives the required byte count whenever
 * the inputs are valid; returns false and leaves the buffer untouched when
 * capacity is too small. Unchanged gaps of up to 8 bytes are folded into
 * the surrounding run because a new run header costs 8 bytes. */
bool physics_sync_encode_delta(u32 tick, u32 baseline_tick, const u8 *baseline,
                               usize baseline_size, const u8 *target, usize target_size,
                               u8 *buffer, usize capacity, usize *out_size);
/* Reads the two ticks so the receiver can pick the matching baseline.
 * Outputs are untouched on failure. */
bool physics_sync_delta_ticks(const u8 *data, usize size, u32 *out_tick, u32 *out_baseline_tick);
/* Rebuilds the target snapshot into target. Checks the magic, the baseline
 * checksum, the capacity, every run and the target checksum. The baseline
 * bytes field is informational; the checksum already depends on the length. On
 * failure *out_target_size and *out_tick are unchanged and the contents of
 * target are unspecified. */
bool physics_sync_decode_delta(const u8 *baseline, usize baseline_size, const u8 *data,
                               usize size, u8 *target, usize target_capacity,
                               usize *out_target_size, u32 *out_tick);
/* Decodes into scratch, then restores it like physics_sync_apply_correction,
 * with the same guarantee: on failure the world, the tracker and *out_tick
 * are unchanged. */
bool physics_sync_apply_delta(PhysicsSyncTracker *tracker, PhysicsWorld *pw, const u8 *baseline,
                              usize baseline_size, const u8 *data, usize size, u8 *scratch,
                              usize scratch_capacity, u32 *out_tick);
/* Validates a full correction (magic, length, checksum) and points
 * *out_payload at its snapshot. Outputs are untouched on failure. */
bool physics_sync_correction_payload(const u8 *data, usize size, const u8 **out_payload,
                                     usize *out_payload_size);

void physics_sync_baseline_init(PhysicsSyncBaseline *baseline);
void physics_sync_baseline_release(PhysicsSyncBaseline *baseline);
/* Copies the snapshot and clears the confirmation. Returns false and leaves
 * the baseline empty when allocation fails. */
bool physics_sync_baseline_store(PhysicsSyncBaseline *baseline, u32 tick, const u8 *snapshot,
                                 usize size);
/* Confirms a held baseline when tick is at or after its tick. */
void physics_sync_baseline_confirm(PhysicsSyncBaseline *baseline, u32 tick);
/* Encodes a delta against a confirmed baseline when that is strictly
 * smaller than a full correction, otherwise a full correction. *out_size
 * receives the required byte count; *out_delta says which kind was chosen.
 * Returns false and leaves the buffer untouched when capacity is too small.
 * The baseline itself is not changed: store the snapshot after the packet
 * is actually sent. */
bool physics_sync_baseline_encode(const PhysicsSyncBaseline *baseline, u32 tick,
                                  const u8 *snapshot, usize size, u8 *buffer, usize capacity,
                                  usize *out_size, bool *out_delta);
/* Applies a full or a delta correction, chosen by magic. A delta is decoded
 * against held; its target is bounded by what the world can hold before
 * any allocation. On success the restored snapshot becomes held. On any
 * failure the world, the tracker, held and *out_tick are unchanged. */
bool physics_sync_apply_received(PhysicsSyncTracker *tracker, PhysicsWorld *pw,
                                 PhysicsSyncBaseline *held, const u8 *data, usize size,
                                 u32 *out_tick);
/* *out_first_tick is written only when a desync has been seen. */
bool physics_sync_desynced(const PhysicsSyncTracker *tracker, u32 *out_first_tick);
