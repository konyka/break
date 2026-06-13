/* ==========================================================================
 *  test_character.c — Unit tests for character controller + sweep test.
 * ========================================================================== */

#include "test_framework.h"
#include <physics/character.h>
#include <math.h>

/* ----------------------------------------------------------------------- */

TEST(character_create_basic)
{
    CharacterController cc = character_create(vec3(0, 5, 0), 0.3f, 1.8f);
    ASSERT_TRUE(fabsf(cc.position.e[1] - 5.0f) < 0.001f);
    ASSERT_TRUE(fabsf(cc.radius - 0.3f) < 0.001f);
    ASSERT_TRUE(fabsf(cc.height - 1.8f) < 0.001f);
    ASSERT_TRUE(!cc.grounded);
    ASSERT_TRUE(!cc.jump_requested);
}

TEST(character_gravity_fall)
{
    PhysicsWorld *pw = physics_world_create(16);
    CharacterController cc = character_create(vec3(0, 10, 0), 0.3f, 1.8f);

    f32 y0 = cc.position.e[1];
    for (int i = 0; i < 30; i++) {
        character_update(&cc, pw, 1.0f/60.0f, vec3(0,0,0), false);
    }
    ASSERT_TRUE(cc.position.e[1] < y0);
    physics_world_destroy(pw);
}

TEST(character_movement)
{
    PhysicsWorld *pw = physics_world_create(16);
    CharacterController cc = character_create(vec3(0, 0, 0), 0.3f, 1.8f);

    /* Move forward (positive Z) */
    character_update(&cc, pw, 1.0f/60.0f, vec3(0, 0, 1), false);
    /* Should have moved in Z direction (with damping applied) */
    ASSERT_TRUE(cc.position.e[2] > 0.0f);
    physics_world_destroy(pw);
}

TEST(character_ground_collision)
{
    PhysicsWorld *pw = physics_world_create(16);
    /* Create a static floor at y=0 (top surface at y=0.5) */
    physics_body_create(pw, vec3(0, 0, 0), vec3(10, 0.5f, 10), 0.0f, true, 0);

    /* Character starts above floor, should land */
    CharacterController cc = character_create(vec3(0, 2.0f, 0), 0.3f, 1.8f);

    bool was_grounded = false;
    for (int i = 0; i < 300; i++) {
        character_update(&cc, pw, 1.0f/60.0f, vec3(0,0,0), false);
        if (cc.grounded) was_grounded = true;
    }

    /* Character should have been grounded at some point */
    ASSERT_TRUE(was_grounded);
    /* And position should be near the floor surface */
    ASSERT_TRUE(cc.position.e[1] < 3.0f);
    physics_world_destroy(pw);
}

TEST(character_jump)
{
    PhysicsWorld *pw = physics_world_create(16);
    /* Floor */
    physics_body_create(pw, vec3(0, 0, 0), vec3(10, 0.5f, 10), 0.0f, true, 0);

    CharacterController cc = character_create(vec3(0, 1.0f, 0), 0.3f, 1.8f);

    /* Settle on ground first, find a frame where grounded=true */
    bool found_grounded = false;
    for (int i = 0; i < 300; i++) {
        character_update(&cc, pw, 1.0f/60.0f, vec3(0,0,0), false);
        if (cc.grounded) {
            found_grounded = true;
            /* Immediately request jump while grounded */
            character_update(&cc, pw, 1.0f/60.0f, vec3(0,0,0), true);
            break;
        }
    }
    ASSERT_TRUE(found_grounded);

    /* After jump, velocity should be upward or position increased */
    ASSERT_TRUE(cc.velocity.e[1] > 0.0f || !cc.grounded);
    physics_world_destroy(pw);
}

TEST(get_position)
{
    CharacterController cc = character_create(vec3(1, 2, 3), 0.3f, 1.8f);
    Vec3 p = character_get_position(&cc);
    ASSERT_TRUE(fabsf(p.e[0] - 1.0f) < 0.001f);
    ASSERT_TRUE(fabsf(p.e[1] - 2.0f) < 0.001f);
    ASSERT_TRUE(fabsf(p.e[2] - 3.0f) < 0.001f);
}

TEST(is_grounded_initial)
{
    CharacterController cc = character_create(vec3(0, 0, 0), 0.3f, 1.8f);
    ASSERT_TRUE(!character_is_grounded(&cc));
}

