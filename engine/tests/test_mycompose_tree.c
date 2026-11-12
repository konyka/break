#include "test_framework.h"

#include <myui/mycompose/my_compose.h>
#include <myui/mycompose/my_compose_internal.h>
#include <myui/mycompose/my_compose_tree.h>

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static MyComposeNodeHandle zero_handle(void) {
    MyComposeNodeHandle handle = {0u, 0u};
    return handle;
}

static bool handle_equal(MyComposeNodeHandle a, MyComposeNodeHandle b) {
    return a.index == b.index && a.generation == b.generation;
}

static MyComposeStatus add_node(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle parent, const char *key, const char *type,
    MyComposeNodeHandle *out) {
    MyComposeNodeDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.parent = parent;
    desc.key = key;
    desc.type = type;
    return my_compose_tree_builder_node(builder, &desc, out);
}

static MyComposeStatus begin_root(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle *root) {
    MyComposeStatus status = my_compose_tree_builder_begin(builder);
    if (status != MY_COMPOSE_OK) return status;
    return add_node(builder, zero_handle(), NULL, "@root", root);
}

static MyComposeStatus finish(MyComposeTreeBuilder *builder) {
    MyComposeStatus status = my_compose_tree_builder_end(builder);
    if (status != MY_COMPOSE_OK) return status;
    return my_compose_tree_builder_finalize(builder);
}

static MyComposeValue int_value(int32_t value) {
    MyComposeValue result;
    memset(&result, 0, sizeof(result));
    result.type = MY_COMPOSE_VALUE_INT32;
    result.as.int32_value = value;
    return result;
}

static MyComposeIntent intent_value(uint32_t type, const uint8_t *payload,
    uint32_t payload_size) {
    MyComposeIntent intent;
    memset(&intent, 0, sizeof(intent));
    intent.type = type;
    intent.payload = payload;
    intent.payload_size = payload_size;
    intent.result = MY_COMPOSE_OK;
    return intent;
}

static bool apply_diff_in_order(MyComposeNodeHandle *nodes, uint32_t *count,
    const MyComposeDiff *diff) {
    for (uint32_t i = 0u; i < diff->count; ++i) {
        const MyComposeDiffOp *op = &diff->ops[i];
        if (op->type == MY_COMPOSE_DIFF_UPDATE) continue;
        if (op->type == MY_COMPOSE_DIFF_CREATE) {
            if (*count >= MY_COMPOSE_MAX_NODES || op->to_index > *count) {
                return false;
            }
            for (uint32_t j = *count; j > op->to_index; --j) {
                nodes[j] = nodes[j - 1u];
            }
            nodes[op->to_index] = op->node;
            (*count)++;
        } else if (op->type == MY_COMPOSE_DIFF_DELETE) {
            if (op->from_index >= *count ||
                !handle_equal(nodes[op->from_index], op->node)) {
                return false;
            }
            for (uint32_t j = op->from_index + 1u; j < *count; ++j) {
                nodes[j - 1u] = nodes[j];
            }
            (*count)--;
        } else if (op->type == MY_COMPOSE_DIFF_MOVE) {
            if (op->from_index >= *count || op->to_index >= *count ||
                !handle_equal(nodes[op->from_index], op->node)) {
                return false;
            }
            MyComposeNodeHandle node = nodes[op->from_index];
            if (op->from_index < op->to_index) {
                for (uint32_t j = op->from_index; j < op->to_index; ++j) {
                    nodes[j] = nodes[j + 1u];
                }
            } else {
                for (uint32_t j = op->from_index; j > op->to_index; --j) {
                    nodes[j] = nodes[j - 1u];
                }
            }
            nodes[op->to_index] = node;
        }
    }
    return true;
}

TEST(lifecycle_insert_noop_and_delete) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    ASSERT_NOT_NULL(my_compose_tree_builder_diff(builder));
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), 0u);
    ASSERT_EQ(my_compose_tree_builder_next_node_count(builder), 0u);

    MyComposeNodeHandle root;
    MyComposeNodeHandle column;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 2u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, root));
    ASSERT_EQ(diff->ops[1].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[1].node, column));
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), 2u);

    MyComposeNodeHandle next_root;
    MyComposeNodeHandle next_column;
    ASSERT_EQ(begin_root(builder, &next_root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, next_root, "column", "@column", &next_column),
        MY_COMPOSE_OK);
    ASSERT_TRUE(handle_equal(next_root, root));
    ASSERT_TRUE(handle_equal(next_column, column));
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);

    MyComposeNodeHandle item;
    ASSERT_EQ(begin_root(builder, &next_root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, next_root, "column", "@column", &next_column),
        MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, next_column, "a", "button", &item), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 1u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, item));

    ASSERT_EQ(begin_root(builder, &next_root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, next_root, "column", "@column", &next_column),
        MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 1u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, item));
    MyComposeNodeDesc actual;
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, item, &actual),
        MY_COMPOSE_STALE);

    my_compose_tree_builder_destroy(builder);
    my_compose_tree_builder_destroy(NULL);
}

TEST(keyed_reorder_only_moves_and_preserves_handles) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle column;
    MyComposeNodeHandle a;
    MyComposeNodeHandle b;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "button", &a), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "b", "button", &b), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeNodeHandle b_next;
    MyComposeNodeHandle a_next;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "b", "button", &b_next), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "button", &a_next), MY_COMPOSE_OK);
    ASSERT_TRUE(handle_equal(a, a_next));
    ASSERT_TRUE(handle_equal(b, b_next));
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 1u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_MOVE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, b));
    ASSERT_EQ(diff->ops[0].from_index, 1u);
    ASSERT_EQ(diff->ops[0].to_index, 0u);

    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "b", "button", &b_next), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "button", &a_next), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
    my_compose_tree_builder_destroy(builder);
}

