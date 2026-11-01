#include <physics/soft_body.h>
#include <math.h>

static f32 mean_radius_sq(const SoftBody *body) {
    f32 sum = 0.0f;
    for (u32 i = 0; i < body->count; i++) sum += vec3_len_sq(body->rest[i]);
    return body->count > 0 ? sum / (f32)body->count : 0.0f;
}

bool soft_body_create_count(SoftBody *body, PhysicsWorld *pw, Vec3 center, f32 radius,
                            f32 mass, f32 stiffness, f32 volume_stiffness, u32 count) {
    if (!body || !pw || !(radius > 0.0f) || !(mass > 0.0f)) return false;
    if (!isfinite(stiffness) || stiffness < 0.0f || stiffness > 1.0f) return false;
    if (!isfinite(volume_stiffness) || volume_stiffness < 0.0f || volume_stiffness > 1.0f) return false;
    if (count < 4u || count > SOFT_BODY_MAX) return false;
    if (pw->count + count > pw->capacity) return false;
    Vec3 offsets[SOFT_BODY_MAX];
    for (u32 i = 0; i < count; i++) {
        f32 ang = (f32)i * 6.2831853f / (f32)count;
        f32 lift = (i & 1u) ? radius : -radius;
        offsets[i] = vec3(cosf(ang) * radius, lift * 0.5f, sinf(ang) * radius);
    }
    Vec3 mean = vec3(0, 0, 0);
    for (u32 i = 0; i < count; i++) mean = vec3_add(mean, offsets[i]);
    mean = vec3_scale(mean, 1.0f / (f32)count);
    f32 node_mass = mass / (f32)count;
    for (u32 i = 0; i < count; i++) {
        Vec3 rest = vec3_sub(offsets[i], mean);
        u32 id = physics_body_create_sphere(pw, vec3_add(center, rest), radius * 0.25f, node_mass, false, 0);
        if (id == UINT32_MAX) return false;
        body->nodes[i] = id;
        body->rest[i] = rest;
    }
    body->count = count;
    body->stiffness = stiffness;
    body->volume_stiffness = volume_stiffness;
    body->rest_radius_sq = mean_radius_sq(body);
    return true;
}

bool soft_body_create(SoftBody *body, PhysicsWorld *pw, Vec3 center, f32 radius, f32 mass, f32 stiffness) {
    return soft_body_create_count(body, pw, center, radius, mass, stiffness, 0.0f, 4u);
}

void soft_body_step(SoftBody *body, PhysicsWorld *pw) {
    if (!body || !pw || body->count == 0) return;
    Vec3 com = vec3(0, 0, 0);
    u32 live = 0;
    for (u32 i = 0; i < body->count; i++) {
        u32 id = body->nodes[i];
        if (id >= pw->count || physics_body_is_parked(&pw->bodies[id])) continue;
        com = vec3_add(com, pw->bodies[id].position);
        live++;
    }
    if (live == 0) return;
    com = vec3_scale(com, 1.0f / (f32)live);
    f32 k = body->stiffness;
    for (u32 i = 0; i < body->count; i++) {
        u32 id = body->nodes[i];
        if (id >= pw->count || physics_body_is_parked(&pw->bodies[id])) continue;
        RigidBody *node = &pw->bodies[id];
        if (node->is_static) continue;
        Vec3 goal = vec3_add(com, body->rest[i]);
        node->position = vec3_add(node->position, vec3_scale(vec3_sub(goal, node->position), k));
        node->rest_frames = 0;
    }
    if (!(body->volume_stiffness > 0.0f) || !(body->rest_radius_sq > 0.0f)) return;
    com = vec3(0, 0, 0);
    live = 0;
    for (u32 i = 0; i < body->count; i++) {
        u32 id = body->nodes[i];
        if (id >= pw->count || physics_body_is_parked(&pw->bodies[id])) continue;
        com = vec3_add(com, pw->bodies[id].position);
        live++;
    }
    if (live == 0) return;
    com = vec3_scale(com, 1.0f / (f32)live);
    f32 r2 = 0.0f;
    for (u32 i = 0; i < body->count; i++) {
        u32 id = body->nodes[i];
        if (id >= pw->count || physics_body_is_parked(&pw->bodies[id])) continue;
        r2 += vec3_len_sq(vec3_sub(pw->bodies[id].position, com));
    }
    r2 /= (f32)live;
    if (!(r2 > 1e-8f)) return;
    f32 scale = sqrtf(body->rest_radius_sq / r2);
    f32 blend = 1.0f + (scale - 1.0f) * body->volume_stiffness;
    for (u32 i = 0; i < body->count; i++) {
        u32 id = body->nodes[i];
        if (id >= pw->count || physics_body_is_parked(&pw->bodies[id])) continue;
        RigidBody *node = &pw->bodies[id];
        if (node->is_static) continue;
        Vec3 from = vec3_sub(node->position, com);
        node->position = vec3_add(com, vec3_scale(from, blend));
    }
}
