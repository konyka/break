#pragma once
/* BreakEditorCmdStack — Stage 4 scene editor Phase 1 bounded undo/redo
 * command stack (Task 1).
 *
 * Every document mutation is a command object with the vtable
 * {apply, revert, destroy, describe(char buf[128])}. The doc applies a
 * freshly constructed command first, then pushes it onto its internal
 * stack (created with default capacity 256). The stack is BOUNDED: pushing
 * when full drops the OLDEST executed command (destroying it), sets the
 * `dropped_oldest` flag (readable via
 * break_editor_cmd_stack_dropped_oldest), and never fails. Pushing a new
 * command clears the redo tail — this is what guarantees revert/redo
 * adjacency and makes the generation-restore redo mechanism (editor_doc.h
 * header comment) exact. DEPENDENCY: that mechanism relies on ecs.c
 * free-stack internals (LIFO index reuse + generation bump on
 * destroy/create); if ecs.c changes, re-verify the redo pins in
 * test_editor_cmd.c (redo_add_restores_same_id,
 * redo_restores_exact_ids_with_two_free_indices,
 * rename_remove_undo_chain_keeps_ids_exact).
 *
 * Undo/redo cursors: entries [0, undo_pos) are applied (undoable);
 * [undo_pos, size) are reverted (redoable). undo/redo return false when
 * the respective side is empty, and also fail bounded (cursor unchanged)
 * if the command's revert/apply itself fails.
 *
 * The stack never allocates after create: drop-oldest reuses the fixed
 * entry array, so the only per-mutation allocation is the command object
 * itself (OOM-injectable under BREAK_EDITOR_TESTING, editor_test_hooks.h).
 *
 * Threading: same single-owner-thread convention as the owning document —
 * no mutex. */

#include <core/types.h>

#include <editor/editor_doc.h>

/* 0 => BREAK_EDITOR_CMD_STACK_DEFAULT_CAPACITY (256);
 * > BREAK_EDITOR_CMD_STACK_MAX_CAPACITY (4096) => bounded NULL. */
BreakEditorCmdStack *break_editor_cmd_stack_create(u32 capacity);
void break_editor_cmd_stack_destroy(BreakEditorCmdStack *stack); /* NULL no-op */

bool break_editor_undo(BreakEditorDoc *doc); /* false when empty */
bool break_editor_redo(BreakEditorDoc *doc); /* false when empty */

/* Origin-scoped undo/redo (per-client undo). Every command carries the doc
 * origin that was set when it was pushed (editor_doc.h
 * break_editor_doc_set_origin; 0 = local shell). These act on the NEWEST
 * applied (undo) / OLDEST undone (redo) command of `origin`, and only when
 * that is provably independent of everything it would move past:
 *   undo: no LATER command of another origin (applied or undone) touches one
 *         of its entity indices; commands of the same origin never block
 *         each other (a client's own history stays consistent in its order).
 *   redo: none of the undone commands ahead of it, from another origin,
 *         touches one of its entity indices, and its apply succeeds (an
 *         add/remove needs the ECS free list to hand back the exact id; if
 *         the list is in a different order the attempt fails bounded and
 *         BLOCKED is reported with the document and stack unchanged).
 * On success the command is moved to the applied/undone edge (undo: first
 * redoable entry; redo: last applied entry), so the usual invariants hold:
 * a new push still clears the whole redo tail, global undo/redo still walk
 * the stack from the cursor. Results:
 *   NONE    the origin has nothing to undo/redo (also NULL doc / origin 0
 *           works like any other origin);
 *   APPLIED done; revision +1, doc marked dirty;
 *   BLOCKED the origin has a candidate but independence or its own
 *           revert/apply failed; nothing changed (revision untouched). */
typedef enum {
    BREAK_EDITOR_ORIGIN_NONE = 0,
    BREAK_EDITOR_ORIGIN_APPLIED = 1,
    BREAK_EDITOR_ORIGIN_BLOCKED = 2
} BreakEditorOriginResult;

BreakEditorOriginResult break_editor_undo_origin(BreakEditorDoc *doc, u32 origin);
BreakEditorOriginResult break_editor_redo_origin(BreakEditorDoc *doc, u32 origin);
u32 break_editor_cmd_stack_undo_count_origin(const BreakEditorCmdStack *stack,
                                             u32 origin);
u32 break_editor_cmd_stack_redo_count_origin(const BreakEditorCmdStack *stack,
                                             u32 origin);

/* Test/status-readable accessors (NULL stack => 0/false). */
u32  break_editor_cmd_stack_capacity(const BreakEditorCmdStack *stack);
u32  break_editor_cmd_stack_size(const BreakEditorCmdStack *stack);      /* applied + redoable */
u32  break_editor_cmd_stack_undo_count(const BreakEditorCmdStack *stack);
u32  break_editor_cmd_stack_redo_count(const BreakEditorCmdStack *stack);
bool break_editor_cmd_stack_dropped_oldest(const BreakEditorCmdStack *stack);
/* Change counter: +1 on every push, successful undo and successful redo;
 * never decreases (0 for a NULL stack). */
u64  break_editor_cmd_stack_revision(const BreakEditorCmdStack *stack);

/* Describes the command that the next undo would revert (status bar /
 * console). Bounded: writes at most 128 bytes incl. NUL, truncating long
 * names. Returns false when nothing is applied. */
bool break_editor_cmd_stack_describe_last(const BreakEditorCmdStack *stack,
                                          char buf[128]);

/* Command object surface. The vtable shape is public for later tasks
 * (Task 3 component commands); the concrete payload and constructors live
 * in editor_internal.h (library-internal). */
typedef struct BreakEditorCmd BreakEditorCmd;
