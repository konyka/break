#ifdef ENGINE_PLATFORM_WINDOWS

/* Windows XInput gamepad backend.
 *
 * Implements the same gamepad_init/poll/shutdown contract as the Linux evdev
 * backend (gamepad_linux.c) so window_win32.c can wire it in identically.
 *
 * XInput is loaded dynamically (xinput1_4 -> xinput1_3 -> xinput9_1_0) so the
 * engine links cleanly on systems lacking the newest redistributable and
 * degrades to "no pads" rather than failing to start.
 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <xinput.h>
#include <string.h>
#include <stdio.h>

#include <platform/input.h>
#include <core/types.h>
#include <core/log.h>

#include "gamepad_linux.h"  /* shared gamepad_init/poll/shutdown prototypes */

/* XInput exposes at most 4 controllers — matches INPUT_MAX_GAMEPADS. */
#ifndef XUSER_MAX_COUNT
#define XUSER_MAX_COUNT 4
#endif

typedef DWORD (WINAPI *PFN_XInputGetState)(DWORD, XINPUT_STATE *);

typedef struct {
    HMODULE            dll;
    PFN_XInputGetState get_state;
    bool               initialized;
    bool               connected[INPUT_MAX_GAMEPADS];
    DWORD              last_packet[INPUT_MAX_GAMEPADS];
} GamepadSystemWin;

static GamepadSystemWin g_pad;

/* ---------------------------------------------------------------- */

static f32 normalize_stick(SHORT v, SHORT deadzone) {
    f32 f = (f32)v;
    f32 dz = (f32)deadzone;
    if (f > -dz && f < dz) return 0.0f;
    /* Rescale outside the deadzone to a smooth 0..1 ramp. */
    f32 max = (v < 0) ? 32768.0f : 32767.0f;
    f32 sign = (f < 0.0f) ? -1.0f : 1.0f;
    f32 mag = (f < 0.0f ? -f : f);
    f32 n = (mag - dz) / (max - dz);
    if (n < 0.0f) n = 0.0f;
    if (n > 1.0f) n = 1.0f;
    return sign * n;
}

