#pragma once
/* ==========================================================================
 *  break_crash — Stage 5 Phase C Tasks 1+2: the crash RECORD format
 *  (canonical text "break-crash-v1"), the bounded on-disk SPOOL, and the
 *  async-signal-safe capture (install/handler). Redaction and the upload
 *  seam are Task 3 and deliberately absent here. Zero new external
 *  dependencies; the only platform services consumed are the Stage 4/5 PAL
 *  (platform_fs.h: PlatformAtomicWriter / platform_mkdir / platform_file_size
 *  / platform_list_dir) plus C-standard rename/remove/fread, and the build
 *  identity via break_version.h's break_version_string() — callers link the
 *  PAL and break_version.c themselves (the tests compile
 *  src/platform/platform_fs.c and src/core/break_version.c inline, the
 *  test_break_update / test_break_version precedent).
 *
 *  Canonical record grammar (byte-pinned; the Task 2 signal-side writer
 *  produces BYTE-IDENTICAL output — one grammar, two writers, this header
 *  plus the tests pin it). Every byte is LF or printable ASCII 0x20-0x7E;
 *  the text ends with exactly one final LF; total size ≤ 65536 bytes. Line
 *  sequence (fixed order, each key exactly once, LF-terminated):
 *
 *    break-crash-v1
 *    signo: <hex8>                      (u32 value of the signal number)
 *    code: <hex8>                       (u32 value of the siginfo code)
 *    fault_addr: <hex16>
 *    pid: <hex16>
 *    tid: <hex16>
 *    rip: <hex16>
 *    rsp: <hex16>
 *    rbp: <hex16>
 *    build-id: <1..64 chars [0-9a-z-]>
 *    module: <hex16> <hex16> <name>     (0..64 lines, capture order kept;
 *                                        load-offset size name-basename;
 *                                        name 1..255 chars of 0x21-0x7E
 *                                        minus '/' — no uniqueness/sort
 *                                        constraint)
 *    stack-window:< ":" then EOL when empty, else ": " + hex>  (lowercase
 *                                        hex, even count, 2..8192 chars =
 *                                        1..4096 bytes; EMPTY form is the
 *                                        bare "stack-window:" line — no
 *                                        trailing space)
 *    context-blob:<same rule>           (must be the LAST line)
 *
 *  hex8 = exactly 8 lowercase hex digits; hex16 = exactly 16. ANY deviation
 *  (unknown/misordered/duplicated key, uppercase hex, odd hex count, NUL,
 *  CR/CRLF, TAB, byte ≥ 0x7F, missing final LF, > 64 modules, > 4 KiB blob
 *  or window, > 64 KiB total, trailing garbage) → parse NULL. Parse is
 *  two-pass (validate everything, then fill — the break_update.c manifest
 *  discipline); the public oracle is exactly NULL = invalid.
 *
 *  The 64 KiB cap is unreachable from the builder (a maximal record —
 *  64 modules × 255-char names + 4 KiB window + 4 KiB blob — is ~35.8 KB);
 *  both are enforced.
 *
 *  NULL discipline: every function tolerates a NULL handle — setters are
 *  no-ops, finish returns 0, spool ops return false, count returns 0,
 *  scalar accessors return 0, build_id returns NULL, the window/blob
 *  accessors return 0 and set *out_bytes = NULL, module_at returns false,
 *  destroy(NULL) is a free(NULL)-style no-op. NULL out-params on a live
 *  handle are bounded no-ops: module_at returns false, registers writes
 *  nothing, the window/blob accessors report the length without storing.
 * ========================================================================== */

#include <core/types.h>

#define BREAK_CRASH_RECORD_MAX 65536u
#define BREAK_CRASH_MODULE_MAX 64u
#define BREAK_CRASH_CONTEXT_BLOB_MAX 4096u
#define BREAK_CRASH_STACK_WINDOW_MAX 4096u
#define BREAK_CRASH_SPOOL_KEEP 16u   /* per class: pending/ sent/ discarded/ */

/* Record: opaque parsed owner of canonical-text "break-crash-v1" fields.
 * Field set (key order fixed): signo, code, fault_addr, pid, tid, rip, rsp, rbp,
 * build-id, module lines (name-basename + load-offset + size), stack-window
 * (hex, ≤4KiB, may be empty), context-blob (hex, ≤4KiB, may be empty).
 * All integers fixed-width lowercase hex; parse rejects ANY deviation. */
