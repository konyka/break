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

TEST_MAIN_BEGIN()
    RUN_TEST(stale_constraint_remove_preserves_reused_slot);
    RUN_TEST(parked_body_cannot_rebind_old_constraint_to_new_occupant);
TEST_MAIN_END()
