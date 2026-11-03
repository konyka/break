#include <ai/break_nav_internal.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

static bool field_ok(const BreakNavHeightfield *field) {
    if (!field || !field->heights) {
        return false;
    }
    if (field->width == 0 || field->depth == 0 || field->width > 1024u || field->depth > 1024u) {
        return false;
    }
    if (field->width > UINT32_MAX / field->depth) {
        return false;
    }
    if (!(field->cell > 0.0f) || !isfinite(field->cell) || !isfinite(field->origin_x) ||
        !isfinite(field->origin_z) || !isfinite(field->height_scale)) {
        return false;
    }
    return true;
}

static f32 cell_height(const BreakNavHeightfield *field, u32 x, u32 z) {
    return field->heights[(size_t)z * field->width + x] * field->height_scale;
}

static bool edge_walkable(f32 h0, f32 h1, f32 max_rise) {
    f32 rise = h0 - h1;
    if (rise < 0.0f) {
        rise = -rise;
    }
    return rise <= max_rise;
}

void break_nav_mesh_destroy(BreakNavMesh *mesh) {
    if (!mesh) {
        return;
    }
    break_nav_workspace_pool_destroy(mesh->workspace_pool);
    free(mesh->cell_poly);
    free(mesh->polys);
    free(mesh);
}

