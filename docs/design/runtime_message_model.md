# Runtime Message Model 设计

**状态：Stage 2 设计提案；消息 envelope 与 bounded queue 基元已作为正式可选 `runtime_core` 库的一部分交付（2026-10-22，Task 4），但未集成进 `engine`/`engine_demo`/`dxx_break`；registry、mailbox 拓扑与各域 bridge 仍未实现。**

**已交付事实（2026-10-22，Task 4）**：`runtime_core` 新增 `engine/src/runtime/runtime_message.h/.c`（`BreakRuntimeMessageView` 借用 view：kind/version/flags/sequence + data/size；`break_runtime_message_copy()` 做 checked size 校验（NULL 参数/无 data 的 size>0 → `INVALID`，超过 `BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD`（默认 16 MiB，可编译期覆盖）→ `OVERLOAD`，分配失败 → `OOM`），单分配生成 owned message，只持有拷贝的 bounded bytes，绝不保留生产者栈/World/Lua/Snowflake/UI 指针；`break_runtime_message_release()` 显式释放，test 构建（`BREAK_RUNTIME_TESTING`）用按指针值查询的 live registry 拒绝 double release/外来指针（fail-stop abort，且解引用前先查表，ASan 验证无 UAF））与 `engine/src/runtime/runtime_queue.h/.c`（bounded MPSC FIFO 队列：满 → 非阻塞 `BREAK_RUNTIME_OVERLOAD`；`reserved_control` 槽位仅供 `BREAK_RUNTIME_MESSAGE_FLAG_CONTROL` 消息，数据区满时控制消息仍可入队；enqueue 显式携带 expected generation，失配 → `BREAK_RUNTIME_STALE`；`close()` 停止 admission、推进 generation 并 broadcast 唤醒全部 `wait()` waiter（drain 完毕后报 `CLOSED`）；enqueue 时所有权转移给队列、poll/wait 转移给消费者、任何失败路径调用方保留所有权并负责释放；create 做 count+byte 双检查；`break_runtime_queue_stats()` 暴露 enqueued/dequeued/overload/stale/closed/high-water 计数）。以上均为正式可选库能力，不构成 engine/demo 集成。验证：`test_runtime_facade` 13/13（含 fork 子进程 double-release abort、分配故障注入、4 生产者 MPSC、shutdown wakeup），normal/ASan+UBSan/TSan 三树各 3/3（含 `test_runtime_core` 9/9 与 target contract）；TSan 连跑 10 次零报告。

本文定义 Break Runtime Core 的跨线程消息模型、所有权和生命周期边界。它不声称新增 Runtime target、ECS/Session 正式集成或 PAL/Thread/Task/IO/VFS/Profiler facade 已经存在。本文只覆盖消息合同和与现有 ECS snapshot/schema/delta/AoI/replication、`break_net`/Session 边界的衔接方向。

## 1. 目标与非目标

### 1.1 目标

1. 先正式化现有 ECS snapshot/schema/delta/AoI/replication/fragment 与 `break_net`/Session 的 target 边界，再作为 Runtime Core 的消息生产者/消费者。
2. 让跨线程通信只经过有界、可观测、具有明确所有权的消息队列；网络 callback、IO worker、Task worker 不直接调用 World/ECS/Lua/UI/RHI。
3. 保持 C11 Runtime Core、C++11 application/framework、Lua 脚本边界。C11 公共 ABI 使用不透明句柄、固定宽度整数、显式长度和返回值错误处理。
4. 将当前已有能力、focused/test-only 能力和设计目标分开，避免把提案写成已实现功能。
5. 为正常、ASan、TSan 和故障注入测试提供可执行的容量、backpressure、shutdown 和 failure 合同。

### 1.2 非目标

本文不实现以下内容：

- 不修改 `engine/CMakeLists.txt`、源码、公共 ABI 或正式 target；
- 不设计 player authentication backend、加密认证、在线更新、反作弊、分布式 Cell、预测/回滚或 Lua gameplay callback；
- 不把 FNV-1a fragment checksum 当作加密认证；
- 不把现有 focused target 的通过结果升级为正式 `engine` runtime/session integration；
- 不定义 RHI 命令提交或 UI 线程操作的跨线程例外。

