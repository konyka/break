# QUIC Datagram — 实时流量的不可靠通道 + Replay Window 接线

Status: **已交付**（2026-11-19，break_net_quic 数据报通道 + snow 上游 `f2a40587`）。本文是 break_net_quic 的实时流量切片，与流式通道（`docs/design/quic_transport.md`）并存。

## 1. 动机：为什么卸载

可靠流是「保证送达 + 严格有序」的昂贵保证。对实时流量，它带来的不是可靠性而是**队头阻塞（HOL blocking）**——丢包重传期间，后续所有字节排队等待，延迟被放大。

实时数据的特征是**时效性 > 完整性**：

| 流量 | 丢包时的正确行为 | 可靠流的代价 |
|---|---|---|
| 语音帧 | 直接丢弃，PLC 插值掩盖，播下一帧 | 等重传 = 卡顿，比丢帧更糟 |
| 位置/状态快照 | 新状态覆盖旧状态 | 重传旧状态 = 浪费带宽 + 增加延迟 |
| 认证/资产/命令 | 必须可靠有序 | 不适用（留在流上） |

QUIC 数据报（RFC 9221）提供「不可靠、不保序、不重传」的消息通道，但**参与拥塞控制**（CUBIC/BBR 正常降速）、**走同一套 TLS AEAD 加密**（安全性不降级）。它把「哪些字节必须到」的决定权交还给应用层——这正是实时流量需要的语义。

## 2. 流量分类与分工

同一 QUIC 连接内，可靠流与数据报并存，互不阻塞：

```text
┌─ 可靠流（已有，break_net_quic 流式通道）─────────────┐
│  认证（CHALLENGE/AUTH-v2）、资产、命令、聊天、配置     │
│  语义：保证送达 + 严格有序 + 信封序号严格递增          │
└─────────────────────────────────────────────────────┘
┌─ 数据报（本切片新增）───────────────────────────────┐
│  语音帧、位置/状态快照、实时遥测                     │
│  语义：尽力而为 + 不保序 + 应用层重放窗口去重         │
└─────────────────────────────────────────────────────┘
```

**分类原则**：只有「丢失可接受且过时无价值」的流量才走数据报。任何「必须到达」的消息留在可靠流上——分类错误比不卸载更糟。

## 3. 线格式设计

### 3.1 数据报消息格式

每个 QUIC 数据报承载一条自包含消息：

```text
[u8 type][u64 sequence（大端）][payload bytes]
```

- `type`：应用消息类型（与信封的 message_id 语义对齐，但数据报不复用信封的 18 字节头——数据报已经是消息边界，不需要长度前缀）
- `sequence`：64 位消息号（见 §4）
- `payload`：应用载荷，长度由数据报自身边界确定（QUIC 数据报是消息，不是字节流）

### 3.2 与信封的关系

数据报**不复用** `break_net_envelope` 的 18 字节头（magic/version/sequence/payload_size 四元组是为字节流设计的）。数据报有自己的消息边界，重复字段是浪费。但语义对齐：
- `type` ↔ 信封的 `message_id`
- `sequence` ↔ 信封的 `sequence`（但放宽为「允许乱序，重放窗口去重」，不再严格递增）

应用层消息注册表（`break_net_message_registry`）继续复用：同一个 message_id 在流和数据报上的语义必须一致（注册表加「传输类别」标记，见 §8）。

## 4. 消息号分配

- **64 位无符号整数**，每方向独立（client→server 与 server→client 各自计数）
- **从 1 开始**（0 保留不用，与 replay window 的语义一致）
- **严格单调递增**，不复用、不回绕（2^64 在宇宙寿命内用不完）
- 与信封序号**不共享**计数器（两个通道的序号空间独立）
- 连接重建后从 1 重新开始（重放窗口按 §5 的规则处理跨连接重放）

## 5. Replay Window 接线策略

复用已交付的 `break_replay_window`（`engine/src/network/break_replay_window.{h,c}`，RFC 4303 §3.4.3 风格，64 位滑动窗口）。该库 2026-10-30 交付时就明确预留了这个用途（transport_security.md §3 的 2026-10-30 决策）。

### 5.1 接线点

```text
数据报到达
   │
   ├─ 提取 type + sequence
   ├─ break_replay_window_check(window, sequence)
   │     ├─ DUPLICATE / TOO_OLD → 丢弃（计数）
   │     └─ OK → 继续
   ├─ （QUIC 的 AEAD 已在传输层验证过完整性，无需应用层 MAC）
   ├─ break_replay_window_check_and_mark(window, sequence)  // 登记序号
   └─ 投递给应用回调（按类型分派：语音解码器 / 状态快照应用）
```

### 5.2 窗口语义

