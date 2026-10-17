# RHI 回滚 Runbook（rollback / device-loss / present-failure）

适用范围：多后端 RHI（Vulkan / Metal / D3D12）+ 兼容期 OpenGL fallback。
日志入口：运行时结构化行 `RHIEVT {...}`（event ∈ backend_selected/fallback/device_lost/present_failure/shader_failure）。

## 1. 开关治理表

| 开关 | 类型 | owner | expiry | rollback 步骤 |
|---|---|---|---|---|
| `ENGINE_RHI_BACKEND`（CMake cache：auto/opengl/vulkan/metal/d3d12） | 构建期 | @konyka | OpenGL 删除 release（v2.0.0）发布 +30 天 | 重新 configure：`-DENGINE_RHI_BACKEND=<上一后端>`，重跑 headless 套件与对应 runtime lane |
| `engine/assets/rhi_backend_rollout.json`（allowed/fallback_chain/config_version） | 发布配置 | @konyka | 每个 minor release 复审一次 | `git revert` 配置 commit → bump `config_version` → 重发；运行时不读远端，配置随二进制固化 |
| 兼容期 OpenGL fallback（`reason=compat-override` 路径） | 兼容开关 | @konyka | v2.0.0（OpenGL 删除 release） | 删除前：引导用户设 `ENGINE_RHI_BACKEND=opengl` 重建；删除后：回滚到 v1.x tag（见 §4） |

治理规则：开关新增/变更必须更新本表（契约测试 `test_rhi_rollback_runbook_contract` 强制 owner/expiry/rollback 三列存在）；expiry 到期未处理的开关在下一个 release 评审中必须移除或续期。

## 2. Device loss 处置

1. 日志检索：`grep 'RHIEVT ' app.log | grep '"event":"device_lost"'`。
2. 确认是否已知坏境：NVIDIA 616.56 混合 GPU 的 DEVICE_LOST 不作源码修复依据（规格 §7），须在健康设备独立复现后立项。
3. 缓解：重启进程；若同机型批量出现，用 rollout 配置把该平台 fallback_chain 次位后端提前（发配置补丁 release）。
4. 根因修复后 bump `config_version` 并在台账记录收据。

## 3. Present failure 处置

1. `grep '"event":"present_failure"'` 按 `result` 分类：`OUT_OF_DATE` 多为 resize 竞态，`SURFACE_LOST` 多为 WSI 挂起/恢复路径。
2. 对照 frame 生命周期契约（规格 §4.3）确认 backend 自动重建 swapchain 是否失败；失败时 `lifecycle_result` 已 fail-fast，属预期。
3. 持续失败 → 按 §1 表回滚后端或回退版本。

## 4. 版本回滚（含 OpenGL 删除后的回退）

1. 每个 release 打签名 tag（Task 9）：`git tag -s v<x.y.z>`；旧 major（含 OpenGL 的最后版本 v1.x）长期保留。
2. 回退命令：`git checkout v1.x.y && cmake -S engine -B build -DENGINE_RHI_BACKEND=opengl ...`（删除后版本中 `opengl` 值已不存在，必须回到旧 tag）。
3. CI 演练：`.github/workflows/rollback-drill.yml`（workflow_dispatch 手动触发），输入上一 tag，验证其 clean checkout 可构建且 headless 套件绿。每 release 前必跑一次。

## 5. 签名与完整性

- rollout 配置当前为 `sha256-payload` 完整性哈希（非真实性签名）；`ed25519-sha256` 随发布签名密钥启用。
- release tag 使用 maintainer GPG key 签名；发布包附 `SHA256SUMS`。
