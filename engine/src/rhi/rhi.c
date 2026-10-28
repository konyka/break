#include <rhi/rhi.h>
#include <rhi/rhi_native_vulkan.h>
#include <rhi/rhi_backend_internal.h>
#include <core/log.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>

#include "rhi/rhi_rollout.h"

static void rhi_rollout_emit_backend_selected(void) {
    RHIRolloutEvent ev = {
        .event = "backend_selected",
        .backend = rhi_rollout_compiled_backend(),
        .reason = rhi_rollout_compiled_reason(),
        .config_version = ENGINE_RHI_ROLLOUT_CONFIG_VERSION,
        .result = "OK",
    };
    rhi_rollout_emit(&ev);
}

_Thread_local RHIDevice *g_current_device = NULL;
/* Pre-seeded to ERROR before each backend rhi_device_create call; the
 * backend may downgrade to UNAVAILABLE via rhi_backend_note_create_result
 * (e.g. D3D12 with no hardware adapter). */
static _Thread_local RHIResult g_backend_create_result = RHI_RESULT_ERROR;

void rhi_backend_note_create_result(RHIResult result) {
    g_backend_create_result = result;
}
#ifdef ENGINE_RHI_TEST
static _Thread_local RHIDevice *g_test_lifecycle_device;
static _Thread_local RHIResult g_test_lifecycle_result = RHI_RESULT_OK;
#endif
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

bool rhi_device_resource_usage(const RHIDevice *dev, u32 *out_used,
                               u32 *out_capacity) {
    if (dev == NULL) return false;
    if (out_used != NULL) *out_used = RHI_MAX_RESOURCES - dev->free_count;
    if (out_capacity != NULL) *out_capacity = RHI_MAX_RESOURCES;
    return true;
}

static RHIResult rhi_result_for_device(const RHIDevice *dev) {
    if (dev == NULL) return RHI_RESULT_INVALID_ARGUMENT;
    if (dev->status == RHI_DEVICE_STATUS_LOST) return RHI_RESULT_DEVICE_LOST;
#ifdef ENGINE_RHI_TEST
    if (g_test_lifecycle_device == dev && g_test_lifecycle_result != RHI_RESULT_OK)
        return g_test_lifecycle_result;
#endif
    return RHI_RESULT_OK;
}

RHIDevice *rhi_device_create_ex(RHIBackend backend, void *window_native,
                                void *display_native, u32 w, u32 h,
                                RHIResult *out_result) {
    if (out_result != NULL) *out_result = RHI_RESULT_OK;
    if (backend == RHI_BACKEND_D3D12) {
        /* Plan D Task 3: pass through to engine_rhi_d3d12. D3D12 needs a
         * native HWND (window_native); display_native is unused on Win32.
         * Argument faults are INVALID_ARGUMENT; once the backend runs,
         * adapter-absent maps to UNAVAILABLE and any other init failure to
         * ERROR (reported via rhi_backend_note_create_result). */
        RHIDevice *dev;
        if (!rhi_drawable_dimensions_valid(w, h) || window_native == NULL) {
            if (out_result != NULL) *out_result = RHI_RESULT_INVALID_ARGUMENT;
            return NULL;
        }
        g_backend_create_result = RHI_RESULT_ERROR;
        dev = rhi_device_create(backend, window_native, display_native, w, h);
        if (dev == NULL && out_result != NULL)
            *out_result = g_backend_create_result;
        if (dev != NULL) rhi_rollout_emit_backend_selected();
        return dev;
    }
    if (backend == RHI_BACKEND_METAL) {
        /* Plan C Task 3: pass through to engine_rhi_metal. window_native is
         * the CAMetalLayer * (window_cocoa.m platform_window_native; iOS
         * injects via PlatformConfig.native_window); display_native is
         * unused on Apple platforms. Argument faults are INVALID_ARGUMENT;
         * once the backend runs, a nil system device maps to ERROR via the
         * pre-seeded g_backend_create_result (spec §4.2). */
        RHIDevice *dev;
        if (!rhi_drawable_dimensions_valid(w, h) || window_native == NULL) {
            if (out_result != NULL) *out_result = RHI_RESULT_INVALID_ARGUMENT;
            return NULL;
        }
        g_backend_create_result = RHI_RESULT_ERROR;
        dev = rhi_device_create(backend, window_native, display_native, w, h);
        if (dev == NULL && out_result != NULL)
            *out_result = g_backend_create_result;
        if (dev != NULL) rhi_rollout_emit_backend_selected();
        return dev;
    }
    if (backend != RHI_BACKEND_OPENGL && backend != RHI_BACKEND_VULKAN) {
        if (out_result != NULL) *out_result = RHI_RESULT_UNSUPPORTED;
        return NULL;
    }
    if (!rhi_drawable_dimensions_valid(w, h)) {
        if (out_result != NULL) *out_result = RHI_RESULT_INVALID_ARGUMENT;
        return NULL;
    }
    if (window_native == NULL || display_native == NULL) {
        if (out_result != NULL) *out_result = RHI_RESULT_UNAVAILABLE;
        return NULL;
    }
    RHIDevice *dev = rhi_device_create(backend, window_native, display_native, w, h);
    if (dev == NULL && out_result != NULL) *out_result = RHI_RESULT_ERROR;
    if (dev != NULL) rhi_rollout_emit_backend_selected();
    return dev;
}

