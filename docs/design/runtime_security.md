# Runtime Security Design

## 1. 目的、范围与状态语义

本文是 Stage 2 的设计文档，不是实现报告。它把现有 ECS snapshot/schema/delta/AoI/replication/fragment 与 `break_net`/Session 的 target 边界正式化，并定义后续 Runtime Core（PAL、Thread、Task、Message、IO、VFS、Profiler）的安全边界。Stage 2 的选定顺序是：

1. 先将已有 focused API 的所有权、容量、失败和 target 边界正式化；
2. 再实现 Runtime Core 的平台、线程、任务、消息、IO、VFS、Profiler 合同；
3. 最后才允许 ECS/network 进入正式 runtime/session 集成。

状态词严格按以下含义使用：

- **当前已有**：源码和现有测试可以直接证明的行为；不等于正式产品集成。
- **focused/test-only**：源码存在且有专项测试，但仅由测试 target 编译或链接。
- **设计目标**：本文建议的接口、边界或验收标准，尚未实现。
- **未实现/风险**：明确不在当前交付范围，不能由本文推断为已有能力。

路线依据是 `docs/design/roadmap_2026-10-22.md:31-49` 和
`docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md:14-24`：Stage 2 当前仍是 design next，且要求先解决 focused ECS/network 到正式库的边界。本文不修改源码、CMake 或 target，也不声称已完成 Stage 2。

## 2. 真实现状与 target 证据

### 2.1 正式 engine target

根架构文档定义 `engine/` 为纯 C11 引擎层、`framework/` 为 C++ 应用框架层（`docs/Architecture_Overview.md:41-72`、`:102-110`）。实际 `engine/CMakeLists.txt:319-403` 的 `engine` static library 已包含 Core、Platform、Profiler、Time/Filewatch、Asset/VFS、ECS、Task、Lua script、普通 network 等源；但该列表没有 `world_snapshot.c`、`world_delta.c`、`replication_schema.c`、`break_aoi.c`、`break_replication.c`、`break_net_adapter.c`、`break_session.c` 或 `break_replication_fragment.c`。

因此，“ECS/Network 模块在目录中存在”不能写成“正式 runtime 已集成”。正式 target 的安全规则是：

- `engine` 只暴露经过稳定 C11 ABI 评审的 Runtime Core 与既有正式模块；
- focused 源在独立 target 验收前，不得被 `engine_demo`、`dxx_break` 或 `framework` 间接依赖；
- 不以复制源码到多个 executable 的方式制造第二套 ownership 语义。

### 2.2 focused/test-only target

真实 CMake 证据如下：

- `engine/CMakeLists.txt:3165-3179` 将 `test_ecs_replication` 直接编入 `ecs.c`、`replication_schema.c`、`world_snapshot.c`、`world_delta.c`、`break_aoi.c`；注释明确写着这些源不在 `engine` static library。
- `engine/CMakeLists.txt:3219-3233` 创建 test-only `break_replication_fragment` static library 和 `test_break_replication_fragment`。
- `engine/CMakeLists.txt:3235-3283` 只在 Snowflake 条件成立时创建 `break_net`，并将 adapter、protocol、Session、AoI、replication、fragment 编入其中；`test_break_net_adapter`、`test_break_replication`、`test_break_session` 链接该库。
- `BREAK_ENABLE_SNOWFLAKE` 还要求真实 `SNOWFLAKE_SOURCE_DIR` 和 `snow::net` target（`engine/CMakeLists.txt:291-308`）；不存在替代 transport。

当前 focused API 的边界在 `docs/design/ecs_snapshot_replication_aoi.md:5-20`、`docs/design/session_protocol.md:1-19`、`docs/design/snowflake_c11_adapter.md:1-17` 已有记录。本文沿用这些事实：fragment checksum 是 FNV-1a 完整性检查，不是加密认证；Session 不是 player authentication backend；`break_net` 仍是可选/test-gated 集成。

## 3. 威胁模型与安全目标

### 3.1 保护对象

Runtime Core 保护的是进程内的 ownership、边界内存、线程状态、队列资源、文件访问范围、诊断数据和可验证的网络消息完整性。它不把客户端视为可信 authority，也不承诺防止有本地代码执行能力的攻击者修改进程。统一生命周期、容量和错误契约仍是设计目标/未实现；本文件不把安全边界写成已有 Runtime facade。

### 3.2 主要威胁

