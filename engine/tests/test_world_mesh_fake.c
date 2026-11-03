#include "test_framework.h"
#include "world_fake_rhi.h"
#include <renderer/mesh_gpu.h>

static MeshMaterial material_with_texture(RHITexture texture, RHISampler sampler) {
    MeshMaterial material;
    memset(&material, 0, sizeof(material));
    material.base_color = vec3(0.5f, 0.25f, 1.0f);
    material.roughness = 0.75f;
    material.albedo = texture;
    material.sampler = sampler;
    return material;
}

TEST(lit_mesh_binds_material_and_time_of_day) {
    world_fake_reset(false);
    RHIDevice *dev = (RHIDevice *)1;
    RHICmdBuffer *cmd = (RHICmdBuffer *)1;
    MeshPipeline pipe;
    ASSERT_TRUE(mesh_pipeline_create_lit(dev, &pipe, false));

    u8 red[4] = {255, 0, 0, 255};
    RHITextureDesc texture_desc = {1, 1, RHI_FORMAT_R8G8B8A8_UNORM, 1, red};
    RHITexture texture = rhi_texture_create(dev, &texture_desc);
    RHISamplerDesc sampler_desc = {RHI_FILTER_NEAREST, RHI_FILTER_NEAREST,
                                   RHI_WRAP_REPEAT, RHI_WRAP_REPEAT, RHI_WRAP_REPEAT};
    RHISampler sampler = rhi_sampler_create(dev, &sampler_desc);
    MeshMaterial material = material_with_texture(texture, sampler);
    Mat4 view = mat4_identity();
    Mat4 projection = mat4_identity();
    TimeOfDayLighting lighting;
    lighting.sun_dir = vec3(0.0f, 1.0f, 0.0f);
    lighting.sun_color = vec3(0.8f, 0.7f, 0.6f);
    lighting.ambient = vec3(0.1f, 0.2f, 0.3f);
    lighting.fog = 0.4f;

    rhi_cmd_bind_pipeline(cmd, pipe.pipeline);
    mesh_pipeline_bind_frame(cmd, &pipe, &view, &projection, &lighting, vec3(1, 2, 3));
    mesh_pipeline_bind_material(cmd, &pipe, &material, RHI_HANDLE_NULL, RHI_HANDLE_NULL);
    MeshGpu gpu = {{20, 20}, {21, 21}};
    MeshDrawDesc desc = {4, 36, 6};
    ASSERT_TRUE(mesh_gpu_draw_desc(cmd, &gpu, &desc, 1u));
    ASSERT_EQ(g_world_fake.draw_count, 1u);
    WorldFakeDraw *draw = &g_world_fake.draws[0];
    ASSERT_EQ(draw->texture.index, texture.index);
    ASSERT_EQ(draw->sampler.index, sampler.index);
    ASSERT_EQ(draw->index_count, 6u);
    ASSERT_FLOAT_EQ(draw->uniforms.base_color.e[0], 0.5f, 1e-6);
    ASSERT_FLOAT_EQ(draw->uniforms.roughness, 0.75f, 1e-6);
    ASSERT_FLOAT_EQ(draw->uniforms.sun_color.e[1], 0.7f, 1e-6);
    ASSERT_FLOAT_EQ(draw->uniforms.ambient.e[2], 0.3f, 1e-6);
    ASSERT_FLOAT_EQ(draw->uniforms.fog, 0.4f, 1e-6);
    ASSERT_FLOAT_EQ(draw->uniforms.camera.e[2], 3.0f, 1e-6);
    ASSERT_FLOAT_EQ(draw->uniforms.projection.e[3][3], 1.0f, 1e-6);

    mesh_pipeline_bind_material(cmd, &pipe, &material, texture, sampler);
    material.albedo = RHI_HANDLE_NULL;
    material.sampler = RHI_HANDLE_NULL;
    mesh_pipeline_bind_material(cmd, &pipe, &material, texture, sampler);
    ASSERT_EQ(g_world_fake.current_texture.index, texture.index);
    mesh_pipeline_destroy(dev, &pipe);
    rhi_texture_destroy(dev, texture);
    rhi_sampler_destroy(dev, sampler);
    ASSERT_EQ(g_world_fake.live_pipelines, 0u);
    ASSERT_EQ(g_world_fake.live_bindings, 0u);
}

TEST(lit_mesh_supports_vulkan_instance_bindings_and_fails_atomically) {
    world_fake_reset(true);
    RHIDevice *dev = (RHIDevice *)1;
    MeshPipeline pipe;
    ASSERT_TRUE(mesh_pipeline_create_lit(dev, &pipe, true));
    ASSERT_TRUE(g_world_fake.pipeline_descs[0].is_instanced);
    ASSERT_TRUE(g_world_fake.pipeline_descs[0].uses_texel_buffer);
    ASSERT_EQ(g_world_fake.pipeline_descs[0].vertex_stride, 36u);
    mesh_pipeline_destroy(dev, &pipe);
    ASSERT_EQ(g_world_fake.live_pipelines, 0u);
    ASSERT_EQ(g_world_fake.live_shaders, 0u);

    g_world_fake.fail_bindings = true;
    ASSERT_FALSE(mesh_pipeline_create_lit(dev, &pipe, false));
    ASSERT_FALSE(rhi_handle_valid(pipe.pipeline));
    ASSERT_EQ(g_world_fake.live_pipelines, 0u);
    ASSERT_EQ(g_world_fake.live_shaders, 0u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(lit_mesh_binds_material_and_time_of_day);
    RUN_TEST(lit_mesh_supports_vulkan_instance_bindings_and_fails_atomically);
TEST_MAIN_END()