TEST(mixed_keyed_and_unkeyed_nodes_keep_their_identity_rules) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle column;
    MyComposeNodeHandle a;
    MyComposeNodeHandle unkeyed;
    MyComposeNodeHandle b;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "button", &a), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, NULL, "label", &unkeyed), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "b", "button", &b), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeNodeHandle next[3];
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "b", "button", &next[0]), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, NULL, "label", &next[1]), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "button", &next[2]), MY_COMPOSE_OK);
    ASSERT_TRUE(handle_equal(next[0], b));
    ASSERT_TRUE(handle_equal(next[1], unkeyed));
    ASSERT_TRUE(handle_equal(next[2], a));
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 2u);
    MyComposeNodeHandle applied[MY_COMPOSE_MAX_NODES] = {a, unkeyed, b};
    MyComposeNodeHandle expected[3] = {b, unkeyed, a};
    uint32_t applied_count = 3u;
    ASSERT_TRUE(apply_diff_in_order(applied, &applied_count, diff));
    ASSERT_EQ(applied_count, 3u);
    for (uint32_t i = 0u; i < 3u; ++i) {
        ASSERT_TRUE(handle_equal(applied[i], expected[i]));
    }
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_MOVE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, b));
    ASSERT_EQ(diff->ops[0].from_index, 2u);
    ASSERT_EQ(diff->ops[0].to_index, 0u);
    ASSERT_EQ(diff->ops[1].type, MY_COMPOSE_DIFF_MOVE);
    ASSERT_TRUE(handle_equal(diff->ops[1].node, a));
    ASSERT_EQ(diff->ops[1].from_index, 1u);
    ASSERT_EQ(diff->ops[1].to_index, 2u);
    my_compose_tree_builder_destroy(builder);
}

TEST(mixed_reorder_with_create_keeps_unkeyed_fixed) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle a;
    MyComposeNodeHandle unkeyed;
    MyComposeNodeHandle b;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &a), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, NULL, "label", &unkeyed), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "b", "button", &b), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeNodeHandle next_b;
    MyComposeNodeHandle next_unkeyed;
    MyComposeNodeHandle created;
    MyComposeNodeHandle next_a;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "b", "button", &next_b), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, NULL, "label", &next_unkeyed), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "c", "button", &created), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &next_a), MY_COMPOSE_OK);
    ASSERT_TRUE(handle_equal(next_b, b));
    ASSERT_TRUE(handle_equal(next_unkeyed, unkeyed));
    ASSERT_TRUE(handle_equal(next_a, a));
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 3u);
    MyComposeNodeHandle applied[MY_COMPOSE_MAX_NODES] = {a, unkeyed, b};
    MyComposeNodeHandle expected[4] = {b, unkeyed, created, a};
    uint32_t applied_count = 3u;
    ASSERT_TRUE(apply_diff_in_order(applied, &applied_count, diff));
    ASSERT_EQ(applied_count, 4u);
    for (uint32_t i = 0u; i < 4u; ++i) {
        ASSERT_TRUE(handle_equal(applied[i], expected[i]));
    }
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, created));
    ASSERT_EQ(diff->ops[1].type, MY_COMPOSE_DIFF_MOVE);
    ASSERT_TRUE(handle_equal(diff->ops[1].node, b));
    ASSERT_EQ(diff->ops[1].from_index, 3u);
    ASSERT_EQ(diff->ops[1].to_index, 0u);
    ASSERT_EQ(diff->ops[2].type, MY_COMPOSE_DIFF_MOVE);
    ASSERT_TRUE(handle_equal(diff->ops[2].node, a));
    ASSERT_EQ(diff->ops[2].from_index, 1u);
    ASSERT_EQ(diff->ops[2].to_index, 3u);
    my_compose_tree_builder_destroy(builder);
}

TEST(unkeyed_insert_uses_absolute_child_position) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle column;
    MyComposeNodeHandle first;
    MyComposeNodeHandle old_edit;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, NULL, "button", &first), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, NULL, "edit", &old_edit), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeNodeHandle next_first;
    MyComposeNodeHandle label;
    MyComposeNodeHandle new_edit;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, NULL, "button", &next_first), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, NULL, "label", &label), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, NULL, "edit", &new_edit), MY_COMPOSE_OK);
    ASSERT_TRUE(handle_equal(first, next_first));
    ASSERT_FALSE(handle_equal(old_edit, new_edit));
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 3u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, old_edit));
    ASSERT_EQ(diff->ops[1].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[1].node, label));
    ASSERT_EQ(diff->ops[2].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[2].node, new_edit));
    my_compose_tree_builder_destroy(builder);
}

TEST(type_change_is_delete_then_create_with_a_new_generation) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle column;
    MyComposeNodeHandle old_button;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "button", &old_button), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeNodeHandle edit;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "edit", &edit), MY_COMPOSE_OK);
    ASSERT_FALSE(handle_equal(old_button, edit));
    ASSERT_EQ(edit.index, old_button.index);
    ASSERT_EQ(edit.generation, old_button.generation + 1u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 2u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, old_button));
    ASSERT_EQ(diff->ops[1].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[1].node, edit));
    MyComposeNodeDesc actual;
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, old_button, &actual),
        MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, edit, &actual), MY_COMPOSE_OK);
    ASSERT_STR_EQ(actual.type, "edit");
    my_compose_tree_builder_destroy(builder);
}

TEST(cross_parent_key_is_delete_then_create) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle column;
    MyComposeNodeHandle stack;
    MyComposeNodeHandle old_item;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "stack", "@stack", &stack), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "shared", "button", &old_item), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeNodeHandle moved;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "stack", "@stack", &stack), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, stack, "shared", "button", &moved), MY_COMPOSE_OK);
    ASSERT_FALSE(handle_equal(old_item, moved));
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 2u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, old_item));
    ASSERT_EQ(diff->ops[1].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[1].node, moved));
    ASSERT_TRUE(handle_equal(diff->ops[1].parent, stack));
    my_compose_tree_builder_destroy(builder);
}

