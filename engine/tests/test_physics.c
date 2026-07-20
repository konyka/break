/* ==========================================================================
 *  test_physics.c — Unit tests for the physics + BVH module.
 * ========================================================================== */

#include "test_framework.h"
#include <physics/physics.h>
#include <math.h>

/* ----------------------------------------------------------------------- */
/*  AABB utilities                                                          */
/* ----------------------------------------------------------------------- */

TEST(aabb_from_body_basic)
{
    RigidBody b = {0};
    b.position     = vec3(5, 10, 15);
    b.half_extent  = vec3(1, 2, 3);
    AABB a = aabb_from_body(&b);
    ASSERT_TRUE(fabsf(a.min.e[0] - 4.0f) < 0.001f);
    ASSERT_TRUE(fabsf(a.min.e[1] - 8.0f) < 0.001f);
    ASSERT_TRUE(fabsf(a.min.e[2] - 12.0f) < 0.001f);
    ASSERT_TRUE(fabsf(a.max.e[0] - 6.0f) < 0.001f);
    ASSERT_TRUE(fabsf(a.max.e[1] - 12.0f) < 0.001f);
    ASSERT_TRUE(fabsf(a.max.e[2] - 18.0f) < 0.001f);
}

TEST(aabb_overlap_true)
{
    AABB a = { .min = vec3(0,0,0), .max = vec3(2,2,2) };
    AABB b = { .min = vec3(1,1,1), .max = vec3(3,3,3) };
    ASSERT_TRUE(aabb_overlap(a, b));
}

TEST(aabb_overlap_false)
{
    AABB a = { .min = vec3(0,0,0), .max = vec3(1,1,1) };
    AABB b = { .min = vec3(2,2,2), .max = vec3(3,3,3) };
    ASSERT_TRUE(!aabb_overlap(a, b));
}

TEST(aabb_overlap_touching)
{
    AABB a = { .min = vec3(0,0,0), .max = vec3(1,1,1) };
    AABB b = { .min = vec3(1,0,0), .max = vec3(2,1,1) };
    /* Touching edges count as overlapping (>=) */
    ASSERT_TRUE(aabb_overlap(a, b));
}

/* ----------------------------------------------------------------------- */
/*  PhysicsWorld                                                             */
/* ----------------------------------------------------------------------- */

TEST(world_create_destroy)
{
    PhysicsWorld *pw = physics_world_create(64);
    ASSERT_NOT_NULL(pw);
    ASSERT_EQ(pw->count, 0u);
    ASSERT_EQ(pw->capacity, 64u);
    physics_world_destroy(pw);
}

TEST(body_create)
{
    PhysicsWorld *pw = physics_world_create(64);
    u32 id = physics_body_create(pw, vec3(0,5,0), vec3(0.5f,0.5f,0.5f), 1.0f, false, 0);
    ASSERT_EQ(id, 0u);
    ASSERT_EQ(pw->count, 1u);
    ASSERT_TRUE(fabsf(pw->bodies[0].position.e[1] - 5.0f) < 0.001f);
    ASSERT_TRUE(!pw->bodies[0].is_static);
    physics_world_destroy(pw);
}

TEST(body_static)
{
    PhysicsWorld *pw = physics_world_create(64);
    u32 id = physics_body_create(pw, vec3(0,0,0), vec3(10,0.1f,10), 0.0f, true, 0);
    ASSERT_EQ(id, 0u);
    ASSERT_TRUE(pw->bodies[0].is_static);
    ASSERT_TRUE(pw->bodies[0].mass == 0.0f);
    physics_world_destroy(pw);
}

TEST(gravity_fall)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(0,10,0), vec3(0.5f,0.5f,0.5f), 1.0f, false, 0);

    f32 y0 = pw->bodies[0].position.e[1];
    /* Step 60 times at 1/60s = 1 second */
    for (int i = 0; i < 60; i++) physics_step(pw, 1.0f/60.0f);
    f32 y1 = pw->bodies[0].position.e[1];
    /* After 1s of gravity, body should have fallen */
    ASSERT_TRUE(y1 < y0);
    physics_world_destroy(pw);
}

TEST(impulse)
{
    PhysicsWorld *pw = physics_world_create(64);
    u32 id = physics_body_create(pw, vec3(0,0,0), vec3(0.5f,0.5f,0.5f), 2.0f, false, 0);
    /* Apply upward impulse: F=20N, mass=2kg -> dv=10 m/s */
    physics_body_apply_impulse(pw, id, vec3(0, 20.0f, 0));
    ASSERT_TRUE(pw->bodies[id].velocity.e[1] > 9.0f);
    physics_world_destroy(pw);
}

