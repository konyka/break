#include <renderer/voxel.h>

static const i32 k_face_n[6][3] = {
    {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}
};

static u8 voxel_at(const u8 *blocks, u32 sx, u32 sy, u32 sz, i32 x, i32 y, i32 z) {
    if (x < 0 || y < 0 || z < 0) return 0;
    if ((u32)x >= sx || (u32)y >= sy || (u32)z >= sz) return 0;
    return blocks[(u32)x + (u32)y * sx + (u32)z * sx * sy];
}

u32 voxel_build_faces(const u8 *blocks, u32 size_x, u32 size_y, u32 size_z, f32 cell,
                      VoxelVertex *out, u32 cap, u32 *dropped_faces) {
    if (dropped_faces) *dropped_faces = 0;
    if (!blocks || size_x == 0 || size_y == 0 || size_z == 0 || !(cell > 0.0f)) return 0;
    if (cap > 0 && !out) return 0;
    if (size_x > 64u || size_y > 64u || size_z > 64u) return 0;
    u32 written = 0;
    u32 dropped = 0;
    for (u32 z = 0; z < size_z; z++) {
        for (u32 y = 0; y < size_y; y++) {
            for (u32 x = 0; x < size_x; x++) {
                if (voxel_at(blocks, size_x, size_y, size_z, (i32)x, (i32)y, (i32)z) == 0) continue;
                for (int face = 0; face < 6; face++) {
                    i32 nx = (i32)x + k_face_n[face][0];
                    i32 ny = (i32)y + k_face_n[face][1];
                    i32 nz = (i32)z + k_face_n[face][2];
                    if (voxel_at(blocks, size_x, size_y, size_z, nx, ny, nz) != 0) continue;
                    if (written + 4u > cap) {
                        dropped++;
                        continue;
                    }
                    Vec3 normal = vec3((f32)k_face_n[face][0], (f32)k_face_n[face][1], (f32)k_face_n[face][2]);
                    f32 x0 = (f32)x * cell;
                    f32 y0 = (f32)y * cell;
                    f32 z0 = (f32)z * cell;
                    f32 x1 = x0 + cell;
                    f32 y1 = y0 + cell;
                    f32 z1 = z0 + cell;
                    Vec3 quad[4];
                    if (face == 0) {
                        quad[0] = vec3(x1, y0, z0); quad[1] = vec3(x1, y1, z0);
                        quad[2] = vec3(x1, y1, z1); quad[3] = vec3(x1, y0, z1);
                    } else if (face == 1) {
                        quad[0] = vec3(x0, y0, z1); quad[1] = vec3(x0, y1, z1);
                        quad[2] = vec3(x0, y1, z0); quad[3] = vec3(x0, y0, z0);
                    } else if (face == 2) {
                        quad[0] = vec3(x0, y1, z0); quad[1] = vec3(x0, y1, z1);
                        quad[2] = vec3(x1, y1, z1); quad[3] = vec3(x1, y1, z0);
                    } else if (face == 3) {
                        quad[0] = vec3(x0, y0, z1); quad[1] = vec3(x0, y0, z0);
                        quad[2] = vec3(x1, y0, z0); quad[3] = vec3(x1, y0, z1);
                    } else if (face == 4) {
                        quad[0] = vec3(x0, y0, z1); quad[1] = vec3(x1, y0, z1);
                        quad[2] = vec3(x1, y1, z1); quad[3] = vec3(x0, y1, z1);
                    } else {
                        quad[0] = vec3(x1, y0, z0); quad[1] = vec3(x0, y0, z0);
                        quad[2] = vec3(x0, y1, z0); quad[3] = vec3(x1, y1, z0);
                    }
                    for (int v = 0; v < 4; v++) {
                        out[written].position = quad[v];
                        out[written].normal = normal;
                        written++;
                    }
                }
            }
        }
    }
    if (dropped_faces) *dropped_faces = dropped;
    return written;
}
