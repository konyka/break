# Stage 5 Phase B (Update Client: Download/Resume/A-B/Rollback) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver Stage 5 subproject 2: a headless-testable update client inside `break_update` — transport-agnostic chunked download with byte-level resume, staging into A/B slots, atomic activation, boot confirmation, and policy-bounded rollback — built on Phase A's signed manifest, CAS chunk store, and atomic writer. No real network transport ships in this phase (HTTP/TLS wiring is Phase C+); the fetch transport is a caller-supplied callback, tested with an in-process fake.

**Architecture:** The update client is a state machine persisted under an update root: `chunks/` (Phase A CAS, shared across slots), `slots/A` + `slots/B` (materialized trees), and a canonical-text `state` file (atomically written, same parse discipline as the manifest). Download is chunk-granular with per-chunk `.part` byte-level resume: the fetch callback supports ranged reads (`offset`/`len`); in-flight chunk bytes spool to `<chunk>.part` with progress persisted in the state file, so a crash mid-chunk resumes at the byte boundary. Staging verifies every chunk hash against the signed manifest before materialization; activation flips `current` to the staged slot with `confirmed=no`; `confirm_boot` marks the new slot good; `rollback` swaps back to the retained previous slot subject to min-rollback-version policy. Gray rollout （灰度） is server-side policy — the client's only knob is its configured channel (documented; no client-side bucket logic this phase).

**Tech Stack:** C11; Phase A `break_update` (manifest + store) extended in place (same static target, contract source-list pins updated); `platform_fs` atomic writer; fake-fetch failure-injection tests; ASan/UBSan/TSan.

## Global Constraints

- C11; ZERO new external dependencies (OpenSSL only via existing `break_crypto`). No socket/HTTP/TLS code anywhere in this phase — `BreakUpdateFetchFn` is the sole transport seam; document that production transport wiring remains Phase C (transport auth) + application integration.
- Everything bounded: state file ≤ 64 KiB; slot count exactly 2 (A/B); chunk count per stage ≤ manifest limit (65536); in-flight `.part` count ≤ 1 (sequential download); resume progress entries bounded by chunk count; all disk arithmetic overflow-checked.
- Fail closed: any state-file parse anomaly → client open fails (no heuristic repair); any chunk hash mismatch → stage fails with partial slot removed; partial states are always resumable or cleanly abortable, never half-active.
- Crash-safety: every state transition persists via `PlatformAtomicWriter` BEFORE the visible effect (write-ahead discipline); activation/rollback are pointer flips in the state file (slots are directories, never renamed while live — documented decision: `current` is data, not a symlink).
- `break_update` stays out of `engine`/`engine_demo`/`dxx_break`/`editor` link closures; contract ctest updated for the new symbols/sources.
- Same-object re-download suppression: chunks already in CAS (has_chunk) are never re-fetched (test counts fetch calls).
- Error discipline: stage/resume return `false` with an internal reason enum surfaced via `break_update_client_last_error()` (fixed enum, no error strings from attacker-controlled input); fetch failures are retryable (state unchanged except progress).
- Windows: no new `_WIN32` branches this phase (slot trees use only existing PAL primitives); `BREAK_ENABLE_CRYPTO=OFF` ⇒ entire update target absent (inherited gate).
- Three-tree lanes (normal / ASan+UBSan / TSan), contract ctests, nm export gates, `ENGINE_BUILD_TESTS=OFF` tree, per established SDD protocol. Fuzz lane `Not Run` (house convention).
- Honest docs: this phase delivers the client-side offline mechanics; "no unsigned update path in release" stays true (stage requires a verified signature); no server, no gray-rollout client logic, no real transport.

---

## File and Target Map

- Modify: `engine/src/update/break_update.h/.c` — add state machine + client + downloader (same target; source list unchanged = 1 TU; header grows).
- Create: `engine/src/update/break_update_client.h` — client/state/fetch API (separate header to keep Phase A manifest header stable); implementation in `break_update_client.c` (target becomes 2 TUs — contract source-list pin updated).
- Create: `engine/tests/test_break_update_client.c` — state machine + fake-fetch download/resume/activate/rollback suite.
- Modify: `engine/tests/test_break_update_target_contract.cmake` — source list 1→2 TUs, nm gate symbol-set update, no-link pins unchanged.
- Modify: `engine/CMakeLists.txt` — second TU into `break_update`; new test registration.
- Modify at closeout: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 5 subproject 2 → delivered client-side-offline-mechanics), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`, `docs/design/security_threat_model.md` §4/§10 status updates.
- Docs: new `docs/design/update_client.md` (state machine, on-disk layout, resume semantics, rollback policy, transport seam contract).

---

### Task 1: Update client state machine + A/B slots (no download yet)

**Files:**
- Create: `engine/src/update/break_update_client.h`, `engine/src/update/break_update_client.c`
- Create: `engine/tests/test_break_update_client.c`
- Modify: `engine/CMakeLists.txt`, `engine/tests/test_break_update_target_contract.cmake` (source list 2 TUs)

**Interfaces (verbatim):**
```c
/* engine/src/update/break_update_client.h */
/* On-disk layout under <root>: chunks/ (Phase A CAS), slots/A/, slots/B/,
 * and canonical-text file "state" (≤64 KiB, atomically replaced):
 *   break-update-state-v1
 *   current: A|B|none
 *   staged: A|B|none            (slot whose materialization completed)
 *   pending: yes|no             (staged and activated, awaiting confirm)
 *   confirmed: yes|no
 *   current-version: M.m.p      (none when current=none)
 *   previous-version: M.m.p     (none when no previous)
 *   min-rollback-version: M.m.p (policy floor for rollback)
 *   resume-chunk: <sha256hex>|<offset>  OR  none
 * Same canonical discipline as break-manifest-v1 (key order fixed as listed,
 * LF, ASCII, unknown/malformed → parse fail). */

