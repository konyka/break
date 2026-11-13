#pragma once

#include <core/types.h>

#define CORE_APP_SCENARIO_MAX_BYTES (64u * 1024u)
#define CORE_APP_SCENARIO_MAX_EVENTS 4096u
#define CORE_APP_SCENARIO_MAX_LINE 511u
#define CORE_APP_SCENARIO_PATH_CAPACITY 256u
#define CORE_APP_SCENARIO_MAX_TICK 1048576u

typedef enum CoreAppScenarioKind {
    CORE_APP_SCENARIO_KEY = 1,
    CORE_APP_SCENARIO_TOUCH,
    CORE_APP_SCENARIO_PAD,
    CORE_APP_SCENARIO_FLOW,
    CORE_APP_SCENARIO_SAVE,
    CORE_APP_SCENARIO_SAVE_TO,
    CORE_APP_SCENARIO_LOAD,
    CORE_APP_SCENARIO_LOAD_FROM,
    CORE_APP_SCENARIO_UNLOAD,
    CORE_APP_SCENARIO_SCREENSHOT,
    CORE_APP_SCENARIO_QUIT,
    CORE_APP_SCENARIO_LEVEL
} CoreAppScenarioKind;

typedef enum CoreAppScenarioTouchPhase {
    CORE_APP_SCENARIO_TOUCH_DOWN = 1,
    CORE_APP_SCENARIO_TOUCH_MOVE,
    CORE_APP_SCENARIO_TOUCH_UP,
    CORE_APP_SCENARIO_TOUCH_CANCEL
} CoreAppScenarioTouchPhase;

typedef struct CoreAppScenarioEvent {
    u32 tick;
    CoreAppScenarioKind kind;
    i32 key_code;
    i32 key_down;
    i64 touch_source;
    CoreAppScenarioTouchPhase touch_phase;
    f32 x;
    f32 y;
    u32 pad;
    u32 axis;
    f32 value;
    u32 flow_key;
    char path[CORE_APP_SCENARIO_PATH_CAPACITY];
} CoreAppScenarioEvent;

typedef struct CoreAppScenario {
    CoreAppScenarioEvent *events;
    u32 event_count;
    u32 event_capacity;
    u64 seed;
    u64 fixed_dt_ns;
    bool has_quit;
} CoreAppScenario;

typedef enum CoreAppScenarioStatus {
    CORE_APP_SCENARIO_OK = 0,
    CORE_APP_SCENARIO_INVALID,
    CORE_APP_SCENARIO_IO
} CoreAppScenarioStatus;

CoreAppScenarioStatus core_app_scenario_parse(const char *text, usize size,
                                              CoreAppScenario *out);
CoreAppScenarioStatus core_app_scenario_load(const char *path,
                                             CoreAppScenario *out);
