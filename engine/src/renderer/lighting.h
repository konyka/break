#pragma once
#include <core/types.h>
#include <rhi/rhi.h>
#include <math/math.h>
#include <renderer/point_shadow.h>

#define CLUSTER_X 16
#define CLUSTER_Y 8
#define CLUSTER_Z 24
#define CLUSTER_COUNT (CLUSTER_X * CLUSTER_Y * CLUSTER_Z)
#define LIGHT_MAX_POINT 256
#define LIGHT_MAX_DIR 4
#define LIGHT_MAX_PER_CLUSTER 128

typedef struct {
    f32 pos[3];
    f32 radius;
    f32 color[3];
    f32 shadow_index; /* cubemap slot index, or -1.0f if no shadow */
} PointLight;

typedef struct {
    f32 dir[3];
    f32 _pad0;
    f32 color[3];
    f32 _pad1;
} DirLight;

typedef struct {
    RHIDevice     *device;
    PointLight     point_lights[LIGHT_MAX_POINT];
    DirLight       dir_lights[LIGHT_MAX_DIR];
    u32            point_count;
    u32            dir_count;

    RHIBuffer      light_data_buf;
    RHIBuffer      light_grid_buf;

    /* GPU cluster binning (replaces light_system_cull when available). */
    RHIPipeline    cluster_cull_pipeline;
    bool           gpu_cull;
    i32            cc_loc_vp;
    i32            cc_loc_params0;
    i32            cc_loc_params1;

    u32            grid_offsets_counts[CLUSTER_COUNT * 2];
    u32            grid_indices[CLUSTER_COUNT * LIGHT_MAX_PER_CLUSTER];
    u32            grid_index_total;

    f32            near_plane;
    f32            far_plane;
    u32            screen_w;
    u32            screen_h;
    /* Pointer to external cascade VP array (avoids 256-byte memcpy per frame).
     * Set via light_system_set_cascade_vp(); falls back to identity matrices when NULL. */
    const Mat4    *cascade_vp_src;

    /* Persistent staging buffers (avoids per-frame calloc/free). */
    u8            *_upload_buf;      /* max-size for light_data upload   */
    usize          _upload_buf_size;
    u32           *_grid_buf;        /* max-size for grid_data upload    */
    usize          _grid_buf_size;

    /* Cached cluster depth LUT (avoids 25 powf per cull call). */
    f32            _z_depths[CLUSTER_Z + 1];
    bool           _z_depths_dirty;
} LightSystem;

void light_system_init(LightSystem *ls, RHIDevice *dev);
void light_system_shutdown(LightSystem *ls);
void light_system_add_point(LightSystem *ls, f32 x, f32 y, f32 z, f32 r, f32 cr, f32 cg, f32 cb);
void light_system_add_dir(LightSystem *ls, f32 dx, f32 dy, f32 dz, f32 cr, f32 cg, f32 cb);
void light_system_clear(LightSystem *ls);
void light_system_cull(LightSystem *ls, const Mat4 *view, const Mat4 *proj, u32 screen_w, u32 screen_h);
void light_system_upload(LightSystem *ls);

/* Uploads only the light_data buffer (point/dir lights + cascade matrices),
 * leaving the cluster grid to be produced on the GPU.  Use with the GPU cull
 * path instead of light_system_upload (which also uploads a CPU-built grid). */
void light_system_upload_lights(LightSystem *ls);

/* Fill PointLight.shadow_index from the active point-shadow system.
 * Lights with no shadow get -1.0f; shadow-casting lights get their cubemap slot
 * index (0..3). Call before light_system_upload/light_system_upload_lights. */
void light_system_set_point_shadow_indices(LightSystem *ls, const PointShadowSystem *ps);

/* Bind external cascade VP array pointer (avoids 256-byte memcpy per frame).
 * Pass NULL to fall back to identity matrices.  Safe to call every frame. */
static inline void light_system_set_cascade_vp(LightSystem *ls, const Mat4 *src) {
    ls->cascade_vp_src = src;
}

/* Loads the cluster_cull.comp pipeline; returns true and sets ls->gpu_cull on
 * success.  When enabled, call light_system_cull_gpu each frame in place of the
 * CPU light_system_cull. */
bool light_system_init_gpu_cull(LightSystem *ls);

/* Records a GPU light-binning dispatch into `cmd`: bins point lights into the
 * cluster grid buffer (consumed by the PBR fragment shader as a texel buffer).
 * Must be called inside a frame before the clustered geometry draw; it suspends
 * the active render pass for the compute dispatch and inserts a barrier.
 * `vp` is the pre-computed proj*view matrix (avoids redundant mat4_mul). */
void light_system_cull_gpu(LightSystem *ls, RHICmdBuffer *cmd,
                           const f32 *vp, u32 screen_w, u32 screen_h);
