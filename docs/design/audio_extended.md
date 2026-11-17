# 扩展音频：事件、音乐、DSP 与空间衰减

日期：2026-11-03

## 已交付边界

P10 在现有 `AudioSystem` 和同一个 miniaudio `ma_engine` 内实现。新增代码位于 `engine/src/audio/audio_extended.{h,c}` 与 `audio_dsp.{h,c}`；没有第二个设备或软件混音器。`test_audio_extended` 通过真实 miniaudio API 驱动 fake（`noDevice` + `ma_engine_read_pcm_frames`）和 null 后端，`test_audio_dsp` 验证确定性 PCM。

已实现：

- 命名 clip 与声音事件；`ALLOW`、`RESTART`、`IGNORE` 重触发，以及容量满时 `REJECT` 或 `STEAL_OLDEST`。
- 带 generation 的 voice handle；自然结束、显式停止和抢占后的 stale handle 拒绝。
- 最多 16 轨的音乐 playlist、循环播放、零淡化切轨及样本级线性交叉淡化。音乐只使用预留 voice 0/1。
- 最多四级的可组合 DSP：一极低通滤波、反馈延迟和固定四 tap 混响。delay/reverb 可带 filter 组成同一条链。
- LogicThread 射线回调驱动的遮挡，以及与既有逆距离模型一致的距离衰减；扩展 voice 同时遵守现有 bus/master 增益。
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

LogicThread 是唯一命令生产者。START、STOP、RAMP 都是值命令，携带稳定内部 PCM 指针、公共 serial、独立内部 epoch 和预计算配置；head/tail 用 C11 release/acquire 原子发布。每次 START 都递增 epoch，公共 RESTART handle 不变；STOP/RAMP 只作用于对应 epoch，旧完成不能回收新播放。空间快照在单个 64-bit 原子值中打包 32-bit revision 和 32-bit gain bits，所有写入均通过整快照 CAS，START 初始 gain 的 CAS 失败不重试、不覆盖新 revision。LogicThread 的 position/listener 发布若因 callback START CAS 先成功而失败，会重新验证 epoch、revision 和当前快照后用新增益重试，不会重试旧 START；主线程 revision 只在发布成功后提交。`spatial_epoch` 标记快照归属，voice_read 在 snapshot 前后各 acquire-load 一次 epoch，只有两次结果相同且等于 `playing_epoch` 才采用新快照，否则保留 callback 私有的已应用增益。回调只有在消费 START 时才归零 cursor、发布初始空间快照并发布 `started_epoch`；音乐 update 仅在 `started_epoch == voice->epoch` 时读取 cursor。自然结束用 `completed_epoch` 与当前 epoch 匹配后才能回收 voice。队列空间预检后才发布，失败保持原状态。

epoch 0 保留为未启动/无效值；max-1→max 可以启动，达到 UINT64_MAX 后该 voice 退休，后续 START 返回 `AUDIO_OVERLOAD`，不绕回或重置。revision 在 voice 生命周期内单调递增，达到 UINT32_MAX 后 position/listener 和新 START 均拒绝，不回绕。快照字段大小由 C11 静态断言约束，原子类型不要求 lock-free。

PCM 回调只做以下工作：

- 消费预分配命令和 PCM；
- 推进 cursor/fade，合成 source/bus/master/spatial 增益；
- 在预分配 filter/delay/reverb 状态上做算术并写输出。

回调不分配或释放内存，不访问文件、网络、World、应用对象或射线 callback，不做 playlist 决策。`test_audio_realtime_contract` 对这些函数体做源级约束；实际 PCM 与 TSan 测试补充运行证据。

遮挡射线只从 event trigger、`audio_voice_set_position` 和 listener 实际变化的 `audio_system_update` 调用。listener 的 NaN/Inf 在更新前拒绝，距离和增益先验证再 ray/发布；stop-pending voice 不再发射线或重定位。非空间事件不发射线，空间增益在 LogicThread 计算后写入原子快照。

## 失败原子与生命周期

clip/event/playlist 在完整校验名称、引用、容量、数值和格式后才提交。playlist 引用不存在返回 `AUDIO_STALE`，非法长度/格式返回 `AUDIO_INVALID`，容量不足返回 `AUDIO_OVERLOAD`。交叉淡化切换先确认新旧两条命令队列都有空间，再启动新轨和淡出旧轨；不会留下半切换状态。

RESTART 保留 handle 并从头播放；STEAL_OLDEST 提升 generation，使旧 handle 返回 `AUDIO_STALE`。命令环满是非阻塞背压，调用方可在后续帧重试。系统销毁先拆除扩展 node，再清理 legacy source，最后销毁 engine/context 和固定存储。

