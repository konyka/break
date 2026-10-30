#pragma once
/* ==========================================================================
 *  break_crash_upload_http — Stage 5 subproject 3: the BreakCrashUploadFn that
 *  posts a redacted crash record to a crash server over break_http
 *  (docs/design/crash_symbolization.md).
 *
 *  Kept out of the break_crash archive on purpose: break_crash has no
 *  dependencies and exports no network symbols (pinned by
 *  test_break_crash_target_contract); the transport is opted into by linking
 *  this separate library.
 *
 *  The adapter reports success ONLY for HTTP 200 from the server. Anything
 *  else (connection or TLS failure, timeout, 4xx/5xx, an oversized or
 *  malformed answer) is false, so the spool counts an attempt and keeps the
 *  record pending until its attempt budget runs out. The transport rules of
 *  break_http apply unchanged: https needs a CA file, plain http only to a
 *  loopback address, no redirects.
 * ========================================================================== */

#include <core/types.h>
#include <net_http/break_http.h>

#define BREAK_CRASH_UPLOAD_HTTP_CONTENT_TYPE "application/x-break-crash"
#define BREAK_CRASH_UPLOAD_HTTP_MAX_BYTES 65536u

typedef struct BreakCrashUploadHttp {
    BreakHttpConfig cfg;
    char base_url[256]; /* e.g. "https://crash.example.com" (no trailing '/'); POSTs to <base_url>/crash */
} BreakCrashUploadHttp;

/* Matches BreakCrashUploadFn (crash/break_crash.h); `user` is a
 * const BreakCrashUploadHttp *. */
bool break_crash_upload_http(void *user, const void *record_bytes, usize len);
