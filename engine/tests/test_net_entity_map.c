/* Cross-World persistent network identity: a NetEntityId outlives the World
 * Entity it is bound to and can be rebound to a new Entity in another World. */
#include "test_framework.h"
#include <ecs/ecs.h>
#include <ecs/net_entity_map.h>
#include <ecs/world_snapshot.h>
#include <string.h>

#define SCOPE_COMPONENT 11u

typedef struct {
    u32 value;
} ScopeValue;

static BreakNetEntityMap *make_map(u32 capacity) {
    BreakNetEntityMapConfig cfg = {capacity, 1u};
    BreakNetEntityMap *m = NULL;
    return break_net_entity_map_create(&cfg, &m) ? m : NULL;
}

TEST(create_validates_config) {
    BreakNetEntityMapConfig zero = {0u, 1u};
    BreakNetEntityMapConfig big = {BREAK_NET_ENTITY_MAP_MAX_CAPACITY + 1u, 1u};
    BreakNetEntityMapConfig no_first = {4u, 0u};
    BreakNetEntityMap *m = (BreakNetEntityMap *)1;
    ASSERT_FALSE(break_net_entity_map_create(&zero, NULL));
    ASSERT_FALSE(break_net_entity_map_create(NULL, &m));
    ASSERT_TRUE(m == NULL);
    ASSERT_FALSE(break_net_entity_map_create(&zero, &m));
    ASSERT_FALSE(break_net_entity_map_create(&big, &m));
    ASSERT_FALSE(break_net_entity_map_create(&no_first, &m));
    ASSERT_TRUE(m == NULL);
    break_net_entity_map_destroy(NULL);
}

TEST(allocated_ids_are_unique_monotonic_and_never_reused) {
    World *w = world_create();
    BreakNetEntityMap *m = make_map(4u);
    Entity a, b;
    BreakNetEntityId ia = 0u, ib = 0u, ic = 0u;
    ASSERT_NOT_NULL(w);
    ASSERT_NOT_NULL(m);
    a = world_create_entity(w);
    b = world_create_entity(w);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 7u, a, &ia), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 7u, b, &ib), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(ia, 1u);
    ASSERT_EQ(ib, 2u);
    ASSERT_EQ(break_net_entity_map_release(m, ia), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 7u, a, &ic), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(ic, 3u); /* a released id is never handed out again */
    break_net_entity_map_destroy(m);
    world_destroy(w);
}

TEST(lookups_work_in_both_directions_per_world) {
    World *w = world_create();
    BreakNetEntityMap *m = make_map(4u);
    Entity a, out;
    BreakNetEntityId id = 0u, back = 0u;
    u32 world_key = 0u;
    ASSERT_NOT_NULL(w);
    ASSERT_NOT_NULL(m);
    a = world_create_entity(w);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 7u, a, &id), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_entity(m, id, &world_key, &out), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(world_key, 7u);
    ASSERT_EQ(out.index, a.index);
    ASSERT_EQ(out.generation, a.generation);
    ASSERT_EQ(break_net_entity_map_id(m, 7u, a, &back), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(back, id);
    ASSERT_EQ(break_net_entity_map_id(m, 8u, a, &back), BREAK_NET_ENTITY_NOT_FOUND);
    ASSERT_EQ(break_net_entity_map_id(m, 7u, ENTITY_NULL, &back), BREAK_NET_ENTITY_INVALID);
    ASSERT_EQ(break_net_entity_map_entity(m, 99u, &world_key, &out), BREAK_NET_ENTITY_NOT_FOUND);
    ASSERT_EQ(break_net_entity_map_entity(m, 0u, &world_key, &out), BREAK_NET_ENTITY_INVALID);
    break_net_entity_map_destroy(m);
    world_destroy(w);
}

TEST(rebind_moves_an_identity_into_another_world) {
    World *w1 = world_create();
    World *w2 = world_create();
    BreakNetEntityMap *m = make_map(4u);
    Entity a, c, out;
    BreakNetEntityId id = 0u, back = 0u;
    u32 world_key = 0u;
    ASSERT_NOT_NULL(w1);
    ASSERT_NOT_NULL(w2);
    ASSERT_NOT_NULL(m);
    a = world_create_entity(w1);
    (void)world_create_entity(w2);
    c = world_create_entity(w2);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, a, &id), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_rebind(m, id, 2u, c), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_entity(m, id, &world_key, &out), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(world_key, 2u);
    ASSERT_EQ(out.index, c.index);
    ASSERT_EQ(break_net_entity_map_id(m, 1u, a, &back), BREAK_NET_ENTITY_NOT_FOUND);
    ASSERT_EQ(break_net_entity_map_id(m, 2u, c, &back), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(back, id);
    break_net_entity_map_destroy(m);
    world_destroy(w2);
    world_destroy(w1);
}

