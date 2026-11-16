# Clock probe responder in the core_app transport

Status: Done

## Context

The clock probe message `0x4004` and its codec exist
(2026-11-16-clock-probe-wire.md), but the core_app server ignores it. This
slice makes the server answer probes so a peer can estimate the clock
offset between the two machines. Sending probes from the server side and
feeding the result to `trace_merge` are later slices.

## Design

- `core_app_net_transport.c` registers a handler for
  `CORE_APP_CLOCK_PROBE_MESSAGE_ID`. The registry already limits it to the
  AUTHENTICATED phase and exactly 32 bytes.
- The handler takes `t1 = time_microseconds()` first, decodes the payload
  and accepts only a REQUEST. Anything else increments
  `clock_probe_decode_failed` and returns false (counted by the session
  layer as a handler failure; the session stays open).
- An accepted request is stored per connection slot (latest request wins).
  `net_send_pending` answers it with `t2 = time_microseconds()` just before
  the send, so the hold time `t2 - t1` covers the wait for the next tick.
  A slot that is no longer sendable drops its pending answer; a closed slot
  clears it.
- `network_stats` gains `clock_probes_answered` and
  `clock_probe_decode_failed`.

## Tests (RED first)

- `test_core_app_net_client` peer A, after the physics exchange:
  - sends a 31-byte probe and a request whose t1 is non-zero (both must be
    rejected without a reply);
  - sends 4 requests, waits for each reply, checks kind, echoed t0 and
    `t2 >= t1`, feeds `ClockOffsetEstimator` with its receive time t3;
  - checks that the estimated offset is within `error_us` of 0 (both ends
    use CLOCK_MONOTONIC on the same machine) and reports
    `clock_offset offset_us=… error_us=… samples=…`.
- `test_core_app_network.cmake` requires `clock_probes_answered >= 4`,
  `clock_probe_decode_failed >= 2` and the client report line.

## Verification

Loopback ctest, mutation run over the handler and send path, ASan, the
three full build trees, forbidden-word check.

## Result

- Implemented as designed. The loopback peer also sends a REPLY to the
  server, which must be rejected (`clock_probe_decode_failed >= 3`), and
  fails if any of the malformed probes (t0 11..13) is answered. The driver
  requires `clock_probes_answered == 4` exactly.
- One local run: `offset_us=8 error_us=71 samples=4`.
- Mutation run (ctest loopback per mutant): 12 mutants, 2 survivors on the
  first pass ("pending never cleared", "decode result ignored"). The exact
  answer count kills the first. The second is left as equivalent: when
  decode fails, `probe` is never written, and its uninitialized kind is not
  REQUEST in practice, so no test can catch it deterministically.
