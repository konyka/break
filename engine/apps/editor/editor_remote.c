/* BreakEditorRemote implementation — see editor_remote.h for the security
 * posture, the fail-closed rules, and the threading contract. The remote
 * path is TLS + CHALLENGE/AUTH-v2 (Task 2); use_tls=false is the
 * test-only plaintext seam.
 *
 * Shape: one STEP-mode reactor + one session manager + a bounded connection
 * table (capacity = max_connections, <= 32). Handlers run on the shell
 * thread inside break_session_manager_poll_adapter (called from
 * break_editor_remote_tick, which the shell calls once per frame), so every
 * doc mutation below routes through the SAME undoable command APIs the UI
 * uses (break_editor_doc_* / break_editor_undo|redo / a console core over
 * the same eval contract) — the command stack stays the single mutation
 * path and Ctrl+Z reverts remote mutations (test pin).
 *
 * Auth: with a PSK installed (required for use_tls=true) sessions become
 * AUTHENTICATED only through the break_session CHALLENGE/AUTH-v2 handshake.
 * The plaintext test seam (use_tls=false, no PSK) instead walks each session
 * NEW -> AUTHENTICATING -> AUTHENTICATED right after the OPENED event binds
 * it; editor_main never reaches it (--remote requires TLS + PSK).
 * remote_on_message refuses + closes any command on a session that is not
 * AUTHENTICATED.
 *
 * Connection table discovery: poll_adapter drains events into the manager
 * but does not enumerate live connections, so the table discovers keys two
 * ways — the message handler inserts the key on first dispatch, and the
 * tick's bounded forward probe over candidate key values adopts live ones
 * (keys are small monotonically increasing integers in the current
 * adapter; the manager answers BREAK_SESSION_UNKNOWN for anything it does
 * not track). See remote_table_sync(). */

#include "editor_remote.h"
#include "editor_shell_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_lua.h>
#include <editor/editor_protocol.h>

/* Key-material wipe the optimizer cannot drop: a plain memset right before
 * free()/return is a dead store and is removed at -O2. */
static void remote_wipe(void *p, size_t n) {
    volatile u8 *v = (volatile u8 *)p;
    while (n-- != 0u) {
        *v++ = 0u;
    }
}

#ifdef BREAK_ENABLE_SNOWFLAKE

#include <network/break_net_adapter.h>
#include <network/break_net_events.h>
#include <network/break_session.h>

#include <snow/acceptor.h>
#include <snow/endpoint.h>

#define EDITOR_REMOTE_MAX_CONNECTIONS 32u

typedef struct {
    u64 key;      /* BreakConnectionKey; 0 = empty slot */
    u32 state;    /* BreakSessionState */
    bool active;  /* slot in use */
} EditorRemoteConnRow;

/* Eval output capture: the remote's console core logs every line BOTH into
 * the shell's shared console ring (via editor_shell_log, the panel
 * precedent — visible to the local user, "lua| " prefix) and into this
 * fixed capture buffer so the EVAL response can carry the newest tail. */
#define EDITOR_REMOTE_EVAL_MAX_LINES BREAK_EDITOR_PROTO_EVAL_MAX_LINES
#define EDITOR_REMOTE_EVAL_LINE_BYTES 128u

typedef struct {
    char lines[EDITOR_REMOTE_EVAL_MAX_LINES][EDITOR_REMOTE_EVAL_LINE_BYTES];
    u16 count;
} EditorRemoteEvalCapture;

struct BreakEditorRemote {
    BreakEditorShell *shell;        /* borrowed */
    BreakEditorLuaConsole *console; /* owned (NULL = degraded eval path) */
    BreakNetReactor *reactor;       /* owned */
    BreakSessionManager *manager;   /* owned */
    snow_acceptor_t *acceptor;      /* owned */
    EditorRemoteConnRow rows[EDITOR_REMOTE_MAX_CONNECTIONS];
    u32 capacity;
    u32 conn_count;
    bool started;
    u16 bound_port;
    u64 poll_count;                 /* test pin: poll_adapter calls */
    EditorRemoteEvalCapture eval_capture;
    /* config copies (the caller's struct/strings are borrowed at create) */
    char bind_host[64];
    u16 cfg_port;
    char tls_cert[256];
    char tls_key[256];
    char tls_ca[256];
    bool use_tls;
    int tls_verify_peer;
    u32 rate_global_per_sec;
    u32 rate_global_burst;
    u32 rate_per_ip_per_minute;
    bool has_psk;
    bool auth_installed;            /* this remote owns the session auth domain */
    u8 psk[32];
    u8 key_id[8];
};

#ifdef BREAK_ENABLE_CRYPTO
/* Process-global key slot behind break_session_set_auth (the session auth
 * configuration is process-wide). The callback reads this static slot, not
 * the remote, so a clear that the library refuses (another manager still
 * holds non-NEW sessions) can never leave it pointing at freed memory:
 * destroy wipes the slot and the callback then fails closed. */
typedef struct {
    bool valid;
    u8 psk[32];
    u8 key_id[8];
} EditorRemoteAuthSlot;

static EditorRemoteAuthSlot g_editor_remote_auth;

static bool remote_auth_key(void *user, const u8 key_id[8], u8 out_psk[32]) {
    const EditorRemoteAuthSlot *slot = (const EditorRemoteAuthSlot *)user;
    u8 diff = 0u;
    u32 i;
    if (slot == NULL || !slot->valid) {
        return false;
    }
    for (i = 0u; i < 8u; i++) {
        diff |= (u8)(slot->key_id[i] ^ key_id[i]);
    }
    if (diff != 0u) {
        return false; /* unknown key id: fail closed */
    }
    memcpy(out_psk, slot->psk, 32u);
    return true;
}

static bool remote_auth_install(BreakEditorRemote *r) {
    if (g_editor_remote_auth.valid) {
        return false; /* one auth domain per process */
    }
    memcpy(g_editor_remote_auth.psk, r->psk, 32u);
    memcpy(g_editor_remote_auth.key_id, r->key_id, 8u);
    g_editor_remote_auth.valid = true;
    if (!break_session_set_auth(remote_auth_key, &g_editor_remote_auth)) {
        memset(&g_editor_remote_auth, 0, sizeof(g_editor_remote_auth));
        return false;
    }
    r->auth_installed = true;
    return true;
}