TEST(impulse_static_ignored)
{
    PhysicsWorld *pw = physics_world_create(64);
    u32 id = physics_body_create(pw, vec3(0,0,0), vec3(1,1,1), 0.0f, true, 0);
    physics_body_apply_impulse(pw, id, vec3(100, 100, 100));
    ASSERT_TRUE(fabsf(pw->bodies[id].velocity.e[0]) < 0.001f);
    physics_world_destroy(pw);
}

TEST(collision_detection)
{
    PhysicsWorld *pw = physics_world_create(64);
    /* Two overlapping dynamic bodies */
    physics_body_create(pw, vec3(0, 0, 0), vec3(1,1,1), 1.0f, false, 0);
    physics_body_create(pw, vec3(0.5f, 0, 0), vec3(1,1,1), 1.0f, false, 0);

    physics_step(pw, 1.0f/60.0f);
    /* Should detect at least one collision */
    ASSERT_TRUE(pw->collision_count > 0);
    physics_world_destroy(pw);
}

TEST(collision_resolves_approach_velocity)
{
    /* R262: two equal-mass dynamic boxes overlapping and moving toward each other
     * must have their approach velocity resolved (stopped/reversed) by the normal
     * impulse. Before the fix the inverted guard skipped the impulse whenever the
     * bodies were approaching, leaving the closing velocity untouched. */
    PhysicsWorld *pw = physics_world_create(64);
    u32 a = physics_body_create(pw, vec3(-0.9f, 0, 0), vec3(1,1,1), 1.0f, false, 0);
    u32 b = physics_body_create(pw, vec3( 0.9f, 0, 0), vec3(1,1,1), 1.0f, false, 0);
    pw->bodies[a].velocity = vec3( 5, 0, 0);  /* A moving +X toward B */
    pw->bodies[b].velocity = vec3(-5, 0, 0);  /* B moving -X toward A */

    physics_step(pw, 1.0f/60.0f);

    ASSERT_TRUE(pw->collision_count > 0);
    /* A was closing at +4.9 (post-damping). Resolved it must no longer race
     * toward B; with restitution 0.3 it reverses to ~-1.5. Buggy code left ~+4.9. */
    ASSERT_TRUE(pw->bodies[a].velocity.e[0] < 1.0f);
    ASSERT_TRUE(pw->bodies[b].velocity.e[0] > -1.0f);
    physics_world_destroy(pw);
}

TEST(ground_respawn)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(0,-20,0), vec3(0.5f,0.5f,0.5f), 1.0f, false, 0);

    /* The body is already below -10, step should trigger respawn */
    physics_step(pw, 1.0f/60.0f);
    ASSERT_TRUE(pw->respawn_count > 0);
    physics_world_destroy(pw);
}

TEST(raycast_hit)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(5, 0, 0), vec3(1,1,1), 1.0f, false, 0);

    /* Force BVH rebuild */
    physics_step(pw, 0.001f);

    u32 hit_body = 0;
    f32 hit_t = 0;
    bool hit = physics_raycast(pw, vec3(0,0,0), vec3(1,0,0), 100.0f, &hit_body, &hit_t);
    ASSERT_TRUE(hit);
    ASSERT_EQ(hit_body, 0u);
    ASSERT_TRUE(hit_t > 0.0f);
    physics_world_destroy(pw);
}

TEST(raycast_miss)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(5, 0, 0), vec3(1,1,1), 1.0f, false, 0);
    physics_step(pw, 0.001f);

    /* Shoot in opposite direction */
    bool hit = physics_raycast(pw, vec3(0,0,0), vec3(-1,0,0), 100.0f, NULL, NULL);
    ASSERT_TRUE(!hit);
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */
/*  BVH standalone                                                          */
/* ----------------------------------------------------------------------- */

TEST(bvh_build_query)
{
    BVH bvh;
    bvh_init(&bvh, 4);

    BVHAABB aabbs[4];
    aabbs[0] = (BVHAABB){ .min = vec3(0,0,0),  .max = vec3(1,1,1) };
    aabbs[1] = (BVHAABB){ .min = vec3(5,5,5),  .max = vec3(6,6,6) };
    aabbs[2] = (BVHAABB){ .min = vec3(0.5f,0,0), .max = vec3(1.5f,1,1) }; /* overlaps with 0 */
    aabbs[3] = (BVHAABB){ .min = vec3(20,20,20), .max = vec3(21,21,21) };

    bvh_build(&bvh, aabbs, 4);
    ASSERT_TRUE(bvh.node_count > 0);

    /* Query AABB overlapping with box 0 and 2 */
    u32 results[8];
    u32 found = bvh_query_aabb(&bvh, (BVHAABB){ .min = vec3(0.2f,0.2f,0.2f), .max = vec3(0.8f,0.8f,0.8f) }, results, 8);
    ASSERT_TRUE(found >= 1);

    bvh_destroy(&bvh);
}

