#include "test_framework.h"
#include <platform/platform.h>
#include <platform/platform_vk_surface.h>
#include <screen/screen.h>

static int failure_property = -1;
static bool failure_flush;
static int destroyed_contexts;
static int destroyed_windows;
static int destroyed_events;

int __real_screen_set_window_property_iv(screen_window_t window, int property,
                                         const int *value);
int __real_screen_flush_context(screen_context_t context, int flags);
int __real_screen_destroy_context(screen_context_t context);
int __real_screen_destroy_window(screen_window_t window);
int __real_screen_destroy_event(screen_event_t event);

int __wrap_screen_set_window_property_iv(screen_window_t window, int property,
                                         const int *value)
{
    if (property == failure_property) return -1;
    return __real_screen_set_window_property_iv(window, property, value);
}

int __wrap_screen_flush_context(screen_context_t context, int flags)
{
    if (failure_flush) return -1;
    return __real_screen_flush_context(context, flags);
}

int __wrap_screen_destroy_context(screen_context_t context)
{
    destroyed_contexts++;
    return __real_screen_destroy_context(context);
}

int __wrap_screen_destroy_window(screen_window_t window)
{
    destroyed_windows++;
    return __real_screen_destroy_window(window);
}

int __wrap_screen_destroy_event(screen_event_t event)
{
    destroyed_events++;
    return __real_screen_destroy_event(event);
}

static bool create_failure_cleans_up(int property, bool flush)
{
    const PlatformConfig config = {
        .width = 64, .height = 64, .title = "Break QNX Screen failure injection"
    };
    Platform *platform;
    bool clean;

    failure_property = property;
    failure_flush = flush;
    destroyed_contexts = 0;
    destroyed_windows = 0;
    destroyed_events = 0;
    platform = platform_create(&config);
    failure_property = -1;
    failure_flush = false;
    clean = platform == NULL && destroyed_contexts == 1 &&
            destroyed_windows == 1 && destroyed_events == 1;
    if (platform != NULL) platform_destroy(platform);
    return clean;
}

static void runtime_failure(const char *message)
{
    printf("  FAIL: %s\n", message);
    g_test_fail++;
}

TEST(qnx_screen_initialization_failure_cleans_up)
{
    ASSERT_TRUE(create_failure_cleans_up(SCREEN_PROPERTY_SIZE, false));
    ASSERT_TRUE(create_failure_cleans_up(SCREEN_PROPERTY_FORMAT, false));
    ASSERT_TRUE(create_failure_cleans_up(SCREEN_PROPERTY_USAGE, false));
    ASSERT_TRUE(create_failure_cleans_up(-1, true));
}

TEST(qnx_screen_native_window_lifecycle)
{
    const PlatformConfig config = {
        .width = 320, .height = 240, .title = "Break QNX Screen runtime"
    };
    Platform *platform;
    screen_window_t window;
    screen_context_t context;
    PlatformWsiSurface wsi;
    PlatformMediaContext media;
    const char *extensions[2] = { NULL, NULL };
    int size[2] = { 0, 0 };
    int format = 0;
    int usage = 0;
    int expected_usage = SCREEN_USAGE_READ | SCREEN_USAGE_WRITE;
    u32 width = 0u;
    u32 height = 0u;
#if defined(ENGINE_VULKAN)
    expected_usage |= SCREEN_USAGE_VULKAN;
#endif

    platform = platform_create(&config);
    if (platform == NULL) {
        runtime_failure("platform_create failed with a reachable Screen service");
        return;
    }
    context = (screen_context_t)platform_display_native(platform);
    window = (screen_window_t)platform_surface_native(platform);
    if (context == NULL || window == NULL ||
        platform_window_native(platform) != (void *)window) {
        runtime_failure("incomplete Screen context/window handles");
        goto cleanup;
    }
    if (screen_get_window_property_iv(window, SCREEN_PROPERTY_SIZE, size) != 0 ||
        size[0] != 320 || size[1] != 240) {
        runtime_failure("native Screen window size was not initialized");
    }
    if (screen_get_window_property_iv(window, SCREEN_PROPERTY_FORMAT, &format) != 0 ||
        format != SCREEN_FORMAT_RGBA8888) {
        runtime_failure("native Screen window format was not initialized");
    }
    if (screen_get_window_property_iv(window, SCREEN_PROPERTY_USAGE, &usage) != 0 ||
        (usage & expected_usage) != expected_usage) {
        runtime_failure("native Screen window usage is incomplete");
    }
    platform_get_size(platform, &width, &height);
    if (width != 320u || height != 240u) {
        runtime_failure("platform size does not match the Screen window");
    }
    platform_get_drawable_size(platform, &width, &height);
    if (width != 320u || height != 240u) {
        runtime_failure("drawable size does not match the Screen window");
    }
    if (!platform_wsi_surface_query(platform, &wsi) ||
        wsi.backend != PLATFORM_WSI_BACKEND_QNX ||
        !platform_wsi_frame_allowed(&wsi)) {
        runtime_failure("Screen WSI is not ready after native window creation");
    }
    if (platform_get_media_generation(platform) == 0u ||
        !platform_get_media_context(platform, &media) || !media.screen) {
        runtime_failure("Screen media context was not initialized");
    }
    if (platform_input(platform) == NULL) {
        runtime_failure("Screen input state was not initialized");
    }
    if (platform_vk_required_instance_extensions(platform, extensions, 2u) != 2u ||
        strcmp(extensions[0], "VK_KHR_surface") != 0 ||
        strcmp(extensions[1], "VK_QNX_screen_surface") != 0) {
        runtime_failure("Screen Vulkan instance extensions are incorrect");
    }
    platform_window_show(platform);
    if (platform_poll(platform) == PLATFORM_EVENT_QUIT) {
        runtime_failure("unexpected close event during Screen startup");
    }

cleanup:
    platform_destroy(platform);
}