static void remote_auth_uninstall(BreakEditorRemote *r) {
    if (!r->auth_installed) {
        return;
    }
    memset(&g_editor_remote_auth, 0, sizeof(g_editor_remote_auth));
    (void)break_session_set_auth(NULL, NULL);
    r->auth_installed = false;
}
#endif

/* The plaintext seam (use_tls=false, no PSK) is the only path that marks
 * sessions AUTHENTICATED without AUTH v2. */
static bool remote_auto_auth(const BreakEditorRemote *r) {
    return !r->use_tls && !r->has_psk;
}

static void remote_plaintext_auth(BreakEditorRemote *r, u64 key) {
    if (break_session_manager_state(r->manager, key) == BREAK_SESSION_NEW) {
        (void)break_session_manager_begin_auth(r->manager, key);
        (void)break_session_manager_auth_succeeded(r->manager, key);
    }
}

/* ---------------- canonical little-endian payload lanes ---------------- */

static u16 proto_get16(const u8 *p) {
    return (u16)((u16)p[0] | ((u16)p[1] << 8u));
}

static void proto_put16(u8 *p, u16 v) { p[0] = (u8)v; p[1] = (u8)(v >> 8u); }

static void proto_put32(u8 *p, u32 v) {
    p[0] = (u8)v; p[1] = (u8)(v >> 8u); p[2] = (u8)(v >> 16u);
    p[3] = (u8)(v >> 24u);
}

static u32 proto_get32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8u) | ((u32)p[2] << 16u) |
           ((u32)p[3] << 24u);
}

/* ---------------- registry ----------------
 * The session manager borrows the break_net DEFAULT registry: the envelope
 * codec only consults break_net_message_registry_default(), and the editor
 * wire ids (4..13) are registered there (the documented codec boundary —
 * a manager-local registry that forgot an id would admit frames the codec
 * already accepted, so the manager must see the same table). Phase ANY +
 * version 1 matches the default registry's editor definitions; the host's
 * remote_on_message gate enforces AUTHENTICATED (and closes otherwise). */

/* ---------------- connection table ---------------- */

static EditorRemoteConnRow *remote_row_find(BreakEditorRemote *r, u64 key) {
    u32 i;
    for (i = 0u; i < r->capacity; i++) {
        if (r->rows[i].active && r->rows[i].key == key) {
            return &r->rows[i];
        }
    }
    return NULL;
}

static void remote_row_add(BreakEditorRemote *r, u64 key) {
    u32 i;
    if (key == 0u || remote_row_find(r, key) != NULL) {
        return;
    }
    for (i = 0u; i < r->capacity; i++) {
        if (!r->rows[i].active) {
            r->rows[i].active = true;
            r->rows[i].key = key;
            r->rows[i].state = (u32)break_session_manager_state(r->manager, key);
            r->conn_count++;
            return;
        }
    }
    /* table full: the reactor's own max_connections cap (same bound) makes
     * this unreachable; fail closed is the manager/reactor's job. */
}

/* Reconciles the table with manager truth: refresh states of tracked rows
 * (and drop them once the session is CLOSED). New keys are adopted where
 * they are authoritative — remote_observe_key() on the OPENED/CLOSED events
 * the tick drains below, and remote_on_message on first dispatch. There is
 * no enumeration API on the manager, and snow connection uids are large
 * (hash-derived), so a probe-the-keyspace scheme cannot work. */
static void remote_table_sync(BreakEditorRemote *r) {
    u32 i;
    for (i = 0u; i < r->capacity; i++) {
        EditorRemoteConnRow *row = &r->rows[i];
        BreakSessionState state;
        if (!row->active) {
            continue;
        }
        state = break_session_manager_state(r->manager, row->key);
        if (state == BREAK_SESSION_UNKNOWN || state == BREAK_SESSION_CLOSED) {
            row->active = false;
            row->key = 0u;
            row->state = 0u;
            r->conn_count--;
            continue;
        }
        if (state == BREAK_SESSION_NEW && remote_auto_auth(r)) {
            /* plaintext test seam: NEW -> AUTHENTICATING -> AUTHENTICATED */
            remote_plaintext_auth(r, row->key);
            state = break_session_manager_state(r->manager, row->key);
        }
        row->state = (u32)state;
    }
}

/* ---------------- response send helpers ---------------- */

/* Sends one response envelope: the per-id success response, or the RESULT
 * wrapper (id == BREAK_EDITOR_MSG_RESULT: status byte + optional payload). */
static bool remote_respond(BreakEditorRemote *r, u64 key, u16 id, u8 status,
                           const u8 *payload, size_t payload_size) {
    u8 buf[1u + BREAK_EDITOR_PROTO_MAX_PAYLOAD];
    const u8 *body = payload;
    size_t body_size = payload_size;
    if (id == BREAK_EDITOR_MSG_RESULT) {
        if (payload_size > BREAK_EDITOR_PROTO_MAX_PAYLOAD - 1u) {
            return false;
        }
        buf[0] = status;
        if (payload_size != 0u) {
            memcpy(buf + 1u, payload, payload_size);
        }
        body = buf;
        body_size = payload_size + 1u;
    }
    return break_net_reactor_send(r->reactor, key, id,
                                  BREAK_EDITOR_PROTO_VERSION, body,
                                  body_size) == BREAK_NET_SEND_OK;
}

/* Console-core log sink: every line lands in the shell's shared ring (the
 * panel's "lua| " prefix convention) AND in the eval capture (the response
 * tail — the capture stores the SAME prefixed text the ring carries, so the
 * remote client sees exactly what the local console shows). */
