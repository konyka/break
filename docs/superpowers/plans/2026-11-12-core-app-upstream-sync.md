# Core App Upstream Synchronization Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 将远程 `327bd6fd` 的 `_spawnv`、文本 LF 和 WGL/Python 修复与当前诊断、checkout 合同及 D3D12 compat 修复合并，保留双方有效行为且不留冲突或矛盾证据。

**Architecture:** 以远程直接进程启动替代 Windows shell 转发，保留现有 slot/raw-return 诊断；POSIX `system()` 不变。七个文本资产采用远程 `text eol=lf`，四个二进制资产采用显式 `binary`，checkout 合同按文件类别断言。compat 的 generator/config 与真实 Agility 暂存保持不动。先解决冲突，再在合并结果上重新验证。

**Tech Stack:** C11、Win32 `_spawnv`、POSIX `system()`、Git attributes、CMake/CTest、MSVC/MinGW/Clang、真实 baker 与 D3D12 Agility SDK。

## Global Constraints

- 工作树 `/home/timeshift/opensource/break/.worktrees/core-app-ci`，当前正在合并 `origin/master`（`327bd6fd`）。`docs/Implementation_Status.md` 与 `engine/tests/test_core_app_assets.c` 有真实内容冲突，不能重置、checkout 任一方或 force-push。
- 保留远程 `test_glad_wgl_loader.c`、`test_ci_image_fix2.py`、`docs/Build_Guide.md` 的修复，不能为了简化冲突而回退。
- Windows 使用 `_spawnv(_P_WAIT)` 直接启动真实 baker，参数按 CRT 规则引用；保留 A/B slot、`launch.command` 和 `launch.spawnv` 原始返回诊断。POSIX 保持原 `system()` 和 `launch.system`。不得改成无引号参数或删除空格路径回归。
- 七个文本资产使用 `text eol=lf`，`level.banm`、`level.bscn`、`level.fg`、`tone.wav` 使用 `binary`。不得以 generic binary 覆盖远程文本规则，也不得归一化比较来掩盖字节差异。
- compat Task 1 的 generator/config 与 Task 2 的真实 Agility 文件、哈希和 gate 删除/恢复不得改变。临时 process probe/validation 分支不进入 master，不建 PR。
- 新名称使用 `core_app`/`CoreApp`/`CORE_APP` 和现有 C/CMake 风格，不引入旧外部引擎前缀或新 `application` 领域名。Vulkan 默认，OpenGL 只作最后降级/画面对照，不引入 X11。
- 所有构建和并行 CTest 使用 `-j3`。每项先 RED、最小 GREEN、变异/恢复、完整非图形回归、独立规格与质量评审。最终必须重跑 ASan+UBSan、TSan、no-tests、显式 fuzz 和真实 Windows/D3D12，不能沿用合并前结果。
- 历史记录只补充当前事实。合并前的外层引用 probe 和 generic binary 方案可保留为历史，但必须明确最终同步采用 `_spawnv` 和分类属性规则，不得写成两套同时生效的实现。

---

### Task 1: 合并直接启动、分类属性与当前证据

