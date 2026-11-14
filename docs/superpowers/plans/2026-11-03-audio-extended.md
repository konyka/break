# P10 Audio Extended Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [x]`) syntax for tracking.

**Goal:** 在现有 miniaudio `AudioSystem` 内交付命名声音事件、固定容量并发/重触发策略、音乐播放列表与交叉淡化、可组合滤波/延迟/混响、射线遮挡和距离衰减，并用真实 null/fake 后端验证生命周期和确定性 PCM。

**Architecture:** `audio.c` 继续独占 miniaudio implementation 和设备生命周期；新增 `audio_extended.c` 只向同一个 `ma_engine` 注册预建 custom data sources。32 个 voice 在创建期全部初始化，0/1 预留给音乐，2..31 给事件；事件、音乐和空间更新只写固定 SPSC 命令环或原子 POD 快照，回调仅读取预拷贝 f32 PCM、命令和 DSP 状态。`audio_dsp.c` 提供同一条无分配处理链；fake 使用 `ma_engine_config.noDevice` + `ma_engine_read_pcm_frames`，不是另一套混音器。

**Tech Stack:** C11、现有 miniaudio、CTest、`test_framework.h`、CMake、GCC/Clang、ASan+UBSan、TSan。

## Global Constraints

- 遵循 `docs/superpowers/specs/2026-11-02-core-capability-completion-design.md` 第 4、5、6、8 节及 P10；只在 `.worktrees/cry-audio` 的 `cry-wave2-audio` 本地提交，不改 master、不 push。
- 每个行为先看到断言级 RED，再写生产实现；编译/链接缺失只作辅助 RED。每项至少做一项关键行为变异并恢复后复验，实际结果追加到 `.superpowers/sdd/audio-extended-report.md`。
- 热路径不分配内存，不在 PCM 回调中做文件 I/O、网络、应用逻辑、射线查询或播放列表决策；所有命令、事件、clip、voice、playlist 和 DSP 容量有硬上限，超限返回错误而非截断。
- 所有注册、播放列表替换和双 voice 交叉淡化先完整验证/预留再提交；失败不留下半注册 clip、半启动 voice 或半切换音乐。
- PCM 是创建后不可变的预解码 f32 mono/stereo，采样率必须为 48000；clip 注册时复制到系统拥有的固定存储。真实听感、Windows/macOS 和其他采样率重采样不在未验证证据中。
- 复用现有 `ma_engine`，不创建设备级平行混音系统；既有 `test_audio`、流式 API 和总线行为必须继续通过。
- 每任务本地提交；最终运行 normal、ASan+UBSan、TSan focused/现有音频回归、`git diff --check`，更新对应设计、`docs/Implementation_Status.md` 和完整报告。

## File Structure

- `engine/src/audio/audio.h/.c`：设备后端选择、系统生命周期、listener/总线与扩展现有 `AudioSystem` 的桥接。
- `engine/src/audio/audio_extended.h/.c`：clip/event 注册、voice 命令、音乐、空间增益及 miniaudio custom data source。
- `engine/src/audio/audio_dsp.h/.c`：固定四级 DSP 描述、状态和确定性 f32 处理。
- `engine/src/audio/audio_stream.c`：只在新旧回调边界需要澄清或兼容修复时修改，保留现有公共 API。
- `engine/tests/test_audio.c`：既有回归，继续覆盖旧距离/总线/句柄。
- `engine/tests/test_audio_extended.c`：真实 fake/null miniaudio API、事件、音乐、遮挡和生命周期。
- `engine/tests/test_audio_dsp.c`：确定性 DSP PCM 与组合顺序。
- `engine/tests/test_audio_realtime_contract.cmake`：回调禁用分配、文件/解码和应用入口的源级契约。
- `engine/CMakeLists.txt`：把扩展接入 `engine` 和 focused 测试。
- `docs/design/audio_extended.md`：公共合同、容量、线程、PCM 格式和限制。
- `docs/design/core_style_runtime.md`、`docs/Implementation_Status.md`：只更新已实际交付的 P10 状态。
- `.superpowers/sdd/audio-extended-report.md`：逐项 RED/GREEN、变异、命令、提交与限制。

---

### Task 1: 固定 PCM voice 池、fake/null 后端与 clip 生命周期

