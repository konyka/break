#include "test_framework.h"

#include <platform/platform.h>

#include <errno.h>
#include <screen/screen.h>
#include <signal.h>
#include <sys/keycodes.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))
#define SCREEN_WAIT_ATTEMPTS 1000
#define SCREEN_WAIT_NANOSECONDS 1000000L
#define SCREEN_WATCHDOG_SECONDS 20u

#define ENGINE_KEY_RETURN 257
#define ENGINE_KEY_SHIFT 289
#define ENGINE_KEY_CTRL 290

typedef struct {
    Platform *platform;
    screen_context_t context;
    screen_window_t window;
    screen_window_t other_window;
    InputState *input;
    u32 sent_events;
    u32 observed_events;
    u32 quit_events;
} ScreenRuntime;

typedef enum {
    APP_KEY_DOWN,
    APP_KEY_UP,
    APP_POINTER_MOVE,
    APP_POINTER_DOWN,
    APP_POINTER_WHEEL,
    APP_POINTER_UP,
} AppEventType;

typedef struct {
    AppEventType type;
    int native_symbol;
    int native_flags;
    int native_modifiers;
    int native_x;
    int native_y;
    int native_buttons;
    int native_wheel;
    int key;
    u8 key_state;
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;
    f32 scroll_y;
    int modifiers;
} InputStep;

typedef struct {
    AppEventType type;
    int key;
    int modifiers;
    f32 x;
    f32 y;
    f32 scroll_y;
} ObservedEvent;

typedef bool (*InputPredicate)(const InputState *input, const void *context);

static void screen_watchdog(int signal_number)
{
    static const char message[] =
        "FAIL: QNX Screen Platform input runtime watchdog expired\n";
    (void)signal_number;
    (void)write(STDERR_FILENO, message, sizeof(message) - 1u);
    _Exit(124);
}

static bool runtime_check(bool condition, const char *message)
{
    if (!condition) {
        printf("\n  FAIL: %s\n", message);
        g_test_fail++;
    }
    return condition;
}

static bool runtime_screen_failure(const char *operation, int error)
{
    char message[256];
    (void)snprintf(message, sizeof(message), "%s: errno=%d (%s)",
                   operation, error, strerror(error));
    return runtime_check(false, message);
}

static void runtime_destroy(ScreenRuntime *runtime)
{
    if (runtime->other_window != NULL) {
        (void)screen_destroy_window(runtime->other_window);
        runtime->other_window = NULL;
    }
    if (runtime->platform != NULL) {
        platform_destroy(runtime->platform);
        runtime->platform = NULL;
    }
}

static bool runtime_open(ScreenRuntime *runtime)
{
    const PlatformConfig config = {
        .width = 320,
        .height = 240,
        .title = "Break QNX Screen Platform input runtime",
    };
    bool handles_valid;

    memset(runtime, 0, sizeof(*runtime));
    runtime->platform = platform_create(&config);
    if (!runtime_check(runtime->platform != NULL,
                       "platform_create failed with a reachable Screen service")) {
        return false;
    }
    runtime->context =
        (screen_context_t)platform_display_native(runtime->platform);
    runtime->window =
        (screen_window_t)platform_surface_native(runtime->platform);
    runtime->input = platform_input(runtime->platform);
    handles_valid = runtime->context != NULL && runtime->window != NULL &&
                    runtime->input != NULL &&
                    platform_window_native(runtime->platform) ==
                        (void *)runtime->window;
    if (!runtime_check(handles_valid,
                       "Platform did not expose its real Screen context/window/input")) {
        runtime_destroy(runtime);
        return false;
    }
    platform_window_show(runtime->platform);
    if (!runtime_check(platform_poll(runtime->platform) != PLATFORM_EVENT_QUIT,
                       "unexpected quit while initializing a Screen input test")) {
        runtime_destroy(runtime);
        return false;
    }
    return true;
}

