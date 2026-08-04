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
#include <poll.h> /* R419: non-blocking socket check in platform_poll */
#include <sys/mman.h>
#include <linux/input-event-codes.h>

#include "xdg-shell-client-protocol.h"
#include "relative-pointer-unstable-v1-client-protocol.h"
#include "pointer-constraints-unstable-v1-client-protocol.h"
#include "xdg-output-unstable-v1-client-protocol.h" /* R443 */
#include "wayland_output.h"                         /* R443: pure output-list logic */

/* ---- Platform state ---- */

/* R443: per-output listener context — wl_output events for different outputs
 * may interleave on the wire, so handlers must not share a "current" slot. */
typedef struct {
    struct Platform *p;
    u32              slot; /* index into p->output_list.items / p->outputs */
} WaylandOutputCtx;

struct Platform {
    struct wl_display    *display;
    struct wl_registry   *registry;
    struct wl_compositor *compositor;
    struct wl_surface    *surface;
    struct wl_seat       *seat;
    struct wl_keyboard   *keyboard;
    struct wl_pointer    *pointer;
    struct xdg_wm_base   *xdg_wm_base;
    struct xdg_surface   *xdg_surface;
    struct xdg_toplevel  *toplevel;

    /* R443: multi-output enumeration — one slot per bound wl_output global
     * (was a single struct wl_output *, which leaked every binding past the
     * first and mixed all outputs' events into monitors[monitor_count]). */
    struct wl_output               *outputs[WAYLAND_OUTPUT_MAX];
    struct zxdg_output_manager_v1  *xdg_output_mgr;   /* optional */
    struct zxdg_output_v1          *xdg_outputs[WAYLAND_OUTPUT_MAX];
    WaylandOutputList               output_list;
    WaylandOutputCtx                output_ctx[WAYLAND_OUTPUT_MAX];

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

