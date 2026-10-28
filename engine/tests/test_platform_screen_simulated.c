#include "test_framework.h"

/* QNX Screen window layer (window_screen.c) compiled on the host against a
 * fake Screen SDK (tests/fake_qnx_screen): checks the fixed-fullscreen
 * window-mode contract (FS2/FS4) without a QNX target. */

#include "platform/platform.h"

#include <screen/screen.h>

#include <stdlib.h>

#include <limits.h>

#define SCREEN_FAKE_DISPLAY_CAP (PLATFORM_MAX_MONITORS + 1)
#define SCREEN_FAKE_NATIVE_LIMIT 64

struct _screen_context { int unused; };
struct _screen_window {
    int size[2];
    int visible;
    screen_display_t display;
};
struct _screen_event {
    int type;
    screen_window_t window;
    int subtype;
};
struct _screen_display {
    int size[2];
    int position[2];
    int physical_size[2];
    int dpi[2];
    int type;
    int failure_property;
    screen_display_mode_t mode;
    char name[64];
};

static struct _screen_display g_displays[SCREEN_FAKE_DISPLAY_CAP];
static screen_display_t g_display_refs[SCREEN_FAKE_DISPLAY_CAP];
static int g_native_display_count = 1;
static int g_context_failure_property = -1;
static int g_window_failure_property = -1;
static int g_display_list_calls;
static int g_window_count;
static int g_pending_type = SCREEN_EVENT_NONE;
static screen_window_t g_pending_window;
static int g_pending_subtype;
static bool g_has_pending_event;

#if defined(SCREEN_TEST_WRAP_CALLOC)
static bool g_fail_calloc;
static size_t g_calloc_calls;
void *__real_calloc(size_t nmemb, size_t size);
void *__wrap_calloc(size_t nmemb, size_t size)
{
    g_calloc_calls++;
    if (g_fail_calloc) return NULL;
    return __real_calloc(nmemb, size);
}
#endif

static void screen_fake_reset(void)
{
    int i;
    memset(g_displays, 0, sizeof(g_displays));
    memset(g_display_refs, 0, sizeof(g_display_refs));
    for (i = 0; i < SCREEN_FAKE_DISPLAY_CAP; ++i) {
        g_display_refs[i] = &g_displays[i];
        g_displays[i].size[0] = 1280;
        g_displays[i].size[1] = 768;
        g_displays[i].position[0] = i * 1280;
        g_displays[i].position[1] = 0;
        g_displays[i].type = SCREEN_DISPLAY_TYPE_VIRTUAL;
        g_displays[i].failure_property = -1;
        g_displays[i].mode.width = 1280u;
        g_displays[i].mode.height = 768u;
        g_displays[i].mode.refresh = 60u;
        g_displays[i].mode.flags = SCREEN_DISPLAY_MODE_FORMAT_VALID |
                                   SCREEN_DISPLAY_MODE_REFRESH_VALID;
        g_displays[i].mode.format = SCREEN_FORMAT_RGBA8888;
        (void)snprintf(g_displays[i].name, sizeof(g_displays[i].name),
                       "screen-%d", i + 1);
    }
    g_native_display_count = 1;
    g_context_failure_property = -1;
    g_window_failure_property = -1;
    g_display_list_calls = 0;
    g_window_count = 0;
    g_pending_type = SCREEN_EVENT_NONE;
    g_pending_window = NULL;
    g_pending_subtype = 0;
    g_has_pending_event = false;
#if defined(SCREEN_TEST_WRAP_CALLOC)
    g_fail_calloc = false;
    g_calloc_calls = 0u;
#endif
}

int screen_create_context(screen_context_t *pctx, int flags)
{
    (void)flags;
    *pctx = calloc(1, sizeof(**pctx));
    return *pctx != NULL ? 0 : -1;
}

int screen_destroy_context(screen_context_t ctx)
{
    free(ctx);
    return 0;
}

int screen_flush_context(screen_context_t ctx, int flags)
{
    (void)ctx;
    (void)flags;
    return 0;
}

int screen_get_context_property_iv(screen_context_t ctx, int pname, int *param)
{
    (void)ctx;
    if (pname == g_context_failure_property) return -1;
    if (pname != SCREEN_PROPERTY_DISPLAY_COUNT) return -1;
    param[0] = g_native_display_count;
    return 0;
}

int screen_get_context_property_pv(screen_context_t ctx, int pname, void **param)
{
    (void)ctx;
    if (pname == g_context_failure_property) return -1;
    if (pname != SCREEN_PROPERTY_DISPLAYS || g_native_display_count < 0 ||
        g_native_display_count > SCREEN_FAKE_DISPLAY_CAP) {
        return -1;
    }
    g_display_list_calls++;
    memcpy(param, g_display_refs,
           (size_t)g_native_display_count * sizeof(g_display_refs[0]));
    return 0;
}

