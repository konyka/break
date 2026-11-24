# Online Logic Network 当前实现事实

日期：2026-11-03

## 1. 目标与边界

P8 的正式可选静态库是 `break_online`，源码位于 `engine/src/network/break_online_*`。它不链入 `engine`、`engine_demo`、`dxx_break` 或编辑器，消费方显式选择该库。库 PUBLIC 依赖 `Threads::Threads` 与既有 `break_replication_core`；UDP 的 `net_*` 符号继续由既有 `network.c` 在最终消费链接中提供，没有第二套 socket、可靠传输、认证、安全分片或 AOI 实现。

可变大厅、NAT 协议、语音播放和 aspect 状态均由创建线程（接入时为 LogicThread）拥有，错误线程返回 `BREAK_RUNTIME_REJECTED`。所有容器在 create 时分配并固定容量；运行路径没有 `malloc/calloc/realloc`。外部身份使用 `{index,generation}` 句柄，失效句柄返回 `STALE`，容量耗尽返回 `OVERLOAD`，非法输入返回 `INVALID`。用户认证回调只在 LogicThread 执行，网络接收路径只验证数据报界限、复制并入有界队列。

## 2. 认证大厅、房间目录与匹配

`break_online_lobby.{h,c}` 实现房间和成员生命周期：

- 默认最多 64 个房间、每房间 16 个成员；硬上限分别为 1024 和 256。名称长度为 1..63 字节。
- `BreakLobbyAuth` 只含不透明 session key 和 `BreakOnlineAuthSource`。调用方不能直接提交 player id；只有认证回调返回非零 `session_id/player_id` 后才可创建或加入。`break_online_session.h` 将真实 `BreakSessionManager` 的 `AUTHENTICATED` 状态映射为 session 域身份，NEW/AUTHENTICATING/CLOSING 均拒绝。该内置映射的 player id 与 session id 相同，不是跨重连账号 id。
- 创建、加入、离开、目录、匹配、断连清理都检查 generation。房间空时销毁；成员或房间槽复用不会复活旧句柄。
- 主机离开时由剩余成员中加入序号最小者继任，`host_epoch` 递增。`break_lobby_disconnect` 移除同一 session 在全部房间中的成员并执行同样的迁移，重复清理是幂等的。
- 目录只列出 `listed` 房间，可按 region/mode 过滤，使用显式 offset/page capacity/`next_offset` 分页，不静默截断。
- 服务端匹配只选择符合过滤条件且未满的 listed 房间，优先成员数较多者，平局按 generation/index 键排序；匹配成功与加入是同一个 LogicThread 操作，没有匹配房间返回 `FAILED`。

直接测试 10/10；真实 `BreakSessionManager` 适配包含在 Session 38/38 中，覆盖认证前拒绝、认证后创建和断连清理。

## 3. 有界收件队列与 UDP NAT 协调

`break_online_inbox.{h,c}` 是 MPSC 有界 FIFO。单项最大 1280 字节，容量为 1..256；生产者不等待、不执行回调，满时整包拒绝并累计 overload/invalid/closed/high-water 统计。只有创建线程可 poll。双生产者并发测试在 TSan 下通过。

`break_online_nat.{h,c}` 使用既有非阻塞 `NetSocket`，所有整数显式 little-endian，消息以 `BRN1` 开始：

| 类型 | 完整字节数 | 行为 |
|---|---:|---|
| DISCOVER | 16 | endpoint 请求公开 registration challenge |
| CHALLENGE | 32 | 来源绑定的 nonce、coordinator 绝对期限，由本地 challenge key 派生 |
| HELLO | 72 | session、nonce、期限、序号和 32 字节 HMAC |
| WELCOME | 56 | 带 MAC 的 generation peer handle |
| PUNCH | 106 | recipient peer/session、pair、nonce、相对 TTL、序号、对端地址和 MAC |
| PING | 24 | 两端向 observed address 发送打洞包 |
| ACK / CLOSE | 72 / 72 | 带 recipient 和 MAC 的确认或 pair 关闭 |

