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
    RUN_TEST(qnx_screen_initialization_failure_cleans_up);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
