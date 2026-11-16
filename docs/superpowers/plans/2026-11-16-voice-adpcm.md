# Compressed network voice: IMA ADPCM frames (2026-11-16)

## Goal
`BRV1` voice frames carry raw little-endian 16-bit PCM: a 20 ms mono frame
at 16 kHz is 640 bytes of samples. The network voice path has no codec
(`docs/cross_engine/missing_capabilities.md` §10). This slice adds a
4-bit IMA ADPCM frame format, 4:1 against 16-bit PCM, with no new
dependency, and keeps `BRV1` working unchanged.

## Design
- `BRV2`: same 16-byte header as `BRV1` (magic, sequence, sample_rate,
  channels, sample_count), then per channel a 4-byte state block (the
  channel's first sample as `predictor:i16 le`, `step_index:u8`,
  `reserved:u8 = 0`) and then one 4-bit code for every later sample, two
  per byte, low nibble first, interleaved by channel the same way the PCM
  samples are. Every frame carries its own start state, so a lost frame
  never breaks the next one.
  Size: `16 + 4 * channels + ceil((sample_count - channels) / 2)`.
- `break_voice_encode_adpcm(frame, out, capacity, &size)`: the encoder
  starts each frame from the first sample of each channel as predictor
  and a step index chosen from the first difference, so the state is
  self-contained.
- The receiver accepts both `BRV1` and `BRV2` for the configured format
  (rate, channels, sample count must still match). `BRV2` with a
  `step_index` above 88 or a non-zero reserved byte, or the wrong length,
  is invalid and counted like any malformed frame.
- `break_voice_decode_adpcm` is not public; decoding happens in `pump`.
- Quality: IMA ADPCM is lossy. The reference model gives 36 dB SNR for a
  440 Hz sine at -6 dBFS sampled at 16 kHz (44 dB at 200 Hz, 29 dB at
  1 kHz, 19 dB at 3 kHz); the test requires more than 30 dB at 440 Hz.
- Not done: Opus or another perceptual codec, packet loss concealment
  beyond the receiver's existing silence fill, bit-exact interop with
  other IMA ADPCM container formats (only the step table and the nibble
  update rule are the standard ones).

## Tests (TDD, `test_break_online_voice`)
- size and layout: exact byte length for mono and stereo, odd sample
  counts; the header fields; reserved bytes zero.
- round trip: a sine through encode -> receiver push / pump / pop has SNR
  >= 20 dB; silence decodes to exact silence; a full-scale square wave
  stays within the i16 range without wrap.
- the reference IMA step table and index table give a known code sequence
  for a fixed input (guards the tables). Expected codes and decoded
  samples come from a separate reference model of the standard tables,
  not from the C code.
- invalid `BRV2`: bad step index, non-zero reserved byte, short and long
  lengths, other channel count: all counted `invalid`, nothing plays.
- `BRV1` frames still decode exactly.
- mixed: `BRV1` and `BRV2` frames of one stream play in sequence order.

## Status
- RED: five cases failed against a stub encoder returning `INVALID`; the
  eight existing cases passed. (A first attempt used 6-sample frames at
  8 kHz, which the receiver refuses as shorter than 1 ms; those vectors
  now use a 1000 Hz stream, since the codec does not depend on the rate.)
- GREEN: `test_break_online_voice` 14/14; ASan+UBSan clean.
- The header macro first counted a code for every sample; the first
  sample of each channel is the start state, so a frame has
  `sample_count - channels` codes.
- Mutation: 27 mutations. The first run had seven survivors: every
  encoder comparison (`>=` against `>`, sign test, start index search and
  magnitude) was untested at its boundary. A new case drives each one
  exactly onto its boundary and compares codes and decoded samples with
  the reference model. One survivor remained: indexing the 16-entry index
  table with `code & 7` changes nothing, because the table's second half
  repeats the first. The table is now the eight distinct entries indexed
  by the magnitude bits. Third run: all killed.
- Not done: Opus or another perceptual codec; the sender side of the
  application (choosing BRV2 by default) is left to the caller.
