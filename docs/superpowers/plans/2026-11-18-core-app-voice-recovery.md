# Core App Voice Capture Recovery Plan

Spec: `docs/superpowers/specs/2026-11-18-core-app-voice-recovery-design.md`.

## Tasks

- [x] 1. RED/GREEN: `test_audio_capture` for `AUDIO_CAPTURE_EVENT_REOPEN_REFUSED`; implement in `audio_capture.{h,c}`.
- [x] 2. RED: `test_core_app_voice` recovery tests 2–5 (spec numbering); they fail to compile or fail on the missing config/stats fields.
- [x] 3. GREEN: config fields, recovery in `core_app_voice_pump`, stats fields.
- [x] 4. core_app: device mode config, `result=stopped` fields; update `test_core_app_voice_device.cmake` regex.
- [x] 5. Mutations from the spec.
- [ ] 6. Independent review, fix findings.
- [x] 7. Docs (append only): `audio_extended.md`, `core_app_integration.md`, `Implementation_Status.md`, `missing_capabilities.md`.
- [ ] 8. Three trees, push, CI.