TEST(an_entity_can_hold_only_one_identity) {
    World *w = world_create();
    BreakNetEntityMap *m = make_map(4u);
    Entity a, b;
    BreakNetEntityId ia = 0u, ib = 0u, dup = 0u;
    BreakNetEntityMapStats stats;
    ASSERT_NOT_NULL(w);
    ASSERT_NOT_NULL(m);
    a = world_create_entity(w);
    b = world_create_entity(w);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, a, &ia), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, b, &ib), BREAK_NET_ENTITY_OK);
    dup = 55u;
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, a, &dup), BREAK_NET_ENTITY_CONFLICT);
    ASSERT_EQ(dup, 0u);
    ASSERT_EQ(break_net_entity_map_rebind(m, ia, 1u, b), BREAK_NET_ENTITY_CONFLICT);
    ASSERT_EQ(break_net_entity_map_rebind(m, ia, 1u, a), BREAK_NET_ENTITY_OK); /* same place */
    ASSERT_EQ(break_net_entity_map_stats(m, &stats), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(stats.bound, 2u);
    ASSERT_EQ(stats.conflicts, 2u);
    ASSERT_EQ(stats.next_id, 3u);
    break_net_entity_map_destroy(m);
    world_destroy(w);
}

TEST(a_full_map_is_overload_and_release_frees_room) {
    World *w = world_create();
    BreakNetEntityMap *m = make_map(2u);
    Entity e[3];
    BreakNetEntityId ids[3] = {0u, 0u, 0u};
    ASSERT_NOT_NULL(w);
    ASSERT_NOT_NULL(m);
    for (u32 i = 0u; i < 3u; ++i) e[i] = world_create_entity(w);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, e[0], &ids[0]), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, e[1], &ids[1]), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, e[2], &ids[2]), BREAK_NET_ENTITY_OVERLOAD);
    ASSERT_EQ(ids[2], 0u);
    ASSERT_EQ(break_net_entity_map_release(m, ids[0]), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_release(m, ids[0]), BREAK_NET_ENTITY_NOT_FOUND);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, e[2], &ids[2]), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(ids[2], 3u);
    ASSERT_EQ(break_net_entity_map_id(m, 1u, e[0], &ids[0]), BREAK_NET_ENTITY_NOT_FOUND);
    break_net_entity_map_destroy(m);
    world_destroy(w);
}

TEST(adopt_registers_a_remote_identity_without_allocating) {
    World *w = world_create();
    BreakNetEntityMap *m = make_map(4u);
    Entity a, b;
    BreakNetEntityId mine = 0u;
    BreakNetEntityMapStats stats;
    ASSERT_NOT_NULL(w);
    ASSERT_NOT_NULL(m);
    a = world_create_entity(w);
    b = world_create_entity(w);
    ASSERT_EQ(break_net_entity_map_adopt(m, 1000u, 1u, a), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_adopt(m, 1000u, 1u, b), BREAK_NET_ENTITY_CONFLICT);
    ASSERT_EQ(break_net_entity_map_adopt(m, 0u, 1u, b), BREAK_NET_ENTITY_INVALID);
    /* A later local allocation skips past every adopted id. */
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, b, &mine), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(mine, 1001u);
    ASSERT_EQ(break_net_entity_map_stats(m, &stats), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(stats.bound, 2u);
    break_net_entity_map_destroy(m);
    world_destroy(w);
}

TEST(id_space_exhaustion_fails_closed) {
    World *w = world_create();
    BreakNetEntityMap *m = make_map(4u);
    Entity a, b;
    BreakNetEntityId id = 7u;
    ASSERT_NOT_NULL(w);
    ASSERT_NOT_NULL(m);
    a = world_create_entity(w);
    b = world_create_entity(w);
    ASSERT_EQ(break_net_entity_map_adopt(m, UINT64_MAX, 1u, a), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, b, &id), BREAK_NET_ENTITY_EXHAUSTED);
    ASSERT_EQ(id, 0u);
    break_net_entity_map_destroy(m);
    world_destroy(w);
}

static BreakComponentSchemaRegistry *make_scope_schemas(void) {
    BreakComponentSchemaRegistry *schemas = break_schema_registry_create();
    BreakComponentSchema schema;
    memset(&schema, 0, sizeof(schema));
    schema.component_id = SCOPE_COMPONENT;
    schema.version = 1u;
    schema.size = sizeof(ScopeValue);
    schema.alignment = _Alignof(ScopeValue);
    schema.flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES;
    if (!schemas) return NULL;
    if (break_schema_register(schemas, &schema) != BREAK_SCHEMA_OK) {
        break_schema_registry_destroy(schemas);
        return NULL;
    }
    return schemas;
}

static Entity scope_spawn(World *world, u32 value) {
    Entity e = world_create_entity(world);
    ScopeValue *v = (ScopeValue *)world_add_component(world, e, SCOPE_COMPONENT);
    if (v) v->value = value;
    return e;
}

