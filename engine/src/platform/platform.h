#pragma once
#include <core/types.h>
#include <platform/input.h>

typedef struct Platform Platform;

typedef struct {
    u32 width;
    u32 height;
    const char *title;
} PlatformConfig;

typedef enum {
    PLATFORM_EVENT_NONE,
    PLATFORM_EVENT_QUIT,
} PlatformEventResult;

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
InputState         *platform_input(Platform *p);
void               *platform_window_native(Platform *p);
void               *platform_display_native(Platform *p);
void               *platform_surface_native(Platform *p);
void                platform_get_size(Platform *p, u32 *w, u32 *h);
void                platform_toggle_fullscreen(Platform *p);
void                platform_mouse_capture(Platform *p, bool capture);
void                platform_mouse_set_visible(Platform *p, bool visible);
void                platform_mouse_set_relative(Platform *p, bool relative);

/* High DPI */
f32                 platform_get_dpi(Platform *p);
i32                 platform_get_scale_factor(Platform *p);

/* Multi-monitor */
u32                 platform_get_monitor_count(Platform *p);
bool                platform_get_monitor_info(Platform *p, u32 index, MonitorInfo *out);
