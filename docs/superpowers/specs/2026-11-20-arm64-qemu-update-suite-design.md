# Design: HTTP and online-update tests on arm64 with QEMU

## Context

The arm64 lane already runs seven crash-related CTest tests through
`CMAKE_CROSSCOMPILING_EMULATOR` and explicit nested runners. The HTTP/update
family has seven more tests:

1. `test_break_update` (21 cases);
2. `test_break_update_client` (44 cases);
3. `test_break_http` (72 cases);
4. `test_break_manifest_tool` (host CMake driver);
5. `test_break_update_target_contract` (host CMake driver plus generated link check);
6. `test_break_http_target_contract` (host CMake archive inspection);
7. `test_break_update_e2e` (host CMake driver with four target tools).

An unmodified cross/QEMU diagnostic showed all three executable-target tests
passing: 21/21, 44/44, and 72/72, including the real HTTP loopback suite. Both
archive contracts failed at missing `nm`; the manifest and update-e2e drivers
failed when their host scripts directly executed arm64 tools.

This slice adds the remaining harness plumbing and combines both families into
one 14-test CI selection. No production HTTP/update behavior needs to change.

## Approaches

1. **Reuse the established emulator/tool inputs (recommended).** Forward the
   existing CMake emulator and `CMAKE_NM`, add optional runner prefixes only to
   target-process launches, and use one anchored CTest prefix group.
2. Add another independent CI job for updates. This duplicates dependency
   installation, build artifacts, and emulator configuration without adding a
   new boundary; the current job already has the required sysroot and OpenSSL.
3. Use binfmt or generic host packages. This hides execution and does not solve
   target archive inspection, so it is rejected.

## CMake and contract inputs

Forward `"-DTARGET_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"` to
`test_break_manifest_tool` and `test_break_update_e2e`.

For `test_break_update_target_contract`, add:

```cmake
-DUPDATE_CONTRACT_NM=${CMAKE_NM}
"-DUPDATE_CONTRACT_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Prefix only its generated `archive_link_check` execution. The name avoids the
Windows installer-detection heuristic applied to unmanifested executables whose
names contain `update`; the existing compiler, libcrypto selection, exact export
list, manifest/store/client checks, and return codes remain unchanged.

For `test_break_http_target_contract`, add `-DNM=${CMAKE_NM}`. It executes no
target program. Existing TLS-policy and export assertions remain unchanged.

Native empty runners preserve direct execution; native `CMAKE_NM` selects the
same host tool already used by the contracts.

## Manifest and update-e2e drivers

In `test_break_manifest_tool.cmake`, prefix the `run` helper with
`TARGET_RUNNER`. Every current `run` invocation executes `TOOL` or `VERIFY`;
host `ls`, `sh`, `truncate`, file operations, and symlink checks remain outside
the emulator. Key permissions, canonical manifest bytes, signature rejection,
size bounds, overwrite protection, and symlink assertions do not change.

In `test_break_update_e2e.cmake`:

- prefix the release `run` helper for `TOOL`/`VERIFY`;
- prefix `client` with `${TARGET_RUNNER}`;
- shell-quote each runner element independently in `start_server`, using the
  same POSIX single-quote escaping as the crash e2e driver;
- launch `SERVER` through that prefix without emulating host CMake or shell
  utilities.

The rollout gate, byte-identical install, exact Range/resume counts, tamper and
signature rejection, no-CA refusal, and server cleanup remain intact. The
manifest fixture's explicit `linux-x86-64` platform string is test data for the
format/compatibility rules, not architecture auto-detection, and stays unchanged.

## Unified 14-test CI selection

Add these seven build targets to the existing nine crash targets:

```text
test_break_update test_break_update_client test_break_http
break_manifest_tool break_manifest_verify break_update_server break_update_e2e
```

Keep the crash environment overrides and use:

```sh
timeout 300 ctest --test-dir build-arm64 --verbose --no-tests=error \
  -R '^(test_break_crash|test_break_update|test_break_http|test_break_manifest_tool)'
```

The current exact selection is 14 tests: seven crash tests, four update tests
(including update client/contract/e2e), two HTTP tests, and the manifest tool.
`test_break_update` and `test_break_http` intentionally match their related
suffix-named tests. `--no-tests=error` still rejects an empty selection.

The three new executable targets and existing crash executables use CMake's
emulator. Host-driven scripts receive explicit nested runners and host cross
binutils. Individual test timeouts and the outer 300-second limit remain active;
no retry, filtering, binfmt registration, or masked status is introduced. The
observed 53.62-second emulated HTTP test fits its existing 120-second timeout.

Rename the QEMU step and job display name to mention crash/update coverage;
keep the job key, packages, configure sysroot, OpenGL compile-only path, and
object checks unchanged.

## TDD and verification

1. Preserve the observed RED baseline: 21/21, 44/44, and 72/72 pass; the four
   host-driven tests fail at direct execution or `nm` discovery.
2. Add optional runner/tool plumbing and run the native focused seven-test
   family to prove empty-runner behavior is unchanged.
3. Run the intended seven-test cross family with the existing emulator before
   editing CI. Require all seven to pass and preserve the 21/44/72 summaries,
   manifest success, both contract messages, and `break_update_e2e OK`.
4. Run a YAML + native-selection contract before the workflow edit; require RED
   on the missing seven targets/14-test regex. After the minimal CI edit,
   require GREEN and an exact 14-name selection.
5. Run the complete native suite after integration: 455 registered tests, zero
   failures, four established platform skips.
6. Execute final CI scripts in a clean Ubuntu container, push directly to
   `master`, and require the real remote arm64 job's 14 tests to pass. Assert
   the actual 21/44/72 and existing crash summaries in remote logs.

## Documentation and limits

Update the build guide, implementation status, update transport design, and
missing-capabilities inventory with the unified 14-test coverage. Preserve all
production-service limitations and previous crash evidence.

This remains selected arm64 coverage, not a full CTest run. It provides no GPU
or physical-device evidence and does not add HTTP/2, proxies, certificate
revocation/pinning, production update-service deployment, or new update
features.
