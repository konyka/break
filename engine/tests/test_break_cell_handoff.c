/* Cross-cell authority handoff: a cell offers an entity to a neighbour,
 * keeps authority until the neighbour accepts, then gives it up and sends
 * the final state in a commit; the neighbour becomes the owner on commit.
 * Retransmission and abort make the exchange survive lost, duplicated and
 * reordered messages, and at no point do two cells hold authority. */
#include "test_framework.h"
#include <network/break_cell_handoff.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CELLS 4u
#define NET_CAP 4096u

typedef struct {
    BreakCellMsg msgs[NET_CAP];
    u32 due[NET_CAP]; /* step at which each queued message is delivered */
    u32 count;
    u32 now;
    u64 rng;
    u32 drop_percent;
    u32 dup_percent;
    u32 max_delay; /* extra steps a message may wait, chosen per copy */
    bool reorder;
    u64 sent;
} Net;

static Net g_net;
static BreakCell *g_cells[MAX_CELLS];

static u32 net_rand(Net *n) {
    n->rng = n->rng * 6364136223846793005ull + 1442695040888963407ull;
    return (u32)(n->rng >> 33);
}

static void net_send(void *user, const BreakCellMsg *msg) {
    Net *n = (Net *)user;
    n->sent++;
    if (n->drop_percent && net_rand(n) % 100u < n->drop_percent) return;
    u32 copies = (n->dup_percent && n->count + 1u < NET_CAP && net_rand(n) % 100u < n->dup_percent) ? 2u : 1u;
    for (u32 c = 0; c < copies && n->count < NET_CAP; c++) {
        n->due[n->count] = n->now + (n->max_delay ? net_rand(n) % (n->max_delay + 1u) : 0u);
        n->msgs[n->count++] = *msg;
    }
}

/* Delivers the messages that are due (messages sent while delivering wait
 * for the next call), in random order when reordering, then advances the
 * clock. */
static void net_deliver(Net *n) {
    static BreakCellMsg batch[NET_CAP];
    u32 count = 0u;
    u32 kept = 0u;
    for (u32 i = 0; i < n->count; i++) {
        if (n->due[i] <= n->now) {
            batch[count++] = n->msgs[i];
        } else {
            n->msgs[kept] = n->msgs[i];
            n->due[kept] = n->due[i];
            kept++;
        }
    }
    n->count = kept;
    if (n->reorder) {
        for (u32 i = count; i > 1u; i--) {
            u32 j = net_rand(n) % i;
            BreakCellMsg t = batch[i - 1u];
            batch[i - 1u] = batch[j];
            batch[j] = t;
        }
    }
    for (u32 i = 0; i < count; i++) {
        u32 to = batch[i].to_cell;
        if (to < MAX_CELLS && g_cells[to]) break_cell_receive(g_cells[to], &batch[i]);
    }
    n->now++;
}

static bool g_hold_outbox;

static BreakCellConfig cell_config(u32 id, u32 capacity) {
    BreakCellConfig cfg;
    memset(&cfg, 0, sizeof cfg);
    cfg.cell_id = id;
    cfg.capacity = capacity;
    cfg.retransmit_ticks = 2u;
    cfg.offer_timeout_ticks = 10u;
    cfg.send = net_send;
    cfg.user = &g_net;
    cfg.hold_outbox = g_hold_outbox;
    return cfg;
}

static void make_cells(u32 count, u32 capacity) {
    memset(&g_net, 0, sizeof g_net);
    g_net.rng = 12345u;
    for (u32 i = 0; i < MAX_CELLS; i++) g_cells[i] = NULL;
    for (u32 i = 0; i < count; i++) {
        BreakCellConfig cfg = cell_config(i, capacity);
        g_cells[i] = break_cell_create(&cfg);
    }
}

static void free_cells(void) {
    for (u32 i = 0; i < MAX_CELLS; i++) {
        break_cell_destroy(g_cells[i]);
        g_cells[i] = NULL;
    }
}

static void step(void) {
    net_deliver(&g_net);
    for (u32 i = 0; i < MAX_CELLS; i++)
        if (g_cells[i]) break_cell_tick(g_cells[i]);
}

static u32 authority_count(u64 entity, i32 *holder) {
    u32 n = 0u;
    for (u32 i = 0; i < MAX_CELLS; i++) {
        if (g_cells[i] && break_cell_is_authoritative(g_cells[i], entity)) {
            n++;
            if (holder) *holder = (i32)i;
        }
    }
    return n;
}

static u64 read_counter(BreakCell *cell, u64 entity, u64 *epoch) {
    u64 value = 0u;
    u32 size = 0u;
    if (!break_cell_read(cell, entity, &value, sizeof value, &size, epoch) || size != sizeof value) return ~0ull;
    return value;
}

