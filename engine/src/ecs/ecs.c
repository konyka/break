#include <ecs/ecs.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>

static Archetype *find_archetype(World *w, const ComponentType *types, u32 count) {
    for (u32 i = 0; i < w->archetype_count; i++) {
        Archetype *a = &w->archetypes[i];
        if (a->key.count != count) continue;
        bool match = true;
        for (u32 j = 0; j < count; j++) {
            if (a->key.ids[j] != types[j]) { match = false; break; }
        }
        if (match) return a;
    }
    return NULL;
}

static i32 archetype_find_component(Archetype *a, ComponentType id) {
    for (u32 i = 0; i < a->key.count; i++) {
        if (a->key.ids[i] == id) return (i32)i;
    }
    return -1;
}

static Chunk *chunk_alloc(u32 chunk_size) {
    Chunk *c = calloc(1, chunk_size);
    c->next = NULL;
    c->count = 0;
    return c;
}

static Archetype *create_archetype(World *w, const ComponentType *types, u32 count) {
    if (w->archetype_count >= ECS_MAX_ARCHETYPES) {
        LOG_FATAL("ECS archetype limit reached");
        return NULL;
    }
    Archetype *a = &w->archetypes[w->archetype_count++];
    a->key.ids = calloc(count, sizeof(ComponentType));
    memcpy(a->key.ids, types, count * sizeof(ComponentType));
    a->key.count = count;
    a->chunks = NULL;
    a->chunk_tail = NULL;
    a->total_count = 0;
    a->edges_add = NULL;
    a->edges_add_count = 0;
    a->edges_remove = NULL;
    a->edges_remove_count = 0;

    u32 per_entity = sizeof(u32);
    for (u32 i = 0; i < count; i++) {
        per_entity += w->component_sizes[types[i]];
    }
    a->chunk_capacity = per_entity > 0 ? (ECS_CHUNK_SIZE - 64) / per_entity : 128;
    if (a->chunk_capacity == 0) a->chunk_capacity = 1;

    a->offsets = calloc(count, sizeof(u32));
    u32 offset = sizeof(Chunk) + sizeof(u32) * a->chunk_capacity;
    offset = (offset + 15u) & ~15u;
    a->entity_offset = sizeof(Chunk);
    for (u32 i = 0; i < count; i++) {
        a->offsets[i] = offset;
        offset += w->component_sizes[types[i]] * a->chunk_capacity;
    }

    return a;
}

World *world_create(void) {
    World *w = calloc(1, sizeof(World));
    w->entities = calloc(ECS_MAX_ENTITIES, sizeof(Entity));
    w->entity_archetype = calloc(ECS_MAX_ENTITIES, sizeof(u32));
    w->entity_index = calloc(ECS_MAX_ENTITIES, sizeof(u32));
    w->free_stack = calloc(ECS_MAX_ENTITIES, sizeof(u32));
    w->free_stack_top = 0;
    w->entity_count = 1;

    w->archetypes[0].key.ids = NULL;
    w->archetypes[0].key.count = 0;
    w->archetypes[0].chunks = NULL;
    w->archetypes[0].chunk_tail = NULL;
    w->archetypes[0].offsets = NULL;
    w->archetypes[0].chunk_capacity = 128;
    w->archetypes[0].entity_offset = sizeof(Chunk);
    w->archetypes[0].total_count = 0;
    w->archetype_count = 1;

    return w;
}

void world_destroy(World *w) {
    for (u32 i = 0; i < w->archetype_count; i++) {
        Archetype *a = &w->archetypes[i];
        Chunk *c = a->chunks;
        a->chunks = NULL;
        while (c) {
            Chunk *next = c->next;
            c->next = NULL;
            free(c);
            c = next;
        }
        free(a->key.ids);
        a->key.ids = NULL;
        free(a->offsets);
        a->offsets = NULL;
        free(a->edges_add);
        a->edges_add = NULL;
        free(a->edges_remove);
        a->edges_remove = NULL;
    }
    for (u32 i = 0; i < 256; i++) {
        free(w->queries[i].matching);
        w->queries[i].matching = NULL;
    }
    free(w->entities);
    free(w->entity_archetype);
    free(w->entity_index);
    free(w->free_stack);
    free(w);
}

void world_register_component(World *w, ComponentType id, u32 size) {
    if (id >= ECS_MAX_COMPONENTS) return;
    w->component_sizes[id] = size;
}

