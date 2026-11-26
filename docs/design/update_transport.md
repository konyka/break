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

凭据以 `Proxy-Authorization: Basic base64(user ":" password)` 只放在 CONNECT 请求里，不会发给目标服务器，明文 http（不走代理）也不会发送。代理仍返回 407 时为 `ERR_STATUS`，不重试、不解析质询（2026-11-17 起 Digest 质询会被回应一次，见下节）。到代理的这一跳是明文 TCP，凭据在这一跳上可见；仍不支持 https 代理。测试在 `engine/tests/test_break_http.c`（新增 4 项，含 RFC 7617 示例、base64 三种余数与 255 字节上限），见 `docs/superpowers/plans/2026-11-16-http-proxy-basic-auth.md`。

## 补充（2026-11-17）：代理 Digest 认证

配置了 `proxy_user`/`proxy_password` 时，第一次 CONNECT 仍带 Basic 凭据。代理以 407 回答、且某个 `Proxy-Authenticate` 头带有可回应的 Digest 质询（RFC 7616）时，客户端关闭该连接，在同一连接预算和同一总 I/O 截止时间内重新连接代理，发送第二次 CONNECT，只带 `Proxy-Authorization: Digest ...`。第二次的回答是最终结果：再次 407 为 `ERR_STATUS`，格式错误为 `ERR_PROTOCOL`，没有第三次尝试。

质询解析：头名与 scheme 不区分大小写；跳过 Basic 等其他 scheme 和不可用的 Digest 质询，取第一个可用的。auth-param 为 `name=token` 或 `name="quoted"`，逗号分隔；quoted 值可用 `\x` 转义，但结果不能含 `"`、`\`、控制字节或非 ASCII 字节，值最长 255 字节。必须有 `realm` 和非空 `nonce`；已知参数重复、空参数名、缺 `=`、引号未闭合、末尾多余逗号或两个参数之间缺逗号，整个质询都不可用。`algorithm` 缺省或 `MD5` 用 MD5，`SHA-256` 用 SHA-256，其他（含 `-sess`）不支持；`qop` 缺省用 RFC 2069 形式，列表含 `auth` 用 `qop=auth`，否则不支持；`userhash` 不是 `false` 时不支持；`opaque` 原样回传，其他参数忽略。

应答：HA1 = H(user:realm:password)，HA2 = H("CONNECT:" authority)；有 qop 时 response = H(HA1:nonce:00000001:cnonce:auth:HA2)，否则 H(HA1:nonce:HA2)，均为小写十六进制。cnonce 是 16 字节 `RAND_bytes` 的十六进制，每次应答重新生成。用户名中的 `"` 与 `\` 转义后放入 `username="..."`，密码不会离开客户端。代理这一跳仍是明文 TCP。测试在 `engine/tests/test_break_http.c`（新增 5 项：RFC 7616 示例参数的 MD5、SHA-256、RFC 2069 形式、宽松语法、最大长度、第二次 407、22 种不可用质询以及 403/无凭据），见 `docs/superpowers/plans/2026-11-17-http-proxy-digest-auth.md`。仍不支持 NTLM、https 代理，也不复用 407 所在的连接。


## 补充（2026-11-17）：OCSP stapling 校验

`BreakHttpConfig` 新增 `require_ocsp_staple`（默认 false，行为不变）。设为 true 时，客户端在握手中请求证书状态（`status_request` 扩展），并在 CA、主机名和钉扎都通过后检查服务端附带的 OCSP 响应。不会联系任何 OCSP responder。上文 CRL 补充中「OCSP stapling 仍未实现」一项由此交付；主动查询 OCSP responder、按分发点下载 CRL 和 delta CRL 仍未实现。

以下任一情况为 `ERR_TLS`：

- 没有附带响应；DER 无法解析或带尾随字节；`responseStatus` 不是 successful（即使附带了有效的 good 响应体）；不是 basic 响应。
- 验证后的链短于 2，即自签名叶子没有签发者可以为响应担保。
- `OCSP_basic_verify`（flags 0）失败：签名者必须是叶子的签发 CA，或由它签发并带 OCSPSigning EKU 的委托 responder，并能链到 `ca_file`。
- 没有与叶子匹配的条目。每条按其自身的哈希算法重算 CertID，所以 SHA-1 和 SHA-256 CertID 都可以。
- 任一匹配条目的状态不是 good（revoked、unknown 都拒绝），或缺少 nextUpdate，或 thisUpdate 比本地时间晚 300 秒以上，或 nextUpdate 比本地时间早 300 秒以上。

