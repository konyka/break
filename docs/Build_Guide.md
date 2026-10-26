# Break Engine 构建与开发指南

## 1. 环境要求

### 1.1 编译器
- `engine/` 是严格 C11 项目；CMake 会选择 GCC、Clang/AppleClang 或 MSVC 的 C 编译器，并启用严格警告。仓库没有在 CMake 中声明 GCC 11 或 Clang 14 的最低版本，因此具体工具链仍需能编译 C11 原子和项目依赖。
- `framework/` 的 `common` 目标使用 C++11；仓库根 CMake 项目要求 CMake 3.25+。
- `engine/` 的 CMake 最低版本是 3.20+。Linux Clang Release 的 IPO/LTO 配置还需要 `lld`。

#### 编译器支持矩阵

| 平台 | 编译器 | 状态 | 工具链文件 | 备注 |
|------|--------|------|-----------|------|
| Linux | GCC | CI 验证 | (默认) | GCC X11/OpenGL、Vulkan、ASan/UBSan 配置见 CI |
| Linux | Clang + lld | CI 验证 | `toolchain-clang-linux.cmake` | Release 配置启用 IPO |
| Windows | MSVC (cl) | 支持 | `toolchain-msvc.cmake` | 原生 Windows 开发 |
| Windows | Clang | 支持 | `toolchain-clang-win.cmake` | clang + lld-link |
| Windows | MinGW GCC | 支持 | `toolchain-mingw.cmake` | Linux 交叉编译 |
| QNX | qcc/q++ (SDP 7.1/8.0) | headless + Screen；Vulkan COMPILED | `toolchain-qnx.cmake` | 默认 headless；显式 Vulkan 需要 Screen/shaderc，GPU runtime 待验证；见 `docs/qnx_compat.md` |

### 1.2 系统依赖（Linux）
- X11 开发库 (libx11-dev、libxrandr-dev) 或 Wayland 开发库（二选一，编译时互斥)；Wayland 还需要 xkbcommon、wayland-scanner 和 wayland-protocols
- OpenGL (libgl1-mesa-dev) 或 Vulkan SDK
- FreeType 开发库（推荐；`dxx_break` 默认 CJK TTC 字体和中文显示需要它）
- pthread
- 游戏手柄支持：evdev（Linux 内核内置，无需额外包）

### 1.3 系统依赖（Windows）
- Visual Studio 2019+ 或 MinGW
- Windows SDK
- DirectX 11 SDK (可选，用于 platform 演示)

### 1.4 macOS、iOS、Android、OHOS 与 QNX
- 平台图形元数据把性能基线与 Vulkan 证据分开：Linux/Windows 的 native baseline 是 OpenGL，macOS 是 Metal；macOS Vulkan 明确走 MoltenVK，不表示已实现 Metal RHI。Vulkan 证据级别使用 `compiled`、`headless`、`native-surface`、`GPU-runtime`、`benchmark-comparable`，不能把编译通过当作运行时支持。
- macOS 由 CMake 识别为 `macos`，当前 Cocoa Vulkan 路径使用 Vulkan loader/MoltenVK、`shaderc_shared` 和 FreeType；仓库的 macOS CI 安装 `molten-vk`、`shaderc`、`freetype`。
- iOS 由 CMake 识别为 `ios`，使用 kqueue 网络后端，但仓库没有声明 iOS runtime 或窗口渲染 CI 覆盖。
- Android 由 CMake 识别为 `android`，使用 epoll；Vulkan 是宿主注入的 compile/integration 路径。启用 `ENGINE_VULKAN=ON` 时必须同时设置 `ENGINE_ANDROID_NATIVE_WINDOW=ON`，并让 CMake 找到 NDK 的 `android/native_window.h`；这不代表完整 Android runtime 支持。
- iOS/Android 的平台契约测试只证明编译路径与宿主注入边界；HarmonyOS 的 Vulkan 状态为 unavailable/unsupported，直到存在 native surface 实现。
- QNX 由 CMake 识别为 `qnx`（`CMAKE_SYSTEM_NAME=QNX`），net_loop 使用 POSIX `poll()` 后端。默认 RHI 为 headless，myui 走 dummy PAL 离屏路径；SDP 提供 Screen 时启用原生窗口层。`ENGINE_RHI_BACKEND=vulkan` 或 `ENGINE_VULKAN=ON` 显式选择 Screen Vulkan WSI，需同时提供目标架构的 Vulkan/shaderc；其他显式后端配置期拒绝。交叉构建用 `cmake --preset qnx-cross`，命令、目标机运行和证据边界见 `docs/qnx_compat.md`。

## 2. 构建配置

### 2.1 引擎（主项目）

#### OpenGL 后端
```bash
cd engine
cmake -B build-gl
cmake --build build-gl
```

#### Vulkan 后端
```bash
cd engine
cmake -B build-vk -DENGINE_VULKAN=ON
cmake --build build-vk
```

#### D3D12 后端（Windows）
```bash
cd engine
cmake -B build-d3d12 -DENGINE_RHI_BACKEND=d3d12
cmake --build build-d3d12
```

## RHI 后端链接模型

- `engine` 静态库只含 `RHI_CORE_SOURCES`（rhi.c 调度/校验、ownership、validation、resources、present_history），不再编译任何后端源。
- 后端各自为独立静态库：`engine_rhi_opengl`（`src/rhi/rhi_gl.c` + glad + 平台 GL 库）、`engine_rhi_vulkan`（`src/rhi/rhi_vk.c`，链接 `Vulkan::Vulkan` + shaderc）、`engine_rhi_d3d12`（`src/rhi/rhi_d3d12.c` + `rhi_d3d12.h`，仅 Windows，链接 d3d12/dxgi/dxguid，Agility redist 由 POST_BUILD 部署）、`engine_rhi_headless`（`src/rhi/rhi_headless.c`，全入口 fail-closed，仅供契约/headless 测试链接，永不构成 GPU 证据）。
- 需要 RHI 的可执行 target 在其 `target_link_libraries` 之后调用 `engine_link_rhi_backend(<target>)`；headless 测试不调用该 helper，直接链接 `engine_rhi_headless`。
- 后端选择：`ENGINE_RHI_BACKEND=auto|opengl|vulkan|d3d12` 与 `ENGINE_VULKAN` 兼容层；`d3d12` 仅 Windows 可选（计划 D 已落地，见下方「Windows D3D12 后端（计划 D）」节），`metal` 在计划 C 落地前仍被拒绝（非 Apple 平台 FATAL_ERROR）。

## WSI / Vulkan surface 分层（2026-10-15 起）

- **`engine/src/platform/platform_vk_surface.h`** 是 PAL 的 Vulkan surface 创建适配层，两个入口：
  - `platform_vk_create_surface(Platform*, ...)`：经 Platform 句柄创建（内部解包 `platform_surface_native`/`platform_display_native` 后转发到 handles 入口）；
  - `platform_vk_create_surface_handles(surface_native, display_native, ...)`：经裸原生句柄创建——`rhi_vk.c` 的 `vk_init` 持有的是裸句柄而非 `Platform`（`rhi_device_create` 公开 ABI 不变），故消费本入口；结果 surface 的销毁权仍在 `rhi_vk.c`（`vkDestroySurfaceKHR`）。Android 路径成功时本入口对 `ANativeWindow` 持有一个 acquire 引用，失败路径自行 release 回滚。
  - uint64/void* 设计理由：分层规则要求 **platform 层不包含 `<vulkan/vulkan.h>`**——`VkInstance` 以 `void*` 传入、`VkSurfaceKHR`（不可分派 64 位句柄）以 `u64` 传出、`vkGetInstanceProcAddr` 以 `void*` 传入（调用方用 memcpy 桥接函数指针，避免 `-Wpedantic` 的函数指针/void* 强转）。六个平台的 `vkCreate*Surface*` create-info 最小 ABI 声明在 `platform_vk_surface_vkabi.h`，由 `test_platform_vk_surface_abi` 对照真实 `<vulkan/vulkan.h>` 逐字段钉死（漂移即编译期/测试期失败）。QNX 分支使用 `VK_QNX_screen_surface` / `vkCreateScreenSurfaceQNX`，context/window 来自 Screen PAL。
- **`engine/src/platform/platform_wsi.h`** 是 header-only 的 WSI 状态机（`PlatformWsiSurface`：UNAVAILABLE/CREATED/RESIZED/LOST/SUSPENDED/DESTROYING），事件源在各 `window_*.c`（Win32/X11/Wayland/Cocoa/Android/QNX Screen 后端均已接入）；尺寸语义（logical 与 drawable 谁是输入，各平台方向不同）由 `platform_size.h` 单点定义，`window_*.c` 只准调用。消费方式：
  - 帧进入 RHI 前查 `platform_wsi_frame_allowed()`——仅 CREATED/RESIZED 放行，SUSPENDED/LOST/DESTROYING/UNAVAILABLE 一律拒绝（应用层据此跳过渲染，而不是让后端在死 surface 上空转）；
  - 销毁门控：`rhi_device_attach_wsi()` 把状态机挂到设备上，`platform_wsi_rhi_teardown_allowed()` 在进入 DESTROYING 后拒绝销毁——销毁顺序契约为 `rhi_device_destroy_ex` 必须先于 `platform_destroy`。
- **`rhi_swapchain_bench`**（`engine/tools/rhi_swapchain_bench.c`）：`./build-*/rhi_swapchain_bench <receipt.json>`，固定 600 帧 clear+present，输出符合 `docs/rhi_benchmark_receipt_schema.md` 的收据（`fps_avg`/`fps_p1`/`frame_ms_avg`/`frame_ms_p99`/`evidence_level=GPU_RUNTIME`/`runner` 等字段）；环境缺显示/GPU 时以退出码 77 标记 unavailable（不算通过，也不产出收据）。元数据由环境变量注入：`RECEIPT_TIMESTAMP`、`RECEIPT_RUNNER`、`RECEIPT_OS_VERSION`、`RECEIPT_BUILD_CONFIG`、`GIT_COMMIT`、`RECEIPT_CPU`、`RECEIPT_RAM`；收据用 `cmake -DRECEIPT=<json> -P engine/tests/test_rhi_benchmark_receipt_validate.cmake` 校验。
- **`ENABLE_GPU_LANES`**：GitHub 仓库变量（Settings → Secrets and variables → Actions → Variables），置为 `1` 才启用 `steam-deck-vulkan-benchmark` lane（self-hosted `linux,gpu-vulkan` runner，跑 graphics 套件 + bench 收据 artifact）；未设置时该 lane 被 `if:` 跳过——GitHub-hosted 运行器没有 self-hosted 标签可接单，不加门会永久 pending。

