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
>
> Phase 2 已交付（2026-10-23 Tasks 1-4，branch `sdd/scene-editor-phase2`，HEAD `b1c3a7eb`（Task 4 收口；代码内容同 `42df32f7`，仅注释修订））：`break_editor` 扩为 9 TU——新增纯 CPU `editor_viewport.*`（orbit 相机/screen→ray/BVH 拾取/focus）与 `editor_gizmo.*`（模式/手柄/命中/拖拽状态机，**整段拖拽 = 恰好一条 undoable 命令**，测试钉住）；`editor` 新增 GPU 3D viewport 面板（`editor_viewport3d.*`：离屏 RHI FBO 渲染 editor-only 代理立方体 + gizmo 手柄，经 plan 允许的唯一 myui 加法扩展槽 `my_vgcanvas_break_rhi_blit_texture` blit 进布局）+ 指针路由 + 真实 Q/W/E/R 模式切换与 F focus。editor lane（+`test_editor_viewport` 16、`test_editor_gizmo` 26、`test_editor_shell` 25）在 `build-sdd-v4`（normal）/`build-sdd-v4-asan`（ASan+UBSan 零报告）/`build-sdd-v4-tsan`（TSan 零报告）各 **8/8**；`ENGINE_BUILD_TESTS=OFF` 树 nm 验证零 test-hook 符号；全量 `ctest -LE 'graphics|fuzz'` **188/188**（1 项 Windows-only platform-skip；预存在 `test_vulkan` GL golden 漂移为 graphics 标签排除项、与 Task 2 HEAD 同签名，非分支引入）；终态 live smoke 复跑 6 秒零错误（smoke 证据，非 GPU 验证；argv 场景路径仅登记为 save 目标，loading 故意未接 argv；人工交互验证 pending）。合同文档 `docs/design/editor_viewport.md`；任务报告 `.superpowers/sdd/2026-10-23-scene-editor-phase2/task-{1..4}-report.md`。asset browser、场景保真渲染/SCENE_NODES ownership、诊断面板（profiler/network/render）、Lua console、remote session 仍未实现。
>
> Phase 3 已交付（2026-10-23 Tasks 1-4，branch `sdd/scene-editor-phase3`，HEAD = `dec9ce1a` + `11d55da4`（收口 nm 门禁发现的真实修复：libbreak_lua.a -O0 本地 test-hook 符号残留 → 宏直通，Stage 3 遗留、零行为变化）+ 文档提交）：**asset browser delivered-with-limits**——`platform_list_dir` PAL（POSIX lstat 不随 symlink + `_WIN32` FindFirstFileA 分支、有界、symlink 策略文档化）+ `BreakEditorAssets` 纯 CPU 模型（root 校验/单段 enter/深度 ≤8/dirs-first 逐字节排序快照/模型侧 CSV 过滤/4096 缓存）+ 面板接线（默认 root=cwd、单击激活、`.bscn` 无确认加载、set_root 失败降级、32 槽点击 ctx 池）；**profiler 面板 partial**——仅本地纯视图（top-N≤16、4 Hz 节流、从不改 profiler 状态有钉），network/render debugger 未交付；**Lua console delivered editor-local**——`BreakEditorLuaConsole` 核心（双 Stage 3 沙箱 runtime、1M 指令预算、lua.c REPL 序包裹、双 probe 注入安全、不可伪造预算跳闸 sentinel、fnref 结果通道、ecs batch 排入可 undo 命令——Ctrl+Z 撤销 Lua spawn 钉住）+ 面板（32 条有界 history、`lua| ` 前缀入共享 ring），remote session 仍 Stage 5-gated；Task 2 经五轮审查修复硬化。editor lane **10/10**（doc 12/cmd 14/scene 15/components 15/viewport 16/gizmo 26/assets 19/lua 32/shell 33/contract）+ break_lua lane **5/5**（runtime 8/module 24/value 34/binding 32/contract）在 `build-sdd-p33`（normal）/`build-sdd-p33-asan`（ASan+UBSan，关键二进制 ×3 零报告）/`build-sdd-p33-tsan`（TSan，×5 零报告）各全绿；`ENGINE_BUILD_TESTS=OFF` 树 `build-sdd-p34-notests` 六个 production 归档 nm 零 test-hook 符号；全量 `ctest -LE 'graphics|fuzz'` **190 入选 = 189 过 + 1 Windows-only skip、0 失败**（预清除 flake 本轮过、预存在 test_vulkan 漂移 graphics 排除、零 branch-caused）；契约测试三树 4/4；终态 live smoke ×2 exit 124、恰两行 INFO（smoke 证据，非 GPU 验证；人工交互验证 pending）。合同文档 `docs/design/editor_panels_phase3.md`；任务报告 `.superpowers/sdd/2026-10-23-scene-editor-phase3/task-{1..4}-report.md`。hot reload 集成、network/render debugger、Lua remote session（Stage 5-gated）、场景保真渲染/SCENE_NODES ownership 仍未实现。

