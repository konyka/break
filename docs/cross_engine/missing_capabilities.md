# Cross-Engine Stage 1：Break 缺失能力清单

## 简介

本文是阶段 1 的 `missing_capabilities` 文档。目标不是宣布任何引擎“完整”或替代产品需求，而是以可追溯证据整理 Break 与 CryENGINE、BW191、Unreal Engine 5.8.3 的能力边界，并指出后续阶段需要补齐的缺口。

比较固定覆盖以下 17 个模块，并且各节保持相同顺序：**模块系统、ECS/实体、世界/场景、任务、线程/消息、网络、UI/输入、渲染/RHI、物理、音频、资产/热重载、编辑器、诊断/远程调试、崩溃上传、在线更新、安全/反作弊、大世界/流式**。

## 证据口径

- Break 的状态只引用当前仓库中的 [`docs/Implementation_Status.md`](../Implementation_Status.md)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md) 和明确的源码/测试路径；“已实现”不等于“有接口声明”。
- `正式 runtime` 指被正式 `engine`/demo 或正式运行时目标链接并有相应运行证据；`focused/test-only` 指测试目标直接编入的切片或只在测试配置生成的目标，不能升级为产品运行时能力。
- `已具基础` 表示可复用的底层机制存在，但不表示对应产品系统已经交付；`产品级未实现` 表示尚无足够证据证明有完整的生命周期、工具链、部署、升级或运营闭环。
- 外部资料以仓库中的 [`cryengine_inventory.md`](cryengine_inventory.md)、[`bw191_inventory.md`](bw191_inventory.md)、[`unreal_inventory.md`](unreal_inventory.md) 及其引用的架构资料为限。未被这些资料直接证明的外部能力统一标记为 **资料不足**，不作推测。
- 影响与建议描述“为什么需要后续立项”，不是本阶段的交付承诺。模块内同时出现多个状态时，以更严格的集成边界为准。

## 统一状态分组

| 分组 | 含义 |
|---|---|
| 已具基础 | Break 有明确源码、公共接口或架构基础，可作为后续实现起点。 |
| focused/test-only | 有 focused API、测试或测试专用目标，但未进入正式 runtime/demo 链路。 |
| 正式 runtime | 已进入正式运行时目标，并有文档或测试证据支持；仍可能有平台/功能边界。 |
| 产品级未实现 | 缺少完整产品生命周期、工具、服务端、运营或安全闭环；不能按局部 API 推断已交付。 |
| 资料不足 | 现有外部资料不足以确认能力，保持未知。 |

## 17 个模块

### 1. 模块系统

- **Break 现状：已具基础 / 正式 runtime。** `docs/Architecture_Overview.md` 描述 `engine/`、`framework/`、`empty/` 的分层；`framework/interface/` 与 `framework/common/` 提供 `RuntimeModuleInterface`、`BaseApplication` 的 Init/Tick/DeInit 生命周期。架构还明确目录隔离、头文件接口和 CMake 单后端链接边界。
- **外部证据：** CryENGINE 的模块化 DLL 由 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L24) 直接记载；BW191 的客户端/服务端独立进程由 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L52) 记载；Unreal 的 `FModuleManager`/插件加载见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L34) 和第 24、25 章。具体版本级模块热替换、卸载保证和部署策略：**资料不足**。
- **缺口、影响与后续：** Break 没有被证据覆盖的统一插件目录、模块依赖解析、运行时热卸载/热替换和产品发行打包闭环。后续阶段建议先定义模块 manifest、依赖拓扑、加载相位和失败回滚，再连接 framework 与 editor/tooling。

### 2. ECS / 实体

- **Break 现状：已具基础；focused/test-only。** `engine/src/ecs/` 有 ECS；`world_snapshot.*`、`world_delta.*`、`replication_schema.*` 的 snapshot、delta、schema 和 generation 证据见 [`docs/Implementation_Status.md`](../Implementation_Status.md#L32) 与 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L482)。这些 snapshot/schema/delta/AoI/replication focused sources 当前直接编入测试 target，不在正式 `engine` static library。
- **外部证据：** CryENGINE 的 `CryEntitySystem` 组件实体见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L139)；BW191 的 entity manager/type 和 BaseApp 实体见 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L39)；Unreal 的 UObject/Actor/组件见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L19)。跨引擎 ECS 数据布局、反射和迁移细节：**资料不足**。
- **缺口、影响与后续：** Break 缺正式 runtime 的实体世界接入、schema negotiation、持久化/编辑器反射和 logic-facing API。后续阶段建议把 focused sources 纳入受控 runtime target，补实体生命周期、组件注册 ABI、序列化版本和真实 session/replication 链路。

### 3. 世界 / 场景

- **Break 现状：已具基础。** [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L133-L136) 将 ECS、Asset、Renderer 列为核心模块；RHI、相机、剔除、地形、水体和后处理在 renderer 目录中有架构定位。当前 snapshot/AoI 只证明确定性数据和可见性范围切片，不证明完整可编辑 world/scene runtime。
- **外部证据：** CryENGINE 的 3D 场景、sector、地形、遮挡裁剪在 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L47)；BW191 的 chunk/cell 空间模型在 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L110)；Unreal 的 `UWorld`、Actor 和 World Partition 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L20-L21)。三者的完整场景编辑、保存和跨版本迁移闭环：**资料不足**。
- **缺口、影响与后续：** Break 缺少被证实的场景资产编排、层级/关卡实例、世界保存与编辑器 round-trip。后续阶段建议先确定 world ownership、场景序列化格式、加载事务和运行时场景变更边界，再接流式系统。

### 4. 任务

- **Break 现状：已具基础 / 正式 runtime。** `engine/src/task/task.h` 定义 `TaskSystem`；架构文档说明 worker、外部提交和 `task_wait` 的线程约束（[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L438-L440)）。
- **外部证据：** Unreal 的 TaskGraph/UE Tasks 在 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L19) 和第 26 章有索引；CryENGINE、BW191 在当前参考资料中没有可核验的任务调度 API/调度策略：**资料不足**。
- **缺口、影响与后续：** Break 尚无证据覆盖优先级、取消、跨帧 continuation、任务图可视化和产品级工作窃取调优。后续建议补 task ownership/cancellation、fence/continuation 契约，以及诊断导出；不得把现有线程池基础误报为完整作业系统。

### 5. 线程 / 消息

- **Break 现状：已具基础；网络消息为 focused/test-only。** Task worker 与主线程边界见 `engine/src/task/task.h`；Session/adapter 的消息 view/copy、队列和 close watermark 见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L442-L480)。网络线程不直接访问 LogicThread、ECS、Lua、UI 或 RHI。
- **外部证据：** Unreal 的线程、队列、消息、委托专题见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L42-L47)；CryENGINE/BW191 的通用消息总线、跨进程事件和线程模型：**资料不足**。
- **缺口、影响与后续：** Break 缺统一 engine-wide event bus、跨线程取消/背压策略和可观测的消息拓扑。后续建议制定消息所有权、序列化、队列容量、优先级与关停协议，并把 network/session 的局部队列接入统一诊断，而不是直接扩大共享状态。

### 6. 网络

- **Break 现状：focused/test-only。** `engine/src/network/break_net_{adapter,message,protocol}.{h,c}` 与 `break_net` 仅在 `ENGINE_BUILD_TESTS=ON && BREAK_ENABLE_SNOWFLAKE=ON` 时生成；真实 loopback 覆盖 inbound/outbound/close，Session 有 18-byte envelope，但 `engine_demo`/`dxx_break` 不链接它。证据见 [`docs/Implementation_Status.md`](../Implementation_Status.md#L50-L55)。
- **外部证据：** CryENGINE 有 CryNetwork、RMI、同步、预测/回滚的仓库参考描述，见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L147-L153)；BW191 有 LoginApp/BaseApp/CellApp、服务端连接和过滤器，见 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L52-L107)；Unreal NetDriver/Iris/复制见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L27)。具体可靠性、部署规模和运营工具：**资料不足**。
- **缺口、影响与后续：** Break 缺正式 socket/session 接线、认证后端、重连、预测/回滚、schema negotiation、超时/eviction scheduler、加密认证和服务端集群。后续建议先把 adapter 从 test-only 提升为显式 runtime 组件，再按认证、可靠传输、复制和服务端部署分阶段验收。

### 7. UI / 输入

- **Break 现状：正式 runtime（边界明确）。** `engine/src/ui/`、`engine/src/platform/` 提供 debug UI、字体、窗口、键鼠/手柄输入；2.0.0 起 Linux 仅使用 Wayland，另有 Win32、Cocoa 和输入能力（[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L125-L142)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L428-L436)）。
- **外部证据：** CryInput/CryFont 见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L163-L172)；BW191 的 GUI、输入和客户端脚本见 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L35-L50)；Unreal Slate/UMG/Input/IME 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L26)。完整 UI 编辑器、无障碍和输入重映射产品能力：**资料不足**。
- **缺口、影响与后续：** Break 的证据集中在 debug/UI 与平台输入，不足以证明完整 retained-mode UI、复杂文本、焦点/无障碍、输入配置资产和 UI 编辑器。后续建议先抽离正式 UI runtime 与 debug UI 的边界，再补布局/文本/焦点/输入映射的可部署契约。

### 8. 渲染 / RHI

- **Break 现状：正式 runtime。** `engine/src/rhi/` 的 compile-time single backend 模型、Vulkan/Metal/D3D12/OpenGL/headless 边界和 capability contract 见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L125-L135)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L243-L295)。D3D12 仍有 MRT MSAA、cubemap FBO 等明确限制；Implementation Status 记录了 focused/WARP 和 GPU/runtime 证据及未实现项（[`docs/Implementation_Status.md`](../Implementation_Status.md#L57-L64)、[`docs/Implementation_Status.md`](../Implementation_Status.md#L107-L123)）。
- **外部证据：** CryENGINE RenderDLL/D3D9/NULL 与后处理见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L69-L87)；BW191 客户端渲染能力只有概览级说明；Unreal RHI、RenderCore/RDG、Renderer 和 shader/DDC 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L22-L25)。BW191 的后端细节与跨平台性能等级：**资料不足**。
- **缺口、影响与后续：** Break 缺产品级渲染资产/shader 编译与缓存、完整 render graph、跨后端 feature parity、GPU crash recovery 和全平台 benchmark gate。后续建议优先收口后端能力矩阵、render-pass/资源生命周期和 shader pipeline cache，再扩展高级 renderer；不可将 headless 或 focused 像素测试等同于全部产品渲染能力。

### 9. 物理

- **Break 现状：已具基础；产品级未实现。** `engine/src/physics/` 在架构核心模块表中存在并声明刚体/角色控制方向（[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L136-L139)），但当前状态文档没有足以证明完整 solver、车辆、布料、破坏和正式 logic 集成的统一 runtime 收据。
- **外部证据：** CryPhysics 明确列出刚体、碰撞、角色、载具、布料、破坏，见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L129-L137)；Unreal Chaos 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L28)；BW191 的物理源码绑定有概览记录，完整 solver 能力：**资料不足**。
- **缺口、影响与后续：** Break 缺被验证的确定性/并行 solver、碰撞过滤、角色/车辆、布料破坏、回放和网络同步。后续建议先定义 physics world ownership、固定步长、查询/事件 API 和 snapshot 边界，再按功能增加 solver 与工具。

### 10. 音频

- **Break 现状：已具基础；产品级未实现。** `engine/src/audio/` 与 miniaudio 依赖在 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L139-L140)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L221-L233) 可见；当前证据未证明完整 mixer、空间音频、资源热加载、音频线程和发行级设备恢复。
- **外部证据：** CrySoundSystem 有音频播放/3D 音效概览，见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L163-L172)；BW191 有 FantasyDemo 音频资源和 FMOD runtime 目录，见 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L22-L30)、[`docs/BW191_Architecture.md`](../BW191_Architecture.md#L159-L162)；Unreal AudioDevice/Mixer/MetaSound 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L30)。具体能力等级和混音拓扑：**资料不足**。
- **缺口、影响与后续：** Break 缺音频资产管线、bus/mixer、3D attenuation、设备热插拔、录制/混音诊断和网络语音。后续建议先固化 audio thread/command ownership 与设备错误恢复，再接资源、空间化和工具。

### 11. 资产 / 热重载

- **Break 现状：已具基础。** `engine/src/asset/` 的 asset、hotreload、vfs 在 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L133-L135) 列出；平台 filewatch 与 shader/资源热重载方向见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L428-L436)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L204-L217)。
- **外部证据：** CryENGINE 有 CGF/MeshCompiler 和资源编译器目录，见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L47-L67)；BW191 有 res、doc_watcher、内容工具，见 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L110-L123)、[`docs/BW191_Architecture.md`](../BW191_Architecture.md#L175-L190)；Unreal AssetRegistry/Cook/Pak/IoStore/DDC 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L36-L37)。
- **缺口、影响与后续：** Break 缺完整导入器、依赖图、派生数据缓存、cook/package、版本化资产格式和编辑器 round-trip。后续建议从 VFS/asset identity/异步 IO 契约开始，随后建设 importer、缓存、打包和热重载失效策略；当前不能把 filewatch 视为完整资产管线。

### 12. 编辑器

- **Break 现状：产品级未实现。** `framework/` 与 demo/工具提供应用骨架，但 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L542-L548) 仍将编辑器/设计工具列为待创建文档，当前状态没有正式 level/content editor runtime 证据。
- **外部证据：** CryENGINE Sandbox/工具集在参考资料中仅以目录和架构定位出现；BW191 有 content tools reference、运行工具和 FantasyDemo；Unreal UnrealEd/LevelEditor/ContentBrowser/事务见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L38)。具体编辑器能力、可扩展 API 和版本：CryENGINE/BW191 **资料不足**（仅有仓库概览）。
- **缺口、影响与后续：** Break 缺场景编辑、属性检查、资源浏览、撤销/事务、PIE/预览、工具插件和内容验证。后续建议以资产/场景 round-trip 为第一阶段验收，不应先做孤立 UI 外壳。
- **2026-10-30 补充：** 场景编辑器已作为可选目标交付（`break_editor` + `editor`）：文档模型与撤销/重做、BSCN 场景存取、组件注册表、outliner/inspector、3D viewport + gizmo + 相机聚焦、asset browser 与热加载、profiler/network/render 诊断面板、Lua console（带指令与 64 MiB 内存预算）、命令面板、I18N 与 CLion 风格主题，见 [`docs/design/editor_phase1.md`](../design/editor_phase1.md) 及 `docs/design/editor_*.md`。仍缺：PIE、多选、插件系统、场景保真渲染。

### 13. 诊断 / 远程调试

- **Break 现状：已具基础 / 正式 runtime（局部）。** Core 包含 log、profiler、assert；架构文档记载 profiler provenance/chrome trace sidecar（[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L270-L272)），Implementation Status 还记录 sanitizer、CTest 和各后端证据边界。远程调试协议与统一 Insights 类工具未见正式 runtime 证据。
- **外部证据：** CrySystem 有 CVar、调试/性能分析概览，见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L215-L223)；BW191 有 watcher、message_logger、运维工具，见 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L70-L79)；Unreal Trace/Insights/Stats/Automation 与远程控制见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L39-L47)。跨引擎远程协议的部署细节：**资料不足**。
- **缺口、影响与后续：** Break 缺统一 trace schema、远程 console/inspector、线上采集权限和跨线程/网络关联 ID。后续建议先统一事件、时间戳、线程和 provenance schema，再提供本地导出与受控远程通道。
- **2026-10-30 补充（阶段 1 之后的交付）：** 编辑器 remote session（TLS + PSK 认证、服务端关闭与认证 deadline、network 面板含会话计数与 `rate_limited`）、render debugger 面板、profiler 面板已交付，见 [`docs/design/editor_remote.md`](../design/editor_remote.md)、[`docs/design/editor_render_debugger.md`](../design/editor_render_debugger.md)。仍缺：统一 trace schema、跨线程/网络关联 ID、生产部署的远程通道。

### 14. 崩溃上传

- **Break 现状：产品级未实现。** 当前证据覆盖 assert/log/profiler、ASan/UBSan/TSan 与测试日志，但没有崩溃捕获、minidump、符号服务器、脱敏或上传服务的正式 runtime 证据。
- **外部证据：** Unreal 诊断章节包含崩溃相关方向，见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L39-L40)；CryENGINE/BW191 的崩溃收集、上传、保留和隐私策略：**资料不足**。
- **缺口、影响与后续：** 缺口会使现场崩溃难以归因，也无法形成版本/平台/符号关联。后续建议先实现本地 crash envelope、线程/构建/GPU provenance 和符号化，再独立设计上传、重试、脱敏、限流与删除政策；不应把测试 sanitizer 报告称为崩溃上传能力。
- **2026-10-30 补充：** 客户端半侧已交付（`break_crash`：async-signal-safe 捕获、`break-crash-v1` 记录、有界 spool、脱敏、调用方提供的上传回调与重试策略），见 [`docs/design/crash_reporting.md`](../design/crash_reporting.md)。仍缺：真实上传传输、服务端符号化、聚类与回归统计。

### 15. 在线更新

- **Break 现状：产品级未实现。** `docs/Implementation_Status.md` 明确将 online update 列为未实现边界（例如网络/session 与 ECS 集成限制，见 [`docs/Implementation_Status.md`](../Implementation_Status.md#L30-L38)、[`docs/Implementation_Status.md`](../Implementation_Status.md#L46-L48)）；未发现正式 patch/manifest/回滚服务链路。
- **外部证据：** Unreal 的 BuildGraph/UAT、Cook/Package/IoStore 可作为构建和分发相关参考，见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L35-L37)，但不自动证明在线更新；CryENGINE/BW191 的在线更新协议、签名和回滚：**资料不足**。
- **缺口、影响与后续：** 缺 manifest、差分包、签名验证、原子切换、失败回滚、版本兼容和 CDN/服务端运维。后续建议先定义内容版本与兼容矩阵，再实现离线可重复 apply/rollback，最后接在线服务；不得由 asset hot reload 推断为在线更新。
- **2026-10-30 补充：** 客户端离线机制已交付（`break_update`：签名 manifest、内容寻址分块、断点续传、A/B 槽、原子激活、确认启动与回滚、渠道策略、灰度分桶客户端半侧），见 [`docs/design/update_client.md`](../design/update_client.md)。仍缺：真实 HTTP/TLS 传输、更新服务端、离线签名工具与密钥生命周期。

### 16. 安全 / 反作弊

