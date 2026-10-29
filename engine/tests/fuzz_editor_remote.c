/* Mutation fuzzer for the editor remote session wire path.
 *
 * The remote editor session (apps/editor/editor_remote.c) is attacker-facing
 * once --remote is on: an authenticated peer can send ids 4..13 with any
 * payload. This drives that path in-process, with no sockets: mutated
 * envelopes are decoded by the real break_net envelope codec and then handed
 * to the real session manager (break_session_manager_apply_adapter_event),
 * which runs its registry/version/size checks, the host's authorization gate
 * and the protocol handlers against a live editor shell and document. The
 * host is ticked every message so responses are drained exactly as in the
 * editor.
 *
 * What it checks besides "no crash / no ASan / no UBSan report":
 *  - fail closed means zero document effect: whenever a message is not
 *    applied OK (invalid, handler-failed, stale, phase-rejected, unknown,
 *    duplicate) the document fingerprint (entities, ids, names, dirty flag,
 *    undo/redo depth, every registered component field) is unchanged;
 *  - the document stays well formed (names < capacity, ids resolvable);
 *  - the outliner still equals the document after every message;
 *  - the connection table and session table stay bounded and recover:
 *    closed sessions are replaced by fresh ones, never wedge the host.
 *
 * Message generation, by weight:
 *  - payload mutation: a valid request for a random id is built from live
 *    entity ids and names, then mutated structurally (byte writes, bit
 *    flips, boundary values on the u16/u32 length lanes, insert/delete that
 *    change the length, truncation, extension past the 4096 B bound), and
 *    re-encoded with a valid header so the handlers see the damaged payload;
 *  - wire mutation: the encoded frame itself is damaged (header or payload,
 *    truncated), so the codec's rejection paths run;
 *  - direct injection: arbitrary id/version/length events that never passed
 *    the codec, to hammer the session manager's own checks.
 * Every payload handed to the manager is an exact-size heap allocation, so
 * an over-read in a handler is an immediate ASan report.
 *
 * Scope limits: sessions are plaintext-seam sessions (auto-authenticated);
 * TLS and AUTH-v2 have their own tests. EVAL runs small mutated Lua snippets
 * under the console's existing instruction budget; Lua semantics are not
 * fuzzed beyond that. */

#include "editor_panels.h"
#include "editor_remote.h"

#include <core/log.h>
#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_doc.h>
#include <editor/editor_protocol.h>
#include <editor/editor_scene.h>
#include <network/break_net_envelope.h>
#include <network/break_net_events.h>
#include <network/break_net_message.h>
#include <network/break_session.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static unsigned long long rng_state = 0xED170ABCu;
static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}
static unsigned rnd_below(unsigned n) { return n == 0u ? 0u : rnd() % n; }

static const u32 interesting_u32[] = {
    0u, 1u, 2u, 7u, 8u, 9u, 10u, 127u, 128u, 129u, 255u, 256u,
    0x00000FFFu, 0x00001000u, 0x00001001u, 0x0000FFFEu, 0x0000FFFFu,
    0x00010000u, 0x7FFFFFFFu, 0x80000000u, 0xFFFFFFFEu, 0xFFFFFFFFu,
};
#define N_INTERESTING (sizeof(interesting_u32) / sizeof(interesting_u32[0]))

static void put16(u8 *p, u16 v) { p[0] = (u8)v; p[1] = (u8)(v >> 8u); }
static void put32(u8 *p, u32 v) {
    p[0] = (u8)v; p[1] = (u8)(v >> 8u); p[2] = (u8)(v >> 16u);
    p[3] = (u8)(v >> 24u);
}

#define MAX_PAYLOAD (BREAK_EDITOR_PROTO_MAX_PAYLOAD + 64u)
#define WIRE_MAX (BREAK_NET_ENVELOPE_HEADER_SIZE + MAX_PAYLOAD)
#define RECREATE_EVERY 160u

/* ---------------- harness ---------------- */

typedef struct Harness {
    BreakEditorShell *shell;
    BreakEditorRemote *remote;
    BreakSessionManager *manager;
    BreakEditorDoc *doc;
    u64 next_key;
    u64 key;          /* current session; 0 = none */
    u32 sequence;     /* per-session request sequence */
    char comp_name[32];
    char field_name[32];
} Harness;

