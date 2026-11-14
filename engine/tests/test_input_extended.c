#include "test_framework.h"
#include <platform/input_extended.h>
#include <core/platform_thread.h>
#include <stdatomic.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

static void touch(InputExtended *s, InputTouchPhase phase, i64 source,
                  f32 x, f32 y, u64 time, InputTouchId *id)
{
    ASSERT_EQ(input_extended_touch(s, phase, source, x, y, time, id),
              INPUT_EXT_OK);
}

TEST(init_has_version_and_empty_bounded_state)
{
    InputExtended s;
    memset(&s, 0xFF, sizeof(s));
    input_extended_init(&s);
    ASSERT_EQ(s.abi_version, INPUT_EXTENDED_ABI_VERSION);
    ASSERT_EQ(s.struct_size, (u32)sizeof(s));
    ASSERT_EQ(s.touch_count, 0u);
    ASSERT_EQ(s.touch_event_count, 0u);
    ASSERT_EQ(s.gesture_count, 0u);
    ASSERT_EQ(s.dropped_touch_events, (u64)0);
    ASSERT_EQ(s.dropped_gestures, (u64)0);
}

TEST(press_move_release_and_frame_transitions)
{
    InputExtended s;
    InputTouchId id;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 11, 0.25f, 0.75f, 100, &id);
    ASSERT_NEQ(id, (InputTouchId)0);
    ASSERT_EQ(s.touch_count, 1u);
    ASSERT_EQ(s.touches[0].phase, INPUT_TOUCH_PRESS);
    ASSERT_EQ(s.touches[0].source_id, 11);
    ASSERT_FLOAT_EQ(s.touches[0].x, 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(s.touches[0].y, 0.75f, 1e-6f);

    input_extended_new_frame(&s);
    ASSERT_EQ(s.touches[0].phase, INPUT_TOUCH_HELD);
    ASSERT_EQ(s.touch_event_count, 0u);
    touch(&s, INPUT_TOUCH_MOVE, 11, 0.5f, 0.5f, 110, NULL);
    ASSERT_EQ(s.touches[0].id, id);
    ASSERT_EQ(s.touches[0].phase, INPUT_TOUCH_MOVE);
    ASSERT_FLOAT_EQ(s.touches[0].x, 0.5f, 1e-6f);
    touch(&s, INPUT_TOUCH_RELEASE, 11, 0.5f, 0.5f, 120, NULL);
    ASSERT_EQ(s.touch_count, 0u);
    ASSERT_EQ(s.touch_event_count, 2u);
    ASSERT_EQ(s.touch_events[0].phase, INPUT_TOUCH_MOVE);
    ASSERT_EQ(s.touch_events[1].phase, INPUT_TOUCH_RELEASE);
    ASSERT_EQ(s.touch_events[1].id, id);
}

TEST(same_frame_source_reuse_changes_generation_and_keeps_old_release)
{
    InputExtended s;
    InputTouchId first, second;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 7, 0.2f, 0.3f, 10, &first);
    touch(&s, INPUT_TOUCH_RELEASE, 7, 0.2f, 0.3f, 20, NULL);
    touch(&s, INPUT_TOUCH_PRESS, 7, 0.4f, 0.5f, 30, &second);
    ASSERT_NEQ(first, second);
    ASSERT_EQ(s.touch_count, 1u);
    ASSERT_EQ(s.touch_event_count, 3u);
    ASSERT_EQ(s.touch_events[1].id, first);
    ASSERT_EQ(s.touch_events[1].phase, INPUT_TOUCH_RELEASE);
    ASSERT_EQ(s.touch_events[2].id, second);
    ASSERT_EQ(s.touches[0].id, second);
}

TEST(cancel_deactivates_without_completion_gesture)
{
    InputExtended s;
    InputTouchId first, second;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 3, 0.1f, 0.1f, 0, &first);
    touch(&s, INPUT_TOUCH_CANCEL, 3, 0.1f, 0.1f, 100, NULL);
    ASSERT_EQ(s.touch_count, 0u);
    ASSERT_EQ(s.gesture_count, 0u);
    ASSERT_EQ(s.touch_events[1].phase, INPUT_TOUCH_CANCEL);
    touch(&s, INPUT_TOUCH_PRESS, 3, 0.1f, 0.1f, 110, &second);
    ASSERT_NEQ(first, second);
}

