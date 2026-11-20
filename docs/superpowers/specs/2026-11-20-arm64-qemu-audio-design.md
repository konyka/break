# arm64 QEMU Audio Tests Design

## Context

The arm64 lane selects exactly 108 tests. Twenty-three audio tests remain
outside it: `test_voice_playback`, `test_audio`, twenty `test_audio_*` DSP and
pipeline executables, and the host-side `test_audio_realtime_contract`. This
slice adds exactly those twenty-three for a 131-test selection.

## Approaches

1. Extend the lane by name with the twenty-two executables and the host
   contract. Recommended: reuses the generated commands.
2. Select by the `audio` label. Rejected: the label also covers
   `test_core_app_voice`, `test_core_app_voice_lane`, and
   `test_editor_audio_sink`, which need core_app or editor runners.
3. Add a separate lane. Rejected: duplicates the multiarch setup.

## Existing Behavior and Baseline

Twenty-two direct executable registrations (`engine/CMakeLists.txt:6666` and
`7247-7403`) link audio sources with `m`, `Threads::Threads`, `dl`, or
`break_online` (`test_voice_playback`). They use no audio device: capture and
playback run against in-process sinks. `test_audio_realtime_contract`
(`engine/CMakeLists.txt:7407`) runs a host `cmake -P` script over the audio
sources.

Case counts (native and unmodified cross agree):

| Test | Cases | Test | Cases |
|---|---|---|---|
| `test_voice_playback` | 4 | `test_audio_noise_suppressor` | 8 |
| `test_audio` | 47 | `test_audio_residual_echo_suppressor` | 8 |
| `test_audio_extended` | 129 | `test_audio_delay_tracker` | 8 |
| `test_audio_dsp` | 10 | `test_audio_gcc_phat` | 8 |
| `test_audio_hrtf` | 9 | `test_audio_drift_estimator` | 8 |
| `test_audio_capture` | 13 | `test_audio_drift_resampler` | 12 |
| `test_audio_agc` | 8 | `test_audio_drift_compensator` | 8 |
| `test_audio_noise_gate` | 8 | `test_audio_edit` | 6 |
| `test_audio_echo_canceller` | 9 | `test_audio_voice_processor` | 3 |
| `test_audio_delay_estimator` | 21 | `test_audio_voice_aligner` | 6 |
| `test_audio_fft` | 8 | `test_audio_wav` | 7 |

That is 356 cases. Unmodified cross focused execution in a clean Ubuntu 24.04
container passes 23/23 in 16.57 seconds; the slowest test is
`test_audio_delay_tracker` at 3.66 seconds, well inside the existing 20/30-second
per-test timeouts and the lane's 300-second limit. No product or test-source
change is needed.

## CI Change

Append the twenty-two executable targets after `test_break_ai_smart_object` and
add:

```text
test_audio(_(extended|dsp|hrtf|capture|agc|noise_gate|echo_canceller|delay_estimator|fft|noise_suppressor|residual_echo_suppressor|delay_tracker|gcc_phat|drift_estimator|drift_resampler|drift_compensator|edit|voice_processor|voice_aligner|wav|realtime_contract))?$|test_voice_playback$
```

The `$` binds the whole optional suffix group, so derived names are rejected.

## TDD and Verification

1. Contract against the old workflow: twenty-two build targets, the exact
   alternatives, rejection of derived names and of `test_core_app_voice`,
   `test_core_app_voice_lane`, `test_editor_audio`, `test_editor_audio_sink`;
   previous 108 plus these twenty-three = 131. Observe RED.
2. Apply the edits; require GREEN on the explicit 131-name set.
3. Focused native with the new `-R`: 23/23.
4. Native full: 455, zero failures, four established skips.
5. Clean-container workflow: 131/131, exactly one ptrace setup skip.
6. Independent review, push, and assert the exact-HEAD remote log with all
   twenty-two per-test counts.

## Boundaries

A selected 131-test suite, not full arm64 CTest. Real audio devices (PipeWire,
ALSA, WASAPI, CoreAudio), core_app voice lanes, editor audio, and
cross-architecture bit-exact DSP output remain outside it. Passing under QEMU
shows the DSP pipeline is self-consistent within one arm64 build; QEMU timing
is not representative of real-time deadlines on arm64 hardware.