typedef struct BreakCrashRecord BreakCrashRecord;
BreakCrashRecord *break_crash_record_parse(const void *text, usize len);   /* NULL on any anomaly */
void break_crash_record_destroy(BreakCrashRecord *r);
/* Accessors: u64 fields via out-params; module_at(i) → basename borrowed + offset/size out;
 * stack_window/context_blob → borrowed bytes + len (len may be 0).
 * NOTE: the record carries "code" (byte-pinned in the grammar) but Task 1
 * exposes no code accessor — the interface is the brief's verbatim set. */
int  break_crash_record_signo(const BreakCrashRecord *r);
u64  break_crash_record_fault_addr(const BreakCrashRecord *r);
u64  break_crash_record_pid(const BreakCrashRecord *r);
u64  break_crash_record_tid(const BreakCrashRecord *r);
void break_crash_record_registers(const BreakCrashRecord *r, u64 out_rip_rsp_rbp[3]);
const char *break_crash_record_build_id(const BreakCrashRecord *r);        /* borrowed */
u64  break_crash_record_module_count(const BreakCrashRecord *r);
bool break_crash_record_module_at(const BreakCrashRecord *r, u64 i,
                                  const char **out_name, u64 *out_offset, u64 *out_size);
usize break_crash_record_stack_window(const BreakCrashRecord *r, const u8 **out_bytes);
usize break_crash_record_context_blob(const BreakCrashRecord *r, const u8 **out_bytes);

/* Builder (normal-context; the signal handler has its own signal-safe writer that
 * produces byte-identical format — same grammar, two writers, one pinned by tests):
 * a fresh builder holds the valid minimal record (all scalars zero, build-id
 * "unknown", zero modules, empty window/blob), so finish never fails on
 * content. set_build_id with an invalid id (NULL, empty, > 64 chars, char
 * outside [0-9a-z-]) is a bounded NO-OP (previous value kept — void return).
 * add_module returns false past 64 modules and on an invalid name (NULL,
 * empty, > 255 chars, char outside 0x21-0x7E or '/'). set_stack_window /
 * set_context_blob clamp len to 4 KiB; bytes == NULL is treated as len 0
 * (clears the section). finish returns the exact byte count, or 0 when
 * capacity is insufficient or out is NULL (content is never the failure —
 * only capacity). */
typedef struct BreakCrashRecordBuilder BreakCrashRecordBuilder;  /* opaque */
BreakCrashRecordBuilder *break_crash_record_builder_create(void); /* NULL on OOM */
void break_crash_record_builder_set_signal(BreakCrashRecordBuilder *b, int signo, int code, u64 fault_addr);
void break_crash_record_builder_set_process(BreakCrashRecordBuilder *b, u64 pid, u64 tid);
void break_crash_record_builder_set_registers(BreakCrashRecordBuilder *b, u64 rip, u64 rsp, u64 rbp);
void break_crash_record_builder_set_build_id(BreakCrashRecordBuilder *b, const char *id);  /* ≤64 chars, [0-9a-z-] */
bool break_crash_record_builder_add_module(BreakCrashRecordBuilder *b, const char *name, u64 offset, u64 size); /* false past 64 */
void break_crash_record_builder_set_stack_window(BreakCrashRecordBuilder *b, const u8 *bytes, usize len);   /* clamps 4KiB */
void break_crash_record_builder_set_context_blob(BreakCrashRecordBuilder *b, const u8 *bytes, usize len);   /* clamps 4KiB */
usize break_crash_record_builder_finish(const BreakCrashRecordBuilder *b, u8 *out, usize capacity);         /* 0 on overflow */
void break_crash_record_builder_destroy(BreakCrashRecordBuilder *b);

