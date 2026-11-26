#pragma once

/* Optional, default-off snapshot channel for the real application.
 *
 * The application never trusts a network peer with authority over its
 * simulation. This module therefore has two halves and no shared mutable
 * state with the level: a fixed, versioned, little-endian snapshot the
 * application publishes, and a decoder that turns a peer message into at
 * most diagnostic data. The decoder cannot produce a level mutation, which
 * is why the outbound and inbound paths are separate types instead of one
 * bidirectional session handle.
 */

#include <core/types.h>
#include <runtime/runtime_types.h>

#include <stddef.h>

#define CORE_APP_SNAPSHOT_MAGIC 0x43534e50u /* "CSNP" */
#define CORE_APP_SNAPSHOT_VERSION 1u
/* Wire layout, all little-endian, 32-byte header:
 *   [0]  u32 magic "CSNP"
 *   [4]  u16 version
 *   [6]  u16 header_bytes
 *   [8]  u64 frame_id
 *   [16] u64 level_generation
 *   [24] u32 schema_hash
 *   [28] u32 entity_count
 * then entity_count * 24 bytes of (u32 index, u32 generation, f32 x, f32 y,
 * f32 z, u32 flags). */
#define CORE_APP_SNAPSHOT_HEADER_BYTES 32u
#define CORE_APP_SNAPSHOT_ENTITY_BYTES 24u
#define CORE_APP_SNAPSHOT_MAX_ENTITIES 64u
#define CORE_APP_SNAPSHOT_MAX_BYTES \
    (CORE_APP_SNAPSHOT_HEADER_BYTES + \
     CORE_APP_SNAPSHOT_MAX_ENTITIES * CORE_APP_SNAPSHOT_ENTITY_BYTES)

#define CORE_APP_SNAPSHOT_MESSAGE_ID 0x4001u
#define CORE_APP_SNAPSHOT_PROTOCOL_VERSION 1u

typedef enum CoreAppSnapshotOutcome {
    CORE_APP_SNAPSHOT_OK = 0,
    CORE_APP_SNAPSHOT_INVALID,
    CORE_APP_SNAPSHOT_BAD_MAGIC,
    CORE_APP_SNAPSHOT_BAD_VERSION,
    CORE_APP_SNAPSHOT_TRUNCATED,
    CORE_APP_SNAPSHOT_OVER_LIMIT
} CoreAppSnapshotOutcome;

/* One entity as published. index and generation together identify an entity
 * across levels; a stale pair never matches the live level. */
typedef struct CoreAppSnapshotEntity {
    u32 index;
    u32 generation;
    f32 x;
    f32 y;
    f32 z;
    u32 flags;
} CoreAppSnapshotEntity;

typedef struct CoreAppSnapshot {
    u32 schema_hash;
    u64 frame_id;
    u64 level_generation;
    u32 entity_count;
    CoreAppSnapshotEntity entities[CORE_APP_SNAPSHOT_MAX_ENTITIES];
} CoreAppSnapshot;

/* Fills a snapshot from POD values only. Returns INVALID when the entity
 * count exceeds the fixed capacity; the caller keeps the previous snapshot. */
CoreAppSnapshotOutcome core_app_snapshot_build(CoreAppSnapshot *out, u64 frame_id,
                                               u64 level_generation, u32 schema_hash,
                                               const CoreAppSnapshotEntity *entities,
                                               u32 entity_count);

/* Encodes into a caller buffer. Sets *out_size to the exact byte count on OK
 * and leaves the buffer untouched on failure. */
CoreAppSnapshotOutcome core_app_snapshot_encode(const CoreAppSnapshot *snapshot,
                                                u8 *out_buffer, size_t capacity,
                                                size_t *out_size);

/* Decodes a peer payload. Never writes outside `out`, never allocates, and
 * reports TRUNCATED/OVER_LIMIT instead of trusting a declared count. On any
 * failure `out` is left exactly as the caller passed it. */
CoreAppSnapshotOutcome core_app_snapshot_decode(const u8 *payload, size_t size,
                                                CoreAppSnapshot *out);

/* Schema hash over the payload field layout, so a peer with a different
 * layout is rejected before any field is interpreted. */
u32 core_app_snapshot_schema_hash(void);

/* Clock probe: a request carries the sender's send time t0; the reply echoes
 * t0 and adds the peer's receive time t1 and send time t2, all in
 * microseconds. Little-endian layout: [0] u32 magic, [4] u8 kind, [5..7]
 * reserved zero, [8] t0, [16] t1, [24] t2. A request must leave t1 and t2
 * zero. */
#define CORE_APP_CLOCK_PROBE_MAGIC 0x504b4c43u /* "CLKP" */
#define CORE_APP_CLOCK_PROBE_BYTES 32u
#define CORE_APP_CLOCK_PROBE_MESSAGE_ID 0x4004u

