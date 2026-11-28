# Device Keyring Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** A reusable per-device keyring for `break_net` servers (load, diff-reload, add, remove, constant-time lookup), a session call that closes every session of a revoked `key_id`, and the editor and `break_keygen` moved onto it.

**Architecture:** `break_keyring` is a pure C11 library in `engine/src/network/` (no Snowflake), compiled into `break_net` and testable on its own. `break_session` gains `break_session_manager_close_key_id`. The editor keeps its process-global auth slot (it guards against a refused auth clear leaving a dangling pointer) and only replaces its private file parser and diff logic with the library. `break_keygen` gains `--max-keys`.

**Tech Stack:** C11, CMake/CTest, the repo's `test_framework.h`, `break_crypto` (CSPRNG), Snowflake loopback for session tests.

Spec: `docs/superpowers/specs/2026-11-28-device-keyring-design.md`.

## Global Constraints

- Keyring file format unchanged: each line `<16 hex key id> <64 hex psk>`, `#` comments and blank lines skipped, `\r\n` accepted, key ids unique.
- `BREAK_KEYRING_MAX_KEYS` = 4096; `BREAK_KEYRING_MAX_FILE_BYTES` = 512 KiB (524288).
- Editor capacity stays 8; the editor's public API and behaviour do not change.
- `break_keygen` default behaviour unchanged (8 keys, 2047-byte ring).
- Key bytes are wiped with volatile stores on remove, replace, destroy and parser-buffer release.
- Lookup compares every slot without an early exit.
- Builds and tests: `build-aoi-net` (Snowflake + crypto, normal), `build-aoi-asan`, `build-aoi-tsan`; `build-myui-tests` full ctest must stay green; warnings are errors.
- Every new behaviour gets targeted mutations that turn a test red.

---

### Task 1: `break_keyring` library

**Files:**
- Create: `engine/src/network/break_keyring.h`, `engine/src/network/break_keyring.c`
- Create: `engine/tests/test_break_keyring.c`
- Modify: `engine/CMakeLists.txt` (add the source to `break_net`, and a standalone test target next to `test_break_identity_rate`)

**Interfaces:**
- Produces (exact):

```c
#define BREAK_KEYRING_MAX_KEYS 4096u
#define BREAK_KEYRING_MAX_FILE_BYTES (512u * 1024u)
typedef struct BreakKeyring BreakKeyring;
BreakKeyring *break_keyring_create(u32 capacity);
void break_keyring_destroy(BreakKeyring *ring);
bool break_keyring_add(BreakKeyring *ring, const u8 key_id[8], const u8 psk[32]);
bool break_keyring_remove(BreakKeyring *ring, const u8 key_id[8]);
u32 break_keyring_count(const BreakKeyring *ring);
bool break_keyring_resolve(void *ring, const u8 key_id[8], u8 out_psk[32]);
typedef void (*BreakKeyringRevokedFn)(void *user, const u8 key_id[8]);
typedef enum BreakKeyringLoadResult {
    BREAK_KEYRING_LOAD_OK = 0,
    BREAK_KEYRING_LOAD_UNREADABLE,
    BREAK_KEYRING_LOAD_MALFORMED,
    BREAK_KEYRING_LOAD_TOO_LARGE,
    BREAK_KEYRING_LOAD_EMPTY
} BreakKeyringLoadResult;
BreakKeyringLoadResult break_keyring_load_file(BreakKeyring *ring, const char *path,
                                               BreakKeyringRevokedFn revoked, void *user);
/* Same as load_file on an in-memory buffer (len bytes, need not be NUL
 * terminated); used by callers that already read the file. */
BreakKeyringLoadResult break_keyring_load_text(BreakKeyring *ring, const char *text,
                                               usize len, BreakKeyringRevokedFn revoked,
                                               void *user);
/* Copies the i-th used key (0-based, insertion order) into id/psk; false
 * when i >= count. For callers that mirror the ring into their own store. */
bool break_keyring_key_at(const BreakKeyring *ring, u32 index, u8 key_id[8], u8 psk[32]);
```

