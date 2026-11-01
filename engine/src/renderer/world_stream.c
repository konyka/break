#include <renderer/world_stream.h>

u32 world_stream_want(u32 camera_tile_x, u32 camera_tile_z,
                      u32 tile_count_x, u32 tile_count_z,
                      const bool *resident, u32 resident_len,
                      StreamWant *out, u32 cap) {
    if (!resident || tile_count_x == 0 || tile_count_z == 0) return 0;
    if (tile_count_x > UINT32_MAX / tile_count_z) return 0;
    if (resident_len < tile_count_x * tile_count_z) return 0;
    if (cap > 0 && !out) return 0;
    u32 written = 0;
    for (u32 z = 0; z < tile_count_z; z++) {
        for (u32 x = 0; x < tile_count_x; x++) {
            u32 dx = x > camera_tile_x ? x - camera_tile_x : camera_tile_x - x;
            u32 dz = z > camera_tile_z ? z - camera_tile_z : camera_tile_z - z;
            u32 cheb = dx > dz ? dx : dz;
            bool is_resident = resident[z * tile_count_x + x];
            bool load = cheb <= 1u && !is_resident;
            bool unload = cheb >= 3u && is_resident;
            if (!load && !unload) continue;
            if (written >= cap) return written;
            out[written].tile_x = x;
            out[written].tile_z = z;
            out[written].resident = load;
            written++;
        }
    }
    return written;
}
