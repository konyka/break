# Net messages and adapter: carry the correlation ID

Follow-up to `2026-11-15-net-envelope-correlation.md`. The envelope codec
carries `correlation_id`; the message types and the adapter drop it.

## Approach

- `BreakNetMessageView` and `BreakNetOwnedMessage` (`engine/src/network/break_net_message.h`)
  gain `uint64_t correlation_id` as the last member. The build uses
  `-Werror=missing-field-initializers`, so existing positional test
  initializers get a trailing `0u`.
- `break_net_message_view_init` keeps its signature and sets the ID to 0.
  `break_net_message_copy` copies it; `break_net_message_release` clears it.
- Adapter receive paths (`break_net_adapter.c`, plaintext and TLS) copy
  `envelope.correlation_id` into the received event message.
- New `break_net_reactor_send_correlated(reactor, key, id, version, cid, data, size)`;
  `break_net_reactor_send` forwards with cid 0. The outbound drain writes the
  queued ID into the envelope.

## Tasks

1. RED: `break_net_message_copy_keeps_correlation_id` and
   `break_net_adapter_loopback_carries_correlation_id` in
   `engine/tests/test_break_net_adapter.c`.
2. GREEN: message types, copy/release, adapter receive, send_correlated, drain.
3. Mutation: copy, release, receive assignment, drain assignment, send forward.
4. Docs: `runtime_network.md` addendum, Implementation_Status entry.

## Status (2026-11-15)

Tasks 1–4 delivered. `test_break_net_adapter` 44/44, `test_break_session` 41/41, seven mutations killed, full ctest 405/405 (Snowflake tree) and 401/401 (default tree).
