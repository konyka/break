#include <renderer/particles.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    char *buf = malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize len = fread(buf, 1, (usize)sz, f);
    buf[len] = '\0';
    fclose(f);
    if (out_len) *out_len = len;
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

    /* ---- GPU alive-particle cull (Round 12) ---- */
    usize cull_len = 0;
    char *cull_src = read_file("shaders/particle_cull.comp", &cull_len);
    if (cull_src) {
        RHIShader cull_cs = rhi_shader_create_compute(dev, cull_src, cull_len);
        free(cull_src);
        if (rhi_handle_valid(cull_cs)) {
            RHIPipelineDesc cull_desc = {0};
            cull_desc.frag = cull_cs;
            cull_desc.is_compute = true;
            cull_desc.uses_storage = true;
            ps->cull_pipeline = rhi_pipeline_create(dev, &cull_desc);
            rhi_shader_destroy(dev, cull_cs);
        }
    }
    if (!rhi_handle_valid(ps->cull_pipeline)) {
        LOG_WARN("Particle cull shader unavailable — will draw all slots");
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
    rpdesc.point_list = true; /* R168-C: POINT_LIST + gl_PointSize / PointCoord */
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

    /* ---- Cull output: DrawIndirectCommand + alive indices (R167) ----
     * Layout: vertexCount, instanceCount, firstVertex, firstInstance, indices[].
     * STORAGE|INDIRECT so compute can write instanceCount and draw_indirect can read. */
    RHIBufferDesc cull_desc_buf = {
        .usage = RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_INDIRECT,
        .size = 4u * sizeof(u32) + PARTICLES_MAX * sizeof(u32),
        .initial_data = NULL,
    };
    ps->cull_buf = rhi_buffer_create(dev, &cull_desc_buf);
    ps->cull_ready = rhi_handle_valid(ps->cull_buf) && rhi_handle_valid(ps->cull_pipeline);
    /* R175: Seed DrawIndirect header once; per-frame only GPU-clears instanceCount. */
    if (ps->cull_ready) {
        u32 hdr[4] = {1u, 0u, 0u, 0u};
        rhi_buffer_update(dev, ps->cull_buf, hdr, sizeof(hdr));
    }

    /* R174: Spawn claim counter for exact emit_rate budgeting. */
    RHIBufferDesc spawn_desc = {
        .usage = RHI_BUFFER_USAGE_STORAGE,
        .size = sizeof(u32),
        .initial_data = NULL,
    };
    ps->spawn_buf = rhi_buffer_create(dev, &spawn_desc);
    ps->emit_accum = 0.0f;

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

    /* R122: Validate all RHI resources before marking system initialized. */
    if (!rhi_handle_valid(ps->particle_ssbo) ||
        !rhi_handle_valid(ps->spawn_buf) ||
        !rhi_handle_valid(ps->sampler) ||
        !rhi_handle_valid(ps->particle_tex)) {
        LOG_WARN("Particle: buffer/texture/sampler creation failed");
        particles_shutdown(ps);
        return false;
    }

    /* Initialize all particles as dead (life <= 0) */
    void *mapped = rhi_buffer_map(dev, ps->particle_ssbo);
    if (mapped) {
        memset(mapped, 0, PARTICLES_MAX * sizeof(GPUParticle));
        rhi_buffer_unmap(dev, ps->particle_ssbo);
    }

    ps->initialized = true;
    ps->last_alive_count = 0;

    /* Build push constant template (Round 18): static fields baked once,
     * only [0] (dt) is overwritten each frame in particles_compute. */
    memset(ps->_push_template, 0, sizeof(ps->_push_template));
    ps->_push_template[1]  = ps->emit_rate;
    ps->_push_template[4]  = ps->emit_pos[0];
    ps->_push_template[5]  = ps->emit_pos[1];
    ps->_push_template[6]  = ps->emit_pos[2];
    ps->_push_template[7]  = ps->gravity;
    ps->_push_template[8]  = ps->emit_vel_min[0];
    ps->_push_template[9]  = ps->emit_vel_min[1];
    ps->_push_template[10] = ps->emit_vel_min[2];
    ps->_push_template[12] = ps->emit_vel_max[0];
    ps->_push_template[13] = ps->emit_vel_max[1];
    ps->_push_template[14] = ps->emit_vel_max[2];
    ps->_push_template[15] = ps->lifetime_min;
    ps->_push_template[19] = ps->lifetime_range;

    /* Cache all uniform locations (compute + render pipelines) */
    ps->_loc_push_dt       = rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "push.dt");
    ps->_loc_dt            = rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "u_dt");
    ps->_loc_emit_rate     = rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "u_emit_rate");
    ps->_loc_emit_pos      = rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "u_emit_pos");
    ps->_loc_gravity       = rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "u_gravity");
    ps->_loc_emit_vel_min  = rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "u_emit_vel_min");
    ps->_loc_emit_vel_max  = rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "u_emit_vel_max");
    ps->_loc_lifetime_min  = rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "u_lifetime_min");
    ps->_loc_lifetime_range= rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "u_lifetime_range");
    ps->_loc_emit_budget   = rhi_pipeline_get_uniform_location(dev, ps->compute_pipeline, "u_emit_budget");
