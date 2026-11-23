# 语音处理链可配置 bypass 实施计划（2026-11-23）

## 背景

`docs/design/audio_extended.md`「集成语音处理链」未做项包含可配置 bypass。处理链固定执行 AEC+残余抑制 → 频谱降噪 → 噪声门 → AGC，调用者无法关闭单个阶段做对照或排查。

## 契约

- `AudioVoiceProcessorConfig` 末尾新增 `u32 bypass_stages`，取 `AUDIO_VOICE_PROCESSOR_STAGE_ECHO`（AEC 与残余抑制一起）、`AUDIO_VOICE_PROCESSOR_STAGE_NOISE`、`AUDIO_VOICE_PROCESSOR_STAGE_GATE`、`AUDIO_VOICE_PROCESSOR_STAGE_AGC` 的按位或。零初始化即旧行为。
- 在创建时确定，运行中不切换：频谱降噪有固定帧延迟，中途切换会使输出错位。未知位返回 `AUDIO_INVALID`。
- 被 bypass 的阶段仍按原规则校验并创建，只是不处理；`reset` 照常重置。频谱降噪被 bypass 时 `latency_frames` 返回 0。
- 输出与去掉相应阶段的手工链逐位一致；四个阶段全部 bypass 时采集保持不变。

## TDD

1. `test_audio_voice_processor`：未知位 INVALID 且 `*out` 不变；每个单阶段 bypass 与对应手工链一致，并与完整链不同；全部 bypass 为恒等；noise bypass 时延迟为 0；带 bypass 的 reset 与新建一致。
2. RED → 实现 → GREEN；逐阶段变异。
3. 完整 Vulkan/OpenGL，ASan+UBSan 与（CI）TSan；更新设计、状态与缺口文档；评审后推送并核验远端。
