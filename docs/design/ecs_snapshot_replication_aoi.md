# ECS Snapshot, Replication and AoI

**Status:** Task 8 documentation for the currently implemented ECS/AoI slice. This document separates shipped behavior from planned transport and authority features. The focused schema/snapshot/delta/AoI/replication APIs are implemented; formal runtime/session integration is a separate boundary.

## Scope and Current Boundary

The current implementation is a C11, LogicThread-facing foundation:

- `replication_schema.*` registers deterministic component schemas and computes a stable schema hash from canonical component IDs.
- `world_snapshot.*` builds an owned, immutable copy of live entity handles and registered component bytes. Snapshot build remains a LogicThread operation after the structural barrier; there is no automatic ECS barrier.
- `world_delta.*` diffs two immutable snapshots and applies a validated delta through ECS-owned deep-clone staging and an atomic replace commit.
- `break_aoi.*` maintains a simple spatial index and computes deterministic `enter`, `stay`, and `leave` sets for one or more witnesses.
- `break_replication.*` tracks per-connection Ghost state, sends baselines/dirty/destroy/dormant records through `BreakNetReactor`, and enforces a byte budget.
- `break_replication_fragment.*` splits non-empty payloads under `BREAK_NET_MAX_PAYLOAD_SIZE` and reassembles one delta at a time after metadata, checksum, duplicate/conflict, and completeness validation. P8 adds caller-storage fragment views with a shared planner/fill. A monotonically newer delta supersedes an incomplete old delta only after all new metadata/first-fragment/result allocations succeed, otherwise the old stream is preserved. A persistent high-water also rejects older deltas after completion; explicit reset starts a new epoch.
- P8 `break_online_aspect.*` adds fixed aspect schemas, generation-aware stores, sparse change-mask packets and transactional apply with per-object record epochs. Explicit-epoch encoding is read-only, and apply advances record ordering without overwriting the public local-value revision. The compatibility `break_aspect_encode` owns a separate per-object automatic encoder high-water, committed only after successful output; callers must not switch back to automatic encoding after issuing a larger explicit epoch on that object. `break_online_aspect_replication.*` maps them onto the existing AOI enter/stay/leave sets with per-connection dirty state and fixed fragment metadata. Each actual send attempt gets a fresh epoch after budget/fragmentation preflight and before the first datagram; callback failure preserves that high-water and dirty state, while only complete success clears dirty. Ordinary scope leaves deactivate without retiring the reusable handle, while explicit object destruction still retires generation. The send callback is the authenticated transport boundary, not a replacement for Session security.

The formal optional libraries are `break_ecs_replication` (ECS schema/snapshot/delta plus ECS-owned AoI-independent dependencies and core logging) and `break_replication_core` (AoI, replication scheduling, and fragmentation). They are non-Snowflake targets and are available even when `ENGINE_BUILD_TESTS=OFF`; the umbrella header is `ecs/replication_runtime.h`. They are deliberately not linked into `engine`, `engine_demo`, or `dxx_break` until a runtime/session owner defines publication, authority, and thread-lifecycle integration. `break_ecs_replication_test` is a test-only composition carrying `BREAK_WORLD_DELTA_TESTING=1`; production libraries never receive that fault-injection macro. `break_net` remains an optional Snowflake adapter: it is produced whenever `BREAK_ENABLE_SNOWFLAKE=ON`, independent of `ENGINE_BUILD_TESTS`, and links `break_replication_core` and `snow::net`. P8 `break_online` is likewise optional and links `break_replication_core`; its actual aspect behavior and limits are recorded in `docs/design/online_session_network.md`.

Task 7 is implemented as a transport-independent fragmentation/reassembly layer. Fragment metadata carries `delta_id`, `base_id`, `fragment_index`, `fragment_count`, and a deterministic FNV-1a checksum over each fragment payload. The reassembler accepts out-of-order fragments, returns `INCOMPLETE` while fragments are missing, returns `COMPLETE` with newly allocated owned bytes only after every fragment is present, reports exact duplicate fragments separately from conflicts, rejects checksum/base/index/count/delta mismatches, and exposes explicit reset/destroy lifecycle operations.

The current Snowflake adapter remains an adapter boundary: it owns transport integration and bounded outbound queues, while the replication layer submits complete messages to `break_net_reactor_send`. Replication and fragmentation do not call Snowflake directly.

## Architecture and Data Flow

