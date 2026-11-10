#include "test_framework.h"
#include <renderer/mesh_gpu.h>
#include <platform/platform.h>

int main(void) {
    printf("=== Running Tests ===\n");
    (void)g_test_count;
    (void)g_test_pass;
    const PlatformConfig config = {.width = 64, .height = 64, .title = "mesh gpu"};
    Platform *platform = platform_create(&config);
    if (!platform) {
        printf("UNAVAILABLE backend=opengl reason=wayland-platform-create\n");
        return 77;
    }
    u32 width = 0, height = 0;
    platform_get_drawable_size(platform, &width, &height);
    RHIDevice *device = rhi_device_create(RHI_BACKEND_OPENGL,
                                          platform_window_native(platform),
                                          platform_display_native(platform),
                                          width, height);
    if (!device) {
        platform_destroy(platform);
        printf("UNAVAILABLE backend=opengl reason=device-create\n");
        return 77;
    }
    RHIDeviceInfo info;
    memset(&info, 0, sizeof(info));
    (void)rhi_device_get_info(device, &info);
    printf("GPU RUNTIME backend=opengl device=%s\n", info.device_name);

    Decal decal;
    memset(&decal, 0, sizeof(decal));
    decal.position = vec3(0.0f, 0.0f, 0.0f);
    decal.normal = vec3(0.0f, 1.0f, 0.0f);
    decal.size = 2.0f;
    decal.material = 2;
    MeshBuffer mesh;
    u32 dropped = 0;
    if (!mesh_buffer_from_decals(&mesh, &decal, 1, &dropped) || mesh.index_count != 6u) {
        printf("  FAIL: decal mesh was not indexed\n");
        g_test_fail++;
    }
    MeshGpu gpu;
    if (g_test_fail == 0 && !mesh_gpu_upload(device, &mesh, &gpu)) {
        printf("  FAIL: mesh_gpu_upload rejected a live GL device\n");
        g_test_fail++;
    }
    MeshPipeline pipe;
    memset(&pipe, 0, sizeof(pipe));
    if (g_test_fail == 0 && !mesh_pipeline_create(device, &pipe)) {
        printf("  FAIL: mesh pipeline was not created\n");
        g_test_fail++;
    }
    if (g_test_fail == 0 && !rhi_handle_valid(pipe.pipeline)) {
        printf("  FAIL: pipeline handle was null\n");
        g_test_fail++;
    }
    if (g_test_fail == 0 && (!rhi_handle_valid(gpu.vertex) || !rhi_handle_valid(gpu.index))) {
        printf("  FAIL: GL buffer handle was null\n");
        g_test_fail++;
    }
    u8 shot[64 * 64 * 4];
    bool captured = false;
    for (int frame = 0; frame < 3 && g_test_fail == 0; frame++) {
        RHICmdBuffer *cmd = rhi_frame_begin(device);
        if (!cmd) {
            printf("  FAIL: frame begin returned null\n");
            g_test_fail++;
            break;
        }
        rhi_cmd_begin_render_pass(cmd);
        rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 0.0f, 1.0f);
        if (!mesh_gpu_draw_with_pipeline(cmd, &pipe, &mesh, &gpu)) {
            printf("  FAIL: mesh_gpu_draw rejected the frame\n");
            g_test_fail++;
        }
        rhi_cmd_end_render_pass(cmd);
        rhi_frame_end(device);
        if (frame == 2)
            captured = rhi_screenshot(device, 0u, 0u, 64u, 64u, shot, sizeof(shot));
        rhi_present(device);
    }
    if (g_test_fail == 0 && !captured) {
        printf("  FAIL: screenshot failed\n");
        g_test_fail++;
    }
    if (g_test_fail == 0) {
        const u8 *px = &shot[(32u * 64u + 32u) * 4u];
        if (px[0] < 200u) {
            printf("  FAIL: center pixel R=%u G=%u B=%u, shader did not cover it\n",
                   px[0], px[1], px[2]);
            g_test_fail++;
        }
    }
    mesh_pipeline_destroy(device, &pipe);
    mesh_gpu_destroy(device, &gpu);
    rhi_device_destroy(device);
    platform_destroy(platform);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_fail == 0 ? 1 : 0, g_test_fail, 1);
    if (g_test_fail == 0) {
        printf("PASS backend=opengl device=%s\n", info.device_name);
    }
    return g_test_fail > 0 ? 1 : 0;
}
