#include <rule_engine/rule_engine.h>

#include <stdint.h>
#include <string.h>

enum { SMOKE_ITERATIONS = 256, MAX_SOURCE = 96 };

static uint32_t next_value(uint32_t *state) {
    *state = *state * 1664525u + 1013904223u;
    return *state;
}

static re_string_t text(const char *data) {
    re_string_t result = {data, strlen(data)};
    return result;
}

static void fill_source(uint32_t *state, char *source, size_t capacity) {
    static const char alphabet[] = "rule{}\"whenthen=; <>!&|0123456789ABC_ ";
    size_t length = (size_t)(next_value(state) % (capacity - 1u)) + 1u;
    size_t index;
    for (index = 0u; index < length; ++index) {
        source[index] = alphabet[next_value(state) % (sizeof(alphabet) - 1u)];
    }
    source[length] = '\0';
}

static int smoke_parser_and_evaluator(uint32_t *state) {
    char source[MAX_SOURCE];
    re_program_t *program = NULL;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t value = {RE_VALUE_INT64, {.int64_value = (int64_t)next_value(state)}};
    re_status_t status;
    fill_source(state, source, sizeof(source));
    if (engine == NULL || facts == NULL) {
        re_facts_destroy(facts);
        re_engine_destroy(engine);
        return 0;
    }
    (void)re_facts_set(facts, text("Fuzz.Value"), &value);
    status = re_program_load(NULL, text(source), NULL, &program);
    if (status == RE_STATUS_OK && program != NULL) {
        (void)re_engine_install(engine, program);
        (void)re_engine_run(engine, facts, NULL, NULL);
    } else {
        re_program_destroy(program);
    }
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    return 1;
}

static int smoke_window_and_provider(uint32_t *state) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = NULL;
    re_state_provider_t *provider = NULL;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = (int64_t)next_value(state)}};
    re_stream_window_options_t window_options = {
        sizeof(window_options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_SLIDING, RE_LATE_EVENT_DROP, 100u, 8u, 256u, 10u, 0u};
    re_memory_provider_options_t provider_options = {
        sizeof(provider_options), RE_STATE_PROVIDER_ABI_VERSION,
        4u, 32u, 64u, NULL, NULL};
    re_snapshot_t snapshot = {sizeof(snapshot), 0u, NULL, 0u, NULL, NULL};
    re_status_t status;
    if (engine == NULL) return 0;
    status = re_stream_window_create_v1(engine, &window_options, &window);
    if (status == RE_STATUS_OK) {
        (void)re_stream_window_record_v1(window, next_value(state) % 200u,
                                          text("event"), &value);
        (void)re_stream_window_snapshot(window, &snapshot);
        if (snapshot.release != NULL) snapshot.release(snapshot.release_context,
                                                        snapshot.data, snapshot.size);
        re_stream_window_destroy(window);
    }
    if (re_state_provider_create_memory(engine, &provider_options, &provider) == RE_STATUS_OK) {
        (void)re_state_provider_update(provider, text("key"), &value, next_value(state) % 20u);
        (void)re_state_provider_snapshot(provider, &snapshot);
        if (snapshot.release != NULL) snapshot.release(snapshot.release_context,
                                                        snapshot.data, snapshot.size);
        re_state_provider_destroy(provider);
    }
    re_engine_destroy(engine);
    return 1;
}

int main(void) {
    uint32_t state = 0x5eed1234u;
    unsigned int iteration;
    for (iteration = 0u; iteration < SMOKE_ITERATIONS; ++iteration) {
        if (!smoke_parser_and_evaluator(&state) || !smoke_window_and_provider(&state)) return 1;
    }
    return 0;
}