BreakNavMesh *break_nav_bake_heightfield(const BreakNavHeightfield *field,
                                         f32 walkable_slope_deg,
                                         f32 agent_radius) {
    if (!field_ok(field) || !isfinite(walkable_slope_deg) || !isfinite(agent_radius) ||
        walkable_slope_deg < 0.0f || walkable_slope_deg >= 89.0f || agent_radius < 0.0f) {
        return NULL;
    }
    u32 count = field->width * field->depth;
    for (u32 i = 0; i < count; i++) {
        if (!isfinite(field->heights[i])) {
            return NULL;
        }
    }
    f32 max_rise = tanf(walkable_slope_deg * 0.01745329251f) * field->cell + 1.0e-4f;

    u8 *open = (u8 *)malloc(count);
    u32 *stack = (u32 *)malloc(sizeof(u32) * count);
    u32 *cell_poly = (u32 *)malloc(sizeof(u32) * count);
    if (!open || !stack || !cell_poly) {
        free(open);
        free(stack);
        free(cell_poly);
        return NULL;
    }
    memset(open, 1, count);

    u32 shrink = 0;
    if (agent_radius > 0.0f) {
        f32 steps = ceilf(agent_radius / field->cell);
        if (steps > 1024.0f) {
            steps = 1024.0f;
        }
        shrink = (u32)steps;
    }
    for (u32 n = 0; n < shrink; n++) {
        u8 *next = (u8 *)malloc(count);
        if (!next) {
            free(open);
            free(stack);
            free(cell_poly);
            return NULL;
        }
        memcpy(next, open, count);
        for (u32 z = 0; z < field->depth; z++) {
            for (u32 x = 0; x < field->width; x++) {
                u32 i = z * field->width + x;
                if (!open[i]) {
                    continue;
                }
                if (x == 0 || z == 0 || x + 1u == field->width || z + 1u == field->depth) {
                    next[i] = 0;
                    continue;
                }
                if (!open[i - 1] || !open[i + 1] || !open[i - field->width] || !open[i + field->width]) {
                    next[i] = 0;
                }
            }
        }
        free(open);
        open = next;
    }

    for (u32 i = 0; i < count; i++) {
        cell_poly[i] = UINT32_MAX;
    }
    u32 poly_count = 0;
    for (u32 i = 0; i < count; i++) {
        if (open[i]) {
            poly_count++;
        }
    }
    BreakNavPoly *polys = NULL;
    if (poly_count > 0) {
        polys = (BreakNavPoly *)calloc(poly_count, sizeof(BreakNavPoly));
        if (!polys) {
            free(open);
            free(stack);
            free(cell_poly);
            return NULL;
        }
    }
    u32 p = 0;
    for (u32 z = 0; z < field->depth; z++) {
        for (u32 x = 0; x < field->width; x++) {
            u32 i = z * field->width + x;
            if (!open[i]) {
                continue;
            }
            cell_poly[i] = p;
            polys[p].cell_x = x;
            polys[p].cell_z = z;
            polys[p].center = vec3(field->origin_x + ((f32)x + 0.5f) * field->cell,
                                   cell_height(field, x, z),
                                   field->origin_z + ((f32)z + 0.5f) * field->cell);
            p++;
        }
    }

    static const i32 k_dx[4] = {1, -1, 0, 0};
    static const i32 k_dz[4] = {0, 0, 1, -1};
    for (u32 i = 0; i < poly_count; i++) {
        u32 x = polys[i].cell_x;
        u32 z = polys[i].cell_z;
        f32 h = cell_height(field, x, z);
        for (u32 d = 0; d < 4; d++) {
            i32 nx = (i32)x + k_dx[d];
            i32 nz = (i32)z + k_dz[d];
            if (nx < 0 || nz < 0 || (u32)nx >= field->width || (u32)nz >= field->depth) {
                continue;
            }
            u32 ni = (u32)nz * field->width + (u32)nx;
            if (cell_poly[ni] == UINT32_MAX) {
                continue;
            }
            if (!edge_walkable(h, cell_height(field, (u32)nx, (u32)nz), max_rise)) {
                continue;
            }
            polys[i].neighbors[polys[i].neighbor_count++] = cell_poly[ni];
        }
    }

    u32 component = 0;
    for (u32 i = 0; i < poly_count; i++) {
        if (polys[i].component != 0) {
            continue;
        }
        component++;
        u32 top = 0;
        stack[top++] = i;
        polys[i].component = component;
        while (top > 0) {
            u32 cur = stack[--top];
            for (u32 n = 0; n < polys[cur].neighbor_count; n++) {
                u32 nb = polys[cur].neighbors[n];
                if (polys[nb].component == 0) {
                    polys[nb].component = component;
                    stack[top++] = nb;
                }
            }
        }
    }
    free(open);
    free(stack);

    BreakNavMesh *mesh = (BreakNavMesh *)calloc(1, sizeof(BreakNavMesh));
    if (!mesh) {
        free(polys);
        free(cell_poly);
        return NULL;
    }
    mesh->width = field->width;
    mesh->depth = field->depth;
    mesh->origin_x = field->origin_x;
    mesh->origin_z = field->origin_z;
    mesh->cell = field->cell;
    mesh->cell_poly = cell_poly;
    mesh->polys = polys;
    mesh->poly_count = poly_count;
    mesh->workspace_pool = break_nav_workspace_pool_create(poly_count);
    if (!mesh->workspace_pool) {
        break_nav_mesh_destroy(mesh);
        return NULL;
    }
    return mesh;
}

bool break_nav_locate(const BreakNavMesh *mesh, Vec3 p, u32 *out_poly) {
    if (!mesh || !out_poly || !(mesh->cell > 0.0f)) {
        return false;
    }
    f32 fx = (p.e[0] - mesh->origin_x) / mesh->cell;
    f32 fz = (p.e[2] - mesh->origin_z) / mesh->cell;
    if (!isfinite(fx) || !isfinite(fz) || fx < 0.0f || fz < 0.0f) {
        return false;
    }
    u32 x = (u32)fx;
    u32 z = (u32)fz;
    if (x >= mesh->width || z >= mesh->depth) {
        return false;
    }
    u32 poly = mesh->cell_poly[z * mesh->width + x];
    if (poly == UINT32_MAX) {
        return false;
    }
    *out_poly = poly;
    return true;
}

bool break_nav_same_component(const BreakNavMesh *mesh, Vec3 a, Vec3 b) {
    u32 pa = 0;
    u32 pb = 0;
    if (!break_nav_locate(mesh, a, &pa) || !break_nav_locate(mesh, b, &pb)) {
        return false;
    }
    return mesh->polys[pa].component != 0 && mesh->polys[pa].component == mesh->polys[pb].component;
}
