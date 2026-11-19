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

每声道一个转折频率为 `AUDIO_PCM_STREAM_ELEVATION_CUTOFF_HZ`（7 kHz）的一阶低通 `lp += a (x − lp)` 始终运行，输出 `x + s (x − lp)`：上方为高架提升，正下方即低通本身，水平声源（`s = 0`）逐位不变。低通在提示关闭或水平时照常运行，所以提示打开或声源移到上下方时从当前信号开始，没有旧状态造成的爆音。`s` 与增益、后方系数一起在所有者线程计算并作为一个原子 f32 发布，混音回调每次读一次；倾斜位于后方提示之后、耳间时差之前。open 把状态清零。

### 事件 voice 的高度提示

`AudioEventDesc.elevation_cue = true`（必须同时设置 `spatial`，否则 `audio_event_register` 返回 `AUDIO_INVALID`）让空间事件使用与 PCM 流相同的频谱倾斜，倾斜量由同一个 `elevation_amount` 计算；未设置时恒为 0，输出不变。

倾斜量与 pan、后方系数走同一协议：START 命令携带初始值（`spatial_tilt`）而不写 `tilt_snapshot`；之后的 `audio_voice_set_position` 与监听者更新先写 `tilt_snapshot = (revision, s)`，再 CAS 增益快照；混音回调采用增益 revision R 时，只有 `tilt_snapshot` 的 revision 也是 R 才采用其中的值，所以 RESTART 后的新倾斜量不会作用到旧 epoch 仍在播放的 PCM。没有打开提示的事件发布的值恒为 0，因此混音器不再单独检查开关。每个 voice 两声道各有低通状态，消费 START 时清零，低通始终运行；倾斜位于后方提示之后、耳间时差之前，与流相同。

## HRTF

`engine/src/audio/audio_hrtf.{h,c}` 提供集合与渲染器；空间 PCM 流可通过 `audio_pcm_stream_set_hrtf` 使用（见下文「PCM 流的 HRTF」），空间事件可通过 `AudioEventDesc.hrtf` 使用（见「事件 voice 的 HRTF」）。方向用方位角（度，0 为正前方，向右为正，[-180, 180]）和仰角（度，向上为正，[-90, 90]）表示，单位向量为 `(cos el·sin az, sin el, cos el·cos az)`。

- `AudioHrtfSet`：1..2048 个方向，每耳 1..128 个 tap，采样率 8000..192000。创建方式有三种：`audio_hrtf_set_create` 复制调用者的数组；`audio_hrtf_set_parse` 读取 `BHRT` 文件；`audio_hrtf_set_create_spherical_head` 生成内置结构模型。参数非法、角度或样本非有限或越界（|样本| > 4）、两个方向的单位向量各分量相差都不超过 1e-6 时返回 `AUDIO_INVALID`；内存不足返回 `AUDIO_OVERLOAD`。只有成功时才写 `*out`。
- `audio_hrtf_set_nearest`：返回点积最大的方向，相同时取较小下标；角度越界、非有限或 set 为 NULL 返回 `UINT32_MAX`。
- `BHRT` v1（小端）：u32 magic `BHRT`、u32 版本 1、u32 采样率、u32 taps、u32 count，然后每个方向依次为 f32 方位角、f32 仰角、taps 个 f32 左耳样本、taps 个 f32 右耳样本。文件大小必须恰好等于 `20 + count × (8 + 8 × taps)`，各字段遵守 create 的规则。
- 球头模型（Brown 与 Duda，1998）：头半径 0.0875 m，声速 343 m/s。共 217 个方向：仰角 -45..75、方位角 -165..180，均以 15 度为步长，另加正上方一个。每只耳朵的处理如下：
  - θ 为声源与耳轴的夹角，延迟按 Woodworth 公式计算后取整到帧；
  - 头影为一极一零滤波器，`α(θ) = 1.05 + 0.95·cos(θ·180/150)`，经双线性变换离散化，Nyquist 处增益为 α(θ)；
  - 五个耳廓回声，延迟依赖方位角与仰角，分数延迟用线性插值；
  - 最后按全集峰值归一化。
  右耳由镜像方位角的左耳得到，所以镜像方向的左右耳逐位互换；正前方与正后方两耳逐位相同。
- `audio_hrtf_renderer_set_index(r, index)` 与 `set_direction` 规则相同，只是直接给集合下标（越界返回 `AUDIO_INVALID`）；`set_direction` 等于 nearest 加 set_index。
- `AudioHrtfRenderer`：由调用者持有，`process` 不分配内存、不加锁。历史缓冲每个样本写两次（`cursor` 与 `cursor + taps`），因此卷积总能读到一段连续窗口。第一次 `process` 之前设置的方向立即生效。之后换方向时，在 `AUDIO_HRTF_FADE_FRAMES`（64）帧内对新旧两个滤波器的输出做线性交叉淡化，淡化第 i 帧新输出的权重为 i/64，最后一帧完全是新滤波器的输出。淡化进行中的修改要等这次淡化结束，下一帧开始新的淡化；与当前滤波器相同的方向不会触发淡化。

### PCM 流的 HRTF

`audio_pcm_stream_set_hrtf(as, h, set)` 为空间流挂上 HRTF 集合（采样率必须是 `AUDIO_PCM_SAMPLE_RATE`，否则 `AUDIO_INVALID`；未 `set_spatial` 先返回 `AUDIO_REJECTED`；open 时没有集合）。

- 所有者线程：位置或监听者变化时，把声源方向换到监听者坐标系（right = forward × up，up' = right × forward，均归一化），方位角 = atan2(x, z)，仰角 = atan2(y, √(x² + z²))，取最近的集合下标，作为原子值与其他空间参数一起发布。声源与监听者重合或没有 right 向量时取正前方。
- 混音回调：每次回调读一次集合指针（seq_cst）和下标。每次 `set_hrtf` 都会递增一个挂接计数；回调看到新计数时重新 init 渲染器（历史清零），再按下标 `set_index`：第一帧立即生效，之后换方向在 64 帧内交叉淡化。每个输出帧取重采样后左右声道的平均 `0.5 (l + r)` 送入渲染器，结果乘以流增益替换立体声输出。
- 挂上集合时声像、后方提示、高度提示和耳间时差都不作用于输出，但它们的滤波状态和延迟线照常运行，所以摘掉集合后从当前信号继续，没有旧状态造成的爆音。
- `set == NULL` 摘掉集合。函数与 close 一样等待正在进行的回调结束（`reading` 握手）才返回，因此集合可以在摘掉或流关闭之后销毁，挂着时不能销毁。
- 渲染器的处理函数纳入 `test_audio_realtime_contract`（不分配、不做文件 I/O）。

### 事件 voice 的 HRTF

`AudioEventDesc.hrtf` 为空间事件指定 HRTF 集合（NULL 表示不用）。注册时要求 `spatial` 为真且集合采样率为 `AUDIO_PCM_SAMPLE_RATE`，否则 `AUDIO_INVALID`。集合由调用者持有，必须比 `AudioSystem` 活得久（事件注册后不能注销，所以没有摘除路径）。

- 所有者线程：trigger、`audio_voice_set_position` 和监听者更新时，用与 PCM 流相同的 `hrtf_direction_index` 取最近下标。trigger 把下标放在 START 命令里；之后的更新与声像、后方、耳间时差、高度提示一样，以 `(revision, index)` 写进 `hrtf_snapshot`，再发布增益快照，混音回调只在同一 revision 下采用。
- 混音回调：START 时每个 voice 重新 init 自己的渲染器（历史清零，RESTART 重触发同样清零），并立即采用 START 的下标；之后换方向在 64 帧内交叉淡化。每帧取 clip 左右声道平均 `0.5 (l + r)` 送入渲染器，结果乘以 voice 增益（音量、淡入淡出、bus、master、距离）。DSP 链仍在 HRTF 之后作用于立体声结果。
- 挂上集合时声像、后方提示、高度提示和耳间时差都不作用于输出，它们的状态照常运行。

## 麦克风采集

`engine/src/audio/audio_capture.{h,c}` 打开输入设备，把采到的帧放进单生产者单消费者的 16 位环形缓冲，所有者线程读取后可直接交给 `break_voice_encode*`。

