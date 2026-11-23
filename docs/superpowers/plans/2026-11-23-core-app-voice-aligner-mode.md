# core_app 语音泵对齐器模式配置实施计划（2026-11-23）

## 背景

`AudioVoiceAligner` 已支持 sinc 与交叉淡化，但 core_app 语音泵私有对齐器只能使用默认线性、立即切换模式。

## 契约

- `CoreAppVoiceConfig` 新增 `aligner_sinc`（bool）与 `aligner_crossfade_frames`（0..48000）。零初始化即旧行为。
- `core_app_voice_create` 在创建对齐器后应用两项设置；对齐器拒绝的淡化时长（>48000）返回 `BREAK_RUNTIME_INVALID`，且不泄漏已创建的采集与对齐器。
- 泵内行为与以同样配置独立构造的对齐器 + 处理器逐位一致。

## TDD

1. `test_core_app_voice` 新增：非法淡化时长返回 INVALID；启用 sinc 与 480 帧淡化时，手动泵出的包与独立管线（同样 set_sinc/set_crossfade）逐位一致。
2. RED → 实现 → GREEN；变异：不应用 sinc、不应用淡化、不校验。
3. 完整 Vulkan/OpenGL，ASan+UBSan/TSan 下 `test_core_app_voice`；更新 `core_app_integration.md`、`audio_extended.md`、状态与缺口文档；评审后推送并核验远端。
