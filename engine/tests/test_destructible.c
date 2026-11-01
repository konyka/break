#include "test_framework.h"
#include <physics/destructible.h>

TEST(destructible_breaks_only_past_the_threshold) {
    PhysicsWorld *pw = physics_world_create(16);
    physics_body_create(pw, vec3(0, -1, 0), vec3(5, 0.5f, 5), 0, true, 0);
    Destructible box;
    memset(&box, 0, sizeof(box));
    ASSERT_TRUE(destructible_create(&box, pw, vec3(0, 2, 0), vec3(1, 1, 1), 8.0f, 10.0f));
    ASSERT_TRUE(box.root != 0u);
    destructible_apply_impulse(&box, pw, 3.0f);
    ASSERT_FALSE(box.broken);
    ASSERT_FALSE(physics_body_is_parked(&pw->bodies[box.root]));

    destructible_apply_impulse(&box, pw, 12.0f);
    ASSERT_TRUE(box.broken);
    ASSERT_TRUE(physics_body_is_parked(&pw->bodies[box.root]));
    ASSERT_EQ(box.fragment_count, 8u);
    for (u32 i = 0; i < box.fragment_count; i++) {
        RigidBody *frag = &pw->bodies[box.fragments[i]];
        ASSERT_FALSE(frag->is_static);
        ASSERT_TRUE(fabsf(frag->position.e[0]) <= 0.5f + 1e-4f);
        ASSERT_TRUE(fabsf(frag->position.e[1] - 2.0f) <= 0.5f + 1e-4f);
        ASSERT_TRUE(fabsf(frag->position.e[2]) <= 0.5f + 1e-4f);
    }
    physics_world_destroy(pw);

    PhysicsWorld *tiny = physics_world_create(2);
    physics_body_create(tiny, vec3(0, -1, 0), vec3(1, 0.2f, 1), 0, true, 0);
    Destructible stuck;
    memset(&stuck, 0, sizeof(stuck));
    ASSERT_TRUE(destructible_create(&stuck, tiny, vec3(0, 1, 0), vec3(0.4f, 0.4f, 0.4f), 2.0f, 1.0f));
    destructible_apply_impulse(&stuck, tiny, 5.0f);
    ASSERT_FALSE(stuck.broken);
    ASSERT_FALSE(physics_body_is_parked(&tiny->bodies[stuck.root]));
    physics_world_destroy(tiny);

    PhysicsWorld *deep = physics_world_create(80);
    physics_body_create(deep, vec3(0, -2, 0), vec3(4, 0.2f, 4), 0, true, 0);
    Destructible again;
    memset(&again, 0, sizeof(again));
    ASSERT_TRUE(destructible_create(&again, deep, vec3(0, 3, 0), vec3(1, 1, 1), 8.0f, 4.0f));
    destructible_apply_impulse(&again, deep, 4.0f);
    ASSERT_EQ(again.fragment_count, 8u);
    destructible_apply_impulse(&again, deep, 1.0f);
    ASSERT_EQ(again.fragment_count, 8u);
    u32 parent = again.fragments[0];
    destructible_apply_impulse(&again, deep, 4.0f);
    ASSERT_EQ(again.generation, 2u);
    ASSERT_EQ(again.fragment_count, 64u);
    ASSERT_TRUE(physics_body_is_parked(&deep->bodies[parent]));
    ASSERT_FLOAT_EQ(deep->bodies[again.fragments[0]].half_extent.e[0], 0.25f, 1e-4);
    physics_world_destroy(deep);
}

TEST_MAIN_BEGIN()
    RUN_TEST(destructible_breaks_only_past_the_threshold);
TEST_MAIN_END()
