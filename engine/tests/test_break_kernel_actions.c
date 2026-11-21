#include "test_framework.h"
#include <kernel/break_kernel.h>
#include <math.h>

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
    input.pads[0].connected = true;
    input.pads[0].axes[0] = 1.0f;
    input.pads[0].axes[1] = 1.0f;
    BreakKernelActionValue values[2];
    memset(values, 0, sizeof(values));
    ASSERT_EQ(break_kernel_eval_actions(kernel, &input, values, 2), BREAK_KERNEL_OK);
    ASSERT_TRUE(values[0].down);
    ASSERT_FLOAT_EQ(values[0].axis, 0.5f, 1e-6);
    ASSERT_FALSE(values[1].down);
    ASSERT_FLOAT_EQ(values[1].axis, 1.0f, 1e-6);

    input.pads[0].axes[0] = 1.0f;
    input.pads[0].axes[1] = 0.0f;
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

static BreakKernelBinding binding(BreakKernelBindSource source, i32 code, i32 pad, f32 scale) {
    BreakKernelBinding b;
    b.source = source;
    b.code = code;
    b.pad = pad;
    b.scale = scale;
    return b;
}

typedef struct {
    World *world;
    BreakKernel *kernel;
} Fixture;

static bool fixture_open(Fixture *f) {
    f->world = world_create();
    f->kernel = f->world ? break_kernel_create(f->world, NULL) : NULL;
    return f->kernel != NULL;
}

static void fixture_close(Fixture *f) {
    break_kernel_destroy(f->kernel);
    world_destroy(f->world);
}

/* Mouse axes map dx, dy and the wheel, mouse buttons count as keys, and a
 * disconnected pad contributes nothing. */
TEST(mouse_and_pad_sources) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));
    BreakKernelBinding look[3] = {binding(BREAK_KERNEL_BIND_MOUSE_AXIS, 0, 0, 0.1f),
                                  binding(BREAK_KERNEL_BIND_MOUSE_AXIS, 1, 0, -0.1f),
                                  binding(BREAK_KERNEL_BIND_MOUSE_AXIS, 2, 0, 1.0f)};
    BreakKernelBinding fire = binding(BREAK_KERNEL_BIND_MOUSE_BUTTON, 1, 0, 1.0f);
    BreakKernelBinding jump = binding(BREAK_KERNEL_BIND_PAD_BUTTON, 2, 1, 1.0f);
    BreakKernelActionDesc desc[5] = {{"look_x", &look[0], 1}, {"look_y", &look[1], 1},
                                     {"zoom", &look[2], 1}, {"fire", &fire, 1},
                                     {"jump", &jump, 1}};
    ASSERT_EQ(break_kernel_bind_actions(f.kernel, desc, 5), BREAK_KERNEL_OK);
    InputState input;
    memset(&input, 0, sizeof(input));
    input.mouse_dx = 4.0f;
    input.mouse_dy = 2.0f;
    input.scroll_dy = -0.5f;
    input.keys[1] = 2;
    input.pads[1].buttons[2] = 2;
    BreakKernelActionValue v[5];
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, &input, v, 5), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(v[0].axis, 0.4f, 1e-6);
    ASSERT_FLOAT_EQ(v[1].axis, -0.2f, 1e-6);
    ASSERT_FLOAT_EQ(v[2].axis, -0.5f, 1e-6);
    ASSERT_FALSE(v[0].down);
    ASSERT_TRUE(v[3].down);
    ASSERT_FLOAT_EQ(v[3].axis, 1.0f, 1e-6);
    /* pad 1 is not connected, so its button is ignored */
    ASSERT_FALSE(v[4].down);
    ASSERT_FLOAT_EQ(v[4].axis, 0.0f, 1e-6);
    input.pads[1].connected = true;
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, &input, v, 5), BREAK_KERNEL_OK);
    ASSERT_TRUE(v[4].down);
    /* a key in the released state (1) is not down */
    input.keys[1] = 1;
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, &input, v, 5), BREAK_KERNEL_OK);
    ASSERT_FALSE(v[3].down);
    fixture_close(&f);
}

/* Several bindings of one action add up and the sum is clamped to [-1, 1];
 * any digital binding being down makes the action down. */
