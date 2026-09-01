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

TEST(hold_jump_no_apex_boost)
{
    /* R280: holding the jump button must not re-apply jump_speed during the
     * ascent. For the first few frames after takeoff the capsule still overlaps
     * the floor AABB, so `grounded` (recomputed as grounded_v||grounded_h) stays
     * true; before the fix a held jump re-launched from a higher position each
     * of those frames, boosting the apex (multi-jump). A single tap and a held
     * button must reach the same peak height. */
    const f32 dt = 1.0f/60.0f;

    /* Single tap: press jump exactly once, then release. */
    PhysicsWorld *pw1 = physics_world_create(16);
    physics_body_create(pw1, vec3(0, 0, 0), vec3(10, 0.5f, 10), 0.0f, true, 0);
    CharacterController tap = character_create(vec3(0, 1.0f, 0), 0.3f, 1.8f);
    for (int i = 0; i < 120; i++)
        character_update(&tap, pw1, dt, vec3(0,0,0), false);
    f32 apex_tap = tap.position.e[1];
    bool tapped = false;
    for (int i = 0; i < 180; i++) {
        bool j = !tapped;
        character_update(&tap, pw1, dt, vec3(0,0,0), j);
        tapped = true;
        if (tap.position.e[1] > apex_tap) apex_tap = tap.position.e[1];
    }
    physics_world_destroy(pw1);

    /* Held: jump requested every frame from the same rest state. */
    PhysicsWorld *pw2 = physics_world_create(16);
    physics_body_create(pw2, vec3(0, 0, 0), vec3(10, 0.5f, 10), 0.0f, true, 0);
    CharacterController hold = character_create(vec3(0, 1.0f, 0), 0.3f, 1.8f);
    for (int i = 0; i < 120; i++)
        character_update(&hold, pw2, dt, vec3(0,0,0), false);
    f32 apex_hold = hold.position.e[1];
    for (int i = 0; i < 180; i++) {
        character_update(&hold, pw2, dt, vec3(0,0,0), true);
        if (hold.position.e[1] > apex_hold) apex_hold = hold.position.e[1];
    }
    physics_world_destroy(pw2);

    /* No boost: a held button reaches the same apex as a single tap. */
    ASSERT_TRUE(apex_hold <= apex_tap + 0.1f);
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
/*  R436: character controller vs dynamic bodies                            */
/* ----------------------------------------------------------------------- */

/* Walking into a dynamic box shoves it aside; the character (infinite-mass
 * KCC) is not blocked the way a static wall blocks it. */
TEST(character_pushes_dynamic_box)
{
    PhysicsWorld *pw = physics_world_create(16);
    /* Floor, top at y=0 */
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0.0f, true, 0);
    /* Dynamic box directly ahead: x in [2.5, 3.5], resting on the floor */
    u32 box = physics_body_create(pw, vec3(3.0f, 0.5f, 0), vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0);

    CharacterController cc = character_create(vec3(0, 0.0f, 0), 0.4f, 1.8f);
    for (int i = 0; i < 200; i++) {
        character_update(&cc, pw, 1.0f/60.0f, vec3(1, 0, 0), false);
    }
    /* The box must have been pushed away from its spawn position. */
    ASSERT_TRUE(pw->bodies[box].position.e[0] > 3.5f);
    /* Infinite-mass semantics: the character kept walking past the box's
     * original left face (2.5) instead of stopping in front of it. */
    ASSERT_TRUE(cc.position.e[0] > 2.5f);
    physics_world_destroy(pw);
}

/* Dropping onto a dynamic box: its top face is walkable, so the character is
 * supported and reports grounded (same rule as static geometry). */
