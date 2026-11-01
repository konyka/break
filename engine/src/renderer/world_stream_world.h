#pragma once
#include <ecs/ecs.h>
#include <asset/vfs.h>
#include <renderer/world_stream.h>

/* Turn resident wants into entities on the calling thread. `slots` is
 * tile_count_z * tile_count_x, row-major in z. A load stores one entity per
 * tile and does not create a second one if that slot is already live. An
 * unload destroys the entity and writes ENTITY_NULL. Out-of-range tiles
 * increment *rejected and leave the slot unchanged. This does not read VFS. */
u32 world_stream_commit(World *world, const StreamWant *wants, u32 count,
                        Entity *slots, u32 tile_count_x, u32 tile_count_z,
                        u32 *rejected);

#define STREAM_TILE_COMPONENT 120u
#define STREAM_TILE_BYTES 32u

typedef struct StreamTileData {
    u32 x;
    u32 z;
    u32 size; /* bytes stored, at most STREAM_TILE_BYTES */
    u8  bytes[STREAM_TILE_BYTES];
} StreamTileData;

/* Like world_stream_commit, and a load reads `tile_<x>_<z>.bin` from vfs.
 * A missing or empty file rejects that tile and creates no entity. The
 * entity stores the first 32 bytes on component 120. A second load of a
 * live tile does not read again and does not create another entity. */
u32 world_stream_commit_vfs(World *world, VFS *vfs, const StreamWant *wants, u32 count,
                            Entity *slots, u32 tile_count_x, u32 tile_count_z,
                            u32 *rejected);