TEST(bvh_raycast_test)
{
    BVH bvh;
    bvh_init(&bvh, 2);

    BVHAABB aabbs[2];
    aabbs[0] = (BVHAABB){ .min = vec3(4,-1,-1), .max = vec3(6,1,1) };
    aabbs[1] = (BVHAABB){ .min = vec3(10,10,10), .max = vec3(11,11,11) };
    bvh_build(&bvh, aabbs, 2);

    BVHRayHit hit;
    bool ok = bvh_raycast(&bvh, vec3(0,0,0), vec3(1,0,0), 100.0f, &hit);
    ASSERT_TRUE(ok);
    ASSERT_EQ(hit.object_index, 0u);

    bvh_destroy(&bvh);
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(physics_empty_world_raycast)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_step(pw, 0.001f);

    /* Raycast in empty world should not crash and return false */
    bool hit = physics_raycast(pw, vec3(0,0,0), vec3(1,0,0), 100.0f, NULL, NULL);
    ASSERT_TRUE(!hit);
    physics_world_destroy(pw);
}

TEST(physics_zero_velocity_body)
{
    PhysicsWorld *pw = physics_world_create(64);
    u32 id = physics_body_create(pw, vec3(0,0,0), vec3(1,1,1), 1.0f, false, 0);

    /* Body with zero velocity should not move without forces */
    Vec3 pos0 = pw->bodies[id].position;
    physics_step(pw, 1.0f/60.0f);
    Vec3 pos1 = pw->bodies[id].position;

    /* Position should change due to gravity */
    ASSERT_TRUE(pos1.e[1] < pos0.e[1]);
    physics_world_destroy(pw);
}

TEST(bvh_single_object)
{
    BVH bvh;
    bvh_init(&bvh, 1);

    BVHAABB aabbs[1];
    aabbs[0] = (BVHAABB){ .min = vec3(0,0,0), .max = vec3(1,1,1) };
    bvh_build(&bvh, aabbs, 1);
    ASSERT_TRUE(bvh.node_count > 0);

    /* Query should find the single object */
    u32 results[8];
    u32 found = bvh_query_aabb(&bvh, (BVHAABB){ .min = vec3(-1,-1,-1), .max = vec3(2,2,2) }, results, 8);
    ASSERT_EQ(found, 1u);

    bvh_destroy(&bvh);
}

TEST(physics_body_at_origin_raycast)
{
    PhysicsWorld *pw = physics_world_create(64);
    /* Body at exact origin */
    physics_body_create(pw, vec3(0,0,0), vec3(1,1,1), 1.0f, false, 0);
    physics_step(pw, 0.001f);

    u32 hit_body = 999;
    f32 hit_t = -1.0f;
    bool hit = physics_raycast(pw, vec3(-5,0,0), vec3(1,0,0), 100.0f, &hit_body, &hit_t);
    ASSERT_TRUE(hit);
    ASSERT_EQ(hit_body, 0u);
    physics_world_destroy(pw);
}

TEST(physics_zero_length_raycast)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(5,0,0), vec3(1,1,1), 1.0f, false, 0);
    physics_step(pw, 0.001f);

    /* Zero-length raycast should not hit anything */
    bool hit = physics_raycast(pw, vec3(0,0,0), vec3(1,0,0), 0.0f, NULL, NULL);
    ASSERT_TRUE(!hit);
    physics_world_destroy(pw);
}

TEST(physics_very_large_mass)
{
    PhysicsWorld *pw = physics_world_create(64);
    /* Very large mass body */
    u32 id = physics_body_create(pw, vec3(0,0,0), vec3(1,1,1), 1e10f, false, 0);
    ASSERT_EQ(id, 0u);

    /* Apply small impulse to very heavy body - should barely move */
    physics_body_apply_impulse(pw, id, vec3(1.0f, 0.0f, 0.0f));
    ASSERT_TRUE(fabsf(pw->bodies[id].velocity.e[0]) < 1e-6f);
    physics_world_destroy(pw);
}

TEST(bvh_empty_build)
{
    BVH bvh;
    bvh_init(&bvh, 0);

    /* Build with zero objects should not crash */
    bvh_build(&bvh, NULL, 0);
    /* node_count may be 0 or undefined - just verify no crash */
    ASSERT_TRUE(true);

    bvh_destroy(&bvh);
}

