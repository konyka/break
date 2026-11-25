# Runtime World Session Coordinator 生命周期绑定设计（2026-11-25）

## 目标与边界

在现有 `runtime_world_session` 可选边界内提供 `BreakRuntimeSubsystem` 注册，
用真实 `BreakRuntimeCoordinator` 串起 stop_admission、stop_producers、
close_queues、drain、join、destroy。通用 Coordinator 状态机不改。

只销毁 adapter；借用的 Bus、World Session、publication 由调用方最后清理。
不包含 snapshot/lease/BRWD/BRFG 数据面、core_app authoritative World、共享
live World、权威 simulation 合并、跨 World 身份或预测回滚。

## 方案比较

1. **adapter 提供 subsystem descriptor + 可选外部 hooks（采用）**。复用真实
   Coordinator 的按注册顺序和 TIMEOUT 精确恢复，adapter 自身不创建 worker。
2. 在 Coordinator 内写死 World 类型。会让通用 runtime_core 反向依赖 ECS/网络，
   破坏现有隔离，不采用。
3. 手工调用 close/drain/destroy。无法获得统一阶段、重试和外部 join 约束，
   是当前真实缺口。
4. 数据面或权威合并接入。需要新的身份、容量和权限协议，超出本项。

## API 与所有权

```c
typedef struct {
    u32 drain_budget; /* 0 = 32 */
    BreakRuntimeError (*stop_producers)(void *user_data);
    BreakRuntimeError (*join)(void *user_data);
    void *user_data;
} BreakRuntimeWorldSessionLifecycle;

BreakRuntimeError break_runtime_world_session_register_subsystem(
    BreakRuntimeWorldSession *adapter,
    BreakRuntimeCoordinator *coordinator,
    const BreakRuntimeWorldSessionLifecycle *lifecycle);
```

只能在 adapter 未关闭且 Coordinator 为 CREATED 时注册；否则 REJECTED。
`lifecycle` 可为 NULL，表示 budget=32、hooks 为 no-op。descriptor 和 hooks
均按值复制，user_data 借用。stop_producers/join 只表示调用方外部生产者或
transport 的 quiesce，不虚构 adapter worker。

注册成功后，adapter 的生命周期由 Coordinator 接管，调用方不得再单独
close/destroy，直到 STOPPED 后 adapter 已释放。注册失败不改变 adapter 或
Coordinator 的既有状态。

实现放在独立 `runtime_world_session_lifecycle.{h,c}`，仍属于现有可选
runtime_world_session target，不加入 runtime_core 源列表。

## 六阶段语义

- **stop_admission**：立即 `break_runtime_world_session_close`，阻止 direct
  submit；幂等，后续 close_queues 不重复产生副作用。
- **stop_producers**：调用可选外部 hook；NULL 为 OK。用于让外部生产者停止，
  不是停止 adapter 自身线程。
- **close_queues**：再次调用同一幂等 close，queue 保持可 drain。
- **drain**：以 lifecycle budget 调用 owner drain。结果按生命周期解释：
  - 实际 queue pending 或 control_pending 非零，或 drain 返回 OVERLOAD，均为
    `TIMEOUT`，不重跑前序阶段。
  - STALE/INVALID/REJECTED/CLOSED 已消费并计数；只要实际 pending 为零即
    可继续，不得造成永久 TIMEOUT。
  - 其他不可恢复错误原样返回，进入 Coordinator 既有 FAILED 路径。
- **join**：调用可选外部 hook；NULL 为 OK。首次 TIMEOUT 由 Coordinator 保持
  STOPPING，重试只恢复 join，adapter 不得提前 destroy。
- **destroy**：只有实际 pending 为零才调用 adapter destroy。成功返回 OK；
  false 映射为 TIMEOUT 且资源保留。重试不得重复 unsubscribe/destroy。

Coordinator 保证已完成的 stop_admission/stop_producers/close/drain/join 不在
TIMEOUT 后重跑；adapter 不另造第二套阶段状态。重复 stop 到 STOPPED 是 OK，
不重复 callback。

## 外部生产者与关闭竞态

direct submit 在 stop_admission 后立即 CLOSED。close 前接受的 direct 与外部
Bus 消息按 FIFO 恰好一次 drain；允许 drained 大于 direct submitted，pending
仍来自真实 queue enqueued-dequeued。

close 后、destroy 退订前，Bus 发布因 queue CLOSED 明确失败/丢弃可观测，不得
增加 pending；退订后发布 delivered=0。destroy 成功仍要求调用方已经停止并
join 外部生产者和 transport，adapter API 本身不是全面线程退出证明。

## 验证