TEST(scope_keep_culls_entities_outside_the_persistent_id_set) {
    BreakComponentSchemaRegistry *schemas = make_scope_schemas();
    World *world = world_create();
    BreakNetEntityMap *m = make_map(8u);
    Entity a, b, c;
    BreakNetEntityId ia = 0u, ib = 0u, ic = 0u;
    BreakNetEntityId scope_ids[2];
    BreakNetEntityScope scope;
    BreakWorldSnapshot *full;
    BreakWorldSnapshot *view;
    ASSERT_NOT_NULL(schemas);
    ASSERT_NOT_NULL(world);
    ASSERT_NOT_NULL(m);
    world_register_component(world, SCOPE_COMPONENT, sizeof(ScopeValue));
    a = scope_spawn(world, 10u);
    b = scope_spawn(world, 20u);
    c = scope_spawn(world, 30u);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, a, &ia), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, b, &ib), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, c, &ic), BREAK_NET_ENTITY_OK);
    scope_ids[0] = ia;
    scope_ids[1] = ic; /* b is out of scope */
    scope.map = m;
    scope.world_key = 1u;
    scope.ids = scope_ids;
    scope.count = 2u;
    full = break_world_snapshot_build(world, schemas, 5u);
    ASSERT_NOT_NULL(full);
    view = break_world_snapshot_filter(full, break_net_entity_scope_keep, &scope);
    ASSERT_NOT_NULL(view);
    ASSERT_EQ(break_world_snapshot_entity_count(view), 2u);
    ASSERT_TRUE(break_world_snapshot_has_entity(view, a));
    ASSERT_TRUE(!break_world_snapshot_has_entity(view, b));
    ASSERT_TRUE(break_world_snapshot_has_entity(view, c));
    break_world_snapshot_release(view);
    break_world_snapshot_release(full);
    break_net_entity_map_destroy(m);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST(scope_keep_culls_unbound_entities_and_wrong_world_and_bad_args) {
    BreakComponentSchemaRegistry *schemas = make_scope_schemas();
    World *world = world_create();
    BreakNetEntityMap *m = make_map(8u);
    Entity bound, unbound;
    BreakNetEntityId id = 0u;
    BreakNetEntityId scope_ids[1];
    BreakNetEntityScope scope;
    BreakWorldSnapshot *full;
    BreakWorldSnapshot *view;
    BreakWorldSnapshot *wrong_world_view;
    ASSERT_NOT_NULL(schemas);
    ASSERT_NOT_NULL(world);
    ASSERT_NOT_NULL(m);
    world_register_component(world, SCOPE_COMPONENT, sizeof(ScopeValue));
    bound = scope_spawn(world, 10u);
    unbound = scope_spawn(world, 20u);
    ASSERT_EQ(break_net_entity_map_bind_new(m, 1u, bound, &id), BREAK_NET_ENTITY_OK);
    scope_ids[0] = id;
    scope.map = m;
    scope.world_key = 1u;
    scope.ids = scope_ids;
    scope.count = 1u;
    full = break_world_snapshot_build(world, schemas, 5u);
    ASSERT_NOT_NULL(full);
    /* The unbound entity has no id, so it is never in scope. */
    view = break_world_snapshot_filter(full, break_net_entity_scope_keep, &scope);
    ASSERT_NOT_NULL(view);
    ASSERT_EQ(break_world_snapshot_entity_count(view), 1u);
    ASSERT_TRUE(break_world_snapshot_has_entity(view, bound));
    ASSERT_TRUE(!break_world_snapshot_has_entity(view, unbound));
    break_world_snapshot_release(view);
    /* A scope naming another world_key resolves no ids, so nothing is kept. */
    scope.world_key = 2u;
    wrong_world_view = break_world_snapshot_filter(full, break_net_entity_scope_keep, &scope);
    ASSERT_NOT_NULL(wrong_world_view);
    ASSERT_EQ(break_world_snapshot_entity_count(wrong_world_view), 0u);
    break_world_snapshot_release(wrong_world_view);
    /* NULL user / NULL map / NULL snapshot keep nothing and never crash. */
    ASSERT_FALSE(break_net_entity_scope_keep(NULL, full, bound));
    scope.world_key = 1u;
    scope.map = NULL;
    ASSERT_FALSE(break_net_entity_scope_keep(&scope, full, bound));
    scope.map = m;
    ASSERT_FALSE(break_net_entity_scope_keep(&scope, NULL, bound));
    break_world_snapshot_release(full);
    break_net_entity_map_destroy(m);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_config);
    RUN_TEST(allocated_ids_are_unique_monotonic_and_never_reused);
    RUN_TEST(lookups_work_in_both_directions_per_world);
    RUN_TEST(rebind_moves_an_identity_into_another_world);
    RUN_TEST(an_entity_can_hold_only_one_identity);
    RUN_TEST(a_full_map_is_overload_and_release_frees_room);
    RUN_TEST(adopt_registers_a_remote_identity_without_allocating);
    RUN_TEST(id_space_exhaustion_fails_closed);
    RUN_TEST(scope_keep_culls_entities_outside_the_persistent_id_set);
    RUN_TEST(scope_keep_culls_unbound_entities_and_wrong_world_and_bad_args);
TEST_MAIN_END()
