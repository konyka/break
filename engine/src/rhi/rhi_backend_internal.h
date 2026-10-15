#ifndef RHI_BACKEND_INTERNAL_H
#define RHI_BACKEND_INTERNAL_H

#include <stdatomic.h>

#include <rhi/rhi.h>

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
    RHI_RES_ACCELERATION_STRUCTURE,
} RHIResourceType;

typedef struct {
    void *ptr;
    u32 generation;
    bool alive;
    RHIResourceType type;
} RHIResourceSlot;

struct RHIDevice {
    RHIResourceSlot slots[RHI_MAX_RESOURCES];
    u32 next_slot;
    void *backend_data;
    u32 width;
    u32 height;
    u32 free_head;
    u32 free_count;
    RHICapabilities capabilities;
    RHIDeviceStatus status;
    RHIResult lifecycle_result;
    RHIPresentRect frame_damage[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 frame_damage_count;
    RHIPresentRect frame_current_damage[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 frame_current_damage_count;
    bool frame_damage_requested;
    bool frame_partial_active;
    atomic_uintptr_t frame_owner;
    PlatformWsiSurface *wsi;
};

extern _Thread_local RHIDevice *g_current_device;
extern _Thread_local RHIDevice *g_rhi_frame_device;
extern _Thread_local bool g_rhi_frame_owner_preclaimed;

void rhi_init_freelist(RHIDevice *dev);
u32 rhi_alloc_slot(RHIDevice *dev);
RHIHandle rhi_make_handle(u32 index, u32 generation);
void *rhi_get_resource_typed(RHIDevice *dev, RHIHandle handle, u32 type);
void rhi_free_slot(RHIDevice *dev, RHIHandle handle);
bool rhi_drawable_dimensions_valid(u32 width, u32 height);
bool rhi_frame_owner_begin_backend(RHIDevice *dev);
bool rhi_frame_owner_try_acquire(RHIDevice *dev);
bool rhi_frame_owner_begin_destroy(RHIDevice *dev);
bool rhi_frame_owner_preclaim_destroy(RHIDevice *dev);
bool rhi_frame_owner_is_current(const RHIDevice *dev);
void rhi_frame_owner_release(RHIDevice *dev);
bool rhi_device_control_try_acquire(RHIDevice *dev);
bool rhi_device_control_preclaim(RHIDevice *dev);
void rhi_device_control_release(RHIDevice *dev);
void rhi_frame_owner_clear_preclaims(RHIDevice *dev);
void rhi_device_set_lifecycle_result(RHIDevice *dev, RHIResult result);

/* Backend-reported create failure family: a backend calls this before
 * returning NULL from rhi_device_create so rhi_device_create_ex can map
 * adapter-absent (UNAVAILABLE) vs generic init failure (ERROR) without a
 * cross-library ABI change. rhi.c pre-seeds ERROR before each call, so a
 * silent backend still fails closed as ERROR. */
void rhi_backend_note_create_result(RHIResult result);

#endif
