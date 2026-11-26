/* Server-side lag compensation: a bounded per-tick history of entity boxes and
 * ray queries against the world as a client saw it at a past tick. */
#include "test_framework.h"

#include <network/break_lag_compensation.h>

#include <math.h>
#include <string.h>

static BreakLagCompBox cube(f32 x, f32 y, f32 z, f32 half) {
    BreakLagCompBox b;
    b.min[0] = x - half;
    b.min[1] = y - half;
    b.min[2] = z - half;
    b.max[0] = x + half;
    b.max[1] = y + half;
    b.max[2] = z + half;
    return b;
}

static BreakLagComp *make(u32 entities, u32 history, u32 rewind) {
    BreakLagCompConfig cfg;
    BreakLagComp *lc = NULL;
    cfg.max_entities = entities;
    cfg.history_ticks = history;
    cfg.max_rewind_ticks = rewind;
    return break_lag_comp_create(&cfg, &lc) == BREAK_LAG_COMP_OK ? lc : NULL;
}

static const f32 k_origin[3] = {0.0f, 0.0f, 0.0f};
static const f32 k_plus_x[3] = {1.0f, 0.0f, 0.0f};

/* A target walks along +z by 1 per tick; at tick t it is at (10, 0, t). */
static void walk(BreakLagComp *lc, u64 first, u64 last) {
    for (u64 t = first; t <= last; ++t) {
        BreakLagCompBox b = cube(10.0f, 0.0f, (f32)(t - first), 0.5f);
        (void)break_lag_comp_begin_tick(lc, t);
        (void)break_lag_comp_record(lc, 7u, &b);
    }
}

