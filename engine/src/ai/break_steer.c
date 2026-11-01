#include <ai/break_ai.h>
#include <math.h>

Vec3 break_steer_avoid(Vec3 self, f32 self_radius, Vec3 wish,
                       const BreakSteerNeighbor *neighbors, u32 count) {
    if (!neighbors || count == 0) {
        return wish;
    }
    u32 n = count;
    if (n > BREAK_STEER_MAX_NEIGHBORS) {
        n = BREAK_STEER_MAX_NEIGHBORS;
    }
    f32 wish_len = sqrtf(wish.e[0] * wish.e[0] + wish.e[1] * wish.e[1] + wish.e[2] * wish.e[2]);
    for (u32 i = 0; i < n; i++) {
        if (!(neighbors[i].radius > 0.0f)) {
            continue;
        }
        f32 dx = neighbors[i].position.e[0] - self.e[0];
        f32 dy = neighbors[i].position.e[1] - self.e[1];
        f32 dz = neighbors[i].position.e[2] - self.e[2];
        f32 dist = sqrtf(dx * dx + dy * dy + dz * dz);
        f32 limit = self_radius + neighbors[i].radius;
        if (!(dist < limit) || dist <= 1.0e-6f) {
            continue;
        }
        f32 side_x = -wish.e[2];
        f32 side_z = wish.e[0];
        f32 side_len = sqrtf(side_x * side_x + side_z * side_z);
        if (side_len <= 1.0e-6f) {
            side_x = 1.0f;
            side_z = 0.0f;
            side_len = 1.0f;
        }
        if (side_x * dx + side_z * dz > 0.0f) {
            side_x = -side_x;
            side_z = -side_z;
        }
        f32 scale = wish_len > 0.0f ? wish_len / side_len : 1.0f / side_len;
        return vec3(side_x * scale, 0.0f, side_z * scale);
    }
    return wish;
}