**Files:**
- Modify: `engine/src/audio/audio.h`, `engine/src/audio/audio.c`
- Create: `engine/src/audio/audio_extended.h`, `engine/src/audio/audio_extended.c`
- Create: `engine/tests/test_audio_extended.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces:

```c
typedef enum { AUDIO_OK, AUDIO_INVALID, AUDIO_STALE, AUDIO_OVERLOAD,
               AUDIO_REJECTED, AUDIO_FAILED } AudioResult;
typedef enum { AUDIO_BACKEND_DEFAULT, AUDIO_BACKEND_NULL,
               AUDIO_BACKEND_FAKE } AudioBackend;
typedef struct { const f32 *samples; u32 frame_count, channels, sample_rate; }
    AudioPcmDesc;
AudioSystem *audio_system_create_ex(AudioBackend backend);
AudioResult audio_system_render(AudioSystem *as, f32 *stereo_out, u32 frames);
AudioResult audio_clip_register(AudioSystem *as, const char *name,
    const AudioPcmDesc *pcm, AudioClipHandle *out);
```

- [x] **Step 1: 写行为测试并确认 RED**

注册 mono 四帧 `[0.25, 0.5, -0.5, 1.0]`，fake/null 后端验证 create/register/render-silence/destroy；clip 尚未触发时真实 `ma_engine_read_pcm_frames` 必须输出全零。注册重名、空 PCM、错误采样率、超过 clip/PCM 容量均返回错误且 clip 数量、PCM 使用量不变。先提供头文件/空实现使测试可链接，再确认容量或注册行为断言失败。

Run: `cmake -S engine -B build-p10-audio -DENGINE_RHI_BACKEND=opengl && cmake --build build-p10-audio -j6 --target test_audio_extended && ./build-p10-audio/test_audio_extended`
Expected RED: 合法 clip 注册返回失败或容量计数错误，不是仅编译失败。非零 PCM 播放 RED 在 Task 2 的事件 trigger 接口出现后验证。

- [x] **Step 2: 实现创建期资源和真实 miniaudio 数据源**

`audio_system_create()` 委托 `audio_system_create_ex(AUDIO_BACKEND_DEFAULT)`；NULL 强制 `ma_backend_null`，FAKE 设置 `noDevice=MA_TRUE`、stereo/48000。扩展状态一次 `calloc`，内含固定 clip/PCM/voice/command 数组。每 voice 以 `ma_data_source_base` 开头，创建期执行 `ma_data_source_init`、`ma_sound_init_from_data_source(...NO_SPATIALIZATION...)`、`ma_sound_start`；任一失败逆序清理并使整个 create 失败。idle read 写零且报告请求帧数，避免 miniaudio 自动停掉池对象。

```c
static ma_result voice_read(ma_data_source *ds, void *out,
                            ma_uint64 frames, ma_uint64 *read) {
    AudioVoice *v = (AudioVoice *)ds;
    voice_drain_commands(v);
    for (u32 f = 0; f < (u32)frames; ++f) voice_render_frame(v, (f32 *)out + 2*f);
    *read = frames;
    return MA_SUCCESS;
}
```

- [x] **Step 3: GREEN、生命周期回归和变异**

Run: `./build-p10-audio/test_audio_extended && ./build-p10-audio/test_audio`
Expected: 全部通过。临时让 idle read 不写输出或让失败注册提前增加 `clip_count`，分别确认 PCM/失败原子测试变红；恢复再跑。销毁顺序必须为扩展 voice uninit → legacy source uninit → `ma_engine_uninit` → context/free。

- [x] **Step 4: 提交**

```bash
git add engine/src/audio engine/tests/test_audio_extended.c engine/CMakeLists.txt
git commit -m "audio: add fixed PCM voices and headless backends"
```

### Task 2: 命名声音事件、并发/重触发与失败原子

**Files:**
- Modify: `engine/src/audio/audio_extended.h`, `engine/src/audio/audio_extended.c`
- Modify: `engine/tests/test_audio_extended.c`

**Interfaces:**

```c
typedef enum { AUDIO_RETRIGGER_ALLOW, AUDIO_RETRIGGER_RESTART,
               AUDIO_RETRIGGER_IGNORE } AudioRetriggerPolicy;
typedef enum { AUDIO_CONCURRENCY_REJECT,
               AUDIO_CONCURRENCY_STEAL_OLDEST } AudioConcurrencyPolicy;
