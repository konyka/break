# break_http 公钥钉扎（2026-11-15）

## 目标
`missing_capabilities.md` 第 15 节仍缺「证书钉扎」。给 `break_http` 增加可选的
SubjectPublicKeyInfo SHA-256 钉扎，用于更新和崩溃上传通道。

## 规则
- `BreakHttpConfig` 新增 `spki_sha256_pins`（`spki_pin_count` 个连续 32 字节摘要）。
- count 为 0 时行为与现在完全相同。
- 钉扎在 CA 校验和主机名校验都通过之后执行，只能收紧，不能替代 CA 校验。
- 叶子证书公钥摘要不在列表中：`BHTTP_ERR_TLS`。
- count 大于 `BREAK_HTTP_MAX_PINS`（8），或 count 非 0 而指针为 NULL：`BHTTP_ERR_URL`，不建立连接。
- 明文 http（仅 loopback）忽略钉扎。

## 步骤
1. 头文件字段 + RED 测试：匹配（列表第二项）通过、不匹配为 TLS 错误、钉扎不能绕过错误 CA、参数校验。
2. GREEN：握手后计算 `i2d_X509_PUBKEY` 的 SHA-256 并比较。
3. 变异：去掉比较、去掉参数校验、只比较第一项、count 为 0 时也检查，测试都必须失败。
4. 全量 ctest，追加 `update_transport.md`、`Implementation_Status.md`，提交推送。

## Status
完成。`test_break_http` 43/43（新增 6 个测试，其中握手超时测试是为消除存活变异而补的）。8 项变异全部被捕获；摘要长度检查不可观察，已删除。全量 ctest 402/402（`build-core-app-master`）。
