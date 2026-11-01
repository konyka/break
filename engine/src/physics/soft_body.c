#include <physics/soft_body.h>

bool soft_body_create(SoftBody *body, PhysicsWorld *pw, Vec3 center, f32 radius, f32 mass, f32 stiffness) {
    if (!body || !pw || !(radius > 0.0f) || !(mass > 0.0f) || !isfinite(stiffness)) return false;
    if (stiffness < 0.0f || stiffness > 1.0f) return false;
    if (pw->count + 4u > pw->capacity) return false;
    Vec3 offsets[4] = {
        vec3(radius, radius, radius),
        vec3(radius, -radius, -radius),
        vec3(-radius, radius, -radius),
        vec3(-radius, -radius, radius)
    };
    for (u32 i = 0; i < 4u; i++) {
        Vec3 pos = vec3_add(center, offsets[i]);
        u32 id = physics_body_create_sphere(pw, pos, radius * 0.25f, mass * 0.25f, false, 0);
        if (id == UINT32_MAX) return false;
        body->nodes[i] = id;
        body->rest[i] = offsets[i];
    }
    body->count = 4;
    body->stiffness = stiffness;
    return true;
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
}
