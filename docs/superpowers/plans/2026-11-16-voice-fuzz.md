# Voice receiver fuzz target (2026-11-16)

## Goal
The voice receiver (`engine/src/network/break_online_voice.c`) decodes
`BRV1` (PCM) and `BRV2` (IMA ADPCM) datagrams that come straight from the
network. It has unit tests but no fuzz target, and the ADPCM decoder
indexes a table with a byte taken from the wire. This slice adds
`fuzz_break_online_voice`, a deterministic mutation fuzzer that runs in the
existing fuzz smoke lane under ASan/UBSan.

## Design
- `engine/tests/fuzz_break_online_voice.c`, usage
  `fuzz_break_online_voice [iterations] [seed]`.
- Each iteration builds a valid frame (random config among 8/16/44.1/48 kHz,
  mono and stereo; sequence near a base so duplicates and stale frames
  happen), encodes it as `BRV1` or `BRV2`, then mutates it: byte writes and
  bit flips, boundary values in the header words, magic swaps, ADPCM step
  index 88/89/255, non-zero reserved byte, truncation, one extra byte.
- An independent reference model in the harness decides whether the bytes
  are a valid frame for the receiver's config and decodes them (its own
  PCM and IMA ADPCM decoder).
- Checks after each `push` + `pump(1)`:
  - exactly one of `accepted/invalid/duplicate/stale/overload` grows by one;
  - `invalid` grows exactly when the reference model rejects the bytes.
- Playout: `pop` runs at an advancing clock. A played frame must have the
  configured sample count, its sequence must be one more than the previous
  playout, and its samples must equal the reference decode of the datagram
  that was accepted with that sequence. Concealed frames are silent.
- The receiver lives across 64 iterations, then is destroyed and recreated
  with a new config, so the jitter buffer state builds up before teardown.
- Some iterations encode a well-formed frame whose only fault is a sample
  count one channel step away from the configured one, so the count check
  alone must reject it.
- CMake: `EXCLUDE_FROM_ALL`, smoke test `fuzz_break_online_voice_smoke`
  (`2000 43`) with label `fuzz` under `ENGINE_BUILD_FUZZ_SMOKE`; added to all
  three CI fuzz build lists (ASan lane, MSVC lane, MinGW lane), which
  `test_wayland_ci_migration_contract` now requires.

## TDD
- RED: the harness runs against mutated copies of the receiver (removed
  step-index check, removed length check, wrong nibble order, wrong
  predictor sign, missing duplicate check, wrong sequence advance); each
  must make the harness fail.
- GREEN: the harness passes on the real receiver, in a plain build and
  under ASan+UBSan.

## Status
Done.
- `test_wayland_ci_migration_contract` was RED after adding the new target to
  its required list (`fuzz_break_online_voice appears 1 times`), GREEN after
  the two other build steps named it.
- Harness against the real receiver: 2000 iterations (seed 43) and 50000
  iterations (seed 7) pass under ASan+UBSan; every outcome (accepted,
  invalid, played, concealed) is reached.
- 28 receiver mutants (`/tmp/mut_voice_fuzz.py`): all caught. The first run
  left two alive: removing the sample-count check (the harness never sent a
  well-formed frame with only a wrong count, fixed by the case above) and
  removing the short-header check (equivalent: the BRV1/BRV2 magic and the
  exact-length checks already reject such datagrams and the inbox always
  holds 1280 bytes, so it was replaced by a channel-check mutant).
- ASan+UBSan fuzz lane `ctest -L fuzz`: 14/14.