平台契约与 profiler provenance sidecar 可用以下命令验证（不会修改
`profile_trace.json`）：

```bash
cmake --build build-vk --target test_platform_compat test_platform_compat_macos test_profiler
ctest --test-dir build-vk -R 'test_platform_compat|test_profiler' --output-on-failure
```

Windows 备注（2026-09-01 起可本机验证）：Vulkan SDK 可无头解包到
`engine/external/VulkanSDK/`（已加入本地 git 排除，勿提交）。Windows 下
`find_package(Vulkan)` 用 `VULKAN_SDK` 环境变量，或显式传
`-DVulkan_LIBRARY=<SDK>/Lib/vulkan-1.lib -DVulkan_INCLUDE_DIR=<SDK>/Include
-DSHADERC_LIB=<SDK>/Lib/shaderc_shared.lib`（Windows 分支的 shaderc 链接由
本仓库补齐，Linux/macOS 分支原本就有）；运行时把 `<SDK>/Bin` 加入 `PATH`
（shaderc_shared.dll），并设 `VK_LAYER_PATH=<SDK>/Bin` 让加载器找到
`VK_LAYER_KHRONOS_validation`。`test_vulkan` 通过 ctest 运行
（`ctest -R ^test_vulkan$`，工作目录须为 engine/ 源码根）即带进程内验证门：
任何验证警告/错误都会判负。

2026-10-17 起 `SHADERC_LIB`/`SHADERC_INCLUDE_DIR` 的自动发现也读取
`VULKAN_SDK` 环境变量（`$VULKAN_SDK/Lib`、`$VULKAN_SDK/Include`，与
`find_package(Vulkan)` 行为对齐），Windows 上不再需要显式传
`-DSHADERC_LIB=...`。CI `windows-clang` lane 用
`engine/tools/fetch_vulkan_sdk_windows.cmake` 静默安装固定版本的
LunarG SDK（1.4.321.0，SHA256 钉死，模式同
`fetch_d3d12_agility_sdk.cmake`）；升版本时版本号与哈希一起改。

设备选择：默认取第一块"caps 可查且可呈现"的 GPU（带兜底的回退到
gpus[0] + 回退 caps，见 rhi_vk.c R574/R575）；要强制指定某块卡（例如本机
AMD 核显的 caps 查询有驱动缺陷、需在 AMD 上验证），设
`RE_VK_DEVICE_INDEX=<n>`（枚举顺序见运行日志里的 Vulkan GPU 行）。

macOS 备注（2026-10-06 起可本机验证，R635）：macOS 加载器**不搜索
Vulkan SDK 目录树**，ICD/层 manifest 须装到加载器搜索路径才生效。本机
（`~/VulkanSDK` 1.4.357）的标准布局是：
`~/.local/share/vulkan/icd.d/MoltenVK_icd.json`（绝对路径指向
`~/VulkanSDK/macOS/lib/libMoltenVK.dylib`）与
`~/.local/share/vulkan/explicit_layer.d/VkLayer_khronos_validation.json`
（从 SDK 同名文件复制并把 `library_path` 改为绝对路径
`~/VulkanSDK/macOS/lib/libVkLayer_khronos_validation.dylib`——相对路径
`../../../lib/...` 只在 SDK 树内成立）。层 manifest 缺失时
`VK_LAYER_KHRONOS_validation` 静默缺席，验证门曾因此常年空转
（"0 messages ✓"是真空）；R635 起引擎在层缺席时 `LOG_WARN` 且门不亮。
`VK_LOADER_DEBUG=layer ./build-macos/test_vulkan` 可核对层是否插入。
同步验证（钓 WAR/RAW 命令间冒险，R633 事故类）以
`BREAK_VK_SYNC_VALIDATION=1 ./build-macos/test_vulkan` 开启（默认关：
有性能成本，属刻意硬化运行）；要求引擎以 Debug/ENGINE_VK_VALIDATION
构建，且层 manifest 已安装。

### 2.2 myui / duanxianxia 集成构建

`engine/src/myui` 与 `engine/apps/duanxianxia` 已作为引擎静态库和可执行目标
接入同一 CMake 工程：

```bash
cd engine

# OpenGL
cmake -B build-myui -DENGINE_BUILD_TESTS=OFF
cmake --build build-myui --target dxx_break break_myui myui_core dxx_core -j

# Vulkan
cmake -B build-myui-vk -DENGINE_BUILD_TESTS=OFF -DENGINE_VULKAN=ON
cmake --build build-myui-vk --target dxx_break break_myui -j

# Headless AA contract
cmake -B build-myui-aa -DENGINE_BUILD_TESTS=ON -DENGINE_VULKAN=OFF
cmake --build build-myui-aa --target test_myui_vgcanvas_backend -j
ctest --test-dir build-myui-aa -R '^test_myui_vgcanvas_backend$' --output-on-failure

# Headless myui 测试
cmake -B build-myui-tests -DENGINE_BUILD_TESTS=ON -DENGINE_VULKAN=OFF
cmake --build build-myui-tests \
  --target test_break_ui_input test_break_ui_damage test_myui_vggeometry \
           test_myui_window_manager test_myui_break_pal test_myui_font \
           test_imgui_compat -j
ctest --test-dir build-myui-tests \
  -R 'test_(break_ui_input|break_ui_damage|myui_vggeometry|myui_window_manager|myui_break_pal|myui_font|imgui_compat)' \
  --output-on-failure
```

`dxx_break` 自动选用平台的简体中文字库；使用自定义 TTC 时可设置
`BREAK_MYUI_FONT=/path/to/font.ttc` 与 `BREAK_MYUI_FONT_FACE=2`。若 CMake 未找到
FreeType，独立 TTF/OTF 仍可通过 `stb_truetype` 使用，但可变 TTC（包括 Linux 的
Noto Sans CJK）不可用。

详细架构、渲染后端与 IME 状态见 `docs/myui_integration.md`。

### 2.3 CMake 选项

`engine/CMakeLists.txt` 当前提供以下选项：

| 选项 | 默认值 | 说明 |
|------|--------|------|
| `ENGINE_ENABLE_WAYLAND` | OFF | Linux 原生 Wayland，关闭时使用 X11 |
| `ENGINE_ENABLE_IPO` | ON | Release 且工具链支持时启用 IPO/LTO |
| `ENGINE_NET_IOURING` | OFF | Linux 实验性 io_uring 网络后端 |
| `ENGINE_ANDROID_NATIVE_WINDOW` | OFF | Android supplied `ANativeWindow` Vulkan 路径 |
| `ENGINE_VULKAN` | OFF | 使用 Vulkan 后端，并查找 Vulkan 与 shaderc |
| `ENGINE_BUILD_TESTS` | ON | 构建 engine 单元测试 |
| `ENGINE_USE_ASAN` / `ENGINE_USE_UBSAN` / `ENGINE_USE_TSAN` | OFF | 分别启用地址、未定义行为、线程消毒器 |
| `RULE_ENGINE_ENABLE_C11_PARALLEL` | OFF | 可选 C11 规则匹配执行器 |
| `RULE_ENGINE_ENABLE_REDIS` | OFF | hiredis 状态提供器；不提供 live Redis 服务 |
| `RULE_ENGINE_REDIS_SOURCE_DIR` | 空 | 可选 Redis/hiredis 源码目录，用于构建私有 hiredis 静态目标 |
| `MYUI_FONT_STB` / `MYUI_FONT_FREETYPE` / `MYUI_IMAGE_STB` | ON | myui 字体与图像后端 |
| `MYUI_UI_YAML` / `MYUI_BIDI` / `MYUI_HARFBUZZ` | ON | YAML、BiDi、可选 OpenType shaping |
| `MYUI_GLES2` / `MYUI_GL_DESKTOP` | ON | 可复用 myui GLES2、桌面 OpenGL 后端 |
| `MYUI_VULKAN` | OFF | 可复用 myui Vulkan 后端 |

软件后端默认使用 8-bit 覆盖率抗锯齿；X11/Wayland EGL 配置优先请求 4x MSAA，驱动不
支持时回退到单采样。GLES2/桌面 GL 的实际能力由上下文报告，Vulkan/RHI 的能力由实际
color/depth sample count 报告。上述命令验证软件像素覆盖率和能力契约；GL/VK 窗口及
复杂 MRT/shadow 路径仍需对应运行时设备，不能由 headless 测试代替。

关闭的可选后端不会执行对应依赖探测。TSAN 是本地配置选项，不是当前 CI gate。

### 2.2.1 Rule-engine core

The rule engine is a standalone C99 core target. `rule_engine_core` contains
only `engine/src/rule_engine/`; it has no graphics, UI, or Lua dependency.
The focused test, benchmark, and strict public-header consumer are built with:

```bash
cmake -S engine -B build-rule -DENGINE_BUILD_TESTS=ON -DENGINE_ENABLE_IPO=OFF
cmake --build build-rule --target test_rule_engine rule_engine_bench rule_engine_c99_consumer
ctest --test-dir build-rule -R test_rule_engine --output-on-failure
```

Run `rule_engine_bench` manually; its timing output is not a CTest regression
claim. The implemented local scope and deferred upstream families are listed in
`docs/Rule_Engine_Architecture.md` and `docs/rule_engine_conformance.yml`.
The public API contract is in `docs/Rule_Engine_Design.md`; upstream-only
evidence is in `docs/rule_engine_upstream.yml`.

