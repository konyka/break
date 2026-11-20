# Design: aspect and fragment replication tests on arm64 with QEMU

## Context

The arm64 lane selects 28 service/security/network tests. Three remaining
network/replication tests require neither Snowflake nor nested host tools:

- `test_break_online_aspect`: 12 cases;
- `test_break_online_aspect_replication`: 9 cases;
- `test_break_replication_fragment`: 12 cases.

The unmodified emulator-configured cross tree built and passed all three with
12/12, 9/9, and 12/12 in 0.26 seconds. They are direct executable-target tests;
there are no nested compiler, shell, or host-CMake launches. No product or test
source change is needed.

Snowflake-backed replication/session tests, core_app network drivers, and QUIC
remain outside this slice. The QUIC Snowflake + OpenSSL>=3.5 dependency gate is
unchanged.

## Approaches

1. **Append the three existing targets to the current lane (recommended).**
   This is minimal and uses the proof already obtained.
2. Mix them into the separate Snowflake/QUIC dependency project. That adds no
   coverage benefit and obscures this independent result.
3. Leave them unrun pending full-suite emulation. That discards valid evidence
   unnecessarily.

## CI change

Append `test_break_online_aspect`,
`test_break_online_aspect_replication`, and `test_break_replication_fragment`
to the build command. Add `test_break_online_aspect` and
`test_break_replication_fragment` to the CTest regex; the aspect prefix selects
both aspect tests, while the fragment alternative selects the third.

The exact current selection becomes 31 tests: previous 28 plus these three.
Keep all names, emulator/environment settings, `--verbose`, `--no-tests=error`,
300-second timeout, packages, job key, and object checks unchanged. No new skip,
dependency, retry, filter, or status mask is introduced.

## TDD and verification

1. Retain the unmodified cross proof (three tests, 12/9/12 totals, 0.26 seconds).
2. Before CI editing, require the three new build targets, extended regex, and
   exact 31-name selection using PyYAML and `ctest -N`; observe RED on the old
   build command.
3. Apply only build/regex changes and rerun the contract for GREEN.
4. Run the native full suite: 455 tests, zero failures, four established
   platform skips.
5. Execute final CI scripts in a clean Ubuntu container and require 31/31 with
   every old/new summary and exactly one existing integrity setup skip.
6. Request read-only review, push directly to `master`, and assert the remote
   arm64 job's 31/31 result and 12/9/12 summaries. Record observed evidence.

## Documentation and limits

Update the build guide, implementation status, runtime network design, and
missing-capabilities inventory with 31-test coverage and the three new totals.
Do not claim Snowflake/QUIC, production replication deployment, full arm64
CTest, GPU, or physical-device evidence.
