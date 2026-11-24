#include "test_framework.h"
#include <core/platform_thread.h>
#include <ecs/world_snapshot_publication.h>

#include <stdatomic.h>

#define COMP_POSITION 11u
#define RACE_ROUNDS 128u
#define RACE_SPIN_LIMIT 1000000u

typedef struct {
    float x;
    float y;
    float z;
} Position;

static BreakComponentSchemaRegistry *make_schemas(void) {
    BreakComponentSchemaRegistry *schemas = break_schema_registry_create();
    BreakComponentSchema schema = {
        .component_id = COMP_POSITION,
        .version = 1u,
        .size = sizeof(Position),
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };
    if (!schemas) return NULL;
    if (break_schema_register(schemas, &schema) != BREAK_SCHEMA_OK) {
        break_schema_registry_destroy(schemas);
        return NULL;
    }
    return schemas;
}

static World *make_world(float x, Entity *out_entity) {
    World *world = world_create();
    if (!world) return NULL;
    world_register_component(world, COMP_POSITION, sizeof(Position));
    Entity entity = world_create_entity(world);
    Position *position = (Position *)world_add_component(world, entity, COMP_POSITION);
    if (!position) {
        world_destroy(world);
        return NULL;
    }
    position->x = x;
    position->y = 2.0f;
    position->z = 3.0f;
    *out_entity = entity;
    return world;
}

static void assert_position(const BreakWorldSnapshotLease *lease, Entity entity,
                            float expected_x) {
    const void *bytes = NULL;
    usize size = 0u;
    ASSERT_TRUE(break_world_snapshot_component_bytes(lease->snapshot, entity,
                                                     COMP_POSITION, &bytes, &size));
    ASSERT_EQ(size, sizeof(Position));
    ASSERT_FLOAT_EQ(((const Position *)bytes)->x, expected_x, 1e-6f);
    ASSERT_FLOAT_EQ(((const Position *)bytes)->y, 2.0f, 1e-6f);
    ASSERT_FLOAT_EQ(((const Position *)bytes)->z, 3.0f, 1e-6f);
}

static void assert_current(BreakWorldSnapshotPublication *publication,
                           BreakWorldSnapshot *snapshot, u64 level, u64 epoch) {
    BreakWorldSnapshotLease lease = {0};
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    ASSERT_TRUE(lease.snapshot == snapshot);
    ASSERT_EQ(lease.level_generation, level);
    ASSERT_EQ(lease.publication_epoch, epoch);
    break_world_snapshot_lease_release(&lease);
}

TEST(create_empty_and_null_arguments_are_safe) {
    BreakWorldSnapshotPublicationConfig config = {0u, 0u};
    BreakWorldSnapshotLease lease = {0};
    ASSERT_TRUE(break_world_snapshot_publication_create(NULL) == NULL);
    ASSERT_EQ(break_world_snapshot_publication_acquire(NULL, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_INVALID);
    break_world_snapshot_publication_close(NULL);
    break_world_snapshot_publication_destroy(NULL);
    break_world_snapshot_lease_release(NULL);

    BreakWorldSnapshotPublication *publication =
        break_world_snapshot_publication_create(&config);
    ASSERT_NOT_NULL(publication);
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, NULL),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_INVALID);
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_EMPTY);
    ASSERT_FALSE(break_world_snapshot_publication_publish(NULL, NULL, 0u));
    ASSERT_FALSE(break_world_snapshot_publication_publish(publication, NULL, 0u));
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_EMPTY);
    break_world_snapshot_publication_close(publication);
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED);
    break_world_snapshot_publication_close(publication);
    break_world_snapshot_publication_destroy(publication);
}

