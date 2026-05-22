#pragma once
#include <core/types.h>
#include <rhi/rhi.h>

#define PARTICLES_MAX 8192

typedef struct {
    f32 pos[3];
    f32 life;
    f32 vel[3];
    f32 max_life;
    f32 size;
    f32 color[3];
    f32 alpha;
} GPUParticle;

typedef struct {
    RHIDevice   *device;
    RHIPipeline  compute_pipeline;
    RHIPipeline  render_pipeline;
    RHIBuffer    particle_ssbo;
    RHISampler   sampler;
    RHITexture   particle_tex;
    bool         initialized;

    f32 emit_pos[3];
    f32 gravity;
    f32 emit_rate;
    f32 lifetime_min;
    f32 lifetime_range;
    f32 emit_vel_min[3];
    f32 emit_vel_max[3];
} ParticleSystem;

bool  particles_init(ParticleSystem *ps, RHIDevice *dev);
void  particles_shutdown(ParticleSystem *ps);
void  particles_compute(ParticleSystem *ps, RHICmdBuffer *cmd, f32 dt);
void  particles_render(ParticleSystem *ps, RHICmdBuffer *cmd, const f32 *view, const f32 *proj);
