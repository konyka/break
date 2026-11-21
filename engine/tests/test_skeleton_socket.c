#include "test_framework.h"
#include <animation/skeleton.h>
#include <stdlib.h>

static void set_identity(Mat4 *m) {
    memset(m, 0, sizeof(*m));
    m->e[0][0] = 1.0f;
    m->e[1][1] = 1.0f;
    m->e[2][2] = 1.0f;
    m->e[3][3] = 1.0f;
}

TEST(sockets_follow_joint_pose_and_cap) {
    Skeleton *sk = (Skeleton *)calloc(1, sizeof(Skeleton));
    ASSERT_NOT_NULL(sk);
    sk->joint_count = 2;
    set_identity(&sk->current_pose[0]);
    set_identity(&sk->current_pose[1]);
    sk->current_pose[1].e[3][0] = 5.0f;
    ASSERT_TRUE(skeleton_socket_set(sk, "prop", 0, vec3(0, 1, 0)));
    Vec3 world = vec3(9, 9, 9);
    ASSERT_TRUE(skeleton_socket_get(sk, "prop", &world));
    ASSERT_FLOAT_EQ(world.e[0], 0.0f, 1e-5);
    ASSERT_FLOAT_EQ(world.e[1], 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(world.e[2], 0.0f, 1e-5);
    ASSERT_TRUE(skeleton_socket_set(sk, "prop", 1, vec3(0, 1, 0)));
    ASSERT_TRUE(skeleton_socket_get(sk, "prop", &world));
    ASSERT_FLOAT_EQ(world.e[0], 5.0f, 1e-5);
    ASSERT_FLOAT_EQ(world.e[1], 1.0f, 1e-5);
    ASSERT_EQ(sk->socket_count, 1u);

    for (u32 i = 0; i < SKELETON_MAX_SOCKETS - 1u; i++) {
        char name[16];
        snprintf(name, sizeof(name), "s%u", i);
        ASSERT_TRUE(skeleton_socket_set(sk, name, 0, vec3(0, 0, 0)));
    }
    ASSERT_EQ(sk->socket_count, SKELETON_MAX_SOCKETS);
    ASSERT_FALSE(skeleton_socket_set(sk, "overflow", 0, vec3(0, 0, 0)));
    ASSERT_TRUE(skeleton_socket_get(sk, "prop", &world));
    ASSERT_FLOAT_EQ(world.e[0], 5.0f, 1e-5);
    Vec3 untouched = vec3(3, 3, 3);
    ASSERT_FALSE(skeleton_socket_get(sk, "missing", &untouched));
    ASSERT_FLOAT_EQ(untouched.e[0], 3.0f, 1e-5);
    free(sk);
}

static Skeleton *two_joints(void) {
    Skeleton *sk = (Skeleton *)calloc(1, sizeof(Skeleton));
    if (!sk) return NULL;
    sk->joint_count = 2;
    set_identity(&sk->current_pose[0]);
    set_identity(&sk->current_pose[1]);
    return sk;
}

/* The socket offset is transformed by the full joint matrix, rotation
 * included: a 90 degree turn about Z maps local +X to world +Y. */
TEST(socket_offset_follows_joint_rotation) {
    Skeleton *sk = two_joints();
    ASSERT_NOT_NULL(sk);
    Mat4 *m = &sk->current_pose[1];
    m->e[0][0] = 0.0f;
    m->e[0][1] = 1.0f;
    m->e[1][0] = -1.0f;
    m->e[1][1] = 0.0f;
    m->e[3][2] = 2.0f;
    ASSERT_TRUE(skeleton_socket_set(sk, "hand", 1, vec3(3, 0, 0)));
    Vec3 world;
    ASSERT_TRUE(skeleton_socket_get(sk, "hand", &world));
    ASSERT_FLOAT_EQ(world.e[0], 0.0f, 1e-5);
    ASSERT_FLOAT_EQ(world.e[1], 3.0f, 1e-5);
    ASSERT_FLOAT_EQ(world.e[2], 2.0f, 1e-5);
    /* the pose is read at query time, so moving the joint moves the socket */
    m->e[3][0] = 1.0f;
    ASSERT_TRUE(skeleton_socket_get(sk, "hand", &world));
    ASSERT_FLOAT_EQ(world.e[0], 1.0f, 1e-5);
    free(sk);
}

/* Invalid joints, names and arguments are refused and change nothing. */
TEST(socket_rejects_bad_joints_and_names) {
    Skeleton *sk = two_joints();
    ASSERT_NOT_NULL(sk);
    ASSERT_FALSE(skeleton_socket_set(sk, "far", 2, vec3(0, 0, 0)));
    ASSERT_FALSE(skeleton_socket_set(sk, "", 0, vec3(0, 0, 0)));
    ASSERT_FALSE(skeleton_socket_set(sk, NULL, 0, vec3(0, 0, 0)));
    ASSERT_FALSE(skeleton_socket_set(NULL, "x", 0, vec3(0, 0, 0)));
    char long_name[40];
    memset(long_name, 'a', sizeof(long_name) - 1u);
    long_name[sizeof(long_name) - 1u] = '\0';
    ASSERT_FALSE(skeleton_socket_set(sk, long_name, 0, vec3(0, 0, 0)));
    long_name[31] = '\0';
    ASSERT_TRUE(skeleton_socket_set(sk, long_name, 0, vec3(0, 0, 0)));
    ASSERT_EQ(sk->socket_count, 1u);
    Vec3 world = vec3(4, 4, 4);
    ASSERT_FALSE(skeleton_socket_get(sk, NULL, &world));
    ASSERT_FALSE(skeleton_socket_get(sk, long_name, NULL));
    ASSERT_FALSE(skeleton_socket_get(NULL, long_name, &world));
    ASSERT_FLOAT_EQ(world.e[0], 4.0f, 1e-6);
    ASSERT_TRUE(skeleton_socket_get(sk, long_name, &world));
    free(sk);
}

/* Updating an existing socket keeps the count and slot even when full. */
TEST(socket_update_in_place_when_full) {
    Skeleton *sk = two_joints();
    ASSERT_NOT_NULL(sk);
    for (u32 i = 0; i < SKELETON_MAX_SOCKETS; i++) {
        char name[16];
        snprintf(name, sizeof(name), "s%u", i);
        ASSERT_TRUE(skeleton_socket_set(sk, name, 0, vec3(0, 0, 0)));
    }
    ASSERT_TRUE(skeleton_socket_set(sk, "s0", 1, vec3(0, 7, 0)));
    ASSERT_EQ(sk->socket_count, SKELETON_MAX_SOCKETS);
    ASSERT_EQ(sk->sockets[0].joint, 1u);
    Vec3 world;
    ASSERT_TRUE(skeleton_socket_get(sk, "s0", &world));
    ASSERT_FLOAT_EQ(world.e[1], 7.0f, 1e-5);
    free(sk);
}

TEST_MAIN_BEGIN()
    RUN_TEST(sockets_follow_joint_pose_and_cap);
    RUN_TEST(socket_offset_follows_joint_rotation);
    RUN_TEST(socket_rejects_bad_joints_and_names);
    RUN_TEST(socket_update_in_place_when_full);
TEST_MAIN_END()
