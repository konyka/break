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


# P10 fix round 3

日期：2026-11-05
基线：`12fefa2e`
复审输入：`.superpowers/sdd/review-fix2-findings.md` 全部条目

## 修复

提交：`e2157bf4` `audio: make spatial snapshot updates atomic`

- START 初始 gain 改为单次整快照 `atomic_compare_exchange_strong`。expected 同时验证 revision 和 spatial_epoch；GameThread 在 load 与 CAS 之间发布新 revision 时 CAS 失败，不重试、不写旧 START。
- GameThread 的 START 与 position 发布也使用整快照 CAS，避免 callback/GameThread 双向丢失更新。
- 新增 `spatial_epoch`。voice_read 只在它等于 `playing_epoch` 时采用新快照，否则保留 callback 私有的 `applied_spatial_gain`，所以 RESTART 待消费期间，新 epoch position/listener 不会立即调制旧 PCM。
- revision 在 voice 生命周期内单调递增，不再随 epoch 重置。达到 UINT32_MAX 后 position 和新 START 均返回 `AUDIO_OVERLOAD`，不回绕。epoch 0/max 退休政策保持不变。
- `test_audio_extended` 专用编译钩子可在 load 与 CAS 之间确定性注入 revision 更新；正式 engine 不包含该钩子。

## RED / GREEN / 变异

- 受控 CAS 交错、held-command 旧 epoch PCM、revision max 三项首次结果为 36/39。修复后 39/39。
- revision 注入最初只改主线程 revision，CAS 正确拒绝不一致快照；测试改为同时注入匹配 snapshot 后，验证 max-1→max 成功、max 后 position/START 拒绝且 snapshot/epoch 不变。
- 将初始 CAS 退化为 store 的生产变异为 38/39，受控 CAS 交错再次覆盖旧 gain；恢复后通过。
- 移除 voice_read epoch 匹配的变异为 38/39，held old PCM 再次使用新 epoch 增益；恢复后通过。
- 最终既有 `test_audio` 17/17、`test_audio_extended` 39/39、`test_audio_dsp` 10/10。

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
2/4 test_audio_extended .............. Passed    0.11 sec
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
2/4 test_audio_extended .............. Passed    0.40 sec
3/4 test_audio_dsp ................... Passed    0.01 sec
4/4 test_audio_realtime_contract ..... Passed    0.01 sec
100% tests passed, 0 tests failed out of 4
```

无 TSan 报告。受控交错行为断言不依赖 TSan 发现逻辑竞态。

差异检查：

```bash
git diff --check 12fefa2e..HEAD
```

通过，无输出。未 push。

## 限制

没有真实设备、实际听测、Windows/macOS 或第四轮独立评审证据。CAS/epoch 交错由测试 TU 内受控注入验证，边界同样通过注入覆盖，不是依赖概率性线程调度。


# P10 fix round 4

日期：2026-11-05
基线：`9cf01634`
复审输入：`.superpowers/sdd/review-fix3-findings.md` 两项开放 Important

## 修复

代码提交：`6c1149ff` `audio: validate spatial snapshots across interleavings`

- `voice_read` 在 acquire-load 空间 snapshot 后再次 acquire-load `spatial_epoch`。只有前后 epoch 相同且等于 `playing_epoch` 才采用 snapshot，RESTART→position/listener 落入原两次 load 间隙时，旧 PCM 保留原增益；新 START 消费后再采用新 epoch 快照。
- GameThread `spatial_publish` 的 CAS 失败路径重新验证非零/当前 epoch、revision 上限、主线程 revision 与当前 snapshot，再以新 position/listener 增益 CAS。callback START 先改变同级 revision 的 gain bits 时，listener 不再静默丢失，也不需要 listener 再次移动。`voice->spatial_revision` 仍只在成功后提交。
- START 初始增益仍是单次整快照 strong CAS，没有重试旧 START。固定容量、热路径不分配、epoch 0/max 退休和 revision max 拒绝政策未改；既有边界与 START CAS 测试继续通过。
- 新增两个测试编译钩子仅属于 `test_audio_extended`，正式 engine 不定义。钩子位于生产 load/CAS 间隙并调用真实 trigger/position/listener/START 路径，不是概率线程测试或另写状态模型。

## RED / GREEN / 变异

- `restart_between_epoch_and_snapshot_loads_keeps_old_pcm_gain`：在 epoch load 与 snapshot load 之间完成真实 RESTART(pos=4)→position(pos=8)。未修复时注入当帧旧 PCM 从应有 0.5 变为 0.125，结果 39/40；加入后读 epoch 复核后 40/40，下一帧新 epoch PCM 为 0.125。
- `listener_start_cas_loss_republishes_same_listener`：listener CAS 前，从真实命令环取出当前 START 并调用生产 `voice_apply_initial_spatial`，确认 snapshot 确实从旧 gain 0.5 变为 START gain 0.25。未修复时相同 listener 再 update 仍滞留 0.25 而非目标 0.125，结果 40/41；重新验证并重发后 41/41，真实 PCM 也为 0.125。
- 生产变异一：把第二次 epoch load 改为复用第一次局部值，可编译运行，结果 40/41，只有 epoch/snapshot 间隙用例失败（0.125 而非 0.5）；恢复后通过。
- 生产变异二：把 GameThread CAS 失败恢复为立即 `AUDIO_OVERLOAD`，可编译运行，结果 40/41，只有 listener 反向交错用例失败（0.25 而非 0.125）；恢复后通过。
- 最终 `test_audio_extended` 41/41；既有 `test_audio`、`test_audio_dsp` 和实时回调源码契约均在下列 focused CTest 中通过。

## 命令与真实输出

normal：

```bash
cmake --build build-p10-audio -j6 --target test_audio test_audio_extended test_audio_dsp engine
./build-p10-audio/test_audio_extended
ctest --test-dir build-p10-audio -R 'test_audio' --output-on-failure
```

```text
=== Results: 41 passed, 0 failed, 41 total ===
1/4 test_audio ....................... Passed    0.00 sec
2/4 test_audio_extended .............. Passed    0.05 sec
3/4 test_audio_dsp ................... Passed    0.00 sec
4/4 test_audio_realtime_contract ..... Passed    0.01 sec
100% tests passed, 0 tests failed out of 4
engine: Built target engine
```

ASan+UBSan（cache 确认 `ENGINE_USE_ASAN=ON`、`ENGINE_USE_UBSAN=ON`）：

```bash
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

TSan（cache 确认 `ENGINE_USE_TSAN=ON`）：

```bash
cmake --build build-p10-audio-tsan -j6 --target test_audio test_audio_extended test_audio_dsp
ctest --test-dir build-p10-audio-tsan -R 'test_audio' --output-on-failure
```

```text
1/4 test_audio ....................... Passed    0.01 sec
2/4 test_audio_extended .............. Passed    0.40 sec
3/4 test_audio_dsp ................... Passed    0.01 sec
4/4 test_audio_realtime_contract ..... Passed    0.01 sec
100% tests passed, 0 tests failed out of 4
```

无 TSan 报告。受控交错的行为断言不依赖 TSan 发现逻辑竞态。

差异检查：

```bash
git diff --check 9cf01634..HEAD
```

通过，无输出。未 push。

## 限制

没有真实声卡、实际听测、Windows/macOS、跨采样率或第四轮独立评审证据。两个新交错均由测试 TU 内生产路径钩子确定性覆盖；TSan 是额外检查，不作为交错命中证据。