static void runtime_delay(void)
{
    const struct timespec delay = {0, SCREEN_WAIT_NANOSECONDS};
    (void)nanosleep(&delay, NULL);
}

static bool native_event_begin(screen_window_t source, int type,
                               screen_event_t *event)
{
    void *source_handle = (void *)source;
    int result;
    int error;

    *event = NULL;
    result = screen_create_event(event);
    if (result == 0) {
        result = screen_set_event_property_iv(*event, SCREEN_PROPERTY_TYPE, &type);
    }
    if (result == 0) {
        result = screen_set_event_property_pv(*event, SCREEN_PROPERTY_WINDOW,
                                              &source_handle);
    }
    if (result == 0) return true;
    error = errno;
    if (*event != NULL) (void)screen_destroy_event(*event);
    *event = NULL;
    return runtime_screen_failure("native event source/type initialization failed",
                                  error);
}

static bool native_event_send(ScreenRuntime *runtime, screen_event_t event)
{
    int result = screen_send_event(runtime->context, event, getpid());
    int error = errno;
    (void)screen_destroy_event(event);
    if (result != 0) {
        return runtime_screen_failure("screen_send_event failed", error);
    }
    runtime->sent_events++;
    return true;
}

static bool native_send_key(ScreenRuntime *runtime, screen_window_t source,
                            int symbol, int flags, int modifiers)
{
    screen_event_t event;
    int result;
    int error;

    if (!native_event_begin(source, SCREEN_EVENT_KEYBOARD, &event)) return false;
    result = screen_set_event_property_iv(event, SCREEN_PROPERTY_SYM, &symbol);
    if (result == 0) {
        result = screen_set_event_property_iv(event, SCREEN_PROPERTY_FLAGS, &flags);
    }
    if (result == 0) {
        result = screen_set_event_property_iv(event, SCREEN_PROPERTY_MODIFIERS,
                                              &modifiers);
    }
    if (result != 0) {
        error = errno;
        (void)screen_destroy_event(event);
        return runtime_screen_failure("native keyboard property setup failed", error);
    }
    return native_event_send(runtime, event);
}

static bool native_send_pointer(ScreenRuntime *runtime, screen_window_t source,
                                int x, int y, int buttons, int wheel,
                                int modifiers)
{
    screen_event_t event;
    int position[2] = {x, y};
    int flags = SCREEN_FLAG_POSITION_VALID;
    int result;
    int error;

    if (!native_event_begin(source, SCREEN_EVENT_POINTER, &event)) return false;
    result = screen_set_event_property_iv(event, SCREEN_PROPERTY_POSITION, position);
    if (result == 0) {
        result = screen_set_event_property_iv(event, SCREEN_PROPERTY_BUTTONS,
                                              &buttons);
    }
    if (result == 0) {
        result = screen_set_event_property_iv(event, SCREEN_PROPERTY_MOUSE_WHEEL,
                                              &wheel);
    }
    if (result == 0) {
        result = screen_set_event_property_iv(event, SCREEN_PROPERTY_MODIFIERS,
                                              &modifiers);
    }
    if (result == 0) {
        result = screen_set_event_property_iv(event, SCREEN_PROPERTY_FLAGS, &flags);
    }
    if (result != 0) {
        error = errno;
        (void)screen_destroy_event(event);
        return runtime_screen_failure("native pointer property setup failed", error);
    }
    return native_event_send(runtime, event);
}

static bool native_send_manager_close(ScreenRuntime *runtime,
                                      screen_window_t source, int subtype)
{
    screen_context_t manager = NULL;
    screen_event_t event = NULL;
    int result;
    int error;

    result = screen_create_context(&manager, SCREEN_WINDOW_MANAGER_CONTEXT);
    if (result == 0) {
        result = native_event_begin(source, SCREEN_EVENT_MANAGER, &event)
                     ? 0
                     : -1;
    }
    if (result == 0) {
        result = screen_set_event_property_iv(event, SCREEN_PROPERTY_SUBTYPE,
                                              &subtype);
    }
    if (result == 0) {
        result = screen_send_event(manager, event, getpid());
    }
    error = errno;
    if (event != NULL) (void)screen_destroy_event(event);
    if (manager != NULL) (void)screen_destroy_context(manager);
    if (result != 0) {
        return runtime_screen_failure("native manager close injection failed", error);
    }
    return true;
}

