#include <renderer/lighting.h>
#include <core/log.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
    #include <immintrin.h>
    #define LIGHT_SSE2 1
#else
    #define LIGHT_SSE2 0
#endif

static f32 cluster_depth(u32 z_slice, f32 near, f32 far) {
    f32 n = (f32)z_slice / (f32)CLUSTER_Z;
    return near * powf(far / near, n);
}

/* R74-3: const Mat4* parameter — eliminates 64B per-call copy in the per-light
 * transform loop (up to 512 calls/frame for 256 point lights). */
static Vec4 mat4_vec4(const Mat4 *m, Vec4 v) {
    Vec4 out;
#if LIGHT_SSE2
    /* SSE2: each row of column-major Mat4 dot v.
     * Row i = m->e[0][i], m->e[1][i], m->e[2][i], m->e[3][i] */
    __m128 v0 = _mm_set1_ps(v.e[0]);
    __m128 v1 = _mm_set1_ps(v.e[1]);
    __m128 v2 = _mm_set1_ps(v.e[2]);
    __m128 v3 = _mm_set1_ps(v.e[3]);
    /* col0 * v0 + col1 * v1 + col2 * v2 + col3 * v3 gives one result per row */
    __m128 r = _mm_mul_ps(_mm_loadu_ps(m->e[0]), v0);
    r = _mm_add_ps(r, _mm_mul_ps(_mm_loadu_ps(m->e[1]), v1));
    r = _mm_add_ps(r, _mm_mul_ps(_mm_loadu_ps(m->e[2]), v2));
    r = _mm_add_ps(r, _mm_mul_ps(_mm_loadu_ps(m->e[3]), v3));
    _mm_storeu_ps(out.e, r);
#else
    /* Scalar fallback: must match SSE2 path (column-based M*v).
     * out[i] = sum_k m->e[k][i] * v[k], NOT row-based dot product. */
    for (int i = 0; i < 4; i++) {
        out.e[i] = m->e[0][i] * v.e[0] + m->e[1][i] * v.e[1] +
                   m->e[2][i] * v.e[2] + m->e[3][i] * v.e[3];
    }
#endif
    return out;
}

void light_system_init(LightSystem *ls, RHIDevice *dev) {
    memset(ls, 0, sizeof(LightSystem));
    ls->device = dev;

    /* Both buffers are sampled as texel buffers by the PBR shader and also
     * accessed as storage buffers by the GPU cluster-binning compute pass
     * (light_data read, grid written), hence TEXEL | STORAGE. */
    RHIBufferDesc light_desc = {
        .usage = RHI_BUFFER_USAGE_TEXEL | RHI_BUFFER_USAGE_STORAGE,
        .size = (LIGHT_MAX_POINT * sizeof(PointLight) + LIGHT_MAX_DIR * sizeof(DirLight) + 4 * sizeof(Mat4)),
        .initial_data = NULL,
    };
    ls->light_data_buf = rhi_buffer_create(dev, &light_desc);

    usize grid_data_size = (CLUSTER_COUNT * 2 + CLUSTER_COUNT * LIGHT_MAX_PER_CLUSTER) * sizeof(u32);
    RHIBufferDesc grid_desc = {
        .usage = RHI_BUFFER_USAGE_TEXEL | RHI_BUFFER_USAGE_STORAGE,
        .size = grid_data_size,
        .initial_data = NULL,
    };
    ls->light_grid_buf = rhi_buffer_create(dev, &grid_desc);

    ls->cluster_cull_pipeline = RHI_HANDLE_NULL;
    ls->gpu_cull = false;

    /* Pre-allocate persistent staging buffers (single alloc: _upload_buf + _grid_buf). */
    ls->_upload_buf_size = light_desc.size;
    ls->_grid_buf_size = grid_data_size / sizeof(u32);
    usize ub_bytes = ls->_upload_buf_size;
    usize gb_off   = (ub_bytes + 3u) & ~(usize)3u;
    usize gb_bytes = ls->_grid_buf_size * sizeof(u32);
    u8 *staging_block = (u8 *)calloc(1, gb_off + gb_bytes);
    ls->_upload_buf = staging_block;
    ls->_grid_buf   = (u32 *)(staging_block + gb_off);

    /* Pre-compute cluster depth LUT (near=0.1, far=100.0 are hardcoded constants). */
    ls->_z_depths_dirty = true;
}