typedef enum CoreAppClockProbeKind {
    CORE_APP_CLOCK_PROBE_REQUEST = 1,
    CORE_APP_CLOCK_PROBE_REPLY = 2
} CoreAppClockProbeKind;

typedef struct CoreAppClockProbe {
    CoreAppClockProbeKind kind;
    u64 t0;
    u64 t1;
    u64 t2;
} CoreAppClockProbe;

/* Writes exactly CORE_APP_CLOCK_PROBE_BYTES. On failure neither the buffer
 * nor *out_size is touched. */
CoreAppSnapshotOutcome core_app_clock_probe_encode(const CoreAppClockProbe *probe,
                                                   u8 *out_buffer, size_t capacity,
                                                   size_t *out_size);
/* Validates size, magic, kind, reserved bytes and request fields; *out is
 * written only on success. */
CoreAppSnapshotOutcome core_app_clock_probe_decode(const u8 *payload, size_t size,
                                                   CoreAppClockProbe *out);
/* Builds the reply to a request with receive time t1 and send time t2
 * (t2 >= t1). *reply is written only on success. */
CoreAppSnapshotOutcome core_app_clock_probe_answer(const CoreAppClockProbe *request,
                                                   u64 t1, u64 t2,
                                                   CoreAppClockProbe *reply);

/* Session welcome: after authentication the server sends each peer the
 * session number it names that peer by in its own trace. Little-endian
 * layout: [0] u32 magic, [4] u32 reserved zero, [8] u64 session id
 * (non-zero). */
#define CORE_APP_SESSION_WELCOME_MAGIC 0x57534553u /* "SESW" */
#define CORE_APP_SESSION_WELCOME_BYTES 16u
#define CORE_APP_SESSION_WELCOME_MESSAGE_ID 0x4005u

/* Writes exactly CORE_APP_SESSION_WELCOME_BYTES. A zero id is INVALID. On
 * failure neither the buffer nor *out_size is touched. */
CoreAppSnapshotOutcome core_app_session_welcome_encode(u64 session_id, u8 *out_buffer,
                                                       size_t capacity, size_t *out_size);
/* Validates size, magic, reserved bytes and a non-zero id; *out_session_id
 * is written only on success. */
CoreAppSnapshotOutcome core_app_session_welcome_decode(const u8 *payload, size_t size,
                                                       u64 *out_session_id);

/* Voice relay: with --voice-relay the server forwards a voice frame it
 * accepted from one peer to every other peer. Little-endian layout: [0] u32
 * magic, [4] u32 reserved zero, [8] u64 source session id (non-zero, the
 * number the source peer received in its welcome), [16] the frame bytes as
 * the source sent them (1..976 bytes, one BRV1 or BRV2 frame). */
#define CORE_APP_VOICE_RELAY_MAGIC 0x594C5256u /* "VRLY" */
#define CORE_APP_VOICE_RELAY_HEADER_BYTES 16u
#define CORE_APP_VOICE_RELAY_MAX_FRAME_BYTES 976u
#define CORE_APP_VOICE_RELAY_MAX_BYTES \
    (CORE_APP_VOICE_RELAY_HEADER_BYTES + CORE_APP_VOICE_RELAY_MAX_FRAME_BYTES)
#define CORE_APP_VOICE_RELAY_MESSAGE_ID 0x4007u

/* Writes the header and copies the frame. A zero source or a NULL or empty
 * frame is INVALID; a frame over the limit or a short buffer is OVER_LIMIT.
 * On failure neither the buffer nor *out_size is touched. */
CoreAppSnapshotOutcome core_app_voice_relay_encode(u64 source_session_id, const u8 *frame,
                                                   size_t frame_size, u8 *out_buffer,
                                                   size_t capacity, size_t *out_size);
/* Validates size, magic, reserved bytes and a non-zero source. *out_frame
 * points into payload; the frame itself is not parsed. Outputs are written
 * only on success. */
CoreAppSnapshotOutcome core_app_voice_relay_decode(const u8 *payload, size_t size,
                                                   u64 *out_source_session_id,
                                                   const u8 **out_frame,
                                                   size_t *out_frame_size);

/* Voice mute: a peer asks the server to stop (or resume) relaying one
 * source session's voice to it. Little-endian layout: [0] u32 magic,
 * [4] u32 flags (bit 0 = mute, every other bit zero), [8] u64 target
 * session id (non-zero, as named in relay headers). */
#define CORE_APP_VOICE_MUTE_MAGIC 0x54554D56u /* "VMUT" */
#define CORE_APP_VOICE_MUTE_BYTES 16u
#define CORE_APP_VOICE_MUTE_FLAG_MUTED 1u
#define CORE_APP_VOICE_MUTE_MESSAGE_ID 0x4008u

