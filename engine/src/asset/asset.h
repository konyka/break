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
    float      base_color[4];
    float      metallic_factor;
    float      roughness_factor;
    float      emissive_strength;
    AlphaMode  alpha_mode;
    float      alpha_cutoff;
    void      *_material_ptr;
} Material;

typedef struct {
    RHIBuffer vertex_buf;
    RHIBuffer index_buf;
    u32       index_count;
    u32       material_idx;
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
} Scene;

bool   asset_load_gltf(AssetCtx *ctx, const char *path, Scene *out_scene);
void   asset_scene_free(AssetCtx *ctx, Scene *scene);
void   scene_compute_world_transforms(Scene *scene);
