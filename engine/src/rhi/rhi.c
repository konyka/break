#include <rhi/rhi.h>
#include <core/log.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>

#define RHI_MAX_RESOURCES 4096

/* Generation values are process-wide, not device-local. This prevents an
 * index/generation pair from accidentally resolving in a second device. */
static atomic_uint g_rhi_generation_seed = 1u;

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
    RHIPresentRect   frame_current_damage[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32              frame_current_damage_count;
    bool             frame_damage_requested;
    bool             frame_partial_active;
    atomic_uintptr_t frame_owner;
};

_Thread_local RHIDevice *g_current_device = NULL;
static _Thread_local unsigned char g_rhi_thread_token;
static _Thread_local RHIDevice *g_rhi_frame_device;
static _Thread_local bool g_rhi_frame_owner_preclaimed;

#define RHI_FRAME_OWNER_DESTROYING ((uintptr_t)1u)
#define RHI_FRAME_OWNER_CONTROLLING ((uintptr_t)2u)

static uintptr_t rhi_thread_owner_token(void) {
    return (uintptr_t)&g_rhi_thread_token;
}

static bool rhi_frame_owner_try_acquire(RHIDevice *dev) {
    uintptr_t expected = 0u;
    if (dev == NULL || g_rhi_frame_device != NULL) return false;
    if (!atomic_compare_exchange_strong_explicit(
        &dev->frame_owner, &expected, rhi_thread_owner_token(),
        memory_order_acquire, memory_order_relaxed)) {
        return false;
    }
    g_rhi_frame_device = dev;
    return true;
}

static bool rhi_frame_owner_begin_destroy(RHIDevice *dev) {
    uintptr_t expected = 0u;
    if (dev == NULL || g_rhi_frame_device == dev) return false;
    return atomic_compare_exchange_strong_explicit(
        &dev->frame_owner, &expected, RHI_FRAME_OWNER_DESTROYING,
        memory_order_acquire, memory_order_relaxed);
}

static bool rhi_device_control_try_acquire(RHIDevice *dev) {
    uintptr_t expected = 0u;
    if (dev == NULL) return false;
    return atomic_compare_exchange_strong_explicit(
        &dev->frame_owner, &expected, RHI_FRAME_OWNER_CONTROLLING,
        memory_order_acquire, memory_order_relaxed);
}

static void rhi_device_control_release(RHIDevice *dev) {
    uintptr_t expected = RHI_FRAME_OWNER_CONTROLLING;
    if (dev == NULL) return;
    (void)atomic_compare_exchange_strong_explicit(
        &dev->frame_owner, &expected, 0u, memory_order_release,
        memory_order_relaxed);
}

static bool rhi_frame_owner_is_current(const RHIDevice *dev) {
    return dev != NULL && g_rhi_frame_device == dev &&
           atomic_load_explicit(&dev->frame_owner, memory_order_acquire) ==
               rhi_thread_owner_token();
}

static void rhi_frame_owner_release(RHIDevice *dev) {
    uintptr_t expected;
    if (dev == NULL) return;
    expected = rhi_thread_owner_token();
    if (atomic_compare_exchange_strong_explicit(
            &dev->frame_owner, &expected, 0u, memory_order_release,
            memory_order_relaxed) && g_rhi_frame_device == dev) {
        g_rhi_frame_device = NULL;
        g_rhi_frame_owner_preclaimed = false;
    }
}

static void rhi_frame_damage_clear(RHIDevice *dev) {
    dev->frame_damage_count = 0u;
    dev->frame_current_damage_count = 0u;
    dev->frame_damage_requested = false;
    dev->frame_partial_active = false;
}

static bool rhi_frame_owner_begin_backend(RHIDevice *dev) {
    if (g_rhi_frame_owner_preclaimed) {
        g_rhi_frame_owner_preclaimed = false;
        return rhi_frame_owner_is_current(dev);
    }
    return rhi_frame_owner_try_acquire(dev);
}

#ifdef ENGINE_RHI_TEST
static bool rhi_cmd_matches_device(RHIDevice *dev, RHICmdBuffer *cmd,
                                    void *backend) {
    return dev != NULL && cmd != NULL && backend != NULL &&
           g_current_device == dev && (void *)cmd == backend;
}
#endif

static bool rhi_drawable_dimensions_valid(u32 width, u32 height) {
    return width != 0u && height != 0u &&
           width <= RHI_MAX_DRAWABLE_DIMENSION &&
           height <= RHI_MAX_DRAWABLE_DIMENSION;
}

