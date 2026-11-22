/* Visibility and input routing that follow an entity across cell handoffs:
 * the client's view is the union of what each cell reports, with a grace
 * period that hides the moment no cell owns the entity, and the gateway
 * routes input to whichever cell announced the highest epoch. */
#include "test_framework.h"
#include <network/break_aoi.h>
#include <network/break_cell_handoff.h>
#include <network/break_cell_partition.h>
#include <network/break_cell_view.h>
#include <string.h>

#define CAP 64u

typedef struct {
    u64 enter[CAP], leave[CAP];
    u32 enter_count, leave_count;
} Events;

static bool tick(BreakCellView *v, Events *e) {
    return break_cell_view_tick(v, e->enter, &e->enter_count, e->leave, &e->leave_count);
}

TEST(view_is_the_union_of_cell_reports) {
    BreakCellView *v = break_cell_view_create(CAP, 2u);
    Events e;
    const u64 a[] = {3u, 1u}, b[] = {2u, 3u};
    ASSERT_NOT_NULL(v);
    ASSERT_TRUE(break_cell_view_report(v, 10u, a, 2u));
    ASSERT_TRUE(break_cell_view_report(v, 11u, b, 2u));
    ASSERT_TRUE(tick(v, &e));
    ASSERT_EQ(e.enter_count, 3u);
    ASSERT_EQ(e.enter[0], 1u);
    ASSERT_EQ(e.enter[1], 2u);
    ASSERT_EQ(e.enter[2], 3u);
    ASSERT_EQ(e.leave_count, 0u);
    ASSERT_EQ(break_cell_view_visible_count(v), 3u);
    /* nothing changes: no events */
    ASSERT_TRUE(tick(v, &e));
    ASSERT_EQ(e.enter_count + e.leave_count, 0u);
    /* cell 10 stops seeing 3, but cell 11 still does: 3 stays visible */
    ASSERT_TRUE(break_cell_view_report(v, 10u, a + 1, 1u));
    for (u32 i = 0; i < 5u; i++) {
        ASSERT_TRUE(tick(v, &e));
        ASSERT_EQ(e.enter_count + e.leave_count, 0u);
    }
    ASSERT_TRUE(break_cell_view_is_visible(v, 3u));
    break_cell_view_destroy(v);
}

TEST(an_entity_leaves_only_after_the_grace_period) {
    BreakCellView *v = break_cell_view_create(CAP, 2u);
    Events e;
    const u64 one[] = {7u};
    ASSERT_TRUE(break_cell_view_report(v, 1u, one, 1u));
    ASSERT_TRUE(tick(v, &e));
    ASSERT_EQ(e.enter_count, 1u);
    ASSERT_TRUE(break_cell_view_report(v, 1u, NULL, 0u));
    ASSERT_TRUE(tick(v, &e)); /* unreported for 1 tick */
    ASSERT_EQ(e.leave_count, 0u);
    ASSERT_TRUE(tick(v, &e)); /* 2 ticks: still within grace */
    ASSERT_EQ(e.leave_count, 0u);
    ASSERT_TRUE(break_cell_view_is_visible(v, 7u));
    ASSERT_TRUE(tick(v, &e)); /* 3 ticks: more than grace */
    ASSERT_EQ(e.leave_count, 1u);
    ASSERT_EQ(e.leave[0], 7u);
    ASSERT_FALSE(break_cell_view_is_visible(v, 7u));
    ASSERT_EQ(break_cell_view_visible_count(v), 0u);
    /* coming back within the grace period produces no events at all */
    ASSERT_TRUE(break_cell_view_report(v, 1u, one, 1u));
    ASSERT_TRUE(tick(v, &e));
    ASSERT_EQ(e.enter_count, 1u);
    ASSERT_TRUE(break_cell_view_report(v, 1u, NULL, 0u));
    ASSERT_TRUE(tick(v, &e));
    ASSERT_TRUE(break_cell_view_report(v, 2u, one, 1u)); /* reappears in another cell */
    ASSERT_TRUE(tick(v, &e));
    ASSERT_EQ(e.enter_count + e.leave_count, 0u);
    /* a report resets the grace clock: gaps of 2 ticks never cause a leave */
    for (u32 round = 0; round < 5u; round++) {
        ASSERT_TRUE(break_cell_view_report(v, 2u, NULL, 0u));
        ASSERT_TRUE(tick(v, &e));
        ASSERT_TRUE(tick(v, &e));
        ASSERT_EQ(e.leave_count, 0u);
        ASSERT_TRUE(break_cell_view_report(v, 2u, one, 1u));
        ASSERT_TRUE(tick(v, &e));
        ASSERT_EQ(e.enter_count + e.leave_count, 0u);
    }
    /* grace 0: leaves on the first unreported tick */
    break_cell_view_destroy(v);
    v = break_cell_view_create(CAP, 0u);
    ASSERT_TRUE(break_cell_view_report(v, 1u, one, 1u));
    ASSERT_TRUE(tick(v, &e));
    ASSERT_TRUE(break_cell_view_report(v, 1u, NULL, 0u));
    ASSERT_TRUE(tick(v, &e));
    ASSERT_EQ(e.leave_count, 1u);
    break_cell_view_destroy(v);
}

