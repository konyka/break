# fuzz_core_app_checkpoint 落盘 corpus 计划（2026-11-14）

## 背景

network 与 scenario fuzzer 已有落盘 corpus。`fuzz_core_app_checkpoint` 只随机变异一份 manifest，manifest 解析的每条规则（magic、version、header_bytes、size 字段、保留字、generation、count 上限、记录名长度与填充、basename 规则、大小写不敏感重名、payload 大小与哈希、find 的重复 kind）都没有固定回归样例。

## 目标

- 新增 `engine/tests/data/core_app_checkpoint_corpus/`，每个文件是一份 `manifest.core` 字节，文件名前缀写明期望结果：
  - `ok-`：`core_app_checkpoint_probe` 返回 OK，`core_app_checkpoint_find(RUNTIME)` 返回 OK，generation 等于 manifest 偏移 24 的值，返回记录的 kind、size、hash 与 manifest 中 RUNTIME 记录一致。
  - `nofind-`：probe 返回 OK，find(RUNTIME) 返回 INVALID（缺 RUNTIME 或 RUNTIME 重复）。
  - `invalid-` / `overload-`：probe 与 find 都返回 INVALID / OVERLOAD。
- 回放时在临时目录写入 fuzzer 固定的 4 个 payload（scene/flow/actors/runtime），对每个样例把文件复制成 `manifest.core` 后检查；结束时确认 4 个 payload 字节未变，再删除临时目录。
- `--emit-corpus <dir>` 用测试内独立重写的 manifest 编码（不调用生产 writer）生成样例，可逐字节重新生成。
- 四种前缀各至少一个文件，否则失败。CMake `file(GLOB CONFIGURE_DEPENDS)` 注册 `fuzz_core_app_checkpoint_corpus`（`fuzz` 标签）；`.gitattributes` 标 binary。

## TDD 步骤

1. RED：先加 `--replay` 与 CMake 注册，目录为空 → 失败。
2. GREEN：生成并提交 corpus，重新 configure 后通过；若暴露生产缺陷，先补单测 RED 再修。
3. 变异：去掉重名检查、去掉保留字检查、find 不拒绝重复 kind、去掉 payload 哈希比较，回放都应判红；恢复后通过。
4. 验证：normal 树 fuzz 与非 fuzz 全量，ASan 树 core_app fuzz。
5. 文档：`core_app_integration.md` Task 12 补充小节、`Implementation_Status.md` 顶部条目；提交并推送。
