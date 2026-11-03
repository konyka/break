# Online Gameplay Network 当前实现事实

日期：2026-11-03

## 1. 目标与边界

P8 的正式可选静态库是 `break_online`，源码位于 `engine/src/network/break_online_*`。它不链入 `engine`、`engine_demo`、`dxx_break` 或编辑器，消费方显式选择该库。库 PUBLIC 依赖 `Threads::Threads` 与既有 `break_replication_core`；UDP 的 `net_*` 符号继续由既有 `network.c` 在最终消费链接中提供，没有第二套 socket、可靠传输、认证、安全分片或 AOI 实现。

可变大厅、NAT 协议、语音播放和 aspect 状态均由创建线程（接入时为 GameThread）拥有，错误线程返回 `BREAK_RUNTIME_REJECTED`。所有容器在 create 时分配并固定容量；运行路径没有 `malloc/calloc/realloc`。外部身份使用 `{index,generation}` 句柄，失效句柄返回 `STALE`，容量耗尽返回 `OVERLOAD`，非法输入返回 `INVALID`。用户认证回调只在 GameThread 执行，网络接收路径只验证数据报界限、复制并入有界队列。

## 2. 认证大厅、房间目录与匹配

`break_online_lobby.{h,c}` 实现房间和成员生命周期：

- 默认最多 64 个房间、每房间 16 个成员；硬上限分别为 1024 和 256。名称长度为 1..63 字节。
- `BreakLobbyAuth` 只含不透明 session key 和 `BreakOnlineAuthSource`。调用方不能直接提交 player id；只有认证回调返回非零 `session_id/player_id` 后才可创建或加入。`break_online_session.h` 将真实 `BreakSessionManager` 的 `AUTHENTICATED` 状态映射为 session 域身份，NEW/AUTHENTICATING/CLOSING 均拒绝。该内置映射的 player id 与 session id 相同，不是跨重连账号 id。
- 创建、加入、离开、目录、匹配、断连清理都检查 generation。房间空时销毁；成员或房间槽复用不会复活旧句柄。
- 主机离开时由剩余成员中加入序号最小者继任，`host_epoch` 递增。`break_lobby_disconnect` 移除同一 session 在全部房间中的成员并执行同样的迁移，重复清理是幂等的。
- 目录只列出 `listed` 房间，可按 region/mode 过滤，使用显式 offset/page capacity/`next_offset` 分页，不静默截断。
- 服务端匹配只选择符合过滤条件且未满的 listed 房间，优先成员数较多者，平局按 generation/index 键排序；匹配成功与加入是同一个 GameThread 操作，没有匹配房间返回 `FAILED`。

直接测试 10/10；真实 `BreakSessionManager` 适配包含在 Session 38/38 中，覆盖认证前拒绝、认证后创建和断连清理。

## 3. 有界收件队列与 UDP NAT 协调

`break_online_inbox.{h,c}` 是 MPSC 有界 FIFO。单项最大 1280 字节，容量为 1..256；生产者不等待、不执行回调，满时整包拒绝并累计 overload/invalid/closed/high-water 统计。只有创建线程可 poll。双生产者并发测试在 TSan 下通过。

`break_online_nat.{h,c}` 使用既有非阻塞 `NetSocket`，所有整数显式 little-endian，消息以 `BRN1` 开始：

| 类型 | 完整字节数 | 行为 |
|---|---:|---|
| HELLO | 16 | endpoint 向 coordinator 提交 session key |
| WELCOME | 24 | coordinator 认证后返回 generation peer handle |
| PUNCH | 50 | 向两端发送 pair handle、nonce、期限和对端 observed IPv4/port |
| PING | 24 | 两端向 observed address 发送打洞包 |
| ACK | 24 | 有效 PING 后向 coordinator 确认 |

coordinator 硬上限为 64 个 peer 和 32 个未关闭 pair；每个 endpoint 同时只跟踪一个 pair。peer 容量是 coordinator 生命周期内的固定表容量，当前没有 peer 回收 API；pair 可关闭或使未确认 pair 过期。过期检查有界，过期或关闭只使对应 generation 失效。

HELLO 在 GameThread 经认证提供方解析身份，UDP 源地址成为 observed address。PING 必须匹配 armed pair、generation、nonce 和期望源地址，否则不会把 endpoint 标为 connected。PUNCH 先发失败时本地不发布半创建 pair；已经交给 OS 的报文无法召回。未确认 pair 到期后，迟到的 PUNCH 同样被拒绝。

测试 7/7 使用三个真实 UDP socket 完成两端注册、双向 PUNCH/PING、ACK 和 observed-address 验证；另覆盖伪造来源、malformed 数据、peer 容量、重复 HELLO、pair 关闭和 TTL。**该证据只证明本机 IPv4 loopback 的协调与打洞行为，不证明任意 NAT、防火墙、公网部署、对称/限制锥 NAT 或可靠送达。**

## 4. 有界 PCM 语音与抖动播放

`break_online_voice.{h,c}` 的 `BRV1` 帧头固定为 16 字节：`sequence:u32`、`sample_rate:u32`、`channels:u16`、`sample_count:u16`，随后是 `sample_count` 个 little-endian 交织 `i16` 样本。每帧最多 480 个样本，完整数据报最多 976 字节。

流配置固定采样率（1..192000）、单/双声道、每帧样本数、jitter delay、jitter/queue 容量。样本数必须被声道数整除，且帧时长至少 1ms；jitter 容量为 1..64，delay 为 0..10000ms。创建后这些参数不变。

