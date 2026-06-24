/* Scene serialization (binary + JSON) + prefab support.
 *
 * Walks the ECS World and Scene structures, emits a chunked binary
 * file (BSCN) or a hand-rolled JSON document. The JSON parser only
 * needs to handle the format we produce.
 *
 * Pure C11, freestanding from third-party JSON libraries. */

#include <scene/scene_serial.h>
#include <core/log.h>

#include <math/math.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---------------------------------------------------------------- */
/* Dynamic byte buffer                                              */
/* ---------------------------------------------------------------- */

typedef struct {
    u8 *data;
    u32 size;
    u32 cap;
} ByteBuf;

static void bb_init(ByteBuf *b) { b->data = NULL; b->size = 0; b->cap = 0; }
static void bb_free(ByteBuf *b) { free(b->data); b->data = NULL; b->size = 0; b->cap = 0; }

static bool bb_reserve(ByteBuf *b, u32 extra) {
    if (b->size + extra <= b->cap) return true;
    u32 nc = b->cap ? b->cap : 256;
    while (nc < b->size + extra) nc *= 2;
    u8 *nd = (u8 *)realloc(b->data, nc);
    if (!nd) return false;
    b->data = nd;
    b->cap = nc;
    return true;
}

static bool bb_write(ByteBuf *b, const void *src, u32 n) {
    if (!bb_reserve(b, n)) return false;
    memcpy(b->data + b->size, src, n);
    b->size += n;
    return true;
}

static bool bb_u32(ByteBuf *b, u32 v) { return bb_write(b, &v, sizeof(v)); }

/* ---------------------------------------------------------------- */
/* Live-entity enumeration                                          */
/* ---------------------------------------------------------------- */

typedef struct {
    u32 *entity_to_saved;  /* world index -> saved index, UINT32_MAX if dead */
    u32 *saved_to_entity;  /* saved index -> world index */
    u32  count;            /* number of live entities */
} EntityMap;

static void emap_free(EntityMap *m) {
    /* Single free: saved_to_entity is within the same block as entity_to_saved */
    free(m->entity_to_saved);
    m->entity_to_saved = m->saved_to_entity = NULL;
    m->count = 0;
}

static bool emap_build(const World *w, EntityMap *m) {
    /* Single allocation: entity_to_saved[N] + saved_to_entity[N].
     * 2 mallocs + 1 calloc → 1 malloc, 2 free → 1 free. */
    u32 n = w->entity_count;
    u8 *block = (u8 *)malloc(sizeof(u32) * n * 2);
    if (!block) return false;
    m->entity_to_saved = (u32 *)block;
    m->saved_to_entity = (u32 *)(block + sizeof(u32) * n);

    for (u32 i = 0; i < n; i++) m->entity_to_saved[i] = UINT32_MAX;

    /* Temporarily borrow the first N bytes of saved_to_entity as an is_free
     * bitmap.  N bytes fit within the N*sizeof(u32) = 4N-byte region, so no
     * out-of-bounds access.  We zero the region first to match calloc. */
    memset(m->saved_to_entity, 0, n * sizeof(u32));
    u8 *is_free = (u8 *)m->saved_to_entity;
    for (u32 i = 0; i < w->free_stack_top; i++) {
        u32 idx = w->free_stack[i];
        if (idx < n) is_free[idx] = 1;
    }

    u32 saved = 0;
    for (u32 i = 1; i < n; i++) {
        if (is_free[i]) continue;
        m->entity_to_saved[i] = saved;
        /* Don't write saved_to_entity here: would clobber is_free[j] at j=4*saved */
        saved++;
    }
    m->count = saved;

    /* Clear the borrowed region, then build saved_to_entity from entity_to_saved */
    memset(m->saved_to_entity, 0, n * sizeof(u32));
    for (u32 i = 1; i < n; i++) {
        if (m->entity_to_saved[i] != UINT32_MAX)
            m->saved_to_entity[m->entity_to_saved[i]] = i;
    }
    return true;
}

/* Resolve the chunk + local row index for an entity. */
static const u8 *entity_component_ptr(const World *w, u32 entity_index,
                                      ComponentType type, u32 *out_size) {
    u32 ai = w->entity_archetype[entity_index];
    const Archetype *a = &w->archetypes[ai];
    i32 ci = -1;
    for (u32 k = 0; k < a->key.count; k++) {
        if (a->key.ids[k] == type) { ci = (i32)k; break; }
    }
    if (ci < 0) return NULL;

    u32 slot = w->entity_index[entity_index];
    Chunk *c = a->chunks;
    while (c && slot >= c->count) { slot -= c->count; c = c->next; }
    if (!c) return NULL;

    u32 sz = w->component_sizes[type];
    if (out_size) *out_size = sz;
    return (const u8 *)c + a->offsets[ci] + slot * sz;
}

/* ---------------------------------------------------------------- */
/* Binary save                                                      */
/* ---------------------------------------------------------------- */

static bool emit_entities_chunk(const World *w, const EntityMap *m, ByteBuf *out) {
    if (!bb_u32(out, m->count)) return false;
    for (u32 s = 0; s < m->count; s++) {
        u32 ei = m->saved_to_entity[s];
        u32 gen = w->entities[ei].generation;
        u32 ai = w->entity_archetype[ei];
        const Archetype *a = &w->archetypes[ai];
        if (!bb_u32(out, gen)) return false;
        if (!bb_u32(out, a->key.count)) return false;
        for (u32 k = 0; k < a->key.count; k++) {
            if (!bb_u32(out, a->key.ids[k])) return false;
        }
    }
    return true;
}

