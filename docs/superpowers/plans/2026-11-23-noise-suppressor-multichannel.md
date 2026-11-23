# 频谱降噪多声道接口实施计划（2026-11-23）

## 背景

`docs/design/audio_extended.md`「频谱降噪」未做项包含多声道。`AudioNoiseSuppressor` 只处理单声道；立体声采集或多声道素材只能由调用者自己拆分声道、各建一个实例、再交织回去。

## 方案选择

- **A. 每声道独立状态（采用）**：每个声道一套噪声底与增益，等价于 N 个单声道实例。实现最小，延迟与单声道相同，结果可以和独立单声道实例逐位比较。缺点是声道间的噪声估计不共享，空间像可能因各声道增益不同而轻微漂移。
- B. 共享噪声底与增益：所有声道用同一组每频点增益，保留声道间的相对电平。需要新的跨声道功率汇总规则，没有现成参照可逐位验证，留待有真实素材时再评估。

## 契约

- 单声道 `AudioNoiseSuppressor` 不变。新增独立类型 `AudioNoiseSuppressorBank`（`engine/src/audio/audio_noise_suppressor.h`），持有 `channels` 个单声道实例与一个所有声道共用的 256 帧去交织暂存区；不给现有结构加模式标志，单声道路径零改动。
- `audio_noise_suppressor_bank_create(config, channels, out)`：`channels` 为 1..8；配置校验与单声道相同；失败不写 `*out` 并释放已建实例。
- `audio_noise_suppressor_bank_process_interleaved_i16(bank, samples, frames)` 原地处理交织 PCM，`frames` 为每声道帧数；NULL bank 为空操作，NULL samples 只在 frames 为 0 时接受。
- `audio_noise_suppressor_bank_channels`、`_latency_frames`（与单声道相同的 frame_size，NULL 为 0）、`_reset`、`_destroy`。
- 每个声道与对同一声道单独运行的单声道实例逐位一致；任意分块与整块逐位一致；只有 create 分配。

## TDD

1. `test_audio_noise_suppressor`：声道数与配置校验且 `*out` 不变；立体声与 3 声道各自等于独立单声道实例；任意分块一致；reset 与新建一致；1 声道 bank 等于单声道实例；NULL 安全。
2. RED → 实现 → GREEN；变异：声道交错索引错位、共享状态、分块边界、reset 漏声道。
3. 完整 Vulkan/OpenGL，ASan/TSan（项目选项）下目标测试；更新设计、状态与缺口文档；评审后推送并核验远端。