- `AudioCaptureConfig`：`backend`（DEFAULT 为系统默认输入，NULL 为 miniaudio 的静音空设备，FAKE 没有设备、由 `audio_capture_inject` 写入）、采样率 8000..192000、1 或 2 声道、环形缓冲帧数（2 的幂，最多 2^20）。参数非法返回 `AUDIO_INVALID`，内存不足 `AUDIO_OVERLOAD`，设备打不开 `AUDIO_FAILED`；只有成功时才写 `*out`。创建后处于停止状态。
- `audio_capture_start` / `stop` 幂等；`destroy` 先停止正在运行的设备（`ma_device_uninit` 等待回调结束）。停止前采到的帧仍可读取。
- 转换：非有限值记为 0，其余限制在 [-1, 1] 后按 `lrintf(x × 32767)` 取整。
- 环形缓冲：生产者（设备回调，FAKE 时为注入线程）持有 `head`，读取者持有 `tail`，均为自由增长的 u32，用 release/acquire 发布。缓冲满时丢弃最新的帧并计入 `audio_capture_overruns`。回调不阻塞、不分配、不写日志，并纳入 `test_audio_realtime_contract`。
- 输入设备选择：`audio_capture_list_devices(backend, out, capacity)` 列出输入设备（名称、序号 id、是否默认），返回设备总数，可能大于 capacity；FAKE 或枚举失败返回 0。`audio_capture_create_named(config, name, out)` 按名称打开设备，NULL 或空名称打开默认设备；没有该名称的设备或 FAKE 带名称时返回 `AUDIO_REJECTED`。设备 id 指向枚举它的 context，所以每个采集对象持有自己的 context，与设备一起释放。`audio_capture_device_name` 返回实际打开的设备名（FAKE 为 "fake"），超长时截断。
- 帧以配置的采样率与声道数交付：设备原生格式不同时由 miniaudio 的内置转换完成。
- 设备丢失与重新打开（热插拔）：
  - `audio_capture_lost` 表示设备在没有停止请求时停止了（拔出、被系统禁用或占用）。来源有两个：miniaudio 的 `stopped` 通知（只在采集处于「已请求启动」状态时才算丢失；`stop`、`destroy` 与 reopen 关闭旧设备时不算），以及设备状态读到已停止而采集仍应运行（部分后端在拔出的设备停不下来时不发停止通知）。
  - 丢失期间 `audio_capture_running` 为 false，`start` 返回 `AUDIO_FAILED`，FAKE 的 `inject` 返回 `AUDIO_REJECTED`；丢失前采到的帧仍可读取。
  - `audio_capture_reroutes` 统计后端自行把流切到另一设备的次数（`rerouted` 通知），采集继续运行。
  - `audio_capture_reopen(capture, name)` 在第二个设备槽中打开指定设备（NULL 或空名称为默认设备），成功后先切换活动槽（旧槽的通知从此被忽略），再关闭旧设备（`ma_device_uninit` 等待其最后一次回调，环形缓冲始终只有一个生产者），清除丢失状态，原先在运行则启动新设备。环形缓冲与其中的帧保留。未知名称或 FAKE 带名称返回 `AUDIO_REJECTED`，打不开返回 `AUDIO_FAILED`，失败时旧设备、设备名与状态不变。丢失后调用过 `stop` 的，reopen 后保持停止。
  - 新设备出现没有通知：调用者轮询 `audio_capture_list_devices`。
  - `audio_capture_simulate_event`（FAKE 与 NULL 后端，供测试）通过同一处理函数投递丢失或重路由事件；DEFAULT 后端返回 `AUDIO_REJECTED`。
- 自动增益、噪声门（时域降噪）、回声消除与频谱降噪见下面各节。

## 自动增益（AGC）

`engine/src/audio/audio_agc.{h,c}` 在所有者线程上原地处理采集到的 16 位帧，放在 `audio_capture_read_i16` 之后、`break_voice_encode*` 之前，使不同音量的说话者得到相近的电平。不分配内存，状态由调用者持有。

- `AudioAgcConfig`：采样率 8000..192000、1 或 2 声道、目标电平 -60..0 dBFS、最大增益 0..60 dB、下降时间常数（attack）0.1..1000 ms、上升时间常数（release）1..10000 ms、门限 -120..0 dBFS 且低于目标。超出范围或 NaN 返回 `AUDIO_INVALID`，失败时不写 `*agc`。初始增益 0 dB。
- 电平：各声道 x² 的平均（x = 样本 / 32768）经 10 ms 一阶平滑，取 `10 log10`。
- 期望增益 = 目标 − 电平，限制在 ±最大增益。电平低于门限（包括完全静音）时增益保持不变，所以静音和底噪不会被放大。
- 增益每帧按一阶时间常数逼近期望值：增益下降用 attack，上升用 release；所有声道用同一个增益，保留声道间的比例。
- 输出 `nearbyint(x × 10^(增益/20))`，限制在 i16 范围内，不会回绕。
- 逐帧处理，分块方式不影响输出。增益用双精度保存：接近稳态时每帧的步长远小于 f32 的精度。

## 噪声门（降噪）

`engine/src/audio/audio_noise_gate.{h,c}` 是时域降噪：一个学习底噪的向下扩展器，衰减接近底噪的帧，让高出底噪的语音通过。它与 AGC 一样在所有者线程上原地处理 16 位帧，不分配内存，状态由调用者持有。建议顺序是 `audio_capture_read_i16` → 噪声门 → AGC → `break_voice_encode*`，这样 AGC 不会放大门关闭时残留的底噪。

- `AudioNoiseGateConfig`：采样率 8000..192000、1 或 2 声道、开门阈值（高出底噪）3..40 dB、关门衰减 0..80 dB、开门时间常数（attack）0.1..1000 ms、关门时间常数（release）1..10000 ms、底噪上升速度 0.1..60 dB/s、初始底噪 -120..0 dBFS。超出范围或 NaN 返回 `AUDIO_INVALID`，失败时不写 `*gate`。初始为开门（0 dB），电平和底噪都从初始底噪开始。
- 电平：各声道 x² 的平均经 10 ms 一阶平滑，取 `10 log10`，不低于 -120 dBFS（完全静音即 -120）。电平取自施加增益之前的输入。
- 底噪：`floor = min(floor + rise / rate, level)`。电平低于底噪时底噪立即跟到电平；否则每帧最多上升 `rise / rate` dB，且不超过电平。
- 电平 ≥ 底噪 + 阈值时目标增益为 0 dB，否则为 −衰减。增益每帧按一阶时间常数逼近目标：上升（开门）用 attack，下降（关门）用 release。所有声道共用一个增益。增益在 [−衰减, 0] dB 之内，输出 `nearbyint(x × 10^(增益/20))` 不会超出 i16 范围。
- 持续不断的稳态声音（例如长时间的单音）会以上升速度抬高底噪，最终使门关闭。上升速度决定这需要多久：阈值 10 dB、上升速度 20 dB/s 时，高出底噪 30 dB 的声音约 1 秒后开始被衰减（底噪要上升 20 dB）。
- 逐帧处理，分块方式不影响输出。
- 本模块本身仍是时域噪声门，不做谱减；需要频谱处理时使用下文「频谱降噪」。门打开时，与语音同时存在的底噪原样通过。

## 回声消除（AEC）

`engine/src/audio/audio_echo_canceller.{h,c}` 消除扬声器播放的远端声音被麦克风再次采到形成的回声。它用归一化最小均方（NLMS）自适应滤波器从播放参考信号学习扬声器到麦克风的路径，再从采集中减去预测的回声。处理在所有者线程上原地进行，只有 create 分配内存。建议顺序是 `audio_capture_read_i16` → 回声消除 → 噪声门 → AGC → `break_voice_encode*`。

- `AudioEchoCancellerConfig`：采样率 8000..192000、滤波器长度 1..`AUDIO_ECHO_CANCELLER_MAX_TAPS`（8192）帧、步长 μ 0.001..1、双讲阈值 0..1（0 关闭检测）、双讲保持时间 0..1000 ms。超出范围或 NaN 返回 `AUDIO_INVALID`，内存不足返回 `AUDIO_OVERLOAD`，只有成功时才写 `*out`。权重和历史初始为 0。
- `audio_echo_canceller_process_i16(aec, reference, capture, frames)`：单声道。`reference` 是与 `capture` 对齐的播放帧（同一帧或更早到达麦克风的播放样本），调用者负责对齐；滤波器覆盖不超过 `taps` 帧的回声路径。`capture` 被替换为采集减去预测回声。
- 记 x = 参考 / 32768、d = 采集 / 32768。预测 `y = Σ w(k) x(n−k)`，误差 `e = d − y`，输出 `nearbyint(e × 32768)` 并限制在 i16 范围内。
- 权重更新 `w(k) += μ e x(n−k) / (Σ x² + taps × 1e-6)`。窗口能量由 i16 平方和精确累加（加入最新样本、减去离开窗口的样本），不会有浮点漂移。历史缓冲每个样本写两次（i 与 i + taps），所以卷积总是读一段连续窗口。
- Geigel 双讲检测：阈值大于 0 且 `|d| > 阈值 × max|x(n−k)|` 时认为近端在说话，本帧及之后保持时间内的帧都不更新权重，回声照常消除。两端都静音不算双讲。检测需要近端声音超过阈值才触发，所以近端开口的前几帧仍会更新权重；步长越小，这几帧带来的偏移越小。`audio_echo_canceller_near_end_active` 报告最近帧的检测或 hangover 状态，零 hangover 的检测帧也为 true，零帧调用保留状态，检测关闭时恒为 false。
- `audio_echo_canceller_reset` 清零权重、历史、保持计数与近端状态；`audio_echo_canceller_weight(aec, k)` 返回回声路径估计的第 k 个权重（越界或 NULL 为 0）。
- 逐帧处理，分块方式不影响输出。每帧的计算量与 `taps` 成正比，8192 tap、48 kHz 时每秒约 8 亿次乘加，长回声路径需要权衡。
- 未做：频域或分块的快速实现、立体声参考。非线性残余的 postprocessor 见下一节；参考与采集的对齐见「延迟估计与参考延迟线」。

## 残余回声抑制

`engine/src/audio/audio_residual_echo_suppressor.{h,c}` 在 AEC 之后抑制仍未消除的非线性回声。它使用调用者持有的状态，不分配、不加锁，处理单声道 i16。可使用 `audio_residual_echo_suppressor_process_with_aec` 逐帧执行 AEC、读取近端状态并抑制残余；该函数已经执行 AEC，调用者不能重复处理同一 capture。自定义检测仍可使用独立 `process_i16`。当前只有库接口和测试，没有生产采集管线的自动接线。