static bool emit_components_chunk(const World *w, const EntityMap *m, ByteBuf *out) {
    /* Count registered components first, then write per-type instance data. */
    u32 type_count = 0;
    for (u32 t = 0; t < ECS_MAX_COMPONENTS; t++) {
        if (w->component_sizes[t] > 0) type_count++;
    }
    if (!bb_u32(out, type_count)) return false;

    for (u32 t = 0; t < ECS_MAX_COMPONENTS; t++) {
        u32 sz = w->component_sizes[t];
        if (!sz) continue;

        /* Reserve header position; we patch instance_count later. */
        if (!bb_u32(out, t)) return false;
        if (!bb_u32(out, sz)) return false;
        u32 count_pos = out->size;
        if (!bb_u32(out, 0)) return false;

        u32 instances = 0;
        for (u32 s = 0; s < m->count; s++) {
            u32 ei = m->saved_to_entity[s];
            u32 src_size = 0;
            const u8 *p = entity_component_ptr(w, ei, t, &src_size);
            if (!p) continue;
            if (!bb_u32(out, s)) return false;
            if (!bb_write(out, p, src_size)) return false;
            instances++;
        }
        memcpy(out->data + count_pos, &instances, sizeof(u32));
    }
    return true;
}

static bool emit_scene_nodes_chunk(const Scene *s, ByteBuf *out) {
    u32 n = s ? s->node_count : 0;
    if (!bb_u32(out, n)) return false;
    for (u32 i = 0; i < n; i++) {
        const SceneNode *nd = &s->nodes[i];
        if (!bb_write(out, nd->local_transform.e, sizeof(nd->local_transform))) return false;
        if (!bb_write(out, nd->world_transform.e, sizeof(nd->world_transform))) return false;
        if (!bb_u32(out, nd->parent_index)) return false;
        if (!bb_u32(out, nd->mesh_index)) return false;
        if (!bb_u32(out, nd->material_idx)) return false;
        if (!bb_u32(out, nd->skin_mesh_index)) return false;
        u32 flags = (nd->has_mesh ? 1u : 0u) | (nd->skinned ? 2u : 0u);
        if (!bb_u32(out, flags)) return false;
    }
    return true;
}

static bool emit_hierarchy_chunk(const Scene *s, ByteBuf *out) {
    u32 n = s ? s->node_count : 0;
    if (!bb_u32(out, n)) return false;
    if (n == 0) return true;

    /* Build parent→children adjacency in O(N) using CSR-style layout.
     * Pass 1: count children per parent.
     * Pass 2: prefix-sum to get offsets.
     * Pass 3: fill children array. */
    /* Single allocation for all 4 arrays (Round 18). */
    u32 *child_count = (u32 *)calloc(4 * n + 1, sizeof(u32));
    if (!child_count) return false;
    u32 *offsets  = child_count + n;
    u32 *children = offsets + n + 1;
    u32 *cursor   = children + n;

    for (u32 j = 0; j < n; j++) {
        u32 p = s->nodes[j].parent_index;
        if (p != j && p < n) child_count[p]++;
    }
    /* Prefix sum */
    for (u32 i = 0; i < n; i++) offsets[i + 1] = offsets[i] + child_count[i];
    /* Fill children (cursor is already zeroed by calloc) */
    for (u32 j = 0; j < n; j++) {
        u32 p = s->nodes[j].parent_index;
        if (p != j && p < n) children[offsets[p] + cursor[p]++] = j;
    }

    for (u32 i = 0; i < n; i++) {
        if (!bb_u32(out, s->nodes[i].parent_index)) { free(child_count); return false; }
        u32 cc = child_count[i];
        if (!bb_u32(out, cc)) { free(child_count); return false; }
        for (u32 k = offsets[i]; k < offsets[i] + cc; k++) {
            if (!bb_u32(out, children[k])) { free(child_count); return false; }
        }
    }

    free(child_count);
    return true;
}

/* ---------------------------------------------------------------- */
/* Resource manifest                                                */
/* ---------------------------------------------------------------- */

static bool bb_u64(ByteBuf *b, u64 v) { return bb_write(b, &v, sizeof(v)); }
static bool bb_f32(ByteBuf *b, f32 v) { return bb_write(b, &v, sizeof(v)); }

/* FNV-1a 64-bit over an arbitrary byte range. */
static u64 fnv1a64(const void *data, u32 n, u64 seed) {
    const u8 *p = (const u8 *)data;
    u64 h = seed ? seed : 1469598103934665603ull;
    for (u32 i = 0; i < n; i++) { h ^= p[i]; h *= 1099511628211ull; }
    return h;
}

/* Stable GUID from a resource's identity fields. */
static u64 resource_guid(u32 type, u32 ref_index, const void *desc, u32 desc_size) {
    u64 h = fnv1a64(&type, sizeof(type), 0);
    h = fnv1a64(&ref_index, sizeof(ref_index), h);
    if (desc && desc_size) h = fnv1a64(desc, desc_size, h);
    return h;
}

static bool emit_one_resource(ByteBuf *out, const SceneResource *res, bool inline_desc) {
    if (!bb_u64(out, res->guid)) return false;
    if (!bb_u32(out, res->type)) return false;
    if (!bb_u32(out, res->ref_index)) return false;
    u32 flags = inline_desc ? 1u : 0u;
    if (!bb_u32(out, flags)) return false;
    if (inline_desc) {
        if (!bb_u32(out, res->u0) || !bb_u32(out, res->u1) || !bb_u32(out, res->u2))
            return false;
        for (u32 i = 0; i < 8; i++) if (!bb_f32(out, res->f[i])) return false;
    }
    u32 plen = 0;
    while (plen < sizeof(res->path) && res->path[plen] != '\0') plen++;
    if (!bb_u32(out, plen)) return false;
    if (plen && !bb_write(out, res->path, plen)) return false;
    return true;
}

