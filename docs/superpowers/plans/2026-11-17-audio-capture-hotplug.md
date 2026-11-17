# Audio: capture device loss, rerouting and reopening (hot-plug)

Status: Done

## Goal

A USB headset can be unplugged or a Bluetooth microphone can drop while
capture runs. Today the capture silently stops delivering frames and the
caller cannot tell why or recover. Report device loss and rerouting, and
let the owner thread reopen the default or a named device without losing
frames already in the ring.

## API (`engine/src/audio/audio_capture.h`)

- `bool audio_capture_lost(const AudioCapture *)`: the device stopped
  without a stop request. Set by miniaudio's `stopped` notification outside
  a requested stop or destroy, or seen when the device state reads stopped
  while capture should run (some backends post no notification when an
  unplugged device fails to stop).
- `u64 audio_capture_reroutes(const AudioCapture *)`: how often the backend
  moved the stream to another device (`rerouted` notification).
- `audio_capture_running` is false while lost; `start` returns FAILED and
  `inject` REJECTED while lost.
- `AudioResult audio_capture_reopen(AudioCapture *, const char *name)`:
  opens the named device (NULL or empty: the default) in a second device
  slot, then closes the old one and restarts if capture was running. The
  ring and its frames are kept. REJECTED for an unknown name or a FAKE
  backend with a name; FAILED when the new device does not open. On any
  failure the old device and state are untouched. Clears the lost state.
- FAKE and NULL backends (tests): `audio_capture_simulate_event(capture, AudioCaptureEvent)`
  with `AUDIO_CAPTURE_EVENT_DEVICE_LOST` or `AUDIO_CAPTURE_EVENT_REROUTED`,
  through the same handler as the notification callback.
- New devices appearing: the caller polls `audio_capture_list_devices`.

## Tests (`test_audio_capture`)

1. FAKE loss: running false, inject REJECTED, start FAILED, earlier frames
   still readable; reopen with a name REJECTED; reopen OK resumes, frames
   stay in order; a stop after loss keeps capture stopped across reopen.
2. FAKE reroute: counted, capture keeps running, not lost; invalid events
   and NULL arguments.
3. Null device: requested stops, restarts and destroy never count as loss;
   reopen while running keeps delivering; an unknown name is REJECTED and
   the old device keeps running.

## Result

- `test_audio_capture`: 3 new tests (11 in total). RED on link, then GREEN.
- `start` sets `wanted` only after the device has started, so a device that
  is still starting never reads as lost.
- Mutations: the first round left 4 of 25 alive. Restoring the device name
  after a failed reopen and clearing `wanted` in destroy had no effect and
  were removed; `simulate_event` now also accepts the NULL backend so the
  device path of loss and reopen is tested. Final: 22 of 23 caught. The
  survivor is the device-state poll for backends that post no stop
  notification on unplug, which needs a real unplugged device.
- TSan, ASan+UBSan, `-Wshadow -Wdouble-promotion` clean;
  `test_audio_realtime_contract` passes.
- Not verified: a real USB or Bluetooth device being unplugged.
