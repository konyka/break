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

static bool scene_file_size_ok(long fsz, long min_bytes) {
    if (fsz < min_bytes) return false;
    if ((u64)fsz > (u64)BSCN_MAX_FILE_BYTES) return false;
    return true;
}

static bool bscn_chunk_layout_valid(const BscnChunkEntry *table, u32 count,
                                    u64 table_end, u64 file_size) {
    for (u32 i = 0; i < count; i++) {
        u64 begin = (u64)table[i].offset;
        u64 end = begin + (u64)table[i].size;
        if (begin < table_end || end > file_size) return false;
        for (u32 j = 0; j < i; j++) {
            u64 other_begin = (u64)table[j].offset;
            u64 other_end = other_begin + (u64)table[j].size;
            /* Half-open payload ranges may touch, but cannot share bytes. */
            if (begin < other_end && other_begin < end) return false;
        }
    }
    return true;
}

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
    if (extra > UINT32_MAX - b->size) return false;
    u32 need = b->size + extra;
    if (need <= b->cap) return true;
    u32 nc = b->cap ? b->cap : 256;
    while (nc < need) {
        if (nc > UINT32_MAX / 2u) {
            nc = need;
            break;
        }
        nc *= 2u;
    }
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

bool scene_serial_test_bytebuf_rejects_wrap(void) {
    ByteBuf b;
    bb_init(&b);
    b.size = 16u;
    b.cap = 16u;
    return !bb_reserve(&b, UINT32_MAX);
}

static bool scene_u32_pair_block_fits_size(u32 a, u32 b) {
    if (a > UINT32_MAX - b) return false;
#if UINTPTR_MAX <= UINT32_MAX
    return (usize)(a + b) <= SIZE_MAX / sizeof(u32);
#else
    (void)a;
    (void)b;
    return true;
#endif
}

bool scene_serial_test_prefab_block_rejects_wrap(void) {
    return !scene_u32_pair_block_fits_size(UINT32_MAX, 1u);
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

static bool emap_block_fits_size(u32 count) {
#if UINTPTR_MAX <= UINT32_MAX
    return (usize)count <= SIZE_MAX / sizeof(u32) / 2u;
#else
    (void)count;
    return true;
#endif
}

static bool emap_build(const World *w, EntityMap *m) {
    /* Single allocation: entity_to_saved[N] + saved_to_entity[N].
     * 2 mallocs + 1 calloc → 1 malloc, 2 free → 1 free. */
    u32 n = w->entity_count;
    if (!emap_block_fits_size(n)) return false;
    u8 *block = (u8 *)malloc(sizeof(u32) * (usize)n * 2u);
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
    bool write_ok = fwrite(&h, sizeof(h), 1, fp) == 1;

    u32 base = (u32)sizeof(BscnHeader) + 5u * (u32)sizeof(BscnChunkEntry);
    BscnChunkEntry table[5];
    u32 cursor = base;
    for (u32 i = 0; i < 5; i++) {
        table[i].type = ctypes[i];
        table[i].offset = cursor;
        table[i].size = chunks[i].size;
        cursor += chunks[i].size;
    }
    if (write_ok && fwrite(table, sizeof(table), 1, fp) != 1) write_ok = false;

    for (u32 i = 0; i < 5 && write_ok; i++) {
        if (chunks[i].size && fwrite(chunks[i].data, 1, chunks[i].size, fp) != chunks[i].size) {
            write_ok = false;
        }
    }
    if (ferror(fp)) write_ok = false;
    if (fclose(fp) != 0) write_ok = false;
    if (!write_ok) goto fail;

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

static bool scene_mat4_finite(const Mat4 *m) {
    for (u32 col = 0; col < 4u; col++) {
        for (u32 row = 0; row < 4u; row++) {
            if (!isfinite(m->e[col][row])) return false;
        }
    }
    return true;
}

static bool scene_resource_finite(const SceneResource *res) {
    for (u32 i = 0; i < 8u; i++) {
        if (!isfinite(res->f[i])) return false;
    }
    return true;
}

void scene_resources_free(Scene *s) {
    if (!s) return;
    free(s->resources);
    s->resources = NULL;
    s->resource_count = 0;
}

void scene_serial_free(Scene *s) {
    if (!s) return;
    free(s->nodes);
    s->nodes = NULL;
    s->node_count = 0;
    scene_resources_free(s);
}

/* Smallest on-disk RESOURCES entry: guid(8) + type(4) + ref_index(4) +
 * flags(4) + path_len(4). Anything the header claims beyond what the chunk can
 * physically hold is bogus. */
#define BSCN_RESOURCE_MIN_BYTES 24u

static bool load_resources_chunk(Scene *s, Reader *r) {
    u32 n = 0;
    if (!rd_u32(r, &n)) return false;
    /* R387: ENTITIES and SCENE_NODES bound their counts before allocating; this
     * chunk did not, so a mutated count sent `n * sizeof(SceneResource)` (~300B
     * each) straight into calloc — 0xFFFFFFFF asks for ~1.2TB. Derive the bound
     * from the chunk's own size so no valid file can be rejected. */
    if ((u64)n * (u64)BSCN_RESOURCE_MIN_BYTES > (u64)(r->end - r->p)) return false;
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
            /* R416: validate the skip BEFORE advancing r->p — advancing past
             * r->end and checking afterwards is UB (pointer out of range). */
            if ((u64)(plen - keep) > (u64)(r->end - r->p)) { free(arr); return false; }
            r->p += (plen - keep);
        } else if (plen) {
            if (!rd_bytes(r, tmp.path, plen)) { free(arr); return false; }
        }
        if (!scene_resource_finite(&tmp)) { free(arr); return false; }
        if (arr) arr[i] = tmp;
    }
    if (s) {
        free(s->resources);
        s->resources = arr;
        s->resource_count = n;
    }
    return true;
}

