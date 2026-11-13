#pragma once

/* Real device capture for the application's optional GPU lane.
 *
 * record mode never creates a window or a device; this module is only used
 * when the operator asks for --render=vulkan|opengl with --require-device.
 * Keeping it in its own translation unit means the record lane keeps its
 * "no RHI calls at all" property, which is what makes a headless machine a
 * valid record host. */

#include <core/types.h>
#include <renderer/mesh_buffer.h>
#include <renderer/world_presentation.h>
#include <rhi/rhi.h>
#include <runtime/runtime_types.h>

#include <stdio.h>

typedef struct CoreAppGpuFrame {
    u64 frame;
    u64 generation;
} CoreAppGpuFrame;

typedef enum CoreAppGpuBackend {
    CORE_APP_GPU_VULKAN = 0,
    CORE_APP_GPU_OPENGL
} CoreAppGpuBackend;

typedef struct CoreAppGpuConfig {
    CoreAppGpuBackend backend;
    u32 width;
    u32 height;
    bool require_device;
    bool no_fallback;
    bool validation;
} CoreAppGpuConfig;

typedef struct CoreAppGpu {
    void *platform;
    RHIDevice *device;
    WorldPresenter presenter;
    FILE *trace;
    u32 width;
    u32 height;
    u64 frames_presented;
    u64 screenshots_written;
    bool live;
    char backend_name[32];
    char device_name[RHI_DEVICE_NAME_MAX];
} CoreAppGpu;

/* Creates the window and device. Returns UNAVAILABLE when the host has no
 * display or no device and the caller did not require one, so a caller can
 * report the reason instead of crashing; FAILED once a device existed and a
 * later step broke. */
BreakRuntimeError core_app_gpu_create(CoreAppGpu *gpu, const CoreAppGpuConfig *config,
                                      FILE *trace);
/* Clears, submits the given world snapshot, presents and optionally captures
 * the frame to a PPM file. `path` may be NULL, in which case the frame is
 * presented without a capture. */
BreakRuntimeError core_app_gpu_render(CoreAppGpu *gpu, const WorldFrameSnapshot *snapshot,
                                      const char *screenshot_path, const CoreAppGpuFrame *frame);
/* Uploads a scene mesh (pos3+normal3+uv2, 32-byte stride) into device buffers
 * and fills the draw descriptor. The host `SceneMeshGeometry` is only read
 * here; nothing outlives the call. */
BreakRuntimeError core_app_gpu_upload_mesh(CoreAppGpu *gpu, const u8 *vertices,
                                           u32 vertex_count, const u32 *indices,
                                           u32 index_count, MeshGpu *out_gpu,
                                           MeshDrawDesc *out_draw);
BreakRuntimeError core_app_gpu_destroy(CoreAppGpu *gpu);