```mermaid
flowchart LR
    GT[LogicThread: mutable World]
    B[Structural barrier and completed ECS tasks]
    S[WorldSnapshot: owned immutable bytes]
    D[Pure WorldDelta diff]
    A[Witnesses + spatial index + AoI policy]
    R[Real objects + per-connection Ghosts]
    Q[BreakNetReactor outbound queue]
    N[Snowflake reactor / transport]
    GT --> B --> S
    S --> D
    S --> A
    A --> R
    D --> R
    R --> Q --> N
    N -. immutable events .-> GT
```

The intended lifecycle is: systems finish, the LogicThread establishes the structural barrier, the LogicThread builds a snapshot, and readers retain that snapshot while diff/AoI work runs. Snapshot build still requires that LogicThread/structural-barrier discipline; the builder does not insert an automatic barrier. The current snapshot builder is stop-the-world and owns all copied bytes; it stores no `World *`, archetype, chunk, RHI, or Scene pointer. Entity identity includes both `index` and `generation`, so index reuse is not mistaken for the same entity.

### Snapshot publication and delta application

```mermaid
sequenceDiagram
    participant G as LogicThread
    participant W as World
    participant S as Snapshot
    participant X as Worker/read-only consumer
    participant V as Validated delta

    G->>W: finish systems and enter structural barrier
    G->>S: build(tick, schema registry; no automatic barrier)
    S-->>G: owned snapshot (refcount 1)
    G->>S: publish/retain for consumers
    X->>S: diff immutable base -> target
    X-->>G: complete delta message
    G->>V: validate base/schema/records and tick monotonicity
    G->>V: deep-clone World into ECS-owned staging
    alt staging apply and final validation succeed
        G->>W: atomically replace contents; consume staging
    else mismatch, malformed, allocation/fault failure
        G-->>X: reject; destroy staging; original World unchanged
    end
```

Implemented snapshot identity is the deterministic hash of tick, schema hash, sorted entity handles, component IDs, and bytes. The schema hash uses canonical component IDs, so registration order does not change the schema identity. The current API exposes snapshot tick, ID/hash, entity lookup, component bytes, and retain/release. Publication is not yet a separate mutex-protected current-snapshot service; callers must retain the object they receive.

A delta retains its base and target snapshots, records entity create/destroy and component add/remove/update operations, validates the complete base world before staging, predicts entity allocation/generation before applying creates, and verifies the final target state. Delta apply requires a target tick greater than the base tick. `break_world_delta_apply` deep-clones the World using ECS-owned clone helpers, applies and final-validates only the staging World, then atomically replaces the destination contents. Any validation, allocation, mutation fault-injection, or final-validation failure destroys staging and leaves the original World unchanged. Clone allocation injection (`ECS_TESTING`) and mutation/final-validation injection (`BREAK_WORLD_DELTA_TESTING`) are test-only hooks, not production behavior.

## Component Schema Rules

A registered component declares component ID, version, size, alignment, flags, and optional encode/decode callbacks. Registration rejects duplicate IDs, zero sizes, invalid alignment, and raw-byte schemas marked pointer-containing. Snapshot raw bytes are accepted only for deterministic POD schemas with `BREAK_SCHEMA_FLAG_RAW_BYTES`; resource references, derived caches, and pointer-containing components are rejected by the snapshot policy.

The registry is initialization/LogicThread-owned. It is not a synchronized hot-path object. A schema change changes the schema hash and therefore requires a new compatible snapshot/delta stream; schema negotiation and online schema updates are not implemented.

## Real, Ghost, Witness, and AoI

- **Real:** `BreakReplicationObject` registered by the replication owner, with stable AoI entity ID, owner ID, position, flags, and priority. Payload/version state is owned by the replication object. Version increments fail closed at `UINT64_MAX`: `register` updates and `mark_dirty` reject before allocating or replacing payload state, preserving the old Real payload and all Ghost state. `UINT64_MAX` is terminal for that object; no epoch rollover is implied.
- **Ghost:** per-connection state recording whether a baseline was sent and the last sent object version. Ghosts are destroyed on disconnect and are not authoritative.
- **Witness:** connection interest source with position, direction, velocity, radius or AABB half-extents, hysteresis, connection ID, and priority.
- **AoI scope:** spatial candidates are filtered by always-relevant, owner-only, and dormant flags, deduplicated across witnesses, and `enter`, `stay`, and `leave` are all returned in deterministic priority-descending/entity-ID-ascending order. Leave ordering uses the current object priority from the spatial index while the object remains indexed. With no witnesses, non-dormant `ALWAYS_RELEVANT` objects enter scope only when they are not `OWNER_ONLY`; owner-only objects require a matching connection witness. Candidate cell bounds use `max(enter_hysteresis, leave_hysteresis)`, while exact inclusion selects enter or leave margin from prior scope membership.

