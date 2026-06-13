#pragma once
#include <core/types.h>

#define INPUT_MAX_KEYS        512
#define INPUT_MAX_GAMEPADS    4
#define INPUT_MAX_AXES        6
#define INPUT_MAX_BUTTONS     16
#define INPUT_MAX_PAD_BUTTONS 16

/* Mouse button indices (occupy slots in the keys[] array) */
#define INPUT_MOUSE_LEFT    300
#define INPUT_MOUSE_RIGHT   301
#define INPUT_MOUSE_MIDDLE  302
#define INPUT_MOUSE_4       303
#define INPUT_MOUSE_5       304

/* ---- Gamepad axes (normalized -1.0 ~ 1.0) ---- */
#define GAMEPAD_AXIS_LEFT_X    0
#define GAMEPAD_AXIS_LEFT_Y    1
#define GAMEPAD_AXIS_RIGHT_X   2
#define GAMEPAD_AXIS_RIGHT_Y   3
#define GAMEPAD_AXIS_LTRIGGER  4
#define GAMEPAD_AXIS_RTRIGGER  5

/* ---- Gamepad buttons ---- */
#define GAMEPAD_BTN_SOUTH      0  /* A / Cross    */
#define GAMEPAD_BTN_EAST       1  /* B / Circle   */
#define GAMEPAD_BTN_WEST       2  /* X / Square   */
#define GAMEPAD_BTN_NORTH      3  /* Y / Triangle */
#define GAMEPAD_BTN_LB         4  /* Left  Bumper */
#define GAMEPAD_BTN_RB         5  /* Right Bumper */
#define GAMEPAD_BTN_BACK       6  /* Back / Select */
#define GAMEPAD_BTN_START      7  /* Start         */
#define GAMEPAD_BTN_GUIDE      8  /* Home / Guide  */
#define GAMEPAD_BTN_LSTICK     9  /* Left  Stick Click */
#define GAMEPAD_BTN_RSTICK     10 /* Right Stick Click */
#define GAMEPAD_BTN_DPAD_UP    11
#define GAMEPAD_BTN_DPAD_DOWN  12
#define GAMEPAD_BTN_DPAD_LEFT  13
#define GAMEPAD_BTN_DPAD_RIGHT 14

typedef struct {
    f32  axes[INPUT_MAX_AXES];           /* normalized -1.0 ~ 1.0           */
    u8   buttons[INPUT_MAX_PAD_BUTTONS]; /* 0=up, 1=released, 2=held, 3=pressed */
    bool connected;
    char name[128];
} GamepadState;

typedef struct {
    u8  keys[INPUT_MAX_KEYS];
    f32 mouse_x, mouse_y;
    f32 mouse_dx, mouse_dy;
    f32 scroll_dx, scroll_dy;
    u64 frame_number;
    GamepadState gamepads[INPUT_MAX_GAMEPADS];
} InputState;

void input_init(InputState *s);
void input_new_frame(InputState *s);
void input_set_key(InputState *s, i32 key, bool pressed);
void input_set_mouse(InputState *s, f32 x, f32 y);
void input_set_scroll(InputState *s, f32 dx, f32 dy);
void input_set_pad_button(InputState *s, i32 pad, i32 button, bool pressed);

#define input_key_down(s, k)     ((s)->keys[(k)] == 2 || (s)->keys[(k)] == 3)
#define input_key_pressed(s, k)  ((s)->keys[(k)] == 3)
#define input_key_released(s, k) ((s)->keys[(k)] == 1)

#define input_pad_button_down(s, p, b)     ((s)->gamepads[(p)].buttons[(b)] == 2 || (s)->gamepads[(p)].buttons[(b)] == 3)
#define input_pad_button_pressed(s, p, b)  ((s)->gamepads[(p)].buttons[(b)] == 3)
#define input_pad_button_released(s, p, b) ((s)->gamepads[(p)].buttons[(b)] == 1)
