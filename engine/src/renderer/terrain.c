#include <renderer/terrain.h>
#include <core/log.h>
#include <math/math.h>
#ifndef ENGINE_VULKAN
#include <glad.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static f32 terrain_height_func(f32 x, f32 z) {
    return sinf(x * 0.3f) * cosf(z * 0.3f) * 2.0f + sinf(x * 0.1f + z * 0.15f) * 3.0f;
}

bool terrain_init(Terrain *t, RHIDevice *dev, u32 grid_size, f32 scale, f32 height_scale) {
    t->device = dev;
    t->grid_size = grid_size;
    t->scale = scale;
    t->height_scale = height_scale;
    t->index_count = 0;

    usize vs_len = 0, fs_len = 0;
    char *vs_src = NULL;
    char *fs_src = NULL;
    FILE *f;

    f = fopen("shaders/terrain.vert", "rb");
    if (f) {
        fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET);
        vs_src = malloc((usize)sz + 1);
        vs_len = fread(vs_src, 1, (usize)sz, f);
        vs_src[vs_len] = '\0';
        fclose(f);
    }
    f = fopen("shaders/terrain.frag", "rb");
    if (f) {
        fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET);
        fs_src = malloc((usize)sz + 1);
        fs_len = fread(fs_src, 1, (usize)sz, f);
        fs_src[fs_len] = '\0';
        fclose(f);
    }

    if (!vs_src || !fs_src) {
        free(vs_src); free(fs_src);
        LOG_WARN("Terrain shaders not found — using blinn_phong");
    }

    RHIShader vs, fs;
    if (vs_src && fs_src) {
        vs = rhi_shader_create(dev, vs_src, vs_len, false);
        fs = rhi_shader_create(dev, fs_src, fs_len, true);
        free(vs_src); free(fs_src);
    } else {
        usize bl_vs_len = 0, bl_fs_len = 0;
        char *bl_vs = NULL;
        char *bl_fs = NULL;
        FILE *bf;
#ifdef ENGINE_VULKAN
        bf = fopen("shaders/blinn_phong_vk.vert", "rb");
#else
        bf = fopen("shaders/blinn_phong.vert", "rb");
#endif
        if (bf) {
            fseek(bf, 0, SEEK_END); long sz = ftell(bf); fseek(bf, 0, SEEK_SET);
            bl_vs = malloc((usize)sz + 1);
            bl_vs_len = fread(bl_vs, 1, (usize)sz, bf);
            bl_vs[bl_vs_len] = '\0';
            fclose(bf);
        }
#ifdef ENGINE_VULKAN
        bf = fopen("shaders/blinn_phong_vk.frag", "rb");
#else
        bf = fopen("shaders/blinn_phong.frag", "rb");
#endif
        if (bf) {
            fseek(bf, 0, SEEK_END); long sz = ftell(bf); fseek(bf, 0, SEEK_SET);
            bl_fs = malloc((usize)sz + 1);
            bl_fs_len = fread(bl_fs, 1, (usize)sz, bf);
            bl_fs[bl_fs_len] = '\0';
            fclose(bf);
        }
        vs = rhi_shader_create(dev, bl_vs, bl_vs_len, false);
        fs = rhi_shader_create(dev, bl_fs, bl_fs_len, true);
        free(bl_vs); free(bl_fs);
    }

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Terrain shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return false;
    }

    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .uses_textures = true, .disable_culling = true};
    t->pipeline = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);

    if (!rhi_handle_valid(t->pipeline)) return false;

    t->loc_model       = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_model");
    t->loc_view        = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_view");
    t->loc_proj        = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_proj");
    t->loc_light_dir   = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_light_dir");
    t->loc_light_color = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_light_color");
    t->loc_ambient     = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_ambient");
    t->loc_camera_pos  = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_camera_pos");
    t->loc_albedo      = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_albedo");

    u32 vert_count = grid_size * grid_size;
    u32 idx_count = (grid_size - 1) * (grid_size - 1) * 6;

    f32 *verts = calloc(vert_count, 8 * sizeof(f32));
    u32 *indices = calloc(idx_count, sizeof(u32));

    for (u32 z = 0; z < grid_size; z++) {
        for (u32 x = 0; x < grid_size; x++) {
            u32 vi = (z * grid_size + x) * 8;
            f32 fx = ((f32)x / (f32)(grid_size - 1) - 0.5f) * scale;
            f32 fz = ((f32)z / (f32)(grid_size - 1) - 0.5f) * scale;
            f32 fy = terrain_height_func(fx, fz) * height_scale;

            verts[vi + 0] = fx;
            verts[vi + 1] = fy;
            verts[vi + 2] = fz;

            f32 hx = 0.1f;
            f32 hz = 0.1f;
            f32 hl = terrain_height_func(fx - hx, fz) * height_scale;
            f32 hr = terrain_height_func(fx + hx, fz) * height_scale;
            f32 hd = terrain_height_func(fx, fz - hz) * height_scale;
            f32 hu = terrain_height_func(fx, fz + hz) * height_scale;

            f32 nx = hl - hr;
            f32 ny = 2.0f * hx;
            f32 nz = hd - hu;
            f32 nl = sqrtf(nx * nx + ny * ny + nz * nz);
            if (nl > 0.0001f) { nx /= nl; ny /= nl; nz /= nl; }

            verts[vi + 3] = nx;
            verts[vi + 4] = ny;
            verts[vi + 5] = nz;
            verts[vi + 6] = (f32)x / (f32)(grid_size - 1);
            verts[vi + 7] = (f32)z / (f32)(grid_size - 1);
        }
    }

    u32 ii = 0;
    for (u32 z = 0; z < grid_size - 1; z++) {
        for (u32 x = 0; x < grid_size - 1; x++) {
            u32 tl = z * grid_size + x;
            u32 tr = tl + 1;
            u32 bl = tl + grid_size;
            u32 br = bl + 1;
            indices[ii++] = tl; indices[ii++] = bl; indices[ii++] = tr;
            indices[ii++] = tr; indices[ii++] = bl; indices[ii++] = br;
        }
    }
    t->index_count = ii;

    RHIBufferDesc vbdesc = {
        .usage = RHI_BUFFER_USAGE_VERTEX,
        .size = vert_count * 8 * sizeof(f32),
        .initial_data = verts,
    };
    t->vbo = rhi_buffer_create(dev, &vbdesc);
    free(verts);

    RHIBufferDesc ibdesc = {
        .usage = RHI_BUFFER_USAGE_INDEX,
        .size = idx_count * sizeof(u32),
        .initial_data = indices,
    };
    t->ibo = rhi_buffer_create(dev, &ibdesc);
    free(indices);

    LOG_INFO("Terrain created: %ux%u grid, %u indices", grid_size, grid_size, t->index_count);
    return true;
}

