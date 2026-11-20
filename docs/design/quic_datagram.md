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
4. **Replay window 集成**：`test_datagram_replay_window_integration` —— 66 个唯一数据报各投递一次，序号 1 的即时重复和窗口外重发各被拒绝一次，应用计数保持 66、连接丢弃计数为 2
5. **三方语音会议**：`test_voice_conference` —— 三个认证客户端分别发送 1000、2000、3000 的 PCM 帧，服务器按连接 ID 混音为每样本 6000，再回发；三个客户端都播放出相同的 160 样本混合帧
6. **会议弱网**：`test_voice_conference_weak_network` —— 每客户端上下行各四帧，每方向第四个 UDP 包丢弃，其余包延迟 15 ms，首包延迟 30 ms 形成乱序；三个客户端仍播放出逐样本为 6000 的混合帧
7. **均衡随机弱网**：`test_voice_conference_seeded_weak_network` —— 种子 `0xB5EED123`，上下行各 25% 丢包与 0–20 ms 抖动，验证双方向丢包／抖动及正确混音
8. **上行高丢包**：`test_voice_conference_seeded_uplink_loss` —— 种子 `0xA11CE002`，上行 40%、下行 5%，验证上行实际丢包与双方向抖动
9. **下行高丢包**：`test_voice_conference_seeded_downlink_loss` —— 种子 `0xD00D1003`，上行 5%、下行 40%，验证下行实际丢包与双方向抖动
10. **C++20 同步**：`test_break_net_quic_cpp20` —— 封装层 echo/auth/datagram 全链路验证，并检查 `Conn::Id()`、`Conn::DroppedDatagrams()` 与 C 接口一致

完整套件：`test_break_net_quic` 23/23（传输 8 + 会话 4 + 数据报 4 + 语音 6 + lobby 1），连续重复运行 10/10 通过；四个独立弱网 CTest 连续重复运行 10/10 通过；C++20 封装测试通过；非图形 CTest 418/418 通过（2026-11-20，含四个独立弱网场景）。

## 12.1 语音路径已迁移到数据报通道

`break_online_voice_quic.{h,c}`（2026-11-19）把现有的 BRV 编码语音路径从 raw UDP socket 迁移到 QUIC 数据报：

- **发送**：`break_voice_encode`（BRV1/BRV2）→ `break_net_quic_datagram_send`，payload 即完整语音帧
- **接收**：QUIC 数据报回调（`type == BREAK_VOICE_QUIC_MSG_TYPE`）→ `break_voice_receiver_push` → 现有 inbox + jitter buffer + 播放路径不变
- **收益**：语音流量获得 QUIC 的 AEAD 加密、CHALLENGE/AUTH-v2 认证门控、拥塞控制（不再裸奔在 UDP 上）
- **序号分层**：QUIC 数据报序号用于传输层去重/重放防护；语音帧序号保留在 BRV 格式内，用于应用层 jitter buffer 排序——两个序号系统各司其职
- **尺寸**：BRV1 最大 976 字节、BRV2 更小，均在 1200 字节数据报载荷限制内

测试 `test_voice_over_quic_datagram`：认证后客户端发语音帧（BRV1）→ 服务器接收器接受（inbox + pump + jitter buffer），服务器回发 → 客户端接受。

## 12.2 多客户端会议接线

服务器的 QUIC 数据报处理器是**每服务器一个**的全局回调，不是每连接回调。多路会议只注册一次处理器，通过 `break_net_quic_conn_id(conn)` 取得非零连接 ID，并把 BRV 数据报直接交给 `break_voice_mixer_push(mixer, conn_id, ...)`；C++20 使用对应的 `Conn::Id()`。不要为每个连接重复调用 `break_voice_quic_attach_receiver_server`，后注册的接收器会覆盖前一个。

`test_voice_conference` 覆盖完整的会议往返：三个客户端完成 CHALLENGE/AUTH-v2 → 三路 BRV1 数据报进入各自混音源 → jitter delay 到期后求和且无削顶 → 服务器向三个已认证连接回发同一混合帧 → 三个客户端各自解码、播放并逐样本验证。

## 12.3 确定性弱网代理

`engine/tests/test_quic_udp_proxy.{h,c}` 是**仅测试使用**的 UDP 转发器，网络 I/O 复用 Snowflake `SnowUdpEngine`，不实现 QUIC、TLS 或丢包恢复协议。三个客户端各使用一个 port-0 代理通道，服务器因此仍看到三个独立源地址；认证完成后才启用故障注入。

