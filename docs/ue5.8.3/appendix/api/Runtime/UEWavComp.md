# Runtime / UEWavComp

- module root: `Source/Runtime/UEWavComp`
- headers: 1; symbols: 2
- symbol kinds: prototype=2

### `Source/Runtime/UEWavComp/Source/uewav.h` (Other)


#### Free symbols / members of external scopes

- L16 _prototype_ `void uewav_encode16(short *samples, short *scratch_buffer, long long num_samples, long long num_channels);` — Encodes/decodes 16-bit samples. samples is the input/output buffer, scratch_buffer is a temporary buffer. operates in place. samples is both input and output. scratch_buffer should be the same size as samples. num_samples is the number of samples in the buffer num_channels is the number of channels in the buffer.
- L17 _prototype_ `void uewav_decode16(short *samples, short *scratch_buffer, long long num_samples, long long num_channels);`
