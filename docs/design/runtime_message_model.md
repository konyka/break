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
- 不设计 player authentication backend、加密认证、在线更新、反作弊、分布式 Cell、预测/回滚或 Lua logic callback；
- 不把 FNV-1a fragment checksum 当作加密认证；
- 不把现有 focused target 的通过结果升级为正式 `engine` runtime/session integration；
- 不定义 RHI 命令提交或 UI 线程操作的跨线程例外。

## 2. 证据与现状分类

### 2.1 正式已有（当前 `engine` target 或已有公共基础设施）

- `engine` static library 在 `engine/CMakeLists.txt:387-471` 已编入 `src/task/task.c`、`src/asset/vfs.c`、`src/core/profiler.c`、`src/network/network.c`、`src/network/packet.c`、`src/network/net_replication.c`、平台选择的 `net_loop` backend，以及 `src/platform/` 中的 input/config/time/filewatch/WSI 相关源；窗口后端由后续 `target_sources(engine ...)` 按平台加入。
- 现有 `src/network/net_replication.c` 是 engine 内 UDP transform snapshot 路径，测试为 `test_net_replication`；它不是 focused ECS `break_replication` / `break_net` Session 路径，不得混称为同一 replication 合同。
- `engine/src/task/task.h` 定义线程池、外部提交队列 `SUBMIT_QUEUE_CAPACITY == 256`、优先级、依赖 handle，并明确 `TaskSystem` 单进程单实例；worker task 不得调用 `task_wait()`/`task_wait_handle()`，否则自等待死锁。
- `engine/src/network/net_loop.h` 提供 epoll/io_uring/kqueue/IOCP 选择的 readiness loop。除 `net_loop_wakeup()` 外，操作与 `wait()`/destroy 不能并发，且 loop-thread-affine。
- `engine/src/asset/vfs.h` 提供 DIR/PAK mount、最多 16 mounts、最多 128 MiB 单文件读取上限；`vfs.c` 已使用锁保护共享 PAK `FILE*` 的 seek/read。
- `engine/src/core/profiler.h` 提供每帧 ring、最多 32 个 profiler thread track 和 Chrome trace/provenance 导出；这不是消息队列本身。
- `engine/src/platform/platform.h` 的窗口、输入、IME、WSI 和 clipboard API 属于所属平台/主循环线程；跨线程调用须通过未来的 command message，不得直接调用。

### 2.2 正式可选库（2026-10-22 Tasks 1-2 交付 target；仍不链入 `engine`/`engine_demo`/`dxx_break`，不等于正式 Runtime 集成）

正式 target graph：`break_ecs_replication`（ECS schema/snapshot/delta + core logging，`engine/CMakeLists.txt:313-324`）、`break_replication_core`（AoI/replication/fragment，`:326-333`）、`break_net`（Snowflake-conditional，`:362-377`）。以下 API 描述不变：

- `engine/src/ecs/replication_schema.{h,c}`：确定性 POD schema 注册、canonical component ID hash；registry 是初始化/LogicThread-owned，非同步热路径。
- `engine/src/ecs/world_snapshot.{h,c}`：LogicThread 在结构屏障完成后构造拥有字节的不可变 snapshot；实体身份含 `(index,generation)`，无自动 barrier。
- `engine/src/ecs/world_delta.{h,c}`：不可变 snapshot diff、base/schema/tick 验证、ECS-owned staging、final validation 和 atomic replace；失败时原 World 不变。
- `engine/src/network/break_aoi.{h,c}`：空间网格、sphere/AABB witness、owner/dormant/relevancy、hysteresis 和确定性 `enter/stay/leave`。
- `engine/src/network/break_replication.{h,c}`：Real/Ghost、baseline/dirty/destroy/dormant、带宽预算和 overload 后 retry。该路径仍经 `BreakNetReactor` 发送（`break_replication.h` 引用 `break_net_adapter.h`，reactor 符号由消费方最终链接解析）；2026-10-22 起由正式可选 `break_replication_core` 承载。
- `engine/src/network/break_replication_fragment.{h,c}`：transport-independent 分片/重组，单次重组上限 `BREAK_REPLICATION_MAX_REASSEMBLY_SIZE == 16 MiB`，FNV-1a 完整性校验、乱序、精确 duplicate/conflict、owned 完整 payload、reset/destroy。同属正式可选 `break_replication_core`。
- `engine/src/network/break_net_adapter.{h,c}`、`break_session.{h,c}` 及相关 protocol/message/event 文件：`BREAK_ENABLE_SNOWFLAKE=ON` 即生成正式可选 `break_net`（独立于 `ENGINE_BUILD_TESTS`，链接 `break_replication_core` + `snow::net`）；`engine_demo`/`dxx_break` 不链接它。adapter event/outbound queue 均为 256 项，Session manager 为 LogicThread-only；真实 loopback 和 focused normal/ASan/TSan 证据见 `docs/design/snowflake_c11_adapter.md`、`docs/design/session_protocol.md`。
- `engine/CMakeLists.txt:3235-3258` 的 `break_ecs_replication_test` 仍以 fault-injection 宏（`BREAK_WORLD_DELTA_TESTING=1`）直接编译 ECS snapshot/schema/delta/AoI 源供 `test_ecs_replication`；`engine/CMakeLists.txt:3405-3412` 的 `test_break_replication_fragment` 链接正式 `break_replication_core`；`engine/CMakeLists.txt:3417-3444` 的 Snowflake 测试链接正式 `break_net`。

### 2.3 设计目标（本文件提出，当前未实现）

- 消息类型 registry、per-kind byte budget、未知 kind/version 策略（envelope 与 owned/borrowed contract 已交付，见文首 Task 4 已交付事实）；
- LogicThread、Task workers、Network/IO、PAL/MainLoop、Profiler 之间的有界 mailbox 拓扑与接线（单队列基元已交付，mailbox 拓扑未接线）；
- snapshot publication、delta apply、fragment timeout/eviction、Session 事件的正式 runtime service；
- PAL facade、mailbox 拓扑接线仍为设计目标；Message/Queue/Task facade 已交付（Task 4），Thread 与 IO/VFS facade 已交付（Task 5），reload coordinator 与 Profiler bridge 已交付（Task 6），各自带独立 focused 测试矩阵（见 `runtime_thread_model.md` §5.3/§6.2、`runtime_hot_reload.md` §2.3）。

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

