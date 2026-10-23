# Stage 5 Phase C (Crash Reporting: Capture + Spool + Redaction + Upload Seam) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver Stage 5 subproject 3 client side: an async-signal-safe crash capture (siginfo + registers + bounded stack window + install-time module list + build id + app-published context blob), a bounded on-disk spool with crash-recovery semantics, a pure-function redaction pass per the threat-model contract, a caller-supplied upload seam with retry/discard policy, and the symbolization contract document. Server-side symbolization/clustering/regression statistics are Phase D+ and NOT this plan; real upload transport is Phase D (transport) + application integration.

**Architecture:** New formal optional static library `break_crash` (zero new dependencies). Install-time pre-stages everything the handler may need (module list parsed from `/proc/self/maps`, build id from `break_version`, a preallocated record buffer, a pre-opened inbox file descriptor), because the handler runs under async-signal-safety constraints. The handler uses ONLY classic POSIX async-signal-safe operations (`write`/`lseek`/`fsync`/`close` + pure-memory hex formatting — no malloc, no stdio, no `open()` in the handler: a single-slot `crash.inbox` file is pre-opened at install), captures the record, then restores and re-raises the default action so process-death semantics (core dump, exit status) are preserved. Post-mortem (next normal run), the spool's open path recovers a present inbox into a named pending record — crash-spool recovery is a roadmap acceptance test. Upload is a caller-supplied function (same seam pattern as Phase B's `BreakUpdateFetchFn`); no transport code ships.

**Tech Stack:** C11; POSIX signals/ucontext (Linux tested); Phase A `PlatformAtomicWriter` + `platform_fs`; `break_version`; fork-based deterministic crash tests; ASan/UBSan/TSan.

## Global Constraints