int screen_create_window(screen_window_t *pwin, screen_context_t ctx)
{
    (void)ctx;
    *pwin = calloc(1, sizeof(**pwin));
    if (*pwin != NULL) g_window_count++;
    return *pwin != NULL ? 0 : -1;
}

int screen_destroy_window(screen_window_t win)
{
    if (win != NULL) g_window_count--;
    free(win);
    return 0;
}

int screen_set_window_property_iv(screen_window_t win, int pname, const int *param)
{
    if (pname == SCREEN_PROPERTY_SIZE) {
        win->size[0] = param[0];
        win->size[1] = param[1];
    } else if (pname == SCREEN_PROPERTY_VISIBLE) {
        win->visible = param[0];
    }
    return 0;
}

int screen_get_window_property_iv(screen_window_t win, int pname, int *param)
{
    if (pname != SCREEN_PROPERTY_SIZE) return -1;
    param[0] = win->size[0];
    param[1] = win->size[1];
    return 0;
}

int screen_get_window_property_pv(screen_window_t win, int pname, void **param)
{
    if (pname == g_window_failure_property) return -1;
    if (pname != SCREEN_PROPERTY_DISPLAY) return -1;
    *(screen_display_t *)param = win->display;
    return 0;
}

int screen_get_display_property_iv(screen_display_t disp, int pname, int *param)
{
    if (disp == NULL || pname == disp->failure_property) return -1;
    switch (pname) {
    case SCREEN_PROPERTY_SIZE:
        memcpy(param, disp->size, sizeof(disp->size));
        return 0;
    case SCREEN_PROPERTY_POSITION:
        memcpy(param, disp->position, sizeof(disp->position));
        return 0;
    case SCREEN_PROPERTY_PHYSICAL_SIZE:
        memcpy(param, disp->physical_size, sizeof(disp->physical_size));
        return 0;
    case SCREEN_PROPERTY_DPI:
        memcpy(param, disp->dpi, sizeof(disp->dpi));
        return 0;
    case SCREEN_PROPERTY_TYPE:
        param[0] = disp->type;
        return 0;
    default:
        return -1;
    }
}

int screen_get_display_property_pv(screen_display_t disp, int pname, void **param)
{
    if (disp == NULL || pname == disp->failure_property ||
        pname != SCREEN_PROPERTY_MODE) {
        return -1;
    }
    memcpy(param, &disp->mode, sizeof(disp->mode));
    return 0;
}

int screen_get_display_property_cv(screen_display_t disp, int pname, int len,
                                   char *param)
{
    size_t length;
    if (disp == NULL || pname == disp->failure_property ||
        pname != SCREEN_PROPERTY_ID_STRING || len <= 0) {
        return -1;
    }
    length = strlen(disp->name);
    if (length >= (size_t)len) {
        memcpy(param, disp->name, (size_t)len);
    } else {
        memcpy(param, disp->name, length + 1u);
    }
    return 0;
}

int screen_create_event(screen_event_t *pev)
{
    *pev = calloc(1, sizeof(**pev));
    return *pev != NULL ? 0 : -1;
}

int screen_destroy_event(screen_event_t ev)
{
    free(ev);
    return 0;
}

int screen_get_event(screen_context_t ctx, screen_event_t ev, unsigned long long timeout)
{
    (void)ctx;
    (void)timeout;
    ev->type = SCREEN_EVENT_NONE;
    if (g_has_pending_event) {
        ev->type = g_pending_type;
        ev->window = g_pending_window;
        ev->subtype = g_pending_subtype;
        g_has_pending_event = false;
    }
    return 0;
}

int screen_get_event_property_iv(screen_event_t ev, int pname, int *param)
{
    if (pname == SCREEN_PROPERTY_TYPE) {
        param[0] = ev->type;
        return 0;
    }
    if (pname == SCREEN_PROPERTY_SUBTYPE) {
        param[0] = ev->subtype;
        return 0;
    }
    return -1;
}

int screen_get_event_property_pv(screen_event_t ev, int pname, void **param)
{
    if (pname != SCREEN_PROPERTY_WINDOW) return -1;
    *(screen_window_t *)param = ev->window;
    return 0;
}

static void screen_fake_manager_event(screen_window_t window, int subtype)
{
    g_pending_type = SCREEN_EVENT_MANAGER;
    g_pending_window = window;
    g_pending_subtype = subtype;
    g_has_pending_event = true;
}

