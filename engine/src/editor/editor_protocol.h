#pragma once
/* Break editor remote wire protocol — Stage 4 scene editor Phase 4 Task 1.
 *
 * Shared message definitions (ids, payload layouts, version) used by the
 * editor remote session host (apps/editor/editor_remote.c) and by test
 * clients. The messages ride the existing 18-byte break_net envelope
 * (network/break_net_envelope.h); the ids live in the DEFAULT registry's
 * free id space (4..19) because the envelope codec only consults
 * break_net_message_registry_default() (docs/design/session_protocol.md:117
 * — the codec-boundary note, documented not worked around).
 *
 * Wire rules (pinned by tests):
 *   - payloads are canonical little-endian binary, parsed with explicit
 *     get16/get32/get64 — no structs on the wire, no unbounded reads;
 *   - every inbound payload is <= BREAK_EDITOR_PROTO_MAX_PAYLOAD (4096 B,
 *     matching the Lua eval input bound); the envelope codec rejects larger
 *     frames before any handler runs (registry payload_limit), and the
 *     handler re-checks the exact layout — unknown id / malformed payload /
 *     oversize closes the connection (fail closed);
 *   - strings are length-prefixed (u16 byte count, no NUL on the wire);
 *   - f32 is its 4 little-endian bytes (uint32 lane, memcpy'd — no aliasing);
 *   - entity ids are the 8 little-endian bytes of {index/u32, generation/u32}
 *     (BreakEditorEntityId layout, editor_doc.h — low 4 bytes index, high 4
 *     bytes generation);
 *   - every request elicits exactly ONE response: the per-id success
 *     response described below, or BREAK_EDITOR_MSG_RESULT with a non-ok
 *     status (0 ok, 1 invalid, 2 failed) for well-formed requests whose
 *     command failed. Malformed frames never get a response: the connection
 *     closes.
 *
 * Threading: the handlers run on the editor shell thread (the GameThread —
 * the STEP-mode reactor is stepped from break_editor_remote_tick inside
 * break_editor_shell_tick), so every doc/Lua/command call below satisfies
 * the single-owner-thread convention by construction. */

#define BREAK_EDITOR_PROTO_VERSION 1u
#define BREAK_EDITOR_PROTO_MAX_PAYLOAD 4096u

enum BreakEditorMessageId {
    BREAK_EDITOR_MSG_DESCRIBE = 4,   /* req: empty → rsp: version/u16, entity_count/u32, dirty/u8 */
    BREAK_EDITOR_MSG_LIST     = 5,   /* req: empty → rsp: count/u16 + per-entity {id/u64, name_len/u16, name} */
    BREAK_EDITOR_MSG_SPAWN    = 6,   /* req: name_len/u16 + name (0 = generated) → rsp: entity_id/u64 */
    BREAK_EDITOR_MSG_REMOVE   = 7,   /* req: entity_id/u64 → rsp: removed/u8 */
    BREAK_EDITOR_MSG_RENAME   = 8,   /* req: entity_id/u64 + name_len/u16 + name → rsp: ok/u8 */
    BREAK_EDITOR_MSG_SET_FIELD= 9,   /* req: entity_id/u64 + comp_len/u16+comp + field_len/u16+field + value/f32 → rsp: ok/u8 */
    BREAK_EDITOR_MSG_UNDO     = 10,  /* req: empty → rsp: applied/u8 */
    BREAK_EDITOR_MSG_REDO     = 11,  /* req: empty → rsp: applied/u8 */
    BREAK_EDITOR_MSG_EVAL     = 12,  /* req: text_len/u16 + text (≤4096) → rsp: ok/u8 + lines (console ring tail, bounded) */
    BREAK_EDITOR_MSG_RESULT   = 13,  /* generic response wrapper: status/u8 (0 ok,1 invalid,2 failed) + payload */
    BREAK_EDITOR_MSG_SAVE     = 14   /* req: empty → rsp: saved/u8 — writes the shell's configured scene path (no path on the wire); 0 = no path or write failed */,
    BREAK_EDITOR_MSG_LOAD    = 15   /* req: empty → rsp: loaded/u8 — reloads the configured scene path from disk; 0 = no path, unsaved changes (never discarded remotely), or load failed */,
    BREAK_EDITOR_MSG_VIEW     = 16   /* req: mask/u8 + value/u8 (bit0 grid, bit1 stats overlay, bit2 reset camera; mask 0 = query) → rsp: grid/u8, stats/u8, camera 7×f32 (target xyz, yaw, pitch, distance, fov_y). View state only: no doc edit, no undo */
};

/* Response status values carried in the BREAK_EDITOR_MSG_RESULT wrapper. */
enum BreakEditorProtoStatus {
    BREAK_EDITOR_PROTO_STATUS_OK = 0,
    BREAK_EDITOR_PROTO_STATUS_INVALID = 1,
    BREAK_EDITOR_PROTO_STATUS_FAILED = 2
};

/* EVAL response layout after the status byte: line_count/u16, then per
 * line {line_len/u16, bytes} — the newest tail of the shared console ring
 * produced by the eval ("lua| ..." lines), bounded so the whole response
 * payload stays <= BREAK_EDITOR_PROTO_MAX_PAYLOAD. */
#define BREAK_EDITOR_PROTO_EVAL_MAX_LINES 16u
