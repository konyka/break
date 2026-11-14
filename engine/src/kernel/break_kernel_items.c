#include <kernel/break_kernel_internal.h>

#define BREAK_KERNEL_MAX_STACK 1000000u
#define BREAK_KERNEL_INVENTORY_STRIDE (BREAK_KERNEL_MAX_ITEMS + 1u)

static BreakKernelError item_error(const BreakKernel *kernel, u32 item_id) {
    if (item_id == 0 || item_id > BREAK_KERNEL_MAX_ITEMS) {
        return BREAK_KERNEL_INVALID;
    }
    if (kernel->items[item_id].stack_limit == 0) {
        return BREAK_KERNEL_STALE;
    }
    return BREAK_KERNEL_OK;
}

static size_t inventory_index(u32 slot, u32 item_id) {
    return (size_t)slot * BREAK_KERNEL_INVENTORY_STRIDE + item_id;
}

void break_kernel_items_on_despawn(BreakKernel *kernel, u32 slot) {
    if (!kernel || !kernel->inventories || slot >= kernel->max_actors) {
        return;
    }
    memset(kernel->inventories + inventory_index(slot, 0), 0,
           BREAK_KERNEL_INVENTORY_STRIDE * sizeof(*kernel->inventories));
}

BreakKernelError break_kernel_item_define(BreakKernel *kernel, const BreakKernelItemDesc *desc) {
    if (!kernel || !desc) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    if (desc->item_id == 0 || desc->item_id > BREAK_KERNEL_MAX_ITEMS ||
        desc->stack_limit == 0 || desc->stack_limit > BREAK_KERNEL_MAX_STACK) {
        return BREAK_KERNEL_INVALID;
    }
    if (kernel->items[desc->item_id].stack_limit != 0) {
        return BREAK_KERNEL_REJECTED;
    }
    kernel->items[desc->item_id] = *desc;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_items_add_slot(BreakKernel *kernel, u32 slot, u32 item_id, u32 count) {
    if (!kernel || slot >= kernel->max_actors || count == 0) {
        return BREAK_KERNEL_INVALID;
    }
    BreakKernelError item = item_error(kernel, item_id);
    if (item != BREAK_KERNEL_OK) {
        return item;
    }
    size_t index = inventory_index(slot, item_id);
    u32 old_count = kernel->inventories[index];
    u32 limit = kernel->items[item_id].stack_limit;
    if (old_count > limit || count > limit - old_count) {
        return BREAK_KERNEL_OVERLOAD;
    }
    kernel->inventories[index] = old_count + count;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_items_remove_slot(BreakKernel *kernel, u32 slot, u32 item_id, u32 count) {
    if (!kernel || slot >= kernel->max_actors || count == 0) {
        return BREAK_KERNEL_INVALID;
    }
    BreakKernelError item = item_error(kernel, item_id);
    if (item != BREAK_KERNEL_OK) {
        return item;
    }
    size_t index = inventory_index(slot, item_id);
    u32 old_count = kernel->inventories[index];
    if (old_count < count) {
        return BREAK_KERNEL_OVERLOAD;
    }
    kernel->inventories[index] = old_count - count;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_inventory_add(BreakKernel *kernel, Entity entity, u32 item_id, u32 count) {
    if (!kernel || count == 0) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    BreakKernelError item = item_error(kernel, item_id);
    if (item != BREAK_KERNEL_OK) {
        return item;
    }
    u32 slot = break_kernel_actor_slot(kernel, entity);
    if (slot == UINT32_MAX) {
        return BREAK_KERNEL_STALE;
    }
    return break_kernel_items_add_slot(kernel, slot, item_id, count);
}

BreakKernelError break_kernel_inventory_count(BreakKernel *kernel, Entity entity, u32 item_id, u32 *out_count) {
    if (!kernel || !out_count) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    BreakKernelError item = item_error(kernel, item_id);
    if (item != BREAK_KERNEL_OK) {
        return item;
    }
    u32 slot = break_kernel_actor_slot(kernel, entity);
    if (slot == UINT32_MAX) {
        return BREAK_KERNEL_STALE;
    }
    *out_count = kernel->inventories[inventory_index(slot, item_id)];
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_inventory_transfer(BreakKernel *kernel, Entity from, Entity to,
                                             u32 item_id, u32 count) {
    if (!kernel || count == 0 || (from.index == to.index && from.generation == to.generation)) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    BreakKernelError item = item_error(kernel, item_id);
    if (item != BREAK_KERNEL_OK) {
        return item;
    }
    u32 from_slot = break_kernel_actor_slot(kernel, from);
    u32 to_slot = break_kernel_actor_slot(kernel, to);
    if (from_slot == UINT32_MAX || to_slot == UINT32_MAX) {
        return BREAK_KERNEL_STALE;
    }
    size_t from_index = inventory_index(from_slot, item_id);
    size_t to_index = inventory_index(to_slot, item_id);
    u32 from_count = kernel->inventories[from_index];
    u32 to_count = kernel->inventories[to_index];
    u32 limit = kernel->items[item_id].stack_limit;
    if (from_count < count || to_count > limit || count > limit - to_count) {
        return BREAK_KERNEL_OVERLOAD;
    }
    kernel->inventories[from_index] = from_count - count;
    kernel->inventories[to_index] = to_count + count;
    return BREAK_KERNEL_OK;
}
