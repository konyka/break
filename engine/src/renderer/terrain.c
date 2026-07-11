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

/* fast_rsqrt provided by math/math.h */

static f32 terrain_height_func(f32 x, f32 z) {
    return sinf(x * 0.3f) * cosf(z * 0.3f) * 2.0f + sinf(x * 0.1f + z * 0.15f) * 3.0f;
}

static f32 terrain_sample_height(const Terrain *t, i32 gx, i32 gz) {
    if (gx < 0) { gx = 0; } else if (gx >= (i32)t->grid_size) { gx = (i32)t->grid_size - 1; }
    if (gz < 0) { gz = 0; } else if (gz >= (i32)t->grid_size) { gz = (i32)t->grid_size - 1; }
    return t->heightmap[gz * t->grid_size + gx];
}

static void terrain_rebuild_region(Terrain *t, i32 gx0, i32 gz0, i32 gx1, i32 gz1) {
    if (gx0 < 0) { gx0 = 0; } if (gz0 < 0) { gz0 = 0; }
    if (gx1 >= (i32)t->grid_size) { gx1 = (i32)t->grid_size - 1; }
    if (gz1 >= (i32)t->grid_size) { gz1 = (i32)t->grid_size - 1; }

    f32 inv = 1.0f / t->inv_nm1;
    i32 row_width = gx1 - gx0 + 1;

    if (!t->_vert_staging) {
        /* Fallback: per-vertex upload (no staging buffer — e.g. test harness) */
        for (i32 gz = gz0; gz <= gz1; gz++) {
            for (i32 gx = gx0; gx <= gx1; gx++) {
                f32 fx = ((f32)gx * inv - 0.5f) * t->scale;
                f32 fz = ((f32)gz * inv - 0.5f) * t->scale;
                f32 fy = t->heightmap[gz * t->grid_size + gx] * t->height_scale;
                f32 hx = (t->scale / (f32)t->grid_size) * 0.5f;
                f32 hl = terrain_sample_height(t, gx - 1, gz) * t->height_scale;
                f32 hr = terrain_sample_height(t, gx + 1, gz) * t->height_scale;
                f32 hd = terrain_sample_height(t, gx, gz - 1) * t->height_scale;
                f32 hu = terrain_sample_height(t, gx, gz + 1) * t->height_scale;
                f32 nx = hl - hr, ny = 2.0f * hx, nz = hd - hu;
                f32 nl2 = nx * nx + ny * ny + nz * nz;
                if (nl2 > 0.0000001f) { f32 inv = fast_rsqrt(nl2); nx *= inv; ny *= inv; nz *= inv; }
                f32 verts[8] = { fx, fy, fz, nx, ny, nz, (f32)gx * inv, (f32)gz * inv };
                u32 offset = (u32)(gz * (i32)t->grid_size + gx) * 8 * sizeof(f32);
                rhi_buffer_update_region(t->device, t->vbo, offset, verts, sizeof(verts));
            }
        }
        return;
    }

    /* Batch upload per row: row_width vertices in one GPU call instead of
     * one call per vertex.  Uses persistent staging buffer. */
    f32 hx = (t->scale / (f32)t->grid_size) * 0.5f;
    f32 ny = 2.0f * hx;
    for (i32 gz = gz0; gz <= gz1; gz++) {
        f32 *row = t->_vert_staging;
        for (i32 gx = gx0; gx <= gx1; gx++) {
            i32 li = (gx - gx0) * 8;
            f32 fx = ((f32)gx * inv - 0.5f) * t->scale;
            f32 fz = ((f32)gz * inv - 0.5f) * t->scale;
            f32 fy = t->heightmap[gz * t->grid_size + gx] * t->height_scale;

            f32 hl = terrain_sample_height(t, gx - 1, gz) * t->height_scale;
            f32 hr = terrain_sample_height(t, gx + 1, gz) * t->height_scale;
            f32 hd = terrain_sample_height(t, gx, gz - 1) * t->height_scale;
            f32 hu = terrain_sample_height(t, gx, gz + 1) * t->height_scale;

            f32 nx = hl - hr;
            f32 ny_n = ny;  /* local copy for normalization */
            f32 nz = hd - hu;
            f32 nl2 = nx * nx + ny_n * ny_n + nz * nz;
            if (nl2 > 0.0000001f) { f32 inv_l = fast_rsqrt(nl2); nx *= inv_l; ny_n *= inv_l; nz *= inv_l; }

            row[li + 0] = fx; row[li + 1] = fy; row[li + 2] = fz;
            row[li + 3] = nx; row[li + 4] = ny_n; row[li + 5] = nz;
            row[li + 6] = (f32)gx * inv; row[li + 7] = (f32)gz * inv;
        }
        u32 offset = (u32)(gz * (i32)t->grid_size + gx0) * 8 * sizeof(f32);
        rhi_buffer_update_region(t->device, t->vbo, offset, row,
                                 (u32)row_width * 8 * sizeof(f32));
    }
}

