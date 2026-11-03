# P10 扩展音频交付报告

日期：2026-11-03
工作树：`.worktrees/cry-audio`
分支：`cry-wave2-audio`（base `a0bfeb95`）
计划：`docs/superpowers/plans/2026-11-03-audio-extended.md`

## 交付状态

实现已覆盖命名声音事件、并发/重触发、音乐 playlist/交叉淡化、滤波/延迟/混响 DSP、射线遮挡与距离衰减、null/fake 生命周期和 legacy 文件回调 PCM 化。所有新代码复用现有 `AudioSystem`/`ma_engine`，没有 push，没有真实听测声明。

## 逐任务 RED / GREEN / 变异

### 计划

- `ba5ad8e1` `docs: plan extended audio capabilities`
- 基线：既有 `test_audio` 17/17；确认 linked worktree、分支和干净起点。

### Task 1：PCM voice、后端和 clip

- 提交：`9b204963` `audio: add fixed PCM voices and headless backends`
- RED-1：最小后端桩下 `test_audio_extended` 0/3，三项均因 `audio_system_create_ex` 返回 NULL。
- RED-2：实现后端后，fake 静默通过，clip 注册两项失败（1/3）；不是只用编译缺失充当 RED。
- GREEN：3/3；既有 `test_audio` 17/17。
- 变异：重名注册错误增加 `clip_count`，结果 2/3，`audio_clip_count(as) != 1u` 按预期失败；恢复后 3/3。

### Task 2：命名事件和并发/重触发

- 提交：`f43bfeea` `audio: add named event concurrency policies`
- RED：事件桩下 3/9，六个新增事件测试均失败，旧三项保持通过。
- 集成调查：初次实现暴露 miniaudio `ma_sound` 固定 512 帧 processing-cache 预读，短 clip 提前结束。改为把相同 custom sources 直接接入现有 `ma_data_source_node`/node graph；不是修改测试游标来掩盖问题。另一个测试自身串音问题通过先停止旧的 capped voice 修正。
- GREEN：9/9；旧 `test_audio` 17/17。
- 变异：移除 voice generation 校验，结果 8/9，旧 handle 的 `audio_voice_stop` 未返回 `AUDIO_STALE`；恢复后 9/9。

### Task 3：可组合 DSP

- 提交：`e70a7a56` `audio: add composable deterministic DSP chains`
- RED：纯 DSP 0/5；真实 fake 事件集成 9/10，延迟样本未生效。
- GREEN：纯 DSP 5/5，扩展 10/10，旧音频 17/17。滤波阶跃、delay tap/feedback、reverb taps 和 filter+delay 均使用手算 PCM。
- 变异：去掉 delay feedback 写回，纯 DSP 4/5，0.5 回声断言失败；恢复后 5/5。

### Task 4：音乐 playlist 和交叉淡化

- 提交：`ed2a7144` `audio: add playlist crossfades`
- RED：10/14，四个新增音乐测试均因 playlist 桩失败。
- GREEN：14/14；两组逐帧交叉淡化、loop wrap、零淡化结束、非法 playlist 失败原子均通过。
- 变异：禁止 ramp 推进，结果 12/14，两个交叉淡化 PCM 测试按预期失败；恢复后 14/14。

### Task 5：遮挡、距离和 bus/master

- 提交：`9eee217b` `audio: drive occlusion and distance from game-thread rays`
- RED：14/17；ray 未调用、空间诊断桩错误、bus/master 未影响 PCM。
- GREEN：17/17；真实 fake PCM 验证 0.5 距离增益、0.125 遮挡+距离、listener 重算、非空间无 ray 和总线合成。
- 变异：ray 结果恒按遮挡处理，结果 16/17，未遮挡 0.5 断言失败；恢复后 17/17。

### Task 6：实时边界、legacy、null/fake 和 sanitizers

- RED：legacy WAV 测试在动态解码/流式路径下为 17/18，首个 0.25 样本缺失。
- 修复：`audio_play`、`audio_play_3d`、`audio_play_streamed` 改为打开时 `DECODE | NO_PITCH`；兼容 API 名称不变，移除回调文件流。
- GREEN：legacy 18/18；加入 bit-exact 与 null 命令生命周期后 20/20。
- 自审补充 RED：填满 16 项命令环后，overload 仍多调用一次 ray，结果 20/21；把队列空间检查移到 ray 之前后 21/21。此处为差异自审，本会话没有独立 reviewer 工具，未声称独立评审。
- 实时契约变异：把 legacy flags 改回 `MA_SOUND_FLAG_STREAM`，`test_audio_realtime_contract` 明确失败“legacy playback must not stream from the audio callback”；恢复后通过。
- null 压测最初把合法命令环 `AUDIO_OVERLOAD` 当成测试失败；已修正测试以接受明确背压，生产容量和错误语义未放宽。

## 最终验证命令与结果

normal：

```bash
cmake -S engine -B build-p10-audio -DENGINE_RHI_BACKEND=opengl -DCMAKE_BUILD_TYPE=Debug
cmake --build build-p10-audio -j6 --target test_audio test_audio_extended test_audio_dsp
ctest --test-dir build-p10-audio -R 'test_audio' --output-on-failure
cmake --build build-p10-audio -j6 --target engine
```

结果：focused 4/4（`test_audio`、`test_audio_extended`、`test_audio_dsp`、`test_audio_realtime_contract`）；正式 `engine` 目标构建成功；最终 `git diff --check` 通过。

ASan+UBSan：

```bash
cmake -S engine -B build-p10-audio-asan -DENGINE_RHI_BACKEND=opengl -DCMAKE_BUILD_TYPE=Debug -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-p10-audio-asan -j6 --target test_audio test_audio_extended test_audio_dsp
ctest --test-dir build-p10-audio-asan -R 'test_audio' --output-on-failure
```

结果：4/4，无 ASan/UBSan 报告。

TSan：

```bash
cmake -S engine -B build-p10-audio-tsan -DENGINE_RHI_BACKEND=opengl -DCMAKE_BUILD_TYPE=Debug -DENGINE_USE_TSAN=ON
cmake --build build-p10-audio-tsan -j6 --target test_audio test_audio_extended test_audio_dsp
ctest --test-dir build-p10-audio-tsan -R 'test_audio' --output-on-failure
```

结果：4/4，无 TSan 报告。跨线程证据覆盖真实 null 设备上的 trigger/restart、listener、music update/stop 和 destroy；fake 提供确定性 PCM，不冒充设备听测。

## 限制

- 仅接受 48000 Hz f32 mono/stereo PCM；没有做跨采样率重采样。
- 混响是固定四 tap 的有界算法，不是物理空间声学；没有实际听测、真实声卡、Windows/macOS 或 CI 证据。
- legacy `audio_play_streamed` 为兼容名称，现为打开时完整解码，可能阻塞调用线程并占用大文件解码内存。
- 固定容量满时返回错误；没有自动扩容。所有行为细节见 `docs/design/audio_extended.md`。
