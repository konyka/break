# Core App Voice PCM Pump Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [x]`) syntax for tracking.

Status: Complete

**Goal:** Deliver a reusable 48 kHz mono capture→alignment→voice-processing pump with deterministic manual driving, an optional owner thread and a bounded PCM-frame handoff queue.

**Architecture:** `CoreAppVoice` owns capture, aligner and processor objects and borrows the playback system's reference API. The same 480-frame pump runs manually or on a worker; immutable `BreakVoiceFrame` values cross a 16-entry SPSC queue.

**Tech Stack:** C11 atomics, existing audio capture/reference/alignment/processor modules, `PlatformThread`, runtime error types, CMake/CTest and sanitizers.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-core-app-voice-pump-design.md`.
- Fixed 48000 Hz mono, 480 frames per packet, 4096-frame capture ring and 16-packet queue; one producer and one consumer.
- No allocation, lock, logging or file/network I/O in pump/pop; only create/thread-start allocate.
- Stop joins the worker before stopping capture/reference; queued packets remain readable. No tail flush or automatic lost-device recovery.
- No CLI, network-hook, encoding/send, drift-compensation or production-deployment claims.
- Preserve repository naming/terminology and existing backends/dependencies.

### Task 1: Public contract, production target and RED

**Files:**
- Create: `engine/apps/core_app/core_app_voice.h`
- Create: `engine/apps/core_app/core_app_voice.c` (include-only RED skeleton)
- Create: `engine/tests/test_core_app_voice.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:** Use the exact public types and signatures from the spec:

```c
#define CORE_APP_VOICE_FRAME_FRAMES 480u
#define CORE_APP_VOICE_QUEUE_CAPACITY 16u

typedef struct {
    AudioSystem *playback;
    AudioBackend capture_backend;
    AudioVoiceAlignerConfig aligner;
    AudioVoiceProcessorConfig processor;
    bool use_gcc;
} CoreAppVoiceConfig;

typedef struct {
    u64 produced, dropped, capture_overruns, reference_overruns;
} CoreAppVoiceStats;
```

  Declare `core_app_voice_{create,start,start_threaded,inject,pump,pop,stats,stop,destroy}` with the spec's exact argument and return types. Include `audio_voice_aligner.h`, `audio_voice_processor.h`, `network/break_online_voice.h`, and `runtime/runtime_types.h`; the voice header has no codec link dependency.

- [x] Add the source skeleton to `core_app_runtime`. Add `test_core_app_voice`, linking the formal `core_app_runtime`, `m` and `Threads::Threads`; label `headless;core_app;audio`.
- [x] Create a valid test config with FAKE capture, borrowed FAKE playback, 48 kHz tracker/processor modules, tracker max delay 64/window 256/update period 480, and the voice-processor test values converted to 48000 Hz. Use noise frame size 64, echo taps 64, mono gate/AGC.
- [x] Add `create_validates_config_and_lifecycle`: NULL/out-of-range/nested rejection, unchanged output pointer, empty pop, pump-before-start rejection, idempotent start/stop, insufficient-half-packet gating, zero stats and NULL destroy.
- [x] Add `manual_packet_matches_independent_pipeline`: inject/render exactly 480 frames, then derive expected capture conversion, final-stereo reference downmix, alignment and voice processing with separate objects. Require exact PCM, sequence 0, 48000 Hz/mono/480 samples and one produced packet.
- [x] Add `queue_is_bounded_and_drains_after_stop`: produce 17 packets without popping; require 16 ordered sequence values, one drop, then empty after stop. Produce once more and require sequence 17, proving dropped sequence 16 is not reused.
- [x] Add `pump_waits_for_each_input`: capture-only and reference-only phases each remain empty until both have 480 frames, including after restart.
- [x] Add `threaded_voice_produces_and_stops`: start the real worker, reject external pump, drive bounded FAKE injection/render and pop waits, receive one packet, stop/join, and require no worker error or capture/reference overrun.
- [x] Register five tests. Reconfigure the build tree before expecting the new target; verify RED as unresolved `core_app_voice_*` symbols after a valid target exists.

