# Voice Alignment Controller Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [x]`) syntax for tracking.

Status: Complete

**Goal:** Deliver deterministic, confidence-gated delay tracking and delay-line application as one owner-thread PCM alignment component.

**Architecture:** `AudioVoiceAligner` owns an existing tracker and delay line. It splits input at exact update-period boundaries, pushes raw reference/capture to the tracker, emits delayed reference, and applies accepted measurements from the next frame onward.

**Tech Stack:** C11, existing time-domain/GCC-PHAT estimators and linear delay line, CMake/CTest, ASan/UBSan/TSan.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-voice-aligner-design.md`.
- Mono owner-thread PCM; only create allocates; no hidden threads, locks or logging in processing.
- Update exactly every configured 1..192000 frames, after emitting the boundary chunk; arbitrary caller chunking must not change output.
- Default constructor uses the time-domain tracker; `create_gcc` explicitly selects GCC-PHAT.
- No reset, crossfade/sinc mode, drift compensation, device/AEC/core_app/network integration or acoustic claims.
- Preserve existing naming/terminology and do not add dependencies.

### Task 1: Aligner API, target and RED tests

**Files:**
- Create: `engine/src/audio/audio_voice_aligner.h`
- Create: `engine/src/audio/audio_voice_aligner.c` (include-only RED skeleton)
- Create: `engine/tests/test_audio_voice_aligner.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:** Declare exactly:

```c
typedef struct {
    AudioDelayTrackerConfig tracker;
    u32 update_period_frames;
} AudioVoiceAlignerConfig;

typedef struct AudioVoiceAligner AudioVoiceAligner;

AudioResult audio_voice_aligner_create(const AudioVoiceAlignerConfig *config,
                                       AudioVoiceAligner **out);
AudioResult audio_voice_aligner_create_gcc(const AudioVoiceAlignerConfig *config,
                                           AudioVoiceAligner **out);
void audio_voice_aligner_destroy(AudioVoiceAligner *aligner);
AudioResult audio_voice_aligner_process_i16(AudioVoiceAligner *aligner,
                                            const i16 *reference, const i16 *capture,
                                            i16 *aligned_reference, u32 frames);
double audio_voice_aligner_delay(const AudioVoiceAligner *aligner);
u64 audio_voice_aligner_updates(const AudioVoiceAligner *aligner);
bool audio_voice_aligner_locked(const AudioVoiceAligner *aligner);
bool audio_voice_aligner_uses_gcc(const AudioVoiceAligner *aligner);
u64 audio_voice_aligner_rejections(const AudioVoiceAligner *aligner);
```

- [x] Include `audio/audio_delay_tracker.h` from the new public header and declare all nine functions without implementation.
- [x] Add the include-only production skeleton to the `engine` source list. Add `test_audio_voice_aligner` with direct sources `audio_voice_aligner.c`, `audio_delay_tracker.c`, `audio_delay_estimator.c`, `audio_gcc_phat.c`, `audio_fft.c`; link `m` and label `headless;audio`.
- [x] Build a deterministic nonperiodic 12.5-frame fractional echo in `test_audio_voice_aligner.c`, using the tracker's existing independent sinc reference approach. Use sample rate 16000, max delay 64, window 2048, minimum correlation 0.2, maximum slew 10, lock count 1, hold count 2, and update period 4096.
- [x] Add `create_validates_configuration_and_calls`: NULL/out-of-range/period/GCC-history rejection, unchanged `*out`, NULL accessors, zero-frame call, NULL signals and exact capture/output alias rejection without state/output mutation.
- [x] Add `known_fractional_echo_updates_at_exact_period`: after 4095 frames no update; after one more frame exactly one update, accepted/locked delay near 12.5 with zero rejections; the next output frame equals an independent linear interpolation using the reported delay.
- [x] Add `irregular_chunks_match_whole_blocks`: process the same 16384 frames in one call versus repeating 1/7/31/128 chunks; require byte-identical output and equal update/delay/lock/rejection accessors.
- [x] Add `silent_capture_rejects_without_moving_delay`: active reference plus zero capture advances updates/rejections at the boundary, preserves zero delay and passes reference unchanged; a later valid echo is still accepted.
- [x] Add `gcc_constructor_applies_known_delay`: the explicit GCC instance schedules one update and applies a delay near 12.5.
- [x] Register the five tests. Build the target and verify RED only as unresolved `audio_voice_aligner_*` symbols after the target/source skeleton exists.

