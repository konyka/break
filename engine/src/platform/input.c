#include <platform/input.h>
#include <string.h>

void input_init(InputState *s) {
    memset(s, 0, sizeof(*s));
}

void input_new_frame(InputState *s) {
    s->mouse_dx = 0;
    s->mouse_dy = 0;
    s->scroll_dx = 0;
    s->scroll_dy = 0;
    s->frame_number++;

    for (usize i = 0; i < INPUT_MAX_KEYS; i++) {
        u8 v = s->keys[i];
        if (v == 3) s->keys[i] = 2;  /* just pressed -> held */
        else if (v == 1) s->keys[i] = 0;  /* just released -> up */
    }

    for (usize p = 0; p < INPUT_MAX_GAMEPADS; p++) {
        for (usize b = 0; b < INPUT_MAX_PAD_BUTTONS; b++) {
            u8 v = s->gamepads[p].buttons[b];
            if (v == 3) s->gamepads[p].buttons[b] = 2;
            else if (v == 1) s->gamepads[p].buttons[b] = 0;
        }
    }
}

void input_set_key(InputState *s, i32 key, bool pressed) {
    if (key < 0 || key >= INPUT_MAX_KEYS) return;
    if (pressed) {
        /* R295 (CORRECTNESS): latch the just-pressed edge (3) only from up(0) or
         * just-released(1). A key already held(2) must NOT be reset to 3, else
         * OS key auto-repeat — which the Win32 (WM_KEYDOWN, no repeat-bit filter)
         * and Cocoa (keyDown:, isARepeat ignored) backends forward verbatim as
         * repeated `pressed` events — re-fires input_key_pressed() every repeat
         * tick while the key is held, so one-shot actions bound to the
         * just-pressed edge (jump, toggle) mis-trigger repeatedly. The old guard
         * `!= 3` allowed 2→3; mirror input_set_pad_button's correct `!= 2` guard
         * (input_key_down stays true for both 2 and 3, so hold is unaffected). */
        if (s->keys[key] != 2 && s->keys[key] != 3) s->keys[key] = 3;
    } else {
        if (s->keys[key] == 3 || s->keys[key] == 2) s->keys[key] = 1;
    }
}

void input_release_all(InputState *s) {
    /* R263: mirror input_set_key(false) for every held/just-pressed slot so the
     * just-released edge still fires once and input_key_down() goes false. Mouse
     * buttons share keys[] (INPUT_MOUSE_* >= 300), so this covers them too.
     * Gamepads are not window-focus bound and are left untouched. */
    for (usize i = 0; i < INPUT_MAX_KEYS; i++) {
        if (s->keys[i] == 3 || s->keys[i] == 2) s->keys[i] = 1;
    }
}

void input_set_mouse(InputState *s, f32 x, f32 y) {
    s->mouse_dx += x - s->mouse_x;
    s->mouse_dy += y - s->mouse_y;
    s->mouse_x = x;
    s->mouse_y = y;
}

void input_set_scroll(InputState *s, f32 dx, f32 dy) {
    s->scroll_dx += dx;
    s->scroll_dy += dy;
}

void input_set_pad_button(InputState *s, i32 pad, i32 button, bool pressed) {
    if (pad < 0 || pad >= INPUT_MAX_GAMEPADS) return;
    if (button < 0 || button >= INPUT_MAX_PAD_BUTTONS) return;
    u8 *slot = &s->gamepads[pad].buttons[button];
    if (pressed) {
        if (*slot != 2) *slot = 3;
    } else {
        if (*slot == 3 || *slot == 2) *slot = 1;
    }
}
