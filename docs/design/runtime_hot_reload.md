# Runtime Hot Reload 设计

## 1. 文档定位与状态词汇

本文是 Stage 2 Runtime Design 的设计文档，不是实现报告。Stage 2 的既定顺序是：

1. 先正式化现有 ECS snapshot/schema/delta/AoI/replication/fragment 与 `break_net`/Session 的 target 边界；
2. 再实现 PAL、Thread、Task、Message、IO、VFS、Profiler Runtime Core；
3. 最后在这些所有权、队列和生命周期合同之上接入资源、脚本和编辑器热重载。

本文使用以下状态词汇：

- **当前已有**：代码和文档中已有、可以引用真实文件或 target 的行为；不表示已完成产品级热重载。
- **focused/test-only**：由测试 target 直接编译或仅用于专项验证的实现，不能当作正式 `engine` runtime 集成。
- **设计目标**：本文建议的接口、所有权和验收合同，当前未实现除非另有证据。
- **未实现/风险**：明确不能由当前代码推断出来的能力；不得在实现前写成已完成。

路线依据：`docs/design/roadmap_2026-10-22.md:31-49` 将这些文件列为 Stage 2 输出，并要求映射到正式 CMake target、定义所有权/容量/背压/关闭和测试 lane；`docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md:14-24` 仍将本文和正式-vs-focused target review 标为未完成。

## 2. 真实代码与 target 证据

### 2.1 已有的运行时基础

- 正式 `engine` static library 在 `engine/CMakeLists.txt:387-471` 已包含 `src/core/profiler.c`、`src/platform/filewatch.c`/`filewatch_backend.c`、`src/asset/hotreload.c`、`vfs.c`、`async_loader.c`、`src/task/task.c` 和 `src/script/script.c`/`script_lua.c`。这证明这些模块进入了 engine target，但不证明它们组成了统一的 Runtime Core 或具有跨域热重载合同。
- `engine/src/asset/hotreload.h:5-36` 和 `hotreload.c` 当前提供 shader pipeline、texture 的开发期 watcher；shader 失败会保留旧 pipeline（`hotreload.c:43-54`），texture 失败不会替换旧 texture（`hotreload.c:111-163`）。当前回调在 `filewatch_poll()` 所在线程同步执行，并可直接调用 RHI；没有通用事件队列、版本号、提交 fence 或跨域调度合同。
- `engine/src/platform/filewatch.h:5-61` 提供 legacy 单文件 watcher，以及结构化递归 `FileWatch`。当前结构化 watcher 使用 `FW_EVENT_QUEUE_SIZE == 32`（`engine/src/platform/filewatch.c:12-14`），队列满时丢事件；Linux inotify overflow 只发一个 root `MODIFIED`，提示调用方 rescan（`filewatch.c:1054-1069`）。这必须被视为“提示/重新扫描”机制，而不是可靠变更日志。
- `engine/src/asset/vfs.h:5-73` 已有 DIR/PAK mount、最大 16 mount、`VFS_MAX_FILE_BYTES == 128 MiB` 和 PAK 读锁；`engine/src/asset/async_loader.h:36-87` 提供 IO worker、主线程 `async_loader_tick()` 回调、取消和 range/priority request。实现中的 completion queue 是 1024 项，request 上限也是 1024（`engine/src/asset/async_loader.c:16-24`），但这些容量目前不是本文所需的统一 Runtime Message contract。
- `engine/src/task/task.h:39-147` 定义 worker 每优先级 1024 项 Chase-Lev deque，外部 submit queue 为 256 项，并明确 TaskSystem 是进程单实例、worker task 不得调用 `task_wait()`/`task_wait_handle()`。`task.c` 的 C11 atomics 和 platform thread wrapper 是可复用基础；尚无面向 hot reload 的任务域、取消 token 或 reload transaction API。
- `engine/src/core/profiler.h:4-119` 的 profiler 已在正式 `engine` target；它有 120 帧、64 region、32 thread 的上限，并以 TLS 分配 thread id。它可为 reload transaction 记录 trace，但当前没有 reload-specific span、失败计数或 queue saturation 元数据合同。
- Framework 层是 C++11：`framework/interface/runtime_module_interface.h:21-30` 的 `RuntimeModuleInterface` 只定义 `Init/DeInit/Tick`。`docs/Architecture_Overview.md:102-110,188-217` 明确 engine 是 C11，framework/application/editor 是 C++11；本文不把 C++ 对象或异常带入 C11 Runtime Core。

### 2.2 Stage 2 必须先收口的 focused/test-only 边界