bool rhi_texture_desc_validate(const RHITextureDesc *desc) {
    u32 max_extent;
    u32 max_mips = 1u;

    if (desc == NULL || desc->width == 0u || desc->height == 0u ||
        desc->width > RHI_MAX_DRAWABLE_DIMENSION ||
        desc->height > RHI_MAX_DRAWABLE_DIMENSION ||
        desc->format < RHI_FORMAT_R8G8B8A8_UNORM ||
        desc->format > RHI_FORMAT_D32_FLOAT ||
        desc->format == RHI_FORMAT_UNDEFINED ||
        desc->mip_levels > RHI_MAX_MIP_LEVELS) {
        return false;
    }
    max_extent = desc->width > desc->height ? desc->width : desc->height;
    while (max_extent > 1u) {
        max_extent >>= 1u;
        max_mips++;
    }
    return desc->mip_levels == 0u || desc->mip_levels <= max_mips;
}

bool rhi_buffer_desc_validate(const RHIBufferDesc *desc) {
    const RHIBufferUsage known_usage = (RHIBufferUsage)(
        RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX |
        RHI_BUFFER_USAGE_UNIFORM | RHI_BUFFER_USAGE_TEXEL |
        RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_INDIRECT);
    return desc != NULL && desc->size != 0u &&
           (desc->usage & known_usage) != 0 &&
           (desc->usage & (RHIBufferUsage)~known_usage) == 0;
}

bool rhi_cubemap_desc_validate(const RHICubemapDesc *desc) {
    u32 max_mips = 1u;
    u32 extent;

    if (desc == NULL || desc->size == 0u ||
        desc->size > RHI_MAX_DRAWABLE_DIMENSION ||
        desc->format < RHI_FORMAT_R8G8B8A8_UNORM ||
        desc->format > RHI_FORMAT_R16G16B16A16_SFLOAT ||
        desc->mip_levels > RHI_MAX_MIP_LEVELS) {
        return false;
    }
    extent = desc->size;
    while (extent > 1u) {
        extent >>= 1u;
        max_mips++;
    }
    return desc->mip_levels == 0u || desc->mip_levels <= max_mips;
}

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
    dev->slots[idx].generation =
        atomic_fetch_add_explicit(&g_rhi_generation_seed, 1u,
                                  memory_order_relaxed);
    if (dev->slots[idx].generation == 0u) {
        dev->slots[idx].generation =
            atomic_fetch_add_explicit(&g_rhi_generation_seed, 1u,
                                      memory_order_relaxed);
        if (dev->slots[idx].generation == 0u)
            dev->slots[idx].generation = 1u;
    }
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

bool rhi_present_damage_to_bottom_left(const RHIPresentRect *rects, u32 count,
                                       u32 width, u32 height,
                                       RHIPresentRect *out, u32 capacity) {
    u32 i;

    if (count > capacity || (count != 0u && out == NULL) ||
        !rhi_present_damage_validate(rects, count, width, height)) {
        return false;
    }
    for (i = 0u; i < count; ++i) {
        RHIPresentRect rect = rects[i];
        rect.y = (i32)(height - ((u32)rect.y + rect.h));
        out[i] = rect;
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
        if (!rhi_frame_owner_try_acquire(dev)) return NULL;
        rhi_frame_damage_clear(dev);
        g_rhi_frame_owner_preclaimed = true;
        {
            RHICmdBuffer *cmd = rhi_frame_begin(dev);
            if (cmd == NULL) {
                rhi_frame_damage_clear(dev);
                g_rhi_frame_owner_preclaimed = false;
                rhi_frame_owner_release(dev);
            }
            return cmd;
        }
    }
    if (!rhi_frame_owner_try_acquire(dev)) return NULL;
    if (count != 0u) {
        memcpy(dev->frame_current_damage, rects, count * sizeof(*rects));
        memcpy(dev->frame_damage, rects, count * sizeof(*rects));
    }
    dev->frame_current_damage_count = count;
    dev->frame_damage_count = count;
    dev->frame_damage_requested = true;
    g_rhi_frame_owner_preclaimed = true;
    {
        RHICmdBuffer *cmd = rhi_frame_begin(dev);
        if (cmd == NULL) {
            g_rhi_frame_owner_preclaimed = false;
            rhi_frame_damage_clear(dev);
            rhi_frame_owner_release(dev);
        }
        if (out_partial != NULL) *out_partial = dev->frame_partial_active;
        return cmd;
    }
}

bool rhi_frame_get_damage(const RHIDevice *dev, RHIPresentRect *rects,
                          u32 capacity, u32 *out_count) {
    if (dev == NULL || out_count == NULL ||
        (rects == NULL && capacity != 0u) ||
        capacity < dev->frame_damage_count) {
        return false;
    }
    if (dev->frame_damage_count != 0u) {
        memcpy(rects, dev->frame_damage,
               dev->frame_damage_count * sizeof(dev->frame_damage[0]));
    }
    *out_count = dev->frame_damage_count;
    return true;
}

