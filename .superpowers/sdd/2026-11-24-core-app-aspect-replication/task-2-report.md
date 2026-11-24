# core_app aspect replication — Task 2 report

## Scope

- Worktree: `/home/timeshift/opensource/break/.worktrees/core-app-aspect`
- Branch: `feature/core-app-aspect`
- Starting HEAD: `952feef855f862b1a0d836d9558ffae558907f70`
- Task 2 only: real loopback, negative control, compatibility/full-suite verification, focused sanitizers, and documentation. No production transport diff remains from the negative control.

## Real loopback implementation

Added `aspect` mode to `test_core_app_net_client` and `test_core_app_network_aspect` through `engine/CMakeLists.txt` and `test_core_app_network.cmake`.

The client uses the formal BRFG wire decoder and reassembly pool, checks the BRFG base and BRA1 schema hash against its local schema, and applies completed packets into a local store with fixed handles `{index=1,generation=1}` and `{index=2,generation=1}`. It checks all six aspects (index, generation, x/y/z, flags) against the corresponding snapshot. It then sends a valid BRA1 baseline in reverse fragment order, resends one identical fragment, and sends a separate packet with a corrupted BRA1 schema hash but the correct BRFG base. A clock reply barriers server-side draining before close.

Passing client evidence:

```text
aspect applied=2 values=1 valid_fragments=3 duplicates=1 mismatch_fragments=3
client trace_lines=1
client failures=0
```

Passing server evidence from the first GREEN run:

```text
event=network_aspect_stats opened=1 closed=1 applied=1 rejected=1 drained=2 sent_fragments=12 queue_depth=0 dropped=0
```

The CTest contract requires applied=1, rejected=1, drained=2, sent_fragments>=2, queue_depth=0, and dropped=0. It also compares all non-network trace lines with an offline run. Every non-aspect network mode explicitly rejects `event=network_aspect_stats`, proving the default-off trace boundary.

## Negative control

Temporarily removed only the server's `0x4009` handler registration, rebuilt `core_app`, and reran the aspect case.

- Result: **0/1 passed** (the new CTest failed as required).
- The client still received/applied both server baselines and completed its outbound sends, but the server reported:

```text
event=network_aspect_stats opened=1 closed=1 applied=0 rejected=0 drained=0 sent_fragments=10 queue_depth=0 dropped=0
```

- CMake stopped at `expected applied=1`. Restored the handler registration, rebuilt, and the case again passed **1/1**. `git diff -- engine/apps/core_app/core_app_net_transport.c` is empty.

## Normal compatibility and focused counts

- `test_core_app_network_aspect`: **1/1**.
- All `test_core_app_network*` offline/loopback cases: **12/12**.
- All `test_core_app_lifecycle*` cases: **12/12**.
- Naming/dangling focused checks after documentation updates: **3/3 on Vulkan** and **3/3 on OpenGL**.
- Direct focused binaries:
  - `test_core_app_net_transport`: **11/11**.
  - `test_break_replication_session` (bridge): **19/19**.
  - `test_break_online_aspect_session`: **12/12**.
  - `test_break_online_aspect_session_link`: **1/1**.
  - `test_break_session`: **43/43**.
  - `test_break_replication_wire`: **9/9**.
  - `test_break_replication_fragment`: **28/28**.

## Sanitizers

All sanitizer configures used the required Snowflake pin `4ab761fc` and network enabled.

### ASan+UBSan

`ENGINE_USE_ASAN=ON`, `ENGINE_USE_UBSAN=ON`, `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1`, and `UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1`.

**9/9 CTest suites passed**: aspect loopback, net transport, target contract, bridge, aspect session, link, Session, wire, and fragment. No sanitizer or leak report was emitted.

### TSan

The nine-suite attempt passed seven and hit the documented pre-existing Lua longjmp-buffer environment failure in both core_app process scenarios:

- `test_core_app_target_contract`: exit 66 at `luaD_throw`, `ThreadSanitizer: can't find longjmp buf`.
- `test_core_app_network_aspect`: server exit 66 from the same existing Lua actor-tick path before the client could connect.

These are recorded as **7/9**, not hidden or converted to passes. The seven transport/library suites were rerun separately and passed **7/7**. To exercise the new client itself under TSan, the complete aspect driver was also run with the normal `engine/build/core_app` server and `engine/build-tsan/test_core_app_net_client`; it passed **1/1** with client failures=0 and server applied/rejected/drained=1/1/2. No TSan diagnostic appeared in that client run.

## Full backend CTest

Registrations are **481 Vulkan** and **472 OpenGL**. The four conditional skips in each suite are kept separate from passes:

- `test_d3d12_dependency_gate`
- `test_core_app_nm_missing`
- `test_core_app_nm_unsupported`
- `test_core_app_nm_symbol_missing_unsupported`

Intermediate verification is retained for transparency:

- First Vulkan run: 476 passed, 4 conditional skips, 1 failed (`test_repo_naming_contract`) because the pre-existing plan literally enumerated the prohibited naming terms. The plan now refers to the repository naming contract without repeating them, and the gate passes independently.
- First OpenGL run and an overlapping Vulkan rerun read seven documents after append calls had accidentally omitted append mode, replacing those documents. This caused four naming/dependent-contract failures. All seven files were restored from the clean HEAD and the sections reapplied with explicit append mode. Diff numstat is additions-only, and both backends pass the three focused naming/dangling checks 3/3. The stale overlapping Vulkan run was cancelled, not counted as a final suite result.

Final runs entirely after the document restoration:

- **Vulkan:** 481 registered; **477 executed passes, 4 conditional skips, 0 failures** (total 582.98 s).
- **OpenGL:** 472 registered; **468 executed passes, 4 conditional skips, 0 failures** (total 547.97 s).

## Documentation

Appended new 2026-11-24 sections covering the default-off flag, fixed handle policy, diagnostic-only inbound store, drain-only apply, trace fields, loopback evidence and exact counts:

- `docs/design/session_protocol.md`
- `docs/design/online_session_network.md`
- `docs/design/runtime_network.md`
- `docs/design/ecs_snapshot_replication_aoi.md`
- `docs/design/core_app_integration.md`
- `docs/Implementation_Status.md`
- `docs/cross_engine/missing_capabilities.md`

World delta, inbound-to-simulation, level rebaseline, and reliable recovery remain explicitly not done. No remote or other-platform result is claimed.

## Files changed

- `engine/CMakeLists.txt`
- `engine/tests/test_core_app_net_client.c`
- `engine/tests/test_core_app_network.cmake`
- `docs/superpowers/plans/2026-11-24-core-app-aspect-replication.md`
- The seven documentation files listed above
- `.superpowers/sdd/2026-11-24-core-app-aspect-replication/task-2-report.md`

`git diff --check` passes. No push is performed.

## Final review (agent-425) strengthening

Verdict approve with minor fixes: the duplicate used to be sent after the packet
completed, which starts a new partial stream instead of hitting duplicate
suppression. The client now repeats fragment 1 before fragment 0, and the aspect
trace adds duplicates and pending_bytes. Final aspect loopback: 1/1 with
network_aspect_stats opened=1 closed=1 applied=1 rejected=1 drained=2
sent_fragments=10 queue_depth=0 dropped=0 duplicates=1 pending_bytes=0.
Trace-field documentation updated to match.