TEST(aabb_contained)
{
    /* One AABB fully contained within another */
    AABB outer = { .min = vec3(0,0,0), .max = vec3(10,10,10) };
    AABB inner = { .min = vec3(2,2,2), .max = vec3(8,8,8) };
    ASSERT_TRUE(aabb_overlap(outer, inner));
    ASSERT_TRUE(aabb_overlap(inner, outer));
}

/* ----------------------------------------------------------------------- */
/*  Round 6: shapes, narrowphase, CCD, contact callbacks                    */
/* ----------------------------------------------------------------------- */

TEST(aabb_from_sphere)
{
    RigidBody b = {0};
    b.shape = SHAPE_SPHERE;
    b.position = vec3(1, 2, 3);
    b.radius = 0.5f;
    AABB a = aabb_from_body(&b);
    ASSERT_FLOAT_EQ(a.min.e[0], 0.5f, 1e-4f);
    ASSERT_FLOAT_EQ(a.max.e[1], 2.5f, 1e-4f);
}

TEST(aabb_from_capsule)
{
    RigidBody b = {0};
    b.shape = SHAPE_CAPSULE;
    b.position = vec3(0, 0, 0);
    b.radius = 0.5f;
    b.half_height = 1.0f;
    AABB a = aabb_from_body(&b);
    /* Y extent = half_height + radius = 1.5 */
    ASSERT_FLOAT_EQ(a.min.e[1], -1.5f, 1e-4f);
    ASSERT_FLOAT_EQ(a.max.e[1],  1.5f, 1e-4f);
    ASSERT_FLOAT_EQ(a.max.e[0],  0.5f, 1e-4f);
}

TEST(collide_sphere_sphere_hit)
{
    RigidBody a = {0}, b = {0};
    a.shape = SHAPE_SPHERE; a.position = vec3(0,0,0); a.radius = 1.0f;
    b.shape = SHAPE_SPHERE; b.position = vec3(1.5f,0,0); b.radius = 1.0f;
    Contact c;
    ASSERT_TRUE(physics_collide(&a, &b, &c));
    ASSERT_FLOAT_EQ(c.depth, 0.5f, 1e-4f);
    ASSERT_TRUE(c.normal.e[0] > 0.9f);  /* normal from a -> b points +x */
}

TEST(collide_sphere_sphere_miss)
{
    RigidBody a = {0}, b = {0};
    a.shape = SHAPE_SPHERE; a.position = vec3(0,0,0); a.radius = 1.0f;
    b.shape = SHAPE_SPHERE; b.position = vec3(3.0f,0,0); b.radius = 1.0f;
    Contact c;
    ASSERT_FALSE(physics_collide(&a, &b, &c));
}

TEST(collide_capsule_capsule)
{
    /* Two parallel upright capsules side by side, overlapping. */
    RigidBody a = {0}, b = {0};
    a.shape = SHAPE_CAPSULE; a.position = vec3(0,0,0);  a.radius = 0.5f; a.half_height = 1.0f;
    b.shape = SHAPE_CAPSULE; b.position = vec3(0.6f,0,0); b.radius = 0.5f; b.half_height = 1.0f;
    Contact c;
    ASSERT_TRUE(physics_collide(&a, &b, &c));
    ASSERT_TRUE(c.depth > 0.0f);
    ASSERT_TRUE(c.normal.e[0] > 0.9f);
}

TEST(collide_capsule_on_box_floor)
{
    /* Capsule resting just above a box top: outside-face contact, normal down. */
    RigidBody cap = {0};
    cap.shape = SHAPE_CAPSULE; cap.position = vec3(0, 0.8f, 0); cap.radius = 0.5f; cap.half_height = 0.5f;
    /* segment bottom centre = 0.8 - 0.5 = 0.3; box top at 0 -> dist 0.3 < r */
    RigidBody box = {0};
    box.shape = SHAPE_BOX; box.position = vec3(0, -0.5f, 0); box.half_extent = vec3(5, 0.5f, 5);
    Contact c;
    ASSERT_TRUE(physics_collide(&cap, &box, &c));
    ASSERT_TRUE(c.normal.e[1] < -0.5f);  /* capsule(above) -> box(below) = down */
    ASSERT_FLOAT_EQ(c.depth, 0.2f, 1e-3f);
}

