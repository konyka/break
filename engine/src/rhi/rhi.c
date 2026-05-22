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
};

RHIDevice *g_current_device = NULL;

u32 rhi_alloc_slot(RHIDevice *dev) {
    for (u32 i = 0; i < RHI_MAX_RESOURCES; i++) {
        u32 idx = (dev->next_slot + i) % RHI_MAX_RESOURCES;
        if (!dev->slots[idx].alive) {
            dev->slots[idx].alive = true;
            dev->slots[idx].generation++;
            if (dev->slots[idx].generation == 0) dev->slots[idx].generation = 1;
            dev->next_slot = (idx + 1) % RHI_MAX_RESOURCES;
            return idx;
        }
    }
    LOG_FATAL("RHI resource pool exhausted");
    return 0;
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
    if (s->generation == h.generation) s->alive = false;
}

#ifdef ENGINE_VULKAN
#include <rhi/rhi_vk.c>
#else
#include <rhi/rhi_gl.c>
#endif
