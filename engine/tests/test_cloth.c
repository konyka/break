#include "test_framework.h"
#include <physics/cloth.h>

static void cloth_test_post_step(PhysicsWorld *pw, void *user) {
    (void)pw;
    (void)user;
}

TEST(cloth_pins_the_top_row_and_pulls_back) {
    PhysicsWorld *pw = physics_world_create(24);
    Cloth cloth;
    memset(&cloth, 0, sizeof(cloth));
    ASSERT_TRUE(cloth_create(&cloth, pw, vec3(0, 3, 0), 0.5f, 3, 3, 0.2f));
    ASSERT_EQ(cloth.width, 3u);
    ASSERT_TRUE(pw->bodies[cloth.nodes[0].index].is_static);
    ASSERT_FALSE(pw->bodies[cloth.nodes[8].index].is_static);
    ASSERT_EQ(physics_constraint_count(pw), 20u);
    bool saw_diag = false;
    f32 diag = 0.5f * 1.41421356f;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (!pw->constraints[i].active) continue;
        f32 rest = pw->constraints[i].rest_length;
        if (rest > diag - 0.02f && rest < diag + 0.02f) saw_diag = true;
    }
    ASSERT_TRUE(saw_diag);

    PhysicsBodyHandle corner = cloth.nodes[8];
    PhysicsBodyHandle above = cloth.nodes[5];
    pw->bodies[corner.index].position.e[1] -= 1.0f;
    f32 stretched = pw->bodies[above.index].position.e[1] - pw->bodies[corner.index].position.e[1];
    if (stretched < 0) stretched = -stretched;
    for (int i = 0; i < 12; i++) physics_step(pw, 0.016f);
    f32 after = pw->bodies[above.index].position.e[1] - pw->bodies[corner.index].position.e[1];
    if (after < 0) after = -after;
    ASSERT_TRUE(after < stretched);

    PhysicsBodyHandle left = cloth.nodes[3];
    PhysicsBodyHandle right = cloth.nodes[5];
    pw->bodies[left.index].position = vec3(0, 1, 0);
    pw->bodies[right.index].position = vec3(0, 1, 0);
    pw->bodies[left.index].velocity = vec3(0, 0, 0);
    pw->bodies[right.index].velocity = vec3(0, 0, 0);
    physics_step(pw, 0.016f);
    f32 dx = pw->bodies[left.index].position.e[0] - pw->bodies[right.index].position.e[0];
    f32 dy = pw->bodies[left.index].position.e[1] - pw->bodies[right.index].position.e[1];
    f32 dz = pw->bodies[left.index].position.e[2] - pw->bodies[right.index].position.e[2];
    f32 apart = sqrtf(dx * dx + dy * dy + dz * dz);
    ASSERT_TRUE(apart > 0.05f);

    for (u32 i = 0; i < 9u; i++) {
        PhysicsBodyHandle id = cloth.nodes[i];
        if (physics_body_handle_equal(id, left) || physics_body_handle_equal(id, right)) continue;
        pw->bodies[id.index].position = vec3(0.0f, 40.0f + (f32)i, 0.0f);
    }
    pw->bodies[left.index].radius = 0.0f;
    pw->bodies[right.index].radius = 0.0f;
    pw->bodies[left.index].half_extent = vec3(0, 0, 0);
    pw->bodies[right.index].half_extent = vec3(0, 0, 0);
    pw->bodies[left.index].position = vec3(0, 1, 0);
    pw->bodies[right.index].position = vec3(0, 1, 0);
    cloth_collide(&cloth, pw);
    dx = pw->bodies[left.index].position.e[0] - pw->bodies[right.index].position.e[0];
    dy = pw->bodies[left.index].position.e[1] - pw->bodies[right.index].position.e[1];
    dz = pw->bodies[left.index].position.e[2] - pw->bodies[right.index].position.e[2];
    apart = sqrtf(dx * dx + dy * dy + dz * dz);
    ASSERT_TRUE(apart > 0.15f);

    PhysicsBodyHandle mid = cloth.nodes[4];
    for (u32 i = 0; i < 9u; i++) {
        PhysicsBodyHandle id = cloth.nodes[i];
        if (physics_body_handle_equal(id, left) || physics_body_handle_equal(id, mid)) continue;
        pw->bodies[id.index].position = vec3(0.0f, 40.0f + (f32)i, 0.0f);
    }
    pw->bodies[left.index].position = vec3(2, 1, 0);
    pw->bodies[mid.index].position = vec3(2, 1, 0);
    cloth_collide(&cloth, pw);
    dx = pw->bodies[left.index].position.e[0] - pw->bodies[mid.index].position.e[0];
    dy = pw->bodies[left.index].position.e[1] - pw->bodies[mid.index].position.e[1];
    dz = pw->bodies[left.index].position.e[2] - pw->bodies[mid.index].position.e[2];
    apart = sqrtf(dx * dx + dy * dy + dz * dz);
    ASSERT_TRUE(apart < 0.02f);

    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) physics_constraint_remove(pw, (PhysicsConstraintHandle){i, pw->constraints[i].generation});
    for (u32 i = 0; i < 9u; i++) {
        PhysicsBodyHandle id = cloth.nodes[i];
        pw->bodies[id.index].acceleration = vec3(0, 0, 0);
        pw->bodies[id.index].velocity = vec3(0, 0, 0);
        if (physics_body_handle_equal(id, left) || physics_body_handle_equal(id, right)) continue;
        pw->bodies[id.index].position = vec3(0.0f, 40.0f + (f32)i, 0.0f);
    }
    pw->bodies[left.index].radius = 0.0f;
    pw->bodies[right.index].radius = 0.0f;
    pw->bodies[left.index].position = vec3(0, 1, 0);
    pw->bodies[right.index].position = vec3(0, 1, 0);
    physics_step(pw, 0.016f);
    dx = pw->bodies[left.index].position.e[0] - pw->bodies[right.index].position.e[0];
    dy = pw->bodies[left.index].position.e[1] - pw->bodies[right.index].position.e[1];
    dz = pw->bodies[left.index].position.e[2] - pw->bodies[right.index].position.e[2];
    apart = sqrtf(dx * dx + dy * dy + dz * dz);
    ASSERT_TRUE(apart > 0.15f);
    physics_world_destroy(pw);

    PhysicsWorld *full = physics_world_create(32);
    PhysicsBodyHandle a = physics_body_create(full, vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    PhysicsBodyHandle b = physics_body_create(full, vec3(1, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    for (u32 i = 0; i < 64; i++) {
        ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_distance(full, a, b, 1.0f)));
    }
    u32 count = full->count;
    Cloth refused;
    memset(&refused, 0, sizeof(refused));
    ASSERT_FALSE(cloth_create(&refused, full, vec3(0, 2, 0), 0.5f, 2, 2, 0.2f));
    ASSERT_EQ(full->count, count);
    physics_world_destroy(full);

    PhysicsWorld *hooks = physics_world_create(16);
    for (u32 i = 0; i < PHYSICS_MAX_POST_STEPS; i++) {
        ASSERT_TRUE(physics_add_post_step(hooks, cloth_test_post_step, NULL));
    }
    ASSERT_FALSE(physics_add_post_step(hooks, cloth_test_post_step, NULL));
    u32 hooked = hooks->count;
    Cloth blocked;
    memset(&blocked, 0, sizeof(blocked));
    ASSERT_FALSE(cloth_create(&blocked, hooks, vec3(0, 2, 0), 0.5f, 2, 2, 0.2f));
    ASSERT_EQ(hooks->count, hooked);
    physics_world_destroy(hooks);

    PhysicsWorld *many = physics_world_create(48);
    Cloth sheets[8];
    for (u32 i = 0; i < 8u; i++) {
        memset(&sheets[i], 0, sizeof(sheets[i]));
        ASSERT_TRUE(cloth_create(&sheets[i], many, vec3((f32)i * 3.0f, 2.0f, 0.0f), 0.5f, 2u, 2u, 0.2f));
    }
    ASSERT_EQ(many->post_step_count, 8u);
    physics_world_destroy(many);

    PhysicsWorld *fifth = physics_world_create(40);
    Cloth small[4];
    for (u32 i = 0; i < 4u; i++) {
        memset(&small[i], 0, sizeof(small[i]));
        ASSERT_TRUE(cloth_create(&small[i], fifth, vec3((f32)i * 3.0f, 4.0f, 0.0f), 0.5f, 2u, 2u, 0.2f));
    }
    Cloth big;
    memset(&big, 0, sizeof(big));
    ASSERT_TRUE(cloth_create(&big, fifth, vec3(0, 3, 0), 0.5f, 3u, 3u, 0.2f));
    ASSERT_EQ(fifth->post_step_count, 5u);
    PhysicsBodyHandle late_left = big.nodes[3];
    PhysicsBodyHandle late_right = big.nodes[5];
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++)
        physics_constraint_remove(fifth, (PhysicsConstraintHandle){i, fifth->constraints[i].generation});
    for (u32 i = 0; i < fifth->count; i++) {
        fifth->bodies[i].acceleration = vec3(0, 0, 0);
        fifth->bodies[i].velocity = vec3(0, 0, 0);
        if (i == late_left.index || i == late_right.index) continue;
        fifth->bodies[i].position = vec3(0.0f, 30.0f + (f32)i, 0.0f);
    }
    fifth->bodies[late_left.index].radius = 0.0f;
    fifth->bodies[late_right.index].radius = 0.0f;
    fifth->bodies[late_left.index].position = vec3(0, 1, 0);
    fifth->bodies[late_right.index].position = vec3(0, 1, 0);
    physics_step(fifth, 0.016f);
    dx = fifth->bodies[late_left.index].position.e[0] - fifth->bodies[late_right.index].position.e[0];
    dy = fifth->bodies[late_left.index].position.e[1] - fifth->bodies[late_right.index].position.e[1];
    dz = fifth->bodies[late_left.index].position.e[2] - fifth->bodies[late_right.index].position.e[2];
    apart = sqrtf(dx * dx + dy * dy + dz * dz);
    ASSERT_TRUE(apart > 0.15f);
    physics_world_destroy(fifth);
}

TEST_MAIN_BEGIN()
    RUN_TEST(cloth_pins_the_top_row_and_pulls_back);
TEST_MAIN_END()
