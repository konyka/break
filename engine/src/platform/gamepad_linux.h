#pragma once

/* Public API for the platform-specific gamepad backend.
 *
 * Implementations:
 *   - Linux: gamepad_linux.c (evdev / /dev/input/event*)
 *
 * On platforms without an implementation these symbols may be stubbed
 * out by the platform layer (see CMakeLists.txt).
 */

#include <platform/input.h>
#include <platform/input_extended.h>

/* Initialize the gamepad subsystem. Safe to call exactly once during
 * platform startup. Failures (missing /dev/input, permission denied,
 * etc.) are logged but never fatal. */
void gamepad_init(void);

/* Pump all queued events for every connected gamepad and write the
 * resulting per-pad state into out_pads (must point to an array with
 * at least INPUT_MAX_GAMEPADS entries — typically &input.gamepads[0]).
 *
 * Designed to be called once per frame after input_new_frame(). */
void gamepad_poll(GamepadState *out_pads);

/* Executes queued feedback only on the platform polling thread. */
void gamepad_feedback_poll(InputExtended *extended);

/* Tear down the gamepad subsystem and release every owned descriptor. */
void gamepad_shutdown(void);