- [ ] **Step 1: Write the failing tests** in `engine/tests/test_break_keyring.c`. Write the helper files to the working directory (`ctest` runs from the build tree); remove them before asserting. Cases:
  - `keyring_add_remove_and_capacity`: create(0) and create(4097) are NULL, create(1) and create(4096) succeed; add then add the same id is false; a full ring refuses; remove of an absent id is false; count tracks.
  - `keyring_resolve_returns_the_psk_and_leaves_misses_alone`: hit copies the 32 bytes; miss returns false and leaves a pre-filled 0xAA output untouched; NULL ring/id/out false.
  - `keyring_load_accepts_comments_blank_lines_and_crlf`: two keys with a `#` line, an empty line and `\r\n`; result OK, count 2, both resolve.
  - `keyring_load_rejects_each_malformed_shape_and_leaves_the_ring`: ring preloaded with one key; each of: 80-char line, missing space, non-hex id, non-hex psk, duplicate id, 3 keys into a capacity-2 ring (TOO_LARGE), only comments (EMPTY), nonexistent path (UNREADABLE); after each, count is 1, the original key resolves, and the revoked callback count is 0.
  - `keyring_load_rejects_an_oversized_file`: a file of BREAK_KEYRING_MAX_FILE_BYTES + 1 bytes of `#` comment lines → TOO_LARGE.
  - `keyring_reload_applies_the_difference`: ring {A, B, C}; file {A (same psk), B (new psk), D}; result OK; revoked called exactly for B and C (record ids in order seen); A, B(new), D resolve; C does not; count 3.
  - `keyring_revoked_sees_the_id_before_the_wipe`: the callback calls `break_keyring_resolve` for the id it was given and records the result; expect false (already removed from lookup) but the id argument itself equals the removed id byte-for-byte.
  - `keyring_load_text_matches_load_file`: same content through both entry points gives the same count and resolutions.
  - `keyring_key_at_walks_insertion_order`: three adds, remove the middle one; `key_at(0)` and `key_at(1)` give the first and third keys, `key_at(2)` is false; NULL arguments are false.
- [ ] **Step 2: Add CMake and run to verify RED.** In `engine/CMakeLists.txt` after the `test_break_identity_rate` block add:

```cmake
    add_executable(test_break_keyring tests/test_break_keyring.c
        src/network/break_keyring.c)
    target_include_directories(test_break_keyring PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_break_keyring COMMAND test_break_keyring)
    set_tests_properties(test_break_keyring PROPERTIES LABELS "headless;security")
```

  Run: `cmake build-aoi-net && cmake --build build-aoi-net --target test_break_keyring`
  Expected: configure fails because `src/network/break_keyring.c` does not exist.
- [ ] **Step 3: Implement** `break_keyring.{h,c}`: a header comment stating the file format, the all-or-nothing load, the constant-time lookup and the ownership (one owner, Logic thread). Storage: `struct { u8 used; u8 key_id[8]; u8 psk[32]; } *slots` of `capacity`, plus `count`. `resolve` loops over all `capacity` slots, computes `diff` with XOR over the 8 bytes for each used slot and selects with a mask (no branch that exits early), then copies the selected PSK only when a match was found. `load_text` parses into a heap scratch array of `capacity` entries, checking line shape, hex and duplicates, then applies: first pass removes (calling `revoked` before the wipe) every current key not present with the same PSK, second pass adds every new key. Wipe helper: `static void keyring_wipe(void *p, usize n)` with a `volatile u8 *` loop. `load_file` opens with `fopen(path, "rb")`, `setvbuf(_IONBF)`, reads up to `BREAK_KEYRING_MAX_FILE_BYTES + 1` into a heap buffer, returns TOO_LARGE when that extra byte is read, otherwise calls `load_text`, then wipes and frees the buffer.
- [ ] **Step 4: Run** `./build-aoi-net/test_break_keyring` — all pass. Add `src/network/break_keyring.c` to the `break_net` source list (after `break_identity_rate.c`) and rebuild `break_net`.
- [ ] **Step 5: Mutations** (each must turn a case red, then restore): skip the duplicate check; accept a 15-char id; off-by-one capacity check in `add`; `load_text` applies changes before validating the whole file; `revoked` not called for a re-keyed id; resolve copies the PSK on a miss; `create` accepts capacity 4097; oversized-file check off by one.
- [ ] **Step 6: Sanitizers and commit.** Run under `build-aoi-asan` (with leak detection) and `build-aoi-tsan`. Commit `network: add a reusable per-device keyring with diff reload`.

