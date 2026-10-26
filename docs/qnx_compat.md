# QNX 平台兼容（feat/qnx-compat，2026-10-26）

当前里程碑包括：**默认 headless 兼容层、QNX Screen 原生窗口、显式
Screen Vulkan WSI/后端编译路径**。引擎核心与 myui（dummy PAL 离屏路径）
可在无显示环境运行；Vulkan 必须显式选择，不会静默替换默认 headless。
本文记录架构决策、TDD 过程、验证状态与目标机操作步骤。

**Screen 运行证据**：QNX SDP 8.0 软件虚拟显示器上可创建、查询、显示并销毁
真实 `screen_context` / `screen_window`，尺寸、格式、usage、WSI 状态与失败
清理均由 `test_platform_qnx_screen_runtime` 验证。该证据属于 NATIVE_SURFACE，
不代表 GPU 渲染。

**Vulkan 边界**：x86_64 与 aarch64le 的完整 Vulkan 后端均可交叉编译；
`vkCreateScreenSurfaceQNX` 的参数、扩展、ABI 和失败路径有无 GPU 契约测试，
shaderc 在 x86_64 目标侧编译真实 GLSL。当前 VM 没有 Vulkan ICD/GPU 运行收据；
aarch64le 也没有目标机运行证据。因此本文不声称 QNX 上所有图形功能或全部
myui 原生交互均已验证。最新数量与复验记录见 §5，遗留范围见 §7。

## 1. 范围与证据等级

| 能力 | 状态 | 证据 |
|------|------|------|
| 平台描述符与 poll net_loop | 契约及目标语义验证 | 描述符模拟/目标测试；`test_net_loop`/`test_net_replication` |
| 引擎核心与 myui headless | **x86_64 目标 HEADLESS** | 默认及显式 Vulkan 配置的完整目标命令清单，见 §5 |
| 效率（吞吐下限断言） | 目标冒烟验证 | `test_qnx_perf_smoke` 实测见 §6；不是 GPU 基准 |
| QNX Screen 窗口 | **x86_64 NATIVE_SURFACE**；aarch64le COMPILED | 软件虚拟显示器上的真实窗口、属性、WSI 和失败清理测试 |
| Screen Vulkan WSI / 完整 RHI | **双架构 COMPILED** | 扩展、create-info ABI、入口解析、成功/失败注入、完整后端链接 |
| shaderc | **x86_64 目标运行**；aarch64le COMPILED | 目标侧 GLSL→SPIR-V 顶点/片元用例 |
| GPU 实例、交换链、渲染与 GPU 性能 | **当前环境未验证** | 无可用 ICD；不以 loader、shaderc 或虚拟显示器代替 GPU 证据 |

编译、无 GPU 契约和原生窗口是不同证据等级；完整边界见 §7。

## 2. 架构决策

### 2.1 平台描述符（`engine/src/platform/platform_compat.h`）

默认 headless（Screen 可用时）：

```
TARGET_FAMILY = QNX          NET_LOOP = POLL
SURFACE      = QNX_SCREEN    REQUIRES_HOST_SURFACE = 0
GRAPHICS_API = NONE          TARGET_GRAPHICS_API = NONE
VULKAN       = UNAVAILABLE   SUPPORT_EVIDENCE = COMPILED
```

显式 Vulkan 时保留 `SURFACE=QNX_SCREEN`，并切换为
`TARGET_GRAPHICS_API=VULKAN`、`VULKAN_SUPPORT=COMPILED`；编译期
`SUPPORT_EVIDENCE` 仍为 COMPILED，不会根据 configure 结果伪造 GPU_RUNTIME。
`REQUIRES_HOST_SURFACE=0` 表示 headless 核心不依赖宿主注入 surface，Screen
窗口由平台自行创建；没有 Screen 服务或依赖缺失时必须 fail-closed。

### 2.2 net_loop POLL 后端（`engine/src/network/net_loop_poll.c`）

QNX Neutrino 没有 epoll/kqueue，`poll()` 是原生就绪通知机制。在 poll 的
约束内做吞吐优化：

- 兴趣集保存在用户态 slot 数组，**仅注册变更时置 dirty**，稳态 `wait()`
  一次调用恰好一次 `poll()` 系统调用、零数组重建；
