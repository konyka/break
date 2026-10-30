#define _POSIX_C_SOURCE 200809L
/* break_integrity: tamper signals. Files are hashed against an expected
 * SHA-256; the debugger and module checks read /proc (Linux). */

#include "test_framework.h"

#include <integrity/break_integrity.h>

#include <crypto/break_crypto.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if !defined(_WIN32)
#include <signal.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

static void tmp_path(char *out, usize cap, const char *name) {
    (void)test_tmp(out, cap, name);
}

static bool write_file(const char *path, const void *data, usize n) {
    FILE *f = fopen(path, "wb");
    bool ok = f != NULL && fwrite(data, 1u, n, f) == n;
    if (f != NULL && fclose(f) != 0) ok = false;
    return ok;
}

TEST(matching_file_is_clean_and_a_flipped_byte_is_a_mismatch) {
    char path[300];
    u8 body[100000];
    BreakIntegrityFile f;
    for (usize i = 0; i < sizeof(body); i++) body[i] = (u8)(i * 31u + 7u);
    tmp_path(path, sizeof(path), "integ_ok");
    ASSERT_TRUE(write_file(path, body, sizeof(body)));   /* bigger than one read block */
    ASSERT_TRUE(break_crypto_sha256(body, sizeof(body), f.sha256));
    f.path = path;
    ASSERT_EQ(break_integrity_check_files(&f, 1u), 0u);
    body[sizeof(body) - 1u] ^= 1u;
    ASSERT_TRUE(write_file(path, body, sizeof(body)));
    ASSERT_EQ(break_integrity_check_files(&f, 1u), (u32)BINT_SIG_FILE_MISMATCH);
    /* a shorter file is a mismatch too */
    ASSERT_TRUE(write_file(path, body, 10u));
    ASSERT_EQ(break_integrity_check_files(&f, 1u), (u32)BINT_SIG_FILE_MISMATCH);
    /* an empty file hashed against the right empty digest is clean */
    ASSERT_TRUE(write_file(path, "", 0u));
    ASSERT_TRUE(break_crypto_sha256("", 0u, f.sha256));
    ASSERT_EQ(break_integrity_check_files(&f, 1u), 0u);
    remove(path);
}

TEST(missing_or_unreadable_file_is_a_check_error_not_clean) {
    BreakIntegrityFile f;
    memset(&f, 0, sizeof(f));
    f.path = "/nonexistent/definitely/not/here.bin";
    ASSERT_EQ(break_integrity_check_files(&f, 1u), (u32)BINT_SIG_CHECK_ERROR);
    /* a directory is not a file */
    f.path = test_tmp_root();
    ASSERT_EQ(break_integrity_check_files(&f, 1u), (u32)BINT_SIG_CHECK_ERROR);
}

TEST(mixed_results_combine_and_bad_arguments_are_errors) {
    char good[300], bad[300];
    BreakIntegrityFile f[3];
    u8 a[] = "alpha", b[] = "beta";
    tmp_path(good, sizeof(good), "integ_good");
    tmp_path(bad, sizeof(bad), "integ_bad");
    ASSERT_TRUE(write_file(good, a, 5u));
    ASSERT_TRUE(write_file(bad, b, 4u));
    f[0].path = good;
    ASSERT_TRUE(break_crypto_sha256(a, 5u, f[0].sha256));
    f[1].path = bad;
    ASSERT_TRUE(break_crypto_sha256("not-beta", 8u, f[1].sha256));   /* wrong digest */
    f[2].path = "/nonexistent/x";
    memset(f[2].sha256, 0, 32u);
    ASSERT_EQ(break_integrity_check_files(f, 2u), (u32)BINT_SIG_FILE_MISMATCH);
    ASSERT_EQ(break_integrity_check_files(f, 3u), (u32)(BINT_SIG_FILE_MISMATCH | BINT_SIG_CHECK_ERROR));
    ASSERT_EQ(break_integrity_check_files(f, 1u), 0u);
    ASSERT_EQ(break_integrity_check_files(NULL, 1u), (u32)BINT_SIG_CHECK_ERROR);
    ASSERT_EQ(break_integrity_check_files(f, 0u), (u32)BINT_SIG_CHECK_ERROR);
    ASSERT_EQ(break_integrity_check_files(f, BREAK_INTEGRITY_MAX_FILES + 1u), (u32)BINT_SIG_CHECK_ERROR);
    f[0].path = NULL;
    ASSERT_EQ(break_integrity_check_files(f, 1u), (u32)BINT_SIG_CHECK_ERROR);
    remove(good);
    remove(bad);
}

