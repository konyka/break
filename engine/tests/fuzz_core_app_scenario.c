/* Mutation fuzzer for the scenario text parser.
 *
 * Mutates a valid scenario in every lexical dimension the parser claims to
 * validate (length, tick, coordinates, commands, paths) and requires the
 * parser to either accept the text or classify it as INVALID/IO. A partial
 * parse that leaves events behind on a rejected document is a bug: callers
 * rely on a rejected scenario having event_count == 0. */

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

int main(int argc, char **argv) {
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
