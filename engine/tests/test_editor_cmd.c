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
#include <editor/editor_components.h>
#include <editor/editor_internal.h>
#include <editor/editor_test_hooks.h>

#include <ecs/ecs.h>

#include <stdio.h>
#include <stdlib.h>
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

/* revision: strictly increases on every push, undo and redo (the doc's
 * change signal — dirty alone cannot tell "changed again since I looked"),
 * and stays put on failed undo/redo. */
TEST(revision_counts_every_change) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *st = break_editor_doc_stack(doc);
    u64 r0 = break_editor_cmd_stack_revision(st);
    ASSERT_FALSE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_cmd_stack_revision(st), r0);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    u64 r1 = break_editor_cmd_stack_revision(st);
    ASSERT_TRUE(r1 > r0);
    ASSERT_TRUE(break_editor_undo(doc));
    u64 r2 = break_editor_cmd_stack_revision(st);
    ASSERT_TRUE(r2 > r1);
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_cmd_stack_revision(st) > r2);
    ASSERT_EQ(break_editor_cmd_stack_revision(NULL), 0u);
    break_editor_doc_destroy(doc);
}


/* ---- origin-scoped undo/redo (per-client undo) ---- */

static const char *name_of(BreakEditorDoc *doc, BreakEditorEntityId id) {
    for (usize i = 0; i < break_editor_doc_entity_count(doc); i++) {
        BreakEditorEntityId at;
        const char *nm = NULL;
        if (break_editor_doc_entity_at(doc, i, &at, &nm) &&
            break_editor_entity_id_eq(at, id)) {
            return nm;
        }
    }
    return NULL;
}

TEST(origin_defaults_to_zero_and_is_settable) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_editor_doc_origin(doc), 0u);
    break_editor_doc_set_origin(doc, 7u);
    ASSERT_EQ(break_editor_doc_origin(doc), 7u);
    break_editor_doc_set_origin(doc, 0u);
    ASSERT_EQ(break_editor_doc_origin(doc), 0u);
    ASSERT_EQ(break_editor_doc_origin(NULL), 0u);
    break_editor_doc_set_origin(NULL, 3u); /* bounded no-op */
    break_editor_doc_destroy(doc);
}

TEST(origin_undo_reverts_only_own_independent_command) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *st = break_editor_doc_stack(doc);
    break_editor_doc_set_origin(doc, 1u);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    break_editor_doc_set_origin(doc, 2u);
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "b");
    break_editor_doc_set_origin(doc, 0u);
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_TRUE(break_editor_entity_id_valid(b));

    ASSERT_EQ(break_editor_cmd_stack_undo_count_origin(st, 1u), 1u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count_origin(st, 2u), 1u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count_origin(st, 3u), 0u);

    /* origin 1 undoes its own add even though origin 2 pushed after it */
    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(a)));
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(b)));
    ASSERT_STR_EQ(name_of(doc, b), "b");
    ASSERT_EQ(break_editor_cmd_stack_undo_count(st), 1u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count(st), 1u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count_origin(st, 1u), 0u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count_origin(st, 1u), 1u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count_origin(st, 2u), 0u);

    /* the global undo now reverts the one command left on the applied side */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_FALSE(world_entity_exists(doc_world(doc), to_ecs(b)));
    break_editor_doc_destroy(doc);
}

TEST(origin_undo_is_none_without_own_commands) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *st = break_editor_doc_stack(doc);
    ASSERT_EQ((int)break_editor_undo_origin(doc, 5u), (int)BREAK_EDITOR_ORIGIN_NONE);
    ASSERT_EQ((int)break_editor_redo_origin(doc, 5u), (int)BREAK_EDITOR_ORIGIN_NONE);
    break_editor_doc_set_origin(doc, 1u);
    ASSERT_TRUE(break_editor_entity_id_valid(break_editor_doc_add_entity(doc, "a")));
    break_editor_doc_set_origin(doc, 0u);
    u64 rev = break_editor_cmd_stack_revision(st);
    ASSERT_EQ((int)break_editor_undo_origin(doc, 5u), (int)BREAK_EDITOR_ORIGIN_NONE);
    ASSERT_EQ(break_editor_cmd_stack_revision(st), rev); /* nothing changed */
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_EQ((int)break_editor_undo_origin(NULL, 1u), (int)BREAK_EDITOR_ORIGIN_NONE);
    ASSERT_EQ((int)break_editor_redo_origin(NULL, 1u), (int)BREAK_EDITOR_ORIGIN_NONE);
    break_editor_doc_destroy(doc);
}

