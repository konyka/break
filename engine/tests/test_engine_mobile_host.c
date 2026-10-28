#include "test_framework.h"

#include "engine.h"
#include <platform/time.h>

static u64 test_clock_us = 1000u;

void time_init(void) {}
u64 time_microseconds(void) { test_clock_us += 16000u; return test_clock_us; }
void time_sleep_us(u64 microseconds) { (void)microseconds; }

typedef struct {
    u32 calls;
    Engine *last_engine;
    bool resize_result;
} HostProbe;

static bool host_poll(void *context, Engine *engine)
{
    HostProbe *probe = context;
    probe->calls++;
    probe->last_engine = engine;
    if (probe->calls == 1u)
        input_set_key(platform_input(engine->platform), INPUT_MOUSE_LEFT, true);
    return probe->calls < 2u;
}

static bool host_resize(void *context, Engine *engine)
{
    HostProbe *probe = context;
    probe->calls++;
    probe->resize_result = platform_mobile_resize(engine->platform,
                                                  400, 300, 800, 600, 2.0f);
    return false;
}

static bool host_suspend_resume(void *context, Engine *engine)
{
    HostProbe *probe = context;
    probe->calls++;
    if (probe->calls == 1u) platform_mobile_notify_suspend(engine->platform);
    else platform_mobile_notify_resume(engine->platform);
    return probe->calls < 2u;
}

TEST(host_receives_native_handles_and_polls_after_input_reset)
{
    int window, display;
    HostProbe probe = {0};
    EngineHost host = { &probe, host_poll };
    const EngineConfig config = {
        .width = 320, .height = 240, .title = "iOS host", .target_fps = 0.0,
        .native_window = &window, .native_display = &display, .host = &host,
    };
    Engine engine = {0};

    ASSERT_TRUE(engine_init(&engine, &config));
    ASSERT_EQ(engine.host, &host);
    ASSERT_EQ(platform_window_native(engine.platform), &window);
    ASSERT_EQ(platform_display_native(engine.platform), &display);
    ASSERT_EQ(probe.calls, 0u);
    ASSERT_TRUE(engine_frame(&engine));
    ASSERT_EQ(probe.calls, 1u);
    ASSERT_EQ(probe.last_engine, &engine);
    ASSERT_EQ(engine.frame_count, 1u);
    ASSERT_TRUE(input_key_pressed(platform_input(engine.platform), INPUT_MOUSE_LEFT));
    ASSERT_FALSE(engine_frame(&engine));
    ASSERT_EQ(probe.calls, 2u);
    ASSERT_EQ(engine.frame_count, 1u);
    ASSERT_EQ(platform_input(engine.platform)->frame_number, 2u);
    engine_shutdown(&engine);
    ASSERT_EQ(engine.host, NULL);
    ASSERT_EQ(engine.platform, NULL);
}

TEST(host_can_resize_mobile_drawable_before_rendering)
{
    int window;
    HostProbe probe = {0};
    EngineHost host = { &probe, host_resize };
    const EngineConfig config = {
        .width = 320, .height = 240, .title = "iOS viewport",
        .native_window = &window, .host = &host,
    };
    Engine engine = {0};
    PlatformWsiSurface wsi;
    u32 width = 0u, height = 0u;

    ASSERT_TRUE(engine_init(&engine, &config));
    ASSERT_FALSE(engine_frame(&engine));
    ASSERT_TRUE(probe.resize_result);
    ASSERT_EQ(engine.frame_count, 0u);
    platform_get_logical_size(engine.platform, &width, &height);
    ASSERT_EQ(width, 400u);
    ASSERT_EQ(height, 300u);
    platform_get_drawable_size(engine.platform, &width, &height);
    ASSERT_EQ(width, 800u);
    ASSERT_EQ(height, 600u);
    ASSERT_FLOAT_EQ(platform_get_content_scale(engine.platform), 2.0f, 0.001f);
    ASSERT_TRUE(platform_wsi_surface_query(engine.platform, &wsi));
    ASSERT_EQ(wsi.state, PLATFORM_WSI_RESIZED);
    ASSERT_EQ(wsi.drawable_width, 800u);
    ASSERT_EQ(wsi.drawable_height, 600u);
    engine_shutdown(&engine);
}

TEST(host_suspends_and_resumes_mobile_surface_on_engine_thread)
{
    int window;
    HostProbe probe = {0};
    EngineHost host = { &probe, host_suspend_resume };
    const EngineConfig config = {
        .width = 320, .height = 240, .title = "iOS lifecycle",
        .native_window = &window, .host = &host,
    };
    Engine engine = {0};
    PlatformWsiSurface wsi;

    ASSERT_TRUE(engine_init(&engine, &config));
    ASSERT_TRUE(engine_frame(&engine));
    ASSERT_TRUE(platform_wsi_surface_query(engine.platform, &wsi));
    ASSERT_EQ(wsi.state, PLATFORM_WSI_SUSPENDED);
    ASSERT_FALSE(platform_wsi_frame_allowed(&wsi));
    ASSERT_FALSE(engine_frame(&engine));
    ASSERT_TRUE(platform_wsi_surface_query(engine.platform, &wsi));
    ASSERT_EQ(wsi.state, PLATFORM_WSI_CREATED);
    ASSERT_TRUE(platform_wsi_frame_allowed(&wsi));
    engine_shutdown(&engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(host_receives_native_handles_and_polls_after_input_reset);
    RUN_TEST(host_can_resize_mobile_drawable_before_rendering);
    RUN_TEST(host_suspends_and_resumes_mobile_surface_on_engine_thread);
TEST_MAIN_END()