- 配置：采样率 8000..192000、衰减 0..80 dB、比值余量 0..40 dB、attack 0.1..1000 ms、release 1..10000 ms、路径上升速度 0.1..60 dB/s、初始路径 -120..0 dB、参考门限 -80..0 dBFS、hangover 0..1000 ms。非法或 NaN 返回 `AUDIO_INVALID`，且不改调用者状态。
- 参考与 AEC 误差功率分别经 10 ms 一阶平滑。参考功率达到门限时视为活动；停止后按 hangover 保留最后活动参考功率，以覆盖衰减中的回声尾部。
- 可控残余帧计算 `10 log10(max(error,1e-12)/max(reference,1e-12))`，学习值不超过 0 dB。路径每次下降立即跟随，上升不超过配置速度且不超过观测值。比值不超过 `path + margin` 时以配置的负衰减为目标，否则暂时打开增益并继续适应。
- `near_end_active=true` 时路径冻结且增益打开。独立接口的标志由调用者提供；集成接口逐帧复用 AEC 的 Geigel/hangover 状态，不把最后帧状态错误应用到整块历史。
- 增益打开使用 attack，关闭使用 release；增益始终在 [-reduction,0] dB，不放大。`gain_db`、`path_db` 提供诊断，NULL 分别返回 0 和 -120。
- `reset` 清空包络、保持的参考功率、路径、增益与 hangover。任意分块与整块逐位一致。
- 未做：频谱相干性抑制、立体声、生产采集管线接线与真实声学环境验证。

## 延迟估计与参考延迟线

`engine/src/audio/audio_delay_estimator.{h,c}` 从信号本身估计播放参考到采集回声的延迟，再用延迟线把参考对齐后交给回声消除。扬声器到麦克风的总延迟（输出缓冲、设备延迟、声学路径）常有几十毫秒，远超回声消除器的滤波器长度；对齐后滤波器只需覆盖房间的回声尾部。单声道，所有者线程，只有 create 分配内存。

- `AudioDelayEstimatorConfig`：最大延迟 1..96000 帧、相关窗口 16..96000 帧。超出范围返回 `AUDIO_INVALID`，内存不足返回 `AUDIO_OVERLOAD`，只有成功时才写 `*out`。
- `audio_delay_estimator_push_i16(est, reference, capture, frames)` 追加对齐推送的两路信号，保留最近 窗口 + 最大延迟 帧（每个样本写两次，窗口总是连续的）。
- `audio_delay_estimator_estimate`：取最近 `window` 个采集帧 c(i)，对每个延迟 L = 0..最大延迟计算 `S(L) = Σ c(i) r(i−L) / √(Σ c² · Σ r²)`，平方和与互相关和都用 i64 精确累加。返回 |S| 最大的 L（相同时取较小的 L）和该 S（[-1, 1]，反相回声为负）。推送不足 窗口 + 最大延迟 帧、采集窗口静音或所有参考窗口都静音时返回 false，输出不变。每次估计的计算量为 (最大延迟 + 1) × 窗口 次乘加，例如最大延迟 4800、窗口 4096 约 2000 万次，适合每秒估计一次而不是每帧。`reset` 只清零推送计数。
- `AudioDelayLine`：`audio_delay_line_create(最大延迟 0..96000)`，`set_delay`（超过最大值返回 `AUDIO_INVALID`），`delay`，`process_i16(line, in, out, frames)` 输出 `out[n] = in[n − 延迟]`，第一帧之前为静音，`out` 可以与 `in` 是同一缓冲区。默认仍在改变延迟后下一帧立即读取新位置。
- 亚帧估计：`audio_delay_estimator_estimate_subframe` 共用整数搜索，在内部最佳峰值两侧对 |S| 做抛物线插值，偏移限制 ±0.5 帧，输出整数峰值的带符号 S。边界、非凹或非有限/非局部顶点回退整数；未准备好或静音时输出不变。sinc 测试的误差容差为 0.25 帧，不是所有信号的精度保证。
- 分数延迟线：`audio_delay_line_set_subframe_delay` 接受有限且不超过最大值的 D；默认线性模式下 D=d+f 时输出 `(1−f)x[n−d] + f x[n−d−1]`。旧 `set_delay` 等价于整数调用，旧 `delay` 返回整数部分；`subframe_delay` 返回完整值，NULL 为 0。整数输出不变，支持原地与分块。
- 高质量延迟：`audio_delay_line_set_sinc` 切换 16 tap Blackman 加窗 sinc 模式，`audio_delay_line_sinc` 查询模式，`audio_delay_line_sinc_extra_delay` 报告额外延迟。该模式为实时因果性增加固定 8 帧，实际延迟为 D+8，配置访问器仍报告 D；f=0 直接精确读取，f>0 使用归一化核。核过冲在取整后饱和到 i16 范围，线性路径不做额外处理。48 kHz 的 8 kHz 测试音在收敛后保留至少 95% 幅度，DC 保持单位增益。
- 连续变化：`audio_delay_line_set_crossfade_frames` 配置 0..48000 帧，0 保持立即切换。非零时新旧目标共用当前历史，按 1/N..1 逐帧线性淡化；活跃期间 retarget、模式和时长修改均返回 `AUDIO_REJECTED` 且状态不变。线性/ sinc 均支持原地与任意分块，sinc 在混合后取整并饱和。
- 自动跟踪：`engine/src/audio/audio_delay_tracker.{h,c}` 内部持有所选估计器。`AudioDelayTrackerConfig` 增加采样率、最小 |S|、最大双向漂移帧/秒、锁定所需连续接受数与拒绝保持数。默认 `audio_delay_tracker_create` 使用时域估计器，`audio_delay_tracker_create_gcc` 使用 GCC-PHAT 与归一化置信度，配置结构不变且只分配选定后端。锁定前直接采用测量；锁定后按两次 update 之间推送的帧数计算经过时间并限制变化，零时间不动。拒绝保持延迟；超过保持数才解锁，恢复良好测量会清空拒绝游程。`reset` 同时重置所选估计器与跟踪状态。
- 频域估计：`engine/src/audio/audio_gcc_phat.{h,c}` 提供独立的 GCC-PHAT 对象。FFT 大小为至少两倍 `window + max_delay` 的下一个 2 的幂，最大 65536；计算 `conj(FFT(reference))·FFT(capture)`，逐 bin 归一化相位后逆变换，在 0..max_delay 取最大绝对峰，返回其带符号 raw peak。内部峰可做 ±0.5 抛物线细化；边界和无效曲线回退整数。只有 create 分配，raw peak 不是归一化相关系数。
- 归一化置信度：`audio_gcc_phat_estimate_with_confidence` 返回相同的细化延迟，并在选中的整数 lag 上直接计算 `cr/sqrt(cc*rr)`，与 tracker 的相关性门控同义。该分数描述整数对齐，反相为负；所选参考窗口零能量时返回 false 且两个输出不变。旧 raw-peak 接口与行为不变。
- 用法：把参考与采集推入估计器、tracker 或 GCC-PHAT 对象，得到延迟 D 后把参考延迟线设为 D 减去几帧余量（滤波器从因果的前几个 tap 开始），延迟后的参考与采集送入 `audio_echo_canceller_process_i16`。启用 sinc 时还需减去其 8 帧额外延迟。tracker 由调用者主动 update，没有隐藏后台线程；GCC 后端在创建时选择，不能运行中切换。
- 未做：自动更新调度与多声道；时钟漂移补偿见后续小节。

## 时钟漂移估计

`engine/src/audio/audio_drift_estimator.{h,c}` 把置信度门控的分数延迟测量转换为相对时钟漂移 ppm。它不使用墙钟、不直接处理音频，补偿器是独立组件。

- `AudioDriftEstimatorConfig`：2..1024 个样本的滑窗、最小 |correlation| 0..1、最大 |drift| 1..10000 ppm。非法或 NaN 返回 `AUDIO_INVALID`，内存不足返回 `AUDIO_OVERLOAD`，只有成功才写 `*out`。
- `push(frame_index, delay_frames, correlation)` 只接受有限值、达到门限的相关性和严格递增帧号；拒绝不改窗口。只有 create 分配，reset 清空所有样本与最后帧状态。
- `estimate(drift_ppm, mean_correlation)` 以最旧环帧为相对基准，做居中最小二乘回归，`ppm = delay/frame 斜率 × 1e6`，并返回接受样本的平均带符号相关性。少于两个样本、零时间方差、非有限或超限时返回 false，输出不变。
- `estimate_robust` 使用 Siegel repeated-median：逐样本斜率中位数再取总中位数，抵抗孤立离群点；两个 window 长度 scratch 在 create 分配，堆排序不分配。帧差保留大公共基准和符号，非有限斜率/结果及超限均原子失败。平均带符号相关性与旧接口相同，旧最小二乘结果不变。最大窗口 1024 已验证。
- 未做：自动更新调度/闭环控制与真实设备验证；tracker 可在创建时显式选择 GCC 后端，重采样补偿见下一节。

## 时钟漂移补偿

`engine/src/audio/audio_drift_resampler.{h,c}` 是调用者持有状态的单声道重采样器，与估计器配合完成漂移补偿。默认线性插值，可选 sinc 质量模式；所有状态内嵌，无分配。