TEST(view_rejects_bad_reports_without_changing) {
    BreakCellView *v = break_cell_view_create(3u, 1u);
    Events e;
    const u64 dup[] = {1u, 1u}, three[] = {1u, 2u, 3u}, four[] = {4u};
    ASSERT_TRUE(break_cell_view_create(0u, 1u) == NULL);
    ASSERT_FALSE(break_cell_view_report(v, 1u, dup, 2u));
    ASSERT_FALSE(break_cell_view_report(v, 1u, NULL, 1u));
    ASSERT_FALSE(break_cell_view_report(NULL, 1u, three, 3u));
    ASSERT_TRUE(break_cell_view_report(v, 1u, three, 3u));
    ASSERT_FALSE(break_cell_view_report(v, 2u, four, 1u)); /* a 4th entity: over capacity */
    ASSERT_TRUE(tick(v, &e));
    ASSERT_EQ(e.enter_count, 3u);
    /* an entity in its grace period still takes a slot */
    ASSERT_TRUE(break_cell_view_report(v, 1u, three, 2u));
    ASSERT_TRUE(tick(v, &e));
    ASSERT_FALSE(break_cell_view_report(v, 2u, four, 1u));
    ASSERT_TRUE(tick(v, &e)); /* entity 3 leaves: its slot frees up */
    ASSERT_EQ(e.leave_count, 1u);
    ASSERT_TRUE(break_cell_view_report(v, 2u, four, 1u));
    /* the cell table is bounded */
    for (u32 c = 3u; c < 3u + BREAK_CELL_VIEW_MAX_CELLS - 2u; c++)
        ASSERT_TRUE(break_cell_view_report(v, c, NULL, 0u));
    ASSERT_FALSE(break_cell_view_report(v, 999u, NULL, 0u));
    ASSERT_FALSE(break_cell_view_tick(v, NULL, &e.enter_count, e.leave, &e.leave_count));
    ASSERT_FALSE(break_cell_view_tick(NULL, e.enter, &e.enter_count, e.leave, &e.leave_count));
    ASSERT_FALSE(break_cell_view_is_visible(NULL, 1u));
    ASSERT_EQ(break_cell_view_visible_count(NULL), 0u);
    break_cell_view_destroy(v);
    break_cell_view_destroy(NULL);
}

