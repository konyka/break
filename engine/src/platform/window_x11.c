#include <platform/platform.h>
#include <platform/input.h>
#include <core/log.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <string.h>
#include <stdlib.h>

struct Platform {
    Display    *display;
    Window      window;
    Atom        wm_delete;
    InputState  input;
    u32         width;
    u32         height;
    bool        should_close;
};

static i32 x11_key_to_index(KeySym ks) {
    if (ks >= XK_a && ks <= XK_z) return (i32)ks;
    if (ks >= XK_A && ks <= XK_Z) return (i32)(ks - XK_A + 'a');
    if (ks >= XK_0 && ks <= XK_9) return (i32)ks;
    if (ks == XK_Escape)    return 256;
    if (ks == XK_space)     return 32;
    if (ks == XK_Return)    return 257;
    if (ks == XK_Tab)       return 259;
    if (ks == XK_BackSpace) return 260;
    if (ks == XK_Left)      return 261;
    if (ks == XK_Right)     return 262;
    if (ks == XK_Up)        return 263;
    if (ks == XK_Down)      return 264;
    if (ks >= XK_F1 && ks <= XK_F12) return (i32)(ks - XK_F1 + 271);
    return -1;
}

Platform *platform_create(const PlatformConfig *cfg) {
    Platform *p = calloc(1, sizeof(Platform));
    if (!p) { LOG_FATAL("Failed to allocate Platform"); return NULL; }

    p->display = XOpenDisplay(NULL);
    if (!p->display) {
        LOG_FATAL("Failed to open X11 display");
        free(p);
        return NULL;
    }

    i32 screen = DefaultScreen(p->display);
    p->width  = cfg->width;
    p->height = cfg->height;

    p->window = XCreateSimpleWindow(
        p->display, RootWindow(p->display, screen),
        0, 0, cfg->width, cfg->height, 0,
        BlackPixel(p->display, screen),
        BlackPixel(p->display, screen));

    XStoreName(p->display, p->window, cfg->title);

    p->wm_delete = XInternAtom(p->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(p->display, p->window, &p->wm_delete, 1);

    XSelectInput(p->display, p->window,
                 ExposureMask | KeyPressMask | KeyReleaseMask |
                 ButtonPressMask | ButtonReleaseMask |
                 PointerMotionMask | StructureNotifyMask);

    XMapWindow(p->display, p->window);
    XFlush(p->display);

    input_init(&p->input);

    LOG_INFO("Platform initialized: %ux%u \"%s\"", cfg->width, cfg->height, cfg->title);
    return p;
}

void platform_destroy(Platform *p) {
    if (!p) return;
    if (p->display) {
        XDestroyWindow(p->display, p->window);
        XCloseDisplay(p->display);
    }
    free(p);
    LOG_INFO("Platform destroyed");
}

PlatformEventResult platform_poll(Platform *p) {
    input_new_frame(&p->input);

    while (XPending(p->display) > 0) {
        XEvent ev;
        XNextEvent(p->display, &ev);

        switch (ev.type) {
        case ClientMessage:
            if ((Atom)ev.xclient.data.l[0] == p->wm_delete) {
                p->should_close = true;
                return PLATFORM_EVENT_QUIT;
            }
            break;

        case KeyPress: {
            KeySym ks = XLookupKeysym(&ev.xkey, 0);
            i32 idx = x11_key_to_index(ks);
            if (idx >= 0) input_set_key(&p->input, idx, true);
            break;
        }
        case KeyRelease: {
            KeySym ks = XLookupKeysym(&ev.xkey, 0);
            i32 idx = x11_key_to_index(ks);
            if (idx >= 0) input_set_key(&p->input, idx, false);
            break;
        }
        case MotionNotify:
            input_set_mouse(&p->input, (f32)ev.xmotion.x, (f32)ev.xmotion.y);
            break;

        case ConfigureNotify:
            p->width  = (u32)ev.xconfigure.width;
            p->height = (u32)ev.xconfigure.height;
            break;
        }
    }

    return PLATFORM_EVENT_NONE;
}

InputState *platform_input(Platform *p) {
    return &p->input;
}

void *platform_window_native(Platform *p) {
    return (void *)(uintptr_t)p->window;
}

void *platform_display_native(Platform *p) {
    return (void *)p->display;
}

void platform_get_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p->width;
    if (h) *h = p->height;
}