- 比率是每输出帧消耗的输入帧数，有限且在 0.1..10：1 为直通，2 为抽取，0.5 为上采样。可调用 `set_ratio` 改变后续步进；`ratio(NULL)` 为 0。比率符号由调用者按管线决定。
- 默认模式以绝对输入下标和下一个输出位置插值；当前位置恰好等于当前输入时取当前样本，否则在上一帧与当前帧之间插值。reset 保留当前比率和质量模式并清空位置/历史。
- sinc 模式由 `audio_drift_resampler_set_sinc` 切换，使用 16 tap Blackman 加窗核、完整权重归一化和取整后 i16 饱和。每个输出等待 8 个输入帧前瞻，整数位置也保持固定延迟；`audio_drift_resampler_sinc_extra_delay` 报告该值。有限流尾部需补零取完所需位置，零输入仍为空操作。
- 两种模式都写入 32 项历史。sinc 切回线性后从真实历史补齐积压的分数位置，不重复最新样本；线性状态有积压时 `output_capacity` 增加 `ceil(pending/ratio)`，无积压的旧容量公式不变。
- `output_capacity` 给出新输入块的安全上限，零输入、NULL 或溢出返回 0。`process_i16` 在改状态前验证参数和容量，消费全部输入并返回实际输出数；输入与输出缓冲不得重叠。
- 已验证恒等、抽取、半位置上采样、任意分块、动态比率、双向模式切换、容量失败原子性、满幅过冲及真实 50 ppm 估计驱动。固定 sinc 核改善分数插值，但不是强降采样的比例自适应抗混叠器；未做多声道、自动闭环控制和真实设备验证。

## 离线音频编辑

`engine/src/audio/audio_edit.{h,c}` 提供单/双声道交错 i16 缓冲的原地编辑，不分配、不做文件 I/O，也不依赖编辑器状态。

- `trim` 保留 [begin,end) 并移到开头，`cut` 删除该区间并合拢；二者返回新帧数，只有成功才写输出。零长度合法，非法范围、声道或指针返回 `AUDIO_INVALID`。
- `fade` 按毫秒配置两端线性增益；采样率 8000..192000。多帧斜坡外端为 0、内端为 1，两端重叠时取较小增益，零时长不改变样本。帧数在 double 中舍入后再转 u32，不经过 long。
- `normalize` 以 -120..0 dBFS 的目标峰值缩放，数字静音不变；负峰值按绝对值处理，转换有舍入和限幅。
- `mix` 用 [-8,8] 的有限线性增益把源加到公共前缀，结果限幅，目标尾部不变；源与目标缓冲不得重叠。
- 所有缓冲区在访问前经 `audio_edit_buffer_span` 检查样本数与字节数；交错索引、指针偏移和字节计数使用 usize，避免大帧数与 32 位平台溢出。
- 编辑器文档集成：`editor/editor_audio` 为 `BreakEditorDoc` 提供可选短 PCM 附件，trim/cut/fade/normalize/mix 通过 before/after 快照进入现有 undo/redo、origin 冲突和 drop-oldest 历史。附件在 reset、成功场景 load 和 destroy 时释放；编辑失败与 OOM 均保持 PCM/历史不变。首版最多 65536 帧。
- WAV 导入：`audio_wav` 无分配解析 RIFF，校验完整大小、chunk/pad、PCM 格式/采样率/对齐和容量后显式小端解码；`break_editor_doc_audio_attach_wav` 用不超过 1 MiB 的文件临时区与有界 PCM 临时区导入，失败不改文档/历史。`test_audio_wav` 与手工 `fuzz_audio_wav` 覆盖有效种子和结构变异。
- 未做：编辑器 UI、时间线、其他媒体格式与导出、自动化和真实听测；文档级撤销及 PCM WAV 导入已覆盖。

## 集成语音处理链

`engine/src/audio/audio_voice_processor.{h,c}` 把现有模块组合为单声道、所有者线程的处理链：逐帧 AEC+近端残余抑制 → Hann/STFT 频谱降噪 → 噪声门 → AGC。它只负责已对齐参考与采集 PCM 的处理，不打开设备、不对齐延迟、不编码或联网。

- `AudioVoiceProcessorConfig` 嵌套五个现有配置；采样率必须一致，噪声门与 AGC 必须为单声道，各模块原有范围不变。创建失败不写 `*out`，部分构造会逆序释放。
- `process_i16` 原地处理，任意分块与手工五级链逐位一致。非法调用为空操作；只有 create 分配。reset 重置 AEC/残余/频谱状态，并用保存的配置重新初始化噪声门和 AGC。
- `audio_voice_processor_latency_frames` 返回频谱降噪的固定 frame_size；有限流尾部需为参考与采集都补该数量的零帧。测试用手工五级链独立校验正文和排空尾部。
- 未做：多声道、可配置 bypass、core_app 设备/网络接线、自动延迟跟踪与真实声学验证。

## 播放参考捕获

`audio.h` 的 `audio_reference_*` 接口通过 miniaudio `ma_engine_config.onProcess` 取得最终立体声混音，在真实设备回调与 FAKE 的 `audio_system_render` 中共用同一采集点。每帧按 `0.5 * (left + right)` 下混，非有限值记为零，限幅后以 `lrintf(x * 32767)` 转成 i16；播放输出本身不被修改。

- 固定为 48 kHz 单声道，环容量 `AUDIO_REFERENCE_RING_FRAMES` 为 16384。状态嵌入 `AudioImpl` 的唯一分配，回调不分配、不加锁、不写日志。
- 默认关闭；`start`/`stop` 幂等且保留未读帧，停止后仍可 `read_i16` 排空。`reset` 只在停止状态接受，清空未读帧和 overrun 计数。
- 环为单生产者单消费者，自由增长 head/tail 用 release/acquire 发布；满环丢弃最新帧并按帧计数。有效 stop 推进代际并等待在途回调的活动计数归零；回调登记后复核启用和代际，阻止 stop/reset/start 之间的旧帧写入。控制路径可让出 CPU，回调不等待控制路径。
- `test_audio` 新增 5 项（24→29）：生命周期/参数、真实立体声 PCM 流下混逐样本一致、非静音溢出身份与环索引环绕、并发渲染/读取，以及旧回调跨 restart 的确定性代际回归。普通、ASan+UBSan、TSan 均 29/29；release→relaxed 变异由 TSan 的实际环槽竞争报告捕获。
- 这是 AEC 的参考来源，不是已经接线的语音管线；不做采集、延迟对齐、漂移补偿、编码、网络发送或真实声学验收。

## 语音参考自动对齐

`engine/src/audio/audio_voice_aligner.{h,c}` 将延迟 tracker 与延迟线组合为单声道、所有者线程的 `AudioVoiceAligner`：`create` 选择时域估计，`create_gcc` 显式选择 GCC-PHAT，`uses_gcc` 可核验实际后端。它消费原始播放参考和采集 PCM，输出用于后续 AEC 的对齐参考，不修改采集。

- `update_period_frames` 为 1..192000；处理按精确周期边界切块，与调用者分块无关。每块先把原始参考/采集推入 tracker，并让原始参考经过延迟线；边界到达后更新一次，接受的分数延迟从下一帧生效。拒绝或历史不足保持旧延迟。
- `updates` 统计实际调度次数（含拒绝），`rejections`、`locked` 转发 tracker 状态，`delay` 返回延迟线实际应用值。创建失败不改变 `*out`，只有 create 分配；零帧合法，非零 NULL 信号及 capture/output 别名在改状态前拒绝。reference/output 可原地复用。
- `test_audio_voice_aligner` 6 项覆盖参数/调用契约、12.5 帧已知回声的精确更新边界、整块与 1/7/31/128 任意分块逐位一致、静音采集拒绝、GCC 构造及延迟设置失败后的周期恢复。普通、ASan+UBSan、TSan 均 6/6；原始路由、倒计时、延迟应用/提前应用、后端选择、别名、三个 NULL 检查与失败恢复十个变异均判红（删除倒计时恢复表现为超时）。
- 未做：reset（底层 delay line 尚无 reset）、sinc/交叉淡化配置、时钟漂移补偿、多声道、设备/VoiceProcessor/core_app/网络接线与真实声学验证。

## Core App 语音 PCM 泵

`engine/apps/core_app/core_app_voice.{h,c}` 在正式 `core_app_runtime` 中组合采集、播放参考、自动对齐与 `AudioVoiceProcessor`。固定 48 kHz 单声道、每包 480 帧；手动 `pump` 与专用 worker 共用同一处理路径，输出通过 16 项 SPSC 队列交付 `BreakVoiceFrame`，不在语音线程编码或联网。

