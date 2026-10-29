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
>
> Phase 4 已交付（2026-10-25 Tasks 1-4，branch `sdd/scene-editor-phase4`，提交范围 `master..HEAD`：Task 1 `1af632eb`、Task 2 `7fc7a1ef`+`ca9a2785`、Task 3 `5df792cd`+`357be082`、Task 4 收口）：**editor remote session（dev-tool 形态）**——线协议 ids 4..13（default registry 空闲段 4..19）、STEP 模式 reactor + session manager 由 shell tick 每帧驱动（shell 线程 = GameThread，零跨线程派发）、每条远端变更 1:1 映射可 undo doc 命令（Ctrl+Z 与远端 UNDO 均可撤销远端 spawn，测试钉住）、TLS + CHALLENGE/AUTH-v2 必需、默认 OFF（`--remote` 只绑 127.0.0.1、默认限速 20/s burst 40 + 120/IP/min）、dev PSK（文件优先，hex 经 /proc cmdline 可见）；**network 诊断面板**（纯视图、≤4 Hz、16×96B、profiler 下方）。`test_editor_shell` **59/59** 三树绿（ASan ×3 / TSan ×5 零报告），editor lane 10/10、break_net lane 3/3、契约 7/7 ×3；全量 `ctest -LE 'graphics|fuzz'` **203=202+1skip 零失败**；`ENGINE_BUILD_TESTS=OFF` 树构建 `editor`；nm：engine/engine_demo/dxx_break 零 break_net/break_crypto 符号；TLS+AUTH-v2 E2E transcript 见 `docs/design/editor_remote.md` §7。构建形态变化：`editor` 现需 `BREAK_ENABLE_SNOWFLAKE=ON`。**未交付**：remote load/save、remote render control、render debugger、生产凭证系统、WAN/多客户端管理、remote undo-stack 共享、服务端 transport close/认证 deadline；Win32 lane 仅交叉编译（无运行）；后续证据（master `4a28ddf0`，见 `docs/design/editor_remote.md` §10 Follow-up）：sanitizer 树在 master 重跑 ASan ×3 / TSan ×5 均 59/59 零报告，`ctest -L fuzz` 5/5（ASan+UBSan，既有 fuzzer，无 editor 协议专用 fuzzer），live `editor --remote` 冒烟（TLS+AUTH-v2 脚本客户端 DESCRIBE/SPAWN/LIST/UNDO 通过，无 AUTH/错 PSK 客户端零响应），Win32 `zig cc` 交叉编译 `editor.exe`（Snowflake OFF）通过、Snowflake ON 仅编译到对象文件、链接受缺 nghttp2 阻塞。