- `poll()` 一次系统调用返回一批就绪 fd（批量语义与其余后端一致）；
- 非阻塞 pipe 实现跨线程 wakeup（`write()` 异步信号安全）；
- 电平触发（poll 固有）：每次 wait 都报告仍就绪的 socket；调用方按
  文档化的高吞吐模式排空 socket，在 ET 后端与 LT 后端下同为最优；
- slot↔pollfd 映射在 wait 期间稳定（loop 线程亲和），但 rebuild 前被
  remove 的 slot 会残留旧映射——`test_net_loop` 的 QNX 段专门验证该
  陈旧映射不会上报死 slot。

### 2.3 RHI 解析与依赖门控

`ENGINE_RHI_BACKEND=auto` 在 QNX 默认解析为 `headless`；显式 `vulkan` 或
兼容选项 `ENGINE_VULKAN=ON` 选择完整 Vulkan RHI：

- opengl/metal/d3d12 在 QNX 配置期 FATAL，不静默回退；
- Vulkan 配置必须有 Screen 头文件/库、Vulkan loader/头文件和目标架构的
  shaderc，缺任一项即配置期 FATAL；
- `engine_link_rhi_backend()` 分别链接 `engine_rhi_headless` 或
  `engine_rhi_vulkan`；链接和 shader 编译通过不等于存在 GPU/ICD。

### 2.4 平台层与系统库

- SDP 提供 Screen 时由 `window_screen.c` 自建窗口；否则 `window_mobile.c`
  提供 fail-closed 的平台入口，不能伪称存在原生窗口；
- filewatch 走可移植轮询回退分支（无 inotify）；
- QNX socket API 在 libsocket：`check_library_exists` 探测式链接
  （glibc/macOS 宿主模拟时在 libc，自动跳过）；
- 引擎编译定义 `ENGINE_PLATFORM_QNX=1 _POSIX_C_SOURCE=200112L`。

### 2.5 myui

- `MYUI_PAL` 默认 `dummy`（离屏、确定性），与 QNX headless 形态一致；
- `MYUI_GLES2` / `MYUI_GL_DESKTOP` / `MYUI_VULKAN` 探测仅限
  linux/win32，QNX 不自动启用；引擎 Screen PAL 不等于独立 myui Screen PAL；
- myui headless 测试覆盖布局/CSS/编辑器/echart/MVVM/窗口管理/指标等，
  不据此声称原生 Screen 交互或 GPU 渲染已覆盖。

### 2.6 Screen 窗口层（`engine/src/platform/window_screen.c`）

- CMake 在 QNX 平台探测 SDP 的 `screen/screen.h` + `libscreen`（默认
  `ENGINE_QNX_SCREEN=ON`）；toolchain 的 `CMAKE_FIND_ROOT_PATH` 同时挂
  `$QNX_TARGET` 与 `$QNX_TARGET/<arch>`（头文件在 `usr/include`，库在
  `<arch>/usr/lib`）；
- 平台描述符的 surface 为 `ENGINE_SURFACE_QNX_SCREEN`（自建、非宿主注入）。
  默认 RHI 仍为 headless；显式 Vulkan 时 target API 为 VULKAN，支持等级和
  编译期证据均为 COMPILED；
- `platform_create` 依次创建 context/window/event，设置
  SIZE/FORMAT_RGBA8888/USAGE 并 flush。显式 Vulkan 增加
  `SCREEN_USAGE_VULKAN`。任一步失败均销毁已经创建的句柄并返回 NULL；
  运行时测试用链接器 wrapping 注入 SIZE/FORMAT/USAGE/flush 失败，验证
  context/window/event 各释放一次；
- `platform_poll` 非阻塞处理 CLOSE、POINTER（坐标/左中右键/垂直滚轮）和
  KEYBOARD（`screen_keymap.h` 映射）。尺寸查询实时读取
  `SCREEN_PROPERTY_SIZE`；键映射常量以 `_Static_assert` 对照 QNX 真头文件；
- WSI 使用 `PLATFORM_WSI_BACKEND_QNX`，不借用 X11 标识。
  `platform_window_native/surface_native` = `screen_window_t`，
  `platform_display_native` = `screen_context_t`，直接传给
  `vkCreateScreenSurfaceQNX`；PAL 请求 `VK_KHR_surface` 和
  `VK_QNX_screen_surface`，失败时清空输出 surface；
- 文本/IME、剪贴板、显示器枚举、相对鼠标仍是 fail-closed 桩；真实 Screen
  键盘/指针事件注入尚未完成，纯键映射测试不等于交互运行收据。

