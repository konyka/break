#include "test_framework.h"
#include <physics/ragdoll.h>
#include <stdlib.h>

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc;
    return (RHIBuffer){ .index = 1, .generation = 1 };
}
void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset,
                              const void *data, usize size) {
    (void)dev; (void)buf; (void)offset; (void)data; (void)size;
}
u32 rhi_frame_index(RHIDevice *dev) { (void)dev; return 0u; }

static const f32 PI = 3.14159265358979323846f;

static Mat4 trs(Vec3 p, Quat q, Vec3 s) {
    Mat4 m = mat4_from_quat(q);
    for (int row = 0; row < 3; row++) {
        m.e[0][row] *= s.e[0];
        m.e[1][row] *= s.e[1];
        m.e[2][row] *= s.e[2];
    }
    m.e[3][0] = p.e[0];
    m.e[3][1] = p.e[1];
    m.e[3][2] = p.e[2];
    return m;
}

static void skeleton_fixture(Skeleton *sk, u32 joints) {
    memset(sk, 0, sizeof(*sk));
    sk->joint_count = joints;
    for (u32 i = 0; i < joints; i++) {
        sk->joint_parents[i] = UINT32_MAX;
        sk->inverse_bind[i] = mat4_identity();
        sk->current_pose[i] = mat4_identity();
    }
}

static void set_joint_world(Skeleton *sk, u32 joint, Vec3 p, Quat q) {
    sk->current_pose[joint] = trs(p, q, vec3(1, 1, 1));
}

static void set_body_pose(PhysicsWorld *pw, PhysicsBodyHandle id, Vec3 p, Quat q) {
    RigidBody *b = &pw->bodies[id.index];
    b->position = p;
    b->acceleration = vec3(0, 0, 0);
    PhysicsPose pose;
    pose.orientation = q;
    pose.angular_velocity = vec3(0, 0, 0);
    pose.inertia_diag = vec3(1, 1, 1);
    physics_body_set_pose(pw, id, &pose);
}

static bool quat_near(Quat a, Quat b) {
    f32 dot = 0.0f;
    for (int i = 0; i < 4; i++) dot += a.e[i] * b.e[i];
    return fabsf(dot) > 0.9999f;
}

static bool mat4_near(Mat4 a, Mat4 b, f32 eps) {
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            if (fabsf(a.e[c][r] - b.e[c][r]) > eps) return false;
        }
    }
    return true;
}

TEST(ragdoll_world_bodies_convert_to_local_trs) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle root_body = physics_body_create(pw, vec3(0, 0, 0), vec3(0, 0, 0), 1, false, 0);
    PhysicsBodyHandle child_body = physics_body_create(pw, vec3(0, 0, 0), vec3(0, 0, 0), 1, false, 0);
    Quat root_q = quat_from_axis_angle(vec3(0, 0, 1), PI / 2.0f);
    Quat child_local_q = quat_from_axis_angle(vec3(0, 1, 0), PI / 2.0f);
    Quat child_world_q = quat_normalize(quat_mul(root_q, child_local_q));
    Vec3 root_p = vec3(5, 6, 7);
    Vec3 child_p = vec3(3, 6, 7);
    set_body_pose(pw, root_body, root_p, root_q);
    set_body_pose(pw, child_body, child_p, child_world_q);

    Skeleton sk;
    skeleton_fixture(&sk, 2);
    sk.joint_parents[1] = 0;
    sk.inverse_bind[1] = mat4_translation(0, -2, 0);
    Ragdoll rd;
    memset(&rd, 0, sizeof(rd));
    rd.active = true;
    rd.bone_count = 2;
    for (u32 i = 0; i < 2; i++) {
        rd.bones[i].joint = i;
        rd.bones[i].body_id = i == 0 ? root_body : child_body;
        rd.bones[i].parent_bone = i == 0 ? UINT32_MAX : 0;
        rd.bones[i].body_to_joint_rot = QUAT_IDENTITY;
        rd.bones[i].local_scale = vec3(1, 1, 1);
    }
    rd.bones[1].local_scale = vec3(2, 2, 2);

    Vec3 local_p[2];
    Quat local_q[2];
    Vec3 local_s[2];
    ASSERT_TRUE(ragdoll_write_local_trs(&rd, pw, &sk, local_p, local_q, local_s));
    ASSERT_FLOAT_EQ(local_p[0].e[0], 5.0f, 1e-5f);
    ASSERT_FLOAT_EQ(local_p[0].e[1], 6.0f, 1e-5f);
    ASSERT_TRUE(quat_near(local_q[0], root_q));
    ASSERT_FLOAT_EQ(local_p[1].e[0], 0.0f, 1e-5f);
    ASSERT_FLOAT_EQ(local_p[1].e[1], 2.0f, 1e-5f);
    ASSERT_FLOAT_EQ(local_p[1].e[2], 0.0f, 1e-5f);
    ASSERT_TRUE(quat_near(local_q[1], child_local_q));
    ASSERT_FLOAT_EQ(local_s[1].e[0], 2.0f, 1e-6f);

    ragdoll_write_pose(&rd, pw, &sk);
    Mat4 expected_world = trs(child_p, child_world_q, vec3(2, 2, 2));
    Mat4 expected_skin = mat4_mul(expected_world, sk.inverse_bind[1]);
    ASSERT_TRUE(mat4_near(sk.current_pose[1], expected_skin, 2e-4f));
    physics_world_destroy(pw);
}

