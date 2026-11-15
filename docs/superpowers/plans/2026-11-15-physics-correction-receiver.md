# Receiver applies the physics correction in the loopback test

## Goal
core_app sends a `0x4003` physics correction to the peer that reported a
desync, but nothing on the receiving side restores it. The loopback client
only checks the header and checksum by hand. Show that a receiver can apply
the correction with `physics_sync_apply_correction` and end up with the
authority's state for that tick.

## Design
- `test_core_app_net_client` remembers the tick and hash of the latest
  `0x4002` report it sees while waiting for the correction. The server sends
  the report for tick N before the correction for tick N, so the matching
  report is always seen first.
- After the hand-decoded checks pass, the client restores the payload into
  its own `physics_world_create(32)` world (the same capacity core_app uses)
  with `physics_sync_apply_correction`, then compares
  `physics_state_hash` with the reported hash for tick N.
- The client writes `physics_correction_applied tick=N converged=0|1` to its
  report and records the check `a_applied_physics_correction`.
- The client target links `physics_sync.c physics.c bvh.c math.c log.c`, the
  same list `test_core_app_net_transport` uses.

## Tests
- `test_core_app_network.cmake` requires
  `physics_correction_applied tick=<N> converged=1` where N is the tick in the
  `physics_correction` line. RED before the client change.

## Docs
- Status here, `docs/Implementation_Status.md`,
  `docs/cross_engine/missing_capabilities.md` section 9.

## Status
- Done. `test_core_app_network_loopback` RED (driver: "the client did not
  restore the correction to the reported state"), then GREEN: the client
  restores the tick 21 correction (10644 bytes) and reproduces the hash the
  authority reported for tick 21.
- Mutations (4): core_app encodes the correction with `tick + 1`; client
  hash comparison inverted; report never marked as seen; report tick off by
  one. All killed.
- Still missing: core_app itself only runs as the authority, so no runtime
  client applies corrections in a live session yet; delta corrections;
  parallel solver; cross-platform determinism.
