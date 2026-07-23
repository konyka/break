#ifdef ENGINE_PLATFORM_WAYLAND

#include <platform/platform.h>
#include <platform/input.h>
#include <core/log.h>
#include "gamepad_linux.h"

#include <wayland-client.h>
#include <wayland-egl.h>
#include <xkbcommon/xkbcommon.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input-event-codes.h>

#include "xdg-shell-client-protocol.h"
#include "relative-pointer-unstable-v1-client-protocol.h"
#include "pointer-constraints-unstable-v1-client-protocol.h"

/* ---- Platform state ---- */

struct Platform {
    struct wl_display    *display;
    struct wl_registry   *registry;
    struct wl_compositor *compositor;
    struct wl_surface    *surface;
    struct wl_seat       *seat;
    struct wl_keyboard   *keyboard;
    struct wl_pointer    *pointer;
    struct wl_output     *output;
    struct xdg_wm_base   *xdg_wm_base;
    struct xdg_surface   *xdg_surface;
    struct xdg_toplevel  *toplevel;

    /* Relative pointer + pointer constraints (unstable v1) */
    struct zwp_relative_pointer_manager_v1 *rel_pointer_mgr;
    struct zwp_pointer_constraints_v1      *pointer_constraints;
    struct zwp_relative_pointer_v1         *rel_pointer;
    struct zwp_locked_pointer_v1           *locked_pointer;

    /* EGL / Vulkan window */
    struct wl_egl_window *egl_window;

    /* XKB keyboard state */
    struct xkb_context  *xkb_ctx;
    struct xkb_keymap   *xkb_keymap;
    struct xkb_state    *xkb_state;

    InputState input;
    u32 width, height;
    bool should_close;
    bool configured;
    bool is_fullscreen;
    i32 scale;

    /* Mouse state */
    bool mouse_captured;
    bool mouse_visible;
    bool mouse_relative;
    f64 pointer_x, pointer_y;
    u32 pointer_enter_serial;   /* needed for wl_pointer_set_cursor */

    /* DPI / Monitor */
    f32 dpi;
    MonitorInfo monitors[PLATFORM_MAX_MONITORS];
    u32 monitor_count;
};

/* Forward decls for relative-pointer wiring. */
static void wayland_apply_relative(Platform *p);
static void wayland_clear_relative(Platform *p);
static void wayland_update_cursor_visibility(Platform *p);

/* ---- Key mapping (XKB keysyms are identical to X11 KeySyms) ---- */

static i32 wayland_keysym_to_engine(xkb_keysym_t ks) {
    if (ks >= XKB_KEY_a && ks <= XKB_KEY_z) return (i32)ks;
    if (ks >= XKB_KEY_A && ks <= XKB_KEY_Z) return (i32)(ks - XKB_KEY_A + 'a');
    if (ks >= XKB_KEY_0 && ks <= XKB_KEY_9) return (i32)ks;
    if (ks == XKB_KEY_Escape)    return 256;
    if (ks == XKB_KEY_space)     return 32;
    if (ks == XKB_KEY_Return)    return 257;
    if (ks == XKB_KEY_Tab)       return 259;
    if (ks == XKB_KEY_BackSpace) return 260;
    if (ks == XKB_KEY_Left)      return 261;
    if (ks == XKB_KEY_Right)     return 262;
    if (ks == XKB_KEY_Up)        return 263;
    if (ks == XKB_KEY_Down)      return 264;
    if (ks >= XKB_KEY_F1 && ks <= XKB_KEY_F12) return (i32)(ks - XKB_KEY_F1 + 271);
    if (ks == XKB_KEY_Page_Up)   return 283;
    if (ks == XKB_KEY_Page_Down) return 284;
    if (ks == XKB_KEY_Home)      return 285;
    if (ks == XKB_KEY_End)       return 286;
    if (ks == XKB_KEY_Insert)    return 287;
    if (ks == XKB_KEY_Delete)    return 288;
    if (ks == XKB_KEY_minus || ks == XKB_KEY_underscore)      return (i32)'-';
    if (ks == XKB_KEY_plus || ks == XKB_KEY_equal)            return (i32)'=';
    if (ks == XKB_KEY_parenleft || ks == XKB_KEY_braceleft)   return (i32)'(';
    if (ks == XKB_KEY_parenright || ks == XKB_KEY_braceright) return (i32)')';
    if (ks == XKB_KEY_bracketleft)  return (i32)'[';
    if (ks == XKB_KEY_bracketright) return (i32)']';
    if (ks == XKB_KEY_slash || ks == XKB_KEY_question)    return (i32)'/';
    if (ks == XKB_KEY_backslash || ks == XKB_KEY_bar)     return (i32)'\\';
    if (ks == XKB_KEY_grave || ks == XKB_KEY_asciitilde)  return (i32)'`';
    if (ks == XKB_KEY_semicolon || ks == XKB_KEY_colon)   return (i32)';';
    if (ks == XKB_KEY_apostrophe || ks == XKB_KEY_quotedbl) return (i32)'\'';
    if (ks == XKB_KEY_comma)  return (i32)',';
    if (ks == XKB_KEY_period) return (i32)'.';
    return -1;
}

