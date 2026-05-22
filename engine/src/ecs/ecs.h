#pragma once
#include <core/types.h>

#define ECS_MAX_COMPONENTS 128
#define ECS_CHUNK_SIZE     (16 * 1024)
#define ECS_MAX_ENTITIES   (64 * 1024)
#define ECS_MAX_ARCHETYPES 1024

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

typedef struct {
    Archetype **matching;
    u32         match_count;
    u32         match_cap;
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
QueryIter  query_begin(Query *q);
bool       query_next(QueryIter *it);
void       query_done(Query *q);

void *chunk_get_component(Chunk *c, u32 index, u32 component_offset);
Entity chunk_get_entity(Chunk *c, u32 index, u32 entity_offset);
