#include "test_framework.h"

#include <myui/mycompose/my_compose_internal.h>
#include <myui/mycompose/my_compose_remember.h>
#include <myui/mycompose/my_compose_tree.h>

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define DISPOSE_LOG_CAPACITY 128u

typedef struct RememberValue {
    uint32_t id;
    uint32_t value;
} RememberValue;

typedef struct DisposeLog {
    uint32_t order[DISPOSE_LOG_CAPACITY];
    uint32_t sizes[DISPOSE_LOG_CAPACITY];
    const void *storage[DISPOSE_LOG_CAPACITY];
    uint32_t counts[DISPOSE_LOG_CAPACITY];
    uint32_t count;
} DisposeLog;

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

static void record_dispose(void *context, void *storage, uint32_t size) {
    DisposeLog *log = context;
    const RememberValue *value = storage;
    uint32_t id = value->id;
    if (log->count < DISPOSE_LOG_CAPACITY) {
        log->order[log->count] = id;
        log->sizes[log->count] = size;
        log->storage[log->count] = storage;
    }
    log->count++;
    if (id < DISPOSE_LOG_CAPACITY) log->counts[id]++;
}

static MyComposeRememberOps dispose_ops(DisposeLog *log) {
    MyComposeRememberOps ops;
    ops.context = log;
    ops.dispose = record_dispose;
    return ops;
}

static MyComposeStatus remember_value(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle owner, uint32_t local_slot, uint64_t type_tag,
    DisposeLog *log, void **out) {
    MyComposeRememberOps ops = dispose_ops(log);
    return my_compose_tree_builder_remember(builder, owner, local_slot, type_tag,
        32u, MY_COMPOSE_MAX_ALIGNMENT, &ops, out);
}

static void set_value(void *storage, uint32_t id, uint32_t value) {
    RememberValue *remembered = storage;
    remembered->id = id;
    remembered->value = value;
}

TEST(keyed_reorder_preserves_storage_pointer_and_value) {
    DisposeLog log;
    memset(&log, 0, sizeof(log));
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle a;
    MyComposeNodeHandle b;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &a), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "b", "button", &b), MY_COMPOSE_OK);
    void *a_storage = NULL;
    void *b_storage = NULL;
    ASSERT_EQ(remember_value(builder, a, 0u, 11u, &log, &a_storage),
        MY_COMPOSE_OK);
    ASSERT_EQ(remember_value(builder, b, 0u, 12u, &log, &b_storage),
        MY_COMPOSE_OK);
    ASSERT_EQ((uintptr_t)a_storage % MY_COMPOSE_MAX_ALIGNMENT, 0u);
    set_value(a_storage, 1u, 1234u);
    set_value(b_storage, 2u, 5678u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(log.count, 0u);

    MyComposeNodeHandle next_b;
    MyComposeNodeHandle next_a;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "b", "button", &next_b), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &next_a), MY_COMPOSE_OK);
    ASSERT_TRUE(handle_equal(next_a, a));
    ASSERT_TRUE(handle_equal(next_b, b));
    void *reused_b = NULL;
    void *reused_a = NULL;
    ASSERT_EQ(remember_value(builder, next_b, 0u, 12u, &log, &reused_b),
        MY_COMPOSE_OK);
    ASSERT_EQ(remember_value(builder, next_a, 0u, 11u, &log, &reused_a),
        MY_COMPOSE_OK);
    ASSERT_EQ(reused_a, a_storage);
    ASSERT_EQ(reused_b, b_storage);
    ASSERT_EQ(((RememberValue *)reused_a)->value, 1234u);
    ASSERT_EQ(((RememberValue *)reused_b)->value, 5678u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(log.count, 0u);

    void *current = NULL;
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, a, 0u, &current),
        MY_COMPOSE_OK);
    ASSERT_EQ(current, a_storage);
    ASSERT_EQ(((RememberValue *)current)->value, 1234u);
    my_compose_tree_builder_destroy(builder);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(log.counts[1], 1u);
    ASSERT_EQ(log.counts[2], 1u);
}

