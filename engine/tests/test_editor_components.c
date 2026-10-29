/* Stage 4 scene editor Phase 1 Task 3: editor component registry + inspector
 * data model tests.
 *
 * Covers the brief checkboxes: registry enumeration (exactly the registered
 * editable types, bounded), has/get/set field f32 (zeroed on add, byte-exact
 * reads), set via command -> undo restores the previous 4 bytes exactly (and
 * redo restores the new ones), add/remove component undoable with the
 * component bytes snapshotted into the command (<= 256 byte cap), unregistered
 * component id -> bounded false with the doc unchanged, field index OOB ->
 * false, break_editor_parse_f32 strictness (bounded 64-byte input; empty /
 * overflow / trailing garbage rejected; locale-independent '.'), and the
 * EditorTransform component bytes round-tripping through BSCN save/load
 * (scene_serial COMPONENTS chunk stores raw bytes per registered type). */

#include "test_framework.h"

#include <editor/editor_doc.h>
#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_scene.h>
#include <editor/editor_test_hooks.h>

#include <ecs/ecs.h>

#include <float.h>
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

static u32 f32_bits(f32 v) {
    u32 b;
    memcpy(&b, &v, sizeof(b));
    return b;
}

static f32 bits_f32(u32 b) {
    f32 v;
    memcpy(&v, &b, sizeof(v));
    return v;
}

static const EditorTransform *raw_transform(BreakEditorDoc *doc,
                                            BreakEditorEntityId id) {
    return (const EditorTransform *)world_get_component(
        doc_world(doc), to_ecs(id), BREAK_EDITOR_COMPONENT_TRANSFORM);
}

/* Fills the transform with distinctive per-field values base+i (i = field
 * index 0..8) through the public set_field API. */
static bool set_all_fields(BreakEditorDoc *doc, BreakEditorEntityId id,
                           f32 base) {
    for (u32 f = 0; f < 9; f++) {
        if (!break_editor_doc_set_field_f32(
                doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, f,
                base + (f32)f)) {
            return false;
        }
    }
    return true;
}

static bool fields_match(BreakEditorDoc *doc, BreakEditorEntityId id,
                         f32 base) {
    for (u32 f = 0; f < 9; f++) {
        f32 v = 0.0f;
        if (!break_editor_doc_get_field_f32(doc, id,
                                            BREAK_EDITOR_COMPONENT_TRANSFORM,
                                            f, &v)) {
            return false;
        }
        if (f32_bits(v) != f32_bits(base + (f32)f)) return false;
    }
    return true;
}

/* All 9 fields exactly +0.0f (the zeroed-add state). */
/* A freshly added transform: pos/rot exactly zero, scale exactly one. */
static bool fields_default(BreakEditorDoc *doc, BreakEditorEntityId id) {
    for (u32 f = 0; f < 9; f++) {
        f32 v = -1.0f;
        if (!break_editor_doc_get_field_f32(doc, id,
                                            BREAK_EDITOR_COMPONENT_TRANSFORM,
                                            f, &v)) {
            return false;
        }
        if (f < 6u ? f32_bits(v) != 0u : v != 1.0f) return false;
    }
    return true;
}

TEST(registry_enumeration) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);

    /* Exactly one editable type registered at create: the transform. */
    ASSERT_EQ(break_editor_doc_component_count(doc), 1u);

    BreakEditorComponentInfo info;
    memset(&info, 0xAB, sizeof(info));
    ASSERT_TRUE(break_editor_doc_component_info(doc, 0, &info));
    ASSERT_EQ(info.component_id, BREAK_EDITOR_COMPONENT_TRANSFORM);
    ASSERT_STR_EQ(info.display_name, "Transform");
    ASSERT_EQ(info.field_count, 9u);

    static const char *const want_names[9] = {
        "pos.x",   "pos.y",   "pos.z",
        "rot.x",   "rot.y",   "rot.z",
        "scale.x", "scale.y", "scale.z",
    };
    for (u32 f = 0; f < 9; f++) {
        ASSERT_STR_EQ(info.fields[f].name, want_names[f]);
        /* Column f is pos[f], rot[f-3] or scale[f-6]: each f32 slot. */
        ASSERT_EQ(info.fields[f].offset, (u32)(f * sizeof(f32)));
        ASSERT_EQ(info.fields[f].type, 0u); /* 0 = f32 */
    }

    /* Past the registered count: bounded false, out untouched. */
    memset(&info, 0xAB, sizeof(info));
    ASSERT_FALSE(break_editor_doc_component_info(doc, 1, &info));
    ASSERT_EQ((u8)info.component_id, 0xABu);
    ASSERT_FALSE(break_editor_doc_component_info(doc, 1000, &info));
    ASSERT_FALSE(break_editor_doc_component_info(doc, 0, NULL));

    /* NULL doc: bounded. */
    ASSERT_EQ(break_editor_doc_component_count(NULL), 0u);
    ASSERT_FALSE(break_editor_doc_component_info(NULL, 0, &info));

    break_editor_doc_destroy(doc);
}

