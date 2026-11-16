# break_http: Basic authentication to the CONNECT proxy

Status: Done

## Context

`break_http` reaches https targets through an HTTP CONNECT proxy
(2026-11-16-http-connect-proxy.md), but a proxy that answers 407 cannot be
used. Many forward proxies require Basic credentials.

## Design

- `BreakHttpConfig.proxy_user` / `proxy_password`. Both NULL (or both empty)
  = no credentials. Exactly one set is `ERR_URL`.
- Both must be 1..255 bytes of printable ASCII (0x20..0x7e). The user must
  not contain `:`. Anything else is `ERR_URL` before any socket. Credentials
  without a `proxy` are `ERR_URL` too (a configuration error, not silently
  ignored).
- The CONNECT request gains `Proxy-Authorization: Basic
  base64(user ":" password)`. The header is sent only in CONNECT, never to
  the target and never for plain http (which ignores the proxy).
- A 407 is still `ERR_STATUS`; there is no retry and no challenge parsing.
- The proxy hop is plain TCP, so the credentials are visible on that hop.
  This is documented; an https proxy is still not supported.

## Tests (engine/tests/test_break_http.c, written first)

1. The CONNECT head carries the exact header (RFC 7617 example
   `Aladdin:open sesame` -> `QWxhZGRpbjpvcGVuIHNlc2FtZQ==`) and the target
   request has no `Proxy-Authorization`.
2. Lengths that exercise base64 padding (1, 2, 3 byte remainders) and the
   255-byte maximum encode correctly.
3. Invalid credentials are `ERR_URL` without a connection: only one set,
   `:` in the user, control or non-ASCII bytes, 256 bytes, credentials
   without a proxy.
4. Plain http with a proxy and credentials still goes direct and sends no
   proxy header.

## Verification

test_break_http, mutation run on the new code, ASan/TSan, the three full
build trees, banned-word check, then commit and push.

Result: 61/61. Mutation: 16 mutants, 1 survivor in the first run (the
empty-string check in `credential_ok` duplicated the caller's), removed;
all others killed. ASan+UBSan clean, TSan clean on three runs.

## Docs

break_http.h, docs/design/update_transport.md, docs/Implementation_Status.md,
docs/cross_engine/missing_capabilities.md.
