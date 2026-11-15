# Net envelope: correlation ID on the wire

Gap: `missing_capabilities.md` §13 and the 2026-11-15 Implementation_Status
entries — runtime messages and profiler events carry `correlation_id`, but
the network envelope (`engine/src/network/break_net_envelope.{h,c}`) does not.

## Wire format

- Base header unchanged (18 bytes, little endian).
- New codec-owned flag `BREAK_NET_ENVELOPE_FLAG_CORRELATED = 0x0010`, outside
  the caller flag mask `0x000f`.
- When set, an 8-byte little-endian correlation ID follows the header, before
  the payload. The length field at offset 14 counts extension + payload
  ("body length"), so framers that read only the length field (the adapter
  plaintext parser) still find frame boundaries.
- Frames with `correlation_id == 0` are byte-identical to before.
- Compatibility: older decoders reject the flag (INVALID_FLAGS) instead of
  misreading the payload. Senders only set an ID for peers on this build.

## Rules

- Encode: `correlation_id != 0` -> set the flag and write the extension.
  Caller flags containing `0x0010` -> INVALID_FLAGS (the bit is codec-owned).
  Payload limits apply to the payload only.
- Decode: flag set -> body length must be >= 8 (else INVALID_LENGTH); an ID of
  0 is non-canonical -> INVALID_FLAGS. Output `flags` excludes the codec bit,
  `correlation_id` is filled, `payload_size` excludes the extension.
- Adapter plaintext framer: raw body length bound grows by 8 bytes.
- QUIC sender initializes `correlation_id = 0`.

## Tasks

1. RED: envelope tests in `engine/tests/test_break_session.c` (round trip,
   wire bytes, uncorrelated byte identity, reserved flag, short body, zero ID,
   max payload with ID).
2. GREEN: codec, adapter bound, QUIC init.
3. Mutation: flag write, extension offset, zero-ID reject, short-body reject,
   flag strip, caller-bit reject.
4. Docs: `docs/design/runtime_network.md` addendum, Implementation_Status.

Out of scope (next slice): carrying the ID through `BreakNetMessageView`,
adapter events and the session layer.

## Status (2026-11-15)

Tasks 1–4 delivered. `test_break_session` 41/41, eight mutations killed, full ctest 405/405 (Snowflake tree) and 401/401 (default tree).
