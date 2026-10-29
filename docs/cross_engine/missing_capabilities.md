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
- **缺口、影响与后续：** Break 缺正式 runtime 的实体世界接入、schema negotiation、持久化/编辑器反射和 gameplay-facing API。后续阶段建议把 focused sources 纳入受控 runtime target，补实体生命周期、组件注册 ABI、序列化版本和真实 session/replication 链路。

### 3. 世界 / 场景

- **Break 现状：已具基础。** [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L133-L136) 将 ECS、Asset、Renderer 列为核心模块；RHI、相机、剔除、地形、水体和后处理在 renderer 目录中有架构定位。当前 snapshot/AoI 只证明确定性数据和可见性范围切片，不证明完整可编辑 world/scene runtime。
- **外部证据：** CryENGINE 的 3D 场景、sector、地形、遮挡裁剪在 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L47)；BW191 的 chunk/cell 空间模型在 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L110)；Unreal 的 `UWorld`、Actor 和 World Partition 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L20-L21)。三者的完整场景编辑、保存和跨版本迁移闭环：**资料不足**。
- **缺口、影响与后续：** Break 缺少被证实的场景资产编排、层级/关卡实例、世界保存与编辑器 round-trip。后续阶段建议先确定 world ownership、场景序列化格式、加载事务和运行时场景变更边界，再接流式系统。

### 4. 任务

- **Break 现状：已具基础 / 正式 runtime。** `engine/src/task/task.h` 定义 `TaskSystem`；架构文档说明 worker、外部提交和 `task_wait` 的线程约束（[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L438-L440)）。
- **外部证据：** Unreal 的 TaskGraph/UE Tasks 在 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L19) 和第 26 章有索引；CryENGINE、BW191 在当前参考资料中没有可核验的任务调度 API/调度策略：**资料不足**。
- **缺口、影响与后续：** Break 尚无证据覆盖优先级、取消、跨帧 continuation、任务图可视化和产品级工作窃取调优。后续建议补 task ownership/cancellation、fence/continuation 契约，以及诊断导出；不得把现有线程池基础误报为完整作业系统。

### 5. 线程 / 消息

- **Break 现状：已具基础；网络消息为 focused/test-only。** Task worker 与主线程边界见 `engine/src/task/task.h`；Session/adapter 的消息 view/copy、队列和 close watermark 见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L442-L480)。网络线程不直接访问 GameThread、ECS、Lua、UI 或 RHI。
- **外部证据：** Unreal 的线程、队列、消息、委托专题见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L42-L47)；CryENGINE/BW191 的通用消息总线、跨进程事件和线程模型：**资料不足**。
- **缺口、影响与后续：** Break 缺统一 engine-wide event bus、跨线程取消/背压策略和可观测的消息拓扑。后续建议制定消息所有权、序列化、队列容量、优先级与关停协议，并把 network/session 的局部队列接入统一诊断，而不是直接扩大共享状态。

### 6. 网络

- **Break 现状：focused/test-only。** `engine/src/network/break_net_{adapter,message,protocol}.{h,c}` 与 `break_net` 仅在 `ENGINE_BUILD_TESTS=ON && BREAK_ENABLE_SNOWFLAKE=ON` 时生成；真实 loopback 覆盖 inbound/outbound/close，Session 有 18-byte envelope，但 `engine_demo`/`dxx_break` 不链接它。证据见 [`docs/Implementation_Status.md`](../Implementation_Status.md#L50-L55)。
- **外部证据：** CryENGINE 有 CryNetwork、RMI、同步、预测/回滚的仓库参考描述，见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L147-L153)；BW191 有 LoginApp/BaseApp/CellApp、服务端连接和过滤器，见 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L52-L107)；Unreal NetDriver/Iris/复制见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L27)。具体可靠性、部署规模和运营工具：**资料不足**。
- **缺口、影响与后续：** Break 缺正式 socket/session 接线、认证后端、重连、预测/回滚、schema negotiation、超时/eviction scheduler、加密认证和服务端集群。后续建议先把 adapter 从 test-only 提升为显式 runtime 组件，再按认证、可靠传输、复制和服务端部署分阶段验收。