- `engine/CMakeLists.txt:313-324` 的正式可选 `break_ecs_replication` 承载 `ecs.c`、`replication_schema.c`、`world_snapshot.c`、`world_delta.c` 与 core logging（这些源不在正式 `engine` static library）；`test_ecs_replication` 经 fault-injection 变体 `break_ecs_replication_test`（`:3235-3249`，另含 `break_aoi.c`）编译。
- AoI/replication/fragment 由正式可选 `break_replication_core`（`engine/CMakeLists.txt:326-333`）承载；`engine/CMakeLists.txt:362-377` 的 `break_net` 在 `BREAK_ENABLE_SNOWFLAKE=ON` 时生成（独立于 `ENGINE_BUILD_TESTS`），并且 `engine_demo`/`dxx_break` 不链接它。
- `docs/design/ecs_snapshot_replication_aoi.md:5-20,148-159` 记录 snapshot/schema/delta/AoI/replication/fragment focused API 已实现，但正式 runtime/session integration、snapshot publication service、wire schema/tick、fragment timeout/eviction、认证仍未实现。
- `engine/src/ecs/world_snapshot.h:11-27` 的 snapshot API 要求从 GameThread-owned `World` 构建；`world_delta.h:39-63` 的 apply 通过不可变 snapshot diff 和 atomic replace 语义工作；`replication_schema.h:46-52` 的 registry 是可变注册表，非同步热路径对象。
- `engine/src/network/break_net_adapter.h:30-73` 和 `engine/src/network/break_session.h:64-103` 显式定义 adapter 的 256 项 event/outbound queues，以及 SessionManager 为 GameThread-owned、not thread-safe。`docs/design/session_protocol.md:32-84`、`docs/design/snowflake_c11_adapter.md:73-103` 禁止 network callback 直接调用 World/ECS/Lua/UI/RHI；消息必须 copy 后入队。
- `engine/src/network/break_replication_fragment.h:30-59` 的 reassembler 当前单 delta、16 MiB 总预算、checksum/duplicate/conflict/reset；`docs/design/ecs_snapshot_replication_aoi.md:134-146` 明确没有 timeout/eviction，FNV-1a 也不是加密认证。

因此，Stage 2 的第一道门不是“让 hot reload 直接调用这些 API”，而是先决定哪些 focused 源成为正式库、哪些继续 test-only，并给正式库补 target、ABI、生命周期和 sanitizer 证据。本文的 Runtime Core 只消费正式合同；在该门通过前不得声称网络 session 热重载已集成。

### 2.3 Runtime Core Task 6 已交付事实（2026-10-23）

以下事实由代码与测试证据支持，其余部分仍为设计目标：

