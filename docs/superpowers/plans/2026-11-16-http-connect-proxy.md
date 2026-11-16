# break_http: HTTPS through an HTTP CONNECT proxy

Status: Done

## Context

`break_http` (engine/src/net_http/break_http.c) connects straight to the
target. Networks that only allow outbound traffic through a forward proxy
cannot reach the update server or the crash collector.
`docs/cross_engine/missing_capabilities.md` lists the proxy as missing.

## Design

- `BreakHttpConfig.proxy`: `"http://host:port"` (path empty or `/`, no
  query, no userinfo). NULL or empty means no proxy. A malformed value is
  `BHTTP_ERR_URL` before any socket, for every target scheme.
- Only https targets use the proxy, through a `CONNECT` tunnel:
  1. TCP connect to the proxy within `connect_timeout_ms`. The proxy address
     does not have to be loopback; the target name is not resolved locally.
  2. Send `CONNECT host:port HTTP/1.1`, `Host: host:port`,
     `User-Agent: break-http/1`. IPv6 hosts are bracketed, the port is always
     written (443 when the URL has none).
  3. Read the proxy head (at most 8 KiB, same `parse_head` rules).
     1xx or malformed: `ERR_PROTOCOL`. Not 2xx: `ERR_STATUS`. Bytes after the
     head: `ERR_PROTOCOL` (they would otherwise be fed to TLS).
  4. TLS handshake as usual: CA, target host name, pins and CRL are checked
     against the target, so the proxy cannot impersonate it.
  5. The CONNECT exchange counts against `io_timeout_ms` (total budget).
- Plain http targets ignore the proxy and keep the loopback-only rule.
- No proxy authentication, no https proxy, no environment variables.

## Tests (engine/tests/test_break_http.c, written first)

A scripted proxy thread records the CONNECT head, sends a scripted reply
and, on 2xx, relays bytes to the scripted TLS server.

1. https GET through the proxy succeeds; the CONNECT head is exact and the
   target sees the normal request.
2. CONNECT line brackets IPv6 and writes the default port 443.
3. 403/407/502 from the proxy are `ERR_STATUS`; the target sees no
   connection.
4. Malformed head, 101, extra bytes after the head, oversized head, early
   close: `ERR_PROTOCOL`.
5. Bad proxy URLs are `ERR_URL` without a connection attempt.
6. Wrong CA or a name the certificate does not cover is still `ERR_TLS`
   through the proxy.
7. A silent proxy is `ERR_TIMEOUT` inside the io budget.
8. A refused proxy port is `ERR_CONNECT`; a non-loopback proxy is
   attempted (not refused as `ERR_URL`).
9. Plain http to loopback ignores the proxy.

## Verification

test_break_http, mutation run on the new code, ASan/TSan, the three full
build trees, banned-word check, then commit and push.

Result: 57/57. Mutation: 16 of 18 killed; the 2 survivors are equivalent
(without the head cap a zero-length read still ends as ERR_PROTOCOL; an
ignored CONNECT write error surfaces as the same code from the head read).
ASan+UBSan clean, TSan clean on three runs.

## Docs

Header comment in break_http.h, docs/design/update_transport.md,
docs/Implementation_Status.md, docs/cross_engine/missing_capabilities.md.