TEST(route_follows_the_highest_epoch) {
    BreakCellRoute *r = break_cell_route_create(2u);
    u32 cell = 0u;
    u64 epoch = 0u;
    ASSERT_NOT_NULL(r);
    ASSERT_TRUE(break_cell_route_create(0u) == NULL);
    ASSERT_FALSE(break_cell_route_lookup(r, 5u, &cell, &epoch));
    ASSERT_EQ(break_cell_route_observe(r, 5u, 1u, 1u), BREAK_CELL_ROUTE_UPDATED);
    ASSERT_EQ(break_cell_route_observe(r, 5u, 1u, 1u), BREAK_CELL_ROUTE_SAME);
    ASSERT_EQ(break_cell_route_observe(r, 5u, 2u, 2u), BREAK_CELL_ROUTE_UPDATED);
    ASSERT_EQ(break_cell_route_observe(r, 5u, 1u, 1u), BREAK_CELL_ROUTE_STALE); /* late */
    ASSERT_EQ(break_cell_route_observe(r, 5u, 3u, 2u), BREAK_CELL_ROUTE_CONFLICT);
    ASSERT_TRUE(break_cell_route_lookup(r, 5u, &cell, &epoch));
    ASSERT_EQ(cell, 2u);
    ASSERT_EQ(epoch, 2u);
    ASSERT_TRUE(break_cell_route_lookup(r, 5u, NULL, NULL));
    ASSERT_EQ(break_cell_route_observe(r, 6u, 1u, 1u), BREAK_CELL_ROUTE_UPDATED);
    ASSERT_EQ(break_cell_route_observe(r, 7u, 1u, 1u), BREAK_CELL_ROUTE_FULL);
    ASSERT_EQ(break_cell_route_observe(r, 7u, 1u, 0u), BREAK_CELL_ROUTE_INVALID);
    ASSERT_EQ(break_cell_route_observe(NULL, 7u, 1u, 1u), BREAK_CELL_ROUTE_INVALID);
    ASSERT_TRUE(break_cell_route_forget(r, 5u)); /* forgetting the first keeps the rest */
    ASSERT_TRUE(break_cell_route_lookup(r, 6u, &cell, &epoch));
    ASSERT_EQ(cell, 1u);
    ASSERT_EQ(break_cell_route_observe(r, 5u, 2u, 2u), BREAK_CELL_ROUTE_UPDATED);
    ASSERT_TRUE(break_cell_route_forget(r, 6u));
    ASSERT_FALSE(break_cell_route_forget(r, 6u));
    ASSERT_FALSE(break_cell_route_lookup(r, 6u, NULL, NULL));
    ASSERT_EQ(break_cell_route_observe(r, 7u, 1u, 1u), BREAK_CELL_ROUTE_UPDATED);
    ASSERT_FALSE(break_cell_route_forget(NULL, 7u));
    ASSERT_FALSE(break_cell_route_lookup(NULL, 7u, NULL, NULL));
    break_cell_route_destroy(r);
    break_cell_route_destroy(NULL);
}

/* ---- end to end ---- */

#define CELLS 3u
#define NET_CAP 256u

static BreakCell *g_cells[CELLS];
static BreakCellMsg g_queue[NET_CAP];
static u32 g_queued;

static void queue_send(void *user, const BreakCellMsg *msg) {
    (void)user;
    if (g_queued < NET_CAP) g_queue[g_queued++] = *msg;
}

/* Delivers every queued message once, one network hop per step. */
static void deliver(void) {
    static BreakCellMsg batch[NET_CAP];
    u32 n = g_queued;
    memcpy(batch, g_queue, n * sizeof batch[0]);
    g_queued = 0u;
    for (u32 i = 0; i < n; i++)
        if (batch[i].to_cell < CELLS) break_cell_receive(g_cells[batch[i].to_cell], &batch[i]);
}

/* A walker crosses three cells while a client at its side watches it and
 * a static marker in every cell. Each cell indexes only the entities it
 * owns and reports its AoI result for the client. The walker must stay
 * visible the whole way (no leave), and input routed by the gateway must
 * always reach the walker's current owner. */