TEST(transform_registered_in_world_at_create) {
    /* The documented free id 64 (< ECS_MAX_COMPONENTS 128; the engine demo
     * uses 1..3, in-repo tests use small ids) must be live in the doc World
     * with the exact EditorTransform size — this is also what makes BSCN
     * save/load carry the payload (editor_scene.c re-registers the doc's
     * component set into the staging world on load). */
    ASSERT_EQ(BREAK_EDITOR_COMPONENT_TRANSFORM, 64u);
    ASSERT_EQ(sizeof(EditorTransform), 36u);

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(doc_world(doc)->component_sizes[BREAK_EDITOR_COMPONENT_TRANSFORM],
              (u32)sizeof(EditorTransform));
    break_editor_doc_destroy(doc);
}

TEST(has_component_and_default_add) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));

    /* Registered but not yet added. */
    ASSERT_FALSE(break_editor_doc_has_component(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM));
    /* Unregistered id: bounded false. */
    ASSERT_FALSE(break_editor_doc_has_component(doc, id, 7u));
    /* Stale/invalid entity: bounded false. */
    ASSERT_FALSE(break_editor_doc_has_component(
        doc, BREAK_EDITOR_ENTITY_NULL, BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_FALSE(break_editor_doc_has_component(
        NULL, id, BREAK_EDITOR_COMPONENT_TRANSFORM));

    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));

    /* Add yields the registered DEFAULT bytes, deterministically (the ECS
     * reuses chunk rows, so stale bytes must be overwritten). For
     * EditorTransform that is the identity: pos 0, rot 0, scale 1 — a
     * zeroed scale made every new proxy invisible and un-scalable. */
    const EditorTransform *t = raw_transform(doc, id);
    ASSERT_NOT_NULL(t);
    for (u32 i = 0; i < 6; i++) {
        ASSERT_EQ(f32_bits(((const f32 *)t)[i]), 0u);
    }
    for (u32 i = 6; i < 9; i++) {
        ASSERT_TRUE(((const f32 *)t)[i] == 1.0f);
    }

    break_editor_doc_destroy(doc);
}

TEST(get_set_fields_round_trip) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));

    ASSERT_TRUE(fields_default(doc, id));
    ASSERT_TRUE(set_all_fields(doc, id, 100.0f));
    ASSERT_TRUE(fields_match(doc, id, 100.0f));

    /* Cross-check against the raw ECS bytes through the borrowed World. */
    const EditorTransform *t = raw_transform(doc, id);
    ASSERT_NOT_NULL(t);
    ASSERT_EQ(f32_bits(t->pos[0]), f32_bits(100.0f));
    ASSERT_EQ(f32_bits(t->rot[2]), f32_bits(105.0f));
    ASSERT_EQ(f32_bits(t->scale[2]), f32_bits(108.0f));

    /* NULL out pointer: bounded false. */
    ASSERT_FALSE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, NULL));

    break_editor_doc_destroy(doc);
}

