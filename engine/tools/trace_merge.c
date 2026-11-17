/* trace_merge: merges break.trace Chrome trace documents written by several
 * processes into one timeline (core/trace_merge.h).
 *
 *   trace_merge --out MERGED.json [--label NAME] [--offset-us N] IN.json ...
 *   trace_merge --out MERGED.json --clock-offset SERVER.trace SERVER.json PEER.json
 *
 * Input k (1-based) gets pid k. --label and --offset-us apply to the next
 * input only. --clock-offset reads the single event=network_clock_offset
 * line of a core_app server text trace (offset = peer minus server) and
 * shifts whichever of the two inputs is behind; it needs exactly two inputs
 * and no --offset-us. Exit codes: 0 merged, 1 read/merge/write failure or
 * no usable clock offset, 2 usage. */
#include <core/clock_offset.h>
#include <core/trace_core_app.h>
#include <core/trace_merge.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRACE_MERGE_MAX_INPUTS 64u

typedef struct ToolInput {
    const char *path;
    const char *label;
    u64 offset_us;
    char *text;
    usize size;
} ToolInput;

static int usage_error(const char *message)
{
    fprintf(stderr, "trace_merge: %s\n", message);
    return 2;
}

static void print_help(void)
{
    puts("Usage: trace_merge --out PATH [--label NAME] [--offset-us N] INPUT ...\n"
         "       trace_merge --out PATH --clock-offset SERVER_TRACE SERVER.json PEER.json\n"
         "  Input k gets pid k; --label and --offset-us apply to the next input.\n"
         "  --clock-offset aligns the two inputs with the server's traced clock offset.");
}

static bool parse_offset(const char *value, u64 *out)
{
    u64 parsed = 0u;
    for (const char *p = value; *p != '\0'; ++p) {
        if (*p < '0' || *p > '9') return false;
        u64 digit = (u64)(*p - '0');
        if (parsed > (UINT64_MAX - digit) / 10u) return false;
        parsed = parsed * 10u + digit;
    }
    *out = parsed;
    return true;
}

static bool read_file(const char *path, char **text, usize *size)
{
    bool ok = false;
    long length = -1;
    FILE *f = fopen(path, "rb");
    if (!f) return false;
    if (fseek(f, 0, SEEK_END) == 0) length = ftell(f);
    if (length >= 0 && fseek(f, 0, SEEK_SET) == 0) {
        *text = malloc((usize)length + 1u);
        if (*text && fread(*text, 1u, (usize)length, f) == (usize)length) {
            *size = (usize)length;
            ok = true;
        }
    }
    fclose(f);
    return ok;
}

static bool write_file(const char *path, const char *text, usize size)
{
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    bool ok = fwrite(text, 1u, size, f) == size;
    return fclose(f) == 0 && ok;
}

static int merge_inputs(const char *out_path, ToolInput *inputs, u32 count)
{
    BreakTraceMergeInput merge_inputs[TRACE_MERGE_MAX_INPUTS];
    for (u32 i = 0u; i < count; ++i) {
        if (!read_file(inputs[i].path, &inputs[i].text, &inputs[i].size)) {
            fprintf(stderr, "trace_merge: cannot read %s\n", inputs[i].path);
            return 1;
        }
        merge_inputs[i] = (BreakTraceMergeInput){inputs[i].text, inputs[i].size, i + 1u,
                                                 inputs[i].offset_us, inputs[i].label};
    }
    BreakTraceMergeReport report;
    BreakTraceMergeStatus status = break_trace_merge(merge_inputs, count, NULL, 0u, &report);
    if (status == BREAK_TRACE_MERGE_BAD_DOCUMENT) {
        fprintf(stderr, "trace_merge: input %u (%s) is not a break.trace document at line %u\n",
                report.error_input + 1u, inputs[report.error_input].path, report.error_line);
        return 1;
    }
    if (status != BREAK_TRACE_MERGE_TOO_SMALL) {
        fprintf(stderr, "trace_merge: merge failed\n");
        return 1;
    }
    char *merged = malloc((usize)report.bytes + 1u);
    if (!merged || break_trace_merge(merge_inputs, count, merged, (usize)report.bytes + 1u,
                                     &report) != BREAK_TRACE_MERGE_OK) {
        free(merged);
        fprintf(stderr, "trace_merge: merge failed\n");
        return 1;
    }
    bool written = write_file(out_path, merged, (usize)report.bytes);
    free(merged);
    if (!written) {
        fprintf(stderr, "trace_merge: cannot write %s\n", out_path);
        return 1;
    }
    printf("trace_merge: %u inputs, %u events -> %s\n", count, report.events, out_path);
    return 0;
}

