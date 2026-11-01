#include <physics/rope.h>

bool rope_create(Rope *rope, PhysicsWorld *pw, Vec3 start, Vec3 end, u32 segments, f32 node_mass) {
    if (!rope || !pw || segments == 0 || segments > ROPE_MAX_SEGMENTS || !(node_mass > 0.0f)) return false;
    u32 nodes = segments + 1u;
    u32 free_constraints = 0;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (!pw->constraints[i].active) free_constraints++;
    }
    if (free_constraints < segments) return false;
    if (pw->count + nodes > pw->capacity) return false;
    u32 before = pw->count;
    for (u32 i = 0; i < nodes; i++) {
        f32 t = (f32)i / (f32)segments;
        Vec3 pos = vec3(start.e[0] + (end.e[0] - start.e[0]) * t,
                        start.e[1] + (end.e[1] - start.e[1]) * t,
                        start.e[2] + (end.e[2] - start.e[2]) * t);
        bool pinned = i == 0u;
        u32 id = physics_body_create_sphere(pw, pos, 0.05f, pinned ? 0.0f : node_mass, pinned, 0);
        if (id == UINT32_MAX) {
            for (u32 k = before; k < pw->count; k++) physics_body_park(pw, k);
            return false;
        }
        rope->nodes[i] = id;
    }
    for (u32 i = 0; i < segments; i++) {
        Vec3 a = pw->bodies[rope->nodes[i]].position;
        Vec3 b = pw->bodies[rope->nodes[i + 1u]].position;
        f32 rest = vec3_len(vec3_sub(b, a));
        if (physics_constraint_add_distance(pw, rope->nodes[i], rope->nodes[i + 1u], rest) == UINT32_MAX) {
            for (u32 k = before; k < pw->count; k++) physics_body_park(pw, k);
            rope->count = 0;
            return false;
        }
    }
    rope->count = nodes;
    return true;
}
