#define _POSIX_C_SOURCE 200809L
/* break_crash_e2e — the CLIENT half of the crash-reporting end-to-end test. It
 * uses the real capture (break_crash), the real spool and the real HTTP
 * transport; the cmake script test_break_crash_e2e.cmake drives the reference
 * server and the report tool around it.
 *
 *   break_crash_e2e build-id
 *   break_crash_e2e crash   <spool>                          faults for real (SIGSEGV in leaf())
 *   break_crash_e2e upload  <spool> <base url> <ca pem|->    one upload pass over the spool
 *   break_crash_e2e status  <spool>                          pending / sent / discarded counts
 *   break_crash_e2e post    <url> <ca pem|-> <file> <content-type>   raw POST, prints status=
 *   break_crash_e2e forge   <out> <build-id> <signo>         a minimal record from the builder
 *   break_crash_e2e rebuild <in> <out> <build-id>            the same crash as if from another build
 *   break_crash_e2e spool-put <spool> <file>                 stage a record file as pending
 * Stdout carries `key=value` lines for the script. Exit 0 = ok, 1 = failure, 2 = usage. */
#include <core/break_version.h>
#include <crash/break_crash.h>
#include <crash/break_crash_upload_http.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __has_feature
#define __has_feature(x) 0
#endif
#if defined(__SANITIZE_ADDRESS__) || __has_feature(address_sanitizer)
/* the crash handler replaces the sanitizer runtime's SIGSEGV handler */
const char *__asan_default_options(void) {
    return "allow_user_segv_handler=1";
}
#endif

static volatile int *g_null;

/* The faulting path carries no sanitizer instrumentation: ASan's shadow checks and UBSan's
 * null-store check must not intercept the fault before the break_crash handler runs, and the
 * handler copies the 4 KiB of stack above the faulting rsp, which must not contain poisoned
 * redzones of instrumented frames (the attributes test_break_crash.c uses for its children). */
#define NOSAN __attribute__((noinline, no_sanitize("address"), no_sanitize("undefined"), no_sanitize("thread")))

NOSAN static int leaf(int x) {
    *g_null = x;
    return x;
}
NOSAN static int mid(int x) { return leaf(x + 1) + 1; }
NOSAN static int outer(int x) { return mid(x + 1) + 1; }

NOSAN static int crash_step(const char *spool) {
    BreakCrashConfig cfg;
    cfg.spool_root = spool;
    if (!break_crash_install(&cfg)) return 1;
    return outer(1);
}

static u8 *read_all(const char *path, usize *len) {
    FILE *f = fopen(path, "rb");
    u8 *buf;
    long n;
    if (f == NULL) return NULL;
    if (fseek(f, 0, SEEK_END) != 0 || (n = ftell(f)) < 0 || n > 4 * 1024 * 1024 || fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return NULL;
    }
    buf = (u8 *)malloc((usize)n + 1u);
    if (buf == NULL || fread(buf, 1u, (usize)n, f) != (usize)n) {
        fclose(f);
        free(buf);
        return NULL;
    }
    fclose(f);
    *len = (usize)n;
    return buf;
}

static bool write_all(const char *path, const void *data, usize len) {
    FILE *f = fopen(path, "wb");
    bool ok = f != NULL && fwrite(data, 1u, len, f) == len;
    if (f != NULL && fclose(f) != 0) ok = false;
    return ok;
}

static const char *build_id(void) {
    const char *v = break_version_string();
    const char *plus = strchr(v, '+');
    return plus != NULL && plus[1] != '\0' ? plus + 1 : "unknown";
}

static int usage(void) {
    fprintf(stderr, "usage: break_crash_e2e build-id | crash <spool> | upload <spool> <url> <ca|-> | status <spool> |\n"
                    "       spool-put <spool> <file> | post <url> <ca|-> <file> <content-type> | forge <out> <build-id> <signo> |\n"
                    "       rebuild <in> <out> <build-id>\n");
    return 2;
}

static void print_counts(BreakCrashSpool *s) {
    printf("pending=%llu sent=%llu discarded=%llu\n", (unsigned long long)break_crash_spool_count(s, 0),
           (unsigned long long)break_crash_spool_count(s, 1), (unsigned long long)break_crash_spool_count(s, 2));
}

