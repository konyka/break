/* Mutation fuzzer for the scenario text parser.
 *
 * Mutates a valid scenario in every lexical dimension the parser claims to
 * validate (length, tick, coordinates, commands, paths) and requires the
 * parser to either accept the text or classify it as INVALID/IO. A partial
 * parse that leaves events behind on a rejected document is a bug: callers
 * rely on a rejected scenario having event_count == 0.
 *
 * Usage:
 *   fuzz_core_app_scenario [iterations] [seed]   random mutation run
 *   fuzz_core_app_scenario --emit-corpus <dir>   write the fixed text samples
 *   fuzz_core_app_scenario --replay <file>...    load each sample through
 *       core_app_scenario_load and check it against its `accept-` or
 *       `reject-` file prefix; both prefixes must appear at least once. */

#include "../apps/core_app/scenario.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

static const char k_base[] =
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "2 key w 1\n"
    "3 key w 0\n"
    "4 touch 0 down 0.5 0.25\n"
    "5 pad 0 0 0.5\n"
    "6 flow 7 1.0\n"
    "7 quit\n";

static const char *k_substitutions[] = {
    "core-app-scenario 2\n", "core-app-scenario 0\n", "core-app-scenario\n",
    "seed -1\n", "seed abc\n", "seed\n",
    "fixed-dt-ns 0\n", "fixed-dt-ns -5\n", "fixed-dt-ns\n",
    "0 level\n", "1 level /../../etc/passwd\n", "1048577 level\n",
    "2 key\n", "2 key w 2\n", "2 key unknown 1\n",
    "4 touch 0 bogus 1.0 1.0\n", "4 touch 0 move nan 1.0\n", "4 touch 0 move 1e999 1.0\n",
    "4 touch 0 move 1.5 -2.25\n",
    "5 pad 0 99 0.5\n", "5 pad 4294967296 0 0.5\n",
    "6 flow 0\n", "6 flow 7 1.0e9\n", "7 screenshot\n", "8 quit\n", "9 quit\n"
};

static void copy_scenario(char *out, size_t capacity, const char *text) {
    size_t length = strlen(text);
    if (length + 1u > capacity) length = capacity - 1u;
    memcpy(out, text, length);
    out[length] = '\0';
}

static long parse_and_check(const char *text, usize size) {
    CoreAppScenario scenario;
    memset(&scenario, 0, sizeof(scenario));
    CoreAppScenarioStatus status = core_app_scenario_parse(text, size, &scenario);
    if (status == CORE_APP_SCENARIO_OK) {
        if (scenario.event_count > CORE_APP_SCENARIO_MAX_EVENTS) {
            fprintf(stderr, "fuzz_core_app_scenario: accepted %u events over the limit\n",
                    scenario.event_count);
            free(scenario.events);
            return -1;
        }
        free(scenario.events);
        return 1;
    }
    if (scenario.event_count != 0u) {
        fprintf(stderr,
                "fuzz_core_app_scenario: rejected text left %u partial events\n",
                scenario.event_count);
        free(scenario.events);
        return -1;
    }
    free(scenario.events);
    return 0;
}

/* The file name prefix before the first '-' names the expected status. */
static int corpus_expectation(const char *path) {
    const char *base = path;
    for (const char *p = path; *p; ++p) {
        if (*p == '/' || *p == '\\') base = p + 1;
    }
    if (strncmp(base, "accept-", 7u) == 0) return 1;
    if (strncmp(base, "reject-", 7u) == 0) return 0;
    return -1;
}