/* R353: undo entities created by a failed load so World is not left polluted. */
static void rollback_entities(World *w, Entity *ents, u32 count) {
    if (!w || !ents) return;
    for (u32 i = 0; i < count; i++) {
        if (entity_valid(ents[i]))
            world_destroy_entity(w, ents[i]);
    }
}

#define BSCN_MAX_LOAD_ENTITIES ECS_MAX_ENTITIES
#define BSCN_MAX_LOAD_NODES    (64u * 1024u)

static bool load_entities_chunk(World *w, Reader *r,
                                Entity **out_entities, u32 *out_count,
                                u32 declared_known[ECS_MAX_COMPONENTS]) {
    u32 n = 0;
    memset(declared_known, 0, ECS_MAX_COMPONENTS * sizeof(*declared_known));
    if (!rd_u32(r, &n)) return false;
    if (n > BSCN_MAX_LOAD_ENTITIES) return false;
    Entity *ents = (Entity *)calloc(n ? n : 1, sizeof(Entity));
    if (!ents) return false;

    for (u32 i = 0; i < n; i++) {
        u32 saved_gen = 0, comp_count = 0;
        if (!rd_u32(r, &saved_gen) || !rd_u32(r, &comp_count)) {
            rollback_entities(w, ents, i);
            free(ents); return false;
        }
        /* Live entity handles always have a nonzero generation.  Retaining
         * world_create_entity's generation for a zero disk value changes ID. */
        if (saved_gen == 0) {
            rollback_entities(w, ents, i);
            free(ents); return false;
        }
        /* R396: comp_count drives an unbounded inner loop + world_add_component.
         * Saves only emit a->key.count (<= ECS_MAX_COMPONENTS). Also derive a
         * bound from bytes left so mutated/truncated chunks fail before work. */
        if (comp_count > ECS_MAX_COMPONENTS) {
            rollback_entities(w, ents, i);
            free(ents); return false;
        }
        {
            u64 rem = (u64)(r->end - r->p);
            u64 need = (u64)comp_count * 4u;
            u64 min_tail = (u64)(n - i - 1u) * 8u;
            if (need + min_tail > rem) {
                rollback_entities(w, ents, i);
                free(ents); return false;
            }
        }
        Entity e = world_create_entity(w);
        if (!entity_valid(e)) {
            rollback_entities(w, ents, i);
            free(ents); return false;
        }
        /* Restore the saved generation so (index, generation) identity — the
         * stable "unified ID" shared with the scene — round-trips intact. */
        w->entities[e.index].generation = saved_gen;
        e.generation = saved_gen;
        ents[i] = e;
        u64 seen_types_lo = 0;
        u64 seen_types_hi = 0;
        for (u32 k = 0; k < comp_count; k++) {
            u32 type = 0;
            if (!rd_u32(r, &type)) {
                rollback_entities(w, ents, i + 1u);
                free(ents); return false;
            }
            /* Archetype component IDs form a set.  Fixed bitsets catch
             * duplicates without a per-entity allocation; future IDs stay
             * skippable for forward compatibility. */
            if (type < 64u) {
                u64 bit = (u64)1 << type;
                if (seen_types_lo & bit) {
                    rollback_entities(w, ents, i + 1u);
                    free(ents); return false;
                }
                seen_types_lo |= bit;
            } else if (type < ECS_MAX_COMPONENTS) {
                u64 bit = (u64)1 << (type - 64u);
                if (seen_types_hi & bit) {
                    rollback_entities(w, ents, i + 1u);
                    free(ents); return false;
                }
                seen_types_hi |= bit;
            }
            if (type < ECS_MAX_COMPONENTS && w->component_sizes[type]) {
                declared_known[type]++;
                world_add_component(w, e, type);
            }
        }
    }
    *out_entities = ents;
    *out_count = n;
    return true;
}

