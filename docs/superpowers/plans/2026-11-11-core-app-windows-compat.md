# Core App Windows Compatibility Fixtures Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 让 Core App compat 在 Windows 多配置 CTest 与 D3D12 归档配置中运行真实合同，而不是落入 `NOT_AVAILABLE` 或缺少 Agility DLL。

**Architecture:** 将父级实际 CMake generator 和构建配置显式传给 compat 的生成器与嵌套 CTest，避免多配置测试未选择配置。归档 HEAD 后，仅为 D3D12 将父级已锁定的两个真实 Agility DLL 复制到归档对应位置并校验哈希；不下载替代版本、不创建占位 SDK。两个问题分别 TDD、分别评审。

**Tech Stack:** CMake/CTest、Ninja Multi-Config、Visual Studio/MSVC、D3D12 Agility SDK、Git archive、Windows CI、C11 项目测试。

## Global Constraints

- 正式实现工作树为 `/home/timeshift/opensource/break/.worktrees/core-app-ci`，分支 `core-app-ci`；不得把临时 `core-app-ci-validation`、APFS 变异或临时 process probe 合入 master。实现代理串行，每项 scoped commit 和独立规格/质量评审，不建 PR。
- 以原生 run `43016548952`、job `130508974968` 为 RED 证据。完整日志在 `build-core-ci-controller-logs/d3d12-compat-diagnostic-round1.log`。
- 生成的 `CTestTestfile.cmake` 含按配置分支的 `add_test` 和 `else() add_test(... NOT_AVAILABLE)`；旧嵌套调用没有 `-C`。禁止只改引号或无条件删除测试来掩盖这一机制。
- 父级 Agility DLL 位于 `engine/external/d3d12/agility/build/native/bin/x64`，被 `.gitignore` 排除，HEAD archive 不包含它们。D3D12 归档只复制该真实父级 `D3D12Core.dll` 和 `d3d12SDKLayers.dll`，源/目标 SHA-256 必须一致；缺失真实输入必须 FAIL。
- 保留现有 Core App API/ABI、后端有效值、D3D12 DLL gate、nm 缺符号 FAIL、无 Git UNVERIFIED 边界和原有负例。不得把 `Not Run`、nested configure failure 或真实错误改成 skip/PASS。
- 新名称使用 `core_app`/`CoreApp`/`CORE_APP` 和现有 CMake 风格，不引入旧外部引擎前缀或新 `game` 领域名。Vulkan 默认，OpenGL 只作最后降级/画面对照，不引入 X11。
- 构建和并行 CTest 使用 `-j3`。Linux Ninja Multi-Config 只验证相同生成器/配置机制，不冒充 native Windows/D3D12。最终必须有真实 Windows compat 和 D3D12 lane 结果。
- 每项先 RED、最小 GREEN、变异/恢复、完整非图形回归、独立规格与质量评审。文档只追加当前事实；controller 负责验证分支的原生运行与最终合并，代理不 push。
- 运行合同的完成判定必须来自真实返回码和 `core_app compatibility contract passed`。只在生成文件中存在合法 `NOT_AVAILABLE` 分支不构成失败；`Not Run` 只在实际运行输出中判定。缺工具、缺真实 SDK 或缺输入不能被当作产品 RED/GREEN。

---

### Task 1: 继承实际 generator 与 CTEST_CONFIGURATION_TYPE

**Files:**
- Modify: `engine/CMakeLists.txt`（compat 与新增回归注册）
- Modify: `engine/tests/test_core_app_contract_compat.cmake`
- Create: `engine/tests/test_core_app_ctest_config_contract.cmake`
- Report: `.superpowers/sdd/2026-11-11-core-app-windows-compat/task-1-report.md`

**Interfaces:**
- Parent provides: `NESTED_CMAKE_GENERATOR="${CMAKE_GENERATOR}"`、`NESTED_CTEST_CONFIG="$<CONFIG>"`。
- Compat consumes: generator 用于每个 fixture configure；非空 config 生成 `ctest -C <config>` 参数。多配置 generator 必须要求非空 config。
- Preserves: 现有 archive/nm/CLI/Git 合同预期；失败仍是失败，nm unavailable 仍按既有 skip 合同处理。

- [ ] **Step 1: 建立具有最终判定的真实多配置 RED**

创建 `test_core_app_ctest_config_contract.cmake`。除 compat 原有必填输入外，要求 `NESTED_CMAKE_GENERATOR` 和 `NESTED_CTEST_CONFIG`（后者允许为空）已定义，并明确构造真实后端/SDK 参数：

```cmake
set(nested_toolchain_defs
    "-DNESTED_ENGINE_RHI_BACKEND=${NESTED_ENGINE_RHI_BACKEND}")
foreach(cache_var Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
    if(DEFINED ${cache_var} AND NOT "${${cache_var}}" STREQUAL "")
        list(APPEND nested_toolchain_defs "-D${cache_var}=${${cache_var}}")
    endif()
endforeach()
if(NESTED_ENGINE_RHI_BACKEND STREQUAL "vulkan")
    foreach(required Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
        if(NOT DEFINED ${required} OR "${${required}}" STREQUAL "")
            message(FATAL_ERROR "real Vulkan input is required: ${required}")
        endif()
    endforeach()
endif()
```