Entity world_create_entity(World *w) {
    u32 idx;
    if (w->free_stack_top > 0) {
        idx = w->free_stack[--w->free_stack_top];
        w->entities[idx].generation++;
        if (w->entities[idx].generation == 0) w->entities[idx].generation = 1;
    } else {
        if (w->entity_count >= ECS_MAX_ENTITIES) {
            LOG_FATAL("ECS entity limit reached");
            return ENTITY_NULL;
        }
        idx = w->entity_count++;
        w->entities[idx].index = idx;
        w->entities[idx].generation = 1;
    }

    w->entity_archetype[idx] = 0;
    w->entity_index[idx] = 0;

    Archetype *empty = &w->archetypes[0];
    if (!empty->chunks) {
        empty->chunks = chunk_alloc(ECS_CHUNK_SIZE);
        empty->chunks->capacity = empty->chunk_capacity;
        empty->chunk_tail = empty->chunks;
    }
    Chunk *c = empty->chunk_tail;
    if (c->count >= c->capacity) {
        Chunk *nc = chunk_alloc(ECS_CHUNK_SIZE);
        nc->capacity = empty->chunk_capacity;
        c->next = nc;
        empty->chunk_tail = nc;
        c = nc;
    }

    u32 ei = c->count++;
    u32 *entities = (u32 *)((u8 *)c + empty->entity_offset);
    entities[ei] = idx;
    w->entity_index[idx] = empty->total_count;
    empty->total_count++;

    return w->entities[idx];
}

void world_destroy_entity(World *w, Entity e) {
    if (e.index >= w->entity_count) return;
    if (w->entities[e.index].generation != e.generation) return;

    u32 arch_idx = w->entity_archetype[e.index];
    Archetype *a = &w->archetypes[arch_idx];

    Chunk *c = a->chunks;
    u32 chunk_offset = 0;
    while (c) {
        u32 *entities = (u32 *)((u8 *)c + a->entity_offset);
        for (u32 i = 0; i < c->count; i++) {
            if (entities[i] == e.index) {
                u32 last = c->count - 1;
                if (i != last) {
                    for (u32 ci = 0; ci < a->key.count; ci++) {
                        u8 *col = (u8 *)c + a->offsets[ci];
                        u32 sz = w->component_sizes[a->key.ids[ci]];
                        memcpy(col + i * sz, col + last * sz, sz);
                    }
                    entities[i] = entities[last];
                    w->entity_index[entities[i]] = chunk_offset + i;
                }
                c->count--;
                a->total_count--;
                goto done;
            }
        }
        chunk_offset += c->count;
        c = c->next;
    }
done:
    w->free_stack[w->free_stack_top++] = e.index;
    w->entities[e.index].generation++;
}

static void *archetype_alloc_slot(World *w, Archetype *a, u32 *out_global_index) {
    (void)w;
    if (!a->chunks) {
        a->chunks = chunk_alloc(ECS_CHUNK_SIZE);
        a->chunks->capacity = a->chunk_capacity;
        a->chunk_tail = a->chunks;
    }
    Chunk *c = a->chunk_tail;
    if (c->count >= c->capacity) {
        Chunk *nc = chunk_alloc(ECS_CHUNK_SIZE);
        nc->capacity = a->chunk_capacity;
        c->next = nc;
        a->chunk_tail = nc;
        c = nc;
    }
    *out_global_index = a->total_count;
    c->count++;
    a->total_count++;
    return c;
}

void *world_add_component(World *w, Entity e, ComponentType id) {
    if (e.index >= w->entity_count) return NULL;
    if (w->entities[e.index].generation != e.generation) return NULL;

    u32 arch_idx = w->entity_archetype[e.index];
    Archetype *old = &w->archetypes[arch_idx];

    i32 existing = archetype_find_component(old, id);
    if (existing >= 0) {
        u32 global_ei = w->entity_index[e.index];
        Chunk *c = old->chunks;
        u32 coffset = 0;
        while (c) {
            if (coffset + c->count > global_ei) {
                u32 local = global_ei - coffset;
                return (u8 *)c + old->offsets[existing] + w->component_sizes[id] * local;
            }
            coffset += c->count;
            c = c->next;
        }
        return NULL;
    }

    u32 new_count = old->key.count + 1;
    ComponentType *new_types = calloc(new_count, sizeof(ComponentType));
    if (old->key.count > 0 && old->key.ids) {
        memcpy(new_types, old->key.ids, old->key.count * sizeof(ComponentType));
    }
    new_types[old->key.count] = id;
    for (u32 i = old->key.count; i > 0 && new_types[i] < new_types[i-1]; i--) {
        ComponentType tmp = new_types[i];
        new_types[i] = new_types[i-1];
        new_types[i-1] = tmp;
    }

    Archetype *dest = find_archetype(w, new_types, new_count);
    if (!dest) {
        dest = create_archetype(w, new_types, new_count);
    }
    free(new_types);

    u32 old_slot = w->entity_index[e.index];
    Chunk *old_chunk = old->chunks;
    u32 chunk_offset = 0;
    while (old_chunk) {
        if (chunk_offset + old_chunk->count > old_slot) break;
        chunk_offset += old_chunk->count;
        old_chunk = old_chunk->next;
    }

    u32 local_old = old_slot - chunk_offset;

    if (!old_chunk) return NULL;

    u8 old_data[4096];
    for (u32 ci = 0; ci < old->key.count; ci++) {
        u8 *col = (u8 *)old_chunk + old->offsets[ci];
        u32 sz = w->component_sizes[old->key.ids[ci]];
        if (ci * sz + sz <= sizeof(old_data)) {
            memcpy(old_data + old->offsets[ci], col + local_old * sz, sz);
        }
    }

    u32 new_global_slot;
    Chunk *new_chunk = archetype_alloc_slot(w, dest, &new_global_slot);
    u32 local_new = new_chunk->count - 1;
    u32 *entities = (u32 *)((u8 *)new_chunk + dest->entity_offset);
    entities[local_new] = e.index;

    for (u32 ci = 0; ci < old->key.count; ci++) {
        i32 di = archetype_find_component(dest, old->key.ids[ci]);
        if (di >= 0) {
            u8 *dst = (u8 *)new_chunk + dest->offsets[di];
            u32 sz = w->component_sizes[old->key.ids[ci]];
            memcpy(dst + local_new * sz, old_data + old->offsets[ci], sz);
        }
    }

    if (old_chunk && old_chunk->count > 0) {
        u32 last = old_chunk->count - 1;
        if (local_old < last) {
            for (u32 ci = 0; ci < old->key.count; ci++) {
                u8 *col = (u8 *)old_chunk + old->offsets[ci];
                u32 sz = w->component_sizes[old->key.ids[ci]];
                memcpy(col + local_old * sz, col + last * sz, sz);
            }
            u32 *old_entities = (u32 *)((u8 *)old_chunk + old->entity_offset);
            old_entities[local_old] = old_entities[last];
            w->entity_index[old_entities[local_old]] = chunk_offset + local_old;
        }
        old_chunk->count--;
        old->total_count--;
    }

    w->entity_archetype[e.index] = (u32)(dest - w->archetypes);
    w->entity_index[e.index] = new_global_slot;

    i32 new_comp_idx = archetype_find_component(dest, id);
    if (new_comp_idx < 0) return NULL;
    u32 sz = w->component_sizes[id];
    return (u8 *)new_chunk + dest->offsets[new_comp_idx] + local_new * sz;
}

