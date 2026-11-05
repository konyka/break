# P10 fix round 1 报告

日期：2026-11-03
基线：`e82dae38`
评审输入：`.superpowers/sdd/review-findings.md` 全部条目

## 修复与提交

- `7a6c20f2` `audio: isolate voice command epochs`
  - 每次 START 分配独立 64-bit 内部 epoch；公共 generation 语义不变，RESTART handle 保持不变。
  - 自然完成、STOP、RAMP 只作用于对应 epoch；回收和 music done 只比较当前 epoch。
  - cursor 仅在回调消费 START 时归零，初始 spatial gain 随 START 发布。enqueue 是提交点，失败不改 serial/owner/order/cursor/gain。
- `5ec9870c` `audio: validate spatial and bus inputs`
  - listener 九分量先验证有限性；距离与衰减用 double 计算并验证后才 ray/发布。
  - listener 更新先回收完成 voice，跳过 stop-pending；position 在 stop-pending 时拒绝。
  - bus 在 legacy/extended 任一状态改变前统一拒绝 NaN/Inf；stale clip 返回 `AUDIO_STALE`，零 id 返回 `AUDIO_INVALID`。
- `149fc68f` `audio: restore decoded 3d doppler`
  - 三个 legacy 文件入口移除 `NO_PITCH`，保留打开时 DECODE。真实 `audio_play_3d` 源速度回归证明 Doppler 改变 PCM。
- `fa03a214` `test: harden audio DSP and callback contracts`
  - DSP frame×channel 先用 `usize` 计算；补非有限参数、stereo 独立状态及两种 filter/delay 顺序参考 PCM。
  - 实时扫描扩展到 dequeue/finish/configure/drain/fade/read/reverb/process 完整调用链，并禁止 legacy `NO_PITCH`。

## RED / GREEN / 变异证据

- epoch：新增 STOP→RESTART、自然末帧、cursor 和初始 gain 测试后，结果为 22/25；STOP→RESTART 被旧完成回收，cursor 在入队前已归零，初始 gain 提前改变。修复后 25/25。
- epoch 可编译变异：把回收条件退化为公共 serial，结果 24/25，`stop_then_restart_before_drain_keeps_new_epoch_live` 的 active count 再次为 0；恢复后 25/25。
- 输入验证：新增 NaN/Inf listener、stop-pending ray、bus NaN/Inf、stale clip 后为 25/29；修复后 29/29。极端有限 listener 也验证 ray 输入有限且输出衰减为 0.01。
- Doppler：`NO_PITCH` 下两份不同源速度的 decoded 3D PCM 完全相同，新增测试为 29/30。移除 flag 后，首块只更新 spatializer Doppler，第二块才应用 pitch；按真实 miniaudio 时序比较第二块，最终 30/30。
- DSP 索引契约：宽索引要求加入时 `test_audio_realtime_contract` 失败，输出 `DSP frame indexing must widen before multiplication`；修复后通过。
- 扫描覆盖变异：在 `voice_configure_dsp` 临时加入 `malloc`，契约失败并指出 `malloc is forbidden ... voice_configure_dsp`；恢复后通过。
- NaN/Inf DSP 参数、stereo 和链顺序新增行为覆盖均通过。最终 `test_audio_extended` 30/30、`test_audio_dsp` 8/8、既有 `test_audio` 17/17。

## 命令与输出

normal：

```bash
cmake --build build-p10-audio -j6 --target test_audio test_audio_extended test_audio_dsp engine
ctest --test-dir build-p10-audio -R 'test_audio' --output-on-failure
```

```text
1/4 test_audio ....................... Passed
2/4 test_audio_extended .............. Passed
3/4 test_audio_dsp ................... Passed
4/4 test_audio_realtime_contract ..... Passed
100% tests passed, 0 tests failed out of 4
engine: Built target engine
```

ASan+UBSan：

```bash
cmake -S engine -B build-p10-audio-asan -DENGINE_RHI_BACKEND=opengl -DCMAKE_BUILD_TYPE=Debug -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-p10-audio-asan -j6 --target test_audio test_audio_extended test_audio_dsp
ctest --test-dir build-p10-audio-asan -R 'test_audio' --output-on-failure
```

```text
1/4 test_audio ....................... Passed
2/4 test_audio_extended .............. Passed
3/4 test_audio_dsp ................... Passed
4/4 test_audio_realtime_contract ..... Passed
100% tests passed, 0 tests failed out of 4
```

无 ASan/UBSan 报告。

TSan：

```bash
cmake -S engine -B build-p10-audio-tsan -DENGINE_RHI_BACKEND=opengl -DCMAKE_BUILD_TYPE=Debug -DENGINE_USE_TSAN=ON
cmake --build build-p10-audio-tsan -j6 --target test_audio test_audio_extended test_audio_dsp
ctest --test-dir build-p10-audio-tsan -R 'test_audio' --output-on-failure
```

```text
1/4 test_audio ....................... Passed
2/4 test_audio_extended .............. Passed
3/4 test_audio_dsp ................... Passed
4/4 test_audio_realtime_contract ..... Passed
100% tests passed, 0 tests failed out of 4
```

无 TSan 报告。真实 null 后端继续执行并发 trigger/restart、listener、music update/stop/destroy；fake 输出用于确定性 PCM，不表示实际听测。

## 差异检查

```bash
git diff --check e82dae38..HEAD
```

通过，无输出。没有 push。

## 限制

