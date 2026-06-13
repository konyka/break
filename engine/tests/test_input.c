/* test_input.c — Input state machine unit tests
 *
 * Tests cover:
 *   - input_init: zero-initialization
 *   - key state transitions: up→pressed→held→released→up
 *   - key macros: key_down, key_pressed, key_released
 *   - input_new_frame: state decay
 *   - input_set_mouse: position and delta tracking
 *   - input_set_scroll: scroll accumulation
 *   - input_set_key: out-of-bounds safety
 *   - input_set_pad_button: gamepad button state machine
 *   - mouse button constants
 *   - multi-key simultaneous tracking
 */

#include "test_framework.h"
#include <platform/input.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* input_init                                                          */
/* ------------------------------------------------------------------ */

TEST(init_zeros)
{
    InputState s;
    memset(&s, 0xFF, sizeof(s)); /* fill with garbage */
    input_init(&s);

    ASSERT_EQ(s.keys[0], 0);
    ASSERT_EQ(s.keys[255], 0);
    ASSERT_EQ(s.keys[511], 0);
    ASSERT_FLOAT_EQ(s.mouse_x, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.mouse_y, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.mouse_dx, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.mouse_dy, 0.0f, 1e-6f);
    ASSERT_EQ(s.frame_number, (u64)0);
}

/* ------------------------------------------------------------------ */
/* Key state machine                                                   */
/* ------------------------------------------------------------------ */

TEST(key_press_sets_state_3)
{
    InputState s;
    input_init(&s);
    input_set_key(&s, 65, true); /* press 'A' */
    ASSERT_EQ(s.keys[65], 3);
}

TEST(key_pressed_macro)
{
    InputState s;
    input_init(&s);
    input_set_key(&s, 10, true);
    ASSERT_TRUE(input_key_pressed(&s, 10));
    ASSERT_TRUE(!input_key_pressed(&s, 11));
}

TEST(key_down_after_press)
{
    InputState s;
    input_init(&s);
    input_set_key(&s, 20, true);
    ASSERT_TRUE(input_key_down(&s, 20));
}

TEST(key_held_after_new_frame)
{
    InputState s;
    input_init(&s);

    input_set_key(&s, 30, true);  /* state=3 (just pressed) */
    ASSERT_EQ(s.keys[30], 3);

    input_new_frame(&s);           /* state: 3→2 (held) */
    ASSERT_EQ(s.keys[30], 2);
    ASSERT_TRUE(input_key_down(&s, 30));
    ASSERT_TRUE(!input_key_pressed(&s, 30)); /* no longer "just pressed" */
}

TEST(key_release_sets_state_1)
{
    InputState s;
    input_init(&s);

    input_set_key(&s, 40, true);   /* press: state=3 */
    input_new_frame(&s);            /* 3→2 (held) */
    input_set_key(&s, 40, false);  /* release: 2→1 */
    ASSERT_EQ(s.keys[40], 1);
    ASSERT_TRUE(input_key_released(&s, 40));
}

TEST(key_up_after_release_frame)
{
    InputState s;
    input_init(&s);

    input_set_key(&s, 50, true);   /* press: 3 */
    input_new_frame(&s);            /* 3→2 */
    input_set_key(&s, 50, false);  /* release: 2→1 */
    ASSERT_EQ(s.keys[50], 1);

    input_new_frame(&s);            /* 1→0 (up) */
    ASSERT_EQ(s.keys[50], 0);
    ASSERT_TRUE(!input_key_down(&s, 50));
    ASSERT_TRUE(!input_key_released(&s, 50));
}

TEST(key_full_cycle)
{
    /* Verify: up→pressed→held→held→released→up */
    InputState s;
    input_init(&s);

    ASSERT_EQ(s.keys[0], 0);       /* up */
    input_set_key(&s, 0, true);
    ASSERT_EQ(s.keys[0], 3);       /* just pressed */

    input_new_frame(&s);
    ASSERT_EQ(s.keys[0], 2);       /* held */

    input_new_frame(&s);
    ASSERT_EQ(s.keys[0], 2);       /* still held */

    input_set_key(&s, 0, false);
    ASSERT_EQ(s.keys[0], 1);       /* just released */

    input_new_frame(&s);
    ASSERT_EQ(s.keys[0], 0);       /* up */
}

