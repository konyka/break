#include <network/break_lag_compensation.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    u64 id;
    BreakLagCompBox box;
} Entry;

/* Tick t lives in slot t % history_ticks. Each slot holds up to max_entities
 * entries in record order plus the tick it belongs to, so a stale slot is
 * never mistaken for a newer tick. */
typedef struct {
    u64 tick;
    bool used;
    u32 count;
} Slot;

struct BreakLagComp {
    u32 max_entities;
    u32 history_ticks;
    u32 max_rewind_ticks;
    bool started;
    u64 current;
    Slot *slots;
    Entry *entries; /* history_ticks * max_entities */
};

static Slot *slot_for(const BreakLagComp *lc, u64 tick) {
    return &lc->slots[tick % lc->history_ticks];
}

static Entry *entries_for(const BreakLagComp *lc, u64 tick) {
    return lc->entries + (usize)(tick % lc->history_ticks) * lc->max_entities;
}

BreakLagCompResult break_lag_comp_create(const BreakLagCompConfig *cfg, BreakLagComp **out) {
    BreakLagComp *lc;
    if (out) *out = NULL;
    if (!cfg || !out) return BREAK_LAG_COMP_INVALID;
    if (cfg->max_entities == 0u || cfg->max_entities > BREAK_LAG_COMP_MAX_ENTITIES ||
        cfg->history_ticks == 0u || cfg->history_ticks > BREAK_LAG_COMP_MAX_HISTORY ||
        cfg->max_rewind_ticks >= cfg->history_ticks)
        return BREAK_LAG_COMP_INVALID;
    lc = (BreakLagComp *)calloc(1u, sizeof *lc);
    if (!lc) return BREAK_LAG_COMP_OOM;
    lc->slots = (Slot *)calloc(cfg->history_ticks, sizeof *lc->slots);
    lc->entries = (Entry *)calloc((usize)cfg->history_ticks * cfg->max_entities,
                                  sizeof *lc->entries);
    if (!lc->slots || !lc->entries) {
        break_lag_comp_destroy(lc);
        return BREAK_LAG_COMP_OOM;
    }
    lc->max_entities = cfg->max_entities;
    lc->history_ticks = cfg->history_ticks;
    lc->max_rewind_ticks = cfg->max_rewind_ticks;
    *out = lc;
    return BREAK_LAG_COMP_OK;
}

void break_lag_comp_destroy(BreakLagComp *lc) {
    if (!lc) return;
    free(lc->slots);
    free(lc->entries);
    free(lc);
}

BreakLagCompResult break_lag_comp_begin_tick(BreakLagComp *lc, u64 tick) {
    Slot *s;
    if (!lc) return BREAK_LAG_COMP_INVALID;
    if (lc->started && (lc->current == UINT64_MAX || tick != lc->current + 1u))
        return BREAK_LAG_COMP_INVALID;
    s = slot_for(lc, tick);
    s->tick = tick;
    s->used = true;
    s->count = 0u;
    lc->current = tick;
    lc->started = true;
    return BREAK_LAG_COMP_OK;
}

static bool box_ok(const BreakLagCompBox *b) {
    for (int k = 0; k < 3; ++k) {
        if (!isfinite(b->min[k]) || !isfinite(b->max[k]) || b->min[k] > b->max[k]) return false;
    }
    return true;
}

BreakLagCompResult break_lag_comp_record(BreakLagComp *lc, u64 id, const BreakLagCompBox *box) {
    Slot *s;
    Entry *e;
    if (!lc || !box || id == 0u || !lc->started || !box_ok(box)) return BREAK_LAG_COMP_INVALID;
    s = slot_for(lc, lc->current);
    e = entries_for(lc, lc->current);
    for (u32 i = 0u; i < s->count; ++i) {
        if (e[i].id == id) return BREAK_LAG_COMP_INVALID;
    }
    if (s->count == lc->max_entities) return BREAK_LAG_COMP_FULL;
    e[s->count].id = id;
    e[s->count].box = *box;
    s->count++;
    return BREAK_LAG_COMP_OK;
}

