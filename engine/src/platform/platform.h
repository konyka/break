#pragma once
#include <core/types.h>
#include <platform/input.h>

typedef struct Platform Platform;

typedef enum {
    PLATFORM_CURSOR_ARROW = 0,
    PLATFORM_CURSOR_TEXT,
    PLATFORM_CURSOR_HAND,
} PlatformCursor;

typedef struct {
    u32 width;
    u32 height;
    const char *title;
} PlatformConfig;

typedef enum {
    PLATFORM_EVENT_NONE,
    PLATFORM_EVENT_QUIT,
} PlatformEventResult;

typedef enum {
    PLATFORM_TEXT_COMMIT,
    PLATFORM_TEXT_PREEDIT,
    PLATFORM_TEXT_CANDIDATE,
    PLATFORM_TEXT_DELETE_SURROUNDING,
} PlatformTextType;

typedef enum {
    PLATFORM_CLIPBOARD_EMPTY,
    PLATFORM_CLIPBOARD_READY,
    PLATFORM_CLIPBOARD_PENDING,
} PlatformClipboardResult;

typedef struct {
    PlatformTextType type;
    char utf8[64];
    char *utf8_extra;
    usize utf8_bytes;
    i32 cursor;
    i32 before;
    i32 after;
} PlatformTextEvent;

#define PLATFORM_MAX_MONITORS 8

typedef struct {
    char name[64];
    i32 x, y;             /* position offset */
    u32 width, height;    /* pixel resolution */
    u32 refresh_rate;     /* Hz */
    f32 dpi;              /* DPI */
    i32 scale;            /* scale factor (1, 2, 3...) */
    bool primary;
} MonitorInfo;

Platform           *platform_create(const PlatformConfig *cfg);
void                platform_destroy(Platform *p);
PlatformEventResult platform_poll(Platform *p);
u32                 platform_poll_text(Platform *p, PlatformTextEvent *out,
                                       u32 max_events);
void                platform_ime_set_enabled(Platform *p, bool enabled);
bool                platform_ime_is_enabled(Platform *p);
void                platform_ime_set_surrounding(Platform *p, const char *utf8,
                                                  i32 cursor, i32 anchor);
void                platform_ime_set_spot(Platform *p, i32 x, i32 y);
InputState         *platform_input(Platform *p);
/* OpenGL native target (for example wl_egl_window on Wayland). */
void               *platform_window_native(Platform *p);
void               *platform_display_native(Platform *p);
/* Vulkan WSI surface target (for example wl_surface on Wayland). */
void               *platform_surface_native(Platform *p);
/* Native client size in the platform's event-coordinate unit. */
void                platform_get_size(Platform *p, u32 *w, u32 *h);
/* UI layout size in logical pixels. */
void                platform_get_logical_size(Platform *p, u32 *w, u32 *h);
/* Physical drawable size used by GL/Vulkan framebuffers and swapchains. */
void                platform_get_drawable_size(Platform *p, u32 *w, u32 *h);
void                platform_toggle_fullscreen(Platform *p);
void                platform_mouse_capture(Platform *p, bool capture);
void                platform_mouse_set_visible(Platform *p, bool visible);
void                platform_mouse_set_relative(Platform *p, bool relative);
bool                platform_cursor_set(Platform *p, PlatformCursor cursor);
bool                platform_window_begin_move(Platform *p);
bool                platform_needs_client_decoration(Platform *p);
bool                platform_clipboard_set_text(Platform *p, const char *utf8);
bool                platform_clipboard_get_text(Platform *p, char *out,
                                                usize out_size);
PlatformClipboardResult platform_clipboard_get_text_alloc(Platform *p,
                                                           char **out);

/* High DPI */
f32                 platform_get_dpi(Platform *p);
f32                 platform_get_content_scale(Platform *p);
/* Input coordinates are divided by this factor before UI dispatch. */
f32                 platform_get_input_scale(Platform *p);
i32                 platform_get_scale_factor(Platform *p);

/* Multi-monitor */
u32                 platform_get_monitor_count(Platform *p);
bool                platform_get_monitor_info(Platform *p, u32 index, MonitorInfo *out);