static bool entity_declares_component(const World *w, Entity e,
                                      ComponentType type) {
    if (!w || e.index == 0 || e.index >= w->entity_count ||
        w->entities[e.index].generation != e.generation)
        return false;
    const Archetype *a = &w->archetypes[w->entity_archetype[e.index]];
    for (u32 i = 0; i < a->key.count; i++) {
        if (a->key.ids[i] == type) return true;
    }
    return false;
}

static bool load_components_chunk(World *w, Reader *r,
                                  const Entity *ents, u32 ent_count,
                                  const u32 declared_known[ECS_MAX_COMPONENTS]) {
    u32 type_count = 0;
    if (!rd_u32(r, &type_count)) return false;
    /* A save writes at most one record for every registered engine component.
     * Reject impossible counts before their file-controlled loop can burn CPU;
     * each record also needs its fixed type/size/instance header. */
    if (type_count > ECS_MAX_COMPONENTS ||
        (u64)type_count * 3u * sizeof(u32) > (u64)(r->end - r->p))
        return false;
    u64 seen_types_lo = 0;
    u64 seen_types_hi = 0;
    ComponentType seen_type_ids[ECS_MAX_COMPONENTS];
    u64 seen_instances[ECS_ENTITY_BITMAP_WORDS];
    for (u32 t = 0; t < type_count; t++) {
        u32 type = 0, size = 0, instances = 0;
        if (!rd_u32(r, &type) || !rd_u32(r, &size) || !rd_u32(r, &instances)) return false;
        /* Current-format component IDs are unique, including an unknown ID
         * whose payload we skip.  The small fixed list preserves that v1
         * invariant without narrowing future ID values or allocating memory. */
        for (u32 prev = 0; prev < t; prev++) {
            if (seen_type_ids[prev] == type) return false;
        }
        seen_type_ids[t] = type;
        if (type < 64u) {
            u64 bit = (u64)1 << type;
            if (seen_types_lo & bit) return false;
            seen_types_lo |= bit;
        } else if (type < ECS_MAX_COMPONENTS) {
            u64 bit = (u64)1 << (type - 64u);
            if (seen_types_hi & bit) return false;
            seen_types_hi |= bit;
        }
        /* A writer emits at most one instance per saved entity for each type.
         * Reject an impossible count and its minimum record bytes before the
         * file-controlled loop can perform component migrations. */
        if (instances > ent_count ||
            (u64)instances * ((u64)sizeof(u32) + (u64)size) >
                (u64)(r->end - r->p))
            return false;
        bool known = (type < ECS_MAX_COMPONENTS) && (w->component_sizes[type] == size);
        /* Every v1 type record, including an unknown one we skip, has at most
         * one instance per saved entity.  Reuse the fixed bitmap per record. */
        memset(seen_instances, 0, sizeof(seen_instances));
        if (known) {
            /* A v1 writer emits exactly one payload for every locally declared
             * compatible component.  Count plus per-entity bits makes this a
             * bijection without rescanning archetypes or allocating memory. */
            if (instances != declared_known[type]) return false;
        }
        for (u32 i = 0; i < instances; i++) {
            u32 saved_idx = 0;
            if (!rd_u32(r, &saved_idx)) return false;
            if ((u32)(r->end - r->p) < size) return false;
            /* Component type data can be skipped for forward compatibility,
             * but every instance still needs a real saved entity owner. */
            if (saved_idx >= ent_count) return false;
            u32 word = saved_idx / 64u;
            u64 bit = (u64)1 << (saved_idx % 64u);
            if (seen_instances[word] & bit) return false;
            seen_instances[word] |= bit;
            if (known) {
                if (!entity_declares_component(w, ents[saved_idx], type)) return false;
                void *dst = world_get_component(w, ents[saved_idx], type);
                if (!dst) return false;
                memcpy(dst, r->p, size);
            }
            r->p += size;
        }
    }
    /* A compatible local declaration requires its own type record.  A record
     * with a different size remains a forward-compatible skip. */
    for (u32 type = 0; type < ECS_MAX_COMPONENTS; type++) {
        bool seen = type < 64u ? (seen_types_lo & ((u64)1 << type)) != 0 :
                                 (seen_types_hi & ((u64)1 << (type - 64u))) != 0;
        if (declared_known[type] && !seen) return false;
    }
    return true;
}

