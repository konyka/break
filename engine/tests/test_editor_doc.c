/* Stage 4 scene editor Phase 1 Task 1: BreakEditorDoc surface tests.
 *
 * Covers: create/destroy, add/remove/rename via the internal command stack,
 * the bounded name map (128-byte cap incl. NUL, over-cap REJECTED with
 * false), ascending-index entity iteration for the outliner, the dirty
 * flag, and OOM injection on every editor-owned allocation path. */

#include "test_framework.h"

#include <editor/editor_doc.h>
#include <editor/editor_test_hooks.h>

#include <ecs/ecs.h>

#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* BreakEditorEntityId must match the ECS Entity layout (ecs.h:14-17) — the
 * decision recorded in the Task 1 brief; no u64 flattening anywhere. */
_Static_assert(sizeof(BreakEditorEntityId) == sizeof(Entity),
               "BreakEditorEntityId must match Entity size");
_Static_assert(offsetof(BreakEditorEntityId, index) == offsetof(Entity, index),
               "BreakEditorEntityId.index must match Entity.index");
_Static_assert(offsetof(BreakEditorEntityId, generation) ==
                   offsetof(Entity, generation),
               "BreakEditorEntityId.generation must match Entity.generation");

static Entity to_ecs(BreakEditorEntityId id) {
    Entity e;
    e.index = id.index;
    e.generation = id.generation;
    return e;
}

static World *doc_world(BreakEditorDoc *doc) {
    return (World *)break_editor_doc_world(doc);
}

TEST(create_destroy_empty_doc) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));
    ASSERT_TRUE(break_editor_doc_world(doc) != NULL);

    BreakEditorEntityId out_id;
    const char *out_name = NULL;
    ASSERT_FALSE(break_editor_doc_entity_at(doc, 0, &out_id, &out_name));

    break_editor_doc_destroy(doc);
    break_editor_doc_destroy(NULL); /* bounded no-op */
}

TEST(add_entity_basic) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "alpha");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(id)));

    BreakEditorEntityId at_id = BREAK_EDITOR_ENTITY_NULL;
    const char *at_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, id));
    ASSERT_STR_EQ(at_name, "alpha");

    break_editor_doc_destroy(doc);
}

TEST(add_entity_null_name_generates_default) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, NULL);
    ASSERT_TRUE(break_editor_entity_id_valid(id));

    char expected[128];
    snprintf(expected, sizeof(expected), "entity_%u_%u", id.index,
             id.generation);
    const char *at_name = NULL;
    BreakEditorEntityId at_id;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, expected);

    break_editor_doc_destroy(doc);
}

TEST(name_capacity_127_ok_128_rejected) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    char name_ok[128]; /* 127 visible chars + NUL */
    memset(name_ok, 'a', sizeof(name_ok) - 1u);
    name_ok[sizeof(name_ok) - 1u] = '\0';
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, name_ok);
    ASSERT_TRUE(break_editor_entity_id_valid(id));

    char name_long[129]; /* 128 visible chars + NUL: over cap, rejected */
    memset(name_long, 'b', sizeof(name_long) - 1u);
    name_long[sizeof(name_long) - 1u] = '\0';
    usize before = break_editor_doc_entity_count(doc);
    BreakEditorEntityId bad = break_editor_doc_add_entity(doc, name_long);
    ASSERT_FALSE(break_editor_entity_id_valid(bad));
    ASSERT_EQ(break_editor_doc_entity_count(doc), before);

    /* Over-cap rename is rejected with false and leaves the name unchanged. */
    ASSERT_FALSE(break_editor_doc_rename_entity(doc, id, name_long));
    const char *at_name = NULL;
    BreakEditorEntityId at_id;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, name_ok);

    /* Boundary: rename to exactly 127 visible chars succeeds. */
    char name_edge[128];
    memset(name_edge, 'c', sizeof(name_edge) - 1u);
    name_edge[sizeof(name_edge) - 1u] = '\0';
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, id, name_edge));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, name_edge);

    break_editor_doc_destroy(doc);
}

TEST(rename_basic_and_stale_ids) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "old");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, id, "new"));

    const char *at_name = NULL;
    BreakEditorEntityId at_id;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, "new");

    /* Rename of a nonexistent id fails bounded. */
    BreakEditorEntityId bogus = {999u, 1u};
    ASSERT_FALSE(break_editor_doc_rename_entity(doc, bogus, "x"));
    ASSERT_FALSE(break_editor_doc_remove_entity(doc, bogus));

    /* Stale generation: remove then re-add reuses the index (ECS free-stack
     * LIFO) with a bumped generation; the old id must be rejected. */
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, id));
    BreakEditorEntityId id2 = break_editor_doc_add_entity(doc, "second");
    ASSERT_TRUE(break_editor_entity_id_valid(id2));
    ASSERT_EQ(id2.index, id.index);
    ASSERT_NEQ(id2.generation, id.generation);
    ASSERT_FALSE(break_editor_doc_rename_entity(doc, id, "stale"));
    ASSERT_FALSE(break_editor_doc_remove_entity(doc, id));

    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, "second");

    break_editor_doc_destroy(doc);
}

TEST(remove_entity_basic_and_double_remove) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "gone");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, id));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(id)));

    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_FALSE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));

    ASSERT_FALSE(break_editor_doc_remove_entity(doc, id));
    ASSERT_FALSE(break_editor_doc_remove_entity(doc, BREAK_EDITOR_ENTITY_NULL));

    break_editor_doc_destroy(doc);
}