- [x] Design editor shell and command routing（Phase 1 Task 4：`editor` + `BreakEditorShell` + 单表 `k_editor_shortcuts` + Ctrl+P 调色板；`test_editor_shell` 15/15）
- [x] World outliner/entity inspector（Task 4：虚拟化 my_list_view outliner + inspector 组件节；同测试钉住）
- [x] Property transactions and undo/redo（Tasks 1+3：命令式 undo/redo、逐字节精确；`test_editor_doc`/`test_editor_cmd`/`test_editor_components`）
- [ ] Asset browser and hot reload（asset browser **delivered-with-limits**：Phase 3 Tasks 1+3，`platform_list_dir` + `BreakEditorAssets` 模型 + 面板接线；默认 root=cwd、单击激活、快照 listing、32 槽点击池；**场景 hot reload 已于 2026-10-26 交付**：当前 `.bscn` 由 Runtime Core worker 暂存、shell 线程提交，非法文件与未保存编辑保持原状，浏览器列表每秒重列当前目录，见 `docs/design/editor_hot_reload.md`；**viewport shader hot reload 已于 2026-10-27 交付**（见 `docs/design/editor_hot_reload.md` §7）；**图片预览纹理 hot reload 已于 2026-10-28 交付**（§8）；材质/场景纹理 hot reload、VFS pak 枚举、Windows/macOS 实机未交付）
- [x] Viewport/gizmo/scene round-trip（scene save-load round-trip：Phase 1 Task 2 BSCN+sidecar、`test_editor_scene` 15/15；3D viewport/gizmo/相机：Phase 2 Tasks 1-4 交付——纯 CPU 相机/拾取/gizmo 状态机 + GPU 视口面板，editor lane 三树 8/8、全量 188/188、记录在案 live smoke（非 GPU 验证）；场景保真渲染/SCENE_NODES ownership 为 Phase 3+ 排除项，见 `docs/design/editor_viewport.md` §9）
- [x] Console/profiler/network/render panels（**delivered-with-limits**：render debugger 2026-10-26 已交付纯视图（`docs/design/editor_render_debugger.md`；无 capture/控制/GPU timing）；此前 **partial**：profiler 面板已交付为本地纯视图——Phase 3 Task 3，top-N≤16、4 Hz 节流、从不修改 profiler 状态有测试钉住；Lua console 面板输出落共享 ring；**network 面板已交付**——Phase 4 Task 3，纯视图 reactor/session/admission/connection 行、≤16×96B、≤4 Hz、诊断列 profiler 下方；**render debugger 已交付**（2026-10-26，纯视图，见 `docs/design/editor_render_debugger.md`）；Phase 1 另有有界 64×128B 动作日志环）
- [x] Lua console + remote session（console：Phase 3 editor-local；**remote session dev-tool 形态已交付**——Phase 4 Tasks 1-2：STEP 模式 reactor 由 shell tick 驱动、handler 全在 shell 线程映射可 undo 命令、TLS + CHALLENGE/AUTH-v2 必需、默认 OFF、`--remote` 只绑 loopback + 默认限速、dev PSK（非生产凭证体系）；契约 `docs/design/editor_remote.md`；**未交付**：remote load/save、remote render control、WAN/多客户端管理、服务端 transport close/认证 deadline）
- [x] Editor smoke and native UI evidence（headless：dummy PAL + PPM 冒烟测试三 lane 绿；native：`editor` 二进制 live X11 + OpenGL 4.6 Mesa 6 秒 smoke 零错误，Phase 1 Task 5 记录确切命令、Phase 2 Task 4 于终态复跑同型命令（`build-sdd-v4`，exit 124 超时即存活、两次运行日志逐字节相同）——不构成 GPU 验证；headless RHI 后端不存在，configure 拒绝 `ENGINE_RHI_BACKEND=headless`；脚本化交互钩子不存在，人工交互验证 pending）
- [x] Editor 乱码修复与 I18N（2026-10-27，branch `sdd/editor-i18n`：字体跨发行版查找 + 位图回退告警、en-US/zh-CN 表、`--lang`/环境变量、命令面板运行时切换、`test_source_encoding`；见 `docs/design/editor_i18n.md`；RTL/复杂整形、Windows/macOS 字体与 CI 未验证）

## Stage 5 — Online update/crash/security

> Phase A 已交付（2026-10-24 Tasks 1-5，branch `sdd/stage5-security-foundations`，提交范围 `515ee51a..HEAD`）：威胁模型/安全契约文档 `docs/design/security_threat_model.md` + 版本身份 `break_version` 0.1.0+buildid + `break_crypto`（系统 OpenSSL 3.5.9 EVP：SHA-256/HMAC-SHA256/Ed25519 verify/CSPRNG，零自造密码学，`BREAK_ENABLE_CRYPTO` fail-closed 门控）+ 写侧 PAL 原子写（`PlatformAtomicWriter` fsync file→rename→fsync dir）+ `break_update`（签名 canonical manifest + 内容寻址 chunk store，**仅客户端离线验证**）。测试 `test_break_version` 7 / `test_break_crypto` 20 / `test_platform_fs_write` 10 / `test_break_update` 19 在 `build-sdd-p5a`（normal，全量非图形套件 196=195+1skip 零失败）/`-asan`（×3 零报告）/`-tsan`（×5 零报告）三树全绿；六个 target contract ctest 三树 6/6（两新库不泄入 engine/demos/editor 链接闭包）；`ENGINE_BUILD_TESTS=OFF` 树全部 production target 构建成功。下载/续传/A-B/回滚、崩溃 capture/spool/upload、传输认证、重放/限速/反篡改**实现**均未交付（子项目 2-5，后续 Phase 计划）；Win32 lane 与 fuzz lane 未跑（fuzz `Not Run`）。任务报告 `.superpowers/sdd/2026-10-24-stage5-security-foundations/task-{1..5}-report.md`。