/* Derive a resource manifest from a scene's meshes/materials/textures, writing
 * each entry to `out`. `include` inlines the descriptor payload (else path-only
 * reference). */
static bool emit_resources_chunk(const Scene *s, bool include, ByteBuf *out) {
    if (!s) return bb_u32(out, 0);

    /* Collect distinct texture handle indices referenced by materials. */
    u32 tex_handles[256];
    u32 tex_count = 0;
    for (u32 i = 0; i < s->material_count && tex_count < 256; i++) {
        const Material *mat = &s->materials[i];
        const RHITexture cand[4] = { mat->albedo, mat->metallic_roughness,
                                     mat->normal_map, mat->emissive };
        for (u32 c = 0; c < 4 && tex_count < 256; c++) {
            if (!rhi_handle_valid(cand[c])) continue;
            u32 hidx = cand[c].index;
            bool seen = false;
            for (u32 k = 0; k < tex_count; k++) if (tex_handles[k] == hidx) { seen = true; break; }
            if (!seen) tex_handles[tex_count++] = hidx;
        }
    }

    u32 total = s->mesh_count + s->material_count + tex_count;
    if (!bb_u32(out, total)) return false;

    /* Meshes */
    for (u32 i = 0; i < s->mesh_count; i++) {
        const Mesh *me = &s->meshes[i];
        SceneResource r;
        memset(&r, 0, sizeof(r));
        r.type = BSCN_RES_MESH;
        r.ref_index = i;
        r.u0 = me->index_count;
        r.u1 = me->vertex_count;
        r.u2 = me->material_idx;
        r.f[0] = me->aabb_min.e[0]; r.f[1] = me->aabb_min.e[1]; r.f[2] = me->aabb_min.e[2];
        r.f[3] = me->aabb_max.e[0]; r.f[4] = me->aabb_max.e[1]; r.f[5] = me->aabb_max.e[2];
        r.guid = resource_guid(r.type, r.ref_index, &r.u0, sizeof(u32) * 3 + sizeof(f32) * 8);
        if (!emit_one_resource(out, &r, include)) return false;
    }

    /* Materials */
    for (u32 i = 0; i < s->material_count; i++) {
        const Material *mat = &s->materials[i];
        SceneResource r;
        memset(&r, 0, sizeof(r));
        r.type = BSCN_RES_MATERIAL;
        r.ref_index = i;
        r.u0 = (u32)mat->alpha_mode;
        r.u1 = rhi_handle_valid(mat->albedo) ? 1u : 0u;
        r.f[0] = mat->base_color[0]; r.f[1] = mat->base_color[1];
        r.f[2] = mat->base_color[2]; r.f[3] = mat->base_color[3];
        r.f[4] = mat->metallic_factor; r.f[5] = mat->roughness_factor;
        r.f[6] = mat->emissive_strength; r.f[7] = mat->alpha_cutoff;
        r.guid = resource_guid(r.type, r.ref_index, &r.u0, sizeof(u32) * 3 + sizeof(f32) * 8);
        if (!emit_one_resource(out, &r, include)) return false;
    }

    /* Textures (referenced by handle identity) */
    for (u32 i = 0; i < tex_count; i++) {
        SceneResource r;
        memset(&r, 0, sizeof(r));
        r.type = BSCN_RES_TEXTURE;
        r.ref_index = tex_handles[i];
        r.guid = resource_guid(r.type, r.ref_index, NULL, 0);
        if (!emit_one_resource(out, &r, include)) return false;
    }
    return true;
}

bool scene_save_binary(const World *w, const Scene *s,
                       const char *path, const SerializeOptions *opts) {
    if (!w || !path) return false;
    bool include_res = (opts && opts->include_resources);

    EntityMap m = {0};
    if (!emap_build(w, &m)) return false;

    ByteBuf chunks[5];
    for (u32 i = 0; i < 5; i++) bb_init(&chunks[i]);

    bool ok =
        emit_entities_chunk(w, &m, &chunks[0]) &&
        emit_components_chunk(w, &m, &chunks[1]) &&
        emit_hierarchy_chunk(s, &chunks[2]) &&
        emit_resources_chunk(s, include_res, &chunks[3]) &&
        emit_scene_nodes_chunk(s, &chunks[4]);
    if (!ok) goto fail;

    static const u32 ctypes[5] = {
        BSCN_CHUNK_ENTITIES, BSCN_CHUNK_COMPONENTS, BSCN_CHUNK_HIERARCHY,
        BSCN_CHUNK_RESOURCES, BSCN_CHUNK_SCENE_NODES
    };

    FILE *fp = fopen(path, "wb");
    if (!fp) goto fail;

    BscnHeader h;
    h.magic = BSCN_MAGIC;
    h.version = BSCN_VERSION;
    h.chunk_count = 5;
    if (fwrite(&h, sizeof(h), 1, fp) != 1) { fclose(fp); goto fail; }

    u32 base = (u32)sizeof(BscnHeader) + 5u * (u32)sizeof(BscnChunkEntry);
    BscnChunkEntry table[5];
    u32 cursor = base;
    for (u32 i = 0; i < 5; i++) {
        table[i].type = ctypes[i];
        table[i].offset = cursor;
        table[i].size = chunks[i].size;
        cursor += chunks[i].size;
    }
    if (fwrite(table, sizeof(table), 1, fp) != 1) { fclose(fp); goto fail; }

    for (u32 i = 0; i < 5; i++) {
        if (chunks[i].size && fwrite(chunks[i].data, 1, chunks[i].size, fp) != chunks[i].size) {
            fclose(fp); goto fail;
        }
    }
    fclose(fp);

    for (u32 i = 0; i < 5; i++) bb_free(&chunks[i]);
    emap_free(&m);
    return true;

fail:
    for (u32 i = 0; i < 5; i++) bb_free(&chunks[i]);
    emap_free(&m);
    return false;
}

