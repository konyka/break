#include "audio_dsp.h"
#include <math.h>
#include <string.h>

#define AUDIO_DSP_REVERB_FRAMES 997u

static bool finite_range(f32 value, f32 minimum, f32 maximum) {
    return isfinite(value) && value >= minimum && value <= maximum;
}

AudioResult audio_dsp_chain_validate(const AudioDspChainDesc *desc,
                                     u32 sample_rate) {
    if (!desc || sample_rate == 0) return AUDIO_INVALID;
    if (desc->stage_count > AUDIO_DSP_MAX_STAGES) return AUDIO_OVERLOAD;
    for (u32 i = 0; i < desc->stage_count; ++i) {
        const AudioDspStageDesc *stage = &desc->stages[i];
        if (stage->type == AUDIO_DSP_FILTER) {
            if (!isfinite(stage->cutoff_hz) || stage->cutoff_hz <= 0.0f ||
                stage->cutoff_hz > (f32)sample_rate * 0.5f) return AUDIO_INVALID;
        } else if (stage->type == AUDIO_DSP_DELAY) {
            if (stage->delay_frames == 0 ||
                stage->delay_frames > AUDIO_DSP_MAX_DELAY_FRAMES ||
                !finite_range(stage->feedback, 0.0f, 0.95f) ||
                !finite_range(stage->mix, 0.0f, 1.0f)) return AUDIO_INVALID;
        } else if (stage->type == AUDIO_DSP_REVERB) {
            if (!finite_range(stage->room, 0.0f, 0.95f) ||
                !finite_range(stage->mix, 0.0f, 1.0f)) return AUDIO_INVALID;
        } else {
            return AUDIO_INVALID;
        }
    }
    return AUDIO_OK;
}

f32 audio_dsp_filter_alpha(f32 cutoff_hz, u32 sample_rate) {
    const f32 pi = 3.14159265358979323846f;
    return 1.0f - expf(-2.0f * pi * cutoff_hz / (f32)sample_rate);
}

AudioResult audio_dsp_chain_init(AudioDspChain *chain,
    const AudioDspChainDesc *desc, f32 *delay_storage, usize sample_capacity,
    u32 sample_rate) {
    if (!chain) return AUDIO_INVALID;
    AudioResult validation = audio_dsp_chain_validate(desc, sample_rate);
    if (validation != AUDIO_OK) return validation;

    usize delay_stages = 0;
    for (u32 i = 0; i < desc->stage_count; ++i) {
        if (desc->stages[i].type != AUDIO_DSP_FILTER) delay_stages++;
    }
    usize required = delay_stages * AUDIO_DSP_MAX_DELAY_FRAMES * 2u;
    if (sample_capacity < required || (required > 0 && !delay_storage)) {
        return AUDIO_OVERLOAD;
    }

    AudioDspChain prepared;
    memset(&prepared, 0, sizeof(prepared));
    prepared.stage_count = desc->stage_count;
    prepared.sample_rate = sample_rate;
    usize offset = 0;
    for (u32 i = 0; i < desc->stage_count; ++i) {
        AudioDspStage *stage = &prepared.stages[i];
        stage->desc = desc->stages[i];
        if (stage->desc.type == AUDIO_DSP_FILTER) {
            stage->alpha = audio_dsp_filter_alpha(stage->desc.cutoff_hz,
                                                  sample_rate);
        } else {
            stage->delay_line = delay_storage + offset;
            offset += AUDIO_DSP_MAX_DELAY_FRAMES * 2u;
        }
    }
    if (required > 0) memset(delay_storage, 0, required * sizeof(f32));
    *chain = prepared;
    return AUDIO_OK;
}

static u32 reverb_delay(u32 cursor, u32 tap) {
    return (cursor + AUDIO_DSP_REVERB_FRAMES - tap) % AUDIO_DSP_REVERB_FRAMES;
}

void audio_dsp_chain_process(AudioDspChain *chain, f32 *interleaved,
                             u32 frames, u32 channels) {
    if (!chain || !interleaved || (channels != 1 && channels != 2)) return;
    for (u32 frame = 0; frame < frames; ++frame) {
        usize base = (usize)frame * channels;
        f32 sample[2];
        sample[0] = interleaved[base];
        sample[1] = channels == 2 ? interleaved[base + 1u] : sample[0];
        for (u32 i = 0; i < chain->stage_count; ++i) {
            AudioDspStage *stage = &chain->stages[i];
            if (stage->desc.type == AUDIO_DSP_FILTER) {
                for (u32 channel = 0; channel < channels; ++channel) {
                    f32 *state = &stage->filter_state[channel];
                    *state += stage->alpha * (sample[channel] - *state);
                    sample[channel] = *state;
                }
            } else if (stage->desc.type == AUDIO_DSP_DELAY) {
                u32 delay = stage->desc.delay_frames;
                for (u32 channel = 0; channel < channels; ++channel) {
                    f32 *line = stage->delay_line + channel * AUDIO_DSP_MAX_DELAY_FRAMES;
                    f32 delayed = line[stage->delay_cursor];
                    f32 dry = sample[channel];
                    line[stage->delay_cursor] = dry + delayed * stage->desc.feedback;
                    sample[channel] = dry * (1.0f - stage->desc.mix) +
                                      delayed * stage->desc.mix;
                }
                stage->delay_cursor = (stage->delay_cursor + 1u) % delay;
            } else {
                static const u32 taps[4] = {149, 311, 587, 997};
                for (u32 channel = 0; channel < channels; ++channel) {
                    f32 *line = stage->delay_line + channel * AUDIO_DSP_MAX_DELAY_FRAMES;
                    f32 wet = 0.0f;
                    for (u32 tap = 0; tap < 4; ++tap) {
                        wet += line[reverb_delay(stage->delay_cursor, taps[tap])];
                    }
                    wet *= 0.25f;
                    f32 oldest = line[stage->delay_cursor];
                    f32 dry = sample[channel];
                    f32 feedback = 0.5f + 0.4f * stage->desc.room;
                    line[stage->delay_cursor] = dry + oldest * feedback;
                    sample[channel] = dry * (1.0f - stage->desc.mix) +
                                      wet * stage->desc.mix;
                }
                stage->delay_cursor = (stage->delay_cursor + 1u) %
                                      AUDIO_DSP_REVERB_FRAMES;
            }
        }
        interleaved[base] = sample[0];
        if (channels == 2) interleaved[base + 1u] = sample[1];
    }
}
