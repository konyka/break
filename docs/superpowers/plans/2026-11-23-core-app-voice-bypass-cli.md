# core_app 语音处理链 bypass 命令行开关实施计划（2026-11-23）

## 背景

`AudioVoiceProcessorConfig.bypass_stages` 已支持关闭单个阶段，但 core_app 命令行无法设置，语音泵总是运行全部阶段。

## 契约

- 新增 `--voice-bypass LIST`，LIST 为逗号分隔的 `echo`、`noise`、`gate`、`agc`（可重复、顺序无关），映射为 `AUDIO_VOICE_PROCESSOR_STAGE_*`。空项、未知名或空列表为 CLI 错误（退出 2）；要求 `--voice=fake|device`。
- `CoreAppConfig.voice_bypass_stages` 在语音通道启动时写入 `CoreAppVoiceConfig.processor.bypass_stages`。
- `core_app_voice_bypass_stages` 查询处理链实际生效的位（NULL 为 0），由新的 `audio_voice_processor_bypass_stages` 提供。
- 给出该开关时，在 ready 行（及可选的 voice_aligner 行）之后写 `COREAPPTRACE version=1 event=voice_bypass echo=0|1 noise=0|1 gate=0|1 agc=0|1`，数值取自查询；不给开关时 trace 不变。

## TDD

1. `test_audio_voice_processor`：`audio_voice_processor_bypass_stages` 的 NULL 与配置值。`test_core_app_voice`：查询默认 0、配置值透传，且泵输出与同配置独立处理链一致。
2. `test_core_app_voice_lane.cmake`：`--voice=fake --voice-bypass=gate,agc` 写出 `event=voice_bypass echo=0 noise=0 gate=1 agc=1`、仍消费全部包、两次一致；与 aligner 开关同时给出时两行顺序固定；错误组合退出 2。
3. RED → 实现 → GREEN；变异：解析遗漏某名、不写入配置、查询返回常量、缺依赖校验、无开关也写 trace。
4. 完整 Vulkan/OpenGL，ASan+UBSan/TSan（`ENGINE_USE_TSAN=ON`）下相关目标；更新设计、状态与缺口文档；评审后推送并核验远端。
