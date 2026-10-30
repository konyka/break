#define _POSIX_C_SOURCE 200809L
/* break_crash_report — the operator's view of the crash statistics file that
 * break_crash_server maintains (docs/design/crash_symbolization.md).
 *
 *   break_crash_report <stats file> report
 *   break_crash_report <stats file> register-build <build-id>
 *   break_crash_report <stats file> mark-fixed <signature or 8+ hex prefix> <build-id>
 *
 * Builds are registered in release order; "regressed" means a crash from a
 * build registered AFTER the fix build. Every change takes the same file lock
 * as the server and replaces the file atomically. A statistics file that does
 * not parse is never overwritten: the tool exits 1 and says so.
 * Exit codes: 0 ok, 1 refused or failed, 2 usage. */
#include <crash/break_crash_cluster.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REPORT_CAP (4u * 1024u * 1024u)

static int usage(void) {
    fprintf(stderr, "usage: break_crash_report <stats file> report\n"
                    "       break_crash_report <stats file> register-build <build-id>\n"
                    "       break_crash_report <stats file> mark-fixed <signature|prefix> <build-id>\n");
    return 2;
}

int main(int argc, char **argv) {
    const char *path, *cmd;
    BreakCrashClusterLock *lock;
    BreakCrashClusterStore *s;
    int rc = 1;
    if (argc < 3) return usage();
    path = argv[1];
    cmd = argv[2];
    if (strcmp(cmd, "report") == 0 && argc == 3) {
        char *buf;
        usize n;
        s = break_crash_cluster_open(path);
        if (s == NULL) {
            fprintf(stderr, "break_crash_report: cannot read the statistics file\n");
            return 1;
        }
        buf = (char *)malloc(REPORT_CAP);
        n = buf != NULL ? break_crash_cluster_report(s, buf, REPORT_CAP) : 0u;
        if (n == 0u) {
            fprintf(stderr, "break_crash_report: cannot format the report\n");
        } else {
            fwrite(buf, 1u, n, stdout);
            rc = 0;
        }
        free(buf);
        break_crash_cluster_destroy(s);
        return rc;
    }
    if ((strcmp(cmd, "register-build") == 0 && argc == 4) || (strcmp(cmd, "mark-fixed") == 0 && argc == 5)) {
        lock = break_crash_cluster_lock(path);
        if (lock == NULL) {
            fprintf(stderr, "break_crash_report: cannot lock the statistics file\n");
            return 1;
        }
        s = break_crash_cluster_open(path);
        if (s == NULL) {
            fprintf(stderr, "break_crash_report: the statistics file does not parse; refusing to overwrite it\n");
            break_crash_cluster_unlock(lock);
            return 1;
        }
        if (strcmp(cmd, "register-build") == 0) {
            if (!break_crash_cluster_register_build(s, argv[3])) {
                fprintf(stderr, "break_crash_report: build id malformed, already registered, or the list is full\n");
            } else if (!break_crash_cluster_save(s, path)) {
                fprintf(stderr, "break_crash_report: cannot write the statistics file\n");
            } else {
                printf("registered %s\n", argv[3]);
                rc = 0;
            }
        } else {
            char full[65];
            if (!break_crash_cluster_resolve_prefix(s, argv[3], full)) {
                fprintf(stderr, "break_crash_report: no single signature matches '%s'\n", argv[3]);
            } else if (!break_crash_cluster_mark_fixed(s, full, argv[4])) {
                fprintf(stderr, "break_crash_report: the build '%s' is not registered\n", argv[4]);
            } else if (!break_crash_cluster_save(s, path)) {
                fprintf(stderr, "break_crash_report: cannot write the statistics file\n");
            } else {
                printf("fixed %.16s at %s\n", full, argv[4]);
                rc = 0;
            }
        }
        break_crash_cluster_destroy(s);
        break_crash_cluster_unlock(lock);
        return rc;
    }
    return usage();
}
