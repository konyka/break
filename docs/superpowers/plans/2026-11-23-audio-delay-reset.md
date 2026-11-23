# 延迟线与语音对齐器 reset 实施计划（2026-11-23）

## 背景

`docs/design/audio_extended.md`「语音参考自动对齐」列出未做项：reset（底层 delay line 尚无 reset）。调用者在设备重开、会话切换或流中断后只能销毁重建对象，重建需要重新分配。

## 契约

- `void audio_delay_line_reset(AudioDelayLine *line)`：NULL 为空操作；清零历史缓冲与写位置，取消进行中的交叉淡化；保留最大延迟、当前延迟、sinc 模式和交叉淡化帧数配置。不分配，之后的输出与以相同配置新建的延迟线逐样本一致。
- `void audio_voice_aligner_reset(AudioVoiceAligner *aligner)`：NULL 为空操作；重置 tracker（含估计器）与延迟线，应用延迟归零，`updates` 归零，更新倒计时恢复为完整周期；保留后端选择与配置。不分配，之后的行为与新建对齐器逐位一致。

## TDD 步骤

1. `test_audio_delay_estimator` 新增 `the_delay_line_reset_matches_a_fresh_line`：线性与 sinc 两种模式、带分数延迟和进行中的交叉淡化，reset 后与同配置新建线逐样本一致；配置查询保持；NULL 安全。
2. `test_audio_voice_aligner` 新增 `reset_matches_a_fresh_aligner`：时域与 GCC 两种后端，处理一个周期以上并锁定后 reset，`delay/updates/locked/rejections/correlation` 回到初值，随后的输出与新建对齐器在多个周期内逐位一致；NULL 安全。
3. 先确认 RED（缺少符号导致编译失败），再实现，确认 GREEN。
4. 完整 Vulkan/OpenGL 套件，ASan+UBSan 与 TSan 下两个目标；更新设计文档、Implementation_Status 与 missing_capabilities，推送 master 并核验远端。
