# Interaural delay: crossfade delay changes (2026-11-17)

Status: Done

## Goal
A change of interaural delay (source or listener moving, the cue turned on
or off) jumps the far ear to another point of its history, which clicks.
This slice crossfades from the old delay to the new one.

## Design
- Streams and voices share one `ItdLine`: 64 frames of history, `current`
  and `previous` delays (signed, positive delays the left ear), `fade`
  frames left and `primed`.
- Each frame is pushed first. Then, if no fade is running and the target
  differs from `current`, a fade starts: `previous = current`,
  `current = target`, `fade = AUDIO_PCM_STREAM_ITD_FADE_FRAMES` (32, about
  0.67 ms, as long as the largest delay). A target that changes during a
  fade waits until it ends, so the output stays continuous.
- Both ears read their own delay of `current` (the near ear reads the frame
  just pushed). During a fade, step `s` = 1..32, `t = s / 32`, and each ear
  is `old * (1 - t) + new * t` with `old` read at `previous`. Step 32 gives
  the new delay exactly.
- A line that has played nothing takes the target at once, without a fade:
  a stream that is placed before it plays, and every voice START, start at
  their delay as before. Open and START reset the line.

## Tests (TDD, `test_audio_extended`)
- Streams: turning the delay on after 10 frames crossfades over 32 frames,
  checked frame by frame against the formula, then exact. A move to the
  other side in the middle of a fade waits: the first fade finishes, then
  a 31 -> -31 fade runs.
- The existing history tests (stream and event) now expect the crossfade
  after a change and the exact delay once it ends.
- Placing a stream or starting a voice at the side still delays from the
  first frame, with no fade.

## Not done
HRTF, elevation cues.

## Result
- `ItdLine` (`line`, `written`, `current`, `previous`, `fade`, `primed`) is
  shared by streams and voices; `itd_line_push` became `itd_line_process`,
  which resolves both ears and fades each ear on its own. A change while a
  fade runs is deferred to the next frame after it ends.
- `test_audio_extended` grows by 2 (107 total): a change during a fade waits
  (stereo stream, each ear its own channel), and the fade leaves the near
  ear bit-exact on `0.7f` (where `x * (1 - t) + x * t` rounds away from `x`).
  Both history tests now compare every frame against a reference model of
  the fade and check the exact delay after it.
- One existing test needed a 32-frame drain before comparing both ears of a
  flat voice: its earlier voice was still fading to no delay.
- 15 mutants of the new code (`/tmp/mut_itdx.py`): 14 died first, "same ear
  fades" survived because mixing an equal sample through the fade is nearly
  always exact; the `0.7f` test kills it. All 15 killed.