- 创建拥有 4096 帧采集环、aligner 和 processor，播放系统仅借用 reference API。start 先启用参考再启动采集，失败回滚；stop 先 join worker 再停采集/参考，队列可在停止后排空。FAKE 输入由 `inject` 走真实采集路径。
- 两路输入都积累到 480 帧才处理；依次执行 aligner 与 processor，再发布序号、采样率/声道和 PCM。满队丢最新包且序号继续前进；`stats` 原子报告 produced/dropped 和两环 overrun。worker 发布 id/ready 后才允许启动返回，外部 pump 在 worker 活跃时被拒绝。
- `test_core_app_voice` 5 项覆盖生命周期/格式、独立 aligner+processor 逐样本对照、17 包容量与丢弃后序号、分别缺输入、真实 worker 接收/停止。普通、ASan+UBSan、TSan 均 5/5；九个行为/并发变异均被捕获。
- 未做：core_app CLI/协调器/网络 hook 接线、编码发送、设备丢失自动恢复、尾部排空、漂移补偿和真实声学验证。
- 2026-11-18 补充：CLI 与协调器接线已完成，见 [`core_app_integration.md`](core_app_integration.md)「Core App 语音通道」（`--voice off|fake|device`、`voice` 子系统在 join 阶段销毁、Null 采集后端视为无麦克风、运行中 worker 出错以 `stage=voice` 失败）。组件侧同时把采集设备无法打开或启动（`AUDIO_FAILED`）映射为 `BREAK_RUNTIME_UNAVAILABLE`，并新增 `core_app_voice_worker_error`、`core_app_voice_capture_backend`、`core_app_voice_capture_name`、`core_app_voice_simulate_capture_event`；`audio_capture_backend_name` 返回 `none`/`fake` 或 miniaudio 后端名。`test_core_app_voice` 现为 7 项，`test_audio_capture` 为 12 项。仍缺：编码发送、设备丢失自动恢复、尾部排空、漂移补偿和真实声学验证。
- 2026-11-18 补充：编码发送已完成，见 [`core_app_integration.md`](core_app_integration.md)「语音帧经网络发送」。CoreAppThread 弹出帧后经可选 hook `voice_frame` 交给传输层，由传输层编码为 BRV2 并作为消息 `0x4006` 发往每个已认证对端；语音组件和运行时库本身仍不编码、不联网、不链接编解码器。
- 2026-11-18 补充：服务端接收对端语音已完成，见 [`core_app_integration.md`](core_app_integration.md)「服务端接收对端语音」。传输层按连接用 `BreakVoiceReceiver` 做抖动缓冲，按单调时钟播放并在连接关闭时尾部排空，只更新计数与峰值；对端语音不进入本地播放或语音通道。仍缺：混音与播放、漂移补偿、设备丢失自动恢复和真实声学验证。
- 2026-11-18 补充：采集设备丢失后自动恢复已完成，见 [`core_app_integration.md`](core_app_integration.md)「语音采集设备自动恢复」。`CoreAppVoiceConfig` 新增 `reopen_interval_ms`、`max_reopen_failures`（为 0 时保持原行为：丢失即 UNAVAILABLE）；`core_app_voice_pump` 在采集丢失时按间隔调用 `audio_capture_reopen(capture, NULL)`，成功后丢弃无对应采集的播放参考积压并重置 voice processor，连续失败达到上限才返回 UNAVAILABLE。`CoreAppVoiceStats` 追加 `capture_recoveries`、`capture_reopen_failures`。`audio_capture_simulate_event` 新增 `AUDIO_CAPTURE_EVENT_REOPEN_REFUSED`（仅 FAKE/NULL，每个事件让一次 reopen 返回 FAILED 且不改变状态）。仍缺：按名称切换到其他设备、播放参考设备恢复、漂移补偿和真实声学验证。
- 2026-11-18 补充：播放设备丢失后自动恢复已完成，见 [`core_app_integration.md`](core_app_integration.md)「播放设备自动恢复」。`AudioSystem` 新增 `audio_system_lost`、`audio_system_reopen`（在原内存中重开默认输出，保留 node graph、声源与参考环）和仅测试用的 `audio_system_simulate_event`；所有设备后端的 context 改由系统持有。丢失按设备状态判定（非 started 超过 250 ms），`audio_system_recoveries` 计数真正替换设备的重开，语音 pump 据此丢弃无参考的采集并重置 processor。core_app device 模式由 owner 线程按 100 ms × 50 次重开。仍缺：按名称切换设备、漂移补偿和真实声学验证。

## FFT

`engine/src/audio/audio_fft.{h,c}` 提供基 2 实数 FFT 与周期 Hann 窗，作为频谱降噪等频域处理的数值基础。`AudioFft` 计划保存位反转和旋转因子表；只有 `audio_fft_create` 分配内存，正逆变换与窗函数不分配、不加锁。计划创建后只读，可由多个线程共享，但每个调用者必须有自己的样本与频谱缓冲区。

- `audio_fft_create` 接受 4..65536 内的 2 的幂；非法大小或 NULL 输出地址返回 `AUDIO_INVALID`，内存不足返回 `AUDIO_OVERLOAD`，失败时不写 `*out`。`audio_fft_destroy(NULL)` 是空操作，`audio_fft_size(NULL)` 返回 0。
- `audio_fft_forward` 把 `size` 个实数样本变为 `size/2+1` 个非冗余频谱 bin，不修改输入；DC 与 Nyquist 的虚部固定为 0。实现把偶数与奇数样本打包成一次 `size/2` 点复数 FFT，再分离实数频谱。输入 `x`、实部 `re`、虚部 `im` 三个缓冲区不得重叠。
- `audio_fft_inverse` 根据共轭对称关系恢复 `size` 个实数样本，包含完整的 `1/size` 归一化；DC 与 Nyquist 的虚部被忽略，`re`、`im` 用作临时存储，返回后内容不保证。`re`、`im` 与输出 `x` 三个缓冲区不得重叠。
- `audio_fft_hann` 生成 `w[t] = 0.5 − 0.5 cos(2πt/size)`；大小必须是非 0 偶数。以 `size/2` 为 hop 时，相邻窗逐样本相加为 1，可直接用于 50% 重叠的 STFT/重叠相加。
- 全部计算使用 f64。测试对 4..1024 的每个尺寸做全 bin 直接 DFT 对照，对 2048..65536 做 DC、Nyquist、n/4 自配对区域及其他代表 bin 的直接 DFT 对照；另有手工构造频谱的独立逆变换参考，并在 65536 点验证能量守恒。
- 未做：f32 接口、SIMD、非 2 的幂尺寸、多声道批量变换。本模块本身不是降噪器；频谱降噪见下节。

## 频谱降噪

`engine/src/audio/audio_noise_suppressor.{h,c}` 在所有者线程上对单声道 i16 采集信号做频谱降噪，可替代时域噪声门；若两者串联，应先做频谱降噪。只有 create 分配内存，process 不分配、不加锁。建议链路为 `audio_capture_read_i16` → 回声消除 → 频谱降噪 → AGC → `break_voice_encode*`。

- `AudioNoiseSuppressorConfig`：采样率 8000..192000、FFT 大小 16..1024 内的 2 的幂、最大衰减 0..80 dB、底噪上升速度 0.1..60 dB/s、初始底噪 -120..0 dBFS。参数非法或 NaN 返回 `AUDIO_INVALID`，内存不足返回 `AUDIO_OVERLOAD`，只有成功时才写 `*out`。
- 处理链：周期 Hann 分析窗 → 实数 FFT → 每 bin 增益 → 逆 FFT → 不加合成窗的 50% 重叠相加。Hann 的相邻窗之和为 1，因此单位增益可精确重建。预填半窗零并丢弃第一块的负时间输出，避免开头半窗被误淡出。
- 原始 bin 功率 `P = (re² + im²) / Σw²`，下限为 `1e-12`。每个 bin 用 100 ms 指数平均得到平滑目标 S；底噪最多按配置速度上升且不超过 S，S 下降时底噪立即跟随。底噪与平滑目标分开保存，避免把随机噪声的每个瞬时低谷误认为长期底噪。
- 幅度增益为 `max(10^(−最大衰减/20), 1 − 2·noise/P)`。固定 2 倍谱减用于达到实际噪声抑制量；最大衰减为 0 dB 时下限为 1，增益恒为 1，输出逐样本等于延迟后的输入。最大衰减限制作用于每个 bin；聚合 RMS 还受相邻块相位与量化影响，测试给 6 dB 配置保留 2 dB 容差。
- 固定延迟为 `frame_size` 帧，`audio_noise_suppressor_latency_frames` 返回该值（NULL 为 0）。内部 N 项输出环与半窗 hop 使任意分块和整块处理逐位一致；流结束时再送 N 帧静音即可取完已有输入。
- `audio_noise_suppressor_reset` 恢复初始底噪、平滑功率、输入历史、overlap、输出延迟与块相位；NULL 是空操作。
- 单音保持只保证启动与底噪跟踪瞬态。持续单音或其他稳态声音最终会像现有噪声门一样被学习为噪声并衰减，不能把该模块当作持续音高保真器。
- 输出取整使用 `nearbyint`，精确重建约定假定调用者保持默认的就近舍入模式。
- 未做：多声道、学习型降噪、自动补偿语音传输的端到端延迟、真实麦克风与听感验证。

## 验证与限制

- `test_audio_extended`：clip/容量、并发/重触发、stale handle、真实 DSP 接线、逐样本交叉淡化、loop/停止、遮挡/距离、bus/master、legacy WAV、bit-exact fake 和 null 命令生命周期。
- `test_audio_dsp`：手算滤波阶跃、延迟 tap/feedback、混响早期 taps、filter+delay 组合和失败原子。
- normal、ASan+UBSan、TSan 的 `test_audio`/`test_audio_extended`/`test_audio_dsp`/`test_audio_realtime_contract` 均通过。
- 降采样低通由 `test_audio_extended` 中的双精度参考模型（96 kHz、88.2 kHz）、Nyquist 音、30 kHz / 1 kHz 正弦、立体声分离和重开复位覆盖；`test_voice_playback` 在 96 kHz 下跑生产者/关闭/混音线程竞争。
- `test_audio_hrtf`（9 项）覆盖以下内容：
  - `set_index` 的范围检查、首帧立即生效与之后的交叉淡化；
  - 渲染器与双精度直接卷积对比，包括不等长的分块调用；
  - 交叉淡化与淡化中的修改；
  - 首次方向与重复方向；
  - 最近方向：±180 回绕、正上方、相同时的下标规则；
  - create 与 parse 的每种拒绝情况、`BHRT` 往返、每个截断长度和字段损坏；
  - 2048 个方向的上限；
  - 球头模型：对称性与镜像、Woodworth 双耳时差（误差 1 帧以内）、远耳的高低频能量比、各方向直流和一致、Nyquist 增益等于 α 之比、仰角差异。

  45 项变异中有 44 项被测试捕获。存活的“正后方复制”是等价变异：sin(π) 的舍入误差不足以改变 lrint 和滤波结果。