TEST(bindings_sum_and_clamp) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));
    BreakKernelBinding pair[3] = {binding(BREAK_KERNEL_BIND_KEY, 30, 0, 0.75f),
                                  binding(BREAK_KERNEL_BIND_KEY, 31, 0, -0.25f),
                                  binding(BREAK_KERNEL_BIND_KEY, 32, 0, 0.75f)};
    BreakKernelActionDesc desc = {"axis", pair, 3};
    ASSERT_EQ(break_kernel_bind_actions(f.kernel, &desc, 1), BREAK_KERNEL_OK);
    InputState input;
    memset(&input, 0, sizeof(input));
    input.keys[30] = 2;
    input.keys[31] = 2;
    BreakKernelActionValue v;
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, &input, &v, 1), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(v.axis, 0.5f, 1e-6);
    ASSERT_TRUE(v.down);
    input.keys[32] = 3;
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, &input, &v, 1), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(v.axis, 1.0f, 1e-6);
    memset(&input, 0, sizeof(input));
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, &input, &v, 1), BREAK_KERNEL_OK);
    ASSERT_FALSE(v.down);
    ASSERT_FLOAT_EQ(v.axis, 0.0f, 1e-6);
    fixture_close(&f);
}

/* Invalid bindings, duplicate names and bad arguments are refused and the
 * previous binding set stays in force. */
TEST(bad_bindings_keep_the_previous_set) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));
    BreakKernelBinding key = binding(BREAK_KERNEL_BIND_KEY, 5, 0, 1.0f);
    BreakKernelActionDesc good = {"use", &key, 1};
    ASSERT_EQ(break_kernel_bind_actions(f.kernel, &good, 1), BREAK_KERNEL_OK);
    BreakKernelBinding bad[] = {
        binding(BREAK_KERNEL_BIND_KEY, -1, 0, 1.0f),
        binding(BREAK_KERNEL_BIND_KEY, INPUT_MAX_KEYS, 0, 1.0f),
        binding(BREAK_KERNEL_BIND_KEY, 5, 1, 1.0f),
        binding(BREAK_KERNEL_BIND_MOUSE_AXIS, 3, 0, 1.0f),
        binding(BREAK_KERNEL_BIND_PAD_AXIS, 0, INPUT_MAX_PADS, 1.0f),
        binding(BREAK_KERNEL_BIND_PAD_AXIS, INPUT_MAX_AXES, 0, 1.0f),
        binding(BREAK_KERNEL_BIND_PAD_BUTTON, INPUT_MAX_PAD_BUTTONS, 0, 1.0f),
        binding(BREAK_KERNEL_BIND_KEY, 5, 0, NAN),
        binding((BreakKernelBindSource)0, 5, 0, 1.0f),
    };
    for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); i++) {
        BreakKernelActionDesc d = {"x", &bad[i], 1};
        ASSERT_EQ(break_kernel_bind_actions(f.kernel, &d, 1), BREAK_KERNEL_INVALID);
    }
    BreakKernelActionDesc dup[2] = {{"same", &key, 1}, {"same", &key, 1}};
    ASSERT_EQ(break_kernel_bind_actions(f.kernel, dup, 2), BREAK_KERNEL_REJECTED);
    BreakKernelActionDesc no_bindings = {"empty", NULL, 1};
    ASSERT_EQ(break_kernel_bind_actions(f.kernel, &no_bindings, 1), BREAK_KERNEL_INVALID);
    BreakKernelActionDesc unnamed = {"", &key, 1};
    ASSERT_EQ(break_kernel_bind_actions(f.kernel, &unnamed, 1), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_bind_actions(f.kernel, NULL, 1), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_bind_actions(NULL, &good, 1), BREAK_KERNEL_INVALID);
    InputState input;
    memset(&input, 0, sizeof(input));
    input.keys[5] = 2;
    BreakKernelActionValue v;
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, &input, &v, 1), BREAK_KERNEL_OK);
    ASSERT_TRUE(v.down);
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, NULL, &v, 1), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, &input, NULL, 1), BREAK_KERNEL_INVALID);
    /* binding zero actions clears the set */
    ASSERT_EQ(break_kernel_bind_actions(f.kernel, NULL, 0), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_eval_actions(f.kernel, &input, NULL, 0), BREAK_KERNEL_OK);
    fixture_close(&f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(bind_and_eval_keys_axes_and_replace);
    RUN_TEST(mouse_and_pad_sources);
    RUN_TEST(bindings_sum_and_clamp);
    RUN_TEST(bad_bindings_keep_the_previous_set);
TEST_MAIN_END()