> Phase B 已交付（2026-10-24 Tasks 1-4，branch `sdd/stage5-update-client`，提交范围 `bb4a1a2e..HEAD`）：`break_update` 扩为 2 TU——update client 状态机 + A/B 槽（`state` canonical 文本 ≤64 KiB、每次变更 write-ahead 经原子写、fail-closed 解析无修复启发式）+ 分块下载器（chunk 粒度、`chunks/<hash>.part` 字节级续传、CAS 去重永不重取、流式 SHA-256 全量校验后入库）+ stage/activate/confirm-boot/unstage/rollback 管线（**签名与 compatible() 策略先于一切传输**——VERIFY/POLICY 失败零 fetch/零磁盘/零状态变；回滚受 min-rollback 地板 + staged 互斥约束，unstage 为唯一不激活清 staged 途径）。传输 = 调用方 `BreakUpdateFetchFn` 回调（ranged read、false 可重试、offset/len 由 client 钳制永不溢出），仓库内以 in-process fake 测试、**无任何真实网络代码**。测试 `test_break_update_client` 43/43（+ `test_break_update` 19/19）在 `build-sdd-p5b`（normal，全量非图形套件 197=196+1skip 零失败）/`-asan`（五二进制 ×3 零报告）/`-tsan`（×5 零报告）三树全绿；契约 ctest 三树 6/6（nm 恰 28 导出）；notests 树九归档零 test-hook（推迟项 #2 唯一例外不变）；`BREAK_ENABLE_CRYPTO=OFF` 树构建成功、update/crypto target 缺席。契约文档 `docs/design/update_client.md`（含 A/B 槽窗口/崩溃代价/解析校验非认证的诚实边界）。**未交付**：真实传输接线、灰度客户端逻辑、服务端、签名后在线流程（子项目 2 在线半侧）；子项目 3-5 不变；Win32 lane 未跑、fuzz `Not Run`。任务报告 `.superpowers/sdd/2026-10-24-stage5-update-client/task-{1..4}-report.md`。

> Phase C 已交付客户端半侧（2026-10-24 Tasks 1-4，branch `sdd/stage5-crash-reporting`，提交范围 `3bf56df6..HEAD`）：正式可选 static target `break_crash`（`BREAK_ENABLE_CRASH` 默认 ON，不链入 `engine`/`engine_demo`/`dxx_break`/`editor`——契约钉住）——async-signal-safe 捕获（install 期预置模块表/build-id/记录缓冲/预打开 inbox fd；白名单 handler；一次性捕获 + SIG_DFL/raise 保持原死法；argv/env zone_lo 隐私钳制）+ canonical 记录 `break-crash-v1`（≤64 KiB、模块 ≤64、窗口/blob ≤4 KiB）+ 有界 spool（inbox→pending 崩溃恢复 at-least-once、retention 16/16/16、fail-closed 隔离）+ 纯函数 redact（模块名 basename 幂等/占位符、blob 直通因 app 预脱敏义务——威胁模型 §6 客户端执行点）+ 调用方上传接缝 `BreakCrashUploadFn`（false=可重试、app 拥有传输、attempts sidecar 原子持久化跨 reopen、第 5 次失败丢弃、at-least-once）。测试 `test_break_crash` **36/36**（fork 用例双钉死亡信号与记录内容）在 `build-sdd-p5c`（normal，全量非图形套件 199=198+1skip 零失败）/`-asan`（×3 零报告）/`-tsan`（×5 零报告）三树全绿；契约 ctest 三树 **7/7**（nm 恰 36 导出）；notests 树九归档零 test-hook（推迟项 #2 唯一例外不变）+ `libbreak_crash.a` 零 test-hook；`BREAK_ENABLE_CRASH=OFF` 树构建成功、target 缺席。契约文档 `docs/design/crash_reporting.md`（捕获清单/隐私表/handler 白名单/恢复序列/retention+backoff/上传接缝/符号化契约/NOT-delivered）。**未交付**：服务端符号化/聚类/回归（Phase D+）、真实上传传输、GPU/RHI/网络/输入摘要捕获（app context-blob 后续集成）、minidump/PE 格式、Windows SEH（`_WIN32` stub）；Win32 lane 未跑、fuzz `Not Run`。任务报告 `.superpowers/sdd/2026-10-24-stage5-crash-reporting/task-{1..4}-report.md`。