static void harness_close(Harness *h) {
    break_editor_remote_destroy(h->remote);
    break_editor_shell_destroy(h->shell);
    h->remote = NULL;
    h->shell = NULL;
    h->manager = NULL;
    h->doc = NULL;
    h->key = 0u;
}

static bool harness_open(Harness *h) {
    BreakEditorRemoteConfig cfg;
    BreakEditorComponentInfo info;
    u32 i;
    h->key = 0u;
    h->shell = break_editor_shell_create_for_test();
    if (h->shell == NULL) {
        return false;
    }
    memset(&cfg, 0, sizeof(cfg));
    cfg.bind_host = "127.0.0.1";
    cfg.bind_port = 0u;
    cfg.max_connections = 8u;
    h->remote = break_editor_remote_create(h->shell, &cfg);
    if (h->remote == NULL || !break_editor_remote_start(h->remote)) {
        break_editor_remote_destroy(h->remote);
        break_editor_shell_destroy(h->shell);
        h->remote = NULL;
        h->shell = NULL;
        return false;
    }
    break_editor_shell_set_remote(h->shell, h->remote);
    /* SAVE/LOAD (ids 14/15) act on the configured scene path: give the
     * harness a real per-process file so both reach disk I/O. */
    {
        static char scene_path[256];
        if (scene_path[0] == '\0') {
            (void)snprintf(scene_path, sizeof(scene_path),
                           "/tmp/break_fuzz_editor_remote_%ld.bscn",
                           (long)getpid());
        }
        (void)break_editor_shell_set_scene_path(h->shell, scene_path);
    }
    h->manager = (BreakSessionManager *)break_editor_remote_manager_for_test(
        h->remote);
    h->doc = break_editor_shell_doc(h->shell);
    if (h->manager == NULL || h->doc == NULL ||
        !break_editor_doc_component_info(h->doc, 0u, &info)) {
        harness_close(h);
        return false;
    }
    snprintf(h->comp_name, sizeof(h->comp_name), "%s", info.display_name);
    snprintf(h->field_name, sizeof(h->field_name), "%s",
             info.field_count > 0u ? info.fields[0].name : "pos.x");
    for (i = 0u; i < 5u; i++) {
        char name[16];
        BreakEditorEntityId id;
        snprintf(name, sizeof(name), "seed_%u", i);
        id = break_editor_doc_add_entity(h->doc, name);
        if (break_editor_entity_id_valid(id) && (i & 1u) == 0u) {
            (void)break_editor_doc_add_component(h->doc, id, info.component_id);
        }
    }
    break_editor_shell_refresh(h->shell);
    return true;
}

/* ---------------- document fingerprint ---------------- */

typedef struct DocPrint {
    usize count;
    bool dirty;
    u32 undo;
    u32 redo;
    u64 hash;
    bool well_formed;
} DocPrint;

static u64 mix(u64 h, const void *data, usize n) {
    const u8 *p = (const u8 *)data;
    usize i;
    for (i = 0u; i < n; i++) {
        h = (h ^ p[i]) * 1099511628211ULL;
    }
    return h;
}

static DocPrint doc_print(BreakEditorDoc *doc) {
    DocPrint d;
    usize i, ci, comps;
    memset(&d, 0, sizeof(d));
    d.hash = 14695981039346656037ULL;
    d.well_formed = true;
    d.count = break_editor_doc_entity_count(doc);
    d.dirty = break_editor_doc_is_dirty(doc);
    d.undo = break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc));
    d.redo = break_editor_cmd_stack_redo_count(break_editor_doc_stack(doc));
    comps = break_editor_doc_component_count(doc);
    for (i = 0u; i < d.count; i++) {
        BreakEditorEntityId id;
        const char *name = NULL;
        if (!break_editor_doc_entity_at(doc, i, &id, &name) || name == NULL ||
            strlen(name) >= BREAK_EDITOR_NAME_CAPACITY ||
            !break_editor_entity_id_valid(id)) {
            d.well_formed = false;
            return d;
        }
        d.hash = mix(d.hash, &id, sizeof(id));
        d.hash = mix(d.hash, name, strlen(name) + 1u);
        for (ci = 0u; ci < comps; ci++) {
            BreakEditorComponentInfo info;
            u32 fi;
            if (!break_editor_doc_component_info(doc, ci, &info)) {
                continue;
            }
            for (fi = 0u; fi < info.field_count; fi++) {
                f32 v = 0.0f;
                u32 bits = 0u;
                bool present = break_editor_doc_get_field_f32(
                    doc, id, info.component_id, fi, &v);
                if (present) {
                    memcpy(&bits, &v, sizeof(bits));
                }
                d.hash = mix(d.hash, &present, sizeof(present));
                d.hash = mix(d.hash, &bits, sizeof(bits));
            }
        }
    }
    return d;
}

