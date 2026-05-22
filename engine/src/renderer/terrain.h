#pragma once
#include <core/types.h>
#include <rhi/rhi.h>

typedef struct {
    RHIDevice  *device;
    RHIPipeline pipeline;
    RHIBuffer   vbo;
    RHIBuffer   ibo;
    u32         index_count;
    u32         grid_size;
    f32         scale;
    f32         height_scale;
    i32 loc_model, loc_view, loc_proj;
    i32 loc_light_dir, loc_light_color, loc_ambient, loc_camera_pos;
    i32 loc_albedo;
} Terrain;

bool  terrain_init(Terrain *t, RHIDevice *dev, u32 grid_size, f32 scale, f32 height_scale);
void  terrain_shutdown(Terrain *t);
void  terrain_render(Terrain *t, RHICmdBuffer *cmd,
                     const f32 *view, const f32 *proj,
                     const f32 camera_pos[3],
                     RHITexture fallback_tex, RHISampler sampler);
f32   terrain_get_height(const Terrain *t, f32 x, f32 z);
