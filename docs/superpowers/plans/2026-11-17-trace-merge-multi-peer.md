# trace_merge: clock offsets for several peers (2026-11-17)

Status: Done

## Goal
A core_app server traces one `event=network_clock_offset session=N ...`
line per peer. `trace_merge --clock-offset` reads only a trace with a single
such line, so merging a server with two or more peers still needs manual
`--offset-us`. This slice picks each peer's line by its session.

## Design
- `break_trace_core_app_clock_offset_for_session(text, size, session,
  &offset_us, &error_us)` in `core/trace_core_app`: like the single-line
  reader, but only lines whose `session` is the canonical decimal `session`
  count. A clock line without a canonical `session` is MALFORMED; two lines
  for the session are AMBIGUOUS; none is NOT_FOUND.
- `clock_offset_merge_shifts_many(offsets, count, &server_shift,
  peer_shifts)` in `core/clock_offset`: with offset_i = peer_i minus server,
  base = max(0, max offset_i), the server shifts by base and peer i by
  base - offset_i. All shifts are non-negative and put every input on the
  server's timeline moved by base. One peer gives the same shifts as
  `clock_offset_merge_shifts`.
- `trace_merge`: `--session N` applies to the next input, which is a peer.
  With `--clock-offset`, either no input has `--session` (exactly two
  inputs, as before) or every input after the first has one and the first
  has none. `--session` without `--clock-offset` is a usage error.

## Tests (RED first)
- `test_trace_core_app`: session selection among three peers, the session
  absent, repeated, missing or non-canonical on a clock line, invalid
  arguments, outputs untouched on failure.
- `test_clock_offset`: shifts for mixed signs, all negative, one peer equal
  to the two-input helper, extremes (INT64_MIN and INT64_MAX together).
- `test_trace_merge_tool.cmake`: a server and two peers merged on one
  timeline; each new usage error and the per-session failure messages.

## Verification
Unit tests plus tool contract, mutation run over the new code, the three
full build trees, compat contracts, forbidden-word check.

## Result
- RED: `test_clock_offset` failed to compile (`clock_offset_merge_shifts_many`
  undeclared) and the tool contract reported `unknown or malformed argument`
  for `--session`.
- GREEN: `test_clock_offset` (8), `test_trace_core_app` (12),
  `test_trace_merge`, `test_trace_merge_tool` pass. The dangling-option
  message now names `--session`; its contract was updated.
- Mutation run (`/tmp/mut_tmp.py`): 24 mutants over the shift helper, the
  session parser and the tool. "session digit" (no lower-bound digit check)
  survived; a `session=/` case now kills it. 24/24.
- Remaining gap: offsets come only from server-side probes, and core_app
  does not print which session belongs to which peer process, so the user
  maps sessions to peer traces by hand.