AudioResult audio_event_register(AudioSystem *as, const char *name,
                                 const AudioEventDesc *desc);
AudioResult audio_event_trigger(AudioSystem *as, const char *name, Vec3 pos,
                                AudioVoiceHandle *out);
AudioResult audio_voice_stop(AudioSystem *as, AudioVoiceHandle voice);
AudioResult audio_event_active_count(AudioSystem *as, const char *name,
                                     u32 *out);
```

`AudioEventDesc` 包含 clip、`max_instances`、两种策略、volume、looping、spatial、距离参数、occluded_gain、bus 和 DSP 描述。handle 为 24-bit generation + 8-bit slot；只有完成 serial 与当前 serial 相同才回收，防止 steal/restart 的旧完成通知释放新 voice。

- [x] **Step 1: 写策略和句柄 RED**

使用 16 帧常量 clip 覆盖：ALLOW 同时输出两个实例；IGNORE 第二次返回 REJECTED 且计数仍为 1；RESTART 渲染 4 帧后重触发，下一帧重新等于首样本；max=1 REJECT 不改旧 cursor/handle；STEAL_OLDEST 使旧 handle 返回 STALE，新 voice 从首样本开始。全局 30 个事件 voice 满返回 OVERLOAD；未知名称、max=0、事件表满均拒绝且注册表不变。

- [x] **Step 2: 确认 RED 后实现固定 SPSC 命令和策略**

每 voice 16 项命令环以 C11 atomic head/tail 和 release/acquire 发布；START 携带完整不可变 clip 指针和配置，STOP/GAIN_RAMP 不带宿主指针。trigger 先找事件、回收完成 voice、计算策略和候选，再检查命令空间；任何失败不写 generation/owner/sequence。成功后才提交 ring 和主线程簿记。重触发/抢占复用已建 `ma_sound`，不运行期创建节点。

- [x] **Step 3: GREEN 与关键变异**

Run: `./build-p10-audio/test_audio_extended`
Expected: 全通过。分别移除 generation 校验、把 STEAL_OLDEST 改成直接返回 OVERLOAD，确认 stale/抢占测试变红；恢复再跑。检查无效 trigger 的 out=0、active count 与 PCM cursor 未变化。

- [x] **Step 4: 提交**

```bash
git add engine/src/audio/audio_extended.* engine/tests/test_audio_extended.c
git commit -m "audio: add named event concurrency policies"
```

### Task 3: 可组合滤波、延迟和混响 DSP

**Files:**
- Create: `engine/src/audio/audio_dsp.h`, `engine/src/audio/audio_dsp.c`
- Modify: `engine/src/audio/audio_extended.h`, `engine/src/audio/audio_extended.c`
- Create: `engine/tests/test_audio_dsp.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
#define AUDIO_DSP_MAX_STAGES 4u
#define AUDIO_DSP_MAX_DELAY_FRAMES 8192u
typedef enum { AUDIO_DSP_FILTER, AUDIO_DSP_DELAY, AUDIO_DSP_REVERB }
    AudioDspType;
AudioResult audio_dsp_chain_init(AudioDspChain *chain,
    const AudioDspChainDesc *desc, f32 *delay_storage, usize sample_capacity);
void audio_dsp_chain_process(AudioDspChain *chain, f32 *interleaved,
                             u32 frames, u32 channels);
