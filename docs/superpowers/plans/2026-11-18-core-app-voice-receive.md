# Core App Voice Receive Plan

Spec: `docs/superpowers/specs/2026-11-18-core-app-voice-receive-design.md`.

## Tasks

- [x] 1. Characterization: `test_break_online_voice` `voice_pop_at_max_time_flushes_buffered_frames_in_order`.
- [x] 2. RED: client `voice` scenario sends 20 tone frames, a duplicate and a wrong-rate frame; driver MODE=voice expects the five new counters. Fails: the counters are missing.
- [x] 3. GREEN: `net_on_voice`, per-slot receivers, pop in `net_tick`, tail flush on release and destroy, the five counters.
- [x] 4. Mutations: no handler registration; no tail flush; peak not updated. Each must fail task 2.
- [x] 5. Independent review, fix findings.
- [x] 6. Docs: `core_app_integration.md`, `session_protocol.md`, `audio_extended.md`, `Implementation_Status.md`, `missing_capabilities.md` (append only).
- [ ] 7. Three trees, push, CI.

## Review (agent-313, Ready)

No Critical or Important findings. Minor findings handled:

- Spec said the handler requires `net_slot_live`; the code checks "exists and not closing" on purpose (AUTH and voice in one pump batch). Spec corrected.
- Frames the capped tail flush cannot reach were lost from the totals; they now count as dropped (`accepted - played`).
- An empty 0x4006 payload was a `handler_failed`; it now counts as dropped and the handler returns true.
- The tail-flush mutation depended on timing; the client now closes right after the clock-probe reply. The three mutations were re-run after the fixes and all fail the test.
- Comments note the 160 ms tick limit of the per-tick pop cap and that release must run on the owner thread.
- The `session_protocol.md` sentence moved to its own paragraph instead of inside an existing one.
