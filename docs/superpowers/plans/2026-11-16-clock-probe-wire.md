# Clock probe wire format

Status: Done

## Context

`core/clock_offset` estimates the clock offset between two peers from
NTP-style samples (2026-11-16-clock-offset-estimator.md), but no message
carries the timestamps between core_app peers. This slice defines that
message and its codec. Sending and answering probes in the transport is the
next slice.

## Design

- Message id `BREAK_NET_MESSAGE_ID_CLOCK_PROBE` = `0x4004` in
  `network/break_net_message_registry.h`, protocol version 1, payload
  exactly 32 bytes, AUTHENTICATED phase only, duplicates idempotent (like
  the other core_app messages). The default registry grows by one entry.
- Payload, little-endian (`core_app_network.h`):
  - `[0]  u32 magic "CLKP"` (`0x504b4c43`)
  - `[4]  u8 kind`: 1 = request, 2 = reply
  - `[5]  u8 reserved`, `[6] u16 reserved`: must be 0
  - `[8]  u64 t0`: requester send time (the reply echoes it)
  - `[16] u64 t1`: responder receive time (0 in a request)
  - `[24] u64 t2`: responder send time (0 in a request)
- The requester takes `t3` from its own clock on receipt, so `t3` never
  travels.
- `core_app_clock_probe_encode` / `_decode` reuse `CoreAppSnapshotOutcome`:
  a wrong size is `TRUNCATED` (short) or `OVER_LIMIT` (long), a wrong magic
  is `BAD_MAGIC`, an unknown kind is `BAD_VERSION`, and non-zero reserved
  bytes or a request carrying `t1`/`t2` are `INVALID`. Encode refuses the
  same invalid values and leaves the buffer untouched on failure.
- `core_app_clock_probe_answer(request, t1, t2, &reply)`: builds the reply
  for a decoded request. `INVALID` when the input is not a request or
  `t2 < t1`.
- A decoded reply is only diagnostic data. It feeds `clock_offset_add`,
  which rejects impossible samples, and it never changes the simulation.

## Tests (written first)

1. test_core_app_network: request and reply round-trip byte for byte
   (golden bytes); every rejection rule; answer rules; a full exchange
   decoded into a `ClockOffsetSample` gives the expected offset.
2. test_break_session: the registry has `0x4004` with limit 32,
   AUTHENTICATED, version 1; the count grows by one.

## Verification

Both tests, mutation run, three full build trees, banned-word check,
commit and push.

## Result

- Implemented as designed; `test_core_app_network` 16/16 and
  `test_break_session` 43/43 pass.
- Mutation run: 37 mutants, one survivor on the first pass (dropping the
  reserved u16 write went unnoticed because the encode buffer happened to
  be zero). The golden test now prefills the buffer with 0xa5; all mutants
  are killed.
