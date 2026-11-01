#include <renderer/world_stream_world.h>

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