- **窗口大小 64**（`BREAK_REPLAY_WINDOW_SIZE`）：允许最近 64 个消息内的乱序到达，过老/重复拒绝
- **每方向独立窗口**（client→server 与 server→client 各自维护）
- **序号 0 保留**（fresh window 的 highest = 0，序号 0 永远拒绝）
- **跨连接重放**：连接重建后序号从 1 重启，旧连接的包在新连接上无法通过窗口检查（窗口已初始化，序号空间不连续）

### 5.3 与 AEAD 的顺序

仓库既定纪律是 `check → MAC/AEAD verify → check_and_mark`（伪造包不能消耗序号）。在 QUIC 数据报上，AEAD 由传输层完成（QUIC 数据报帧本身就被 AEAD 保护），所以应用层只需 `check → check_and_mark`——不存在「伪造包烧序号」的攻击面（伪造者过不了 QUIC 的 AEAD）。

## 6. 尺寸边界

QUIC 数据报受**路径 MTU** 和 `max_udp_payload_size` 传输参数约束：

- 典型路径 MTU 1500 → QUIC 数据报可用载荷约 **1350 字节**（减去 QUIC 头 + AEAD 标签）
- **不分片原则**：超过数据报容量的消息**拒绝发送**（返回错误），由调用方决定走可靠流或自行分片
- 语音帧（Opus 典型 20–160 字节）和位置快照（几十字节）天然适配
- 发送侧在 `break_net_quic_datagram_send` 入口检查尺寸，超限 fail-closed

**为什么不自动分片**：分片需要重组状态机 + 部分丢失处理，把数据报的「简单」变成「另一个可靠协议」。需要大消息的流量本来就该走可靠流。

## 7. 与现有会话层的共存

- **认证**：CHALLENGE/AUTH-v2 仍在可靠流上完成（已交付，quic_transport.md §3）。数据报通道在会话认证后才对应用开放——未认证连接的数据报被丢弃（计数）
- **投递模型**：数据报通过**同步回调**（在 `step()` 的接收路径里直接调用应用回调），**不进入事件队列**。理由：实时数据不应排队等待；同步回调保持内存有界（无 per-conn 数据报队列）；回调必须快速返回、不能阻塞。这与可靠流的「事件队列 + 应用读取」模型不同——流式消息需要排队等待应用处理，数据报是「到达即处理」
- **信封序号**：可靠流的严格递增序号与数据报的重放窗口序号互不干扰（两个计数器、两个语义）
- **消息注册表**：同一个 message_id 可以在两种传输上注册，但语义必须一致（见 §8 的传输类别标记）
- **流控**：可靠流走 ngtcp2 的流控窗口（256 KiB，上游 `696a1ec5` 修复）；数据报参与连接级拥塞控制但不占用流控窗口

## 8. 消息注册表扩展

`break_net_message_registry` 的 `BreakNetMessageDefinition` 增加传输类别标记：

```c
typedef enum BreakNetTransportClass {
    BREAK_NET_TRANSPORT_RELIABLE_STREAM = 0,  /* 默认：可靠流 */
    BREAK_NET_TRANSPORT_DATAGRAM_OK,          /* 允许数据报（实时类） */
    BREAK_NET_TRANSPORT_DATAGRAM_ONLY,        /* 只允许数据报（语音/快照） */
} BreakNetTransportClass;
```

- 默认 `RELIABLE_STREAM`（向后兼容：现有消息不变）
- `DATAGRAM_ONLY` 的消息在可靠流上出现 = 协议错误（fail-closed）
- `DATAGRAM_OK` 的消息两种传输都接受（应用层自行决定优先级）

## 9. 安全模型

- **加密**：QUIC 数据报与流共用同一套 TLS 密钥（AEAD），安全性不降级
- **重放防护**：replay window（§5）覆盖应用层；传输层 AEAD 保证完整性
- **0-RTT**：如果未来启用 0-RTT 恢复，数据报可以在 0-RTT 中发送——但 0-RTT 数据报有重放风险（攻击者可以重放整个 0-RTT 飞行）。0-RTT 数据报必须是**幂等**的（位置快照是幂等的，语音帧也是；命令类不走数据报）
- **认证门槛**：未认证连接的数据报被丢弃（§7），不给未认证者消耗服务器资源的机会

## 10. 有界性台账

| 资源 | 上界 | 执行点 |
|---|---|---|
| 数据报载荷 | ≤ 1350 B（路径 MTU） | 发送入口拒绝超限 |
| Replay window | 64 消息位图（固定 64 位） | 库内固定 |
| 每方向窗口 | 1 个 `BreakReplayWindow`（8+8 字节） | 连接状态内嵌 |
| 未认证数据报 | 全部丢弃 + 计数 | 会话门控 |
| 消息类型 | 注册表登记（传输类别校验） | 注册表扩展（§8） |

