# GCC-PHAT Normalized Confidence Design

Status: Implemented and locally verified

## Purpose

Provide a confidence score with the same meaning as `AudioDelayTracker`'s normalized-correlation gate, without changing the existing PHAT raw-peak API or delay selection.

## Approaches considered

1. **Direct normalized cross-correlation at the PHAT-selected integer lag (selected).** Gives a signed score directly comparable with the existing estimator and tracker, using exact i64 sample products and one O(window) pass.
2. **Normalize the PHAT inverse peak by spectral energy.** Retains a PHAT-specific scale but is not equivalent to normalized sample correlation and cannot safely reuse tracker thresholds.
3. **Replace the existing peak output.** Would break callers and still leave the score definition unclear; rejected.

## API

Add:

```c
bool audio_gcc_phat_estimate_with_confidence(AudioGccPhat *phat,
                                             double *delay_frames,
                                             double *confidence);
```

- NULL arguments, incomplete history, silent capture, silent reference history, or a zero-energy reference window at the selected lag return false with both outputs untouched.
- Success returns the same refined delay as `audio_gcc_phat_estimate` and a signed normalized sample-correlation score in [-1,1].
- `audio_gcc_phat_estimate` remains unchanged and continues to return the signed non-normalized PHAT peak.
- Only create allocates. Estimation remains owner-thread-only and may reuse the existing scratch buffers.

## Algorithm

Refactor the existing PHAT calculation into an internal helper that can also return the selected integer lag before parabolic refinement; both public entry points share that helper. The old wrapper returns its raw peak, while the new wrapper uses local delay/peak temporaries and the returned integer lag. Let `c(i)` be the latest `window` capture samples and `r(i)` the reference samples at that integer lag. Compute with i64 accumulators:

`cr = Σc(i)r(i)`, `cc = Σc(i)²`, `rr = Σr(i)²`, then `confidence = cr / sqrt(cc*rr)`.

If `rr` is zero, fail rather than reporting an undefined score. The confidence intentionally describes the integer alignment even when the returned delay has subframe refinement. This mirrors the existing subframe estimator, whose correlation is also the signed score at the integer peak.

## Tests

Add two tests to the existing six-test suite:

1. NULL/readiness/silence failure atomicity for the new outputs, plus deterministic repeated calls and equality of the old/new delay results.
2. Direct signed-score references for clean, noisy, inverted, fractional and maximum-lag inputs; exact sample-domain computation must agree to 1e-12. Include evidence that greater capture noise lowers absolute confidence and that scores remain in [-1,1].

Mutate the numerator, denominator, selected lag and failure write behavior. Run ASan+UBSan, strict warnings, terminology checks, independent review and three-tree verification before push.

## Limits

This slice does not connect GCC-PHAT to the tracker, alter PHAT weighting, add multichannel processing or provide real acoustic validation. Normalized confidence does not make the PHAT peak itself normalized and does not guarantee detection quality for every signal.