### Task 2: `break_session_manager_close_key_id`

**Files:**
- Modify: `engine/src/network/break_session.h`, `engine/src/network/break_session.c`
- Test: `engine/tests/test_break_session.c`

**Interfaces:**
- Consumes: `break_keyring_resolve`, `break_keyring_load_file` (Task 1).
- Produces:

```c
#ifdef BREAK_ENABLE_CRYPTO
/* Closes (CLOSING) every authenticated session whose AUTH v2 key_id equals
 * key_id and returns how many. Logic thread. */
size_t break_session_manager_close_key_id(BreakSessionManager *manager,
                                          const u8 key_id[8]);
#endif
```

- [ ] **Step 1: Write the failing tests** (inside the `BREAK_ENABLE_CRYPTO` block, collect results and assert only after cleanup, as the identity-rate tests do):
  - `break_session_close_key_id_closes_only_that_identity`: one manager, two loopback AUTH v2 connections, one with `break_session_auth_key_id` and one with the all-zero id (`keys.allow_default = true`). `close_key_id(test id)` returns 1; that connection is CLOSING, the other AUTHENTICATED; a second call returns 0; NULL manager or id returns 0.
  - `break_session_keyring_reload_revokes_live_sessions`: auth callback `break_keyring_resolve` on a ring loaded from a temp file with the test key; authenticate; rewrite the file without that key; `break_keyring_load_file(ring, path, revoked_cb, manager)` where `revoked_cb` calls `close_key_id`; the session is CLOSING; a new connection with the same key fails to authenticate (CLOSING after its AUTH).
  Two loopback connections need two fixtures sharing one manager; add a helper `break_session_auth_fixture_open_second(BreakSessionAuthFixture *first, BreakSessionAuthFixture *second)` that connects a second socket to `first->acceptor`, pumps until a new `CONNECTION_OPENED` key appears and reads its CHALLENGE, and sets `second->manager`/`reactor` to the first's (with a `borrowed` flag so `fixture_close` does not destroy them).
- [ ] **Step 2: Run** `cmake --build build-aoi-net --target test_break_session` — fails to compile (no `break_session_manager_close_key_id`).
- [ ] **Step 3: Implement**: loop over `manager->entries`; for used entries with `key_id_valid` and `state == AUTHENTICATED` whose `key_id` matches, call `break_session_manager_close(manager, entry->connection, 0u)`, clear `key_id_valid`, count. Return 0 for NULL arguments.
- [ ] **Step 4: Run** the session test in `build-aoi-net`, `build-aoi-asan`, `build-aoi-tsan` — all pass.
- [ ] **Step 5: Mutations**: no key comparison (closes all); does not clear `key_id_valid` (second call returns 1); ignores state (closes a NEW session); revoked callback not wired in the reload test path. Each turns a case red.
- [ ] **Step 6: Commit** `network: close every session of a revoked key_id`.

### Task 3: Editor uses `break_keyring` for parsing and diff

**Files:**
- Modify: `engine/apps/editor/editor_remote.c` (`remote_keyring_file_read`, `break_editor_remote_reload_keyring`)
- Test: `engine/tests/test_editor_shell.c` (unchanged; regression gate)

**Interfaces:**
- Consumes: `break_keyring_create`, `break_keyring_add`, `break_keyring_load_text`, `break_keyring_load_file`, `break_keyring_key_at`, `break_keyring_count`, `break_keyring_destroy`, `BreakKeyringRevokedFn` (Task 1).

The editor keeps `EditorRemoteKey keys[8]`, the static `g_editor_remote_auth` slot, `add_key`/`revoke_key` and its connection-row bookkeeping. Only the file parser and the reload diff change.