- 每通道固定 32 个待发包槽位，每包最多 `SNOW_QUIC_NGTCP2_MAX_PACKET` 字节；槽位耗尽即丢弃并计数
- 延迟使用引擎 owner 线程的单调时钟与 service deadline，条件轮询驱动，无固定 sleep
- 到期包按 `(due_ns, ordinal)` 而非槽位顺序选择，避免高负载下多个包同时到期时退化为原顺序
- 每方向独立按包计数，第四个包丢弃；首包双倍延迟，统计只在后序包实际先发送时增加 `reordered`
- 测试断言每通道上下行均至少四个包、`dropped >= 2`、`delayed >= 6`、`reordered >= 2`，并验证丢包/乱序后的混合语音内容
- 代理只进入 `test_break_net_quic` 测试目标，不改变生产网络 API 或 C++20 封装

## 12.4 重复与过老数据报的端到端证据

`break_net_quic_conn_dropped_datagrams()` 提供每连接的认证／replay-window 拒绝计数，C++20 对应 `Conn::DroppedDatagrams()`。它独立于 listener 级别的聚合丢弃计数，测试可以等待到确切的过滤次数后再断言应用回调未多收。

直接复制 UDP 密文包不能覆盖本模块的 replay window：相同 QUIC packet number 会由 ngtcp2 更早去重。因此测试使用 `BREAK_NET_QUIC_TESTING` 下的 `break_net_quic_client_set_next_datagram_sequence_for_test()` 指定应用序号，让重复或旧序号进入**新的、正常加密的 QUIC 数据报**，再经真实 UDP 代理送达。该钩子仅在 `ENGINE_BUILD_TESTS=ON` 时编译，正常生产构建不包含它；拥塞重试时每次尝试都重置序号，避免测试自身产生序号跳变。

`test_datagram_replay_window_integration` 的顺序为：发送序号 1 → 以新 QUIC 包重发序号 1（DUPLICATE，拒绝计数 1）→ 发送序号 2…66 → 再以新 QUIC 包重发序号 1（age 65，TOO_OLD，拒绝计数 2）。最终应用回调仅收到 66 个唯一序号，最后序号为 66，代理自身没有丢包。

## 12.5 固定种子的丢包率与抖动分布

`test_quic_udp_proxy_set_random` 为每通道、每方向初始化独立的 xorshift32 状态，零状态有固定非零回退；上下行丢包率分别配置。每个到达包先取随机数执行 `value % 100 < drop_percent[direction]`，幸存包再取 `value % 21`，得到 0–20 ms 的均匀离散延迟。相同输入序列与种子因此产生相同的代理决策，不依赖全局随机状态。

| 场景 | 种子 | 上行丢包 | 下行丢包 |
|---|---|---:|---:|
| `test_voice_conference_seeded_weak_network` | `0xB5EED123` | 25% | 25% |
| `test_voice_conference_seeded_uplink_loss` | `0xA11CE002` | 40% | 5% |
| `test_voice_conference_seeded_downlink_loss` | `0xD00D1003` | 5% | 40% |

三个场景均为每客户端上下行各六帧，低于八帧 jitter capacity；代理队列全部排空后才做混音和播放断言。`dropped_by_direction` 用于断言每个配置为至少 25% 的方向确实发生丢包，`jittered_by_direction` 用于断言上下行都出现非零抖动；短样本的实际比例不被当作统计收敛证明。语音发送遇到拥塞时有界重试，BRV 帧内容及其应用序号保持不变；传输数据报序号允许因失败尝试产生间隔。

## 12.6 独立 CTest 场景

`test_break_net_quic` 支持 `--only <test-case>` 精确选择一个内部用例；未知名称或错误参数返回 2，不会静默漏跑。原无参数入口仍执行全部 23 项，保持现有本地工作流不变。

四个弱网场景另外注册为独立 CTest，名称依次为：

- `test_break_net_quic_voice_conference_weak_network`
- `test_break_net_quic_voice_conference_seeded_weak_network`
- `test_break_net_quic_voice_conference_seeded_uplink_loss`
- `test_break_net_quic_voice_conference_seeded_downlink_loss`

它们带 `weak_network` 标签，可与全量入口并行调度；因此非图形 CTest 总数由 414 增至 418，新增四项是有意的独立覆盖，不是测试清单误重复。

```sh
./build-review-now/test_break_net_quic --only voice_conference_seeded_downlink_loss
ctest --test-dir build-review-now -L weak_network -j4 --output-on-failure
ctest --test-dir build-review-now -R '^test_break_net_quic_voice_conference_seeded_uplink_loss$' --output-on-failure
```

## 13. NOT delivered（本切片明确不覆盖）

- 数据报分片与重组（§6 解释了为什么不做）
- 0-RTT 数据报的启用（依赖上游 0-RTT 接线；当前未启用）
- 多流并行（语音与控制分流是数据报的职责，不需要多流）
- Windows/IPv6 支持（与 break_net_quic v1 的平台边界一致）
- 真实公网与运营商弱网验证（当前仅本机 UDP 代理的确定性／固定种子丢包、延迟、乱序和应用序号重放，不覆盖真实路径）

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
