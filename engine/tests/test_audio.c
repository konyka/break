/* ==========================================================================
 *  test_audio.c — 3D distance attenuation model (headless).
 *
 *  Exercises the pure inverse-distance gain function used by the streaming
 *  audio system for spatialization. The actual playback path needs an audio
 *  device + miniaudio and is validated by the demo build, not here.
 * ========================================================================== */

#include "test_framework.h"
#include <audio/audio.h>

TEST(atten_inside_min_is_full)
{
    /* At or below min distance the sound plays at full gain. */
    ASSERT_FLOAT_EQ(audio_attenuation_gain(0.0f, 1.0f, 100.0f, 1.0f), 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(audio_attenuation_gain(1.0f, 1.0f, 100.0f, 1.0f), 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(audio_attenuation_gain(0.5f, 1.0f, 100.0f, 1.0f), 1.0f, 1e-5);
}

TEST(atten_inverse_known_values)
{
    /* g = min / (min + rolloff*(d-min)) */
    ASSERT_FLOAT_EQ(audio_attenuation_gain(2.0f, 1.0f, 100.0f, 1.0f), 0.5f, 1e-5);
    ASSERT_FLOAT_EQ(audio_attenuation_gain(3.0f, 1.0f, 100.0f, 1.0f), 1.0f / 3.0f, 1e-5);
    /* higher rolloff drops faster: d=2,rolloff=2 -> 1/(1+2)=1/3 */
    ASSERT_FLOAT_EQ(audio_attenuation_gain(2.0f, 1.0f, 100.0f, 2.0f), 1.0f / 3.0f, 1e-5);
}

TEST(atten_monotonic_decreasing)
{
    f32 prev = 2.0f;
    for (f32 d = 1.0f; d <= 40.0f; d += 1.0f) {
        f32 g = audio_attenuation_gain(d, 2.0f, 40.0f, 1.0f);
        ASSERT_TRUE(g <= prev + 1e-6f);
        ASSERT_TRUE(g >= 0.0f && g <= 1.0f);
        prev = g;
    }
}

TEST(atten_clamped_beyond_max)
{
    /* Past max distance the gain is clamped to the value at max distance. */
    f32 at_max = audio_attenuation_gain(40.0f, 2.0f, 40.0f, 1.0f);
    f32 far    = audio_attenuation_gain(1000.0f, 2.0f, 40.0f, 1.0f);
    ASSERT_FLOAT_EQ(at_max, far, 1e-5);
}

TEST(atten_zero_rolloff_is_full)
{
    /* No rolloff => no attenuation regardless of distance (within max). */
    ASSERT_FLOAT_EQ(audio_attenuation_gain(50.0f, 1.0f, 100.0f, 0.0f), 1.0f, 1e-5);
}

TEST_MAIN_BEGIN()
    RUN_TEST(atten_inside_min_is_full);
    RUN_TEST(atten_inverse_known_values);
    RUN_TEST(atten_monotonic_decreasing);
    RUN_TEST(atten_clamped_beyond_max);
    RUN_TEST(atten_zero_rolloff_is_full);
TEST_MAIN_END()