/* ---------------------------------------------------------------- */
/* Binary load                                                      */
/* ---------------------------------------------------------------- */

typedef struct {
    const u8 *p;
    const u8 *end;
} Reader;

static bool rd_bytes(Reader *r, void *dst, u32 n) {
    if ((u32)(r->end - r->p) < n) return false;
    memcpy(dst, r->p, n);
    r->p += n;
    return true;
}
static bool rd_u32(Reader *r, u32 *v) { return rd_bytes(r, v, sizeof(*v)); }
static bool rd_u64(Reader *r, u64 *v) { return rd_bytes(r, v, sizeof(*v)); }

void scene_resources_free(Scene *s) {
    if (!s) return;
    free(s->resources);
    s->resources = NULL;
    s->resource_count = 0;
}

static bool load_resources_chunk(Scene *s, Reader *r) {
    u32 n = 0;
    if (!rd_u32(r, &n)) return false;
    SceneResource *arr = NULL;
    if (s && n) {
        arr = (SceneResource *)calloc(n, sizeof(SceneResource));
        if (!arr) return false;
    }
    for (u32 i = 0; i < n; i++) {
        SceneResource tmp;
        memset(&tmp, 0, sizeof(tmp));
        u32 flags = 0;
        if (!rd_u64(r, &tmp.guid) || !rd_u32(r, &tmp.type) ||
            !rd_u32(r, &tmp.ref_index) || !rd_u32(r, &flags)) {
            free(arr); return false;
        }
        tmp.flags = flags;
        if (flags & 1u) {
            if (!rd_u32(r, &tmp.u0) || !rd_u32(r, &tmp.u1) || !rd_u32(r, &tmp.u2)) {
                free(arr); return false;
            }
            for (u32 k = 0; k < 8; k++) {
                if (!rd_bytes(r, &tmp.f[k], sizeof(f32))) { free(arr); return false; }
            }
        }
        u32 plen = 0;
        if (!rd_u32(r, &plen)) { free(arr); return false; }
        if (plen >= sizeof(tmp.path)) { /* clamp; read+truncate */
            u32 keep = (u32)sizeof(tmp.path) - 1u;
            if (!rd_bytes(r, tmp.path, keep)) { free(arr); return false; }
            r->p += (plen - keep);
            if (r->p > r->end) { free(arr); return false; }
        } else if (plen) {
            if (!rd_bytes(r, tmp.path, plen)) { free(arr); return false; }
        }
        if (arr) arr[i] = tmp;
    }
    if (s) {
        free(s->resources);
        s->resources = arr;
        s->resource_count = n;
    }
    return true;
}

static bool load_entities_chunk(World *w, Reader *r,
                                Entity **out_entities, u32 *out_count) {
    u32 n = 0;
    if (!rd_u32(r, &n)) return false;
    Entity *ents = (Entity *)calloc(n ? n : 1, sizeof(Entity));
    if (!ents) return false;

    for (u32 i = 0; i < n; i++) {
        u32 saved_gen = 0, comp_count = 0;
        if (!rd_u32(r, &saved_gen) || !rd_u32(r, &comp_count)) {
            free(ents); return false;
        }
        Entity e = world_create_entity(w);
        if (!entity_valid(e)) { free(ents); return false; }
        /* Restore the saved generation so (index, generation) identity — the
         * stable "unified ID" shared with the scene — round-trips intact. */
        if (saved_gen != 0) {
            w->entities[e.index].generation = saved_gen;
            e.generation = saved_gen;
        }
        ents[i] = e;
        for (u32 k = 0; k < comp_count; k++) {
            u32 type = 0;
            if (!rd_u32(r, &type)) { free(ents); return false; }
            if (type < ECS_MAX_COMPONENTS && w->component_sizes[type]) {
                world_add_component(w, e, type);
            }
        }
    }
    *out_entities = ents;
    *out_count = n;
    return true;
}

static bool load_components_chunk(World *w, Reader *r,
                                  const Entity *ents, u32 ent_count) {
    u32 type_count = 0;
    if (!rd_u32(r, &type_count)) return false;
    for (u32 t = 0; t < type_count; t++) {
        u32 type = 0, size = 0, instances = 0;
        if (!rd_u32(r, &type) || !rd_u32(r, &size) || !rd_u32(r, &instances)) return false;
        bool known = (type < ECS_MAX_COMPONENTS) && (w->component_sizes[type] == size);
        for (u32 i = 0; i < instances; i++) {
            u32 saved_idx = 0;
            if (!rd_u32(r, &saved_idx)) return false;
            if ((u32)(r->end - r->p) < size) return false;
            if (known && saved_idx < ent_count) {
                void *dst = world_get_component(w, ents[saved_idx], type);
                if (!dst) dst = world_add_component(w, ents[saved_idx], type);
                if (dst) memcpy(dst, r->p, size);
            }
            r->p += size;
        }
    }
    return true;
}

