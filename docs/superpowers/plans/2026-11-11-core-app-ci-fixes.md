# Core App Cross-Platform CI Fixes Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 修复 Core App 合入后暴露的跨平台构建合同、配置与资产测试问题，并以真实 CI 证明所有受影响 lane 恢复。

**Architecture:** 先修独立于生成器的合同与 fixture，再处理 nested 配置传播；Windows baker 先以不改变行为的诊断确定唯一失败操作，随后按该操作写最小回归和修复。无 Git、旧 CMake 和无 SDK 环境都必须有明确证据等级，不能假 PASS。

**Tech Stack:** C11、CMake/CTest、Git archive、Win32/POSIX filesystem、macOS APFS、Vulkan/Metal、GitHub Actions。

## Global Constraints

- 工作树固定为 `/home/timeshift/opensource/break/.worktrees/core-app-ci`，实现代理串行、只读评审可并行。每项 scoped commit 与独立规格/质量评审，不建 PR，构建和并行 CTest 使用 `-j3`。
- 基线 `975606db` 的主 CI 与 D3D12 均失败，不能用先前全绿代替。每项先取得实际 RED，再最小实现 GREEN；没有 native 证据时明确写限制。
- 新名称遵循 `core_app`/`CoreApp`/`CORE_APP` 和现有 C/CMake 风格，不引入外部引擎前缀或旧应用领域名。
- 不得关闭 Vulkan、禁用警告、删除测试、无条件下调断言、临时 `git init` 伪装 tracking、伪造 SDK，或把 Linux/Zig 交叉编译当作 Windows/macOS native 结果。
- 保留现有 `core_app` API/ABI、序列化布局和 checkpoint writer 行为，除非真实证据要求修改；历史文档不改写。
- `UNVERIFIED` 只能用于环境能力缺失，真实合同失败、命名违规、nm 缺符号、nested configure 失败和 Git 执行/权限错误均不得转为 skip。
- 每项独立验收：真实进程/reader 行为、至少一个变异被杀死后恢复、全量非图形回归、独立规格与质量评审。CI 图形标签不得作为 GPU 证据。
- 最终交付前执行普通、ASan+UBSan、TSan、no-tests、显式 fuzz 和真实 Windows/macOS CI；Vulkan 默认，OpenGL 仅作最后降级/画面对照，X11 不引入。

---

### Task 1: 旧 CMake、无 Git 与命名转义合同

**Files:**
- Modify: `engine/CMakeLists.txt`、`engine/tests/test_core_app_target_contract.cmake`、`test_core_app_formal_assets.cmake`、`test_core_app_naming_contract.cmake`
- Create: `engine/tests/test_core_app_contract_compat.cmake`
- Report: `.superpowers/sdd/core-app-ci/task-1-report.md`

**Interfaces:**
- Produces: 精确 skip token `UNVERIFIED: core_app symbol scan skipped:` 与 `CORE_APP_TRACKING_UNVERIFIED`；无 Git 时仅 tracking 未验证，其它命名/reader 合同仍执行。
- Preserves: Git checkout 中真实 11-asset tracking PASS；真实错误仍 FAIL。

- [ ] **Step 1: 写兼容合同 RED**

用当前 HEAD archive 创建无 `.git` fixture，不初始化仓库。要求 formal tracking 明确 `CORE_APP_TRACKING_UNVERIFIED`；naming 先完成所有非 Git 检查，再只为 tracking 报告未验证。向 fixture 植入独立命名违规必须仍失败。真实 Git checkout 必须比较 11 个文件并 PASS。

```cmake
set_tests_properties(test_core_app_nm_missing test_core_app_nm_unsupported
    test_core_app_formal_asset_tracking test_core_app_naming_contract
    PROPERTIES
        SKIP_RETURN_CODE 77
        SKIP_REGULAR_EXPRESSION "UNVERIFIED: core_app symbol scan skipped:|CORE_APP_TRACKING_UNVERIFIED")
```

为 naming 的精确 worktree/branch 豁免使用 bracket argument，保留独立 `cry` 拒绝：

```cmake
string(REPLACE [=[`cry-integration`]=] "" text "${text}")
# `cry-integration2` 不得被移除，仍必须命中 forbidden token。
```

