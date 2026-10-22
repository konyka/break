# BW191 Inventory

## 简介

本文是跨引擎比较阶段 1 的 BW191（BigWorld Technology 1.9.1）inventory。目标是记录可由当前仓库材料确认的模块边界、能力和证据位置，不把引擎名称、目录存在或常见 MMO 设计升级为未经证明的运行时行为。本文只描述 BW191；与 Break 的对照仅用于定义比较边界，不表示对 Break 进行实现承诺。

BW191 的现有仓库证据是 [`docs/BW191_Architecture.md`](../BW191_Architecture.md)。该文档记载 BW191 为 C++ 核心、Python 脚本/工具，客户端面向 Windows、服务端面向 Linux，源码规模约 1,306 个 `.cpp` 文件；顶层分为 `bigworld/src/`、资源、文档、库和 FantasyDemo 等目录（来源：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §1-2）。除该文档明确列出的内容外，本文不推测版本内部实现、部署协议、平台覆盖或产品化运营能力。

## 证据口径

- **证据优先**：每个模块都按“范围 → 已知能力 → 证据/来源 → 与 Break 的比较边界”记录。
- **资料不足**：当前仓库材料没有明确确认的 API、运行时语义、线程模型、协议、部署能力或产品能力均标为 `资料不足`，不以“通常会有”补全。
- **来源层级**：本 inventory 的 BW191 事实主要来自仓库中的架构摘要；其中列出的原始路径（如 `bigworld/src/server/cellapp/`）是摘要中的定位线索，不等同于本仓库已包含或已逐行核验的 BW191 源码。
- **能力与集成分开**：目录、模块名、示例资源或架构描述只证明“文档声称存在/承担该职责”，不单独证明所有平台、运行配置或产品部署均可用。
- **统一顺序**：以下 17 个模块按阶段 1 设计固定顺序排列。后续 `feature_matrix` 和 `missing_capabilities` 应复用这些模块名。

## 17 个模块

### 1. 模块系统

- **范围**：引擎核心、客户端、服务端和公共代码的组织与加载边界。
- **已知能力**：文档将 BW191 分为 `bigworld/src/client/`、`bigworld/src/server/`、`bigworld/src/common/` 和 `egclient*` 客户端变体；服务端组件以独立进程形式组织，包括 Base App、Cell App、各自 manager、DBMgr、LoginApp 和 Reviver。文档还描述 `egclient` 到 `egclient4` 的递进式客户端入口。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.1-3.4（客户端、服务端、公共模块、精简客户端）。
- **与 Break 的比较边界**：可比较“客户端/服务端/公共层以及多进程服务划分”。BW191 的模块加载阶段、插件 ABI、热插拔实现和模块依赖解析细节为 `资料不足`；不要用 `bigworld/src/` 目录结构替代这些证据。

### 2. ECS / entity

- **范围**：实体创建、类型、生命周期、查询和实体逻辑承载方式。
- **已知能力**：客户端明确列出 `entity.cpp`、`entity_manager.cpp`、`entity_type.cpp`、`entity_picker.cpp`，职责包括实体创建、销毁、查询和类型管理。公共模块还列出 Python 实体绑定文件 `py_moo.cpp`。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.1 的“实体系统”表；§3.3 的 `py_moo.cpp`；§5 的 Python 脚本说明。
- **与 Break 的比较边界**：可比较“实体系统/类型管理”和脚本暴露。BW191 是否为严格 ECS、组件存储布局、系统调度、数据导向迭代、复制快照格式均为 `资料不足`；实体系统不能直接等同于 ECS。

### 3. World / scene

- **范围**：世界空间、场景组织、地图/空间加载和服务端空间分区。
- **已知能力**：`chunk_portal.cpp/hpp` 被描述为空间分块与入口/出口管理（室内场景）；服务端 Cell App 负责空间分区计算；FantasyDemo 资源包含 `maps/`、`spaces/`、`environments/` 等目录。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.3、§3.2、§4。
- **与 Break 的比较边界**：可比较“空间分块/Cell 分区和场景资源组织”。BW191 的 World 对象模型、场景图、可见性算法、跨 Cell 边界协议和加载时序为 `资料不足`；资源目录不能证明运行时流式加载行为。

