#include <renderer/forward_velocity.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline fv_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("ForwardVelocity: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
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

bool forward_velocity_init(ForwardVelocitySystem *sys, RHIDevice *dev, u32 w, u32 h) {
    if (!sys || !dev) return false;
    memset(sys, 0, sizeof(*sys));
    sys->device = dev;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps) ||
        !shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
        !shader_variant_path("shaders/camera_velocity.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
        LOG_WARN("ForwardVelocity: capability query or shader variant path failed");
        return false;
    }
    sys->pipe = fv_create_pipe(dev, vs_path, fs_path);
    if (!rhi_handle_valid(sys->pipe)) {
        LOG_WARN("ForwardVelocity: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。本管线是
     * no_vertex_input 族：camera_velocity(_vk).frag 把 u_inv_proj/
     * u_curr_vp/u_prev_vp 全部声明为真实 push 成员（u_prev_vp@128），
     * 成员行优先于 rhi_vk.c 的 u_prev_vp→u_prev_mvp 别名行，resolve
     * 与 legacy no_vertex_input 行为（128）一致；别名行只作用于声明
     * u_prev_mvp 的 gbuffer 顶点输入族（legacy 192）。 */
    sys->bind_pipe = rhi_pipeline_bindings_create(dev, sys->pipe);
    if (!sys->bind_pipe)
        LOG_WARN("ForwardVelocity: bindings create failed; uniform locations resolve -1");

    sys->fbo = rhi_offscreen_fbo_create_fmt(dev, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u     = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v     = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w     = RHI_WRAP_CLAMP_TO_EDGE,
    };
    sys->sampler = rhi_sampler_create(dev, &sdesc);

    /* R350: align R348 — do not mark ready with empty FBO/sampler. */
    if (!rhi_handle_valid(sys->fbo.fb) || !rhi_handle_valid(sys->sampler)) {
        LOG_WARN("ForwardVelocity: FBO/sampler creation failed");
        forward_velocity_shutdown(sys);
        return false;
    }

    sys->loc_inv_proj = rhi_pipeline_bindings_resolve(sys->bind_pipe, "u_inv_proj");
    sys->loc_curr_vp  = rhi_pipeline_bindings_resolve(sys->bind_pipe, "u_curr_vp");
    sys->loc_prev_vp  = rhi_pipeline_bindings_resolve(sys->bind_pipe, "u_prev_vp");

    sys->ready = true;
    LOG_INFO("ForwardVelocity: initialized (%ux%u)", w, h);
    return true;
}

void forward_velocity_shutdown(ForwardVelocitySystem *sys) {
    if (!sys || !sys->device) return;
    if (sys->bind_pipe) { rhi_pipeline_bindings_destroy(sys->device, sys->bind_pipe); sys->bind_pipe = NULL; }
    if (rhi_handle_valid(sys->fbo.fb)) rhi_offscreen_fbo_destroy(sys->device, &sys->fbo);
    if (rhi_handle_valid(sys->sampler)) rhi_sampler_destroy(sys->device, sys->sampler);
    if (rhi_handle_valid(sys->pipe)) rhi_pipeline_destroy(sys->device, sys->pipe);
    sys->ready = false;
}

void forward_velocity_apply(ForwardVelocitySystem *sys, RHICmdBuffer *cmd,
                            RHITexture depth_tex,
                            const f32 *inv_proj, const f32 *curr_vp, const f32 *prev_vp,
                            u32 w, u32 h) {
    if (!sys || !sys->ready || !rhi_handle_valid(sys->fbo.fb)) return;

    rhi_offscreen_fbo_bind(cmd, &sys->fbo);
    rhi_cmd_bind_pipeline(cmd, sys->pipe);
    rhi_cmd_bind_texture(cmd, depth_tex, sys->sampler, 0u);
    if (inv_proj && sys->loc_inv_proj >= 0)
        rhi_cmd_set_uniform_mat4(cmd, sys->loc_inv_proj, inv_proj);
    if (curr_vp && sys->loc_curr_vp >= 0)
        rhi_cmd_set_uniform_mat4(cmd, sys->loc_curr_vp, curr_vp);
    if (prev_vp && sys->loc_prev_vp >= 0)
        rhi_cmd_set_uniform_mat4(cmd, sys->loc_prev_vp, prev_vp);
    rhi_cmd_draw(cmd, 3u, 1u);
    (void)w; (void)h;
}

RHITexture forward_velocity_get_texture(ForwardVelocitySystem *sys) {
    if (!sys || !sys->ready) return RHI_HANDLE_NULL;
    return sys->fbo.color_tex;
}
