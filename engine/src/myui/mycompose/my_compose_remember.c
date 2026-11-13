#include <myui/mycompose/my_compose_internal.h>

#include <string.h>

static uint32_t find_remember_slot(const MyComposeTreeBuilder *builder,
    MyComposeNodeHandle owner, uint32_t local_slot) {
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_REMEMBER_SLOTS; ++i) {
        const MyComposeRememberSlot *slot = &builder->remember_slots[i];
        if (slot->state != MY_COMPOSE_REMEMBER_FREE &&
            slot->owner.index == owner.index &&
            slot->owner.generation == owner.generation &&
            slot->local_slot == local_slot) {
            return i;
        }
    }
    return MY_COMPOSE_NO_INDEX;
}

static void dispose_remember_slot(MyComposeRememberSlot *slot) {
    if (slot->ops.dispose != NULL) {
        slot->ops.dispose(slot->ops.context, slot->storage.bytes, slot->size);
    }
    memset(slot, 0, sizeof(*slot));
}

static void dispose_current_nodes(MyComposeTreeBuilder *builder,
    const MyComposeTree *next, bool dispose_all) {
    const MyComposeTree *current = builder->current;
    uint32_t max_depth = 0u;
    for (uint32_t i = 0u; i < current->node_count; ++i) {
        if (current->nodes[i].depth > max_depth) {
            max_depth = current->nodes[i].depth;
        }
    }
    for (uint32_t depth = max_depth; depth != 0u; --depth) {
        for (uint32_t i = current->node_count; i-- != 0u;) {
            const MyComposeNodeRecord *node = &current->nodes[i];
            if (node->depth != depth ||
                (!dispose_all &&
                    my_compose_tree_internal_old_node_is_retained(next, i))) {
                continue;
            }
            for (uint32_t local = MY_COMPOSE_REMEMBER_SLOTS_PER_NODE;
                 local-- != 0u;) {
                uint32_t slot_index = find_remember_slot(builder, node->handle,
                    local);
                if (slot_index == MY_COMPOSE_NO_INDEX) continue;
                MyComposeRememberSlot *slot =
                    &builder->remember_slots[slot_index];
                if (slot->state == MY_COMPOSE_REMEMBER_CURRENT) {
                    dispose_remember_slot(slot);
                }
            }
        }
    }
}

void my_compose_remember_abort(MyComposeTreeBuilder *builder) {
    for (uint32_t i = MY_COMPOSE_MAX_REMEMBER_SLOTS; i-- != 0u;) {
        MyComposeRememberSlot *slot = &builder->remember_slots[i];
        if (slot->state == MY_COMPOSE_REMEMBER_CANDIDATE) {
            dispose_remember_slot(slot);
        }
    }
}

void my_compose_remember_finalize(MyComposeTreeBuilder *builder) {
    dispose_current_nodes(builder, builder->next, false);
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_REMEMBER_SLOTS; ++i) {
        MyComposeRememberSlot *slot = &builder->remember_slots[i];
        if (slot->state == MY_COMPOSE_REMEMBER_CANDIDATE) {
            slot->state = MY_COMPOSE_REMEMBER_CURRENT;
        }
    }
}

void my_compose_remember_destroy(MyComposeTreeBuilder *builder) {
    my_compose_remember_abort(builder);
    dispose_current_nodes(builder, NULL, true);
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_REMEMBER_SLOTS; ++i) {
        MyComposeRememberSlot *slot = &builder->remember_slots[i];
        if (slot->state != MY_COMPOSE_REMEMBER_FREE) {
            dispose_remember_slot(slot);
        }
    }
}

void my_compose_remember_reseed(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle handle, uint32_t generation) {
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_REMEMBER_SLOTS; ++i) {
        MyComposeRememberSlot *slot = &builder->remember_slots[i];
        if (slot->state == MY_COMPOSE_REMEMBER_CURRENT &&
            slot->owner.index == handle.index &&
            slot->owner.generation == handle.generation) {
            slot->owner.generation = generation;
        }
    }
}

MyComposeStatus my_compose_tree_builder_remember(
    MyComposeTreeBuilder *builder, MyComposeNodeHandle owner,
    uint32_t local_slot, uint64_t type_tag, uint32_t size, uint32_t alignment,
    const MyComposeRememberOps *ops, void **out_storage) {
    if (builder == NULL || out_storage == NULL) return MY_COMPOSE_INVALID;
    if (builder->state != MY_COMPOSE_BUILD_NODES) return MY_COMPOSE_INVALID;
    if (local_slot >= MY_COMPOSE_REMEMBER_SLOTS_PER_NODE ||
        size > MY_COMPOSE_REMEMBER_BYTES ||
        alignment > MY_COMPOSE_MAX_ALIGNMENT) {
        return MY_COMPOSE_OVERLOAD;
    }
    if (size == 0u || alignment == 0u ||
        (alignment & (alignment - 1u)) != 0u) {
        return MY_COMPOSE_INVALID;
    }
    if (my_compose_tree_internal_find_node(builder->next, owner) ==
        MY_COMPOSE_NO_INDEX) {
        return MY_COMPOSE_STALE;
    }

    uint32_t slot_index = find_remember_slot(builder, owner, local_slot);
    if (slot_index != MY_COMPOSE_NO_INDEX) {
        MyComposeRememberSlot *slot = &builder->remember_slots[slot_index];
        if (slot->type_tag != type_tag) return MY_COMPOSE_TYPE_MISMATCH;
        *out_storage = slot->storage.bytes;
        return MY_COMPOSE_OK;
    }

    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_REMEMBER_SLOTS; ++i) {
        if (builder->remember_slots[i].state == MY_COMPOSE_REMEMBER_FREE) {
            slot_index = i;
            break;
        }
    }
    if (slot_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_OVERLOAD;

    MyComposeRememberSlot *slot = &builder->remember_slots[slot_index];
    memset(slot, 0, sizeof(*slot));
    slot->owner = owner;
    slot->local_slot = local_slot;
    slot->type_tag = type_tag;
    slot->size = size;
    slot->alignment = alignment;
    if (ops != NULL) slot->ops = *ops;
    slot->state = MY_COMPOSE_REMEMBER_CANDIDATE;
    *out_storage = slot->storage.bytes;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_tree_builder_remember_get(
    const MyComposeTreeBuilder *builder, MyComposeNodeHandle owner,
    uint32_t local_slot, void **out_storage) {
    if (builder == NULL || out_storage == NULL) return MY_COMPOSE_INVALID;
    if (local_slot >= MY_COMPOSE_REMEMBER_SLOTS_PER_NODE) {
        return MY_COMPOSE_OVERLOAD;
    }
    if (my_compose_tree_internal_find_node(builder->current, owner) ==
        MY_COMPOSE_NO_INDEX) {
        return MY_COMPOSE_STALE;
    }
    uint32_t slot_index = find_remember_slot(builder, owner, local_slot);
    if (slot_index == MY_COMPOSE_NO_INDEX ||
        builder->remember_slots[slot_index].state !=
            MY_COMPOSE_REMEMBER_CURRENT) {
        return MY_COMPOSE_FAILED;
    }
    *out_storage = (void *)builder->remember_slots[slot_index].storage.bytes;
    return MY_COMPOSE_OK;
}