### 4. Tasks

- **范围**：任务调度、后台作业、并行执行和工作线程抽象。
- **已知能力**：当前 BW191 摘要没有列出任务系统、调度器、job API 或 worker 线程实现。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §1-7 未给出可核验的 Task 模块或调度 API；因此状态为 `资料不足`。
- **与 Break 的比较边界**：不得因 BW191 存在多进程服务端就推断其有进程内 task scheduler，也不得将服务端组件并列当作 task API。线程池、任务依赖、优先级、取消和执行时序均为 `资料不足`。

### 5. Threads / messages

- **范围**：线程模型、进程间通信、消息队列、事件和跨线程所有权。
- **已知能力**：文档确认服务端由多个独立进程组成，并列出客户端/服务端公共的接口与连接代码；但未说明进程间消息格式、队列语义或线程所有权。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.2 的分布式服务架构；§3.3 的 `client_interface.cpp/hpp`、`login_interface.cpp/hpp`、`servconn.cpp/hpp`。
- **与 Break 的比较边界**：可比较“多进程服务及连接接口的存在”。具体 IPC/网络消息总线、线程亲和性、锁、队列容量、背压和事件顺序为 `资料不足`；不能把 `servconn` 文件名解释成某种消息协议。

### 6. Networking

- **范围**：客户端连接、登录、服务端通信、状态同步和网络扩展。
- **已知能力**：客户端列出 `connection_control.cpp` 和公共 `servconn.cpp`；服务端包含 LoginApp、BaseApp、CellApp、manager 和 DBMgr；公共代码包含登录接口、服务端连接管理；客户端过滤器用于实体位置/状态同步过滤，摘要明确提到客户端预测/插值语境。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.1-3.3、§7；§3.2 的服务端拓扑。
- **与 Break 的比较边界**：可比较“登录入口、分布式服务、实体同步过滤和连接管理”。BW191 的传输协议、可靠性、加密、认证后端、带宽预算、回滚算法、NAT/部署和真实 E2E 证据为 `资料不足`；“网络预测和回滚”在摘要的关键模式中被提及，但没有进一步 API 或测试证据，不能展开为完整实现结论。

### 7. UI / input

- **范围**：客户端 UI、字体、键盘/鼠标/手柄输入和 UI 脚本入口。
- **已知能力**：客户端应用模块包含 `gui_app.cpp`；FantasyDemo 有 `res/gui/`；脚本目录包含客户端 UI 交互和键位绑定；`bwvoip.cpp` 另列语音通信。CryENGINE 文档中的输入证据不属于 BW191，不能混用。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.1、§4、§5。
- **与 Break 的比较边界**：可比较“GUI 入口、GUI 资源和脚本键位绑定被文档提及”。UI 控件树、布局、渲染后端、输入设备枚举、焦点/捕获、手柄细节和跨线程规则为 `资料不足`。

### 8. Rendering / RHI

- **范围**：客户端渲染管线、图形 API 抽象、着色器、材质和渲染资源。
- **已知能力**：客户端包含 `device_app.cpp` 和 `camera_app.cpp`；FantasyDemo 资源包括材质、着色器、模型、环境、植被、粒子；架构摘要没有给出独立 RHI 名称或后端接口。顶层目录列出 DirectX redist，但这不能单独证明渲染器实现细节。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §2、§3.1、§4。
- **与 Break 的比较边界**：可比较“设备初始化入口和客户端渲染资源类别”。BW191 的具体图形 API、RHI 抽象层、渲染线程、管线/资源生命周期、shader 编译、GPU 能力查询和验证矩阵为 `资料不足`；不能将 DirectX redist 推断为固定 D3D 版本或完整 RHI。

### 9. Physics

- **范围**：刚体、碰撞、角色、车辆、布料和物理脚本接口。
- **已知能力**：公共模块列出 `py_physics2.cpp`，说明存在向 Python 暴露物理相关接口的文件；当前摘要没有列出物理核心实现或能力清单。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.3 的 Python 绑定表。
- **与 Break 的比较边界**：只能比较“存在物理 Python 绑定线索”。物理库来源、求解器、碰撞形状、角色控制器、车辆/布料、确定性和线程模型均为 `资料不足`。

