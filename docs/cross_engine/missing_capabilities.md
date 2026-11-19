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
- **第 13 节（诊断/跨线程关联）追加**：`trace_merge --clock-offset SERVER_TRACE SERVER.json --session N PEER.json ...` 按会话从服务端 trace 读取每个对端的偏移（`break_trace_core_app_clock_offset_for_session`），用 `clock_offset_merge_shifts_many` 把服务端与所有对端放在同一时间轴上，「多个对端时只能手动指定 `--offset-us`」由此交付。仍缺：偏移只来自服务端探测；对端 trace 与会话号的对应仍需手动指定。
- **第 10 节（音频）追加**：空间 PCM 流可打开高度提示（`audio_pcm_stream_set_elevation_cue`，按声源与 up 向量夹角做频谱倾斜：上方高架提升，下方低通），「高度提示」由此交付。仍缺：HRTF、事件 voice 的高度提示、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 10 节（音频）追加**：空间事件 voice 也可打开高度提示（`AudioEventDesc.elevation_cue`），高度提示覆盖 PCM 流与事件两类声源，「事件 voice 的高度提示」由此交付。仍缺：HRTF、麦克风采集、感知编码器（Opus 等）、音频编辑工具。
- **第 15 节（在线更新）追加**：`break_http` 可回应代理的 Digest 质询（RFC 7616，MD5/SHA-256，qop=auth 或 RFC 2069 形式），在新连接上重发一次 CONNECT，「Digest 代理认证」由此交付。仍缺：NTLM、https 代理、OCSP、HTTP/2，发布二进制仍没有链接 `break_http`。
- **第 15 节（在线更新）追加**：`break_http` 支持强制 OCSP stapling（`require_ocsp_staple`）：握手时请求证书状态，要求附带的响应由叶子的签发 CA 或其委托 responder 签名、状态为 good 且在有效期内，「OCSP」中的 stapling 部分由此交付。仍缺：主动查询 OCSP responder、NTLM、https 代理、HTTP/2，发布二进制仍没有链接 `break_http`。
- **第 9 节（物理）追加**：`physics_sync` 提供增量修正包（"PSND"，相对双方已持有的基线快照只发送变化的字节区段，接收端在临时缓冲区重建并校验后原子恢复），「增量同步」的编解码部分由此交付。仍缺：core_app 保存每个对端的基线并选择增量或完整包、core_app 运行时作为客户端应用修正、并行 solver、跨平台确定性。
- **第 9 节（物理）追加**：core_app 为每个对端保存最近修正的基线，对端用匹配报告确认后，下一次修正改发增量包（loopback 本机 10644 字节对 28 字节），接收端 `physics_sync_apply_received` 统一处理完整包和增量包并维护自己的基线，「增量同步」由此在运行时接入。仍缺：core_app 运行时作为客户端应用修正、并行 solver、跨平台确定性。
- **第 13 节（诊断/跨线程关联）追加**：服务端认证行带 `session=`（`network_session result=authenticated session=S tick=N`），与 `network_clock_offset` 的会话号一致，驱动脚本验证两者对应。只看服务端 trace 就能列出会话和偏移，但对端 trace 自身仍不记录会话号，`trace_merge` 中对端文件与会话的对应仍需手动指定。仍缺：对端 trace 写入自己的会话号（需要服务端在认证后告知对端）。
- **第 13 节（诊断/跨线程关联）追加**：2026-11-17 服务端在认证后发送会话欢迎消息 `0x4005`（16 字节，`SESW` + 保留 + u64 会话号），对端由此得知服务端 trace 中自己的会话号；欢迎是对端认证后收到的第一条应用消息，`network_stats` 追加 `session_welcomes_sent`。见 [`docs/design/core_app_integration.md`](../design/core_app_integration.md)「服务端告知对端会话号」。「需要服务端在认证后告知对端」由此交付。仍缺：core_app 运行时本身不作为客户端运行，没有发布二进制把会话号写进对端 trace（目前只有测试客户端读取）。
- **第 14 节（崩溃上传）追加**：2026-11-17 Mach-O 读取器支持通用（fat）文件，`break_macho_symbols_open_cpu` 取指定 CPU 的 slice，符号库默认取 x86_64；条目逐个校验（越界、重叠、重复 CPU、slice 与条目 CPU 不符都拒绝）。见 [`docs/design/crash_symbolization.md`](../design/crash_symbolization.md) 第 2 节。「fat 文件」由此交付。仍缺：生产部署的收集服务、minidump、Windows 符号化、arm64 帧展开。
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
- **第 10 节（音频）/第 12 节（编辑器）追加**：2026-11-19 编辑器音频页支持波形缩放与滚动：`+`/`-` 以视图中心折半或加倍（下限 16 帧），`<`/`>` 移动视图长度的四分之一，波形列与刻度步长随视图变细。见 [`docs/design/audio_extended.md`](../design/audio_extended.md)「离线音频编辑」。「缩放」由此交付。仍缺：滚轮与键盘缩放、滚动条控件、播放时自动滚动、其他格式、VFS 与真实听测。
