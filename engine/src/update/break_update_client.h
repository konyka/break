#pragma once
/* ==========================================================================
 *  break_update_client — Stage 5 Phase B: update client state machine + A/B
 *  slot layout (Task 1) + chunked downloader with byte-level resume (Task 2)
 *  + the stage/activate/unstage pipeline (Task 3). No network code exists in
 *  this phase (plan Global Constraints): the caller-supplied
 *  BreakUpdateFetchFn below is the sole transport seam.
 *
 *  Interface (plan 2026-10-24-stage5-update-client.md, verbatim):
 *
 *  On-disk layout under <root>: chunks/ (Phase A CAS), slots/A/, slots/B/,
 *  and canonical-text file "state" (≤64 KiB, atomically replaced):
 *    break-update-state-v1
 *    current: A|B|none
 *    staged: A|B|none            (slot whose materialization completed)
 *    pending: yes|no             (staged and activated, awaiting confirm)
 *    confirmed: yes|no
 *    current-version: M.m.p      (none when current=none)
 *    previous-version: M.m.p     (none when no previous)
 *    min-rollback-version: M.m.p (policy floor for rollback)
 *    resume-chunk: <sha256hex>|<offset>  OR  none
 *  Same canonical discipline as break-manifest-v1 (key order fixed as listed,
 *  LF, ASCII, unknown/malformed → parse fail).
 *
 *  Canonical enforcement details (all deviations → open NULL; NO heuristic
 *  repair — the plan's fail-closed constraint):
 *   - every byte is LF or printable ASCII 0x20-0x7E (no CR, TAB, NUL, bytes
 *     >= 0x7F); the text ends with exactly one final LF;
 *   - the nine keys appear in the fixed order listed above, each exactly
 *     once, separator ": " (one space), value runs to end of line;
 *   - current/staged values are exactly "A", "B", or "none"; pending and
 *     confirmed are exactly "yes" or "no";
 *   - versions use the manifest grammar (decimal components, no leading
 *     zeros, u32 range); current-version/previous-version additionally
 *     accept the literal "none"; min-rollback-version is ALWAYS a version
 *     triple (a fresh install starts at 0.0.0 — no floor);
 *   - resume-chunk is "none" or exactly 64 lowercase hex chars + '|' + a
 *     decimal u64 offset (no leading zeros, overflow-checked);
 *   - cross-field invariants (states no legal transition can produce are
 *     malformed): current=none IFF current-version=none; current=none ⇒
 *     previous-version=none (no live slot ⇒ no previous slot); never
 *     pending=yes AND confirmed=yes; pending=yes ⇒ current!=none;
 *     confirmed=yes ⇒ current!=none.
 *
 *  Write-ahead discipline: every state transition serializes the NEXT state
 *  to canonical text and commits it through PlatformAtomicWriter (fsync file
 *  → rename → fsync dir, see platform_fs.h) BEFORE the in-memory state (the
 *  visible effect) changes. A persist failure returns false with
 *  BREAK_UPDATE_CLIENT_IO and leaves the in-memory state untouched, so a
 *  transient IO error never wedges the client (the op can be retried). No
 *  writer tmp file survives any operation (commit/abort both clean up —
 *  pinned by test_break_update_client).
 *
 *  Fresh open: when <root>/state is absent the full layout (chunks/,
 *  slots/A/, slots/B/) is created and this initial state is persisted
 *  (byte-exact, pinned by the test):
 *    break-update-state-v1
 *    current: none
 *    staged: none
 *    pending: no
 *    confirmed: no
 *    current-version: none
 *    previous-version: none
 *    min-rollback-version: 0.0.0
 *    resume-chunk: none
 *
 *  Error discipline: fixed enum BreakUpdateClientError; NO attacker-
 *  controlled strings anywhere. last_error reflects the most recent
 *  confirm_boot/rollback/fetch_all call (BREAK_UPDATE_CLIENT_OK on success)
 *  and is OK initially after open; open itself reports failure as NULL only
 *  (no client exists to hold an error). confirm_boot without pending → false
 *  + STATE (state unchanged). rollback: staged slot exists → false + STATE (clean it
 *  first — Task 3 unstage is the only non-activating way); no previous slot
 *  (previous-version=none) → false + STATE; previous-version below
 *  min-rollback-version → false + POLICY. Rollback swaps current↔previous
 *  (slot AND version), clears pending, and sets confirmed=yes: the previous
 *  slot is by construction a boot that confirmed once already (it was
 *  current before), so the rolled-back boot is known-good (documented
 *  decision). current is DATA in the state file, not a symlink — slots are
 *  never renamed while live (plan Crash-safety constraint).
 * ========================================================================== */