- `test_audio_extended` 的 PCM 流 HRTF 测试（4 项）：参数（REJECTED、采样率、句柄、STALE、重开后无集合，关闭后可销毁集合）；单声道右方声源等于该方向脉冲响应的直接卷积乘距离增益，同时打开的声像、后方、耳间时差、高度提示不起作用；立体声取平均、旋转后的监听者坐标系、上方、重合、退化坐标系、未归一化的 forward/up；移动声源与参考渲染器逐位一致，摘掉后恢复普通输出，重新挂上从空历史开始。20 项变异全部被捕获。
- `test_audio_extended` 的事件 HRTF 测试（5 项）：注册要求 spatial 与引擎采样率；单声道右方事件等于直接卷积乘距离增益，同时打开的其他提示不起作用；立体声 clip 取平均，`audio_voice_set_position` 与监听者转身更新下标；移动声源与参考渲染器逐位一致；RESTART 重触发从空历史开始。11 项变异全部被捕获。
- sinc 重采样由双精度 Lanczos 参考模型（16 kHz、88.2 kHz 经低通、24 kHz 立体声）、前瞻等待、高频正弦误差、引擎采样率不变、模式切换的历史和重开复位覆盖。
- 后方提示由阶跃响应参考模型（PCM 流正后方与 45°、事件正后方）、前方/侧面/重合逐位不变、监听者转身、RESTART 与 revision 门控、立体声状态分离和重开复位覆盖。
- `test_audio_residual_echo_suppressor`（7 项）：全部配置边界、所有浮点字段 NaN、NULL、访问器与配置失败原子性；无参考直通与连续 hangover 尾部；真实 NLMS 加 `0.25*x + 0.12*x*|x|` 非线性回声后残余衰减超过 10 dB，且测量拒绝非有限值；先关闭再经近端标志重新打开增益，近端单音 1 dB 内且路径冻结；attack/release 方向；单帧与 1000 帧路径上升速率、下降与 0 dB 上限；1/7/255/13 分块、reset 与新初始化状态一致、静音与动态状态清零。40/40 定向变异被捕获；ASan+UBSan、严格告警通过。
- `test_audio_noise_suppressor`（8 项）：配置范围、NaN、NULL、配置失败原子性与延迟访问；16/64/256/1024 点、含 ±满幅输入的 0 dB 精确延迟重建；稳态白噪声衰减约 11.0 dB 及 6 dB 每 bin 限值（聚合 RMS 容差 2 dB）；启动/跟踪瞬态单音和初始底噪上的安静单音幅度在 1 dB 内；持续单音在 60 dB/s 测试最后 0.25 秒衰减超过 10 dB；1/7/255/13 帧分块逐位一致；强噪声训练后 reset 与新对象处理安静单音逐位一致；静音保持为零。37 项变异捕获 32 项，5 个存活项及非等价情形见 `docs/Implementation_Status.md`；ASan+UBSan、严格告警检查通过。
- `test_audio_fft`（8 项）：尺寸与 NULL 校验、失败时不写 `*out`；延迟脉冲与单音的已知频谱；4..1024 的每个 2 的幂尺寸对直接 DFT 逐 bin 一致且输入不变；2048..65536 的 DC、Nyquist、n/4 自配对区域与代表 bin 对直接 DFT 一致；手工构造频谱经独立逆 DFT 公式核对，包括 4 点手算值与任意内部复数 bin；4、256、4096、65536 点逆变换恢复原信号，Parseval 能量守恒，DC/Nyquist 虚部被忽略；线性与循环移位的相位关系；Hann 窗的对称、边界值、50% 重叠相加为 1 及非法大小。所有数值断言拒绝 NaN。27 项定向变异全部被捕获；ASan+UBSan、`-Wshadow -Wdouble-promotion` 检查通过。
- `test_audio_edit`（6 项）：内部缓冲区跨度与极端值、参数/NULL/零长度及失败时样本不变；全/空/内部立体声 trim/cut；独立淡化端点和双声道同增益；静音、负峰值占优、目标峰值与限幅；单/双声道混合增益、前缀、尾部和舍入。30/32 定向变异被捕获，2 个防御性存活项见 `docs/Implementation_Status.md`；ASan+UBSan、严格告警通过。
- `test_audio_drift_resampler`（6 项）：比率/NULL/容量与溢出、恒等与抽取、半位置上采样和任意分块、运行中 0.5→2.0 手算切换、已有状态的不足容量原子性与 reset 保留比率、真实 50 ppm 估计驱动（16 输入产生 15 输出）。21/26 定向变异被捕获，5 个存活项及原因见 `docs/Implementation_Status.md`；ASan+UBSan、严格告警通过。
- `test_audio_drift_estimator`（5 项）：配置、NULL、初始/复位与失败原子性；非均匀帧的 +50 ppm 和平均相关性；低置信度、非有限、非递增、退化与超限拒绝；四环最新窗口与重用；大 u64 基准的 -40 ppm。全部数值断言拒绝 NaN，门限相等有覆盖。25/26 定向变异被捕获，唯一存活为严格递增输入下不可达的零分母防御。ASan+UBSan、严格告警通过。
- `test_audio_gcc_phat`（6 项）：配置、FFT 上限、准备/静音与极端 u32；内部 FFT 尺寸和精确并列纯函数；精确/反相/长延迟、冲激峰值 1、常量输入与重复确定性；含噪分数延迟 0.25 帧容差；分块、reset 后立即/不足历史失败和直接时域 lag 参考。22/27 定向变异被捕获，5 个存活项及原因见 `docs/Implementation_Status.md`；ASan+UBSan、严格告警通过。
- `test_audio_delay_tracker`（5 项）：配置边界、NULL 与访问器；分数测量锁定；低置信度保持、恢复与解锁；按推送时间的双向漂移和零时间不动；分块、reset 与估计失败。另覆盖反相关、锁前接受游程清零、恢复后拒绝游程清零、零阈值下估计仍失败。34/37 定向变异被捕获，3 项为估计器重复边界；ASan+UBSan、严格告警通过。
- `test_audio_delay_estimator`（11 项）：原有配置、整数延迟、反相、静音/重置、暴力模型、并列、延迟线与 AEC 对齐保持不变；新增 3.25/12.5/31.75 帧 sinc 回声的 0.25 帧容差和最近整数距离的 sinc 相关性参考、端点、反相亚帧与失败原子性；2.25 帧延迟线原地分块、非整除舍入、非法值、整数兼容与空历史。16/18 定向变异被捕获，两个存活保护由局部峰值不等式和有限性兜底覆盖。ASan+UBSan 还捕获并修复了测试 sinc 生成器的尾部越界；最终 ASan+UBSan、`-Wshadow -Wdouble-promotion` 检查通过。
- `test_audio_echo_canceller`（8 项）：参数校验与失败时不写 `*out`、上下限可接受、初始权重为 0；-10 dBFS 白噪声经两 tap 回声路径，1 秒后回声衰减（ERLE）超过 40 dB，权重与路径相差 1e-3 以内，越界读权重为 0，阈值为 0 时照常学习；参考静音时采集逐位原样通过（含满幅样本）；双讲时打开检测输出对近端单音的信噪比 31 dB、权重误差 0.027，关闭检测为 12 dB、0.24，检测触发后权重完全冻结；保持时间内不学习、两端静音不触发保持、短保持时间过后照常学习；回声路径改变后重新收敛；reset 后与新建的对象逐位一致；1、7、480 帧分块输出逐位相同，并与独立参考模型（移位历史）在 1 LSB 内一致、权重差 1e-9 以内。34 项变异全部被捕获；ASan+UBSan、`-Wshadow -Wdouble-promotion` 检查通过。
- `test_audio_noise_gate`（8 项）：参数校验与失败时不写状态、上下限可接受；-50 dBFS 稳态噪声使底噪收敛、门关闭、输出降到约 -80 dBFS；高出底噪 30 dB 的单音开门并以原电平通过；长时间稳态单音抬高底噪后关门；更安静的噪声立即拉低底噪；静音输出为零、底噪保持 -120 且有限；恒定输入时底噪上升到电平而不越过；立体声及 1、7、480 帧分块与独立参考模型逐位一致。30 项变异中 27 项被捕获。存活的 3 项中两项是等价变异（静音记为 -inf 会被下一行限制回 -120；初始线性增益在首次使用前就被每帧重算）；`>=` 改 `>` 只在电平恰好等于底噪加阈值时不同，双精度下测试信号无法构造。ASan+UBSan、`-Wshadow -Wdouble-promotion` 检查通过。
- `test_audio_agc`（8 项）：参数校验与失败时不写状态、安静与响亮正弦都稳定到目标（1 dB 内）、最大增益上限、门限下增益保持与输出不变、放大后突发大音量被限幅且不回绕、立体声共享增益、分块不影响输出、与独立参考模型逐样本一致。23 项变异全部被捕获；ASan+UBSan 通过。
- `test_audio_capture` 的热插拔测试（3 项）：FAKE 丢失后运行状态、注入、启动被拒，丢失前的帧在 reopen 后按序读出，FAKE 带名称 reopen 被拒且不清除丢失，丢失后 stop 在 reopen 后保持停止，已停止时的停止事件不算丢失；重路由计数、采集继续运行、非法事件与 NULL 参数；空设备两轮启停与 destroy 不算丢失，运行中 reopen 继续交付帧并报告新设备名，未知名称不影响运行中的设备及其名称，停止状态下 reopen 保持停止，丢失后 start 失败、reopen 恢复运行。23 项变异中 22 项被捕获；存活的是「设备状态已停止」的轮询分支，只有真实设备被拔出且后端不发停止通知时才会走到，本环境无法构造。TSan、ASan+UBSan 通过。
- `test_audio_capture`（8 项）：设备列表（空设备、容量 0、FAKE、非法参数）、按名称打开与默认名称、未知名称与 FAKE 带名称被拒绝、设备名截断（13 项变异全部被捕获）；配置校验与 `*out` 不变、转换（取整、限幅、NaN/Inf）、顺序与部分读取、立体声跨缓冲末尾回绕、缓冲满时保留最旧的帧并计数、启停幂等与注入门控、空设备实时交付静音帧（两轮启停、运行中销毁）、生产者线程与读取者不丢帧且有序。20 项变异全部被捕获；TSan、ASan+UBSan 通过。
- 没有真实听测、真实声卡验证。采集、自动增益、噪声门、频谱降噪和回声消除没有用真实麦克风与扬声器验证。简单 DSP/混响不等于物理声学或听感验收。Windows/macOS 由远程 CI 构建和测试，但不构成真实声卡或听感验收。
- 2026-11-18 补充：`AudioSystem` 支持按名称列出（`audio_system_list_devices`）、打开（`audio_system_create_named`）与运行中切换（`audio_system_switch_device`）播放设备；切换先在持有的 context 上打开新设备，模拟拒绝或打开失败时旧设备照常播放，成功后替换 `engine->pDevice` 并计一次恢复；`audio_system_reopen` 优先打开已选名称，名称消失时退回默认但保留选择。`test_audio` 新增 11 项（含名称长度在 create 与 switch 一致拒绝、切换启动失败后在同一块内存重开旧设备并保留选择、旧设备也启动失败时保持设备块并由 reopen 修复、无 context 的 reopen 不查名称、按选择重开），变异判红。
- 2026-11-19 补充：core_app 网络服务端可转发对端语音（`--voice-relay`，消息 `0x4007`）。只转发 `BreakVoiceReceiver` 接受的帧（以 `accepted` 计数前后差判断），重复、过期、格式不符的帧不转发；帧字节原样转发，不在服务端解码后重编码。客户端按来源会话号各用一个接收器。没有服务端混音。
- 2026-11-19 补充：转发的语音可由接收方按来源屏蔽（`0x4008`，服务端跳过该接收方并计 `voice_frames_muted`）。屏蔽只作用于服务端转发，不影响来源对服务端的发送和服务端自己的接收计数。
- 2026-11-19 补充：core_app 服务端在语音进入抖动缓冲前按连接限速（`BreakMsgRate`，120 帧/秒、突发 64 帧），超限帧计 `voice_frames_rate_limited`，不进入接收器，也不会被转发。
- 2026-11-19 补充：core_app 在运行中通过音频命令队列调用 `audio_system_switch_device`（scenario `audio-device [NAME]`），调用发生在音频 owner 线程上，满足“只能在 owner 线程调用”的约束。
- 2026-11-19 补充：core_app 语音层在运行中通过单槽请求（`core_app_voice_request_capture_device`）调用 `audio_capture_reopen`，调用发生在语音泵线程上，满足“只能在泵线程调用”的约束；未知名称返回 REJECTED，旧设备保持运行。
- 2026-11-19 补充：`BreakVoiceMixer`（`break_online`）把多个来源的 `BreakVoiceReceiver` 输出逐样本相加并饱和到 i16，`clipped_samples` 计饱和样本数；只有所有参与的帧都是补偿帧时输出才标记为 concealed。

