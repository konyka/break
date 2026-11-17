# Robust Clock-Drift Estimation Design

Status: Implemented and locally verified

## Purpose

Add an outlier-resistant drift estimate for delay measurements while preserving the existing least-squares API and its exact outputs.

## Approaches considered

1. **Siegel repeated-median slope with fixed scratch (selected).** Robust to isolated measurement outliers, needs only O(window) scratch and does not depend on a contaminated initial fit.
2. **Least-squares fit followed by residual trimming.** Simpler, but a sufficiently biased initial slope can reject the wrong samples; rejected.
3. **Theil–Sen with every pairwise slope stored.** Simpler global median, but the maximum 1024-sample window would require over 500,000 doubles; rejected.

## API

Add:

```c
bool audio_drift_estimator_estimate_robust(AudioDriftEstimator *est,
                                           double *drift_ppm,
                                           double *mean_correlation);
```

- NULL, fewer than two samples, non-finite intermediate values, degenerate/non-finite results, or drift beyond `max_abs_drift_ppm` return false with both outputs untouched.
- Success returns drift in ppm and the same arithmetic mean of all accepted signed correlations as the existing estimator.
- `audio_drift_estimator_estimate`, push validation, ring behavior and reset are unchanged.
- Only create allocates. Two additional `double[window_size]` scratch arrays are owned by the object and reused by robust estimation.

## Algorithm

For every sample `i`, compute slopes to every other sample `j`:

`(delay[j]-delay[i]) / signed_frame_delta(frame[j],frame[i])`.

`signed_frame_delta(a,b)` returns `a>=b ? a-b : -(b-a)` without unsigned underflow or loss of a large common frame-number base. Any non-finite slope fails the estimate.

For each `i`, sort its `count-1` slopes in place and take the median; even counts use `0.5*lower + 0.5*upper` to avoid overflow. Collect these per-sample medians, sort them in place, and take their median as the final delay-per-frame slope. Multiply by 1e6 to obtain ppm.

Sorting uses an internal allocation-free heap sort, including two-point windows and exact ties. Scratch mutation does not change the stored samples, so repeated calls and calls to the legacy estimator are deterministic. Mean correlation uses the original samples without outlier removal.

The worst-case work is O(window² log window), with O(window) scratch; the intended bounded update cadence remains caller-controlled.

## Tests

Add three tests to the existing five-test suite:

1. Clean uneven-frame positive drift matches 50 ppm; isolated large positive/negative outliers disrupt the legacy fit but leave the robust result within 1e-6 ppm of 50. Mean signed correlation is unchanged.
2. NULL/insufficient/limit/non-finite-intermediate failures leave outputs untouched; two samples and reset/reuse work.
3. Wrapped windows and a near-UINT64_MAX frame base preserve negative drift and reject isolated outliers.

Mutate signed frame delta, median selection, heap ordering, output guards and the legacy slope. Run ASan+UBSan, strict warnings, terminology checks, independent review and three-tree verification before push.

## Limits

This is repeated-median slope estimation, not a complete robust delay tracker or automatic control loop. It does not remove samples from the window, change confidence admission, add multichannel support or provide real-device validation.