- 未做真实声卡、实际听测、Windows/macOS 或跨采样率验证。
- legacy 单发音源存在 miniaudio resampler EOF 冲刷语义；PCM fixture 使用循环源验证解码内容，Doppler 使用两个处理块验证实际 pitch 应用。
- 本轮依据独立评审逐项修复并做差异自审，未进行第二轮独立评审。


# P10 fix round 2

日期：2026-11-05
基线：`df8fc32e`
复审输入：`.superpowers/sdd/review-fix1-findings.md` 全部条目

## 修复

提交：`8ff137c1` `audio: version spatial snapshots and playback starts`

- 空间快照使用一个 C11 `atomic_uint_least64_t`：高 32 位 revision，低 32 位 f32 gain bits。START 只在 snapshot revision 仍等于命令 revision 时应用初始 gain；position/listener 只在当前 epoch 匹配时递增 revision 并发布，因此旧 START 不会覆盖较新的位置。
- 回调消费 START 后发布独立 `started_epoch`，并在 cursor 归零之后 release-store。`audio_music_update` 仅在 `started_epoch == voice->epoch` 时读取 cursor，未消费的新播放不会依据旧 cursor 跳轨。
- epoch 0 保留为未启动/无效值。允许 max-1→max；达到 UINT64_MAX 后 voice 永久退休，后续 START 返回 `AUDIO_OVERLOAD`，不绕回、不重置、不与旧完成身份重合。revision 达到 UINT32_MAX 时 position/listener 停止发布；新 epoch 从 revision 1 开始。
- 快照字段有 `sizeof(u32) == sizeof(f32) == 4` 和 `sizeof(u64) == 8` 的 C11 静态断言。原子类型不要求 lock-free，仅依赖标准原子语义；Linux normal/ASan+UBSan/TSan 已验证，Windows/macOS 未验证。
- 补 reverb.mix NaN/Inf、delay/reverb stereo 独立状态和 extended stereo clip PCM 覆盖。

## RED / GREEN / 变异

- 空间 trigger→position、trigger→listener、RESTART→position 和音乐 replay 用例首次执行时，空间三项失败；音乐首次用例只经过未使用 voice，扩展到第二次 replay 后也失败。四项共同结果为 30/34；修复后 34/34。
- epoch 边界注入在 max 后仍返回成功并绕回 0，结果 34/35；加入退休政策后 35/35，且 serial/order/snapshot 不变。
- START revision 可编译变异为 33/36，三个空间顺序用例全部重新失败；恢复后 36/36。
- 移除 started_epoch gate 的变异为 35/36，第二次零淡化 replay 再次跳轨；恢复后通过。
- extended 右声道复制左声道变异为 35/36，stereo clip 断言失败；恢复后通过。
- DSP 右声道复制左声道变异为 7/10，filter/delay/reverb 三个 stereo 测试均失败；恢复后 10/10。
- 最终既有 `test_audio` 17/17、`test_audio_extended` 36/36、`test_audio_dsp` 10/10。

## 命令与真实输出

normal：

```bash
cmake --build build-p10-audio -j6 --target test_audio test_audio_extended test_audio_dsp engine
ctest --test-dir build-p10-audio -R 'test_audio' --output-on-failure
```

```text
1/4 test_audio ....................... Passed    0.00 sec
2/4 test_audio_extended .............. Passed    0.05 sec
3/4 test_audio_dsp ................... Passed    0.00 sec
4/4 test_audio_realtime_contract ..... Passed    0.01 sec
100% tests passed, 0 tests failed out of 4
engine: Built target engine
```

ASan+UBSan：

```bash
cmake -S engine -B build-p10-audio-asan -DENGINE_RHI_BACKEND=opengl -DCMAKE_BUILD_TYPE=Debug -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-p10-audio-asan -j6 --target test_audio test_audio_extended test_audio_dsp
ctest --test-dir build-p10-audio-asan -R 'test_audio' --output-on-failure
```

```text
1/4 test_audio ....................... Passed    0.01 sec
2/4 test_audio_extended .............. Passed    0.10 sec
3/4 test_audio_dsp ................... Passed    0.01 sec
4/4 test_audio_realtime_contract ..... Passed    0.01 sec
100% tests passed, 0 tests failed out of 4
```

无 ASan/UBSan 报告。

TSan：

```bash
cmake -S engine -B build-p10-audio-tsan -DENGINE_RHI_BACKEND=opengl -DCMAKE_BUILD_TYPE=Debug -DENGINE_USE_TSAN=ON
cmake --build build-p10-audio-tsan -j6 --target test_audio test_audio_extended test_audio_dsp
ctest --test-dir build-p10-audio-tsan -R 'test_audio' --output-on-failure
```

```text
1/4 test_audio ....................... Passed    0.01 sec
2/4 test_audio_extended .............. Passed    0.39 sec
3/4 test_audio_dsp ................... Passed    0.01 sec
4/4 test_audio_realtime_contract ..... Passed    0.01 sec
100% tests passed, 0 tests failed out of 4
```

无 TSan 报告。

差异检查：

```bash
git diff --check df8fc32e..HEAD
```

通过，无输出。未 push。

## 限制

没有真实声卡或实际听测证据，也没有 Windows/macOS 或第三轮独立评审。测试使用 fake 确定性 PCM 和真实 miniaudio null 后端生命周期；退休与 revision 边界采用测试 TU 内注入，不是等待自然 64-bit 回绕。
