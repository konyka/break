# core_app 语音对齐器模式命令行开关实施计划（2026-11-23）

## 背景

`CoreAppVoiceConfig` 已有 `aligner_sinc` 与 `aligner_crossfade_frames`，但 core_app 命令行无法开启，`app_voice_config` 始终使用默认值。

## 契约

- 新增 `--voice-aligner-sinc` 与 `--voice-aligner-crossfade FRAMES`（1..48000 的十进制整数）。两者都要求 `--voice=fake|device`，否则为 CLI 错误（退出 2）；非法帧数同样退出 2。
- `CoreAppConfig` 新增 `voice_aligner_sinc`、`voice_aligner_crossfade_frames`，语音通道启动时在 `app_voice_config` 之后写入 `CoreAppVoiceConfig`。
- `CoreAppVoice` 新增只读查询 `core_app_voice_aligner_sinc`、`core_app_voice_aligner_crossfade_frames`（NULL 返回 false/0），反映私有对齐器的实际设置。
- 只有给出任一开关时，在 ready 行之后写一行 `COREAPPTRACE version=1 event=voice_aligner sinc=0|1 crossfade=N`，数值取自上述查询；不给开关时 trace 逐字节不变。

## TDD

1. `test_core_app_voice`：查询的 NULL 与默认值；启用后的值。
2. `test_core_app_voice_lane.cmake`：`--voice=fake --voice-aligner-sinc --voice-aligner-crossfade 480` 运行成功、写出 `event=voice_aligner sinc=1 crossfade=480`、仍产出全部包且两次运行一致；不带开关无该行；五个错误组合退出 2 且为 CLI 诊断。
3. RED → 实现 → GREEN；变异：不写入配置、查询返回常量、缺少依赖校验。
4. 完整 Vulkan/OpenGL，ASan+UBSan/TSan 下两个目标；更新 `core_app_integration.md`、`audio_extended.md`、状态与缺口文档；评审后推送并核验远端。