static bool native_create_other_window(ScreenRuntime *runtime)
{
    int result = screen_create_window(&runtime->other_window, runtime->context);
    if (result == 0) result = screen_flush_context(runtime->context, 0);
    if (result != 0) {
        return runtime_screen_failure("real auxiliary Screen window creation failed",
                                      errno);
    }
    return true;
}

static bool native_set_origin_zero(ScreenRuntime *runtime)
{
    int origin[2] = {0, 0};
    int actual[2] = {-1, -1};
    int result = screen_set_window_property_iv(
        runtime->window, SCREEN_PROPERTY_POSITION, origin);
    if (result == 0) result = screen_flush_context(runtime->context, 0);
    if (result == 0) {
        result = screen_get_window_property_iv(
            runtime->window, SCREEN_PROPERTY_POSITION, actual);
    }
    if (result != 0) {
        return runtime_screen_failure("native window origin setup failed", errno);
    }
    return runtime_check(actual[0] == 0 && actual[1] == 0,
                         "native window origin is not the expected (0, 0)");
}

static int application_modifiers(const InputState *input)
{
    int modifiers = 0;
    if (input_key_down(input, ENGINE_KEY_SHIFT)) modifiers |= KEYMOD_SHIFT;
    if (input_key_down(input, ENGINE_KEY_CTRL)) modifiers |= KEYMOD_CTRL;
    return modifiers;
}

static bool input_step_is_pointer(const InputStep *step)
{
    return step->type == APP_POINTER_MOVE || step->type == APP_POINTER_DOWN ||
           step->type == APP_POINTER_WHEEL || step->type == APP_POINTER_UP;
}

static bool input_step_matches(const InputState *input, const void *context)
{
    const InputStep *step = (const InputStep *)context;

    if (application_modifiers(input) != step->modifiers) return false;
    if (step->key >= 0 && input->keys[step->key] != step->key_state) return false;
    if (!input_step_is_pointer(step)) return true;
    if (!input->has_mouse_pos || input->mouse_x != step->x ||
        input->mouse_y != step->y || input->mouse_dx != step->dx ||
        input->mouse_dy != step->dy || input->scroll_dx != 0.0f ||
        input->scroll_dy != step->scroll_y) {
        return false;
    }
    if (input_key_down(input, INPUT_MOUSE_RIGHT) ||
        input_key_down(input, INPUT_MOUSE_MIDDLE)) {
        return false;
    }
    if (step->key < 0 && input_key_down(input, INPUT_MOUSE_LEFT)) return false;
    return true;
}

static void print_input_snapshot(const InputState *input)
{
    printf("\n  Input snapshot: a=%u b=%u x=%u return=%u shift=%u ctrl=%u "
           "left=%u right=%u middle=%u pos=(%g, %g) delta=(%g, %g) "
           "scroll=(%g, %g) has_pos=%u\n",
           (unsigned)input->keys[(int)'a'], (unsigned)input->keys[(int)'b'],
           (unsigned)input->keys[(int)'x'],
           (unsigned)input->keys[ENGINE_KEY_RETURN],
           (unsigned)input->keys[ENGINE_KEY_SHIFT],
           (unsigned)input->keys[ENGINE_KEY_CTRL],
           (unsigned)input->keys[INPUT_MOUSE_LEFT],
           (unsigned)input->keys[INPUT_MOUSE_RIGHT],
           (unsigned)input->keys[INPUT_MOUSE_MIDDLE],
           (double)input->mouse_x, (double)input->mouse_y,
           (double)input->mouse_dx, (double)input->mouse_dy,
           (double)input->scroll_dx, (double)input->scroll_dy,
           input->has_mouse_pos ? 1u : 0u);
}