#include <core/types.h>
#include <update/break_update.h> /* BreakUpdateManifest (Phase A header stays stable) */

typedef struct BreakUpdateClient BreakUpdateClient;
BreakUpdateClient *break_update_client_open(const char *root_path);  /* creates layout+initial state if absent; NULL on error/corrupt */
void break_update_client_destroy(BreakUpdateClient *c);

typedef enum BreakUpdateClientError {  /* fixed enum; no attacker-controlled strings */
    BREAK_UPDATE_CLIENT_OK = 0, BREAK_UPDATE_CLIENT_INVALID, BREAK_UPDATE_CLIENT_IO,
    BREAK_UPDATE_CLIENT_PARSE, BREAK_UPDATE_CLIENT_POLICY, BREAK_UPDATE_CLIENT_FETCH,
    BREAK_UPDATE_CLIENT_VERIFY, BREAK_UPDATE_CLIENT_STATE
} BreakUpdateClientError;
BreakUpdateClientError break_update_client_last_error(const BreakUpdateClient *c);

/* Queries (borrowed strings, fixed buffers): */
char break_update_client_current_slot(const BreakUpdateClient *c);   /* 'A'/'B'/'-' */
bool break_update_client_pending(const BreakUpdateClient *c);        /* staged, awaiting confirm */
bool break_update_client_confirmed(const BreakUpdateClient *c);
void break_update_client_current_version(const BreakUpdateClient *c, u32 out[3]);  /* 0.0.0 when none */

/* Boot lifecycle: */
bool break_update_client_confirm_boot(BreakUpdateClient *c);   /* pending → confirmed, persists first */
bool break_update_client_rollback(BreakUpdateClient *c);       /* swap current↔previous slot; policy:
    false when no previous slot, when previous-version < min-rollback-version, or when staged exists
    (must abort/clean staged first — documented); persists first, then flips */

/* ---- Task 2: chunked downloader with byte-level resume ---------------------
 *
 * Interface (plan 2026-10-24-stage5-update-client.md, verbatim): */

/* Caller-supplied ranged fetch of a remote object by name (this phase: object name ==
 * chunk sha256hex). out capacity ≥ len; false = transport failure (retryable).
 * offset+len overflow-checked by the client before calling. */
typedef bool (*BreakUpdateFetchFn)(void *user, const char *object_name,
                                   u64 offset, u64 len, u8 *out);

/* Downloads all manifest chunks missing from CAS, spooling each through
 * chunks/<hash>.part (byte-level resume via state resume-chunk = hash|offset),
 * verifying sha256 == manifest hash before store_put_chunk. Sequential, one
 * .part at a time. Returns true when every chunk is present in CAS.
 * false + last_error: FETCH (transport; progress kept — call again to resume),
 * VERIFY (hash mismatch; .part discarded), IO, STATE (corrupt resume → restarted clean). */
bool break_update_client_fetch_all(BreakUpdateClient *c, const BreakUpdateManifest *m,
                                   BreakUpdateFetchFn fetch, void *user);