/* ---- XDG WM Base (ping/pong) ---- */

static void xdg_wm_base_ping(void *data, struct xdg_wm_base *base, u32 serial) {
    (void)data;
    xdg_wm_base_pong(base, serial);
}

static const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping,
};

/* ---- XDG Surface ---- */

static void xdg_surface_handle_configure(void *data, struct xdg_surface *surface, u32 serial) {
    Platform *p = data;
    xdg_surface_ack_configure(surface, serial);
    p->configured = true;
}

static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};

/* ---- XDG Toplevel ---- */

static void xdg_toplevel_handle_configure(void *data, struct xdg_toplevel *tl,
                                          i32 w, i32 h, struct wl_array *states) {
    (void)tl;
    (void)states;
    Platform *p = data;
    if (w > 0 && h > 0) {
        p->width = (u32)w;
        p->height = (u32)h;
        if (p->egl_window)
            wl_egl_window_resize(p->egl_window, w, h, 0, 0);
    }
}

static void xdg_toplevel_handle_close(void *data, struct xdg_toplevel *tl) {
    (void)tl;
    Platform *p = data;
    p->should_close = true;
}

static const struct xdg_toplevel_listener xdg_toplevel_listener = {
    .configure = xdg_toplevel_handle_configure,
    .close = xdg_toplevel_handle_close,
};

/* ---- Keyboard listener ---- */

static void keyboard_keymap(void *data, struct wl_keyboard *kb, u32 format,
                            i32 fd, u32 size) {
    (void)kb;
    Platform *p = data;
    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        return;
    }
    char *map_str = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map_str == MAP_FAILED) {
        close(fd);
        return;
    }

    if (p->xkb_keymap) xkb_keymap_unref(p->xkb_keymap);
    if (p->xkb_state)  xkb_state_unref(p->xkb_state);

    p->xkb_keymap = xkb_keymap_new_from_string(p->xkb_ctx, map_str,
        XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS);
    if (p->xkb_keymap)
        p->xkb_state = xkb_state_new(p->xkb_keymap);

    munmap(map_str, size);
    close(fd);
}

static void keyboard_enter(void *data, struct wl_keyboard *kb, u32 serial,
                           struct wl_surface *surface, struct wl_array *keys) {
    (void)data; (void)kb; (void)serial; (void)surface; (void)keys;
}

static void keyboard_leave(void *data, struct wl_keyboard *kb, u32 serial,
                           struct wl_surface *surface) {
    (void)kb; (void)serial; (void)surface;
    /* R263: keyboard focus lost — release all keys so a key released while
     * unfocused (Wayland delivers no key event to an unfocused surface) can't
     * stay stuck down and keep driving movement after refocus. */
    Platform *p = data;
    if (p) input_release_all(&p->input);
}

