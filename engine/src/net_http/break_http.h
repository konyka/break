#pragma once
/* ==========================================================================
 *  break_http — Stage 5 subproject 2/3: a bounded HTTP/1.1 client over
 *  OpenSSL (docs/design/update_transport.md). It is the transport behind the
 *  update client's BreakUpdateFetchFn and the crash uploader.
 *
 *  Design rules (each one pinned by a test):
 *   - TLS is the default and verification is not optional. https needs a CA
 *     file; the system trust store is NOT consulted (the trust set is
 *     explicit). TLS 1.2 or newer, certificate and host name (or IP) checked.
 *     There is no insecure mode.
 *   - Plain http:// is accepted ONLY when every address the host resolves to
 *     is loopback (127.0.0.0/8, ::1), for tests and local development. Any
 *     other http URL fails with ERR_URL before a socket is created.
 *   - Redirects are never followed (a 3xx is a status error). No cookies, no
 *     proxy, no authentication, no keep-alive: one request per connection.
 *   - Every size is bounded by the caller's buffer: the status line plus
 *     headers are at most 8 KiB and 64 header lines; the body must fit the
 *     buffer or the call fails with ERR_TOO_BIG before reading it.
 *   - Framing is strict: a Content-Length is required (except 204), chunked
 *     transfer-encoding and any non-identity content-encoding are refused,
 *     duplicate Content-Length / Content-Range headers are refused, header
 *     lines must end CRLF with no folding, 1xx responses are refused, and
 *     bytes after the declared body are a protocol error.
 *   - Time is bounded: connect_timeout_ms for the TCP connect, then
 *     io_timeout_ms is the TOTAL for TLS handshake + request + response
 *     (a slow-drip server cannot hold the call open). DNS resolution itself
 *     (getaddrinfo) cannot be interrupted and is not covered; use an IP
 *     literal where that matters.
 *   - SIGPIPE is blocked for the duration on the calling thread and a
 *     SIGPIPE raised by this call is consumed, so a peer that closes early
 *     cannot kill the process.
 *
 *  POSIX only (sockets, poll). Windows is not implemented.
 * ========================================================================== */

#include <core/types.h>

#define BREAK_HTTP_DEFAULT_CONNECT_MS 5000u
#define BREAK_HTTP_DEFAULT_IO_MS 10000u
#define BREAK_HTTP_MAX_IO_MS 600000u
#define BREAK_HTTP_MAX_URL 2048u
#define BREAK_HTTP_MAX_HEAD 8192u
#define BREAK_HTTP_MAX_HEADERS 64u

typedef struct BreakHttpConfig {
    const char *ca_file;      /* PEM bundle; required for https, ignored for http */
    u32 connect_timeout_ms;   /* 0 = default */
    u32 io_timeout_ms;        /* 0 = default; total for handshake + request + response */
} BreakHttpConfig;

typedef enum BreakHttpError {
    BHTTP_OK = 0,
    BHTTP_ERR_URL,       /* bad URL, bad arguments, http to a non-loopback host, https without a CA */
    BHTTP_ERR_CONNECT,   /* no address accepted the connection */
    BHTTP_ERR_TLS,       /* handshake or certificate / host name verification failed */
    BHTTP_ERR_TIMEOUT,   /* the connect or total I/O budget ran out */
    BHTTP_ERR_STATUS,    /* a status other than the expected one (redirects included) */
    BHTTP_ERR_RANGE,     /* a range request was not answered with exactly the asked range */
    BHTTP_ERR_TOO_BIG,   /* the body is larger than the caller's buffer / the asked length */
    BHTTP_ERR_PROTOCOL   /* malformed, truncated or forbidden response framing */
} BreakHttpError;

const char *break_http_error_name(BreakHttpError e);

/* GET url, expecting 200 and a body of at most `cap` bytes. */
BreakHttpError break_http_get(const BreakHttpConfig *cfg, const char *url,
                              u8 *out, u64 cap, u64 *out_len);

/* GET url with "Range: bytes=offset-(offset+len-1)", expecting 206 whose
 * Content-Range is exactly that range and a body of exactly `len` bytes
 * (written to `out`, which must hold `len`). len must be > 0 and offset+len
 * must not overflow. A server that answers 200 (ignoring the range) is
 * BHTTP_ERR_RANGE. */
BreakHttpError break_http_get_range(const BreakHttpConfig *cfg, const char *url,
                                    u64 offset, u64 len, u8 *out);

/* POST body (content_type is a token/token media type). Any complete
 * well-formed response counts as BHTTP_OK and *status carries its code; the
 * caller decides what a 4xx means. The response body (at most resp_cap) goes
 * to `resp`. */
BreakHttpError break_http_post(const BreakHttpConfig *cfg, const char *url,
                               const void *body, usize body_len,
                               const char *content_type, u8 *resp, usize resp_cap,
                               usize *resp_len, int *status);

/* ---- adapters ------------------------------------------------------------ */

typedef struct BreakHttpUpdateCtx {
    BreakHttpConfig cfg;
    char base_url[256]; /* e.g. "https://updates.example.com/stable" (no trailing '/') */
} BreakHttpUpdateCtx;

/* Matches BreakUpdateFetchFn (update/break_update_client.h): fetches
 * <base_url>/objects/<object_name> with a Range request. object_name must be
 * a 64-character lowercase hex chunk hash; anything else is refused before a
 * connection is made. Returns true only for a complete, exact range. */
bool break_http_update_fetch(void *user, const char *object_name, u64 offset,
                             u64 len, u8 *out);

/* GET <base_url>/rollout -> "<digits>\n": the share of devices the release is
 * published to, in basis points (0..10000). The body is at most 16 bytes,
 * digits only with one optional final LF. This value is advisory input to
 * break_update_client_stage_rollout; a manifest is still verified offline. */
bool break_http_rollout_percent_bp(const BreakHttpConfig *cfg, const char *base_url,
                                   u32 *out_bp);