RHIResult rhi_device_destroy_ex(RHIDevice *dev) {
    if (dev == NULL) return RHI_RESULT_INVALID_ARGUMENT;
    if (!rhi_frame_owner_preclaim_destroy(dev)) return RHI_RESULT_BUSY;
    /* WSI DESTROYING 门控：窗口已进入销毁流程的 surface 上不再拆设备；
     * 调用方必须先完成 RHI 销毁再进入 platform_destroy。 */
    if (dev->wsi != NULL && !platform_wsi_rhi_teardown_allowed(dev->wsi)) {
        rhi_frame_owner_clear_preclaims(dev);
        return RHI_RESULT_BUSY;
    }
    rhi_device_destroy(dev);
    return RHI_RESULT_OK;
}

void rhi_device_attach_wsi(RHIDevice *dev, PlatformWsiSurface *wsi) {
    if (dev != NULL) dev->wsi = wsi;
}

RHIResult rhi_device_resize_ex(RHIDevice *dev, u32 w, u32 h) {
    if (dev == NULL || !rhi_drawable_dimensions_valid(w, h))
        return RHI_RESULT_INVALID_ARGUMENT;
    RHIResult forced = rhi_result_for_device(dev);
    if (forced != RHI_RESULT_OK) return forced;
    if (!rhi_device_control_preclaim(dev)) return RHI_RESULT_BUSY;
    if (dev->backend_data == NULL) {
        rhi_device_control_release(dev);
        return RHI_RESULT_UNAVAILABLE;
    }
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
    rhi_device_resize(dev, w, h);
    rhi_device_control_release(dev);
    return dev->lifecycle_result;
}

RHICmdBuffer *rhi_frame_begin_ex(RHIDevice *dev, RHIResult *out_result) {
    if (out_result != NULL) *out_result = RHI_RESULT_OK;
    if (dev == NULL) {
        if (out_result != NULL) *out_result = RHI_RESULT_INVALID_ARGUMENT;
        return NULL;
    }
    RHIResult forced = rhi_result_for_device(dev);
    if (forced != RHI_RESULT_OK) {
        if (out_result != NULL) *out_result = forced;
        return NULL;
    }
    if (dev->backend_data == NULL) {
        if (out_result != NULL) *out_result = RHI_RESULT_UNAVAILABLE;
        return NULL;
    }
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
    RHICmdBuffer *cmd = rhi_frame_begin(dev);
    if (cmd == NULL && out_result != NULL)
        *out_result = dev->lifecycle_result != RHI_RESULT_OK ?
            dev->lifecycle_result : RHI_RESULT_UNAVAILABLE;
    return cmd;
}

RHICmdBuffer *rhi_frame_acquire_ex(RHIDevice *dev, RHIResult *out_result) {
    return rhi_frame_begin_ex(dev, out_result);
}

RHIResult rhi_frame_end_ex(RHIDevice *dev) {
    if (dev == NULL) return RHI_RESULT_INVALID_ARGUMENT;
    RHIResult forced = rhi_result_for_device(dev);
    if (forced != RHI_RESULT_OK) return forced;
    if (dev->backend_data == NULL) return RHI_RESULT_UNAVAILABLE;
    if (!rhi_frame_owner_is_current(dev)) return RHI_RESULT_BUSY;
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
    rhi_frame_end(dev);
    return dev->lifecycle_result;
}

