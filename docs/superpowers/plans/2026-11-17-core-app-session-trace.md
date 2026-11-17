# core_app session id on the authenticated trace line

Status: Done

## Goal

missing_capabilities section 13: the server writes
`network_session result=authenticated tick=N` without the session number,
while `network_clock_offset` lines carry `session=N`. Nothing in the server
trace ties a clock offset to the moment that session authenticated, so
picking `--session` for `trace_merge` still needs outside knowledge.

## Change

- `net_sync_sessions` writes
  `network_session result=authenticated session=S tick=N`.
- Driver (`test_core_app_network.cmake`, loopback): every authenticated line
  carries a canonical `session=`; the count equals `authenticated` from
  `network_stats`; session ids are distinct; the session in the single
  `network_clock_offset` line is one of them.

## Tests

RED: the driver assertions fail against the current line. GREEN after the
format change.

## Result

- Authenticated line carries `session=`; driver checks pass in loopback and
  late_auth (RED before the format change).
- Repeated loopback runs exposed two timing flakes in the test client
  (server clock probe count, delta baseline confirmation); both fixed, 15
  consecutive passes.