- 正式可选 `runtime_core` static target（仍不链入 `engine`/`engine_demo`/`dxx_break`，`ENGINE_BUILD_TESTS=OFF` 可独立构建）新增两个翻译单元：`engine/src/runtime/runtime_reload.h/.c`（热重载 coordinator）与 `engine/src/runtime/runtime_profiler.h/.c`（profiler 桥接）。公共 API 只有 opaque `BreakRuntimeReload *`、u64+generation `BreakRuntimeReloadRequest`（0 非法，高 32 位为 slot generation）与 opaque `BreakRuntimeProfiler *`；无 World*/Archetype*/Chunk*/OS 线程句柄/Lua VM/RHI 句柄。
- **Reload 状态机**：brief 状态枚举逐字交付（`LOADING/VALIDATING/COMMITTED/FAILED_KEEP_OLD/CANCELLED/TIMEOUT/OOM`）。worker 线程经借用 VFS 读入 owned staging copy（16 MiB 预算，超限 → `FAILED_KEEP_OLD`），纯 validate hook 在 worker 上运行，commit hook 只在 owner 线程的 `break_runtime_reload_commit_owner()` 内运行；load/validate/commit 失败均 `FAILED_KEEP_OLD`（旧版本保持服务）。每个 request 恰好一次 terminal completion：poll 对非终态非消费、对终态消费并释放 slot（同 handle 再 poll/cancel → `STALE`）。
- **Coalescing 与 backpressure**：`break_runtime_reload_notify_file_event()` 是 FileWatch 唯一接缝（任意线程、复制路径、有界去重 hint 队列；同 path 合并计入 `events_coalesced`，新 path 满队列 → 非阻塞 `OVERLOAD`）；owner 线程 `pump_events` 把 hint 转为 request，同 asset 在飞时 head-of-line 延迟（`events_deferred`），在飞期间不覆盖旧 staging；request 层同 path 合并（`merged`）；request 准入为 live 计数 + pending ring 物理占用双闸门，满 → 非阻塞 `OVERLOAD`；commit 队列有界，满 → 该 request 落 `FAILED_KEEP_OLD`（`commit_overloads`），worker 不阻塞、不覆盖 live entry。
- **cancel/timeout/OOM/shutdown**：cancel 无分配路径（不可能半取消），QUEUED/LOADING/VALIDATING → `CANCELLED`（bump publication epoch，worker 迟到结果按 stale epoch 丢弃并计数 `stale_drops`）；已 CANCELLED 幂等 OK；owner 正在 commit（COMMITTING）或已有真实终态 → `REJECTED`；`request_timeout_ms` 处理 deadline 在 load 前检查 → `TIMEOUT`；staging 分配失败 → `OOM` 终态；`shutdown(timeout_ms)` 关闭 admission（→`CLOSED`）、把 QUEUED/LOADING/VALIDATING 全部 finalize 为 `CANCELLED`（terminal 态跨 shutdown 可 poll）、有界 stop/join worker，worker 超时或 owner commit 在飞（`commit_owner` 在 hook 期间放开 facade mutex）均返回 `TIMEOUT` 并保留 live ownership（不 free、保持 STOPPING、commit_owner 返回后重试可完成），因此跨线程 destroy 不可能在 owner commit 在飞时释放 facade；`destroy` 要求已 STOPPED（test 构建 fail-stop abort）。
- **Profiler 桥接**：`break_runtime_profiler_record()` 任意线程、不分配、不等容量、不跑 callback（有界 ring + 短 mutex），在调用点捕获 `profiler_current_tid()` 与微秒时间戳，满 → `OVERLOAD` 计数丢弃；owner/collector 线程 `collect()` 把事件移入有界 presentation window（满则丢弃计数，不覆盖 live entry），`export_meta()` 借用 window 填充 `ProfilerMetaInstant` 交给现有 `profiler_export_chrome_trace()`，`window_advance()` 由 owner 按 FIFO 退休已展示条目以释放 window 容量（持续 handoff，不是一次性缓冲区；不 advance 则 window 饱和后持续丢弃并计数）。`engine/src/core/profiler.c` 逐字节未动，现有 consumer 行为不变；span 记录仍由录制线程直接 `profiler_push/pop`（桥不在 collector 重放 span，避免排队延迟失真）。
- **现有 filewatch/hotreload 集成边界**：`filewatch.c`/`hotreload.c` 零改动；集成只靠消费者把 filewatch callback 接到 `notify_file_event()`、把 swap 逻辑放进 owner 线程 commit hook。端到端 watch→commit 接线（真实 watcher 驱动 coordinator）仍是设计目标。
- **Lua**：本任务无 Lua VM；Lua module reload 的 staging VM/版本保留策略属 Stage 3 依赖（见 §3.3、§9）。validate/commit hook 是当前唯一 staging 面。
- 验证：`test_runtime_reload` 32/32（coalescing、双闸门 overload、commit 队列 overload、failed-keep-old 三lane、stale generation、cancel 各相位、timeout、OOM 注入、shutdown/timeout 重试、跨线程 shutdown 撞上在飞 owner commit 保留所有权、owner-thread 强制、fork 子进程 destroy 合约 abort、profiler record/collect/export/window_advance/多线程交接/close），normal/ASan+UBSan/TSan 三树（`build-sdd-t6*`）全绿；生产 `runtime_core` nm 验证 0 个 test-hook 符号。报告：`.superpowers/sdd/2026-10-22-runtime-core-formalization/task-6-report.md`。

## 3. 语言、层次和边界

### 3.1 C11 Runtime Core

以下组件属于 C11 engine/runtime 侧，公开头文件使用 opaque pointer、项目类型 `u8/u16/u32/u64/usize`（定义见 `engine/src/core/types.h`）、定长/有界数据、返回值或错误码，不使用异常、RTTI、C++ templates 或 STL：

- PAL/thread/time/filewatch；
- Task、Message、IO、VFS、Profiler；
- reload coordinator、resource registry、versioned staging/commit；
- ECS snapshot/delta/replication 的正式化 C API（在 Stage 2 target boundary gate 通过后）。

C11 API 必须把借用 view 与 owned copy 区分开；跨线程只传 owned message、immutable snapshot、或明确 retain/release 的对象。所有加法、乘法、文件大小、队列计数和版本递增必须 checked；失败返回错误，不以截断、静默丢弃或伪成功继续。

### 3.2 C++11 framework/application/editor

C++11 只负责应用生命周期、编辑器 command routing、窗口/UI 所属线程以及把宿主事件翻译成 C11 command。`RuntimeModuleInterface::Init/Tick/DeInit` 是宿主调用点，不是 C11 子系统的线程共享 API。C++ 层不得把 `World*`、RHI 原生句柄或 Lua state 放入跨线程 queue；需提交 C11 command 或 snapshot。

### 3.3 Lua

