# CryENGINE Inventory（Stage 1）

## 简介

本文是 Stage 1 的 CryENGINE 侧 inventory，目标是为跨引擎比较提供可追溯的事实清单，而不是补齐 CryENGINE 的未知实现细节。本文覆盖统一的 17 个模块，顺序与 Stage 1 设计一致。CryENGINE 的证据范围限于仓库中的 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md)；该文档描述的是 CryENGINE v3.1.2 / Build 1742 的 PC 源码架构，不能自动代表其他版本、平台或产品线。

## 证据口径

- **证据优先**：CryENGINE 的能力只在 `docs/CryENGINE_Architecture.md` 明确记载时列为“文档已知”；未在该来源中出现的能力标为 `资料不足`，不按行业常识推测。
- **来源类型**：本文件引用仓库内文档的章节和路径；文档中列出的源码文件或目录是架构证据，不等于本次重新编译或运行验证。
- **Break 对照**：Break 的状态只引用当前 [`docs/Implementation_Status.md`](../Implementation_Status.md)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md) 或明确源码路径。`focused/test-only` 不写成正式 runtime 能力。
- **状态限制**：CryENGINE 侧的“已知”表示资料有记载，不表示本工作区拥有或验证了 CryENGINE 源码。`资料不足` 是证据状态，不是对能力不存在的判断。

## 1. 模块系统

- **范围**：引擎核心模块、游戏层和模块间接口/装载边界。
- **已知能力**：CryENGINE 采用模块化 DLL 架构；`Code/CryEngine/` 下列出 Cry3DEngine、CryAction、CryAISystem、CryAnimation、CryCommon、CryEntitySystem、CryFont、CryInput、CryMovie、CryNetwork、CryPhysics、CryScriptSystem、CrySoundSystem、CrySystem 和 RenderDLL 等模块。CryCommon 通过接口解耦子系统，CrySystem 负责初始化和主循环。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §1、§3、§3.10、§5、§6；证据中的 `Code/CryEngine/`、`Game/`、`Tools/` 目录结构。
- **与 Break 的比较边界**：Break 的核心为纯 C11，引擎/框架/应用分层见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §2–§3；目录与接口边界不能直接等同于 CryENGINE DLL 边界。

## 2. ECS / Entity

- **范围**：实体创建、组件、实体生命周期和对象查询。
- **已知能力**：资料描述 CryEntitySystem 为基于组件的实体管理，包含实体创建/销毁/查询、RenderMesh/Physics/Script 等组件注册、实体池和区域（Sector）管理；CryAction 还包含 GameObjects。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3.3、§3.7，目录名 `Code/CryEngine/CryEntitySystem/`。
- **与 Break 的比较边界**：Break 的 ECS 路径为 `engine/src/ecs/ecs.c`、`engine/src/ecs/ecs_system.c`；snapshot/schema/delta/replication 目前有 focused API，但其正式 runtime 集成边界见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §ECS Snapshot / Replication / AoI 及 [`docs/Implementation_Status.md`](../Implementation_Status.md) 最新 ECS/network 条目。CryENGINE 资料未提供 ECS 查询语义或测试证据，不能进一步对比。

## 3. World / Scene

- **范围**：世界、场景、区域组织、场景加载和可见性相关对象。
- **已知能力**：Cry3DEngine 负责场景管理、场景加载、可见性裁剪、光照、阴影和地形；资料还列出 Sector 管理、RenderNode、CGF 模型加载、MeshCompiler、IsoOctree 等组件。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3.1、§3.7，`Cry3DEngine/`、`CGF/`、`MeshCompiler/`、`IsoOctree/`。
- **与 Break 的比较边界**：Break 的场景/渲染边界以 `engine/src/renderer/` 与 `engine/src/asset/` 为准；ECS World/Snapshot 的线程和结构屏障边界见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §ECS Snapshot / Replication / AoI。CryENGINE 资料没有给出完整 World API、持久化格式或运行时场景测试，标为 `资料不足`。

## 4. Tasks

- **范围**：任务调度、异步工作和并行执行。
- **已知能力**：资料不足。CryENGINE 参考文档没有明确描述独立的 task/job 调度器、队列语义或调度测试。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) 中未提供 Tasks/Job/ThreadPool 专门章节或可核验接口。
- **与 Break 的比较边界**：Break 有 `engine/src/task/task.c`、`engine/src/task/task.h`；线程/等待约束见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §线程与任务边界。不能据此推断 CryENGINE 的对应实现或性能。

