#pragma once
#include <core/types.h>
#include <rhi/rhi.h>

typedef struct {
    RHIDevice  *device;
    RHIPipeline pipeline;
    i32         loc_inv_proj;
    i32         loc_view;
    bool        ready;
} Skybox;

bool skybox_init(Skybox *sb, RHIDevice *dev);
void skybox_shutdown(Skybox *sb);
void skybox_render(Skybox *sb, RHICmdBuffer *cmd, const f32 *view, const f32 *proj);
