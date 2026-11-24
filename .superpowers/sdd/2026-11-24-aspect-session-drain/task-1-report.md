# Aspect session drain — Task 1 report

## Scope and commit

- Worktree: `/home/timeshift/opensource/break/.worktrees/replication-aspect-drain`
- Branch: `feature/replication-aspect-drain`
- Starting HEAD: `257ee2b8ee38efe3bf1db1ff6e860992aa417d80` (`docs(replication): design aspect session drain`)
- Commit subject: `feat(replication): drain session completions into aspects`
- Final commit SHA: use the post-commit `git rev-parse HEAD` value returned in the task handoff; this report is included in that same commit.
- No push, pull request, merge, production core_app/editor wiring, World delta, recovery, or asset-chain work was performed.

Implemented Task 1 only:

- `break_aspect_connection_open` now rejects fragment data sizes above `BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE` (65496), rather than allowing 65536 bytes that cannot fit BRFG/v1 with its 40-byte header.
- New `BreakAspectSession` owns a `BreakReplicationSessionBridge` and borrows a `BreakAspectStore`. `open` always derives the expected base from `break_aspect_schema_hash(store)`.
- The network handler remains the bridge's queue-only handler. `break_aspect_session_drain` is the only new-module call site of `break_aspect_apply`; it drains in FIFO order, counts applied/rejected/drained packets, continues after rejection, and releases every polled completion.
- Stats include a snapshot of all bridge stats. Tick, close, bridge access, and BRFG/v1 send forwarding are covered. No thread, lock, atomic, or apply-in-handler production path was added.

## Files changed

- `engine/CMakeLists.txt`
- `engine/src/network/break_online_aspect_replication.c`
- `engine/src/network/break_online_aspect_session.h` (new)
- `engine/src/network/break_online_aspect_session.c` (new)
- `engine/tests/test_break_online_aspect_replication.c`
- `engine/tests/test_break_online_aspect_session.c` (new, 11 tests)
- `.superpowers/sdd/2026-11-24-aspect-session-drain/task-1-report.md`

The final diff has no change to `break_replication_session.c`; its temporary handler mutation below was fully reverted.

## Configuration and baseline

All three explicit configures used the required Snowflake pin and `BREAK_ENABLE_SNOWFLAKE=ON`:

```sh
WT=/home/timeshift/opensource/break/.worktrees/replication-aspect-drain
SNOW=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc

cmake -S "$WT/engine" -B "$WT/engine/build-task1" -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_VULKAN=OFF -DMYUI_VULKAN=OFF \
  -DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR="$SNOW"

cmake -S "$WT/engine" -B "$WT/engine/build-asan" -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_VULKAN=OFF -DMYUI_VULKAN=OFF \
  -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR="$SNOW"

cmake -S "$WT/engine" -B "$WT/engine/build-tsan" -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_VULKAN=OFF -DMYUI_VULKAN=OFF -DENGINE_USE_TSAN=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR="$SNOW"
```

Configure verified Snowflake commit `4ab761fc58a9d15970f295e231003c99a7d44df8`. Before changes, the six relevant existing CTests passed 6/6; direct executable totals were 120/120: bridge 19, session 43, wire 9, fragment 28, aspect 12, and aspect replication 9.

## TDD RED evidence

Tests and CTest registration were written before the production cap change or new module.

### 1. Existing send-side behavior RED

```sh
cmake --build "$WT/engine/build-task1" \
  --target test_break_online_aspect_replication -j 4
"$WT/engine/build-task1/test_break_online_aspect_replication"
```

The new first assertion failed because 65536 was still accepted; the other nine existing tests passed:

```text
FAIL: ... break_aspect_connection_open(fixture.replication, 1u, 1024u, 65536u)
      != BREAK_RUNTIME_INVALID
=== Results: 9 passed, 1 failed, 10 total ===
```

The same test also requires 65496 to be accepted and checks connection counts after both calls.

### 2. Missing session API RED

```sh
cmake --build "$WT/engine/build-task1" \
  --target test_break_online_aspect_session -j 4
```

Build failed for the intended missing-API reason:

```text
engine/tests/test_break_online_aspect_session.c:5:10: fatal error:
  network/break_online_aspect_session.h: No such file or directory
compilation terminated.
ninja: build stopped: subcommand failed.
```

Only after both RED results were observed were the header, implementation, and cap change added.

### Test-fixture correction during GREEN

The first implementation run passed 10/11 new tests. The remaining expiry test called `tick(109)` and then expected expiry at 110. Pool evidence showed `tick(109)` ran the five-unit schedule, observed only nine units idle, returned zero, and advanced `last_tick`; the next call at 110 was correctly rate-limited. Changing only the intermediate fixture timestamp to 104 preserved the real expiry assertion at 110 and produced 11/11. No production expiry behavior was changed.

## Final normal GREEN evidence

Final command on the restored sources:

```sh
cmake --build "$WT/engine/build-task1" --target \
  break_net test_break_online_aspect_session test_break_replication_session \
  test_break_session test_break_replication_wire test_break_replication_fragment \
  test_break_online_aspect test_break_online_aspect_replication -j 4

ctest --test-dir "$WT/engine/build-task1" --output-on-failure \
  -R '^(test_break_online_aspect_session|test_break_replication_session|test_break_session|test_break_replication_wire|test_break_replication_fragment|test_break_online_aspect|test_break_online_aspect_replication)$'
```