```mermaid
flowchart TD
    W[Witness set] --> G[Grid cell candidates]
    G --> P[Relevancy and owner/dormant policy]
    P --> U[Union and deterministic priority/ID sort]
    U --> C{Compare previous scope}
    C --> E[enter: baseline]
    C --> T[stay: dirty update if version changed and budget allows]
    C --> L[leave: destroy or dormant]
```

The explicit set contract is `enter = new - old`, `stay = new ∩ old`, and `leave = old - new`. Sphere and AABB shapes, hysteresis, multiple-witness union, duplicate suppression, boundary validation, and safe rejection of non-finite/negative inputs are covered by `test_ecs_replication`. Replication scheduling then sends complete records through the Break adapter, prioritizing higher-priority objects and deferring records that exceed the connection budget or outbound queue capacity.

## Thread Ownership and Lifecycle

```mermaid
flowchart LR
    subgraph LogicThread
        W[World/ECS mutation]
        S[Snapshot build and retain]
        A[AoI and replication state]
        G[Apply only validated complete deltas]
    end
    subgraph ReadOnlyWorkers
        D[Snapshot diff]
        C[AoI candidate computation]
    end
    subgraph NetworkThread
        R[Snowflake/Break adapter]
        Q[Owned bounded event and outbound queues]
    end
    W --> S
    S --> D
    S --> C
    D --> A
    C --> A
    A --> Q
    R --> Q
    Q --> G
```

The LogicThread owns mutable `World`, ECS structural state, schema registration, Real objects, Ghost maps, and connection scope state. Snapshot and AoI consumers may read only owned immutable values. Network callbacks and reactor workers handle bounded message views/copies and queue events; they must not call World/ECS/Lua/UI/RHI or mutate replication state directly. The adapter has one driver per reactor (`BREAK_NET_DRIVE_STEP` or its host-thread mode), and shutdown is terminate, join when applicable, destroy reactor, then publish stopped. The adapter's `timeout_ms` is currently compatibility-only because the underlying thread abstraction has no timed join.

Replication version safety is fail-closed: an object at `UINT64_MAX` cannot be registered again or marked dirty, and the rejection occurs before payload allocation, freeing, or version mutation. This is a terminal-version policy rather than an epoch rollover; callers must replace the object identity if they need a new version domain.

Lifecycle on a connection is: open connection state, compute scope, send baseline on `enter`, send dirty versioned payloads on `stay`, send destroy/dormant on `leave`, and discard all Ghost state on disconnect. Queue overload is reported without blocking the LogicThread; a later sync can retry unsent baseline or dirty records.

## Fragmentation and Validation Boundary

The transport payload limit is `BREAK_NET_MAX_PAYLOAD_SIZE` (64 KiB), and the total reassembly budget is `BREAK_REPLICATION_MAX_REASSEMBLY_SIZE` (16 MiB). `break_replication_fragment_payload()` rejects empty or over-budget payloads, rejects a zero fragment size, reports a caller-selected fragment size above the transport limit as `OVER_LIMIT`, and emits non-owning fragment views into the caller's payload. The caller releases only the metadata array with `break_replication_fragments_free()` and must keep the source payload alive until fragmentation is finished.

Each emitted fragment carries:

- `delta_id` and `base_id`;
- zero-based `fragment_index` and common `fragment_count`;
- fragment byte length and FNV-1a checksum.

`break_replication_reassembler_create(expected_base_id)` owns one in-progress delta assembly. `push()` validates non-empty data, transport size, base ID, checksum, index/count bounds, and rejects fragment counts or metadata allocations beyond the 16 MiB reassembly budget before allocating per-fragment state; it also rejects any `total_size` growth beyond that budget. It then fixes the first fragment's delta ID/count as the assembly identity. Later fragments with another delta/count are conflicts. Exact duplicate bytes return `DUPLICATE`; same-index bytes with different size/checksum/content return `CONFLICT`. Fragments are copied into reassembler-owned storage, so the input view may be temporary. Missing fragments return `INCOMPLETE`; only the final validated set produces a newly allocated contiguous payload and `COMPLETE`. The caller owns that result and releases it with `break_replication_reassembly_free()`.

Completion clears the assembly state. An incomplete or failed final allocation leaves collected fragments available for retry; `break_replication_reassembler_reset()` explicitly discards that state, and destroy also frees all owned fragment storage. The focused API has no timeout or eviction policy: the owning replication scheduler must bound lifetime and call reset/recreate on loss or expiry. The checksum is integrity validation, not cryptographic authentication. No Snowflake call and no World mutation belongs in this layer. The LogicThread applies only the fully reassembled result after its own base/schema/delta validation; the fragmentation API itself does not enqueue or apply deltas.