void *world_get_component(World *w, Entity e, ComponentType id) {
    if (e.index >= w->entity_count) return NULL;
    if (w->entities[e.index].generation != e.generation) return NULL;

    u32 arch_idx = w->entity_archetype[e.index];
    Archetype *a = &w->archetypes[arch_idx];
    i32 ci = archetype_find_component(a, id);
    if (ci < 0) return NULL;

    u32 ei = w->entity_index[e.index];
    Chunk *c = a->chunks;
    while (c) {
        if (ei < c->count) {
            return (u8 *)c + a->offsets[ci] + w->component_sizes[id] * ei;
        }
        ei -= c->count;
        c = c->next;
    }
    return NULL;
}

void world_remove_component(World *w, Entity e, ComponentType id) {
    (void)w; (void)e; (void)id;
}

void *chunk_get_component(Chunk *c, u32 index, u32 component_offset) {
    return (u8 *)c + component_offset + index;
}

Entity chunk_get_entity(Chunk *c, u32 index, u32 entity_offset) {
    u32 *entities = (u32 *)((u8 *)c + entity_offset);
    (void)index;
    Entity e = {entities[0], 0};
    return e;
}

Query *world_query(World *w, const ComponentType *types, u32 count) {
    Query *q = &w->queries[0];
    if (q->matching) { free(q->matching); q->matching = NULL; }
    q->match_count = 0;
    q->match_cap = 64;
    q->matching = calloc(q->match_cap, sizeof(Archetype *));

    for (u32 i = 0; i < w->archetype_count; i++) {
        Archetype *a = &w->archetypes[i];
        bool match = true;
        for (u32 j = 0; j < count; j++) {
            if (archetype_find_component(a, types[j]) < 0) {
                match = false;
                break;
            }
        }
        if (match && a->total_count > 0) {
            if (q->match_count >= q->match_cap) {
                q->match_cap *= 2;
                q->matching = realloc(q->matching, q->match_cap * sizeof(Archetype *));
            }
            q->matching[q->match_count++] = a;
        }
    }
    return q;
}

bool query_next(QueryIter *it) {
    if (!it->query || it->arch_index >= it->query->match_count) return false;

    while (it->arch_index < it->query->match_count) {
        if (!it->chunk) {
            it->arch_index++;
            if (it->arch_index >= it->query->match_count) return false;
            it->chunk = it->query->matching[it->arch_index]->chunks;
            it->index = 0;
        }
        if (it->chunk && it->index < it->chunk->count) {
            it->index++;
            return true;
        }
        if (it->chunk) {
            it->chunk = it->chunk->next;
            it->index = 0;
        }
    }
    return false;
}

void query_done(Query *q) {
    if (q) {
        free(q->matching);
        q->matching = NULL;
        q->match_count = 0;
        q->match_cap = 0;
    }
}

QueryIter query_begin(Query *q) {
    QueryIter it = {0};
    it.query = q;
    it.arch_index = 0;
    it.chunk = (q && q->match_count > 0) ? q->matching[0]->chunks : NULL;
    it.index = 0;
    return it;
}