控制面使用 `break_crypto_hmac_sha256`（既有 OpenSSL EVP 包装）和每 session 的 32 字节密钥。NAT 配置必须同时提供认证回调、`session_key` 和 coordinator 本地 `challenge_key`；应用负责密钥 provision/rotation。challenge 是 stateless 的：coordinator 不为未认证 DISCOVER 分配每 session 状态，伪造 session 刷量不能占满槽位。nonce 由 session、来源和到期窗口计算，endpoint 只转发不透明的 challenge expiry，coordinator 在自己的时钟上验证期限。HELLO 的 challenge 绑定请求来源，认证后才登记 observed address，64 项 replay window 和精确 duplicate 记录保证幂等且不接受重放。WELCOME/PUNCH/ACK/CLOSE 都验证 recipient、registered 状态和 MAC；PUNCH 还必须匹配 peer/session。完全相同的 PUNCH 是幂等的，冲突 nonce/TTL/地址/序号或篡改 MAC 不会覆盖 connected。

coordinator 硬上限为 64 个 peer 和 32 个未关闭 pair；每个 endpoint 同时只跟踪一个 pair。peer 容量是 coordinator 生命周期内的固定表容量，当前没有 peer 回收 API；pair 可关闭或使未确认 pair 过期。PUNCH 只携带相对 TTL，coordinator 用自己的时钟计算期限，endpoint 用各自本地时钟计算 deadline，不比较不同 epoch。显式关闭和过期都会发送认证 CLOSE。endpoint 保存持久 control high-water，inactive 时序号不高于 high-water 的 PUNCH/CLOSE 都拒绝；只有 active pair 的完全相同 PUNCH 或完全相同 CLOSE 可幂等。较旧 CLOSE 不能回退 high-water，合法更大 generation/sequence 的 re-pair 仍可接受。

PING 必须匹配 armed pair、generation、nonce 和期望源地址，否则不会把 endpoint 标为 connected。PUNCH 先发失败时本地不发布半创建 pair；已经交给 OS 的报文无法召回。所有新容器仍 create 时固定分配，网络接收只校验界限并入队。`BREAK_ENABLE_CRYPTO=OFF` 时完整 HMAC 测试不构建，独立 `test_break_online_nat_nocrypto` 只验证 coordinator/endpoint create 返回 REJECTED 且输出为空，成功路径不运行。

测试 23/23 使用真实 UDP socket 完成注册、双向 PUNCH/PING、ACK/CLOSE 和 observed-address 验证；另含有效 HMAC captured HELLO 跨 socket 重放、伪造 DISCOVER 刷槽、本地 TTL 后重放、连续 CLOSE 后最早 PUNCH、旧 CLOSE 乱序、未注册 PUNCH、重复/冲突 PUNCH、篡改 MAC、未知 pair/nonce、四 endpoint pair 容量、close-before/after-connect、re-pair 和跨时钟 epoch。**该证据只证明本机 IPv4 loopback 的协调、认证和打洞行为，不证明任意 NAT、防火墙、公网部署、对称/限制锥 NAT 或可靠送达。**

## 4. 有界 PCM 语音与抖动播放

`break_online_voice.{h,c}` 的 `BRV1` 帧头固定为 16 字节：`sequence:u32`、`sample_rate:u32`、`channels:u16`、`sample_count:u16`，随后是 `sample_count` 个 little-endian 交织 `i16` 样本。每帧最多 480 个样本，完整数据报最多 976 字节。

流配置固定采样率（1..192000）、单/双声道、每帧样本数、jitter delay、jitter/queue 容量。样本数必须被声道数整除，且帧时长至少 1ms；jitter 容量为 1..64，delay 为 0..10000ms。创建后这些参数不变。

- 网络入口只检查数据报大小并复制入队；LogicThread 的 pump 才检查 magic、流格式和精确长度、解码 PCM 并维护序号。
- 首帧到达后经过配置的 jitter delay 才开始播放。播放前可按无符号序号关系重排，覆盖 `UINT32_MAX -> 0` 回绕；重复帧和播放后的迟到帧分别计数并拒绝。
- 期望帧缺失但已存在更晚帧时，按固定节奏输出一个同序号、同长度、全零且 `concealed=true` 的帧，然后前进一个序号。迟到的缺失帧不能覆盖后续 PCM。没有更晚帧时不无限制造静音。
- pop 只向调用方返回 PCM，不混音、不调用音频设备，也不在网络线程执行应用逻辑。

测试 8/8 覆盖逐字节线序、立体声样本、非法/尾随数据、jitter 重排、丢帧隐藏、重复/回绕、队列满和真实 UDP loopback 样本一致性。**未做听感测试，未证明网络丢包下的主观音质。**

## 5. Aspect schema 与带宽友好编码