static bool doc_print_eq(const DocPrint *a, const DocPrint *b) {
    return a->count == b->count && a->dirty == b->dirty && a->undo == b->undo &&
           a->redo == b->redo && a->hash == b->hash;
}

/* ---------------- request generation ---------------- */

static const char *const k_eval_snippets[] = {
    "return 1+2",
    "brk.ecs.spawn()",
    "print('x')",
    "for i=1,3 do brk.ecs.spawn() end",
    "local t={} for i=1,50 do t[i]=i end return #t",
    "x = ",
    "return (",
    "error('boom')",
    "return tostring(nil)",
};
#define N_EVAL (sizeof(k_eval_snippets) / sizeof(k_eval_snippets[0]))

/* An entity id: usually a live one, sometimes junk. */
static void pick_entity_id(const Harness *h, u8 out[8]) {
    usize n = break_editor_doc_entity_count(h->doc);
    BreakEditorEntityId id = {0u, 0u};
    if (n != 0u && rnd_below(5u) != 0u) {
        const char *name = NULL;
        (void)break_editor_doc_entity_at(h->doc, rnd_below((unsigned)n), &id,
                                         &name);
    } else {
        id.index = interesting_u32[rnd_below(N_INTERESTING)];
        id.generation = interesting_u32[rnd_below(N_INTERESTING)];
    }
    put32(out, id.index);
    put32(out + 4u, id.generation);
}

static usize put_name(u8 *out, usize cap, bool allow_empty) {
    static const unsigned lens[] = {0u, 1u, 5u, 31u, 32u, 127u, 128u, 200u};
    unsigned len = rnd_below(3u) == 0u ? lens[rnd_below(8u)] : 1u + rnd_below(20u);
    unsigned i;
    if (!allow_empty && len == 0u) {
        len = 1u;
    }
    if (len + 2u > cap) {
        len = (unsigned)(cap - 2u);
    }
    put16(out, (u16)len);
    for (i = 0u; i < len; i++) {
        out[2u + i] = (u8)('a' + rnd_below(26u));
    }
    return 2u + len;
}

static usize put_str(u8 *out, const char *s) {
    usize n = strlen(s);
    put16(out, (u16)n);
    memcpy(out + 2u, s, n);
    return 2u + n;
}