#if defined(__linux__)

TEST(a_normal_process_has_no_tracer) {
    ASSERT_EQ(break_integrity_check_debugger(), 0u);
}

TEST(a_traced_process_reports_the_debugger_bit) {
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0);
    if (pid == 0) {
        /* child: ask to be traced by the parent, stop, then report */
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) != 0) _exit(90);
        raise(SIGSTOP);
        _exit(break_integrity_check_debugger() == BINT_SIG_DEBUGGER ? 0 : 91);
    }
    {
        int status = 0;
        ASSERT_EQ(waitpid(pid, &status, 0), pid);     /* child stopped itself */
        ASSERT_TRUE(WIFSTOPPED(status));
        ASSERT_EQ(ptrace(PTRACE_CONT, pid, NULL, NULL), 0);
        ASSERT_EQ(waitpid(pid, &status, 0), pid);
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(WEXITSTATUS(status), 0);
    }
}

/* Collects the basenames of this process's own file-backed mappings. */
static u32 own_basenames(char names[][128], u32 cap) {
    FILE *f = fopen("/proc/self/maps", "r");
    char line[1024];
    u32 n = 0u;
    if (f == NULL) return 0u;
    while (fgets(line, sizeof(line), f) != NULL) {
        char *slash = strrchr(line, '/');
        char *nl;
        u32 dup = 0u;
        if (strchr(line, '/') == NULL || slash == NULL) continue;
        nl = strchr(slash, '\n');
        if (nl) *nl = '\0';
        if (strstr(slash, " (deleted)")) *strstr(slash, " (deleted)") = '\0';
        for (u32 i = 0; i < n; i++) if (strcmp(names[i], slash + 1) == 0) dup = 1u;
        if (!dup && n < cap && strlen(slash + 1) < 128u) {
            strcpy(names[n++], slash + 1);
        }
    }
    fclose(f);
    return n;
}

TEST(the_real_module_list_is_clean_and_removing_one_name_flags_it) {
    static char names[256][128];
    const char *allowed[256];
    u32 n = own_basenames(names, 256u);
    ASSERT_TRUE(n >= 2u);
    for (u32 i = 0; i < n; i++) allowed[i] = names[i];
    ASSERT_EQ(break_integrity_check_modules(allowed, n), 0u);
    /* drop the first name: that mapping is now unknown */
    ASSERT_EQ(break_integrity_check_modules(allowed + 1, n - 1u), (u32)BINT_SIG_UNKNOWN_MODULE);
    /* An exact match is required in BOTH directions. Every other mapped name
     * stays in the list, so the ONLY thing that can raise UNKNOWN_MODULE is how
     * the one altered entry compares with the real name it was derived from. */
    {
        char altered[160];
        const char *list[256];
        size_t longest = 0u, pick = 0u;
        for (u32 i = 0; i < n; i++) {
            if (strlen(names[i]) > longest) { longest = strlen(names[i]); pick = i; }
        }
        ASSERT_TRUE(longest >= 3u);
        for (u32 i = 0; i < n; i++) list[i] = names[i];
        /* sanity: the unaltered list is clean */
        ASSERT_EQ(break_integrity_check_modules(list, n), 0u);
        /* the entry is a PREFIX of the mapped name ("libc.so" vs "libc.so.6") */
        snprintf(altered, sizeof(altered), "%.*s", (int)longest - 1, names[pick]);
        list[pick] = altered;
        ASSERT_EQ(break_integrity_check_modules(list, n), (u32)BINT_SIG_UNKNOWN_MODULE);
        /* the mapped name is a PREFIX of the entry ("libc.so.6-extra" vs "libc.so.6") */
        snprintf(altered, sizeof(altered), "%.120s-extra", names[pick]);
        list[pick] = altered;
        ASSERT_EQ(break_integrity_check_modules(list, n), (u32)BINT_SIG_UNKNOWN_MODULE);
    }
}

