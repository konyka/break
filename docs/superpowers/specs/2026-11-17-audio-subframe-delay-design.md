# Subframe Delay Estimation Design

Status: Implemented and validated; remaining limits are listed below

## Purpose

Add fractional-frame delay estimates and delay-line alignment while preserving every existing integer API and output sequence.

## Approaches considered

1. **Parabolic correlation-peak interpolation plus linear delay-line interpolation (selected).** Small, deterministic, uses existing history and needs no new dependency or allocation after creation.
2. **GCC-PHAT with frequency-domain phase.** Better for some noisy conditions, but requires a larger spectral implementation and does not fit this compatibility slice.
3. **Sinc interpolation in the delay line.** Higher fidelity but more taps, state and computational cost; deferred until listening or accuracy evidence requires it.

## Estimator API

```c
bool audio_delay_estimator_estimate_subframe(AudioDelayEstimator *est,
    double *delay_frames, double *correlation);
```

Use the same readiness, silence, history and tie rules as the integer estimate. Find the integer lag with greatest absolute normalized correlation. At 0, maximum lag, a non-concave curve, or a non-finite/nonlocal vertex, return that integer lag. Otherwise, for absolute scores a,b,c at L-1,L,L+1, use offset `0.5*(a-c)/(a-2*b+c)` and require |offset| <= 0.5. Return `L + offset` and the signed score at L. Outputs remain untouched on failure.

The existing integer function shares the same best-lag search and is byte-for-byte behaviorally unchanged.

## Delay-line API

```c
AudioResult audio_delay_line_set_subframe_delay(AudioDelayLine *line, double delay_frames);
double audio_delay_line_subframe_delay(const AudioDelayLine *line);
```

Delay must be finite and in [0,max_delay]. For D=d+f, output `(1-f)*x[n-d] + f*x[n-d-1]`, with silent initial history. Integer delays keep the existing exact reads; input/output may alias and chunking is irrelevant. The old setter selects the same state as the new setter with an integer argument. The old integer accessor returns the integer part; the new accessor returns the full value and 0 for NULL.

## Tests

- Existing eight tests remain unchanged in behavior and continue to pass.
- Sinc-generated fractional echoes at 3.25, 12.5 and 31.75 frames estimate within 0.25 frame. Correlation is checked against `|sinc(distance to the nearest integer)|` with 0.1 tolerance, rather than assuming every fractional delay has a near-unity integer-peak correlation; integer endpoints remain exact.
- Delay-line fractional values, in-place/chunked output, negative/NaN/above-maximum rejection, NULL accessors and exact integer compatibility.
- Show RED on the three new symbols before implementation, then GREEN.
- Mutation, ASan+UBSan, strict warnings, independent review and three-tree verification before push.

## Limits

Parabolic interpolation is an estimate, not sub-sample ground truth under every noise/path condition. Linear delay interpolation attenuates high frequencies. Drift tracking, clock-drift compensation, GCC-PHAT and sinc delay-line modes remain separate work.
