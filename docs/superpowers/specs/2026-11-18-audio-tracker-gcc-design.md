# GCC Backend for Adaptive Delay Tracker Design

Status: Implemented and locally verified

## Purpose

Allow the existing delay tracker to use GCC-PHAT measurements and normalized confidence without changing default time-domain behavior or the configuration layout.

## Approaches considered

1. **Separate GCC constructor with shared tracker state machine (selected).** `audio_delay_tracker_create_gcc` selects the backend without adding a configuration field that old field-by-field initializers could leave uninitialized.
2. **Add a method field to `AudioDelayTrackerConfig`.** More uniform construction, but changes the public config layout and requires every existing caller to initialize the new field; rejected.
3. **Run both estimators and combine results.** Doubles history/compute cost and introduces voting policy unrelated to the requested backend choice; rejected.

## API

Add:

```c
AudioResult audio_delay_tracker_create_gcc(const AudioDelayTrackerConfig *config,
                                           AudioDelayTracker **out);
```

- `audio_delay_tracker_create` retains its existing time-domain behavior.
- The GCC constructor applies all existing config checks plus the GCC history limit `window_frames + max_delay_frames <= 32768` and FFT allocation rules. `AUDIO_INVALID`/`AUDIO_OVERLOAD` and success-only `*out` writes match the old constructor.
- Existing reset, push, update, delay, correlation, locked and rejection APIs work unchanged for either backend.
- No backend accessor or runtime backend switch is added; lifecycle selection is explicit at create.

## Architecture and data flow

The opaque tracker holds one `AudioDelayEstimator *` or `AudioGccPhat *` plus a backend flag. Only the selected object is allocated and receives pushed samples. Reset resets the selected object and all existing tracking state.

Update performs exactly one measurement:

- Time domain: `audio_delay_estimator_estimate_subframe`.
- GCC: `audio_gcc_phat_estimate_with_confidence`.

Both produce a fractional delay and signed normalized sample correlation. The existing confidence threshold, accepted-run locking, rejection hold/unlock, pushed-time slew limiting, counters and accessors are shared without policy changes. Estimator failure remains a rejected update.

Only create allocates. Owner-thread, mono, explicit caller-driven update cadence and no hidden background thread remain unchanged.

## Tests

Add three tests to the existing five-test suite and link the focused target with `audio_gcc_phat.c` and `audio_fft.c`:

1. GCC constructor NULL/range/history-limit failure atomicity, initial accessors, reset and not-ready rejection.
2. Fractional measurement delay/confidence, accepted-run locking, uncorrelated-input rejection/hold and inverted-signal acceptance.
3. Whole/chunk equivalence, reset/fresh equivalence and locked slew limiting through the GCC backend.

Mutate backend selection, GCC confidence use, reset/push routing and shared slew behavior. Run ASan+UBSan, strict warnings, terminology checks, independent review and three-tree verification before push.

## Limits

This slice adds explicit backend selection only. It does not run both methods together, switch a live tracker, add multichannel processing, automatically schedule updates, close the drift-control loop or provide real acoustic validation.
