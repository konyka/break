# core_app World replication — Task 2 report

## Scope and baseline

- Worktree: `/home/timeshift/opensource/break/.worktrees/core-app-world`
- Branch: `feature/core-app-world`
- Starting HEAD: `530e3ee3f60842560792fdb6d333603a1ea6b595`
- Task 2 only: real loopback, negative control, regressions, focused sanitizers, full backend verification and documentation. No production transport change is retained, no deferred Minor is included, and no push is performed.
- All reused build trees retain `BREAK_ENABLE_SNOWFLAKE=ON`, `CORE_APP_ENABLE_NETWORK=ON`, and `SNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc` (pin `4ab761fc58a9d15970f295e231003c99a7d44df8`). Automatic regeneration verified that pin again. New full-suite configure commands are recorded with their results below.

## Real loopback

`test_core_app_net_client world` uses the existing TLS/AUTH-v2 client, formal BRFG codec/reassembly and a real receiving `BreakWorldSession`. The CMake driver starts the actual `core_app --world-replication` process.

Server-to-client coverage:

1. Receive the server's full, reverse all fragments and duplicate one before completion; drain and require the rebuilt snapshot id to equal the wire target id.
2. ACK that full. The production `hooks.tick` path then automatically publishes a delta against the acknowledged target; receive it with the same reversed/duplicate method and verify its target id.
3. Before both drains, require the local World snapshot id, confirmed baseline and applied count to remain unchanged and the completion/duplicate counts to advance. This naturally covers automatic tick publication; no extra publishing scope was added.

Client-to-server coverage:

1. Send a full in reverse fragment order with one duplicate and wait for the server's ACK, proving its diagnostic World reached the same target.
2. Change the diagnostic target, send a delta with a corrupted internal base snapshot id, and require NEED_FULL carrying the last-good id/tick.
3. Send a fresh full and require its ACK. Non-network server trace lines must equal a separate offline run.

Passing evidence:

```text
world_receiver attempts=2 full=1 delta=1 target_matches=2 pre_drain=2 duplicates=2 reversed=9
world_sender full=2 delta=1 fragments=36 duplicates=1 need_full=1 recovered=1
client failures=0
event=network_world_stats opened=1 closed=1 applied=2 need_full=1 rejected=1 full_publishes=1 delta_publishes=1 sent_fragments=9 queue_depth=0 dropped=0
```

The contract requires `sent_fragments>=2`; all other World statistics above are exact. Every non-world network mode rejects `event=network_world_stats`.

## RED, GREEN and negative control

The first compile stopped on a discarded `const` qualifier in the new test; this was a test compile error, not behavioral RED and not counted as such.

The first executable run was **0/1**. Every World protocol check passed, but the driver incorrectly required `session_handler_failed=0`. The actual value 2 exactly matched `clock_replies_unmatched=2`, caused by the existing client deliberately sending an invalid and a duplicate clock reply. Removing that invalid assertion (without production changes) produced **1/1** in `task2-world-green-pre-control.log`.

For the required negative control, only the server's 0x400A handler registration was removed, then `core_app` was rebuilt and the same CTest was run:

- Result: **0/1**, failing at `world_server_drained_inbound_full_to_diagnostic_target`.
- Server evidence: `applied=0 need_full=0 rejected=0 full_publishes=1 delta_publishes=1`; unhandled-message accounting increased.
- Restored the registration, rebuilt and reran: **1/1**.
- `git diff --exit-code -- engine/apps/core_app/core_app_net_transport.c` passed after restoration; no residual production diff remains.

Logs are `engine/build/task2-initial-world.log`, `task2-world-green-pre-control.log`, `task2-negative-control-world.log`, and `task2-restored-world-green.log`.

## Normal focused regression

Build command:

```sh
cmake --build engine/build --target \
  test_core_app_net_transport test_core_app_net_client \
  test_world_session test_world_session_loopback test_world_session_recovery \
  test_break_replication_session test_break_online_aspect_session \
  test_break_online_aspect_session_link test_break_session \
  test_break_replication_wire test_break_replication_fragment \
  test_ecs_replication test_world_delta_wire trace_convert trace_merge core_app -j4
```

Results:

- `ctest --test-dir engine/build --output-on-failure -R '^test_core_app_(network|lifecycle)' -j2`: **25/25**, comprising network/offline **13/13** and lifecycle **12/12**.
- Focused CTest selection (`test_core_app_net_transport`, target contract, world session/loopback/recovery, bridge, aspect session/link, Session, wire, fragment, ECS and World delta wire): **13/13**.
- The real world case itself is **1/1** and the default-off loopback/aspect/voice paths emit no World statistics line.

Logs: `engine/build/task2-network-lifecycle-green.log` and `task2-focused-libraries-green.log`.

## ASan + UBSan + LSan

Reused the Task 1 `engine/build-asan` tree with `ENGINE_USE_ASAN=ON`, `ENGINE_USE_UBSAN=ON`, network enabled and the required Snowflake pin. Built the same focused targets and ran:

```sh
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  ctest --test-dir engine/build-asan --output-on-failure -j2 -R \
  '^(test_core_app_network_world|test_core_app_net_transport|test_core_app_target_contract|test_world_session|test_world_session_loopback|test_world_session_recovery|test_break_replication_session|test_break_online_aspect_session|test_break_online_aspect_session_link|test_break_session|test_break_replication_wire|test_break_replication_fragment|test_ecs_replication|test_world_delta_wire)$'
```

