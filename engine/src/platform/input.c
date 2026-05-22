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
        if (s->keys[i] == 3) s->keys[i] = 2;
        if (s->keys[i] == 1) s->keys[i] = 0;
    }
}

void input_set_key(InputState *s, i32 key, bool pressed) {
    if (key < 0 || key >= INPUT_MAX_KEYS) return;
    if (pressed) {
        s->keys[key] = 3;
    } else {
        if (s->keys[key] == 3 || s->keys[key] == 2) s->keys[key] = 1;
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