TEST(origin_undo_blocked_by_later_foreign_command_on_same_entity) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_set_origin(doc, 1u);
    BreakEditorEntityId e = break_editor_doc_add_entity(doc, "e");
    break_editor_doc_set_origin(doc, 2u);
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, e, "renamed"));
    break_editor_doc_set_origin(doc, 0u);

    /* origin 1 cannot pull its add out from under origin 2's rename */
    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_BLOCKED);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_STR_EQ(name_of(doc, e), "renamed");
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc)), 2u);

    /* origin 2 can undo its own rename (the add before it is origin 1's) */
    ASSERT_EQ((int)break_editor_undo_origin(doc, 2u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_STR_EQ(name_of(doc, e), "e");

    /* ... but the undone rename still waits on the redo side and touches e,
     * so origin 1 stays blocked until that command is gone */
    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_BLOCKED);
    ASSERT_EQ((int)break_editor_redo_origin(doc, 2u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_STR_EQ(name_of(doc, e), "renamed");
    break_editor_doc_destroy(doc);
}

TEST(origin_undo_redo_roundtrip_keeps_ids_and_other_clients_edits) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *st = break_editor_doc_stack(doc);
    BreakEditorEntityId e1 = break_editor_doc_add_entity(doc, "one");
    BreakEditorEntityId e2 = break_editor_doc_add_entity(doc, "two");
    break_editor_doc_set_origin(doc, 1u);
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, e1, "one-by-1"));
    break_editor_doc_set_origin(doc, 2u);
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, e2, "two-by-2"));
    break_editor_doc_set_origin(doc, 0u);

    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_STR_EQ(name_of(doc, e1), "one");
    ASSERT_STR_EQ(name_of(doc, e2), "two-by-2"); /* the other client's edit stays */
    ASSERT_EQ(break_editor_cmd_stack_undo_count(st), 3u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count(st), 1u);

    ASSERT_EQ((int)break_editor_redo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_STR_EQ(name_of(doc, e1), "one-by-1");
    ASSERT_STR_EQ(name_of(doc, e2), "two-by-2");
    ASSERT_EQ(break_editor_cmd_stack_undo_count(st), 4u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count(st), 0u);
    ASSERT_EQ((int)break_editor_redo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_NONE);

    /* ids stayed exact through the move */
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(e1)));
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(e2)));
    break_editor_doc_destroy(doc);
}

TEST(origin_undo_set_field_touches_only_that_entity) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "b");
    ASSERT_TRUE(break_editor_doc_add_component(doc, a, BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_add_component(doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM));
    break_editor_doc_set_origin(doc, 1u);
    ASSERT_TRUE(break_editor_doc_set_field_f32(doc, a, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, 5.0f));
    break_editor_doc_set_origin(doc, 2u);
    ASSERT_TRUE(break_editor_doc_set_field_f32(doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, 9.0f));
    break_editor_doc_set_origin(doc, 0u);

    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    f32 v = -1.0f;
    ASSERT_TRUE(break_editor_doc_get_field_f32(doc, a, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &v));
    ASSERT_TRUE(v == 0.0f);
    ASSERT_TRUE(break_editor_doc_get_field_f32(doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &v));
    ASSERT_TRUE(v == 9.0f);

    /* a second edit by origin 2 on the SAME entity as origin 1's: blocked */
    break_editor_doc_set_origin(doc, 1u);
    ASSERT_TRUE(break_editor_doc_set_field_f32(doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM, 1u, 3.0f));
    break_editor_doc_set_origin(doc, 2u);
    ASSERT_TRUE(break_editor_doc_set_field_f32(doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM, 2u, 4.0f));
    break_editor_doc_set_origin(doc, 0u);
    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_BLOCKED);
    ASSERT_TRUE(break_editor_doc_get_field_f32(doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM, 1u, &v));
    ASSERT_TRUE(v == 3.0f);
    break_editor_doc_destroy(doc);
}