## 2. 证据与现状分类

### 2.1 正式已有（当前 `engine` target 或已有公共基础设施）

- `engine` static library 在 `engine/CMakeLists.txt:319-403` 已编入 `src/task/task.c`、`src/asset/vfs.c`、`src/core/profiler.c`、`src/network/network.c`、`src/network/packet.c`、`src/network/net_replication.c`、平台选择的 `net_loop` backend，以及 `src/platform/` 中的 input/config/time/filewatch/WSI 相关源；窗口后端由后续 `target_sources(engine ...)` 按平台加入。
- 现有 `src/network/net_replication.c` 是 engine 内 UDP transform snapshot 路径，测试为 `test_net_replication`；它不是 focused ECS `break_replication` / `break_net` Session 路径，不得混称为同一 replication 合同。
- `engine/src/task/task.h` 定义线程池、外部提交队列 `SUBMIT_QUEUE_CAPACITY == 256`、优先级、依赖 handle，并明确 `TaskSystem` 单进程单实例；worker task 不得调用 `task_wait()`/`task_wait_handle()`，否则自等待死锁。
- `engine/src/network/net_loop.h` 提供 epoll/io_uring/kqueue/IOCP 选择的 readiness loop。除 `net_loop_wakeup()` 外，操作与 `wait()`/destroy 不能并发，且 loop-thread-affine。
- `engine/src/asset/vfs.h` 提供 DIR/PAK mount、最多 16 mounts、最多 128 MiB 单文件读取上限；`vfs.c` 已使用锁保护共享 PAK `FILE*` 的 seek/read。
- `engine/src/core/profiler.h` 提供每帧 ring、最多 32 个 profiler thread track 和 Chrome trace/provenance 导出；这不是消息队列本身。
- `engine/src/platform/platform.h` 的窗口、输入、IME、WSI 和 clipboard API 属于所属平台/主循环线程；跨线程调用须通过未来的 command message，不得直接调用。

### 2.2 已有但 focused/test-only（不可称为正式 Runtime 集成）

- `engine/src/ecs/replication_schema.{h,c}`：确定性 POD schema 注册、canonical component ID hash；registry 是初始化/GameThread-owned，非同步热路径。
- `engine/src/ecs/world_snapshot.{h,c}`：GameThread 在结构屏障完成后构造拥有字节的不可变 snapshot；实体身份含 `(index,generation)`，无自动 barrier。
- `engine/src/ecs/world_delta.{h,c}`：不可变 snapshot diff、base/schema/tick 验证、ECS-owned staging、final validation 和 atomic replace；失败时原 World 不变。
- `engine/src/network/break_aoi.{h,c}`：空间网格、sphere/AABB witness、owner/dormant/relevancy、hysteresis 和确定性 `enter/stay/leave`。
- `engine/src/network/break_replication.{h,c}`：Real/Ghost、baseline/dirty/destroy/dormant、带宽预算和 overload 后 retry。该路径依赖 `BreakNetReactor`，当前只随 `break_net`/focused tests 存在。
- `engine/src/network/break_replication_fragment.{h,c}`：transport-independent 分片/重组，单次重组上限 `BREAK_REPLICATION_MAX_REASSEMBLY_SIZE == 16 MiB`，FNV-1a 完整性校验、乱序、精确 duplicate/conflict、owned 完整 payload、reset/destroy。
- `engine/src/network/break_net_adapter.{h,c}`、`break_session.{h,c}` 及相关 protocol/message/event 文件：只在 `ENGINE_BUILD_TESTS=ON && BREAK_ENABLE_SNOWFLAKE=ON` 下生成 `break_net`；`engine_demo`/`dxx_break` 不链接它。adapter event/outbound queue 均为 256 项，Session manager 为 GameThread-only；真实 loopback 和 focused normal/ASan/TSan 证据见 `docs/design/snowflake_c11_adapter.md`、`docs/design/session_protocol.md`。
- `engine/CMakeLists.txt:3165-3179` 将 ECS snapshot/schema/delta/AoI 直接编入 `test_ecs_replication`；`engine/CMakeLists.txt:3219-3233` 将 fragment 编为 test-only `break_replication_fragment`；`engine/CMakeLists.txt:3235-3283` 将 `break_net` 及其 Session/replication tests 限定在测试/Snowflake 条件下。

