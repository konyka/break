# Physics desync detection

## Goal

Give peers a way to detect that their physics worlds diverged, using the
existing `physics_state_hash`. This is the smallest network-sync slice: it
does not move state between peers, it only reports the first tick where the
hashes differ.

## Design

New pure module `engine/src/physics/physics_sync.{h,c}`, no network or
allocation dependency.

- Report wire format, little-endian, 16 bytes: magic `PSYN` (u32
  0x4e595350), tick u32, hash u64. Decode requires the exact length and magic.
- `PhysicsSyncTracker` keeps the last `PHYSICS_SYNC_HISTORY` (64) local
  `(tick, hash)` pairs in a ring. `physics_sync_record` requires strictly
  increasing ticks and rejects the rest.
- `physics_sync_check(tracker, tick, remote_hash)` returns
  `PHYSICS_SYNC_MATCH`, `PHYSICS_SYNC_DESYNC` or `PHYSICS_SYNC_UNKNOWN`
  (tick not in the local window). The first desync tick is latched and kept
  until `physics_sync_init` runs again; a later desync at an earlier tick
  lowers it.

## Tests (`test_physics_sync`)

1. Report encode/decode round trip; wrong magic, short and long buffers and a
   too-small encode buffer are rejected.
2. Two identical worlds stepped in lockstep always match.
3. A one-off impulse on one world produces DESYNC at that tick, and the
   latched first-desync tick stays there for later checks.
4. Ticks older than the window and future ticks give UNKNOWN; non-increasing
   record calls are rejected.

## Verification

RED (missing module), GREEN, mutation run over `physics_sync.c`, full ctest
on `build-core-app-master`.

## Status

Done. `test_physics_sync` 4/4. Mutation run over `physics_sync.c`: 26 of 26
killed. While simplifying the tracker, a new RED case showed that an
unwritten ring slot (tick 0, hash 0) matched a report for tick 0; each slot
now has a `valid` flag.
