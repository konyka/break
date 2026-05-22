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

Platform           *platform_create(const PlatformConfig *cfg);
void                platform_destroy(Platform *p);
PlatformEventResult platform_poll(Platform *p);
InputState         *platform_input(Platform *p);
void               *platform_window_native(Platform *p);
void               *platform_display_native(Platform *p);
void                platform_get_size(Platform *p, u32 *w, u32 *h);
