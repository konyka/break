#include <physics/cloth.h>

static u32 cloth_free_constraints(const PhysicsWorld *pw) {
    u32 free_slots = 0;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (!pw->constraints[i].active) free_slots++;
    }
    return free_slots;
}

bool cloth_create(Cloth *cloth, PhysicsWorld *pw, Vec3 origin, f32 spacing,
                  u32 width, u32 height, f32 node_mass) {
    if (!cloth || !pw || width < 2u || height < 2u || width > CLOTH_MAX_SIDE || height > CLOTH_MAX_SIDE) {
        return false;
    }
    if (!(spacing > 0.0f) || !(node_mass > 0.0f)) return false;
    u32 nodes = width * height;
    u32 structural = (width - 1u) * height + width * (height - 1u);
    u32 shear = (width - 1u) * (height - 1u) * 2u;
    u32 links = structural + shear;
    if (cloth_free_constraints(pw) < links) return false;
    if (pw->count + nodes > pw->capacity) return false;
    u32 before = pw->count;
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            Vec3 pos = vec3(origin.e[0] + (f32)x * spacing,
                            origin.e[1] - (f32)y * spacing,
                            origin.e[2]);
            bool pinned = y == 0u;
            u32 id = physics_body_create_sphere(pw, pos, spacing * 0.2f,
                                               pinned ? 0.0f : node_mass, pinned, 0);
            if (id == UINT32_MAX) {
                for (u32 k = before; k < pw->count; k++) {
                    if (k != 0u) physics_body_park(pw, k);
                }
                return false;
            }
            cloth->nodes[y * width + x] = id;
        }
    }
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            u32 id = cloth->nodes[y * width + x];
            if (x + 1u < width) {
                u32 right = cloth->nodes[y * width + x + 1u];
                if (physics_constraint_add_distance(pw, id, right, spacing) == UINT32_MAX) {
                    for (u32 k = before; k < pw->count; k++) {
                        if (k != 0u) physics_body_park(pw, k);
                    }
                    cloth->width = 0;
                    return false;
                }
            }
            if (y + 1u < height) {
                u32 below = cloth->nodes[(y + 1u) * width + x];
                if (physics_constraint_add_distance(pw, id, below, spacing) == UINT32_MAX) {
                    for (u32 k = before; k < pw->count; k++) {
                        if (k != 0u) physics_body_park(pw, k);
                    }
                    cloth->width = 0;
                    return false;
                }
            }
            if (x + 1u < width && y + 1u < height) {
                f32 diag = spacing * 1.41421356f;
                u32 down_right = cloth->nodes[(y + 1u) * width + x + 1u];
                u32 down_left = cloth->nodes[(y + 1u) * width + x];
                u32 right = cloth->nodes[y * width + x + 1u];
                if (physics_constraint_add_distance(pw, id, down_right, diag) == UINT32_MAX ||
                    physics_constraint_add_distance(pw, right, down_left, diag) == UINT32_MAX) {
                    for (u32 k = before; k < pw->count; k++) {
                        if (k != 0u) physics_body_park(pw, k);
                    }
                    cloth->width = 0;
                    return false;
                }
            }
        }
    }
    cloth->width = width;
    cloth->height = height;
    return true;
}