Lua 是唯一计划中的 runtime scripting language，Lua VM 必须由一个明确的 Script/Game owner 线程拥有；但 Stage 2 这里只定义 boundary，不能要求当前已有 Lua VM/facade。`engine/src/script/script.h:39-60` 当前是有限的 `ScriptEngine`/`.script` API，`script_lua.c` 的存在不等于稳定 `BreakLuaRuntime` facade。本文只定义边界：Lua reload 请求进入 Game/Script owner 的 bounded command queue；新 chunk/module 在隔离 staging VM 或受控 staging state 中加载和校验；旧 module 在新版本成功提交前继续服务；失败只产生错误事件并保留旧版本。Lua 不直接访问 raw RHI、network reactor、ECS mutable World 或 UI。

`BreakLuaRuntime` facade、module dependency graph、sandbox、memory/instruction budget、C API binding 和 ASan/TSan lane 属于后续 Stage 3，本文不将其写成当前实现。

## 4. 目标架构

### 4.1 组件职责

```text
PAL/FileWatch -> IO/VFS -> ReloadCoordinator -> Staging/Validator
                                      |              |
                                      v              v
                               Message queues    Commit fence
                                      |              |
       Network/Session -> GameThread command <- Task workers (read-only)
                                      |
                   ECS World / Lua owner / RHI owner / Editor UI owner
```

- **PAL/FileWatch**：只产生有界、可丢弃的变更提示；不执行资源编译、ECS apply、Lua callback 或 RHI mutation。
- **IO/VFS**：以路径/asset id 读取受预算限制的 bytes；目录 mount/PAK mount 由 VFS 管理，资源 loader 不暴露 FILE* 或平台句柄。
- **ReloadCoordinator**：去重、合并同一 asset 的 burst events，分配单调版本，驱动统一状态机 `LOADING -> VALIDATING -> COMMITTED`，失败进入 `FAILED_KEEP_OLD`；取消、deadline 和分配失败分别进入 `CANCELLED`、`TIMEOUT`、`OOM`。
- **Staging/Validator**：worker 只生成 owned staging object；验证 schema、尺寸、依赖、shader reflection、Lua bytecode/模块约束和资源预算；不触碰 owner 状态。
- **Commit fence**：按 owner thread 提交 command；只有 owner 在安全点完成 swap，旧版本延迟到引用和 GPU/任务 fence 都释放后销毁。
- **Message/Profiler**：所有域间通知使用 typed owned message；每个 request/commit/failure 带 asset id、old/new version、source fingerprint 和 correlation id，Profiler 记录排队、加载、校验、commit、retire 时间。

### 4.2 所有权和线程模型

| 域 | 唯一 owner | 可做 | 禁止 |
|---|---|---|---|
| FileWatch/PAL | PAL poller 或专用 watcher producer | 产生路径事件、标记 overflow | 调用 Game/ECS/Lua/UI/RHI |
| IO/VFS | IO workers；VFS mount 生命周期由 Runtime owner | 读取/解码到 owned bytes | 写 World、调用脚本、替换 GPU资源 |
| Task workers | TaskSystem worker | 只读 snapshot diff、decode、validate | 等待自身 task；持有 owner-only handle |
| Game/ECS | GameThread | World mutation、schema registration、snapshot build、delta apply、reload command commit | 被 network/PAL callback 直接调用 |
| Session/replication | GameThread（当前合同） | poll adapter、Session transition、完整 delta validation/apply | network callback 直接改状态 |
| RHI/render | Render owner（当前应用帧线程；具体 backend 规则另行设计） | pipeline/texture swap、retire fence | worker 直接 destroy/use live GPU resource |
| Lua | Script/Game owner | module call、module commit、error policy | 网络/IO线程执行 Lua |
| Editor/UI | UI/window thread | 显示状态、发 command | 直接跨线程写 ECS/RHI |
| Profiler | 每线程写 TLS/当前帧槽，导出 owner 负责 | bounded region/metadata | 让 profiler export 反向阻塞 runtime |

当前 TaskSystem 是单进程单实例（`task.h:101-112`），因此 Runtime Core 不创建第二套 worker pool。当前 `BreakNetReactor` thread mode 只能由其 host thread 驱动，step mode 只能由一个 driver 调用；这些现有限制必须被 adapter facade 保留。

### 4.3 队列、容量和 backpressure

设计目标采用固定初始容量，并允许配置但不能无界增长。Runtime Core facade 满载统一非阻塞返回 `BREAK_RUNTIME_OVERLOAD`；compatibility API 的现有行为独立保留，legacy Task queue-full inline 仅是兼容事实。Network/IO/Audio/RHI 热路径禁止 inline 或等待，completion wait 必须可被 deadline/shutdown 打断：