#ifdef ENGINE_VULKAN
    ps->_loc_view = rhi_pipeline_get_uniform_location(dev, ps->render_pipeline, "push.view");
    ps->_loc_proj = rhi_pipeline_get_uniform_location(dev, ps->render_pipeline, "push.proj");
#else
    ps->_loc_view = rhi_pipeline_get_uniform_location(dev, ps->render_pipeline, "u_view");
    ps->_loc_proj = rhi_pipeline_get_uniform_location(dev, ps->render_pipeline, "u_proj");
#endif

    LOG_INFO("Particle system initialized (%u particles, compute-driven%s)",
             PARTICLES_MAX, ps->cull_ready ? ", GPU cull" : "");
    return true;
}

void particles_shutdown(ParticleSystem *ps) {
    if (!ps->device) return;
    if (rhi_handle_valid(ps->particle_tex))       rhi_texture_destroy(ps->device, ps->particle_tex);
    if (rhi_handle_valid(ps->sampler))             rhi_sampler_destroy(ps->device, ps->sampler);
    if (rhi_handle_valid(ps->cull_buf))            rhi_buffer_destroy(ps->device, ps->cull_buf);
    if (rhi_handle_valid(ps->spawn_buf))           rhi_buffer_destroy(ps->device, ps->spawn_buf);
    if (rhi_handle_valid(ps->particle_ssbo))       rhi_buffer_destroy(ps->device, ps->particle_ssbo);
    if (rhi_handle_valid(ps->cull_pipeline))       rhi_pipeline_destroy(ps->device, ps->cull_pipeline);
    if (rhi_handle_valid(ps->render_pipeline))     rhi_pipeline_destroy(ps->device, ps->render_pipeline);
    if (rhi_handle_valid(ps->compute_pipeline))    rhi_pipeline_destroy(ps->device, ps->compute_pipeline);
    ps->initialized = false;
    ps->cull_ready = false;
}

