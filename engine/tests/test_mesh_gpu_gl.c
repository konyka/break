#include "test_framework.h"
#include <renderer/mesh_gpu.h>
#include <platform/platform.h>
#include <X11/Xlib.h>

static bool display_open(void) {
    Display *display = XOpenDisplay(NULL);
    if (!display) return false;
    XCloseDisplay(display);
    return true;
}

int main(void) {
    if (!display_open()) {
        printf("SKIP: no reachable X11 display\n");
        return 77;
    }
    printf("=== Running Tests ===\n");
    (void)g_test_count;
    (void)g_test_pass;
    const PlatformConfig config = {.width = 64, .height = 64, .title = "mesh gpu"};
    Platform *platform = platform_create(&config);
    if (!platform) {
        printf("SKIP: platform window was not created\n");
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
        printf("SKIP: OpenGL device was not created\n");
        return 77;
    }

    Decal decal;
    memset(&decal, 0, sizeof(decal));
    decal.position = vec3(0.0f, 0.0f, 0.0f);
    decal.normal = vec3(0.0f, 1.0f, 0.0f);
    decal.size = 1.0f;
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
    if (g_test_fail == 0 && (!rhi_handle_valid(gpu.vertex) || !rhi_handle_valid(gpu.index))) {
        printf("  FAIL: GL buffer handle was null\n");
        g_test_fail++;
    }
    RHICmdBuffer *cmd = NULL;
    if (g_test_fail == 0) {
        cmd = rhi_frame_begin(device);
        if (!cmd) {
            printf("  FAIL: frame begin returned null\n");
            g_test_fail++;
        }
    }
    if (g_test_fail == 0 && !mesh_gpu_draw(cmd, &mesh, &gpu)) {
        printf("  FAIL: mesh_gpu_draw rejected the frame\n");
        g_test_fail++;
    }
    if (cmd) {
        rhi_frame_end(device);
        rhi_present(device);
    }
    mesh_gpu_destroy(device, &gpu);
    rhi_device_destroy(device);
    platform_destroy(platform);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_fail == 0 ? 1 : 0, g_test_fail, 1);
    return g_test_fail > 0 ? 1 : 0;
}
