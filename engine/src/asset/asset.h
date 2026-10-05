#pragma once
#include <core/types.h>
#include <rhi/rhi.h>
#include <math/math.h>
#include <animation/skeleton.h>

typedef struct VFS VFS;

typedef struct {
    RHIDevice *device;
    VFS       *vfs;
} AssetCtx;

void     asset_ctx_init(AssetCtx *ctx, RHIDevice *dev);
RHITexture asset_load_texture(AssetCtx *ctx, const char *path);
void     asset_texture_free(AssetCtx *ctx, RHITexture tex);

typedef enum {
    ALPHA_OPAQUE = 0,
    ALPHA_MASK   = 1,
    ALPHA_BLEND  = 2,
} AlphaMode;

typedef struct {
    RHITexture albedo;
    RHITexture metallic_roughness;
    RHITexture normal_map;
    RHITexture emissive;
    /* R583: glTF occlusionTexture (R channel = occlusion). Consumed by the
     * deferred G-Buffer as ao = mix(1.0, tex.r, occlusion_strength); the
     * white 1x1 fallback preserves the textureless behavior (ao = 1). */
    RHITexture occlusion;
    float      base_color[4];
    float      metallic_factor;
    float      roughness_factor;
    float      emissive_strength;
    /* R582: glTF emissiveFactor (spec default [0,0,0] — an emissive texture
     * alone emits nothing). Composed with the emissive texture and
     * emissive_strength into the deferred G-Buffer emissive target. */
    float      emissive_factor[3];
    /* R581: glTF occlusionTexture.strength (1.0 when the material has no
     * occlusion texture). R583: consumed by the deferred G-Buffer as the
     * strength of the per-pixel occlusion mix(1.0, tex.r, strength). */
    float      occlusion_strength;
    AlphaMode  alpha_mode;
    float      alpha_cutoff;
    void      *_material_ptr;
} Material;

typedef struct {
    RHIBuffer vertex_buf;
    RHIBuffer index_buf;
    u32       index_count;
    u32       vertex_count;
    u32       material_idx;
    Vec3      aabb_min;
    Vec3      aabb_max;
} Mesh;

typedef struct {
    RHIBuffer vertex_buf;
    RHIBuffer index_buf;
    u32       index_count;
    u32       material_idx;
    bool      skinned;
} SkinnedMesh;

typedef struct {
    Mat4    local_transform;
    Mat4    world_transform;
    u32     parent_index;
    u32     mesh_index;
    u32     material_idx;
    u32     skin_mesh_index;
    bool    has_mesh;
    bool    skinned;
} SceneNode;

/* A serialized resource reference (mesh/material/texture) recovered from the
 * BSCN RESOURCES chunk. `guid` is a deterministic content hash so the same
 * resource keeps a stable identity across save/load. `type` holds a
 * BscnResourceType value; `ref_index` is the scene-local mesh/material index it
 * identifies (or the RHI handle index for textures). When `flags & 1` the
 * inline descriptor (`u0..u2`, `f[]`) is valid (controlled by
 * SerializeOptions.include_resources). */
