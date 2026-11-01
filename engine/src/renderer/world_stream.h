#pragma once
#include <core/types.h>

typedef struct StreamWant {
    u32 tile_x;
    u32 tile_z;
    bool resident; /* true: load, false: unload */
} StreamWant;

u32 world_stream_want(u32 camera_tile_x, u32 camera_tile_z,
                      u32 tile_count_x, u32 tile_count_z,
                      const bool *resident, u32 resident_len,
                      StreamWant *out, u32 cap);
