#pragma once
/* Scheduled mono playback-reference alignment using the existing delay tracker
 * and delay line. Owner thread; only create allocates. */

#include <audio/audio_delay_tracker.h>

typedef struct {
    AudioDelayTrackerConfig tracker;
    u32 update_period_frames; /* 1..192000 */
} AudioVoiceAlignerConfig;

typedef struct AudioVoiceAligner AudioVoiceAligner;

/* Failure leaves *out unchanged. GCC uses the same config and tracker policy. */
AudioResult audio_voice_aligner_create(const AudioVoiceAlignerConfig *config,
                                       AudioVoiceAligner **out);
AudioResult audio_voice_aligner_create_gcc(const AudioVoiceAlignerConfig *config,
                                           AudioVoiceAligner **out);
void audio_voice_aligner_destroy(AudioVoiceAligner *aligner); /* NULL is a no-op */
/* Raw reference/capture inputs; aligned reference output. Reference/output may
 * alias, capture/output may not. Updates take effect after each exact period. */
AudioResult audio_voice_aligner_process_i16(AudioVoiceAligner *aligner,
                                            const i16 *reference, const i16 *capture,
                                            i16 *aligned_reference, u32 frames);
double audio_voice_aligner_delay(const AudioVoiceAligner *aligner);
u64 audio_voice_aligner_updates(const AudioVoiceAligner *aligner);
bool audio_voice_aligner_locked(const AudioVoiceAligner *aligner);
bool audio_voice_aligner_uses_gcc(const AudioVoiceAligner *aligner);
u64 audio_voice_aligner_rejections(const AudioVoiceAligner *aligner);
/* The tracker's latest signed score (audio_delay_tracker_correlation); 0 for NULL. */
double audio_voice_aligner_correlation(const AudioVoiceAligner *aligner);
