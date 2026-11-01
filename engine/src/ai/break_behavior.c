#include <ai/break_ai.h>
#include <math.h>

static f32 dist3(Vec3 a, Vec3 b) {
    f32 dx = a.e[0] - b.e[0];
    f32 dy = a.e[1] - b.e[1];
    f32 dz = a.e[2] - b.e[2];
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

static bool last_seen_set(Vec3 v) {
    return v.e[0] != 0.0f || v.e[1] != 0.0f || v.e[2] != 0.0f;
}

static bool tree_ok(const BreakNode *nodes, u32 node_count, u32 index, u32 depth) {
    if (depth > 16u || index >= node_count) {
        return false;
    }
    const BreakNode *node = &nodes[index];
    if (node->kind == BREAK_NODE_LEAF) {
        return node->leaf == BREAK_LEAF_IDLE || node->leaf == BREAK_LEAF_CHASE ||
               node->leaf == BREAK_LEAF_ATTACK;
    }
    if (node->kind != BREAK_NODE_SELECTOR && node->kind != BREAK_NODE_SEQUENCE) {
        return false;
    }
    if ((u32)node->child_begin + node->child_count > node_count) {
        return false;
    }
    for (u16 i = 0; i < node->child_count; i++) {
        if (!tree_ok(nodes, node_count, (u32)node->child_begin + i, depth + 1u)) {
            return false;
        }
    }
    return true;
}

static BreakBehaveStatus tick_node(const BreakNode *nodes, u32 index,
                                   BreakBlackboard *board, BreakNavFollower *follower,
                                   Vec3 self_position, f32 dt, BreakBehaveResult *out) {
    const BreakNode *node = &nodes[index];
    if (node->kind == BREAK_NODE_SELECTOR) {
        for (u16 i = 0; i < node->child_count; i++) {
            BreakBehaveStatus status = tick_node(nodes, (u32)node->child_begin + i, board, follower,
                                                 self_position, dt, out);
            if (status != BREAK_BEHAVE_FAILURE) {
                return status;
            }
        }
        return BREAK_BEHAVE_FAILURE;
    }
    if (node->kind == BREAK_NODE_SEQUENCE) {
        BreakBehaveStatus status = BREAK_BEHAVE_SUCCESS;
        for (u16 i = 0; i < node->child_count; i++) {
            status = tick_node(nodes, (u32)node->child_begin + i, board, follower, self_position, dt, out);
            if (status != BREAK_BEHAVE_SUCCESS) {
                return status;
            }
        }
        return status;
    }
    out->attack = false;
    out->wish = vec3(0, 0, 0);
    if (node->leaf == BREAK_LEAF_IDLE) {
        return BREAK_BEHAVE_SUCCESS;
    }
    if (node->leaf == BREAK_LEAF_ATTACK) {
        if (board->seen && dist3(self_position, board->last_seen) < 1.5f) {
            out->attack = true;
            board->attack = true;
            return BREAK_BEHAVE_SUCCESS;
        }
        return BREAK_BEHAVE_FAILURE;
    }
    if (!board->seen && !last_seen_set(board->last_seen)) {
        return BREAK_BEHAVE_FAILURE;
    }
    if (!follower) {
        return BREAK_BEHAVE_FAILURE;
    }
    out->wish = break_nav_follow_wish(follower, self_position, 1.0f, dt);
    if (break_nav_follow_arrived(follower)) {
        return BREAK_BEHAVE_SUCCESS;
    }
    return BREAK_BEHAVE_RUNNING;
}

BreakBehaveStatus break_behavior_tick(const BreakNode *nodes, u32 node_count, u32 root,
                                      BreakBlackboard *board, BreakNavFollower *follower,
                                      Vec3 self_position, f32 dt, BreakBehaveResult *out) {
    if (!nodes || !board || !out || node_count == 0 || root >= node_count || !tree_ok(nodes, node_count, root, 0)) {
        return BREAK_BEHAVE_FAILURE;
    }
    out->status = BREAK_BEHAVE_FAILURE;
    out->wish = vec3(0, 0, 0);
    out->attack = false;
    BreakBehaveStatus status = tick_node(nodes, root, board, follower, self_position, dt, out);
    out->status = status;
    return status;
}
