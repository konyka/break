#include <kernel/break_kernel_internal.h>

#include <math.h>

#define INVENTORY_STRIDE (BREAK_KERNEL_MAX_ITEMS + 1u)

static size_t inventory_index(u32 slot, u32 item_id) {
    return (size_t)slot * INVENTORY_STRIDE + item_id;
}

BreakKernelError break_kernel_entity_actions_apply(BreakKernel *kernel,
                                               const BreakKernelEntityAction *actions,
                                               u32 count) {
    if (!kernel || (count > 0u && !actions)) return BREAK_KERNEL_INVALID;
    if (!break_kernel_is_owner(kernel)) return BREAK_KERNEL_REJECTED;
    if (count > BREAK_KERNEL_MAX_ENTITY_ACTIONS) return BREAK_KERNEL_OVERLOAD;
    for (u32 i = 0u; i < count; i++) {
        const BreakKernelEntityAction *action = &actions[i];
        u32 slot = break_kernel_actor_slot(kernel, action->entity);
        if (slot == UINT32_MAX) return BREAK_KERNEL_STALE;
        if (action->type == BREAK_KERNEL_ENTITY_SET_POSITION) {
            if (!isfinite(action->position.e[0]) ||
                !isfinite(action->position.e[1]) ||
                !isfinite(action->position.e[2])) {
                return BREAK_KERNEL_INVALID;
            }
            if (kernel->world->component_sizes[BREAK_KERNEL_POSITION_COMPONENT] < sizeof(Vec3) ||
                !world_get_component(kernel->world, action->entity,
                                     BREAK_KERNEL_POSITION_COMPONENT)) {
                return BREAK_KERNEL_FAILED;
            }
        } else if (action->type == BREAK_KERNEL_ENTITY_INVENTORY_ADD) {
            if (action->item_id == 0u || action->item_id > BREAK_KERNEL_MAX_ITEMS ||
                action->count == 0u) {
                return BREAK_KERNEL_INVALID;
            }
            u32 limit = kernel->items[action->item_id].stack_limit;
            if (limit == 0u) return BREAK_KERNEL_STALE;
            u64 total = kernel->inventories[inventory_index(slot, action->item_id)];
            for (u32 k = 0u; k < i; k++) {
                const BreakKernelEntityAction *prior = &actions[k];
                if (prior->type == BREAK_KERNEL_ENTITY_INVENTORY_ADD &&
                    prior->item_id == action->item_id &&
                    break_kernel_actor_slot(kernel, prior->entity) == slot) {
                    total += prior->count;
                }
            }
            total += action->count;
            if (total > limit) return BREAK_KERNEL_OVERLOAD;
        } else {
            return BREAK_KERNEL_INVALID;
        }
    }
    for (u32 i = 0u; i < count; i++) {
        const BreakKernelEntityAction *action = &actions[i];
        u32 slot = break_kernel_actor_slot(kernel, action->entity);
        if (action->type == BREAK_KERNEL_ENTITY_SET_POSITION) {
            void *position = world_get_component(kernel->world, action->entity,
                                                 BREAK_KERNEL_POSITION_COMPONENT);
            memcpy(position, &action->position, sizeof(action->position));
        } else {
            kernel->inventories[inventory_index(slot, action->item_id)] += action->count;
        }
    }
    return BREAK_KERNEL_OK;
}
