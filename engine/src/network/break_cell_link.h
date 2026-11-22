#ifndef BREAK_CELL_LINK_H
#define BREAK_CELL_LINK_H

#include "../core/types.h"
#include "break_cell_handoff.h"
#include "network.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Cross-process transport for BreakCell handoff messages (design:
 * docs/design/cell_handoff.md "跨进程传输").
 *
 * Wire format, little-endian, one message per UDP datagram:
 *   u32 magic 'BRC1'  u16 version  u16 type
 *   u32 from_cell  u32 to_cell  u32 state_size
 *   u64 entity  u64 epoch  u64 txn  u64 nonce
 *   u64 sequence                      per-sender, strictly increasing, > 0
 *   u32 key_id                        which key made the tag, > 0
 *   u8  state[state_size]             state_size <= BREAK_CELL_STATE_MAX
 *   u8  tag[32]                       HMAC-SHA256(key, every byte above)
 * Every cell of one world shares the key. Keys rotate without a pause: a
 * link holds a current key, which it sends with, and the previous one,
 * which it still accepts until break_cell_link_retire_previous_key. Rotate
 * every receiver first, then every sender, then retire. A receiver accepts a
 * datagram only if the length, magic, version, type and state size are
 * valid, key_id names a key it holds, the tag matches, from_cell is a configured peer, to_cell is the local cell, and the
 * sequence passes that peer's replay window. The window is marked only after
 * the tag verifies, so a forged datagram cannot use up a sequence number.
 * Sequences start at the wall clock in microseconds, so a restarted sender
 * still lands above everything it sent before; a receiver whose own restart
 * reset its windows relies on BreakCell itself tolerating duplicates.
 *
 * Threading: one owner thread per link, the same thread as its BreakCell. */

#define BREAK_CELL_WIRE_MAGIC 0x31435242u
#define BREAK_CELL_WIRE_VERSION 2u
#define BREAK_CELL_WIRE_HEADER_SIZE 64u
#define BREAK_CELL_WIRE_TAG_SIZE 32u
#define BREAK_CELL_WIRE_MAX_SIZE \
    (BREAK_CELL_WIRE_HEADER_SIZE + BREAK_CELL_STATE_MAX + BREAK_CELL_WIRE_TAG_SIZE)
#define BREAK_CELL_LINK_MIN_KEY_SIZE 16u
#define BREAK_CELL_LINK_MAX_KEY_SIZE 64u
#define BREAK_CELL_LINK_MAX_PEERS 16u

typedef enum {
    BREAK_CELL_WIRE_OK = 0,
    BREAK_CELL_WIRE_INVALID_ARGUMENT,
    BREAK_CELL_WIRE_BAD_LENGTH,
    BREAK_CELL_WIRE_BAD_HEADER, /* magic, version, type or state size */
    BREAK_CELL_WIRE_BAD_TAG,
    BREAK_CELL_WIRE_BUFFER_TOO_SMALL
} BreakCellWireResult;

/* Encodes msg with the given key id (> 0) and sequence (> 0). */
BreakCellWireResult break_cell_wire_encode(const u8 *key, u32 key_size, u32 key_id, u64 sequence,
                                           const BreakCellMsg *msg, u8 *out, u32 capacity,
                                           u32 *out_size);
/* Validates and decodes one datagram; replay and peer checks are the link's.
 * out_key_id may be NULL. */
BreakCellWireResult break_cell_wire_decode(const u8 *key, u32 key_size, const u8 *data,
                                           u32 size, BreakCellMsg *out_msg, u64 *out_sequence,
                                           u32 *out_key_id);
/* Reads the unauthenticated key id, to pick the key to verify with. */
bool break_cell_wire_key_id(const u8 *data, u32 size, u32 *out_key_id);

typedef struct {
    u32 cell_id;
    NetAddress address;
} BreakCellPeer;

typedef struct {
    u32 cell_id;
    u16 bind_port; /* 0 picks a free port; see break_cell_link_port */
    const u8 *key;
    u32 key_size; /* BREAK_CELL_LINK_MIN_KEY_SIZE..MAX_KEY_SIZE */
    u32 key_id;   /* > 0 */
    const BreakCellPeer *peers;
    u32 peer_count; /* 1..BREAK_CELL_LINK_MAX_PEERS, distinct ids, not cell_id */
} BreakCellLinkConfig;

typedef struct {
    u64 sent;
    u64 send_failed;    /* unknown destination cell or socket error */
    u64 received;       /* delivered to the cell */
    u64 bad_format;     /* length, header */
    u64 bad_tag;
    u64 unknown_key;    /* key_id is neither the current nor the previous key */
    u64 unknown_peer;   /* from_cell not configured, or to_cell not local */
    u64 replayed;       /* duplicate or older than the replay window */
} BreakCellLinkStats;

typedef struct BreakCellLink BreakCellLink;

/* NULL for invalid configuration or when the socket cannot be bound. The
 * caller has called net_init. */
BreakCellLink *break_cell_link_create(const BreakCellLinkConfig *config);
void break_cell_link_destroy(BreakCellLink *link);
u16 break_cell_link_port(const BreakCellLink *link);

/* Matches BreakCellSendFn: pass break_cell_link_send as the cell's send
 * callback and the link as its user pointer. Messages whose from_cell is not
 * the link's cell or whose to_cell is not a configured peer are counted as
 * send_failed and dropped. */
void break_cell_link_send(void *link, const BreakCellMsg *msg);

/* Reads up to max_datagrams pending datagrams without blocking and hands
 * every accepted message to break_cell_receive. Returns the number
 * delivered. */
u32 break_cell_link_poll(BreakCellLink *link, BreakCell *cell, u32 max_datagrams);

/* Makes `key` the current key (used for sending) and keeps the old current
 * key as the previous one (still accepted); any older key is dropped. False,
 * with no change, for an invalid key or a key_id the link already holds. */
bool break_cell_link_rotate_key(BreakCellLink *link, u32 key_id, const u8 *key, u32 key_size);
/* Stops accepting the previous key. False when there is none. */
bool break_cell_link_retire_previous_key(BreakCellLink *link);

bool break_cell_link_stats(const BreakCellLink *link, BreakCellLinkStats *out_stats);

/* Rejection events (design: docs/design/cell_handoff.md "拒绝事件"). The
 * hook runs on the polling thread, once per rejected datagram, after the
 * matching counter moved; it must not call back into the link. `from_cell`
 * is the claimed sender (0 when the datagram was too short to name one) and
 * is unauthenticated except for BREAK_CELL_LINK_REJECT_REPLAYED and
 * _UNKNOWN_PEER, which are only reported after the tag verified. Typical
 * use: forward security events to the runtime message bus or a log. */
typedef enum {
    BREAK_CELL_LINK_REJECT_BAD_FORMAT = 1,
    BREAK_CELL_LINK_REJECT_UNKNOWN_KEY = 2,
    BREAK_CELL_LINK_REJECT_BAD_TAG = 3,
    BREAK_CELL_LINK_REJECT_UNKNOWN_PEER = 4,
    BREAK_CELL_LINK_REJECT_REPLAYED = 5
} BreakCellLinkReject;

typedef void (*BreakCellLinkRejectFn)(void *user, BreakCellLinkReject reason, u32 from_cell);

/* NULL hook removes it. False for a NULL link. */
bool break_cell_link_set_reject_hook(BreakCellLink *link, BreakCellLinkRejectFn hook, void *user);

#ifdef __cplusplus
}
#endif

#endif
