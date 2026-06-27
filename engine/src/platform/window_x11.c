#include <platform/platform.h>
#include <platform/input.h>
#include <core/log.h>
#include "gamepad_linux.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/Xrandr.h>
#include <string.h>
#include <stdlib.h>

struct Platform {
    Display    *display;
    Window      window;
    Atom        wm_delete;
    Atom        wm_state;
    Atom        wm_fullscreen;
    InputState  input;
    u32         width;
    u32         height;
    bool        should_close;
    bool        is_fullscreen;
    bool        mouse_captured;
    bool        mouse_visible;
    bool        mouse_relative;
    Cursor      invisible_cursor;
    f32         dpi;
    i32         scale_factor;
    MonitorInfo monitors[PLATFORM_MAX_MONITORS];
    u32         monitor_count;
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
    if (ks == XK_Page_Up)   return 283;
    if (ks == XK_Page_Down) return 284;
    if (ks == XK_Home)      return 285;
    if (ks == XK_End)       return 286;
    if (ks == XK_Insert)    return 287;
    if (ks == XK_Delete)    return 288;
    if (ks == XK_minus || ks == XK_underscore)  return (i32)'-';
    if (ks == XK_plus || ks == XK_equal)         return (i32)'=';
    if (ks == XK_parenleft || ks == XK_braceleft)   return (i32)'(';
    if (ks == XK_parenright || ks == XK_braceright) return (i32)')';
    if (ks == XK_bracketleft)  return (i32)'[';
    if (ks == XK_bracketright) return (i32)']';
    if (ks == XK_slash || ks == XK_question) return (i32)'/';
    if (ks == XK_backslash || ks == XK_bar)  return (i32)'\\';
    if (ks == XK_grave || ks == XK_asciitilde) return (i32)'`';
    if (ks == XK_semicolon || ks == XK_colon)   return (i32)';';
    if (ks == XK_apostrophe || ks == XK_quotedbl) return (i32)'\'';
    if (ks == XK_comma)  return (i32)',';
    if (ks == XK_period) return (i32)'.';
    return -1;
}

static void x11_query_monitors(Platform *p) {
    XRRScreenResources *res = XRRGetScreenResources(p->display, DefaultRootWindow(p->display));
    if (!res) {
        p->dpi = 96.0f;
        p->scale_factor = 1;
        return;
    }

    p->monitor_count = 0;
    for (int i = 0; i < res->noutput && p->monitor_count < PLATFORM_MAX_MONITORS; i++) {
        XRROutputInfo *output = XRRGetOutputInfo(p->display, res, res->outputs[i]);
        if (!output || output->connection != RR_Connected) {
            if (output) XRRFreeOutputInfo(output);
            continue;
        }

        XRRCrtcInfo *crtc = NULL;
        if (output->crtc)
            crtc = XRRGetCrtcInfo(p->display, res, output->crtc);

        MonitorInfo *m = &p->monitors[p->monitor_count];
        memset(m, 0, sizeof(MonitorInfo));
        strncpy(m->name, output->name, 63);
        m->name[63] = '\0';

        if (crtc) {
            m->x = crtc->x;
            m->y = crtc->y;
            m->width = (u32)crtc->width;
            m->height = (u32)crtc->height;

            /* Find refresh rate */
            for (int j = 0; j < res->nmode; j++) {
                if (res->modes[j].id == crtc->mode) {
                    XRRModeInfo *mode = &res->modes[j];
                    if (mode->hTotal && mode->vTotal)
                        m->refresh_rate = (u32)((f64)mode->dotClock / ((f64)mode->hTotal * (f64)mode->vTotal));
                    break;
                }
            }
            XRRFreeCrtcInfo(crtc);
        }

        /* Calculate DPI */
        if (output->mm_width > 0 && m->width > 0)
            m->dpi = (f32)m->width / ((f32)output->mm_width / 25.4f);
        else
            m->dpi = 96.0f;

        /* Scale factor (rounded to nearest integer based on DPI) */
        m->scale = (i32)((m->dpi + 48.0f) / 96.0f);
        if (m->scale < 1) m->scale = 1;

        /* Primary monitor heuristic (first connected or at 0,0) */
        m->primary = (m->x == 0 && m->y == 0);

        p->monitor_count++;
        XRRFreeOutputInfo(output);
    }

    XRRFreeScreenResources(res);

    /* Set global DPI from primary monitor */
    if (p->monitor_count > 0) {
        for (u32 i = 0; i < p->monitor_count; i++) {
            if (p->monitors[i].primary) {
                p->dpi = p->monitors[i].dpi;
                p->scale_factor = p->monitors[i].scale;
                return;
            }
        }
        p->dpi = p->monitors[0].dpi;
        p->scale_factor = p->monitors[0].scale;
    } else {
        p->dpi = 96.0f;
        p->scale_factor = 1;
    }
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
    p->wm_state = XInternAtom(p->display, "_NET_WM_STATE", False);
    p->wm_fullscreen = XInternAtom(p->display, "_NET_WM_STATE_FULLSCREEN", False);
    XSetWMProtocols(p->display, p->window, &p->wm_delete, 1);

    XSelectInput(p->display, p->window,
                 ExposureMask | KeyPressMask | KeyReleaseMask |
                 ButtonPressMask | ButtonReleaseMask |
                 PointerMotionMask | StructureNotifyMask);

    XMapWindow(p->display, p->window);
    XFlush(p->display);

    p->mouse_captured = false;
    p->mouse_visible = true;
    p->mouse_relative = false;
    p->invisible_cursor = 0;

    input_init(&p->input);
    gamepad_init();

    x11_query_monitors(p);

    LOG_INFO("Platform initialized: %ux%u \"%s\" (DPI=%.1f scale=%d monitors=%u)",
             cfg->width, cfg->height, cfg->title, p->dpi, p->scale_factor, p->monitor_count);
    return p;
}

