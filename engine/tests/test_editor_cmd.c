/* Stage 4 scene editor Phase 1 Task 1: BreakEditorCmdStack tests.
 *
 * Covers: bounded stack create/destroy, undo/redo semantics over the doc's
 * internal stack, the redo-after-undo SAME-id pin (the add command stores
 * the created id; revert destroys by id; redo re-creates and forcibly
 * restores the stored generation via the scene_serial mechanism,
 * scene_serial.c:1056-1064), drop-oldest overflow with the readable
 * dropped_oldest flag, redo-clear on new mutation, describe_last for the
 * status bar, and OOM injection on command allocation. */

#include "test_framework.h"

#include <editor/editor_doc.h>
#include <editor/editor_cmd.h>
#include <editor/editor_test_hooks.h>

#include <ecs/ecs.h>

#include <stdio.h>
#include <string.h>

static Entity to_ecs(BreakEditorEntityId id) {
    Entity e;
    e.index = id.index;
    e.generation = id.generation;
    return e;
}

static World *doc_world(BreakEditorDoc *doc) {
    return (World *)break_editor_doc_world(doc);
}

TEST(stack_create_destroy) {
    BreakEditorCmdStack *def = break_editor_cmd_stack_create(0);
    ASSERT_NOT_NULL(def);
    ASSERT_EQ(break_editor_cmd_stack_capacity(def), 256u);
    ASSERT_EQ(break_editor_cmd_stack_size(def), 0u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(def), 0u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count(def), 0u);
    ASSERT_FALSE(break_editor_cmd_stack_dropped_oldest(def));
    break_editor_cmd_stack_destroy(def);

    BreakEditorCmdStack *small = break_editor_cmd_stack_create(8);
    ASSERT_NOT_NULL(small);
    ASSERT_EQ(break_editor_cmd_stack_capacity(small), 8u);
    break_editor_cmd_stack_destroy(small);

    /* Over the documented hard cap: bounded NULL. */
    ASSERT_TRUE(break_editor_cmd_stack_create(1u << 20) == NULL);
    break_editor_cmd_stack_destroy(NULL); /* bounded no-op */
}

TEST(doc_stack_is_default_capacity) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    ASSERT_NOT_NULL(stack);
    ASSERT_EQ(break_editor_cmd_stack_capacity(stack), 256u);
    break_editor_doc_destroy(doc);
}

TEST(undo_redo_empty_stack) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_FALSE(break_editor_undo(doc));
    ASSERT_FALSE(break_editor_redo(doc));
    ASSERT_FALSE(break_editor_undo(NULL));
    ASSERT_FALSE(break_editor_redo(NULL));
    break_editor_doc_destroy(doc);
}

TEST(undo_add_removes_entity_and_frees_name) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "temp");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(id)));

    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_FALSE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_EQ(break_editor_cmd_stack_redo_count(break_editor_doc_stack(doc)),
              1u);

    break_editor_doc_destroy(doc);
}

TEST(redo_add_restores_same_id) {
    /* THE PIN: redo-after-undo must restore the SAME {index, generation}. */
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "pinned");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(id)));
    ASSERT_TRUE(break_editor_redo(doc));

    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(id)));
    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, id));
    ASSERT_STR_EQ(at_name, "pinned");

    /* Undo/redo once more: still the same id (generation forcing is stable
     * across repeated revert/redo cycles). */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, id));

    break_editor_doc_destroy(doc);
}