static void keyboard_key(void *data, struct wl_keyboard *kb, u32 serial,
                         u32 time, u32 key, u32 state) {
    (void)kb; (void)serial; (void)time;
    Platform *p = data;
    if (!p->xkb_state) return;

    /* Wayland key codes are evdev codes; XKB expects evdev + 8 */
    u32 keycode = key + 8;
    xkb_keysym_t sym = xkb_state_key_get_one_sym(p->xkb_state, keycode);
    i32 engine_key = wayland_keysym_to_engine(sym);
    if (engine_key >= 0) {
        input_set_key(&p->input, engine_key, state == WL_KEYBOARD_KEY_STATE_PRESSED);
    }
}

static void keyboard_modifiers(void *data, struct wl_keyboard *kb, u32 serial,
                               u32 mods_depressed, u32 mods_latched,
                               u32 mods_locked, u32 group) {
    (void)kb; (void)serial;
    Platform *p = data;
    if (p->xkb_state)
        xkb_state_update_mask(p->xkb_state, mods_depressed, mods_latched,
                              mods_locked, 0, 0, group);
}

static void keyboard_repeat_info(void *data, struct wl_keyboard *kb,
                                 i32 rate, i32 delay) {
    (void)data; (void)kb; (void)rate; (void)delay;
}

static const struct wl_keyboard_listener keyboard_listener = {
    .keymap      = keyboard_keymap,
    .enter       = keyboard_enter,
    .leave       = keyboard_leave,
    .key         = keyboard_key,
    .modifiers   = keyboard_modifiers,
    .repeat_info = keyboard_repeat_info,
};

/* ---- Pointer listener ---- */

static void pointer_enter(void *data, struct wl_pointer *ptr, u32 serial,
                          struct wl_surface *surface, wl_fixed_t sx, wl_fixed_t sy) {
    (void)surface;
    Platform *p = data;
    p->pointer_x = wl_fixed_to_double(sx);
    p->pointer_y = wl_fixed_to_double(sy);
    p->pointer_enter_serial = serial;
    (void)ptr;
    /* Re-apply hidden cursor each time the pointer re-enters the surface. */
    wayland_update_cursor_visibility(p);
}

static void pointer_leave(void *data, struct wl_pointer *ptr, u32 serial,
                          struct wl_surface *surface) {
    (void)data; (void)ptr; (void)serial; (void)surface;
}

static void pointer_motion(void *data, struct wl_pointer *ptr, u32 time,
                           wl_fixed_t sx, wl_fixed_t sy) {
    (void)ptr; (void)time;
    Platform *p = data;
    f64 nx = wl_fixed_to_double(sx);
    f64 ny = wl_fixed_to_double(sy);

    /* R346: when zwp_relative_pointer is active (relative/capture), deltas
     * come from relative_pointer_motion. Also accumulating surface Δ here
     * double-counts — especially if pointer-constraints lock is missing and
     * the cursor still moves on the surface. */
    if (!p->rel_pointer) {
        p->input.mouse_dx += (f32)(nx - p->pointer_x);
        p->input.mouse_dy += (f32)(ny - p->pointer_y);
    }
    p->pointer_x = nx;
    p->pointer_y = ny;
    p->input.mouse_x = (f32)nx;
    p->input.mouse_y = (f32)ny;
}

static void pointer_button(void *data, struct wl_pointer *ptr, u32 serial,
                           u32 time, u32 button, u32 state) {
    (void)ptr; (void)serial; (void)time;
    Platform *p = data;
    i32 key = -1;
    if (button == BTN_LEFT)        key = INPUT_MOUSE_LEFT;
    else if (button == BTN_RIGHT)  key = INPUT_MOUSE_RIGHT;
    else if (button == BTN_MIDDLE) key = INPUT_MOUSE_MIDDLE;
    else if (button == BTN_SIDE)   key = INPUT_MOUSE_4;
    else if (button == BTN_EXTRA)  key = INPUT_MOUSE_5;
    if (key >= 0)
        input_set_key(&p->input, key, state == WL_POINTER_BUTTON_STATE_PRESSED);
}