static void remote_console_log(void *ctx, const char *line) {
    BreakEditorRemote *r = (BreakEditorRemote *)ctx;
    EditorRemoteEvalCapture *cap;
    size_t len;
    if (r == NULL || line == NULL) {
        return;
    }
    editor_shell_log(r->shell, "lua| %s", line);
    cap = &r->eval_capture;
    if (cap->count == EDITOR_REMOTE_EVAL_MAX_LINES) {
        memmove(cap->lines[0], cap->lines[1],
                (EDITOR_REMOTE_EVAL_MAX_LINES - 1u) *
                    EDITOR_REMOTE_EVAL_LINE_BYTES);
        cap->count--;
    }
    len = strlen(line);
    if (len + 5u >= EDITOR_REMOTE_EVAL_LINE_BYTES) {
        len = EDITOR_REMOTE_EVAL_LINE_BYTES - 6u; /* bounded: prefix + text + NUL */
    }
    memcpy(cap->lines[cap->count], "lua| ", 5u);
    memcpy(cap->lines[cap->count] + 5u, line, len);
    cap->lines[cap->count][5u + len] = '\0';
    cap->count++;
}

/* ---------------- protocol handlers ----------------
 * Return true to keep the connection up (a response was sent), false to
 * fail closed (remote_on_message closes the session on a handler failure).
 * Malformed payloads are protocol errors: NO response, close.
 * Command failures on well-formed payloads answer RESULT invalid/failed. */

static bool remote_handle_describe(BreakEditorRemote *r, u64 key,
                                   const u8 *p, size_t size) {
    u8 rsp[7];
    BreakEditorDoc *doc;
    if (size != 0u) {
        return false;
    }
    (void)p;
    doc = break_editor_shell_doc(r->shell);
    proto_put16(rsp, (u16)BREAK_EDITOR_PROTO_VERSION);
    proto_put32(rsp + 2u, (u32)break_editor_doc_entity_count(doc));
    rsp[6] = break_editor_doc_is_dirty(doc) ? 1u : 0u;
    return remote_respond(r, key, BREAK_EDITOR_MSG_DESCRIBE, 0u, rsp,
                          sizeof(rsp));
}

static bool remote_handle_list(BreakEditorRemote *r, u64 key, const u8 *p,
                               size_t size) {
    u8 rsp[2u + BREAK_EDITOR_PROTO_MAX_PAYLOAD];
    BreakEditorDoc *doc;
    usize count, i;
    size_t off = 2u;
    u16 shown = 0u;
    if (size != 0u) {
        return false;
    }
    (void)p;
    doc = break_editor_shell_doc(r->shell);
    count = break_editor_doc_entity_count(doc);
    for (i = 0u; i < count; i++) {
        BreakEditorEntityId id;
        const char *name = NULL;
        size_t name_len;
        if (!break_editor_doc_entity_at(doc, i, &id, &name) || name == NULL) {
            return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                                  BREAK_EDITOR_PROTO_STATUS_FAILED, NULL, 0u);
        }
        name_len = strlen(name);
        if (off + 10u + name_len > sizeof(rsp)) {
            break; /* bounded: the response never exceeds the payload cap */
        }
        proto_put32(rsp + off, id.index);
        proto_put32(rsp + off + 4u, id.generation);
        off += 8u;
        proto_put16(rsp + off, (u16)name_len);
        off += 2u;
        memcpy(rsp + off, name, name_len);
        off += name_len;
        shown++;
    }
    proto_put16(rsp, shown);
    return remote_respond(r, key, BREAK_EDITOR_MSG_LIST, 0u, rsp, off);
}

static bool remote_handle_spawn(BreakEditorRemote *r, u64 key, const u8 *p,
                                size_t size) {
    BreakEditorDoc *doc = break_editor_shell_doc(r->shell);
    BreakEditorEntityId id;
    char name[BREAK_EDITOR_NAME_CAPACITY];
    const char *name_arg = NULL;
    u8 rsp[8];
    u16 name_len;
    if (size < 2u) {
        return false;
    }
    name_len = proto_get16(p);
    if ((size_t)name_len != size - 2u) {
        return false; /* malformed: trailing garbage or truncated name */
    }
    if (name_len > 0u) {
        if ((size_t)name_len >= BREAK_EDITOR_NAME_CAPACITY) {
            return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                                  BREAK_EDITOR_PROTO_STATUS_INVALID, NULL, 0u);
        }
        memcpy(name, p + 2u, name_len);
        name[name_len] = '\0';
        name_arg = name;
    }
    id = break_editor_doc_add_entity(doc, name_arg);
    if (!break_editor_entity_id_valid(id)) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_FAILED, NULL, 0u);
    }
    editor_shell_refresh_all(r->shell);
    proto_put32(rsp, id.index);
    proto_put32(rsp + 4u, id.generation);
    return remote_respond(r, key, BREAK_EDITOR_MSG_SPAWN, 0u, rsp,
                          sizeof(rsp));
}

static bool remote_parse_entity_id(const u8 *p, BreakEditorEntityId *out) {
    out->index = proto_get32(p);
    out->generation = proto_get32(p + 4u);
    return break_editor_entity_id_valid(*out);
}

static bool remote_handle_remove(BreakEditorRemote *r, u64 key, const u8 *p,
                                 size_t size) {
    BreakEditorDoc *doc = break_editor_shell_doc(r->shell);
    BreakEditorEntityId id;
    u8 rsp[1];
    if (size != 8u) {
        return false;
    }
    if (!remote_parse_entity_id(p, &id)) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_INVALID, NULL, 0u);
    }
    rsp[0] = break_editor_doc_remove_entity(doc, id) ? 1u : 0u;
    editor_shell_refresh_all(r->shell);
    return remote_respond(r, key, BREAK_EDITOR_MSG_REMOVE, 0u, rsp,
                          sizeof(rsp));
}

static bool remote_handle_rename(BreakEditorRemote *r, u64 key, const u8 *p,
                                 size_t size) {
    BreakEditorDoc *doc = break_editor_shell_doc(r->shell);
    BreakEditorEntityId id;
    char name[BREAK_EDITOR_NAME_CAPACITY];
    u8 rsp[1];
    u16 name_len;
    if (size < 10u) {
        return false;
    }
    if (!remote_parse_entity_id(p, &id)) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_INVALID, NULL, 0u);
    }
    name_len = proto_get16(p + 8u);
    if ((size_t)name_len != size - 10u) {
        return false;
    }
    if (name_len == 0u || (size_t)name_len >= BREAK_EDITOR_NAME_CAPACITY) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_INVALID, NULL, 0u);
    }
    memcpy(name, p + 10u, name_len);
    name[name_len] = '\0';
    rsp[0] = break_editor_doc_rename_entity(doc, id, name) ? 1u : 0u;
    editor_shell_refresh_all(r->shell);
    return remote_respond(r, key, BREAK_EDITOR_MSG_RENAME, 0u, rsp,
                          sizeof(rsp));
}