TEST(cancel_all_ends_every_active_touch)
{
    InputExtended s;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 1, 0.1f, 0.1f, 0, NULL);
    touch(&s, INPUT_TOUCH_PRESS, 2, 0.2f, 0.2f, 1, NULL);
    touch(&s, INPUT_TOUCH_PRESS, 3, 0.3f, 0.3f, 2, NULL);
    ASSERT_EQ(input_extended_cancel_all(&s, 50), INPUT_EXT_OK);
    ASSERT_EQ(s.touch_count, 0u);
    ASSERT_EQ(s.touch_event_count, 6u);
    ASSERT_EQ(s.touch_events[3].phase, INPUT_TOUCH_CANCEL);
    ASSERT_EQ(s.touch_events[4].phase, INPUT_TOUCH_CANCEL);
    ASSERT_EQ(s.touch_events[5].phase, INPUT_TOUCH_CANCEL);
    ASSERT_EQ(s.gesture_count, 0u);
}

TEST(invalid_normalized_and_pixel_coordinates_are_transactional)
{
    InputExtended s;
    InputTouchId id = 99;
    input_extended_init(&s);
    ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_PRESS, 1, -0.01f, 0.5f, 0, &id),
              INPUT_EXT_INVALID);
    ASSERT_EQ(id, (InputTouchId)0);
    ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_PRESS, 1, 0.5f, 1.01f, 0, NULL),
              INPUT_EXT_INVALID);
    ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_PRESS, 1, NAN, 0.5f, 0, NULL),
              INPUT_EXT_INVALID);
    ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_PRESS, 1, 0.5f, INFINITY, 0, NULL),
              INPUT_EXT_INVALID);
    ASSERT_EQ(input_extended_touch_pixels(&s, INPUT_TOUCH_PRESS, 1, 50, 50,
                                          0, 100, 0, NULL), INPUT_EXT_INVALID);
    ASSERT_EQ(input_extended_touch_pixels(&s, INPUT_TOUCH_PRESS, 1, 101, 50,
                                          100, 100, 0, NULL), INPUT_EXT_INVALID);
    ASSERT_EQ(s.touch_count, 0u);
    ASSERT_EQ(s.touch_event_count, 0u);
    ASSERT_EQ(s.touch_last_error, INPUT_EXT_INVALID);

    ASSERT_EQ(input_extended_touch_pixels(&s, INPUT_TOUCH_PRESS, 1, 25, 75,
                                          200, 100, 0, &id), INPUT_EXT_OK);
    ASSERT_FLOAT_EQ(s.touches[0].x, 0.125f, 1e-6f);
    ASSERT_FLOAT_EQ(s.touches[0].y, 0.75f, 1e-6f);
}

TEST(stale_and_duplicate_source_events_do_not_change_state)
{
    InputExtended s;
    InputTouchId id;
    input_extended_init(&s);
    ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_MOVE, 4, 0.2f, 0.2f, 0, NULL),
              INPUT_EXT_STALE);
    touch(&s, INPUT_TOUCH_PRESS, 4, 0.2f, 0.2f, 0, &id);
    ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_PRESS, 4, 0.3f, 0.3f, 1, NULL),
              INPUT_EXT_INVALID);
    ASSERT_EQ(s.touch_count, 1u);
    ASSERT_EQ(s.touch_event_count, 1u);
    ASSERT_EQ(s.touches[0].id, id);
    ASSERT_FLOAT_EQ(s.touches[0].x, 0.2f, 1e-6f);
}

TEST(active_capacity_is_bounded)
{
    InputExtended s;
    input_extended_init(&s);
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++)
        touch(&s, INPUT_TOUCH_PRESS, (i64)i, 0.1f, 0.1f, i, NULL);
    ASSERT_EQ(s.touch_count, INPUT_MAX_TOUCH_POINTS);
    ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_PRESS, 99, 0.2f, 0.2f, 99, NULL),
              INPUT_EXT_OVERLOAD);
    ASSERT_EQ(s.touch_count, INPUT_MAX_TOUCH_POINTS);
    ASSERT_EQ(s.touch_event_count, INPUT_MAX_TOUCH_POINTS);
    ASSERT_EQ(s.dropped_touch_events, (u64)1);
}