## Legacy 文件 API

`audio_play`、`audio_play_3d` 和兼容命名的 `audio_play_streamed` 都使用 `MA_SOUND_FLAG_DECODE` 在打开时完整解码，不再禁用 pitch/Doppler。`AudioStreamManager` 的公共 API 保留，但不再从音频回调读取文件或补 decoder 数据。代价是打开大文件会阻塞调用线程并占用对应解码内存；实时安全的扩展路径要求使用预解码 clip。decoded `audio_play_3d` 的源速度 Doppler 由真实 PCM 回归覆盖。

## PCM 流的采样率转换与抗混叠

`audio_pcm_stream_open_rate` 接受 8000..192000 Hz 的流，混音回调用整数位置（以 1/48000 帧为单位）做线性插值转换到 48 kHz。高于 48 kHz 的流先经过 4 阶 Butterworth 低通（两级 RBJ biquad，Q = 0.5412 / 1.3066，截止 21600 Hz，按流采样率用双线性变换在 open 时算系数），再插值；否则 24 kHz 以上的内容会折回可听频段。96 kHz 输入时 1 kHz 基本无衰减，30 kHz 约 -19.5 dB，流的 Nyquist 频率处为零点；紧贴 24 kHz 以上的衰减较小。

滤波在环形缓冲里原地进行：`[tail, head)` 的帧在 tail 越过之前归混音回调所有，生产者不会改写。回调私有的 `filtered` 记录 tail 之后已滤过的帧数，读插值所需帧之前、以及释放被跨过的帧之前都先按顺序补滤，所以每帧恰好滤一次，抽取跳过的帧也会经过滤波器。滤波状态、系数和 `filtered` 与位置 `pos` 遵守同一规则：open 在槽位关闭时重置，回调只在看到 `open` 后读写。滤波函数不分配、不加锁，纳入 `test_audio_realtime_contract` 的检查范围。≤48 kHz 的流不滤波；线性插值上采样产生的镜像也不滤除（可改用下面的 sinc 模式）。

### sinc 重采样

`audio_pcm_stream_set_resample(as, h, AUDIO_RESAMPLE_SINC)` 把流的插值换成 16 tap Lanczos 核（a = 8，taps 为 i-7 .. i+8，权重归一化，常数原样通过；f = 0 时直接取帧 i）。open 时恢复为 `AUDIO_RESAMPLE_LINEAR`，已有调用方输出不变；未知模式返回 `AUDIO_INVALID`。模式是一个原子值，混音回调每次读取一次，所有者线程随时可改。

核需要位置之后 `AUDIO_PCM_STREAM_SINC_LOOKAHEAD`（8）帧：在这之前流播放静音并计入 underrun，位置不动；这一条件在整帧位置上同样成立，所以延迟固定为 8 个源帧（16 kHz 时 0.5 ms）。tail 之前的帧已交还生产者，回调在两种模式下都把每个释放的帧（快流为低通之后的值）复制进自己的 8 帧历史环，所以中途切到 sinc 时用的是真实的过去帧；open 把历史清零，流开始之前的帧视为 0。高于 48 kHz 的流先低通，再读取到 i+8 为止的帧。48 kHz 的流没有小数位置，sinc 模式不改变它，也没有前瞻延迟。

16 kHz 输入的 4 kHz 正弦（幅度 0.5）与理想 48 kHz 正弦的 RMS 误差：线性插值 0.075，sinc 0.00026。没有多相表，每个输出帧计算 32 次 `sin`；强降采样仍由 Butterworth 负责抗混叠，核宽不随比例变化。clip voice 不重采样（只接受 48 kHz）。

## PCM 流的声像

`audio_pcm_stream_set_panning(as, h, enabled)` 为空间流打开立体声声像（open 时关闭；未 `set_spatial` 的流返回 `AUDIO_REJECTED`）。监听者右向量为 `forward × up`（forward -Z、up +Y 时为 +X），`pan` 为声源方向与右向量夹角的余弦，按等功率规律 `θ = (pan + 1)π/4` 得到左 `cos θ`、右 `sin θ`：正中两侧各 -3 dB，正右方只有右声道。声源与监听者重合，或 forward 与 up 平行时取正中。声像本身不区分前后、上下（没有 HRTF、耳间时差）；前后可用下面的后方提示。