### 10. Audio

- **范围**：音频播放、空间音频、语音、音频资源和设备后端。
- **已知能力**：FantasyDemo 有 `audio/` 资源目录，包含 `atmos/`、`fx/` 和 `ui/`；客户端核心模块列出 `bwvoip.cpp` 语音通信。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.1、§4。
- **与 Break 的比较边界**：可比较“示例游戏音频资源组织和 VoIP 文件线索”。音频设备 API、混音线程、3D 声场、编解码、FMOD 的实际接入方式和运行时验证为 `资料不足`；顶层 `fmod-redist/` 只证明发行包目录被记录。

### 11. Assets / hot reload

- **范围**：资源格式、加载、缓存、内容工具和开发期热重载。
- **已知能力**：FantasyDemo 资源按 characters、environments、maps、materials、objects、particles、scripts、shaders 等类别组织；`bigworld/res/scripts/common/` 和客户端脚本目录被明确列出；公共模块有 `doc_watcher.cpp/hpp`，职责为文档/配置热重载监听；`tools/cat/` 是资源查看/处理工具。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.3、§4、§5；§6 的 content tools/file grammar 文档目录。
- **与 Break 的比较边界**：可比较“资源分类、内容工具和文档/配置监听”。完整资产数据库、依赖图、导入/烘焙、运行时缓存、纹理/模型格式、增量重载一致性和热重载覆盖范围为 `资料不足`；`doc_watcher` 不自动等于全部资产 hot reload。

### 12. Editor

- **范围**：关卡/资源编辑器、内容创建工具、实时预览和编辑器到运行时的连接。
- **已知能力**：文档列出 `fantasydemo/tools/cat/` 资源查看/处理工具，`bigworld/doc/content_tools_reference_guide/` 内容工具参考，并在顶层结构中列出工具目录；未确认一个完整 editor 产品或其模块边界。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §2、§4、§6；§3.1 的 `LivePreview` 仅出现在 CryENGINE 部分，不属于 BW191，不能作为 BW191 证据。
- **与 Break 的比较边界**：可比较“内容工具和资源处理入口”。BW191 是否有场景编辑器、属性面板、多人协作、事务/撤销、PIE、远程编辑或 editor RPC 为 `资料不足`；不得把文档指南或 `tools/cat` 直接升级为全功能编辑器。

### 13. Diagnostics / remote debugging

- **范围**：日志、性能分析、监控、运行时诊断、远程观察和调试接口。
- **已知能力**：服务端工具目录明确列出 `message_logger/`、`watcher/`、`snapshot_helper/`、`bwmachined/`、`eload/` 等运维/监控/负载相关工具；`bigworld/doc/server_operations_guide/` 记录服务端运维文档目录。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.2、§6。
- **与 Break 的比较边界**：可比较“服务端运维工具和消息日志/监控名称被明确记录”。诊断数据格式、采集开关、远程调试协议、性能 trace、指标后端、权限和生产安全边界为 `资料不足`；工具名不证明具体协议或可用版本。

### 14. Crash upload

- **范围**：崩溃捕获、dump、错误报告、上传和服务端收集。
- **已知能力**：当前 BW191 架构摘要没有明确列出 crash reporter、minidump、上传客户端或错误收集服务。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) 全文未给出可核验的 crash upload 模块，故状态为 `资料不足`。
- **与 Break 的比较边界**：不得用 `reviver`（服务端故障恢复组件）或运维工具名推断客户端崩溃上传。崩溃格式、脱敏、重试、端点、保留策略和用户同意均为 `资料不足`。

### 15. Online update

- **范围**：补丁/热更新、版本检查、内容分发、回滚和在线服务升级。
- **已知能力**：顶层结构列出 web 接口（PHP/Python）和运维工具，但当前摘要没有明确在线更新、patch manifest、下载器或服务端滚动升级能力。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.2 的 `web/` 和 §6 的 `web_integration/` 文档目录；在线更新本身为 `资料不足`。
- **与 Break 的比较边界**：可比较“Web 集成/运维工具目录存在这一事实”。不得将 Web 接口等同于客户端在线更新、差分补丁、签名校验或回滚；这些均为 `资料不足`。

