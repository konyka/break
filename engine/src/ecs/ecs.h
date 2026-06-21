#pragma once
#include <core/types.h>

#define ECS_MAX_COMPONENTS 128
#define ECS_CHUNK_SIZE     (16 * 1024)
#define ECS_MAX_ENTITIES   (64 * 1024)
#define ECS_MAX_ARCHETYPES 1024
#define ECS_QUERY_CACHE_SIZE 64
#define ECS_ENTITY_BITMAP_WORDS ((ECS_MAX_ENTITIES + 63) / 64)

typedef u32 ComponentType;

typedef struct {
    u32 index;
    u32 generation;
} Entity;

#define ENTITY_NULL ((Entity){0, 0})
#define entity_valid(e) ((e).generation != 0)

typedef struct {
    ComponentType *ids;
    u32            count;
} ArchetypeKey;

typedef struct Chunk Chunk;

struct Chunk {
    Chunk *next;
    u32    count;
    u32    capacity;
};

typedef struct Archetype Archetype;

typedef struct {
    ComponentType component;
    Archetype    *target;
} ArchetypeEdge;

struct Archetype {
    ArchetypeKey    key;
    Chunk          *chunks;
    Chunk          *chunk_tail;
    u32            *offsets;
    u32             chunk_capacity;
    u32             entity_offset;
    u32             total_count;
    u32             stride;
    ArchetypeEdge  *edges_add;
    u32             edges_add_count;
    ArchetypeEdge  *edges_remove;
    u32             edges_remove_count;
};

#define ECS_QUERY_INLINE_CAP 64

typedef struct {
    Archetype **matching;
    u32         match_count;
    u32         match_cap;
    /* Inline buffer avoids heap alloc for typical queries (≤64 matching archetypes) */
    Archetype  *_inline_matching[ECS_QUERY_INLINE_CAP];
    /* Cache fields */
    u32         cache_signature;  /* hash of component types for cache lookup */
    u32         cache_version;    /* world version when cache was populated */
    bool        cached;           /* true if this query result is cached */
    /* Exclude/Optional masks (component ID must be < 64) */
    u64         exclude_mask;     /* archetypes containing any of these are excluded */
    u64         optional_mask;    /* optional components: column may be NULL if absent */
} Query;

typedef struct {
    Query     *query;
    u32        arch_index;
    Chunk     *chunk;
    u32        index;
} QueryIter;

typedef struct {
    Archetype  archetypes[ECS_MAX_ARCHETYPES];
    u32        archetype_count;

    Entity    *entities;
    u32       *entity_archetype;
    u32       *entity_index;
    u32        entity_count;
    u32       *free_stack;
    u32        free_stack_top;

    u32        component_sizes[ECS_MAX_COMPONENTS];

    Query      queries[256];
    u32        query_count;
    u32        query_next_slot;

    /* Query cache: maps signature hash to query slot for O(1) lookup */
    u32        query_cache[ECS_QUERY_CACHE_SIZE]; /* slot index, 0xFFFFFFFF = empty */
    u32        cache_version; /* incremented on structural changes */

    /* Archetype hash: FNV1a of sorted component type IDs for fast early-reject */
    u32        archetype_hash[ECS_MAX_ARCHETYPES];

    /* Entity bitmap: fast O(1) entity existence check per archetype */
    u64        entity_bitmap[ECS_ENTITY_BITMAP_WORDS];
} World;

World *world_create(void);
void   world_destroy(World *w);

Entity world_create_entity(World *w);
void   world_destroy_entity(World *w, Entity e);

void  world_register_component(World *w, ComponentType id, u32 size);
void *world_add_component(World *w, Entity e, ComponentType id);
void *world_get_component(World *w, Entity e, ComponentType id);
void  world_remove_component(World *w, Entity e, ComponentType id);

Query     *world_query(World *w, const ComponentType *types, u32 count);
Query     *world_query_cached(World *w, const ComponentType *types, u32 count);
QueryIter  query_begin(Query *q);
bool       query_next(QueryIter *it);
void       query_done(Query *q);

/* Exclude/Optional query builders (component ID must be < 64) */
void       ecs_query_exclude(Query *q, ComponentType comp_id);
void       ecs_query_optional(Query *q, ComponentType comp_id);

/* Re-run archetype matching with current exclude/optional masks applied.
 * Call after ecs_query_exclude / ecs_query_optional to rebuild matching list. */
void       ecs_query_refresh(World *w, Query *q, const ComponentType *types, u32 count);

/* Entity bitmap operations */
bool       world_entity_exists(World *w, Entity e);
void       world_query_invalidate(World *w);

void *chunk_get_component(Chunk *c, u32 index, u32 component_offset, u32 component_size);
Entity chunk_get_entity(Chunk *c, u32 index, u32 entity_offset);
