#pragma once
#include <core/types.h>
#include <rhi/rhi.h>

typedef struct {
    RHIDevice  *device;
    RHIPipeline pipeline;
    i32         loc_inv_proj;
    i32         loc_view;
    i32         loc_sun_dir;
    i32         loc_sun_color;
    bool        ready;
} Skybox;

bool skybox_init(Skybox *sb, RHIDevice *dev);
void skybox_shutdown(Skybox *sb);
void skybox_render(Skybox *sb, RHICmdBuffer *cmd, const f32 *view, const f32 *inv_proj,
                   f32 sun_dx, f32 sun_dy, f32 sun_dz,
                   f32 sun_r, f32 sun_g, f32 sun_b);