| 队列 | 初始容量/证据 | 满载策略 |
|---|---:|---|
| FileWatch event queue | 32（当前 `filewatch.c:12-14`） | 丢弃重复/非关键提示，设置 `overflow/rescan_required`；下一次按目录重新扫描，不声称每个事件可靠 |
| Runtime reload request queue | 256（设计目标） | 同 asset 合并为一个最新 fingerprint；新 asset 入队失败返回 `OVERLOAD`，保留旧版本并记录指标，不阻塞 producer |
| Game/owner commit queue | 256（设计目标，与 `break_net` event/outbound 256 对齐） | 不执行 commit；staging 保留到 bounded TTL/取消，向请求方返回 overload |
| Task external submit | 256（当前 `task.h:68-83`） | `task_submit_ex` 必须返回显式失败/句柄无效；不得静默覆盖；worker 不等待队列空间 |
| IO completion | 1024（当前 `async_loader.c:16-24`） | producer 不覆盖未消费 completion；请求进入 FAILED/RETRYABLE，并由主线程观测 backlog |
| Network adapter event/outbound | 256（当前 `break_net_adapter.h:39-41`） | `BREAK_NET_SEND_OVERLOAD`/event drop 只影响网络记录；GameThread 不阻塞，replication 下次 sync 重试 |
| Fragment reassembly bytes | 16 MiB（当前 header:36-38） | fail closed；未来 scheduler 必须 timeout/evict，不能无限保留 incomplete assembly |

背压规则：变更提示是 lossy、请求/commit 是可观测失败、owned payload 队列绝不覆盖 live entry；任何 coalescing 都按 asset id/version 明确记录。禁止在 PAL callback、network callback、RHI callback 中睡眠等待队列空间。高优先级安全/生命周期消息可以使用独立保留槽，但不能绕过容量计数。

## 5. 热重载数据流和接口方向

以下是设计方向，不是当前 API 的已实现声明：

```c
/* Opaque C11 direction; names and ABI are subject to implementation plan. */
typedef struct BreakRuntimeReload BreakRuntimeReload;
typedef struct BreakReloadRequest BreakReloadRequest;
typedef struct BreakReloadVersion BreakReloadVersion;
typedef u64 BreakReloadRequestHandle;
typedef u64 BreakReloadGeneration;

typedef enum BreakReloadState {
    BREAK_RELOAD_LOADING = 0,
    BREAK_RELOAD_VALIDATING,
    BREAK_RELOAD_COMMITTED,
    BREAK_RELOAD_FAILED_KEEP_OLD,
    BREAK_RELOAD_CANCELLED,
    BREAK_RELOAD_TIMEOUT,
    BREAK_RELOAD_OOM
} BreakReloadState;

typedef enum BreakReloadResult {
    BREAK_RELOAD_OK = 0,
    BREAK_RELOAD_QUEUED,
    BREAK_RELOAD_OVERLOAD,
    BREAK_RELOAD_STALE,
    BREAK_RELOAD_INVALID,
    BREAK_RELOAD_CLOSED,
    BREAK_RELOAD_NOT_FOUND,
    BREAK_RELOAD_LOAD_FAILED,
    BREAK_RELOAD_VALIDATE_FAILED,
    BREAK_RELOAD_COMMIT_DEFERRED,
    BREAK_RELOAD_CANCELLED_RESULT,
    BREAK_RELOAD_TIMEOUT_RESULT,
    BREAK_RELOAD_OOM_RESULT
} BreakReloadResult;

typedef struct BreakReloadCompletion {
    BreakReloadRequestHandle request;
    BreakReloadGeneration generation;
    BreakReloadState state;
    BreakReloadResult result;
    BreakReloadVersion *version; /* owned by completion until release */
    u64 fingerprint;
} BreakReloadCompletion;

BreakReloadResult break_runtime_reload_request(
    BreakRuntimeReload *, const char *logical_path, u64 fingerprint,
    u32 flags, BreakReloadRequestHandle *out_request);
BreakReloadResult break_runtime_reload_poll(BreakRuntimeReload *,
                                            u32 max_events,
                                            BreakReloadCompletion *out,
                                            u32 *out_count);
BreakReloadResult break_runtime_reload_commit_owner(BreakRuntimeReload *,
                                                    u32 max_commits,
                                                    u32 *out_count);
BreakReloadResult break_runtime_reload_cancel(BreakRuntimeReload *,
                                              BreakReloadRequestHandle request);
void break_runtime_reload_completion_release(BreakReloadCompletion *completion);
void break_runtime_reload_request_release(BreakRuntimeReload *,
                                           BreakReloadRequestHandle request);
```

request handle 是 stream/reload instance 内唯一的 opaque `u64` token，实现必须带 generation 以拒绝 slot reuse；request submit 成功后 coordinator 持有 request ownership。poll 将 completion 和其中的 `BreakReloadVersion` ownership 转移给调用方，调用方必须调用 `break_runtime_reload_completion_release`；request release 只释放调用方持有的 request reference，不能释放已 poll 的 completion。cancel、poll、commit 在 `CLOSED`/`STOPPING`/generation 不匹配时返回明确结果，不产生空成功；completion 必须 exactly once。

