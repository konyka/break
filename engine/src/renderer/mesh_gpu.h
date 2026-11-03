#pragma once
#include <renderer/mesh_buffer.h>
#include <renderer/time_of_day.h>

typedef struct MeshGpu {
    RHIBuffer vertex;
    RHIBuffer index;
} MeshGpu;

typedef struct MeshMaterial {
    Vec3 base_color;
    f32 roughness;
    RHITexture albedo;
    RHISampler sampler;
} MeshMaterial;

typedef struct MeshPipeline {
    RHIShader vert;
    RHIShader frag;
    RHIPipeline pipeline;
    RHIPipelineBindings *bindings;
    i32 loc_view;
    i32 loc_proj;
    i32 loc_sun_dir;
    i32 loc_sun_color;
    i32 loc_ambient;
    i32 loc_fog;
    i32 loc_camera;
    i32 loc_base_color;
    i32 loc_roughness;
    i32 loc_albedo;
    i32 loc_instance_offset;
    bool lit;
    bool instanced;
} MeshPipeline;

bool mesh_gpu_upload(RHIDevice *dev, const MeshBuffer *mesh, MeshGpu *out);
void mesh_gpu_destroy(RHIDevice *dev, MeshGpu *gpu);
bool mesh_pipeline_create(RHIDevice *dev, MeshPipeline *out);
bool mesh_pipeline_create_lit(RHIDevice *dev, MeshPipeline *out, bool instanced);
void mesh_pipeline_destroy(RHIDevice *dev, MeshPipeline *pipe);
void mesh_pipeline_bind_frame(RHICmdBuffer *cmd, const MeshPipeline *pipe,
                              const Mat4 *view, const Mat4 *projection,
                              const TimeOfDayLighting *lighting, Vec3 camera);
void mesh_pipeline_bind_material(RHICmdBuffer *cmd, const MeshPipeline *pipe,
                                 const MeshMaterial *material,
                                 RHITexture white, RHISampler fallback);
void mesh_pipeline_set_instance_offset(RHICmdBuffer *cmd, const MeshPipeline *pipe,
                                       u32 first_instance);
bool mesh_gpu_draw_desc(RHICmdBuffer *cmd, const MeshGpu *gpu,
                        const MeshDrawDesc *desc, u32 instance_count);
bool mesh_gpu_draw(RHICmdBuffer *cmd, const MeshBuffer *mesh, const MeshGpu *gpu);
bool mesh_gpu_draw_with_pipeline(RHICmdBuffer *cmd, const MeshPipeline *pipe,
                                 const MeshBuffer *mesh, const MeshGpu *gpu);
