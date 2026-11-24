# 共享只读 World snapshot publication 与 fan-out 设计（2026-11-25）

## 目标与边界

每 tick 由 owner 在 ECS 结构屏障后构建一次 immutable snapshot，让多个连接
复用同一 target，同时让只读消费者安全取得当前 lease。关闭的是“库级只读
publication 和共享 snapshot fan-out”缺口，不是多写入者共享 live World。

不包含：跨线程传递 live `World *`、多连接 inbound drain 到同一 World、权威
simulation 合并、跨 World 持久身份、预测/回滚、Runtime bus kind、新网络
消息、自动换级、资产链、core_app 自动 rebaseline、无锁 publication 或通用
epoch-reclamation 框架。

## 方案比较

1. **短锁保护 current + 既有引用计数（采用）**。锁只保护 acquire 与
   replace/close 的短临界区；取得后由 snapshot 引用计数保证 lease 生命期，
   不需要另做回收框架。
2. 原子裸指针加 hazard/epoch 回收。能降低临界区成本，但引入新的内存回收
   协议和验证面，当前规模不需要。
3. 只允许 owner 获取 snapshot。实现最简单，但无法支持只读 worker 的
   diff/AOI，不能满足并发只读消费目标。
4. 多连接写同一个 live World。需要权限、排序和冲突仲裁，属于权威合并独立
   项目，不在本项扩展。

## Publication 对象与所有权

新增 `world_snapshot_publication.{h,c}`，不依赖 Snowflake、Runtime Core 或
网络库。CMake 给 formal/test replication 库显式传播 `Threads::Threads`。

```c
typedef struct BreakWorldSnapshotPublication BreakWorldSnapshotPublication;

typedef struct {
    u64 schema_hash;
    u64 level_generation;
} BreakWorldSnapshotPublicationConfig;

typedef struct {
    BreakWorldSnapshot *snapshot;
    u64 level_generation;
    u64 publication_epoch;
} BreakWorldSnapshotLease;

typedef enum {
    BREAK_WORLD_SNAPSHOT_ACQUIRE_OK = 0,
    BREAK_WORLD_SNAPSHOT_ACQUIRE_EMPTY,
    BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED,
    BREAK_WORLD_SNAPSHOT_ACQUIRE_INVALID
} BreakWorldSnapshotAcquireResult;

BreakWorldSnapshotPublication *break_world_snapshot_publication_create(
    const BreakWorldSnapshotPublicationConfig *config);
void break_world_snapshot_publication_destroy(
    BreakWorldSnapshotPublication *publication);
bool break_world_snapshot_publication_publish(
    BreakWorldSnapshotPublication *publication,
    BreakWorldSnapshot *snapshot, u64 level_generation);
BreakWorldSnapshotAcquireResult break_world_snapshot_publication_acquire(
    BreakWorldSnapshotPublication *publication,
    BreakWorldSnapshotLease *out_lease);
void break_world_snapshot_publication_close(
    BreakWorldSnapshotPublication *publication);
void break_world_snapshot_lease_release(BreakWorldSnapshotLease *lease);
```

create 只保存 config 并初始化短锁；首次 acquire 返回 EMPTY。publish 不消费
调用者引用，成功时 publication 自己 retain；acquire 在锁内 retain 并返回独立
lease，publication_epoch 从 1 开始随成功发布递增。

publish 的准入必须全部在替换 current 前完成：

- snapshot 非空、tick 非零、schema hash 等于 config；publication 未关闭且
  publication_epoch 不溢出。
- 新 level 小于 current 时拒绝；同 level 要求 tick 严格大于当前 snapshot。
- 更高 level 表示新流纪元，允许相同或更小 tick，也允许复用同一个 immutable
  snapshot 指针；旧 level lease 不得覆盖新 current。
- 任一失败都保持 current、level、tick 和 publication_epoch 不变。

publish/close 仅由同一个 owner 调用。acquire 可与其他线程的 acquire、owner 的
publish/close 竞态：close 在锁内标记 CLOSED 并移出 current，之前的 acquire
取得有效 lease，之后的 acquire 返回 CLOSED。replace/close 后旧 publication
引用在锁外 release，旧 lease 不受影响。

destroy 要求调用者先 close 并停止所有并发 publication API 调用；不承诺与
并发 acquire/destroy 自同步。lease 不保存 publication 指针，因此 publication
销毁后仍可读取并调用 `break_world_snapshot_lease_release`。lease_release 只
释放 snapshot 引用并清零 lease，NULL 和重复清零均安全。

锁内只做状态检查、retain 和指针/元数据更新。构建 snapshot、diff、AOI、
编码、网络发送、drain、用户回调、渲染和音频处理均在锁外；session 不接触
publication 或这把锁。调用方必须在进入热路径前取得 lease。

## Session 共享 snapshot fan-out

新增：

```c
BreakNetSendResult break_world_session_publish_snapshot(
    BreakWorldSession *session, BreakConnectionKey connection,
    BreakWorldSnapshot *target, u64 level_generation);
```

target 是调用方 borrow 的 immutable snapshot，不来自 live World 指针。
session 校验 target 非空、tick 非零、schema 与 session 一致、level 等于当前
session level；成功后由 attempt/history 按现有规则持有引用。每个连接分别
retain 同一 target，保持独立 full/delta、confirmed、history、ACK/NEED_FULL、
OVERLOAD attempt 和 rebaseline 状态。

现有 `break_world_session_publish(World *, tick)` 保持原行为：构建一个 owned
snapshot 后委托同一内部发布路径。新入口与旧入口在 attempt.active 时都优先
续发原不可变 attempt，不读取本次 target；没有 active attempt 才执行上述准入。
失败不得消耗 next_delta_id 或改变 confirmed/history。

publisher current 已前进不强制连接跳到 current。session 只能以该连接自己的
confirmed/newest-unacknowledged target 为 base 生成 delta，预算或未知基线仍
回退 full。publication_epoch 只是 lease 元数据，不进入 BRWD/BRWC，也不是
持久身份。

level rebaseline 后，旧 lease 仍可由只读消费者读取，但作为新代发布输入会
因 level 不匹配返回 INVALID；两连接均重新 full 并分别等待当前代 ACK。

## 验证

- publication：EMPTY/OK/CLOSED/INVALID、metadata、旧 lease 在 replace/close/
  destroy 后稳定、live World 修改不改变旧 snapshot、重复 release 清零。
- 准入失败原子：错误 schema/tick/level、close 后 publish 均不替换 current；
  epoch 溢出 guard 由代码评审检查。初始 level 可为 0；同 level tick 严格
  递增，高 level 开新纪元。
- 真实线程 close/acquire 竞态在 TSan 下只能得到有效 lease 或 CLOSED；
  destroy 在 join 后执行，旧 lease 最后释放。
- fan-out：两个连接共享 S1 full，只有 A ACK 后 A 可发 S1→S2 delta，B 仍 full；
  publisher 到 S3 时 B 仍用自己的 base；A OVERLOAD 不妨碍 B；release 本地
  lease 后 history 仍有效。
- rebaseline 旧 lease 拒绝但内容可读，错误 schema/tick/level 不改变 sender
  state；两个认证连接交错收片、延迟 ACK 和 NEED_FULL 的真实 socket 验收。
- formal target 链接契约证明新模块和线程依赖进入正式库，test hook 不进入
  formal target。每项生产缺陷修复附定向变异判红并恢复。
- 最终运行 focused normal、ASan+UBSan（显式 leak 检测）、TSan、完整
  Vulkan/OpenGL，独立任务与整分支评审后推送并核验远端矩阵。
