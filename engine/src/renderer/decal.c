#include <renderer/decal.h>
#include <math.h>

static f32 sample_h(const f32 *heights, u32 width, u32 depth, i32 x, i32 z) {
    if (x < 0) x = 0;
    if (z < 0) z = 0;
    if ((u32)x >= width) x = (i32)width - 1;
    if ((u32)z >= depth) z = (i32)depth - 1;
    return heights[(u32)z * width + (u32)x];
}

u32 decal_place_on_heightfield(const Decal *in, u32 count,
                               Decal *out, u32 cap,
                               const f32 *heights, u32 width, u32 depth,
                               f32 cell, f32 height_scale, u32 *dropped) {
    if (dropped) *dropped = 0;
    if (!in || !heights || width == 0 || depth == 0 || !(cell > 0.0f) || !isfinite(cell) ||
        !isfinite(height_scale)) {
        return 0;
    }
    if (cap > 0 && !out) return 0;
    u32 written = 0;
    u32 drop = 0;
    for (u32 i = 0; i < count; i++) {
        if (!isfinite(in[i].position.e[0]) || !isfinite(in[i].position.e[2]) || !(in[i].size > 0.0f)) {
            drop++;
            continue;
        }
        f32 fx = in[i].position.e[0] / cell;
        f32 fz = in[i].position.e[2] / cell;
        if (fx < 0.0f || fz < 0.0f || fx >= (f32)width || fz >= (f32)depth) {
            drop++;
            continue;
        }
        if (written >= cap) {
            drop++;
            continue;
        }
        u32 x = (u32)fx;
        u32 z = (u32)fz;
        f32 h = sample_h(heights, width, depth, (i32)x, (i32)z) * height_scale;
        f32 hl = sample_h(heights, width, depth, (i32)x - 1, (i32)z) * height_scale;
        f32 hr = sample_h(heights, width, depth, (i32)x + 1, (i32)z) * height_scale;
        f32 hd = sample_h(heights, width, depth, (i32)x, (i32)z - 1) * height_scale;
        f32 hu = sample_h(heights, width, depth, (i32)x, (i32)z + 1) * height_scale;
        Vec3 normal = vec3(hl - hr, 2.0f * cell, hd - hu);
        f32 nlen = vec3_len(normal);
        if (nlen > 1e-6f) normal = vec3_scale(normal, 1.0f / nlen);
        else normal = vec3(0, 1, 0);
        out[written] = in[i];
        out[written].position.e[1] = h;
        out[written].normal = normal;
        written++;
    }
    if (dropped) *dropped = drop;
    return written;
}
