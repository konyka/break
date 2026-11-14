# Core App Windows Process Launch Probe Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 用真实 C `system()` 和真实 Windows baker 对照命令行变体，确定 `ensure_baked()` 在生成前失败的准确机制，不先猜修复。

**Architecture:** 新增仅用于临时验证分支的进程探针，直接接收一条完整命令并调用 C `system()`，保存原始返回值及 OS/CRT 错误。CMake 以真实 `core_app_asset_bake.exe` 分别执行当前格式、整串额外引用、反斜杠路径和无空格路径不加引用；所有输出目录彼此独立。探针和验证配置永不合并到 master，取得证据后另写最小修复计划。

**Tech Stack:** C11、C `system()`、Win32、CMake/CTest、MSVC、GitHub Actions、真实 baker 文件输出。

## Global Constraints

- 临时工作树固定为 `/home/timeshift/opensource/break/.worktrees/core-app-ci-validation`，分支 `core-app-ci-validation`，基线为 `f9f6f9be1ac809730c92a6dd29c3de1a0b380257`；临时提交不合并到 master，不建 PR，代理不 push。
- 已证实的原生失败是 `system()` 返回 1，子进程输出 `The filename, directory name, or volume label syntax is incorrect`，A/B 目录为空；直接 baker 返回 0。不得把它提前断言为某条引号规则或文件系统故障。
- 只使用真实 C `system()`、真实可执行文件和独立输出目录，不以 PowerShell/`cmd.exe` 的直接调用冒充相同 CRT 边界，不伪造 SDK 或运行结果。
- 不改变生产 baker、现有资产测试、PAL、序列化、Core App API/ABI、RHI 或 CI 通过条件。新名称使用 `core_app`/`CoreApp`/`CORE_APP`，不引入旧外部引擎前缀或新 `application` 领域名。
- 所有构建和并行 CTest 使用 `-j3`。Linux 结果只验证探针，不是 native Windows 证据。先 RED、再 GREEN、变异/恢复，独立规格与质量评审后才由 controller push。
- 现有原生日志为 `build-core-ci-controller-logs/native-windows-diagnostic-round1.log`。报告必须保留每条命令、原始返回、OS/CRT 错误、生成的 `level.bscn` 是否存在，以及后续修复仍需的未知项。

---

### Task 1: 真实 C system() 命令行对照探针

**Files:**
- Create: `engine/tests/test_core_app_process_launch.c`
- Create: `engine/tests/test_core_app_process_launch.cmake`
- Modify: `engine/CMakeLists.txt`（仅临时探针/target 注册）
- Modify: `.github/workflows/core-app-native-validation.yml`（仅临时构建与探针步骤）
- Modify: `engine/tests/test_core_app_native_validation.cmake`（临时工作流合同）
- Report: `.superpowers/sdd/2026-11-11-core-app-windows-launch-probe/task-1-report.md`

**Interfaces:**
- Produces: `test_core_app_process_launch` 接受一个完整命令字符串，真实调用 `system()`，打印 `CORE_APP_PROCESS_LAUNCH command=<...> raw=<...> os_error=<...> errno=<...>`。
- Produces: `test_core_app_process_launch_probe` 输出 original/outer-quoted/backslashes/unquoted 四组真实结果；不变成永久生产测试或通过条件。
- Preserves: 原有 direct baker、`test_core_app_assets` 及完整失败日志。即使探针失败，后续原始资产诊断也必须执行。

- [ ] **Step 1: 先写探针合同并证明 RED**

在 `test_core_app_native_validation.cmake` 中要求 helper target、真实探针步骤及后续原始 assets 步骤仍然存在。首次运行：

```bash
cmake -DREPO_ROOT="$PWD" -P engine/tests/test_core_app_native_validation.cmake
```

预期因 probe 文件/构建/运行合同缺失而 RED，不得把不相关的旧 Windows 失败当作探针 RED。

探针 C 文件以下来源级最小接口为边界；实现时保持打印在 `system()` 后立即保存错误的顺序：

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN32)
#include <windows.h>
#endif

