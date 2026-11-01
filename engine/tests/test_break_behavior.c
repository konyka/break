#include "test_framework.h"
#include <ai/break_ai.h>

static void sample_tree(BreakNode *nodes) {
    memset(nodes, 0, sizeof(BreakNode) * 5);
    nodes[0].kind = BREAK_NODE_SELECTOR;
    nodes[0].child_begin = 1;
    nodes[0].child_count = 3;
    nodes[1].kind = BREAK_NODE_LEAF;
    nodes[1].leaf = BREAK_LEAF_ATTACK;
    nodes[2].kind = BREAK_NODE_SEQUENCE;
    nodes[2].child_begin = 4;
    nodes[2].child_count = 1;
    nodes[3].kind = BREAK_NODE_LEAF;
    nodes[3].leaf = BREAK_LEAF_IDLE;
    nodes[4].kind = BREAK_NODE_LEAF;
    nodes[4].leaf = BREAK_LEAF_CHASE;
}

TEST(behavior_idles_chases_and_attacks) {
    BreakNode nodes[5];
    sample_tree(nodes);
    BreakBlackboard board;
    memset(&board, 0, sizeof(board));
    BreakBehaveResult result;
    memset(&result, 0, sizeof(result));
    ASSERT_EQ(break_behavior_tick(nodes, 5, 0, &board, NULL, vec3(0, 0, 0), 1.0f, &result),
              BREAK_BEHAVE_SUCCESS);
    ASSERT_FALSE(result.attack);
    ASSERT_FLOAT_EQ(result.wish.e[0], 0.0f, 1e-6);

    board.seen = true;
    board.last_seen = vec3(6, 0, 0);
    board.target = (Entity){4, 1};
    BreakNavPath path;
    memset(&path, 0, sizeof(path));
    path.count = 2;
    path.points[0] = vec3(0, 0, 0);
    path.points[1] = board.last_seen;
    BreakNavFollower follower;
    break_nav_follow_reset(&follower, &path, 0.25f);
    ASSERT_EQ(break_behavior_tick(nodes, 5, 0, &board, &follower, vec3(0, 0, 0), 1.0f, &result),
              BREAK_BEHAVE_RUNNING);
    ASSERT_FLOAT_EQ(board.last_seen.e[0], 6.0f, 1e-6);
    ASSERT_TRUE(result.wish.e[0] > 0.5f);

    board.last_seen = vec3(1, 0, 0);
    ASSERT_EQ(break_behavior_tick(nodes, 5, 0, &board, &follower, vec3(0, 0, 0), 1.0f, &result),
              BREAK_BEHAVE_SUCCESS);
    ASSERT_TRUE(result.attack);
    ASSERT_FLOAT_EQ(result.wish.e[0], 0.0f, 1e-6);

    board.last_seen = vec3(3, 4, 5);
    board.seen = false;
    board.attack = false;
    ASSERT_EQ(break_behavior_tick(nodes, 5, 9, &board, &follower, vec3(0, 0, 0), 1.0f, &result),
              BREAK_BEHAVE_FAILURE);
    ASSERT_FLOAT_EQ(board.last_seen.e[0], 3.0f, 1e-6);
    ASSERT_FLOAT_EQ(board.last_seen.e[1], 4.0f, 1e-6);
    ASSERT_FLOAT_EQ(board.last_seen.e[2], 5.0f, 1e-6);
    ASSERT_FALSE(board.attack);
}

TEST_MAIN_BEGIN()
    RUN_TEST(behavior_idles_chases_and_attacks);
TEST_MAIN_END()
