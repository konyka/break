# World session Task 2 report

Date: 2026-11-24
Branch: `feature/world-session`
Starting HEAD: `5dd953d6d9208832c7bdb5d8c597b1e00c0c862a`
Origin note: `origin/master` was `fc26e099286975f1fc986ad9b6b0468863319df8`; no rebase was performed.

## Scope delivered

- 0x400A carries BRWD fragments and 0x400B carries a fixed 32-byte BRWC/v1 control payload. NEED_FULL contains the receiver's last-good target id/tick; ACK contains `(delta_id, target_snapshot_id, target_tick)`.
- Receiver ACKs coalesce to the latest applied target. NEED_FULL is limited to one event per connection per configured N target ticks; suppressed requests are counted separately without changing the rejection count.
- Sender history is per connection and bounded by entry count, BRWD bytes, and packet bytes. Exact ACKs trim through the matching entry and establish the confirmed sender baseline. Unknown baselines, NEED_FULL, and budget pressure produce full attempts with fresh delta IDs.
- Full attempts clear obsolete history and the old confirmed baseline only after every fragment is queued successfully. OVERLOAD preserves the original snapshot, encoded BRWD bytes, delta ID, and next-fragment cursor; later calls do not read or regenerate the supplied World.
- Close/reopen releases receiver baselines, sender confirmed/history state, pending attempts and controls, rate-limit epochs, and resets the next delta ID to 1.
- Real raw TCP/AUTH loopback covers reordered and duplicate 0x400A fragments, drain-only World application, target snapshot IDs, base mismatch to NEED_FULL, a following full recovery, and a real registry-removal failure followed by restored success.
- Semantics are at-least-once/final-consistency, not exactly-once. core_app enablement, production level rebaseline policy, cross-connection shared World, Runtime Core mapping, and authoritative simulation merge remain undone.

## TDD RED evidence

Two new CTest suites and their tests were written before production recovery APIs:

- `test_world_session_recovery`: six tests for rate/wire control, ACK trimming/full fallback, history count/bytes, packet cap, immutable OVERLOAD retry, and reconnect reset.
- `test_world_session_loopback`: two tests for real socket recovery and registry negative control.

Initial builds were RED for the intended missing features:

- `BreakWorldSessionConfig` had no `history_entry_limit`, `history_byte_limit`, `packet_byte_limit`, or `need_full_tick_interval`.
- `BreakWorldSessionControl` and `BreakWorldSessionSenderState` did not exist.
- `break_world_session_publish`, `_poll_control`, `_send_control`, `_handle_control`, and `_sender_state` were undeclared.
- New stats fields were absent. Both new targets failed compilation under the repository's `-Werror` settings.

After the first implementation, loopback was immediately **2/2**. Recovery initially reported **2 passed, 5 failed, 6 total**. Diagnostics showed publish returned OK but fragment reassembly failed checksum validation; the OVERLOAD case's first fragment returned checksum mismatch (result 5).

Root cause investigation traced this to `break_replication_fragment_payload`: it allocates only descriptors and borrows the source BRWD buffer. `world_session_build_attempt` freed that buffer immediately after creating descriptors. The fix retains the immutable buffer in the attempt until the last fragment is sent. This is also required for byte-identical OVERLOAD retries. After the fix and removal of diagnostics, recovery was **6/6** and loopback remained **2/2**.

## GREEN evidence

All explicit configure commands used:

```sh
-DBREAK_ENABLE_SNOWFLAKE=ON \
-DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
```

Main tree: `/home/timeshift/opensource/break/.worktrees/world-session/engine/build`
Main backend configure: `-DENGINE_RHI_BACKEND=vulkan`
OpenGL tree: `/home/timeshift/opensource/break/.worktrees/world-session/engine/build-gl`
OpenGL backend configure: `-DENGINE_RHI_BACKEND=opengl`

Final direct normal runs:

| Suite | Result |
| --- | --- |
| `test_world_session_recovery` | **6/6** |
| `test_world_session_loopback` | **2/2** |
| `test_world_session` | **11/11** |
| `test_break_replication_session` | **20/20** |
| `test_break_online_aspect_session` | **12/12** |
| `test_break_session` | **43/43** |
| `test_break_replication_wire` | **9/9** |
| `test_break_replication_fragment` | **28/28** |
| `test_ecs_replication` | **35/35** |
| `test_world_delta_wire` | **23/23** |
| Total | **189/189** |

The focused normal CTest run, including `test_replication_target_contract`, was **11/11**. The production `break_net` target also built successfully.

