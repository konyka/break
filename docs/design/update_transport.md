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
- Wiring into the editor or an application: nothing in this repository links `break_http` yet, so no shipped binary downloads updates.

## 补充（2026-11-15）：公钥钉扎

`BreakHttpConfig` 新增可选字段 `spki_sha256_pins` 和 `spki_pin_count`：`spki_pin_count` 个连续 32 字节摘要，每个是叶子证书 DER SubjectPublicKeyInfo 的 SHA-256。上文「不支持证书钉扎」一项由此改为已支持；吊销检查（CRL/OCSP）仍未实现。

- count 为 0 时行为与原来完全相同。
- 钉扎在握手、CA 校验和主机名校验全部通过之后才检查，只能收紧信任，不能替代 CA 校验：用错误 CA 加正确钉扎仍是 `ERR_TLS`。
- 叶子公钥不在列表中：`ERR_TLS`。握手超时仍报 `ERR_TIMEOUT`，不会变成钉扎失败。
- count 大于 `BREAK_HTTP_MAX_PINS`（8），或 count 非 0 而指针为 NULL：在建立任何 socket 之前返回 `ERR_URL`。
- 比较使用 `CRYPTO_memcmp`。明文 http（仅 loopback）忽略钉扎。

测试在 `engine/tests/test_break_http.c`：列表第二项匹配时通过、不匹配为 TLS 错误、钉扎不能绕过错误 CA、参数校验、握手超时、loopback http 忽略钉扎。

## 补充（2026-11-16）：证书吊销列表（CRL）

`BreakHttpConfig` 新增可选字段 `crl_file`（PEM，可含多个 CRL）。为空时行为不变。设置后，握手时链上每张证书（叶子和各级 CA）都要用其签发者的 CRL 检查：已吊销、签发者在文件中没有 CRL、CRL 已过期或签名不对，都返回 `ERR_TLS`。文件读不了或其中没有 CRL，在建立任何 socket 之前返回 `ERR_URL`。明文 loopback http 忽略此字段。上文第 4 节中「不检查吊销（CRL/OCSP）」一项里的 CRL 部分由此交付；OCSP、OCSP stapling、按分发点下载 CRL 和 delta CRL 仍未实现。测试在 `engine/tests/test_break_http.c`（新增 5 项，含三级证书链），设计与验证见 `docs/superpowers/plans/2026-11-16-break-http-crl.md`。

## 补充（2026-11-16）：经 HTTP CONNECT 代理访问 https

`BreakHttpConfig` 新增可选字段 `proxy`，格式为 `http://host:port`（路径为空或 `/`，不允许查询串、用户信息或 https 代理）。为 NULL 或空串时行为不变。格式不合法时，无论目标是什么协议，都在建立任何 socket 之前返回 `ERR_URL`。

只有 https 目标走代理：

1. 在 `connect_timeout_ms` 内 TCP 连接代理。代理地址不要求是回环，目标主机名由代理解析。
2. 发送 `CONNECT host:port HTTP/1.1`、`Host: host:port`、`User-Agent: break-http/1`。IPv6 主机加方括号，端口总是写出（URL 未给出时为 443）。
3. 读取代理响应头（最多 8 KiB，与普通响应同一套 `parse_head` 规则）。格式错误或 1xx 返回 `ERR_PROTOCOL`；非 2xx 返回 `ERR_STATUS`；与响应头一起到达的多余字节返回 `ERR_PROTOCOL`，不会交给 TLS。
4. 照常做 TLS 握手，CA、主机名、钉扎和 CRL 都针对目标校验，代理无法冒充目标。
5. CONNECT 交换计入 `io_timeout_ms` 总预算。

明文 http 目标忽略代理，仍只允许回环地址。不支持代理认证（407 返回 `ERR_STATUS`）、https 代理和从环境变量读取代理。测试在 `engine/tests/test_break_http.c`（新增 9 项，脚本化代理线程转发到 TLS 服务器），设计与验证见 `docs/superpowers/plans/2026-11-16-http-connect-proxy.md`。

## 补充（2026-11-16）：代理 Basic 认证

`BreakHttpConfig` 新增可选字段 `proxy_user`、`proxy_password`。两者都为 NULL 或空串时不发送凭据。否则两者都必须是 1..255 字节的可打印 ASCII（0x20..0x7e），用户名不能含 `:`；只设置其中一个、含控制字符或非 ASCII 字节、超长，或设置了凭据却没有配置 `proxy`，都在建立任何 socket 之前返回 `ERR_URL`。

凭据以 `Proxy-Authorization: Basic base64(user ":" password)` 只放在 CONNECT 请求里，不会发给目标服务器，明文 http（不走代理）也不会发送。代理仍返回 407 时为 `ERR_STATUS`，不重试、不解析质询。到代理的这一跳是明文 TCP，凭据在这一跳上可见；仍不支持 https 代理。测试在 `engine/tests/test_break_http.c`（新增 4 项，含 RFC 7617 示例、base64 三种余数与 255 字节上限），见 `docs/superpowers/plans/2026-11-16-http-proxy-basic-auth.md`。
