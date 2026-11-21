/* Cell partition: a uniform grid over the XZ plane maps positions to cell
 * ids; an entity migrates only after it is more than the hysteresis
 * distance outside its current cell, so motion along a boundary does not
 * flap. Combined with BreakCell, an owner that moves its entity hands it to
 * the cell it walked into. */
#include "test_framework.h"
#include <network/break_cell_handoff.h>
#include <network/break_cell_partition.h>
#include <math.h>
#include <string.h>

/* x in [-30, 30), z in [-10, 30), 20-unit cells: ids 0 1 2 / 3 4 5 */
static BreakCellPartition grid3x2(void) {
    BreakCellPartition p;
    memset(&p, 0, sizeof p);
    (void)break_cell_partition_init(&p, -30.0f, -10.0f, 20.0f, 3u, 2u);
    return p;
}

TEST(locate_maps_positions_to_row_major_cells) {
    BreakCellPartition p;
    ASSERT_TRUE(break_cell_partition_init(&p, -30.0f, -10.0f, 20.0f, 3u, 2u));
    ASSERT_EQ(break_cell_partition_cell_count(&p), 6u);
    ASSERT_EQ(break_cell_partition_locate(&p, -29.0f, -9.0f), 0u);
    ASSERT_EQ(break_cell_partition_locate(&p, -10.0f, -9.0f), 1u); /* left edge belongs to the cell */
    ASSERT_EQ(break_cell_partition_locate(&p, -10.001f, -9.0f), 0u);
    ASSERT_EQ(break_cell_partition_locate(&p, 29.0f, -9.0f), 2u);
    ASSERT_EQ(break_cell_partition_locate(&p, -29.0f, 10.0f), 3u);
    ASSERT_EQ(break_cell_partition_locate(&p, 29.0f, 29.0f), 5u);
    /* outside the grid clamps to the nearest edge cell */
    ASSERT_EQ(break_cell_partition_locate(&p, -500.0f, -500.0f), 0u);
    ASSERT_EQ(break_cell_partition_locate(&p, 500.0f, 500.0f), 5u);
    ASSERT_EQ(break_cell_partition_locate(&p, 30.0f, 30.0f), 5u);
    /* a non-finite coordinate maps to column/row 0 */
    ASSERT_EQ(break_cell_partition_locate(&p, NAN, 0.0f), 0u);
    ASSERT_EQ(break_cell_partition_locate(&p, 0.0f, INFINITY), 1u);
    f32 lo_x = 0.0f, lo_z = 0.0f, hi_x = 0.0f, hi_z = 0.0f;
    ASSERT_TRUE(break_cell_partition_bounds(&p, 4u, &lo_x, &lo_z, &hi_x, &hi_z));
    ASSERT_FLOAT_EQ(lo_x, -10.0f, 1e-6f);
    ASSERT_FLOAT_EQ(lo_z, 10.0f, 1e-6f);
    ASSERT_FLOAT_EQ(hi_x, 10.0f, 1e-6f);
    ASSERT_FLOAT_EQ(hi_z, 30.0f, 1e-6f);
    ASSERT_FALSE(break_cell_partition_bounds(&p, 6u, &lo_x, &lo_z, &hi_x, &hi_z));
}

TEST(init_rejects_bad_grids) {
    BreakCellPartition p;
    ASSERT_FALSE(break_cell_partition_init(NULL, 0.0f, 0.0f, 1.0f, 1u, 1u));
    ASSERT_FALSE(break_cell_partition_init(&p, 0.0f, 0.0f, 0.0f, 1u, 1u));
    ASSERT_FALSE(break_cell_partition_init(&p, 0.0f, 0.0f, -1.0f, 1u, 1u));
    ASSERT_FALSE(break_cell_partition_init(&p, 0.0f, 0.0f, INFINITY, 1u, 1u));
    ASSERT_FALSE(break_cell_partition_init(&p, NAN, 0.0f, 1.0f, 1u, 1u));
    ASSERT_FALSE(break_cell_partition_init(&p, 0.0f, 0.0f, 1.0f, 0u, 1u));
    ASSERT_FALSE(break_cell_partition_init(&p, 0.0f, 0.0f, 1.0f, 1u, 0u));
    ASSERT_FALSE(break_cell_partition_init(&p, 0.0f, 0.0f, 1.0f, 70000u, 70000u)); /* id overflow */
    ASSERT_TRUE(break_cell_partition_init(&p, 0.0f, 0.0f, 1.0f, 1u, 1u));
    ASSERT_EQ(break_cell_partition_locate(&p, 123.0f, -5.0f), 0u);
}