TEST(ragdoll_local_translation_removes_parent_scale) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle root_body = physics_body_create(pw, vec3(0, 0, 0), vec3(0, 0, 0), 1, false, 0);
    PhysicsBodyHandle child_body = physics_body_create(pw, vec3(0, 0, 0), vec3(0, 0, 0), 1, false, 0);
    Quat root_q = quat_from_axis_angle(vec3(0, 0, 1), PI / 2.0f);
    set_body_pose(pw, root_body, vec3(1, 2, 3), root_q);
    set_body_pose(pw, child_body, vec3(-1, 2, 3), root_q);
    Skeleton sk;
    skeleton_fixture(&sk, 2);
    sk.joint_parents[1] = 0;
    Ragdoll rd;
    memset(&rd, 0, sizeof(rd));
    rd.active = true;
    rd.bone_count = 2;
    for (u32 i = 0; i < 2; i++) {
        rd.bones[i].joint = i;
        rd.bones[i].body_id = i == 0 ? root_body : child_body;
        rd.bones[i].parent_bone = i == 0 ? UINT32_MAX : 0;
        rd.bones[i].body_to_joint_rot = QUAT_IDENTITY;
        rd.bones[i].local_scale = vec3(1, 1, 1);
    }
    rd.bones[0].local_scale = vec3(2, 2, 2);
    Vec3 local_p[2];
    Quat local_q[2];
    Vec3 local_s[2];
    ASSERT_TRUE(ragdoll_write_local_trs(&rd, pw, &sk, local_p, local_q, local_s));
    ASSERT_FLOAT_EQ(local_p[1].e[0], 0.0f, 1e-5f);
    ASSERT_FLOAT_EQ(local_p[1].e[1], 1.0f, 1e-5f);
    ASSERT_FLOAT_EQ(local_p[1].e[2], 0.0f, 1e-5f);
    physics_world_destroy(pw);
}

TEST(ragdoll_activation_preserves_bind_pose_and_recycles) {
    Skeleton sk;
    skeleton_fixture(&sk, 2);
    sk.joint_parents[1] = 0;
    Quat root_q = quat_from_axis_angle(vec3(0, 0, 1), PI / 2.0f);
    Quat child_q = quat_from_axis_angle(vec3(1, 0, 0), PI / 6.0f);
    set_joint_world(&sk, 0, vec3(2, 3, 4), root_q);
    set_joint_world(&sk, 1, vec3(1, 3, 4), quat_normalize(quat_mul(root_q, child_q)));

    PhysicsWorld *pw = physics_world_create(4);
    Ragdoll rd;
    memset(&rd, 0, sizeof(rd));
    ASSERT_TRUE(ragdoll_activate(&rd, pw, &sk, NULL));
    ASSERT_EQ(rd.bone_count, 2u);
    ASSERT_EQ(physics_constraint_count(pw), 1u);
    PhysicsBodyHandle root_body = rd.bones[0].body_id;
    PhysicsBodyHandle child_body = rd.bones[1].body_id;
    Vec3 local_p[2];
    Quat local_q[2];
    Vec3 local_s[2];
    ASSERT_TRUE(ragdoll_write_local_trs(&rd, pw, &sk, local_p, local_q, local_s));
    ASSERT_FLOAT_EQ(local_p[0].e[0], 2.0f, 2e-4f);
    ASSERT_FLOAT_EQ(local_p[0].e[1], 3.0f, 2e-4f);
    ASSERT_TRUE(quat_near(local_q[0], root_q));
    ASSERT_FLOAT_EQ(local_p[1].e[0], 0.0f, 2e-4f);
    ASSERT_FLOAT_EQ(local_p[1].e[1], 1.0f, 2e-4f);
    ASSERT_TRUE(quat_near(local_q[1], child_q));

    ragdoll_deactivate(&rd, pw);
    ASSERT_FALSE(rd.active);
    ASSERT_EQ(rd.bone_count, 0u);
    ASSERT_EQ(physics_constraint_count(pw), 0u);
    ASSERT_TRUE(physics_body_is_parked(&pw->bodies[root_body.index]));
    ASSERT_TRUE(physics_body_is_parked(&pw->bodies[child_body.index]));
    PhysicsBodyHandle reused_root = physics_body_create(pw, vec3(0, 8, 0), vec3(1, 1, 1), 1, false, 0);
    PhysicsBodyHandle reused_child = physics_body_create(pw, vec3(1, 8, 0), vec3(1, 1, 1), 1, false, 0);
    ASSERT_EQ(reused_root.index, root_body.index);
    ASSERT_EQ(reused_child.index, child_body.index);
    ASSERT_NEQ(reused_root.generation, root_body.generation);
    ASSERT_NEQ(reused_child.generation, child_body.generation);
    ragdoll_deactivate(&rd, pw);
    physics_world_destroy(pw);
}