TEST(sweep_test_hit)
{
    PhysicsWorld *pw = physics_world_create(16);
    physics_body_create(pw, vec3(5, 0, 0), vec3(1, 1, 1), 0.0f, true, 0);
    physics_step(pw, 0.001f); /* Force BVH rebuild */

    Vec3 hit_pos;
    f32 t;
    bool hit = physics_sweep_test(pw, vec3(0, 0, 0), vec3(10, 0, 0), 999, &hit_pos, &t);
    ASSERT_TRUE(hit);
    ASSERT_TRUE(t > 0.0f && t < 1.0f);
    physics_world_destroy(pw);
}

TEST(sweep_test_miss)
{
    PhysicsWorld *pw = physics_world_create(16);
    physics_body_create(pw, vec3(5, 0, 0), vec3(1, 1, 1), 0.0f, true, 0);
    physics_step(pw, 0.001f);

    /* Sweep in opposite direction */
    bool hit = physics_sweep_test(pw, vec3(0, 0, 0), vec3(-10, 0, 0), 999, NULL, NULL);
    ASSERT_TRUE(!hit);
    physics_world_destroy(pw);
}

TEST(sweep_test_ignore_body)
{
    PhysicsWorld *pw = physics_world_create(16);
    u32 id = physics_body_create(pw, vec3(5, 0, 0), vec3(1, 1, 1), 0.0f, true, 0);
    physics_step(pw, 0.001f);

    /* Ignore the only body */
    bool hit = physics_sweep_test(pw, vec3(0, 0, 0), vec3(10, 0, 0), id, NULL, NULL);
    ASSERT_TRUE(!hit);
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(sweep_test_empty_world)
{
    PhysicsWorld *pw = physics_world_create(16);
    physics_step(pw, 0.001f);

    /* Sweep in empty world should not crash and return false */
    bool hit = physics_sweep_test(pw, vec3(0, 0, 0), vec3(10, 0, 0), 999, NULL, NULL);
    ASSERT_TRUE(!hit);
    physics_world_destroy(pw);
}

TEST(character_zero_input_still)
{
    PhysicsWorld *pw = physics_world_create(16);
    CharacterController cc = character_create(vec3(0, 0, 0), 0.3f, 1.8f);

    /* With zero input and no gravity (in air), horizontal position should stay */
    Vec3 pos0 = cc.position;
    character_update(&cc, pw, 1.0f/60.0f, vec3(0,0,0), false);

    /* X and Z should be unchanged (only Y changes due to gravity) */
    ASSERT_TRUE(fabsf(cc.position.e[0] - pos0.e[0]) < 0.001f);
    ASSERT_TRUE(fabsf(cc.position.e[2] - pos0.e[2]) < 0.001f);
    physics_world_destroy(pw);
}

TEST(character_create_zero_dimensions)
{
    /* Edge case: zero radius and height - should not crash */
    CharacterController cc = character_create(vec3(0, 0, 0), 0.0f, 0.0f);
    ASSERT_TRUE(fabsf(cc.radius) < 0.001f);
    ASSERT_TRUE(fabsf(cc.height) < 0.001f);
}

TEST(character_large_movement)
{
    PhysicsWorld *pw = physics_world_create(16);
    CharacterController cc = character_create(vec3(0, 0, 0), 0.3f, 1.8f);

    /* Apply large input - should be clamped/damped */
    character_update(&cc, pw, 1.0f/60.0f, vec3(1000, 0, 1000), false);

    /* Position should not be absurdly large due to damping */
    ASSERT_TRUE(cc.position.e[0] < 100.0f);
    ASSERT_TRUE(cc.position.e[2] < 100.0f);
    physics_world_destroy(pw);
}

TEST(sweep_test_zero_movement)
{
    PhysicsWorld *pw = physics_world_create(16);
    physics_body_create(pw, vec3(5, 0, 0), vec3(1, 1, 1), 0.0f, true, 0);
    physics_step(pw, 0.001f);

    /* Zero-length sweep should not hit anything */
    bool hit = physics_sweep_test(pw, vec3(0, 0, 0), vec3(0, 0, 0), 999, NULL, NULL);
    ASSERT_TRUE(!hit);
    physics_world_destroy(pw);
}

TEST(character_create_negative_dimensions)
{
    /* Edge case: negative radius and height - implementation-defined */
    CharacterController cc = character_create(vec3(0, 0, 0), -1.0f, -2.0f);
    /* Just verify no crash */
    (void)cc;
    ASSERT_TRUE(true);
}

TEST(character_multiple_updates)
{
    PhysicsWorld *pw = physics_world_create(16);
    /* Floor */
    physics_body_create(pw, vec3(0, 0, 0), vec3(10, 0.5f, 10), 0.0f, true, 0);

    CharacterController cc = character_create(vec3(0, 5.0f, 0), 0.3f, 1.8f);

    /* Run many updates */
    for (int i = 0; i < 1000; i++) {
        character_update(&cc, pw, 1.0f/60.0f, vec3(0,0,0), false);
    }

    /* Character should have settled somewhere */
    ASSERT_TRUE(cc.position.e[1] < 10.0f);
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */
/*  Round 6: capsule collide-and-slide, step-up, wall block                 */
/* ----------------------------------------------------------------------- */

/* Walking into a tall wall should not pass through it. */
TEST(character_wall_block)
{
    PhysicsWorld *pw = physics_world_create(16);
    /* Floor */
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0.0f, true, 0);
    /* Tall wall: spans x in [2.5, 3.5], up to y=3 */
    physics_body_create(pw, vec3(3.0f, 1.5f, 0), vec3(0.5f, 1.5f, 5), 0.0f, true, 0);

    CharacterController cc = character_create(vec3(0, 0.0f, 0), 0.4f, 1.8f);

    /* Walk toward +x for a while. */
    for (int i = 0; i < 200; i++) {
        character_update(&cc, pw, 1.0f/60.0f, vec3(1, 0, 0), false);
    }
    /* Character (radius 0.4) must be stopped before the wall's left face (2.5). */
    ASSERT_TRUE(cc.position.e[0] < 2.5f);
    physics_world_destroy(pw);
}

/* A low step within step_height should be climbed. */
TEST(character_step_up)
{
    PhysicsWorld *pw = physics_world_create(16);
    /* Floor at y top = 0 */
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0.0f, true, 0);
    /* Low step: top at y=0.25 (within default step_height 0.3), x in [2,4] */
    physics_body_create(pw, vec3(3.0f, 0.125f, 0), vec3(1.0f, 0.125f, 5), 0.0f, true, 0);

    CharacterController cc = character_create(vec3(0, 0.0f, 0), 0.4f, 1.8f);

    /* Walk forward; the step is only 4 units wide on a 40-wide floor, so track
     * the peak height while traversing it rather than the final resting pose. */
    f32 max_y = 0.0f;
    f32 x_at_peak = 0.0f;
    for (int i = 0; i < 60; i++) {
        character_update(&cc, pw, 1.0f/60.0f, vec3(1, 0, 0), false);
        if (cc.position.e[1] > max_y) {
            max_y = cc.position.e[1];
            x_at_peak = cc.position.e[0];
        }
    }
    /* Character should have climbed onto the step top (~0.25) while over it. */
    ASSERT_TRUE(max_y > 0.2f);
    ASSERT_TRUE(x_at_peak > 2.0f);  /* lifted while standing on top of the step */
    physics_world_destroy(pw);
}

