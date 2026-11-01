#include "test_framework.h"
#include <renderer/vegetation.h>

TEST(vegetation_places_and_drops) {
    u8 zero[4] = {0, 0, 0, 0};
    f32 heights[4] = {1, 2, 3, 4};
    VegetationDesc desc;
    desc.density = zero;
    desc.width = 2;
    desc.depth = 2;
    desc.cell = 1.0f;
    desc.prototype_count = 2;
    VegetationBuild build;
    memset(&build, 0, sizeof(build));
    ASSERT_TRUE(vegetation_build(&desc, heights, 2.0f, &build));
    ASSERT_EQ(build.count, 0u);
    ASSERT_EQ(build.dropped, 0u);

    u8 one[1] = {3};
    f32 h = 4.0f;
    desc.density = one;
    desc.width = 1;
    desc.depth = 1;
    VegetationInstance inst;
    build.instances = &inst;
    build.capacity = 1;
    ASSERT_TRUE(vegetation_build(&desc, &h, 2.0f, &build));
    ASSERT_EQ(build.count, 1u);
    ASSERT_FLOAT_EQ(inst.position.e[1], 8.0f, 1e-5);
    ASSERT_EQ(inst.prototype, 1u);

    u8 dense[3] = {1, 2, 1};
    f32 hs[3] = {0, 0, 0};
    desc.density = dense;
    desc.width = 3;
    desc.depth = 1;
    VegetationInstance slot;
    build.instances = &slot;
    build.capacity = 1;
    ASSERT_TRUE(vegetation_build(&desc, hs, 1.0f, &build));
    ASSERT_EQ(build.count, 1u);
    ASSERT_EQ(build.dropped, 2u);

    desc.width = 0xFFFFFFF0u;
    desc.depth = 16;
    ASSERT_FALSE(vegetation_build(&desc, hs, 1.0f, &build));
}

TEST_MAIN_BEGIN()
    RUN_TEST(vegetation_places_and_drops);
TEST_MAIN_END()