TEST(ragdoll_uses_real_parent_indices) {
    Skeleton sk;
    skeleton_fixture(&sk, 3);
    sk.joint_parents[1] = UINT32_MAX;
    sk.joint_parents[2] = 1;
    set_joint_world(&sk, 0, vec3(0, 0, 0), QUAT_IDENTITY);
    set_joint_world(&sk, 1, vec3(5, 0, 0), QUAT_IDENTITY);
    set_joint_world(&sk, 2, vec3(5, 2, 0), QUAT_IDENTITY);
    PhysicsWorld *pw = physics_world_create(8);
    Ragdoll rd;
    memset(&rd, 0, sizeof(rd));
    ASSERT_TRUE(ragdoll_activate(&rd, pw, &sk, NULL));
    ASSERT_EQ(rd.bones[1].parent_bone, UINT32_MAX);
    ASSERT_EQ(rd.bones[2].parent_bone, 1u);
    ASSERT_EQ(physics_constraint_count(pw), 1u);
    ASSERT_TRUE(physics_body_handle_equal(pw->constraints[0].body_a, rd.bones[1].body_id));
    ASSERT_TRUE(physics_body_handle_equal(pw->constraints[0].body_b, rd.bones[2].body_id));
    ragdoll_deactivate(&rd, pw);
    ASSERT_EQ(physics_constraint_count(pw), 0u);
    physics_world_destroy(pw);
}

TEST(ragdoll_suspends_and_restores_ik) {
    Skeleton sk;
    skeleton_fixture(&sk, 3);
    sk.joint_parents[1] = 0;
    sk.joint_parents[2] = 1;
    Mat4 worlds[3];
    Vec3 positions[3] = {0};
    Quat rotations[3];
    for (u32 i = 0; i < 3; i++) {
        Vec3 p = vec3(0, (f32)i, 0);
        set_joint_world(&sk, i, p, QUAT_IDENTITY);
        worlds[i] = trs(p, QUAT_IDENTITY, vec3(1, 1, 1));
        rotations[i] = QUAT_IDENTITY;
    }
    IKSystem ik;
    anim_ik_init(&ik);
    anim_ik_set_target(&ik, 0, 0, 1, 2, vec3(1, 1.5f, 0), vec3(1, 0, 0));
    anim_ik_set_weight(&ik, 0, 1.0f);
    PhysicsWorld *pw = physics_world_create(8);
    Ragdoll rd;
    memset(&rd, 0, sizeof(rd));
    ASSERT_TRUE(ragdoll_activate(&rd, pw, &sk, &ik));
    Quat suspended[3];
    memcpy(suspended, rotations, sizeof(rotations));
    anim_ik_solve(&ik, positions, rotations, worlds, 3);
    ASSERT_EQ(memcmp(suspended, rotations, sizeof(rotations)), 0);
    ragdoll_deactivate(&rd, pw);
    anim_ik_solve(&ik, positions, rotations, worlds, 3);
    ASSERT_FALSE(quat_near(rotations[0], QUAT_IDENTITY) && quat_near(rotations[1], QUAT_IDENTITY));
    physics_world_destroy(pw);
}

