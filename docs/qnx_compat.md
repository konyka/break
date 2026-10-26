# QNX 平台兼容（feat/qnx-compat，2026-10-26）

QNX Neutrino 目标的第一个里程碑：**headless 兼容层**。引擎核心与 myui
（dummy PAL 离屏路径）以 QNX 平台定义编译并可在无显示环境运行；窗口/图形
保持 fail-closed，直到集成 Screen WSI。本文记录架构决策、TDD 过程、
验证状态与目标机操作步骤。

**2026-10-26 真机收据**：QNX SDP 8.0.0（qcc/gcc 12.2）x86_64 交叉编译
100% 通过；全部 headless 测试（144 条命令，含 WILL_FAIL 语义）在
QNX 8.0.0 Neutrino x86_64 目标机（QEMU/KVM VM）上 **144/144 通过**，
证据等级由 COMPILED 升级为 **HEADLESS**。

## 1. 范围与证据等级

| 能力 | 状态 | 证据 |
|------|------|------|
| 平台描述符（`ENGINE_TARGET_FAMILY_QNX`） | 契约锁定 | `test_platform_compat_qnx`（模拟）、`test_platform_compat`（真机，通过） |
| net_loop（POSIX `poll()` 后端） | 全量语义验证 | `test_net_loop_qnx` 宿主 CI + `test_net_loop`/`test_net_replication` 真机通过 |
| 引擎核心（task/time/filewatch/network/audio/script/…） | **真机全量 HEADLESS** | QNX 8.0.0 x86_64 目标机 144/144（见 §5） |
| myui（widget/layout/css/edit/echart/mvvm/离屏 vgcanvas） | **真机全量 HEADLESS** | 同上（myui 全部 headless 测试在目标机通过） |
| 效率（吞吐下限断言） | 真机冒烟锁定 | `test_qnx_perf_smoke` 目标机实测见 §6 |
| 窗口 / 图形 / Vulkan | **UNAVAILABLE，fail-closed** | `ENGINE_VULKAN=ON` 于 qnx 配置期直接 FATAL；RHI 解析为 `headless` |

窗口/图形升级到 Screen WSI 的路径见 §7。

## 2. 架构决策

### 2.1 平台描述符（`engine/src/platform/platform_compat.h`）

```
TARGET_FAMILY = QNX          NET_LOOP = POLL
SURFACE      = UNAVAILABLE   REQUIRES_HOST_SURFACE = 0
GRAPHICS_API = NONE          NATIVE/TARGET_GRAPHICS_API = NONE
VULKAN       = UNAVAILABLE   SUPPORT_EVIDENCE = COMPILED
```

`REQUIRES_HOST_SURFACE = 0` 与 OHOS（=1）刻意不同：QNX 里程碑是
headless 可运行，不需要也不接受宿主注入 surface；图形入口全部 fail-closed。

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

### 2.3 headless RHI 解析

`ENGINE_RHI_BACKEND` 在 qnx 平台只接受 `auto`，解析结果为 `headless`：

- 显式 opengl/vulkan/metal/d3d12 → 配置期 FATAL（fail-closed，不静默回退）；
- `ENGINE_VULKAN=ON` → 配置期 FATAL（无 Screen/Vulkan WSI）;
- `engine_link_rhi_backend()` 增加 `headless` 分支链接 `engine_rhi_headless`
  （全入口 fail-closed），保持构建图在目标上完整。

### 2.4 平台层与系统库

- `window_mobile.c` 守卫扩展到 QNX：提供全部 `platform_*` 符号，
  `platform_create` 在无宿主 native window 时返回 NULL（fail-closed）；
- filewatch 走可移植轮询回退分支（无 inotify）；
- QNX socket API 在 libsocket：`check_library_exists` 探测式链接
  （glibc/macOS 宿主模拟时在 libc，自动跳过）；
- 引擎编译定义 `ENGINE_PLATFORM_QNX=1 _POSIX_C_SOURCE=200112L`。

### 2.5 myui

- `MYUI_PAL` 默认 `dummy`（离屏、确定性），与 QNX headless 形态一致；
- `MYUI_GLES2` / `MYUI_GL_DESKTOP` / `MYUI_VULKAN` 探测仅限
  linux/win32，qnx 自动跳过（无窗口系统）；
- myui 全部 headless 测试（布局/CSS/编辑器/echart/MVVM/窗口管理/指标）
  与平台无关，QNX 平台定义下原样通过。