static bool remote_handle_set_field(BreakEditorRemote *r, u64 key,
                                    const u8 *p, size_t size) {
    BreakEditorDoc *doc = break_editor_shell_doc(r->shell);
    BreakEditorEntityId id;
    char comp[32];
    char field[32];
    u8 rsp[1];
    u16 comp_len, field_len;
    usize comp_count, ci;
    u32 component_id = 0u, field_index = 0u;
    bool comp_found = false, field_found = false;
    f32 value;
    u32 bits;
    size_t off;
    if (size < 10u) {
        return false;
    }
    if (!remote_parse_entity_id(p, &id)) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_INVALID, NULL, 0u);
    }
    comp_len = proto_get16(p + 8u);
    off = 10u;
    if ((size_t)comp_len > size - off) {
        return false;
    }
    if (comp_len == 0u || (size_t)comp_len >= sizeof(comp)) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_INVALID, NULL, 0u);
    }
    memcpy(comp, p + off, comp_len);
    comp[comp_len] = '\0';
    off += comp_len;
    if (size - off < 2u) {
        return false;
    }
    field_len = proto_get16(p + off);
    off += 2u;
    if ((size_t)field_len > size - off) {
        return false;
    }
    if (field_len == 0u || (size_t)field_len >= sizeof(field)) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_INVALID, NULL, 0u);
    }
    memcpy(field, p + off, field_len);
    field[field_len] = '\0';
    off += field_len;
    if (size - off != 4u) {
        return false; /* malformed: the f32 must be the exact tail */
    }
    bits = proto_get32(p + off);
    memcpy(&value, &bits, 4u);
    /* registry-gated name resolution (byte-wise, case-sensitive — the Lua
     * console record application rule) */
    comp_count = break_editor_doc_component_count(doc);
    for (ci = 0u; ci < comp_count && !comp_found; ci++) {
        BreakEditorComponentInfo info;
        u32 fi;
        if (!break_editor_doc_component_info(doc, ci, &info)) {
            continue;
        }
        if (strcmp(info.display_name, comp) != 0) {
            continue;
        }
        comp_found = true;
        component_id = info.component_id;
        for (fi = 0u; fi < info.field_count; fi++) {
            if (strcmp(info.fields[fi].name, field) == 0) {
                field_found = true;
                field_index = fi;
                break;
            }
        }
    }
    if (!comp_found || !field_found) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_INVALID, NULL, 0u);
    }
    rsp[0] = break_editor_doc_set_field_f32(doc, id, component_id, field_index,
                                            value)
                 ? 1u
                 : 0u;
    editor_shell_refresh_all(r->shell);
    return remote_respond(r, key, BREAK_EDITOR_MSG_SET_FIELD, 0u, rsp,
                          sizeof(rsp));
}

static bool remote_handle_undo_redo(BreakEditorRemote *r, u64 key,
                                    const u8 *p, size_t size, bool is_undo) {
    BreakEditorDoc *doc = break_editor_shell_doc(r->shell);
    u8 rsp[1];
    bool applied;
    if (size != 0u) {
        return false;
    }
    (void)p;
    applied = is_undo ? break_editor_undo(doc) : break_editor_redo(doc);
    rsp[0] = applied ? 1u : 0u;
    if (applied) {
        editor_shell_refresh_all(r->shell);
    }
    return remote_respond(r, key,
                          is_undo ? BREAK_EDITOR_MSG_UNDO
                                  : BREAK_EDITOR_MSG_REDO,
                          0u, rsp, sizeof(rsp));
}

static bool remote_handle_eval(BreakEditorRemote *r, u64 key, const u8 *p,
                               size_t size) {
    u16 text_len;
    char *text;
    bool ok;
    u8 rsp[3u + BREAK_EDITOR_PROTO_MAX_PAYLOAD];
    size_t off;
    u16 i, written = 0u;
    if (size < 2u) {
        return false;
    }
    text_len = proto_get16(p);
    if ((size_t)text_len != size - 2u) {
        return false;
    }
    if ((u32)text_len > BREAK_EDITOR_LUA_INPUT_MAX_BYTES) {
        /* the input exceeds the console's own 4096 B bound: a command
         * failure (RESULT invalid), NOT a protocol error — the connection
         * stays up (fail-closed is reserved for malformed wire data). */
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_INVALID, NULL, 0u);
    }
    if (r->console == NULL) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_FAILED, NULL, 0u);
    }
    text = (char *)malloc((size_t)text_len + 1u);
    if (text == NULL) {
        return remote_respond(r, key, BREAK_EDITOR_MSG_RESULT,
                              BREAK_EDITOR_PROTO_STATUS_FAILED, NULL, 0u);
    }
    memcpy(text, p + 2u, text_len);
    text[text_len] = '\0';
    /* Same console core contract as the panel: same 4096 B cap, same
     * sandbox, failed eval => bounded error lines, zero partial record
     * application. We ARE the shell thread (the handler runs inside
     * poll_adapter from break_editor_remote_tick), so the owner-thread rule
     * holds by construction. */
    r->eval_capture.count = 0u;
    editor_shell_log(r->shell, "lua| > %s", text);
    ok = break_editor_lua_eval(r->console, text);
    free(text);
    editor_shell_refresh_all(r->shell);
    /* response: ok/u8 + line_count/u16 + per-line {len/u16, bytes} (bounded) */
    rsp[0] = ok ? 1u : 0u;
    off = 3u;
    for (i = 0u; i < r->eval_capture.count; i++) {
        usize len = strlen(r->eval_capture.lines[i]);
        if (off + 2u + len > sizeof(rsp)) {
            break; /* bounded: the response never exceeds the payload cap */
        }
        proto_put16(rsp + off, (u16)len);
        off += 2u;
        memcpy(rsp + off, r->eval_capture.lines[i], len);
        off += len;
        written++;
    }
    proto_put16(rsp + 1u, written);
    return remote_respond(r, key, BREAK_EDITOR_MSG_EVAL, 0u, rsp, off);
}