TEST(key_release_from_just_pressed)
{
    /* Release immediately after press (state=3 → 1) */
    InputState s;
    input_init(&s);

    input_set_key(&s, 77, true);   /* state=3 */
    input_set_key(&s, 77, false);  /* release from 3 → 1 */
    ASSERT_EQ(s.keys[77], 1);
    ASSERT_TRUE(input_key_released(&s, 77));
}

/* ------------------------------------------------------------------ */
/* input_new_frame                                                     */
/* ------------------------------------------------------------------ */

TEST(new_frame_increments_counter)
{
    InputState s;
    input_init(&s);
    ASSERT_EQ(s.frame_number, (u64)0);

    input_new_frame(&s);
    ASSERT_EQ(s.frame_number, (u64)1);

    input_new_frame(&s);
    ASSERT_EQ(s.frame_number, (u64)2);
}

TEST(new_frame_clears_mouse_delta)
{
    InputState s;
    input_init(&s);

    input_set_mouse(&s, 100.0f, 200.0f);
    ASSERT_TRUE(s.mouse_dx > 0.0f);

    input_new_frame(&s);
    ASSERT_FLOAT_EQ(s.mouse_dx, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.mouse_dy, 0.0f, 1e-6f);
}

TEST(new_frame_clears_scroll)
{
    InputState s;
    input_init(&s);

    input_set_scroll(&s, 1.0f, 2.0f);
    ASSERT_FLOAT_EQ(s.scroll_dx, 1.0f, 1e-6f);

    input_new_frame(&s);
    ASSERT_FLOAT_EQ(s.scroll_dx, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.scroll_dy, 0.0f, 1e-6f);
}

/* ------------------------------------------------------------------ */
/* Mouse tracking                                                      */
/* ------------------------------------------------------------------ */

TEST(mouse_position_and_delta)
{
    InputState s;
    input_init(&s);

    input_set_mouse(&s, 50.0f, 60.0f);
    ASSERT_FLOAT_EQ(s.mouse_x, 50.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.mouse_y, 60.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.mouse_dx, 50.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.mouse_dy, 60.0f, 1e-6f);

    input_set_mouse(&s, 70.0f, 80.0f);
    ASSERT_FLOAT_EQ(s.mouse_x, 70.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.mouse_y, 80.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.mouse_dx, 70.0f, 1e-6f); /* 50 + 20 */
    ASSERT_FLOAT_EQ(s.mouse_dy, 80.0f, 1e-6f); /* 60 + 20 */
}

TEST(scroll_accumulates)
{
    InputState s;
    input_init(&s);

    input_set_scroll(&s, 1.0f, 0.5f);
    input_set_scroll(&s, 2.0f, -1.0f);
    ASSERT_FLOAT_EQ(s.scroll_dx, 3.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.scroll_dy, -0.5f, 1e-6f);
}

/* ------------------------------------------------------------------ */
/* Out-of-bounds safety                                                */
/* ------------------------------------------------------------------ */

TEST(key_out_of_bounds_negative)
{
    InputState s;
    input_init(&s);
    input_set_key(&s, -1, true);  /* should be ignored */
    /* No crash = pass */
    ASSERT_EQ(s.keys[0], 0);
}

TEST(key_out_of_bounds_too_large)
{
    InputState s;
    input_init(&s);
    input_set_key(&s, INPUT_MAX_KEYS, true);  /* should be ignored */
    ASSERT_EQ(s.keys[0], 0);
}

/* ------------------------------------------------------------------ */
/* Gamepad buttons                                                     */
/* ------------------------------------------------------------------ */

TEST(pad_button_press_release)
{
    InputState s;
    input_init(&s);

    input_set_pad_button(&s, 0, GAMEPAD_BTN_SOUTH, true);
    ASSERT_TRUE(input_pad_button_pressed(&s, 0, GAMEPAD_BTN_SOUTH));
    ASSERT_TRUE(input_pad_button_down(&s, 0, GAMEPAD_BTN_SOUTH));

    input_new_frame(&s);
    ASSERT_TRUE(!input_pad_button_pressed(&s, 0, GAMEPAD_BTN_SOUTH));
    ASSERT_TRUE(input_pad_button_down(&s, 0, GAMEPAD_BTN_SOUTH));

    input_set_pad_button(&s, 0, GAMEPAD_BTN_SOUTH, false);
    ASSERT_TRUE(input_pad_button_released(&s, 0, GAMEPAD_BTN_SOUTH));

    input_new_frame(&s);
    ASSERT_TRUE(!input_pad_button_down(&s, 0, GAMEPAD_BTN_SOUTH));
}

