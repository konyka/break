#include "test_framework.h"
#include <platform/input_extended.h>
#include <windows.h>
#include <xinput.h>

static DWORD fake_set_result;
static XINPUT_VIBRATION fake_vibration;
static u32 fake_set_calls;

static DWORD WINAPI fake_set_state(DWORD pad, XINPUT_VIBRATION *vibration)
{
    (void)pad;
    fake_set_calls++;
    fake_vibration = *vibration;
    return fake_set_result;
}

#include "../src/platform/gamepad_win.c"

#ifdef GAMEPAD_WIN_PORTABLE_TEST
static u64 fake_now_us;
u64 time_microseconds(void) { return fake_now_us; }
#endif

static void reset_fake(void)
{
#ifdef GAMEPAD_WIN_PORTABLE_TEST
    fake_now_us = 1000000u;
#endif
    memset(&g_pad, 0, sizeof(g_pad));
    g_pad.initialized = true;
    g_pad.set_state = fake_set_state;
    g_pad.connected[0] = true;
    g_pad.feedback_available[0] = true;
    g_pad.connection_serial[0] = 1;
    fake_set_result = ERROR_SUCCESS;
    fake_set_calls = 0;
    memset(&fake_vibration, 0, sizeof(fake_vibration));
}

TEST(xinput_fake_receives_bounded_motor_values)
{
    InputExtended input;
    u64 id;
    reset_fake();
    input_extended_init(&input);
    gamepad_feedback_poll(&input);
    ASSERT_EQ(input_extended_request_haptic(&input, 0, 0.25f, 0.75f, 200, &id),
              INPUT_EXT_OK);
    gamepad_feedback_poll(&input);
    ASSERT_EQ(fake_set_calls, 1u);
    ASSERT_EQ(fake_vibration.wLeftMotorSpeed, 16384);
    ASSERT_EQ(fake_vibration.wRightMotorSpeed, 49151);
    ASSERT_EQ(input_extended_haptic_result(&input, id), INPUT_EXT_OK);
}

TEST(xinput_no_feedback_and_disconnect_degrade_without_retry_storm)
{
    InputExtended input;
    u64 id;
    reset_fake();
    g_pad.feedback_available[0] = false;
    input_extended_init(&input);
    gamepad_feedback_poll(&input);
    ASSERT_EQ(input_extended_request_haptic(&input, 0, 0.5f, 0.5f, 100, &id),
              INPUT_EXT_UNSUPPORTED);
    ASSERT_EQ(fake_set_calls, 0u);

    g_pad.feedback_available[0] = true;
    gamepad_feedback_poll(&input);
    ASSERT_EQ(input_extended_request_haptic(&input, 0, 0.5f, 0.5f, 100, &id),
              INPUT_EXT_OK);
    fake_set_result = ERROR_DEVICE_NOT_CONNECTED;
    gamepad_feedback_poll(&input);
    ASSERT_EQ(fake_set_calls, 1u);
    ASSERT_EQ(input_extended_haptic_result(&input, id), INPUT_EXT_DISCONNECTED);
    ASSERT_FALSE(g_pad.connected[0]);
    ASSERT_EQ(input_extended_request_haptic(&input, 0, 0.5f, 0.5f, 100, &id),
              INPUT_EXT_DISCONNECTED);
    ASSERT_EQ(input_extended_request_haptic(&input, 0, 0.5f, 0.5f, 100, NULL),
              INPUT_EXT_INVALID);
}

TEST(xinput_zero_duration_stops_motors)
{
    InputExtended input;
    u64 id;
    reset_fake();
    input_extended_init(&input);
    gamepad_feedback_poll(&input);
    ASSERT_EQ(input_extended_request_haptic(&input, 0, 0, 0, 0, &id), INPUT_EXT_OK);
    gamepad_feedback_poll(&input);
    ASSERT_EQ(fake_set_calls, 1u);
    ASSERT_EQ(fake_vibration.wLeftMotorSpeed, 0);
    ASSERT_EQ(fake_vibration.wRightMotorSpeed, 0);
    ASSERT_EQ(input_extended_haptic_result(&input, id), INPUT_EXT_OK);
}

TEST(xinput_duration_expiry_stops_motors_on_poll_thread)
{
    InputExtended input;
    u64 id;
    u64 deadline;
    reset_fake();
    input_extended_init(&input);
    gamepad_feedback_poll(&input);
    ASSERT_EQ(input_extended_request_haptic(&input, 0, 0.5f, 0.25f,
                                            INPUT_HAPTIC_MAX_DURATION_MS, &id),
              INPUT_EXT_OK);
    gamepad_feedback_poll(&input);
    ASSERT_EQ(fake_set_calls, 1u);
    ASSERT_TRUE(g_pad.vibration_active[0]);
    deadline = g_pad.stop_deadline_us[0];
    win_haptic_tick(deadline - 1u);
    ASSERT_EQ(fake_set_calls, 1u);
    win_haptic_tick(deadline);
    ASSERT_EQ(fake_set_calls, 2u);
    ASSERT_EQ(fake_vibration.wLeftMotorSpeed, 0);
    ASSERT_EQ(fake_vibration.wRightMotorSpeed, 0);
    ASSERT_FALSE(g_pad.vibration_active[0]);
    ASSERT_EQ(input_extended_haptic_result(&input, id), INPUT_EXT_OK);
}

int main(void)
{
    printf("=== Running Tests ===\n");
    RUN_TEST(xinput_fake_receives_bounded_motor_values);
    RUN_TEST(xinput_no_feedback_and_disconnect_degrade_without_retry_storm);
    RUN_TEST(xinput_zero_duration_stops_motors);
    RUN_TEST(xinput_duration_expiry_stops_motors_on_poll_thread);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
