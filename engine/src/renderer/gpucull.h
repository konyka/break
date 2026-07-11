#pragma once

#include <rhi/rhi.h>

#define GPUCULL_MAX_OBJECTS 4096
#define GPUCULL_MAX_DRAWS   8192

/* Draw command for indirect drawing */
typedef struct {
    u32 index_count;
    u32 instance_count;
    u32 first_index;
    i32 vertex_offset;
    u32 first_instance;
} GPUCullDrawCmd;

/* Per-object data for unified culling */
typedef struct {
    f32 position[4];      /* xyz = center, w = bounding_radius */
    f32 aabb_min[4];      /* xyz = aabb min, w = unused */
    f32 aabb_max[4];      /* xyz = aabb max, w = unused */
    u32 draw_cmd_index;   /* Index into draw commands buffer */
    u32 material_id;      /* For sorting/state changes */
    u32 flags;            /* Bit 0: static, Bit 1: always_visible */
    u32 pad;
} GPUCullObject;

typedef struct {
    RHIDevice      *device;
    RHIPipeline     cull_pipe;           /* Legacy frustum-only culling */
    RHIPipeline     unified_cull_pipe;   /* Unified frustum+occlusion+compact */
    RHIBuffer       object_ssbo;         /* Input: object data */
    RHIBuffer       draw_cmds_ssbo;      /* Input: draw commands */
    RHIBuffer       visible_ssbo;        /* Output: visible object indices */
    RHIBuffer       visible_draws_ssbo;  /* Output: compacted draw commands */
    RHIBuffer       count_buf;           /* Atomic counter for visible count */
    RHIBuffer       draw_count_buf;      /* Atomic counter for draw count */
    RHIBuffer       visible_flags_ssbo;  /* Per-object visibility (1/0) from unified cull */
    RHIBuffer       vis_flags_staging[2]; /* R172: per in-flight frame slot */
    RHISampler      hi_z_sampler;        /* Nearest sampler for unified Hi-Z reads */
    RHITexture      hi_z_fallback;       /* 1x1 placeholder when Hi-Z disabled */
    u32             object_count;
    u32             draw_count;
    bool            ready;
    bool            unified_ready;       /* Unified pipeline initialized */
    bool            objects_uploaded;    /* R193-B: skip redundant DL object_ssbo staging */
    bool            vis_flags_staging_valid[2]; /* R172: per-slot completed GPU copy */

    /* Cached uniform locations (legacy pipeline) */
    i32             _loc_cull_vp;
    i32             _loc_cull_count;
    /* Cached uniform locations (unified pipeline) */
    i32             _loc_uni_vp;
    i32             _loc_uni_count;
    i32             _loc_uni_hz_w;
    i32             _loc_uni_hz_h;
    i32             _loc_uni_use;
    i32             _loc_uni_write;  /* R169: skip draw compaction when flags-only */

    /* Persistent staging buffers (avoid per-frame malloc/free) */
    f32            *_pack_buf;
    usize           _pack_buf_cap;      /* capacity in f32 elements */
    u32            *_zero_buf;
    usize           _zero_buf_cap;      /* capacity in u32 elements */
    GPUCullDrawCmd *_zero_draws;        /* unused after R171 GPU fill; kept NULL */
} GPUCullSystem;

/* Legacy API */
bool gpucull_init(GPUCullSystem *gc, RHIDevice *dev);
void gpucull_shutdown(GPUCullSystem *gc);
void gpucull_update_objects(GPUCullSystem *gc, const f32 *positions, const f32 *radii, u32 count);
void gpucull_dispatch(GPUCullSystem *gc, RHICmdBuffer *cmd, const f32 *vp);

/*
 * GPU frustum cull writing per-object visibility flags (1/0) directly into an
 * external flags buffer (e.g. an IndirectDrawSystem's visibility buffer), so
 * GPU compaction can consume the result with no CPU readback. The flags buffer
 * must hold at least gc->object_count u32 entries, one per object in the same
 * order the objects were uploaded.
 */
void gpucull_dispatch_flags(GPUCullSystem *gc, RHICmdBuffer *cmd,
                            const f32 *vp, RHIBuffer flags_buf);

void gpucull_get_results(GPUCullSystem *gc, u32 *out_visible_count);

/* Unified culling API - combines frustum + occlusion + compact in single pass */
bool gpucull_init_unified(GPUCullSystem *gc, RHIDevice *dev);
void gpucull_upload_draw_cmds(GPUCullSystem *gc, const GPUCullDrawCmd *cmds, u32 count);
void gpucull_upload_objects_unified(GPUCullSystem *gc, const GPUCullObject *objects, u32 count);

/*
 * Dispatch unified culling:
 *   - Frustum culling using view-projection matrix
 *   - Hierarchical Z-buffer occlusion culling when `hi_z_texture` is valid
 *     (uses previous frame's Hi-Z pyramid, 1-frame latency)
 *   - Compaction of visible draws into indirect draw buffer when compact_draws
 *   - Copies vis flags to staging for next-frame CPU readback only when
 *     stage_readback is set (main-camera vis-flags path; R170)
 */
void gpucull_dispatch_unified(GPUCullSystem *gc, RHICmdBuffer *cmd,
                              const f32 *vp, const f32 *camera_pos,
                              RHITexture hi_z_texture,
                              u32 hi_z_width, u32 hi_z_height,
                              RHIBuffer vis_flags_out,
                              bool compact_draws,
                              bool stage_readback);

/* Read per-draw visibility flags from the previous frame's staging copy (R169).
 * Returns false if no prior frame is available — caller should treat all as visible. */
bool gpucull_read_vis_flags(GPUCullSystem *gc, u32 count, u32 *out_flags);

/* Get the number of visible objects after unified culling */
void gpucull_get_unified_results(GPUCullSystem *gc, 
                                 u32 *out_visible_objects,
                                 u32 *out_visible_draws);

/* Execute the compacted indirect draws */
void gpucull_execute_indirect_draws(GPUCullSystem *gc, RHIDevice *dev);