    /* DPI / Monitor — R443: per-output data lives in output_list (converted
     * to MonitorInfo on query); dpi/scale mirror the primary (slot 0) output. */
    f32 dpi;
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
    if (ks == XKB_KEY_Return || ks == XKB_KEY_KP_Enter) return 257; /* R371: keypad Enter = Select */
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
    /* R360: disambiguate End/Insert dual-binds in main (reset/DOF). */
    if (ks == XKB_KEY_Pause)       return 291;
    if (ks == XKB_KEY_Scroll_Lock) return 292;
    if (ks == XKB_KEY_Num_Lock)    return 293;
    if (ks == XKB_KEY_Caps_Lock)   return 294;
    if (ks == XKB_KEY_Menu)        return 295; /* R361: SSGI (was '[') */
    if (ks == XKB_KEY_KP_Multiply) return 296; /* R361: SSS */
    if (ks == XKB_KEY_KP_Divide)   return 297; /* R361: lens flare */
    if (ks == XKB_KEY_KP_Subtract) return 298; /* R361: sharpen */
    if (ks == XKB_KEY_KP_Add)      return 299; /* R361: contact shadow */
    /* R363: boom was 300 (=INPUT_MOUSE_LEFT); KP_* live at 305+ */
    if (ks == XKB_KEY_KP_0 || ks == XKB_KEY_KP_Insert) return 305; /* particle boom */
    if (ks == XKB_KEY_KP_1 || ks == XKB_KEY_KP_End)    return 306; /* tornado */
    if (ks == XKB_KEY_KP_2 || ks == XKB_KEY_KP_Down)   return 307; /* particle trail */
    if (ks == XKB_KEY_KP_3 || ks == XKB_KEY_KP_Next)   return 308; /* layout */
    if (ks == XKB_KEY_KP_4 || ks == XKB_KEY_KP_Left)   return 309; /* AA cycle */
    /* R364: CG/lens off digit row (FPS is Shift+`) */
    if (ks == XKB_KEY_KP_5 || ks == XKB_KEY_KP_Begin)  return 310; /* temp- */
    if (ks == XKB_KEY_KP_6 || ks == XKB_KEY_KP_Right)  return 311; /* temp+ */
    if (ks == XKB_KEY_KP_7 || ks == XKB_KEY_KP_Home)   return 312; /* tint- */
    if (ks == XKB_KEY_KP_8 || ks == XKB_KEY_KP_Up)     return 313; /* tint+ */
    if (ks == XKB_KEY_KP_9 || ks == XKB_KEY_KP_Prior)  return 314; /* color grade */
    if (ks == XKB_KEY_KP_Decimal || ks == XKB_KEY_KP_Delete) return 315; /* lensfx / CA / vig cycle */
    if (ks == XKB_KEY_Shift_L || ks == XKB_KEY_Shift_R) return 289;
    if (ks == XKB_KEY_Control_L || ks == XKB_KEY_Control_R) return 290; /* R366: anim crossfade */
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
    (void)ptr; (void)serial; (void)surface;
    /* R354: compositor may omit ButtonRelease when the pointer leaves the
     * surface; release mouse keys so drag/click cannot stick (keyboard_leave
     * already calls input_release_all for focus loss). */
    Platform *p = data;
    if (!p) return;
    input_set_key(&p->input, INPUT_MOUSE_LEFT, false);
    input_set_key(&p->input, INPUT_MOUSE_MIDDLE, false);
    input_set_key(&p->input, INPUT_MOUSE_RIGHT, false);
    input_set_key(&p->input, INPUT_MOUSE_4, false);
    input_set_key(&p->input, INPUT_MOUSE_5, false);
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
        /* R432: seed on the first sample — pointer_x/pointer_y start zeroed,
         * so the first motion event otherwise emitted a delta spike up to the
         * window size (same fix as input_set_mouse's has_mouse_pos). */
        if (p->input.has_mouse_pos) {
            p->input.mouse_dx += (f32)(nx - p->pointer_x);
            p->input.mouse_dy += (f32)(ny - p->pointer_y);
        } else {
            p->input.has_mouse_pos = true;
        }
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

/* ---- wl_output listener (R443: per-output via WaylandOutputCtx) ---- */

static void output_geometry(void *data, struct wl_output *output,
    i32 x, i32 y, i32 phys_w, i32 phys_h, i32 subpixel,
    const char *make, const char *model, i32 transform) {
    (void)output; (void)phys_w; (void)phys_h; (void)subpixel; (void)make; (void)transform;
    WaylandOutputCtx *ctx = data;
    WaylandOutputInfo *o = &ctx->p->output_list.items[ctx->slot];
    o->x = x;
    o->y = y;
    if (o->name[0] == '\0') {
        strncpy(o->name, model ? model : "unknown", 63);
        o->name[63] = '\0';
    }
}

static void output_mode(void *data, struct wl_output *output,
    u32 flags, i32 w, i32 h, i32 refresh) {
    (void)output;
    WaylandOutputCtx *ctx = data;
    wl_out_accumulate_mode(&ctx->p->output_list.items[ctx->slot],
        (flags & WL_OUTPUT_MODE_CURRENT) != 0, w, h, refresh);
}

static void output_scale(void *data, struct wl_output *output, i32 factor) {
    (void)output;
    WaylandOutputCtx *ctx = data;
    ctx->p->output_list.items[ctx->slot].scale = factor;
}

static void output_done(void *data, struct wl_output *output) {
    (void)output;
    WaylandOutputCtx *ctx = data;
    Platform *p = ctx->p;
    WaylandOutputInfo *o = &p->output_list.items[ctx->slot];
    o->done = true;
    /* Slot 0 is the primary output; keep the global dpi/scale mirroring it
     * (single-output behavior unchanged from the pre-R443 implementation). */
    if (ctx->slot == 0) {
        p->scale = o->scale;
        p->dpi = 96.0f * (f32)o->scale;
    }
}

static const struct wl_output_listener output_listener = {
    .geometry = output_geometry,
    .mode     = output_mode,
    .done     = output_done,
    .scale    = output_scale,
};

/* ---- zxdg_output_v1 listener (R443: logical position + readable name) ---- */

static void xdg_output_logical_position(void *data, struct zxdg_output_v1 *xo,
                                        i32 x, i32 y) {
    (void)xo;
    WaylandOutputCtx *ctx = data;
    WaylandOutputInfo *o = &ctx->p->output_list.items[ctx->slot];
    /* More authoritative than wl_output.geometry (often 0,0 on wlroots). */
    o->x = x;
    o->y = y;
}

static void xdg_output_logical_size(void *data, struct zxdg_output_v1 *xo,
                                    i32 w, i32 h) {
    (void)data; (void)xo; (void)w; (void)h;
    /* MonitorInfo.width/height stay pixel-resolution (X11 parity); the
     * logical size is scale-derived and not part of the public shape. */
}

static void xdg_output_done(void *data, struct zxdg_output_v1 *xo) {
    (void)data; (void)xo;
}

static void xdg_output_name(void *data, struct zxdg_output_v1 *xo,
                            const char *name) {
    (void)xo;
    WaylandOutputCtx *ctx = data;
    WaylandOutputInfo *o = &ctx->p->output_list.items[ctx->slot];
    strncpy(o->name, name ? name : "unknown", 63);
    o->name[63] = '\0';
}

static void xdg_output_description(void *data, struct zxdg_output_v1 *xo,
                                   const char *description) {
    (void)data; (void)xo; (void)description;
}

static const struct zxdg_output_v1_listener xdg_output_listener = {
    .logical_position = xdg_output_logical_position,
    .logical_size     = xdg_output_logical_size,
    .done             = xdg_output_done,
    .name             = xdg_output_name,
    .description      = xdg_output_description,
};

/* R443: bind zxdg_output_v1 for a slot when the manager is available. Called
 * from both registry branches because global advertisement order between
 * wl_output and zxdg_output_manager_v1 is not guaranteed. */
static void wayland_bind_xdg_output(Platform *p, u32 slot) {
    if (!p->xdg_output_mgr || !p->outputs[slot] || p->xdg_outputs[slot]) return;
    p->xdg_outputs[slot] = zxdg_output_manager_v1_get_xdg_output(
        p->xdg_output_mgr, p->outputs[slot]);
    if (p->xdg_outputs[slot])
        zxdg_output_v1_add_listener(p->xdg_outputs[slot],
            &xdg_output_listener, &p->output_ctx[slot]);
}

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
        /* R443: bind every advertised output (was: single p->output). */
        i32 slot = wl_out_add(&p->output_list, name);
        if (slot >= 0 && !p->outputs[slot]) {
            p->output_ctx[slot] = (WaylandOutputCtx){ p, (u32)slot };
            /* v3: geometry/mode/done/scale (name/description need v4, which
             * xdg-output covers instead). */
            p->outputs[slot] = wl_registry_bind(reg, name, &wl_output_interface, 3);
            wl_output_add_listener(p->outputs[slot], &output_listener,
                &p->output_ctx[slot]);
            wayland_bind_xdg_output(p, (u32)slot);
        }
    }
    else if (strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        /* R443: optional — logical position/names; degrade to wl_output-only
         * data when the compositor lacks it. */
        p->xdg_output_mgr = wl_registry_bind(reg, name,
            &zxdg_output_manager_v1_interface, 3);
        for (u32 i = 0; i < p->output_list.count; i++)
            wayland_bind_xdg_output(p, i);
    }
    else if (strcmp(interface, zwp_relative_pointer_manager_v1_interface.name) == 0)
        p->rel_pointer_mgr = wl_registry_bind(reg, name,
            &zwp_relative_pointer_manager_v1_interface, 1);
    else if (strcmp(interface, zwp_pointer_constraints_v1_interface.name) == 0)
        p->pointer_constraints = wl_registry_bind(reg, name,
            &zwp_pointer_constraints_v1_interface, 1);
}

