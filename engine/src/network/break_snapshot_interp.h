#pragma once
/* Snapshot interpolation for remote entities.
 *
 * A client receives server snapshots of other entities at a fixed tick rate,
 * but late, unevenly and sometimes out of order. Drawing each snapshot as it
 * arrives makes remote entities stutter. Instead, the client draws them a
 * fixed delay behind its estimate of the server time and blends between the
 * two snapshots around that moment: position linearly, orientation by
 * quaternion slerp along the shorter arc.
 *
 * One BreakSnapshotInterp holds the recent snapshots of one entity, sorted by
 * server tick; duplicates and snapshots older than the oldest kept one are
 * ignored. sample(render_tick) takes a fractional tick (server time minus the
 * interpolation delay, in ticks):
 *  - between two snapshots: blended (INTERPOLATED);
 *  - past the newest one: held at the newest, or extrapolated along the last
 *    velocity for at most `max_extrapolate_ticks` and then held (HELD /
 *    EXTRAPOLATED), so a lost packet does not freeze the entity at once and a
 *    long outage does not send it flying;
 *  - before the oldest kept one: clamped to the oldest (HELD).
 * A gap wider than `max_gap_ticks` between two snapshots is not blended
 * (the entity teleported or was out of view): the older snapshot is held
 * until render time reaches the newer one.
 *
 * Pure C, no allocation, no locking (one owner: the render thread).
 * Design: docs/design/client_prediction.md section 6. */

#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_SNAPSHOT_INTERP_CAPACITY 32u

typedef struct BreakSnapshotPose {
    f32 position[3];
    f32 rotation[4]; /* unit quaternion x, y, z, w */
} BreakSnapshotPose;

typedef enum BreakSnapshotInterpResult {
    BREAK_SNAPSHOT_INTERP_INTERPOLATED = 0,
    BREAK_SNAPSHOT_INTERP_EXTRAPOLATED,
    BREAK_SNAPSHOT_INTERP_HELD,
    BREAK_SNAPSHOT_INTERP_EMPTY,   /* no snapshot yet */
    BREAK_SNAPSHOT_INTERP_INVALID  /* bad argument */
} BreakSnapshotInterpResult;

typedef enum BreakSnapshotPushResult {
    BREAK_SNAPSHOT_PUSH_OK = 0,
    BREAK_SNAPSHOT_PUSH_DUPLICATE, /* that tick is already held */
    BREAK_SNAPSHOT_PUSH_TOO_OLD,   /* older than the oldest held when full */
    BREAK_SNAPSHOT_PUSH_INVALID    /* NULL, non-finite value or a zero quaternion */
} BreakSnapshotPushResult;

typedef struct BreakSnapshotInterpConfig {
    f32 max_extrapolate_ticks; /* >= 0 */
    f32 max_gap_ticks;         /* > 0: wider gaps are not blended */
} BreakSnapshotInterpConfig;

typedef struct BreakSnapshotInterp {
    BreakSnapshotInterpConfig cfg;
    u32 count;
    u64 ticks[BREAK_SNAPSHOT_INTERP_CAPACITY];
    BreakSnapshotPose poses[BREAK_SNAPSHOT_INTERP_CAPACITY];
} BreakSnapshotInterp;

/* False on NULL or a config out of range (non-finite, negative extrapolation
 * or a gap <= 0). */
bool break_snapshot_interp_init(BreakSnapshotInterp *si, const BreakSnapshotInterpConfig *cfg);

/* Adds a snapshot. The quaternion is normalized on the way in. When full, the
 * oldest is dropped to make room, unless the new one is older than it. */
BreakSnapshotPushResult break_snapshot_interp_push(BreakSnapshotInterp *si, u64 tick,
                                                   const BreakSnapshotPose *pose);

/* Drops every snapshot older than `tick` except the newest one at or before
 * it, which later samples may still blend from. */
void break_snapshot_interp_discard_before(BreakSnapshotInterp *si, f64 tick);

BreakSnapshotInterpResult break_snapshot_interp_sample(const BreakSnapshotInterp *si,
                                                       f64 render_tick,
                                                       BreakSnapshotPose *out);

u32 break_snapshot_interp_count(const BreakSnapshotInterp *si);

#ifdef __cplusplus
} /* extern "C" */
#endif