/* Read a whole file into a malloc'd buffer; returns length via *out_len. */
static char *terrain_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    if (sz <= 0) { fclose(f); return NULL; }
    char *buf = (char *)malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

bool terrain_init(Terrain *t, RHIDevice *dev, u32 grid_size, f32 scale, f32 height_scale) {
    /* R161-A: Validate grid_size to prevent unsigned underflow in (grid_size - 1)
     * expressions.  grid_size=0 causes (grid_size-1) to wrap to 0xFFFFFFFF,
     * making the index-generation loop run ~4 billion iterations and write far
     * past the 24-byte indices allocation — a massive heap buffer overflow.
     * grid_size=1 causes division by zero in (f32)(grid_size-1) divisors. */
    if (grid_size < 2) {
        LOG_ERROR("Terrain: grid_size must be >= 2 (got %u)", grid_size);
        return false;
    }
    t->device = dev;
    t->grid_size = grid_size;
    t->scale = scale;
    t->inv_scale = (scale > 0.0f) ? 1.0f / scale : 0.0f;
    t->inv_nm1 = (f32)(grid_size - 1);
    t->height_scale = height_scale;
    t->index_count = 0;

    /* Single alloc: heightmap (f32[grid_size²]) + _vert_staging (f32[grid_size*8]) */
    usize hm_bytes = (usize)grid_size * grid_size * sizeof(f32);
    usize vs_bytes = (usize)grid_size * 8 * sizeof(f32);
    u8 *terrain_block = (u8 *)calloc(1, hm_bytes + vs_bytes);
    if (!terrain_block) return false;
    t->heightmap = (f32 *)terrain_block;
    t->_vert_staging = (f32 *)(terrain_block + hm_bytes);
    t->_vert_staging_cap = grid_size;

    for (u32 z = 0; z < grid_size; z++) {
        for (u32 x = 0; x < grid_size; x++) {
            f32 fx = ((f32)x / (f32)(grid_size - 1) - 0.5f) * scale;
            f32 fz = ((f32)z / (f32)(grid_size - 1) - 0.5f) * scale;
            t->heightmap[z * grid_size + x] = terrain_height_func(fx, fz);
        }
    }

    usize vs_len = 0, fs_len = 0;
    char *vs_src = NULL;
    char *fs_src = NULL;

#ifdef ENGINE_VULKAN
    vs_src = terrain_read_file("shaders/terrain_vk.vert", &vs_len);
    fs_src = terrain_read_file("shaders/terrain_vk.frag", &fs_len);
#else
    vs_src = terrain_read_file("shaders/terrain.vert", &vs_len);
    fs_src = terrain_read_file("shaders/terrain.frag", &fs_len);
#endif

    if (!vs_src || !fs_src) {
        free(vs_src); free(fs_src);
        LOG_WARN("Terrain shaders not found — using blinn_phong");
    }

    RHIShader vs, fs;
    bool used_terrain_shaders = false;
    if (vs_src && fs_src) {
        vs = rhi_shader_create(dev, vs_src, vs_len, false);
        fs = rhi_shader_create(dev, fs_src, fs_len, true);
        free(vs_src); free(fs_src);
        used_terrain_shaders = true;
    } else {
        usize bl_vs_len = 0, bl_fs_len = 0;
        char *bl_vs = NULL;
        char *bl_fs = NULL;
#ifdef ENGINE_VULKAN
        bl_vs = terrain_read_file("shaders/blinn_phong_vk.vert", &bl_vs_len);
        bl_fs = terrain_read_file("shaders/blinn_phong_vk.frag", &bl_fs_len);
#else
        bl_vs = terrain_read_file("shaders/blinn_phong.vert", &bl_vs_len);
        bl_fs = terrain_read_file("shaders/blinn_phong.frag", &bl_fs_len);
#endif
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

    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .uses_textures = true,
                             .disable_culling = true,
                             .terrain_layout = used_terrain_shaders,
                             .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT};
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
t->loc_shadow_bias = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_shadow_bias");
t->loc_light_vp    = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_light_vp");
t->loc_water_y     = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_water_y");
t->loc_time        = rhi_pipeline_get_uniform_location(dev, t->pipeline, "u_time");

    u32 vert_count = grid_size * grid_size;
    u32 idx_count = (grid_size - 1) * (grid_size - 1) * 6;

    /* Single allocation: verts + indices → 1 calloc, 1 free. */
    usize vert_bytes = (usize)vert_count * 8 * sizeof(f32);
    usize idx_bytes  = (usize)idx_count * sizeof(u32);
    u8 *geom_block = (u8 *)calloc(1, vert_bytes + idx_bytes);
    if (!geom_block) return false;
    f32 *verts   = (f32 *)geom_block;
    u32 *indices = (u32 *)(geom_block + vert_bytes);

    for (u32 z = 0; z < grid_size; z++) {
        for (u32 x = 0; x < grid_size; x++) {
            u32 vi = (z * grid_size + x) * 8;
            f32 fx = ((f32)x / (f32)(grid_size - 1) - 0.5f) * scale;
            f32 fz = ((f32)z / (f32)(grid_size - 1) - 0.5f) * scale;
            f32 fy = t->heightmap[z * grid_size + x] * height_scale;

            verts[vi + 0] = fx;
            verts[vi + 1] = fy;
            verts[vi + 2] = fz;

            f32 hx = (scale / (f32)grid_size) * 0.5f;
            f32 hl = terrain_sample_height(t, (i32)x - 1, (i32)z) * height_scale;
            f32 hr = terrain_sample_height(t, (i32)x + 1, (i32)z) * height_scale;
            f32 hd = terrain_sample_height(t, (i32)x, (i32)z - 1) * height_scale;
            f32 hu = terrain_sample_height(t, (i32)x, (i32)z + 1) * height_scale;

            f32 nx = hl - hr;
            f32 ny = 2.0f * hx;
            f32 nz = hd - hu;
            f32 nl2 = nx * nx + ny * ny + nz * nz;
            if (nl2 > 0.0000001f) { f32 inv_l = fast_rsqrt(nl2); nx *= inv_l; ny *= inv_l; nz *= inv_l; }

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

    /* R187: VBO is edited by brush/generate — keep HOST_VISIBLE (no initial_data).
     * IBO stays DEVICE_LOCAL via initial_data. */
    RHIBufferDesc vbdesc = {
        .usage = RHI_BUFFER_USAGE_VERTEX,
        .size = vert_count * 8 * sizeof(f32),
        .initial_data = NULL,
    };
    t->vbo = rhi_buffer_create(dev, &vbdesc);
    if (rhi_handle_valid(t->vbo))
        rhi_buffer_update(dev, t->vbo, verts, vert_count * 8 * sizeof(f32));

    RHIBufferDesc ibdesc = {
        .usage = RHI_BUFFER_USAGE_INDEX,
        .size = idx_count * sizeof(u32),
        .initial_data = indices,
    };
    t->ibo = rhi_buffer_create(dev, &ibdesc);
    free(geom_block);  /* Single free: verts + indices in one block */

    if (!rhi_handle_valid(t->vbo) || !rhi_handle_valid(t->ibo)) {
        LOG_WARN("Terrain: buffer creation failed");
        terrain_shutdown(t);
        return false;
    }

    LOG_INFO("Terrain created: %ux%u grid, %u indices", grid_size, grid_size, t->index_count);
    /* _vert_staging already allocated as part of heightmap single block */
    return true;
}

void terrain_shutdown(Terrain *t) {
    if (!t->device) return;
    free(t->heightmap); t->heightmap = NULL; t->_vert_staging = NULL; /* single alloc */
    free(t->_flatten_indices); t->_flatten_indices = NULL; t->_flatten_dists = NULL; /* single alloc */
    if (rhi_handle_valid(t->ibo))      rhi_buffer_destroy(t->device, t->ibo);
    if (rhi_handle_valid(t->vbo))      rhi_buffer_destroy(t->device, t->vbo);
    if (rhi_handle_valid(t->pipeline)) rhi_pipeline_destroy(t->device, t->pipeline);
}

void terrain_render(Terrain *t, RHICmdBuffer *cmd,
                    const f32 *view, const f32 *proj,
                    const f32 camera_pos[3],
                    RHITexture fallback_tex, RHISampler sampler,
                    RHITexture shadow_map, const f32 *light_vp,
                    f32 shadow_bias, f32 water_y, f32 time) {
    if (t->index_count == 0) return;

    static const Mat4 identity_model = { .e = {
        {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}
    }};
    rhi_cmd_bind_pipeline(cmd, t->pipeline);
    rhi_cmd_set_uniform_mat4(cmd, t->loc_model, &identity_model.e[0][0]);
    rhi_cmd_set_uniform_mat4(cmd, t->loc_view, view);
    rhi_cmd_set_uniform_mat4(cmd, t->loc_proj, proj);
    if (t->loc_light_dir >= 0) {
        /* R97-1: Normalize light direction — terrain_vk.frag no longer normalizes
         * (R96-3 removed normalize(-u_light_dir)). Original (0.5,-0.8,0.3) had
         * length 0.98995, causing ~1% brightness error. */
        f32 ldx = 0.5f, ldy = -0.8f, ldz = 0.3f;
        f32 llen = sqrtf(ldx*ldx + ldy*ldy + ldz*ldz);
        if (llen > 1e-20f) { f32 inv = 1.0f / llen; ldx *= inv; ldy *= inv; ldz *= inv; }
        rhi_cmd_set_uniform_vec3(cmd, t->loc_light_dir, ldx, ldy, ldz);
    }
    if (t->loc_light_color >= 0) rhi_cmd_set_uniform_vec3(cmd, t->loc_light_color, 1.0f, 0.95f, 0.9f);
    if (t->loc_ambient >= 0) rhi_cmd_set_uniform_vec3(cmd, t->loc_ambient, 0.35f, 0.35f, 0.40f);
    if (camera_pos) rhi_cmd_set_uniform_vec3(cmd, t->loc_camera_pos, camera_pos[0], camera_pos[1], camera_pos[2]);
    if (t->loc_albedo >= 0) rhi_cmd_set_uniform_i32(cmd, t->loc_albedo, 0);
    if (t->loc_shadow_bias >= 0) rhi_cmd_set_uniform_f32(cmd, t->loc_shadow_bias, shadow_bias);
    if (t->loc_light_vp >= 0 && light_vp) rhi_cmd_set_uniform_mat4(cmd, t->loc_light_vp, light_vp);
    if (t->loc_water_y >= 0) rhi_cmd_set_uniform_f32(cmd, t->loc_water_y, water_y);
    if (t->loc_time >= 0) rhi_cmd_set_uniform_f32(cmd, t->loc_time, time);
    /* R99-2: Use rhi_cmd_bind_material_textures instead of two rhi_cmd_bind_texture
     * calls. In the VK path, rhi_cmd_bind_texture ignores the unit parameter and
     * binds all 9 descriptor slots to the same texture — the second call would
     * overwrite the first, making the shader see shadow_map on binding 0 (u_albedo)
     * instead of the terrain texture. rhi_cmd_bind_material_textures correctly
     * assigns albedo→binding 0 and shadow→binding 1 in a single descriptor set. */
    rhi_cmd_bind_material_textures(cmd, fallback_tex, fallback_tex, fallback_tex,
                                   fallback_tex, shadow_map, fallback_tex, sampler);
    rhi_cmd_bind_vertex_buffer(cmd, t->vbo, 0);
    rhi_cmd_bind_index_buffer(cmd, t->ibo, 0);
    rhi_cmd_draw_indexed(cmd, t->index_count, 1);
}

f32 terrain_get_height(const Terrain *t, f32 x, f32 z) {
    if (!t->heightmap) return 0.0f;
    f32 gx = (x * t->inv_scale + 0.5f) * t->inv_nm1;
    f32 gz = (z * t->inv_scale + 0.5f) * t->inv_nm1;
    i32 ix = (i32)floorf(gx); i32 iz = (i32)floorf(gz);
    f32 fx = gx - (f32)ix; f32 fz = gz - (f32)iz;
    f32 h00 = terrain_sample_height(t, ix, iz);
    f32 h10 = terrain_sample_height(t, ix + 1, iz);
    f32 h01 = terrain_sample_height(t, ix, iz + 1);
    f32 h11 = terrain_sample_height(t, ix + 1, iz + 1);
    f32 h = h00 * (1 - fx) * (1 - fz) + h10 * fx * (1 - fz) + h01 * (1 - fx) * fz + h11 * fx * fz;
    return h * t->height_scale;
}

void terrain_modify_height(Terrain *t, f32 wx, f32 wz, f32 radius, f32 strength) {
    if (!t->heightmap) return;
    t->modify_count++;
    t->total_delta += fabsf(strength);
    { f32 hc=t->scale*0.5f; t->edit_quadrant[(wx<hc?0:1)+(wz<hc?0:2)]++; }
    f32 inv = 1.0f / t->inv_nm1;
    i32 gr = (i32)(radius * t->inv_scale * (f32)t->grid_size) + 1;
    f32 cgx = (wx * t->inv_scale + 0.5f) * t->inv_nm1;
    f32 cgz = (wz * t->inv_scale + 0.5f) * t->inv_nm1;
    i32 gx0 = (i32)floorf(cgx) - gr;
    i32 gz0 = (i32)floorf(cgz) - gr;
    i32 gx1 = (i32)ceilf(cgx) + gr;
    i32 gz1 = (i32)ceilf(cgz) + gr;
    if (gx0 < 0) { gx0 = 0; } if (gz0 < 0) { gz0 = 0; }
    if (gx1 >= (i32)t->grid_size) { gx1 = (i32)t->grid_size - 1; }
    if (gz1 >= (i32)t->grid_size) { gz1 = (i32)t->grid_size - 1; }

    f32 r2 = radius * radius;
    f32 inv_r2 = 1.0f / r2;
    for (i32 gz = gz0; gz <= gz1; gz++) {
        for (i32 gx = gx0; gx <= gx1; gx++) {
            f32 fwx = ((f32)gx * inv - 0.5f) * t->scale;
            f32 fwz = ((f32)gz * inv - 0.5f) * t->scale;
            f32 dx = fwx - wx; f32 dz = fwz - wz;
            f32 d2 = dx * dx + dz * dz;
            if (d2 < r2) {
                f32 falloff = 1.0f - d2 * inv_r2;
                t->heightmap[gz * t->grid_size + gx] += strength * falloff;
            }
        }
    }
    terrain_rebuild_region(t, gx0 - 1, gz0 - 1, gx1 + 1, gz1 + 1);
}

void terrain_flatten(Terrain *t, f32 wx, f32 wz, f32 radius) {
    if (!t->heightmap) return;
    t->modify_count++;
    t->total_delta += radius * 0.1f;
    { f32 hc=t->scale*0.5f; t->edit_quadrant[(wx<hc?0:1)+(wz<hc?0:2)]++; }
    f32 inv = 1.0f / t->inv_nm1;
    i32 gr = (i32)(radius * t->inv_scale * (f32)t->grid_size) + 1;
    f32 cgx = (wx * t->inv_scale + 0.5f) * t->inv_nm1;
    f32 cgz = (wz * t->inv_scale + 0.5f) * t->inv_nm1;
    i32 gx0 = (i32)floorf(cgx) - gr;
    i32 gz0 = (i32)floorf(cgz) - gr;
    i32 gx1 = (i32)ceilf(cgx) + gr;
    i32 gz1 = (i32)ceilf(cgz) + gr;
    if (gx0 < 0) { gx0 = 0; } if (gz0 < 0) { gz0 = 0; }
    if (gx1 >= (i32)t->grid_size) { gx1 = (i32)t->grid_size - 1; }
    if (gz1 >= (i32)t->grid_size) { gz1 = (i32)t->grid_size - 1; }

    f32 r2 = radius * radius;
    f32 avg = 0.0f;
    i32 cnt = 0;

    /* Single-pass: collect matching indices and heights, then apply flatten.
     * Avoids redundant coordinate transform + distance check in second pass. */
    i32 area = (gx1 - gx0 + 1) * (gz1 - gz0 + 1);
    /* Use persistent buffers — grow if needed, never shrink */
    if ((u32)area > t->_flatten_cap) {
        free(t->_flatten_indices); /* single alloc: indices + dists */
        /* Merge: i32 indices[area] + f32 dists[area] in one block */
        usize ind_bytes = (usize)area * sizeof(i32);
        usize dist_off  = (ind_bytes + 3u) & ~(usize)3u; /* align to f32 */
        u8 *flat_block  = (u8 *)malloc(dist_off + (usize)area * sizeof(f32));
        if (!flat_block) return;
        t->_flatten_indices = (i32 *)flat_block;
        t->_flatten_dists   = (f32 *)(flat_block + dist_off);
        t->_flatten_cap = (u32)area;
    }
    i32 *indices = t->_flatten_indices;
    f32 *dists   = t->_flatten_dists;
    if (!indices || !dists) return;

    for (i32 gz = gz0; gz <= gz1; gz++) {
        for (i32 gx = gx0; gx <= gx1; gx++) {
            f32 fwx = ((f32)gx * inv - 0.5f) * t->scale;
            f32 fwz = ((f32)gz * inv - 0.5f) * t->scale;
            f32 dx = fwx - wx; f32 dz = fwz - wz;
            f32 d2 = dx * dx + dz * dz;
            if (d2 < r2) {
                indices[cnt] = gz * (i32)t->grid_size + gx;
                dists[cnt] = d2;
                avg += t->heightmap[indices[cnt]];
                cnt++;
            }
        }
    }
    if (cnt == 0) return;
    avg /= (f32)cnt;
    f32 inv_r2 = 1.0f / r2;
    for (i32 k = 0; k < cnt; k++) {
        f32 falloff = 1.0f - dists[k] * inv_r2;
        f32 *h = &t->heightmap[indices[k]];
        *h += (avg - *h) * falloff * 0.2f;
    }
    terrain_rebuild_region(t, gx0 - 1, gz0 - 1, gx1 + 1, gz1 + 1);
}

void terrain_erode(Terrain *t, f32 wx, f32 wz, f32 radius, i32 iterations) {
    if (!t->heightmap) return;
    t->modify_count++;
    t->total_delta += (f32)iterations * 0.1f;
    { f32 hc=t->scale*0.5f; t->edit_quadrant[(wx<hc?0:1)+(wz<hc?0:2)]++; }
    i32 n = (i32)t->grid_size;
    f32 inv = 1.0f / t->inv_nm1;

    /* Compute grid-space bounds for the erosion radius (like terrain_modify_height) */
    f32 cgx = (wx * t->inv_scale + 0.5f) * t->inv_nm1;
    f32 cgz = (wz * t->inv_scale + 0.5f) * t->inv_nm1;
    f32 gr  = radius * t->inv_scale * t->inv_nm1;
    i32 gx0 = (i32)(cgx - gr) - 1;  if (gx0 < 1)     gx0 = 1;
    i32 gx1 = (i32)(cgx + gr) + 2;  if (gx1 > n - 1) gx1 = n - 1;
    i32 gz0 = (i32)(cgz - gr) - 1;  if (gz0 < 1)     gz0 = 1;
    i32 gz1 = (i32)(cgz + gr) + 2;  if (gz1 > n - 1) gz1 = n - 1;

    for (i32 it = 0; it < iterations; it++) {
        for (i32 gz = gz0; gz < gz1; gz++) {
            for (i32 gx = gx0; gx < gx1; gx++) {
                f32 h = t->heightmap[gz * n + gx];
                f32 h_l = t->heightmap[gz * n + gx - 1];
                f32 h_r = t->heightmap[gz * n + gx + 1];
                f32 h_u = t->heightmap[(gz-1) * n + gx];
                f32 h_d = t->heightmap[(gz+1) * n + gx];
                f32 max_d = 0.0f;
                f32 total_d = 0.0f;
                f32 diffs[4] = { h - h_l, h - h_r, h - h_u, h - h_d };
                for (i32 d = 0; d < 4; d++) {
                    if (diffs[d] > 0.0f) { total_d += diffs[d]; if (diffs[d] > max_d) max_d = diffs[d]; }
                }
                if (max_d <= 0.0f) continue;
                f32 fwx = ((f32)gx * inv - 0.5f) * t->scale;
                f32 fwz = ((f32)gz * inv - 0.5f) * t->scale;
                f32 dx2 = fwx - wx; f32 dz2 = fwz - wz;
                if (dx2*dx2 + dz2*dz2 > radius*radius) continue;
                f32 amount = fminf(max_d, h * 0.5f) * 0.5f;
                t->heightmap[gz * n + gx] -= amount;
                f32 inv_total_d = 1.0f / total_d;
                f32 share[4] = {0,0,0,0};
                for (i32 d = 0; d < 4; d++) if (diffs[d] > 0.0f) share[d] = diffs[d] * inv_total_d;
                t->heightmap[gz * n + gx - 1] += amount * share[0];
                t->heightmap[gz * n + gx + 1] += amount * share[1];
                t->heightmap[(gz-1) * n + gx] += amount * share[2];
                t->heightmap[(gz+1) * n + gx] += amount * share[3];
            }
        }
    }
    terrain_rebuild_region(t, gx0 > 1 ? gx0 - 1 : 0, gz0 > 1 ? gz0 - 1 : 0,
                           gx1 < n - 1 ? gx1 + 1 : n - 1, gz1 < n - 1 ? gz1 + 1 : n - 1);
}

static f32 simple_noise(f32 x, f32 z) {
    return sinf(x * 1.3f + 0.5f) * cosf(z * 0.9f + 1.2f) * 0.5f
         + sinf(x * 2.7f + z * 1.8f) * 0.25f
         + cosf(x * 0.4f - z * 3.1f) * 0.25f;
}

void terrain_noise_stamp(Terrain *t, f32 wx, f32 wz, f32 radius, f32 strength, f32 seed) {
    if (!t->heightmap) return;
    t->modify_count++;
    t->total_delta += fabsf(strength);
    { f32 hc=t->scale*0.5f; t->edit_quadrant[(wx<hc?0:1)+(wz<hc?0:2)]++; }
    f32 inv = 1.0f / t->inv_nm1;
    i32 gr = (i32)(radius * t->inv_scale * (f32)t->grid_size) + 1;
    f32 cgx = (wx * t->inv_scale + 0.5f) * t->inv_nm1;
    f32 cgz = (wz * t->inv_scale + 0.5f) * t->inv_nm1;
    i32 gx0 = (i32)floorf(cgx) - gr; if (gx0 < 0) gx0 = 0;
    i32 gz0 = (i32)floorf(cgz) - gr; if (gz0 < 0) gz0 = 0;
    i32 gx1 = (i32)ceilf(cgx) + gr; if (gx1 >= (i32)t->grid_size) gx1 = (i32)t->grid_size - 1;
    i32 gz1 = (i32)ceilf(cgz) + gr; if (gz1 >= (i32)t->grid_size) gz1 = (i32)t->grid_size - 1;
    f32 r2 = radius * radius;
    f32 inv_r2 = 1.0f / r2;
    for (i32 gz = gz0; gz <= gz1; gz++) {
        for (i32 gx = gx0; gx <= gx1; gx++) {
            f32 fwx = ((f32)gx * inv - 0.5f) * t->scale;
            f32 fwz = ((f32)gz * inv - 0.5f) * t->scale;
            f32 dx = fwx - wx, dz = fwz - wz;
            f32 d2 = dx * dx + dz * dz;
            if (d2 < r2) {
                f32 falloff = 1.0f - d2 * inv_r2;
                f32 n = sinf(fwx * 3.7f + seed) * cosf(fwz * 2.9f - seed * 0.7f) * 0.5f
                      + sinf((fwx + fwz) * 5.3f + seed * 1.3f) * 0.3f
                      + cosf(fwx * 1.8f - fwz * 4.1f + seed * 0.5f) * 0.2f;
                t->heightmap[gz * t->grid_size + gx] += strength * n * falloff;
            }
        }
    }
    terrain_rebuild_region(t, gx0 - 1, gz0 - 1, gx1 + 1, gz1 + 1);
}

void terrain_generate(Terrain *t, u32 preset) {
    if (!t->heightmap) return;
    u32 n = t->grid_size;
    f32 hs = t->height_scale;

    /* Precompute separable trig values for presets 2/3: O(n) instead of O(n²).
     * Single allocation for both LUT arrays: 2 mallocs → 1 per branch. */
    f32 *pre_sin_x = NULL, *pre_sin_z = NULL, *pre_cos_z = NULL;
    f32 *pre_trig_block = NULL;  /* owns the single allocation */
    f32 inv_nm1 = 1.0f / (f32)(n - 1);
    u32 pmod = preset % 5;
    if (pmod == 2) {
        pre_trig_block = (f32 *)malloc(2 * n * sizeof(f32));
        if (pre_trig_block) {
            pre_sin_x = pre_trig_block;
            pre_sin_z = pre_trig_block + n;
            for (u32 i = 0; i < n; i++) {
                f32 ni = (f32)i * inv_nm1;
                pre_sin_x[i] = sinf(ni * 12.0f);
                pre_sin_z[i] = sinf(ni * 12.0f);
            }
        }
    } else if (pmod == 3) {
        pre_trig_block = (f32 *)malloc(2 * n * sizeof(f32));
        if (pre_trig_block) {
            pre_sin_x = pre_trig_block;
            pre_cos_z = pre_trig_block + n;
            for (u32 i = 0; i < n; i++) {
                f32 ni = (f32)i * inv_nm1;
                pre_sin_x[i] = fabsf(sinf(ni * 5.0f));
                pre_cos_z[i] = fabsf(cosf(ni * 4.0f));
            }
        }
    }

    for (u32 z = 0; z < n; z++) {
        for (u32 x = 0; x < n; x++) {
            f32 nx = (f32)x * inv_nm1;
            f32 nz = (f32)z * inv_nm1;
            f32 h = 0.0f;
            switch (pmod) {
                case 0:
                    h = simple_noise(nx * 6.0f, nz * 6.0f) * hs * 0.5f;
                    break;
                case 1: {
                    f32 dx = nx - 0.5f, dz = nz - 0.5f;
                    f32 d2 = dx * dx + dz * dz;
                    f32 d = d2 > 1e-12f ? d2 * fast_rsqrt(d2) : 0.0f;
                    h = fmaxf(0.0f, 1.0f - d * 3.0f) * hs;
                    h += simple_noise(nx * 8.0f, nz * 8.0f) * hs * 0.15f;
                    break;
                }
                case 2:
                    if (pre_sin_x && pre_sin_z)
                        h = (pre_sin_x[x] * pre_sin_z[z] * 0.5f + 0.5f) * hs;
                    else
                        h = (sinf(nx * 12.0f) * sinf(nz * 12.0f) * 0.5f + 0.5f) * hs;
                    break;
                case 3:
                    if (pre_sin_x && pre_cos_z)
                        h = (1.0f - pre_sin_x[x] * pre_cos_z[z]) * hs * 0.8f;
                    else
                        h = (1.0f - fabsf(sinf(nx * 5.0f)) * fabsf(cosf(nz * 4.0f))) * hs * 0.8f;
                    h += simple_noise(nx * 10.0f, nz * 10.0f) * hs * 0.2f;
                    break;
                case 4: {
                    h = simple_noise(nx * 4.0f, nz * 4.0f) * hs * 0.3f;
                    f32 craters[] = {0.3f,0.7f, 0.7f,0.3f, 0.5f,0.5f, 0.2f,0.2f, 0.8f,0.8f};
                    for (i32 ci = 0; ci < 5; ci++) {
                        f32 dx = nx - craters[ci*2], dz = nz - craters[ci*2+1];
                        f32 d2 = dx*dx + dz*dz;
                        f32 r = 0.08f + (f32)ci * 0.02f;
                        f32 d = d2 > 1e-12f ? d2 * fast_rsqrt(d2) : 0.0f;
                        f32 inv_r = 1.0f / r;
                        if (d < r) {
                            h -= (1.0f - d * inv_r) * hs * 0.6f;
                        } else if (d < r * 1.5f) {
                            h += (1.0f - (d-r) * (1.0f/(r*0.5f))) * hs * 0.15f;
                        }
                    }
                    break;
                }
            }
            t->heightmap[z * n + x] = h;
        }
    }
    free(pre_trig_block);  /* Single free: pre_sin_x + pre_sin_z/cos_z in one block */
    terrain_rebuild_region(t, 0, 0, n - 1, n - 1);
}
