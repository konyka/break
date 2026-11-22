/* Load-based cell assignment: cells are ordered along a Hilbert curve and
 * that order is cut into one contiguous segment per server so that the
 * busiest server carries as little load as possible. Rebalancing is only
 * proposed when the current assignment is clearly worse than the best one. */
#include "test_framework.h"
#include <network/break_cell_balance.h>
#include <network/break_cell_partition.h>
#include <stdlib.h>
#include <string.h>

static BreakCellPartition grid(u32 columns, u32 rows) {
    BreakCellPartition p;
    memset(&p, 0, sizeof p);
    (void)break_cell_partition_init(&p, 0.0f, 0.0f, 10.0f, columns, rows);
    return p;
}

static u32 manhattan(const BreakCellPartition *p, u32 a, u32 b) {
    i32 ax = (i32)(a % p->columns), az = (i32)(a / p->columns);
    i32 bx = (i32)(b % p->columns), bz = (i32)(b / p->columns);
    return (u32)(abs(ax - bx) + abs(az - bz));
}

TEST(hilbert_order_visits_every_cell_once_through_neighbours) {
    static const u32 sizes[][2] = {{1u, 1u}, {2u, 2u}, {4u, 4u}, {8u, 8u}, {16u, 16u}};
    for (u32 s = 0; s < sizeof sizes / sizeof sizes[0]; s++) {
        BreakCellPartition p = grid(sizes[s][0], sizes[s][1]);
        u32 n = break_cell_partition_cell_count(&p);
        u32 order[256];
        u8 seen[256];
        memset(seen, 0, sizeof seen);
        ASSERT_EQ(break_cell_hilbert_order(&p, order, 256u), n);
        for (u32 i = 0; i < n; i++) {
            ASSERT_TRUE(order[i] < n);
            ASSERT_EQ(seen[order[i]], 0u);
            seen[order[i]] = 1u;
            if (i > 0u) ASSERT_EQ(manhattan(&p, order[i - 1u], order[i]), 1u);
        }
    }
    /* non-square and non-power-of-two grids still visit every cell once */
    BreakCellPartition q = grid(5u, 3u);
    u32 order[64];
    u8 seen[64];
    memset(seen, 0, sizeof seen);
    ASSERT_EQ(break_cell_hilbert_order(&q, order, 64u), 15u);
    for (u32 i = 0; i < 15u; i++) {
        ASSERT_TRUE(order[i] < 15u);
        ASSERT_EQ(seen[order[i]], 0u);
        seen[order[i]] = 1u;
    }
    ASSERT_EQ(break_cell_hilbert_order(&q, order, 14u), 0u); /* too small */
    ASSERT_EQ(break_cell_hilbert_order(NULL, order, 64u), 0u);
}

/* For each server, the cells it got must be one run of the Hilbert order. */
static bool segments_contiguous(const BreakCellPartition *p, const u32 *assign, u32 servers) {
    u32 order[256];
    u32 n = break_cell_hilbert_order(p, order, 256u);
    u8 done[64];
    memset(done, 0, sizeof done);
    u32 prev = UINT32_MAX;
    for (u32 i = 0; i < n; i++) {
        u32 s = assign[order[i]];
        if (s >= servers) return false;
        if (s != prev) {
            if (done[s]) return false; /* server reappears after another one */
            if (prev != UINT32_MAX) done[prev] = 1u;
            prev = s;
        }
    }
    return true;
}

static u64 max_server_load(const u32 *load, const u32 *assign, u32 cells, u32 servers) {
    u64 per[64];
    memset(per, 0, sizeof per);
    for (u32 c = 0; c < cells; c++) per[assign[c]] += load[c];
    u64 m = 0u;
    for (u32 s = 0; s < servers; s++) m = per[s] > m ? per[s] : m;
    return m;
}

/* the best achievable maximum over every way to cut the order */
static u64 brute_force(const u32 *ordered_load, u32 n, u32 servers) {
    if (servers == 1u || n == 0u) {
        u64 sum = 0u;
        for (u32 i = 0; i < n; i++) sum += ordered_load[i];
        return sum;
    }
    u64 best = UINT64_MAX;
    u64 head = 0u;
    for (u32 k = 0; k <= n; k++) {
        if (k > 0u) head += ordered_load[k - 1u];
        u64 rest = brute_force(ordered_load + k, n - k, servers - 1u);
        u64 m = head > rest ? head : rest;
        if (m < best) best = m;
    }
    return best;
}

TEST(assignment_is_contiguous_and_optimal) {
    u64 rng = 99u;
    for (u32 round = 0; round < 300u; round++) {
        u32 columns = 1u + (u32)(round % 4u);
        u32 rows = 1u + (u32)((round / 4u) % 3u);
        BreakCellPartition p = grid(columns, rows);
        u32 n = break_cell_partition_cell_count(&p);
        u32 servers = 1u + (u32)(round % 4u);
        u32 load[16];
        for (u32 c = 0; c < n; c++) {
            rng = rng * 6364136223846793005ull + 1442695040888963407ull;
            load[c] = (u32)(rng >> 33) % 50u;
            if (round % 7u == 0u && c % 3u == 0u) load[c] = 0u;
        }
        u32 assign[16];
        u64 got = 0u;
        ASSERT_TRUE(break_cell_balance(&p, load, servers, assign, &got));
        ASSERT_TRUE(segments_contiguous(&p, assign, servers));
        ASSERT_EQ(max_server_load(load, assign, n, servers), got);
        u32 order[16];
        u32 ordered[16];
        ASSERT_EQ(break_cell_hilbert_order(&p, order, 16u), n);
        for (u32 i = 0; i < n; i++) ordered[i] = load[order[i]];
        ASSERT_EQ(got, brute_force(ordered, n, servers));
    }
}