TEST(hysteresis_keeps_boundary_walkers_in_their_cell) {
    BreakCellPartition p = grid3x2();
    /* cell 1 spans x in [-10, 10), z in [-10, 10) */
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, 0.0f, 0.0f, 2.0f), 1u);
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, 11.5f, 0.0f, 2.0f), 1u); /* 1.5 outside */
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, 12.0f, 0.0f, 2.0f), 1u); /* exactly 2.0 */
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, 12.5f, 0.0f, 2.0f), 2u);
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, -12.5f, 0.0f, 2.0f), 0u);
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, 0.0f, 12.5f, 2.0f), 4u);
    /* diagonal: the Euclidean distance to the cell rectangle, not per axis
     * (1.4 on each axis is 1.98 away, 1.5 on each axis is 2.12 away) */
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, 11.4f, 11.4f, 2.0f), 1u);
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, 11.5f, 11.5f, 2.0f), 5u);
    /* zero hysteresis migrates as soon as the position leaves the cell */
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, 10.0f, 0.0f, 0.0f), 2u);
    /* the outer edge of the grid never migrates out */
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 2u, 500.0f, 0.0f, 2.0f), 2u);
    /* an unknown current cell, or bad hysteresis, falls back to locate */
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 99u, 0.0f, 0.0f, 2.0f), 1u);
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, 12.5f, 0.0f, -1.0f), 2u);
    /* a non-finite position never triggers a migration */
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 1u, NAN, 0.0f, 2.0f), 1u);
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 4u, 0.0f, -INFINITY, 2.0f), 4u);
    ASSERT_EQ(break_cell_partition_migrate_target(&p, 4u, NAN, 20.0f, 2.0f), 4u);
}

/* ---- end to end with BreakCell ---- */

#define CELLS 6u

typedef struct {
    BreakCellMsg msgs[1024];
    u32 count;
} Wire;

static Wire g_wire;
static BreakCell *g_cells[CELLS];

static void wire_send(void *user, const BreakCellMsg *m) {
    Wire *w = (Wire *)user;
    if (w->count < 1024u) w->msgs[w->count++] = *m;
}

static void wire_deliver(void) {
    static BreakCellMsg batch[1024];
    u32 n = g_wire.count;
    memcpy(batch, g_wire.msgs, (usize)n * sizeof(BreakCellMsg));
    g_wire.count = 0u;
    for (u32 i = 0; i < n; i++)
        if (batch[i].to_cell < CELLS) break_cell_receive(g_cells[batch[i].to_cell], &batch[i]);
}

typedef struct {
    f32 x, z;
    u32 steps;
} Walker;

static i32 owner_of(u64 entity) {
    i32 owner = -1;
    u32 n = 0u;
    for (u32 c = 0; c < CELLS; c++) {
        if (break_cell_is_authoritative(g_cells[c], entity)) {
            owner = (i32)c;
            n++;
        }
    }
    return n == 1u ? owner : (n == 0u ? -1 : -2);
}

/* The owning cell advances the walker, then asks the partition whether it
 * should go; the handoff carries the walker's state to the new cell. */