TEST(character_grounded_on_dynamic_box)
{
    PhysicsWorld *pw = physics_world_create(16);
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0.0f, true, 0);
    /* Dynamic platform with its top at y=1.0 */
    physics_body_create(pw, vec3(0, 0.5f, 0), vec3(1.0f, 0.5f, 1.0f), 1.0f, false, 0);

    CharacterController cc = character_create(vec3(0, 3.0f, 0), 0.4f, 1.8f);
    bool was_grounded = false;
    for (int i = 0; i < 300; i++) {
        character_update(&cc, pw, 1.0f/60.0f, vec3(0,0,0), false);
        if (cc.grounded) was_grounded = true;
    }
    ASSERT_TRUE(was_grounded);
    /* Feet rest on the box top (y=1.0), not sunk to the floor (y=0). */
    ASSERT_TRUE(cc.position.e[1] > 0.9f);
    ASSERT_TRUE(cc.position.e[1] < 1.2f);
    physics_world_destroy(pw);
}

/* physics_push_body: invalid ids, static bodies and parked tombstones are
 * safe no-ops; a valid push moves the body by normal*depth and clears
 * rest_frames (R432 contract). */
TEST(physics_push_body_invalid_safe)
{
    PhysicsWorld *pw = physics_world_create(16);
    u32 stat = physics_body_create(pw, vec3(0, 0, 0), vec3(1, 1, 1), 0.0f, true, 0);
    u32 dyn  = physics_body_create(pw, vec3(5, 0, 0), vec3(1, 1, 1), 1.0f, false, 0);

    /* Out-of-range id: no crash, no effect. */
    physics_push_body(pw, 999, vec3(1, 0, 0), 1.0f);
    /* Static body: not movable. */
    physics_push_body(pw, stat, vec3(1, 0, 0), 1.0f);
    ASSERT_TRUE(pw->bodies[stat].position.e[0] == 0.0f);
    /* Parked tombstone (moved to (0,-1000,0) by park): push must not move it. */
    physics_body_park(pw, dyn);
    physics_push_body(pw, dyn, vec3(1, 0, 0), 1.0f);
    ASSERT_TRUE(pw->bodies[dyn].position.e[1] == -1000.0f);

    /* Valid push: full normal*depth separation (capsule side is immovable),
     * rest_frames cleared so the BVH refit cannot skip the stale AABB. */
    u32 dyn2 = physics_body_create(pw, vec3(9, 0, 0), vec3(1, 1, 1), 1.0f, false, 0);
    pw->bodies[dyn2].rest_frames = 5;
    physics_push_body(pw, dyn2, vec3(1, 0, 0), 0.5f);
    ASSERT_TRUE(fabsf(pw->bodies[dyn2].position.e[0] - 9.5f) < 1e-4f);
    ASSERT_TRUE(pw->bodies[dyn2].rest_frames == 0);
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */
/*  R437: platform velocity inheritance (ride moving dynamic platforms)     */
/* ----------------------------------------------------------------------- */

/* Tests do not run physics_step, so a "kinematic" platform is moved by
 * integrating position manually and clearing rest_frames (BVH-refit contract),
 * with velocity set for the controller to inherit. */
static void r437_move_platform(PhysicsWorld *pw, u32 plat, Vec3 v, f32 dt) {
    pw->bodies[plat].velocity = v;
    pw->bodies[plat].position = vec3_add(pw->bodies[plat].position,
                                         vec3_scale(v, dt));
    pw->bodies[plat].rest_frames = 0;
}

/* A character standing on a horizontally moving dynamic platform is carried
 * with it: zero input, Δx == Σ v*dt. Without inheritance the platform slides
 * out from under the character, which drops to the floor and stays behind. */
TEST(character_rides_moving_platform)
{
    PhysicsWorld *pw = physics_world_create(16);
    /* Floor, top at y=0 */
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0.0f, true, 0);
    /* Dynamic platform, top at y=1.0, 4x4 m so the character stays aboard */
    u32 plat = physics_body_create(pw, vec3(0, 0.5f, 0), vec3(2.0f, 0.5f, 2.0f), 1.0f, false, 0);

    CharacterController cc = character_create(vec3(0, 1.2f, 0), 0.4f, 1.8f);
    const f32 dt = 1.0f/60.0f;
    for (int i = 0; i < 60; i++)
        character_update(&cc, pw, dt, vec3(0,0,0), false);
    ASSERT_TRUE(cc.grounded);
    const f32 start_x = cc.position.e[0];

    const f32 vx = 2.0f;
    const int frames = 120;
    for (int i = 0; i < frames; i++) {
        r437_move_platform(pw, plat, vec3(vx, 0, 0), dt);
        character_update(&cc, pw, dt, vec3(0,0,0), false);
    }
    /* Carried the full Σ v*dt and still standing on the platform top. */
    ASSERT_TRUE(fabsf(cc.position.e[0] - (start_x + vx * dt * (f32)frames)) < 0.05f);
    ASSERT_TRUE(fabsf(cc.position.e[1] - 1.0f) < 0.1f);
    ASSERT_TRUE(cc.grounded);
    physics_world_destroy(pw);
}

