#include "test_framework.h"
#include <kernel/break_kernel.h>

TEST(bind_and_eval_keys_axes_and_replace) {
    World *world = world_create();
    BreakKernel *kernel = break_kernel_create(world, NULL);
    ASSERT_NOT_NULL(kernel);
    BreakKernelBinding key;
    key.source = BREAK_KERNEL_BIND_KEY;
    key.code = 17;
    key.pad = 0;
    key.scale = 0.5f;
    BreakKernelBinding pos;
    pos.source = BREAK_KERNEL_BIND_PAD_AXIS;
    pos.code = 0;
    pos.pad = 0;
    pos.scale = 1.0f;
    BreakKernelBinding neg;
    neg.source = BREAK_KERNEL_BIND_PAD_AXIS;
    neg.code = 1;
    neg.pad = 0;
    neg.scale = 1.0f;
    BreakKernelBinding axes[2] = {pos, neg};
    BreakKernelActionDesc desc[2];
    desc[0].name = "use";
    desc[0].bindings = &key;
    desc[0].binding_count = 1;
    desc[1].name = "move";
    desc[1].bindings = axes;
    desc[1].binding_count = 2;
    ASSERT_EQ(break_kernel_bind_actions(kernel, desc, 2), BREAK_KERNEL_OK);

    InputState input;
    memset(&input, 0, sizeof(input));
    input.keys[17] = 3;
    input.gamepads[0].connected = true;
    input.gamepads[0].axes[0] = 1.0f;
    input.gamepads[0].axes[1] = 1.0f;
    BreakKernelActionValue values[2];
    memset(values, 0, sizeof(values));
    ASSERT_EQ(break_kernel_eval_actions(kernel, &input, values, 2), BREAK_KERNEL_OK);
    ASSERT_TRUE(values[0].down);
    ASSERT_FLOAT_EQ(values[0].axis, 0.5f, 1e-6);
    ASSERT_FALSE(values[1].down);
    ASSERT_FLOAT_EQ(values[1].axis, 1.0f, 1e-6);

    input.gamepads[0].axes[0] = 1.0f;
    input.gamepads[0].axes[1] = 0.0f;
    BreakKernelBinding back;
    back.source = BREAK_KERNEL_BIND_PAD_AXIS;
    back.code = 0;
    back.pad = 0;
    back.scale = -3.0f;
    desc[1].bindings = &back;
    desc[1].binding_count = 1;
    ASSERT_EQ(break_kernel_bind_actions(kernel, desc, 2), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_eval_actions(kernel, &input, values, 2), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(values[1].axis, -1.0f, 1e-6);

    BreakKernelBinding nine[9];
    for (int i = 0; i < 9; i++) nine[i] = key;
    BreakKernelActionDesc bad = desc[0];
    bad.bindings = nine;
    bad.binding_count = 9;
    ASSERT_EQ(break_kernel_bind_actions(kernel, &bad, 1), BREAK_KERNEL_INVALID);
    input.keys[17] = 0;
    input.keys[17] = 3;
    ASSERT_EQ(break_kernel_eval_actions(kernel, &input, values, 2), BREAK_KERNEL_OK);
    ASSERT_TRUE(values[0].down);

    BreakKernelBinding rebound;
    rebound.source = BREAK_KERNEL_BIND_KEY;
    rebound.code = 18;
    rebound.pad = 0;
    rebound.scale = 1.0f;
    desc[0].bindings = &rebound;
    desc[0].binding_count = 1;
    ASSERT_EQ(break_kernel_bind_actions(kernel, desc, 2), BREAK_KERNEL_OK);
    input.keys[17] = 3;
    input.keys[18] = 0;
    ASSERT_EQ(break_kernel_eval_actions(kernel, &input, values, 2), BREAK_KERNEL_OK);
    ASSERT_FALSE(values[0].down);
    input.keys[17] = 0;
    input.keys[18] = 3;
    ASSERT_EQ(break_kernel_eval_actions(kernel, &input, values, 2), BREAK_KERNEL_OK);
    ASSERT_TRUE(values[0].down);

    BreakKernelActionValue dirty;
    dirty.down = true;
    dirty.axis = 9.0f;
    ASSERT_EQ(break_kernel_eval_actions(kernel, &input, &dirty, 1), BREAK_KERNEL_OVERLOAD);
    ASSERT_TRUE(dirty.down);
    ASSERT_FLOAT_EQ(dirty.axis, 9.0f, 1e-6);

    BreakKernelActionDesc too_many[65];
    BreakKernelBinding one = key;
    char names[65][8];
    for (int i = 0; i < 65; i++) {
        snprintf(names[i], sizeof(names[i]), "a%d", i);
        too_many[i].name = names[i];
        too_many[i].bindings = &one;
        too_many[i].binding_count = 1;
    }
    ASSERT_EQ(break_kernel_bind_actions(kernel, too_many, 65), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(break_kernel_eval_actions(kernel, &input, values, 2), BREAK_KERNEL_OK);
    ASSERT_TRUE(values[0].down);

    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(bind_and_eval_keys_axes_and_replace);
TEST_MAIN_END()
