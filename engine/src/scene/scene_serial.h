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

/* Free the RESOURCES manifest owned by a Scene (safe on NULL / empty). Called
 * automatically by asset_scene_free; exposed for tests / standalone scenes. */
void scene_resources_free(Scene *s);

/* ---- JSON text format (debug/editor) ---- */
bool scene_save_json(const World *w, const Scene *s,
                     const char *path, const SerializeOptions *opts);
bool scene_load_json(World *w, Scene *s, const char *path);

/* ---- Prefab: subgraph save + instantiate ---- */
bool scene_save_prefab(const World *w, const Entity *entities,
                       u32 count, const char *path);
bool scene_instantiate_prefab(World *w, Scene *s,
                              const char *path, Vec3 position);

#endif /* SCENE_SERIAL_H */
