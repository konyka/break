#include "test_framework.h"
#include <physics/cloth.h>

TEST(cloth_pins_the_top_row_and_pulls_back) {
    PhysicsWorld *pw = physics_world_create(24);
    Cloth cloth;
    memset(&cloth, 0, sizeof(cloth));
    ASSERT_TRUE(cloth_create(&cloth, pw, vec3(0, 3, 0), 0.5f, 3, 3, 0.2f));
    ASSERT_EQ(cloth.width, 3u);
    ASSERT_TRUE(pw->bodies[cloth.nodes[0]].is_static);
    ASSERT_FALSE(pw->bodies[cloth.nodes[8]].is_static);
    ASSERT_EQ(physics_constraint_count(pw), 20u);
    bool saw_diag = false;
    f32 diag = 0.5f * 1.41421356f;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (!pw->constraints[i].active) continue;
        f32 rest = pw->constraints[i].rest_length;
        if (rest > diag - 0.02f && rest < diag + 0.02f) saw_diag = true;
    }
    ASSERT_TRUE(saw_diag);

    u32 corner = cloth.nodes[8];
    u32 above = cloth.nodes[5];
    pw->bodies[corner].position.e[1] -= 1.0f;
    f32 stretched = pw->bodies[above].position.e[1] - pw->bodies[corner].position.e[1];
    if (stretched < 0) stretched = -stretched;
    for (int i = 0; i < 12; i++) physics_step(pw, 0.016f);
    f32 after = pw->bodies[above].position.e[1] - pw->bodies[corner].position.e[1];
    if (after < 0) after = -after;
    ASSERT_TRUE(after < stretched);

    u32 left = cloth.nodes[3];
    u32 right = cloth.nodes[5];
    pw->bodies[left].position = vec3(0, 1, 0);
    pw->bodies[right].position = vec3(0, 1, 0);
    pw->bodies[left].velocity = vec3(0, 0, 0);
    pw->bodies[right].velocity = vec3(0, 0, 0);
    physics_step(pw, 0.016f);
    f32 dx = pw->bodies[left].position.e[0] - pw->bodies[right].position.e[0];
    f32 dy = pw->bodies[left].position.e[1] - pw->bodies[right].position.e[1];
    f32 dz = pw->bodies[left].position.e[2] - pw->bodies[right].position.e[2];
    f32 apart = sqrtf(dx * dx + dy * dy + dz * dz);
    ASSERT_TRUE(apart > 0.05f);
    physics_world_destroy(pw);

    PhysicsWorld *full = physics_world_create(32);
    u32 a = physics_body_create(full, vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    u32 b = physics_body_create(full, vec3(1, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    for (u32 i = 0; i < 64; i++) {
        ASSERT_TRUE(physics_constraint_add_distance(full, a, b, 1.0f) != UINT32_MAX);
    }
    u32 count = full->count;
    Cloth refused;
    memset(&refused, 0, sizeof(refused));
    ASSERT_FALSE(cloth_create(&refused, full, vec3(0, 2, 0), 0.5f, 2, 2, 0.2f));
    ASSERT_EQ(full->count, count);
    physics_world_destroy(full);
}

TEST_MAIN_BEGIN()
    RUN_TEST(cloth_pins_the_top_row_and_pulls_back);
TEST_MAIN_END()