The hardening gate adds bounded `rule_engine_fuzz_smoke` and, when
`RULE_ENGINE_ENABLE_C11_PARALLEL=ON` with `<threads.h>`,
`test_rule_engine_executor_stress`. The serial-vs-parallel callback trace check
remains in `test_rule_engine`. ASan/UBSan presets are in
`engine/CMakePresets.json`; configure or runtime failures mean unavailable
evidence, not a passing sanitizer gate. Redis is intentionally OFF by default.
`RULE_ENGINE_ENABLE_REDIS=ON` checks for hiredis headers and a library at
configure time. When both are found, the native adapter is compiled and linked;
when either is missing, CMake force-disables the option without a fallback.
Dependency discovery does not provide a live Redis integration service.
For a source checkout such as Redis 8.10.1, set
`-DRULE_ENGINE_REDIS_SOURCE_DIR=/home/timeshift/opensource/redis-8.10.1`.
This builds a private static hiredis target from `deps/hiredis`, avoiding a
system install and keeping the Redis client out of the public ABI.
The adapter validates `RE_REDIS_URL` (maximum 4096 bytes and a maximum 128-byte
`prefix`), bounds keys to 4096 bytes and values to 16 MiB, and rejects operation
timeouts longer than 24 hours before allocating or connecting. A non-zero
`operation_timeout_ms` configures both connect and blocking command socket
timeouts; timeout failures are exposed as `RE_PROVIDER_ERROR_TIMEOUT`, while
other connection or command failures remain `RE_PROVIDER_ERROR_UNAVAILABLE`.
Zero keeps hiredis's no-command-timeout behavior and should only be used when
the caller controls the surrounding operation lifetime. These are local safety
limits; a missing client still force-disables the option without fallback.

### 2.3 Wayland 后端构建

依赖安装 (Fedora):
```bash
sudo dnf install wayland-devel wayland-protocols-devel libxkbcommon-devel mesa-libEGL-devel
```

依赖安装 (Ubuntu/Debian):
```bash
sudo apt install libwayland-dev wayland-protocols libxkbcommon-dev libegl1-mesa-dev
```

构建命令:
```bash
cd engine
cmake .. -DENGINE_ENABLE_WAYLAND=ON                    # Wayland + OpenGL
cmake .. -DENGINE_ENABLE_WAYLAND=ON -DENGINE_VULKAN=ON # Wayland + Vulkan
```

> ⚠️ **注意**：`ENGINE_ENABLE_WAYLAND` 与 X11 后端为**编译时互斥选项**，不可同时启用。默认为 OFF（使用 X11）。
Wayland 后端通过 EGL 提供 OpenGL 上下文，通过 `VK_KHR_wayland_surface` 提供 Vulkan 支持。CMake 会调用 `wayland-scanner` 从 `wayland-protocols` 自动生成 `xdg-shell` 客户端代码。
同时生成 `text-input-v3`、`cursor-shape-v1`（可用时）和 tablet 协议绑定；cursor-shape
不可用时自动退回 `wayland-cursor` theme。

myui 的 Break PAL 在 Wayland 下使用共享 RHI surface：逻辑 dialog 不创建第二个 OS window，
并且只有 root window 的 CSD 标题栏允许请求 `xdg_toplevel_move`。X11/Wayland 外部 clipboard
读取由事件循环异步完成；第一次 `Ctrl+V` 会自动重试，不阻塞渲染帧。

### 2.4 Linux 构建矩阵

Linux 平台支持 4 种窗口后端 + 图形 API 组合：

| 配置 | 窗口 | 图形 | CMake 选项 | 验证构建目录 |
|------|------|------|-----------|---------------|
| **X11 + OpenGL** | X11 | OpenGL 4.x | `(默认)` | `build-verify-x11-gl/` |
| **X11 + Vulkan** | X11 | Vulkan 1.x | `-DENGINE_VULKAN=ON` | `build-verify-x11-vk/` |
| **Wayland + OpenGL** | Wayland | OpenGL 4.x (EGL) | `-DENGINE_ENABLE_WAYLAND=ON` | `build-verify-wl-gl/` |
| **Wayland + Vulkan** | Wayland | Vulkan 1.x | `-DENGINE_ENABLE_WAYLAND=ON -DENGINE_VULKAN=ON` | `build-verify-wl-vk/` |

示例：
```bash
cd engine
# X11 + OpenGL (默认)
cmake -B build-verify-x11-gl && cmake --build build-verify-x11-gl

# X11 + Vulkan
cmake -B build-verify-x11-vk -DENGINE_VULKAN=ON && cmake --build build-verify-x11-vk

# Wayland + OpenGL
cmake -B build-verify-wl-gl -DENGINE_ENABLE_WAYLAND=ON && cmake --build build-verify-wl-gl

# Wayland + Vulkan
cmake -B build-verify-wl-vk -DENGINE_ENABLE_WAYLAND=ON -DENGINE_VULKAN=ON && cmake --build build-verify-wl-vk
```

#### Linux Clang 构建

```bash
cd engine
mkdir build-clang && cd build-clang
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-clang-linux.cmake -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

或直接指定编译器：
```bash
cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
```

#### AddressSanitizer 版本
```bash
cd engine
cmake -B build-asan -DENGINE_USE_ASAN=ON
cmake --build build-asan
```

#### UndefinedBehaviorSanitizer 版本
`ENGINE_USE_UBSAN` 默认为 OFF；GCC/Clang/QCC 开启后使用 `-fsanitize=undefined`，不改变默认构建。QCC 会按 SDP 的 SONAME 显式链接运行库，目标部署需提供对应库及别名。QNX ASan 建议至少 3 GiB RAM；ASLR 与消毒器不兼容时，按运行库提示用 `on -ad <test-binary>` 仅对测试进程禁用 ASLR。
```bash
cd engine
cmake -B build-ubsan -DENGINE_USE_UBSAN=ON
cmake --build build-ubsan
```

### 2.5 Windows 平台构建

#### Windows + Clang 验证

本机已验证 Clang 22 + Ninja 原生构建；无 GPU 的 CI 仅运行非 `graphics` CTest：

```powershell
cmake -S engine -B build-win-clang -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug
cmake --build build-win-clang --parallel
ctest --test-dir build-win-clang -LE graphics --output-on-failure
```

GL 后端在 Windows 使用默认配置即可构建：myr 桌面 GL 后端（`MYUI_HAS_GL_DESKTOP`）通过
`my_gl_desktop.c` 内的一次性 `wglGetProcAddress` 解析加载 GL 1.3/2.0 入口（无 glad 依赖；
无当前上下文或 GL 1.1-only 驱动下 `my_gl_desktop_default()` 返回 NULL）；GLES2 后端改为
configure 时真实探测 `GLES2/gl2.h` 与导入库，stock Windows 无 SDK 时保持诚实 stub。

`test_shader_io` 与无 graphics 标签的 `test_platform_win32_runtime`、`test_myui_gl_desktop_win32`
（WGL 指针解析 headless 契约）、`test_net_loop`（IOCP 后端）在 Windows CTest 中启用；
`test_platform_win32_runtime` 使用真实 Win32 窗口、`GetWindowTextW`、`WM_SIZE` 和平台销毁路径，
不创建 graphics context；WM_SETTINGCHANGE/WM_DPICHANGED 以同步 `SendMessageW` 注入以兼容
新版 Windows 的 `ERROR_MESSAGE_SYNC_ONLY` 限制。源码路径同时支持 `/` 与 `\\` 分隔符。
`test_vulkan` 与 `test_myui_gl_desktop_runtime` 需要真实 WGL/GPU 环境，因此保留 `graphics`
标签并从 headless CI 中排除。

在具备本机 GPU 的 Windows 环境可额外执行完整 graphics 集成测试：

```powershell
Push-Location engine
..\build-win-clang\test_vulkan.exe
ctest --test-dir ..\build-win-clang -R test_myui_gl_desktop_runtime --output-on-failure
Pop-Location
```

图形集成测试仍需具备 WGL/Vulkan/GPU 环境后单独验证（`test_myui_gl_desktop_runtime` 已在
真实 ICD 上端到端通过 program 编译与纹理上传，但不覆盖帧级 present/swap 行为）。

**engine_demo Windows 运行时验证（2026-09-28）**：main() 含约 4.4 MB 局部结构（按 Linux 8 MB
默认栈设计），Windows 链接器默认 1 MB 栈保留会在序言栈探测即故障；CMake 现在对 engine_demo
在 Windows 显式设置 8 MB 栈保留（`/STACK:8388608`）。已在本机验证：

```powershell
cd engine
$env:BREAK_FRAMES = "120"; $env:BREAK_UI = "0"
..\build-win-clang\engine_demo.exe    # GL: 完整 120 帧 + 优雅关闭 + 0 FATAL
..\build-win-vk\engine_demo.exe       # Vulkan: NVIDIA 真卡 120 帧完整跑通
```

**Windows Vulkan 构建（2026-09-28 已验证）**：无头解包 Vulkan SDK 到
`engine/external/VulkanSDK/` 后：

```powershell
$sdk = "E:\work\break\engine\external\VulkanSDK"
cmake -S engine -B build-win-vk -G Ninja -DCMAKE_C_COMPILER=clang `
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=ON `
  -DVulkan_LIBRARY="$sdk\Lib\vulkan-1.lib" -DVulkan_INCLUDE_DIR="$sdk\Include" `
  -DSHADERC_LIB="$sdk\Lib\shaderc_shared.lib" -DSHADERC_INCLUDE_DIR="$sdk\Include"
cmake --build build-win-vk --parallel
ctest --test-dir build-win-vk -LE graphics --output-on-failure
```

运行 `test_vulkan` 需 `$env:PATH = "$sdk\Bin;$env:PATH"; $env:VK_LAYER_PATH = "$sdk\Bin"`，
工作目录 engine/ 源码根。当前边界：TEST 1-7 + FBO/MSAA/stress/1000-draw/10K 在 NVIDIA 真卡
稳定通过（段前缀二分 0/4 TDR；validation 0 消息）；TEST 9→10 边界区负载（unified cull + Hi-Z +
grouped compact 初始化/上传链）在本机驱动（RTX 4060 Laptop × NVIDIA 616.56，混合 AMD 显示）
概率→近确定触发驱动级 TDR/DEVICE_LOST（nvlddmkm Event 153 与 FATAL 秒级对齐 8/8；demo 同
子系统家族 240 秒免疫；Linux lavapipe CI 通过全部测试）——细节与证据见
`docs/Implementation_Status.md` R577；根因定位需 GPU 捕获或异地 NVIDIA 复现。

