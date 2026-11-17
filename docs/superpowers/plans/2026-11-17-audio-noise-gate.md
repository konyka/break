# Audio: noise gate with an adaptive noise floor for captured voice

Status: Done

## Goal

Captured voice carries room and fan noise between words. Add a time-domain
noise reduction step for the owner thread: a downward expander that learns
the noise floor and attenuates what stays near it, while speech above it
passes. There is no FFT in the engine, so spectral subtraction stays out of
scope.

## API (`engine/src/audio/audio_noise_gate.h`)

- `AudioNoiseGateConfig { sample_rate, channels, threshold_db,
  reduction_db, attack_ms, release_ms, floor_rise_db_per_s,
  initial_floor_dbfs }`. Ranges: rate 8000..192000, 1 or 2 channels,
  threshold 3..40 dB above the floor, reduction 0..80 dB, attack
  0.1..1000 ms (opening), release 1..10000 ms (closing), floor rise
  0.1..60 dB/s, initial floor -120..0 dBFS. INVALID otherwise.
- `audio_noise_gate_init`, `audio_noise_gate_process_i16` (in place),
  `audio_noise_gate_gain_db`, `audio_noise_gate_floor_dbfs`.

## Behaviour

- Level: 10 ms one-pole mean square of the channel average, in dBFS,
  at least -120 (silence).
- Floor: falls to the level at once when the level is below it; otherwise
  rises by `floor_rise_db_per_s / rate` per frame, never past the level.
  Never below -120.
- Open when level >= floor + threshold: target gain 0 dB; closed:
  -reduction_db. The gain approaches the target with the attack time
  constant while rising and the release time constant while falling.
- Output `nearbyint(x * 10^(gain / 20))`, clamped to i16; one gain for
  all channels; frame by frame, so chunking does not change the output.
- Long steady speech raises the floor at the rise rate and eventually
  closes the gate; the rise rate sets how long that takes.

## Tests (`test_audio_noise_gate`)

1. Config validation, *gate untouched on failure.
2. Steady noise: the floor converges to it, the gate closes, the output
   drops by reduction_db.
3. A tone well above the floor passes at 0 dB after the attack.
4. Quieter noise pulls the floor down at once.
5. Silence: floor -120, output zero, no NaN.
6. Stereo and chunking match an independent reference model bit for bit.

## Result

- `test_audio_noise_gate`: 8 tests (a 7th test checks that the floor rises
  to a constant level and never past it). RED on link, then GREEN.
- Mutations: 27 of 30 caught. The separate floor-fall branch and the i16
  clamp were unreachable (the floor update is `min(floor + rise, level)`;
  the gain never exceeds 0 dB), so they were removed. Survivors: silence as
  -inf (clamped to -120 on the next line), initial linear gain (recomputed
  every frame before use), and `>=` vs `>` at the threshold (differs only
  at exact equality).
- ASan+UBSan and `-Wshadow -Wdouble-promotion` clean.
- Docs: `docs/design/audio_extended.md` "噪声门（降噪）",
  `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`.