### 16. Security / anti-cheat

- **范围**：登录认证、授权、通信保护、反作弊、密钥和审计。
- **已知能力**：服务端拓扑包含 LoginApp；公共模块包含 `login_interface.cpp/hpp`；文档说明客户端登录入口连接到 LoginApp。当前摘要没有明确安全协议、加密实现或反作弊模块。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.2 的 LoginApp；§3.3 的 `login_interface.cpp/hpp`。
- **与 Break 的比较边界**：可比较“登录服务和登录接口被记录”。认证后端、令牌/会话、TLS、密钥生命周期、反作弊检测、篡改防护、权限模型和审计为 `资料不足`；LoginApp 的存在不证明安全能力已经闭合。

### 17. Large-world / streaming

- **范围**：大世界分区、空间流送、跨区迁移、LOD、场景边界和持续在线容量。
- **已知能力**：文档明确描述 Cell 分区：世界按空间划分为 Cell，由不同 CellApp 管理；`chunk_portal.cpp/hpp` 负责空间分块与入口/出口；客户端有自适应 LOD 控制器 `adaptive_lod_controller.cpp`；服务端以多个 CellApp 和 CellAppMgr 组织空间计算。
- **证据/来源**：[`docs/BW191_Architecture.md`](../BW191_Architecture.md) §3.1 的 LOD 和过滤器；§3.2 的 CellApp/CellAppMgr；§3.3 的 `chunk_portal.cpp/hpp`；§7 的 Cell 分区与自适应 LOD 关键模式。
- **与 Break 的比较边界**：可比较“服务端 Cell 分区、空间 chunk/portal 和客户端 LOD 线索”。具体流送触发条件、预取/卸载、跨 Cell 实体迁移、持久化一致性、容量指标和客户端大世界坐标策略为 `资料不足`；Cell 分区不自动等于客户端资产 streaming 完整实现。

## 与 Break 的比较边界

本文件的比较对象是 BW191 的文档可见架构摘要，不是一次 BW191 源码构建或运行验证。Break 侧若需进入后续矩阵，必须引用当前仓库的事实来源：[`docs/Implementation_Status.md`](../Implementation_Status.md)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md) 或具体 `engine/` 源码/测试路径。尤其应区分：Break 的 focused/test-only API 与正式 `engine`/demo runtime 集成（参见 [`docs/Implementation_Status.md`](../Implementation_Status.md) §“ECS Snapshot / Replication / AoI 边界”及网络适配器边界）；不能因为某个 Break 头文件、测试或设计文档存在就把它写成产品级能力。

对照时建议保持以下非对称边界：

- BW191 的“分布式服务架构”可与 Break 的网络/Session 设计比较，但不能把两者的服务部署、协议或生产规模互相推断。
- BW191 的实体、Cell、过滤器和脚本线索可与 Break 的 ECS、AoI、replication 和 Script 模块比较；BW191 的实体系统不应自动标为 ECS，Break 的 focused replication 也不应自动标为正式 multiplayer runtime。
- BW191 的资源、工具和 watcher 线索可与 Break 的 Asset/Platform 文件监视能力比较；两边都应把热重载的具体覆盖范围单独取证。
- BW191 的渲染和设备证据不足时，应保留 `资料不足`，不能用 DirectX redist 或资源着色器目录替代 RHI/runtime 证据。
- 对 crash upload、online update、security/anti-cheat 等产品系统，BW191 当前材料没有闭合证据，应在矩阵中明确标记 `资料不足`。

## 来源 / 限制

### 主要来源

1. [`docs/BW191_Architecture.md`](../BW191_Architecture.md)：BW191 版本、目录、客户端/服务端/公共模块、服务端拓扑、FantasyDemo 资源、脚本、文档和关键设计模式的仓库内架构摘要。
2. [`docs/Implementation_Status.md`](../Implementation_Status.md)：仅作为后续 Break 对照的当前状态来源；本文不从中推断 BW191 能力。
3. [`docs/Architecture_Overview.md`](../Architecture_Overview.md)：仅作为后续 Break 对照的架构边界来源；本文不从中推断 BW191 能力。

### 限制与未核验项