TEST(pad_button_out_of_bounds)
{
    InputState s;
    input_init(&s);

    /* Invalid pad index */
    input_set_pad_button(&s, -1, 0, true);
    input_set_pad_button(&s, INPUT_MAX_GAMEPADS, 0, true);

    /* Invalid button index */
    input_set_pad_button(&s, 0, -1, true);
    input_set_pad_button(&s, 0, INPUT_MAX_PAD_BUTTONS, true);
    /* No crash = pass */
}

/* Gamepad backends (evdev / XInput) only write axes on change events and rely
 * on input_new_frame NOT clearing them — verify that contract. */
TEST(pad_axes_persist_across_frames)
{
    InputState s;
    input_init(&s);

    s.gamepads[0].axes[GAMEPAD_AXIS_LEFT_X]  = -0.5f;
    s.gamepads[0].axes[GAMEPAD_AXIS_LTRIGGER] = 0.75f;

    input_new_frame(&s);

    ASSERT_FLOAT_EQ(s.gamepads[0].axes[GAMEPAD_AXIS_LEFT_X],  -0.5f, 1e-6f);
    ASSERT_FLOAT_EQ(s.gamepads[0].axes[GAMEPAD_AXIS_LTRIGGER], 0.75f, 1e-6f);
}

/* Button edge decay must run for every pad slot, not just pad 0. */
TEST(pad_all_slots_advance_on_new_frame)
{
    InputState s;
    input_init(&s);

    for (int p = 0; p < INPUT_MAX_GAMEPADS; p++)
        input_set_pad_button(&s, p, GAMEPAD_BTN_START, true);

    for (int p = 0; p < INPUT_MAX_GAMEPADS; p++)
        ASSERT_TRUE(input_pad_button_pressed(&s, p, GAMEPAD_BTN_START));

    input_new_frame(&s);

    for (int p = 0; p < INPUT_MAX_GAMEPADS; p++) {
        ASSERT_TRUE(!input_pad_button_pressed(&s, p, GAMEPAD_BTN_START));
        ASSERT_TRUE(input_pad_button_down(&s, p, GAMEPAD_BTN_START)); /* held */
    }
}

/* Per-pad state must be independent between slots. */
TEST(pad_slots_independent)
{
    InputState s;
    input_init(&s);

    input_set_pad_button(&s, 1, GAMEPAD_BTN_NORTH, true);

    ASSERT_TRUE(input_pad_button_down(&s, 1, GAMEPAD_BTN_NORTH));
    ASSERT_TRUE(!input_pad_button_down(&s, 0, GAMEPAD_BTN_NORTH));
    ASSERT_TRUE(!input_pad_button_down(&s, 2, GAMEPAD_BTN_NORTH));
}

/* ------------------------------------------------------------------ */
/* Mouse button constants                                             */
/* ------------------------------------------------------------------ */

TEST(mouse_buttons_via_key_api)
{
    InputState s;
    input_init(&s);

    input_set_key(&s, INPUT_MOUSE_LEFT, true);
    ASSERT_TRUE(input_key_pressed(&s, INPUT_MOUSE_LEFT));
    ASSERT_TRUE(input_key_down(&s, INPUT_MOUSE_LEFT));

    input_set_key(&s, INPUT_MOUSE_RIGHT, true);
    ASSERT_TRUE(input_key_down(&s, INPUT_MOUSE_RIGHT));

    input_new_frame(&s);
    ASSERT_TRUE(input_key_down(&s, INPUT_MOUSE_LEFT));
    ASSERT_TRUE(input_key_down(&s, INPUT_MOUSE_RIGHT));
}

/* ------------------------------------------------------------------ */
/* Multi-key simultaneous                                              */
/* ------------------------------------------------------------------ */

