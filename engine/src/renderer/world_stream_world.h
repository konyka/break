#pragma once
#include <ecs/ecs.h>
#include <asset/vfs.h>
#include <renderer/mesh_stage.h>
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
#define STREAM_TILE_MAGIC 0x314C4954u /* 'TIL1' little-endian */
#define STREAM_TILE_VERSION 1u
#define STREAM_TILE_MAX_VERTS 64u

typedef struct StreamTileData {
    u32 x;
    u32 z;
    u32 vertex_count;
    MeshStageVertex verts[STREAM_TILE_MAX_VERTS];
} StreamTileData;

/* Like world_stream_commit, and a load reads `tile_<x>_<z>.bin` from vfs.
 * The file is magic, version, vertex_count, then that many MeshStageVertex.
 * Version must be 1, the count must be 1..64, and the file length must match.
 * Anything else rejects the tile and creates no entity. A second load of a
 * live tile does not read again and does not create another entity. */
u32 world_stream_commit_vfs(World *world, VFS *vfs, const StreamWant *wants, u32 count,
                            Entity *slots, u32 tile_count_x, u32 tile_count_z,
                            u32 *rejected);
