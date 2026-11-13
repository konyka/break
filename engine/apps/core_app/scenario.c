#include "scenario.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void scenario_clear(CoreAppScenario *out) {
    if (!out) return;
    free(out->events);
    memset(out, 0, sizeof(*out));
}

static bool decimal_u64(const char *token, u64 limit, u64 *out) {
    u64 value = 0u;
    const char *cursor = token;
    if (!token || token[0] < '0' || token[0] > '9') return false;
    while (*cursor >= '0' && *cursor <= '9') {
        u64 digit = (u64)(*cursor - '0');
        if (value > (limit - digit) / 10u) return false;
        value = value * 10u + digit;
        cursor++;
    }
    if (*cursor != '\0') return false;
    *out = value;
    return true;
}

static bool decimal_i64(const char *token, i64 *out) {
    u64 magnitude = 0u;
    bool negative = false;
    if (token && token[0] == '-') {
        negative = true;
        token++;
    }
    if (!decimal_u64(token, negative ? (u64)INT64_MAX + 1u : (u64)INT64_MAX,
                     &magnitude)) {
        return false;
    }
    if (negative && magnitude == (u64)INT64_MAX + 1u) {
        *out = INT64_MIN;
        return true;
    }
    *out = negative ? -(i64)magnitude : (i64)magnitude;
    return true;
}

static bool header_u64(const char *line, const char *name, bool nonzero, u64 *out) {
    const char *cursor = line;
    usize name_length = strlen(name);
    if (strncmp(cursor, name, name_length) != 0 || cursor[name_length] != ' ') {
        return false;
    }
    cursor += name_length + 1u;
    if (!decimal_u64(cursor, UINT64_MAX, out)) return false;
    return !nonzero || *out != 0u;
}

static bool finite_number(const char *token, f32 minimum, f32 maximum, f32 *out) {
    char *end = NULL;
    double value;
    if (!token || token[0] == '\0' || isspace((unsigned char)token[0])) return false;
    value = strtod(token, &end);
    if (end == token || *end != '\0' || !isfinite(value) ||
        value < (double)minimum || value > (double)maximum) {
        return false;
    }
    *out = (f32)value;
    return true;
}

static bool key_code(const char *token, i32 *out) {
    if (!token || token[1] != '\0') return false;
    if (token[0] >= 'A' && token[0] <= 'Z') {
        *out = (i32)(token[0] - 'A' + 'a');
        return true;
    }
    if ((token[0] >= 'a' && token[0] <= 'z') ||
        (token[0] >= '0' && token[0] <= '9')) {
        *out = (i32)token[0];
        return true;
    }
    return false;
}

static bool touch_phase(const char *token, CoreAppScenarioTouchPhase *out) {
    if (strcmp(token, "down") == 0) *out = CORE_APP_SCENARIO_TOUCH_DOWN;
    else if (strcmp(token, "move") == 0) *out = CORE_APP_SCENARIO_TOUCH_MOVE;
    else if (strcmp(token, "up") == 0) *out = CORE_APP_SCENARIO_TOUCH_UP;
    else if (strcmp(token, "cancel") == 0) *out = CORE_APP_SCENARIO_TOUCH_CANCEL;
    else return false;
    return true;
}

static bool relative_path(char *out, const char *token) {
    usize length = token ? strlen(token) : 0u;
    if (length == 0u || length >= CORE_APP_SCENARIO_PATH_CAPACITY ||
        token[0] == '/' || token[0] == '\\' || strstr(token, "..") != NULL) {
        return false;
    }
    memcpy(out, token, length + 1u);
    return true;
}

static bool asset_root(char *out, const char *token) {
    usize length = token ? strlen(token) : 0u;
    if (length == 0u || length >= CORE_APP_SCENARIO_PATH_CAPACITY) return false;
    memcpy(out, token, length + 1u);
    return true;
}