TEST(spawn_write_and_read_on_the_owner) {
    make_cells(2u, 4u);
    ASSERT_NOT_NULL(g_cells[0]);
    u64 v = 7u;
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 100u, &v, sizeof v));
    ASSERT_FALSE(break_cell_spawn(g_cells[0], 100u, &v, sizeof v)); /* already present */
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 100u), BREAK_CELL_ENTITY_OWNED);
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 100u), BREAK_CELL_ENTITY_NONE);
    ASSERT_TRUE(break_cell_is_authoritative(g_cells[0], 100u));
    u64 epoch = 0u;
    ASSERT_EQ(read_counter(g_cells[0], 100u, &epoch), 7u);
    ASSERT_EQ(epoch, 1u);
    v = 8u;
    ASSERT_TRUE(break_cell_write(g_cells[0], 100u, &v, sizeof v));
    ASSERT_FALSE(break_cell_write(g_cells[1], 100u, &v, sizeof v));
    ASSERT_EQ(read_counter(g_cells[0], 100u, NULL), 8u);
    u8 big[BREAK_CELL_STATE_MAX + 1u];
    memset(big, 0, sizeof big);
    ASSERT_FALSE(break_cell_write(g_cells[0], 100u, big, sizeof big));
    ASSERT_FALSE(break_cell_spawn(g_cells[0], 101u, big, sizeof big));
    ASSERT_FALSE(break_cell_spawn(g_cells[0], 101u, NULL, 4u));
    /* capacity is bounded */
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 101u, &v, sizeof v));
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 102u, &v, sizeof v));
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 103u, &v, sizeof v));
    ASSERT_FALSE(break_cell_spawn(g_cells[0], 104u, &v, sizeof v));
    ASSERT_EQ(break_cell_entity_count(g_cells[0]), 4u);
    BreakCellConfig bad;
    memset(&bad, 0, sizeof bad);
    ASSERT_EQ(break_cell_create(&bad), NULL); /* no send function, no capacity */
    ASSERT_EQ(break_cell_create(NULL), NULL);
    free_cells();
}

TEST(clean_handoff_moves_authority_and_the_latest_state) {
    make_cells(2u, 4u);
    u64 v = 1u;
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 5u, &v, sizeof v));
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 5u, 1u));
    ASSERT_FALSE(break_cell_begin_handoff(g_cells[0], 5u, 1u)); /* already offering */
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 5u), BREAK_CELL_ENTITY_OFFERING);
    /* still the authority while offering: writes land and travel with the commit */
    v = 2u;
    ASSERT_TRUE(break_cell_write(g_cells[0], 5u, &v, sizeof v));
    net_deliver(&g_net); /* OFFER -> B */
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 5u), BREAK_CELL_ENTITY_RECEIVING);
    ASSERT_EQ(authority_count(5u, NULL), 1u);
    v = 3u;
    ASSERT_TRUE(break_cell_write(g_cells[0], 5u, &v, sizeof v));
    net_deliver(&g_net); /* ACCEPT -> A: A gives up authority and sends COMMIT */
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 5u), BREAK_CELL_ENTITY_COMMITTING);
    ASSERT_FALSE(break_cell_write(g_cells[0], 5u, &v, sizeof v));
    ASSERT_EQ(authority_count(5u, NULL), 0u);
    net_deliver(&g_net); /* COMMIT -> B */
    i32 holder = -1;
    ASSERT_EQ(authority_count(5u, &holder), 1u);
    ASSERT_EQ(holder, 1);
    u64 epoch = 0u;
    ASSERT_EQ(read_counter(g_cells[1], 5u, &epoch), 3u);
    ASSERT_EQ(epoch, 2u);
    net_deliver(&g_net); /* COMMIT_ACK -> A: record released */
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 5u), BREAK_CELL_ENTITY_NONE);
    ASSERT_EQ(break_cell_entity_count(g_cells[0]), 0u);
    BreakCellStats s;
    ASSERT_TRUE(break_cell_stats(g_cells[0], &s));
    ASSERT_EQ(s.handoffs_out, 1u);
    ASSERT_TRUE(break_cell_stats(g_cells[1], &s));
    ASSERT_EQ(s.handoffs_in, 1u);
    ASSERT_FALSE(break_cell_begin_handoff(g_cells[0], 5u, 1u)); /* not ours anymore */
    ASSERT_FALSE(break_cell_begin_handoff(g_cells[1], 5u, 1u)); /* to itself */
    free_cells();
}

