#ifndef SCENE_SERIAL_H
#define SCENE_SERIAL_H

#include <ecs/ecs.h>
#include <asset/asset.h>
#include <core/types.h>

/* ---- Binary scene format ----
 * File layout:
 *   [BscnHeader]
 *   [BscnChunkEntry * chunk_count]
 *   [Chunk 1 data ...]
 *   [Chunk 2 data ...]
 *   ...
 *
 * Little-endian assumption (all modern x86/ARM targets).
 */

#define BSCN_MAGIC   0x4E534342u   /* "BSCN" little-endian */
#define BSCN_VERSION 1u
/* R398: load paths read the whole file into memory; cap before malloc. */
#define BSCN_MAX_FILE_BYTES (64u << 20)  /* 64 MiB */

bool scene_serial_test_bytebuf_rejects_wrap(void);
bool scene_serial_test_prefab_block_rejects_wrap(void);

typedef enum {
    BSCN_CHUNK_ENTITIES    = 1,
    BSCN_CHUNK_COMPONENTS  = 2,
    BSCN_CHUNK_HIERARCHY   = 3,
    BSCN_CHUNK_RESOURCES   = 4,
    BSCN_CHUNK_SCENE_NODES = 5
} BscnChunkType;

typedef struct {
    u32 type;
    u32 offset;
    u32 size;
} BscnChunkEntry;

typedef struct {
    u32 magic;
    u32 version;
    u32 chunk_count;
    /* followed by chunk_count * BscnChunkEntry */
} BscnHeader;

/* Resource reference type ids (stored in RESOURCES chunk). */
typedef enum {
    BSCN_RES_MESH     = 1,
    BSCN_RES_TEXTURE  = 2,
    BSCN_RES_MATERIAL = 3,
    BSCN_RES_SCENE    = 4
} BscnResourceType;

/* Serialization options. */
typedef struct {
    bool include_resources; /* inline resource bytes (false = path-only refs) */
    bool pretty_json;       /* pretty-printed JSON output */
} SerializeOptions;

/* ---- Binary format ---- */
bool scene_save_binary(const World *w, const Scene *s,
                       const char *path, const SerializeOptions *opts);
bool scene_load_binary(World *w, Scene *s, const char *path);
/* R380: validate BSCN without mutating World — use before clear-on-load. */
bool scene_probe_binary(const char *path);

/* Free the RESOURCES manifest owned by a Scene (safe on NULL / empty). */
void scene_resources_free(Scene *s);

/* R383: teardown for a Scene populated by scene_load_binary / scene_load_json
 * outside the asset pipeline. Those loaders allocate both `nodes` and
 * `resources`, but asset_scene_free needs an AssetContext + RHI device, so a
 * standalone caller (BSCN reload, tests) had no way to release `nodes`.
 * Safe on NULL and on repeated calls. */
void scene_serial_free(Scene *s);

/* ---- JSON text format (debug/editor) ---- */
bool scene_save_json(const World *w, const Scene *s,
                     const char *path, const SerializeOptions *opts);
bool scene_load_json(World *w, Scene *s, const char *path);

/* ---- Prefab: subgraph save + instantiate ---- */
bool scene_save_prefab(const World *w, const Entity *entities,
                       u32 count, const char *path);
/* R416: instantiate loads via scene_load_binary, which has REPLACE semantics —
 * the scene's existing nodes/resources are freed and swapped for the loaded
 * ones (it does not append). The position offset is applied to every loaded
 * node's local transform. */
bool scene_instantiate_prefab(World *w, Scene *s,
                              const char *path, Vec3 position);

#endif /* SCENE_SERIAL_H */