#### 使用 MSVC (Visual Studio)

已在 MSVC 19.51.36246 / Visual Studio 2026 Developer Command Prompt 中使用 Ninja 完成
Debug 原生 Windows 构建与非图形 Win32 runtime smoke。可复制以下命令：
```cmd
cmake -S engine -B build-msvc-1451-audit -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON -DENGINE_VULKAN=OFF -DENGINE_ENABLE_IPO=OFF
cmake --build build-msvc-1451-audit --parallel
ctest --test-dir build-msvc-1451-audit -LE graphics --output-on-failure
```

上述配置成功，完整构建在 `/W4 /WX /utf-8` 以及 `/experimental:c11atomics` 下通过；重复构建无剩余工作。
非图形 CTest `56/56` 通过，其中包括 `test_platform_win32_runtime`。CI 另外显式构建并执行
`test_platform_config`、`test_platform_null_safety` 和 `test_platform_win32_runtime`，避免平台
runtime 门禁仅依赖全量测试筛选。这提供的是非图形、headless
Win32 平台证据，不证明 WGL、Vulkan、GPU、present 或图形 runtime，也不证明 Windows Vulkan 构建。

或显式指定 MSVC 工具链文件：
```cmd
cmake -S engine -B build-msvc -DCMAKE_TOOLCHAIN_FILE=engine/toolchain-msvc.cmake -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-msvc --parallel
```

#### Windows Clang 构建（从 Linux 交叉编译）