TEST(set_field_undo_redo_byte_exact) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));

    /* Distinctive non-zero bit pattern, then a second one, including the
     * -0.0f vs +0.0f distinction (bitwise different, numerically equal). */
    const u32 first = 0x3FC00001u;  /* ~1.5000001f */
    const u32 second = 0x80000000u; /* -0.0f */

    f32 v = 1.0f;
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, bits_f32(first)));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), first);

    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, bits_f32(second)));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), second);

    /* Undo restores the previous 4 bytes exactly; twice more to zero. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), first);
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), 0u); /* +0.0f, NOT the -0.0f bit pattern */

    /* Redo restores the newer bytes exactly, in order. */
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), first);
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), second);

    break_editor_doc_destroy(doc);
}

TEST(set_field_same_value_records_no_command) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    u32 size_before = break_editor_cmd_stack_size(stack);
    break_editor_doc_clear_dirty(doc);

    /* Bitwise-identical write: success, but no command, no dirty. */
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, 0.0f));
    ASSERT_EQ(break_editor_cmd_stack_size(stack), size_before);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    /* Numerically equal but bitwise different (-0.0f over +0.0f): recorded. */
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, -0.0f));
    ASSERT_EQ(break_editor_cmd_stack_size(stack), size_before + 1u);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    f32 v = 0.0f;
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), 0x80000000u);

    break_editor_doc_destroy(doc);
}

TEST(set_field_bounded_failures_leave_doc_unchanged) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    BreakEditorEntityId bare = break_editor_doc_add_entity(doc, "bare");
    ASSERT_TRUE(break_editor_entity_id_valid(bare));
    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    u32 size_before = break_editor_cmd_stack_size(stack);
    break_editor_doc_clear_dirty(doc);

    /* Unregistered component id (7 is not in the editor registry). */
    ASSERT_FALSE(break_editor_doc_set_field_f32(doc, id, 7u, 0, 1.0f));
    /* Field index out of bounds (registry has 9 fields). */
    ASSERT_FALSE(break_editor_doc_set_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 9u, 1.0f));
    ASSERT_FALSE(break_editor_doc_set_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 1000u, 1.0f));
    /* Entity does not have the component. */
    ASSERT_FALSE(break_editor_doc_set_field_f32(
        doc, bare, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, 1.0f));
    /* Invalid / stale entity ids. */
    ASSERT_FALSE(break_editor_doc_set_field_f32(
        doc, BREAK_EDITOR_ENTITY_NULL, BREAK_EDITOR_COMPONENT_TRANSFORM, 0,
        1.0f));
    BreakEditorEntityId stale = {12345u, 1u};
    ASSERT_FALSE(break_editor_doc_set_field_f32(
        doc, stale, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, 1.0f));
    /* NULL doc. */
    ASSERT_FALSE(break_editor_doc_set_field_f32(
        NULL, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, 1.0f));

    /* get_field shares the validation surface. */
    f32 v = 77.0f;
    ASSERT_FALSE(break_editor_doc_get_field_f32(doc, id, 7u, 0, &v));
    ASSERT_FALSE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 9u, &v));
    ASSERT_FALSE(break_editor_doc_get_field_f32(
        doc, bare, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), f32_bits(77.0f)); /* out untouched on failure */

    /* Nothing changed: no commands pushed, dirty still clear, value zero. */
    ASSERT_EQ(break_editor_cmd_stack_size(stack), size_before);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), 0u);

    break_editor_doc_destroy(doc);
}

TEST(add_component_undo_redo_symmetric) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));

    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    /* Undo removes; redo re-adds with the snapshot (zeroed) bytes. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_FALSE(break_editor_doc_has_component(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(fields_default(doc, id));

    /* Full chain: set field, undo set, undo add, redo add (zeroed), redo
     * set — every step exact. */
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 4, 42.5f));
    ASSERT_TRUE(break_editor_undo(doc)); /* undo set */
    f32 v = 1.0f;
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 4, &v));
    ASSERT_EQ(f32_bits(v), 0u);
    ASSERT_TRUE(break_editor_undo(doc)); /* undo add */
    ASSERT_FALSE(break_editor_doc_has_component(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_redo(doc)); /* redo add: zeroed, not 42.5 */
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 4, &v));
    ASSERT_EQ(f32_bits(v), 0u);
    ASSERT_TRUE(break_editor_redo(doc)); /* redo set */
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 4, &v));
    ASSERT_EQ(f32_bits(v), f32_bits(42.5f));

    break_editor_doc_destroy(doc);
}