TEST(a_full_neighbour_rejects_and_the_source_keeps_the_entity) {
    make_cells(2u, 1u);
    u64 v = 1u;
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 1u, &v, sizeof v));
    ASSERT_TRUE(break_cell_spawn(g_cells[1], 2u, &v, sizeof v));
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 1u, 1u));
    for (u32 i = 0; i < 4u; i++) step();
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 1u), BREAK_CELL_ENTITY_OWNED);
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 1u), BREAK_CELL_ENTITY_NONE);
    BreakCellStats s;
    ASSERT_TRUE(break_cell_stats(g_cells[0], &s));
    ASSERT_EQ(s.rejected, 1u);
    free_cells();
}

/* No answer within the timeout: the source aborts and keeps authority, and
 * a late ACCEPT for the aborted offer is answered with ABORT, so the
 * neighbour drops its pending record. */
TEST(timeout_aborts_and_a_late_accept_is_refused) {
    make_cells(2u, 4u);
    u64 v = 1u;
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 9u, &v, sizeof v));
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 9u, 1u));
    /* only A's offers get through: B's ACCEPTs and A's ABORT are lost */
    BreakCell *b = g_cells[1];
    for (u32 t = 0; t < 12u; t++) {
        u32 count = g_net.count;
        for (u32 i = 0; i < count; i++) {
            if (g_net.msgs[i].type == BREAK_CELL_MSG_OFFER) break_cell_receive(b, &g_net.msgs[i]);
        }
        g_net.count = 0u;
        break_cell_tick(g_cells[0]);
        break_cell_tick(b);
    }
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 9u), BREAK_CELL_ENTITY_OWNED);
    ASSERT_TRUE(break_cell_is_authoritative(g_cells[0], 9u));
    ASSERT_EQ(break_cell_entity_state(b, 9u), BREAK_CELL_ENTITY_RECEIVING);
    BreakCellStats s;
    ASSERT_TRUE(break_cell_stats(g_cells[0], &s));
    ASSERT_EQ(s.aborted, 1u);
    ASSERT_TRUE(s.retransmits > 0u);
    /* now let everything through: B's retransmitted ACCEPT meets the abort */
    for (u32 i = 0; i < 6u; i++) step();
    ASSERT_EQ(break_cell_entity_state(b, 9u), BREAK_CELL_ENTITY_NONE);
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 9u), BREAK_CELL_ENTITY_OWNED);
    u64 epoch = 0u;
    ASSERT_EQ(read_counter(g_cells[0], 9u, &epoch), 1u);
    ASSERT_EQ(epoch, 1u);
    /* and a fresh handoff still works */
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 9u, 1u));
    for (u32 i = 0; i < 6u; i++) step();
    ASSERT_EQ(break_cell_entity_state(b, 9u), BREAK_CELL_ENTITY_OWNED);
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 9u), BREAK_CELL_ENTITY_NONE);
    free_cells();
}

/* An entity handed straight back: the new owner's offer, at the new epoch,
 * stands in for a lost COMMIT_ACK. */
TEST(handing_back_before_the_ack_arrives) {
    make_cells(2u, 4u);
    u64 v = 4u;
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 3u, &v, sizeof v));
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 3u, 1u));
    net_deliver(&g_net); /* OFFER */
    net_deliver(&g_net); /* ACCEPT */
    net_deliver(&g_net); /* COMMIT */
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 3u), BREAK_CELL_ENTITY_OWNED);
    g_net.count = 0u;    /* the COMMIT_ACK is lost */
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 3u), BREAK_CELL_ENTITY_COMMITTING);
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[1], 3u, 0u));
    for (u32 i = 0; i < 8u; i++) step();
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 3u), BREAK_CELL_ENTITY_OWNED);
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 3u), BREAK_CELL_ENTITY_NONE);
    u64 epoch = 0u;
    ASSERT_EQ(read_counter(g_cells[0], 3u, &epoch), 4u);
    ASSERT_EQ(epoch, 3u);
    free_cells();
}

