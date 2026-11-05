#include "test_framework.h"
#include <physics/physics.h>

TEST(stale_constraint_remove_preserves_reused_slot) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 0, 0), vec3(0, 0, 0), 1, false, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(2, 0, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[a.index].acceleration = vec3(0, 0, 0);
    pw->bodies[b.index].acceleration = vec3(0, 0, 0);
    PhysicsConstraintHandle old_handle = physics_constraint_add_distance(pw, a, b, 2.0f);
    ASSERT_TRUE(physics_constraint_handle_is_valid(old_handle));
    physics_constraint_remove(pw, old_handle);
    PhysicsConstraintHandle fresh_handle = physics_constraint_add_distance(pw, a, b, 2.0f);
    ASSERT_EQ(fresh_handle.index, old_handle.index);
    ASSERT_NEQ(fresh_handle.generation, old_handle.generation);
    physics_constraint_remove(pw, old_handle);
    ASSERT_TRUE(pw->constraints[fresh_handle.index].active);
    ASSERT_EQ(physics_constraint_count(pw), 1u);
    physics_constraint_remove(pw, fresh_handle);
    physics_world_destroy(pw);
}

TEST(parked_body_cannot_rebind_old_constraint_to_new_occupant) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle old_body = physics_body_create(pw, vec3(0, 0, 0), vec3(0, 0, 0), 0, true, 0);
    PhysicsBodyHandle other = physics_body_create(pw, vec3(4, 0, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[other.index].acceleration = vec3(0, 0, 0);
    PhysicsConstraintHandle constraint = physics_constraint_add_distance(pw, old_body, other, 1.0f);
    ASSERT_TRUE(physics_constraint_handle_is_valid(constraint));
    physics_body_park(pw, old_body);
    PhysicsBodyHandle new_body = physics_body_create(pw, vec3(20, 0, 0), vec3(0, 0, 0), 0, true, 0);
    ASSERT_EQ(new_body.index, old_body.index);
    ASSERT_NEQ(new_body.generation, old_body.generation);
    physics_step(pw, 0.016f);
    ASSERT_FALSE(pw->constraints[constraint.index].active);
    ASSERT_EQ(physics_constraint_count(pw), 0u);
    ASSERT_FLOAT_EQ(pw->bodies[other.index].position.e[0], 4.0f, 1e-5f);
    ASSERT_TRUE(physics_body_resolve(pw, old_body) == NULL);
    physics_world_destroy(pw);
}

TEST(revive_rejects_stale_tombstone_handle) {
    PhysicsWorld *pw = physics_world_create(2);
    PhysicsBodyHandle old = physics_body_create(pw, vec3(0, 2, 0), vec3(0.5f, 0.5f, 0.5f), 1, false, 0);
    physics_body_park(pw, old);
    PhysicsBodyHandle current = {old.index, pw->bodies[old.index].generation};
    ASSERT_NEQ(current.generation, old.generation);
    PhysicsBodyHandle rejected = physics_body_revive(pw, old, 1, false, 1);
    ASSERT_FALSE(physics_body_handle_is_valid(rejected));
    ASSERT_TRUE(physics_body_is_parked(&pw->bodies[old.index]));
    PhysicsBodyHandle revived = physics_body_revive(pw, current, 1, false, 1);
    ASSERT_TRUE(physics_body_handle_is_valid(revived));
    ASSERT_NOT_NULL(physics_body_resolve(pw, revived));
    physics_world_destroy(pw);
}

TEST(revive_rejects_live_body_without_changing_identity) {
    PhysicsWorld *pw = physics_world_create(2);
    PhysicsBodyHandle live = physics_body_create(pw, vec3(0, 2, 0), vec3(0.5f, 0.5f, 0.5f), 1, false, 0);
    RigidBody before = pw->bodies[live.index];
    PhysicsBodyHandle rejected = physics_body_revive(pw, live, 2, false, 10);
    ASSERT_FALSE(physics_body_handle_is_valid(rejected));
    ASSERT_EQ(memcmp(&pw->bodies[live.index], &before, sizeof(before)), 0);
    physics_world_destroy(pw);
}

TEST(generation_exhaustion_retires_slots_permanently) {
    PhysicsWorld *pw = physics_world_create(1);
    PhysicsBodyHandle old = physics_body_create(pw, vec3(0, 0, 0), vec3(0.5f, 0.5f, 0.5f), 1, false, 0);
    pw->bodies[old.index].generation = UINT32_MAX;
    physics_body_park(pw, (PhysicsBodyHandle){old.index, UINT32_MAX});
    ASSERT_TRUE(pw->bodies[old.index].retired);
    ASSERT_FALSE(physics_body_handle_is_valid(
        physics_body_create(pw, vec3(1, 0, 0), vec3(0.5f, 0.5f, 0.5f), 1, false, 0)));
    ASSERT_EQ(pw->count, 1u);
    ASSERT_TRUE(physics_body_resolve(pw, old) == NULL);
    physics_world_destroy(pw);

    pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 0, 0), vec3(0, 0, 0), 0, true, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(2, 0, 0), vec3(0, 0, 0), 1, false, 0);
    PhysicsConstraintHandle old_constraint = physics_constraint_add_distance(pw, a, b, 2.0f);
    pw->constraints[old_constraint.index].generation = UINT32_MAX;
    physics_constraint_remove(pw, (PhysicsConstraintHandle){old_constraint.index, UINT32_MAX});
    ASSERT_TRUE(pw->constraints[old_constraint.index].retired);
    PhysicsConstraintHandle fresh = physics_constraint_add_distance(pw, a, b, 2.0f);
    ASSERT_TRUE(physics_constraint_handle_is_valid(fresh));
    ASSERT_NEQ(fresh.index, old_constraint.index);
    physics_constraint_remove(pw, old_constraint);
    ASSERT_TRUE(pw->constraints[fresh.index].active);
    physics_world_destroy(pw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stale_constraint_remove_preserves_reused_slot);
    RUN_TEST(parked_body_cannot_rebind_old_constraint_to_new_occupant);
    RUN_TEST(revive_rejects_stale_tombstone_handle);
    RUN_TEST(revive_rejects_live_body_without_changing_identity);
    RUN_TEST(generation_exhaustion_retires_slots_permanently);
TEST_MAIN_END()