Real loopback assertions include AUTH=1, at least one duplicate fragment, zero World entities before drain, exact ACK delta/target/tick, last-good NEED_FULL target/tick, two successful applies plus one rejection, and exact recovered snapshot ID. In the negative control the custom manager registry omits only 0x400A: the real Session reports `invalid=1`, bridge completion=0, and the World remains empty. Restoring the definition in a fresh real socket case completes and applies the full target.

## Mutation evidence

Each mutation was built and run independently, observed RED, then reverted before the next one.

| # | Mutation | RED evidence |
| --- | --- | --- |
| 1 | NEED_FULL interval effectively reduced to one tick | Recovery **5 passed / 1 failed**, second request was not suppressed |
| 2 | ACK trimming stopped subtracting released history bytes | Recovery **4 passed / 2 failed**, ACK bytes and later byte-budget behavior |
| 3 | NEED_FULL no longer forced full | Recovery **5 passed / 1 failed**, fresh full assertion |
| 4 | History byte-budget check removed | Recovery **5 passed / 1 failed**, byte-limited full fallback |
| 5 | BRWD payload freed immediately after fragment planning | Recovery **2 passed / 5 failed**, checksum failures reproduced |
| 6 | Pending OVERLOAD attempt restarted at fragment zero | Recovery **5 passed / 1 failed**, retry did not complete the expected original packet |
| 7 | Open no longer reset next delta ID | Recovery output **1 passed / 6 failed / 6 total**, initial and reopened publish failures |
| 8 | Successful full retained the old confirmed baseline | Recovery **5 passed / 1 failed**, confirmed baseline was not zero |

After all reversions, both new CTest targets were rerun: **2/2 passed**. Final direct normal and sanitizer runs were also green.

## Sanitizer evidence

Sanitizer trees:

- `/home/timeshift/opensource/break/.worktrees/world-session/engine/build-world-session-asan`
- `/home/timeshift/opensource/break/.worktrees/world-session/engine/build-world-session-tsan`

ASan+UBSan flags: `-fsanitize=address,undefined -fno-omit-frame-pointer` for C/C++ and corresponding linker flags.
TSan flags: `-fsanitize=thread -fno-omit-frame-pointer` for C/C++ and corresponding linker flags.

The exact nine-target focused selection was recovery, loopback, world session, replication session, Session, replication wire, replication fragment, ECS replication, and world delta wire.

ASan+UBSan environment:

```sh
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1
```

Result: **9/9 CTest passed**, no sanitizer or leak diagnostics. Direct cases represented by this selection: **177/177**.

TSan environment:

```sh
TSAN_OPTIONS=halt_on_error=1
```

Result: **9/9 CTest passed**, no race diagnostics. These are focused suites, not complete sanitizer suites.

## Full Vulkan and OpenGL evidence

Both complete build trees were built before running unfiltered `ctest --output-on-failure`. The first Vulkan run had 462 executed passes, 4 skips, and 1 failure; OpenGL had 460 executed passes, 4 skips, and 1 failure. The only failure in each was `test_repo_naming_contract`: the existing plan's prohibition line itself contained prohibited names. The line now refers to the project naming policy without repeating those names; no source or test name changed. The gate then passed independently in both trees and both complete suites were rerun, with final results below.

- Vulkan registered **467**: **463 executed/passed, 4 conditional skips, 0 failed** (352.03 s).
- OpenGL registered **465**: **461 executed/passed, 4 conditional skips, 0 failed** (342.21 s).

The four conditional skips are kept separate from executed passes:

- `test_d3d12_dependency_gate`
- `test_core_app_nm_missing`
- `test_core_app_nm_unsupported`
- `test_core_app_nm_symbol_missing_unsupported`

## Documentation

New 2026-11-24 sections were appended to:

- `docs/design/session_protocol.md`
- `docs/design/runtime_network.md`
- `docs/design/online_session_network.md`
- `docs/design/ecs_snapshot_replication_aoi.md`
- `docs/Implementation_Status.md`
- `docs/cross_engine/missing_capabilities.md`

Each records 0x400A/0x400B, baseline/ACK semantics, full fallback, rate limiting, loopback evidence, exact counts, and the remaining core_app/level/shared-World boundaries.

## Changed files

- `.superpowers/sdd/2026-11-24-world-session/task-2-report.md`
- `docs/Implementation_Status.md`
- `docs/cross_engine/missing_capabilities.md`
- `docs/design/ecs_snapshot_replication_aoi.md`
- `docs/design/online_session_network.md`
- `docs/design/runtime_network.md`
- `docs/design/session_protocol.md`
- `docs/superpowers/plans/2026-11-24-world-session.md`
- `engine/CMakeLists.txt`
- `engine/src/ecs/world_session.c`
- `engine/src/ecs/world_session.h`
- `engine/tests/test_world_session_loopback.c`
- `engine/tests/test_world_session_recovery.c`