static int run_step(int argc, char **argv) {
    const char *step;
    if (argc < 2) return usage();
    step = argv[1];
    if (strcmp(step, "build-id") == 0 && argc == 2) {
        printf("%s\n", build_id());
        return 0;
    }
    if (strcmp(step, "status") == 0 && argc == 3) {
        BreakCrashSpool *s = break_crash_spool_open(argv[2]);
        if (s == NULL) return 1;
        print_counts(s);
        break_crash_spool_destroy(s);
        return 0;
    }
    if (strcmp(step, "upload") == 0 && argc == 5) {
        BreakCrashUploadHttp ctx;
        BreakCrashSpool *s = break_crash_spool_open(argv[2]);
        u32 sent;
        if (s == NULL) return 1;
        memset(&ctx, 0, sizeof(ctx));
        ctx.cfg.ca_file = strcmp(argv[4], "-") == 0 ? NULL : argv[4];
        ctx.cfg.io_timeout_ms = 8000u;
        if (strlen(argv[3]) >= sizeof(ctx.base_url)) return 2;
        memcpy(ctx.base_url, argv[3], strlen(argv[3]) + 1u);
        sent = break_crash_spool_upload_pending(s, break_crash_upload_http, &ctx);
        printf("uploaded=%u\n", sent);
        print_counts(s);
        break_crash_spool_destroy(s);
        return 0;
    }
    if (strcmp(step, "post") == 0 && argc == 6) {
        BreakHttpConfig cfg;
        usize len = 0, rl = 0;
        u8 *body = read_all(argv[4], &len);
        u8 resp[256];
        int status = 0;
        BreakHttpError e;
        if (body == NULL) return 1;
        memset(&cfg, 0, sizeof(cfg));
        cfg.ca_file = strcmp(argv[3], "-") == 0 ? NULL : argv[3];
        cfg.io_timeout_ms = 8000u;
        e = break_http_post(&cfg, argv[2], body, len, argv[5], resp, sizeof(resp) - 1u, &rl, &status);
        free(body);
        resp[rl] = '\0';
        printf("error=%s status=%d\n", break_http_error_name(e), status);
        if (e == BHTTP_OK) printf("body=%s", (const char *)resp);
        return e == BHTTP_OK ? 0 : 1;
    }
    if (strcmp(step, "forge") == 0 && argc == 5) {
        BreakCrashRecordBuilder *b = break_crash_record_builder_create();
        u8 text[BREAK_CRASH_RECORD_MAX];
        usize n;
        if (b == NULL) return 1;
        break_crash_record_builder_set_signal(b, atoi(argv[4]), 1, 0);
        break_crash_record_builder_set_process(b, 4242u, 4242u);
        break_crash_record_builder_set_registers(b, 0x401000u, 0x7ffd0000u, 0x7ffd0020u);
        break_crash_record_builder_set_build_id(b, argv[3]);
        (void)break_crash_record_builder_add_module(b, "break_crash_e2e", 0x400000u, 0x10000u);
        n = break_crash_record_builder_finish(b, text, sizeof(text));
        break_crash_record_builder_destroy(b);
        return n != 0u && write_all(argv[2], text, n) ? 0 : 1;
    }
    if (strcmp(step, "spool-put") == 0 && argc == 4) {
        usize len = 0;
        u8 *rec = read_all(argv[3], &len);
        BreakCrashSpool *s = break_crash_spool_open(argv[2]);
        bool ok = rec != NULL && s != NULL && break_crash_spool_put_pending(s, rec, len);
        free(rec);
        break_crash_spool_destroy(s);
        return ok ? 0 : 1;
    }
    if (strcmp(step, "rebuild") == 0 && argc == 5) {
        usize len = 0, n;
        u8 *in = read_all(argv[2], &len);
        BreakCrashRecord *r = in != NULL ? break_crash_record_parse(in, len) : NULL;
        BreakCrashRecordBuilder *b = break_crash_record_builder_create();
        static u8 text[BREAK_CRASH_RECORD_MAX];
        u64 regs[3], modules;
        const u8 *win = NULL, *ctxb = NULL;
        usize wlen, clen;
        if (r == NULL || b == NULL) return 1;
        break_crash_record_registers(r, regs);
        break_crash_record_builder_set_signal(b, break_crash_record_signo(r), 1, break_crash_record_fault_addr(r));
        break_crash_record_builder_set_process(b, break_crash_record_pid(r) + 1u, break_crash_record_tid(r) + 1u);
        break_crash_record_builder_set_registers(b, regs[0], regs[1], regs[2]);
        break_crash_record_builder_set_build_id(b, argv[4]);
        modules = break_crash_record_module_count(r);
        for (u64 i = 0; i < modules; i++) {
            const char *name = NULL;
            u64 off = 0, size = 0;
            if (break_crash_record_module_at(r, i, &name, &off, &size)) {
                (void)break_crash_record_builder_add_module(b, name, off, size);
            }
        }
        wlen = break_crash_record_stack_window(r, &win);
        clen = break_crash_record_context_blob(r, &ctxb);
        break_crash_record_builder_set_stack_window(b, win, wlen);
        break_crash_record_builder_set_context_blob(b, ctxb, clen);
        n = break_crash_record_builder_finish(b, text, sizeof(text));
        break_crash_record_builder_destroy(b);
        break_crash_record_destroy(r);
        free(in);
        return n != 0u && write_all(argv[3], text, n) ? 0 : 1;
    }
    return usage();
}

/* main holds no locals, so the frame the crash handler reads above the fault is clean. */
NOSAN int main(int argc, char **argv) {
    if (argc == 3 && strcmp(argv[1], "crash") == 0) return crash_step(argv[2]);
    return run_step(argc, argv);
}
