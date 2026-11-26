/* Reliable per-epoch broadcast: every reader sees every published snapshot
 * in order, the log refuses or evicts when a reader falls `capacity` behind,
 * and leases outlive the log. */
#include "test_framework.h"
#include <core/platform_thread.h>
#include <ecs/world_snapshot_log.h>

#include <stdatomic.h>
#include <string.h>

#define COMP_COUNTER 12u
#define THREAD_EPOCHS 2000u
#define THREAD_SPIN_LIMIT 50000000u

typedef struct {
    u32 value;
} Counter;

static BreakComponentSchemaRegistry *make_schemas(void) {
    BreakComponentSchemaRegistry *schemas = break_schema_registry_create();
    BreakComponentSchema schema;
    memset(&schema, 0, sizeof schema);
    schema.component_id = COMP_COUNTER;
    schema.version = 1u;
    schema.size = sizeof(Counter);
    schema.alignment = _Alignof(Counter);
    schema.flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES;
    if (!schemas) return NULL;
    if (break_schema_register(schemas, &schema) != BREAK_SCHEMA_OK) {
        break_schema_registry_destroy(schemas);
        return NULL;
    }
    return schemas;
}

typedef struct {
    BreakComponentSchemaRegistry *schemas;
    World *world;
    Entity entity;
} Source;

static bool source_init(Source *s) {
    s->schemas = make_schemas();
    s->world = world_create();
    if (!s->schemas || !s->world) return false;
    world_register_component(s->world, COMP_COUNTER, sizeof(Counter));
    s->entity = world_create_entity(s->world);
    return world_add_component(s->world, s->entity, COMP_COUNTER) != NULL;
}

static void source_dispose(Source *s) {
    world_destroy(s->world);
    break_schema_registry_destroy(s->schemas);
}

/* A snapshot at `tick` whose counter equals the tick. */
static BreakWorldSnapshot *snap(Source *s, u64 tick) {
    ((Counter *)world_get_component(s->world, s->entity, COMP_COUNTER))->value = (u32)tick;
    return break_world_snapshot_build(s->world, s->schemas, tick);
}

static u32 counter_of(const BreakWorldSnapshotLogLease *lease, Entity e) {
    const void *bytes = NULL;
    usize size = 0u;
    if (!break_world_snapshot_component_bytes(lease->snapshot, e, COMP_COUNTER, &bytes, &size) ||
        size != sizeof(Counter)) {
        return 0xffffffffu;
    }
    return ((const Counter *)bytes)->value;
}

static BreakWorldSnapshotLogConfig config_for(const Source *s, u32 capacity, bool evict) {
    BreakWorldSnapshotLogConfig cfg;
    memset(&cfg, 0, sizeof cfg);
    cfg.schema_hash = break_schema_hash(s->schemas);
    cfg.capacity = capacity;
    cfg.max_readers = 4u;
    cfg.evict_slow_readers = evict;
    return cfg;
}

static BreakWorldSnapshotLogResult publish_tick(BreakWorldSnapshotLog *log, Source *s, u64 tick,
                                                u64 *epoch) {
    BreakWorldSnapshot *snapshot = snap(s, tick);
    BreakWorldSnapshotLogResult r = break_world_snapshot_log_publish(log, snapshot, epoch);
    break_world_snapshot_release(snapshot);
    return r;
}

