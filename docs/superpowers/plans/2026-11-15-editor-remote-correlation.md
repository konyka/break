# Editor remote: echo the request correlation ID

Follow-up to `2026-11-15-net-message-correlation.md`. The adapter now hands
received messages their envelope correlation ID and can send one. The editor
remote host (`engine/apps/editor/editor_remote.c`) still answers every
request with ID 0, so a client cannot match a response to its request.

## Approach

- `BreakEditorRemote` keeps `u64 reply_correlation_id`, set from the request
  message in `remote_on_message` before every dispatch. No reset afterwards:
  `remote_respond` is only reached from dispatch handlers, so a reset would
  be unobservable (its mutation survived).
- `remote_respond` sends through `break_net_reactor_send_correlated` with that
  ID, so success and RESULT responses both echo it. Uncorrelated requests get
  uncorrelated (byte-identical) responses.
- The SNOWFLAKE=OFF stub surface is unchanged.

## Tasks

1. RED: `remote_response_echoes_request_correlation_id` in
   `engine/tests/test_editor_shell.c` (correlated DESCRIBE, correlated
   failing request -> RESULT, uncorrelated DESCRIBE). The test client's
   receive buffer grows by `BREAK_NET_ENVELOPE_CORRELATION_SIZE`.
2. GREEN: field, set/reset, respond.
3. Mutation: set, respond forward.
4. Docs: `editor_phase1.md` or the remote protocol doc addendum,
   Implementation_Status entry.

## Status (2026-11-15)

Tasks 1–4 delivered. `test_editor_shell` 198/198, two mutations killed, full ctest 405/405 (Snowflake tree) and 401/401 (default tree).
