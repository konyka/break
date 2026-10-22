#pragma once

#include <ecs/ecs.h>
#include <ecs/replication_schema.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakWorldSnapshot BreakWorldSnapshot;

BreakWorldSnapshot *break_world_snapshot_build(
    World *world, const BreakComponentSchemaRegistry *schemas, u64 tick);
void break_world_snapshot_retain(BreakWorldSnapshot *snapshot);
void break_world_snapshot_release(BreakWorldSnapshot *snapshot);

u64 break_world_snapshot_tick(const BreakWorldSnapshot *snapshot);
u64 break_world_snapshot_id(const BreakWorldSnapshot *snapshot);
u64 break_world_snapshot_hash(const BreakWorldSnapshot *snapshot);
u64 break_world_snapshot_schema_hash(const BreakWorldSnapshot *snapshot);
usize break_world_snapshot_entity_count(const BreakWorldSnapshot *snapshot);
Entity break_world_snapshot_entity_at(const BreakWorldSnapshot *snapshot, usize index);
bool break_world_snapshot_has_entity(const BreakWorldSnapshot *snapshot, Entity entity);
bool break_world_snapshot_component_bytes(const BreakWorldSnapshot *snapshot,
                                           Entity entity, ComponentType component,
                                           const void **out_bytes, usize *out_size);

#ifdef __cplusplus
}
#endif