```bash
cd engine
mkdir build-clang-win && cd build-clang-win
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-clang-win.cmake -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

#### 使用 MinGW（原生 Windows）
```bash
cd engine
cmake -B build-mingw -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc
cmake --build build-mingw
```

#### 使用 MinGW 交叉编译（Linux 主机）
```bash
cd engine
cmake -B build-cross -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake
cmake --build build-cross
```

#### Windows 依赖
- Vulkan SDK（如使用 Vulkan 后端）
- Windows SDK（系统自带）
- Visual Studio 2019+ 或 MinGW-w64

### 2.5 macOS 平台构建

macOS 使用 Xcode Command Line Tools 提供系统框架；当前 Cocoa 渲染路径还需要
MoltenVK/Vulkan、`shaderc_shared` 和 FreeType。文件监视模块额外链接 `CoreServices`
与 `CoreFoundation`。

```bash
cd engine
cmake -B build-macos -G Xcode -DCMAKE_BUILD_TYPE=Debug
cmake --build build-macos --config Debug --parallel
ctest --test-dir build-macos -C Debug -LE graphics --output-on-failure
```

使用 Ninja 构建：

```bash
cd engine
cmake -B build-macos -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-macos --parallel
```

#### macOS 依赖
- Xcode Command Line Tools（Clang、Xcode/Ninja 构建工具）
- MoltenVK/Vulkan SDK、`shaderc_shared` 和 FreeType（当前 Cocoa 路径会探测并链接）
- Metal、QuartzCore、IOKit、CoreServices、CoreFoundation（系统框架，自动链接）

#### macOS 文件监视
- 小/浅目录树使用 `kqueue` 以获得精确的单文件事件
- 大/深目录树使用 `FSEvents` 以降低 watch 数量
- 任一后端初始化失败时自动回退到另一后端

### 2.6 框架应用
```bash
# 从项目根目录
cmake -B build-gl
cmake --build build-gl
```

### 2.7 CMake 选项
| 选项 | 默认值 | 说明 |
|------|--------|------|
| ENGINE_VULKAN | OFF | 启用 Vulkan 后端（可与 X11/Wayland 任一窗口后端组合）；macOS Cocoa 路径自动使用 Vulkan/MoltenVK |
| ENGINE_ENABLE_WAYLAND | OFF | 启用 Wayland 窗口后端（与 X11 **编译时互斥**） |
| ENGINE_USE_ASAN | OFF | 启用 AddressSanitizer（GCC/Clang/QCC 使用 `-fsanitize=address`，MSVC 使用 `/fsanitize=address`） |
| ENGINE_USE_TSAN | OFF | 启用 ThreadSanitizer（GCC/Clang 使用 `-fsanitize=thread`；用于线程安全专项验证） |
| ENGINE_USE_UBSAN | OFF | 启用 UndefinedBehaviorSanitizer（GCC/Clang/QCC 使用 `-fsanitize=undefined`；MSVC 不启用） |
| ENGINE_BUILD_TESTS | ON | 构建并注册 CTest 测试；关闭后不注册测试 |
| ENGINE_ENABLE_IPO | ON | Release 构建中在工具链支持时启用 IPO/LTO，仅作用于 `engine` 静态库 |
| MYUI_FONT_FREETYPE | ON | 找到 FreeType 时启用 hinted 字形和 TTC 多字面选择；CJK 默认字体需要此选项 |
| MYUI_FONT_STB | ON | 启用 `stb_truetype` 独立 TTF/OTF 回退 |
| MYUI_GLES2 | ON | 探测可用依赖后启用可复用 GLES2 后端 |
| MYUI_GL_DESKTOP | ON | 探测可用依赖后启用桌面 OpenGL 后端 |
| MYUI_VULKAN | OFF | 启用可复用 Vulkan 后端；需要 Vulkan/shaderc 依赖 |
| ENGINE_ANDROID_NATIVE_WINDOW | OFF | Android Vulkan 必须开启，并提供 NDK `android/native_window.h` |
| RULE_ENGINE_ENABLE_C11_PARALLEL | OFF | 启用可选 C11 规则并行执行器；不代表全引擎句柄线程安全 |
| RULE_ENGINE_ENABLE_REDIS | OFF | 启用 Redis 状态提供者；需要 hiredis/Redis 源目录 |
| RULE_ENGINE_REDIS_SOURCE_DIR | (空) | 指定 Redis/hiredis 源目录，仅在 Redis 选项启用时使用 |
| CMAKE_C_STANDARD | 11 | C 语言标准 |
| CMAKE_C_COMPILER | (自动) | 指定 C 编译器（`gcc` / `clang` / `cl`） |
| CMAKE_CXX_COMPILER | (自动) | 指定 C++ 编译器（`g++` / `clang++` / `cl`） |
| CMAKE_TOOLCHAIN_FILE | (无) | 使用工具链文件（见上方编译器支持矩阵） |

> 编译器标志由 CMake 根据 MSVC / Clang / GCC **自动检测并应用三路分支**，无需手动指定告警/优化标志。

`net_loop` 的 `add`、`modify`、`remove`、`wait` 和 `destroy` 必须在同一个
loop owner 线程调用；只有 `net_loop_wakeup` 可从其他线程调用。IOCP 后端只提供
`NET_LOOP_READ`，会拒绝包含 `NET_LOOP_WRITE` 的注册，避免用立即完成的零字节发送伪造
可写边沿并造成忙循环。其他后端按各自原生 readiness/completion 语义提供 READ/WRITE。

## 锁定依赖（计划 F Task 1 起，2026-10-17）

全部构建/测试/发布依赖钉版。机器可校验清单：`engine/external/locked_dependencies.json`
（契约测试 `test_locked_dependencies`——字段完整性、禁止 "latest"、vendored 文件 sha256）；
人读说明：`engine/external/LOCKED_DEPENDENCIES.md`。实际钉版要点：

- CMake `>=3.25,<4.0`（CI 钉 ubuntu-24.04 apt `cmake=3.28.*`）；clang `>=17`（CI 钉 clang-18）、
  gcc `>=12`（CI 钉 gcc-13）、MSVC `>=19.38`。
- vendored Vulkan SDK 1.4.357.0（tarball sha256 钉死；含 shaderc（sdk-bundled，运行时
  GLSL→SPIR-V，target env Vulkan 1.2 / SPIR-V 1.5）、glslang 16.4.0、dxc 1.9.0.5399、
  VK_LAYER_KHRONOS_validation）；Windows CI 另以 LunarG SDK 1.4.321.0 静默安装
  （`engine/tools/fetch_vulkan_sdk_windows.cmake`，版本 + SHA256 钉死）。
- Android NDK r27c（27.2.12479018）；Xcode `>=15.4`（macOS 侧 glslc/spirv-cross/cmake/ninja
  的 pin 见 LOCKED_DEPENDENCIES.md 注记）；Windows SDK 10.0.26100.0。
- D3D12 Agility SDK 1.619.6（runtime-shipped；`engine/external/d3d12/agility_sdk_lock.txt`
  以 SHA512 复核 nupkg 与 D3D12Core.dll）。
- Linux CI 依赖（noble）：`libvulkan-dev=1.3.275.*`、`libshaderc-dev=2023.8*`、`cmake=3.28.*`。自 R700 起这些包预装在容器镜像 `ghcr.io/konyka/break-ci-linux:latest` 里（`.github/docker/ci-linux.Dockerfile`，由 `.github/workflows/ci-image.yml` 构建发布），Linux lane 在镜像里运行，job 里不再执行 `apt-get install`。要改包或版本：改 Dockerfile，等 `ci-image` 工作流构建完成后再触发 CI。`lane-proton`（周跑，需要 i386 + wine）仍在 job 里 apt 安装。

禁止使用 "latest" 或未钉版系统包构建 release。缺失依赖的平台在 CI/台账中标记 UNAVAILABLE，
不得伪造证据。

### 2.8 完整构建矩阵

验证等级约定：`compiled` 只表示配置和编译成功；`headless` 表示无窗口契约测试通过；
`native-surface` 表示创建了目标平台原生 surface；`GPU-runtime` 表示真实 GPU 图形测试；
`benchmark-comparable` 只有在同一场景、分辨率、帧数、构建类型和 validation 状态一致时才成立。
远程复核（2026-10-13）使用 SSH 环境变量完成且未记录凭据：Fedora 44 x86_64 的 OpenGL
契约与 Vulkan 配置/编译均通过，Vulkan 契约测试 `6/6` 通过，但该主机没有 `xvfb-run`，
因此没有宣称 graphics runtime；macOS 26.7.1 ARM64 的 AppleClang 可用，但远程环境缺少
`shaderc_shared` 与 MoltenVK，CMake 按设计 fail-closed，状态保持为依赖阻塞而非代码通过。
本机复核（2026-10-13）：macOS 26.7.1 ARM64（Apple M2，AppleClang 21，VulkanSDK 1.4.357，
MoltenVK ICD 与验证层 manifest 按 2.1 节 macOS 备注安装）全量构建通过，CTest `133/133`
通过——Cocoa runtime 契约 `3/3`、无头套件 `127/127`、`graphics`/`fuzz` 标记 `6/6`
（`test_vulkan` 进程内验证门在真实 GPU 上经 MoltenVK 通过）。

本机 Metal 复核（2026-10-17）：`ENGINE_RHI_BACKEND=metal` 的 Ninja Debug 构建完成，
离线 shader 管线生成 109 个 metallib 条目；macOS 平台/RHI 契约及无头测试 `168/168`
通过（D3D12 依赖门按平台跳过），Metal 设备、帧生命周期、资源和 consumer smoke
均通过。编译期 Metal 入口直接创建 `CAMetalLayer` 对应的 Metal 设备，并将
`shader_variant` 固定为 Vulkan-layout GLSL，以匹配离线 MSL manifest。
同日 @579928c 后续复核：`test_vulkan` 只在 `ENGINE_RHI_BACKEND_EFFECTIVE` 为
`vulkan`/`opengl` 时注册（metal/d3d12 构建下它会请求被后端按设计拒绝的 OpenGL，
曾以既存基线失败污染 `-L graphics` 收据），`rhi_swapchain_bench` 新增 Metal 分支
（收据 `backend=metal`），macOS Vulkan 构建的收据 backend 按 schema 改写为
`vulkan-moltenvk`（此前误写 `vulkan`）。本机（Apple M2）Metal 构建（含手动构建的 5 个 fuzz 目标）
CTest `178/178`、MoltenVK 默认构建 `176/176`，D3D12 依赖门均为平台跳过；Metal
`-L graphics` 为 `5/5`，`rhi_swapchain_bench` 约 120 fps（vsync 未关闭的合成 harness，
非 benchmark-comparable 证据）。

2026-10-22 同步 @fb589d7e（含 R638–R661 的 D3D12 工作）后在 macOS 复核，发现并修复两处
回归：① `tools/compile_metal_shaders.sh` 的 `shaders/*.comp` 通配吞入了新增的
`*_hlsl.comp`（D3D12 HLSL sidecar，不是 GLSL），`glslc` 报 `#version` 错误导致
`engine.metallib` 无法生成，现与 `*_gl.comp` 一并跳过；② `rhi_metal.m` 新增的
`rhi_shader_create_path` 依赖 `shader_read_file`，`test_rhi_metal_device_contract` 与
`test_rhi_metal_frame_lifecycle` 的源文件列表缺 `src/core/shader_io.c`，链接失败，已补上。
复核结果：Metal 构建（含 5 个手动 fuzz 目标）CTest `179/179`，`-L graphics` `5/5`；
MoltenVK 构建（`-DENGINE_VULKAN=ON`，与 CI 一致）`179/179`，`test_vulkan` 与
`rhi_swapchain_bench` 均通过，D3D12 依赖门均为平台跳过。注意：`ENGINE_RHI_BACKEND=auto`
在 macOS 上解析为 `opengl`（macOS 不支持，`rhi_gl.c` 编译失败），macOS 上必须显式给出
`-DENGINE_VULKAN=ON` 或 `-DENGINE_RHI_BACKEND=metal`。

2026-10-24 同步 @5e320ac9（R662–R687）后复核：两套构建 CTest 均 `179/179`（Metal 含 5 个
手动 fuzz 目标，`-L graphics` `5/5`），本轮远程改动未引入 macOS 构建或测试回归。
`engine_demo` 实机截图（`BREAK_SCREENSHOT=60 ... --frames 70`，须在 `engine/` 目录运行，
shader 按相对路径加载）发现 Metal 的 `rhi_screenshot` 仍按旧的 bottom-up 约定反转行序，
与 `rhi.h` 现行契约（ac15c54a 起：top-left 原点、各后端 top-down）相反，Metal 截图因此上下
颠倒；已改为直接拷贝，`test_rhi_metal_resources` 新增 `screenshot_rows_are_top_down`
（顶部半屏 scissor 画红、底部为清屏蓝，断言首行红末行蓝；修复前该用例失败）。
已知缺口（非本轮回归，同步前的 b715881c 截图一致）：Metal 下 `engine_demo` 只有 UI 可见、
3D 场景为黑——`rhi_metal.m` 的 `rhi_cmd_bind_material_textures_ibl`、
`rhi_cmd_set_shadow_viewport`、`rhi_cmd_bind_texel_buffers`、深度状态等十余个入口仍是
`not implemented` 桩，且多条渲染器管线的 bindings 创建失败，70 帧日志约 3000 条错误；
MoltenVK 构建下同一场景正常渲染。

2026-10-25 同步 @51e2d1a7（R689–R694：GL 回读、延迟 G-buffer 尺寸、CSM 直接 mega draw、
R694 固定步长物理）后复核：无冲突（`--ff-only`），MoltenVK 与 Metal 两套构建 CTest 均
`179/179`，Metal `-L graphics` `5/5`，无需修复。`engine_demo` 截图：MoltenVK 3D 场景与 UI 朝向
正确；Metal 仍只有 UI（既有缺口，日志错误数约 3000/70 帧，与上次持平）。R694 后物理改为
1/60 s 固定步长，第 60 帧角色尚在下落（HUD `grounded: 0 (body 4294967295)`，即 UINT32_MAX
未着地），第 300 帧已 `grounded: 1`，属预期行为变化。

2026-10-26 同步 @7da2498a（18 个提交，含 R696 弹性阈值、R697 Agility SDK、R699 WARP
着色器修复、Linux 预构建 CI 镜像及 R701a 纯 C11 meshoptimizer 移植）后复核：无冲突
（`--ff-only`）。新增 `test_meshopt_c` 起初在 MoltenVK 与 Metal 两套构建均失败：AppleClang
在 ARM64 默认将 `a*b+c` 融合为 FMA，使库计算及测试网格生成器的浮点结果偏离上游参考表；
未放宽断言，改为对 `meshopt_c` 和 `test_meshopt_c` 固定 `-ffp-contract=off`，并同步更新
`external/meshopt_c/README.md` 的参考表复现命令。修复前两套均 179/180、该测试失败，修复后
两套均 `180/180`，Metal `-L graphics` `5/5`。`engine_demo` 截图：MoltenVK 的 3D 场景和 UI
正常；Metal 仍只有 UI、3D 黑屏（既有缺口，70 帧约 3000 条错误，无变化）。

2026-10-26 后续修复 Metal 默认 FORWARD 黑屏：① `rhi_pipeline_bindings_create/resolve` 从固定空桩
改为持有 pipeline desc 副本并复用 VK 对齐的 offset 表，恢复全部命名 uniform 写入；② bloom 六个
pass 改为先绑 FBO 再绑 pipeline/texture，避免 Metal encoder 切换丢弃绑定；③ 实现 IBL 材质/cubemap、
RGBA32F texel buffer（4096 texel 行宽、16/17 槽位）和 graphics storage buffer 按 set 展开绑定，
实例 upload blit 后显式重绑 pipeline；④ 实现阴影视口、MRT 单附件 clear、各目标 depth clear，
深度状态与 depth-to-read 按 Metal/PSO 语义处理。`test_rhi_metal_resources` 由 44 增至 **47/47**，
新增阴影像限、清深度保留颜色、跨 4096 行 texel 读取断言；consumer smoke 增加 bindings/pipeline
坏日志门禁。MoltenVK 与 Metal 全量 CTest 均 `180/180`，Metal `-L graphics` `5/5`。
`BREAK_SCREENSHOT=60 ... --frames 70` 实证 Metal 的 3D 场景已恢复、朝向正确，本次运行日志中
`not implemented` 和 `without a bound graphics pipeline` 均未出现。与 MoltenVK 对比，构图接近，
但水面、光照和物体细节仍有明显差异，尚不宣称逐像素一致；DEFERRED binder、indirect-count 等
可选路径也未在本次补齐，证据等级保持待复核。

随后获取并整合远程 `@bed3f6c1`（含 R701b/R702 LOD 与 QNX 支持）。新增 ECS LOD 分块绘制在
每批实例 upload blit 后遗漏了实例管线重绑；Metal consumer smoke 的 `without a bound graphics
pipeline` 日志门禁捕获该问题，补齐后再次验证两后端 70 帧截图及默认路径日志。最终 Metal 与
MoltenVK 全量 CTest 均 **186/186**（远程新增 6 项亦通过），Metal graphics **5/5**、资源测试
**47/47**；上文所述渲染差异、未实现路径及证据等级复核状态不变。

2026-10-26 同步 `@0e714f06`（R703/R704 LOD fade/cache）后，Metal consumer smoke 初次因
离线 manifest 未覆盖 LOD 变体而 fail-closed。`engine/tools/compile_metal_shaders.sh` 补齐
blinn/pbr 前向路径及 G-Buffer 静态、数组路径的实际 define 链（含 `FORWARD_MRT,LOD_FADE`
和 `HAS_IBL,LOD_FADE`），生成 **124** 个 manifest 条目，修复提交为 `@83d672b7`。重新构建后
Metal 全量 CTest **187/187**、graphics **5/5**、资源测试 **47/47**；MoltenVK 全量 CTest
同样 **187/187**（两者仅 D3D12 dependency gate 按平台跳过）。两后端均完成
`BREAK_SCREENSHOT=60 ... --frames 70` 实机运行，3D 场景和 UI 可见、朝向正确，日志无 manifest
缺失、管线绑定或 fatal 错误。Metal 与 MoltenVK 的光照、材质和水面仍有差异，本次不宣称
逐像素一致，也不升级证据等级。推送前远程又前进至 `@8eee4a58`（R705/R706），本地提交
无冲突 rebase 后再次完成上述两套测试和 70 帧截图，结果保持 **187/187**、graphics **5/5**、
资源 **47/47**。

RHI 第一阶段还提供统一的设备健康状态查询 `rhi_device_get_status()`。`UNKNOWN` 表示
没有有效设备，`READY` 表示设备可用，`LOST` 表示后端报告设备丢失；该接口是后续 Vulkan、
Metal、D3D12 后端共用的生命周期合同。
平台兼容描述符还区分当前 native graphics baseline 与未来 `target_graphics_api`；目标
API 只是迁移计划元数据，不能替代 Metal/D3D12 的实际编译、native-surface 或 GPU-runtime
证据。
`ENGINE_RHI_BACKEND_EFFECTIVE` 和 `ENGINE_RHI_BACKEND_*` 编译宏只描述当前已经实现的
OpenGL/Vulkan/Metal/D3D12（仅 Windows）构建选择；平台 target metadata 不会自动改写选择。

Windows D3D12 contract-first gate（2026-10-13）已确认 Windows SDK 10.0.26100
头文件/库和 Vulkan SDK 内的 `dxc.exe` 可见，但当前环境没有独立的 `cl`/PIX PATH 证据，
也没有完成 D3D12 native-surface/GPU-runtime/Debug Layer 验证。该时点 D3D12 仍不可选择
（`target metadata + dependency/runtime gate blocked`）；计划 D（2026-10-15）起 D3D12 已落地为
可选后端，见下方「Windows D3D12 后端（计划 D）」节。
精确依赖审计要求 `d3d12.h`、任一 `dxgi*.h`、`d3d12.lib`、`dxgi.lib` 和 DXC；
Windows SDK 将 DXGI headers 放在 `Include/<version>/shared`，而 D3D12 headers 放在
`Include/<version>/um`，gate 会分别搜索这两个目录。该时点主机的 SDK/DXC compile
依赖可见，native surface、Debug Layer、PIX 和 GPU-runtime 尚未验证（计划 D 已补齐，见下节）。
仓库新增 `test_d3d12_dependency_gate`：Windows 上会分类 SDK headers/libs 与 DXC 是否齐全，
非 Windows 或依赖不完整返回 `UNAVAILABLE`（CTest skip），不会把依赖可见误报为 native
device/surface/GPU-runtime 支持。
`test_d3d12_shader_compile_gate` 进一步用 DXC 的 `vs_6_0` CLI contract 验证 shader ABI：
有效 HLSL 必须返回成功状态并生成非空 DXIL，包含文件必须可解析；无效 HLSL 和缺失 include
必须返回失败状态、保留诊断且不接受 output blob。gate 同时记录 DXC `--version` identity、
profile、include search path 和 valid/invalid/missing-include 结果，并在每次运行后删除临时
HLSL、include 和 DXIL。仓库没有提交生成的 DXIL，也没有 DXC import library，因此该 gate
验证 CLI 可观察到的 `IDxcCompiler3`/`IDxcResult` 等价结果边界，而不实现 COM backend。
成功证据中的 `include_dir=` 会打印本次运行实际使用的临时 include 目录字面路径；这不是
独立的 COM `IDxcCompiler3`/`IDxcResult` 验证。
这是 compile-only shader toolchain 证据，不接入 RHI、不创建 D3D12 device/surface，也不代表
Windows D3D12 GPU-runtime 已实现。Focused command:

```powershell
cmake -DCMAKE_CURRENT_BINARY_DIR=<build-dir> `
  -P <repo-root>/engine/tests/test_d3d12_shader_compile_gate.cmake
```

### Windows D3D12 后端（计划 D，2026-10-15 起）

Windows 上 D3D12 已是可选 RHI 后端（GPU_RUNTIME 级证据；收据见
`docs/rhi_backend_evidence.md`，特性面见 `docs/rhi_metal_d3d12_feature_matrix.md`）：

```bash
cmake -S engine -B build-d3d12 -DENGINE_RHI_BACKEND=d3d12 -DCMAKE_BUILD_TYPE=Debug
cmake --build build-d3d12
ctest --test-dir build-d3d12 -L graphics -R test_d3d12 --output-on-failure
```

- 依赖锁定（`engine/external/d3d12/agility_sdk_lock.txt`，由 `test_d3d12_sdk_lock`
  做哈希校验）：Windows SDK 10.0.26100.0、Agility SDK
  （Microsoft.Direct3D.D3D12）1.619.6、dxc 优先 vendored
  `engine/external/VulkanSDK/Bin/dxc.exe`（CI 用 Windows SDK 自带 dxc）。
- Agility SDK 获取：`cmake -P engine/tools/fetch_d3d12_agility_sdk.cmake`（NuGet
  下载 + 锁文件 SHA512 校验）；构建系统把 `D3D12Core.dll` / `d3d12SDKLayers.dll`
  POST_BUILD 部署到构建目录（exe 旁 `D3D12SDKPath` 生效），缺失即 configure 期
  FATAL_ERROR 并指向该 fetch 脚本。
- `ENGINE_D3D12_DEBUG`：Debug 默认 ON、Release 默认 OFF（显式
  `-DENGINE_D3D12_DEBUG=OFF` 可覆盖）；ON 时启用 D3D12 debug layer +
  GPU-based validation，DRED（auto breadcrumbs + page fault）全配置强制。
  运行时 `BREAK_D3D12_GBV=0` 只保留 debug layer、关掉 GPU-based validation
  （demo 在 Debug 构建下从约 20 FPS 回到 76–87 FPS）；默认开启，测试与 CI 不受影响。
  PIX 捕获与 device-lost（DRED）排查见 `docs/rhi_rollback_runbook.md` 的
  D3D12/PIX 节。
- shader 路径：手写 HLSL 旁挂（`engine/shaders/*_hlsl.{vert,frag}`）构建期经 dxc
  编译为 DXIL（SM 6.0），产物在构建目录 `shaders_d3d12/`，不入库。
- 证据纪律：Proton（Wine/vkd3d-proton）兼容 lane
  （`.github/workflows/proton-d3d12.yml`）只作兼容参考，不计入 Windows 原生证据等级。

Phase 2 的显式选择器为：

```bash
cmake -S engine -B build-rhi-gl -DENGINE_RHI_BACKEND=opengl
cmake -S engine -B build-rhi-vk -DENGINE_RHI_BACKEND=vulkan
```

`ENGINE_RHI_BACKEND=auto` 保持历史默认行为。当前 selector 控制已有 OpenGL/Vulkan/D3D12（仅 Windows）
实现的构建选择，不声称 Metal 已实现；`test_rhi_backend_selection` 会锁定
允许值和后续拆分前的行为边界。配置阶段还会输出 effective backend，并定义
`ENGINE_RHI_BACKEND_OPENGL=1` / `ENGINE_RHI_BACKEND_VULKAN=1` / `ENGINE_RHI_BACKEND_D3D12=1` 编译宏，供后续
backend target 拆分和发布 receipt 使用。

Phase 2 的 source-split 前置层位于私有头文件
`engine/src/rhi/rhi_backend_internal.h`，只集中共享设备布局、资源槽和后端 helper
声明；当前仍采用 unity inclusion，以保证拆分前没有运行时行为变化。
`test_rhi_backend_internal_contract` 会在 OpenGL/Vulkan 配置中检查三份 RHI 源文件
都显式依赖该私有合同，防止后续拆分依赖 unity 编译的隐式声明。
frame owner 与 device control helper 也属于该合同；实现暂留在 `rhi.c`，避免在没有
独立 translation-unit build gate 前引入行为变化。
当前第一批 ownership helper 已迁移到 `rhi_ownership.c`，并由 RHI headless 测试目标
显式链接；这保证测试构建不会依赖 unity inclusion 的隐式符号。
当前纯 CPU TLAS instance encoder 已迁移到 `rhi_validation.c`，engine、`test_rt_trace`
和独立 headless contract test 均显式链接；这只是 source split，不新增 backend 或 RT 能力。
纹理、buffer、cubemap descriptor validator 也已迁移到该纯验证单元，OpenGL/Vulkan
测试目标显式链接并保持相同行为。
资源槽/生成器、backend dispatch、加速结构代理和 frame-damage state 暂不拆出；这些
区域仍依赖公共设备布局或后端生命周期，必须先有独立 contract test 才能迁移。
公共 native proxy 的 headless contract 会先清零输出并在无效设备/资源时 fail-closed；
Vulkan 专用的 opaque AS handle 不作为 Metal/D3D12 的通用接口。
`rhi.c` 中的 device/info/native proxy 只负责统一参数清理与 fail-closed 转发；AS build、
creation/destruction 和 Vulkan handle wrapper 暂不拆出，直到有独立 backend contract。
AS descriptor/BLAS input validation 已进入纯 validation 单元；AS build、device address、
creation/destruction 和 Vulkan opaque handle 仍保留在 backend dispatch 边界。
资源槽初始化、generation 分配、typed lookup 与 free-list recycling 已迁移到
`rhi_resources.c`，engine、RHI tests 和 `test_rt_trace` 都显式链接该源文件。
所有直接消费 `rhi.c` 的 target 都必须显式列出 ownership、validation、resources
三个拆分源文件；`test_rhi_backend_internal_contract` 会锁定该构建图规则。
frame-damage state 暂留在 `rhi.c`，因为 OpenGL/Vulkan 的 begin/end/present 路径都会
修改 partial-present 状态；其 owner-busy 和 damage publication contract 已有测试覆盖。

| lane（.github/workflows/ci.yml） | runner | 后端 / 配置 | 收据 artifact |
|---|---|---|---|
| lane-headless-linux-clang | ubuntu-24.04 | 默认 GL（兼容期），Clang/LLD Release + IPO | evidence-receipt-headless-linux-clang |
| lane-headless-linux-gcc-asan | ubuntu-24.04 | 默认 GL（兼容期），GCC Debug + ASan/UBSan（+fuzz smoke） | evidence-receipt-headless-linux-gcc-asan |
| lane-headless-linux-gcc-tsan | ubuntu-24.04 | 默认 GL（兼容期），GCC Debug + TSan | evidence-receipt-headless-linux-gcc-tsan |
| lane-headless-windows-clang | windows-latest | Vulkan（+GL 默认），Clang Debug（含 win32 runtime trio 步） | evidence-receipt-headless-windows-clang |
| lane-headless-windows-asan | windows-latest | 默认 GL（兼容期），Clang Debug + ASan | evidence-receipt-headless-windows-asan |
| lane-native-surface-wayland | ubuntu-24.04 | Wayland + Vulkan，Debug（weston headless） | evidence-receipt-native-surface-wayland |
| wayland-gl（DEPRECATED，兼容期，Task 6 删） | ubuntu-latest | Wayland + GL，Debug | evidence-receipt-native-surface-wayland-gl |
| lane-native-surface-win32 | windows-latest | Win32 原生 surface trio，Clang Debug | evidence-receipt-native-surface-win32 |
| lane-native-surface-cocoa | macos-14 | Cocoa + MoltenVK，Debug | evidence-receipt-native-surface-cocoa |
| lane-gpu-runtime-linux-gl（DEPRECATED，兼容期，Task 6 删） | ubuntu-latest | X11 + GL，Debug，Xvfb 软渲染 | evidence-receipt-gpu-runtime-linux-gl |
| lane-gpu-runtime-linux-vk | ubuntu-24.04 | X11 + Vulkan，clang-18 Debug，Xvfb + lavapipe（软渲染，收据如实标注） | evidence-receipt-gpu-runtime-linux |
| lane-gpu-runtime-macos-metal | macos-14 | Metal，Debug（hosted 无 Metal 会话时收据如实降级 HEADLESS） | evidence-receipt-gpu-runtime-macos-metal |
| lane-gpu-runtime-windows-d3d12（+ 常开 unavailable 孪生 job） | self-hosted windows gpu（`ENABLE_GPU_LANES` 门控） | D3D12，Release（hosted WARP floor 在 windows-d3d12.yml） | evidence-receipt-gpu-runtime-windows-d3d12 |
| lane-validation-linux-vk | ubuntu-24.04 | Vulkan，Debug，VK_LAYER_KHRONOS_validation（VUID 即红） | evidence-receipt-validation-linux |
| lane-benchmark-linux-vk | ubuntu-24.04 | Vulkan，Release，`rhi_swapchain_bench` 600 帧 lavapipe（GPU_RUNTIME 收据注明软渲染） | evidence-receipt-benchmark-linux-vk |
| lane-benchmark-steam-deck-vk | self-hosted linux gpu-vulkan（`ENABLE_GPU_LANES` 门控） | Vulkan，RelWithDebInfo，真 GPU BENCHMARK_COMPARABLE 收据 | evidence-receipt-benchmark-steam-deck |
| lane-proton（schedule 周一 03:23 UTC + 手动） | ubuntu-24.04 | steamrt sniper 钉 digest 容器内构建 + ctest（兼容参考） | evidence-receipt-proton |
| clean-room（Task 2 交付，非 lane 命名） | ubuntu-24.04 | 钉版工具链 + git archive 干净导出 + Vulkan | — |
| ios-metal-build（compile only） | macos-14 | iOS Simulator build-only + metallib 断言 | — |

## 3. 构建产物

| 产物 | 位置 | 说明 |
|------|------|------|
| libengine.a | build-*/libengine.a | 引擎静态库 |
| libglad.a | build-*/libglad.a | OpenGL 加载库 |
| engine_demo | build-*/engine_demo | 渲染演示程序 |
| test_vulkan | build-*/test_vulkan | Vulkan 后端集成 + golden 回归测试程序 |
| packer | build-*/packer | 资源打包工具 |
| empty | build-gl/empty/empty | 最小化应用示例 |