TEST(redo_restores_exact_ids_with_two_free_indices) {
    /* Pop-order pin with TWO indices on the free stack: undoing two
     * create-type commands pushes B's index then A's; redoing must pop in
     * LIFO order (A first) so each command's stored index matches. A
     * free-stack regression (LIFO -> FIFO) in ecs.c would make the first
     * redo pop B's index, hit the stored-index mismatch, and degrade redo
     * to bounded failure — this test fails on both the false return and
     * the id mismatch. */
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "b");
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_TRUE(break_editor_entity_id_valid(b));
    ASSERT_NEQ(a.index, b.index);

    ASSERT_TRUE(break_editor_undo(doc)); /* reverts add B: push b.index */
    ASSERT_TRUE(break_editor_undo(doc)); /* reverts add A: push a.index */
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(a)));
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(b)));
    ASSERT_EQ(break_editor_cmd_stack_redo_count(break_editor_doc_stack(doc)),
              2u);

    /* Redo A then B: BOTH must succeed with the EXACT original ids. */
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(a)));
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(b)));

    /* Doc contents and ascending-index iteration order match the original. */
    BreakEditorEntityId at0, at1;
    const char *name0 = NULL;
    const char *name1 = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at0, &name0));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 1, &at1, &name1));
    ASSERT_TRUE(at0.index < at1.index);
    if (a.index < b.index) {
        ASSERT_TRUE(break_editor_entity_id_eq(at0, a));
        ASSERT_TRUE(break_editor_entity_id_eq(at1, b));
        ASSERT_STR_EQ(name0, "a");
        ASSERT_STR_EQ(name1, "b");
    } else {
        ASSERT_TRUE(break_editor_entity_id_eq(at0, b));
        ASSERT_TRUE(break_editor_entity_id_eq(at1, a));
        ASSERT_STR_EQ(name0, "b");
        ASSERT_STR_EQ(name1, "a");
    }

    break_editor_doc_destroy(doc);
}

TEST(rename_remove_undo_chain_keeps_ids_exact) {
    /* Chain pin: rename X -> remove X -> undo(remove) -> undo(rename). The
     * remove-revert must restore X's exact generation, because the OLDER
     * rename command's stored id is only valid again if it does (its
     * defensive has_entity check compares generation). Then redo(rename),
     * redo(remove): renamed name applied, then entity gone. */
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId x = break_editor_doc_add_entity(doc, "before");
    ASSERT_TRUE(break_editor_entity_id_valid(x));
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, x, "after"));
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, x));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);

    BreakEditorEntityId at_id;
    const char *at_name = NULL;

    /* Undo remove: entity back with exact id and the post-rename name. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(x)));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, x));
    ASSERT_STR_EQ(at_name, "after");

    /* Undo rename: the older rename command's stored id must match the
     * restored entity exactly; final state equals the pre-rename name. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, x));
    ASSERT_STR_EQ(at_name, "before");

    /* Redo rename, redo remove: name applied, then entity gone. */
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, x));
    ASSERT_STR_EQ(at_name, "after");
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(x)));

    break_editor_doc_destroy(doc);
}

TEST(undo_remove_restores_id_and_name) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "keep");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, id));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(id)));

    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(id)));
    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, id));
    ASSERT_STR_EQ(at_name, "keep");

    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(id)));

    break_editor_doc_destroy(doc);
}

TEST(undo_redo_rename) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "before");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, id, "after"));

    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, "after");

    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, "before");

    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, "after");

    break_editor_doc_destroy(doc);
}

TEST(redo_cleared_on_new_mutation) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_cmd_stack_redo_count(break_editor_doc_stack(doc)),
              1u);

    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "b");
    ASSERT_TRUE(break_editor_entity_id_valid(b));
    ASSERT_EQ(break_editor_cmd_stack_redo_count(break_editor_doc_stack(doc)),
              0u);
    ASSERT_FALSE(break_editor_redo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);

    break_editor_doc_destroy(doc);
}

