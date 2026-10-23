# Runtime Expansion Todo / Master Plan

> Status ledger for the requested multi-stage work. Each subproject must get its own design/spec, implementation plan, tests, review, and evidence before being marked complete.

## Stage 1 — Cross-engine inventory

- [x] `docs/cross_engine/cryengine_inventory.md`
- [x] `docs/cross_engine/bw191_inventory.md`
- [x] `docs/cross_engine/unreal_inventory.md`
- [x] `docs/cross_engine/feature_matrix.md`
- [x] `docs/cross_engine/missing_capabilities.md`
- [x] Evidence policy and 17-module coverage validated

## Stage 2 — Runtime design

> 设计已完成，实施计划为 `docs/superpowers/plans/2026-10-22-runtime-core-formalization.md`。实施已交付（2026-10-22/23 Tasks 1-7）：正式可选 targets `break_ecs_replication`、`break_replication_core`、`break_net`（Snowflake-conditional）与 `runtime_core`（coordinator/message/queue/task/thread/io/reload/profiler），均不链入 `engine`/`engine_demo`/`dxx_break`；normal/ASan+UBSan/TSan/fuzz/full-suite 验证证据见 `docs/Implementation_Status.md` 顶部条目。Lua boundary facade、统一 PAL facade、mailbox 拓扑、真实子系统接入与 engine/demo 集成仍是设计目标，尚未实现。

- [x] `runtime_overview.md`
- [x] `runtime_thread_model.md`
- [x] `runtime_message_model.md`
- [x] `runtime_network.md`
- [x] `runtime_asset_streaming.md`
- [x] `runtime_hot_reload.md`
- [x] `runtime_security.md`
- [x] Review formal-vs-focused CMake target boundaries
- [x] Review unified Runtime Core contract: coordinator lifecycle, local subsystem mappings, compatibility-vs-formal API behavior, capacities/backpressure, and `BreakRuntimeError`
- [x] Review Lua boundary and Asset/HotReload state/result contract; Stage 2 remains design goal/not implemented
- [x] Review opaque `u64` request handles, generation checks, owned `BreakAssetCompletion`/`BreakReloadCompletion`, explicit completion/request release, and poll/commit/cancel result enums
- [x] User approval of Stage 2 design in auto execution mode
- [x] Keep all Stage 2 lifecycle/backpressure/Lua/type/error/Asset-HotReload contracts marked design target/unimplemented
- [x] Create `docs/superpowers/plans/2026-10-22-runtime-core-formalization.md`

## Stage 3 — Lua runtime

> 实施已交付（2026-10-23 Tasks 1-5，branch `sdd/lua-runtime`）：正式可选 static target `break_lua`（独立于 `ENGINE_BUILD_TESTS`，不链入 `engine`/`engine_demo`/`dxx_break`）+ test-only `break_lua_test` 变体；测试 `test_break_lua_runtime`（8）/`test_break_lua_module`（19）/`test_break_lua_value`（26）/`test_break_lua_binding`（22）+ `test_break_lua_target_contract` + 兼容层 `test_script_lua` 在干净树 `build-sdd-l5`（normal）/`build-sdd-l5-asan`（ASan+UBSan 零报告）/`build-sdd-l5-tsan`（TSan 四二进制各 10 连跑零报告）各 6/6；`ENGINE_BUILD_TESTS=OFF` 树 nm 验证 0 test-hook 符号；全量 `ctest -LE 'graphics|fuzz'` 180/180（1 项 Windows-only platform-skip）；兼容层 `script_lua.*`/`test_script_lua.c` 全分支 diff 0 行。合同文档 `docs/design/lua_runtime.md`；任务报告 `.superpowers/sdd/2026-10-23-lua-runtime/task-{1,2,3,4,5}-report.md`。editor-automation 绑定、batch 记录真实 apply、host 侧动态 config 更新、module dependency graph、engine/demo 集成与 LuaJIT 仍未实现。

- [x] Design `BreakLuaRuntime` opaque C11 facade（`docs/superpowers/plans/2026-10-23-lua-runtime.md` + `docs/design/lua_runtime.md`）
- [x] Define module load/reload/version/error contracts（Task 2 交付 + `lua_runtime.md` §2.3）
- [x] Define bounded ECS batch/command bindings（Task 4 交付 `BreakLuaEcsBatch`/`brk.ecs.*` + config；`lua_runtime.md` §2.6）
- [x] Add normal/ASan/TSan RED/GREEN tests（per-task RED 证据见 task-{1..4}-report.md；GREEN：`build-sdd-l5{,-asan,-tsan}` 各 6/6）
- [x] Implement production target and docs（`break_lua` 顶层 target + `lua_runtime.md` + roadmap Stage 3 状态）
- [ ] Review LuaJIT as optional backend only after baseline（gating：baseline 合同稳定；未开始）