### 2.3 设计目标（本文件提出，当前未实现）

- 消息类型 registry、per-kind byte budget、未知 kind/version 策略（envelope 与 owned/borrowed contract 已交付，见文首 Task 4 已交付事实）；
- GameThread、Task workers、Network/IO、PAL/MainLoop、Profiler 之间的有界 mailbox 拓扑与接线（单队列基元已交付，mailbox 拓扑未接线）；
- snapshot publication、delta apply、fragment timeout/eviction、Session 事件的正式 runtime service；
- PAL/Thread/IO/VFS/Profiler Runtime Core facade 及其独立测试矩阵（Message/Queue/Task facade 已交付，其余仍为设计目标）。

## 3. 语言与 ABI 边界

### 3.1 C11 Runtime Core

Runtime Core 的实现和公共 C ABI 使用 C11，沿用 `engine/src/core/types.h` 的 `u8/u16/u32/u64/usize`。公共消息不得依赖 C++ class、exception、RTTI、模板、隐式构造/析构或 packed host struct。所有 wire/持久化字段使用显式 little-endian 编解码；消息 header 的大小、版本、payload length 和加法溢出均在验证前检查。

建议方向（未实现，不是现有 API）：

```c
/* Example types come from engine/src/core/types.h. This is design-only. */
typedef struct BreakRuntimeMessage BreakRuntimeMessage;
typedef struct BreakRuntimeMailbox BreakRuntimeMailbox;

typedef enum BreakRuntimeMessageKind {
    BREAK_RUNTIME_MSG_NONE = 0,
    BREAK_RUNTIME_MSG_ECS_SNAPSHOT_READY,
    BREAK_RUNTIME_MSG_ECS_DELTA_READY,
    BREAK_RUNTIME_MSG_AOI_RESULT,
    BREAK_RUNTIME_MSG_REPLICATION_RECORD,
    BREAK_RUNTIME_MSG_NET_EVENT,
    BREAK_RUNTIME_MSG_SESSION_COMMAND,
    BREAK_RUNTIME_MSG_IO_COMPLETION,
    BREAK_RUNTIME_MSG_PLATFORM_EVENT,
    BREAK_RUNTIME_MSG_TASK_COMPLETION,
    BREAK_RUNTIME_MSG_PROFILER_SAMPLE,
    BREAK_RUNTIME_MSG_SHUTDOWN
} BreakRuntimeMessageKind;

typedef enum BreakRuntimeError {
    BREAK_RUNTIME_OK = 0,
    BREAK_RUNTIME_INVALID,
    BREAK_RUNTIME_CLOSED,
    BREAK_RUNTIME_OVERLOAD,
    BREAK_RUNTIME_OOM,
    BREAK_RUNTIME_TIMEOUT,
    BREAK_RUNTIME_STALE,
    BREAK_RUNTIME_REJECTED,
    BREAK_RUNTIME_FAILED
} BreakRuntimeError;
```

实际字段应保持 opaque handle + discriminated payload，不把 `World *`、`lua_State *`、RHI native handle、Snowflake connection pointer 或平台 native object 放进可跨线程消息。消息只携带 immutable snapshot/delta handle、复制的 bounded bytes、ID/版本/tick、错误码和审计 metadata。

### 3.2 C++11 application/framework

`framework/` 继续使用 C++11 的 `RuntimeModuleInterface`/`BaseApplication` 生命周期（见 `docs/Architecture_Overview.md:102-109`）。C++ 层只能持有 C opaque handle 或调用 C ABI；不得把 `std::function`、STL 容器布局或 exception 穿过 Runtime Core ABI。C++ application 的 `Init/Tick/DeInit` 负责创建、驱动和关闭 Runtime，而不取得 World/ECS 的跨线程写权限。