void light_system_shutdown(LightSystem *ls) {
    if (!ls->device) return;
    if (rhi_handle_valid(ls->cluster_cull_pipeline)) rhi_pipeline_destroy(ls->device, ls->cluster_cull_pipeline);
    if (rhi_handle_valid(ls->light_grid_buf)) rhi_buffer_destroy(ls->device, ls->light_grid_buf);
    if (rhi_handle_valid(ls->light_data_buf)) rhi_buffer_destroy(ls->device, ls->light_data_buf);
    free(ls->_upload_buf); /* single free: _upload_buf + _grid_buf */
    ls->_upload_buf = NULL;
    ls->_grid_buf = NULL;
}

void light_system_add_point(LightSystem *ls, f32 x, f32 y, f32 z, f32 r, f32 cr, f32 cg, f32 cb) {
    if (ls->point_count >= LIGHT_MAX_POINT) return;
    PointLight *l = &ls->point_lights[ls->point_count++];
    l->pos[0] = x; l->pos[1] = y; l->pos[2] = z;
    l->radius = r;
    l->color[0] = cr; l->color[1] = cg; l->color[2] = cb;
}

void light_system_add_dir(LightSystem *ls, f32 dx, f32 dy, f32 dz, f32 cr, f32 cg, f32 cb) {
    if (ls->dir_count >= LIGHT_MAX_DIR) return;
    DirLight *l = &ls->dir_lights[ls->dir_count++];
    l->dir[0] = dx; l->dir[1] = dy; l->dir[2] = dz;
    l->color[0] = cr; l->color[1] = cg; l->color[2] = cb;
}

void light_system_clear(LightSystem *ls) {
    ls->point_count = 0;
    ls->dir_count = 0;
}