static void pointer_axis(void *data, struct wl_pointer *ptr, u32 time,
                         u32 axis, wl_fixed_t value) {
    (void)ptr; (void)time;
    Platform *p = data;
    f32 v = (f32)wl_fixed_to_double(value);
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL)
        input_set_scroll(&p->input, 0.0f, -v / 10.0f);
    else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL)
        input_set_scroll(&p->input, v / 10.0f, 0.0f);
}

static void pointer_frame(void *data, struct wl_pointer *ptr) {
    (void)data; (void)ptr;
}

static void pointer_axis_source(void *data, struct wl_pointer *ptr, u32 source) {
    (void)data; (void)ptr; (void)source;
}

static void pointer_axis_stop(void *data, struct wl_pointer *ptr, u32 time, u32 axis) {
    (void)data; (void)ptr; (void)time; (void)axis;
}

static void pointer_axis_discrete(void *data, struct wl_pointer *ptr, u32 axis, i32 discrete) {
    (void)data; (void)ptr; (void)axis; (void)discrete;
}

static const struct wl_pointer_listener pointer_listener = {
    .enter         = pointer_enter,
    .leave         = pointer_leave,
    .motion        = pointer_motion,
    .button        = pointer_button,
    .axis          = pointer_axis,
    .frame         = pointer_frame,
    .axis_source   = pointer_axis_source,
    .axis_stop     = pointer_axis_stop,
    .axis_discrete = pointer_axis_discrete,
};

/* ---- Relative pointer listener (zwp_relative_pointer_v1) ---- */

static void relative_pointer_motion(void *data, struct zwp_relative_pointer_v1 *rp,
                                    u32 utime_hi, u32 utime_lo,
                                    wl_fixed_t dx, wl_fixed_t dy,
                                    wl_fixed_t dx_unaccel, wl_fixed_t dy_unaccel) {
    (void)rp; (void)utime_hi; (void)utime_lo; (void)dx; (void)dy;
    Platform *p = data;
    /* Prefer unaccelerated deltas for camera-style relative input. */
    p->input.mouse_dx += (f32)wl_fixed_to_double(dx_unaccel);
    p->input.mouse_dy += (f32)wl_fixed_to_double(dy_unaccel);
}

static const struct zwp_relative_pointer_v1_listener relative_pointer_listener = {
    .relative_motion = relative_pointer_motion,
};

/* ---- Seat listener ---- */

static void seat_capabilities(void *data, struct wl_seat *seat, u32 caps) {
    Platform *p = data;

    if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && !p->keyboard) {
        p->keyboard = wl_seat_get_keyboard(seat);
        wl_keyboard_add_listener(p->keyboard, &keyboard_listener, p);
    } else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && p->keyboard) {
        wl_keyboard_destroy(p->keyboard);
        p->keyboard = NULL;
    }

    if ((caps & WL_SEAT_CAPABILITY_POINTER) && !p->pointer) {
        p->pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(p->pointer, &pointer_listener, p);
    } else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && p->pointer) {
        wl_pointer_destroy(p->pointer);
        p->pointer = NULL;
    }
}

static void seat_name(void *data, struct wl_seat *seat, const char *name) {
    (void)data; (void)seat; (void)name;
}

static const struct wl_seat_listener seat_listener = {
    .capabilities = seat_capabilities,
    .name         = seat_name,
};

/* ---- wl_output listener ---- */

static void output_geometry(void *data, struct wl_output *output,
    i32 x, i32 y, i32 phys_w, i32 phys_h, i32 subpixel,
    const char *make, const char *model, i32 transform) {
    (void)output; (void)phys_w; (void)phys_h; (void)subpixel; (void)make; (void)transform;
    Platform *p = data;
    if (p->monitor_count < PLATFORM_MAX_MONITORS) {
        MonitorInfo *m = &p->monitors[p->monitor_count];
        m->x = x;
        m->y = y;
        strncpy(m->name, model ? model : "unknown", 63);
        m->name[63] = '\0';
    }
}