static bool remote_dispatch(BreakEditorRemote *r, BreakConnectionKey connection,
                            const BreakNetOwnedMessage *message);

/* Single dispatch entry registered for every editor message id. */
static bool remote_on_message(BreakConnectionKey connection,
                              const BreakNetOwnedMessage *message,
                              void *user_data) {
    BreakEditorRemote *r = (BreakEditorRemote *)user_data;
    bool ok;
    remote_row_add(r, connection); /* first dispatch discovers the key */
    if (remote_auto_auth(r)) {
        remote_plaintext_auth(r, connection);
    }
    /* Authorization gate: editor ids are PHASE_ANY in the default registry,
     * so the host refuses every command on a session that has not completed
     * AUTH v2 (or the plaintext test seam) — and, like every handler
     * failure, closes the session: the manager only auto-closes a failed
     * AUTH handler, so the close is explicit here (fail closed). */
    ok = break_session_manager_state(r->manager, connection) ==
             BREAK_SESSION_AUTHENTICATED &&
         remote_dispatch(r, connection, message);
    if (!ok) {
        (void)break_session_manager_close(r->manager, connection, 0u);
    }
    return ok;
}

static bool remote_dispatch(BreakEditorRemote *r, BreakConnectionKey connection,
                            const BreakNetOwnedMessage *message) {
    const u8 *p = (const u8 *)message->data;
    size_t size = message->size;
    if (message->protocol_version != BREAK_EDITOR_PROTO_VERSION) {
        return false; /* fail closed */
    }
    switch (message->message_id) {
    case BREAK_EDITOR_MSG_DESCRIBE:
        return remote_handle_describe(r, connection, p, size);
    case BREAK_EDITOR_MSG_LIST:
        return remote_handle_list(r, connection, p, size);
    case BREAK_EDITOR_MSG_SPAWN:
        return remote_handle_spawn(r, connection, p, size);
    case BREAK_EDITOR_MSG_REMOVE:
        return remote_handle_remove(r, connection, p, size);
    case BREAK_EDITOR_MSG_RENAME:
        return remote_handle_rename(r, connection, p, size);
    case BREAK_EDITOR_MSG_SET_FIELD:
        return remote_handle_set_field(r, connection, p, size);
    case BREAK_EDITOR_MSG_UNDO:
        return remote_handle_undo_redo(r, connection, p, size, true);
    case BREAK_EDITOR_MSG_REDO:
        return remote_handle_undo_redo(r, connection, p, size, false);
    case BREAK_EDITOR_MSG_EVAL:
        return remote_handle_eval(r, connection, p, size);
    default:
        return false;
    }
}

/* ---------------- lifecycle ---------------- */

BreakEditorRemote *break_editor_remote_create(
    BreakEditorShell *shell, const BreakEditorRemoteConfig *cfg) {
    BreakEditorRemote *r;
    const char *host;
    BreakSessionConfig session_config;
    BreakNetReactorConfig reactor_config;
    static const u16 k_handler_ids[] = {
        BREAK_EDITOR_MSG_DESCRIBE, BREAK_EDITOR_MSG_LIST,
        BREAK_EDITOR_MSG_SPAWN,    BREAK_EDITOR_MSG_REMOVE,
        BREAK_EDITOR_MSG_RENAME,   BREAK_EDITOR_MSG_SET_FIELD,
        BREAK_EDITOR_MSG_UNDO,     BREAK_EDITOR_MSG_REDO,
        BREAK_EDITOR_MSG_EVAL};
    usize i;
    if (shell == NULL || cfg == NULL ||
        cfg->max_connections > EDITOR_REMOTE_MAX_CONNECTIONS) {
        return NULL;
    }
    r = (BreakEditorRemote *)calloc(1u, sizeof(*r));
    if (r == NULL) {
        return NULL;
    }
    r->shell = shell;
    r->capacity = cfg->max_connections != 0u ? cfg->max_connections
                                             : EDITOR_REMOTE_MAX_CONNECTIONS;
    host = cfg->bind_host != NULL ? cfg->bind_host : "127.0.0.1";
    if (strlen(host) >= sizeof(r->bind_host)) {
        free(r);
        return NULL;
    }
    memcpy(r->bind_host, host, strlen(host) + 1u);
    r->cfg_port = cfg->bind_port; /* 0 = ephemeral; the kernel-assigned port is read back after bind */
    r->use_tls = cfg->use_tls;
    r->tls_verify_peer = cfg->tls_verify_peer;
    r->rate_global_per_sec = cfg->rate_global_per_sec;
    r->rate_global_burst = cfg->rate_global_burst;
    r->rate_per_ip_per_minute = cfg->rate_per_ip_per_minute;
    if (cfg->tls_cert_file != NULL) {
        if (strlen(cfg->tls_cert_file) >= sizeof(r->tls_cert)) {
            free(r);
            return NULL;
        }
        memcpy(r->tls_cert, cfg->tls_cert_file,
               strlen(cfg->tls_cert_file) + 1u);
    }
    if (cfg->tls_key_file != NULL) {
        if (strlen(cfg->tls_key_file) >= sizeof(r->tls_key)) {
            free(r);
            return NULL;
        }
        memcpy(r->tls_key, cfg->tls_key_file, strlen(cfg->tls_key_file) + 1u);
    }
    if (cfg->tls_ca_file != NULL) {
        if (strlen(cfg->tls_ca_file) >= sizeof(r->tls_ca)) {
            free(r);
            return NULL;
        }
        memcpy(r->tls_ca, cfg->tls_ca_file, strlen(cfg->tls_ca_file) + 1u);
    }
    /* owned console core for the remote EVAL path: borrows the shell's doc,
     * logs through remote_console_log (shared ring + capture). */
    r->console = break_editor_lua_create(break_editor_shell_doc(shell),
                                         remote_console_log, r);
    reactor_config.drive_mode = BREAK_NET_DRIVE_STEP;
    reactor_config.logical_index = 0;
    reactor_config.max_connections = r->capacity;
    reactor_config.empty_connection_timeout_ms = 0;
    reactor_config.watchdog_interval_ms = 0u;
    reactor_config.step_timeout_ms = 0u;
    r->reactor = break_net_reactor_create(&reactor_config);
    memset(&session_config, 0, sizeof(session_config));
    session_config.max_sessions = r->capacity;
    session_config.first_session_id = 1u;
    session_config.registry = NULL; /* NULL => the default registry */
    r->manager = break_session_manager_create(&session_config);
    if (r->reactor == NULL || r->manager == NULL ||
        !break_session_manager_attach_reactor(r->manager, r->reactor)) {
        break_editor_remote_destroy(r);
        return NULL;
    }
    for (i = 0u; i < sizeof(k_handler_ids) / sizeof(k_handler_ids[0]); i++) {
        if (!break_session_manager_set_message_handler(
                r->manager, k_handler_ids[i], remote_on_message, r)) {
            break_editor_remote_destroy(r);
            return NULL;
        }
    }
    return r;
}

