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

/* ---- Screen-space geometric error selection (runtime mega LOD) ----
 * errors[l] is the world-space geometric error of level l relative to LOD0
 * (errors[0] = 0, non-decreasing). A level is acceptable when its error
 * projects to <= pixel_err pixels. Returns the coarsest acceptable level,
 * with a hysteresis band of +-LOD_SCREEN_HYSTERESIS around pixel_err:
 * coarsening needs the coarser level at <= pixel_err*(1-h), refining starts
 * only once the current level exceeds pixel_err*(1+h), so a camera hovering
 * near a threshold never flips back and forth. */
#define LOD_SCREEN_HYSTERESIS 0.2f
#define LOD_SCREEN_MIN_DIST   1e-3f

/* Pixels per world unit at distance 1: screen_h / (2 * tan(fov/2)). */
f32 lod_screen_proj_factor(f32 fov, f32 screen_h);

/* dist = distance from the camera to the nearest point of the object's
 * bounding sphere (clamped to LOD_SCREEN_MIN_DIST). */
u32 lod_select_by_screen_error(const f32 *errors, u32 count, f32 dist,
                               f32 proj_factor, f32 pixel_err, u32 current_level);

/* Convenience form: distance from |center - cam_pos| - radius. */
u32 lod_select_screen_error(const f32 *errors, u32 count, Vec3 center, f32 radius,
                            Vec3 cam_pos, f32 fov, f32 screen_h, f32 pixel_err,
                            u32 current_level);

/* ---- Instanced draws grouped by (mesh, level) (runtime ECS LOD) ----
 * Stable counting sort of count instances into mesh_count * levels buckets,
 * key = mesh * levels + level (mesh-major, so all-LOD0 input yields the
 * per-mesh order of an ungrouped draw). inst_level may be NULL (all LOD0);
 * levels >= levels clamp to levels - 1; instances with mesh >= mesh_count
 * are dropped. offsets receives mesh_count * levels + 1 entries: bucket k is
 * order[offsets[k] .. offsets[k + 1]). Returns the number of kept instances
 * (offsets[last]); 0 on invalid arguments. */
u32 lod_bucket_instances(const u32 *inst_mesh, const u8 *inst_level, u32 count,
                         u32 mesh_count, u32 levels, u32 *offsets, u32 *order);

/* Per-instance hysteresis state for lod_select_by_screen_error, keyed by a
 * slot (e.g. entity index) and a tag that changes when the slot is reused
 * (e.g. entity generation + 1; tag 0 = never set). A slot whose stored tag
 * differs starts from LOD0. Slots >= capacity select statelessly from LOD0.
 * *changed (optional) is set when a tracked slot's level changed. */
typedef struct {
    u8  *level;     /* [capacity] */
    u32 *tag;       /* [capacity] */
    u32  capacity;
} LodInstanceState;

u32 lod_instance_select(LodInstanceState *st, u32 slot, u32 tag,
                        const f32 *errors, u32 count, f32 dist, f32 proj_factor,
                        f32 pixel_err, bool *changed);
/* Stored level for (slot, tag) without updating it; 0 if not tracked. */
u32 lod_instance_level(const LodInstanceState *st, u32 slot, u32 tag);

/* ---- Dithered cross-fade between LOD levels (runtime LOD phase 2.2) ----
 * A level switch shows both levels for fade_s seconds with complementary
 * 4x4 ordered (Bayer) dither: the finer (lower-index) level keeps the pixels
 * whose Bayer threshold is < k, the coarser level keeps the rest, where k
 * (0..16) is the finer level's share in 16ths. Every pixel is covered by
 * exactly one of the two, so no blending or sorting is needed and depth
 * writes stay on. `level` is the committed (target) level -- the hysteresis
 * input of lod_select_by_screen_error, unchanged from phase 1 -- and `from`
 * the level fading out (== level when idle). */
#define LOD_FADE_STEPS 16u

typedef struct {
    u8  level;
    u8  from;
    f64 start;   /* clock time the current fade began */
} LodFade;

/* Idle at level. */
void lod_fade_reset(LodFade *f, u32 level);
/* Apply this frame's selected level at clock time now. fade_s <= 0 switches
 * instantly. A finished fade completes first. A new level while idle starts
 * a fade from the current level. While fading: selecting `from` again
 * reverses the fade with the same finer-level share (no pattern jump);
 * selecting a third level restarts from whichever of the two levels covers
 * more pixels. Returns true when the level changed. */
bool lod_fade_update(LodFade *f, u32 new_level, f64 now, f32 fade_s);
/* k = the finer level's share in 16ths at clock time now (0..16) and the
 * two levels. Idle (or finished): *finer = *coarser = level, k = 16.
 * k == 0 means draw only the coarser level, 16 only the finer one; 1..15
 * means draw both with lod_fade_dither_value(+-k). */
u32 lod_fade_split(const LodFade *f, f64 now, f32 fade_s, u32 *finer, u32 *coarser);
static inline bool lod_fade_active(const LodFade *f) { return f->from != f->level; }

/* The shader's per-draw u_lod_fade value: +k for the finer level, -k for the
 * coarser one (k in 1..15); 0 = no dither. */
static inline f32 lod_fade_dither_value(u32 k, bool finer) {
    return finer ? (f32)k : -(f32)k;
}
/* Reference of the shader test: 4x4 Bayer threshold (0..15) of a pixel and
 * whether a draw with u_lod_fade = value keeps it. */
u32  lod_bayer4(u32 x, u32 y);
bool lod_fade_keep(u32 bayer, f32 value);