/* Builds a VALID request payload for editor id `id`. */
static usize build_valid(const Harness *h, u16 id, u8 *out) {
    usize off = 0u;
    switch (id) {
    case BREAK_EDITOR_MSG_SPAWN:
        return put_name(out, MAX_PAYLOAD, true);
    case BREAK_EDITOR_MSG_REMOVE:
        pick_entity_id(h, out);
        return 8u;
    case BREAK_EDITOR_MSG_RENAME:
        pick_entity_id(h, out);
        return 8u + put_name(out + 8u, MAX_PAYLOAD - 8u, true);
    case BREAK_EDITOR_MSG_SET_FIELD: {
        u32 bits = interesting_u32[rnd_below(N_INTERESTING)];
        pick_entity_id(h, out);
        off = 8u;
        off += put_str(out + off, rnd_below(6u) == 0u ? "Nope" : h->comp_name);
        off += put_str(out + off, rnd_below(6u) == 0u ? "nope.z" : h->field_name);
        if (rnd_below(3u) == 0u) {
            bits = (u32)rnd(); /* arbitrary float bit pattern incl. NaN/Inf */
        }
        put32(out + off, bits);
        return off + 4u;
    }
    case BREAK_EDITOR_MSG_VIEW:
        /* mostly valid masks (bits 0..2), sometimes unknown bits */
        out[0] = rnd_below(5u) == 0u ? (u8)rnd() : (u8)rnd_below(8u);
        out[1] = (u8)rnd();
        return 2u;
    case BREAK_EDITOR_MSG_CAMERA_SET: {
        /* mostly in-range poses, sometimes an interesting bit pattern */
        static const f32 sane[7] = {0.0f, 1.0f, -2.0f, 0.3f, -0.4f, 5.0f, 1.0f};
        unsigned k;
        for (k = 0u; k < 7u; k++) {
            u32 bits;
            f32 v = sane[k] * (f32)(1u + rnd_below(3u));
            memcpy(&bits, &v, 4u);
            if (rnd_below(6u) == 0u) {
                bits = interesting_u32[rnd_below(N_INTERESTING)];
            }
            put32(out + k * 4u, bits);
        }
        return 28u;
    }
    case BREAK_EDITOR_MSG_EVAL: {
        const char *s = k_eval_snippets[rnd_below((unsigned)N_EVAL)];
        return put_str(out, s);
    }
    case BREAK_EDITOR_MSG_RESULT: {
        unsigned n = rnd_below(12u), i;
        for (i = 0u; i < n; i++) {
            out[i] = (u8)rnd();
        }
        return n;
    }
    default: /* DESCRIBE, LIST, UNDO, REDO: empty */
        return 0u;
    }
}

static usize mutate_payload(u8 *buf, usize len, unsigned nmut) {
    unsigned m;
    for (m = 0u; m < nmut; m++) {
        switch (rnd_below(8u)) {
        case 0: /* boundary value into a length-lane-shaped spot */
            if (len >= 2u) {
                u32 v = interesting_u32[rnd_below(N_INTERESTING)];
                usize pos = (usize)rnd_below((unsigned)len - 1u);
                if (len >= 4u && rnd_below(2u) == 0u) {
                    pos = (usize)rnd_below((unsigned)len - 3u);
                    put32(buf + pos, v);
                } else {
                    put16(buf + pos, (u16)v);
                }
            }
            break;
        case 1:
            if (len != 0u) {
                buf[rnd_below((unsigned)len)] = (u8)rnd();
            }
            break;
        case 2:
            if (len != 0u) {
                buf[rnd_below((unsigned)len)] ^= (u8)(1u << rnd_below(8u));
            }
            break;
        case 3: /* delete a span */
            if (len != 0u) {
                usize pos = rnd_below((unsigned)len);
                usize cut = 1u + rnd_below((unsigned)(len - pos));
                memmove(buf + pos, buf + pos + cut, len - pos - cut);
                len -= cut;
            }
            break;
        case 4: /* insert bytes */
            if (len + 8u < MAX_PAYLOAD) {
                usize pos = len != 0u ? rnd_below((unsigned)len + 1u) : 0u;
                usize add = 1u + rnd_below(8u), i;
                memmove(buf + pos + add, buf + pos, len - pos);
                for (i = 0u; i < add; i++) {
                    buf[pos + i] = (u8)rnd();
                }
                len += add;
            }
            break;
        case 5: /* truncate */
            if (len != 0u) {
                len = rnd_below((unsigned)len);
            }
            break;
        case 6: /* extend, sometimes past the 4096 B bound */
            {
                usize want = rnd_below(4u) == 0u
                                 ? (usize)BREAK_EDITOR_PROTO_MAX_PAYLOAD + 1u +
                                       rnd_below(32u)
                                 : len + 1u + rnd_below(64u);
                usize i;
                if (want > MAX_PAYLOAD) {
                    want = MAX_PAYLOAD;
                }
                for (i = len; i < want; i++) {
                    buf[i] = (u8)rnd();
                }
                if (want > len) {
                    len = want;
                }
            }
            break;
        default:
            if (len != 0u) {
                buf[rnd_below((unsigned)len)] = rnd_below(2u) ? 0xFFu : 0x00u;
            }
            break;
        }
    }
    return len;
}

/* ---------------- counters ---------------- */