static int replay_one(const char *path, int *accepted, int *rejected) {
    int expect = corpus_expectation(path);
    if (expect < 0) {
        fprintf(stderr, "fuzz_core_app_scenario: %s: unknown prefix\n", path);
        return 1;
    }
    CoreAppScenario scenario;
    memset(&scenario, 0, sizeof(scenario));
    CoreAppScenarioStatus status = core_app_scenario_load(path, &scenario);
    int rc = 1;
    if (expect == 0) {
        if (status != CORE_APP_SCENARIO_INVALID) {
            fprintf(stderr, "fuzz_core_app_scenario: %s: status=%d, expected INVALID\n", path,
                    (int)status);
        } else if (scenario.event_count != 0u || scenario.events != NULL) {
            fprintf(stderr, "fuzz_core_app_scenario: %s: rejected file left events\n", path);
        } else {
            (*rejected)++;
            rc = 0;
        }
        free(scenario.events);
        return rc;
    }
    if (status != CORE_APP_SCENARIO_OK) {
        fprintf(stderr, "fuzz_core_app_scenario: %s: status=%d, expected OK\n", path,
                (int)status);
    } else if (scenario.event_count == 0u ||
               scenario.event_count > CORE_APP_SCENARIO_MAX_EVENTS || !scenario.has_quit ||
               scenario.events[scenario.event_count - 1u].kind != CORE_APP_SCENARIO_QUIT) {
        fprintf(stderr, "fuzz_core_app_scenario: %s: accepted %u events without a final quit\n",
                path, scenario.event_count);
    } else {
        rc = 0;
        u32 last = 0u;
        for (u32 i = 0u; i < scenario.event_count; ++i) {
            u32 tick = scenario.events[i].tick;
            if (tick == 0u || tick > CORE_APP_SCENARIO_MAX_TICK || tick < last) {
                fprintf(stderr, "fuzz_core_app_scenario: %s: event %u has tick %u\n", path, i,
                        tick);
                rc = 1;
                break;
            }
            last = tick;
        }
        if (rc == 0) (*accepted)++;
    }
    free(scenario.events);
    return rc;
}

static int replay_corpus(int count, char **paths) {
    int accepted = 0;
    int rejected = 0;
    for (int i = 0; i < count; ++i) {
        if (replay_one(paths[i], &accepted, &rejected) != 0) return 1;
    }
    if (accepted == 0 || rejected == 0) {
        fprintf(stderr, "fuzz_core_app_scenario: corpus needs accept and reject files "
                "(accept=%d reject=%d)\n", accepted, rejected);
        return 1;
    }
    printf("fuzz_core_app_scenario: replayed=%d accept=%d reject=%d\n", count, accepted,
           rejected);
    return 0;
}
#define CORPUS_HEADER "core-app-scenario 1\nseed 1\nfixed-dt-ns 16666667\n"

static int emit_bytes(const char *dir, const char *name, const char *bytes, size_t size) {
    char path[1024];
    int n = snprintf(path, sizeof(path), "%s/%s.scenario", dir, name);
    if (n < 0 || (size_t)n >= sizeof(path)) return 1;
    FILE *file = fopen(path, "wb");
    if (!file) {
        fprintf(stderr, "fuzz_core_app_scenario: cannot write %s\n", path);
        return 1;
    }
    size_t written = size ? fwrite(bytes, 1u, size, file) : 0u;
    int closed = fclose(file);
    return written == size && closed == 0 ? 0 : 1;
}

static int emit_text(const char *dir, const char *name, const char *text) {
    return emit_bytes(dir, name, text, strlen(text));
}

/* Header, then `keys` key events at tick 1, then quit. */
static size_t build_many_events(char *out, size_t capacity, unsigned keys) {
    size_t used = (size_t)snprintf(out, capacity, "%s", CORPUS_HEADER);
    for (unsigned i = 0u; i < keys && used + 16u < capacity; ++i) {
        used += (size_t)snprintf(out + used, capacity - used, "1 key w %u\n", i & 1u);
    }
    used += (size_t)snprintf(out + used, capacity - used, "2 quit\n");
    return used;
}

/* Header, one comment line of exactly `line_bytes` bytes, then quit. */
static size_t build_long_line(char *out, size_t capacity, size_t line_bytes) {
    size_t used = (size_t)snprintf(out, capacity, "%s", CORPUS_HEADER);
    out[used++] = '#';
    for (size_t i = 1u; i < line_bytes; ++i) out[used++] = (char)('a' + i % 26u);
    used += (size_t)snprintf(out + used, capacity - used, "\n1 quit\n");
    return used;
}

