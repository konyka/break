# Remaining features plan (2026-10-30)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans (or subagent-driven-development) to implement this plan task by task. Steps use checkbox (`- [ ]`) syntax.

**Goal:** Close the seven items left open in the deferred ledger of `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`: independent code review fixes, per-client undo, material/scene texture hot reload, LuaJIT evaluation, server authority + client anti-tamper, online update real transport + server, crash symbolization + upload.

**Architecture:** Each workstream is an independent optional library or editor extension with its own tests; none is linked into `engine` / `engine_demo` / `dxx_break` (the release-config contract pins this). Order: A (review fixes) -> B (per-client undo) -> C (texture reload) -> D (LuaJIT) -> E (authority + integrity) -> F (HTTP transport + update server) -> G (crash symbolize + upload; reuses F's HTTP client).

**Tech Stack:** C11, CMake, OpenSSL 3.5.9 (system), vendored Lua 5.4 (`engine/external/lua`), Snowflake (pinned) for the reactor, stb_image.

## Global Constraints

- TDD: write the failing test, run it red, implement, run it green. Mutation-check each new security rule (remove the check, the test must go red).
- Verification trees (already configured): `build-sdd-p4-final` (Snowflake + crypto, normal), `build-sdd-p4-asan` (ASan+UBSan). Build with `cmake --build <tree> -j8`, test with `ctest --output-on-failure -LE 'graphics|fuzz'` (graphics tests may be skipped when no display). The only known failure is the x11 fullscreen one.
- Release contract: `test_release_config_contract` and the per-library `*_target_contract.cmake` tests must stay green; new libraries must be absent from `engine`, `engine_demo`, `dxx_break` link closures and export no test hooks.
- Docs: every workstream updates its design doc, `docs/Implementation_Status.md` (new top entry, honest NOT-delivered list), the ledger in `2026-10-22-runtime-expansion-todo.md`, and `docs/design/security_threat_model.md` §10 when the security status changes.
- Never overwrite existing doc content; append or amend only the stale statements.
- One commit per task, pushed to `origin/master` after the tree is green (user instruction: no PR, merge straight to master).
- Do not claim what was not run: Windows/macOS lanes, real GPUs and WAN are out of reach on this host and stay listed as not delivered.

---

## Workstream A: independent review fixes

Findings from the independent reviewers (2026-10-30). Review 1 (tools) is in; review 2 (editor remote + msg_rate) is folded in as it arrives.

### Task A1: `break_manifest_tool` body validation and keygen overwrite safety

**Files:**
- Modify: `engine/tools/break_manifest_tool.c` (sign body parsing around the chunk-size and name checks; keygen public-key open)
- Test: `engine/tests/test_break_manifest_tool.cmake`

**Interfaces:** none new; behaviour only.

- [ ] Step 1: add failing cmake cases: (a) `sign` of a body whose chunk size is `99999999999999999999999` exits non-zero and writes no signature file; (b) a chunk name containing a NUL byte or a control byte exits non-zero; (c) `keygen K K` exits non-zero and leaves `K` untouched; (d) `keygen new_priv existing_priv` exits non-zero and leaves `existing_priv` byte-identical; (e) a chunk larger than 128 MiB (`134217729`) is refused by `build`/`sign` with a clear message.
- [ ] Step 2: run `ctest -R test_break_manifest_tool` in `build-sdd-p4-final`; expect the five new cases FAIL.
- [ ] Step 3: implement: size field at most 20 digits with explicit u64 overflow check; reject any byte outside 0x20-0x7E using explicit lengths (no `strchr`/`strlen` on possibly NUL-bearing input); open the public file with `open(O_WRONLY|O_CREAT|O_EXCL|O_NOFOLLOW, 0644)`; compare `stat` dev/inode of the two paths and refuse identical; cap chunk size at the client store limit; check `ferror` after reading the body; open the seed with `open`+`read` (unbuffered) and `explicit_bzero`/volatile wipe of the read buffer; `fstat` the key and refuse group/other-readable seeds.
- [ ] Step 4: rerun, expect PASS; mutation: drop the identical-path check, case (c) must go red.
- [ ] Step 5: commit `tools: manifest tool validates bodies like the client and never overwrites a key`.

### Task A2: `break_keygen` ring cap, atomic append, symlink safety

**Files:**
- Modify: `engine/tools/break_keygen.c`
- Test: `engine/tests/test_break_keygen.cmake`

- [ ] Step 1: failing cases: (a) a 1990-byte ring plus one new key (would exceed 2047 B) exits non-zero and leaves ring and device file absent; (b) the ring path being a symlink exits non-zero and the link target is unchanged; (c) an existing ring with mode 0644 is refused (or tightened to 0600; choose refuse, document); (d) the append is a single write: after a forced failure (read-only directory for the device file) the ring is byte-identical.
- [ ] Step 2: run red.
- [ ] Step 3: implement: `n + needs_lf + 82 <= 2047` check; open ring with `O_NOFOLLOW`, `fstat` regular file + mode check; compose LF+line in one buffer and `write` once, check full length; `flock(LOCK_EX)` on the ring for the duration; create the device file before the ring append and unlink it if the append fails; Windows branch documents that mode bits are not owner-only (no claim).
- [ ] Step 4: green + mutation (remove the cap check, case (a) red).
- [ ] Step 5: commit `tools: keygen keeps the keyring within the editor cap and appends atomically`.

### Task A3: review 2 findings (editor remote, msg_rate)

- [ ] Step 1: read the reviewer output (`agent-155`); verify each finding by reproducing it in a test before touching code; discard what does not reproduce.
- [ ] Step 2: for each confirmed finding, add a failing test in `engine/tests/test_editor_shell.c` or `engine/tests/test_break_msg_rate.c`, fix, rerun both trees, one commit per finding.
- [ ] Step 3: fix the stale text noted by review 1: `docs/design/update_client.md:297-298` still lists the rollout allow-list as undelivered.

### Task A4: record the review

- [ ] Add a "Independent review 2026-10-30" section to `docs/Implementation_Status.md` listing every finding, severity, disposition (fixed with commit / not reproduced / accepted with reason). Tick "Final independent code review" in the ledger only for the reviewed scope (2026-10-30 additions) and say so.

---

## Workstream B: per-client undo

**Design:** the shared stack stays. Each command is tagged with an origin id (`0` = local shell, `1..32` = remote connection slot generation id). A remote client's UNDO/REDO acts on the newest applied (REDO: oldest-undone... see below) command whose origin equals its own, only if no later command from another origin touches the same entity; otherwise the answer is `blocked` (new result code) and nothing changes. Rationale: undoing an old command under newer edits to the same entity corrupts state (the generation-restore redo mechanism in `editor_cmd.h` depends on adjacency), so selective undo is allowed only when it is provably independent.

**Files:**
- Modify: `engine/src/editor/editor_cmd.c`, `engine/src/editor/editor_cmd.h`, `engine/src/editor/editor_internal.h` (origin field on `BreakEditorCmd`), `engine/apps/editor/editor_remote.c`, `engine/src/editor/editor_protocol.h`, `docs/design/editor_remote.md`
- Test: `engine/tests/test_editor_cmd.c`, `engine/tests/test_editor_shell.c`, `engine/tests/fuzz_editor_remote.c` (new ids)

**Interfaces:**
- Produces: `void break_editor_doc_set_origin(BreakEditorDoc *doc, u32 origin);` (scopes subsequent pushes), `u32 break_editor_doc_origin(const BreakEditorDoc *doc);`, `bool break_editor_undo_origin(BreakEditorDoc *doc, u32 origin);`, `bool break_editor_redo_origin(BreakEditorDoc *doc, u32 origin);`, `u32 break_editor_cmd_stack_undo_count_origin(const BreakEditorCmdStack *s, u32 origin);`.
- Wire: `BREAK_EDITOR_MSG_UNDO_OWN = 19`, `BREAK_EDITOR_MSG_REDO_OWN = 20`, request empty, response `applied/u8` + `blocked/u8` (blocked=1 when the client has a command on the stack but a later foreign command on the same entity prevents it). Existing UNDO/REDO (global) keep their meaning.

### Task B1: origin tagging and independence rule in the command stack

- [ ] Step 1: failing tests in `test_editor_cmd.c`: (a) two origins each rename a different entity; `undo_origin(A)` reverts only A's rename, B's stays; (b) A renames entity E, B renames E afterwards; `undo_origin(A)` returns false (blocked) and both stay; (c) undo_origin then global redo restores identically and entity ids are exact; (d) `undo_count_origin` counts only that origin; (e) origin survives drop-oldest; (f) group commands inherit the origin of their creator.
- [ ] Step 2: run red (functions undefined).
- [ ] Step 3: implement: `origin` field set in `break_editor_cmd_stack_push_applied` from `doc->origin`; `undo_origin` scans from `undo_pos-1` down for the newest entry with that origin, checks that every later applied entry has a different origin AND a disjoint touched-entity set (each command already stores `id`; GROUP commands expose their children's ids via a new `touches(cmd, id)` vtable-free helper switch on `kind`); if independent: revert it, then rotate it to the top of the redo side by swapping with later entries only when they are independent, else refuse. To keep the generation-restore invariant, restrict to the SIMPLE case: the command must be adjacent after discounting entries from other origins that touch different entities; implement by physically moving the command to position `undo_pos-1` (shifting later independent entries down), then calling the existing revert and `undo_pos--`. Movement is safe because independence was proven.
- [ ] Step 4: green; mutation: skip the touched-entity check, test (b) must go red.
- [ ] Step 5: commit `editor: command stack tags origins and undoes independent commands per client`.

### Task B2: remote wiring and wire ids

- [ ] Step 1: failing tests in `test_editor_shell.c` (`remote_undo_own_only_reverts_this_clients_commands`): two TLS clients A and B; A spawns, B spawns; A sends UNDO_OWN -> only A's entity disappears (B's present); B renames A-independent entity, then A sends UNDO_OWN on a command whose entity B later edited -> `blocked=1`, doc unchanged; revoking A's key (existing keyring path) leaves its commands on the stack but later UNDO_OWN from a reused slot of a different connection must NOT see them (origin = per-connection monotonically increasing id, never the slot index).
- [ ] Step 2: run red.
- [ ] Step 3: implement: remote host assigns `origin = next_origin++` per accepted connection stored in the connection row (cleared in `remote_row_add` like `auth_key_known`); wrap every mutating handler in `set_origin(row.origin)` / `set_origin(0)`; add ids 19/20 to `k_handler_ids` and the protocol header; HISTORY keeps global numbers.
- [ ] Step 4: green on both trees; extend `fuzz_editor_remote.c` id range to 4..20 and run the ASan fuzz smoke (`ctest -L fuzz`).
- [ ] Step 5: docs: protocol table in `docs/design/editor_remote.md`, Implementation_Status entry, ledger line (remove "按客户端区分的 undo 未做"). Commit.

---

## Workstream C: material / scene texture hot reload

**Deviation found while reading the code (recorded 2026-10-30):** the original design drew entity proxies with their material's albedo texture. That is not derivable: the BSCN has no link from the editor's entities (ENTITIES/COMPONENTS chunks) to scene nodes or materials; `SCENE_NODES` carries `material_idx` per *node*, and nodes are a separate render graph that the editor keeps as opaque bytes. Mapping "the Nth entity to the Nth node" would be invented data, so it is NOT done. Delivered instead: a **Scene textures** view.

**Design:** the kept RESOURCES chunk (raw game bytes preserved by the editor) lists `BSCN_RES_TEXTURE` entries (source uri in `path`, max 63 chars) and `BSCN_RES_MATERIAL` entries (`tex_slots[5]` = albedo, metallic-roughness, normal, emissive, occlusion -> texture `ref_index`, v3 files only). The editor (1) parses that into a read-only model, (2) resolves each texture path against the scene file's directory (relative paths only; absolute paths, `..`, and over-long or non-printable names are rejected, never probed), (3) loads up to 8 of them as RHI textures with the existing image-preview machinery (each gets its own Runtime Core reload + file watch, so editing a PNG on disk updates the thumbnail), and (4) shows them in the assets panel area as a list of `name  WxH  used by N materials  state`, with the selected row's thumbnail. No new shaders: thumbnails use the existing myui blit.

**Files:**
- Create: `engine/src/editor/editor_scene_textures.{h,c}` (pure CPU model, in `break_editor` + `break_editor_test`), `engine/apps/editor/editor_scene_textures.{h,c}` (owner of up to 8 `BreakEditorImagePreview`), `engine/tests/test_editor_scene_textures.c`
- Modify: `engine/src/editor/editor_scene.{h,c}` (accessor for a kept chunk + the BSCN version it came from), `engine/src/editor/editor_internal.h` (`kept_version`), `engine/apps/editor/editor_panel_assets.c` and `editor_panels.c` (list + thumbnail, tick, device attach), i18n tables, `engine/CMakeLists.txt`, `docs/design/editor_hot_reload.md` (new section)
- Test: `engine/tests/test_editor_scene_textures.c`, `engine/tests/test_editor_shell.c`, `engine/tests/test_editor_i18n.c`

**Interfaces (produces):**

```c
/* src/editor/editor_scene.h */
bool break_editor_doc_kept_chunk(const BreakEditorDoc *doc, u32 chunk_type,
                                 const u8 **bytes, u32 *size, u32 *bscn_version);
/* src/editor/editor_scene_textures.h */
#define BREAK_EDITOR_SCENE_TEXTURES_MAX 64u
typedef struct { u32 ref_index; char path[64]; u32 used_by_materials; } BreakEditorSceneTexture;
typedef struct { u32 ref_index; u32 slot_texture[5]; /* ~0u = none/unknown */ } BreakEditorSceneMaterial;
u32 break_editor_scene_textures_parse(const BreakEditorDoc *doc, BreakEditorSceneTexture *out, u32 cap, BreakEditorSceneMaterial *mats, u32 mat_cap, u32 *mat_total);
bool break_editor_scene_texture_path_ok(const char *path);
bool break_editor_scene_texture_resolve(const char *scene_path, const char *uri, char *out, usize cap);
```

### Task C1: CPU model
- [ ] Failing `test_editor_scene_textures.c`: genuine BSCN from `scene_save_binary` (2 textures `a.png`/`b.png`, one material with albedo -> b), loaded with `break_editor_doc_load`; parse returns 2 textures with the right paths and `used_by_materials` 0/1, material slot 0 -> ref of b; v1/v2 layouts (hand-built chunk) parse without tex_slots and report slots as unknown; no RESOURCES chunk -> 0; truncated chunk / count larger than bytes -> 0 and no overflow; `path_ok` rejects empty, absolute, `..`, backslash, control bytes, > 63 chars; `resolve` joins against the scene file directory and rejects over-long results.
- [ ] Implement, green on both trees, mutation (drop the `..` check), commit.

### Task C2: owner with hot reload
- [ ] Failing tests in `test_editor_shell.c` with the fake RHI: set doc + scene path with 2 textures -> 2 textures created; rewrite one PNG with a new size -> replaced, old destroyed after the new exists; garbage keeps the old (failed counter); a path with `..` is never opened; reloading another scene drops textures not in the new list and stops watching them; more than 8 textures -> first 8 loaded, rest reported `skipped`; bounded shutdown with a held worker.
- [ ] Implement by composing `BreakEditorImagePreview` instances; green incl. ASan/TSan; commit.

### Task C3: panel + docs
- [ ] Failing shell test: panel rows text (`name WxH used by N` en + zh-CN), click selects a row and shows its thumbnail widget; i18n keys covered by `test_editor_i18n`.
- [ ] Implement; live run on this host (Vulkan and OpenGL: edit a PNG on disk, thumbnail changes) or record the exact reason it could not run; docs (`editor_hot_reload.md` section, Implementation_Status, ledger); commit and push.

---

## Workstream D: LuaJIT evaluation

**Scope:** an evidence-based go/no-go, not a mandatory integration. The runtime (`engine/src/script/break_lua*.c`) uses the Lua 5.4 C API (`lua_rotate`, `lua_pcallk`, `lua_absindex`, `lua_pushglobaltable`, `luaL_loadbufferx`, custom allocator via `lua_newstate` for the memory budget, `lua_sethook` for the instruction budget). LuaJIT implements the 5.1 ABI plus selected 5.2 extensions; the evaluation answers whether the contract tests can run against it and at what cost.

**Files:**
- Create: `docs/design/luajit_evaluation.md`, `engine/tests/bench_lua_backends.c` (EXCLUDE_FROM_ALL benchmark), `tools/luajit_probe/` is NOT added; probes run in `/tmp` and only results are recorded
- Modify: `docs/design/lua_runtime.md` (link), `docs/design/roadmap_2026-10-22.md` (subproject 5 status), ledger

### Task D1: fetch and build LuaJIT in a scratch dir

- [ ] Step 1: `git clone --depth 1 https://luajit.org/git/luajit.git /tmp/luajit-eval` (fall back to the GitHub mirror `LuaJIT/LuaJIT` on failure); record the commit hash and licence (MIT) in the doc. Build with `make -j8 XCFLAGS=-DLUAJIT_ENABLE_LUA52COMPAT`. Record: build time, GC64 on/off, `jit.status()` on this x86-64.
- [ ] Step 2: write `/tmp/luajit-eval/api_probe.c` that links `libluajit.a` and checks, one line of output per item: `lua_newstate` with a counting custom allocator succeeds and the allocator is used (LuaJIT 2.1 GC64 supports it; 2.0 does not), `lua_sethook(LUA_MASKCOUNT)` fires and can abort a `while true do end` loop, `luaL_loadbufferx`, `lua_absindex`, `lua_pushglobaltable`, `lua_rotate` (absent in 5.1: expect missing), `lua_pcallk` (absent), integer vs float number model (`lua_Integer` is double in LuaJIT: `2^53+1` round-trip), bitwise operators `&|~` (syntax error in LuaJIT; `bit` library instead), `goto` (supported), `utf8`/`string.pack` (absent).
- [ ] Step 3: record the table in `luajit_evaluation.md` verbatim from probe output (no guesses).

### Task D2: contract-test compatibility spike

- [ ] Step 1: compile the existing Lua test sources against a thin shim header `/tmp/luajit-eval/lua54_shim.h` that maps the missing 5.4 calls onto 5.1 equivalents (`lua_rotate`, `lua_pcallk` -> `lua_pcall`, `lua_absindex`); count how many of the `test_break_lua*` assertions fail and group failures by cause (integer subtype, bit operators in test scripts, `lua_rotate` semantic edge cases, `string.format('%d')` of floats, sandbox whitelist differences).
- [ ] Step 2: write the number: passed / total, plus the cause table, into the doc.

### Task D3: performance and memory

- [ ] Step 1: failing-first is not applicable for a benchmark; add `bench_lua_backends.c` (EXCLUDE_FROM_ALL) running three microbenchmarks (fib(32), table insert/sum 1e6, string concat/format 2e5) against Lua 5.4 and, when `-DBREAK_LUAJIT_EVAL_DIR=/tmp/luajit-eval` is passed, LuaJIT interpreter and JIT modes. Run 5 times each; record median and spread, and the allocator-accounted peak bytes.
- [ ] Step 2: record results and caveats (one host, no mobile/iOS; iOS forbids JIT, so LuaJIT there is interpreter-only; hot-reload state tables unaffected).

### Task D4: decision and gating

- [ ] Write the decision in `luajit_evaluation.md`: (a) adopt as optional backend behind `BREAK_LUA_BACKEND=luajit` only if the spike passes >= 95% of contract assertions with a documented shim and the memory budget/instruction budget work; otherwise (b) not adopted, with the specific blocking causes and what would have to change. If (a), the implementation is a separate plan (not in this one); if (b), close the ledger item as "evaluated, not adopted" with the evidence path. Update roadmap subproject 5 either way. Commit and push.

---

## Workstream E: server authority and client anti-tamper

**Design:** there is no game server in this repo, so deliver the reusable, testable server-side building blocks plus the client-side signal collector, with the trust boundaries enforced by construction.

- `break_authority` (server-side, `engine/src/authority/`): an intent/verdict engine. Intents carry `{session_id, sequence u64, kind, args}`; the engine rejects replays and gaps using `break_replay_window`, rate-limits with `break_msg_rate`, and applies kinds against server-owned ledgers: economy (balances in i64 with checked add/sub, never negative, per-kind max amount), inventory (slot table, item counts bounded), damage (server-computed from server-side attacker/target state; the client's reported damage value is not a parameter at all). Every verdict is `{OK, DENIED_*}` with a fixed enum; the ledger changes only inside `break_authority_apply`.
- `break_integrity` (client-side, `engine/src/integrity/`): collects tamper *signals* only: (1) self-hash of a caller-given list of files/regions against an expected SHA-256 (e.g. pak files, executable), (2) debugger present (`TracerPid` in `/proc/self/status` on Linux; `IsDebuggerPresent` on Windows is compile-only), (3) loaded-module allow-list check against `/proc/self/maps` basenames. Output is a bitmask `BreakIntegritySignals` consumed by the caller as one input for server-side risk scoring. The library has NO function that grants or denies anything; a contract test pins that the public header exports no `*_allow`/`*_grant` style symbol and that `break_authority` does not include the integrity header.

**Files:**
- Create: `engine/src/authority/break_authority.{h,c}`, `engine/src/integrity/break_integrity.{h,c}`, `engine/tests/test_break_authority.c`, `engine/tests/test_break_integrity.c`, `engine/tests/test_break_authority_target_contract.cmake`, `docs/design/server_authority.md`, `docs/design/client_integrity.md`
- Modify: `engine/CMakeLists.txt` (two optional static libs + tests + contract), `docs/design/security_threat_model.md` (§3, §10), `docs/Implementation_Status.md`, ledger

### Task E1: authority ledger primitives

**Interfaces (produces):**

```c
typedef enum { BAUTH_OK = 0, BAUTH_DENIED_REPLAY, BAUTH_DENIED_GAP, BAUTH_DENIED_RATE,
               BAUTH_DENIED_INVALID, BAUTH_DENIED_FUNDS, BAUTH_DENIED_LIMIT,
               BAUTH_DENIED_NO_SESSION } BreakAuthVerdict;
typedef struct BreakAuthority BreakAuthority;
BreakAuthority *break_authority_create(u32 max_sessions);
void break_authority_destroy(BreakAuthority *a);
bool break_authority_open_session(BreakAuthority *a, u64 session_id, i64 initial_balance);
void break_authority_close_session(BreakAuthority *a, u64 session_id);
BreakAuthVerdict break_authority_grant_server(BreakAuthority *a, u64 session_id, i64 amount); /* server-only entry; no intent path */
BreakAuthVerdict break_authority_intent_spend(BreakAuthority *a, u64 session_id, u64 sequence, u32 item_id, u32 qty, u64 now_us);
BreakAuthVerdict break_authority_intent_attack(BreakAuthority *a, u64 session_id, u64 sequence, u32 target_session, u64 now_us);
i64 break_authority_balance(const BreakAuthority *a, u64 session_id);
u32 break_authority_item_count(const BreakAuthority *a, u64 session_id, u32 item_id);
i32 break_authority_health(const BreakAuthority *a, u64 session_id);
```

- [ ] Step 1: failing tests: spend with enough funds deducts `price*qty` from a server-side price table and adds the item; insufficient funds -> `DENIED_FUNDS` and nothing changes; `qty` 0 or above the per-intent cap -> `DENIED_LIMIT`; `price*qty` overflow near `INT64_MAX` -> `DENIED_INVALID` (checked arithmetic); replay of the same sequence -> `DENIED_REPLAY`; sequence far ahead beyond the window -> `DENIED_GAP`; burst above the rate bucket -> `DENIED_RATE` (injected clock `now_us`); attack reduces the target's health by the server's weapon table amount (no client damage parameter exists); attacking a closed or unknown session -> `DENIED_NO_SESSION`; the attacker dead (health <= 0) -> `DENIED_INVALID`; balance can never go negative across a randomized 100k-intent sequence (property test with a fixed seed, invariant checked each step).
- [ ] Step 2: red; Step 3: implement over `break_replay_window` and `break_msg_rate` (reuse, do not copy); tables are fixed-size, no allocation after create; Step 4: green on both trees; mutations: remove the overflow check -> overflow test red; remove replay check -> replay test red.
- [ ] Step 5: contract cmake test (symbols, no test hooks, not linked into engine/demos/editor); commit.

### Task E2: integration with the transport identity

- [ ] Step 1: failing test `test_break_authority.c::session_id_comes_from_transport_not_payload`: a helper `break_authority_session_from_key(BreakConnectionKey key, u64 *out)` maps the authenticated connection key; an intent whose payload claims another session id is dropped before reaching the engine (the decode function has no session field in the wire struct). Test the decoder rejects payloads with a session field and accepts exactly the documented layout.
- [ ] Step 2-4: implement `break_authority_decode_intent(const u8 *p, usize n, BreakAuthIntent *out)` with exact-length parsing; green; Step 5: docs `server_authority.md` (state machine, wire layout, what stays game-specific), threat-model §3 changed from "design goals only" to "reference engine delivered; no game server", commit.

### Task E3: client integrity signals

**Interfaces (produces):**

```c
typedef u32 BreakIntegritySignals;
enum { BINT_SIG_FILE_MISMATCH = 1u<<0, BINT_SIG_DEBUGGER = 1u<<1, BINT_SIG_UNKNOWN_MODULE = 1u<<2, BINT_SIG_CHECK_ERROR = 1u<<3 };
typedef struct { const char *path; u8 sha256[32]; } BreakIntegrityFile;
BreakIntegritySignals break_integrity_check_files(const BreakIntegrityFile *files, u32 count);
BreakIntegritySignals break_integrity_check_debugger(void);
BreakIntegritySignals break_integrity_check_modules(const char *const *allowed_basenames, u32 count);
```

- [ ] Step 1: failing tests: a temp file with the correct hash -> 0; one flipped byte -> `FILE_MISMATCH`; missing file -> `CHECK_ERROR` (not silently clean); under `gdb --batch` or `ptrace(PTRACE_TRACEME)` in a forked child the debugger bit is set, in a normal process it is clear; modules check with an allow-list lacking `libc.so.6` sets `UNKNOWN_MODULE`, with the real list of this test binary's maps clear (build the list from `/proc/self/maps` in the test itself, then remove one entry for the negative case); count 0 / NULL args are bounded and return `CHECK_ERROR`.
- [ ] Step 2: red; Step 3: implement with `break_crypto` SHA-256 (streamed 64 KiB blocks); Linux real, other platforms return `CHECK_ERROR` for unsupported checks (documented, not faked); Step 4: green; Step 5: contract test: header has no allow/grant/deny symbols and `break_authority` sources never include `break_integrity.h`; docs `client_integrity.md` with the explicit statement "signals are risk inputs, never authority", threat-model §2/§10 updated; commit and push.

---

## Workstream F: online update real transport and reference server

**Design:** two new pieces. (1) `break_http` (client, `engine/src/net_http/`): a bounded HTTP/1.1 client over OpenSSL (`BIO`/`SSL`) with TLS certificate and hostname verification against a CA file (no insecure mode), `Range` GET, status/Content-Range/Content-Length validation, response body bounded by the caller's buffer, connect/read deadlines, and plain `http://` allowed only for loopback (127.0.0.0/8, ::1) so tests and local dev work without weakening production. It exposes an adapter `break_http_update_fetch` matching `BreakUpdateFetchFn`. (2) `break_update_server` (tool): a small blocking server (thread per connection, bounded) serving `/manifest`, `/manifest.sig`, `/objects/<sha256hex>` with `Range` support from a directory produced by `break_manifest_tool build`, over TLS with a given cert/key. It is a reference/e2e server, not a production deployment (documented).

Percentage source (rollout): the server serves `/rollout` as `<percent_bp>\n`; the client reads it with `break_http_get` (bounded 16 B, digits only, 0..10000) and passes it to the existing `stage_rollout`. Signature of the manifest is still verified offline with the pinned public key; the rollout value is advisory input with the same threat status as the allow-list (a lying server can only widen/narrow its own rollout, never bypass verification).

**Files:**
- Create: `engine/src/net_http/break_http.{h,c}`, `engine/tools/break_update_server.c`, `engine/tests/test_break_http.c`, `engine/tests/test_break_update_e2e.cmake` (+ helper `engine/tests/break_update_e2e.c`), `engine/tests/test_break_http_target_contract.cmake`, `docs/design/update_transport.md`
- Modify: `engine/CMakeLists.txt`, `docs/design/update_client.md` (online half), `docs/design/security_threat_model.md` §10 item 1, `docs/design/transport_security.md` (cross-reference), Implementation_Status, ledger

**Interfaces (produces):**

```c
typedef struct {
    const char *ca_file;         /* PEM; required for https */
    u32 connect_timeout_ms;      /* default 5000 */
    u32 io_timeout_ms;           /* default 10000 */
} BreakHttpConfig;
typedef enum { BHTTP_OK = 0, BHTTP_ERR_URL, BHTTP_ERR_CONNECT, BHTTP_ERR_TLS, BHTTP_ERR_TIMEOUT,
               BHTTP_ERR_STATUS, BHTTP_ERR_RANGE, BHTTP_ERR_TOO_BIG, BHTTP_ERR_PROTOCOL } BreakHttpError;
BreakHttpError break_http_get_range(const BreakHttpConfig *cfg, const char *url,
                                    u64 offset, u64 len, u8 *out, u64 *out_len);
BreakHttpError break_http_post(const BreakHttpConfig *cfg, const char *url,
                               const void *body, usize body_len, const char *content_type,
                               u8 *resp, usize resp_cap, usize *resp_len, int *status);
bool break_http_update_fetch(void *user, const char *object_name, u64 offset, u64 len, u8 *out); /* user = BreakHttpUpdateCtx* */
typedef struct { BreakHttpConfig cfg; char base_url[256]; } BreakHttpUpdateCtx;
```

### Task F1: `break_http` client core with a test server

- [ ] Step 1: failing `test_break_http.c`: the test spawns a tiny in-process loopback server thread (plain HTTP) that returns scripted responses. Cases: 206 with correct `Content-Range` fills `out` exactly; server returns 200 full body to a Range request -> `BHTTP_ERR_RANGE`; `Content-Range` mismatching the requested offset/len -> `ERR_RANGE`; body longer than `len` -> `ERR_TOO_BIG`; truncated body -> `ERR_PROTOCOL`; 404/500 -> `ERR_STATUS`; stalled server -> `ERR_TIMEOUT` within 2x the io timeout; redirects are NOT followed (3xx -> `ERR_STATUS`); header line > 8 KiB or > 64 headers -> `ERR_PROTOCOL`; `http://` to a non-loopback host -> `ERR_URL` without any connect attempt; `offset+len` overflow -> `ERR_URL`; url with CR/LF or userinfo -> `ERR_URL`.
- [ ] Step 2: red; Step 3: implement (blocking sockets with `poll` deadlines, hand-rolled bounded response parser; no `Transfer-Encoding: chunked` support in v1: respond `ERR_PROTOCOL`, documented); Step 4: green on both trees incl. ASan; Step 5: commit.

### Task F2: TLS with verification

- [ ] Step 1: failing tests using the existing self-signed fixture dir (`BREAK_TEST_SSL_FIXTURE_DIR`, same idiom as `test_break_net_tls`): https to a TLS test server with the right CA works; wrong CA -> `ERR_TLS`; hostname mismatch (connect to `127.0.0.1` with cert for `localhost`) -> `ERR_TLS`; expired or untrusted cert -> `ERR_TLS`; `ca_file == NULL` for https -> `ERR_URL` (no default-insecure); TLS < 1.2 refused (server forced to 1.1 in the test if the OpenSSL build allows, else documented skip with the reason).
- [ ] Step 2-4: implement with `SSL_CTX_set_min_proto_version(TLS1_2_VERSION)`, `SSL_VERIFY_PEER`, `SSL_set1_host`, CA file only (no system store, to keep the trust set explicit); Step 5: commit.

### Task F3: update server tool and end-to-end test

- [ ] Step 1: failing `test_break_update_e2e`: generate keys with `break_manifest_tool keygen`, build a manifest over temp chunk files with `build`, sign with `sign`; start `break_update_server --root <dir> --cert --key --port 0 --print-port`; client `break_update_client` fetches `/manifest` + `/manifest.sig`, verifies with the public key, `fetch_all` through `break_http_update_fetch` over TLS, `stage`, `activate`, `confirm_boot`; assert installed slot content hash equals the source; second run resumes: kill the server mid-download (server option `--drop-after N` bytes), restart, client resumes from the `.part` offset (assert the server saw `Range: bytes=N-`); a chunk tampered on the server -> VERIFY error, `.part` discarded, state unchanged; tampered manifest (flip a byte) -> parse/verify failure before any chunk request (server request counter stays 0 for `/objects/`).
- [ ] Step 2: red; Step 3: implement `break_update_server.c` (path whitelist `[0-9a-f]{64}` for objects, `Range` single-range only, no directory listing, no path traversal by construction since only fixed routes + hex names are accepted, bounded request size, max 16 concurrent connections, TLS required unless `--insecure-loopback`); Step 4: green; Step 5: `/rollout` route + client helper `break_http_rollout_percent_bp` with tests (non-digit, > 10000, > 16 B body all rejected); commit.

### Task F4: contract and docs

- [ ] `test_break_http_target_contract.cmake`: `break_http` absent from engine/demos/editor link closures, no test hooks, only `break_http_*` exports. Update `update_client.md` online half, threat-model §10 item 1 (real transport delivered; **still not delivered**: production CDN/server deployment, offline-signing key custody, chunked transfer-encoding, HTTP/2, proxy support), Implementation_Status, ledger. Commit and push.

---

## Workstream G: crash symbolization, clustering, regression stats, upload

**Design:** server-side half as library + tool, reusing `break_crash` records and F's HTTP client.

- `break_crash_symbolize` (library, `engine/src/crash/break_crash_symbolize.{h,c}`): ELF64 little-endian `.symtab`/`.dynsym` reader (bounds-checked, rejects overlapping/oversized sections) that resolves `address - module_load_offset` to the nearest preceding function symbol with size containment; frame recovery from the record: frame 0 = `rip`; further frames by walking the saved `rbp` chain through the stack window (each `[rbp]` = previous rbp, `[rbp+8]` = return address; every dereference must fall inside the window; max 32 frames; stops on non-monotonic rbp). Returns `{module, symbol, offset}` per frame or `unresolved`.
- `break_crash_cluster`: signature = SHA-256 of `signo | build-id | top-3 resolved symbol names (or module+offset when unresolved)`; independent of pid/tid/addresses (ASLR). Stats store: `{signature, first_build, last_build, count, per-build counts}` in a canonical text file, atomically replaced; regression = a signature seen in build N+1 whose count in a build marked `fixed-in` is non-zero (the store records `fixed_in` markers set by an operator command).
- `break_crash_server` (tool): receives `POST /crash` (TLS) with a redacted record; validates with `break_crash_record_parse` (reject anything non-canonical), symbolizes against a symbol directory `<root>/symbols/<build-id>/<module>` , appends to the stats store, replies `200` (stored, idempotent on identical record bytes hash for at-least-once uploads). Bounded body (64 KiB), rate limited per source IP by `break_msg_rate`.
- Upload (client): `break_crash_http_upload` adapter matching `BreakCrashUploadFn` using `break_http_post` (https required, same CA rule); `break_crash_spool_upload_pending` already provides at-least-once + backoff.

**Files:**
- Create: `engine/src/crash/break_crash_symbolize.{h,c}`, `engine/src/crash/break_crash_cluster.{h,c}`, `engine/tools/break_crash_server.c`, `engine/tools/break_crash_report.c` (prints stats), `engine/tests/test_break_crash_symbolize.c`, `engine/tests/test_break_crash_cluster.c`, `engine/tests/test_break_crash_e2e.cmake` (+ helper), `docs/design/crash_symbolization.md`
- Modify: `engine/CMakeLists.txt`, `engine/src/crash/break_crash.h` (no changes to the record grammar; only add `break_crash_http_upload` in a separate header `break_crash_upload_http.h` to keep the break_crash archive HTTP-free), `docs/design/crash_reporting.md` §9, Implementation_Status, threat-model §10 item 2, ledger

### Task G1: ELF symbol resolver

- [ ] Step 1: failing tests: compile a tiny fixture ELF at test time with the host compiler (`cc -g -O0 -fno-pie -no-pie fixture.c -o fixture`), read symbol addresses with the library, assert `resolve(addr_of(foo)+4)` -> `foo`, address past `foo`'s size -> unresolved, address in padding between functions -> unresolved, stripped binary (`strip`) -> all unresolved without error, truncated file / section header table pointing outside the file / `sh_entsize` 0 / symbol name offset outside strtab -> `NULL` handle (fuzz-style table of 8 corruptions), non-ELF / 32-bit / big-endian -> `NULL`, PIE load offset applied (test with `-pie` and an explicit offset).
- [ ] Step 2: red; Step 3: implement (mmap-free: read whole file bounded to 256 MiB, validate every offset with overflow-safe helpers); Step 4: green on both trees incl. ASan; add the resolver to the fuzz lane (`fuzz_crash_elf.c`, run the smoke); Step 5: commit.

### Task G2: frame recovery from a record

- [ ] Step 1: failing test: write a C fixture that crashes via `abort()` inside nested calls compiled with `-fno-omit-frame-pointer`, install `break_crash` in the child, let it crash, read the spooled record, then symbolize against the fixture binary: frame 0..2 names equal the known call chain (`leaf`, `mid`, `outer`) in order; a record whose window is too small stops early without reading out of bounds; a forged window where the saved rbp points backward is rejected at that frame; module not in the symbol dir -> `unresolved` frames kept in order.
- [ ] Step 2-4: implement; mutation: remove the monotonic-rbp check -> the forged-window test goes red (infinite-loop guard test with a 32-frame cap); Step 5: commit.

### Task G3: clustering and regression store

- [ ] Step 1: failing tests: same crash twice with different pid/tid/ASLR offset -> same signature; different top symbol -> different signature; unresolved frames cluster by module+offset; store roundtrip is byte-stable (canonical text, atomic replace, parse rejects any deviation like the other canonical files); counts per build correct after 1000 mixed adds; `mark_fixed(signature, build)` then a new occurrence in a later build -> reported as regression, in an earlier build -> not; store with > 4096 signatures evicts the lowest-count (documented) without breaking the file.
- [ ] Step 2-4: implement; Step 5: commit.

### Task G4: upload adapter, crash server and end-to-end

- [ ] Step 1: failing e2e (`test_break_crash_e2e`): start `break_crash_server --root R --cert --key --port 0`; a client process with `break_crash` installed crashes; the parent runs `break_crash_spool_upload_pending` with the HTTP adapter against the server; the stats store shows one signature with the resolved top symbol; uploading the same record again (at-least-once) does not increment the count (idempotent by record hash); a non-canonical body -> `400` and nothing stored; body > 64 KiB -> `413`; http (non-TLS) client URL for non-loopback -> adapter refuses before connecting; server killed mid-upload -> record stays pending with backoff bookkeeping (existing sidecar), next run succeeds.
- [ ] Step 2-4: implement `break_crash_upload_http.{h,c}` and the tool; Step 5: `break_crash_report R` prints top signatures and regressions (golden-output test); contract test: `break_crash` archive still has exactly its documented exports and no HTTP symbols; docs; commit and push.

---

## Final integration task

- [ ] Run the full suite on `build-sdd-p4-final` and `build-sdd-p4-asan` (`ctest -LE 'graphics|fuzz'` and `ctest -L fuzz`) and the Vulkan/OpenGL graphics-labelled editor tests that run on this host; record counts.
- [ ] Update `docs/Implementation_Status.md` (one entry per workstream with tests, mutation checks, and an honest NOT-delivered list), the ledger checkboxes (tick only what has evidence), `docs/design/security_threat_model.md` §9-§10, and the "Final independent code review" line (reviewed scope only).
- [ ] `git fetch && git rebase origin/master` if needed, push to `origin/master`, then check the CI run result with `gh run list` and fix anything the Windows/macOS lanes report (cross-platform guards: `NOT WIN32` for POSIX-only tools, `O_NOFOLLOW`/`flock` behind `#ifndef _WIN32`).

## Self-review notes

- Coverage: the user's seven items map to Workstreams A-G (LuaJIT evaluation = D, authority + anti-tamper = E, update transport + server = F, crash symbolization + upload = G, material/scene texture reload = C, per-client undo = B, independent review = A).
- Known scope limits stated up front: no production deployment of the servers, no Windows/macOS/mobile runs, no GPU pixel proof beyond the existing live-run method, anti-tamper stays advisory by design, LuaJIT adoption depends on the measured result.
- Names cross-checked: `BreakHttpConfig`/`break_http_*` (F) are the only HTTP surface consumed by G; `BreakEditorSceneTextures` composes the existing `BreakEditorImagePreview`; `break_editor_undo_origin` (B1) is what the wire ids 19/20 call in B2.
