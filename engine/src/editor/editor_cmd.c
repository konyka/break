/* BreakEditorCmdStack + built-in Task 1 command objects — see editor_cmd.h
 * for the stack contract and editor_doc.h for the redo-after-undo
 * generation-restore mechanism. */

#include <editor/editor_cmd.h>

#include <editor/editor_internal.h>
#include <editor/editor_test_hooks.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BreakEditorCmdStack *break_editor_cmd_stack_create(u32 capacity) {
    if (capacity == 0) capacity = BREAK_EDITOR_CMD_STACK_DEFAULT_CAPACITY;
    if (capacity > BREAK_EDITOR_CMD_STACK_MAX_CAPACITY) return NULL;
    BreakEditorCmdStack *stack = break_editor_test_calloc(sizeof(*stack));
    if (!stack) return NULL;
    stack->entries =
        break_editor_test_calloc((usize)capacity * sizeof(*stack->entries));
    if (!stack->entries) {
        free(stack);
        return NULL;
    }
    stack->capacity = capacity;
    return stack;
}

void break_editor_cmd_stack_destroy(BreakEditorCmdStack *stack) {
    if (!stack) return;
    for (u32 i = 0; i < stack->size; i++) {
        stack->entries[i]->destroy(stack->entries[i]);
    }
    free(stack->entries);
    free(stack);
}

void break_editor_cmd_stack_push_applied(BreakEditorDoc *doc,
                                         BreakEditorCmd *cmd) {
    doc->stack->revision++;
    BreakEditorCmdStack *stack = doc->stack;

    /* New mutation clears the redo tail (this is what keeps revert/redo
     * adjacent for the generation-restore mechanism). */
    while (stack->size > stack->undo_pos) {
        stack->size--;
        stack->entries[stack->size]->destroy(stack->entries[stack->size]);
        stack->entries[stack->size] = NULL;
    }

    if (stack->size == stack->capacity) {
        /* Bounded drop-oldest: destroy the oldest executed command and
         * shift. The drop is observable via dropped_oldest. */
        stack->entries[0]->destroy(stack->entries[0]);
        memmove(stack->entries, stack->entries + 1,
                (usize)(stack->size - 1u) * sizeof(*stack->entries));
        stack->size--;
        stack->undo_pos--;
        stack->dropped_oldest = true;
    }

    stack->entries[stack->size++] = cmd;
    stack->undo_pos++;
}

bool break_editor_undo(BreakEditorDoc *doc) {
    if (!doc || !doc->stack) return false;
    BreakEditorCmdStack *stack = doc->stack;
    if (stack->undo_pos == 0) return false;
    BreakEditorCmd *cmd = stack->entries[stack->undo_pos - 1u];
    if (!cmd->revert(cmd, doc)) return false; /* cursor unchanged */
    stack->undo_pos--;
    stack->revision++;
    doc->dirty = true;
    return true;
}

bool break_editor_redo(BreakEditorDoc *doc) {
    if (!doc || !doc->stack) return false;
    BreakEditorCmdStack *stack = doc->stack;
    if (stack->undo_pos == stack->size) return false;
    BreakEditorCmd *cmd = stack->entries[stack->undo_pos];
    if (!cmd->apply(cmd, doc)) return false; /* cursor unchanged */
    stack->undo_pos++;
    stack->revision++;
    doc->dirty = true;
    return true;
}

void break_editor_cmd_stack_clear(BreakEditorCmdStack *stack) {
    if (!stack) return;
    for (u32 i = 0; i < stack->size; i++) {
        stack->entries[i]->destroy(stack->entries[i]);
        stack->entries[i] = NULL;
    }
    stack->size = 0;
    stack->undo_pos = 0;
    stack->dropped_oldest = false;
}

u32 break_editor_cmd_stack_capacity(const BreakEditorCmdStack *stack) {
    return stack ? stack->capacity : 0u;
}

u32 break_editor_cmd_stack_size(const BreakEditorCmdStack *stack) {
    return stack ? stack->size : 0u;
}

u32 break_editor_cmd_stack_undo_count(const BreakEditorCmdStack *stack) {
    return stack ? stack->undo_pos : 0u;
}

u32 break_editor_cmd_stack_redo_count(const BreakEditorCmdStack *stack) {
    return stack ? stack->size - stack->undo_pos : 0u;
}

u64 break_editor_cmd_stack_revision(const BreakEditorCmdStack *stack) {
    return stack ? stack->revision : 0u;
}

bool break_editor_cmd_stack_dropped_oldest(const BreakEditorCmdStack *stack) {
    return stack ? stack->dropped_oldest : false;
}