TEST(qnx_screen_monitor_enumeration_matches_native_displays)
{
    const PlatformConfig config = {
        .width = 64, .height = 64, .title = "Break QNX Screen monitor runtime"
    };
    Platform *platform = platform_create(&config);
    screen_context_t context;
    screen_window_t window;
    screen_display_t *displays = NULL;
    screen_display_t current = NULL;
    MonitorInfo invalid;
    MonitorInfo zero;
    int native_count = 0;
    int current_result;
    u32 count;
    u32 expected_count;
    u32 i;

    if (platform == NULL) {
        runtime_failure("platform_create failed in monitor runtime");
        return;
    }
    context = (screen_context_t)platform_display_native(platform);
    window = (screen_window_t)platform_surface_native(platform);
    count = platform_get_monitor_count(platform);
    if (count == 0u || count > PLATFORM_MAX_MONITORS) {
        runtime_failure("Screen monitor count is zero or exceeds the public bound");
        goto cleanup;
    }
    if (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_COUNT,
                                       &native_count) != 0 ||
        native_count <= 0 || native_count > 64) {
        runtime_failure("native Screen display count is unavailable or unsafe");
        goto cleanup;
    }
    expected_count = native_count > PLATFORM_MAX_MONITORS
                         ? (u32)PLATFORM_MAX_MONITORS
                         : (u32)native_count;
    if (count != expected_count) {
        runtime_failure("Platform and native Screen display counts differ");
        goto cleanup;
    }
    displays = (screen_display_t *)calloc((usize)native_count, sizeof(*displays));
    if (displays == NULL ||
        screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS,
                                       (void **)displays) != 0) {
        runtime_failure("native Screen display list query failed");
        goto cleanup;
    }
    current_result = screen_get_window_property_pv(window, SCREEN_PROPERTY_DISPLAY,
                                                   (void **)&current);

    for (i = 0u; i < count; ++i) {
        MonitorInfo info;
        screen_display_mode_t mode;
        int size[2] = {0, 0};
        int position[2] = {0, 0};
        int native_dpi[2] = {0, 0};
        int physical[2] = {0, 0};
        int native_type = 0;
        int dpi_result;
        int physical_result;
        int mode_result;
        int name_result;
        char native_name[64] = {0};
        const char *dpi_source;
        f32 expected_dpi;
        i32 expected_scale;
        bool expected_primary;

        if (displays[i] == NULL) {
            runtime_failure("native Screen returned a NULL display handle");
            continue;
        }
        memset(&info, 0, sizeof(info));
        if (!platform_get_monitor_info(platform, i, &info)) {
            runtime_failure("Platform monitor info query failed");
            continue;
        }
        if (screen_get_display_property_iv(displays[i], SCREEN_PROPERTY_SIZE, size) != 0 ||
            size[0] <= 0 || size[1] <= 0) {
            runtime_failure("native Screen display SIZE is invalid");
            continue;
        }
        if (screen_get_display_property_iv(displays[i], SCREEN_PROPERTY_POSITION,
                                           position) != 0) {
            runtime_failure("native Screen display POSITION query failed");
            continue;
        }
        if (info.width != (u32)size[0] || info.height != (u32)size[1] ||
            info.x != position[0] || info.y != position[1]) {
            runtime_failure("Platform monitor geometry differs from native Screen");
        }

        memset(&mode, 0, sizeof(mode));
        mode_result = screen_get_display_property_pv(displays[i], SCREEN_PROPERTY_MODE,
                                                     (void **)&mode);
        if (mode_result == 0 &&
            (mode.flags & SCREEN_DISPLAY_MODE_REFRESH_VALID) != 0u &&
            mode.refresh > 0u) {
            if (info.refresh_rate != mode.refresh) {
                runtime_failure("Platform refresh differs from the native display mode");
            }
        } else if (info.refresh_rate != 0u) {
            runtime_failure("unsupported refresh was not degraded to zero");
        }

        dpi_result = screen_get_display_property_iv(displays[i], SCREEN_PROPERTY_DPI,
                                                    native_dpi);
        physical_result = screen_get_display_property_iv(
            displays[i], SCREEN_PROPERTY_PHYSICAL_SIZE, physical);
        if (dpi_result == 0 && native_dpi[0] > 0 && native_dpi[1] > 0) {
            expected_dpi = (f32)native_dpi[0];
            dpi_source = "screen-dpi";
        } else if (physical_result == 0 && physical[0] > 0 && physical[1] > 0) {
            expected_dpi = (f32)size[0] * 25.4f / (f32)physical[0];
            dpi_source = "physical-size";
        } else {
            expected_dpi = 96.0f;
            dpi_source = "logical-fallback";
        }
        expected_scale = (i32)((expected_dpi + 48.0f) / 96.0f);
        if (expected_scale < 1) expected_scale = 1;
        if (fabs((double)info.dpi - (double)expected_dpi) > 0.01 ||
            info.scale != expected_scale) {
            runtime_failure("Platform DPI/scale does not match native data or explicit fallback");
        }

        name_result = screen_get_display_property_cv(
            displays[i], SCREEN_PROPERTY_ID_STRING, (int)sizeof(native_name), native_name);
        native_name[sizeof(native_name) - 1u] = '\0';
        if (name_result == 0 && native_name[0] != '\0') {
            if (strcmp(info.name, native_name) != 0) {
                runtime_failure("Platform monitor name differs from Screen ID_STRING");
            }
        } else {
            char expected_name[64];
            (void)snprintf(expected_name, sizeof(expected_name), "Screen %u",
                           (unsigned)(i + 1u));
            if (strcmp(info.name, expected_name) != 0) {
                runtime_failure("missing monitor name did not use the explicit fallback");
            }
        }

        expected_primary = current_result == 0 && current != NULL
                               ? displays[i] == current
                               : i == 0u;
        if (info.primary != expected_primary) {
            runtime_failure("Platform primary flag differs from the window display/default");
        }
        if (count == 1u && !info.primary) {
            runtime_failure("a sole Screen display must be primary");
        }

        (void)screen_get_display_property_iv(displays[i], SCREEN_PROPERTY_TYPE,
                                             &native_type);
        printf("\n  Monitor %u: name=%s type=0x%x position=(%d,%d) size=%ux%u "
               "refresh=%u dpi=%.1f source=%s scale=%d primary=%u "
               "physical=%dx%dmm mode-format=%d\n",
               (unsigned)i, info.name, native_type, info.x, info.y, info.width,
               info.height, info.refresh_rate, (double)info.dpi, dpi_source,
               info.scale, info.primary ? 1u : 0u, physical[0], physical[1],
               mode_result == 0 ? mode.format : -1);
        if (native_type == SCREEN_DISPLAY_TYPE_VIRTUAL &&
            (mode_result != 0 ||
             (mode.flags & SCREEN_DISPLAY_MODE_FORMAT_VALID) == 0u ||
             mode.format != SCREEN_FORMAT_RGBA8888)) {
            runtime_failure("current virtual display mode is not native RGBA8888");
        }
    }

    memset(&invalid, 0xa5, sizeof(invalid));
    memset(&zero, 0, sizeof(zero));
    if (platform_get_monitor_info(platform, count, &invalid) ||
        memcmp(&invalid, &zero, sizeof(invalid)) != 0) {
        runtime_failure("out-of-range monitor query did not fail with a zeroed output");
    }

cleanup:
    free(displays);
    platform_destroy(platform);
}

int main(void)
{
    const PlatformConfig probe = {
        .width = 64, .height = 64, .title = "Break QNX Screen probe"
    };
    Platform *platform = platform_create(&probe);
    if (platform == NULL) {
        printf("SKIP: no usable QNX Screen service\n");
        return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL ? 1 : 77;
    }
    platform_destroy(platform);
    printf("=== Running Tests ===\n");
    RUN_TEST(qnx_screen_native_window_lifecycle);
    RUN_TEST(qnx_screen_monitor_enumeration_matches_native_displays);
    RUN_TEST(qnx_screen_initialization_failure_cleans_up);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