TEST(multi_key_simultaneous)
{
    InputState s;
    input_init(&s);

    input_set_key(&s, 10, true);
    input_set_key(&s, 20, true);
    input_set_key(&s, 30, true);

    ASSERT_TRUE(input_key_pressed(&s, 10));
    ASSERT_TRUE(input_key_pressed(&s, 20));
    ASSERT_TRUE(input_key_pressed(&s, 30));
    ASSERT_TRUE(!input_key_pressed(&s, 40));

    input_new_frame(&s);
    input_set_key(&s, 20, false); /* release middle key */

    ASSERT_TRUE(input_key_down(&s, 10));   /* still held */
    ASSERT_TRUE(input_key_released(&s, 20)); /* just released */
    ASSERT_TRUE(input_key_down(&s, 30));   /* still held */
}

/* ------------------------------------------------------------------ */
/*  Edge Cases                                                          */
/* ------------------------------------------------------------------ */

TEST(key_boundary_index)
{
    InputState s;
    input_init(&s);

    /* Test key at INPUT_MAX_KEYS - 1 (last valid key) */
    input_set_key(&s, INPUT_MAX_KEYS - 1, true);
    ASSERT_TRUE(input_key_pressed(&s, INPUT_MAX_KEYS - 1));
    ASSERT_TRUE(input_key_down(&s, INPUT_MAX_KEYS - 1));
}

TEST(multiple_new_frames_in_a_row)
{
    InputState s;
    input_init(&s);

    input_set_key(&s, 50, true);
    ASSERT_EQ(s.keys[50], 3);  /* just pressed */

    for (int i = 0; i < 10; i++) {
        input_new_frame(&s);
    }

    /* After many frames, state should still be held (2) */
    ASSERT_EQ(s.keys[50], 2);
    ASSERT_TRUE(input_key_down(&s, 50));
    ASSERT_TRUE(!input_key_pressed(&s, 50));
}

TEST(mouse_position_extremes)
{
    InputState s;
    input_init(&s);

    /* Very large coordinates */
    input_set_mouse(&s, 1e6f, 1e6f);
    ASSERT_FLOAT_EQ(s.mouse_x, 1e6f, 1e-3f);
    ASSERT_FLOAT_EQ(s.mouse_y, 1e6f, 1e-3f);

    /* Negative coordinates */
    input_set_mouse(&s, -1e6f, -1e6f);
    ASSERT_FLOAT_EQ(s.mouse_x, -1e6f, 1e-3f);
    ASSERT_FLOAT_EQ(s.mouse_y, -1e6f, 1e-3f);
}

TEST(scroll_zero_values)
{
    InputState s;
    input_init(&s);

    /* Zero scroll should not accumulate */
    input_set_scroll(&s, 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(s.scroll_dx, 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.scroll_dy, 0.0f, 1e-6f);

    input_set_scroll(&s, 1.0f, 1.0f);
    input_set_scroll(&s, 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(s.scroll_dx, 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(s.scroll_dy, 1.0f, 1e-6f);
}

/* ------------------------------------------------------------------ */

int main(void) {
    RUN_TEST(init_zeros);
    RUN_TEST(key_press_sets_state_3);
    RUN_TEST(key_pressed_macro);
    RUN_TEST(key_down_after_press);
    RUN_TEST(key_held_after_new_frame);
    RUN_TEST(key_release_sets_state_1);
    RUN_TEST(key_up_after_release_frame);
    RUN_TEST(key_full_cycle);
    RUN_TEST(key_release_from_just_pressed);
    RUN_TEST(new_frame_increments_counter);
    RUN_TEST(new_frame_clears_mouse_delta);
    RUN_TEST(new_frame_clears_scroll);
    RUN_TEST(mouse_position_and_delta);
    RUN_TEST(scroll_accumulates);
    RUN_TEST(key_out_of_bounds_negative);
    RUN_TEST(key_out_of_bounds_too_large);
    RUN_TEST(pad_button_press_release);
    RUN_TEST(pad_button_out_of_bounds);
    RUN_TEST(pad_axes_persist_across_frames);
    RUN_TEST(pad_all_slots_advance_on_new_frame);
    RUN_TEST(pad_slots_independent);
    RUN_TEST(mouse_buttons_via_key_api);
    RUN_TEST(multi_key_simultaneous);
    /* Edge cases */
    RUN_TEST(key_boundary_index);
    RUN_TEST(multiple_new_frames_in_a_row);
    RUN_TEST(mouse_position_extremes);
    RUN_TEST(scroll_zero_values);

    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
