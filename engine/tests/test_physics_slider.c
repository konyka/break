#include "test_framework.h"
#include <physics/physics.h>

TEST(slider_kills_perpendicular_offset_and_respects_the_limit) {
    PhysicsWorld *pw = physics_world_create(4);
    u32 a = physics_body_create(pw, vec3(0, 2, 0), vec3(0.2f, 0.2f, 0.2f), 0, true, 0);
    u32 b = physics_body_create(pw, vec3(0.5f, 2, 0), vec3(0.2f, 0.2f, 0.2f), 1, false, 0);
    pw->bodies[b].acceleration = vec3(0, 0, 0);
    SliderDesc slider;
    memset(&slider, 0, sizeof(slider));
    slider.body_a = a;
    slider.body_b = b;
    slider.axis_local_a = vec3(1, 0, 0);
    u32 id = physics_constraint_add_slider(pw, &slider);
    ASSERT_TRUE(id != UINT32_MAX);
    for (int i = 0; i < 8; i++) {
        pw->bodies[b].acceleration = vec3(0, 0, 0);
        physics_step(pw, 0.016f);
    }
    ASSERT_TRUE(fabsf(pw->bodies[b].position.e[1] - 2.0f) < 0.02f);
    ASSERT_TRUE(fabsf(pw->bodies[b].position.e[2]) < 0.02f);
    f32 along = pw->bodies[b].position.e[0] - pw->bodies[a].position.e[0];
    ASSERT_TRUE(fabsf(along - 0.5f) < 0.05f);

    pw->constraints[id].limit_min = -0.2f;
    pw->constraints[id].limit_max = 0.2f;
    for (int i = 0; i < 8; i++) {
        pw->bodies[b].acceleration = vec3(0, 0, 0);
        physics_step(pw, 0.016f);
    }
    along = pw->bodies[b].position.e[0] - pw->bodies[a].position.e[0];
    ASSERT_TRUE(along <= 0.2f + 1e-3f);

    PhysicsPose pose;
    pose.orientation = QUAT_IDENTITY;
    pose.angular_velocity = vec3(0, 3, 0);
    pose.inertia_diag = vec3(1, 1, 1);
    physics_body_set_pose(pw, b, &pose);
    pw->bodies[b].acceleration = vec3(0, 0, 0);
    physics_step(pw, 0.05f);
    Quat spun = pw->bodies[b].orientation;
    f32 twist = 2.0f * atan2f(spun.e[1], spun.e[3]);
    ASSERT_TRUE(fabsf(twist) < 1e-3f);

    physics_constraint_set_slider_torsion(pw, id, 0.5f);
    pose.orientation = quat_from_axis_angle(vec3(0, 1, 0), 0.2f);
    pose.angular_velocity = vec3(0, 0, 0);
    pose.inertia_diag = vec3(1, 1, 1);
    physics_body_set_pose(pw, b, &pose);
    pw->bodies[b].acceleration = vec3(0, 0, 0);
    physics_step(pw, 0.05f);
    spun = pw->bodies[b].orientation;
    twist = 2.0f * atan2f(spun.e[1], spun.e[3]);
    ASSERT_TRUE(twist > 0.07f && twist < 0.13f);
    physics_step(pw, 0.05f);
    spun = pw->bodies[b].orientation;
    twist = 2.0f * atan2f(spun.e[1], spun.e[3]);
    ASSERT_TRUE(twist > 0.03f && twist < 0.07f);
    physics_world_destroy(pw);

    PhysicsWorld *full = physics_world_create(4);
    u32 c = physics_body_create(full, vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    u32 d = physics_body_create(full, vec3(1, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    for (u32 i = 0; i < 64; i++) {
        ASSERT_TRUE(physics_constraint_add_distance(full, c, d, 1.0f) != UINT32_MAX);
    }
    SliderDesc extra;
    memset(&extra, 0, sizeof(extra));
    extra.body_a = c;
    extra.body_b = d;
    extra.axis_local_a = vec3(0, 1, 0);
    ASSERT_EQ(physics_constraint_add_slider(full, &extra), UINT32_MAX);
    physics_world_destroy(full);
}

TEST_MAIN_BEGIN()
    RUN_TEST(slider_kills_perpendicular_offset_and_respects_the_limit);
TEST_MAIN_END()