TEST(remove_component_undo_restores_byte_snapshot) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(set_all_fields(doc, id, 7.25f));

    /* Byte snapshot before removal for an exact comparison. */
    EditorTransform before;
    const EditorTransform *t = raw_transform(doc, id);
    ASSERT_NOT_NULL(t);
    memcpy(&before, t, sizeof(before));

    ASSERT_TRUE(break_editor_doc_remove_component(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_FALSE(break_editor_doc_has_component(doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));

    /* Undo: component back with the snapshotted bytes, byte-exact. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    t = raw_transform(doc, id);
    ASSERT_NOT_NULL(t);
    ASSERT_EQ(memcmp(&before, t, sizeof(before)), 0);
    ASSERT_TRUE(fields_match(doc, id, 7.25f));

    /* Redo: removed again; second undo still byte-exact. */
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_FALSE(break_editor_doc_has_component(doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_undo(doc));
    t = raw_transform(doc, id);
    ASSERT_NOT_NULL(t);
    ASSERT_EQ(memcmp(&before, t, sizeof(before)), 0);

    break_editor_doc_destroy(doc);
}

/* Undoing remove_entity restores the entity WITH its components, byte-exact
 * (was: id + name only — the transform silently vanished on undo). Redo
 * removes it again; a second undo restores the same bytes. */
TEST(remove_entity_undo_restores_components) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(set_all_fields(doc, id, 3.5f));
    EditorTransform before;
    const EditorTransform *t = raw_transform(doc, id);
    ASSERT_NOT_NULL(t);
    memcpy(&before, t, sizeof(before));

    ASSERT_TRUE(break_editor_doc_remove_entity(doc, id));
    ASSERT_FALSE(break_editor_doc_has_component(doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    t = raw_transform(doc, id);
    ASSERT_NOT_NULL(t);
    ASSERT_EQ(memcmp(&before, t, sizeof(before)), 0);
    ASSERT_TRUE(fields_match(doc, id, 3.5f));

    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_FALSE(break_editor_doc_has_component(doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_undo(doc));
    t = raw_transform(doc, id);
    ASSERT_NOT_NULL(t);
    ASSERT_EQ(memcmp(&before, t, sizeof(before)), 0);

    /* an entity with no components still round-trips (nothing to restore) */
    {
        BreakEditorEntityId bare = break_editor_doc_add_entity(doc, "bare");
        ASSERT_TRUE(break_editor_doc_remove_entity(doc, bare));
        ASSERT_TRUE(break_editor_undo(doc));
        ASSERT_FALSE(break_editor_doc_has_component(
            doc, bare, BREAK_EDITOR_COMPONENT_TRANSFORM));
    }
    break_editor_doc_destroy(doc);
}

/* Duplicate: one undoable command creates a new entity named "<name> copy"
 * with byte-exact copies of every registered component. Undo removes the
 * copy; redo restores the same id with the same bytes. */
TEST(duplicate_entity_copies_components_in_one_command) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId src = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_doc_add_component(doc, src,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(set_all_fields(doc, src, 4.5f));
    u32 depth = break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc));

    BreakEditorEntityId dup = break_editor_doc_duplicate_entity(doc, src);
    ASSERT_TRUE(break_editor_entity_id_valid(dup));
    ASSERT_FALSE(break_editor_entity_id_eq(dup, src));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc)),
              depth + 1u);
    ASSERT_TRUE(fields_match(doc, dup, 4.5f));
    {
        BreakEditorEntityId id;
        const char *name = NULL;
        ASSERT_TRUE(break_editor_doc_entity_at(doc, 1u, &id, &name));
        ASSERT_TRUE(break_editor_entity_id_eq(id, dup));
        ASSERT_STR_EQ(name, "hero copy");
    }
    /* the copy is independent of the source */
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, dup, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, 9.0f));
    ASSERT_TRUE(fields_match(doc, src, 4.5f));
    ASSERT_TRUE(break_editor_undo(doc)); /* the field edit */
    ASSERT_TRUE(break_editor_undo(doc)); /* the duplicate */
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    ASSERT_TRUE(fields_match(doc, dup, 4.5f));

    /* bounded: stale id, NULL doc; an over-long copy name still fits (the
     * suffix is dropped rather than truncating the source name) */
    ASSERT_FALSE(break_editor_entity_id_valid(
        break_editor_doc_duplicate_entity(NULL, src)));
    {
        BreakEditorEntityId gone = break_editor_doc_add_entity(doc, "gone");
        ASSERT_TRUE(break_editor_doc_remove_entity(doc, gone));
        ASSERT_FALSE(break_editor_entity_id_valid(
            break_editor_doc_duplicate_entity(doc, gone)));
    }
    {
        char longname[BREAK_EDITOR_NAME_CAPACITY];
        memset(longname, 'n', sizeof(longname) - 1u);
        longname[sizeof(longname) - 1u] = '\0';
        BreakEditorEntityId l = break_editor_doc_add_entity(doc, longname);
        ASSERT_TRUE(break_editor_entity_id_valid(l));
        BreakEditorEntityId lc = break_editor_doc_duplicate_entity(doc, l);
        ASSERT_TRUE(break_editor_entity_id_valid(lc));
    }
    break_editor_doc_destroy(doc);
}

