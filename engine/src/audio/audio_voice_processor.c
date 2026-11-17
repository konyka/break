#include "audio_voice_processor.h"

#include <stdlib.h>

struct AudioVoiceProcessor {
    AudioVoiceProcessorConfig config;
    AudioEchoCanceller *echo;
    AudioNoiseSuppressor *noise;
    AudioResidualEchoSuppressor residual;
    AudioNoiseGate gate;
    AudioAgc agc;
};

AudioResult audio_voice_processor_create(const AudioVoiceProcessorConfig *config,
                                         AudioVoiceProcessor **out) {
    if (!config || !out || config->echo.sample_rate != config->residual.sample_rate ||
        config->echo.sample_rate != config->noise.sample_rate ||
        config->echo.sample_rate != config->gate.sample_rate ||
        config->echo.sample_rate != config->agc.sample_rate ||
        config->gate.channels != 1u || config->agc.channels != 1u) {
        return AUDIO_INVALID;
    }
    AudioVoiceProcessor *processor = (AudioVoiceProcessor *)calloc(1u, sizeof(*processor));
    if (!processor) return AUDIO_OVERLOAD;
    processor->config = *config;
    AudioResult result = audio_echo_canceller_create(&config->echo, &processor->echo);
    if (result == AUDIO_OK) {
        result = audio_residual_echo_suppressor_init(&processor->residual, &config->residual);
    }
    if (result == AUDIO_OK) {
        result = audio_noise_suppressor_create(&config->noise, &processor->noise);
    }
    if (result == AUDIO_OK) result = audio_noise_gate_init(&processor->gate, &config->gate);
    if (result == AUDIO_OK) result = audio_agc_init(&processor->agc, &config->agc);
    if (result != AUDIO_OK) {
        audio_voice_processor_destroy(processor);
        return result;
    }
    *out = processor;
    return AUDIO_OK;
}

void audio_voice_processor_destroy(AudioVoiceProcessor *processor) {
    if (!processor) return;
    audio_noise_suppressor_destroy(processor->noise);
    audio_echo_canceller_destroy(processor->echo);
    free(processor);
}

void audio_voice_processor_reset(AudioVoiceProcessor *processor) {
    if (!processor) return;
    audio_echo_canceller_reset(processor->echo);
    audio_residual_echo_suppressor_reset(&processor->residual);
    audio_noise_suppressor_reset(processor->noise);
    (void)audio_noise_gate_init(&processor->gate, &processor->config.gate);
    (void)audio_agc_init(&processor->agc, &processor->config.agc);
}

void audio_voice_processor_process_i16(AudioVoiceProcessor *processor,
                                       const i16 *reference, i16 *capture, u32 frames) {
    if (!processor || frames == 0u || !reference || !capture) return;
    audio_residual_echo_suppressor_process_with_aec(&processor->residual, processor->echo,
                                                    reference, capture, frames);
    audio_noise_suppressor_process_i16(processor->noise, capture, frames);
    audio_noise_gate_process_i16(&processor->gate, capture, frames);
    audio_agc_process_i16(&processor->agc, capture, frames);
}

u32 audio_voice_processor_latency_frames(const AudioVoiceProcessor *processor) {
    return processor ? audio_noise_suppressor_latency_frames(processor->noise) : 0u;
}