/* Vertical inheritance: a descending platform carries the character down so
 * the feet keep tracking its top face (free-fall alone cannot keep up).
 * The platform moves before character_update, mirroring the real game loop
 * (physics_step advances bodies, then the character inherits velocity from
 * the support recorded on the previous contact frame). */
TEST(character_rides_descending_platform)
{
    PhysicsWorld *pw = physics_world_create(16);
    /* No floor: the platform is the only support. Top at y=1.0. */
    u32 plat = physics_body_create(pw, vec3(0, 0.5f, 0), vec3(2.0f, 0.5f, 2.0f), 1.0f, false, 0);

    CharacterController cc = character_create(vec3(0, 1.2f, 0), 0.4f, 1.8f);
    const f32 dt = 1.0f/60.0f;
    for (int i = 0; i < 60; i++)
        character_update(&cc, pw, dt, vec3(0,0,0), false);
    ASSERT_TRUE(cc.grounded);

    const f32 vy = -8.0f;
    for (int i = 0; i < 30; i++) {
        r437_move_platform(pw, plat, vec3(0, vy, 0), dt);
        character_update(&cc, pw, dt, vec3(0,0,0), false);
    }
    const f32 top = pw->bodies[plat].position.e[1] + 0.5f;
    ASSERT_TRUE(fabsf(cc.position.e[1] - top) < 0.05f);
    ASSERT_TRUE(cc.grounded);
    physics_world_destroy(pw);
}

/* Boundary: a stationary dynamic platform (velocity 0) imparts no motion;
 * the character stays put (also guarded by character_zero_input_still). */
TEST(character_stationary_platform_no_carry)
{
    PhysicsWorld *pw = physics_world_create(16);
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0.0f, true, 0);
    u32 plat = physics_body_create(pw, vec3(0, 0.5f, 0), vec3(2.0f, 0.5f, 2.0f), 1.0f, false, 0);

    CharacterController cc = character_create(vec3(0, 1.2f, 0), 0.4f, 1.8f);
    const f32 dt = 1.0f/60.0f;
    for (int i = 0; i < 60; i++)
        character_update(&cc, pw, dt, vec3(0,0,0), false);
    ASSERT_TRUE(cc.grounded);
    const f32 x0 = cc.position.e[0];
    const f32 y0 = cc.position.e[1];

    for (int i = 0; i < 120; i++) {
        r437_move_platform(pw, plat, vec3(0, 0, 0), dt);
        character_update(&cc, pw, dt, vec3(0,0,0), false);
    }
    ASSERT_TRUE(fabsf(cc.position.e[0] - x0) < 1e-4f);
    ASSERT_TRUE(fabsf(cc.position.e[1] - y0) < 1e-4f);
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */
/*  Repo-review: fast fall onto a thin slab (capsule skewer + stale ground) */
/* ----------------------------------------------------------------------- */

/* A character falling ~63 m/s moves >1 m per frame, so its capsule axis
 * crosses a thin slab's interior in a single step. The old single-point
 * capsule-vs-box MTV faced the wrong side of the mid-plane and under-
 * separated, shoving the character THROUGH the slab; the sticky grounded
 * flag then reported a stale supported state. Must end ON TOP, grounded. */