## Implemented vs Future Work

| Area | Implemented now | Not implemented / future boundary |
|---|---|---|
| Snapshot | Deep copy, generation-aware handles, canonical-ID schema hash, deterministic hash, refcount lifetime; LogicThread/structural-barrier build contract | Automatic barrier, mutex publication service, epoch reclamation; formal runtime/session publication integration |
| Delta | Immutable diff, base-world validation, generation prediction, staging final validation, ECS-owned deep clone, atomic replace commit, unchanged-on-failure behavior | Wire schema/tick fields, authority protocol; formal runtime/session integration |
| AoI | Grid, sphere/AABB, witnesses, flags, hysteresis, enter/stay/leave | Distributed spatial cells, occlusion/LOD policy, prediction; formal runtime/session integration |
| Replication | Real/Ghost records, baseline/dirty/destroy/dormant, budget and queue retry | Full authority handoff and client prediction/rollback; formal runtime/session integration |
| Transport | Break adapter queue boundary and owned payloads; Task 7 fragmentation/reassembly, checksum, reorder, duplicate/conflict, base validation, owned output, reset | Real Snowflake registration/socket send integration, timeout/eviction scheduler, cryptographic authentication |
| Logic | No network-thread mutation; LogicThread-owned apply boundary | Lua callbacks, editor RPC, online updates, security/authentication |

Distributed Cell services, cross-World persistent NetEntityId, client prediction, rollback, authority handoff, Lua logic integration, editor tooling, online schema updates, and security policy are deliberately outside this slice.

## Validation

Focused validation uses `test_ecs_replication`, `test_break_replication_fragment`, and, when Snowflake is enabled, `test_break_replication`. Earlier fragment and Snowflake replication focused evidence was **7/7** in normal, ASan, and TSan lanes, with independent fuzz smoke evidence of **5/5**. The Task 7 closeout record (2026-10-23, clean `build-sdd-t7`/`build-sdd-t7-asan`/`build-sdd-t7-tsan` trees, `BREAK_ENABLE_SNOWFLAKE=ON`): the focused runtime/ecs/net lane passes **16/16** in each of the normal, ASan+UBSan, and TSan trees; all five fuzz executables are explicitly built and `ctest -L fuzz` passes **5/5**; the full non-graphics/non-fuzz CTest run has 178 selected tests with **177 passed, 0 failed, and 1 platform skip** (`test_d3d12_dependency_gate`, Windows-only lane) out of 187 registered tests. `test_break_replication_fragment` passed in every lane in this record; it carries a pre-existing intermittent flake note parked outside this plan's commits. The historical `test_myui_text_layout` Hebrew boundary failure did not reproduce (the test passed in the full run); `test_vulkan` is graphics-labeled and was not exercised in this host run. Documentation changes are checked with `git diff --check`.


## 补充（2026-11-20）：arm64 ECS/replication 验证

arm64 lane 新增 `test_ecs`（45 例）、`test_ecs_system`（6 例）、`test_ecs_replication`（35 例）与 `test_replication_target_contract`，统一选择达到四十二项。原生与交叉 focused 均为 4/4，快照/增量/AOI 和事务回滚用例直接经 QEMU 执行，目标契约保持宿主 CMake 源码结构检查。

选择使用 `test_ecs(_system|_replication)?$` 与 `test_replication_target_contract$`，局部结尾锚点覆盖整个名称，防止未来派生前缀自动混入。本项证据不外推为 world streaming、网络传输或全量 arm64 覆盖。


## 补充（2026-11-23）：分片重组超时与驱逐

`break_replication_reassembler` 新增调用者时钟驱动的超时原语：`break_replication_reassembler_push_at(r, fragment, now, …)` 在接受分片（含完全相同的重复分片）时记录未完成 stream 的最近活动时间，结果与 `push` 一致；`break_replication_reassembler_expire(r, now, max_idle)` 在空闲达到 `max_idle` 时丢弃未完成 stream 并返回 true（`now` 早于记录时间视为 0 空闲，`max_idle=0` 立即驱逐）；`break_replication_reassembler_pending_bytes` 报告其占用的负载字节（不含每分片元数据，后者另有至多 16 MiB 的预算）。被拒绝的分片（CONFLICT、CHECKSUM_MISMATCH、BASE_MISMATCH、失败的 supersession 等）不刷新活动时间，因此无效分片无法让 stream 长期存活；完全相同的重复分片会刷新，这是有意的取舍：FNV-1a 不是认证，能重放已接受分片的一方本来也能伪造新分片，内存上限不变。由普通 `push` 开始的 stream 为“未计时”，`expire` 不驱逐它，之后同一 stream 的 `push_at` 也不会开始计时；要使用驱逐，应始终用 `push_at` 喂入分片。high-water 保留：更旧 delta 仍为 CONFLICT，被驱逐 delta 的迟到分片与完成后一样重新开始。模块不读墙钟、不新增结果枚举值。上文“fragment timeout/eviction 未实现”中的**驱逐原语**由此交付；周期性调用 `expire` 的调度器以及与 session/网络的接线仍未实现。


