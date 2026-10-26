#pragma once

/* Borderless-fullscreen window mode: the backend-independent state machine
 * every window backend drives (docs/superpowers/specs/
 * 2026-10-27-borderless-fullscreen-design.md). Header-only and free of native
 * calls so it is testable on every host (test_platform_window_mode).
 *
 * Win32, Cocoa and the X11 no-WM fallback switch synchronously: request()
 * then confirm() at once. X11 (EWMH) and Wayland ask the window manager /
 * compositor and confirm() from the reply (_NET_WM_STATE PropertyNotify,
 * xdg_toplevel configure states), which may also report a switch nobody
 * requested (a WM shortcut) or a refusal. */

#include <platform/platform.h>
#include <platform/monitor_selection.h>

#include <string.h>

#if defined(__GNUC__) || defined(__clang__)
#define PLATFORM_WM_INLINE static inline __attribute__((unused))
#else
#define PLATFORM_WM_INLINE static inline
#endif

typedef struct {
    i32 x, y;
    u32 width, height;
} PlatformWindowRect;

typedef enum {
    PLATFORM_WINDOW_MODE_ACTION_NONE = 0,     /* already there (or already asked) */
    PLATFORM_WINDOW_MODE_ACTION_ENTER,        /* go borderless fullscreen */
    PLATFORM_WINDOW_MODE_ACTION_LEAVE,        /* go back to the saved window */
    PLATFORM_WINDOW_MODE_ACTION_UNSUPPORTED,  /* fixed-mode platform */
} PlatformWindowModeAction;

typedef struct {
    PlatformWindowMode current;    /* last mode the platform confirmed */
    PlatformWindowMode requested;  /* last mode asked for (== current when idle) */
    bool pending;                  /* a request is waiting for confirmation */
    bool fixed;                    /* mobile / QNX Screen: mode cannot change */
    bool saved_valid;
    bool saved_maximized;
    PlatformWindowRect saved;      /* windowed rect to restore on LEAVE */
} PlatformWindowModeState;

PLATFORM_WM_INLINE bool platform_window_mode_valid(PlatformWindowMode mode)
{
    return mode == PLATFORM_WINDOW_MODE_WINDOWED ||
           mode == PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN;
}

PLATFORM_WM_INLINE void platform_window_mode_init(PlatformWindowModeState *s,
                                                  PlatformWindowMode mode)
{
    if (s == NULL) return;
    memset(s, 0, sizeof(*s));
    if (!platform_window_mode_valid(mode)) mode = PLATFORM_WINDOW_MODE_WINDOWED;
    s->current = mode;
    s->requested = mode;
}

/* A platform whose surface is always the whole screen. */
PLATFORM_WM_INLINE void platform_window_mode_init_fixed(PlatformWindowModeState *s,
                                                        PlatformWindowMode mode)
{
    platform_window_mode_init(s, mode);
    if (s != NULL) s->fixed = true;
}

/* What the backend has to do to reach `mode`. Asking again for the mode a
 * pending request already targets is NONE; asking for the opposite of a
 * pending request returns the action that reaches it (the last request
 * wins once the platform has answered both). */
PLATFORM_WM_INLINE PlatformWindowModeAction platform_window_mode_request(
    PlatformWindowModeState *s, PlatformWindowMode mode)
{
    if (s == NULL || !platform_window_mode_valid(mode))
        return PLATFORM_WINDOW_MODE_ACTION_NONE;
    if (s->fixed)
        return mode == s->current ? PLATFORM_WINDOW_MODE_ACTION_NONE
                                  : PLATFORM_WINDOW_MODE_ACTION_UNSUPPORTED;
    if (mode == s->requested) return PLATFORM_WINDOW_MODE_ACTION_NONE;
    s->requested = mode;
    s->pending = true;
    return mode == PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN
               ? PLATFORM_WINDOW_MODE_ACTION_ENTER
               : PLATFORM_WINDOW_MODE_ACTION_LEAVE;
}

/* The platform reports the mode the window is really in. Ends the pending
 * request once the reported mode is the requested one; a report while idle
 * is an external switch and becomes the new requested mode too. */
PLATFORM_WM_INLINE void platform_window_mode_confirm(PlatformWindowModeState *s,
                                                     PlatformWindowMode mode)
{
    if (s == NULL || s->fixed || !platform_window_mode_valid(mode)) return;
    s->current = mode;
    if (!s->pending) {
        s->requested = mode;
        return;
    }
    if (mode == s->requested) s->pending = false;
}

/* The platform could not carry out the pending request (refused, failed):
 * stay in the confirmed mode. */
PLATFORM_WM_INLINE void platform_window_mode_fail(PlatformWindowModeState *s)
{
    if (s == NULL) return;
    s->requested = s->current;
    s->pending = false;
}

/* Mode a toggle should ask for: the opposite of the latest request, so two
 * quick toggles before the first confirm go there and back. */
PLATFORM_WM_INLINE PlatformWindowMode platform_window_mode_toggle_target(
    const PlatformWindowModeState *s)
{
    if (s == NULL) return PLATFORM_WINDOW_MODE_WINDOWED;
    return s->requested == PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN
               ? PLATFORM_WINDOW_MODE_WINDOWED
               : PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN;
}

/* Remember the windowed geometry before entering fullscreen. */
PLATFORM_WM_INLINE void platform_window_mode_save_windowed(PlatformWindowModeState *s,
                                                           PlatformWindowRect r,
                                                           bool maximized)
{
    if (s == NULL) return;
    s->saved = r;
    s->saved_maximized = maximized;
    s->saved_valid = r.width > 0u && r.height > 0u;
}

PLATFORM_WM_INLINE bool platform_window_mode_restore_rect(const PlatformWindowModeState *s,
                                                          PlatformWindowRect *out)
{
    if (s == NULL || out == NULL || !s->saved_valid) return false;
    *out = s->saved;
    return true;
}

PLATFORM_WM_INLINE bool platform_window_mode_restore_maximized(const PlatformWindowModeState *s,
                                                               bool *out)
{
    if (s == NULL || out == NULL || !s->saved_valid) return false;
    *out = s->saved_maximized;
    return true;
}

/* Fullscreen covers the monitor that holds most of the window (closest one
 * when the window is between monitors), same rule as DPI selection. */
PLATFORM_WM_INLINE bool platform_window_mode_fullscreen_rect(const MonitorInfo *monitors,
                                                             u32 monitor_count,
                                                             PlatformWindowRect window,
                                                             PlatformWindowRect *out)
{
    i32 i;
    if (out == NULL) return false;
    i = platform_monitor_select(monitors, monitor_count, window.x, window.y,
                                window.width, window.height);
    if (i < 0) return false;
    out->x = monitors[i].x;
    out->y = monitors[i].y;
    out->width = monitors[i].width;
    out->height = monitors[i].height;
    return out->width > 0u && out->height > 0u;
}

#undef PLATFORM_WM_INLINE