static void expect_read(BreakWorldSnapshotLog *log, BreakWorldSnapshotReaderId reader,
                        const Source *s, u64 epoch, u32 value) {
    BreakWorldSnapshotLogLease lease;
    ASSERT_EQ(break_world_snapshot_log_read(log, reader, &lease), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_EQ(lease.epoch, epoch);
    ASSERT_EQ(counter_of(&lease, s->entity), value);
    break_world_snapshot_log_lease_release(&lease);
    ASSERT_TRUE(lease.snapshot == NULL);
}

TEST(every_reader_sees_every_epoch_in_order) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId a = 99u;
    BreakWorldSnapshotReaderId b = 99u;
    BreakWorldSnapshotLogLease lease;
    u64 epoch = 0u;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 8u, false);
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_NOT_NULL(log);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &a));
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &b));
    ASSERT_TRUE(a != b);
    ASSERT_EQ(break_world_snapshot_log_read(log, a, &lease), BREAK_WORLD_SNAPSHOT_LOG_EMPTY);
    for (u64 t = 1u; t <= 5u; ++t) {
        ASSERT_EQ(publish_tick(log, &s, t * 10u, &epoch), BREAK_WORLD_SNAPSHOT_LOG_OK);
        ASSERT_EQ(epoch, t);
    }
    ASSERT_EQ(break_world_snapshot_log_backlog(log, a), 5u);
    for (u64 e = 1u; e <= 5u; ++e) expect_read(log, a, &s, e, (u32)(e * 10u));
    ASSERT_EQ(break_world_snapshot_log_read(log, a, &lease), BREAK_WORLD_SNAPSHOT_LOG_EMPTY);
    ASSERT_TRUE(lease.snapshot == NULL);
    ASSERT_EQ(lease.epoch, 0u);
    ASSERT_EQ(break_world_snapshot_log_backlog(log, a), 0u);
    /* b reads interleaved with new publishes and still misses nothing */
    expect_read(log, b, &s, 1u, 10u);
    ASSERT_EQ(publish_tick(log, &s, 60u, &epoch), BREAK_WORLD_SNAPSHOT_LOG_OK);
    for (u64 e = 2u; e <= 6u; ++e) expect_read(log, b, &s, e, (u32)(e * 10u));
    expect_read(log, a, &s, 6u, 60u);
    {
        BreakWorldSnapshotLogStats st;
        break_world_snapshot_log_stats(log, &st);
        ASSERT_EQ(st.published, 6u);
        ASSERT_EQ(st.delivered, 12u);
        ASSERT_EQ(st.retained, 6u); /* the oldest goes only when a publish needs its slot */
        ASSERT_EQ(st.readers, 2u);
        ASSERT_EQ(st.refused_full, 0u);
    }
    break_world_snapshot_log_destroy(log);
    source_dispose(&s);
}