static bool load_scene_nodes_chunk(Scene *s, Reader *r) {
    u32 n = 0;
    if (!rd_u32(r, &n)) return false;
    if (!s) {
        /* skip the chunk */
        for (u32 i = 0; i < n; i++) {
            Mat4 tmp; u32 dummy;
            if (!rd_bytes(r, tmp.e, sizeof(tmp)) ||
                !rd_bytes(r, tmp.e, sizeof(tmp)) ||
                !rd_u32(r, &dummy) || !rd_u32(r, &dummy) ||
                !rd_u32(r, &dummy) || !rd_u32(r, &dummy) ||
                !rd_u32(r, &dummy)) return false;
        }
        return true;
    }
    SceneNode *nodes = (SceneNode *)calloc(n ? n : 1, sizeof(SceneNode));
    if (!nodes) return false;
    for (u32 i = 0; i < n; i++) {
        SceneNode *nd = &nodes[i];
        u32 flags = 0;
        if (!rd_bytes(r, nd->local_transform.e, sizeof(nd->local_transform)) ||
            !rd_bytes(r, nd->world_transform.e, sizeof(nd->world_transform)) ||
            !rd_u32(r, &nd->parent_index) ||
            !rd_u32(r, &nd->mesh_index) ||
            !rd_u32(r, &nd->material_idx) ||
            !rd_u32(r, &nd->skin_mesh_index) ||
            !rd_u32(r, &flags)) {
            free(nodes); return false;
        }
        nd->has_mesh = (flags & 1u) != 0;
        nd->skinned  = (flags & 2u) != 0;
    }
    free(s->nodes);
    s->nodes = nodes;
    s->node_count = n;
    return true;
}

bool scene_load_binary(World *w, Scene *s, const char *path) {
    if (!w || !path) return false;
    FILE *fp = fopen(path, "rb");
    if (!fp) return false;
    fseek(fp, 0, SEEK_END);
    long fsz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (fsz < (long)sizeof(BscnHeader)) { fclose(fp); return false; }

    u8 *buf = (u8 *)malloc((size_t)fsz);
    if (!buf) { fclose(fp); return false; }
    if (fread(buf, 1, (size_t)fsz, fp) != (size_t)fsz) { fclose(fp); free(buf); return false; }
    fclose(fp);

    BscnHeader h;
    memcpy(&h, buf, sizeof(h));
    if (h.magic != BSCN_MAGIC || h.version != BSCN_VERSION) { free(buf); return false; }

    u32 table_off = (u32)sizeof(BscnHeader);
    if (h.chunk_count > 64) { free(buf); return false; }
    /* R108-1: validate chunk table fits within file buffer */
    u64 table_end = (u64)table_off + (u64)h.chunk_count * (u64)sizeof(BscnChunkEntry);
    if (table_end > (u64)fsz) { free(buf); return false; }
    BscnChunkEntry *table = (BscnChunkEntry *)(buf + table_off);

    Entity *ents = NULL; u32 ent_count = 0;
    bool ok = true;

    /* First pass: ENTITIES (must precede COMPONENTS). */
    for (u32 i = 0; i < h.chunk_count && ok; i++) {
        if (table[i].type != BSCN_CHUNK_ENTITIES) continue;
        /* R108-1: validate chunk data bounds */
        u64 chunk_end = (u64)table[i].offset + (u64)table[i].size;
        if (chunk_end > (u64)fsz) { ok = false; break; }
        Reader r;
        r.p = buf + table[i].offset;
        r.end = r.p + table[i].size;
        ok = load_entities_chunk(w, &r, &ents, &ent_count);
    }
    /* Second pass: remaining chunks. */
    for (u32 i = 0; i < h.chunk_count && ok; i++) {
        /* R108-1: validate chunk data bounds */
        u64 chunk_end = (u64)table[i].offset + (u64)table[i].size;
        if (chunk_end > (u64)fsz) { ok = false; break; }
        Reader r;
        r.p = buf + table[i].offset;
        r.end = r.p + table[i].size;
        switch (table[i].type) {
        case BSCN_CHUNK_ENTITIES: break;
        case BSCN_CHUNK_COMPONENTS:
            ok = load_components_chunk(w, &r, ents, ent_count); break;
        case BSCN_CHUNK_SCENE_NODES:
            ok = load_scene_nodes_chunk(s, &r); break;
        case BSCN_CHUNK_RESOURCES:
            ok = load_resources_chunk(s, &r); break;
        case BSCN_CHUNK_HIERARCHY:
        default:
            /* Hierarchy is implicit in SceneNode.parent_index. Skip silently. */
            break;
        }
    }

    free(ents);
    free(buf);
    return ok;
}

/* ---------------------------------------------------------------- */
/* JSON output                                                      */
/* ---------------------------------------------------------------- */

static bool sb_putc(ByteBuf *b, char c) { return bb_write(b, &c, 1); }
static bool sb_puts(ByteBuf *b, const char *s) {
    return bb_write(b, s, (u32)strlen(s));
}
static bool sb_indent(ByteBuf *b, bool pretty, u32 depth) {
    if (!pretty) return true;
    if (!sb_putc(b, '\n')) return false;
    for (u32 i = 0; i < depth; i++) {
        if (!sb_puts(b, "  ")) return false;
    }
    return true;
}
static bool sb_u32_dec(ByteBuf *b, u32 v) {
    char tmp[16];
    int n = snprintf(tmp, sizeof(tmp), "%u", v);
    if (n <= 0) return false;
    return bb_write(b, tmp, (u32)n);
}
static bool sb_hex_bytes(ByteBuf *b, const u8 *p, u32 n) {
    static const char hex[] = "0123456789abcdef";
    if (!sb_putc(b, '"')) return false;
    for (u32 i = 0; i < n; i++) {
        char c[2] = { hex[p[i] >> 4], hex[p[i] & 0xF] };
        if (!bb_write(b, c, 2)) return false;
    }
    return sb_putc(b, '"');
}

