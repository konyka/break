#include <rhi/rhi_backend_internal.h>

#include <stdatomic.h>
#include <stdlib.h>

static atomic_uint g_rhi_generation_seed = 1u;

void rhi_init_freelist(RHIDevice *dev) {
    dev->free_head = 0;
    dev->free_count = RHI_MAX_RESOURCES;
    for (u32 i = 0; i < RHI_MAX_RESOURCES - 1u; ++i)
        dev->slots[i].ptr = (void *)(uintptr_t)(i + 1u);
    dev->slots[RHI_MAX_RESOURCES - 1u].ptr = (void *)(uintptr_t)UINT32_MAX;
}

u32 rhi_alloc_slot(RHIDevice *dev) {
    u32 idx;
    if (dev->free_count == 0u) abort();
    idx = dev->free_head;
    dev->free_head = (u32)(uintptr_t)dev->slots[idx].ptr;
    --dev->free_count;
    dev->slots[idx].alive = true;
    dev->slots[idx].generation = atomic_fetch_add_explicit(
        &g_rhi_generation_seed, 1u, memory_order_relaxed);
    if (dev->slots[idx].generation == 0u) {
        dev->slots[idx].generation = atomic_fetch_add_explicit(
            &g_rhi_generation_seed, 1u, memory_order_relaxed);
        if (dev->slots[idx].generation == 0u)
            dev->slots[idx].generation = 1u;
    }
    dev->next_slot = idx;
    return idx;
}

RHIHandle rhi_make_handle(u32 index, u32 generation) {
    return (RHIHandle){index, generation};
}

void *rhi_get_resource_typed(RHIDevice *dev, RHIHandle handle, u32 type) {
    RHIResourceSlot *slot;
    if (dev == NULL || handle.generation == 0u ||
        handle.index >= RHI_MAX_RESOURCES) return NULL;
    slot = &dev->slots[handle.index];
    if (slot->generation != handle.generation || !slot->alive ||
        (u32)slot->type != type) return NULL;
    return slot->ptr;
}

void rhi_free_slot(RHIDevice *dev, RHIHandle handle) {
    RHIResourceSlot *slot;
    if (dev == NULL || handle.generation == 0u ||
        handle.index >= RHI_MAX_RESOURCES) return;
    slot = &dev->slots[handle.index];
    if (slot->generation == handle.generation && slot->alive) {
        slot->alive = false;
        slot->ptr = (void *)(uintptr_t)dev->free_head;
        dev->free_head = handle.index;
        ++dev->free_count;
    }
}
