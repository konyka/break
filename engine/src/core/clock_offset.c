#include <core/clock_offset.h>

#include <string.h>

/* floor(value / 2) without relying on the sign behavior of >> */
static i64 floor_half(i64 value)
{
    return value >= 0 ? value / 2 : -((-value + 1) / 2);
}

ClockOffsetStatus clock_offset_measure(const ClockOffsetSample *sample, ClockOffsetMeasure *out)
{
    if (!sample || !out) return CLOCK_OFFSET_INVALID;
    if (sample->t0 > CLOCK_OFFSET_MAX_US || sample->t1 > CLOCK_OFFSET_MAX_US ||
        sample->t2 > CLOCK_OFFSET_MAX_US || sample->t3 > CLOCK_OFFSET_MAX_US) {
        return CLOCK_OFFSET_INVALID;
    }
    if (sample->t2 < sample->t1) return CLOCK_OFFSET_INVALID;
    /* every timestamp is at most 2^61, so each difference fits in i64; a
     * t3 < t0 makes round_trip negative and fails the hold check */
    i64 round_trip = (i64)sample->t3 - (i64)sample->t0;
    i64 hold = (i64)sample->t2 - (i64)sample->t1;
    if (hold > round_trip) return CLOCK_OFFSET_INVALID;
    i64 forward = (i64)sample->t1 - (i64)sample->t0;
    i64 backward = (i64)sample->t2 - (i64)sample->t3;
    out->offset_us = floor_half(forward + backward);
    out->delay_us = round_trip - hold;
    return CLOCK_OFFSET_OK;
}

void clock_offset_init(ClockOffsetEstimator *estimator)
{
    if (estimator) memset(estimator, 0, sizeof(*estimator));
}

ClockOffsetStatus clock_offset_add(ClockOffsetEstimator *estimator, const ClockOffsetSample *sample)
{
    if (!estimator || !sample) return CLOCK_OFFSET_INVALID;
    ClockOffsetMeasure m;
    if (clock_offset_measure(sample, &m) != CLOCK_OFFSET_OK) {
        estimator->rejected++;
        return CLOCK_OFFSET_INVALID;
    }
    estimator->window[estimator->next] = m;
    estimator->next = (estimator->next + 1u) % CLOCK_OFFSET_WINDOW;
    if (estimator->count < CLOCK_OFFSET_WINDOW) estimator->count++;
    return CLOCK_OFFSET_OK;
}

ClockOffsetStatus clock_offset_estimate(const ClockOffsetEstimator *estimator,
                                        ClockOffsetEstimate *out)
{
    if (!estimator || !out) return CLOCK_OFFSET_INVALID;
    if (estimator->count == 0u) return CLOCK_OFFSET_EMPTY;
    /* walk from the newest to the oldest so a strict < keeps the newest tie */
    const ClockOffsetMeasure *best = NULL;
    for (u32 age = 0u; age < estimator->count; ++age) {
        u32 index = (estimator->next + CLOCK_OFFSET_WINDOW - 1u - age) % CLOCK_OFFSET_WINDOW;
        const ClockOffsetMeasure *m = &estimator->window[index];
        if (!best || m->delay_us < best->delay_us) best = m;
    }
    out->offset_us = best->offset_us;
    out->delay_us = best->delay_us;
    out->error_us = ((u64)best->delay_us + 1u) / 2u;
    out->samples = estimator->count;
    return CLOCK_OFFSET_OK;
}

void clock_offset_merge_shifts(i64 offset_us, u64 *a_shift, u64 *b_shift)
{
    if (!a_shift || !b_shift) return;
    if (offset_us >= 0) {
        *a_shift = (u64)offset_us;
        *b_shift = 0u;
    } else {
        *a_shift = 0u;
        *b_shift = 0u - (u64)offset_us;
    }
}
