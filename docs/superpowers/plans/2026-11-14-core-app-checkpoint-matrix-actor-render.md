# core_app checkpoint 失败矩阵：失效 Actor 行与 render 资源 staging 失败

## 背景

`docs/design/core_app_integration.md` Task 8 slice 3 的“仍未做”记录了两项失败矩阵用例：错误 Actor generation、GPU/record 资源 staging 失败。现有矩阵在 `engine/tests/test_core_app_lifecycle.cmake`，用 Python 改坏 checkpoint 文件并同步 manifest 的长度与哈希。

## 注入点

- 失效 Actor 行（stale_actor）：`actors.sidecar` 只存“实体序号 类名”，实体代际由 `parse_sidecar`（`engine/src/kernel/break_kernel_level.c`）按当前 world 的实体表核对：序号越界或该槽位不是存活实体时返回 `BREAK_KERNEL_STALE`。用例把 `2 User` 改成 `99 User`，指向本代 world 不存在的槽位，期望 `load_rejected stage=actor`。
- render 资源 staging 失败（render_resource）：`.bscn` 无内容校验，用例把 RESOURCES chunk 第一个资源的 guid 写成 0。`core_app_render_stage_level` 拒绝 id 为 0 的资源，期望 `load_rejected stage=render`。

## 步骤

1. 在矩阵 Python 补丁里加 `stale_actor` 与 `zero_guid` 两种模式，矩阵列表加两行。
2. 运行 `test_core_app_lifecycle_load_unload`。这两项是对现有行为的特征测试，先验证它们通过，再做变异：
   - `parse_sidecar` 的越界/存活判定改成恒假 → stale_actor 必须变红；
   - `core_app_render_stage_level` 的 `id == 0u` 判定改成恒假 → render_resource 必须变红。
3. ASan/TSan 树跑 `test_core_app_`。
4. 文档追加：`core_app_integration.md` Task 8 slice 3 后补充小节，`Implementation_Status.md` 顶部条目。
5. normal 全量、提交、archive 契约、推送、确认 CI。