- C11; ZERO new external dependencies. POSIX signal path fully tested on Linux; `_WIN32` gets a compile-time stub (`break_crash_install` returns false, documented) — no SEH/VEH this phase.
- New formal optional target `break_crash` + test variant; NOT linked by `engine`/`engine_demo`/`dxx_break`/`editor` (contract ctest pins); `BREAK_ENABLE_CRASH` option default ON (no external prereq; OFF ⇒ target absent).
- Async-signal-safety is the core contract: handler whitelist = siginfo/ucontext field reads, `getpid`, raw `syscall(SYS_gettid)`, `write`, `lseek`, `fsync`, `close`, pure-memory helpers (hand-rolled hex append, bounded memcpy). NOTHING else. Documented and review-verified line-by-line.
- Bounded everything: record ≤ 64 KiB (canonical text `break-crash-v1`, hex fields); module list ≤ 64 entries (install-time); context blob ≤ 4 KiB (copied at publish time into a preallocated slot); stack window ≤ 4 KiB (copied only when the range is provably inside the faulting thread's mapped stack — guard for stack-overflow SIGSEGV: skip window when fault address is within ±8 KiB of rsp); spool retention: pending ≤ 16, sent ≤ 16, discarded ≤ 16 (oldest overflow → discarded/deleted, counters observable).
- Capture exactly one crash per process run (one-shot guard; second signal falls through to the default action immediately).
- Fail closed: any spool/record parse anomaly → quarantine to `discarded/` with counter, never crash the reader; inbox recovery never blocks startup beyond bounded IO.
- Privacy by omission: cmdline, env, usernames, peer addresses are NOT captured. Redaction contract (`security_threat_model.md` §6): paths → basename; context blob passes through only because the app pre-redacts it (documented obligation); fault/register addresses are KEPT (required for symbolization; threat-model note: addresses are not user data).
- No client-side symbolization; no home-grown anything; record carries build id + module basenames + load offsets so the server symbolizes (contract in Task 4 doc).
- Three-tree lanes (normal / ASan+UBSan / TSan), contract ctest, nm export gate, `ENGINE_BUILD_TESTS=OFF` tree; fuzz lane `Not Run` (house convention).
- Honest docs: client-side mechanics only; no server, no real upload transport, no GPU/RHI-specific capture (apps publish summaries via the context-blob seam — engine integration is a later task).

---

## File and Target Map

- Create: `engine/src/crash/break_crash.h/.c` — record format (canonical text `break-crash-v1`) + spool + install/handler + redaction + upload seam.
- Create: `engine/tests/test_break_crash.c` — record/spool unit tests + fork-based crash-capture tests + redaction/upload tests.
- Create: `engine/tests/test_break_crash_target_contract.cmake`.
- Modify: `engine/CMakeLists.txt` (`BREAK_ENABLE_CRASH` option, target, tests, contract).
- Docs: new `docs/design/crash_reporting.md`; closeout touches `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 5 subproject 3), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`, `docs/design/security_threat_model.md` (§6 status sync).

---

### Task 1: Crash record format + bounded spool (no signals yet)

**Files:**
- Create: `engine/src/crash/break_crash.h`, `engine/src/crash/break_crash.c` (record + spool only)
- Create: `engine/tests/test_break_crash.c`
- Create: `engine/tests/test_break_crash_target_contract.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces (verbatim):**
```c
/* engine/src/crash/break_crash.h */
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
 * stack_window/context_blob → borrowed bytes + len (len may be 0). */
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
 * produces byte-identical format — same grammar, two writers, one pinned by tests): */
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
 * inbox into pending/<next-id>.bcr (torn/invalid → discarded/), enforcing retention. */
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
```

- [ ] RED: tests fail to link (symbols absent).
- [ ] GREEN tests: builder→finish→parse round-trip all fields byte-exact; canonical rejection battery (unknown key/order/dup/uppercase hex/NUL/CRLF/oversize/>64 modules/4KiB+1 blob); builder clamps (blob 5 KiB → 4 KiB; module 65th → false); spool: fresh open creates layout; put→count→read round-trip; retention overflow (17 puts → oldest discarded, counter observable via counts); inbox recovery: hand-crafted valid inbox → moved to pending; torn inbox (truncated/garbage) → discarded with count; mark_sent/mark_discarded transitions + bad index → false; reopen persistence.
- [ ] Lanes: build-sdd-p5c, -asan, -tsan green ×3; ASan ×3 / TSan ×5 zero reports; contract ctest green; nm gate symbol set pinned.
- [ ] Commit.

### Task 2: Signal handler + install-time capture (fork-tested)

**Files:**
- Modify: `engine/src/crash/break_crash.h/.c`
- Modify: `engine/tests/test_break_crash.c`

**Interfaces (verbatim):**
```c
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
```

Handler behavior (the pinned contract): one-shot guard → format record (siginfo signo/code/si_addr, ucontext RIP/RSP/RBP on x86-64; other arch → zeros documented, plus build id/modules/blob, stack window with overflow guard) into the preallocated buffer → `lseek(0)`+`write`+`fsync` the pre-opened inbox → restore SIG_DFL → `raise(sig)` so the process dies with original semantics (core dump if enabled). Only POSIX async-signal-safe calls (getpid, syscall(SYS_gettid), lseek/write/fsync/close + pure-memory helpers). No malloc/stdio/open in the handler.

- [ ] RED: fork tests fail (install/capture symbols absent).
- [ ] GREEN tests (parent/child via `fork()`+`waitpid`, spool in tmp): child installs → deliberate `*(volatile char *)0 = 0` → parent waits, expects death-by-SIGSEGV (`WIFSIGNALED`+`WTERMSIG`), then opens spool: inbox recovered to pending, record parses, signo=SIGSEGV, fault_addr=0, rip nonzero, build-id equals `break_version_string()`'s suffix, module list non-empty with basename-only names; SIGABRT child (`abort()`) same shape; double-install → false; uninstall restores (second child crashes WITHOUT record after uninstall); context blob published pre-crash appears in record; stack window present for normal SIGSEGV; record ≤ 64 KiB; one-shot guard (handler re-entry impossible by construction — documented, code-read pinned by review).
- [ ] Lanes ×3 green; ASan ×3 / TSan ×5 zero reports (fork tests included); `timeout -s KILL 60` direct runs exit 0 (proves no hang on crash paths).
- [ ] Commit.

### Task 3: Redaction + upload seam + spool recovery integration

**Files:**
- Modify: `engine/src/crash/break_crash.h/.c`
- Modify: `engine/tests/test_break_crash.c`

**Interfaces (verbatim):**
```c
/* Pure redaction pass per security_threat_model.md §6: module names → basename
 * (idempotent; builder already stores basenames — pin), any absolute-path-looking
 * field → basename, context blob kept as-is (app pre-redacted — documented).
 * Returns a NEW record; NULL on parse anomaly (input should already be valid). */