/* Removing several entities is ONE undoable command: undo brings all of
 * them back (ids, names, components), redo removes all again. Stale or
 * duplicate ids in the list are skipped; an all-stale list is a bounded
 * false with nothing recorded. */
TEST(remove_entities_is_one_command) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "b");
    BreakEditorEntityId c = break_editor_doc_add_entity(doc, "c");
    ASSERT_TRUE(break_editor_doc_add_component(doc, b,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, 7.0f));
    u32 depth = break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc));
    BreakEditorEntityId ids[4] = {a, b, a, BREAK_EDITOR_ENTITY_NULL};
    ASSERT_EQ(break_editor_doc_remove_entities(doc, ids, 4u), 2u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc)),
              depth + 1u);
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 3u);
    {
        f32 x = 0.0f;
        ASSERT_TRUE(break_editor_doc_get_field_f32(
            doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &x));
        ASSERT_TRUE(x == 7.0f);
        BreakEditorEntityId id;
        const char *name = NULL;
        ASSERT_TRUE(break_editor_doc_entity_at(doc, 0u, &id, &name));
        ASSERT_STR_EQ(name, "a");
    }
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    /* nothing removable: bounded, no command */
    depth = break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc));
    ASSERT_EQ(break_editor_doc_remove_entities(doc, ids, 2u), 0u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc)), depth);
    ASSERT_EQ(break_editor_doc_remove_entities(NULL, ids, 2u), 0u);
    ASSERT_EQ(break_editor_doc_remove_entities(doc, NULL, 2u), 0u);
    (void)c;
    break_editor_doc_destroy(doc);
}

/* Duplicating several entities is ONE undoable command; out[] receives the
 * copies in input order. Stale and repeated ids are skipped. */
TEST(duplicate_entities_is_one_command) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "b");
    ASSERT_TRUE(break_editor_doc_add_component(doc, b,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, 3.0f));
    u32 depth = break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc));
    BreakEditorEntityId ids[3] = {a, b, a};
    BreakEditorEntityId out[3];
    ASSERT_EQ(break_editor_doc_duplicate_entities(doc, ids, 3u, out), 2u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 4u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc)),
              depth + 1u);
    {
        BreakEditorEntityId id;
        const char *name = NULL;
        f32 x = 0.0f;
        ASSERT_TRUE(break_editor_doc_entity_at(doc, 2u, &id, &name));
        ASSERT_TRUE(break_editor_entity_id_eq(id, out[0]));
        ASSERT_STR_EQ(name, "a copy");
        ASSERT_TRUE(break_editor_doc_entity_at(doc, 3u, &id, &name));
        ASSERT_TRUE(break_editor_entity_id_eq(id, out[1]));
        ASSERT_STR_EQ(name, "b copy");
        ASSERT_TRUE(break_editor_doc_get_field_f32(
            doc, out[1], BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &x));
        ASSERT_TRUE(x == 3.0f);
    }
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 4u);
    {
        f32 x = 0.0f;
        ASSERT_TRUE(break_editor_doc_get_field_f32(
            doc, out[1], BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &x));
        ASSERT_TRUE(x == 3.0f);
    }
    /* nothing to copy / bad args: no command */
    depth = break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc));
    {
        BreakEditorEntityId none = BREAK_EDITOR_ENTITY_NULL;
        ASSERT_EQ(break_editor_doc_duplicate_entities(doc, &none, 1u, out), 0u);
    }
    ASSERT_EQ(break_editor_doc_duplicate_entities(NULL, ids, 2u, out), 0u);
    ASSERT_EQ(break_editor_doc_duplicate_entities(doc, NULL, 2u, out), 0u);
    ASSERT_EQ(break_editor_doc_duplicate_entities(doc, ids, 2u, NULL), 0u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc)), depth);
    break_editor_doc_destroy(doc);
}

