# core_app physics delta corrections

Status: Done

## Goal

`ca1ad5cc` added delta correction packets ("PSND") to `physics_sync`, but
core_app still always sends full snapshots. Make the authority send a delta
when it knows the peer holds a baseline, and fall back to a full packet
otherwise.

## Baseline rule

The authority keeps, per connection, the snapshot it last sent in a
correction (full or delta) and its tick. The baseline is *confirmed* only
after that peer sends a MATCH report for a tick at or after the baseline
tick. A peer that applied the correction matches; a peer that dropped it
stays diverged and never confirms. Sending a new correction stores the new
target and clears the confirmation, so at most one delta can go to a peer
that lost its baseline before the next one is full again.

## API (physics_sync.h)

- `PhysicsSyncBaseline`: owned bytes, size, tick, `confirmed`.
- `physics_sync_baseline_init` / `_release`.
- `physics_sync_baseline_store(b, tick, snapshot, size)`: copies, clears
  confirmation; on allocation failure the baseline is emptied.
- `physics_sync_baseline_confirm(b, tick)`.
- `physics_sync_baseline_encode(b, tick, snapshot, size, buf, cap, out_size,
  out_delta)`: delta when confirmed and strictly smaller, else full PSNP.
- `physics_sync_correction_payload(data, size, &payload, &payload_size)`:
  validates a full packet and returns its snapshot; the transport uses it on
  the bytes core_app hands over.
- `physics_sync_apply_received(tracker, pw, b, data, size, out_tick)`:
  dispatches on magic, applies, and on success keeps the restored snapshot as
  the receiver's baseline. A delta target is bounded by the world capacity
  before allocating. Failure changes nothing, the baseline included.

## Transport

- Per-slot `PhysicsSyncBaseline`, released on close and destroy.
- MATCH report from a slot confirms its baseline.
- `net_physics_correction` encodes per slot, stores the baseline on
  `SEND_OK`. New stat `physics_delta_corrections_sent`.

## Tests

1. `test_physics_sync`: encode picks full before confirmation, full after a
   too-early confirm, delta after confirm; store clears confirmation; the
   receiver applies full then delta and rejects a delta against a baseline it
   does not hold without changing anything.
2. Loopback: peer A, after the first (full) correction, echoes a matching
   report at or after that tick, then a desync; it must get a delta smaller
   than the full packet and converge to the authority's reported hash.

## Result

- Baseline API and `physics_sync_apply_received` in `physics_sync`;
  `test_physics_sync` has 13 cases.
- Transport keeps a baseline per slot and sends deltas after confirmation;
  loopback asserts one delta (28 bytes vs 10644 full on this machine).
- The loopback client retries up to 3 rounds: a repeated desync from the
  earlier exchange can arrive after the first correction and trigger one
  more full packet against an unconfirmed baseline.
- Two equivalent mutations remain, documented in core_app_integration.md.