static bool load_scene_nodes_chunk(Scene *s, Reader *r) {
    u32 n = 0;
    if (!rd_u32(r, &n)) return false;
    if (n > BSCN_MAX_LOAD_NODES) return false;
    if (!s) {
        /* Discarding nodes must not weaken validation of their transforms. */
        for (u32 i = 0; i < n; i++) {
            Mat4 local, world; u32 dummy;
            if (!rd_bytes(r, local.e, sizeof(local)) ||
                !rd_bytes(r, world.e, sizeof(world)) ||
                !rd_u32(r, &dummy) || !rd_u32(r, &dummy) ||
                !rd_u32(r, &dummy) || !rd_u32(r, &dummy) ||
                !rd_u32(r, &dummy)) return false;
            if (!scene_mat4_finite(&local) || !scene_mat4_finite(&world))
                return false;
        }
        return true;
    }
    /* R383: n==0 used to still take a 1-element block (calloc(0) may return NULL,
     * which the OOM check would misread). Skip the alloc instead — matches
     * load_resources_chunk and leaves node_count==0 with nodes==NULL. */
    SceneNode *nodes = NULL;
    if (n) {
        nodes = (SceneNode *)calloc(n, sizeof(SceneNode));
        if (!nodes) return false;
    }
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
        if (!scene_mat4_finite(&nd->local_transform) ||
            !scene_mat4_finite(&nd->world_transform)) {
            free(nodes); return false;
        }
    }
    free(s->nodes);
    s->nodes = nodes;
    s->node_count = n;
    return true;
}

bool scene_probe_binary(const char *path) {
    if (!path) return false;
    FILE *fp = fopen(path, "rb");
    if (!fp) return false;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return false; }
    long fsz = ftell(fp);
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return false; }
    if (!scene_file_size_ok(fsz, (long)sizeof(BscnHeader))) { fclose(fp); return false; }
    u8 *buf = (u8 *)malloc((size_t)fsz);
    if (!buf) { fclose(fp); return false; }
    if (fread(buf, 1, (size_t)fsz, fp) != (size_t)fsz) { fclose(fp); free(buf); return false; }
    fclose(fp);
    BscnHeader h;
    memcpy(&h, buf, sizeof(h));
    if (h.magic != BSCN_MAGIC || h.version != BSCN_VERSION) { free(buf); return false; }
    if (h.chunk_count > 64) { free(buf); return false; }
    u32 table_off = (u32)sizeof(BscnHeader);
    u64 table_end = (u64)table_off + (u64)h.chunk_count * (u64)sizeof(BscnChunkEntry);
    if (table_end > (u64)fsz) { free(buf); return false; }
    BscnChunkEntry *table = (BscnChunkEntry *)(buf + table_off);
    bool ok = bscn_chunk_layout_valid(table, h.chunk_count, table_end, (u64)fsz);
    free(buf);
    return ok;
}