直接运行新合同，预期旧实现因无 `.git`、缺失 skip 正则和 `\`` 转义而 RED。记录本地 CMake 版本，3.28 行为由 clean-room native 最终确认。

- [ ] **Step 2: 实现最小兼容修复**

为 nm 的两个负路径添加字面量 `SKIP_REGULAR_EXPRESSION "UNVERIFIED: core_app symbol scan skipped:"`，保留 77 与 `contract_skip()` 在已有合同错误时先失败的逻辑。

无 Git 时只在确认仓库元数据不存在后进入 `CORE_APP_TRACKING_UNVERIFIED`。formal tracking 可跳过；naming 只在所有非 Git 检查通过后为 tracking 跳过，不能打印完整合同 PASS。Git 执行/权限错误、列表不匹配继续 FAIL。两个测试都配置上述 token 与 77。

- [ ] **Step 3: GREEN、变异与回归**

运行无 Git archive、真实 Git、额外/缺失资产、独立命名违规、`cry-integration2`、旧/new CMake focused。普通非图形 `-j3` 全量不得回归。验证缺 nm 的 nested configure/CLI 错误不会借用 skip。

- [ ] **Step 4: 独立评审并提交**

确认没有把 tracking 或真实命名违规变成 skip。提交 `test: make core app contracts portable`。

### Task 2: nested Vulkan/Metal 配置与假绿防线

**Files:**
- Modify: `engine/CMakeLists.txt`、`engine/tests/test_core_app_target_contract.cmake`、`test_core_app_nm_symbol_missing.cmake`
- Create: `engine/tests/test_core_app_nested_contract.cmake`
- Report: `.superpowers/sdd/core-app-ci/task-2-report.md`

**Interfaces:**
- Produces: `NESTED_ENGINE_RHI_BACKEND` 与非空真实 `Vulkan_LIBRARY`、`Vulkan_INCLUDE_DIR`、`SHADERC_LIB`、`SHADERC_INCLUDE_DIR` 传递列表；父 Metal 子 Metal，父 Vulkan 子 Vulkan，auto 保持既有选择语义。
- Preserves: 无 Vulkan 的 Metal 不引入新 SDK 依赖，真实 nm 缺符号仍是非 77 的 FAIL。

- [ ] **Step 1: 写 nested RED**

建立两个独立嵌套配置：Metal 父配置没有 Vulkan SDK，子配置必须仍选 Metal 并成功；另一配置逐项比较四个真实路径，不允许重新发现其它 SDK。使用独立 build root 证明没有读取旧 cache。

向 `test_core_app_nm_symbol_missing.cmake` 注入 nested configure failure 和缺符号文本，必须 RED；不能因为缺符号诊断存在就 PASS。

- [ ] **Step 2: 实现两跳传递**

仿照 `_rhi_selector_toolchain_defs`，在父 `add_test` 参数与脚本 `execute_process` 间传递非空真实变量及有效后端。禁止硬编码 auto 使 Metal 子配置错误地转向 Vulkan。`nm_symbol_missing` 的包装脚本也必须转发同一组定义。

明确拒绝 `no-tests target/scope configure failed`，只有真实 nm 输出缺 `core_app_run` 且其它合同成功时，wrapped 负例才算通过。

- [ ] **Step 3: GREEN、变异与回归**

运行全部 target/nm focused 和普通非图形。临时删除一个路径传递或恢复 auto，必须在对应配置 RED；恢复后 GREEN。不能用占位 SDK 或关闭 Vulkan 通过测试。

- [ ] **Step 4: 独立评审并提交**

检查无 SDK Metal 路径、真实 Vulkan 路径、wrapper 二次嵌套和假绿防线。提交 `test: preserve core app nested toolchain configuration`。

### Task 3: macOS reserved-alias 夹具

**Files:**
- Modify: `engine/tests/test_core_app_assets.c`
- Report: `.superpowers/sdd/core-app-ci/task-3-report.md`

**Interfaces:**
- Preserves: checkpoint writer 不修改；reserved alias 仍返回 `BREAK_RUNTIME_INVALID`，旧 manifest 完整不变，probe 成功，原 payload 存在。