int main(int argc, char **argv) {
    if (argc != 2 || argv[1][0] == '\0') return 2;
    errno = 0;
    int raw = system(argv[1]);
    int saved_errno = errno;
#if defined(_WIN32)
    unsigned long os_error = (unsigned long)GetLastError();
#else
    unsigned long os_error = 0;
#endif
    printf("CORE_APP_PROCESS_LAUNCH command=%s raw=%d os_error=%lu errno=%d\n",
           argv[1], raw, os_error, saved_errno);
    return raw == 0 ? 0 : 1;
}
```

- [ ] **Step 2: 实现 helper 与四种真实命令对照**

`test_core_app_process_launch.cmake` 必须要求 `CORE_APP_PROCESS_LAUNCH`、`CORE_APP_ASSET_BAKE`、`WORK` 非空，删除并重建独立 `WORK`，对 helper 的真实路径和 baker 的真实路径都检查 `EXISTS`。当前格式必须逐字复用 `run_baker()` 的 `"<exe>" --output "<dir>"`；额外整串引用必须等价于在该完整字符串外再包一层 `"`，而不是只包裹 exe。

```cmake
set(original "\"${CORE_APP_ASSET_BAKE}\" --output \"${WORK}/original\"")
set(outer_quoted "\"${original}\"")
set(exe_backslashes "${CORE_APP_ASSET_BAKE}")
set(out_backslashes "${WORK}/backslashes")
string(REPLACE "/" "\\" exe_backslashes "${exe_backslashes}")
string(REPLACE "/" "\\" out_backslashes "${out_backslashes}")
set(backslashes "\"${exe_backslashes}\" --output \"${out_backslashes}\"")
set(unquoted "${CORE_APP_ASSET_BAKE} --output ${WORK}/unquoted")
```

每个变体用 `execute_process(COMMAND "${CORE_APP_PROCESS_LAUNCH}" "${command}" ...)` 调用，记录完整 stdout/stderr、返回码和 `${WORK}/<variant>/level.bscn` 是否存在。打印所有变体后，Linux 要求 original 成功；Windows 要求 original 复现非零，并要求至少一个候选真实成功，否则探针本身 FAIL 且不形成修复结论。保留原始输出，不截断。

- [ ] **Step 3: 临时原生执行、GREEN 与变异**

注册 helper 和 `test_core_app_process_launch_probe`，在临时 Windows job 中构建 `core_app_asset_bake`、`test_core_app_process_launch`、`test_core_app_assets`，在原始 baker/assets 步骤前以 `continue-on-error: true` 执行 probe 的 `ctest -V`。该设置只允许继续采集原始失败，不得令最终失败 job 变绿。原始 baker/assets 和 failure-only 目录快照必须保留。

本机配置/构建/运行探针验证 Linux 的真实 C `system()`，并临时删除一个候选变体，要求合同 RED，恢复后 GREEN。运行：

```bash
cmake --build build --target core_app_asset_bake test_core_app_process_launch test_core_app_assets -j3
ctest --test-dir build -R '^test_core_app_process_launch_probe$' -V
```

本机没有对应 build 根时按仓库现有配置创建独立 `build-launch-probe`，不复用其它工作树。controller push 后读取真实 Windows 四组输出；如果所有候选失败，停止并补充新的诊断，不反复尝试猜测。

- [ ] **Step 4: 独立评审、提交与后续拆分**

检查探针确实经过 C `system()`，而不是 shell 近似；原始失败控制与每个候选的路径隔离/结果均完整。提交仅限上述临时探针与验证配置：

```bash
git add engine/CMakeLists.txt engine/tests/test_core_app_process_launch.c \
  engine/tests/test_core_app_process_launch.cmake \
  engine/tests/test_core_app_native_validation.cmake \
  .github/workflows/core-app-native-validation.yml
git commit -m "test: probe core app Windows process launch"
```

将 RED/GREEN/变异、Linux 结果、原生限制写入指定 report。独立规格与质量评审通过后由 controller push 并补充真实 Windows 结果。随后按证据另建独立最小修复计划，不把本诊断任务写成 Windows 已修复。