TEST(full_tree_cross_parent_replace_uses_a_new_generation) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle column;
    MyComposeNodeHandle stack;
    MyComposeNodeHandle items[MY_COMPOSE_MAX_NODES - 3u];
    char key[16];
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "stack", "@stack", &stack), MY_COMPOSE_OK);
    for (uint32_t i = 0; i < MY_COMPOSE_MAX_NODES - 3u; ++i) {
        snprintf(key, sizeof(key), "k%u", i);
        ASSERT_EQ(add_node(builder, column, key, "node", &items[i]), MY_COMPOSE_OK);
    }
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "stack", "@stack", &stack), MY_COMPOSE_OK);
    for (uint32_t i = 1u; i < MY_COMPOSE_MAX_NODES - 3u; ++i) {
        MyComposeNodeHandle next;
        snprintf(key, sizeof(key), "k%u", i);
        ASSERT_EQ(add_node(builder, column, key, "node", &next), MY_COMPOSE_OK);
        ASSERT_TRUE(handle_equal(next, items[i]));
    }
    MyComposeNodeHandle moved;
    ASSERT_EQ(add_node(builder, stack, "k0", "node", &moved), MY_COMPOSE_OK);
    ASSERT_EQ(moved.index, items[0].index);
    ASSERT_EQ(moved.generation, items[0].generation + 1u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 2u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, items[0]));
    ASSERT_EQ(diff->ops[1].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[1].node, moved));
    my_compose_tree_builder_destroy(builder);
}

TEST(full_tree_unkeyed_cross_parent_reclaims_disappearing_slot) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle column;
    MyComposeNodeHandle stack;
    MyComposeNodeHandle items[MY_COMPOSE_MAX_NODES - 3u];
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "stack", "@stack", &stack), MY_COMPOSE_OK);
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES - 3u; ++i) {
        ASSERT_EQ(add_node(builder, column, NULL, "node", &items[i]), MY_COMPOSE_OK);
    }
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "stack", "@stack", &stack), MY_COMPOSE_OK);
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES - 4u; ++i) {
        MyComposeNodeHandle next;
        ASSERT_EQ(add_node(builder, column, NULL, "node", &next), MY_COMPOSE_OK);
        ASSERT_TRUE(handle_equal(next, items[i]));
    }
    MyComposeNodeHandle moved;
    ASSERT_EQ(add_node(builder, stack, NULL, "node", &moved), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_next_node_count(builder), MY_COMPOSE_MAX_NODES);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), MY_COMPOSE_MAX_NODES);
    ASSERT_EQ(moved.index, items[MY_COMPOSE_MAX_NODES - 4u].index);
    ASSERT_EQ(moved.generation, items[MY_COMPOSE_MAX_NODES - 4u].generation + 1u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 2u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node,
        items[MY_COMPOSE_MAX_NODES - 4u]));
    ASSERT_EQ(diff->ops[1].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[1].node, moved));
    my_compose_tree_builder_destroy(builder);
}

TEST(full_tree_duplicate_key_subtree_replacement_reuses_only_retiring_slots) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle left;
    MyComposeNodeHandle right;
    MyComposeNodeHandle other;
    MyComposeNodeHandle old_branch;
    MyComposeNodeHandle old_children[2];
    MyComposeNodeHandle right_branch;
    MyComposeNodeHandle fillers[MY_COMPOSE_MAX_NODES - 8u];
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "left", "@column", &left), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "right", "@column", &right), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "other", "@column", &other), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, left, "branch", "subtree", &old_branch), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, old_branch, NULL, "leaf", &old_children[0]),
        MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, old_branch, NULL, "leaf", &old_children[1]),
        MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, right, "branch", "leaf", &right_branch),
        MY_COMPOSE_OK);
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES - 8u; ++i) {
        ASSERT_EQ(add_node(builder, root, NULL, "filler", &fillers[i]),
            MY_COMPOSE_OK);
    }
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), 0u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), MY_COMPOSE_MAX_NODES);

    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "left", "@column", &left), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "right", "@column", &right), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "other", "@column", &other), MY_COMPOSE_OK);
    MyComposeNodeHandle next_right_branch;
    ASSERT_EQ(add_node(builder, right, "branch", "leaf", &next_right_branch),
        MY_COMPOSE_OK);
    ASSERT_TRUE(handle_equal(next_right_branch, right_branch));
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES - 8u; ++i) {
        MyComposeNodeHandle next;
        ASSERT_EQ(add_node(builder, root, NULL, "filler", &next), MY_COMPOSE_OK);
        ASSERT_TRUE(handle_equal(next, fillers[i]));
    }
    MyComposeNodeHandle new_branch;
    MyComposeNodeHandle new_children[2];
    ASSERT_EQ(add_node(builder, other, "branch", "subtree", &new_branch),
        MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, new_branch, NULL, "leaf", &new_children[0]),
        MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, new_branch, NULL, "leaf", &new_children[1]),
        MY_COMPOSE_OK);
    ASSERT_FALSE(handle_equal(new_branch, old_branch));
    ASSERT_NEQ(new_branch.index, right_branch.index);
    ASSERT_EQ(new_branch.generation, old_branch.generation + 1u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), MY_COMPOSE_MAX_NODES);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 6u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, old_children[1]));
    ASSERT_EQ(diff->ops[1].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_TRUE(handle_equal(diff->ops[1].node, old_children[0]));
    ASSERT_EQ(diff->ops[2].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_TRUE(handle_equal(diff->ops[2].node, old_branch));
    ASSERT_EQ(diff->ops[3].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[3].node, new_branch));
    ASSERT_EQ(diff->ops[4].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[4].node, new_children[0]));
    ASSERT_EQ(diff->ops[5].type, MY_COMPOSE_DIFF_CREATE);
    ASSERT_TRUE(handle_equal(diff->ops[5].node, new_children[1]));
    MyComposeNodeDesc actual;
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, right_branch, &actual),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, old_branch, &actual),
        MY_COMPOSE_STALE);
    my_compose_tree_builder_destroy(builder);
}

