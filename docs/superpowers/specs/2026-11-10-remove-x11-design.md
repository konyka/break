# X11 完全移除设计

日期：2026-11-10

## 目标与背景

当前主开发环境是 Fedora 原生 Wayland，X11 只能通过 XWayland 兼容运行。长期修补 X11 窗口几何推断不能证明不同窗口管理器下的事件所有权，继续保留该后端会消耗后续 Cry 对照能力集成的验证成本。用户已明确要求完全移除 X11 代码、功能与专属测试，验证通过后直接推送远程主分支，再继续集成任务。

本设计采用完全移除，不设置弃用期，不保留 X11 兼容实现。原生 Wayland 是 Linux 唯一窗口系统；Vulkan 仍是默认 RHI，OpenGL 仍是最后降级与画面对照后端。

## 方案比较

1. **完全移除（选定）**：删除 X11 生产实现、依赖、专属测试和 CI 启动路径，把通用测试迁移到 Wayland。优点是只有一套 Linux 窗口语义，不再维护无法普遍证明的几何启发式；代价是破坏性版本升级，旧配置与旧回滚版本不再受当前树支持。
2. **标记 DEPRECATED，保留一个主版本**：迁移较平滑，但仍需维护 X11 源码、测试与故障路径，不符合完全移除要求。
3. **只从 CI/默认路径禁用**：短期改动较小，但源码和隐含依赖仍存在，不能满足删除功能的要求，也会留下未测试代码。

## 范围

### 删除

- 引擎 X11 窗口、XI2 输入、Xlib Vulkan surface 与 GLX 实现：`window_x11.c`、`x11_touch.c/.h`、`rhi_gl.c` 中 GLX 路径、`platform_vk_surface*` 中 Xlib 分支。
- myui X11 PAL 和独立 XCB/GLX 示例；explorer 的 X11/XImage/EGL-X11 runner。
- `PLATFORM_WSI_BACKEND_X11`、`platform_size_x11()` 及只属于 X11 的公共声明、结构、常量和平台映射。
- CMake 的 X11/Xrandr/XI 探测、链接、include、源文件与 `MYUI_PAL=x11` 支持。
- X11 专属测试、Xvfb/XTest/xdpyinfo 启动与断言、CI 中的 X11 执行路径和镜像里的直接 X11 开发包。
- GLAD 中实际用于 GLX 动态加载的路径；通用 OpenGL loader、EGL/WGL 和 `GL_SYNC_X11_FENCE_EXT` 这类不要求 X11 窗口系统的扩展常量不属于窗口后端，不做无关生成代码重写。

### 迁移而非丢失覆盖

- 将只依赖公共 Platform/RHI API 的 `test_rhi_x11_runtime.c` 改为原生 Wayland runtime 测试，保留 EGL damage frame、F16 cubemap 等真实行为。
- 删除 world/mesh GPU 测试中的 X11 显示探针，使用公共平台创建结果与真实 compositor；不得因此把图形断言改成 record/headless。
- 将当前 X11 的 OpenGL、Vulkan/lavapipe、validation、benchmark CI 执行迁移到 Weston/Wayland，并验证不是全部以 77 跳过。
- 缩减跨平台 WSI/size/ABI 合同中的 X11 正向要求，增加 X11 不得回潮的负向配置与依赖扫描。
- 为 Wayland 补共享窗口尺寸语义的直接回归，避免只删除 X11 专属用例而降低公共覆盖。

### 保留

- Wayland 的全部协议、生成代码、输入、窗口、touch、EGL/Vulkan surface 与测试。
- Win32、Cocoa、Android、iOS、QNX 的公共实现和合同；公共枚举中其余成员的数值保持稳定。
- OpenGL/EGL/WGL、Vulkan、headless CPU 测试、myui dummy PAL。dummy/record 不能冒充 Linux 原生窗口或 GPU 证据。
- Linux evdev、fontconfig、通用 EDID parser、通用键码数值与其他被多平台共享的代码。仅把过时的“X11 键码”等注释改为平台中立描述。
- 历史文档中的 X11 事实、故障与 CI 链接。新增移除记录，不改写过去发生的验证。

## Linux 配置与运行行为