> Phase D 已交付客户端+库半侧（2026-10-24 Tasks 1-5，branch `sdd/stage5-transport-security`，提交范围 `a7c0588b..HEAD`）：Snowflake 钉版 `d5d4a928`（configure 期 fail-closed FATAL 门，CMakeLists/locked_dependencies/snowflake_c11_adapter.md 三处同步，篡改实验在 /tmp 干净副本复核 FATAL）+ `break_net` TLS 传输模式（服务端接受模式、handshake 失败 fail-closed、`verify_peer` mTLS、无 CA 拒配；限制如实：无 TLS shutdown API——close_notify 与 TCP FIN 不可区分、无会话恢复）+ CHALLENGE/AUTH-v2 会话认证（16B CSPRNG server_nonce + 56B AUTH v2，HMAC-SHA256 只经 `break_crypto`——零自造密码学；跨连接逐字节重放钉死必败；`BREAK_ENABLE_CRYPTO=OFF` 树整面缺席无 plaintext 旁路）+ key 生命周期**接缝**（`BreakNetAuthKeyFn` app 侧解析 key_id→PSK；进程级配置 NEW-only + 操作租约纪律；可选 `max_age` 过期）+ 每连接单调出站序号（1 起、饱和不回绕）+ 准入限速（Snowflake admission hook 全局 token bucket + 每 IP 滑窗、1024 表满 fail-closed 拒新 IP、`_Atomic` 可观测拒绝计数；token 不退还保守方向）。测试 `test_break_net_tls` 10/10、`test_break_net_adapter` 38/38、`test_break_session` 34/34 在 normal/ASan+UBSan/TSan 三树全绿（连跑 ×3/×5 零报告），全量非图形套件 **203=202+1skip 零失败**三树一致；nm 钉住 libbreak_net.a 恰 63 导出；`ENGINE_BUILD_TESTS=OFF` 树与 CRYPTO=OFF 树构建成功。契约文档 `docs/design/transport_security.md`（信任链/nonce 重放论证/key 接缝/限速模型/生产 PKI 要求/已记录限制/NOT-delivered）。**未交付**：服务端产品与 server authority、per-device provisioning tooling、反篡改代码（成本模型文档 only）、应用消息级 replay window、消息/字节级限速、DTLS/QUIC、会话恢复、remote debug 通道；自签 fixture 仅供测试、无安全部署声明；Win32 lane 未跑、fuzz `Not Run`。任务报告 `.superpowers/sdd/2026-10-24-stage5-transport-security/task-{1..5}-report.md`。