- **Break 现状：产品级未实现。** Session 有 envelope 校验、长度/版本/序列检查；fragment checksum 是完整性校验而非加密认证，Implementation Status 明确将 cryptographic authentication、security integration 列为未实现边界（[`docs/Implementation_Status.md`](../Implementation_Status.md#L36-L38)、[`docs/Implementation_Status.md`](../Implementation_Status.md#L46-L48)）。
- **外部证据：** 现有 CryENGINE、BW191、UE5.8.3 参考资料未提供足以核验的完整反作弊、密钥生命周期、服务器权威安全模型或发行安全方案：**资料不足**。
- **缺口、影响与后续：** Break 缺认证/授权、密钥轮换、传输和存储保护、反篡改、服务器权威校验、审计与隐私边界。后续建议先做 threat model 与 trust boundary，再定义加密认证、重放防护、权限和审计；不能把 magic/length/checksum 校验升级为安全能力。
- **2026-10-30 补充：** 已交付：威胁模型（[`docs/design/security_threat_model.md`](../design/security_threat_model.md)）、`break_crypto`（OpenSSL EVP 封装，零自造密码学）、TLS 传输与 mTLS、CHALLENGE/AUTH-v2 HMAC 会话认证、握手级重放论证、admission 限速、每连接消息/字节限速（`break_session_manager_set_message_rate`，默认关闭）、应用消息防重放窗口库（`break_replay_window`，流式传输上已决定不接入：重连重放已被握手 nonce 阻断，连接内由严格递增序号阻断；留给将来的数据报 / 逐消息 AEAD 通道，采用 epoch+64 位计数方案，见 [`docs/design/transport_security.md`](../design/transport_security.md) §3 的 2026-10-30 决策）。仍缺：服务器权威实现、客户端反篡改（仅成本模型文档）、凭证 provisioning/轮换/吊销。

### 17. 大世界 / 流式

- **Break 现状：focused/test-only；产品级未实现。** `break_aoi.*` 有空间网格、Witness、owner/dormant/relevancy、hysteresis 和确定性 enter/stay/leave；`break_replication.*` 有 Real/Ghost 与带宽预算，但 focused sources 不在正式 `engine` static library，且 distributed Cell service、timeout/eviction、正式 session integration 未实现。证据见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L482-L506)。
- **外部证据：** BW191 的 CellApp 分区、chunk portal 和分布式空间是直接可见的参考，见 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L52-L107)、[`docs/BW191_Architecture.md`](../BW191_Architecture.md#L110-L123)； CryENGINE sector/场景管理见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L47-L67)；Unreal World Partition/LevelStreaming/DataLayer 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L20-L21)。具体容量、迁移和线上 SLA：**资料不足**。
- **缺口、影响与后续：** Break 缺世界分区服务、持久化、跨分区 authority handoff、流式 IO/优先级、客户端预测/回滚和大世界工具链。后续建议先把 AoI 与正式网络/session 接上，再定义 cell ownership、迁移事务、持久化和可观测性；当前 AoI 不能称为完整大世界系统。

## 与 Break 的比较边界

1. **比较的是能力边界，不是代码量。** CryENGINE/BW191 的架构文档是仓库内参考资料，Unreal 资料是 UE5.8.3 源码抽取导航；它们不能证明所有发行版、平台或线上服务能力。
2. **局部 API 不等于产品能力。** Break 的 ECS/replication/AoI/fragment 与 Snowflake adapter 有明确 focused 证据，但 source/target 边界仍决定其不是正式 runtime；同理 RHI contract test 不等于所有后端 feature parity。
3. **文档、编译、focused、runtime 分开。** `docs/Architecture_Overview.md` 的架构定位、源码存在、编译成功、headless/focused 测试、native-surface/GPU runtime 和 benchmark-comparable 是不同证据等级，不能互换。
4. **外部未知不补齐。** 对 CryENGINE、BW191、Unreal 未在现有参考资料中直接确认的模块、版本、平台、服务或安全性质，保持“资料不足”；本文件不根据产品声誉或名称推断实现。
5. **范围限制。** 本阶段只创建缺口文档；不改变源码、CMake、测试或其他文档，也不把后续建议写成当前交付。

## 来源与限制

- Break 状态主来源：[`docs/Implementation_Status.md`](../Implementation_Status.md)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md)。实现级追踪优先使用这两份文档中列出的源码路径、target 条件和测试结果。
- CryENGINE 参考：[`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md)。该文件描述 CryENGINE v3.1.2 的仓库结构与模块概览，不是本阶段重新核验的完整源码审计。
- BW191 参考：[`docs/BW191_Architecture.md`](../BW191_Architecture.md)。该文件描述客户端、服务端 Cell/BaseApp、工具与脚本概览，不足以证明每个产品模块的运行时细节。
- Unreal 参考入口：[`docs/ue5.8.3/README.md`](../ue5.8.3/README.md)，并链接到本目录的 `design/01~32`、`appendix/` 和 `PROGRESS.md`。README 明确列出抽取器覆盖范围和第三方/平台闭源限制。
- Inventory 限制：本次读取时仓库没有三份阶段 inventory 文件；因此不能宣称已完成对三份 inventory 的逐项交叉复核。后续若 inventory 补入，应按本文 17 节顺序复核状态、来源链接和“资料不足”标记。
- 覆盖统计：17/17 模块已逐节覆盖；每节均包含 Break 状态、外部证据边界、影响和后续建议。正式 runtime、focused/test-only、产品级未实现和资料不足均有明确使用场景；外部引擎未核验的细节不作推测。

## 补充证据修订（2026-10-22）

### 修订背景

本次补充勘察取得 CryENGINE v3.1.2 实际源码树与 BW191 设计文档树（详见 [`cryengine_inventory.md` 附录 A](cryengine_inventory.md)、[`bw191_inventory.md` 附录 A](bw191_inventory.md)、[`feature_matrix.md` 补充证据修订](feature_matrix.md)）。三份阶段 inventory 现已全部存在并含源码/文档级补充证据，正文“来源与限制”中“本次读取时仓库没有三份阶段 inventory 文件”的限制已解除。

### 外部证据状态变化（Break 缺口不变）

以下只更新外部证据侧的描述，**Break 的缺口、影响与后续建议全部维持正文原状**：

- **第 4 节（任务）**：CryENGINE 的 `IThreadTask`/`StreamEngine` 任务机制与 BW191 的 MainLoopTask/BgTaskManager 现有源码/文档证据，不再是 `资料不足`。
- **第 5 节（线程/消息）**：CryENGINE 的 CryThread 平台原语族与“无统一消息总线、gEnv 接口互访”结构、BW191 的“客户端无独立渲染线程 + 单 Mercury 主线程 + cstdmf 同步原语”模型现有证据。
- **第 13 节（诊断/远程调试）**：CryENGINE 的 IRemoteControl/内置 HTTP/DebugKit/LuaDebugger 与 BW191 的 Watcher/Python 远程端口/web_console 三层体系现有证据。
- **第 14 节（崩溃上传）**：CryENGINE 客户端侧（DebugCallStack/WER/JiraClient）与 UE 的 CrashContext/CrashReportClient 现有证据；BW191 仍仅弱证据（Reviver/geh/stack_walker）。所有外部引擎的服务端符号化/聚合闭环仍 `资料不足`。
- **第 15 节（在线更新）**：CryENGINE 的 DownloadManager/HTTPDownloader 与 UE 的 ChunkDownloader/MobilePatchingUtils/BuildPatchServices 现有证据；BW191 仅 digest 校验/受控关闭弱证据。各引擎的签名/回滚/灰度完整闭环证据仍不完整。
- **第 16 节（安全/反作弊）**：CryENGINE 的 AntiCheat/DefenceContext + AES + 密钥交换 + 认证链、BW191 的 RSA/Blowfish/防重放/限速登录链、UE 的 Online 子系统 EOS AntiCheat 插件条目现有证据；产品级反作弊部署闭环仍 `资料不足`。

### 对 Break 缺口的补充说明

外部证据升级不改变 Break 侧任何状态，但使两处对比更具体：

1. **线程/消息缺口**：BW191 证明“单线程渲染 + 明确锁纪律”可以支撑大型 MMO 客户端，UE 证明 GT/RT/RHI 分离是高吞吐路线；Break 的 Stage 2 线程模型设计（`docs/design/runtime_thread_model.md`）在两者之间选择了显式线程域 + 消息/命令队列，该选择现有两个反例边界可参考：不要退回 BW191 式主线程全包，也不必一步到位 UE 式全分离。
2. **安全缺口**：CryENGINE 与 BW191 的证据表明“认证 + 信道加密 + 服务端权威 + 限速/防重放”是引擎层可交付的最小闭环；Break 第 16 节的后续建议（threat model → 加密认证 → 重放防护 → 审计）与该最小闭环一致，可按 Stage 5 子项目拆分独立验收。

## 补充证据修订（2026-11-15）

### 修订背景

正文与 2026-10-30 补充里的若干「仍缺」项已在后续提交中交付。本节按当前 `master` 重新核对，只记录有源码和测试证据的状态变化，不改写上面的原文。核对用的构建树是 `build-core-app-master`：全量 CTest 401/401 通过，下面列出的定向测试也都在这棵树里通过。

### Break 状态变化

- **第 9 节（物理）**：`engine/src/physics/` 现有刚体、BVH、角色、载具、布料、绳索、软体、布娃娃和可破坏体。定向测试 `test_physics`、`test_physics_hinge`、`test_physics_slider`、`test_physics_cone_twist`、`test_physics_identity`、`test_character`、`test_vehicle`、`test_cloth`、`test_rope`、`test_soft_body`、`test_ragdoll`、`test_destructible` 通过。状态由「已具基础」升为「正式 runtime（局部）」。仍缺：并行 solver、网络同步和回放。
- **第 10 节（音频）**：`engine/src/audio/` 有 DSP、流式播放和扩展模块；`core_app_audio` 使用 256 项命令队列，并有真实设备通道 `test_core_app_audio_device`。`test_audio`、`test_audio_dsp`、`test_audio_extended`、`test_audio_realtime_contract` 通过。仍缺：网络语音和音频编辑工具。
- **第 12 节（编辑器）**：编辑器 remote 已支持 HISTORY、SAVE、SET_FIELD（含 bool 字段）、多设备 keyring 与吊销，以及 RENDER 消息，见 `docs/Implementation_Status.md` 的 2026-10-30 与 2026-11-14 条目。`test_editor*` 共 16 个测试。仍缺项同 2026-10-30 补充。
- **第 14 节（崩溃上传）**：2026-10-30 补充所列缺口已交付。`break_crash_symbolize` 读取 ELF 符号并恢复最多 32 帧；`break_crash_cluster` 负责签名、回归统计和去重；`break_crash_upload_http` 是 HTTP 上传实现；`break_crash_server` 是参考收集服务，要求 TLS。见 [`docs/design/crash_symbolization.md`](../design/crash_symbolization.md)。`test_break_crash*` 与 `test_break_crash_e2e` 通过。仍缺：生产部署的收集服务、minidump 格式、Windows/macOS 符号化。
- **第 14 节（崩溃上传）追加**：2026-11-17 符号库支持 Mach-O。`break_macho_symbols_open` 读单架构 64 位小端 Mach-O（x86_64、arm64）的 `LC_SYMTAB`，构建 id 取 `LC_UUID`；`break_crash_symbols_open` 按 magic 分派，符号库用它。见 [`docs/design/crash_symbolization.md`](../design/crash_symbolization.md) 第 2 节。仍缺：生产部署的收集服务、minidump、Windows 符号化、arm64 帧展开、fat 文件。
- **第 15 节（在线更新）**：真实传输与参考服务端已交付。`break_http` 是有界 HTTP/1.1 客户端，强制 TLS 1.2 以上、要求 CA 文件并校验主机名；另有参考服务端 `break_update_server`，`test_break_update_e2e` 覆盖灰度拒绝、断点续传、篡改块拒绝和 manifest 验签失败。见 [`docs/design/update_transport.md`](../design/update_transport.md)。仍缺：生产更新服务、HTTP/2、代理、证书吊销与钉扎；目前没有发布二进制链接 `break_http`。
- **第 16 节（安全/反作弊）**：服务端权威参考引擎 `break_authority` 和客户端完整性信号 `break_integrity` 已交付，见 [`docs/design/server_authority.md`](../design/server_authority.md)、[`docs/design/client_integrity.md`](../design/client_integrity.md)。`break_integrity` 只观察和上报，不作为授权输入；契约测试禁止它导出任何「放行/拒绝」类函数。`test_break_authority`、`test_break_integrity` 及其 target contract 通过。仍缺：服务端产品与持久化、凭证 provisioning 和轮换。
- **第 17 节（大世界/流式）**：`test_world_stream`、`test_world_stream_job`、`test_world_stream_world`、`test_mipmap_stream`、`test_ecs_replication`、`test_net_replication` 通过。`break_aoi.c` 现在属于 `break_replication_core`（`engine/CMakeLists.txt` 第 827 行）。`break_net` 和 `break_online` 链接这个库；`core_app` 在 `CORE_APP_ENABLE_NETWORK` 与 `BREAK_ENABLE_SNOWFLAKE` 都开启时链接 `break_net`。因此 AoI 已不再是 test-only，但仍不在 `engine` static library 中，离线构建也不链接它。状态由「focused/test-only」改为「可选 runtime 组件」。分布式 Cell 服务和跨分区 authority handoff 仍未实现。

### 未变化

第 1–8、11、13 节的 Break 缺口维持正文和 2026-10-30 补充的描述，本次核对没有发现足以改变状态的新证据。

## 补充交付记录（2026-11-15 第二批）

本节只记录 2026-11-15 新交付的项，不修改上文状态描述。证据见 `docs/Implementation_Status.md` 同日条目。

- **第 13 节（诊断/跨线程关联）**
  - Runtime Core 消息和 profiler 事件带 `correlation_id`，`break_runtime_correlation_next()` 发号（`a4614457`）。
  - `break_runtime_profiler_export_flows` 把关联事件导出成 Chrome trace slice 和 flow 事件（`26e15d63`）。
  - 网络 envelope 新增可选 8 字节关联扩展，标志位 `0x0010`；不带 ID 的帧与原格式逐字节相同（`e507ef37`）。
  - `BreakNetMessageView`、owned message、adapter 收发路径传递 ID，新增 `break_net_reactor_send_correlated`（`937b69e9`）。
  - 编辑器远程响应回带请求 ID（`32a01091`）。
- **第 12 节（编辑器）**
  - Ctrl+Shift+P/D/L 诊断快捷键（`478a0aee`）。
  - F5–F8 play mode：进入时记录 history mark，停止时回滚场景（`0d06c0bb`）。这不是独立进程的 PIE。

仍缺：session 层与 Runtime Core 消息之间的 ID 映射，以及统一 trace schema。CI 不构建 Snowflake 网络目标，所以网络相关测试只在本地 Snowflake 构建树 `build-net-master` 里跑过（405/405）。

## 补充交付记录（2026-11-15 第三批）

本节只记录新交付的项，不修改上文状态描述。

- **第 13 节（诊断/跨线程关联）**
  - session 层回复 CHALLENGE 时，AUTH 帧回带 CHALLENGE 的 `correlation_id`（`9a958b68`），测试 `break_session_challenge_auth_reply_echoes_correlation_id`。上文「session 层与 Runtime Core 消息之间的 ID 映射」中，session 握手这一段已覆盖；core_app 快照路径仍未映射，因为快照目前只进入 inbox 计数，没有可观察的消费者。
- **第 9 节（物理）**
  - 世界快照 `physics_snapshot_save/restore` 和状态哈希 `physics_state_hash`（`65884bb1`）。
  - 输入录制与回放文件格式 `physics_replay.{h,c}`，`physics_replay_run` 返回 OK、DIVERGED 或 INVALID，并给出第一处分歧的记录下标（`03564f30`），测试 `test_physics_replay`。
  - 仍缺：并行 solver、网络同步、跨平台确定性。回放只保证同一构建、同一平台上的结果一致。
- **第 15 节（在线更新）**
  - `break_http` 支持可选的 SPKI SHA-256 钉扎，最多 8 个 pin，在 TLS 握手成功后比较（`21fd9e02`）。见 [`docs/design/update_transport.md`](../design/update_transport.md)。
  - 仍缺：代理、证书吊销（CRL/OCSP）、HTTP/2；发布二进制仍没有链接 `break_http`。
- **第 9 节（物理）追加**：`physics_sync` 提供基于 `physics_state_hash` 的 desync 检测报文和快照修正包（`a33587ea` 及后续提交）。它解决的是「发现分歧并整体恢复」，还不是增量状态同步，也没有接入网络层。
- **第 12 节（编辑器）追加**：插件系统的第一步是命令注册表 `editor_plugin_cmds`，插件可以向命令面板贡献命令，卸载前按 owner 移除。命令面板接入和 `break_plugin` 加载流程的接线还没做。
- **第 12 节（编辑器）追加**：命令面板已列出并执行插件命令。剩下的是编辑器在加载 `break_plugin` 插件时调用注册表，以及插件提供面板或检查器扩展。
- **第 12 节（编辑器）追加**：插件宿主桥 `editor_plugin_host` 已交付，真实动态库插件能通过 `break_plugin` 加载并向命令面板注册命令，失败加载不会留下命令。仍缺：编辑器启动时发现和加载插件、插件面板和检查器扩展。
- **第 9 节（物理）追加**：`physics_sync` 的报告（`0x4002`）和修正包（`0x4003`）已登记进 break_net 默认注册表，可以通过已认证会话的 envelope 传输。仍缺：core_app 等运行时在每帧发送报告并在 DESYNC 后请求修正、增量同步、并行 solver、跨平台确定性。
- **第 9 节（物理）追加**：core_app 已在认证通道上每帧发送物理状态哈希报告并检查对端回报，desync 会写入 trace 和 `network_stats`。仍缺：DESYNC 后自动下发修正包、增量同步、并行 solver、跨平台确定性。
- **第 9 节（物理）追加**：core_app 在对端报告 desync 后会自动下发完整物理快照修正包，只发给报告方。仍缺：接收端运行时应用修正、增量同步、并行 solver、跨平台确定性。
- **第 13 节（诊断/跨线程关联）追加**：Chrome trace 导出统一标记 schema `break.trace` v1，类别集中定义在 `core/trace_schema.h`。仍缺：跨进程/网络对端 trace 合并、core_app 文本 trace（COREAPPTRACE）纳入同一 schema。
- **第 9 节（物理）追加**：loopback 测试客户端已能把收到的修正包恢复到自己的物理世界，状态哈希与权威端该 tick 的报告一致，端到端证明修正包可用。仍缺：core_app 运行时作为客户端应用修正、增量同步、并行 solver、跨平台确定性。
- **第 12 节（编辑器）追加**：编辑器插件可通过文本 manifest（build id + SHA-256 + 路径）批量加载，经 plugin host 的加载窗口登记命令，失败的插件不会留下命令。仍缺：editor 二进制启动时读取 manifest 并接入真实 `break_plugin` 加载、插件面板、检查器扩展点。
- **第 13 节（诊断/跨线程关联）追加**：core_app 文本 trace（COREAPPTRACE）可通过 `break_trace_core_app_to_chrome` 转成带 `break.trace` v1 标记的 Chrome trace JSON。仍缺：转换的 CLI 入口、文本 trace 的真实时间戳、跨进程/网络对端 trace 合并。
- **第 13 节（诊断/跨线程关联）追加**：`core_app --trace-json PATH` 直接输出带 `break.trace` 标记的 Chrome trace，可在 trace 查看器中打开。仍缺：文本 trace 的真实时间戳、跨进程/网络对端 trace 合并。
- **第 13 节（诊断/跨线程关联）追加**：`break_trace_merge` 可把多个进程的 `break.trace` 文档合并成一条时间线，每个进程独立 pid 轨道并支持时间偏移。仍缺：合并的命令行入口、core_app 文本 trace 的真实时间戳、网络对端之间的时钟对齐。
- **第 13 节（诊断/跨线程关联）追加**：`trace_merge` 命令行工具已交付，可把多个进程的 `break.trace` 文件合并为一个时间线文件。仍缺：core_app 文本 trace 的真实时间戳、网络对端之间的时钟对齐。
- **第 12 节（编辑器）追加**：editor 二进制支持 `--plugin-manifest PATH`，启动前校验 manifest，错误时以 2 退出（fail closed），合法时列出条目。仍缺：editor 真正调用 `break_plugin` 加载（需要不违反 `test_break_system_target_contract` 的可选加载库）、插件面板、检查器扩展点。
- **第 12 节（编辑器）追加**：`BREAK_EDITOR_PLUGINS=ON` 构建的 editor 会真正加载 `--plugin-manifest` 列出的插件（SHA-256 校验后经 `break_plugin` 加载，命令进入命令面板，退出时卸载）；默认构建仍只校验 manifest。仍缺：插件面板、检查器扩展点、CI 中的 `BREAK_EDITOR_PLUGINS=ON` 构建任务。
- **第 12 节（编辑器）追加**：插件可通过 `add_section` 向检查器添加只读区块，按选中实体显示，插件卸载或加载失败时移除。仍缺：插件可编辑字段、可停靠的插件面板、插件文本的多语言。
- **第 12 节（编辑器）追加**：插件可为自己的命令标签和检查器区块标题登记各语言文本，并通过 `lang_tag` 读取当前语言；切换语言时命令面板与检查器随之切换。仍缺：插件可编辑字段、可停靠的插件面板。
- **第 12 节（编辑器）追加**：插件可注册可编辑组件类型，字段在检查器中编辑，支持撤销、保存/加载、Lua 与远程协议；加载失败的插件不留下类型。仍缺：可停靠的插件面板、插件卸载时移除其组件类型（目前保留到编辑器退出）。
- **第 12 节（编辑器）追加**：插件可在底部工具窗口的「插件」页添加只读文本面板，页面可见时定时刷新，标题支持多语言。仍缺：插件面板内的交互控件（按钮、输入框）、插件卸载时移除其组件类型。
- **第 15 节（在线更新）追加**：`break_http` 支持从本地文件加载 CRL 并检查整条证书链的吊销状态。仍缺：OCSP、代理、HTTP/2，发布二进制仍没有链接 `break_http`。
- **第 10 节（音频）追加**：网络语音已可播放：`break_online_voice` 接收的 PCM 经新的 `audio_pcm_stream_*` 写入混音器，按总线增益播放，缓冲耗尽时输出静音并计数。上文「仍缺：网络语音」中接收与播放部分由此交付。仍缺：麦克风采集与编码（目前是原始 16 位 PCM）、采样率转换、语音的空间化、音频编辑工具。
- **第 10 节（音频）追加**：PCM 流支持 8..192 kHz 输入并在混音器中转换到 48 kHz，常见的 16 kHz 语音可直接播放。仍缺：麦克风采集与编码、语音空间化、音频编辑工具。
- **第 10 节（音频）追加**：网络语音流可按声源位置随距离衰减（与空间事件同一模型，含遮挡）。仍缺：麦克风采集与编码、声像/HRTF、音频编辑工具。
- **第 10 节（音频）追加**：网络语音有了压缩帧格式 `BRV2`（4 位 IMA ADPCM，约为 16 位 PCM 的四分之一），接收器兼容旧的 `BRV1`。仍缺：麦克风采集、感知编码器（Opus 等）、声像/HRTF、音频编辑工具。
- **第 10 节（音频）追加**：网络语音接收器有了 fuzz 目标 `fuzz_break_online_voice`（参考解码器 + 影子抖动缓冲，进入 CI fuzz 冒烟）。仍缺：麦克风采集、感知编码器（Opus 等）、声像/HRTF、音频编辑工具。
- **第 12 节（编辑器）追加**：插件卸载时移除它注册且未被实体使用的组件类型（仍被使用的保留，下次 release 再试）。上文「插件卸载时移除其组件类型」由此交付。仍缺：插件面板内的交互控件（按钮、输入框）。
- **第 12 节（编辑器）追加**：插件面板可以带按钮（每个面板最多 4 个，标签可翻译，点击用编辑器文档运行插件回调，失败时记日志）。上文「插件面板内的交互控件」中的按钮由此交付。仍缺：插件面板内的输入框。
- **第 12 节（编辑器）追加**：插件面板可以带单行输入框（每个面板最多 2 个，提示文字可翻译，草稿在重建后保留，回车用编辑器文档提交给插件回调，失败时记日志）。「插件面板内的交互控件」（按钮、输入框）至此全部交付。
- **第 10 节（音频）追加**：高于 48 kHz 的 PCM 流在降采样前经过 4 阶 Butterworth 抗混叠低通（截止 21.6 kHz），上文「降采样前的低通滤波」由此交付。仍缺：麦克风采集、感知编码器（Opus 等）、声像/HRTF、高质量（sinc）重采样、音频编辑工具。
- **第 10 节（音频）追加**：空间 PCM 流可按监听者朝向做等功率立体声声像（`audio_pcm_stream_set_panning`），上文「声像/HRTF」中的声像部分由此交付。仍缺：HRTF 与前后区分、事件 voice 的声像、麦克风采集、感知编码器（Opus 等）、高质量（sinc）重采样、音频编辑工具。
- **第 10 节（音频）追加**：空间事件 voice 可按监听者朝向做等功率立体声声像（`AudioEventDesc.panned`），「事件 voice 的声像」由此交付。仍缺：HRTF 与前后区分、麦克风采集、感知编码器（Opus 等）、高质量（sinc）重采样、音频编辑工具。
- **第 10 节（音频）追加**：PCM 流可选 16 tap Lanczos 重采样（`audio_pcm_stream_set_resample`），「高质量（sinc）重采样」由此交付。仍缺：HRTF 与前后区分、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：空间 PCM 流可打开后方提示（`audio_pcm_stream_set_rear_cue`，身后声源加低通），「前后区分」的基础部分由此交付。仍缺：HRTF、耳间时差、高度提示、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：空间事件 voice 也可打开后方提示（`AudioEventDesc.rear_cue`），前后区分覆盖 PCM 流与事件两类声源。仍缺：HRTF、耳间时差、高度提示、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 15 节（在线更新）追加**：`break_http` 可经 HTTP CONNECT 代理访问 https 目标（`BreakHttpConfig.proxy`），TLS 仍校验目标的证书、主机名、钉扎和 CRL。仍缺：代理认证、https 代理、OCSP、HTTP/2，发布二进制仍没有链接 `break_http`。
- **第 15 节（在线更新）追加**：`break_http` 支持代理 Basic 认证（`proxy_user`/`proxy_password`，只放在 CONNECT 请求中）。仍缺：Digest/NTLM 等其他代理认证、https 代理、OCSP、HTTP/2，发布二进制仍没有链接 `break_http`。
- **第 13 节（诊断/跨线程关联）追加**：core_app 文本 trace 转换器支持可选的 `ts_us` 微秒时间戳作为事件时间，无该字段的旧 trace 输出不变。仍缺：core_app 写出 `ts_us`、网络对端之间的时钟对齐。
- **第 13 节（诊断/跨线程关联）追加**：`core_app --trace-timestamps` 在文本 trace 每行写入单调时钟 `ts_us`，`--trace-json` 与 `trace_merge` 得到真实时间轴（同一台机器上的多个进程可直接对齐）。仍缺：不同机器上网络对端之间的时钟对齐。
- **第 13 节（诊断/跨线程关联）追加**：`core/clock_offset` 用 NTP 式探测样本估计两台机器的时钟偏移（最小延迟样本、误差上界 `ceil(delay/2)`），并换算成 `trace_merge --offset-us` 的平移量。仍缺：探测包在 core_app 会话协议上的收发、估计结果自动用于 trace 合并。
- **第 13 节（诊断/跨线程关联）追加**：时钟探测消息 `0x4004` 的 32 字节线格式与编解码（`core_app_clock_probe_*`）已加入默认注册表。服务端 transport 已应答探测，并主动探测每个对端、把偏移写入 `event=network_clock_offset` trace 行。`trace_merge --clock-offset SERVER_TRACE` 已从服务端 trace 读取该行并自动平移两个输入。仍缺：多个对端时只能手动指定 `--offset-us`；偏移只来自服务端探测。
- **第 10 节（音频）追加**：空间 PCM 流可打开耳间时差（`audio_pcm_stream_set_interaural_delay`，Woodworth 模型，远端耳朵最多延迟 31 帧），「耳间时差」由此交付。仍缺：HRTF、高度提示、事件 voice 的耳间时差、延迟变化的平滑、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：空间事件 voice 也可打开耳间时差（`AudioEventDesc.interaural_delay`），耳间时差覆盖 PCM 流与事件两类声源，上文「事件 voice 的耳间时差」由此交付。仍缺：HRTF、高度提示、延迟变化的平滑、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：耳间时差的延迟变化不再跳变，流与事件 voice 共用 `ItdLine`，在 32 帧（`AUDIO_PCM_STREAM_ITD_FADE_FRAMES`，约 0.67 ms）内线性交叉淡化，延迟未变的耳朵保持逐位精确；淡化中目标再变时等本次结束，尚未播放的延迟线直接采用目标。「延迟变化的平滑」由此交付。仍缺：HRTF、高度提示、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 13 节（诊断/跨线程关联）追加**：`trace_merge --clock-offset SERVER_TRACE SERVER.json --session N PEER.json ...` 按会话从服务端 trace 读取每个对端的偏移（`break_trace_core_app_clock_offset_for_session`），用 `clock_offset_merge_shifts_many` 把服务端与所有对端放在同一时间轴上，「多个对端时只能手动指定 `--offset-us`」由此交付。仍缺：偏移只来自服务端探测。2026-11-20 补充：对端文档若带 `event=network_session_welcome`，`trace_merge` 会自行读出会话号，不再需要手动 `--session`（核心 `break_trace_core_app_session`/`_from_chrome`）；2026-11-20 补充：loopback 测试客户端新增 `--trace`，用 core_app 同一写入器写出自己的 `event=network_session_welcome` 行，驱动核对它命名的会话与服务端认证的会话一致。2026-11-20 补充：测试客户端新增 `single` 场景（单连接单会话）与 `trace_convert` 工具，`test_core_app_network_single_session` 端到端验证「对端自报会话号 -> trace_merge 自行读出 -> 同一时间轴」，不再需要 `--session`。仍缺：发布二进制中的客户端模式（目前只有测试客户端）。
- **第 10 节（音频）追加**：空间 PCM 流可打开高度提示（`audio_pcm_stream_set_elevation_cue`，按声源与 up 向量夹角做频谱倾斜：上方高架提升，下方低通），「高度提示」由此交付。仍缺：HRTF、事件 voice 的高度提示、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：空间事件 voice 也可打开高度提示（`AudioEventDesc.elevation_cue`），高度提示覆盖 PCM 流与事件两类声源，「事件 voice 的高度提示」由此交付。仍缺：HRTF、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 15 节（在线更新）追加**：`break_http` 可回应代理的 Digest 质询（RFC 7616，MD5/SHA-256，qop=auth 或 RFC 2069 形式），在新连接上重发一次 CONNECT，「Digest 代理认证」由此交付。仍缺：NTLM、https 代理、OCSP、HTTP/2，发布二进制仍没有链接 `break_http`。
- **第 15 节（在线更新）追加**：`break_http` 支持强制 OCSP stapling（`require_ocsp_staple`）：握手时请求证书状态，要求附带的响应由叶子的签发 CA 或其委托 responder 签名、状态为 good 且在有效期内，「OCSP」中的 stapling 部分由此交付。仍缺：主动查询 OCSP responder、NTLM、https 代理、HTTP/2，发布二进制仍没有链接 `break_http`。
- **第 9 节（物理）追加**：`physics_sync` 提供增量修正包（"PSND"，相对双方已持有的基线快照只发送变化的字节区段，接收端在临时缓冲区重建并校验后原子恢复），「增量同步」的编解码部分由此交付。仍缺：core_app 保存每个对端的基线并选择增量或完整包、core_app 运行时作为客户端应用修正、并行 solver、跨平台确定性。
- **第 9 节（物理）追加**：core_app 为每个对端保存最近修正的基线，对端用匹配报告确认后，下一次修正改发增量包（loopback 本机 10644 字节对 28 字节），接收端 `physics_sync_apply_received` 统一处理完整包和增量包并维护自己的基线，「增量同步」由此在运行时接入。仍缺：core_app 运行时作为客户端应用修正、并行 solver、跨平台确定性。
- **第 13 节（诊断/跨线程关联）追加**：服务端认证行带 `session=`（`network_session result=authenticated session=S tick=N`），与 `network_clock_offset` 的会话号一致，驱动脚本验证两者对应。只看服务端 trace 就能列出会话和偏移，但对端 trace 自身仍不记录会话号，`trace_merge` 中对端文件与会话的对应仍需手动指定。仍缺：对端 trace 写入自己的会话号（需要服务端在认证后告知对端）。
- **第 13 节（诊断/跨线程关联）追加**：2026-11-17 服务端在认证后发送会话欢迎消息 `0x4005`（16 字节，`SESW` + 保留 + u64 会话号），对端由此得知服务端 trace 中自己的会话号；欢迎是对端认证后收到的第一条应用消息，`network_stats` 追加 `session_welcomes_sent`。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「服务端告知对端会话号」。「需要服务端在认证后告知对端」由此交付。仍缺：core_app 运行时本身不作为客户端运行，没有发布二进制把会话号写进对端 trace（目前只有测试客户端读取）。
- **第 14 节（崩溃上传）追加**：2026-11-17 Mach-O 读取器支持通用（fat）文件，`break_macho_symbols_open_cpu` 取指定 CPU 的 slice，符号库默认取 x86_64；条目逐个校验（越界、重叠、重复 CPU、slice 与条目 CPU 不符都拒绝）。见 [`docs/design/crash_symbolization.md`](../design/crash_symbolization.md) 第 2 节。「fat 文件」由此交付。2026-11-20：arm64 帧展开已可用——AAPCS64 与 x86-64 的帧记录同为 `[fp]`/`[fp+8]`，同一套遍历通用并有 arm64 形状的用例；信号处理器在 Linux arm64 下读 `pc`/`sp`/`x29` 而不再写零，字段名已对照内核 aarch64 `asm/sigcontext.h` 编译验证；2026-11-20 新增 `toolchain-aarch64-linux.cmake` 与 CI 的 `lane-cross-aarch64-linux`（初版仅构建）；初版仍缺可运行 arm64 测试的通道，由下一条 QEMU 交付补齐。
- **第 14 节（崩溃上传）追加**：2026-11-20 `lane-cross-aarch64-linux` 增加 `qemu-user`，在保留 arm64 编译/链接和对象架构检查的同时执行 `test_break_crash`，37 项包含真实 SIGSEGV/SIGABRT 记录捕获。该步交付时 arm64 `test_break_crash_symbolize` 仍待工具链与嵌套 fixture 接入，由下一条补齐。
- **第 14 节（崩溃上传）追加**：2026-11-20 ELF64 读取器支持 `EM_AARCH64`，CI 通过显式交叉 `nm/readelf/strip` 和嵌套 QEMU runner 执行 `test_break_crash_symbolize`，45 项包含真实非 PIE/PIE arm64 调用链符号化。精简 QEMU 环境的两个真实 LLVM Mach-O 子检查可条件跳过，不记作已运行。仍缺：物理设备、GPU、生产部署的收集服务、minidump 和 Windows 符号化。
- **第 14 节（崩溃上传）追加**：2026-11-20 arm64 lane 统一执行 `^test_break_crash` 的七项 CTest：六个 `crash` 标签测试加服务端归档契约。聚类 26 例、上传 8 例、两项归档契约和 e2e 11 场景均接入，不再只有崩溃记录与符号化两项；目标 `nm` 和嵌套目标进程均显式配置。仍缺：全量其他 arm64 测试、物理设备、GPU、生产收集服务、minidump 和 Windows 符号化。
- **第 15 节（在线更新）追加**：2026-11-20 arm64 lane 新增七项 HTTP/更新测试，并与崩溃七项统一为十四项 CTest。更新核心 21 例、客户端 44 例、HTTP 72 例、manifest、两个归档契约和更新 e2e 七项均纳入 arm64 QEMU lane；目标进程由 QEMU 启动，HTTP 契约等宿主驱动由 CMake/交叉 `nm` 检查目标文件。仍缺：生产更新服务、HTTP/2、https 代理、主动 OCSP、其他 arm64 子系统、GPU 和物理设备证据。
- **第 16 节（安全/反作弊）追加**：2026-11-20 arm64 lane 新增六项安全/密码学测试，与既有十四项统一为二十项，覆盖全部 security 标签测试。crypto 20 例、keygen 权限/短写/并发、authority 14 例及两个契约通过；integrity 其他七项执行，ptrace 正例因 QEMU `PTRACE_TRACEME=ENOSYS` 仅跳过设置步骤，原生正例仍严格通过。客户端信号仍不参与授权；真机反调试、生产权威持久化及其他子系统未由此交付。
- **第 6 节（网络）追加**：2026-11-20 arm64 lane 新增八项无 Snowflake 依赖的核心网络测试，统一选择达到二十八项。packet/network、online lobby/NAT/voice、voice mixer、replay window、message rate 分项 20/18/10/23/16/11/5/4 均通过 QEMU，未改测试或产品代码。Snowflake 适配器/会话/TLS 和 QUIC 仍受依赖门控；QUIC 需要独立 Snowflake + OpenSSL≥3.5 交叉依赖项目，当前 OpenSSL 3.0.13 不会被当作通过。
- **第 10 节（音频）追加**：2026-11-17 新增独立的 HRTF 模块 `audio_hrtf`。它包含三部分：每个方向的左右耳脉冲响应集合，可从调用者数组、`BHRT` 文件或内置的 Brown–Duda 球头模型（217 个方向）创建；最近方向查找；不分配内存的单声道转立体声卷积渲染器，换方向时做 64 帧交叉淡化。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「HRTF」。「HRTF」的基础模块由此交付。仍缺：把 HRTF 接入 PCM 流和事件 voice（以及它与现有声像、耳间时差、后方提示、高度提示的取舍）、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：2026-11-17 空间 PCM 流（网络语音、生成音频）可挂上 HRTF 集合做双耳渲染（`audio_pcm_stream_set_hrtf`）：按监听者坐标系的声源方向取最近方向，对左右声道平均后的单声道做卷积，换方向时 64 帧交叉淡化；挂上时声像、后方、高度提示和耳间时差不作用。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「PCM 流的 HRTF」。「把 HRTF 接入 PCM 流」由此交付。仍缺：事件 voice 的 HRTF、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：2026-11-17 空间事件 voice 也可通过 `AudioEventDesc.hrtf` 做双耳渲染：注册时要求 spatial 与引擎采样率的集合，每个 voice 有自己的渲染器（START 时历史清零），下标随 trigger、`audio_voice_set_position` 和监听者更新按 revision 发布，换方向 64 帧交叉淡化；挂上时声像、后方、高度提示和耳间时差不作用。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「事件 voice 的 HRTF」。「事件 voice 的 HRTF」由此交付，HRTF 覆盖 PCM 流与事件两类声源。仍缺：麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：2026-11-17 新增麦克风采集模块 `audio_capture`：打开默认输入（或 miniaudio 空设备、无设备的 FAKE），把帧转换为 16 位放入单生产者单消费者环形缓冲，所有者线程读取后可交给 `break_voice_encode*`；缓冲满时丢弃最新帧并计数，回调纳入实时契约。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「麦克风采集」。「麦克风采集」由此交付。帧以配置的采样率交付（miniaudio 内置转换）。仍缺：回声消除、降噪、自动增益、指定输入设备、真实麦克风验证、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：2026-11-17 采集可按名称选择输入设备（`audio_capture_list_devices`、`audio_capture_create_named`，`audio_capture_device_name` 返回实际打开的设备），「指定输入设备」由此交付；采集帧以配置的采样率交付（miniaudio 内置转换），不存在采集端采样率转换的缺口。仍缺：回声消除、降噪、自动增益、设备热插拔、真实麦克风录音验证、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：2026-11-17 新增采集语音的自动增益 `audio_agc`（10 ms 均方电平、噪声门限下增益保持、±最大增益、attack/release、限幅不回绕），在 `audio_capture_read_i16` 与 `break_voice_encode*` 之间使用。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「自动增益（AGC）」。「自动增益」由此交付。仍缺：回声消除、降噪、设备热插拔、真实麦克风录音验证、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：2026-11-17 新增采集语音的噪声门 `audio_noise_gate`（时域降噪：10 ms 均方电平、自适应底噪、高出底噪达到阈值才开门、关门时按配置衰减、attack/release），建议放在 AGC 之前。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「噪声门（降噪）」。「降噪」以时域方式交付；频谱降噪（谱减、维纳滤波）没有做，因为引擎没有 FFT。仍缺：回声消除、设备热插拔、频谱降噪、真实麦克风录音验证、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：2026-11-17 新增采集语音的回声消除 `audio_echo_canceller`（NLMS 自适应滤波器学习扬声器到麦克风的路径并减去预测回声，Geigel 双讲检测加保持时间），放在噪声门与 AGC 之前。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「回声消除（AEC）」。「回声消除」由此交付；参考信号需由调用者对齐。仍缺：自动延迟估计、非线性残余回声抑制、设备热插拔、频谱降噪、真实麦克风与扬声器验证、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：2026-11-17 采集支持设备丢失检测与重新打开：`audio_capture_lost`（无停止请求时设备停止，来自 miniaudio 通知或设备状态轮询）、`audio_capture_reroutes`（后端自行切换设备的次数）、`audio_capture_reopen`（先开新设备再关旧设备，保留环形缓冲中的帧，失败时不变）。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「麦克风采集」。「设备热插拔」由此交付；新设备出现需轮询 `audio_capture_list_devices`。仍缺：真实设备拔插验证、频谱降噪、自动延迟估计、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：2026-11-17 新增回声参考的延迟估计 `audio_delay_estimator`（归一化互相关，返回整数帧延迟与相关系数）与延迟线 `audio_delay_line`，用于在 `audio_echo_canceller` 之前对齐播放参考。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「延迟估计与参考延迟线」。「参考与采集自动对齐」由此交付。仍缺：亚帧精度、延迟漂移跟踪与时钟漂移补偿、非线性残余回声抑制、频谱降噪、真实设备验证、感知编码器（Opus 等）、音频编辑工具。

- **第 10 节（音频）追加**：2026-11-17 新增 `audio_fft`：4..65536 的基 2 实数正逆 FFT、周期 Hann 窗，计划只读且只有创建时分配。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「FFT」。上文「因为没有 FFT 而未做频谱降噪」的基础依赖由此交付，但频谱降噪本身仍未实现。仍缺：频谱降噪、非线性残余回声抑制、亚帧延迟与漂移补偿、感知编码器（Opus 等）、音频编辑工具、真实设备验证。

- **第 10 节（音频）追加**：2026-11-17 新增 `audio_noise_suppressor`，基于 `audio_fft` 提供单声道 Hann/STFT 频谱降噪：100 ms 平滑功率目标、受限底噪跟踪、2 倍谱减、可配置最大衰减、固定一帧 FFT 大小延迟与任意分块一致性。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「频谱降噪」。上文「频谱降噪未实现」由此交付。仍缺：多声道与学习型降噪、非线性残余回声抑制、感知编码器（Opus 等）、真实设备与听感验证。

- **第 10 节（音频）追加**：2026-11-17 新增 `audio_residual_echo_suppressor`，在线性 NLMS 之后按参考/误差包络比值抑制非线性残余回声，支持参考 hangover、受限路径跟踪、近端活动冻结及平滑增益。真实 AEC 端到端测试验证残余衰减超过 10 dB，38/38 定向变异被捕获。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「残余回声抑制」。上文「非线性残余回声抑制」的基础 postprocessor 由此交付；近端标志由调用者提供。仍缺：自动近端检测、频谱相干性抑制、多声道、真实声学验证。

- **第 10 节（音频）追加**：2026-11-18 `audio_delay_estimator_estimate_subframe` 以最佳绝对相关峰值的抛物线插值提供亚帧延迟，新增分数延迟线用线性插值对齐参考；旧整数接口与输出保持兼容。sinc 测试在 3.25/12.5/31.75 帧处误差小于 0.25 帧。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「延迟估计与参考延迟线」。上文「亚帧精度」的基础能力由此交付。仍缺：延迟漂移跟踪、时钟漂移补偿、GCC-PHAT、延迟线 sinc 模式及真实声学验证。

- **第 10 节（音频）追加**：2026-11-18 新增 `audio_delay_tracker`，在亚帧估计之上提供最小 |correlation| 门控、连续接受锁定、拒绝保持/解锁和按推送时间限制的双向延迟漂移。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「延迟估计与参考延迟线」。「按置信度自动跟踪延迟漂移」由此交付。仍缺：时钟漂移估计与重采样补偿、GCC-PHAT、自动更新调度及真实设备验证。

- **第 10 节（音频）追加**：2026-11-18 新增 `audio_gcc_phat`：使用现有实数 FFT 实现 GCC-PHAT 延迟估计，支持带符号 raw peak、整数端点与亚帧抛物线细化；只有 create 分配。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「延迟估计与参考延迟线」。上文「GCC-PHAT/频域加速」的独立频域能力由此交付。仍缺：与 tracker 的自动接线、时钟漂移补偿、多声道、归一化置信度与真实声学验证。

- **第 10 节（音频）追加**：2026-11-18 新增 `audio_drift_estimator`，对置信度门控的延迟样本做有界滑窗线性回归，输出相对时钟漂移 ppm 和平均相关性；严格递增帧号与相对索引避免大基准和环回绕误差。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「时钟漂移估计」。「时钟漂移估计」由此交付，但「重采样补偿」仍未实现。仍缺：补偿器、自动接线、抗离群点回归与真实设备验证。

- **第 10 节（音频）追加**：2026-11-18 新增 `audio_drift_resampler`，用可调输入/输出比率的流式线性插值补偿时钟漂移，支持任意分块、容量失败原子性和实际输出计数；真实估计器的 50 ppm 结果可直接设置比率。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「时钟漂移补偿」。上文「重采样补偿器」由此交付。仍缺：sinc 质量模式、多声道、自动闭环控制与真实设备验证。

- **第 10 节（音频）追加**：2026-11-18 新增 `audio_edit`，提供单/双声道 i16 原地裁剪、删除、线性淡入淡出、峰值归一化和限幅混合；无分配且覆盖零长度与失败原子性。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。上文「音频编辑工具」的基础库部分由此交付。仍缺：编辑器 UI、时间线/撤销、媒体文件解析、自动化和真实听测。

- **第 10 节（音频）追加**：2026-11-18 `AudioDelayLine` 新增可选 16 tap Blackman 加窗 sinc 模式，以明确的 8 帧额外延迟提供因果高质量分数延迟，支持原地/分块与 i16 过冲饱和，旧线性输出不变。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「延迟估计与参考延迟线」。上文「延迟线 sinc 模式」由此交付。仍缺：多声道、连续延迟交叉淡化、自动质量选择与真实声学验证。

- **第 10 节（音频）追加**：2026-11-18 `AudioDriftResampler` 新增固定 16 tap sinc 质量模式、8 输入帧前瞻、动态比率与双向模式切换，切回线性时按历史补齐积压位置并扩大安全容量。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「时钟漂移补偿」。上文漂移补偿的「sinc 质量模式」由此交付。仍缺：比例自适应强降采样抗混叠、多声道、自动闭环控制与真实设备验证。

- **第 10 节（音频）追加**：2026-11-18 `audio_gcc_phat_estimate_with_confidence` 在 PHAT 选中的整数 lag 上直接计算带符号归一化互相关，与 tracker 门控同义，旧 raw peak 保留。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「延迟估计与参考延迟线」。上文「归一化置信度」由此交付。仍缺：GCC-PHAT 与 tracker 的自动接线、多声道及真实声学验证。

- **第 10 节（音频）追加**：2026-11-18 `audio_delay_tracker_create_gcc` 提供显式 GCC-PHAT 后端，复用原配置、归一化门控和跟踪状态机，只分配选定后端；默认时域行为不变。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「延迟估计与参考延迟线」。上文「GCC-PHAT 与 tracker 接线」由此交付。仍缺：运行中后端切换、自动更新调度、多声道与真实声学验证。

- **第 10 节（音频）追加**：2026-11-18 `audio_drift_estimator_estimate_robust` 以 repeated-median 提供抗孤立离群点的漂移斜率，固定 scratch、无估计期分配，旧最小二乘接口不变。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「时钟漂移估计」。上文「抗离群点回归」由此交付。仍缺：自动闭环控制、多声道与真实设备验证。

- **第 10 节（音频）追加**：2026-11-18 AEC 暴露逐帧近端状态，`audio_residual_echo_suppressor_process_with_aec` 自动把该状态用于残余抑制，且与手工逐帧序列逐位一致。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「残余回声抑制」。上文「自动近端检测」的库集成由此交付。仍缺：频谱相干性、生产采集管线接线、多声道与真实声学验证。

- **第 10 节（音频）追加**：2026-11-18 新增 `AudioVoiceProcessor`，统一串联 AEC、残余抑制、频谱降噪、噪声门和 AGC，支持任意分块、reset 与尾部排空，手工参考链逐位一致。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「集成语音处理链」。这是可复用处理库，不是生产采集接线。仍缺：core_app 设备/网络集成、多声道、自动延迟跟踪与真实声学验证。

- **第 10 节（音频）追加**：2026-11-18 `AudioDelayLine` 支持可选连续延迟交叉淡化，新旧目标共用历史，活跃期拒绝重定向并保持状态原子性；默认立即切换不变。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「延迟估计与参考延迟线」。上文「连续延迟交叉淡化」由此交付。仍缺：多声道、自动淡化策略与真实声学验证。

- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-18 `BreakEditorDoc` 支持短 PCM 附件及 trim/cut/fade/normalize/mix 的真实快照 undo/redo，含 origin、drop-oldest、OOM 和 reset/load 生命周期。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。上文「音频编辑工具」的文档/撤销部分由此交付。仍缺：波形 UI、媒体文件解析、时间线/自动化与真实听测。

- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-18 `audio_wav` 与 `break_editor_doc_audio_attach_wav` 支持严格校验的 PCM16 单/双声道 WAV 导入，含结构 fuzz、OOM 和历史原子性。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。上文「媒体文件解析」的 PCM WAV 子集由此交付。仍缺：其他格式、导出、VFS、波形 UI、时间线与真实听测。


- **第 10 节（音频）追加**：2026-11-18 新增 `audio_reference_*` 播放参考捕获，真实设备与 FAKE 渲染共用引擎最终混音回调，以固定 48 kHz 单声道 i16 SPSC 环交付；支持启停、停止后排空、有界溢出计数与安全重置。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「播放参考捕获」。这补齐了语音处理链的真实参考来源，但不等于 core_app 采集/处理/网络接线完成。仍缺：参考与采集的自动延迟/漂移闭环、生产语音管线、多声道与真实声学验证。


- **第 10 节（音频）追加**：2026-11-18 新增 `AudioVoiceAligner`，把原始播放参考/采集的 tracker 推送、固定周期更新与分数延迟线应用接成确定性控制环；支持时域/GCC-PHAT 显式构造和任意调用分块一致。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「语音参考自动对齐」。上文「自动更新调度」和 tracker→延迟线接线由此交付。仍缺：漂移补偿闭环、reset、sinc/交叉淡化配置、生产采集/VoiceProcessor/core_app/网络接线与真实声学验证。


- **第 10 节（音频）追加**：2026-11-18 正式 `core_app_runtime` 新增 `CoreAppVoice` PCM 泵，将 48 kHz 单声道采集、播放参考、自动对齐与语音处理接成 480 帧处理路径，并以 16 项 SPSC 队列交付 PCM；手动和专用 worker 共用实现。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「Core App 语音 PCM 泵」。这是生产组件而非完整在线语音。仍缺：core_app CLI/协调器/网络 hook、编码发送、设备恢复、尾部排空、漂移补偿和真实声学验证。
- **第 10 节（音频）追加**：2026-11-18 `core_app` 新增 `--voice off|fake|device` 语音通道：PCM 泵进入真实可执行程序和协调器生命周期（`voice` 子系统先于 audio 停止并在 join 阶段销毁），Null 采集后端与打不开的采集设备按无麦克风处理（`--require-device` 时退出 77），运行中采集失败以 `stage=voice` 失败。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「Core App 语音通道」。上一条中的「core_app CLI/协调器」由此交付。仍缺：编码与通过网络 hook 发送、设备丢失自动恢复、尾部排空、漂移补偿、真实声学验证；CI 无音频设备，设备通道只在本机验证。
- **第 10 节（音频）追加**：2026-11-18 core_app 语音帧经 `--network` 发送：新消息 `0x4006`（AUTHENTICATED，上限一帧 BRV1），每帧编码为 BRV2 发给每个已认证对端，实时丢弃不排队；真实 TLS + AUTH-v2 对端解码 30 帧连续语音。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「语音帧经网络发送」。「编码与通过网络 hook 发送」由此交付。仍缺：服务端接收与混音对端语音、路由/静音、真实对端上的抖动与漂移处理、尾部排空、设备恢复、Opus。
- **第 10 节（音频）追加**：2026-11-18 core_app 服务端接收对端语音：`0x4006` 处理函数按连接做 40 ms 抖动缓冲，按单调时钟播放，连接关闭时尾部排空；真实对端突发 20 帧后服务端全部播放，重复帧与错误格式帧计为丢弃。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「服务端接收对端语音」。「服务端接收对端语音」和「尾部排空」由此交付。仍缺：混音与播放、对端之间转发与静音、漂移补偿、设备恢复、Opus。
- **第 10 节（音频）追加**：2026-11-18 core_app 语音采集设备丢失后自动重开默认输入（device 模式 100 ms × 50 次），恢复后丢弃播放参考积压并重置处理链，用尽才失败。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「语音采集设备自动恢复」。「设备恢复」中的采集部分由此交付。仍缺：命名设备切换、播放参考设备恢复、漂移补偿、Opus。
- **第 10 节（音频）追加**：2026-11-18 core_app 播放设备丢失后自动重开默认输出（device 模式 100 ms × 50 次），声源、总线、听者与播放参考环保留，语音通道跟随重开重新对齐参考，用尽才让当帧失败。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「播放设备自动恢复」。「设备恢复」中的播放部分由此交付。仍缺：命名设备切换、漂移补偿、对端语音混音与转发、Opus。
- **第 10 节（音频）追加**：2026-11-18 播放与采集设备可按名称列出、打开和切换（`audio_system_switch_device` 先开新设备，失败保留旧设备），core_app 通过 `--audio-device`、`--voice-capture-device` 选择设备，未知名称 exit 2 并写 rejected 行，恢复时重开已选设备。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「按名称选择音频设备」。「命名设备切换」由此交付。仍缺：漂移补偿、对端语音混音与转发、按对端静音、Opus、真实声学验证。
- **第 10 节（音频）追加**：2026-11-19 core_app 服务端开启 `--voice-relay` 后，把从一个对端接受的语音帧（经接收器校验）以 `0x4007` 转发给其他所有已认证对端，附来源会话号，不回传给来源。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「服务端语音转发」。「对端语音转发」由此交付。仍缺：对端语音混音、按对端静音、语音专用限速、漂移补偿、Opus、真实声学验证。
- **第 10 节（音频）追加**：2026-11-19 core_app 用户可通过 `0x4008` 请服务端停止或恢复把某个来源会话的语音转发给自己（每个连接最多 16 个，断开即清空）。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「按用户屏蔽语音」。「按对端静音」由此交付。仍缺：对端语音混音、语音专用限速、漂移补偿、Opus、真实声学验证。
- **第 10 节（音频）追加**：2026-11-19 core_app 服务端对每个连接的语音限速（120 帧/秒，突发 64 帧），超限帧在解码和转发前丢弃并计数，连接保持。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「语音限速」。「语音专用限速」由此交付。仍缺：对端语音混音、漂移补偿、Opus、真实声学验证。
- **第 10 节（音频）追加**：2026-11-19 core_app 可在运行中通过 scenario 命令 `audio-device [NAME]` 切换播放设备，切换在音频 owner 线程上按队列顺序执行，未知名称被拒且旧设备继续播放。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「运行中切换播放设备」。「运行中通过命令切换设备」中的播放部分由此交付。仍缺：运行中切换采集设备、对端语音混音、漂移补偿、Opus、真实声学验证。
- **第 10 节（音频）追加**：2026-11-19 core_app 可在运行中通过 scenario 命令 `voice-capture-device [NAME]` 切换语音采集设备，切换在语音泵线程上执行，未知名称被拒且旧输入继续采集，不退回默认。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「运行中切换采集设备」。「运行中切换采集设备」由此交付。仍缺：对端语音混音、漂移补偿、Opus、真实声学验证。
- **第 10 节（音频）追加**：2026-11-19 `break_online` 新增对端语音混音器 `BreakVoiceMixer`（`src/network/break_voice_mixer.h`）：每个来源会话一个抖动缓冲接收器，按插入顺序以 i32 累加并饱和到 i16，最多 16 个来源，超过时按空闲超时淘汰最久未活动的来源，否则拒绝。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「对端语音混音」。「对端语音混音」的客户端部件由此交付；core_app 没有客户端模式，尚未接入。仍缺：漂移补偿、Opus、真实声学验证。
- **第 10 节（音频）追加**：2026-11-19 新增闭环时钟漂移补偿器 `AudioDriftCompensator`（`src/audio/audio_drift_compensator.h`）：延迟测量送入漂移估计器，每次 update 把残余延迟斜率换算成重采样比率 `r·(1 - gain·slope)`，限幅到 `max_correction_ppm`，然后清空估计窗口；参考信号用该比率经 `audio_drift_resampler` 重采样。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「时钟漂移闭环补偿」。「漂移补偿」的组件部分由此交付；尚未接入 core_app 语音泵。仍缺：漂移补偿接入语音管线、Opus、真实声学验证。
- **第 10 节（音频）追加**：2026-11-19 core_app 语音泵接入 `AudioDriftCompensator`：播放参考先按当前比率重采样再交给对齐器，对齐器锁定后每 10 个包取一次延迟测量，每 32 个被接受的测量更新一次比率；采集恢复、切换设备和播放重开时比率归 1。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「语音漂移补偿」。「漂移补偿」由此交付。仍缺：Opus、真实声学验证。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 `audio_wav_encode_i16` 输出规范的 44 字节头 PCM16 WAV；`break_editor_doc_audio_save_wav` 把编辑器中的音频附件先写到 `<path>.tmp`，再重命名覆盖目标，失败时不留下半个文件，也不改动文档。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。上文「导出」由此交付（PCM16 WAV）。仍缺：其他格式、VFS、波形 UI、时间线与真实听测。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器底部工具窗新增“音频”页：显示文档音频附件的采样率、声道与时长，以及按像素列计算的最小/最大波形，随编辑、撤销和重置刷新；资源浏览器点击 `.wav` 打开附件（已有附件时拒绝替换）。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。上文「波形 UI」由此交付（只读）。仍缺：播放、选区编辑、时间线、其他格式、VFS 与真实听测。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页可以播放附件：副本经引擎 PCM 流送到默认播放设备，写完排空后自动停止，编辑时停止，播放中显示位置。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。上文「播放」由此交付。仍缺：选区编辑、时间线、跳转/循环、其他格式、VFS 与真实听测。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页支持点击波形跳转并显示播放光标：播放中从点击处重播，停止时作为下次播放起点。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「跳转」由此交付。仍缺：选区编辑、时间线、循环、其他格式、VFS 与真实听测。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页支持 Shift+点击选区，并用“裁剪/剪切”按钮对选区执行可撤销编辑。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「选区编辑」中的裁剪与剪切由此交付；有选区时“播放”只播放选区；“淡入淡出/归一化”可只作用于选区。拖动波形可选区，波形上方有时间刻度条，可循环播放当前范围。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页支持波形缩放与滚动：`+`/`-` 以视图中心折半或加倍（下限 16 帧），`<`/`>` 移动视图长度的四分之一，波形列与刻度步长随视图变细。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「缩放」由此交付。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页支持滚轮缩放（以指针下的帧为锚点，Shift+滚轮平移）和“跟随”复选框（播放时视图按自身长度整段跳转以包住播放位置）。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「滚轮缩放」与「播放时自动滚动」由此交付。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页支持键盘缩放与滚动：波形取得焦点后 `+`/`-` 缩放、左右方向键平移、`Home` 回到整段，命中的键不再落到 shell 全局快捷键。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「键盘缩放快捷键」由此交付。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页新增视图滚动条（水平 `my_scroll_bar`，映射视图位置与占比并可拖动跳转）；`my_scroll_bar` 本身新增水平方向支持。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「滚动条控件」由此交付。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页新增幅度缩放（只作用于显示的 1~32 倍，2 的幂步进），安静素材的包络也能看清。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。仍缺：dB/对数刻度、按峰值自动增益、逐帧平滑滚动、其他格式、VFS 与真实听测。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页按声道分泳道绘制波形（核心 `break_editor_doc_audio_waveform_channel`），立体声可分别看左右声道。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「分声道显示」由此交付。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页新增幅度自适应（"=" 按钮按当前视图峰值选显示倍数）。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「按峰值自动增益」由此交付。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频预览支持分声道独奏（独奏声道写进所有输出声道，`editor-audio-solo` 按钮循环切换）。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「分声道独奏」由此交付。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频预览支持分声道静音（该声道清零、其余保留，独奏生效时不应用），`editor-audio-mute` 按钮循环切换。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「分声道静音」由此交付。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页显示当前视图的 peak/RMS dBFS 读数（核心 `break_editor_doc_audio_peak_range`）。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「dB 读数」由此交付。
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-20 编辑器音频波形新增 dB 网格（每泳道 -6/-12/-18/-24 dBFS 对称网格线，随幅度缩放移动）。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「波形上的 dB 网格」由此交付；2026-11-20 网格线另带级别标注（泳道过窄时只画线不标注），显示幅度倍数按泳道独立设置并可各自按峰值适配；电平读数另含 4 倍过采样的真峰值（dBTP）和门控整体响度（LUFS，K 加权 + 双门，系数按素材采样率推导）。另含末尾 3 秒的短期响度与 EBU R128 响度范围（LRA）。另可一键归一化到 -23 LUFS（增益按峰值余量封顶，不削波，可撤销）。波形上另画有随时间的响度曲线。另可一键把真峰值压到 -1 dBTP（整段缩放，可撤销）。另有前瞻式动态限幅（逐样本增益，不让单个瞬态压低整段）。另有过采样域动态限幅（所需增益取自 4 倍重建，约束采样间峰值）。仍缺：真实听测。

- **第 6 节（网络）追加**：2026-11-20 arm64 lane 新增 online aspect 12 例、aspect replication 9 例和 replication fragment 12 例，统一选择达到三十一项。未修改 QEMU 树三项全通过，无嵌套工具或新增 skip；Snowflake 适配器/会话/TLS、core_app 网络驱动、QUIC 和生产部署仍为独立边界。

- **第 6 节（网络）追加**：2026-11-20 arm64 lane 新增 core_app network 单元 25 例与 offline 确定性/无网络符号契约，统一选择达到三十三项。`CORE_APP_RUNNER` 只启动 core_app，精确正则排除 loopback/voice/start-failure/net-transport；这些 Snowflake 场景与 QUIC 仍未覆盖，未计为跳过或通过。


- **运行时/架构验证追加**：2026-11-20 arm64 lane 新增 runtime_core 生命周期协调器 9 例与目标结构契约，统一选择达到三十五项。两项在未修改 QEMU 树直接通过，无新增 skip；runtime IO/reload/facade、Lua/ECS 和其他 arm64 子系统仍需独立覆盖。


- **运行时/架构验证追加**：2026-11-20 arm64 lane 新增 runtime facade 18 例、runtime IO 16 例、runtime reload/profiler 34 例，统一选择达到三十八项。未修改 QEMU 树三项全通过，无嵌套工具或新增 skip；Lua/ECS、编辑器/渲染和其他 arm64 子系统仍需独立覆盖。


- **ECS/实体系统验证追加**：2026-11-20 arm64 lane 新增 ECS 核心 45 例、系统调度 6 例、ECS snapshot/delta/AOI 35 例和 replication 目标结构契约，统一选择达到四十二项。未修改 QEMU 树四项全通过，无新增 skip；Lua、world streaming、编辑器/渲染和其他 arm64 子系统仍需独立覆盖。


- **脚本/Lua 验证追加**：2026-11-20 arm64 lane 新增九个 Stage 3 Lua 可执行测试与目标契约，共 126 个分项，统一选择达到五十二项。未修改 QEMU 树十项全通过，无新增 skip；LuaJIT、旧版 `test_script_lua` 兼容层、编辑器/渲染和其他 arm64 子系统仍需独立覆盖。


- **资源/热加载验证追加**：2026-11-20 arm64 lane 新增 async loader 17 例、hotreload 7 例、VFS 36 例和 filewatch backend 26 例，统一选择达到五十六项。未修改 QEMU 树四项全通过，无新增 skip；材质/场景纹理、glTF、world streaming 和真实 GPU 热替换仍需独立覆盖。


- **渲染/RHI 验证追加**：2026-11-20 arm64 lane 新增 RHI dispatch 44 项检查、capabilities 59 例、error contract 7 例、frame lifecycle 5 例和 render graph 22 例，统一选择达到六十一项。未修改 QEMU 树五项全通过，无新增 skip；运行时 rollout、WSI、shader 工具、真实 OpenGL/Vulkan 和画面一致性仍需独立覆盖。


- **诊断/远程调试验证追加**：2026-11-20 arm64 lane 新增 profiler 28 例、clock offset 8 例、trace core 15 例、trace merge 5 例及真实 trace_merge 工具契约，统一选择达到六十六项。`TRACE_MERGE_RUNNER` 仅启动目标工具，空参数 shell 路径也实际通过；实时远程会话、生产授权和其他 arm64 子系统仍需独立覆盖。


- **PAL/线程与任务验证追加**：2026-11-20 arm64 lane 新增 platform config 10 例、null-safety 1 例、fs-write 11 例、size-semantics 3 例、task 16 例和 task-singleton 1 例，统一选择达到七十二项。未修改 QEMU 树六项全通过，无新增 skip 或 X11 内容；窗口/WSI、移动设备后端和其他 arm64 子系统仍需独立覆盖。


- **物理验证追加**：2026-11-20 arm64 lane 新增刚体核心、replay、sync、hinge、cone-twist、identity、ragdoll、vehicle 八项共 135 例，统一选择达到八十项。未修改 QEMU 树八项全通过，无新增 skip。仍缺：跨架构物理确定性（x86-64 录制在 arm64 回放、跨架构 lockstep）的专门测试，以及 cloth/rope/soft-body/destructible/slider 的 arm64 覆盖。另：`test_physics` 是同组中唯一缺少 `LABELS "headless;physics"` 的测试，`ctest -L physics` 会漏掉它（既有问题，不影响 `-R` 选择）。


- **扩展物理验证追加**：2026-11-20 arm64 lane 新增 slider、cloth、rope、soft-body、destructible 五项和 character 30 例，统一选择达到八十六项，所有以物理模块为主体的已注册测试均纳入 arm64。仍缺：五个扩展模块各只有一个测试场景，首个失败断言会提前返回并遮住后续检查，汇总只报 1 例。
- **动画验证追加**：2026-11-20 arm64 lane 新增八项动画测试（73 个分项），统一选择达到九十四项。仍缺：GPU 蒙皮、跨架构逐位回放验证；locomotion、socket、aim 各只有单个用例。
- **AI 验证追加**：2026-11-20 arm64 lane 新增 `break_ai` 十四项，统一选择达到一百零八项。仍缺：真实关卡 navmesh、大规模群体性能、编辑器 AI 工具；nav follow、perception、behavior、steer 各只有单个用例。
- **音频验证追加**：2026-11-20 arm64 lane 新增二十三项音频测试（348 个分项），统一选择达到一百三十一项。仍缺：真实音频设备后端在 arm64 上的验证、core_app 语音通道与编辑器音频的 arm64 运行、跨架构逐位一致的 DSP 输出与真机实时期限。
- **规则引擎验证追加**：2026-11-20 arm64 lane 新增二十一项规则引擎测试（643 个分项），统一选择达到一百五十二项。仍缺：Redis 路径（`RULE_ENGINE_ENABLE_REDIS` 默认关闭，stream ext 中 10 例只打印 SKIP，643 例中有断言的为 633 例）、C11 并行执行器压力测试与 fuzz 的 arm64 运行、大规则集性能。
- **QEMU 偶发挂起记录**：`test_runtime_io` 的 fork 子进程在 qemu-user 下创建线程时于高宿主负载下偶发死锁（12 路并行 180 次中 5 次），原生不复现；待评估在 QEMU 用户态下改用不在 fork 子进程中起线程的等价断言。 2026-11-20 又在 `test_runtime_reload` 的同类用例（fork 子进程建 worker 线程后期待 abort）观察到一次；最小复现与 QEMU 上游 issue 358 复现程序均未触发，根因未定位。
- **arm64 lane 时间预算追加**：2026-11-20 外层守护由 300 秒放宽到 600 秒（实测 171 秒）。仍缺：`test_break_http` 在 QEMU 下比原生慢约 6 倍，若后续继续扩选，需要评估拆分 lane。
- **fork 子进程截止等待追加**：2026-11-20 两个 fork 后 abort 的用例改用 `tests/test_fork.h` 的 30 秒有界等待（io 例的阶段管道读与两例的 waitpid 都已限定），QEMU 挂起时会以本用例失败结束并给出诊断，不再拖垮整条 lane。根因仍未定位。
- **macOS Cocoa + MoltenVK 偶发构建失败记录**：最近 39 次 CI 中该 job 失败 4 次（`7ae28b5b`、`e1944152`、`753765ff`、`60aeae9d`），其中前三次都是 `clang: error: unable to execute command: posix_spawn failed: Resource temporarily unavailable`，即 `cmake --build build --parallel`（未限定并发数）在 macOS 15 runner 上耗尽进程资源；`60aeae9d` 那次是 `test_fork_deadline` 的 `snprintf` 声明问题，已修。待评估给该 job 的两处 `--parallel` 设定上限。
- **kernel/flow 验证追加**：2026-11-20 arm64 lane 新增 kernel 八项、kernel target 契约与 flow 三项（62 个分项），统一选择达到一百六十四项。仍缺：kernel actions/move/level 各只有一个用例；Flow 侧车格式的跨架构逐位一致性未验证。
- **无头 world 验证追加**：2026-11-20 arm64 lane 新增十五项 `headless;world` 测试（29 个分项），统一选择达到一百七十九项。仍缺：GPU 呈现（`*_gl`）与真实设备渲染的 arm64 验证；十项只有单个用例。
- **编辑器核心验证追加**：2026-11-21 arm64 lane 新增九个 `headless;editor` 可执行目标（doc/cmd/scene/components/viewport/gizmo/assets/i18n/scene_textures，共 177 个分项）和宿主目标契约，统一选择达到一百八十九项。原生全量 456 项零失败；非 root 干净容器中 arm64 189/189；远端 CI run 44852395640 的 arm64 job 136686557790 在提交 `819579b8` 上成功，原始日志严格断言确认九个分项计数、全部旧契约/e2e 和唯一既有 ptrace 设置跳过；主 CI 与独立 Windows D3D12 工作流均整体成功。仍缺：编辑器 shell/UI、音频编辑器、插件、Lua 集成、字体/平台设置、远程会话、GPU/窗口渲染和物理设备验证。
- **编辑器音频核心验证追加**：2026-11-21 arm64 lane 新增 `test_editor_audio`（23 个纯 CPU 分项），统一选择达到一百九十项。原生全量 456 项零失败；非 root 干净容器中 arm64 190/190；远端 CI run 44856764765 的 arm64 job 136700677779 在提交 `783482de` 上成功，原始日志严格断言确认音频及此前全部编辑器计数、旧契约/e2e 和唯一 ptrace 设置跳过；主 CI 与独立 Windows D3D12 工作流均整体成功。音频编辑器 shell/UI、真实设备、听感和跨架构逐位输出仍未覆盖。
- **编辑器插件核心验证追加**：2026-11-21 arm64 lane 新增 plugin cmds/host/sections/panels/manifest 五项（7/8/5/9/10，共 39 个纯 CPU 分项），统一选择达到一百九十五项。初版聚合写法触发 CTest 32 捕获组上限并返回零项，改为五个独立精确 alternative 后保持 31 组和严格集合差。原生全量 456 项零失败；非 root 干净容器中 arm64 195/195；远端 CI run 44860821764 的 arm64 job 136713543834 在提交 `07e0aec0` 上成功，原始日志严格断言确认全部旧计数、契约/e2e 和唯一 ptrace 设置跳过；主 CI 与独立 Windows D3D12 工作流均整体成功。动态库加载、CLI、shell/UI、Lua 集成和物理设备仍未覆盖。
- **Compose 核心验证追加**：2026-11-21 arm64 lane 新增 mycompose tree/remember/store/runtime/async 五项（28/8/27/8/17，共 88 个纯 CPU 分项），统一选择达到二百项。表达式维持 31 个捕获组上限，采用平铺精确 alternative。原生全量 456 项零失败；非 root 干净容器中 arm64 200/200；远端 CI run 44863859591 的 arm64 job 136723065162 在提交 `6d79959c` 上成功，原始日志严格断言确认全部 20 组计数、旧契约/e2e 和唯一 ptrace 设置跳过；主 CI 与独立 Windows D3D12 工作流均整体成功。Compose 与 myui 控件集成、C++20 对等层的 arm64 运行和 GPU 呈现仍未覆盖。
- **系统扩展与着色器 I/O 验证追加**：2026-11-21 arm64 lane 新增 break_cvar、break_xml、editor_flow、editor_image、shader_io 五项（12/13/3/7/59，共 94 个纯 CPU 分项），统一选择达到二百零五项。原生全量 456 项零失败；非 root 干净容器中 arm64 205/205；远端 CI run 44865662299 的 arm64 job 136728628102 在提交 `1323cfe7` 上成功，原始日志严格断言确认全部 25 组计数、旧契约/e2e 和唯一 ptrace 设置跳过；主 CI 与独立 Windows D3D12 工作流均整体成功。shader_io 主要是源码结构检查，不代表 GPU 或着色器编译器证据。插件动态加载、编辑器字体/设置/输入脚本和 shell/UI 仍未覆盖。
- **UI/渲染 CPU 路径验证追加**：2026-11-21 arm64 lane 新增 mycompose_myui、mycompose_widget_primitives、render_features、rt_trace、rhi_tlas_instance_encode、rhi_metal_format_mapping、input_extended 七项（18/7/4/2/2/5/21，共 59 个纯 CPU 分项），统一选择达到二百一十二项。原生全量 456 项零失败；非 root 干净容器中 arm64 212/212；远端 CI run 44867577433 的 arm64 job 136734595535 在提交 `351a5dfa` 上成功，原始日志严格断言确认全部 32 组计数、旧契约/e2e 和唯一 ptrace 设置跳过；主 CI 与独立 Windows D3D12 工作流均整体成功。单核输入变体、Vulkan 设备探测、GPU 渲染与光追硬件、真实输入设备仍未覆盖。
- **C++20 对等层验证追加**：2026-11-21 arm64 lane 新增 mycompose C++20 对等层四项、public API C++20 门禁、core-style 原型与 fork 截止等待辅助测试，统一选择达到二百一十九项。C++20 目标由 `aarch64-linux-gnu-g++` 编译，`test_mycompose_cpp20` 在 arm64 上检查真实 C/C++ ABI。`test_fork_deadline` 的故意超时标记由专用脚本限定，其他超时标记仍判失败。原生全量 456 项零失败；非 root 干净容器中 arm64 219/219，全部旧计数与契约通过。远端 CI run 44870376931 的 arm64 job 136743338509 在提交 `2891bc9b` 上成功，原始日志严格断言确认全部 36 组计数、旧契约/e2e、唯一 ptrace 设置跳过与限定的超时标记；主 CI 与独立 Windows D3D12 工作流均整体成功。qemu-user 下 fork 后建线程挂起的根因、GPU Compose 和编辑器 shell/Lua 仍未覆盖。
- **音频 PCM 流握手修复追加**：2026-11-21 arm64 QEMU 全量运行暴露 `test_voice_playback` 偶发 SEGFAULT。根因是混音读取与 close/set_hrtf 的存-读握手在 x86 宿主 qemu-user 下可重排（试金石 200000 次中 45322 次），close 因而释放仍在读取的环形缓冲。三处握手加入 seq_cst 栅栏，`test_audio_realtime_contract` 新增结构检查（先 RED 后 GREEN），QEMU 循环 400 次由 20 次崩溃降为 0。arm64 真机未测。
- **平台输入/窗口验证追加**：2026-11-21 arm64 lane 新增 platform_screen_simulated、platform_window_mode、pad_linux_feedback、pad_win_feedback_portable、win32_touch、wayland_touch 六项（3/14/3/4/4/4，共 32 个纯 CPU 分项，Windows/QNX 路径经假头文件编译），统一选择达到二百二十五项。原生全量 456 项零失败；修复音频握手后，非 root 干净容器中 arm64 225/225，全部 43 组计数与契约通过。远端 CI run 44873919545 的 arm64 job 136754291598 在提交 `f93cdbe7` 上成功，原始日志严格断言确认全部 43 组计数、旧契约/e2e 与唯一 ptrace 设置跳过；主 CI 与独立 Windows D3D12 工作流均整体成功。真实输入设备、合成器交互、单核亲和性变体与宿主 CMake 编译矩阵仍未覆盖。
- **RHI CPU 路径验证追加**：2026-11-21 arm64 lane 新增 rhi_rollout_log、rhi_runtime_select（49 项选择检查）、rhi_fault_injection（6）、rhi_wsi_attach（3）、rhi_golden_parity 五项，统一选择达到二百三十项。golden 比较在 arm64 与原生上的 MAE（0.33/0.64）完全一致。原生全量 456 项零失败；非 root 干净容器中 arm64 230/230，全部 45 组计数与契约通过。远端 CI run 44876090860 的 arm64 job 136760982706 在提交 `f894c566` 上成功，原始日志严格断言确认全部 45 组计数、golden MAE 与本地一致、旧契约/e2e 与唯一 ptrace 设置跳过；主 CI 与独立 Windows D3D12 工作流均整体成功。Vulkan 探测、GPU 设备、多后端符号形状和 arm64 真实渲染仍未覆盖。
- **编辑器/core_app 纯 CPU 组件验证追加**：2026-11-21 arm64 lane 新增 editor_input_script、editor_settings、editor_fonts、editor_audio_sink、core_app_mesh、core_app_runtime 六项（8/7/7/5/3/60，共 90 个纯 CPU 分项），统一选择达到二百三十六项。原生全量 456 项零失败；非 root 干净容器中 arm64 236/236，全部 51 组计数与契约通过。远端 CI run 44878718341 的 arm64 job 136769073389 在提交 `93239517` 上成功，原始日志严格断言确认全部 51 组计数、旧契约/e2e 与唯一 ptrace 设置跳过；主 CI 与独立 Windows D3D12 工作流均整体成功。字体真实系统用例在托管 runner 上找到 3 个候选（仓库自带两款加一款预装系统字体），不经 fontconfig；系统字体发现、core_app 语音通道与 lifecycle、编辑器 shell/Lua 与插件动态加载仍未覆盖。
- **插件/Lua/shell 验证追加**：2026-11-21 arm64 lane 新增 break_plugin（11，真实 arm64 共享库 `dlopen`）、editor_plugin_load（5）、editor_lua（37）、editor_shell（185）四项，统一选择达到二百四十项。试跑中发现一个纯本地 shell 用例误入 Snowflake 门控块，已移出并在非 Snowflake 构建中执行。原生全量 456 项零失败；非 root 干净容器中 arm64 240/240，全部 55 组计数与契约通过。远端 CI run 44881560470 的 arm64 job 136777765750 在提交 `e91bb19c` 上成功，原始日志严格断言确认全部 55 组计数；主 CI 与独立 Windows D3D12 工作流均整体成功。随后远程 CLI 参数解析用例也移出门控并改用临时目录，非 Snowflake 构建的 shell 增至 186 例。其余 47 个远程会话/网络面板用例（需 Snowflake）、插件 manifest CLI 与编辑器 GPU 呈现仍未在 arm64 覆盖。
- **跨平台可移植契约验证追加**：2026-11-21 arm64 lane 新增 glad_wgl_loader、platform_wsi_lifecycle（8）、d3d12_lifetime_hresult_contract（7）、net_loop_qnx（17）、qnx_perf_smoke（3）、break_plugin_unsupported（1）六项，统一选择达到二百四十六项。`test_core_app_assets` 经 `system()` 启动的宿主 shell 无法执行 arm64 烘焙器（未注册 aarch64 binfmt_misc，9 例失败），lane 不依赖宿主 binfmt 状态，因此排除。原生全量 456 项零失败；非 root 干净容器中 arm64 246/246，全部 60 组计数与契约通过。远端 CI run 44884540793 的 arm64 job 136786851930 在提交 `fa564267` 上成功，原始日志严格断言确认全部 60 组计数（editor_fonts 因上游新增用例为 8 例）；主 CI 与独立 Windows D3D12 工作流均整体成功。Windows/QNX/D3D12 真机行为、资产烘焙子进程与 Vulkan 表面 ABI 仍未在 arm64 覆盖。
- **core_app 生命周期 arm64 验证追加**：2026-11-21 生命周期驱动接入 `CORE_APP_RUNNER`（交叉模拟器，原生为空），十二个 `test_core_app_lifecycle_*` 真实进程测试进入 arm64 lane，统一选择达到二百五十八项。`LD_PRELOAD` 故障注入在模拟运行时显式跳过并打印 UNVERIFIED，只在原生 Linux 覆盖。原生全量 456 项零失败；非 root 干净容器中 arm64 258/258。arm64 上的故障注入、资产烘焙子进程与 core_app 语音通道仍未覆盖。
- **core_app 语音通道 arm64 验证追加**：2026-11-21 语音通道驱动接入 `CORE_APP_RUNNER`，`test_core_app_voice_lane`（fake 语音通道、帧计数、trace 确定性与 CLI 拒绝）进入 arm64 lane，统一选择达到二百五十九项。生命周期切片在远端 CI run 44889138925 的 arm64 job 136800898270 上以精确 258 项通过。原生全量 456 项零失败；非 root 干净容器中 arm64 259/259。生命周期切片所在提交 `3d83a1d3` 的主 CI 与独立 Windows D3D12 工作流均整体成功。真实音频设备与回声消除质量仍未在 arm64 覆盖。
- **资源包打包往返 arm64 验证追加**：2026-11-21 打包往返驱动接入 `TOOL_RUNNER`，`test_packer_roundtrip` 在 arm64 上经 QEMU 运行真实的 `packer` 与 `verify_pak`，统一选择达到二百六十项。原生全量 456 项零失败；非 root 干净容器中 arm64 260/260。运行时 VFS 挂载已由 lane 内的 `test_vfs` 覆盖；该测试不覆盖打包成功替换已有包的路径。
- **编辑器插件清单命令行 arm64 验证追加**：2026-11-21 清单命令行驱动接入 `EDITOR_RUNNER`，lane 构建 `editor` 并经 QEMU 运行 `test_editor_plugin_manifest_cli`（非法清单在开窗前以退出码 2 拒绝、合法清单报告条目），统一选择达到二百六十一项。原生全量 456 项零失败；非 root 干净容器中 arm64 261/261。远端 CI run 44893304171 的 arm64 job 136813548754 在提交 `db25a513` 上以精确 261 项通过，主 CI 与独立 Windows D3D12 工作流均整体成功。开启 `BREAK_EDITOR_PLUGINS` 后的开窗加载路径与真实窗口仍未在 arm64 覆盖。
- **arm64 lane 收尾结论**：2026-11-21 对 lane 外剩余五十项 headless 测试逐项归类：宿主契约、嵌套构建与符号检查、真实设备依赖、qemu-user binfmt 限制，以及实测通过但耗时 104 秒且依赖挂钟轮询的 `test_core_app_voice`，均不纳入 arm64 QEMU lane；lane 稳定在二百六十一项。
- **qemu-user fork 挂起复查**：2026-11-21 两个 fork 后建线程的 abort 用例已有 30 秒子进程截止等待；arm64 QEMU 下交替运行各 60 次 0 次挂起，根因仍未定位，保持监测。
- **第 9 节（物理）追加**：2026-11-21 x86-64 与 arm64 的物理结果已逐位一致：根因是 `fast_rsqrt` 在 SSE 平台用近似 `rsqrtss`，现在所有架构都用正确舍入的 `1.0f / sqrtf`，物理与数学源码另以 `-ffp-contract=off` 禁止 FMA 融合（否则 AppleClang 与 x86-64-v3 构建会得到不同哈希）；`test_physics_replay` 以金标准哈希守住，x86 与 arm64 CI 同时运行。仍缺：金标准场景不含旋转，libm 三角函数的跨版本/跨平台差异（`atan2f` 实测 1 ULP）尚未纳入；Windows/macOS 已由 CI 7e6fb69d 验证通过；并行 solver。
- **第 9 节（物理）追加**：带旋转的金标准用例（非零惯量与恒定角速度，240 步内 `sinf`/`cosf` 各调用 240 次）在 glibc 2.39/2.44 x86-64 与 glibc 2.39 arm64 上哈希一致，加入 `test_physics_replay`。仍缺：hinge、cone-twist、slider 约束（使用 `atan2f`，不同 glibc 间实测 1 ULP 差异）的跨平台金标准。
- **第 9 节（物理）追加**：物理角度改用确定性 `math_atan2f`（只用 IEEE 基本运算，最大误差约 3.2e-7 弧度），带限位铰链在 glibc 2.39 与 2.44 间由分歧变为逐位一致，加入第三个金标准。仍缺：`sinf`/`cosf`（四元数积分与软体创建）与载具的常量 `tanf` 仍来自平台 libm（已测环境与 CI 一致），并行 solver。
- **第 9 节（物理）追加**：新增宿主契约 `test_physics_determinism_contract`，在任何主机上阻止三类跨平台确定性回退（平台 `atan2f`、SSE 近似倒数平方根、缺少 `-ffp-contract=off`），弥补金标准只在特定 glibc 上失败的检测缺口。
- **第 9 节（物理）追加**：2026-11-21 物理改用确定性 `math_sincosf`（`quat_from_axis_angle`、软体创建），载具 `tanf` 改为字面量，物理代码不再依赖任何平台三角函数，源码契约同步禁止。上一条中的「`sinf`/`cosf` 与载具 `tanf` 来自平台 libm」由此关闭。仍缺：并行 solver；MSVC 若启用 `/arch:AVX2` 需补 `/fp:contract-`。
- **第 9 节（物理）追加**：2026-11-21 新增并行接触求解：按刚体岛分发到 job，世界统计按配对顺序重放，与串行逐位相同；BVH refit 改为批量，32k 刚体串行步长 10.5→3.6 ms。上文「并行 solver」中的接触部分由此交付。仍缺：距离/铰链等约束求解、积分与 refit 的并行；引擎主循环（`main.c`）尚未启用调度器；MSVC 若启用 `/arch:AVX2` 需补 `/fp:contract-`。
- **第 4 节（任务）追加**：2026-11-22 任务系统新增协作式取消：调用方持有 `TaskCancelToken`，`task_submit_cancellable` 提交的任务在令牌置位后不再执行 `fn`，但仍完成并释放依赖它的任务；运行中的任务可轮询 `task_cancel_requested`。见 [`docs/design/runtime_thread_model.md`](../design/runtime_thread_model.md)「任务取消」。上文「取消」由此交付。仍缺：跨帧 continuation、任务图可视化、工作窃取调优。
- **物理验证追加**：2026-11-22 cloth、rope、soft-body、destructible、slider 测试按场景拆为独立用例（共 17 例），单个场景失败不再遮住其余场景。上文「五个扩展模块各只有一个测试场景」由此关闭。
- **动画验证追加**：2026-11-22 locomotion、socket、aim 测试分别补到 5、4、5 例，覆盖插值区间、旋转变换、名字与关节校验、权重夹取和链越界跳过。上文「locomotion、socket、aim 各只有单个用例」由此关闭。仍缺：GPU 蒙皮、跨架构逐位回放验证。
- **AI 验证追加**：2026-11-22 perception、steer、behavior、nav follow 测试分别补到 4、5、4、5 例，覆盖视锥边界与三维角度、侧移方向与邻居上限、行为树短路与畸形树、路径跳点与不越界步长。上文「nav follow、perception、behavior、steer 各只有单个用例」由此关闭。仍缺：真实关卡 navmesh、大规模群体性能、编辑器 AI 工具。
- **kernel/flow 验证追加**：2026-11-22 kernel move、actions、level 测试分别补到 5、4、4 例，覆盖输入夹取与方向、多来源绑定与非法绑定、侧车格式与各类错误回滚。上文「kernel actions/move/level 各只有一个用例」由此关闭。仍缺：Flow 侧车格式的跨架构逐位一致性未验证。
- **kernel/flow 验证追加**：2026-11-22 `test_break_flow_serial` 新增序列化字节金标准（336 字节，固定 FNV-1a 哈希，再加载写出逐字节相同），x86-64 与 arm64 CI 都对它断言。上文「Flow 侧车格式的跨架构逐位一致性未验证」由此关闭。
- **无头 world 验证追加**：2026-11-22 time_of_day、decal、road、voxel、world_stream、vegetation、visarea、mesh_stage、world_stream_job 都补到 3~5 例，期间修复 `visarea_visible` 对 NULL 房间数组的读取崩溃。上文「十项只有单个用例」中九项由此关闭；`test_mesh_gpu` 的上传与绘制需要真实设备，保持单个无头用例。仍缺：GPU 呈现与真实设备渲染的 arm64 验证。
- **规则引擎验证追加**：2026-11-22 arm64 lane 打开 `RULE_ENGINE_ENABLE_C11_PARALLEL`，C11 并行执行器压力测试与 `rule_engine_fuzz_smoke` 在 arm64 上运行。上文「C11 并行执行器压力测试与 fuzz 的 arm64 运行」由此关闭。仍缺：Redis 路径、大规则集性能。
- **规则引擎验证追加**：2026-11-22 `rule_engine_bench` 新增 100/300/1000 条规则场景。冷加载与规则数成线性，热求值约为 n²（1000 条规则单次约 390 ms），原因是每次触发后重新求值全部已见规则。上文「大规则集性能」由此有了测量；仍缺：按读集增量重算以消除 n² 增长、Redis 路径。
- **规则引擎验证追加**：2026-11-22 议程已触发键改为哈希索引查找，1000 条规则单次求值由约 390 ms 降至约 225 ms，去重语义不变。仍缺：按读集增量重算、`retracted_root` 线性扫描事实、Redis 路径。
- **规则引擎验证追加**：2026-11-22 没有 retract 标志时跳过 retract 门控扫描，1000 条规则单次求值降至约 171 ms（最初约 390 ms）。仍缺：按读集增量重算、条件求值中的字符串分配、Redis 路径。
- **规则引擎验证追加**：2026-11-22 条件求值的帧栈与规则栈改为栈上内置数组，简单条件匹配不再分配堆内存，1000 条规则单次求值降至约 152 ms（最初约 390 ms）。仍缺：按读集增量重算、Redis 路径。
- **规则引擎验证追加**：2026-11-22 新增 CI lane `lane-rule-engine-redis`，以 libhiredis 构建原生 Redis 提供者，并对临时 redis-server 运行规则引擎测试（不允许任何 SKIP）。上文「Redis 路径」在 Linux 上由此关闭；仍缺：Windows/macOS 上的 Redis 路径、按读集增量重算。
- **第 4 节（任务）追加**：2026-11-22 新增跨帧 continuation 队列 `TaskFrameQueue`（到第 N 帧执行，可在 TaskSystem 上并行并支持取消）。上文「跨帧 continuation」由此交付。仍缺：任务图可视化、工作窃取调优。
- **第 4 节（任务）追加**：2026-11-22 任务系统新增每 worker 的执行、窃取与空闲睡眠计数及 inline 执行计数，为工作窃取调优提供测量。仍缺：窃取策略调优本身、任务图可视化。
- **规则引擎验证追加**：2026-11-22 recognize-act 循环实现按读集增量重算（默认开启，以 400 个随机程序的开关差分测试和评审反例守护），1000 条规则单次求值降至约 37 ms（最初约 390 ms）。上文「按读集增量重算」由此交付。仍缺：Windows/macOS 上的 Redis 路径。
- **第 4 节（任务）追加**：2026-11-22 任务系统新增可选的任务图追踪：定长日志记录每个任务的开始/结束时间、执行线程和依赖边，并导出为 Chrome trace 文档（每个 worker 一条轨道，依赖画成 flow 箭头）。见 [`docs/design/runtime_thread_model.md`](../design/runtime_thread_model.md)「任务图追踪与 Chrome trace 导出」。上文「任务图可视化」由此交付。仍缺：工作窃取策略调优。
- **规则引擎验证追加**：2026-11-22 `lane-rule-engine-redis` 改为矩阵，新增 macOS 15（Homebrew hiredis 与 redis，Metal 后端需要的 shaderc/spirv-cross 一并安装）。macOS 作业 136971379894 成功，`redis_roundtrip_when_service_available` 通过，测试输出中没有 SKIP。上文「Windows/macOS 上的 Redis 路径」中的 macOS 部分由此关闭；仍缺：Windows 上的 Redis 路径（Windows runner 没有现成的 Redis 服务）。
- **第 4 节（任务）追加**：2026-11-22 工作窃取改为按优先级窃取（先扫所有 worker 的高优先级队列），并且 worker 先取全局提交再弹本地队列，外部提交的高优先级任务不再被本地低优先级任务挡住。见 [`docs/design/runtime_thread_model.md`](../design/runtime_thread_model.md)「工作窃取的优先级策略」。上文「工作窃取调优」由此交付，第 4 节列出的任务缺口全部关闭。
- **第 9 节（物理）追加**：2026-11-22 刚体积分与积分后 BVH 叶子 refit 可在 `parallel_for` 上按刚体区间并行（默认至少 8192 个刚体，有醒着的 CCD 刚体时保持串行），与串行逐位相同；32768 个刚体每步 2.73 → 2.27 ms。见 [`docs/design/physics_extended.md`](../design/physics_extended.md)「并行积分与积分后 BVH refit」。上文「积分与 refit 的并行」中积分与积分后 refit 由此交付。仍缺：距离/铰链等约束求解与积分前 refit 的并行；引擎主循环（`main.c`）尚未启用调度器；MSVC 若启用 `/arch:AVX2` 需补 `/fp:contract-`。
- **第 9 节（物理）追加**：2026-11-22 引擎主循环（`main.c`）把 `TaskSystem` 交给物理世界作为并行调度器，并在销毁前解除，由源码契约 `test_main_physics_dispatch_contract` 守住。上文「引擎主循环（`main.c`）尚未启用调度器」由此关闭。约束求解不做并行：每个世界最多 `PHYSICS_MAX_CONSTRAINTS`（64）个约束，Gauss-Seidel 只迭代 4 次，派发开销大于收益；积分前 refit 只被 CCD 扫掠读取，而有醒着的 CCD 刚体时积分本就串行（见上一条）。仍缺：若约束上限提高到数千，需要按岛着色的并行约束求解；MSVC 若启用 `/arch:AVX2` 需补 `/fp:contract-`。
- **第 5 节（线程/消息）追加**：2026-11-22 Runtime Core 新增消息总线 `BreakRuntimeBus`（`engine/src/runtime/runtime_bus.h`）：带版本上限和 payload 预算的 kind 注册表，按 kind 把消息复制给订阅者各自的有界队列；队列满时丢弃该份并计数，发布者得到 OVERLOAD 而不会阻塞；可导出 kind、订阅者与队列计数组成的 JSON 拓扑。见 [`docs/design/runtime_message_model.md`](../design/runtime_message_model.md)「消息总线」。上文「统一 engine-wide event bus、背压策略和可观测的消息拓扑」中的总线本身、背压与拓扑由此交付。仍缺：把各线程域现有队列接入总线；按 kind 的优先级与配额。
- **第 5 节（线程/消息）追加**：2026-11-22 消息总线的 kind 支持 `control`（副本使用订阅者队列的预留控制容量，数据占满队列时仍能送达）和 `max_per_tick`（每个 tick 的发布配额，超出即 OVERLOAD 并计数）。见 [`docs/design/runtime_message_model.md`](../design/runtime_message_model.md)「按 kind 的优先级与配额」。上一条中的「按 kind 的优先级与配额」由此交付。仍缺：把各线程域现有队列接入总线。
- **第 17 节（大世界/流式）追加**：2026-11-22 `break_replication_core` 新增跨 cell authority 交接 `BreakCell`（`engine/src/network/break_cell_handoff.h`）：OFFER/ACCEPT/COMMIT/COMMIT_ACK/ABORT 五种消息，源在发送 COMMIT 前放弃权威，目标只在 nonce 匹配时接受，丢包、重复、乱序和延迟下任何时刻最多一个权威，交接中的写入随 COMMIT 送达。见 [`docs/design/cell_handoff.md`](../design/cell_handoff.md)。上文「跨分区 authority handoff」的协议核心由此交付。仍缺：cell 划分与负载均衡、跨进程传输接线、持久化、AoI 与客户端连接随交接迁移。
- **第 17 节（大世界/流式）追加**：2026-11-22 新增均匀网格分区 `BreakCellPartition`（`engine/src/network/break_cell_partition.h`）：把位置映射到行优先的 cell id，并按到当前 cell 的欧氏距离加滞后带决定何时发起 `BreakCell` 交接，边界抖动不会导致反复交接。见 [`docs/design/cell_handoff.md`](../design/cell_handoff.md)「分区」。上一条中的「cell 划分」由此交付（均匀网格）。仍缺：按负载拆分或合并 cell、跨进程传输接线、持久化、AoI 与客户端连接随交接迁移。
- **第 17 节（大世界/流式）追加**：2026-11-22 新增按负载分配 cell 的规划器 `break_cell_balance`（`engine/src/network/break_cell_balance.h`）：按 Hilbert 曲线排序后切成每台服务器一段，使最忙的服务器负载最小（与穷举结果一致），并以 `break_cell_balance_needed` 按阈值判断是否值得重新分配。见 [`docs/design/cell_handoff.md`](../design/cell_handoff.md)「按负载分配」。上一条中的「按负载拆分或合并 cell」由此以“按负载把 cell 分给服务器”的方式交付。仍缺：跨进程传输接线、持久化、AoI 与客户端连接随交接迁移。
- **第 17 节（大世界/流式）追加**：2026-11-22 新增 cell 交接的跨进程传输 `break_cell_link`（`engine/src/network/break_cell_link.h`）：`BreakCellMsg` 以带 HMAC-SHA256 的 UDP 数据报发送，接收方校验头部、对端与每个对端的重放窗口；发送方重启后序号从墙钟开始，正常走时的时钟可避免误判重放，时钟不可用时创建失败，倒拨场景不属于持久化保证。见 [`docs/design/cell_handoff.md`](../design/cell_handoff.md)「跨进程传输」。上一条中的「跨进程传输接线」由此交付。仍缺：持久化、AoI 与客户端连接随交接迁移、密钥轮换。
- **第 17 节（大世界/流式）追加**：2026-11-22 `break_cell_link` 支持不停机的密钥轮换（线格式版本 2 带 `key_id`，link 同时接受当前与上一个密钥，退役后拒绝旧密钥）。见 [`docs/design/cell_handoff.md`](../design/cell_handoff.md)「跨进程传输」。上一条中的「密钥轮换」由此交付。仍缺：持久化、AoI 与客户端连接随交接迁移。
- **第 17 节（大世界/流式）追加**：2026-11-22 `BreakCell` 支持崩溃恢复：快照包含所有记录和事务号、nonce 计数器，带哈希校验；配合 `hold_outbox` 和“先快照再 flush”的顺序，从最新快照恢复的 cell 不会再次拥有已交出的实体。见 [`docs/design/cell_handoff.md`](../design/cell_handoff.md)「崩溃恢复」。上一条中的「持久化」由此交付。仍缺：AoI 与客户端连接随交接迁移。
- **第 17 节（大世界/流式）追加**：2026-11-22 新增 `BreakCellView`（合并各 cell 的 AoI 报告，带宽限期，实体交接时客户端看不到 leave/enter）和 `BreakCellRoute`（按最高 epoch 把输入路由到当前权威 cell），见 `engine/src/network/break_cell_view.h` 与 [`docs/design/cell_handoff.md`](../design/cell_handoff.md)「可见性与连接随交接迁移」。上一条中的「AoI 与客户端连接随交接迁移」由此交付，第 17 节 cell 交接相关的缺口已全部关闭。
- **第 5 节（线程/消息）追加**：2026-11-22 第一个线程域接入消息总线：core_app 语音 worker 的设备事件以 control kind 发布到 `BreakRuntimeBus`，不再只能靠轮询计数器发现；总线新增 `break_runtime_bus_kind_matches`，多个组件共用一个 kind 时检查登记参数一致。见 [`docs/design/runtime_message_model.md`](../design/runtime_message_model.md)「语音设备事件接入总线」。仍缺：LogicThread、Task、Network/IO、PAL/MainLoop、Profiler 队列接入总线，core_app 主循环改为订阅语音事件。
- **第 5 节（线程/消息）追加**：2026-11-22 core_app 主循环改为从总线队列读取语音切换结果，不再逐帧比较计数器。上一条中的「core_app 主循环改为订阅语音事件」由此交付。仍缺：LogicThread、Task、Network/IO、PAL/MainLoop、Profiler 队列接入总线。
- **动画验证追加**：2026-11-22 `test_animation` 固定了分层混合（加法层、骨骼掩码、交叉淡入）的跨架构金标准哈希，动画采样与混合源码改为 `-ffp-contract=off` 编译，并由 `test_physics_determinism_contract` 检查。见 [`docs/design/animation_extended.md`](../design/animation_extended.md)「跨架构逐位一致的混合」。上文「跨架构逐位回放验证」由此对混合部分交付。仍缺：GPU 蒙皮；两骨骼 IK 仍使用平台 `atan2f`。
- **动画验证追加**：2026-11-22 两骨骼 IK 改用 `math_atan2f`，固定了跨平台金标准哈希；同时修复已弯曲的链在弯曲平面与 pole 不一致时末端偏离目标（最多 0.5）的缺陷。见 [`docs/design/animation_extended.md`](../design/animation_extended.md)「跨架构逐位一致的混合」。上一条中的「两骨骼 IK 仍使用平台 `atan2f`」由此关闭。仍缺：GPU 蒙皮。
- **第 5 节（线程/消息）追加**：2026-11-22 Profiler 与消息总线接通：总线的丢弃与拒绝以带 correlation_id 的 profiler 事件记录，Chrome trace 中可见背压发生在因果链的哪一步。仍缺：LogicThread、Task、Network/IO、PAL/MainLoop 队列接入总线。
- **第 5 节（线程/消息）追加**：2026-11-22 Task workers 接入消息总线：任务完成后由 worker 发布带 correlation_id 的完成通知，拥有者从自己的队列得知完成情况。见 [`docs/design/runtime_message_model.md`](../design/runtime_message_model.md)「任务完成接入总线」。仍缺：LogicThread、Network/IO、PAL/MainLoop 队列接入总线。
- **第 5 节（线程/消息）追加**：2026-11-22 IO workers 接入消息总线：每个 IO 完成都会在总线上发一条不含文件内容的通知。仍缺：LogicThread、Network、PAL/MainLoop 队列接入总线。
- **动画验证追加**：2026-11-22 GPU 蒙皮实际已实现（GL/Vulkan/D3D12 蒙皮顶点着色器、`skinned_pipeline`、关节矩阵 texel buffer），此前「仍缺：GPU 蒙皮」的记录有误。`test_vulkan` 新增 GPU 与 CPU（`lod_skin_positions`）的逐列像素对照，误差 1 像素以内，并用反向权重检查斜率方向。见 [`docs/design/animation_extended.md`](../design/animation_extended.md)「GPU 蒙皮与 CPU 参考对照」。动画验证的缺口由此关闭。
- **第 5 节（线程/消息）追加**：2026-11-22 Network 接入消息总线：`break_net` reactor 提供事件 hook（入队与丢弃都上报，不含负载），core_app transport 把每个网络事件以带 correlation_id 的 control 通知发布到总线，CoreAppThread 每个 tick 取空。见 [`docs/design/runtime_message_model.md`](../design/runtime_message_model.md)「网络事件接入总线」。仍缺：LogicThread、PAL/MainLoop 队列接入总线。
- **第 5 节（线程/消息）追加**：2026-11-22 PAL/MainLoop 接入消息总线：`runtime_mainloop` 观察器把主循环每帧读取的平台事实（尺寸、关闭请求、WSI 状态、缩放）的变化发布为 control 通知，编辑器主循环已接入。见 [`docs/design/runtime_message_model.md`](../design/runtime_message_model.md)「PAL/MainLoop 接入总线」。仍缺：LogicThread 队列接入总线；编辑器内的通知订阅方。
- **第 5 节（线程/消息）追加**：2026-11-22 LogicThread 接入消息总线：core_app 的 CoreAppThread 订阅 IO 完成通知，每个 tick 取空，并核对每条通知对应一次已完成的场景读取。见 [`docs/design/runtime_message_model.md`](../design/runtime_message_model.md)「LogicThread 订阅 IO 通知」。上文各条「仍缺：LogicThread …接入总线」由此对 core_app 交付。仍缺：C++ framework 的 LogicThread 消费总线；编辑器内的主循环通知订阅方。
- **第 5 节（线程/消息）追加**：2026-11-22 编辑器 shell 订阅主循环通知，渲染调试面板显示窗口尺寸、缩放、WSI 状态与关闭请求次数。见 [`docs/design/runtime_message_model.md`](../design/runtime_message_model.md)「编辑器订阅主循环通知」。上一条中的「编辑器内的主循环通知订阅方」由此交付。仍缺：C++ framework 的 LogicThread 消费总线。
- **资源/热加载验证追加**：2026-11-22 修复兼容 async loader 在完成发布后读取请求槽写日志的数据竞争，五类失败路径都先记录日志再发布完成。增强后的真实 burst 用例在修复前由 TSan 检出，修复后两个 CPU 上连续 100 次完整测试通过；TSan CI 不再排除 `test_async_loader`。详见 [`docs/design/runtime_asset_streaming.md`](../design/runtime_asset_streaming.md)「兼容 loader 的完成发布所有权」。


## 补充（2026-11-22）：第 5 节的 C++ framework IO 通知消费

`bk::RuntimeBusApplication` 与可选静态库 `common_runtime` 现已让 C++20 framework 的 `Init/Tick/DeInit` 生命周期消费 `BREAK_RUNTIME_IO_NOTICE_KIND`：应用借用总线，自有 64 槽（16 个 control 预留）队列，以 `framework.application.io` 订阅，并在 Tick 所有者线程回调 `OnRuntimeIoNotice`。调用方负责 IO attach/kind 注册、IO 生产者与全局 shutdown；总线必须比挂接关系长寿。Attach、失败重试、重复 Init 拒绝、畸形计数、先退订后销毁队列及幂等清理的完整契约见 [`docs/design/runtime_message_model.md`](../design/runtime_message_model.md)「C++20 framework 消费 IO 通知」，使用顺序见 [`docs/Build_Guide.md`](../Build_Guide.md)。

上文“C++ framework 的 LogicThread 消费总线”这一后续追加缺口由此对 IO notice 关闭，但不表示创建了新的线程，也不表示所有消息类型已经接入。`common_runtime` 使用 C++20；本文历史段落中的 C++11 仅为旧记录。根 `BREAK_FRAMEWORK_ENABLE_RUNTIME` 默认 OFF，默认 `empty` 仍无 `common_runtime`、`runtime_core` 或 `engine` 依赖，因此本项是显式可选能力，不是默认应用行为。

当前证据限于 `test_framework_runtime_bus` 的 9 个行为用例、focused CTest 3/3、根契约 1/1（四个子树）以及实现者记录的 focused ASan/UBSan/TSan 通过。完整 Vulkan/OpenGL、ASan 非图形套件、fuzz、Windows/macOS/其他生成器与远端 CI 尚待最终验收；不能据此把第 5 节全部线程/消息能力或全平台验收标记为完成。

验证补充（2026-11-22）：本项在 rebase 后源码上完成标准 Wayland Vulkan 453/453、OpenGL 451/451、ASan+UBSan 非图形 438/438、fuzz 14/14 与相关 TSan 6/6，未改变默认依赖边界。arm64、Windows、macOS 和远端流水线结果不由 Linux 本地证据推断，须以实际平台收据关闭对应验证缺口。

平台验证补充（2026-11-22）：本项的 arm64 QEMU 276/276、Windows MSVC/D3D12 远端作业、macOS Metal/MoltenVK 实机及两种根构建生成器均已取得实际通过证据；主 CI 为 24 成功、3 条件跳过、0 失败。Proton 仅按兼容通道记录，两个合同在无 GPU 时返回 77 跳过，不将其写成 GPU 通过。详见 `docs/Implementation_Status.md` 的 framework 总线远端与实机验收。

## 补充交付记录（2026-11-22）：第 14 节的 core_app 本地崩溃上下文

- **自动摘要缺口的部分关闭**：正式 `core_app` 现在可通过显式 `--crash-context DIR` 安装既有 `break_crash` 处理器，并把 RHI/GPU、网络计数和输入计数发布到 context-blob。它关闭的是上文“各子系统自动填写摘要”在这一应用内的缺口，不代表所有 engine、演示或编辑器已经接入，也不代表崩溃上传已成为产品能力。
- **默认与生命周期**：运行时默认 OFF；未传选项时不安装、不建 spool、不发布。start 在参数与网络配置校验后、`core_app_run` 前执行；随后先发布请求的 backend、`gpu=pending`、其余值归零的初始快照，`runtime_running` 后发布真实 tick 0，之后只在完整 tick 末尾发布。运行返回后 stop 恰好一次，先清 blob 再卸载，成功与失败都保留原运行结果。`BREAK_ENABLE_CRASH=OFF` 时选项明确 unavailable 并退出 2。
- **privacy allowlist**：只允许 `backend/gpu`、`live/seen/dropped`、`tick/keys/pads/touches/gestures/touch_status/haptic_status`。不包含原始按键码、文本、坐标、输入设备名、触摸来源 ID、网络地址、连接 key、session id、PSK 或数据包内容。快照仅在 `CoreAppThread` 上生成，字符串仅回调期间借用，无堆分配、跨线程采集或信号内发布。
- **无上传边界**：`core_app` 不链接 `break_crash_upload_http`，该选项只写本地捕获/spool，不上传记录。生产收集服务、上传者认证与运营保留策略仍是缺口。
- **真实证据**：原生 Linux 已验证第 2 帧 SIGABRT 的严格 `record/none/tick=1/keys=1` 和全部零计数、`runtime_running` 前 SIGABRT 的 `pending/tick=0/keys=0`，以及成功/失败退出时的 stop 与零 pending。focused CTest **7/7**、diagnostics **7/7**；compat/NM/config 为 **3 pass + 3 expected skip + 0 fail**。ASan/TSan 无 runtime 和 native preload 不可用均明确 77，UBSan 无额外 runtime 的强制路径完整执行并返回 0。
- **仍未交付/未验证**：Windows 仍是 start=false stub，非 Linux full-process 不声称捕获；ASan/TSan 插桩后的真实崩溃序列未运行。完整 Vulkan/OpenGL、ASan/UBSan 非图形与 fuzz、相关 TSan、root/default 契约、Windows/macOS/arm64 及远端 CI 尚待 Task 4 后续验收，本记录不预写成功或 run-id。

## 最终验收补充（2026-11-23）：第 14 节 core_app 本地崩溃上下文

本节是上一追加段“尚未验证”之后的证据更新，历史时点保持不变。

- **Linux 本地矩阵**：rebase 前 `acc3c5d2` 的 Vulkan/OpenGL 分别为 470/470、468/468（各 4 项条件 skip），ASan+UBSan 非图形 443/443（4 项条件 skip）+ fuzz 14/14，TSan 相关 8/8，两种根契约各 1/1。rebase 到 `33cc4be4` 后的 `321cf4f9` 的 Vulkan/OpenGL 资源交集各 3/3、core_app focused 7/7、ASan 资源/崩溃交集 7/7 + fuzz 14/14、TSan 资源与并发交集 9/9、两种根契约各 1/1；无冲突标记，双方追加内容均保留。
- **sanitizer 能力边界**：ASan 真实 full-process 已通过，真实 runtime 为 `libasan.so.8`/`libtsan.so.2`；ASCII 或空 ASan/TSan runtime 均在创建工作目录/进程前返回 77，UBSan 不需要额外 runtime。早期 sigaction 懒解析与 helper 去插桩只影响测试基础设施，`core_app` 保持插桩。TSan full-process 在本机 Fedora GCC 16/glibc 2.44 仍以 Lua longjmp CHECK 退出 66，未验证通过，等待 Ubuntu CI。
- **macOS ARM64**：中间 `0ddd` 的 Metal 全量 435/435、MoltenVK 修正 SDK 前缀后全量 438/438，各 5 项条件 skip（含 crash_context）；最终 `321cf4f9` 两套资源/diagnostics/lifecycle 交集各 7/7（crash_context 明确 skip）、graphics/gpu 各 6/6。MoltenVK 初轮因 Homebrew 顶层 include 符号链接发生 staging 失败，改用实际 `vulkan-headers`/`shaderc` 前缀后才通过，保留该失败历史。非 Linux 捕获仍不能据此声称。
- **仍缺外部验收**：Windows 实机、主 CI、windows-d3d12、由 `engine/CMakeLists.txt` 触发的 QUIC 和 Proton 待后续结果，不预写 run-id 或成功。Windows install=false stub、无上传接线及非 Linux full-process 不声称捕获的边界不变。

### Windows 实机补充（`321cf4f9`）

前述 Windows 实机待办已有结果：Windows Clang 的 D3D12 树构建成功，完整非图形 CTest 共 **425 项，4 失败、5 项条件 skip**，不能写成全套通过。diagnostics **7/7**（POSIX 用例只是占位，install=false stub 不是捕获证据）、runtime **65/65**；crash_build OFF、nested 契约通过，target、crash_context 按平台 skip；VFS、async loader、Runtime IO 分别通过。

`test_locked_dependencies` 首轮缺少 `ENGINE_LOCKED_DEPS_ALLOW_ABSENT=1` 失败，按 CI 环境设置后通过。平台 runtime 为 **20/26**，远程桌面窗口样式、最大化、全屏恢复失败；D3D12 UAV 交换链创建返回 `0x887a0022`，WARP 亦失败，warp_runtime 条件 skip，不声称 GPU 或交互桌面通过。

`test_scene_serial` 为 **121/122**，`failed_load_keeps_previous_scene` 中 `scene_load_binary(wd,&dst,pa)` 失败。scene 实现和测试从 `0ddd`、rebase base 到当前均无变化，故不是本分支改动引入；根因仍未关闭，记录为独立既有/平台问题，不谎称环境原因已证明，待 Windows CI 交叉核验。

主 CI、windows-d3d12、QUIC（因 `engine/CMakeLists.txt` 变更会触发）和 Proton 仍待，不预写 run-id 或成功。Windows install=false stub、无上传接线及非 Linux 捕获边界不变。

### 远端验收收据（`7fdcdfe318f43ce4f8620f0e455be795bb66e87b`）

[主 CI 45101195431](https://github.com/konyka/break/actions/runs/45101195431)：27 个矩阵作业，24 success、3 conditional skipped、0 failure；arm64 job `137452184436` 的 QEMU 选择套件 276/276，含 VFS、async loader、Runtime IO、core_app runtime。Ubuntu 24.04 TSan job `137452533153` 的 Configure/Build/Test (headless suite) 全成功，但无逐项 crash-context/BCR 日志，只称 TSan headless suite 通过，不伪造独立 SIGABRT/BCR artifact；Fedora longjmp 边界不变。

[windows-d3d12 45101195116](https://github.com/konyka/break/actions/runs/45101195116) 成功，Headless+contract、WARP floor、push-constant gate、Agility deployment、artifact upload 均成功；托管 Windows Clang 也成功。本机 scene_serial 单例失败仍未定位，本机全套不称通过。[QUIC 45101195104](https://github.com/konyka/break/actions/runs/45101195104) conclusion=success，但 `SNOWFLAKE_READ_TOKEN` 未配置，UNAVAILABLE、No test ran，四个场景未执行，不是 QUIC 测试通过。[Proton 45102712864](https://github.com/konyka/break/actions/runs/45102712864) 成功，上游 run-id=`45101195116`、artifact ID `14785842612`，device/pipeline contract 均 77，仅兼容通道，不是 GPU 或原生 D3D12 通过。

这些收据不属于本收据文档提交之后的工作流；新主 CI、windows-d3d12、Proton 待实际核验，不预写成功或 run-id。Windows install=false stub 与非 Linux 捕获边界不变。


## 补充（2026-11-23）：fork 截止等待清理与剩余边界

本次只关闭测试基础设施中的 waitpid 中断与错误所有权缺口。`test_waitpid_deadline(pid_t pid, int *status, unsigned timeout_ms)` 的签名和返回语义保持不变；EINTR 会重试，其他错误清零非 NULL 的 `*status`，并且只有 `pid > 0`、错误非 ECHILD 时才 kill/reap。原超时路径与符合条件的错误路径使用同一个私有清理 helper。

五个确定性注入覆盖正常退出前的 EINTR、超时前的 EINTR、EIO、ECHILD 和 PID 0。实际 RED 为五个旧用例通过、五个新用例失败，GREEN 为 **10/10**，focused CTest 为 **4/4**。fallback 必须经真实 `waitpid(..., WNOHANG)` 返回 0 确认存活后才发送信号，GREEN 的三个子进程用例均为 `cleanup=0`，所以 fallback 不能替代被测 helper 获得通过。ECHILD/PID 0 用例的 kill spy 仅作记录，不真实发送信号。

以下缺口保持打开：qemu-user 下 fork 后创建线程的挂起尚未解决；Windows scene 独立问题尚未解决。本地完整矩阵结果见下节；远端验收结果见下文收据。


### 本地完整验证补充（2026-11-23）

本地完整原生套件实测为 Vulkan **455/455**、OpenGL **454/454**，均 **0 失败**，且两套各有 **4 个既有平台条件 skip**；skip 不转换为执行通过。ASan+UBSan focused **4/4**、TSan focused **4/4**，仅表示四项 focused 测试在对应 sanitizer 下通过，不表示完整 sanitizer suite 已执行。

上述本地结果不关闭 qemu-user 下 fork 后创建线程的挂起或 Windows scene 独立问题；两项仍未解决。远端验收结果见下文收据。


### 远端验收收据（`3cbe982d`，2026-11-23）

以下收据属于 `3cbe982d341e42f6bc93afb618c1193a2aa3ea86`：[主 CI 45111186620](https://github.com/konyka/break/actions/runs/45111186620) 共 27 个作业，**24 success、3 conditional skipped、0 failure**；arm64 job `137483673104` 的 QEMU 选择套件 **276/276**，且 `test_fork_deadline` 实际编译并在 QEMU 中通过。[windows-d3d12 45111186576](https://github.com/konyka/break/actions/runs/45111186576) 成功。

[Proton 45112518778](https://github.com/konyka/break/actions/runs/45112518778) 成功，artifact 上游 run-id=`45111186576`，artifact ID `14789468602`；`device_contract=77`、`pipeline_contract=77`，仅表示兼容通道，不是 GPU 或原生 D3D12 通过。QUIC 未触发，不声称测试通过。

这些结果不关闭 qemu-user 下 fork 后创建线程的挂起或 Windows scene 独立问题，两者仍未解决。本收据提交还会触发新的工作流，待实际核验，不预写其结果。


## Scene 临时路径隔离后的剩余缺口（2026-11-23）

本次仅关闭 `failed_load_keeps_previous_scene` 的局部路径碰撞：Windows 旧 fixture 的 `pa`、`pb` 都为 63 字节且相同，保存 B 覆盖 A，造成第一次加载 A 失败及 **121/122**。提交 `c4c0d966` 将两者改为 512 字节，并在第一次 save 前加入路径相异断言；最终 Windows 完整 `test_scene_serial` **122/122**、Linux focused **4/4**。共享 `test_tmp`、产品代码和场景文件格式没有改动。

以下缺口保持打开：

- 共享 `test_tmp` 的截断整改尚未完成，局部 512 字节缓冲区不构成共享 helper 修复。
- qemu-user 下 fork 后创建线程的挂起尚未解决。
- 无关 Windows 平台/GPU 问题尚未解决，不能由本场景用例通过推断其状态。
- 完整 Vulkan/OpenGL 与 ASan+UBSan/TSan 矩阵、远端结果仍待执行和核验；此处不预写通过结论或运行编号。


### Scene 临时路径完整验证后的缺口（2026-11-23）

上一追加段的本地完整矩阵待验证状态已由实测更新：Vulkan **455/455**、OpenGL **454/454**，均 **0 失败**，各有 **4 个既有条件 skip**；ASan+UBSan focused **4/4**、TSan focused **4/4**。条件 skip 不计为执行通过，sanitizer 计数不表示完整 sanitizer suite。

Windows 在最终 `c4c0d966` 上取得完整 `test_scene_serial` **122/122**，以及 `test_runtime_io`、`test_runtime_reload`、`test_core_app_diagnostics` 各 **1/1**。

远端验收结果见下节。以下事项仍未解决：共享 `test_tmp` 截断整改、qemu-user 下 fork 后创建线程的挂起，以及无关 Windows 平台/GPU 问题。


### Scene 临时路径远端验收收据（`cb38913d`，2026-11-23）

以下结果属于 `cb38913d2a353193b3fd52a8b265570b80dba941`，不是本收据提交之后新触发工作流的结果。

- **主 CI**：[run 45117520898](https://github.com/konyka/break/actions/runs/45117520898) 共 27 个作业，**24 success、3 conditional skipped、0 failure**。
- **arm64**：job `137503639503` 的 QEMU 选择套件 **276/276**。scene 修复不在该选择中，本结果不覆盖 scene 修复。
- **Windows D3D12**：[run 45117520942](https://github.com/konyka/break/actions/runs/45117520942) 成功。
- **Proton**：[run 45119309958](https://github.com/konyka/break/actions/runs/45119309958) 成功；artifact 上游 run-id=`45117520942`，artifact ID `14792364601`。`device_contract=77`、`pipeline_contract=77`，仅表示兼容通道，不是 GPU 或原生 D3D12 通过。
- **QUIC**：未触发，不声称测试通过。

共享 `test_tmp` 截断整改、qemu-user 下 fork 后创建线程的挂起，以及无关 Windows 平台/GPU 问题仍未解决。

本收据提交还会触发新的工作流，待实际核验，不预写其结果或 run-id。


## fork 持续 EINTR 期限修复后的边界（2026-11-23）

上一波 EINTR 重试在持续中断时绕过超时计数。本轮改用 `CLOCK_MONOTONIC` 绝对截止时间，EINTR 和子进程仍运行都经过同一个期限检查；签名、返回语义、非 EINTR 错误所有权和 ECHILD/PID 0 防护不变。新增持续 200 ms EINTR、50 ms 期限用例，旧实现 **10/11**，修复后 **11/11**，且 fallback 均为 `cleanup=0`。两套 macOS 后端 focused 均 **4/4**，直接 ASan+UBSan **11/11**、无诊断；本机没有 LeakSanitizer 或本轮 TSan 通过结论。

仍保留以下边界：本修改只涉及 POSIX 测试 helper，不解决 qemu-user 下 fork 后创建线程的独立挂起，也不改变产品运行时；Windows/Linux 与远端矩阵须以各自实际结果为准。修复后最终本地完整矩阵：Metal 435/435、MoltenVK 438/438，各 5 项既有条件 skip（不计为执行通过）；未运行 TSan/LSan。

## 共享 test_tmp 截断缺口关闭与剩余边界（2026-11-23）

上文历史段落中的“共享 `test_tmp` 截断整改尚未完成”由本次追加所记录的整改关闭，历史时点保持不改。正常 `snprintf` 能完整写入时，路径字节保持原样；只有该最终格式化确认截断，才在原临时根下使用掩码后的 32 位 FNV-1a 哈希叶名。POSIX 根保持 `/tmp`，Windows 根保持规范化后的原 TEMP，不以替换根目录规避长度问题。

两个截断层都已加防护。Windows 的 `test_tmp` 和 `test_tmp_root` 在规范化后直接检查源字符串是否完整，溢出即输出 `TEST PATH TRUNCATED` 并 `abort()`。常规路径截断后的名称若含 `/` 或 `\` 会失败，避免哈希吞掉父目录；`cap < 32`、常规或回退 `snprintf` 的负结果、回退后仍然溢出，也都明确失败。Windows 动态容量使用 `R + 17 + P` 并 clamp 到 32，其中 `R` 为根长度、`P` 为 PID 位数；17 字节已包含分隔符、固定叶名前缀、八位哈希和 NUL，实际路径长度严格小于容量。

验证包含真实行为而非仅字符串形状：async 用例在文件 I/O 前核对叶名，写入已知字节后挂载临时根，经真实 VFS/async loader 请求该精确叶名并检查一次回调及其字节。两个 Windows 溢出探针分别覆盖 root/tmp 规范化入口，要求非零进程结果和截断标记，并有 30 秒进程超时；旧实现返回 0 时均为 RED，无标记崩溃不能冒充通过。

已取得的结果为 Linux fork **14/14**、async **19/19**、focused CTest **6/6** 和 mipmap/editor **2/2**；Windows scene **123/123**、async **19/19**、root/tmp 溢出探针 **2/2**，以及 mipmap、editor、runtime I/O/reload、diagnostics **5/5**。这些 focused 收据不扩展为完整矩阵或全平台结论。

以下缺口保持打开：

- 完整 Vulkan/OpenGL、ASan+UBSan、TSan 矩阵仍待实际执行，条件跳过必须在结果中保持可见。
- 远端工作流结果仍待核验，不预写通过结论或运行编号。
- qemu-user 下 fork 后创建线程的挂起尚未解决。
- 无关 Windows 平台/GPU 问题尚未解决，不能由上述临时路径测试推断其状态。


### 共享 test_tmp 完整验证后的剩余缺口（2026-11-23）

上一追加段的本地验证待执行状态由实测结果更新：Vulkan **455/455**、OpenGL **454/454**，均 **0 失败**，各有 **4 个既有条件 skip**；skip 不计为执行通过。ASan+UBSan focused **8/8**、TSan focused **8/8**，两项计数仅覆盖本次 focused 范围，不表示完整 sanitizer suite 已执行。

Windows scene **123/123**、async **19/19**，两个溢出探针通过；mipmap、editor、runtime_io、runtime_reload、core_app_diagnostics 均通过。共享截断场景仅说明 norm 溢出明确失败，不扩大其验证结论。

以下事项保持打开：qemu-user 下 fork 后创建线程的挂起仍未解决；无关 Windows 平台/GPU 问题仍未解决。远端结果待推送后核验，不预写 run-id 或成功结论。


#### 共享 test_tmp 紧凑路径远端收据（2026-11-23）

- 变基到 `234c3bbe` 后，最终提交 `a45ebe8e`（含 `a96c9e88` `test(temp): add compact paths for long temporary names`）已直接推送 `master`。变基后本地默认 Vulkan 全量 **462/462**、0 失败、4 个既有条件 skip；`test_fork_deadline` 合入上游 EINTR 用例后 **15/15**。变基后未重跑 OpenGL 与 sanitizer 树，此前结果来自变基前代码。
- CI run `45135178329`：completed/success，27 个 job 中 24 个 success，3 个按条件 skip（`lane-gpu-runtime-windows-d3d12`、Steam Deck 实机基准、Proton 参考 lane），skip 不计为执行通过。
- arm64：`Linux arm64 cross-build + QEMU tests (GCC)` 日志确认选择套件 **276/276** 通过，其中包含 `test_async_loader` 与 `test_fork_deadline`。
- windows-d3d12 run `45135178298`：completed/success。
- QUIC Weak Network run `45135178436`：completed/success（4 个独立场景）。
- Proton run `45137309048`：success，artifact 上游 run-id=`45135178298`（即本提交的 windows-d3d12），`device_contract=77`、`pipeline_contract=77`，仅表示兼容通道，不是 GPU 或原生 D3D12 通过。同 SHA 另一 Proton run `45135718032` 的上游为更早的 `45134413135`，不作为本提交证据。
- qemu-user 下 fork 后创建线程的挂起和无关 Windows 平台/GPU 问题仍未解决。本收据提交自身触发的工作流结果不在此预写。

## 第 10 节（音频）补充（2026-11-23）：延迟线与对齐器复位

`audio_delay_line_reset` 与 `audio_voice_aligner_reset` 已交付，设备重开或会话切换后无需销毁重建，复位后的行为与新建对象逐位一致。语音对齐器剩余缺口：sinc/交叉淡化配置、多声道，以及设备/VoiceProcessor/core_app/网络接线与真实声学验证。

## 第 10 节（音频）补充（2026-11-23）：对齐器 sinc 与交叉淡化配置

语音对齐器现在可选 sinc 延迟（自动扣除 8 帧固定延迟，输出总延迟仍等于测得延迟）和交叉淡化，淡化期间到达的更新被跳过并在下一周期重试。剩余缺口：多声道，以及设备/VoiceProcessor/core_app/网络接线与真实声学验证；core_app 语音泵仍使用默认线性、立即切换模式。

#### 延迟线复位与对齐器 sinc/淡化配置远端收据（2026-11-23）

- `e38b633a`（`feat(audio): reset delay lines and voice aligners`）：CI run `45142486616` completed/success，27 个 job 中 24 个 success、3 个按条件 skip（Windows D3D12 GPU lane、Steam Deck 实机基准、Proton 参考 lane），skip 不计为执行通过；arm64 QEMU 选择套件 **276/276**，含 `test_audio_delay_estimator` 与 `test_audio_voice_aligner`。windows-d3d12 run `45142486473` success；Proton run `45144037463` success，artifact 上游 run-id=`45142486473`，`device_contract=77`、`pipeline_contract=77`，仅表示兼容通道。
- `0e31707c`（`feat(audio): configure sinc and crossfade on voice aligners`）：CI run `45146038454` completed/success，24 success、3 个同样的条件 skip；arm64 **276/276**，含 `test_audio_voice_aligner`。windows-d3d12 run `45146038451` success；Proton run `45147666121` success，上游 run-id=`45146038451`，两项 contract 退出码均为 77，仅表示兼容通道。
- 同一提交更正 `docs/design/audio_extended.md` 两处过时的“自动更新调度”未做项：固定周期调度已由 `AudioVoiceAligner` 提供。本收据提交自身触发的工作流结果不在此预写。

## 第 10 节（音频）补充（2026-11-23）：core_app 语音泵可选对齐器模式

`CoreAppVoiceConfig` 可选 sinc 与交叉淡化，对齐器“core_app 接线”缺口中的模式配置部分关闭。剩余：CLI 开关、多声道、真实声学验证。

## 第 10 节（音频）补充（2026-11-23）：语音对齐器模式命令行开关

core_app 新增 `--voice-aligner-sinc` 与 `--voice-aligner-crossfade`，对齐器模式可从命令行开启并写入 trace。剩余：多声道与真实声学验证。

## 第 10 节（音频）补充（2026-11-23）：语音处理链可配置 bypass

`AudioVoiceProcessor` 可在创建时关闭 AEC/残余、频谱降噪、噪声门、AGC 中任意阶段，用于对照与排查。剩余：多声道、运行中切换（受频谱延迟约束未提供）、真实声学验证；core_app 语音泵尚未暴露该选项。
