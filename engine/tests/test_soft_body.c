#include "test_framework.h"
#include <physics/soft_body.h>

TEST(soft_body_restores_offsets_when_stiff) {
    PhysicsWorld *pw = physics_world_create(8);
    SoftBody soft;
    memset(&soft, 0, sizeof(soft));
    ASSERT_TRUE(soft_body_create(&soft, pw, vec3(0, 3, 0), 0.4f, 1.0f, 1.0f));
    ASSERT_EQ(soft.count, 4u);
    Vec3 rest0 = vec3_sub(pw->bodies[soft.nodes[0].index].position, vec3(0, 3, 0));
    pw->bodies[soft.nodes[0].index].position.e[0] += 2.0f;
    soft_body_step(&soft, pw);
    Vec3 com = vec3(0, 0, 0);
    for (u32 i = 0; i < soft.count; i++) com = vec3_add(com, pw->bodies[soft.nodes[i].index].position);
    com = vec3_scale(com, 0.25f);
    Vec3 offset = vec3_sub(pw->bodies[soft.nodes[0].index].position, com);
    ASSERT_FLOAT_EQ(offset.e[0], rest0.e[0], 1e-4);
    ASSERT_FLOAT_EQ(offset.e[1], rest0.e[1], 1e-4);
    ASSERT_FLOAT_EQ(offset.e[2], rest0.e[2], 1e-4);

    PhysicsWorld *loose = physics_world_create(8);
    SoftBody floppy;
    memset(&floppy, 0, sizeof(floppy));
    ASSERT_TRUE(soft_body_create(&floppy, loose, vec3(0, 0, 0), 0.3f, 1.0f, 0.0f));
    loose->bodies[floppy.nodes[0].index].position.e[0] += 1.5f;
    f32 moved = loose->bodies[floppy.nodes[0].index].position.e[0];
    soft_body_step(&floppy, loose);
    ASSERT_FLOAT_EQ(loose->bodies[floppy.nodes[0].index].position.e[0], moved, 1e-5);
    physics_world_destroy(loose);

    PhysicsWorld *bulk = physics_world_create(8);
    SoftBody inflated;
    memset(&inflated, 0, sizeof(inflated));
    ASSERT_TRUE(soft_body_create_count(&inflated, bulk, vec3(0, 0, 0), 0.5f, 1.0f, 0.0f, 1.0f, 4u));
    Vec3 bulk_com = vec3(0, 0, 0);
    for (u32 i = 0; i < inflated.count; i++) bulk_com = vec3_add(bulk_com, bulk->bodies[inflated.nodes[i].index].position);
    bulk_com = vec3_scale(bulk_com, 0.25f);
    f32 before = 0.0f;
    for (u32 i = 0; i < inflated.count; i++) {
        Vec3 from = vec3_sub(bulk->bodies[inflated.nodes[i].index].position, bulk_com);
        before += vec3_len_sq(from);
        bulk->bodies[inflated.nodes[i].index].position = vec3_add(bulk_com, vec3_scale(from, 2.0f));
    }
    before *= 0.25f;
    soft_body_step(&inflated, bulk);
    Vec3 after_com = vec3(0, 0, 0);
    for (u32 i = 0; i < inflated.count; i++) after_com = vec3_add(after_com, bulk->bodies[inflated.nodes[i].index].position);
    after_com = vec3_scale(after_com, 0.25f);
    f32 after = 0.0f;
    for (u32 i = 0; i < inflated.count; i++) {
        after += vec3_len_sq(vec3_sub(bulk->bodies[inflated.nodes[i].index].position, after_com));
    }
    after *= 0.25f;
    ASSERT_FLOAT_EQ(after, before, before * 0.05f + 1e-4f);

    PhysicsWorld *wide = physics_world_create(12);
    SoftBody six;
    memset(&six, 0, sizeof(six));
    ASSERT_TRUE(soft_body_create_count(&six, wide, vec3(1, 1, 1), 0.4f, 2.0f, 1.0f, 0.0f, 6u));
    ASSERT_EQ(six.count, 6u);
    ASSERT_FALSE(soft_body_create_count(&six, wide, vec3(0, 0, 0), 0.2f, 1.0f, 1.0f, 0.0f, 3u));
    PhysicsWorld *many = physics_world_create(110);
    SoftBody dozen;
    memset(&dozen, 0, sizeof(dozen));
    ASSERT_TRUE(soft_body_create_count(&dozen, many, vec3(0, 2, 0), 0.3f, 1.0f, 1.0f, 0.0f, 96u));
    ASSERT_EQ(dozen.count, 96u);
    ASSERT_FALSE(soft_body_create_count(&dozen, many, vec3(0, 0, 0), 0.2f, 1.0f, 1.0f, 0.0f, 129u));
    physics_world_destroy(many);
    physics_world_destroy(wide);
    physics_world_destroy(bulk);
    physics_world_destroy(pw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(soft_body_restores_offsets_when_stiff);
TEST_MAIN_END()
