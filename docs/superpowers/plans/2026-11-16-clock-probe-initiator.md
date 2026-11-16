# Server-initiated clock probes in the core_app transport

Status: Done

## Context

The server answers clock probes (2026-11-16-clock-probe-responder.md), so
a peer can estimate the offset. The server itself still has no estimate,
so its trace cannot be aligned with a peer trace. This slice makes the
server probe each authenticated peer and trace the result.

## Design

- Per connection slot: a `ClockOffsetEstimator`, the t0 of the one
  outstanding request, the time it was sent, the time the next probe is
  due, and whether the offset was traced. Everything is reset when a slot
  is added or closed.
- `net_send_pending` (only while producing and the event queue is empty)
  sends a request to every sendable slot with no outstanding request once
  `CORE_APP_NET_CLOCK_PROBE_INTERVAL_TICKS` (8) ticks have passed since the
  last one. t0 is `time_microseconds()` just before the send. A request
  with no reply after `CORE_APP_NET_CLOCK_PROBE_TIMEOUT_TICKS` (32) ticks is
  dropped and counted in `clock_probes_lost`. A tick counter that went
  backwards (new level) counts as elapsed. (First drafted with wall-clock
  200 ms / 1 s; a headless run advances 1500 ticks in about 0.1 s, so only
  2 probes went out. Ticks make the schedule independent of run speed.)
- The 0x4004 handler takes t3 on entry. A REPLY whose t0 matches the
  outstanding request becomes a sample (`clock_replies_matched`); any other
  REPLY is counted in `clock_replies_unmatched` and fails the handler.
  Requests are still answered as before.
- When a slot's estimator first holds
  `CORE_APP_NET_CLOCK_OFFSET_TRACE_SAMPLES` (4) samples, the transport
  writes `COREAPPTRACE version=1 event=network_clock_offset session=<id>
  offset_us=<B minus server> error_us=<bound> samples=4`. The driver drops
  `event=network*` lines before comparing with the offline trace.
- `network_stats` gains `clock_probes_sent`, `clock_replies_matched`,
  `clock_replies_unmatched`, `clock_probes_lost`.

## Tests (RED first)

- `test_core_app_net_client` peer A, after its own probe exchange,
  answers 6 server requests (t1 on receipt, t2 just before the send).
- `test_core_app_network.cmake`:
  - `clock_probes_sent >= 4`, `clock_replies_matched >= 4`,
    `clock_replies_unmatched >= 1` (the forged REPLY from A), and
    `clock_probe_decode_failed >= 2`;
  - the trace has exactly one `event=network_clock_offset` line for A, and
    `|offset_us| <= error_us` (both ends read CLOCK_MONOTONIC on one host).

## Verification

Loopback ctest, mutation run over the new paths, the three full build
trees, compat contracts after a local commit, forbidden-word check.

## Result

- Implemented with tick-based scheduling (see Design). The loopback peer
  answers server requests inside `client_recv`, so no helper that skips
  other ids can drop one. It leaves one request unanswered (server must
  count `clock_probes_lost >= 1`), and before its first real reply it
  sends one with a far-future t0, then repeats the real reply; both must
  be counted as unmatched and `clock_samples_rejected` must stay 0.
- One local run: `event=network_clock_offset session=1 offset_us=0
  error_us=74 samples=4`, `clock_probes_sent=10 clock_replies_matched=7
  clock_replies_unmatched=3 clock_probes_lost=2`.
- Mutation run (ctest loopback per mutant): 18 mutants. One survivor:
  removing `outstanding = false` in the timeout branch. The next send
  overwrites `outstanding` anyway, so the two differ only when that send
  fails (overload or closed), which the loopback cannot force; the line
  stays so a failed send does not count the same loss every tick.
