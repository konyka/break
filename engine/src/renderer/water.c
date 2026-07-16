#include <renderer/water.h>
#include <core/log.h>
#include <math/math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static char *file_read(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    char *buf = malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

bool water_init(WaterPlane *w, RHIDevice *dev, f32 water_y, f32 size) {
    w->device = dev;
    w->water_y = water_y;
    w->time = 0.0f;
    w->time_scale = 1.0f;
    w->color = vec3(0.1f, 0.3f, 0.5f);
    w->enabled = true;
    w->render_above = false;
    w->sampler = RHI_HANDLE_NULL;

    usize vs_len = 0, fs_len = 0;
    char *vs_src = NULL, *fs_src = NULL;

#ifdef ENGINE_VULKAN
    vs_src = file_read("shaders/water_vk.vert", &vs_len);
    fs_src = file_read("shaders/water_vk.frag", &fs_len);
#else
    vs_src = file_read("shaders/water.vert", &vs_len);
    fs_src = file_read("shaders/water.frag", &fs_len);
#endif

    if (!vs_src || !fs_src) {
        LOG_WARN("Water shaders not found");
        free(vs_src); free(fs_src);
        return false;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Water shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return false;
    }

    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .uses_textures = true,
                             .disable_culling = true, .alpha_blend = true,
                             .water_layout = true,
                             .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT};
    w->pipeline = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);

    if (!rhi_handle_valid(w->pipeline)) return false;

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    w->sampler = rhi_sampler_create(dev, &sdesc);

    w->loc_view = rhi_pipeline_get_uniform_location(dev, w->pipeline, "u_view");
    w->loc_proj = rhi_pipeline_get_uniform_location(dev, w->pipeline, "u_proj");
    w->loc_time = rhi_pipeline_get_uniform_location(dev, w->pipeline, "u_time");
    w->loc_camera_pos = rhi_pipeline_get_uniform_location(dev, w->pipeline, "u_camera_pos");
    w->loc_water_color = rhi_pipeline_get_uniform_location(dev, w->pipeline, "u_water_color");
w->loc_light_vp = rhi_pipeline_get_uniform_location(dev, w->pipeline, "u_light_vp");
w->loc_shadow_bias = rhi_pipeline_get_uniform_location(dev, w->pipeline, "u_shadow_bias");
w->loc_water_y = rhi_pipeline_get_uniform_location(dev, w->pipeline, "u_water_y");
w->loc_model = rhi_pipeline_get_uniform_location(dev, w->pipeline, "u_model");

    f32 hs = size * 0.5f;
    f32 verts[] = {
        -hs, 0.0f, -hs,
         hs, 0.0f, -hs,
         hs, 0.0f,  hs,
        -hs, 0.0f,  hs
    };
    u32 indices[] = { 0, 1, 2, 0, 2, 3 };

    RHIBufferDesc vbdesc = { .usage = RHI_BUFFER_USAGE_VERTEX, .size = sizeof(verts), .initial_data = verts };
    w->vbo = rhi_buffer_create(dev, &vbdesc);

    RHIBufferDesc ibdesc = { .usage = RHI_BUFFER_USAGE_INDEX, .size = sizeof(indices), .initial_data = indices };
    w->ibo = rhi_buffer_create(dev, &ibdesc);

    if (!rhi_handle_valid(w->vbo) || !rhi_handle_valid(w->ibo)) {
        LOG_WARN("Water: buffer creation failed");
        water_shutdown(w);
        return false;
    }

    LOG_INFO("Water plane initialized at y=%.1f (%.0fx%.0f)", water_y, size, size);
    return true;
}

void water_shutdown(WaterPlane *w) {
    if (!w->device) return;
    if (rhi_handle_valid(w->ibo))      rhi_buffer_destroy(w->device, w->ibo);
    if (rhi_handle_valid(w->vbo))      rhi_buffer_destroy(w->device, w->vbo);
    if (rhi_handle_valid(w->sampler))  rhi_sampler_destroy(w->device, w->sampler);
    if (rhi_handle_valid(w->pipeline)) rhi_pipeline_destroy(w->device, w->pipeline);
}

void water_update(WaterPlane *w, f32 dt) {
    w->time += dt * w->time_scale;
}

void water_render(WaterPlane *w, RHICmdBuffer *cmd,
                  const f32 *view, const f32 *proj,
                  const f32 camera_pos[3],
                  RHITexture shadow_map, const f32 *light_vp,
                  f32 shadow_bias) {
    if (!w->enabled || !rhi_handle_valid(w->pipeline)) return;

    rhi_cmd_bind_pipeline(cmd, w->pipeline);
    rhi_cmd_set_uniform_mat4(cmd, w->loc_view, view);
    rhi_cmd_set_uniform_mat4(cmd, w->loc_proj, proj);
    rhi_cmd_set_uniform_f32(cmd, w->loc_time, w->time);
    if (w->loc_camera_pos >= 0) rhi_cmd_set_uniform_vec3(cmd, w->loc_camera_pos, camera_pos[0], camera_pos[1], camera_pos[2]);
    if (w->loc_water_color >= 0) rhi_cmd_set_uniform_vec3(cmd, w->loc_water_color, w->color.e[0], w->color.e[1], w->color.e[2]);
    if (w->loc_shadow_bias >= 0) rhi_cmd_set_uniform_f32(cmd, w->loc_shadow_bias, shadow_bias);
    if (w->loc_water_y >= 0) rhi_cmd_set_uniform_f32(cmd, w->loc_water_y, w->water_y);
    if (w->loc_light_vp >= 0 && light_vp) rhi_cmd_set_uniform_mat4(cmd, w->loc_light_vp, light_vp);
    if (rhi_handle_valid(shadow_map) && rhi_handle_valid(w->sampler))
        rhi_cmd_bind_texture(cmd, shadow_map, w->sampler, 1);

    /* Cached model matrix — only water_y changes per frame */
    static Mat4 model = {0};
    static f32 cached_y = -1e30f;
    if (cached_y != w->water_y) {
        model = mat4_identity();
        model.e[3][1] = w->water_y;
        cached_y = w->water_y;
    }
    if (w->loc_model >= 0) rhi_cmd_set_uniform_mat4(cmd, w->loc_model, &model.e[0][0]);

    rhi_cmd_bind_vertex_buffer(cmd, w->vbo, 0);
    rhi_cmd_bind_index_buffer(cmd, w->ibo, 0, true);
    rhi_cmd_draw_indexed(cmd, 6, 1);
}
