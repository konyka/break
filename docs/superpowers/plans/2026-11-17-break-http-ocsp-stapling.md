# break_http：OCSP stapling 校验

Status: Done

## 背景

`docs/design/update_transport.md` 的 CRL 补充写明「OCSP、OCSP stapling、按分发点下载 CRL 和 delta CRL 仍未实现」。`missing_capabilities.md` 第 15 节也列出 OCSP。OCSP stapling 只需要 OpenSSL 已有的 `ocsp` 模块，不加新依赖，也不需要客户端访问外部 responder。

## 接口

`BreakHttpConfig` 新增 `bool require_ocsp_staple`，默认 false，行为不变。设为 true 时：

1. 握手前请求证书状态（`status_request` 扩展）。
2. 握手、CA、主机名、钉扎都通过后，检查服务端附带的 OCSP 响应。以下任一情况为 `ERR_TLS`：
   - 没有附带响应、DER 无法解析或带尾随字节。
   - `responseStatus` 不是 successful，或不是 basic 响应。
   - 签名验证失败。签名者必须是叶子的签发 CA，或由它签发并带 OCSPSigning EKU 的委托 responder，且能链到 `ca_file`（`OCSP_basic_verify`，flags 0）。
   - 没有与叶子匹配的单条响应。匹配时按每条响应自身的哈希算法计算 CertID，所以 SHA-1 和 SHA-256 都可以。
   - 状态不是 good（revoked、unknown 都拒绝）。
   - 缺少 nextUpdate；thisUpdate 晚于当前时间 300 秒以上；nextUpdate 早于当前时间 300 秒以上。
   - 验证后的链长度小于 2（自签名叶子没有可询问的签发者，按失败处理）。
3. 明文 loopback http 忽略该字段。

## TDD

测试写在 `engine/tests/test_break_http.c`。脚本服务端增加 status 回调，可以附带任意 DER，并记录客户端是否请求了状态。测试在进程内生成 CA、叶子、委托 responder（有 EKU 和无 EKU 两种）和 OCSP 响应。

- 对照：good 响应（SHA-1 CertID、SHA-256 CertID、委托 responder、同时开 CRL）都通过。
- revoked、unknown 拒绝；未开启时不请求状态，revoked 响应也不影响连接。
- 缺失、垃圾字节、尾随字节、tryLater 拒绝。
- 过期、缺 nextUpdate、thisUpdate 在未来拒绝；60 秒内的时钟偏差接受。
- 不受信 CA 签名、无 EKU 的委托 responder、针对其他证书的响应拒绝。
- 自签名叶子拒绝。
- loopback http 忽略。

## 验证

`test_break_http`、变异测试、影子变量检查、三棵完整树、兼容契约、禁用词检查、CI 三项。

## Result

72 项测试全部通过（新增 6 项）。19 项变异全部被捕获：首轮存活的 responseStatus 检查，通过「未成功状态但附带有效 good 响应体」的用例补上。影子变量检查 rc=0。三棵完整树、兼容契约与 CI 结果见提交记录。