bool scene_save_json(const World *w, const Scene *s,
                     const char *path, const SerializeOptions *opts) {
    if (!w || !path) return false;
    bool pretty = (opts && opts->pretty_json);

    EntityMap m = {0};
    if (!emap_build(w, &m)) return false;

    ByteBuf b; bb_init(&b);
    bool ok = sb_putc(&b, '{');
    ok = ok && sb_indent(&b, pretty, 1) && sb_puts(&b, "\"version\":") &&
         sb_u32_dec(&b, BSCN_VERSION) && sb_putc(&b, ',');
    ok = ok && sb_indent(&b, pretty, 1) && sb_puts(&b, "\"entities\":[");

    for (u32 si = 0; si < m.count && ok; si++) {
        u32 ei = m.saved_to_entity[si];
        u32 ai = w->entity_archetype[ei];
        const Archetype *a = &w->archetypes[ai];

        if (si) ok = ok && sb_putc(&b, ',');
        ok = ok && sb_indent(&b, pretty, 2) && sb_putc(&b, '{');
        ok = ok && sb_indent(&b, pretty, 3) && sb_puts(&b, "\"id\":") &&
             sb_u32_dec(&b, si) && sb_putc(&b, ',');
        ok = ok && sb_indent(&b, pretty, 3) && sb_puts(&b, "\"gen\":") &&
             sb_u32_dec(&b, w->entities[ei].generation) && sb_putc(&b, ',');
        ok = ok && sb_indent(&b, pretty, 3) && sb_puts(&b, "\"components\":[");

        for (u32 k = 0; k < a->key.count && ok; k++) {
            ComponentType t = a->key.ids[k];
            u32 sz = 0;
            const u8 *p = entity_component_ptr(w, ei, t, &sz);
            if (!p) continue;
            if (k) ok = ok && sb_putc(&b, ',');
            ok = ok && sb_indent(&b, pretty, 4) && sb_putc(&b, '{');
            ok = ok && sb_puts(&b, "\"type\":") && sb_u32_dec(&b, t) && sb_putc(&b, ',');
            ok = ok && sb_puts(&b, "\"size\":") && sb_u32_dec(&b, sz) && sb_putc(&b, ',');
            ok = ok && sb_puts(&b, "\"data\":") && sb_hex_bytes(&b, p, sz);
            ok = ok && sb_putc(&b, '}');
        }
        ok = ok && sb_indent(&b, pretty, 3) && sb_putc(&b, ']');
        ok = ok && sb_indent(&b, pretty, 2) && sb_putc(&b, '}');
    }
    ok = ok && sb_indent(&b, pretty, 1) && sb_putc(&b, ']');

    /* Scene nodes (optional) */
    if (s && s->node_count) {
        ok = ok && sb_putc(&b, ',');
        ok = ok && sb_indent(&b, pretty, 1) && sb_puts(&b, "\"nodes\":[");
        for (u32 i = 0; i < s->node_count && ok; i++) {
            const SceneNode *nd = &s->nodes[i];
            if (i) ok = ok && sb_putc(&b, ',');
            ok = ok && sb_indent(&b, pretty, 2) && sb_putc(&b, '{');
            ok = ok && sb_puts(&b, "\"parent\":") && sb_u32_dec(&b, nd->parent_index) && sb_putc(&b, ',');
            ok = ok && sb_puts(&b, "\"mesh\":") && sb_u32_dec(&b, nd->mesh_index) && sb_putc(&b, ',');
            ok = ok && sb_puts(&b, "\"flags\":") &&
                 sb_u32_dec(&b, (nd->has_mesh ? 1u : 0u) | (nd->skinned ? 2u : 0u)) && sb_putc(&b, ',');
            ok = ok && sb_puts(&b, "\"local\":") &&
                 sb_hex_bytes(&b, (const u8 *)nd->local_transform.e, sizeof(nd->local_transform));
            ok = ok && sb_putc(&b, '}');
        }
        ok = ok && sb_indent(&b, pretty, 1) && sb_putc(&b, ']');
    }

    ok = ok && sb_indent(&b, pretty, 0) && sb_putc(&b, '}');

    if (ok) {
        FILE *fp = fopen(path, "wb");
        if (!fp) ok = false;
        else {
            if (b.size && fwrite(b.data, 1, b.size, fp) != b.size) ok = false;
            fclose(fp);
        }
    }
    bb_free(&b);
    emap_free(&m);
    return ok;
}

/* ---------------------------------------------------------------- */
/* JSON parser (tailored for the format above)                      */
/* ---------------------------------------------------------------- */

typedef struct {
    const char *p;
    const char *end;
} JsonR;

