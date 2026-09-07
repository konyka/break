#include "test_framework.h"

#include "engine.h"
#include <math.h>

TEST(invalid_initialization_leaves_a_safe_engine_state)
{
    Engine engine = {0};
    const EngineConfig config = {640, 480, NULL, 60.0};

    ASSERT_FALSE(engine_init(&engine, &config));
    ASSERT_EQ(engine.platform, NULL);
    ASSERT_FALSE(engine_frame(&engine));
    engine_shutdown(&engine);
    engine_shutdown(&engine);
}

TEST(null_engine_arguments_are_rejected)
{
    const EngineConfig config = {640, 480, "Break", 60.0};

    ASSERT_FALSE(engine_init(NULL, &config));
    ASSERT_FALSE(engine_frame(NULL));
    engine_shutdown(NULL);
}

TEST(reinitialization_with_an_active_platform_is_rejected)
{
    Engine engine = {0};
    const EngineConfig config = {640, 480, "Break", 60.0};

    engine.platform = (Platform *)(uintptr_t)1;
    ASSERT_FALSE(engine_init(&engine, &config));
    ASSERT_EQ(engine.platform, (Platform *)(uintptr_t)1);
    engine.platform = NULL;
}

TEST(invalid_target_fps_is_rejected)
{
    const EngineConfig negative = {640, 480, "Break", -1.0};
    const EngineConfig nan_value = {640, 480, "Break", NAN};
    const EngineConfig infinite = {640, 480, "Break", INFINITY};
    Engine engine = {0};

    ASSERT_FALSE(engine_init(&engine, &negative));
    ASSERT_FALSE(engine_init(&engine, &nan_value));
    ASSERT_FALSE(engine_init(&engine, &infinite));
    ASSERT_EQ(engine.platform, NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(invalid_initialization_leaves_a_safe_engine_state);
    RUN_TEST(null_engine_arguments_are_rejected);
    RUN_TEST(reinitialization_with_an_active_platform_is_rejected);
    RUN_TEST(invalid_target_fps_is_rejected);
TEST_MAIN_END()
