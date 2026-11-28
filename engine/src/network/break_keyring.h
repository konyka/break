#pragma once
/* Per-device AUTH v2 keyring: a fixed-capacity table of 8-byte key ids and
 * their 32-byte pre-shared keys, for break_net servers that issue one key
 * per device and need to rotate or revoke them while running.
 *
 * File format (shared with break_keygen and the editor's
 * --remote-keyring-file): one "<16 hex key id> <64 hex psk>" per line; lines
 * starting with '#' and empty lines are skipped; "\r\n" line ends are
 * accepted; key ids must not repeat. A file is at most
 * BREAK_KEYRING_MAX_FILE_BYTES.
 *
 * Loading is all-or-nothing: the whole text is parsed and validated into a
 * scratch table first, and only then is the ring made equal to it. Keys no
 * longer listed, or listed with a different psk, are removed (the revoked
 * callback runs for each after the key is removed from lookups; the
 * callback gets a copy of the id); new keys are added; unchanged keys stay.
 * On any failure the ring is unchanged and revoked is never called.
 *
 * break_keyring_resolve compares the key id against every slot in constant
 * time (no early exit on a match) and is BreakNetAuthKeyFn-compatible, with
 * the ring as the user pointer. Every copy of key bytes the library makes is
 * wiped before it is released.
 *
 * One owner, no locks: use a ring from one thread only (for a server, the
 * Logic thread that runs break_session). The break_session auth callback is
 * process-wide, so every break_session manager polled under that auth and
 * every load, add and remove on the ring must run on that same thread.
 *
 * A ring installed with break_session_set_auth(break_keyring_resolve, ring)
 * may be destroyed only after break_session_set_auth(NULL, NULL) returns
 * true. set_auth refuses while any session in the process is not NEW or an
 * auth operation is active; destroying the ring before that leaves the
 * process-wide callback reading freed memory. */

#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_KEYRING_MAX_KEYS 4096u
#define BREAK_KEYRING_MAX_FILE_BYTES (512u * 1024u)

typedef struct BreakKeyring BreakKeyring;

/* capacity 1..BREAK_KEYRING_MAX_KEYS; NULL on a bad capacity or OOM. */
BreakKeyring *break_keyring_create(u32 capacity);
/* Wipes every key, then frees. NULL is a no-op. */
void break_keyring_destroy(BreakKeyring *ring);

/* Adds key_id -> psk. False for NULL, a duplicate key_id or a full ring. */
bool break_keyring_add(BreakKeyring *ring, const u8 key_id[8], const u8 psk[32]);
/* Removes and wipes a key. False for NULL or an absent key_id. */
bool break_keyring_remove(BreakKeyring *ring, const u8 key_id[8]);
/* Keys in the ring; 0 for NULL. */
u32 break_keyring_count(const BreakKeyring *ring);

/* BreakNetAuthKeyFn-compatible lookup: ring is the BreakKeyring. Copies the
 * psk of key_id into out_psk and returns true; on a miss or a NULL argument
 * returns false and leaves out_psk untouched. */
bool break_keyring_resolve(void *ring, const u8 key_id[8], u8 out_psk[32]);

/* Called once per key_id a load removed or re-keyed, after it is gone from
 * lookups, so the caller can close that identity's sessions. key_id is a
 * copy that is wiped after the callback returns. The callback may resolve
 * keys but must not add or remove any. */
typedef void (*BreakKeyringRevokedFn)(void *user, const u8 key_id[8]);

typedef enum BreakKeyringLoadResult {
    BREAK_KEYRING_LOAD_OK = 0,
    BREAK_KEYRING_LOAD_UNREADABLE,
    BREAK_KEYRING_LOAD_MALFORMED, /* bad line, bad hex, duplicate id */
    BREAK_KEYRING_LOAD_TOO_LARGE, /* more keys than capacity, or the file
                                   * is over BREAK_KEYRING_MAX_FILE_BYTES */
    BREAK_KEYRING_LOAD_EMPTY      /* no key line */
} BreakKeyringLoadResult;

/* Reads the keyring file at path and makes the ring equal to it (see the
 * header comment). revoked may be NULL. The file is read unbuffered into a
 * heap buffer that is wiped before it is freed. */
BreakKeyringLoadResult break_keyring_load_file(BreakKeyring *ring, const char *path,
                                               BreakKeyringRevokedFn revoked, void *user);
/* Same as load_file on an in-memory buffer (len bytes, need not be NUL
 * terminated); used by callers that already read the file. */
BreakKeyringLoadResult break_keyring_load_text(BreakKeyring *ring, const char *text,
                                               usize len, BreakKeyringRevokedFn revoked,
                                               void *user);

/* Copies the i-th used key (0-based, insertion order) into id/psk; false
 * when i >= count. For callers that mirror the ring into their own store. */
bool break_keyring_key_at(const BreakKeyring *ring, u32 index, u8 key_id[8], u8 psk[32]);

#ifdef __cplusplus
} /* extern "C" */
#endif