TEST(a_slow_reader_makes_publish_refuse_without_losing_anything) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId fast;
    BreakWorldSnapshotReaderId slow;
    BreakWorldSnapshotLogStats st;
    u64 epoch = 77u;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 3u, false);
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &fast));
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &slow));
    for (u64 t = 1u; t <= 3u; ++t) {
        ASSERT_EQ(publish_tick(log, &s, t, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
        expect_read(log, fast, &s, t, (u32)t);
    }
    ASSERT_EQ(publish_tick(log, &s, 4u, &epoch), BREAK_WORLD_SNAPSHOT_LOG_FULL);
    ASSERT_EQ(epoch, 77u);
    ASSERT_EQ(publish_tick(log, &s, 4u, NULL), BREAK_WORLD_SNAPSHOT_LOG_FULL);
    break_world_snapshot_log_stats(log, &st);
    ASSERT_EQ(st.refused_full, 2u);
    ASSERT_EQ(st.retained, 3u);
    expect_read(log, slow, &s, 1u, 1u);
    /* one slot freed: the retry gets the next epoch, not a skipped one */
    ASSERT_EQ(publish_tick(log, &s, 4u, &epoch), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_EQ(epoch, 4u);
    for (u64 e = 2u; e <= 4u; ++e) expect_read(log, slow, &s, e, (u32)e);
    expect_read(log, fast, &s, 4u, 4u);
    break_world_snapshot_log_destroy(log);
    source_dispose(&s);
}

TEST(eviction_drops_the_slow_reader_and_tells_it_once) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId fast;
    BreakWorldSnapshotReaderId slow;
    BreakWorldSnapshotLogLease lease;
    BreakWorldSnapshotLogStats st;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 2u, true);
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &fast));
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &slow));
    for (u64 t = 1u; t <= 5u; ++t) {
        ASSERT_EQ(publish_tick(log, &s, t, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
        expect_read(log, fast, &s, t, (u32)t);
        break_world_snapshot_log_stats(log, &st);
        /* evicted by the first publish that needs epoch 1's slot (tick 3) */
        ASSERT_EQ(st.evicted_readers, t >= 3u ? 1u : 0u);
    }
    break_world_snapshot_log_stats(log, &st);
    ASSERT_EQ(st.evicted_readers, 1u); /* counted once, not per dropped epoch */
    ASSERT_EQ(st.retained, 2u);
    /* an evicted reader's backlog is what it will read after LAGGED */
    ASSERT_EQ(break_world_snapshot_log_backlog(log, slow), 2u);
    memset(&lease, 0xab, sizeof lease);
    ASSERT_EQ(break_world_snapshot_log_read(log, slow, &lease), BREAK_WORLD_SNAPSHOT_LOG_LAGGED);
    ASSERT_TRUE(lease.snapshot == NULL);
    /* after LAGGED the reader resumes at the oldest retained epoch */
    expect_read(log, slow, &s, 4u, 4u);
    expect_read(log, slow, &s, 5u, 5u);
    ASSERT_EQ(break_world_snapshot_log_read(log, slow, &lease), BREAK_WORLD_SNAPSHOT_LOG_EMPTY);
    ASSERT_EQ(publish_tick(log, &s, 6u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    expect_read(log, slow, &s, 6u, 6u);
    expect_read(log, fast, &s, 6u, 6u);
    break_world_snapshot_log_stats(log, &st);
    ASSERT_EQ(st.evicted_readers, 1u);
    break_world_snapshot_log_destroy(log);
    source_dispose(&s);
}

TEST(a_reader_added_later_starts_at_the_next_epoch) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId first;
    BreakWorldSnapshotReaderId late;
    BreakWorldSnapshotLogLease lease;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 4u, false);
    log = break_world_snapshot_log_create(&cfg);
    /* with no reader, nothing waits: publish never fills the log */
    for (u64 t = 1u; t <= 10u; ++t) ASSERT_EQ(publish_tick(log, &s, t, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &first));
    ASSERT_EQ(break_world_snapshot_log_read(log, first, &lease), BREAK_WORLD_SNAPSHOT_LOG_EMPTY);
    ASSERT_EQ(publish_tick(log, &s, 11u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &late));
    expect_read(log, first, &s, 11u, 11u);
    ASSERT_EQ(break_world_snapshot_log_read(log, late, &lease), BREAK_WORLD_SNAPSHOT_LOG_EMPTY);
    ASSERT_EQ(publish_tick(log, &s, 12u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    expect_read(log, late, &s, 12u, 12u);
    expect_read(log, first, &s, 12u, 12u);
    break_world_snapshot_log_destroy(log);
    source_dispose(&s);
}

TEST(removing_a_reader_releases_what_it_held_back) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId a;
    BreakWorldSnapshotReaderId b;
    BreakWorldSnapshotReaderId c;
    BreakWorldSnapshotLogLease lease;
    BreakWorldSnapshotLogStats st;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 2u, false);
    cfg.max_readers = 2u;
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &a));
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &b));
    ASSERT_FALSE(break_world_snapshot_log_add_reader(log, &c)); /* max_readers */
    ASSERT_EQ(publish_tick(log, &s, 1u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_EQ(publish_tick(log, &s, 2u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    expect_read(log, a, &s, 1u, 1u);
    expect_read(log, a, &s, 2u, 2u);
    ASSERT_EQ(publish_tick(log, &s, 3u, NULL), BREAK_WORLD_SNAPSHOT_LOG_FULL);
    ASSERT_TRUE(break_world_snapshot_log_remove_reader(log, b));
    ASSERT_FALSE(break_world_snapshot_log_remove_reader(log, b));
    break_world_snapshot_log_stats(log, &st);
    ASSERT_EQ(st.retained, 2u);
    ASSERT_EQ(st.readers, 1u);
    ASSERT_EQ(break_world_snapshot_log_read(log, b, &lease), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    ASSERT_EQ(break_world_snapshot_log_backlog(log, b), 0u);
    ASSERT_EQ(publish_tick(log, &s, 3u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    /* the freed id can be reused, and the new reader starts fresh */
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &c));
    ASSERT_EQ(break_world_snapshot_log_read(log, c, &lease), BREAK_WORLD_SNAPSHOT_LOG_EMPTY);
    expect_read(log, a, &s, 3u, 3u);
    break_world_snapshot_log_destroy(log);
    source_dispose(&s);
}

TEST(publish_validates_schema_tick_and_arguments) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId r;
    BreakWorldSnapshot *zero;
    BreakWorldSnapshotLogStats st;
    BreakWorldSnapshotLogLease lease;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 4u, false);
    ASSERT_TRUE(break_world_snapshot_log_create(NULL) == NULL);
    cfg.capacity = 0u;
    ASSERT_TRUE(break_world_snapshot_log_create(&cfg) == NULL);
    cfg.capacity = BREAK_WORLD_SNAPSHOT_LOG_MAX_CAPACITY + 1u;
    ASSERT_TRUE(break_world_snapshot_log_create(&cfg) == NULL);
    cfg = config_for(&s, 4u, false);
    cfg.max_readers = 0u;
    ASSERT_TRUE(break_world_snapshot_log_create(&cfg) == NULL);
    cfg.max_readers = BREAK_WORLD_SNAPSHOT_LOG_MAX_READERS + 1u;
    ASSERT_TRUE(break_world_snapshot_log_create(&cfg) == NULL);
    cfg = config_for(&s, BREAK_WORLD_SNAPSHOT_LOG_MAX_CAPACITY, false);
    cfg.max_readers = BREAK_WORLD_SNAPSHOT_LOG_MAX_READERS;
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_NOT_NULL(log);
    break_world_snapshot_log_destroy(log);
    cfg = config_for(&s, 4u, false);
    cfg.schema_hash ^= 1u;
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_EQ(publish_tick(log, &s, 1u, NULL), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    break_world_snapshot_log_destroy(log);
    cfg = config_for(&s, 4u, false);
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &r));
    zero = snap(&s, 0u);
    ASSERT_EQ(break_world_snapshot_log_publish(log, zero, NULL), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    break_world_snapshot_release(zero);
    ASSERT_EQ(publish_tick(log, &s, 5u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_EQ(publish_tick(log, &s, 5u, NULL), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    ASSERT_EQ(publish_tick(log, &s, 4u, NULL), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    ASSERT_EQ(break_world_snapshot_log_publish(log, NULL, NULL), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    ASSERT_EQ(break_world_snapshot_log_publish(NULL, NULL, NULL), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    break_world_snapshot_log_stats(log, &st);
    ASSERT_EQ(st.published, 1u);
    memset(&lease, 0xab, sizeof lease);
    ASSERT_EQ(break_world_snapshot_log_read(log, r + 1000u, &lease), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    ASSERT_TRUE(lease.snapshot == NULL);
    ASSERT_EQ(lease.epoch, 0u);
    memset(&lease, 0xab, sizeof lease);
    ASSERT_EQ(break_world_snapshot_log_read(NULL, r, &lease), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    ASSERT_TRUE(lease.snapshot == NULL);
    ASSERT_EQ(break_world_snapshot_log_read(log, r, NULL), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    ASSERT_EQ(break_world_snapshot_log_read(NULL, r, &lease), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    ASSERT_FALSE(break_world_snapshot_log_add_reader(log, NULL));
    ASSERT_FALSE(break_world_snapshot_log_add_reader(NULL, &r));
    ASSERT_FALSE(break_world_snapshot_log_remove_reader(NULL, r));
    ASSERT_EQ(break_world_snapshot_log_backlog(NULL, r), 0u);
    break_world_snapshot_log_stats(NULL, &st);
    break_world_snapshot_log_stats(log, NULL);
    break_world_snapshot_log_lease_release(NULL);
    expect_read(log, r, &s, 1u, 5u);
    break_world_snapshot_log_destroy(log);
    break_world_snapshot_log_destroy(NULL);
    source_dispose(&s);
}

TEST(peek_and_advance_consume_only_on_commit) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId r;
    BreakWorldSnapshotLogLease lease;
    BreakWorldSnapshotLogStats st;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 4u, false);
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &r));
    ASSERT_EQ(break_world_snapshot_log_peek(log, r, &lease), BREAK_WORLD_SNAPSHOT_LOG_EMPTY);
    ASSERT_FALSE(break_world_snapshot_log_advance(log, r, 1u)); /* nothing published yet */
    ASSERT_EQ(publish_tick(log, &s, 3u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_EQ(publish_tick(log, &s, 4u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    for (u32 i = 0u; i < 2u; ++i) { /* peeking twice yields the same epoch */
        ASSERT_EQ(break_world_snapshot_log_peek(log, r, &lease), BREAK_WORLD_SNAPSHOT_LOG_OK);
        ASSERT_EQ(lease.epoch, 1u);
        ASSERT_EQ(counter_of(&lease, s.entity), 3u);
        break_world_snapshot_log_lease_release(&lease);
    }
    ASSERT_EQ(break_world_snapshot_log_backlog(log, r), 2u);
    ASSERT_FALSE(break_world_snapshot_log_advance(log, r, 2u)); /* not the peeked epoch */
    ASSERT_FALSE(break_world_snapshot_log_advance(log, r + 1u, 1u));
    ASSERT_FALSE(break_world_snapshot_log_advance(NULL, r, 1u));
    ASSERT_TRUE(break_world_snapshot_log_advance(log, r, 1u));
    ASSERT_FALSE(break_world_snapshot_log_advance(log, r, 1u)); /* only once */
    ASSERT_EQ(break_world_snapshot_log_backlog(log, r), 1u);
    break_world_snapshot_log_stats(log, &st);
    ASSERT_EQ(st.delivered, 1u);
    expect_read(log, r, &s, 2u, 4u);
    memset(&lease, 0xab, sizeof lease);
    ASSERT_EQ(break_world_snapshot_log_peek(log, r + 1u, &lease), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    ASSERT_TRUE(lease.snapshot == NULL);
    ASSERT_EQ(break_world_snapshot_log_peek(log, r, NULL), BREAK_WORLD_SNAPSHOT_LOG_INVALID);
    break_world_snapshot_log_destroy(log);
    source_dispose(&s);
}

TEST(peek_reports_lagged_and_resumes_like_read) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId fast;
    BreakWorldSnapshotReaderId slow;
    BreakWorldSnapshotLogLease lease;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 2u, true);
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &fast));
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &slow));
    for (u64 t = 1u; t <= 4u; ++t) {
        ASSERT_EQ(publish_tick(log, &s, t, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
        expect_read(log, fast, &s, t, (u32)t);
    }
    ASSERT_EQ(break_world_snapshot_log_peek(log, slow, &lease), BREAK_WORLD_SNAPSHOT_LOG_LAGGED);
    ASSERT_EQ(break_world_snapshot_log_peek(log, slow, &lease), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_EQ(lease.epoch, 3u);
    break_world_snapshot_log_lease_release(&lease);
    /* evicted again before committing: advance refuses, peek says LAGGED */
    ASSERT_EQ(publish_tick(log, &s, 5u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    expect_read(log, fast, &s, 5u, 5u);
    ASSERT_EQ(publish_tick(log, &s, 6u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_FALSE(break_world_snapshot_log_advance(log, slow, 3u));
    ASSERT_EQ(break_world_snapshot_log_peek(log, slow, &lease), BREAK_WORLD_SNAPSHOT_LOG_LAGGED);
    ASSERT_EQ(break_world_snapshot_log_peek(log, slow, &lease), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_EQ(lease.epoch, 5u);
    ASSERT_TRUE(break_world_snapshot_log_advance(log, slow, lease.epoch));
    break_world_snapshot_log_lease_release(&lease);
    expect_read(log, slow, &s, 6u, 6u);
    break_world_snapshot_log_destroy(log);
    source_dispose(&s);
}

TEST(a_lease_outlives_the_log) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId r;
    BreakWorldSnapshotLogLease lease;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 4u, false);
    log = break_world_snapshot_log_create(&cfg);
    ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &r));
    ASSERT_EQ(publish_tick(log, &s, 9u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_EQ(publish_tick(log, &s, 10u, NULL), BREAK_WORLD_SNAPSHOT_LOG_OK);
    ASSERT_EQ(break_world_snapshot_log_read(log, r, &lease), BREAK_WORLD_SNAPSHOT_LOG_OK);
    break_world_snapshot_log_destroy(log); /* epoch 2 is still unread: released here */
    world_destroy(s.world);
    s.world = NULL;
    ASSERT_EQ(lease.epoch, 1u);
    ASSERT_EQ(break_world_snapshot_tick(lease.snapshot), 9u);
    break_world_snapshot_log_lease_release(&lease);
    break_schema_registry_destroy(s.schemas);
}

typedef struct {
    BreakWorldSnapshotLog *log;
    BreakWorldSnapshotReaderId reader;
    Entity entity;
    atomic_bool done;
    u64 seen;
    bool in_order;
} ThreadReader;

static PLATFORM_THREAD_RET run_reader(PLATFORM_THREAD_ARG argument) {
    ThreadReader *tr = (ThreadReader *)argument;
    tr->in_order = true;
    for (u32 spin = 0u; spin < THREAD_SPIN_LIMIT && tr->seen < THREAD_EPOCHS; ++spin) {
        BreakWorldSnapshotLogLease lease;
        BreakWorldSnapshotLogResult r = break_world_snapshot_log_read(tr->log, tr->reader, &lease);
        if (r == BREAK_WORLD_SNAPSHOT_LOG_EMPTY) {
            platform_thread_yield();
            continue;
        }
        if (r != BREAK_WORLD_SNAPSHOT_LOG_OK || lease.epoch != tr->seen + 1u ||
            counter_of(&lease, tr->entity) != (u32)lease.epoch) {
            tr->in_order = false;
            break_world_snapshot_log_lease_release(&lease);
            break;
        }
        tr->seen = lease.epoch;
        break_world_snapshot_log_lease_release(&lease);
    }
    atomic_store_explicit(&tr->done, true, memory_order_release);
    return PLATFORM_THREAD_RETURN;
}

/* Two reader threads against one publishing thread through a small log:
 * the producer is refused often, and each reader still gets all epochs. */
TEST(threaded_readers_receive_every_epoch_through_a_small_log) {
    Source s;
    BreakWorldSnapshotLogConfig cfg;
    BreakWorldSnapshotLog *log;
    ThreadReader readers[2];
    PlatformThread threads[2];
    BreakWorldSnapshotLogStats st;
    u64 t = 1u;
    ASSERT_TRUE(source_init(&s));
    cfg = config_for(&s, 4u, false);
    log = break_world_snapshot_log_create(&cfg);
    for (u32 i = 0u; i < 2u; ++i) {
        memset(&readers[i], 0, sizeof readers[i]);
        readers[i].log = log;
        readers[i].entity = s.entity;
        atomic_init(&readers[i].done, false);
        ASSERT_TRUE(break_world_snapshot_log_add_reader(log, &readers[i].reader));
    }
    for (u32 i = 0u; i < 2u; ++i) ASSERT_TRUE(platform_thread_create(&threads[i], run_reader, &readers[i]));
    for (u32 spin = 0u; spin < THREAD_SPIN_LIMIT && t <= THREAD_EPOCHS; ++spin) {
        BreakWorldSnapshotLogResult r = publish_tick(log, &s, t, NULL);
        if (r == BREAK_WORLD_SNAPSHOT_LOG_OK) {
            t++;
        } else {
            ASSERT_EQ(r, BREAK_WORLD_SNAPSHOT_LOG_FULL);
            platform_thread_yield();
        }
    }
    for (u32 i = 0u; i < 2u; ++i) platform_thread_join(threads[i]);
    ASSERT_EQ(t, THREAD_EPOCHS + 1u);
    for (u32 i = 0u; i < 2u; ++i) {
        ASSERT_TRUE(atomic_load_explicit(&readers[i].done, memory_order_acquire));
        ASSERT_TRUE(readers[i].in_order);
        ASSERT_EQ(readers[i].seen, (u64)THREAD_EPOCHS);
    }
    break_world_snapshot_log_stats(log, &st);
    ASSERT_EQ(st.published, (u64)THREAD_EPOCHS);
    ASSERT_EQ(st.delivered, 2u * THREAD_EPOCHS);
    ASSERT_EQ(st.evicted_readers, 0u);
    break_world_snapshot_log_destroy(log);
    source_dispose(&s);
}

TEST_MAIN_BEGIN()
    RUN_TEST(every_reader_sees_every_epoch_in_order);
    RUN_TEST(a_slow_reader_makes_publish_refuse_without_losing_anything);
    RUN_TEST(eviction_drops_the_slow_reader_and_tells_it_once);
    RUN_TEST(a_reader_added_later_starts_at_the_next_epoch);
    RUN_TEST(removing_a_reader_releases_what_it_held_back);
    RUN_TEST(publish_validates_schema_tick_and_arguments);
    RUN_TEST(peek_and_advance_consume_only_on_commit);
    RUN_TEST(peek_reports_lagged_and_resumes_like_read);
    RUN_TEST(a_lease_outlives_the_log);
    RUN_TEST(threaded_readers_receive_every_epoch_through_a_small_log);
TEST_MAIN_END()