static u32 simulate(const BreakCellPartition *p, f32 start_x, f32 start_z, f32 (*path_x)(u32),
                    f32 (*path_z)(u32), u32 ticks, u32 *out_handoffs, i32 *out_final) {
    memset(&g_wire, 0, sizeof g_wire);
    for (u32 c = 0; c < CELLS; c++) {
        BreakCellConfig cfg;
        memset(&cfg, 0, sizeof cfg);
        cfg.cell_id = c;
        cfg.capacity = 4u;
        cfg.send = wire_send;
        cfg.user = &g_wire;
        g_cells[c] = break_cell_create(&cfg);
    }
    Walker w = {start_x, start_z, 0u};
    u32 first = break_cell_partition_locate(p, w.x, w.z);
    (void)break_cell_spawn(g_cells[first], 1u, &w, sizeof w);
    u32 violations = 0u;
    for (u32 t = 0; t < ticks; t++) {
        i32 owner = owner_of(1u);
        if (owner == -2) violations++;
        if (owner >= 0) {
            Walker cur;
            u32 size = 0u;
            (void)break_cell_read(g_cells[owner], 1u, &cur, sizeof cur, &size, NULL);
            cur.steps++;
            cur.x = path_x(cur.steps);
            cur.z = path_z(cur.steps);
            (void)break_cell_write(g_cells[owner], 1u, &cur, sizeof cur);
            u32 to = break_cell_partition_migrate_target(p, (u32)owner, cur.x, cur.z, 1.0f);
            if (to != (u32)owner) (void)break_cell_begin_handoff(g_cells[owner], 1u, to);
        }
        wire_deliver();
        for (u32 c = 0; c < CELLS; c++) break_cell_tick(g_cells[c]);
    }
    for (u32 i = 0; i < 8u; i++) {
        wire_deliver();
        for (u32 c = 0; c < CELLS; c++) break_cell_tick(g_cells[c]);
    }
    *out_handoffs = 0u;
    for (u32 c = 0; c < CELLS; c++) {
        BreakCellStats s;
        if (break_cell_stats(g_cells[c], &s)) *out_handoffs += (u32)s.handoffs_in;
    }
    *out_final = owner_of(1u);
    if (*out_final >= 0) {
        Walker end;
        u32 size = 0u;
        (void)break_cell_read(g_cells[*out_final], 1u, &end, sizeof end, &size, NULL);
        if (end.steps == 0u) violations++;
    }
    for (u32 c = 0; c < CELLS; c++) {
        break_cell_destroy(g_cells[c]);
        g_cells[c] = NULL;
    }
    return violations;
}

/* straight line from x=-25 to x=25 along z=0, half a unit per step */
static f32 line_x(u32 s) { return -25.0f + 0.5f * (f32)(s < 100u ? s : 100u); }
static f32 line_z(u32 s) { (void)s; return 0.0f; }
/* jitter around the x=-10 boundary by 0.8, inside the 1.0 hysteresis */
static f32 jitter_x(u32 s) { return -10.0f + ((s % 2u) ? 0.8f : -0.8f); }

TEST(a_walker_is_handed_along_the_cells_it_crosses) {
    BreakCellPartition p = grid3x2();
    u32 handoffs = 0u;
    i32 final_owner = -1;
    u32 v = simulate(&p, -25.0f, 0.0f, line_x, line_z, 200u, &handoffs, &final_owner);
    ASSERT_EQ(v, 0u);
    ASSERT_EQ(final_owner, 2);
    ASSERT_EQ(handoffs, 2u); /* 0 -> 1 -> 2 */
}

TEST(jitter_inside_the_hysteresis_band_never_hands_off) {
    BreakCellPartition p = grid3x2();
    u32 handoffs = 0u;
    i32 final_owner = -1;
    u32 v = simulate(&p, -10.8f, 0.0f, jitter_x, line_z, 200u, &handoffs, &final_owner);
    ASSERT_EQ(v, 0u);
    ASSERT_EQ(handoffs, 0u);
    ASSERT_EQ(final_owner, 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(locate_maps_positions_to_row_major_cells);
    RUN_TEST(init_rejects_bad_grids);
    RUN_TEST(hysteresis_keeps_boundary_walkers_in_their_cell);
    RUN_TEST(a_walker_is_handed_along_the_cells_it_crosses);
    RUN_TEST(jitter_inside_the_hysteresis_band_never_hands_off);
TEST_MAIN_END()