TEST(event_overflow_is_explicit_and_terminal_event_never_sticks)
{
    InputExtended s;
    input_extended_init(&s);
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++)
        touch(&s, INPUT_TOUCH_PRESS, (i64)i, 0.1f, 0.1f, i, NULL);
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++)
        touch(&s, INPUT_TOUCH_MOVE, (i64)i, 0.2f, 0.2f, 20 + i, NULL);
    ASSERT_EQ(s.touch_event_count, INPUT_MAX_TOUCH_EVENTS);
    ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_MOVE, 0, 0.8f, 0.8f, 90, NULL),
              INPUT_EXT_OVERLOAD);
    ASSERT_FLOAT_EQ(s.touches[0].x, 0.2f, 1e-6f);
    ASSERT_EQ(input_extended_touch_end(&s, 0, false, 91), INPUT_EXT_OVERLOAD);
    ASSERT_EQ(s.touch_count, INPUT_MAX_TOUCH_POINTS - 1u);
    ASSERT_EQ(s.dropped_touch_events, (u64)2);
}

TEST(tap_thresholds_are_deterministic)
{
    InputExtended s;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 1, 0.2f, 0.2f, 100, NULL);
    touch(&s, INPUT_TOUCH_RELEASE, 1, 0.2f, 0.2f, 400, NULL);
    ASSERT_EQ(s.gesture_count, 1u);
    ASSERT_EQ(s.gestures[0].type, INPUT_GESTURE_TAP);
    ASSERT_FLOAT_EQ(s.gestures[0].x, 0.2f, 1e-6f);

    input_extended_new_frame(&s);
    touch(&s, INPUT_TOUCH_PRESS, 2, 0.2f, 0.2f, 500, NULL);
    touch(&s, INPUT_TOUCH_RELEASE, 2, 0.2f, 0.2f, 801, NULL);
    ASSERT_EQ(s.gesture_count, 0u);
}

TEST(long_press_fires_once_and_motion_blocks_it)
{
    InputExtended s;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 1, 0.3f, 0.4f, 1000, NULL);
    input_extended_update(&s, 1499);
    ASSERT_EQ(s.gesture_count, 0u);
    input_extended_update(&s, 1500);
    ASSERT_EQ(s.gesture_count, 1u);
    ASSERT_EQ(s.gestures[0].type, INPUT_GESTURE_LONG_PRESS);
    input_extended_update(&s, 2000);
    ASSERT_EQ(s.gesture_count, 1u);

    input_extended_cancel_all(&s, 2001);
    input_extended_new_frame(&s);
    touch(&s, INPUT_TOUCH_PRESS, 2, 0.3f, 0.4f, 3000, NULL);
    touch(&s, INPUT_TOUCH_MOVE, 2, 0.35f, 0.4f, 3010, NULL);
    input_extended_update(&s, 4000);
    ASSERT_EQ(s.gesture_count, 0u);
}

TEST(swipe_reports_final_displacement)
{
    InputExtended s;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 9, 0.1f, 0.2f, 10, NULL);
    touch(&s, INPUT_TOUCH_MOVE, 9, 0.4f, 0.6f, 100, NULL);
    touch(&s, INPUT_TOUCH_RELEASE, 9, 0.4f, 0.6f, 200, NULL);
    ASSERT_EQ(s.gesture_count, 1u);
    ASSERT_EQ(s.gestures[0].type, INPUT_GESTURE_SWIPE);
    ASSERT_FLOAT_EQ(s.gestures[0].dx, 0.3f, 1e-6f);
    ASSERT_FLOAT_EQ(s.gestures[0].dy, 0.4f, 1e-6f);
}

TEST(second_touch_blocks_single_touch_gestures)
{
    InputExtended s;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 1, 0.1f, 0.1f, 0, NULL);
    touch(&s, INPUT_TOUCH_PRESS, 2, 0.8f, 0.8f, 1, NULL);
    touch(&s, INPUT_TOUCH_RELEASE, 2, 0.8f, 0.8f, 2, NULL);
    touch(&s, INPUT_TOUCH_RELEASE, 1, 0.1f, 0.1f, 3, NULL);
    ASSERT_EQ(s.gesture_count, 0u);
}

