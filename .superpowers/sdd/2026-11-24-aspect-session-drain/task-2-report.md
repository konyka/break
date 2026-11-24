# Aspect session drain — Task 2 report

## Scope and commit

- Worktree: `/home/timeshift/opensource/break/.worktrees/replication-aspect-drain`
- Branch: `feature/replication-aspect-drain`
- Starting HEAD: `67e7503608f0c6ee77d1f3c35fd02b77edbbc6ac` (`fix(replication): propagate aspect session link dependency`)
- Task 1 implementation/review base: `c513ed0b` plus `67e75036`
- Commit subject: `test(replication): cover aspect session loopback`
- Final commit SHA: use the post-commit `git rev-parse HEAD` value returned in the task handoff; this report is included in that commit.
- No push, production core_app/editor wiring, World delta, reliable recovery, or asset-chain implementation was added.

Task 2 adds one integrated real-socket test, its negative control evidence, six design/status supplements, and the complete normal/sanitizer/RHI validation record. The only production-source edit made during the task was the temporary registry negative control; it was fully reverted. A pre-existing forbidden domain-word literal in the design spec was corrected after the repository naming contract identified it.

## Files changed

- `engine/tests/test_break_online_aspect_session.c`
- `docs/design/session_protocol.md`
- `docs/design/online_session_network.md`
- `docs/design/runtime_network.md`
- `docs/design/ecs_snapshot_replication_aoi.md`
- `docs/Implementation_Status.md`
- `docs/cross_engine/missing_capabilities.md`
- `docs/superpowers/specs/2026-11-24-aspect-session-drain-design.md` (naming-contract line only)
- `.superpowers/sdd/2026-11-24-aspect-session-drain/task-2-report.md`

`break_net_message_registry.c` has no final diff.

## Real socket loopback evidence

New test: `aspect_session_real_socket_send_drain_reject_and_key_reuse`.

The test follows the existing bridge socket pattern rather than invoking the bridge handler directly:

1. Start a real Snowflake acceptor/reactor in step mode and a `BreakSessionManager` using the default registry.
2. Connect a raw TCP client and send AUTH first. The real AUTH handler records one call, and the manager reaches `BREAK_SESSION_AUTHENTICATED` before the aspect session is opened.
3. Register the real 0x4009 bridge handler with `break_aspect_session_bridge(session)`.
4. Use the existing `BreakAspectReplication` AOI enter/stay path and `BreakAspectSendFn` to produce BRA1 fragments. The callback writes actual BRFG/v1 payloads inside 0x4009 envelopes on the raw client socket. `break_net_reactor_step` plus `break_session_manager_poll_adapter` drives the real registry, session dispatch, reassembly, and completion queue.
5. Drain only on the owner thread through `break_aspect_session_drain`.

The remote handle is pre-adopted because the existing `break_aspect_apply` contract requires a live generation. Before the first drain it is only a placeholder: active mask and object revision are zero, and both U32/I32 getters return `BREAK_RUNTIME_FAILED` without changing their output sentinels. Thus no replicated active object state appears before drain.

The integrated assertions cover:

- First baseline delta 40: three pre-drain state checks remain clear; after one drain, U32=42 and I32=-17 with both aspect bits active.
- Second dirty delta 41: the test changes only the BRA1-internal schema hash and recomputes the packet checksum. BRFG/base/reassembly still succeeds, but apply rejects it. U32/I32 remain 42/-17.
- Same authenticated key close/reopen: delta 1 is accepted after prior deltas 40/41, proving a fresh bridge high-water. After the final drain, U32/I32=84/-34.
- Completion release and stats remain balanced: completion count returns to zero and drained equals applied plus rejected.

Non-vacuous instrumentation and protocol counters:

| Observation | Exact result |
|---|---:|
| AUTH handler calls | 1 |
| Existing aspect send callbacks | 3 |
| BRA1 fragments written to the real socket | 3 |
| Completed bridge packets | 3 |
| Shared consumer count before any drain | 0 |
| Shared consumer count after all drains | 3 |
| Applied / rejected / drained | 2 / 1 / 3 |
| Rejected bridge fragments | 0 |
| Session apply successes | 5 (connection open, AUTH, three 0x4009 messages) |
| Session invalid / handler-failed counters | 0 / 0 |
| Final aspect session direct suite | **12 passed, 0 failed, 12 total** |

## 0x4009 registration negative control

With the new test first passing 12/12, the default 0x4009 registry definition was temporarily disabled and the crypto/non-crypto registry counts reduced accordingly. The test was rebuilt and run:

```text
[12] aspect_session_real_socket_send_drain_reject_and_key_reuse ...
  FAIL: test_aspect_socket_start(fixture) is false
=== Results: 11 passed, 1 failed, 12 total ===
```

The failure is intentional and specific: `BreakSessionManager` cannot register a handler for an ID absent from its registry. The other 11 tests still pass. Restoring the definition and original 30/29 counts produced **12/12** again, and `git diff --exit-code -- engine/src/network/break_net_message_registry.c` succeeded.