static MyComposeStatus add_full_slot_fillers(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle root, MyComposeNodeHandle fillers[MY_COMPOSE_MAX_NODES - 3u]) {
    char key[16];
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES - 3u; ++i) {
        snprintf(key, sizeof(key), "f%u", i);
        MyComposeStatus status = add_node(builder, root, key, "filler", &fillers[i]);
        if (status != MY_COMPOSE_OK) return status;
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus create_full_slot_fixture(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle *root, MyComposeNodeHandle *a, MyComposeNodeHandle *b,
    MyComposeNodeHandle fillers[MY_COMPOSE_MAX_NODES - 3u]) {
    MyComposeStatus status = begin_root(builder, root);
    if (status != MY_COMPOSE_OK) return status;
    status = add_node(builder, *root, "a", "button", a);
    if (status != MY_COMPOSE_OK) return status;
    status = add_node(builder, *root, "b", "button", b);
    if (status != MY_COMPOSE_OK) return status;
    status = add_full_slot_fillers(builder, *root, fillers);
    if (status != MY_COMPOSE_OK) return status;
    return finish(builder);
}

TEST(future_match_node_after_reclaim_keeps_identity_and_high_water) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle a;
    MyComposeNodeHandle b;
    MyComposeNodeHandle fillers[MY_COMPOSE_MAX_NODES - 3u];
    ASSERT_EQ(create_full_slot_fixture(builder, &root, &a, &b, fillers),
        MY_COMPOSE_OK);

    MyComposeNodeHandle incoming;
    MyComposeNodeHandle retained_a;
    MyComposeNodeHandle next_fillers[MY_COMPOSE_MAX_NODES - 3u];
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "incoming", "button", &incoming),
        MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &retained_a), MY_COMPOSE_OK);
    ASSERT_EQ(add_full_slot_fillers(builder, root, next_fillers), MY_COMPOSE_OK);
    ASSERT_TRUE(handle_equal(retained_a, a));
    ASSERT_EQ(incoming.index, a.index);
    ASSERT_EQ(incoming.generation, a.generation + 1u);
    ASSERT_FALSE(handle_equal(incoming, retained_a));
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES - 3u; ++i) {
        ASSERT_TRUE(handle_equal(next_fillers[i], fillers[i]));
    }
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    MyComposeNodeDesc actual;
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, incoming, &actual),
        MY_COMPOSE_OK);
    ASSERT_STR_EQ(actual.key, "incoming");
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, retained_a, &actual),
        MY_COMPOSE_OK);
    ASSERT_STR_EQ(actual.key, "a");
    ASSERT_STR_EQ(actual.type, "button");

    MyComposeNodeHandle replacement;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "edit", &replacement), MY_COMPOSE_OK);
    ASSERT_EQ(add_full_slot_fillers(builder, root, next_fillers), MY_COMPOSE_OK);
    ASSERT_EQ(replacement.index, a.index);
    ASSERT_EQ(replacement.generation, incoming.generation + 1u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, replacement, &actual),
        MY_COMPOSE_OK);
    ASSERT_STR_EQ(actual.key, "a");
    ASSERT_STR_EQ(actual.type, "edit");
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, incoming, &actual),
        MY_COMPOSE_STALE);
    my_compose_tree_builder_destroy(builder);
}

TEST(future_match_replace_after_reclaim_advances_generation_again) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle a;
    MyComposeNodeHandle b;
    MyComposeNodeHandle fillers[MY_COMPOSE_MAX_NODES - 3u];
    ASSERT_EQ(create_full_slot_fixture(builder, &root, &a, &b, fillers),
        MY_COMPOSE_OK);

    MyComposeNodeHandle incoming;
    MyComposeNodeHandle replacement;
    MyComposeNodeHandle next_fillers[MY_COMPOSE_MAX_NODES - 3u];
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "incoming", "button", &incoming),
        MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "edit", &replacement), MY_COMPOSE_OK);
    ASSERT_EQ(add_full_slot_fillers(builder, root, next_fillers), MY_COMPOSE_OK);
    ASSERT_EQ(incoming.index, replacement.index);
    ASSERT_EQ(incoming.generation, a.generation + 1u);
    MyComposeStatus publish_status = finish(builder);
    if (publish_status == MY_COMPOSE_CONFLICT) {
        ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
        ASSERT_EQ(my_compose_tree_builder_current_node_count(builder),
            MY_COMPOSE_MAX_NODES);
        MyComposeNodeDesc before;
        ASSERT_EQ(my_compose_tree_builder_get_node(builder, a, &before),
            MY_COMPOSE_OK);
        ASSERT_STR_EQ(before.key, "a");
        ASSERT_STR_EQ(before.type, "button");
    }
    ASSERT_EQ(publish_status, MY_COMPOSE_OK);
    ASSERT_EQ(replacement.generation, incoming.generation + 1u);
    ASSERT_FALSE(handle_equal(incoming, replacement));
    MyComposeNodeDesc actual;
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, incoming, &actual),
        MY_COMPOSE_OK);
    ASSERT_STR_EQ(actual.key, "incoming");
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, replacement, &actual),
        MY_COMPOSE_OK);
    ASSERT_STR_EQ(actual.key, "a");
    ASSERT_STR_EQ(actual.type, "edit");
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, a, &actual),
        MY_COMPOSE_STALE);
    my_compose_tree_builder_destroy(builder);
}

