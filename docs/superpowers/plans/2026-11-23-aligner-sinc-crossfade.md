# 语音对齐器 sinc 与交叉淡化配置实施计划（2026-11-23）

## 背景

`docs/design/audio_extended.md`「语音参考自动对齐」未做项包含 sinc/交叉淡化配置。对齐器私有的延迟线只能使用默认线性、立即切换模式。直接开放底层开关有两个问题：sinc 模式固定多出 8 帧，对齐结果会落后回声；淡化期间延迟线拒绝新的延迟，现有更新路径会把 `AUDIO_REJECTED` 当作 `process` 失败返回。

## 契约

- `audio_voice_aligner_set_sinc` / `audio_voice_aligner_sinc`：切换延迟线 sinc 模式。对齐器应用 `max(测得延迟 − 8, 0)`，使输出总延迟等于测得延迟（测得延迟小于 8 帧时为 8）。切换后立即按当前测得延迟重新应用；淡化进行中返回 `AUDIO_REJECTED` 且状态不变。
- `audio_voice_aligner_set_crossfade_frames` / `audio_voice_aligner_crossfade_frames`：转发延迟线配置（0..48000，淡化中 `AUDIO_REJECTED`）。
- `audio_voice_aligner_delay` 返回输出的实际总延迟：延迟线延迟加 sinc 额外延迟，线性模式下与原值相同。
- 更新到达时若延迟线仍在淡化，跳过本次应用而不是失败；`updates` 照常计数，下一次更新重新应用。其他错误（测试钩子注入的 `AUDIO_FAILED`）仍返回。
- `reset` 保留两项配置，结果与新建并做同样配置的对齐器逐位一致（复位应用 0 延迟时不启动淡化）。

## TDD 步骤

1. `test_audio_voice_aligner` 新增：配置参数与默认值；sinc 模式补偿后对齐输出与回声的零延迟归一化相关 > 0.98 且延迟在 12.5±0.25；淡化中途到达的更新被跳过且 `process` 成功，下一周期再应用；淡化中切换 sinc 被拒绝；带配置复位与新建对象逐位一致。
2. 确认 RED，再实现，确认 GREEN，做关键变异。
3. 完整 Vulkan/OpenGL，ASan+UBSan/TSan 下目标测试；更新设计、状态与缺口文档，评审后推送 master 并核验远端。