## 3. TDD 记录

| 循环 | 红 | 绿 |
|------|----|----|
| 平台描述符 | `test_platform_compat_qnx` 编译失败（枚举不存在） | `platform_compat.h` 增加 QNX 族 + `ENGINE_NET_LOOP_POLL` |
| poll 后端 | `test_net_loop_qnx` 配置失败（后端源不存在） | `net_loop_poll.c` 实现 + 故障注入钩子 |
| 平台接线 | 宿主 QNX 模拟构建失败（`task.c` nanosleep、`platform_vk_surface.c` unused-function、测试目标缺 qnx 分支） | 引擎/测试 CMake qnx 分支 + `pvk_resolve` WSI 条件定义 |
| 效率冒烟 | `test_qnx_perf_smoke`（新） | 三条吞吐下限断言 + 实测打印 |
| 宿主 CI | Windows 构建 `test_qnx_perf_smoke` 失败（无 `poll.h`/`sys/socket.h`/`clock_gettime`）；macOS `_SC_NPROCESSORS_ONLN` 被 `_POSIX_C_SOURCE` 隐藏 | 该目标仅在 linux/macos/qnx 构建；macOS 追加 `_DARWIN_C_SOURCE` |
| 真实 SDP 交叉编译 | qcc 构建失败：`_SC_NPROCESSORS_ONLN`/`CLOCK_MONOTONIC` 被 `-std=c11` 严格模式隐藏；`-lpthread`/`-ldl` 不存在（QNX 8 并入 libc）；独立网络测试缺 `-lsocket`；`__isfinitef` 需 `-lm` | toolchain 加 `-D_QNX_SOURCE` + 交叉 binutils；qnx 分支去 pthread/dl、补条件 socket/m 链接 |
| 目标机运行 | 首轮 127/137：4 个 Memory fault（QNX 默认栈过小）、6 个数据路径/参数问题 | 运行器 `ulimit -s 8192`（README 的 8MB 栈假设）；`ENGINE_TEST_SOURCE_ROOT` 可覆盖 + 目标机部署布局；ctest 参数/WILL_FAIL 语义纳入运行器 → **144/144** |
| Screen 窗口层 | `test_platform_compat_qnx_screen` 编译失败（`ENGINE_SURFACE_QNX_SCREEN` 不存在） | `platform_compat.h` 增加枚举与 ENGINE_QNX_SCREEN 描述符变体；`window_screen.c` 双架构交叉编译 100% |
| Screen 键映射 | `test_screen_keymap` 编译失败（头不存在） | `screen_keymap.h` 纯整数映射 + `_Static_assert` 钉死 `<sys/keycodes.h>` 镜像 |
| 目标机 test_vfs 偶发 | qnx6 `ftruncate` 按剩余空间截断却返回成功 → >MAX 前置条件静默失效 | 测试前置校验实际文件大小（文件系统给不出 >MAX 稀疏文件时跳过断言；引擎逻辑本身正确） |
| QNX Vulkan 描述符/WSI | 旧 WSI 源码契约失败、缺少 QNX usage/后端标识 | 描述符变体、ABI 对照、5 个无 GPU 创建用例及 QNX WSI 生命周期变体 |
| Screen 初始化失败清理 | 注入 SIZE 设置失败后 `platform_create` 仍返回非 NULL | SIZE/FORMAT/USAGE/flush 全部检查返回值；失败时三个句柄各销毁一次，运行时 2/2 |
| 目标运行器隔离 | `BREAK_QNX_TARGET_ROOT` 探针仍进入固定 `/tmp/bt`，退出码 2 | 运行器支持独立部署根路径，默认 `/tmp/bt` 不变；宿主探针通过 |
| 测试源码根 | `test_shader_io` 在目标机读不到 shader（21 项失败） | shader/source 均优先读取 `TEST_SOURCE_ROOT`，保留旧回退；目标定向 58/58 |
| 运行器假绿 | 缺失命令清单返回 0 并打印 0/0 | 缺失/不可读清单和空清单均退出 2；正常探针 1/1 |

## 4. 构建

### 4.1 QNX SDP 交叉编译（目标机）

需要 QNX SDP（本文验证使用 8.0.0，qcc/gcc 12.2）。默认配置是 headless，
即使 SDP 探测到 Screen 也不会自动启用 GPU：

