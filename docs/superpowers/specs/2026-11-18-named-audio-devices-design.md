# Named Audio Devices Design

## Goal

core_app can open a named playback device and a named capture device instead of the defaults, and `AudioSystem` can switch its playback device by name while it runs. Sources, buses, the listener and the reference tap survive a switch. Recovery after a loss reopens the selected device, not the default.

## Scope

In scope:

- `audio.h`:
  - `u32 audio_system_list_devices(AudioBackend backend, AudioDeviceInfo *out, u32 capacity)`: playback devices, same contract as `audio_capture_list_devices` (DEFAULT the system's, NULL miniaudio's "NULL Playback Device", FAKE none; returns the total, writes up to capacity; 0 when the backend cannot be enumerated or `out` is NULL with capacity > 0).
  - `AudioResult audio_system_create_named(AudioBackend backend, const char *device_name, AudioSystem **out)`: like `audio_system_create_ex`, opening the named playback device. NULL or "" opens the default. REJECTED for a FAKE backend with a name or a name no device of the opened backend has; FAILED when the system does not open; INVALID for NULL `out` or an invalid backend. `*out` is written only on success.
  - `AudioResult audio_system_switch_device(AudioSystem *as, const char *device_name)`: opens the named (NULL/"": default) device stopped, and only then closes the old one, installs the new one and starts it. REJECTED for an unknown name or a FAKE system with a name, FAILED when the new device does not open (the old device keeps playing) or does not start (the system is then lost). OK selects the name for later reopens and counts one in `audio_system_recoveries`, so a reader of the reference tap realigns. Owner thread, like `audio_system_reopen`.
  - `bool audio_system_selected_device(const AudioSystem *as, char *out, usize capacity)`: the selected name, false and "" for the default.
  - `audio_system_reopen` opens the selected device. When no device has that name any more it opens the default instead, and the selection is kept so a later reopen returns to the named device once it is back.
- The two devices never run at once: the new device is initialised stopped (miniaudio does not start a device in `ma_device_init`), the old one is uninitialised (which waits for its last callback), then the engine's device pointer is swapped and the new device started. The new device is allocated with the engine's allocation callbacks, because `ma_engine_uninit` frees `pDevice` with them.
- `core_app`:
  - CLI `--audio-device NAME` (requires `--audio=device`) and `--voice-capture-device NAME` (requires `--voice=device`).
  - `CoreAppConfig.audio_device_name` and `voice_capture_device_name`; `CoreAppVoiceConfig.capture_device_name` (borrowed for the voice's lifetime). Capture recovery reopens the named input; a REJECTED reopen (the device is gone) counts as a refused reopen.
  - `core_app_audio_start_device_named(audio, trace, require_device, asset_root, backend, device_name)`; the existing start functions call it with NULL.
  - A name no device has is a configuration error: the trace gets `event=audio mode=device result=rejected reason=device_name` or `event=voice mode=device result=rejected reason=device_name`, and the run fails (exit 2, not 77).

Out of scope: switching devices from a running core_app (no command or UI drives `audio_system_switch_device` yet), matching names by prefix or case, drift between playback and capture devices.

## Testing

`test_audio` (NULL backend):

1. `audio_system_list_devices` reports "NULL Playback Device", NULL/0 sizes, FAKE 0, invalid backend 0, NULL out with capacity 0.
2. `audio_system_create_named` with the null device's name opens it; an unknown name is REJECTED and leaves `*out` untouched; FAKE with a name is REJECTED; "" and NULL open the default.
3. `audio_system_switch_device` to the null device: OK, recoveries 1, selected name reported, the reference tap receives frames afterwards, a source started before the switch is still active.
4. Unknown name: REJECTED, nothing changes (recoveries 0, not lost, selected empty).
5. After a selection, a simulated loss and `audio_system_reopen` keeps the selection.

`test_audio_capture` already covers named capture.

`test_core_app_voice`: a NULL capture with `capture_device_name = "NULL Capture Device"` creates; an unknown name returns REJECTED.

`test_core_app_runtime`: `core_app_audio_start_device_named` on NULL with an unknown name returns REJECTED and writes the rejected trace line.

cmake contracts: `core_app --audio=device --audio-device "no such output"` exits 2 with the rejected line; `--audio-device` without `--audio=device` and `--voice-capture-device` without `--voice=device` are CLI errors; on a host with a real device, `--audio-device` with the default device's listed name reaches `result=ready` with that device (skipped without a device).

Mutations: switch that uninitialises the old device before the new one opens (the FAILED-keeps-playing test must fail), reopen that ignores the selection, voice recovery that ignores the capture name.

## Revisions

- `CoreAppVoiceConfig.capture_device_name` is copied into the voice (`char[128]`) at create instead of being borrowed, so callers may pass a temporary. A name of 128 bytes or more is REJECTED before anything opens.
- Voice capture recovery reopens the named input; when that reopen is REJECTED (the name is gone) it retries the default input in the same attempt instead of counting a refusal, so a removed headset falls back to the system input.
- `--voice-capture-device` conflicts with `--voice-null-capture` (CLI error, exit 2).
- The cmake contract `test_core_app_named_device` checks the unknown capture name only on a host with a playback device, because voice needs the playback device before it looks up the capture.
- `audio_system_switch_device` closes a replacement that does not start, restores the previous selection and reopens the previous device (named or default) in the same block: a refused switch changes neither the selection nor playback and counts no recovery. When the previous device does not open or start either, the block stays installed (zeroed, or opened and stopped) so a later `audio_system_reopen` repairs it; `engine->pDevice` never becomes NULL. A test hook (`AUDIO_SWITCH_START_TEST_HOOK`) refuses a counted number of starts in `test_audio`.
- `audio_system_create_named` and `audio_system_switch_device` both reject names of 128 bytes or more instead of truncating.
- `audio_reopen_device` looks the selection up only when the context is initialised.
- The rejected trace line is not best-effort: an unwritable trace returns FAILED rather than exit 2 without the reason.
- Known limit: with the NULL capture backend the default device has the same name as the named one, so a mutation that drops the name on recovery is not detectable there; the create-time name is covered.

## Result

- `test_audio` 47/47 (11 new), `test_core_app_voice` 14/14 (1 new), `test_core_app_runtime` 55/55 (2 new), new ctest `test_core_app_named_device`; each first RED (missing API or field).
- Mutations, all red: switch that closes the old device first (`a_refused_switch_keeps_the_old_device_playing`), reopen that ignores the selection (`reopen_keeps_the_selected_device`), voice create that ignores the capture name, core_app_audio that does not reject an unknown name, core_app voice that does not reject an unknown name (`test_core_app_named_device`).
- Real PulseAudio: the default device's listed name ("内置音频 模拟立体声") reopens by name and the ready line names the same device.
