#pragma once

#include <audio/audio.h>

#define AUDIO_DSP_MAX_STAGES 4u
#define AUDIO_DSP_MAX_DELAY_FRAMES 8192u

typedef enum {
    AUDIO_DSP_FILTER = 0,
    AUDIO_DSP_DELAY,
    AUDIO_DSP_REVERB
} AudioDspType;

typedef struct {
    AudioDspType type;
    f32 cutoff_hz;
    u32 delay_frames;
    f32 feedback;
    f32 mix;
    f32 room;
} AudioDspStageDesc;

typedef struct {
    u32 stage_count;
    AudioDspStageDesc stages[AUDIO_DSP_MAX_STAGES];
} AudioDspChainDesc;

typedef struct {
    AudioDspStageDesc desc;
    f32 alpha;
    f32 filter_state[2];
    f32 *delay_line;
    u32 delay_cursor;
} AudioDspStage;

typedef struct {
    u32 stage_count;
    u32 sample_rate;
    AudioDspStage stages[AUDIO_DSP_MAX_STAGES];
} AudioDspChain;

AudioResult audio_dsp_chain_validate(const AudioDspChainDesc *desc,
                                     u32 sample_rate);
f32 audio_dsp_filter_alpha(f32 cutoff_hz, u32 sample_rate);
AudioResult audio_dsp_chain_init(AudioDspChain *chain,
    const AudioDspChainDesc *desc, f32 *delay_storage, usize sample_capacity,
    u32 sample_rate);
void audio_dsp_chain_process(AudioDspChain *chain, f32 *interleaved,
                             u32 frames, u32 channels);
