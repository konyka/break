/* C side of test_mycompose_gpu: the production frame path and screenshot
 * inspection. See test_mycompose_image.h. */
#include "test_mycompose_image.h"

#include <platform/input.h>
#include <platform/platform.h>
#include <platform/platform_text.h>
#include <rhi/rhi.h>
#include <rhi/rhi_native_vulkan.h>
#include <ui/myui_break.h>

#include "mypal/my_event.h"
#include "myr/my_font.h"
#include "myui/my_widget.h"
#include "myui/my_widget_class.h"
#include "myui/my_window.h"
#include "myui/my_window_manager.h"
#include "myui/mycompose_myui/my_compose_myui.h"
#include "myui/widgets/my_edit.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMPOSE_GPU_W 480u
#define COMPOSE_GPU_H 320u

struct ComposeGpu {
    int vulkan;
    Platform *platform;
    RHIDevice *dev;
    BreakUI *ui;
    my_window_t *win;
    MyComposeStore *store;
    MyComposeTreeBuilder *builder;
    MyComposeMyui *adapter;
    MyComposeRuntime *runtime;
    u8 *shot;
    usize shot_bytes;
    ComposeGpuCounters counters;
};

static int file_exists(const char *path) {
    FILE *f = path != NULL ? fopen(path, "rb") : NULL;
    if (f == NULL) return 0;
    fclose(f);
    return 1;
}

static int glyph_size(my_font_t *font, uint32_t cp, int32_t *w, int32_t *h) {
    my_glyph_t g;
    int ink = 0;
    memset(&g, 0, sizeof(g));
    *w = 0;
    *h = 0;
    if (font != NULL && my_font_get_glyph(font, cp, 24, &g) == MY_RET_OK) {
        ink = g.bitmap != NULL && g.w > 0 && g.h > 0;
        *w = g.w;
        *h = g.h;
        my_font_glyph_release(&g);
    }
    return ink;
}

/* Each bundled face must load on its own and draw its script; the BreakUI
 * chain must draw U+5927 with the NotoSansSC metrics (not the bitmap). */
static int check_fonts(ComposeGpu *gpu, const char *mono, const char *cjk,
    ComposeGpuFonts *fonts) {
    my_font_source_t one;
    my_font_t *font;
    my_font_t *chain = NULL;
    int32_t chain_size = 0, cw = 0, ch = 0;
    memset(fonts, 0, sizeof(*fonts));
    memset(&one, 0, sizeof(one));
    one.path = mono;
    font = file_exists(mono) ? my_font_create_chain_ex(NULL, &one, 1u, 64u) : NULL;
    fonts->mono_loaded = glyph_size(font, 'A', &fonts->mono_w, &fonts->mono_h);
    if (font != NULL) my_font_destroy(font);
    one.path = cjk;
    font = file_exists(cjk) ? my_font_create_chain_ex(NULL, &one, 1u, 64u) : NULL;
    fonts->cjk_loaded = glyph_size(font, 0x5927u, &fonts->cjk_w, &fonts->cjk_h);
    if (font != NULL) my_font_destroy(font);
    my_window_font_of_widget((my_widget_t *)gpu->win, &chain, &chain_size);
    fonts->chain_uses_cjk = glyph_size(chain, 0x5927u, &cw, &ch) &&
        cw == fonts->cjk_w && ch == fonts->cjk_h;
    return fonts->mono_loaded && fonts->cjk_loaded && fonts->chain_uses_cjk;
}