Lua 是唯一计划中的 runtime scripting language（`docs/design/roadmap_2026-10-22.md:7-12`）。Lua VM 所在线程拥有 `lua_State`；消息 handler 不把裸 Lua state 交给 Network/IO/Task worker。未来 Lua facade 只消费 LogicThread 上的 typed command/result，ECS 写入走 bounded batch command，不能直接持有 World、RHI、socket、native PAL 或任意 message queue 内部指针。Lua runtime facade 尚未实现。

## 4. 架构与 target 边界

### 4.1 目标 target graph（设计方向）

```text
engine (当前正式 C11 engine library)
  ├─ core/platform/task/asset/network 基础（已有）
  └─ [未来显式集成，需独立批准]
       runtime_core (coordinator + Message/Queue/Task/Thread/IO/Reload/Profiler contracts)
          ├─ ecs_runtime_bridge (snapshot/schema/delta/AoI/replication)
          ├─ session_runtime_bridge (break_net/Session)
          └─ application/framework consumers (C++11)

正式可选 targets（2026-10-22/23 Tasks 1-6 交付；不链入 engine/engine_demo/dxx_break）
  break_ecs_replication -> snapshot/schema/delta sources（非 Snowflake）
  break_replication_core -> AoI/replication/fragment sources（非 Snowflake）
  break_net -> Snowflake + adapter/session sources（BREAK_ENABLE_SNOWFLAKE=ON）
  runtime_core -> src/runtime/ 8 个翻译单元（engine/CMakeLists.txt:345-356）

test-only 变体（fault-injection hooks，生产库不带）
  break_ecs_replication_test (BREAK_WORLD_DELTA_TESTING=1) -> test_ecs_replication
  runtime_core_test (BREAK_RUNTIME_TESTING=1) -> test_runtime_facade/io/reload
```

关键规则：focused source 在实现正式 bridge 前不能移动进 `engine`，不能仅通过扩大 library source list 宣称完成。正式 target 必须有独立头文件依赖、link contract、normal/ASan/TSan 测试和 runtime/session E2E。

### 4.2 线程域

| 域 | 所有者 | 允许写入 | 消息出口 |
|---|---|---|---|
| LogicThread | application/runtime tick | mutable World/ECS、schema registry、Real/Ghost、Session manager、Lua state | Task/IO/Network/PAL command queues |
| Task worker | `TaskSystem` worker | worker-local scratch；只读 snapshot/delta/AoI calculation result | owned result message 到 LogicThread |
| Network reactor/adapter | Snowflake driver 或 Break host thread | transport state、adapter identity、event/outbound queues | copied `BreakNetEvent` 到 LogicThread |
| IO worker | future IO service | owned read/decode buffers、request state | `IO_COMPLETION` 到 LogicThread/asset owner |
| PAL/main loop | platform main-loop thread | Platform/Window/WSI/Input/IME state | platform event/command queues |
| Profiler recorder | calling thread + profiler internals | per-thread trace slots | bounded export/flush request |

LogicThread 是 mutable World/ECS/script/Session 的唯一 owner。Network callback 只验证、复制、入队；不调用 LogicThread、Session、ECS、Lua、UI、RHI。Task worker 只读取已经 retain 的 immutable snapshot/delta/AoI inputs；不能从 worker 调 `task_wait`。PAL/window/WSI 只在所属主线程执行。上述边界是对当前文档已有约束的正式化，不是新增实现。

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
LogicThread: finish systems + structural barrier
  -> build owned WorldSnapshot
  -> retain/publish snapshot handle
  -> Task worker: pure diff / AoI candidate calculation
  -> LogicThread: validate result, update Real/Ghost, schedule records
  -> replication message / fragment message
  -> Network queue: copy + bounded send
  -> adapter/Snowflake transport

Network callback
  -> validate envelope + copy bounded event
  -> adapter event queue
  -> LogicThread poll_adapter
  -> Session state transition / future replication input
  -> complete delta only after reassembly + base/schema/tick validation
  -> staging apply + atomic World replace
