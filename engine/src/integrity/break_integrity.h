#pragma once
/* ==========================================================================
 *  break_integrity — Stage 5 subproject 5: client-side tamper SIGNALS
 *  (docs/design/client_integrity.md, security_threat_model.md section 2).
 *
 *  The only thing this library does is observe and report. It has no
 *  function that allows, denies, grants or revokes anything, and it is not
 *  an authority input: whatever the client reports about itself is
 *  untrusted, and anyone with code execution on the machine can defeat any
 *  of these checks. The signals are a cost raiser and, at most, one INPUT
 *  to a server-side risk score. They never unlock a privileged action and
 *  the server never relaxes a check because a client reports "clean".
 *  (A contract test pins that the header exports no allow/grant/deny style
 *  symbol and that break_authority does not include this header.)
 *
 *  A check that cannot run reports BINT_SIG_CHECK_ERROR, never "clean": a
 *  missing file, an unreadable /proc, an unsupported platform, or a NULL
 *  argument must not look the same as a pass.
 *
 *  Platforms: file hashing is portable (stdio). The debugger and module
 *  checks read /proc and are Linux-only; elsewhere they return
 *  CHECK_ERROR (documented, not faked). Windows (IsDebuggerPresent,
 *  EnumProcessModules) and macOS (sysctl P_TRACED, dyld image list) are not
 *  implemented.
 * ========================================================================== */

#include <core/types.h>

typedef u32 BreakIntegritySignals;
enum {
    BINT_SIG_FILE_MISMATCH = 1u << 0,   /* a listed file's SHA-256 differs */
    BINT_SIG_DEBUGGER = 1u << 1,        /* a tracer is attached to this process */
    BINT_SIG_UNKNOWN_MODULE = 1u << 2,  /* a mapped file whose basename is not allowed */
    BINT_SIG_CHECK_ERROR = 1u << 3      /* a check could not run (or bad arguments) */
};

#define BREAK_INTEGRITY_MAX_FILES 64u
#define BREAK_INTEGRITY_MAX_MODULES 256u

typedef struct BreakIntegrityFile {
    const char *path;
    u8 sha256[32];
} BreakIntegrityFile;

/* Hashes each file (streamed) and compares. 0 = every file matches. A file
 * that cannot be opened/read, count 0 or above the maximum, or a NULL
 * list/path sets CHECK_ERROR; mismatches set FILE_MISMATCH; both can be set. */
BreakIntegritySignals break_integrity_check_files(const BreakIntegrityFile *files, u32 count);

/* Linux: TracerPid in /proc/self/status. */
BreakIntegritySignals break_integrity_check_debugger(void);

/* Linux: every file-backed mapping in /proc/self/maps must have a basename
 * in `allowed_basenames` (exact match). Anonymous mappings and pseudo
 * entries like [heap] are skipped; a "(deleted)" mapping counts by its name.
 * count 0 / NULL list / above the maximum -> CHECK_ERROR. */
BreakIntegritySignals break_integrity_check_modules(const char *const *allowed_basenames,
                                                    u32 count);