Final checks before commit: `git diff --check`, direct 189/189, focused normal 11/11, focused sanitizer 9/9 in each lane, forbidden-name scan, and the complete backend summaries above.


## Review fix: full replacement, control ordering, and terminal attempts

Review base: `1059c951e71a916febe98a8f030cc34970108f75`.

### RED evidence before fixes

- `world_session_sparse_full_replaces_diverged_world` was changed from expecting the old allocator-history rejection to requiring a legal sparse full replacement. Together with the new stale-nonempty reconnect case, `test_world_session` was **10 passed / 2 failed / 12 total**: both left the stale entity in place.
- `world_session_ack_after_need_full_does_not_reuse_unconfirmed_baseline` built sender history A,B and receiver last-good A, rejected B, then delivered NEED_FULL followed by ACK A. The next attempt was expected to be fresh-id full; it was a B-based delta. `world_session_fragment_count_invalid_releases_attempt` required two fragments with a configured count cap of one and found `attempt_pending=true`. `test_world_session_recovery` was **6 passed / 2 failed / 8 total**.
- `world_session_full_fault_rolls_back_world_and_baseline` initially failed compilation because `break_world_delta_wire_test_fail_after_mutation` did not exist. This supplied the explicit fault-injection RED for full-apply rollback.
- The first full-specific replacement implementation also exposed an integration failure: a directly created staging World has null query match pointers, which `world_replace_contents` rejects. The fix uses a deep clone of the validated empty-built staging World, whose query pointers satisfy the existing atomic-replacement invariant. Temporary diagnostics were removed before the green runs.

### Fixes after RED

- Added `break_world_delta_wire_apply_full`: BRWD_FULL is applied into an empty staging World, the target snapshot is rebuilt and hash-checked, and only then is the destination atomically replaced. `world_session` no longer converts full targets into deltas against the old World. Fault injection after staging mutation confirms that destination and confirmed baseline remain unchanged on failure.
- ACK processing no longer clears `force_full`. Only successful completion of a full publish attempt clears it, so NEED_FULL followed by ACK A cannot produce a B-based delta while B is unconfirmed.
- Publish now checks the generated fragment count against the bridge limit before advancing `next_delta_id`. `world_session_resume_attempt` retains attempts only for OVERLOAD and releases them for INVALID/CLOSED terminal results.
- The reconnect test now establishes receiver and confirmed sender baselines, queues ACK and NEED_FULL, advances the NEED_FULL tick epoch, and retains an OVERLOAD attempt before close. Reopen verifies all state and queued controls are cleared.
- Both loopback fixtures are initialized before use and have a single cleanup exit covering snapshots, wire buffers, sockets, partial `socket_start` failures, and every assertion path.
- Packet-cap documentation now states that full is attempted under pressure, but an over-cap full is rejected without consuming history or a delta ID. The full-apply documentation was updated to describe empty-staging replacement rather than old-World delta application.

### After-fix verification

- `test_world_session`: **13/13** (sparse full success, explicit full-fault rollback, stale reconnect recovery).
- `test_world_session_recovery`: **8/8** (ACK-after-NEED_FULL ordering and small fragment-count INVALID cleanup included).
- `test_world_session_loopback`: **2/2** with unconditional cleanup.
- Direct total across the original ten suites: **193/193**, up from 189. Sanitizer-selected direct cases: **181/181**, up from 177.
- Focused normal CTest including replication target and naming contracts: **12/12**.
- Focused ASan+UBSan (`detect_leaks=1`) and TSan: **9/9 each**, no diagnostics.
- Full Vulkan: **467 registered, 463 executed/passed, 4 conditional skips, 0 failed**.
- Full OpenGL: **465 registered, 461 executed/passed, 4 conditional skips, 0 failed**.
- The conditional skips remain `test_d3d12_dependency_gate`, `test_core_app_nm_missing`, `test_core_app_nm_unsupported`, and `test_core_app_nm_symbol_missing_unsupported`.

Review-fix files: `engine/src/ecs/world_delta_wire.{h,c}`, `engine/src/ecs/world_session.c`, `engine/tests/test_world_session.c`, `engine/tests/test_world_session_recovery.c`, `engine/tests/test_world_session_loopback.c`, `engine/CMakeLists.txt`, the three protocol/design documents above, and this report.