### 3.3 Lua

Lua 是唯一计划中的 runtime scripting language（`docs/design/roadmap_2026-10-22.md:7-12`）。Lua VM 所在线程拥有 `lua_State`；消息 handler 不把裸 Lua state 交给 Network/IO/Task worker。未来 Lua facade 只消费 GameThread 上的 typed command/result，ECS 写入走 bounded batch command，不能直接持有 World、RHI、socket、native PAL 或任意 message queue 内部指针。Lua runtime facade 尚未实现。

## 4. 架构与 target 边界

### 4.1 目标 target graph（设计方向）

```text
engine (当前正式 C11 engine library)
  ├─ core/platform/task/asset/network 基础（已有）
  └─ [未来显式集成，需独立批准]
       runtime_core (PAL/Thread/Task/Message/IO/VFS/Profiler contracts)
          ├─ ecs_runtime_bridge (snapshot/schema/delta/AoI/replication)
          ├─ session_runtime_bridge (break_net/Session)
          └─ application/framework consumers (C++11)

focused/test-only（当前）
  test_ecs_replication -> snapshot/schema/delta/AoI sources
  break_replication_fragment -> test_break_replication_fragment
  break_net -> Snowflake + adapter/session/replication focused tests
```

关键规则：focused source 在实现正式 bridge 前不能移动进 `engine`，不能仅通过扩大 library source list 宣称完成。正式 target 必须有独立头文件依赖、link contract、normal/ASan/TSan 测试和 runtime/session E2E。

### 4.2 线程域

| 域 | 所有者 | 允许写入 | 消息出口 |
|---|---|---|---|
| GameThread | application/runtime tick | mutable World/ECS、schema registry、Real/Ghost、Session manager、Lua state | Task/IO/Network/PAL command queues |
| Task worker | `TaskSystem` worker | worker-local scratch；只读 snapshot/delta/AoI calculation result | owned result message 到 GameThread |
| Network reactor/adapter | Snowflake driver 或 Break host thread | transport state、adapter identity、event/outbound queues | copied `BreakNetEvent` 到 GameThread |
| IO worker | future IO service | owned read/decode buffers、request state | `IO_COMPLETION` 到 GameThread/asset owner |
| PAL/main loop | platform main-loop thread | Platform/Window/WSI/Input/IME state | platform event/command queues |
| Profiler recorder | calling thread + profiler internals | per-thread trace slots | bounded export/flush request |

GameThread 是 mutable World/ECS/script/Session 的唯一 owner。Network callback 只验证、复制、入队；不调用 GameThread、Session、ECS、Lua、UI、RHI。Task worker 只读取已经 retain 的 immutable snapshot/delta/AoI inputs；不能从 worker 调 `task_wait`。PAL/window/WSI 只在所属主线程执行。上述边界是对当前文档已有约束的正式化，不是新增实现。

### 4.3 线程所有权转移

- `Borrowed`：只在单次函数调用或 handler duration 有效；不入异步队列。当前 `BreakNetMessageView`（`engine/src/network/break_net_message.h:11-17`）是此类。
- `Owned`：由创建方显式 copy，队列槽位或 opaque handle 持有；poll 后转移给接收方，最终调用 release。当前 `BreakNetOwnedMessage` 和 `break_net_event_release()` 是可复用证据。
- `Shared immutable`：snapshot/delta 在异步消费者期间 retain，最后 release；不得通过消息携带裸 `World *`。
- `Command`：payload 由生产者 copy，消费成功/拒绝/过期后由 mailbox 释放；不得保存生产者栈地址。
- `Native resource`：只传 stable ID/opaque ownership token；实际 socket/window/RHI object 仍由所属域销毁。

## 5. 消息结构、队列与数据流

### 5.1 消息 envelope 方向