## Focused normal and sanitizer matrices

The six focused executables are the aspect session, link-only contract, bridge, Session, wire, and fragment tests. Every configure used the required Snowflake options and pin:

```sh
WT=/home/timeshift/opensource/break/.worktrees/replication-aspect-drain
SNOW=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
# Existing build-task1/build-asan/build-tsan trees were reconfigured by CMake
# with BREAK_ENABLE_SNOWFLAKE=ON and SNOWFLAKE_SOURCE_DIR="$SNOW".
```

The sanitizer trees use `ENGINE_USE_ASAN=ON + ENGINE_USE_UBSAN=ON` and `ENGINE_USE_TSAN=ON`, respectively. ASan/LSan runtime options were `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1`; UBSan used `halt_on_error=1:print_stacktrace=1`, and TSan used `halt_on_error=1`.

| Lane | CTest result | Aspect session | Link | Bridge | Session | Wire | Fragment | Combined direct |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| Normal | **6/6 passed** | 12/12 | 1/1 | 19/19 | 43/43 | 9/9 | 28/28 | **112/112** |
| ASan+UBSan, leak detection on | **6/6 passed** | 12/12 | 1/1 | 19/19 | 43/43 | 9/9 | 28/28 | **112/112** |
| TSan | **6/6 passed** | 12/12 | 1/1 | 19/19 | 43/43 | 9/9 | 28/28 | **112/112** |

No ASan, UBSan, leak, or TSan diagnostic was emitted. These are focused sanitizer lanes, not complete sanitizer suites.

## Full Vulkan and OpenGL builds and CTest suites

Final full-tree configurations:

```sh
cmake -S "$WT/engine" -B "$WT/engine/build-task1" -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_RHI_BACKEND=vulkan -DENGINE_VULKAN=ON -DMYUI_VULKAN=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR="$SNOW"

cmake -S "$WT/engine" -B "$WT/engine/build-gl" -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_RHI_BACKEND=opengl -DENGINE_VULKAN=OFF -DMYUI_VULKAN=OFF \
  -DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR="$SNOW"

cmake --build "$WT/engine/build-task1" -j 2
cmake --build "$WT/engine/build-gl" -j 2
ctest --test-dir "$WT/engine/build-task1" --output-on-failure -j 2
ctest --test-dir "$WT/engine/build-gl" --output-on-failure -j 2
```

Both complete builds exited 0. No test labels were excluded from either final CTest run.

### Initial full-run failure and root cause

The first full runs each had one failure, not hidden or excluded:

| Tree | Registered | Executed passes | Conditional skips | Failed |
|---|---:|---:|---:|---:|
| Vulkan, initial | 463 | 458 | 4 | 1 (`test_repo_naming_contract`) |
| OpenGL, initial | 461 | 456 | 4 | 1 (`test_repo_naming_contract`) |

Both failures identified the same pre-existing line in `docs/superpowers/specs/2026-11-24-aspect-session-drain-design.md`, whose naming instruction itself contained a forbidden domain word. The line now refers to the repository naming contract without using that word. Focused `test_repo_naming_contract` then passed 1/1 in each tree, after which the complete suites were rerun.

### Final full-run results

| Tree | Registered | Executed passes | Conditional skips | Failed | Wall time |
|---|---:|---:|---:|---:|---:|
| Vulkan, final | **463** | **459** | **4** | **0** | 181.96 s |
| OpenGL, final | **461** | **457** | **4** | **0** | 171.94 s |
| Combined | **924** | **916** | **8** | **0** | — |

CTest prints `100% tests passed, 0 tests failed`; the table deliberately subtracts the four tests CTest lists under `The following tests did not run` instead of counting them as executed passes. The four conditional skips in each tree are exactly:

- `test_d3d12_dependency_gate`
- `test_core_app_nm_missing`
- `test_core_app_nm_unsupported`
- `test_core_app_nm_symbol_missing_unsupported`

Final logs are `engine/build-task1/ctest-task2-final.log` and `engine/build-gl/ctest-task2-final.log` in the ignored build trees.

## Documentation updates

New dated 2026-11-24 sections were appended to all six requested documents. They record the schema-hash-derived expected base, drain-only apply and release semantics, 65496 fragment cap, PUBLIC `break_online` link dependency and 1/1 link contract, real loopback counters, registry negative control, focused sanitizer counts, and final RHI counts. Each section retains production core_app/editor wiring, World delta, reliable recovery, and the complete asset chain as not done.

`git diff --check` passes. No placeholder validation count remains in the six new sections.

## Remaining boundaries

- The production owner still must wire and call `break_aspect_session_drain`; core_app/editor integration is not implemented.
- This is an aspect BRA1 path, not a World delta protocol.
- Packet retry, connection recovery, persistent high-water recovery, and the complete asset dependency chain remain unimplemented.
- No remote CI, Windows, Proton, deployment, or full sanitizer-suite claim is made.