TEST(a_shot_hits_where_the_target_was_at_the_view_tick) {
    BreakLagComp *lc = make(8u, 32u, 16u);
    BreakLagCompHit hit;
    ASSERT_NOT_NULL(lc);
    walk(lc, 100u, 110u);
    /* Now the target is at z = 10; the client still saw it at z = 0 (tick 100). */
    ASSERT_EQ(break_lag_comp_raycast(lc, 110u, k_origin, k_plus_x, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_MISS);
    ASSERT_EQ(break_lag_comp_raycast(lc, 100u, k_origin, k_plus_x, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_OK);
    ASSERT_EQ(hit.entity_id, 7u);
    ASSERT_FLOAT_EQ(hit.distance, 9.5f, 1e-5f);
    ASSERT_FLOAT_EQ(hit.point[0], 9.5f, 1e-5f);
    ASSERT_FLOAT_EQ(hit.point[2], 0.0f, 1e-5f);
    /* one tick later it had moved by a full box: a miss */
    ASSERT_EQ(break_lag_comp_raycast(lc, 101u, k_origin, k_plus_x, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_MISS);
    ASSERT_EQ(break_lag_comp_current_tick(lc), 110u);
    break_lag_comp_destroy(lc);
}

TEST(view_ticks_outside_the_rewind_window_are_rejected) {
    BreakLagComp *lc = make(8u, 32u, 5u);
    BreakLagCompHit hit;
    ASSERT_NOT_NULL(lc);
    walk(lc, 100u, 110u);
    ASSERT_EQ(break_lag_comp_raycast(lc, 111u, k_origin, k_plus_x, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_REJECTED); /* the future */
    ASSERT_EQ(break_lag_comp_raycast(lc, 104u, k_origin, k_plus_x, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_REJECTED); /* 6 back, limit 5 */
    ASSERT_EQ(break_lag_comp_raycast(lc, 105u, k_origin, k_plus_x, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_MISS); /* exactly 5 back is allowed */
    ASSERT_EQ(break_lag_comp_raycast(lc, 99u, k_origin, k_plus_x, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_REJECTED); /* before any history */
    break_lag_comp_destroy(lc);
}

TEST(history_older_than_its_length_is_gone) {
    BreakLagComp *lc = make(8u, 4u, 3u);
    BreakLagCompBox box;
    ASSERT_NOT_NULL(lc);
    walk(lc, 1u, 10u);
    ASSERT_EQ(break_lag_comp_box_at(lc, 7u, 7u, &box), BREAK_LAG_COMP_OK);
    ASSERT_FLOAT_EQ(box.min[2], 5.5f, 1e-6f);
    ASSERT_EQ(break_lag_comp_box_at(lc, 6u, 7u, &box), BREAK_LAG_COMP_REJECTED);
    ASSERT_EQ(break_lag_comp_box_at(lc, 10u, 7u, &box), BREAK_LAG_COMP_OK);
    ASSERT_FLOAT_EQ(box.min[2], 8.5f, 1e-6f);
    ASSERT_EQ(break_lag_comp_box_at(lc, 10u, 8u, &box), BREAK_LAG_COMP_MISS);
    ASSERT_EQ(break_lag_comp_box_at(lc, 11u, 7u, &box), BREAK_LAG_COMP_REJECTED);
    break_lag_comp_destroy(lc);
}

TEST(an_entity_that_did_not_exist_at_the_view_tick_cannot_be_hit) {
    BreakLagComp *lc = make(8u, 16u, 8u);
    BreakLagCompBox b = cube(5.0f, 0.0f, 0.0f, 1.0f);
    BreakLagCompHit hit;
    ASSERT_NOT_NULL(lc);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 1u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 2u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 3u, &b), BREAK_LAG_COMP_OK); /* spawns at tick 2 */
    ASSERT_EQ(break_lag_comp_raycast(lc, 1u, k_origin, k_plus_x, 50.0f, 0u, &hit),
              BREAK_LAG_COMP_MISS);
    ASSERT_EQ(break_lag_comp_raycast(lc, 2u, k_origin, k_plus_x, 50.0f, 0u, &hit),
              BREAK_LAG_COMP_OK);
    ASSERT_EQ(hit.entity_id, 3u);
    /* despawns at tick 3: gone now, still there in the past */
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 3u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_raycast(lc, 3u, k_origin, k_plus_x, 50.0f, 0u, &hit),
              BREAK_LAG_COMP_MISS);
    ASSERT_EQ(break_lag_comp_raycast(lc, 2u, k_origin, k_plus_x, 50.0f, 0u, &hit),
              BREAK_LAG_COMP_OK);
    break_lag_comp_destroy(lc);
}

TEST(the_nearest_hit_wins_and_the_shooter_is_skipped) {
    BreakLagComp *lc = make(8u, 8u, 4u);
    BreakLagCompBox shooter = cube(0.0f, 0.0f, 0.0f, 1.0f);
    BreakLagCompBox near_box = cube(5.0f, 0.0f, 0.0f, 0.5f);
    BreakLagCompBox far_box = cube(9.0f, 0.0f, 0.0f, 0.5f);
    BreakLagCompBox twin = cube(5.0f, 0.0f, 0.0f, 0.5f);
    BreakLagCompHit hit;
    ASSERT_NOT_NULL(lc);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 1u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 1u, &shooter), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 30u, &far_box), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 20u, &near_box), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 10u, &twin), BREAK_LAG_COMP_OK);
    /* without skipping, the shooter's own box contains the origin: distance 0 */
    ASSERT_EQ(break_lag_comp_raycast(lc, 1u, k_origin, k_plus_x, 50.0f, 0u, &hit),
              BREAK_LAG_COMP_OK);
    ASSERT_EQ(hit.entity_id, 1u);
    ASSERT_FLOAT_EQ(hit.distance, 0.0f, 1e-6f);
    ASSERT_EQ(break_lag_comp_raycast(lc, 1u, k_origin, k_plus_x, 50.0f, 1u, &hit),
              BREAK_LAG_COMP_OK);
    ASSERT_EQ(hit.entity_id, 10u); /* tie with 20 at 4.5: smaller id */
    ASSERT_FLOAT_EQ(hit.distance, 4.5f, 1e-5f);
    /* a range that stops short of the nearest box */
    ASSERT_EQ(break_lag_comp_raycast(lc, 1u, k_origin, k_plus_x, 4.4f, 1u, &hit),
              BREAK_LAG_COMP_MISS);
    ASSERT_EQ(break_lag_comp_raycast(lc, 1u, k_origin, k_plus_x, 4.5f, 1u, &hit),
              BREAK_LAG_COMP_OK);
    break_lag_comp_destroy(lc);
}

