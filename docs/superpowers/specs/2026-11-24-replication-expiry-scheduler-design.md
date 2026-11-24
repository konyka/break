# 复制分片重组池周期过期调度设计（2026-11-24）

## 背景与目标

`BreakReplicationReassemblyPool` 已支持多 delta、共享预算和逐流 `expire(now, max_idle)`，但调用者必须自行记住何时调用 expire。下一个独立切片是在池内提供可选的、所有者线程驱动的周期调度，使常规 frame/tick 与分片入口都能执行有界维护。

本项不创建后台线程、不读墙钟、不接 session/网络。默认不启用调度，现有 24 项测试和手动 expire 行为保持不变。

## 方案比较

- **采用：池内可选调度策略。** 池已经拥有流活动时间、高水位和 reset 生命周期；增加 interval/max_idle 与调度纪元即可复用这些状态。`push_at` 在分片准入前维护，可在满槽时先释放已到期槽位。
- 独立 scheduler 对象包装 pool。能把策略与池分离，但引入 borrowed/owned 生命周期、额外分配和另一组 API，实际仍须转发同一批调用，收益不足以抵消复杂度。
- 后台线程定时 expire。需要锁、停止协议和跨线程所有权，违反当前池的所有者线程契约，也超出本切片需求。

## 公共契约

在现有 `break_replication_fragment.h` 增加：

```c
void break_replication_reassembly_pool_set_expiry_schedule(
    BreakReplicationReassemblyPool *pool,
    uint64_t interval, uint64_t max_idle);
void break_replication_reassembly_pool_disable_expiry_schedule(
    BreakReplicationReassemblyPool *pool);
size_t break_replication_reassembly_pool_tick(
    BreakReplicationReassemblyPool *pool, uint64_t now);
```

- `set_expiry_schedule` 启用或替换策略，`interval` 与 `max_idle` 使用调用者时钟的同一任意单位。`interval=0` 表示每次 tick 都到期，`max_idle=0` 表示到期 tick 驱逐全部计时未完成流。NULL 为空操作。
- `disable_expiry_schedule` 关闭自动维护并清除调度纪元，不影响已有流、手动 expire 或池配置。NULL 为空操作。
- `tick` 在调度启用时按周期调用现有 pool expire，返回本次实际驱逐数量；NULL、未启用或尚未到期间隔均返回 0。
- 启用/替换策略后的第一次 tick 立即检查，不等一个 interval。这允许对已有流启用策略后立即回收，也使空池的第一次 `push_at` 建立当前纪元。
- 后续 tick 只有 `now - last_tick >= interval` 才执行；`now < last_tick` 视为时钟回退，不执行也不修改纪元。长间隔只执行一次维护，不做无界 catch-up。
- 到期 tick 把 `last_tick` 推进到本次 `now`；手动 `pool_expire` 不改变调度纪元。
- `push_at` 在处理任何分片（包括随后会被拒绝的分片）前先调用一次 tick。因此过期维护发生在准入、预算与容量判断之前；拒绝本身仍不刷新流活动时间。除这次独立的到期维护外，原失败原子规则不变。
- `pool_reset` 清空流和高水位，保留调度 enabled/interval/max_idle 配置，但清除调度纪元；reset 后第一次 tick 立即检查。
- 调度与池一样只能在所有者线程串行调用，不新增分配、锁、原子操作或线程。

## TDD 与验收

在 `test_break_replication_fragment` 先新增测试并确认编译 RED：

1. **间隔与活动时间**：启用 interval=10/max_idle=5 后，第一次 push 建立纪元；间隔未到不驱逐；重复分片刷新自己的活动时间；到期 tick 按实际 idle 驱逐并返回准确数量。
2. **准入前维护与 reset**：容量 1 的池在间隔内拒绝新流，下一次到期 push 先驱逐旧流再接受新流；reset 后策略仍启用但第一次 tick 立即执行。
3. **零周期、禁用与重新启用**：interval=0/max_idle=0 每次 tick 都清理；disable 后即使时间前进也不自动清理；重新启用后的第一次 tick 立即按既有活动时间清理。
4. **时钟回退与多空槽**：回退不触发且不改纪元，恢复到原时间轴后按原间隔执行；一次到期 tick 可驱逐多个槽，长间隔不重复 catch-up。

实现到 GREEN 后做定向变异：首次 tick 错等一个周期、间隔比较差一、push 在准入后维护、时钟回退无符号回绕、disable 不清配置、reset 丢失策略或纪元、长间隔 catch-up。随后运行完整 Vulkan/OpenGL、项目选项 ASan+UBSan/TSan focused，追加设计/状态/缺口文档，独立评审后推送并核验远端。

## 明确边界

本项只交付确定性调度原语。应用仍需在 owner tick/frame 中调用 `pool_tick`，或经 `push_at` 触发维护；没有流量且应用不 tick 时不存在隐式后台维护。session/网络接线、真实网络和生产服务验收仍未完成。
