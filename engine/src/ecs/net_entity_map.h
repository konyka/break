#pragma once
/* Cross-World persistent network identity (docs/design/ecs_snapshot_replication_aoi.md,
 * section "跨 World 持久身份").
 *
 * A World Entity {index, generation} is local to one World and dies with it.
 * A BreakNetEntityId is a u64 that names the same logical object across
 * Worlds: when the object moves to a new World (level change, cell handoff,
 * a rebuilt inbound World) the id is rebound to the new Entity and stays the
 * same on the wire.
 *
 * Rules:
 *  - Ids are non-zero. Locally allocated ids are strictly increasing and
 *    never reused, even after release, so a stale id on the wire can never
 *    name a different object. adopt() registers an id allocated elsewhere
 *    (e.g. by the authority) and moves the local allocator past it.
 *  - Each id is bound to exactly one (world_key, Entity) and each
 *    (world_key, Entity) to at most one id; a second binding is CONFLICT.
 *  - world_key is a caller-chosen u32 naming the World (e.g. a level
 *    generation); the map never dereferences a World.
 *  - Bounded: at most `capacity` live bindings; a full map is OVERLOAD.
 *  - Not thread-safe: owned by the thread that owns the Worlds (LogicThread).
 *    Allocation happens only at create. */

#include <core/types.h>
#include <ecs/ecs.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef u64 BreakNetEntityId; /* 0 = none */

#define BREAK_NET_ENTITY_MAP_MAX_CAPACITY 65536u

typedef enum BreakNetEntityResult {
    BREAK_NET_ENTITY_OK = 0,
    BREAK_NET_ENTITY_INVALID,   /* NULL argument, id 0, invalid Entity */
    BREAK_NET_ENTITY_NOT_FOUND, /* no such binding */
    BREAK_NET_ENTITY_CONFLICT,  /* id or (world_key, Entity) already bound elsewhere */
    BREAK_NET_ENTITY_OVERLOAD,  /* capacity live bindings already */
    BREAK_NET_ENTITY_EXHAUSTED  /* the u64 id space is used up */
} BreakNetEntityResult;

typedef struct BreakNetEntityMapConfig {
    u32 capacity; /* 1..BREAK_NET_ENTITY_MAP_MAX_CAPACITY */
    u64 first_id; /* first locally allocated id; must be non-zero */
} BreakNetEntityMapConfig;

typedef struct BreakNetEntityMapStats {
    u32 bound;     /* live bindings */
    u64 next_id;   /* next locally allocated id (0 once exhausted) */
    u64 conflicts; /* bind/rebind/adopt rejected CONFLICT */
    u64 overloads; /* bind/adopt rejected OVERLOAD */
} BreakNetEntityMapStats;

typedef struct BreakNetEntityMap BreakNetEntityMap;

/* false on NULL arguments, capacity 0 or above the max, first_id 0, or
 * allocation failure; *out is then NULL. */
bool break_net_entity_map_create(const BreakNetEntityMapConfig *config, BreakNetEntityMap **out);
void break_net_entity_map_destroy(BreakNetEntityMap *map);

/* Allocates a fresh id and binds it to (world_key, entity). *out_id is 0 on
 * any failure. */
BreakNetEntityResult break_net_entity_map_bind_new(BreakNetEntityMap *map, u32 world_key,
                                                   Entity entity, BreakNetEntityId *out_id);

/* Binds an id allocated elsewhere. The local allocator then never hands out
 * an id at or below it. */
BreakNetEntityResult break_net_entity_map_adopt(BreakNetEntityMap *map, BreakNetEntityId id,
                                                u32 world_key, Entity entity);

/* Moves a bound id to (world_key, entity). Rebinding to its current place is
 * OK; a target already holding another id is CONFLICT and nothing changes. */
BreakNetEntityResult break_net_entity_map_rebind(BreakNetEntityMap *map, BreakNetEntityId id,
                                                 u32 world_key, Entity entity);

/* Drops a binding. The id is never allocated again. */
BreakNetEntityResult break_net_entity_map_release(BreakNetEntityMap *map, BreakNetEntityId id);

BreakNetEntityResult break_net_entity_map_entity(const BreakNetEntityMap *map, BreakNetEntityId id,
                                                 u32 *out_world_key, Entity *out_entity);
BreakNetEntityResult break_net_entity_map_id(const BreakNetEntityMap *map, u32 world_key,
                                             Entity entity, BreakNetEntityId *out_id);
BreakNetEntityResult break_net_entity_map_stats(const BreakNetEntityMap *map,
                                                BreakNetEntityMapStats *out_stats);

/* AOI scope driven by persistent ids. `ids`/`count` are a connection's visible
 * BreakNetEntityId set (e.g. break_aoi_compute output); `map` resolves each
 * World Entity in `world_key` to its id. Pass a pointer to this struct as the
 * `user` of break_world_snapshot_filter / break_world_session_publish_filtered
 * via break_net_entity_scope_keep. Borrowed; the caller owns map and ids. */
typedef struct BreakNetEntityScope {
    const BreakNetEntityMap *map;
    u32 world_key;
    const BreakNetEntityId *ids;
    usize count;
} BreakNetEntityScope;

/* BreakWorldSnapshotEntityFilter: keeps `entity` when it has a bound id in
 * `world_key` and that id is in the scope's id set. An entity with no id, or an
 * id outside the set, is culled. A NULL scope or map keeps nothing. */
struct BreakWorldSnapshot;
bool break_net_entity_scope_keep(void *user, const struct BreakWorldSnapshot *snapshot,
                                 Entity entity);

#ifdef __cplusplus
} /* extern "C" */
#endif