bool scene_load_binary(World *w, Scene *s, const char *path) {
    if (!w || !path) return false;
    FILE *fp = fopen(path, "rb");
    if (!fp) return false;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return false; }
    long fsz = ftell(fp);
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return false; }
    if (!scene_file_size_ok(fsz, (long)sizeof(BscnHeader))) { fclose(fp); return false; }

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
    /* Validate complete, non-overlapping payload layout before parsing. */
    if (!bscn_chunk_layout_valid(table, h.chunk_count, table_end, (u64)fsz)) {
        free(buf);
        return false;
    }

    Entity *ents = NULL; u32 ent_count = 0;
    u32 declared_known[ECS_MAX_COMPONENTS];
    memset(declared_known, 0, sizeof(declared_known));
    bool ok = true;
    /* R384: stage Scene chunks so a later failing chunk cannot clobber the
     * caller's scene graph. NULL `s` still means "parse and discard". */
    Scene staged = {0};
    Scene *dst = s ? &staged : NULL;

    /* First pass: ENTITIES (must precede COMPONENTS). */
    /* R387: this scanned every chunk without stopping, so a file declaring two
     * ENTITIES chunks called load_entities_chunk twice — the second overwrote
     * `ents` and leaked the first allocation. A well-formed BSCN has exactly
     * one, and picking arbitrarily between two would leave the COMPONENTS
     * chunk's entity indices ambiguous, so reject the duplicate outright. */
    bool seen_entities = false;
    for (u32 i = 0; i < h.chunk_count && ok; i++) {
        if (table[i].type != BSCN_CHUNK_ENTITIES) continue;
        if (seen_entities) { ok = false; break; }
        seen_entities = true;
        /* R108-1: validate chunk data bounds */
        u64 chunk_end = (u64)table[i].offset + (u64)table[i].size;
        if (chunk_end > (u64)fsz) { ok = false; break; }
        Reader r;
        r.p = buf + table[i].offset;
        r.end = r.p + table[i].size;
        ok = load_entities_chunk(w, &r, &ents, &ent_count, declared_known) && r.p == r.end;
    }
    /* Second pass: remaining chunks. */
    bool seen_components = false;
    bool seen_scene_nodes = false;
    bool seen_resources = false;
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
            if (seen_components) { ok = false; break; }
            seen_components = true;
            ok = load_components_chunk(w, &r, ents, ent_count, declared_known) && r.p == r.end; break;
        case BSCN_CHUNK_SCENE_NODES:
            if (seen_scene_nodes) { ok = false; break; }
            seen_scene_nodes = true;
            ok = load_scene_nodes_chunk(dst, &r) && r.p == r.end; break;
        case BSCN_CHUNK_RESOURCES:
            if (seen_resources) { ok = false; break; }
            seen_resources = true;
            ok = load_resources_chunk(dst, &r) && r.p == r.end; break;
        case BSCN_CHUNK_HIERARCHY:
        default:
            /* Hierarchy is implicit in SceneNode.parent_index. Skip silently. */
            break;
        }
    }

    /* If no COMPONENTS chunk exists, local declarations cannot have payloads.
     * Empty legacy scenes remain loadable because they declare no local type. */
    if (ok && !seen_components) {
        for (u32 type = 0; type < ECS_MAX_COMPONENTS; type++) {
            if (declared_known[type]) { ok = false; break; }
        }
    }

    /* R353: COMPONENTS/NODES/RESOURCES failure must not leave orphan entities. */
    if (!ok)
        rollback_entities(w, ents, ent_count);
    /* R384: same reasoning for the Scene. Chunks are applied in table order, so
     * a valid SCENE_NODES followed by a corrupt COMPONENTS used to free the
     * caller's old nodes and install the new ones, then return false — losing
     * the previous scene graph on a failed load. Commit only on success. */
    if (s) {
        if (ok) {
            free(s->nodes);
            s->nodes = staged.nodes;
            s->node_count = staged.node_count;
            free(s->resources);
            s->resources = staged.resources;
            s->resource_count = staged.resource_count;
        } else {
            scene_serial_free(&staged);
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

        /* R426: comma placement tracked by an emitted counter, not the
         * archetype slot k — a NULL first component (skipped below) would
         * otherwise emit a leading comma. */
        u32 emitted = 0;
        for (u32 k = 0; k < a->key.count && ok; k++) {
            ComponentType t = a->key.ids[k];
            u32 sz = 0;
            const u8 *p = entity_component_ptr(w, ei, t, &sz);
            if (!p) continue;
            if (emitted) ok = ok && sb_putc(&b, ',');
            emitted++;
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
            if (ferror(fp)) ok = false;
            if (fclose(fp) != 0) ok = false;
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
/* After an object member, require either its closing brace or one comma
 * followed by another member.  JSON never permits a trailing comma. */
static bool js_object_separator(JsonR *r) {
    if (js_peek(r, '}')) return true;
    return js_match(r, ',') && !js_peek(r, '}');
}
/* Array elements follow the same no-trailing-comma rule, but each JSON node
 * is specifically an object. */
static bool js_node_array_separator(JsonR *r) {
    if (js_peek(r, ']')) return true;
    return js_match(r, ',') && !js_peek(r, ']') && js_peek(r, '{');
}
static bool js_u32(JsonR *r, u32 *out) {
    js_skip_ws(r);
    if (r->p >= r->end || !isdigit((unsigned char)*r->p)) return false;
    u32 v = 0;
    while (r->p < r->end && isdigit((unsigned char)*r->p)) {
        u32 d = (u32)(*r->p - '0');
        /* R426: reject literals > UINT32_MAX — v*10+d wrapped silently. */
        if (v > (UINT32_MAX - d) / 10u) return false;
        v = v * 10u + d;
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
typedef struct {
    char close;
    u8 phase;
    bool allow_close;
} JsonSkipFrame;

static bool js_skip_value(JsonR *r);
static bool js_skip_string(JsonR *r) {
    if (!js_match(r, '"')) return false;
    while (r->p < r->end) {
        unsigned char c = (unsigned char)*r->p++;
        if (c == '"') return true;
        if (c < 0x20u) return false;
        if (c != '\\') continue;
        if (r->p >= r->end) return false;
        char escape = *r->p++;
        if (escape == '"' || escape == '\\' || escape == '/' ||
            escape == 'b' || escape == 'f' || escape == 'n' ||
            escape == 'r' || escape == 't') continue;
        if (escape != 'u' || r->end - r->p < 4) return false;
        for (u32 i = 0; i < 4; i++) {
            if (hex_digit(r->p[i]) < 0) return false;
        }
        r->p += 4;
    }
    return false;
}
static bool js_skip_number(JsonR *r) {
    const char *p = r->p;
    if (p < r->end && *p == '-') p++;
    if (p >= r->end) return false;
    if (*p == '0') {
        p++;
    } else if (*p >= '1' && *p <= '9') {
        do { p++; } while (p < r->end && isdigit((unsigned char)*p));
    } else {
        return false;
    }
    if (p < r->end && *p == '.') {
        p++;
        if (p >= r->end || !isdigit((unsigned char)*p)) return false;
        do { p++; } while (p < r->end && isdigit((unsigned char)*p));
    }
    if (p < r->end && (*p == 'e' || *p == 'E')) {
        p++;
        if (p < r->end && (*p == '+' || *p == '-')) p++;
        if (p >= r->end || !isdigit((unsigned char)*p)) return false;
        do { p++; } while (p < r->end && isdigit((unsigned char)*p));
    }
    r->p = p;
    return true;
}
static bool js_skip_literal(JsonR *r, const char *literal, usize len) {
    if ((usize)(r->end - r->p) < len || memcmp(r->p, literal, len) != 0)
        return false;
    r->p += len;
    return true;
}
static bool js_skip_value_start(JsonR *r, JsonSkipFrame *frames, u32 *depth) {
    js_skip_ws(r);
    if (r->p >= r->end) return false;
    char c = *r->p;
    if (c == '"') return js_skip_string(r);
    if (c == '{' || c == '[') {
        if (*depth >= 256u) return false;
        frames[*depth].close = (c == '{') ? '}' : ']';
        frames[*depth].phase = 0;
        frames[*depth].allow_close = true;
        (*depth)++;
        r->p++;
        return true;
    }
    if (c == '-' || isdigit((unsigned char)c)) return js_skip_number(r);
    if (c == 't') return js_skip_literal(r, "true", 4u);
    if (c == 'f') return js_skip_literal(r, "false", 5u);
    if (c == 'n') return js_skip_literal(r, "null", 4u);
    return false;
}
static bool js_skip_value(JsonR *r) {
    /* Validate unknown extension values without recursion or heap allocation.
     * Frames parse each nested object/array's local member/element grammar. */
    JsonSkipFrame frames[256];
    u32 depth = 0;
    if (!js_skip_value_start(r, frames, &depth)) return false;
    while (depth > 0) {
        JsonSkipFrame *f = &frames[depth - 1u];
        if (f->close == '}') {
            if (f->phase == 0) { /* key or (only for a fresh object) close */
                if (js_peek(r, '}')) {
                    if (!f->allow_close) return false;
                    r->p++;
                    depth--;
                } else if (js_skip_string(r)) {
                    f->phase = 1;
                } else {
                    return false;
                }
            } else if (f->phase == 1) { /* colon */
                if (!js_match(r, ':')) return false;
                f->phase = 2;
            } else if (f->phase == 2) { /* member value */
                if (!js_skip_value_start(r, frames, &depth)) return false;
                f->phase = 3;
            } else { /* comma or close */
                if (js_peek(r, '}')) {
                    r->p++;
                    depth--;
                } else if (js_match(r, ',')) {
                    f->phase = 0;
                    f->allow_close = false;
                } else {
                    return false;
                }
            }
        } else {
            if (f->phase == 0) { /* element or (only for a fresh array) close */
                if (js_peek(r, ']')) {
                    if (!f->allow_close) return false;
                    r->p++;
                    depth--;
                } else {
                    if (!js_skip_value_start(r, frames, &depth)) return false;
                    f->phase = 1;
                }
            } else { /* comma or close */
                if (js_peek(r, ']')) {
                    r->p++;
                    depth--;
                } else if (js_match(r, ',')) {
                    f->phase = 0;
                    f->allow_close = false;
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}

static bool json_load_components(World *w, JsonR *r, Entity ent) {
    if (!js_match(r, '[')) return false;
    if (js_match(r, ']')) return true;
    ComponentType seen_types[ECS_MAX_COMPONENTS];
    u32 type_count = 0;
    do {
        if (type_count >= ECS_MAX_COMPONENTS) return false;
        if (!js_match(r, '{')) return false;
        u32 type = 0, size = 0;
        bool got_data = false;
        bool seen_type = false;
        bool seen_size = false;
        bool seen_data = false;
        u8 stack_buf[1024];
        u8 *data = stack_buf;
        u32 data_size = 0;
        while (!js_peek(r, '}')) {
            js_skip_ws(r);
            if (js_key(r, "type")) {
                if (seen_type) goto fail;
                seen_type = true;
                if (!js_u32(r, &type)) goto fail;
            } else if (js_key(r, "size")) {
                if (seen_size) goto fail;
                seen_size = true;
                if (!js_u32(r, &size)) goto fail;
            }
            else if (js_key(r, "data")) {
                if (seen_data) goto fail;
                seen_data = true;
                /* R384: `size` is attacker-controlled and was passed straight to
                 * malloc — a bogus "size": 4000000000 forced a 4GB request. Hex
                 * needs 2 chars per byte, so bound it by the remaining input the
                 * way load_components_chunk bounds itself by (r->end - r->p). */
                if ((u64)size * 2u > (u64)(r->end - r->p)) goto fail;
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
            if (!js_object_separator(r)) goto fail;
        }
        if (!js_match(r, '}')) goto fail;

        /* JSON output, like BSCN, groups one object per component type.  Keep
         * unknown IDs skippable but reject duplicate definitions by full ID. */
        for (u32 prev = 0; prev < type_count; prev++) {
            if (seen_types[prev] == type) goto fail;
        }
        seen_types[type_count++] = type;

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
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return false; }
    long fsz = ftell(fp);
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return false; }
    if (!scene_file_size_ok(fsz, 1)) { fclose(fp); return false; }
    char *buf = (char *)malloc((size_t)fsz);
    if (!buf) { fclose(fp); return false; }
    if (fread(buf, 1, (size_t)fsz, fp) != (size_t)fsz) {
        fclose(fp); free(buf); return false;
    }
    fclose(fp);

    JsonR r;
    r.p = buf;
    r.end = buf + fsz;

    Entity *created = NULL;
    u32 created_count = 0, created_cap = 0;

    /* R422: stage parsed nodes locally and commit only after the WHOLE
     * document parses — the binary path does the same via its R384 temp
     * Scene. Committing mid-parse freed the caller's old scene graph before
     * a later top-level failure returned false. */
    SceneNode *staged_nodes = NULL;
    u32 staged_node_count = 0;
    bool nodes_staged = false;

    bool seen_version = false;
    bool seen_entities = false;
    bool seen_nodes = false;
    bool ok = js_match(&r, '{');
    while (ok && !js_peek(&r, '}')) {
        if (js_key(&r, "version")) {
            if (seen_version) { ok = false; break; }
            seen_version = true;
            u32 v = 0;
            ok = js_u32(&r, &v) && (v == BSCN_VERSION);
        } else if (js_key(&r, "entities")) {
            if (seen_entities) { ok = false; break; }
            seen_entities = true;
            ok = js_match(&r, '[');
            if (ok && !js_match(&r, ']')) {
                do {
                    if (!js_match(&r, '{')) { ok = false; break; }
                    Entity e = world_create_entity(w);
                    if (!entity_valid(e)) { ok = false; break; }
                    /* R353: track for rollback if later parse/nodes fail. */
                    if (created_count >= created_cap) {
                        u32 nc = created_cap ? created_cap * 2u : 16u;
                        Entity *tmp = (Entity *)realloc(created, nc * sizeof(Entity));
                        if (!tmp) {
                            world_destroy_entity(w, e);
                            ok = false; break;
                        }
                        created = tmp;
                        created_cap = nc;
                    }
                    created[created_count++] = e;
                    bool seen_gen = false;
                    bool seen_components = false;
                    while (ok && !js_peek(&r, '}')) {
                        if (js_key(&r, "gen")) {
                            if (seen_gen) { ok = false; break; }
                            seen_gen = true;
                            /* R243: JSON save emits "gen" but load previously
                             * skipped it, so the (index, generation) identity —
                             * restored on the binary path (see load_entities_chunk)
                             * and asserted by generation_restore_roundtrip — was
                             * lost on JSON round-trips. Restore it identically. */
                            u32 g = 0;
                            ok = js_u32(&r, &g) && g != 0;
                            if (ok) {
                                w->entities[e.index].generation = g;
                                e.generation = g;
                                created[created_count - 1u] = e;
                            }
                        } else if (js_key(&r, "components")) {
                            if (seen_components) { ok = false; break; }
                            seen_components = true;
                            ok = json_load_components(w, &r, e);
                        } else {
                            /* skip key:value */
                            if (!js_skip_string(&r) || !js_match(&r, ':') ||
                                !js_skip_value(&r)) { ok = false; break; }
                        }
                        if (!js_object_separator(&r)) { ok = false; break; }
                    }
                    if (!ok) break;
                    if (!js_match(&r, '}')) { ok = false; break; }
                } while (js_match(&r, ','));
                ok = ok && js_match(&r, ']');
            }
        } else if (js_key(&r, "nodes")) {
            if (seen_nodes) { ok = false; break; }
            seen_nodes = true;
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
                        /* Keep JSON import bounded by the same SceneNode cap
                         * as BSCN. Check before growing the staging array so
                         * a compact hostile document cannot force an unbounded
                         * realloc chain or partially commit a huge graph. */
                        if (node_count >= BSCN_MAX_LOAD_NODES) {
                            ok = false;
                            break;
                        }
                        if (node_count >= node_cap) {
                            node_cap *= 2;
                            SceneNode *tmp = (SceneNode *)realloc(nodes, node_cap * sizeof(SceneNode));
                            if (!tmp) { ok = false; break; }
                            nodes = tmp;
                        }
                        SceneNode *nd = &nodes[node_count++];
                        memset(nd, 0, sizeof(*nd));
                        /* R426: a node missing the "parent" key must default to
                         * root, not to parent 0 (memset left parent_index == 0,
                         * silently parenting it to node 0). Binary/glTF paths
                         * use UINT32_MAX for root. */
                        nd->parent_index = UINT32_MAX;
                        u32 flags = 0;
                        bool seen_parent = false;
                        bool seen_mesh = false;
                        bool seen_flags = false;
                        bool seen_local = false;
                        while (ok && !js_peek(&r, '}')) {
                            if (js_key(&r, "parent")) {
                                if (seen_parent) { ok = false; break; }
                                seen_parent = true;
                                ok = js_u32(&r, &nd->parent_index);
                            } else if (js_key(&r, "mesh")) {
                                if (seen_mesh) { ok = false; break; }
                                seen_mesh = true;
                                ok = js_u32(&r, &nd->mesh_index);
                            } else if (js_key(&r, "flags")) {
                                if (seen_flags) { ok = false; break; }
                                seen_flags = true;
                                ok = js_u32(&r, &flags);
                            } else if (js_key(&r, "local")) {
                                if (seen_local) { ok = false; break; }
                                seen_local = true;
                                ok = js_hex(&r, (u8 *)nd->local_transform.e,
                                             (u32)sizeof(nd->local_transform));
                                if (ok) ok = scene_mat4_finite(&nd->local_transform);
                            } else {
                                if (!js_skip_string(&r) || !js_match(&r, ':') ||
                                    !js_skip_value(&r)) { ok = false; break; }
                            }
                            if (!js_object_separator(&r)) { ok = false; break; }
                        }
                        nd->has_mesh = (flags & 1u) != 0;
                        nd->skinned  = (flags & 2u) != 0;
                        if (!ok) break;
                        if (!js_match(&r, '}')) { ok = false; break; }
                        if (!js_node_array_separator(&r)) { ok = false; break; }
                    }
                    if (ok) {
                        /* R422: stage only — s->nodes is committed below once
                         * the entire document has parsed successfully. */
                        free(staged_nodes);
                        staged_nodes = nodes;
                        staged_node_count = node_count;
                        nodes_staged = true;
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
        if (!js_object_separator(&r)) { ok = false; break; }
    }
    ok = ok && js_match(&r, '}');
    /* A valid scene occupies the whole document; permit only trailing JSON
     * whitespace after the root object, never an ignored second value. */
    if (ok) {
        js_skip_ws(&r);
        ok = r.p == r.end;
    }
    /* R422: commit the staged nodes only on full success; otherwise drop the
     * staging buffer and leave the caller's old scene graph intact. */
    if (s && ok && nodes_staged) {
        free(s->nodes);
        s->nodes = staged_nodes;
        s->node_count = staged_node_count;
    } else {
        free(staged_nodes);
    }
    if (!ok)
        rollback_entities(w, created, created_count);
    free(created);
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
    if (!scene_u32_pair_block_fits_size(ec, sc)) return false;
    /* Single allocation: entity_to_saved[ec] + saved_to_entity[sc] */
    u8 *prefab_block = (u8 *)malloc(sizeof(u32) * (usize)(ec + sc));
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
    if (fp) {
        if (ferror(fp)) ok = false;
        if (fclose(fp) != 0) ok = false;
    }
    bb_free(&chunks[0]); bb_free(&chunks[1]);
    emap_free(&m);
    return ok;
}

bool scene_instantiate_prefab(World *w, Scene *s,
                              const char *path, Vec3 position) {
    bool ok = scene_load_binary(w, s, path);
    if (ok && s && s->node_count > 0) {
        /* R416: scene_load_binary REPLACES s->nodes wholesale (frees the old
         * array and commits the staged one), so there is no "newly appended"
         * tail — offset ALL loaded nodes, not nodes [old_count..count). */
        f32 px = position.e[0], py = position.e[1], pz = position.e[2];
        if (px != 0.0f || py != 0.0f || pz != 0.0f) {
            for (u32 i = 0; i < s->node_count; i++) {
                SceneNode *nd = &s->nodes[i];
                /* R422: offset ROOT nodes only. Children inherit their
                 * parent's translation through world-transform composition,
                 * so adding the offset to every node displaced a node at
                 * depth d by (d+1)x position. (parent_index >= node_count is
                 * treated as a root, matching scene_compute_world_transforms'
                 * R151 malformed-parent guard.) */
                if (nd->parent_index != UINT32_MAX && nd->parent_index < s->node_count)
                    continue;
                nd->local_transform.e[3][0] += px;
                nd->local_transform.e[3][1] += py;
                nd->local_transform.e[3][2] += pz;
            }
        }
    }
    return ok;
}
