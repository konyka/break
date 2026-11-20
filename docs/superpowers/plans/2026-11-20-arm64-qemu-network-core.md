# arm64 QEMU Core Network Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add eight dependency-free network tests to the arm64 lane, producing an exact 28-test selection without weakening the Snowflake/QUIC gate.

**Architecture:** Reuse the existing executable-target emulator; no nested runners or product/test changes are needed. Extend only the build targets, CTest regex, and evidence documentation.

**Tech Stack:** CMake/CTest, C11 networking, QEMU user emulation, GitHub Actions YAML, Python 3 + PyYAML, Podman Ubuntu 24.04.

## Global Constraints

- Add packet, network, online lobby/NAT/voice, voice mixer, replay window, and message rate: eight tests with totals 20/18/10/23/16/11/5/4.
- Preserve all previous 20 tests and the explicit integrity setup skip.
- Do not claim Snowflake adapter/session/TLS or QUIC coverage; OpenSSL>=3.5 + Snowflake remains a separate dependency project.
- No new dependencies, skips, retries, filtering, status masking, or full-suite/physical-device claims.

---

### Task 1: CI selection and evidence

**Files:**
- Modify: `.github/workflows/ci.yml:208-230`
- Modify: `docs/Build_Guide.md`, `docs/Implementation_Status.md`
- Modify: `docs/design/runtime_network.md`, `docs/cross_engine/missing_capabilities.md`
- Test: inline YAML + actual native CTest selection; real cross tests already passed unchanged

**Interfaces:**
- Consumes: eight existing executable targets and the current emulator configuration.
- Produces: 28 build targets and exactly 28 selected tests.

- [ ] **Step 1: Preserve cross proof and run failing CI contract**

Retain the unmodified cross result: eight tests passed in 1.68 seconds with totals 20/18/10/23/16/11/5/4. Then assert with PyYAML that the build command ends with the eight targets in the design order and the run regex adds those names to the existing eight alternatives. Use `ctest -N` with the new regex on `build-core-app-net` and assert selection equals the previous 20 names plus `test_packet`, `test_network`, `test_break_online_lobby`, `test_break_online_nat`, `test_break_online_voice`, `test_break_voice_mixer`, `test_break_replay_window`, `test_break_msg_rate`; size 28. Expected: RED on the old build command before editing.

- [ ] **Step 2: Apply minimal workflow edits**

Append to the build command:

```text
test_packet test_network test_break_online_lobby test_break_online_nat test_break_online_voice test_break_voice_mixer test_break_replay_window test_break_msg_rate
```

Use this exact regex:

```yaml
            -R '^(test_break_crash|test_break_update|test_break_http|test_break_manifest_tool|test_break_crypto|test_break_keygen|test_break_integrity|test_break_authority|test_packet|test_network|test_break_online_lobby|test_break_online_nat|test_break_online_voice|test_break_voice_mixer|test_break_replay_window|test_break_msg_rate)'
```

Keep names, emulator, environment, timeout, packages, job key, and object checks unchanged.

- [ ] **Step 3: Verify contract GREEN and full native regression**

Rerun Step 1's contract; expected 28 names and PASS. From `build-core-app-net` run:

```bash
cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure
```

Expected 455 tests, zero failures, four established platform skips. Run `git diff --check`.

- [ ] **Step 4: Update documentation**

Document the unified 28-name selection, eight new totals and 1.68-second focused runtime. Explain that all eight are direct executable-target QEMU tests without nested tools. Record the QUIC investigation accurately: current arm64 OpenSSL 3.0.13 and absent Snowflake cannot satisfy QUIC's OpenSSL>=3.5 + Snowflake gate; no version downgrade or fake pass occurred. Update implementation status and missing capabilities with selected coverage only.

- [ ] **Step 5: Commit**

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md docs/Implementation_Status.md \
  docs/design/runtime_network.md docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-network-core.md
git commit -m "ci: run arm64 core network tests"
```

### Task 2: Final verification and remote proof

**Files:** verify all changes; modify implementation status only with observed remote evidence.

- [ ] **Step 1: Run final clean container and integrate remote**

Fetch/rebase if needed without discarding independent changes. Execute every arm64 workflow run block in a fresh Ubuntu container with runner CMake provisioning. Require 28 targets, object checks, 28 tests, all old/new summaries, exactly one existing integrity setup skip, and no new skip. Preserve complete logs.

- [ ] **Step 2: Independent review**

Review exact 28-name coverage, unchanged dependency gates, target-only emulation, timeout, and documentation. Fix Critical/Important findings test-first and verify adopted minor fixes.

- [ ] **Step 3: Push and assert remote evidence**

Push normally and wait for exact HEAD's arm64 job. Assert `0 tests failed out of 28`, all old summaries and new 20/18/10/23/16/11/5/4, all contracts/e2e, and exactly one existing integrity skip. Record run/job URLs and commit.

- [ ] **Step 4: Record and audit**

Commit observed evidence as `docs: record arm64 network CI results` and push normally. Finish clean with `HEAD == origin/master`; keep the broader goal open, including the separate QUIC dependency project.