## Stage 4 — Scene editor

> Phase 1 已交付（2026-10-23 Tasks 1-5，branch `sdd/scene-editor-phase1`）：正式可选 static targets `break_editor`（文档模型 + 有界命令栈 undo/redo + BSCN/sidecar save/load + 组件注册表）与 `editor` 可执行（BreakUI shell：toolbar/outliner/inspector/console/status bar + Ctrl+P 调色板 + 快捷键表），均独立于 `ENGINE_BUILD_TESTS` 且不链入 `engine`/`engine_demo`/`dxx_break`。测试 `test_editor_doc`（12）/`test_editor_cmd`（14）/`test_editor_scene`（15）/`test_editor_components`（15）/`test_editor_shell`（15，dummy PAL + 判别性 PPM）+ `test_break_editor_target_contract` 在 `build-sdd-e5`（normal）/`build-sdd-e5-asan`（ASan+UBSan 零报告）/`build-sdd-e5-tsan`（TSan 零报告）各 6/6；`ENGINE_BUILD_TESTS=OFF` 树 nm 验证 production `libbreak_editor.a` 零 test-hook 符号；全量 `ctest -LE 'graphics|fuzz'` 186/186（1 项 Windows-only platform-skip）；`editor` 二进制在 live X11+GL 下 smoke-run 6 秒零错误（非 GPU 验证）。合同文档 `docs/design/editor_phase1.md`；任务报告 `.superpowers/sdd/2026-10-23-scene-editor-phase1/task-{1..5}-report.md`。asset browser、3D viewport/gizmo/相机、诊断面板（profiler/network/render）、Lua console、remote session 仍未实现。

- [x] Design editor shell and command routing（Phase 1 Task 4：`editor` + `BreakEditorShell` + 单表 `k_editor_shortcuts` + Ctrl+P 调色板；`test_editor_shell` 15/15）
- [x] World outliner/entity inspector（Task 4：虚拟化 my_list_view outliner + inspector 组件节；同测试钉住）
- [x] Property transactions and undo/redo（Tasks 1+3：命令式 undo/redo、逐字节精确；`test_editor_doc`/`test_editor_cmd`/`test_editor_components`）
- [ ] Asset browser and hot reload（**未交付**，Phase 1 范围外，无代码）
- [ ] Viewport/gizmo/scene round-trip（scene save-load round-trip 部分已交付——Task 2 BSCN+sidecar、`test_editor_scene` 15/15；3D viewport/gizmo/相机未交付，保持 unchecked）
- [ ] Console/profiler/network/render panels（Phase 1 仅有界 64×128B 动作日志环，非诊断面板）
- [x] Editor smoke and native UI evidence（headless：dummy PAL + PPM 冒烟测试三 lane 绿；native：`editor` 二进制 live X11 + OpenGL 4.6 Mesa 6 秒 smoke 零错误，Task 5 记录确切命令——不构成 GPU 验证；headless RHI 后端不存在，configure 拒绝 `ENGINE_RHI_BACKEND=headless`）

## Stage 5 — Online update/crash/security

- [ ] Signed manifest/content-addressed package design
- [ ] Download/resume/A-B/rollback implementation plan
- [ ] Crash context/spool/upload/symbolization design
- [ ] Authentication/replay/rate-limit threat model
- [ ] Anti-cheat trust-boundary design
- [ ] Security review and release configuration tests

## Stage 6 — Graphics API lifecycle

- [ ] Audit existing Vulkan/D3D12/Metal/headless plans
- [ ] Complete backend-specific remaining gaps in separate plans
- [ ] Collect per-backend evidence
- [ ] Maintain OpenGL deprecation/removal gate

## Cross-cutting validation

- [x] Clean normal build with all relevant targets explicitly built（2026-10-23 Task 7：`build-sdd-t7`，Snowflake ON，4 个正式 target 显式构建 + 完整默认 target 集）
- [x] Clean ASan/UBSan build and relevant tests（`build-sdd-t7-asan`，focused runtime/ecs/net lane 16/16）
- [x] Clean TSan build and relevant tests（`build-sdd-t7-tsan`，同一 lane 16/16，零报告）
- [x] Explicitly build/run all fuzz smoke targets（5 个 fuzz target 显式构建，`ctest -L fuzz` 5/5）
- [ ] Native/CI cross-platform evidence recorded
- [x] Full CTest failures classified as code vs environment vs not-built（178 项入选：177 通过、0 失败、1 platform skip；graphics/fuzz label 排除项逐项列出）
- [x] `git diff --check`
- [x] 文档自审：生命周期、shutdown 顺序、错误类别、容量/背压、Lua boundary、Asset/HotReload 状态机前后一致
- [ ] Final independent code review