```

当前 `break_world_snapshot_build()` 要求 LogicThread/structural barrier，`break_world_delta_apply()` 已有 staging + atomic replace；未来 message model 只传这些 owned immutable values，不能绕过现有验证。

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
- Replication scheduler 在 LogicThread 拥有 Real/Ghost 和 connection state；Network 只拥有 copied command/event。queue full 后的 retry 不得重复递增 Real version 或重复改变 Ghost state。

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

Runtime shutdown 由 `runtime_overview.md` 定义的唯一 Runtime coordinator 发起；LogicThread/application 只能提交 stop 请求。全局状态和顺序不在本文件重复定义，Session/adapter/mailbox 的状态只是局部映射。Message 域只执行：停止 admission 后拒绝新 message；停止 producer 并发布 close/error watermark；关闭 mailbox、发出 bounded wakeup；在 coordinator 的 drain deadline 内 poll 有界 completion；把仍存活的 queue/worker ownership 交回 coordinator。任何 timeout 返回 `BREAK_RUNTIME_TIMEOUT`/`TIMEOUT`，不得强制 free 仍可能被 worker/callback 访问的对象；失败状态只允许诊断、cleanup 和安全 retry。

## 7. 正式化顺序与接口方向

### Phase A：先 formalize ECS/network boundary（target 拆分已交付 2026-10-22 Tasks 1-2；integration 仍未实现）

1. 已交付：snapshot/schema/delta/AoI/replication/fragment 的单独 formal library contract——`break_ecs_replication` 与 `break_replication_core`（`engine/CMakeLists.txt:313-333`）；现有 focused target 保留为 RED/GREEN 回归，未删除。
2. 已交付拆分：`break_replication_core` 为不依赖 Snowflake 的 policy/fragment 库；`break_net` 保留为可选 Snowflake adapter/session 库（链接 `break_replication_core` + `snow::net`）；Session 继续 LogicThread-only。注意 `break_replication.h` 仍引用 `break_net_adapter.h`，reactor send 符号由消费方最终链接解析。
3. 增加正式 publication service：LogicThread publish owned snapshot，workers retain；明确 mutex/atomic publication 和 shutdown epoch。当前文档明确此 service 尚不存在。
4. 增加 wire schema/tick/base fields 与 version negotiation；没有 schema negotiation 前不称为 production replication。
5. 增加 fragment timeout/eviction scheduler；当前 reassembler 只支持 reset/destroy，无 timeout/eviction。

### Phase B：Runtime Core foundation（部分交付 2026-10-22/23 Tasks 3-6）

1. PAL/Thread contract：Thread 已交付（Task 5 `runtime_thread.h/.c`：opaque handle、joinable lifecycle、bounded stop/timeout-retry，不暴露 OS type）；统一 PAL contract（time/deadline/platform capability）仍为设计目标。
2. Message registry/mailbox：owned message 与 bounded MPSC queue 已交付（Task 4）；固定 registry、per-kind byte budget、mailbox 拓扑接线仍为设计目标。
3. Task bridge：formal task facade 已交付（Task 4 `runtime_task.h/.c`，bounded pending queue、绝不 inline、owner drain 到借用 legacy TaskSystem）；worker 禁止跨域访问 World 的约束不变。
4. IO bridge：`runtime_io.h/.c` 已交付（Task 5：借用 VFS、owned completion、deadline/shutdown 可打断 wait、非阻塞 OVERLOAD）；decode 队列/typed blob 仍为设计目标。
5. VFS bridge：VFS 读取经 `runtime_io` 借用注入（128 MiB cap 沿用 `vfs.h`）；mount 管理进入 formal facade 仍为设计目标。
6. Profiler bridge：`runtime_profiler.h/.c` 已交付（Task 6：任意线程 record、owner collect/export 经现有 `profiler_export_chrome_trace()`、bounded presentation window）；`engine/src/core/profiler.c` 未动。

### Phase C：Application/Application bridge（未实现）

C++11 framework 在 `Init/Tick/DeInit` 建立 runtime；每 tick 由 LogicThread poll control、network、IO、task result，再按优先级运行 ECS apply/replication。Lua 只接收 LogicThread typed messages。编辑器/远程 RPC 必须另有 auth/security 设计，不能通过本 message model 默认放行。

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
2. LogicThread snapshot -> worker diff/AoI -> replication -> adapter queue -> loopback transport -> LogicThread apply 的真实调用链通过；
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
- `docs/design/session_protocol.md:1-19,21-84,174-237`：Session/adapter message ownership、256 queue、LogicThread-only 和 wire lifecycle。
- `docs/design/snowflake_c11_adapter.md:1-17,73-103,201-228`：Snowflake ownership、driver mode、bounded stop 和 failure cleanup。
- `engine/CMakeLists.txt:313-377,387-471,3235-3298,3405-3444`：正式 `engine` source、正式可选 targets 与 test-only 变体的真实构建边界。
- `engine/src/ecs/{replication_schema.h,world_snapshot.h,world_delta.h}`：C11 snapshot/schema/delta API 方向。
- `engine/src/network/{break_net_message.h,break_net_events.h,break_net_adapter.h,break_session.h,break_replication_fragment.h}`：owned/borrowed message、event/queue、Session、fragment API 证据。
- `engine/src/task/task.h`, `engine/src/network/net_loop.h`, `engine/src/asset/vfs.h`, `engine/src/core/profiler.h`, `engine/src/core/platform_thread.h`：现有 Task/IO/VFS/Profiler/PAL基础约束。

## 补充（2026-11-15）：correlation ID 已交付

§5 建议的 envelope 字段里，`correlation_id` 现在进入了 formal Runtime Core：

- `BreakRuntimeMessageView` 新增 `u64 correlation_id`，0 表示不关联。`break_runtime_message_copy` 把它存进 owned message，`break_runtime_message_view` 原样返回。现有构造点都先 `memset` 清零 view，所以默认仍为 0。
- `break_runtime_correlation_next()`（`engine/src/runtime/runtime_message.h`）是进程内唯一的 ID 源：一次 C11 原子自增，线程安全，从不返回 0，后一次调用的返回值一定大于之前所有调用。ID 只在本进程内唯一，网络对端不能把收到的 ID 当成自己的 ID。
- profiler bridge 新增 `break_runtime_profiler_record_correlated(profiler, name, id)`，`record()` 等于传 0。导出的 meta value 在 ID 非 0 时为 `tid=N ts=US cid=ID`，否则仍为 `tid=N ts=US`。`BREAK_RUNTIME_PROFILER_VALUE_CAPACITY` 从 56 增大到 80，最长的值（63 字节）不会被截断。同一条因果链在不同线程上记录的事件可以按 `cid=` 关联起来。

测试：`test_runtime_facade` 的 `message_copy_keeps_correlation_id`、`correlation_next_is_unique_across_threads`（4 线程 × 1000 个 ID，全部非 0 且互不相同），以及 `test_runtime_reload` 的 `profiler_correlated_events_export_cid`（跨线程共享 ID、0 不输出、`UINT64_MAX` 不截断）。

仍未做：`BreakNetEnvelope` 线格式里的关联 ID、Chrome trace flow 事件（ph:"s"/"f"）、统一 trace schema。计划：`docs/superpowers/plans/2026-11-15-runtime-correlation-id.md`。

## 补充（2026-11-22）：消息总线

§2.3 中的“消息类型 registry、per-kind byte budget、未知 kind/version 策略”和“mailbox 拓扑”现在有了 formal Runtime Core 实现：`engine/src/runtime/runtime_bus.{h,c}`，属于 `runtime_core` 与 `runtime_core_test`，仍不链入 `engine`/`engine_demo`/`dxx_break`。

- **kind registry**：`break_runtime_bus_register_kind` 登记 kind、可接受的最高版本（接受 1..max_version）、每 kind 的 payload 预算（不超过 `BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD`）和名字（1~31 个 `[A-Za-z0-9._-]` 字符）。最多 64 个 kind，重复登记返回 INVALID。
- **订阅**：订阅者有名字，持有自己的有界 `BreakRuntimeQueue`，并列出要接收的 kind（每个必须已登记，最多 16 个，不能重复）。总线只借用队列。最多 32 个订阅者；id 非 0 且不重用。
- **发布**：未登记的 kind 或版本返回 REJECTED，payload 超过预算返回 OVERLOAD，都不投递，并按总线或 kind 计数。合法消息按订阅顺序给每个订阅者复制一份 owned message，用队列的当前 generation 入队。发布者从不等待：队列已满、已关闭或复制失败时，只丢弃该订阅者的这一份，计入订阅者和 kind 的 `dropped`，其他订阅者照常收到；此时返回 OVERLOAD（背压），`*out_delivered` 给出实际入队的份数。
- **线程模型**：所有调用都可以在任意线程上进行。一把互斥锁串行化注册表和扇出过程，锁顺序固定为“总线 → 队列”，队列不会回调总线。所以 `unsubscribe` 返回后，总线不会再访问那个队列，队列所有者此后才能销毁它。`destroy` 要求没有其他调用在进行。
- **可观测拓扑**：`break_runtime_bus_export_topology` 输出一个 JSON 对象，包含未知 kind 计数、每个 kind 的登记信息与计数（published/delivered/dropped/version_rejects/size_rejects），以及每个订阅者的 id、名字、kind 列表、delivered/dropped 和其队列的 enqueued/dequeued/high_water/overload_rejects。

测试 `test_runtime_bus`（8 例）：登记校验与上限；按 kind 扇出且每个订阅者得到独立副本；未知 kind、版本越界、超预算、空指针；慢订阅者队列满时发布不阻塞、快订阅者不受影响、计数准确，排空后恢复，关闭的队列计为丢弃；订阅校验、退订、id 不重用、订阅者上限；拓扑导出内容与缓冲区不足时的长度；复制分配失败被计为丢弃；3 个发布线程各 2000 条消息，同时反复订阅/退订，每份消息不是投递就是计为丢弃，退订后队列计数不再变化。

仍未做：把 LogicThread、Task workers、Network/IO、PAL/MainLoop 和 Profiler 的现有队列实际接到总线上；按 kind 的优先级与配额（目前只有队列的 reserved control 容量）。

### 补充（2026-11-22）：按 kind 的优先级与配额

`BreakRuntimeBusKind` 新增两个字段（追加在末尾，已有的位置初始化方式不变）：
- `control`：该 kind 的副本带上 `BREAK_RUNTIME_MESSAGE_FLAG_CONTROL`，可以使用订阅者队列的 reserved control 容量。所以关停、故障这类 kind 在数据已占满队列时仍能送达。其他 kind 的副本由总线清除该标志，发布者设置了也无效，数据消息不能占用预留槽位。
- `max_per_tick`：两次 `break_runtime_bus_tick` 之间接受的发布次数，0 表示不限。超出配额的发布返回 OVERLOAD，不投递给任何订阅者，计入 `quota_rejects`，不影响其他 kind。`break_runtime_bus_tick` 通常每帧调用一次。

拓扑导出的每个 kind 增加 `control`、`max_per_tick` 与 `quota_rejects`。`test_runtime_bus` 新增 2 例（共 10 例）：数据填满队列后控制 kind 仍送达，且普通 kind 即使发布者设置了控制标志也进不了预留槽位；配额在 tick 之间限制发布次数，tick 后恢复，不影响其他 kind，并出现在拓扑中。上文「仍未做」中的“按 kind 的优先级与配额”由此交付；仍未做的是把各线程域的现有队列接到总线上。

### 补充（2026-11-22）：语音设备事件接入总线

这是第一个接到总线上的现有线程域。core_app 的语音 worker 线程原来只更新原子计数器（`capture_recoveries`、`playback_recoveries`、`capture_switch_*`、`capture_reopen_failures`），拥有者线程要靠每帧比较计数器才能知道发生了什么。现在 `core_app_voice_attach_bus(voice, bus)`（`engine/apps/core_app/core_app_voice.h`）让泵线程在每次设备事件时发布一条 kind `CORE_APP_VOICE_EVENT_KIND`（0x0701，版本 1，名字 `core_app.voice.event`）消息：

- payload 为 16 字节小端：`u32 type`、`u32 reserved`（必须为 0）、`u64 count`（事件发生后对应的统计计数器值；`CAPTURE_UNAVAILABLE` 为 0）。`core_app_voice_event_decode` 严格解码，长度不对、类型未知或保留字段非 0 时返回 false。
- 事件类型：采集恢复、采集重开失败、采集放弃（连续失败达到上限，worker 随后停止；每次 start 只发一次）、播放设备重开、采集切换成功、切换被拒绝、切换失败。
- 该 kind 登记为 control kind，所以订阅者队列被数据占满时，设备事件仍能使用预留的控制容量送达。
- 泵线程从不等待：订阅者队列满时，该份副本被总线丢弃，语音一侧计入 `CoreAppVoiceEventStats.undelivered`；`published` 计至少送达一个订阅者的事件数。
- `attach` 只能在语音停止时调用（运行中返回 REJECTED），传 NULL 解除。kind 尚未登记时由 attach 登记；已登记时，只有参数完全一致才接受，否则返回 REJECTED，避免两个组件对同一 kind 的理解不同。为此总线新增 `break_runtime_bus_kind_matches(bus, kind)`：参数完全一致返回 OK，不一致返回 REJECTED，未登记返回 STALE。

测试：`test_runtime_bus` 新增 `a_registration_can_be_compared`（共 11 例，逐项改变版本、预算、名字、control、配额）；`test_core_app_voice` 新增 3 例（共 24 例）：手动泵模式下各类事件按发生顺序送达且计数正确、放弃事件不重复；worker 线程模式下订阅者从不排空时 worker 照常恢复 5 次采集，前 2 次送达、后 3 次计为未送达；payload 严格解码与已登记 kind 参数不一致时拒绝 attach。变异检查：非 control、重复放弃事件、计数错误、保留字段与类型范围不检查、运行中允许 attach、接受参数不同的 kind、count 不编码、事件类型错误，以及 `kind_matches` 逐项比较，均被检出。`test_runtime_bus` 在 ThreadSanitizer 下无告警。

core_app 主循环随后改为订阅这些事件（2026-11-22）：语音通道创建自己的总线和一个 64 项（16 项预留给 control）的队列，`app_voice_report_switch` 每个 tick 在 CoreAppThread 上排空队列，用切换成功/拒绝/失败事件写出 `voice_capture_device` 追踪，替代原来对三个计数器的逐帧比较；其他设备事件被排空后忽略，总数仍由停止时的追踪给出。语音销毁后才解除订阅并销毁队列与总线。已有的 `test_core_app_voice_lane` 与 `test_core_app_voice_device` 端到端检查追踪内容，覆盖这次改动：把切换成功或拒绝事件的类型改错时，4 个语音用例都失败；去掉“只在有请求时追踪”的判断是等价变异，因为语音只会在 core_app 请求时切换设备。

仍未做：把 LogicThread、Task workers、Network/IO、PAL/MainLoop 与 Profiler 的现有队列接到总线上（这些队列各有自己的所有权与生命周期约束，需要逐个迁移）。

### 补充（2026-11-22）：总线丢弃与拒绝记入 Profiler

`break_runtime_bus_attach_profiler(bus, profiler)` 让总线把每一次丢弃和拒绝记为一个 profiler 事件，并带上消息的 `correlation_id`：`bus.drop`（订阅者队列满、已关闭或复制失败）、`bus.reject.kind`、`bus.reject.version`、`bus.reject.size`、`bus.reject.quota`。成功投递不记录。这样同一条因果链在 Chrome trace 中能看到它在哪里遇到了背压（`export_flows` 会把同一 cid 的事件连成 flow）。记录遵守 profiler 的热路径约定：不分配、不等待；profiler 环满时只计入它自己的 `overload_drops`，发布者照常立即得到 OVERLOAD。记录在总线互斥锁内进行；profiler 的互斥锁是叶子锁，不回调总线，所以锁顺序“总线 → profiler”不会死锁。传 NULL 解除；profiler 必须比挂接更长寿。

`runtime_core` 中的总线因此引用 `profiler_*`（来自 `engine`）。`core_app_runtime` 把 `runtime_core` 列在 `engine` 之后，单遍归档链接器（GNU ld）需要在使用者的链接行中再列一次 `runtime_core engine`（`test_core_app_voice`）。

测试：`test_runtime_bus` 新增 2 例（共 13 例）：投递成功不记录；队列满、未知 kind、版本越界、超预算分别以正确的名字和 cid 记录；未关联的丢弃不带 cid；解除后不再记录；超配额 10 次而 profiler 环只有 4 槽时，发布照常返回 OVERLOAD，profiler 记录 4 次、自身溢出 6 次。变异检查：去掉任一类记录、cid 丢失、解除不生效、事件名写错，均被检出。ThreadSanitizer 下无告警。

### 补充（2026-11-22）：任务完成接入总线

Task workers 是第二个接入总线的线程域。`break_runtime_task_queue_publish_completions(queue, bus, kind)`（`engine/src/runtime/runtime_task.h`）让每个经该队列转发的任务在 worker 上执行完回调后，发布一条 `kind`（版本 1）消息：payload 为 8 字节的任务 payload 序号（本机字节序），`correlation_id` 取自任务 payload（payload 为 NULL 时两者都为 0）。回调拥有并释放 payload，所以 trampoline 在调用回调之前读取这两个值。拥有者线程从自己的队列得知哪些工作已经完成，并能按 correlation_id 把完成通知与发起请求对应起来，不再需要轮询共享计数器。

- kind 必须已在总线上登记，且接受版本 1、预算至少 8 字节，否则返回 REJECTED。为此总线新增 `break_runtime_bus_kind_accepts(bus, kind, version, size)`：按登记表判断一次发布能否通过版本与大小检查（不考虑配额和订阅者队列）。
- worker 从不等待：订阅者队列满时通知被丢弃，计入 `BreakRuntimeTaskStats.completions_dropped`；送达至少一个订阅者的计入 `completions_published`。这两个计数由 worker 原子递增，不经队列互斥锁。计数放在独立的引用计数块里，队列和每个带总线转发的任务各持一个引用，所以拥有者收到最后一条通知后立即销毁队列也是安全的（2026-11-22 修复：trampoline 原来在发布之后还写队列里的计数，是 use-after-free）。
- 设置只对之后 drain 转发的任务生效（转发时把总线与 kind 记入任务节点）；传 NULL 解除。总线必须比所有已转发的任务更长寿。

测试：`test_runtime_facade` 新增 2 例（共 20 例）：4 个带 correlation_id 的任务和 1 个无 payload 的任务在 2 个 worker 上执行，拥有者收到 5 条通知，correlation_id 与序号一一对应，无 payload 的任务通知为 0；未登记的 kind 被拒绝；解除后任务照常执行但不再发布；拥有者队列只有 2 槽时 10 个任务全部执行，2 条送达、8 条计为丢弃。`test_runtime_bus` 新增 1 例（共 14 例）覆盖 `kind_accepts` 的版本与大小边界。变异检查：correlation_id 或序号丢失、丢弃计为送达、从不发布、接受未登记的 kind、解除不生效、接受版本 0、大小边界差一，均被检出（“解除不生效”第一轮未检出，因为测试用 kind 0 解除，而发布到未登记的 kind 0 本来就没有订阅者；改为用真实 kind 解除后检出）。`test_runtime_facade` 在 ThreadSanitizer 下无告警。

仍未做：LogicThread、Network/IO 与 PAL/MainLoop 的现有队列接入总线。

### 补充（2026-11-22）：IO 完成通知接入总线

IO workers 是第三个接入总线的线程域。`break_runtime_io_attach_bus(bus)`（`engine/src/runtime/runtime_io.h`）之后，每发布一个 IO 完成（worker 读完、读取失败或超时、`cancel`、shutdown 清空队列时的取消）都会再发一条 kind `BREAK_RUNTIME_IO_NOTICE_KIND`（0x4F4E，版本 1，名字 `runtime.io.notice`，control kind）的通知。通知是 24 字节小端：请求 id、状态、错误码、字节数；不含文件内容，文件内容仍随完成消息交给请求本身。拥有者因此可以只看一个队列就知道哪些读取已经结束，再去取对应请求的完成消息，不必逐个轮询。

- 三条路径都在 facade 互斥锁内、唤醒等待者之前发布通知，所以 `wait_completion`/`poll_completion` 一旦拿到完成，对应通知已经在总线上（或已计为丢弃）。总线互斥锁从不回调 facade，不会死锁。最初 worker 与 cancel 路径在解锁之后才发布：arm64 QEMU 上测试线程拿到完成后立即读统计，通知还没发出，`notices_dropped` 少计（CI run 44983968111）；调整顺序后修复。同一次 CI 还因超时退出（124）：测试用的拉取闸门只在 worker 进入等待前检查一次，已经在等待新请求的 worker 被唤醒后会越过刚关闭的闸门取走请求，shutdown 清空用例于是在 init 中等待残留 worker。现在 worker 每次被唤醒都重新检查闸门。本地以 2 核运行 32 份并发副本复现：修复前 32 份中 17 份失败或卡住，修复后 64 份全部通过，ThreadSanitizer 无告警。
- 从不等待：订阅者队列满时通知被丢弃。`BreakRuntimeIoStats` 增加 `notices_published` 与 `notices_dropped`，它们和总线挂接一样是进程级的（facade 本身就是进程级单例），跨 init/shutdown 累计。
- kind 尚未登记时由 attach 登记；已登记时参数必须完全一致（`break_runtime_bus_kind_matches`），否则返回 REJECTED。`break_runtime_io_notice_view` 严格校验 kind、版本和长度。传 NULL 解除。attach 换上新指针后，会等所有正在向旧总线发送的通知结束才返回，所以返回后可以销毁旧总线；worker 本身从不等待。不能在持有总线互斥锁时调用。

测试：`test_runtime_io` 新增 4 例（共 20 例）：成功、文件不存在、取消三种完成各发一条通知，状态、错误码、字节数正确；订阅者队列只有 2 槽时 6 次读取全部完成，2 条送达、4 条计为丢弃；解除后读取照常完成但不再发通知；通知解析拒绝错误长度、错误 kind 和空指针；shutdown 清空队列时的取消也发通知（拉取闸门一直关闭到清空完成，shutdown 在辅助线程上运行，所以该请求必定走清空路径）。变异检查：worker、cancel、shutdown 清空三条路径中任一条不发通知，状态或字节数不编码，丢弃计为送达，解除不生效，解析不检查长度或 kind，均被检出（shutdown 清空路径最初没有测试覆盖，补充用例后检出）。`test_runtime_io` 在 ThreadSanitizer 下无告警。

仍未做：LogicThread、Network 与 PAL/MainLoop 的现有队列接入总线。

### 补充（2026-11-22）：网络事件接入总线

Network 是第四个接入总线的线程域，分两层：

- `break_net`：`break_net_reactor_set_event_hook(reactor, hook, user)`（`engine/src/network/break_net_adapter.h`）。reactor 每产生一个事件（连接打开、收到消息、发送排空、连接关闭、传输错误）都会在产生它的线程上调用一次 hook：入队成功时 `queued=true`，事件队列已满被丢弃时 `queued=false`。hook 拿到的 `BreakNetEventInfo` 只有身份信息（类型、连接 key、原因，收到消息时还有消息 id、correlation_id 和负载长度），不含负载。调用时不持有 reactor 的锁。传 NULL 移除。
- core_app：`core_app_net_transport_attach_bus(transport, bus)` 在启动前挂接总线，transport 把 hook 收到的每个事件编码为 40 字节小端的 `CoreAppNetEventNotice`，以 control kind `CORE_APP_NET_EVENT_KIND`（0x0702，`core_app.net.event`）发布，消息带事件的 correlation_id。发布从不等待：订阅者队列满时丢弃该副本，计入 `CoreAppNetEventStats.undelivered`。kind 已以不同参数登记时 attach 返回 REJECTED，运行中 attach 也返回 REJECTED。runtime 通过新增的可选 hook `CoreAppNetworkHooks.attach_bus` 在 `network_start` 之前创建自己的总线和 256 槽队列，CoreAppThread 每个 tick 发布快照后取空队列，销毁网络时写出 `event=network_events seen=N reactor_dropped=M`。离线 core_app 不链接任何网络代码，这一路径也不改变。

测试：`test_break_net_adapter` 新增 1 例（共 45 例）：打开、带 correlation 的消息、队列满时丢弃的事件各上报一次且身份正确，移除后不再上报；变异检查（丢弃时不上报、丢失 correlation_id、丢失消息 id、移除不生效）均被检出。`test_core_app_net_transport` 新增 2 例（共 4 例）：事件按顺序出现在总线上，字段与 correlation_id 正确；只有 2 槽的订阅者队列使 4 条通知中 2 条计为未送达；运行中 attach 被拒绝；冲突的 kind 被拒绝。`test_core_app_network_loopback` 要求 `network_events` 的 seen 不少于 opened + closed，且 reactor_dropped 为 0（本地一次运行：opened=7、closed=7、seen=436）。transport 不调用 attach 时该用例失败；把每条通知都计为 reactor 丢弃时也失败。

仍未做：LogicThread 与 PAL/MainLoop 的现有队列接入总线。

### 补充（2026-11-22）：PAL/MainLoop 接入总线

平台层（`engine/src/platform/`）不链接 runtime_core，所以 PAL/MainLoop 不由平台后端直接发布，而是由主循环在每帧 `platform_poll` 之后读取平台事实，交给观察器：

- `engine/src/runtime/runtime_mainloop.{h,c}`（属于 runtime_core）：`break_runtime_mainloop_create(bus, &ml)` 登记 control kind `BREAK_RUNTIME_MAINLOOP_NOTICE_KIND`（0x4C4D，版本 1，24 字节，`runtime.mainloop.notice`），已以相同参数登记时复用，参数不同时返回 REJECTED。`break_runtime_mainloop_observe(ml, &facts)` 比较本帧事实（帧号、drawable 尺寸、关闭请求、WSI 状态、content scale）与上一次观察，按固定顺序为每项变化发布一条通知：CLOSE_REQUESTED（每次请求一次，持续挂起不重复，取消后再次请求会再发）、RESIZED（宽、高，最小化时为 0×0）、WSI_CHANGED（新状态、旧状态）、SCALE_CHANGED（千分之一单位）。第一次观察报告初始尺寸、WSI 状态和缩放。发布从不等待，订阅者队列满时丢弃并计入 `stats.dropped`；跟踪的状态总是跟随最新事实，丢掉的通知不会重发。非有限或负的缩放返回 INVALID。观察器属于主循环线程。实现不依赖 libm（不是所有 runtime_core 的使用方都链接 `-lm`，最初用 `lroundf` 时 CI 的 GCC 构建链接失败）。
- `engine/src/runtime/runtime_mainloop_platform.{h,c}`（不属于 runtime_core，与平台后端一起链接）：`break_runtime_mainloop_platform_facts(platform, frame, close_requested, &facts)` 从 `Platform` 读取 drawable 尺寸、content scale 与 WSI 状态。
- 编辑器主循环（`engine/apps/editor/editor_main.c`）每帧观察一次，退出时在 stderr 打印 `editor: main loop notices observed=N published=M dropped=K`。

测试：`test_runtime_mainloop` 5 例：初始状态只报一次、不变的帧不发布；多项变化按固定顺序各一条；仅高度变化也算 resize；关闭请求不重复、取消后再发；最小化 0×0 是 resize；2 槽队列时 7 条中 5 条计为丢弃，之后的变化相对最后一次观察计算；缩放为负或 NaN 被拒；冲突 kind 被拒；通知解析拒绝未知类型、错误长度和错误 kind。`test_runtime_mainloop_platform` 1 例：用无需显示器的 mobile 平台层（只有 `tests/runtime_mainloop_mobile_layer.c` 以 iOS 选择器编译 `window_mobile.c`，时钟与 profiler 仍用宿主平台实现；最初整个目标定义 `ENGINE_PLATFORM_IOS`，Windows 上 `time.c` 因此走了 POSIX 分支），`platform_mobile_resize` 产生 RESIZED 与 WSI_CHANGED（RESIZED 状态），`platform_mobile_notify_suspend` 产生 WSI_CHANGED（SUSPENDED，旧状态 RESIZED），关闭请求按调用方传入。变异检查（关闭请求重复发送、关闭请求不随取消清除、不报旧 WSI 状态、只比较宽度、丢弃计为送达、缩放截断而不是四舍五入、解析不检查类型上限、从不记录已观察）均被检出；“只比较宽度”第一轮未检出，补充仅高度变化的用例后检出。实机：Fedora Wayland 上以 `BREAK_EDITOR_INPUT_SCRIPT=ON` 构建的编辑器运行 `wait 30` + `quit` 脚本，Vulkan 后端，正常退出并打印 `observed=31 published=0 dropped=3`。编辑器内目前没有订阅者，所以初始的三条通知计为丢弃。

仍未做：编辑器内的订阅方（例如远程会话把窗口变化转告客户端）；LogicThread 的现有队列接入总线。

### 补充（2026-11-22）：LogicThread 订阅 IO 通知

前面各节让 worker、reactor 与主循环成为总线的发布方；core_app 的 CoreAppThread（core_app 中的 LogicThread，拥有 World、关卡与资源状态）现在是 IO 通知的订阅方。`core_app_run` 在 `break_runtime_io_init` 之前创建自己的总线和 32 槽队列（8 个 control 预留槽），`break_runtime_io_attach_bus` 挂接，订阅 `BREAK_RUNTIME_IO_NOTICE_KIND`。CoreAppThread 每个 tick 开始时取空队列；每次关卡场景读取完成时记下请求 id，每条通知都要能对应一个已完成的读取，否则计为 unknown。IO 停止后写出 `event=io_notices seen=N finished=M unknown=U dropped=D`（`io_stopped` 行保持不变），随后解除挂接并销毁总线；若 IO shutdown 超时，facade 仍可能发布，总线与 facade 一样保留。

测试：`test_core_app_lifecycle_load_unload` 要求两次关卡加载各有一条通知（seen = finished ≥ 2），unknown 与 dropped 均为 0。实测 `seen=2 finished=2 unknown=0 dropped=0`。变异检查：不挂接总线、不记录完成的请求、记录错误的请求 id，均使该用例失败。

至此，Task、IO、Network、PAL/MainLoop、语音和 Profiler 都已接到总线上，LogicThread 也作为订阅方接入。仍未做：编辑器内的主循环通知订阅方；core_app 之外（C++ framework 的 `Init/Tick/DeInit`）的 LogicThread 尚未消费总线。

### 补充（2026-11-22）：编辑器订阅主循环通知

编辑器 shell 成为主循环通知的订阅方。`break_editor_shell_attach_mainloop_bus(shell, bus)`（`engine/apps/editor/editor_panels.h`）登记 kind 并以 64 槽（16 个 control 预留）的自有队列订阅，同时只能挂接一次，重复挂接被拒；传 NULL 同步退订、销毁队列并移除面板行，之后可用同一总线重新挂接。`break_editor_shell_destroy` 在释放渲染面板之前也会解除。`break_editor_shell_tick` 每帧取空队列，记录最新尺寸、WSI 状态、缩放与关闭请求次数，渲染调试面板在固定的 9 行之后多显示一行 `window: <w>x<h> scale=<s> wsi=<状态> closes=<n>`（挂接后、收到第一条通知前为 `window: no notices`）。窗口状态按挂接代次隔离：重挂会清空可见性标记，尚未在本次挂接中收到的字段显示 `?`，不会沿用上一次订阅的旧值。通知文本更新遵守面板 250 ms 节流，只有新增或移除 `window:` 行才立即刷新。未挂接时面板行数与内容不变。`editor_main.c` 创建观察器后立即挂接，退出时先解除再销毁总线，stderr 行增加 `shell_received=N`。

测试：`test_editor_shell` 新增 `render_panel_shows_main_loop_window_notices` 与 `main_loop_shell_destroy_detaches_bus`，并扩展 `shader_reload_viewport_and_shell_shutdown_retry_same_owner`（`build-current-vk` 当前配置共 188 例）。挂接前后的行、两次观察后行内容随尺寸、缩放、WSI 状态和关闭请求更新，共收到 6 条通知，重复挂接被拒；解除后发布确有变化的事实，shell 的 `received/last_frame` 与其余面板行不变且 `window:` 行移除；同一总线可重新挂接并接收后续变化，重复解除安全。直接销毁仍挂接的 shell 后，公共 subscriber stats 对原 id 返回 STALE，topology 不再含 `editor.shell`；销毁 fail-early 后订阅仍收到初始 3 条通知，重试成功后订阅移除。该回归修复前在“解除后仍有 `window:` 行”断言失败（186 passed、1 failed、187 total），首次修复后 187/187；受控删除 destroy 内 detach 时直接销毁与重试两条用例均失败（186 passed、2 failed、188 total），恢复后 188/188。变异检查：不统计关闭请求、不更新 WSI 状态、允许重复挂接、解除不生效、tick 不取空队列，均被检出。实机：Wayland 上编辑器脚本运行输出 `observed=31 published=3 dropped=0 shell_received=3`（此前没有订阅方时为 `published=0 dropped=3`）。

2026-11-22 macOS 复核扩展同一窗口通知用例：连续变化后仅过 1 ms 时保留旧行，到 300 ms 时才刷新；脱离期间同时改变尺寸、缩放和 WSI，重挂后只发 close 通知，面板必须显示 `window: ? scale=? wsi=? closes=1`。旧代码分别在节流断言和重挂状态断言失败（各为 187 passed、1 failed、188 total）；两项修复后 188/188。

合并前复核（rebase 到远端 `e2f8136c`）：默认配置 Vulkan 444/444、OpenGL 442/442；ASan+UBSan 的 shell 188/188 与 fuzz 14/14；TSan 的总线、主循环和平台适配 3/3。Wayland/Vulkan 实机最新输出 `observed=31 published=4 dropped=0 shell_received=4`。本机 Fedora GCC 16.2.1/glibc 2.44 的完整 TSan shell 在 Lua console 受保护加载路径发生 `can't find longjmp buf` 工具运行时中止，不作为完整 TSan 通过收据，完整 TSan 由 Ubuntu 24.04 CI lane 复验。实机输入回放结束后恢复 `BREAK_EDITOR_INPUT_SCRIPT=OFF` 并验证发行配置契约。