#define SCREEN_CHECK(condition) do { \
    if (!(condition)) { \
        printf("\n  FAIL: %s:%d: %s\n", __FILE__, __LINE__, #condition); \
        g_test_fail++; \
    } \
} while (0)

static Platform *screen_fake_create(void)
{
    const PlatformConfig config = {
        .width = 640, .height = 360, .title = "Break QNX Screen fake"
    };
    return platform_create(&config);
}

static bool screen_monitor_is_zero(const MonitorInfo *info)
{
    MonitorInfo zero;
    memset(&zero, 0, sizeof(zero));
    return memcmp(info, &zero, sizeof(*info)) == 0;
}

TEST(screen_window_is_fixed_borderless_fullscreen)
{
    const PlatformConfig config = {.width = 640, .height = 360, .title = "Break QNX Screen"};
    Platform *platform;
    u32 width = 0;
    u32 height = 0;

    screen_fake_reset();
    platform = platform_create(&config);
    ASSERT_NOT_NULL(platform);
    ASSERT_EQ(g_window_count, 1);
    ASSERT_EQ(platform_poll(platform), PLATFORM_EVENT_NONE);
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_TRUE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN));
    ASSERT_FALSE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED));
    ASSERT_FALSE(platform_set_window_mode(platform, (PlatformWindowMode)7));
    platform_toggle_fullscreen(platform);
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_FALSE(platform_needs_client_decoration(platform));
    ASSERT_FALSE(platform_get_window_decorated(platform));
    ASSERT_FALSE(platform_window_title_bar_visible(platform));
    ASSERT_TRUE(platform_set_window_decorated(platform, false));
    ASSERT_FALSE(platform_set_window_decorated(platform, true));
    platform_get_size(platform, &width, &height);
    ASSERT_EQ(width, 640u);
    ASSERT_EQ(height, 360u);
    platform_destroy(platform);
    ASSERT_EQ(g_window_count, 0);
}

TEST(screen_start_fullscreen_is_the_same_fixed_mode)
{
    const PlatformConfig config = {.width = 640, .height = 360,
                                   .title = "Break QNX Screen start fullscreen",
                                   .start_fullscreen = true};
    Platform *platform;

    screen_fake_reset();
    platform = platform_create(&config);
    ASSERT_NOT_NULL(platform);
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_FALSE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED));
    platform_destroy(platform);
}

TEST(screen_window_mode_null_safety)
{
    ASSERT_FALSE(platform_set_window_mode(NULL, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN));
    ASSERT_EQ(platform_get_window_mode(NULL), PLATFORM_WINDOW_MODE_WINDOWED);
    platform_toggle_fullscreen(NULL);
}

TEST(screen_manager_close_filters_source_and_subtype)
{
    const PlatformConfig config = {.width = 640, .height = 360,
                                   .title = "Break QNX Screen manager"};
    Platform *platform;
    screen_window_t other = NULL;

    screen_fake_reset();
    platform = platform_create(&config);
    ASSERT_NOT_NULL(platform);
    ASSERT_EQ(screen_create_window(&other, NULL), 0);
    ASSERT_NOT_NULL(other);
    screen_fake_manager_event(other, 0x4d595543);
    ASSERT_EQ(platform_poll(platform), PLATFORM_EVENT_NONE);
    screen_fake_manager_event(platform_window_native(platform), 0);
    ASSERT_EQ(platform_poll(platform), PLATFORM_EVENT_NONE);
    screen_fake_manager_event(platform_window_native(platform), 0x4d595543);
    ASSERT_EQ(platform_poll(platform), PLATFORM_EVENT_QUIT);
    screen_destroy_window(other);
    platform_destroy(platform);
    ASSERT_EQ(g_window_count, 0);
}

TEST(screen_monitor_enumerates_native_display_metadata)
{
    Platform *platform;
    MonitorInfo info;
    MonitorInfo invalid;

    screen_fake_reset();
    g_displays[0].position[0] = 16;
    g_displays[0].position[1] = 32;
    g_displays[0].dpi[0] = 192;
    g_displays[0].dpi[1] = 192;
    (void)snprintf(g_displays[0].name, sizeof(g_displays[0].name), "virtual-1");
    platform = screen_fake_create();
    SCREEN_CHECK(platform != NULL);
    if (platform == NULL) return;

    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_count(platform) == 1u);
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(strcmp(info.name, "virtual-1") == 0);
    SCREEN_CHECK(info.x == 16 && info.y == 32);
    SCREEN_CHECK(info.width == 1280u && info.height == 768u);
    SCREEN_CHECK(info.refresh_rate == 60u);
    SCREEN_CHECK(fabs((double)info.dpi - 192.0) < 0.001);
    SCREEN_CHECK(info.scale == 2);
    SCREEN_CHECK(info.primary);

    memset(&invalid, 0xa5, sizeof(invalid));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 1u, &invalid));
    SCREEN_CHECK(screen_monitor_is_zero(&invalid));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, NULL));
    SCREEN_CHECK(platform_get_monitor_count(NULL) == 0u);
    memset(&invalid, 0xa5, sizeof(invalid));
    SCREEN_CHECK(!platform_get_monitor_info(NULL, 0u, &invalid));
    SCREEN_CHECK(screen_monitor_is_zero(&invalid));
    platform_destroy(platform);
}