## 5. Threads / Messages

- **范围**：线程模型、跨线程消息、主循环和线程安全边界。
- **已知能力**：CrySystem 负责引擎初始化和主循环；除此之外，资料不足，未给出 worker thread、消息总线或跨线程 ownership 规则。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3.10 对 CrySystem 的职责描述。
- **与 Break 的比较边界**：Break 的 Task/平台线程接口分别位于 `engine/src/task/`、`engine/src/core/platform_thread.h`，网络线程与 GameThread 的边界见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §Snowflake C11 网络适配器边界。CryENGINE 消息语义不能从模块名称推断。

## 6. Networking

- **范围**：连接模型、远程调用、同步、预测和带宽管理。
- **已知能力**：资料描述 CryNetwork 支持客户端/服务端架构、RMI、状态同步、网络预测和回滚、带宽优化；CryAction 也列出 Network 子系统。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3.3、§3.8，`Code/CryEngine/CryNetwork/`。
- **与 Break 的比较边界**：Break 的网络适配器和 Session 源码在 `engine/src/network/break_net_adapter.*`、`engine/src/network/break_session.*`；当前真实 loopback、bounded stop 和 envelope/session focused 证据及正式集成限制见 [`docs/Implementation_Status.md`](../Implementation_Status.md) 网络条目。CryENGINE 资料没有协议格式、传输库或验证记录，不能推断其生产级覆盖。

## 7. UI / Input

- **范围**：用户输入、字体/UI 和游戏内界面。
- **已知能力**：CryInput 提供键盘、鼠标、手柄输入；CryFont 提供 TrueType 字体渲染；Game 脚本目录包含 UI；CryAction 包含 ForceFeedbackSystem。资料没有给出完整 UI 框架 API。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3、§3.10、§4，`CryInput/`、`CryFont/`、`Game/Scripts/UI/`。
- **与 Break 的比较边界**：Break 的 UI/input 路径为 `engine/src/ui/`、`engine/src/platform/`；输入平台范围见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §平台支持。CryENGINE 资料只足以确认输入和字体模块，不能确认编辑器 UI、布局系统或跨线程 UI 规则。

## 8. Rendering / RHI

- **范围**：场景渲染、后处理、着色器、图形 API 后端和空渲染路径。
- **已知能力**：Cry3DEngine 负责主渲染循环、光照、阴影、地形、遮挡/Z-buffer 裁剪、云、贴花等；RenderDLL 提供可插拔后端，文档列出 D3D9 主渲染器和 NULL 渲染器，并列出 HDR、Bloom、SSAO、DOF 等后处理、纹理和着色器目录。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3.1–§3.2；`RenderDLL/XRenderD3D9/`、`RenderDLL/XRenderNULL/`。
- **与 Break 的比较边界**：Break 的公共 RHI 与后端位于 `engine/src/rhi/`，当前后端和证据等级见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §9、§RHI 分层；Break 的渲染器位于 `engine/src/renderer/`。CryENGINE 文档不提供 D3D9 运行时测试收据，不能与 Break 的 GPU/runtime 证据做数值比较。

## 9. Physics

- **范围**：刚体、碰撞、角色、载具、布料和破坏。
- **已知能力**：CryPhysics 被描述为自研物理引擎，包含刚体动力学、碰撞检测、角色控制器、载具物理、布料模拟和破坏系统。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3.6，`Code/CryEngine/CryPhysics/`。
- **与 Break 的比较边界**：Break 的物理源码路径为 `engine/src/physics/physics.c`、`engine/src/physics/character.c`、`engine/src/physics/bvh.c`；CryENGINE 资料没有求解器、碰撞层、测试或集成边界，不能推断两者能力等价。

## 10. Audio

- **范围**：音频播放、3D 音频、设备和运行时音频控制。
- **已知能力**：CrySoundSystem 提供音频播放和 3D 音效；更细的混音、设备、资源或线程模型资料不足。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3.10，`Code/CryEngine/CrySoundSystem/`。
- **与 Break 的比较边界**：Break 音频入口为 `engine/src/audio/audio.c`，架构概览标明基于 miniaudio；见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §4、§8。双方的设备和空间化语义没有共同测试口径。

## 11. Assets / Hot Reload