- 未在本次阶段 1 工作中构建、运行或逐行审计 BW191 原始源码；`docs/BW191_Architecture.md` 中的文件路径是当前仓库摘要提供的证据定位。
- 未核验 BW191 的完整 API、ABI、编译配置、平台矩阵、线程模型、网络线协议、数据库 schema、性能数字或线上部署操作。
- 未核验 BW191 的编辑器、crash upload、在线更新、加密/认证、反作弊和产品级服务能力；这些模块已按要求标为 `资料不足`，除非摘要有更窄的事实（例如 LoginApp 或 Web 目录）。
- `资料不足` 表示当前证据不足，不表示功能一定不存在；后续阶段若取得原始源码、官方手册或可复现运行证据，应逐模块补充来源并保留证据等级。
- 本文件只新增文档，不修改源码、CMake 或其他文档，也不包含提交操作。

## 附录 A：设计文档补充勘察（2026-10-22）

### A.0 证据范围变更

- 本次补充直接勘察了 BW191 的设计文档树：`/home/timeshift/opensource/game_engine/BW191/docs/design/`（共 10 个文件），并对照了 BW191 顶层源码布局（`bigworld/src/`、`src/lib/`、`src/tools/`、`fantasydemo/`）。协议版本以 `LOGIN_VERSION = 51` 为准。
- 文档清单：`README.md`（索引）、`00-概要设计.md`（进程拓扑/线程模型/登录与帧循环时序）、`详细设计/01-服务端详细设计.md`、`02-客户端详细设计.md`、`03-共享库详细设计.md`、`04-Mercury网络接口.md`、`05-实体系统.md`、`06-工具链与FantasyDemo.md`、`07-线程与渲染同步.md`、`附录/A-数据字典.md`、`附录/B-接口原型签名.md`。官方手册（HTML/PDF/CHM）在 `bigworld/doc/`。
- 已知源码缺口：`cellappmgr` 只有接口头与客户端代理桩（进程实现不在仓库）；`BgTaskManager` 的 `.cpp` 未随仓库提供，契约由头文件推断。
- 本附录将正文多个 `资料不足` 升级为“设计文档证据”；正文章节保留原样，以本附录为准的条目在各节标注“（升级正文第 N 节）”。

### A.4 Tasks（升级正文第 4 节）

- 客户端 `MainLoopTask` 框架：`MainLoopTasks::add(task, name, rules)` 按组排序执行（Device→VOIP→Script→Camera→Canvas→World→Flora→Facade→Lens→GUI→Debug→Finale），每组实现 `init/fini/tick/draw/inactiveTick`（证据：`02-客户端详细设计.md` §2）。
- 后台任务：`BgTaskManager`，优先级 0–128（MIN/LOW=32/DEFAULT=64/HIGH=96/MAX=128），仅 1 条 `BackgroundTaskThread` 做读盘/chunk 解析（证据：`07-线程与渲染同步.md` §3）。
- 服务端用 Nub 定时器（TIMEOUT_GAME_TICK/TRIM_HISTORIES/LOADING_TICK，证据：`01-服务端详细设计.md` §6.1）。

### A.5 Threads / Messages（升级正文第 5 节）

- 核心结论：客户端**没有独立渲染线程**；主线程同时承担输入、Python、Mercury 收发、全部 D3D 绘制。`Moo::g_renderThread` 是线程局部布尔量，仅 `createDevice` 所在线程为 true（证据：`07-线程与渲染同步.md` §1–2）。
- 服务端每进程一条 Mercury 主线程跑 Python；DBMgr 有 `WorkerThreadPool`（每线程一条 MySQL 连接）；BaseApp 有 `WorkerThread` 做文件流。
- 同步原语：`SimpleMutex/SimpleSemaphore/SimpleThread`（`cstdmf/concurrency.hpp`）；约定“锁内 swap 完成队列、锁外执行回调”，持锁期间不做磁盘/D3D/Python/Mercury send。Chunk 状态机：后台 `loaded` → 主线程 `bind` → `online` 才可绘制。

### A.6 Networking（补充正文第 6 节协议细节）