/* reset: an empty, clean document with no history; components still work */
TEST(reset_empties_the_document) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "a");
    ASSERT_TRUE(break_editor_doc_add_component(doc, a,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    ASSERT_TRUE(break_editor_doc_reset(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc)), 0u);
    ASSERT_FALSE(break_editor_undo(doc));
    /* the old id is gone; new entities and components behave normally */
    ASSERT_FALSE(break_editor_doc_has_component(doc, a,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "b");
    ASSERT_TRUE(break_editor_entity_id_valid(b));
    ASSERT_TRUE(break_editor_doc_add_component(doc, b,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, b, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, 2.0f));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_FALSE(break_editor_doc_reset(NULL));
    break_editor_doc_destroy(doc);
}

TEST(add_remove_component_bounded_failures) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    u32 size_before = break_editor_cmd_stack_size(stack);

    /* Adding an existing component: bounded false. */
    ASSERT_FALSE(break_editor_doc_add_component(doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    /* Unregistered id: bounded false for both. */
    ASSERT_FALSE(break_editor_doc_add_component(doc, id, 7u));
    ASSERT_FALSE(break_editor_doc_remove_component(doc, id, 7u));
    /* Invalid entity. */
    ASSERT_FALSE(break_editor_doc_add_component(
        doc, BREAK_EDITOR_ENTITY_NULL, BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_FALSE(break_editor_doc_remove_component(
        doc, BREAK_EDITOR_ENTITY_NULL, BREAK_EDITOR_COMPONENT_TRANSFORM));
    /* NULL doc. */
    ASSERT_FALSE(break_editor_doc_add_component(NULL, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_FALSE(break_editor_doc_remove_component(NULL, id,
                                                   BREAK_EDITOR_COMPONENT_TRANSFORM));

    /* Nothing recorded, component still present and zeroed. */
    ASSERT_EQ(break_editor_cmd_stack_size(stack), size_before);
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));

    /* Removing a component the entity does not have: bounded false. */
    BreakEditorEntityId bare = break_editor_doc_add_entity(doc, "bare");
    ASSERT_TRUE(break_editor_entity_id_valid(bare));
    ASSERT_FALSE(break_editor_doc_remove_component(
        doc, bare, BREAK_EDITOR_COMPONENT_TRANSFORM));

    break_editor_doc_destroy(doc);
}

TEST(oom_component_command_alloc_fails_bounded) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    u32 size_before = break_editor_cmd_stack_size(stack);

    /* add_component OOM: no command, no component, not dirty. */
    break_editor_doc_clear_dirty(doc);
    break_editor_test_set_alloc_budget(0);
    bool ok = break_editor_doc_add_component(doc, id,
                                             BREAK_EDITOR_COMPONENT_TRANSFORM);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_FALSE(ok);
    ASSERT_FALSE(break_editor_doc_has_component(doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_EQ(break_editor_cmd_stack_size(stack), size_before);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    /* Recovers once the budget is restored. */
    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));

    /* set_field OOM: value and stack unchanged. */
    break_editor_doc_clear_dirty(doc);
    break_editor_test_set_alloc_budget(0);
    ok = break_editor_doc_set_field_f32(doc, id,
                                        BREAK_EDITOR_COMPONENT_TRANSFORM, 0,
                                        9.0f);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_FALSE(ok);
    f32 v = 1.0f;
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, &v));
    ASSERT_EQ(f32_bits(v), 0u);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    /* remove_component OOM: component still present. */
    break_editor_test_set_alloc_budget(0);
    ok = break_editor_doc_remove_component(doc, id,
                                           BREAK_EDITOR_COMPONENT_TRANSFORM);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_FALSE(ok);
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));

    break_editor_doc_destroy(doc);
}

