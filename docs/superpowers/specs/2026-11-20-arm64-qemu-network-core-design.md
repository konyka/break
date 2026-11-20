# Design: core network tests on arm64 with QEMU

## Context and dependency boundary

The arm64 lane currently selects 20 crash/HTTP/update/security tests. The
initial QUIC investigation found that neither the native build tree nor the
arm64 tree registers `test_break_net_quic`: `BREAK_ENABLE_QUIC=OFF`. Enabling it
requires Snowflake plus OpenSSL >= 3.5, while the arm64 multiroot has OpenSSL
3.0.13 and no Snowflake source configured. No existing CI QUIC dependency lane
exists to reuse. This slice does not weaken that gate or claim QUIC coverage.

A bounded, independently useful set of eight network tests needs neither
Snowflake nor QUIC:

| Test | arm64/QEMU result |
|---|---|
| `test_packet` | 20/20 |
| `test_network` | 18/18 |
| `test_break_online_lobby` | 10/10 |
| `test_break_online_nat` | 23/23 |
| `test_break_online_voice` | 16/16 |
| `test_break_voice_mixer` | 11/11 |
| `test_break_replay_window` | 5/5 |
| `test_break_msg_rate` | 4/4 |

All eight are executable-target tests with no nested compiler, host CMake
driver, or shell-launched target tool. The unmodified emulator-configured cross
tree built and passed all eight in 1.68 seconds. No product or test-source
change is required.

Snowflake-backed adapter/session/TLS/replication tests and QUIC C/C++20 tests
remain excluded until their separate dependency project exists.

## Approaches

1. **Add the eight existing targets to the current selection (recommended).**
   This uses the proven emulator and preserves the dependency gate with minimal
   configuration change.
2. Start a Snowflake/OpenSSL>=3.5 cross-build project in the same slice. This
   mixes dependency provisioning with network evidence and has a much larger
   failure surface; it remains a separate design.
3. Leave networking untested until QUIC is available. This discards valid
   coverage that already runs unchanged and is unnecessary.

## CI change

Append these eight targets to the existing 20-target build command:

```text
test_packet test_network test_break_online_lobby test_break_online_nat
test_break_online_voice test_break_voice_mixer
test_break_replay_window test_break_msg_rate
```

Extend the existing CTest regex with the same eight names. The exact current
selection becomes 28 tests: the previous 20 plus these eight. Keep the generic
job/step names, `CMAKE_CROSSCOMPILING_EMULATOR`, environment overrides,
`--verbose`, `--no-tests=error`, 300-second outer timeout, packages, job key,
and object checks unchanged. The measured additional runtime is 1.68 seconds,
so the existing timeout remains appropriate.

No new job, dependency, runner variable, test skip, output filter, retry, or
status mask is introduced. CMake automatically applies QEMU to all eight
executable targets.

## TDD and verification

1. Retain the unmodified cross result as proof that the tests themselves need
   no adaptation: eight tests, all case summaries above, zero failures.
2. Before editing CI, run a YAML + actual native-selection contract requiring
   28 targets, the extended regex, and exactly the previous 20 names plus the
   eight new names. It must fail on the old build command.
3. Apply only the build-command and regex edits; rerun the contract for GREEN.
4. Run the complete native suite: 455 registered tests, zero failures, four
   established platform skips.
5. Run all final CI scripts in a clean Ubuntu container and require 28/28 with
   every previous summary and the eight new summaries. Request read-only review.
6. Push directly to `master` and assert the real remote arm64 job's 28/28 result
   and exact case summaries in its log. Record observed evidence.

## Documentation and limits

Update the build guide, implementation status, runtime network design, and
missing-capabilities inventory. State the eight new case totals and the unified
28-test selection. Explicitly retain the Snowflake/QUIC dependency gate and do
not describe these tests as QUIC, deployed networking, full arm64 CTest, GPU, or
physical-device evidence.
