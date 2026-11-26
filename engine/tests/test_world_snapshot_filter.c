/* Per-connection AOI culling of a World snapshot: a filtered snapshot keeps
 * only the entities a predicate admits (e.g. the AOI scope of one
 * connection) and feeds the existing delta path unchanged. */
#include "test_framework.h"
#include <ecs/world_delta.h>
#include <ecs/world_snapshot.h>
#include <ecs/world_snapshot_test_hooks.h>
#include <network/break_aoi.h>

#include <string.h>

#define COMP_POSITION 11u

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
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES};
    if (!schemas) return NULL;
    if (break_schema_register(schemas, &schema) != BREAK_SCHEMA_OK) {
        break_schema_registry_destroy(schemas);
        return NULL;
    }
    return schemas;
}

static Entity spawn(World *world, float x) {
    Entity e = world_create_entity(world);
    Position *p = (Position *)world_add_component(world, e, COMP_POSITION);
    if (p) {
        p->x = x;
        p->y = 0.0f;
        p->z = 0.0f;
    }
    return e;
}

static bool keep_x_below(void *user, const BreakWorldSnapshot *snapshot, Entity entity) {
    const void *bytes = NULL;
    usize size = 0u;
    if (!break_world_snapshot_component_bytes(snapshot, entity, COMP_POSITION, &bytes, &size))
        return false;
    return ((const Position *)bytes)->x < *(const float *)user;
}

static bool keep_none(void *user, const BreakWorldSnapshot *snapshot, Entity entity) {
    (void)user;
    (void)snapshot;
    (void)entity;
    return false;
}

static float x_of(const BreakWorldSnapshot *s, Entity e) {
    const void *bytes = NULL;
    usize size = 0u;
    if (!break_world_snapshot_component_bytes(s, e, COMP_POSITION, &bytes, &size)) return -1.0f;
    return ((const Position *)bytes)->x;
}