void particles_compute(ParticleSystem *ps, RHICmdBuffer *cmd, f32 dt) {
    if (!ps->initialized) return;

    rhi_cmd_end_render_pass(cmd);

    /* R174: Integer emit budget from rate*dt with fractional carry. */
    ps->emit_accum += ps->emit_rate * dt;
    u32 budget = 0u;
    if (ps->emit_accum >= 1.0f) {
        budget = (u32)ps->emit_accum;
        ps->emit_accum -= (f32)budget;
        if (budget > PARTICLES_MAX) budget = PARTICLES_MAX;
    }
    rhi_cmd_fill_buffer(cmd, ps->spawn_buf, 0, sizeof(u32), 0u);

    rhi_cmd_bind_pipeline(cmd, ps->compute_pipeline);
    rhi_cmd_bind_storage_buffer(cmd, ps->particle_ssbo, 0);
    rhi_cmd_bind_storage_buffer(cmd, ps->spawn_buf, 1);

#ifdef ENGINE_VULKAN
    if (ps->_loc_push_dt >= 0) {
        f32 push_data[20];
        memcpy(push_data, ps->_push_template, sizeof(push_data));
        push_data[0] = dt;
        push_data[1] = ps->emit_rate;
        push_data[2] = (f32)budget; /* pad0 = emit budget */
        push_data[4] = ps->emit_pos[0];
        push_data[5] = ps->emit_pos[1];
        push_data[6] = ps->emit_pos[2];
        push_data[7] = ps->gravity;
        rhi_cmd_set_uniform_mat4(cmd, ps->_loc_push_dt, push_data);
    }
#else
    if (ps->_loc_dt >= 0)            rhi_cmd_set_uniform_f32(cmd, ps->_loc_dt, dt);
    if (ps->_loc_emit_rate >= 0)     rhi_cmd_set_uniform_f32(cmd, ps->_loc_emit_rate, ps->emit_rate);
    if (ps->_loc_emit_budget >= 0)   rhi_cmd_set_uniform_f32(cmd, ps->_loc_emit_budget, (f32)budget);
    if (ps->_loc_emit_pos >= 0)      rhi_cmd_set_uniform_vec3(cmd, ps->_loc_emit_pos, ps->emit_pos[0], ps->emit_pos[1], ps->emit_pos[2]);
    if (ps->_loc_gravity >= 0)       rhi_cmd_set_uniform_f32(cmd, ps->_loc_gravity, ps->gravity);
    if (ps->_loc_emit_vel_min >= 0)  rhi_cmd_set_uniform_vec3(cmd, ps->_loc_emit_vel_min, ps->emit_vel_min[0], ps->emit_vel_min[1], ps->emit_vel_min[2]);
    if (ps->_loc_emit_vel_max >= 0)  rhi_cmd_set_uniform_vec3(cmd, ps->_loc_emit_vel_max, ps->emit_vel_max[0], ps->emit_vel_max[1], ps->emit_vel_max[2]);
    if (ps->_loc_lifetime_min >= 0)  rhi_cmd_set_uniform_f32(cmd, ps->_loc_lifetime_min, ps->lifetime_min);
    if (ps->_loc_lifetime_range >= 0) rhi_cmd_set_uniform_f32(cmd, ps->_loc_lifetime_range, ps->lifetime_range);
#endif

    rhi_cmd_dispatch(cmd, PARTICLES_MAX / 256, 1, 1);
    rhi_cmd_memory_barrier(cmd);

    rhi_cmd_begin_render_pass(cmd);
}

void particles_cull(ParticleSystem *ps, RHICmdBuffer *cmd) {
    if (!ps->initialized || !ps->cull_ready) return;

    rhi_cmd_end_render_pass(cmd);

    /* R175: GPU-clear instanceCount only — host memcpy raced with in-flight
     * draw_indirect / prior cull on HOST_VISIBLE STORAGE|INDIRECT. */
    rhi_cmd_fill_buffer(cmd, ps->cull_buf, sizeof(u32), sizeof(u32), 0u);

    rhi_cmd_bind_pipeline(cmd, ps->cull_pipeline);
    rhi_cmd_bind_storage_buffer(cmd, ps->particle_ssbo, 0);
    rhi_cmd_bind_storage_buffer(cmd, ps->cull_buf, 1);
    rhi_cmd_dispatch(cmd, (PARTICLES_MAX + 255) / 256, 1, 1);
    rhi_cmd_memory_barrier(cmd);

    rhi_cmd_begin_render_pass(cmd);
}

void particles_render(ParticleSystem *ps, RHICmdBuffer *cmd, const f32 *view, const f32 *proj) {
    if (!ps->initialized) return;

    rhi_cmd_bind_pipeline(cmd, ps->render_pipeline);
    rhi_cmd_bind_storage_buffer(cmd, ps->particle_ssbo, 0);
    if (ps->cull_ready)
        rhi_cmd_bind_storage_buffer(cmd, ps->cull_buf, 1);

    if (ps->_loc_view >= 0) rhi_cmd_set_uniform_mat4(cmd, ps->_loc_view, view);
    if (ps->_loc_proj >= 0) rhi_cmd_set_uniform_mat4(cmd, ps->_loc_proj, proj);

    if (ps->cull_ready) {
        /* R167: GPU-driven instance count — only alive particles invoke VS.
         * Avoids scheduling PARTICLES_MAX (8192) empty early-out invocations.
         * No CPU readback (R86-2): last_alive_count stays as upper-bound hint. */
        rhi_cmd_draw_indirect(ps->device, ps->cull_buf, 0, 1, 16);
        ps->last_alive_count = PARTICLES_MAX; /* upper bound; exact needs readback */
    } else {
        rhi_cmd_draw(cmd, 1, PARTICLES_MAX);
        ps->last_alive_count = PARTICLES_MAX;
    }
}
