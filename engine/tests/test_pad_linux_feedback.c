#include "test_framework.h"
#include <platform/input_extended.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

static int fake_ioctl_calls;
static int fake_ioctl_result;
static int fake_ioctl_error;
static struct ff_effect fake_effect;
static int fake_write_calls;
static ssize_t fake_write_result;
static int fake_write_error;
static struct input_event fake_event;

static int fake_ioctl(int fd, unsigned long request, ...)
{
    va_list args;
    void *argument;
    (void)fd;
    fake_ioctl_calls++;
    va_start(args, request);
    argument = va_arg(args, void *);
    va_end(args);
    if (fake_ioctl_result != 0) {
        errno = fake_ioctl_error;
        return fake_ioctl_result;
    }
    if (request == EVIOCSFF) {
        ((struct ff_effect *)argument)->id = 42;
        fake_effect = *(const struct ff_effect *)argument;
    }
    return 0;
}

static ssize_t fake_write(int fd, const void *data, size_t size)
{
    (void)fd;
    fake_write_calls++;
    if (fake_write_result != -100) {
        if (fake_write_result < 0) errno = fake_write_error;
        return fake_write_result;
    }
    if (size == sizeof(fake_event)) memcpy(&fake_event, data, size);
    return (ssize_t)size;
}

#define ioctl fake_ioctl
#define write fake_write
#include "../src/platform/pad_linux.c"
#undef write
#undef ioctl

static void reset_fakes(void)
{
    fake_ioctl_calls = 0;
    fake_ioctl_result = 0;
    fake_ioctl_error = 0;
    memset(&fake_effect, 0, sizeof(fake_effect));
    fake_write_calls = 0;
    fake_write_result = -100;
    fake_write_error = 0;
    memset(&fake_event, 0, sizeof(fake_event));
}

static PadDevice feedback_device(void)
{
    PadDevice device;
    memset(&device, 0, sizeof(device));
    device.fd = 7;
    device.connected = true;
    device.feedback_available = true;
    device.effect_id = -1;
    return device;
}

static InputHapticCommand haptic_command(f32 low, f32 high, u32 duration)
{
    InputHapticCommand command;
    memset(&command, 0, sizeof(command));
    command.request_id = 1;
    command.generation = 1;
    command.low = low;
    command.high = high;
    command.duration_ms = duration;
    return command;
}

TEST(evdev_uploads_rumble_and_stops_reused_effect)
{
    PadDevice device = feedback_device();
    InputHapticCommand command = haptic_command(0.25f, 0.75f, 250);
    reset_fakes();
    ASSERT_EQ(linux_device_haptic(&device, &command), INPUT_EXT_OK);
    ASSERT_EQ(fake_ioctl_calls, 1);
    ASSERT_EQ(fake_effect.type, FF_RUMBLE);
    ASSERT_EQ(fake_effect.id, 42);
    ASSERT_EQ(fake_effect.replay.length, 250);
    ASSERT_EQ(fake_effect.u.rumble.strong_magnitude, 16384);
    ASSERT_EQ(fake_effect.u.rumble.weak_magnitude, 49151);
    ASSERT_EQ(device.effect_id, 42);
    ASSERT_EQ(fake_write_calls, 1);
    ASSERT_EQ(fake_event.type, EV_FF);
    ASSERT_EQ(fake_event.code, 42);
    ASSERT_EQ(fake_event.value, 1);

    command = haptic_command(0.0f, 0.0f, 0);
    ASSERT_EQ(linux_device_haptic(&device, &command), INPUT_EXT_OK);
    ASSERT_EQ(fake_ioctl_calls, 1);
    ASSERT_EQ(fake_write_calls, 2);
    ASSERT_EQ(fake_event.value, 0);
}

TEST(evdev_disconnected_and_no_feedback_do_not_touch_os)
{
    PadDevice device = feedback_device();
    InputHapticCommand command = haptic_command(0.5f, 0.5f, 100);
    reset_fakes();
    device.connected = false;
    ASSERT_EQ(linux_device_haptic(&device, &command), INPUT_EXT_DISCONNECTED);
    device = feedback_device();
    device.feedback_available = false;
    ASSERT_EQ(linux_device_haptic(&device, &command), INPUT_EXT_UNSUPPORTED);
    ASSERT_EQ(fake_ioctl_calls, 0);
    ASSERT_EQ(fake_write_calls, 0);
}

TEST(evdev_upload_and_write_failures_preserve_error_meaning)
{
    PadDevice device = feedback_device();
    InputHapticCommand command = haptic_command(0.5f, 0.5f, 100);
    reset_fakes();
    fake_ioctl_result = -1;
    fake_ioctl_error = ENODEV;
    ASSERT_EQ(linux_device_haptic(&device, &command), INPUT_EXT_DISCONNECTED);
    fake_ioctl_error = EIO;
    ASSERT_EQ(linux_device_haptic(&device, &command), INPUT_EXT_FAILED);

    reset_fakes();
    fake_write_result = -2;
    ASSERT_EQ(linux_device_haptic(&device, &command), INPUT_EXT_FAILED);
    fake_write_result = -1;
    fake_write_error = ENODEV;
    ASSERT_EQ(linux_device_haptic(&device, &command), INPUT_EXT_DISCONNECTED);
}

int main(void)
{
    printf("=== Running Tests ===\n");
    RUN_TEST(evdev_uploads_rumble_and_stops_reused_effect);
    RUN_TEST(evdev_disconnected_and_no_feedback_do_not_touch_os);
    RUN_TEST(evdev_upload_and_write_failures_preserve_error_meaning);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
