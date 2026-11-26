/* Cross-World persistent network identity: a NetEntityId outlives the World
 * Entity it is bound to and can be rebound to a new Entity in another World. */
#include "test_framework.h"
#include <ecs/ecs.h>
#include <ecs/net_entity_map.h>
#include <string.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(create_validates_config);
    RUN_TEST(allocated_ids_are_unique_monotonic_and_never_reused);
    RUN_TEST(lookups_work_in_both_directions_per_world);
    RUN_TEST(rebind_moves_an_identity_into_another_world);
    RUN_TEST(an_entity_can_hold_only_one_identity);
    RUN_TEST(a_full_map_is_overload_and_release_frees_room);
    RUN_TEST(adopt_registers_a_remote_identity_without_allocating);
    RUN_TEST(id_space_exhaustion_fails_closed);
TEST_MAIN_END()
