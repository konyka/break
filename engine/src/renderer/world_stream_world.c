#include <renderer/world_stream_world.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u32 world_stream_commit(World *world, const StreamWant *wants, u32 count,
                        Entity *slots, u32 tile_count_x, u32 tile_count_z,
                        u32 *rejected) {
    if (rejected) *rejected = 0;
    if (!world || !wants || !slots || count == 0 || tile_count_x == 0 || tile_count_z == 0) {
        return 0;
    }
    u32 applied = 0;
    u32 bad = 0;
    for (u32 i = 0; i < count; i++) {
        u32 x = wants[i].tile_x;
        u32 z = wants[i].tile_z;
        if (x >= tile_count_x || z >= tile_count_z) {
            bad++;
            continue;
        }
        Entity *slot = &slots[z * tile_count_x + x];
        if (wants[i].resident) {
            if (!entity_valid(*slot) || !world_entity_exists(world, *slot)) {
                Entity created = world_create_entity(world);
                if (!entity_valid(created)) {
                    bad++;
                    continue;
                }
                *slot = created;
            }
        } else if (entity_valid(*slot)) {
            world_destroy_entity(world, *slot);
            *slot = ENTITY_NULL;
        }
        applied++;
    }
    if (rejected) *rejected = bad;
    return applied;
}

static bool stream_tile_parse(const u8 *data, usize file_size, StreamTileData *tile, u32 x, u32 z) {
    if (!data || file_size < 12u) return false;
    u32 magic = 0, version = 0, vcount = 0;
    memcpy(&magic, data, 4);
    memcpy(&version, data + 4, 4);
    memcpy(&vcount, data + 8, 4);
    if (magic != STREAM_TILE_MAGIC || version != STREAM_TILE_VERSION) return false;
    if (vcount == 0u || vcount > STREAM_TILE_MAX_VERTS) return false;
    usize need = 12u + (usize)vcount * sizeof(MeshStageVertex);
    if (file_size != need) return false;
    memset(tile, 0, sizeof *tile);
    tile->x = x;
    tile->z = z;
    tile->vertex_count = vcount;
    memcpy(tile->verts, data + 12, (usize)vcount * sizeof(MeshStageVertex));
    return true;
}

u32 world_stream_commit_vfs(World *world, VFS *vfs, const StreamWant *wants, u32 count,
                            Entity *slots, u32 tile_count_x, u32 tile_count_z,
                            u32 *rejected) {
    if (rejected) *rejected = 0;
    if (!world || !vfs || !wants || !slots || count == 0 || tile_count_x == 0 || tile_count_z == 0) {
        return 0;
    }
    world_register_component(world, STREAM_TILE_COMPONENT, (u32)sizeof(StreamTileData));
    u32 applied = 0;
    u32 bad = 0;
    for (u32 i = 0; i < count; i++) {
        u32 x = wants[i].tile_x;
        u32 z = wants[i].tile_z;
        if (x >= tile_count_x || z >= tile_count_z) {
            bad++;
            continue;
        }
        Entity *slot = &slots[z * tile_count_x + x];
        if (!wants[i].resident) {
            if (entity_valid(*slot)) {
                world_destroy_entity(world, *slot);
                *slot = ENTITY_NULL;
            }
            applied++;
            continue;
        }
        if (entity_valid(*slot) && world_entity_exists(world, *slot)) {
            applied++;
            continue;
        }
        char path[64];
        int wrote = snprintf(path, sizeof path, "tile_%u_%u.bin", x, z);
        if (wrote < 0 || (usize)wrote >= sizeof path) {
            bad++;
            continue;
        }
        usize file_size = 0;
        u8 *data = vfs_read_all(vfs, path, &file_size);
        StreamTileData parsed;
        if (!stream_tile_parse(data, file_size, &parsed, x, z)) {
            free(data);
            bad++;
            continue;
        }
        free(data);
        Entity created = world_create_entity(world);
        StreamTileData *tile = entity_valid(created)
            ? (StreamTileData *)world_add_component(world, created, STREAM_TILE_COMPONENT)
            : NULL;
        if (!tile) {
            if (entity_valid(created)) world_destroy_entity(world, created);
            bad++;
            continue;
        }
        *tile = parsed;
        *slot = created;
        applied++;
    }
    if (rejected) *rejected = bad;
    return applied;
}
