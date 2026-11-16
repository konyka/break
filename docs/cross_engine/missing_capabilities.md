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
