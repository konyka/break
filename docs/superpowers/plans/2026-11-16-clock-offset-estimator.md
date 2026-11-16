# Clock offset between network peers

Status: Done

## Context

`core_app --trace-timestamps` stamps trace lines with the local monotonic
clock, and `trace_merge --offset-us N` can shift one input. Two machines
have unrelated monotonic origins, so nothing computes N.
`docs/cross_engine/missing_capabilities.md` lists clock alignment between
network peers as missing.

This slice adds the estimator as a pure module. Carrying the probe over the
core_app session protocol is a later slice.

## Design (`engine/src/core/clock_offset.{h,c}`)

- A sample is the four NTP timestamps in microseconds: `t0` A sends, `t1`
  B receives, `t2` B replies, `t3` A receives (t0/t3 on A's clock, t1/t2 on
  B's). Each must be at most 2^61 so the sums cannot overflow i64.
- `offset = floor(((t1 - t0) + (t2 - t3)) / 2)` is B's clock minus A's;
  `delay = (t3 - t0) - (t2 - t1)` is the round trip without B's hold time.
- A sample is rejected (`CLOCK_OFFSET_INVALID`, counted) when `t2 < t1`,
  B's hold exceeds the round trip (this covers `t3 < t0`) or a value
  exceeds 2^61.
- `ClockOffsetEstimator` keeps the last `CLOCK_OFFSET_WINDOW` (8) accepted
  samples. The estimate is the offset of the sample with the smallest
  delay (ties: the newest), with error bound `delay / 2` rounded up; an
  empty window is `CLOCK_OFFSET_EMPTY`.
- `clock_offset_merge_shifts(offset, &a_shift, &b_shift)`: non-negative
  shifts that put A's and B's timestamps on one timeline for
  `trace_merge` (the earlier origin gets the shift).

## Tests (`engine/tests/test_clock_offset.c`, written first)

1. Symmetric path: offset and delay exact; B behind A gives a negative
   offset; odd sums floor toward negative infinity.
2. Invalid samples are rejected and counted and do not change the estimate.
3. The minimum-delay sample wins; ties go to the newest; a window of 8
   evicts the oldest (a low-delay sample ages out).
4. Asymmetric delay: the true offset lies within the reported error bound.
5. Merge shifts for positive, negative and zero offsets, and the
   most-negative representable offset.

## Verification

test_clock_offset, mutation run, ASan/TSan, three full build trees,
banned-word check, commit and push.

## Result

test_clock_offset 5/5 (RED: the source did not exist). Mutation: 17
mutants; the separate `t3 < t0` check survived because the hold check
already rejects it, so it was removed and the rejection is documented.
All others killed. ASan and TSan clean on three runs.