- **范围**：模型/纹理/字体等资源加载、离线编译、虚拟文件系统和热重载。
- **已知能力**：Cry3DEngine 资料列出 CGF 模型格式加载、MeshCompiler、场景加载、纹理管理、着色器目录；CrySystem 列出内存管理。热重载、VFS、资源编译器的完整运行时契约资料不足；顶层结构只列出 `Bin32/rc/` 资源编译器。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §1、§2、§3.1、§3.2。
- **与 Break 的比较边界**：Break 的资源路径为 `engine/src/asset/asset.c`、`engine/src/asset/vfs.c`、`engine/src/asset/async_loader.c`、`engine/src/platform/filewatch.c`；职责见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §4、§7。CryENGINE 的热重载只能记为 `资料不足`，不能因存在资源编译器目录而升级状态。

## 12. Editor

- **范围**：关卡/资源编辑器、可视化逻辑、实时预览和工具链。
- **已知能力**：CryENGINE 以 Sandbox 编辑器著称（简介）；CryAction 列出 LivePreview，FlowSystem 为可视化流程脚本系统；顶层结构列出 `Tools/` 和资源编译器。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §1、§2、§3.3、§6。
- **与 Break 的比较边界**：Break 架构概览的 `platform/` 是演示代码，当前网络 Session 条目明确 editor RPC 未实现；见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §2、§Snowflake C11 网络适配器边界和 [`docs/Implementation_Status.md`](../Implementation_Status.md) Session 未实现范围。Break 不应被描述为具有 CryENGINE Sandbox 对等物。

## 13. Diagnostics / Remote Debugging

- **范围**：日志、控制台变量、性能分析、调试可视化和远程调试。
- **已知能力**：CrySystem 包含 CVars（运行时可调参数）和内存管理；CryScriptSystem 提供脚本调试和性能分析支持；RenderDLL 的 D3D9 Profiler 目录被列出。远程调试协议或远程诊断工具资料不足。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3.2、§3.9、§3.10、§6。
- **与 Break 的比较边界**：Break 有 `engine/src/core/log.c`、`engine/src/core/profiler.c` 和 `engine/src/ui/debug_ui.c`；profiler provenance 约束见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §9。远程诊断不能从 Break 的本地 profiler 或 CryENGINE 的 CVar 描述推断存在。

## 14. Crash Upload

- **范围**：崩溃捕获、dump 生成、符号化、上传和服务端归档。
- **已知能力**：资料不足。CryENGINE 参考文档未描述 crash reporter、dump 上传协议或崩溃服务。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) 未列出 crash upload 组件或接口。
- **与 Break 的比较边界**：Break 的架构/状态文档没有把 crash upload 列为已实现运行时能力；不能以日志、断言、ASan 或 CTest 代替 crash upload 证据。需要后续专门收集源码或产品文档。

## 15. Online Update

- **范围**：在线补丁、版本检查、内容更新、回滚和更新安全。
- **已知能力**：资料不足。CryENGINE 参考文档没有在线更新、补丁分发或版本回滚描述。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) 未列出 online update 模块；`Bin32/` 只被描述为编译输出、DLL 和资源编译器目录，不能据此推断在线更新。
- **与 Break 的比较边界**：Break 的当前 Session/网络状态明确将 online update 列为未实现；见 [`docs/Implementation_Status.md`](../Implementation_Status.md) Session 未实现范围和网络集成边界。构建系统、资源热重载或网络 adapter 不等于在线更新。

## 16. Security / Anti-cheat

- **范围**：身份认证、传输安全、完整性、反作弊和安全更新。
- **已知能力**：资料不足。CryENGINE 参考文档未给出认证、加密、反作弊或安全服务的接口/证据。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) 未列出 security/anti-cheat 模块。
- **与 Break 的比较边界**：Break 的 Session 文档与状态记录明确指出 player authentication backend 和额外 security 功能未实现；fragment checksum 只是完整性校验而非加密认证，见 [`docs/Implementation_Status.md`](../Implementation_Status.md) 网络条目及 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §ECS Snapshot / Replication / AoI。不能把协议校验提升为反作弊能力。

## 17. Large-world / Streaming