typedef struct BreakUpdateClient BreakUpdateClient;
BreakUpdateClient *break_update_client_open(const char *root_path);  /* creates layout+initial state if absent; NULL on error/corrupt */
void break_update_client_destroy(BreakUpdateClient *c);

typedef enum BreakUpdateClientError {  /* fixed enum; no attacker-controlled strings */
    BREAK_UPDATE_CLIENT_OK = 0, BREAK_UPDATE_CLIENT_INVALID, BREAK_UPDATE_CLIENT_IO,
    BREAK_UPDATE_CLIENT_PARSE, BREAK_UPDATE_CLIENT_POLICY, BREAK_UPDATE_CLIENT_FETCH,
    BREAK_UPDATE_CLIENT_VERIFY, BREAK_UPDATE_CLIENT_STATE
} BreakUpdateClientError;
BreakUpdateClientError break_update_client_last_error(const BreakUpdateClient *c);

/* Queries (borrowed strings, fixed buffers): */
char break_update_client_current_slot(const BreakUpdateClient *c);   /* 'A'/'B'/'-' */
bool break_update_client_pending(const BreakUpdateClient *c);        /* staged, awaiting confirm */
bool break_update_client_confirmed(const BreakUpdateClient *c);
void break_update_client_current_version(const BreakUpdateClient *c, u32 out[3]);  /* 0.0.0 when none */

/* Boot lifecycle: */
bool break_update_client_confirm_boot(BreakUpdateClient *c);   /* pending → confirmed, persists first */
bool break_update_client_rollback(BreakUpdateClient *c);       /* swap current↔previous slot; policy:
    false when no previous slot, when previous-version < min-rollback-version, or when staged exists
    (must abort/clean staged first — documented); persists first, then flips */
```

- [ ] RED: tests fail to link (client symbols absent).
- [ ] GREEN tests: fresh open → current=none state file created (byte-exact canonical text pinned); reopen persistence round-trip; corrupt state (truncated/unknown key/bad value) → open NULL; state >64 KiB → NULL; confirm_boot without pending → false; rollback without previous → false; rollback below min-rollback → false (POLICY); rollback with staged present → false (STATE); state file rewritten via atomic writer (tmp gone after each op); NULL-arg matrix.
- [ ] Lanes: build-sdd-p5b, -asan, -tsan; new test green ×3; ASan ×3/TSan ×5 zero reports; contract ctest updated (2 TUs) green ×3.
- [ ] Commit.

### Task 2: Chunked downloader with byte-level resume

**Files:**
- Modify: `engine/src/update/break_update_client.h/.c`
- Modify: `engine/tests/test_break_update_client.c`

**Interfaces (verbatim):**
```c
/* Caller-supplied ranged fetch of a remote object by name (this phase: object name ==
 * chunk sha256hex). out capacity ≥ len; false = transport failure (retryable).
 * offset+len overflow-checked by the client before calling. */
typedef bool (*BreakUpdateFetchFn)(void *user, const char *object_name,
                                   u64 offset, u64 len, u8 *out);

/* Downloads all manifest chunks missing from CAS, spooling each through
 * chunks/<hash>.part (byte-level resume via state resume-chunk = hash|offset),
 * verifying sha256 == manifest hash before store_put_chunk. Sequential, one
 * .part at a time. Returns true when every chunk is present in CAS.
 * false + last_error: FETCH (transport; progress kept — call again to resume),
 * VERIFY (hash mismatch; .part discarded), IO, STATE (corrupt resume → restarted clean). */
bool break_update_client_fetch_all(BreakUpdateClient *c, const BreakUpdateManifest *m,
                                   BreakUpdateFetchFn fetch, void *user);
