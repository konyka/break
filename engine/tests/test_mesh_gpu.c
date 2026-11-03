#include "test_framework.h"
#include <renderer/mesh_gpu.h>

bool rhi_device_get_capabilities(const RHIDevice *dev, RHICapabilities *out) {
    (void)dev;
    (void)out;
    return false;
}

TEST(mesh_gpu_rejects_a_null_device_and_command) {
    Decal decal;
    memset(&decal, 0, sizeof(decal));
    decal.position = vec3(0.0f, 1.0f, 0.0f);
    decal.normal = vec3(0.0f, 1.0f, 0.0f);
    decal.size = 1.0f;
    decal.material = 1;
    MeshBuffer mesh;
    u32 dropped = 0;
    ASSERT_TRUE(mesh_buffer_from_decals(&mesh, &decal, 1, &dropped));
    ASSERT_EQ(mesh.index_count, 6u);

    MeshGpu gpu;
    gpu.vertex = RHI_HANDLE_NULL;
    gpu.index = RHI_HANDLE_NULL;
    ASSERT_FALSE(mesh_gpu_upload(NULL, &mesh, &gpu));
    ASSERT_FALSE(rhi_handle_valid(gpu.vertex));
    ASSERT_FALSE(rhi_handle_valid(gpu.index));
    ASSERT_FALSE(mesh_gpu_draw(NULL, &mesh, &gpu));
    MeshPipeline pipe;
    ASSERT_FALSE(mesh_pipeline_create(NULL, &pipe));
    ASSERT_FALSE(rhi_handle_valid(pipe.pipeline));
    ASSERT_FALSE(mesh_gpu_upload(NULL, NULL, &gpu));
}

TEST_MAIN_BEGIN()
    RUN_TEST(mesh_gpu_rejects_a_null_device_and_command);
TEST_MAIN_END()