- 恶意或损坏的网络 envelope、fragment、schema、tick、sequence、长度和连接事件；
- 队列、fragment reassembly、VFS 文件、Profiler 元数据造成的资源耗尽；
- callback/worker 线程越权调用 World、ECS、Lua、UI、RHI 或 Session；
- shutdown 与 callback/IO/task 并发导致 use-after-free、double destroy、泄漏或永久阻塞；
- 路径穿越、mount 越界、PAK 元数据溢出或大文件分配；
- 把调试 trace、路径、peer 信息或用户数据无意写入不受控导出；
- 误把 checksum、sequence 或 schema hash 当作身份认证、保密或服务器权威。

### 3.3 不在本文承诺的安全能力

Stage 5 才设计 signed manifest/content-addressed update、transport authentication、replay protection、rate limit、crash upload、anti-tamper 和 server authority（`docs/design/roadmap_2026-10-22.md:91-107`）。本文只规定 Runtime Core 必须留下可接入这些服务的边界；不实现、不模拟、不用 FNV-1a 冒充密码学认证，也不提供默认 remote debug 或 unsigned update 路径。

## 4. 语言、ABI 与分层边界

### 4.1 C11 Runtime Core

Runtime Core 的公共实现语言为 C11，与架构文档 `docs/Architecture_Overview.md:188-217` 一致：显式分配/释放、opaque pointer、返回值/错误码、slice（指针+长度）、无异常。公共 C ABI 规则：

- 所有输入长度使用项目 `usize`（定义见 `engine/src/core/types.h`），先做加法和乘法 checked arithmetic；
- borrowed view 不取得所有权，owned object 必须有对应 release/destroy；
- 句柄/API 不暴露 pthread、Snowflake、RHI backend 或 C++ 类型；
- formal facade 的错误返回统一映射为 `BreakRuntimeError`：`OK`、`INVALID`、`CLOSED`、`OVERLOAD`、`OOM`、`TIMEOUT`、`STALE`、`REJECTED`、`FAILED`；compatibility API 的 `OVER_LIMIT`、`SHUTDOWN`、`OUT_OF_MEMORY`、`AUTH/INTEGRITY` 等名称只在原边界保留，不得用“成功但丢弃”隐藏失败；
- 失败路径保留调用者可重试的旧状态；提交式 mutation 使用 staging + validate + atomic replace。

### 4.2 C++11 framework/application

`framework/` 只管理应用生命周期和 C++11 面向对象封装，不取得 C11 Runtime Core 内部结构的直接写权限。框架通过 C opaque handle、命令、快照和 fence 调用 C11 层。C++ 异常、RAII 和 STL 容器不得穿过 C11 公共 ABI；异常应在 C++ 边界转为错误码并完成 C 资源释放。UI/window API 仍只在其所属主循环线程执行，跨域操作排成 command。

### 4.3 Lua

Lua 是唯一计划中的 runtime scripting language（roadmap `:5-6`）。当前 `script_lua.c/.h` 已在正式 `engine` 源列表中，但稳定 `BreakLuaRuntime` facade、reload policy 和安全绑定尚未交付（roadmap `:51-68`）。设计边界为：

- Lua VM 由一个明确的 Script/Game owner 线程独占；worker/network/PAL 不直接进入 VM；
- Lua 只消费受限 command/snapshot/query facade，不获得 World 指针、RHI 原生句柄、Snowflake connection、VFS host FILE* 或 allocator internals；
- Lua callback 的预算、错误、stack、GC 和 reload 失败必须转成 Runtime 错误，不可跨线程抛出或回调 gameplay；
- Lua runtime 的 normal/ASan/TSan 验收是 Stage 3 依赖，不因当前 `script_lua.c` 存在而提前宣称完成。

## 5. 现有 ECS/network 边界正式化

### 5.1 World、schema、snapshot、delta

**当前已有/focused：** `replication_schema.*`、`world_snapshot.*`、`world_delta.*` 的行为见 `docs/design/ecs_snapshot_replication_aoi.md:7-18,45-78`。GameThread 独占可变 World、ECS 结构、schema 和 delta apply；snapshot 是拥有 bytes 的不可变对象，实体身份含 `(index,generation)`；delta 在 immutable snapshots 间 diff，并通过 ECS-owned deep clone/staging、最终验证和 atomic replace commit 应用，失败时原 World 不变。

**安全设计目标：**