TEST(ragdoll_failures_preserve_world_and_destination) {
    Skeleton sk;
    skeleton_fixture(&sk, 3);
    sk.joint_parents[1] = 0;
    sk.joint_parents[2] = 1;
    for (u32 i = 0; i < 3; i++) set_joint_world(&sk, i, vec3(0, (f32)i, 0), QUAT_IDENTITY);

    PhysicsWorld *pw = physics_world_create(8);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(10, 0, 0), vec3(0, 0, 0), 1, false, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(12, 0, 0), vec3(0, 0, 0), 1, false, 0);
    for (u32 i = 0; i < 63; i++) ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_distance(pw, a, b, 2)));
    DistanceConstraint constraints_before[PHYSICS_MAX_CONSTRAINTS];
    RigidBody bodies_before[8];
    memcpy(constraints_before, pw->constraints, sizeof(constraints_before));
    memcpy(bodies_before, pw->bodies, sizeof(bodies_before));
    Ragdoll rd;
    memset(&rd, 0x5a, sizeof(rd));
    rd.active = false;
    rd.bone_count = 77;
    Ragdoll rd_before = rd;
    IKSystem ik;
    anim_ik_init(&ik);
    ASSERT_FALSE(ragdoll_activate(&rd, pw, &sk, &ik));
    ASSERT_EQ(memcmp(&rd, &rd_before, sizeof(rd)), 0);
    ASSERT_EQ(memcmp(constraints_before, pw->constraints, sizeof(constraints_before)), 0);
    ASSERT_EQ(memcmp(bodies_before, pw->bodies, sizeof(bodies_before)), 0);
    ASSERT_EQ(pw->count, 2u);
    ASSERT_EQ(physics_constraint_count(pw), 63u);
    ASSERT_FALSE(ik.physics_suspended);
    physics_world_destroy(pw);

    pw = physics_world_create(2);
    physics_body_create(pw, vec3(0, 0, 0), vec3(1, 1, 1), 0, true, 0);
    physics_body_create(pw, vec3(2, 0, 0), vec3(1, 1, 1), 1, false, 0);
    RigidBody full_before[2];
    memcpy(full_before, pw->bodies, sizeof(full_before));
    rd = rd_before;
    ASSERT_FALSE(ragdoll_activate(&rd, pw, &sk, NULL));
    ASSERT_EQ(memcmp(&rd, &rd_before, sizeof(rd)), 0);
    ASSERT_EQ(memcmp(full_before, pw->bodies, sizeof(full_before)), 0);
    ASSERT_EQ(physics_constraint_count(pw), 0u);
    physics_world_destroy(pw);

    sk.joint_parents[1] = 1;
    pw = physics_world_create(8);
    rd = rd_before;
    ASSERT_FALSE(ragdoll_activate(&rd, pw, &sk, NULL));
    ASSERT_EQ(memcmp(&rd, &rd_before, sizeof(rd)), 0);
    ASSERT_EQ(pw->count, 0u);
    ASSERT_EQ(physics_constraint_count(pw), 0u);
    physics_world_destroy(pw);
}

TEST(ragdoll_stale_deactivate_preserves_reused_resources) {
    Skeleton sk;
    skeleton_fixture(&sk, 2);
    sk.joint_parents[1] = 0;
    set_joint_world(&sk, 0, vec3(0, 0, 0), QUAT_IDENTITY);
    set_joint_world(&sk, 1, vec3(0, 1, 0), QUAT_IDENTITY);
    PhysicsWorld *pw = physics_world_create(6);
    Ragdoll rd;
    memset(&rd, 0, sizeof(rd));
    ASSERT_TRUE(ragdoll_activate(&rd, pw, &sk, NULL));
    Ragdoll stale = rd;
    ragdoll_deactivate(&rd, pw);
    PhysicsBodyHandle new_a = physics_body_create(pw, vec3(10, 0, 0), vec3(0, 0, 0), 1, false, 0);
    PhysicsBodyHandle new_b = physics_body_create(pw, vec3(12, 0, 0), vec3(0, 0, 0), 1, false, 0);
    PhysicsConstraintHandle new_constraint = physics_constraint_add_distance(pw, new_a, new_b, 2.0f);
    ASSERT_TRUE(physics_constraint_handle_is_valid(new_constraint));
    ragdoll_deactivate(&stale, pw);
    ASSERT_FALSE(physics_body_is_parked(&pw->bodies[new_a.index]));
    ASSERT_FALSE(physics_body_is_parked(&pw->bodies[new_b.index]));
    ASSERT_TRUE(pw->constraints[new_constraint.index].active);
    ASSERT_EQ(physics_constraint_count(pw), 1u);
    physics_world_destroy(pw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(ragdoll_world_bodies_convert_to_local_trs);
    RUN_TEST(ragdoll_local_translation_removes_parent_scale);
    RUN_TEST(ragdoll_activation_preserves_bind_pose_and_recycles);
    RUN_TEST(ragdoll_uses_real_parent_indices);
    RUN_TEST(ragdoll_suspends_and_restores_ik);
    RUN_TEST(ragdoll_failures_preserve_world_and_destination);
    RUN_TEST(ragdoll_stale_deactivate_preserves_reused_resources);
TEST_MAIN_END()
