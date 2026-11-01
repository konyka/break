#include "test_framework.h"
#include <physics/ragdoll.h>
#include <stdlib.h>

static void set_pos(Mat4 *m, f32 x, f32 y, f32 z) {
    memset(m, 0, sizeof(*m));
    m->e[0][0] = m->e[1][1] = m->e[2][2] = m->e[3][3] = 1.0f;
    m->e[3][0] = x;
    m->e[3][1] = y;
    m->e[3][2] = z;
}

TEST(ragdoll_spawns_bodies_and_rolls_back) {
    PhysicsWorld *pw = physics_world_create(16);
    Skeleton *sk = (Skeleton *)calloc(1, sizeof(Skeleton));
    ASSERT_NOT_NULL(sk);
    sk->joint_count = 2;
    set_pos(&sk->current_pose[0], 0, 0, 0);
    set_pos(&sk->current_pose[1], 0, 1, 0);
    Ragdoll rd;
    memset(&rd, 0, sizeof(rd));
    u32 before = pw->count;
    ASSERT_TRUE(ragdoll_activate(&rd, pw, sk));
    ASSERT_EQ(pw->count, before + 2u);
    ASSERT_FALSE(pw->bodies[rd.bones[0].body_id].is_static);
    ASSERT_FALSE(pw->bodies[rd.bones[1].body_id].is_static);
    pw->bodies[rd.bones[1].body_id].position = vec3(0, 1, 0.2f);
    ragdoll_write_pose(&rd, pw, sk);
    ASSERT_FLOAT_EQ(sk->current_pose[1].e[3][2], 0.2f, 1e-5);

    PhysicsWorld *full = physics_world_create(16);
    u32 a = physics_body_create(full, vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    u32 b = physics_body_create(full, vec3(1, 0, 0), vec3(0.1f, 0.1f, 0.1f), 1, false, 0);
    for (u32 i = 0; i < 64; i++) physics_constraint_add_distance(full, a, b, 1.0f);
    u32 count = full->count;
    Ragdoll failed;
    memset(&failed, 0, sizeof(failed));
    ASSERT_FALSE(ragdoll_activate(&failed, full, sk));
    ASSERT_EQ(full->count, count);
    physics_world_destroy(full);
    physics_world_destroy(pw);
    free(sk);
}

TEST_MAIN_BEGIN()
    RUN_TEST(ragdoll_spawns_bodies_and_rolls_back);
TEST_MAIN_END()
