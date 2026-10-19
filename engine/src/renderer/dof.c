#include <renderer/dof.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline dof_create_pipe_path(RHIDevice *dev, const char *vert_path,
                                        const char *frag_path) {
    RHIShader vs = rhi_shader_create_path(dev, vert_path, false);
    RHIShader fs = rhi_shader_create_path(dev, frag_path, true);
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("DOF: sidecar shader unavailable (%s, %s)", vert_path,
                 frag_path);
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return RHI_HANDLE_NULL;
    }
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs;
    pdesc.frag = fs;
    pdesc.no_vertex_input = true;
    pdesc.uses_textures = true;
    pdesc.depth_write_disable = true;
    pdesc.disable_culling = true;
    pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

static RHIPipeline dof_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("DOF: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("DOF: shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return RHI_HANDLE_NULL;
    }

    RHIPipelineDesc pdesc = {
        .vert = vs, .frag = fs,
        .no_vertex_input = true,
        .uses_textures = true,
        .depth_write_disable = true,
        .disable_culling = true,
    };
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

bool dof_init(DOFSystem *dof, RHIDevice *dev, u32 width, u32 height) {
    memset(dof, 0, sizeof(*dof));
    dof->device = dev;
    dof->focus_dist = -1.0f;
    dof->focus_range = 5.0f;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps)) {
        LOG_WARN("DOF: capability query failed");
        return false;
    }
    if (caps.shader_sidecar_paths) {
        /* R620: D3D12 never compiles HLSL in-process; the backend resolves
         * these to post_hlsl.vert / dof_hlsl.frag. */
        dof->dof_pipe = dof_create_pipe_path(dev, "shaders/post.vert",
                                             "shaders/dof.frag");
    } else {
        if (!shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
            !shader_variant_path("shaders/dof.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
            LOG_WARN("DOF: shader variant path failed");
            return false;
        }
        dof->dof_pipe = dof_create_pipe(dev, vs_path, fs_path);
    }

    if (!rhi_handle_valid(dof->dof_pipe)) {
        LOG_WARN("DOF: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_dof_* 是
     * dof(_vk).frag 的真实成员名，两后端同源，无别名行。 */
    dof->bind_pipe = rhi_pipeline_bindings_create(dev, dof->dof_pipe);
    if (!dof->bind_pipe)
        LOG_WARN("DOF: bindings create failed; uniform locations resolve -1");

    /* R347: main clamps render size to ≥1; width/2 can still be 0 → VK extent 0. */
    u32 pw = width / 2, ph = height / 2;
    if (pw < 1) pw = 1;
    if (ph < 1) ph = 1;

    dof->dof_fbo = rhi_offscreen_fbo_create_fmt(dev, pw, ph, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    dof->sampler = rhi_sampler_create(dev, &sdesc);

    if (!rhi_handle_valid(dof->dof_fbo.fb) || !rhi_handle_valid(dof->sampler)) {
        LOG_WARN("DOF: FBO/sampler creation failed");
        dof_shutdown(dof);
        return false;
    }

    dof->loc_focus_dist = rhi_pipeline_bindings_resolve(dof->bind_pipe, "u_dof_focus");
    dof->loc_focus_range = rhi_pipeline_bindings_resolve(dof->bind_pipe, "u_dof_range");
    dof->loc_near = rhi_pipeline_bindings_resolve(dof->bind_pipe, "u_dof_near");
    dof->loc_far = rhi_pipeline_bindings_resolve(dof->bind_pipe, "u_dof_far");
    dof->loc_screen_w = rhi_pipeline_bindings_resolve(dof->bind_pipe, "u_dof_sw");
    dof->loc_screen_h = rhi_pipeline_bindings_resolve(dof->bind_pipe, "u_dof_sh");

    dof->ready = true;
    LOG_INFO("DOF: initialized (%ux%u, focus=%.1f range=%.1f)", pw, ph, dof->focus_dist, dof->focus_range);
    return true;
}

void dof_shutdown(DOFSystem *dof) {
    if (!dof->device) return;
    if (dof->bind_pipe) { rhi_pipeline_bindings_destroy(dof->device, dof->bind_pipe); dof->bind_pipe = NULL; }
    if (rhi_handle_valid(dof->dof_fbo.fb)) rhi_offscreen_fbo_destroy(dof->device, &dof->dof_fbo);
    if (rhi_handle_valid(dof->sampler)) rhi_sampler_destroy(dof->device, dof->sampler);
    if (rhi_handle_valid(dof->dof_pipe)) rhi_pipeline_destroy(dof->device, dof->dof_pipe);
    dof->ready = false;
}

void dof_apply(DOFSystem *dof, RHICmdBuffer *cmd, RHITexture color_tex, RHITexture depth_tex,
               const f32 *inv_proj, u32 screen_w, u32 screen_h) {
    if (!dof->ready) return;
    (void)inv_proj;

    rhi_cmd_end_render_pass(cmd);

    rhi_offscreen_fbo_bind(cmd, &dof->dof_fbo);

    rhi_cmd_bind_pipeline(cmd, dof->dof_pipe);

    RHITexture tex[2] = { color_tex, depth_tex };
    rhi_cmd_bind_textures_multi(cmd, tex, 2, dof->sampler);

    if (dof->loc_focus_dist >= 0)  rhi_cmd_set_uniform_f32(cmd, dof->loc_focus_dist, dof->focus_dist);
    if (dof->loc_focus_range >= 0) rhi_cmd_set_uniform_f32(cmd, dof->loc_focus_range, dof->focus_range);
    if (dof->loc_near >= 0)        rhi_cmd_set_uniform_f32(cmd, dof->loc_near, 0.1f);
    if (dof->loc_far >= 0)         rhi_cmd_set_uniform_f32(cmd, dof->loc_far, 100.0f);
    if (dof->loc_screen_w >= 0)    rhi_cmd_set_uniform_f32(cmd, dof->loc_screen_w, (f32)screen_w);
    if (dof->loc_screen_h >= 0)    rhi_cmd_set_uniform_f32(cmd, dof->loc_screen_h, (f32)screen_h);

    rhi_cmd_draw(cmd, 3, 1);

    /* R196-B: skip intermediate swapchain CLEAR unbind. */
}

RHITexture dof_get_texture(DOFSystem *dof) {
    return dof->ready ? dof->dof_fbo.color_tex : RHI_HANDLE_NULL;
}
