#include "test_framework.h"

#include "../apps/core_app/scenario.h"
#include "../apps/core_app/core_app_audio.h"
#include "../apps/core_app/core_app_input.h"
#include "../apps/core_app/core_app_render.h"
#include "../apps/core_app/core_app_simulation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static CoreAppScenario *scenario_new(void) {
    return (CoreAppScenario *)calloc(1u, sizeof(CoreAppScenario));
}

static void scenario_free(CoreAppScenario *scenario) {
    if (!scenario) return;
    free(scenario->events);
    free(scenario);
}

static CoreAppScenarioStatus parse(const char *text, CoreAppScenario *out) {
    return core_app_scenario_parse(text, strlen(text), out);
}

TEST(scenario_rejects_tick_regression_without_partial_events) {
    CoreAppScenario *scenario = scenario_new();
    const char *text =
        "core-app-scenario 1\n"
        "seed 12648430\n"
        "fixed-dt-ns 16666667\n"
        "2 key w 1\n"
        "1 key w 0\n"
        "3 quit\n";
    ASSERT_NOT_NULL(scenario);
    ASSERT_EQ(parse(text, scenario), CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    ASSERT_FALSE(scenario->has_quit);
    scenario_free(scenario);
}

TEST(scenario_rejects_too_many_events_without_partial_events) {
    CoreAppScenario *scenario = scenario_new();
    char *text = (char *)malloc(900000u);
    usize used = 0u;
    u32 i;
    ASSERT_NOT_NULL(scenario);
    ASSERT_NOT_NULL(text);
    used = (usize)snprintf(text, 900000u,
        "core-app-scenario 1\nseed 1\nfixed-dt-ns 16666667\n");
    for (i = 1u; i <= CORE_APP_SCENARIO_MAX_EVENTS; ++i) {
        int written = snprintf(text + used, 900000u - used, "%u key w 1\n", i);
        ASSERT_TRUE(written > 0);
        used += (usize)written;
    }
    used += (usize)snprintf(text + used, 900000u - used, "%u quit\n", i);
    ASSERT_EQ(core_app_scenario_parse(text, used, scenario),
              CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    free(text);
    scenario_free(scenario);
}

TEST(scenario_accepts_exactly_max_events) {
    CoreAppScenario *scenario = scenario_new();
    char *text = (char *)malloc(900000u);
    usize used = 0u;
    u32 i;
    ASSERT_NOT_NULL(scenario);
    ASSERT_NOT_NULL(text);
    used = (usize)snprintf(text, 900000u,
        "core-app-scenario 1\nseed 1\nfixed-dt-ns 16666667\n");
    for (i = 1u; i < CORE_APP_SCENARIO_MAX_EVENTS; ++i) {
        int written = snprintf(text + used, 900000u - used, "%u key w 1\n", i);
        ASSERT_TRUE(written > 0);
        used += (usize)written;
    }
    used += (usize)snprintf(text + used, 900000u - used, "%u quit\n", i);
    ASSERT_TRUE(used <= CORE_APP_SCENARIO_MAX_BYTES);
    ASSERT_EQ(core_app_scenario_parse(text, used, scenario), CORE_APP_SCENARIO_OK);
    ASSERT_EQ(scenario->event_count, CORE_APP_SCENARIO_MAX_EVENTS);
    ASSERT_TRUE(scenario->has_quit);
    free(text);
    scenario_free(scenario);
}

TEST(scenario_rejects_oversized_file_without_partial_events) {
    CoreAppScenario *scenario = scenario_new();
    char *text = (char *)malloc(CORE_APP_SCENARIO_MAX_BYTES + 8u);
    usize used;
    ASSERT_NOT_NULL(scenario);
    ASSERT_NOT_NULL(text);
    memset(text, ' ', CORE_APP_SCENARIO_MAX_BYTES + 1u);
    memcpy(text, "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n", 39u);
    text[CORE_APP_SCENARIO_MAX_BYTES + 1u] = '\0';
    used = strlen(text);
    ASSERT_TRUE(used > CORE_APP_SCENARIO_MAX_BYTES);
    ASSERT_EQ(core_app_scenario_parse(text, used, scenario),
              CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    free(text);
    scenario_free(scenario);
}

TEST(scenario_rejects_unknown_command_and_nan_without_partial_events) {
    CoreAppScenario *scenario = scenario_new();
    const char *unknown =
        "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n1 teleport 1\n2 quit\n";
    const char *nan_text =
        "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n"
        "1 touch 7 move nan 0.5\n2 quit\n";
    ASSERT_NOT_NULL(scenario);
    ASSERT_EQ(parse(unknown, scenario), CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    ASSERT_EQ(parse(nan_text, scenario), CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    scenario_free(scenario);
}

TEST(scenario_rejects_duplicate_quit_without_partial_events) {
    CoreAppScenario *scenario = scenario_new();
    const char *text =
        "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n1 quit\n2 quit\n";
    ASSERT_NOT_NULL(scenario);
    ASSERT_EQ(parse(text, scenario), CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    ASSERT_FALSE(scenario->has_quit);
    scenario_free(scenario);
}

TEST(scenario_parses_ordered_input_and_header) {
    CoreAppScenario *scenario = scenario_new();
    const char *text =
        "core-app-scenario 1\n"
        "# comment\n"
        "\n"
        "seed 12648430\n"
        "fixed-dt-ns 16666667\n"
        "1 key w 1\n"
        "1 touch 42 move 0.25 0.5\n"
        "1 pad 0 1 -0.5\n"
        "1 flow 7 1.25\n"
        "2 quit\n";
    ASSERT_NOT_NULL(scenario);
    ASSERT_EQ(parse(text, scenario), CORE_APP_SCENARIO_OK);
    ASSERT_EQ(scenario->seed, 12648430ull);
    ASSERT_EQ(scenario->fixed_dt_ns, 16666667ull);
    ASSERT_EQ(scenario->event_count, 5u);
    ASSERT_EQ(scenario->events[0].kind, CORE_APP_SCENARIO_KEY);
    ASSERT_EQ(scenario->events[0].key_code, (i32)'w');
    ASSERT_EQ(scenario->events[0].key_down, 1);
    ASSERT_EQ(scenario->events[1].kind, CORE_APP_SCENARIO_TOUCH);
    ASSERT_EQ(scenario->events[1].touch_source, 42);
    ASSERT_EQ(scenario->events[1].touch_phase, CORE_APP_SCENARIO_TOUCH_MOVE);
    ASSERT_EQ(scenario->events[2].kind, CORE_APP_SCENARIO_PAD);
    ASSERT_EQ(scenario->events[2].pad, 0u);
    ASSERT_EQ(scenario->events[2].axis, 1u);
    ASSERT_EQ(scenario->events[3].kind, CORE_APP_SCENARIO_FLOW);
    ASSERT_EQ(scenario->events[3].flow_key, 7u);
    ASSERT_TRUE(scenario->has_quit);
    scenario_free(scenario);
}

TEST(scenario_parses_space_key) {
    CoreAppScenario *scenario = scenario_new();
    const char *text =
        "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n1 key space 1\n2 quit\n";
    ASSERT_NOT_NULL(scenario);
    ASSERT_EQ(parse(text, scenario), CORE_APP_SCENARIO_OK);
    ASSERT_EQ(scenario->event_count, 2u);
    ASSERT_EQ(scenario->events[0].kind, CORE_APP_SCENARIO_KEY);
    ASSERT_EQ(scenario->events[0].key_code, 32);
    ASSERT_EQ(scenario->events[0].key_down, 1);
    scenario_free(scenario);
}

TEST(scenario_rejects_event_after_quit_without_partial_events) {
    CoreAppScenario *scenario = scenario_new();
    const char *text =
        "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n1 key w 1\n2 quit\n3 key w 0\n";
    ASSERT_NOT_NULL(scenario);
    ASSERT_EQ(parse(text, scenario), CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    ASSERT_FALSE(scenario->has_quit);
    scenario_free(scenario);
}

TEST(scenario_rejects_tick_beyond_limit_without_partial_events) {
    CoreAppScenario *scenario = scenario_new();
    char text[160];
    ASSERT_NOT_NULL(scenario);
    snprintf(text, sizeof(text),
             "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n1 key w 1\n%u quit\n",
             CORE_APP_SCENARIO_MAX_TICK + 1u);
    ASSERT_EQ(parse(text, scenario), CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    snprintf(text, sizeof(text),
             "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n1 key w 1\n%u quit\n",
             CORE_APP_SCENARIO_MAX_TICK);
    ASSERT_EQ(parse(text, scenario), CORE_APP_SCENARIO_OK);
    ASSERT_EQ(scenario->events[1].tick, CORE_APP_SCENARIO_MAX_TICK);
    ASSERT_EQ(parse("core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n0 key w 1\n1 quit\n",
                    scenario), CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    scenario_free(scenario);
}

TEST(scenario_parses_level_with_and_without_asset_root) {
    CoreAppScenario *scenario = scenario_new();
    const char *text =
        "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n"
        "1 level\n2 level /tmp/core-app/assets\n3 quit\n";
    const char *extra =
        "core-app-scenario 1\nseed 1\nfixed-dt-ns 1\n1 level a b\n2 quit\n";
    ASSERT_NOT_NULL(scenario);
    ASSERT_EQ(parse(text, scenario), CORE_APP_SCENARIO_OK);
    ASSERT_EQ(scenario->event_count, 3u);
    ASSERT_EQ(scenario->events[0].kind, CORE_APP_SCENARIO_LEVEL);
    ASSERT_EQ(scenario->events[0].path[0], '\0');
    ASSERT_EQ(scenario->events[1].kind, CORE_APP_SCENARIO_LEVEL);
    ASSERT_EQ(strcmp(scenario->events[1].path, "/tmp/core-app/assets"), 0);
    ASSERT_EQ(parse(extra, scenario), CORE_APP_SCENARIO_INVALID);
    ASSERT_EQ(scenario->event_count, 0u);
    scenario_free(scenario);
}

TEST(formal_scenarios_parse) {
    static const char *const names[] = {
        "deterministic.scenario", "load_unload.scenario", "rollback.scenario"
    };
    u32 i;
    for (i = 0u; i < sizeof(names) / sizeof(names[0]); ++i) {
        char path[512];
        CoreAppScenario *scenario = scenario_new();
        int written = snprintf(path, sizeof(path), "%s/%s",
                               CORE_APP_SOURCE_ASSET_DIR, names[i]);
        ASSERT_NOT_NULL(scenario);
        ASSERT_TRUE(written > 0 && (usize)written < sizeof(path));
        if (core_app_scenario_load(path, scenario) != CORE_APP_SCENARIO_OK) {
            printf("  formal scenario rejected: %s\n", names[i]);
            scenario_free(scenario);
            ASSERT_TRUE(false);
        }
        ASSERT_TRUE(scenario->has_quit);
        scenario_free(scenario);
    }
}

static CoreAppScenarioEvent event_key(u32 tick, i32 code, i32 down) {
    CoreAppScenarioEvent event;
    memset(&event, 0, sizeof(event));
    event.tick = tick;
    event.kind = CORE_APP_SCENARIO_KEY;
    event.key_code = code;
    event.key_down = down;
    return event;
}

static CoreAppScenarioEvent event_touch(u32 tick, i64 source,
                                        CoreAppScenarioTouchPhase phase,
                                        f32 x, f32 y) {
    CoreAppScenarioEvent event;
    memset(&event, 0, sizeof(event));
    event.tick = tick;
    event.kind = CORE_APP_SCENARIO_TOUCH;
    event.touch_source = source;
    event.touch_phase = phase;
    event.x = x;
    event.y = y;
    return event;
}

TEST(input_reuses_touch_id_with_new_generation) {
    CoreAppInput *input = core_app_input_create();
    CoreAppInputFrame frame;
    CoreAppScenarioEvent down = event_touch(1u, 42, CORE_APP_SCENARIO_TOUCH_DOWN,
                                            0.5f, 0.5f);
    CoreAppScenarioEvent up = event_touch(1u, 42, CORE_APP_SCENARIO_TOUCH_UP,
                                          0.5f, 0.5f);
    CoreAppScenarioEvent again = event_touch(2u, 42, CORE_APP_SCENARIO_TOUCH_DOWN,
                                             0.4f, 0.4f);
    InputTouchId first = 0u;
    ASSERT_NOT_NULL(input);
    ASSERT_EQ(core_app_input_begin_tick(input, 1u, 1000u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_apply(input, &down), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    ASSERT_EQ(frame.touch_count, 1u);
    first = frame.touches[0].id;
    ASSERT_EQ(core_app_input_apply(input, &up), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_begin_tick(input, 2u, 1016u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_apply(input, &again), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    ASSERT_EQ(frame.touch_count, 1u);
    ASSERT_NEQ(frame.touches[0].id, first);
    core_app_input_destroy(input);
}

TEST(input_cancel_emits_no_gesture_and_next_tick_is_idle) {
    CoreAppInput *input = core_app_input_create();
    CoreAppInputFrame frame;
    CoreAppScenarioEvent down = event_touch(1u, 7, CORE_APP_SCENARIO_TOUCH_DOWN,
                                            0.2f, 0.2f);
    CoreAppScenarioEvent cancel = event_touch(1u, 7, CORE_APP_SCENARIO_TOUCH_CANCEL,
                                              0.9f, 0.9f);
    ASSERT_NOT_NULL(input);
    ASSERT_EQ(core_app_input_begin_tick(input, 1u, 1000u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_apply(input, &down), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_apply(input, &cancel), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    ASSERT_EQ(frame.gesture_count, 0u);
    ASSERT_EQ(frame.touch_count, 0u);
    ASSERT_EQ(core_app_input_begin_tick(input, 2u, 1016u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    ASSERT_EQ(frame.touch_count, 0u);
    core_app_input_destroy(input);
}

TEST(input_key_hold_survives_tick_and_release_clears_it) {
    CoreAppInput *input = core_app_input_create();
    CoreAppInputFrame frame;
    CoreAppScenarioEvent down = event_key(1u, (i32)'w', 1);
    CoreAppScenarioEvent up = event_key(3u, (i32)'w', 0);
    ASSERT_NOT_NULL(input);
    ASSERT_EQ(core_app_input_begin_tick(input, 1u, 1000u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_apply(input, &down), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    ASSERT_TRUE(input_key_down(&frame.state, 'w'));
    ASSERT_EQ(core_app_input_begin_tick(input, 2u, 1016u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    ASSERT_TRUE(input_key_down(&frame.state, 'w'));
    ASSERT_EQ(core_app_input_begin_tick(input, 3u, 1032u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_apply(input, &up), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    ASSERT_FALSE(input_key_down(&frame.state, 'w'));
    core_app_input_destroy(input);
}

static InputExtResult haptic_ok(void *context, const InputHapticCommand *command) {
    (void)command;
    if (context) (*(u32 *)context)++;
    return INPUT_EXT_OK;
}

TEST(input_haptic_unsupported_and_disconnected_requests_are_not_executed) {
    CoreAppInput *input = core_app_input_create();
    CoreAppInputFrame frame;
    InputExtResult result = INPUT_EXT_OK;
    u64 request_id;
    u32 executed = 0u;
    ASSERT_NOT_NULL(input);
    ASSERT_EQ(core_app_input_request_area_haptic(input, 0u, 0.5f, 0.5f, 100u),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    ASSERT_EQ(frame.haptic_status, INPUT_EXT_DISCONNECTED);
    core_app_input_backend_pad(input, 0u, true, false, 1u);
    ASSERT_EQ(core_app_input_request_area_haptic(input, 0u, 0.5f, 0.5f, 100u),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    ASSERT_EQ(frame.haptic_status, INPUT_EXT_UNSUPPORTED);
    core_app_input_backend_pad(input, 0u, true, true, 1u);
    ASSERT_EQ(core_app_input_request_area_haptic(input, 0u, 0.5f, 0.5f, 100u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    request_id = frame.haptic_request_id;
    ASSERT_NEQ(request_id, 0u);
    core_app_input_backend_pad(input, 0u, false, false, 1u);
    ASSERT_EQ(core_app_input_pump_haptics(input, haptic_ok, &executed),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(executed, 0u);
    ASSERT_EQ(core_app_input_haptic_result(input, request_id, &result),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(result == INPUT_EXT_DISCONNECTED || result == INPUT_EXT_STALE);
    core_app_input_destroy(input);
}

typedef struct HapticRecorder {
    u32 executed;
    u32 generation;
    u64 request_id;
} HapticRecorder;

static InputExtResult haptic_record(void *context, const InputHapticCommand *command) {
    HapticRecorder *recorder = (HapticRecorder *)context;
    recorder->executed++;
    recorder->generation = command->generation;
    recorder->request_id = command->request_id;
    return INPUT_EXT_OK;
}

TEST(input_haptic_carries_pad_generation_and_reconnect_is_stale) {
    CoreAppInput *input = core_app_input_create();
    CoreAppInputFrame frame;
    HapticRecorder recorder;
    InputExtResult result = INPUT_EXT_INVALID;
    u32 generation = 0u;
    u32 reconnected = 0u;
    u64 first;
    u64 second;
    memset(&recorder, 0, sizeof(recorder));
    ASSERT_NOT_NULL(input);
    core_app_input_backend_pad(input, 0u, true, true, 1u);
    ASSERT_EQ(core_app_input_pad_generation(input, 0u, &generation), BREAK_RUNTIME_OK);
    ASSERT_NEQ(generation, 0u);
    ASSERT_EQ(core_app_input_request_area_haptic(input, 0u, 0.5f, 0.5f, 100u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    first = frame.haptic_request_id;
    ASSERT_EQ(core_app_input_pump_haptics(input, haptic_record, &recorder),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(recorder.executed, 1u);
    ASSERT_EQ(recorder.generation, generation);
    ASSERT_EQ(recorder.request_id, first);
    ASSERT_EQ(core_app_input_haptic_result(input, first, &result), BREAK_RUNTIME_OK);
    ASSERT_EQ(result, INPUT_EXT_OK);

    ASSERT_EQ(core_app_input_request_area_haptic(input, 0u, 0.5f, 0.5f, 100u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_input_frame(input, &frame), BREAK_RUNTIME_OK);
    second = frame.haptic_request_id;
    core_app_input_backend_pad(input, 0u, true, true, 2u);
    ASSERT_EQ(core_app_input_pad_generation(input, 0u, &reconnected), BREAK_RUNTIME_OK);
    ASSERT_NEQ(reconnected, generation);
    ASSERT_EQ(core_app_input_pump_haptics(input, haptic_record, &recorder),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(recorder.executed, 1u);
    ASSERT_EQ(core_app_input_haptic_result(input, second, &result), BREAK_RUNTIME_OK);
    ASSERT_EQ(result, INPUT_EXT_STALE);
    core_app_input_destroy(input);
}

TEST(input_snapshot_copies_platform_touches_without_mutating_source) {
    InputState state;
    InputExtended *extended = (InputExtended *)calloc(1u, sizeof(InputExtended));
    CoreAppInputFrame frame;
    InputTouchId id = 0u;
    u32 count_before;
    ASSERT_NOT_NULL(extended);
    input_init(&state);
    input_set_key(&state, 'w', true);
    input_extended_init(extended);
    ASSERT_EQ(input_extended_touch(extended, INPUT_TOUCH_PRESS, 9, 0.5f, 0.5f,
                                   1000u, &id), INPUT_EXT_OK);
    count_before = extended->touch_count;
    ASSERT_EQ(core_app_input_snapshot(&state, extended, &frame), BREAK_RUNTIME_OK);
    ASSERT_TRUE(input_key_down(&frame.state, 'w'));
    ASSERT_EQ(frame.touch_count, 1u);
    ASSERT_EQ(frame.touches[0].id, id);
    ASSERT_EQ(extended->touch_count, count_before);
    extended->abi_version++;
    ASSERT_EQ(core_app_input_snapshot(&state, extended, &frame), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(frame.touch_count, 0u);
    extended->abi_version--;
    extended->struct_size--;
    ASSERT_EQ(core_app_input_snapshot(&state, extended, &frame), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_input_snapshot(&state, NULL, &frame), BREAK_RUNTIME_INVALID);
    free(extended);
}

typedef struct SimFixture {
    World *world;
    BreakGame *actor_runtime;
    PhysicsWorld *physics;
    Entity user;
    CoreAppSimulation *simulation;
    CoreAppInput *input;
} SimFixture;

static bool sim_fixture_init(SimFixture *fixture) {
    CoreAppSimulationDesc desc;
    Vec3 *position;
    memset(fixture, 0, sizeof(*fixture));
    fixture->world = world_create();
    if (!fixture->world) return false;
    world_register_component(fixture->world, BREAK_GAME_POSITION_COMPONENT,
                             sizeof(Vec3));
    fixture->user = world_create_entity(fixture->world);
    position = (Vec3 *)world_add_component(fixture->world, fixture->user,
                                           BREAK_GAME_POSITION_COMPONENT);
    if (!position) return false;
    *position = vec3(0.0f, 1.5f, 0.0f);
    fixture->actor_runtime = break_game_create(fixture->world, NULL);
    fixture->physics = physics_world_create(16u);
    if (!fixture->actor_runtime || !fixture->physics) return false;
    physics_body_create(fixture->physics, vec3(0.0f, 0.0f, 0.0f),
                        vec3(50.0f, 0.5f, 50.0f), 0.0f, true, 0u);
    memset(&desc, 0, sizeof(desc));
    desc.world = fixture->world;
    desc.actor_runtime = fixture->actor_runtime;
    desc.physics = fixture->physics;
    desc.user = fixture->user;
    desc.spawn = *position;
    fixture->simulation = core_app_simulation_create(&desc);
    fixture->input = core_app_input_create();
    return fixture->simulation && fixture->input;
}

static void sim_fixture_dispose(SimFixture *fixture) {
    core_app_input_destroy(fixture->input);
    core_app_simulation_destroy(fixture->simulation);
    if (fixture->physics) physics_world_destroy(fixture->physics);
    if (fixture->actor_runtime) break_game_destroy(fixture->actor_runtime);
    if (fixture->world) world_destroy(fixture->world);
}

static u64 g_sim_ms_per_tick = 16u;

static bool sim_step(SimFixture *fixture, u32 tick,
                     const CoreAppScenarioEvent *events, u32 event_count) {
    CoreAppInputFrame frame;
    u32 i;
    if (core_app_input_begin_tick(fixture->input, tick,
                                  (u64)tick * g_sim_ms_per_tick) !=
        BREAK_RUNTIME_OK) {
        return false;
    }
    for (i = 0u; i < event_count; ++i) {
        if (core_app_input_apply(fixture->input, &events[i]) != BREAK_RUNTIME_OK) {
            return false;
        }
    }
    return core_app_input_frame(fixture->input, &frame) == BREAK_RUNTIME_OK &&
           core_app_simulation_tick(fixture->simulation, &frame) == BREAK_RUNTIME_OK;
}

static bool sim_run_key(SimFixture *fixture, u32 ticks) {
    CoreAppScenarioEvent down = event_key(1u, (i32)'w', 1);
    u32 tick;
    for (tick = 1u; tick <= ticks; ++tick) {
        if (!sim_step(fixture, tick, &down, tick == 1u ? 1u : 0u)) return false;
    }
    return true;
}

static bool sim_run_touch(SimFixture *fixture, u32 ticks) {
    CoreAppScenarioEvent drag[2];
    u32 tick;
    drag[0] = event_touch(1u, 3, CORE_APP_SCENARIO_TOUCH_DOWN, 0.5f, 0.5f);
    drag[1] = event_touch(1u, 3, CORE_APP_SCENARIO_TOUCH_MOVE, 0.5f, 0.3f);
    for (tick = 1u; tick <= ticks; ++tick) {
        if (!sim_step(fixture, tick, drag, tick == 1u ? 2u : 0u)) return false;
    }
    return true;
}

TEST(simulation_key_and_touch_drag_reach_same_position) {
    SimFixture key;
    SimFixture touch;
    Vec3 key_position;
    Vec3 touch_position;
    Vec3 *component;
    ASSERT_TRUE(sim_fixture_init(&key));
    ASSERT_TRUE(sim_fixture_init(&touch));
    ASSERT_TRUE(sim_run_key(&key, 180u));
    ASSERT_TRUE(sim_run_touch(&touch, 180u));
    ASSERT_EQ(core_app_simulation_user_position(key.simulation, &key_position),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_simulation_user_position(touch.simulation, &touch_position),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_simulation_tick_count(key.simulation), 180u);
    ASSERT_TRUE(key_position.e[2] > 2.0f);
    ASSERT_FLOAT_EQ(key_position.e[0], touch_position.e[0], 1e-5);
    ASSERT_FLOAT_EQ(key_position.e[1], touch_position.e[1], 1e-5);
    ASSERT_FLOAT_EQ(key_position.e[2], touch_position.e[2], 1e-5);
    component = (Vec3 *)world_get_component(key.world, key.user,
                                            BREAK_GAME_POSITION_COMPONENT);
    ASSERT_NOT_NULL(component);
    ASSERT_EQ(memcmp(component, &key_position, sizeof(Vec3)), 0);
    sim_fixture_dispose(&key);
    sim_fixture_dispose(&touch);
}

TEST(simulation_release_and_cancel_stop_on_next_tick) {
    SimFixture key;
    SimFixture touch;
    CoreAppScenarioEvent up = event_key(11u, (i32)'w', 0);
    CoreAppScenarioEvent cancel = event_touch(11u, 3, CORE_APP_SCENARIO_TOUCH_CANCEL,
                                              0.5f, 0.3f);
    Vec3 before;
    Vec3 after;
    ASSERT_TRUE(sim_fixture_init(&key));
    ASSERT_TRUE(sim_fixture_init(&touch));
    ASSERT_TRUE(sim_run_key(&key, 10u));
    ASSERT_EQ(core_app_simulation_user_position(key.simulation, &before),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(sim_step(&key, 11u, &up, 1u));
    ASSERT_EQ(core_app_simulation_user_position(key.simulation, &after),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(fabsf(after.e[0] - before.e[0]) < 1e-6f);
    ASSERT_TRUE(fabsf(after.e[2] - before.e[2]) < 1e-6f);
    ASSERT_TRUE(sim_run_touch(&touch, 10u));
    ASSERT_EQ(core_app_simulation_user_position(touch.simulation, &before),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(before.e[2] > 0.0f);
    ASSERT_TRUE(sim_step(&touch, 11u, &cancel, 1u));
    ASSERT_TRUE(sim_step(&touch, 12u, NULL, 0u));
    ASSERT_EQ(core_app_simulation_user_position(touch.simulation, &after),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(fabsf(after.e[0] - before.e[0]) < 1e-6f);
    ASSERT_TRUE(fabsf(after.e[2] - before.e[2]) < 1e-6f);
    sim_fixture_dispose(&key);
    sim_fixture_dispose(&touch);
}

TEST(simulation_repeated_runs_are_bitwise_identical) {
    SimFixture first;
    SimFixture second;
    Vec3 a;
    Vec3 b;
    ASSERT_TRUE(sim_fixture_init(&first));
    ASSERT_TRUE(sim_fixture_init(&second));
    ASSERT_TRUE(sim_run_key(&first, 120u));
    ASSERT_TRUE(sim_run_key(&second, 120u));
    ASSERT_EQ(core_app_simulation_user_position(first.simulation, &a),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_simulation_user_position(second.simulation, &b),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(memcmp(&a, &b, sizeof(a)), 0);
    sim_fixture_dispose(&first);
    sim_fixture_dispose(&second);
}

TEST(simulation_ignores_wall_clock_pacing) {
    SimFixture fast;
    SimFixture slow;
    Vec3 a;
    Vec3 b;
    ASSERT_TRUE(sim_fixture_init(&fast));
    ASSERT_TRUE(sim_fixture_init(&slow));
    g_sim_ms_per_tick = 8u;
    ASSERT_TRUE(sim_run_key(&fast, 90u));
    g_sim_ms_per_tick = 33u;
    ASSERT_TRUE(sim_run_key(&slow, 90u));
    g_sim_ms_per_tick = 16u;
    ASSERT_EQ(core_app_simulation_user_position(fast.simulation, &a),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_simulation_user_position(slow.simulation, &b),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(a.e[2] > 1.0f);
    ASSERT_EQ(memcmp(&a, &b, sizeof(a)), 0);
    sim_fixture_dispose(&fast);
    sim_fixture_dispose(&slow);
}

TEST(accumulator_caps_substeps_and_records_dropped_time) {
    CoreAppAccumulator accumulator;
    memset(&accumulator, 0, sizeof(accumulator));
    ASSERT_EQ(core_app_accumulator_advance(&accumulator, 10000000ull), 0u);
    ASSERT_EQ(accumulator.remainder_ns, 10000000ull);
    ASSERT_EQ(core_app_accumulator_advance(&accumulator, 10000000ull), 1u);
    ASSERT_EQ(accumulator.remainder_ns, 20000000ull - CORE_APP_FIXED_DT_NS);
    memset(&accumulator, 0, sizeof(accumulator));
    ASSERT_EQ(core_app_accumulator_advance(&accumulator, 1000000000ull),
              CORE_APP_MAX_SUBSTEPS);
    ASSERT_EQ(accumulator.dropped_ns, 51ull * CORE_APP_FIXED_DT_NS);
    ASSERT_EQ(accumulator.remainder_ns, 1000000000ull - 59ull * CORE_APP_FIXED_DT_NS);
}

static CoreAppResourceTable *resource_table_new(void) {
    CoreAppResourceTable *table = (CoreAppResourceTable *)calloc(1u, sizeof(*table));
    if (table) core_app_resource_table_init(table);
    return table;
}

TEST(resource_late_completion_after_reload_is_stale) {
    CoreAppResourceTable *table = resource_table_new();
    const u8 old_bytes[4] = {1u, 2u, 3u, 4u};
    const u8 new_bytes[4] = {9u, 8u, 7u, 6u};
    u32 slot_a = UINT32_MAX;
    u32 slot_b = UINT32_MAX;
    u64 request_a = 0u;
    u64 request_b = 0u;
    ASSERT_NOT_NULL(table);
    ASSERT_EQ(core_app_resource_request(table, 1u, &slot_a, &request_a), BREAK_RUNTIME_OK);
    ASSERT_NEQ(request_a, 0u);
    ASSERT_EQ(core_app_resource_retire_generation(table, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_resource_request(table, 2u, &slot_b, &request_b), BREAK_RUNTIME_OK);
    ASSERT_EQ(slot_b, slot_a);
    ASSERT_NEQ(request_b, request_a);
    ASSERT_EQ(core_app_resource_complete(table, slot_a, request_a, 1u, old_bytes, 4u),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(table->stale_completions, 1u);
    ASSERT_EQ(table->slots[slot_b].state, CORE_APP_RESOURCE_PENDING);
    ASSERT_EQ(table->slots[slot_b].byte_count, 0u);
    ASSERT_EQ(core_app_resource_complete(table, slot_b, request_b, 1u, old_bytes, 4u),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(table->stale_completions, 2u);
    ASSERT_EQ(core_app_resource_complete(table, slot_b, request_b, 2u, new_bytes, 4u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(table->slots[slot_b].state, CORE_APP_RESOURCE_LIVE);
    ASSERT_EQ(table->slots[slot_b].version, 1u);
    ASSERT_EQ(memcmp(table->slots[slot_b].bytes, new_bytes, 4u), 0);
    ASSERT_EQ(core_app_resource_complete(table, slot_b, request_b, 2u, old_bytes, 4u),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(memcmp(table->slots[slot_b].bytes, new_bytes, 4u), 0);
    ASSERT_EQ(table->slots[slot_b].version, 1u);
    free(table);
}

TEST(resource_failed_staging_keeps_live_bytes) {
    CoreAppResourceTable *table = resource_table_new();
    const u8 bytes[4] = {5u, 5u, 5u, 5u};
    u8 huge[CORE_APP_RESOURCE_MAX_BYTES + 1u];
    u32 slot = UINT32_MAX;
    u64 request = 0u;
    memset(huge, 0xEE, sizeof(huge));
    ASSERT_NOT_NULL(table);
    ASSERT_EQ(core_app_resource_request(table, 3u, &slot, &request), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_resource_complete(table, slot, request, 3u, bytes, 4u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_resource_reload(table, slot, 3u, &request), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_resource_complete(table, slot, request, 3u, huge, sizeof(huge)),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(table->slots[slot].state, CORE_APP_RESOURCE_LIVE);
    ASSERT_EQ(table->slots[slot].version, 1u);
    ASSERT_EQ(table->slots[slot].byte_count, 4u);
    ASSERT_EQ(memcmp(table->slots[slot].bytes, bytes, 4u), 0);
    free(table);
}

TEST(resource_table_overload_does_not_touch_live_slots) {
    CoreAppResourceTable *table = resource_table_new();
    CoreAppResourceTable *before = (CoreAppResourceTable *)calloc(1u, sizeof(*before));
    u32 slot = UINT32_MAX;
    u64 request = 0u;
    u32 i;
    ASSERT_NOT_NULL(table);
    ASSERT_NOT_NULL(before);
    for (i = 0u; i < CORE_APP_RESOURCE_SLOTS; ++i) {
        u8 byte = (u8)i;
        ASSERT_EQ(core_app_resource_request(table, 4u, &slot, &request), BREAK_RUNTIME_OK);
        ASSERT_EQ(slot, i);
        ASSERT_EQ(core_app_resource_complete(table, slot, request, 4u, &byte, 1u),
                  BREAK_RUNTIME_OK);
    }
    memcpy(before, table, sizeof(*before));
    slot = 77u;
    request = 77u;
    ASSERT_EQ(core_app_resource_request(table, 4u, &slot, &request), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(slot, 77u);
    ASSERT_EQ(request, 77u);
    ASSERT_EQ(memcmp(table->slots, before->slots, sizeof(table->slots)), 0);
    ASSERT_EQ(table->overloads, 1u);
    free(before);
    free(table);
}

static FILE *audio_trace_open(void) {
    return tmpfile();
}

static void audio_trace_read(FILE *trace, char *out, usize capacity) {
    usize used = 0u;
    if (!trace || !out || capacity == 0u) return;
    fflush(trace);
    rewind(trace);
    for (;;) {
        size_t read = fread(out + used, 1u, capacity - 1u - used, trace);
        used += (usize)read;
        if (read == 0u || used >= capacity - 1u) break;
    }
    out[used] = '\0';
}

TEST(audio_queue_admits_two_hundred_fifty_six_commands) {
    CoreAppAudio audio;
    FILE *trace = audio_trace_open();
    ASSERT_NOT_NULL(trace);
    ASSERT_EQ(core_app_audio_start(&audio, trace), BREAK_RUNTIME_OK);
    ASSERT_EQ(CORE_APP_AUDIO_QUEUE_CAPACITY, 256u);
    for (u32 i = 0u; i < CORE_APP_AUDIO_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_LISTENER, 1u), BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(audio.count, CORE_APP_AUDIO_QUEUE_CAPACITY);
    ASSERT_EQ(audio.overloads, 0u);
    fclose(trace);
}

TEST(audio_full_queue_reports_overload_and_keeps_oldest) {
    CoreAppAudio audio;
    FILE *trace = audio_trace_open();
    ASSERT_NOT_NULL(trace);
    ASSERT_EQ(core_app_audio_start(&audio, trace), BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < CORE_APP_AUDIO_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_LISTENER, 1u), BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(audio.commands[audio.head].sequence, 1u);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_LISTENER, 1u), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(audio.overloads, 1u);
    ASSERT_EQ(audio.count, CORE_APP_AUDIO_QUEUE_CAPACITY);
    ASSERT_EQ(audio.commands[audio.head].sequence, 1u);
    ASSERT_EQ(core_app_audio_drain_record(&audio, 1u), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(audio.count, CORE_APP_AUDIO_QUEUE_CAPACITY - 1u);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_LISTENER, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(audio.count, CORE_APP_AUDIO_QUEUE_CAPACITY);
    fclose(trace);
}

TEST(audio_record_trace_keeps_command_order_and_generation) {
    CoreAppAudio audio;
    FILE *trace = audio_trace_open();
    char text[4096];
    ASSERT_NOT_NULL(trace);
    ASSERT_EQ(core_app_audio_start(&audio, trace), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_LISTENER, 3u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_PLAY_3D, 3u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_POSITION, 3u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_STOP, 3u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_drain_record(&audio, CORE_APP_AUDIO_QUEUE_CAPACITY),
              BREAK_RUNTIME_OK);
    audio_trace_read(trace, text, sizeof(text));
    ASSERT_NOT_NULL(strstr(text,
        "event=audio kind=listener generation=3 sequence=1 source=0\n"));
    ASSERT_NOT_NULL(strstr(text,
        "event=audio kind=play_3d generation=3 sequence=2 source=1\n"));
    ASSERT_NOT_NULL(strstr(text,
        "event=audio kind=position generation=3 sequence=3 source=1\n"));
    ASSERT_NOT_NULL(strstr(text,
        "event=audio kind=stop generation=3 sequence=4 source=1\n"));
    fclose(trace);
}

TEST(audio_source_generation_rejects_late_stop_for_new_level) {
    CoreAppAudio audio;
    FILE *trace = audio_trace_open();
    ASSERT_NOT_NULL(trace);
    ASSERT_EQ(core_app_audio_start(&audio, trace), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_PLAY_3D, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_drain_record(&audio, CORE_APP_AUDIO_QUEUE_CAPACITY),
              BREAK_RUNTIME_OK);
    u32 old_slot = audio.play_slots[0].slot;
    ASSERT_NEQ(old_slot, CORE_APP_AUDIO_SOURCE_INVALID);
    ASSERT_EQ(audio.play_slots[0].generation, 1u);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_STOP, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_drain_record(&audio, CORE_APP_AUDIO_QUEUE_CAPACITY),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(audio.stale_commands, 0u);
    ASSERT_EQ(audio.play_slots[0].slot, CORE_APP_AUDIO_SOURCE_INVALID);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_PLAY_3D, 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_drain_record(&audio, CORE_APP_AUDIO_QUEUE_CAPACITY),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(audio.play_slots[0].slot, old_slot);
    ASSERT_EQ(audio.play_slots[0].generation, 2u);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_STOP, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_drain_record(&audio, CORE_APP_AUDIO_QUEUE_CAPACITY),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(audio.stale_commands, 1u);
    ASSERT_EQ(audio.play_slots[0].slot, old_slot);
    ASSERT_EQ(audio.play_slots[0].generation, 2u);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_STOP, 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_drain_record(&audio, CORE_APP_AUDIO_QUEUE_CAPACITY),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(audio.stale_commands, 1u);
    ASSERT_EQ(audio.play_slots[0].slot, CORE_APP_AUDIO_SOURCE_INVALID);
    fclose(trace);
}

TEST(audio_shutdown_drains_and_refuses_new_commands) {
    CoreAppAudio audio;
    FILE *trace = audio_trace_open();
    ASSERT_NOT_NULL(trace);
    ASSERT_EQ(core_app_audio_start(&audio, trace), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_LISTENER, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_stop_admission(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_LISTENER, 1u), BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(core_app_audio_stop_producers(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_close_queues(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_join(&audio), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(core_app_audio_drain_record(&audio, CORE_APP_AUDIO_QUEUE_CAPACITY),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_join(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_destroy(&audio), BREAK_RUNTIME_OK);
    fclose(trace);
}

TEST(audio_null_mode_accepts_commands_without_a_trace) {
    CoreAppAudio audio;
    ASSERT_EQ(core_app_audio_start_null(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_LISTENER, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_drain_null(&audio, CORE_APP_AUDIO_QUEUE_CAPACITY), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_stop_admission(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_stop_producers(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_close_queues(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_join(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_destroy(&audio), BREAK_RUNTIME_OK);
}

TEST(audio_device_mode_reports_unavailable_and_degrades_to_null) {
    CoreAppAudio audio;
    FILE *trace = audio_trace_open();
    char text[4096];
    ASSERT_NOT_NULL(trace);
    ASSERT_EQ(core_app_audio_start_device(&audio, trace, false), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(audio.mode, CORE_APP_AUDIO_BACKEND_NULL);
    ASSERT_EQ(audio.device_fallbacks, 1u);
    audio_trace_read(trace, text, sizeof(text));
    ASSERT_NOT_NULL(strstr(text,
        "event=audio mode=device result=unavailable fallback=null\n"));
    ASSERT_EQ(core_app_audio_enqueue(&audio, CORE_APP_AUDIO_LISTENER, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_stop_admission(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_stop_producers(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_close_queues(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_drain_record(&audio, CORE_APP_AUDIO_QUEUE_CAPACITY),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_join(&audio), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_audio_destroy(&audio), BREAK_RUNTIME_OK);
    fclose(trace);
}

TEST(audio_device_required_mode_fails_when_no_device_exists) {
    CoreAppAudio audio;
    FILE *trace = audio_trace_open();
    ASSERT_NOT_NULL(trace);
    ASSERT_EQ(core_app_audio_start_device(&audio, trace, true), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(audio.device_fallbacks, 0u);
    fclose(trace);
}

TEST_MAIN_BEGIN()
    RUN_TEST(scenario_rejects_tick_regression_without_partial_events);
    RUN_TEST(scenario_rejects_too_many_events_without_partial_events);
    RUN_TEST(scenario_accepts_exactly_max_events);
    RUN_TEST(scenario_rejects_oversized_file_without_partial_events);
    RUN_TEST(scenario_rejects_unknown_command_and_nan_without_partial_events);
    RUN_TEST(scenario_rejects_duplicate_quit_without_partial_events);
    RUN_TEST(scenario_parses_ordered_input_and_header);
    RUN_TEST(scenario_parses_space_key);
    RUN_TEST(scenario_rejects_event_after_quit_without_partial_events);
    RUN_TEST(scenario_rejects_tick_beyond_limit_without_partial_events);
    RUN_TEST(scenario_parses_level_with_and_without_asset_root);
    RUN_TEST(formal_scenarios_parse);
    RUN_TEST(input_reuses_touch_id_with_new_generation);
    RUN_TEST(input_cancel_emits_no_gesture_and_next_tick_is_idle);
    RUN_TEST(input_key_hold_survives_tick_and_release_clears_it);
    RUN_TEST(input_haptic_unsupported_and_disconnected_requests_are_not_executed);
    RUN_TEST(input_haptic_carries_pad_generation_and_reconnect_is_stale);
    RUN_TEST(input_snapshot_copies_platform_touches_without_mutating_source);
    RUN_TEST(simulation_key_and_touch_drag_reach_same_position);
    RUN_TEST(simulation_release_and_cancel_stop_on_next_tick);
    RUN_TEST(simulation_repeated_runs_are_bitwise_identical);
    RUN_TEST(simulation_ignores_wall_clock_pacing);
    RUN_TEST(accumulator_caps_substeps_and_records_dropped_time);
    RUN_TEST(resource_late_completion_after_reload_is_stale);
    RUN_TEST(resource_failed_staging_keeps_live_bytes);
    RUN_TEST(resource_table_overload_does_not_touch_live_slots);
    RUN_TEST(audio_queue_admits_two_hundred_fifty_six_commands);
    RUN_TEST(audio_full_queue_reports_overload_and_keeps_oldest);
    RUN_TEST(audio_record_trace_keeps_command_order_and_generation);
    RUN_TEST(audio_source_generation_rejects_late_stop_for_new_level);
    RUN_TEST(audio_shutdown_drains_and_refuses_new_commands);
    RUN_TEST(audio_null_mode_accepts_commands_without_a_trace);
    RUN_TEST(audio_device_mode_reports_unavailable_and_degrades_to_null);
    RUN_TEST(audio_device_required_mode_fails_when_no_device_exists);
TEST_MAIN_END()
