# core_app: tell each peer its session number

Status: Done

## Goal

missing_capabilities section 13: the server trace names every session
(`network_session result=authenticated session=S`), but a peer does not know
its own number, so `trace_merge --session N PEER.json` still needs the
operator to pair files with sessions. After authentication the server now
sends the peer one message carrying the session number.

## Wire format

Message `0x4005` (`BREAK_NET_MESSAGE_ID_SESSION_WELCOME`), version 1,
AUTHENTICATED only, `IDEMPOTENT`, exactly 16 bytes, little-endian:
`[0]` u32 magic `SESW` (`0x57534553`), `[4]` u32 reserved zero, `[8]` u64
session id (non-zero).

- `core_app_session_welcome_encode(session_id, buf, cap, &size)`: INVALID for
  id 0 or NULL, OVER_LIMIT when cap < 16; nothing written on failure.
- `core_app_session_welcome_decode(payload, size, &id)`: TRUNCATED /
  OVER_LIMIT for a wrong length, BAD_MAGIC, INVALID for non-zero reserved
  bytes or id 0; output untouched on failure.

## Server

The transport sends the welcome once per slot, in `net_send_pending`, before
snapshots, physics reports and clock probes, so it is the first application
message the peer receives. `network_stats` gains `session_welcomes_sent`.
The server registers no handler for `0x4005`: a peer that sends one is
counted as `session_handler_failed` and the session stays open.

## Tests

1. `test_core_app_network`: golden bytes round trip; every malformed payload
   rejected without writing; encode refuses id 0, NULL, small capacity.
2. `test_break_session`: registry entry for `0x4005`, count 26 / 25.
3. loopback: peers A, A2, F each receive a welcome before any snapshot; A
   and A2 get different ids; the report has `session_welcome session=S`;
   the driver requires each reported id to be one of the authenticated
   sessions in the server trace and `session_welcomes_sent == authenticated`.
   A also sends a welcome to the server, which must not close it.

## Result

Delivered as planned; the welcome also gates every other send to the slot.
`test_core_app_network` 19 cases, loopback and late_auth 12/12 locally. Of
17 mutations, 15 are caught; requiring `welcomed` in `net_slot_sendable`
and the liveness check before sending a welcome are defence in depth (the
welcome goes out first in the same pump, and an unauthenticated slot has
session id 0, which the encoder refuses). Not done: the core_app runtime as
a client writing its own session number into its trace.

