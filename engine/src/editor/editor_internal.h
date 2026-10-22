#pragma once
/* Library-internal shared state for break_editor (Task 1). Not part of the
 * public editor API — only editor_doc.c, editor_cmd.c, and later
 * editor_components.c (Task 3) include this. */

#include <editor/editor_cmd.h>
#include <editor/editor_doc.h>

#include <ecs/ecs.h>

/* Bounded name copy: src is validated to contain a NUL within
 * BREAK_EDITOR_NAME_CAPACITY bytes (name_fits in editor_doc.c); copies up
 * to and including that NUL and zero-pads the rest. Never reads past the
 * first NUL — a plain 128-byte memcpy would over-read short callers'
 * strings (caught by ASan). */
static inline void break_editor_name_copy(char *dst, const char *src) {
    usize i = 0;
    for (; i < BREAK_EDITOR_NAME_CAPACITY && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    for (; i < BREAK_EDITOR_NAME_CAPACITY; i++) {
        dst[i] = '\0';
    }
}

enum {
    BREAK_EDITOR_CMD_KIND_ADD_ENTITY = 1,
    BREAK_EDITOR_CMD_KIND_REMOVE_ENTITY = 2,
    BREAK_EDITOR_CMD_KIND_RENAME_ENTITY = 3
};

/* Concrete command: one bounded allocation per mutation. name/other_name
 * are always NUL-terminated within 128 bytes (constructors reject over-cap
 * input before allocation).
 *   add:    name = final display name (generated on first apply when the
 *           caller passed NULL); reapply distinguishes redo-apply from the
 *           first apply (id is only stored after a successful first apply).
 *   remove: name = snapshot of the display name at construction.
 *   rename: name = old display name snapshot, other_name = new name. */
struct BreakEditorCmd {
    bool (*apply)(BreakEditorCmd *self, BreakEditorDoc *doc);
    bool (*revert)(BreakEditorCmd *self, BreakEditorDoc *doc);
    void (*destroy)(BreakEditorCmd *self);
    void (*describe)(const BreakEditorCmd *self, char buf[128]);
    u32 kind;
    BreakEditorEntityId id;
    bool reapply;
    char name[BREAK_EDITOR_NAME_CAPACITY];
    char other_name[BREAK_EDITOR_NAME_CAPACITY];
};

/* Name slot: slot-per-entity-index storage, generation 0 = empty. */
typedef struct {
    u32 generation;                        /* generation this name belongs to */
    char name[BREAK_EDITOR_NAME_CAPACITY]; /* NUL-terminated */
} BreakEditorNameSlot;

struct BreakEditorDoc {
    World *world;               /* owned: world_create/world_destroy */
    BreakEditorNameSlot *slots; /* owned: ECS_MAX_ENTITIES slots */
    usize named_count;          /* live named entities == entity_count */
    bool dirty;
    BreakEditorCmdStack *stack; /* owned */
};

struct BreakEditorCmdStack {
    BreakEditorCmd **entries; /* fixed array of `capacity` */
    u32 capacity;
    u32 size;     /* applied + redoable commands currently held */
    u32 undo_pos; /* [0, undo_pos) applied; [undo_pos, size) redoable */
    bool dropped_oldest;
};

/* editor_doc.c internals shared with editor_cmd.c. */
World *break_editor_doc_world_raw(BreakEditorDoc *doc);
bool break_editor_doc_has_entity(const BreakEditorDoc *doc,
                                 BreakEditorEntityId id);
/* slot_set/slot_clear keep named_count exact; name must point at a
 * NUL-terminated 128-byte-bounded buffer (command storage). */
void break_editor_doc_slot_set(BreakEditorDoc *doc, u32 index, u32 generation,
                               const char *name);
void break_editor_doc_slot_clear(BreakEditorDoc *doc, u32 index);
/* Pushes an already-applied command; clears the redo tail; on overflow
 * destroys the oldest entry and sets dropped_oldest. Never allocates,
 * never fails. */
void break_editor_cmd_stack_push_applied(BreakEditorDoc *doc,
                                         BreakEditorCmd *cmd);

/* Command constructors (editor_cmd.c). Return NULL on OOM; the remove and
 * rename constructors also return NULL when the id is not a live named
 * entity of this document. Callers validate name lengths first. */
BreakEditorCmd *break_editor_cmd_add_entity_create(const char *name_or_null);
BreakEditorCmd *break_editor_cmd_remove_entity_create(BreakEditorDoc *doc,
                                                      BreakEditorEntityId id);
BreakEditorCmd *break_editor_cmd_rename_entity_create(BreakEditorDoc *doc,
                                                      BreakEditorEntityId id,
                                                      const char *new_name);
