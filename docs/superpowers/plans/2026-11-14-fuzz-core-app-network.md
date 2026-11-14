# fuzz_core_app_network 计划（2026-11-14）

## 背景

`docs/Implementation_Status.md` 的 Core App P12 Task 12 条目记录了“`fuzz_core_app_network` 未做”。
`core_app_network` 的 snapshot 解码器和权威防火墙是对端字节第一次被解释的地方，
目前只有 `test_core_app_network` 的 10 个固定用例覆盖。

## 目标

新增确定性变异 fuzzer `engine/tests/fuzz_core_app_network.c`，只链接 `core_app_network`：

1. 每次迭代用 `core_app_snapshot_build` + `encode` 生成合法 payload（0..64 个随机实体，含 NaN/Inf 位型）。
2. 五类变异：翻转任意字节；截断到任意长度；改写 count 字段（0..64、65、`UINT32_MAX`、随机值）；
   改写 magic/version/header_bytes；在尾部追加随机字节。
3. 解码输入放在恰好 `size` 字节的堆块里，ASan 能抓到越界读。
4. 断言：
   - 结果与参考模型一致（size<32→TRUNCATED，magic→BAD_MAGIC，version 或 header_bytes→BAD_VERSION，
     count>64→OVER_LIMIT，size<32+24·count→TRUNCATED，否则 OK）。
   - 拒绝时 `out` 与哨兵字节逐字节相同（解码失败不写输出）。
   - 接受时重新 encode 的字节与 payload 前 `needed` 字节相同（字段逐位往返）。
   - 接受的 snapshot 送入 inbox（随机 authenticated、message id、live generation），
     admission 与参考模型一致，且各拒绝计数加 accepted 等于调用次数。
   - 接受的 snapshot 推入 outbox，count 不超过 8，`enqueued + dropped` 等于推入次数，弹出顺序为 FIFO。
5. 输出 `iterations accepted` 与各拒绝类别的计数，同一 seed 两次输出逐字相同。

## 接线

- `engine/CMakeLists.txt`：`add_executable(fuzz_core_app_network EXCLUDE_FROM_ALL ...)`，
  `ENGINE_BUILD_FUZZ_SMOKE` 下注册 `fuzz_core_app_network_smoke`（2000 次，seed 41），标签 `fuzz`。
- `.github/workflows/ci.yml`：ASan 列表和两个 “Build fuzz targets” 步骤都加上该目标。
- `engine/tests/test_wayland_ci_migration_contract.cmake`：要求三个 core_app fuzzer 在 ci.yml 中各出现至少 3 次。
- `core_app_network.h`：decode 注释写明“失败时不写 `out`”。

## TDD

- RED：先改契约，`test_wayland_ci_migration_contract` 因 ci.yml 缺目标而失败；fuzzer 先写好，
  对三处生产变异（去掉 size<needed 检查、去掉 header_bytes 检查、admit 跳过 generation 检查）必须失败。
- GREEN：ci.yml 补齐；fuzzer 对未变异代码通过；ASan+UBSan 树跑 smoke 无报告。

## 不做

- 结构感知的 libFuzzer、落盘 corpus。
- 真实 TLS/Session 传输（仍需 `CORE_APP_ENABLE_NETWORK=ON` + Snowflake 构建）。