static void output_mode(void *data, struct wl_output *output,
    u32 flags, i32 w, i32 h, i32 refresh) {
    (void)output;
    Platform *p = data;
    if ((flags & WL_OUTPUT_MODE_CURRENT) && p->monitor_count < PLATFORM_MAX_MONITORS) {
        MonitorInfo *m = &p->monitors[p->monitor_count];
        m->width = (u32)w;
        m->height = (u32)h;
        m->refresh_rate = (u32)(refresh / 1000);  /* mHz -> Hz */
    }
}

static void output_scale(void *data, struct wl_output *output, i32 factor) {
    (void)output;
    Platform *p = data;
    p->scale = factor;
    if (p->monitor_count < PLATFORM_MAX_MONITORS) {
        p->monitors[p->monitor_count].scale = factor;
    }
}

static void output_done(void *data, struct wl_output *output) {
    (void)output;
    Platform *p = data;
    if (p->monitor_count < PLATFORM_MAX_MONITORS) {
        MonitorInfo *m = &p->monitors[p->monitor_count];
        m->dpi = 96.0f * (f32)m->scale;
        m->primary = (p->monitor_count == 0);
        p->monitor_count++;
    }
    p->dpi = 96.0f * (f32)p->scale;
}

static const struct wl_output_listener output_listener = {
    .geometry = output_geometry,
    .mode     = output_mode,
    .done     = output_done,
    .scale    = output_scale,
};

/* ---- Registry listener ---- */

static void registry_global(void *data, struct wl_registry *reg, u32 name,
                            const char *interface, u32 version) {
    (void)version;
    Platform *p = data;
    if (strcmp(interface, wl_compositor_interface.name) == 0)
        p->compositor = wl_registry_bind(reg, name, &wl_compositor_interface, 4);
    else if (strcmp(interface, xdg_wm_base_interface.name) == 0)
        p->xdg_wm_base = wl_registry_bind(reg, name, &xdg_wm_base_interface, 1);
    else if (strcmp(interface, wl_seat_interface.name) == 0)
        p->seat = wl_registry_bind(reg, name, &wl_seat_interface, 5);
    else if (strcmp(interface, wl_output_interface.name) == 0) {
        p->output = wl_registry_bind(reg, name, &wl_output_interface, 3);
        wl_output_add_listener(p->output, &output_listener, p);
    }
    else if (strcmp(interface, zwp_relative_pointer_manager_v1_interface.name) == 0)
        p->rel_pointer_mgr = wl_registry_bind(reg, name,
            &zwp_relative_pointer_manager_v1_interface, 1);
    else if (strcmp(interface, zwp_pointer_constraints_v1_interface.name) == 0)
        p->pointer_constraints = wl_registry_bind(reg, name,
            &zwp_pointer_constraints_v1_interface, 1);
}

static void registry_global_remove(void *data, struct wl_registry *reg, u32 name) {
    (void)data; (void)reg; (void)name;
}

static const struct wl_registry_listener registry_listener = {
    .global        = registry_global,
    .global_remove = registry_global_remove,
};

/* ---- Platform API ---- */