方向性约束：

1. `logical_path` 先规范化并映射到 VFS asset id；原始 OS path 只留在 PAL/diagnostics。
2. file event 不携带借用指针越过 callback；coordinator 复制路径并生成 fingerprint（mtime 仅可作为提示，内容 hash/size 由 IO 验证）。
3. 同一 asset 在 `LOADING/VALIDATING` 时出现新版本，旧 staging 可取消；若取消不安全则新版本排队，永不将新 bytes 写入旧对象。
4. worker 产出 `BreakReloadVersion`，其中包含 owned bytes/decoded object、schema/dependency metadata、source fingerprint、版本号和错误信息；owner 只消费 immutable staging。
5. owner commit 先验证当前 live version 仍等于 request 的 `base_version`，否则返回 `STALE` 并重新排队/合并；提交顺序是 publish-new、切换引用、发布旧版 retire，不能先销毁旧版。
6. RHI 资源采用双版本或 handle indirection：GPU 使用完成前旧 resource 由 render fence 保留。当前 `hotreload.c:146-153` 直接 destroy old 后写 target，只能作为开发期同步路径，不能作为多线程 Runtime Core 合同。
7. Lua module commit 采用旧版保留策略；模块加载/校验失败不得替换旧 module。Lua 的真实 facade 待 Stage 3。
8. ECS schema 变化不是普通 asset swap：schema hash 变化必须建立新的 snapshot/delta epoch；在正式 schema negotiation/authority policy 前，拒绝把新 schema 直接应用到旧 stream。当前 `docs/design/ecs_snapshot_replication_aoi.md:74-79` 已明确 schema change 会改变 hash，online schema update 未实现。

### 5.1 典型流程

1. PAL poller 收到 `MODIFIED` 或 overflow/rescan hint；入队并去重。
2. Game/Runtime owner 在 tick 中 poll，向 IO queue 提交 bounded read；不在 callback 中加载。
3. IO worker 从 VFS 读取并解码；Task worker 做只读验证、shader reflection、schema/dependency 检查。
4. coordinator 将结果投递到对应 owner commit queue；Profiler 记录 request id。
5. owner 在安全点执行 compare-version、publish-new、fence-retire；失败则保留 old 并发布错误消息。
6. editor/UI、Session 或 Lua 只消费 owned status/event；它们不能反向调用 coordinator 的内部对象。

## 6. 关闭、失败和恢复

### 6.1 Shutdown 顺序

唯一 Runtime coordinator 发布全局状态 `CREATED -> STARTING -> RUNNING -> QUIESCING -> DRAINING -> STOPPING -> STOPPED/FAILED`；HotReload/Asset 的 `LOADING/VALIDATING/COMMITTED/FAILED_KEEP_OLD/CANCELLED/TIMEOUT/OOM` 只映射局部状态。统一顺序为：停止 Network/IO/Task external submit admission；停止 watcher/producer callbacks；关闭 mailbox/queues；drain bounded completions/close watermarks；join workers；最后 destroy IO/Network/RHI/PAL。任何 timed stop 返回 `TIMEOUT` 时必须保留 live ownership，由同一 coordinator retry，不能 free 仍被 worker/host thread 使用的对象。

这与现有 adapter 合同一致：`docs/design/snowflake_c11_adapter.md:201-225` 要求 terminate、观察 host exit 后 join/destroy；timeout 保留 STOPPING 和资源。Runtime Core 不得用 `pthread_join`/platform join 的无限等待伪装成 bounded shutdown。

### 6.2 失败矩阵

- watcher 初始化/OS error：记录 `WATCH_UNAVAILABLE`，允许显式 manual reload；不关闭非本模块 fd。已有 `test_hotreload` 验证 failed texture init 的 shutdown 不关闭 stdin（`engine/tests/test_hotreload.c:71-92`）。
- path 太长、文件超过预算、整数溢出、无效 VFS path：拒绝 request；不截断为另一个路径。现有测试已覆盖 shader/filewatch/texture path truncation（`test_hotreload.c:57-69,94-150`）。
- 文件不存在、读失败、decode/compile/reflection 失败：发布失败事件，旧版本保持可用。
- schema/base/tick mismatch：不 apply；delta staging 销毁，原 World 不变。现行合同见 `world_delta.h:14-21,57-63` 和 `ecs_snapshot_replication_aoi.md:61-72`。
- queue overload：formal facade 统一返回 `BREAK_RUNTIME_OVERLOAD`，合并可合并的同 asset event；不阻塞 producer，不把“排队成功”写成“已提交”。
- stale request：当前 owner version 已变化时丢弃 commit，保留 live object，重新从最新 source fingerprint 取数。
- worker panic/abnormal return：C11 callback 必须返回错误并释放 owned staging；不允许跨线程继续使用已取消 context。
- shutdown race：新请求统一 `SHUTTING_DOWN`；poll/commit 对空或停止对象 fail closed；所有 completion 必须带 generation/request id，防止 slot reuse 误投递。

