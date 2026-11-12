#include <myui/mycompose/my_compose_internal.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static bool handle_is_zero(MyComposeNodeHandle handle) {
    return handle.index == 0u && handle.generation == 0u;
}

static MyComposeStatus bounded_string(const char *text, uint32_t capacity,
    uint32_t *length) {
    if (text == NULL) return MY_COMPOSE_INVALID;
    for (uint32_t i = 0u; i < capacity; ++i) {
        if (text[i] == '\0') {
            *length = i;
            return MY_COMPOSE_OK;
        }
    }
    return MY_COMPOSE_OVERLOAD;
}

static uint32_t find_node(const MyComposeTree *tree,
    MyComposeNodeHandle handle) {
    if (handle_is_zero(handle)) return MY_COMPOSE_NO_INDEX;
    for (uint32_t i = 0u; i < tree->node_count; ++i) {
        if (tree->nodes[i].handle.index == handle.index &&
            tree->nodes[i].handle.generation == handle.generation) {
            return i;
        }
    }
    return MY_COMPOSE_NO_INDEX;
}

static uint32_t find_property(const MyComposeTree *tree,
    const MyComposeNodeRecord *node, const char *name) {
    uint32_t index = node->first_property;
    while (index != MY_COMPOSE_NO_INDEX) {
        const MyComposePropertyRecord *property = &tree->properties[index];
        if (strcmp(tree->strings + property->name_offset, name) == 0) return index;
        index = property->next;
    }
    return MY_COMPOSE_NO_INDEX;
}

static uint32_t find_event(const MyComposeTree *tree,
    const MyComposeNodeRecord *node, const char *name) {
    uint32_t index = node->first_event;
    while (index != MY_COMPOSE_NO_INDEX) {
        const MyComposeEventRecord *event = &tree->events[index];
        if (strcmp(tree->strings + event->name_offset, name) == 0) return index;
        index = event->next;
    }
    return MY_COMPOSE_NO_INDEX;
}

static uint32_t copy_string(MyComposeTree *tree, const char *text,
    uint32_t length) {
    uint32_t offset = tree->string_used;
    if (length != 0u) memcpy(tree->strings + offset, text, length);
    tree->strings[offset + length] = '\0';
    tree->string_used += length + 1u;
    return offset;
}

static bool arena_has_room(const MyComposeTree *tree, uint32_t needed) {
    return needed <= MY_COMPOSE_STRING_BYTES - tree->string_used;
}

static uint32_t current_child_at(const MyComposeTree *tree,
    const MyComposeNodeRecord *parent, uint32_t position) {
    uint32_t index = parent->first_child;
    while (index != MY_COMPOSE_NO_INDEX) {
        uint32_t node_index = tree->child_links[index].node;
        if (tree->nodes[node_index].child_index == position) return node_index;
        index = tree->child_links[index].next;
    }
    return MY_COMPOSE_NO_INDEX;
}

static bool old_node_is_reused(const MyComposeTree *next, uint32_t old_index);

static uint32_t find_free_slot(MyComposeTreeBuilder *builder) {
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES; ++i) {
        const MyComposeSlot *slot = &builder->slots[i];
        if (!slot->in_use && !slot->retired && !slot->reserved &&
            slot->generation != UINT32_MAX) {
            return i;
        }
    }
    return MY_COMPOSE_NO_INDEX;
}

MyComposeTreeBuilder *my_compose_tree_builder_create(void) {
    MyComposeTreeBuilder *builder = calloc(1u, sizeof(*builder));
    if (builder == NULL) return NULL;
    builder->current = &builder->storage[0];
    builder->next = &builder->storage[1];
    builder->diff.ops = builder->diff_ops;
    builder->state = MY_COMPOSE_BUILD_IDLE;
    return builder;
}

void my_compose_tree_builder_destroy(MyComposeTreeBuilder *builder) {
    if (builder != NULL) my_compose_remember_destroy(builder);
    free(builder);
}