/* Spool: <root>/{crash.inbox,pending/,sent/,discarded/}. open recovers a non-empty
 * inbox into pending/<next-id>.bcr (torn/invalid → discarded/), enforcing retention.
 *
 * Spool semantics (byte-pinned by tests):
 *  - open creates the layout (root + three class dirs + an empty crash.inbox
 *    when missing); trailing '/' on root_path is stripped; over-long roots
 *    (no room for "/discarded/<max-id>.bcr" inside PLATFORM_FS_PATH_CAPACITY)
 *    fail NULL.
 *  - Record file names are canonical decimal ids: "<id>.bcr", id ≥ 1, no
 *    leading zeros. Ids are unique across all three classes and monotone per
 *    spool lifetime; open re-derives next-id as max(existing)+1 and put
 *    skips ids that collided with foreign files. Foreign (non-canonical)
 *    entries — including atomic-writer tmp residue "*.tmpXXXXXX" — are never
 *    counted, moved, or deleted.
 *  - Inbox recovery at open: a non-empty inbox is read (≤ 64 KiB; larger is
 *    invalid WITHOUT a full read); a byte-valid record is committed to
 *    pending/<next-id>.bcr through PlatformAtomicWriter and the inbox is
 *    reset to empty; anything else (torn/garbage/oversize/unreadable) is
 *    rename()d WHOLE into discarded/<next-id>.bcr (forensic bytes kept) and
 *    the inbox recreated empty. Recovery is AT-LEAST-ONCE: a crash between
 *    the pending commit and the inbox reset re-recovers a duplicate under a
 *    new id on the next open (documented, never a loss). Any persistence
 *    failure during recovery → open returns NULL with the inbox left
 *    recoverable (fail closed; never blocks startup beyond bounded IO:
 *    ≤ 64 KiB read + bounded listing of ≤ 4096 entries/class).
 *  - count(class) live-scans: 0=pending 1=sent 2=discarded; other classes
 *    and IO errors → 0.
 *  - put_pending validates (0 < len ≤ 64 KiB AND the bytes parse) before
 *    staging — pending/ only ever holds parseable records; invalid input →
 *    false, nothing written, id not consumed.
 *  - read_pending/mark_* address pending by index, NEWEST-FIRST (index 0 =
 *    highest id = most recently staged). read returns caller-owned malloc
 *    bytes (free()); the bytes are returned as stored (no re-validation —
 *    put/inbox validation makes pending parseable by construction; Task 3's
 *    redact re-parses anyway). Bad index → false.
 *  - mark_sent/mark_discarded rename pending/<id>.bcr into the target class
 *    (same filesystem; directory fsynced best-effort) and enforce retention.
 *  - Retention (BREAK_CRASH_SPOOL_KEEP = 16 per class): on overflow the
 *    OLDEST (lowest id) of pending/sent moves to discarded/; discarded
 *    overflow DELETES its oldest. Counters stay observable via count().
 *  - Not thread-safe (one spool owner per process — the repo convention). */
typedef struct BreakCrashSpool BreakCrashSpool;
BreakCrashSpool *break_crash_spool_open(const char *root_path);   /* creates layout; NULL on error */
void break_crash_spool_destroy(BreakCrashSpool *s);
u64  break_crash_spool_count(const BreakCrashSpool *s, int class_);  /* 0=pending 1=sent 2=discarded */
/* Stage a built record into pending/ (atomic writer; retention enforced): */
bool break_crash_spool_put_pending(BreakCrashSpool *s, const void *record_bytes, usize len);
/* Read i-th pending record (newest-first ordering, documented): caller-owned out_buf: */
bool break_crash_spool_read_pending(const BreakCrashSpool *s, u64 index, u8 **out_buf, u64 *out_len);
bool break_crash_spool_mark_sent(BreakCrashSpool *s, u64 index);       /* pending → sent/ */
bool break_crash_spool_mark_discarded(BreakCrashSpool *s, u64 index);  /* pending → discarded/ */

