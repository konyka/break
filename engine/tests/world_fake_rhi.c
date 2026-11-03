#include "world_fake_rhi.h"
#include <string.h>

WorldFakeRhi g_world_fake;

struct RHIPipelineBindings {
    RHIPipeline pipeline;
};

static RHIPipelineBindings g_bindings[WORLD_FAKE_MAX_PIPELINES];

static RHIHandle handle(void) {
    g_world_fake.next_handle++;
    return (RHIHandle){g_world_fake.next_handle, g_world_fake.next_handle};
}

void world_fake_reset(bool vulkan) {
    memset(&g_world_fake, 0, sizeof(g_world_fake));
    memset(g_bindings, 0, sizeof(g_bindings));
    g_world_fake.vulkan = vulkan;
}

bool rhi_device_get_capabilities(const RHIDevice *dev, RHICapabilities *out) {
    if (!dev || !out) return false;
    memset(out, 0, sizeof(*out));
    out->backend = g_world_fake.vulkan ? RHI_BACKEND_VULKAN : RHI_BACKEND_OPENGL;
    out->shader_variant = g_world_fake.vulkan ? RHI_SHADER_VARIANT_GLSL_VK : RHI_SHADER_VARIANT_GLSL;
    out->push_constants_supported = g_world_fake.vulkan;
    out->max_push_constant_size = g_world_fake.vulkan ? 256u : 0u;
    return true;
}

RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment) {
    (void)source;
    (void)len;
    (void)is_fragment;
    if (!dev) return RHI_HANDLE_NULL;
    g_world_fake.live_shaders++;
    return handle();
}

void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    (void)dev;
    if (rhi_handle_valid(shader) && g_world_fake.live_shaders > 0u) g_world_fake.live_shaders--;
}

RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    g_world_fake.pipeline_create_calls++;
    if (!dev || !desc || g_world_fake.fail_pipeline ||
        (g_world_fake.pipeline_fail_on_call > 0u &&
         g_world_fake.pipeline_create_calls == g_world_fake.pipeline_fail_on_call))
        return RHI_HANDLE_NULL;
    if (g_world_fake.pipeline_count < WORLD_FAKE_MAX_PIPELINES)
        g_world_fake.pipeline_descs[g_world_fake.pipeline_count++] = *desc;
    g_world_fake.live_pipelines++;
    return handle();
}

void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    (void)dev;
    if (rhi_handle_valid(pipe) && g_world_fake.live_pipelines > 0u) g_world_fake.live_pipelines--;
}

RHIPipelineBindings *rhi_pipeline_bindings_create(RHIDevice *dev, RHIPipeline pipe) {
    if (!dev || !rhi_handle_valid(pipe) || g_world_fake.fail_bindings) return NULL;
    for (u32 i = 0; i < WORLD_FAKE_MAX_PIPELINES; i++) {
        if (!rhi_handle_valid(g_bindings[i].pipeline)) {
            g_bindings[i].pipeline = pipe;
            g_world_fake.live_bindings++;
            return &g_bindings[i];
        }
    }
    return NULL;
}

void rhi_pipeline_bindings_destroy(RHIDevice *dev, RHIPipelineBindings *bindings) {
    (void)dev;
    if (!bindings) return;
    bindings->pipeline = RHI_HANDLE_NULL;
    if (g_world_fake.live_bindings > 0u) g_world_fake.live_bindings--;
}

static i32 binding_slot(const char *name, bool vulkan) {
    if (!name) return -1;
    if (vulkan) {
        if (strcmp(name, "u_view") == 0) return 0;
        if (strcmp(name, "u_proj") == 0) return 64;
        if (strcmp(name, "u_sun_dir") == 0) return 128;
        if (strcmp(name, "u_fog") == 0) return 140;
        if (strcmp(name, "u_sun_color") == 0) return 144;
        if (strcmp(name, "u_roughness") == 0) return 156;
        if (strcmp(name, "u_ambient") == 0) return 160;
        if (strcmp(name, "u_instance_offset") == 0) return 172;
        if (strcmp(name, "u_camera_pos") == 0) return 176;
        if (strcmp(name, "u_base_color") == 0) return 192;
        return -1;
    }
    if (strcmp(name, "u_view") == 0) return 1;
    if (strcmp(name, "u_proj") == 0) return 2;
    if (strcmp(name, "u_sun_dir") == 0) return 3;
    if (strcmp(name, "u_fog") == 0) return 4;
    if (strcmp(name, "u_sun_color") == 0) return 5;
    if (strcmp(name, "u_roughness") == 0) return 6;
    if (strcmp(name, "u_ambient") == 0) return 7;
    if (strcmp(name, "u_instance_offset") == 0) return 8;
    if (strcmp(name, "u_camera_pos") == 0) return 9;
    if (strcmp(name, "u_base_color") == 0) return 10;
    if (strcmp(name, "u_albedo") == 0) return 11;
    return -1;
}