void break_editor_remote_destroy(BreakEditorRemote *r) {
    if (r == NULL) {
        return;
    }
    /* detach from the host shell first: the shell borrows the remote, so a
     * destroy without a detach would leave its tick driving freed memory
     * (the borrowed-pointer contract — the shell never owns the remote). */
    if (r->shell != NULL) {
        break_editor_shell_set_remote(r->shell, NULL);
    }
    if (r->reactor != NULL && r->started) {
        (void)break_net_reactor_stop(r->reactor, 1000u);
    }
    break_session_manager_destroy(r->manager);
    break_net_reactor_destroy(r->reactor);
    if (r->acceptor != NULL) {
        snow_acceptor_destroy(r->acceptor);
    }
#ifdef BREAK_ENABLE_CRYPTO
    /* after the manager is gone (its sessions no longer pin the global
     * auth configuration), release the process-global auth domain */
    remote_auth_uninstall(r);
#endif
    break_editor_lua_destroy(r->console);
    remote_wipe(r->psk, sizeof(r->psk));
    remote_wipe(r->key_id, sizeof(r->key_id));
    free(r);
}

bool break_editor_remote_set_psk(BreakEditorRemote *r, const uint8_t key_id[8],
                                 const uint8_t psk[32]) {
#ifdef BREAK_ENABLE_CRYPTO
    if (r == NULL || key_id == NULL || psk == NULL || r->started) {
        return false;
    }
    memcpy(r->key_id, key_id, sizeof(r->key_id));
    memcpy(r->psk, psk, sizeof(r->psk));
    r->has_psk = true;
    return true;
#else
    (void)r;
    (void)key_id;
    (void)psk;
    return false; /* no AUTH-v2 without break_crypto: TLS start fails closed */
#endif
}

bool break_editor_remote_start(BreakEditorRemote *r) {
    snow_endpoint_t *endpoint = NULL;
    snow_status_t status;
    if (r == NULL || r->started) {
        return false;
    }
    /* fail closed: TLS needs cert + key (readability is checked by
     * break_net_reactor_set_tls below) AND the AUTH-v2 PSK — there is no
     * unauthenticated TLS command path */
    if (r->use_tls && (r->tls_cert[0] == '\0' || r->tls_key[0] == '\0' ||
                       !r->has_psk)) {
        return false;
    }
    if (snow_endpoint_create(&endpoint) != SNOW_OK) {
        return false;
    }
    status = snow_endpoint_set_host(endpoint, r->bind_host);
    if (status == SNOW_OK) {
        status = snow_endpoint_set_port(endpoint, (int)r->cfg_port);
    }
    if (status == SNOW_OK) {
        status = snow_acceptor_create(endpoint, &r->acceptor);
    }
    snow_endpoint_destroy(endpoint);
    if (status != SNOW_OK) {
        return false;
    }
    if (snow_acceptor_bind(r->acceptor, 1) != SNOW_OK) {
        goto fail;
    }
    if (r->use_tls) {
        BreakNetTlsConfig tls;
        tls.cert_file = r->tls_cert;
        tls.key_file = r->tls_key;
        tls.ca_file = r->tls_ca[0] != '\0' ? r->tls_ca : NULL;
        tls.verify_peer = r->tls_verify_peer;
        if (!break_net_reactor_set_tls(r->reactor, &tls)) {
            goto fail;
        }
    }
    if (r->rate_global_per_sec != 0u || r->rate_global_burst != 0u ||
        r->rate_per_ip_per_minute != 0u) {
        BreakNetRateLimitConfig rate;
        rate.global_accept_per_sec = r->rate_global_per_sec;
        rate.global_burst = r->rate_global_burst;
        rate.per_ip_per_minute = r->rate_per_ip_per_minute;
        if (!break_net_reactor_set_rate_limits(r->reactor, &rate)) {
            goto fail;
        }
    }
    if (!break_net_reactor_set_acceptor(r->reactor, r->acceptor)) {
        goto fail;
    }
#ifdef BREAK_ENABLE_CRYPTO
    /* installed before the first accept: the adapter issues the CHALLENGE
     * nonce only while session auth is configured */
    if (r->has_psk && !remote_auth_install(r)) {
        goto fail;
    }
#endif
    if (!break_net_reactor_start(r->reactor)) {
        goto fail;
    }
    r->bound_port =
        (u16)snow_endpoint_port(snow_acceptor_endpoint(r->acceptor));
    r->started = true;
    return true;
fail:
#ifdef BREAK_ENABLE_CRYPTO
    remote_auth_uninstall(r);
#endif
    (void)break_net_reactor_stop(r->reactor, 1000u);
    snow_acceptor_destroy(r->acceptor);
    r->acceptor = NULL;
    return false;
}