左右增益在 `set_spatial`、`set_position`、监听者更新时于所有者线程计算，打包成一个 64 位原子值发布，混音回调不会看到只更新了一侧的增益。单声道流先复制到两声道再声像；立体声流的每个声道乘以本侧增益。关闭声像恢复两侧增益为 1。

### 后方提示

`audio_pcm_stream_set_rear_cue(as, h, enabled)` 为空间流打开一个模拟头部遮挡的一极低通 `y += α(x − y)`（open 时关闭；未 `set_spatial` 返回 `AUDIO_REJECTED`）。后方程度 `b = max(0, −cos∠(声源 − 监听者, forward))`，`α = 1 − b(1 − α_rear)`，`α_rear = 1 − exp(−2π·5000/48000) ≈ 0.48`：侧面及前方 α = 1，不滤波，输出与关闭时逐位相同；正后方截止约 5 kHz，24 kHz 处约为原幅度的 1/3。声源与监听者重合或 forward 为零向量时不滤波。

α 与距离增益一起在所有者线程计算（`set_spatial`、`set_position`、监听者更新），作为一个原子 f32 发布，混音回调每次读一次。滤波在插值之后、增益与声像之前进行；α = 1 时状态跟随信号，所以打开提示或声源转到身后时从当前信号开始，没有旧状态带来的咔嗒声。状态归回调所有，与 `pos` 一样由 open 重置。

### 耳间时差

`audio_pcm_stream_set_interaural_delay(as, h, enabled)` 为空间流打开耳间时差：离声源较远的耳朵晚听到声音（open 时关闭；未 `set_spatial` 返回 `AUDIO_REJECTED`）。侧向量 `p` 取声像使用的 `listener_pan`（与右向量夹角的余弦），按 Woodworth 模型 `秒数 = r / c × (asin|p| + |p|)`，`r = AUDIO_PCM_STREAM_HEAD_RADIUS`（0.0875 m），`c = AUDIO_PCM_STREAM_SPEED_OF_SOUND`（343 m/s），乘 48000 后 `lrint` 取整：正前、正后、正上方和与监听者重合时为 0，正侧方为 `AUDIO_PCM_STREAM_ITD_MAX_FRAMES`（31 帧，约 0.65 ms），30° 时为 13 帧。声源在右侧时延迟左声道，在左侧时延迟右声道。

带符号的帧数（正数表示左耳延迟）与增益、声像一起在所有者线程计算并作为一个原子 int 发布，混音回调每次读一次。混音器在后方提示之后、增益与声像之前把每个播放帧写入 64 帧（`AUDIO_PCM_STREAM_ITD_LINE_FRAMES`）的延迟线，远端耳朵从中读取延迟后的样本。延迟关闭时延迟线也照常写入，所以打开延迟或声源转到侧面时播放的是真实的历史，而不是插入静音。open 把延迟线清零。延迟变化（声源或监听者移动、开关提示）在新旧延迟之间用 32 帧（`AUDIO_PCM_STREAM_ITD_FADE_FRAMES`，约 0.67 ms）线性交叉淡化，两端耳朵各按自己的延迟读取，延迟未变的那只耳朵不混音、保持逐位精确。淡化进行中目标又变化时等这次淡化结束再开始下一次，输出保持连续。尚未播放过的延迟线（流在播放前摆位、voice 的每次 START）直接采用目标延迟，不淡化。

### 事件 voice 的声像

`AudioEventDesc.panned = true`（必须同时设置 `spatial`，否则 `audio_event_register` 返回 `AUDIO_INVALID`）让空间事件使用与 PCM 流相同的监听者声像模型和等功率规律（两者共用 `listener_pan` 与 `pan_gains`）。未设置的事件输出不变。

START 命令携带初始 pan，但不写 `pan_snapshot`：`spatial_begin_start` 推进增益 revision 时保留旧增益，旧 epoch 的 PCM 可能采用这个 revision，因此它也必须保留旧 pan。之后的更新（`audio_voice_set_position`、监听者移动）先写 `pan_snapshot = (revision, pan)`，再 CAS 增益快照；混音回调采用增益 revision R 时，只有 `pan_snapshot` 的 revision 也等于 R 才采用其中的 pan，否则保留上一个 pan，直到采用该 revision。这样重启后的新 pan 不会作用到旧 epoch 的 PCM。左右增益在 voice DSP 链之前施加；单声道 clip 复制到两声道，立体声 clip 每个声道乘以本侧增益。

### 事件 voice 的后方提示