TEST(type_replacement_retires_old_generation_exactly_once) {
    DisposeLog log;
    memset(&log, 0, sizeof(log));
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle old_button;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &old_button), MY_COMPOSE_OK);
    void *old_storage = NULL;
    ASSERT_EQ(remember_value(builder, old_button, 0u, 21u, &log, &old_storage),
        MY_COMPOSE_OK);
    set_value(old_storage, 1u, 99u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeNodeHandle edit;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "edit", &edit), MY_COMPOSE_OK);
    ASSERT_FALSE(handle_equal(edit, old_button));
    void *current = NULL;
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, old_button, 0u,
        &current), MY_COMPOSE_OK);
    ASSERT_EQ(current, old_storage);
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, edit, 0u, &current),
        MY_COMPOSE_STALE);
    void *new_storage = NULL;
    ASSERT_EQ(remember_value(builder, edit, 0u, 21u, &log, &new_storage),
        MY_COMPOSE_OK);
    ASSERT_NEQ(new_storage, old_storage);
    for (uint32_t i = 0u; i < 32u; ++i) {
        ASSERT_EQ(((uint8_t *)new_storage)[i], 0u);
    }
    set_value(new_storage, 2u, 100u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(log.count, 1u);
    ASSERT_EQ(log.order[0], 1u);
    ASSERT_EQ(log.sizes[0], 32u);
    ASSERT_EQ(log.storage[0], old_storage);
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, old_button, 0u,
        &current), MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, edit, 0u, &current),
        MY_COMPOSE_OK);
    ASSERT_EQ(current, new_storage);
    ASSERT_EQ(my_compose_tree_builder_finalize(builder), MY_COMPOSE_INVALID);
    ASSERT_EQ(log.count, 1u);

    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(log.order[1], 2u);
    ASSERT_EQ(log.counts[1], 1u);
    ASSERT_EQ(log.counts[2], 1u);
    ASSERT_EQ(my_compose_tree_builder_finalize(builder), MY_COMPOSE_INVALID);
    ASSERT_EQ(log.count, 2u);
    my_compose_tree_builder_destroy(builder);
    ASSERT_EQ(log.count, 2u);
}

TEST(removal_disposes_by_depth_then_reverse_declaration) {
    DisposeLog log;
    memset(&log, 0, sizeof(log));
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle parent;
    MyComposeNodeHandle first;
    MyComposeNodeHandle grandchild;
    MyComposeNodeHandle second;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "parent", "@column", &parent),
        MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, parent, "first", "node", &first), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, first, "grandchild", "node", &grandchild),
        MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, parent, "second", "node", &second),
        MY_COMPOSE_OK);
    MyComposeNodeHandle owners[] = {parent, first, grandchild, second};
    uint32_t ids[] = {10u, 20u, 30u, 40u};
    for (uint32_t i = 0u; i < 4u; ++i) {
        for (uint32_t local = 0u; local < 2u; ++local) {
            void *storage = NULL;
            ASSERT_EQ(remember_value(builder, owners[i], local, 30u + i,
                &log, &storage), MY_COMPOSE_OK);
            set_value(storage, ids[i] + local, local);
        }
    }
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    const uint32_t expected[] = {31u, 30u, 41u, 40u, 21u, 20u, 11u, 10u};
    ASSERT_EQ(log.count, 8u);
    for (uint32_t i = 0u; i < 8u; ++i) {
        ASSERT_EQ(log.order[i], expected[i]);
        ASSERT_EQ(log.counts[expected[i]], 1u);
    }
    ASSERT_EQ(my_compose_tree_builder_finalize(builder), MY_COMPOSE_INVALID);
    ASSERT_EQ(log.count, 8u);
    my_compose_tree_builder_destroy(builder);
    ASSERT_EQ(log.count, 8u);
}

TEST(aborted_replacement_disposes_only_candidate_storage) {
    DisposeLog log;
    memset(&log, 0, sizeof(log));
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle old_button;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &old_button), MY_COMPOSE_OK);
    void *old_storage = NULL;
    ASSERT_EQ(remember_value(builder, old_button, 0u, 41u, &log, &old_storage),
        MY_COMPOSE_OK);
    set_value(old_storage, 1u, 77u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    MyComposeNodeHandle replacement;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "edit", &replacement), MY_COMPOSE_OK);
    void *candidate = NULL;
    ASSERT_EQ(remember_value(builder, replacement, 0u, 41u, &log, &candidate),
        MY_COMPOSE_OK);
    set_value(candidate, 2u, 88u);
    ASSERT_EQ(my_compose_tree_builder_begin(builder), MY_COMPOSE_OK);
    ASSERT_EQ(log.count, 1u);
    ASSERT_EQ(log.order[0], 2u);
    ASSERT_EQ(log.counts[1], 0u);
    void *current = NULL;
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, old_button, 0u,
        &current), MY_COMPOSE_OK);
    ASSERT_EQ(current, old_storage);
    ASSERT_EQ(((RememberValue *)current)->value, 77u);
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, replacement, 0u,
        &current), MY_COMPOSE_STALE);

    ASSERT_EQ(add_node(builder, zero_handle(), NULL, "@root", &root),
        MY_COMPOSE_OK);
    MyComposeNodeHandle retained;
    ASSERT_EQ(add_node(builder, root, "a", "button", &retained), MY_COMPOSE_OK);
    ASSERT_TRUE(handle_equal(retained, old_button));
    void *reused = NULL;
    ASSERT_EQ(remember_value(builder, retained, 0u, 41u, &log, &reused),
        MY_COMPOSE_OK);
    ASSERT_EQ(reused, old_storage);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(log.count, 1u);
    my_compose_tree_builder_destroy(builder);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(log.counts[1], 1u);
    ASSERT_EQ(log.counts[2], 1u);
}

