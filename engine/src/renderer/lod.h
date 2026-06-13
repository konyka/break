#pragma once
#include <core/types.h>
#include <math/math.h>
#include <rhi/rhi.h>

#define LOD_MAX_LEVELS 4
#define LOD_MAX_GROUPS 4096

/* ---- Mesh reference for each LOD level ---- */
typedef struct {
    RHIBuffer vertex_buf;
    RHIBuffer index_buf;
    u32       index_count;
    u32       vertex_count;
} LODMesh;

/* ---- A group of meshes at different detail levels ---- */
typedef struct {
    LODMesh meshes[LOD_MAX_LEVELS];       /* LOD 0 = highest quality */
    f32     thresholds[LOD_MAX_LEVELS];   /* switch distance thresholds (world units) */
    f32     thresholds_sq[LOD_MAX_LEVELS];/* squared thresholds for dist² comparison */
    u32     vertex_counts[LOD_MAX_LEVELS];/* per-level vertex count (for stats) */
    u32     level_count;                  /* actual LOD levels (1-4) */
    f32     bounding_radius;              /* bounding sphere radius for screen-size calc */
    u32     entity_id;                    /* owning entity for O(1) unregister */
} LODGroup;

/* ---- System state ---- */
typedef struct {
    LODGroup groups[LOD_MAX_GROUPS];
    u32      entity_to_group[LOD_MAX_GROUPS];  /* entity ID -> group index mapping */
    u32      current_levels[LOD_MAX_GROUPS];   /* currently selected LOD level per entity */
    u32      count;                            /* number of registered LOD groups */

    /* Configuration */
    f32  bias;              /* global LOD bias (>0 lowers quality, <0 raises it) */
    bool use_screen_size;  /* true=screen-fraction strategy, false=distance strategy */
    f32  screen_threshold; /* base threshold for screen-fraction mode */

    /* Per-frame statistics */
    u32 total_triangles_saved;
    u32 lod_transitions_this_frame;
} LODSystem;

/* ---- Lifecycle ---- */
void lod_init(LODSystem *sys);
void lod_shutdown(LODSystem *sys);

/* ---- Registration ---- */
void lod_register(LODSystem *sys, u32 entity, const LODGroup *group);
void lod_unregister(LODSystem *sys, u32 entity);

/* ---- Single-entity LOD selection ---- */
u32 lod_select(LODSystem *sys, u32 entity, Vec3 object_pos, Vec3 camera_pos, f32 fov);

/* ---- Batch update all entities (call once per frame) ---- */
void lod_update_all(LODSystem *sys, Vec3 camera_pos, f32 fov,
                    const Vec3 *positions, u32 count);

/* ---- Query ---- */
LODMesh lod_get_mesh(LODSystem *sys, u32 entity);
u32     lod_get_level(LODSystem *sys, u32 entity);

/* ---- Configuration ---- */
void lod_set_bias(LODSystem *sys, f32 bias);
void lod_set_strategy(LODSystem *sys, bool use_screen_size);

/* ---- Helper: auto-generate thresholds from base distance ---- */
void lod_group_set_auto_thresholds(LODGroup *group, f32 base_distance);
