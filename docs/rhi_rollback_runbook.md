# RHI 回滚 Runbook（rollback / device-loss / present-failure）

适用范围：多后端 RHI（Vulkan / Metal / D3D12）+ OpenGL。

**默认后端（维护者决定，2026-10-26）：Linux / Windows 默认 Vulkan。** `ENGINE_RHI_BACKEND=auto` 在配置期探测 Vulkan 加载器/头文件 + shaderc：齐全则选 Vulkan，缺失则带 `falling back to OpenGL` 警告降级到 OpenGL；契约测试 `test_rhi_backend_selection` 钉住这条规则。

**运行时降级（2026-10-26 交付）：** 默认 `auto` 构建同时链接 Vulkan 与 OpenGL，设备创建时先试 Vulkan，失败则在同一窗口改用 OpenGL，并记录 `RHIEVT fallback` 与 `backend_selected`。只在设备创建失败时降级；运行中的 device lost 不会切换后端。运行时开关：`BREAK_RHI_BACKEND=opengl|vulkan`（限定后端）、`BREAK_RHI_NO_FALLBACK=1`（禁止降级）、`BREAK_RHI_FAIL_VULKAN=1`（测试钩子，强制 Vulkan 创建失败）。契约见 `docs/design/rhi_runtime_backend.md`。

**OpenGL 策略（维护者决定，2026-10-26）：长期保留，不计划移除。** 它是 `fallback_chain` 的**最后一级**降级方案（Windows/Linux/steam-linux），同时是跨后端渲染效果对比的参考基准（`test_rhi_golden_parity`：VK golden ≈ sRGB(GL golden) 的垂直镜像）。原 "v2.0.0 删除 OpenGL" 计划作废。
日志入口：运行时结构化行 `RHIEVT {...}`（event ∈ backend_selected/fallback/device_lost/present_failure/shader_failure）。

## 1. 开关治理表

| 开关 | 类型 | owner | expiry | rollback 步骤 |
|---|---|---|---|---|
| `ENGINE_RHI_BACKEND`（CMake cache：auto/opengl/vulkan/metal/d3d12） | 构建期 | @konyka | 长期（无计划到期；每个 minor release 复审一次） | 重新 configure：`-DENGINE_RHI_BACKEND=<上一后端>`，重跑 headless 套件与对应 runtime lane |
| `engine/assets/rhi_backend_rollout.json`（allowed/fallback_chain/config_version） | 发布配置 | @konyka | 每个 minor release 复审一次 | `git revert` 配置 commit → bump `config_version` → 重发；运行时不读远端，配置随二进制固化 |
| `BREAK_RHI_BACKEND` / `BREAK_RHI_NO_FALLBACK`（运行时环境变量，仅多后端构建） | 运行期 | @konyka | 长期（每个 minor release 复审一次） | 取消该环境变量即恢复默认链 vulkan → opengl；`BREAK_RHI_BACKEND=opengl` 可直接改用 OpenGL，无需重建 |
| OpenGL 最后降级 / 对比基准（`reason=compat-override` 路径） | 降级开关 | @konyka | 长期（无计划到期；每个 minor release 复审一次） | 引导用户设 `ENGINE_RHI_BACKEND=opengl`（或旧开关 `-DENGINE_VULKAN=OFF`）重建；同一源码树即可，无需回退版本 |

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

## 4. 版本回滚

1. 每个 release 打签名 tag（Task 9）：`git tag -s v<x.y.z>`；旧 major 长期保留。
2. 回退命令：`git checkout v<x.y.z> && cmake -S engine -B build -DENGINE_RHI_BACKEND=<上一后端> ...`。OpenGL 仍在当前树内，选 `opengl` 无需回到旧 tag。
3. CI 演练：`.github/workflows/rollback-drill.yml`（workflow_dispatch 手动触发），输入上一 tag，验证其 clean checkout 可构建且 headless 套件绿。每 release 前必跑一次。

## 5. 签名与完整性

- rollout 配置当前为 `sha256-payload` 完整性哈希（非真实性签名）；`ed25519-sha256` 随发布签名密钥启用。
- release tag 使用 maintainer GPG key 签名；发布包附 `SHA256SUMS`。

### §5.1 semver 规则（Task 9，2026-10-17）

- **major = 破坏性变更**（公共 API / 配置 schema / 平台支持面的不兼容变化）。OpenGL 已决定长期保留，不再占用任何 major 版号。
- **minor = 新后端/新能力**；**patch = 修复**。
- **版本唯一来源** = `engine/CMakeLists.txt` 的 `project(PureCEngine VERSION x.y.z)`（当前 1.9.0）；tag 名 `v<x.y.z>` 必须与之严格相等，由契约测试 `test_release_package_contract` 比对（HEAD 无 tag 时跳过）。
- **tag 由 maintainer 在发布时创建**（`git tag -s`），不随开发 commit 自动打；验签（`git tag -v`）与 clean checkout 构建演练由 `rollback-drill.yml` 承担（§4.3）。
- 离线发布包：`engine/tools/package_release.sh <repo> <build> <out> <version>`（tarball + `MANIFEST` + `SHA256SUMS` + tarball.sha256；缺失平台产物 = UNAVAILABLE，MANIFEST 如实反映）。