TEST(malformed_messages_are_ignored) {
    make_cells(2u, 4u);
    u64 v = 1u;
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 1u, &v, sizeof v));
    BreakCellMsg m;
    memset(&m, 0, sizeof m);
    m.type = BREAK_CELL_MSG_COMMIT; /* commit nobody offered */
    m.from_cell = 0u;
    m.to_cell = 1u;
    m.entity = 1u;
    m.epoch = 2u;
    m.txn = 77u;
    m.state_size = sizeof v;
    memcpy(m.state, &v, sizeof v);
    break_cell_receive(g_cells[1], &m);
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 1u), BREAK_CELL_ENTITY_NONE);
    m.type = BREAK_CELL_MSG_OFFER;
    m.state_size = BREAK_CELL_STATE_MAX + 1u;
    break_cell_receive(g_cells[1], &m);
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 1u), BREAK_CELL_ENTITY_NONE);
    m.state_size = 0u;
    m.to_cell = 0u; /* addressed to someone else */
    break_cell_receive(g_cells[1], &m);
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 1u), BREAK_CELL_ENTITY_NONE);
    m.to_cell = 1u;
    m.type = 200u;
    break_cell_receive(g_cells[1], &m);
    m.type = BREAK_CELL_MSG_ACCEPT; /* accept for an offer A never made */
    m.from_cell = 1u;
    m.to_cell = 0u;
    break_cell_receive(g_cells[0], &m);
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 1u), BREAK_CELL_ENTITY_OWNED);
    break_cell_receive(g_cells[0], NULL);
    break_cell_receive(NULL, &m);
    BreakCellStats s;
    ASSERT_TRUE(break_cell_stats(g_cells[1], &s));
    ASSERT_EQ(s.ignored, 4u);
    free_cells();
}

/* Random handoffs and writes among four cells over a network that drops,
 * duplicates and reorders. At every step at most one cell is authoritative
 * for each entity and authority epochs only grow; once the network heals,
 * every entity has exactly one owner, nothing is in flight, and each
 * entity's counter equals the number of writes that were accepted. */
static u64 g_chaos_handoffs;
static u64 g_chaos_aborts;

static void run_chaos(u64 seed, u32 drop, u32 dup, u32 delay, bool reorder, u32 *out_violation) {
    make_cells(MAX_CELLS, 16u);
    g_net.rng = seed;
    g_net.drop_percent = drop;
    g_net.dup_percent = dup;
    g_net.max_delay = delay;
    g_net.reorder = reorder;
    enum { ENTITIES = 12 };
    u64 accepted[ENTITIES];
    u64 last_epoch[ENTITIES];
    for (u32 e = 0; e < ENTITIES; e++) {
        u64 zero = 0u;
        accepted[e] = 0u;
        last_epoch[e] = 1u;
        (void)break_cell_spawn(g_cells[e % MAX_CELLS], 1000u + e, &zero, sizeof zero);
    }
    *out_violation = 0u;
    for (u32 t = 0; t < 3000u && *out_violation == 0u; t++) {
        if (t == 2400u) {
            g_net.drop_percent = 0u;
            g_net.dup_percent = 0u;
        }
        if (t == 2700u) g_net.max_delay = 0u;
        for (u32 e = 0; e < ENTITIES; e++) {
            u64 id = 1000u + e;
            i32 holder = -1;
            u32 n = authority_count(id, &holder);
            if (n > 1u) *out_violation = 1u;
            if (n == 1u && t < 2400u) {
                u64 epoch = 0u;
                u64 cur = read_counter(g_cells[holder], id, &epoch);
                if (epoch < last_epoch[e]) *out_violation = 2u;
                last_epoch[e] = epoch;
                if (net_rand(&g_net) % 3u == 0u) {
                    u64 next = cur + 1u;
                    if (break_cell_write(g_cells[holder], id, &next, sizeof next)) accepted[e]++;
                }
                if (net_rand(&g_net) % 7u == 0u) {
                    u32 to = net_rand(&g_net) % MAX_CELLS;
                    (void)break_cell_begin_handoff(g_cells[holder], id, to);
                }
            }
        }
        step();
    }
    for (u32 e = 0; e < ENTITIES && *out_violation == 0u; e++) {
        u64 id = 1000u + e;
        i32 holder = -1;
        if (authority_count(id, &holder) != 1u) {
            *out_violation = 3u;
            break;
        }
        if (break_cell_entity_state(g_cells[holder], id) != BREAK_CELL_ENTITY_OWNED) *out_violation = 4u;
        for (u32 c = 0; c < MAX_CELLS; c++)
            if ((i32)c != holder && break_cell_entity_state(g_cells[c], id) != BREAK_CELL_ENTITY_NONE)
                *out_violation = 5u;
        if (read_counter(g_cells[holder], id, NULL) != accepted[e]) *out_violation = 6u;
    }
    for (u32 c = 0; c < MAX_CELLS; c++) {
        BreakCellStats s;
        if (break_cell_stats(g_cells[c], &s)) {
            g_chaos_handoffs += s.handoffs_in;
            g_chaos_aborts += s.aborted;
        }
    }
    free_cells();
}