bool rhi_offscreen_fbo_desc_validate(const RHICapabilities *caps,
                                     const RHIOffscreenFBODesc *desc) {
    if (!caps || !desc || desc->width == 0u || desc->height == 0u ||
        desc->width > RHI_MAX_DRAWABLE_DIMENSION ||
        desc->height > RHI_MAX_DRAWABLE_DIMENSION) return false;
    if (desc->color_format < RHI_FORMAT_R8G8B8A8_UNORM ||
        desc->color_format > RHI_FORMAT_R32_FLOAT ||
        desc->color_format == RHI_FORMAT_UNDEFINED ||
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

bool rhi_mrt_desc_validate(u32 width, u32 height,
                           const RHIFormat *formats, u32 attachment_count) {
    if (width == 0u || height == 0u ||
        width > RHI_MAX_DRAWABLE_DIMENSION ||
        height > RHI_MAX_DRAWABLE_DIMENSION ||
        formats == NULL || attachment_count == 0u ||
        attachment_count > RHI_MRT_MAX_ATTACHMENTS) {
        return false;
    }
    for (u32 i = 0u; i < attachment_count; ++i) {
        if (formats[i] < RHI_FORMAT_R8G8B8A8_UNORM ||
            formats[i] > RHI_FORMAT_R32_FLOAT ||
            formats[i] == RHI_FORMAT_UNDEFINED ||
            formats[i] == RHI_FORMAT_D32_FLOAT) {
            return false;
        }
    }
    return true;
}

void *rhi_get_resource(RHIDevice *dev, RHIHandle h) {
    if (dev == NULL || h.generation == 0u || h.index >= RHI_MAX_RESOURCES) return NULL;
    RHIResourceSlot *s = &dev->slots[h.index];
    if (s->generation != h.generation || !s->alive) return NULL;
    return s->ptr;
}

void *rhi_get_resource_typed(RHIDevice *dev, RHIHandle h, u32 type) {
    if (dev == NULL || h.generation == 0u || h.index >= RHI_MAX_RESOURCES) return NULL;
    RHIResourceSlot *s = &dev->slots[h.index];
    if (s->generation != h.generation || !s->alive || (u32)s->type != type) return NULL;
    return s->ptr;
}

void rhi_free_slot(RHIDevice *dev, RHIHandle h) {
    if (dev == NULL || h.generation == 0u || h.index >= RHI_MAX_RESOURCES) return;
    RHIResourceSlot *s = &dev->slots[h.index];
    if (s->generation == h.generation && s->alive) {
        s->alive = false;
        s->ptr = (void *)(uintptr_t)dev->free_head;
        dev->free_head = h.index;
        dev->free_count++;
    }
}

#ifdef ENGINE_RHI_TEST
bool rhi_test_cmd_matches_device(RHIDevice *dev, RHICmdBuffer *cmd,
                                  void *backend) {
    return rhi_cmd_matches_device(dev, cmd, backend);
}

void rhi_test_set_current_device(RHIDevice *dev) {
    g_current_device = dev;
}

void rhi_test_set_backend(RHIDevice *dev, void *backend) {
    if (dev != NULL) dev->backend_data = backend;
}

void rhi_test_set_dimensions(RHIDevice *dev, u32 width, u32 height) {
    if (dev == NULL) return;
    dev->width = width;
    dev->height = height;
}

bool rhi_test_frame_owner_try_acquire(RHIDevice *dev) {
    return rhi_frame_owner_try_acquire(dev);
}

bool rhi_test_frame_owner_is_current(const RHIDevice *dev) {
    return rhi_frame_owner_is_current(dev);
}

void rhi_test_frame_owner_release(RHIDevice *dev) {
    rhi_frame_owner_release(dev);
}

bool rhi_test_frame_owner_begin_destroy(RHIDevice *dev) {
    return rhi_frame_owner_begin_destroy(dev);
}

bool rhi_test_device_control_try_acquire(RHIDevice *dev) {
    return rhi_device_control_try_acquire(dev);
}

void rhi_test_device_control_release(RHIDevice *dev) {
    rhi_device_control_release(dev);
}

RHIDevice *rhi_test_device_create(void) {
    RHIDevice *dev = (RHIDevice *)calloc(1, sizeof(*dev));
    if (dev != NULL) rhi_init_freelist(dev);
    return dev;
}

void rhi_test_device_destroy(RHIDevice *dev) {
    free(dev);
}

RHIHandle rhi_test_resource_create(RHIDevice *dev) {
    u32 index;
    if (dev == NULL) return RHI_HANDLE_NULL;
    index = rhi_alloc_slot(dev);
    dev->slots[index].ptr = dev;
    dev->slots[index].type = RHI_RES_BUFFER;
    return rhi_make_handle(index, dev->slots[index].generation);
}

void rhi_test_resource_destroy(RHIDevice *dev, RHIHandle handle) {
    if (dev == NULL) return;
    rhi_free_slot(dev, handle);
}
#endif

#ifdef ENGINE_VULKAN
/* The Vulkan backend is included as a unity translation unit.  Keep this
 * include's owner current when backend contracts change so incremental builds
 * rebuild the engine even on generators without header dependency scanning. */
#include <rhi/rhi_vk.c>
#else
#include <rhi/rhi_gl.c>
#endif