`break_online_aspect.{h,c}` 支持最多 64 个 aspect id、1024 个对象、每值 256 字节和每包 65536 字节。创建 store 时同时分配对象/值存储、单对象 staging 和包 scratch。首个对象成功创建/采用后 schema 冻结。

每个 schema 包含 aspect id、version、类型和值容量。规范 hash 按 aspect id 顺序计算，包含这些字段，与注册顺序无关。对象句柄的 generation 编入对象 id；槽复用递增 generation，adopt 只拒绝早于已退休 generation 的身份，因此 destroy 后的合法下一代 gen2 可以重建，更旧身份仍返回 STALE。

`BRA1` 包格式为：

```text
magic[4] || schema_hash:u64le || object_id:u64le ||
revision:varuint || kind:u8 || aspect_mask:varuint || values...
```

kind 为 BASELINE、DIRTY、DESTROY 或 DORMANT。baseline 携带当前全部 active aspect，dirty 只携带 mask 指定的变化 aspect；控制记录的 mask 必须为 0。wire 中沿用历史名称的 `revision:varuint` 字段实际承载 record epoch，不是公共 value revision。值按 aspect id 升序编码：U32 使用 LEB128，I32 使用 zigzag LEB128，F32 使用 4 字节 little-endian 并拒绝非有限值，BYTES 使用 varint 长度和精确字节。仅变化字段进入包，因此小整数和稀疏变化不会发送整个对象。

兼容 `break_aspect_encode` 不再从 value revision 推导顺序，而是为每对象独立保存 encoder epoch/hash。首次成功自动编码使用 epoch 1，之后每次成功加一；只有完整输出成功后才提交这份 encoder 状态，INVALID、STALE、输出容量或内部包容量 OVERLOAD 都不消耗 epoch，也不改输出、对象值、value revision 或 apply record 状态。因此 baseline→DORMANT→DESTROY 使用 1/2/3，DORMANT 后同值 baseline 使用下一 epoch。传输失败后若要重发同一 attempt，调用方必须复用原字节；再次调用自动 API 会创建更高 epoch 的新 attempt。encoder 状态只存在于当前 store 的对象生命周期，新 create/adopt 从零开始，不是跨进程持久序号。

`break_aspect_encode_with_epoch` 对 record 和 encoder 状态都只读；epoch 小于任一 high-water，或等于任一 high-water 但 packet hash 不同，均返回 STALE，相同字节可重复编码。**同一对象必须明确 epoch owner：** 自动转显式时，从大于最后自动 epoch 的值开始并继续使用显式 API；显式较大 epoch 不推进自动 high-water，之后不能切回自动包装器。scheduler 始终使用自己的显式 per-attempt high-water。自动 encoder 或 apply record epoch 达到 `UINT64_MAX` 后，自动编码返回 OVERLOAD 且保持输出和状态不变；跨进程恢复或需要自行持久排序的调用方必须全程使用显式 epoch。

apply 要求相同 schema hash、live generation 和递增的每对象 record epoch，成功时只更新 record epoch/hash，不把 record epoch 写回公共 value revision；公共 value revision 只表示本地值变更，不再兼任控制顺序。全部 mask、varint、类型、长度及精确包结束先验证，再在 staging 暂存，最后一次性提交。DORMANT/DESTROY 都只是去激活并清 active mask，后续更高 epoch 的 baseline 可用同一 handle 唤醒；永久销毁仍由显式 `break_aspect_object_destroy` 退休 generation。相同包的重复 apply 可幂等，旧 control 或同 epoch 不同 hash 返回 STALE。任何失败都保留原对象值、value revision 和 record epoch；相同值 setter 不增加 value revision，value revision 或 record epoch 达到 `UINT64_MAX` 后 setter 返回 OVERLOAD 且值不变。测试 12/12 包含手工 `health=300` 的字节证据、直接兼容 API 连续控制/同值唤醒、短输出预算重试、自动/显式冲突、epoch 耗尽、baseline/dirty 往返、gen2 重建、负值/浮点/字节、stale handle、较小 epoch 及 malformed 无部分提交。

## 6. AOI 驱动复制与复用边界

`break_online_aspect_replication.{h,c}` 的硬上限为 64 个连接、1024 个 Real 对象和 2048 个片段/单记录。create 分配 Real/Connection/Ghost、包和片段元数据；同步路径不分配。Real 注册复用既有 `BreakSpatialIndex`，同步直接消费既有 `BreakAoIResult` 的优先级/ID 顺序：

