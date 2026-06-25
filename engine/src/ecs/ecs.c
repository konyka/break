#include <ecs/ecs.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>

/* FNV1a hash of sorted component type IDs for archetype early-reject */
static u32 archetype_key_hash(const ComponentType *types, u32 count) {
    u32 h = 2166136261u;
    for (u32 i = 0; i < count; i++) {
        h ^= types[i];
        h *= 16777619u;
    }
    return h;
}

static Archetype *find_archetype(World *w, const ComponentType *types, u32 count) {
    u32 target_hash = archetype_key_hash(types, count);
    for (u32 i = 0; i < w->archetype_count; i++) {
        if (w->archetype_hash[i] != target_hash) continue;  /* fast early-reject */
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

/* R102: Archetype edge cache — O(1) transition lookup for add/remove.
 * Each archetype stores a small array of (component_id → target_archetype*)
 * edges.  The first add/remove of a given component from a given archetype
 * pays the O(N) find_archetype cost; subsequent transitions with the same
 * component are O(E) where E is edges per archetype (typically ≤ component
 * type count, almost always single-digit). */

static Archetype *edge_lookup_add(Archetype *a, ComponentType id) {
    for (u32 i = 0; i < a->edges_add_count; i++) {
        if (a->edges_add[i].component == id) return a->edges_add[i].target;
    }
    return NULL;
}

static Archetype *edge_lookup_remove(Archetype *a, ComponentType id) {
    for (u32 i = 0; i < a->edges_remove_count; i++) {
        if (a->edges_remove[i].component == id) return a->edges_remove[i].target;
    }
    return NULL;
}

static void edge_cache_add(Archetype *a, ComponentType id, Archetype *target) {
    for (u32 i = 0; i < a->edges_add_count; i++) {
        if (a->edges_add[i].component == id) {
            a->edges_add[i].target = target;
            return;
        }
    }
    ArchetypeEdge *new_arr = realloc(a->edges_add,
                                     (a->edges_add_count + 1) * sizeof(ArchetypeEdge));
    if (!new_arr) return;
    a->edges_add = new_arr;
    a->edges_add[a->edges_add_count].component = id;
    a->edges_add[a->edges_add_count].target    = target;
    a->edges_add_count++;
}

static void edge_cache_remove(Archetype *a, ComponentType id, Archetype *target) {
    for (u32 i = 0; i < a->edges_remove_count; i++) {
        if (a->edges_remove[i].component == id) {
            a->edges_remove[i].target = target;
            return;
        }
    }
    ArchetypeEdge *new_arr = realloc(a->edges_remove,
                                     (a->edges_remove_count + 1) * sizeof(ArchetypeEdge));
    if (!new_arr) return;
    a->edges_remove = new_arr;
    a->edges_remove[a->edges_remove_count].component = id;
    a->edges_remove[a->edges_remove_count].target    = target;
    a->edges_remove_count++;
}

static Chunk *chunk_alloc(u32 chunk_size) {
    Chunk *c = calloc(1, chunk_size);
    if (!c) return NULL;
    c->next = NULL;
    c->count = 0;
    return c;
}

static Archetype *create_archetype(World *w, const ComponentType *types, u32 count) {
    if (w->archetype_count >= ECS_MAX_ARCHETYPES) {
        LOG_FATAL("ECS archetype limit reached");
        return NULL;
    }
    u32 idx = w->archetype_count++;
    Archetype *a = &w->archetypes[idx];
    /* Single alloc: key.ids (ComponentType[]) + offsets (u32[]) */
    u32 *arch_buf = (u32 *)calloc(count * 2, sizeof(u32));
    if (!arch_buf) { w->archetype_count--; return NULL; }
    a->key.ids = arch_buf;
    memcpy(a->key.ids, types, count * sizeof(ComponentType));
    a->key.count = count;
    a->chunks = NULL;
    a->chunk_tail = NULL;
    a->total_count = 0;
    a->edges_add = NULL;
    a->edges_add_count = 0;
    a->edges_remove = NULL;
    a->edges_remove_count = 0;
    w->archetype_hash[idx] = archetype_key_hash(types, count);

    u32 per_entity = sizeof(u32);
    for (u32 i = 0; i < count; i++) {
        per_entity += w->component_sizes[types[i]];
    }
    a->chunk_capacity = per_entity > 0 ? (ECS_CHUNK_SIZE - 64) / per_entity : 128;
    if (a->chunk_capacity == 0) a->chunk_capacity = 1;

    a->offsets = arch_buf + count;
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
    if (!w) return NULL;

    /* Single allocation for all per-entity arrays (saves 3 calloc calls).
     * Layout: [Entity entities | u32 archetype | u32 index | u32 free_stack] */
    usize ent_bytes  = (usize)ECS_MAX_ENTITIES * sizeof(Entity);
    usize arch_bytes = (usize)ECS_MAX_ENTITIES * sizeof(u32);
    usize idx_bytes  = (usize)ECS_MAX_ENTITIES * sizeof(u32);
    usize free_bytes = (usize)ECS_MAX_ENTITIES * sizeof(u32);
    u8 *block = (u8 *)calloc(1, ent_bytes + arch_bytes + idx_bytes + free_bytes);
    if (!block) { free(w); return NULL; }
    w->entities        = (Entity *)block;
    w->entity_archetype = (u32 *)(block + ent_bytes);
    w->entity_index     = (u32 *)(block + ent_bytes + arch_bytes);
    w->free_stack       = (u32 *)(block + ent_bytes + arch_bytes + idx_bytes);

    w->free_stack_top = 0;
    w->entity_count = 1;
    w->query_next_slot = 0;
    w->cache_version = 1;

    /* Initialize query cache to empty */
    for (u32 i = 0; i < ECS_QUERY_CACHE_SIZE; i++) {
        w->query_cache[i] = 0xFFFFFFFF;
    }

    w->archetypes[0].key.ids = NULL;
    w->archetypes[0].key.count = 0;
    w->archetypes[0].chunks = NULL;
    w->archetypes[0].chunk_tail = NULL;
    w->archetypes[0].offsets = NULL;
    w->archetypes[0].chunk_capacity = 128;
    w->archetypes[0].entity_offset = sizeof(Chunk);
    w->archetypes[0].total_count = 0;
    w->archetype_hash[0] = archetype_key_hash(NULL, 0);
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
        free(a->key.ids); /* single alloc: key.ids + offsets */
        a->key.ids = NULL;
        a->offsets = NULL;
        free(a->edges_add);
        a->edges_add = NULL;
        free(a->edges_remove);
        a->edges_remove = NULL;
    }
    for (u32 i = 0; i < 256; i++) {
        if (w->queries[i].match_cap > ECS_QUERY_INLINE_CAP) {
            free(w->queries[i].matching);
        }
        w->queries[i].matching = NULL;
    }
    /* Single free for all per-entity arrays (allocated as one block) */
    free(w->entities);
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

    /* Update entity bitmap */
    w->entity_bitmap[idx / 64] |= (u64)1 << (idx % 64);
    /* Invalidate query cache on structural change */
    w->cache_version++;

    Archetype *empty = &w->archetypes[0];
    if (!empty->chunks) {
        empty->chunks = chunk_alloc(ECS_CHUNK_SIZE);
        if (!empty->chunks) return ENTITY_NULL;
        empty->chunks->capacity = empty->chunk_capacity;
        empty->chunk_tail = empty->chunks;
    }
    Chunk *c = empty->chunk_tail;
    if (c->count >= c->capacity) {
        Chunk *nc = chunk_alloc(ECS_CHUNK_SIZE);
        if (!nc) return ENTITY_NULL;
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

    /* Use entity_index (global slot) to skip directly to the right chunk
     * instead of linearly scanning all entities in all chunks. */
    u32 global_idx = w->entity_index[e.index];
    Chunk *c = a->chunks;
    u32 chunk_offset = 0;
    while (c) {
        if (global_idx < chunk_offset + c->count) {
            u32 i = global_idx - chunk_offset;
            u32 last = c->count - 1;
            u32 *entities = (u32 *)((u8 *)c + a->entity_offset);
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
        chunk_offset += c->count;
        c = c->next;
    }
done:
    w->free_stack[w->free_stack_top++] = e.index;
    w->entities[e.index].generation++;
    /* Clear entity bitmap */
    w->entity_bitmap[e.index / 64] &= ~((u64)1 << (e.index % 64));
    /* Invalidate query cache on structural change */
    w->cache_version++;
}

static void *archetype_alloc_slot(World *w, Archetype *a, u32 *out_global_index) {
    (void)w;
    if (!a->chunks) {
        a->chunks = chunk_alloc(ECS_CHUNK_SIZE);
        if (!a->chunks) return NULL;
        a->chunks->capacity = a->chunk_capacity;
        a->chunk_tail = a->chunks;
    }
    Chunk *c = a->chunk_tail;
    if (c->count >= c->capacity) {
        Chunk *nc = chunk_alloc(ECS_CHUNK_SIZE);
        if (!nc) return NULL;
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

    /* R102: Edge cache — try O(1) lookup before O(N) find_archetype */
    Archetype *dest = edge_lookup_add(old, id);
    if (!dest) {
        u32 new_count = old->key.count + 1;
        /* Stack buffer to avoid heap alloc for typical component counts (<16) */
        ComponentType stack_types[16];
        ComponentType *new_types = (new_count <= 16) ? stack_types
            : (ComponentType *)calloc(new_count, sizeof(ComponentType));
        if (!new_types) return NULL;
        if (old->key.count > 0 && old->key.ids) {
            memcpy(new_types, old->key.ids, old->key.count * sizeof(ComponentType));
        }
        new_types[old->key.count] = id;
        for (u32 i = old->key.count; i > 0 && new_types[i] < new_types[i-1]; i--) {
            ComponentType tmp = new_types[i];
            new_types[i] = new_types[i-1];
            new_types[i-1] = tmp;
        }

        dest = find_archetype(w, new_types, new_count);
        if (!dest) {
            dest = create_archetype(w, new_types, new_count);
        }
        if (new_types != stack_types) free(new_types);

        edge_cache_add(old, id, dest);
    }

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

    /* 使用紧凑排列的临时缓冲区，避免使用 chunk 偏移量造成栈溢出。
       chunk 内偏移量包含 chunk 头部、entity 索引数组以及前面所有列
       的容量，可能远超 4096 字节，无法直接作为临时缓冲区的写入位置。 */
    u32 total_size = 0;
    for (u32 ci = 0; ci < old->key.count; ci++) {
        total_size += w->component_sizes[old->key.ids[ci]];
    }

    u8 stack_buf[4096];
    u8 *old_data = stack_buf;
    if (total_size > sizeof(stack_buf)) {
        old_data = (u8 *)malloc(total_size);
        if (!old_data) return NULL;
    }

    u32 compact_offset = 0;
    for (u32 ci = 0; ci < old->key.count; ci++) {
        u8 *col = (u8 *)old_chunk + old->offsets[ci];
        u32 sz = w->component_sizes[old->key.ids[ci]];
        memcpy(old_data + compact_offset, col + local_old * sz, sz);
        compact_offset += sz;
    }

    u32 new_global_slot;
    Chunk *new_chunk = archetype_alloc_slot(w, dest, &new_global_slot);
    if (!new_chunk) { if (old_data != stack_buf) free(old_data); return NULL; }
    u32 local_new = new_chunk->count - 1;
    u32 *entities = (u32 *)((u8 *)new_chunk + dest->entity_offset);
    entities[local_new] = e.index;

    compact_offset = 0;
    for (u32 ci = 0; ci < old->key.count; ci++) {
        u32 sz = w->component_sizes[old->key.ids[ci]];
        i32 di = archetype_find_component(dest, old->key.ids[ci]);
        if (di >= 0) {
            u8 *dst = (u8 *)new_chunk + dest->offsets[di];
            memcpy(dst + local_new * sz, old_data + compact_offset, sz);
        }
        compact_offset += sz;
    }

    if (old_data != stack_buf) {
        free(old_data);
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
    /* Invalidate query cache - archetype membership changed */
    w->cache_version++;

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
    if (e.index >= w->entity_count) return;
    if (w->entities[e.index].generation != e.generation) return;

    u32 arch_idx = w->entity_archetype[e.index];
    Archetype *old = &w->archetypes[arch_idx];

    i32 removed = archetype_find_component(old, id);
    if (removed < 0) return;

    /* R102: Edge cache — try O(1) lookup before O(N) find_archetype */
    Archetype *dest = edge_lookup_remove(old, id);
    if (!dest) {
        u32 new_count = old->key.count - 1;
        if (new_count == 0) {
            dest = &w->archetypes[0];
        } else {
            /* Stack buffer to avoid heap alloc for typical component counts (<16) */
            ComponentType stack_types[16];
            ComponentType *new_types = (new_count <= 16) ? stack_types
                : (ComponentType *)calloc(new_count, sizeof(ComponentType));
            if (!new_types) return;
            u32 j = 0;
            for (u32 i = 0; i < old->key.count; i++) {
                if ((i32)i == removed) continue;
                new_types[j++] = old->key.ids[i];
            }
            dest = find_archetype(w, new_types, new_count);
            if (!dest) {
                dest = create_archetype(w, new_types, new_count);
                /* archetypes 数组是固定大小的内联存储，create_archetype 不会使旧
                   指针失效，但保险起见重新解算 old 指针。 */
                old = &w->archetypes[arch_idx];
            }
            if (new_types != stack_types) free(new_types);
            if (!dest) return;
        }
        edge_cache_remove(old, id, dest);
    }

    u32 old_slot = w->entity_index[e.index];
    Chunk *old_chunk = old->chunks;
    u32 chunk_offset = 0;
    while (old_chunk) {
        if (chunk_offset + old_chunk->count > old_slot) break;
        chunk_offset += old_chunk->count;
        old_chunk = old_chunk->next;
    }
    if (!old_chunk) return;

    u32 local_old = old_slot - chunk_offset;

    /* 使用紧凑排列的临时缓冲区，仅保存除被移除组件外的列数据，
       与 world_add_component 对应的镜像处理。 */
    u32 total_size = 0;
    for (u32 ci = 0; ci < old->key.count; ci++) {
        if ((i32)ci == removed) continue;
        total_size += w->component_sizes[old->key.ids[ci]];
    }

    u8 stack_buf[4096];
    u8 *old_data = stack_buf;
    if (total_size > sizeof(stack_buf)) {
        old_data = (u8 *)malloc(total_size);
        if (!old_data) return;
    }

    u32 compact_offset = 0;
    for (u32 ci = 0; ci < old->key.count; ci++) {
        if ((i32)ci == removed) continue;
        u8 *col = (u8 *)old_chunk + old->offsets[ci];
        u32 sz = w->component_sizes[old->key.ids[ci]];
        memcpy(old_data + compact_offset, col + local_old * sz, sz);
        compact_offset += sz;
    }

    u32 new_global_slot;
    Chunk *new_chunk = archetype_alloc_slot(w, dest, &new_global_slot);
    if (!new_chunk) { if (old_data != stack_buf) free(old_data); return; }
    u32 local_new = new_chunk->count - 1;
    u32 *entities = (u32 *)((u8 *)new_chunk + dest->entity_offset);
    entities[local_new] = e.index;

    compact_offset = 0;
    for (u32 ci = 0; ci < old->key.count; ci++) {
        if ((i32)ci == removed) continue;
        u32 sz = w->component_sizes[old->key.ids[ci]];
        i32 di = archetype_find_component(dest, old->key.ids[ci]);
        if (di >= 0) {
            u8 *dst = (u8 *)new_chunk + dest->offsets[di];
            memcpy(dst + local_new * sz, old_data + compact_offset, sz);
        }
        compact_offset += sz;
    }

    if (old_data != stack_buf) {
        free(old_data);
    }

    /* swap-remove：把旧 chunk 的最后一行搬到被移除位置以填补空洞 */
    if (old_chunk->count > 0) {
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
    /* Invalidate query cache - archetype membership changed */
    w->cache_version++;
}

void *chunk_get_component(Chunk *c, u32 index, u32 component_offset, u32 component_size) {
    return (u8 *)c + component_offset + index * component_size;
}

Entity chunk_get_entity(Chunk *c, u32 index, u32 entity_offset) {
    u32 *entities = (u32 *)((u8 *)c + entity_offset);
    Entity e = {entities[index], 0};
    return e;
}

/* Build component bitmask for a given archetype (covers component IDs 0-63) */
static u64 archetype_component_mask(Archetype *a) {
    u64 mask = 0;
    for (u32 i = 0; i < a->key.count; i++) {
        if (a->key.ids[i] < 64) {
            mask |= (u64)1 << a->key.ids[i];
        }
    }
    return mask;
}

Query *world_query(World *w, const ComponentType *types, u32 count) {
    u32 slot = w->query_next_slot;
    w->query_next_slot = (w->query_next_slot + 1) % 256;
    Query *q = &w->queries[slot];
    /* Free heap-allocated matching (from previous use with >64 results) */
    if (q->match_cap > ECS_QUERY_INLINE_CAP) { free(q->matching); }
    q->match_count = 0;
    q->match_cap = ECS_QUERY_INLINE_CAP;
    q->matching = q->_inline_matching;
    q->exclude_mask = 0;
    q->optional_mask = 0;
    q->cached = false;

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
                u32 new_cap = q->match_cap * 2;
                Archetype **new_buf;
                if (q->match_cap <= ECS_QUERY_INLINE_CAP) {
                    /* Transition from inline to heap */
                    new_buf = (Archetype **)malloc(new_cap * sizeof(Archetype *));
                    if (!new_buf) break;
                    memcpy(new_buf, q->matching, q->match_count * sizeof(Archetype *));
                } else {
                    new_buf = (Archetype **)realloc(q->matching, new_cap * sizeof(Archetype *));
                    if (!new_buf) break;
                }
                q->matching = new_buf;
                q->match_cap = new_cap;
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
        if (q->match_cap > ECS_QUERY_INLINE_CAP) {
            free(q->matching);
        }
        q->matching = q->_inline_matching;
        q->match_count = 0;
        q->match_cap = ECS_QUERY_INLINE_CAP;
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

/* ---- Query Cache ---- */

static u32 query_signature_hash(const ComponentType *types, u32 count) {
    /* FNV-1a hash of component type IDs */
    u32 hash = 2166136261u;
    for (u32 i = 0; i < count; i++) {
        hash ^= types[i];
        hash *= 16777619u;
    }
    return hash;
}

Query *world_query_cached(World *w, const ComponentType *types, u32 count) {
    if (!w || !types || count == 0) return NULL;

    u32 sig = query_signature_hash(types, count);
    u32 cache_slot = sig % ECS_QUERY_CACHE_SIZE;

    /* Check cache */
    u32 slot_idx = w->query_cache[cache_slot];
    if (slot_idx != 0xFFFFFFFF) {
        Query *q = &w->queries[slot_idx];
        /* Verify signature match (handle hash collisions) and version */
        if (q->cache_signature == sig && q->cached &&
            q->cache_version == w->cache_version) {
            return q; /* Cache hit */
        }
        /* Stale or collision - invalidate this cache entry */
        w->query_cache[cache_slot] = 0xFFFFFFFF;
    }

    /* Cache miss - perform full query */
    Query *q = world_query(w, types, count);
    q->cache_signature = sig;
    q->cache_version = w->cache_version;
    q->cached = true;

    /* Store in cache */
    u32 q_slot = (u32)(q - w->queries);
    w->query_cache[cache_slot] = q_slot;

    return q;
}

bool world_entity_exists(World *w, Entity e) {
    if (!w || e.index == 0 || e.index >= w->entity_count) return false;
    /* Fast bitmap check */
    if (!(w->entity_bitmap[e.index / 64] & ((u64)1 << (e.index % 64)))) return false;
    /* Verify generation */
    return w->entities[e.index].generation == e.generation;
}

void world_query_invalidate(World *w) {
    if (!w) return;
    w->cache_version++;
    /* Clear all cache entries */
    for (u32 i = 0; i < ECS_QUERY_CACHE_SIZE; i++) {
        w->query_cache[i] = 0xFFFFFFFF;
    }
}

/* ---- Exclude / Optional query helpers ---- */

void ecs_query_exclude(Query *q, ComponentType comp_id) {
    if (!q || comp_id >= 64) return;
    q->exclude_mask |= (u64)1 << comp_id;
}

void ecs_query_optional(Query *q, ComponentType comp_id) {
    if (!q || comp_id >= 64) return;
    q->optional_mask |= (u64)1 << comp_id;
}

void ecs_query_refresh(World *w, Query *q, const ComponentType *types, u32 count) {
    if (!w || !q) return;

    /* Save exclude/optional masks before resetting via world_query internals */
    u64 saved_exclude  = q->exclude_mask;
    u64 saved_optional = q->optional_mask;

    /* Free old heap buffer if present */
    if (q->match_cap > ECS_QUERY_INLINE_CAP) { free(q->matching); }
    q->match_count = 0;
    q->match_cap   = ECS_QUERY_INLINE_CAP;
    q->matching    = q->_inline_matching;
    q->exclude_mask  = saved_exclude;
    q->optional_mask = saved_optional;
    q->cached = false;

    for (u32 i = 0; i < w->archetype_count; i++) {
        Archetype *a = &w->archetypes[i];

        /* Must contain all required (non-optional) components */
        bool match = true;
        for (u32 j = 0; j < count; j++) {
            ComponentType cid = types[j];
            bool is_optional = (cid < 64) && (saved_optional & ((u64)1 << cid));
            if (!is_optional && archetype_find_component(a, cid) < 0) {
                match = false;
                break;
            }
        }
        if (!match) continue;

        /* Exclude: reject archetype if it has any excluded component */
        if (saved_exclude) {
            u64 arch_mask = archetype_component_mask(a);
            if (arch_mask & saved_exclude) continue;
        }

        if (a->total_count == 0) continue;

        if (q->match_count >= q->match_cap) {
            u32 new_cap = q->match_cap * 2;
            Archetype **new_buf;
            if (q->match_cap <= ECS_QUERY_INLINE_CAP) {
                new_buf = (Archetype **)malloc(new_cap * sizeof(Archetype *));
                if (!new_buf) break;
                memcpy(new_buf, q->matching, q->match_count * sizeof(Archetype *));
            } else {
                new_buf = (Archetype **)realloc(q->matching, new_cap * sizeof(Archetype *));
                if (!new_buf) break;
            }
            q->matching = new_buf;
            q->match_cap = new_cap;
        }
        q->matching[q->match_count++] = a;
    }
}