- **范围**：大世界分区、流式加载、地形/区域流送和运行时内存控制。
- **已知能力**：Cry3DEngine 资料列出地形、场景加载、Sector 管理、IsoOctree、场景合并和体素数据节点；这些条目支持“场景/空间组织组件存在”的判断。完整 large-world 坐标策略、跨区域流式调度、持久化分块和网络 streaming 资料不足。
- **证据/来源**：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md) §3.1、§3.7，`Cry3DEngine/` 下 `IsoOctree/`、`CVoxDataNode.cpp`、`CVoxMeshNode.cpp` 等条目。
- **与 Break 的比较边界**：Break 有 `engine/src/renderer/terrain.c` 和 `engine/src/asset/mipmap_stream.c` / `engine/src/asset/async_loader.c`，但架构概览明确网络 replication/AoI focused API 与正式 runtime integration 分开，见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md) §ECS Snapshot / Replication / AoI。不能把 terrain 或 mipmap streaming 单独等同于 CryENGINE 的 large-world 系统。

## 与 Break 的比较边界

本文件只建立 CryENGINE 证据索引，不给出综合排名，也不把两个引擎的同名目录视为同一抽象。比较时应遵循以下边界：

1. CryENGINE 侧以 v3.1.2 / Build 1742 的仓库内架构文档为准；Break 侧以当前状态文档和源码路径为准。
2. CryENGINE 的“文档已知”与 Break 的“已实现”不是同一状态等级；前者没有本次构建/运行证明，后者也必须区分正式 runtime、focused/test-only 和未实现。
3. Break 的 snapshot/AoI/replication、Snowflake adapter 和 Session 有 focused 或 loopback 证据，但当前文档仍明确记录正式 engine/demo 集成边界；这些边界不可省略。
4. `资料不足` 只表示当前收集范围不能验证，不表示 CryENGINE 或 Break 必然没有该能力。
5. 性能、平台覆盖、商业产品服务和安全能力均没有共同的可复现实验条件，本阶段不做定量结论。

## 来源 / 限制

- 主要来源：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md)。该来源声明其对象为 CryENGINE v3.1.2 / Build 1742 PC 源码，并提供模块、目录和职责摘要。
- Break 状态来源：[`docs/Implementation_Status.md`](../Implementation_Status.md)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md)，以及各模块在 `engine/src/` 下的路径。
- 本文件未访问外部 Crytek 文档、未编译 CryENGINE、未运行 CryENGINE 测试，也未把未列出的文件或商业服务作为证据。
- 因而 Tasks、Threads/Messages、Crash Upload、Online Update、Security/Anti-cheat，以及多个模块的细节均保留 `资料不足`；后续阶段如需升级状态，必须补充可定位的公开文档、源码或运行收据。

覆盖统计：17/17 模块；统一顺序 17/17；含 Break 对照 17/17；明确 `资料不足` 的模块/子范围按证据缺口保留，未核验外部运行时与产品级服务。

## 附录 A：源码补充勘察（2026-10-22）

### A.0 证据范围变更

- 本次补充直接勘察了 CryENGINE v3.1.2 / Build 1742 的实际源码树：`/home/timeshift/opensource/game_engine/CryENGINE_FullCode_PC_v3_1_2_1742/Code`。用户原指定的 `Code/doc` 目录不存在；实际存在 `Code/docs/design/`（中文设计文档，含 `interfaces/IThreadTask.h.md` 等接口抽取），该目录不像原始交付物，仅作辅助线索，结论仍以源码文件为准。
- `Code/CryEngine/` 下确认的完整模块列表：Cry3DEngine、CryAction、CryAISystem、CryAnimation、CryCommon、CryEntitySystem、CryFont、CryInput、CryMovie、CryNetwork、CryPhysics、CryScriptSystem、CrySoundSystem、CrySystem、RenderDLL；顶层另有 `Game/`、`GameSkeleton/`、`Sandbox/`、`SDKs/`、`Tools/`、`Solutions/`。
- 本附录将正文中标记为 `资料不足` 的若干维度升级为“源码证据”，正文章节保留原样；以本附录为准的条目在各节标题后标注“（升级正文第 N 节）”。
- 证据等级仍为“源码存在 + 接口可读”，不等于本工作区编译或运行过 CryENGINE。

### A.4 Tasks（升级正文第 4 节）

- 存在独立任务抽象：`CryEngine/CryCommon/IThreadTask.h` 定义 `IThreadTask`/`IThreadTaskContext`；实现位于 `CryEngine/CrySystem/ThreadTask.h/.cpp`。
- 异步 IO 建立在任务系统之上：`IStreamEngine`（`CryCommon/IStreamEngine.h`）的读请求队列基于 IThreadTask，实现为 `CrySystem/StreamEngine.cpp`、`RefStreamEngine.cpp`、`RefReadStream*.cpp`。
- 子系统自有任务示例：`CryAnimation/AnimationThreadTask.h`。
- 结论：CryENGINE 有任务/异步作业机制（线程任务 + 流式 IO 队列），正文“资料不足”由本源码证据取代；但无 UE TaskGraph 式统一任务图证据。