TEST(rays_in_any_direction_and_unnormalized_directions) {
    BreakLagComp *lc = make(8u, 8u, 4u);
    BreakLagCompBox b = cube(-3.0f, 4.0f, 0.0f, 0.5f);
    BreakLagCompHit hit;
    const f32 toward[3] = {-30.0f, 40.0f, 0.0f}; /* length 50, points at the box centre */
    const f32 away[3] = {3.0f, -4.0f, 0.0f};
    const f32 up[3] = {0.0f, 0.0f, 2.0f};
    ASSERT_NOT_NULL(lc);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 1u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 5u, &b), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_raycast(lc, 1u, k_origin, toward, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_OK);
    /* the box face nearest the origin along that ray: distance in world units */
    ASSERT_TRUE(hit.distance > 4.0f && hit.distance < 5.0f);
    ASSERT_FLOAT_EQ(hit.point[0], -0.6f * hit.distance, 1e-4f);
    ASSERT_FLOAT_EQ(hit.point[1], 0.8f * hit.distance, 1e-4f);
    {
        /* a ray from elsewhere reports a world-space point, not an offset */
        const f32 from[3] = {-3.0f, 4.0f, -10.0f};
        const f32 down_z[3] = {0.0f, 0.0f, 1.0f};
        ASSERT_EQ(break_lag_comp_raycast(lc, 1u, from, down_z, 100.0f, 0u, &hit),
                  BREAK_LAG_COMP_OK);
        ASSERT_FLOAT_EQ(hit.distance, 9.5f, 1e-5f);
        ASSERT_FLOAT_EQ(hit.point[0], -3.0f, 1e-5f);
        ASSERT_FLOAT_EQ(hit.point[1], 4.0f, 1e-5f);
        ASSERT_FLOAT_EQ(hit.point[2], -0.5f, 1e-5f);
    }
    ASSERT_EQ(break_lag_comp_raycast(lc, 1u, k_origin, away, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_MISS); /* behind the origin */
    ASSERT_EQ(break_lag_comp_raycast(lc, 1u, k_origin, up, 100.0f, 0u, &hit),
              BREAK_LAG_COMP_MISS); /* parallel to two slabs, outside them */
    break_lag_comp_destroy(lc);
}

TEST(recording_rules_and_tick_order) {
    BreakLagComp *lc = make(2u, 8u, 4u);
    BreakLagCompBox b = cube(0.0f, 0.0f, 0.0f, 1.0f);
    BreakLagCompBox inverted = b;
    BreakLagCompBox nan_box = b;
    ASSERT_NOT_NULL(lc);
    ASSERT_EQ(break_lag_comp_record(lc, 1u, &b), BREAK_LAG_COMP_INVALID); /* no tick yet */
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 50u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 50u), BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 52u), BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 49u), BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_current_tick(lc), 50u);
    ASSERT_EQ(break_lag_comp_record(lc, 0u, &b), BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_record(lc, 1u, NULL), BREAK_LAG_COMP_INVALID);
    inverted.min[1] = 2.0f;
    ASSERT_EQ(break_lag_comp_record(lc, 1u, &inverted), BREAK_LAG_COMP_INVALID);
    nan_box.max[2] = NAN;
    ASSERT_EQ(break_lag_comp_record(lc, 1u, &nan_box), BREAK_LAG_COMP_INVALID);
    nan_box = b;
    nan_box.min[0] = -INFINITY;
    ASSERT_EQ(break_lag_comp_record(lc, 1u, &nan_box), BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_record(lc, 1u, &b), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 1u, &b), BREAK_LAG_COMP_INVALID); /* twice */
    ASSERT_EQ(break_lag_comp_record(lc, 2u, &b), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 3u, &b), BREAK_LAG_COMP_FULL);
    /* the next tick starts empty */
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 51u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 3u, &b), BREAK_LAG_COMP_OK);
    {
        BreakLagCompBox got;
        ASSERT_EQ(break_lag_comp_box_at(lc, 51u, 1u, &got), BREAK_LAG_COMP_MISS);
        ASSERT_EQ(break_lag_comp_box_at(lc, 50u, 2u, &got), BREAK_LAG_COMP_OK);
    }
    break_lag_comp_destroy(lc);
}

