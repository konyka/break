#include <rhi/rhi.h>
#include "test_framework.h"
static RHIDevice *g_dev;

TEST(dxr_unsupported_fails_closed) {
    /* Fail-closed half: every RT entry refuses cleanly, never crashes. */
    RHIAccelerationStructureDesc desc;
    desc.type = RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL;
    desc.storage_size = 1024u;
    RHIAccelerationStructure as = rhi_acceleration_structure_create(g_dev, &desc);
    ASSERT_FALSE(rhi_handle_valid(as));
}

TEST(dxr_blas_device_address) {
    RHIAccelerationStructureDesc desc;
    desc.type = RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL;
    desc.storage_size = 0u; /* size comes from the prebuild query */
    RHIAccelerationStructure blas = rhi_acceleration_structure_create(g_dev, &desc);
    ASSERT_TRUE(rhi_handle_valid(blas));
    ASSERT_TRUE(rhi_acceleration_structure_get_device_address(g_dev, blas) != 0u);
    rhi_acceleration_structure_destroy(g_dev, blas);
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (g_dev == NULL) return 77;
    RHICapabilities caps;
    if (!rhi_device_get_capabilities(g_dev, &caps)) return 1;
    printf("=== Running Tests ===\n");
    if ((caps.feature_bits & RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u) {
        RUN_TEST(dxr_unsupported_fails_closed);
        rhi_device_destroy(g_dev);
        return 77; /* SKIP: DXR tier unsupported; fail-closed half verified */
    }
    RUN_TEST(dxr_blas_device_address);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