检查 `cmake -E capabilities` 实际包含 `Ninja Multi-Config`，并找到真实 `ninja` 可执行文件；缺工具时明确环境失败，不进入产品通过结论。以函数执行真实 compat 并打印组合日志，返回结果给调用方：

```cmake
function(run_compat name default_generator nested_generator nested_config work)
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E env
            "CMAKE_GENERATOR=${default_generator}"
            "${CMAKE_COMMAND}"
            "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
            "-DREPOSITORY_ROOT=${REPOSITORY_ROOT}"
            "-DPLAN_FILE=${PLAN_FILE}"
            "-DDESIGN_FILE=${DESIGN_FILE}"
            "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
            "-DCORE_APP=${CORE_APP}"
            "-DNETWORK_ENABLED=${NETWORK_ENABLED}"
            "-DCTEST_EXECUTABLE=${CTEST_EXECUTABLE}"
            "-DWORK=${work}"
            "-DNESTED_CMAKE_GENERATOR=${nested_generator}"
            "-DNESTED_CTEST_CONFIG=${nested_config}"
            ${nested_toolchain_defs}
            -P "${ENGINE_SOURCE_DIR}/tests/test_core_app_contract_compat.cmake"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error)
    set(log "${output}${error}")
    message(STATUS "${name}: result=${result}\n${log}")
    set(COMPAT_RESULT "${result}" PARENT_SCOPE)
    set(COMPAT_LOG "${log}" PARENT_SCOPE)
endfunction()
```

另一个 `expect_compat_success(name)` 必须要求 `COMPAT_RESULT` 为 0、日志包含 `core_app compatibility contract passed`，并拒绝实际输出中的 `Not Run`/`NOT_AVAILABLE`。它必须在 `run_compat` 之后执行，不能像空包装一样对旧/新实现都成功。

首个场景以默认和请求的 generator 都是 `Ninja Multi-Config`、config `Debug` 运行。旧实现没有 `-C Debug`，应在 corrupt/nm/nested 实际运行中 `Not Run`。记录 `COMPAT_RESULT` 非零、缺少完成标记以及实际 `Not Run`，同时排除缺工具/缺输入的脚手架错误。

- [ ] **Step 2: 最小传递、所有调用与三种独立场景**

父 `test_core_app_contract_compat` 注册增加：

```cmake
"-DNESTED_CMAKE_GENERATOR=${CMAKE_GENERATOR}"
"-DNESTED_CTEST_CONFIG=$<CONFIG>"
```

compat 要求 generator 非空；在 permission/corrupt/nm/archive 的实际 configure 中使用 `-G "${NESTED_CMAKE_GENERATOR}"`。构造并复用：

```cmake
set(nested_ctest_config_args)
if(NOT "${NESTED_CTEST_CONFIG}" STREQUAL "")
    list(APPEND nested_ctest_config_args -C "${NESTED_CTEST_CONFIG}")
endif()
if(NESTED_CMAKE_GENERATOR MATCHES "Visual Studio|Xcode|Multi-Config" AND
   "${NESTED_CTEST_CONFIG}" STREQUAL "")
    message(FATAL_ERROR "a multi-config nested CTest requires NESTED_CTEST_CONFIG")
endif()
```

将 `${nested_ctest_config_args}` 放到每个嵌套 `ctest --test-dir <root>` 后，包括 formal/naming corrupt、archive tracking、精确豁免、nm skip 与 nested/CLI error。同步新增回归的父注册，保留有效后端与真实 SDK 两跳定义。

回归脚本必须分别运行并作出最终判定：

1. `Ninja Multi-Config` 默认/请求值和 `Debug`：证明旧实现未传 `-C` 的 RED，修复后完整 compat PASS。
2. 默认 `Ninja`、请求 `Ninja Multi-Config`、config `Debug`：验证请求 generator 确实覆盖默认值。读取 permission（若实际生成）、corrupt、nm、archive 的 `CMakeCache.txt`，要求 `CMAKE_GENERATOR` 为 `Ninja Multi-Config`；permission 因既有 root 条件未生成时记录该限制，不能伪造其结果。删除 `-G` 必须使这些断言 RED，即使该场景旧实现可能因单配置而侥幸通过。
3. 默认/请求值均为 `Ninja`、config 为空：完整 compat PASS，证明合法单配置空值不会被误拒绝或附加无效 `-C`。

每一个成功场景都检查真实返回码、完成标记及实际 `Not Run`，不是读取生成文件中的合法 fallback 文本。

- [ ] **Step 3: GREEN、变异与完整回归**

运行上述三个场景，均须符合各自结果和缓存断言。执行以下变异并精确恢复：

- 删除一个嵌套 CTest 的 `${nested_ctest_config_args}`，多配置场景 RED。
- 清空多配置 `NESTED_CTEST_CONFIG`，必须出现显式 `requires NESTED_CTEST_CONFIG`，不能变成 skip。
- 删除一个 fixture 的 `-G "${NESTED_CMAKE_GENERATOR}"`，不同默认 generator 的缓存断言 RED。