- [x] Design editor shell and command routing（Phase 1 Task 4：`editor` + `BreakEditorShell` + 单表 `k_editor_shortcuts` + Ctrl+P 调色板；`test_editor_shell` 15/15）
- [x] World outliner/entity inspector（Task 4：虚拟化 my_list_view outliner + inspector 组件节；同测试钉住）
- [x] Property transactions and undo/redo（Tasks 1+3：命令式 undo/redo、逐字节精确；`test_editor_doc`/`test_editor_cmd`/`test_editor_components`）
- [ ] Asset browser and hot reload（asset browser **delivered-with-limits**：Phase 3 Tasks 1+3，`platform_list_dir` + `BreakEditorAssets` 模型 + 面板接线；默认 root=cwd、单击激活、快照 listing、32 槽点击池；**hot reload 集成仍未交付**）
- [x] Viewport/gizmo/scene round-trip（scene save-load round-trip：Phase 1 Task 2 BSCN+sidecar、`test_editor_scene` 15/15；3D viewport/gizmo/相机：Phase 2 Tasks 1-4 交付——纯 CPU 相机/拾取/gizmo 状态机 + GPU 视口面板，editor lane 三树 8/8、全量 188/188、记录在案 live smoke（非 GPU 验证）；场景保真渲染/SCENE_NODES ownership 为 Phase 3+ 排除项，见 `docs/design/editor_viewport.md` §9）
- [ ] Console/profiler/network/render panels（**partial**：profiler 面板已交付为本地纯视图——Phase 3 Task 3，top-N≤16、4 Hz 节流、从不修改 profiler 状态有测试钉住；Lua console 面板输出落共享 ring；**network/render debugger 仍未交付**；Phase 1 另有有界 64×128B 动作日志环）
- [x] Editor smoke and native UI evidence（headless：dummy PAL + PPM 冒烟测试三 lane 绿；native：`editor` 二进制 live X11 + OpenGL 4.6 Mesa 6 秒 smoke 零错误，Phase 1 Task 5 记录确切命令、Phase 2 Task 4 于终态复跑同型命令（`build-sdd-v4`，exit 124 超时即存活、两次运行日志逐字节相同）——不构成 GPU 验证；headless RHI 后端不存在，configure 拒绝 `ENGINE_RHI_BACKEND=headless`；脚本化交互钩子不存在，人工交互验证 pending）

## Stage 5 — Online update/crash/security

> Phase A 已交付（2026-10-24 Tasks 1-5，branch `sdd/stage5-security-foundations`，提交范围 `515ee51a..HEAD`）：威胁模型/安全契约文档 `docs/design/security_threat_model.md` + 版本身份 `break_version` 0.1.0+buildid + `break_crypto`（系统 OpenSSL 3.5.9 EVP：SHA-256/HMAC-SHA256/Ed25519 verify/CSPRNG，零自造密码学，`BREAK_ENABLE_CRYPTO` fail-closed 门控）+ 写侧 PAL 原子写（`PlatformAtomicWriter` fsync file→rename→fsync dir）+ `break_update`（签名 canonical manifest + 内容寻址 chunk store，**仅客户端离线验证**）。测试 `test_break_version` 7 / `test_break_crypto` 20 / `test_platform_fs_write` 10 / `test_break_update` 19 在 `build-sdd-p5a`（normal，全量非图形套件 196=195+1skip 零失败）/`-asan`（×3 零报告）/`-tsan`（×5 零报告）三树全绿；六个 target contract ctest 三树 6/6（两新库不泄入 engine/demos/editor 链接闭包）；`ENGINE_BUILD_TESTS=OFF` 树全部 production target 构建成功。下载/续传/A-B/回滚、崩溃 capture/spool/upload、传输认证、重放/限速/反篡改**实现**均未交付（子项目 2-5，后续 Phase 计划）；Win32 lane 与 fuzz lane 未跑（fuzz `Not Run`）。任务报告 `.superpowers/sdd/2026-10-24-stage5-security-foundations/task-{1..5}-report.md`。

- [x] Signed manifest/content-addressed package design（**超出 design**：Phase A 已交付格式 + 客户端离线验证实现 `break_update` 19/19 + `break_crypto` 20/20；下载/激活不在内——见下项）
- [ ] Download/resume/A-B/rollback implementation plan（**未交付**：Phase A 无任何下载/传输代码，实现计划属后续 Phase B）
- [ ] Crash context/spool/upload/symbolization design（**未交付**：仅脱敏契约设计已交付——`security_threat_model.md` §6；capture/spool/upload/symbolization 设计与实现均 pending）
- [x] Authentication/replay/rate-limit threat model（威胁模型**文档**已交付——`security_threat_model.md` §5 传输认证范围声明 + §7 重放/限速模型声明；**实现未交付**）
- [x] Anti-cheat trust-boundary design（信任边界 + 反篡改成本模型设计已交付——`security_threat_model.md` §2；任何反篡改**代码**未交付）
- [ ] Security review and release configuration tests（安全评审**文档**已交付——`security_threat_model.md`（§10 NOT-delivered 清单经代码交叉核对）；release 配置**测试**不存在——Phase A 无任何更新路径，无 remote debug 通道）

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