TEST(pinch_reports_scale_centroid_and_rotation)
{
    InputExtended s;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 1, 0.2f, 0.5f, 0, NULL);
    touch(&s, INPUT_TOUCH_PRESS, 2, 0.4f, 0.5f, 1, NULL);
    touch(&s, INPUT_TOUCH_MOVE, 2, 0.6f, 0.5f, 2, NULL);
    ASSERT_EQ(s.gesture_count, 1u);
    ASSERT_EQ(s.gestures[0].type, INPUT_GESTURE_PINCH);
    ASSERT_FLOAT_EQ(s.gestures[0].scale, 2.0f, 1e-5f);
    ASSERT_FLOAT_EQ(s.gestures[0].x, 0.4f, 1e-6f);
    ASSERT_FLOAT_EQ(s.gestures[0].rotation, 0.0f, 1e-6f);

    touch(&s, INPUT_TOUCH_MOVE, 2, 0.2f, 0.8f, 3, NULL);
    ASSERT_EQ(s.gesture_count, 2u);
    ASSERT_FLOAT_EQ(s.gestures[1].scale, 1.5f, 1e-5f);
    ASSERT_FLOAT_EQ(s.gestures[1].rotation, 1.5707963f, 1e-5f);
}

TEST(gesture_capacity_returns_overload)
{
    InputExtended s;
    input_extended_init(&s);
    touch(&s, INPUT_TOUCH_PRESS, 1, 0.1f, 0.5f, 0, NULL);
    touch(&s, INPUT_TOUCH_PRESS, 2, 0.2f, 0.5f, 1, NULL);
    for (u32 i = 0; i < INPUT_MAX_GESTURE_EVENTS; i++) {
        f32 x = 0.3f + 0.01f * (f32)i;
        touch(&s, INPUT_TOUCH_MOVE, 2, x, 0.5f, 2 + i, NULL);
    }
    ASSERT_EQ(s.gesture_count, INPUT_MAX_GESTURE_EVENTS);
    ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_MOVE, 2, 0.8f, 0.5f, 99, NULL),
              INPUT_EXT_OVERLOAD);
    ASSERT_EQ(s.dropped_gestures, (u64)1);
}

typedef struct {
    InputHapticCommand commands[256];
    u32 count;
    InputExtResult result;
} FakeHapticDevice;

static InputExtResult fake_haptic_execute(void *context,
                                          const InputHapticCommand *command)
{
    FakeHapticDevice *fake = context;
    if (fake->count < 256u) fake->commands[fake->count] = *command;
    fake->count++;
    return fake->result;
}

static void init_haptic_pad(InputExtended *s, bool feedback)
{
    input_extended_init(s);
    input_extended_backend_pad(s, 0, true, feedback, 1);
}

TEST(haptic_validation_disconnect_and_no_feedback)
{
    InputExtended s;
    u64 id = 99;
    input_extended_init(&s);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.5f, 0.5f, 100, &id),
              INPUT_EXT_DISCONNECTED);
    ASSERT_EQ(id, (u64)0);
    input_extended_backend_pad(&s, 0, true, false, 1);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.5f, 0.5f, 100, &id),
              INPUT_EXT_UNSUPPORTED);
    input_extended_backend_pad(&s, 0, true, true, 1);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.5f, 0.5f, 100, NULL),
              INPUT_EXT_INVALID);
    ASSERT_EQ(input_extended_request_haptic(&s, INPUT_MAX_PADS,
                                            0.5f, 0.5f, 100, NULL), INPUT_EXT_INVALID);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, -0.01f, 0.5f, 100, NULL),
              INPUT_EXT_INVALID);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.5f, NAN, 100, NULL),
              INPUT_EXT_INVALID);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.5f, 0.5f,
                                            INPUT_HAPTIC_MAX_DURATION_MS + 1u, NULL),
              INPUT_EXT_INVALID);
    ASSERT_EQ(s.haptic_count, 0u);
}

