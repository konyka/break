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
    d->generation = 0;
    return true;
}

static bool split_box(PhysicsWorld *pw, Vec3 center, Vec3 half, f32 mass, u32 *out_ids) {
    if (pw->count + DESTRUCTIBLE_FRAGMENTS > pw->capacity) return false;
    u32 before = pw->count;
    Vec3 child_half = vec3_scale(half, 0.5f);
    f32 child_mass = mass / (f32)DESTRUCTIBLE_FRAGMENTS;
    for (u32 i = 0; i < DESTRUCTIBLE_FRAGMENTS; i++) {
        int ix = i & 1;
        int iy = (i >> 1) & 1;
        int iz = (i >> 2) & 1;
        Vec3 pos = vec3(center.e[0] + ((ix == 0) ? -child_half.e[0] : child_half.e[0]),
                        center.e[1] + ((iy == 0) ? -child_half.e[1] : child_half.e[1]),
                        center.e[2] + ((iz == 0) ? -child_half.e[2] : child_half.e[2]));
        u32 id = physics_body_create(pw, pos, child_half, child_mass, false, 0);
        if (id == UINT32_MAX) {
            for (u32 k = before; k < pw->count; k++) {
                if (k != 0u) physics_body_park(pw, k);
            }
            return false;
        }
        out_ids[i] = id;
    }
    return true;
}

void destructible_apply_impulse(Destructible *d, PhysicsWorld *pw, f32 impulse) {
    if (!d || !pw || d->root == 0u || d->root >= pw->count) return;
    if (!(impulse >= d->break_impulse)) return;
    if (!d->broken) {
        u32 created[DESTRUCTIBLE_FRAGMENTS];
        if (!split_box(pw, d->center, d->half_extent, d->mass, created)) return;
        physics_body_park(pw, d->root);
        for (u32 i = 0; i < DESTRUCTIBLE_FRAGMENTS; i++) d->fragments[i] = created[i];
        d->fragment_count = DESTRUCTIBLE_FRAGMENTS;
        d->broken = true;
        d->generation = 1;
        return;
    }
    if (d->generation != 1u || d->fragment_count != DESTRUCTIBLE_FRAGMENTS) return;
    if (pw->count + DESTRUCTIBLE_MAX_PIECES > pw->capacity) return;
    u32 parents[DESTRUCTIBLE_FRAGMENTS];
    for (u32 i = 0; i < DESTRUCTIBLE_FRAGMENTS; i++) parents[i] = d->fragments[i];
    u32 next[DESTRUCTIBLE_MAX_PIECES];
    u32 before = pw->count;
    for (u32 p = 0; p < DESTRUCTIBLE_FRAGMENTS; p++) {
        RigidBody *parent = &pw->bodies[parents[p]];
        Vec3 center = parent->position;
        Vec3 half = parent->half_extent;
        f32 mass = parent->mass;
        u32 created[DESTRUCTIBLE_FRAGMENTS];
        if (!split_box(pw, center, half, mass, created)) {
            for (u32 k = before; k < pw->count; k++) {
                if (k != 0u) physics_body_park(pw, k);
            }
            return;
        }
        for (u32 c = 0; c < DESTRUCTIBLE_FRAGMENTS; c++) next[p * DESTRUCTIBLE_FRAGMENTS + c] = created[c];
    }
    for (u32 p = 0; p < DESTRUCTIBLE_FRAGMENTS; p++) physics_body_park(pw, parents[p]);
    for (u32 i = 0; i < DESTRUCTIBLE_MAX_PIECES; i++) d->fragments[i] = next[i];
    d->fragment_count = DESTRUCTIBLE_MAX_PIECES;
    d->generation = 2;
}
