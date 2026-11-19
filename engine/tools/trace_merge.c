/* trace_merge: merges break.trace Chrome trace documents written by several
 * processes into one timeline (core/trace_merge.h).
 *
 *   trace_merge --out MERGED.json [--label NAME] [--offset-us N] IN.json ...
 *   trace_merge --out MERGED.json --clock-offset SERVER.trace SERVER.json PEER.json
 *   trace_merge --out MERGED.json --clock-offset SERVER.trace SERVER.json
 *               --session N PEER.json [--session M PEER2.json ...]
 *   trace_merge --out MERGED.json --clock-offset SERVER.trace SERVER.json
 *               PEER.json PEER2.json          (peers name their own session)
 *
 * Input k (1-based) gets pid k. --label and --offset-us apply to the next
 * input only. --clock-offset reads the single event=network_clock_offset
 * line of a core_app server text trace (offset = peer minus server) and
 * shifts whichever of the two inputs is behind; it needs exactly two inputs
 * and no --offset-us. With several peers, --session N before each peer input
 * picks that session's line (the first input, the server, takes none), and
 * every input is moved onto one timeline. Exit codes: 0 merged, 1
 * read/merge/write failure or no usable clock offset, 2 usage. */
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
    bool has_session;
    u64 session;
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
         "       trace_merge --out PATH --clock-offset SERVER_TRACE SERVER.json\n"
         "                   --session N PEER.json [--session M PEER.json ...]\n"
         "  Input k gets pid k; --label and --offset-us apply to the next input.\n"
         "  --clock-offset aligns the inputs with the server's traced clock offsets;\n"
         "  --session N names the peer session of the next input; without it a peer\n"
         "  trace that carries event=network_session_welcome names its own.");
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