TEST(screen_monitor_dpi_uses_physical_size_then_logical_fallback)
{
    Platform *platform;
    MonitorInfo info;

    screen_fake_reset();
    g_displays[0].size[0] = 1920;
    g_displays[0].size[1] = 1080;
    g_displays[0].physical_size[0] = 254;
    g_displays[0].physical_size[1] = 143;
    platform = screen_fake_create();
    SCREEN_CHECK(platform != NULL);
    if (platform == NULL) return;

    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(fabs((double)info.dpi - 192.0) < 0.01);
    SCREEN_CHECK(info.scale == 2);

    memset(g_displays[0].physical_size, 0, sizeof(g_displays[0].physical_size));
    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(fabs((double)info.dpi - 96.0) < 0.001);
    SCREEN_CHECK(info.scale == 1);

    g_displays[0].failure_property = SCREEN_PROPERTY_DPI;
    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(fabs((double)info.dpi - 96.0) < 0.001);
    g_displays[0].failure_property = SCREEN_PROPERTY_PHYSICAL_SIZE;
    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(fabs((double)info.dpi - 96.0) < 0.001);
    platform_destroy(platform);
}

TEST(screen_monitor_extreme_metadata_does_not_overflow)
{
    Platform *platform;
    MonitorInfo info;

    screen_fake_reset();
    g_displays[0].size[0] = INT_MAX;
    g_displays[0].size[1] = INT_MAX;
    g_displays[0].physical_size[0] = 1;
    g_displays[0].physical_size[1] = 1;
    platform = screen_fake_create();
    SCREEN_CHECK(platform != NULL);
    if (platform == NULL) return;
    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(info.dpi > 1.0e9f);
    SCREEN_CHECK(info.scale > 0);
    platform_destroy(platform);
}

TEST(screen_monitor_optional_metadata_degrades_explicitly)
{
    Platform *platform;
    MonitorInfo info;

    screen_fake_reset();
    platform = screen_fake_create();
    SCREEN_CHECK(platform != NULL);
    if (platform == NULL) return;

    g_displays[0].failure_property = SCREEN_PROPERTY_MODE;
    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(info.refresh_rate == 0u);

    g_displays[0].failure_property = SCREEN_PROPERTY_ID_STRING;
    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(strcmp(info.name, "Screen 1") == 0);

    g_displays[0].mode.flags &= ~SCREEN_DISPLAY_MODE_REFRESH_VALID;
    g_displays[0].failure_property = -1;
    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(info.refresh_rate == 0u);

    g_window_failure_property = SCREEN_PROPERTY_DISPLAY;
    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(info.primary);
    platform_destroy(platform);
}

TEST(screen_monitor_primary_associates_default_with_first_display)
{
    Platform *platform;
    MonitorInfo first;
    MonitorInfo second;
    screen_window_t window;

    screen_fake_reset();
    g_native_display_count = 2;
    platform = screen_fake_create();
    SCREEN_CHECK(platform != NULL);
    if (platform == NULL) return;
    window = (screen_window_t)platform_window_native(platform);

    memset(&first, 0, sizeof(first));
    memset(&second, 0, sizeof(second));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &first));
    SCREEN_CHECK(platform_get_monitor_info(platform, 1u, &second));
    SCREEN_CHECK(first.primary && !second.primary);

    window->display = &g_displays[1];
    memset(&first, 0, sizeof(first));
    memset(&second, 0, sizeof(second));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &first));
    SCREEN_CHECK(platform_get_monitor_info(platform, 1u, &second));
    SCREEN_CHECK(!first.primary && second.primary);

    window->display = NULL;
    memset(&first, 0, sizeof(first));
    SCREEN_CHECK(platform_get_monitor_info(platform, 0u, &first));
    SCREEN_CHECK(first.primary);
    platform_destroy(platform);
}

