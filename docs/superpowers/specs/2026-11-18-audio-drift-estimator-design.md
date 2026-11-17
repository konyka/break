# Clock Drift Estimator Design

Status: Implemented and validated; remaining limits are listed below

## Purpose

Estimate relative clock drift in parts per million from confidence-gated fractional delay measurements. This slice deliberately excludes the resampler; a separate compensation component will consume the estimate.

## Approaches considered

1. **Sliding-window linear regression (selected).** Directly estimates delay change per frame, handles uneven sample times, limits memory and has simple independent references.
2. **Difference between two tracker outputs.** Cheaper but highly sensitive to a single noisy measurement and hard to validate over long intervals.
3. **Frequency-domain clock estimator.** Unnecessary when delay measurements already exist.

## API

`AudioDriftEstimatorConfig` contains window size 2..1024, minimum absolute correlation 0..1 and maximum absolute drift 1..10000 ppm.

The opaque object supports create, destroy, reset, push, estimate and count:

```c
bool audio_drift_estimator_push(AudioDriftEstimator *est, u64 frame_index,
    double delay_frames, double correlation);
bool audio_drift_estimator_estimate(AudioDriftEstimator *est,
    double *drift_ppm, double *mean_correlation);
```

Push requires finite values, |correlation| at least the configured minimum and a strictly increasing frame index. Rejection leaves the window unchanged. Only create allocates; reset forgets all samples.

Estimate requires at least two samples and nonzero time variance. Subtract an accepted frame index before conversion to double, then compute the centered least-squares slope. `drift_ppm = slope * 1e6`; mean correlation is the signed mean of accepted samples. Non-finite results or drift outside the configured limit leave outputs untouched and return false.

## Tests

1. Configuration, NULL, failure atomicity, initial/reset state.
2. +50 ppm uneven-frame sequence gives the known slope and mean correlation.
3. Low confidence, NaN/Inf and non-increasing frames are rejected; too few/duplicate-time data and an over-limit slope fail atomically.
4. A four-entry ring keeps the latest slope and count; reset permits exact reuse.
5. A large u64 base and -40 ppm slope preserve accuracy.

Mutation, ASan+UBSan, strict warnings, independent review and three-tree verification are required before push.

## Limits

No resampling yet, no automatic delay-tracker wiring, no outlier-robust regression, no wall-clock input or real-device validation. The estimate is only as reliable as the supplied correlation measurements.