void break_editor_remote_tick(BreakEditorRemote *r) {
    BreakNetEvent event;
    u32 processed = 0u;
    if (r == NULL || !r->started) {
        return;
    }
    r->poll_count++;
    /* STEP-mode reactor: the shell thread steps the driver explicitly (no
     * host thread ever runs the network callbacks — they fire right here),
     * then drains the produced events into the session manager, which
     * invokes the protocol handlers on THIS thread. The drain is the same
     * poll_adapter loop, open-coded so the connection table can adopt keys
     * from the authoritative OPENED/CLOSED events (the manager has no
     * enumeration API). */
    (void)break_net_reactor_step(r->reactor, 0);
    while (processed < 32u &&
           break_net_reactor_poll_event(r->reactor, &event) ==
               BREAK_NET_EVENT_OK) {
        if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED) {
            remote_row_add(r, event.connection_key);
        }
        (void)break_session_manager_apply_adapter_event(r->manager, &event);
        break_net_event_release(&event);
        processed++;
    }
    /* finalize CLOSING -> CLOSED (the manager's low-level close
     * finalization — fail-closed sessions fully retire here, so the
     * connection table drops them on this tick's sync) */
    if (break_net_reactor_event_queue_empty(r->reactor)) {
        /* same gate as poll_adapter: finalize only once drained, so a
         * CLOSED entry never precedes an event still queued for it */
        (void)break_session_manager_poll(r->manager, 32u);
    }
    remote_table_sync(r);
}

bool break_editor_remote_is_running(const BreakEditorRemote *r) {
    return r != NULL && r->started;
}

uint16_t break_editor_remote_port(const BreakEditorRemote *r) {
    return r != NULL ? r->bound_port : 0u;
}

uint64_t break_editor_remote_admission_denied(const BreakEditorRemote *r) {
    if (r == NULL || r->reactor == NULL) {
        return 0u;
    }
    return break_net_reactor_admission_denied(r->reactor);
}

uint32_t break_editor_remote_connection_count(const BreakEditorRemote *r) {
    return r != NULL ? r->conn_count : 0u;
}

uint32_t break_editor_remote_connections_snapshot(const BreakEditorRemote *r,
                                                  uint64_t *out_keys,
                                                  uint32_t *out_states,
                                                  uint32_t capacity) {
    u32 i, n = 0u;
    if (r == NULL || out_keys == NULL || out_states == NULL ||
        capacity == 0u) {
        return 0u;
    }
    for (i = 0u; i < r->capacity && n < capacity; i++) {
        if (r->rows[i].active) {
            out_keys[n] = r->rows[i].key;
            out_states[n] = r->rows[i].state;
            n++;
        }
    }
    return n;
}

/* Test accessors beyond the brief's pinned surface: poll_count pins the
 * per-frame tick wiring (poll_adapter runs exactly once per tick), and
 * session_id exposes the manager's stable per-connection id for the
 * snapshot rows. */
u64 break_editor_remote_poll_count(const BreakEditorRemote *r) {
    return r != NULL ? r->poll_count : 0u;
}

void *break_editor_remote_manager_for_test(BreakEditorRemote *r) {
    return r != NULL ? (void *)r->manager : NULL;
}

u64 break_editor_remote_session_id(const BreakEditorRemote *r, u64 key) {
    if (r == NULL || r->manager == NULL) {
        return 0u;
    }
    return break_session_manager_session_id(r->manager, key);
}

#else /* !BREAK_ENABLE_SNOWFLAKE — full stub surface (remote unavailable) */

struct BreakEditorRemote {
    int unused;
};

BreakEditorRemote *break_editor_remote_create(
    BreakEditorShell *shell, const BreakEditorRemoteConfig *cfg) {
    (void)shell;
    (void)cfg;
    return NULL;
}

void break_editor_remote_destroy(BreakEditorRemote *r) { (void)r; }

bool break_editor_remote_start(BreakEditorRemote *r) {
    (void)r;
    return false;
}

void break_editor_remote_tick(BreakEditorRemote *r) { (void)r; }

bool break_editor_remote_is_running(const BreakEditorRemote *r) {
    (void)r;
    return false;
}

uint16_t break_editor_remote_port(const BreakEditorRemote *r) {
    (void)r;
    return 0u;
}

uint64_t break_editor_remote_admission_denied(const BreakEditorRemote *r) {
    (void)r;
    return 0u;
}

uint32_t break_editor_remote_connection_count(const BreakEditorRemote *r) {
    (void)r;
    return 0u;
}

uint32_t break_editor_remote_connections_snapshot(const BreakEditorRemote *r,
                                                  uint64_t *out_keys,
                                                  uint32_t *out_states,
                                                  uint32_t capacity) {
    (void)r;
    (void)out_keys;
    (void)out_states;
    (void)capacity;
    return 0u;
}

u64 break_editor_remote_poll_count(const BreakEditorRemote *r) {
    (void)r;
    return 0u;
}

u64 break_editor_remote_session_id(const BreakEditorRemote *r, u64 key) {
    (void)r;
    (void)key;
    return 0u;
}

bool break_editor_remote_set_psk(BreakEditorRemote *r, const uint8_t key_id[8],
                                 const uint8_t psk[32]) {
    (void)r;
    (void)key_id;
    (void)psk;
    return false;
}

#endif /* BREAK_ENABLE_SNOWFLAKE */

/* ---------------- editor_main --remote flag plumbing ---------------- */

static void remote_cli_error(char *err, size_t cap, const char *msg,
                             const char *arg) {
    if (err != NULL && cap != 0u) {
        snprintf(err, cap, "%s%s%s", msg, arg != NULL ? ": " : "",
                 arg != NULL ? arg : "");
    }
}

static int remote_hex_nibble(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

static bool remote_hex_decode(const char *hex, u8 *out, size_t out_len) {
    size_t i;
    if (strlen(hex) != out_len * 2u) {
        return false;
    }
    for (i = 0u; i < out_len; i++) {
        int hi = remote_hex_nibble(hex[2u * i]);
        int lo = remote_hex_nibble(hex[2u * i + 1u]);
        if (hi < 0 || lo < 0) {
            return false;
        }
        out[i] = (u8)((hi << 4) | lo);
    }
    return true;
}

/* Dev key file: exactly 32 raw bytes (a 33rd byte is an error). */
static bool remote_psk_file_read(const char *path, u8 out[32]) {
    u8 buf[33];
    size_t n;
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        return false;
    }
    /* unbuffered: no stdio heap buffer is left holding the key bytes */
    if (setvbuf(f, NULL, _IONBF, 0) != 0) {
        fclose(f);
        return false;
    }
    n = fread(buf, 1u, sizeof(buf), f);
    fclose(f);
    if (n != 32u) {
        remote_wipe(buf, sizeof(buf));
        return false;
    }
    memcpy(out, buf, 32u);
    remote_wipe(buf, sizeof(buf));
    return true;
}