void terrain_shutdown(Terrain *t) {
    if (!t->device) return;
    if (rhi_handle_valid(t->ibo))      rhi_buffer_destroy(t->device, t->ibo);
    if (rhi_handle_valid(t->vbo))      rhi_buffer_destroy(t->device, t->vbo);
    if (rhi_handle_valid(t->pipeline)) rhi_pipeline_destroy(t->device, t->pipeline);
}

void terrain_render(Terrain *t, RHICmdBuffer *cmd,
                    const f32 *view, const f32 *proj,
                    const f32 camera_pos[3],
                    RHITexture fallback_tex, RHISampler sampler) {
    if (t->index_count == 0) return;

    Mat4 model = mat4_identity();
    rhi_cmd_bind_pipeline(cmd, t->pipeline);
    rhi_cmd_set_uniform_mat4(cmd, t->loc_model, &model.e[0][0]);
    rhi_cmd_set_uniform_mat4(cmd, t->loc_view, view);
    rhi_cmd_set_uniform_mat4(cmd, t->loc_proj, proj);
    rhi_cmd_set_uniform_vec3(cmd, t->loc_light_dir, 0.5f, -0.8f, 0.3f);
    rhi_cmd_set_uniform_vec3(cmd, t->loc_light_color, 1.0f, 0.95f, 0.9f);
    rhi_cmd_set_uniform_vec3(cmd, t->loc_ambient, 0.35f, 0.35f, 0.40f);
    if (camera_pos) rhi_cmd_set_uniform_vec3(cmd, t->loc_camera_pos, camera_pos[0], camera_pos[1], camera_pos[2]);
    if (t->loc_albedo >= 0) rhi_cmd_set_uniform_i32(cmd, t->loc_albedo, 0);
    rhi_cmd_bind_texture(cmd, fallback_tex, sampler, 0);
    rhi_cmd_bind_vertex_buffer(cmd, t->vbo, 0);
    rhi_cmd_bind_index_buffer(cmd, t->ibo, 0);
    rhi_cmd_draw_indexed(cmd, t->index_count, 1);
}

f32 terrain_get_height(const Terrain *t, f32 x, f32 z) {
    (void)t;
    return terrain_height_func(x, z) * t->height_scale;
}