static void registry_global_remove(void *data, struct wl_registry *reg, u32 name) {
    (void)reg;
    Platform *p = data;
    /* R444: output hot-unplug. Tombstones would exhaust the fixed 8-slot
     * budget under repeated plug/unplug and fight wl_out_add's append-dedup
     * semantics, so removal compacts all parallel arrays instead. */
    i32 slot = wl_out_find(&p->output_list, name);
    if (slot < 0) return; /* not an output we bound (seat, compositor...) */
    u32 i = (u32)slot;
    /* zxdg_output_v1 wraps the wl_output, so it must go first. */
    if (p->xdg_outputs[i]) zxdg_output_v1_destroy(p->xdg_outputs[i]);
    if (p->outputs[i])     wl_output_destroy(p->outputs[i]);
    wl_out_remove(&p->output_list, name);
    /* Shift the pointer arrays down over the removed slot. output_ctx is NOT
     * moved: listeners hold the addresses of its members, so the structs must
     * stay put — only their .slot numbers shift with the compaction. */
    u32 tail = p->output_list.count - i;
    if (tail > 0) {
        memmove(&p->outputs[i], &p->outputs[i + 1], tail * sizeof(p->outputs[0]));
        memmove(&p->xdg_outputs[i], &p->xdg_outputs[i + 1], tail * sizeof(p->xdg_outputs[0]));
    }
    p->outputs[p->output_list.count] = NULL;
    p->xdg_outputs[p->output_list.count] = NULL;
    for (u32 k = i; k < p->output_list.count; k++)
        p->output_ctx[k].slot = k;
    /* If slot 0 was unplugged, p->scale/p->dpi keep the old primary's values
     * until the new slot-0 output delivers its next done event — an accepted
     * brief staleness (the values remain plausible for the same session). */
}

static const struct wl_registry_listener registry_listener = {
    .global        = registry_global,
    .global_remove = registry_global_remove,
};

/* ---- Platform API ---- */

/* R427: bail-out cleanup for platform_create — destroys whatever was created
 * so far (every member NULL-checked), mirroring platform_destroy. The old
 * failure paths only disconnected the display, leaking the registry and the
 * xkb context (and any bound globals). */