- enter：发送当前全部 active aspect 的 baseline；重复 enter 不重复 baseline。
- stay：每连接独立 dirty mask，只发送该连接未确认的 aspect；相同值和无变化 stay 不发送。
- leave：按对象 flags 发送 DESTROY 或 DORMANT，并保存 pending_leave/kind；即使下一轮 AOI 为空也优先重试，只有全部片段成功后才清理 ghost。
- disconnect：清理该连接全部 ghost；重连必须重新 baseline。

每个包经 `break_replication_fragment_payload_into` 使用调用方固定元数据切片；分配式与固定存储 API 共用同一 planner/fill，避免 wire 漂移。编码、分片和片段字节预算均在首个 datagram 前预检，预算不足不推进 record epoch，并保留 dirty 供后续重试。预检通过后、首个 datagram 前，publish 把 Real 的 record epoch 推进到本次实际发送尝试的 epoch；即使完整包已交付后 callback 才返回失败，也保留这个 attempt high-water 和 dirty。后续尝试使用新的 record epoch 与 delta id，因此接收端不会把修改后的值误判为同 epoch 冲突。只有全部片段经 `BreakAspectSendFn` 成功交付后才清 dirty/更新 ghost。reassembler 保存持久 delta high-water，完成后更旧 delta 也返回 CONFLICT；新流元数据、首片和结果分配全部成功后才淘汰旧流，OVER_LIMIT/OOM 不改变旧流。显式 reset 才开启新 epoch。已发出的片段无法召回，但接收方可利用 duplicate/conflict/checksum 检查。

`BreakAspectSendFn` 是接入现有认证 Session/`BreakNetReactor` 或其他安全传输的明确边界；本模块不直接把 connection id 当作认证证明。**FNV 校验和只是完整性检查，不是认证；本切片没有新增可靠传输、客户端预测、回滚或 authority handoff。**

调度测试 9/9 使用真实 AOI、两个独立接收端、预算优先级、零预算不推进 epoch、完整包交付后 callback 失败并修改值的重试、第二片失败后的持久重组、空 AOI pending leave、普通 leave 重入、DORMANT 唤醒、旧 control 乱序和断连。固定分片测试 12/12 另覆盖 4/4/2 切片、短容量不发布部分元数据、完成后旧 delta 拒绝以及失败淘汰保留旧流。

## 7. 验证与限制

最终源码上，Linux/GCC 16.2.1 的 crypto ON 无 Snowflake normal focused 为 11/11；使用仓库钉住的 Snowflake `0fceed6d885bb8578743d82cc4a5d7ab2f6b0620` 时，normal、ASan+UBSan、TSan 的网络/复制/Session 标签均为 13/13，基础网络补充均为 5/5。no-crypto normal/ASan+UBSan/TSan 的独立 fail-closed focused 也均为 11/11；无 sanitizer 报告。每个 crypto-enabled lane 均运行 NAT 和语音真实 UDP loopback。no-crypto lane 只运行独立 fail-closed 合约，不执行 HMAC 成功路径。各项 RED/GREEN 和变异输出见 `.superpowers/sdd/online-session-network-report.md`。

这些结果是 focused 网络验证，不是全仓库、全平台或外部部署证明。Windows/macOS/移动原生 lane、任意 NAT、公网服务、主观听感、可靠传输、预测回滚和生产账号后端均未在本切片声称完成。

2026-11-10 Darwin 同步补充：`net_sendto()` 返回完整长度不代表对端非阻塞接收队列已经可读。NAT malformed、captured HELLO 和 voice UDP 测试现按原状态/计数/`ready` 条件做有界接收与 pump，不改变非阻塞 API，也不把 `NET_WOULD_BLOCK` 当成功。captured HELLO 必须先完成合法 peer 登记，跨 socket 重放必须实际被处理并使 invalid 计数增加 1，随后仍验证 observed address 不变。该修复没有改动生产 socket 地址、challenge、HMAC、nonce 或 replay 代码；Linux 故障注入精确复现并验证首次 `recvfrom=EAGAIN` 的行为，但 native macOS 仍须后续 CI 确认。