## 7. 当前已有、focused/test-only、设计目标、未实现清单

| 主题 | 当前已有 | focused/test-only | 设计目标 | 仍未实现 |
|---|---|---|---|---|
| 文件监视 | `FileWatcher`、递归 `FileWatch`、Linux inotify/macOS kqueue/FSEvents/Windows API；Runtime Core reload coordinator 已交付有界去重 hint 接缝 `break_runtime_reload_notify_file_event()`（Task 6，可选库） | `test_hotreload` 直接编译 watcher/hotreload 源 | watcher 只发 bounded hint，coordinator 去重并可 rescan；真实 watcher → coordinator 的端到端接线仍未做 | 可靠跨平台 event journal、统一 overflow contract |
| Shader/texture reload | 开发期 pipeline/texture callback；失败保留旧对象；Runtime Core reload coordinator 已交付 staging→validate→owner-commit 状态机（failed-keep-old、cancel/timeout/OOM、恰好一次 completion，Task 6，可选库） | `test_hotreload` 使用 RHI stubs；`test_runtime_reload` 用 probe hook 验证 owner-thread commit | staging + owner commit + GPU fence + versioned registry | 多线程 RHI-safe swap、依赖图、生产资源 registry |
| VFS/IO | DIR/PAK、128 MiB file cap、async loader、range/priority | `test_vfs`、`test_async_loader` 等专项 target | IO/decoder/commit 分离，统一 backpressure/cancel | Runtime Core IO facade、跨域 cancellation contract |
| Task | C11 worker pool、work stealing、submit 256、单实例 | `test_task`/TSan lanes | reload job class、bounded submit result、可观测 cancellation | reload-specific scheduler policy |
| ECS snapshot/schema/delta/AoI | API 已实现、GameThread ownership；正式可选 `break_ecs_replication`（2026-10-22 Task 1，未链入 engine/demo） | `test_ecs_replication` 经 `break_ecs_replication_test` 变体编译 focused 源 | 接入 engine/runtime 前先交付 immutable version publication | formal runtime integration、schema negotiation/epoch |
| replication/fragment | Real/Ghost/AoI/fragment；16 MiB guard；正式可选 `break_replication_core`（Task 1） | `test_break_replication_fragment` 链接正式库与 Snowflake tests | owner scheduler 管 timeout/eviction、完整 wire contract | timeout/eviction、加密认证、authority/prediction |
| break_net/Session | C11 adapter、256 queues、GameThread Session、loopback；正式可选 `break_net`（Task 2，Snowflake-conditional） | Snowflake-enabled tests 链接正式 `break_net` | engine/demo 集成与 Runtime Message boundary | `engine_demo`/`dxx_break` integration、auth/Lua/editor RPC |
| Lua | `.script` engine、Lua source 与 `script_lua.c` | `test_script*` | owner-thread versioned module reload、old-version retention | `BreakLuaRuntime` facade 和完整 policy |
| Profiler | frame ring、per-thread tid、Chrome trace/sidecar | existing profiler tests | reload span/status/backpressure telemetry | reload-specific export schema |

## 8. 验证与验收

### 8.1 必须先通过的 target boundary gate

1. CMake 显式列出正式库与 focused/test-only 源；任何 `engine`、`break_net`、fragment library 的归属变化都要有 target contract test。
2. `engine_demo`/`dxx_break` 是否链接 formal ECS/network/session 由独立决策和构建证据确认；在此之前本文只称 focused/test-only。
3. 验证 schema hash、snapshot retain/release、delta atomic failure、AoI deterministic ordering、fragment reassembly、adapter/session queue ownership 均有 normal/ASan/TSan 结果。
4. `break_net` 若仍依赖 Snowflake，必须注明 `SNOWFLAKE_SOURCE_DIR` 和真实 `snow::net` target；不能引入 fallback transport。

### 8.2 Hot reload focused tests（设计目标）

新增测试应遵循项目现有 CTest 习惯，先 RED 再实现，至少覆盖：

- 同 asset burst events coalesce，overflow hint 触发 rescan；容量满返回 overload，不阻塞、不覆盖未消费 owned message。
- load/decode/validate 失败保留旧版本；compile failure、schema mismatch、bad fingerprint、stale commit 均可观测。
- owner commit 只在 owner thread 运行；worker、PAL、network callback 触发直接 mutation 的测试必须失败。
- old/new 版本引用计数、取消、slot generation、shutdown drain 和 timed retry 无 use-after-free、double free 或 lost wakeup。
- shader/texture 的 staging swap 在 GPU fence 前不销毁旧资源；当前同步 stub path 只作为 unit test，不作为并发证据。
- VFS 128 MiB cap、path length、整数 overflow、PAK concurrent read、async completion queue saturation。
- Lua facade（Stage 3）验证旧 module retention、错误回滚、禁止 raw handle；本文仅定义验收方向。