- schema registry 初始化/GameThread-owned，不在热路径隐式加锁；schema hash 变化即切断旧 delta stream，直到未来 schema negotiation 明确允许；
- snapshot build 只能在调用方已经完成 structural barrier 后执行；builder 不偷偷建立 barrier；
- snapshot publication 未来由一个明确 owner 的 current-snapshot service 负责 retain/release；在该 service 实现前，调用方必须持有已返回 snapshot；
- delta apply 只接受单调 tick、匹配 base/schema、经过完整校验的 payload；不接受“尽力应用”或半更新；
- pointer-containing/non-deterministic raw component 不得走 raw bytes schema；资源引用、派生 cache、RHI/Scene 指针必须使用未来显式 encode/decode contract。

**未实现：** 正式 engine library/session integration、wire schema/tick fields、schema negotiation、authority handoff、prediction/rollback 和 mutex-protected publication service。不能把 `test_ecs_replication` 的通过写成正式网络安全证明。

### 5.2 AoI、Real/Ghost 与 replication

**当前已有/focused：** `break_aoi.*` 有空间网格、sphere/AABB、多个 Witness、owner/always-relevant/dormant、hysteresis 和确定性 `enter/stay/leave`；`break_replication.*` 有 Real/Ghost baseline、dirty、destroy/dormant、预算和 overload retry。证据见 `docs/design/ecs_snapshot_replication_aoi.md:80-98`。

**安全设计目标：** AoI 只产生 bounded、排序稳定的候选/记录；connection scope 与 Ghost map 归 GameThread owner；网络线程不能直接改变 scope 或 Ghost。版本到 `UINT64_MAX` 时 fail-closed，不能 rollover 或释放旧 payload 后重试。带宽或 outbound overload 返回可观察结果，未发送 baseline/dirty 留待后续 sync，而不是假报 sent。

**未实现：** distributed Cell、持久跨 World NetEntityId、authority handoff、客户端预测/rollback 和 server-authoritative policy。

### 5.3 Fragment/reassembly

**当前已有/focused：** `engine/src/network/break_replication_fragment.h:20-59` 定义 delta/base ID、fragment index/count、checksum、owned reassembler output、reset/destroy；当前总重组预算为 16 MiB，transport payload 上限为 64 KiB，且支持乱序、精确重复与冲突拒绝（`docs/design/ecs_snapshot_replication_aoi.md:134-146`）。

**安全设计目标：** reassembler 必须在元数据分配、单片拷贝和 total-size 累加前检查上限；每个 connection/stream 只允许有界 assembly 数和总字节数；外部 scheduler 负责 deadline/eviction，过期必须 reset 并计数；完整重组后仍须在 GameThread 做 base/schema/delta validation，fragment layer 不调用 World 或 Snowflake。

**未实现：** 当前 focused API 没有 timeout/eviction scheduler，也没有 cryptographic MAC/AEAD。FNV-1a 只能发现传输损坏/错误重复，不能证明来源、抗篡改或保密；正式接入前必须由 Stage 5 transport security contract 提供认证。

### 5.4 break_net 与 Session

**当前已有/focused：** `BreakNetReactor` 是 C11 opaque adapter，Snowflake 负责 socket、connection、readiness、transport queue；Break 负责 lifecycle、driver、状态同步、bounded view/copy/release。`engine/src/network/break_net_adapter.h:21-73` 明确了 thread/step drive、256 event queue、256 outbound queue、256 identity capacity；`docs/design/snowflake_c11_adapter.md:73-103,201-228` 定义单 driver、stop deadline、timeout 后保留 live resources 的语义。

网络 callback 只能验证、复制、入队；不能调用 GameThread、Session、World、ECS、Lua、UI 或 RHI。Session 是 GameThread-only，状态为 `NEW -> AUTHENTICATING -> AUTHENTICATED -> CLOSING -> CLOSED`，queued event/payload ownership 见 `docs/design/session_protocol.md:21-37,40-84,164-187`。

**容量与 backpressure：** event/outbound 队列满必须显式失败或丢弃并计数，不能 callback 阻塞；send 满返回 `BREAK_NET_SEND_OVERLOAD`，closed state 返回 `BREAK_NET_SEND_CLOSED`；GameThread 下一次 poll/sync 再决定 retry/drop。固定 256 是当前 adapter contract，不应被设计文档扩大解释为系统全局连接容量。

**shutdown：** thread mode 先 terminate Snowflake，等待 adapter-owned `host_exited` deadline，确认退出后 join，再 destroy Snowflake reactor，最后发布 stopped；timeout 返回 false 且保留 `STOPPING` 和所有 live ownership，后续 stop 可继续。step mode 由唯一 caller 驱动并拒绝并发 step。