TEST(duplicate_key_preflight_leaves_next_and_current_unchanged) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle column;
    MyComposeNodeHandle a;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "button", &a), MY_COMPOSE_OK);
    MyComposeNodeHandle duplicate = {77u, 88u};
    ASSERT_EQ(add_node(builder, column, "a", "edit", &duplicate),
        MY_COMPOSE_DUPLICATE_KEY);
    ASSERT_EQ(duplicate.index, 77u);
    ASSERT_EQ(duplicate.generation, 88u);
    ASSERT_EQ(my_compose_tree_builder_next_node_count(builder), 3u);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), 0u);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeNodeHandle next_a;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "column", "@column", &column), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "button", &next_a), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, column, "a", "edit", &duplicate),
        MY_COMPOSE_DUPLICATE_KEY);
    ASSERT_EQ(my_compose_tree_builder_next_node_count(builder), 3u);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), 3u);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
    ASSERT_TRUE(handle_equal(a, next_a));
    MyComposeNodeDesc actual;
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, a, &actual), MY_COMPOSE_OK);
    ASSERT_STR_EQ(actual.type, "button");
    my_compose_tree_builder_destroy(builder);
}

TEST(property_and_event_payloads_are_owned_and_update_diffs_are_granular) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle item;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &item), MY_COMPOSE_OK);
    char text[] = {'b', 'e', 'f', 'o', 'r', 'e'};
    MyComposeValue value;
    memset(&value, 0, sizeof(value));
    value.type = MY_COMPOSE_VALUE_STRING;
    value.as.string.data = text;
    value.as.string.size = 6u;
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "title", &value),
        MY_COMPOSE_OK);
    uint8_t payload[] = {1u, 0u, 2u, 3u};
    MyComposeIntent intent = intent_value(73u, payload, sizeof(payload));
    ASSERT_EQ(my_compose_tree_builder_event(builder, item, "clicked", &intent),
        MY_COMPOSE_OK);
    memset(text, 'x', sizeof(text));
    memset(payload, 9u, sizeof(payload));
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeValue actual_value;
    ASSERT_EQ(my_compose_tree_builder_get_property(builder, item, "title", &actual_value),
        MY_COMPOSE_OK);
    ASSERT_EQ(actual_value.type, MY_COMPOSE_VALUE_STRING);
    ASSERT_EQ(actual_value.as.string.size, 6u);
    ASSERT_TRUE(memcmp(actual_value.as.string.data, "before", 6u) == 0);
    ASSERT_EQ(actual_value.as.string.data[6], '\0');
    MyComposeIntent actual_intent;
    ASSERT_EQ(my_compose_tree_builder_get_event(builder, item, "clicked", &actual_intent),
        MY_COMPOSE_OK);
    ASSERT_EQ(actual_intent.type, 73u);
    ASSERT_EQ(actual_intent.payload_size, 4u);
    const uint8_t expected_payload[] = {1u, 0u, 2u, 3u};
    ASSERT_TRUE(memcmp(actual_intent.payload, expected_payload, 4u) == 0);
    ASSERT_TRUE(handle_equal(actual_intent.owner, item));

    memcpy(text, "before", 6u);
    memcpy(payload, expected_payload, sizeof(payload));
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &item), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "title", &value),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_event(builder, item, "clicked", &intent),
        MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);

    memcpy(text, "after!", 6u);
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &item), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "title", &value),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_event(builder, item, "clicked", &intent),
        MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 1u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_UPDATE);
    ASSERT_TRUE(handle_equal(diff->ops[0].node, item));
    ASSERT_STR_EQ(diff->ops[0].name, "title");
    ASSERT_FALSE(diff->ops[0].on_event);

    memcpy(text, "after!", 6u);
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &item), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "title", &value),
        MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, 1u);
    ASSERT_EQ(diff->ops[0].type, MY_COMPOSE_DIFF_UPDATE);
    ASSERT_STR_EQ(diff->ops[0].name, "clicked");
    ASSERT_TRUE(diff->ops[0].on_event);
    my_compose_tree_builder_destroy(builder);
}

TEST(message_payload_limit_and_stale_handles_are_checked) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle item;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &item), MY_COMPOSE_OK);
    uint8_t payload[MY_COMPOSE_MESSAGE_BYTES + 1u];
    memset(payload, 0x5a, sizeof(payload));
    MyComposeIntent intent = intent_value(1u, payload, sizeof(payload));
    ASSERT_EQ(my_compose_tree_builder_event(builder, item, "event", &intent),
        MY_COMPOSE_OVERLOAD);
    intent.payload_size = MY_COMPOSE_MESSAGE_BYTES;
    ASSERT_EQ(my_compose_tree_builder_event(builder, item, "event", &intent),
        MY_COMPOSE_OK);
    MyComposeValue value = int_value(4);
    MyComposeNodeHandle stale = item;
    stale.generation++;
    ASSERT_EQ(my_compose_tree_builder_property(builder, stale, "value", &value),
        MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_tree_builder_event(builder, stale, "other", &intent),
        MY_COMPOSE_STALE);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    MyComposeIntent actual;
    ASSERT_EQ(my_compose_tree_builder_get_event(builder, item, "event", &actual),
        MY_COMPOSE_OK);
    ASSERT_EQ(actual.payload_size, MY_COMPOSE_MESSAGE_BYTES);
    ASSERT_EQ(actual.payload[0], 0x5a);
    ASSERT_EQ(actual.payload[MY_COMPOSE_MESSAGE_BYTES - 1u], 0x5a);
    my_compose_tree_builder_destroy(builder);
}

TEST(node_and_child_link_capacity_is_exact) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle child;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    for (uint32_t i = 1u; i < MY_COMPOSE_MAX_NODES; ++i) {
        ASSERT_EQ(add_node(builder, root, NULL, "node", &child), MY_COMPOSE_OK);
    }
    ASSERT_EQ(my_compose_tree_builder_next_node_count(builder), MY_COMPOSE_MAX_NODES);
    MyComposeNodeHandle overflow = {91u, 92u};
    ASSERT_EQ(add_node(builder, root, NULL, "node", &overflow), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(overflow.index, 91u);
    ASSERT_EQ(overflow.generation, 92u);
    ASSERT_EQ(my_compose_tree_builder_next_node_count(builder), MY_COMPOSE_MAX_NODES);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), MY_COMPOSE_MAX_NODES);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, MY_COMPOSE_MAX_NODES);
    my_compose_tree_builder_destroy(builder);
}

