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
/* Returns to the just-created state: tracker and delay line reset, delay 0,
 * update count 0 and a full period until the next update. Keeps the backend,
 * configuration, sinc mode and crossfade length. No allocation; NULL is a no-op. */
void audio_voice_aligner_reset(AudioVoiceAligner *aligner);
/* Raw reference/capture inputs; aligned reference output. Reference/output may
 * alias, capture/output may not. Updates take effect after each exact period. */
AudioResult audio_voice_aligner_process_i16(AudioVoiceAligner *aligner,
                                            const i16 *reference, const i16 *capture,
                                            i16 *aligned_reference, u32 frames);
/* Switches the delay line's sinc mode and re-applies the latest applied delay
 * minus the 8-frame sinc latency (floored at 0), so the output stays aligned.
 * The switch itself is immediate. INVALID for NULL; REJECTED during a fade. */
AudioResult audio_voice_aligner_set_sinc(AudioVoiceAligner *aligner, bool enabled);
bool audio_voice_aligner_sinc(const AudioVoiceAligner *aligner); /* false for NULL */
/* Fade length for later delay updates, 0..48000 frames (see the delay line).
 * An update that arrives during a fade is skipped and retried next period. */
AudioResult audio_voice_aligner_set_crossfade_frames(AudioVoiceAligner *aligner, u32 frames);
u32 audio_voice_aligner_crossfade_frames(const AudioVoiceAligner *aligner); /* 0 for NULL */
/* Total output delay in frames: the line delay plus the sinc latency. */
double audio_voice_aligner_delay(const AudioVoiceAligner *aligner);
u64 audio_voice_aligner_updates(const AudioVoiceAligner *aligner);
bool audio_voice_aligner_locked(const AudioVoiceAligner *aligner);
bool audio_voice_aligner_uses_gcc(const AudioVoiceAligner *aligner);
u64 audio_voice_aligner_rejections(const AudioVoiceAligner *aligner);
/* The tracker's latest signed score (audio_delay_tracker_correlation); 0 for NULL. */
double audio_voice_aligner_correlation(const AudioVoiceAligner *aligner);
