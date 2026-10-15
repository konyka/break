#include <rhi/rhi.h>
#include "test_framework.h"
/* Plan D Task 6: the D3D12 blit pipeline must be creatable from the
 * hand-authored HLSL sidecars (engine/shaders/blit_hlsl.{vert,frag},
 * precompiled to DXIL at build time) and must expose its push-constant
 * range as a byte-offset location, matching the VK convention. */
static RHIDevice *g_dev;

TEST(blit_pipeline_push_location) {
    /* The blit pipeline must exist and expose its push range as a
     * byte-offset location, matching the VK convention. */
    RHIShader vs = rhi_shader_create(g_dev, "blit_hlsl.vert", 0, false);
    RHIShader fs = rhi_shader_create(g_dev, "blit_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));
    RHIPipelineDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs; desc.frag = fs; desc.no_vertex_input = true;
    desc.color_format = RHI_FORMAT_B8G8R8A8_UNORM;
    RHIPipeline pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_TRUE(rhi_handle_valid(pipe));
    i32 loc = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_transform");
    ASSERT_TRUE(loc >= 0);           /* byte offset into the root constants */
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    /* The sentinel HWND needs the explicit test-only fallback-window opt-in
     * (Task 4 review gate: the fallback is fail-closed by default). */
    _putenv("BREAK_D3D12_TEST_FALLBACK_HWND=1");
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (g_dev == NULL) return 77;
    printf("=== Running Tests ===\n");
    RUN_TEST(blit_pipeline_push_location);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
