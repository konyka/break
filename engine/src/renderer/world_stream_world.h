#pragma once
#include <ecs/ecs.h>
#include <renderer/world_stream.h>

/* Turn resident wants into entities on the calling thread. `slots` is
 * tile_count_z * tile_count_x, row-major in z. A load stores one entity per
 * tile and does not create a second one if that slot is already live. An
 * unload destroys the entity and writes ENTITY_NULL. Out-of-range tiles
 * increment *rejected and leave the slot unchanged. This does not read VFS. */
u32 world_stream_commit(World *world, const StreamWant *wants, u32 count,
                        Entity *slots, u32 tile_count_x, u32 tile_count_z,
                        u32 *rejected);
