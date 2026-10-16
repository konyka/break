#include "test_framework.h"
#include "rhi_oracle.h"
#include <string.h>
#include <stdio.h>

TEST(downsample_constant_frame_is_constant_grid)
{
    u8 rgba[8 * 8 * 4];
    u8 grid[RHI_ORACLE_GW * RHI_ORACLE_GH * 3];
    for (usize i = 0; i < sizeof(rgba); i += 4u) {
        rgba[i] = 200u; rgba[i + 1u] = 100u; rgba[i + 2u] = 50u; rgba[i + 3u] = 255u;
    }
    rhi_oracle_downsample(rgba, 8u, 8u, grid);
    for (usize i = 0; i < sizeof(grid); i += 3u) {
        ASSERT_EQ(grid[i], 200u);
        ASSERT_EQ(grid[i + 1u], 100u);
        ASSERT_EQ(grid[i + 2u], 50u);
    }
}

TEST(ppm_roundtrip_and_drift_detection)
{
    u8 grid[RHI_ORACLE_GW * RHI_ORACLE_GH * 3];
    u8 drift[RHI_ORACLE_GW * RHI_ORACLE_GH * 3];
    RHIOracleResult res = {0.0, 0u};
    const char *path = "tmp_rhi_oracle_test.ppm";
    for (usize i = 0; i < sizeof(grid); i++) grid[i] = (u8)(i % 251u);
    ASSERT_EQ(rhi_oracle_compare_ppm(path, grid, &res), -1); /* 缺失 */
    ASSERT_TRUE(rhi_oracle_write_ppm(path, grid));
    ASSERT_EQ(rhi_oracle_compare_ppm(path, grid, &res), 0);
    ASSERT_TRUE(res.mae == 0.0 && res.maxd == 0u);
    memcpy(drift, grid, sizeof(drift));
    drift[0] = (u8)(drift[0] + 57u); /* 超过 MAXD_MAX 56 */
    ASSERT_EQ(rhi_oracle_compare_ppm(path, drift, &res), 0);
    ASSERT_TRUE(res.maxd >= 57u);
    remove(path);
}

TEST(compare_frame_rejects_blank_when_asked)
{
    u8 shot[64 * 48 * 4];
    memset(shot, 0x11, sizeof(shot));
    ASSERT_FALSE(rhi_oracle_compare_frame(shot, 64u, 48u,
                                          "tmp_rhi_oracle_blank.ppm", true));
}

TEST_MAIN_BEGIN()
    RUN_TEST(downsample_constant_frame_is_constant_grid);
    RUN_TEST(ppm_roundtrip_and_drift_detection);
    RUN_TEST(compare_frame_rejects_blank_when_asked);
TEST_MAIN_END()
