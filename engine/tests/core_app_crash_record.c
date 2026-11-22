#include <crash/break_crash.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_USAGE 2
#define EXIT_RECOVERY 3
#define EXIT_PARSE 4
#define EXIT_CONTRACT 5

static int parse_u64(const char *text, u64 *out) {
    u64 value = 0;
    usize i;
    if (!text || !text[0]) return 0;
    for (i = 0; text[i]; ++i) {
        u64 digit;
        if (text[i] < '0' || text[i] > '9') return 0;
        digit = (u64)(text[i] - '0');
        if (value > (UINT64_MAX - digit) / 10u) return 0;
        value = value * 10u + digit;
    }
    *out = value;
    return 1;
}

static int take_line(char **cursor, char **line) {
    char *newline;
    if (!*cursor || !**cursor) return 0;
    *line = *cursor;
    newline = strchr(*cursor, '\n');
    if (!newline) return 0;
    *newline = '\0';
    *cursor = newline + 1;
    return 1;
}

static int take_field(char **cursor, const char *key, char **value) {
    char *line;
    usize key_size = strlen(key);
    usize i;
    if (!take_line(cursor, &line) || strncmp(line, key, key_size) != 0 ||
        line[key_size] != '=') return 0;
    *value = line + key_size + 1u;
    for (i = 0; (*value)[i]; ++i) {
        unsigned char c = (unsigned char)(*value)[i];
        if (c < 0x20u || c > 0x7eu || c == '/' || c == '\\' || c == '=') return 0;
    }
    return 1;
}

static int take_section(char **cursor, const char *section) {
    char *line;
    return take_line(cursor, &line) && strcmp(line, section) == 0;
}

static int check_contract(const BreakCrashRecord *record, u32 expected_tick) {
    static const char *const keys[] = {
        "backend", "gpu", "live", "seen", "dropped", "tick", "keys",
        "pads", "touches", "gestures", "touch_status", "haptic_status"
    };
    char blob[BREAK_CRASH_CONTEXT_BLOB_MAX + 1u];
    char *values[sizeof(keys) / sizeof(keys[0])];
    const u8 *bytes = NULL;
    usize size = break_crash_record_context_blob(record, &bytes);
    char *cursor = blob;
    u64 number;
    usize i;
    if (!bytes || size == 0u || size > BREAK_CRASH_CONTEXT_BLOB_MAX) return 0;
    memcpy(blob, bytes, size);
    blob[size] = '\0';
    if (memchr(blob, '\0', size) != NULL) return 0;
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); ++i) {
        if (i == 0u && !take_section(&cursor, "[rhi]")) return 0;
        if (i == 2u && !take_section(&cursor, "[net]")) return 0;
        if (i == 5u && !take_section(&cursor, "[input]")) return 0;
        if (!take_field(&cursor, keys[i], &values[i])) return 0;
    }
    if ((usize)(cursor - blob) != size) return 0;
    if (strcmp(values[0], "record") != 0 || strcmp(values[1], "none") != 0 ||
        strcmp(values[2], "false") != 0) return 0;
    if (!parse_u64(values[3], &number) || !parse_u64(values[4], &number) ||
        !parse_u64(values[5], &number) || number != expected_tick) return 0;
    if (!parse_u64(values[6], &number) || number != 1u) return 0;
    for (i = 7; i < sizeof(keys) / sizeof(keys[0]); ++i) {
        if (!parse_u64(values[i], &number) || number > UINT32_MAX) return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    BreakCrashSpool *spool = NULL;
    BreakCrashRecord *record = NULL;
    u8 *bytes = NULL;
    u64 byte_count = 0;
    u64 expected_tick = 0;
    int result = EXIT_RECOVERY;

    if (argc != 3 || !parse_u64(argc == 3 ? argv[2] : NULL, &expected_tick) ||
        expected_tick > UINT32_MAX) {
        fprintf(stderr, "usage: core_app_crash_record <spool-root> <expected-tick>\n");
        return EXIT_USAGE;
    }
    spool = break_crash_spool_open(argv[1]);
    if (!spool) goto done;
    if (break_crash_spool_count(spool, 0) != 1u ||
        break_crash_spool_count(spool, 1) != 0u ||
        break_crash_spool_count(spool, 2) != 0u) goto done;
    if (!break_crash_spool_read_pending(spool, 0, &bytes, &byte_count) ||
        byte_count == 0u || byte_count > BREAK_CRASH_RECORD_MAX) goto done;
    record = break_crash_record_parse(bytes, (usize)byte_count);
    if (!record) {
        result = EXIT_PARSE;
        goto done;
    }
    if (!check_contract(record, (u32)expected_tick)) {
        result = EXIT_CONTRACT;
        goto done;
    }
    result = 0;

done:
    break_crash_record_destroy(record);
    free(bytes);
    break_crash_spool_destroy(spool);
    if (result != 0) fprintf(stderr, "core_app_crash_record: exit=%d\n", result);
    return result;
}