/* A tall step above step_height should block (no climb). */
TEST(character_high_step_blocks)
{
    PhysicsWorld *pw = physics_world_create(16);
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0.0f, true, 0);
    /* High step: top at y=1.0 (> step_height) */
    physics_body_create(pw, vec3(3.0f, 0.5f, 0), vec3(1.0f, 0.5f, 5), 0.0f, true, 0);

    CharacterController cc = character_create(vec3(0, 0.0f, 0), 0.4f, 1.8f);

    for (int i = 0; i < 300; i++) {
        character_update(&cc, pw, 1.0f/60.0f, vec3(1, 0, 0), false);
    }
    /* Should be blocked before the step (x in [2,4], left face 2.0). */
    ASSERT_TRUE(cc.position.e[0] < 2.05f);
    ASSERT_TRUE(cc.position.e[1] < 0.3f);  /* stayed on the ground floor */
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(character_create_basic);
    RUN_TEST(character_gravity_fall);
    RUN_TEST(character_movement);
    RUN_TEST(character_ground_collision);
    RUN_TEST(character_jump);
    RUN_TEST(get_position);
    RUN_TEST(is_grounded_initial);
    RUN_TEST(sweep_test_hit);
    RUN_TEST(sweep_test_miss);
    RUN_TEST(sweep_test_ignore_body);
    /* Edge cases */
    RUN_TEST(sweep_test_empty_world);
    RUN_TEST(character_zero_input_still);
    RUN_TEST(character_create_zero_dimensions);
    RUN_TEST(character_large_movement);
    RUN_TEST(sweep_test_zero_movement);
    RUN_TEST(character_create_negative_dimensions);
    RUN_TEST(character_multiple_updates);
    /* Round 6: capsule collide-and-slide */
    RUN_TEST(character_wall_block);
    RUN_TEST(character_step_up);
    RUN_TEST(character_high_step_blocks);
TEST_MAIN_END()