TEST(finalize_failure_preserves_current_and_restart_cleans_candidate) {
    DisposeLog log;
    memset(&log, 0, sizeof(log));
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle old_button;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "button", &old_button), MY_COMPOSE_OK);
    void *old_storage = NULL;
    ASSERT_EQ(remember_value(builder, old_button, 0u, 51u, &log, &old_storage),
        MY_COMPOSE_OK);
    set_value(old_storage, 1u, 123u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_internal_seed_generation(builder, old_button,
        UINT32_MAX - 1u), MY_COMPOSE_OK);
    MyComposeNodeHandle near_limit = old_button;
    near_limit.generation = UINT32_MAX - 1u;
    void *current = NULL;
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, near_limit, 0u,
        &current), MY_COMPOSE_OK);
    ASSERT_EQ(current, old_storage);

    MyComposeNodeHandle replacement;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "edit", &replacement), MY_COMPOSE_OK);
    void *candidate = NULL;
    ASSERT_EQ(remember_value(builder, replacement, 0u, 51u, &log, &candidate),
        MY_COMPOSE_OK);
    set_value(candidate, 2u, 456u);
    ASSERT_EQ(my_compose_tree_builder_end(builder), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_tree_builder_finalize(builder), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(log.count, 0u);
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, near_limit, 0u,
        &current), MY_COMPOSE_OK);
    ASSERT_EQ(((RememberValue *)current)->value, 123u);
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, replacement, 0u,
        &current), MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_tree_builder_finalize(builder), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(log.count, 0u);

    ASSERT_EQ(my_compose_tree_builder_begin(builder), MY_COMPOSE_OK);
    ASSERT_EQ(log.count, 1u);
    ASSERT_EQ(log.order[0], 2u);
    ASSERT_EQ(log.counts[1], 0u);
    ASSERT_EQ(add_node(builder, zero_handle(), NULL, "@root", &root),
        MY_COMPOSE_OK);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(log.order[1], 1u);
    ASSERT_EQ(log.counts[1], 1u);
    my_compose_tree_builder_destroy(builder);
    ASSERT_EQ(log.count, 2u);
}

TEST(input_limits_and_local_type_mismatch_do_not_overwrite_storage) {
    DisposeLog log;
    memset(&log, 0, sizeof(log));
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle item;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "node", &item), MY_COMPOSE_OK);
    MyComposeRememberOps ops = dispose_ops(&log);
    void *storage = (void *)(uintptr_t)1u;
    ASSERT_EQ(my_compose_tree_builder_remember(NULL, item, 0u, 1u, 32u, 1u,
        &ops, &storage), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_remember(builder, item, 0u, 1u, 32u, 1u,
        &ops, NULL), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_remember(builder, item, 4u, 1u, 32u, 1u,
        &ops, &storage), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(storage, (void *)(uintptr_t)1u);
    ASSERT_EQ(my_compose_tree_builder_remember(builder, item, 0u, 1u, 257u, 1u,
        &ops, &storage), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(my_compose_tree_builder_remember(builder, item, 0u, 1u, 0u, 1u,
        &ops, &storage), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_remember(builder, item, 0u, 1u, 32u, 0u,
        &ops, &storage), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_remember(builder, item, 0u, 1u, 32u, 3u,
        &ops, &storage), MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_remember(builder, item, 0u, 1u, 32u,
        MY_COMPOSE_MAX_ALIGNMENT * 2u, &ops, &storage),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(storage, (void *)(uintptr_t)1u);

    ASSERT_EQ(remember_value(builder, item, 0u, 61u, &log, &storage),
        MY_COMPOSE_OK);
    set_value(storage, 1u, 999u);
    void *original = storage;
    storage = (void *)(uintptr_t)1u;
    ASSERT_EQ(remember_value(builder, item, 0u, 62u, &log, &storage),
        MY_COMPOSE_TYPE_MISMATCH);
    ASSERT_EQ(storage, (void *)(uintptr_t)1u);
    ASSERT_EQ(((RememberValue *)original)->value, 999u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    ASSERT_EQ(log.count, 0u);
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, item, 0u, &storage),
        MY_COMPOSE_OK);
    ASSERT_EQ(storage, original);
    ASSERT_EQ(((RememberValue *)storage)->value, 999u);
    storage = (void *)(uintptr_t)1u;
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, item, 1u, &storage),
        MY_COMPOSE_FAILED);
    ASSERT_EQ(storage, (void *)(uintptr_t)1u);
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, item, 4u, &storage),
        MY_COMPOSE_OVERLOAD);
    MyComposeNodeHandle stale = item;
    stale.generation++;
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, stale, 0u, &storage),
        MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_tree_builder_remember_get(NULL, item, 0u, &storage),
        MY_COMPOSE_INVALID);
    ASSERT_EQ(my_compose_tree_builder_remember_get(builder, item, 0u, NULL),
        MY_COMPOSE_INVALID);
    my_compose_tree_builder_destroy(builder);
    ASSERT_EQ(log.counts[1], 1u);
}