static void wayland_create_fail(Platform *p) {
    if (p->toplevel)     xdg_toplevel_destroy(p->toplevel);
    if (p->xdg_surface)  xdg_surface_destroy(p->xdg_surface);
    if (p->surface)      wl_surface_destroy(p->surface);
    if (p->xdg_wm_base)  xdg_wm_base_destroy(p->xdg_wm_base);
    if (p->seat)         wl_seat_destroy(p->seat);
    /* R443: multi-output */
    for (u32 i = 0; i < WAYLAND_OUTPUT_MAX; i++) {
        if (p->xdg_outputs[i]) zxdg_output_v1_destroy(p->xdg_outputs[i]);
        if (p->outputs[i])     wl_output_destroy(p->outputs[i]);
    }
    if (p->xdg_output_mgr) zxdg_output_manager_v1_destroy(p->xdg_output_mgr);
    if (p->compositor)   wl_compositor_destroy(p->compositor);
    if (p->registry)     wl_registry_destroy(p->registry);
    if (p->xkb_ctx)      xkb_context_unref(p->xkb_ctx);
    if (p->display)      wl_display_disconnect(p->display);
    free(p);
}

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
        wayland_create_fail(p);
        return NULL;
    }
    if (!p->xdg_wm_base) {
        LOG_FATAL("Missing xdg_wm_base interface");
        wayland_create_fail(p);
        return NULL;
    }

    xdg_wm_base_add_listener(p->xdg_wm_base, &xdg_wm_base_listener, p);

    /* Create surface. R443: the window is still created on whichever output
     * the compositor picks — per-output window placement is out of scope for
     * this round (enumeration/query only). */
    p->surface = wl_compositor_create_surface(p->compositor);
    if (!p->surface) {
        LOG_FATAL("Failed to create wl_surface");
        wayland_create_fail(p);
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
    /* R427: NULL-check — a failed egl window would crash the RHI init later. */
    if (!p->egl_window) {
        LOG_FATAL("Failed to create wl_egl_window");
        wayland_create_fail(p);
        return NULL;
    }

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

    /* R443: extra roundtrip so wl_output/xdg-output initial events (bound
     * during the first roundtrip's dispatch) have arrived before queries. */
    wl_display_roundtrip(p->display);

    LOG_INFO("Platform initialized (Wayland): %ux%u \"%s\" (DPI=%.1f scale=%d monitors=%u)",
             cfg->width, cfg->height, cfg->title, p->dpi, p->scale,
             platform_get_monitor_count(p));
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
    /* R443: multi-output */
    for (u32 i = 0; i < WAYLAND_OUTPUT_MAX; i++) {
        if (p->xdg_outputs[i]) zxdg_output_v1_destroy(p->xdg_outputs[i]);
        if (p->outputs[i])     wl_output_destroy(p->outputs[i]);
    }
    if (p->xdg_output_mgr) zxdg_output_manager_v1_destroy(p->xdg_output_mgr);
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

    /* R419 (PERF): wl_display_roundtrip() blocked on a full compositor
     * round-trip every frame. Use the prepare_read pattern with a zero-timeout
     * poll instead: flush outgoing requests, read whatever is already buffered
     * on the socket (non-blocking), then dispatch — all pending events are
     * still processed each call, but we never wait on the compositor. */
    while (wl_display_prepare_read(p->display) != 0) {
        if (wl_display_dispatch_pending(p->display) < 0) {
            LOG_ERROR("Wayland display error");
            p->should_close = true;
            return PLATFORM_EVENT_QUIT;
        }
    }
    wl_display_flush(p->display);
    struct pollfd pfd = { wl_display_get_fd(p->display), POLLIN, 0 };
    if (poll(&pfd, 1, 0) > 0 && (pfd.revents & POLLIN)) {
        if (wl_display_read_events(p->display) < 0) {
            LOG_ERROR("Wayland read failed");
            p->should_close = true;
            return PLATFORM_EVENT_QUIT;
        }
    } else {
        wl_display_cancel_read(p->display);
    }
    if (wl_display_dispatch_pending(p->display) < 0) {
        LOG_ERROR("Wayland dispatch failed");
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
    /* R443: count outputs whose initial event burst completed (done). */
    u32 n = 0;
    for (u32 i = 0; i < p->output_list.count; i++)
        if (p->output_list.items[i].done) n++;
    return n;
}

bool platform_get_monitor_info(Platform *p, u32 index, MonitorInfo *out) {
    if (!out) return false;
    /* R443: map the public packed index onto the nth completed output slot. */
    for (u32 i = 0; i < p->output_list.count; i++) {
        const WaylandOutputInfo *o = &p->output_list.items[i];
        if (!o->done) continue;
        if (index-- > 0) continue;
        memset(out, 0, sizeof(*out));
        memcpy(out->name, o->name, sizeof(out->name));
        out->x = o->x;
        out->y = o->y;
        out->width = o->width;
        out->height = o->height;
        out->refresh_rate = o->refresh_rate;
        out->scale = o->scale;
        out->dpi = 96.0f * (f32)o->scale;
        out->primary = (i == 0);
        return true;
    }
    return false;
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
