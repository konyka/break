# World session Task 1 report

Date: 2026-11-24
Branch: `feature/world-session`
Starting HEAD: `fbc010c13a455390a06ef47ff0ab951cf31d7af9`

## Scope delivered

- `BreakReplicationSessionBridgeConfig.message_id` is configurable; zero retains the existing 0x4009 default. Both the send path and message handler use the configured value.
- The default registry adds 0x400A (`BREAK_NET_MESSAGE_ID_WORLD_DELTA`) and 0x400B (`BREAK_NET_MESSAGE_ID_WORLD_CONTROL`), both v1, AUTHENTICATED, IDEMPOTENT, with a 65536-byte payload cap. Registry counts are now 32 with crypto and 31 without crypto.
- `engine/src/ecs/world_session.{h,c}` owns one bridge and one confirmed baseline per connection. The stream epoch is a stable FNV-1a derivation over little-endian protocol version, schema hash, and level generation.
- Network handling only reassembles and queues. `break_world_session_drain` selectively polls one connection, decodes BRWD, checks its confirmed base, rebuilds and target-hash-checks with `break_world_delta_wire_rebuild`, applies through `break_world_delta_apply` staging, and advances the baseline only after success.
- Base, schema, level, target hash, and apply failures preserve the World and baseline and increment both rejected and need-full counters. Malformed BRWD increments rejected only. Close releases the baseline.
- No ACK, recovery control message, publish history, full fallback policy, core_app integration, or cross-connection World sharing was added; those remain outside Task 1.

## TDD RED evidence

Tests and CTest registration were written before production implementation.

1. Registry test, before registry changes:
   - Built and ran `test_break_session`.
   - Result: **42 passed, 1 failed, 43 total**.
   - Expected failure at `test_break_session.c:1043`: `registry->count != 32u` (the old count was 30).
2. Configurable bridge test, before the config field existed:
   - Built `test_break_replication_session`.
   - Expected compile failure at `test_break_replication_session.c:1271`: `BreakReplicationSessionBridgeConfig` has no member `message_id`.
3. New world-session tests, before the module existed:
   - Built `test_world_session`.
   - Expected compile failure at `test_world_session.c:3`: `ecs/world_session.h` not found.

The first implementation then produced 11/11 world-session tests and 43/43 session tests. The custom bridge test initially failed because its pre-existing hand-built fragment deliberately used a non-FNV checksum; the fixture was corrected to use a valid checksum for the new inbound assertion, after which the real configurable-ID path passed 19/19.

## GREEN evidence

Main build tree: `/home/timeshift/opensource/break/.worktrees/world-session/engine/build` (created for this task).

Every explicit configure used:

```sh
-DBREAK_ENABLE_SNOWFLAKE=ON \
-DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
```

The main configure also used `-G Ninja -DENGINE_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug`. The production `break_net` target built successfully, including `src/ecs/world_session.c` without test hooks.

Final direct executable runs:

| Suite | Result |
| --- | --- |
| `test_world_session` | **11/11** |
| `test_break_replication_session` | **19/19** |
| `test_break_online_aspect_session` | **12/12** |
| `test_break_session` | **43/43** |
| `test_break_replication_wire` | **9/9** |
| `test_break_replication_fragment` | **28/28** |
| `test_ecs_replication` | **35/35** |
| `test_world_delta_wire` | **23/23** |
| Total | **180/180** |

Additional CTest verification:

- Focused CTest set, including `test_replication_target_contract`: **9/9 passed**.
- `test_core_app_network` and `test_core_app_network_offline`: **2/2 passed**; neither existing test file was changed.
- The optional live core_app loopback test was not enabled by this configuration.

New CTest registration: `test_world_session`, timeout 30, labels `ecs;replication;session;wire`.

## Mutation evidence

Each mutation was applied alone, rebuilt, run, observed RED, and reverted before the next mutation.

| # | Targeted mutation | RED evidence |
| --- | --- | --- |
| 1 | Zero config ID defaulted to 0x4100 instead of 0x4009 | Bridge **4 passed / 15 failed** |
| 2 | Outbound bridge send hardcoded 0x4009 instead of configured ID | Bridge **18 passed / 1 failed**, custom outbound ID assertion |
| 3 | 0x400A registry phase changed to ANY | Session **42 passed / 1 failed**, AUTHENTICATED assertion |
| 4 | Level generation omitted from stream epoch | World session **10 passed / 1 failed**, independently derived epoch assertion |
| 5 | Successful apply cleared rather than advanced baseline | World session **3 passed / 8 failed** |
| 6 | `break_world_delta_apply` replaced with unconditional success | Cases 2 and 3 failed real World assertions; case 4 exited abnormally when its expected component was absent |
| 7 | Selective completion poll ignored the requested connection | World session **10 passed / 1 failed**, per-connection isolation assertion |
| 8 | Need-full accounting removed | World session **5 passed / 6 failed** |

After all reversions, `test_world_session`, `test_break_replication_session`, and `test_break_session` were rerun through CTest: **3/3 passed**. The final full direct runs above were also green.

## Sanitizer evidence

Independent builds were configured with the same required Snowflake options:

- `engine/build-world-session-asan`: C/C++ flags `-fsanitize=address,undefined -fno-omit-frame-pointer`, corresponding linker flags.
- `engine/build-world-session-tsan`: C/C++ flags `-fsanitize=thread -fno-omit-frame-pointer`, corresponding linker flags.

Both built the new test and all seven related suites. The focused eight-test regex was run in each tree.

ASan+UBSan command environment:

```sh
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1
```

Result: **8/8 CTest tests passed**, including leak detection, with no sanitizer diagnostics.

TSan command environment:

```sh
TSAN_OPTIONS=halt_on_error=1
```

Result: **8/8 CTest tests passed**, with no thread sanitizer diagnostics.

## Changed files

- `.superpowers/sdd/2026-11-24-world-session/task-1-report.md`
- `engine/CMakeLists.txt`
- `engine/src/ecs/world_session.c`
- `engine/src/ecs/world_session.h`
- `engine/src/network/break_net_message_registry.c`
- `engine/src/network/break_net_message_registry.h`
- `engine/src/network/break_replication_session.c`
- `engine/src/network/break_replication_session.h`
- `engine/tests/test_break_replication_session.c`
- `engine/tests/test_break_session.c`
- `engine/tests/test_world_session.c`

Final checks before commit: `git diff --check` passed; the focused source and test files contain no forbidden naming; no build products are included in the change.
