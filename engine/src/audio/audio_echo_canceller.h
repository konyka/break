#pragma once
/* Acoustic echo cancellation for captured voice: an NLMS adaptive filter
 * that predicts the echo of the playback reference in the capture and
 * subtracts it, with Geigel double-talk detection
 * (docs/design/audio_extended.md, "Echo cancellation"). Owner thread only;
 * allocates only in create. */

#include <audio/audio.h>

#define AUDIO_ECHO_CANCELLER_MAX_TAPS 8192u

typedef struct {
    u32 sample_rate;           /* 8000..192000 */
    u32 taps;                  /* 1..AUDIO_ECHO_CANCELLER_MAX_TAPS, echo path length in frames */
    f32 step_size;             /* 0.001..1, NLMS mu */
    f32 double_talk_threshold; /* 0..1, 0 turns detection off */
    f32 hangover_ms;           /* 0..1000, adaptation stays off this long after double talk */
} AudioEchoCancellerConfig;

typedef struct AudioEchoCanceller AudioEchoCanceller;

/* INVALID for a NULL argument or a config out of range, OVERLOAD when memory
 * runs out; *out is written only on success. Weights and history start at 0. */
AudioResult audio_echo_canceller_create(const AudioEchoCancellerConfig *config,
                                        AudioEchoCanceller **out);
void audio_echo_canceller_destroy(AudioEchoCanceller *aec); /* NULL is a no-op */
/* Clears the weights, the history and the hangover. */
void audio_echo_canceller_reset(AudioEchoCanceller *aec);
/* Mono. `reference` holds the playback frames aligned with `capture`;
 * `capture` is replaced by the capture minus the predicted echo. */
void audio_echo_canceller_process_i16(AudioEchoCanceller *aec, const i16 *reference,
                                      i16 *capture, u32 frames);
/* Weight k of the echo path estimate; 0 for NULL or k >= taps. */
double audio_echo_canceller_weight(const AudioEchoCanceller *aec, u32 k);
/* Whether the most recently processed frame matched Geigel detection or consumed
 * hangover. False for NULL, reset or disabled detection; zero frames preserve it. */
bool audio_echo_canceller_near_end_active(const AudioEchoCanceller *aec);
