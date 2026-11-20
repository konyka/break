#include "test_framework.h"

#include "engine.h"
#include <math.h>

#if defined(ENGINE_TEST_TIME_WRAPPERS)
static u64 scripted_now_us;

u64 __wrap_time_microseconds(void)
{
    return scripted_now_us;
}

PlatformEventResult __wrap_platform_poll(Platform *platform)
{
    (void)platform;
    return PLATFORM_EVENT_NONE;
}

InputState *__wrap_platform_input(Platform *platform)
{
    static InputState input;
    (void)platform;
    return &input;
}
#endif

TEST(invalid_initialization_leaves_a_safe_engine_state)
{
    Engine engine = {0};
    const EngineConfig config = {640, 480, NULL, 60.0, false, false, false, NULL, NULL, 0.0f, NULL};

    ASSERT_FALSE(engine_init(&engine, &config));
    ASSERT_EQ(engine.platform, NULL);
    ASSERT_FALSE(engine_frame(&engine));
    engine_shutdown(&engine);
    engine_shutdown(&engine);
}

TEST(null_engine_arguments_are_rejected)
{
    const EngineConfig config = {640, 480, "Break", 60.0, false, false, false, NULL, NULL, 0.0f, NULL};

    ASSERT_FALSE(engine_init(NULL, &config));
    ASSERT_FALSE(engine_frame(NULL));
    engine_shutdown(NULL);
}

TEST(reinitialization_with_an_active_platform_is_rejected)
{
    Engine engine = {0};
    const EngineConfig config = {640, 480, "Break", 60.0, false, false, false, NULL, NULL, 0.0f, NULL};

    engine.platform = (Platform *)(uintptr_t)1;
    ASSERT_FALSE(engine_init(&engine, &config));
    ASSERT_EQ(engine.platform, (Platform *)(uintptr_t)1);
    engine.platform = NULL;
}

TEST(invalid_target_fps_is_rejected)
{
    const EngineConfig negative = {640, 480, "Break", -1.0, false, false, false, NULL, NULL, 0.0f, NULL};
    const EngineConfig nan_value = {640, 480, "Break", NAN, false, false, false, NULL, NULL, 0.0f, NULL};
    const EngineConfig infinite = {640, 480, "Break", INFINITY, false, false, false, NULL, NULL, 0.0f, NULL};
    Engine engine = {0};

    ASSERT_FALSE(engine_init(&engine, &negative));
    ASSERT_FALSE(engine_init(&engine, &nan_value));
    ASSERT_FALSE(engine_init(&engine, &infinite));
    ASSERT_EQ(engine.platform, NULL);
}

#if defined(ENGINE_TEST_TIME_WRAPPERS)
TEST(frame_metrics_use_raw_time_while_simulation_delta_is_clamped)
{
    Engine engine = {0};
    int frame;
    engine.platform = (Platform *)(uintptr_t)1;
    engine.last_frame_us = 1000000u;
    scripted_now_us = 3000000u;

    for (frame = 0; frame < 5; ++frame) {
        ASSERT_TRUE(engine_frame(&engine));
        ASSERT_FLOAT_EQ(engine.delta_time, 0.1, 0.0);
        ASSERT_FLOAT_EQ(engine.raw_delta_time, 2.0, 0.0);
        scripted_now_us += 2000000u;
    }
    ASSERT_FLOAT_EQ(engine.fps, 0.5, 0.0);
    ASSERT_EQ(engine.frame_count, 5u);
}
#endif

TEST_MAIN_BEGIN()
    RUN_TEST(invalid_initialization_leaves_a_safe_engine_state);
    RUN_TEST(null_engine_arguments_are_rejected);
    RUN_TEST(reinitialization_with_an_active_platform_is_rejected);
    RUN_TEST(invalid_target_fps_is_rejected);
#if defined(ENGINE_TEST_TIME_WRAPPERS)
    RUN_TEST(frame_metrics_use_raw_time_while_simulation_delta_is_clamped);
#endif
TEST_MAIN_END()
