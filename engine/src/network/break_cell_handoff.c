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
    BreakCellMsg *outbox;
    u32 outbox_count;
    u32 outbox_capacity;
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
    if (!cell->cfg.hold_outbox) {
        cell->cfg.send(cell->cfg.user, &m);
        return;
    }
    if (cell->outbox_count == cell->outbox_capacity) {
        u32 grown = cell->outbox_capacity ? cell->outbox_capacity * 2u : 16u;
        BreakCellMsg *next = (BreakCellMsg *)realloc(cell->outbox, (usize)grown * sizeof(*next));
        if (!next) return; /* the same as losing the message on the network */
        cell->outbox = next;
        cell->outbox_capacity = grown;
    }
    cell->outbox[cell->outbox_count++] = m;
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
    free(cell->outbox);
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

u32 break_cell_flush(BreakCell *cell) {
    u32 sent = 0u;
    if (!cell) return 0u;
    /* send may not call back into this cell, so the queue cannot grow here */
    for (; sent < cell->outbox_count; sent++) cell->cfg.send(cell->cfg.user, &cell->outbox[sent]);
    cell->outbox_count = 0u;
    return sent;
}

u32 break_cell_outbox_count(BreakCell *cell) { return cell ? cell->outbox_count : 0u; }

/* ---- snapshots ----
 * Little-endian: u32 magic, u32 version, u32 cell_id, u32 record count,
 * u64 next_txn, u64 next_nonce, then per record u32 state, peer, size,
 * since_send, offer_age, u64 entity, epoch, txn, nonce, size bytes of state;
 * finally a u64 FNV-1a hash of everything before it. Every step of FNV-1a
 * is a bijection on the hash state, so any single changed byte changes the
 * hash. */

#define SNAP_MAGIC 0x53434b42u /* 'BKCS' */
#define SNAP_VERSION 1u
#define SNAP_HEADER 32u
#define SNAP_RECORD 52u
#define SNAP_HASH 8u

static u64 snap_hash(const u8 *p, u32 n) {
    u64 h = 0xcbf29ce484222325ull;
    for (u32 i = 0; i < n; i++) {
        h ^= p[i];
        h *= 0x100000001b3ull;
    }
    return h;
}

static void snap_u32(u8 *p, u32 v) {
    for (u32 i = 0; i < 4u; i++) p[i] = (u8)(v >> (8u * i));
}

static void snap_u64(u8 *p, u64 v) {
    for (u32 i = 0; i < 8u; i++) p[i] = (u8)(v >> (8u * i));
}

static u32 snap_get_u32(const u8 *p) {
    u32 v = 0u;
    for (u32 i = 0; i < 4u; i++) v |= (u32)p[i] << (8u * i);
    return v;
}

static u64 snap_get_u64(const u8 *p) {
    u64 v = 0u;
    for (u32 i = 0; i < 8u; i++) v |= (u64)p[i] << (8u * i);
    return v;
}

u32 break_cell_snapshot_size(BreakCell *cell) {
    u64 n = SNAP_HEADER + SNAP_HASH;
    if (!cell) return 0u;
    for (u32 i = 0; i < cell->cfg.capacity; i++)
        if (cell->records[i].used) n += SNAP_RECORD + cell->records[i].size;
    return n > UINT32_MAX ? 0u : (u32)n;
}

bool break_cell_snapshot(BreakCell *cell, void *out, u32 capacity, u32 *out_size) {
    u8 *p = (u8 *)out;
    u32 size, at = SNAP_HEADER, count = 0u;
    if (!cell || !out || !out_size) return false;
    size = break_cell_snapshot_size(cell);
    if (size == 0u || capacity < size) return false;
    for (u32 i = 0; i < cell->cfg.capacity; i++) {
        const CellRecord *r = &cell->records[i];
        if (!r->used) continue;
        snap_u32(p + at, (u32)r->state);
        snap_u32(p + at + 4u, r->peer);
        snap_u32(p + at + 8u, r->size);
        snap_u32(p + at + 12u, r->since_send);
        snap_u32(p + at + 16u, r->offer_age);
        snap_u64(p + at + 20u, r->entity);
        snap_u64(p + at + 28u, r->epoch);
        snap_u64(p + at + 36u, r->txn);
        snap_u64(p + at + 44u, r->nonce);
        memcpy(p + at + SNAP_RECORD, r->data, r->size);
        at += SNAP_RECORD + r->size;
        count++;
    }
    snap_u32(p, SNAP_MAGIC);
    snap_u32(p + 4u, SNAP_VERSION);
    snap_u32(p + 8u, cell->cfg.cell_id);
    snap_u32(p + 12u, count);
    snap_u64(p + 16u, cell->next_txn);
    snap_u64(p + 24u, cell->next_nonce);
    snap_u64(p + at, snap_hash(p, at));
    *out_size = size;
    return true;
}

BreakCell *break_cell_restore(const BreakCellConfig *config, const void *snapshot, u32 size) {
    const u8 *p = (const u8 *)snapshot;
    BreakCell *cell;
    u32 count, at = SNAP_HEADER;
    if (!config || !p || size < SNAP_HEADER + SNAP_HASH) return NULL;
    if (snap_get_u64(p + size - SNAP_HASH) != snap_hash(p, size - SNAP_HASH)) return NULL;
    count = snap_get_u32(p + 12u);
    if (snap_get_u32(p) != SNAP_MAGIC || snap_get_u32(p + 4u) != SNAP_VERSION ||
        snap_get_u32(p + 8u) != config->cell_id || count > config->capacity)
        return NULL;
    cell = break_cell_create(config);
    if (!cell) return NULL;
    cell->next_txn = snap_get_u64(p + 16u);
    cell->next_nonce = snap_get_u64(p + 24u);
    for (u32 i = 0; i < count; i++) {
        CellRecord *r;
        u32 state, rsize;
        u64 entity;
        if (size - SNAP_HASH - at < SNAP_RECORD) goto bad;
        state = snap_get_u32(p + at);
        rsize = snap_get_u32(p + at + 8u);
        entity = snap_get_u64(p + at + 20u);
        if (state < BREAK_CELL_ENTITY_OWNED || state > BREAK_CELL_ENTITY_RECEIVING ||
            rsize > BREAK_CELL_STATE_MAX || size - SNAP_HASH - at - SNAP_RECORD < rsize ||
            cell_find(cell, entity))
            goto bad;
        r = cell_alloc(cell, entity);
        if (!r) goto bad;
        r->state = (BreakCellEntityState)state;
        r->peer = snap_get_u32(p + at + 4u);
        r->size = rsize;
        r->since_send = snap_get_u32(p + at + 12u);
        r->offer_age = snap_get_u32(p + at + 16u);
        r->epoch = snap_get_u64(p + at + 28u);
        r->txn = snap_get_u64(p + at + 36u);
        r->nonce = snap_get_u64(p + at + 44u);
        memcpy(r->data, p + at + SNAP_RECORD, rsize);
        at += SNAP_RECORD + rsize;
    }
    if (at != size - SNAP_HASH) goto bad;
    return cell;
bad:
    break_cell_destroy(cell);
    return NULL;
}