TEST(global_capacity_accepts_64_and_rejects_the_real_65th_slot) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle nodes[16];
    void *storage[64];
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    char key[16];
    for (uint32_t i = 0u; i < 16u; ++i) {
        snprintf(key, sizeof(key), "n%u", i);
        ASSERT_EQ(add_node(builder, root, key, "node", &nodes[i]), MY_COMPOSE_OK);
        for (uint32_t local = 0u; local < 4u; ++local) {
            uint32_t index = i * 4u + local;
            ASSERT_EQ(my_compose_tree_builder_remember(builder, nodes[i], local,
                1000u + index, 1u, 1u, NULL, &storage[index]), MY_COMPOSE_OK);
            *(uint8_t *)storage[index] = (uint8_t)(index + 1u);
        }
    }
    MyComposeNodeHandle overflow;
    ASSERT_EQ(add_node(builder, root, "overflow", "node", &overflow),
        MY_COMPOSE_OK);
    void *rejected = (void *)(uintptr_t)1u;
    ASSERT_EQ(my_compose_tree_builder_remember(builder, overflow, 0u, 2000u,
        1u, 1u, NULL, &rejected), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(rejected, (void *)(uintptr_t)1u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);
    for (uint32_t i = 0u; i < 16u; ++i) {
        for (uint32_t local = 0u; local < 4u; ++local) {
            uint32_t index = i * 4u + local;
            void *current = NULL;
            ASSERT_EQ(my_compose_tree_builder_remember_get(builder, nodes[i],
                local, &current), MY_COMPOSE_OK);
            ASSERT_EQ(current, storage[index]);
            ASSERT_EQ(*(uint8_t *)current, (uint8_t)(index + 1u));
        }
    }
    my_compose_tree_builder_destroy(builder);
}

TEST(builder_destroy_disposes_current_and_uncommitted_candidate) {
    DisposeLog log;
    memset(&log, 0, sizeof(log));
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    ASSERT_NOT_NULL(builder);
    MyComposeNodeHandle root;
    MyComposeNodeHandle current_node;
    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "node", &current_node), MY_COMPOSE_OK);
    void *storage = NULL;
    ASSERT_EQ(remember_value(builder, current_node, 0u, 71u, &log, &storage),
        MY_COMPOSE_OK);
    set_value(storage, 1u, 1u);
    ASSERT_EQ(finish(builder), MY_COMPOSE_OK);

    ASSERT_EQ(begin_root(builder, &root), MY_COMPOSE_OK);
    ASSERT_EQ(add_node(builder, root, "a", "node", &current_node), MY_COMPOSE_OK);
    MyComposeNodeHandle candidate_node;
    ASSERT_EQ(add_node(builder, root, "b", "node", &candidate_node),
        MY_COMPOSE_OK);
    ASSERT_EQ(remember_value(builder, current_node, 0u, 71u, &log, &storage),
        MY_COMPOSE_OK);
    ASSERT_EQ(remember_value(builder, candidate_node, 0u, 72u, &log, &storage),
        MY_COMPOSE_OK);
    set_value(storage, 2u, 2u);
    my_compose_tree_builder_destroy(builder);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(log.counts[1], 1u);
    ASSERT_EQ(log.counts[2], 1u);
}

int main(void) {
    RUN_TEST(keyed_reorder_preserves_storage_pointer_and_value);
    RUN_TEST(type_replacement_retires_old_generation_exactly_once);
    RUN_TEST(removal_disposes_by_depth_then_reverse_declaration);
    RUN_TEST(aborted_replacement_disposes_only_candidate_storage);
    RUN_TEST(finalize_failure_preserves_current_and_restart_cleans_candidate);
    RUN_TEST(input_limits_and_local_type_mismatch_do_not_overwrite_storage);
    RUN_TEST(global_capacity_accepts_64_and_rejects_the_real_65th_slot);
    RUN_TEST(builder_destroy_disposes_current_and_uncommitted_candidate);

    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
        g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
