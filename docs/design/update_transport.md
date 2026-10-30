# Update transport and reference server

Status: delivered 2026-10-30 (Stage 5 subproject 2, the online half). Three pieces, none linked into `engine`, `engine_demo`, `dxx_break` or `editor`:

- `break_http` (`engine/src/net_http/break_http.{h,c}`): a bounded HTTP/1.1 client over OpenSSL. Tests: `engine/tests/test_break_http.c` (37), `engine/tests/test_break_http_target_contract.cmake`.
- `break_update_server` (`engine/tools/break_update_server.c`): a small reference server so the whole path can run end to end. **Not a production deployment.**
- `break_update_e2e` (`engine/tests/break_update_e2e.c`) plus `engine/tests/test_break_update_e2e.cmake`: the release tool, the server and the real update client, run together.

The signature check is unchanged: the client verifies the manifest offline with the pinned public key before it requests a single object (`update_client.md`). The transport carries bytes; it is not trusted for anything the hashes and the signature do not already cover.

## 1. `break_http` rules

Each rule below has a test that fails when the rule is removed.

**TLS** (https): a CA file is required (`BHTTP_ERR_URL` without one); the system trust store is deliberately not used, so the trust set is explicit. TLS 1.2 or newer, peer verification on, the certificate checked against the URL's host name (or IP address), the verify result checked again after the handshake, no compression, no renegotiation. There is no insecure mode and no option to turn verification off. Tests use certificates generated in the test (right name, other name, expired, not yet valid, untrusted issuer), the shared fixture certificate, an IP literal against a name-only certificate, a plain-HTTP server answering a TLS client, and a nonexistent CA file.

**Plain http**: accepted only when every address the host resolves to is loopback (`127.0.0.0/8`, `::1`, v4-mapped loopback). Anything else fails with `BHTTP_ERR_URL` before a socket exists (checked against TEST-NET, private, public, `0.0.0.0`, `128.0.0.1`, IPv6 documentation and v4-mapped public addresses).

**URL**: at most 2047 bytes, printable ASCII only, no userinfo, no `#`, no backslash, port 1..65535, IPv6 literals validated with `inet_pton`, host characters restricted. 25 malformed forms are tested.

**No redirects, cookies, proxies, authentication or keep-alive**: one request per connection (`Connection: close`). A 3xx is a status error.

**Framing is strict**: the status line must be `HTTP/1.x ddd`; CRLF only (a bare CR or LF is refused), no NUL, no obsolete line folding, header names are tokens, at most 64 headers and 8 KiB of head. `Content-Length` is required (no read-until-close, no chunked), must be canonical decimal and unique. `Content-Range` must be unique and well-formed. `Transfer-Encoding` of any kind and any `Content-Encoding` other than `identity` are refused. 1xx responses are refused. Bytes after the declared body are a protocol error. The body must fit the caller's buffer, and that is checked from the header before the body is read (`BHTTP_ERR_TOO_BIG`).

**Ranges**: `break_http_get_range` sends `Range: bytes=a-b` and accepts only a `206` whose `Content-Range` is exactly that range and whose body is exactly that long. A `200` (the server ignored the range) is `BHTTP_ERR_RANGE`; a different window, a missing header, a short or long body, a malformed header are all errors. `offset + len` overflow and `len == 0` are refused before any connection.

**Time**: `connect_timeout_ms` bounds the TCP connect; `io_timeout_ms` is the TOTAL for handshake, request and response, so a server that drips one byte every 60 ms cannot hold the call open (tested: 20 bytes at 60 ms against a 600 ms budget ends in `TIMEOUT` well under 1.4 s). DNS resolution itself (`getaddrinfo`) cannot be interrupted and is not covered; use IP literals where that matters.

**SIGPIPE**: the call blocks SIGPIPE on the calling thread for its duration and consumes one it raised itself. Tested over plain HTTP and over TLS against a server that half-closes and then resets while the client is still writing 16 MiB; a handler installed for SIGPIPE must see zero deliveries. Over TLS only the signal mask protects (OpenSSL uses plain `write`); dropping the mask turns the TLS case red. Dropping only `MSG_NOSIGNAL` does not (the mask covers it), so `MSG_NOSIGNAL` is defence in depth, not independently tested.

**Adapters**: `break_http_update_fetch` matches `BreakUpdateFetchFn`, fetches `<base>/objects/<64 lowercase hex>` with a Range request, and refuses any other object name (traversal, upper case, wrong length) before connecting. `break_http_rollout_percent_bp` reads `<base>/rollout`: at most 16 bytes, digits with one optional final LF, canonical (no leading zero), 0..10000; any failure leaves the output untouched.

POSIX only (sockets, `poll`). Not built on Windows.

## 2. Reference server

`break_update_server --root <dir> --cert <pem> --key <pem> [--port N] [--print-port] [--rollout BP] [--truncate-request K] [--log FILE] [--max-requests N]`

Routes, exact match, GET only: `/manifest`, `/rollout` (only with `--rollout`), `/objects/<64 hex>` with a single `Range: bytes=a-b`. The file name is rebuilt from a validated 64-character hex string, so no request text is ever a path. TLS is required; plain http needs `--insecure-loopback` and a loopback bind address. Requests are served one at a time. `--truncate-request K` makes the K-th object response send half its body and close, and `--log` writes one line per request; both exist so the end-to-end test can observe resume. No access control, rate limiting, logging pipeline, CDN or release hot-reload: that is the deployment's job.

## 3. End-to-end test

`test_break_update_e2e` runs the real tool chain (`break_manifest_tool` keygen, build, sign; `break_manifest_verify`), the server over TLS, and the real update client over `break_http`:

1. the advertised rollout share is read;
2. a normal install ends byte-identical to the release (hashes compared) in slot A at version 1.2.3;
3. a device outside the rollout share is refused with zero object requests and zero files written (checked in the server's request log);
4. a connection cut mid-chunk fails as a fetch error, leaves the installed state untouched, and the retry resumes at byte 65536: the first 64 KiB block is requested exactly once, the second exactly twice (the cut one and the retry);
5. a chunk tampered on the server (same length, other bytes) is rejected by the hash check and installs nothing;
6. a manifest with a changed byte fails the signature check with zero object requests;
7. https with no CA file is refused before any request reaches the server.

Mutations that turn it red: the server ignoring Range, the client ignoring the persisted resume offset, the server truncating the wrong request.

## 4. Not delivered

- A production update service: deployment, CDN, access control, rate limiting, release pipeline, hot reload of the release on the server.
- HTTP/2, chunked transfer encoding, proxies, redirects, authentication, connection reuse.
- Windows support for `break_http` and the server; the Windows and macOS lanes were not run.
- Certificate revocation checking (CRL/OCSP), certificate pinning, and any custody of the offline signing key (unchanged from `update_client.md`).
- Interruptible DNS.
- Wiring into the editor or a game: nothing in this repository links `break_http` yet, so no shipped binary downloads updates.