/* Task 2 semantics (documented decisions; all pinned by test_break_update_client):
 *
 *  - Object identity: the fetch object name is the chunk's sha256 hex (the
 *    manifest chunk NAME field is a slot-relative path for Task 3 staging and
 *    plays no role here). All fetch ranges derive from the MANIFEST-declared
 *    chunk size — the transport is never asked for a size and its claims are
 *    never trusted: len = min(64 KiB, size - offset), so offset+len ≤ size ≤
 *    UINT64_MAX and no u64 overflow can occur by construction (checked before
 *    every call per the interface contract). No allocation is ever sized by
 *    the manifest chunk size during transfer (the spool buffer is a fixed 64
 *    KiB block); a >128 MiB chunk fails at store_put_chunk (the store's own
 *    cap) with IO, after spooling.
 *  - Order: a valid resume entry's chunk is continued FIRST (its entry would
 *    otherwise be clobbered by starting another chunk), then the manifest in
 *    order. Strictly sequential: at most one .part exists at any moment
 *    (created only after the state's resume entry names it, removed before
 *    the entry clears).
 *  - Write-ahead progress: starting a chunk persists resume-chunk=hash|0
 *    BEFORE the .part is created; every fetched block is appended + fflush'd
 *    BEFORE the new offset persists. A crash in the window leaves .part
 *    LONGER than the persisted offset — detected as corrupt on the next call
 *    (below): the chunk restarts clean. Crash-durable progress granularity is
 *    one block (fsync of .part is deliberately not done; the fail-closed
 *    detection covers process/power loss at the cost of re-fetching the
 *    in-flight block window).
 *  - Resume-entry triage at entry (state resume-chunk = H|O):
 *      H names a manifest chunk already in CAS  → stale (crash between
 *          store_put and entry-clear): .part removed, entry cleared, fetch_all
 *          CONTINUES (no error — a resumable partial state);
 *      H names a manifest chunk not in CAS, O ≤ chunk size, and the .part is
 *          consistent with O (absent iff O == 0, exact size otherwise — O ==
 *          size is valid: a fully-spooled chunk pending verify+store) →
 *          resumed at byte offset O;
 *      anything else (unknown hash, O > size, .part missing/short/long) →
 *          CORRUPT: .part removed, entry cleared (both persisted), false +
 *          STATE. The next call restarts the chunk from 0 — "restarted clean".
 *  - On resume the existing .part prefix is re-hashed into the streaming
 *    sha256 ctx (a prefix cannot be verified against the final digest; the
 *    bytes are trusted until completion, then the FULL chunk digest gates the
 *    store — VERIFY discards the .part and clears the entry, nothing enters
 *    CAS). store_put_chunk re-computes the hash, so the chunk lands under the
 *    manifest name by construction.
 *  - Errors: FETCH = the callback returned false (progress kept — the
 *    persisted offset and .part are consistent; call again to resume). VERIFY
 *    = digest mismatch (.part discarded, entry cleared). IO = local resource
 *    failure (store open, .part open/read/write/fflush, OOM, sha256 backend,
 *    state persist, store put, .part removal) — the in-memory state and the
 *    persisted entry stay consistent (a partially-written block self-heals
 *    via the corrupt-detection above on the next call). INVALID = NULL
 *    manifest or fetch (a NULL client returns false without an error slot).
 *    STATE = corrupt resume entry (already restarted clean on return).
 *  - fetch_all ignores the slot fields entirely (chunks/ is the shared CAS);
 *    a fresh state's resume-chunk: none line round-trips byte-exactly. */

/* ---- Task 3: stage → activate → unstage pipeline ----------------------------
 *
 * Interface (plan 2026-10-24-stage5-update-client.md, verbatim): */

/* Full pipeline: verify signature (pubkey) → compatible() policy (channel/platform/
 * current version from state) → fetch_all → materialize chunks into the INACTIVE slot
 * (each manifest chunk name → slots/<inactive>/files/<name>, via atomic writer;
 * names already manifest-validated; nested names create intermediate dirs via
 * platform_mkdir per component) → mark staged. Any failure: staged slot removed,
 * state unchanged except resume progress. */
bool break_update_client_stage(BreakUpdateClient *c, const BreakUpdateManifest *m,
                               const u8 pubkey[32], const char *channel, const char *platform,
                               BreakUpdateFetchFn fetch, void *user);
/* Atomically flip current → staged slot, pending=yes, confirmed=no, previous-* recorded.
 * Persists state BEFORE the flip becomes visible. False when no staged slot. */