TEST(a_hot_spot_gets_a_server_to_itself) {
    BreakCellPartition p = grid(4u, 4u);
    u32 load[16];
    for (u32 c = 0; c < 16u; c++) load[c] = 1u;
    load[5] = 100u;
    u32 assign[16];
    u64 max_load = 0u;
    ASSERT_TRUE(break_cell_balance(&p, load, 4u, assign, &max_load));
    ASSERT_EQ(max_load, 100u);
    for (u32 c = 0; c < 16u; c++)
        if (c != 5u) ASSERT_TRUE(assign[c] != assign[5]);
}

TEST(more_servers_than_cells_and_bad_arguments) {
    BreakCellPartition p = grid(2u, 1u);
    u32 load[2] = {3u, 4u};
    u32 assign[2];
    u64 m = 0u;
    ASSERT_TRUE(break_cell_balance(&p, load, 5u, assign, &m));
    ASSERT_EQ(m, 4u);
    ASSERT_TRUE(assign[0] != assign[1]);
    ASSERT_TRUE(assign[0] < 5u && assign[1] < 5u);
    ASSERT_FALSE(break_cell_balance(&p, load, 0u, assign, &m));
    ASSERT_FALSE(break_cell_balance(NULL, load, 2u, assign, &m));
    ASSERT_FALSE(break_cell_balance(&p, NULL, 2u, assign, &m));
    ASSERT_FALSE(break_cell_balance(&p, load, 2u, NULL, &m));
    ASSERT_FALSE(break_cell_balance(&p, load, BREAK_CELL_BALANCE_MAX_SERVERS + 1u, assign, &m));
    ASSERT_TRUE(break_cell_balance(&p, load, 2u, assign, NULL));
    BreakCellPartition big = grid(128u, 128u); /* more cells than the planner handles */
    static u32 big_load[128u * 128u];
    static u32 big_assign[128u * 128u];
    ASSERT_FALSE(break_cell_balance(&big, big_load, 2u, big_assign, &m));
}

/* Rebalance only when the current busiest server carries more than `ratio`
 * times the best achievable maximum; small drifts keep the assignment. */
TEST(rebalance_is_proposed_only_past_the_ratio) {
    BreakCellPartition p = grid(4u, 4u);
    u32 load[16];
    for (u32 c = 0; c < 16u; c++) load[c] = 10u;
    u32 assign[16];
    ASSERT_TRUE(break_cell_balance(&p, load, 4u, assign, NULL));
    ASSERT_FALSE(break_cell_balance_needed(&p, load, assign, 4u, 1.25f));
    /* one server's cells grow by 20%: below the 1.25 ratio */
    u32 victim = assign[0];
    u32 drift[16];
    memcpy(drift, load, sizeof load);
    for (u32 c = 0; c < 16u; c++)
        if (assign[c] == victim) drift[c] = 12u;
    ASSERT_FALSE(break_cell_balance_needed(&p, drift, assign, 4u, 1.25f));
    /* they triple: the current maximum is far above the best one */
    for (u32 c = 0; c < 16u; c++)
        if (assign[c] == victim) drift[c] = 30u;
    ASSERT_TRUE(break_cell_balance_needed(&p, drift, assign, 4u, 1.25f));
    /* an assignment that names an unknown server always needs a rebalance */
    u32 bad[16];
    memcpy(bad, assign, sizeof assign);
    bad[3] = 9u;
    ASSERT_TRUE(break_cell_balance_needed(&p, load, bad, 4u, 1.25f));
    /* an idle world never needs one */
    u32 idle[16];
    memset(idle, 0, sizeof idle);
    ASSERT_FALSE(break_cell_balance_needed(&p, idle, assign, 4u, 1.25f));
    /* ratio 1 asks for a rebalance as soon as the current maximum is above
     * the best one, and never when the assignment is already optimal */
    ASSERT_TRUE(break_cell_balance_needed(&p, drift, assign, 4u, 1.0f));
    u32 best[16];
    ASSERT_TRUE(break_cell_balance(&p, drift, 4u, best, NULL));
    ASSERT_FALSE(break_cell_balance_needed(&p, drift, best, 4u, 1.0f));
    /* a 30% skew: needed at ratio 1.25, not at 1.5 */
    u32 skew[16];
    memcpy(skew, load, sizeof load);
    for (u32 c = 0; c < 16u; c++)
        if (assign[c] == victim) skew[c] = 13u;
    ASSERT_TRUE(break_cell_balance_needed(&p, skew, assign, 4u, 1.0f));
    ASSERT_FALSE(break_cell_balance_needed(&p, skew, assign, 4u, 1.5f));
    ASSERT_FALSE(break_cell_balance_needed(NULL, load, assign, 4u, 1.25f));
    ASSERT_FALSE(break_cell_balance_needed(&p, load, assign, 4u, 0.5f)); /* ratio < 1 is invalid */
}

TEST_MAIN_BEGIN()
    RUN_TEST(hilbert_order_visits_every_cell_once_through_neighbours);
    RUN_TEST(assignment_is_contiguous_and_optimal);
    RUN_TEST(a_hot_spot_gets_a_server_to_itself);
    RUN_TEST(more_servers_than_cells_and_bad_arguments);
    RUN_TEST(rebalance_is_proposed_only_past_the_ratio);
TEST_MAIN_END()
