# Scene Editor Phase 4 (Remote Session + Network Diagnostics Panel) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver Stage 4 Phase 4: an editor remote session (a break_net/break_session server hosted by the `editor` executable, secured by the Stage 5 Phase D transport contracts — TLS + CHALLENGE/AUTH-v2 + admission rate limits) that lets a remote client inspect the editor document and issue undoable doc commands (spawn/remove/rename/set-field/undo/redo/eval), plus a network diagnostics panel (pure view of reactor/session/admission state). The shell thread is the GameThread: one `break_session_manager_poll_adapter` per frame satisfies every owner-thread constraint (doc, Lua console, commands) with zero cross-thread dispatch.

**Architecture:** New `editor_remote` module in the editor app (mirroring `editor_panel_profiler.c` lifecycle: create/build/destroy/tick over `editor_shell_internal.h`). It owns a `BreakNetReactor` (STEP mode — the shell thread drives it explicitly in the frame loop; no host thread), a `BreakSessionManager` attached to that reactor, and a custom `BreakNetMessageRegistry` for editor message definitions (registered into the default registry's free id space ≥4 — the envelope codec only consults the default registry, `session_protocol.md:117`). Every frame `break_editor_shell_tick` calls the remote tick → `break_session_manager_poll_adapter` → handlers run on the shell thread and call `break_editor_doc_*` commands / `break_editor_undo|redo` / `break_editor_lua_eval` directly (all owner-thread-safe by construction). The remote protocol is version-tagged canonical binary messages over the existing 18-byte envelope. The network diagnostics panel follows the profiler panel's pure-view + ≤4 Hz snapshot discipline and never mutates.

**Tech Stack:** C11; `break_net`/`break_session` (Stage 5 Phase D: TLS, CHALLENGE/AUTH-v2, monotonic sequence, admission rate limits); `break_editor` doc command stack; `break_editor_lua` console; dummy-PAL headless shell tests + port-0 loopback condition-polling; ASan/UBSan/TSan.

## Global Constraints

- C11; zero new external dependencies. `break_net` is opt-in linked by the `editor` executable ONLY (engine/engine_demo/dxx_break no-link pins stay untouched; contract ctests updated to allow editor→break_net, mirroring the Phase 3 break_lua precedent).
- Security by construction, using Stage 5 Phase D as-is: TLS is REQUIRED for the remote session (plaintext mode is a test-only seam, documented); CHALLENGE/AUTH-v2 required (the editor refuses unauthenticated remote commands; key provisioning stays app-side — the editor ships a config-file/dev-key path documented as non-production); admission rate limits configured by default (global + per-IP, documented values); no remote debug surface exists when the session is disabled (default OFF — session starts only with explicit `--remote` flag or config, documented).
- Bounded everything: editor message registry ≤ 16 definitions (ids 4..19); inbound payload ≤ 4096 B (matches Lua eval bound); remote eval uses the same 4096 B cap and the console's own sandbox (no new Lua surface); connection table ≤ 32 entries in the editor_remote host; network panel snapshot ≤ 16 rows × 96 B; every remote command maps 1:1 to an existing undoable doc command (no raw world mutation).
- Owner-thread discipline: ALL doc/Lua/command access happens on the shell thread inside `poll_adapter` handlers; STEP-mode reactor is driven by the shell thread only (`break_net_reactor_step` atomic guard); no widget-event injection for remote commands (direct doc API per `editor_panels.h:16-21` layering).
- Fail closed: any protocol/parse/handler failure closes the connection (existing break_session discipline); remote eval failure returns the bounded console error lines, never partial record application (inherited from the Lua console contract); load/save are NOT exposed remotely this phase (documented — load's world-swap + selection reconcile needs a design of its own).
- Codec boundary honesty: editor message ids live in the default registry free id space (4..19); the custom-registry-only codec limitation is documented, not silently worked around.
- Three-tree lanes (normal / ASan+UBSan / TSan), contract ctests, nm export discipline, `ENGINE_BUILD_TESTS=OFF` tree; fuzz lane `Not Run` (house convention); Win32 lane untested (PAL compile-only precedent).
- Honest docs: remote session is a development/diagnostic tool, not a production deployment; TLS+auth are required but key provisioning is dev-path; the self-signed fixture and dev keys are test-only; no WAN claim.

---

## File and Target Map

- Create: `engine/apps/editor/editor_remote.h/.c` — remote session host (reactor + session manager + editor registry + connection table + protocol handlers).
- Create: `engine/apps/editor/editor_panel_network.c` — network diagnostics panel (pure view, ≤4 Hz snapshot).
- Create: `engine/src/editor/editor_protocol.h` — shared wire message definitions (ids, payload layouts, version) used by host and test client.
- Modify: `engine/apps/editor/editor_panels.c/.h` — tick wiring (call remote tick), panel registration, test accessors for remote/network panel state.
- Modify: `engine/apps/editor/editor_main.c` — `--remote`-flag / config plumbing (documented default OFF).
- Modify: `engine/tests/test_editor_shell.c` — headless remote tests (port-0 loopback client + condition polling).
- Modify: `engine/CMakeLists.txt` — editor links `break_net` (+`break_crypto` transitively); new TUs; contract ctest updates.
- Modify: `engine/tests/test_break_editor_target_contract.cmake` — allow editor→break_net (mirror break_lua precedent); no-link pins for engine/engine_demo/dxx_break unchanged.
- Docs: new `docs/design/editor_remote.md`; closeout touches `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 4 subprojects 6/7 status), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`.

---

### Task 1: Editor wire protocol + remote session host core (plaintext seam first)

**Files:**
- Create: `engine/src/editor/editor_protocol.h`
- Create: `engine/apps/editor/editor_remote.h`, `engine/apps/editor/editor_remote.c`
- Modify: `engine/apps/editor/editor_panels.c/.h` (tick wiring + test accessors)
- Modify: `engine/CMakeLists.txt`, `engine/tests/test_break_editor_target_contract.cmake`
- Modify: `engine/tests/test_editor_shell.c`

**Interfaces (verbatim):**
```c
/* engine/src/editor/editor_protocol.h — ids in the default-registry free space */
#define BREAK_EDITOR_PROTO_VERSION 1u
enum BreakEditorMessageId {
    BREAK_EDITOR_MSG_DESCRIBE = 4,   /* req: empty → rsp: version/u16, entity_count/u32, dirty/u8 */
    BREAK_EDITOR_MSG_LIST     = 5,   /* req: empty → rsp: count/u16 + per-entity {id/u64, name_len/u16, name} */
    BREAK_EDITOR_MSG_SPAWN    = 6,   /* req: name_len/u16 + name (0 = generated) → rsp: entity_id/u64 */
    BREAK_EDITOR_MSG_REMOVE   = 7,   /* req: entity_id/u64 → rsp: removed/u8 */
    BREAK_EDITOR_MSG_RENAME   = 8,   /* req: entity_id/u64 + name_len/u16 + name → rsp: ok/u8 */
    BREAK_EDITOR_MSG_SET_FIELD= 9,   /* req: entity_id/u64 + comp_len/u16+comp + field_len/u16+field + value/f32 → rsp: ok/u8 */
    BREAK_EDITOR_MSG_UNDO     = 10,  /* req: empty → rsp: applied/u8 */
    BREAK_EDITOR_MSG_REDO     = 11,  /* req: empty → rsp: applied/u8 */
    BREAK_EDITOR_MSG_EVAL     = 12,  /* req: text_len/u16 + text (≤4096) → rsp: ok/u8 + lines (console ring tail, bounded) */
    BREAK_EDITOR_MSG_RESULT   = 13   /* generic response wrapper: status/u8 (0 ok,1 invalid,2 failed) + payload */
};
/* Payloads are canonical little-endian binary, ≤ 4096 B, parsed with explicit
 * get16/get32/get64 — no structs on the wire, no unbounded reads. */
```

```c
/* engine/apps/editor/editor_remote.h */
typedef struct BreakEditorRemote BreakEditorRemote;
typedef struct BreakEditorRemoteConfig {
    const char *bind_host;          /* "127.0.0.1" default; documented loopback-first */
    uint16_t bind_port;             /* 0 = ephemeral (tests); actual port readable via accessor */
    uint32_t max_connections;       /* ≤ 32 */
    bool use_tls;                   /* false only for tests/dev (documented) */
    const char *tls_cert_file, *tls_key_file, *tls_ca_file;  /* required when use_tls */
    int tls_verify_peer;
    uint32_t rate_global_per_sec, rate_global_burst, rate_per_ip_per_minute; /* 0 = unlimited */
} BreakEditorRemoteConfig;
BreakEditorRemote *break_editor_remote_create(BreakEditorShell *shell, const BreakEditorRemoteConfig *cfg);
void break_editor_remote_destroy(BreakEditorRemote *r);
bool break_editor_remote_start(BreakEditorRemote *r);    /* fail-closed; false on config/startup error */
void break_editor_remote_tick(BreakEditorRemote *r);     /* shell thread, once per frame */
bool break_editor_remote_is_running(const BreakEditorRemote *r);
uint16_t break_editor_remote_port(const BreakEditorRemote *r);
uint64_t break_editor_remote_admission_denied(const BreakEditorRemote *r);
uint32_t break_editor_remote_connection_count(const BreakEditorRemote *r);
/* Test accessor: bounded snapshot of {connection_key, session_id, state} rows. */
uint32_t break_editor_remote_connections_snapshot(const BreakEditorRemote *r,
                                                  uint64_t *out_keys, uint32_t *out_states, uint32_t capacity);
```

- [x] RED: protocol parse tests + headless shell remote tests fail to build/link before implementation. *(closeout note: RED evidence lives with the Task 1–3 implementer runs; not re-run at Task 4 — GREEN re-verified at HEAD)*
- [x] GREEN tests: plaintext-seam loopback (port-0, condition polling, test client over raw socket): DESCRIBE returns version/entity_count/dirty; LIST returns entity rows; SPAWN creates entity (doc entity_count +1) and is undoable (Ctrl+Z reverts — pin); REMOVE/RENAME/SET_FIELD map to undoable commands; UNDO/REDO apply; EVAL `return 1+2` returns ok with `lua| 3` in the console ring; unknown id/malformed payload/oversize → connection closed (fail closed); disabled remote (no start) leaves shell untouched; tick wiring is per-frame (poll_adapter called each tick — counter pin).
- [x] Lanes: build-sdd-p4, -asan, -tsan; editor lane green ×3; ASan ×3 / TSan ×5 zero reports on new tests; contract ctest updated and green. *(re-verified at HEAD in Task 4: normal `build-sdd-p4-final`, `build-sdd-p4-asan` ×3, `build-sdd-p4-tsan` ×5, `test_editor_shell` 59/59, zero reports; contract 7/7 ×3)*
- [x] Commit. (`1af632eb`)

### Task 2: TLS + CHALLENGE/AUTH-v2 wiring (required for remote; plaintext stays test-only)

**Files:**
- Modify: `engine/apps/editor/editor_remote.h/.c`
- Modify: `engine/apps/editor/editor_main.c` (config plumbing)
- Modify: `engine/tests/test_editor_shell.c`

**Interfaces:** `BreakEditorRemoteConfig` as in Task 1 (verbatim, unchanged). Editor-side auth config: a documented dev-key file path (32 raw bytes) or `--remote-psk-hex` argument feeding the `BreakNetAuthKeyFn` seam; **production provisioning explicitly out of scope** (documented).

- [x] RED: TLS+auth loopback tests fail before wiring (no TLS config path). *(closeout note: RED evidence lives with the Task 1–3 implementer runs; not re-run at Task 4 — GREEN re-verified at HEAD)*
- [x] GREEN tests: full handshake over TLS + AUTH-v2 with test fixture certs (reuse `BREAK_TEST_SSL_FIXTURE_DIR` idiom): authenticated client issues DESCRIBE/SPAWN successfully; unauthenticated client (no AUTH v2 / bad tag / unknown key) → closed, zero doc effect; plaintext config → start false when `use_tls` true and certs missing; rate-limit denials observable via `break_editor_remote_admission_denied`; `use_tls=false` documented test-only path still works (Task 1 suite); main.c `--remote` flag absent → no listener (nm/behavior pin).
- [x] Lanes ×3 green; ASan ×3 / TSan ×5 zero reports; timeout-wrapped direct runs. *(re-verified at HEAD in Task 4: normal `build-sdd-p4-final`, `build-sdd-p4-asan` ×3, `build-sdd-p4-tsan` ×5, `test_editor_shell` 59/59, zero reports; contract 7/7 ×3)*
- [x] Commit. (`7fc7a1ef` + review round 1 `ca9a2785`)

### Task 3: Network diagnostics panel (pure view)

**Files:**
- Create: `engine/apps/editor/editor_panel_network.c`
- Modify: `engine/apps/editor/editor_panels.c/.h`, `engine/apps/editor/editor_shell_internal.h`
- Modify: `engine/tests/test_editor_shell.c`

**Interfaces (verbatim):**
```c
/* editor_panel_network — mirrors editor_panel_profiler lifecycle exactly */
BreakEditorPanelNetwork *editor_panel_network_create(BreakEditorShell *shell, BreakEditorRemote *remote);
void editor_panel_network_destroy(BreakEditorPanelNetwork *p);
void editor_panel_network_build(BreakEditorPanelNetwork *p, MyWidget *parent);
void editor_panel_network_tick(BreakEditorPanelNetwork *p);   /* ≤ 4 Hz snapshot, never mutates */
/* Snapshot rows (fixed storage ≤16 × 96 B, refreshed on tick):
 *   reactor: running/tls/outbound/admission_denied
 *   session: applied/unknown/stale/invalid/phase_rejected/duplicate/handler_failed (7 counters)
 *   connections: count + per-row {connection_key, state} */
uint32_t editor_panel_network_row_count(const BreakEditorPanelNetwork *p);
const char *editor_panel_network_row_text(const BreakEditorPanelNetwork *p, uint32_t index);
```

- [x] RED: panel tests fail before implementation. *(closeout note: RED evidence lives with the Task 1–3 implementer runs; not re-run at Task 4 — GREEN re-verified at HEAD)*
- [x] GREEN tests: panel rows populate after a loopback connect + commands (reactor/session counters match `break_session_manager_apply_stats` + reactor accessors byte-for-byte); ≤4 Hz throttle pinned (two ticks within 250 ms → row storage unchanged); remote==NULL → bounded "remote: off" row; panel never calls send/close/transition (source-scan + behavior pin); layout presence (panel registered under diagnostics area, documented placement).
- [x] Lanes ×3 green; ASan ×3 / TSan ×5 zero reports. *(re-verified at HEAD in Task 4: normal `build-sdd-p4-final`, `build-sdd-p4-asan` ×3, `build-sdd-p4-tsan` ×5, `test_editor_shell` 59/59, zero reports; contract 7/7 ×3)*
- [x] Commit. (`5df792cd` + review round 1 `357be082`)

### Task 4: Validation and documentation closeout

**Files:**
- Create: `docs/design/editor_remote.md`
- Modify: `docs/Implementation_Status.md`, `docs/design/roadmap_2026-10-22.md` (Stage 4 subproject 6 → network panel delivered, render debugger pending; subproject 7 → remote session delivered dev-tool form), `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`

- [x] Clean normal tree: full default build + editor lane + break_net lanes green; `ENGINE_BUILD_TESTS=OFF` tree builds `editor`; nm: `editor` links break_net, engine/engine_demo/dxx_break zero break_net/break_crypto symbols (contract).
- [x] ASan/UBSan + TSan trees green, zero reports; contract ctests green ×3.
- [x] Full non-graphics/non-fuzz suite; classify failures per house convention. (203 = 202 passed + 1 Windows-only skip, 0 failed)
- [x] Remote end-to-end over TLS+AUTH-v2 from a scripted client (test binary): connect → auth → describe → spawn → undo → disconnect; record the transcript in the report.
- [x] editor_remote.md: protocol reference (message table, payload layouts, error taxonomy), security model (TLS+AUTH-v2 required, dev-key provisioning non-production, default OFF, loopback-first bind, rate limits), threading model (shell thread = GameThread, STEP mode rationale), codec-boundary note (default-registry id space 4..19), NOT-delivered (remote load/save, remote render control, production credential system, WAN/multi-client management, remote undo-stack sharing, render debugger panel).
- [x] `git diff --check` clean on branch range.

## Cross-cutting Review Gates

- RED before production code; GREEN normal/ASan/TSan after.
- Security default: remote session OFF unless explicitly enabled; TLS+AUTH-v2 REQUIRED for remote commands; plaintext only in tests/dev with documented flag; no unsigned/unauthenticated command path.
- Owner-thread discipline: zero cross-thread doc/Lua/command access (reviewer verifies every handler runs under `poll_adapter` on the shell thread).
- Command purity: every remote mutation maps 1:1 to an existing undoable doc command; Ctrl+Z reverts a remote spawn (test pin); no raw world pointers.
- Bounded: registry ≤16 ids (4..19), payload ≤4096 B, connection table ≤32, panel rows ≤16×96 B.
- Fail closed: protocol/parse/handler failure → connection closes; eval failure → bounded error lines, zero partial record application.
- Plaintext regression: editor shell with no remote configured is byte-identical in behavior (existing editor lane proves it).
- No-link discipline: engine/engine_demo/dxx_break never gain break_net/break_crypto symbols (contract pins).
- Docs honest: dev-tool framing, dev-key provisioning non-production, no WAN/multi-client/production claims; remote load/save explicitly deferred.
- A task completes only after focused code review, doc update, and `git diff --check` on its range.