static bool poll_for_input(ScreenRuntime *runtime, InputPredicate predicate,
                           const void *context, const char *description)
{
    char message[256];
    int attempt;

    for (attempt = 0; attempt < SCREEN_WAIT_ATTEMPTS; ++attempt) {
        if (platform_poll(runtime->platform) == PLATFORM_EVENT_QUIT) {
            (void)snprintf(message, sizeof(message),
                           "unexpected quit while waiting for %s", description);
            return runtime_check(false, message);
        }
        if (predicate(runtime->input, context)) return true;
        runtime_delay();
    }
    (void)snprintf(message, sizeof(message),
                   "bounded watchdog expired waiting for %s", description);
    print_input_snapshot(runtime->input);
    return runtime_check(false, message);
}

static int input_step_expected_event_key(const InputStep *step)
{
    if (step->type == APP_POINTER_MOVE || step->type == APP_POINTER_WHEEL) {
        return -1;
    }
    return step->key;
}

static bool observe_input_step(ScreenRuntime *runtime, const InputStep *step,
                               ObservedEvent *observed)
{
    const InputState *input = runtime->input;
    int key;

    memset(observed, 0, sizeof(*observed));
    observed->key = -1;
    observed->modifiers = application_modifiers(input);
    observed->x = input->mouse_x;
    observed->y = input->mouse_y;
    observed->scroll_y = input->scroll_dy;
    if (input_step_is_pointer(step)) {
        for (key = INPUT_MOUSE_LEFT; key <= INPUT_MOUSE_MIDDLE; ++key) {
            if (input->keys[key] == 3u || input->keys[key] == 1u) {
                observed->key = key;
                observed->type = input->keys[key] == 3u ? APP_POINTER_DOWN
                                                        : APP_POINTER_UP;
                break;
            }
        }
        if (observed->key < 0) {
            observed->type = input->scroll_dx != 0.0f || input->scroll_dy != 0.0f
                                 ? APP_POINTER_WHEEL
                                 : APP_POINTER_MOVE;
        }
        if ((step->type == APP_POINTER_DOWN || step->type == APP_POINTER_UP) &&
            observed->key < 0) {
            return runtime_check(false,
                                 "pointer button observation has no actual key edge");
        }
    } else {
        for (key = 0; key < INPUT_MOUSE_LEFT; ++key) {
            if (input->keys[key] == 3u || input->keys[key] == 1u) {
                observed->key = key;
                observed->type = input->keys[key] == 3u ? APP_KEY_DOWN : APP_KEY_UP;
                break;
            }
        }
        if (observed->key < 0) {
            return runtime_check(false,
                                 "keyboard observation has no actual key edge");
        }
    }
    runtime->observed_events++;
    return true;
}

static bool run_input_step(ScreenRuntime *runtime, const InputStep *step,
                           const char *description, ObservedEvent *observed)
{
    bool sent;
    if (input_step_is_pointer(step)) {
        sent = native_send_pointer(runtime, runtime->window, step->native_x,
                                   step->native_y, step->native_buttons,
                                   step->native_wheel, step->native_modifiers);
    } else {
        sent = native_send_key(runtime, runtime->window, step->native_symbol,
                               step->native_flags, step->native_modifiers);
    }
    if (!sent) return false;
    if (!poll_for_input(runtime, input_step_matches, step, description)) return false;
    return observe_input_step(runtime, step, observed);
}

typedef struct {
    int key;
    u8 state;
} KeyExpectation;

static bool key_expectation_matches(const InputState *input, const void *context)
{
    const KeyExpectation *expectation = (const KeyExpectation *)context;
    return input->keys[expectation->key] == expectation->state;
}

static bool wait_for_key(ScreenRuntime *runtime, int key, u8 state,
                         const char *description)
{
    const KeyExpectation expectation = {key, state};
    return poll_for_input(runtime, key_expectation_matches, &expectation,
                          description);
}

