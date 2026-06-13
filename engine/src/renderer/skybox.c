#include <renderer/skybox.h>
#include <core/log.h>
#include <math/math.h>
#ifndef ENGINE_VULKAN
#include <glad.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *skybox_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    fseek(f, 0, SEEK_SET);
    char *buf = malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

bool skybox_init(Skybox *sb, RHIDevice *dev) {
    sb->device = dev;
    sb->ready = false;

    usize vs_len = 0, fs_len = 0;
#ifdef ENGINE_VULKAN
    char *vs_src = skybox_read_file("shaders/skybox_vk.vert", &vs_len);
    char *fs_src = skybox_read_file("shaders/skybox_vk.frag", &fs_len);
#else
    char *vs_src = skybox_read_file("shaders/skybox.vert", &vs_len);
    char *fs_src = skybox_read_file("shaders/skybox.frag", &fs_len);
#endif
    if (!vs_src || !fs_src) {
        LOG_WARN("Skybox shaders not found");
        free(vs_src);
        free(fs_src);
        return false;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src);
    free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Skybox shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return false;
    }

    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .no_vertex_input = true, .depth_compare_lequal = true, .depth_write_disable = true,
                             .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT};
    sb->pipeline = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);

    if (!rhi_handle_valid(sb->pipeline)) {
        LOG_WARN("Skybox pipeline create failed");
        return false;
    }

    sb->loc_inv_proj = rhi_pipeline_get_uniform_location(dev, sb->pipeline, "u_inv_proj");
    sb->loc_view = rhi_pipeline_get_uniform_location(dev, sb->pipeline, "u_view");
    sb->loc_sun_dir = rhi_pipeline_get_uniform_location(dev, sb->pipeline, "u_sun_dir");
    sb->loc_sun_color = rhi_pipeline_get_uniform_location(dev, sb->pipeline, "u_sun_color");

    sb->ready = true;
    return true;
}

void skybox_shutdown(Skybox *sb) {
    if (!sb->device) return;
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

#ifndef ENGINE_VULKAN
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
#endif
    rhi_cmd_draw(cmd, 3, 1);
#ifndef ENGINE_VULKAN
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
#endif
}