TEST(depth_32_is_accepted_and_33_is_overload) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle parent;
    ASSERT_EQ(begin_root(builder, &parent), MY_COMPOSE_OK);
    for (uint32_t depth = 2u; depth <= MY_COMPOSE_MAX_DEPTH; ++depth) {
        MyComposeNodeHandle child;
        ASSERT_EQ(add_node(builder, parent, NULL, "node", &child), MY_COMPOSE_OK);
        parent = child;
    }
    MyComposeNodeHandle overflow;
    ASSERT_EQ(add_node(builder, parent, NULL, "node", &overflow), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(my_compose_tree_builder_next_node_count(builder), MY_COMPOSE_MAX_DEPTH);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), MY_COMPOSE_MAX_DEPTH);
    my_compose_tree_builder_destroy(builder);
}

TEST(global_property_capacity_is_512) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle nodes[9];
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    for (uint32_t i = 0; i < 9u; ++i) {
        ASSERT_EQ(add_node(builder, root, NULL, "node", &nodes[i]), MY_COMPOSE_OK);
    }
    MyComposeValue value = int_value(7);
    char name[16];
    for (uint32_t i = 0; i < 8u; ++i) {
        for (uint32_t j = 0; j < 64u; ++j) {
            snprintf(name, sizeof(name), "p%u", j);
            ASSERT_EQ(my_compose_tree_builder_property(builder, nodes[i], name, &value),
                MY_COMPOSE_OK);
        }
    }
    ASSERT_EQ(my_compose_tree_builder_property(builder, nodes[8], "overflow", &value),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    MyComposeValue actual;
    ASSERT_EQ(my_compose_tree_builder_get_property(builder, nodes[7], "p63", &actual),
        MY_COMPOSE_OK);
    ASSERT_EQ(actual.as.int32_value, 7);
    my_compose_tree_builder_destroy(builder);
}

TEST(per_node_property_capacity_is_64) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle item;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, NULL, "node", &item), MY_COMPOSE_OK);
    MyComposeValue value = int_value(3);
    char name[16];
    for (uint32_t i = 0; i < 64u; ++i) {
        snprintf(name, sizeof(name), "p%u", i);
        ASSERT_EQ(my_compose_tree_builder_property(builder, item, name, &value),
            MY_COMPOSE_OK);
    }
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "p64", &value),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    MyComposeValue actual;
    ASSERT_EQ(my_compose_tree_builder_get_property(builder, item, "p63", &actual),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_get_property(builder, item, "p64", &actual),
        MY_COMPOSE_FAILED);
    my_compose_tree_builder_destroy(builder);
}

TEST(global_event_capacity_is_256) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle nodes[9];
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    for (uint32_t i = 0; i < 9u; ++i) {
        ASSERT_EQ(add_node(builder, root, NULL, "node", &nodes[i]), MY_COMPOSE_OK);
    }
    MyComposeIntent intent = intent_value(8u, NULL, 0u);
    char name[16];
    for (uint32_t i = 0; i < 8u; ++i) {
        for (uint32_t j = 0; j < 32u; ++j) {
            snprintf(name, sizeof(name), "e%u", j);
            ASSERT_EQ(my_compose_tree_builder_event(builder, nodes[i], name, &intent),
                MY_COMPOSE_OK);
        }
    }
    ASSERT_EQ(my_compose_tree_builder_event(builder, nodes[8], "overflow", &intent),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    MyComposeIntent actual;
    ASSERT_EQ(my_compose_tree_builder_get_event(builder, nodes[7], "e31", &actual),
        MY_COMPOSE_OK);
    ASSERT_EQ(actual.type, 8u);
    my_compose_tree_builder_destroy(builder);
}

TEST(per_node_event_capacity_is_32) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle item;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, NULL, "node", &item), MY_COMPOSE_OK);
    MyComposeIntent intent = intent_value(2u, NULL, 0u);
    char name[16];
    for (uint32_t i = 0; i < 32u; ++i) {
        snprintf(name, sizeof(name), "e%u", i);
        ASSERT_EQ(my_compose_tree_builder_event(builder, item, name, &intent),
            MY_COMPOSE_OK);
    }
    ASSERT_EQ(my_compose_tree_builder_event(builder, item, "e32", &intent),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    MyComposeIntent actual;
    ASSERT_EQ(my_compose_tree_builder_get_event(builder, item, "e31", &actual),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_get_event(builder, item, "e32", &actual),
        MY_COMPOSE_FAILED);
    my_compose_tree_builder_destroy(builder);
}