```

- [x] **Step 1: 写确定性 PCM RED**

滤波用阶跃输入验证 `y[0]=alpha`、`y[1]=y[0]+alpha*(1-y[0])`；延迟 2 帧、mix=1 的 impulse 在前两帧为 0、第 2 帧为 1，feedback=0.5 时第 4 帧为 0.5；reverb impulse 只在固定 taps 后出现；FILTER→DELAY 与 DELAY→FILTER 的 PCM 不完全相同。覆盖 stage>4、delay>8192、非有限 cutoff/mix/feedback、存储不足，失败时原 chain 不变。

- [x] **Step 2: 确认 RED 后实现固定状态链**

创建/START 时预计算 filter alpha，reset 所有 delay 光标和状态。delay 每声道执行 `delayed=line[pos]`、`out=dry*(1-mix)+delayed*mix`、`line[pos]=dry+delayed*feedback`。reverb 使用同一预分配 ring 的 149/311/587/997 帧 taps 和有界 feedback；每 voice 每 delay 类 stage 有独立 stereo storage，处理函数只做算术和数组访问。

- [x] **Step 3: GREEN、集成和变异**

Run: `cmake --build build-p10-audio -j6 --target test_audio_dsp test_audio_extended && ./build-p10-audio/test_audio_dsp && ./build-p10-audio/test_audio_extended`
Expected: 全通过，事件经 fake 引擎的输出与直接 DSP 参考逐样本一致。临时忽略第二 DSP stage、去掉 feedback 写回，分别确认组合/回声断言变红；恢复再跑。

- [x] **Step 4: 提交**

```bash
git add engine/src/audio/audio_dsp.* engine/src/audio/audio_extended.* engine/tests/test_audio_dsp.c engine/CMakeLists.txt
git commit -m "audio: add composable deterministic DSP chains"
```

### Task 4: 音乐播放列表与样本精确交叉淡化

**Files:**
- Modify: `engine/src/audio/audio_extended.h`, `engine/src/audio/audio_extended.c`
- Modify: `engine/tests/test_audio_extended.c`

**Interfaces:**

```c
AudioResult audio_music_set_playlist(AudioSystem *as,
    const AudioMusicPlaylistDesc *desc);
AudioResult audio_music_play(AudioSystem *as);
AudioResult audio_music_stop(AudioSystem *as);
AudioResult audio_music_update(AudioSystem *as);
AudioResult audio_music_state(AudioSystem *as, AudioMusicState *state,
                              u32 *track_index);
```

playlist 固定最多 16 个 clip handle；保存副本，不保留调用方数组。音乐只使用预留 voice 0/1，START 可带初始 gain 和 ramp，旧 voice 同时 ramp-to-zero-and-stop。每次更新由 atomic cursor 判断是否进入 fade，不在音频回调中切换 clip。

- [x] **Step 1: 写播放列表/淡化 RED**

两个 8 帧 clip 分别为 0.25/0.75，fade=4：渲染并逐帧 update，确认第 4..7 帧同时含旧 `(7-i)/8` 和新 `(i-3)/8` 分量，轨道索引只前进一次；旧 voice 完成后只输出新 clip。playlist loop 回第 0 轨，非 loop 最后一轨结束为 STOPPED。非法/超过 16 项/stale clip/fade 大于任一轨道长度均完整保留旧 playlist；运行中 set 返回 REJECTED。

- [x] **Step 2: 确认 RED 后实现原子双 voice 切换**

切换前同时检查新旧 voice 各有一个命令空间；START 已包含新 voice 的 fade-in，因此两队列各只需一项。只有两次 enqueue 都保证可成功后，才更新 current/previous/index/state；任何错误不启动新轨、不改旧轨增益。stop 对两个预留 voice 发 STOP，并在完成 serial 到达后回到 STOPPED。

- [x] **Step 3: GREEN 与关键变异**

Run: `./build-p10-audio/test_audio_extended`
Expected: 全通过。临时把 fade 分母改为 0/固定 1，或切换后不保存 previous voice，确认交叉淡化/旧轨静音测试变红；恢复再跑。

- [x] **Step 4: 提交**

```bash
git add engine/src/audio/audio_extended.* engine/tests/test_audio_extended.c
git commit -m "audio: add playlist crossfades"
```

### Task 5: 射线回调遮挡、距离衰减和空间生命周期

**Files:**
- Modify: `engine/src/audio/audio_extended.h`, `engine/src/audio/audio_extended.c`
- Modify: `engine/tests/test_audio_extended.c`
- Modify: `engine/src/audio/audio.c`（listener 更新桥接）

**Interfaces:**

```c
typedef bool (*AudioOcclusionRayFn)(void *user, Vec3 listener, Vec3 source);
void audio_set_occlusion_ray_callback(AudioSystem *as,
    AudioOcclusionRayFn fn, void *user);
AudioResult audio_voice_set_position(AudioSystem *as,
                                     AudioVoiceHandle voice, Vec3 position);
