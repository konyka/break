#include <ai/break_ai.h>
#include <math.h>
#include <string.h>

void break_nav_follow_reset(BreakNavFollower *follower, const BreakNavPath *path, f32 arrive_radius) {
    if (!follower) {
        return;
    }
    memset(follower, 0, sizeof(*follower));
    if (path) {
        follower->path = *path;
    }
    follower->arrive_radius = arrive_radius > 0.0f ? arrive_radius : 0.0f;
}

bool break_nav_follow_arrived(const BreakNavFollower *follower) {
    return follower && follower->cursor >= follower->path.count;
}

Vec3 break_nav_follow_wish(BreakNavFollower *follower, Vec3 position, f32 speed, f32 dt) {
    Vec3 zero = vec3(0, 0, 0);
    if (!follower || !isfinite(speed) || !isfinite(dt) || dt < 0.0f || speed <= 0.0f) {
        return zero;
    }
    f32 radius = follower->arrive_radius;
    while (follower->cursor < follower->path.count) {
        Vec3 point = follower->path.points[follower->cursor];
        f32 dx = point.e[0] - position.e[0];
        f32 dy = point.e[1] - position.e[1];
        f32 dz = point.e[2] - position.e[2];
        f32 dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (dist > radius) {
            f32 step = speed * dt;
            if (step > dist) {
                step = dist;
            }
            if (dist <= 1.0e-8f) {
                return zero;
            }
            f32 scale = step / dist;
            return vec3(dx * scale, dy * scale, dz * scale);
        }
        follower->cursor++;
    }
    return zero;
}
