#include "break_cell_handoff.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
    bool used;
    BreakCellEntityState state;
    u64 entity;
    u64 epoch; /* OWNED/OFFERING: current; COMMITTING: the committed epoch;
                * RECEIVING: the offer's epoch */
    u32 size;
    u8 data[BREAK_CELL_STATE_MAX];
    u32 peer;  /* OFFERING/COMMITTING: target; RECEIVING: source */
    u64 txn;   /* the source's transaction id */
    u64 nonce; /* the target's receiving-record id */
    u32 since_send;
    u32 offer_age;
} CellRecord;

struct BreakCell {
    BreakCellConfig cfg;
    CellRecord *records;
    u64 next_txn;
    u64 next_nonce;
    BreakCellStats stats;
};

static CellRecord *cell_find(BreakCell *cell, u64 entity) {
    for (u32 i = 0; i < cell->cfg.capacity; i++) {
        if (cell->records[i].used && cell->records[i].entity == entity) return &cell->records[i];
    }
    return NULL;
}

static CellRecord *cell_alloc(BreakCell *cell, u64 entity) {
    for (u32 i = 0; i < cell->cfg.capacity; i++) {
        CellRecord *r = &cell->records[i];
        if (!r->used) {
            memset(r, 0, sizeof(*r));
            r->used = true;
            r->entity = entity;
            return r;
        }
    }
    return NULL;
}

static void cell_free(CellRecord *r) {
    memset(r, 0, sizeof(*r));
}

static void cell_send(BreakCell *cell, u32 type, u32 to, const CellRecord *r, u64 entity, u64 epoch,
                      u64 txn, u64 nonce) {
    BreakCellMsg m;
    memset(&m, 0, sizeof(m));
    m.type = type;
    m.from_cell = cell->cfg.cell_id;
    m.to_cell = to;
    m.entity = entity;
    m.epoch = epoch;
    m.txn = txn;
    m.nonce = nonce;
    if (r && (type == BREAK_CELL_MSG_OFFER || type == BREAK_CELL_MSG_COMMIT)) {
        m.state_size = r->size;
        memcpy(m.state, r->data, r->size);
    }
    cell->cfg.send(cell->cfg.user, &m);
}

/* What a record (re)sends; nothing for OWNED. */
static void cell_resend(BreakCell *cell, CellRecord *r) {
    switch (r->state) {
    case BREAK_CELL_ENTITY_OFFERING:
        cell_send(cell, BREAK_CELL_MSG_OFFER, r->peer, r, r->entity, r->epoch, r->txn, 0u);
        break;
    case BREAK_CELL_ENTITY_COMMITTING:
        cell_send(cell, BREAK_CELL_MSG_COMMIT, r->peer, r, r->entity, r->epoch, r->txn, r->nonce);
        break;
    case BREAK_CELL_ENTITY_RECEIVING:
        cell_send(cell, BREAK_CELL_MSG_ACCEPT, r->peer, NULL, r->entity, r->epoch, r->txn, r->nonce);
        break;
    default:
        break;
    }
    r->since_send = 0u;
}

BreakCell *break_cell_create(const BreakCellConfig *config) {
    BreakCell *cell;
    if (!config || !config->send || config->capacity == 0u) return NULL;
    cell = (BreakCell *)calloc(1, sizeof(*cell));
    if (!cell) return NULL;
    cell->records = (CellRecord *)calloc(config->capacity, sizeof(CellRecord));
    if (!cell->records) {
        free(cell);
        return NULL;
    }
    cell->cfg = *config;
    if (cell->cfg.retransmit_ticks == 0u) cell->cfg.retransmit_ticks = 1u;
    if (cell->cfg.offer_timeout_ticks == 0u) cell->cfg.offer_timeout_ticks = 8u * cell->cfg.retransmit_ticks;
    cell->next_txn = 1u;
    cell->next_nonce = 1u;
    return cell;
}

void break_cell_destroy(BreakCell *cell) {
    if (!cell) return;
    free(cell->records);
    free(cell);
}

static bool cell_state_ok(const void *state, u32 size) {
    return size <= BREAK_CELL_STATE_MAX && (state || size == 0u);
}

bool break_cell_spawn(BreakCell *cell, u64 entity, const void *state, u32 size) {
    CellRecord *r;
    if (!cell || !cell_state_ok(state, size) || cell_find(cell, entity)) return false;
    r = cell_alloc(cell, entity);
    if (!r) return false;
    r->state = BREAK_CELL_ENTITY_OWNED;
    r->epoch = 1u;
    r->size = size;
    if (size) memcpy(r->data, state, size);
    return true;
}

static CellRecord *cell_authoritative(BreakCell *cell, u64 entity) {
    CellRecord *r = cell ? cell_find(cell, entity) : NULL;
    if (r && (r->state == BREAK_CELL_ENTITY_OWNED || r->state == BREAK_CELL_ENTITY_OFFERING)) return r;
    return NULL;
}

