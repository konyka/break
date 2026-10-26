#pragma once

/* Host stand-in for the QNX Screen SDK header: just the declarations
 * window_screen.c uses, so test_platform_screen_simulated can compile the
 * real backend on every host. Implemented in test_platform_screen_simulated.c.
 * Values are arbitrary; real cross builds use the SDK's <screen/screen.h>. */

typedef struct _screen_context *screen_context_t;
typedef struct _screen_window *screen_window_t;
typedef struct _screen_event *screen_event_t;

enum {
    SCREEN_APPLICATION_CONTEXT = 0
};

enum {
    SCREEN_EVENT_NONE = 0,
    SCREEN_EVENT_CLOSE = 1,
    SCREEN_EVENT_POINTER = 2,
    SCREEN_EVENT_KEYBOARD = 3
};

enum {
    SCREEN_PROPERTY_TYPE = 1,
    SCREEN_PROPERTY_SIZE,
    SCREEN_PROPERTY_FORMAT,
    SCREEN_PROPERTY_USAGE,
    SCREEN_PROPERTY_VISIBLE,
    SCREEN_PROPERTY_POSITION,
    SCREEN_PROPERTY_BUTTONS,
    SCREEN_PROPERTY_MOUSE_WHEEL,
    SCREEN_PROPERTY_SYM,
    SCREEN_PROPERTY_FLAGS
};

enum {
    SCREEN_FORMAT_RGBA8888 = 8
};

enum {
    SCREEN_USAGE_READ = 1 << 1,
    SCREEN_USAGE_WRITE = 1 << 2
};

enum {
    SCREEN_LEFT_MOUSE_BUTTON = 1 << 0,
    SCREEN_MIDDLE_MOUSE_BUTTON = 1 << 1,
    SCREEN_RIGHT_MOUSE_BUTTON = 1 << 2
};

int screen_create_context(screen_context_t *pctx, int flags);
int screen_destroy_context(screen_context_t ctx);
int screen_flush_context(screen_context_t ctx, int flags);
int screen_create_window(screen_window_t *pwin, screen_context_t ctx);
int screen_destroy_window(screen_window_t win);
int screen_set_window_property_iv(screen_window_t win, int pname, const int *param);
int screen_get_window_property_iv(screen_window_t win, int pname, int *param);
int screen_create_event(screen_event_t *pev);
int screen_destroy_event(screen_event_t ev);
int screen_get_event(screen_context_t ctx, screen_event_t ev, unsigned long long timeout);
int screen_get_event_property_iv(screen_event_t ev, int pname, int *param);