TEST(qnx_screen_native_input_reaches_platform_polling)
{
    static const InputStep steps[] = {
        {
            .type = APP_KEY_DOWN,
            .native_symbol = KEYCODE_LEFT_SHIFT,
            .native_flags = KEY_DOWN | KEY_SYM_VALID,
            .native_modifiers = KEYMOD_SHIFT,
            .key = ENGINE_KEY_SHIFT,
            .key_state = 3,
            .modifiers = KEYMOD_SHIFT,
        },
        {
            .type = APP_KEY_DOWN,
            .native_symbol = 'A',
            .native_flags = KEY_DOWN | KEY_SYM_VALID,
            .native_modifiers = KEYMOD_SHIFT,
            .key = (int)'a',
            .key_state = 3,
            .modifiers = KEYMOD_SHIFT,
        },
        {
            .type = APP_KEY_UP,
            .native_symbol = 'A',
            .native_flags = KEY_SYM_VALID,
            .native_modifiers = KEYMOD_SHIFT,
            .key = (int)'a',
            .key_state = 1,
            .modifiers = KEYMOD_SHIFT,
        },
        {
            .type = APP_KEY_UP,
            .native_symbol = KEYCODE_LEFT_SHIFT,
            .native_flags = KEY_SYM_VALID,
            .key = ENGINE_KEY_SHIFT,
            .key_state = 1,
        },
        {
            .type = APP_KEY_DOWN,
            .native_symbol = KEYCODE_LEFT_CTRL,
            .native_flags = KEY_DOWN | KEY_SYM_VALID,
            .native_modifiers = KEYMOD_CTRL,
            .key = ENGINE_KEY_CTRL,
            .key_state = 3,
            .modifiers = KEYMOD_CTRL,
        },
        {
            .type = APP_KEY_DOWN,
            .native_symbol = KEYCODE_RETURN,
            .native_flags = KEY_DOWN | KEY_SYM_VALID,
            .native_modifiers = KEYMOD_CTRL,
            .key = ENGINE_KEY_RETURN,
            .key_state = 3,
            .modifiers = KEYMOD_CTRL,
        },
        {
            .type = APP_KEY_UP,
            .native_symbol = KEYCODE_RETURN,
            .native_flags = KEY_SYM_VALID,
            .native_modifiers = KEYMOD_CTRL,
            .key = ENGINE_KEY_RETURN,
            .key_state = 1,
            .modifiers = KEYMOD_CTRL,
        },
        {
            .type = APP_POINTER_MOVE,
            .native_flags = SCREEN_FLAG_POSITION_VALID,
            .native_modifiers = KEYMOD_CTRL,
            .native_x = 11,
            .native_y = 12,
            .key = -1,
            .x = 11.0f,
            .y = 12.0f,
            .modifiers = KEYMOD_CTRL,
        },
        {
            .type = APP_POINTER_DOWN,
            .native_flags = SCREEN_FLAG_POSITION_VALID,
            .native_modifiers = KEYMOD_CTRL,
            .native_x = 11,
            .native_y = 12,
            .native_buttons = SCREEN_LEFT_MOUSE_BUTTON,
            .key = INPUT_MOUSE_LEFT,
            .key_state = 3,
            .x = 11.0f,
            .y = 12.0f,
            .modifiers = KEYMOD_CTRL,
        },
        {
            .type = APP_POINTER_MOVE,
            .native_flags = SCREEN_FLAG_POSITION_VALID,
            .native_modifiers = KEYMOD_CTRL,
            .native_x = 30,
            .native_y = 40,
            .native_buttons = SCREEN_LEFT_MOUSE_BUTTON,
            .key = INPUT_MOUSE_LEFT,
            .key_state = 2,
            .x = 30.0f,
            .y = 40.0f,
            .dx = 19.0f,
            .dy = 28.0f,
            .modifiers = KEYMOD_CTRL,
        },
        {
            .type = APP_POINTER_WHEEL,
            .native_flags = SCREEN_FLAG_POSITION_VALID,
            .native_modifiers = KEYMOD_CTRL,
            .native_x = 30,
            .native_y = 40,
            .native_buttons = SCREEN_LEFT_MOUSE_BUTTON,
            .native_wheel = 3,
            .key = INPUT_MOUSE_LEFT,
            .key_state = 2,
            .x = 30.0f,
            .y = 40.0f,
            .scroll_y = 3.0f,
            .modifiers = KEYMOD_CTRL,
        },
        {
            .type = APP_POINTER_UP,
            .native_flags = SCREEN_FLAG_POSITION_VALID,
            .native_modifiers = KEYMOD_CTRL,
            .native_x = 30,
            .native_y = 40,
            .key = INPUT_MOUSE_LEFT,
            .key_state = 1,
            .x = 30.0f,
            .y = 40.0f,
            .modifiers = KEYMOD_CTRL,
        },
        {
            .type = APP_KEY_UP,
            .native_symbol = KEYCODE_LEFT_CTRL,
            .native_flags = KEY_SYM_VALID,
            .key = ENGINE_KEY_CTRL,
            .key_state = 1,
        },
    };
    ScreenRuntime runtime;
    ObservedEvent observed[SCREEN_ARRAY_COUNT(steps)];
    usize completed = 0u;
    usize i;

    if (!runtime_open(&runtime)) return;
    memset(observed, 0, sizeof(observed));
    if (native_set_origin_zero(&runtime)) {
        for (i = 0u; i < SCREEN_ARRAY_COUNT(steps); ++i) {
            char description[96];
            (void)snprintf(description, sizeof(description),
                           "ordered native input event %u", (unsigned)(i + 1u));
            if (!run_input_step(&runtime, &steps[i], description, &observed[i])) {
                break;
            }
            completed++;
        }
    }
    if (completed == SCREEN_ARRAY_COUNT(steps)) {
        (void)runtime_check(runtime.sent_events == SCREEN_ARRAY_COUNT(steps),
                            "native input send count differs from the script");
        (void)runtime_check(runtime.observed_events == SCREEN_ARRAY_COUNT(steps),
                            "Platform input observation count differs from the script");
        for (i = 0u; i < SCREEN_ARRAY_COUNT(steps); ++i) {
            (void)runtime_check(
                observed[i].type == steps[i].type &&
                    observed[i].key == input_step_expected_event_key(&steps[i]),
                "Platform input events arrived out of order or with the wrong key");
            (void)runtime_check(observed[i].modifiers == steps[i].modifiers,
                                "application modifier state differs from native input");
            if (input_step_is_pointer(&steps[i])) {
                (void)runtime_check(observed[i].x == steps[i].x &&
                                        observed[i].y == steps[i].y &&
                                        observed[i].scroll_y == steps[i].scroll_y,
                                    "pointer coordinates or wheel delta changed");
            }
        }
        (void)runtime_check(runtime.input->keys[(int)'A'] == 0u,
                            "uppercase Screen symbol did not map to the engine lowercase key");
        (void)runtime_check(!input_key_down(runtime.input, (int)'a') &&
                                !input_key_down(runtime.input, ENGINE_KEY_RETURN) &&
                                !input_key_down(runtime.input, ENGINE_KEY_SHIFT) &&
                                !input_key_down(runtime.input, ENGINE_KEY_CTRL) &&
                                !input_key_down(runtime.input, INPUT_MOUSE_LEFT),
                            "a key or button remained held after its native release");
    }
    runtime_destroy(&runtime);
}