Platform *platform_create(const PlatformConfig *cfg) {
    Platform *p = calloc(1, sizeof(Platform));
    if (!p) { LOG_FATAL("Failed to allocate Platform"); return NULL; }

    p->width  = cfg->width;
    p->height = cfg->height;
    p->mouse_visible = true;
    p->scale = 1;

    /* Connect to Wayland display */
    p->display = wl_display_connect(NULL);
    if (!p->display) {
        LOG_FATAL("Failed to connect to Wayland display");
        free(p);
        return NULL;
    }

    /* Initialize XKB context */
    p->xkb_ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    if (!p->xkb_ctx) {
        LOG_ERROR("Failed to create XKB context");
    }

    /* Get registry and bind globals */
    p->registry = wl_display_get_registry(p->display);
    wl_registry_add_listener(p->registry, &registry_listener, p);
    wl_display_roundtrip(p->display);

    if (!p->compositor) {
        LOG_FATAL("Missing wl_compositor interface");
        wl_display_disconnect(p->display);
        free(p);
        return NULL;
    }
    if (!p->xdg_wm_base) {
        LOG_FATAL("Missing xdg_wm_base interface");
        wl_display_disconnect(p->display);
        free(p);
        return NULL;
    }

    xdg_wm_base_add_listener(p->xdg_wm_base, &xdg_wm_base_listener, p);

    /* Create surface */
    p->surface = wl_compositor_create_surface(p->compositor);
    if (!p->surface) {
        LOG_FATAL("Failed to create wl_surface");
        wl_display_disconnect(p->display);
        free(p);
        return NULL;
    }

    /* Create xdg_surface + toplevel */
    p->xdg_surface = xdg_wm_base_get_xdg_surface(p->xdg_wm_base, p->surface);
    xdg_surface_add_listener(p->xdg_surface, &xdg_surface_listener, p);

    p->toplevel = xdg_surface_get_toplevel(p->xdg_surface);
    xdg_toplevel_add_listener(p->toplevel, &xdg_toplevel_listener, p);
    xdg_toplevel_set_title(p->toplevel, cfg->title);
    xdg_toplevel_set_app_id(p->toplevel, "break-engine");

    /* Create EGL window (used by RHI for EGL/Vulkan surface) */
    p->egl_window = wl_egl_window_create(p->surface, (i32)cfg->width, (i32)cfg->height);

    /* Commit surface and wait for initial configure */
    wl_surface_commit(p->surface);
    wl_display_roundtrip(p->display);

    /* Bind seat (keyboard + pointer) */
    if (p->seat) {
        wl_seat_add_listener(p->seat, &seat_listener, p);
        wl_display_roundtrip(p->display);
    }

    input_init(&p->input);
    gamepad_init();

    LOG_INFO("Platform initialized (Wayland): %ux%u \"%s\"", cfg->width, cfg->height, cfg->title);
    return p;
}

void platform_destroy(Platform *p) {
    if (!p) return;

    gamepad_shutdown();

    wayland_clear_relative(p);
    if (p->rel_pointer_mgr)     zwp_relative_pointer_manager_v1_destroy(p->rel_pointer_mgr);
    if (p->pointer_constraints) zwp_pointer_constraints_v1_destroy(p->pointer_constraints);

    if (p->egl_window)   wl_egl_window_destroy(p->egl_window);
    if (p->keyboard)     wl_keyboard_destroy(p->keyboard);
    if (p->pointer)      wl_pointer_destroy(p->pointer);
    if (p->toplevel)     xdg_toplevel_destroy(p->toplevel);
    if (p->xdg_surface)  xdg_surface_destroy(p->xdg_surface);
    if (p->surface)      wl_surface_destroy(p->surface);
    if (p->xdg_wm_base)  xdg_wm_base_destroy(p->xdg_wm_base);
    if (p->seat)         wl_seat_destroy(p->seat);
    if (p->output)       wl_output_destroy(p->output);
    if (p->compositor)   wl_compositor_destroy(p->compositor);
    if (p->registry)     wl_registry_destroy(p->registry);
    if (p->xkb_state)   xkb_state_unref(p->xkb_state);
    if (p->xkb_keymap)  xkb_keymap_unref(p->xkb_keymap);
    if (p->xkb_ctx)     xkb_context_unref(p->xkb_ctx);
    if (p->display)     wl_display_disconnect(p->display);

    free(p);
    LOG_INFO("Platform destroyed (Wayland)");
}

PlatformEventResult platform_poll(Platform *p) {
    input_new_frame(&p->input);

    if (wl_display_dispatch_pending(p->display) < 0) {
        LOG_ERROR("Wayland display error");
        p->should_close = true;
        return PLATFORM_EVENT_QUIT;
    }

    /* Flush and read events (non-blocking via roundtrip) */
    wl_display_flush(p->display);
    if (wl_display_roundtrip(p->display) < 0) {
        LOG_ERROR("Wayland roundtrip failed");
        p->should_close = true;
        return PLATFORM_EVENT_QUIT;
    }

    /* Pump gamepads (evdev) into the shared input state. */
    gamepad_poll(p->input.gamepads);

    if (p->should_close) return PLATFORM_EVENT_QUIT;
    return PLATFORM_EVENT_NONE;
}

