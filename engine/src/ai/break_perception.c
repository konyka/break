#include <ai/break_ai.h>
#include <math.h>

BreakNavError break_sight_query(const BreakSight *sight,
                                const BreakSightTarget *targets, u32 target_count,
                                BreakSightRayFn ray_clear, void *user,
                                Entity *out_visible, u32 cap, u32 *out_count) {
    if (!sight || !out_count || (target_count > 0 && !targets) || (cap > 0 && !out_visible) || !ray_clear) {
        return BREAK_NAV_INVALID;
    }
    f32 flen = sqrtf(sight->forward.e[0] * sight->forward.e[0] +
                     sight->forward.e[1] * sight->forward.e[1] +
                     sight->forward.e[2] * sight->forward.e[2]);
    if (!isfinite(flen) || flen < 0.99f || flen > 1.01f || !(sight->distance >= 0.0f) ||
        !isfinite(sight->half_angle_rad)) {
        return BREAK_NAV_INVALID;
    }
    if (target_count > BREAK_SIGHT_MAX_TARGETS) {
        return BREAK_NAV_OVERLOAD;
    }
    f32 min_dot = cosf(sight->half_angle_rad);
    u32 written = 0;
    u32 visible = 0;
    for (u32 i = 0; i < target_count; i++) {
        Vec3 to = vec3(targets[i].point.e[0] - sight->eye.e[0],
                       targets[i].point.e[1] - sight->eye.e[1],
                       targets[i].point.e[2] - sight->eye.e[2]);
        f32 dist = sqrtf(to.e[0] * to.e[0] + to.e[1] * to.e[1] + to.e[2] * to.e[2]);
        if (dist > sight->distance || dist <= 1.0e-8f) {
            continue;
        }
        f32 dot = (to.e[0] * sight->forward.e[0] + to.e[1] * sight->forward.e[1] +
                   to.e[2] * sight->forward.e[2]) / dist;
        if (dot < min_dot) {
            continue;
        }
        if (!ray_clear(user, sight->eye, targets[i].point)) {
            continue;
        }
        visible++;
        if (written < cap) {
            out_visible[written++] = targets[i].entity;
        }
    }
    if (visible > cap) {
        *out_count = written;
        return BREAK_NAV_OVERLOAD;
    }
    *out_count = written;
    return BREAK_NAV_OK;
}
