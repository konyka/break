# 扩展音频：事件、音乐、DSP 与空间衰减

日期：2026-11-03

## 已交付边界

P10 在现有 `AudioSystem` 和同一个 miniaudio `ma_engine` 内实现。新增代码位于 `engine/src/audio/audio_extended.{h,c}` 与 `audio_dsp.{h,c}`；没有第二个设备或软件混音器。`test_audio_extended` 通过真实 miniaudio API 驱动 fake（`noDevice` + `ma_engine_read_pcm_frames`）和 null 后端，`test_audio_dsp` 验证确定性 PCM。

已实现：

- 命名 clip 与声音事件；`ALLOW`、`RESTART`、`IGNORE` 重触发，以及容量满时 `REJECT` 或 `STEAL_OLDEST`。
- 带 generation 的 voice handle；自然结束、显式停止和抢占后的 stale handle 拒绝。
- 最多 16 轨的音乐 playlist、循环播放、零淡化切轨及样本级线性交叉淡化。音乐只使用预留 voice 0/1。
- 最多四级的可组合 DSP：一极低通滤波、反馈延迟和固定四 tap 混响。delay/reverb 可带 filter 组成同一条链。
- GameThread 射线回调驱动的遮挡，以及与既有逆距离模型一致的距离衰减；扩展 voice 同时遵守现有 bus/master 增益。
- `AUDIO_BACKEND_NULL` 的真实设备生命周期，`AUDIO_BACKEND_FAKE` 的确定性离线 PCM。没有实际听测结论。

## 固定容量

| 项目 | 上限与失败行为 |
|---|---|
| clip | 48；重名 `AUDIO_REJECTED`，满 `AUDIO_OVERLOAD` |
| PCM 存储 | 1,048,576 个 f32 sample（4 MiB），注册时复制；不足返回 `AUDIO_OVERLOAD` |
| 事件定义 | 32；重名拒绝，满返回 overload |
| voice | 32 个创建期预建节点；30 个事件 voice + 2 个音乐 voice |
| 每 voice 命令 | 16 项 SPSC ring；满返回 `AUDIO_OVERLOAD`，不扩容、不等待 |
| 每事件并发 | 调用方配置 1..30；超过定义或全局容量按策略拒绝/抢占 |
| playlist | 16 个 clip handle；调用时复制，运行中替换返回 `AUDIO_REJECTED` |
| DSP | 每链 4 级；每 delay 类 stage 最多 8192 帧 |
| 输入格式 | f32 interleaved mono/stereo，48000 Hz；其他采样率返回 `AUDIO_INVALID` |

所有事件、clip、voice、命令、playlist 和 DSP storage 都在系统创建时分配。clip 注册只复制到预留 PCM 区域。没有运行期数组扩容。

## 线程与回调合同

`audio_extended_init` 在创建期把 32 个 custom data source 直接接到现有 engine node graph 的 `ma_data_source_node`。没有使用 `ma_sound` 的扩展 PCM 路径，因为其实现会预读固定大小的 processing cache，短 clip 会在小渲染请求下被提前消费。直接 node graph 路径按请求帧数读取，测试覆盖了这一点。

GameThread 是唯一命令生产者。START、STOP、RAMP 都是值命令，携带稳定内部 PCM 指针、公共 serial、独立内部 epoch 和预计算配置；head/tail 用 C11 release/acquire 原子发布。每次 START 都递增 epoch，公共 RESTART handle 不变；STOP/RAMP 只作用于对应 epoch，旧完成不能回收新播放。音频回调是唯一消费者，只有消费 START 时才归零 cursor 并发布该代际初始 spatial gain。listener、位置、遮挡和 bus 变化发布为原子 f32-bit POD 快照；自然结束用 `completed_epoch` 与当前 epoch 匹配后才能回收 voice。enqueue 成功前不改主线程簿记，失败保持原状态。

PCM 回调只做以下工作：

- 消费预分配命令和 PCM；
- 推进 cursor/fade，合成 source/bus/master/spatial 增益；
- 在预分配 filter/delay/reverb 状态上做算术并写输出。

回调不分配或释放内存，不访问文件、网络、World、游戏对象或射线 callback，不做 playlist 决策。`test_audio_realtime_contract` 对这些函数体做源级约束；实际 PCM 与 TSan 测试补充运行证据。

遮挡射线只从 event trigger、`audio_voice_set_position` 和 listener 实际变化的 `audio_system_update` 调用。listener 的 NaN/Inf 在更新前拒绝，距离和增益先验证再 ray/发布；stop-pending voice 不再发射线或重定位。非空间事件不发射线，空间增益在 GameThread 计算后写入原子快照。

## 失败原子与生命周期

clip/event/playlist 在完整校验名称、引用、容量、数值和格式后才提交。playlist 引用不存在返回 `AUDIO_STALE`，非法长度/格式返回 `AUDIO_INVALID`，容量不足返回 `AUDIO_OVERLOAD`。交叉淡化切换先确认新旧两条命令队列都有空间，再启动新轨和淡出旧轨；不会留下半切换状态。

RESTART 保留 handle 并从头播放；STEAL_OLDEST 提升 generation，使旧 handle 返回 `AUDIO_STALE`。命令环满是非阻塞背压，调用方可在后续帧重试。系统销毁先拆除扩展 node，再清理 legacy source，最后销毁 engine/context 和固定存储。

## Legacy 文件 API

`audio_play`、`audio_play_3d` 和兼容命名的 `audio_play_streamed` 都使用 `MA_SOUND_FLAG_DECODE` 在打开时完整解码，不再禁用 pitch/Doppler。`AudioStreamManager` 的公共 API 保留，但不再从音频回调读取文件或补 decoder 数据。代价是打开大文件会阻塞调用线程并占用对应解码内存；实时安全的扩展路径要求使用预解码 clip。decoded `audio_play_3d` 的源速度 Doppler 由真实 PCM 回归覆盖。

## 验证与限制

- `test_audio_extended`：clip/容量、并发/重触发、stale handle、真实 DSP 接线、逐样本交叉淡化、loop/停止、遮挡/距离、bus/master、legacy WAV、bit-exact fake 和 null 命令生命周期。
- `test_audio_dsp`：手算滤波阶跃、延迟 tap/feedback、混响早期 taps、filter+delay 组合和失败原子。
- normal、ASan+UBSan、TSan 的 `test_audio`/`test_audio_extended`/`test_audio_dsp`/`test_audio_realtime_contract` 均通过。
- 没有真实听测、真实声卡、Windows、macOS 或跨采样率播放验证。简单 DSP/混响不等于物理声学或听感验收。