TEST(key_type_and_name_lengths_cannot_be_truncated) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    char long_key[MY_COMPOSE_KEY_BYTES + 1u];
    char long_type[MY_COMPOSE_TYPE_BYTES + 1u];
    char long_name[MY_COMPOSE_NAME_BYTES + 1u];
    memset(long_key, 'k', sizeof(long_key));
    memset(long_type, 't', sizeof(long_type));
    memset(long_name, 'n', sizeof(long_name));
    long_key[MY_COMPOSE_KEY_BYTES - 1u] = '\0';
    long_type[MY_COMPOSE_TYPE_BYTES - 1u] = '\0';
    long_name[MY_COMPOSE_NAME_BYTES - 1u] = '\0';
    MyComposeNodeHandle root;
    MyComposeNodeHandle item;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, long_key, long_type, &item), MY_COMPOSE_OK);
    long_key[MY_COMPOSE_KEY_BYTES - 1u] = 'k';
    long_key[MY_COMPOSE_KEY_BYTES] = '\0';
    MyComposeNodeHandle rejected;
    ASSERT_EQ(add_node(builder, root, long_key, "node", &rejected), MY_COMPOSE_OVERLOAD);
    long_type[MY_COMPOSE_TYPE_BYTES - 1u] = 't';
    long_type[MY_COMPOSE_TYPE_BYTES] = '\0';
    ASSERT_EQ(add_node(builder, root, "other", long_type, &rejected), MY_COMPOSE_OVERLOAD);
    MyComposeValue value = int_value(1);
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, long_name, &value),
        MY_COMPOSE_OK);
    long_name[MY_COMPOSE_NAME_BYTES - 1u] = 'n';
    long_name[MY_COMPOSE_NAME_BYTES] = '\0';
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "other", &value),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, long_name, &value),
        MY_COMPOSE_OVERLOAD);
    MyComposeIntent intent = intent_value(1u, NULL, 0u);
    ASSERT_EQ(my_compose_tree_builder_event(builder, item, long_name, &intent),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    my_compose_tree_builder_destroy(builder);
}

TEST(string_arena_boundary_and_embedded_nul_are_not_truncated) {
    const size_t max_value_size = MY_COMPOSE_STRING_BYTES -
        (sizeof("@root") + sizeof("n") + sizeof("p") + 1u);
    char *source = malloc(max_value_size + 1u);
    ASSERT_NOT_NULL(source);
    memset(source, 'v', max_value_size + 1u);

    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle item;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, NULL, "n", &item), MY_COMPOSE_OK);
    MyComposeValue value;
    memset(&value, 0, sizeof(value));
    value.type = MY_COMPOSE_VALUE_STRING;
    value.as.string.data = source;
    value.as.string.size = (uint32_t)max_value_size;
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "p", &value), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    MyComposeValue actual;
    ASSERT_EQ(my_compose_tree_builder_get_property(builder, item, "p", &actual), MY_COMPOSE_OK);
    ASSERT_EQ(actual.as.string.size, (uint32_t)max_value_size);
    ASSERT_EQ(actual.as.string.data[max_value_size], '\0');
    my_compose_tree_builder_destroy(builder);

    builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, NULL, "n", &item), MY_COMPOSE_OK);
    value.as.string.size = (uint32_t)max_value_size + 1u;
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "p", &value),
        MY_COMPOSE_OVERLOAD);
    value.as.string.data = "ok";
    value.as.string.size = 2u;
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "p", &value), MY_COMPOSE_OK);
    const char embedded[] = {'a', '\0', 'b'};
    value.as.string.data = embedded;
    value.as.string.size = sizeof(embedded);
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "embedded", &value),
        MY_COMPOSE_INVALID);
    value.as.string.data = NULL;
    value.as.string.size = 0u;
    ASSERT_EQ(my_compose_tree_builder_property(builder, item, "empty", &value),
        MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_get_property(builder, item, "p", &actual), MY_COMPOSE_OK);
    ASSERT_STR_EQ(actual.as.string.data, "ok");
    ASSERT_EQ(my_compose_tree_builder_get_property(builder, item, "embedded", &actual),
        MY_COMPOSE_FAILED);
    ASSERT_EQ(my_compose_tree_builder_get_property(builder, item, "empty", &actual),
        MY_COMPOSE_OK);
    ASSERT_EQ(actual.as.string.size, 0u);
    ASSERT_NOT_NULL(actual.as.string.data);
    ASSERT_EQ(actual.as.string.data[0], '\0');
    free(source);
    my_compose_tree_builder_destroy(builder);
}

TEST(root_parent_and_build_state_validation) {
    ASSERT_EQ(my_compose_tree_builder_begin(NULL), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_end(NULL), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_finalize(NULL), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_diff(NULL), (const MyComposeDiff *)NULL);
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    ASSERT_EQ(my_compose_tree_builder_end(builder), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_finalize(builder), MY_COMPOSE_INVALID);
    MyComposeNodeHandle node;
    ASSERT_EQ(my_compose_tree_builder_begin(builder), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, zero_handle(), NULL, "@column", &node), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_next_node_count(builder), 0u);
    MyComposeNodeHandle root;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, zero_handle(), NULL, "@root", &node), MY_COMPOSE_INVALID);
    MyComposeNodeHandle unknown = {200u, 3u};
    ASSERT_EQ(add_node(builder, unknown, NULL, "node", &node), MY_COMPOSE_STALE);
    MyComposeValue value = int_value(1);
    ASSERT_EQ(my_compose_tree_builder_end(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_property(builder, root, "p", &value),
        MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_finalize(builder), MY_COMPOSE_OK);
    my_compose_tree_builder_destroy(builder);
}

static MyComposeStatus declare_diff_capacity_tree(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle handles[MY_COMPOSE_MAX_NODES], bool changed,
    bool change_extra_property) {
    MyComposeStatus status = begin_root(builder, &handles[0]);
    if (status != MY_COMPOSE_OK) return status;
    for (uint32_t i = 1u; i < MY_COMPOSE_MAX_NODES; ++i) {
        status = add_node(builder, handles[0], NULL, "n", &handles[i]);
        if (status != MY_COMPOSE_OK) return status;
    }
    char name[16];
    for (uint32_t i = 0; i < MY_COMPOSE_MAX_NODES; ++i) {
        for (uint32_t j = 0; j < 2u; ++j) {
            uint32_t property_index = i * 2u + j;
            if (changed && property_index < 256u) {
                snprintf(name, sizeof(name), "q%u", property_index);
            } else {
                snprintf(name, sizeof(name), "p%u", property_index);
            }
            int32_t property_value = 1;
            if (changed && change_extra_property && property_index == 256u) {
                property_value = 2;
            }
            MyComposeValue value = int_value(property_value);
            status = my_compose_tree_builder_property(builder, handles[i], name, &value);
            if (status != MY_COMPOSE_OK) return status;
        }
        if (changed) {
            snprintf(name, sizeof(name), "r%u", i);
        } else {
            snprintf(name, sizeof(name), "e%u", i);
        }
        MyComposeIntent intent = intent_value(11u, NULL, 0u);
        status = my_compose_tree_builder_event(builder, handles[i], name, &intent);
        if (status != MY_COMPOSE_OK) return status;
    }
    return MY_COMPOSE_OK;
}