/* The slot for `tick` when it is still in the history. */
static const Slot *held(const BreakLagComp *lc, u64 tick) {
    const Slot *s;
    if (!lc->started || tick > lc->current || lc->current - tick >= lc->history_ticks)
        return NULL;
    s = slot_for(lc, tick);
    return s->used && s->tick == tick ? s : NULL;
}

/* Slab test: entry distance along a unit ray, or false when it misses within
 * [0, max_t]. An axis the ray is parallel to must contain the origin. */
static bool ray_box(const BreakLagCompBox *b, const f32 o[3], const f32 d[3], f32 max_t,
                    f32 *out_t) {
    f32 t0 = 0.0f, t1 = max_t;
    for (int k = 0; k < 3; ++k) {
        if (d[k] == 0.0f) {
            if (o[k] < b->min[k] || o[k] > b->max[k]) return false;
            continue;
        }
        {
            f32 inv = 1.0f / d[k];
            f32 a = (b->min[k] - o[k]) * inv;
            f32 c = (b->max[k] - o[k]) * inv;
            if (a > c) {
                f32 tmp = a;
                a = c;
                c = tmp;
            }
            if (a > t0) t0 = a;
            if (c < t1) t1 = c;
            if (t0 > t1) return false;
        }
    }
    *out_t = t0;
    return true;
}

BreakLagCompResult break_lag_comp_raycast(const BreakLagComp *lc, u64 view_tick,
                                         const f32 origin[3], const f32 direction[3],
                                         f32 max_distance, u64 ignore_id,
                                         BreakLagCompHit *out) {
    const Slot *s;
    const Entry *e;
    f32 n[3], len;
    bool found = false;
    BreakLagCompHit best;
    if (!lc || !origin || !direction || !out || !(max_distance >= 0.0f) ||
        !isfinite(max_distance))
        return BREAK_LAG_COMP_INVALID;
    for (int k = 0; k < 3; ++k) {
        if (!isfinite(origin[k]) || !isfinite(direction[k])) return BREAK_LAG_COMP_INVALID;
    }
    len = sqrtf(direction[0] * direction[0] + direction[1] * direction[1] +
                direction[2] * direction[2]);
    if (!(len > 0.0f) || !isfinite(len)) return BREAK_LAG_COMP_INVALID;
    if (!lc->started || view_tick > lc->current ||
        lc->current - view_tick > lc->max_rewind_ticks)
        return BREAK_LAG_COMP_REJECTED;
    s = held(lc, view_tick);
    if (!s) return BREAK_LAG_COMP_REJECTED;
    for (int k = 0; k < 3; ++k) n[k] = direction[k] / len;
    e = entries_for(lc, view_tick);
    memset(&best, 0, sizeof best);
    for (u32 i = 0u; i < s->count; ++i) {
        f32 t;
        if (e[i].id == ignore_id) continue;
        if (!ray_box(&e[i].box, origin, n, max_distance, &t)) continue;
        if (!found || t < best.distance || (t == best.distance && e[i].id < best.entity_id)) {
            found = true;
            best.entity_id = e[i].id;
            best.distance = t;
        }
    }
    if (!found) return BREAK_LAG_COMP_MISS;
    for (int k = 0; k < 3; ++k) best.point[k] = origin[k] + n[k] * best.distance;
    *out = best;
    return BREAK_LAG_COMP_OK;
}

BreakLagCompResult break_lag_comp_box_at(const BreakLagComp *lc, u64 tick, u64 id,
                                        BreakLagCompBox *out) {
    const Slot *s;
    const Entry *e;
    if (!lc || !out) return BREAK_LAG_COMP_INVALID;
    s = held(lc, tick);
    if (!s) return BREAK_LAG_COMP_REJECTED;
    e = entries_for(lc, tick);
    for (u32 i = 0u; i < s->count; ++i) {
        if (e[i].id == id) {
            *out = e[i].box;
            return BREAK_LAG_COMP_OK;
        }
    }
    return BREAK_LAG_COMP_MISS;
}

u64 break_lag_comp_current_tick(const BreakLagComp *lc) { return lc ? lc->current : 0u; }
