/*
 * window_screen.c — QNX Screen window layer (ENGINE_QNX_SCREEN).
 *
 * The platform creates its own native window through the QNX Screen API
 * (screen_context/screen_window), polls close/pointer/keyboard events, and
 * exposes the window/context handles to the Vulkan Screen WSI. The default
 * RHI is headless; native-window and GPU runtime evidence is tracked
 * separately in docs/qnx_compat.md.
 *
 * Not yet mapped (follow-up with the graphics milestone): text/IME,
 * clipboard, relative mouse mode. Those surface fail-closed exactly like
 * window_mobile.c.
 */

#if defined(ENGINE_PLATFORM_QNX) && defined(ENGINE_QNX_SCREEN)

#include <platform/platform.h>
#include <platform/screen_keymap.h>
#include <screen/screen.h>
#include <sys/keycodes.h>
#include <stdlib.h>
#include <string.h>
#include <platform/window_mode.h>

/* The keymap mirrors <sys/keycodes.h> as raw integers so it stays
 * host-testable (test_screen_keymap.c); pin the mirror to the real header
 * at compile time on QNX cross builds. */
_Static_assert(KEYCODE_PC_KEYS == SCREEN_KEYMAP_PC_KEYS,
               "screen_keymap PC_KEYS base drifted from sys/keycodes.h");
_Static_assert(KEYCODE_ESCAPE == SCREEN_KEYMAP_PC(0x1B), "ESCAPE drifted");
_Static_assert(KEYCODE_RETURN == SCREEN_KEYMAP_PC(0x0D), "RETURN drifted");
_Static_assert(KEYCODE_LEFT == SCREEN_KEYMAP_PC(0x51), "LEFT drifted");
_Static_assert(KEYCODE_UP == SCREEN_KEYMAP_PC(0x52), "UP drifted");
_Static_assert(KEYCODE_RIGHT == SCREEN_KEYMAP_PC(0x53), "RIGHT drifted");
_Static_assert(KEYCODE_DOWN == SCREEN_KEYMAP_PC(0x54), "DOWN drifted");
_Static_assert(KEYCODE_F1 == SCREEN_KEYMAP_PC(0xBE), "F1 drifted");
_Static_assert(KEYCODE_F12 == SCREEN_KEYMAP_PC(0xC9), "F12 drifted");
_Static_assert(KEYCODE_PG_UP == SCREEN_KEYMAP_PC(0x55), "PG_UP drifted");
_Static_assert(KEYCODE_HOME == SCREEN_KEYMAP_PC(0x50), "HOME drifted");
_Static_assert(KEYCODE_INSERT == SCREEN_KEYMAP_PC(0x63), "INSERT drifted");
_Static_assert(KEYCODE_DELETE == SCREEN_KEYMAP_PC(0xFF), "DELETE drifted");
_Static_assert(KEYCODE_LEFT_SHIFT == SCREEN_KEYMAP_PC(0xE1), "LSHIFT drifted");
_Static_assert(KEYCODE_LEFT_CTRL == SCREEN_KEYMAP_PC(0xE3), "LCTRL drifted");

struct Platform {
    screen_context_t ctx;
    screen_window_t  win;
    screen_event_t   ev;
    InputState       input;
    u32              width, height;
    bool             quit;
    u64              media_generation;
    PlatformMediaContext media;
    PlatformWsiSurface   wsi;
    PlatformWindowModeState window_mode;
};

static void screen_destroy_handles(Platform *p)
{
    if (p->ev)  (void)screen_destroy_event(p->ev);
    if (p->win) (void)screen_destroy_window(p->win);
    if (p->ctx) (void)screen_destroy_context(p->ctx);
    p->ev = NULL;
    p->win = NULL;
    p->ctx = NULL;
}