### A.5 Threads / Messages（升级正文第 5 节）

- 跨平台线程原语集中在 `CryCommon/CryThread*.h`：`CryThreadImpl_windows.h`、`CryThreadImpl_pthreads.h`、`CryThreadImpl_ps3.h` 等平台实现，另有 `MultiThread.h`、`MultiThread_Containers.h`（无锁/多线程容器）、`ThreadProfilerSupport.h`。
- 模块间通信不走统一消息总线：主线是 DLL 模块 + 纯虚接口（`CryCommon/I*.h`）+ 全局环境 `SSystemGlobalEnvironment/gEnv`（`ISystem.h`），模块经接口指针互访；跨线程靠 CryThread 原语与各子系统自带队列（如 StreamEngine、动画任务）。
- 线程诊断：`CrySystem/ThreadProfiler.cpp`、`ThreadSampler.cpp`（Xbox 对应 `XenonThreadSampler.cpp`）。

### A.6 Networking（补充正文第 6 节细节）

- `CryNetwork/Context/`：状态复制的 Context/Aspect 体系——`ContextEstablisher.cpp`、`CET_Server.cpp`（Context Establishment Task 任务链）、`ClientContextView.cpp`、`Authentication.cpp`、`BreakagePlayback.cpp`、`ChangeList.h`。
- 压缩与加密：`CryNetwork/Compression/`（含算术编码压缩）、`CryNetwork/Cryptography/`（`rijndael.cpp` AES、`StreamCipher.cpp`、`Protocol/ExponentialKeyExchange.cpp` 密钥交换；大数库 `SDKs/BigDigits`）。
- 大厅层：`CryNetwork/Lobby/` 抽象 LAN / Xbox Live / PSN 三后端；分布式日志 `DistributedLogger.cpp`；错误码集中 `Errors.h`。
- 网络调试：`DebugKit/`（NetworkInspector、NetVis、ServerProfiler、DebugOutput）。

### A.11 Assets / Hot Reload（升级正文第 11 节热重载部分）

- 包文件与 VFS：`CrySystem/CryPak.cpp/.h`、`ZipDir*.cpp/.h`（ZipDirCache/ZipDirTree/ZipDirFind，含 RW 变体）、`PakVars.h`、`ZipFileFormat.h`。
- 异步资源 IO：`StreamEngine`/`RefReadStream*`（见 A.4）。
- 资产热更链路：CryAction 侧 `HotUpdate`（HotUpdate.h）、`LivePreview`、`LiveCreate` SDK；资源编译器 `Bin32/rc/`（正文已记）。
- 结论：CryENGINE 的 pak 式 VFS、异步 IO 和开发期资产热更新均有源码证据。

### A.12 Editor（补充正文第 12 节）

- Sandbox 编辑器源码随引擎同树发布：`Code/Sandbox/`（MFC 技术栈），引擎侧经 `IEditorGame` 接口对接；编辑器加密狗锁接口 `CryCommon/UniKeySecurity/IUniKeyManager.h`。
- `Code/Tools/` 与 `Bin32/rc/` 为配套工具链。

### A.13 Diagnostics / Remote Debugging（升级正文第 13 节远程部分）

- 性能剖析：`CrySystem/FrameProfileSystem.cpp`、`PerfHUD.cpp`（`CryCommon/IPerfHud.h`）、`BudgetingSystem.cpp`、`ThreadProfiler.cpp/ThreadSampler.cpp`、`DiskProfiler.cpp/LoadingProfiler.cpp`、`CrySystem/Statistics/`。
- 内存诊断：`CrySizerImpl.cpp/CrySizerStats.cpp`（分模块内存统计）、`MemoryFragmentationProfiler.h`、`MemReplay.cpp`、`CryMTrace.cpp`。
- 远程调试/控制：接口 `CryCommon/IRemoteControl.h`，实现 `CryNetwork/RemoteControl/RemoteControl.cpp`；内置 HTTP 服务 `CryNetwork/Http/SimpleHttpServer.cpp`（`ISimpleHttpServer.h`）；CryAction 侧另有 `RemoteControl/`、`SimpleHttpServer/`；Lua 调试器 `CryScriptSystem/LuaDebugger/`；数据探针 `CrySystem/DataProbe.cpp`（`IDataProbe.h`）。
- 测试框架：`CryCommon/ITestSystem.h`、`CrySystem/UnitTestSystem.cpp/TestSystemLegacy.cpp/VisRegTest.cpp`。
- 结论：远程诊断通道（RemoteControl + 内置 HTTP）有源码证据，正文“远程调试资料不足”由本证据取代。