TEST(component_commands_describe) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    BreakEditorEntityId id = break_editor_doc_add_entity(doc, "hero");
    ASSERT_TRUE(break_editor_entity_id_valid(id));

    char buf[128];
    ASSERT_TRUE(break_editor_doc_add_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_cmd_stack_describe_last(stack, buf));
    ASSERT_TRUE(strstr(buf, "Transform") != NULL);

    ASSERT_TRUE(break_editor_doc_set_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0, 1.0f));
    ASSERT_TRUE(break_editor_cmd_stack_describe_last(stack, buf));
    ASSERT_TRUE(strstr(buf, "pos.x") != NULL);

    ASSERT_TRUE(break_editor_doc_remove_component(doc, id,
                                                  BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_cmd_stack_describe_last(stack, buf));
    ASSERT_TRUE(strstr(buf, "Transform") != NULL);

    break_editor_doc_destroy(doc);
}

TEST(parse_f32_accepts) {
    f32 out = 12345.0f;
    static const struct {
        const char *text;
        f32 want;
    } cases[] = {
        { "0", 0.0f },
        { "-0.0", -0.0f },
        { "1", 1.0f },
        { "-1", -1.0f },
        { "+1", 1.0f },
        { "1.5", 1.5f },
        { ".5", 0.5f },
        { "-.5", -0.5f },
        { "1.", 1.0f },
        { "007.25", 7.25f },
        { "1e3", 1000.0f },
        { "1E3", 1000.0f },
        { "1e-3", 0.001f },
        { "-2.5e+2", -250.0f },
        { "+.5e2", 50.0f },
        { "0e0", 0.0f },
        /* FLT_MAX written with its exact round-trip decimal digits. */
        { "3.4028234663852886e38", FLT_MAX },
        /* Subnormal and total underflow (accepted, documented). */
        { "1e-45", 1e-45f },
        { "1e-50", 0.0f },
        { "-1e-50", -0.0f },
    };
    for (usize i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        ASSERT_TRUE(break_editor_parse_f32(cases[i].text, &out));
        if (f32_bits(out) != f32_bits(cases[i].want)) {
            printf("  FAIL: parse \"%s\" got bits 0x%08X want 0x%08X\n",
                   cases[i].text, f32_bits(out), f32_bits(cases[i].want));
            g_test_fail++;
            return;
        }
    }
}

TEST(parse_f32_rejects) {
    f32 out = 12345.0f;
    static const char *const bad[] = {
        "",        /* empty */
        " ",       /* whitespace only */
        " 1",      /* leading whitespace: strict */
        "1 ",      /* trailing whitespace: strict */
        "1\t",     "\t1",
        ".",       /* no mantissa digits */
        "+",       "-", "+.", "-.",
        "1e",      "1e+", "1E-", /* exponent without digits */
        "abc", "e3", "x",
        "inf", "nan", "INFINITY", /* no special values */
        "0x1p3",   /* no hex floats */
        "1,5",     /* comma is NOT a decimal separator (locale-independent) */
        "1.2.3",   "1..2",
        "--1", "++1", "1e1e1",
        "1a", "1.5f", /* trailing garbage */
        /* Overflow beyond FLT_MAX: rejected (documented). */
        "3.5e38", "1e39", "-1e39", "1e100",
    };
    for (usize i = 0; i < sizeof(bad) / sizeof(bad[0]); i++) {
        if (break_editor_parse_f32(bad[i], &out)) {
            printf("  FAIL: parse \"%s\" unexpectedly accepted\n", bad[i]);
            g_test_fail++;
            return;
        }
        ASSERT_EQ(f32_bits(out), f32_bits(12345.0f)); /* out untouched */
    }

    /* NULL text / NULL out. */
    ASSERT_FALSE(break_editor_parse_f32(NULL, &out));
    ASSERT_FALSE(break_editor_parse_f32("1", NULL));

    /* Bounded 64-byte input: a 64-char string has no NUL within the scan
     * window and is rejected even though it is otherwise grammatical. */
    char long_input[65];
    memset(long_input, '1', 64);
    long_input[64] = '\0';
    ASSERT_FALSE(break_editor_parse_f32(long_input, &out));
    /* 63 digits fit the window; rejected on overflow grounds instead. */
    char max_input[64];
    memset(max_input, '1', 63);
    max_input[63] = '\0';
    ASSERT_FALSE(break_editor_parse_f32(max_input, &out));
}