typedef struct {
    u64  guid;
    u32  type;        /* BscnResourceType */
    u32  ref_index;
    u32  flags;       /* bit0: descriptor inlined */
    u32  u0, u1, u2;  /* mesh: index_count, vertex_count, material_idx
                         material: alpha_mode, has_albedo, texture-presence
                         bits (R585, BSCN v2: bit0 mr, bit1 normal,
                         bit2 emissive, bit3 occlusion; 0 in v1 files) */
    /* R605 (BSCN v3): material per-slot texture links — the manifest's
     * material->texture wiring, which presence bits alone cannot express.
     * tex_slots[0..4] = albedo, metallic_roughness, normal, emissive,
     * occlusion; the value is the linked texture entry's ref_index (RHI
     * handle index at save time), or ~0u when the slot is empty / unknown
     * (v1/v2 files back-fill ~0u; non-material entries write ~0u). Kept
     * between u0..u2 and f[] so the guid hash domain stays one contiguous
     * run (8 u32 + 12 f32). */
    u32  tex_slots[5];
    f32  f[12];       /* mesh: aabb_min(3)+aabb_max(3)
                         material: base_color(4)+metallic+roughness+
                         emissive_strength+cutoff (f[0..7], v1 layout) +
                         occlusion_strength (f[8], R585; v1 loads default
                         1.0) + emissive_factor rgb (f[9..11], R585; v1
                         loads default 0) */
    char path[64];    /* optional source path; empty when unknown. R604: for
                         BSCN_RES_TEXTURE entries the serializer fills this
                         from Scene.texture_sources (the glTF image uri as
                         authored, relative to the glTF file) — a content-
                         stable identity, unlike the cross-process-meaningless
                         handle index in ref_index. */
} SceneResource;

/* R604: texture source-path manifest entry — maps a texture handle index to
 * the glTF image uri it was loaded from (as authored, relative to the glTF
 * file; truncated to 63 chars at record time). Populated by asset_load_gltf
 * only; programmatic scenes leave the table empty and their texture resource
 * paths stay empty (= "unknown"). */
typedef struct {
    u32  handle_index; /* RHITexture.index */
    char uri[64];
} SceneTextureSource;

typedef struct {
    Material     *materials;
    u32           material_count;
    Mesh         *meshes;
    u32           mesh_count;
    SkinnedMesh  *skinned_meshes;
    u32           skinned_mesh_count;
    SceneNode    *nodes;
    u32           node_count;
    u32           joint_count;
    u32          *joint_parents;
    Mat4         *inverse_bind;
    u32           anim_clip_count;
    AnimClip     *anim_clips;
    /* Resource manifest (RESOURCES chunk); populated on load, owned by Scene. */
    SceneResource *resources;
    u32            resource_count;
    /* R604: texture handle -> source uri table (glTF loads only); consumed by
     * the BSCN serializer to fill SceneResource.path for texture entries.
     * Owned by Scene, freed by asset_scene_free. */
    SceneTextureSource *texture_sources;
    u32                 texture_source_count;
} Scene;

/* R607: rebind manifest-wired textures into a scene's materials — the GPU
 * half of the BSCN material roundtrip. Precondition: the manifest
 * (scene->resources) is loaded and scene->materials is populated (call
 * scene_rebuild_materials_from_manifest first for BSCN-loaded scenes).
 * For every material resource entry, each tex_slots[k] naming a texture
 * entry with a non-empty path is loaded from base_dir + '/' + path
 * (path as-is when base_dir is NULL/empty) and assigned to the material's
 * k-th slot (albedo/mr/normal/emissive/occlusion). Best-effort: missing
 * files / unknown refs keep the slot's current handle; slots already
 * holding a valid handle are never touched. Repeated references share one
 * load (generational handles make the duplicate destroy in
 * asset_scene_free a no-op, same as R426). Returns the number of slots
 * rebound. */
u32      asset_scene_rebind_textures(AssetCtx *ctx, Scene *scene,
                                     const char *base_dir);

/* out_scene must be zero-initialized before the call (memset or {}): failure
 * paths unwind via asset_scene_free(ctx, out_scene), which frees whatever the
 * pointer fields hold. All in-tree callers zero it first. */
bool   asset_load_gltf(AssetCtx *ctx, const char *path, Scene *out_scene);
void   asset_scene_free(AssetCtx *ctx, Scene *scene);
void   scene_compute_world_transforms(Scene *scene);

/* ---- Async loading interface ---- */
typedef void (*AssetAsyncCallback)(void *user_data, void *data, u32 size);

u64  asset_load_texture_async(AssetCtx *ctx, const char *path,
                              AssetAsyncCallback cb, void *user);
u64  asset_load_file_async(AssetCtx *ctx, const char *path,
                           AssetAsyncCallback cb, void *user);
