# Adaptive Delay Tracker Design

Status: Implemented and validated; remaining limits are listed below

## Purpose

Track fractional playback-to-capture delay across successive estimates, reject low-confidence measurements, limit locked drift rate, and recover from loss of confidence. This is the automatic-tracking layer above `audio_delay_estimator_estimate_subframe`, not clock-drift compensation.

## Approaches considered

1. **Tracker around the existing estimator (selected).** Reuses validated history, correlation and subframe math; exposes an explicit update boundary and needs one internal estimator only.
2. **Add tracking state directly to the estimator.** Fewer wrappers, but would mix signal measurement with tracking policy and make simple one-shot use less clear.
3. **Continuous per-frame correlation tracking.** Unnecessary cost; the existing estimator is intended for periodic estimates.

## API

`AudioDelayTrackerConfig` contains sample rate 8000..192000, estimator maximum/window limits, minimum absolute correlation 0..1, maximum locked slew 0.1..96000 frames/s, lock count 1..1000 and low-confidence hold 0..1000 updates.

The opaque tracker supports create, destroy, reset, `push_i16`, `update`, and accessors for delay, signed correlation, locked state and rejected-update count. `update` returns true only for an accepted high-confidence measurement. NULL accessors return zero/false as appropriate.

## State machine

- Push counts frames since the last update. Update calls the real subframe estimator once; estimator failure or |score| below threshold is rejected.
- Before lock, an accepted measurement sets the delay directly. `lock_count` consecutive accepted measurements are required to lock.
- While locked, elapsed time is pushed_frames/sample_rate and the delay change is clamped to ±max_slew*elapsed. An update with no new frames cannot move the delay.
- A rejected update preserves delay and clears the accepted-run count. While locked, `hold_updates` consecutive rejections preserve the lock; the next rejection unlocks. Zero hold unlocks immediately. Accepted measurements clear the rejection-run count.
- Reset resets both the estimator and every tracking state, including pushed/update counters and rejection count.

Only create allocates. Processing is owner-thread and mono. The caller chooses when to update; no hidden timer or background thread exists.

## Tests

1. Configuration bounds, failure atomicity, NULL and initial accessors.
2. Fractional echo locks after the configured accepted count and reports the measured delay/correlation.
3. Uncorrelated input is rejected, delay is held, rejection count grows, and lock is released only after the configured hold.
4. Locked drift is clamped by pushed time, including no movement at zero elapsed time.
5. Whole/chunked pushes agree, reset matches a fresh tracker, and estimator failures count as rejection.
6. Mutation, ASan+UBSan, strict warnings, independent review and three-tree verification before push.

## Limits

No confidence calibration beyond normalized correlation or real-device validation. The explicit GCC-PHAT backend extension is specified in `docs/superpowers/specs/2026-11-18-audio-tracker-gcc-design.md`; clock-drift estimation/resampling remains in the separate drift modules. The caller must choose an appropriate update cadence; the API does not claim real-time background operation.