Result: **14/14 PASS**, including the real ASan+UBSan server and client world loopback. No ASan, UBSan or leak report was emitted. Log: `engine/build-asan/task2-focused-green.log`.

## TSan and uncovered paths

Reused `engine/build-tsan` with `ENGINE_USE_TSAN=ON` and the required pin.

The 13-suite attempt produced **12 passes and 1 environment failure**. `test_core_app_target_contract` exits 66 in the existing offline record path with `ThreadSanitizer: can't find longjmp buf`, through `luaD_throw`, `break_kernel_lua_actor_tick` and `app_tick_level`. This is not claimed as a pass and no Lua workaround was added. Log: `engine/build-tsan/task2-focused-with-lua-limit.log`.

The other 12 direct transport/library suites were rerun independently: **12/12 PASS** with `TSAN_OPTIONS=halt_on_error=1`. The complete world driver was then run with the normal `engine/build/core_app` server and `engine/build-tsan/test_core_app_net_client`: **1/1 PASS**, with the same target/recovery counts and no TSan diagnostic. Logs: `task2-focused-libraries-green.log` and `task2-world-hybrid-green.log` in that build tree.

The hybrid run does not cover a TSan-instrumented real server socket process or the TSan offline record/target path. Server transport hooks and all library paths above are covered directly under TSan; the full real server/client loopback is covered normally and under ASan+UBSan. No complete sanitizer suite is claimed.

## Documentation

Appended only new 2026-11-24 sections, preserving historical records and the existing World session receipt:

- `docs/design/session_protocol.md`
- `docs/design/runtime_network.md`
- `docs/design/online_session_network.md`
- `docs/design/ecs_snapshot_replication_aoi.md`
- `docs/design/core_app_integration.md`
- `docs/Implementation_Status.md`
- `docs/cross_engine/missing_capabilities.md`

All explicitly retain production level rebaseline, cross-connection shared live World, Runtime Core mapping, authoritative simulation merge, and the complete asset chain as open gaps.

The first naming run was **1/2** because the pre-existing implementation plan literally enumerated prohibited naming examples. `docs/superpowers/plans/2026-11-24-core-app-world-replication.md` now refers to the repository naming contract without repeating those examples; the design meaning is unchanged. `test_core_app_naming_contract` and `test_repo_naming_contract` then passed **2/2** (`engine/build/task2-naming-restored-green.log`).

## Full backend CTest and final HEAD verification

The code, tests, documentation and this report were committed as `13d74092e52b084e8036c9d0324abd99079f584c` before either full archive-based contract ran. OpenGL reused the existing required-pin tree; Vulkan was configured explicitly with:

```sh
cmake -S engine -B engine/build-vulkan -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=vulkan -DBREAK_ENABLE_CRASH=ON \
  -DBREAK_ENABLE_CRYPTO=ON -DCORE_APP_ENABLE_NETWORK=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
```

Both commands then performed a full build followed by an unfiltered CTest run with `-j2`:

```sh
cmake --build engine/build -j2
ctest --test-dir engine/build --output-on-failure -j2
cmake --build engine/build-vulkan -j2
ctest --test-dir engine/build-vulkan --output-on-failure -j2
```

After the interruption, the recovered task records showed both original background commands `completed` with exit code 0; their complete logs were read and neither suite was rerun.

- **OpenGL:** 477 registered, **473 executed passes, 4 conditional skips, 0 failures**, 310.06 s. Log: `engine/build/task2-full-ctest.log`.
- **Vulkan:** 479 registered, **475 executed passes, 4 conditional skips, 0 failures**, 297.11 s. Log: `engine/build-vulkan/task2-full-ctest.log`.
- Both skip sets are exactly `test_d3d12_dependency_gate`, `test_core_app_nm_missing`, `test_core_app_nm_unsupported`, and `test_core_app_nm_symbol_missing_unsupported`; they are not counted as executed passes.
- `test_core_app_network_world`, `test_clean_room_build_contract`, `test_core_app_contract_compat`, and `test_core_app_ctest_config_contract` actually passed in both full runs, including the archive-based contracts against HEAD `13d74092`.

The final documentation-only follow-up HEAD repeats only these recorded results; it does not change the tested source. After the additions, both naming contracts passed **2/2 on each backend**, and `test_core_app_checkout_attributes_dangling` also passed, giving **3/3 on OpenGL and 3/3 on Vulkan**. Logs: `engine/build/task2-final-docs-gates.log` and `engine/build-vulkan/task2-final-docs-gates.log`. No full suite is represented as a sanitizer run, and no remote result is claimed.

## Self-review

- Production transport is unchanged; the retained code changes are test registration, the real client scenario and its CMake contract.
- The test uses actual socket/TLS/AUTH traffic and real World session drain/control behavior, not direct completion injection.
- No new dependency, production naming surface, deferred authoritative partial-update work, or additional replication feature was introduced.
- The new report and all source files were in HEAD `13d74092` before the full archive-based contracts ran. The final full-suite results are recorded in this documentation-only follow-up; no already-green suite was rerun after recovery.