int compose_gpu_open(ComposeGpu **out, int vulkan, const char *mono_font,
    const char *cjk_font, ComposeGpuDevice *device, ComposeGpuFonts *fonts) {
    PlatformConfig config;
    RHIDeviceInfo info;
    my_font_source_t sources[2];
    ComposeGpu *gpu;
    RHIBackend backend = vulkan ? RHI_BACKEND_VULKAN : RHI_BACKEND_OPENGL;
    u32 w = 0u, h = 0u;
    void *window;
    *out = NULL;
    if (!file_exists(mono_font) || !file_exists(cjk_font)) {
        printf("FAIL: bundled font missing (mono=%s cjk=%s)\n",
            file_exists(mono_font) ? "ok" : mono_font,
            file_exists(cjk_font) ? "ok" : cjk_font);
        return 1;
    }
    gpu = (ComposeGpu *)calloc(1u, sizeof(*gpu));
    if (gpu == NULL) return 1;
    gpu->vulkan = vulkan;
    memset(&config, 0, sizeof(config));
    config.width = COMPOSE_GPU_W;
    config.height = COMPOSE_GPU_H;
    config.title = "compose mvi gpu";
    gpu->platform = platform_create(&config);
    if (gpu->platform == NULL) {
        printf("UNAVAILABLE backend=%s reason=wayland-platform-create\n",
            vulkan ? "vulkan" : "opengl");
        free(gpu);
        return 77;
    }
    platform_get_drawable_size(gpu->platform, &w, &h);
    window = vulkan ? platform_surface_native(gpu->platform)
                    : platform_window_native(gpu->platform);
    gpu->dev = rhi_device_create(backend, window,
        platform_display_native(gpu->platform), w, h);
    if (gpu->dev == NULL) {
        printf("UNAVAILABLE backend=%s reason=device-create\n",
            vulkan ? "vulkan" : "opengl");
        platform_destroy(gpu->platform);
        free(gpu);
        return 77;
    }
    memset(&info, 0, sizeof(info));
    (void)rhi_device_get_info(gpu->dev, &info);
    memset(device, 0, sizeof(*device));
    device->backend = (int)info.backend;
    snprintf(device->name, sizeof(device->name), "%s", info.device_name);
    device->vendor_id = info.vendor_id;
    device->device_id = info.device_id;
    device->api_version = info.api_version;
    device->driver_version = info.driver_version;
    device->device_type = (int)info.device_type;
    device->device_type_name = rhi_device_type_name(info.device_type);
    rhi_device_attach_wsi(gpu->dev, platform_wsi_surface(gpu->platform));
    rhi_set_vsync(gpu->dev, false);
    *out = gpu;
    if (info.backend != backend) {
        printf("FAIL: requested backend %d, device reports %d (fallback)\n",
            (int)backend, (int)info.backend);
        return 1;
    }
    memset(sources, 0, sizeof(sources));
    sources[0].path = mono_font;
    sources[1].path = cjk_font;
    gpu->ui = break_ui_create();
    if (gpu->ui == NULL || !break_ui_init_with_fonts(gpu->ui, gpu->platform,
            gpu->dev, sources, 2u, COMPOSE_GPU_W, COMPOSE_GPU_H)) {
        printf("FAIL: break_ui_init_with_fonts\n");
        return 1;
    }
    gpu->win = break_ui_get_window(gpu->ui);
    if (!check_fonts(gpu, mono_font, cjk_font, fonts)) {
        printf("FAIL: fonts mono=%d cjk=%d chain_cjk=%d\n", fonts->mono_loaded,
            fonts->cjk_loaded, fonts->chain_uses_cjk);
        return 1;
    }
    return 0;
}

int compose_gpu_bind(ComposeGpu *gpu, MyComposeStore *store, MyComposeView view,
    void *view_context) {
    MyComposeRuntimeConfig config;
    if (gpu == NULL || store == NULL) return 1;
    gpu->store = store;
    gpu->builder = my_compose_tree_builder_create();
    gpu->adapter = gpu->builder != NULL
        ? my_compose_myui_create(gpu->win, gpu->builder, store) : NULL;
    if (gpu->adapter == NULL) return 1;
    memset(&config, 0, sizeof(config));
    config.store = store;
    config.view = view;
    config.view_context = view_context;
    config.sink = my_compose_myui_sink(gpu->adapter);
    gpu->runtime = my_compose_runtime_create(gpu->builder, &config);
    return gpu->runtime != NULL ? 0 : 1;
}