建议 Runtime envelope 包含：`kind`、`version`、`flags`、`sequence`、`source_domain`、`target_domain`、`payload_size`、`correlation_id`、`tick` 和 discriminated payload。header 应有固定上限，payload 必须受每种 kind 的 registry limit 约束。它可复用当前 `BreakNetEnvelope` 的显式 little-endian 思路，但不应直接复用当前 default registry：当前 codec 仍使用 default registry，且 custom registry codec 边界已记录为未完成。

ECS 消息方向：

```text
GameThread: finish systems + structural barrier
  -> build owned WorldSnapshot
  -> retain/publish snapshot handle
  -> Task worker: pure diff / AoI candidate calculation
  -> GameThread: validate result, update Real/Ghost, schedule records
  -> replication message / fragment message
  -> Network queue: copy + bounded send
  -> adapter/Snowflake transport

Network callback
  -> validate envelope + copy bounded event
  -> adapter event queue
  -> GameThread poll_adapter
  -> Session state transition / future replication input
  -> complete delta only after reassembly + base/schema/tick validation
  -> staging apply + atomic World replace
```

当前 `break_world_snapshot_build()` 要求 GameThread/structural barrier，`break_world_delta_apply()` 已有 staging + atomic replace；未来 message model 只传这些 owned immutable values，不能绕过现有验证。

### 5.2 容量与 backpressure

初始设计值必须显式固定，而不是无限增长。Compatibility API 的现有行为与 Runtime Core facade 的正式行为分开记录：legacy Task queue 满载时 inline execute 保持不变；formal task submit 采用 reject/credit policy。Runtime Core queue 满统一非阻塞返回 `BREAK_RUNTIME_OVERLOAD`，Network/IO/Audio/RHI 热路径禁止 inline 或等待队列空间。completion queue 的等待必须可被 request deadline 或 shutdown wakeup 打断：

| 队列 | 初始容量方向 | 满载行为 |
|---|---:|---|
| Network inbound events | 256（与 `BREAK_NET_EVENT_QUEUE_CAPACITY` 一致） | 非阻塞丢弃/计数；不得阻塞 callback；payload 在失败路径释放 |
| Network outbound commands | 256（与 `BREAK_NET_OUTBOUND_QUEUE_CAPACITY` 一致） | 返回 `FULL/OVERLOAD`，保留上层未发送状态，后续 sync retry |
| Runtime control/mailbox | 256 slots；按 kind 可设 byte budget | control/error/shutdown 可保留 reserved slots；普通消息返回 FULL |
| Task external submit | 256（与 `SUBMIT_QUEUE_CAPACITY` 一致） | 返回失败或明确记录 overload；禁止无界 malloc 逃逸 |
| Network wire fragment | 单片 64 KiB（wire 上限） | 只限制 transport fragment，不等同 Runtime message 或 asset blob |
| Runtime internal message | 按 kind 的 fixed slots/byte budget | `BREAK_RUNTIME_OVERLOAD`；不隐式分片 |
| Asset manifest/blob | manifest 与 blob 分开预算 | 分别校验元数据与 bytes，不套用 wire fragment 上限 |
| Fragment reassembly | 16 MiB total per assembly | `OVERLOAD`；另设 per-connection aggregate bytes/assembly-count 预算方向；无分配或保留旧 assembly，直到 reset/evict |
| Message payload | Runtime kind-specific budget | `BREAK_RUNTIME_OVERLOAD`；禁止截断或隐式分片 |
| VFS read | 128 MiB per file（与 `VFS_MAX_FILE_BYTES` 一致） | fail closed；不创建超限 buffer |

Backpressure policy 分三类：

1. **可重试数据**（dirty/baseline、IO completion、低优先级 profiler）：返回 overload，记录 dropped/deferred counter，由 owner 在下一 tick 重试或合并。
2. **不可丢控制**（shutdown、close watermark、failure）：使用 reserved control capacity；若仍无法入队，转为同步 owner-local failure latch，阻止继续消费数据并进入 shutdown。
3. **过时数据**（stale connection、旧 snapshot generation、已关闭 session）：不重试，分类为 `STALE` 并释放 owned payload。

禁止默认阻塞发送。若未来提供 blocking API，只能是 owner thread 的显式等待版本，必须带 deadline，并且 callback/worker 不能调用。