TEST(module_check_arguments_are_validated) {
    const char *one[1] = {"x"};
    ASSERT_EQ(break_integrity_check_modules(NULL, 1u), (u32)BINT_SIG_CHECK_ERROR);
    ASSERT_EQ(break_integrity_check_modules(one, 0u), (u32)BINT_SIG_CHECK_ERROR);
    ASSERT_EQ(break_integrity_check_modules(one, BREAK_INTEGRITY_MAX_MODULES + 1u), (u32)BINT_SIG_CHECK_ERROR);
    one[0] = NULL;
    ASSERT_EQ(break_integrity_check_modules(one, 1u), (u32)BINT_SIG_CHECK_ERROR);
}

TEST(a_library_loaded_after_the_allow_list_was_built_is_flagged) {
    static char names[256][128];
    const char *allowed[256];
    u32 n = own_basenames(names, 256u);
    /* the allow-list is a snapshot; a mapping that appears later and is not in
     * it (here: a fresh temporary file mapped read-only) is an unknown module */
    char path[300];
    u8 body[4096];
    FILE *f;
    void *map;
    int fd;
    memset(body, 0x5a, sizeof(body));
    tmp_path(path, sizeof(path), "integ_mapped.so");
    ASSERT_TRUE(write_file(path, body, sizeof(body)));
    for (u32 i = 0; i < n; i++) allowed[i] = names[i];
    ASSERT_EQ(break_integrity_check_modules(allowed, n), 0u);
    f = fopen(path, "rb");
    ASSERT_NOT_NULL(f);
    fd = fileno(f);
    {
        map = mmap(NULL, sizeof(body), PROT_READ, MAP_PRIVATE, fd, 0);
        ASSERT_TRUE(map != MAP_FAILED);
        ASSERT_EQ(break_integrity_check_modules(allowed, n), (u32)BINT_SIG_UNKNOWN_MODULE);
        munmap(map, sizeof(body));
    }
    fclose(f);
    ASSERT_EQ(break_integrity_check_modules(allowed, n), 0u);
    remove(path);
}

#else  /* not Linux: the /proc checks report CHECK_ERROR, never "clean" */

TEST(unsupported_platform_reports_check_error) {
    const char *one[1] = {"x"};
    ASSERT_EQ(break_integrity_check_debugger(), (u32)BINT_SIG_CHECK_ERROR);
    ASSERT_EQ(break_integrity_check_modules(one, 1u), (u32)BINT_SIG_CHECK_ERROR);
}

#endif

TEST_MAIN_BEGIN()
    RUN_TEST(matching_file_is_clean_and_a_flipped_byte_is_a_mismatch);
    RUN_TEST(missing_or_unreadable_file_is_a_check_error_not_clean);
    RUN_TEST(mixed_results_combine_and_bad_arguments_are_errors);
#if defined(__linux__)
    RUN_TEST(a_normal_process_has_no_tracer);
    RUN_TEST(a_traced_process_reports_the_debugger_bit);
    RUN_TEST(the_real_module_list_is_clean_and_removing_one_name_flags_it);
    RUN_TEST(module_check_arguments_are_validated);
    RUN_TEST(a_library_loaded_after_the_allow_list_was_built_is_flagged);
#else
    RUN_TEST(unsupported_platform_reports_check_error);
#endif
TEST_MAIN_END()