TEST(chaos_keeps_a_single_authority_and_loses_nothing) {
    struct { u32 drop, dup, delay; bool reorder; } modes[] = {
        {0u, 0u, 0u, false}, {0u, 0u, 0u, true}, {20u, 0u, 0u, false}, {0u, 30u, 0u, true},
        {25u, 25u, 0u, true}, {0u, 30u, 12u, true}, {20u, 30u, 12u, true}, {10u, 50u, 30u, true}};
    for (u32 m = 0; m < sizeof modes / sizeof modes[0]; m++) {
        g_chaos_handoffs = 0u;
        g_chaos_aborts = 0u;
        for (u64 seed = 1u; seed <= 20u; seed++) {
            u32 violation = 0u;
            run_chaos(seed * 7919u + m, modes[m].drop, modes[m].dup, modes[m].delay, modes[m].reorder, &violation);
            if (violation) printf("    mode %u seed %llu violation %u\n", m, (unsigned long long)seed, violation);
            ASSERT_EQ(violation, 0u);
        }
        printf("    mode %u: %llu handoffs, %llu aborted offers\n", m, (unsigned long long)g_chaos_handoffs,
               (unsigned long long)g_chaos_aborts);
        /* the runs really move entities around */
        ASSERT_TRUE(g_chaos_handoffs > 500u);
    }
}

/* A's COMMIT_ACK is lost, B hands the entity on to C, and then a delayed
 * copy of A's original OFFER reaches B and creates a stale receiving
 * record. A, still waiting for its ack, answers that record's ACCEPT with
 * ABORT; that frees the record, so A's next COMMIT retransmit is
 * acknowledged and A is released. */
TEST(a_stale_offer_after_moving_on_does_not_wedge_the_old_source) {
    make_cells(3u, 4u);
    u64 v = 6u;
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 8u, &v, sizeof v));
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 8u, 1u));
    BreakCellMsg old_offer = g_net.msgs[0];
    ASSERT_EQ(old_offer.type, (u32)BREAK_CELL_MSG_OFFER);
    net_deliver(&g_net); /* OFFER -> B */
    net_deliver(&g_net); /* ACCEPT -> A */
    net_deliver(&g_net); /* COMMIT -> B */
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 8u), BREAK_CELL_ENTITY_OWNED);
    g_net.count = 0u;    /* the COMMIT_ACK is lost */
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[1], 8u, 2u));
    for (u32 i = 0; i < 4u; i++) {
        net_deliver(&g_net); /* B <-> C only: drop anything addressed to A */
        u32 kept = 0u;
        for (u32 k = 0; k < g_net.count; k++)
            if (g_net.msgs[k].to_cell != 0u) g_net.msgs[kept++] = g_net.msgs[k];
        g_net.count = kept;
    }
    ASSERT_EQ(break_cell_entity_state(g_cells[2], 8u), BREAK_CELL_ENTITY_OWNED);
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 8u), BREAK_CELL_ENTITY_NONE);
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 8u), BREAK_CELL_ENTITY_COMMITTING);
    break_cell_receive(g_cells[1], &old_offer); /* the delayed duplicate */
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 8u), BREAK_CELL_ENTITY_RECEIVING);
    for (u32 i = 0; i < 10u; i++) step();
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 8u), BREAK_CELL_ENTITY_NONE);
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 8u), BREAK_CELL_ENTITY_NONE);
    ASSERT_EQ(break_cell_entity_state(g_cells[2], 8u), BREAK_CELL_ENTITY_OWNED);
    i32 holder = -1;
    ASSERT_EQ(authority_count(8u, &holder), 1u);
    ASSERT_EQ(holder, 2);
    free_cells();
}

/* ---- crash recovery ---- */

#define SNAP_CAP 8192u

static u32 take_snapshot(BreakCell *cell, u8 *buf) {
    u32 size = 0u;
    if (!break_cell_snapshot(cell, buf, SNAP_CAP, &size)) return 0u;
    return size;
}