static f32 normalize_trigger_win(BYTE v) {
    if (v <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD) return 0.0f;
    f32 n = (f32)(v - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) /
            (255.0f - (f32)XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
    if (n > 1.0f) n = 1.0f;
    return n;
}

static void apply_button_state(u8 *slot, bool pressed) {
    if (pressed) {
        if (*slot != 2) *slot = 3;
    } else {
        if (*slot == 3 || *slot == 2) *slot = 1;
    }
}

static void map_buttons(const XINPUT_GAMEPAD *gp, GamepadState *s) {
    WORD w = gp->wButtons;
    apply_button_state(&s->buttons[GAMEPAD_BTN_SOUTH],     w & XINPUT_GAMEPAD_A);
    apply_button_state(&s->buttons[GAMEPAD_BTN_EAST],      w & XINPUT_GAMEPAD_B);
    apply_button_state(&s->buttons[GAMEPAD_BTN_WEST],      w & XINPUT_GAMEPAD_X);
    apply_button_state(&s->buttons[GAMEPAD_BTN_NORTH],     w & XINPUT_GAMEPAD_Y);
    apply_button_state(&s->buttons[GAMEPAD_BTN_LB],        w & XINPUT_GAMEPAD_LEFT_SHOULDER);
    apply_button_state(&s->buttons[GAMEPAD_BTN_RB],        w & XINPUT_GAMEPAD_RIGHT_SHOULDER);
    apply_button_state(&s->buttons[GAMEPAD_BTN_BACK],      w & XINPUT_GAMEPAD_BACK);
    apply_button_state(&s->buttons[GAMEPAD_BTN_START],     w & XINPUT_GAMEPAD_START);
    apply_button_state(&s->buttons[GAMEPAD_BTN_LSTICK],    w & XINPUT_GAMEPAD_LEFT_THUMB);
    apply_button_state(&s->buttons[GAMEPAD_BTN_RSTICK],    w & XINPUT_GAMEPAD_RIGHT_THUMB);
    apply_button_state(&s->buttons[GAMEPAD_BTN_DPAD_UP],   w & XINPUT_GAMEPAD_DPAD_UP);
    apply_button_state(&s->buttons[GAMEPAD_BTN_DPAD_DOWN], w & XINPUT_GAMEPAD_DPAD_DOWN);
    apply_button_state(&s->buttons[GAMEPAD_BTN_DPAD_LEFT], w & XINPUT_GAMEPAD_DPAD_LEFT);
    apply_button_state(&s->buttons[GAMEPAD_BTN_DPAD_RIGHT],w & XINPUT_GAMEPAD_DPAD_RIGHT);
    /* Standard XInput has no Guide button slot. */
}

/* ---------------------------------------------------------------- */

void gamepad_init(void) {
    memset(&g_pad, 0, sizeof(g_pad));

    static const char *dlls[] = {
        "xinput1_4.dll", "xinput1_3.dll", "xinput9_1_0.dll"
    };
    for (int i = 0; i < 3; i++) {
        g_pad.dll = LoadLibraryA(dlls[i]);
        if (g_pad.dll) {
            g_pad.get_state =
                (PFN_XInputGetState)GetProcAddress(g_pad.dll, "XInputGetState");
            if (g_pad.get_state) {
                LOG_INFO("gamepad: XInput backend loaded (%s)", dlls[i]);
                break;
            }
            FreeLibrary(g_pad.dll);
            g_pad.dll = NULL;
        }
    }

    if (!g_pad.get_state) {
        LOG_WARN("gamepad: XInput unavailable — no gamepads");
    }
    g_pad.initialized = true;
}

void gamepad_poll(GamepadState *out_pads) {
    if (!g_pad.initialized || !out_pads || !g_pad.get_state) return;

    int max = (INPUT_MAX_GAMEPADS < XUSER_MAX_COUNT)
                  ? INPUT_MAX_GAMEPADS : XUSER_MAX_COUNT;

    for (int i = 0; i < max; i++) {
        XINPUT_STATE st;
        memset(&st, 0, sizeof(st));
        DWORD res = g_pad.get_state((DWORD)i, &st);
        GamepadState *s = &out_pads[i];

        if (res != ERROR_SUCCESS) {
            if (g_pad.connected[i]) {
                /* Clear state on disconnect frame. */
                memset(s->axes, 0, sizeof(s->axes));
                for (int b = 0; b < INPUT_MAX_PAD_BUTTONS; b++)
                    apply_button_state(&s->buttons[b], false);
                s->connected = false;
                s->name[0]   = 0;
                g_pad.connected[i] = false;
                LOG_INFO("gamepad: disconnected slot=%d", i);
            }
            continue;
        }

        if (!g_pad.connected[i]) {
            g_pad.connected[i] = true;
            s->connected = true;
            snprintf(s->name, sizeof(s->name), "XInput Controller %d", i);
            LOG_INFO("gamepad: connected slot=%d name=\"%s\"", i, s->name);
        }

        const XINPUT_GAMEPAD *gp = &st.Gamepad;
        map_buttons(gp, s);

        s->axes[GAMEPAD_AXIS_LEFT_X]  =  normalize_stick(gp->sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        /* Negate Y so "up" is negative, matching the evdev backend convention. */
        s->axes[GAMEPAD_AXIS_LEFT_Y]  = -normalize_stick(gp->sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        s->axes[GAMEPAD_AXIS_RIGHT_X] =  normalize_stick(gp->sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
        s->axes[GAMEPAD_AXIS_RIGHT_Y] = -normalize_stick(gp->sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
        s->axes[GAMEPAD_AXIS_LTRIGGER] = normalize_trigger_win(gp->bLeftTrigger);
        s->axes[GAMEPAD_AXIS_RTRIGGER] = normalize_trigger_win(gp->bRightTrigger);

        g_pad.last_packet[i] = st.dwPacketNumber;
    }
}

void gamepad_shutdown(void) {
    if (!g_pad.initialized) return;
    if (g_pad.dll) FreeLibrary(g_pad.dll);
    memset(&g_pad, 0, sizeof(g_pad));
}

#endif /* ENGINE_PLATFORM_WINDOWS */