2026-11-12 close-before-punch 同步补充：主 CI run `43181031519` 的 macOS Cocoa + MoltenVK job `131056765414` 中，`nat_close_before_punch_blocks_late_punch` 在 late PUNCH 后重新 arm A（22/23）。`break_nat_coordinator_pair_close` 只负责向双端发送 CLOSE 并 retire pair；`endpoint_close` 必须实际处理后才会清除 active 并记录 closed pair/sequence，随后 `endpoint_punch` 才按同 generation/sequence 拒绝重放。原测试固定 8 次 pump 不能保证该状态已发布，初始两个 disarmed 断言通过后再次 arm 与这一时序一致，并不证明生产协议错误。测试现以既有五秒 `nat_pump_until_closed` 等待双端 disconnected 且 disarmed，再发送真实 late PUNCH；初始/最终断言、receive/poll、首错传播与认证 high-water 语义全部保留，未增加 sleep、skip、生产 hook 或协议改动。controller 旧逻辑本地 200 次未复现，因此不宣称稳定本地 RED 或生产 bug；修正后的单核 200/200 与 TSan focused 通过，fresh full CI/D3D12 仍待 controller 验收。

第三轮 MSVC 补充：voice UDP 测试的 `BreakVoicePlayback playback` 在声明时以 `{0}` 零初始化，消除有界循环路径上的 C4701 静态诊断。该初始化不改变播放语义；`ready==true`、sequence 77 和真实 PCM `-123/456` 断言继续执行，native MSVC 仍待后续 CI。

2026-11-12 fresh CI 验收：合并提交 `a9c25224` 的主 CI run `43186135276` 全部可执行 job 成功，macOS Cocoa job `131073643195` 的 `test_break_online_nat` 实际通过，覆盖此前失败的 close-before-punch 场景；clean-room job `131073947704` 为 352 selected、0 FAIL，三个缺库合同按预期 SKIP，dangling 合同通过。D3D12 run `43186135119` 的 headless、WARP runtime 1/1、push-constant、Agility 和七个 D3D12-labelled 测试均成功。主工作树合并结果的非图形为 358 selected、354 PASS、4 个文档化 SKIP、0 FAIL。上述 fresh native 结果与旧逻辑本机 200 次未复现的限制同时成立；不把本地重复或单次通过解释为生产环境已消除所有 UDP 重排，也不把 WARP 当作独立显卡证明。

## 补充（2026-11-16）：语音接入混音器

`pop` 本身仍不调用音频设备。新增 `audio_pcm_stream_*`（`audio/audio_extended.h`）：应用在 LogicThread 把 `break_voice_receiver_pop` 得到的 PCM 写入一个流，混音器在音频回调里按顺序播放，空了就输出静音并计入 underrun。（2026-11-16 更新：`audio_pcm_stream_open_rate` 接受 8000..192000 Hz 的流，混音器以线性插值转换到 48 kHz，因此 8/16/24 kHz 语音可直接写入；降采样不做低通滤波。2026-11-16 再补充：`audio_pcm_stream_set_spatial` / `set_position` 让流按与空间事件相同的距离衰减与遮挡模型随监听者和声源位置变化增益，只调增益，没有声像或 HRTF。）没有麦克风采集。`test_voice_playback` 把乱序到达的 `BRV1` 帧经真实接收器写入流，验证混音输出与发送顺序一致。设计与验证见 `docs/superpowers/plans/2026-11-16-audio-pcm-stream.md`。

## 补充（2026-11-16）：BRV2 压缩语音帧

新增 `BRV2` 帧格式与 `break_voice_encode_adpcm`：在 `BRV1` 的 16 字节头之后，每个声道一个 4 字节起始状态（该声道首个样本作为预测值 i16 le、步长索引 u8 0..88、保留字节 0），之后每个后续样本一个 4 位 IMA ADPCM 码，两码一字节、低半字节在前，按声道交错。帧大小为 `16 + 4 × 声道数 + ceil((样本数 − 声道数) / 2)`，约为 `BRV1` 的四分之一。每帧自带起始状态，丢帧不影响后续帧。接收器对配置格式同时接受 `BRV1` 与 `BRV2`；步长索引超过 88、保留字节非零或长度不符的 `BRV2` 计入 `invalid`。16 kHz、−6 dBFS、440 Hz 正弦的往返信噪比超过 30 dB。没有感知编码器（如 Opus）。设计与验证见 `docs/superpowers/plans/2026-11-16-voice-adpcm.md`。

## 补充（2026-11-16）：语音接收器 fuzz

