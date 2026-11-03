#include "test_framework.h"
#include <ai/break_ai.h>
#include <float.h>

static f32 speed(Vec3 value) {
    return sqrtf(value.e[0] * value.e[0] + value.e[2] * value.e[2]);
}

TEST(head_on_velocity_avoidance_is_bounded_and_deterministic) {
    BreakSteerAgent neighbor;
    neighbor.position = vec3(3.0f, 0.0f, 0.0f);
    neighbor.velocity = vec3(-2.0f, 0.0f, 0.0f);
    neighbor.radius = 0.5f;
    Vec3 desired = vec3(2.0f, 0.0f, 0.0f);
    Vec3 output;
    ASSERT_EQ(break_steer_avoid_velocity(vec3(0, 0, 0), desired, 0.5f, 2.0f,
                                         desired, &neighbor, 1, 2.0f, &output), BREAK_NAV_OK);
    ASSERT_TRUE(speed(output) <= 2.0f + 1.0e-5f);
    ASSERT_TRUE(fabsf(output.e[0] - desired.e[0]) > 1.0e-4f ||
                fabsf(output.e[2] - desired.e[2]) > 1.0e-4f);
    Vec3 repeated;
    ASSERT_EQ(break_steer_avoid_velocity(vec3(0, 0, 0), desired, 0.5f, 2.0f,
                                         desired, &neighbor, 1, 2.0f, &repeated), BREAK_NAV_OK);
    ASSERT_EQ(memcmp(&output, &repeated, sizeof(output)), 0);
}

TEST(moving_neighbor_changes_the_avoidance_decision) {
    BreakSteerAgent neighbor;
    neighbor.position = vec3(1.5f, 0.0f, 1.5f);
    neighbor.velocity = vec3(0.0f, 0.0f, 0.0f);
    neighbor.radius = 0.5f;
    Vec3 desired = vec3(2.0f, 0.0f, 0.0f);
    Vec3 static_result;
    ASSERT_EQ(break_steer_avoid_velocity(vec3(0, 0, 0), desired, 0.5f, 2.0f,
                                         desired, &neighbor, 1, 1.0f, &static_result), BREAK_NAV_OK);
    ASSERT_FLOAT_EQ(static_result.e[0], desired.e[0], 1.0e-6);
    ASSERT_FLOAT_EQ(static_result.e[2], desired.e[2], 1.0e-6);
    neighbor.velocity = vec3(0.0f, 0.0f, -2.0f);
    Vec3 moving_result;
    ASSERT_EQ(break_steer_avoid_velocity(vec3(0, 0, 0), desired, 0.5f, 2.0f,
                                         desired, &neighbor, 1, 1.0f, &moving_result), BREAK_NAV_OK);
    ASSERT_TRUE(fabsf(moving_result.e[0] - desired.e[0]) > 1.0e-4f ||
                fabsf(moving_result.e[2] - desired.e[2]) > 1.0e-4f);
}

TEST(reciprocal_agents_integrate_without_overlap) {
    Vec3 a = vec3(0.0f, 0.0f, 0.0f);
    Vec3 b = vec3(5.0f, 0.0f, 0.0f);
    Vec3 va = vec3(2.0f, 0.0f, 0.0f);
    Vec3 vb = vec3(-2.0f, 0.0f, 0.0f);
    f32 minimum = 5.0f;
    for (u32 step = 0; step < 120; step++) {
        BreakSteerAgent neighbor_a;
        neighbor_a.position = b;
        neighbor_a.velocity = vb;
        neighbor_a.radius = 0.5f;
        BreakSteerAgent neighbor_b;
        neighbor_b.position = a;
        neighbor_b.velocity = va;
        neighbor_b.radius = 0.5f;
        Vec3 next_a;
        Vec3 next_b;
        ASSERT_EQ(break_steer_avoid_velocity(a, va, 0.5f, 2.0f, vec3(2, 0, 0),
                                             &neighbor_a, 1, 1.0f, &next_a), BREAK_NAV_OK);
        ASSERT_EQ(break_steer_avoid_velocity(b, vb, 0.5f, 2.0f, vec3(-2, 0, 0),
                                             &neighbor_b, 1, 1.0f, &next_b), BREAK_NAV_OK);
        va = next_a;
        vb = next_b;
        a.e[0] += va.e[0] * 0.05f;
        a.e[2] += va.e[2] * 0.05f;
        b.e[0] += vb.e[0] * 0.05f;
        b.e[2] += vb.e[2] * 0.05f;
        f32 dx = b.e[0] - a.e[0];
        f32 dz = b.e[2] - a.e[2];
        f32 distance = sqrtf(dx * dx + dz * dz);
        if (distance < minimum) {
            minimum = distance;
        }
    }
    ASSERT_TRUE(minimum >= 0.95f);
}