/* Writes exactly CORE_APP_VOICE_MUTE_BYTES. A zero target is INVALID. On
 * failure neither the buffer nor *out_size is touched. */
CoreAppSnapshotOutcome core_app_voice_mute_encode(u64 target_session_id, bool muted,
                                                  u8 *out_buffer, size_t capacity,
                                                  size_t *out_size);
/* Validates size, magic, unknown flag bits and a non-zero target; outputs
 * are written only on success. */
CoreAppSnapshotOutcome core_app_voice_mute_decode(const u8 *payload, size_t size,
                                                  u64 *out_target_session_id,
                                                  bool *out_muted);

/* Prediction channel (--prediction). Each connection drives one body the
 * server owns; the peer predicts it with the same step and is corrected by
 * the server's snapshots (break_prediction, break_prediction_session). The
 * body is not a level entity, so it never changes the simulation trace.
 * State, little-endian: [0] i32 position, [4] i32 velocity. Input: [0] i32
 * acceleration. */
#define CORE_APP_PREDICTION_STATE_BYTES 8u
#define CORE_APP_PREDICTION_INPUT_BYTES 4u
#define CORE_APP_PREDICTION_MAX_ACCEL 8
#define CORE_APP_PREDICTION_MAX_SPEED 1000

/* One tick, a BreakPredictionStepFn (`user` is unused): velocity += accel,
 * clamped to +-CORE_APP_PREDICTION_MAX_SPEED, then position += velocity
 * with u32 wrap-around. An acceleration outside +-CORE_APP_PREDICTION_MAX_ACCEL
 * or a NULL argument returns false and writes nothing; this is where the
 * server refuses an input a peer cannot legitimately send. `out_state` may
 * alias `state`. */
bool core_app_prediction_step(void *user, const void *state, const void *input,
                              void *out_state);

/* Inbound authority firewall.
 *
 * A decoded peer snapshot is diagnostic data. Feeding it to this function is
 * the only way the application consumes it, and the function counts what it
 * rejected. It never returns a value the simulation applies. */
typedef struct CoreAppSnapshotInbox {
    u64 accepted_snapshots;
    u64 rejected_unknown_message;
    u64 rejected_unauthenticated;
    u64 rejected_schema;
    u64 rejected_stale_level;
    u64 overloads;
    bool authenticated;
    u16 admission_message_id;
    u32 peer_schema_hash;
} CoreAppSnapshotInbox;

void core_app_snapshot_inbox_init(CoreAppSnapshotInbox *inbox, bool authenticated,
                                  u16 admission_message_id, u32 peer_schema_hash);

typedef enum CoreAppSnapshotAdmission {
    CORE_APP_SNAPSHOT_ADMITTED = 0,
    CORE_APP_SNAPSHOT_REJECTED_UNKNOWN_MESSAGE,
    CORE_APP_SNAPSHOT_REJECTED_UNAUTHENTICATED,
    CORE_APP_SNAPSHOT_REJECTED_SCHEMA,
    CORE_APP_SNAPSHOT_REJECTED_STALE_LEVEL
} CoreAppSnapshotAdmission;

/* Admits a peer message for diagnostics only. level_generation is the live
 * value the application owns; a snapshot naming any other generation is
 * stale and dropped. */
CoreAppSnapshotAdmission core_app_snapshot_admit(CoreAppSnapshotInbox *inbox,
                                                 u16 message_id,
                                                 const CoreAppSnapshot *snapshot,
                                                 u64 live_level_generation);

/* Records one outbound enqueue attempt. Over capacity is counted and the
 * snapshot is dropped; the caller's frame is never blocked or rolled back. */
#define CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY 8u
typedef struct CoreAppSnapshotOutbox {
    CoreAppSnapshot pending[CORE_APP_SNAPSHOT_OUTBOUND_CAPACITY];
    u64 enqueued;
    u64 dropped;
    u32 head;
    u32 count;
} CoreAppSnapshotOutbox;

void core_app_snapshot_outbox_init(CoreAppSnapshotOutbox *outbox);
CoreAppSnapshotOutcome core_app_snapshot_outbox_push(CoreAppSnapshotOutbox *outbox,
                                                     const CoreAppSnapshot *snapshot);
/* Pops the oldest snapshot. Returns false when the outbox is empty. */
bool core_app_snapshot_outbox_pop(CoreAppSnapshotOutbox *outbox, CoreAppSnapshot *out);

/* Reads the environment variable `name` as exactly 2*size hex digits into
 * `out`, then removes the variable from the process environment whether or
 * not it decoded, so child processes and later getenv calls never see the
 * secret. An all-zero value is rejected as a placeholder. On failure `out`
 * is zeroed. The initial environment block the kernel exposes (for example
 * /proc/<pid>/environ) is not rewritten. */
bool core_app_net_take_secret_env(const char *name, u8 *out, usize size);