/* One production frame: platform_poll -> [synthetic InputState edges] ->
 * break_ui_pump -> [direct IME commit] -> my_compose_myui_pump ->
 * break_ui_frame_begin/render -> rhi_frame_end -> rhi_screenshot ->
 * rhi_present. */
int compose_gpu_frame(ComposeGpu *gpu, const ComposeGpuInject *inject,
    const char *direct_commit, int want_shot, int *shot_taken) {
    u32 nw = 0u, nh = 0u, lw = 0u, lh = 0u;
    bool skip = false;
    RHICmdBuffer *cmd;
    MyComposeStatus status;
    if (shot_taken != NULL) *shot_taken = 0;
    if (platform_poll(gpu->platform) == PLATFORM_EVENT_QUIT) {
        printf("FAIL: platform_poll reported QUIT\n");
        return 1;
    }
    platform_get_drawable_size(gpu->platform, &nw, &nh);
    if (nw != 0u && nh != 0u && (nw != gpu->counters.drawable_w ||
            nh != gpu->counters.drawable_h)) {
        if (gpu->counters.drawable_w != 0u) rhi_device_resize(gpu->dev, nw, nh);
        gpu->counters.drawable_w = nw;
        gpu->counters.drawable_h = nh;
    }
    platform_get_logical_size(gpu->platform, &lw, &lh);
    gpu->counters.logical_w = lw != 0u ? lw : COMPOSE_GPU_W;
    gpu->counters.logical_h = lh != 0u ? lh : COMPOSE_GPU_H;
    if (inject != NULL) {
        InputState *input = platform_input(gpu->platform);
        float scale = platform_get_input_scale(gpu->platform);
        if (scale <= 0.0f) scale = 1.0f;
        if (inject->move) input_set_mouse(input, inject->x * scale, inject->y * scale);
        if (inject->key >= 0) {
            input_set_key(input, inject->key, inject->press != 0);
            if (inject->key >= INPUT_MOUSE_LEFT && inject->key <= INPUT_MOUSE_5) {
                gpu->counters.synthetic_pointer_edges++;
            } else {
                gpu->counters.synthetic_key_edges++;
            }
        }
    }
    {
        uint64_t before = compose_gpu_alloc_count();
        break_ui_pump(gpu->ui);
        gpu->counters.myui_allocs += compose_gpu_alloc_count() - before;
    }
    if (direct_commit != NULL) {
        /* break_ui_pump already drained platform_poll_text; anything it
         * held would have been delivered there, so probe it is empty. */
        PlatformTextEvent events[8];
        u32 n = platform_poll_text(gpu->platform, events, 8u);
        u32 i;
        gpu->counters.queue_text_events += n;
        for (i = 0u; i < n; ++i) platform_text_event_destroy(&events[i]);
        {
            my_event_t e = my_event_init(MY_EVENT_IME_COMMIT);
            e.u.ime.text = direct_commit;
            e.u.ime.cursor = 0;
            (void)my_window_manager_dispatch_surface_event(
                break_ui_get_window_manager(gpu->ui), &e);
        }
        gpu->counters.direct_text_commits++;
    }
    {
        uint64_t before = compose_gpu_alloc_count();
        status = my_compose_myui_pump(gpu->adapter, gpu->runtime);
        gpu->counters.compose_allocs += compose_gpu_alloc_count() - before;
    }
    if (status != MY_COMPOSE_OK) {
        printf("FAIL: my_compose_myui_pump=%d\n", (int)status);
        return 1;
    }
    if (want_shot) my_widget_invalidate((my_widget_t *)gpu->win, NULL);
    gpu->counters.frames++;
    cmd = break_ui_frame_begin(gpu->ui, gpu->counters.drawable_w,
        gpu->counters.drawable_h, &skip, NULL);
    if (cmd == NULL) {
        gpu->counters.skipped++;
        return 0;
    }
    {
        uint64_t before = compose_gpu_alloc_count();
        break_ui_render(gpu->ui, cmd, gpu->counters.drawable_w, gpu->counters.drawable_h);
        gpu->counters.myui_allocs += compose_gpu_alloc_count() - before;
    }
    rhi_frame_end(gpu->dev);
    gpu->counters.rendered++;
    if (want_shot) {
        usize bytes = (usize)gpu->counters.drawable_w * gpu->counters.drawable_h * 4u;
        if (bytes != gpu->shot_bytes) {
            free(gpu->shot);
            gpu->shot = (u8 *)calloc(1u, bytes);
            gpu->shot_bytes = gpu->shot != NULL ? bytes : 0u;
        }
        if (gpu->shot == NULL || !rhi_screenshot(gpu->dev, 0, 0,
                gpu->counters.drawable_w, gpu->counters.drawable_h, gpu->shot,
                gpu->shot_bytes)) {
            printf("FAIL: rhi_screenshot\n");
            return 1;
        }
        gpu->counters.shots++;
        if (shot_taken != NULL) *shot_taken = 1;
    }
    rhi_present(gpu->dev);
    gpu->counters.presents++;
    return 0;
}

