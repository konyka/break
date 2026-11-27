#include "asset/scene_manifest_graph.h"

#include <scene/scene_serial.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_LINK 0xffffffffu

typedef struct {
    const SceneResource *res;
    u32 count;
} Manifest;

static bool is_declared_type(u32 type) {
    return type == BSCN_RES_TEXTURE || type == BSCN_RES_MATERIAL || type == BSCN_RES_MESH ||
           type == BSCN_RES_SKINNED_MESH;
}

static const SceneResource *find(const Manifest *m, u32 type, u32 ref_index) {
    for (u32 i = 0u; i < m->count; ++i) {
        if (m->res[i].type == type && m->res[i].ref_index == ref_index) return &m->res[i];
    }
    return NULL;
}

static bool in_list(const BreakAssetId *list, u32 count, BreakAssetId id) {
    for (u32 i = 0u; i < count; ++i) {
        if (list[i] == id) return true;
    }
    return false;
}

/* Every declared entry: a guid unlike the scene and every other entry, and
 * a type+ref_index no other entry has. A guid or scene id of 0 needs no
 * check here: the graph rejects it, and the build rolls back. */
static bool manifest_valid(const Manifest *m, BreakAssetId scene_id) {
    for (u32 i = 0u; i < m->count; ++i) {
        const SceneResource *a = &m->res[i];
        if (!is_declared_type(a->type)) continue;
        if (a->guid == scene_id) return false;
        for (u32 j = 0u; j < i; ++j) {
            const SceneResource *b = &m->res[j];
            if (!is_declared_type(b->type)) continue;
            if (a->guid == b->guid || (a->type == b->type && a->ref_index == b->ref_index))
                return false;
        }
    }
    return true;
}

/* The dependencies of one entry, without duplicates; links to absent
 * entries are counted in *dangling. */
static u32 entry_deps(const Manifest *m, const SceneResource *e, BreakAssetId *deps,
                      u32 *dangling) {
    u32 n = 0u;
    if (e->type == BSCN_RES_MATERIAL) {
        for (u32 k = 0u; k < 5u; ++k) {
            const SceneResource *t;
            if (e->tex_slots[k] == NO_LINK) continue;
            t = find(m, BSCN_RES_TEXTURE, e->tex_slots[k]);
            if (!t) {
                (*dangling)++;
            } else if (!in_list(deps, n, t->guid)) {
                deps[n++] = t->guid;
            }
        }
    } else if ((e->type == BSCN_RES_MESH || e->type == BSCN_RES_SKINNED_MESH) &&
               (e->flags & 1u) != 0u) {
        const SceneResource *mat = find(m, BSCN_RES_MATERIAL, e->u2);
        if (!mat) {
            (*dangling)++;
        } else {
            deps[n++] = mat->guid;
        }
    }
    return n;
}

static bool texture_path(const BreakSceneManifestGraphConfig *c, const SceneResource *e,
                         char *out) {
    const char *dir = c->texture_base_dir;
    if (e->type != BSCN_RES_TEXTURE || e->path[0] == '\0') return false;
    /* fits: the base dir was checked to leave room for a full entry path */
    if (dir && dir[0] != '\0') {
        (void)snprintf(out, BREAK_SCENE_MANIFEST_MAX_PATH, "%s/%.*s", dir, (int)sizeof(e->path),
                       e->path);
    } else {
        (void)snprintf(out, BREAK_SCENE_MANIFEST_MAX_PATH, "%.*s", (int)sizeof(e->path), e->path);
    }
    return true;
}

/* Removes what this call declared, newest first: each removed id is then
 * listed by nothing still declared. */
static void roll_back(BreakAssetGraph *graph, const BreakAssetId *declared, u32 count) {
    while (count-- > 0u) (void)break_asset_graph_remove(graph, declared[count]);
}

BreakAssetGraphResult break_scene_manifest_graph_build(const BreakSceneManifestGraphConfig *config,
                                                       const SceneResource *resources,
                                                       u32 resource_count, BreakAssetGraph *graph,
                                                       BreakSceneManifestGraphStats *out_stats) {
    Manifest m;
    BreakSceneManifestGraphStats st;
    BreakAssetId *declared = NULL;
    BreakAssetId *deps = NULL;
    u32 declared_count = 0u;
    BreakAssetGraphResult r = BREAK_ASSET_GRAPH_OK;
    char path[BREAK_SCENE_MANIFEST_MAX_PATH];
    if (!config || !graph || !out_stats || (!resources && resource_count != 0u) ||
        !config->scene_path || config->scene_path[0] == '\0' ||
        strlen(config->scene_path) >= BREAK_SCENE_MANIFEST_MAX_PATH ||
        (config->texture_base_dir &&
         strlen(config->texture_base_dir) + 1u + sizeof(resources->path) >
             BREAK_SCENE_MANIFEST_MAX_PATH)) {
        return BREAK_ASSET_GRAPH_INVALID;
    }
    m.res = resources;
    m.count = resource_count;
    if (!manifest_valid(&m, config->scene_id)) return BREAK_ASSET_GRAPH_INVALID;
    memset(&st, 0, sizeof(st));
    /* the scene needs at most every entry; an entry at most 5 textures */
    declared = (BreakAssetId *)malloc(((usize)resource_count + 1u) * sizeof(*declared));
    deps = (BreakAssetId *)malloc(((usize)resource_count + 5u) * sizeof(*deps));
    if (!declared || !deps) {
        free(declared);
        free(deps);
        return BREAK_ASSET_GRAPH_OVERLOAD;
    }
    /* textures, then materials, then meshes: each id is declared after what
     * it needs, so a rollback newest first always succeeds */
    static const u32 k_order[] = {BSCN_RES_TEXTURE, BSCN_RES_MATERIAL, BSCN_RES_MESH,
                                  BSCN_RES_SKINNED_MESH};
    for (u32 pass = 0u; pass < 4u && r == BREAK_ASSET_GRAPH_OK; ++pass) {
        for (u32 i = 0u; i < resource_count; ++i) {
            const SceneResource *e = &resources[i];
            u32 n;
            if (e->type != k_order[pass]) continue;
            n = entry_deps(&m, e, deps, &st.dangling_links);
            r = break_asset_graph_add(graph, e->guid, deps, n);
            if (r != BREAK_ASSET_GRAPH_OK) break;
            declared[declared_count++] = e->guid;
            if (e->type == BSCN_RES_TEXTURE) {
                st.textures++;
            } else if (e->type == BSCN_RES_MATERIAL) {
                st.materials++;
            } else {
                st.meshes++;
            }
        }
    }
    if (r == BREAK_ASSET_GRAPH_OK) {
        u32 n = 0u;
        for (u32 i = 0u; i < resource_count; ++i) {
            if (resources[i].type != BSCN_RES_TEXTURE && is_declared_type(resources[i].type))
                deps[n++] = resources[i].guid;
        }
        r = break_asset_graph_add(graph, config->scene_id, deps, n);
    }
    if (r != BREAK_ASSET_GRAPH_OK) {
        roll_back(graph, declared, declared_count);
        free(declared);
        free(deps);
        return r;
    }
    if (config->path) {
        for (u32 i = 0u; i < resource_count; ++i) {
            const SceneResource *e = &resources[i];
            if (!is_declared_type(e->type)) continue;
            config->path(config->path_user, e->guid,
                         texture_path(config, e, path) ? path : config->scene_path);
        }
        config->path(config->path_user, config->scene_id, config->scene_path);
    }
    free(declared);
    free(deps);
    *out_stats = st;
    return BREAK_ASSET_GRAPH_OK;
}