static void js_skip_ws(JsonR *r) {
    while (r->p < r->end && isspace((unsigned char)*r->p)) r->p++;
}
static bool js_match(JsonR *r, char c) {
    js_skip_ws(r);
    if (r->p < r->end && *r->p == c) { r->p++; return true; }
    return false;
}
static bool js_peek(JsonR *r, char c) {
    js_skip_ws(r);
    return (r->p < r->end && *r->p == c);
}
static bool js_u32(JsonR *r, u32 *out) {
    js_skip_ws(r);
    if (r->p >= r->end || !isdigit((unsigned char)*r->p)) return false;
    u32 v = 0;
    while (r->p < r->end && isdigit((unsigned char)*r->p)) {
        v = v * 10u + (u32)(*r->p - '0');
        r->p++;
    }
    *out = v;
    return true;
}
static bool js_key(JsonR *r, const char *key) {
    js_skip_ws(r);
    if (r->p >= r->end || *r->p != '"') return false;
    const char *s = r->p + 1;
    const char *e = (const char *)memchr(s, '"', (size_t)(r->end - s));
    if (!e) return false;
    size_t kl = strlen(key);
    if ((size_t)(e - s) != kl || memcmp(s, key, kl) != 0) return false;
    r->p = e + 1;
    return js_match(r, ':');
}
static int hex_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}
/* Parse hex-encoded byte string "abcd..." into dst (returns bytes read). */
static bool js_hex(JsonR *r, u8 *dst, u32 expected) {
    if (!js_match(r, '"')) return false;
    for (u32 i = 0; i < expected; i++) {
        if (r->p + 2 > r->end) return false;
        int hi = hex_digit(r->p[0]);
        int lo = hex_digit(r->p[1]);
        if (hi < 0 || lo < 0) return false;
        dst[i] = (u8)((hi << 4) | lo);
        r->p += 2;
    }
    return js_match(r, '"');
}
static bool js_skip_value(JsonR *r);
static bool js_skip_string(JsonR *r) {
    if (!js_match(r, '"')) return false;
    while (r->p < r->end && *r->p != '"') {
        if (*r->p == '\\' && r->p + 1 < r->end) r->p += 2;
        else r->p++;
    }
    return js_match(r, '"');
}
static bool js_skip_value(JsonR *r) {
    js_skip_ws(r);
    if (r->p >= r->end) return false;
    char c = *r->p;
    if (c == '"') return js_skip_string(r);
    if (c == '{' || c == '[') {
        char close_c = (c == '{') ? '}' : ']';
        r->p++;
        int depth = 1;
        while (r->p < r->end && depth > 0) {
            js_skip_ws(r);
            if (r->p >= r->end) return false;
            char k = *r->p;
            if (k == '"') { if (!js_skip_string(r)) return false; continue; }
            if (k == '{' || k == '[') { depth++; r->p++; continue; }
            if (k == '}' || k == ']') { depth--; r->p++; continue; }
            r->p++;
        }
        (void)close_c;
        return depth == 0;
    }
    /* number / true / false / null */
    while (r->p < r->end && *r->p != ',' && *r->p != '}' && *r->p != ']' &&
           !isspace((unsigned char)*r->p)) r->p++;
    return true;
}

static bool json_load_components(World *w, JsonR *r, Entity ent) {
    if (!js_match(r, '[')) return false;
    if (js_match(r, ']')) return true;
    do {
        if (!js_match(r, '{')) return false;
        u32 type = 0, size = 0;
        bool got_data = false;
        u8 stack_buf[1024];
        u8 *data = stack_buf;
        u32 data_size = 0;
        while (!js_peek(r, '}')) {
            js_skip_ws(r);
            if (js_key(r, "type")) { if (!js_u32(r, &type)) goto fail; }
            else if (js_key(r, "size")) { if (!js_u32(r, &size)) goto fail; }
            else if (js_key(r, "data")) {
                data_size = size;
                if (size > sizeof(stack_buf)) {
                    data = (u8 *)malloc(size);
                    if (!data) goto fail;
                }
                if (!js_hex(r, data, size)) goto fail;
                got_data = true;
            } else {
                /* unknown key — skip key+value */
                if (!js_skip_string(r)) goto fail;
                if (!js_match(r, ':')) goto fail;
                if (!js_skip_value(r)) goto fail;
            }
            (void)js_match(r, ',');
        }
        if (!js_match(r, '}')) goto fail;

        if (got_data && type < ECS_MAX_COMPONENTS &&
            w->component_sizes[type] == size) {
            void *dst = world_add_component(w, ent, type);
            if (dst) memcpy(dst, data, size);
        }
        if (data != stack_buf) free(data);
        data = stack_buf;
        data_size = 0;
        (void)data_size;
        continue;
    fail:
        if (data != stack_buf) free(data);
        return false;
    } while (js_match(r, ','));
    return js_match(r, ']');
}

bool scene_load_json(World *w, Scene *s, const char *path) {
    if (!w || !path) return false;
    FILE *fp = fopen(path, "rb");
    if (!fp) return false;
    fseek(fp, 0, SEEK_END);
    long fsz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (fsz <= 0) { fclose(fp); return false; }
    char *buf = (char *)malloc((size_t)fsz);
    if (!buf) { fclose(fp); return false; }
    if (fread(buf, 1, (size_t)fsz, fp) != (size_t)fsz) {
        fclose(fp); free(buf); return false;
    }
    fclose(fp);

    JsonR r;
    r.p = buf;
    r.end = buf + fsz;

    bool ok = js_match(&r, '{');
    while (ok && !js_peek(&r, '}')) {
        if (js_key(&r, "version")) {
            u32 v = 0;
            ok = js_u32(&r, &v) && (v == BSCN_VERSION);
        } else if (js_key(&r, "entities")) {
            ok = js_match(&r, '[');
            if (ok && !js_match(&r, ']')) {
                do {
                    if (!js_match(&r, '{')) { ok = false; break; }
                    Entity e = world_create_entity(w);
                    while (ok && !js_peek(&r, '}')) {
                        if (js_key(&r, "components")) {
                            ok = json_load_components(w, &r, e);
                        } else {
                            /* skip key:value */
                            if (!js_skip_string(&r) || !js_match(&r, ':') ||
                                !js_skip_value(&r)) { ok = false; break; }
                        }
                        (void)js_match(&r, ',');
                    }
                    if (!ok) break;
                    if (!js_match(&r, '}')) { ok = false; break; }
                } while (js_match(&r, ','));
                ok = ok && js_match(&r, ']');
            }
        } else if (js_key(&r, "nodes")) {
            if (!s) {
                /* skip nodes array if no Scene provided */
                ok = js_skip_value(&r);
            } else {
                ok = js_match(&r, '[');
                if (ok && !js_match(&r, ']')) {
                    u32 node_cap = 16;
                    SceneNode *nodes = (SceneNode *)calloc(node_cap, sizeof(SceneNode));
                    u32 node_count = 0;
                    if (!nodes) { ok = false; }
                    while (ok && !js_peek(&r, ']')) {
                        if (!js_match(&r, '{')) { ok = false; break; }
                        if (node_count >= node_cap) {
                            node_cap *= 2;
                            SceneNode *tmp = (SceneNode *)realloc(nodes, node_cap * sizeof(SceneNode));
                            if (!tmp) { ok = false; break; }
                            nodes = tmp;
                        }
                        SceneNode *nd = &nodes[node_count++];
                        memset(nd, 0, sizeof(*nd));
                        u32 flags = 0;
                        while (ok && !js_peek(&r, '}')) {
                            if (js_key(&r, "parent")) {
                                ok = js_u32(&r, &nd->parent_index);
                            } else if (js_key(&r, "mesh")) {
                                ok = js_u32(&r, &nd->mesh_index);
                            } else if (js_key(&r, "flags")) {
                                ok = js_u32(&r, &flags);
                            } else if (js_key(&r, "local")) {
                                ok = js_hex(&r, (u8 *)nd->local_transform.e,
                                             (u32)sizeof(nd->local_transform));
                            } else {
                                if (!js_skip_string(&r) || !js_match(&r, ':') ||
                                    !js_skip_value(&r)) { ok = false; break; }
                            }
                            (void)js_match(&r, ',');
                        }
                        nd->has_mesh = (flags & 1u) != 0;
                        nd->skinned  = (flags & 2u) != 0;
                        if (!ok) break;
                        if (!js_match(&r, '}')) { ok = false; break; }
                        (void)js_match(&r, ',');
                    }
                    if (ok) {
                        free(s->nodes);
                        s->nodes = nodes;
                        s->node_count = node_count;
                    } else {
                        free(nodes);
                    }
                    ok = ok && js_match(&r, ']');
                }
            }
        } else {
            /* unknown top-level key */
            if (!js_skip_string(&r) || !js_match(&r, ':') || !js_skip_value(&r)) {
                ok = false; break;
            }
        }
        (void)js_match(&r, ',');
    }
    ok = ok && js_match(&r, '}');
    free(buf);
    return ok;
}

