#pragma once

/* Public API for the platform-specific pad backend.
 *
 * Implementations:
 *   - Linux: pad_linux.c (evdev / /dev/input/event*)
 *
 * On platforms without an implementation these symbols may be stubbed
 * out by the platform layer (see CMakeLists.txt).
 */

#include <platform/input.h>
#include <platform/input_extended.h>

/* Initialize the pad subsystem. Safe to call exactly once during
 * platform startup. Failures (missing /dev/input, permission denied,
 * etc.) are logged but never fatal. */
void pad_init(void);

/* Pump all queued events for every connected pad and write the
 * resulting per-pad state into out_pads (must point to an array with
 * at least INPUT_MAX_PADS entries — typically &input.pads[0]).
 *
 * Designed to be called once per frame after input_new_frame(). */
void pad_poll(PadState *out_pads);

/* Executes queued feedback only on the platform polling thread. */
void pad_feedback_poll(InputExtended *extended);

/* Tear down the pad subsystem and release every owned descriptor. */
void pad_shutdown(void);