bool break_cell_write(BreakCell *cell, u64 entity, const void *state, u32 size) {
    CellRecord *r = cell_authoritative(cell, entity);
    if (!r || !cell_state_ok(state, size)) return false;
    r->size = size;
    if (size) memcpy(r->data, state, size);
    return true;
}

bool break_cell_read(BreakCell *cell, u64 entity, void *out, u32 capacity, u32 *out_size,
                     u64 *out_epoch) {
    CellRecord *r = cell_authoritative(cell, entity);
    if (!r || (!out && capacity > 0u)) return false;
    if (out) memcpy(out, r->data, r->size < capacity ? r->size : capacity);
    if (out_size) *out_size = r->size;
    if (out_epoch) *out_epoch = r->epoch;
    return true;
}

bool break_cell_is_authoritative(BreakCell *cell, u64 entity) {
    return cell_authoritative(cell, entity) != NULL;
}

BreakCellEntityState break_cell_entity_state(BreakCell *cell, u64 entity) {
    CellRecord *r = cell ? cell_find(cell, entity) : NULL;
    return r ? r->state : BREAK_CELL_ENTITY_NONE;
}

u32 break_cell_entity_count(BreakCell *cell) {
    u32 n = 0u;
    if (!cell) return 0u;
    for (u32 i = 0; i < cell->cfg.capacity; i++) n += cell->records[i].used ? 1u : 0u;
    return n;
}

bool break_cell_begin_handoff(BreakCell *cell, u64 entity, u32 to_cell) {
    CellRecord *r = cell ? cell_find(cell, entity) : NULL;
    if (!r || r->state != BREAK_CELL_ENTITY_OWNED || to_cell == cell->cfg.cell_id) return false;
    r->state = BREAK_CELL_ENTITY_OFFERING;
    r->peer = to_cell;
    r->txn = cell->next_txn++;
    r->nonce = 0u;
    r->offer_age = 0u;
    cell_resend(cell, r);
    return true;
}

/* ---- target side ---- */

static void cell_on_offer(BreakCell *cell, const BreakCellMsg *m) {
    CellRecord *r = cell_find(cell, m->entity);
    if (r && r->state == BREAK_CELL_ENTITY_COMMITTING && m->epoch >= r->epoch) {
        /* only the cell we committed to could have produced this epoch, so
         * it applied our commit: the ack is no longer needed */
        cell_free(r);
        r = NULL;
    }
    if (r && r->state == BREAK_CELL_ENTITY_RECEIVING) {
        bool same = r->peer == m->from_cell && r->txn == m->txn;
        bool newer = m->epoch > r->epoch ||
                     (m->epoch == r->epoch && r->peer == m->from_cell && m->txn > r->txn);
        if (same) {
            cell_resend(cell, r); /* duplicate offer: repeat the accept */
            return;
        }
        if (!newer) {
            cell->stats.ignored++; /* a stale offer must not replace a live record */
            return;
        }
        cell_free(r); /* superseded: its source gave up that offer */
        r = NULL;
    }
    if (r) {
        cell->stats.ignored++; /* we own or offer it: the offer is stale */
        return;
    }
    r = cell_alloc(cell, m->entity);
    if (!r) {
        cell_send(cell, BREAK_CELL_MSG_REJECT, m->from_cell, NULL, m->entity, m->epoch, m->txn, 0u);
        return;
    }
    r->state = BREAK_CELL_ENTITY_RECEIVING;
    r->epoch = m->epoch;
    r->peer = m->from_cell;
    r->txn = m->txn;
    r->nonce = cell->next_nonce++;
    cell_resend(cell, r);
}

static void cell_on_commit(BreakCell *cell, const BreakCellMsg *m) {
    CellRecord *r = cell_find(cell, m->entity);
    if (r && r->state == BREAK_CELL_ENTITY_RECEIVING && r->peer == m->from_cell && r->txn == m->txn) {
        if (r->nonce != m->nonce) {
            /* a record re-created from a duplicate offer; the source aborts
             * it when our accept arrives, then this commit is acknowledged */
            cell->stats.ignored++;
            return;
        }
        r->state = BREAK_CELL_ENTITY_OWNED;
        r->epoch = m->epoch;
        r->size = m->state_size;
        memcpy(r->data, m->state, m->state_size);
        r->peer = 0u;
        r->txn = 0u;
        r->nonce = 0u;
        cell->stats.handoffs_in++;
    } else {
        /* no receiving record for it: it was applied already (records
         * leave only by commit, or by an abort the source never sends for a
         * committed transaction) */
        cell->stats.ignored++;
    }
    cell_send(cell, BREAK_CELL_MSG_COMMIT_ACK, m->from_cell, NULL, m->entity, m->epoch, m->txn, m->nonce);
}

