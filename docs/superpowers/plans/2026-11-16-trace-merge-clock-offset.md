# trace_merge reads the clock offset from a server trace

Status: Done

## Context

The core_app server writes one `event=network_clock_offset` line per peer
(2026-11-16-clock-probe-initiator.md): `offset_us` is the peer clock minus
the server clock. `trace_merge` still needs the shift typed by hand with
`--offset-us`, which cannot express a negative offset for the second input.

## Design

- `core/trace_core_app.h`:
  `BreakTraceClockOffsetStatus break_trace_core_app_clock_offset(const char *text, usize size, i64 *offset_us, u64 *error_us)`.
  It scans lines with the same parser as the converter and looks at valid
  lines whose event is `network_clock_offset`.
  - OK: exactly one such line, with `offset_us` an optionally signed
    canonical decimal (no leading zero, no `-0`, at most 18 digits) and
    `error_us` a canonical decimal.
  - NOT_FOUND: no such line.
  - AMBIGUOUS: more than one (several peers; the caller must pick by hand).
  - MALFORMED: a matching line with a missing or non-canonical field.
  - INVALID: NULL outputs, or NULL text with non-zero size.
  Outputs are written only on OK.
- `trace_merge --clock-offset SERVER_TRACE`: needs exactly two inputs (1 is
  the server's JSON, 2 the peer's) and no `--offset-us`. The tool reads the
  text trace, calls the function, converts the offset with
  `clock_offset_merge_shifts`, and applies `a_shift` to input 1 and
  `b_shift` to input 2. It prints the offset and error bound. Failures exit
  1 with a message naming the status; misuse exits 2.

## Tests (RED first)

- `test_trace_core_app`: positive and negative offsets, ts_us on the line,
  not found, two lines, each malformed field form, invalid arguments, and
  outputs untouched on failure.
- `test_trace_merge_tool.cmake`: negative offset shifts input 2, positive
  shifts input 1, plus each failure exit code and message.

## Verification

Unit test plus tool contract, mutation run over the parser, the three full
build trees, compat contracts after a local commit, forbidden-word check.

## Result

- RED: the unit test failed to compile and the tool contract reported
  `unknown or malformed argument` for `--clock-offset`.
- GREEN: `test_trace_core_app` (10 tests), `test_trace_merge` and
  `test_trace_merge_tool` pass.
- Mutation run: 21 mutants. The first pass left two alive. `find key`
  (match keys by length only) survived because `offset_us` was the only
  9-character key; `cr strip` survived because `error_us` was not the last
  field, so the stray `\r` never reached a parsed number. The positive test
  line now has `peer_hint` and `bytes_us` before `offset_us` and ends with
  `error_us=56\r\n`. Both mutants are now killed, 21/21.
- Remaining gap: with several peers the server trace has several lines and
  the tool asks for `--offset-us`; the offset only comes from server-side
  probes.

