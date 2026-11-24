# World delta wire codec — Task 1 report

## Scope and implementation

Base: `88a4dd5b8034599cfc8c89bf7cd82e9e074d51d1` on `feature/world-delta-wire`.
`origin/master` advanced to `d69e78c471f51a3b5aa7fb9ef4febf8541412244` during the task; no rebase was performed.

Added:

- `engine/src/ecs/world_delta_wire.h`: BRWD/v1 public types, limits, codec, cleanup, and rebuild API.
- `engine/src/ecs/world_delta_wire.c`: explicit little-endian encoding/decoding, borrowed payload decode, strict envelope/record/termination validation, and staging-only target reconstruction with snapshot-ID verification.
- `engine/tests/test_world_delta_wire.c`: 14 tests covering golden bytes, unaligned input, full/delta round trips, every record kind, malformed/truncated/oversized input, tampering, mismatch handling, and failure-atomic outputs.
- `engine/CMakeLists.txt`: production/test library sources and `test_world_delta_wire` with labels `ecs;replication;wire`.
- This report.

The wire header is 60 bytes and each record header is 17 bytes. Limits are 1,048,576 records and 67,108,864 bytes per message. Decoded record arrays are owned by the decoded message; component payload bytes remain borrowed from the input. Full messages require zero base ID/tick; delta messages require a nonzero base ID and a matching caller-provided base snapshot/world. Rebuilds mutate only a private staging world, recompute the target with `break_world_snapshot_build`, and compare `break_world_snapshot_id` with the wire target ID.

No session, bridge, core_app, ACK/retry, or thread implementation was changed.

## RED evidence

The test and CTest target were added before the public header or implementation. Command:

```sh
cmake --build build-world-delta-wire --target test_world_delta_wire -j2
```

Result: expected build failure, exit 2:

```text
engine/tests/test_world_delta_wire.c:3:10: fatal error:
ecs/world_delta_wire.h: No such file or directory
```

Two implementation-cycle corrections followed actual test evidence: an always-false allocation check was removed for the 64-bit target, and a payload equal to the whole-message byte limit was correctly reclassified as over-limit once record headers were included. The recycled-entity fixture was corrected from generation 2 to generation 3 after inspecting ECS destroy/reuse semantics.

## GREEN evidence

All configures used:

```sh
-DBREAK_ENABLE_SNOWFLAKE=ON
-DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
```

The Snowflake adapter verified commit `4ab761fc58a9d15970f295e231003c99a7d44df8` in every build tree.

Normal build: `build-world-delta-wire`.

| Suite | Result |
| --- | ---: |
| `test_world_delta_wire` | 14/14 |
| `test_ecs_replication` | 35/35 |
| `test_break_replication_session` (bridge) | 19/19 |
| `test_break_online_aspect_session` | 12/12 |
| `test_break_session` | 43/43 |
| `test_break_replication_wire` | 9/9 |
| `test_break_replication_fragment` | 28/28 |
| `test_core_app_network` | 25/25 |
| `test_core_app_network_offline` | 1/1 CTest |

Focused CTest invocations passed 4/4 entries (`test_world_delta_wire`, ECS replication, BRFG wire, fragmentation) and 5/5 entries (bridge, aspect session, session, core-app network unit, core-app network offline). Direct executable runs produced the exact inner counts above. `git diff --check` passed.

## Targeted mutation evidence

Each mutation was built and run against `test_world_delta_wire`, observed red, and immediately reverted. The restored implementation then passed 14/14.

| Mutation | Observed failure evidence |
| --- | --- |
| Big-endian `put16` | 11 passed / 3 failed; golden bytes and both round trips failed |
| Accept trailing bytes (`offset > size`) | 11 passed / 5 failed assertion count; trailing, count, and record-shape rejection failed |
| Ignore decoder maximum-record-count result | 13 passed / 1 failed; count-limit case returned INVALID instead of OVER_LIMIT |
| Skip comparison with recomputed target snapshot ID | 12 passed / 3 failed; target-ID, payload, and target-tick tampering were accepted |
| Do not zero decode output on entry/failure | 9 passed / 130 failed assertion count; malformed-output zeroing checks failed |
| Allow full messages with nonzero base ID/tick | 12 passed / 4 failed assertion count; decode and encode validation failed |

The framework increments its failure counter per failed helper assertion, so some mutation summaries have more failures than the 14 named tests. An additional redundancy probe removed only the early count-versus-truncation precheck; it remained 14/14 because later exact parsing rejects those inputs. That probe was also restored. The required maximum-count mutation above independently proved the observable count-limit behavior.

## Sanitizer evidence

### ASan + UBSan + leak detection

Build tree: `build-world-delta-wire-asan`.

Flags:

```sh
CMAKE_C_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
CMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
CMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined"
CMAKE_SHARED_LINKER_FLAGS="-fsanitize=address,undefined"
ASAN_OPTIONS=detect_leaks=1
UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1
```

Result: 4/4 CTest entries passed, covering 86 inner tests (14 new + 35 ECS replication + 9 BRFG wire + 28 fragmentation), with no sanitizer or leak report.

### TSan

Build tree: `build-world-delta-wire-tsan`.

Flags:

```sh
CMAKE_C_FLAGS="-fsanitize=thread -fno-omit-frame-pointer"
CMAKE_CXX_FLAGS="-fsanitize=thread -fno-omit-frame-pointer"
CMAKE_EXE_LINKER_FLAGS="-fsanitize=thread"
CMAKE_SHARED_LINKER_FLAGS="-fsanitize=thread"
TSAN_OPTIONS=halt_on_error=1
```

Result: the same 4/4 CTest entries and 86 inner tests passed with no TSan report.
