int platform_mobile_translation_unit;

#if defined(ENGINE_PLATFORM_IOS) || defined(ENGINE_PLATFORM_ANDROID) || defined(ENGINE_PLATFORM_HARMONYOS)

#include <platform/platform.h>
#include <stdlib.h>
#include <string.h>

struct Platform {
    void *native_window;
    void *native_display;
    InputState input;
    u32 width, height;
    bool ime_enabled;
    u64 media_generation;
    PlatformMediaContext media;
};

Platform *platform_create(const PlatformConfig *cfg)
{
    Platform *p;
    if (!platform_config_valid(cfg) || cfg->native_window == NULL) {
        return NULL;
    }
    p = calloc(1, sizeof(*p));
    if (!p) return NULL;
    /* Handles remain owned by the host; Android Vulkan takes its own reference. */
    p->native_window = cfg->native_window;
    p->native_display = cfg->native_display;
    p->width = cfg->width;
    p->height = cfg->height;
    p->media_generation = 1u;
    p->media.screen = true;
    p->media.capabilities = PLATFORM_MEDIA_CAP_POINTER_COARSE |
                            PLATFORM_MEDIA_CAP_ANY_POINTER_COARSE |
                            PLATFORM_MEDIA_CAP_COLOR_SRGB;
    p->media.known = PLATFORM_MEDIA_KNOWN_POINTER |
                     PLATFORM_MEDIA_KNOWN_ANY_POINTER |
                     PLATFORM_MEDIA_KNOWN_COLOR_GAMUT;
    input_init(&p->input);
    return p;
}

void platform_destroy(Platform *p) { free(p); }
PlatformEventResult platform_poll(Platform *p) {
    if (!p) return PLATFORM_EVENT_QUIT;
    input_new_frame(&p->input);
    return PLATFORM_EVENT_NONE;
}
u32 platform_poll_text(Platform *p, PlatformTextEvent *out, u32 max_events) {
    (void)p; (void)out; (void)max_events; return 0u;
}
void platform_ime_set_enabled(Platform *p, bool enabled) { if (p) p->ime_enabled = enabled; }
bool platform_ime_is_enabled(Platform *p) { return p && p->ime_enabled; }
void platform_ime_set_surrounding(Platform *p, const char *s, i32 c, i32 a) { (void)p; (void)s; (void)c; (void)a; }
void platform_ime_set_spot(Platform *p, i32 x, i32 y) { (void)p; (void)x; (void)y; }
InputState *platform_input(Platform *p) { return p ? &p->input : NULL; }
void *platform_window_native(Platform *p) { return p ? p->native_window : NULL; }
void *platform_display_native(Platform *p) { return p ? p->native_display : NULL; }
void *platform_surface_native(Platform *p) { return p ? p->native_window : NULL; }

static void mobile_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p ? p->width : 0u;
    if (h) *h = p ? p->height : 0u;
}
void platform_get_size(Platform *p, u32 *w, u32 *h) { mobile_size(p, w, h); }
void platform_get_logical_size(Platform *p, u32 *w, u32 *h) { mobile_size(p, w, h); }
void platform_get_drawable_size(Platform *p, u32 *w, u32 *h) { mobile_size(p, w, h); }
void platform_toggle_fullscreen(Platform *p) { (void)p; }
void platform_mouse_capture(Platform *p, bool v) { (void)p; (void)v; }
void platform_mouse_set_visible(Platform *p, bool v) { (void)p; (void)v; }
void platform_mouse_set_relative(Platform *p, bool v) { (void)p; (void)v; }
bool platform_cursor_set(Platform *p, PlatformCursor c) { (void)p; (void)c; return false; }
bool platform_window_begin_move(Platform *p) { (void)p; return false; }
bool platform_needs_client_decoration(Platform *p) { (void)p; return false; }
bool platform_clipboard_set_text(Platform *p, const char *s) { (void)p; (void)s; return false; }
bool platform_clipboard_get_text(Platform *p, char *s, usize n) { (void)p; (void)s; (void)n; return false; }
PlatformClipboardResult platform_clipboard_get_text_alloc(Platform *p, char **out) { (void)p; if (out) *out = NULL; return PLATFORM_CLIPBOARD_EMPTY; }
f32 platform_get_dpi(Platform *p) { (void)p; return 96.0f; }
f32 platform_get_content_scale(Platform *p) { (void)p; return 1.0f; }
f32 platform_get_input_scale(Platform *p) { (void)p; return 1.0f; }
i32 platform_get_scale_factor(Platform *p) { (void)p; return 1; }
bool platform_get_media_context(Platform *p, PlatformMediaContext *out) {
    if (!p || !out) { if (out) memset(out, 0, sizeof(*out)); return false; }
    *out = p->media; return true;
}
u64 platform_get_media_generation(Platform *p) { return p ? p->media_generation : 0u; }
u32 platform_get_monitor_count(Platform *p) { (void)p; return 0u; }
bool platform_get_monitor_info(Platform *p, u32 i, MonitorInfo *out) { (void)p; (void)i; (void)out; return false; }

#endif
