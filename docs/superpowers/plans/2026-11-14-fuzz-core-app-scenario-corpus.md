# fuzz_core_app_scenario 落盘 corpus 计划（2026-11-14）

## 背景

`fuzz_core_app_network` 已有落盘 corpus（`2026-11-14-fuzz-core-app-network-corpus.md`）。`fuzz_core_app_scenario` 仍只从 seed 随机变异一份内置文本，scenario 解析器的边界（4096 事件上限、511 字节行长、1048576 tick 上限、CRLF、注释、quit 之后的事件、`..` 路径）没有固定回归样例。

## 目标

- 新增 `engine/tests/data/core_app_scenario_corpus/`，文件名 `accept-<name>.scenario` 或 `reject-<name>.scenario`。
- `fuzz_core_app_scenario --emit-corpus <dir>` 用固定文本写出这些文件，可逐字节重新生成。
- `fuzz_core_app_scenario --replay <file>...` 对每个文件调用真实的 `core_app_scenario_load`（走文件读取路径），断言：
  - 状态等于前缀：accept → OK，reject → INVALID；前缀未知直接失败。
  - reject 时 `event_count == 0` 且 `events == NULL`。
  - accept 时事件数 1..4096，`has_quit`，最后一个事件是 QUIT，tick 单调不减且都在 1..1048576。
  - 两种前缀各至少一个文件，否则失败。
- CMake 用 `file(GLOB CONFIGURE_DEPENDS)` 注册 `fuzz_core_app_scenario_corpus`（`fuzz` 标签）。
- `.gitattributes` 把该目录标为 binary（含 CRLF 和控制字符样例）。

## TDD 步骤

1. RED：先加 `--replay` 与 CMake 注册，目录为空 → 失败。
2. GREEN：`--emit-corpus` 生成并提交，重新 configure 后通过。
3. 变异：去掉 `has_quit` 之后拒绝新事件的检查、去掉 4096 事件上限、去掉 `..` 路径检查，回放都应判红；恢复后通过。
4. 验证：normal 树 fuzz 与非 fuzz 全量、ASan 树 core_app fuzz。
5. 文档：`core_app_integration.md` Task 12 补充小节、`Implementation_Status.md` 顶部条目；提交并推送。
