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

/* Returns true to keep `entity` in a filtered view. Called once per entity of
 * `snapshot`, in snapshot order, on the calling thread. */
typedef bool (*BreakWorldSnapshotEntityFilter)(void *user, const BreakWorldSnapshot *snapshot,
                                               Entity entity);

/* Builds a new immutable snapshot holding only the entities `keep` admits,
 * with their component bytes copied (the view does not reference `snapshot`,
 * which may be released first). Tick and schema hash are inherited; hash and
 * id are computed exactly as break_world_snapshot_build would for those
 * entities, so a filtered view diffs and applies like any snapshot and two
 * views of the same entities compare equal. This is the per-connection AOI
 * cull: pass a predicate over the connection's AOI scope. Returns NULL on
 * NULL snapshot/keep or allocation failure; the caller owns one reference. */
BreakWorldSnapshot *break_world_snapshot_filter(const BreakWorldSnapshot *snapshot,
                                                BreakWorldSnapshotEntityFilter keep,
                                                void *user);

#ifdef __cplusplus
}
#endif
