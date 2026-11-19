/* trace_convert: turns a core_app text trace into the Chrome trace-event
 * document trace_merge reads (core/trace_core_app.h).
 *
 *   trace_convert IN.trace OUT.json
 *
 * Exit codes: 0 converted, 1 read/convert/write failure, 2 usage. */
#include <core/trace_core_app.h>

#include <stdio.h>
#include <stdlib.h>

static char *read_all(const char *path, usize *size)
{
    FILE *f = fopen(path, "rb");
    long length = -1;
    char *text = NULL;
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) == 0) length = ftell(f);
    if (length >= 0 && fseek(f, 0, SEEK_SET) == 0) {
        text = malloc((usize)length + 1u);
        if (text && fread(text, 1u, (usize)length, f) == (usize)length) {
            text[length] = '\0';
            *size = (usize)length;
        } else {
            free(text);
            text = NULL;
        }
    }
    fclose(f);
    return text;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: trace_convert IN.trace OUT.json\n");
        return 2;
    }
    usize size = 0u;
    char *text = read_all(argv[1], &size);
    if (!text) {
        fprintf(stderr, "trace_convert: cannot read %s\n", argv[1]);
        return 1;
    }
    BreakTraceCoreAppReport report;
    if (break_trace_core_app_to_chrome(text, size, NULL, 0u, &report) !=
        BREAK_TRACE_CONVERT_TOO_SMALL) {
        free(text);
        fprintf(stderr, "trace_convert: cannot size %s\n", argv[1]);
        return 1;
    }
    char *json = malloc(report.bytes + 1u);
    if (!json || break_trace_core_app_to_chrome(text, size, json, report.bytes + 1u,
                                                &report) != BREAK_TRACE_CONVERT_OK) {
        free(json);
        free(text);
        fprintf(stderr, "trace_convert: cannot convert %s\n", argv[1]);
        return 1;
    }
    free(text);
    FILE *out = fopen(argv[2], "wb");
    bool ok = out && fwrite(json, 1u, report.bytes, out) == report.bytes;
    if (out) ok = fclose(out) == 0 && ok;
    free(json);
    if (!ok) {
        fprintf(stderr, "trace_convert: cannot write %s\n", argv[2]);
        return 1;
    }
    printf("trace_convert: %u events, %u skipped -> %s\n", report.events, report.skipped,
           argv[2]);
    return 0;
}