- [ ] **Step 1: Record the baseline**: run `./build-aoi-net/test_editor_shell` and save the Results line (all keyring tests listed in the spec must pass).
- [ ] **Step 2: Replace `remote_keyring_file_read`**: keep the file read (unbuffered, ≤ 2047 bytes, oversize rejected) and then parse with a temporary `break_keyring_create(8)` + `break_keyring_load_text(tmp, text, n, NULL, NULL)`. On OK, copy the `break_keyring_count(tmp)` keys into `out->keys` with `break_keyring_key_at`, set `out->key_count`, then wipe the text buffer and destroy the temporary ring. Any non-OK result returns false with `out->key_count = 0` and `out->keys` wiped, as today.
- [ ] **Step 3: Replace the diff in `break_editor_remote_reload_keyring`**: build a ring of capacity 8 mirroring the current `r->keys` (add each used key), call `break_keyring_load_file(ring, path, editor_revoked_cb, r)` where `editor_revoked_cb` calls `break_editor_remote_revoke_key(r, id)`; on OK, add every key of the ring not present in `r->keys` via `break_editor_remote_add_key`; destroy the ring. A non-OK result returns false and changes nothing (the callback is never called on failure).
- [ ] **Step 4: Run** `./build-aoi-net/test_editor_shell` — the Results line equals the baseline. Run it under `build-aoi-asan` too.
- [ ] **Step 5: Mutations**: the editor revoke callback does nothing (`remote_tls_keyring_reload_revokes_removed_keys` red); reload skips adding new keys (`remote_tls_keyring_reload...` or `remote_tls_cli_keyring_file_installs_all_keys` red).
- [ ] **Step 6: Commit** `editor: parse and diff the remote keyring with break_keyring`.

### Task 4: `break_keygen --max-keys`

**Files:**
- Modify: `engine/tools/break_keygen.c`
- Test: `engine/tests/test_break_keygen.cmake`

**Interfaces:** CLI only: `break_keygen [--max-keys N] <keyring> <16 hex key id> <device psk file>`, N in 1..4096, default 8. The ring byte limit becomes `N == 8 ? 2047 : BREAK_KEYRING_MAX_FILE_BYTES - 1` (the editor limit is kept for the default so editor rings stay loadable).

- [ ] **Step 1: Write the failing tests** in `test_break_keygen.cmake`: `--max-keys 9` accepts a 9th key into a ring that the default refuses at 9; `--max-keys 0`, `--max-keys 4097` and `--max-keys x` exit 2 and change no file; the default (no flag) still refuses the 9th key.
- [ ] **Step 2: Run** `ctest -R test_break_keygen` in `build-aoi-net` — fails (unknown flag / usage error).
- [ ] **Step 3: Implement**: parse an optional leading `--max-keys N` (strict decimal, 1..4096), replace the `KG_MAX_KEYS`/`KG_MAX_RING` constants by locals, size the scan buffer on the heap when the limit exceeds the stack buffer. Update the header comment and usage text.
- [ ] **Step 4: Run** `ctest -R test_break_keygen` — passes, existing cases unchanged.
- [ ] **Step 5: Mutations**: accept N = 4097; ignore the flag (always 8). Both red.
- [ ] **Step 6: Commit** `tools: let break_keygen size rings for break_keyring servers`.

### Task 5: Full verification and documentation

**Files:**
- Modify: `docs/design/transport_security.md` (§4 key lifecycle: delivered pieces), `docs/design/security_threat_model.md` (credential row), `docs/design/editor_remote.md` (keyring now backed by `break_keyring`), `docs/Implementation_Status.md` (new entry), `docs/superpowers/specs/2026-11-28-device-keyring-design.md` (status line: implemented, add `break_keyring_key_at` and `break_keyring_load_text` to §4.1).

- [ ] **Step 1:** Full ctest in `build-aoi-net` and `build-myui-tests`; `build-current-vk` builds.
- [ ] **Step 2:** Update the docs listed above with what shipped, test counts and mutation results; state the remaining boundary (no device enrolment, no escrow, no cross-process revocation, POSIX-only file guarantees).
- [ ] **Step 3:** Commit `docs: record the device keyring` and push to `origin/master`.
