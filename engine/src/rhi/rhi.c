#include <rhi/rhi.h>
#include <rhi/rhi_backend_internal.h>
#include <core/log.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>

/* Generation values are process-wide, not device-local. This prevents an
 * index/generation pair from accidentally resolving in a second device. */
static atomic_uint g_rhi_generation_seed = 1u;

_Thread_local RHIDevice *g_current_device = NULL;
static void rhi_frame_damage_clear(RHIDevice *dev) {
    dev->frame_damage_count = 0u;
    dev->frame_current_damage_count = 0u;
    dev->frame_damage_requested = false;
    dev->frame_partial_active = false;
}

#ifdef ENGINE_RHI_TEST
static bool rhi_cmd_matches_device(RHIDevice *dev, RHICmdBuffer *cmd,
                                    void *backend) {
    return dev != NULL && cmd != NULL && backend != NULL &&
           g_current_device == dev && (void *)cmd == backend;
}
#endif

bool rhi_drawable_dimensions_valid(u32 width, u32 height) {
    return width != 0u && height != 0u &&
           width <= RHI_MAX_DRAWABLE_DIMENSION &&
           height <= RHI_MAX_DRAWABLE_DIMENSION;
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

RHIDeviceStatus rhi_device_get_status(const RHIDevice *dev) {
    if (dev == NULL) return RHI_DEVICE_STATUS_UNKNOWN;
    if (dev->status == RHI_DEVICE_STATUS_LOST) return RHI_DEVICE_STATUS_LOST;
    return dev->backend_data != NULL ? RHI_DEVICE_STATUS_READY : dev->status;
}

bool rhi_device_get_info(const RHIDevice *dev, RHIDeviceInfo *out) {
    if (dev == NULL || out == NULL) return false;
    memset(out, 0, sizeof(*out));
    out->backend = dev->capabilities.backend;
    out->feature_bits = dev->capabilities.feature_bits;
    if (dev->backend_data == NULL) return true;
    return rhi_backend_get_device_info(dev, out);
}

bool rhi_texture_get_native_info(const RHIDevice *dev, RHITexture texture,
                                 RHITextureNativeInfo *out) {
    if (dev == NULL || out == NULL || !rhi_handle_valid(texture)) return false;
    memset(out, 0, sizeof(*out));
    return rhi_backend_texture_get_native_info(dev, texture, out);
}

bool rhi_cmd_buffer_get_native_info(const RHIDevice *dev,
                                    const RHICmdBuffer *cmd,
                                    RHICmdBufferNativeInfo *out) {
    if (dev == NULL || cmd == NULL || out == NULL) return false;
    memset(out, 0, sizeof(*out));
    return rhi_backend_cmd_buffer_get_native_info(dev, cmd, out);
}

bool rhi_device_get_native_device(const RHIDevice *dev, RHINativeDevice *out) {
    if (dev == NULL || out == NULL) return false;
    memset(out, 0, sizeof(*out));
    return rhi_backend_get_native_device(dev, out);
}

bool rhi_acceleration_structure_desc_validate(
    const RHIAccelerationStructureDesc *desc) {
    return desc != NULL &&
           (desc->type == RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL ||
            desc->type == RHI_ACCELERATION_STRUCTURE_TOP_LEVEL) &&
           desc->storage_size != 0u &&
           desc->storage_size <= (usize)RHI_MAX_SCREENSHOT_BYTES * 16u;
}

bool rhi_blas_one_triangle_desc_validate(
    const RHIBLASOneTriangleDesc *desc) {
    if (desc == NULL || !rhi_handle_valid(desc->vertex_buffer) ||
        desc->vertex_count != 3u || desc->vertex_stride < 12u ||
        desc->vertex_format != RHI_VERTEX_FORMAT_R32G32B32_SFLOAT ||
        !desc->indexed || !rhi_handle_valid(desc->index_buffer) ||
        desc->index_count != 3u) {
        return false;
    }
    return true;
}

bool rhi_build_blas_one_triangle(
    RHIDevice *dev, RHIAccelerationStructure blas,
    const RHIBLASOneTriangleDesc *desc, RHIBuffer scratch_buffer,
    usize scratch_offset) {
    if (dev == NULL || !rhi_handle_valid(blas) ||
        !rhi_handle_valid(scratch_buffer) ||
        !rhi_blas_one_triangle_desc_validate(desc)) return false;
    return rhi_backend_cmd_build_blas_one_triangle(NULL, dev, blas, desc,
                                                   scratch_buffer, scratch_offset);
}

u64 rhi_acceleration_structure_get_device_address(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    if (dev == NULL || !rhi_handle_valid(structure)) return 0u;
    return rhi_backend_acceleration_structure_get_device_address(
        dev, structure);
}

bool rhi_tlas_one_instance_get_build_sizes(
    RHIDevice *dev, RHIBuffer instance_buffer,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    if (out_sizes != NULL) memset(out_sizes, 0, sizeof(*out_sizes));
    if (dev == NULL || out_sizes == NULL || !rhi_handle_valid(instance_buffer))
        return false;
    return rhi_backend_tlas_one_instance_get_build_sizes(
        dev, instance_buffer, out_sizes);
}

bool rhi_build_tlas_one_instance(
    RHIDevice *dev, RHIAccelerationStructure tlas, RHIBuffer instance_buffer,
    RHIBuffer scratch_buffer, usize scratch_offset) {
    if (dev == NULL || !rhi_handle_valid(tlas) ||
        !rhi_handle_valid(instance_buffer) ||
        !rhi_handle_valid(scratch_buffer)) return false;
    return rhi_backend_cmd_build_tlas_one_instance(
        NULL, dev, tlas, instance_buffer, scratch_buffer, scratch_offset);
}

bool rhi_acceleration_structure_get_vk_handle(
    RHIDevice *dev, RHIAccelerationStructure structure, void **out_handle) {
    if (dev == NULL || !rhi_handle_valid(structure) || out_handle == NULL)
        return false;
    *out_handle = NULL;
    return rhi_backend_acceleration_structure_get_vk_handle(
        dev, structure, out_handle);
}

RHIAccelerationStructure rhi_acceleration_structure_create(
    RHIDevice *dev, const RHIAccelerationStructureDesc *desc) {
    if (dev == NULL || !rhi_acceleration_structure_desc_validate(desc)) {
        return RHI_HANDLE_NULL;
    }
    return rhi_backend_acceleration_structure_create(dev, desc);
}

void rhi_acceleration_structure_destroy(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    if (dev == NULL || !rhi_handle_valid(structure)) return;
    rhi_backend_acceleration_structure_destroy(dev, structure);
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
    if (dev != NULL) {
        rhi_init_freelist(dev);
        dev->status = RHI_DEVICE_STATUS_READY;
    }
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
