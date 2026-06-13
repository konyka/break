#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      extract_pipe;
    RHIPipeline      blur_pipe;
    RHIPipeline      composite_pipe;
    RHIPipeline      tex_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  fbo_ping;
    RHIOffscreenFBO  fbo_pong;
    RHIOffscreenFBO  fbo_composite;
    i32              loc_threshold;
    i32              loc_direction;
    i32              loc_bloom_strength;
    float            bloom_strength;
    float            threshold;
    bool             ready;
} PostProcess;

bool post_process_init(PostProcess *pp, RHIDevice *dev, u32 width, u32 height);
void post_process_shutdown(PostProcess *pp);
void post_process_apply(PostProcess *pp, RHICmdBuffer *cmd, RHITexture scene_color, u32 screen_w, u32 screen_h);
RHITexture post_process_get_bloom_texture(PostProcess *pp);