## 补充（2026-11-23）：多 delta 并发重组池

`BreakReplicationReassemblyPool` 在既有单流重组器之上提供固定槽位的多 delta 并发重组，不改变旧单流 API 或“较新 delta 取代旧流”的语义。本切片新增：

```c
size_t break_replication_reassembly_pool_expire(
    BreakReplicationReassemblyPool *pool, uint64_t now, uint64_t max_idle);
void break_replication_reassembly_pool_reset(BreakReplicationReassemblyPool *pool);
```

池按 `delta_id` 路由，槽位数为 1..64，所有活跃流共享创建时的 `max_pending_bytes` 负载预算。满槽或新增负载超预算返回 `OVER_LIMIT`，不覆盖活跃流且拒绝前后状态不变；完全相同的重复分片不重复计预算。完成或过期推进“已退出高水位”的最大值：严格小于它的新流返回 `CONFLICT`，等于它的迟到分片可重新开始，已经活跃的较旧流仍可完成。`completed_delta_id` 标识实际完成的 delta，payload 仍由 `break_replication_reassembly_free()` 释放。

`expire` 逐槽复用单流计时契约，只驱逐达到阈值的计时未完成流并返回数量；重复分片只刷新自己的槽，校验失败或冲突不刷新，时钟回退按 0 空闲，`max_idle=0` 驱逐全部计时流。`reset` 清空所有流、pending 计数和高水位，与同配置新池行为一致，同时保留槽位容量、负载预算和 expected base。所有池 API 均为所有者线程语义，不读墙钟，不引入锁、线程或网络调用。

`test_break_replication_fragment` 现为 **22/22**。测试覆盖三流独立过期、复位对照、高水位单调性、交织时非零 pending 字节，以及带 pending 数据销毁。八项定向变异（错误路由、满槽覆盖、漏 completed id、共享预算不累计、重复计预算、expire 漏槽、过期不推进高水位、reset 漏清 pending）均成功构建并被行为断言判红。完整 Vulkan 为 462 项注册、458 通过、4 条件 skip、0 失败；OpenGL 为 453 项注册、449 通过、4 条件 skip、0 失败；ASan+UBSan（含显式 leak 检测）与 TSan focused 均为 22/22、无诊断。

本项只交付传输无关的池原语。周期性调用 `expire` 的调度器、session/网络接线、真实网络与生产服务验收仍未完成；FNV-1a 仍不是安全认证。


## 补充（2026-11-24）：池预算范围与恢复/丢弃完成验收

`max_pending_bytes` 只限制池内各活跃流已接收、尚未完成或驱逐的**分片负载字节之和**，不是进程总 RSS 上限，也不包含全部分配。每个槽的分片元数据仍独立遵循单流原有 `BREAK_REPLICATION_MAX_REASSEMBLY_SIZE`（16 MiB）上限；池最多 64 槽，这些元数据及固定槽存储不共享 `max_pending_bytes`。完成时的拼装临时缓冲不计共享 pending；已移交调用方的 payload 也不再计入，其所有权和释放责任仍属调用方。因此不能由该配置推断总 RSS 或所有暂存内存的上限。

新增 `reassembly_pool_expire_releases_shared_budget_for_retry`：8 字节共享预算下，delta 59/60 共占 6 字节，单分片 delta 61 首次为 `OVER_LIMIT`；只驱逐较低 id 的 60 后 pending 降为 2 字节，原 61 分片重试完成，活跃较旧 59 随后完成，最终 high-water 仍为 61 并拒绝新 delta 60。新增 `reassembly_pool_complete_with_null_outputs_discards_and_recycles`：单分片完成时 `completed_delta_id`、`payload`、`payload_size` 全部为 NULL，仍返回 `COMPLETE`、pending 归零，容量 1 的槽可接收下一 delta，且高水位拒绝较旧流。

本次只补测试和文档，生产代码未变。focused normal、ASan+UBSan（显式 LSan）和 TSan 均为 **24/24**，无 sanitizer/leak 诊断。