TEST(old_lease_survives_world_mutation_replace_close_and_destroy) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    Entity entity;
    World *world = make_world(10.0f, &entity);
    BreakWorldSnapshotPublicationConfig config = {
        break_schema_hash(schemas), 0u
    };
    BreakWorldSnapshotPublication *publication =
        break_world_snapshot_publication_create(&config);
    ASSERT_NOT_NULL(publication);
    BreakWorldSnapshotLease lease = {0};
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_EMPTY);

    BreakWorldSnapshot *first = break_world_snapshot_build(world, schemas, 10u);
    ASSERT_NOT_NULL(first);
    ASSERT_TRUE(break_world_snapshot_publication_publish(publication, first, 0u));
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    ASSERT_TRUE(lease.snapshot == first);
    ASSERT_EQ(lease.level_generation, 0u);
    ASSERT_EQ(lease.publication_epoch, 1u);
    assert_position(&lease, entity, 10.0f);
    break_world_snapshot_release(first);

    Position *live_position = (Position *)world_get_component(world, entity, COMP_POSITION);
    ASSERT_NOT_NULL(live_position);
    live_position->x = 99.0f;
    assert_position(&lease, entity, 10.0f);

    BreakWorldSnapshot *second = break_world_snapshot_build(world, schemas, 11u);
    ASSERT_NOT_NULL(second);
    ASSERT_TRUE(break_world_snapshot_publication_publish(publication, second, 0u));
    assert_current(publication, second, 0u, 2u);
    assert_position(&lease, entity, 10.0f);

    break_world_snapshot_publication_close(publication);
    BreakWorldSnapshotLease closed_lease = {0};
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &closed_lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED);
    break_world_snapshot_publication_destroy(publication);
    assert_position(&lease, entity, 10.0f);

    break_world_snapshot_lease_release(&lease);
    ASSERT_TRUE(lease.snapshot == NULL);
    ASSERT_EQ(lease.level_generation, 0u);
    ASSERT_EQ(lease.publication_epoch, 0u);
    break_world_snapshot_lease_release(&lease);
    break_world_snapshot_release(second);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST(admission_failures_preserve_current_level_and_epoch) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    BreakComponentSchemaRegistry *changed_schemas = break_schema_registry_create();
    BreakComponentSchema changed_schema = {
        .component_id = COMP_POSITION,
        .version = 2u,
        .size = sizeof(Position),
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };
    ASSERT_NOT_NULL(changed_schemas);
    ASSERT_EQ(break_schema_register(changed_schemas, &changed_schema), BREAK_SCHEMA_OK);
    Entity entity;
    World *world = make_world(5.0f, &entity);
    BreakWorldSnapshotPublicationConfig config = {
        break_schema_hash(schemas), 7u
    };
    BreakWorldSnapshotPublication *publication =
        break_world_snapshot_publication_create(&config);
    ASSERT_NOT_NULL(publication);

    BreakWorldSnapshot *current = break_world_snapshot_build(world, schemas, 20u);
    BreakWorldSnapshot *wrong_schema =
        break_world_snapshot_build(world, changed_schemas, 30u);
    BreakWorldSnapshot *zero_tick = break_world_snapshot_build(world, schemas, 0u);
    BreakWorldSnapshot *same_tick = break_world_snapshot_build(world, schemas, 20u);
    BreakWorldSnapshot *lower_tick = break_world_snapshot_build(world, schemas, 19u);
    BreakWorldSnapshot *later = break_world_snapshot_build(world, schemas, 100u);
    ASSERT_NOT_NULL(current);
    ASSERT_NOT_NULL(wrong_schema);
    ASSERT_NOT_NULL(zero_tick);
    ASSERT_NOT_NULL(same_tick);
    ASSERT_NOT_NULL(lower_tick);
    ASSERT_NOT_NULL(later);
    ASSERT_TRUE(break_world_snapshot_publication_publish(publication, current, 7u));

    ASSERT_FALSE(break_world_snapshot_publication_publish(publication, wrong_schema, 8u));
    assert_current(publication, current, 7u, 1u);
    ASSERT_FALSE(break_world_snapshot_publication_publish(publication, zero_tick, 8u));
    assert_current(publication, current, 7u, 1u);
    ASSERT_FALSE(break_world_snapshot_publication_publish(publication, same_tick, 7u));
    assert_current(publication, current, 7u, 1u);
    ASSERT_FALSE(break_world_snapshot_publication_publish(publication, lower_tick, 7u));
    assert_current(publication, current, 7u, 1u);
    ASSERT_FALSE(break_world_snapshot_publication_publish(publication, later, 6u));
    assert_current(publication, current, 7u, 1u);

    BreakWorldSnapshotLease old_lease = {0};
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &old_lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    break_world_snapshot_publication_close(publication);
    ASSERT_FALSE(break_world_snapshot_publication_publish(publication, later, 8u));
    ASSERT_TRUE(old_lease.snapshot == current);
    ASSERT_EQ(old_lease.level_generation, 7u);
    ASSERT_EQ(old_lease.publication_epoch, 1u);
    assert_position(&old_lease, entity, 5.0f);
    BreakWorldSnapshotLease closed_lease = {0};
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &closed_lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED);

    break_world_snapshot_publication_destroy(publication);
    break_world_snapshot_lease_release(&old_lease);
    break_world_snapshot_release(later);
    break_world_snapshot_release(lower_tick);
    break_world_snapshot_release(same_tick);
    break_world_snapshot_release(zero_tick);
    break_world_snapshot_release(wrong_schema);
    break_world_snapshot_release(current);
    world_destroy(world);
    break_schema_registry_destroy(changed_schemas);
    break_schema_registry_destroy(schemas);
}