f32 audio_voice_spatial_gain(AudioSystem *as, AudioVoiceHandle voice);
```

- [x] **Step 1: 写空间 RED**

fake ray 记录 listener/source 并按 user 返回 blocked；source `(2,0,0)`、listener 原点、min=1/rolloff=1 时未遮挡 gain=0.5，遮挡后乘 occluded_gain=0.25 得 0.125。listener/source 更新会重算，非 spatial 事件始终为 1 且不发 ray；stale handle、NaN/Inf position 返回错误且不改变旧 gain。fake PCM 输出验证实际增益而非只查诊断字段。

- [x] **Step 2: 确认 RED 后实现主线程空间快照**

ray 只在 trigger、`audio_voice_set_position`、`audio_system_update` 的 LogicThread 路径执行。结果使用既有 `audio_attenuation_gain` 组合，写入每 voice `atomic_uint` f32-bit gain；回调只 load 并乘 source/bus/master/fade。listener 不变时不重复发 ray；无 ray callback 时只应用距离。

- [x] **Step 3: GREEN 与关键变异**

Run: `./build-p10-audio/test_audio_extended && ./build-p10-audio/test_audio`
Expected: 全通过。临时忽略 ray 返回值、跳过 listener 更新重算，分别确认遮挡/新距离 PCM 测试变红；恢复再跑。

- [x] **Step 4: 提交**

```bash
git add engine/src/audio/audio.c engine/src/audio/audio_extended.* engine/tests/test_audio_extended.c
git commit -m "audio: drive occlusion and distance from logic-thread rays"
```

### Task 6: 实时约束、兼容回归、sanitizers 与文档交付

**Files:**
- Create: `engine/tests/test_audio_realtime_contract.cmake`
- Modify: `engine/CMakeLists.txt`, `engine/src/audio/audio_stream.c`（仅实际兼容修复需要时）
- Create: `docs/design/audio_extended.md`, `.superpowers/sdd/audio-extended-report.md`
- Modify: `docs/design/core_style_runtime.md`, `docs/Implementation_Status.md`, `docs/superpowers/plans/2026-11-03-audio-extended.md`

- [x] **Step 1: 写回调契约并确认能失败**

CTest 脚本抽取 `voice_read`、`voice_render_frame`、`audio_dsp_chain_process` 的函数体，拒绝 `malloc/calloc/realloc/free/fopen/fread/ma_decoder/audio_event_trigger/audio_music_update/ray_callback`。测试 null 后端并发 trigger/listener/stop/destroy 生命周期；fake 做同输入两次 bit-exact PCM。审计 `audio_stream.c`：若扩展路径引用 `MA_SOUND_FLAG_STREAM`，先写无文件回调测试并改为预解码 PCM；保留 legacy API 时必须在报告明确其边界，不能把 legacy 文件流描述成实时安全路径。

- [x] **Step 2: 构建三棵独立树并运行 focused/既有回归**

```bash
cmake -S engine -B build-p10-audio -DENGINE_RHI_BACKEND=opengl
cmake -S engine -B build-p10-audio-asan -DENGINE_RHI_BACKEND=opengl -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake -S engine -B build-p10-audio-tsan -DENGINE_RHI_BACKEND=opengl -DENGINE_USE_TSAN=ON
cmake --build <tree> -j6 --target test_audio test_audio_extended test_audio_dsp
ctest --test-dir <tree> -R 'test_audio|audio_realtime' --output-on-failure
```

Expected: normal、ASan+UBSan、TSan 全通过且无 sanitizer 报告。再构建 `engine`/`audio_stream` 所属目标并运行现有相关回归；若环境缺少图形依赖，记录配置事实，不关闭 sanitizer 或跳过音频测试。

- [x] **Step 3: 最终变异、文档与报告**

恢复所有变异后重跑 focused。设计文档写明 48 clips、32 events、30 事件 voices + 2 音乐 voices、16 commands/voice、16 tracks、4 DSP stages、8192 delay 帧和 48000Hz 输入限制；状态文档不声称听测、Windows/macOS、真设备、重采样或旧文件流实时安全已通过。报告逐项记录 RED/GREEN 的实际输出、变异与恢复、所有命令和 commit id。

- [x] **Step 4: 最终检查和本地提交**

```bash
git diff --check
git status --short --branch
git add engine docs .superpowers/sdd/audio-extended-report.md
git commit -m "test: verify audio realtime lifecycle contracts"
```

确认只包含 P10 文件，工作树无未提交源文件，不 push；最终 handoff 返回状态、逐任务提交、三树测试摘要和未验证限制。