TEST(filter_keeps_only_admitted_entities_and_their_bytes) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    World *world = world_create();
    Entity a, b, c;
    float limit = 5.0f;
    BreakWorldSnapshot *full;
    BreakWorldSnapshot *view;
    ASSERT_NOT_NULL(schemas);
    ASSERT_NOT_NULL(world);
    world_register_component(world, COMP_POSITION, sizeof(Position));
    a = spawn(world, 1.0f);
    b = spawn(world, 9.0f);
    c = spawn(world, 4.0f);
    full = break_world_snapshot_build(world, schemas, 7u);
    ASSERT_NOT_NULL(full);
    view = break_world_snapshot_filter(full, keep_x_below, &limit);
    ASSERT_NOT_NULL(view);
    ASSERT_EQ(break_world_snapshot_entity_count(view), 2u);
    ASSERT_TRUE(break_world_snapshot_has_entity(view, a));
    ASSERT_TRUE(!break_world_snapshot_has_entity(view, b));
    ASSERT_TRUE(break_world_snapshot_has_entity(view, c));
    ASSERT_FLOAT_EQ(x_of(view, a), 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(x_of(view, c), 4.0f, 1e-6f);
    ASSERT_EQ(break_world_snapshot_tick(view), 7u);
    ASSERT_EQ(break_world_snapshot_schema_hash(view), break_world_snapshot_schema_hash(full));
    ASSERT_NEQ(break_world_snapshot_hash(view), break_world_snapshot_hash(full));
    break_world_snapshot_release(full); /* the view owns its own copy */
    ASSERT_FLOAT_EQ(x_of(view, c), 4.0f, 1e-6f);
    break_world_snapshot_release(view);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST(filter_hash_matches_a_snapshot_built_from_the_same_entities) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    World *world = world_create();
    World *only = world_create();
    float limit = 5.0f;
    BreakWorldSnapshot *full;
    BreakWorldSnapshot *view;
    BreakWorldSnapshot *direct;
    ASSERT_NOT_NULL(schemas);
    ASSERT_NOT_NULL(world);
    ASSERT_NOT_NULL(only);
    world_register_component(world, COMP_POSITION, sizeof(Position));
    world_register_component(only, COMP_POSITION, sizeof(Position));
    (void)spawn(world, 1.0f);
    (void)spawn(only, 1.0f); /* same index/generation, same bytes */
    (void)spawn(world, 9.0f);
    full = break_world_snapshot_build(world, schemas, 3u);
    direct = break_world_snapshot_build(only, schemas, 3u);
    ASSERT_NOT_NULL(full);
    ASSERT_NOT_NULL(direct);
    view = break_world_snapshot_filter(full, keep_x_below, &limit);
    ASSERT_NOT_NULL(view);
    ASSERT_EQ(break_world_snapshot_hash(view), break_world_snapshot_hash(direct));
    ASSERT_EQ(break_world_snapshot_id(view), break_world_snapshot_id(direct));
    break_world_snapshot_release(direct);
    break_world_snapshot_release(view);
    break_world_snapshot_release(full);
    world_destroy(only);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST(filtered_views_diff_and_apply_like_full_snapshots) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    World *world = world_create();
    World *client = world_create();
    Entity near_e, far_e;
    float limit = 5.0f;
    BreakWorldSnapshot *s0, *s1, *v0, *v1, *client_view;
    BreakWorldDelta *initial;
    BreakWorldDelta *delta;
    BreakWorldSnapshot *empty;
    ASSERT_NOT_NULL(schemas);
    ASSERT_NOT_NULL(world);
    ASSERT_NOT_NULL(client);
    world_register_component(world, COMP_POSITION, sizeof(Position));
    world_register_component(client, COMP_POSITION, sizeof(Position));
    near_e = spawn(world, 1.0f);
    far_e = spawn(world, 9.0f);
    s0 = break_world_snapshot_build(world, schemas, 1u);
    ((Position *)world_get_component(world, near_e, COMP_POSITION))->x = 2.0f;
    ((Position *)world_get_component(world, far_e, COMP_POSITION))->x = 3.0f; /* enters */
    s1 = break_world_snapshot_build(world, schemas, 2u);
    ASSERT_NOT_NULL(s0);
    ASSERT_NOT_NULL(s1);
    v0 = break_world_snapshot_filter(s0, keep_x_below, &limit);
    v1 = break_world_snapshot_filter(s1, keep_x_below, &limit);
    ASSERT_NOT_NULL(v0);
    ASSERT_NOT_NULL(v1);
    ASSERT_EQ(break_world_snapshot_entity_count(v0), 1u);
    ASSERT_EQ(break_world_snapshot_entity_count(v1), 2u);
    /* Baseline: the client starts empty and receives the view at tick 1. */
    empty = break_world_snapshot_build(client, schemas, 0u);
    ASSERT_NOT_NULL(empty);
    initial = break_world_delta_diff(empty, v0);
    ASSERT_NOT_NULL(initial);
    ASSERT_EQ(break_world_delta_apply(client, initial), BREAK_DELTA_OK);
    delta = break_world_delta_diff(v0, v1);
    ASSERT_NOT_NULL(delta);
    ASSERT_EQ(break_world_delta_base_id(delta), break_world_snapshot_id(v0));
    ASSERT_EQ(break_world_delta_target_id(delta), break_world_snapshot_id(v1));
    ASSERT_EQ(break_world_delta_apply(client, delta), BREAK_DELTA_OK);
    client_view = break_world_snapshot_build(client, schemas, 2u);
    ASSERT_NOT_NULL(client_view);
    ASSERT_EQ(break_world_snapshot_hash(client_view), break_world_snapshot_hash(v1));
    break_world_snapshot_release(client_view);
    break_world_delta_release(delta);
    break_world_delta_release(initial);
    break_world_snapshot_release(empty);
    break_world_snapshot_release(v1);
    break_world_snapshot_release(v0);
    break_world_snapshot_release(s1);
    break_world_snapshot_release(s0);
    world_destroy(client);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

typedef struct {
    const BreakAoIScope *scope;
} ScopeFilter;

/* AOI entity ids here are index | generation << 32, the caller's choice. */
static bool keep_in_scope(void *user, const BreakWorldSnapshot *snapshot, Entity entity) {
    const ScopeFilter *f = (const ScopeFilter *)user;
    BreakAoIEntityId id = (BreakAoIEntityId)entity.index | ((BreakAoIEntityId)entity.generation << 32);
    (void)snapshot;
    for (usize i = 0u; i < f->scope->count; ++i)
        if (f->scope->ids[i] == id) return true;
    return false;
}

TEST(an_aoi_scope_drives_the_filter) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    World *world = world_create();
    BreakSpatialIndex *index = break_spatial_index_create(4.0f);
    BreakWitness witness;
    BreakAoIResult result;
    BreakAoIScope scope;
    ScopeFilter filter;
    Entity e[3];
    float xs[3] = {0.0f, 50.0f, 2.0f};
    BreakWorldSnapshot *full;
    BreakWorldSnapshot *view;
    ASSERT_NOT_NULL(schemas);
    ASSERT_NOT_NULL(world);
    ASSERT_NOT_NULL(index);
    world_register_component(world, COMP_POSITION, sizeof(Position));
    for (u32 i = 0u; i < 3u; ++i) {
        BreakReplicationObject obj;
        e[i] = spawn(world, xs[i]);
        memset(&obj, 0, sizeof obj);
        obj.entity_id = (BreakAoIEntityId)e[i].index | ((BreakAoIEntityId)e[i].generation << 32);
        obj.position[0] = xs[i];
        ASSERT_TRUE(break_spatial_index_insert(index, &obj));
    }
    memset(&witness, 0, sizeof witness);
    witness.radius = 5.0f;
    witness.shape = BREAK_AOI_SHAPE_SPHERE;
    memset(&result, 0, sizeof result);
    memset(&scope, 0, sizeof scope);
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, &scope, &result));
    ASSERT_EQ(result.enter_count, 2u);
    ASSERT_TRUE(break_aoi_scope_assign(&scope, result.enter, result.enter_count));
    full = break_world_snapshot_build(world, schemas, 1u);
    ASSERT_NOT_NULL(full);
    filter.scope = &scope;
    view = break_world_snapshot_filter(full, keep_in_scope, &filter);
    ASSERT_NOT_NULL(view);
    ASSERT_EQ(break_world_snapshot_entity_count(view), 2u);
    ASSERT_TRUE(break_world_snapshot_has_entity(view, e[0]));
    ASSERT_TRUE(!break_world_snapshot_has_entity(view, e[1]));
    ASSERT_TRUE(break_world_snapshot_has_entity(view, e[2]));
    break_world_snapshot_release(view);
    break_world_snapshot_release(full);
    break_aoi_scope_clear(&scope);
    break_aoi_result_clear(&result);
    break_spatial_index_destroy(index);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST(empty_views_and_bad_arguments) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    World *world = world_create();
    BreakWorldSnapshot *full;
    BreakWorldSnapshot *view;
    ASSERT_NOT_NULL(schemas);
    ASSERT_NOT_NULL(world);
    world_register_component(world, COMP_POSITION, sizeof(Position));
    (void)spawn(world, 1.0f);
    full = break_world_snapshot_build(world, schemas, 1u);
    ASSERT_NOT_NULL(full);
    view = break_world_snapshot_filter(full, keep_none, NULL);
    ASSERT_NOT_NULL(view);
    ASSERT_EQ(break_world_snapshot_entity_count(view), 0u);
    ASSERT_EQ(break_world_snapshot_entity_at(view, 0u).generation, 0u);
    break_world_snapshot_release(view);
    ASSERT_TRUE(break_world_snapshot_filter(NULL, keep_none, NULL) == NULL);
    ASSERT_TRUE(break_world_snapshot_filter(full, NULL, NULL) == NULL);
    break_world_snapshot_release(full);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}


