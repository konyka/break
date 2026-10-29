/* BreakEditorDoc implementation — see editor_doc.h for the contract
 * (bounded name map, command-routed mutations, single owner thread). */

#include <editor/editor_doc.h>

#include <editor/editor_internal.h>
#include <editor/editor_test_hooks.h>

#include <stdlib.h>
#include <string.h>

#if defined(BREAK_EDITOR_TESTING)
_Atomic u64 g_break_editor_test_alloc_budget = BREAK_EDITOR_TEST_ALLOC_DISABLED;
#endif

/* Bounded name-length check: reads at most BREAK_EDITOR_NAME_CAPACITY
 * bytes; a NUL within the first 128 bytes means the name fits (≤127
 * visible chars). NULL is reported as fitting — callers decide whether
 * NULL is acceptable (add: yes, generates; rename: no). */
static bool name_fits(const char *name) {
    if (!name) return true;
    for (usize i = 0; i < BREAK_EDITOR_NAME_CAPACITY; i++) {
        if (name[i] == '\0') return true;
    }
    return false;
}

BreakEditorDoc *break_editor_doc_create(void) {
    BreakEditorDoc *doc = break_editor_test_calloc(sizeof(*doc));
    if (!doc) return NULL;

    doc->world = world_create();
    if (!doc->world) {
        free(doc);
        return NULL;
    }

    doc->slots =
        break_editor_test_calloc(sizeof(BreakEditorNameSlot) * ECS_MAX_ENTITIES);
    if (!doc->slots) {
        world_destroy(doc->world);
        free(doc);
        return NULL;
    }

    doc->stack = break_editor_cmd_stack_create(0);
    if (!doc->stack) {
        free(doc->slots);
        world_destroy(doc->world);
        free(doc);
        return NULL;
    }

    /* Task 3: editable-component registry + World registration (no
     * allocation, never fails). */
    break_editor_doc_init_components(doc);

    return doc;
}

void break_editor_doc_destroy(BreakEditorDoc *doc) {
    if (!doc) return;
    break_editor_cmd_stack_destroy(doc->stack);
    free(doc->slots);
    world_destroy(doc->world);
    break_editor_doc_kept_chunks_free(doc);
    free(doc);
}

void *break_editor_doc_world(BreakEditorDoc *doc) {
    return doc ? (void *)doc->world : NULL;
}

World *break_editor_doc_world_raw(BreakEditorDoc *doc) {
    return doc ? doc->world : NULL;
}

bool break_editor_doc_has_entity(const BreakEditorDoc *doc,
                                 BreakEditorEntityId id) {
    if (!doc || !break_editor_entity_id_valid(id) ||
        id.index >= ECS_MAX_ENTITIES) {
        return false;
    }
    return doc->slots[id.index].generation == id.generation;
}

void break_editor_doc_slot_set(BreakEditorDoc *doc, u32 index, u32 generation,
                               const char *name) {
    if (!doc || index >= ECS_MAX_ENTITIES) return;
    if (doc->slots[index].generation == 0) doc->named_count++;
    doc->slots[index].generation = generation;
    memcpy(doc->slots[index].name, name, BREAK_EDITOR_NAME_CAPACITY);
}

void break_editor_doc_slot_clear(BreakEditorDoc *doc, u32 index) {
    if (!doc || index >= ECS_MAX_ENTITIES) return;
    if (doc->slots[index].generation != 0) doc->named_count--;
    doc->slots[index].generation = 0;
    doc->slots[index].name[0] = '\0';
}

BreakEditorEntityId break_editor_doc_add_entity(BreakEditorDoc *doc,
                                                const char *name) {
    if (!doc) return BREAK_EDITOR_ENTITY_NULL;
    if (name && !name_fits(name)) {
        return BREAK_EDITOR_ENTITY_NULL; /* over-cap: rejected, no truncate */
    }
    BreakEditorCmd *cmd = break_editor_cmd_add_entity_create(name);
    if (!cmd) return BREAK_EDITOR_ENTITY_NULL;
    if (!cmd->apply(cmd, doc)) {
        cmd->destroy(cmd);
        return BREAK_EDITOR_ENTITY_NULL;
    }
    break_editor_cmd_stack_push_applied(doc, cmd);
    doc->dirty = true;
    return cmd->id;
}

bool break_editor_doc_remove_entity(BreakEditorDoc *doc,
                                    BreakEditorEntityId id) {
    if (!doc || !break_editor_entity_id_valid(id)) return false;
    BreakEditorCmd *cmd = break_editor_cmd_remove_entity_create(doc, id);
    if (!cmd) return false; /* nonexistent/stale id or OOM: bounded false */
    if (!cmd->apply(cmd, doc)) {
        cmd->destroy(cmd);
        return false;
    }
    break_editor_cmd_stack_push_applied(doc, cmd);
    doc->dirty = true;
    return true;
}

bool break_editor_doc_rename_entity(BreakEditorDoc *doc,
                                    BreakEditorEntityId id,
                                    const char *name) {
    if (!doc || !break_editor_entity_id_valid(id)) return false;
    if (!name || !name_fits(name)) {
        return false; /* over-cap/NULL rename: rejected, no truncate */
    }
    BreakEditorCmd *cmd = break_editor_cmd_rename_entity_create(doc, id, name);
    if (!cmd) return false; /* nonexistent/stale id or OOM: bounded false */
    if (!cmd->apply(cmd, doc)) {
        cmd->destroy(cmd);
        return false;
    }
    break_editor_cmd_stack_push_applied(doc, cmd);
    doc->dirty = true;
    return true;
}

usize break_editor_doc_entity_count(const BreakEditorDoc *doc) {
    return doc ? doc->named_count : 0u;
}

bool break_editor_doc_entity_at(const BreakEditorDoc *doc, usize i,
                                BreakEditorEntityId *out_id,
                                const char **out_name) {
    if (!doc || !out_id || !out_name || i >= doc->named_count) return false;
    /* Stable ordering: ascending entity index. Index 0 is the ECS
     * ENTITY_NULL sentinel and never carries a slot. O(i + index) scan; the
     * outliner list view is virtualized, so only visible rows are asked. */
    for (u32 idx = 1; idx < ECS_MAX_ENTITIES; idx++) {
        if (doc->slots[idx].generation == 0) continue;
        if (i == 0) {
            out_id->index = idx;
            out_id->generation = doc->slots[idx].generation;
            *out_name = doc->slots[idx].name;
            return true;
        }
        i--;
    }
    return false;
}

bool break_editor_doc_is_dirty(const BreakEditorDoc *doc) {
    return doc ? doc->dirty : false;
}

void break_editor_doc_clear_dirty(BreakEditorDoc *doc) {
    if (doc) doc->dirty = false;
}

BreakEditorCmdStack *break_editor_doc_stack(BreakEditorDoc *doc) {
    return doc ? doc->stack : NULL;
}