```

- [ ] RED: tests fail (symbol absent).
- [ ] GREEN tests with an in-process fake fetcher (fixture buffer map + scriptable failure: fail-after-N-bytes, fail-on-call-K, deterministic): full download of a 3-chunk manifest → fetch call counts == missing chunks only (CAS pre-seeded chunk not re-fetched); mid-chunk failure → resume continues at byte offset (fake asserts offset>0 on resume, final bytes equal); completed chunk never re-fetched across reopen (persisted progress); hash mismatch → VERIFY false + .part gone + chunk absent from CAS; corrupt resume entry → STATE, chunk restarted from 0, succeeds; zero-byte chunk; manifest with 0 chunks → true no-op; offset+len overflow path (fake claims size near U64_MAX — client clamps from manifest size, never calls with overflow).
- [ ] Lanes ×3 green; ASan ×3 / TSan ×5 zero reports.
- [ ] Commit.

### Task 3: Stage → activate → confirm → rollback pipeline

**Files:**
- Modify: `engine/src/update/break_update_client.h/.c`
- Modify: `engine/tests/test_break_update_client.c`

**Interfaces (verbatim):**
```c
/* Full pipeline: verify signature (pubkey) → compatible() policy (channel/platform/
 * current version from state) → fetch_all → materialize chunks into the INACTIVE slot
 * (each manifest chunk name → slots/<inactive>/files/<name>, via atomic writer;
 * names already manifest-validated; nested names create intermediate dirs via
 * platform_mkdir per component) → mark staged. Any failure: staged slot removed,
 * state unchanged except resume progress. */
bool break_update_client_stage(BreakUpdateClient *c, const BreakUpdateManifest *m,
                               const u8 pubkey[32], const char *channel, const char *platform,
                               BreakUpdateFetchFn fetch, void *user);
/* Atomically flip current → staged slot, pending=yes, confirmed=no, previous-* recorded.
 * Persists state BEFORE the flip becomes visible. False when no staged slot. */
bool break_update_client_activate(BreakUpdateClient *c);
/* Remove a staged (not yet activated) slot and clear it from state; false when none staged.
 * This is the ONLY way to clear a staged slot without activating it (rollback refuses
 * while staged exists). */
bool break_update_client_unstage(BreakUpdateClient *c);
```

- [ ] RED: tests fail (symbols absent).
- [ ] GREEN tests (end-to-end headless): fixture manifest + chunks → stage → activate → confirm; byte-exact slot content equals chunk bytes; signature-invalid → stage false (VERIFY), zero disk change AND zero fetch calls (signature before transport, gate-pinned); channel/platform mismatch → POLICY false; older-than-min-version → POLICY; activate without stage → false (STATE); rollback after activate (pre-confirm) → current flips back, pending cleared; rollback after confirm → allowed while previous retained, blocked below min-rollback floor; rollback while staged → false (STATE), then unstage → rollback allowed again; unstage without staged → false; full cycle re-stage over retained slot (A→B→A) correct; crash-simulation (kill between stage and activate via reopen) → state consistent (staged slot intact, current unchanged).
- [ ] Lanes ×3 green; ASan ×3 / TSan ×5 zero reports; `timeout -s KILL 60` direct runs exit 0.
- [ ] Commit.

### Task 4: Validation and documentation closeout

**Files:**
- Create: `docs/design/update_client.md`
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 5 subproject 2 → delivered client-side offline mechanics; download transport + gray-rollout client logic pending), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`, `docs/design/security_threat_model.md` (§4/§10 status sync)
- Modify: `engine/CMakeLists.txt` only if a real fix is needed.

- [ ] Clean normal tree: full default build + all lanes green (version/crypto/fs_write/update/update_client + contracts).
- [ ] ASan/UBSan + TSan trees green, zero reports; `ENGINE_BUILD_TESTS=OFF` tree builds; nm: production archives zero test-hook symbols (deferral #2 remains the sole documented exception); `BREAK_ENABLE_CRYPTO=OFF` tree still builds clean without update targets.
- [ ] Full non-graphics/non-fuzz suite; classify failures (graphics / platform-skip / pre-cleared flake / pre-existing drift / branch-caused=fix).
- [ ] Contract ctests green (all suites); `git diff --check` clean on branch range.
- [ ] update_client.md: state machine diagram (text), on-disk layout, byte-level resume semantics, write-ahead persistence ordering, rollback policy, transport seam contract (`BreakUpdateFetchFn` requirements: ranged reads, false=retryable), honest NOT-delivered list (real transport, gray rollout client logic, server).
- [ ] Cross-check roadmap acceptance lines for subproject 2: "Offline update rollback tests" — point to the specific tests; no claim of online/server behavior.

## Cross-cutting Review Gates

- RED before production code; GREEN normal/ASan/TSan after (three-tree evidence per task).
- No transport code: grep gate — no socket/HTTP/TLS/curl symbols introduced; `BreakUpdateFetchFn` is the only seam (review verifies).
- Signature before everything: `stage` must verify signature + policy BEFORE any fetch call (test pins zero fetch calls on VERIFY/POLICY failure).
- Write-ahead: every state mutation persists before visible effect; activation/rollback are data flips (no directory renames while live).
- CAS dedup: present chunks never re-fetched (call-count pins).
- Byte-exact: staged slot content == chunk bytes (hash-verified); resume resumes at byte boundary (offset asserted by fake).
- Bounded: state file ≤64 KiB; one `.part` at a time; manifest limits inherited.
- Fail closed + fixed error enum; no attacker-controlled strings; corrupt state → open fails (no repair heuristics).
- break_update stays out of engine/demos/editor link closures (contract).
- Docs honest: offline client mechanics only; server/transport/gray-rollout client logic pending; fuzz `Not Run`.
- A task completes only after focused code review, doc update, and `git diff --check` on its range.
