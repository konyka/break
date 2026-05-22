#include <renderer/particles.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc((usize)sz + 1);
    usize len = fread(buf, 1, (usize)sz, f);
    buf[len] = '\0';
    fclose(f);
    *out_len = len;
    return buf;
}

bool particles_init(ParticleSystem *ps, RHIDevice *dev) {
    memset(ps, 0, sizeof(*ps));
    ps->device = dev;
    ps->initialized = false;

    ps->emit_pos[0] = 0.0f; ps->emit_pos[1] = 2.0f; ps->emit_pos[2] = 0.0f;
    ps->gravity = 9.8f;
    ps->emit_rate = 200.0f;
    ps->lifetime_min = 1.0f;
    ps->lifetime_range = 2.0f;
    ps->emit_vel_min[0] = -2.0f; ps->emit_vel_min[1] = 3.0f;  ps->emit_vel_min[2] = -2.0f;
    ps->emit_vel_max[0] =  2.0f; ps->emit_vel_max[1] = 6.0f;  ps->emit_vel_max[2] =  2.0f;

    /* ---- Compute pipeline (particle update) ---- */
    usize cs_len = 0;
    char *cs_src = read_file("shaders/particle_update.comp", &cs_len);
    if (!cs_src) {
        LOG_WARN("Particle compute shader not found — particles disabled");
        return false;
    }

    RHIShader cs = rhi_shader_create_compute(dev, cs_src, cs_len);
    free(cs_src);
    if (!rhi_handle_valid(cs)) {
        LOG_WARN("Particle compute shader compile failed");
        return false;
    }

    RHIPipelineDesc cpdesc = {0};
    cpdesc.frag = cs;
    cpdesc.is_compute = true;
    ps->compute_pipeline = rhi_pipeline_create(dev, &cpdesc);
    rhi_shader_destroy(dev, cs);

    if (!rhi_handle_valid(ps->compute_pipeline)) {
        LOG_WARN("Particle compute pipeline creation failed");
        return false;
    }

    /* ---- Graphics pipeline (particle render) ---- */
    usize vs_len = 0, fs_len = 0;
    char *vs_src = read_file("shaders/particle.vert", &vs_len);
    char *fs_src = read_file("shaders/particle.frag", &fs_len);
    if (!vs_src || !fs_src) {
        free(vs_src); free(fs_src);
        LOG_WARN("Particle render shaders not found");
        rhi_pipeline_destroy(dev, ps->compute_pipeline);
        return false;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        rhi_pipeline_destroy(dev, ps->compute_pipeline);
        LOG_WARN("Particle render shader compile failed");
        return false;
    }

    RHIPipelineDesc rpdesc = {0};
    rpdesc.vert = vs;
    rpdesc.frag = fs;
    rpdesc.no_vertex_input = true;
    rpdesc.uses_storage = true;
    rpdesc.alpha_blend = true;
    rpdesc.depth_write_disable = true;
    ps->render_pipeline = rhi_pipeline_create(dev, &rpdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);

    if (!rhi_handle_valid(ps->render_pipeline)) {
        rhi_pipeline_destroy(dev, ps->compute_pipeline);
        LOG_WARN("Particle render pipeline creation failed");
        return false;
    }

    /* ---- Particle SSBO ---- */
    RHIBufferDesc bdesc = {
        .usage = RHI_BUFFER_USAGE_STORAGE,
        .size = PARTICLES_MAX * sizeof(GPUParticle),
        .initial_data = NULL,
    };
    ps->particle_ssbo = rhi_buffer_create(dev, &bdesc);

    /* ---- Sampler + fallback texture ---- */
    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    ps->sampler = rhi_sampler_create(dev, &sdesc);

    u8 white[4] = {255, 255, 200, 255};
    RHITextureDesc tdesc = { .width = 1, .height = 1, .format = RHI_FORMAT_R8G8B8A8_UNORM, .mip_levels = 1, .data = white };
    ps->particle_tex = rhi_texture_create(dev, &tdesc);

    /* Initialize all particles as dead (life <= 0) */
    void *mapped = rhi_buffer_map(dev, ps->particle_ssbo);
    if (mapped) {
        memset(mapped, 0, PARTICLES_MAX * sizeof(GPUParticle));
        rhi_buffer_unmap(dev, ps->particle_ssbo);
    }

    ps->initialized = true;
    LOG_INFO("Particle system initialized (%u particles, compute-driven)", PARTICLES_MAX);
    return true;
}

void particles_shutdown(ParticleSystem *ps) {
    if (!ps->device) return;
    if (rhi_handle_valid(ps->particle_tex))       rhi_texture_destroy(ps->device, ps->particle_tex);
    if (rhi_handle_valid(ps->sampler))             rhi_sampler_destroy(ps->device, ps->sampler);
    if (rhi_handle_valid(ps->particle_ssbo))       rhi_buffer_destroy(ps->device, ps->particle_ssbo);
    if (rhi_handle_valid(ps->render_pipeline))     rhi_pipeline_destroy(ps->device, ps->render_pipeline);
    if (rhi_handle_valid(ps->compute_pipeline))    rhi_pipeline_destroy(ps->device, ps->compute_pipeline);
    ps->initialized = false;
}

void particles_compute(ParticleSystem *ps, RHICmdBuffer *cmd, f32 dt) {
    if (!ps->initialized) return;

    rhi_cmd_end_render_pass(cmd);

    rhi_cmd_bind_pipeline(cmd, ps->compute_pipeline);
    rhi_cmd_bind_storage_buffer(cmd, ps->particle_ssbo, 0);

    i32 loc = rhi_pipeline_get_uniform_location(ps->device, ps->compute_pipeline, "push.dt");
    if (loc >= 0) {
        f32 push_data[20];
        memset(push_data, 0, sizeof(push_data));
        push_data[0] = dt;
        push_data[1] = ps->emit_rate;
        push_data[4] = ps->emit_pos[0];
        push_data[5] = ps->emit_pos[1];
        push_data[6] = ps->emit_pos[2];
        push_data[7] = ps->gravity;
        push_data[8]  = ps->emit_vel_min[0];
        push_data[9]  = ps->emit_vel_min[1];
        push_data[10] = ps->emit_vel_min[2];
        push_data[12] = ps->emit_vel_max[0];
        push_data[13] = ps->emit_vel_max[1];
        push_data[14] = ps->emit_vel_max[2];
        push_data[15] = ps->lifetime_min;
        push_data[19] = ps->lifetime_range;
        rhi_cmd_set_uniform_mat4(cmd, loc, push_data);
    }

    rhi_cmd_dispatch(cmd, PARTICLES_MAX / 256, 1, 1);
    rhi_cmd_memory_barrier(cmd);

    rhi_cmd_begin_render_pass(cmd);
}

void particles_render(ParticleSystem *ps, RHICmdBuffer *cmd, const f32 *view, const f32 *proj) {
    if (!ps->initialized) return;

    rhi_cmd_bind_pipeline(cmd, ps->render_pipeline);
    rhi_cmd_bind_storage_buffer(cmd, ps->particle_ssbo, 0);

    i32 loc_view = rhi_pipeline_get_uniform_location(ps->device, ps->render_pipeline, "push.view");
    if (loc_view >= 0) rhi_cmd_set_uniform_mat4(cmd, loc_view, view);
    i32 loc_proj = rhi_pipeline_get_uniform_location(ps->device, ps->render_pipeline, "push.proj");
    if (loc_proj >= 0) rhi_cmd_set_uniform_mat4(cmd, loc_proj, proj);

    rhi_cmd_draw(cmd, PARTICLES_MAX, 1);
}