## 时钟漂移闭环补偿

`engine/src/audio/audio_drift_compensator.{h,c}` 把估计器和重采样器连成闭环。单声道，只允许 owner 线程调用，只有 create 分配内存（分配发生在估计器内部）。设计见 `docs/superpowers/specs/2026-11-19-audio-drift-compensator-design.md`。

- **模型**：采集中的回声满足 `capture[n] ≈ ref[n - d(n)]`，`d(n) = d0 + s·n`。参考信号按比率 `r` 重采样后，测得的残余斜率为 `s' = 1 - (1 - s)/r`，当 `r = 1 - s` 时为 0。
- **配置**：`AudioDriftCompensatorConfig` 包含估计器配置；`min_samples` 取 2..window_size；`max_correction_ppm` 取 1..`max_abs_drift_ppm`；`gain` 取 (0, 1]；`robust` 为真时改用 repeated-median 估计斜率。非法值或 NaN 返回 `AUDIO_INVALID`，内存不足返回 `AUDIO_OVERLOAD`，只有成功才写 `*out`。
- **observe 与 update**：`observe` 把测量转交估计器。`update` 在样本数达到 `min_samples` 且估计成功时，令 `r = r·(1 - gain·slope)`，把 `|r - 1|` 限制在 `max_correction_ppm` 以内（计 `clamped`），然后清空估计窗口。清空的原因是比率一变，旧测量的残余斜率就失效了。成功时计 `corrections` 并返回 true；否则返回 false，状态不变。
- **reset**：比率回到 1，估计窗口与重采样位置清空，`corrections` 和 `clamped` 两个计数保留。
- **查询与处理**：`correction_ppm` 返回 `(1 - r)·1e6`，即当前比率所补偿的漂移量。`output_capacity` 与 `process_i16` 以线性插值重采样参考信号，约定与 `audio_drift_resampler_process_i16` 相同。
- **测试**：`test_audio_drift_compensator`（6 项）覆盖以下场景：
  - 配置边界与 NULL；
  - +100 ppm 在半增益下 24 轮收敛到 1e-7 以内；
  - -150 ppm 用 robust 一步到位；
  - ±500 ppm 被限幅到 ±300 ppm；
  - 样本不足或低置信度时不更新，修正后窗口清空；
  - 比率为 1 时输出恒等，修正后 10 万输入帧的输出数与 `n/r` 相差不超过 2；
  - reset 后比率回到 1、计数保留。

  定向变异共 6 个，全部判红：比率符号取反、去掉上限、去掉下限、修正后不清窗口、reset 不恢复比率、忽略 `min_samples`。
- **未做**：接入 core_app 语音泵、多声道、sinc 模式、真实设备验证。
- 2026-11-19 补充：闭环漂移补偿组件已交付，接入 core_app 语音泵是下一步。
- 2026-11-19 补充：闭环补偿评审后的修改。新增端到端用例：噪声参考经补偿器重采样，采集信号在漂移时钟上生成，用 `audio_delay_estimator_estimate_subframe` 测量延迟，+100 ppm 与 -150 ppm 在增益 1 和 0.5 下都收敛到 1e-6 以内；比率符号取反的变异单靠这一用例就判红。头文件写明测量约定：采集落后于参考时延迟为正，`frame_index` 按采集帧计数；每次 update 后的第一个测量仍包含旧比率重采样的样本，可以跳过。`clamped` 改为比率生效之后才计数。上文“时钟漂移估计”“时钟漂移补偿”两节“未做”中的闭环控制，组件部分已由「时钟漂移闭环补偿」交付。create 同时分配补偿器结构体和估计器。测试共 8 项。
- 2026-11-19 补充：`audio_voice_aligner_correlation` 返回 tracker 最近一次的带符号相关分数（NULL 返回 0）。core_app 语音泵用它和锁定后的延迟驱动 `AudioDriftCompensator`，见 [`core_app_integration.md`](core_app_integration.md)「语音漂移补偿」。
- 2026-11-19 补充：WAV 导出。设计见 `docs/superpowers/specs/2026-11-19-audio-wav-export-design.md`。
  - **大小计算**：`audio_wav_encoded_size(channels, frames, *out_size)` 返回 `44 + frames × channels × 2` 字节。声道不是 1 或 2、RIFF 大小字段放不下（超过 4 GiB）时返回 INVALID。
  - **编码**：`audio_wav_encode_i16(info, samples, out, capacity, *out_size)` 写规范的 44 字节头（RIFF、16 字节 PCM fmt 块、data 块）和小端样本。校验范围与解码器一致（8000..192000 Hz、1 或 2 声道）；参数无效或容量不足时返回 INVALID，且不写任何字节。
  - **编辑器保存**：`break_editor_doc_audio_save_wav(doc, path)` 先在内存中编码，写到 `<path>.tmp`，再重命名覆盖 `path`；Windows 上与场景保存一样先删除目标。没有附件、路径为空，或分配、写入、重命名任何一步失败，都返回 false 并删除临时文件。文档、历史和脏标记都不改动。
  - **测试**：
    - `test_audio_wav` 共 7 项，新增 3 项：已知单声道头的逐字节比对与立体声字段、单/双声道在 8000/44100/192000 Hz 下 0/16/32 帧经解码器往返一致、所有失败不写输出且大小溢出被拒。
    - `test_editor_audio` 共 7 项，新增 1 项：剪切后保存，再导入新文档时样本一致；空路径、目录不存在、分配失败、目标是目录导致重命名失败，都不留下文件或临时文件；第二次保存整体替换旧文件。
    - 变异 5 个，都判红：RIFF 大小写错、跳过容量检查、跳过溢出检查、直接写目标文件、失败时不删临时文件。