MyComposeStatus my_compose_tree_builder_begin(MyComposeTreeBuilder *builder) {
    if (builder == NULL) return MY_COMPOSE_INVALID;
    my_compose_remember_abort(builder);
    memset(builder->next, 0, sizeof(*builder->next));
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES; ++i) {
        builder->slots[i].next_generation = builder->slots[i].generation;
        builder->slots[i].reserved = false;
    }
    builder->diff.count = 0u;
    builder->state = MY_COMPOSE_BUILD_NODES;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_tree_builder_node(MyComposeTreeBuilder *builder,
    const MyComposeNodeDesc *desc, MyComposeNodeHandle *out) {
    if (builder == NULL || desc == NULL || out == NULL) return MY_COMPOSE_INVALID;
    if (builder->state != MY_COMPOSE_BUILD_NODES) return MY_COMPOSE_INVALID;

    uint32_t type_length;
    MyComposeStatus status = bounded_string(desc->type, MY_COMPOSE_TYPE_BYTES,
        &type_length);
    if (status != MY_COMPOSE_OK) return status;
    if (type_length == 0u) return MY_COMPOSE_INVALID;
    uint32_t key_length = 0u;
    if (desc->key != NULL) {
        status = bounded_string(desc->key, MY_COMPOSE_KEY_BYTES, &key_length);
        if (status != MY_COMPOSE_OK) return status;
    }
    bool keyed = desc->key != NULL && key_length != 0u;
    MyComposeTree *tree = builder->next;
    bool is_root = tree->node_count == 0u;
    uint32_t parent_index = MY_COMPOSE_NO_INDEX;
    uint32_t depth = 1u;
    uint32_t child_index = 0u;

    if (is_root) {
        if (!handle_is_zero(desc->parent) || strcmp(desc->type, "@root") != 0) {
            return MY_COMPOSE_INVALID;
        }
    } else {
        if (handle_is_zero(desc->parent) || strcmp(desc->type, "@root") == 0) {
            return MY_COMPOSE_INVALID;
        }
        parent_index = find_node(tree, desc->parent);
        if (parent_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_STALE;
        MyComposeNodeRecord *parent = &tree->nodes[parent_index];
        depth = parent->depth + 1u;
        if (depth > MY_COMPOSE_MAX_DEPTH) return MY_COMPOSE_OVERLOAD;
        child_index = parent->child_count;
        if (keyed) {
            uint32_t link = parent->first_child;
            while (link != MY_COMPOSE_NO_INDEX) {
                const MyComposeNodeRecord *sibling =
                    &tree->nodes[tree->child_links[link].node];
                if (sibling->key_offset != MY_COMPOSE_NO_INDEX &&
                    strcmp(tree->strings + sibling->key_offset, desc->key) == 0) {
                    return MY_COMPOSE_DUPLICATE_KEY;
                }
                link = tree->child_links[link].next;
            }
        }
    }

    if (tree->node_count >= MY_COMPOSE_MAX_NODES) return MY_COMPOSE_OVERLOAD;
    if (!is_root && tree->child_link_count >= MY_COMPOSE_MAX_CHILD_LINKS) {
        return MY_COMPOSE_OVERLOAD;
    }
    uint32_t arena_needed = type_length + 1u;
    if (keyed) arena_needed += key_length + 1u;
    if (!arena_has_room(tree, arena_needed)) return MY_COMPOSE_OVERLOAD;

    uint32_t previous = MY_COMPOSE_NO_INDEX;
    MyComposeMatch match = MY_COMPOSE_MATCH_NONE;
    if (is_root && builder->current->node_count != 0u) {
        previous = 0u;
        match = MY_COMPOSE_MATCH_NODE;
    } else if (!is_root) {
        const MyComposeNodeRecord *next_parent = &tree->nodes[parent_index];
        if (next_parent->match == MY_COMPOSE_MATCH_NODE) {
            const MyComposeTree *current = builder->current;
            const MyComposeNodeRecord *old_parent =
                &current->nodes[next_parent->previous];
            uint32_t old_index = MY_COMPOSE_NO_INDEX;
            if (keyed) {
                uint32_t link = old_parent->first_child;
                while (link != MY_COMPOSE_NO_INDEX) {
                    uint32_t candidate_index = current->child_links[link].node;
                    const MyComposeNodeRecord *candidate =
                        &current->nodes[candidate_index];
                    if (candidate->key_offset != MY_COMPOSE_NO_INDEX &&
                        strcmp(current->strings + candidate->key_offset,
                            desc->key) == 0) {
                        old_index = candidate_index;
                        break;
                    }
                    link = current->child_links[link].next;
                }
            } else {
                uint32_t candidate_index = current_child_at(current, old_parent,
                    child_index);
                if (candidate_index != MY_COMPOSE_NO_INDEX &&
                    current->nodes[candidate_index].key_offset == MY_COMPOSE_NO_INDEX) {
                    old_index = candidate_index;
                }
            }
            if (old_index != MY_COMPOSE_NO_INDEX) {
                previous = old_index;
                if (strcmp(current->strings + current->nodes[old_index].type_offset,
                        desc->type) == 0) {
                    match = MY_COMPOSE_MATCH_NODE;
                } else {
                    match = MY_COMPOSE_MATCH_REPLACE;
                }
            }
        }
    }
    if (match == MY_COMPOSE_MATCH_NONE &&
        find_free_slot(builder) == MY_COMPOSE_NO_INDEX) {
        const MyComposeTree *current = builder->current;
        for (uint32_t i = 0u; i < current->node_count; ++i) {
            const MyComposeNodeRecord *candidate = &current->nodes[i];
            const MyComposeSlot *slot = &builder->slots[candidate->handle.index];
            if (old_node_is_reused(tree, i) || slot->reserved ||
                candidate->handle.generation >= UINT32_MAX - 1u) {
                continue;
            }
            previous = i;
            match = MY_COMPOSE_MATCH_REPLACE;
            break;
        }
    }

    MyComposeNodeHandle handle = {0u, 0u};
    uint32_t slot_index = MY_COMPOSE_NO_INDEX;
    if (match == MY_COMPOSE_MATCH_NODE) {
        handle = builder->current->nodes[previous].handle;
        slot_index = handle.index;
        if (builder->slots[slot_index].next_generation < handle.generation) {
            builder->slots[slot_index].next_generation = handle.generation;
        }
    } else if (match == MY_COMPOSE_MATCH_REPLACE) {
        handle = builder->current->nodes[previous].handle;
        slot_index = handle.index;
        MyComposeSlot *slot = &builder->slots[slot_index];
        uint32_t base_generation = slot->next_generation;
        if (base_generation < handle.generation) base_generation = handle.generation;
        handle.generation = base_generation == UINT32_MAX ? UINT32_MAX :
            base_generation + 1u;
        slot->next_generation = handle.generation;
    } else {
        slot_index = find_free_slot(builder);
        if (slot_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_OVERLOAD;
        handle.index = slot_index;
        handle.generation = builder->slots[slot_index].next_generation;
        if (handle.generation == 0u) handle.generation = 1u;
        builder->slots[slot_index].next_generation = handle.generation;
    }
    if (slot_index >= MY_COMPOSE_MAX_NODES) return MY_COMPOSE_FAILED;
    builder->slots[slot_index].reserved = true;

    uint32_t node_index = tree->node_count;
    MyComposeNodeRecord *node = &tree->nodes[node_index];
    memset(node, 0, sizeof(*node));
    node->handle = handle;
    node->parent = parent_index;
    node->previous = previous;
    node->match = match;
    node->key_offset = keyed ? copy_string(tree, desc->key, key_length) :
        MY_COMPOSE_NO_INDEX;
    node->type_offset = copy_string(tree, desc->type, type_length);
    node->depth = depth;
    node->child_index = child_index;
    node->first_child = MY_COMPOSE_NO_INDEX;
    node->last_child = MY_COMPOSE_NO_INDEX;
    node->first_property = MY_COMPOSE_NO_INDEX;
    node->last_property = MY_COMPOSE_NO_INDEX;
    node->first_event = MY_COMPOSE_NO_INDEX;
    node->last_event = MY_COMPOSE_NO_INDEX;
    tree->node_count++;

    if (!is_root) {
        MyComposeNodeRecord *parent = &tree->nodes[parent_index];
        uint32_t link_index = tree->child_link_count++;
        MyComposeChildLink *link = &tree->child_links[link_index];
        link->node = node_index;
        link->next = MY_COMPOSE_NO_INDEX;
        if (parent->last_child == MY_COMPOSE_NO_INDEX) {
            parent->first_child = link_index;
        } else {
            tree->child_links[parent->last_child].next = link_index;
        }
        parent->last_child = link_index;
        parent->child_count++;
    }
    *out = handle;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_tree_builder_property(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle owner, const char *name, const MyComposeValue *value) {
    if (builder == NULL || name == NULL || value == NULL) return MY_COMPOSE_INVALID;
    if (builder->state != MY_COMPOSE_BUILD_NODES) return MY_COMPOSE_INVALID;
    MyComposeTree *tree = builder->next;
    uint32_t node_index = find_node(tree, owner);
    if (node_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_STALE;
    MyComposeNodeRecord *node = &tree->nodes[node_index];
    uint32_t name_length;
    MyComposeStatus status = bounded_string(name, MY_COMPOSE_NAME_BYTES,
        &name_length);
    if (status != MY_COMPOSE_OK) return status;
    if (name_length == 0u) return MY_COMPOSE_INVALID;
    if (find_property(tree, node, name) != MY_COMPOSE_NO_INDEX) {
        return MY_COMPOSE_CONFLICT;
    }
    if (value->type < MY_COMPOSE_VALUE_NONE ||
        value->type > MY_COMPOSE_VALUE_COLOR) {
        return MY_COMPOSE_INVALID;
    }
    uint32_t arena_needed = name_length + 1u;
    if (value->type == MY_COMPOSE_VALUE_STRING) {
        if (value->as.string.size != 0u && value->as.string.data == NULL) {
            return MY_COMPOSE_INVALID;
        }
        if (value->as.string.size >= MY_COMPOSE_STRING_BYTES) {
            return MY_COMPOSE_OVERLOAD;
        }
        if (value->as.string.data != NULL && value->as.string.size != 0u &&
            memchr(value->as.string.data, '\0', value->as.string.size) != NULL) {
            return MY_COMPOSE_INVALID;
        }
        arena_needed += value->as.string.size + 1u;
    }
    if (tree->property_count >= MY_COMPOSE_MAX_PROPERTIES ||
        node->property_count >= MY_COMPOSE_MAX_PROPERTIES_PER_NODE) {
        return MY_COMPOSE_OVERLOAD;
    }
    if (!arena_has_room(tree, arena_needed)) return MY_COMPOSE_OVERLOAD;

    uint32_t property_index = tree->property_count;
    MyComposePropertyRecord *property = &tree->properties[property_index];
    property->name_offset = copy_string(tree, name, name_length);
    property->value = *value;
    if (value->type == MY_COMPOSE_VALUE_STRING) {
        uint32_t value_offset = copy_string(tree, value->as.string.data,
            value->as.string.size);
        property->value.as.string.data = tree->strings + value_offset;
    }
    property->next = MY_COMPOSE_NO_INDEX;
    if (node->last_property == MY_COMPOSE_NO_INDEX) {
        node->first_property = property_index;
    } else {
        tree->properties[node->last_property].next = property_index;
    }
    node->last_property = property_index;
    node->property_count++;
    tree->property_count++;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_tree_builder_event(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle owner, const char *name, const MyComposeIntent *intent) {
    if (builder == NULL || name == NULL || intent == NULL) return MY_COMPOSE_INVALID;
    if (builder->state != MY_COMPOSE_BUILD_NODES) return MY_COMPOSE_INVALID;
    MyComposeTree *tree = builder->next;
    uint32_t node_index = find_node(tree, owner);
    if (node_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_STALE;
    MyComposeNodeRecord *node = &tree->nodes[node_index];
    uint32_t name_length;
    MyComposeStatus status = bounded_string(name, MY_COMPOSE_NAME_BYTES,
        &name_length);
    if (status != MY_COMPOSE_OK) return status;
    if (name_length == 0u) return MY_COMPOSE_INVALID;
    if (find_event(tree, node, name) != MY_COMPOSE_NO_INDEX) {
        return MY_COMPOSE_CONFLICT;
    }
    if (intent->payload_size > MY_COMPOSE_MESSAGE_BYTES) return MY_COMPOSE_OVERLOAD;
    if (intent->payload_size != 0u && intent->payload == NULL) {
        return MY_COMPOSE_INVALID;
    }
    if (tree->event_count >= MY_COMPOSE_MAX_EVENTS ||
        node->event_count >= MY_COMPOSE_MAX_EVENTS_PER_NODE) {
        return MY_COMPOSE_OVERLOAD;
    }
    if (!arena_has_room(tree, name_length + 1u)) return MY_COMPOSE_OVERLOAD;

    uint32_t event_index = tree->event_count;
    MyComposeEventRecord *event = &tree->events[event_index];
    event->name_offset = copy_string(tree, name, name_length);
    event->type = intent->type;
    event->payload_size = intent->payload_size;
    event->result = intent->result;
    if (intent->payload_size != 0u) {
        memcpy(event->payload, intent->payload, intent->payload_size);
    }
    event->next = MY_COMPOSE_NO_INDEX;
    if (node->last_event == MY_COMPOSE_NO_INDEX) {
        node->first_event = event_index;
    } else {
        tree->events[node->last_event].next = event_index;
    }
    node->last_event = event_index;
    node->event_count++;
    tree->event_count++;
    return MY_COMPOSE_OK;
}

static MyComposeStatus prepare_diff(MyComposeTreeBuilder *builder);

MyComposeStatus my_compose_tree_builder_end(MyComposeTreeBuilder *builder) {
    return prepare_diff(builder);
}

static bool value_equal(const MyComposeValue *a, const MyComposeValue *b) {
    if (a->type != b->type) return false;
    switch (a->type) {
        case MY_COMPOSE_VALUE_NONE:
            return true;
        case MY_COMPOSE_VALUE_BOOL:
            return a->as.bool_value == b->as.bool_value;
        case MY_COMPOSE_VALUE_INT32:
            return a->as.int32_value == b->as.int32_value;
        case MY_COMPOSE_VALUE_UINT32:
            return a->as.uint32_value == b->as.uint32_value;
        case MY_COMPOSE_VALUE_INT64:
            return a->as.int64_value == b->as.int64_value;
        case MY_COMPOSE_VALUE_FLOAT: {
            uint32_t a_bits;
            uint32_t b_bits;
            memcpy(&a_bits, &a->as.float_value, sizeof(a_bits));
            memcpy(&b_bits, &b->as.float_value, sizeof(b_bits));
            return a_bits == b_bits;
        }
        case MY_COMPOSE_VALUE_DOUBLE: {
            uint64_t a_bits;
            uint64_t b_bits;
            memcpy(&a_bits, &a->as.double_value, sizeof(a_bits));
            memcpy(&b_bits, &b->as.double_value, sizeof(b_bits));
            return a_bits == b_bits;
        }
        case MY_COMPOSE_VALUE_STRING:
            return a->as.string.size == b->as.string.size &&
                (a->as.string.size == 0u ||
                    memcmp(a->as.string.data, b->as.string.data,
                        a->as.string.size) == 0);
        case MY_COMPOSE_VALUE_COLOR:
            return a->as.color == b->as.color;
    }
    return false;
}

static bool event_equal(const MyComposeEventRecord *a,
    const MyComposeEventRecord *b) {
    return a->type == b->type && a->payload_size == b->payload_size &&
        a->result == b->result &&
        (a->payload_size == 0u ||
            memcmp(a->payload, b->payload, a->payload_size) == 0);
}

static bool append_diff(MyComposeTreeBuilder *builder, MyComposeDiffType type,
    MyComposeNodeHandle node, MyComposeNodeHandle parent, uint32_t from_index,
    uint32_t to_index, const char *name, bool on_event) {
    if (builder->diff.count >= MY_COMPOSE_MAX_DIFF_OPS) return false;
    MyComposeDiffOp *op = &builder->diff_ops[builder->diff.count++];
    op->type = type;
    op->node = node;
    op->parent = parent;
    op->from_index = from_index;
    op->to_index = to_index;
    op->name = name;
    op->on_event = on_event;
    return true;
}

static MyComposeNodeHandle parent_handle(const MyComposeTree *tree,
    const MyComposeNodeRecord *node) {
    if (node->parent == MY_COMPOSE_NO_INDEX) {
        MyComposeNodeHandle zero = {0u, 0u};
        return zero;
    }
    return tree->nodes[node->parent].handle;
}

static bool old_node_is_retained(const MyComposeTree *next,
    uint32_t old_index) {
    for (uint32_t i = 0u; i < next->node_count; ++i) {
        if (next->nodes[i].previous == old_index &&
            next->nodes[i].match == MY_COMPOSE_MATCH_NODE) {
            return true;
        }
    }
    return false;
}

uint32_t my_compose_tree_internal_find_node(const MyComposeTree *tree,
    MyComposeNodeHandle handle) {
    return find_node(tree, handle);
}

bool my_compose_tree_internal_old_node_is_retained(const MyComposeTree *next,
    uint32_t old_index) {
    return old_node_is_retained(next, old_index);
}

static bool build_delete_diff(MyComposeTreeBuilder *builder) {
    const MyComposeTree *current = builder->current;
    const MyComposeTree *next = builder->next;
    uint32_t max_depth = 0u;
    for (uint32_t i = 0u; i < current->node_count; ++i) {
        if (current->nodes[i].depth > max_depth) max_depth = current->nodes[i].depth;
    }
    for (uint32_t depth = max_depth; depth != 0u; --depth) {
        for (uint32_t i = current->node_count; i-- != 0u;) {
            const MyComposeNodeRecord *node = &current->nodes[i];
            if (node->depth == depth && !old_node_is_retained(next, i)) {
                if (!append_diff(builder, MY_COMPOSE_DIFF_DELETE, node->handle,
                        parent_handle(current, node), node->child_index,
                        MY_COMPOSE_NO_INDEX, NULL, false)) {
                    return false;
                }
            }
        }
    }
    return true;
}

static uint32_t retained_next_index(const MyComposeTree *next,
    uint32_t old_index) {
    for (uint32_t i = 0u; i < next->node_count; ++i) {
        if (next->nodes[i].previous == old_index &&
            next->nodes[i].match == MY_COMPOSE_MATCH_NODE) {
            return i;
        }
    }
    return MY_COMPOSE_NO_INDEX;
}

static uint32_t work_find(const uint32_t *work, uint32_t count,
    uint32_t node_index) {
    for (uint32_t i = 0u; i < count; ++i) {
        if (work[i] == node_index) return i;
    }
    return MY_COMPOSE_NO_INDEX;
}

static void work_insert(uint32_t *work, uint32_t *count, uint32_t position,
    uint32_t node_index) {
    for (uint32_t i = *count; i > position; --i) work[i] = work[i - 1u];
    work[position] = node_index;
    (*count)++;
}

static void work_move(uint32_t *work, uint32_t from, uint32_t to) {
    uint32_t node_index = work[from];
    if (from < to) {
        for (uint32_t i = from; i < to; ++i) work[i] = work[i + 1u];
    } else {
        for (uint32_t i = from; i > to; --i) work[i] = work[i - 1u];
    }
    work[to] = node_index;
}

static bool append_move_diff(MyComposeTreeBuilder *builder,
    const MyComposeNodeRecord *node, uint32_t from_index, uint32_t to_index) {
    return append_diff(builder, MY_COMPOSE_DIFF_MOVE, node->handle,
        parent_handle(builder->next, node), from_index, to_index, NULL, false);
}

static bool build_parent_move_diff(MyComposeTreeBuilder *builder,
    uint32_t parent_index) {
    const MyComposeTree *next = builder->next;
    const MyComposeTree *current = builder->current;
    const MyComposeNodeRecord *parent = &next->nodes[parent_index];
    if (parent->match != MY_COMPOSE_MATCH_NODE) return true;
    uint32_t work[MY_COMPOSE_MAX_CHILD_LINKS];
    uint32_t work_count = 0u;
    const MyComposeNodeRecord *old_parent = &current->nodes[parent->previous];
    uint32_t old_link = old_parent->first_child;
    while (old_link != MY_COMPOSE_NO_INDEX) {
        uint32_t old_index = current->child_links[old_link].node;
        uint32_t next_index = retained_next_index(next, old_index);
        if (next_index != MY_COMPOSE_NO_INDEX &&
            next->nodes[next_index].parent == parent_index) {
            work[work_count++] = next_index;
        }
        old_link = current->child_links[old_link].next;
    }

    uint32_t new_link = parent->first_child;
    while (new_link != MY_COMPOSE_NO_INDEX) {
        uint32_t next_index = next->child_links[new_link].node;
        if (next->nodes[next_index].match != MY_COMPOSE_MATCH_NODE) {
            work_insert(work, &work_count, next->nodes[next_index].child_index,
                next_index);
        }
        new_link = next->child_links[new_link].next;
    }

    uint32_t position = 0u;
    new_link = parent->first_child;
    while (new_link != MY_COMPOSE_NO_INDEX) {
        uint32_t next_index = next->child_links[new_link].node;
        const MyComposeNodeRecord *desired = &next->nodes[next_index];
        uint32_t work_index = work_find(work, work_count, next_index);
        if (work_index == MY_COMPOSE_NO_INDEX) return false;
        if (work_index != position) {
            if (desired->match == MY_COMPOSE_MATCH_NODE &&
                desired->key_offset != MY_COMPOSE_NO_INDEX) {
                work_move(work, work_index, position);
                if (!append_move_diff(builder, desired, work_index, position)) {
                    return false;
                }
            } else {
                uint32_t offender_index = work[position];
                const MyComposeNodeRecord *offender = &next->nodes[offender_index];
                if (offender->match != MY_COMPOSE_MATCH_NODE ||
                    offender->key_offset == MY_COMPOSE_NO_INDEX ||
                    offender->child_index <= position ||
                    offender->child_index >= work_count) {
                    return false;
                }
                work_move(work, position, offender->child_index);
                if (!append_move_diff(builder, offender, position,
                        offender->child_index)) {
                    return false;
                }
            }
        }
        if (work[position] != next_index) return false;
        position++;
        new_link = next->child_links[new_link].next;
    }
    return true;
}

static bool build_structural_diff(MyComposeTreeBuilder *builder) {
    const MyComposeTree *next = builder->next;
    for (uint32_t i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *node = &next->nodes[i];
        if (node->match != MY_COMPOSE_MATCH_NODE) {
            if (!append_diff(builder, MY_COMPOSE_DIFF_CREATE, node->handle,
                    parent_handle(next, node), MY_COMPOSE_NO_INDEX,
                    node->child_index, NULL, false)) {
                return false;
            }
        }
    }
    for (uint32_t i = 0u; i < next->node_count; ++i) {
        if (!build_parent_move_diff(builder, i)) return false;
    }
    return true;
}

static bool build_property_diff(MyComposeTreeBuilder *builder,
    const MyComposeNodeRecord *old_node, const MyComposeNodeRecord *new_node,
    MyComposeNodeHandle parent) {
    const MyComposeTree *current = builder->current;
    const MyComposeTree *next = builder->next;
    uint32_t old_index = old_node->first_property;
    while (old_index != MY_COMPOSE_NO_INDEX) {
        const MyComposePropertyRecord *old = &current->properties[old_index];
        const char *old_name = current->strings + old->name_offset;
        uint32_t new_index = find_property(next, new_node, old_name);
        if (new_index == MY_COMPOSE_NO_INDEX) {
            if (!append_diff(builder, MY_COMPOSE_DIFF_UPDATE, new_node->handle,
                    parent, old_node->child_index, new_node->child_index,
                    old_name, false)) {
                return false;
            }
        } else {
            const MyComposePropertyRecord *new = &next->properties[new_index];
            if (!value_equal(&old->value, &new->value) &&
                !append_diff(builder, MY_COMPOSE_DIFF_UPDATE, new_node->handle,
                    parent, old_node->child_index, new_node->child_index,
                    next->strings + new->name_offset, false)) {
                return false;
            }
        }
        old_index = old->next;
    }
    uint32_t new_index = new_node->first_property;
    while (new_index != MY_COMPOSE_NO_INDEX) {
        const MyComposePropertyRecord *new = &next->properties[new_index];
        const char *new_name = next->strings + new->name_offset;
        if (find_property(current, old_node, new_name) == MY_COMPOSE_NO_INDEX &&
            !append_diff(builder, MY_COMPOSE_DIFF_UPDATE, new_node->handle,
                parent, old_node->child_index, new_node->child_index,
                new_name, false)) {
            return false;
        }
        new_index = new->next;
    }
    return true;
}

static bool build_event_diff(MyComposeTreeBuilder *builder,
    const MyComposeNodeRecord *old_node, const MyComposeNodeRecord *new_node,
    MyComposeNodeHandle parent) {
    const MyComposeTree *current = builder->current;
    const MyComposeTree *next = builder->next;
    uint32_t old_index = old_node->first_event;
    while (old_index != MY_COMPOSE_NO_INDEX) {
        const MyComposeEventRecord *old = &current->events[old_index];
        const char *old_name = current->strings + old->name_offset;
        uint32_t new_index = find_event(next, new_node, old_name);
        if (new_index == MY_COMPOSE_NO_INDEX) {
            if (!append_diff(builder, MY_COMPOSE_DIFF_UPDATE, new_node->handle,
                    parent, old_node->child_index, new_node->child_index,
                    old_name, true)) {
                return false;
            }
        } else {
            const MyComposeEventRecord *new = &next->events[new_index];
            if (!event_equal(old, new) &&
                !append_diff(builder, MY_COMPOSE_DIFF_UPDATE, new_node->handle,
                    parent, old_node->child_index, new_node->child_index,
                    next->strings + new->name_offset, true)) {
                return false;
            }
        }
        old_index = old->next;
    }
    uint32_t new_index = new_node->first_event;
    while (new_index != MY_COMPOSE_NO_INDEX) {
        const MyComposeEventRecord *new = &next->events[new_index];
        const char *new_name = next->strings + new->name_offset;
        if (find_event(current, old_node, new_name) == MY_COMPOSE_NO_INDEX &&
            !append_diff(builder, MY_COMPOSE_DIFF_UPDATE, new_node->handle,
                parent, old_node->child_index, new_node->child_index,
                new_name, true)) {
            return false;
        }
        new_index = new->next;
    }
    return true;
}

static bool build_update_diff(MyComposeTreeBuilder *builder) {
    const MyComposeTree *next = builder->next;
    const MyComposeTree *current = builder->current;
    for (uint32_t i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *new_node = &next->nodes[i];
        if (new_node->match != MY_COMPOSE_MATCH_NODE) continue;
        const MyComposeNodeRecord *old_node = &current->nodes[new_node->previous];
        MyComposeNodeHandle parent = parent_handle(next, new_node);
        if (!build_property_diff(builder, old_node, new_node, parent) ||
            !build_event_diff(builder, old_node, new_node, parent)) {
            return false;
        }
    }
    return true;
}

static bool old_node_is_reused(const MyComposeTree *next, uint32_t old_index) {
    for (uint32_t i = 0u; i < next->node_count; ++i) {
        if (next->nodes[i].previous == old_index &&
            next->nodes[i].match != MY_COMPOSE_MATCH_NONE) {
            return true;
        }
    }
    return false;
}

static void publish_slots(MyComposeTreeBuilder *builder) {
    const MyComposeTree *current = builder->current;
    const MyComposeTree *next = builder->next;
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES; ++i) {
        builder->slots[i].reserved = false;
    }
    for (uint32_t i = 0u; i < current->node_count; ++i) {
        const MyComposeNodeRecord *old = &current->nodes[i];
        if (old_node_is_reused(next, i)) continue;
        MyComposeSlot *slot = &builder->slots[old->handle.index];
        uint32_t released_generation = old->handle.generation == UINT32_MAX ?
            UINT32_MAX : old->handle.generation + 1u;
        if (slot->next_generation < released_generation) {
            slot->next_generation = released_generation;
        }
        slot->in_use = false;
        if (slot->next_generation == UINT32_MAX) slot->retired = true;
    }
    for (uint32_t i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *node = &next->nodes[i];
        MyComposeSlot *slot = &builder->slots[node->handle.index];
        if (slot->next_generation < node->handle.generation) {
            slot->next_generation = node->handle.generation;
        }
        slot->in_use = true;
        slot->retired = false;
    }
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES; ++i) {
        MyComposeSlot *slot = &builder->slots[i];
        if (slot->generation < slot->next_generation) {
            slot->generation = slot->next_generation;
        }
        slot->next_generation = slot->generation;
    }
}

static bool next_handles_are_unique(const MyComposeTree *tree) {
    for (uint32_t i = 0u; i < tree->node_count; ++i) {
        for (uint32_t j = i + 1u; j < tree->node_count; ++j) {
            if (tree->nodes[i].handle.index == tree->nodes[j].handle.index &&
                tree->nodes[i].handle.generation == tree->nodes[j].handle.generation) {
                return false;
            }
        }
    }
    return true;
}

static MyComposeStatus prepare_diff(MyComposeTreeBuilder *builder) {
    if (builder == NULL) return MY_COMPOSE_INVALID;
    if (builder->state != MY_COMPOSE_BUILD_NODES ||
        builder->next->node_count == 0u) {
        return MY_COMPOSE_INVALID;
    }
    builder->diff.count = 0u;
    if (!next_handles_are_unique(builder->next)) {
        return MY_COMPOSE_CONFLICT;
    }
    if (!build_delete_diff(builder) || !build_structural_diff(builder) ||
        !build_update_diff(builder)) {
        builder->diff.count = 0u;
        return MY_COMPOSE_OVERLOAD;
    }
    builder->state = MY_COMPOSE_BUILD_ENDED;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_tree_builder_finalize(MyComposeTreeBuilder *builder) {
    MyComposeTree *published;
    if (builder == NULL) return MY_COMPOSE_INVALID;
    if (builder->state != MY_COMPOSE_BUILD_ENDED) return MY_COMPOSE_INVALID;
    for (uint32_t i = 0u; i < builder->next->node_count; ++i) {
        const MyComposeNodeRecord *node = &builder->next->nodes[i];
        if (node->match == MY_COMPOSE_MATCH_REPLACE &&
            node->handle.generation == UINT32_MAX) {
            builder->diff.count = 0u;
            return MY_COMPOSE_OVERLOAD;
        }
    }
    my_compose_remember_finalize(builder);
    publish_slots(builder);
    published = builder->current;
    builder->current = builder->next;
    builder->next = published;
    builder->state = MY_COMPOSE_BUILD_IDLE;
    return MY_COMPOSE_OK;
}

const MyComposeDiff *my_compose_tree_builder_diff(
    const MyComposeTreeBuilder *builder) {
    return builder == NULL ? NULL : &builder->diff;
}

uint32_t my_compose_tree_builder_current_node_count(
    const MyComposeTreeBuilder *builder) {
    return builder == NULL ? 0u : builder->current->node_count;
}

uint32_t my_compose_tree_builder_next_node_count(
    const MyComposeTreeBuilder *builder) {
    return builder == NULL ? 0u : builder->next->node_count;
}

MyComposeStatus my_compose_tree_builder_get_node(
    const MyComposeTreeBuilder *builder, MyComposeNodeHandle handle,
    MyComposeNodeDesc *out) {
    if (builder == NULL || out == NULL) return MY_COMPOSE_INVALID;
    uint32_t node_index = find_node(builder->current, handle);
    if (node_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_STALE;
    const MyComposeTree *tree = builder->current;
    const MyComposeNodeRecord *node = &tree->nodes[node_index];
    out->parent = parent_handle(tree, node);
    out->key = node->key_offset == MY_COMPOSE_NO_INDEX ? NULL :
        tree->strings + node->key_offset;
    out->type = tree->strings + node->type_offset;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_tree_builder_get_property(
    const MyComposeTreeBuilder *builder, MyComposeNodeHandle owner,
    const char *name, MyComposeValue *out) {
    if (builder == NULL || name == NULL || out == NULL) return MY_COMPOSE_INVALID;
    uint32_t node_index = find_node(builder->current, owner);
    if (node_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_STALE;
    const MyComposeTree *tree = builder->current;
    uint32_t property_index = find_property(tree, &tree->nodes[node_index], name);
    if (property_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_FAILED;
    *out = tree->properties[property_index].value;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_tree_builder_get_event(
    const MyComposeTreeBuilder *builder, MyComposeNodeHandle owner,
    const char *name, MyComposeIntent *out) {
    if (builder == NULL || name == NULL || out == NULL) return MY_COMPOSE_INVALID;
    uint32_t node_index = find_node(builder->current, owner);
    if (node_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_STALE;
    const MyComposeTree *tree = builder->current;
    uint32_t event_index = find_event(tree, &tree->nodes[node_index], name);
    if (event_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_FAILED;
    const MyComposeEventRecord *event = &tree->events[event_index];
    out->type = event->type;
    out->payload_size = event->payload_size;
    out->payload = event->payload;
    out->owner = owner;
    out->result = event->result;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_tree_builder_internal_seed_generation(
    MyComposeTreeBuilder *builder, MyComposeNodeHandle handle,
    uint32_t generation) {
    if (builder == NULL || generation == 0u) return MY_COMPOSE_INVALID;
    uint32_t node_index = find_node(builder->current, handle);
    if (node_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_STALE;
    MyComposeNodeRecord *node = &builder->current->nodes[node_index];
    node->handle.generation = generation;
    my_compose_remember_reseed(builder, handle, generation);
    MyComposeSlot *slot = &builder->slots[handle.index];
    slot->generation = generation;
    slot->next_generation = generation;
    slot->in_use = true;
    slot->retired = false;
    return MY_COMPOSE_OK;
}