### 3.1 运行 engine_demo（Linux 桌面）

- **Wayland/XWayland 节流**：在 Wayland 会话下 GL demo 走 XWayland，`glXSwapBuffers` 会被 Present 节流到 ~1 FPS（profiler 显示 `Frame: 1000 ms`，而引擎 dt 按 R147 钳制 0.1s）。脚本化截图/相机复现前请用 `vblank_mode=0 ./build_gl/engine_demo` 绕过节流，否则一秒的鼠标输入会在单帧内一次性生效。
- 脚本化钩子（均无默认值，不设即原行为）：`BREAK_FRAMES=N`（N 帧后退出）、`BREAK_SCREENSHOT=a,b,c`（R446 起支持逗号列表，逐帧截图到 screenshot_N.bmp）、`BREAK_CAM=x,y,z[,yaw,pitch]`（初始机位）、`BREAK_CAM_SPIN=deg`（R446，每帧 yaw 增量，复现相机运动伪影）、`BREAK_TAA=0` / `BREAK_MB=0`（R446，TAA/动态模糊开关，用于 A/B 对照）、`BREAK_SSR=1` / `BREAK_SSGI=1` / `BREAK_CS=1` / `BREAK_VOL=1` / `BREAK_LF=1`（R550-A，开启默认关闭的 SSR/SSGI/接触阴影/体积雾/镜头光晕——五路 pass 自 R550-A 起真实合成进帧链）、`BREAK_IBL_STATIC=1`（R559，禁用运行时 IBL rebake）、`BREAK_IBL_REBAKE_FRAMES=N`（R559，每 N 帧触发一次、用于无头验证；rebake 仍跨 42 帧完成）、`BREAK_JITTER=0`（关闭 Halton 抖动，便于隔离时间重投影伪影）。TSR 在初始化或分辨率重建后的第一帧只输出当前帧，不采样历史；随后才恢复历史重投影。