## 11. 依赖与上游工作

**上游依赖已落地**（snow `f2a40587`）：`SnowQuicNgtcp2SendDatagram` + `recv_datagram` 回调 + `SnowQuicNgtcp2SetDatagramCallback`（运行时更新回调）。ngtcp2 的 RFC 9221 实现提供协议逻辑，snow 适配器透传，break 只做应用层接线——符合「引用不造轮子」原则。

实现要点：
- transport params 总是 advertise `max_datagram_frame_size=2048`（握手时交换，不能事后启用）
- 发送是单包直写、不排队、不重传；超过 1350 字节（含 type/sequence 头）fail-closed
- 接收经 `bnq_recv_datagram` 解析 type/sequence → replay window → 应用回调

## 12. 测试证据

全部真实 UDP loopback，port-0，条件轮询零固定 sleep：

1. **数据报回声**：`test_datagram_echo` —— 认证后的 client/server 互发数据报，验证 type/sequence/payload 完整到达（server_cap.count、client_cap.count 均 ≥1）
2. **尺寸边界**：`test_datagram_size_boundary` —— 1200 字节接受，1201 字节发送侧拒绝（不进入网络）
3. **未认证门控**：`test_datagram_unauthenticated_dropped` —— 未认证连接的数据报被丢弃（server_cap.count == 0）
4. **C++20 同步**：`test_break_net_quic_cpp20` 的 `run_datagram_echo` —— 封装层 `SendDatagram` / `SetDatagramHandler` 全链路验证

完整套件：`test_break_net_quic` 16/16（传输 8 + 会话 4 + 数据报 3 + 语音 1），C++20 封装 echo+auth+datagram 全过。

## 12.1 语音路径已迁移到数据报通道

`break_online_voice_quic.{h,c}`（2026-11-19）把现有的 BRV 编码语音路径从 raw UDP socket 迁移到 QUIC 数据报：

- **发送**：`break_voice_encode`（BRV1/BRV2）→ `break_net_quic_datagram_send`，payload 即完整语音帧
- **接收**：QUIC 数据报回调（`type == BREAK_VOICE_QUIC_MSG_TYPE`）→ `break_voice_receiver_push` → 现有 inbox + jitter buffer + 播放路径不变
- **收益**：语音流量获得 QUIC 的 AEAD 加密、CHALLENGE/AUTH-v2 认证门控、拥塞控制（不再裸奔在 UDP 上）
- **序号分层**：QUIC 数据报序号用于传输层去重/重放防护；语音帧序号保留在 BRV 格式内，用于应用层 jitter buffer 排序——两个序号系统各司其职
- **尺寸**：BRV1 最大 976 字节、BRV2 更小，均在 1200 字节数据报载荷限制内

测试 `test_voice_over_quic_datagram`：认证后客户端发语音帧（BRV1）→ 服务器接收器接受（inbox + pump + jitter buffer），服务器回发 → 客户端接受。

## 13. NOT delivered（本切片明确不覆盖）

- 数据报分片与重组（§6 解释了为什么不做）
- 0-RTT 数据报的启用（依赖上游 0-RTT 接线；当前未启用）
- 多流并行（语音与控制分流是数据报的职责，不需要多流）
- Windows/IPv6 支持（与 break_net_quic v1 的平台边界一致）
- WAN/弱网验证（loopback 证据不覆盖真实丢包/抖动环境）
- 乱序/重复/过老数据报的显式测试（replay window 的单元测试在 `test_break_replay_window` 里已覆盖；集成路径的乱序注入需要测试侧代理，留作后续硬化）

## 14. 文档关系

- 本文是 `docs/design/quic_transport.md` 的续篇（该文档 §9 的 NOT delivered 清单包含本切片）
- Replay window 的原始设计约定见 `docs/design/transport_security.md` §3（2026-10-30 决策：留给数据报传输）
- 消息注册表的扩展（§8）影响 `docs/design/session_protocol.md` 的消息语义描述
- 上游依赖（§11）见 `docs/design/snowflake_c11_adapter.md` 的集成策略

## 15. 评审要点

1. 流量分类原则（§2）是否清晰可操作？是否存在「必须到达但被错误卸载」的风险？
2. 消息号与信封序号的分离（§4）是否会造成应用层混淆？
3. Replay window 的 64 位窗口是否足够（语音 50fps 下 64 帧 ≈ 1.28 秒乱序容忍）？
4. 不分片原则（§6）是否会误伤某些合法的大消息场景？
5. 上游依赖（§11）的接口形状是否符合 snow 的演进方向？
