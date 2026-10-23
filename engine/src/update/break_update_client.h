#pragma once
/* ==========================================================================
 *  break_update_client — Stage 5 Phase B Task 1: update client state machine
 *  + A/B slot layout. NO download yet: fetch/stage/activate/unstage land in
 *  Tasks 2/3 and are deliberately NOT declared here. No network code exists
 *  in this phase (plan Global Constraints); the caller-supplied
 *  BreakUpdateFetchFn transport seam arrives with Task 2.
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
 *  confirm_boot/rollback call (BREAK_UPDATE_CLIENT_OK on success) and is OK
 *  initially after open; open itself reports failure as NULL only (no client
 *  exists to hold an error). confirm_boot without pending → false + STATE
 *  (state unchanged). rollback: staged slot exists → false + STATE (clean it
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