远端验收（`4ac72d59a763e3be9c2127f9a940e7c5728cf4c6`）：CI run 45001336313、windows-d3d12 run 45001336382、proton-d3d12 run 45002398409 均成功。CI 的 27 个矩阵作业中 23 个成功、4 个按条件跳过；Ubuntu 24.04 的 `Linux + GCC (TSan, headless)` 完成构建和非图形测试，未排除 `test_editor_shell`，但仍排除既有的 `test_async_loader`。本批未改动 `QUIC Weak Network` 的触发路径，没有对应的运行记录。

仍未做：core_app 之外（C++ framework 的 `Init/Tick/DeInit`）的 LogicThread 尚未消费总线。


### 补充（2026-11-22）：C++20 framework 消费 IO 通知

语言版本先作追加澄清：本文较早段落中的 C++11 application/framework 是历史描述；当前根项目、`common_runtime` 和 `test_framework_runtime_bus` 均明确要求 **C++20**。引擎侧 Runtime Core 仍保持 C11，既有 C ABI 边界不变。

`bk::RuntimeBusApplication`（`framework/common/runtime_bus_application.h`）是 `BaseApplication` 的可选派生类，由独立的 `common_runtime` 静态库提供。该库链接 `common`、`runtime_core`、`engine` 与 `Threads::Threads`；只有显式选择它的应用承担这些依赖。默认 `empty` 不链接 `common_runtime`、`runtime_core` 或 `engine`。