TEST(qnx_screen_input_rejects_other_source_window)
{
    ScreenRuntime runtime;
    bool sent = false;
    bool valid_down = false;
    bool valid_up = false;

    if (!runtime_open(&runtime)) return;
    if (native_create_other_window(&runtime)) {
        sent = native_send_pointer(&runtime, runtime.other_window, 173, 91,
                                   SCREEN_LEFT_MOUSE_BUTTON, 4, KEYMOD_CTRL) &&
               native_send_key(&runtime, runtime.other_window, KEYCODE_LEFT_SHIFT,
                               KEY_DOWN | KEY_SYM_VALID, KEYMOD_SHIFT) &&
               native_send_key(&runtime, runtime.other_window, 'x',
                               KEY_DOWN | KEY_SYM_VALID, KEYMOD_SHIFT) &&
               native_send_key(&runtime, runtime.window, 'b',
                               KEY_DOWN | KEY_SYM_VALID, 0);
    }
    if (sent) {
        valid_down = wait_for_key(&runtime, (int)'b', 3u,
                                  "valid-window keyboard sentinel");
        if (valid_down) {
            runtime.observed_events++;
            (void)runtime_check(!runtime.input->has_mouse_pos &&
                                    runtime.input->scroll_dx == 0.0f &&
                                    runtime.input->scroll_dy == 0.0f,
                                "pointer/wheel input from another Screen window was consumed");
            (void)runtime_check(!input_key_down(runtime.input, INPUT_MOUSE_LEFT) &&
                                    !input_key_down(runtime.input, ENGINE_KEY_SHIFT) &&
                                    !input_key_down(runtime.input, (int)'x'),
                                "keyboard/button/modifier input from another window was consumed");
            valid_up = native_send_key(&runtime, runtime.window, 'b',
                                       KEY_SYM_VALID, 0) &&
                       wait_for_key(&runtime, (int)'b', 1u,
                                    "valid-window keyboard release");
            if (valid_up) runtime.observed_events++;
        }
    }
    if (valid_down && valid_up) {
        (void)runtime_check(runtime.sent_events == 5u,
                            "unexpected native send count in source-window test");
        (void)runtime_check(runtime.observed_events == 2u,
                            "unexpected valid-window input event count");
    }
    runtime_destroy(&runtime);
}