- 网络入口只检查数据报大小并复制入队；GameThread 的 pump 才检查 magic、流格式和精确长度、解码 PCM 并维护序号。
- 首帧到达后经过配置的 jitter delay 才开始播放。播放前可按无符号序号关系重排，覆盖 `UINT32_MAX -> 0` 回绕；重复帧和播放后的迟到帧分别计数并拒绝。
- 期望帧缺失但已存在更晚帧时，按固定节奏输出一个同序号、同长度、全零且 `concealed=true` 的帧，然后前进一个序号。迟到的缺失帧不能覆盖后续 PCM。没有更晚帧时不无限制造静音。
- pop 只向调用方返回 PCM，不混音、不调用音频设备，也不在网络线程执行游戏逻辑。

测试 8/8 覆盖逐字节线序、立体声样本、非法/尾随数据、jitter 重排、丢帧隐藏、重复/回绕、队列满和真实 UDP loopback 样本一致性。**未做听感测试，未证明网络丢包下的主观音质。**

## 5. Aspect schema 与带宽友好编码

`break_online_aspect.{h,c}` 支持最多 64 个 aspect id、1024 个对象、每值 256 字节和每包 65536 字节。创建 store 时同时分配对象/值存储、单对象 staging 和包 scratch。首个对象成功创建/采用后 schema 冻结。

每个 schema 包含 aspect id、version、类型和值容量。规范 hash 按 aspect id 顺序计算，包含这些字段，与注册顺序无关。对象句柄的 generation 编入对象 id；槽复用递增 generation，adopt 也不允许采用不超过已退休 generation 的旧身份。

`BRA1` 包格式为：

```text
magic[4] || schema_hash:u64le || object_id:u64le ||
revision:varuint || kind:u8 || aspect_mask:varuint || values...
```

kind 为 BASELINE、DIRTY、DESTROY 或 DORMANT。baseline 携带当前全部 active aspect，dirty 只携带 mask 指定的变化 aspect；控制记录的 mask 必须为 0。值按 aspect id 升序编码：U32 使用 LEB128，I32 使用 zigzag LEB128，F32 使用 4 字节 little-endian 并拒绝非有限值，BYTES 使用 varint 长度和精确字节。仅变化字段进入包，因此小整数和稀疏变化不会发送整个对象。

apply 要求相同 schema hash、live generation 和更新的 revision，先验证全部 mask、varint、类型、长度及精确包结束，再在 staging 暂存，最后一次性提交。任何失败都保留原对象值和 revision；相同值 setter 不增加 revision。测试 5/5 包含手工 `health=300` 的字节证据、baseline/dirty 往返、负值/浮点/字节、stale handle、输出容量及 malformed 无部分提交。

## 6. AOI 驱动复制与复用边界

`break_online_aspect_replication.{h,c}` 的硬上限为 64 个连接、1024 个 Real 对象和 2048 个片段/单记录。create 分配 Real/Connection/Ghost、包和片段元数据；同步路径不分配。Real 注册复用既有 `BreakSpatialIndex`，同步直接消费既有 `BreakAoIResult` 的优先级/ID 顺序：

- enter：发送当前全部 active aspect 的 baseline；重复 enter 不重复 baseline。
- stay：每连接独立 dirty mask，只发送该连接未确认的 aspect；相同值和无变化 stay 不发送。
- leave：按对象 flags 发送 DESTROY 或 DORMANT，成功后清理 ghost。
- disconnect：清理该连接全部 ghost；重连必须重新 baseline。

每个包经 `break_replication_fragment_payload_into` 使用调用方固定元数据切片，保留既有 delta/base id、FNV-1a 片段校验和及 reassembler 语义；原分配式 API 未改变。片段字节预算在首次发送前检查，不足则保留 dirty 供后续重试。所有片段经 `BreakAspectSendFn` 成功交付后才清 dirty/更新 ghost；回调失败保留状态，重试使用新 delta id。已发出的片段无法召回，但接收方可利用既有 duplicate/conflict/checksum 检查。

`BreakAspectSendFn` 是接入现有认证 Session/`BreakNetReactor` 或其他安全传输的明确边界；本模块不直接把 connection id 当作认证证明。**FNV 校验和只是完整性检查，不是认证；本切片没有新增可靠传输、客户端预测、回滚或 authority handoff。**

调度测试 3/3 使用真实 AOI、两个独立接收端、预算优先级、发送失败重试、片段逆序重组、dormant 和断连。固定分片测试 9/9 另覆盖 4/4/2 切片及短容量不发布部分元数据。

## 7. 验证与限制

最终源码上，Linux/GCC 16.2.1 的无 Snowflake normal focused 为 11/11。使用仓库钉住的 Snowflake `0fceed6d885bb8578743d82cc4a5d7ab2f6b0620` 时，normal、ASan+UBSan、TSan 的网络/复制/Session 标签均为 13/13，基础网络补充均为 5/5；无 sanitizer 报告。每个 lane 均运行 NAT 和语音真实 UDP loopback。各项 RED/GREEN 和变异输出见 `.superpowers/sdd/online-gameplay-network-report.md`。

这些结果是 focused 网络验证，不是全仓库、全平台或外部部署证明。Windows/macOS/移动原生 lane、任意 NAT、公网服务、主观听感、可靠传输、预测回滚和生产账号后端均未在本切片声称完成。