i32 rhi_pipeline_bindings_resolve(const RHIPipelineBindings *bindings, const char *name) {
    if (!bindings) return -1;
    return binding_slot(name, g_world_fake.vulkan);
}

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    if (!dev || !desc || desc->size == 0u) return RHI_HANDLE_NULL;
    g_world_fake.live_buffers++;
    return handle();
}

void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buffer) {
    (void)dev;
    if (rhi_handle_valid(buffer) && g_world_fake.live_buffers > 0u) g_world_fake.live_buffers--;
}

RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    if (!dev || !desc) return RHI_HANDLE_NULL;
    g_world_fake.live_textures++;
    return handle();
}

void rhi_texture_destroy(RHIDevice *dev, RHITexture texture) {
    (void)dev;
    if (rhi_handle_valid(texture) && g_world_fake.live_textures > 0u) g_world_fake.live_textures--;
}

RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    if (!dev || !desc) return RHI_HANDLE_NULL;
    g_world_fake.live_samplers++;
    return handle();
}

void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    (void)dev;
    if (rhi_handle_valid(sampler) && g_world_fake.live_samplers > 0u) g_world_fake.live_samplers--;
}

void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    (void)cmd;
    g_world_fake.current_pipeline = pipe;
}

void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buffer, usize offset) {
    (void)cmd;
    (void)offset;
    g_world_fake.current_vertex = buffer;
}

void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buffer, usize offset, bool is_u32) {
    (void)cmd;
    (void)offset;
    (void)is_u32;
    g_world_fake.current_index = buffer;
}

void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture texture, RHISampler sampler, u32 unit) {
    (void)cmd;
    (void)unit;
    g_world_fake.current_texture = texture;
    g_world_fake.current_sampler = sampler;
}

static bool is_vk_offset(i32 location, i32 offset) {
    return g_world_fake.vulkan && location == offset;
}

void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *matrix) {
    (void)cmd;
    if (!matrix) return;
    if (location == 1 || is_vk_offset(location, 0))
        memcpy(g_world_fake.uniforms.view.e, matrix, sizeof(Mat4));
    else if (location == 2 || is_vk_offset(location, 64))
        memcpy(g_world_fake.uniforms.projection.e, matrix, sizeof(Mat4));
}

void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z) {
    (void)cmd;
    Vec3 value = vec3(x, y, z);
    if (location == 3 || is_vk_offset(location, 128)) g_world_fake.uniforms.sun_dir = value;
    else if (location == 5 || is_vk_offset(location, 144)) g_world_fake.uniforms.sun_color = value;
    else if (location == 7 || is_vk_offset(location, 160)) g_world_fake.uniforms.ambient = value;
    else if (location == 9 || is_vk_offset(location, 176)) g_world_fake.uniforms.camera = value;
    else if (location == 10 || is_vk_offset(location, 192)) g_world_fake.uniforms.base_color = value;
}

void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 value) {
    (void)cmd;
    if (location == 4 || is_vk_offset(location, 140)) g_world_fake.uniforms.fog = value;
    else if (location == 6 || is_vk_offset(location, 156)) g_world_fake.uniforms.roughness = value;
}

void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 value) {
    (void)cmd;
    if (location == 8 || is_vk_offset(location, 172)) g_world_fake.uniforms.instance_offset = value;
}

static void record_draw(u32 vertex_count, u32 index_count, u32 instance_count) {
    if (g_world_fake.draw_count >= WORLD_FAKE_MAX_DRAWS) return;
    WorldFakeDraw *draw = &g_world_fake.draws[g_world_fake.draw_count++];
    draw->pipeline = g_world_fake.current_pipeline;
    draw->vertex = g_world_fake.current_vertex;
    draw->index = g_world_fake.current_index;
    draw->texture = g_world_fake.current_texture;
    draw->sampler = g_world_fake.current_sampler;
    draw->uniforms = g_world_fake.uniforms;
    draw->vertex_count = vertex_count;
    draw->index_count = index_count;
    draw->instance_count = instance_count;
}

void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    (void)cmd;
    record_draw(vertex_count, 0u, instance_count);
}

void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count) {
    (void)cmd;
    record_draw(0u, index_count, instance_count);
}

void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buffer, usize offset,
                           const void *data, usize size) {
    (void)cmd;
    (void)buffer;
    if (!data || offset > WORLD_FAKE_INSTANCE_BYTES || size > WORLD_FAKE_INSTANCE_BYTES - offset) return;
    memcpy(g_world_fake.instance_data + offset, data, size);
    g_world_fake.update_count++;
    g_world_fake.update_size = size;
}

void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1) {
    (void)cmd;
    (void)buf1;
    g_world_fake.texel_buffer = buf0;
}