TEST(qnx_screen_native_property_resize_reaches_platform)
{
    ScreenRuntime runtime;
    PlatformWsiSurface wsi;
    const int resized_size[2] = {377, 211};
    bool resized = false;
    bool poll_ok = true;
    int attempt;

    if (!runtime_open(&runtime)) return;
    if (runtime_check(platform_wsi_surface_query(runtime.platform, &wsi),
                      "cannot query initial Screen WSI state")) {
        (void)runtime_check(wsi.state == PLATFORM_WSI_CREATED &&
                                wsi.logical_width == 320u &&
                                wsi.logical_height == 240u &&
                                wsi.drawable_width == 320u &&
                                wsi.drawable_height == 240u,
                            "initial Screen WSI dimensions/state are incorrect");
    }
    if (screen_set_window_property_iv(runtime.window, SCREEN_PROPERTY_SIZE,
                                      resized_size) != 0 ||
        screen_flush_context(runtime.context, 0) != 0) {
        (void)runtime_screen_failure("native SCREEN_PROPERTY_SIZE resize failed",
                                     errno);
        runtime_destroy(&runtime);
        return;
    }

    for (attempt = 0; attempt < SCREEN_WAIT_ATTEMPTS; ++attempt) {
        int native_size[2] = {0, 0};
        u32 width = 0u;
        u32 height = 0u;
        u32 logical_width = 0u;
        u32 logical_height = 0u;
        u32 drawable_width = 0u;
        u32 drawable_height = 0u;
        if (platform_poll(runtime.platform) == PLATFORM_EVENT_QUIT) {
            poll_ok = runtime_check(false, "unexpected quit during native resize");
            break;
        }
        platform_get_size(runtime.platform, &width, &height);
        platform_get_logical_size(runtime.platform, &logical_width, &logical_height);
        platform_get_drawable_size(runtime.platform, &drawable_width,
                                   &drawable_height);
        if (screen_get_window_property_iv(runtime.window, SCREEN_PROPERTY_SIZE,
                                          native_size) == 0 &&
            native_size[0] == resized_size[0] &&
            native_size[1] == resized_size[1] && width == 377u && height == 211u &&
            logical_width == 377u && logical_height == 211u &&
            drawable_width == 377u && drawable_height == 211u) {
            resized = true;
            break;
        }
        runtime_delay();
    }
    if (poll_ok) {
        (void)runtime_check(resized,
                            "native SCREEN_PROPERTY_SIZE resize did not reach all Platform size queries");
    }
    if (resized &&
        runtime_check(platform_wsi_surface_query(runtime.platform, &wsi),
                      "cannot query Screen WSI state after native resize")) {
        (void)runtime_check(wsi.state == PLATFORM_WSI_RESIZED,
                            "native resize did not transition Screen WSI to RESIZED");
        (void)runtime_check(wsi.logical_width == 377u &&
                                wsi.logical_height == 211u &&
                                wsi.drawable_width == 377u &&
                                wsi.drawable_height == 211u,
                            "native resize left stale Screen WSI dimensions");
    }
    runtime_destroy(&runtime);
}