- [ ] **Step 1: 固定 fixture 破坏顺序**

保留 native macOS RED 作为证据：`MANIFEST.CORE` 在 case-insensitive APFS 上就是 `manifest.core`，测试在 writer 调用前用 `"wb"` 把它截成 4 字节。先在本地合同中断言 reserved-alias 测试不得在调用 writer 前写入任何 alias payload，旧 fixture 因包含预写而 RED。

- [ ] **Step 2: 只修测试夹具**

删除 reserved alias 的预写分支，不添加 macOS 特判。writer 仍收到 alias，并在 payload probe 前按既有名称校验拒绝。保留调用前 hash，增加完整 manifest 字节比较；原 probe、`runtime_1.bin` 和 INVALID 断言不削弱。

- [ ] **Step 3: GREEN 与 native 限制**

Linux/Windows 回归用于证明无回归，但不作为 case-insensitive 修复证据；macOS native 必须原样重跑该项和全部 assets。临时恢复预写应在 APFS 再次 RED，删除后恢复 GREEN。

- [ ] **Step 4: 独立评审并提交**

确认没有修改 writer、没有移动 hash、没有跳过 macOS 测试。提交 `test: preserve manifest across reserved aliases`。

### Task 4: Windows baker 分阶段诊断（不是修复完成）

**Files:**
- Modify: `engine/apps/core_app/core_app_asset_bake.c`、`engine/tests/test_core_app_assets.c`
- Modify only when required for real OS errors: `engine/src/platform/platform_fs.c`
- Create: `engine/tests/test_core_app_baker_diagnostics.cmake`
- Report: `.superpowers/sdd/core-app-ci/task-4-report.md`

**Interfaces:**
- Produces: `FAIL: CORE_APP_BAKE` 与 `FAIL: CORE_APP_TEST` 的阶段、步骤、路径、原始返回值和真实 OS 错误；成功/失败返回行为不变。
- Does not produce: Windows 修复结论。诊断提交不得宣称 baker 已通过或 CI 已恢复。

- [ ] **Step 1: 先写诊断 RED 合同**

要求输出目录准备、进程启动、scene.save、scene.commit(probe/file_size/malloc/fopen/read/close/atomic/remove) 都有唯一步骤。默认只报 `asset generation failed` 的实现必须 RED。

- [ ] **Step 2: 实现不改变行为的诊断**

保留 baker 短路顺序和所有返回值。`prepare_directory` 输出 step/path/errno；`run_baker` 输出 A/B、路径、原始 `system()` 状态。scene.save 失败与 commit 子步骤分开，输出 temporary/final path、got/expected/extra/ferror/errno。

Win32 在失败 API 后立即保存 `GetLastError()`，覆盖 CreateFileA/WriteFile/FlushFileBuffers/CloseHandle/MoveFileExA；CRT 保存 `errno`/`ferror`。POSIX 对应保存 mkstemp/write/fsync/close/rename/open(dir)/fsync(dir)/unlink 的 errno。清理不得覆盖原始错误。错误前缀必须为 `FAIL:`，使现有 CI 筛选可见。

- [ ] **Step 3: 验证诊断本身并取真实证据**

用不可创建的输出父目录等受控失败验证诊断可达、阶段准确、返回码不变。正常 POSIX baker 不回归。推送诊断后，在 Windows 直接运行 baker 与 assets，记录第一条失败步骤、真实 OS 错误、目录 entry/size/临时残留；不得修改 scene、Flow、anim、WAV、Lua 或 PAL 来猜测根因。

- [ ] **Step 4: 独立评审并提交**

评审只确认诊断真实、无行为变化、无过度声称。提交 `test: diagnose core app baker stages`。随后按真实错误建立下一项独立修复计划和回归，不得把本任务当作 Windows 已修复。

### Final Integration Gate

- 真实 Windows 修复完成后，重跑普通/ASan+UBSan/TSan/no-tests/显式 fuzz 与全部受影响 CI；保存最终 run ID、lane 结果和剩余限制。
- 更新 `docs/Implementation_Status.md` 与 `docs/design/core_app_integration.md` 的当前证据，不改写历史。独立全分支评审、merged-result 测试和 `git diff --check` 全部通过后，才直接 push master。
