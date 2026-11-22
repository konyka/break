#ifndef BREAK_CELL_HANDOFF_H
#define BREAK_CELL_HANDOFF_H

#include "../core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Cross-cell authority handoff (design: docs/design/cell_handoff.md).
 *
 * A world is split into cells; each entity is simulated by exactly one
 * authoritative cell. BreakCell is one cell's side of moving an entity to a
 * neighbour. It is transport-neutral: outgoing messages go to the
 * configured send callback, incoming ones are passed to break_cell_receive,
 * and break_cell_tick drives retransmission and timeouts. The transport may
 * drop, duplicate and reorder messages.
 *
 * Protocol (source S, target T, one transaction id per offer):
 *   S: OFFER(txn, epoch, state)      S stays authoritative and writable.
 *   T: ACCEPT(txn, nonce)            T holds a receiving record; the nonce
 *                                    identifies that record. REJECT when
 *                                    T has no room.
 *   S: COMMIT(txn, nonce, epoch + 1, latest state)
 *                                    S gives up authority before sending.
 *   T: COMMIT_ACK(txn, nonce)        T is now the authority (applies the
 *                                    COMMIT only to the record with that
 *                                    nonce); S drops its record on the ack.
 *   S: ABORT(txn, nonce or 0)        after an offer timeout, or in answer to
 *                                    an ACCEPT S cannot use; T drops the
 *                                    matching receiving record.
 * OFFER and COMMIT are retransmitted until answered, ACCEPT until the
 * record is committed or aborted. An offer times out only while S is still
 * authoritative; a COMMIT is never abandoned. A COMMIT that matches no
 * receiving record was already applied (a receiving record leaves only by
 * commit or by an ABORT, and S never aborts a transaction it committed), so
 * T acknowledges it. An OFFER at an epoch not lower than the one S
 * committed also proves T applied the commit, which releases S. Hence at
 * most one cell is authoritative for an entity at any time, and epochs only
 * grow.
 *
 * Threading: a BreakCell is single-threaded; call everything from the
 * cell's own thread. The send callback runs inside these calls and must not
 * call back into the same cell. */

#define BREAK_CELL_STATE_MAX 64u

typedef enum {
    BREAK_CELL_MSG_OFFER = 1,
    BREAK_CELL_MSG_ACCEPT = 2,
    BREAK_CELL_MSG_REJECT = 3,
    BREAK_CELL_MSG_COMMIT = 4,
    BREAK_CELL_MSG_COMMIT_ACK = 5,
    BREAK_CELL_MSG_ABORT = 6
} BreakCellMsgType;

typedef struct {
    u32 type; /* BreakCellMsgType; other values are ignored */
    u32 from_cell;
    u32 to_cell;
    u32 state_size;
    u64 entity;
    u64 epoch;
    u64 txn;
    u64 nonce;
    u8 state[BREAK_CELL_STATE_MAX];
} BreakCellMsg;

typedef void (*BreakCellSendFn)(void *user, const BreakCellMsg *msg);

typedef struct {
    u32 cell_id;
    u32 capacity;            /* entity records, receiving ones included; > 0 */
    u32 retransmit_ticks;    /* 0 selects 1 */
    u32 offer_timeout_ticks; /* 0 selects 8 * retransmit_ticks */
    BreakCellSendFn send;    /* required */
    void *user;
    /* Queue outgoing messages until break_cell_flush instead of sending
     * them at once. Required for crash recovery from snapshots: see
     * break_cell_snapshot. */
    bool hold_outbox;
} BreakCellConfig;

typedef enum {
    BREAK_CELL_ENTITY_NONE = 0,
    BREAK_CELL_ENTITY_OWNED,      /* authoritative */
    BREAK_CELL_ENTITY_OFFERING,   /* authoritative, offer in flight */
    BREAK_CELL_ENTITY_COMMITTING, /* authority given up, waiting for the ack */
    BREAK_CELL_ENTITY_RECEIVING   /* accepted an offer, waiting for the commit */
} BreakCellEntityState;

typedef struct {
    u64 handoffs_out; /* commits sent (authority given up) */
    u64 handoffs_in;  /* commits applied (authority taken) */
    u64 rejected;     /* offers the target refused */
    u64 aborted;      /* offers that timed out */
    u64 retransmits;
    u64 ignored;      /* malformed or stale messages */
} BreakCellStats;

typedef struct BreakCell BreakCell;

/* NULL for a NULL config, no send callback, zero capacity, or OOM. */
BreakCell *break_cell_create(const BreakCellConfig *config);
void break_cell_destroy(BreakCell *cell);

/* Creates an owned entity at epoch 1. False if the entity already has a
 * record here, the state is too large or NULL with size > 0, or the cell is
 * full. */
bool break_cell_spawn(BreakCell *cell, u64 entity, const void *state, u32 size);
/* Replaces the state; only while authoritative. */
bool break_cell_write(BreakCell *cell, u64 entity, const void *state, u32 size);
/* Copies the state (up to capacity bytes) while authoritative. */
bool break_cell_read(BreakCell *cell, u64 entity, void *out, u32 capacity, u32 *out_size,
                     u64 *out_epoch);
bool break_cell_is_authoritative(BreakCell *cell, u64 entity);
BreakCellEntityState break_cell_entity_state(BreakCell *cell, u64 entity);
u32 break_cell_entity_count(BreakCell *cell);

/* Offers an owned entity to another cell. False unless the entity is OWNED
 * here and to_cell differs from this cell. */
bool break_cell_begin_handoff(BreakCell *cell, u64 entity, u32 to_cell);

void break_cell_receive(BreakCell *cell, const BreakCellMsg *msg);
/* Advances retransmission and offer timeouts by one tick. */
void break_cell_tick(BreakCell *cell);
bool break_cell_stats(BreakCell *cell, BreakCellStats *out_stats);

/* Sends every queued message (hold_outbox) in order. Returns the count. */
u32 break_cell_flush(BreakCell *cell);
u32 break_cell_outbox_count(BreakCell *cell);

/* Crash recovery. A snapshot holds every record, in-flight ones included,
 * and the transaction and nonce counters; queued messages and stats are not
 * part of it. Safe recovery needs hold_outbox and this order after each
 * batch of calls: snapshot, write it to durable storage, then flush. Then
 * every message a peer has seen comes from a durable state, so a cell
 * restored from its latest snapshot can never again own an entity it gave
 * away, nor reuse a transaction id or nonce; losing the unflushed messages
 * is the same as losing them on the network. Writes made after the latest
 * snapshot are lost with the crash.
 *
 * break_cell_snapshot_size gives the bytes needed (0 for NULL or for a
 * snapshot that would not fit in 32 bits).
 * break_cell_snapshot writes the snapshot and its size; false for NULL
 * arguments, a snapshot that would not fit in 32 bits, or a buffer that is
 * too small. */
u32 break_cell_snapshot_size(BreakCell *cell);
bool break_cell_snapshot(BreakCell *cell, void *out, u32 capacity, u32 *out_size);
/* Creates a cell from a snapshot. NULL for an invalid config (as
 * break_cell_create), or a snapshot that is truncated, corrupt (checksum),
 * from another cell id, or holds more records than config->capacity.
 * In-flight records keep their retransmit and offer-timeout counters. */
BreakCell *break_cell_restore(const BreakCellConfig *config, const void *snapshot, u32 size);

#ifdef __cplusplus
}
#endif

#endif