TEST(a_reused_slot_forgets_the_old_tick) {
    BreakLagComp *lc = make(4u, 3u, 2u);
    BreakLagCompBox a = cube(5.0f, 0.0f, 0.0f, 1.0f);
    BreakLagCompBox got;
    ASSERT_NOT_NULL(lc);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 1u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_record(lc, 9u, &a), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 2u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 3u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 4u), BREAK_LAG_COMP_OK); /* reuses tick 1's slot */
    ASSERT_EQ(break_lag_comp_box_at(lc, 4u, 9u, &got), BREAK_LAG_COMP_MISS);
    ASSERT_EQ(break_lag_comp_box_at(lc, 1u, 9u, &got), BREAK_LAG_COMP_REJECTED);
    break_lag_comp_destroy(lc);
}

TEST(arguments_are_validated) {
    BreakLagCompConfig cfg = {4u, 8u, 4u};
    BreakLagComp *lc = (BreakLagComp *)&cfg;
    BreakLagCompHit hit;
    BreakLagCompBox got;
    const f32 zero[3] = {0.0f, 0.0f, 0.0f};
    const f32 nan_dir[3] = {NAN, 0.0f, 0.0f};
    ASSERT_EQ(break_lag_comp_create(NULL, &lc), BREAK_LAG_COMP_INVALID);
    ASSERT_TRUE(lc == NULL);
    ASSERT_EQ(break_lag_comp_create(&cfg, NULL), BREAK_LAG_COMP_INVALID);
    cfg.max_entities = 0u;
    ASSERT_EQ(break_lag_comp_create(&cfg, &lc), BREAK_LAG_COMP_INVALID);
    cfg.max_entities = BREAK_LAG_COMP_MAX_ENTITIES + 1u;
    ASSERT_EQ(break_lag_comp_create(&cfg, &lc), BREAK_LAG_COMP_INVALID);
    cfg.max_entities = 4u;
    cfg.history_ticks = 0u;
    ASSERT_EQ(break_lag_comp_create(&cfg, &lc), BREAK_LAG_COMP_INVALID);
    cfg.history_ticks = BREAK_LAG_COMP_MAX_HISTORY + 1u;
    ASSERT_EQ(break_lag_comp_create(&cfg, &lc), BREAK_LAG_COMP_INVALID);
    cfg.history_ticks = 8u;
    cfg.max_rewind_ticks = 8u; /* must be below history_ticks */
    ASSERT_EQ(break_lag_comp_create(&cfg, &lc), BREAK_LAG_COMP_INVALID);
    ASSERT_TRUE(lc == NULL);
    cfg.max_entities = BREAK_LAG_COMP_MAX_ENTITIES;
    cfg.history_ticks = BREAK_LAG_COMP_MAX_HISTORY;
    cfg.max_rewind_ticks = BREAK_LAG_COMP_MAX_HISTORY - 1u;
    ASSERT_EQ(break_lag_comp_create(&cfg, &lc), BREAK_LAG_COMP_OK);
    break_lag_comp_destroy(lc);
    lc = make(4u, 8u, 0u); /* rewind 0: only the current tick */
    ASSERT_NOT_NULL(lc);
    ASSERT_EQ(break_lag_comp_raycast(lc, 0u, k_origin, k_plus_x, 1.0f, 0u, &hit),
              BREAK_LAG_COMP_REJECTED); /* no tick begun */
    ASSERT_EQ(break_lag_comp_begin_tick(lc, 0u), BREAK_LAG_COMP_OK);
    ASSERT_EQ(break_lag_comp_raycast(lc, 0u, k_origin, k_plus_x, 1.0f, 0u, &hit),
              BREAK_LAG_COMP_MISS);
    ASSERT_EQ(break_lag_comp_raycast(lc, 0u, k_origin, zero, 1.0f, 0u, &hit),
              BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_raycast(lc, 0u, k_origin, nan_dir, 1.0f, 0u, &hit),
              BREAK_LAG_COMP_INVALID);
    {
        /* a non-finite origin is refused even where every box test would miss */
        const f32 nan_origin[3] = {0.0f, NAN, 0.0f};
        const f32 inf_origin[3] = {INFINITY, 0.0f, 0.0f};
        BreakLagCompBox b = cube(0.0f, 0.0f, 0.0f, 1.0f);
        ASSERT_EQ(break_lag_comp_record(lc, 1u, &b), BREAK_LAG_COMP_OK);
        ASSERT_EQ(break_lag_comp_raycast(lc, 0u, nan_origin, k_plus_x, 1.0f, 0u, &hit),
                  BREAK_LAG_COMP_INVALID);
        ASSERT_EQ(break_lag_comp_raycast(lc, 0u, inf_origin, k_plus_x, 1.0f, 0u, &hit),
                  BREAK_LAG_COMP_INVALID);
    }
    ASSERT_EQ(break_lag_comp_raycast(lc, 0u, k_origin, k_plus_x, -1.0f, 0u, &hit),
              BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_raycast(lc, 0u, k_origin, k_plus_x, NAN, 0u, &hit),
              BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_raycast(lc, 0u, NULL, k_plus_x, 1.0f, 0u, &hit),
              BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_raycast(lc, 0u, k_origin, NULL, 1.0f, 0u, &hit),
              BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_raycast(lc, 0u, k_origin, k_plus_x, 1.0f, 0u, NULL),
              BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_raycast(NULL, 0u, k_origin, k_plus_x, 1.0f, 0u, &hit),
              BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_box_at(lc, 0u, 1u, NULL), BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_box_at(NULL, 0u, 1u, &got), BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_begin_tick(NULL, 1u), BREAK_LAG_COMP_INVALID);
    ASSERT_EQ(break_lag_comp_current_tick(NULL), 0u);
    break_lag_comp_destroy(lc);
    break_lag_comp_destroy(NULL);
}

