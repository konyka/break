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

- [ ] **Step 1: 建立真实多配置 RED**

创建 `test_core_app_ctest_config_contract.cmake`，复用 compat 所需的 `ENGINE_SOURCE_DIR`、`REPOSITORY_ROOT`、`PLAN_FILE`、`DESIGN_FILE`、`GIT_EXECUTABLE`、`CORE_APP`、`NETWORK_ENABLED`、`CTEST_EXECUTABLE`、`WORK`、有效后端和四个真实 Vulkan/shaderc 路径。运行真实 compat，而不是模拟其断言：

```cmake
execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env
        "CMAKE_GENERATOR=Ninja Multi-Config"
        "${CMAKE_COMMAND}"
        "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
        "-DREPOSITORY_ROOT=${REPOSITORY_ROOT}"
        "-DPLAN_FILE=${PLAN_FILE}"
        "-DDESIGN_FILE=${DESIGN_FILE}"
        "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
        "-DCORE_APP=${CORE_APP}"
        "-DNETWORK_ENABLED=${NETWORK_ENABLED}"
        "-DCTEST_EXECUTABLE=${CTEST_EXECUTABLE}"
        "-DWORK=${WORK}"
        "-DNESTED_CMAKE_GENERATOR=Ninja Multi-Config"
        "-DNESTED_CTEST_CONFIG=Debug"
        ${nested_toolchain_defs}
        -P "${ENGINE_SOURCE_DIR}/tests/test_core_app_contract_compat.cmake"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error)
```

旧实现忽略新接口、使用多配置默认生成器但未给嵌套 CTest `-C Debug`，因此 corrupt/nm/nested 用例 `Not Run`。要求 RED 输出包含 `Not Run` 或 `NOT_AVAILABLE`，且不是缺编译器、缺 SDK、缺测试文件等脚手架错误。`Ninja Multi-Config` 不可用时必须明确 FAIL，不得把缺工具记成产品验证通过。

- [ ] **Step 2: 最小传递与所有嵌套调用**

父 `test_core_app_contract_compat` 注册增加：

```cmake
"-DNESTED_CMAKE_GENERATOR=${CMAKE_GENERATOR}"
"-DNESTED_CTEST_CONFIG=$<CONFIG>"
```

compat 要求 generator 非空；在配置 fixture 时使用 `-G "${NESTED_CMAKE_GENERATOR}"`，覆盖 permission/corrupt/nm/archive 的实际 configure。生成：

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

将 `${nested_ctest_config_args}` 放到每个嵌套 `ctest --test-dir <root>` 后，包括 formal/naming corrupt、archive tracking、精确豁免、nm skip 与 nested/CLI error；不得只修一个可见用例。同步新增回归的父注册，保留有效后端与真实 SDK 两跳定义。

- [ ] **Step 3: GREEN、变异与回归**

运行新合同，必须不再出现 `Not Run`/`NOT_AVAILABLE`，并得到 compat 完整 PASS。临时删除一个 `nested_ctest_config_args` 传递或清空多配置 config，必须 RED；精确恢复后 GREEN。再运行 target/nested/nm/compat focused 和：

```bash
ctest --test-dir build-core-ci-normal -LE 'graphics|fuzz' -j3 --output-on-failure
```

确认没有弱化 corrupt Git、额外/缺失资产、命名违规、nm unavailable、nested configure/CLI error 的任何断言。提交：

```bash
git commit -m "test: preserve core app nested CTest configuration"
```

- [ ] **Step 4: 独立规格与质量评审**

重点检查每个生成器/CTest 调用、含空格 generator 的参数边界、多配置空 config 的显式拒绝和原有负例。原生 Windows 尚未验证前不得标记 Task 1 native 完成；controller 将合并已评审提交到临时验证分支。

### Task 2: 为 D3D12 归档提供真实 Agility DLL

**Files:**
- Modify: `engine/tests/test_core_app_contract_compat.cmake`
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

- [ ] **Step 3: GREEN、变异与原生验证**

非 D3D12 的完整 compat/完整非图形 `-j3` 不回归。controller 在真实 D3D12 验证分支运行 compat：归档 configure、nm skip、nested/CLI error、corrupt Git 和命名负例必须按各自合同执行，不能再由缺 DLL 阻断。临时移除一个真实文件暂存必须重新得到该文件的 gate RED；恢复后 compat GREEN。记录 compat 及后续 WARP 步骤的真实结果，WARP/headless 不得冒充独立显卡。

- [ ] **Step 4: 独立规格与质量评审、提交**

确认只改 compat fixture、真实哈希、非 D3D12 无新依赖，且原 Task 1 的 `Not Run` 没有复发。提交：

```bash
git commit -m "test: stage real D3D12 SDK in core app archive"
```

更新 `docs/Implementation_Status.md` 和 `docs/design/core_app_integration.md` 的当前 Windows compat/D3D12 证据与剩余限制。完整最终验证、独立全分支评审与 controller push 是后续 integration gate，不在本任务提前声称完成。
