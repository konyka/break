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
 * the same mechanism and restores the entity id, display name and every
 * registered component (byte snapshot taken when the command is built).
 * DEPENDENCY: this mechanism
 * relies on ecs.c free-stack internals (LIFO index reuse,
 * ecs.c:563-566/681, and the generation bump on destroy/create,
 * ecs.c:565/682). If ecs.c changes, re-verify the redo pins in
 * test_editor_cmd.c: redo_add_restores_same_id,
 * redo_restores_exact_ids_with_two_free_indices (>=2 free indices at pop
 * time), and rename_remove_undo_chain_keeps_ids_exact.
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
/* Origin stamped on every command pushed from now on (0 = the local shell,
 * the default). The remote host sets one per connection around its handlers
 * so undo can be scoped to a client (editor_cmd.h break_editor_undo_origin).
 * NULL doc: no-op / 0. */
void break_editor_doc_set_origin(BreakEditorDoc *doc, u32 origin);
u32 break_editor_doc_origin(const BreakEditorDoc *doc);
void break_editor_doc_destroy(BreakEditorDoc *doc); /* NULL is a no-op */
/* Borrowed World* (shell-only). A successful break_editor_doc_load SWAPS the
 * internal World (editor_scene.h): any pointer borrowed before the load
 * DANGLES afterwards — callers must re-fetch. */
void *break_editor_doc_world(BreakEditorDoc *doc);

/* Command-driven mutations (all fail bounded, document unchanged on
 * failure): */
BreakEditorEntityId break_editor_doc_add_entity(BreakEditorDoc *doc,
                                                const char *name);
bool break_editor_doc_remove_entity(BreakEditorDoc *doc,
                                    BreakEditorEntityId id);
/* Removes every live entity in ids[0..count) as ONE undoable command (undo
 * restores all, with names and components). Stale and repeated ids are
 * skipped. Returns how many were removed; 0 = nothing recorded (also for
 * NULL arguments, OOM, or count above BREAK_EDITOR_GROUP_MAX). */
#define BREAK_EDITOR_GROUP_MAX 256u
u32 break_editor_doc_remove_entities(BreakEditorDoc *doc,
                                     const BreakEditorEntityId *ids, u32 count);
bool break_editor_doc_rename_entity(BreakEditorDoc *doc,
                                    BreakEditorEntityId id,
                                    const char *name);
/* One undoable command: a new entity named "<name> copy" (the source name
 * alone when the suffix would not fit) holding byte-exact copies of every
 * registered component of `id`. NULL id on stale id / NULL doc / ECS cap /
 * OOM (document unchanged). */
BreakEditorEntityId break_editor_doc_duplicate_entity(BreakEditorDoc *doc,
                                                      BreakEditorEntityId id);
/* Duplicates every live entity in ids[0..count) (same naming as
 * duplicate_entity) as ONE undoable command; out[k] is the k-th copy, in
 * input order, for the returned count. Stale and repeated ids are skipped.
 * 0 = nothing recorded (also NULL arguments, OOM, count above
 * BREAK_EDITOR_GROUP_MAX). */
u32 break_editor_doc_duplicate_entities(BreakEditorDoc *doc,
                                        const BreakEditorEntityId *ids,
                                        u32 count, BreakEditorEntityId *out);

/* Empties the document: a fresh world (components registered as at
 * create), no names, no kept game chunks, no undo history, clean. Ids from
 * before the reset are stale afterwards. false for NULL or when the new
 * world cannot be allocated (document unchanged). */
bool break_editor_doc_reset(BreakEditorDoc *doc);

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
