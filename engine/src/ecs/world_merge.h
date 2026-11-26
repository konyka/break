#pragma once
/* Authoritative merge of peer-written World state.
 *
 * Replication brings each peer's World into its own inbound World (one per
 * connection, see world_session.h). Nothing there is trusted. This module is
 * the only path by which such state reaches the authoritative World, and it
 * decides per entity and per component what a peer may change:
 *
 *  - Identity: entities are matched by persistent id (net_entity_map.h).
 *    The authoritative map resolves an id in the authoritative World; each
 *    connection has its own map for its inbound World, because a peer's
 *    Entity values are its own and an id binds to one place per map.
 *  - Ownership: the authority grants a connection ownership of ids. A
 *    connection may only write entities it owns; everything else in its
 *    inbound World is ignored.
 *  - Writable components: only components registered as writable are merged.
 *    Each has a validate callback that sees the authoritative value and the
 *    proposed one and may accept, clamp (by writing the accepted value) or
 *    reject.
 *  - Transactional: merge_connection either applies every accepted change of
 *    that connection or none. A rejected value rejects the whole batch, so a
 *    peer cannot get half of an inconsistent update through.
 *  - No structural changes: a peer cannot create or destroy authoritative
 *    entities or add/remove components. An owned entity missing from the
 *    inbound World, or lacking a writable component there, is left alone.
 *
 * Owner thread only (the thread that owns the authoritative World); no
 * locks. Design: docs/design/ecs_snapshot_replication_aoi.md
 * "权威合并". */
#include <ecs/ecs.h>
#include <ecs/net_entity_map.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_WORLD_MERGE_MAX_COMPONENTS 32u
#define BREAK_WORLD_MERGE_MAX_OWNED 4096u
#define BREAK_WORLD_MERGE_MAX_VALUE_BYTES 4096u

typedef u64 BreakWorldMergeConnection;

typedef enum BreakWorldMergeResult {
    BREAK_WORLD_MERGE_OK = 0,
    BREAK_WORLD_MERGE_INVALID,   /* bad argument or configuration */
    BREAK_WORLD_MERGE_REJECTED,  /* a validate callback refused; nothing applied */
    BREAK_WORLD_MERGE_CONFLICT,  /* the id is owned by another connection */
    BREAK_WORLD_MERGE_OVERLOAD,  /* owned capacity reached */
    BREAK_WORLD_MERGE_NOT_FOUND
} BreakWorldMergeResult;

typedef enum BreakWorldMergeVerdict {
    BREAK_WORLD_MERGE_ACCEPT = 0, /* write `accepted` (pre-filled with the proposed value) */
    BREAK_WORLD_MERGE_KEEP,       /* leave this component as it is; the batch goes on */
    BREAK_WORLD_MERGE_REJECT      /* refuse the whole batch */
} BreakWorldMergeVerdict;

/* `current` is the authoritative value, `proposed` the peer's; both `size`
 * bytes. `accepted` starts as a copy of `proposed` and may be changed (for
 * example clamped) before ACCEPT. */
typedef BreakWorldMergeVerdict (*BreakWorldMergeValidateFn)(
    void *user, BreakWorldMergeConnection connection, BreakNetEntityId id,
    ComponentType component, const void *current, const void *proposed, void *accepted,
    u32 size);

typedef struct BreakWorldMergeComponent {
    ComponentType component;
    BreakWorldMergeValidateFn validate; /* required */
    void *user;
} BreakWorldMergeComponent;

typedef struct BreakWorldMergeConfig {
    World *authoritative;            /* borrowed */
    const BreakNetEntityMap *ids;    /* borrowed; resolves ids in the authoritative World */
    u32 authoritative_key;           /* world_key of the authoritative World in `ids` */
    const BreakWorldMergeComponent *components; /* copied */
    u32 component_count;             /* 1..BREAK_WORLD_MERGE_MAX_COMPONENTS */
    u32 max_owned;                   /* 1..BREAK_WORLD_MERGE_MAX_OWNED */
} BreakWorldMergeConfig;

typedef struct BreakWorldMergeReport {
    u32 entities;  /* owned entities found in the inbound World */
    u32 written;   /* component values written to the authoritative World */
    u32 kept;      /* values a validate callback kept unchanged */
    u32 unchanged; /* values equal to the authoritative one (not validated) */
    u32 skipped;   /* owned entities or components absent on one side */
} BreakWorldMergeReport;

typedef struct BreakWorldMergeStats {
    u64 merges;
    u64 rejected;
    u64 written;
    u32 owned;
} BreakWorldMergeStats;

typedef struct BreakWorldMerge BreakWorldMerge;

BreakWorldMergeResult break_world_merge_create(const BreakWorldMergeConfig *config,
                                               BreakWorldMerge **out);
void break_world_merge_destroy(BreakWorldMerge *merge);

/* Grants `connection` write ownership of `id`. Granting an id it already
 * owns is OK; an id owned by another connection is CONFLICT. */
BreakWorldMergeResult break_world_merge_grant(BreakWorldMerge *merge,
                                              BreakWorldMergeConnection connection,
                                              BreakNetEntityId id);
BreakWorldMergeResult break_world_merge_revoke(BreakWorldMerge *merge, BreakNetEntityId id);
/* Revokes every id `connection` owns (on disconnect); returns how many. */
u32 break_world_merge_revoke_connection(BreakWorldMerge *merge,
                                        BreakWorldMergeConnection connection);
/* The owner of `id`, or 0 when nobody owns it. */
BreakWorldMergeConnection break_world_merge_owner(const BreakWorldMerge *merge,
                                                  BreakNetEntityId id);

/* Merges `inbound` for `connection`. `inbound_ids` resolves ids in
 * `inbound` under `inbound_key`. On REJECTED nothing changed in the
 * authoritative World. `report` may be NULL; it is zeroed on any non-OK
 * result. */
BreakWorldMergeResult break_world_merge_connection(BreakWorldMerge *merge,
                                                   BreakWorldMergeConnection connection,
                                                   World *inbound,
                                                   const BreakNetEntityMap *inbound_ids,
                                                   u32 inbound_key,
                                                   BreakWorldMergeReport *report);

void break_world_merge_stats(const BreakWorldMerge *merge, BreakWorldMergeStats *out);

#ifdef __cplusplus
}
#endif