static bool append_event(CoreAppScenario *parsed, const CoreAppScenarioEvent *event) {
    if (parsed->event_count == parsed->event_capacity) {
        u32 capacity = parsed->event_capacity == 0u ? 16u : parsed->event_capacity * 2u;
        CoreAppScenarioEvent *events;
        if (capacity > CORE_APP_SCENARIO_MAX_EVENTS) {
            capacity = CORE_APP_SCENARIO_MAX_EVENTS;
        }
        if (parsed->event_count == capacity) return false;
        events = (CoreAppScenarioEvent *)realloc(parsed->events,
                                                 capacity * sizeof(*events));
        if (!events) return false;
        parsed->events = events;
        parsed->event_capacity = capacity;
    }
    parsed->events[parsed->event_count++] = *event;
    return true;
}

CoreAppScenarioStatus core_app_scenario_parse(const char *text, usize size,
                                              CoreAppScenario *out) {
    CoreAppScenario parsed;
    const char *cursor;
    const char *end;
    bool saw_header = false;
    bool saw_seed = false;
    bool saw_dt = false;
    bool saw_tick = false;
    u32 last_tick = 0u;
    if (!out) return CORE_APP_SCENARIO_INVALID;
    scenario_clear(out);
    if (!text || size > CORE_APP_SCENARIO_MAX_BYTES ||
        memchr(text, '\0', size) != NULL) {
        return CORE_APP_SCENARIO_INVALID;
    }
    memset(&parsed, 0, sizeof(parsed));
    cursor = text;
    end = text + size;
    while (cursor < end) {
        const char *line = cursor;
        const char *newline = memchr(cursor, '\n', (usize)(end - cursor));
        usize length;
        char buffer[CORE_APP_SCENARIO_MAX_LINE + 1u];
        char tick_token[16];
        const char *tick_end;
        usize tick_length;
        char command[32];
        char fields[6][CORE_APP_SCENARIO_PATH_CAPACITY];
        u64 tick = 0u;
        int count;
        CoreAppScenarioEvent event;
        if (newline) {
            length = (usize)(newline - cursor);
            cursor = newline + 1;
        } else {
            length = (usize)(end - cursor);
            cursor = end;
        }
        if (length > 0u && line[length - 1u] == '\r') length--;
        if (length > CORE_APP_SCENARIO_MAX_LINE) goto invalid;
        if (length == 0u || line[0] == '#') continue;
        memcpy(buffer, line, length);
        buffer[length] = '\0';
        if (!saw_header) {
            if (strcmp(buffer, "core-app-scenario 1") != 0) goto invalid;
            saw_header = true;
            continue;
        }
        if (!saw_seed) {
            if (!header_u64(buffer, "seed", false, &parsed.seed)) goto invalid;
            saw_seed = true;
            continue;
        }
        if (!saw_dt) {
            if (!header_u64(buffer, "fixed-dt-ns", true, &parsed.fixed_dt_ns)) {
                goto invalid;
            }
            saw_dt = true;
            continue;
        }
        tick_end = strchr(buffer, ' ');
        if (!tick_end) goto invalid;
        tick_length = (usize)(tick_end - buffer);
        if (tick_length == 0u || tick_length >= sizeof(tick_token)) goto invalid;
        memcpy(tick_token, buffer, tick_length);
        tick_token[tick_length] = '\0';
        memset(command, 0, sizeof(command));
        memset(fields, 0, sizeof(fields));
        count = sscanf(buffer, "%*s %31s %255s %255s %255s %255s %255s %255s",
                       command, fields[0], fields[1], fields[2], fields[3],
                       fields[4], fields[5]);
        if (count < 1 || parsed.has_quit ||
            !decimal_u64(tick_token, CORE_APP_SCENARIO_MAX_TICK, &tick) ||
            tick == 0u || (saw_tick && (u32)tick < last_tick)) {
            goto invalid;
        }
        memset(&event, 0, sizeof(event));
        event.tick = (u32)tick;
        if (strcmp(command, "key") == 0 && count == 3 &&
            (strcmp(fields[1], "0") == 0 || strcmp(fields[1], "1") == 0) &&
            key_code(fields[0], &event.key_code)) {
            event.kind = CORE_APP_SCENARIO_KEY;
            event.key_down = fields[1][0] == '1';
        } else if (strcmp(command, "touch") == 0 && count == 5 &&
                   decimal_i64(fields[0], &event.touch_source) &&
                   touch_phase(fields[1], &event.touch_phase) &&
                   finite_number(fields[2], 0.0f, 1.0f, &event.x) &&
                   finite_number(fields[3], 0.0f, 1.0f, &event.y)) {
            event.kind = CORE_APP_SCENARIO_TOUCH;
        } else if (strcmp(command, "pad") == 0 && count == 4) {
            u64 pad = 0u;
            u64 axis = 0u;
            if (!decimal_u64(fields[0], 3u, &pad) ||
                !decimal_u64(fields[1], 5u, &axis) ||
                !finite_number(fields[2], -1.0f, 1.0f, &event.value)) {
                goto invalid;
            }
            event.kind = CORE_APP_SCENARIO_PAD;
            event.pad = (u32)pad;
            event.axis = (u32)axis;
        } else if (strcmp(command, "flow") == 0 && count == 3) {
            u64 key = 0u;
            if (!decimal_u64(fields[0], UINT32_MAX, &key) ||
                !finite_number(fields[1], -1.0e6f, 1.0e6f, &event.value)) {
                goto invalid;
            }
            event.kind = CORE_APP_SCENARIO_FLOW;
            event.flow_key = (u32)key;
        } else if (strcmp(command, "save") == 0 && count == 1) {
            event.kind = CORE_APP_SCENARIO_SAVE;
        } else if (strcmp(command, "save-to") == 0 && count == 2 &&
                   relative_path(event.path, fields[0])) {
            event.kind = CORE_APP_SCENARIO_SAVE_TO;
        } else if (strcmp(command, "load") == 0 && count == 1) {
            event.kind = CORE_APP_SCENARIO_LOAD;
        } else if (strcmp(command, "load-from") == 0 && count == 2 &&
                   relative_path(event.path, fields[0])) {
            event.kind = CORE_APP_SCENARIO_LOAD_FROM;
        } else if (strcmp(command, "unload") == 0 && count == 1) {
            event.kind = CORE_APP_SCENARIO_UNLOAD;
        } else if (strcmp(command, "screenshot") == 0 && count == 1) {
            event.kind = CORE_APP_SCENARIO_SCREENSHOT;
        } else if (strcmp(command, "level") == 0 && (count == 1 || count == 2)) {
            if (count == 2 && !asset_root(event.path, fields[0])) goto invalid;
            event.kind = CORE_APP_SCENARIO_LEVEL;
        } else if (strcmp(command, "quit") == 0 && count == 1) {
            event.kind = CORE_APP_SCENARIO_QUIT;
            parsed.has_quit = true;
        } else {
            goto invalid;
        }
        if (!append_event(&parsed, &event)) goto invalid;
        last_tick = event.tick;
        saw_tick = true;
    }
    if (!saw_header || !saw_seed || !saw_dt || !parsed.has_quit) goto invalid;
    *out = parsed;
    return CORE_APP_SCENARIO_OK;

invalid:
    scenario_clear(&parsed);
    return CORE_APP_SCENARIO_INVALID;
}

CoreAppScenarioStatus core_app_scenario_load(const char *path,
                                             CoreAppScenario *out) {
    FILE *file;
    char *bytes;
    usize size;
    CoreAppScenarioStatus status;
    if (!out) return CORE_APP_SCENARIO_INVALID;
    scenario_clear(out);
    if (!path) return CORE_APP_SCENARIO_INVALID;
    file = fopen(path, "rb");
    if (!file) return CORE_APP_SCENARIO_IO;
    bytes = (char *)malloc(CORE_APP_SCENARIO_MAX_BYTES + 1u);
    if (!bytes) {
        fclose(file);
        return CORE_APP_SCENARIO_IO;
    }
    size = fread(bytes, 1u, CORE_APP_SCENARIO_MAX_BYTES + 1u, file);
    if (ferror(file)) {
        free(bytes);
        fclose(file);
        return CORE_APP_SCENARIO_IO;
    }
    fclose(file);
    status = core_app_scenario_parse(bytes, size, out);
    free(bytes);
    return status;
}