TEST(haptic_capacity_drain_budget_and_result_slot_reuse)
{
    InputExtended s;
    FakeHapticDevice fake = { .result = INPUT_EXT_OK };
    u64 ids[INPUT_MAX_HAPTIC_COMMANDS];
    u64 overflow_id;
    init_haptic_pad(&s, true);
    for (u32 i = 0; i < INPUT_MAX_HAPTIC_COMMANDS; i++) {
        ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.1f, 0.2f, 50, &ids[i]),
                  INPUT_EXT_OK);
        ASSERT_NEQ(ids[i], (u64)0);
    }
    ASSERT_EQ(s.haptic_count, INPUT_MAX_HAPTIC_COMMANDS);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.1f, 0.2f, 50, &overflow_id),
              INPUT_EXT_OVERLOAD);
    ASSERT_EQ(input_extended_haptic_pump(&s, fake_haptic_execute, &fake), INPUT_EXT_OK);
    ASSERT_EQ(fake.count, INPUT_HAPTIC_DRAIN_BUDGET);
    ASSERT_EQ(s.haptic_count, INPUT_MAX_HAPTIC_COMMANDS);
    for (u32 i = 0; i < INPUT_HAPTIC_DRAIN_BUDGET; i++)
        ASSERT_EQ(input_extended_haptic_result(&s, ids[i]), INPUT_EXT_OK);
    ASSERT_EQ(s.haptic_count, INPUT_MAX_HAPTIC_COMMANDS - INPUT_HAPTIC_DRAIN_BUDGET);
    ASSERT_EQ(input_extended_haptic_result(&s, ids[0]), INPUT_EXT_STALE);
    ASSERT_EQ(input_extended_haptic_result(&s, ids[INPUT_HAPTIC_DRAIN_BUDGET]),
              INPUT_EXT_PENDING);

    for (u32 round = 1; round < INPUT_MAX_HAPTIC_COMMANDS / INPUT_HAPTIC_DRAIN_BUDGET; round++)
        ASSERT_EQ(input_extended_haptic_pump(&s, fake_haptic_execute, &fake), INPUT_EXT_OK);
    for (u32 i = INPUT_HAPTIC_DRAIN_BUDGET; i < INPUT_MAX_HAPTIC_COMMANDS; i++)
        ASSERT_EQ(input_extended_haptic_result(&s, ids[i]), INPUT_EXT_OK);
    ASSERT_EQ(s.haptic_count, 0u);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.1f, 0.2f, 50, &ids[0]),
              INPUT_EXT_OK);
    ASSERT_EQ(input_extended_haptic_pump(&s, fake_haptic_execute, &fake), INPUT_EXT_OK);
    ASSERT_EQ(input_extended_haptic_result(&s, ids[0]), INPUT_EXT_OK);
}

TEST(haptic_pending_disconnect_completes_without_device_call)
{
    InputExtended s;
    FakeHapticDevice fake = { .result = INPUT_EXT_OK };
    u64 id;
    init_haptic_pad(&s, true);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.5f, 0.5f, 100, &id), INPUT_EXT_OK);
    input_extended_backend_pad(&s, 0, false, false, 1);
    ASSERT_EQ(input_extended_haptic_pump(&s, fake_haptic_execute, &fake), INPUT_EXT_OK);
    ASSERT_EQ(fake.count, 0u);
    ASSERT_EQ(input_extended_haptic_result(&s, id), INPUT_EXT_DISCONNECTED);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.5f, 0.5f, 100, &id),
              INPUT_EXT_DISCONNECTED);
}

TEST(haptic_reconnect_makes_old_generation_stale)
{
    InputExtended s;
    InputPadFeedbackStatus status;
    FakeHapticDevice fake = { .result = INPUT_EXT_OK };
    u64 id;
    u32 old_generation;
    init_haptic_pad(&s, true);
    ASSERT_EQ(input_extended_pad_status(&s, 0, &status), INPUT_EXT_OK);
    old_generation = status.generation;
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.5f, 0.5f, 100, &id), INPUT_EXT_OK);
    input_extended_backend_pad(&s, 0, false, false, 1);
    input_extended_backend_pad(&s, 0, true, true, 2);
    ASSERT_EQ(input_extended_pad_status(&s, 0, &status), INPUT_EXT_OK);
    ASSERT_NEQ(status.generation, old_generation);
    ASSERT_EQ(input_extended_haptic_pump(&s, fake_haptic_execute, &fake), INPUT_EXT_OK);
    ASSERT_EQ(fake.count, 0u);
    ASSERT_EQ(input_extended_haptic_result(&s, id), INPUT_EXT_STALE);
}