TEST(diff_op_1024_is_accepted) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle handles[MY_COMPOSE_MAX_NODES];
    ASSERT_EQ(declare_diff_capacity_tree(builder, handles, false, false), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, MY_COMPOSE_MAX_NODES);
    ASSERT_EQ(declare_diff_capacity_tree(builder, handles, true, false), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const MyComposeDiff *diff = my_compose_tree_builder_diff(builder);
    ASSERT_EQ(diff->count, MY_COMPOSE_MAX_DIFF_OPS);
    for (uint32_t i = 0; i < diff->count; ++i) {
        ASSERT_EQ(diff->ops[i].type, MY_COMPOSE_DIFF_UPDATE);
    }
    my_compose_tree_builder_destroy(builder);
}

TEST(diff_op_1025_fails_without_publishing) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle handles[MY_COMPOSE_MAX_NODES];
    ASSERT_EQ(declare_diff_capacity_tree(builder, handles, false, false), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(declare_diff_capacity_tree(builder, handles, true, true), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), MY_COMPOSE_MAX_NODES);
    MyComposeValue value;
    ASSERT_EQ(my_compose_tree_builder_get_property(builder, handles[128], "p256", &value),
        MY_COMPOSE_OK);
    ASSERT_EQ(value.as.int32_value, 1);
    MyComposeIntent intent;
    ASSERT_EQ(my_compose_tree_builder_get_event(builder, handles[0], "e0", &intent),
        MY_COMPOSE_OK);
    my_compose_tree_builder_destroy(builder);
}

TEST(generation_near_overflow_never_wraps_and_retires_slot) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle old_item;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &old_item), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_internal_seed_generation(builder, old_item,
        UINT32_MAX - 1u), MY_COMPOSE_OK);
    MyComposeNodeHandle near_limit = old_item;
    near_limit.generation = UINT32_MAX - 1u;
    MyComposeNodeDesc actual;
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, near_limit, &actual), MY_COMPOSE_OK);

    MyComposeNodeHandle replacement;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "edit", &replacement), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, near_limit, &actual), MY_COMPOSE_OK);
    ASSERT_STR_EQ(actual.type, "button");

    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 1u);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->ops[0].type, MY_COMPOSE_DIFF_DELETE);
    ASSERT_EQ(my_compose_tree_builder_get_node(builder, near_limit, &actual), MY_COMPOSE_STALE);

    MyComposeNodeHandle recreated;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &recreated), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_NEQ(recreated.index, near_limit.index);
    ASSERT_NEQ(recreated.generation, 0u);
    ASSERT_NEQ(recreated.generation, UINT32_MAX);
    my_compose_tree_builder_destroy(builder);
}

TEST(end_prepares_diff_before_nonfailing_finalize) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    MyComposeNodeHandle root;
    MyComposeNodeHandle item;
    ASSERT_NOT_NULL(builder);
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &item), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_end(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), 0u);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 2u);
    ASSERT_EQ(my_compose_tree_builder_finalize(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_current_node_count(builder), 2u);
    ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 2u);
    my_compose_tree_builder_destroy(builder);
}

int main(void) {
    RUN_TEST(end_prepares_diff_before_nonfailing_finalize);
    RUN_TEST(lifecycle_insert_noop_and_delete);
    RUN_TEST(keyed_reorder_only_moves_and_preserves_handles);
    RUN_TEST(mixed_keyed_and_unkeyed_nodes_keep_their_identity_rules);
    RUN_TEST(mixed_reorder_with_create_keeps_unkeyed_fixed);
    RUN_TEST(unkeyed_insert_uses_absolute_child_position);
    RUN_TEST(type_change_is_delete_then_create_with_a_new_generation);
    RUN_TEST(cross_parent_key_is_delete_then_create);
    RUN_TEST(full_tree_cross_parent_replace_uses_a_new_generation);
    RUN_TEST(full_tree_unkeyed_cross_parent_reclaims_disappearing_slot);
    RUN_TEST(full_tree_duplicate_key_subtree_replacement_reuses_only_retiring_slots);
    RUN_TEST(future_match_node_after_reclaim_keeps_identity_and_high_water);
    RUN_TEST(future_match_replace_after_reclaim_advances_generation_again);
    RUN_TEST(duplicate_key_preflight_leaves_next_and_current_unchanged);
    RUN_TEST(property_and_event_payloads_are_owned_and_update_diffs_are_granular);
    RUN_TEST(message_payload_limit_and_stale_handles_are_checked);
    RUN_TEST(node_and_child_link_capacity_is_exact);
    RUN_TEST(depth_32_is_accepted_and_33_is_overload);
    RUN_TEST(global_property_capacity_is_512);
    RUN_TEST(per_node_property_capacity_is_64);
    RUN_TEST(global_event_capacity_is_256);
    RUN_TEST(per_node_event_capacity_is_32);
    RUN_TEST(key_type_and_name_lengths_cannot_be_truncated);
    RUN_TEST(string_arena_boundary_and_embedded_nul_are_not_truncated);
    RUN_TEST(root_parent_and_build_state_validation);
    RUN_TEST(diff_op_1024_is_accepted);
    RUN_TEST(diff_op_1025_fails_without_publishing);
    RUN_TEST(generation_near_overflow_never_wraps_and_retires_slot);

    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
        g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