- Mercury 是基于 UDP 的可靠消息层：`Nub`（socket+定时器+接口表+select 循环）、`Channel`（可靠/有序流）、`Bundle`（多消息打包）、`Packet`（最大 1472 字节，Flags 含 IS_RELIABLE/IS_FRAGMENT/HAS_ACKS/HAS_CHECKSUM/INDEXED_CHANNEL 等）。
- 接口用宏声明（`BEGIN_MERCURY_INTERFACE`/`MERCURY_FIXED_MESSAGE`）；11 套接口（Login/BaseAppExt/Client/BaseAppInt/CellApp/BaseAppMgr/CellAppMgr/DB/Reviver/Bots/LoginInt）；实体方法占消息号 128–254。进程发现走 MachineGuard（bwmachined，MGMPacket）。默认端口：Login 20013、Watcher 20017、machined 20018（证据：`04-Mercury网络接口.md` §1、§3–13）。

### A.8 Rendering / RHI（升级正文第 8 节后端细节）

- Direct3D9 封装库 `moo`：`RenderContext`（设备/变换/灯光）、`Visual/Primitive`/动态 VB/IB、`ManagedTexture`、`ManagedEffect`/FX 编译、`RenderTarget`、`GraphicsSettings` 画质档、CPU 蒙皮（证据：`03-共享库详细设计.md` §8–10）。
- 单帧 draw 管线：DeviceApp 清屏 → Camera → World（ChunkManager.draw：Terrain、ChunkModel、SpeedTree、粒子、可选 Umbra 遮挡剔除）→ Facade（天空/水体/天气）→ Lens → GUI → Finale Present。Shader 可后台编译（`compileMutex_`），但 `finishInit` 必须在渲染所属主线程执行（`effectInitQueue_` 延迟队列）。
- 无多后端 RHI 抽象；DirectX redist 对应 D3D9 实现。

### A.9 Physics（升级正文第 9 节）

- 无独立刚体物理引擎（设计明确列为非目标）。客户端 `physics2` 库做世界三角碰撞/hull + Chunk obstacle；玩家本地预测由客户端 `Physics`（collide/jump/teleport）执行，服务器 `forcedPosition` 纠正，客户端回 `ackPhysicsCorrection`（证据：`00-概要设计.md` §10、§6.3；`02-客户端详细设计.md` §3）。
- 服务端 Cell 权威物理由 Controller 体系实现（Move/Navigation/Turn/Proximity 等 12 种 Controller），寻路靠 `waypoint` 导航网格（证据：`01-服务端详细设计.md` §6.3）。

### A.10 Audio（升级正文第 10 节）

- `fmod`/`fmodsound`（FMOD）与 `xactsnd`（XACT）双实现 + `sound` 抽象层；FMOD 混音线程由库内部创建，引擎侧听者定位在主线程 `DeviceApp::draw`；VOIP 走 `VOIPApp` 任务组与 Mercury `voiceData` 消息（证据：`03-共享库详细设计.md` §13；`07-线程与渲染同步.md` §1）。

### A.11 Assets / Hot Reload（升级正文第 11 节）

- `resmgr`：`BWResource` 单例多路径（`BW_RES_PATH`），`DataSection/XMLSection/BinSection/PackedSection` + `MultiFileSystem/ZipFileSystem/DataSectionCache`；后台加载走 BgTaskManager；禁止主线程同步读大文件（开发配置断言 `watchAccessFromCallingThread`）。
- 热加载：`BigWorld.reloadChunks`/`reloadTextures` 脚本 API。在线资源流：`Proxy::streamStringToClient`/`streamFileToClient` + `FileStreamingJob`（64KB 缓冲），客户端收 `resourceHeader`/`resourceFragment` 消息（证据：`03-共享库详细设计.md` §3；`02-客户端详细设计.md` §4–5；`01-服务端详细设计.md` §5.3）。

### A.12 Editor（升级正文第 12 节）

- WorldEditor（`src/tools/worldeditor`）：空间、地形、实体放置、UDO、chunk 保存，依赖 `ual/gizmo/guitabs/editor_chunk_item/bwlockd`；编辑器与游戏共用 Chunk 格式；`.def` 属性可标 `EDITOR_ONLY/Editable`。配套 ModelEditor、ParticleEditor、Max/Maya 导出器、res_packer、assetprocessor 等（证据：`06-工具链与FantasyDemo.md` §1；`05-实体系统.md` §2）。

