# arm64 QEMU platform input/window slice (219 → 225)

**Goal:** run six pure-CPU platform tests in `lane-cross-aarch64-linux`: `test_platform_screen_simulated` (3 cases, fake QNX Screen SDK), `test_platform_window_mode` (14, header-only borderless state machine), `test_pad_linux_feedback` (3, evdev rumble with injected I/O), `test_pad_win_feedback_portable` (4, XInput feedback over `tests/fake_windows`), `test_win32_touch` (4, Win32 touch over `tests/fake_windows`) and `test_wayland_touch` (4, Wayland touch dispatch; needs `wayland-client` for arm64, already installed by the lane).

**Excluded and why:** `test_input_extended_single_cpu` (CPU-affinity variant, `RUN_SERIAL`, meaningless under qemu-user); `test_platform_wsi_lifecycle`, `test_platform_wsi_compile_matrix`, `test_platform_vk_surface_abi` (host CMake/compile matrices); Vulkan device probes and `test_rhi_native`.

**Constraint:** the complete `-R` expression already holds 31 capture groups; append flat exact alternatives `|name$` only.

## Task 1: selection contract
- [x] **Step 1:** Contract requires the build suffix `test_fork_deadline` + six targets, the six alternatives last, at most 31 groups, no `Too many parentheses`, exact native sets 219/225 with a six-element difference, guide/workflow byte equality and a 225 intro count. Negative probes cover every excluded name and prefix extensions.
- [x] **Step 2:** Run on the current workflow; require RED at `missing platform input build targets`.
- [x] **Step 3:** Append targets and alternatives in workflow and guide; update the 1.5 title, intro and current-count paragraph to 225, keeping 219 as history.
- [x] **Step 4:** Selection and lane-budget contracts GREEN, valid YAML, clean `git diff --check`.

## Task 2: verification
- [x] **Step 1:** Native focused 6/6 with 3/14/3/4/4/4 cases.
- [x] **Step 2:** Clean Ubuntu 24.04 container: build and run the six arm64 targets under QEMU; require 6/6 with identical counts.
- [x] **Step 3:** Native full suite; require 456 tests, zero failures, four established platform skips.
- [x] **Step 4:** Clean non-root container running the exact workflow steps; require 225/225, all counted per-test numbers, all contracts/e2e, one ptrace setup skip, no root-permission skip, and `assert_timeout_markers.py` OK.

## Task 3: review, push, receipts
- [x] **Step 1:** Read-only independent review; reproduce and fix every Critical/Important finding.
- [x] **Step 2:** Commit `ci: run arm64 platform input tests`, push, monitor the full CI and Windows D3D12 workflows.
- [x] **Step 3:** Download the raw arm64 log and assert 225 with all counted per-test numbers.
- [x] **Step 4:** Append local/remote receipts and remaining gaps to `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; check off completed steps.

## Task 4: fix found during verification (test_voice_playback SEGFAULT under QEMU)
- [x] **Step 1:** Reproduce: 20/400 SEGFAULT under qemu-aarch64, 0/300 native; store-buffering litmus shows qemu-user reorders `stlr`→`ldar` (45322/200000) and a seq_cst fence removes it (0).
- [x] **Step 2:** RED: `test_audio_realtime_contract` requires a seq_cst fence between each handshake store and its first atomic load in `audio_extended.c`; fails on the old source.
- [x] **Step 3:** GREEN: fences in `pcm_stream_read`, `audio_pcm_stream_close` and `audio_pcm_stream_set_hrtf`; contract passes, QEMU loop 0/400, native audio/voice tests pass.