TEST(entity_at_ascending_index_order) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId ids[4];
    ids[0] = break_editor_doc_add_entity(doc, "e0");
    ids[1] = break_editor_doc_add_entity(doc, "e1");
    ids[2] = break_editor_doc_add_entity(doc, "e2");
    ids[3] = break_editor_doc_add_entity(doc, "e3");
    for (int i = 0; i < 4; i++) ASSERT_TRUE(break_editor_entity_id_valid(ids[i]));

    /* Remove the second entity: iteration must skip the hole and stay
     * ascending by index. */
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, ids[1]));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 3u);

    u32 prev = 0;
    for (usize i = 0; i < 3; i++) {
        BreakEditorEntityId at_id;
        const char *at_name = NULL;
        ASSERT_TRUE(break_editor_doc_entity_at(doc, i, &at_id, &at_name));
        ASSERT_TRUE(at_id.index > prev || i == 0);
        prev = at_id.index;
        ASSERT_TRUE(at_name != NULL && at_name[0] != '\0');
    }
    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_FALSE(break_editor_doc_entity_at(doc, 3, &at_id, &at_name));

    break_editor_doc_destroy(doc);
}

TEST(dirty_flag_set_and_cleared) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "d");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    break_editor_doc_clear_dirty(doc); /* Task 2 save path clears via this */
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    ASSERT_TRUE(break_editor_doc_rename_entity(doc, id, "d2"));
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    break_editor_doc_destroy(doc);
}

TEST(oom_doc_create_sweep) {
    /* Doc create performs exactly 4 editor-owned allocations: doc struct,
     * name-slot block, stack struct, stack entry array. Budgets 0..3 must
     * fail with NULL (no leak); budget 4 is the first success. */
    for (u64 budget = 0; budget < 4; budget++) {
        break_editor_test_set_alloc_budget(budget);
        BreakEditorDoc *doc = break_editor_doc_create();
        break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
        ASSERT_TRUE(doc == NULL);
    }

    break_editor_test_set_alloc_budget(4);
    BreakEditorDoc *doc = break_editor_doc_create();
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_NOT_NULL(doc);
    break_editor_doc_destroy(doc);

    /* Ample budget always succeeds. */
    BreakEditorDoc *doc2 = break_editor_doc_create();
    ASSERT_NOT_NULL(doc2);
    break_editor_doc_destroy(doc2);
}

TEST(oom_remove_and_rename_command_alloc_fail_bounded) {
    /* Per-constructor injection: remove and rename allocate their command
     * objects only after the entity-exists check; budget 0 must fail both
     * bounded with the doc completely unchanged. */
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "target");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    break_editor_doc_clear_dirty(doc);

    break_editor_test_set_alloc_budget(0);
    bool removed = break_editor_doc_remove_entity(doc, id);
    bool renamed = break_editor_doc_rename_entity(doc, id, "other");
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_FALSE(removed);
    ASSERT_FALSE(renamed);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(id)));
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));
    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, "target");

    /* Recovery: both mutations succeed with the budget disabled. */
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, id, "other"));
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, id));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);

    break_editor_doc_destroy(doc);
}

TEST(oom_command_allocation_fails_bounded_doc_unchanged) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId keep = break_editor_doc_add_entity(doc, "keep");
    ASSERT_TRUE(break_editor_entity_id_valid(keep));
    break_editor_doc_clear_dirty(doc);

    break_editor_test_set_alloc_budget(0);
    BreakEditorEntityId bad = break_editor_doc_add_entity(doc, "nope");
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_FALSE(break_editor_entity_id_valid(bad));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    /* Recovery: with the budget disabled the same mutation succeeds. */
    BreakEditorEntityId ok = break_editor_doc_add_entity(doc, "nope");
    ASSERT_TRUE(break_editor_entity_id_valid(ok));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);

    break_editor_doc_destroy(doc);
}

TEST(null_doc_calls_fail_bounded) {
    ASSERT_FALSE(break_editor_entity_id_valid(
        break_editor_doc_add_entity(NULL, "x")));
    ASSERT_FALSE(break_editor_doc_remove_entity(NULL, BREAK_EDITOR_ENTITY_NULL));
    ASSERT_FALSE(break_editor_doc_rename_entity(NULL, BREAK_EDITOR_ENTITY_NULL,
                                                "x"));
    ASSERT_EQ(break_editor_doc_entity_count(NULL), 0u);
    ASSERT_FALSE(break_editor_doc_is_dirty(NULL));
    ASSERT_TRUE(break_editor_doc_world(NULL) == NULL);
    BreakEditorEntityId id;
    const char *name = NULL;
    ASSERT_FALSE(break_editor_doc_entity_at(NULL, 0, &id, &name));
}

int main(void) {
    printf("=== test_editor_doc ===\n");
    RUN_TEST(create_destroy_empty_doc);
    RUN_TEST(add_entity_basic);
    RUN_TEST(add_entity_null_name_generates_default);
    RUN_TEST(name_capacity_127_ok_128_rejected);
    RUN_TEST(rename_basic_and_stale_ids);
    RUN_TEST(remove_entity_basic_and_double_remove);
    RUN_TEST(entity_at_ascending_index_order);
    RUN_TEST(dirty_flag_set_and_cleared);
    RUN_TEST(oom_doc_create_sweep);
    RUN_TEST(oom_command_allocation_fails_bounded_doc_unchanged);
    RUN_TEST(oom_remove_and_rename_command_alloc_fail_bounded);
    RUN_TEST(null_doc_calls_fail_bounded);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n", g_test_pass,
           g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