- Linux 构建始终使用原生 Wayland。缺少 Wayland/scanner/EGL/xkbcommon 等必需开发依赖时 configure 明确失败，不回退 X11，不静默改为 dummy。
- `ENGINE_ENABLE_WAYLAND=OFF` 在 Linux 上产生迁移诊断并失败；旧 build cache 不会被重新解释成另一个后端。
- `MYUI_PAL=x11` 产生同样的移除诊断并失败。`MYUI_PAL=wayland` 与独立的 `dummy` 继续有效。
- 没有 compositor 时，普通引擎应用明确报告显示初始化失败；只有本来就允许环境缺证的 runtime 测试可以返回 77，并由 CI 区分执行与跳过。
- RHI 选择不变：auto 优先 Vulkan，创建失败后最后尝试 OpenGL。显式 Vulkan 禁止 fallback；显式 OpenGL 用于对照。

## 公共接口与版本

删除公共 X11 API 和配置属于破坏性变更，项目主版本升级到 2.0.0；不创建未经用户要求的发布 tag。其余 WSI 枚举成员使用显式数值，避免连带 ABI 变化。

负向迁移测试可以保留 `x11` 字符串，用于证明旧配置被拒绝、源码不再包含 X11 头和链接库；这些字符串不是兼容实现。当前文档统一说明“X11 已移除”，历史文档继续保留原始证据。

## CI、镜像与回滚

- 当前 Linux 收据改为 `linux-wayland`；native-surface 与真实 GPU runtime 证据继续分栏。
- CI 镜像删除直接 X11 开发包和 Xvfb 工具，保留 Mesa 可能带来的系统传递依赖，不将系统包依赖图误写成项目源码支持。
- Steam Runtime/Proton 环境若缺 Wayland 工具链，必须明确记录 UNAVAILABLE 或补齐环境；不得静默退回 X11，也不得把跳过写成通过。
- 回滚演练只接受包含本移除的版本。早于 2.0.0 的历史 tag 不再由当前回滚工作流支持，不为其保留 X11 安装脚本。没有合格 tag 时显示 UNAVAILABLE，不虚构回滚成功。
- 推送后核查主 CI、镜像重建、Windows D3D12 及其他原生通道。新镜像未发布前，不能把旧镜像结果当作无 X11 依赖的证明。

## 文档

更新 README、Build Guide、Architecture Overview、Engine Modules、myui 当前集成/图表说明、Vulkan 支持矩阵、RHI 证据与 benchmark 收据说明、输入设计、跨引擎现状。`docs/Implementation_Status.md` 顶部追加实际移除内容、命令、结果、CI 和限制；旧记录不删除。

本移除不批量重命名无关的现有引擎模块。后续 Cry 对照集成遵循用户最新命名要求：不使用 `cry/Cry/CRY` 前缀，也不机械替换为 `break/Break/BREAK`，按现有领域命名与 Google 一致的文件、类型、函数、变量和常量规则另行迁移 P12。

## 验证与完成定义

1. 在同步最新 `origin/master` 后，使用全新构建目录完成 Wayland auto 与显式 OpenGL 全量构建；普通非图形测试全部通过。
2. 原生 Wayland 下运行窗口/输入与真实 Vulkan、OpenGL 图形测试，读取并查看图像；实际 backend、device 和非 skip 证据分别记录。
3. ASan+UBSan、TSan 全量非图形通过且无报告；显式构建全部 fuzz 目标并通过。
4. `ENGINE_ENABLE_WAYLAND=OFF` 与 `MYUI_PAL=x11` 明确配置失败；源码、compile commands 和链接行无 X11 实现、头或项目库依赖。
5. Win32/Cocoa/Android/iOS 的合同与可用交叉编译通道通过；无法本地运行的平台以推送后的原生 CI 为准，不虚报实机验证。
6. 独立规格与质量评审无未解决 Critical/Important；`git diff --check` 通过，文档与实现一致。
7. 处理远程分叉后直接推送 `origin/master`，不创建 PR；检查 CI 并修复由本次移除引起的失败。完成此次推送后恢复暂停的 P12 Task 2。

若真实图形或特定外部运行环境不可用，必须列为 UNAVAILABLE；record、headless、null 与旧 X11 结果不能顶替。未完成的 P12 工作不得包含在本次移除推送中。