**Files:**
- Modify: `engine/tests/test_core_app_assets.c`
- Modify: `engine/tests/test_core_app_baker_diagnostics.cmake`
- Modify: `.gitattributes`
- Modify: `engine/tests/test_core_app_checkout_attributes.cmake`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/core_app_integration.md`（原生验收后追加）
- Report: `.superpowers/sdd/2026-11-12-core-app-upstream-sync/task-1-report.md`

**Interfaces:**
- Windows: `run_baker(output, slot)` 使用 `_spawnv(_P_WAIT, CORE_APP_ASSET_BAKE_EXECUTABLE, argv)`，argv 为带 CRT 引号的 executable/output 参数和 `--output`，保留 `launch.command`/`launch.spawnv`。
- POSIX: `run_baker(output, slot)` 使用原 `system(command)` 和 `launch.system`。
- Checkout: 文本断言 `text: set` 与 `eol: lf`；二进制断言 `binary: set` 且无 `text: set`；11 个路径逐一验证，不以 generic binary 覆盖文本规则。
- Preserves: 原始返回、A/B 短路、长度检查、诊断、11 资产逐字节比较、空格输出目录、无 Git/损坏元数据边界及 compat 的 SDK gate。

- [ ] **Step 1: 固定冲突 RED 与测试合同**

保留当前冲突证据：远程 `run_baker(output)` 使用 `_spawnv`，当前 `run_baker(output, slot)` 使用完整命令外层引用；`.gitattributes` 同时含远程文本规则与 generic binary；两份状态文档开头不同。

先把 `test_core_app_baker_diagnostics.cmake` 改为要求 Windows `_spawnv`、CRT 引用参数与 `launch.spawnv`，POSIX 仍为 `system()`/`launch.system`，保留真实启动成功、缺失 baker、空格 TEMP、返回码和短路断言。旧 Windows 外层引用合同在合并后的设计中不再成立，但删除它的原因必须是直接启动消除了 shell 依赖，而不是降低验证。

先把 `test_core_app_checkout_attributes.cmake` 改为要求这些独立行并实际运行 `git check-attr -a`：

```gitattributes
engine/assets/core_app/*.lua text eol=lf
engine/assets/core_app/*.scenario text eol=lf
engine/assets/core_app/actors.sidecar text eol=lf
engine/assets/core_app/level.banm binary
engine/assets/core_app/level.bscn binary
engine/assets/core_app/level.fg binary
engine/assets/core_app/tone.wav binary
```

文本文件要求 `text: set` 和 `eol: lf`，不得有 `binary: set`；四个二进制文件要求 `binary: set` 且无 `text: set`。缺少分类规则、generic binary 覆盖或 eol 不符必须 RED。保留空 Git/真实 archive UNVERIFIED、损坏目录或悬空 `.git` FAIL。

- [ ] **Step 2: 解决启动与属性冲突**

Windows `run_baker` 按远程 `_spawnv` 实现，保留 `slot`、命令缓冲区和长度失败诊断。executable_arg/output_arg 各自按 CRT 规则引用，失败时报告 `launch.command`；`_spawnv` 返回后立即保存 OS/CRT 错误并以 `launch.spawnv` 报告原始返回值。不得先调用 `system()` 或丢弃 slot。

POSIX 保持原单层命令格式和 `launch.system`。`baker_supports_spaces_in_output_path` 保留，并以 `prepare_asset_directory(..., "space")`、`run_baker(..., "space")`、`clear_directory(..., "space")` 兼容诊断签名。保留远程 WGL 和 Python UTF-8 修改。

`.gitattributes` 使用上述七个精确规则，删除 generic `engine/assets/core_app/* binary`。注释说明 baker 的字节确定性、文本 LF 与二进制不可规范化。保留 `This section is scoped to shaders only.` 和 PPM 规则。

- [ ] **Step 3: 文档、变异与完整回归**

解决 `docs/Implementation_Status.md` 开头冲突：保留远程 `_spawnv`/文本 LF/WGL/Python 记录和本分支诊断记录，将本分支的外层引用与 generic binary 明确标为合并前历史方案；最终同步语义以本计划为准，原生验收后追加真实 run ID、数量与剩余限制，不反向改写历史。

执行 focused assets/diagnostics/checkout、WGL/Python、compat/config 与完整非图形 `-j3`。临时将 Windows `_spawnv` 改回 `system()` 或将一个文本规则改为 generic binary/eol=crlf，合同必须 RED；精确恢复后 GREEN。检查不存在冲突标记且 11 个资产哈希未变。

在最终合并提交上重新配置/构建并跑普通、ASan+UBSan、TSan、no-tests 和显式 fuzz，不能复用合并前的 ASan 结果。controller 在临时 validation 上验收真实 Windows `_spawnv`、空格 TEMP、16/16 或加入远程空格用例后的 17/17、checkout 属性、完整 compat 和 WARP；不得把合并前外层引用或 generic binary 的通过结果冒充合并结果。

- [ ] **Step 4: 独立评审、合并提交与文档**

独立规格与质量评审确认冲突完整解决、远程修复无回退、诊断和 SDK 语义一致、无简化覆盖或假绿。以现有 merge 提交完成：

```bash
git commit -m "merge: integrate upstream Core App fixes"
```

写完整 `task-1-report.md`，列出每个冲突的实际解决、RED/GREEN/变异、完整验证、run ID 与限制。controller 负责独立全分支终审、真实 CI、文档和最终 push；临时分支不合并到 master。