### 5.3 snapshot、delta、fragment 消息

- Snapshot message 只携带 snapshot handle/ID、tick、schema hash 和 retain token；接收者在消费期间 retain，不能访问 live World。
- Delta message 必须携带 base ID、target ID、base/target schema hash、base/target tick 和 records；接收端先做 metadata validation，再进入 fragment reassembly，完整 payload 后再次做 schema/base/tick validation。
- Fragment layer 仍 transport-independent；它不入队、不调用 Snowflake、不修改 World。当前 checksum 只保证完整性，不保证 authenticity。
- AoI result 必须是 owner 可释放的 sorted ID arrays；不能携带指向 spatial index 内部节点的指针。
- Replication scheduler 在 GameThread 拥有 Real/Ghost 和 connection state；Network 只拥有 copied command/event。queue full 后的 retry 不得重复递增 Real version 或重复改变 Ghost state。

## 6. 错误、failure 与 shutdown

### 6.1 错误模型

C11 API 返回 enum/bool，formal facade 统一使用 `BreakRuntimeError`：`OK`、`INVALID`、`CLOSED`、`OVERLOAD`、`OOM`、`TIMEOUT`、`STALE`、`REJECTED`、`FAILED`。compatibility API 的 `FULL`、`OVER_LIMIT`、`WRONG_OWNER`、`SCHEMA_MISMATCH` 等名称只在其现有边界内保留，并映射到统一类别。错误对象只带稳定数值、source/kind/correlation/tick；不把 `errno`、Snowflake 指针或 transient string 跨线程保存。

所有失败路径要求：

- 输出对象先清零或保持旧有效对象；
- checked `count + 1`、`count * sizeof`、payload/header 加法后才分配；
- partial owned payload 由当前 owner 释放；
- delta staging 失败时原 World 保持不变；
- adapter start failure terminate/destroy 后才发布 FAILED；
- handler failure 通过 Session apply stats 分类并进入既定 close policy，不在 callback 线程执行业务恢复。

### 6.2 shutdown 局部动作

Runtime shutdown 由 `runtime_overview.md` 定义的唯一 Runtime coordinator 发起；GameThread/application 只能提交 stop 请求。全局状态和顺序不在本文件重复定义，Session/adapter/mailbox 的状态只是局部映射。Message 域只执行：停止 admission 后拒绝新 message；停止 producer 并发布 close/error watermark；关闭 mailbox、发出 bounded wakeup；在 coordinator 的 drain deadline 内 poll 有界 completion；把仍存活的 queue/worker ownership 交回 coordinator。任何 timeout 返回 `BREAK_RUNTIME_TIMEOUT`/`TIMEOUT`，不得强制 free 仍可能被 worker/callback 访问的对象；失败状态只允许诊断、cleanup 和安全 retry。

## 7. 正式化顺序与接口方向

### Phase A：先 formalize ECS/network boundary（未实现）

1. 为 snapshot/schema/delta/AoI/replication/fragment 建立单独 formal library contract；保留现有 focused target 作为 RED/GREEN 回归，不直接删除。
2. 决定 `break_net` 是否拆成不依赖 Snowflake 的 protocol/message/fragment library 与可选 Snowflake adapter；Session 继续 GameThread-only。
3. 增加正式 publication service：GameThread publish owned snapshot，workers retain；明确 mutex/atomic publication 和 shutdown epoch。当前文档明确此 service 尚不存在。
4. 增加 wire schema/tick/base fields 与 version negotiation；没有 schema negotiation 前不称为 production replication。
5. 增加 fragment timeout/eviction scheduler；当前 reassembler 只支持 reset/destroy，无 timeout/eviction。

### Phase B：Runtime Core foundation（未实现）

