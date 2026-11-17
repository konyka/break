#pragma once
/* Internal checked buffer arithmetic for audio_edit and focused tests. */

#include <audio/audio.h>

/* Validate mono/stereo channels and compute sample/byte spans without overflow.
 * False for NULL outputs, invalid channels or values not representable by the
 * platform's usize. */
bool audio_edit_buffer_span(u32 frames, u32 channels, usize *samples, usize *bytes);