TEST(character_fast_fall_lands_on_slab)
{
    PhysicsWorld *pw = physics_world_create(16);
    /* 1 m thick slab, top at y=0.5. */
    physics_body_create(pw, vec3(0, 0, 0), vec3(10, 0.5f, 10), 0.0f, true, 0);

    CharacterController cc = character_create(vec3(0, 1.6f, 0), 0.3f, 1.8f);
    const f32 dt = 1.0f / 60.0f;
    cc.velocity.e[1] = -63.0f;  /* >1 m of fall per frame: skewer case */
    for (int i = 0; i < 10; i++)
        character_update(&cc, pw, dt, vec3(0, 0, 0), false);

    /* Feet must rest ON the slab top (y=0.5), supported, fall stopped. */
    ASSERT_TRUE(cc.grounded);
    ASSERT_TRUE(cc.position.e[1] > 0.4f);
    ASSERT_TRUE(cc.position.e[1] < 0.7f);
    ASSERT_TRUE(cc.velocity.e[1] == 0.0f);
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */
/*  Repo-review: sweep NaN rejection + idle rsqrt guard                     */
/* ----------------------------------------------------------------------- */

TEST(sweep_test_rejects_nan)
{
    PhysicsWorld *pw = physics_world_create(16);
    physics_body_create(pw, vec3(5, 0, 0), vec3(1, 1, 1), 0.0f, true, 0);
    physics_step(pw, 0.001f);

    /* NaN origin/delta used to pass every slab comparison -> phantom hit t=0. */
    ASSERT_TRUE(!physics_sweep_test(pw, vec3(NAN, 0, 0), vec3(10, 0, 0), 999, NULL, NULL));
    ASSERT_TRUE(!physics_sweep_test(pw, vec3(0, 0, 0), vec3(10, NAN, 0), 999, NULL, NULL));
    /* Sane sweep still hits. */
    ASSERT_TRUE(physics_sweep_test(pw, vec3(0, 0, 0), vec3(10, 0, 0), 999, NULL, NULL));
    physics_world_destroy(pw);
}

TEST(character_idle_position_stays_finite)
{
    /* fast_rsqrt(0) = +inf made horiz_len = 0*inf = NaN with zero input. */
    PhysicsWorld *pw = physics_world_create(16);
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0.0f, true, 0);

    CharacterController cc = character_create(vec3(0, 0.2f, 0), 0.3f, 1.8f);
    for (int i = 0; i < 120; i++)
        character_update(&cc, pw, 1.0f / 60.0f, vec3(0, 0, 0), false);

    ASSERT_TRUE(isfinite(cc.position.e[0]));
    ASSERT_TRUE(isfinite(cc.position.e[1]));
    ASSERT_TRUE(isfinite(cc.position.e[2]));
    ASSERT_TRUE(isfinite(cc.velocity.e[0]));
    ASSERT_TRUE(isfinite(cc.velocity.e[1]));
    ASSERT_TRUE(isfinite(cc.velocity.e[2]));
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(character_create_basic);
    RUN_TEST(character_gravity_fall);
    RUN_TEST(character_movement);
    RUN_TEST(character_ground_collision);
    RUN_TEST(character_jump);
    RUN_TEST(hold_jump_no_apex_boost);
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
    /* R436: character vs dynamic bodies */
    RUN_TEST(character_pushes_dynamic_box);
    RUN_TEST(character_grounded_on_dynamic_box);
    RUN_TEST(physics_push_body_invalid_safe);
    /* R437: platform velocity inheritance */
    RUN_TEST(character_rides_moving_platform);
    RUN_TEST(character_rides_descending_platform);
    RUN_TEST(character_stationary_platform_no_carry);
    /* Repo-review: skewer fall-through, NaN sweep, idle rsqrt */
    RUN_TEST(character_fast_fall_lands_on_slab);
    RUN_TEST(sweep_test_rejects_nan);
    RUN_TEST(character_idle_position_stays_finite);
TEST_MAIN_END()
