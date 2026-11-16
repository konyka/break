# 事件 voice 后方提示（rear cue）

Status: Done

## 目标

`AudioEventDesc.rear_cue` 让空间事件 voice 获得与 `audio_pcm_stream_set_rear_cue` 相同的后方低通提示：
声源在监听者正后方时用 `AUDIO_PCM_STREAM_REAR_CUTOFF_HZ` 的一阶低通，前方和侧面不滤波。

## 设计

- `rear_cue` 要求 `spatial`，否则 `audio_event_register` 返回 `AUDIO_INVALID`。
- 系数用已有的 `rear_cue_alpha(as, position)`；desc 未开启时为 1。
- START 命令携带初始 alpha（`spatial_rear`）。后续位置或监听者更新时，`spatial_publish`
  在增益快照 CAS 之前写入 `rear_snapshot = spatial_pack(revision, alpha)`，与 `pan_snapshot` 同一协议。
- 混音只在 rear 快照的 revision 等于所采用的增益 revision 时才采用 alpha，
  因此 RESTART 后的新 alpha 不会作用到旧 epoch 仍在播放的 PCM。
- 每个 voice 有 `rear_state[2]`，消费 START 时清零；滤波放在声像之前、DSP 链之前。
  alpha 为 1 时状态跟随信号，开启时从当前帧开始，不产生跳变。
- 混音侧代码留在 `voice_read` 内，已被实时合同覆盖。

## TDD 步骤

1. RED：新增测试
   - `event_rear_cue_requires_spatial`
   - `rear_cue_event_leaves_front_and_side_untouched`（与关闭时逐位相同）
   - `rear_cue_event_filters_a_source_behind`（阶跃响应符合 `ref_rear_alpha(1)`）
   - `rear_cue_event_follows_the_listener`（转身后立即停止滤波）
   - `rear_cue_event_restart_keeps_the_old_alpha_on_held_pcm`
   - `rear_cue_event_keeps_stereo_state_apart`
2. GREEN：实现头文件字段与 audio_extended.c 改动。
3. 变异测试、ASan、TSan、音频 ctest、三棵完整构建树。
4. 文档：`docs/design/audio_extended.md`、`docs/Implementation_Status.md`、
   `docs/cross_engine/missing_capabilities.md`、头文件注释。
5. 提交、推送、轮询 CI。

## Result

- RED：新测试引用 `rear_snapshot` 等字段，编译失败。GREEN：`test_audio_extended` 94/94，`test_voice_playback` 4/4。
- 额外测试：`rear_cue_event_keeps_its_alpha_until_that_revision_is_published`。
- 变异 18 项：首轮存活「监听者更新不写系数」「初始化 applied_rear_alpha=1」。前者在 `rear_cue_event_follows_the_listener` 中加只转身的断言后被捕获；后者是冗余赋值（START 总会设置），已删除。其余全部被捕获。
- ASan+UBSan 94/94；TSan 三次 94/94，0 报告。
- 正后方系数 `α = 1 − exp(−2π·5000/48000) ≈ 0.48`；滤波在增益之前，距离 2 时阶跃终值 0.5。