TEST(origin_is_inherited_by_group_commands_and_group_conflicts_are_checked) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId ids[2];
    ids[0] = break_editor_doc_add_entity(doc, "g0");
    ids[1] = break_editor_doc_add_entity(doc, "g1");
    BreakEditorEntityId other = break_editor_doc_add_entity(doc, "other");

    break_editor_doc_set_origin(doc, 3u);
    ASSERT_EQ(break_editor_doc_remove_entities(doc, ids, 2u), 2u); /* one group command */
    break_editor_doc_set_origin(doc, 4u);
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, other, "other2"));
    break_editor_doc_set_origin(doc, 0u);

    BreakEditorCmdStack *st = break_editor_doc_stack(doc);
    ASSERT_EQ(break_editor_cmd_stack_undo_count_origin(st, 3u), 1u);
    /* independent of origin 4's rename of a different entity: both come back */
    ASSERT_EQ((int)break_editor_undo_origin(doc, 3u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 3u);
    ASSERT_STR_EQ(name_of(doc, ids[0]), "g0");
    ASSERT_STR_EQ(name_of(doc, ids[1]), "g1");
    ASSERT_STR_EQ(name_of(doc, other), "other2");

    /* now origin 4 renames a member of a group that origin 3 removes */
    ASSERT_EQ((int)break_editor_redo_origin(doc, 3u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    break_editor_doc_destroy(doc);

    doc = break_editor_doc_create();
    ids[0] = break_editor_doc_add_entity(doc, "m0");
    ids[1] = break_editor_doc_add_entity(doc, "m1");
    break_editor_doc_set_origin(doc, 3u);
    ASSERT_EQ(break_editor_doc_duplicate_entities(doc, ids, 2u, (BreakEditorEntityId[2]){0}), 2u);
    break_editor_doc_set_origin(doc, 4u);
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, ids[1], "m1-renamed"));
    break_editor_doc_set_origin(doc, 0u);
    /* origin 4's rename touches the SOURCE m1, not a duplicate: independent */
    ASSERT_EQ((int)break_editor_undo_origin(doc, 3u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    break_editor_doc_destroy(doc);
}

TEST(origin_redo_of_structural_commands_is_bounded_when_free_list_order_differs) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_set_origin(doc, 1u);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "A");
    break_editor_doc_set_origin(doc, 2u);
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "B");
    break_editor_doc_set_origin(doc, 0u);
    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ((int)break_editor_undo_origin(doc, 2u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);

    /* The ECS hands indices back LIFO, so re-creating A's exact id first
     * cannot work (B's index is on top). The attempt must fail bounded and
     * leave the document and the stack as they were ... */
    BreakEditorCmdStack *st = break_editor_doc_stack(doc);
    u64 rev = break_editor_cmd_stack_revision(st);
    ASSERT_EQ((int)break_editor_redo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_BLOCKED);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_EQ(break_editor_cmd_stack_revision(st), rev);
    ASSERT_EQ(break_editor_cmd_stack_redo_count(st), 2u);

    /* ... and redoing in the order the free list allows restores both with
     * their exact ids. */
    ASSERT_EQ((int)break_editor_redo_origin(doc, 2u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ((int)break_editor_redo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(a)));
    ASSERT_TRUE(world_entity_exists(doc_world(doc), to_ecs(b)));
    ASSERT_STR_EQ(name_of(doc, a), "A");
    ASSERT_STR_EQ(name_of(doc, b), "B");
    break_editor_doc_destroy(doc);
}

TEST(origin_survives_drop_oldest_and_new_push_clears_the_redo_tail) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *st = break_editor_doc_stack(doc);
    BreakEditorEntityId e = break_editor_doc_add_entity(doc, "e");
    break_editor_doc_set_origin(doc, 1u);
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, e, "x1"));
    break_editor_doc_set_origin(doc, 2u);
    BreakEditorEntityId f = break_editor_doc_add_entity(doc, "f");
    break_editor_doc_set_origin(doc, 0u);
    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ(break_editor_cmd_stack_redo_count_origin(st, 1u), 1u);
    /* any new mutation clears the redo tail, including an origin's undone command */
    break_editor_doc_set_origin(doc, 2u);
    ASSERT_TRUE(break_editor_doc_rename_entity(doc, f, "f2"));
    break_editor_doc_set_origin(doc, 0u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count_origin(st, 1u), 0u);
    ASSERT_EQ((int)break_editor_redo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_NONE);
    break_editor_doc_destroy(doc);
}