BreakCrashRecord *break_crash_record_redact(const BreakCrashRecord *r);
usize break_crash_record_serialize(const BreakCrashRecord *r, u8 *out, usize capacity); /* 0 on overflow */

/* Upload seam (caller supplies transport; same pattern as Phase B BreakUpdateFetchFn).
 * Iterates pending newest-first: redact → serialize → up(); true → mark_sent,
 * false → attempts++ persisted in a <id>.meta sidecar; attempts ≥ 5 → mark_discarded.
 * Returns count successfully uploaded this pass. */
typedef bool (*BreakCrashUploadFn)(void *user, const void *record_bytes, usize len);
u32 break_crash_spool_upload_pending(BreakCrashSpool *s, BreakCrashUploadFn up, void *user);
```

- [ ] RED: tests fail (symbols absent).
- [ ] GREEN tests: redact purity (input unchanged) + basename idempotence + blob passthrough; serialize→parse round-trip; upload: fake uploader all-true → all sent, counts moved; all-false → attempts increment across passes (persisted across spool reopen), 5th failure → discarded; mixed outcomes ordering; crash-spool recovery acceptance scenario end-to-end: child crash (Task 2 path) → parent spool_open recovers → redact → upload via fake → sent; `BreakCrashUploadFn` NULL → INVALID-style no-op 0.
- [ ] Lanes ×3 green; ASan ×3 / TSan ×5 zero reports; nm gate symbol set updated.
- [ ] Commit.

### Task 4: Validation and documentation closeout

**Files:**
- Create: `docs/design/crash_reporting.md`
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 5 subproject 3 → delivered client-side capture+spool+redaction+upload seam; server symbolization/clustering/regression and real transport pending), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`, `docs/design/security_threat_model.md` (§6 redaction contract → delivered client-side enforcement points; §10 NOT-delivered sync)

- [ ] Clean normal tree: full default build + lanes green (record/spool/crash/redact/upload + contract).
- [ ] ASan/UBSan + TSan trees green, zero reports; `ENGINE_BUILD_TESTS=OFF` tree builds; nm: production archives zero test-hook symbols (deferral #2 remains the sole documented exception).
- [ ] Full non-graphics/non-fuzz suite; classify failures per house convention.
- [ ] Contract ctests green; `git diff --check` clean on branch range.
- [ ] crash_reporting.md: capture inventory (what is/ isn't captured + privacy-by-omission table), async-signal-safe whitelist table, inbox→pending recovery sequence, retention/backoff policy, upload seam contract (`BreakCrashUploadFn`: false=retryable, app owns transport), symbolization contract (server consumes build-id + module basenames + load offsets + RIP; client never symbolizes), honest NOT-delivered list (server, real transport, GPU/RHI/network/input summary capture = app context-blob integration later, minidump/PE formats, Windows SEH).
- [ ] Threat model §6 sync: redaction obligations now have a client-side enforcement point (redact pass) — status-word update per house discipline.

## Cross-cutting Review Gates

- RED before production code; GREEN normal/ASan/TSan after.
- Async-signal-safety: reviewer line-verifies the handler's call set against the documented whitelist (no malloc/stdio/open/locks; formatting is pure-memory).
- One-shot capture: second signal → default action immediately (no nested formatting); process death semantics preserved (SIG_DFL + raise).
- No privacy regression: cmdline/env/usernames/peer addresses never captured; redaction is pure + idempotent; blob obligation documented.
- Bounded: record ≤64 KiB, modules ≤64, blob/window ≤4 KiB, spool 16/16/16, attempts ≤5 — all pinned by tests.
- Fail closed: torn inbox → discarded (never blocks startup); parse anomaly → quarantine; upload failures never lose records before the 5-attempt policy.
- break_crash stays out of engine/demos/editor link closures (contract).
- Fork tests must assert death-by-signal (WIFSIGNALED/WTERMSIG) AND record content — not just "a file appeared".
- Docs honest: client-side only; server symbolization/clustering/regression pending; Windows stub; fuzz `Not Run`.
- A task completes only after focused code review, doc update, and `git diff --check` on its range.
