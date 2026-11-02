#include <ai/break_ai.h>
#include <math.h>

#define BREAK_STEER_CANDIDATE_DIRECTIONS 16u
#define BREAK_STEER_CANDIDATE_COUNT (3u + BREAK_STEER_CANDIDATE_DIRECTIONS * 2u)

static bool steer_vec_ok(Vec3 value) {
    return isfinite(value.e[0]) && isfinite(value.e[1]) && isfinite(value.e[2]);
}

static Vec3 steer_clamp(Vec3 value, f32 max_speed) {
    value.e[1] = 0.0f;
    f32 length_sq = value.e[0] * value.e[0] + value.e[2] * value.e[2];
    if (length_sq > max_speed * max_speed && length_sq > 1.0e-20f) {
        f32 scale = max_speed / sqrtf(length_sq);
        value.e[0] *= scale;
        value.e[2] *= scale;
    }
    return value;
}

static f32 steer_collision_cost(Vec3 self, f32 self_radius, Vec3 candidate,
                                const BreakSteerAgent *neighbors, u32 count,
                                f32 horizon) {
    f32 total = 0.0f;
    for (u32 i = 0; i < count; i++) {
        f32 rx = neighbors[i].position.e[0] - self.e[0];
        f32 rz = neighbors[i].position.e[2] - self.e[2];
        f32 rvx = neighbors[i].velocity.e[0] - candidate.e[0];
        f32 rvz = neighbors[i].velocity.e[2] - candidate.e[2];
        f32 rv2 = rvx * rvx + rvz * rvz;
        f32 time = 0.0f;
        if (rv2 > 1.0e-12f) {
            time = -(rx * rvx + rz * rvz) / rv2;
            if (time < 0.0f) {
                time = 0.0f;
            } else if (time > horizon) {
                time = horizon;
            }
        }
        f32 dx = rx + rvx * time;
        f32 dz = rz + rvz * time;
        f32 distance = sqrtf(dx * dx + dz * dz);
        f32 limit = self_radius + neighbors[i].radius + 0.05f;
        if (distance < limit) {
            f32 severity = (limit - distance) / limit;
            f32 urgency = (horizon - time) / horizon;
            total += 4.0f + 4.0f * urgency + 2.0f * severity;
        }
    }
    return total;
}

BreakNavError break_steer_avoid_velocity(Vec3 self, Vec3 self_velocity,
                                         f32 self_radius, f32 max_speed,
                                         Vec3 desired_velocity,
                                         const BreakSteerAgent *neighbors,
                                         u32 count, f32 horizon, Vec3 *out_velocity) {
    if (!out_velocity) {
        return BREAK_NAV_INVALID;
    }
    if (count > BREAK_STEER_MAX_NEIGHBORS) {
        return BREAK_NAV_OVERLOAD;
    }
    if (!steer_vec_ok(self) || !steer_vec_ok(self_velocity) ||
        !steer_vec_ok(desired_velocity) || !isfinite(self_radius) ||
        !isfinite(max_speed) || !isfinite(horizon) || self_radius < 0.0f ||
        max_speed <= 0.0f || horizon <= 0.0f || (count > 0 && !neighbors)) {
        return BREAK_NAV_INVALID;
    }
    for (u32 i = 0; i < count; i++) {
        if (!steer_vec_ok(neighbors[i].position) || !steer_vec_ok(neighbors[i].velocity) ||
            !isfinite(neighbors[i].radius) || neighbors[i].radius < 0.0f) {
            return BREAK_NAV_INVALID;
        }
    }
    Vec3 preferred = steer_clamp(desired_velocity, max_speed);
    Vec3 candidates[BREAK_STEER_CANDIDATE_COUNT];
    u32 candidate_count = 0;
    candidates[candidate_count++] = preferred;
    candidates[candidate_count++] = steer_clamp(self_velocity, max_speed);
    candidates[candidate_count++] = vec3(0, 0, 0);
    Vec3 basis = preferred;
    f32 basis_length_sq = basis.e[0] * basis.e[0] + basis.e[2] * basis.e[2];
    if (basis_length_sq <= 1.0e-12f) {
        basis = steer_clamp(self_velocity, max_speed);
        basis_length_sq = basis.e[0] * basis.e[0] + basis.e[2] * basis.e[2];
    }
    f32 base_angle = basis_length_sq > 1.0e-12f ? atan2f(basis.e[2], basis.e[0]) : 0.0f;
    const f32 pi = 3.14159265358979323846f;
    for (u32 level = 0; level < 2; level++) {
        f32 magnitude = level == 0 ? max_speed * 0.5f : max_speed;
        for (u32 i = 0; i < BREAK_STEER_CANDIDATE_DIRECTIONS; i++) {
            f32 angle = base_angle + (2.0f * pi * (f32)i) / BREAK_STEER_CANDIDATE_DIRECTIONS;
            candidates[candidate_count++] = vec3(cosf(angle) * magnitude, 0.0f,
                                                 sinf(angle) * magnitude);
        }
    }
    u32 best = 0;
    f32 best_cost = 0.0f;
    for (u32 i = 0; i < candidate_count; i++) {
        f32 dx = candidates[i].e[0] - preferred.e[0];
        f32 dz = candidates[i].e[2] - preferred.e[2];
        f32 cost = sqrtf(dx * dx + dz * dz) / max_speed +
                   steer_collision_cost(self, self_radius, candidates[i], neighbors, count, horizon);
        if (i == 0 || cost < best_cost - 1.0e-6f) {
            best = i;
            best_cost = cost;
        }
    }
    *out_velocity = candidates[best];
    return BREAK_NAV_OK;
}