`fuzz_break_online_voice`（`engine/tests/fuzz_break_online_voice.c`）对 `BRV1`/`BRV2` 帧做字节变异（随机写、位翻转、头部边界值、magic 互换、ADPCM 步长索引 88/89/255、保留字节、截断、多一字节、只错样本数的完整帧），再推入同一个接收器。harness 自带独立的 PCM 与 IMA ADPCM 解码器（标准 16 项索引表）和影子抖动缓冲：每个数据报必须恰好使 accepted/invalid/duplicate/stale/overload 之一加一，且与模型一致；播放序号、样本（等于被接受数据报的参考解码）和补偿帧（静音）都按模型检查。接收器每 64 次重建，格式在 8–48 kHz、单/双声道间轮换。冒烟测试 `fuzz_break_online_voice_smoke`（2000 次，seed 43，`fuzz` 标签）进入三条 CI fuzz 构建列表。设计与验证见 `docs/superpowers/plans/2026-11-16-voice-fuzz.md`。


## 补充（2026-11-24）：复制分片 wire codec 的 session 边界

`break_replication_wire.{h,c}` 现在为 `BreakReplicationFragment` 提供 BRFG/v1 canonical 编码，属于 `break_replication_core`，没有新增消息 ID，也没有接入 `break_online`、Session 或 reactor。后续独立 bridge 才能注册预留的 `0x4009` 并把 decode 后的 borrowed data 在同一输入生命周期内交给重组池；网络接收队列若要复用或释放缓冲，必须先完成这次复制。

aspect 接入仍有一个明确发送侧缺口：现有 fragmenter 的通用片长上限是 65536，而 BRFG 数据片必须收窄到 65496，才能给 40 字节头留出空间。bridge 还必须另设完成队列、每连接和全 manager 预算，不能把 count 的绝对上限 1048576 当成生产准入配置。decode 不验 FNV-1a 是有意分层，重组池继续负责 checksum/base/high-water；FNV 仍不是认证。

focused 证据为新 wire **7/7**、旧 fragment/scheduler **28/28**，ASan+UBSan/TSan 亦通过相同两组测试。真实 session 收发、消息注册、aspect 发送上限调整、可靠传输、认证和 World delta 协议均不在本切片，不以 codec 往返测试冒充真实网络验收。


### 复制分片 wire codec 最终验证补充（2026-11-24）

最终代码与测试对象为 `2f1c28d08ab9444f119fdf24bdc5d1c4fac16a26`。控制器在该 SHA 实际取得 Vulkan **100%（463/463）**：459 通过、4 条件 skip、0 失败，以及 OpenGL **100%（454/454）**：450 通过、4 条件 skip、0 失败。skip 为 `test_d3d12_dependency_gate` 和 `test_core_app_nm_missing`、`test_core_app_nm_unsupported`、`test_core_app_nm_symbol_missing_unsupported`，不计为执行通过。

fix 后 normal、ASan+UBSan/LSan、TSan focused 均为 wire **9/9**、旧 fragment/scheduler **28/28**，累计 **14 项变异均判红并恢复**。上一段的 **7/7** 与首轮八项变异是 fix 前历史记录，最终为 **9/9、14 项**。

这些结果不改变本文件的接入边界：完整 sanitizer suite、Session 收发、消息注册、aspect bridge、真实网络及远端验收仍未完成，不以 codec/CTest 证据代替，也不预写推送或 CI 结果。


## 补充（2026-11-24）：BRFG/v1 接入认证 Session

`0x4009` 现为 `BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT`，定义是 BRFG/v1、payload 上限 64 KiB、`AUTHENTICATED + IDEMPOTENT`；默认 registry 在 crypto 开启/关闭时分别为 **30/29** 项。`BreakReplicationSessionBridge` 的 create/destroy、open/close、send、tick、handler、poll/release 与 stats API 已接入 `break_net`，但尚未接入 online aspect scheduler。

每次 open 为 connection key 创建独立重组池并固定 expected base；每连接 pending 预算的乘积在 create 时受总预算约束。完成 queue 另受条数、单包与总字节限制，按 FIFO 交付 connection、delta id 和 owned bytes。只有 `poll_completed` 执行 ownership-at-poll 转移，`completion_release` 负责释放；close 清理该连接的池和未取项，同 key 重开从新高水位开始。stats 暴露连接/pending/completion 快照及 rejected、duplicate、completed、dropped、expired 计数。handler 不执行 aspect apply 或 World 变更，不新增线程或锁。

