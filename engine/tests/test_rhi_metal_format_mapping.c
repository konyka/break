#include "test_framework.h"
#include <rhi/rhi_metal_format.h>

TEST(every_color_and_depth_format_maps) {
    for (int f = RHI_FORMAT_R8G8B8A8_UNORM; f <= RHI_FORMAT_D32_FLOAT; ++f) {
        ASSERT_TRUE(rhi_metal_format_from_rhi((RHIFormat)f) != RHI_METAL_FORMAT_INVALID);
        ASSERT_TRUE(rhi_metal_format_bytes_per_pixel(
            rhi_metal_format_from_rhi((RHIFormat)f)) > 0u);
    }
}
TEST(undefined_format_fails_closed) {
    ASSERT_EQ(rhi_metal_format_from_rhi(RHI_FORMAT_UNDEFINED), RHI_METAL_FORMAT_INVALID);
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_INVALID), 0u);
}
TEST(readback_byte_contract_matches_rhi) {
    /* R587/R593/R602: RGBA8/BGRA8=4, RG16F=4, RGBA16F=8, R32F=4, D32=4 */
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_RGBA8_UNORM), 4u);
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_RGBA16_FLOAT), 8u);
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_DEPTH32_FLOAT), 4u);
}
TEST(frame_slot_pacing) {
    ASSERT_EQ(rhi_metal_frame_slot(0u), 0u);
    ASSERT_EQ(rhi_metal_frame_slot(1u), 1u);
    ASSERT_EQ(rhi_metal_frame_slot(2u), 0u);
    ASSERT_EQ(rhi_metal_slot_wait_value(0u), 0u);  /* first two frames never wait */
    ASSERT_EQ(rhi_metal_slot_wait_value(1u), 0u);
    ASSERT_EQ(rhi_metal_slot_wait_value(2u), 0u);  /* ==0: 未 signal 时 wait(0) 立即成立 */
    ASSERT_EQ(rhi_metal_slot_wait_value(3u), 1u);
    ASSERT_EQ(rhi_metal_slot_wait_value(5u), 3u);
}
TEST_MAIN_BEGIN()
    RUN_TEST(every_color_and_depth_format_maps);
    RUN_TEST(undefined_format_fails_closed);
    RUN_TEST(readback_byte_contract_matches_rhi);
    RUN_TEST(frame_slot_pacing);
TEST_MAIN_END()