**未实现：** player authentication backend、真实 credential/key lifecycle、Session 与 ECS replication 的正式 runtime integration、Lua gameplay callback、editor RPC、online update 和额外 security 功能。默认 AUTH/PING registry 允许协议测试流转，不等于身份认证。

## 6. Runtime Core 设计目标

### 6.1 PAL 与线程

**当前已有：** `engine/src/platform/` 已有 time、filewatch、window/input 等平台实现；`engine/src/core/platform_thread.h` 是 Task 所用平台线程抽象；架构文档 `docs/Architecture_Overview.md:438-440` 已记录 UI 主线程、Task worker 和 `task_wait` worker self-deadlock 边界。

**设计目标：** PAL 只暴露稳定、可测试、fail-closed 的 C11 contract：线程 create/join/detach（默认禁止 detach）、mutex/cond/atomic wait、monotonic deadline、文件 descriptor/socket 等 opaque handle。所有 API 明确 owner 和调用线程。禁止在持有 Runtime lifecycle lock 时调用可能回调用户代码、阻塞无限期或进入 Snowflake 的函数。

线程角色最小集合：Game/Main owner、Render owner、IO owner、Network driver、Task workers、Profiler registration caller。线程注册表只记录 opaque identity 和 shutdown epoch；不允许借线程 ID 推断 World ownership。跨线程交互只用 owned message、bounded queue、immutable snapshot 或 fence。

### 6.2 Task

**当前已有：** `engine/src/task/task.h:39-93` 定义每优先级 Chase-Lev deque（容量 1024）、external submit queue（容量 256）、worker 数、running 状态和单进程单实例约束；`:109-147` 规定 worker 内禁止 `task_wait`/`task_wait_handle`，避免 self-deadlock。Task 已编入正式 `engine` target，但本文不改变其源码契约。

**设计目标：** Task API 必须区分 submit overload、shutdown rejection、invalid dependency 和 execution failure。legacy external queue 满载 inline 的行为保持不变；formal task submit 使用 reject/credit policy，统一非阻塞返回 `BREAK_RUNTIME_OVERLOAD`，Network/IO/Audio/RHI 热路径不得 inline。全局 shutdown 由唯一 coordinator 发布 `CREATED -> STARTING -> RUNNING -> QUIESCING -> DRAINING -> STOPPING -> STOPPED/FAILED`；Task 的 `QUIESCING/DRAINING/STOPPING` 只是局部映射，不能另立全局状态机。

任务函数不得直接变更非 owner World/ECS/Session/Lua/UI/RHI；只读 snapshot 或输出 owned command。任务失败写入 task result/diagnostic，不跨线程抛异常；若无法保存错误，至少计数并使上层 fence 失败。Task pool、dependency links 和 context 生命周期必须在 task completion fence 后释放。

### 6.3 Message 与 IO

**设计目标：** Message 是 Runtime Core 的统一 ownership 载体：header、type/version、sequence、payload length、deadline/trace id 和 owned bytes；decode 前检查 magic/version/length/limit，未知 type 默认拒绝。Borrowed view 只能在回调期间使用；跨线程一律 deep copy 或引用计数 immutable blob。

每个 producer/consumer pair 必须声明容量、计数器和 backpressure policy。建议初始容量沿已有事实保持：网络 event/outbound 256；fragment assembly 16 MiB 总预算；Task external submit 256。IO completion queue 不应无限增长，设计目标为固定容量或总字节预算，overload 时保持 caller 可重试状态。IO callback 只投递 completion message，不直接调用 gameplay。

IO shutdown 先停止新请求，再取消/标记未完成请求，等待 completion producer 停止，drain 可释放消息，最后关闭 handles。cancel race 的结果必须是 exactly-one completion（成功、取消或失败之一），并带 request generation，避免旧 completion 命中新请求。

### 6.4 VFS

**当前已有：** `engine/src/asset/vfs.h:5-12` 有 16 mounts、260 字符路径、4096 PAK entries、128 MiB `VFS_MAX_FILE_BYTES`；`:42-73` 定义 opaque VFS、DIR/PAK mount、open/read/read_all。`engine/src/asset/vfs.c` 在正式 `engine` target 中，且 PAK 共享 FILE* 的并发 seek/read 已有 lock 说明（header `:55-60`）。

**设计目标：** VFS 解析路径时拒绝绝对路径、`..` 穿越、NUL/过长/非法 UTF-8（若平台策略要求）；mount 名与实际 host path 隔离；DIR/PAK lookup 都受 entry/file/total read budget。PAK header、version、entry count、offset+size、name offset+length 在读取前 checked，错误不继续读未验证偏移。异步 loader 只能收到 owned bytes 或 immutable asset blob，不能持有共享 FILE cursor。

