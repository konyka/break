# fuzz_core_app_network 落盘 corpus 计划（2026-11-14）

## 背景

`docs/design/core_app_integration.md` 的 `fuzz_core_app_network` 小节写着“仍未做：没有落盘 corpus”。现在的 fuzzer 每次只从 seed 随机生成输入，边界样例（空包、差一字节、count=65、count=UINT32_MAX 等）只是概率命中，没有固定的回归样例。

## 目标

- 仓库新增 `engine/tests/data/core_app_network_corpus/`，每个文件是一份 snapshot 线上字节，文件名 `<outcome>-<name>.bin` 写明期望的解码结果（`ok`、`truncated`、`bad_magic`、`bad_version`、`over_limit`）。
- `fuzz_core_app_network --emit-corpus <dir>` 用固定构造（不用随机数）写出这组文件，可以重新生成。
- `fuzz_core_app_network --replay <file>...` 逐个读文件并断言：
  - 解码结果等于文件名前缀，也等于参考模型；未知前缀直接失败。
  - 拒绝时 `out` 保持 0xA5 哨兵。
  - 接受时重新编码等于 payload 前 `needed` 字节；`schema_hash` 等于当前 `core_app_snapshot_schema_hash()`（布局变了必须重新生成 corpus）；认证、schema 相同、generation 相同的 inbox 恰好 ADMITTED，generation 不同时 STALE_LEVEL。
  - 五种结果每种至少出现一次，否则失败（防止 glob 为空时假通过）。
- CMake 在 `ENGINE_BUILD_FUZZ_SMOKE` 下用 configure 时的 `file(GLOB)` 把文件作为参数注册 `fuzz_core_app_network_corpus`，带 `fuzz` 标签。CI 已构建该目标并跑 `-L fuzz`，不需要改 ci.yml。目录用参数传入，不用 dirent，MSVC 也能跑。

## TDD 步骤

1. RED：先加 `--replay`/`--emit-corpus` 解析和 CMake 注册，corpus 目录为空 → 测试因为缺结果类别失败。
2. GREEN：`--emit-corpus` 生成文件并提交，重新 configure 后测试通过。
3. 变异：去掉 decode 的 `size < needed` 检查、去掉 header_bytes 检查，回放应判红；恢复后通过。
4. 验证：normal 树 fuzz lane 与全量非 fuzz、ASan 树 fuzz lane。
5. 文档：`core_app_integration.md` 补充小节，`Implementation_Status.md` 顶部条目。提交并推送。