TEST(a_walker_stays_visible_and_reachable_across_handoffs) {
    BreakCellPartition part;
    BreakCellView *view = break_cell_view_create(CAP, 3u);
    BreakCellRoute *route = break_cell_route_create(CAP);
    const u64 walker = 100u;
    u32 owner = 0u, handoffs_seen = 0u, input_ok = 0u, input_sent = 0u;
    Events e;
    ASSERT_TRUE(break_cell_partition_init(&part, 0.0f, 0.0f, 10.0f, CELLS, 1u));
    ASSERT_NOT_NULL(view);
    ASSERT_NOT_NULL(route);
    g_queued = 0u;
    for (u32 c = 0; c < CELLS; c++) {
        BreakCellConfig cfg;
        memset(&cfg, 0, sizeof cfg);
        cfg.cell_id = c;
        cfg.capacity = 8u;
        cfg.retransmit_ticks = 2u;
        cfg.send = queue_send;
        g_cells[c] = break_cell_create(&cfg);
        ASSERT_NOT_NULL(g_cells[c]);
        ASSERT_TRUE(break_cell_spawn(g_cells[c], 200u + c, NULL, 0u)); /* a marker per cell */
    }
    ASSERT_TRUE(break_cell_spawn(g_cells[0], walker, NULL, 0u));

    for (u32 t = 0; t < 300u; t++) {
        f32 x = 1.0f + 0.1f * (f32)t; /* 1 .. 30.9: crosses x = 10 and x = 20 */
        /* the owner starts handoffs as the walker moves */
        for (u32 c = 0; c < CELLS; c++) {
            if (!break_cell_is_authoritative(g_cells[c], walker)) continue;
            u32 target = break_cell_partition_migrate_target(&part, c, x, 0.0f, 0.5f);
            if (target != c && break_cell_entity_state(g_cells[c], walker) == BREAK_CELL_ENTITY_OWNED)
                (void)break_cell_begin_handoff(g_cells[c], walker, target);
        }
        deliver();
        for (u32 c = 0; c < CELLS; c++) break_cell_tick(g_cells[c]);

        /* each cell: index what it owns, compute the client's AoI, report,
         * and announce ownership to the gateway */
        for (u32 c = 0; c < CELLS; c++) {
            BreakSpatialIndex *index = break_spatial_index_create(4.0f);
            BreakWitness wit;
            BreakAoIResult res;
            u64 ids[CAP];
            u32 n = 0u;
            ASSERT_NOT_NULL(index);
            memset(&wit, 0, sizeof wit);
            wit.position[0] = x;
            wit.radius = 1000.0f;
            memset(&res, 0, sizeof res);
            for (u64 id = walker; id <= 200u + CELLS; id++) {
                u64 epoch = 0u;
                u32 size = 0u;
                BreakReplicationObject obj;
                if (!break_cell_read(g_cells[c], id, NULL, 0u, &size, &epoch)) continue;
                memset(&obj, 0, sizeof obj);
                obj.entity_id = id;
                obj.position[0] = id == walker ? x : 10.0f * (f32)(id - 200u) + 5.0f;
                ASSERT_TRUE(break_spatial_index_insert(index, &obj));
                (void)break_cell_route_observe(route, id, c, epoch);
            }
            ASSERT_TRUE(break_aoi_compute(index, &wit, 1u, NULL, &res));
            for (usize i = 0; i < res.enter_count; i++) ids[n++] = res.enter[i];
            for (usize i = 0; i < res.stay_count; i++) ids[n++] = res.stay[i];
            ASSERT_TRUE(break_cell_view_report(view, c, ids, n));
            break_aoi_result_clear(&res);
            break_spatial_index_destroy(index);
        }
        ASSERT_TRUE(tick(view, &e));
        if (t == 0u) ASSERT_EQ(e.enter_count, 1u + CELLS);
        else ASSERT_EQ(e.enter_count, 0u);
        ASSERT_EQ(e.leave_count, 0u);
        ASSERT_TRUE(break_cell_view_is_visible(view, walker));

        /* input for the walker goes where the gateway routes it */
        {
            u32 cell = 0u;
            ASSERT_TRUE(break_cell_route_lookup(route, walker, &cell, NULL));
            input_sent++;
            if (break_cell_is_authoritative(g_cells[cell], walker)) input_ok++;
            for (u32 c = 0; c < CELLS; c++)
                if (break_cell_is_authoritative(g_cells[c], walker) && c != owner) {
                    owner = c;
                    handoffs_seen++;
                }
        }
    }
    ASSERT_EQ(owner, 2u);
    ASSERT_EQ(handoffs_seen, 2u);
    /* input can only miss while the walker is in flight between cells */
    ASSERT_TRUE(input_ok + 2u * 4u >= input_sent);
    {
        u32 cell = 0u;
        ASSERT_TRUE(break_cell_route_lookup(route, walker, &cell, NULL));
        ASSERT_EQ(cell, 2u);
    }
    for (u32 c = 0; c < CELLS; c++) break_cell_destroy(g_cells[c]);
    break_cell_route_destroy(route);
    break_cell_view_destroy(view);
}

TEST_MAIN_BEGIN()
    RUN_TEST(view_is_the_union_of_cell_reports);
    RUN_TEST(an_entity_leaves_only_after_the_grace_period);
    RUN_TEST(view_rejects_bad_reports_without_changing);
    RUN_TEST(route_follows_the_highest_epoch);
    RUN_TEST(a_walker_stays_visible_and_reachable_across_handoffs);
TEST_MAIN_END()
