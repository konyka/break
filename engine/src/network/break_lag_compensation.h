#pragma once
/* Server-side lag compensation: rewinding entity positions to the moment a
 * client saw them.
 *
 * A client renders the world some time behind the server (its round trip
 * plus its interpolation delay). When it reports "I aimed at what I saw at
 * view tick T", the server must test the hit against where each entity was
 * at T, not where it is now. This module keeps a bounded history of every
 * tracked entity's axis-aligned box per server tick and answers ray queries
 * against the boxes as they were at a given tick.
 *
 * The server never trusts the client's clock beyond a limit: a view tick
 * older than `max_rewind_ticks` behind the current tick, or ahead of it, is
 * refused (REJECTED), so a client cannot shoot into the distant past or the
 * future by lying about T. Only entities recorded at exactly T are tested;
 * an entity that did not exist at T cannot be hit.
 *
 * Usage per server tick: begin_tick(tick), then record(id, box) for every
 * live entity. Ticks must increase by exactly one; history older than
 * `history_ticks` is overwritten. Pure C, one allocation at create, no
 * locking (one owner: the simulation thread). Design:
 * docs/design/lag_compensation.md. */

#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_LAG_COMP_MAX_ENTITIES 4096u
#define BREAK_LAG_COMP_MAX_HISTORY 256u

typedef enum BreakLagCompResult {
    BREAK_LAG_COMP_OK = 0,
    BREAK_LAG_COMP_INVALID,  /* bad argument, or a tick that is not the next one */
    BREAK_LAG_COMP_FULL,     /* max_entities already recorded this tick */
    BREAK_LAG_COMP_REJECTED, /* view tick outside the allowed rewind window */
    BREAK_LAG_COMP_MISS,     /* the ray hit nothing */
    BREAK_LAG_COMP_OOM
} BreakLagCompResult;

typedef struct BreakLagCompBox {
    f32 min[3];
    f32 max[3];
} BreakLagCompBox;

typedef struct BreakLagCompConfig {
    u32 max_entities;      /* per tick, 1..BREAK_LAG_COMP_MAX_ENTITIES */
    u32 history_ticks;     /* ticks kept, 1..BREAK_LAG_COMP_MAX_HISTORY */
    u32 max_rewind_ticks;  /* how far back a query may reach, < history_ticks */
} BreakLagCompConfig;

typedef struct BreakLagCompHit {
    u64 entity_id;
    f32 distance;  /* from origin to the hit point, in world units */
    f32 point[3];
} BreakLagCompHit;

typedef struct BreakLagComp BreakLagComp;

/* INVALID on a NULL argument or a limit out of range; *out is NULL then. */
BreakLagCompResult break_lag_comp_create(const BreakLagCompConfig *cfg, BreakLagComp **out);
void break_lag_comp_destroy(BreakLagComp *lc);

/* Starts recording `tick`. The first call may use any tick; later calls must
 * use the previous tick + 1 (INVALID otherwise, nothing changes). The slot of
 * the tick history_ticks back is reused. */
BreakLagCompResult break_lag_comp_begin_tick(BreakLagComp *lc, u64 tick);

/* Records entity `id` (non-zero) at the current tick. INVALID before the
 * first begin_tick, for id 0, for an id already recorded this tick, or for a
 * box whose min exceeds its max on any axis or holds a non-finite value.
 * FULL when max_entities are already recorded this tick. */
BreakLagCompResult break_lag_comp_record(BreakLagComp *lc, u64 id, const BreakLagCompBox *box);

/* Casts a ray from `origin` along `direction` (need not be unit length,
 * must not be zero; it is normalized, so `max_distance` and the reported
 * distance are world units) up to `max_distance` against the boxes recorded at
 * `view_tick`, skipping `ignore_id` (the shooter; 0 = none). Returns the
 * nearest hit, ties broken by the smaller entity id. REJECTED when
 * view_tick is ahead of the current tick, older than current -
 * max_rewind_ticks, or no longer in the history; MISS when nothing is hit.
 * A ray that starts inside a box hits it at distance 0. */
BreakLagCompResult break_lag_comp_raycast(const BreakLagComp *lc, u64 view_tick,
                                         const f32 origin[3], const f32 direction[3],
                                         f32 max_distance, u64 ignore_id,
                                         BreakLagCompHit *out);

/* The box recorded for `id` at `tick`: OK, REJECTED when the tick is not in
 * the history, MISS when the entity was not recorded then. */
BreakLagCompResult break_lag_comp_box_at(const BreakLagComp *lc, u64 tick, u64 id,
                                        BreakLagCompBox *out);

u64 break_lag_comp_current_tick(const BreakLagComp *lc);

#ifdef __cplusplus
} /* extern "C" */
#endif