1. PAL/Thread contract：thread ID、mutex/cond、wakeup、deadline、owner assertions，复用 `engine/src/core/platform_thread.h` 语义但不暴露 OS type。
2. Message registry/mailbox：固定容量、reserved control slots、per-kind byte budget、FIFO/priority 规则、sequence/correlation、owned release。
3. Task bridge：只接受 immutable input handle 或 copied command，禁止跨 worker 访问 World；显式记录 submit/reject/completed。
4. IO bridge：`net_loop`/VFS/async loader 的 completion 统一为 copied result；IO worker 不触碰 UI/ECS/Lua。
5. VFS bridge：mount/read request 带 path length 和 128 MiB cap；PAK shared cursor 继续由 VFS owner lock 保护。
6. Profiler bridge：每线程只写自身 recorder，flush/export 在 owner 线程；queue overload 不破坏 frame ring 或 trace JSON。

### Phase C：Game/Application bridge（未实现）

C++11 framework 在 `Init/Tick/DeInit` 建立 runtime；每 tick 由 GameThread poll control、network、IO、task result，再按优先级运行 ECS apply/replication。Lua 只接收 GameThread typed messages。编辑器/远程 RPC 必须另有 auth/security 设计，不能通过本 message model 默认放行。

## 8. 测试与验收设计

### 8.1 Focused contract tests

在不改变现有源码/CMake的前提下，本节只定义未来验收：

- message header round-trip、little-endian bytes、version/kind/flags/length/sequence 校验；
- borrowed view 在生产者修改/释放后不会影响 owned message；double release、zero payload、NULL/overflow/64 KiB over-limit；
- FIFO、capacity-1/full、reserved shutdown slot、non-blocking overload 和 retry/drop counters；
- wrong-owner send、closed mailbox、stale connection、duplicate sequence、correlation mismatch；
- snapshot retain/release、worker 只读、delta base/schema/tick mismatch、staging failure 后 World byte-for-byte 不变；
- fragment reorder、duplicate/conflict、16 MiB boundary、timeout/eviction、reset 后无 use-after-free；
- Session adapter loopback 保持当前真实 AUTH/PING/close/stale 证据，不把 handler callback 放回 network thread；
- PAL/IO/VFS shutdown wakeup、deadline、partial read、PAK lock 和 VFS 128 MiB cap；
- profiler 多线程 tid 分配、ring wrap、export failure 和 message overload。

### 8.2 Sanitizer 与并发验收

每个正式 target 必须有 normal、ASan/UBSan、TSan 三条 focused lane（平台工具不可用时记录 unavailable，不伪造通过）：

- **ASan**：队列满/失败释放、borrowed-after-return、double release、fragment reset/destroy、shutdown race、VFS read cap；无 leak/UAF/heap-buffer-overflow。
- **TSan**：多 producer event enqueue、single consumer poll、snapshot retain/release、Task completion、profiler per-thread record、shutdown wakeup；无 data race。Session/World 单线程违规应由 owner test 或 debug assertion 检出，不以加 mutex 隐藏边界。
- **UBSan/编译器 gate**：整数加法/size overflow、enum/shift、alignment、显式 wire decode；C11 `-Wall -Wextra -Werror -pedantic` 兼容现有构建策略。
- **压力/故障注入**：随机 producer delay、worker stop、allocation failure、queue full、Snowflake start failure、step timeout、late close/open；每次失败都必须最终释放所有 owned payload 或保留明确可重试状态。

### 8.3 End-to-end 验收门

只有同时满足以下条件，才可把 ECS/network bridge 标记为正式 runtime integration：

1. 正式 target 被显式构建，且 focused/test-only target 仍独立存在；
2. GameThread snapshot -> worker diff/AoI -> replication -> adapter queue -> loopback transport -> GameThread apply 的真实调用链通过；
3. 完整 delta 在 base/schema/tick 验证后才 apply，失败不修改 World；
4. queue overload、fragment timeout/eviction、Session close watermark、adapter bounded stop 都有断言；
5. normal/ASan/TSan 均通过并记录命令、build tree、测试计数；
6. full CTest 中未构建的 fuzz target、已知环境失败和 skipped lane 单独分类，不能写成 full gate；
7. `git diff --check` 通过，文档中的 implemented/focused/design/not implemented 状态与源码/CMake证据一致。

