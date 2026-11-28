# core_app Keyring Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** core_app's network server accepts per-device keys from a keyring file (`--keyring-file PATH`) instead of one PSK from an environment variable, reloads the file while running, and revokes removed keys by closing their sessions.

**Architecture:** `CoreAppNetTransportConfig` gains `keyring_file`; exactly one of `psk_env` and `keyring_file` is set. With a keyring, `net_start` creates a `break_keyring` (capacity `CORE_APP_NET_KEYRING_CAPACITY` = 1024), loads the file (failure stops start), and installs `break_keyring_resolve` with `break_session_set_auth`. `net_tick` re-reads the file every `CORE_APP_NET_KEYRING_RELOAD_TICKS` ticks; the revoked callback calls `break_session_manager_close_key_id`, and the existing `net_sync_sessions` closes the transport of CLOSING sessions. Destroy follows the keyring contract: destroy the ring only after `break_session_set_auth(NULL, NULL)` returns true.

**Tech Stack:** C11, core_app transport (`engine/apps/core_app/core_app_net_transport.{h,c}`, `main.c`), `break_keyring`, `break_session`, CTest.

## Global Constraints

- Default behaviour unchanged: `--psk-env` keeps working exactly as today (fixed key id `coreapp1`).
- `--keyring-file` and `--psk-env` are mutually exclusive; `--network` requires exactly one of them.
- Keyring file format and limits are `break_keyring`'s (`<16 hex key id> <64 hex psk>`, ≤ 512 KiB); server capacity 1024; provision with `break_keygen --max-keys 1024`.
- A failed reload keeps the current ring and writes one trace line `COREAPPTRACE version=1 event=keyring result=rejected` when the state flips from accepted to rejected; an accepted reload after a rejection writes `result=reloaded keys=N`.
- The ring is destroyed only after `break_session_set_auth(NULL, NULL)` returns true; otherwise it is leaked with the transport (existing leak path).
- Builds: `build-aoi-net` (Snowflake + crypto, -Werror), `build-aoi-asan`; full ctest in `build-aoi-net` and `build-myui-tests` stays green.
- Every new behaviour gets targeted mutations that turn a test red.

---

### Task 1: core_app `--keyring-file`

**Files:**
- Modify: `engine/apps/core_app/core_app_net_transport.h` (config field, constants), `engine/apps/core_app/core_app_net_transport.c` (start/tick/destroy), `engine/apps/core_app/main.c` (flag, usage, validation)
- Test: `engine/tests/test_core_app_net_transport.c`; CLI validation where existing core_app CLI tests live (`engine/tests/test_core_app_network.cmake` or the core_app CLI test the repo already has — find the one that checks `--psk-env` errors)

**Interfaces:**
- Consumes: `break_keyring_create/destroy/load_file/resolve/count`, `BreakKeyringRevokedFn` (`engine/src/network/break_keyring.h`); `break_session_manager_close_key_id` (`engine/src/network/break_session.h`).
- Produces: `CoreAppNetTransportConfig.keyring_file` (`const char *`, NULL = not used); `CORE_APP_NET_KEYRING_CAPACITY 1024u`; `CORE_APP_NET_KEYRING_RELOAD_TICKS` (60u); test hook `core_app_net_transport_keyring_reload_for_test(CoreAppNetTransport *)` that runs one reload immediately (declared with the file's other `_for_test` hooks).

- [ ] **Step 1: Failing tests** in `test_core_app_net_transport.c` (collect results; destroy the transport and remove files before asserting):
  - `keyring_file_authenticates_listed_devices`: write a keyring with two keys; start the transport with `keyring_file` and no `psk_env`; connect with the AUTH v2 client helper using key A and then key B (the file's existing client helpers drive a real TLS connection — reuse them; set the client key id with `break_session_manager_set_client_key_id`); both reach authenticated (`stats.authenticated == 2`).
  - `keyring_reload_revokes_removed_device`: as above with key A connected; rewrite the file without A; call the reload hook; tick until the slot is closed; A's session is gone (`stats.closed` increments), a new connection with A fails to authenticate, and B still authenticates.
  - `keyring_reload_rejects_a_bad_file_and_keeps_the_ring`: rewrite the file with garbage; reload; trace contains `event=keyring result=rejected` once; A still authenticates; fix the file; reload; trace contains `result=reloaded keys=`.
  - `keyring_start_fails_on_a_bad_file`: start with a malformed keyring returns a failure and leaves no port file.
  - Config shape: `create` with both `psk_env` and `keyring_file`, or neither, returns NULL.
  - CLI: `--network` with both `--psk-env` and `--keyring-file`, or neither, exits with the usage error.
- [ ] **Step 2: Run** them in `build-aoi-net` — compile failure (no field/hook).
- [ ] **Step 3: Implement** as in Architecture. `net_auth_key` stays for the PSK path. Reload: read via `break_keyring_load_file(ring, path, net_keyring_revoked, t)`; `net_keyring_revoked` calls `break_session_manager_close_key_id(t->manager, key_id)`. Keep the last result to log only state flips.
- [ ] **Step 4: Run** the new tests and the whole `test_core_app_net_transport` in `build-aoi-net` and `build-aoi-asan`; full ctest in `build-aoi-net` and `build-myui-tests`.
- [ ] **Step 5: Mutations**: revoked callback does nothing; reload never called from tick; start ignores a bad file; trace logs on every rejected reload instead of on the flip; ring destroyed although `set_auth(NULL)` failed (assert via the existing leak-path test pattern if feasible, otherwise state it is covered by review).
- [ ] **Step 6: Docs**: `docs/design/core_app_integration.md` (network section: the flag, reload cadence, revocation, provisioning with `break_keygen --max-keys 1024`), `docs/design/transport_security.md` §4 ("no server product uses break_keyring yet" → core_app does), `docs/Implementation_Status.md` entry. Commit and push.