TEST(higher_level_allows_same_tick_same_pointer_and_lower_tick) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    Entity entity;
    World *world = make_world(8.0f, &entity);
    BreakWorldSnapshotPublicationConfig config = {
        break_schema_hash(schemas), 0u
    };
    BreakWorldSnapshotPublication *publication =
        break_world_snapshot_publication_create(&config);
    ASSERT_NOT_NULL(publication);
    BreakWorldSnapshot *first = break_world_snapshot_build(world, schemas, 50u);
    BreakWorldSnapshot *second = break_world_snapshot_build(world, schemas, 1u);
    ASSERT_NOT_NULL(first);
    ASSERT_NOT_NULL(second);

    ASSERT_TRUE(break_world_snapshot_publication_publish(publication, first, 0u));
    assert_current(publication, first, 0u, 1u);
    ASSERT_TRUE(break_world_snapshot_publication_publish(publication, first, 1u));
    assert_current(publication, first, 1u, 2u);
    ASSERT_TRUE(break_world_snapshot_publication_publish(publication, second, 2u));
    assert_current(publication, second, 2u, 3u);

    break_world_snapshot_publication_close(publication);
    break_world_snapshot_publication_destroy(publication);
    break_world_snapshot_release(second);
    break_world_snapshot_release(first);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

typedef struct {
    BreakWorldSnapshotPublication *publication;
    BreakWorldSnapshot *snapshot;
    atomic_uint ready;
    atomic_bool start;
    BreakWorldSnapshotAcquireResult result;
    BreakWorldSnapshotLease lease;
    bool passed;
} CloseAcquireRace;

static bool wait_for_atomic_uint(atomic_uint *value) {
    for (u32 spin = 0u; spin < RACE_SPIN_LIMIT; ++spin) {
        if (atomic_load_explicit(value, memory_order_acquire) != 0u) return true;
        platform_thread_yield();
    }
    return false;
}

static bool wait_for_atomic_bool(atomic_bool *value) {
    for (u32 spin = 0u; spin < RACE_SPIN_LIMIT; ++spin) {
        if (atomic_load_explicit(value, memory_order_acquire)) return true;
        platform_thread_yield();
    }
    return false;
}

static PLATFORM_THREAD_RET run_close_acquire_race(PLATFORM_THREAD_ARG argument) {
    CloseAcquireRace *race = (CloseAcquireRace *)argument;
    atomic_store_explicit(&race->ready, 1u, memory_order_release);
    if (!wait_for_atomic_bool(&race->start)) return PLATFORM_THREAD_RETURN;

    race->result = break_world_snapshot_publication_acquire(race->publication,
                                                            &race->lease);
    if (race->result == BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED) {
        race->passed = true;
    } else if (race->result == BREAK_WORLD_SNAPSHOT_ACQUIRE_OK) {
        race->passed = race->lease.snapshot == race->snapshot &&
                       race->lease.level_generation == 0u &&
                       race->lease.publication_epoch == 1u &&
                       break_world_snapshot_tick(race->lease.snapshot) == 7u &&
                       break_world_snapshot_entity_count(race->lease.snapshot) == 1u;
    }
    return PLATFORM_THREAD_RETURN;
}

TEST(platform_thread_close_and_acquire_race_returns_only_valid_lease_or_closed) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    Entity entity;
    World *world = make_world(42.0f, &entity);
    BreakWorldSnapshot *snapshot = break_world_snapshot_build(world, schemas, 7u);
    ASSERT_NOT_NULL(snapshot);
    BreakWorldSnapshotPublicationConfig config = {
        break_schema_hash(schemas), 0u
    };

    for (u32 round = 0u; round < RACE_ROUNDS; ++round) {
        CloseAcquireRace race;
        memset(&race, 0, sizeof(race));
        race.snapshot = snapshot;
        race.publication = break_world_snapshot_publication_create(&config);
        ASSERT_NOT_NULL(race.publication);
        ASSERT_TRUE(break_world_snapshot_publication_publish(race.publication,
                                                             snapshot, 0u));
        atomic_init(&race.ready, 0u);
        atomic_init(&race.start, false);

        PlatformThread thread;
        ASSERT_TRUE(platform_thread_create(&thread, run_close_acquire_race, &race));
        bool ready = wait_for_atomic_uint(&race.ready);
        atomic_store_explicit(&race.start, true, memory_order_release);
        break_world_snapshot_publication_close(race.publication);
        platform_thread_join(thread);
        ASSERT_TRUE(ready);
        ASSERT_TRUE(race.passed);

        BreakWorldSnapshotLease after_close = {0};
        ASSERT_EQ(break_world_snapshot_publication_acquire(race.publication,
                                                           &after_close),
                  BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED);
        break_world_snapshot_publication_destroy(race.publication);
        if (race.result == BREAK_WORLD_SNAPSHOT_ACQUIRE_OK) {
            ASSERT_EQ(break_world_snapshot_tick(race.lease.snapshot), 7u);
        }
        break_world_snapshot_lease_release(&race.lease);
    }

    break_world_snapshot_release(snapshot);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_empty_and_null_arguments_are_safe);
    RUN_TEST(old_lease_survives_world_mutation_replace_close_and_destroy);
    RUN_TEST(admission_failures_preserve_current_level_and_epoch);
    RUN_TEST(higher_level_allows_same_tick_same_pointer_and_lower_tick);
    RUN_TEST(platform_thread_close_and_acquire_race_returns_only_valid_lease_or_closed);
TEST_MAIN_END()
