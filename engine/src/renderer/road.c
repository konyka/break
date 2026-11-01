#include <renderer/road.h>
#include <math.h>

static bool road_height(const f32 *heights, u32 width, u32 depth, f32 cell, f32 height_scale,
                        f32 x, f32 z, f32 *out_y) {
    if (x < 0.0f || z < 0.0f) return false;
    f32 fx = x / cell;
    f32 fz = z / cell;
    if (fx >= (f32)width || fz >= (f32)depth) return false;
    *out_y = heights[(u32)fz * width + (u32)fx] * height_scale;
    return true;
}

u32 road_build_ribbon(const Vec3 *points, u32 count, f32 half_width,
                      const f32 *heights, u32 width, u32 depth,
                      f32 cell, f32 height_scale,
                      Vec3 *out, u32 cap_pairs, u32 *dropped) {
    if (dropped) *dropped = 0;
    if (!points || !heights || count < 2u || !(half_width > 0.0f) || !(cell > 0.0f) ||
        width == 0 || depth == 0 || !isfinite(height_scale)) {
        return 0;
    }
    if (cap_pairs > 0 && !out) return 0;
    u32 written = 0;
    u32 drop = 0;
    for (u32 i = 0; i < count; i++) {
        Vec3 dir;
        if (i + 1u < count) dir = vec3_sub(points[i + 1u], points[i]);
        else dir = vec3_sub(points[i], points[i - 1u]);
        dir.e[1] = 0.0f;
        f32 len = vec3_len(dir);
        if (len <= 1e-5f) {
            drop++;
            continue;
        }
        dir = vec3_scale(dir, 1.0f / len);
        Vec3 side = vec3(-dir.e[2], 0.0f, dir.e[0]);
        f32 y = 0.0f;
        if (!road_height(heights, width, depth, cell, height_scale, points[i].e[0], points[i].e[2], &y)) {
            drop++;
            continue;
        }
        if (written >= cap_pairs) {
            drop++;
            continue;
        }
        out[written * 2u] = vec3(points[i].e[0] + side.e[0] * half_width, y,
                                 points[i].e[2] + side.e[2] * half_width);
        out[written * 2u + 1u] = vec3(points[i].e[0] - side.e[0] * half_width, y,
                                      points[i].e[2] - side.e[2] * half_width);
        written++;
    }
    if (dropped) *dropped = drop;
    return written;
}
