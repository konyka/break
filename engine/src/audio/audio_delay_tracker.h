#pragma once
/* Confidence-gated fractional delay tracking above audio_delay_estimator:
 * accepted-run locking, low-confidence hold/unlock and pushed-time slew
 * (docs/design/audio_extended.md, "Delay estimation"). Mono owner
 * thread; only create allocates. */

#include <audio/audio.h>

#include <audio/audio_delay_estimator.h>

typedef struct {
    u32 sample_rate;             /* 8000..192000 */
    u32 max_delay_frames;        /* estimator limits */
    u32 window_frames;           /* estimator limits */
    f32 min_abs_correlation;     /* 0..1 */
    f32 max_slew_frames_per_s;   /* 0.1..96000 while locked */
    u32 lock_count;              /* 1..1000 consecutive accepted estimates */
    u32 hold_updates;            /* 0..1000 rejected updates kept locked */
} AudioDelayTrackerConfig;

typedef struct AudioDelayTracker AudioDelayTracker;

/* INVALID for NULL/out-of-range config, OVERLOAD on allocation failure; *out
 * is written only on success. */
AudioResult audio_delay_tracker_create(const AudioDelayTrackerConfig *config,
                                       AudioDelayTracker **out);
void audio_delay_tracker_destroy(AudioDelayTracker *tracker); /* NULL is a no-op */
void audio_delay_tracker_reset(AudioDelayTracker *tracker); /* estimator included */
void audio_delay_tracker_push_i16(AudioDelayTracker *tracker, const i16 *reference,
                                  const i16 *capture, u32 frames);
/* Run one subframe estimate. True only for an accepted high-confidence result;
 * locked state may still be false until lock_count accepted updates. */
bool audio_delay_tracker_update(AudioDelayTracker *tracker);
/* Current delay in frames; 0 for NULL. */
double audio_delay_tracker_delay(const AudioDelayTracker *tracker);
/* Latest signed estimator score, including a rejected low-confidence result;
 * 0 after reset, for NULL, or when the estimator cannot produce a result. */
double audio_delay_tracker_correlation(const AudioDelayTracker *tracker);
bool audio_delay_tracker_locked(const AudioDelayTracker *tracker); /* false for NULL */
u64 audio_delay_tracker_rejections(const AudioDelayTracker *tracker); /* 0 for NULL */