TEST(a_snapshot_restores_every_record_and_counter) {
    static u8 a[SNAP_CAP], b[SNAP_CAP];
    u64 v = 5u;
    g_hold_outbox = false;
    make_cells(3u, 8u);
    /* cell 0: one owned, one offering, one committing; cell 1 receiving */
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 1u, &v, sizeof v));
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 2u, &v, sizeof v));
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 3u, &v, sizeof v));
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 3u, 1u));
    net_deliver(&g_net); /* OFFER -> 1 */
    net_deliver(&g_net); /* ACCEPT -> 0: cell 0 commits entity 3 */
    g_net.count = 0u;    /* the COMMIT is lost: 1 keeps a receiving record */
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 2u, 2u));
    g_net.count = 0u;
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 3u), BREAK_CELL_ENTITY_COMMITTING);
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 2u), BREAK_CELL_ENTITY_OFFERING);
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 3u), BREAK_CELL_ENTITY_RECEIVING);
    v = 6u;
    ASSERT_TRUE(break_cell_write(g_cells[0], 1u, &v, sizeof v));
    /* one tick gives the in-flight records non-zero timing counters, which
     * the round trip below must keep */
    for (u32 c = 0; c < 2u; c++) break_cell_tick(g_cells[c]);
    g_net.count = 0u;

    for (u32 c = 0; c < 2u; c++) {
        u32 n = take_snapshot(g_cells[c], a);
        ASSERT_TRUE(n > 0u);
        ASSERT_EQ(n, break_cell_snapshot_size(g_cells[c]));
        BreakCellConfig cfg = cell_config(c, 8u);
        BreakCell *r = break_cell_restore(&cfg, a, n);
        ASSERT_NOT_NULL(r);
        /* restoring is lossless: the restored cell snapshots to the same bytes */
        ASSERT_EQ(take_snapshot(r, b), n);
        ASSERT_TRUE(memcmp(a, b, n) == 0);
        ASSERT_EQ(break_cell_entity_count(r), break_cell_entity_count(g_cells[c]));
        for (u64 e = 1u; e <= 3u; e++)
            ASSERT_EQ(break_cell_entity_state(r, e), break_cell_entity_state(g_cells[c], e));
        break_cell_destroy(g_cells[c]);
        g_cells[c] = r;
    }
    {
        u64 epoch = 0u;
        ASSERT_EQ(read_counter(g_cells[0], 1u, &epoch), 6u);
        ASSERT_EQ(epoch, 1u);
    }
    /* the restored cells finish both handoffs, and new transactions do not
     * reuse ids: the restored source's next offer is accepted normally */
    for (u32 i = 0; i < 40u; i++) step();
    ASSERT_EQ(break_cell_entity_state(g_cells[1], 3u), BREAK_CELL_ENTITY_OWNED);
    ASSERT_EQ(break_cell_entity_state(g_cells[0], 3u), BREAK_CELL_ENTITY_NONE);
    ASSERT_EQ(break_cell_entity_state(g_cells[2], 2u), BREAK_CELL_ENTITY_OWNED);
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 1u, 2u));
    for (u32 i = 0; i < 40u; i++) step();
    ASSERT_EQ(break_cell_entity_state(g_cells[2], 1u), BREAK_CELL_ENTITY_OWNED);
    ASSERT_EQ(read_counter(g_cells[2], 1u, NULL), 6u);
    free_cells();
}

/* Appends the snapshot's trailing FNV-1a hash over the first n bytes. */
static void reseal(u8 *buf, u32 n) {
    u64 h = 0xcbf29ce484222325ull;
    for (u32 i = 0; i < n; i++) {
        h ^= buf[i];
        h *= 0x100000001b3ull;
    }
    for (u32 i = 0; i < 8u; i++) buf[n + i] = (u8)(h >> (8u * i));
}

TEST(a_bad_snapshot_is_refused) {
    static u8 a[SNAP_CAP];
    u64 v = 1u;
    u32 n;
    BreakCellConfig cfg;
    g_hold_outbox = false;
    make_cells(2u, 4u);
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 1u, &v, sizeof v));
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 2u, &v, sizeof v));
    n = take_snapshot(g_cells[0], a);
    ASSERT_TRUE(n > 0u);
    cfg = cell_config(0u, 4u);
    for (u32 len = 0; len < n; len++) ASSERT_TRUE(break_cell_restore(&cfg, a, len) == NULL);
    for (u32 byte = 0; byte < n; byte++) {
        a[byte] ^= 0x10u;
        ASSERT_TRUE(break_cell_restore(&cfg, a, n) == NULL);
        a[byte] ^= 0x10u;
    }
    {
        BreakCell *ok = break_cell_restore(&cfg, a, n);
        ASSERT_NOT_NULL(ok);
        break_cell_destroy(ok);
    }
    /* well-formed hash, bad content: a duplicated record, a trailing byte */
    {
        static u8 forged[SNAP_CAP];
        const u32 header = 32u, record = 52u + (u32)sizeof v;
        u32 fn = n - 8u;
        memcpy(forged, a, fn);
        memcpy(forged + fn, a + header, record); /* the first record again */
        fn += record;
        forged[12] = 3u;                         /* record count */
        reseal(forged, fn);
        ASSERT_TRUE(break_cell_restore(&cfg, forged, fn + 8u) == NULL);
        memcpy(forged, a, n - 8u);
        forged[n - 8u] = 0u;
        reseal(forged, n - 7u);
        ASSERT_TRUE(break_cell_restore(&cfg, forged, n + 1u) == NULL);
        /* the helper itself reproduces a valid snapshot */
        memcpy(forged, a, n - 8u);
        reseal(forged, n - 8u);
        {
            BreakCell *ok = break_cell_restore(&cfg, forged, n);
            ASSERT_NOT_NULL(ok);
            break_cell_destroy(ok);
        }
    }
    cfg = cell_config(1u, 4u); /* another cell's snapshot */
    ASSERT_TRUE(break_cell_restore(&cfg, a, n) == NULL);
    cfg = cell_config(0u, 1u); /* two records do not fit */
    ASSERT_TRUE(break_cell_restore(&cfg, a, n) == NULL);
    cfg = cell_config(0u, 4u);
    cfg.send = NULL;
    ASSERT_TRUE(break_cell_restore(&cfg, a, n) == NULL);
    cfg = cell_config(0u, 4u);
    ASSERT_TRUE(break_cell_restore(&cfg, NULL, n) == NULL);
    ASSERT_TRUE(break_cell_restore(NULL, a, n) == NULL);
    {
        u32 size = 0u;
        ASSERT_FALSE(break_cell_snapshot(g_cells[0], a, n - 1u, &size));
        ASSERT_FALSE(break_cell_snapshot(g_cells[0], NULL, n, &size));
        ASSERT_FALSE(break_cell_snapshot(g_cells[0], a, n, NULL));
        ASSERT_FALSE(break_cell_snapshot(NULL, a, n, &size));
        ASSERT_EQ(break_cell_snapshot_size(NULL), 0u);
    }
    free_cells();
}

