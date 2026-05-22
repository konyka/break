#pragma once
#include <core/types.h>

#define INPUT_MAX_KEYS    512
#define INPUT_MAX_GAMEPADS 4
#define INPUT_MAX_AXES     6
#define INPUT_MAX_BUTTONS  16

typedef struct {
    u8  keys[INPUT_MAX_KEYS];
    f32 mouse_x, mouse_y;
    f32 mouse_dx, mouse_dy;
    f32 scroll_dx, scroll_dy;
    u64 frame_number;
} InputState;

void input_init(InputState *s);
void input_new_frame(InputState *s);
void input_set_key(InputState *s, i32 key, bool pressed);
void input_set_mouse(InputState *s, f32 x, f32 y);
void input_set_scroll(InputState *s, f32 dx, f32 dy);

#define input_key_down(s, k)    ((s)->keys[(k)] & 1)
#define input_key_pressed(s, k) (((s)->keys[(k)] & 3) == 3)
#define input_key_released(s, k) (((s)->keys[(k)] & 3) == 1)