bool break_editor_cmd_stack_describe_last(const BreakEditorCmdStack *stack,
                                          char buf[128]) {
    if (!stack || !buf || stack->undo_pos == 0) return false;
    const BreakEditorCmd *cmd = stack->entries[stack->undo_pos - 1u];
    cmd->describe(cmd, buf);
    return true;
}

/* ---- shared command helpers ---- */

static void cmd_destroy(BreakEditorCmd *self) {
    free(self);
}

/* Re-creates the entity with the EXACT stored id after the matching
 * destroy. The ECS free stack is LIFO and revert/redo of one command are
 * always adjacent (a new mutation clears the redo tail), so
 * world_create_entity pops the same index; the generation is then forcibly
 * restored — the scene_serial generation-restore mechanism
 * (engine/src/scene/scene_serial.c:1056-1064). Fails bounded (destroying
 * the wrong entity again) if the world diverged from the command's
 * expectation. DEPENDENCY: ecs.c free-stack internals (LIFO reuse
 * ecs.c:563-566/681 + generation bump ecs.c:565/682); if ecs.c changes,
 * re-verify the redo pins in test_editor_cmd.c. */
static bool recreate_with_stored_id(BreakEditorDoc *doc,
                                    BreakEditorEntityId stored) {
    World *w = break_editor_doc_world_raw(doc);
    Entity e = world_create_entity(w);
    if (!entity_valid(e)) return false;
    if (e.index != stored.index) {
        world_destroy_entity(w, e);
        return false;
    }
    w->entities[e.index].generation = stored.generation;
    return true;
}

/* remove_entity and duplicate_entity carry a byte snapshot of every
 * registered component (taken at construction): remove restores it on
 * undo, duplicate installs it on every apply. One bounded allocation: the
 * base must stay the first member. */
typedef struct {
    BreakEditorCmd base;
    u32 count;
    struct {
        u32 component_id;
        u32 size;
        u8 bytes[BREAK_EDITOR_COMPONENT_SNAPSHOT_CAPACITY];
    } comps[BREAK_EDITOR_COMPONENT_REGISTRY_CAPACITY];
} BreakEditorSnapshotEntityCmd;

/* Fills r->comps from the components `id` currently has. */
static void snapshot_components(BreakEditorDoc *doc, BreakEditorEntityId id,
                                BreakEditorSnapshotEntityCmd *r) {
    r->count = 0;
    for (u32 i = 0; i < doc->component_count; i++) {
        const BreakEditorComponentReg *reg = &doc->components[i];
        const u8 *bytes =
            break_editor_doc_component_bytes(doc, id, reg->component_id);
        if (bytes == NULL ||
            reg->size > BREAK_EDITOR_COMPONENT_SNAPSHOT_CAPACITY) {
            continue; /* entity lacks it (sizes are capped at register) */
        }
        r->comps[r->count].component_id = reg->component_id;
        r->comps[r->count].size = reg->size;
        memcpy(r->comps[r->count].bytes, bytes, reg->size);
        r->count++;
    }
}

/* Adds the snapshot's components to the live entity `id`. On failure the
 * components already added stay; the caller destroys the entity. */
static bool install_components(BreakEditorDoc *doc, BreakEditorEntityId id,
                               const BreakEditorSnapshotEntityCmd *r) {
    World *w = break_editor_doc_world_raw(doc);
    Entity e;
    e.index = id.index;
    e.generation = id.generation;
    for (u32 i = 0; i < r->count; i++) {
        u8 *p = world_add_component(w, e, r->comps[i].component_id);
        if (!p) return false;
        memcpy(p, r->comps[i].bytes, r->comps[i].size);
    }
    return true;
}

/* ---- add_entity ---- */

static bool add_apply(BreakEditorCmd *self, BreakEditorDoc *doc) {
    World *w = break_editor_doc_world_raw(doc);
    if (self->reapply) {
        if (!recreate_with_stored_id(doc, self->id)) return false;
    } else {
        Entity e = world_create_entity(w);
        if (!entity_valid(e)) return false;
        self->id.index = e.index;
        self->id.generation = e.generation;
        self->reapply = true;
        if (self->name[0] == '\0') {
            snprintf(self->name, sizeof(self->name), "entity_%u_%u", e.index,
                     e.generation);
        }
    }
    break_editor_doc_slot_set(doc, self->id.index, self->id.generation,
                              self->name);
    return true;
}

static bool add_revert(BreakEditorCmd *self, BreakEditorDoc *doc) {
    World *w = break_editor_doc_world_raw(doc);
    Entity e;
    e.index = self->id.index;
    e.generation = self->id.generation;
    world_destroy_entity(w, e);
    break_editor_doc_slot_clear(doc, self->id.index);
    return true;
}

