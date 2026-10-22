#pragma once
/* BreakEditorDoc — Stage 4 scene editor Phase 1 document model (Task 1:
 * undo/redo core).
 *
 * A document owns exactly one ECS World (world_create at doc create,
 * world_destroy at doc destroy; engine/src/ecs/ecs.h:118-119) plus a
 * bounded entity name map and one bounded command stack. ALL document
 * mutations route through command objects
 * {apply, revert, destroy, describe(char buf[128])} pushed onto the stack,
 * so undo/redo is exact and snapshot-free (plan Global Constraints).
 *
 * Entity names: ECS has no entity names, so the doc owns a slot-per-index
 * name map (cap = ECS_MAX_ENTITIES entries, key = {index, generation};
 * index 0 is the ECS ENTITY_NULL sentinel and never used). A name is at
 * most BREAK_EDITOR_NAME_CAPACITY (128) bytes INCLUDING the NUL terminator
 * (127 usable characters). Over-cap names are REJECTED: the mutation
 * returns failure (false / BREAK_EDITOR_ENTITY_NULL) and the document is
 * left unchanged — there is no truncation. break_editor_doc_add_entity
 * accepts NULL name and generates "entity_<index>_<generation>".
 *
 * Entity iteration for the outliner (break_editor_doc_entity_at) has a
 * stable ordering: ASCENDING entity index, holes skipped. i in
 * [0, break_editor_doc_entity_count). out_name is a borrowed pointer into
 * the doc, valid until the entity is removed/renamed or the doc is
 * destroyed.
 *
 * Redo-after-undo restores the SAME BreakEditorEntityId: the add command
 * stores the created id; revert destroys by id; redo re-creates (the ECS
 * free stack is LIFO, and revert/redo are always adjacent because any new
 * mutation clears the redo tail) and forcibly restores the stored
 * generation — the same generation-restore mechanism scene_serial uses
 * (engine/src/scene/scene_serial.c:1056-1064). remove_entity revert uses
 * the same mechanism and restores the entity id + display name; component
 * bytes are NOT restored — component restoration lands with Task 3's
 * add/remove-component commands (plan Task 3).
 *
 * Dirty flag: any successful command apply (add/remove/rename) and any
 * successful undo/redo sets it; only break_editor_doc_clear_dirty clears
 * it (the Task 2 save path calls it). Undoing back to the saved state
 * does NOT clear the flag (conservative, no saved-state cursor).
 *
 * Threading: single-owner-thread convention — the editor shell thread owns
 * the document; there is no mutex. Cross-thread use is a contract
 * violation, same convention as runtime_coordinator/break_lua.
 *
 * Bounds: every public mutation fails bounded (false /
 * BREAK_EDITOR_ENTITY_NULL) on over-cap names, nonexistent/stale ids, ECS
 * entity-cap exhaustion, or allocation failure, leaving the document
 * unchanged. */

#include <core/types.h>

/* Entity name byte cap INCLUDING the NUL terminator (127 usable chars). */
#define BREAK_EDITOR_NAME_CAPACITY 128u
/* Command stack default capacity (create(0)) and hard cap. */
#define BREAK_EDITOR_CMD_STACK_DEFAULT_CAPACITY 256u
#define BREAK_EDITOR_CMD_STACK_MAX_CAPACITY 4096u

typedef struct BreakEditorDoc BreakEditorDoc;
typedef struct BreakEditorCmdStack BreakEditorCmdStack;

/* Editor entity handle — layout matches Entity (engine/src/ecs/ecs.h:14-17)
 * exactly (pinned by _Static_assert in test_editor_doc.c). No u64
 * flattening anywhere (Task 1 brief decision). generation == 0 is the
 * invalid/null id, matching entity_valid(). */
typedef struct {
    u32 index;
    u32 generation;
} BreakEditorEntityId;

#define BREAK_EDITOR_ENTITY_NULL ((BreakEditorEntityId){0u, 0u})

static inline bool break_editor_entity_id_valid(BreakEditorEntityId id) {
    return id.generation != 0u;
}

static inline bool break_editor_entity_id_eq(BreakEditorEntityId a,
                                             BreakEditorEntityId b) {
    return a.index == b.index && a.generation == b.generation;
}

BreakEditorDoc *break_editor_doc_create(void); /* owns an internal World */
void break_editor_doc_destroy(BreakEditorDoc *doc); /* NULL is a no-op */
void *break_editor_doc_world(BreakEditorDoc *doc); /* borrowed World*, shell-only */

/* Command-driven mutations (all fail bounded, document unchanged on
 * failure): */
BreakEditorEntityId break_editor_doc_add_entity(BreakEditorDoc *doc,
                                                const char *name);
bool break_editor_doc_remove_entity(BreakEditorDoc *doc,
                                    BreakEditorEntityId id);
bool break_editor_doc_rename_entity(BreakEditorDoc *doc,
                                    BreakEditorEntityId id,
                                    const char *name);

usize break_editor_doc_entity_count(const BreakEditorDoc *doc);
bool break_editor_doc_entity_at(const BreakEditorDoc *doc, usize i,
                                BreakEditorEntityId *out_id,
                                const char **out_name); /* borrowed name */
bool break_editor_doc_is_dirty(const BreakEditorDoc *doc);
/* Clears the dirty flag; the Task 2 save path calls this after a
 * successful save. */
void break_editor_doc_clear_dirty(BreakEditorDoc *doc);

/* Borrowed handle to the doc's internal command stack (created with
 * default capacity 256 at doc create). For tests/status accessors in
 * editor_cmd.h; callers never push directly. */
BreakEditorCmdStack *break_editor_doc_stack(BreakEditorDoc *doc);
