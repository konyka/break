#include "test_framework.h"
#include <renderer/vegetation.h>
#include <math.h>

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

static VegetationDesc grid(const u8 *density, u32 w, u32 d, f32 cell, u32 prototypes) {
    VegetationDesc desc;
    desc.density = density;
    desc.width = w;
    desc.depth = d;
    desc.cell = cell;
    desc.prototype_count = prototypes;
    return desc;
}

/* Instances sit at cell centres in row-major order, scaled by the cell
 * size, and the prototype is the density modulo the prototype count. */
TEST(vegetation_positions_order_and_prototypes) {
    u8 density[6] = {1, 0, 5, 2, 3, 0};
    f32 heights[6] = {0, 0, 1, 2, 3, 0};
    VegetationDesc desc = grid(density, 3, 2, 2.0f, 3);
    VegetationInstance inst[6];
    VegetationBuild build;
    memset(&build, 0, sizeof(build));
    build.instances = inst;
    build.capacity = 6;
    ASSERT_TRUE(vegetation_build(&desc, heights, 1.0f, &build));
    ASSERT_EQ(build.count, 4u);
    ASSERT_EQ(build.dropped, 0u);
    ASSERT_FLOAT_EQ(inst[0].position.e[0], 1.0f, 1e-6);
    ASSERT_FLOAT_EQ(inst[0].position.e[2], 1.0f, 1e-6);
    ASSERT_EQ(inst[0].prototype, 1u);
    ASSERT_FLOAT_EQ(inst[1].position.e[0], 5.0f, 1e-6);
    ASSERT_FLOAT_EQ(inst[1].position.e[1], 1.0f, 1e-6);
    ASSERT_EQ(inst[1].prototype, 2u);
    ASSERT_FLOAT_EQ(inst[2].position.e[2], 3.0f, 1e-6);
    ASSERT_EQ(inst[2].prototype, 2u);
    ASSERT_EQ(inst[3].prototype, 0u);
    ASSERT_FLOAT_EQ(inst[3].position.e[1], 3.0f, 1e-6);
}

/* A non-finite height under a populated cell fails the build; one under an
 * empty cell is ignored. */
TEST(vegetation_checks_heights_only_where_it_places) {
    u8 density[2] = {0, 1};
    f32 heights[2] = {NAN, 1.0f};
    VegetationDesc desc = grid(density, 2, 1, 1.0f, 1);
    VegetationInstance inst[2];
    VegetationBuild build;
    memset(&build, 0, sizeof(build));
    build.instances = inst;
    build.capacity = 2;
    ASSERT_TRUE(vegetation_build(&desc, heights, 1.0f, &build));
    ASSERT_EQ(build.count, 1u);
    heights[1] = INFINITY;
    ASSERT_FALSE(vegetation_build(&desc, heights, 1.0f, &build));
}

/* Bad descriptors and outputs are refused. */
TEST(vegetation_rejects_bad_descriptors) {
    u8 density[1] = {1};
    f32 heights[1] = {0};
    VegetationInstance inst;
    VegetationBuild build;
    memset(&build, 0, sizeof(build));
    build.instances = &inst;
    build.capacity = 1;
    VegetationDesc desc = grid(density, 1, 1, 1.0f, 9);
    ASSERT_FALSE(vegetation_build(&desc, heights, 1.0f, &build));
    desc = grid(density, 1, 1, 1.0f, 0);
    ASSERT_FALSE(vegetation_build(&desc, heights, 1.0f, &build));
    desc = grid(density, 1, 1, 0.0f, 1);
    ASSERT_FALSE(vegetation_build(&desc, heights, 1.0f, &build));
    desc = grid(density, 1, 1, INFINITY, 1);
    ASSERT_FALSE(vegetation_build(&desc, heights, 1.0f, &build));
    desc = grid(density, 0, 1, 1.0f, 1);
    ASSERT_FALSE(vegetation_build(&desc, heights, 1.0f, &build));
    desc = grid(NULL, 1, 1, 1.0f, 1);
    ASSERT_FALSE(vegetation_build(&desc, heights, 1.0f, &build));
    desc = grid(density, 1, 1, 1.0f, 8);
    ASSERT_FALSE(vegetation_build(&desc, heights, NAN, &build));
    ASSERT_FALSE(vegetation_build(&desc, NULL, 1.0f, &build));
    ASSERT_FALSE(vegetation_build(NULL, heights, 1.0f, &build));
    ASSERT_FALSE(vegetation_build(&desc, heights, 1.0f, NULL));
    build.instances = NULL;
    ASSERT_FALSE(vegetation_build(&desc, heights, 1.0f, &build));
    build.instances = &inst;
    ASSERT_TRUE(vegetation_build(&desc, heights, 1.0f, &build));
    ASSERT_EQ(inst.prototype, 1u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(vegetation_places_and_drops);
    RUN_TEST(vegetation_positions_order_and_prototypes);
    RUN_TEST(vegetation_checks_heights_only_where_it_places);
    RUN_TEST(vegetation_rejects_bad_descriptors);
TEST_MAIN_END()