void platform_destroy(Platform *p) {
    if (!p) return;
    gamepad_shutdown();
    if (p->display) {
        if (p->invisible_cursor) XFreeCursor(p->display, p->invisible_cursor);
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
        case MotionNotify: {
            if (p->mouse_relative) {
                i32 cx = (i32)(p->width / 2);
                i32 cy = (i32)(p->height / 2);
                i32 dx = ev.xmotion.x - cx;
                i32 dy = ev.xmotion.y - cy;
                if (dx != 0 || dy != 0) {
                    p->input.mouse_dx += (f32)dx;
                    p->input.mouse_dy += (f32)dy;
                    XWarpPointer(p->display, None, p->window, 0, 0, 0, 0, cx, cy);
                }
            } else {
                input_set_mouse(&p->input, (f32)ev.xmotion.x, (f32)ev.xmotion.y);
            }
            break;
        }
        case ButtonPress: {
            i32 btn = ev.xbutton.button;
            if (btn == Button1)      input_set_key(&p->input, INPUT_MOUSE_LEFT,   true);
            else if (btn == Button2) input_set_key(&p->input, INPUT_MOUSE_MIDDLE, true);
            else if (btn == Button3) input_set_key(&p->input, INPUT_MOUSE_RIGHT,  true);
            else if (btn == 4)       input_set_scroll(&p->input, 0.0f,  1.0f);
            else if (btn == 5)       input_set_scroll(&p->input, 0.0f, -1.0f);
            else if (btn == 8)       input_set_key(&p->input, INPUT_MOUSE_4, true);
            else if (btn == 9)       input_set_key(&p->input, INPUT_MOUSE_5, true);
            break;
        }
        case ButtonRelease: {
            i32 btn = ev.xbutton.button;
            if (btn == Button1)      input_set_key(&p->input, INPUT_MOUSE_LEFT,   false);
            else if (btn == Button2) input_set_key(&p->input, INPUT_MOUSE_MIDDLE, false);
            else if (btn == Button3) input_set_key(&p->input, INPUT_MOUSE_RIGHT,  false);
            else if (btn == 8)       input_set_key(&p->input, INPUT_MOUSE_4, false);
            else if (btn == 9)       input_set_key(&p->input, INPUT_MOUSE_5, false);
            break;
        }

        case ConfigureNotify:
            p->width  = (u32)ev.xconfigure.width;
            p->height = (u32)ev.xconfigure.height;
            break;
        }
    }

    /* Pump gamepads (evdev) into the shared input state. */
    gamepad_poll(p->input.gamepads);

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

void *platform_surface_native(Platform *p) {
    return (void *)(uintptr_t)p->window;
}

void platform_get_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p->width;
    if (h) *h = p->height;
}

void platform_mouse_capture(Platform *p, bool capture) {
    if (capture && !p->mouse_captured) {
        XGrabPointer(p->display, p->window, True,
                     ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                     GrabModeAsync, GrabModeAsync, p->window, None, CurrentTime);
        p->mouse_captured = true;
    } else if (!capture && p->mouse_captured) {
        XUngrabPointer(p->display, CurrentTime);
        p->mouse_captured = false;
    }
}

void platform_mouse_set_visible(Platform *p, bool visible) {
    if (!visible && p->mouse_visible) {
        if (!p->invisible_cursor) {
            Pixmap blank = XCreatePixmap(p->display, p->window, 1, 1, 1);
            XColor dummy = {0};
            p->invisible_cursor = XCreatePixmapCursor(p->display, blank, blank,
                                                     &dummy, &dummy, 0, 0);
            XFreePixmap(p->display, blank);
        }
        XDefineCursor(p->display, p->window, p->invisible_cursor);
    } else if (visible && !p->mouse_visible) {
        XUndefineCursor(p->display, p->window);
    }
    p->mouse_visible = visible;
}

void platform_mouse_set_relative(Platform *p, bool relative) {
    p->mouse_relative = relative;
    if (relative) {
        platform_mouse_capture(p, true);
        platform_mouse_set_visible(p, false);
        XWarpPointer(p->display, None, p->window, 0, 0, 0, 0,
                     (i32)(p->width / 2), (i32)(p->height / 2));
        XFlush(p->display);
    } else {
        platform_mouse_capture(p, false);
        platform_mouse_set_visible(p, true);
    }
}

f32 platform_get_dpi(Platform *p) {
    return p->dpi;
}

i32 platform_get_scale_factor(Platform *p) {
    return p->scale_factor;
}

u32 platform_get_monitor_count(Platform *p) {
    return p->monitor_count;
}

bool platform_get_monitor_info(Platform *p, u32 index, MonitorInfo *out) {
    if (index >= p->monitor_count || !out) return false;
    *out = p->monitors[index];
    return true;
}

void platform_toggle_fullscreen(Platform *p) {
    XEvent ev = {0};
    ev.type = ClientMessage;
    ev.xclient.window = p->window;
    ev.xclient.message_type = p->wm_state;
    ev.xclient.format = 32;
    ev.xclient.data.l[0] = p->is_fullscreen ? 0 : 1;
    ev.xclient.data.l[1] = (long)p->wm_fullscreen;
    ev.xclient.data.l[2] = 0;
    XSendEvent(p->display, DefaultRootWindow(p->display), False,
               SubstructureRedirectMask | SubstructureNotifyMask, &ev);
    XFlush(p->display);
    p->is_fullscreen = !p->is_fullscreen;
}
