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
#include <platform/win_proc.h>
#include <platform/time.h>
#include <core/types.h>
#include <core/log.h>

#include "gamepad_linux.h"  /* shared gamepad_init/poll/shutdown prototypes */

/* XInput exposes at most 4 controllers — matches INPUT_MAX_GAMEPADS. */
#ifndef XUSER_MAX_COUNT
#define XUSER_MAX_COUNT 4
#endif

typedef DWORD (WINAPI *PFN_XInputGetState)(DWORD, XINPUT_STATE *);
typedef DWORD (WINAPI *PFN_XInputSetState)(DWORD, XINPUT_VIBRATION *);
typedef DWORD (WINAPI *PFN_XInputGetCapabilities)(DWORD, DWORD, XINPUT_CAPABILITIES *);

#ifndef XINPUT_CAPS_FFB_SUPPORTED
#define XINPUT_CAPS_FFB_SUPPORTED 0x0001
#endif

typedef struct {
    HMODULE                   dll;
    PFN_XInputGetState        get_state;
    PFN_XInputSetState        set_state;
    PFN_XInputGetCapabilities get_capabilities;
    bool                      initialized;
    bool                      connected[INPUT_MAX_GAMEPADS];
    bool                      feedback_available[INPUT_MAX_GAMEPADS];
    bool                      vibration_active[INPUT_MAX_GAMEPADS];
    u64                       stop_deadline_us[INPUT_MAX_GAMEPADS];
    u32                       connection_serial[INPUT_MAX_GAMEPADS];
    u32                       next_serial;
    DWORD                     last_packet[INPUT_MAX_GAMEPADS];
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
    /* R570: not idempotent — a second call would overwrite g_pad.dll and leak
     * the xinput HMODULE. Early-return once initialized. */
    if (g_pad.initialized) return;
    memset(&g_pad, 0, sizeof(g_pad));

    static const char *dlls[] = {
        "xinput1_4.dll", "xinput1_3.dll", "xinput9_1_0.dll"
    };
    for (int i = 0; i < 3; i++) {
        g_pad.dll = LoadLibraryA(dlls[i]);
        if (g_pad.dll) {
            g_pad.get_state = NULL;
            WIN_PROC_LOAD(g_pad.get_state,
                          GetProcAddress(g_pad.dll, "XInputGetState"));
            if (g_pad.get_state) {
                WIN_PROC_LOAD(g_pad.set_state,
                              GetProcAddress(g_pad.dll, "XInputSetState"));
                WIN_PROC_LOAD(g_pad.get_capabilities,
                              GetProcAddress(g_pad.dll, "XInputGetCapabilities"));
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

static void win_query_feedback(u32 pad) {
    bool available = g_pad.set_state != NULL;
    if (g_pad.get_capabilities != NULL) {
        XINPUT_CAPABILITIES capabilities;
        memset(&capabilities, 0, sizeof(capabilities));
        if (g_pad.get_capabilities(pad, 0, &capabilities) == ERROR_SUCCESS) {
            available = available &&
                        (capabilities.Flags & XINPUT_CAPS_FFB_SUPPORTED) != 0;
        }
    }
    g_pad.feedback_available[pad] = available;
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
                g_pad.feedback_available[i] = false;
                g_pad.vibration_active[i] = false;
                LOG_INFO("gamepad: disconnected slot=%d", i);
            }
            continue;
        }

        if (!g_pad.connected[i]) {
            g_pad.connected[i] = true;
            g_pad.next_serial++;
            if (g_pad.next_serial == 0u) g_pad.next_serial++;
            g_pad.connection_serial[i] = g_pad.next_serial;
            win_query_feedback((u32)i);
            s->connected = true;
            snprintf(s->name, sizeof(s->name), "XInput Controller %d", i);
            LOG_INFO("gamepad: connected slot=%d name=\"%s\" feedback=%d",
                     i, s->name, g_pad.feedback_available[i] ? 1 : 0);
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

static InputExtResult win_execute_haptic(void *context,
                                         const InputHapticCommand *command) {
    XINPUT_VIBRATION vibration;
    DWORD result;
    u32 pad;
    (void)context;
    if (command == NULL || command->pad >= INPUT_MAX_GAMEPADS)
        return INPUT_EXT_INVALID;
    pad = command->pad;
    if (!g_pad.connected[pad]) return INPUT_EXT_DISCONNECTED;
    if (!g_pad.feedback_available[pad] || g_pad.set_state == NULL)
        return INPUT_EXT_UNSUPPORTED;
    vibration.wLeftMotorSpeed = (WORD)(command->low * 65535.0f + 0.5f);
    vibration.wRightMotorSpeed = (WORD)(command->high * 65535.0f + 0.5f);
    result = g_pad.set_state(pad, &vibration);
    if (result == ERROR_SUCCESS) {
        g_pad.vibration_active[pad] = command->duration_ms != 0u;
        g_pad.stop_deadline_us[pad] = command->duration_ms == 0u
            ? 0u : time_microseconds() + (u64)command->duration_ms * 1000u;
        return INPUT_EXT_OK;
    }
    if (result == ERROR_DEVICE_NOT_CONNECTED) {
        g_pad.connected[pad] = false;
        g_pad.feedback_available[pad] = false;
        g_pad.vibration_active[pad] = false;
        return INPUT_EXT_DISCONNECTED;
    }
    return INPUT_EXT_FAILED;
}

static void win_haptic_tick(u64 now_us) {
    for (u32 i = 0; i < INPUT_MAX_GAMEPADS; i++) {
        XINPUT_VIBRATION stop;
        if (!g_pad.vibration_active[i] || now_us < g_pad.stop_deadline_us[i])
            continue;
        stop.wLeftMotorSpeed = 0;
        stop.wRightMotorSpeed = 0;
        if (g_pad.connected[i] && g_pad.set_state != NULL &&
            g_pad.set_state(i, &stop) == ERROR_DEVICE_NOT_CONNECTED) {
            g_pad.connected[i] = false;
            g_pad.feedback_available[i] = false;
        }
        g_pad.vibration_active[i] = false;
        g_pad.stop_deadline_us[i] = 0;
    }
}

static void win_sync_haptic_pads(InputExtended *extended) {
    for (u32 i = 0; i < INPUT_MAX_GAMEPADS; i++) {
        input_extended_backend_pad(extended, i, g_pad.connected[i],
                                   g_pad.feedback_available[i],
                                   g_pad.connection_serial[i]);
    }
}

void gamepad_feedback_poll(InputExtended *extended) {
    if (!g_pad.initialized || extended == NULL) return;
    win_sync_haptic_pads(extended);
    (void)input_extended_haptic_pump(extended, win_execute_haptic, NULL);
    win_haptic_tick(time_microseconds());
    win_sync_haptic_pads(extended);
}

void gamepad_shutdown(void) {
    if (!g_pad.initialized) return;
    for (u32 i = 0; i < INPUT_MAX_GAMEPADS; i++) {
        if (g_pad.vibration_active[i] && g_pad.connected[i] && g_pad.set_state != NULL) {
            XINPUT_VIBRATION stop;
            stop.wLeftMotorSpeed = 0;
            stop.wRightMotorSpeed = 0;
            (void)g_pad.set_state(i, &stop);
        }
    }
    if (g_pad.dll) FreeLibrary(g_pad.dll);
    memset(&g_pad, 0, sizeof(g_pad));
}

#endif /* ENGINE_PLATFORM_WINDOWS */