int compose_gpu_settle(ComposeGpu *gpu, unsigned idle) {
    unsigned i;
    int taken = 0;
    for (i = 0u; i < idle; ++i) {
        if (compose_gpu_frame(gpu, NULL, NULL, 0, NULL) != 0) return 1;
    }
    for (i = 0u; i < 60u; ++i) {
        if (compose_gpu_frame(gpu, NULL, NULL, 1, &taken) != 0) return 1;
        if (taken) return 0;
    }
    printf("FAIL: no rendered frame for the screenshot in 60 attempts\n");
    return 1;
}

int compose_gpu_rect(ComposeGpu *gpu, MyComposeNodeHandle node, ComposeGpuRect *out) {
    my_widget_t *w = my_compose_myui_widget(gpu->adapter, node);
    int32_t x = 0, y = 0;
    if (w == NULL) return 1;
    my_widget_local_to_global(w, &x, &y);
    out->x = x;
    out->y = y;
    out->w = w->rect.w;
    out->h = w->rect.h;
    return 0;
}

int compose_gpu_click(ComposeGpu *gpu, MyComposeNodeHandle node) {
    ComposeGpuRect r;
    ComposeGpuInject down, up;
    if (compose_gpu_rect(gpu, node, &r) != 0) return 1;
    memset(&down, 0, sizeof(down));
    down.move = 1;
    down.x = (float)r.x + (float)r.w / 2.0f;
    down.y = (float)r.y + (float)r.h / 2.0f;
    down.key = INPUT_MOUSE_LEFT;
    down.press = 1;
    up = down;
    up.press = 0;
    if (compose_gpu_frame(gpu, &down, NULL, 0, NULL) != 0 ||
        compose_gpu_frame(gpu, &up, NULL, 0, NULL) != 0) {
        return 1;
    }
    return compose_gpu_settle(gpu, 2u);
}

int compose_gpu_tap_key(ComposeGpu *gpu, int key) {
    ComposeGpuInject down, up;
    memset(&down, 0, sizeof(down));
    down.key = key;
    down.press = 1;
    up = down;
    up.press = 0;
    if (compose_gpu_frame(gpu, &down, NULL, 0, NULL) != 0 ||
        compose_gpu_frame(gpu, &up, NULL, 0, NULL) != 0) {
        return 1;
    }
    return compose_gpu_settle(gpu, 2u);
}

const void *compose_gpu_widget(ComposeGpu *gpu, MyComposeNodeHandle node) {
    return my_compose_myui_widget(gpu->adapter, node);
}

int compose_gpu_text(ComposeGpu *gpu, MyComposeNodeHandle node, char *out, size_t cap) {
    my_widget_t *w = my_compose_myui_widget(gpu->adapter, node);
    my_value_t value;
    int ok = 0;
    if (out == NULL || cap == 0u) return 1;
    out[0] = '\0';
    if (w == NULL) return 1;
    my_value_init(&value, NULL);
    if (my_widget_get_prop(w, "text", &value) == MY_RET_OK &&
        value.type == MY_VALUE_STR) {
        snprintf(out, cap, "%s", value.u.str != NULL ? value.u.str : "");
        ok = 1;
    }
    my_value_reset(&value);
    return ok ? 0 : 1;
}