typedef struct Stats {
    unsigned iters;
    unsigned encode_rejected;
    unsigned decode_rejected;
    unsigned applied;
    unsigned closed_by_message;
    unsigned sessions;
    unsigned session_table_stuck;
    unsigned result[8];
    unsigned evals;
    unsigned max_entities;
    /* per editor id 4..13: messages that reached the session manager, and how
     * many the handler accepted (apply OK) */
    unsigned reached[18];
    unsigned accepted[18];
    unsigned state_changing_ok; /* applied OK AND the document fingerprint moved */
} Stats;

/* ---------------- one message ---------------- */

/* Transport keys come from a small recycled pool: snow connection uids are
 * (list magic | slot), so a finished connection's key is reused by the next
 * one, and the session manager only reclaims a CLOSED entry when its key
 * opens again. Fresh keys every time would exhaust the 8-entry table, which
 * is a property of the harness, not of the product. */
#define KEY_POOL 6u

static bool ensure_session(Harness *h, Stats *st) {
    u32 attempt;
    BreakSessionState state;
    if (h->key != 0u) {
        state = break_session_manager_state(h->manager, h->key);
        if (state == BREAK_SESSION_AUTHENTICATED || state == BREAK_SESSION_NEW) {
            return true; /* the plaintext seam authenticates on first dispatch */
        }
    }
    for (attempt = 0u; attempt < KEY_POOL * 2u; attempt++) {
        BreakNetEvent ev;
        memset(&ev, 0, sizeof(ev));
        ev.type = BREAK_NET_EVENT_CONNECTION_OPENED;
        ev.connection_key = 1000u + (h->next_key++ % KEY_POOL);
        if (break_session_manager_apply_adapter_event(h->manager, &ev)) {
            h->key = ev.connection_key;
            h->sequence = 0u;
            st->sessions++;
            return true;
        }
        /* CLOSING entries finalize to CLOSED on the host tick */
        break_editor_remote_tick(h->remote);
    }
    st->session_table_stuck++;
    return false;
}

static bool feed(Harness *h, u16 id, u16 version, u32 sequence, const void *data,
                 usize size) {
    BreakNetMessageView view;
    BreakNetEvent ev;
    memset(&ev, 0, sizeof(ev));
    if (break_net_message_view_init(&view, id, version, sequence, data, size) !=
            BREAK_NET_MESSAGE_OK ||
        break_net_message_copy(&ev.message, &view) != BREAK_NET_MESSAGE_OK) {
        return false;
    }
    ev.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    ev.connection_key = h->key;
    (void)break_session_manager_apply_adapter_event(h->manager, &ev);
    break_net_event_release(&ev);
    return true;
}

static u16 pick_id(void) {
    unsigned r = rnd_below(16u);
    if (r < 12u) {
        return (u16)(4u + rnd_below(14u)); /* 4..17 */
    }
    if (r == 12u) return (u16)rnd_below(4u);      /* 0..3 */
    if (r == 13u) return (u16)(18u + rnd_below(8u));
    if (r == 14u) return 0xFFFFu;
    return (u16)rnd();
}

static u16 pick_version(void) {
    unsigned r = rnd_below(12u);
    if (r < 10u) return BREAK_EDITOR_PROTO_VERSION;
    if (r == 10u) return 0u;
    return (u16)rnd();
}

static u32 pick_sequence(Harness *h) {
    unsigned r = rnd_below(10u);
    if (r < 7u) return ++h->sequence;               /* in order */
    if (r == 7u) return h->sequence;                /* replay */
    if (r == 8u) return 0u;
    return interesting_u32[rnd_below(N_INTERESTING)];
}

