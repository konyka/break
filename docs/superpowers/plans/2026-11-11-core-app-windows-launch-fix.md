# Core App Windows Process Launch Fix Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 让 Windows `test_core_app_assets` 通过真实 `system()` 启动 baker 并完成 A/B 资产比较，同时保持 POSIX 命令和失败语义不变。

**Architecture:** 原生探针已经证明 `cmd /c` 需要给完整命令额外包一层引号，而仅给 exe/输出路径分别引用会在解释器阶段失败。只在 `_WIN32` 的测试启动命令外加一层引号；POSIX 保持原格式。既有真实资产测试是行为回归，诊断合同增加成功启动断言，不把临时 process probe 合入正式分支。

**Tech Stack:** C11、C `system()`、Windows `cmd /c`、MSVC/MinGW/Clang、CMake/CTest、真实 baker 与文件比较。

## Global Constraints

- 正式工作树 `/home/timeshift/opensource/break/.worktrees/core-app-ci`，分支 `core-app-ci`，基线 `c666c88a`。不建 PR，不合并临时 validation/APFS/probe 分支；controller 负责独立评审后的原生验证与最终 push。
- 原生 run `43025231891`、job `130538179477` 已证明：original 返回 1 且无 `level.bscn`；outer-quoted 返回 0 且生成 `level.bscn`；backslashes 返回 1；unquoted 返回 0 但不能处理空格。日志为 `build-core-ci-controller-logs/windows-launch-probe-results.log`。
- 只修改 Windows 测试进程启动，不改 baker 生成、PAL、序列化、CLI、公共 API/ABI、checkpoint writer、RHI、D3D12/compat 或 CI 通过条件。
- 不把无空格路径不加引号作为修复；必须保留 exe/输出路径各自引用及完整命令额外引用，支持空格路径。
- 新名称使用 `core_app`/`CoreApp`/`CORE_APP`，不引入旧外部引擎前缀或新 `application` 领域名。Vulkan 默认，OpenGL 只作最后降级/画面对照，不引入 X11。
- 所有构建和并行 CTest 使用 `-j3`。每项先真实 RED、最小 GREEN、变异/恢复、全量非图形回归、独立规格与质量评审。Linux 结果不能替代 native Windows；controller 负责真实 CI。

---

### Task 1: Windows 完整命令引用与真实资产回归

**Files:**
- Modify: `engine/tests/test_core_app_assets.c`（仅 `run_baker()` 的 Windows 命令构造）
- Modify: `engine/tests/test_core_app_baker_diagnostics.cmake`（真实启动成功与格式合同）
- Modify: `docs/Implementation_Status.md`（原生结果出来后追加）
- Modify: `docs/design/core_app_integration.md`（原生结果出来后追加）
- Report: `.superpowers/sdd/2026-11-11-core-app-windows-launch-fix/task-1-report.md`

**Interfaces:**
- Consumes: `CORE_APP_ASSET_BAKE_EXECUTABLE`、A/B 输出路径和既有 `run_baker(output, slot)` 原始 `system()` 返回值。
- Produces: Windows 完整命令形如 `""D:/path/core_app_asset_bake.exe" --output "C:/output path""`；POSIX 仍为 `"/path/core_app_asset_bake" --output "/output path"`。
- Preserves: 原始返回码、`ensure_baked()` 消费方式、失败诊断、A/B 短路和全部资产断言。

- [ ] **Step 1: 固化原生 RED 和启动成功合同**

记录 `43025231891/job 130538179477` 中 original 的 `raw=1`、解释器语法错误和空输出目录，以及 outer-quoted 的真实成功。修改 `test_core_app_baker_diagnostics.cmake`，在正常 baker 检查之后增加真实 `system()` 启动的资产测试：

```cmake
run_process(system_baked_assets 0 "${CORE_APP_ASSET_TEST}")
expect_not_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}"
    "FAIL: CORE_APP_TEST stage=launch" "real system() baker launch")
if(WIN32)
    file(MAKE_DIRECTORY "${WORK}/temp with space")
    run_process(system_baked_assets_with_space 0 "${CMAKE_COMMAND}" -E env
        "TEMP=${WORK}/temp with space" "${CORE_APP_ASSET_TEST}")
    expect_not_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}"
        "FAIL: CORE_APP_TEST stage=launch" "space-containing system() baker launch")
endif()
```

旧 Windows 实现此处返回 1，构成正式行为 RED。另在已有源码合同中要求 `_WIN32` 的格式为 `"\"\"%s\" --output \"%s\"\""`，非 Windows 保持 `"\"%s\" --output \"%s\""`；该格式检查只是补充，不能替代真实进程/文件断言。Linux 旧实现可直接通过真实启动，但原生 Windows RED 已经存在，不宣称本地重新复现了 Windows。Windows 额外以含空格的 `TEMP` 运行同一真实资产测试，证明路径引用没有退化成仅适用于无空格路径。

- [ ] **Step 2: 仅修改 Windows 命令构造**

保持 `run_baker()` 的命令缓冲区、长度检查、原始返回和诊断路径，只将格式选择改为：

```c
#if defined(_WIN32)
    int n = snprintf(command, sizeof(command), "\"\"%s\" --output \"%s\"\"",
                     CORE_APP_ASSET_BAKE_EXECUTABLE, output);
#else
    int n = snprintf(command, sizeof(command), "\"%s\" --output \"%s\"",
                     CORE_APP_ASSET_BAKE_EXECUTABLE, output);
#endif
```

不得把 `system()` 改成不经过 shell 的 POSIX 调用，也不得改变 baker、PAL 或其它平台路径规则。Windows 的 exe 和输出路径仍分别引用，完整字符串再包一层引号。

- [ ] **Step 3: GREEN、变异、完整回归与原生验收**

运行 focused diagnostics/assets/PAL 和完整非图形 `-j3`。临时把 Windows 格式恢复为单层的 `"\"%s\" --output \"%s\""`，格式合同必须 RED；精确恢复双层后 GREEN。该静态变异只是本地补充，原生 original/outer-quoted 探针已提供真实行为变异对照。

controller 将已评审提交合并到临时 validation 分支，实际运行 Windows direct baker、`test_core_app_assets` 和诊断合同。要求：
- `test_core_app_assets` 16/16（Windows 无 POSIX fault injection），不再出现 `launch.system raw=1`；
- A/B 均由真实 `system()` 启动，11 个正式资产逐字节比较通过；
- 诊断合同覆盖原始启动成功、受控失败和既有返回语义；
- 临时 probe 的 original 仍为负对照，outer-quoted 成功，最终 outcome/gate 正确，不能把临时 probe 合入 master；
- macOS 合同保持 GREEN，D3D12 compat 的独立后续任务不被误标为完成。

- [ ] **Step 4: 独立评审、提交与文档**

独立规格与质量评审检查精确引号、跨平台分支、返回/清理行为和真实回归，不接受无空格路径不加引号的替代。提交：

```bash
git commit -m "fix: quote core app Windows process launch"
```

原生证据取得后，追加 `docs/Implementation_Status.md` 与 `docs/design/core_app_integration.md` 的当前结果和剩余 compat 限制。完整 sanitizer/no-tests/fuzz、全分支终审和 controller push 是后续 integration gate，不在本任务提前宣称完成。