## 3. TDD 记录

| 循环 | 红 | 绿 |
|------|----|----|
| 平台描述符 | `test_platform_compat_qnx` 编译失败（枚举不存在） | `platform_compat.h` 增加 QNX 族 + `ENGINE_NET_LOOP_POLL` |
| poll 后端 | `test_net_loop_qnx` 配置失败（后端源不存在） | `net_loop_poll.c` 实现 + 故障注入钩子 |
| 平台接线 | 宿主 QNX 模拟构建失败（`task.c` nanosleep、`platform_vk_surface.c` unused-function、测试目标缺 qnx 分支） | 引擎/测试 CMake qnx 分支 + `pvk_resolve` WSI 条件定义 |
| 效率冒烟 | `test_qnx_perf_smoke`（新） | 三条吞吐下限断言 + 实测打印 |
| 真实 SDP 交叉编译 | qcc 构建失败：`_SC_NPROCESSORS_ONLN`/`CLOCK_MONOTONIC` 被 `-std=c11` 严格模式隐藏；`-lpthread`/`-ldl` 不存在（QNX 8 并入 libc）；独立网络测试缺 `-lsocket`；`__isfinitef` 需 `-lm` | toolchain 加 `-D_QNX_SOURCE` + 交叉 binutils；qnx 分支去 pthread/dl、补条件 socket/m 链接 |
| 目标机运行 | 首轮 127/137：4 个 Memory fault（QNX 默认栈过小）、6 个数据路径/参数问题 | 运行器 `ulimit -s 8192`（README 的 8MB 栈假设）；`ENGINE_TEST_SOURCE_ROOT` 可覆盖 + 目标机部署布局；ctest 参数/WILL_FAIL 语义纳入运行器 → **144/144** |

## 4. 构建

### 4.1 QNX SDP 交叉编译（目标机）

需要 QNX SDP 7.1/8.0（`qcc`/`q++`）：

```bash
source /opt/qnx800/qnxsdp-env.sh   # 设置 QNX_HOST / QNX_TARGET
cmake --preset qnx-cross           # engine/CMakePresets.json：aarch64le 默认
cmake --build engine/build-qnx -j
```

`QNX_ARCH` 可选 `aarch64le`（默认）/`x86_64`/`armle`。toolchain 自动选用
`nto<arch>-ar/ranlib/strip` 交叉 binutils，并在 `-std=c11` 严格模式下补
`-D_QNX_SOURCE`（否则 `_SC_NPROCESSORS_ONLN`、QNX 的 `CLOCK_MONOTONIC`
暴露等被隐藏）。

**在目标机跑 headless 套件**（本次验证用的工作流，x86_64 QEMU/KVM VM；
脚本已入库 `engine/tools/qnx/`）：

1. 配置目标构建时指向目标机上的源码副本（供读取仓库源码/资产的测试）：
   `-DENGINE_TEST_SOURCE_ROOT=/tmp/bt`；
2. 把构建产物二进制 + `engine/{src,shaders}` + `tests/data` + 字体
   `assets/LiberationSans-Regular.ttf` 推到目标机 `/tmp/bt`（cwd 即 `/tmp/bt`，
   `read_engine_source` 的 `../src` 候选路径用 `/tmp/src -> /tmp/bt/src`
   符号链接满足）；
3. 宿主侧生成命令清单：
   `python3 engine/tools/qnx/gen_target_cmds.py <build-dir> <engine> /tmp/bt cmds.txt`
   （等价复刻 `-LE "graphics|fuzz"` 选择，剔除需宿主 CMake 运行时的
   `cmake -P` 契约测试，标注 `WILL_FAIL` 语义）；
4. 目标机侧运行：`sh run_target_suite.sh cmds.txt`——要点：
   `ulimit -s 8192`（QNX 默认栈远小于 Linux 8MB 假设，大局部数组测试会
   Memory fault）；`EXPECT_FAIL` 前缀测试的非零退出计为通过。

### 4.2 宿主 QNX 平台模拟（无 SDP 时验证接线）

用一个声明 `CMAKE_SYSTEM_NAME=QNX`、实际用宿主 gcc 的工具链文件配置，
引擎按 qnx 平台分支编译（poll 后端、headless RHI、dummy PAL），
全部 headless 测试照常运行。它验证平台接线与 POSIX 代码路径，
**不**验证 qcc 工具链与 Neutrino 目标机运行时——那需要 §4.1 与真机。