InputState *platform_input(Platform *p) {
    return &p->input;
}

void *platform_window_native(Platform *p) {
    return (void *)p->egl_window;
}

void *platform_display_native(Platform *p) {
    return (void *)p->display;
}

void *platform_surface_native(Platform *p) {
    return (void *)p->surface;
}

void platform_get_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p->width;
    if (h) *h = p->height;
}

f32 platform_get_dpi(Platform *p) {
    return p->dpi;
}

i32 platform_get_scale_factor(Platform *p) {
    return p->scale;
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
    if (p->is_fullscreen) {
        xdg_toplevel_unset_fullscreen(p->toplevel);
    } else {
        xdg_toplevel_set_fullscreen(p->toplevel, NULL);
    }
    p->is_fullscreen = !p->is_fullscreen;
    wl_surface_commit(p->surface);
}

/* Hide the cursor by attaching a NULL cursor surface; restore by leaving the
 * default. Requires the latest pointer-enter serial. */
static void wayland_update_cursor_visibility(Platform *p) {
    if (!p->pointer) return;
    if (!p->mouse_visible) {
        wl_pointer_set_cursor(p->pointer, p->pointer_enter_serial, NULL, 0, 0);
    }
    /* When visible again we let the compositor restore its default cursor on
     * the next enter; nothing to do here for the simple case. */
}

/* Lock + relative motion: confines the pointer in place and feeds unaccelerated
 * deltas via the relative-pointer protocol — the correct Wayland analog of an
 * X11 warp-based capture. */
static void wayland_apply_relative(Platform *p) {
    if (!p->pointer) return;

    if (p->rel_pointer_mgr && !p->rel_pointer) {
        p->rel_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(
            p->rel_pointer_mgr, p->pointer);
        if (p->rel_pointer)
            zwp_relative_pointer_v1_add_listener(p->rel_pointer,
                &relative_pointer_listener, p);
    }
    if (p->pointer_constraints && p->surface && !p->locked_pointer) {
        p->locked_pointer = zwp_pointer_constraints_v1_lock_pointer(
            p->pointer_constraints, p->surface, p->pointer, NULL,
            ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
    }
    if (!p->rel_pointer_mgr || !p->pointer_constraints) {
        LOG_WARN("Wayland: compositor lacks relative-pointer/pointer-constraints; "
                 "relative mouse degraded");
    }
}

static void wayland_clear_relative(Platform *p) {
    if (p->locked_pointer) {
        zwp_locked_pointer_v1_destroy(p->locked_pointer);
        p->locked_pointer = NULL;
    }
    if (p->rel_pointer) {
        zwp_relative_pointer_v1_destroy(p->rel_pointer);
        p->rel_pointer = NULL;
    }
}

void platform_mouse_capture(Platform *p, bool capture) {
    /* On Wayland "capture" maps to a persistent pointer lock. */
    p->mouse_captured = capture;
    if (capture) wayland_apply_relative(p);
    else if (!p->mouse_relative) wayland_clear_relative(p);
}

void platform_mouse_set_visible(Platform *p, bool visible) {
    p->mouse_visible = visible;
    wayland_update_cursor_visibility(p);
}

void platform_mouse_set_relative(Platform *p, bool relative) {
    p->mouse_relative = relative;
    if (relative) {
        wayland_apply_relative(p);
        p->mouse_visible = false;
        wayland_update_cursor_visibility(p);
    } else {
        if (!p->mouse_captured) wayland_clear_relative(p);
        p->mouse_visible = true;
        wayland_update_cursor_visibility(p);
    }
}

#endif /* ENGINE_PLATFORM_WAYLAND */
