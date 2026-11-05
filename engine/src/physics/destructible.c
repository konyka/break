#include <physics/destructible.h>

bool destructible_create(Destructible *d, PhysicsWorld *pw, Vec3 center, Vec3 half_extent,
                         f32 mass, f32 break_impulse) {
    if (!d || !pw || !(mass > 0.0f) || !(break_impulse > 0.0f)) return false;
    for (int i = 0; i < 3; i++) {
        if (!(half_extent.e[i] > 0.0f) || !isfinite(center.e[i])) return false;
    }
    PhysicsBodyHandle id = physics_body_create(pw, center, half_extent, mass, false, 0);
    if (!physics_body_handle_is_valid(id)) return false;
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

static void park_handles(PhysicsWorld *pw, PhysicsBodyHandle *ids, u32 count) {
    for (u32 i = 0; i < count; i++) physics_body_park(pw, ids[i]);
}

static bool split_box(PhysicsWorld *pw, Vec3 center, Vec3 half, f32 mass, PhysicsBodyHandle *out_ids) {
    if (pw->count + DESTRUCTIBLE_FRAGMENTS > pw->capacity) return false;
    Vec3 child_half = vec3_scale(half, 0.5f);
    f32 child_mass = mass / (f32)DESTRUCTIBLE_FRAGMENTS;
    u32 created = 0;
    for (u32 i = 0; i < DESTRUCTIBLE_FRAGMENTS; i++) {
        int ix = i & 1;
        int iy = (i >> 1) & 1;
        int iz = (i >> 2) & 1;
        Vec3 pos = vec3(center.e[0] + ((ix == 0) ? -child_half.e[0] : child_half.e[0]),
                        center.e[1] + ((iy == 0) ? -child_half.e[1] : child_half.e[1]),
                        center.e[2] + ((iz == 0) ? -child_half.e[2] : child_half.e[2]));
        PhysicsBodyHandle id = physics_body_create(pw, pos, child_half, child_mass, false, 0);
        if (!physics_body_handle_is_valid(id)) {
            park_handles(pw, out_ids, created);
            return false;
        }
        out_ids[i] = id;
        created++;
    }
    return true;
}

void destructible_apply_impulse(Destructible *d, PhysicsWorld *pw, f32 impulse) {
    if (!d || !pw || (!d->broken && !physics_body_resolve(pw, d->root))) return;
    if (!(impulse >= d->break_impulse)) return;
    if (!d->broken) {
        PhysicsBodyHandle created[DESTRUCTIBLE_FRAGMENTS];
        if (!split_box(pw, d->center, d->half_extent, d->mass, created)) return;
        physics_body_park(pw, d->root);
        for (u32 i = 0; i < DESTRUCTIBLE_FRAGMENTS; i++) d->fragments[i] = created[i];
        d->fragment_count = DESTRUCTIBLE_FRAGMENTS;
        d->broken = true;
        d->generation = 1;
        return;
    }
    if (d->generation == 1u && d->fragment_count == DESTRUCTIBLE_FRAGMENTS) {
        if (pw->count + DESTRUCTIBLE_GEN2_PIECES > pw->capacity) return;
        PhysicsBodyHandle parents[DESTRUCTIBLE_FRAGMENTS];
        for (u32 i = 0; i < DESTRUCTIBLE_FRAGMENTS; i++) parents[i] = d->fragments[i];
        PhysicsBodyHandle next[DESTRUCTIBLE_GEN2_PIECES];
        u32 next_count = 0;
        for (u32 p = 0; p < DESTRUCTIBLE_FRAGMENTS; p++) {
            RigidBody *parent = physics_body_resolve(pw, parents[p]);
            if (!parent) return;
            PhysicsBodyHandle created[DESTRUCTIBLE_FRAGMENTS];
            if (!split_box(pw, parent->position, parent->half_extent, parent->mass, created)) {
                park_handles(pw, next, next_count);
                return;
            }
            for (u32 c = 0; c < DESTRUCTIBLE_FRAGMENTS; c++) next[next_count++] = created[c];
        }
        park_handles(pw, parents, DESTRUCTIBLE_FRAGMENTS);
        for (u32 i = 0; i < DESTRUCTIBLE_GEN2_PIECES; i++) d->fragments[i] = next[i];
        d->fragment_count = DESTRUCTIBLE_GEN2_PIECES;
        d->generation = 2;
        return;
    }
    if (d->generation != 2u || d->fragment_count != DESTRUCTIBLE_GEN2_PIECES) return;
    if (pw->count + DESTRUCTIBLE_MAX_PIECES > pw->capacity) return;
    PhysicsBodyHandle parents[DESTRUCTIBLE_GEN2_PIECES];
    for (u32 i = 0; i < DESTRUCTIBLE_GEN2_PIECES; i++) parents[i] = d->fragments[i];
    PhysicsBodyHandle next[DESTRUCTIBLE_MAX_PIECES];
    u32 next_count = 0;
    for (u32 p = 0; p < DESTRUCTIBLE_GEN2_PIECES; p++) {
        RigidBody *parent = physics_body_resolve(pw, parents[p]);
        if (!parent) return;
        PhysicsBodyHandle created[DESTRUCTIBLE_FRAGMENTS];
        if (!split_box(pw, parent->position, parent->half_extent, parent->mass, created)) {
            park_handles(pw, next, next_count);
            return;
        }
        for (u32 c = 0; c < DESTRUCTIBLE_FRAGMENTS; c++) next[next_count++] = created[c];
    }
    park_handles(pw, parents, DESTRUCTIBLE_GEN2_PIECES);
    for (u32 i = 0; i < DESTRUCTIBLE_MAX_PIECES; i++) d->fragments[i] = next[i];
    d->fragment_count = DESTRUCTIBLE_MAX_PIECES;
    d->generation = 3;
}
