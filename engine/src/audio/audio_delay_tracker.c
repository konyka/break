#include "audio_delay_tracker.h"

#include "audio_gcc_phat.h"

#include <math.h>
#include <stdlib.h>

struct AudioDelayTracker {
    AudioDelayEstimator *estimator;
    AudioGccPhat *gcc;
    double sample_rate;
    double min_abs_correlation;
    double max_slew;
    double delay;
    double correlation;
    u32 lock_count;
    u32 hold_updates;
    u32 accepted_run;
    u32 rejected_run;
    bool locked;
    bool use_gcc;
    u64 frames_since_update;
    u64 rejected;
};

static bool tracker_in_range(double value, double low, double high) {
    return value >= low && value <= high;
}

static AudioResult tracker_create(const AudioDelayTrackerConfig *config,
                                  AudioDelayTracker **out, bool use_gcc) {
    if (!config || !out ||
        !tracker_in_range((double)config->sample_rate, 8000.0, 192000.0) ||
        config->max_delay_frames < 1u ||
        config->max_delay_frames > AUDIO_DELAY_ESTIMATOR_MAX_DELAY ||
        config->window_frames < AUDIO_DELAY_ESTIMATOR_MIN_WINDOW ||
        config->window_frames > AUDIO_DELAY_ESTIMATOR_MAX_WINDOW ||
        !tracker_in_range(config->min_abs_correlation, 0.0, 1.0) ||
        !tracker_in_range(config->max_slew_frames_per_s, 0.1, 96000.0) ||
        config->lock_count < 1u || config->lock_count > 1000u ||
        config->hold_updates > 1000u) {
        return AUDIO_INVALID;
    }
    AudioDelayTracker *tracker = (AudioDelayTracker *)calloc(1u, sizeof(*tracker));
    if (!tracker) return AUDIO_OVERLOAD;
    tracker->sample_rate = config->sample_rate;
    tracker->min_abs_correlation = config->min_abs_correlation;
    tracker->max_slew = config->max_slew_frames_per_s;
    tracker->lock_count = config->lock_count;
    tracker->hold_updates = config->hold_updates;
    tracker->use_gcc = use_gcc;
    AudioResult result = AUDIO_OK;
    if (use_gcc) {
        const AudioGccPhatConfig gcc_config = {
            config->max_delay_frames, config->window_frames};
        result = audio_gcc_phat_create(&gcc_config, &tracker->gcc);
    } else {
        const AudioDelayEstimatorConfig estimator_config = {
            config->max_delay_frames, config->window_frames};
        result = audio_delay_estimator_create(&estimator_config, &tracker->estimator);
    }
    if (result != AUDIO_OK) {
        free(tracker);
        return result;
    }
    *out = tracker;
    return AUDIO_OK;
}

AudioResult audio_delay_tracker_create(const AudioDelayTrackerConfig *config,
                                       AudioDelayTracker **out) {
    return tracker_create(config, out, false);
}

AudioResult audio_delay_tracker_create_gcc(const AudioDelayTrackerConfig *config,
                                           AudioDelayTracker **out) {
    return tracker_create(config, out, true);
}

void audio_delay_tracker_destroy(AudioDelayTracker *tracker) {
    if (!tracker) return;
    audio_delay_estimator_destroy(tracker->estimator);
    audio_gcc_phat_destroy(tracker->gcc);
    free(tracker);
}

void audio_delay_tracker_reset(AudioDelayTracker *tracker) {
    if (!tracker) return;
    if (tracker->use_gcc) {
        audio_gcc_phat_reset(tracker->gcc);
    } else {
        audio_delay_estimator_reset(tracker->estimator);
    }
    tracker->delay = 0.0;
    tracker->correlation = 0.0;
    tracker->accepted_run = 0u;
    tracker->rejected_run = 0u;
    tracker->locked = false;
    tracker->frames_since_update = 0u;
    tracker->rejected = 0u;
}

void audio_delay_tracker_push_i16(AudioDelayTracker *tracker, const i16 *reference,
                                  const i16 *capture, u32 frames) {
    if (!tracker || !reference || !capture) return;
    if (tracker->use_gcc) {
        audio_gcc_phat_push_i16(tracker->gcc, reference, capture, frames);
    } else {
        audio_delay_estimator_push_i16(tracker->estimator, reference, capture, frames);
    }
    tracker->frames_since_update += frames;
}

bool audio_delay_tracker_update(AudioDelayTracker *tracker) {
    if (!tracker) return false;
    double measured = 0.0, score = 0.0;
    bool estimated = false;
    if (tracker->use_gcc) {
        estimated = audio_gcc_phat_estimate_with_confidence(tracker->gcc, &measured, &score);
    } else {
        estimated = audio_delay_estimator_estimate_subframe(tracker->estimator, &measured, &score);
    }
    const u64 elapsed_frames = tracker->frames_since_update;
    tracker->frames_since_update = 0u;
    tracker->correlation = estimated ? score : 0.0;
    if (!estimated || fabs(score) < tracker->min_abs_correlation) {
        ++tracker->rejected;
        ++tracker->rejected_run;
        tracker->accepted_run = 0u;
        if (tracker->locked && tracker->rejected_run > tracker->hold_updates) {
            tracker->locked = false;
        }
        return false;
    }
    tracker->rejected_run = 0u;
    if (!tracker->locked) {
        tracker->delay = measured;
        ++tracker->accepted_run;
        if (tracker->accepted_run >= tracker->lock_count) tracker->locked = true;
        return true;
    }
    const double elapsed = (double)elapsed_frames / tracker->sample_rate;
    const double maximum = tracker->max_slew * elapsed;
    double change = measured - tracker->delay;
    if (change > maximum) change = maximum;
    if (change < -maximum) change = -maximum;
    tracker->delay += change;
    return true;
}

double audio_delay_tracker_delay(const AudioDelayTracker *tracker) {
    return tracker ? tracker->delay : 0.0;
}

double audio_delay_tracker_correlation(const AudioDelayTracker *tracker) {
    return tracker ? tracker->correlation : 0.0;
}

bool audio_delay_tracker_locked(const AudioDelayTracker *tracker) {
    return tracker && tracker->locked;
}

u64 audio_delay_tracker_rejections(const AudioDelayTracker *tracker) {
    return tracker ? tracker->rejected : 0u;
}
