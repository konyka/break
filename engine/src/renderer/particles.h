#pragma once
#include <core/types.h>
#include <rhi/rhi.h>

#define PARTICLES_MAX 8192

/* Must mirror the std430 `Particle` struct in particle_update.comp and
 * particle.vert EXACTLY (4x vec4 = 64 bytes). The SSBO is GPU-only (compute
 * writes, vertex shader reads); the CPU only uses this to size a zeroed initial
 * buffer. previous_pos is initialized on spawn so newborn particles have zero
 * motion and cannot reproject unrelated history. */
typedef struct {
    f32 pos_life[4];      /* xyz = position, w = current life        */
    f32 vel_maxlife[4];   /* xyz = velocity, w = max lifetime        */
    f32 size_color[4];    /* x = size, yzw = color (linear RGB)      */
    f32 previous_pos[4];  /* xyz = position from prior frame          */
} GPUParticle;

typedef struct {
    RHIDevice   *device;
    RHIPipeline  compute_pipeline;
    RHIPipeline  cull_pipeline;
    RHIPipeline  render_pipeline;
    RHIBuffer    particle_ssbo;
    RHIBuffer    cull_buf;       /* draw_count + alive particle indices */
    RHIBuffer    spawn_buf;      /* R174: uint claimed for emit budget */
    RHISampler   sampler;
    RHITexture   particle_tex;
    bool         initialized;
    bool         cull_ready;
    u32          last_alive_count;
    f32          emit_accum;     /* R174: fractional emit carry */

    f32 emit_pos[3];
    f32 gravity;
    f32 emit_rate;
    f32 lifetime_min;
    f32 lifetime_range;
    f32 emit_vel_min[3];
    f32 emit_vel_max[3];

    /* Cached uniform locations — compute pipeline */
    i32 _loc_push_dt;              /* Vulkan: push.dt block */
    i32 _loc_dt;                   /* OpenGL loose uniforms */
    i32 _loc_emit_rate;
    i32 _loc_emit_pos;
    i32 _loc_gravity;
    i32 _loc_emit_vel_min;
    i32 _loc_emit_vel_max;
    i32 _loc_lifetime_min;
    i32 _loc_lifetime_range;
    i32 _loc_emit_budget;          /* R174: GL emit budget */
    /* Cached uniform locations — render pipeline */
    i32 _loc_view;
    i32 _loc_proj;

    /* Pre-built push constant template (Round 18) — only [0] (dt) changes per frame */
    f32 _push_template[20];
} ParticleSystem;

bool  particles_init(ParticleSystem *ps, RHIDevice *dev, bool forward_mrt);
void  particles_shutdown(ParticleSystem *ps);
void  particles_compute(ParticleSystem *ps, RHICmdBuffer *cmd, f32 dt);
void  particles_cull(ParticleSystem *ps, RHICmdBuffer *cmd);
void  particles_render(ParticleSystem *ps, RHICmdBuffer *cmd, const f32 *view, const f32 *proj);

/* Build a valid DrawIndirectCommand fallback when GPU culling is unavailable. */
static inline void particles_build_cull_fallback(u32 *words, usize word_count) {
    const usize required_words = 4u + PARTICLES_MAX;
    if (!words || word_count < required_words) return;

    /* Draw every slot through the same indexed DrawIndirect layout used by culling. */
    words[0] = 1u;
    words[1] = PARTICLES_MAX;
    words[2] = 0u;
    words[3] = 0u;
    for (u32 i = 0; i < PARTICLES_MAX; i++) words[4u + i] = i;
}