## 5. 已验证状态（2026-10-26，分支 feat/qnx-compat）

- Linux 宿主基线（改动前 master）：headless 套件 168 项全绿；
- 宿主 QNX 平台模拟树：全量构建通过；headless 套件 168 项全绿
  （`test_d3d12_dependency_gate` 为 Windows-only 设计内跳过）；
- **真实 QNX SDP 8.0.0 交叉编译（qcc/gcc 12.2）：x86_64 与 aarch64le
  双架构整树 100% 构建通过**（aarch64le 为 COMPILED 证据——本环境无
  aarch64 目标机可运行；产物经 `file`/`ntoaarch64-strip` 校验为
  AArch64 QNX 动态可执行）；
- **QNX 8.0.0 Neutrino x86_64 目标机（QEMU/KVM VM）：headless 套件
  144/144 命令通过**（含 myui 全部 headless 测试、net_loop/net/network/
  net_replication、task/ECS/规则引擎、verify 工具的 WILL_FAIL 语义用例；
  等价于宿主 `-LE "graphics|fuzz"` 选择，宿主-only 的 cmake 契约测试不在
  目标机复刻）。目标机运行要点与运行器语义见 §4.1（脚本已入库
  `engine/tools/qnx/`）；
- 未验证（诚实边界）：aarch64le 目标机运行、非 VM 真硬件收据、
  图形/Screen 路径（设计即 fail-closed）。

## 6. 效率验证（test_qnx_perf_smoke）

断言的吞吐下限（刻意宽松，sanitizer/慢 CI 下仍成立）与实测值：

| 子系统 | 断言下限 | 宿主参考（16 核 Linux, gcc -O3） | **QNX 8.0 目标机实测**（x86_64, KVM VM, qcc/gcc 12.2 -O3） |
|--------|---------|----------------------------------|------------------------------------------------------------|
| poll net_loop 数据报 | ≥256/s | 397,824 datagrams/s | **61,918 datagrams/s** |
| task 系统（2 worker） | ≥5,000/s | 3,818,980 tasks/s | **1,775,253 tasks/s** |
| myui 离屏 vg 管线 | ≥20,000 ops/s | 279,720,280 vg ops/s | **97,799,511 vg ops/s** |

目标机整套 144 项测试 7.6 秒跑完（含全部 myui headless 用例）。
目标机后续运行把打印值继续回填本表即可累积收据（对齐
`docs/rhi_backend_evidence.md` 的证据分级习惯）。

## 7. 升级路径（后续里程碑）

1. ~~真机：SDP 交叉编译 + Neutrino 目标跑套件与冒烟~~（已完成，2026-10-26：
   x86_64 交叉 100% + 目标机 144/144 + §6 收据；aarch64le 交叉 100%
   （COMPILED），aarch64le 目标机运行与非 VM 真硬件收据待补）；
2. Screen WSI：`window_screen.c` + `ENGINE_SURFACE_*` 语义，
   图形证据等级从 NONE 起步；
3. Vulkan（QNX 平台 Vulkan driver via Screen）或 GLES2 后端：
   myui `MYUI_GLES2` 已是可复用后端，接入 Screen EGL；
4. `ENGINE_NET_LOOP_POLL` 在高 fd 数下的 tunable（当前重建仅发生在
   注册变更时，稳态零开销）；
5. 目标机套件纳入日常验证（可选：qconn/ssh 驱动的自建 CI lane）。

## 8. 相关文件

- 平台描述符/契约：`engine/src/platform/platform_compat.h`、
  `engine/tests/test_platform_compat_simulated.c`（SIMULATE_QNX）
- poll 后端：`engine/src/network/net_loop_poll.c`、
  `engine/tests/test_net_loop.c`（QNX 段）、`engine/tests/test_net_loop_qnx`（CMake 目标）
- 效率冒烟：`engine/tests/test_qnx_perf_smoke.c`
- 目标机套件工作流：`engine/tools/qnx/gen_target_cmds.py`（宿主生成命令清单）、
  `engine/tools/qnx/run_target_suite.sh`（目标机运行器）
- 工具链：`engine/toolchain-qnx.cmake`、`engine/CMakePresets.json`（`qnx-cross`）
- fail-closed 修复：`engine/src/platform/platform_vk_surface.c`（`pvk_resolve` 条件定义）、
  `engine/src/platform/window_mobile.c`（QNX 守卫）
