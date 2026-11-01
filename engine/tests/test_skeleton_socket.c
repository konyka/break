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

TEST_MAIN_BEGIN()
    RUN_TEST(sockets_follow_joint_pose_and_cap);
TEST_MAIN_END()