尾随字节检查只在 OpenSSL 3 上生效：OpenSSL 4 在握手时自行解码附带的响应，`SSL_get_tlsext_status_ocsp_resp` 返回重新编码的副本，尾随字节在库内已被丢弃（垃圾字节则直接导致握手失败，同样是 `ERR_TLS`）。签名覆盖的内容在两个版本上都照常验证。

可与 `crl_file` 同时开启。明文 loopback http 忽略该字段。测试在 `engine/tests/test_break_http.c`（新增 6 项，进程内生成 CA、叶子、委托 responder 和 OCSP 响应），计划见 `docs/superpowers/plans/2026-11-17-break-http-ocsp-stapling.md`。


## 补充（2026-11-20）：Linux arm64 QEMU 验证

`lane-cross-aarch64-linux` 复用 `CMAKE_CROSSCOMPILING_EMULATOR=/usr/bin/qemu-aarch64;-L;/`，把 HTTP/在线更新七项测试加入既有崩溃七项，统一为十四项 CTest：更新核心、更新客户端、HTTP、manifest 工具、更新目标契约、HTTP 契约和更新 e2e。

未修改基线中三个可执行目标已通过 21/21、44/44、72/72；manifest 与更新 e2e 因宿主直接执行 arm64 工具失败，两个契约因缺少目标感知 `nm` 失败。接入后，manifest 和更新 e2e 的 TOOL/VERIFY/server/client 使用可选 `TARGET_RUNNER`，更新契约的现场链接程序使用 `UPDATE_CONTRACT_RUNNER`，两个契约使用宿主交叉 `nm`。宿主 CMake、shell 和 `nm` 本身不模拟；原生空运行器保持直接执行。

修改 CI 前的干净 Ubuntu 容器七项全部通过：`break_manifest_tool OK`、21/44/72、两个契约以及 `break_update_e2e OK`。这验证 QEMU 中 arm64 目标二进制的签名 manifest、A/B 状态、TLS、Range/断点续传、篡改与无 CA 拒绝；HTTP 72 项还覆盖代理认证、SPKI 钉扎、CRL 和 OCSP stapling。没有放宽或过滤任何用例。

本结果仍是选定测试的模拟证据，不是全量 arm64 CTest、GPU 或物理设备验证，也不代表生产更新服务、HTTP/2、https 代理、主动 OCSP responder 或发布二进制接入由此交付。

## 响应头解析器的 fuzz（2026-11-27）

`parse_head`（`engine/src/net_http/break_http.c`）解析不可信服务器返回的状态行和头部，update、崩溃上传和
metrics 推送的每个响应都要经过它。它是 static 函数，此前只能通过脚本化 socket 服务器的单元测试间接触达，
没有变异 fuzz。

新增 `engine/tests/fuzz_http_head.c`。它直接 `#include` `break_http.c` 以调用 static 函数（沿用
`test_audio.c` / `test_pad_linux_feedback.c` 的做法），自己链接 OpenSSL，而不是链接 `break_http` 库，
否则会出现重复符号。种子有五个：200、206 带 Content-Range、1.0 的 204、404 带 identity 编码、206 带
`/*` 总长。变异包括字节翻转、插入语法字节、删除、原地复制片段（用于触达 64 头上限和重复头拒绝）、截尾。
每个输入都复制到大小恰好的堆缓冲，越界读会被 ASan 抓到。不变量：不越界；被接受的头部 status 在
100..599 之间，Content-Range 满足 first <= last；同一输入解析两次，结论和字段一致。
`HTTP_HEAD_LIBFUZZER=1` 时导出给 libFuzzer。注册为 `fuzz_http_head_smoke`（种子 73），并加入 CI 的三处
fuzz 构建列表。

验证：种子 73 跑 200000 次（接受 27197 次）、种子 107 跑 100000 次（接受 13439 次），ASan+UBSan+leak
全程 clean。负向对照：删掉 `\r\n\r\n` 结尾检查后，fuzzer 立即在 `break_http.c:624` 报
heap-buffer-overflow。这说明后面的扫描循环依赖这项检查来保证不越界，fuzzer 能发现它被去掉。
`test_break_http` 72/72，`build-current-vk` fuzz lane 21/21。