```bash
source /opt/qnx800/qnxsdp-env.sh   # 按实际 SDP 安装位置设置 QNX_HOST/QNX_TARGET
cmake -S engine -B /tmp/build-qnx \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-qnx.cmake" \
  -DQNX_ARCH=x86_64 \
  -DENGINE_TEST_SOURCE_ROOT=/tmp/break-qnx-validation
cmake --build /tmp/build-qnx -j
```

`QNX_ARCH` 可选 `aarch64le`（preset 默认）/`x86_64`/`armle`；也可使用
`engine/CMakePresets.json` 的 `qnx-cross`。toolchain 自动选用交叉 binutils，
并定义 `_QNX_SOURCE`，不再给 q++ 传已弃用的 `-lang-c++`。

**在目标机跑 headless 套件**（脚本位于 `engine/tools/qnx/`）：

1. 选择部署根（通常 `/tmp/bt`，也可用独立测试盘上的目录），配置时把
   `ENGINE_TEST_SOURCE_ROOT` 指向该根；
2. 部署清单中的二进制，并保留源目录形状：`engine/src` → `<root>/src`、
   `engine/shaders` → `<root>/shaders`、`engine/tests/data` →
   `<root>/tests/data`、`engine/assets` → `<root>/assets`。仅复制
   `tests/data` 到根目录会生成错误的 `<root>/data`；全新 VM 上不能依赖旧目录；
3. 将 `<根父目录>/src` 链接到 `<root>/src`（例如 `/tmp/bt` 使用 `/tmp/src`），
   满足部分测试的 `../src` 回退读取。默认/Vulkan 配置应使用不同部署根，
   避免覆盖二进制和混用 shaderc；不同源码树并发验证应使用独立 VM；
4. 宿主生成清单：
   `python3 engine/tools/qnx/gen_target_cmds.py <build-dir> "$PWD/engine" <root> cmds.txt`。
   它复刻 `-LE "graphics|fuzz"`，剔除宿主 CMake 脚本测试并保留 WILL_FAIL；
5. 将清单复制为 `<root>/cmds.txt`，目标侧运行：
   `BREAK_QNX_TARGET_ROOT=<root> sh <root>/run_target_suite.sh cmds.txt`。
   运行器设置 8 MiB 栈和正确的动态库路径，EXPECT_FAIL 的非零退出计为通过；
6. graphics 标签测试不在清单内，必须另外部署和运行（见 §4.3）。部署前用
   `df -h` 和 `df -g` 同时检查块与 inode；QNX6 可在有空闲块时因 inode 用尽
   返回 ENOSPC。

### 4.2 宿主 QNX 平台模拟（无 SDP 时验证接线）

用一个声明 `CMAKE_SYSTEM_NAME=QNX`、实际用宿主 gcc 的工具链文件配置，
引擎按 qnx 平台分支编译（poll 后端、headless RHI、dummy PAL），
全部 headless 测试照常运行。它验证平台接线与 POSIX 代码路径，
**不**验证 qcc 工具链与 Neutrino 目标机运行时——那需要 §4.1 与真机。

### 4.3 显式 Vulkan、shaderc 与 Screen 运行时

本次用 shaderc v2025.3（提交 `8c2e602ce440b7739c95ff3d69cecb1adf6becda`，
依赖由该提交的 DEPS 固定）构建目标库，不修改第三方源码：

```bash
export SHADERC_SRC=/tmp/shaderc-qnx-v2025.3
# 在该源码目录执行一次 python3 utils/git-sync-deps，拉取 DEPS 固定的依赖。
cmake -S "$SHADERC_SRC" -B /tmp/shaderc-qnx-x86 \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-qnx.cmake" \
  -DQNX_ARCH=x86_64 -DCMAKE_BUILD_TYPE=Release \
  -DSHADERC_SKIP_TESTS=ON -DSHADERC_SKIP_EXAMPLES=ON \
  -DSHADERC_SKIP_EXECUTABLES=OFF -DSHADERC_SKIP_COPYRIGHT_CHECK=ON \
  -DSHADERC_SKIP_INSTALL=OFF
cmake --build /tmp/shaderc-qnx-x86 --target shaderc_shared -j
```

保持上游安装/可执行目标的默认组合，避免非默认组合的安装导出问题。
aarch64le 只替换 `QNX_ARCH` 和构建目录。随后配置完整 Vulkan 引擎：