Platform *platform_create(const PlatformConfig *cfg)
{
    if (!platform_config_valid(cfg)) return NULL;
    Platform *p = (Platform *)calloc(1, sizeof(*p));
    if (!p) return NULL;
    if (screen_create_context(&p->ctx, SCREEN_APPLICATION_CONTEXT) != 0) {
        free(p);
        return NULL;
    }
    if (screen_create_window(&p->win, p->ctx) != 0 ||
        screen_create_event(&p->ev) != 0) {
        screen_destroy_handles(p);
        free(p);
        return NULL;
    }

    int size[2] = { (int)cfg->width, (int)cfg->height };
    int format = SCREEN_FORMAT_RGBA8888;
    int usage = SCREEN_USAGE_READ | SCREEN_USAGE_WRITE;
#if defined(ENGINE_VULKAN)
    usage |= SCREEN_USAGE_VULKAN;
#endif
    if (screen_set_window_property_iv(p->win, SCREEN_PROPERTY_SIZE, size) != 0 ||
        screen_set_window_property_iv(p->win, SCREEN_PROPERTY_FORMAT, &format) != 0 ||
        screen_set_window_property_iv(p->win, SCREEN_PROPERTY_USAGE, &usage) != 0 ||
        screen_flush_context(p->ctx, 0) != 0) {
        screen_destroy_handles(p);
        free(p);
        return NULL;
    }

    p->width = cfg->width;
    p->height = cfg->height;
    (void)platform_wsi_surface_init(&p->wsi, true, cfg->width, cfg->height,
                                    cfg->width, cfg->height);
    platform_window_mode_init_fixed(&p->window_mode,
                                    PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    p->media_generation = 1u;
    p->media.screen = true;
    p->media.capabilities = PLATFORM_MEDIA_CAP_POINTER_FINE |
                            PLATFORM_MEDIA_CAP_COLOR_SRGB;
    p->media.known = PLATFORM_MEDIA_KNOWN_POINTER |
                     PLATFORM_MEDIA_KNOWN_COLOR_GAMUT;
    input_init(&p->input);
    return p;
}

void platform_destroy(Platform *p)
{
    if (!p) return;
    (void)platform_wsi_surface_destroy(&p->wsi);
    screen_destroy_handles(p);
    free(p);
}

bool platform_wsi_surface_query(Platform *p, PlatformWsiSurface *out)
{
    if (p == NULL || out == NULL) return false;
    *out = p->wsi;
    return true;
}

PlatformWsiSurface *platform_wsi_surface(Platform *p)
{
    return p != NULL ? &p->wsi : NULL;
}

bool platform_mobile_resize(Platform *p, u32 logical_width, u32 logical_height,
                            u32 drawable_width, u32 drawable_height, f32 scale) {
    (void)p; (void)logical_width; (void)logical_height;
    (void)drawable_width; (void)drawable_height; (void)scale;
    return false;
}
void platform_mobile_notify_suspend(Platform *p)   { (void)p; }
void platform_mobile_notify_resume(Platform *p)    { (void)p; }
void platform_mobile_notify_surface_lost(Platform *p) { (void)p; }
void platform_mobile_notify_surface_recreated(Platform *p, void *w,
                                              u32 width, u32 height)
{
    (void)p; (void)w; (void)width; (void)height;
}

static void screen_apply_pointer(Platform *p)
{
    int pos[2] = { 0, 0 };
    int buttons[1] = { 0 };
    if (screen_get_event_property_iv(p->ev, SCREEN_PROPERTY_POSITION, pos) == 0) {
        input_set_mouse(&p->input, (f32)pos[0], (f32)pos[1]);
    }
    if (screen_get_event_property_iv(p->ev, SCREEN_PROPERTY_BUTTONS,
                                     buttons) == 0) {
        input_set_key(&p->input, INPUT_MOUSE_LEFT,
                      (buttons[0] & SCREEN_LEFT_MOUSE_BUTTON) != 0);
        input_set_key(&p->input, INPUT_MOUSE_MIDDLE,
                      (buttons[0] & SCREEN_MIDDLE_MOUSE_BUTTON) != 0);
        input_set_key(&p->input, INPUT_MOUSE_RIGHT,
                      (buttons[0] & SCREEN_RIGHT_MOUSE_BUTTON) != 0);
    }
    /* Vertical wheel: upward ticks are positive (x11 parity: up = +1 dy). */
    int wheel[1] = { 0 };
    if (screen_get_event_property_iv(p->ev, SCREEN_PROPERTY_MOUSE_WHEEL,
                                     wheel) == 0 && wheel[0] != 0) {
        input_set_scroll(&p->input, 0.0f, (f32)wheel[0]);
    }
}

static void screen_apply_keyboard(Platform *p)
{
    int sym[1] = { 0 };
    int flags[1] = { 0 };
    if (screen_get_event_property_iv(p->ev, SCREEN_PROPERTY_SYM, sym) != 0)
        return;
    if (screen_get_event_property_iv(p->ev, SCREEN_PROPERTY_FLAGS, flags) != 0)
        return;
    if ((flags[0] & KEY_SYM_VALID) == 0) return;
    i32 engine_key = screen_keymap_sym_to_engine((u32)sym[0]);
    if (engine_key < 0) return;
    /* KEY_REPEAT keeps the key held; KEY_DOWN alone decides press/release. */
    input_set_key(&p->input, engine_key, (flags[0] & KEY_DOWN) != 0);
}

static bool screen_event_from_window(Platform *p)
{
    screen_window_t source = NULL;
    return screen_get_event_property_pv(p->ev, SCREEN_PROPERTY_WINDOW,
                                        (void **)&source) == 0 &&
           source == p->win;
}

PlatformEventResult platform_poll(Platform *p)
{
    if (!p) return PLATFORM_EVENT_QUIT;
    input_new_frame(&p->input);
    for (;;) {
        if (screen_get_event(p->ctx, p->ev, 0ULL) != 0) break;
        int type = SCREEN_EVENT_NONE;
        if (screen_get_event_property_iv(p->ev, SCREEN_PROPERTY_TYPE, &type) != 0)
            break;
        if (type == SCREEN_EVENT_NONE) break;
        switch (type) {
        case SCREEN_EVENT_CLOSE:
            p->quit = true;
            break;
        case SCREEN_EVENT_MANAGER: {
            int subtype = 0;
            if (screen_event_from_window(p) &&
                screen_get_event_property_iv(p->ev, SCREEN_PROPERTY_SUBTYPE,
                                             &subtype) == 0 &&
                subtype == 0x4d595543) {
                p->quit = true;
            }
            break;
        }
        case SCREEN_EVENT_POINTER:
            if (screen_event_from_window(p)) screen_apply_pointer(p);
            break;
        case SCREEN_EVENT_KEYBOARD:
            if (screen_event_from_window(p)) screen_apply_keyboard(p);
            break;
        default:
            /* Remaining metadata events are drained but not translated;
             * see the file header. */
            break;
        }
        if (p->quit) break;
    }
    return p->quit ? PLATFORM_EVENT_QUIT : PLATFORM_EVENT_NONE;
}

u32 platform_poll_text(Platform *p, PlatformTextEvent *out, u32 max_events)
{
    (void)p; (void)out; (void)max_events;
    return 0u;
}
void platform_ime_set_enabled(Platform *p, bool enabled) { (void)p; (void)enabled; }
bool platform_ime_is_enabled(Platform *p) { (void)p; return false; }
void platform_ime_set_surrounding(Platform *p, const char *s, i32 c, i32 a)
{
    (void)p; (void)s; (void)c; (void)a;
}
void platform_ime_set_spot(Platform *p, i32 x, i32 y) { (void)p; (void)x; (void)y; }
InputState *platform_input(Platform *p) { return p ? &p->input : NULL; }

/* WSI consumers pair the window with the Screen context: Vulkan's
 * vkCreateScreenSurfaceQNX takes (screen_context, screen_window). */
void *platform_window_native(Platform *p)   { return p ? (void *)p->win  : NULL; }
void *platform_display_native(Platform *p)  { return p ? (void *)p->ctx  : NULL; }
void *platform_surface_native(Platform *p)  { return p ? (void *)p->win  : NULL; }

void platform_window_show(Platform *p)
{
    if (!p) return;
    int visible = 1;
    (void)screen_set_window_property_iv(p->win, SCREEN_PROPERTY_VISIBLE, &visible);
    (void)screen_flush_context(p->ctx, 0);
}
void platform_window_hide(Platform *p)
{
    if (!p) return;
    int visible = 0;
    (void)screen_set_window_property_iv(p->win, SCREEN_PROPERTY_VISIBLE, &visible);
}

static void screen_size(Platform *p, u32 *w, u32 *h)
{
    u32 cw = p ? p->width : 0u;
    u32 ch = p ? p->height : 0u;
    if (p && p->win) {
        int size[2] = { 0, 0 };
        if (screen_get_window_property_iv(p->win, SCREEN_PROPERTY_SIZE, size) == 0 &&
            size[0] > 0 && size[1] > 0) {
            cw = (u32)size[0];
            ch = (u32)size[1];
            p->width = cw;
            p->height = ch;
            if (p->wsi.logical_width != cw || p->wsi.logical_height != ch ||
                p->wsi.drawable_width != cw || p->wsi.drawable_height != ch) {
                (void)platform_wsi_surface_resize(&p->wsi, cw, ch, cw, ch);
            }
        }
    }
    if (w) *w = cw;
    if (h) *h = ch;
}
void platform_get_size(Platform *p, u32 *w, u32 *h)         { screen_size(p, w, h); }
void platform_get_logical_size(Platform *p, u32 *w, u32 *h) { screen_size(p, w, h); }
void platform_get_drawable_size(Platform *p, u32 *w, u32 *h){ screen_size(p, w, h); }

/* A Screen application window always covers the display. */
bool platform_set_window_mode(Platform *p, PlatformWindowMode mode)
{
    if (!p || !platform_window_mode_valid(mode)) return false;
    return platform_window_mode_request(&p->window_mode, mode) ==
           PLATFORM_WINDOW_MODE_ACTION_NONE;
}
PlatformWindowMode platform_get_window_mode(Platform *p)
{
    return p ? p->window_mode.current : PLATFORM_WINDOW_MODE_WINDOWED;
}
void platform_toggle_fullscreen(Platform *p)
{
    if (p) (void)platform_set_window_mode(p, platform_window_mode_toggle_target(&p->window_mode));
}
/* No window frame exists: only "undecorated" is accepted. */
bool platform_set_window_decorated(Platform *p, bool decorated)
{
    return p && platform_window_mode_set_decorated(&p->window_mode, decorated) ==
                    PLATFORM_DECORATION_ACTION_NONE;
}
bool platform_get_window_decorated(Platform *p) { return p && p->window_mode.decorated; }
bool platform_window_title_bar_visible(Platform *p)
{
    return p && platform_window_mode_title_bar_visible(&p->window_mode);
}
void platform_mouse_capture(Platform *p, bool v) { (void)p; (void)v; }
void platform_mouse_set_visible(Platform *p, bool v) { (void)p; (void)v; }
void platform_mouse_set_relative(Platform *p, bool v) { (void)p; (void)v; }
bool platform_cursor_set(Platform *p, PlatformCursor c) { (void)p; (void)c; return false; }
bool platform_window_begin_move(Platform *p) { (void)p; return false; }
bool platform_needs_client_decoration(Platform *p) { (void)p; return false; }
bool platform_clipboard_set_text(Platform *p, const char *s) { (void)p; (void)s; return false; }
bool platform_clipboard_get_text(Platform *p, char *s, usize n) { (void)p; (void)s; (void)n; return false; }
PlatformClipboardResult platform_clipboard_get_text_alloc(Platform *p, char **out)
{
    (void)p;
    if (out) *out = NULL;
    return PLATFORM_CLIPBOARD_EMPTY;
}
f32 platform_get_dpi(Platform *p)          { (void)p; return 96.0f; }
f32 platform_get_content_scale(Platform *p){ (void)p; return 1.0f; }
f32 platform_get_input_scale(Platform *p)  { (void)p; return 1.0f; }
i32 platform_get_scale_factor(Platform *p) { (void)p; return 1; }
bool platform_get_media_context(Platform *p, PlatformMediaContext *out)
{
    if (!p || !out) { if (out) memset(out, 0, sizeof(*out)); return false; }
    *out = p->media;
    return true;
}
u64 platform_get_media_generation(Platform *p) { return p ? p->media_generation : 0u; }
static bool screen_monitor_displays(Platform *p, screen_display_t **out,
                                    u32 *count)
{
    int native_count = 0;
    screen_display_t *displays;
    int i;
    *out = NULL;
    *count = 0u;
    if (p == NULL ||
        screen_get_context_property_iv(p->ctx, SCREEN_PROPERTY_DISPLAY_COUNT,
                                       &native_count) != 0 ||
        native_count < 0 || native_count > 64) return false;
    if (native_count == 0) return true;
    displays = (screen_display_t *)calloc((size_t)native_count,
                                          sizeof(*displays));
    if (displays == NULL) return false;
    if (screen_get_context_property_pv(p->ctx, SCREEN_PROPERTY_DISPLAYS,
                                       (void **)displays) != 0) {
        free(displays);
        return false;
    }
    for (i = 0; i < native_count; ++i) {
        if (displays[i] == NULL) {
            free(displays);
            return false;
        }
    }
    *out = displays;
    *count = native_count > PLATFORM_MAX_MONITORS
                 ? PLATFORM_MAX_MONITORS : (u32)native_count;
    return true;
}

u32 platform_get_monitor_count(Platform *p)
{
    screen_display_t *displays;
    u32 count;
    if (!screen_monitor_displays(p, &displays, &count)) return 0u;
    free(displays);
    return count;
}

bool platform_get_monitor_info(Platform *p, u32 i, MonitorInfo *out)
{
    screen_display_t *displays;
    screen_display_t current = NULL;
    screen_display_mode_t mode;
    int size[2] = { 0, 0 };
    int position[2] = { 0, 0 };
    int physical[2] = { 0, 0 };
    int dpi[2] = { 0, 0 };
    u32 count;
    bool ok = false;
    if (out != NULL) memset(out, 0, sizeof(*out));
    if (out == NULL || !screen_monitor_displays(p, &displays, &count))
        return false;
    if (i >= count) {
        free(displays);
        return false;
    }
    if (screen_get_display_property_iv(displays[i], SCREEN_PROPERTY_SIZE,
                                       size) != 0 || size[0] <= 0 ||
        size[1] <= 0 ||
        screen_get_display_property_iv(displays[i], SCREEN_PROPERTY_POSITION,
                                       position) != 0) goto done;
    out->x = position[0];
    out->y = position[1];
    out->width = (u32)size[0];
    out->height = (u32)size[1];
    out->dpi = 96.0f;
    out->scale = 1;
    if (screen_get_display_property_cv(displays[i], SCREEN_PROPERTY_ID_STRING,
                                       (int)sizeof(out->name), out->name) == 0)
        out->name[sizeof(out->name) - 1u] = '\0';
    if (out->name[0] == '\0') {
        memcpy(out->name, "Screen ", 7u);
        out->name[7] = (char)('1' + i);
        out->name[8] = '\0';
    }
    memset(&mode, 0, sizeof(mode));
    if (screen_get_display_property_pv(displays[i], SCREEN_PROPERTY_MODE,
                                       (void **)&mode) == 0 &&
        (mode.flags & SCREEN_DISPLAY_MODE_REFRESH_VALID) != 0u)
        out->refresh_rate = mode.refresh;
    if (screen_get_display_property_iv(displays[i], SCREEN_PROPERTY_DPI,
                                       dpi) == 0 && dpi[0] > 0) {
        out->dpi = (f32)dpi[0];
    } else if (screen_get_display_property_iv(displays[i],
                                              SCREEN_PROPERTY_PHYSICAL_SIZE,
                                              physical) == 0) {
        if (physical[0] > 0)
            out->dpi = (f32)size[0] * 25.4f / (f32)physical[0];
        else if (physical[1] > 0)
            out->dpi = (f32)size[1] * 25.4f / (f32)physical[1];
    }
    if (out->dpi >= (f32)INT32_MAX * 96.0f) {
        out->scale = INT32_MAX;
    } else {
        out->scale = (i32)((out->dpi + 48.0f) / 96.0f);
        if (out->scale < 1) out->scale = 1;
    }
    out->primary = i == 0u;
    if (screen_get_window_property_pv(p->win, SCREEN_PROPERTY_DISPLAY,
                                      (void **)&current) == 0 &&
        current != NULL) out->primary = current == displays[i];
    ok = true;
done:
    free(displays);
    if (!ok) memset(out, 0, sizeof(*out));
    return ok;
}

#endif /* ENGINE_PLATFORM_QNX && ENGINE_QNX_SCREEN */