TEST(origin_redo_blocked_by_earlier_undone_foreign_command_on_same_entity) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId e = break_editor_doc_add_entity(doc, "e");
    ASSERT_TRUE(break_editor_doc_add_component(doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM));
    break_editor_doc_set_origin(doc, 1u);
    ASSERT_TRUE(break_editor_doc_set_field_f32(doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, 5.0f));
    break_editor_doc_set_origin(doc, 2u);
    ASSERT_TRUE(break_editor_doc_set_field_f32(doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 1u, 6.0f));
    break_editor_doc_set_origin(doc, 0u);
    ASSERT_TRUE(break_editor_undo(doc)); /* origin 2's edit */
    ASSERT_TRUE(break_editor_undo(doc)); /* origin 1's edit */
    BreakEditorCmdStack *st = break_editor_doc_stack(doc);
    u64 rev = break_editor_cmd_stack_revision(st);

    /* origin 2 would jump over origin 1's undone edit of the same entity */
    ASSERT_EQ((int)break_editor_redo_origin(doc, 2u), (int)BREAK_EDITOR_ORIGIN_BLOCKED);
    f32 v = -1.0f;
    ASSERT_TRUE(break_editor_doc_get_field_f32(doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 1u, &v));
    ASSERT_TRUE(v == 0.0f);
    ASSERT_EQ(break_editor_cmd_stack_revision(st), rev);

    /* in stack order it works */
    ASSERT_EQ((int)break_editor_redo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ((int)break_editor_redo_origin(doc, 2u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_TRUE(break_editor_doc_get_field_f32(doc, e, BREAK_EDITOR_COMPONENT_TRANSFORM, 1u, &v));
    ASSERT_TRUE(v == 6.0f);
    break_editor_doc_destroy(doc);
}

static bool opaque_apply(BreakEditorCmd *self, BreakEditorDoc *doc) { (void)self; (void)doc; return true; }
static void opaque_destroy(BreakEditorCmd *self) { free(self); }
static void opaque_describe(const BreakEditorCmd *self, char buf[128]) { (void)self; snprintf(buf, 128, "opaque"); }

TEST(origin_command_without_a_touch_set_conflicts_with_everything) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_set_origin(doc, 1u);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    /* a foreign command that cannot say what it touches (touched == NULL) */
    BreakEditorCmd *opaque = calloc(1u, sizeof(*opaque));
    ASSERT_NOT_NULL(opaque);
    opaque->apply = opaque_apply;
    opaque->revert = opaque_apply;
    opaque->destroy = opaque_destroy;
    opaque->describe = opaque_describe;
    break_editor_doc_set_origin(doc, 2u);
    break_editor_cmd_stack_push_applied(doc, opaque);
    break_editor_doc_set_origin(doc, 0u);

    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_BLOCKED);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    /* and the opaque command itself can be undone by its own origin */
    ASSERT_EQ((int)break_editor_undo_origin(doc, 2u), (int)BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ((int)break_editor_undo_origin(doc, 1u), (int)BREAK_EDITOR_ORIGIN_BLOCKED);
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
    RUN_TEST(revision_counts_every_change);
    RUN_TEST(origin_defaults_to_zero_and_is_settable);
    RUN_TEST(origin_undo_reverts_only_own_independent_command);
    RUN_TEST(origin_undo_is_none_without_own_commands);
    RUN_TEST(origin_undo_blocked_by_later_foreign_command_on_same_entity);
    RUN_TEST(origin_undo_redo_roundtrip_keeps_ids_and_other_clients_edits);
    RUN_TEST(origin_undo_set_field_touches_only_that_entity);
    RUN_TEST(origin_is_inherited_by_group_commands_and_group_conflicts_are_checked);
    RUN_TEST(origin_redo_of_structural_commands_is_bounded_when_free_list_order_differs);
    RUN_TEST(origin_survives_drop_oldest_and_new_push_clears_the_redo_tail);
    RUN_TEST(origin_redo_blocked_by_earlier_undone_foreign_command_on_same_entity);
    RUN_TEST(origin_command_without_a_touch_set_conflicts_with_everything);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n", g_test_pass,
           g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