/* Random boxes and rays checked against a brute-force reference at a random
 * past tick: same verdict, same entity, same distance. */
static bool ref_slab(const BreakLagCompBox *b, const f32 o[3], const f32 d[3], f32 max_t,
                     f32 *out_t) {
    f32 t0 = 0.0f, t1 = max_t;
    for (int k = 0; k < 3; ++k) {
        if (d[k] == 0.0f) {
            if (o[k] < b->min[k] || o[k] > b->max[k]) return false;
        } else {
            f32 a = (b->min[k] - o[k]) / d[k];
            f32 c = (b->max[k] - o[k]) / d[k];
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

static u32 g_rng = 4242u;

static u32 rnd16(void) {
    g_rng = g_rng * 1103515245u + 12345u;
    return (g_rng >> 8) & 0xFFFFu;
}

TEST(random_queries_match_a_brute_force_reference) {
    enum { k_ticks = 40, k_ents = 24, k_history = 16, k_rewind = 12 };
    BreakLagComp *lc = make(k_ents, k_history, k_rewind);
    BreakLagCompBox boxes[k_ticks][k_ents];
    bool alive[k_ticks][k_ents];
    u32 hits = 0u;
    ASSERT_NOT_NULL(lc);
    for (u32 t = 0u; t < (u32)k_ticks; ++t) {
        ASSERT_EQ(break_lag_comp_begin_tick(lc, 1000u + t), BREAK_LAG_COMP_OK);
        for (u32 e = 0u; e < (u32)k_ents; ++e) {
            f32 x, y, z, half;
            alive[t][e] = rnd16() % 4u != 0u;
            x = (f32)(rnd16() % 40u) - 20.0f;
            y = (f32)(rnd16() % 40u) - 20.0f;
            z = (f32)(rnd16() % 40u) - 20.0f;
            half = 0.5f + (f32)(rnd16() % 3u);
            boxes[t][e] = cube(x, y, z, half);
            if (alive[t][e])
                ASSERT_EQ(break_lag_comp_record(lc, e + 1u, &boxes[t][e]), BREAK_LAG_COMP_OK);
        }
        for (u32 q = 0u; q < 30u; ++q) {
            u32 back = rnd16() % (k_rewind + 1u);
            u32 vt;
            f32 o[3], d[3], len;
            BreakLagCompHit hit;
            BreakLagCompResult r;
            u64 best_id = 0u, skip = rnd16() % 3u == 0u ? (u64)(rnd16() % k_ents + 1u) : 0u;
            f32 best_t = 0.0f;
            if (back > t) back = t;
            vt = t - back;
            for (int k = 0; k < 3; ++k) {
                o[k] = (f32)(rnd16() % 60u) - 30.0f;
                d[k] = (f32)(rnd16() % 21u) - 10.0f;
            }
            if (d[0] == 0.0f && d[1] == 0.0f && d[2] == 0.0f) d[0] = 1.0f;
            len = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
            r = break_lag_comp_raycast(lc, 1000u + vt, o, d, 80.0f, skip, &hit);
            {
                f32 n[3] = {d[0] / len, d[1] / len, d[2] / len};
                for (u32 e = 0u; e < (u32)k_ents; ++e) {
                    f32 th;
                    if (!alive[vt][e] || e + 1u == skip) continue;
                    if (ref_slab(&boxes[vt][e], o, n, 80.0f, &th) &&
                        (best_id == 0u || th < best_t - 1e-4f)) {
                        best_id = e + 1u;
                        best_t = th;
                    }
                }
            }
            if (best_id == 0u) {
                ASSERT_EQ(r, BREAK_LAG_COMP_MISS);
            } else {
                ASSERT_EQ(r, BREAK_LAG_COMP_OK);
                ASSERT_FLOAT_EQ(hit.distance, best_t, 1e-3f);
                hits++;
            }
        }
    }
    ASSERT_TRUE(hits > 50u);
    break_lag_comp_destroy(lc);
}

TEST_MAIN_BEGIN()
    RUN_TEST(a_shot_hits_where_the_target_was_at_the_view_tick);
    RUN_TEST(view_ticks_outside_the_rewind_window_are_rejected);
    RUN_TEST(history_older_than_its_length_is_gone);
    RUN_TEST(an_entity_that_did_not_exist_at_the_view_tick_cannot_be_hit);
    RUN_TEST(the_nearest_hit_wins_and_the_shooter_is_skipped);
    RUN_TEST(rays_in_any_direction_and_unnormalized_directions);
    RUN_TEST(recording_rules_and_tick_order);
    RUN_TEST(a_reused_slot_forgets_the_old_tick);
    RUN_TEST(arguments_are_validated);
    RUN_TEST(random_queries_match_a_brute_force_reference);
TEST_MAIN_END()