## 4. 编译选项与标准

### 4.1 编译器警告
```cmake
-Wall -Wextra -Werror -pedantic
```
- 零容忍警告策略
- 严格 C11 标准遵从

### 4.1.1 编译器兼容性说明

- **GCC/Clang 通用标志**：`-Wall -Wextra -Werror -pedantic`
- **MSVC 标志**：`/W4 /WX /utf-8 /experimental:c11atomics`，自动定义 `_CRT_SECURE_NO_WARNINGS`
- **GCC 特有**：`-Wno-format-truncation` 仅在 GCC 下对 packer 工具启用
- **Sanitizer**：GCC/Clang 使用 `-fsanitize=address`，MSVC 使用 `/fsanitize=address`
- **对齐宏**：代码使用 `ENGINE_ALIGN(x)` 宏，自动适配 `__attribute__` (GCC/Clang) 或 `__declspec(align)` (MSVC)
- 编译器检测完全自动化，无需手动指定标志

### 4.2 平台链接库
| 平台/后端 | OpenGL | Vulkan |
|----------|--------|--------|
| Linux (X11) | X11, GL, dl, pthread | Vulkan, shaderc_shared, dl, pthread |
| Linux (Wayland) | wayland-client, wayland-egl, EGL, GL, xkbcommon, dl, pthread | Vulkan, wayland-client, xkbcommon, shaderc_shared, dl, pthread |
| Windows | opengl32, gdi32 | vulkan-1 |

## 5. 工具链

### 5.1 Packer 资源打包工具
```bash
# 用法
./packer output.pak /path/to/assets [/another/dir ...]
```

#### PAK 文件格式
```
┌─────────────┐
│ Header (16B)│  Magic: 0x54415045 ("EAPE"), Version: 1
├─────────────┤
│ Entry[]     │  每条 16B: name_hash + name_offset + data_offset + size
├─────────────┤
│ Names       │  字符串表（\0 结尾）
├─────────────┤
│ Data        │  资源原始数据
└─────────────┘
```
- FNV-1a 哈希快速查找
- 最多 4096 个文件
- 递归扫描目录

### 5.2 着色器编译（Vulkan）
Vulkan 着色器需要 SPIR-V 编译：
```bash
glslangValidator -V shader.vert -o shader.vert.spv
glslangValidator -V shader.frag -o shader.frag.spv
```

## 6. 开发工作流

### 6.1 热重载
- 引擎支持文件监视（filewatch 模块）
- 着色器和脚本修改后自动重新加载
- 开发时无需重启应用

### 6.2 调试模式
- AddressSanitizer 内存检测
- 调试可视化（线框、法线、深度）
- DebugUI 文本叠加
- Profiler 性能分析

### 6.3 测试
```bash
cd engine
cmake -B build-verify-x11-gl
cmake --build build-verify-x11-gl
ctest --test-dir build-verify-x11-gl -LE graphics --output-on-failure

# Vulkan 后端集成测试（需要 -DENGINE_VULKAN=ON）
cmake -B build-verify-x11-vk -DENGINE_VULKAN=ON
cmake --build build-verify-x11-vk
ctest --test-dir build-verify-x11-vk -L graphics --output-on-failure
```

图形测试会创建真实窗口，GL 与 Vulkan 必须顺序执行，避免 X11 窗口资源竞争。完成构建后，
推荐按以下完整矩阵验证 forward MRT、真实 IBL、RT1 temporal consumers（TAA/combined AA/
motion blur；GL/Vulkan graphics gate 都使用真实 `RG16F` 输入并检查 blur 输出变化）和运行时错误门禁：

```bash
# 无头单元/集成测试
ctest --test-dir build-verify-x11-gl -LE graphics --output-on-failure
ctest --test-dir build-verify-x11-vk -LE graphics --output-on-failure

# 图形测试：严格顺序，不并行
ctest --test-dir build-verify-x11-gl -L graphics --output-on-failure
ctest --test-dir build-verify-x11-vk -L graphics --output-on-failure

# 运行时 smoke：GL 检查 Mesa API 错误；VK 检查 validation 层
MESA_DEBUG=1 BREAK_FRAMES=120 BREAK_UI=0 ./build-verify-x11-gl/engine_demo
BREAK_FRAMES=120 BREAK_UI=0 ./build-verify-x11-vk/engine_demo
```

Windows 的本轮 MSVC 证据限于原生编译和非图形 Win32 platform smoke；Linux 交叉构建不能替代
该验证。`test_platform_win32_runtime` 不创建 graphics context，因此 WGL、Vulkan、GPU、present
和图形 runtime 仍待在相应目标环境验证，Windows Vulkan 构建也仍待验证。

