#include "test_framework.h"
#include <renderer/time_of_day.h>
#include <math.h>

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

/* At dawn and dusk the sun is on the horizon: east before noon (-X),
 * west after (+X), with no direct light yet; light rises with height. */
TEST(time_of_day_sun_path_and_brightness) {
    TimeOfDayLighting dawn, morning, noon, dusk;
    time_of_day_eval(2.5f, 10.0f, &dawn);
    time_of_day_eval(3.75f, 10.0f, &morning);
    time_of_day_eval(5.0f, 10.0f, &noon);
    time_of_day_eval(7.5f, 10.0f, &dusk);
    ASSERT_FLOAT_EQ(dawn.sun_dir.e[1], 0.0f, 1e-5);
    ASSERT_FLOAT_EQ(dawn.sun_dir.e[0], -1.0f, 1e-5);
    ASSERT_FLOAT_EQ(dusk.sun_dir.e[0], 1.0f, 1e-5);
    ASSERT_TRUE(morning.sun_dir.e[0] < 0.0f && morning.sun_dir.e[1] > 0.0f);
    ASSERT_TRUE(morning.sun_color.e[0] > 0.0f && morning.sun_color.e[0] < noon.sun_color.e[0]);
    ASSERT_FLOAT_EQ(noon.sun_color.e[0], 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(noon.fog, 0.2f, 1e-5);
    ASSERT_TRUE(morning.fog > noon.fog && morning.fog < 0.35f);
    ASSERT_FLOAT_EQ(len3(noon.sun_dir), 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(noon.sun_dir.e[2], 0.0f, 0.0f);
}

/* Negative and large times land on the same point of the day (the phase
 * is periodic, so this holds whether or not the time is wrapped first);
 * non-finite times and non-positive day lengths fall back to safe values;
 * NULL is ignored. */
TEST(time_of_day_wraps_and_guards_inputs) {
    TimeOfDayLighting a, b;
    time_of_day_eval(-2.5f, 10.0f, &a);
    time_of_day_eval(7.5f, 10.0f, &b);
    ASSERT_FLOAT_EQ(a.sun_dir.e[0], b.sun_dir.e[0], 1e-5);
    time_of_day_eval(1003.75f, 10.0f, &a);
    time_of_day_eval(3.75f, 10.0f, &b);
    ASSERT_FLOAT_EQ(a.sun_dir.e[1], b.sun_dir.e[1], 1e-3);
    time_of_day_eval(NAN, 10.0f, &a);
    time_of_day_eval(0.0f, 10.0f, &b);
    ASSERT_FLOAT_EQ(a.sun_dir.e[1], b.sun_dir.e[1], 0.0f);
    time_of_day_eval(0.5f, 0.0f, &a);
    time_of_day_eval(0.5f, 1.0f, &b);
    ASSERT_FLOAT_EQ(a.sun_dir.e[1], b.sun_dir.e[1], 0.0f);
    time_of_day_eval(0.5f, -4.0f, &a);
    ASSERT_FLOAT_EQ(a.sun_dir.e[1], b.sun_dir.e[1], 0.0f);
    time_of_day_eval(1.0f, 10.0f, NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(time_of_day_noon_and_midnight);
    RUN_TEST(time_of_day_sun_path_and_brightness);
    RUN_TEST(time_of_day_wraps_and_guards_inputs);
TEST_MAIN_END()