/* Returns 0 ok, nonzero = invariant violation (printed). */
static int one_message(Harness *h, Stats *st, unsigned it) {
    static u8 payload[MAX_PAYLOAD];
    static u8 wire[WIRE_MAX];
    static u8 raw[WIRE_MAX];
    DocPrint before, after;
    BreakSessionApplyResult result;
    usize len;
    u16 id, version;
    u16 last_id = 0u;
    u32 sequence;
    unsigned mode = rnd_below(100u);

    if (!ensure_session(h, st)) {
        return 0;
    }
    before = doc_print(h->doc);
    if (!before.well_formed) {
        fprintf(stderr, "INVARIANT iter %u: document malformed before message\n", it);
        return 3;
    }

    id = pick_id();
    version = pick_version();
    sequence = pick_sequence(h);

    if (mode < 12u) {
        /* direct injection: arbitrary id/version/size, never decoded */
        len = rnd_below(4u) == 0u ? (usize)rnd_below(MAX_PAYLOAD)
                                  : (usize)rnd_below(40u);
        {
            usize i;
            for (i = 0u; i < len; i++) {
                payload[i] = (u8)rnd();
            }
        }
        if (id == BREAK_EDITOR_MSG_EVAL) {
            st->evals++;
        }
        last_id = id;
        if (!feed(h, id, version, sequence, len != 0u ? payload : NULL, len)) {
            return 0;
        }
    } else {
        BreakNetEnvelope env;
        BreakNetEnvelope dec;
        size_t wire_size = 0u;

        len = build_valid(h, id, payload);
        if (rnd_below(4u) != 0u) {
            len = mutate_payload(payload, len, 1u + rnd_below(4u));
        }
        memset(&env, 0, sizeof(env));
        env.protocol_version = version;
        env.message_id = id;
        env.sequence = sequence;
        env.payload = len != 0u ? payload : NULL;
        env.payload_size = len;
        if (break_net_envelope_encode(&env, wire, sizeof(wire), &wire_size) !=
            BREAK_NET_ENVELOPE_OK) {
            st->encode_rejected++;
            /* hand-build a frame the codec refused to encode, so the decoder
             * sees it (unknown id, oversize, bad version) */
            put32(raw, BREAK_NET_ENVELOPE_MAGIC);
            put16(raw + 4u, version);
            put16(raw + 6u, id);
            put16(raw + 8u, (u16)(rnd_below(4u) == 0u ? rnd() : 0u));
            put32(raw + 10u, sequence);
            put32(raw + 14u, (u32)len);
            if (len != 0u) {
                memcpy(raw + BREAK_NET_ENVELOPE_HEADER_SIZE, payload, len);
            }
            wire_size = BREAK_NET_ENVELOPE_HEADER_SIZE + len;
            memcpy(wire, raw, wire_size);
        }
        if (mode >= 70u) {
            /* wire-level damage: header or payload, sometimes truncated */
            unsigned m, nm = 1u + rnd_below(4u);
            for (m = 0u; m < nm && wire_size != 0u; m++) {
                usize pos = rnd_below(3u) != 0u
                                ? rnd_below((unsigned)(wire_size < 24u ? wire_size : 24u))
                                : rnd_below((unsigned)wire_size);
                switch (rnd_below(4u)) {
                case 0: wire[pos] = (u8)rnd(); break;
                case 1: wire[pos] ^= (u8)(1u << rnd_below(8u)); break;
                case 2:
                    if (wire_size >= 4u) {
                        put32(wire + (pos % (wire_size - 3u)),
                              interesting_u32[rnd_below(N_INTERESTING)]);
                    }
                    break;
                default: wire[pos] = 0xFFu; break;
                }
            }
            if (rnd_below(6u) == 0u && wire_size != 0u) {
                wire_size = 1u + rnd_below((unsigned)wire_size);
            }
        }
        memset(&dec, 0, sizeof(dec));
        if (break_net_envelope_decode(wire, wire_size, &dec) !=
            BREAK_NET_ENVELOPE_OK) {
            st->decode_rejected++;
            return 0;
        }
        if (dec.message_id == BREAK_EDITOR_MSG_EVAL) {
            st->evals++;
        }
        last_id = dec.message_id;
        if (!feed(h, dec.message_id, dec.protocol_version, dec.sequence,
                  dec.payload_size != 0u ? dec.payload : NULL, dec.payload_size)) {
            return 0;
        }
    }

    result = break_session_manager_last_result(h->manager);
    if (last_id >= 4u && last_id <= 17u) {
        st->reached[last_id]++;
        if (result == BREAK_SESSION_APPLY_OK) {
            st->accepted[last_id]++;
        }
    }
    st->result[(unsigned)result < 8u ? (unsigned)result : 7u]++;
    if (result == BREAK_SESSION_APPLY_OK) {
        st->applied++;
    }
    break_editor_remote_tick(h->remote);
    after = doc_print(h->doc);

    if (!after.well_formed) {
        fprintf(stderr, "INVARIANT iter %u: document malformed after message\n", it);
        return 3;
    }
    if (result == BREAK_SESSION_APPLY_OK && !doc_print_eq(&before, &after)) {
        st->state_changing_ok++;
    }
    if (result != BREAK_SESSION_APPLY_OK && !doc_print_eq(&before, &after)) {
        fprintf(stderr,
                "INVARIANT iter %u: message rejected (apply result %d) but the "
                "document changed: entities %zu->%zu dirty %d->%d undo %u->%u "
                "redo %u->%u hash %s\n",
                it, (int)result, before.count, after.count, (int)before.dirty,
                (int)after.dirty, before.undo, after.undo, before.redo,
                after.redo, before.hash == after.hash ? "same" : "differs");
        return 3;
    }
    if (break_editor_shell_outliner_count(h->shell) != after.count) {
        fprintf(stderr,
                "INVARIANT iter %u: outliner shows %zu rows, document has %zu "
                "(apply result %d)\n",
                it, break_editor_shell_outliner_count(h->shell), after.count,
                (int)result);
        return 3;
    }
    if (break_editor_remote_connection_count(h->remote) > 8u) {
        fprintf(stderr, "INVARIANT iter %u: connection table exceeded its bound\n",
                it);
        return 3;
    }
    if (after.count > st->max_entities) {
        st->max_entities = (unsigned)after.count;
    }
    if (break_session_manager_state(h->manager, h->key) !=
        BREAK_SESSION_AUTHENTICATED) {
        st->closed_by_message++;
    }
    return 0;
}