TEST(haptic_fake_receives_exact_command_and_backend_errors)
{
    InputExtended s;
    InputPadFeedbackStatus status;
    FakeHapticDevice fake = { .result = INPUT_EXT_OK };
    u64 id;
    init_haptic_pad(&s, true);
    ASSERT_EQ(input_extended_pad_status(&s, 0, &status), INPUT_EXT_OK);
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.25f, 0.75f, 250, &id), INPUT_EXT_OK);
    ASSERT_EQ(input_extended_haptic_pump(&s, fake_haptic_execute, &fake), INPUT_EXT_OK);
    ASSERT_EQ(fake.count, 1u);
    ASSERT_EQ(fake.commands[0].request_id, id);
    ASSERT_EQ(fake.commands[0].pad, 0u);
    ASSERT_EQ(fake.commands[0].generation, status.generation);
    ASSERT_FLOAT_EQ(fake.commands[0].low, 0.25f, 1e-6f);
    ASSERT_FLOAT_EQ(fake.commands[0].high, 0.75f, 1e-6f);
    ASSERT_EQ(fake.commands[0].duration_ms, 250u);
    ASSERT_EQ(input_extended_haptic_result(&s, id), INPUT_EXT_OK);

    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.0f, 0.0f, 0, &id), INPUT_EXT_OK);
    ASSERT_EQ(input_extended_haptic_pump(&s, fake_haptic_execute, &fake), INPUT_EXT_OK);
    ASSERT_EQ(fake.commands[1].duration_ms, 0u);
    fake.result = INPUT_EXT_FAILED;
    ASSERT_EQ(input_extended_request_haptic(&s, 0, 0.5f, 0.5f, 100, &id), INPUT_EXT_OK);
    ASSERT_EQ(input_extended_haptic_pump(&s, fake_haptic_execute, &fake), INPUT_EXT_OK);
    ASSERT_EQ(input_extended_haptic_result(&s, id), INPUT_EXT_FAILED);
}

#define TEST_PRODUCER_COUNT 4u
#define TEST_REQUESTS_PER_PRODUCER 64u

typedef struct {
    InputExtended *input;
    u64 ids[TEST_REQUESTS_PER_PRODUCER];
    u32 count;
    InputExtResult error;
    atomic_uint *done;
} HapticProducer;

#ifdef _WIN32
static DWORD WINAPI haptic_produce(void *argument)
#else
static void *haptic_produce(void *argument)
#endif
{
    HapticProducer *producer = argument;
    while (producer->count < TEST_REQUESTS_PER_PRODUCER) {
        u64 id;
        InputExtResult result = input_extended_request_haptic(
            producer->input, 0, 0.2f, 0.3f, 40, &id);
        if (result == INPUT_EXT_OK) {
            do {
                result = input_extended_haptic_result(producer->input, id);
                if (result == INPUT_EXT_PENDING) platform_thread_yield();
            } while (result == INPUT_EXT_PENDING);
            if (result != INPUT_EXT_OK) {
                producer->error = result;
                break;
            }
            producer->ids[producer->count++] = id;
        } else if (result == INPUT_EXT_OVERLOAD) {
            platform_thread_yield();
        } else {
            producer->error = result;
            break;
        }
    }
    (void)atomic_fetch_add_explicit(producer->done, 1u, memory_order_release);
#ifdef _WIN32
    return 0;
#else
    return NULL;
#endif
}