### 6.4 持续集成（CI）

[![CI](https://github.com/konyka/break/actions/workflows/ci.yml/badge.svg)](https://github.com/konyka/break/actions/workflows/ci.yml)

GitHub Actions workflow：`.github/workflows/ci.yml`。触发：push/PR 到 `master` + schedule
（周一 03:23 UTC）+ workflow_dispatch。计划 F Task 7（2026-10-17）起重排为六类证据 lane
（headless / native-surface / GPU-runtime / validation / benchmark / proton），每 lane 尾部以
`engine/tools/make_evidence_receipt.cmake` 生成收据、`engine/tests/test_evidence_receipt_schema.cmake`
校验并上传 `evidence-receipt-*` artifact（Task 8 台账消费）。lane 明细同 §2.8 的六 lane 矩阵表
（lane 名 / runner / 后端配置 / 收据 artifact 名），此处列分组：

| lane 类 | job |
|---|---|
| headless | lane-headless-linux-clang / -gcc-asan / -gcc-tsan / -windows-clang / -windows-asan |
| native-surface | lane-native-surface-wayland / -win32 / -cocoa（+ 兼容期 wayland-gl，DEPRECATED） |
| GPU-runtime | lane-gpu-runtime-linux-gl（DEPRECATED）/ -linux-vk / -macos-metal / -windows-d3d12（+ 常开 unavailable 孪生 job） |
| validation | lane-validation-linux-vk（VK_LAYER_KHRONOS_validation，VUID 即红） |
| benchmark | lane-benchmark-linux-vk（lavapipe，GPU_RUNTIME 收据）/ lane-benchmark-steam-deck-vk（真机 BENCHMARK_COMPARABLE，`ENABLE_GPU_LANES` 门控） |
| proton | lane-proton（steamrt sniper 钉 digest 容器内构建 + ctest；兼容参考，不计 Windows 原生证据；仅 schedule/手动触发） |
| 非 lane 命名保留 | clean-room（Task 2 交付）、ios-metal-build（compile only） |

收据纪律：失败 lane 的收据如实降级 UNAVAILABLE（`job.status` 守卫）；hosted macOS 无 Metal
会话时 graphics 整体 SKIP → HEADLESS；lavapipe/llvmpipe 软渲染收据在 gpu 字段与 command 字段
如实标注，不计入硬件 GPU 证据。最近全绿 run（17 success / 3 设计内 skipped，15 个
evidence-receipt artifact）：https://github.com/konyka/break/actions/runs/38990768014 （@3c92a06b，
2026-10-17）。

`lane-gpu-runtime-linux-vk` 显式启动 Xvfb，并选择 Mesa 的软件 Vulkan ICD（lavapipe）及 llvmpipe；
若 runner 缺少 Xvfb 或 lavapipe ICD，步骤直接失败，不把未执行宣称为通过。软件渲染与参考 GPU 的
golden image 可能存在差异，因此该 lane 是环境/启动 smoke，不替代真实 GPU graphics 验证。Windows
lane 的 `test_platform_win32_runtime` 提供 Win32 platform smoke 证据，不覆盖 WGL/Vulkan/GPU/present；
macOS lane 执行 Cocoa window smoke；Wayland lane 启动 Weston headless compositor 后执行 Wayland
platform smoke。上述 smoke 仍不等价于真实 GPU、IME、buffer-age 或物理设备矩阵，也不等价于完整
retained-buffer partial-present 验证。

## 7. 项目结构与两套构建

### 7.1 独立引擎构建 (engine/CMakeLists.txt)
- 产出：libengine.a + demo 程序
- 纯 C 项目，C11 标准
- 包含所有引擎子系统

### 7.2 框架构建 (根 CMakeLists.txt)
- 产出：libcommon.a + empty 应用
- C++ 框架层
- 用于演示应用集成方式

### 7.3 构建关系图
```
根 CMakeLists.txt
├── framework/common → libcommon.a (C++)
└── empty → empty 可执行文件 (链接 libcommon.a)

engine/CMakeLists.txt (独立)
├── external/glad → libglad.a
├── src/** → libengine.a
├── src/main.c → engine_demo
└── tools/packer.c → packer
```

## 8. 新应用创建指南

### 8.1 最小应用模板
```cpp
// my_app.cc
#include "base_application.h"

namespace bk {
class MyApp : public BaseApplication {
    int Init() override { /* 初始化 */ return 0; }
    void Tick() override { /* 每帧更新 */ }
    void DeInit() override { /* 清理 */ }
};
}

bk::MyApp g_App;
bk::ApplicationInterface* g_pApp = &g_App;
```

### 8.2 直接使用引擎 API（纯 C）
```c
// 链接 libengine.a
#include "engine.h"

int main() {
    Engine engine = {0};
    EngineConfig cfg = { .width = 1280, .height = 720, .title = "My Game" };
    if (!engine_init(&engine, &cfg)) return 1;
    while (engine_frame(&engine)) {
        // 游戏逻辑
    }
    engine_shutdown(&engine);
}
```

## 9. 常见问题

### Q: OpenGL 版本不够怎么办？
A: 引擎需要 OpenGL 4.5+。检查 `glxinfo | grep "OpenGL version"`。

### Q: Vulkan 验证层报错？
A: 确保安装了 Vulkan SDK 并设置 `VK_LAYER_PATH`。

### Q: 如何切换渲染后端？
A: 重新 cmake 配置：`cmake -B build -DENGINE_VULKAN=ON/OFF`

## 10. 性能基准

| 配置 | 分辨率 | FPS | 硬件 |
|------|--------|-----|------|
| Full Pipeline | 1280×720 | ~188 | Intel UHD TGL GT1 |

---

## Windows 平台验证边界

MSVC 19.51.36246 / Visual Studio 2026 Developer Command Prompt + Ninja 已完成原生 Debug
构建与非图形 Win32 smoke。以下项目仍待验证或完善：

### 待验证项

1. **MinGW 交叉编译验证** — 在 Linux 上安装 mingw-w64 后使用 `toolchain-mingw.cmake` 交叉编译，验证产出物可在 Windows 运行
2. ~~**OpenGL WGL 后端运行验证**~~ — **已验证（2026-09-28）**：8 MB 栈保留修复后，engine_demo GL 模式在真实 ICD 完整 120 帧 + 优雅关闭；输入响应的交互级验证仍待人工桌面会话确认
3. ~~**Vulkan Win32 Surface 运行验证**~~ — **已验证（2026-09-28）**：engine_demo Vulkan 模式在 NVIDIA 真卡完整 120 帧；test_vulkan TEST 1-9 通过（TEST 10 起见 §2.5 边界）
4. ~~**高 DPI 验证**~~ — **已验证（2026-09-29，静态链路）**：在 144 DPI / 150% 缩放 / 2560×1600 实机探针验证 `platform_get_dpi=144.0`、`content_scale=1.500`、`input_scale=1.500`、`scale_factor=2`、`drawable/logical=1.501` 全部精确。语义备注：`PlatformConfig` 尺寸按物理像素解释（1280×720 物理 = 853×480 逻辑），与 myui PAL 的逻辑像素约定不同但自洽。WM_DPICHANGED 跨屏动态响应仍需交互验证
5. ~~**文件热重载验证**~~ — **已验证（2026-09-29）**：GL demo 运行中修改 `blinn_phong.frag`，完整链路实证："changed, recompiling pipeline" → "pipeline recompiled successfully" → 优雅退出

### 环境准备

- 安装 MinGW: `sudo dnf install mingw64-gcc mingw64-headers`
- 或准备 Windows 虚拟机/物理机进行原生测试
- Vulkan 测试需安装 Windows 版 Vulkan SDK
## Windows Clang 原生验证

已在 Windows + Clang/LLVM + Ninja 环境验证：

```powershell
cmake -S engine -B build-win-clang -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-win-clang --parallel
ctest --test-dir build-win-clang -LE graphics --output-on-failure
```

结果：Clang 非图形测试 `40/40` 通过；该记录不提供本轮 MSVC 证据，也不改变 WGL/Vulkan/GPU/present
仍待验证的边界。

## Metal 后端构建（计划 C，macOS / iOS）

依赖：Xcode 15.4+（`xcrun metal` 组件；macOS 26 需
`xcodebuild -downloadComponent MetalToolchain`）、`brew install shaderc spirv-cross`
（glslc + SPIRV-Cross，pin 版本见 `docs/rhi_backend_evidence.md` 计划 C 收据）。

```bash
# macOS（本机构建 + 测试）
cmake -S engine -B build-metal -G Ninja -DCMAKE_BUILD_TYPE=Debug \
    -DENGINE_RHI_BACKEND=metal -DMYUI_PAL=cocoa
cmake --build build-metal --parallel
ctest --test-dir build-metal -R test_rhi_metal --output-on-failure
./build-metal/engine_demo --frames 3          # consumer smoke（退出码 0）

# iOS（build-only；模拟器证据 = compile only）
cmake -S engine -B build-ios -G Xcode \
    -DCMAKE_SYSTEM_NAME=iOS -DENGINE_RHI_BACKEND=metal -DENGINE_BUILD_TESTS=OFF
xcodebuild -project build-ios/PureCEngine.xcodeproj -scheme engine_demo \
    -destination 'generic/platform=iOS Simulator' build
```

说明：
- 离线 shader 管线（GLSL→SPIR-V→MSL→metallib + FNV manifest）在构建期运行，
  产物 `metal_shaders/engine.metallib` 拷到各 consumer 旁；`xcode-select` 指向
  CommandLineTools 时 `DEVELOPER_DIR` 由 CMake 自动烘焙为标准 Xcode 路径。
- iOS 交叉编译时 manifest 生成器自动切换为宿主编译（`gen_metal_shader_manifest_host`，
  见 `engine/CMakeLists.txt` M6 注释）；`xcrun metal` 目标 SDK 切 `iphoneos`。
- `METAL_DEVICE_WRAPPER_TYPE=1 ./engine_demo --frames 3` 开 Metal validation
  取证（encoder-state 类缺陷的唯一可靠观测，计划 C Task 11 方法学）。
