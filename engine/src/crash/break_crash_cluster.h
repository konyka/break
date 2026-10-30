#pragma once
/* ==========================================================================
 *  break_crash_cluster — Stage 5 subproject 3, server side: group symbolized
 *  crashes into signatures, count them per build, and flag regressions
 *  (docs/design/crash_symbolization.md).
 *
 *  A signature is SHA-256 over the signal number and the first three frames
 *  (function name when resolved, module+offset otherwise). It does NOT contain
 *  the pid, tid, addresses or the build id, so the same defect in two builds
 *  or two ASLR layouts lands in one cluster. Unresolved frames fall back to
 *  module+offset, which is build specific: such crashes only cluster inside
 *  one build.
 *
 *  Build order is the order builds were REGISTERED (release order). A cluster
 *  marked fixed at build B regressed when a crash from a build registered
 *  after B arrives; reports from B or earlier builds do not count (old
 *  clients keep crashing after a fix ships).
 *
 *  The statistics live in one canonical text file (replaced atomically). The
 *  parser accepts only text that the serializer would produce byte for byte.
 *  Bounded: 4096 signatures (lowest count evicted), 1024 builds, 4096 remembered
 *  record hashes (duplicate uploads are not counted twice while remembered).
 * ========================================================================== */

#include <core/types.h>
#include <crash/break_crash_symbolize.h>

#define BREAK_CRASH_SIGNATURE_HEX 64u
#define BREAK_CRASH_CLUSTER_MAX_SIGNATURES 4096u
#define BREAK_CRASH_CLUSTER_MAX_BUILDS 1024u
#define BREAK_CRASH_CLUSTER_MAX_SEEN 4096u
#define BREAK_CRASH_CLUSTER_SYMBOL_MAX 127u
#define BREAK_CRASH_CLUSTER_FILE_MAX (4u * 1024u * 1024u)

/* Writes the 64-char lowercase hex signature + NUL. signo must be 1..64.
 * Uses at most the first three of `n` frames; n may be 0. */
bool break_crash_signature(int signo, const BreakCrashFrame *frames, u32 n, char out_hex[65]);

typedef struct BreakCrashClusterStore BreakCrashClusterStore;

/* Loads `path`. A missing file gives an empty store. NULL for an unreadable,
 * oversized or non-canonical file (never a partial load). */
BreakCrashClusterStore *break_crash_cluster_open(const char *path);
void break_crash_cluster_destroy(BreakCrashClusterStore *s); /* NULL no-op */

/* Appends a build id ([0-9a-z-]{1,64}) to the release order. False when
 * already registered, malformed, or 1024 builds exist. */
bool break_crash_cluster_register_build(BreakCrashClusterStore *s, const char *build_id);
bool break_crash_cluster_build_known(const BreakCrashClusterStore *s, const char *build_id);

typedef struct BreakCrashClusterOutcome {
    bool duplicate;          /* this record hash was already counted: nothing changed */
    bool new_signature;      /* first report of this signature */
    bool regression_started; /* this report flipped the cluster to regressed */
    bool unknown_build;      /* the build was not registered: nothing changed */
    u64 count;               /* the cluster's count after the call (0 when rejected) */
} BreakCrashClusterOutcome;

/* Counts one crash. record_hash_hex and signature_hex are 64 lowercase hex;
 * top_symbol is the first resolved frame name (NULL or "" for none; bytes
 * outside 0x21..0x7E become '?', cut at 127). False on malformed input or an
 * unregistered build (outcome->unknown_build). */
bool break_crash_cluster_add(BreakCrashClusterStore *s, const char *record_hash_hex,
                             const char *signature_hex, const char *build_id,
                             const char *top_symbol, BreakCrashClusterOutcome *out);

/* Marks a known signature fixed at a registered build and clears its
 * regressed flag. False when the signature or the build is unknown. */
bool break_crash_cluster_mark_fixed(BreakCrashClusterStore *s, const char *signature_hex,
                                    const char *build_id);

bool break_crash_cluster_find(const BreakCrashClusterStore *s, const char *signature_hex, u64 *out_count,
                              bool *out_regressed);
/* Expands a signature prefix (8..64 lowercase hex, as the report prints
 * them) to the full signature. False when the prefix is shorter than 8,
 * malformed, matches nothing, or matches more than one signature. */
bool break_crash_cluster_resolve_prefix(const BreakCrashClusterStore *s, const char *prefix, char out_hex[65]);
u32 break_crash_cluster_signature_count(const BreakCrashClusterStore *s);
u32 break_crash_cluster_build_count(const BreakCrashClusterStore *s);

/* Atomically replaces the file (fsync file, rename, fsync directory). */
bool break_crash_cluster_save(const BreakCrashClusterStore *s, const char *path);

/* Human readable report, count descending then signature ascending. Returns
 * the length written (NUL excluded), 0 when `cap` is too small. */
usize break_crash_cluster_report(const BreakCrashClusterStore *s, char *out, usize cap);

/* Serializes to the canonical text (exposed for the tests). Returns the
 * length, 0 when cap is too small. */
usize break_crash_cluster_serialize(const BreakCrashClusterStore *s, char *out, usize cap);
/* Parses canonical text (exposed for the tests); NULL on any deviation. */
BreakCrashClusterStore *break_crash_cluster_parse(const char *text, usize len);

/* Cross-process lock around a read-modify-write of one statistics file
 * (flock on "<path>.lock"). Release with _unlock. */
typedef struct BreakCrashClusterLock BreakCrashClusterLock;
BreakCrashClusterLock *break_crash_cluster_lock(const char *path);
void break_crash_cluster_unlock(BreakCrashClusterLock *l); /* NULL no-op */
