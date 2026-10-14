#pragma once
#include <rhi/rhi.h>

/* Vulkan-shaped native interop, moved out of rhi.h so the public header stays
 * backend-neutral (multi-backend RHI spec §4.4). Consumers that need native
 * handles include this header explicitly. The declarations keep their
 * historical signatures (opaque void* handles) so existing call sites compile
 * unchanged apart from the added include. */

typedef struct {
    RHINativeHandleType type;
    void *instance;
    void *physical_device;
    void *device;
    void *graphics_queue;
    u32 graphics_queue_family;
    u32 feature_bits;
} RHINativeDevice;

typedef struct {
    RHINativeHandleType type;
    void *image;
    void *memory;
    void *view;
    u32 image_layout;
    RHIFormat format;
    u32 native_format;
    u32 width;
    u32 height;
    u32 mip_levels;
    u32 array_layers;
} RHITextureNativeInfo;

typedef struct {
    RHINativeHandleType type;
    void *command_buffer;
    bool recording;
} RHICmdBufferNativeInfo;

bool       rhi_texture_get_native_info(
               const RHIDevice *dev, RHITexture texture,
               RHITextureNativeInfo *out);
bool       rhi_cmd_buffer_get_native_info(
               const RHIDevice *dev, const RHICmdBuffer *cmd,
               RHICmdBufferNativeInfo *out);
bool       rhi_device_get_native_device(const RHIDevice *dev, RHINativeDevice *out);
bool       rhi_backend_get_native_device(const RHIDevice *dev, RHINativeDevice *out);
bool       rhi_backend_texture_get_native_info(
               const RHIDevice *dev, RHITexture texture,
               RHITextureNativeInfo *out);
bool       rhi_backend_cmd_buffer_get_native_info(
               const RHIDevice *dev, const RHICmdBuffer *cmd,
               RHICmdBufferNativeInfo *out);
bool       rhi_backend_acceleration_structure_get_vk_handle(
               RHIDevice *dev, RHIAccelerationStructure structure,
               void **out_handle);
/* Opaque native acceleration-structure handle (VkAccelerationStructureKHR on
 * Vulkan). Fails closed on OpenGL or invalid handles. */
bool       rhi_acceleration_structure_get_vk_handle(
               RHIDevice *dev, RHIAccelerationStructure structure,
               void **out_handle);

/* R438: Vulkan validation-message gate (defined only by the VK backend).
 * The counters link and stay inert (0 / no-op) when the gate was never
 * enabled. */
u32  rhi_vk_validation_message_count(void);
void rhi_vk_validation_message_count_reset(void);
bool rhi_vk_validation_gate_active(void);
void rhi_vk_validation_set_enabled(bool enabled);
