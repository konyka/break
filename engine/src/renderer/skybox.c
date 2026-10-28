#include <renderer/skybox.h>
#include <core/log.h>
#include <math/math.h>
#include <core/shader_io.h>
/* R81-2: Removed #include <glad.h> — no more direct GL calls in this file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool skybox_init(Skybox *sb, RHIDevice *dev, bool forward_mrt) {
    sb->device = dev;
    sb->ready = false;

    usize vs_len = 0, fs_len = 0;
    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps)) {
        LOG_WARN("Skybox: capability query failed");
        return false;
    }
    RHIShader vs, fs;
    if (caps.shader_sidecar_paths) {
        /* R606: D3D12 never compiles GLSL; its shaders are hand-authored HLSL
         * sidecars resolved from the requested path by the backend, which
         * gains an idempotent "_hlsl" before the stage extension. skybox.vert
         * has no FORWARD_MRT arm, so one vertex sidecar serves both pipeline
         * shapes; only the fragment stage differs, so the MRT one is requested
         * under the _mrt name the sidecar derivation then resolves. */
        LOG_INFO("skybox: backend resolves shader sidecars; loading "
                 "shaders/skybox.vert as skybox_hlsl.vert and "
                 "shaders/skybox%s.frag as skybox%s_hlsl.frag",
                 forward_mrt ? "_mrt" : "", forward_mrt ? "_mrt" : "");
        vs = rhi_shader_create_path(dev, "shaders/skybox.vert", false);
        fs = rhi_shader_create_path(dev,
                                    forward_mrt ? "shaders/skybox_mrt.frag"
                                                : "shaders/skybox.frag", true);
    } else {
        if (!shader_variant_path("shaders/skybox.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
            !shader_variant_path("shaders/skybox.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
            LOG_WARN("Skybox: capability query or shader variant path failed");
            return false;
        }
        char *vs_src = shader_read_file(vs_path, &vs_len);
        char *fs_src = shader_read_file(fs_path, &fs_len);
        if (!vs_src || !fs_src) {
            LOG_WARN("Skybox shaders not found");
            free(vs_src);
            free(fs_src);
            return false;
        }

        usize fs_mrt_len = 0;
        char *fs_mrt = forward_mrt ? shader_inject_define(fs_src, fs_len, "FORWARD_MRT", &fs_mrt_len) : NULL;
        vs = rhi_shader_create(dev, vs_src, vs_len, false);
        fs = rhi_shader_create(dev, fs_mrt ? fs_mrt : fs_src,
                               fs_mrt ? fs_mrt_len : fs_len, true);
        free(vs_src);
        free(fs_src);
        free(fs_mrt);
    }

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Skybox shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return false;
    }

    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .no_vertex_input = true, .depth_compare_lequal = true, .depth_write_disable = true,
                             .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT};
    if (forward_mrt) {
        pdesc.mrt_attachment_count = 2u;
        pdesc.mrt_formats[0] = RHI_FORMAT_R16G16B16A16_SFLOAT;
        pdesc.mrt_formats[1] = RHI_FORMAT_R16G16_SFLOAT;
    }
    sb->pipeline = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);

    if (!rhi_handle_valid(sb->pipeline)) {
        LOG_WARN("Skybox pipeline create failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_inv_proj/u_view
     * 在 skybox_vk.vert 与 skybox_vk.frag 的 push 块里偏移一致（0/64），
     * u_sun_dir/u_sun_color 是 frag 成员；两后端同名同源，无别名行。 */
    sb->bind_pipeline = rhi_pipeline_bindings_create(dev, sb->pipeline);
    if (!sb->bind_pipeline)
        LOG_WARN("Skybox: bindings create failed; uniform locations resolve -1");

    sb->loc_inv_proj = rhi_pipeline_bindings_resolve(sb->bind_pipeline, "u_inv_proj");
    sb->loc_view = rhi_pipeline_bindings_resolve(sb->bind_pipeline, "u_view");
    sb->loc_sun_dir = rhi_pipeline_bindings_resolve(sb->bind_pipeline, "u_sun_dir");
    sb->loc_sun_color = rhi_pipeline_bindings_resolve(sb->bind_pipeline, "u_sun_color");

    sb->ready = true;
    return true;
}

void skybox_shutdown(Skybox *sb) {
    if (!sb->device) return;
    if (sb->bind_pipeline) { rhi_pipeline_bindings_destroy(sb->device, sb->bind_pipeline); sb->bind_pipeline = NULL; }
    if (rhi_handle_valid(sb->pipeline)) rhi_pipeline_destroy(sb->device, sb->pipeline);
    sb->ready = false;
}

void skybox_render(Skybox *sb, RHICmdBuffer *cmd, const f32 *view, const f32 *inv_proj,
                   f32 sun_dx, f32 sun_dy, f32 sun_dz,
                   f32 sun_r, f32 sun_g, f32 sun_b) {
    if (!sb->ready) return;

    rhi_cmd_bind_pipeline(cmd, sb->pipeline);

    rhi_cmd_set_uniform_mat4(cmd, sb->loc_inv_proj, inv_proj);
    rhi_cmd_set_uniform_mat4(cmd, sb->loc_view, view);

    if (sb->loc_sun_dir >= 0)   rhi_cmd_set_uniform_vec3(cmd, sb->loc_sun_dir, sun_dx, sun_dy, sun_dz);
    if (sb->loc_sun_color >= 0) rhi_cmd_set_uniform_vec3(cmd, sb->loc_sun_color, sun_r, sun_g, sun_b);

    /* R78-2/R80-2: All state changes go through cached RHI paths — no direct
     * GL calls that could bypass caches (depth func, depth mask, cull face). */
    rhi_cmd_set_depth_func_less_or_equal(cmd);
    rhi_cmd_set_depth_mask(cmd, false);
    rhi_cmd_set_cull_face(cmd, false);
    rhi_cmd_draw(cmd, 3, 1);
    rhi_cmd_set_cull_face(cmd, true);
    rhi_cmd_set_depth_mask(cmd, true);
    rhi_cmd_set_depth_func_less(cmd);
}
