# Aspect session drain 设计（2026-11-24）

## 背景与边界

`break_replication_session`（master `3b775bd2`）已经把 BRFG 分片接入真实
session/reactor，并把完成包放进有界 FIFO，只有 owner 调用
`poll_completed` 才转移所有权。`break_aspect_apply` 在
`break_online_aspect.c:734` 起已经校验 BRA1 magic 与
`break_aspect_schema_hash(store)`。

本子项目只把二者接起来：完成包在 owner 线程被 drain 时才交给 aspect。
不接生产 core_app/editor，不定义 World delta，不做可靠恢复或完整资产链。

## 命名

沿用现有 `break_online_aspect*` 命名，并遵循仓库命名合同。
新文件 `engine/src/network/break_online_aspect_session.{h,c}`，类型与函数使用
`BreakAspectSession` / `break_aspect_session_*`。

## 结构

```c
typedef struct BreakAspectSession BreakAspectSession;

typedef struct BreakAspectSessionConfig {
    BreakAspectStore *store;                 /* borrowed, owner thread */
    BreakReplicationSessionBridgeConfig bridge;
} BreakAspectSessionConfig;

typedef struct BreakAspectSessionStats {
    size_t applied_packets;
    size_t rejected_packets;   /* BRA1/apply 校验或解码失败 */
    size_t drained_packets;    /* applied + rejected */
    BreakReplicationSessionBridgeStats bridge;
} BreakAspectSessionStats;

BreakAspectSession *break_aspect_session_create(const BreakAspectSessionConfig *);
void break_aspect_session_destroy(BreakAspectSession *);
BreakReplicationSessionBridge *break_aspect_session_bridge(BreakAspectSession *);
bool break_aspect_session_open(BreakAspectSession *, BreakConnectionKey);
bool break_aspect_session_close(BreakAspectSession *, BreakConnectionKey);
size_t break_aspect_session_tick(BreakAspectSession *, uint64_t now);
size_t break_aspect_session_drain(BreakAspectSession *, size_t max_packets);
void break_aspect_session_stats(const BreakAspectSession *, BreakAspectSessionStats *);
BreakRuntimeError break_aspect_session_send(BreakAspectSession *, BreakConnectionKey,
                                            const BreakReplicationFragment *);
```

- `open` 的 expected base 固定为 `break_aspect_schema_hash(store)`，调用方不能
  指定其它 base；`store` 为 NULL 或 schema hash 尚未可用时失败。
- `bridge` 配置里的 `reactor` 用于发送；`break_aspect_session_send` 的签名与
  `BreakAspectSendFn` 的语义对应（user_data 为 session），因此
  `break_online_aspect_replication` 可以直接把分片交给 bridge，再经
  `break_net_reactor_send` 发出，ID/版本固定 0x4009/v1。
- `drain` 只在 owner 线程运行：每次最多取 `max_packets` 个完成包，逐个调用
  `break_aspect_apply`，随后 `completion_release`；apply 失败计入
  `rejected_packets`，继续处理后续包，不把单包失败升级为连接关闭。
  `max_packets` 为 0 返回 0，不访问 store。
- 网络回调路径保持只入队：bridge handler 不接触 aspect store，drain 是唯一
  apply 入口。所有 API 都是 owner-thread，无新增线程/锁/原子。

## fragment_size 上限收窄

`break_online_aspect_replication.c:212-213` 目前允许
`fragment_size <= BREAK_NET_MAX_PAYLOAD_SIZE`(65536)。BRFG/v1 数据片上限是
65496（40 字节头）。把上限改为
`BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE`，使发送侧产生的分片必然能被
bridge 接收，不再依赖调用方自觉。超界配置返回 `BREAK_RUNTIME_INVALID`，与
现有语义一致。

## 验证要求（TDD）

1. 先写失败测试：fragment_size 65536 现在必须被拒绝；drain 之前 aspect store
   不出现对象；合法 BRA1 包经真实 socket 到达后，只有调用 drain 才 apply；
   schema hash 不匹配的包计入 rejected 且 store 不变；FIFO、字节上限、
   close 清理与 key 复用沿用 bridge 语义。
2. 变异：drain 在 handler 内 apply、跳过 apply 失败计数、open 使用错误 base、
   fragment_size 上限恢复 65536、drain 不 release completion，均须判红。
3. focused normal/ASan+UBSan(detect_leaks=1)/TSan，以及完整 Vulkan/OpenGL。
4. 文档追加新小节，保留生产接线、World delta、可靠恢复缺口。