恢复后三个场景重新 GREEN。运行 target/nested/nm/compat focused 和：

```bash
ctest --test-dir build-core-ci-normal -LE 'graphics|fuzz' -j3 --output-on-failure
```

确认没有弱化 corrupt Git、额外/缺失资产、命名违规、nm unavailable、nested configure/CLI error 的任何断言。提交：

```bash
git commit -m "test: preserve core app nested CTest configuration"
```

- [ ] **Step 4: 独立规格与质量评审**

重点检查每个生成器/CTest 调用、含空格 generator 的参数边界、真实返回码与完成标记、多配置空 config 拒绝、单配置空 config 接受，以及原有负例。原生 Windows 尚未验证前不得标记 Task 1 native 完成；controller 将合并已评审提交到临时验证分支。

### Task 2: 为 D3D12 归档提供真实 Agility DLL

**Files:**
- Modify: `engine/tests/test_core_app_contract_compat.cmake`
- Modify: `docs/Implementation_Status.md`（只追加当前证据）
- Modify: `docs/design/core_app_integration.md`（只追加当前证据）
- Report: `.superpowers/sdd/2026-11-11-core-app-windows-compat/task-2-report.md`

**Interfaces:**
- Consumes: `NESTED_ENGINE_RHI_BACKEND` 和真实父级 `ENGINE_SOURCE_DIR`。
- Produces: D3D12 归档中的 `external/d3d12/agility/build/native/bin/x64/{D3D12Core.dll,d3d12SDKLayers.dll}`，与父级真实文件逐字节一致。
- Preserves: 真实 `engine/CMakeLists.txt` DLL gate 和 fetcher 锁定机制；非 D3D12 归档不增加这些文件。

- [ ] **Step 1: 固定归档缺文件 RED 与输入要求**

以原生日志中 archive/no-tests 的 `D3D12Core.dll missing` 为 RED。在 compat 中增加 D3D12 专属的源文件存在、目标存在和 SHA-256 相等检查，先在未暂存实现上失败；失败必须指向真实父级路径或缺失归档文件，不得写空 DLL、文本占位或改用未锁定下载。

- [ ] **Step 2: 最小真实文件暂存**

在 archive 解包和覆盖合同文件之后、archive configure 之前：

```cmake
if(NESTED_ENGINE_RHI_BACKEND STREQUAL "d3d12")
    foreach(dll_name D3D12Core.dll d3d12SDKLayers.dll)
        set(relative "external/d3d12/agility/build/native/bin/x64/${dll_name}")
        set(source "${ENGINE_SOURCE_DIR}/${relative}")
        set(destination "${archive_engine}/${relative}")
        if(NOT EXISTS "${source}")
            message(FATAL_ERROR "real parent Agility input is missing: ${source}")
        endif()
        configure_file("${source}" "${destination}" COPYONLY)
        file(SHA256 "${source}" source_hash)
        file(SHA256 "${destination}" destination_hash)
        if(NOT source_hash STREQUAL destination_hash)
            message(FATAL_ERROR "staged Agility hash mismatch: ${relative}")
        endif()
    endforeach()
endif()
```

`configure_file` 自动创建父目录。D3D12 下 archive configure 成功后，再次检查两个 destination 的存在和哈希。不得放宽 `engine/CMakeLists.txt` 的 DLL gate，也不得把父 build 目录下的 DLL 当成 archive 输入。

- [ ] **Step 3: GREEN、真实 gate 变异与原生验证**

非 D3D12 的完整 compat/完整非图形 `-j3` 不回归。controller 在真实 D3D12 验证分支运行 compat：归档 configure、nm skip、nested/CLI error、corrupt Git 和命名负例必须按各自合同执行，不能再由缺 DLL 阻断。

原生变异分两步，不能提前被 staging 自检拦截：

1. 在 staging 哈希检查完成后、archive configure 前，删除归档副本 `D3D12Core.dll`（不删除父级真实输入），运行 archive configure，要求真实 gate 输出 `D3D12Core.dll missing`。
2. 用同一父级真实输入 `configure_file(... COPYONLY)` 恢复归档副本，重新验证 SHA-256 和 archive configure，compat 必须 GREEN。

记录 compat 及后续 WARP 步骤的真实结果，WARP/headless 不得冒充独立显卡。若原生失败进入其它未覆盖分支，先写最小回归，不猜测修复。

- [ ] **Step 4: 独立规格与质量评审、提交**

确认实现代码只改 compat fixture、真实哈希、非 D3D12 无新依赖，且原 Task 1 的 `Not Run` 没有复发。提交：

```bash
git commit -m "test: stage real D3D12 SDK in core app archive"
```

按上述文件范围更新 `docs/Implementation_Status.md` 和 `docs/design/core_app_integration.md` 的当前 Windows compat/D3D12 证据与剩余限制；文档变更不是生产 fixture 之外的额外实现。完整最终验证、独立全分支评审与 controller push 是后续 integration gate，不在本任务提前声称完成。