`AudioEventDesc.rear_cue = true`（必须同时设置 `spatial`，否则 `audio_event_register` 返回 `AUDIO_INVALID`）让空间事件使用与 PCM 流相同的后方低通，系数由同一个 `rear_cue_alpha` 计算。未设置时系数恒为 1，输出不变。

系数与 pan 走同一协议：START 命令携带初始系数而不写 `rear_snapshot`；之后的 `audio_voice_set_position` 与监听者更新先写 `rear_snapshot = (revision, α)`，再 CAS 增益快照；混音回调采用增益 revision R 时，只有 `rear_snapshot` 的 revision 也是 R 才采用其中的 α。每个 voice 两声道各有滤波状态，消费 START 时清零；滤波在增益、声像与 DSP 链之前，α = 1 时状态跟随信号，所以声源转到身后时从当前信号开始。

### 事件 voice 的耳间时差

`AudioEventDesc.interaural_delay = true`（必须同时设置 `spatial`，否则 `audio_event_register` 返回 `AUDIO_INVALID`）让空间事件使用与 PCM 流相同的耳间时差，帧数由同一个 `interaural_delay_frames` 计算。未设置时延迟恒为 0，输出不变。

帧数与 pan、后方系数走同一协议：START 命令携带初始帧数（`spatial_itd`）而不写 `itd_snapshot`；之后的 `audio_voice_set_position` 与监听者更新先写 `itd_snapshot = (revision, 帧数)`，再 CAS 增益快照；混音回调采用增益 revision R 时，只有 `itd_snapshot` 的 revision 也是 R、且该事件打开了耳间时差才采用其中的帧数，所以 RESTART 后的新延迟不会作用到旧 epoch 仍在播放的 PCM。每个 voice 有自己的 64 帧延迟线，消费 START 时清零；延迟放在后方提示之后、增益与声像之前。PCM 流与 voice 共用 `itd_line_push`。

### 高度提示

`audio_pcm_stream_set_elevation_cue(as, h, enabled)` 为空间流打开高度提示（open 时关闭；未 `set_spatial` 返回 `AUDIO_REJECTED`）。没有 HRTF 时用频谱倾斜区分上下：上方声源保留更多高频，下方声源被躯干遮挡、高频衰减。`e` 为声源方向与监听者 up 向量夹角的余弦（up 不必是单位长度），倾斜量 `s` 在上方为 `e × AUDIO_PCM_STREAM_ELEVATION_BOOST`（0.5），在下方为 `e`；声源与监听者重合或 up 为零向量时为 0。

每声道一个转折频率为 `AUDIO_PCM_STREAM_ELEVATION_CUTOFF_HZ`（7 kHz）的一阶低通 `lp += a (x − lp)` 始终运行，输出 `x + s (x − lp)`：上方为高架提升，正下方即低通本身，水平声源（`s = 0`）逐位不变。低通在提示关闭或水平时照常运行，所以提示打开或声源移到上下方时从当前信号开始，没有旧状态造成的爆音。`s` 与增益、后方系数一起在所有者线程计算并作为一个原子 f32 发布，混音回调每次读一次；倾斜位于后方提示之后、耳间时差之前。open 把状态清零。事件 voice 尚无高度提示。

## 验证与限制

- `test_audio_extended`：clip/容量、并发/重触发、stale handle、真实 DSP 接线、逐样本交叉淡化、loop/停止、遮挡/距离、bus/master、legacy WAV、bit-exact fake 和 null 命令生命周期。
- `test_audio_dsp`：手算滤波阶跃、延迟 tap/feedback、混响早期 taps、filter+delay 组合和失败原子。
- normal、ASan+UBSan、TSan 的 `test_audio`/`test_audio_extended`/`test_audio_dsp`/`test_audio_realtime_contract` 均通过。
- 降采样低通由 `test_audio_extended` 中的双精度参考模型（96 kHz、88.2 kHz）、Nyquist 音、30 kHz / 1 kHz 正弦、立体声分离和重开复位覆盖；`test_voice_playback` 在 96 kHz 下跑生产者/关闭/混音线程竞争。
- sinc 重采样由双精度 Lanczos 参考模型（16 kHz、88.2 kHz 经低通、24 kHz 立体声）、前瞻等待、高频正弦误差、引擎采样率不变、模式切换的历史和重开复位覆盖。
- 后方提示由阶跃响应参考模型（PCM 流正后方与 45°、事件正后方）、前方/侧面/重合逐位不变、监听者转身、RESTART 与 revision 门控、立体声状态分离和重开复位覆盖。
- 没有真实听测、真实声卡、Windows 或 macOS 验证。简单 DSP/混响不等于物理声学或听感验收。