TEST(a_held_outbox_sends_only_on_flush) {
    u64 v = 1u;
    g_hold_outbox = true;
    make_cells(2u, 4u);
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 1u, &v, sizeof v));
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 1u, 1u));
    ASSERT_EQ(g_net.sent, 0u);
    ASSERT_EQ(break_cell_outbox_count(g_cells[0]), 1u);
    break_cell_tick(g_cells[0]);
    break_cell_tick(g_cells[0]); /* a retransmit joins the queue */
    ASSERT_EQ(break_cell_outbox_count(g_cells[0]), 2u);
    ASSERT_EQ(g_net.sent, 0u);
    ASSERT_EQ(break_cell_flush(g_cells[0]), 2u);
    ASSERT_EQ(g_net.sent, 2u);
    ASSERT_EQ(g_net.msgs[0].type, (u32)BREAK_CELL_MSG_OFFER);
    ASSERT_EQ(break_cell_outbox_count(g_cells[0]), 0u);
    ASSERT_EQ(break_cell_flush(g_cells[0]), 0u);
    ASSERT_EQ(break_cell_flush(NULL), 0u);
    ASSERT_EQ(break_cell_outbox_count(NULL), 0u);
    /* without hold_outbox nothing is queued */
    g_hold_outbox = false;
    free_cells();
    make_cells(2u, 4u);
    ASSERT_TRUE(break_cell_spawn(g_cells[0], 1u, &v, sizeof v));
    ASSERT_TRUE(break_cell_begin_handoff(g_cells[0], 1u, 1u));
    ASSERT_EQ(g_net.sent, 1u);
    ASSERT_EQ(break_cell_outbox_count(g_cells[0]), 0u);
    free_cells();
}

/* Chaos with crashes. After every step each cell either snapshots and then
 * flushes (snapshot_first, the documented order) or flushes and then
 * snapshots. A crash right after the flush restores the cell from its
 * latest snapshot. Writes made since that snapshot are lost, so the checks
 * are single authority, epochs never going back, settling to one owner, and
 * counters never exceeding the largest accepted write. */