void light_system_cull(LightSystem *ls, const Mat4 *view, const Mat4 *proj, u32 screen_w, u32 screen_h) {
    ls->screen_w = screen_w;
    ls->screen_h = screen_h;

    /* R74-3: Pass view/proj pointers directly to mat4_vec4 — no local copies. */

    f32 near = 0.1f, far = 100.0f;
    ls->near_plane = near;
    ls->far_plane = far;

    memset(ls->grid_offsets_counts, 0, sizeof(ls->grid_offsets_counts));
    ls->grid_index_total = 0;

    /* Use cached z_depths LUT; recompute only on first call or after clear. */
    if (ls->_z_depths_dirty) {
        for (u32 zi = 0; zi <= CLUSTER_Z; zi++)
            ls->_z_depths[zi] = cluster_depth(zi, near, far);
        ls->_z_depths_dirty = false;
    }

    /* Pre-transform all lights once (O(n)) before the O(clusters*n) loop.
     * Static buffers: light_system_cull is called at most once per frame on
     * the main thread; no concurrent access. */
    u32 pc = ls->point_count;
    static Vec4 view_pos[LIGHT_MAX_POINT];
    static Vec4 clip_pos[LIGHT_MAX_POINT];
    static f32 screen_x[LIGHT_MAX_POINT];
    static f32 screen_y[LIGHT_MAX_POINT];
    static f32 screen_r[LIGHT_MAX_POINT];
    static f32 screen_xmin[LIGHT_MAX_POINT];
    static f32 screen_xmax[LIGHT_MAX_POINT];
    static f32 screen_ymin[LIGHT_MAX_POINT];
    static f32 screen_ymax[LIGHT_MAX_POINT];
    static bool screen_ok[LIGHT_MAX_POINT];
    for (u32 li = 0; li < pc; li++) {
        PointLight *pl = &ls->point_lights[li];
        Vec4 wp = vec4(pl->pos[0], pl->pos[1], pl->pos[2], 1.0f);
        view_pos[li] = mat4_vec4(view, wp);
        clip_pos[li] = mat4_vec4(proj, view_pos[li]);  /* proj * view_pos */

        /* Pre-compute screen-space projection (depends only on light, not cluster) */
        Vec4 sp = clip_pos[li];
        if (sp.e[3] > 0.001f) {
            f32 inv_w = 1.0f / sp.e[3];
            screen_x[li] = (sp.e[0] * inv_w * 0.5f + 0.5f) * (f32)screen_w;
            screen_y[li] = (sp.e[1] * inv_w * 0.5f + 0.5f) * (f32)screen_h;
            f32 inv_vz = 1.0f / (-view_pos[li].e[2]);
            screen_r[li] = pl->radius * inv_vz * (f32)screen_w * 0.5f;
            screen_xmin[li] = screen_x[li] - screen_r[li];
            screen_xmax[li] = screen_x[li] + screen_r[li];
            screen_ymin[li] = screen_y[li] - screen_r[li];
            screen_ymax[li] = screen_y[li] + screen_r[li];
            screen_ok[li] = true;
        } else {
            screen_ok[li] = false;
        }
    }

    f32 tile_w = (f32)screen_w / (f32)CLUSTER_X;
    f32 tile_h = (f32)screen_h / (f32)CLUSTER_Y;

    /* Use cached z_depths LUT (computed once in init, never changes). */
    const f32 *z_depths = ls->_z_depths;

    u32 ci = 0;
    for (u32 cz = 0; cz < CLUSTER_Z; cz++) {
        f32 z_near = z_depths[cz];
        f32 z_far = z_depths[cz + 1];
        for (u32 cy = 0; cy < CLUSTER_Y; cy++) {
            f32 sy = cy * tile_h;
            f32 ey = (cy + 1) * tile_h;
            for (u32 cx = 0; cx < CLUSTER_X; cx++, ci++) {
                if (ls->grid_index_total >= CLUSTER_COUNT * LIGHT_MAX_PER_CLUSTER - LIGHT_MAX_POINT) goto done;

                f32 sx = cx * tile_w;
                f32 ex = (cx + 1) * tile_w;

                u32 offset = ls->grid_index_total;
                u32 count = 0;

                for (u32 li = 0; li < pc; li++) {
                    if (count >= LIGHT_MAX_PER_CLUSTER) break;

                    f32 r = ls->point_lights[li].radius;
                    Vec4 vp_pos = view_pos[li];

                    if (vp_pos.e[2] + r < -z_far || vp_pos.e[2] - r > -z_near) continue;

                    if (screen_ok[li]) {
                        if (screen_xmax[li] < sx || screen_xmin[li] > ex ||
                            screen_ymax[li] < sy || screen_ymin[li] > ey) continue;
                    }

                    if (ls->grid_index_total < CLUSTER_COUNT * LIGHT_MAX_PER_CLUSTER) {
                        ls->grid_indices[ls->grid_index_total++] = li;
                        count++;
                    }
                }

                ls->grid_offsets_counts[ci * 2 + 0] = offset;
                ls->grid_offsets_counts[ci * 2 + 1] = count;
            }
        }
    }
done:;
}

/* Upload light data only (shared helper). */
static void light_system_upload_lights_only(LightSystem *ls) {
    if (!rhi_handle_valid(ls->light_data_buf)) return;

    usize light_struct_size = LIGHT_MAX_POINT * sizeof(PointLight) + LIGHT_MAX_DIR * sizeof(DirLight);
    usize total_size = light_struct_size + 4 * sizeof(Mat4);

    if (ls->_upload_buf && total_size <= ls->_upload_buf_size) {
        /* No memset needed: memcpy overwrites every live region; stale tail is never read. */
        memcpy(ls->_upload_buf, ls->point_lights, ls->point_count * sizeof(PointLight));
        memcpy(ls->_upload_buf + LIGHT_MAX_POINT * sizeof(PointLight), ls->dir_lights, ls->dir_count * sizeof(DirLight));
        /* Use external cascade VP source (zero-copy); fall back to identity when NULL. */
        const Mat4 *csrc = ls->cascade_vp_src;
        if (csrc) {
            memcpy(ls->_upload_buf + light_struct_size, csrc, 4 * sizeof(Mat4));
        } else {
            static const Mat4 id4[4] = {
                { .e = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} },
                { .e = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} },
                { .e = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} },
                { .e = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} },
            };
            memcpy(ls->_upload_buf + light_struct_size, id4, 4 * sizeof(Mat4));
        }
        rhi_buffer_update(ls->device, ls->light_data_buf, ls->_upload_buf, total_size);
    }
}