TEST(collide_sphere_box_swapped_normal)
{
    /* Verify normal sign is correct regardless of argument order. */
    RigidBody sph = {0};
    sph.shape = SHAPE_SPHERE; sph.position = vec3(0, 0.3f, 0); sph.radius = 0.5f;
    RigidBody box = {0};
    box.shape = SHAPE_BOX; box.position = vec3(0, -0.5f, 0); box.half_extent = vec3(5, 0.5f, 5);

    Contact c1, c2;
    ASSERT_TRUE(physics_collide(&sph, &box, &c1));  /* sphere -> box: down */
    ASSERT_TRUE(c1.normal.e[1] < -0.5f);
    ASSERT_TRUE(physics_collide(&box, &sph, &c2));  /* box -> sphere: up */
    ASSERT_TRUE(c2.normal.e[1] > 0.5f);
}

static int  g_contact_hits = 0;
static void test_on_contact(const Contact *c, void *user) {
    (void)c; (void)user;
    g_contact_hits++;
}

TEST(contact_callback_fires)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_set_contact_callback(pw, test_on_contact, NULL);
    physics_body_create(pw, vec3(0, 0, 0), vec3(1,1,1), 1.0f, false, 0);
    physics_body_create(pw, vec3(0.5f, 0, 0), vec3(1,1,1), 1.0f, false, 0);
    g_contact_hits = 0;
    physics_step(pw, 1.0f/60.0f);
    ASSERT_TRUE(g_contact_hits > 0);
    physics_world_destroy(pw);
}

TEST(ccd_prevents_tunnel)
{
    PhysicsWorld *pw = physics_world_create(64);
    /* Thin static wall at x=5 (left face x=4.9). */
    physics_body_create(pw, vec3(5, 0, 0), vec3(0.1f, 5, 5), 0.0f, true, 0);
    /* Fast sphere headed straight at it with CCD on. */
    u32 id = physics_body_create_sphere(pw, vec3(0, 0, 0), 0.5f, 1.0f, false, 0);
    physics_body_set_ccd(pw, id, true);
    pw->bodies[id].velocity = vec3(1000, 0, 0);

    physics_step(pw, 0.1f); /* would advance ~98 units without CCD */
    /* CCD must stop the body before passing through the wall. */
    ASSERT_TRUE(pw->bodies[id].position.e[0] < 5.0f);
    physics_world_destroy(pw);
}

TEST(no_ccd_tunnels)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(5, 0, 0), vec3(0.1f, 5, 5), 0.0f, true, 0);
    u32 id = physics_body_create_sphere(pw, vec3(0, 0, 0), 0.5f, 1.0f, false, 0);
    /* CCD disabled (default): single big step tunnels through the thin wall. */
    pw->bodies[id].velocity = vec3(1000, 0, 0);
    physics_step(pw, 0.1f);
    ASSERT_TRUE(pw->bodies[id].position.e[0] > 5.0f);
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(aabb_from_body_basic);
    RUN_TEST(aabb_overlap_true);
    RUN_TEST(aabb_overlap_false);
    RUN_TEST(aabb_overlap_touching);
    RUN_TEST(world_create_destroy);
    RUN_TEST(body_create);
    RUN_TEST(body_static);
    RUN_TEST(gravity_fall);
    RUN_TEST(impulse);
    RUN_TEST(impulse_static_ignored);
    RUN_TEST(collision_detection);
    RUN_TEST(collision_resolves_approach_velocity);
    RUN_TEST(ground_respawn);
    RUN_TEST(raycast_hit);
    RUN_TEST(raycast_miss);
    RUN_TEST(bvh_build_query);
    RUN_TEST(bvh_raycast_test);
    /* Edge cases */
    RUN_TEST(physics_empty_world_raycast);
    RUN_TEST(physics_zero_velocity_body);
    RUN_TEST(bvh_single_object);
    RUN_TEST(physics_body_at_origin_raycast);
    RUN_TEST(physics_zero_length_raycast);
    RUN_TEST(physics_very_large_mass);
    RUN_TEST(bvh_empty_build);
    RUN_TEST(aabb_contained);
    /* Round 6: shapes / narrowphase / CCD / contacts */
    RUN_TEST(aabb_from_sphere);
    RUN_TEST(aabb_from_capsule);
    RUN_TEST(collide_sphere_sphere_hit);
    RUN_TEST(collide_sphere_sphere_miss);
    RUN_TEST(collide_capsule_capsule);
    RUN_TEST(collide_capsule_on_box_floor);
    RUN_TEST(collide_sphere_box_swapped_normal);
    RUN_TEST(contact_callback_fires);
    RUN_TEST(ccd_prevents_tunnel);
    RUN_TEST(no_ccd_tunnels);
TEST_MAIN_END()
