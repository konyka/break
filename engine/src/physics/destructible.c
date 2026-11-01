#include <physics/destructible.h>

bool destructible_create(Destructible *d, PhysicsWorld *pw, Vec3 center, Vec3 half_extent,
                         f32 mass, f32 break_impulse) {
    if (!d || !pw || !(mass > 0.0f) || !(break_impulse > 0.0f)) return false;
    for (int i = 0; i < 3; i++) {
        if (!(half_extent.e[i] > 0.0f) || !isfinite(center.e[i])) return false;
    }
    u32 id = physics_body_create(pw, center, half_extent, mass, false, 0);
    if (id == UINT32_MAX || id == 0u) {
        if (id != UINT32_MAX && id != 0u) physics_body_park(pw, id);
        return false;
    }
    d->root = id;
    d->fragment_count = 0;
    d->center = center;
    d->half_extent = half_extent;
    d->mass = mass;
    d->break_impulse = break_impulse;
    d->broken = false;
    return true;
}

void destructible_apply_impulse(Destructible *d, PhysicsWorld *pw, f32 impulse) {
    if (!d || !pw || d->broken || d->root == 0u || d->root >= pw->count) return;
    if (!(impulse >= d->break_impulse)) return;
    if (pw->count + DESTRUCTIBLE_FRAGMENTS > pw->capacity) return;
    f32 frag_mass = d->mass / (f32)DESTRUCTIBLE_FRAGMENTS;
    Vec3 half = vec3_scale(d->half_extent, 0.5f);
    u32 created[DESTRUCTIBLE_FRAGMENTS];
    u32 n = 0;
    u32 before = pw->count;
    for (int iz = 0; iz < 2; iz++) {
        for (int iy = 0; iy < 2; iy++) {
            for (int ix = 0; ix < 2; ix++) {
                Vec3 pos = vec3(d->center.e[0] + ((ix == 0) ? -half.e[0] : half.e[0]),
                                d->center.e[1] + ((iy == 0) ? -half.e[1] : half.e[1]),
                                d->center.e[2] + ((iz == 0) ? -half.e[2] : half.e[2]));
                u32 id = physics_body_create(pw, pos, half, frag_mass, false, 0);
                if (id == UINT32_MAX) {
                    for (u32 k = before; k < pw->count; k++) {
                        if (k != 0u) physics_body_park(pw, k);
                    }
                    return;
                }
                created[n++] = id;
            }
        }
    }
    physics_body_park(pw, d->root);
    for (u32 i = 0; i < n; i++) d->fragments[i] = created[i];
    d->fragment_count = n;
    d->broken = true;
}
