# Design: the loopback peer writes its own trace

`trace_merge` now reads a peer's session from the peer's own document
(`2026-11-20-trace-peer-session-design.md`), but nothing in the repository
produces such a document: the loopback test client decodes the welcome and
then drops it. That leaves the new path covered only by a hand-written
fixture, and leaves the merge chain untested end to end.

## Change

`tests/test_core_app_net_client.c`:

- A fourth argument `--trace PATH` (after the optional scenario name) opens
  that file and writes trace lines through `break_trace_core_app_fprintf`,
  the same writer core_app uses, so the stamping behaviour is identical.
- When the welcome is decoded, the client writes
  `COREAPPTRACE version=1 event=network_session_welcome session=N` once per
  accepted welcome. A rejected welcome (`bad_welcomes`) writes nothing, since
  there is no session to name.
- With `--trace`, the client also sets the trace clock
  (`break_trace_core_app_set_clock`) to its own microsecond clock, so the
  line carries `ts_us` exactly as a core_app peer's would.
- Without `--trace` the client behaves byte for byte as before: no file, no
  clock, no lines.
- The report file gains `client trace_lines=N`, so the CMake driver can see
  the line was written without parsing the trace.

`CMakeLists.txt` and the network driver:

- The loopback driver passes `--trace` for the peer and, after the run,
  merges the server trace with the converted peer document using
  `trace_merge --clock-offset` and *no* `--session`, which is the end-to-end
  check the previous slice could not make.

## Tests

- `test_core_app_net_client` is itself a test binary driven by CMake; the new
  behaviour is checked by the driver: the peer trace exists, contains one
  `event=network_session_welcome` line with a `session=` that matches the
  server's `network_session` line, and `trace_merge` with no `--session`
  aligns the two.
- The existing report assertions keep working, so a client run without
  `--trace` is unchanged.

## Out of scope

Tracing anything else from the peer (snapshots, voice), a release client
binary, the peer measuring its own clock offset.

## Result

Delivered, and the end-to-end merge the spec asked for turned out not to
apply.

The client writes its trace and the loopback driver checks it: the file
exists, its first line is stamped `ts_us=` like core_app's, every session it
names was authenticated by the server, and the number of names equals the
number of the server's authenticated lines. `client trace_lines=N` in the
report says the same without parsing the trace. Two mutations fail the
loopback test: the traced session off by one, and
`break_trace_core_app_set_clock` not called.

**The merge step was dropped, for a real reason.** This one client process
opens several connections in sequence (authenticated, unauthenticated,
unknown-id, wrong-PSK, deadline, alive-at-end), so it is welcomed into
several sessions and its trace names all three the server authenticated.
`trace_merge`'s self-naming path deliberately treats a document naming two
different sessions as AMBIGUOUS — one document is one peer timeline — so
feeding this trace to it would be wrong, not a bug to work around. The
driver therefore checks the correspondence directly (names ⊆ authenticated
sessions, and equal counts), which is the stronger statement anyway.

A peer that merges would be a single-session process, which this repository
does not have; `missing_capabilities.md` records that as what is still
missing rather than claiming the chain is closed.