Run:

```bash
cmake .  # from build-core-app-master
cmake --build . --target test_core_app_voice -j16
```

### Task 2: Owned components, packet pump and worker lifecycle

**Files:**
- Modify: `engine/apps/core_app/core_app_voice.c`

**Interfaces:** Implement Task 1 without changing existing audio modules.

- [x] Define private state for playback/capture/aligner/processor, queue storage, free-running atomic head/tail, atomic produced/dropped, next sequence, worker/thread IDs, stop flag, latched worker error and lifecycle booleans.
- [x] Validate config/out before allocation. Create capture with `{capture_backend, 48000, 1, 4096}`, then selected aligner and processor; unwind in reverse on failure. Use a single mapping from `AudioResult` to runtime errors, with allocation `AUDIO_OVERLOAD` mapped to `BREAK_RUNTIME_OOM`.
- [x] Implement start/reference→capture ordering, rollback and idempotence. `start_threaded` requires a stopped, non-worker object and rolls back if thread creation fails.
- [x] Implement pump gating on capture loss and both inputs having 480 frames; read exact counts, run aligner then processor, fill sequence/rate/channel/sample count, and publish into the ring. Full queues drop the newest frame while sequence still advances. Zero max_packets is a no-op.
- [x] Implement pop with acquire head/release tail and empty `out_ready=false`; implement stats from atomic produced/dropped and the two device counters. Invalid calls write neither frame nor ready/stat outputs.
- [x] Implement worker loop with at most four packets per iteration and a 1 ms sleep when idle; latch the first pump error. Stop requests/joins the worker before stopping capture/reference, preserves queued packets and returns the first worker/device error. Destroy stops then unwinds all owned objects.
- [x] Add a compile-time power-of-two assertion for the queue capacity. Do not add test hooks to production hot paths.

Run:

```bash
cmake --build build-core-app-master --target test_core_app_voice -j16
./build-core-app-master/test_core_app_voice
ctest --test-dir build-core-app-master -R '^test_core_app_voice$' --output-on-failure
```

Expected GREEN: 5/5 and CTest 1/1 without warnings or hangs.

### Task 3: Mutation, review and delivery

**Files:**
- Modify: `docs/design/audio_extended.md`
- Modify: `docs/design/core_app_integration.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Modify: `docs/superpowers/specs/2026-11-18-core-app-voice-pump-design.md`
- Modify: `docs/superpowers/plans/2026-11-18-core-app-voice-pump.md`

- [x] Rebuild/run the final test in `/tmp/editor-audio-asan` and `/tmp/build-audio-tsan`; require 5/5 with no report. Run strict C11 warnings and repeated threaded tests to check for flaky shutdown.
- [x] Mutate input gating, raw reference/capture routing, aligner→processor order, sequence advancement, drop accounting, queue head publication and worker stop/join. Require focused failure or timeout; restore and rerun clean source after every mutation.
- [x] Run added-line terminology checks and `git diff --check`. Obtain independent read-only review; fix Critical/Important through failing tests and scoped re-review.
- [x] Maintain the listed documents without deleting old limitations. Commit as `core_app: add voice PCM pump`.
- [x] Run `/tmp/full_trees.sh`; expected 434/434, 434/434 and 442/442. Amend final documentation if needed and rerun the final commit's three trees.
- [x] Fetch `origin/master`, handle divergence without force-push, push `master`, and inspect main, Windows D3D12 and Proton CI including real MSVC `/W4 /WX`.

## Result

Implementation and local verification are complete. Five tests pass in normal, ASan+UBSan and TSan trees; worker startup has an explicit ready handshake, and independent re-review is Ready. The first three-tree run exposed the core_app naming contract's fixed seven-source list; after updating it to eight sources, the trees pass 434/434, 434/434 and 442/442.