### 7. UI / 输入

- **Break 现状：正式 runtime（边界明确）。** `engine/src/ui/`、`engine/src/platform/` 提供 debug UI、字体、窗口、键鼠/手柄输入；架构文档列出 X11、Wayland、Win32、Cocoa 和输入能力（[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L125-L142)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L428-L436)）。
- **外部证据：** CryInput/CryFont 见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L163-L172)；BW191 的 GUI、输入和客户端脚本见 [`docs/BW191_Architecture.md`](../BW191_Architecture.md#L35-L50)；Unreal Slate/UMG/Input/IME 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L26)。完整 UI 编辑器、无障碍和输入重映射产品能力：**资料不足**。
- **缺口、影响与后续：** Break 的证据集中在 debug/UI 与平台输入，不足以证明完整 retained-mode UI、复杂文本、焦点/无障碍、输入配置资产和 UI 编辑器。后续建议先抽离正式 UI runtime 与 debug UI 的边界，再补布局/文本/焦点/输入映射的可部署契约。

### 8. 渲染 / RHI

- **Break 现状：正式 runtime。** `engine/src/rhi/` 的 compile-time single backend 模型、Vulkan/Metal/D3D12/OpenGL/headless 边界和 capability contract 见 [`docs/Architecture_Overview.md`](../Architecture_Overview.md#L125-L135)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L243-L295)。D3D12 仍有 MRT MSAA、cubemap FBO 等明确限制；Implementation Status 记录了 focused/WARP 和 GPU/runtime 证据及未实现项（[`docs/Implementation_Status.md`](../Implementation_Status.md#L57-L64)、[`docs/Implementation_Status.md`](../Implementation_Status.md#L107-L123)）。
- **外部证据：** CryENGINE RenderDLL/D3D9/NULL 与后处理见 [`docs/CryENGINE_Architecture.md`](../CryENGINE_Architecture.md#L69-L87)；BW191 客户端渲染能力只有概览级说明；Unreal RHI、RenderCore/RDG、Renderer 和 shader/DDC 见 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md#L22-L25)。BW191 的后端细节与跨平台性能等级：**资料不足**。
- **缺口、影响与后续：** Break 缺产品级渲染资产/shader 编译与缓存、完整 render graph、跨后端 feature parity、GPU crash recovery 和全平台 benchmark gate。后续建议优先收口后端能力矩阵、render-pass/资源生命周期和 shader pipeline cache，再扩展高级 renderer；不可将 headless 或 focused 像素测试等同于全部产品渲染能力。

### 9. 物理

- **Break 现状：已具基础；产品级未实现。** `engine/src/physics/` 在架构核心模块表中存在并声明刚体/角色控制方向（[`docs/Architecture_Overview.md`](../Architecture_Overview.md#L136-L139)），但当前状态文档没有足以证明完整 solver、车辆、布料、破坏和正式 gameplay 集成的统一 runtime 收据。
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
- **2026-10-30 补充：** 已交付：威胁模型（[`docs/design/security_threat_model.md`](../design/security_threat_model.md)）、`break_crypto`（OpenSSL EVP 封装，零自造密码学）、TLS 传输与 mTLS、CHALLENGE/AUTH-v2 HMAC 会话认证、握手级重放论证、admission 限速、每连接消息/字节限速（`break_session_manager_set_message_rate`，默认关闭）、应用消息防重放窗口库（`break_replay_window`，尚未接入：需先定协议，见 [`docs/design/transport_security.md`](../design/transport_security.md) §3）。仍缺：服务器权威实现、客户端反篡改（仅成本模型文档）、凭证 provisioning/轮换/吊销。

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