两个真实 socket 用例覆盖 AUTH 后乱序交织两个 delta、相同 BRFG bytes 的重复片、错误 base 拒绝、完成 FIFO/connection/payload、poll 前 consumer 计数为 0，以及 close 后同 key 真实重连完成较低 delta。`test_break_replication_session` 现为 **19/19**； companion Session/wire/fragment 分别为 **43/43、9/9、28/28**。完整 Vulkan 为 **464 通过 + 4 条件 skip/468，0 失败**，OpenGL 为 **455 通过 + 4 条件 skip/459，0 失败**；skip 是 `test_d3d12_dependency_gate` 与三个 `test_core_app_nm_*`，不计执行通过。ASan+UBSan（显式 leak 检测）和 TSan focused 均 **4/4**，直接 case 计数同样为 **19/19、43/43、9/9、28/28**，无诊断。

剩余边界明确保留：**生产 core_app/editor 接线、aspect drain、World delta、可靠恢复和完整资产链均未完成**。aspect 发送侧 fragment size 收窄、completion drain 中校验 `BRA1.schema_hash == expected_base` 后再 apply，仍属于后续独立工作。


## 补充（2026-11-24）：AOI aspect 发送与 Session drain 对接

`BreakAspectSession` 将现有 `BreakAspectReplication` 的 BRA1 发送端与认证 Session 的 completion queue 连接起来。接收连接 open 时 expected base 固定来自远端 `break_aspect_schema_hash(store)`；发送侧 `fragment_size` 上限收窄为 **65496**，因此每片都可由 BRFG/v1 的 40 字节头封装。接收 handler 不调用 aspect store，owner 必须显式调用 `break_aspect_session_drain` 才 apply；每个 completion 无论成功或拒绝都会 release，拒绝只累计 `rejected_packets`，不关闭连接。stats 同时包含 applied/rejected/drained 与完整 bridge stats。

`break_net`/`break_net_test` 通过 PUBLIC `break_online` 链接依赖满足上述实现；独立 link-only 测试 **1/1**，防止消费方必须显式追加 `break_online` 的隐性契约。发送适配仍固定 0x4009/v1，不包含可靠恢复语义。

真实 socket 验收使用 AUTH 后的既有 AOI enter/stay sync，而不是直接构造 completion。首个 baseline 到达后、drain 前，预 adopt 占位 handle 没有 active aspect、record revision 或可读字段；drain 后 U32/I32 为 42/-17。schema-mismatch dirty 包计 rejected 且两值不变；同 key close/reopen 后较低 delta 1 在旧 delta 40/41 之后被接受，最终为 84/-34。实际发送回调/BRA1 分片/completion 各 3，consumer 从 0 到 3，最终 applied/rejected/drained 为 2/1/3。registry 负对照为 **11/12**，恢复为 **12/12**。

normal、ASan+UBSan（显式 leak 检测）和 TSan focused 均为 **6/6、112/112**：aspect session **12/12**、link **1/1**、bridge **19/19**、Session **43/43**、wire **9/9**、fragment **28/28**。完整 Vulkan 注册 **463** 项，**459 执行通过、4 条件 skip、0 失败**；OpenGL 注册 **461** 项，**457 执行通过、4 条件 skip、0 失败**。四项为 `test_d3d12_dependency_gate`、`test_core_app_nm_missing`、`test_core_app_nm_unsupported`、`test_core_app_nm_symbol_missing_unsupported`，不计执行通过。

**生产 core_app/editor 接线、World delta、可靠恢复和完整资产链保持未完成**。本证据不表示已有可靠传输、自动重连恢复或资产依赖解析。


## 补充（2026-11-24）：core_app 使用 AOI aspect 与 Session drain

`BreakAspectSession` 现已接入生产 `core_app` 的可选网络 transport。默认关闭 `--aspect-replication` 时没有 aspect 状态或新增 trace；开启后两个同 schema store 使用固定 handle 1/2，authoritative 只从现有两个 snapshot POD 实体复制 index、generation、x/y/z、flags。AOI enter/stay 产生 BRA1，经 BRFG/v1 和认证后的 0x4009 发送；接收端 owner-thread drain 才 apply 到 diagnostic inbound store。连接回滚、断开、AOI scope 清理和 shutdown drain 都在同一线程完成，未新增锁。