### A.13 Diagnostics / Remote Debugging（升级正文第 13 节细节）

- 三层体系：① `Watcher`（`cstdmf`，`callWatcher` 消息，端口 20017；`tools/watcher`/deem 网关）+ DogWatch + stat_logger 性能入库；② Python 远程端口：BaseApp 40000+id、CellApp 50000+id（telnet `PythonServer`，仍是主线程 Nub 上另一个 fd）；③ `web_console`（Pylons Web 控制台：进程、日志、space viewer）+ `message_logger`（证据：`00-概要设计.md` §3/§9；`01-服务端详细设计.md` §8；`06-工具链与FantasyDemo.md` §2）。

### A.14 Crash Upload（补充正文第 14 节）

- 文档未专列章节，维持弱证据：`Reviver` 进程监视各管理进程 Birth/Death 并自动拉起；`src/lib/geh`（游戏异常处理库）与 `third_party/stack_walker` 提供崩溃栈支持；BaseApp 新式逐实体备份（`backupBaseEntity` hash 备份到其它 BaseApp）保证进程崩溃后 restore。
- 结论：有进程级故障恢复与栈捕获线索；无独立“崩溃上传客户端/服务端”设计，该子项仍 `资料不足`。

### A.15 Online Update（补充正文第 15 节）

- `DEFAULT_UPDATER_ENABLED=false` 默认关闭（`src/lib/server/common.hpp`），文档仅列为常量。相关机制：登录 `digest`（脚本/资源 MD5）校验不一致拒绝登录（`LOGIN_REJECTED_BAD_DIGEST`）；受控关闭分阶段支持滚动维护；res_packer 打包。
- 结论：仅有版本/摘要校验与受控关闭证据；无补丁下载/回滚设计，该子项仍 `资料不足`。

### A.16 Security / Anti-cheat（升级正文第 16 节）

- 登录链：客户端内置 LoginApp 公钥（v48 起不可从服务器拉取）→ `login` 包 RSA 加密 LogOnParams → 成功后用 `encryptionKey` 建 Blowfish 信道（v46 强制，v49 XOR 防重放，v51 不可靠包防重放）→ BaseApp `authenticate` 校验 SessionKey → 脚本 MD5 digest 校验。
- 外加：协议版本检查（LOGIN_VERSION）、登录限速（cachedLogins/systemOverloaded_）、`RateLimitMessageFilter`、外部信道拒绝 `FLAG_FIRST_PACKET` 滥用。Cell Real 权威物理 + 服务器 forcedPosition 纠正本身是反外挂基础（证据：`04-Mercury网络接口.md` §12；`00-概要设计.md` §1/§9）。

### A.17 Large-world / Streaming（补充正文第 17 节细节）

- 服务端分流：Space 切 Cell，CellAppMgr 负责几何 `updateBounds`、负载均衡（`informOfLoad` + `shouldOffload`，`DEFAULT_MAX_CPU_OFFLOAD=0.02`）、实体迁移（`convertRealToGhost` → 目标 Cell onload → `convertGhostToReal`）。`GHOST_DISTANCE=500m` 内建 Ghost。
- AoI：Real 实体的 `Witness` 维护可见实体缓存与带宽（默认 `DEFAULT_BANDWIDTH_TO_CLIENT=256 B/s`），`enterAoI/leaveAoI` + EventNumber 补洞；带宽优化：VolatileInfo 分级、DataLoD 最多 6 级、PackedXZ/XHZ/XYZ 压缩、IDAlias、相对位置。
- 客户端流式：`ChunkManager::tick` 扫描相机邻域 → 后台线程读 `.chunk/.cdata` → 主线程 bind/卸载远块（证据：`00-概要设计.md` §7.2/§7.4；`01-服务端详细设计.md` §6.2/§6.4；`05-实体系统.md` §3）。

### A.18 补充后的覆盖统计

- 升级/补充的维度：4、5、6、8、9、10、11、12、13、16、17 的细节；14、15 仅有弱证据，维持对应子项 `资料不足`。
- 证据等级为“设计文档明确记载 + 顶层源码布局对照”，不等于本工作区构建或运行过 BW191。
