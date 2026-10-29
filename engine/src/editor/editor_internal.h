#pragma once
/* Library-internal shared state for break_editor (Task 1). Not part of the
 * public editor API — only editor_doc.c, editor_cmd.c, editor_components.c
 * (Task 3), editor_viewport.c/editor_gizmo.c (Phase 2) include this. */

#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
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
    BREAK_EDITOR_CMD_KIND_RENAME_ENTITY = 3,
    BREAK_EDITOR_CMD_KIND_SET_FIELD_F32 = 4,
    BREAK_EDITOR_CMD_KIND_ADD_COMPONENT = 5,
    BREAK_EDITOR_CMD_KIND_REMOVE_COMPONENT = 6,
    BREAK_EDITOR_CMD_KIND_GIZMO_TRANSFORM = 7,
    BREAK_EDITOR_CMD_KIND_DUPLICATE_ENTITY = 8,
    BREAK_EDITOR_CMD_KIND_GROUP = 9
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

/* Registry entry for one editable component type (Task 3). Mirrors the
 * public BreakEditorComponentInfo plus the World's registered byte size
 * (needed for snapshot bounds and field-offset validation). */
typedef struct {
    u32 component_id;
    char display_name[32];        /* NUL-terminated */
    u32 size;                     /* byte size registered in the World */
    BreakEditorField fields[9];   /* matches BreakEditorComponentInfo cap */
    u32 field_count;
    /* bytes a freshly added component starts with (NULL = all zero) */
    const u8 *default_bytes;
} BreakEditorComponentReg;

/* Concrete component command payload (Task 3): one bounded allocation,
 * vtable-compatible via the embedded base (MUST be the first member).
 * base.id is the entity; base.name/other_name are unused (zeroed). The
 * display/field names are copied in at construction because describe() has
 * no doc access.
 *   set_field_f32:   old_bits/new_bits are the 4 bytes at field_offset
 *                    (byte-exact revert; -0.0/NaN payloads survive).
 *   add_component:   snapshot captured after the first apply (the zeroed
 *                    state), restored on redo.
 *   remove_component: snapshot captured at construction (the pre-remove
 *                    bytes), restored on revert. */
typedef struct {
    BreakEditorCmd base;
    u32 component_id;
    u32 field_offset;    /* set_field: byte offset within the component */
    u32 old_bits;        /* set_field: previous 4 bytes */
    u32 new_bits;        /* set_field: bytes to apply */
    u32 snapshot_size;   /* add/remove: component size (<= 256) */
    bool snapshot_taken; /* add: snapshot captured after first apply */
    char display_name[32];
    char field_name[32]; /* set_field only */
    u8 snapshot[BREAK_EDITOR_COMPONENT_SNAPSHOT_CAPACITY];
} BreakEditorComponentCmd;

struct BreakEditorDoc {
    World *world;               /* owned: world_create/world_destroy */
    BreakEditorNameSlot *slots; /* owned: ECS_MAX_ENTITIES slots */
    usize named_count;          /* live named entities == entity_count */
    bool dirty;
    BreakEditorCmdStack *stack; /* owned */
    /* Task 3: bounded editable-component registry (cap 16). Phase 1 holds
     * exactly one entry (EditorTransform) installed at doc create by
     * break_editor_doc_init_components. */
    BreakEditorComponentReg components[BREAK_EDITOR_COMPONENT_REGISTRY_CAPACITY];
    u32 component_count;
    /* Game-side chunks of the last loaded BSCN that the editor does not
     * model (every chunk except ENTITIES/COMPONENTS/HIERARCHY: SCENE_NODES,
     * RESOURCES, mesh/skin geometry, skeleton, anims, future types). Kept
     * as the exact {type, bytes} the file held and spliced back by save, so
     * a re-save never drops them. NULL/0 = none. Owned (one allocation per
     * payload + the table). */
    struct BreakEditorKeptChunk *kept_chunks;
    u32 kept_chunk_count;
};

struct BreakEditorCmdStack {
    BreakEditorCmd **entries; /* fixed array of `capacity` */
    u32 capacity;
    u32 size;     /* applied + redoable commands currently held */
    u32 undo_pos; /* [0, undo_pos) applied; [undo_pos, size) redoable */
    bool dropped_oldest;
    u64 revision; /* +1 per push / undo / redo (change signal) */
};

/* editor_scene.c: releases doc->kept_chunks (safe when none). */
void break_editor_doc_kept_chunks_free(BreakEditorDoc *doc);

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

/* Destroys every held command and resets size/undo_pos/dropped_oldest to a
 * fresh state. Never allocates, never fails. editor_scene.c calls this on a
 * successful load: the recorded commands reference the pre-load world, which
 * no longer exists. */
void break_editor_cmd_stack_clear(BreakEditorCmdStack *stack);

/* Command constructors (editor_cmd.c). Return NULL on OOM; the remove and
 * rename constructors also return NULL when the id is not a live named
 * entity of this document. Callers validate name lengths first. */
BreakEditorCmd *break_editor_cmd_add_entity_create(const char *name_or_null);
/* duplicate: an add_entity whose apply also installs byte copies of every
 * registered component `src` has (snapshotted at construction). */
BreakEditorCmd *break_editor_cmd_duplicate_entity_create(BreakEditorDoc *doc,
                                                         BreakEditorEntityId src,
                                                         const char *name);
/* group: owns up to BREAK_EDITOR_GROUP_MAX already-built child commands;
 * apply runs them in order (undoing the applied prefix on a failure),
 * revert runs them in reverse. `children` is copied; on NULL (OOM) the
 * caller still owns the children. */
BreakEditorCmd *break_editor_cmd_group_create(BreakEditorCmd **children,
                                              u32 count, const char *label);
BreakEditorCmd *break_editor_cmd_remove_entity_create(BreakEditorDoc *doc,
                                                      BreakEditorEntityId id);
BreakEditorCmd *break_editor_cmd_rename_entity_create(BreakEditorDoc *doc,
                                                      BreakEditorEntityId id,
                                                      const char *new_name);

/* Task 3 (editor_components.c): installs the doc's editable-component
 * registry and registers each type into the doc's World. No allocation,
 * never fails. Called by break_editor_doc_create. */
void break_editor_doc_init_components(BreakEditorDoc *doc);

/* Registry lookup (editor_components.c): NULL when component_id is not a
 * registered editable type. */
const BreakEditorComponentReg *break_editor_doc_find_component(
    const BreakEditorDoc *doc, u32 component_id);

/* Raw component bytes for the gizmo's coalescing drag command (Phase 2
 * Task 2, editor_gizmo.c): registry-gated (NULL for unregistered ids,
 * stale entities, or absent components). The gizmo writes through this
 * pointer ONLY while its in-progress multi-field command owns the mutation
 * (begin_drag..end_drag); the command is pushed at end_drag, so the undo
 * stack still sees exactly one command per drag. */
u8 *break_editor_doc_component_bytes(BreakEditorDoc *doc,
                                     BreakEditorEntityId id,
                                     u32 component_id);