int compose_gpu_focused(ComposeGpu *gpu, MyComposeNodeHandle node) {
    my_widget_t *w = my_compose_myui_widget(gpu->adapter, node);
    return w != NULL && gpu->win->dispatcher.focused == w;
}

ComposeGpuRegion compose_gpu_inspect(ComposeGpu *gpu, ComposeGpuRect r,
    uint32_t rgba, int tol) {
    ComposeGpuRegion out;
    const ComposeGpuCounters *c = &gpu->counters;
    float sx = c->logical_w != 0u ? (float)c->drawable_w / (float)c->logical_w : 1.0f;
    float sy = c->logical_h != 0u ? (float)c->drawable_h / (float)c->logical_h : 1.0f;
    int x0 = (int)((float)(r.x + 3) * sx), y0 = (int)((float)(r.y + 3) * sy);
    int x1 = (int)((float)(r.x + r.w - 3) * sx), y1 = (int)((float)(r.y + r.h - 3) * sy);
    int er = (int)((rgba >> 24) & 0xFFu), eg = (int)((rgba >> 16) & 0xFFu);
    int eb = (int)((rgba >> 8) & 0xFFu);
    int x, y;
    memset(&out, 0, sizeof(out));
    if (gpu->shot == NULL) return out;
    for (y = y0 < 0 ? 0 : y0; y < y1 && y < (int)c->drawable_h; ++y) {
        for (x = x0 < 0 ? 0 : x0; x < x1 && x < (int)c->drawable_w; ++x) {
            const u8 *p = &gpu->shot[((usize)y * c->drawable_w + (usize)x) * 4u];
            out.total++;
            if (abs((int)p[0] - er) <= tol && abs((int)p[1] - eg) <= tol &&
                abs((int)p[2] - eb) <= tol) {
                out.match++;
            }
            if (p[0] < 96u && p[1] < 96u && p[2] < 96u) {
                out.dark++;
                out.signature = out.signature * 1099511628211ull +
                    (uint64_t)((y - y0) * 4096 + (x - x0)) + 1u;
            }
        }
    }
    return out;
}

int compose_gpu_write_ppm(ComposeGpu *gpu, const char *path) {
    FILE *f;
    usize i, n;
    if (gpu->shot == NULL) return 1;
    f = fopen(path, "wb");
    if (f == NULL) return 1;
    fprintf(f, "P6\n%u %u\n255\n", gpu->counters.drawable_w, gpu->counters.drawable_h);
    n = (usize)gpu->counters.drawable_w * gpu->counters.drawable_h;
    for (i = 0u; i < n; ++i) (void)fwrite(gpu->shot + i * 4u, 1u, 3u, f);
    return fclose(f) == 0 ? 0 : 1;
}

void compose_gpu_counters(ComposeGpu *gpu, ComposeGpuCounters *out) {
    *out = gpu->counters;
}

uint32_t compose_gpu_vk_validation_messages(void) {
#ifdef ENGINE_VULKAN
    return rhi_vk_validation_message_count();
#else
    return 0u;
#endif
}

void compose_gpu_close(ComposeGpu *gpu) {
    if (gpu == NULL) return;
    if (gpu->dev != NULL) rhi_device_idle(gpu->dev);
    my_compose_runtime_destroy(gpu->runtime);
    my_compose_myui_destroy(gpu->adapter);
    my_compose_tree_builder_destroy(gpu->builder);
    if (gpu->ui != NULL) break_ui_destroy(gpu->ui);
    if (gpu->dev != NULL) rhi_device_destroy(gpu->dev);
    if (gpu->platform != NULL) platform_destroy(gpu->platform);
    free(gpu->shot);
    free(gpu);
}