TEST(velocity_avoidance_validates_limits_without_touching_output) {
    BreakSteerAgent neighbors[17];
    memset(neighbors, 0, sizeof(neighbors));
    for (u32 i = 0; i < 17; i++) {
        neighbors[i].position = vec3((f32)i + 2.0f, 0.0f, 0.0f);
        neighbors[i].radius = 0.25f;
    }
    Vec3 output = vec3(7.0f, 8.0f, 9.0f);
    Vec3 before = output;
    ASSERT_EQ(break_steer_avoid_velocity(vec3(0, 0, 0), vec3(0, 0, 0), 0.5f, 2.0f,
                                         vec3(2, 0, 0), neighbors, 17, 1.0f, &output),
              BREAK_NAV_OVERLOAD);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    ASSERT_EQ(break_steer_avoid_velocity(vec3(0, 0, 0), vec3(0, 0, 0), 0.5f, 2.0f,
                                         vec3(NAN, 0, 0), NULL, 0, 1.0f, &output),
              BREAK_NAV_INVALID);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    ASSERT_EQ(break_steer_avoid_velocity(vec3(0, 0, 0), vec3(0, 0, 0), 0.5f, 2.0f,
                                         vec3(4, 0, 0), NULL, 0, 1.0f, &output), BREAK_NAV_OK);
    ASSERT_TRUE(speed(output) <= 2.0f + 1.0e-5f);
}

TEST(extreme_finite_velocity_keeps_direction) {
    Vec3 output;
    ASSERT_EQ(break_steer_avoid_velocity(vec3(0, 0, 0), vec3(0, 0, 0), 0.5f, 2.0f,
                                         vec3(FLT_MAX, 0, FLT_MAX), NULL, 0, 1.0f, &output),
              BREAK_NAV_OK);
    ASSERT_TRUE(output.e[0] > 1.0f);
    ASSERT_TRUE(output.e[2] > 1.0f);
    ASSERT_TRUE(speed(output) <= 2.0f + 1.0e-5f);
}

TEST(extreme_finite_max_speed_still_clamps_diagonal) {
    Vec3 output;
    ASSERT_EQ(break_steer_avoid_velocity(vec3(0, 0, 0), vec3(0, 0, 0), 0.5f, FLT_MAX,
                                         vec3(FLT_MAX, 0, FLT_MAX), NULL, 0, 1.0f, &output),
              BREAK_NAV_OK);
    f32 peak = fmaxf(fabsf(output.e[0]), fabsf(output.e[2]));
    ASSERT_TRUE(peak > 0.0f);
    f32 scaled_x = output.e[0] / peak;
    f32 scaled_z = output.e[2] / peak;
    f32 speed_ratio = (peak / FLT_MAX) * sqrtf(scaled_x * scaled_x + scaled_z * scaled_z);
    ASSERT_TRUE(speed_ratio <= 1.0f + 1.0e-6f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(head_on_velocity_avoidance_is_bounded_and_deterministic);
    RUN_TEST(moving_neighbor_changes_the_avoidance_decision);
    RUN_TEST(reciprocal_agents_integrate_without_overlap);
    RUN_TEST(velocity_avoidance_validates_limits_without_touching_output);
    RUN_TEST(extreme_finite_velocity_keeps_direction);
    RUN_TEST(extreme_finite_max_speed_still_clamps_diagonal);
TEST_MAIN_END()