### 8.3 Sanitizer/运行时验收

- **Normal**：相关 formal target clean build；focused tests、reload unit/integration、真实 Snowflake loopback（可用时）通过。
- **ASan/UBSan**：覆盖 staging lifetime、queue drop/merge、VFS/decoder、fragment payload、shutdown/cancel、RHI old-version retire；不得以只运行 import/compile 代替真实 reload 流程。
- **TSan**：至少覆盖 FileWatch producer→reload queue、IO/Task completion→owner commit、adapter event queue→Session poll、Profiler per-thread registration；零 data race，特别检查 C11 atomic publication、mutex/cond 生命周期和 queue slot reuse。
- **End-to-end**：修改一个受监视 shader/texture 或测试 asset，真实经过 watch→read→validate→owner commit→旧版保留/retire；注入坏版本确认画面/对象仍使用旧版。ECS 端真实场景必须先构建 snapshot、生成 delta、完成 validation，再 apply；network 端只能由 GameThread `poll_adapter` 消费，不允许 callback 直接 apply。
- **证据纪律**：记录 build configuration、target、CTest 数量、ASan/TSan 输出和环境失败分类。`docs/Implementation_Status.md:26-39` 已说明当前 full CTest 可能缺少 fuzz executable、存在无关图形/UI failure；这些不能被混写成 hot reload 通过证据。

## 9. 后续依赖与实现顺序

1. **Formal target boundary**：更新 Stage 2 总体设计和 CMake contract，明确 ECS/network focused 源哪些进入正式库；本文不修改 CMake。
2. **Runtime Core contracts**：先定义 PAL/thread/time、owned Message、bounded queue、Task result/cancel、IO/VFS request、Profiler event 的 C11 headers 和错误码。
3. **Publication/commit primitive**：实现 immutable version、owner command queue、generation check、fence-retire；这是 shader/texture/Lua/ECS reload 的共同地基。
4. **Asset hot reload**：把现有 `hotreload.c` 的同步 callback 迁移到 staging/coordinator；保留失败保旧行为和 path/size guards。
5. **ECS/network integration**：在 formal target 和 schema/session contracts 通过后，接 snapshot publication、delta apply scheduler、fragment timeout/eviction 和 Session message routing。
6. **Lua Stage 3**：实现 `BreakLuaRuntime` opaque C11 facade、module version/reload/error policy，再允许 script reload 消费 Runtime Core。
7. **Editor Stage 4**：UI 只显示 owned reload status、发 command；不把编辑器 direct mutation 当作 runtime hot reload。
8. **Online update/security Stage 5**：签名包、远端更新、认证和 crash reporting 必须另有设计；本地 filewatch hot reload 不得复用为安全更新机制。

## 10. 未决风险

- 当前 filewatch 结构化队列只有 32 项且会丢事件；若只在其上加 callback，burst 修改会造成 silent stale state。必须保留 overflow/rescan 语义并让 coordinator 可验证最终 fingerprint。
- 当前 `hotreload.c` 直接替换 RHI handle；多线程 renderer 或 deferred GPU destruction 未由现有 API 证明。没有 fence/owner contract 前不能推广为生产路径。
- `WorldSnapshot` build 仍要求调用方建立 structural barrier；自动 publication service、epoch reclamation 和 schema negotiation 缺失，ECS 热重载不能绕过这些条件。
- `break_net`/Session 的 fixed 256 queues 和 GameThread-only API 很适合边界测试，但尚未是正式 engine runtime/session integration；把可选 library 直接当生产依赖（不经 integration 验收就链入 engine/demo）会制造错误的完成度声明。
- Fragment checksum 是 FNV-1a 完整性检查，不是认证；timeout/eviction 未实现。热重载或网络 delta 不能把它当安全更新校验。
- TaskSystem 单实例与 worker 禁止 self-wait 会限制 runtime shutdown 编排；需要明确 coordinator 的 owner/thread 和 drain 责任，避免 shutdown deadlock。
- VFS/async loader 的静态上限解决了无界分配的一部分风险，但 queue saturation、cancel 与 callback user-data 生命周期仍需统一合同。
- Lua、editor、online update、安全策略尚未实现；任何把“文件变化”描述为可执行 gameplay/editor/remote update 的设计都越过当前边界。
- 跨平台 filewatch backend（inotify/kqueue/FSEvents/Win32）事件语义不同，当前 macOS/非 Linux 的 runtime evidence 不能由 Linux focused test 推断。
