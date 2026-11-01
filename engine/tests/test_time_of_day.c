#include "test_framework.h"
#include <renderer/time_of_day.h>

static f32 len3(Vec3 v) {
    return sqrtf(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

TEST(time_of_day_noon_and_midnight) {
    TimeOfDayLighting a, b, noon, midnight;
    time_of_day_eval(0.0f, 10.0f, &a);
    time_of_day_eval(10.0f, 10.0f, &b);
    ASSERT_FLOAT_EQ(a.sun_dir.e[0], b.sun_dir.e[0], 1e-5);
    ASSERT_FLOAT_EQ(a.sun_dir.e[1], b.sun_dir.e[1], 1e-5);
    ASSERT_FLOAT_EQ(a.sun_color.e[0], b.sun_color.e[0], 1e-5);

    time_of_day_eval(5.0f, 10.0f, &noon);
    ASSERT_TRUE(noon.sun_dir.e[1] > 0.9f);
    time_of_day_eval(0.0f, 10.0f, &midnight);
    ASSERT_TRUE(len3(midnight.sun_color) == 0.0f);
    ASSERT_FLOAT_EQ(midnight.ambient.e[0], 0.03f, 1e-5);
    ASSERT_FLOAT_EQ(midnight.ambient.e[1], 0.03f, 1e-5);
    ASSERT_FLOAT_EQ(midnight.ambient.e[2], 0.05f, 1e-5);
    ASSERT_TRUE(isfinite(noon.sun_dir.e[0]) && isfinite(noon.fog));
    ASSERT_TRUE(isfinite(midnight.sun_dir.e[1]) && isfinite(midnight.fog));
}

TEST_MAIN_BEGIN()
    RUN_TEST(time_of_day_noon_and_midnight);
TEST_MAIN_END()