static void add_describe(const BreakEditorCmd *self, char buf[128]) {
    /* Precision limits keep the worst-case output provably < 128 bytes. */
    snprintf(buf, 128, "add entity '%.64s' (%u:%u)", self->name,
             self->id.index, self->id.generation);
}

BreakEditorCmd *break_editor_cmd_add_entity_create(const char *name_or_null) {
    BreakEditorCmd *cmd = break_editor_test_calloc(sizeof(*cmd));
    if (!cmd) return NULL;
    cmd->apply = add_apply;
    cmd->revert = add_revert;
    cmd->destroy = cmd_destroy;
    cmd->describe = add_describe;
    cmd->kind = BREAK_EDITOR_CMD_KIND_ADD_ENTITY;
    cmd->id = BREAK_EDITOR_ENTITY_NULL;
    cmd->reapply = false;
    if (name_or_null) {
        /* Caller already rejected over-cap names: NUL within 128 bytes. */
        break_editor_name_copy(cmd->name, name_or_null);
    }
    return cmd;
}

/* ---- duplicate_entity ---- */

static bool dup_apply(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorSnapshotEntityCmd *r = (BreakEditorSnapshotEntityCmd *)self;
    if (!add_apply(self, doc)) return false;
    if (!install_components(doc, self->id, r)) {
        (void)add_revert(self, doc); /* entity + slot gone, cursor unchanged */
        return false;
    }
    return true;
}

static void dup_describe(const BreakEditorCmd *self, char buf[128]) {
    snprintf(buf, 128, "duplicate entity '%.64s' (%u:%u)", self->name,
             self->id.index, self->id.generation);
}

BreakEditorCmd *break_editor_cmd_duplicate_entity_create(BreakEditorDoc *doc,
                                                         BreakEditorEntityId src,
                                                         const char *name) {
    if (!break_editor_doc_has_entity(doc, src)) return NULL;
    BreakEditorSnapshotEntityCmd *r = break_editor_test_calloc(sizeof(*r));
    if (!r) return NULL;
    BreakEditorCmd *cmd = &r->base;
    snapshot_components(doc, src, r);
    cmd->apply = dup_apply;
    cmd->revert = add_revert;
    cmd->destroy = cmd_destroy;
    cmd->describe = dup_describe;
    cmd->kind = BREAK_EDITOR_CMD_KIND_DUPLICATE_ENTITY;
    cmd->id = BREAK_EDITOR_ENTITY_NULL;
    cmd->reapply = false;
    break_editor_name_copy(cmd->name, name);
    return cmd;
}

/* ---- remove_entity ---- */



static bool remove_apply(BreakEditorCmd *self, BreakEditorDoc *doc) {
    World *w = break_editor_doc_world_raw(doc);
    Entity e;
    e.index = self->id.index;
    e.generation = self->id.generation;
    world_destroy_entity(w, e);
    break_editor_doc_slot_clear(doc, self->id.index);
    return true;
}

static bool remove_revert(BreakEditorCmd *self, BreakEditorDoc *doc) {
    /* Restores the id, the display name and every component snapshotted at
     * construction, byte-exact. */
    BreakEditorSnapshotEntityCmd *r = (BreakEditorSnapshotEntityCmd *)self;
    if (!recreate_with_stored_id(doc, self->id)) return false;
    if (!install_components(doc, self->id, r)) {
        /* ECS cap/OOM: undo the partial restore, cursor unchanged */
        Entity e;
        e.index = self->id.index;
        e.generation = self->id.generation;
        world_destroy_entity(break_editor_doc_world_raw(doc), e);
        return false;
    }
    break_editor_doc_slot_set(doc, self->id.index, self->id.generation,
                              self->name);
    return true;
}

static void remove_describe(const BreakEditorCmd *self, char buf[128]) {
    snprintf(buf, 128, "remove entity '%.64s' (%u:%u)", self->name,
             self->id.index, self->id.generation);
}

BreakEditorCmd *break_editor_cmd_remove_entity_create(BreakEditorDoc *doc,
                                                      BreakEditorEntityId id) {
    if (!break_editor_doc_has_entity(doc, id)) return NULL;
    BreakEditorSnapshotEntityCmd *r = break_editor_test_calloc(sizeof(*r));
    if (!r) return NULL;
    BreakEditorCmd *cmd = &r->base;
    snapshot_components(doc, id, r);
    cmd->apply = remove_apply;
    cmd->revert = remove_revert;
    cmd->destroy = cmd_destroy;
    cmd->describe = remove_describe;
    cmd->kind = BREAK_EDITOR_CMD_KIND_REMOVE_ENTITY;
    cmd->id = id;
    const BreakEditorNameSlot *slot = &doc->slots[id.index];
    memcpy(cmd->name, slot->name, BREAK_EDITOR_NAME_CAPACITY);
    return cmd;
}

