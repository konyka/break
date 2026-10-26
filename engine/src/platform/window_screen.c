/*
 * window_screen.c — QNX Screen window layer (ENGINE_QNX_SCREEN).
 *
 * Milestone: COMPILED. The platform creates its own native window through
 * the QNX Screen API (screen_context/screen_window), polls Screen events
 * (close + pointer), and exposes the window/context handles for a future
 * GL/Vulkan-via-Screen RHI. Runtime receipts require a target running the
 * screen service; until then every graphics entry point above this layer
 * stays fail-closed (headless RHI, docs/qnx_compat.md §7).
 *
 * Not yet mapped (follow-up with the graphics milestone): keyboard/text
 * events (drained, not translated), mouse wheel/relative mode, clipboard,
 * IME, monitors. Those surface fail-closed exactly like window_mobile.c.
 */

#if defined(ENGINE_PLATFORM_QNX) && defined(ENGINE_QNX_SCREEN)

#include <platform/platform.h>
#include <screen/screen.h>
#include <stdlib.h>
#include <string.h>

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
    (void)screen_set_window_property_iv(p->win, SCREEN_PROPERTY_SIZE, size);
    int format = SCREEN_FORMAT_RGBA8888;
    (void)screen_set_window_property_iv(p->win, SCREEN_PROPERTY_FORMAT, &format);
    int usage = SCREEN_USAGE_READ | SCREEN_USAGE_WRITE;
    (void)screen_set_window_property_iv(p->win, SCREEN_PROPERTY_USAGE, &usage);
    (void)screen_flush_context(p->ctx, 0);

    p->width = cfg->width;
    p->height = cfg->height;
    (void)platform_wsi_surface_init(&p->wsi, true, cfg->width, cfg->height,
                                    cfg->width, cfg->height);
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
        case SCREEN_EVENT_POINTER:
            screen_apply_pointer(p);
            break;
        default:
            /* Keyboard/text/metadata events are drained but not translated
             * yet; see the file header. */
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
        }
    }
    if (w) *w = cw;
    if (h) *h = ch;
}
void platform_get_size(Platform *p, u32 *w, u32 *h)         { screen_size(p, w, h); }
void platform_get_logical_size(Platform *p, u32 *w, u32 *h) { screen_size(p, w, h); }
void platform_get_drawable_size(Platform *p, u32 *w, u32 *h){ screen_size(p, w, h); }

void platform_toggle_fullscreen(Platform *p) { (void)p; }
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
u32 platform_get_monitor_count(Platform *p) { (void)p; return 0u; }
bool platform_get_monitor_info(Platform *p, u32 i, MonitorInfo *out)
{
    (void)p; (void)i; (void)out;
    return false;
}

#endif /* ENGINE_PLATFORM_QNX && ENGINE_QNX_SCREEN */
