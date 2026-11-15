# core_app physics sync reports over the authenticated transport

## Goal
core_app (the authority) tells authenticated peers its physics state hash
every tick and checks hashes that peers report back, so a desync is visible in
the trace. Builds on `physics_sync` and the 0x4002 registry entry.

## Design
- `CoreAppNetworkHooks.tick` gains `u64 physics_hash`; `app_network_publish`
  passes `physics_state_hash(level->physics)`.
- Transport keeps a `PhysicsSyncTracker`. Each producing tick it records
  `(tick, hash)`; if the record is refused (tick not increasing) it reinits
  the tracker and records again. The latest report is sent once to every
  sendable slot, after the snapshot outbox, under the same
  "event queue empty" rule.
- Handler for `BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT`: decode with
  `physics_sync_decode_report`; failure counts `physics_decode_failed` and
  returns false. Otherwise `physics_sync_check` counts
  `physics_matched` / `physics_desynced` / `physics_unknown`. The first desync
  traces `event=network_physics_sync result=desync tick=N` once (the `event=network` prefix keeps it out of the offline trace comparison).
- Peer reports never change the world; the transport still has no level
  pointer. Sending corrections is out of scope.
- `network_stats` gains `physics_reports_sent physics_matched
  physics_desynced physics_unknown physics_decode_failed`.

## Tests (Snowflake tree, `test_core_app_network_loopback`)
- Client A, after its first snapshot, reads the next 0x4002 report
  (hand-decoded, independent of `physics_sync.c`), echoes it unchanged, then
  sends it with the hash flipped, then sends a 15-byte payload.
- Unauthenticated peer B must receive neither snapshots nor reports.
- Driver expects `physics_reports_sent>=2 physics_matched>=1
  physics_desynced>=1 physics_decode_failed>=1`, the desync trace line, and
  still an identical simulation trace vs offline.
- `test_core_app_net_transport` keeps building (adds `physics_sync.c`).

## Status
- Done. RED: `a_received_physics_report` failed in `test_core_app_network_loopback`.
  GREEN: loopback passes; `build-core-app-net` full ctest 414/414.
- Mutation: 9/9 killed after adding a repeated desync send
  (`physics_desynced>=2`), which caught "trace every desync".
- Not done: sending a 0x4003 correction after a desync.
