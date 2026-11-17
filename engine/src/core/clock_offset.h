#pragma once
/* Clock offset between two peers from NTP-style probes.
 *
 * A sample is four microsecond timestamps: t0 A sends, t1 B receives, t2 B
 * replies, t3 A receives (t0 and t3 on A's clock, t1 and t2 on B's).
 *   offset = floor(((t1 - t0) + (t2 - t3)) / 2)   B's clock minus A's
 *   delay  = (t3 - t0) - (t2 - t1)                round trip minus B's hold
 * A sample with t3 < t0, t2 < t1, a negative delay or a timestamp above
 * CLOCK_OFFSET_MAX_US is rejected.
 *
 * The estimator keeps the last CLOCK_OFFSET_WINDOW accepted samples and
 * reports the offset of the one with the smallest delay (ties: the newest).
 * The true offset lies within error_us = ceil(delay / 2) of it, whatever the
 * split of the delay between the two directions. */
#include <core/types.h>

#define CLOCK_OFFSET_WINDOW 8u
#define CLOCK_OFFSET_MAX_US (1ull << 61)

typedef enum ClockOffsetStatus {
    CLOCK_OFFSET_OK = 0,
    CLOCK_OFFSET_INVALID,
    CLOCK_OFFSET_EMPTY,
} ClockOffsetStatus;

typedef struct ClockOffsetSample {
    u64 t0, t1, t2, t3;
} ClockOffsetSample;

typedef struct ClockOffsetMeasure {
    i64 offset_us;
    i64 delay_us;
} ClockOffsetMeasure;

typedef struct ClockOffsetEstimate {
    i64 offset_us;
    i64 delay_us;
    u64 error_us;
    u32 samples; /* accepted samples currently in the window */
} ClockOffsetEstimate;

typedef struct ClockOffsetEstimator {
    ClockOffsetMeasure window[CLOCK_OFFSET_WINDOW];
    u32 count;
    u32 next;
    u64 rejected;
} ClockOffsetEstimator;

/* INVALID for a NULL argument or a rejected sample (*out untouched). */
ClockOffsetStatus clock_offset_measure(const ClockOffsetSample *sample, ClockOffsetMeasure *out);

void clock_offset_init(ClockOffsetEstimator *estimator);

/* Adds an accepted sample, evicting the oldest when the window is full. A
 * rejected sample only increments `rejected`. */
ClockOffsetStatus clock_offset_add(ClockOffsetEstimator *estimator, const ClockOffsetSample *sample);

/* EMPTY when no sample has been accepted. */
ClockOffsetStatus clock_offset_estimate(const ClockOffsetEstimator *estimator,
                                        ClockOffsetEstimate *out);

/* Non-negative shifts that put A's and B's timestamps on one timeline (for
 * trace_merge --offset-us): A + a_shift and B + b_shift are comparable.
 * Exactly one of them is non-zero unless offset is 0. */
void clock_offset_merge_shifts(i64 offset_us, u64 *a_shift, u64 *b_shift);

/* The same for one server and `count` peers, offsets_us[i] being peer i
 * minus the server: with base = max(0, max offsets_us[i]) the server shifts
 * by base and peer i by base - offsets_us[i], so every input lands on the
 * server's timeline moved by base. All shifts are non-negative and fit in
 * u64. One peer gives clock_offset_merge_shifts. False, with nothing
 * written, for NULL pointers or count 0. */
bool clock_offset_merge_shifts_many(const i64 *offsets_us, u32 count, u64 *server_shift,
                                    u64 *peer_shifts);
