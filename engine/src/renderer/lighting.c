#include <renderer/lighting.h>
#include <core/log.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

static f32 cluster_depth(u32 z_slice, f32 near, f32 far) {
    f32 n = (f32)z_slice / (f32)CLUSTER_Z;
    return near * powf(far / near, n);
}

static Vec4 mat4_vec4(Mat4 m, Vec4 v) {
    Vec4 out;
    for (int i = 0; i < 4; i++) {
        out.e[i] = m.e[i][0] * v.e[0] + m.e[i][1] * v.e[1] +
                   m.e[i][2] * v.e[2] + m.e[i][3] * v.e[3];
    }
    return out;
}

void light_system_init(LightSystem *ls, RHIDevice *dev) {
    memset(ls, 0, sizeof(LightSystem));
    ls->device = dev;

    RHIBufferDesc light_desc = {
        .usage = RHI_BUFFER_USAGE_TEXEL,
        .size = (LIGHT_MAX_POINT * sizeof(PointLight) + LIGHT_MAX_DIR * sizeof(DirLight) + 4 * sizeof(Mat4)),
        .initial_data = NULL,
    };
    ls->light_data_buf = rhi_buffer_create(dev, &light_desc);

    usize grid_data_size = (CLUSTER_COUNT * 2 + CLUSTER_COUNT * LIGHT_MAX_PER_CLUSTER) * sizeof(u32);
    RHIBufferDesc grid_desc = {
        .usage = RHI_BUFFER_USAGE_TEXEL,
        .size = grid_data_size,
        .initial_data = NULL,
    };
    ls->light_grid_buf = rhi_buffer_create(dev, &grid_desc);
}

void light_system_shutdown(LightSystem *ls) {
    if (!ls->device) return;
    if (rhi_handle_valid(ls->light_grid_buf)) rhi_buffer_destroy(ls->device, ls->light_grid_buf);
    if (rhi_handle_valid(ls->light_data_buf)) rhi_buffer_destroy(ls->device, ls->light_data_buf);
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

void light_system_cull(LightSystem *ls, const f32 *view, const f32 *proj, u32 screen_w, u32 screen_h) {
    ls->screen_w = screen_w;
    ls->screen_h = screen_h;

    Mat4 vp;
    memcpy(&vp, proj, sizeof(Mat4));
    Mat4 v;
    memcpy(&v, view, sizeof(Mat4));
    vp = mat4_mul(vp, v);

    f32 near = 0.1f, far = 100.0f;
    ls->near_plane = near;
    ls->far_plane = far;

    memset(ls->grid_offsets_counts, 0, sizeof(ls->grid_offsets_counts));
    memset(ls->grid_indices, 0, sizeof(ls->grid_indices));
    ls->grid_index_total = 0;

    f32 tile_w = (f32)screen_w / (f32)CLUSTER_X;
    f32 tile_h = (f32)screen_h / (f32)CLUSTER_Y;

    for (u32 ci = 0; ci < CLUSTER_COUNT; ci++) {
        if (ls->grid_index_total >= CLUSTER_COUNT * LIGHT_MAX_PER_CLUSTER - LIGHT_MAX_POINT) break;

        u32 cx = ci % CLUSTER_X;
        u32 cy = (ci / CLUSTER_X) % CLUSTER_Y;
        u32 cz = ci / (CLUSTER_X * CLUSTER_Y);

        f32 z_near = cluster_depth(cz, near, far);
        f32 z_far = cluster_depth(cz + 1, near, far);

        f32 sx = cx * tile_w;
        f32 ex = (cx + 1) * tile_w;
        f32 sy = cy * tile_h;
        f32 ey = (cy + 1) * tile_h;

        u32 offset = ls->grid_index_total;
        u32 count = 0;

        for (u32 li = 0; li < ls->point_count; li++) {
            if (count >= LIGHT_MAX_PER_CLUSTER) break;

            PointLight *pl = &ls->point_lights[li];
            f32 px = pl->pos[0], py = pl->pos[1], pz = pl->pos[2];
            f32 r = pl->radius;

            Vec4 wp = vec4(px, py, pz, 1.0f);
            Vec4 vp_pos = mat4_vec4(v, wp);

            if (vp_pos.e[2] + r < -z_far || vp_pos.e[2] - r > -z_near) continue;

            Vec4 sp = mat4_vec4(vp, wp);
            if (sp.e[3] > 0.001f) {
                f32 inv_w = 1.0f / sp.e[3];
                f32 sx2 = (sp.e[0] * inv_w * 0.5f + 0.5f) * (f32)screen_w;
                f32 sy2 = (sp.e[1] * inv_w * 0.5f + 0.5f) * (f32)screen_h;
                f32 screen_r = r / (-vp_pos.e[2]) * (f32)screen_w * 0.5f;

                if (sx2 + screen_r < sx || sx2 - screen_r > ex ||
                    sy2 + screen_r < sy || sy2 - screen_r > ey) continue;
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

void light_system_upload(LightSystem *ls) {
    if (!rhi_handle_valid(ls->light_data_buf)) return;

    usize light_struct_size = LIGHT_MAX_POINT * sizeof(PointLight) + LIGHT_MAX_DIR * sizeof(DirLight);
    usize total_size = light_struct_size + 4 * sizeof(Mat4);
    u8 *light_data = calloc(1, total_size);
    if (light_data) {
        memcpy(light_data, ls->point_lights, ls->point_count * sizeof(PointLight));
        memcpy(light_data + LIGHT_MAX_POINT * sizeof(PointLight), ls->dir_lights, ls->dir_count * sizeof(DirLight));
        memcpy(light_data + light_struct_size, ls->cascade_vp, 4 * sizeof(Mat4));
        rhi_buffer_update(ls->device, ls->light_data_buf, light_data, total_size);
        free(light_data);
    }

    if (!rhi_handle_valid(ls->light_grid_buf)) return;

    usize grid_size = (CLUSTER_COUNT * 2 + ls->grid_index_total) * sizeof(u32);
    u32 *grid_data = calloc(1, grid_size);
    if (grid_data) {
        memcpy(grid_data, ls->grid_offsets_counts, CLUSTER_COUNT * 2 * sizeof(u32));
        memcpy(grid_data + CLUSTER_COUNT * 2, ls->grid_indices, ls->grid_index_total * sizeof(u32));
        rhi_buffer_update(ls->device, ls->light_grid_buf, grid_data, grid_size);
        free(grid_data);
    }
}