- **所有权与订阅**：应用只借用调用方创建的 `BreakRuntimeBus`，自己创建并销毁一个 64 槽队列，其中 16 槽预留给 control 消息；订阅名为 `framework.application.io`，只订阅 `BREAK_RUNTIME_IO_NOTICE_KIND`。IO notice kind 的注册由调用方通过 `break_runtime_io_attach_bus` 完成，适配类不注册该 kind，也不拥有进程级 IO attach/shutdown。类显式禁止复制构造、复制赋值、移动构造和移动赋值；总线必须比所有挂接关系长寿。
- **初始化与重试**：`AttachRuntimeBus` 只接受未初始化且当前未挂接的状态。`Init` 先执行基类初始化，再建队列和订阅；任一步失败都会清理本次订阅/队列并保留已 Attach 的借用总线，修正 kind 缺失或订阅容量等问题后可重试。已初始化时重复 `Init` 返回 `BREAK_RUNTIME_REJECTED`。
- **Tick 与计数**：`Tick` 在调用它的所有者线程非阻塞排空队列，经 `break_runtime_io_notice_view` 解码后同步调用派生类的 `OnRuntimeIoNotice(const BreakRuntimeIoNotice&)`，不会在 IO worker 上回调。`RuntimeBusApplicationStats.io_notices` 累计合法通知，`malformed_notices` 累计版本、长度或 kind 等校验失败且未触发回调的消息；队列丢弃和高水位仍由总线/队列统计提供。
- **解除与关停**：`DetachRuntimeBus` 严格先退订，再销毁队列，最后清除借用指针。`DeInit` 与析构中的解除路径均可重复执行。运行中 Detach 只停止当前消费，不允许直接再次 Init；如需恢复，必须先 DeInit，再在下一次 Init 前重新 Attach。调用方先停止 IO 生产者，完成应用 DeInit、IO shutdown 和 `break_runtime_io_attach_bus(nullptr)` 后，才能销毁总线。

针对正式 `common_runtime` 的 `test_framework_runtime_bus` 当前有 9 个行为用例。实现者记录的 focused CTest 为 3/3（本测试、`test_runtime_bus`、`test_runtime_io`），根构建契约 `test_framework_runtime_build_contract` 为 1/1（default、enabled、engine-tests-default、engine-tests-enabled 四个子树），focused ASan/UBSan 与 TSan 运行也已通过。这些仅是当前 focused 证据；完整 Vulkan/OpenGL、ASan 非图形套件、fuzz、Windows/macOS/其他生成器以及远端 CI 尚待最终验收，不能提前记为全量通过。

因此，上一节及更早记录中“core_app 之外（C++ framework 的 `Init/Tick/DeInit`）的 LogicThread 尚未消费总线”这一具体缺口由本批关闭。这里交付的是既有 framework 生命周期对 IO notice 的可选消费：适配类不创建线程，不改变既有 LogicThread 的归属，也不表示所有消息类型都已接入总线。
