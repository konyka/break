# C++20 `main` linkage 修复报告

- 日期：2026-11-10
- 工作树：`/home/timeshift/opensource/break/.worktrees/remove-x11`
- 基线 HEAD：`d04f7e945e36df5f834cafd0ebb73d6217282bc2`
- 对应 `origin/master` / 远程 run SHA：`103d19b5dd7fa8ba0a8b4c9ca89a75fa470ae00c`

## 结论与范围

远程 Windows D3D12 run [42449243711](https://github.com/konyka/break/actions/runs/42449243711) 的失败不是测试源中显式包裹了 `main`，而是 `engine/src/core/types.h` 在 `_MSC_VER` 分支没有关闭自己的 `extern "C"`。最小根因修复是把既有的 C++ linkage 关闭块移到对齐宏条件之外。

没有修改 `engine/tests/test_public_api_cpp20.cpp`，没有删除测试或断言，没有关闭/过滤警告，也没有改变 live `break_version_string()` 调用。测试源中的条件补 `}` 会掩盖公共头非自包含问题，因此没有采用。

这也造成一个必须明确交接的范围偏差：委托文字只允许修改必要测试文件和状态文档，但实际根因修复必须修改公共头 `engine/src/core/types.h`。本提交保留真实根因修复，并在此记录该偏差，不声称只改了测试文件。

## 远程证据

命令：

```bash
gh run view 42449243711 --json headSha,headBranch,event,status,conclusion,url,workflowName
gh run view 42449243711 --log-failed
```

元数据：

```text
{"conclusion":"failure","event":"push","headBranch":"master","headSha":"103d19b5dd7fa8ba0a8b4c9ca89a75fa470ae00c","status":"completed","url":"https://github.com/konyka/break/actions/runs/42449243711","workflowName":"windows-d3d12"}
```

失败日志中的实际编译器定义为 `ENGINE_PLATFORM_WINDOWS=1`、`ENGINE_RHI_BACKEND_D3D12=1`，编译器为 Windows runner 上的 `clang++.exe`，标准为 `gnu++20`，并启用 `-Wall -Wextra -Werror -pedantic`。关键输出：

```text
D:/a/break/break/engine/tests/test_public_api_cpp20.cpp:55:5: error: 'main' should not be 'extern "C"' [-Werror,-Wmain]
   55 | int main() {
      |     ^
D:/a/break/break/engine/tests/test_public_api_cpp20.cpp:59:2: error: expected '}'
   59 | }
      |  ^
D:/a/break/break/engine/src\core/types.h:18:12: note: to match this '{'
   18 | extern "C" {
```

## 根因

修复前 `core/types.h` 的结构为：

```cpp
#if defined(_MSC_VER)
    #define ENGINE_ALIGN(x) __declspec(align(x))
#else
    #define ENGINE_ALIGN(x) __attribute__((aligned(x)))
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
```

因此非 MSVC 分支会关闭从文件 `:18` 开始的 `extern "C"`，MSVC 分支不会。后续公共头和测试 `main` 都处于这个未关闭的 linkage specification 中。

修复后只调整预处理边界：

```cpp
#if defined(_MSC_VER)
    #define ENGINE_ALIGN(x) __declspec(align(x))
#else
    #define ENGINE_ALIGN(x) __attribute__((aligned(x)))
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
```

公共头声明仍位于 C linkage 内，头文件返回后 `main` 恢复 C++ linkage。

## RED：修复前本机 Clang 复现

本机编译器：

```text
$ clang++ --version
clang version 22.1.8 (Fedora 22.1.8-4.fc44)
Target: x86_64-redhat-linux-gnu
```

先使用现有 Linux target 的实际 include/defines 加显式 `-Wmain`：

```bash
clang++ \
  -DENGINE_PLATFORM_LINUX=1 -DENGINE_PLATFORM_WAYLAND=1 \
  -DENGINE_RHI_BACKEND_VULKAN=1 -DENGINE_RHI_ROLLOUT_CONFIG_VERSION=3 \
  -DENGINE_VULKAN=1 -D_POSIX_C_SOURCE=199309L \
  -Iengine/src -Iengine/external -Iengine/include \
  -std=gnu++20 -Wall -Wextra -Werror -Wmain -pedantic \
  -fsyntax-only engine/tests/test_public_api_cpp20.cpp
```

修复前该命令也通过（exit 0），因为非 MSVC 分支原本就关闭 linkage；它不能复现远程 Windows 分支，不能作为 Windows 证据。

随后保留完整测试 TU 和远程 target defines，强制 `_MSC_VER` 以选择出问题的预处理分支：

```bash
clang++ -include atomic \
  -D_MSC_VER=1944 -fms-extensions \
  -DENGINE_PLATFORM_WINDOWS=1 -DENGINE_RHI_BACKEND_D3D12=1 \
  -DENGINE_RHI_ROLLOUT_CONFIG_VERSION=3 -D_CRT_SECURE_NO_WARNINGS \
  -D_WIN32_WINNT=0x0601 \
  -Iengine/src -Iengine/external -Iengine/include \
  -std=gnu++20 -Wall -Wextra -Werror -Wmain -pedantic \
  -fsyntax-only engine/tests/test_public_api_cpp20.cpp
```

输出（exit 1）：

```text
engine/tests/test_public_api_cpp20.cpp:55:5: error: 'main' should not be 'extern "C"' [-Werror,-Wmain]
   55 | int main() {
      |     ^
engine/tests/test_public_api_cpp20.cpp:59:2: error: expected '}'
   59 | }
      |  ^
engine/src/core/types.h:18:12: note: to match this '{'
   18 | extern "C" {
      |            ^
2 errors generated.
```

`-include atomic` 的用途仅是预先加载宿主 libstdc++ 的 `<atomic>`。不预装时，Linux 标准库模板会在未关闭的 C linkage 中提前报错，淹没远程日志中的 `main` 诊断；预装后同一完整测试 TU 精确到达远程两条错误。它不是 native Windows 标准库、SDK 或运行时验证。

另用最小 TU 独立确认了同一根因：

```bash
clang++ -D_MSC_VER=1944 -fms-extensions -Iengine/src \
  -std=gnu++20 -Werror -Wmain -pedantic -x c++ -fsyntax-only - <<'EOF'
#include <core/types.h>
int main() { return 0; }
EOF
```

输出同样为 `main should not be extern "C"`、`expected '}'`，并指向 `core/types.h:18`。

## GREEN：最小修复后

### 1. 远程分支复现命令转绿

重新执行上述完整 TU 的 `_MSC_VER=1944` 命令：

```text
（无编译输出，exit 0）
```

普通 Linux target 的 Clang `-Werror -Wmain` 语法命令也再次通过：

```text
（无编译输出，exit 0）
```

### 2. Clang 实际编译、链接并运行测试

不是只做头文件 import 或关闭诊断；以下命令生成真实对象和可执行文件，链接现有 `engine` 及其实际依赖，并执行测试中的 live API 调用：

```bash
clang++ \
  -DENGINE_PLATFORM_LINUX=1 -DENGINE_PLATFORM_WAYLAND=1 \
  -DENGINE_RHI_BACKEND_VULKAN=1 -DENGINE_RHI_ROLLOUT_CONFIG_VERSION=3 \
  -DENGINE_VULKAN=1 -D_POSIX_C_SOURCE=199309L \
  -Iengine/src -Iengine/external -Iengine/include \
  -g -std=gnu++20 -Wall -Wextra -Werror -Wmain -pedantic \
  -c engine/tests/test_public_api_cpp20.cpp \
  -o build-remove-x11-auto/clang_cpp20_main_fix_test.o

clang++ -g build-remove-x11-auto/clang_cpp20_main_fix_test.o \
  -o build-remove-x11-auto/clang_cpp20_main_fix_test \
  build-remove-x11-auto/libengine.a \
  build-remove-x11-auto/libglad.a \
  build-remove-x11-auto/liblua.a \
  build-remove-x11-auto/libstb_image.a \
  build-remove-x11-auto/libmeshopt_c.a \
  -lwayland-egl -lwayland-cursor -lwayland-client \
  -lm -lxkbcommon -ldl -lpthread

build-remove-x11-auto/clang_cpp20_main_fix_test
```

结果：

```text
（编译、链接和运行均无输出，exit 0）
```

临时对象和可执行文件随后删除。

### 3. 现有 target 与 CTest

```bash
cmake --build build-remove-x11-auto -j3 --target test_public_api_cpp20
ctest --test-dir build-remove-x11-auto -R '^test_public_api_cpp20$' --output-on-failure
```

关键输出：

```text
[100%] Built target test_public_api_cpp20
Test project /home/timeshift/opensource/break/.worktrees/remove-x11/build-remove-x11-auto
    Start 24: test_public_api_cpp20
1/1 Test #24: test_public_api_cpp20 ............   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1
Total Test time (real) =   0.01 sec
```

## 生产变异与精确恢复

变异操作：仅把 `core/types.h` 的 `#ifdef __cplusplus` / `}` / `#endif` 临时移回 `_MSC_VER` 条件的 `#else` 内，使 `main` 再次处于 C linkage；不改测试、不改警告参数。

重新运行同一完整 TU Clang RED 命令，输出（exit 1）：

```text
engine/tests/test_public_api_cpp20.cpp:55:5: error: 'main' should not be 'extern "C"' [-Werror,-Wmain]
   55 | int main() {
      |     ^
engine/tests/test_public_api_cpp20.cpp:59:2: error: expected '}'
   59 | }
      |  ^
engine/src/core/types.h:18:12: note: to match this '{'
   18 | extern "C" {
      |            ^
2 errors generated.
```

随后立即将同一关闭块移回 `_MSC_VER` 条件的 `#endif` 之后。恢复后：

- `_MSC_VER=1944` 完整 TU Clang 命令：无输出，exit 0。
- 普通 Linux target Clang 命令：无输出，exit 0。
- 最终 diff 仍只有预期的一个 linkage 边界 hunk；变异未进入提交。

## 恢复后的完整构建与现有测试

```bash
cmake --build build-remove-x11-auto -j3
ctest --test-dir build-remove-x11-auto -R '^test_public_api_cpp20$' --output-on-failure
```

完整构建成功，末尾输出：

```text
[100%] Built target rhi_swapchain_bench
[100%] Built target test_rhi_runtime_fallback
```

CTest 输出：

```text
Test project /home/timeshift/opensource/break/.worktrees/remove-x11/build-remove-x11-auto
    Start 24: test_public_api_cpp20
1/1 Test #24: test_public_api_cpp20 ............   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Label Time Summary:
headless             =   0.00 sec*proc (1 test)
platform_contract    =   0.00 sec*proc (1 test)

Total Test time (real) =   0.01 sec
```

## 文件清单

- `engine/src/core/types.h`：必要公共头根因修复；仅移动既有 C++ linkage 关闭块。
- `docs/Implementation_Status.md`：顶部加入远程 run、根因、实际验证和边界记录。
- `.superpowers/sdd/2026-11-10-remove-x11/cpp20-main-fix-report.md`：本报告。
- `engine/tests/test_public_api_cpp20.cpp`：**未修改**；全部既有断言和行为保持原样。

## 未验证边界 / concerns

- 本机是 Linux；`_MSC_VER=1944 -fms-extensions` 是对 MSVC 预处理分支的 Clang 编译复现，不是 native Windows 编译或运行证据。
- 未运行 Windows SDK、MSVC 标准库、D3D12、WARP 或远程 runner；run 42449243711 对应 lane 必须在推送后重新执行。
- 本任务只运行了聚焦 CTest，不把完整构建成功表述为全量测试通过。
- 实际必要修复文件是公共头而不是委托预期的测试源；未采用测试内补括号来隐藏该根因。
