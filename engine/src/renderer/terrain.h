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
    f32         inv_scale;     /* 1.0f / scale, 预计算 */
    f32         inv_nm1;       /* (f32)(grid_size - 1), 预计算 */
    f32         height_scale;
    f32        *heightmap;
    u32         modify_count;
    f32         total_delta;
    u32         edit_quadrant[4];
    i32 loc_model, loc_view, loc_proj;
    i32 loc_light_dir, loc_light_color, loc_ambient, loc_camera_pos;
    i32 loc_albedo, loc_shadow_bias, loc_light_vp, loc_water_y, loc_time;
    /* Persistent staging buffer for batched vertex upload */
    f32        *_vert_staging;
    u32         _vert_staging_cap;
    /* Persistent buffers for terrain_flatten (avoids per-call malloc/free) */
    i32        *_flatten_indices;
    f32        *_flatten_dists;
    u32         _flatten_cap;
} Terrain;

bool  terrain_init(Terrain *t, RHIDevice *dev, u32 grid_size, f32 scale, f32 height_scale);
void  terrain_shutdown(Terrain *t);
void  terrain_render(Terrain *t, RHICmdBuffer *cmd,
                     const f32 *view, const f32 *proj,
                     const f32 camera_pos[3],
                     RHITexture fallback_tex, RHISampler sampler,
                     RHITexture shadow_map, const f32 *light_vp,
                     f32 shadow_bias, f32 water_y, f32 time);
f32   terrain_get_height(const Terrain *t, f32 x, f32 z);
void  terrain_modify_height(Terrain *t, f32 wx, f32 wz, f32 radius, f32 strength);
void  terrain_flatten(Terrain *t, f32 wx, f32 wz, f32 radius);
void  terrain_erode(Terrain *t, f32 wx, f32 wz, f32 radius, i32 iterations);
void  terrain_noise_stamp(Terrain *t, f32 wx, f32 wz, f32 radius, f32 strength, f32 seed);
void  terrain_generate(Terrain *t, u32 preset);