```bash
cmake -S engine -B /tmp/build-qnx-vk \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-qnx.cmake" \
  -DQNX_ARCH=x86_64 -DENGINE_RHI_BACKEND=vulkan \
  -DENGINE_TEST_SOURCE_ROOT=/tmp/break-qnx-validation \
  -DSHADERC_LIB=/tmp/shaderc-qnx-x86/libshaderc/libshaderc_shared.so \
  -DSHADERC_INCLUDE_DIR="$SHADERC_SRC/libshaderc/include"
cmake --build /tmp/build-qnx-vk -j
```

目标侧还需部署 `libvulkan.so.1`、`libscreen.so.1`、SONAME 为
`libshaderc_shared.so.1` 的库及 `libc++.so.2`。从 Vulkan 构建重新生成清单；
`test_qnx_shaderc` 在目标 CPU 上把真实顶点/片元 GLSL 编译为 Vulkan 1.2 /
SPIR-V 1.5，检查魔数与 4 字节对齐，**不需要也不证明 GPU**。

Screen 软件虚拟显示器的依赖闭包由脚本收集：

```bash
python3 engine/tools/qnx/stage_screen_runtime.py --output /tmp/qnx-screen-runtime
# 将整个 qnx-screen-runtime 目录部署到目标机，并进入测试二进制所在目录。
export LD_LIBRARY_PATH=/tmp/qnx-screen-runtime/lib:/tmp/qnx-screen-runtime/usr/lib:/tmp/qnx-screen-runtime/lib/dll:$PWD
/tmp/qnx-screen-runtime/sbin/screen \
  -c /tmp/qnx-screen-runtime/graphics-virtual-display.conf &
BREAK_QNX_SCREEN_REQUIRED=1 ./test_platform_qnx_screen_runtime
```

脚本不安装 Vulkan ICD。`graphics-headless.conf` 在当前 VM 上不能创建窗口
（errno 48），所以运行测试使用 `graphics-virtual-display.conf`。测试不可用时
默认返回 77；`BREAK_QNX_SCREEN_REQUIRED=1` 将这种情况变为失败，防止把缺少
服务静默记为通过。真实窗口测试不包含 GPU present、真实输入注入或物理显示器。

## 5. 已验证状态（2026-10-26，分支 feat/qnx-compat）

以下为当前源码、隔离 VM 与独立文件系统上的最终复验结果：

- **Linux 宿主回归（含远端 master 的 R703–R706 LOD 工作）：178/178 通过**
  （`-LE "graphics|fuzz"`；`test_d3d12_dependency_gate` 为 Windows-only
  设计内跳过）；
- **QNX SDP 8.0.0 x86_64 默认配置：全树 100% 构建**，目标机
  **151/151 命令通过**，覆盖引擎核心、net_loop/network、task、规则引擎、
  LOD/LOD cache/MSFT_lod、全部 myui headless 用例和 verify 工具的
  WILL_FAIL 语义；
- **QNX x86_64 完整 Vulkan 配置：全树 100% 构建**，目标机
  **152/152 命令通过**（默认清单 + `test_qnx_shaderc`）。默认与 Vulkan
  使用不同部署根，`test_shader_io` 前后校验和一致；
- **真实 Screen 窗口：2/2 通过**。软件虚拟显示器上创建/查询/显示/销毁
  `screen_context`、`screen_window`，尺寸/格式/usage/WSI 状态正确；
  注入 SIZE/FORMAT/USAGE/flush 失败时 context/window/event 各清理一次；
  显式 Vulkan 构建下 `SCREEN_USAGE_VULKAN` 断言通过；
- **目标侧 shaderc：2/2 通过**（真实 GLSL 顶点/片元 → Vulkan 1.2 /
  SPIR-V 1.5，检查魔数和 4 字节对齐）。x86_64 与 aarch64le 的
  `libshaderc_shared.so.1` 均用最终 toolchain 从固定 v2025.3 源码干净构建；
- **aarch64le：默认与完整 Vulkan 配置均全树 100% 构建**，产物经 `file`
  确认为 AArch64 QNX 动态可执行；本环境无 aarch64le 目标机，仍为
  COMPILED 证据；
