#include "test_framework.h"
#include <physics/rope.h>

TEST(rope_links_nodes_and_refuses_a_full_world) {
    PhysicsWorld *pw = physics_world_create(16);
    Rope rope;
    memset(&rope, 0, sizeof(rope));
    ASSERT_TRUE(rope_create(&rope, pw, vec3(0, 2, 0), vec3(0, 2, 4), 4, 0.2f));
    ASSERT_EQ(rope.count, 5u);
    ASSERT_TRUE(pw->bodies[rope.nodes[0]].is_static);
    ASSERT_FALSE(pw->bodies[rope.nodes[4]].is_static);
    ASSERT_FLOAT_EQ(pw->bodies[rope.nodes[0]].position.e[2], 0.0f, 1e-4);
    ASSERT_FLOAT_EQ(pw->bodies[rope.nodes[4]].position.e[2], 4.0f, 1e-4);
    ASSERT_EQ(physics_constraint_count(pw), 4u);
    physics_world_destroy(pw);

    PhysicsWorld *full = physics_world_create(32);
    u32 a = physics_body_create(full, vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    u32 b = physics_body_create(full, vec3(1, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    for (u32 i = 0; i < 64; i++) {
        ASSERT_TRUE(physics_constraint_add_distance(full, a, b, 1.0f) != UINT32_MAX);
    }
    u32 count = full->count;
    Rope failed;
    memset(&failed, 0, sizeof(failed));
    ASSERT_FALSE(rope_create(&failed, full, vec3(0, 1, 0), vec3(1, 1, 0), 4, 0.2f));
    ASSERT_EQ(full->count, count);
    physics_world_destroy(full);
}

TEST_MAIN_BEGIN()
    RUN_TEST(rope_links_nodes_and_refuses_a_full_world);
TEST_MAIN_END()
