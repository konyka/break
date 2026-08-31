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
    RHICapabilities  capabilities;
    RHIPresentRect   frame_damage[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32              frame_damage_count;
    bool             frame_damage_requested;
    bool             frame_partial_active;
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
        /* R157: Abort instead of returning 0 — returning 0 causes callers to
         * overwrite slot 0's existing resource, corrupting the free list and
         * causing use-after-free when the old resource is destroyed. */
        abort();
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

bool rhi_device_get_capabilities(const RHIDevice *dev, RHICapabilities *out) {
    if (dev == NULL || out == NULL) return false;
    *out = dev->capabilities;
    return true;
}

bool rhi_present_damage_validate(const RHIPresentRect *rects, u32 count,
                                 u32 width, u32 height) {
    u32 i;
    if (count > RHI_MAX_PRESENT_DAMAGE_RECTS || width == 0u || height == 0u ||
        (count != 0u && rects == NULL)) {
        return false;
    }
    for (i = 0; i < count; ++i) {
        const RHIPresentRect *rect = &rects[i];
        if (rect->x < 0 || rect->y < 0 || rect->w == 0u || rect->h == 0u ||
            (u64)rect->x + rect->w > width ||
            (u64)rect->y + rect->h > height) {
            return false;
        }
    }
    return true;
}

bool rhi_screenshot_region_validate(u32 x, u32 y, u32 w, u32 h,
                                    u32 width, u32 height,
                                    usize dst_bytes) {
    usize required;
    usize max_size = (usize)-1;
    if (width == 0u || height == 0u || w == 0u || h == 0u ||
        x >= width || y >= height || w > width - x || h > height - y) {
        return false;
    }
    if ((usize)w > max_size / 4u) {
        return false;
    }
    required = (usize)w * 4u;
    if ((usize)h > max_size / required) {
        return false;
    }
    required *= (usize)h;
    return required <= (usize)RHI_MAX_SCREENSHOT_BYTES && dst_bytes >= required;
}

RHICmdBuffer *rhi_frame_begin_damage(RHIDevice *dev,
                                     const RHIPresentRect *rects, u32 count,
                                     bool *out_partial) {
    if (out_partial != NULL) *out_partial = false;
    if (dev == NULL) {
        return NULL;
    }
    if (!rhi_present_damage_validate(rects, count, dev->width, dev->height)) {
        dev->frame_damage_count = 0u;
        dev->frame_damage_requested = false;
        dev->frame_partial_active = false;
        return rhi_frame_begin(dev);
    }
    if (count != 0u) {
        memcpy(dev->frame_damage, rects, count * sizeof(*rects));
    }
    dev->frame_damage_count = count;
    dev->frame_damage_requested = true;
    {
        RHICmdBuffer *cmd = rhi_frame_begin(dev);
        if (out_partial != NULL) *out_partial = dev->frame_partial_active;
        return cmd;
    }
}

bool rhi_offscreen_fbo_desc_validate(const RHICapabilities *caps,
                                     const RHIOffscreenFBODesc *desc) {
    if (!caps || !desc || desc->width == 0u || desc->height == 0u) return false;
    if (desc->color_format == RHI_FORMAT_UNDEFINED ||
        desc->color_format == RHI_FORMAT_D32_FLOAT) return false;

    u32 samples = desc->sample_count == 0u ? 1u : desc->sample_count;
    u32 sample_bit = rhi_sample_count_bit(samples);
    if (sample_bit == 0u || (caps->color_sample_counts & sample_bit) == 0u ||
        (caps->depth_sample_counts & sample_bit) == 0u)
        return false;
    if (samples > 1u && (!caps->color_resolve_supported ||
                         !caps->depth_resolve_supported))
        return false;
    return true;
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
/* The Vulkan backend is included as a unity translation unit.  Keep this
 * include's owner current when backend contracts change so incremental builds
 * rebuild the engine even on generators without header dependency scanning. */
#include <rhi/rhi_vk.c>
#else
#include <rhi/rhi_gl.c>
#endif
