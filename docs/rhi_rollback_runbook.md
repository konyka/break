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

### §5.1 semver 规则（Task 9，2026-10-17）

- **major = 破坏性变更**：本计划的 OpenGL 删除 = v1.x → **v2.0.0**，版号保留给删除 release（Task 6 闸门 BLOCKED；删除前最后一个 commit 才是 v1 末版位置，届时由 maintainer 在该 commit 上补打 v1 末版签名 tag）。
- **minor = 新后端/新能力**；**patch = 修复**。
- **版本唯一来源** = `engine/CMakeLists.txt` 的 `project(PureCEngine VERSION x.y.z)`（当前 1.9.0，兼容期）；tag 名 `v<x.y.z>` 必须与之严格相等，由契约测试 `test_release_package_contract` 比对（HEAD 无 tag 时跳过）。
- **tag 由 maintainer 在发布时创建**（`git tag -s`），不随开发 commit 自动打；验签（`git tag -v`）与 clean checkout 构建演练由 `rollback-drill.yml` 承担（§4.3）。
- 离线发布包：`engine/tools/package_release.sh <repo> <build> <out> <version>`（tarball + `MANIFEST` + `SHA256SUMS` + tarball.sha256；缺失平台产物 = UNAVAILABLE，MANIFEST 如实反映）。