- **GPU 运行时未通过且未误计**：显式部署并运行 `test_vulkan`，`engine_init`
  成功后在 Vulkan 设备创建处失败——loader 报 required instance extension
  `VK_KHR_surface` unavailable；`vulkaninfo --summary` 同样
  `vkEnumerateInstanceVersion failed with ERROR_INITIALIZATION_FAILED`。
  当前 VM/SDP 只有 Vulkan loader 和 Screen 软件后端，没有 ICD/GPU；
- 未验证边界：aarch64le 目标运行、非 VM 真硬件、GPU/交换链/present、
  myui 原生 Screen PAL、真实输入注入、文本/IME、剪贴板、显示器枚举、
  相对鼠标。不能把本节描述为“QNX 全部功能已验证”。

历史目标机计数从 144/144 逐步扩展到 150/150；中间 147/150、148/151 等
失败均已定位：部署目录缺少 `tests/data`、`../src`/shader 回退路径错误、
或部署清单缺失。相关修复与防假绿检查见 §3。

## 6. 效率验证（test_qnx_perf_smoke）

断言的吞吐下限（刻意宽松，sanitizer/慢 CI 下仍成立）与目标机实测：

| 子系统 | 断言下限 | 首轮 x86_64 VM | 隔离 VM 复验 | 合并 master 后最终复验 |
|--------|---------|----------------|---------------|-------------------------|
| poll net_loop 数据报 | ≥256/s | 61,918 datagrams/s | 37,766 datagrams/s | 74,603 datagrams/s |
| task 系统（2 worker） | ≥5,000/s | 1,775,253 tasks/s | 568,877 tasks/s | 998,901 tasks/s |
| myui 离屏 vg 管线 | ≥20,000 ops/s | 97,799,511 vg ops/s | 50,314,465 vg ops/s | 107,526,882 vg ops/s |

三次均在 QNX 8.0.0 x86_64 QEMU/KVM、qcc/gcc 12.2 -O3 下通过；这是
headless CPU/离屏吞吐收据，不是 GPU benchmark。后续运行继续把打印值
回填本表，证据分级对齐 `docs/rhi_backend_evidence.md`。

## 7. 升级路径（后续里程碑）

1. ~~SDP 交叉编译 + x86_64 目标 headless 套件~~：已完成（§5）；
   aarch64le 仍只有 COMPILED，需对应目标机运行；
2. ~~Screen 窗口运行收据~~：软件虚拟显示器 NATIVE_SURFACE 已完成；
   仍缺物理显示器、真实键盘/指针事件注入、文本/IME、剪贴板、显示器
   枚举和相对鼠标；
3. GPU/ICD 里程碑：安装目标侧 Vulkan ICD 或提供真实 GPU 后重跑
   `test_vulkan` 与交换链/present 路径；当前失败是环境能力缺失，不改
   测试或文档把它写成通过；
4. myui Screen PAL：当前仍为 dummy PAL 离屏路径；引擎 Screen WSI 不等于
   myui 原生窗口/GPU 后端；
5. `ENGINE_NET_LOOP_POLL` 在高 fd 数下的 tunable（稳态零数组重建已实现）；
6. 目标机套件纳入日常验证（可选 qconn/ssh CI lane；并发不同源码树仍应
   使用独立 VM 或独立源码根）。

## 8. 相关文件

- 平台描述符/契约：`engine/src/platform/platform_compat.h`、
  `engine/tests/test_platform_compat_simulated.c`
- QNX Vulkan WSI/ABI：`engine/src/platform/platform_vk_surface.c`、
  `engine/src/platform/platform_vk_surface_vkabi.h`、
  `engine/tests/test_platform_vk_surface_qnx.c`、
  `engine/tests/test_platform_vk_surface_abi.c`
- WSI 生命周期：`engine/src/platform/platform_wsi.h`、
  `engine/tests/test_platform_wsi_lifecycle.c`
- Screen 窗口层与运行测试：`engine/src/platform/window_screen.c`、
  `engine/tests/test_platform_qnx_screen_runtime.c`
- shaderc 目标测试：`engine/tests/test_qnx_shaderc.c`
- 效率冒烟：`engine/tests/test_qnx_perf_smoke.c`
- 目标机工作流：`engine/tools/qnx/gen_target_cmds.py`、
  `engine/tools/qnx/run_target_suite.sh`、
  `engine/tools/qnx/stage_screen_runtime.py`
- 工具链：`engine/toolchain-qnx.cmake`、`engine/CMakePresets.json`