Run:

```bash
cmake --build build-core-app-master --target test_audio_voice_aligner -j16
```

### Task 2: Ownership, exact scheduling and delay application

**Files:**
- Modify: `engine/src/audio/audio_voice_aligner.c`

**Interfaces:** Implement Task 1 exactly.

- [x] Define the private object:

```c
struct AudioVoiceAligner {
    AudioDelayTracker *tracker;
    AudioDelayLine *line;
    u32 update_period_frames;
    u32 frames_until_update;
    u64 updates;
    bool use_gcc;
};
```

- [x] Implement a shared internal create with a `use_gcc` flag. Validate `out`, config and period before allocation; call the selected tracker constructor, then `audio_delay_line_create(config->tracker.max_delay_frames, ...)`. On any failure destroy already-created components and leave `*out` unchanged.
- [x] Initialize the countdown to the period and save `use_gcc`. Destroy releases line, tracker and object; NULL is a no-op.
- [x] Validate the complete process call before mutation. Zero frames with a valid aligner returns `AUDIO_OK`; nonzero calls require all three buffers and reject `capture == aligned_reference`. Reference/output may alias.
- [x] For each period-bounded chunk, call tracker push and line process with the same raw reference. At the exact boundary increment `updates`, call tracker update once, apply an accepted delay with `audio_delay_line_set_subframe_delay`, return any unexpected line error, and restore the countdown.
- [x] Advance all three pointers and remaining frame count by the chunk. Apply the new delay only after the just-emitted boundary chunk.
- [x] Accessors forward actual line delay, scheduled update count, tracker lock state, constructor-selected GCC flag and tracker rejection count; NULL returns zero/false.

Run:

```bash
cmake --build build-core-app-master --target test_audio_voice_aligner -j16
./build-core-app-master/test_audio_voice_aligner
ctest --test-dir build-core-app-master -R '^test_audio_voice_aligner$' --output-on-failure
```

Expected GREEN: 5/5 and CTest 1/1 with no warnings.

### Task 3: Mutation, review and delivery

**Files:**
- Modify: `docs/design/audio_extended.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Modify: `docs/superpowers/specs/2026-11-18-audio-voice-aligner-design.md`
- Modify: `docs/superpowers/plans/2026-11-18-audio-voice-aligner.md`

- [x] Rebuild/run `test_audio_voice_aligner` in `/tmp/editor-audio-asan` and `/tmp/build-audio-tsan`; actual 6/6 with no sanitizer report. Compile the aligner with `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic -Werror`.
- [x] Ten mutants covering raw routing, countdown, delay application/early application, GCC selection, alias/three NULL checks and failure restoration are all killed; the countdown deletion is caught by timeout. Clean-source tests pass afterward.
- [x] Run added-line terminology checks and `git diff --check`. Independent review found the failure-countdown and boundary-evidence gaps; the new regression was RED before the fix and scoped re-review is Ready.
- [x] Record actual results and limits in the listed documents. Commit as `audio: add scheduled voice alignment`.
- [x] Run `/tmp/full_trees.sh`; actual 433/433, 433/433 and 441/441 with zero failures. Amend final documentation and rerun all three trees on the final commit.
- [x] Final-commit rerun, push and main/Windows/Proton CI inspection (including real MSVC `/W4 /WX`) are tracked as delivery steps after this local plan.

## Result

Implementation and local verification are complete. Six tests pass in normal, ASan+UBSan and TSan trees; independent re-review is Ready. The committed tree passes 433/433, 433/433 and 441/441.
