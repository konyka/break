#pragma once
#include <math/math.h>
#include <rhi/rhi.h>

#define WORLD_FAKE_MAX_DRAWS 64u
#define WORLD_FAKE_MAX_PIPELINES 8u
#define WORLD_FAKE_INSTANCE_BYTES (1024u * 64u)

typedef struct WorldFakeUniforms {
    Mat4 view;
    Mat4 projection;
    Vec3 sun_dir;
    Vec3 sun_color;
    Vec3 ambient;
    Vec3 camera;
    Vec3 base_color;
    f32 fog;
    f32 roughness;
    i32 instance_offset;
} WorldFakeUniforms;

typedef struct WorldFakeDraw {
    RHIPipeline pipeline;
    RHIBuffer vertex;
    RHIBuffer index;
    RHITexture texture;
    RHISampler sampler;
    WorldFakeUniforms uniforms;
    u32 vertex_count;
    u32 index_count;
    u32 instance_count;
} WorldFakeDraw;

typedef struct WorldFakeRhi {
    bool vulkan;
    bool fail_pipeline;
    u32 pipeline_fail_on_call;
    u32 pipeline_create_calls;
    bool fail_bindings;
    u32 next_handle;
    u32 live_shaders;
    u32 live_pipelines;
    u32 live_bindings;
    u32 live_buffers;
    u32 live_textures;
    u32 live_samplers;
    u32 pipeline_count;
    RHIPipelineDesc pipeline_descs[WORLD_FAKE_MAX_PIPELINES];
    RHIPipeline current_pipeline;
    RHIBuffer current_vertex;
    RHIBuffer current_index;
    RHITexture current_texture;
    RHISampler current_sampler;
    WorldFakeUniforms uniforms;
    WorldFakeDraw draws[WORLD_FAKE_MAX_DRAWS];
    u32 draw_count;
    u32 update_count;
    usize update_size;
    u8 instance_data[WORLD_FAKE_INSTANCE_BYTES];
    RHIBuffer texel_buffer;
} WorldFakeRhi;

extern WorldFakeRhi g_world_fake;
void world_fake_reset(bool vulkan);
