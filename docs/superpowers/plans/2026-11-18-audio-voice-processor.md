# Audio Voice Processor Pipeline Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Complete

**Goal:** Compose AEC, residual suppression, spectral noise reduction, gate and AGC into one verified mono pipeline.

**Architecture:** An opaque owner-thread object stores the nested configuration, selected heap-backed modules and caller-owned states. Create validates and constructs every stage; processing delegates in the fixed documented order.

**Tech Stack:** C11, existing audio modules, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-voice-processor-design.md`.
- All nested sample rates match; gate/AGC are mono; every nested range remains enforced.
- Only create allocates; reset restores all stages without changing configuration.
- No device, network, tracker, editor or platform integration in this slice.

### Task 1: Files, target and RED

**Files:** create `engine/src/audio/audio_voice_processor.{h,c}` and `engine/tests/test_audio_voice_processor.c`; modify `engine/CMakeLists.txt`.

- [x] Declare the exact config/API from the spec, add the implementation file to the engine and register one `test_audio_voice_processor` with `headless;audio` labels.
- [x] Link the test with `audio_voice_processor.c`, residual/AEC, spectral suppressor/FFT, gate and AGC sources.
- [x] Add three tests: validation/no-op/latency, manual-chain and arbitrary-chunk byte equality, and reset/fresh plus independently referenced zero-padding drain.
- [x] Build/run the new target; after explicit reconfigure, observed RED on `audio_voice_processor_*` references.

### Task 2: Composition and GREEN

**Files:** modify `engine/src/audio/audio_voice_processor.c` and, if required by its contracts, the header.

- [x] Store the config and all stages; validate matching rates/mono before construction and clean up partial creation without writing `*out`.
- [x] Process through residual+AEC, spectral suppression, gate and AGC in that exact order; invalid calls do nothing and latency returns the spectral frame size.
- [x] Reset AEC/residual/spectral states and reinitialize gate/AGC from the stored config, with no allocation.
- [x] Build/run `test_audio_voice_processor`; observed 3/3. Formal engine target also builds.

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/design/core_app_integration.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, and this slice's spec/plan.

- [x] Mutate stage ordering, gate/AGC reset, NULL-object guard, latency forwarding and spectral reset; all six fail focused tests.
- [x] Run ASan+UBSan for the full new pipeline and strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` checks for all changed sources.
- [x] Run added-line terminology checks and independent read-only review; the drain finding was fixed and re-review is Ready.
- [x] Incrementally update documents, explicitly retaining the separate core_app device/network boundary, and commit as `audio: add integrated voice processing pipeline`.
- [x] Run `/tmp/full_trees.sh`; observed 430/430, 430/430 and 438/438 because one CTest target is added. Verify actual counts, push `master` after green and inspect both new CI runs.

## Result

Implementation, review and verification are complete. Normal and ASan+UBSan tests pass 3/3, strict warnings and terminology checks are clean, all six mutants are killed, and the formal engine builds. Review found an invalid drain fixture; the full tail now matches an independent manual chain, and scoped re-review is Ready. The three full trees pass 430/430, 430/430 and 438/438. Remote CI inspection follows the push.