TEST(screen_monitor_bounds_native_count_and_rejects_overflow)
{
    Platform *platform;
    MonitorInfo info;
    int list_calls;

    screen_fake_reset();
    platform = screen_fake_create();
    SCREEN_CHECK(platform != NULL);
    if (platform == NULL) return;

    g_native_display_count = PLATFORM_MAX_MONITORS + 1;
    SCREEN_CHECK(platform_get_monitor_count(platform) == PLATFORM_MAX_MONITORS);
    memset(&info, 0, sizeof(info));
    SCREEN_CHECK(platform_get_monitor_info(platform, PLATFORM_MAX_MONITORS - 1u, &info));
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, PLATFORM_MAX_MONITORS, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));

    g_native_display_count = SCREEN_FAKE_NATIVE_LIMIT + 1;
    list_calls = g_display_list_calls;
    SCREEN_CHECK(platform_get_monitor_count(platform) == 0u);
    SCREEN_CHECK(g_display_list_calls == list_calls);
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));
    SCREEN_CHECK(g_display_list_calls == list_calls);

    g_native_display_count = INT_MAX;
    SCREEN_CHECK(platform_get_monitor_count(platform) == 0u);
    g_native_display_count = -1;
    SCREEN_CHECK(platform_get_monitor_count(platform) == 0u);
    g_native_display_count = 0;
    SCREEN_CHECK(platform_get_monitor_count(platform) == 0u);
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));

    g_native_display_count = 1;
    g_display_refs[0] = NULL;
    SCREEN_CHECK(platform_get_monitor_count(platform) == 0u);
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));
    platform_destroy(platform);
}

TEST(screen_monitor_errors_fail_closed)
{
    Platform *platform;
    MonitorInfo info;

    screen_fake_reset();
    platform = screen_fake_create();
    SCREEN_CHECK(platform != NULL);
    if (platform == NULL) return;

    g_context_failure_property = SCREEN_PROPERTY_DISPLAY_COUNT;
    SCREEN_CHECK(platform_get_monitor_count(platform) == 0u);
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));

    g_context_failure_property = SCREEN_PROPERTY_DISPLAYS;
    SCREEN_CHECK(platform_get_monitor_count(platform) == 0u);
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));

    g_context_failure_property = -1;
    g_displays[0].failure_property = SCREEN_PROPERTY_SIZE;
    SCREEN_CHECK(platform_get_monitor_count(platform) == 1u);
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));

    g_displays[0].failure_property = -1;
    g_displays[0].size[0] = 0;
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));

    g_displays[0].size[0] = 1280;
    g_displays[0].failure_property = SCREEN_PROPERTY_POSITION;
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));
    platform_destroy(platform);
}

#if defined(SCREEN_TEST_WRAP_CALLOC)
TEST(screen_monitor_allocation_failure_fails_closed)
{
    Platform *platform;
    MonitorInfo info;

    screen_fake_reset();
    platform = screen_fake_create();
    SCREEN_CHECK(platform != NULL);
    if (platform == NULL) return;

    g_fail_calloc = true;
    g_calloc_calls = 0u;
    SCREEN_CHECK(platform_get_monitor_count(platform) == 0u);
    memset(&info, 0xa5, sizeof(info));
    SCREEN_CHECK(!platform_get_monitor_info(platform, 0u, &info));
    SCREEN_CHECK(screen_monitor_is_zero(&info));
    SCREEN_CHECK(g_calloc_calls > 0u);
    g_fail_calloc = false;
    platform_destroy(platform);
}
#endif

TEST_MAIN_BEGIN()
    RUN_TEST(screen_window_is_fixed_borderless_fullscreen);
    RUN_TEST(screen_start_fullscreen_is_the_same_fixed_mode);
    RUN_TEST(screen_window_mode_null_safety);
    RUN_TEST(screen_manager_close_filters_source_and_subtype);
    RUN_TEST(screen_monitor_enumerates_native_display_metadata);
    RUN_TEST(screen_monitor_dpi_uses_physical_size_then_logical_fallback);
    RUN_TEST(screen_monitor_extreme_metadata_does_not_overflow);
    RUN_TEST(screen_monitor_optional_metadata_degrades_explicitly);
    RUN_TEST(screen_monitor_primary_associates_default_with_first_display);
    RUN_TEST(screen_monitor_bounds_native_count_and_rejects_overflow);
    RUN_TEST(screen_monitor_errors_fail_closed);
#if defined(SCREEN_TEST_WRAP_CALLOC)
    RUN_TEST(screen_monitor_allocation_failure_fails_closed);
#endif
TEST_MAIN_END()