- [x] Signed manifest/content-addressed package design（**超出 design**：Phase A 已交付格式 + 客户端离线验证实现 `break_update` 19/19 + `break_crypto` 20/20；下载/激活不在内——见下项）
- [x] Download/resume/A-B/rollback implementation plan（**客户端离线机制已交付**：Phase B（2026-10-24 Tasks 1-4，branch `sdd/stage5-update-client`，范围 `bb4a1a2e..HEAD`）——状态机 + A/B 槽（canonical state ≤64 KiB、write-ahead）、分块下载 + `.part` 字节级续传（崩溃代价 = 整个在途 chunk 从 0 重下，文档化）、CAS 去重、stage/activate/confirm/unstage/rollback（签名+策略先于一切传输，VERIFY/POLICY 零 fetch 三层钉死；min-rollback 地板 + staged 互斥 + unstage 语义；fresh 客户端 = 0.0.0）；`test_break_update_client` 43/43 + `test_break_update` 19/19 三树绿、契约 ctest 三树 6/6（nm 恰 28 导出）；传输仅经调用方 `BreakUpdateFetchFn` 回调（in-process fake 测试，**零 socket/HTTP/TLS/curl 代码**）。**未交付半侧**：真实传输接线、灰度客户端逻辑（客户端唯一旋钮 = 配置 channel）、服务端、签名后的在线流程；A/B 槽窗口（stage 回收 retained previous 槽）为文档化边界见 `docs/design/update_client.md` §7）
- [x] Crash context/spool/upload/symbolization design（**客户端半侧已交付**：Phase C（2026-10-24 Tasks 1-4，branch `sdd/stage5-crash-reporting`，范围 `3bf56df6..HEAD`）——capture（async-signal-safe、白名单 handler、一次性捕获、argv/env 钳制）+ canonical 记录 + 有界 spool（inbox 恢复、retention 16/16/16）+ 纯函数 redact（§6 执行点）+ 上传接缝 `BreakCrashUploadFn`（app 拥有传输、5 次丢弃、at-least-once）+ 符号化契约（服务端消费 build-id + 模块 basename + load offset + RIP；客户端永不符号化）；`test_break_crash` 36/36 三树绿、契约 ctest 三树 7/7（nm 恰 36 导出）；契约文档 `docs/design/crash_reporting.md`。**未交付半侧**：服务端符号化/聚类/回归、真实上传传输、GPU/RHI/网络/输入摘要捕获（app context-blob 后续集成）、minidump/PE、Windows SEH）
- [x] Authentication/replay/rate-limit threat model（威胁模型**文档**已交付——`security_threat_model.md` §5/§7；**实现半侧已交付**：Phase D（2026-10-24 Tasks 1-5，branch `sdd/stage5-transport-security`）——TLS 模式 + CHALLENGE/AUTH-v2 + key_id→PSK 接缝 + max_age + 出站单调序号 + admission 限速（契约 `docs/design/transport_security.md`）；**未交付**：per-device provisioning tooling、应用消息级 replay window、消息/字节级限速）
- [x] Anti-cheat trust-boundary design（信任边界 + 反篡改成本模型设计已交付——`security_threat_model.md` §2；任何反篡改**代码**未交付）
- [ ] Security review and release configuration tests（安全评审**文档**已交付——`security_threat_model.md`（§10 NOT-delivered 清单经代码交叉核对）；release 配置**测试**已于 2026-10-28 交付 `test_release_config_contract`（运行时二进制无远程/更新符号、测试钩子白名单棘轮、`editor --remote` fail-closed），同时修复 GCC 16 Release 构建失败与 Release 下实际未测崩溃捕获的问题；发布二进制中的 26 个测试钩子已于同日全部移出（`break_net_test`、`engine_rhi_vulkan_alloc_fault` 测试变体，契约白名单为空）；remote debug 通道默认不存在——Stage 4 Phase 4 起 `editor` 工具有仅经显式 `--remote` 创建、TLS + AUTH-v2 必需的 dev remote session（`docs/design/editor_remote.md` §2），engine/demos 无远端表面（nm 钉住））

## Stage 6 — Graphics API lifecycle

- [x] Audit existing Vulkan/D3D12/Metal/headless plans（2026-10-25，只读审计，产物 `docs/cross_engine/graphics_backend_audit.md`：逐后端状态、OpenGL 移除门 11 条件核对（该门已于 2026-10-26 随 OpenGL 长期保留的决定取消）、17 项缺口及 owner；**未运行**任何 graphics/Metal/D3D12 测试，CI 产物未下载）
- [ ] Complete backend-specific remaining gaps in separate plans（审计 §4 已列 17 项缺口；其中 #7 废弃标记机制、#8 `auto` 默认值、#10 `windows-d3d12.yml` 在 master 上失败（WARP push-constant write-drop 门）、#11 D3D12 consumer 对等 无现有 plan 覆盖，需新建；#1/#2/#3/#6 需要设备/runner/维护者动作）
- [ ] Collect per-backend evidence
- [x] OpenGL policy（2026-10-26 维护者决定：**长期保留**——`fallback_chain` 最后一级降级方案 + 跨后端渲染对比基准，移除计划取消；`test_rhi_rollout_config_contract` 钉住链序与各平台 allowed，`test_rhi_golden_parity` 钉住 VK/GL golden 对应关系；GL goldens 已重生成，本机 GL/VK `test_vulkan` 均 ALL PASSED。**默认后端同日决定为 Vulkan**：`auto` 在 Linux/Windows 解析为 Vulkan（缺 Vulkan 依赖时带警告降级到 OpenGL），rollout v3 vulkan 居首，`test_rhi_backend_selection` 钉住；**运行时降级同日交付**（branch `sdd/rhi-runtime-fallback`）：默认 `auto` 构建同时链接 Vulkan + OpenGL，设备创建失败即在同一窗口降级到 OpenGL，`BREAK_RHI_BACKEND` / `BREAK_RHI_NO_FALLBACK` 可控；本机 Linux X11 实测，Windows/Wayland 未验；契约 `docs/design/rhi_runtime_backend.md`）

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

## Deferred / not-done ledger (2026-10-25, master `b747d6ed`)

