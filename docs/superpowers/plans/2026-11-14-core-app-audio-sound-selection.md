# Core App 音频：按事件选择声音资源（2026-11-14）

## 目标

现在所有 `PLAY_3D` 都播放 `tone.wav`。改为由事件决定声音资源：

- 追踪者声源（第一次 Area enter 起播，每 tick 跟随，卸载时停止）：`tone.wav`，sound 名 `chaser`。
- 物品拾取（背包数量增加的那一 tick）：在用户位置播放一次 `chime.wav`，sound 名 `item`。

两个声源同时属于一个关卡，互不挤占槽位。

## 设计

- `CoreAppAudioSound`：`NONE=0`（LISTENER）、`CHASER=1`、`ITEM=2`。`CoreAppAudioCommand` 新增 `sound`，`CoreAppAudioSlot` 新增 `sound`。
- 新接口 `core_app_audio_enqueue_sound(audio, kind, generation, sound, position)`。`enqueue`/`enqueue_at` 保持原签名：LISTENER 用 `NONE`，其余用 `CHASER`。LISTENER 带非 NONE 的 sound、或 PLAY_3D/POSITION/STOP 带 NONE 或未知 sound，返回 INVALID。
- 槽位按 `(generation, sound)` 认领和查找；`sound_slot_matches` 同时核对 generation 与 sound。
- 设备模式按 sound 选路径（`sound_paths[]`，由 asset_root 拼出）；新增 `device_plays_by_sound`，停机行在 `owner_thread=` 前加 `item_plays=N`。
- trace 行变为 `... source=%u sound=%s\n`（`none|chaser|item`）。
- 应用：背包数量增加时入队 `PLAY_3D sound=item`（用户位置），并记 `item_sound_live`。卸载/切关时对仍在播的每个声源各入队一个 STOP，再按入队条数 drain。
- 资产：baker 生成 `chime.wav`（44100 Hz、mono、PCM16、2205 样本、周期 40 样本的方波），正式资产 11 个变为 12 个。`.gitattributes` 加 `binary`，`.gitignore` 加例外。

## 步骤

1. [ ] RED：`test_core_app_runtime` 新增
   - `audio_sound_selection_keeps_two_sources_per_level`（record：CHASER 与 ITEM 各占一槽，trace 带 sound）；
   - `audio_enqueue_sound_rejects_mismatched_sound`；
   - `audio_device_plays_the_sound_chosen_by_the_event`（FAKE 系统，两个句柄不同、`item_plays=1`）。
   既有 trace 断言改为带 `sound=`。
2. [ ] RED：`test_core_app_assets` 新增 `chime_wav_is_canonical_44100_hz_mono_pcm16`，资产清单加 `chime.wav`；formal/checkout/naming/baker_diagnostics/compat 契约改为 12 个。
3. [ ] RED：`test_core_app_lifecycle` script_walk 断言 tick 61 有 `play_3d ... source=2 sound=item`；设备用例场景改为不在拾取前卸载，要求 `item_plays=1`。
4. [ ] GREEN：实现音频、应用、baker；重新烘焙正式资产。
5. [ ] 变异：ITEM 用 tone 路径、槽位只按 generation 认领、拾取不入队，三处都应变红。
6. [ ] 全量 normal 树、设备用例（真实 PulseAudio）、TSan runtime。
7. [ ] 文档：`docs/design/core_app_integration.md` 追加 slice 6 节，`docs/Implementation_Status.md` 顶部新增条目。
8. [ ] 提交、archive 契约、推送、CI。

## 不做

听感验证；声音资源表的数据驱动（映射在代码里固定）；record/null 模式的 owner 线程。
