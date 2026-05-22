#pragma once

#include <rhi/rhi.h>

#define GPUCULL_MAX_OBJECTS 4096

typedef struct {
    RHIDevice      *device;
    RHIPipeline     cull_pipe;
    RHIBuffer       object_ssbo;
    RHIBuffer       visible_ssbo;
    RHIBuffer       indirect_buf;
    RHIBuffer       count_buf;
    u32             object_count;
    bool            ready;
} GPUCullSystem;

bool gpucull_init(GPUCullSystem *gc, RHIDevice *dev);
void gpucull_shutdown(GPUCullSystem *gc);
void gpucull_update_objects(GPUCullSystem *gc, const f32 *positions, const f32 *radii, u32 count);
void gpucull_dispatch(GPUCullSystem *gc, RHICmdBuffer *cmd, const f32 *vp);
void gpucull_get_results(GPUCullSystem *gc, u32 *out_visible_count);
