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
    doc->dirty = true;
    return true;
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
    /* Task 1 restores the entity id + display name only; component bytes
     * land with Task 3's add/remove-component commands. */
    if (!recreate_with_stored_id(doc, self->id)) return false;
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
    BreakEditorCmd *cmd = break_editor_test_calloc(sizeof(*cmd));
    if (!cmd) return NULL;
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
