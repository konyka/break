# Physics sync messages in the default net registry

## Goal
Let peers carry `physics_sync` reports and corrections over the break_net
envelope codec. The codec only consults `break_net_message_registry_default()`,
so both payloads need registered ids before any transport can send them.

## Design
- `BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT 0x4002u`: v1..1, payload limit
  `BREAK_NET_PHYSICS_SYNC_REPORT_PAYLOAD 16u` (equals
  `PHYSICS_SYNC_REPORT_BYTES`), `AUTHENTICATED`, `IDEMPOTENT`.
- `BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_CORRECTION 0x4003u`: v1..1, payload limit
  `BREAK_NET_MAX_PAYLOAD_SIZE` (64 KiB; a correction is a 16-byte header plus a
  full snapshot whose size depends on body count), `AUTHENTICATED`,
  `IDEMPOTENT`.
- The registry stays free of physics headers; the test pins the 16-byte
  limit against `PHYSICS_SYNC_REPORT_BYTES`.
- Count becomes 24 (CRYPTO=ON) / 23 (OFF).

## Tests (test_break_session, Snowflake tree `build-net-master`)
- `break_session_registry_has_physics_sync_messages`: both ids present with
  the fields above; an encoded report round-trips through
  `break_net_envelope_encode`/`decode`; a 17-byte report payload is rejected
  by encode.

## Docs
- `docs/design/session_protocol.md`: table rows and count sentence.
- Status in this file, `docs/Implementation_Status.md`,
  `docs/cross_engine/missing_capabilities.md` section 9.

## Status
- Done. Ids 0x4002/0x4003 registered; `break_session_registry_has_physics_sync_messages`
  passes (`test_break_session` 43/43 in `build-net-master`); 11 mutations killed.
- Not done: no runtime sends or consumes these messages yet.