TEST(qnx_screen_manager_close_reaches_quit_poll)
{
    ScreenRuntime runtime;
    bool filtered = false;
    bool close_sent = false;
    int attempt;

    if (!runtime_open(&runtime)) return;
    if (native_create_other_window(&runtime) &&
        native_send_manager_close(&runtime, runtime.other_window, 0x4d595543) &&
        native_send_manager_close(&runtime, runtime.window, 0) &&
        native_send_key(&runtime, runtime.window, 'b',
                        KEY_DOWN | KEY_SYM_VALID, 0) &&
        wait_for_key(&runtime, (int)'b', 3u,
                     "sentinel after filtered manager events") &&
        native_send_key(&runtime, runtime.window, 'b', KEY_SYM_VALID, 0) &&
        wait_for_key(&runtime, (int)'b', 1u,
                     "sentinel release after filtered manager events")) {
        filtered = runtime_check(
            platform_poll(runtime.platform) != PLATFORM_EVENT_QUIT,
            "another window or an unknown manager subtype produced quit");
    }
    if (filtered) {
        close_sent = native_send_manager_close(&runtime, runtime.window,
                                               0x4d595543);
    }
    if (runtime_check(close_sent, "real manager close injection must succeed")) {
        for (attempt = 0; attempt < SCREEN_WAIT_ATTEMPTS; ++attempt) {
            if (platform_poll(runtime.platform) == PLATFORM_EVENT_QUIT) {
                runtime.quit_events++;
                break;
            }
            runtime_delay();
        }
        (void)runtime_check(runtime.quit_events == 1u,
                            "real SCREEN_EVENT_MANAGER close did not produce exactly one observed quit");
    }
    runtime_destroy(&runtime);
}

int main(void)
{
    const PlatformConfig probe_config = {
        .width = 64,
        .height = 64,
        .title = "Break QNX Screen Platform input probe",
    };
    Platform *probe;
    const char *required;

    setvbuf(stdout, NULL, _IONBF, 0);
    if (signal(SIGALRM, screen_watchdog) == SIG_ERR) {
        perror("signal(SIGALRM)");
        return 1;
    }
    alarm(SCREEN_WATCHDOG_SECONDS);
    probe = platform_create(&probe_config);
    if (probe == NULL) {
        required = getenv("BREAK_QNX_SCREEN_REQUIRED");
        printf("SKIP: no usable QNX Screen service\n");
        alarm(0);
        return required != NULL && strcmp(required, "1") == 0 ? 1 : 77;
    }
    platform_destroy(probe);

    printf("=== Running Tests ===\n");
    RUN_TEST(qnx_screen_native_input_reaches_platform_polling);
    RUN_TEST(qnx_screen_input_rejects_other_source_window);
    RUN_TEST(qnx_screen_native_property_resize_reaches_platform);
    RUN_TEST(qnx_screen_manager_close_reaches_quit_poll);
    alarm(0);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