真实 loopback 在 AUTH/welcome 后验证两个句柄的全部值，再反序发送 3 个有效片，在完成前重复第 2 片以命中服务端重复抑制，最后发送 3 个 schema-mismatch 片。服务端 `network_aspect_stats` 精确要求 applied=1、rejected=1、drained=2、queue_depth=0、dropped=0、duplicates=1、pending_bytes=0，发送分片至少 2；重复片被服务端计数且没有产生第二次 apply，也没有留下 pending stream。移除 0x4009 handler 的负对照为 **0/1**（0/0/0），恢复为 **1/1**。core_app network **12/12**、lifecycle **12/12**、ASan+UBSan focused **9/9**；TSan library/transport **7/7**，TSan 客户端 loopback **1/1**。core_app 自身在 TSan 下的两个场景受既有 Lua longjmp 环境限制，未掩饰为成功。

本项不定义新消息或 World delta，也不把 inbound 数据合并进 simulation。level 切换 rebaseline、可靠恢复、远端和其他平台验收保持未做。


## 补充（2026-11-24）：World delta 的认证 session 与恢复控制

`0x400A` 现在承载 BRWD/v1 的 BRFG 分片，`0x400B` 承载 BRWC/v1 控制；两者均为 `AUTHENTICATED + IDEMPOTENT`、64 KiB 上限。控制载荷固定 32 字节，NEED_FULL 报告接收方 last-good target id/tick，ACK 以 `(delta_id,target_id,tick)` 精确确认。外层 stream epoch 不随 ACK 基线变化，避免恢复时重建分片池。

接收侧 owner drain 成功后才推进 confirmed baseline 并合并 ACK，拒绝路径不变更 World。每连接 NEED_FULL 按 N tick 限流。发送侧在 ACK 前发 full，ACK 后允许从最新未确认 target 发 delta；精确 ACK 裁剪历史。历史 entry/byte 与 packet 上限、NEED_FULL 和未知 baseline 都会退化到 fresh-id full。所有片段未成功交付前，full 不丢弃旧历史；OVERLOAD 只恢复同一 immutable attempt 的未发片段，close/reopen 重置历史、confirmed baseline、控制限速和 delta id。

真实 socket 验收先 AUTH，再以不同 envelope sequence 反序发送并重复 BRWD 分片；接收 World 只在 drain 后与 target snapshot id 一致。注入内部 base mismatch 后产生 NEED_FULL，后续 full 使 World 达到恢复 target id。独立负对照从 manager registry 删除 0x400A，真实消息被分类 invalid 且 completion/World 都为零；恢复定义后新 socket 用例通过。新增 recovery **6/6**、loopback **2/2**，连同 world session/bridge/aspect/Session/wire/fragment/ECS/delta 直接计数共 **189/189**；normal focused **11/11**，ASan+UBSan（detect_leaks=1）和 TSan focused 均 **9/9**。

完整 Vulkan 注册 **467**，**463 通过、4 条件 skip、0 失败**；OpenGL 注册 **465**，**461 通过、4 条件 skip、0 失败**。四项 skip 不计通过。**core_app 启用、生产 level rebaseline、跨连接共享 World、预测回滚及远端验收仍未完成**；本特性只承诺 at-least-once 和最终一致。


## 补充（2026-11-24）：core_app 的 BRWD/BRWC 双向恢复验收

`test_core_app_net_client world` 复用现有 TLS/AUTH、BRFG wire、真实 `BreakWorldSession` 接收桥和 32 字节 BRWC 控制，而不是用 handler 直调替代网络。服务端先发布 full，收到精确 ACK 后由既有 tick 发布 delta；客户端反序重组并重复分片，验证两个 target snapshot id。随后客户端发送带重复片的 full、base mismatch delta 和恢复 full，服务端依次返回 ACK、NEED_FULL、ACK，覆盖 last-good baseline 和 full 恢复。

普通 focused 中 core_app network/offline 为 **13/13**、lifecycle 为 **12/12**，相关 transport/session/ECS 套件为 **13/13**。ASan+UBSan 且显式 `detect_leaks=1` 为 **14/14**；TSan 相关库为 **12/12**，正常服务端 + TSan 客户端的真实 world loopback 为 **1/1**。TSan 的 core_app target/离线 record 仍在既有 Lua protected-error 路径以 `can't find longjmp buf` 退出 66，未记为通过；混合 loopback 不覆盖 TSan 服务端 socket 进程。

移除 0x400A 注册的真实负对照为 **0/1**，恢复后为 **1/1**，transport 无残留 diff。本项仍是 at-least-once/final-consistency 的诊断切片，不包含完整资产链、生产 level rebaseline 或权威合并。