TEST(component_bytes_survive_save_load) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_components_rt.bscn");

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "alpha");
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "beta");
    BreakEditorEntityId c = break_editor_doc_add_entity(doc, "gamma");
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_TRUE(break_editor_entity_id_valid(b));
    ASSERT_TRUE(break_editor_entity_id_valid(c));
    ASSERT_TRUE(break_editor_doc_add_component(doc, a,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_add_component(doc, b,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    /* c intentionally has no transform: sparse components round-trip too. */
    ASSERT_TRUE(set_all_fields(doc, a, 3.5f));
    ASSERT_TRUE(set_all_fields(doc, b, -17.75f));

    EditorTransform before_a;
    memcpy(&before_a, raw_transform(doc, a), sizeof(before_a));

    ASSERT_TRUE(break_editor_doc_save(doc, path));
    break_editor_doc_destroy(doc);

    /* Fresh doc: registry is per-doc, so the transform type is known again;
     * load re-registers it into the staging world and the BSCN COMPONENTS
     * chunk (raw bytes per type) lands. No holes => ids round-trip exactly
     * (Task 2 index-compaction contract). */
    doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_editor_doc_component_count(doc), 1u);
    ASSERT_TRUE(break_editor_doc_load(doc, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 3u);

    ASSERT_TRUE(break_editor_doc_has_component(doc, a,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_doc_has_component(doc, b,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_FALSE(break_editor_doc_has_component(doc, c,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));

    /* Byte-exact payload comparison, not just fieldwise equality. */
    const EditorTransform *ta = raw_transform(doc, a);
    ASSERT_NOT_NULL(ta);
    ASSERT_EQ(memcmp(&before_a, ta, sizeof(before_a)), 0);
    ASSERT_TRUE(fields_match(doc, a, 3.5f));
    ASSERT_TRUE(fields_match(doc, b, -17.75f));

    break_editor_doc_destroy(doc);
}

int main(void) {
    printf("=== test_editor_components ===\n");
    RUN_TEST(registry_enumeration);
    RUN_TEST(transform_registered_in_world_at_create);
    RUN_TEST(has_component_and_default_add);
    RUN_TEST(get_set_fields_round_trip);
    RUN_TEST(set_field_undo_redo_byte_exact);
    RUN_TEST(set_field_same_value_records_no_command);
    RUN_TEST(set_field_bounded_failures_leave_doc_unchanged);
    RUN_TEST(add_component_undo_redo_symmetric);
    RUN_TEST(remove_component_undo_restores_byte_snapshot);
    RUN_TEST(remove_entity_undo_restores_components);
    RUN_TEST(duplicate_entity_copies_components_in_one_command);
    RUN_TEST(remove_entities_is_one_command);
    RUN_TEST(duplicate_entities_is_one_command);
    RUN_TEST(reset_empties_the_document);
    RUN_TEST(add_remove_component_bounded_failures);
    RUN_TEST(oom_component_command_alloc_fails_bounded);
    RUN_TEST(component_commands_describe);
    RUN_TEST(parse_f32_accepts);
    RUN_TEST(parse_f32_rejects);
    RUN_TEST(component_bytes_survive_save_load);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n", g_test_pass,
           g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
