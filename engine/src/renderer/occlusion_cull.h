#pragma once
#include <core/types.h>
#include <math/math.h>
#include <rhi/rhi.h>

#define OCCLUSION_MAX_OBJECTS 16384

typedef struct {
    Vec3 min;
    f32  _pad0;
    Vec3 max;
    f32  _pad1;
} ObjectAABB;

typedef struct {
    /* Hi-Z pyramid texture (R32F, mipchain) */
    RHITexture  hi_z_texture;
    u32         hi_z_width;
    u32         hi_z_height;
    u32         hi_z_levels;

    /* Object data */
    RHIBuffer   aabb_buffer;        /* SSBO: ObjectAABB[max_objects] */
    RHIBuffer   visibility_buffer;  /* SSBO: u32[max_objects] (0=occluded, 1=visible) */
    RHIBuffer   readback_staging[2]; /* R172: per in-flight frame slot */

    /* Compute pipelines */
    RHIPipeline hi_z_pipeline;
    RHIPipeline cull_pipeline;

    /* Sampler for Hi-Z reads */
    RHISampler  hi_z_sampler;

    /* RHI device reference */
    RHIDevice  *device;

    /* State */
    u32         object_count;
    bool        enabled;

    /* Cached uniform locations (populated at init, avoids per-frame lookup). */
    i32         _loc_hi_z_output_size;    /* hi_z_pipeline: pc.output_size (R436: vec4: first-mip size + chunk mip count) */
    i32         _loc_cull_view_proj;      /* cull_pipeline: pc.view_proj   */
    i32         _loc_cull_object_count;   /* cull_pipeline: pc.object_count */
    i32         _loc_cull_hi_z_width;     /* cull_pipeline: pc.hi_z_width  */
    i32         _loc_cull_hi_z_height;    /* cull_pipeline: pc.hi_z_height */

    /* CPU readback (for draw filtering, uses previous frame result) */
    u32        *visibility_readback;
    /* R167-F / R172: Per-slot staging validity after fence wait. */
    bool        staging_valid[2];
    /* R430: entry count actually staged into each slot (may lag object_count). */
    u32         staged_count[2];

    /* R436: compute dispatches issued by the last occlusion_cull_generate_hi_z
     * call (perf observability for the segmented single-pass chain). */
    u32         hi_z_dispatch_count;
} OcclusionCullSystem;

bool occlusion_cull_init(OcclusionCullSystem *sys, RHIDevice *dev, u32 width, u32 height);
void occlusion_cull_shutdown(OcclusionCullSystem *sys);
void occlusion_cull_resize(OcclusionCullSystem *sys, u32 width, u32 height);

/* Per-frame pipeline */
void occlusion_cull_upload_aabbs(OcclusionCullSystem *sys, const ObjectAABB *aabbs, u32 count);
void occlusion_cull_generate_hi_z(OcclusionCullSystem *sys, RHICmdBuffer *cmd, RHITexture depth_buffer);
void occlusion_cull_dispatch(OcclusionCullSystem *sys, RHICmdBuffer *cmd, const Mat4 *view_proj, u32 object_count);
bool occlusion_cull_is_visible(const OcclusionCullSystem *sys, u32 object_index);

/* Statistics */
u32  occlusion_cull_visible_count(const OcclusionCullSystem *sys);
/* R436: dispatches issued by the last Hi-Z generation call (see field above). */
u32  occlusion_cull_hiz_dispatch_count(const OcclusionCullSystem *sys);