> 集中记录已确认**没有做**的验证项与功能项，避免散落在各阶段注记里被遗漏。每项都应在后续单独立项（design → plan → TDD → review）后才能勾选。

### Validation not done

- [x] **Windows 上的运行**（2026-10-28 关闭测试层面）：CI 的 MSVC / MinGW / Clang / Clang ASan headless lane 构建并运行 `ctest -LE graphics`（含 `test_editor_shell`、`test_editor_i18n`、`test_editor_fonts`、`test_release_config_contract`），运行 40655375019 全部通过；维护者另在 Windows 本机跑过 Clang 四树全量（见 `docs/Implementation_Status.md` 2026-10-28 “远程 170 个提交在 Windows 上的同步验证”）。**仍未做**：窗口化 `editor.exe` 在 Windows 上的真实交互运行
- [x] **editor 协议专用 fuzzer**：2026-10-26 交付 `fuzz_editor_remote`（ids 4..13 全部处理器，经真实 envelope 解码与会话管理器；约 96 万条消息 ASan+UBSan 零报告），见 `docs/design/editor_remote.md` 末节
- [x] **editor 交互验证**（2026-10-28）：`--input-script` 脚本化输入经真实 `InputState` → BreakUI → myui → 控件/快捷键/gizmo，Vulkan 与 OpenGL 实机脚本覆盖工具栏、检查器、视口拾取、gizmo 拖拽、撤销/重做、命令面板、资源浏览器预览，全部通过；首跑发现并修复 BreakUI 吞掉所有鼠标按键的缺陷。见 `docs/design/editor_input_script.md`。**仍未做**：IME 文字、编辑框输入、拖放、右/中键相机拖动、Windows/macOS
- [ ] 跨平台 native/CI 证据：CI 已覆盖 Linux X11/Wayland（OpenGL/Vulkan lavapipe）、macOS Metal/MoltenVK、Windows headless、iOS 编译（运行 40655375019）；**未采集**：Android、Steam Deck 真机、D3D12 真 GPU、iOS 真机

### Features not delivered (carried from earlier phases)

- [ ] editor：remote render control 的剩余部分（渲染设置；**VIEW**=16 已于 2026-10-30 交付：网格/统计开关、相机复位与回读；**CAMERA_SET**=17 同日交付：经校验的完整相机位姿；remote **save/load** 已于 2026-10-30 交付：`BREAK_EDITOR_MSG_SAVE`=14、`LOAD`=15，只作用于本地配置的场景路径，LOAD 不丢弃未保存修改，见 `docs/design/editor_remote.md`；资源浏览器图片预览的纹理 hot reload 已于 2026-10-28 交付，见 `docs/design/editor_hot_reload.md` §8；材质/场景纹理 hot reload 未做；viewport shader hot reload 已于 2026-10-27 交付；render debugger 面板与场景 hot reload 已于 2026-10-26 交付，见 `docs/design/editor_render_debugger.md`、`docs/design/editor_hot_reload.md`）
- [ ] editor remote：生产凭证系统（provisioning/密钥存储；进程内 keyring 已于 2026-10-30 交付：最多 8 个设备密钥、运行时增加、吊销即关闭相关会话，见 `docs/design/editor_remote.md`）、WAN/多客户端管理、remote undo-stack 共享（服务端 transport close 与认证 deadline 已于 2026-10-26 交付，见 `docs/design/editor_remote.md` 末节）
- [ ] Lua：LuaJIT 可选后端评估（gating：baseline 合同稳定）
- [ ] Security：server authority 实现；client anti-tamper 代码；应用消息级 replay window；消息/字节级限速；per-device key provisioning tooling
- [ ] Update/crash：在线更新真实传输、灰度、服务端；crash 服务端符号化/聚类/回归统计、真实上传传输、GPU/RHI/网络/输入摘要捕获
- [ ] Stage 6：各图形后端（Vulkan/D3D12/Metal/headless）缺口计划、逐后端证据（OpenGL 废弃门已取消，见 Stage 6 OpenGL policy）
- [ ] X11 全屏在有窗口管理器的会话下不稳定：`test_platform_x11_runtime` 在 GNOME Xwayland（Mutter）上间歇失败，原因与调查记录见 `docs/Implementation_Status.md` 2026-10-28 条目；CI（Xvfb，无 WM）不受影响
- [ ] Final independent code review