RHIResult rhi_frame_submit_ex(RHIDevice *dev) {
    return rhi_frame_end_ex(dev);
}

RHIResult rhi_present_ex(RHIDevice *dev) {
    if (dev == NULL) return RHI_RESULT_INVALID_ARGUMENT;
    RHIResult forced = rhi_result_for_device(dev);
    if (forced != RHI_RESULT_OK) {
        RHIRolloutEvent ev = { "present_failure", NULL, "none",
            ENGINE_RHI_ROLLOUT_CONFIG_VERSION, rhi_result_name(forced) };
        ev.backend = rhi_rollout_compiled_backend();
        rhi_rollout_emit(&ev);
        return forced;
    }
    if (dev->backend_data == NULL) return RHI_RESULT_UNAVAILABLE;
    if (!rhi_frame_owner_is_current(dev)) return RHI_RESULT_BUSY;
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
    rhi_present(dev);
    if (dev->lifecycle_result != RHI_RESULT_OK) {
        RHIRolloutEvent ev = { "present_failure", NULL, "none",
            ENGINE_RHI_ROLLOUT_CONFIG_VERSION,
            rhi_result_name(dev->lifecycle_result) };
        ev.backend = rhi_rollout_compiled_backend();
        rhi_rollout_emit(&ev);
    }
    return dev->lifecycle_result;
}

RHIResult rhi_device_idle_ex(RHIDevice *dev) {
    if (dev == NULL) return RHI_RESULT_INVALID_ARGUMENT;
    RHIResult forced = rhi_result_for_device(dev);
    if (forced != RHI_RESULT_OK) return forced;
    if (dev->backend_data == NULL) return RHI_RESULT_UNAVAILABLE;
    if (rhi_device_lost(dev)) return RHI_RESULT_DEVICE_LOST;
    if (!rhi_device_idle(dev)) return RHI_RESULT_SYNC_FAILED;
    return rhi_device_lost(dev) ? RHI_RESULT_DEVICE_LOST : RHI_RESULT_OK;
}

RHIResult rhi_device_drain_ex(RHIDevice *dev) {
    return rhi_device_idle_ex(dev);
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
    /* storage_size 0 defers sizing to the backend's prebuild query
     * (spec §4.4; the D3D12 DXR backend implements it as "size
     * comes from the prebuild query"). The strict validator still
     * owns every non-zero size; backends without the deferred path
     * fail closed on 0 themselves (VK re-validates in its create). */
    if (dev == NULL || desc == NULL ||
        (desc->type != RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL &&
         desc->type != RHI_ACCELERATION_STRUCTURE_TOP_LEVEL) ||
        (desc->storage_size != 0u &&
         !rhi_acceleration_structure_desc_validate(desc))) {
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
    if (rhi_result_for_device(dev) != RHI_RESULT_OK || dev->backend_data == NULL)
        return NULL;
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
        dev->lifecycle_result = RHI_RESULT_OK;
    }
    return dev;
}

void rhi_test_set_lifecycle_result(RHIDevice *dev, RHIResult result) {
    g_test_lifecycle_device = dev;
    g_test_lifecycle_result = result;
}

void rhi_test_set_device_status(RHIDevice *dev, RHIDeviceStatus status) {
    if (dev != NULL) dev->status = status;
}

void rhi_test_device_destroy(RHIDevice *dev) {
    if (g_test_lifecycle_device == dev) {
        g_test_lifecycle_device = NULL;
        g_test_lifecycle_result = RHI_RESULT_OK;
    }
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

void rhi_device_set_lifecycle_result(RHIDevice *dev, RHIResult result) {
    if (result == RHI_RESULT_DEVICE_LOST) {
        RHIRolloutEvent ev = { "device_lost", NULL, "none",
            ENGINE_RHI_ROLLOUT_CONFIG_VERSION, "DEVICE_LOST" };
        ev.backend = rhi_rollout_compiled_backend();
        rhi_rollout_emit(&ev);
    }
    if (dev != NULL) dev->lifecycle_result = result;
}
