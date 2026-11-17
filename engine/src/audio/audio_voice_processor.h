#pragma once
/* Integrated mono capture processing: AEC, residual suppression, spectral
 * noise reduction, noise gate and AGC. Owner thread; only create allocates. */

#include <audio/audio_agc.h>
#include <audio/audio_echo_canceller.h>
#include <audio/audio_noise_gate.h>
#include <audio/audio_noise_suppressor.h>
#include <audio/audio_residual_echo_suppressor.h>

typedef struct {
    AudioEchoCancellerConfig echo;
    AudioResidualEchoSuppressorConfig residual;
    AudioNoiseSuppressorConfig noise;
    AudioNoiseGateConfig gate;
    AudioAgcConfig agc;
} AudioVoiceProcessorConfig;

typedef struct AudioVoiceProcessor AudioVoiceProcessor;

/* All nested sample rates must match; gate/AGC must be mono. INVALID for NULL
 * or nested validation failure, OVERLOAD on allocation failure. */
AudioResult audio_voice_processor_create(const AudioVoiceProcessorConfig *config,
                                         AudioVoiceProcessor **out);
void audio_voice_processor_destroy(AudioVoiceProcessor *processor); /* NULL is a no-op */
void audio_voice_processor_reset(AudioVoiceProcessor *processor);
/* Aligned playback reference and in-place capture. NULL signals are accepted
 * only for zero frames; other invalid calls are no-ops. */
void audio_voice_processor_process_i16(AudioVoiceProcessor *processor,
                                       const i16 *reference, i16 *capture, u32 frames);
/* Fixed spectral-processing delay; 0 for NULL. */
u32 audio_voice_processor_latency_frames(const AudioVoiceProcessor *processor);