/* Applies the offset traced by a core_app server: input 0 is the server,
 * input 1 the peer. */
static int apply_clock_offset(const char *path, ToolInput *inputs)
{
    char *text = NULL;
    usize size = 0u;
    if (!read_file(path, &text, &size)) {
        free(text);
        fprintf(stderr, "trace_merge: cannot read %s\n", path);
        return 1;
    }
    i64 offset_us = 0;
    u64 error_us = 0u;
    BreakTraceClockOffsetStatus status =
        break_trace_core_app_clock_offset(text, size, &offset_us, &error_us);
    free(text);
    if (status == BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND) {
        fprintf(stderr, "trace_merge: no network_clock_offset line in %s\n", path);
        return 1;
    }
    if (status == BREAK_TRACE_CLOCK_OFFSET_AMBIGUOUS) {
        fprintf(stderr, "trace_merge: several network_clock_offset lines in %s; use --offset-us\n",
                path);
        return 1;
    }
    if (status != BREAK_TRACE_CLOCK_OFFSET_OK) {
        fprintf(stderr, "trace_merge: malformed network_clock_offset line in %s\n", path);
        return 1;
    }
    clock_offset_merge_shifts(offset_us, &inputs[0].offset_us, &inputs[1].offset_us);
    printf("trace_merge: clock offset offset_us=%lld error_us=%llu\n", (long long)offset_us,
           (unsigned long long)error_us);
    return 0;
}

int main(int argc, char **argv)
{
    static ToolInput inputs[TRACE_MERGE_MAX_INPUTS];
    const char *out_path = NULL;
    const char *pending_label = NULL;
    const char *clock_path = NULL;
    u64 pending_offset = 0u;
    bool pending = false;
    bool any_offset = false;
    u32 count = 0u;

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];
        if (strcmp(arg, "--out") == 0 || strcmp(arg, "--label") == 0 ||
            strcmp(arg, "--offset-us") == 0 || strcmp(arg, "--clock-offset") == 0) {
            if (i + 1 >= argc || argv[i + 1][0] == '\0') {
                fprintf(stderr, "trace_merge: %s requires a value\n", arg);
                return 2;
            }
            const char *value = argv[++i];
            if (arg[2] == 'o' && arg[3] == 'u') {
                out_path = value;
            } else if (arg[2] == 'c') {
                if (clock_path) return usage_error("--clock-offset given twice");
                clock_path = value;
            } else if (arg[2] == 'l') {
                pending_label = value;
                pending = true;
            } else {
                if (!parse_offset(value, &pending_offset)) {
                    return usage_error("--offset-us requires a nonnegative integer");
                }
                pending = true;
                any_offset = true;
            }
        } else if (arg[0] == '-' && arg[1] == '-') {
            return usage_error("unknown or malformed argument");
        } else {
            if (count == TRACE_MERGE_MAX_INPUTS) return usage_error("too many inputs (max 64)");
            inputs[count++] = (ToolInput){arg, pending_label, pending_offset, NULL, 0u};
            pending_label = NULL;
            pending_offset = 0u;
            pending = false;
        }
    }
    if (pending) return usage_error("--label/--offset-us must precede an input");
    if (!out_path) return usage_error("--out is required");
    if (count == 0u) return usage_error("at least one input is required");
    if (clock_path && any_offset) {
        return usage_error("--clock-offset cannot be combined with --offset-us");
    }
    if (clock_path && count != 2u) return usage_error("--clock-offset needs exactly two inputs");

    int rc = clock_path ? apply_clock_offset(clock_path, inputs) : 0;
    if (rc == 0) rc = merge_inputs(out_path, inputs, count);
    for (u32 i = 0u; i < count; ++i) free(inputs[i].text);
    return rc;
}