/* Walks every snapshot-owned allocation failure point in build + filter,
 * including the filter's mid-loop cleanup, which no test reached before. */
TEST(filter_and_build_survive_every_allocation_failure) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    World *world = world_create();
    float limit = 5.0f;
    BreakWorldSnapshot *full;
    ASSERT_NOT_NULL(schemas);
    ASSERT_NOT_NULL(world);
    world_register_component(world, COMP_POSITION, sizeof(Position));
    (void)spawn(world, 1.0f);
    (void)spawn(world, 2.0f);
    (void)spawn(world, 9.0f);
    /* Build: each budget below the needed count must fail cleanly, not leak
     * or crash (ASan/LSan in CI enforce that). */
    for (u64 budget = 0u; budget < 4u; ++budget) {
        break_world_snapshot_test_set_alloc_budget(budget);
        full = break_world_snapshot_build(world, schemas, 7u);
        break_world_snapshot_test_set_alloc_budget(
            BREAK_WORLD_SNAPSHOT_TEST_ALLOC_DISABLED);
        if (full) {
            break_world_snapshot_release(full);
        }
    }
    break_world_snapshot_test_set_alloc_budget(
        BREAK_WORLD_SNAPSHOT_TEST_ALLOC_DISABLED);
    full = break_world_snapshot_build(world, schemas, 7u);
    ASSERT_NOT_NULL(full);
    /* Filter: same sweep. Budget 0..5 covers the keep mask, the view struct,
     * its entity array, its byte block and the per-entity component arrays
     * (two entities are kept, so the mid-loop failure path is exercised). */
    for (u64 budget = 0u; budget < 6u; ++budget) {
        BreakWorldSnapshot *view;
        break_world_snapshot_test_set_alloc_budget(budget);
        view = break_world_snapshot_filter(full, keep_x_below, &limit);
        break_world_snapshot_test_set_alloc_budget(
            BREAK_WORLD_SNAPSHOT_TEST_ALLOC_DISABLED);
        if (view) {
            /* A view that was produced must still be correct. */
            ASSERT_EQ(break_world_snapshot_entity_count(view), 2u);
            break_world_snapshot_release(view);
        }
    }
    /* With the hook off everything works as before. */
    {
        BreakWorldSnapshot *view = break_world_snapshot_filter(full, keep_x_below, &limit);
        ASSERT_NOT_NULL(view);
        ASSERT_EQ(break_world_snapshot_entity_count(view), 2u);
        break_world_snapshot_release(view);
    }
    break_world_snapshot_release(full);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST_MAIN_BEGIN()
    RUN_TEST(filter_keeps_only_admitted_entities_and_their_bytes);
    RUN_TEST(filter_hash_matches_a_snapshot_built_from_the_same_entities);
    RUN_TEST(filtered_views_diff_and_apply_like_full_snapshots);
    RUN_TEST(an_aoi_scope_drives_the_filter);
    RUN_TEST(empty_views_and_bad_arguments);
    RUN_TEST(filter_and_build_survive_every_allocation_failure);
TEST_MAIN_END()
