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

static BreakNode leaf(BreakLeafKind kind) {
    BreakNode n;
    memset(&n, 0, sizeof(n));
    n.kind = BREAK_NODE_LEAF;
    n.leaf = kind;
    return n;
}

static BreakNode branch(BreakNodeKind kind, u16 begin, u16 count) {
    BreakNode n;
    memset(&n, 0, sizeof(n));
    n.kind = kind;
    n.child_begin = begin;
    n.child_count = count;
    return n;
}

/* A sequence stops at the first child that does not succeed: with no
 * target, attack fails and the idle after it never runs (the result keeps
 * the failure). */
TEST(sequence_stops_at_the_first_failure) {
    BreakNode nodes[3];
    nodes[0] = branch(BREAK_NODE_SEQUENCE, 1, 2);
    nodes[1] = leaf(BREAK_LEAF_ATTACK);
    nodes[2] = leaf(BREAK_LEAF_IDLE);
    BreakBlackboard board;
    memset(&board, 0, sizeof(board));
    BreakBehaveResult result;
    ASSERT_EQ(break_behavior_tick(nodes, 3, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_FAILURE);
    ASSERT_EQ(result.status, BREAK_BEHAVE_FAILURE);
    ASSERT_FALSE(result.attack);
    nodes[1] = leaf(BREAK_LEAF_IDLE);
    ASSERT_EQ(break_behavior_tick(nodes, 3, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_SUCCESS);
    ASSERT_EQ(result.status, BREAK_BEHAVE_SUCCESS);
}

/* Chase needs a follower and a known position: without either it fails,
 * and a selector then falls through to the next child. */
TEST(chase_without_follower_or_position_fails_over) {
    BreakNode nodes[3];
    nodes[0] = branch(BREAK_NODE_SELECTOR, 1, 2);
    nodes[1] = leaf(BREAK_LEAF_CHASE);
    nodes[2] = leaf(BREAK_LEAF_IDLE);
    BreakBlackboard board;
    memset(&board, 0, sizeof(board));
    board.seen = true;
    board.last_seen = vec3(5, 0, 0);
    BreakBehaveResult result;
    ASSERT_EQ(break_behavior_tick(nodes, 3, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_SUCCESS);
    ASSERT_FLOAT_EQ(result.wish.e[0], 0.0f, 1e-6);
    BreakNavPath path;
    memset(&path, 0, sizeof(path));
    path.count = 2;
    path.points[1] = vec3(5, 0, 0);
    BreakNavFollower follower;
    break_nav_follow_reset(&follower, &path, 0.25f);
    board.seen = false;
    board.last_seen = vec3(0, 0, 0);
    ASSERT_EQ(break_behavior_tick(nodes, 3, 0, &board, &follower, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_SUCCESS);
    ASSERT_FLOAT_EQ(result.wish.e[0], 0.0f, 1e-6);
    /* a remembered position is enough even when not currently seen */
    board.last_seen = vec3(5, 0, 0);
    ASSERT_EQ(break_behavior_tick(nodes, 3, 0, &board, &follower, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_RUNNING);
    /* the wish is one step of speed 1 over dt */
    ASSERT_FLOAT_EQ(result.wish.e[0], 0.1f, 1e-6);
}

/* Malformed trees fail before any leaf runs: children out of range, an
 * unknown kind or leaf, a root out of range, or nesting deeper than 16. */
TEST(malformed_trees_fail_without_running_leaves) {
    BreakBlackboard board;
    memset(&board, 0, sizeof(board));
    board.seen = true;
    board.last_seen = vec3(0.5f, 0, 0);
    BreakBehaveResult result;
    BreakNode nodes[20];
    nodes[0] = branch(BREAK_NODE_SELECTOR, 1, 2);
    nodes[1] = leaf(BREAK_LEAF_ATTACK);
    ASSERT_EQ(break_behavior_tick(nodes, 2, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_FAILURE);
    nodes[2] = leaf((BreakLeafKind)99);
    ASSERT_EQ(break_behavior_tick(nodes, 3, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_FAILURE);
    nodes[2] = leaf(BREAK_LEAF_IDLE);
    nodes[0].kind = (BreakNodeKind)42;
    ASSERT_EQ(break_behavior_tick(nodes, 3, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_FAILURE);
    nodes[0].kind = BREAK_NODE_SELECTOR;
    ASSERT_EQ(break_behavior_tick(nodes, 3, 3, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_FAILURE);
    ASSERT_FALSE(board.attack);
    /* a valid tree with the same leaves attacks */
    ASSERT_EQ(break_behavior_tick(nodes, 3, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_SUCCESS);
    ASSERT_TRUE(result.attack);
    board.attack = false;
    /* a chain of 18 sequences is deeper than the limit */
    for (u16 i = 0; i < 18u; i++) nodes[i] = branch(BREAK_NODE_SEQUENCE, (u16)(i + 1u), 1);
    nodes[18] = leaf(BREAK_LEAF_ATTACK);
    ASSERT_EQ(break_behavior_tick(nodes, 19, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_FAILURE);
    ASSERT_FALSE(board.attack);
    /* a self-referencing node is rejected by the same depth limit */
    nodes[0] = branch(BREAK_NODE_SEQUENCE, 0, 1);
    ASSERT_EQ(break_behavior_tick(nodes, 1, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_FAILURE);
    ASSERT_EQ(break_behavior_tick(NULL, 1, 0, &board, NULL, vec3(0, 0, 0), 0.1f, &result),
              BREAK_BEHAVE_FAILURE);
}

TEST_MAIN_BEGIN()
    RUN_TEST(behavior_idles_chases_and_attacks);
    RUN_TEST(sequence_stops_at_the_first_failure);
    RUN_TEST(chase_without_follower_or_position_fails_over);
    RUN_TEST(malformed_trees_fail_without_running_leaves);
TEST_MAIN_END()