- 2026-11-19 补充：编辑器音频波形页。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-waveform-design.md`。
  - `break_editor_doc_audio_revision(doc)` 在附件、编辑、撤销/重做、分离时变化；`break_editor_doc_audio_waveform(doc, columns, min, max)` 按 `[c·frames/columns, (c+1)·frames/columns)` 取每列所有声道的最小/最大样本，参数无效、无附件或零帧时返回 false 且不写输出。
  - 编辑器底部工具窗“音频”页显示格式和波形；资源浏览器点击 `.wav` 打开附件（已有附件时拒绝）。上文“未做”中的“编辑器 UI”由此部分交付（只读波形）。仍缺：播放、选区编辑、时间线、缩放和真实听测。
- 2026-11-19 补充：编辑器音频预览播放。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-preview-design.md`。音频页的“播放”把附件的副本经引擎 PCM 流写到默认播放设备（`apps/editor/editor_audio_sink.c`），写完并排空后自动停止，编辑附件时停止。上一条中的“播放”由此交付。仍缺：选区编辑、时间线、跳转/循环、缩放和真实听测。
- 2026-11-19 补充：音频页跳转。点击波形跳到对应帧（播放中立即从该处重播，停止时作为下次起点），波形上有播放光标。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-seek-design.md`。上一条中的“跳转”由此交付。仍缺：选区编辑、时间线、循环、缩放和真实听测。
- 2026-11-19 补充：音频页选区。Shift+点击选择范围，“裁剪/剪切”按钮对选区执行可撤销的 trim/cut。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-selection-design.md`。上一条中的“选区编辑”由此交付（裁剪与剪切）。有选区时“播放”只播放选区；“淡入淡出/归一化”按钮作用于选区（无选区时整段），核心为 `break_editor_doc_audio_fade_range`/`normalize_range`。拖动波形可选区，波形上方有时间刻度条，可循环播放当前范围。仍缺：真实听测。
- 2026-11-19 补充：音频页缩放与滚动。核心新增 `break_editor_doc_audio_waveform_range`（按 `[begin, end)` 取每列最小/最大值，整段函数转发到它）。面板保存可见范围，`+`/`-` 以视图中心折半或加倍（下限 16 帧，上限整段），`<`/`>` 移动视图长度的四分之一；波形列、刻度步长、选区色带、播放光标和所有指针映射都按视图计算，附件变化时视图重置为整段。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-zoom-design.md`。上一条中的“缩放”由此交付。仍缺：滚轮与键盘缩放、滚动条控件、播放时自动滚动和真实听测。
- 2026-11-19 补充：音频页滚轮缩放与跟随播放头。波形上滚轮缩放以指针下的帧为锚点（`editor_panel_audio_zoom_at`，按钮以视图中心转发给它），Shift+滚轮平移视图；视图行的“跟随”复选框在播放时按视图长度整段跳转，使播放位置始终在视图内。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-wheel-design.md`。上一条中的“滚轮缩放”和“播放时自动滚动”由此交付。仍缺：键盘缩放快捷键、滚动条控件、逐帧平滑滚动和真实听测。
- 2026-11-19 补充：音频页键盘缩放与滚动。波形可获得键盘焦点，持有焦点时 `+`/`=` 放大、`-` 缩小、左右方向键平移、`Home` 回到整段，命中的键被消费因而不触发 shell 全局快捷键。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-keys-design.md`。上一条中的“键盘缩放快捷键”由此交付。仍缺：滚动条控件、逐帧平滑滚动、可重绑定按键和真实听测。
- 2026-11-19 补充：音频页视图滚动条。波形下方 12 像素的水平 `my_scroll_bar` 映射视图位置与占比，可拖动跳转，覆盖整段时为满宽滑块。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-scrollbar-design.md`。上一条中的“滚动条控件”由此交付。仍缺：逐帧平滑滚动、可重绑定按键、覆盖整段时自动隐藏和真实听测。
- 2026-11-19 补充：音频页幅度缩放。视图行的 "v"/"^" 按钮以 2 倍步进调整只作用于显示的幅度倍数（1~32），安静素材也能看清包络；不改文档、不进撤销，附件变化时重置。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-gain-design.md`。仍缺：dB/对数刻度、按峰值自动增益和真实听测。
- 2026-11-19 补充：分声道波形。核心新增 `break_editor_doc_audio_waveform_channel`（只统计单声道），音频页按声道分泳道绘制，立体声上下各半、各有中线，单声道不变。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-channels-design.md`。上一条中的“分声道显示”由此交付。仍缺：分声道静音/独奏、各泳道独立幅度缩放、dB/对数刻度和真实听测。
- 2026-11-19 补充：幅度自适应。视图行的 "=" 按钮按当前视图的峰值选出合适的显示倍数（`break_editor_shell_audio_fit_gain`），静音视图不变。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-autogain-design.md`。上一条中的“按峰值自动增益”由此交付。
- 2026-11-19 补充：分声道独奏。预览新增独奏声道（`break_editor_audio_preview_set_solo`），下一次播放把该声道写进所有输出声道；音频页 `editor-audio-solo` 按钮循环切换。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-solo-design.md`。上文的“分声道静音/独奏”中的独奏由此交付。
- 2026-11-19 补充：分声道静音。预览新增静音声道（`break_editor_audio_preview_set_mute`），下一次播放把该声道清零、其余保留；独奏生效时不应用静音。音频页 `editor-audio-mute` 按钮循环切换。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-mute-design.md`。“分声道静音/独奏”至此齐备。
- 2026-11-19 补充：电平读数。核心新增 `break_editor_doc_audio_peak_range`（范围内峰值与 RMS），音频页 `editor-audio-levels` 标签显示当前视图的 peak/rms dBFS（静音按 -120 dB 地板）。设计见 `docs/superpowers/specs/2026-11-19-editor-audio-db-design.md`。上文“dB/对数刻度”中的 dB 读数由此交付。
- 2026-11-20 补充：波形 dB 网格。每条泳道中线上下对称画 -6/-12/-18/-24 dBFS 网格线（不足 4 像素间距或超出泳道的跳过），随幅度缩放移动；`break_editor_shell_audio_grid*` 暴露上一次绘制的网格供验证。设计见 `docs/superpowers/specs/2026-11-20-editor-audio-db-grid-design.md`。“波形上的 dB 网格”由此交付。
- 2026-11-20 补充：网格线标注。每条网格线左端上方标出级别（泳道留不出文字高度时跳过标注但仍画线，镜像的下半边不标注）。设计见 `docs/superpowers/specs/2026-11-20-editor-audio-grid-labels-design.md`。“线上标注”由此交付。
- 2026-11-20 补充：各泳道独立幅度缩放。显示倍数按泳道保存，`break_editor_shell_audio_set_lane_gain`/`_lane_gain`/`_fit_lane_gain` 操作单条泳道，`fit_gain` 每条泳道各按自身峰值适配；网格模型随之记录泳道号。设计见 `docs/superpowers/specs/2026-11-20-editor-audio-lane-gain-design.md`。“各泳道独立幅度缩放”由此交付。
- 2026-11-20 补充：真峰值。核心新增 `break_editor_doc_audio_true_peak_range`（4 倍过采样重建后取绝对值最大者，多相窗 sinc FIR），电平标签追加 dBTP 读数。设计见 `docs/superpowers/specs/2026-11-20-editor-audio-true-peak-design.md`。“真峰值”由此交付（非 BS.1770 系数）。
- 2026-11-20 补充：整体响度。核心新增 `break_editor_doc_audio_loudness_range`（K 加权 + 400 ms 块 75% 重叠 + 绝对/相对双门，系数按素材采样率推导），电平标签追加 LUFS 读数。设计见 `docs/superpowers/specs/2026-11-20-editor-audio-lufs-design.md`。“LUFS”由此交付。
- 2026-11-20 补充：短期响度与响度范围。核心新增 `break_editor_doc_audio_short_term_range`（末尾 3 秒）与 `break_editor_doc_audio_loudness_range_lra`（3 秒窗 1 秒步进 + 双门 + 第 95/第 10 百分位之差），分块与 K 加权提取为共用的 `audio_window_loudness`；电平标签追加 LRA 读数。设计见 `docs/superpowers/specs/2026-11-20-editor-audio-lra-design.md`。“短期/瞬时响度与 LRA”由此交付。
- 2026-11-20 补充：归一化到响度目标。核心新增 `break_editor_doc_audio_normalize_loudness`（测整体响度后施加恒定增益，按峰值余量封顶以免削波，一条可撤销快照），音频页 `editor-audio-lufs-norm` 按钮一键到 -23 LUFS。设计见 `docs/superpowers/specs/2026-11-20-editor-audio-lufs-normalize-design.md`。“归一化到 LUFS 的编辑”由此交付。
- 2026-11-20 补充：响度曲线。核心新增 `break_editor_doc_audio_loudness_curve`（范围上均匀取短期响度），音频页在泳道 0 上画出折线并随视图更新，静音段落留空。设计见 `docs/superpowers/specs/2026-11-20-editor-audio-loudness-curve-design.md`。“响度曲线”由此交付。仍缺：真峰值限幅器、真实听测。