### A.14 Crash Upload（升级正文第 14 节）

- 调用栈捕获与 minidump：`CrySystem/DebugCallStack.cpp/IDebugCallStack.cpp`（配合 `CryCommon/CryAssert.h` 断言体系）；Xbox 对应 `XenonDebugCallStack.cpp`。
- 上报集成：`CrySystem/WindowsErrorReporting.cpp`（WER/FaultRep.dll）；自动缺陷上报客户端 `CrySystem/JiraClient.cpp`（崩溃信息直接提单）；CRT 调试统计 `CryCommon/CrtDebugStats.h`。
- 结论：CryENGINE 有本地崩溃捕获与上报客户端证据；但无独立崩溃服务端/符号化服务证据，该子项仍标 `资料不足`。

### A.15 Online Update（升级正文第 15 节）

- HTTP 下载：`CrySystem/DownloadManager.h/.cpp` + `HTTPDownloader.cpp`（补丁/资源下载）；CryAction 网络侧 `CryAction/Network/DownloadTask.cpp`。
- 运行时热更新见 A.11（HotUpdate/LivePreview/LiveCreate）。
- 未发现独立的版本化 patcher/launcher：`Game/Launcher/Main.cpp`、`DedicatedLauncher/Main.cpp` 仅为启动器壳。
- 结论：有下载器与热更新机制证据；“manifest/签名/回滚的完整在线更新闭环”仍 `资料不足`。

### A.16 Security / Anti-cheat（升级正文第 16 节）

- 反作弊：`CryNetwork/AntiCheat/DefenceContext.cpp/DefenceData.cpp`（服务端校验上下文），配合会话认证 `Context/Authentication.cpp`（ContextEstablisher 认证链）。
- 加密与完整性：AES（`Cryptography/rijndael.cpp`）、Whirlpool 哈希、`StreamCipher.cpp` 流加密、`Protocol/ExponentialKeyExchange.cpp` 密钥交换。
- 正版/防盗版：`CryCommon/CopyProtection.h`（SecuROM 痕迹）；编辑器狗锁 `IUniKeyManager.h`。
- 结论：CryENGINE 有认证、加密和服务端反作弊上下文证据，正文“资料不足”由本源码证据取代；现代在线反作弊产品级闭环（内核驱动、遥测封禁等）不在本版本范围。

### A.17 Large-world / Streaming（补充正文第 17 节）

- 本版本无整关卡流送：`ILevelSystem.h` 无 streaming API，关卡整体加载/卸载；大世界靠地形扇区 + 资源级流送支撑。
- 纹理流送：`RenderDLL/XRenderD3D9/D3DTexturesStreaming.cpp`；静态物体/几何流送：`Cry3DEngine/ObjManStreaming.cpp/StatObjStream.cpp`，入口 `I3DEngine::LoadStatObj(..., bUseStreaming=true)`（I3DEngine.h:1276），状态 `SObjectsStreamingStatus`。
- 地形扇区：`terrain_sector*.cpp`（扇区网格 + 按扇区纹理/几何）、`terrain_hmap.cpp`、远景 impostor `CREImposter.h/D3DREImposter.cpp`。
- 预缓存：`I3DEngine::PrecacheLevel`（I3DEngine.h:2127）、`CryAction/LevelSystem.cpp` 的 `IResourceManager::PrepareLevel`。
- 空间索引：实体 `CryEntitySystem/PartitionGrid.cpp/AreaGrid.cpp`、AI `WorldOctree.cpp`、渲染 `IsoOctree/`。

### A.18 补充后的覆盖统计

- 升级/补充的维度：4（Tasks）、5（Threads/Messages）、6（Networking 细节）、11（Assets/HotReload）、12（Editor）、13（Diagnostics/Remote）、14（Crash Upload）、15（Online Update）、16（Security/Anti-cheat）、17（Streaming 细节）。
- 仍保留 `资料不足` 的子项：整关卡流送、崩溃服务端/符号化、版本化 patcher 闭环、现代产品级反作弊闭环。
- 本附录未编译、未运行 CryENGINE；`Code/docs/design/` 中文文档仅作线索，不作为独立证据。
