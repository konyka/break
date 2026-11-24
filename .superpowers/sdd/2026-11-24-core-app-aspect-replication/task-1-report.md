# core_app aspect replication — Task 1 report

## Scope and implementation

- Worktree: `/home/timeshift/opensource/break/.worktrees/core-app-aspect`
- Branch: `feature/core-app-aspect`
- Baseline: `f882b28855b72f1efc9c82621f9c0ff69cf868f3`
- Added default-off `--aspect-replication` help and parsing. The option participates in `net_option_seen`, so use without `--network` is rejected through the existing network-option validation.
- Added transport-owned authoritative and diagnostic inbound stores with identical six-field POD schemas, fixed handles `{index=1,generation=1}` and `{index=2,generation=1}`, spatial indexing, replication, and aspect session/bridge on the owner thread.
- Registered message `0x4009` with the session bridge as `user_data`; opened both per-connection sides after `net_slot_add` and before adapter-event application, with rollback. Close and destroy disconnect replication before closing the session and release AOI results/scopes.
- Added session tick plus bounded drain (64 packets) after normal and shutdown pumps, AOI sync after welcomes, and direct send-result forwarding. Added enabled-only `event=network_aspect_stats`; existing `network_stats` text is unchanged.
- The inbound store is only drained for diagnostics. It has no simulation or World pointer, and the drain test confirms the authoritative object revision is unchanged by inbound application.

Implementation choices, not protocol deviations:

- The existing registration API allocates from index 0. Authoritative store slot 0 is therefore reserved so the two replicated objects have the required fixed indices 1 and 2; the inbound store adopts only those two handles.
- Schema IDs 1..6 copy index, generation, x/y/z, and flags from the two existing snapshot POD entities.
- Both objects use `BREAK_AOI_OBJECT_ALWAYS_RELEVANT`; AOI computation uses zero witnesses and a per-connection previous scope. Scope advancement occurs only after a fully successful replication sync.
- Test-only state inspection and direct AOI-sync entry points are under `CORE_APP_NET_TRANSPORT_TESTING`; production `core_app` exports no test hook, as verified by the target contract.

## RED evidence

Tests were added before production implementation:

1. `cmake --build engine/build --parallel 4 --target test_core_app_net_transport`
   - Failed at compile time because `CoreAppNetTransportConfig.aspect_replication`, `CoreAppNetAspectTestView`, and the test lifecycle entry points did not exist.
2. `ctest --test-dir engine/build --output-on-failure -R '^test_core_app_target_contract$'`
   - **0/1 passed**. The new checks reported `unknown or malformed argument` instead of `network options require --network`, and help did not list `--aspect-replication`.

## GREEN evidence

Final normal-tree command:

```sh
ctest --test-dir engine/build --output-on-failure \
  -R '^(test_core_app_net_transport|test_core_app_target_contract|test_break_replication_session|test_break_online_aspect_session|test_break_online_aspect_session_link|test_break_session|test_break_replication_wire|test_break_replication_fragment)$'
```

Result: **8/8 CTest suites passed**. Direct binaries provided these exact internal counts:

| Suite | Result |
| --- | ---: |
| `test_core_app_net_transport` | 11/11 (4 existing + 7 new) |
| `test_core_app_target_contract` | 1/1 CTest |
| `test_break_replication_session` (bridge) | 19/19 |
| `test_break_online_aspect_session` | 12/12 |
| `test_break_online_aspect_session_link` | 1/1 |
| `test_break_session` | 43/43 |
| `test_break_replication_wire` | 9/9 |
| `test_break_replication_fragment` | 28/28 |

`ctest --test-dir engine/build --output-on-failure -R '^test_core_app_network'`: **11/11 passed**, including offline, loopback, single-session, late-auth, voice, relay, mute, flood, and start-failure coverage. The first baseline attempt at single-session lacked the `trace_convert` and `trace_merge` executables; after building those existing tools it passed, and the final post-change full run passed 11/11.

The default-off unit test confirms no aspect state and no `network_aspect_stats` event. Existing exact `network_stats` assertions and all 11 network regressions pass unchanged.

## Mutation evidence

Each mutation was applied alone, rebuilt, run against `test_core_app_net_transport`, then immediately reverted.

| Mutation | RED result and primary assertion |
| --- | --- |
| No drain in `net_tick` | 10/11 passed; `stats.applied_packets != 1u` at test line 471 |
| Close does not close the aspect session | 10/11 passed; `stats.bridge.connections != 0u` at line 561 |
| Open uses `key + 1` | 7/11 passed; inbound key rejection at line 465, plus expiry/sync/rollback failures |
| Aspect state created while disabled | 10/11 passed; `view.created is true` at line 387 |
| Successful sends not counted | 10/11 passed; `view.sent_fragments != 2u` at line 550 |

After the fifth revert, the restored binary again passed **11/11**, and the final normal focused run passed **8/8 CTest suites**.

## Sanitizer evidence

Both trees were configured with the required Snowflake pin and default Vulkan selection:

```sh
cmake -S engine -B engine/build-asan \
  -DENGINE_BUILD_TESTS=ON -DCORE_APP_ENABLE_NETWORK=ON \
  -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc

cmake -S engine -B engine/build-tsan \
  -DENGINE_BUILD_TESTS=ON -DCORE_APP_ENABLE_NETWORK=ON \
  -DENGINE_USE_TSAN=ON -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
```

- ASan+UBSan with `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1` and `UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1`: **8/8 CTest suites passed**, including transport, target contract, bridge, aspect session, link, session, wire, and fragment tests. No sanitizer or leak report was emitted.
- TSan with `TSAN_OPTIONS=halt_on_error=1`: the clean focused set excluding the full target contract passed **7/7 CTest suites**. Direct TSan checks of `core_app --help` and `core_app --aspect-replication` also passed: help contains the option and standalone use exits 2 with `network options require --network`.
- The full TSan target-contract attempt passed the same seven suites but the contract itself failed in its unrelated default record scenario, for **7/8**. `core_app` exited 66 at `luaD_throw` with `ThreadSanitizer: can't find longjmp buf` and a TSan interceptor CHECK failure. The stack contains the existing Lua actor tick path, not aspect or transport code. The toolchain exposed no longjmp-interception option. This unrelated runtime limitation was not changed under Task 1; the same full contract passes normally and under ASan+UBSan.

## Files changed

- `engine/apps/core_app/main.c`
- `engine/apps/core_app/core_app_net_transport.h`
- `engine/apps/core_app/core_app_net_transport.c`
- `engine/tests/test_core_app_net_transport.c`
- `engine/tests/test_core_app_target_contract.cmake`
- `.superpowers/sdd/2026-11-24-core-app-aspect-replication/task-1-report.md`

`git diff --check` passes. No loopback client files, production threads, or locks were added.

## Review (agent-424) fix

Verdict approve with minor fixes. The repeated-sync assertion read a stale view;
the test now polls the reactor outbound queue after the second sync and requires
BREAK_NET_EVENT_EMPTY, then refreshes the view before asserting sent_fragments=2.
A duplicated second sync would now fail both checks. Transport remains 11/11.
