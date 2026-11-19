#include "audio_voice_aligner.h"

#include <stdlib.h>

#ifdef AUDIO_VOICE_ALIGNER_DELAY_HOOK
AudioResult AUDIO_VOICE_ALIGNER_DELAY_HOOK(AudioDelayLine *line, double delay);
#endif

struct AudioVoiceAligner {
    AudioDelayTracker *tracker;
    AudioDelayLine *line;
    u32 update_period_frames;
    u32 frames_until_update;
    u64 updates;
    bool use_gcc;
};

static AudioResult aligner_create(const AudioVoiceAlignerConfig *config,
                                  AudioVoiceAligner **out, bool use_gcc) {
    if (!out || !config || config->update_period_frames == 0u ||
        config->update_period_frames > 192000u) {
        return AUDIO_INVALID;
    }
    AudioVoiceAligner *aligner = (AudioVoiceAligner *)calloc(1u, sizeof(*aligner));
    if (!aligner) return AUDIO_OVERLOAD;
    const AudioResult tracker_result = use_gcc
        ? audio_delay_tracker_create_gcc(&config->tracker, &aligner->tracker)
        : audio_delay_tracker_create(&config->tracker, &aligner->tracker);
    if (tracker_result != AUDIO_OK) {
        free(aligner);
        return tracker_result;
    }
    const AudioResult line_result =
        audio_delay_line_create(config->tracker.max_delay_frames, &aligner->line);
    if (line_result != AUDIO_OK) {
        audio_delay_tracker_destroy(aligner->tracker);
        free(aligner);
        return line_result;
    }
    aligner->update_period_frames = config->update_period_frames;
    aligner->frames_until_update = config->update_period_frames;
    aligner->use_gcc = use_gcc;
    *out = aligner;
    return AUDIO_OK;
}

AudioResult audio_voice_aligner_create(const AudioVoiceAlignerConfig *config,
                                       AudioVoiceAligner **out) {
    return aligner_create(config, out, false);
}

AudioResult audio_voice_aligner_create_gcc(const AudioVoiceAlignerConfig *config,
                                           AudioVoiceAligner **out) {
    return aligner_create(config, out, true);
}

void audio_voice_aligner_destroy(AudioVoiceAligner *aligner) {
    if (!aligner) return;
    audio_delay_line_destroy(aligner->line);
    audio_delay_tracker_destroy(aligner->tracker);
    free(aligner);
}

AudioResult audio_voice_aligner_process_i16(AudioVoiceAligner *aligner,
                                            const i16 *reference, const i16 *capture,
                                            i16 *aligned_reference, u32 frames) {
    if (!aligner) return AUDIO_INVALID;
    if (frames == 0u) return AUDIO_OK;
    if (!reference || !capture || !aligned_reference || capture == aligned_reference) {
        return AUDIO_INVALID;
    }
    while (frames > 0u) {
        const u32 chunk = frames < aligner->frames_until_update
                              ? frames
                              : aligner->frames_until_update;
        audio_delay_tracker_push_i16(aligner->tracker, reference, capture, chunk);
        audio_delay_line_process_i16(aligner->line, reference, aligned_reference, chunk);
        aligner->frames_until_update -= chunk;
        if (aligner->frames_until_update == 0u) {
            ++aligner->updates;
            aligner->frames_until_update = aligner->update_period_frames;
            if (audio_delay_tracker_update(aligner->tracker)) {
#ifdef AUDIO_VOICE_ALIGNER_DELAY_HOOK
                const AudioResult result = AUDIO_VOICE_ALIGNER_DELAY_HOOK(
                    aligner->line, audio_delay_tracker_delay(aligner->tracker));
#else
                const AudioResult result = audio_delay_line_set_subframe_delay(
                    aligner->line, audio_delay_tracker_delay(aligner->tracker));
#endif
                if (result != AUDIO_OK) return result;
            }
        }
        reference += chunk;
        capture += chunk;
        aligned_reference += chunk;
        frames -= chunk;
    }
    return AUDIO_OK;
}

double audio_voice_aligner_delay(const AudioVoiceAligner *aligner) {
    return aligner ? audio_delay_line_subframe_delay(aligner->line) : 0.0;
}

u64 audio_voice_aligner_updates(const AudioVoiceAligner *aligner) {
    return aligner ? aligner->updates : 0u;
}

bool audio_voice_aligner_locked(const AudioVoiceAligner *aligner) {
    return aligner && audio_delay_tracker_locked(aligner->tracker);
}

bool audio_voice_aligner_uses_gcc(const AudioVoiceAligner *aligner) {
    return aligner && aligner->use_gcc;
}

u64 audio_voice_aligner_rejections(const AudioVoiceAligner *aligner) {
    return aligner ? audio_delay_tracker_rejections(aligner->tracker) : 0u;
}

double audio_voice_aligner_correlation(const AudioVoiceAligner *aligner) {
    return aligner ? audio_delay_tracker_correlation(aligner->tracker) : 0.0;
}
