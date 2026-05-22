#pragma once
#include <core/types.h>
#include <rhi/rhi.h>
#include <math/math.h>

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
    f32 _pad;
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

    u32            grid_offsets_counts[CLUSTER_COUNT * 2];
    u32            grid_indices[CLUSTER_COUNT * LIGHT_MAX_PER_CLUSTER];
    u32            grid_index_total;

    f32            near_plane;
    f32            far_plane;
    u32            screen_w;
    u32            screen_h;
    Mat4           cascade_vp[4];
} LightSystem;

void light_system_init(LightSystem *ls, RHIDevice *dev);
void light_system_shutdown(LightSystem *ls);
void light_system_add_point(LightSystem *ls, f32 x, f32 y, f32 z, f32 r, f32 cr, f32 cg, f32 cb);
void light_system_add_dir(LightSystem *ls, f32 dx, f32 dy, f32 dz, f32 cr, f32 cg, f32 cb);
void light_system_clear(LightSystem *ls);
void light_system_cull(LightSystem *ls, const f32 *view, const f32 *proj, u32 screen_w, u32 screen_h);
void light_system_upload(LightSystem *ls);