static u32 run_crash_chaos(u64 seed, bool snapshot_first, u64 *out_crashes) {
    static u8 snaps[MAX_CELLS][SNAP_CAP];
    u32 snap_size[MAX_CELLS];
    enum { ENTITIES = 12 };
    u64 accepted[ENTITIES], last_epoch[ENTITIES];
    u32 violation = 0u;
    g_hold_outbox = true;
    make_cells(MAX_CELLS, 16u);
    g_net.rng = seed;
    g_net.drop_percent = 15u;
    g_net.dup_percent = 20u;
    g_net.max_delay = 8u;
    g_net.reorder = true;
    for (u32 e = 0; e < ENTITIES; e++) {
        u64 zero = 0u;
        accepted[e] = 0u;
        last_epoch[e] = 1u;
        (void)break_cell_spawn(g_cells[e % MAX_CELLS], 1000u + e, &zero, sizeof zero);
    }
    for (u32 c = 0; c < MAX_CELLS; c++) snap_size[c] = take_snapshot(g_cells[c], snaps[c]);
    for (u32 t = 0; t < 3000u && violation == 0u; t++) {
        if (t == 2400u) {
            g_net.drop_percent = 0u;
            g_net.dup_percent = 0u;
            g_net.max_delay = 0u;
        }
        for (u32 e = 0; e < ENTITIES; e++) {
            u64 id = 1000u + e;
            i32 holder = -1;
            u32 n = authority_count(id, &holder);
            if (n > 1u) violation = 1u;
            if (n == 1u && t < 2400u) {
                u64 epoch = 0u;
                u64 cur = read_counter(g_cells[holder], id, &epoch);
                if (epoch < last_epoch[e]) violation = 2u;
                if (cur > accepted[e]) violation = 7u;
                last_epoch[e] = epoch;
                if (net_rand(&g_net) % 3u == 0u) {
                    u64 next = cur + 1u;
                    if (break_cell_write(g_cells[holder], id, &next, sizeof next) && next > accepted[e])
                        accepted[e] = next;
                }
                if (net_rand(&g_net) % 7u == 0u)
                    (void)break_cell_begin_handoff(g_cells[holder], id, net_rand(&g_net) % MAX_CELLS);
            }
        }
        step();
        for (u32 c = 0; c < MAX_CELLS; c++) {
            bool crash = t < 2400u && net_rand(&g_net) % 100u < 3u;
            if (snapshot_first) snap_size[c] = take_snapshot(g_cells[c], snaps[c]);
            (void)break_cell_flush(g_cells[c]);
            if (crash) {
                /* the cell dies after sending; it comes back from its
                 * latest durable snapshot, which in the unsafe order
                 * predates what it just sent */
                BreakCellConfig cfg = cell_config(c, 16u);
                break_cell_destroy(g_cells[c]);
                g_cells[c] = break_cell_restore(&cfg, snaps[c], snap_size[c]);
                if (g_cells[c] == NULL) {
                    violation = 8u;
                    break;
                }
                (*out_crashes)++;
            }
            if (!snapshot_first) snap_size[c] = take_snapshot(g_cells[c], snaps[c]);
        }
    }
    for (u32 e = 0; e < ENTITIES && violation == 0u; e++) {
        u64 id = 1000u + e;
        i32 holder = -1;
        if (authority_count(id, &holder) != 1u) {
            violation = 3u;
            break;
        }
        if (break_cell_entity_state(g_cells[holder], id) != BREAK_CELL_ENTITY_OWNED) violation = 4u;
        for (u32 c = 0; c < MAX_CELLS; c++)
            if ((i32)c != holder && break_cell_entity_state(g_cells[c], id) != BREAK_CELL_ENTITY_NONE)
                violation = 5u;
        if (read_counter(g_cells[holder], id, NULL) > accepted[e]) violation = 7u;
    }
    free_cells();
    g_hold_outbox = false;
    return violation;
}

TEST(crashes_restored_from_snapshots_keep_a_single_authority) {
    u64 crashes = 0u;
    for (u64 seed = 1u; seed <= 40u; seed++) {
        u32 violation = run_crash_chaos(seed * 104729u, true, &crashes);
        if (violation) printf("    seed %llu violation %u\n", (unsigned long long)seed, violation);
        ASSERT_EQ(violation, 0u);
    }
    printf("    %llu crashes recovered\n", (unsigned long long)crashes);
    ASSERT_TRUE(crashes > 1000u);
}

/* The same crashes with the order reversed must break the invariant, which
 * shows the test can tell the two orders apart. */
TEST(flushing_before_the_snapshot_is_unsafe) {
    u64 crashes = 0u;
    u32 broken = 0u;
    for (u64 seed = 1u; seed <= 40u; seed++)
        if (run_crash_chaos(seed * 104729u, false, &crashes) != 0u) broken++;
    printf("    %u of 40 runs broke\n", broken);
    ASSERT_TRUE(broken > 0u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(spawn_write_and_read_on_the_owner);
    RUN_TEST(clean_handoff_moves_authority_and_the_latest_state);
    RUN_TEST(a_full_neighbour_rejects_and_the_source_keeps_the_entity);
    RUN_TEST(timeout_aborts_and_a_late_accept_is_refused);
    RUN_TEST(handing_back_before_the_ack_arrives);
    RUN_TEST(malformed_messages_are_ignored);
    RUN_TEST(a_stale_offer_after_moving_on_does_not_wedge_the_old_source);
    RUN_TEST(chaos_keeps_a_single_authority_and_loses_nothing);
    RUN_TEST(a_snapshot_restores_every_record_and_counter);
    RUN_TEST(a_bad_snapshot_is_refused);
    RUN_TEST(a_held_outbox_sends_only_on_flush);
    RUN_TEST(crashes_restored_from_snapshots_keep_a_single_authority);
    RUN_TEST(flushing_before_the_snapshot_is_unsafe);
TEST_MAIN_END()
