# arm64 QEMU Rule Engine Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the twenty-one rule-engine tests to the arm64 lane for an exact 152-test selection.

**Architecture:** Reuse twenty-one generated direct QEMU commands. Append twenty-one build targets after `test_audio_wav` and add one new locally anchored alternative.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Previous 131 + 21 = 152. Do not select `test_rule_engine_executor_stress` or `rule_engine_fuzz_smoke`.
- Alternative: `test_rule_engine(_(transactions|tms|grl_semantics|ir|forall_limits|rete_incremental|agenda|backward|backward_ext|grl_surface|plugin_parity|example_coverage|query_blocks|stream_ext|stream_grl|stream_eval|backward_deep_chain|backward_bindings))?$|test_backward_machine_(structure|context)$`.
- No product/test-source edits, dependency, skip, retry, mask, or assertion relaxation.

---

### Task 1: CI selection and documentation

- [x] **Step 1:** Run `build-core-app-net/rule_engine_selection_contract.py` on the old workflow; expected FAIL at `missing rule engine build targets`.
- [x] **Step 2:** Append the twenty-one targets and the alternative in `.github/workflows/ci.yml` and `docs/Build_Guide.md`.
- [x] **Step 3:** Re-run the contract; expected `exact 152-test rule engine selection and anchor contract passed`; confirm byte-identical regex.
- [x] **Step 4:** Focused native with the new `-R` (21/21) and unmodified cross baseline (21/21, 643 cases).
- [x] **Step 5:** Append status, design, and missing-capability evidence. Commit as `ci: run arm64 rule engine tests`.

### Task 2: Final verification and remote proof

- [ ] **Step 1:** Native full regression; require 455, zero failures, four established skips.
- [ ] **Step 2:** Clean-container workflow; require 152/152, all twenty-one counts, and exactly one ptrace setup skip.
- [ ] **Step 3:** Read-only review; fix adopted findings. Fetch/rebase if needed and push.
- [ ] **Step 4:** `build-core-app-net/assert_arm64_log.py <log> 152` with all twenty-one `NAME=COUNT` pairs from the spec table. Record URLs, commit `docs: record arm64 rule engine CI results`, push.