void light_system_upload(LightSystem *ls) {
    light_system_upload_lights_only(ls);

    if (!rhi_handle_valid(ls->light_grid_buf)) return;

    usize grid_count = CLUSTER_COUNT * 2 + ls->grid_index_total;
    if (ls->_grid_buf && grid_count <= ls->_grid_buf_size) {
        /* No memset needed: memcpy overwrites the exact regions uploaded. */
        memcpy(ls->_grid_buf, ls->grid_offsets_counts, CLUSTER_COUNT * 2 * sizeof(u32));
        memcpy(ls->_grid_buf + CLUSTER_COUNT * 2, ls->grid_indices, ls->grid_index_total * sizeof(u32));
        rhi_buffer_update(ls->device, ls->light_grid_buf, ls->_grid_buf, grid_count * sizeof(u32));
    }
}

void light_system_upload_lights(LightSystem *ls) {
    light_system_upload_lights_only(ls);
}

static char *ls_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    rewind(f);
    char *buf = (char *)malloc((usize)sz + 1u);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

bool light_system_init_gpu_cull(LightSystem *ls) {
    if (!ls || !ls->device) return false;
    if (rhi_handle_valid(ls->cluster_cull_pipeline)) { ls->gpu_cull = true; return true; }

    usize len = 0;
    char *src = ls_read_file("shaders/cluster_cull.comp", &len);
    if (!src) { LOG_WARN("Lighting: cluster_cull.comp not found; using CPU binning"); return false; }
    RHIShader cs = rhi_shader_create_compute(ls->device, src, len);
    free(src);
    if (!rhi_handle_valid(cs)) { LOG_WARN("Lighting: cluster_cull.comp compile failed; using CPU binning"); return false; }

    RHIPipelineDesc d = {0};
    d.frag = cs;
    d.is_compute = true;
    d.uses_storage = true;
    ls->cluster_cull_pipeline = rhi_pipeline_create(ls->device, &d);
    rhi_shader_destroy(ls->device, cs);
    if (!rhi_handle_valid(ls->cluster_cull_pipeline)) {
        LOG_WARN("Lighting: cluster_cull pipeline create failed; using CPU binning");
        return false;
    }

    ls->cc_loc_vp      = rhi_pipeline_get_uniform_location(ls->device, ls->cluster_cull_pipeline, "u_cc_vp");
    ls->cc_loc_params0 = rhi_pipeline_get_uniform_location(ls->device, ls->cluster_cull_pipeline, "u_cc_params0");
    ls->cc_loc_params1 = rhi_pipeline_get_uniform_location(ls->device, ls->cluster_cull_pipeline, "u_cc_params1");
    ls->gpu_cull = true;
    LOG_INFO("Lighting: GPU cluster binning enabled");
    return true;
}

void light_system_cull_gpu(LightSystem *ls, RHICmdBuffer *cmd,
                           const f32 *vp, u32 screen_w, u32 screen_h) {
    if (!ls || !cmd || !rhi_handle_valid(ls->cluster_cull_pipeline)) return;

    ls->screen_w = screen_w;
    ls->screen_h = screen_h;
    ls->near_plane = 0.1f;
    ls->far_plane = 100.0f;

    rhi_cmd_bind_pipeline(cmd, ls->cluster_cull_pipeline);
    rhi_cmd_bind_storage_buffer(cmd, ls->light_data_buf, 0);
    rhi_cmd_bind_storage_buffer(cmd, ls->light_grid_buf, 1);
    if (ls->cc_loc_vp >= 0)      rhi_cmd_set_uniform_mat4(cmd, ls->cc_loc_vp, vp);
    if (ls->cc_loc_params0 >= 0) rhi_cmd_set_uniform_vec4(cmd, ls->cc_loc_params0,
                                     (f32)ls->point_count, (f32)screen_w, (f32)screen_h, ls->near_plane);
    if (ls->cc_loc_params1 >= 0) rhi_cmd_set_uniform_vec4(cmd, ls->cc_loc_params1,
                                     ls->far_plane, 0.0f, 0.0f, 0.0f);

    u32 groups = (CLUSTER_COUNT + 63u) / 64u;
    rhi_cmd_dispatch(cmd, groups, 1u, 1u);
    rhi_cmd_memory_barrier(cmd);
}