Result: **7/7 CTests passed, 0 failed**. Direct executable counts on the same final sources:

| Executable | Passed | Failed | Total |
|---|---:|---:|---:|
| `test_break_online_aspect_session` | 11 | 0 | 11 |
| `test_break_replication_session` (bridge) | 19 | 0 | 19 |
| `test_break_session` | 43 | 0 | 43 |
| `test_break_replication_wire` | 9 | 0 | 9 |
| `test_break_replication_fragment` | 28 | 0 | 28 |
| `test_break_online_aspect` | 12 | 0 | 12 |
| `test_break_online_aspect_replication` | 10 | 0 | 10 |
| **Combined** | **132** | **0** | **132** |

The new 11 tests cover creation/null handling, queue-only handler behavior, schema-derived open and valid BRA1 drain, schema-mismatch rejection with unchanged prior state, subsequent valid draining, zero `max_packets`, FIFO and partial drain, per-key close cleanup, key reuse/high-water reset, tick forwarding, send error mapping, and real-reactor 0x4009/v1 output plus overload mapping. The remote handle is pre-adopted because the existing `break_aspect_apply` contract requires it; its replicated active mask/revision/value remain absent or unchanged until drain.

Broader existing online/aspect regression command:

```sh
ctest --test-dir "$WT/engine/build-task1" --output-on-failure -L 'online|aspect'
```

Result: **7/7 CTests passed**, comprising **93/93 direct tests**:

- lobby 10/10
- NAT 23/23
- online voice 16/16
- voice mixer 11/11
- aspect 12/12
- aspect replication 10/10
- new aspect session 11/11

`git diff --check` passed. The production `break_net` static library also rebuilt successfully with C11, `-Wall -Wextra -Werror -pedantic`.

## Targeted mutation evidence

Each mutation was applied alone, rebuilt, and run. It was then reverted and the relevant GREEN result was reproduced before starting the next mutation.

| # | Temporary production mutation | RED evidence | Evidence after revert |
|---:|---|---|---|
| 1 | Applied the completed payload inside the real `break_replication_session_handle_message`, using a temporary session-store global | **7 passed, 4 failed, 11 total**. Pre-drain assertions failed at `break_aspect_active_mask(...) != 0u`; FIFO also observed the later value too early | 11/11 |
| 2 | Changed `rejected_packets++` to `rejected_packets += 0u` | **10 passed, 1 failed, 11 total**: `stats.rejected_packets != 1u` in the schema-mismatch test | 11/11 |
| 3 | Changed open's expected base to `break_aspect_schema_hash(store) + 1` | **2 passed, 9 failed, 11 total**. Valid fragments were rejected by the bridge; valid send also failed | 11/11 |
| 4 | Restored the send-side cap to `BREAK_NET_MAX_PAYLOAD_SIZE` | **9 passed, 1 failed, 10 total**: 65536 was accepted instead of returning `BREAK_RUNTIME_INVALID` | 10/10 |
| 5 | Replaced completion release with a zeroing `memset`, leaking the owned payload | Functional tests reached the end, but `ASAN_OPTIONS=detect_leaks=1` exited nonzero: **216 bytes leaked in 9 allocations**, rooted at completed-packet assembly | ASan+UBSan 11/11, no leak report |

No mutation scaffolding, global store, handler apply, skipped counter, wrong base, old cap, or missing release remains in the final source.

## Focused ASan+UBSan and TSan evidence

Instrumentation was confirmed in the actual new-module compile commands:

```text
ASan+UBSan: -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined
TSan:       -fsanitize=thread -fno-omit-frame-pointer
```

Both matrices built and ran the new test plus all four requested replication/session tests:

```sh
cmake --build "$WT/engine/build-asan" --target \
  test_break_online_aspect_session test_break_replication_session \
  test_break_session test_break_replication_wire test_break_replication_fragment -j 2
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
ctest --test-dir "$WT/engine/build-asan" --output-on-failure \
  -R '^(test_break_online_aspect_session|test_break_replication_session|test_break_session|test_break_replication_wire|test_break_replication_fragment)$'

cmake --build "$WT/engine/build-tsan" --target \
  test_break_online_aspect_session test_break_replication_session \
  test_break_session test_break_replication_wire test_break_replication_fragment -j 2
TSAN_OPTIONS=halt_on_error=1 \
ctest --test-dir "$WT/engine/build-tsan" --output-on-failure \
  -R '^(test_break_online_aspect_session|test_break_replication_session|test_break_session|test_break_replication_wire|test_break_replication_fragment)$'
```

Results:

| Lane | CTests | New session | Bridge | Session | Wire | Fragment | Diagnostics |
|---|---|---:|---:|---:|---:|---:|---|
| ASan+UBSan, leak detection on | **5/5 passed** | 11/11 | 19/19 | 43/43 | 9/9 | 28/28 | None; 110/110 direct tests |
| TSan | **5/5 passed** | 11/11 | 19/19 | 43/43 | 9/9 | 28/28 | None; 110/110 direct tests |

## Remaining Task 2 work

This task deliberately uses direct real bridge-handler/completion-path tests rather than the full authenticated socket-to-aspect loopback. Task 2 still owns that end-to-end socket coverage, temporary 0x4009 registration mutation, full Vulkan/OpenGL validation, production documentation updates, and any later integration. No claim of full graphics-suite or production-wiring verification is made here.