/* ==========================================================================
 *  Signal capture (Stage 5 Phase C Task 2): install-time pre-staging + an
 *  async-signal-safe handler. POSIX (Linux tested) only: on _WIN32 this
 *  section is a documented compile-time stub (install returns false, the
 *  others are no-ops) — no SEH/VEH this phase.
 *
 *  Install pre-stages EVERYTHING the handler may need, because the handler
 *  runs under async-signal-safety constraints:
 *   - module list: /proc/self/maps parsed NOW (install time), ≤ 64
 *     file-backed entries in capture order; contiguous same-path mappings
 *     merge (load-offset = first-start − first-file-offset, size = end −
 *     first-start); names are basenames validated against the grammar
 *     charset (0x21-0x7E minus '/'), unnameable entries skipped.
 *   - build id: break_version_string()'s "+" suffix (the BREAK_BUILD_ID
 *     CMake injects), or "unknown" when there is no valid suffix.
 *   - record buffer: a preallocated static 64 KiB buffer (the largest
 *     formattable record is ~35.8 KB — the cap is unreachable, same
 *     construction argument as the builder).
 *   - context-blob slot: a preallocated static 4 KiB slot (empty until
 *     break_crash_set_context_blob publishes).
 *   - inbox fd: install performs a spool open/close pass (which recovers a
 *     PREVIOUS run's crash.inbox into pending/ and leaves an empty inbox),
 *     then open()s crash.inbox and HOLDS the fd. The handler never opens
 *     anything.
 *
 *  Handler contract (pinned; byte-identical grammar to the builder — the
 *  tests interlock the two writers through the Task 1 parser): one-shot
 *  guard → format the record (siginfo signo/code/si_addr; ucontext
 *  RIP/RSP/RBP on Linux x86-64, ZEROS on every other architecture —
 *  documented degradation; plus pid/tid, build id, modules, stack window,
 *  context blob) into the preallocated buffer → lseek(0)+write+fsync to the
 *  pre-opened inbox → restore SIG_DFL, unblock, raise(sig) so the process
 *  dies with the original semantics (core dump, WIFSIGNALED status); an
 *  _exit(128+sig) backstop covers the blocked/ignored edge.
 *
 *  One-shot capture: exactly one crash per process run is captured. The
 *  guard is a C11 atomic_flag (the always-lock-free type; C11 7.14.1.1
 *  permits lock-free atomic operations in signal handlers) — any re-entry,
 *  nested or on a racing second thread, goes straight to the restore/raise
 *  tail without touching the record buffer. SA_NODEFER is NOT used and the
 *  handler is NOT installed on an alternate stack (no SA_ONSTACK): a
 *  stack-overflow SIGSEGV deep enough to break the handler's own frame
 *  loses the record but still dies true (fail closed).
 *
 *  Stack window: up to 4 KiB at [rsp, rsp+4KiB) hex-encoded into the record.
 *  The handler executes on the faulting thread's stack, so the window's
 *  pages are the live frames; a read past the mapping's high end would
 *  re-fault into the one-shot guard's die tail (record lost, death
 *  semantics kept). Stack-overflow guard (pinned): when sig == SIGSEGV and
 *  the fault address lies within rsp ± 8 KiB, the window is SKIPPED (the
 *  stack's guard region is near — reading it would fault again); rsp == 0
 *  also yields an empty window.
 *
 *  Privacy by omission, enforced at capture: the argv/env strings block
 *  sits at the top of the initial [stack] mapping, and a shallow
 *  main-thread crash's window would otherwise hex-dump cmdline/env
 *  (usernames, HOME, secrets) — the threat model says those are NEVER
 *  captured. Install computes zone_lo = the lowest argv[0]/environ string
 *  address inside [stack] (glibc: argv[0] via program_invocation_name;
 *  other libcs: environ only — documented degradation); the handler clamps
 *  the window below zone_lo (a crash with rsp inside the zone yields an
 *  empty window). Thread stacks carry no argv/env and are not clamped.
 *
 *  Handler async-signal-safety WHITELIST (the complete call set; review
 *  verifies line-by-line):
 *    siginfo_t / ucontext_t field reads — plain memory, no libc
 *    atomic_flag_test_and_set           — C11 lock-free atomic (above)
 *    getpid()                           — POSIX.1 async-signal-safe list
 *    syscall(SYS_gettid)                — Linux: a direct trap through a
 *                                         stateless libc trampoline (no
 *                                         TLS, no locks; gettid cannot fail
 *                                         so no errno write) — gettid(2) is
 *                                         absent from the POSIX list only
 *                                         because it is not POSIX
 *    lseek, write, fsync                — POSIX.1 list (pre-opened fd)
 *    signal, sigemptyset, sigaddset,
 *    sigprocmask, raise, _exit          — POSIX.1 list (restore-and-die tail)
 *    bs_* helpers                       — hand-rolled pure-memory hex append,
 *                                         no libc at all
 *  BANNED in the handler: malloc/free, stdio, open, locks/pthread, and any
 *  libc beyond the whitelist (formatting is pure-memory by construction).
 *
 *  Thread/concurrency semantics (documented, pinned by review): install and
 *  uninstall are NOT thread-safe — call install once at startup, uninstall
 *  once at shutdown, from the same phase of the process. Second install
 *  while installed → false; after uninstall a fresh install succeeds.
 *  break_crash_set_context_blob is safe PRE-CRASH only (no locking): a
 *  crash racing a publish may capture a torn blob; the app pre-redacts the
 *  blob (threat-model obligation). NULL data clears the slot. */
typedef struct BreakCrashConfig {
    const char *spool_root;   /* created if missing; inbox pre-opened inside */
} BreakCrashConfig;
/* Installs handlers for SIGSEGV/SIGABRT/SIGILL/SIGFPE/SIGBUS. Pre-stages: module list
 * (/proc/self/maps parsed NOW), build id (break_version), preallocated record buffer,
 * pre-opened crash.inbox fd. Once per process; second call false. false on error.
 * NOT thread-safe to install/uninstall concurrently (documented; install once at startup). */
bool break_crash_install(const BreakCrashConfig *config);
bool break_crash_is_installed(void);
/* Publishes an app-owned recent-events snapshot, COPIED NOW into the preallocated slot
 * (≤4KiB clamp). The app pre-redacts it (threat-model obligation). Safe pre-crash only. */
void break_crash_set_context_blob(const void *data, usize len);
/* Restores previous handlers; spool intact; inbox fd closed. */
void break_crash_uninstall(void);
