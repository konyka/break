#include <rhi/rhi.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>

#define RHI_MAX_RESOURCES 4096

typedef enum {
    RHI_RES_NONE,
    RHI_RES_SHADER,
    RHI_RES_PIPELINE,
    RHI_RES_BUFFER,
    RHI_RES_TEXTURE,
    RHI_RES_SAMPLER,
    RHI_RES_FRAMEBUFFER,
    RHI_RES_CUBEMAP,
    RHI_RES_MRT_FBO,
    RHI_RES_CUBEMAP_DEPTH_FBO,
} RHIResourceType;

typedef struct {
    void            *ptr;
    u32              generation;
    bool             alive;
    RHIResourceType  type;
} RHIResourceSlot;

struct RHIDevice {
    RHIResourceSlot  slots[RHI_MAX_RESOURCES];
    u32              next_slot;
    void            *backend_data;
    u32              width;
    u32              height;
    /* Free-list for O(1) slot allocation (Round 18) */
    u32              free_head;   /* UINT32_MAX = empty */
    u32              free_count;
};

RHIDevice *g_current_device = NULL;

/* Build the initial free-list after calloc.  Both GL and VK backends
 * call this once right after allocating the device. */
void rhi_init_freelist(RHIDevice *dev) {
    dev->free_head  = 0;
    dev->free_count = RHI_MAX_RESOURCES;
    for (u32 i = 0; i < RHI_MAX_RESOURCES - 1; i++)
        dev->slots[i].ptr = (void *)(uintptr_t)(i + 1);
    dev->slots[RHI_MAX_RESOURCES - 1].ptr = (void *)(uintptr_t)UINT32_MAX;
}

u32 rhi_alloc_slot(RHIDevice *dev) {
    if (dev->free_count == 0) {
        LOG_FATAL("RHI resource pool exhausted");
        return 0;
    }
    u32 idx = dev->free_head;
    dev->free_head = (u32)(uintptr_t)dev->slots[idx].ptr;
    dev->free_count--;
    dev->slots[idx].alive = true;
    dev->slots[idx].generation++;
    if (dev->slots[idx].generation == 0) dev->slots[idx].generation = 1;
    dev->next_slot = idx;
    return idx;
}

RHIHandle rhi_make_handle(u32 index, u32 gen) {
    return (RHIHandle){index, gen};
}

void *rhi_get_resource(RHIDevice *dev, RHIHandle h) {
    if (h.index >= RHI_MAX_RESOURCES) return NULL;
    RHIResourceSlot *s = &dev->slots[h.index];
    if (s->generation != h.generation || !s->alive) return NULL;
    return s->ptr;
}

void rhi_free_slot(RHIDevice *dev, RHIHandle h) {
    if (h.index >= RHI_MAX_RESOURCES) return;
    RHIResourceSlot *s = &dev->slots[h.index];
    if (s->generation == h.generation && s->alive) {
        s->alive = false;
        s->ptr = (void *)(uintptr_t)dev->free_head;
        dev->free_head = h.index;
        dev->free_count++;
    }
}

#ifdef ENGINE_VULKAN
#include <rhi/rhi_vk.c>
#else
#include <rhi/rhi_gl.c>
#endif
