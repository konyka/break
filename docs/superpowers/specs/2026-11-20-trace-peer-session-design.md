# Design: a peer trace that names its own session

`trace_merge --clock-offset` can align a server with several peers, but each
peer input needs `--session N` typed by hand
(`missing_capabilities.md`: "对端 trace 与会话号的对应仍需手动指定"). The
number is knowable: the server tells each peer its session in the welcome
message (`0x4005`), so a peer that traces at all can write it down, and the
tool can read it instead of being told.

## Change

Core (`src/core/trace_core_app.h`, `.c`, `test_trace_core_app`):

- `break_trace_core_app_session(text, size, out_session)`: reads the session
  a peer trace recorded as
  `COREAPPTRACE version=1 event=network_session_welcome session=N`, with the
  same canonical-decimal rules as the clock-offset reader. NOT_FOUND when no
  such line exists, AMBIGUOUS when several disagree (several lines with the
  *same* session are fine: a peer may reconnect and re-trace it),
  MALFORMED when a matching line lacks a canonical `session`.
- It reuses the existing line scanner, so only lines the converter accepts
  are considered.

Tool (`tools/trace_merge.c`, `test_trace_merge_tool.cmake`):

- With `--clock-offset` and no `--session` for an input, the tool reads that
  input's own session from its text before falling back to the single-peer
  path. An explicit `--session N` still wins, so existing command lines keep
  working.
- A peer whose trace names no session, with more than two inputs, is a usage
  error naming the input, as before.

Peer side (`tests/test_core_app_net_client.c`):

- The loopback peer already decodes the welcome; it now also writes the
  trace line when a `--trace PATH` argument is given, which is what makes
  the tool's new path exercisable end to end.

## Tests

- `test_trace_core_app`: a peer trace with one welcome line reports its
  session; repeated identical lines are fine; two different sessions are
  AMBIGUOUS; a line with no session or a non-canonical one is MALFORMED; no
  line is NOT_FOUND; NULL arguments are INVALID.
- `test_trace_merge_tool.cmake`: a server trace with two peer sessions plus
  two peer traces that name their own sessions merges without any
  `--session` argument, and the result's events are shifted the same way the
  explicit form shifts them.

## Out of scope

The peer learning its offset (that stays the server's measurement), a peer
trace written by a release binary (only the test client traces), merging
without `--clock-offset`.

## Result

Delivered, with one correction to the design and one part dropped.

**The tool reads JSON, not trace text.** The spec had the tool call the text
reader on the peer input. `trace_merge`'s inputs are already-converted Chrome
trace-event documents, so the welcome line arrives as
`{"name":"network_session_welcome",...,"args":{"session":N,...}}`. The slice
therefore ships two readers: `break_trace_core_app_session` for trace text
(useful to anything reading a raw trace) and
`break_trace_core_app_session_from_chrome` for the converted form, which is
what the tool uses. Both have the same statuses and the same
canonical-decimal rules.

**The peer-side trace line was dropped from this slice.** Having the loopback
test client write the line needs a `--trace` argument and a trace file it
does not have today; the tool-side behaviour is testable without it (the
cmake case writes the converted document directly, in the exact shape the
converter produces, which the core case pins against the real converter).
Wiring the test client is a separate slice and `missing_capabilities.md` says
so.

`test_trace_core_app` 15/15 and the `test_trace_merge_tool` script pass. Six
mutations each fail a test: the AMBIGUOUS check firing on a repeated
identical session, the event name compared with the wrong length, the session
field left unparsed, the output written before the NOT_FOUND return, the
tool's own-session lookup disabled, and the tool recording session 0 instead
of what it read.

One existing expectation changed: `--clock-offset` with three inputs used to
be a usage error ("needs exactly two inputs or --session per peer"). It is
now allowed, because the peers may name themselves; the usage error narrows
to a single input, and a peer that names nothing fails at the clock lookup
with the server trace named. The cmake case covers both.