安全更新包、签名 manifest、content address 和 rollback 属 Stage 5；当前 PAK magic/version 和 hash table 不是 authenticity proof。未实现对不可信远程包的信任链。

### 6.5 Profiler

**当前已有：** `engine/src/core/profiler.h:4-13` 有 120 frame、64 region、32 thread 上限；`:15-42` 定义 region/tid/frame ring；`:55-100` 提供线程注册和 Chrome trace 导出；`:103-119` 提供 provenance sidecar。Profiler 已在正式 `engine` target。

**设计目标：** profiler 记录路径必须无阻塞、固定预算、失败可丢样本但不得破坏业务；region overflow、thread overflow、trace path failure 必须有计数/返回值。导出在业务线程外用已拥有的 frame snapshot 执行，不能在持锁时写文件。元数据和 provenance 必须做路径、命令行、peer、用户 payload 的 redaction；不默认记录 secrets、tokens 或完整网络 payload。Profiler API 不得成为任意线程调用 gameplay 的回调通道。

## 7. 错误、隔离与 shutdown 总则

Runtime Core formal facade 统一使用 `BreakRuntimeError`：`OK`、`INVALID`、`CLOSED`、`OVERLOAD`、`OOM`、`TIMEOUT`、`STALE`、`REJECTED`、`FAILED`。Network/IO/Task/Audio/RHI 的 compatibility-specific 错误只在各自边界保留并映射到该集合。全局生命周期和关闭顺序由唯一 coordinator 定义；本节仍是设计目标/未实现。

1. **Validate before allocate/copy/dispatch**：长度、乘法、版本、sequence、预算、状态和 ownership 先验；
2. **No partial commit**：ECS delta、VFS mount、Session transition、resource publication 使用 staging/transaction；
3. **No callback re-entry**：network/IO/task/profiler callback 只能构造结果或 message；GameThread 在明确 poll 点 apply；
4. **Bound every wait**：公共 stop/join/poll/wait API 要有 deadline 版本；超时保留 ownership 并返回可重试错误；
5. **Idempotent cleanup**：release/destroy/stop 可重复调用；失败 start 必须清理已创建的下游对象；
6. **Observable overload**：overload、drop、timeout、stale、invalid、auth/integrity failure 分开计数并可导出；不能把丢包当成功；
7. **Fail closed**：未知 protocol/schema/backend/handle、资源超预算、owner 不匹配和 shutdown 中的提交都拒绝。

## 8. 验证与验收

### 8.1 focused 先行

实现前必须先有 focused RED test，逐条钉住：

- ECS snapshot/schema/delta：barrier 纪律、generation、schema hash、tick/base 校验、staging 失败原 World 不变；
- AoI/replication：确定性排序、owner/dormant/hysteresis、budget、queue overload retry、`UINT64_MAX` fail-closed；
- fragment：16 MiB 与 64 KiB 上限、乱序、duplicate/conflict、reset/eviction、完整 payload ownership；
- adapter/Session：256 队列 overload、borrowed/owned payload、single driver、start-failure cleanup、bounded stop、stale close watermark。

当前已有 focused normal/ASan/TSan 证据必须按实际运行命令记录；`docs/Implementation_Status.md:1-39` 已说明 focused 结果不能替代 clean full gate，且 fuzz 未构建时必须写 `Not Run`。

### 8.2 Runtime Core 验收矩阵

每个新正式 target 至少通过：

- normal：功能、边界、故障注入、重复 shutdown、超时 retry；
- ASan/UBSan：owned payload、queue wrap、task context、VFS read、profiler export 和所有 cleanup；
- TSan：submit/steal/wait、queue producer/consumer、Session event handoff、VFS PAK lock、Profiler thread registration；
- fuzz smoke：envelope/decode、schema/delta input、fragment metadata、VFS path/PAK header；
- deterministic stress：固定 seed、多线程重复运行，检查无 deadlock、无增长失控、错误计数可解释。

TSan 测试必须包含真实并发 producer/consumer，而不是只调用单线程 API；ASan 测试必须真正释放 borrowed/owned 两种路径。每个测试 target 的 CMake label、编译选项和是否正式 library 必须在文档和构建收据中可追溯。

### 8.3 正式 target 晋级 gate

focused 源只有在以下条件同时满足后才可晋级为正式库：