TEST(stack_overflow_drops_oldest_and_flags) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    ASSERT_NOT_NULL(stack);
    ASSERT_EQ(break_editor_cmd_stack_capacity(stack), 256u);

    BreakEditorEntityId first = BREAK_EDITOR_ENTITY_NULL;
    for (u32 i = 0; i < 257; i++) {
        char name[32];
        snprintf(name, sizeof(name), "bulk_%u", i);
        BreakEditorEntityId id = break_editor_doc_add_entity(doc, name);
        ASSERT_TRUE(break_editor_entity_id_valid(id));
        if (i == 0) first = id;
    }
    ASSERT_EQ(break_editor_doc_entity_count(doc), 257u);
    ASSERT_TRUE(break_editor_cmd_stack_dropped_oldest(stack));
    ASSERT_EQ(break_editor_cmd_stack_size(stack), 256u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), 256u);

    /* 256 undos revert adds 257..2; the first add's command was dropped, so
     * its entity survives. */
    for (u32 i = 0; i < 256; i++) ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_FALSE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);

    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, first));
    ASSERT_STR_EQ(at_name, "bulk_0");

    break_editor_doc_destroy(doc);
}

TEST(describe_last_command) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);

    char buf[128];
    ASSERT_FALSE(break_editor_cmd_stack_describe_last(stack, buf));

    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_cmd_stack_describe_last(stack, buf));
    ASSERT_TRUE(strstr(buf, "add") != NULL);
    ASSERT_TRUE(strstr(buf, "hero") != NULL);

    ASSERT_TRUE(break_editor_doc_rename_entity(doc, id, "villain"));
    ASSERT_TRUE(break_editor_cmd_stack_describe_last(stack, buf));
    ASSERT_TRUE(strstr(buf, "rename") != NULL);
    ASSERT_TRUE(strstr(buf, "before") == NULL); /* old name here is "hero" */
    ASSERT_TRUE(strstr(buf, "hero") != NULL);
    ASSERT_TRUE(strstr(buf, "villain") != NULL);

    /* After undoing both, nothing is applied: describe_last fails. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_FALSE(break_editor_cmd_stack_describe_last(stack, buf));

    break_editor_doc_destroy(doc);
}

TEST(oom_command_alloc_leaves_stack_unchanged) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);

    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_EQ(break_editor_cmd_stack_size(stack), 1u);

    break_editor_test_set_alloc_budget(0);
    BreakEditorEntityId bad = break_editor_doc_add_entity(doc, "b");
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_FALSE(break_editor_entity_id_valid(bad));
    ASSERT_EQ(break_editor_cmd_stack_size(stack), 1u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), 1u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count(stack), 0u);

    /* Undo/redo still operate on the surviving command. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_TRUE(break_editor_redo(doc));
    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, a));

    break_editor_doc_destroy(doc);
}

TEST(mixed_sequence_undo_redo) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "b");
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_TRUE(break_editor_entity_id_valid(b));
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, a, "a2"));
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, b));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);

    /* Undo remove: b back with same id and name. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(b)));

    /* Undo rename: a's display name reverts. */
    ASSERT_TRUE(break_editor_undo(doc));
    BreakEditorEntityId at_id;
    const char *at_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_TRUE(break_editor_entity_id_eq(at_id, a));
    ASSERT_STR_EQ(at_name, "a");

    /* Redo rename + remove. */
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &at_id, &at_name));
    ASSERT_STR_EQ(at_name, "a2");
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(b)));

    break_editor_doc_destroy(doc);
}

int main(void) {
    printf("=== test_editor_cmd ===\n");
    RUN_TEST(stack_create_destroy);
    RUN_TEST(doc_stack_is_default_capacity);
    RUN_TEST(undo_redo_empty_stack);
    RUN_TEST(undo_add_removes_entity_and_frees_name);
    RUN_TEST(redo_add_restores_same_id);
    RUN_TEST(redo_restores_exact_ids_with_two_free_indices);
    RUN_TEST(rename_remove_undo_chain_keeps_ids_exact);
    RUN_TEST(undo_remove_restores_id_and_name);
    RUN_TEST(undo_redo_rename);
    RUN_TEST(redo_cleared_on_new_mutation);
    RUN_TEST(stack_overflow_drops_oldest_and_flags);
    RUN_TEST(describe_last_command);
    RUN_TEST(oom_command_alloc_leaves_stack_unchanged);
    RUN_TEST(mixed_sequence_undo_redo);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n", g_test_pass,
           g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