TEST(haptic_multithreaded_producers_only_queue_commands)
{
    InputExtended s;
    FakeHapticDevice fake = { .result = INPUT_EXT_OK };
    HapticProducer producers[TEST_PRODUCER_COUNT];
    atomic_uint done;
    u32 guard = 0;
#ifdef _WIN32
    HANDLE threads[TEST_PRODUCER_COUNT];
#else
    pthread_t threads[TEST_PRODUCER_COUNT];
#endif
    init_haptic_pad(&s, true);
    atomic_init(&done, 0u);
    memset(producers, 0, sizeof(producers));
    for (u32 i = 0; i < TEST_PRODUCER_COUNT; i++) {
        producers[i].input = &s;
        producers[i].done = &done;
#ifdef _WIN32
        threads[i] = CreateThread(NULL, 0, haptic_produce, &producers[i], 0, NULL);
        ASSERT_NOT_NULL(threads[i]);
#else
        ASSERT_EQ(pthread_create(&threads[i], NULL, haptic_produce, &producers[i]), 0);
#endif
    }
    while (atomic_load_explicit(&done, memory_order_acquire) < TEST_PRODUCER_COUNT) {
        u32 executed_before = fake.count;
        ASSERT_EQ(input_extended_haptic_pump(&s, fake_haptic_execute, &fake), INPUT_EXT_OK);
        if (fake.count == executed_before) platform_thread_yield();
        ASSERT_TRUE(++guard < 1000000u);
    }
    for (u32 i = 0; i < TEST_PRODUCER_COUNT; i++) {
#ifdef _WIN32
        ASSERT_EQ(WaitForSingleObject(threads[i], INFINITE), WAIT_OBJECT_0);
        CloseHandle(threads[i]);
#else
        ASSERT_EQ(pthread_join(threads[i], NULL), 0);
#endif
        ASSERT_EQ(producers[i].error, INPUT_EXT_OK);
        ASSERT_EQ(producers[i].count, TEST_REQUESTS_PER_PRODUCER);
    }
    ASSERT_EQ(fake.count, TEST_PRODUCER_COUNT * TEST_REQUESTS_PER_PRODUCER);
    ASSERT_EQ(s.haptic_count, 0u);
}

#ifdef INPUT_EXTENDED_TEST_SINGLE_CPU
#include <sched.h>
static bool pin_to_first_available_cpu(void)
{
    cpu_set_t available;
    cpu_set_t single;
    int cpu = 0;
    CPU_ZERO(&available);
    if (sched_getaffinity(0, sizeof(available), &available) != 0) return false;
    while (cpu < CPU_SETSIZE && !CPU_ISSET(cpu, &available)) cpu++;
    if (cpu == CPU_SETSIZE) return false;
    CPU_ZERO(&single);
    CPU_SET(cpu, &single);
    return sched_setaffinity(0, sizeof(single), &single) == 0;
}
#endif

int main(void)
{
#ifdef INPUT_EXTENDED_TEST_SINGLE_CPU
    if (!pin_to_first_available_cpu()) {
        printf("single-CPU affinity setup failed\n");
        return 1;
    }
#endif
    printf("=== Running Tests ===\n");
    RUN_TEST(init_has_version_and_empty_bounded_state);
    RUN_TEST(press_move_release_and_frame_transitions);
    RUN_TEST(same_frame_source_reuse_changes_generation_and_keeps_old_release);
    RUN_TEST(cancel_deactivates_without_completion_gesture);
    RUN_TEST(cancel_all_ends_every_active_touch);
    RUN_TEST(invalid_normalized_and_pixel_coordinates_are_transactional);
    RUN_TEST(stale_and_duplicate_source_events_do_not_change_state);
    RUN_TEST(active_capacity_is_bounded);
    RUN_TEST(event_overflow_is_explicit_and_terminal_event_never_sticks);
    RUN_TEST(tap_thresholds_are_deterministic);
    RUN_TEST(long_press_fires_once_and_motion_blocks_it);
    RUN_TEST(swipe_reports_final_displacement);
    RUN_TEST(second_touch_blocks_single_touch_gestures);
    RUN_TEST(pinch_reports_scale_centroid_and_rotation);
    RUN_TEST(gesture_capacity_returns_overload);
    RUN_TEST(haptic_validation_disconnect_and_no_feedback);
    RUN_TEST(haptic_capacity_drain_budget_and_result_slot_reuse);
    RUN_TEST(haptic_pending_disconnect_completes_without_device_call);
    RUN_TEST(haptic_reconnect_makes_old_generation_stale);
    RUN_TEST(haptic_fake_receives_exact_command_and_backend_errors);
    RUN_TEST(haptic_multithreaded_producers_only_queue_commands);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