/* a canonical decimal: no sign, no leading zero */
static bool parse_session(const char *value, u64 *out)
{
    if (value[0] == '0' && value[1] != '\0') return false;
    return parse_offset(value, out);
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

static int clock_offset_failure(BreakTraceClockOffsetStatus status, const ToolInput *peer,
                                const char *path)
{
    char which[48] = "";
    if (peer->has_session) {
        snprintf(which, sizeof which, " for session %llu", (unsigned long long)peer->session);
    }
    if (status == BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND) {
        fprintf(stderr, "trace_merge: no network_clock_offset line%s in %s\n", which, path);
    } else if (status == BREAK_TRACE_CLOCK_OFFSET_AMBIGUOUS) {
        fprintf(stderr, "trace_merge: several network_clock_offset lines%s in %s; use %s\n",
                which, path, peer->has_session ? "--offset-us" : "--session or --offset-us");
    } else {
        fprintf(stderr, "trace_merge: malformed network_clock_offset line%s in %s\n", which,
                path);
    }
    return 1;
}

/* Applies the offsets traced by a core_app server: input 0 is the server,
 * the others its peers. A peer's session comes from --session, from the
 * peer's own network_session_welcome line, or (for a single peer) from the
 * server's only clock line. */
static int apply_clock_offset(const char *path, ToolInput *inputs, u32 count)
{
    char *text = NULL;
    usize size = 0u;
    if (!read_file(path, &text, &size)) {
        free(text);
        fprintf(stderr, "trace_merge: cannot read %s\n", path);
        return 1;
    }
    static i64 offsets[TRACE_MERGE_MAX_INPUTS];
    static u64 shifts[TRACE_MERGE_MAX_INPUTS];
    static u64 errors[TRACE_MERGE_MAX_INPUTS];
    for (u32 i = 1u; i < count; ++i) {
        ToolInput *peer = &inputs[i];
        /* a peer document that names its own session needs no --session:
         * read it from the peer's own bytes before falling back. This runs
         * for a single peer too, so a server trace whose only clock line
         * carries session= is matched by session rather than by being the
         * only one. */
        if (!peer->has_session) {
            char *peer_text = NULL;
            usize peer_size = 0u;
            if (read_file(peer->path, &peer_text, &peer_size)) {
                u64 session = 0u;
                /* the inputs are converted documents, so the welcome line
                 * is a JSON event rather than a trace line */
                if (break_trace_core_app_session_from_chrome(peer_text, peer_size,
                                                             &session) ==
                    BREAK_TRACE_CLOCK_OFFSET_OK) {
                    peer->has_session = true;
                    peer->session = session;
                    printf("trace_merge: %s names session=%llu\n", peer->path,
                           (unsigned long long)session);
                }
            }
            free(peer_text);
        }
        BreakTraceClockOffsetStatus status =
            peer->has_session
                ? break_trace_core_app_clock_offset_for_session(text, size, peer->session,
                                                                &offsets[i - 1u], &errors[i - 1u])
                : break_trace_core_app_clock_offset(text, size, &offsets[i - 1u],
                                                    &errors[i - 1u]);
        if (status != BREAK_TRACE_CLOCK_OFFSET_OK) {
            free(text);
            return clock_offset_failure(status, peer, path);
        }
    }
    free(text);
    if (!clock_offset_merge_shifts_many(offsets, count - 1u, &inputs[0].offset_us, shifts)) {
        fprintf(stderr, "trace_merge: no peer input\n");
        return 1;
    }
    for (u32 i = 1u; i < count; ++i) {
        inputs[i].offset_us = shifts[i - 1u];
        if (inputs[i].has_session) {
            printf("trace_merge: clock offset session=%llu offset_us=%lld error_us=%llu\n",
                   (unsigned long long)inputs[i].session, (long long)offsets[i - 1u],
                   (unsigned long long)errors[i - 1u]);
        } else {
            printf("trace_merge: clock offset offset_us=%lld error_us=%llu\n",
                   (long long)offsets[i - 1u], (unsigned long long)errors[i - 1u]);
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    static ToolInput inputs[TRACE_MERGE_MAX_INPUTS];
    const char *out_path = NULL;
    const char *pending_label = NULL;
    const char *clock_path = NULL;
    u64 pending_offset = 0u;
    u64 pending_session = 0u;
    bool pending_has_session = false;
    u32 sessions = 0u;
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
            strcmp(arg, "--offset-us") == 0 || strcmp(arg, "--clock-offset") == 0 ||
            strcmp(arg, "--session") == 0) {
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
            } else if (arg[2] == 's') {
                if (!parse_session(value, &pending_session)) {
                    return usage_error("--session requires a nonnegative integer");
                }
                pending_has_session = true;
                pending = true;
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
            inputs[count++] = (ToolInput){arg, pending_label, pending_offset,
                                          pending_has_session, pending_session, NULL, 0u};
            if (pending_has_session) sessions++;
            pending_label = NULL;
            pending_offset = 0u;
            pending_has_session = false;
            pending = false;
        }
    }
    if (pending) return usage_error("--label/--offset-us/--session must precede an input");
    if (!out_path) return usage_error("--out is required");
    if (count == 0u) return usage_error("at least one input is required");
    if (clock_path && any_offset) {
        return usage_error("--clock-offset cannot be combined with --offset-us");
    }
    if (sessions > 0u && !clock_path) return usage_error("--session needs --clock-offset");
    if (sessions > 0u && inputs[0].has_session) {
        return usage_error("the first input is the server and takes no --session");
    }
    if (sessions > 0u && sessions != count - 1u) {
        return usage_error("every peer input needs --session");
    }
    /* one input has no peer to align; with more than two every peer needs a
     * session, from --session or from its own trace, and
     * apply_clock_offset fails naming the input when neither is there */
    if (clock_path && count < 2u) {
        return usage_error("--clock-offset needs exactly two inputs or --session per peer");
    }

    int rc = clock_path ? apply_clock_offset(clock_path, inputs, count) : 0;
    if (rc == 0) rc = merge_inputs(out_path, inputs, count);
    for (u32 i = 0u; i < count; ++i) free(inputs[i].text);
    return rc;
}