static int emit_corpus(const char *dir) {
    enum { k_big = CORE_APP_SCENARIO_MAX_BYTES + 4096 };
    char *big = (char *)malloc(k_big);
    if (!big) return 1;
    int rc = 0;
    size_t size;

    rc |= emit_text(dir, "accept-minimal", CORPUS_HEADER "1 quit\n");
    rc |= emit_text(dir, "accept-every_command", CORPUS_HEADER
                    "1 level\n"
                    "1 level assets/core_app\n"
                    "2 key w 1\n"
                    "2 key space 0\n"
                    "2 key Z 1\n"
                    "3 touch 0 down 0.5 0.25\n"
                    "3 touch -9223372036854775808 move 0 1\n"
                    "3 touch 7 up 1 0\n"
                    "3 touch 7 cancel 0.0 0.0\n"
                    "4 pad 3 5 -1\n"
                    "4 pad 0 0 1.0\n"
                    "5 flow 4294967295 1000000\n"
                    "5 flow 0 -1e6\n"
                    "6 save\n"
                    "6 save-to slot/a\n"
                    "7 load\n"
                    "7 load-from slot/a\n"
                    "8 screenshot\n"
                    "9 unload\n"
                    "10 quit\n");
    rc |= emit_text(dir, "accept-crlf", "core-app-scenario 1\r\nseed 1\r\nfixed-dt-ns 1\r\n"
                    "1 key w 1\r\n2 quit\r\n");
    rc |= emit_text(dir, "accept-comments_and_blank_lines",
                    "# leading comment\n\ncore-app-scenario 1\n#\nseed 0\n\n"
                    "fixed-dt-ns 16666667\n# between events\n1 key w 1\n\n2 quit\n");
    rc |= emit_text(dir, "accept-no_trailing_newline", CORPUS_HEADER "1 quit");
    rc |= emit_text(dir, "accept-max_tick", CORPUS_HEADER "1048576 quit\n");
    rc |= emit_text(dir, "accept-same_tick", CORPUS_HEADER "5 key w 1\n5 key w 0\n5 quit\n");
    rc |= emit_text(dir, "accept-max_seed",
                    "core-app-scenario 1\nseed 18446744073709551615\n"
                    "fixed-dt-ns 18446744073709551615\n1 quit\n");
    size = build_many_events(big, k_big, CORE_APP_SCENARIO_MAX_EVENTS - 1u);
    rc |= emit_bytes(dir, "accept-max_events", big, size);
    size = build_long_line(big, k_big, CORE_APP_SCENARIO_MAX_LINE);
    rc |= emit_bytes(dir, "accept-max_line", big, size);

    rc |= emit_text(dir, "reject-empty", "");
    rc |= emit_text(dir, "reject-header_only", CORPUS_HEADER);
    rc |= emit_text(dir, "reject-header_version", "core-app-scenario 2\nseed 1\n"
                    "fixed-dt-ns 1\n1 quit\n");
    rc |= emit_text(dir, "reject-missing_seed", "core-app-scenario 1\nfixed-dt-ns 1\n1 quit\n");
    rc |= emit_text(dir, "reject-seed_overflow", "core-app-scenario 1\n"
                    "seed 18446744073709551616\nfixed-dt-ns 1\n1 quit\n");
    rc |= emit_text(dir, "reject-zero_dt", "core-app-scenario 1\nseed 1\nfixed-dt-ns 0\n"
                    "1 quit\n");
    rc |= emit_text(dir, "reject-no_quit", CORPUS_HEADER "1 key w 1\n");
    rc |= emit_text(dir, "reject-tick_zero", CORPUS_HEADER "0 quit\n");
    rc |= emit_text(dir, "reject-tick_over_max", CORPUS_HEADER "1048577 quit\n");
    rc |= emit_text(dir, "reject-tick_decreasing", CORPUS_HEADER "5 key w 1\n4 quit\n");
    rc |= emit_text(dir, "reject-event_after_quit", CORPUS_HEADER "1 quit\n2 key w 1\n");
    rc |= emit_text(dir, "reject-second_quit", CORPUS_HEADER "1 quit\n1 quit\n");
    rc |= emit_text(dir, "reject-parent_path", CORPUS_HEADER "1 save-to slot/../x\n2 quit\n");
    rc |= emit_text(dir, "reject-absolute_path", CORPUS_HEADER "1 load-from /tmp/x\n2 quit\n");
    rc |= emit_text(dir, "reject-touch_out_of_range", CORPUS_HEADER
                    "1 touch 0 move 1.5 0.5\n2 quit\n");
    rc |= emit_text(dir, "reject-touch_nan", CORPUS_HEADER "1 touch 0 move nan 0.5\n2 quit\n");
    rc |= emit_text(dir, "reject-touch_phase", CORPUS_HEADER "1 touch 0 hover 0.5 0.5\n2 quit\n");
    rc |= emit_text(dir, "reject-pad_axis", CORPUS_HEADER "1 pad 0 6 0.5\n2 quit\n");
    rc |= emit_text(dir, "reject-pad_index", CORPUS_HEADER "1 pad 4 0 0.5\n2 quit\n");
    rc |= emit_text(dir, "reject-flow_overflow", CORPUS_HEADER "1 flow 4294967296 1\n2 quit\n");
    rc |= emit_text(dir, "reject-flow_value", CORPUS_HEADER "1 flow 1 1.0e9\n2 quit\n");
    rc |= emit_text(dir, "reject-key_state", CORPUS_HEADER "1 key w 2\n2 quit\n");
    rc |= emit_text(dir, "reject-key_name", CORPUS_HEADER "1 key ww 1\n2 quit\n");
    rc |= emit_text(dir, "reject-extra_field", CORPUS_HEADER "1 save now\n2 quit\n");
    rc |= emit_text(dir, "reject-unknown_command", CORPUS_HEADER "1 teleport\n2 quit\n");
    rc |= emit_text(dir, "reject-control_byte", CORPUS_HEADER "1 qu\x01it\n");
    static const char k_nul[] = CORPUS_HEADER "1 quit\n\0";
    rc |= emit_bytes(dir, "reject-nul_byte", k_nul, sizeof(k_nul) - 1u);
    size = build_many_events(big, k_big, CORE_APP_SCENARIO_MAX_EVENTS);
    rc |= emit_bytes(dir, "reject-over_max_events", big, size);
    size = build_long_line(big, k_big, CORE_APP_SCENARIO_MAX_LINE + 1u);
    rc |= emit_bytes(dir, "reject-over_max_line", big, size);
    size = (size_t)snprintf(big, k_big, "%s1 quit\n", CORPUS_HEADER);
    while (size <= CORE_APP_SCENARIO_MAX_BYTES) {
        size += (size_t)snprintf(big + size, k_big - size, "# padding\n");
    }
    rc |= emit_bytes(dir, "reject-over_max_bytes", big, size);

    free(big);
    if (rc == 0) printf("fuzz_core_app_scenario: corpus written to %s\n", dir);
    return rc;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--replay") == 0) return replay_corpus(argc - 2, argv + 2);
    if (argc == 3 && strcmp(argv[1], "--emit-corpus") == 0) return emit_corpus(argv[2]);
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 500L;
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 500L;

    /* The unmutated document must parse, otherwise the fuzzer is measuring
       nothing. */
    if (parse_and_check(k_base, strlen(k_base)) != 1) {
        fprintf(stderr, "fuzz_core_app_scenario: the base document does not parse\n");
        return 1;
    }

    long accepted = 0;
    long rejected = 0;
    long built = 0;
    char buffer[CORE_APP_SCENARIO_MAX_BYTES];
    for (long iteration = 0; iteration < iterations; ++iteration) {
        copy_scenario(buffer, sizeof(buffer), k_base);
        switch (rnd() % 4u) {
            case 0u: {
                /* Substitute one whole line with a hostile variant. */
                unsigned choice = rnd() % (unsigned)(sizeof(k_substitutions) /
                                                     sizeof(k_substitutions[0]));
                const char *needle = strchr(buffer, '\n');
                if (!needle) break;
                needle += 1;
                const char *line_end = strchr(needle, '\n');
                if (!line_end) break;
                char rebuilt[CORE_APP_SCENARIO_MAX_BYTES];
                size_t head = (size_t)(needle - buffer);
                snprintf(rebuilt, sizeof(rebuilt), "%.*s%s%s",
                         (int)head, buffer, k_substitutions[choice], line_end);
                copy_scenario(buffer, sizeof(buffer), rebuilt);
                built++;
                break;
            }
            case 1u: {
                /* Truncate at an arbitrary byte, including inside a token. */
                size_t length = strlen(buffer);
                if (length > 1u) buffer[rnd() % length] = '\0';
                built++;
                break;
            }
            case 2u: {
                /* Flip one byte to a control character. */
                size_t length = strlen(buffer);
                if (length > 0u) buffer[rnd() % length] = (char)(rnd() % 32u);
                built++;
                break;
            }
            default: {
                /* Append digits to a coordinate to overflow the numeric scan. */
                size_t length = strlen(buffer);
                if (length + 32u < sizeof(buffer)) {
                    snprintf(buffer + length, sizeof(buffer) - length,
                             "%u key w 1\n", (unsigned)(1u + rnd() % CORE_APP_SCENARIO_MAX_TICK));
                }
                built++;
                break;
            }
        }
        long result = parse_and_check(buffer, strlen(buffer));
        if (result < 0) return 1;
        if (result == 1) accepted++;
        else rejected++;
    }

    printf("fuzz_core_app_scenario: iterations=%ld built=%ld accepted=%ld rejected=%ld\n",
           iterations, built, accepted, rejected);
    return 0;
}