## 9. 后续依赖与未决风险

1. **Formal target边界**：当前 focused source 直接编入测试 target，正式 `engine` 未链接；若过早移动，可能把测试宏、Snowflake 依赖和 production ABI 混入 engine。
2. **Snapshot publication**：当前只有 caller-retain contract，没有 mutex-protected current-snapshot service；publication epoch、销毁时序和 worker cancellation 仍待单独设计。
3. **Schema evolution**：schema hash 已确定性，但 wire negotiation、版本兼容、未知组件策略未实现；不能默认跨版本 delta 可用。
4. **Reassembly lifetime**：当前 fragment reassembler 无 timeout/eviction；恶意或失联 peer 可长期占用 16 MiB budget，需 scheduler/authority policy。
5. **Authentication**：FNV-1a 只做完整性，不抵抗篡改；安全/密钥/重放属于 Stage 5，不应由 Runtime Message Model 假装解决。
6. **Backpressure fairness**：固定 256 queue 可保护内存但可能造成高优先级控制与大量 dirty message 竞争；reserved slots、per-kind quotas 和 metrics 必须在实现前钉死。
7. **TaskSystem singleton**：现有 `TaskSystem` 进程单实例且 external submit queue 为 256；Runtime 多实例/测试并行需要隔离策略，不能直接创建第二个 live system。
8. **PAL线程限制**：现有 platform/WSI/window APIs 仍是 main-loop-affine；跨平台 shutdown wakeup、Wayland surface loss、Windows condition variable 和 macOS run loop 需要真实平台 lane。
9. **Snowflake通知粒度**：per-context completion/drop notification 较粗，adapter 当前依赖 send-drained/close 顺序保护 identity；正式 message delivery receipt 需要明确失败/重试语义。
10. **Full gate解释**：`docs/Implementation_Status.md` 记录的 181 项 full CTest 曾包含 5 个未构建 fuzz smoke、已知 Hebrew/golden drift 和 skipped dependency gate；未来验收必须逐项分类，不能只引用总数。
11. **Lua/editor/security依赖**：Lua facade、editor RPC、online update、security/authentication 都依赖本模型，但反向不能把这些尚未批准的功能写入 Runtime Core 的已实现范围。

## 10. 参考证据

- `docs/design/roadmap_2026-10-22.md:31-50,128-145`：Stage 2 顺序、formal-vs-focused 规则和当前 ECS/network gap。
- `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md:14-24,61-70`：Stage 2 交付项、sanitizer/full-gate/审查要求。
- `docs/Architecture_Overview.md:76-110,125-141,438-506`：C11/C++11 分层、现有模块、Task/Snowflake/ECS ownership 和 integration boundary。
- `docs/Implementation_Status.md:1-55`：当前 focused normal/ASan/TSan、adapter/session 生命周期、full CTest 分类证据。
- `docs/design/ecs_snapshot_replication_aoi.md:1-20,43-78,100-159`：snapshot/delta/schema/AoI/replication/fragment 的当前实现与未来边界。
- `docs/design/session_protocol.md:1-19,21-84,174-237`：Session/adapter message ownership、256 queue、GameThread-only 和 wire lifecycle。
- `docs/design/snowflake_c11_adapter.md:1-17,73-103,201-228`：Snowflake ownership、driver mode、bounded stop 和 failure cleanup。
- `engine/CMakeLists.txt:319-403,3165-3283`：正式 `engine` source 与 focused/test-only target 的真实构建边界。
- `engine/src/ecs/{replication_schema.h,world_snapshot.h,world_delta.h}`：C11 snapshot/schema/delta API 方向。
- `engine/src/network/{break_net_message.h,break_net_events.h,break_net_adapter.h,break_session.h,break_replication_fragment.h}`：owned/borrowed message、event/queue、Session、fragment API 证据。
- `engine/src/task/task.h`, `engine/src/network/net_loop.h`, `engine/src/asset/vfs.h`, `engine/src/core/profiler.h`, `engine/src/core/platform_thread.h`：现有 Task/IO/VFS/Profiler/PAL基础约束。