bool break_editor_remote_cli_parse(int argc, char **argv,
                                   BreakEditorRemoteCli *out, char *err,
                                   size_t err_cap) {
    bool saw_remote_option = false;
    bool saw_psk_hex = false, saw_psk_file = false;
    int i;
    if (out == NULL || (argc > 0 && argv == NULL)) {
        remote_cli_error(err, err_cap, "invalid arguments", NULL);
        return false;
    }
    memset(out, 0, sizeof(*out));
    out->port = (uint16_t)BREAK_EDITOR_REMOTE_DEFAULT_PORT;
    for (i = 1; i < argc; i++) {
        const char *arg = argv[i];
        const char *value;
        if (arg == NULL) {
            continue;
        }
        if (strncmp(arg, "--remote", 8u) != 0) {
            if (out->scene_path == NULL) {
                out->scene_path = arg;
                continue;
            }
            remote_cli_error(err, err_cap, "unexpected argument", arg);
            goto fail;
        }
        if (strcmp(arg, "--remote") == 0) {
            out->enabled = true;
            continue;
        }
        saw_remote_option = true;
        if (strcmp(arg, "--remote-port") != 0 &&
            strcmp(arg, "--remote-cert") != 0 &&
            strcmp(arg, "--remote-key") != 0 &&
            strcmp(arg, "--remote-ca") != 0 &&
            strcmp(arg, "--remote-psk-hex") != 0 &&
            strcmp(arg, "--remote-psk-file") != 0 &&
            strcmp(arg, "--remote-key-id-hex") != 0) {
            /* never echo an inline "=value": it may be a PSK */
            const char *eq = strchr(arg, '=');
            if (eq != NULL && err != NULL && err_cap != 0u) {
                snprintf(err, err_cap, "unknown option: %.*s=<redacted>",
                         (int)(eq - arg), arg);
            } else {
                remote_cli_error(err, err_cap, "unknown option", arg);
            }
            goto fail;
        }
        if (i + 1 >= argc || argv[i + 1] == NULL) {
            remote_cli_error(err, err_cap, "missing value for", arg);
            goto fail;
        }
        value = argv[++i];
        if (strcmp(arg, "--remote-port") == 0) {
            char *end = NULL;
            unsigned long port = strtoul(value, &end, 10);
            if (value[0] == '\0' || end == NULL || *end != '\0' || port == 0u ||
                port > 65535u) {
                remote_cli_error(err, err_cap, "invalid --remote-port", value);
                goto fail;
            }
            out->port = (uint16_t)port;
        } else if (strcmp(arg, "--remote-cert") == 0) {
            out->cert_file = value;
        } else if (strcmp(arg, "--remote-key") == 0) {
            out->key_file = value;
        } else if (strcmp(arg, "--remote-ca") == 0) {
            out->ca_file = value;
        } else if (strcmp(arg, "--remote-psk-hex") == 0) {
            if (!remote_hex_decode(value, out->psk, sizeof(out->psk))) {
                remote_cli_error(err, err_cap,
                                 "--remote-psk-hex needs 64 hex digits", NULL);
                goto fail;
            }
            saw_psk_hex = true;
        } else if (strcmp(arg, "--remote-psk-file") == 0) {
            if (!remote_psk_file_read(value, out->psk)) {
                remote_cli_error(err, err_cap,
                                 "--remote-psk-file must hold exactly 32 bytes",
                                 value);
                goto fail;
            }
            saw_psk_file = true;
        } else {
            if (!remote_hex_decode(value, out->key_id, sizeof(out->key_id))) {
                remote_cli_error(err, err_cap,
                                 "--remote-key-id-hex needs 16 hex digits",
                                 NULL);
                goto fail;
            }
        }
    }
    if (!out->enabled) {
        if (saw_remote_option) {
            remote_cli_error(err, err_cap, "--remote-* options need --remote",
                             NULL);
            goto fail;
        }
        return true;
    }
    if (saw_psk_hex && saw_psk_file) {
        remote_cli_error(err, err_cap,
                         "use one of --remote-psk-hex / --remote-psk-file",
                         NULL);
        goto fail;
    }
    if (out->cert_file == NULL || out->key_file == NULL) {
        remote_cli_error(err, err_cap,
                         "--remote requires TLS: --remote-cert and --remote-key",
                         NULL);
        goto fail;
    }
    if (!saw_psk_hex && !saw_psk_file) {
        remote_cli_error(err, err_cap,
                         "--remote requires AUTH-v2: --remote-psk-hex or "
                         "--remote-psk-file",
                         NULL);
        goto fail;
    }
    out->has_psk = true;
    return true;
fail:
    remote_wipe(out->psk, sizeof(out->psk));
    out->has_psk = false;
    out->enabled = false;
    return false;
}

void break_editor_remote_cli_wipe(BreakEditorRemoteCli *cli) {
    if (cli != NULL) {
        remote_wipe(cli->psk, sizeof(cli->psk));
        cli->has_psk = false;
    }
}

void break_editor_remote_cli_to_config(const BreakEditorRemoteCli *cli,
                                       BreakEditorRemoteConfig *out) {
    if (out == NULL) {
        return;
    }
    memset(out, 0, sizeof(*out));
    out->bind_host = "127.0.0.1";
    out->max_connections = 4u;
    out->use_tls = true;
    out->rate_global_per_sec = BREAK_EDITOR_REMOTE_DEFAULT_RATE_PER_SEC;
    out->rate_global_burst = BREAK_EDITOR_REMOTE_DEFAULT_RATE_BURST;
    out->rate_per_ip_per_minute = BREAK_EDITOR_REMOTE_DEFAULT_RATE_PER_IP_PER_MIN;
    if (cli != NULL) {
        out->bind_port = cli->port;
        out->tls_cert_file = cli->cert_file;
        out->tls_key_file = cli->key_file;
        out->tls_ca_file = cli->ca_file;
        out->tls_verify_peer = cli->ca_file != NULL ? 1 : 0;
    }
}
