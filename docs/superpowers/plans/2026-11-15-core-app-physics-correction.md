# core_app physics correction after a reported desync

## Goal
When an authenticated peer reports a physics hash that differs from the
authority, core_app sends that peer a `physics_sync` correction (0x4003): a
full physics snapshot it can restore with `physics_sync_apply_correction`.

## Design
- The transport still has no level pointer. Two optional hooks join
  `CoreAppNetworkHooks`:
  - `bool (*physics_correction_wanted)(void *user)`: true while at least one
    sendable slot is waiting for a correction.
  - `void (*physics_correction)(void *user, u32 tick, const u8 *data, usize size)`:
    hands over the encoded correction bytes, borrowed for the call.
- `app_network_publish`, after `tick`, asks `physics_correction_wanted`; when
  true it allocates `physics_sync_correction_size(level->physics)` bytes,
  calls `physics_sync_encode_correction(level->physics, tick, ...)`, passes the
  bytes, frees them. Corrections larger than `BREAK_NET_MAX_PAYLOAD_SIZE` are
  not sent.
- Transport: a DESYNC from connection K marks K's slot `correction_pending`.
  `physics_correction` sends the bytes as 0x4003 v1 to every pending,
  sendable slot and clears the flag; several desync reports before the next
  tick collapse into one correction. New counter
  `physics_corrections_sent` at the end of `network_stats`.
- Encoding uses `physics_snapshot_save`, which marks the BVH dirty. The
  loopback driver's offline trace comparison shows whether that changes the
  simulation.

## Tests (`build-core-app-net`, `test_core_app_network_loopback`)
- Client A, after its desync reports, waits for a 0x4003 envelope and checks
  by hand: magic `PSNP`, payload length field == size - 16, FNV-1a 32 of the
  payload matches. Reports `physics_correction tick=N bytes=M`.
- Client frame capacity grows to header + 64 KiB.
- Driver: `physics_corrections_sent>=1`, report line present, offline trace
  still identical.

## Status
- Done. RED: `a_received_physics_correction` failed. GREEN: loopback passes.
- Added peer A2 (authenticated, never desyncs) so per-slot targeting and
  clearing the pending flag are observable; driver now expects
  `authenticated==3` and `physics_corrections_sent <= physics_desynced`.
- Mutation: 8/8 killed ("no pending mark" fails to compile; "wanted always
  false" covers the same behavior at runtime).
- Not done: a receiving runtime that applies the correction.