/* ---- group ---- */

typedef struct {
    BreakEditorCmd base;
    u32 count;
    BreakEditorCmd *children[BREAK_EDITOR_GROUP_MAX];
} BreakEditorGroupCmd;

static bool group_apply(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorGroupCmd *g = (BreakEditorGroupCmd *)self;
    for (u32 i = 0; i < g->count; i++) {
        if (!g->children[i]->apply(g->children[i], doc)) {
            while (i > 0u) { /* all-or-nothing */
                i--;
                (void)g->children[i]->revert(g->children[i], doc);
            }
            return false;
        }
    }
    return true;
}

static bool group_revert(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorGroupCmd *g = (BreakEditorGroupCmd *)self;
    u32 i = g->count;
    while (i > 0u) {
        i--;
        if (!g->children[i]->revert(g->children[i], doc)) {
            for (u32 k = i + 1u; k < g->count; k++) { /* re-apply undone tail */
                (void)g->children[k]->apply(g->children[k], doc);
            }
            return false;
        }
    }
    return true;
}

static void group_destroy(BreakEditorCmd *self) {
    BreakEditorGroupCmd *g = (BreakEditorGroupCmd *)self;
    for (u32 i = 0; i < g->count; i++) g->children[i]->destroy(g->children[i]);
    free(g);
}

static void group_describe(const BreakEditorCmd *self, char buf[128]) {
    const BreakEditorGroupCmd *g = (const BreakEditorGroupCmd *)self;
    snprintf(buf, 128, "%.64s (%u)", self->name, g->count);
}

BreakEditorCmd *break_editor_cmd_group_create(BreakEditorCmd **children,
                                              u32 count, const char *label) {
    if (!children || count == 0u || count > BREAK_EDITOR_GROUP_MAX) return NULL;
    BreakEditorGroupCmd *g = break_editor_test_calloc(sizeof(*g));
    if (!g) return NULL;
    memcpy(g->children, children, (usize)count * sizeof(children[0]));
    g->count = count;
    g->base.apply = group_apply;
    g->base.revert = group_revert;
    g->base.destroy = group_destroy;
    g->base.describe = group_describe;
    g->base.kind = BREAK_EDITOR_CMD_KIND_GROUP;
    g->base.id = BREAK_EDITOR_ENTITY_NULL;
    break_editor_name_copy(g->base.name, label ? label : "group");
    return &g->base;
}

/* ---- rename_entity ---- */

static bool rename_apply(BreakEditorCmd *self, BreakEditorDoc *doc) {
    /* Defensive id check: under the command-stack invariants the entity is
     * always live here (undo/redo is strictly LIFO-nested and remove/add
     * revert/redo restore exact ids). */
    if (!break_editor_doc_has_entity(doc, self->id)) return false;
    break_editor_doc_slot_set(doc, self->id.index, self->id.generation,
                              self->other_name);
    return true;
}

static bool rename_revert(BreakEditorCmd *self, BreakEditorDoc *doc) {
    if (!break_editor_doc_has_entity(doc, self->id)) return false;
    break_editor_doc_slot_set(doc, self->id.index, self->id.generation,
                              self->name);
    return true;
}

static void rename_describe(const BreakEditorCmd *self, char buf[128]) {
    snprintf(buf, 128, "rename entity '%.40s' -> '%.40s' (%u:%u)", self->name,
             self->other_name, self->id.index, self->id.generation);
}

BreakEditorCmd *break_editor_cmd_rename_entity_create(BreakEditorDoc *doc,
                                                      BreakEditorEntityId id,
                                                      const char *new_name) {
    if (!break_editor_doc_has_entity(doc, id)) return NULL;
    BreakEditorCmd *cmd = break_editor_test_calloc(sizeof(*cmd));
    if (!cmd) return NULL;
    cmd->apply = rename_apply;
    cmd->revert = rename_revert;
    cmd->destroy = cmd_destroy;
    cmd->describe = rename_describe;
    cmd->kind = BREAK_EDITOR_CMD_KIND_RENAME_ENTITY;
    cmd->id = id;
    memcpy(cmd->name, doc->slots[id.index].name, BREAK_EDITOR_NAME_CAPACITY);
    /* Caller already rejected over-cap names: NUL within 128 bytes. */
    break_editor_name_copy(cmd->other_name, new_name);
    return cmd;
}
