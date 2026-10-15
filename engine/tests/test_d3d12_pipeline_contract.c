#include <rhi/rhi.h>
#include "test_framework.h"
/* GPU resource roundtrip; main skips 77 when no adapter. */
static RHIDevice *g_dev;

TEST(buffer_write_read_roundtrip) {
    const u32 payload[4] = { 11u, 22u, 33u, 44u };
    u32 readback[4] = { 0u, 0u, 0u, 0u };
    RHIBufferDesc bdesc;
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_DEVICE_ADDRESS;
    bdesc.size = sizeof(payload);
    bdesc.initial_data = payload;
    RHIBuffer buf = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(buf));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, readback, 0, sizeof(readback)));
    ASSERT_TRUE(memcmp(readback, payload, sizeof(payload)) == 0);
    rhi_buffer_destroy(g_dev, buf);
}

TEST(texture_create_readback_roundtrip) {
    /* RGBA8 4B/px byte contract (rhi.h:501). */
    static const u8 texels[16] = {
        255,0,0,255, 0,255,0,255, 0,0,255,255, 255,255,255,255 };
    u8 out[16];
    RHITextureDesc tdesc;
    memset(&tdesc, 0, sizeof(tdesc));
    memset(out, 0, sizeof(out));
    tdesc.width = 2u; tdesc.height = 2u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM; tdesc.mip_levels = 1u;
    tdesc.data = texels;
    RHITexture tex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(tex));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, tex, out, sizeof(out)));
    ASSERT_TRUE(memcmp(out, texels, sizeof(out)) == 0);
    rhi_texture_destroy(g_dev, tex);
}

TEST(indirect_abi_rule_shared) {
    /* The shared validator stays authoritative (rhi.h:227-230). */
    ASSERT_TRUE(rhi_indirect_abi_valid((u32)sizeof(RHIIndexedIndirectCommand), 1u));
    ASSERT_FALSE(rhi_indirect_abi_valid(8u, 0u));
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (g_dev == NULL) return 77;
    printf("=== Running Tests ===\n");
    RUN_TEST(buffer_write_read_roundtrip);
    RUN_TEST(texture_create_readback_roundtrip);
    RUN_TEST(indirect_abi_rule_shared);
    if (rhi_device_drain_ex(g_dev) != RHI_RESULT_OK) g_test_fail++;
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