/* The nonce check is a safeguard: an ABORT naming a nonce can only meet a
 * stale record of the same transaction (the source never aborts the record
 * it committed), so removing that record instead would also be safe. */
static void cell_on_abort(BreakCell *cell, const BreakCellMsg *m) {
    CellRecord *r = cell_find(cell, m->entity);
    if (r && r->state == BREAK_CELL_ENTITY_RECEIVING && r->peer == m->from_cell && r->txn == m->txn &&
        (m->nonce == 0u || m->nonce == r->nonce)) {
        cell_free(r);
    } else {
        cell->stats.ignored++;
    }
}

/* ---- source side ---- */

static CellRecord *cell_own_txn(BreakCell *cell, const BreakCellMsg *m) {
    CellRecord *r = cell_find(cell, m->entity);
    if (r && (r->state == BREAK_CELL_ENTITY_OFFERING || r->state == BREAK_CELL_ENTITY_COMMITTING) &&
        r->peer == m->from_cell && r->txn == m->txn) {
        return r;
    }
    return NULL;
}

static void cell_on_accept(BreakCell *cell, const BreakCellMsg *m) {
    CellRecord *r = cell_own_txn(cell, m);
    if (r && r->state == BREAK_CELL_ENTITY_OFFERING) {
        r->state = BREAK_CELL_ENTITY_COMMITTING;
        r->nonce = m->nonce;
        r->epoch++;
        cell->stats.handoffs_out++;
        cell_resend(cell, r);
        return;
    }
    if (r && r->nonce == m->nonce) return; /* duplicate accept of the committed record */
    /* an offer we no longer make (timed out, rejected, superseded or
     * committed with another record): release that record */
    cell_send(cell, BREAK_CELL_MSG_ABORT, m->from_cell, NULL, m->entity, m->epoch, m->txn, m->nonce);
}

static void cell_on_reject(BreakCell *cell, const BreakCellMsg *m) {
    CellRecord *r = cell_own_txn(cell, m);
    if (r && r->state == BREAK_CELL_ENTITY_OFFERING) {
        r->state = BREAK_CELL_ENTITY_OWNED;
        r->txn = 0u;
        cell->stats.rejected++;
    } else {
        cell->stats.ignored++;
    }
}

static void cell_on_commit_ack(BreakCell *cell, const BreakCellMsg *m) {
    CellRecord *r = cell_own_txn(cell, m);
    if (r && r->state == BREAK_CELL_ENTITY_COMMITTING && r->nonce == m->nonce) {
        cell_free(r);
    } else {
        cell->stats.ignored++;
    }
}

void break_cell_receive(BreakCell *cell, const BreakCellMsg *msg) {
    if (!cell || !msg) return;
    if (msg->to_cell != cell->cfg.cell_id || msg->from_cell == cell->cfg.cell_id ||
        msg->state_size > BREAK_CELL_STATE_MAX) {
        cell->stats.ignored++;
        return;
    }
    switch (msg->type) {
    case BREAK_CELL_MSG_OFFER: cell_on_offer(cell, msg); break;
    case BREAK_CELL_MSG_ACCEPT: cell_on_accept(cell, msg); break;
    case BREAK_CELL_MSG_REJECT: cell_on_reject(cell, msg); break;
    case BREAK_CELL_MSG_COMMIT: cell_on_commit(cell, msg); break;
    case BREAK_CELL_MSG_COMMIT_ACK: cell_on_commit_ack(cell, msg); break;
    case BREAK_CELL_MSG_ABORT: cell_on_abort(cell, msg); break;
    default: cell->stats.ignored++; break;
    }
}

void break_cell_tick(BreakCell *cell) {
    if (!cell) return;
    for (u32 i = 0; i < cell->cfg.capacity; i++) {
        CellRecord *r = &cell->records[i];
        if (!r->used || r->state == BREAK_CELL_ENTITY_OWNED) continue;
        if (r->state == BREAK_CELL_ENTITY_OFFERING && ++r->offer_age >= cell->cfg.offer_timeout_ticks) {
            cell_send(cell, BREAK_CELL_MSG_ABORT, r->peer, NULL, r->entity, r->epoch, r->txn, 0u);
            r->state = BREAK_CELL_ENTITY_OWNED;
            r->txn = 0u;
            cell->stats.aborted++;
            continue;
        }
        if (++r->since_send >= cell->cfg.retransmit_ticks) {
            cell_resend(cell, r);
            cell->stats.retransmits++;
        }
    }
}

bool break_cell_stats(BreakCell *cell, BreakCellStats *out_stats) {
    if (!cell || !out_stats) return false;
    *out_stats = cell->stats;
    return true;
}