1. 明确公共头文件和 C11 ABI，移除仅测试 fault-injection 的生产依赖；
2. 由 `engine` 或独立正式 runtime library 单一编译，不再直接复制进测试 executable；
3. `engine_demo`/`dxx_break` 的链接边界经过 target-level contract test；
4. normal/ASan/TSan 和可用平台 lane 均有实际收据；
5. shutdown、backpressure、failure injection、ownership 和 security limitations 已写入对应设计文档；
6. 独立 review 确认“checksum != authentication”“Session != authentication backend”“focused != production integration”。

## 9. 数据流与后续依赖

目标数据流如下：

```text
PAL/OS -> IO/Network driver -> validate + copy -> bounded Message queues
                                                |
                                      GameThread poll/apply
                                                |
                         World/ECS owner -> immutable Snapshot
                                                |
                         Task read-only diff/AoI -> owned commands
                                                |
                         replication/session -> bounded outbound queue
```

依赖顺序：

1. PAL monotonic time、thread/lock/cond 和 allocation/error primitives；
2. bounded Message/IO queue 与统一 shutdown/failure taxonomy；
3. Task ownership、fence、worker shutdown；
4. VFS path/PAK validation 与 async owned blob；
5. Profiler bounded recording/export/redaction；
6. 将 ECS focused sources 迁入正式 runtime library，并由 GameThread/message contracts 接入；
7. 将 `break_net` 从 test-gated 目标晋级，补齐正式 Session/replication integration；
8. Stage 3 Lua facade 只能建立在上述 owner/queue/snapshot contracts 上；
9. Stage 5 才处理认证、签名更新、crash upload、replay protection、server authority 和 anti-tamper。

## 10. 未决风险

- `engine` 当前已有 Task/VFS/Profiler，但其历史 API 的全局 singleton、固定数组和部分 opaque lock 语义可能限制多 runtime instance；必须先做 ABI/生命周期审计，不能直接包装成可多实例服务。
- `break_net` 依赖 Snowflake 的 per-context completion/drop 通知仍较粗粒度；pending identity cleanup 不能在没有真实 completion 证据时提前释放。
- fragment timeout/eviction、schema negotiation、wire tick/schema 字段和正式 current-snapshot publication 尚未实现；在这些依赖完成前，不应宣称可靠 replication 或抗重放。
- FNV-1a checksum、schema hash、sequence 检查都不是密码学身份/完整性/保密机制；Stage 5 必须定义密钥、nonce、replay window、认证失败策略和 server authority。
- VFS 当前 128 MiB 单文件限制和 16 mount/4096 entry 固定上限是资源防护，不是恶意 package 的完整验证；压缩炸弹、符号链接、权限和签名包仍未定义。
- Profiler/日志可能泄漏路径、GPU、peer 或用户数据；redaction contract 在实现前必须由安全评审确认。
- TSan 只证明被执行的并发场景；未运行的 fuzz、缺失的非 Linux stop lane、known full-CTest failures 和未构建 target 必须继续标为未验证。
- C++ framework 与 Lua/editor 仍可能绕过 message/snapshot 边界；在正式集成前需要 target dependency gate 和 API token scan，防止直接引用 World、RHI native 或 Snowflake internals。

## 11. 证据索引

- `docs/design/roadmap_2026-10-22.md`：Stage 顺序、语言规则、网络 callback 禁止项、Stage 5 安全范围。
- `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`：设计/实现/normal-ASan-TSan/fuzz/full-gate 的状态账本。
- `docs/Architecture_Overview.md`：C11/C++11 分层、正式模块、Task/网络/ECS 当前边界与 focused target 事实。
- `docs/Implementation_Status.md`：当前验证数字、已知失败和“focused 不等于正式 integration”的限制。
- `docs/design/ecs_snapshot_replication_aoi.md`：snapshot/schema/delta/AoI/replication/fragment 的 ownership、容量、失败和未实现项。
- `docs/design/session_protocol.md`：18-byte envelope、256 队列、Session GameThread ownership、stale/close 语义。
- `docs/design/snowflake_c11_adapter.md`：Snowflake target 要求、single driver、callback 边界、bounded stop 和 owned payload。
- `engine/CMakeLists.txt:291-308,319-403,3165-3283`：真实 `engine`、focused ECS、fragment、Snowflake `break_net` target 证据。
- `engine/src/task/task.h`、`engine/src/asset/vfs.h`、`engine/src/core/profiler.h`：Runtime Core 现有容量、线程、VFS 和 Profiler API 证据。
