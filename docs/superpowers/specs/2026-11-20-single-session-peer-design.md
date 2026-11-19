# Design: a single-session peer, and the merge chain closed

The previous slice had the loopback peer write its own trace, but that one
process opens several connections, so its document names several sessions —
which `trace_merge`'s self-naming path rightly refuses. The chain
"peer records its session → trace_merge reads it → both traces on one
timeline" therefore stayed untested end to end.

## Change

`tests/test_core_app_net_client.c`:

- A `single` scenario: open once, authenticate, take one snapshot, answer
  the server's clock probes until it has enough samples to trace an offset,
  then close. With `--trace` this produces a document naming exactly one
  session.
- It reuses `client_answer_server_probes`, so the probe handling is the
  suite's existing one rather than a second copy.

`tools/trace_convert.c` (new):

- `trace_convert IN.trace OUT.json` writes the Chrome trace-event document
  `break_trace_core_app_to_chrome` produces. The repository had no way to
  produce one outside a test fixture, which is why the previous slice could
  only hand-write the JSON.

`tools/trace_merge.c`:

- The self-naming lookup now runs for a single peer too. It used to be
  gated on more than two inputs, which meant a two-input merge fell back to
  "the server's only clock line" even when the peer named itself and the
  line carried a `session=`.

`CMakeLists.txt`, `tests/test_core_app_network.cmake`:

- A `test_core_app_network_single_session` test runs the `single` peer, then
  converts both traces and merges them with `--clock-offset` and no
  `--session`, asserting the tool reported reading the peer's session, found
  that session's offset, and kept both inputs.
- The loopback-only statistics assertions are skipped for this mode, which
  checks `authenticated == 1` instead.

## Tests

The new CMake test is the test: it fails if the peer names more than one
session, if the merge needs `--session`, if the tool does not report reading
the peer's own session, or if the merge drops an input.

## Out of scope

A release client binary, the peer measuring its own offset, merging more
than one peer document in this test.

## Result

Delivered as designed. `test_core_app_network_single_session` passes (23 s,
real TLS + AUTH-v2), and `test_core_app_network_loopback` and
`_late_auth` stay green.

Two things the work turned up:

- **The self-naming lookup was gated wrongly.** It ran only with more than
  two inputs, on the assumption that two inputs are always the single-peer
  case. They are not: a two-input merge whose server trace carries
  `session=` on its only clock line used to take the session-less path,
  which works but reports no session. Removing the gate makes the two-input
  case read the peer's name as well, which is what the new test checks.
  Disabling the lookup fails that test.
- **The probe wait needed the suite's own helper.** A first version polled
  `client_read_burst` in a sleep loop and answered one probe, so the server
  never reached the four accepted samples it needs before tracing an offset,
  and the merge had nothing to align. `client_answer_server_probes(&s, 4, 4,
  20000)` is what the other scenarios already use.