/* ---------------------------------------------------------------- */
/* Prefab                                                           */
/* ---------------------------------------------------------------- */

bool scene_save_prefab(const World *w, const Entity *entities,
                       u32 count, const char *path) {
    if (!w || !entities || !path) return false;

    /* Build a synthetic EntityMap covering only the requested entities. */
    EntityMap m;
    u32 ec = w->entity_count;
    u32 sc = count ? count : 1;
    /* Single allocation: entity_to_saved[ec] + saved_to_entity[sc] */
    u8 *prefab_block = (u8 *)malloc(sizeof(u32) * (ec + sc));
    if (!prefab_block) return false;
    m.entity_to_saved = (u32 *)prefab_block;
    m.saved_to_entity = (u32 *)(prefab_block + sizeof(u32) * ec);
    for (u32 i = 0; i < ec; i++) m.entity_to_saved[i] = UINT32_MAX;

    u32 saved = 0;
    for (u32 i = 0; i < count; i++) {
        Entity e = entities[i];
        if (!entity_valid(e)) continue;
        if (e.index >= ec) continue;
        if (w->entities[e.index].generation != e.generation) continue;
        m.entity_to_saved[e.index] = saved;
        m.saved_to_entity[saved] = e.index;
        saved++;
    }
    m.count = saved;

    ByteBuf chunks[2];
    bb_init(&chunks[0]); bb_init(&chunks[1]);
    bool ok = emit_entities_chunk(w, &m, &chunks[0]) &&
              emit_components_chunk(w, &m, &chunks[1]);

    FILE *fp = NULL;
    if (ok) {
        fp = fopen(path, "wb");
        if (!fp) ok = false;
    }
    if (ok) {
        BscnHeader h;
        h.magic = BSCN_MAGIC;
        h.version = BSCN_VERSION;
        h.chunk_count = 2;
        BscnChunkEntry table[2];
        u32 base = (u32)sizeof(h) + 2u * (u32)sizeof(BscnChunkEntry);
        table[0].type = BSCN_CHUNK_ENTITIES;
        table[0].offset = base;
        table[0].size = chunks[0].size;
        table[1].type = BSCN_CHUNK_COMPONENTS;
        table[1].offset = base + chunks[0].size;
        table[1].size = chunks[1].size;
        if (fwrite(&h, sizeof(h), 1, fp) != 1) ok = false;
        if (ok && fwrite(table, sizeof(table), 1, fp) != 1) ok = false;
        for (u32 i = 0; i < 2 && ok; i++) {
            if (chunks[i].size && fwrite(chunks[i].data, 1, chunks[i].size, fp) != chunks[i].size) {
                ok = false;
            }
        }
    }
    if (fp) fclose(fp);
    bb_free(&chunks[0]); bb_free(&chunks[1]);
    emap_free(&m);
    return ok;
}

bool scene_instantiate_prefab(World *w, Scene *s,
                              const char *path, Vec3 position) {
    u32 old_node_count = s ? s->node_count : 0u;
    bool ok = scene_load_binary(w, s, path);
    if (ok && s && s->node_count > old_node_count) {
        /* Apply position offset to newly loaded scene nodes. */
        f32 px = position.e[0], py = position.e[1], pz = position.e[2];
        if (px != 0.0f || py != 0.0f || pz != 0.0f) {
            for (u32 i = old_node_count; i < s->node_count; i++) {
                SceneNode *nd = &s->nodes[i];
                nd->local_transform.e[3][0] += px;
                nd->local_transform.e[3][1] += py;
                nd->local_transform.e[3][2] += pz;
            }
        }
    }
    return ok;
}
