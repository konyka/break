#pragma once
#include <core/types.h>
#include <rhi/rhi.h>
#include <math/math.h>

typedef struct {
    RHIDevice  *device;
    RHIPipeline pipeline;
    RHIBuffer   vbo;
    RHIBuffer   ibo;
    f32         water_y;
    f32         time;
    f32         time_scale;
    Vec3        color;
    bool        enabled;
    bool        render_above;
    i32 loc_view, loc_proj;
    i32 loc_time, loc_camera_pos, loc_water_color;
    i32 loc_light_vp, loc_shadow_bias, loc_water_y;
    i32 loc_model;
} WaterPlane;

bool water_init(WaterPlane *w, RHIDevice *dev, f32 water_y, f32 size);
void water_shutdown(WaterPlane *w);
void water_update(WaterPlane *w, f32 dt);
void water_render(WaterPlane *w, RHICmdBuffer *cmd,
                  const f32 *view, const f32 *proj,
                  const f32 camera_pos[3],
                  RHITexture shadow_map, const f32 *light_vp,
                  f32 shadow_bias);
