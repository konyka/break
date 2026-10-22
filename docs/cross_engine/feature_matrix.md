# 跨引擎 Feature Matrix（阶段 1）

## 简介

本文是阶段 1 的证据优先特性矩阵，比较 CryENGINE v3.1.2、BW191 1.9.1、Unreal Engine 5.8.3 与 Break 在同一组 17 个模块上的已知边界。它不是功能排名，也不把架构描述自动等同于可运行实现；目标是为后续缺口分析提供可复核的入口。

本文件按统一顺序覆盖 17 行：模块系统、ECS/实体、世界/场景、任务、线程/消息、网络、UI/输入、渲染/RHI、物理、音频、资源/热重载、编辑器、诊断/远程调试、崩溃上传、在线更新、安全/反作弊、大世界/流式加载。

## 证据口径

- Break 只采用当前仓库的 [`Implementation_Status.md`](../Implementation_Status.md)、[`Architecture_Overview.md`](../Architecture_Overview.md)、设计文档或源码路径；“已实现”仅用于有运行时目标或明确 API/测试证据的情况。
- `基础/聚焦` 表示已有基础或 focused/test-only API，但不代表正式 engine/demo runtime 集成；尤其 ECS replication/AoI 与 Snowflake network 的边界见 [`Architecture_Overview.md` 的对应章节](../Architecture_Overview.md#ecs-snapshot-replication-aoi-边界) 和 [`Implementation_Status.md`](../Implementation_Status.md)。
- 外部引擎只引用仓库现有架构资料。资料没有明确覆盖的能力统一记为 `资料不足`，不根据产品常识补全。
- 每个单元格先给状态，再给最短证据指针；证据指针是文档链接、章节链接或源码路径。源码路径只表示仓库中存在该边界，不额外声称产品级集成。

## 状态术语

| 状态 | 含义 |
|---|---|
| `已实现` | 有明确的运行时模块/API 与相应实现证据；不等于所有平台或产品能力完整。 |
| `基础/聚焦` | 有基础、设计或 focused/test-only 实现，但正式 runtime、引擎目标或产品集成边界仍未闭合。 |
| `资料描述` | 外部资料明确描述了该能力，但本阶段没有独立运行验证。 |
| `资料不足` | 现有资料没有足够证据判断；禁止推测为有或无。 |
| `未实现` | Break 当前证据明确列为未实现或 fail-closed；不是对外部引擎的推断。 |

## 17 模块矩阵

| 模块 | CryENGINE | BW191 | Unreal | Break |
|---|---|---|---|---|
| 1. 模块系统 | `资料描述` — 模块化 DLL；[`CryENGINE_Architecture.md#3-引擎核心模块`](../CryENGINE_Architecture.md#3-引擎核心模块) | `资料描述` — client/server/common 分层；[`BW191_Architecture.md#3-核心源码架构-bigworldsrc`](../BW191_Architecture.md#3-核心源码架构-bigworldsrc) | `资料描述` — 模块/插件目录与构建章节；[`00_概要设计.md#2-全引擎总体架构`](../ue5.8.3/00_概要设计.md#2-全引擎总体架构) | `已实现` — C11 engine/framework 分层与目录边界；[`Architecture_Overview.md#2-顶层目录结构`](../Architecture_Overview.md#2-顶层目录结构)、`engine/src/` |
| 2. ECS/实体 | `资料描述` — CryEntitySystem 实体与组件；[`CryENGINE_Architecture.md#37-cryentitysystem---实体系统`](../CryENGINE_Architecture.md#37-cryentitysystem---实体系统) | `资料描述` — entity/entity_manager；[`BW191_Architecture.md#31-客户端-srcclient`](../BW191_Architecture.md#31-客户端-srcclient) | `资料描述` — CoreUObject/Actor/Component 设计；[`04_engine_framework.md`](../ue5.8.3/design/04_engine_framework.md) | `基础/聚焦` — ECS、snapshot/delta/schema 已有 focused evidence；[`Architecture_Overview.md#ecs-snapshot-replication-aoi-边界`](../Architecture_Overview.md#ecs-snapshot-replication-aoi-边界)、`engine/src/ecs/` |
| 3. 世界/场景 | `资料描述` — 场景加载、RenderNode、sector；[`CryENGINE_Architecture.md#31-cry3dengine---3d-渲染引擎`](../CryENGINE_Architecture.md#31-cry3dengine---3d-渲染引擎) | `资料描述` — Cell 分区与 chunk portal；[`BW191_Architecture.md#33-公共模块-srccommon`](../BW191_Architecture.md#33-公共模块-srccommon)、[`BW191_Architecture.md#7-关键设计模式`](../BW191_Architecture.md#7-关键设计模式) | `资料描述` — UWorld/World Partition 章节；[`05_world_partition_streaming.md`](../ue5.8.3/design/05_world_partition_streaming.md) | `基础/聚焦` — renderer/scene 路径与 ECS world；[`Architecture_Overview.md#4-核心模块总览`](../Architecture_Overview.md#4-核心模块总览)、`engine/src/renderer/` |
| 4. 任务 | `资料不足` — 现有资料未给出独立任务调度证据 | `资料不足` — 现有资料未给出独立任务调度证据 | `资料描述` — Tick/Task 机制有接口与实现章节；[`31_message_event_mechanisms.md#3158-taskpromisefuturetickerlatent`](../ue5.8.3/design/31_message_event_mechanisms.md#3158-taskpromisefuturetickerlatent) | `已实现` — TaskSystem 与 worker 约束；[`Architecture_Overview.md#线程与任务边界`](../Architecture_Overview.md#线程与任务边界)、`engine/src/task/task.h` |
| 5. 线程/消息 | `资料不足` — 现有资料未给出统一线程/消息总线证据 | `资料不足` — 现有资料未给出统一线程/消息总线证据 | `资料描述` — 消息总线、委托、异步回调；[`31_message_event_mechanisms.md`](../ue5.8.3/design/31_message_event_mechanisms.md) | `已实现` — GameThread/network thread 边界与有界 event queue；[`Architecture_Overview.md#snowflake-c11-网络适配器边界`](../Architecture_Overview.md#snowflake-c11-网络适配器边界)、`engine/src/network/` |
| 6. 网络 | `资料描述` — RMI、状态同步、预测/回滚；[`CryENGINE_Architecture.md#38-cry网络---网络系统`](../CryENGINE_Architecture.md#38-cry网络---网络系统) | `资料描述` — Login/Base/Cell 服务和连接管理；[`BW191_Architecture.md#32-服务端-srcserver`](../BW191_Architecture.md#32-服务端-srcserver)、[`BW191_Architecture.md#31-客户端-srcclient`](../BW191_Architecture.md#31-客户端-srcclient) | `资料描述` — Networking/Replication 章节；[`11_networking_replication.md`](../ue5.8.3/design/11_networking_replication.md) | `基础/聚焦` — Snowflake adapter/session/fragment focused API；正式 engine/demo 集成仍受边界限制；[`Implementation_Status.md`](../Implementation_Status.md)、`engine/src/network/` |
| 7. UI/输入 | `资料描述` — CryInput、CryFont；[`CryENGINE_Architecture.md#310-其他模块`](../CryENGINE_Architecture.md#310-其他模块) | `资料描述` — GUI app、客户端 UI 资源；[`BW191_Architecture.md#31-客户端-srcclient`](../BW191_Architecture.md#31-客户端-srcclient)、[`BW191_Architecture.md#4-fantasydemo-示例游戏`](../BW191_Architecture.md#4-fantasydemo-示例游戏) | `资料描述` — Slate/UMG/Input；[`10_slate_umg_input.md`](../ue5.8.3/design/10_slate_umg_input.md) | `已实现` — platform input 与 UI/font；[`Architecture_Overview.md#4-核心模块总览`](../Architecture_Overview.md#4-核心模块总览)、`engine/src/platform/`、`engine/src/ui/` |
| 8. 渲染/RHI | `资料描述` — Cry3DEngine 与 D3D9/NULL RenderDLL；[`CryENGINE_Architecture.md#31-cry3dengine---3d-渲染引擎`](../CryENGINE_Architecture.md#31-cry3dengine---3d-渲染引擎)、[`CryENGINE_Architecture.md#32-renderdll---渲染后端`](../CryENGINE_Architecture.md#32-renderdll---渲染后端) | `资料描述` — 客户端渲染、shader/resource 资料；[`BW191_Architecture.md#31-客户端-srcclient`](../BW191_Architecture.md#31-客户端-srcclient)、[`BW191_Architecture.md#4-fantasydemo-示例游戏`](../BW191_Architecture.md#4-fantasydemo-示例游戏) | `资料描述` — RHI/RenderCore/RDG/Renderer；[`06_rhi.md`](../ue5.8.3/design/06_rhi.md)、[`07_rendercore_rdg_renderthread.md`](../ue5.8.3/design/07_rendercore_rdg_renderthread.md) | `已实现` — 编译期单后端 RHI 与 VK/Metal/D3D12/GL/headless 边界；[`Architecture_Overview.md#rhi-分层2026-10-14-起`](../Architecture_Overview.md#rhi-分层2026-10-14-起)、`engine/src/rhi/` |
| 9. 物理 | `资料描述` — 刚体、碰撞、角色、载具、布料、破坏；[`CryENGINE_Architecture.md#36-cryphysics---物理引擎`](../CryENGINE_Architecture.md#36-cryphysics---物理引擎) | `资料描述` — physics Python binding 与客户端体系；[`BW191_Architecture.md#33-公共模块-srccommon`](../BW191_Architecture.md#33-公共模块-srccommon) | `资料描述` — Chaos/Physics；[`12_physics_chaos.md`](../ue5.8.3/design/12_physics_chaos.md) | `基础/聚焦` — Physics 模块列入架构，但本矩阵不扩大为产品级能力；[`Architecture_Overview.md#4-核心模块总览`](../Architecture_Overview.md#4-核心模块总览)、`engine/src/physics/` |
| 10. 音频 | `资料描述` — CrySoundSystem 与 3D 音效；[`CryENGINE_Architecture.md#310-其他模块`](../CryENGINE_Architecture.md#310-其他模块) | `资料描述` — FMOD runtime 与 audio 资源；[`BW191_Architecture.md#顶层目录结构`](../BW191_Architecture.md#顶层目录结构) | `资料描述` — Audio 章节；[`14_audio.md`](../ue5.8.3/design/14_audio.md) | `已实现` — miniaudio audio API/device；[`Architecture_Overview.md#linux-已验证范围`](../Architecture_Overview.md#linux-已验证范围)、`engine/src/audio/` |
| 11. 资源/热重载 | `资料描述` — 模型/网格编译和资源目录；[`CryENGINE_Architecture.md#31-cry3dengine---3d-渲染引擎`](../CryENGINE_Architecture.md#31-cry3dengine---3d-渲染引擎)、[`CryENGINE_Architecture.md#顶层目录结构`](../CryENGINE_Architecture.md#顶层目录结构) | `资料描述` — res、doc_watcher、资源工具；[`BW191_Architecture.md#33-公共模块-srccommon`](../BW191_Architecture.md#33-公共模块-srccommon)、[`BW191_Architecture.md#6-文档体系`](../BW191_Architecture.md#6-文档体系) | `资料描述` — Assets/Cook/Package/IO 与 DDC；[`20_assets_cook_package_io.md`](../ue5.8.3/design/20_assets_cook_package_io.md)、[`09_shader_material_ddc.md`](../ue5.8.3/design/09_shader_material_ddc.md) | `已实现` — asset/hotreload/vfs 与 filewatch；[`Architecture_Overview.md#4-核心模块总览`](../Architecture_Overview.md#4-核心模块总览)、[`Architecture_Overview.md#linux-已验证范围`](../Architecture_Overview.md#linux-已验证范围)、`engine/src/asset/` |
| 12. 编辑器 | `资料描述` — Sandbox/editor 工具语境；[`CryENGINE_Architecture.md#项目概述`](../CryENGINE_Architecture.md#项目概述) | `资料描述` — content tools/reference 与运维 tools；[`BW191_Architecture.md#6-文档体系`](../BW191_Architecture.md#6-文档体系)、[`BW191_Architecture.md#2-顶层目录结构`](../BW191_Architecture.md#2-顶层目录结构) | `资料描述` — Editor Core 章节与插件目录；[`22_editor_core.md`](../ue5.8.3/design/22_editor_core.md) | `资料不足` — 架构文档将 editor 列为应用层方向，但未提供正式 editor runtime 证据；[`Architecture_Overview.md#3-分层架构设计`](../Architecture_Overview.md#3-分层架构设计) |
| 13. 诊断/远程调试 | `资料描述` — CVar、调试/性能分析；[`CryENGINE_Architecture.md#关键设计模式`](../CryENGINE_Architecture.md#关键设计模式) | `资料描述` — watcher、message_logger、系统监控工具；[`BW191_Architecture.md#32-服务端-srcserver`](../BW191_Architecture.md#32-服务端-srcserver) | `资料描述` — Diagnostics/Trace/Testing；[`23_diagnostics_tracing_testing.md`](../ue5.8.3/design/23_diagnostics_tracing_testing.md) | `已实现` — log/profiler、validation、trace/测试边界；[`Architecture_Overview.md#4-核心模块总览`](../Architecture_Overview.md#4-核心模块总览)、[`Architecture_Overview.md#9-平台支持`](../Architecture_Overview.md#9-平台支持)、`engine/src/core/` |
| 14. 崩溃上传 | `资料不足` — 现有架构资料未给出 crash upload 证据 | `资料不足` — 现有架构资料未给出 crash upload 证据 | `资料不足` — 本阶段资料未给出 crash upload 产品服务证据 | `资料不足` — 当前状态/架构资料未确认上传服务；仅有本地诊断和测试证据，不能外推为上传 |
| 15. 在线更新 | `资料不足` — 现有架构资料未给出在线更新证据 | `资料不足` — 现有架构资料未给出在线更新证据 | `资料不足` — 本阶段资料未给出在线更新产品服务证据 | `未实现` — 当前 Session/Protocol 边界明确列出 online update 未实现；[`Implementation_Status.md`](../Implementation_Status.md) |
| 16. 安全/反作弊 | `资料不足` — 现有架构资料未给出 anti-cheat 证据 | `资料不足` — 现有架构资料未给出 anti-cheat 证据 | `资料不足` — 本阶段资料未给出 anti-cheat 产品服务证据 | `未实现` — cryptographic authentication 与额外 security 集成明确未实现；[`Implementation_Status.md`](../Implementation_Status.md)、[`Architecture_Overview.md#ecs-snapshot-replication-aoi-边界`](../Architecture_Overview.md#ecs-snapshot-replication-aoi-边界) |
| 17. 大世界/流式加载 | `资料描述` — sector/场景管理；[`CryENGINE_Architecture.md#37-cryentitysystem---实体系统`](../CryENGINE_Architecture.md#37-cryentitysystem---实体系统)、[`CryENGINE_Architecture.md#31-cry3dengine---3d-渲染引擎`](../CryENGINE_Architecture.md#31-cry3dengine---3d-渲染引擎) | `资料描述` — Cell 分区、chunk portal、空间分块；[`BW191_Architecture.md#33-公共模块-srccommon`](../BW191_Architecture.md#33-公共模块-srccommon)、[`BW191_Architecture.md#7-关键设计模式`](../BW191_Architecture.md#7-关键设计模式) | `资料描述` — World Partition/Streaming；[`05_world_partition_streaming.md`](../ue5.8.3/design/05_world_partition_streaming.md) | `资料不足` — 当前架构资料列出 renderer/world，但未证明产品级大世界 streaming runtime；[`Architecture_Overview.md#4-核心模块总览`](../Architecture_Overview.md#4-核心模块总览) |

## 与 Break 的比较边界

- “有模块目录”不等于“有正式 runtime”；例如 Break 的 focused ECS/replication sources 当前直接编入测试 target，不能据此宣称已接入 `engine` static library 或 demo。
- “有网络协议/适配器测试”不等于完整在线服务；当前证据仍把真实 session integration 的部分、玩家认证 backend、Lua gameplay callback、editor RPC、online update 和 security 集成列为边界。
- “已实现”只表示本行所指的局部能力达到证据口径，不表示跨平台、产品化、编辑器、运营服务或反作弊完整。
- 外部引擎的 `资料描述` 只表达仓库资料的明确陈述；本矩阵没有复核外部源码、运行时或商业部署，因此不能与 Break 的本地 focused 测试数字直接做强弱排序。

## 来源与限制

- 主要来源：[`CryENGINE_Architecture.md`](../CryENGINE_Architecture.md)、[`BW191_Architecture.md`](../BW191_Architecture.md)、[`ue5.8.3/00_概要设计.md`](../ue5.8.3/00_概要设计.md)、UE 5.8.3 各模块设计章节、[`Architecture_Overview.md`](../Architecture_Overview.md)、[`Implementation_Status.md`](../Implementation_Status.md)。
- 本阶段未发现独立的 `cryengine_inventory.md`、`bw191_inventory.md` 或 `unreal_inventory.md`；因此本文件直接引用现有架构资料，不伪造 inventory 证据。
- 外部引擎的崩溃上传、在线更新、安全/反作弊，以及 CryENGINE/BW191 的任务、线程/消息等未被现有资料明确覆盖，保留为 `资料不足`。
- Break 的正式 runtime、产品级 editor、在线服务、上传服务和大世界 streaming 不能仅凭目录、设计图或 focused/test-only 代码确认；这些事项留待后续阶段单独核验。

## 补充证据修订（2026-10-22）

本次补充勘察取得两类新证据：CryENGINE v3.1.2 实际源码树（`/home/timeshift/opensource/game_engine/CryENGINE_FullCode_PC_v3_1_2_1742/Code`）和 BW191 设计文档树（`/home/timeshift/opensource/game_engine/BW191/docs/design`，10 个文件）。下表只列出状态发生变化的单元格；未列出的单元格维持上表原状。详细证据见 [`cryengine_inventory.md` 附录 A](cryengine_inventory.md) 与 [`bw191_inventory.md` 附录 A](bw191_inventory.md)。

| 模块 | 列 | 原状态 | 修订后状态 | 最短证据指针 |
|---|---|---|---|---|
| 4. 任务 | CryENGINE | `资料不足` | `资料描述` | `CryCommon/IThreadTask.h`、`CrySystem/ThreadTask.cpp`、`CrySystem/StreamEngine.cpp`、`CryAnimation/AnimationThreadTask.h` |
| 4. 任务 | BW191 | `资料不足` | `资料描述` | `docs/design/02-客户端详细设计.md` §2 MainLoopTask；`07-线程与渲染同步.md` §3 BgTaskManager（优先级 0–128） |
| 5. 线程/消息 | CryENGINE | `资料不足` | `资料描述` | `CryCommon/CryThread*.h`（windows/pthreads/ps3 实现）、`MultiThread.h`、`MultiThread_Containers.h`；无统一消息总线，模块经 `gEnv` 接口指针互访 |
| 5. 线程/消息 | BW191 | `资料不足` | `资料描述` | `07-线程与渲染同步.md`：客户端无独立渲染线程（主线程承担 D3D 绘制）；`cstdmf/concurrency.hpp` SimpleMutex/SimpleSemaphore |
| 8. 渲染/RHI | BW191 | `资料描述`（概览级） | `资料描述`（细化） | `03-共享库详细设计.md` §8–10：moo 库封装 Direct3D9（RenderContext/ManagedEffect/RenderTarget）；无多后端 RHI 抽象 |
| 9. 物理 | BW191 | `资料描述`（绑定线索） | `资料描述`（细化） | `physics2` 三角碰撞/hull + 客户端预测/服务器 forcedPosition 纠正；服务端 12 种 Controller + waypoint 导航网格；无独立刚体求解器（设计非目标） |
| 10. 音频 | BW191 | `资料描述` | `资料描述`（细化） | `fmodsound`/`xactsnd` 双实现 + `sound` 抽象层；混音线程在 FMOD 库内部 |
| 13. 诊断/远程调试 | CryENGINE | `资料描述` | `资料描述`（远程通道确认） | `CryCommon/IRemoteControl.h`、`CryNetwork/RemoteControl/`、`Http/SimpleHttpServer.cpp`、`DebugKit/`、`CryScriptSystem/LuaDebugger/` |
| 13. 诊断/远程调试 | BW191 | `资料描述` | `资料描述`（细化） | Watcher（端口 20017）+ Python 远程端口（BaseApp 40000+id / CellApp 50000+id）+ web_console + message_logger |
| 14. 崩溃上传 | CryENGINE | `资料不足` | `资料描述`（客户端侧） | `CrySystem/DebugCallStack.cpp`、`WindowsErrorReporting.cpp`（WER）、`JiraClient.cpp`；服务端符号化/聚合仍 `资料不足` |
| 14. 崩溃上传 | BW191 | `资料不足` | `资料不足`（维持，附弱证据） | Reviver 进程拉起、`src/lib/geh`、`third_party/stack_walker`；无崩溃上传客户端/服务端设计 |
| 14. 崩溃上传 | Unreal | `资料不足` | `资料描述` | [`23_diagnostics_tracing_testing.md`](../ue5.8.3/design/23_diagnostics_tracing_testing.md) CrashContext/CrashReportClient；与 [`unreal_inventory.md` 第 14 节](unreal_inventory.md) 一致 |
| 15. 在线更新 | CryENGINE | `资料不足` | `资料描述`（下载机制） | `CrySystem/DownloadManager.cpp`/`HTTPDownloader.cpp`、`CryAction/Network/DownloadTask.cpp`；版本化 patcher/回滚闭环仍 `资料不足` |
| 15. 在线更新 | BW191 | `资料不足` | `资料不足`（维持，附弱证据） | `DEFAULT_UPDATER_ENABLED=false` 常量、登录 digest MD5 校验、受控关闭滚动维护；无补丁下载设计 |
| 15. 在线更新 | Unreal | `资料不足` | `资料描述` | [`20_assets_cook_package_io.md`](../ue5.8.3/design/20_assets_cook_package_io.md) ChunkDownloader/MobilePatchingUtils/BuildPatchServices |
| 16. 安全/反作弊 | CryENGINE | `资料不足` | `资料描述` | `CryNetwork/AntiCheat/DefenceContext.cpp`、`Context/Authentication.cpp`、AES `Cryptography/rijndael.cpp`、`Protocol/ExponentialKeyExchange.cpp`、`CryCommon/CopyProtection.h` |
| 16. 安全/反作弊 | BW191 | `资料不足` | `资料描述` | `04-Mercury网络接口.md` §12：RSA 登录 → Blowfish 信道、v49/v51 防重放、SessionKey 认证、脚本 MD5 digest、RateLimitMessageFilter |
| 16. 安全/反作弊 | Unreal | `资料不足` | `资料描述`（接口级） | [`25_plugins_catalog_experimental_editor.md`](../ue5.8.3/design/25_plugins_catalog_experimental_editor.md) Online 子系统 EOS/AntiCheat 插件条目；产品级部署策略仍 `资料不足` |
| 17. 大世界/流式加载 | CryENGINE | `资料描述` | `资料描述`（边界澄清） | 无整关卡流送（ILevelSystem 无 streaming API）；资源级流送：`IStreamEngine`、`ObjManStreaming.cpp/StatObjStream.cpp`、`terrain_sector*.cpp`、`PrecacheLevel` |
| 17. 大世界/流式加载 | BW191 | `资料描述` | `资料描述`（细化） | Space/Cell 分流 + CellAppMgr 负载均衡与实体迁移、Ghost（500m）、Witness AoI + DataLoD/VolatileInfo 带宽分级、ChunkManager 网格流式 |

修订口径说明：

- 上述升级为“资料描述（源码/设计文档证据）”，仍不等于本工作区编译或运行过对应引擎。
- CryENGINE 的 `Code/docs/design/` 中文文档仅作线索；BW191 的 `cellappmgr` 实现与 `BgTaskManager.cpp` 不在仓库，相应结论以接口/文档契约为限。
- Break 列无变化；Break 的缺口追踪以 [`missing_capabilities.md`](missing_capabilities.md) 为准。