- 真实 Coordinator + 真实控制桥记录六阶段顺序，STOPPED 后 adapter 已释放，
  Bus/session/publication 仍可查询并由调用方清理。
- drain budget 小于队列数时首次 DRAINING/TIMEOUT，后续从 drain 恢复，不重跑
  stop_admission/close。
- transport OVERLOAD 保留同一 control/level/epoch/cid，连续重试不越过 FIFO，
  applied 只一次；transport CLOSED 清 pending 后最终 STOPPED。
- 外部 Bus 与 direct 混合提交、close 前后投递结果、join TIMEOUT 后仅恢复 join
  并恰好 destroy 一次。
- “仅 queue 非零”和“queue+control_pending 非零”都不能提前 destroy；重复
  stop 不重复 callback。
- 定向变异：把命令级 STALE 错映射为永久 TIMEOUT、pending 未清就 destroy、
  join 重试重复 destroy，均须判红后恢复。
- focused normal、ASan+UBSan（显式 leak 检测）、TSan 和完整 Vulkan/OpenGL；
  独立任务与整分支评审后推送并核验远端矩阵。


## 修订（2026-11-25）：显式 binding 占用与 abandon 所有权恢复

通用 Coordinator 增加不改变状态机的精确注销：

```c
bool break_runtime_coordinator_unregister_subsystem(
    BreakRuntimeCoordinator *coordinator, const void *user_data);
```

仅 CREATED 或 FAILED 可调用；首个 user_data 指针精确匹配的表项被移除，其他子系统保序，state、last_error 与 resume 状态不变。NULL、未找到或其他状态返回 false。

adapter 在同一 mutex 下保存 lifecycle binding 占用、binding 指针和 lifecycle_destroying。注册采用 reserve→分配→attach→Coordinator register；同一或不同 Coordinator 的第二次注册均 REJECTED，分配/attach/注册失败回滚占用。已绑定 adapter 的直接 destroy 在任何 close/unsubscribe 前返回 false；只有 lifecycle destroy callback 可进入 destroying。失败保留 binding 并恢复可重试状态，成功才清占用并释放 adapter。

World 所有权恢复接口为：

```c
bool break_runtime_world_session_abandon(
    BreakRuntimeWorldSession *adapter,
    BreakRuntimeCoordinator *coordinator);
```

仅 CREATED 或 FAILED 可执行。abandon 在 adapter mutex 内先按 binding 精确 unregister，成功才清占用，随后在锁外 free binding；失败不得清 binding，之后可重试或继续正常 stop。RUNNING、QUIESCING、DRAINING、STOPPING、STOPPED、错误 Coordinator 或未绑定 adapter 均返回 false，双方状态不变。

正常路径是 register→start→外部 stop_producers/join quiesce→stop 到 STOPPED→destroy Coordinator，adapter 已由 lifecycle 成功销毁一次。若 Coordinator 未达 STOPPED而要销毁，调用方必须先 quiesce 外部生产者和其他 adapter API，再在 CREATED/FAILED 对每个 World adapter 执行 abandon，之后才能手动 close/drain/destroy adapter 并销毁 Coordinator。FAILED 后保留的 queue/control_pending 仍须按真实 pending 手动 drain，不能由 abandon 丢弃。

TIMEOUT 语义保持：前序已完成阶段不重跑，返回 TIMEOUT 的 callback 在下一次 stop 精确重入；join/destroy 可因此各进入多次，但成功 adapter destroy 只发生一次。借用的 Bus、World Session、publication 仍由调用方最后清理。本修订不增加数据面、自动 core_app World 接线或权威合并。


## 验证修订（2026-11-25）：ownership fix wave 证据

先 RED 后修复：Core 缺 unregister 编译 RED；World 同/跨 Coordinator 重复注册与直接 destroy 运行期 **27/30**，三项断言判红；abandon 缺 API 编译 RED。分阶段恢复为 Core **12/12**、占用修复 World **30/30**、最终 World **34/34**。RED 日志为 `task-2-fix2-core-unregister-red.log`、`task-2-fix2-world-duplicates-red.log`、`task-2-fix2-abandon-red.log`。

最终 normal、ASan+UBSan（显式 detect_leaks=1）和 TSan 的 adapter/Runtime Core/World/Session/bridge library 均 **12/12**，直接 Core 均 **12/12**、World 均 **34/34**，无 sanitizer 诊断。命令沿用本计划固定 pin 与 focused targets；完整输出保存在 `task-2-fix2-{normal,asan,tsan}-*.log`，自审与计数见 `task-2-report.md` Fix round 2。证据只覆盖本修订，不改写既有完整双后端或 TIMEOUT 收据。