int main(int argc, char **argv) {
    unsigned iters = argc > 1 ? (unsigned)atoi(argv[1]) : 3000u;
    Harness h;
    Stats st;
    unsigned it;
    if (argc > 2) {
        rng_state = (unsigned long long)atoi(argv[2]);
    }
    log_set_level(LOG_FATAL);
    memset(&h, 0, sizeof(h));
    memset(&st, 0, sizeof(st));
    h.next_key = 0u;

    if (!harness_open(&h)) {
        fprintf(stderr, "harness setup failed (no loopback socket or shell?)\n");
        return 2;
    }
    for (it = 0u; it < iters; it++) {
        int rc;
        if (it != 0u && it % RECREATE_EVERY == 0u) {
            harness_close(&h);
            if (!harness_open(&h)) {
                fprintf(stderr, "re-open failed at iter %u\n", it);
                return 2;
            }
        }
        st.iters++;
        rc = one_message(&h, &st, it);
        if (rc != 0) {
            harness_close(&h);
            return rc;
        }
    }
    harness_close(&h);
    printf("fuzz done: %u iters, applied %u, codec-rejected encode %u decode %u, "
           "sessions %u (closed by a message %u, table stuck %u), evals %u, "
           "max entities %u\n",
           st.iters, st.applied, st.encode_rejected, st.decode_rejected,
           st.sessions, st.closed_by_message, st.session_table_stuck, st.evals,
           st.max_entities);
    {
        static const char *const names[18] = {
            "", "", "", "", "DESCRIBE", "LIST", "SPAWN", "REMOVE", "RENAME",
            "SET_FIELD", "UNDO", "REDO", "EVAL", "RESULT", "SAVE", "LOAD", "VIEW", "CAMERA_SET"};
        unsigned i;
        printf("per id (reached manager / handler accepted):");
        for (i = 4u; i <= 17u; i++) {
            printf(" %s %u/%u", names[i], st.reached[i], st.accepted[i]);
        }
        printf("\naccepted messages that changed the document: %u\n",
               st.state_changing_ok);
    }
    printf("apply results: ok %u unknown %u stale %u invalid %u phase %u "
           "duplicate %u handler_failed %u\n",
           st.result[0], st.result[1], st.result[2], st.result[3], st.result[4],
           st.result[5], st.result[6]);
    {
        char path[256];
        (void)snprintf(path, sizeof(path), "/tmp/break_fuzz_editor_remote_%ld.bscn",
                       (long)getpid());
        (void)remove(path);
        (void)snprintf(path, sizeof(path),
                       "/tmp/break_fuzz_editor_remote_%ld.bscn" BREAK_EDITOR_SIDECAR_SUFFIX,
                       (long)getpid());
        (void)remove(path);
    }
    return 0;
}