bool break_update_client_activate(BreakUpdateClient *c);
/* Remove a staged (not yet activated) slot and clear it from state; false when none staged.
 * This is the ONLY way to clear a staged slot without activating it (rollback refuses
 * while staged exists). */
bool break_update_client_unstage(BreakUpdateClient *c);

/* Task 3 semantics (documented decisions; all pinned by test_break_update_client):
 *
 *  - Signature before EVERYTHING (cross-cutting review gate): stage verifies
 *    the manifest signature against pubkey first, then runs the compatible()
 *    policy, and only then may fetch_all invoke the transport. A VERIFY or
 *    POLICY failure performs ZERO fetch calls, ZERO disk writes, and ZERO
 *    state changes (test pins all three). last_error: VERIFY (signature),
 *    POLICY (channel/platform/min-version), STATE (a staged slot already
 *    exists — see below), INVALID (NULL m/pubkey/channel/platform/fetch).
 *  - "Current version from state": the compatible() current triple is the
 *    state's current-version. A FRESH client (current=none) is treated as
 *    source version 0.0.0 — the full policy still runs (channel + platform +
 *    manifest min-version ≤ 0.0.0), so only a payload whose min-version
 *    floor is 0.0.0 can provision a device that has no installed version.
 *  - Inactive slot: the non-current slot; with current=none the fixed choice
 *    is 'A'. stage REFUSES (false + STATE) while a staged slot exists: the
 *    plan designates unstage as the ONLY non-activating way to clear a staged
 *    slot, so re-staging a different payload = unstage + stage.
 *  - Slot tree layout: each manifest chunk name materializes at
 *    slots/<slot>/files/<name>; alongside it stage writes
 *    slots/<slot>/update-version, a one-line canonical "M.m.p\n" marker
 *    carrying the STAGED manifest's version. The Task-1-pinned state format
 *    has no staged-version field, so the version rides inside the slot;
 *    activate reads it back (missing/corrupt marker → false + IO, state
 *    untouched). The marker lives OUTSIDE files/ so no manifest name can
 *    collide with it. Slot file bytes come from break_update_store_get_chunk
 *    (verify-on-read re-hashes before handing bytes out).
 *  - Materialization CLEANS the target slot first (the retained tree from
 *    older cycles is removed), so a staged slot's files/ exactly matches the
 *    manifest — no stale files survive a re-stage. The clean runs only AFTER
 *    fetch_all succeeds: a transport failure never touches a slot (the
 *    retained previous version's bytes survive a failed download).
 *  - Failure atomicity: any failure after the clean removes the partial slot
 *    tree; state is unchanged except resume progress (the staged mark is the
 *    LAST write-ahead persist — a crash before it leaves staged=none and a
 *    partial slot the next stage's clean reclaims).
 *  - activate: pending=yes/confirmed=no/current=staged slot/current-version=
 *    marker version; previous-version records the outgoing current version
 *    (none on the very first activation — a fresh install has nothing to
 *    roll back to). Persist BEFORE the flip, as every transition.
 *  - unstage: persists staged=none FIRST (write-ahead), then removes the
 *    slot tree. A removal failure after the persist reports false + IO with
 *    staged already cleared — the inert leftover is reclaimed by the next
 *    stage's clean (documented; never wedges: rollback's staged-interlock no
 *    longer applies).
 *  - Rollback content caveat (inherent to 2-slot A/B): staging consumes the
 *    inactive slot, which with a live current IS the retained previous slot —
 *    that is why rollback refuses while staged exists. After a stage+unstage
 *    cycle the previous slot's bytes are gone; rollback remains a
 *    version-policy state flip (the plan's pointer-flip design: slots are
 *    never renamed while live). The previous slot's CONTENT is guaranteed
 *    only when no stage has targeted it since it was activated.
 *  - Tree removal uses ISO-C remove() on files and emptied directories
 *    (POSIX removes both; recursion depth ≤ 64, bounded by the manifest's
 *    ≤128-byte names). No new _WIN32 branches (plan Global Constraints);
 *    the open-time root path bound now covers the deepest join:
 *    "/slots/A/files/" + 128-byte name + the writer's ".tmpXXXXXX" + NUL. */
