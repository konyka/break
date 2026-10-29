#pragma once
#include <core/types.h>
#include <platform/input.h>
#include <platform/platform_wsi.h>

typedef struct Platform Platform;

enum {
    PLATFORM_MEDIA_CAP_HOVER = 1u << 0,
    PLATFORM_MEDIA_CAP_POINTER_COARSE = 1u << 1,
    PLATFORM_MEDIA_CAP_POINTER_FINE = 1u << 2,
    PLATFORM_MEDIA_CAP_ANY_POINTER_COARSE = 1u << 3,
    PLATFORM_MEDIA_CAP_ANY_POINTER_FINE = 1u << 4,
    PLATFORM_MEDIA_CAP_COLOR_SRGB = 1u << 5,
    PLATFORM_MEDIA_CAP_COLOR_P3 = 1u << 6,
    PLATFORM_MEDIA_CAP_COLOR_REC2020 = 1u << 7,
    PLATFORM_MEDIA_CAP_HDR = 1u << 8,
};

enum {
    PLATFORM_MEDIA_KNOWN_HOVER = 1u << 0,
    PLATFORM_MEDIA_KNOWN_POINTER = 1u << 1,
    PLATFORM_MEDIA_KNOWN_ANY_POINTER = 1u << 2,
    PLATFORM_MEDIA_KNOWN_COLOR_GAMUT = 1u << 3,
    PLATFORM_MEDIA_KNOWN_HDR = 1u << 4,
    PLATFORM_MEDIA_KNOWN_COLOR_SCHEME = 1u << 5,
    PLATFORM_MEDIA_KNOWN_REDUCED_MOTION = 1u << 6,
};

typedef struct {
    bool screen;
    bool prefers_dark;
    bool prefers_reduced_motion;
    u32 capabilities;
    u32 known;
} PlatformMediaContext;

typedef enum {
    PLATFORM_CURSOR_ARROW = 0,
    PLATFORM_CURSOR_TEXT,
    PLATFORM_CURSOR_HAND,
} PlatformCursor;

typedef struct {
    u32 width;
    u32 height;
    const char *title;
    void *native_window;
    void *native_display;
    bool hide_window_until_first_frame;
    /* Create the window already in PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN.
     * New fields go after this one: PlatformConfig is brace-initialised
     * positionally by existing callers. */
    bool start_fullscreen;
    /* Create the windowed window without title bar and frame (see
     * platform_set_window_decorated). */
    bool undecorated;
    /* Host-provided mobile content scale; zero selects 1.0. */
    f32 native_content_scale;
} PlatformConfig;

/* Keep native window dimensions representable on every supported backend. */
#define PLATFORM_MAX_WINDOW_DIMENSION 16384u
#define PLATFORM_MAX_WINDOW_TITLE_BYTES 4096u

bool platform_config_valid(const PlatformConfig *cfg);
/* Best-effort visibility controls. Wayland has no toplevel hide primitive;
 * its hidden startup path commits no application buffer until show. */
void platform_window_hide(Platform *p);
void platform_window_show(Platform *p);

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
/* Undo a pending close request (the window's close button / WM delete) so
 * the next platform_poll does not report PLATFORM_EVENT_QUIT again — for an
 * app that refuses the close (unsaved changes). Display/connection errors
 * are not cancellable. NULL: no-op. */
void                platform_cancel_close(Platform *p);
/* Retitles the window (UTF-8). false for NULL arguments, invalid UTF-8 or
 * a backend without a window title (mobile, QNX screen). */
bool                platform_set_window_title(Platform *p, const char *utf8);
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
/* Window mode. BORDERLESS_FULLSCREEN = no title bar or frame, covering the
 * monitor the window is on, display mode unchanged (not exclusive), so the
 * swapchain only resizes and Alt-Tab never blanks the screen. */
typedef enum {
    PLATFORM_WINDOW_MODE_WINDOWED = 0,
    PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN,
} PlatformWindowMode;
/* Idempotent. false for NULL, an invalid mode, or a mode the platform cannot
 * enter (mobile / QNX Screen are always fullscreen). */
bool                platform_set_window_mode(Platform *p, PlatformWindowMode mode);
/* Last mode the platform confirmed; WINDOWED for NULL. */
PlatformWindowMode  platform_get_window_mode(Platform *p);
/* set_window_mode(toggle target of the latest request). */
void                platform_toggle_fullscreen(Platform *p);
/* Title bar + frame of the WINDOWED window. false = frameless window of the
 * same client size and position (still movable through
 * platform_window_begin_move, resizable only by the app). Fullscreen never
 * has a title bar; a change made while fullscreen (or while a mode switch is
 * in flight) is kept and applied when the window is windowed again.
 * Idempotent. Returns false for NULL, or decorated=true on a platform that
 * has no window frame (mobile, QNX Screen). */
bool                platform_set_window_decorated(Platform *p, bool decorated);
/* The windowed title-bar preference (false for NULL and frameless platforms). */
bool                platform_get_window_decorated(Platform *p);
/* A title bar is on screen now: windowed and decorated. Client-side
 * decoration (Wayland/myui) also counts: see platform_needs_client_decoration. */
bool                platform_window_title_bar_visible(Platform *p);
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
bool                platform_get_media_context(Platform *p,
                                                PlatformMediaContext *out);
/* Monotonic generation for media facts; zero means no platform object. */
u64                 platform_get_media_generation(Platform *p);

/* Multi-monitor */
u32                 platform_get_monitor_count(Platform *p);
bool                platform_get_monitor_info(Platform *p, u32 index, MonitorInfo *out);

/* ---- WSI surface 状态机（platform_wsi.h）---- */
/* 当前 WSI 状态快照；p 或 out 为 NULL 返回 false。 */
bool platform_wsi_surface_query(Platform *p, PlatformWsiSurface *out);
/* 设备级 WSI 状态对象的非拥有指针（挂到 RHIDevice 用，见 rhi_device_attach_wsi；
 * Platform 拥有存储，生命周期长于任何 RHIDevice 使用窗口）。 */
PlatformWsiSurface *platform_wsi_surface(Platform *p);
/* 在移动宿主线程同步到引擎线程后调用；桌面后端不接管窗口尺寸，返回 false。 */
bool platform_mobile_resize(Platform *p, u32 logical_width, u32 logical_height,
                            u32 drawable_width, u32 drawable_height, f32 scale);
/* 移动宿主回调（iOS/Android 的 host-injection 入口，window_mobile.c 真实实现；
 * 桌面后端是 no-op——桌面没有 OS 级 suspend/resume/surface-lost 事件，相应语义
 * 由 resize 与 DESTROYING 覆盖）。 */
void platform_mobile_notify_suspend(Platform *p);
void platform_mobile_notify_resume(Platform *p);
void platform_mobile_notify_surface_lost(Platform *p);
void platform_mobile_notify_surface_recreated(Platform *p, void *native_window,
                                              u32 width, u32 height);
