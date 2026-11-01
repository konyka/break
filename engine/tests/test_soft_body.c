#include "test_framework.h"
#include <physics/soft_body.h>

TEST(soft_body_restores_offsets_when_stiff) {
    PhysicsWorld *pw = physics_world_create(8);
    SoftBody soft;
    memset(&soft, 0, sizeof(soft));
    ASSERT_TRUE(soft_body_create(&soft, pw, vec3(0, 3, 0), 0.4f, 1.0f, 1.0f));
    ASSERT_EQ(soft.count, 4u);
    Vec3 rest0 = vec3_sub(pw->bodies[soft.nodes[0]].position, vec3(0, 3, 0));
    pw->bodies[soft.nodes[0]].position.e[0] += 2.0f;
    soft_body_step(&soft, pw);
    Vec3 com = vec3(0, 0, 0);
    for (u32 i = 0; i < soft.count; i++) com = vec3_add(com, pw->bodies[soft.nodes[i]].position);
    com = vec3_scale(com, 0.25f);
    Vec3 offset = vec3_sub(pw->bodies[soft.nodes[0]].position, com);
    ASSERT_FLOAT_EQ(offset.e[0], rest0.e[0], 1e-4);
    ASSERT_FLOAT_EQ(offset.e[1], rest0.e[1], 1e-4);
    ASSERT_FLOAT_EQ(offset.e[2], rest0.e[2], 1e-4);

    PhysicsWorld *loose = physics_world_create(8);
    SoftBody floppy;
    memset(&floppy, 0, sizeof(floppy));
    ASSERT_TRUE(soft_body_create(&floppy, loose, vec3(0, 0, 0), 0.3f, 1.0f, 0.0f));
    loose->bodies[floppy.nodes[0]].position.e[0] += 1.5f;
    f32 moved = loose->bodies[floppy.nodes[0]].position.e[0];
    soft_body_step(&floppy, loose);
    ASSERT_FLOAT_EQ(loose->bodies[floppy.nodes[0]].position.e[0], moved, 1e-5);
    physics_world_destroy(loose);
    physics_world_destroy(pw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(soft_body_restores_offsets_when_stiff);
TEST_MAIN_END()
