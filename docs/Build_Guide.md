# Break Engine 构建与开发指南

## 1. 环境要求

### 1.1 编译器
- `engine/` 是严格 C11 项目；CMake 会选择 GCC、Clang/AppleClang 或 MSVC 的 C 编译器，并启用严格警告。仓库没有在 CMake 中声明 GCC 11 或 Clang 14 的最低版本，因此具体工具链仍需能编译 C11 原子和项目依赖。
- **双语言策略（2026-11-08 起）**：引擎保持纯 C11；所有 C++ TU（`framework/`、应用胶水层、C++ 封装头）一律按 **C++20** 构建（根项目与 `engine/` 的 `CMAKE_CXX_STANDARD` 均为 20，`engine/` 现在启用 `LANGUAGES C CXX`）。公开的 `break_*.h` 模块 API 头文件必须可被 C++20 消费（`extern "C"` 守卫 + 无 C-only 构造；`core/types.h` 提供 `BREAK_AGG(T)` / `BREAK_STATIC_ASSERT` 双语拼写宏），由 `test_public_api_cpp20` 钉住。有意边界：`engine.h` 及以下的 runtime 头（platform/math/ecs/renderer 内部）保持 C-only。新增公共功能时 C API 与 C++20 封装同步交付。
- `engine/` 的 CMake 最低版本是 3.20+，仓库根 CMake 项目要求 CMake 3.25+。Linux Clang Release 的 IPO/LTO 配置还需要 `lld`。

#### 编译器支持矩阵

| 平台 | 编译器 | 状态 | 工具链文件 | 备注 |
|------|--------|------|-----------|------|
| Linux | GCC | CI 验证 | (默认) | GCC Wayland/OpenGL、Vulkan、ASan/UBSan 配置见 CI |
| Linux | Clang + lld | CI 验证 | `toolchain-clang-linux.cmake` | Release 配置启用 IPO |
| Windows | MSVC (cl) | 支持 | `toolchain-msvc.cmake` | 原生 Windows 开发 |
| Windows | Clang | 支持 | `toolchain-clang-win.cmake` | clang + lld-link |
| Windows | MinGW GCC | 支持 | `toolchain-mingw.cmake` | Linux 交叉编译 |
| QNX | qcc/q++ (SDP 7.1/8.0) | headless 兼容层 | `toolchain-qnx.cmake` | poll net_loop、headless RHI；见 `docs/qnx_compat.md` |

### 1.2 系统依赖（Linux）
- **Linux 仅支持原生 Wayland**（2.0.0 起）；必需 `libwayland-dev`、`wayland-protocols`、`libxkbcommon-dev`、`wayland-scanner`。缺少这些依赖时 configure 明确失败，不回退到旧窗口系统或 dummy
- Vulkan 加载器/头文件 + shaderc（默认后端，例如 libvulkan-dev libshaderc-dev）。实际启用 OpenGL 路径时，configure 还 REQUIRED 探测 EGL/OpenGL 头文件和库（例如 libegl1-mesa-dev libgl1-mesa-dev）：包括显式 `ENGINE_RHI_BACKEND=opengl`、auto 配置期降级，以及 auto Vulkan 且 `ENGINE_RHI_MULTI_BACKEND=ON` 的运行时 fallback 链；显式 Vulkan-only 且 multi-backend=OFF 不要求安装 GL
- FreeType 开发库（推荐；`dxx_break` 默认 CJK TTC 字体和中文显示需要它）
- pthread
- 手柄支持：evdev（Linux 内核内置，无需额外包）

### 1.3 系统依赖（Windows）
- Visual Studio 2019+ 或 MinGW
- Windows SDK
- DirectX 11 SDK (可选，用于 platform 演示)

### 1.4 macOS、iOS、Android、OHOS 与 QNX
- 平台图形元数据把性能基线与 Vulkan 证据分开：Linux/Windows 的 native baseline 是 OpenGL（渲染对比基准），默认后端是 Vulkan，macOS 是 Metal；macOS Vulkan 明确走 MoltenVK，不表示已实现 Metal RHI。Vulkan 证据级别使用 `compiled`、`headless`、`native-surface`、`GPU-runtime`、`benchmark-comparable`，不能把编译通过当作运行时支持。
- macOS 由 CMake 识别为 `macos`，当前 Cocoa Vulkan 路径使用 Vulkan loader/MoltenVK、`shaderc_shared` 和 FreeType；仓库的 macOS CI 安装 `molten-vk`、`shaderc`、`freetype`。原生 Metal 需要 Xcode 的 `metal`（`xcrun --sdk macosx metal`）和 `spirv-cross`。数学库在 libSystem 里，Apple 与 Windows 一样使用空的接口目标 `m`，链接行不再重复 `-lm`。
- iOS 由 CMake 识别为 `ios`，使用 kqueue 网络后端，但仓库没有声明 iOS runtime 或窗口渲染 CI 覆盖。
- **Apple runner 容量导致的 CI 假红**：GitHub 托管的 macOS arm64 runner 常因容量不足而不分配，`master` CI 里的 iOS build-only、macOS Cocoa + MoltenVK、macOS native Metal 三个 job 会在约 15~23 分钟后以 "The job was not acquired by Runner of type hosted even after multiple attempts" 结束，step 一个都没执行。2026-11-19 连续三次推送都遇到（run 44542440910、44544115913、44552697245），同期其余 20+ 个 job 全绿。判断方法：`gh run view <id>` 看该 job 是否有 annotation 而无 step；这种红不代表代码问题，重跑或下一次推送通常就绿（如 run 44546550200、44548681996）。
- **macOS Cocoa lane 构建并发上限（2026-11-20）**：`lane-native-surface-cocoa` 用默认的 Unix Makefiles 生成器，不带数字的 `cmake --build --parallel` 会变成不限并发的 `make -j`，在 macOS 15 runner 上偶发 `posix_spawn failed: Resource temporarily unavailable`（最近 39 次中 3 次）。该 lane 的两处构建改为 `--parallel "$(sysctl -n hw.ncpu)"`，与 Ninja 的默认并发一致；其余 Makefiles 生成器 lane 都在 Linux 上，未出现此问题，未改。
- Android 由 CMake 识别为 `android`，使用 epoll；Vulkan 是宿主注入的 compile/integration 路径。启用 `ENGINE_VULKAN=ON` 时必须同时设置 `ENGINE_ANDROID_NATIVE_WINDOW=ON`，并让 CMake 找到 NDK 的 `android/native_window.h`；这不代表完整 Android runtime 支持。
- iOS/Android 的平台契约测试只证明编译路径与宿主注入边界；HarmonyOS 的 Vulkan 状态为 unavailable/unsupported，直到存在 native surface 实现。
- QNX 由 CMake 识别为 `qnx`（`CMAKE_SYSTEM_NAME=QNX`），net_loop 使用 POSIX `poll()` 后端，RHI 解析为 headless（图形 fail-closed），myui 走 dummy PAL 离屏路径；交叉构建用 `cmake --preset qnx-cross`，架构与证据边界见 `docs/qnx_compat.md`。

## 2. 构建配置

### 2.1 引擎（主项目）

#### OpenGL 后端
```bash
cd engine
cmake -B build-gl -DENGINE_RHI_BACKEND=opengl
cmake --build build-gl
```

#### Vulkan 后端（Linux / Windows 默认）
```bash
cd engine
cmake -B build-vk -DENGINE_RHI_BACKEND=vulkan   # 等价于省略该参数；显式写出则缺依赖时报错而不是降级
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
- 后端选择：`ENGINE_RHI_BACKEND=auto|opengl|vulkan|d3d12` 与 `ENGINE_VULKAN` 兼容层。**`auto` 在 Linux/Windows 默认 Vulkan**（2026-10-26 决定；Apple 平台保持原生 Metal 路径）：配置期探测 Vulkan 加载器/头文件 + shaderc，齐全则选 Vulkan，缺失则打印 `falling back to OpenGL` 警告并降级到 OpenGL（最后降级方案，不静默）。显式 `-DENGINE_RHI_BACKEND=vulkan` 缺依赖直接报错；显式 `-DENGINE_RHI_BACKEND=opengl` 或旧开关 `-DENGINE_VULKAN=OFF` 选 OpenGL。已有构建目录里缓存的 `ENGINE_VULKAN` 若是用户显式设置的则继续生效。`auto` 解析为 Vulkan 时默认还会链接 OpenGL 做**运行时降级**（`ENGINE_RHI_MULTI_BACKEND=ON`，可设 OFF 关闭）：Vulkan 设备创建失败即在同一窗口改用 OpenGL；运行时开关 `BREAK_RHI_BACKEND=opengl|vulkan`、`BREAK_RHI_NO_FALLBACK=1`，契约见 `docs/design/rhi_runtime_backend.md`；
  `d3d12` 仅 Windows 可选（计划 D 已落地，见下方「Windows D3D12 后端（计划 D）」节），`metal` 在计划 C 落地前仍被拒绝（非 Apple 平台 FATAL_ERROR）。

## WSI / Vulkan surface 分层（2026-10-15 起）

- **`engine/src/platform/platform_vk_surface.h`** 是 PAL 的 Vulkan surface 创建适配层，两个入口：
  - `platform_vk_create_surface(Platform*, ...)`：经 Platform 句柄创建（内部解包 `platform_surface_native`/`platform_display_native` 后转发到 handles 入口）；
  - `platform_vk_create_surface_handles(surface_native, display_native, ...)`：经裸原生句柄创建——`rhi_vk.c` 的 `vk_init` 持有的是裸句柄而非 `Platform`（`rhi_device_create` 公开 ABI 不变），故消费本入口；结果 surface 的销毁权仍在 `rhi_vk.c`（`vkDestroySurfaceKHR`）。Android 路径成功时本入口对 `ANativeWindow` 持有一个 acquire 引用，失败路径自行 release 回滚。
  - uint64/void* 设计理由：分层规则要求 **platform 层不包含 `<vulkan/vulkan.h>`**——`VkInstance` 以 `void*` 传入、`VkSurfaceKHR`（不可分派 64 位句柄）以 `u64` 传出、`vkGetInstanceProcAddr` 以 `void*` 传入（调用方用 memcpy 桥接函数指针，避免 `-Wpedantic` 的函数指针/void* 强转）。五个 `vkCreate*SurfaceKHR` create-info 的最小 ABI 声明在 `platform_vk_surface_vkabi.h`，由 `test_platform_vk_surface_abi` 对照真实 `<vulkan/vulkan.h>` 逐字段钉死（漂移即编译期/测试期失败）。
- **`engine/src/platform/platform_wsi.h`** 是 header-only 的 WSI 状态机（`PlatformWsiSurface`：UNAVAILABLE/CREATED/RESIZED/LOST/SUSPENDED/DESTROYING），事件源在各 `window_*.c`（Win32/Wayland/Cocoa/Android 四后端均已接入）；尺寸语义（logical 与 drawable 谁是输入，各平台方向不同）由 `platform_size.h` 单点定义，`window_*.c` 只准调用。消费方式：
  - 帧进入 RHI 前查 `platform_wsi_frame_allowed()`——仅 CREATED/RESIZED 放行，SUSPENDED/LOST/DESTROYING/UNAVAILABLE 一律拒绝（应用层据此跳过渲染，而不是让后端在死 surface 上空转）；
  - 销毁门控：`rhi_device_attach_wsi()` 把状态机挂到设备上，`platform_wsi_rhi_teardown_allowed()` 在进入 DESTROYING 后拒绝销毁——销毁顺序契约为 `rhi_device_destroy_ex` 必须先于 `platform_destroy`。
- **`rhi_swapchain_bench`**（`engine/tools/rhi_swapchain_bench.c`）：`./build-*/rhi_swapchain_bench <receipt.json>`，固定 600 帧 clear+present，输出符合 `docs/rhi_benchmark_receipt_schema.md` 的收据（`fps_avg`/`fps_p1`/`frame_ms_avg`/`frame_ms_p99`/`evidence_level=GPU_RUNTIME`/`runner` 等字段）；环境缺显示/GPU 时以退出码 77 标记 unavailable（不算通过，也不产出收据）。元数据由环境变量注入：`RECEIPT_TIMESTAMP`、`RECEIPT_RUNNER`、`RECEIPT_OS_VERSION`、`RECEIPT_BUILD_CONFIG`、`GIT_COMMIT`、`RECEIPT_CPU`、`RECEIPT_RAM`；收据用 `cmake -DRECEIPT=<json> -P engine/tests/test_rhi_benchmark_receipt_validate.cmake` 校验。
- **`ENABLE_GPU_LANES`**：GitHub 仓库变量（Settings → Secrets and variables → Actions → Variables），置为 `1` 才启用 `lane-benchmark-steam-deck-vk`（self-hosted `linux,gpu-vulkan` runner，在 Weston/Wayland 下跑 graphics 套件 + bench 收据 artifact）；未设置时该 lane 被 `if:` 跳过——GitHub-hosted 运行器没有 self-hosted 标签可接单，不加门会永久 pending。

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
| `ENGINE_ENABLE_WAYLAND` | ON | Linux 唯一原生窗口后端；Linux 下设为 OFF 会明确失败 |
| `ENGINE_ENABLE_IPO` | ON | Release 且工具链支持时启用 IPO/LTO |
| `ENGINE_NET_IOURING` | OFF | Linux 实验性 io_uring 网络后端 |
| `ENGINE_ANDROID_NATIVE_WINDOW` | OFF | Android supplied `ANativeWindow` Vulkan 路径 |
| `ENGINE_VULKAN` | OFF | 兼容选择开关；`auto` 在依赖齐全时默认 Vulkan，并查找 Vulkan 与 shaderc |
| `ENGINE_BUILD_TESTS` | ON | 构建 engine 单元测试 |
| `ENGINE_USE_ASAN` / `ENGINE_USE_UBSAN` / `ENGINE_USE_TSAN` | OFF | 分别启用地址、未定义行为、线程消毒器 |
| `RULE_ENGINE_ENABLE_C11_PARALLEL` | OFF | 可选 C11 规则匹配执行器 |
| `RULE_ENGINE_ENABLE_REDIS` | OFF | hiredis 状态提供器；不提供 live Redis 服务 |
| `RULE_ENGINE_REDIS_SOURCE_DIR` | 空 | 可选 Redis/hiredis 源码目录，用于构建私有 hiredis 静态目标 |
| `MYUI_FONT_STB` / `MYUI_FONT_FREETYPE` / `MYUI_IMAGE_STB` | ON | myui 字体与图像后端 |
| `MYUI_UI_YAML` / `MYUI_BIDI` / `MYUI_HARFBUZZ` | ON | YAML、BiDi、可选 OpenType shaping |
| `MYUI_GLES2` / `MYUI_GL_DESKTOP` | ON | 可复用 myui GLES2、桌面 OpenGL 后端 |
| `MYUI_VULKAN` | OFF | 可复用 myui Vulkan 后端 |

软件后端默认使用 8-bit 覆盖率抗锯齿；Wayland EGL 配置优先请求 4x MSAA，驱动不
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
sudo dnf install wayland-devel wayland-protocols-devel libxkbcommon-devel mesa-libEGL-devel mesa-libGL-devel
```

依赖安装 (Ubuntu/Debian):
```bash
sudo apt install libwayland-dev wayland-protocols libxkbcommon-dev libegl1-mesa-dev libgl1-mesa-dev
```

构建命令（默认 Vulkan；显式 OpenGL 是最后降级与对比配置）:
```bash
cd engine
cmake .. -DENGINE_RHI_BACKEND=opengl   # Wayland + OpenGL
cmake .. -DENGINE_RHI_BACKEND=vulkan   # Wayland + Vulkan，缺依赖时失败
```

> **2.0.0 边界**：Wayland 是 Linux 唯一窗口后端，`ENGINE_ENABLE_WAYLAND` 默认 ON；设为 OFF 或 `MYUI_PAL=x11` 均明确配置失败。缺少 Wayland/scanner/xkbcommon 依赖不会回退；实际 OpenGL/fallback 路径缺少 EGL 或 OpenGL 也在 configure 明确失败。`MYUI_PAL` 仅接受 dummy/wayland/win32/cocoa，并在顶层 engine 与 standalone 同样检查目标平台。
Wayland 后端通过 EGL 提供 OpenGL 上下文，通过 `VK_KHR_wayland_surface` 提供 Vulkan 支持。CMake 会调用 `wayland-scanner` 从 `wayland-protocols` 自动生成 `xdg-shell` 客户端代码。
同时生成 `text-input-v3`、`cursor-shape-v1`（可用时）和 tablet 协议绑定；cursor-shape
不可用时自动退回 `wayland-cursor` theme。

myui 的 Break PAL 在 Wayland 下使用共享 RHI surface：逻辑 dialog 不创建第二个 OS window，
并且只有 root window 的 CSD 标题栏允许请求 `xdg_toplevel_move`。Wayland 外部 clipboard
读取由事件循环异步完成；第一次 `Ctrl+V` 会自动重试，不阻塞渲染帧。

### 2.4 Linux 构建矩阵

Linux 平台支持原生 Wayland 与两种图形 API 配置；`auto` 优先 Vulkan，OpenGL 仅为最后降级和渲染对比：

| 配置 | 窗口 | 图形 | CMake 选项 | 验证构建目录 |
|------|------|------|-----------|---------------|
| **Wayland + Vulkan** | Wayland | Vulkan 1.x（默认） | 省略或 `-DENGINE_RHI_BACKEND=vulkan` | `build-verify-wl-vk/` |
| **Wayland + OpenGL** | Wayland | OpenGL 4.x (EGL) | `-DENGINE_RHI_BACKEND=opengl` | `build-verify-wl-gl/` |

示例：
```bash
cd engine
# Wayland + OpenGL（显式最后降级/对比）
cmake -B build-verify-wl-gl -DENGINE_RHI_BACKEND=opengl && cmake --build build-verify-wl-gl

# Wayland + Vulkan（默认）
cmake -B build-verify-wl-vk && cmake --build build-verify-wl-vk
```

#### Compose + MVI 图形与 fuzz 验证

Compose 的 GPU 测试在真实 Wayland 窗口上显式创建所选后端设备（不走回退链），设备报告的后端与请求不符即失败。用法见 `docs/design/compose_mvi.md`。

```bash
# Vulkan（默认）
cmake -S engine -B build-compose-vk -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=vulkan -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-compose-vk --target test_mycompose_gpu -j3
ctest --test-dir build-compose-vk --output-on-failure -j3 -L graphics

# OpenGL（同一 fixture 的对照）
cmake -S engine -B build-compose-gl -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=opengl -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-compose-gl --target test_mycompose_gpu -j3
ctest --test-dir build-compose-gl --output-on-failure -j3 -R '^test_mycompose_gpu_opengl$'

# fuzz smoke（两个 Compose fuzz target 为 EXCLUDE_FROM_ALL，需按名构建）
cmake -S engine -B build-compose-fuzz -DENGINE_BUILD_TESTS=ON -DENGINE_BUILD_FUZZ_SMOKE=ON
cmake --build build-compose-fuzz --target fuzz_mycompose_tree fuzz_mycompose_intent -j3
ctest --test-dir build-compose-fuzz -L fuzz -j3

# libFuzzer 覆盖率引导（仅 Clang；目标同样 EXCLUDE_FROM_ALL）
CC=clang cmake -S engine -B build-libfuzzer -G Ninja -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON \
  -DENGINE_BUILD_FUZZ_SMOKE=ON -DENGINE_BUILD_LIBFUZZER=ON
cmake --build build-libfuzzer --target libfuzz_core_app_network libfuzz_core_app_scenario libfuzz_core_app_checkpoint
ctest --test-dir build-libfuzzer -L libfuzzer --output-on-failure
```

`ENGINE_BUILD_LIBFUZZER=ON` 要求 Clang（GCC 或 MSVC 下 configure 直接 FATAL）。`libfuzz_core_app_network_run` 以 `-runs=200000 -seed=1 -max_len=2048` 运行，种子取自已提交的 `engine/tests/data/core_app_network_corpus`（只读），新输入写入构建树下的 `libfuzz_core_app_network_corpus/`。`libfuzz_core_app_scenario_run` 以 `-runs=200000 -seed=1 -max_len=70000` 运行，种子取自 `engine/tests/data/core_app_scenario_corpus`，新输入写入 `libfuzz_core_app_scenario_corpus/`。`libfuzz_core_app_checkpoint_run` 以 `-runs=50000 -seed=1 -max_len=2048` 运行，种子取自 `engine/tests/data/core_app_checkpoint_corpus`，新输入写入 `libfuzz_core_app_checkpoint_corpus/`；它在构建树下建 `fuzz_core_app_ckpt_<pid>/libfuzz/` 放四个固定载荷，每个输入写成 `manifest.core`，进程退出时删除。三个目标都把被测源文件直接编进目标，使其带覆盖插桩。失败时 libFuzzer 在工作目录留下 `crash-*` 文件，可直接作为参数重放：`./libfuzz_core_app_network crash-<hash>`（scenario 同理）。

transport 的 stop 超时单元测试需要 `CORE_APP_ENABLE_NETWORK=ON`、`BREAK_ENABLE_SNOWFLAKE=ON` 和 `BREAK_ENABLE_CRYPTO=ON`（非 Windows）：

```bash
cmake --build build-network --target test_core_app_net_transport
ctest --test-dir build-network -R '^test_core_app_net_transport$' --output-on-failure
```

它链接 `break_net_test`，证书取自 `${SNOWFLAKE_SOURCE_DIR}/tests/common/fixtures/ssl`，单次约 1.5 s（注入的 step 延迟超过 1000 ms 的 stop 超时）。

GPU 测试需要 Wayland 会话（`WAYLAND_DISPLAY`）；没有显示或设备时退出 77（CTest 记为 Skipped），在目标环境必须为 0 skip。日志的 `device:` 行给出设备名与类型，`device_class:` 行给出 `hardware-gpu` 或 `software`；lavapipe/llvmpipe 是软件渲染，不能作为硬件 GPU 证据。设置 `MYCOMPOSE_GPU_REQUIRE_HARDWARE=1` 时，软件设备直接 FAIL；CI 的 llvmpipe lane 不设置它。

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

#### Linux NVIDIA Vulkan ICD 的 LSan 归属
NVIDIA Vulkan ICD 与 GL 共用 `libGLX_nvidia.so`。本机证据表明，loader 扫描/创建/销毁
instance 后，`libnvidia-glcore.so` 和 `libnvidia-glsi.so` 的进程生命周期缓存会被
LeakSanitizer 报告；这些分配不经过本仓库的 allocator，也没有可由仓库调用的公共关闭
接口。`test_myui_window_manager` 和 `test_myui_vgcanvas_backend` 因而只在 ASan/Linux
且实际启用 Vulkan 时由 CTest 设置 `VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1`，
保留模块名供 LSan 归因；`engine/tests/test_vulkan_lsan.h` 只在这两个测试二进制中
suppress 上述两个 NVIDIA 模块。它不 suppress libdbus、其他库或项目分配，也不关闭
ASan/LSan。

直跑这两个测试时使用与 CTest 相同的环境（不带该环境的裸直跑仍可能报告第三方缓存）：
```bash
VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1 ./build-asan/test_myui_window_manager
VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1 ./build-asan/test_myui_vgcanvas_backend
```
如果报告包含项目帧或新的第三方库，应先重新做归属调查，不要扩大这两条 suppression。

#### UndefinedBehaviorSanitizer 版本
`ENGINE_USE_UBSAN` 默认为 OFF；GCC/Clang 开启后使用 `-fsanitize=undefined`，不改变默认构建：
```bash
cd engine
cmake -B build-ubsan -DENGINE_USE_UBSAN=ON
cmake --build build-ubsan
```

### 2.5 Windows 平台构建

#### Windows 上的 OpenSSL（`BREAK_ENABLE_CRYPTO`，默认 ON）

`break_crypto` / `break_update` 需要 OpenSSL libcrypto。CMake 自带的 `FindOpenSSL`
只在 MSVC 分支里搜索安装器目录 `lib/VC/<arch>/<crt>`，所以：

- **MSVC**：`find_package(OpenSSL)` 自己能找到 `C:/Program Files/OpenSSL*`，无需额外参数。
- **Clang / MinGW**：`engine/CMakeLists.txt` 在配置期按顺序探测 `-DOPENSSL_ROOT_DIR`、
  `%OPENSSL_ROOT_DIR%`、`%ProgramFiles%\OpenSSL`、`%ProgramFiles%\OpenSSL-Win64`、
  `C:\OpenSSL-Win64`，命中安装器布局（`lib/VC/x64/MD/libcrypto.lib` 与 `libssl.lib`）后自动
  设置 `LIB_EAY`/`SSL_EAY`。MSYS2/MinGW 自带 OpenSSL（编译器旁 `../lib/libcrypto.dll.a`）时直接使用，不探测安装器目录。
  自动探测不到时手动传 `-DOPENSSL_ROOT_DIR=<前缀> -DLIB_EAY=<libcrypto.lib> -DSSL_EAY=<libssl.lib>`，
  或 `-DBREAK_ENABLE_CRYPTO=OFF`。
- 运行测试时 `libcrypto-*-x64.dll`（安装器的 `bin` 目录）须在 `PATH` 上。
- 契约测试（crypto/update/crash）用 `llvm-nm`/`nm` 做导出符号检查，Windows 上会忽略 UCRT 内联的
  `sprintf`/`_snprintf` 等头文件产物；最小链接用例使用与树一致的 CRT（MSVC 下 `/MD` 或 `/MDd`，
  Clang ASan 树附带 `-D_DLL -D_MT --dependent-lib=msvcrt`）。

#### 本机显示驱动故障会让图形测试假失败（2026-10-31 记录）

显示驱动更新后如果没重启，两个显示适配器可能停在 `CM_PROB_FAILED_POST_START`
（`Get-PnpDevice -Class Display` 可见，`nvidia-smi` 会报“权限不足”）。这时 OpenGL
上下文退回 `1.1.0 (Microsoft Corporation / GDI Generic)` 软件渲染，引擎需要 GL 1.3+，
于是 `test_vulkan`、`rhi_swapchain_bench`、`test_myui_break_rhi_clip` 段错误，
demo 仍能跑但帧时间会离谱地抖动（实测 35–600 ms，恢复后 32–40 ms）。

排查顺序：先看 demo 日志里的 OpenGL 版本号是不是 `4.x NVIDIA`；不是就查适配器状态。
恢复不用重启整机（要管理员；UAC 为 `ConsentPromptBehaviorAdmin=0` 时
`Start-Process -Verb RunAs` 不弹提示）：

```powershell
pnputil /restart-device "PCI\VEN_10DE&DEV_28A0&SUBSYS_13021D05&REV_A1\<instance-id>"   # instance id from Get-PnpDevice
```

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
该用例的剪贴板回归检查会改写系统剪贴板，并使用真实 CF_UNICODETEXT 验证无 NUL 终止输入的
边界；运行前请保存需要保留的剪贴板内容。远程桌面剪贴板同步可能短时占用全局剪贴板，
首次 `OpenClipboard` 最多重试约 5 秒；持续不可用仍判失败，不跳过检查。

跨平台测试写临时文件时，使用 `test_framework.h` 的 `test_tmp(buf, cap, name)` 和
`TEST_MKDIR`/`TEST_RMDIR`，不要在共享测试里直接使用 `unistd.h`、固定 `/tmp` 名称或
`mkdir(path, mode)`：`unistd.h` 不能由 Clang/MSVC 直接包含，MinGW 的 `_mkdir` 只有一个
参数，固定名称还会让并行构建树互相删除文件。`test_world_stream_world` 在 2026-11-02
按此约定修复，真实 VFS 和文件内容断言不变。

fork 子进程的测试在 POSIX 上应包含 `tests/test_fork.h`，用 `test_waitpid_deadline(pid, &status, timeout_ms)` 代替无界 `waitpid(pid, &status, 0)`：子进程超过期限仍未结束时会被 `SIGKILL` 并回收，函数返回 0 并打印 `CHILD TIMEOUT after <ms> ms (killed)`，超时时 `*status` 被清零，调用方必须先断言返回值等于 `pid` 再看 `*status`。父进程若还要从子进程写的管道读数据，用 `test_read_deadline(fd, buf, len, timeout_ms)`，超时返回 -2 并打印 `PIPE TIMEOUT after <ms> ms`。这样挂起会变成本用例的明确失败，而不是拖到外层 CTest 守护超时。在 glibc 严格 C11 下包含者需要 `_POSIX_C_SOURCE >= 199309L`；macOS 上不要定义它，否则会降低 `__DARWIN_C_LEVEL` 并隐藏 `test_framework.h` 用到的 `snprintf`，默认级别已声明所需函数。该头文件独立于 `test_framework.h`，后者的其余包含者不受影响。

`core_app` 的 11 个正式资产由真实 baker 生成并逐字节比较；其中 Lua、scenario 和
`actors.sidecar` 在 `.gitattributes` 固定为 LF，避免 `core.autocrlf=true` 将工作树检出为
CRLF 后产生伪差异。Windows 测试用 `_spawnv(_P_WAIT)` 直接启动 baker，不经过 `system()`
的命令处理器转发；路径参数按 CRT 规则加双引号，并有含空格目录的真实子进程回归用例。
进程失败时输出实际命令和退出状态，不改变资产生成与校验内容。

编辑器 `--input-script` 的 `move_to <list>@<row>` 定位的是控件行，不会把列表视口外的
部分裁掉为可点击区域。目标行没有完全可见时，先 `type <filter>` 将它过滤为第一行，再
执行 `move_to ...` 和 `click left`；不能把被裁剪行的中心当作可点击位置。Windows/OpenGL
已于 2026-11-02 通过此路径验证命令面板的主题切换和设置持久化。

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

上述配置在 `/W4 /WX /utf-8` 以及 `/experimental:c11atomics` 下构建。早先记录的「完整构建通过、非图形 CTest `56/56`」只对当时的代码成立；当时 CI 没有 MSVC lane，之后新增的代码曾让 MSVC 构建失败（10 个文件的 C4090/C4132/C4456/C4310/C4701），2026-10-27 已修复，并在 MSVC 19.51.36260 上重新验证：全量构建 0 警告，非图形 CTest（含 5 个 fuzz 冒烟）`186/186` 通过，包括 `test_platform_win32_runtime`。现在 CI 有 `lane-headless-windows-msvc`（同样的配置与 `-LE graphics` 筛选），新增代码后以它为准；本机重跑上面三条命令仍可复现。CI 另外显式构建并执行
`test_platform_config`、`test_platform_null_safety` 和 `test_platform_win32_runtime`，避免平台
runtime 门禁仅依赖全量测试筛选。这提供的是非图形、headless
Win32 平台证据，不证明 WGL、Vulkan、GPU、present 或图形 runtime，也不证明 Windows Vulkan 构建。

或显式指定 MSVC 工具链文件：
```cmd
cmake -S engine -B build-msvc -DCMAKE_TOOLCHAIN_FILE=engine/toolchain-msvc.cmake -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-msvc --parallel
```

#### Windows ARM64 原生（Snapdragon X Elite 本机）

命令与上面的 MSVC 配置相同，只差环境初始化：在 ARM64 主机上调
`vcvarsall.bat arm64`（生成 HostARM64→ARM64 的原生工具链，不经 x64 模拟），Ninja 可用
VS 自带的 `Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe`。CMake 的
`FindOpenSSL` 从 3.27 起在 MSVC 分支识别 `lib/VC/arm64/<CRT>` 布局（对应
`MD`/`MDd` 目录下的 `libcrypto.lib`），因此需要 ARM64 版 OpenSSL（ShiningLight 的
`Win64ARMOpenSSL` 安装器，winget id `ShiningLight.OpenSSL.Dev`）；x64 的 OpenSSL 安装包
对 ARM64 构建不可见，configure 会按预期 fail-closed 报 `Could NOT find OpenSSL`。机器级
安装需要 UAC；非提权时可从 MSI 管理安装取出的内嵌 Inno 安装程序用 `/CURRENTUSER`
安装到用户可写前缀。OpenSSL ARM64 的 `bin`（`libcrypto-4-arm64.dll`）和 ARM64 Python
要在运行 ctest 前加入 `PATH`，构建与测试保持同一个 `vcvarsall.bat arm64` 会话，供嵌套
契约继承 MSVC 环境。完整命令、每用户安装步骤与实机结果见
`docs/testing/cross_platform_matrix.md` §4.7（W9）。

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
cmake -B build-mingw -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc
cmake --build build-mingw
ctest --test-dir build-mingw -LE graphics --output-on-failure
```

2026-10-27 在 MSYS2 UCRT64 的 GCC 16.2 上验证：此前构建失败（GCC 的 `-Werror` 拒绝 `GetProcAddress`/`wglGetProcAddress` 结果直接强转为函数指针、`net_loop_iocp.c` 的恒假比较、`PlatformConfig` 在 Win32 测试里的省略初始化、`verify_pak.c` 的 `snprintf` 截断），现已修复，全量构建 0 警告，非图形 CTest（含 5 个 fuzz 冒烟）`186/186` 通过。函数指针转换统一走 `platform/win_proc.h` 的 `WIN_PROC_LOAD`（memcpy，不触发 `-Wcast-function-type`/`-Wpedantic`）。CI 现有 `lane-headless-windows-mingw`（镜像自带的 MinGW-w64 gcc，非 MSYS2 UCRT64 的 GCC 16.2，版本不同）。

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

`BREAK_ENABLE_CRYPTO` 默认开启，需要 OpenSSL（libcrypto）。macOS 没有系统自带的
可链接版本；OpenSSL 不在 Homebrew 默认前缀时，配置时加
`-DOPENSSL_ROOT_DIR=<openssl 前缀>`。契约测试的最小链接用例会用解析到的
`OPENSSL_CRYPTO_LIBRARY`，嵌套配置（`test_rhi_backend_selection`）也会继承该前缀；
无 OpenSSL 的主机可整体以 `-DBREAK_ENABLE_CRYPTO=OFF` 配置，嵌套配置同样继承
该开关（后端选择契约与 crypto 无关）。
`break_http` 在 `-Werror` 下同时支持 OpenSSL 3.x 与 4.x：4.0 起主机名校验用
`SSL_set1_dnsname`（`SSL_set1_host` 已弃用），按 `OPENSSL_VERSION_MAJOR` 选择。

QUIC 传输（可选）：`-DBREAK_ENABLE_QUIC=ON` 在 Snowflake 之上启用
`break_net_quic`（契约见 `docs/design/quic_transport.md`）。需要
`BREAK_ENABLE_SNOWFLAKE=ON` + `BREAK_ENABLE_CRYPTO=ON` + OpenSSL ≥ 3.5（QUIC TLS
接缝；本机自编译的 4.x 可用），Snowflake 会构建其 vendored ngtcp2 v1.25.0
（`third_party/NGTCP2_PROVENANCE.txt` 钉版）。v1 仅 POSIX/IPv4。构建并验证：

```bash
cmake -S engine -B build-quic -G Ninja -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=<pinned snow checkout> -DBREAK_ENABLE_QUIC=ON \
  -DOPENSSL_ROOT_DIR=<openssl-3.5+ 前缀>
cmake --build build-quic
ctest --test-dir build-quic -R "quic" --output-on-failure
```

独立弱网 CI 位于 `.github/workflows/quic-weak-network.yml`：macOS 15 上检出
`BREAK_SNOWFLAKE_PIN` 对应的 Snowflake，使用 brew 的 OpenSSL 3.5+，只构建 QUIC
测试目标并以四路并行执行 `ctest -L weak_network`。可在 Actions 的
**QUIC Weak Network** 工作流中单独手动触发；相关网络源码或测试变更也会自动触发。

Snowflake 仓库需要认证读取。仓库维护者需配置仅含 `contents:read` 权限的
`SNOWFLAKE_READ_TOKEN` Actions secret；未配置时工作流明确记录 **UNAVAILABLE**，
不会把未执行记作通过。配置后日志要求精确 `4/4` 通过，并上传
`quic-weak-network-log`。本地等价命令：

```bash
cmake --build build-quic --target test_break_net_quic test_break_net_quic_cpp20
ctest --test-dir build-quic -L weak_network -j4 --output-on-failure --no-tests=error
```

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
cmake -B build-gl -DENGINE_RHI_BACKEND=opengl
cmake --build build-gl
```

### 2.7 CMake 选项
| 选项 | 默认值 | 说明 |
|------|--------|------|
| ENGINE_VULKAN | OFF | 兼容选择开关；`auto` 默认优先 Vulkan，显式 OpenGL 为最后降级；macOS Cocoa 路径自动使用 Vulkan/MoltenVK |
| ENGINE_ENABLE_WAYLAND | ON | Linux 唯一窗口后端；Linux 下关闭会配置失败 |
| ENGINE_USE_ASAN | OFF | 启用 AddressSanitizer（GCC/Clang 使用 `-fsanitize=address`，MSVC 使用 `/fsanitize=address`） |
| ENGINE_USE_TSAN | OFF | 启用 ThreadSanitizer（GCC/Clang 使用 `-fsanitize=thread`；用于线程安全专项验证） |
| ENGINE_USE_UBSAN | OFF | 启用 UndefinedBehaviorSanitizer（GCC/Clang 使用 `-fsanitize=undefined`；MSVC 不启用） |
| ENGINE_BUILD_TESTS | ON | 构建并注册 CTest 测试；关闭后不注册测试 |
| ENGINE_ENABLE_IPO | ON | Release 构建中在工具链支持时启用 IPO/LTO，仅作用于 `engine` 静态库 |
| MYUI_FONT_FREETYPE | ON | 找到 FreeType 时启用 hinted 字形和 TTC 多字面选择；CJK 默认字体需要此选项 |
| MYUI_FONT_STB | ON | 启用 `stb_truetype` 独立 TTF/OTF 回退 |
| MYUI_GLES2 | ON | 探测可用依赖后启用可复用 GLES2 后端 |
| MYUI_GL_DESKTOP | ON | 探测可用依赖后启用桌面 OpenGL 后端 |
| MYUI_VULKAN | OFF | 启用可复用 Vulkan 后端；需要 Vulkan/shaderc 依赖 |
| MYUI_PAL | dummy | 可选 dummy/wayland/win32/cocoa；非法值和不匹配的目标平台在 configure 明确失败 |
| ENGINE_ANDROID_NATIVE_WINDOW | OFF | Android Vulkan 必须开启，并提供 NDK `android/native_window.h` |
| RULE_ENGINE_ENABLE_C11_PARALLEL | OFF | 启用可选 C11 规则并行执行器；不代表全引擎句柄线程安全 |
| RULE_ENGINE_ENABLE_REDIS | OFF | 启用 Redis 状态提供者；需要 hiredis/Redis 源目录 |
| RULE_ENGINE_REDIS_SOURCE_DIR | (空) | 指定 Redis/hiredis 源目录，仅在 Redis 选项启用时使用 |
| CMAKE_C_STANDARD | 11 | C 语言标准 |
| CMAKE_C_COMPILER | (自动) | 指定 C 编译器（`gcc` / `clang` / `cl`） |
| CMAKE_CXX_COMPILER | (自动) | 指定 C++ 编译器（`g++` / `clang++` / `cl`） |
| CMAKE_TOOLCHAIN_FILE | (无) | 使用工具链文件（见上方编译器支持矩阵） |

> 编译器标志由 CMake 根据 MSVC / Clang / GCC **自动检测并应用三路分支**，无需手动指定告警/优化标志。
> MSVC 的 C++20 target 额外使用 `/Zc:__cplusplus`，确保 `__cplusplus` 正确报告 202002；Windows Clang ASan lane 对 `CMAKE_C_FLAGS` 与 `CMAKE_CXX_FLAGS` 同时传入 `-fsanitize=address -fno-omit-frame-pointer`，runtime DLL 部署保持不变。WGL loader 测试只在非 Windows 模拟分支使用 stub 头、`__stdcall` 和 API mock；真实 Windows 使用 SDK `windows.h` 与系统 `opengl32`，不再定义 `LoadLibraryW/GetProcAddress/FreeLibrary`，避免与 kernel32 import library 重复定义。真实分支先创建隐藏 Win32 窗口，设置 pixel format，并以 `wglMakeCurrent` 绑定实际 WGL context，之后才允许 `gladLoadGL` 和现代/legacy 解析断言；现代入口直接对照真实 `wglGetProcAddress` 结果，legacy 入口按 GLAD 的实际顺序优先对应当前 context 的 WGL 结果，WGL 返回 NULL 时必须对应真实 `GetProcAddress` 导出。驱动可提供不同于 DLL 导出地址的有效转发入口，不能只比较 DLL 地址；GL 版本查询仍必须成功。清理先释放 current context，再删除 context、DC、窗口和 class，失败路径同样覆盖；没有扩大为 GPU 像素测试。Linux 继续用可控 mock 验证 WGL 现代入口和 DLL fallback。benchmark 的 Release+IPO lane 配套使用 `clang-18`、`clang++-18` 与 `lld-18`，不让默认 GNU C++ 接管带版本后缀的 LLD；通用 `toolchain-clang-linux.cmake` 同样显式设置 `clang`/`clang++`/`lld`。

`ENGINE_BUILD_TESTS=ON` 时，configure 使用 `find_package(Python3 COMPONENTS Interpreter REQUIRED)`
定位 Python，并用 `echo posix-bash-ok` 探测选择可用的 POSIX bash。Windows 上
`System32\bash.exe` 只是 WSL 启动器，探测失败时改用 git 同目录的 bash，不把它当作
shell helper。CTest 不依赖裸 `python3`，shell helper 显式经该 Bash 启动。CI image 合同只使用
Python 标准库，不要求 PyYAML。Windows 测试需要可用的 Python 与能通过上述探测的 bash（通常是
Git Bash）；工作流 YAML 是 UTF-8，Python 契约 reader 和这些合同的子进程输出必须显式使用
`encoding="utf-8"`，不能依赖宿主的活动代码页；macOS rollback 行为合同不依赖 GNU sort。

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
- Android NDK r27c（27.2.12479018）；Xcode `>=15.4`，CI 在 macos-15 arm64 上钉
  `/Applications/Xcode_16.4.app`（macOS 15.5 SDK、iOS 18.5 simulator；macOS 侧
  glslc/spirv-cross/cmake/ninja 的 pin 见 LOCKED_DEPENDENCIES.md 注记）；Windows SDK 10.0.26100.0。
- D3D12 Agility SDK 1.619.6（runtime-shipped；`engine/external/d3d12/agility_sdk_lock.txt`
  以 SHA512 复核 nupkg 与 D3D12Core.dll）。
- Linux CI 依赖（noble）：`libvulkan-dev=1.3.275.*`、`libshaderc-dev=2023.8*`、`cmake=3.28.*`；另需 `libssl-dev`（noble 为 OpenSSL 3.0.x，未钉小版本，随 apt 安全更新），`BREAK_ENABLE_CRYPTO` 默认开启时缺它整个 Linux configure 都会失败。自 R700 起这些包预装在容器镜像 `ghcr.io/konyka/break-ci-linux:latest` 里（`.github/docker/ci-linux.Dockerfile`，由 `.github/workflows/ci-image.yml` 构建发布），Linux lane 在镜像里运行，job 里不再执行 `apt-get install`。要改包或版本：改 Dockerfile，等 `ci-image` 工作流构建完成后再触发 CI。注意：同一次 push 会同时启动 `ci-image` 与 `CI`，此时 Linux lane 拉到的仍是旧镜像（2026-10-28 加 `libssl-dev` 时就是这样：10 个 Linux 任务拉到旧镜像 digest 全部 configure 失败），需要在镜像发布后再推一次提交或手动触发 `CI`（`workflow_dispatch`；只读令牌无权限重跑，需在 GitHub 页面操作）。`lane-proton`（周跑，需要 i386 + wine）仍在 job 里 apt 安装。

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

2026-10-27 日常同步与复核：本轮从 `@65f8aae0` 同步至 `@83f5670e`，累计 13 个远程
提交，未发生冲突；iOS 修复 rebase 后也完成复验。Metal 与 MoltenVK 全量 CTest 均
**191/191**（D3D12 dependency gate 按平台跳过），Metal `-L graphics` **5/5**、资源
**48/48**、音频 **17/17**，指定的 5 个 fuzz targets 均构建。两后端分别执行
`BREAK_SCREENSHOT=60 ./build-macos-current/engine_demo --frames 70` 和对应的
`build-macos/engine_demo --frames 70`，实际查看截图后确认 3D 场景与 UI 可见、朝向正确；
光照、材质与水面仍有差异，不宣称逐像素一致。远程新增 Win32、GL/myui 修复与本地
iOS 改动均保留，未使用 force push。

2026-10-28 同步与代码 review：本轮从 `@fb0eb120` 快进（`--ff-only`）到 `@e92ac1bc`，累计
15 个远程提交（Windows Clang/MSVC/MinGW 构建修复、Release 配置的 shipped-binary 契约
`test_release_config_contract`、Linux CI 镜像与 OpenSSL/libm 修复），无冲突。Metal 全量
CTest **226/226**、graphics **5/5**，MoltenVK **227/227**（两者仅 D3D12 dependency gate
按平台跳过）。review 发现并修复三处：(1) `sb_append`（`rule_engine/builtins.c`）新加的
溢出判断在 `size == PTRDIFF_MAX` 时 `PTRDIFF_MAX - size - 1u` 回绕，放过了 `need`
超过 `PTRDIFF_MAX` 的请求，改为 `size >= PTRDIFF_MAX` 先行拒绝；(2) 远程为 Linux 链接
顺序给 `lua` 目标加的 `PUBLIC m` 在 macOS 上让每个链接 lua 的目标都出现
`ld: ignoring duplicate libraries: '-lm'`，改为仅非 Apple 的 UNIX 添加（libSystem 自带
数学函数）；(3) 仓库根目录的 `Testing/Temporary/*`（ctest 输出）被误跟踪，取消跟踪并
加入 `.gitignore`。`editor` 目标自身的 `m engine ... engine` 重复链接仍会产生同类提示，
属远程既有写法、无功能影响，本次未改。本轮无渲染代码变化，未重复实机截图，证据等级
不变。

2026-10-28 晚间同步与 review：从 `@4326287e` 快进到 `@6c7cf70d`（17 个远程提交：编辑器
图片预览与纹理热重载、`BREAK_EDITOR_INPUT_SCRIPT` 脚本化输入回放（默认 OFF）、BreakUI
丢鼠标按键修复、发布二进制去掉测试钩子），无冲突。Metal CTest **228/228**、graphics
**5/5**，MoltenVK **229/229**。用 `-DBREAK_EDITOR_INPUT_SCRIPT=ON` 单独构建编辑器，按脚本
回放按键并截图：`test_editor_input_script` 通过，该配置下 `test_release_config_contract`
按设计报“带 input replay 符号”（macOS 上符号 `_` 前缀处理确实生效）。实机截图暴露
两处 Metal 缺陷并已修复（`rhi_metal.m`）：(1) `rhi_cmd_set_viewport` 在离屏/MRT pass 上
不翻转，而 myui 画布在 `rhi_end_frame` 里用它重设视口，整屏 UI 存成上下颠倒（VK 已按
目标约定处理，见 `rhi_vk.c`）；现在离屏/MRT pass 用负高度视口，swapchain 与深度 pass
不变；(2) `editor_color` 管线的 `u_mvp@0`/`u_color@64` 在 Metal 的 push 偏移表里缺失，
编辑器 3D 视口初始化报 `uniform resolve failed`；现按 12 字节顶点步长的管线补上这两项，
其它描述符仍走原表（`push_offsets_match_vk_golden` 不变）。新增 `test_rhi_metal_resources`
用例 `set_viewport_on_offscreen_keeps_ndc_minus_y_in_row_zero` 与
`editor_color_pipeline_resolves_mvp_and_color`，回退修复后两者均失败。修复后编辑器截图
方向正确、日志不再有 `uniform resolve failed`；视口内是空场景的清屏深灰，3D 代理几何
的像素级效果本轮未单独验证，证据等级不变。

2026-10-29 同步与代码 review：从 `@e2bb5661` 快进到 `@8ab8700e`（7 个远程提交：BreakUI
画布裁剪文字/图片、编辑器 JetBrains 暗色主题、大纲选中行高亮、crash 测试期望值饱和），
无冲突。Metal CTest **230/230**、graphics **6/6**，MoltenVK **231/231**（仅 D3D12
dependency gate 按平台跳过）。review 读完画布裁剪（`clip_quad` 的 UV 随裁剪缩放）、
控件绘制与主题改动，未发现需要修的问题。实机截图（`BREAK_EDITOR_INPUT_SCRIPT=ON`
编辑器加两个实体并选中）暴露一处 Metal 缺陷并已修复：`rhi_screenshot` 在 Metal 上返回
drawable 原生 BGRA，而 `rhi.h` 约定 RGBA8（VK 对 BGRA swapchain 做交换），调用方
（`main.c` 的 BMP、编辑器 PPM）再按 RGBA 处理一次，结果 Metal 截图红蓝互换：编辑器里
蓝色“添加”按钮和选中行显示为橙色，`engine_demo` 的 Metal/VK 平均色在 R/B 上互换
（142.4/145.3 对 145.2/142.3）。现在 Metal 在 BGRA 交换链上读回后交换 R/B，同一机位
Metal 与 VK 平均 RGB 为 145.3/148.6/142.4 对 145.2/148.5/142.3；`test_rhi_metal_resources`
里两个读回用例的期望字节序同步改为 RGBA（修复前这两个用例对 RGBA 期望失败，已先验证
红灯）。这只影响截图读回，不影响屏幕上的实际渲染，证据等级不变。

2026-10-29 定时复核：从 `@37b87abd` 快进到 `@eed8c433`（2 个远程提交：BreakUI 画布按
绘制顺序出图、编辑器输入框焦点环），无冲突、无本地改动。Metal CTest **230/230**、
graphics **6/6**（含 5 个 fuzz 目标构建），MoltenVK **231/231**，仅 D3D12 dependency
gate 按平台跳过。`engine_demo` 机位 `BREAK_CAM=0,9,16,0,-25 BREAK_UI=0
BREAK_SCREENSHOT=60` 两后端截图目视确认：朝向正确、3D 场景与 UI 均可见，Metal 与
MoltenVK 画面基本一致；未发现回归，本次无代码修改，证据等级不变。

2026-10-29 同步后 review：从 `@8b0dc8a0` 快进到 `@70fecbca`（4 个远程提交：编辑器浅色
主题与命令面板切换、自带 JetBrains Mono / Noto Sans SC 字体、面板点击修复、输入脚本带引号
参数），无冲突。同步后两套全量测试各有 1 个失败：`test_myui_font` 的
`bundled_noto_sans_sc_loads_and_shapes_cjk`（`font is NULL`）。根因是本机没有 FreeType，
走内置 STB 光栅器，`stb_validate_cmap` 把 platform 0 / encoding 5（format 14 变体选择符，
不是字符映射）也当作必须支持的子表，且 stb_truetype 取最后一个 Unicode 记录会误选
format 14。已修复（`my_font_stb.c`，新用例修复前失败即回归测试）。推送前远程又新增 4 个
提交（工具窗口标签页、主题/语言/标签页持久化 `editor_settings`），无文件重叠，普通 merge 后
重建：Metal CTest **231/231**、graphics **6/6**，MoltenVK **232/232**，仅 D3D12 dependency
gate 按平台跳过。
`BREAK_EDITOR_INPUT_SCRIPT=ON` 编辑器脚本截图目视确认：英文深色、中文深色（Noto Sans SC）、
命令面板列表及通过面板切换“主题：浅色”均渲染正常。FreeType 路径本机未构建，未验证；
17 MB 字体入库对仓库体积的影响由维护者决定。证据等级不变。

2026-10-29 第二次 review（远程无新提交）：读了上一轮合入的 `editor_settings` 与标签页代码，
发现两处问题并修复。(1) `--input-script` 回放会读写真实的 `~/.config/break/editor.ini`，
脚本里切主题会改掉用户偏好、也会被已有偏好影响截图；现在带脚本运行时默认不持久化，
只有显式设置 `BREAK_EDITOR_SETTINGS` 才用（指向临时文件）。(2) `make_parents` 在任一级
`platform_mkdir` 失败时整体返回失败，Windows 盘符前缀（`C:`）等不可创建的父级会让保存永远
失败；改为忽略中间级失败，叶子目录缺失时由文件打开报错。实机（Metal，`INPUT_SCRIPT=ON`）：
脚本切浅色后 `BREAK_EDITOR_SETTINGS` 指向的临时文件含 `theme=light`，再次启动（不带
`--lang`）为浅色；不设该变量时 `~/.config/break` 不会被创建。Metal CTest **231/231**、
graphics **6/6**，MoltenVK **232/232**，仅 D3D12 dependency gate 按平台跳过。Windows 的
`%APPDATA%` 路径与盘符场景未在本机验证。证据等级不变。

2026-10-30 定时复核：从 `@cb42e226` 快进到 `@a075088c`（108 个远程提交，177 个文件：编辑器
多选/复制/框选/网格/视角快捷键/场景管理、`editor remote` 密钥环与 SAVE/LOAD/CAMERA_SET、
更新清单与灰度、locale 无关的数字解析、跨平台 CI 修复等），无冲突、无本地改动。Metal CTest
**237/237**、graphics **6/6**（含 5 个 fuzz 目标构建），MoltenVK **238/238**，仅 D3D12
dependency gate 按平台跳过，构建无 error/warning（除已知的 duplicate libraries 提示）。
`engine_demo` 机位 `BREAK_CAM=0,9,16,0,-25 BREAK_UI=0 BREAK_SCREENSHOT=60` 两后端截图目视
确认：朝向正确、地形/角色/UI 均可见；同步前 `cb42e226` 的 MoltenVK 对照 mad **0.35**，
Metal 与 MoltenVK 互相 mad **1.09**，平均 RGB 一致。`BREAK_EDITOR_INPUT_SCRIPT=ON` 编辑器
脚本（Metal，`BREAK_EDITOR_SETTINGS` 指向临时文件）：添加两个实体、`Ctrl+A` 选中 2 个、
`Ctrl+D` 复制为 4 个、`Home` 与 `1`，全部 expect 通过（退出码 0），截图中统计浮层
（Entities 4 / Selected 2）、资源过滤框、工具窗口标签页、前视图均正常。未发现回归，本次无
代码修改；`editor remote` 密钥环、更新清单工具等没有 macOS 实机场景，只有自动化测试覆盖。
证据等级不变。

2026-10-30 第二次 review：从 `@f0347bed` 快进到 `@f1a88780`（5 个远程提交：视口线框模式
`Z`/命令面板/`wireframe=` 设置/远程 VIEW bit 3、`editor remote` HISTORY（消息 18）、
`test_runtime_io` 双重释放子进程信号诊断），无冲突、无本地改动。读了全部代码 diff：线框模式
把每个代理画成 12 条边并保留选中描边，设置序列化新增键在 8 KiB 缓冲内，HISTORY 响应长度
与 127 字节描述上限一致，消息注册表与 fuzz id 范围同步到 4..18；`Z` 与既有单键快捷键走同
一分发路径，`Ctrl+Z` 仍是撤销。未发现需要修复的问题，本次无代码修改。Metal CTest
**237/237**、graphics **6/6**，MoltenVK **238/238**，仅 D3D12 dependency gate 按平台
跳过，构建无 error/warning。`BREAK_EDITOR_INPUT_SCRIPT=ON` 编辑器脚本（Metal）：添加实体与
Transform 后按 `Z`，视口只剩 12 条边且可透过看到网格线，再按 `Z` 回到实心立方体，`Z` 三次
后设置文件含 `wireframe=on`。远程 HISTORY 与 VIEW bit 3 只有自动化测试覆盖，无 macOS 实机
场景。证据等级不变。

2026-10-31 定时复核：从 `@5af634ad` 快进到 `@91b85ea7`（26 个远程提交，81 个文件：按来源的
撤销/重做与 `UNDO_OWN`/`REDO_OWN`、场景纹理视图、`break_http` HTTP/TLS 传输与参考更新服务器、
`break_authority`/`break_integrity`、崩溃符号化/聚类/上传、keygen 与 manifest 工具加固、
macOS 测试适配等），无冲突、无本地改动。**发现并修复 1 个构建回归**：本机 OpenSSL 4.0.3 下
`break_http.c` 的 `SSL_set1_host`（4.0 起弃用）与 `test_break_http.c` 里
`X509_get_subject_name` 返回 const 都在 `-Werror` 下编译失败，导致 Metal 和 MoltenVK 两套
全量构建都过不了。改为 `OPENSSL_VERSION_MAJOR >= 4` 时用 `SSL_set1_dnsname`、3.x 保持
`SSL_set1_host`，测试证书生成改用 `X509_NAME_new()` + `X509_set_subject_name()`；修复前两处
报错已用 stash 复现。修复后 Metal CTest **245/245**、graphics **6/6**（含 5 个 fuzz 目标
构建），MoltenVK **246/246**，仅 D3D12 dependency gate 按平台跳过。`engine_demo` 文档机位
两后端截图目视确认：地形/角色/UI 正常。`BREAK_EDITOR_INPUT_SCRIPT=ON` 编辑器（Metal）：添加
两个实体、`Ctrl+Z`/`Ctrl+Y` 在新命令栈下 expect 全过，Render 标签正常。OpenSSL 3.x 路径
（`SSL_set1_host`）本机没有 3.x，未编译验证；`break_http` 的 TLS 端到端测试在本机通过，
崩溃上传、更新服务器等没有 macOS 实机场景。证据等级不变。

2026-11-21 复核：从 `@63d7e33b` 快进到 `@2891bc9b`（429 个远程提交：中性命名重构、
`core_app` 与 kernel/runtime、音频/网络/编辑器扩展、arm64 与 QUIC 弱网 CI 等），无冲突、
无本地改动。Metal 与 MoltenVK 全量构建无 error。**发现并修复 1 个测试误报**：
`test_repo_naming_contract` 对 `engine/CMakeLists.txt` 用了 `GLOB_RECURSE`，会匹配
`engine/build-*/` 里 `core_app_ctest_config_contract` 生成的源码拷贝（本机
`engine/build-macos-metal/` 下 15 处），在保留旧构建目录的开发机上必定失败；CI 的干净
checkout 碰不到。改为直接列出顶层 `engine/CMakeLists.txt`，修复前失败、修复后通过。修复后
Metal CTest **411/415**、graphics **6/6**，MoltenVK **414/418**；跳过项都是预期的：
D3D12 dependency gate（非 Windows）和 3 个 `core_app_nm_*` 契约（只在没有 `nm` 时生效）。
`engine_demo` 文档机位两后端截图目视确认地形/角色/UI 正常，平均 RGB 约 143/146/140，
Metal 与 MoltenVK 平均像素差 1.04；Metal 日志里的 `MegaBuffer: merged group indirect init
failed` 警告之前就有，不影响画面。编辑器实机脚本、iOS 模拟器、arm64 Linux 与 QUIC 弱网
场景本轮未在本机验证。证据等级不变。

2026-11-21 第二次复核：从 `@a531e22b` 快进到 `@f4c66dc5`（5 个远程提交：
`audio_extended.c` 的 PCM 流 `reading`/`open`/`hrtf_set` 存后读握手补
`atomic_thread_fence(memory_order_seq_cst)` 及对应源码契约，arm64 CI 加入平台输入与
RHI CPU 测试，OpenSSL 3.5 弱网 CI 演练记录），无冲突、无本地改动。审查了屏障改动：只在
store 与随后 load 之间加全屏障，`close` 在等待 `reading` 清零后才释放 ring，语义不变。
Metal CTest **411/415**、graphics **6/6**，MoltenVK **414/418**，跳过项同上一条；全量构建
无 error。`engine_demo` 文档机位两后端截图正常，平均像素差 1.56。本轮未发现需要修复的问题。
证据等级不变。

2026-11-21 第三次复核：从 `@8ca5c9a1` 快进到 `@e91bb19c`（2 个远程提交：
`test_editor_shell.c` 把 `camera_pose_whose_eye_collapses_onto_the_target_is_rejected` 移出
`BREAK_EDITOR_REMOTE_TESTS` 块，不带 snowflake 的构建也会运行它；arm64 CI 加入插件、编辑器
Lua 与 shell 测试），无冲突、无本地改动。确认该用例只定义和注册一次，在 Metal 与 MoltenVK
两套构建的 `test_editor_shell` 中都实际执行并通过（185/185）。Metal CTest **411/415**、
graphics **6/6**，MoltenVK **414/418**，跳过项同前；全量构建无 error。只改了测试与 CI，
渲染代码未变，本轮未重新截图。未发现需要修复的问题。证据等级不变。

2026-11-21 第四次复核：rebase 到 `@6392fa34`（远程 CLI 参数解析用例移出 Snowflake 门控，
非 Snowflake 构建的 `test_editor_shell` 增至 186 例，本机两套构建都执行通过）。本轮审查
发现并修复 2 个问题：
- **编辑器字体链重复**：在 `engine/` 下运行编辑器（这是文档要求的运行方式）时，
  `$BREAK_ASSET_DIR/assets/fonts/...` 与 cwd 相对的 `./assets/fonts/...` 是同一个文件，
  但只按路径字符串去重，两份都进链，6 个槽位里重复项占了 2 个，内置 Noto Sans SC 被挤到
  第 3 位、系统字体被挤出。`test_editor_fonts` 的 `fonts_bundled_jetbrains_mono_leads_the_chain`
  在 `engine/` 下运行必定失败，只是 CTest 的工作目录是构建目录，所以一直没暴露。
  `editor_fonts.c` 的 `chain_add` 增加按文件身份去重（POSIX 比较 `st_dev`/`st_ino`，Windows
  比较 `GetFullPathNameA` 结果）；新增 `fonts_same_file_through_two_paths_is_listed_once`，
  它自己切换到 `engine/`，修复前失败、修复后通过。用例数变为 Linux 8、macOS 6、Windows 7；
  上文 arm64 切片里的 `test_editor_fonts` 7 例是当时的计数。
- **测试在 `/tmp` 留残留**：`component_bytes_survive_save_load` 不删 `.bscn` 和
  `.editor.json`，标题测试不删 `.editor.json`，字体测试只删文件、不删 `touch()` 建的目录，
  空根目录用例完全不清理。每跑一次全量 CTest 就多 5 个条目，本机已积累约 140 个。修复后这几个
  测试运行前后 `/tmp` 条目数不变。其余 `break_core_app_assets_*`、`break_rtio`、
  `break_test_vfs_*` 等残留来自别的测试，本轮没有处理。

修复后 Metal CTest **411/415**、graphics **6/6**，MoltenVK **414/418**，跳过项同前；全量
构建无 error。证据等级不变。

2026-11-21 第五次复核：快进同步 `be816983..bdf28587`（7 个远程提交：arm64 可移植合同、
core_app 生命周期与 voice lane 驱动走交叉模拟器、记录 LD_PRELOAD 故障注入在 qemu-aarch64
下失败），无冲突。处理上一轮遗留的 `/tmp` 残留：把 415 条 CTest 逐条单独运行，对比每条运行
前后的 `ls -A /tmp`，定位到 7 个测试会留下按 pid 命名的文件或目录，均已在测试结束时清理：
- `test_break_update_client`：`no_tmp_residue` 复用同一个 root 建第二个目录前没有删第一个
  （`break_upc_notmp_<pid>`）。
- `test_runtime_io`：`break_rtio_<pid>` 从不删除；`io_request_double_release_aborts` 里故意
  abort 的子进程也留下一份，现在由父进程在 `waitpid` 后按子进程 pid 删除。
- `test_runtime_reload`：`break_rtreload_<pid>` 及其中 7 个 fixture 文件从不删除。
- `test_script_lua`：两个热重载用例不删 `test_break_reload.lua` / `test_break_noreload.lua`。
- `test_vfs`：`vfs_mount_priority` 的 a/b 两个目录、共享的 `test_vfs_dir`（含 `hello.txt`）
  与 `test_vfs.pak` 不删；R476 截断用例只删了 `aaaa…` 深层目录，没删其下 `make_truncation_prefix`
  建的 `bbbb…` 目录，导致整棵树都删不掉。
- `test_myui_echart_adapter`：写出的 `phase5_echart_adapter.ppm` 没有任何脚本或 CI 读取，
  写完即删（仍然验证写入过程）。
- `test_core_app_assets`：两份烘焙输出 `core_app_assets_a/b`（各 12 个文件）不删，
  `test_core_app_baker_diagnostics` 启动的同源诊断变体也因此留残留；现在 main 结束前清空并删除。

修复后这 7 个测试和 `test_core_app_baker_diagnostics` 单独运行前后 `/tmp` 条目没有新增；两套
全量 CTest 跑完后 `/tmp` 下 `break_*` 条目数保持 733 不变（这些是历史残留，未自动删除）。
扫描中出现的 `/tmp/r1434`、`/tmp/r1434-matrix.log` 单独重跑不复现、仓库里也没有这个名字，
判断来自本仓库之外的进程，未处理。Metal CTest **411/415**、graphics **6/6**，MoltenVK
**414/418**，跳过项同前；全量构建无 error。证据等级不变。

2026-11-21 第六次复核：快进同步 `7390174e..13b99255`（8 个远程提交），无冲突。涉及本平台的
是物理跨架构逐位一致：`fast_rsqrt` 去掉 SSE `rsqrtss` 路径，所有架构都用 `1.0f / sqrtf`；
`src/physics`、`src/math` 与 `tests/test_math.c` 以源文件属性加 `-ffp-contract=off`；约束角度
改用确定性 `math_atan2f`。本机 Apple Clang 21 的 `compile_commands.json` 确认，`physics.c`、
`ragdoll.c` 在引擎库和每个直接编译它们的测试目标里都带该选项。本机（arm64 macOS）上
`test_physics_replay` 的 3 组跨架构金标准哈希（静止、旋转、带限位铰链）与 `test_math` 中
`math_atan2f` 的固定位模式全部通过，说明 AppleClang 关闭 FMA 收缩后与 Linux x86-64/arm64
结果一致。Metal CTest **411/415**、graphics **6/6**，MoltenVK **414/418**，跳过项同前；全量
构建无 error，`/tmp` 下 `break_*` 条目数前后都是 733。未发现需要修复的问题。证据等级不变。

2026-11-22 第七次复核：同步 `52f2266f..c37d8962`（67 个远程提交），第二次同步时把本地修复
rebase 到 `origin/master`，只出现 `runtime_io.h` 注释冲突；合并时保留远程“通知先于唤醒、
在 facade 锁内发布”的语义和本地 attach 生命周期说明，没有改写或覆盖远程提交。审查并修复：
`runtime_bus_printf` 的 256 字节临时缓冲会截断拓扑 JSON，现直接写入调用方缓冲并记录完整长度；
任务完成计数改为独立引用计数块，消除拥有者收到通知后销毁队列导致的 worker use-after-free；
`break_runtime_io_attach_bus` 等待旧总线上正在发送的通知结束，返回后即可安全销毁旧总线；
`TaskFrameQueue` 加互斥锁，允许多个 worker 上的续体并发 `task_frame_defer`；空 cell view 报告
释放 cell 槽位；Hilbert 曲线边长将溢出时返回 0，不再死循环；快照尺寸用 64 位累加，超过
`UINT32_MAX` 时尺寸查询返回 0、快照写入失败。另修复规则引擎两个 Watch 永不触发的无效反例，
并同步过时注释。回归用例覆盖上述行为；修复前总线导出用例失败，cell view 用例 2 处失败，
宽网格用例在 5 秒 alarm 下未结束；旧任务队列在 ASan 下复现 heap-use-after-free，旧跨帧队列在
TSan 下报告数据竞争。当前修复的 ASan facade 21/21、TSan task_frame 5/5 通过且无告警。
rebase 后两套全量构建无 error，Metal CTest **431/431**、MoltenVK **434/434**、graphics **6/6**；
仅原有的 D3D12 依赖闸门和 3 个 `core_app_nm_*` 共 4 项按平台条件跳过。`/private/tmp` 非
`kc_*` 条目在测试前后完全相同。外部进程创建的 `/tmp/emfile*` 不属于本仓库，未删除。
仍未处理：cell_link 测试释放端口后重绑的偶发风险（需要新 API）、Windows `WSAEMSGSIZE`
处理、`timespec_get` 失败时 sequence 回落、物理示例主程序未进入并行路径；这些不改变本次
macOS 回归结论。

2026-11-22 第八次复核：快进同步 `728f700f..461200d5`（7 个远程提交），随后 rebase 到纯文档
提交 `35cbc5f7`，无冲突。编辑器窗口通知审查发现两处问题：重挂后只有部分字段变化时会混入
上一次挂接的旧状态；每次文本变化都强制刷新，绕过渲染面板 250 ms 节流。现在每次挂接独立
记录字段可见性，未收到的尺寸、缩放或 WSI 显示 `?`；只有新增或移除窗口行才立即刷新。
扩展 `render_panel_shows_main_loop_window_notices`：未修代码先在 1 ms 节流断言失败；单独修复
节流后在重挂 close-only 断言失败，两次均为 187 passed、1 failed、188 total，完整修复后 188/188。
异步资源失败日志与槽位生命周期、Windows NM/生成器契约隔离变更未发现新的确定缺陷。修复后
两套全量构建无 error，Metal CTest **431/431**、MoltenVK **434/434**、graphics **6/6**，
跳过项同前；rebase 后又完成两套构建与源码/文档契约检查。测试期间出现 root:wheel 所有的
`/private/tmp/powerlog` 目录，仓库无此路径引用，判断为系统条目，未删除；没有新增本仓库测试残留。

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

`ENGINE_RHI_BACKEND=auto` 在 Linux/Windows 默认 Vulkan（依赖缺失时带警告降级到 OpenGL；Apple 不变）。当前 selector 控制已有 OpenGL/Vulkan/D3D12（仅 Windows）
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

镜像编排采用 `ci.yml` 的 `image` job 调用同 commit 的 `ci-image.yml`，并在 `on.workflow_call.outputs.digest.value` 显式映射 `${{ jobs.prepare.outputs.digest }}`。本地候选 `load` 后先 smoke；随后直接给同一 image ID 打 `verified-<inputs-hash>` 标签并 `docker push`，不再第二次 build。master alias helper 按该 digest pull 同一候选，重新打 verified、commit SHA 与 `latest` 标签，逐一核对本地 image ID 后分别直接 push，并回读三者 digest 必须一致；不再用 `imagetools create` 生成新 index，也不接受不同 manifest 冒充同一 digest。push 进度保持 stderr，helper 的 digest stdout 不被污染。无输入变化复用已验证 digest，schedule 强制重建以获取安全更新。11 个实际 container jobs（含 2026-11-15 新增的 `lane-libfuzzer-linux-clang`）均 `needs: image` 并使用 `needs.image.outputs.digest`，不直接消费 `latest`。镜像额外安装 `libclang-rt-18-dev`（libFuzzer 运行时），候选 smoke 会用 `clang-18 -fsanitize=fuzzer,address` 链接并运行一个空 fuzzer。

PR/fork 不 login、不 push，只 smoke 本地候选，普通 lanes 不把该候选冒充为全 lane 已验证镜像。candidate 始终使用当前 `github.repository_owner`，非发布消费者的 fallback 则固定为上游 `ghcr.io/konyka/break-ci-linux`；upstream PR、fork PR、fork-owned push/manual 都不会解析不存在的 fork `latest`。可选仓库变量 `BREAK_CI_LINUX_DIGEST` 提供显式 `image@sha256:...` override；未设置时在 prepare 阶段匿名 inspect 上游公共 GHCR `latest`，将其解析为 immutable digest 后消费。公共拉取/解析失败会明确失败；lanes 不直接消费 `latest`，也不会因 override 未配置而阻断首次 PR 或 fork-owned CI。

`lane-benchmark-steam-deck-vk` 还要求维护者配置 `STEAM_DECK_VENDOR_ID` 与 `STEAM_DECK_DEVICE_ID`（十进制或 `0x` 十六进制）。原始收据含 Vulkan 实际 `device_type/vendor_id/device_id`；仅 `INTEGRATED`/`DISCRETE` 且 ID 精确匹配才可授予 `BENCHMARK_COMPARABLE`。缺配置、UNKNOWN/OTHER/VIRTUAL/CPU、ID 不匹配均为 UNAVAILABLE 且最终 lane 失败，原始 JSON 与 `hardware.env` 仍上传。hosted lavapipe/llvmpipe 可保留 CPU 类型的普通 `GPU_RUNTIME`，但不进入真机可比证据。

| lane（.github/workflows/ci.yml） | runner | 后端 / 配置 | 收据 artifact |
|---|---|---|---|
| lane-headless-linux-clang | ubuntu-24.04 | 默认 GL，Clang/LLD Release + IPO | evidence-receipt-headless-linux-clang |
| lane-headless-linux-gcc-asan | ubuntu-24.04 | 默认 GL，GCC Debug + ASan/UBSan（+fuzz smoke） | evidence-receipt-headless-linux-gcc-asan |
| lane-headless-linux-gcc-tsan | ubuntu-24.04 | 默认 GL，GCC Debug + TSan | evidence-receipt-headless-linux-gcc-tsan |
| lane-headless-windows-clang | windows-latest | Vulkan（+GL 默认），Clang Debug（含 win32 runtime trio 步） | evidence-receipt-headless-windows-clang |
| lane-headless-windows-asan | windows-latest | 默认 GL，Clang Debug + ASan | evidence-receipt-headless-windows-asan |
| lane-headless-windows-msvc | windows-latest | 默认 GL，MSVC（`cl`，`/W4 /WX`）Debug，`-LE graphics`（+fuzz smoke） | evidence-receipt-headless-windows-msvc |
| lane-headless-windows-mingw | windows-latest | 默认 GL，MinGW-w64 GCC Debug，`-LE graphics`（+fuzz smoke） | evidence-receipt-headless-windows-mingw |
| lane-native-surface-wayland | ubuntu-24.04 | Wayland + Vulkan，Debug（weston headless） | evidence-receipt-native-surface-wayland |
| wayland-gl（OpenGL 长期保留，对比基准） | ubuntu-24.04 | Wayland + GL，Debug | evidence-receipt-native-surface-wayland-gl |
| lane-native-surface-win32 | windows-latest | Win32 原生 surface trio，Clang Debug | evidence-receipt-native-surface-win32 |
| lane-native-surface-cocoa | macos-15 (arm64) | Cocoa + MoltenVK，Debug | evidence-receipt-native-surface-cocoa |
| lane-gpu-runtime-linux-gl（OpenGL 长期保留，对比基准） | ubuntu-24.04 | Wayland + GL，Debug，Weston + Mesa 软渲染 | evidence-receipt-gpu-runtime-linux-gl |
| lane-gpu-runtime-linux-vk | ubuntu-24.04 | Wayland + Vulkan，clang-18 Debug，Weston + lavapipe（软渲染，收据如实标注） | evidence-receipt-gpu-runtime-linux |
| lane-gpu-runtime-macos-metal | macos-15 (arm64) | Metal，Debug（hosted 无 Metal 会话时收据如实降级 HEADLESS） | evidence-receipt-gpu-runtime-macos-metal |
| lane-gpu-runtime-windows-d3d12（+ 常开 unavailable 孪生 job） | self-hosted windows gpu（`ENABLE_GPU_LANES` 门控） | D3D12，Release（hosted WARP floor 在 windows-d3d12.yml） | evidence-receipt-gpu-runtime-windows-d3d12 |
| lane-validation-linux-vk | ubuntu-24.04 | Wayland + Vulkan，Debug，Weston + VK_LAYER_KHRONOS_validation（VUID 即红） | evidence-receipt-validation-linux |
| lane-benchmark-linux-vk | ubuntu-24.04 | Wayland + Vulkan，Release，Weston 下 `rhi_swapchain_bench` 600 帧 lavapipe（GPU_RUNTIME 收据注明软渲染） | evidence-receipt-benchmark-linux-vk |
| lane-benchmark-steam-deck-vk | self-hosted linux gpu-vulkan（`ENABLE_GPU_LANES` 门控） | Wayland + Vulkan，RelWithDebInfo，真 GPU BENCHMARK_COMPARABLE 收据 | evidence-receipt-benchmark-steam-deck |
| lane-proton（schedule 周一 03:23 UTC + 手动） | ubuntu-24.04 | steamrt sniper 钉 digest 容器内构建 + ctest（缺 Wayland 工具链则 UNAVAILABLE；兼容参考） | evidence-receipt-proton |
| clean-room（Task 2 交付，非 lane 命名） | ubuntu-24.04 | 钉版工具链 + git archive 干净导出 + Vulkan | — |
| ios-metal-build（compile only） | macos-15 (arm64) | iOS Simulator build-only + metallib、scene manifest 与资源入包断言 | — |

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

- **历史故障记录（非当前运行路径）**：在 Wayland 会话下 GL demo 走 XWayland，`glXSwapBuffers` 会被 Present 节流到 ~1 FPS（profiler 显示 `Frame: 1000 ms`，而引擎 dt 按 R147 钳制 0.1s）。脚本化截图/相机复现前请用 `vblank_mode=0 ./build_gl/engine_demo` 绕过节流，否则一秒的鼠标输入会在单帧内一次性生效。2.0.0 不再使用该窗口路径，本段仅保留旧故障事实。
- 窗口模式：`G` 或 Alt+Enter 在窗口与**无标题栏全屏**（铺满窗口所在显示器、不改显示器分辨率、不独占，Alt-Tab 不黑屏）之间切换，离开全屏恢复原位置、尺寸与最大化状态；`BREAK_FULLSCREEN=1` 以全屏启动；`BREAK_TOGGLE_FULLSCREEN_AT=f1,f2,...` 在指定帧自动切换，每次切换输出 `WINDOW_MODE_SWITCH`（重建耗时、之后 5 帧最长帧时间），退出时输出 `WINDOW_MODE_STATS`。`BREAK_RESIZE_AT=frame:WxH,...` 不改窗口、只按给定尺寸走同一重建路径，输出 `RESIZE_REBUILD`。API：`platform_set_window_mode` / `platform_get_window_mode`、`PlatformConfig.start_fullscreen`（`platform/platform.h`）。标题栏：Alt+T 切换窗口模式下的标题栏和边框（客户区位置和大小不变，全屏期间的改动在回到窗口时生效）；`BREAK_UNDECORATED=1` 以无标题栏窗口启动；`BREAK_TOGGLE_TITLE_BAR_AT=f1,f2,...` 自动切换并输出 `TITLE_BAR_SWITCH`。API：`platform_set_window_decorated` / `platform_get_window_decorated` / `platform_window_title_bar_visible`、`PlatformConfig.undecorated`。Win32 改窗口样式（无标题栏时最大化只铺满工作区）；Wayland 关掉 myui 的客户端装饰；Cocoa 去掉 `NSWindowStyleMaskTitled`；QNX Screen 与移动端固定无标题栏。Win32、Cocoa 同步切换；Wayland 以 compositor 回报为准；QNX Screen 与移动端固定全屏。
- 脚本化钩子（均无默认值，不设即原行为）：`BREAK_FRAMES=N`（N 帧后退出）、`BREAK_SCREENSHOT=a,b,c`（R446 起支持逗号列表，逐帧截图到 screenshot_N.bmp）、`BREAK_CAM=x,y,z[,yaw,pitch]`（初始机位；不设时默认 (0,2,8) 会抬到地形上方 2 m）、`BREAK_CAM_SPIN=deg`（R446，每帧 yaw 增量，复现相机运动伪影）、`BREAK_TAA=0` / `BREAK_MB=0`（R446，TAA/动态模糊开关，用于 A/B 对照）、`BREAK_SSR=1` / `BREAK_SSGI=1` / `BREAK_CS=1` / `BREAK_VOL=1` / `BREAK_LF=1`（R550-A，开启默认关闭的 SSR/SSGI/接触阴影/体积雾/镜头光晕——五路 pass 自 R550-A 起真实合成进帧链）、`BREAK_IBL_STATIC=1`（R559，禁用运行时 IBL rebake）、`BREAK_IBL_REBAKE_FRAMES=N`（R559，每 N 帧触发一次、用于无头验证；rebake 仍跨 42 帧完成）、`BREAK_JITTER=0`（关闭 Halton 抖动，便于隔离时间重投影伪影）、`BREAK_MODEL_VIEW=s`（模型查看：不画地形/水面/展示区，相机对准命令行加载的模型，s 为距离倍数，s<1 更近）、`BREAK_BSCN_ROUNDTRIP_AT=f`（第 f 帧按 `B` 键路径保存 BSCN，第 f+10 帧按 `N` 键路径读回，用于无头验证读档后 LOD 等状态重建；会在工作目录写 `scene_save.bscn` / `scene_state.bin`）。TSR 在初始化或分辨率重建后的第一帧只输出当前帧，不采样历史；随后才恢复历史重投影。

### 3.2 macOS 窗口模式与标题栏验证

交互演示：`G` 或 Alt+Enter 在窗口与无标题栏全屏之间切换，Alt+T 切换窗口模式的标题栏。`BREAK_FULLSCREEN=1` 直接全屏启动，`BREAK_UNDECORATED=1` 直接以无标题栏窗口启动。

在 `engine/` 下执行以下命令，可单独运行公共状态机与真实 Cocoa 窗口测试，并自动演示全屏进出和标题栏显隐（Metal 构建目录示例为 `build-macos-current`）：

```sh
ctest --test-dir build-macos-current \
  -R '^(test_platform_cocoa_runtime|test_platform_window_mode)$' -V

BREAK_UNDECORATED=1 \
BREAK_TOGGLE_FULLSCREEN_AT=10,40 \
BREAK_TOGGLE_TITLE_BAR_AT=50,60 \
BREAK_SCREENSHOT=25 \
./build-macos-current/engine_demo --frames 70
```

Cocoa 测试直接断言 `NSWindow` 的全屏样式、屏幕矩形、窗口层级，以及标题栏显隐前后的内容矩形。demo 在第 10、40 帧进出全屏，第 50、60 帧显示再隐藏标题栏，第 25 帧保存全屏内容；对应日志为 `WINDOW_MODE_SWITCH`、`TITLE_BAR_SWITCH` 和退出时的 `WINDOW_MODE_STATS`。MoltenVK 演示将可执行文件替换为 `build-macos/engine_demo`。这些入口已集成在现有测试与 `engine_demo` 中，不需要单独的窗口模式 demo 程序。

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
cmake -B build-verify-wl-gl -DENGINE_RHI_BACKEND=opengl
cmake --build build-verify-wl-gl
ctest --test-dir build-verify-wl-gl -LE graphics --output-on-failure

# Vulkan 后端集成测试（Linux/Windows 默认后端）
cmake -B build-verify-wl-vk
cmake --build build-verify-wl-vk
ctest --test-dir build-verify-wl-vk -L graphics --output-on-failure
```

Linux 图形测试会创建真实 Wayland 窗口，必须在原生 Wayland 会话或已启动的 Weston 下运行；GL 与 Vulkan 顺序执行，避免共享 compositor/GPU 资源竞争。完成构建后，
推荐按以下完整矩阵验证 forward MRT、真实 IBL、RT1 temporal consumers（TAA/combined AA/
motion blur；GL/Vulkan graphics gate 都使用真实 `RG16F` 输入并检查 blur 输出变化）和运行时错误门禁：

```bash
# 无头单元/集成测试
ctest --test-dir build-verify-wl-gl -LE graphics --output-on-failure
ctest --test-dir build-verify-wl-vk -LE graphics --output-on-failure

# 图形测试：严格顺序，不并行
ctest --test-dir build-verify-wl-gl -L graphics --output-on-failure
ctest --test-dir build-verify-wl-vk -L graphics --output-on-failure

# 运行时 smoke：GL 检查 Mesa API 错误；VK 检查 validation 层
MESA_DEBUG=1 BREAK_FRAMES=120 BREAK_UI=0 ./build-verify-wl-gl/engine_demo
BREAK_FRAMES=120 BREAK_UI=0 ./build-verify-wl-vk/engine_demo
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
| headless | lane-headless-linux-clang / -gcc-asan / -gcc-tsan / -windows-clang / -windows-asan / -windows-msvc / -windows-mingw |
| native-surface | lane-native-surface-wayland / -win32 / -cocoa（+ wayland-gl，OpenGL 对比基准） |
| GPU-runtime | lane-gpu-runtime-linux-gl（OpenGL 对比基准）/ -linux-vk / -macos-metal / -windows-d3d12（+ 常开 unavailable 孪生 job） |
| validation | lane-validation-linux-vk（VK_LAYER_KHRONOS_validation，VUID 即红） |
| benchmark | lane-benchmark-linux-vk（lavapipe，GPU_RUNTIME 收据）/ lane-benchmark-steam-deck-vk（真机 BENCHMARK_COMPARABLE，`ENABLE_GPU_LANES` 门控） |
| proton | lane-proton（steamrt sniper 钉 digest 容器内构建 + ctest；兼容参考，不计 Windows 原生证据；仅 schedule/手动触发） |
| 非 lane 命名保留 | clean-room（Task 2 交付）、ios-metal-build（compile only） |

收据纪律：失败 lane 的收据如实降级 UNAVAILABLE（`job.status` 与实际 `rc/passed/skipped` 守卫）；Linux 必须实际执行且零 skip 才能授予 GPU_RUNTIME，全 skip 或零执行不会得到通过收据。hosted macOS 无 Metal
会话时 graphics 整体 SKIP → HEADLESS；lavapipe/llvmpipe 软渲染收据在 gpu 字段与 command 字段
如实标注，不计入硬件 GPU 证据。历史全绿 run（17 success / 3 设计内 skipped，15 个
evidence-receipt artifact）：https://github.com/konyka/break/actions/runs/38990768014 （@3c92a06b，
2026-10-17），不代表 2.0.0 新 workflow 已执行。

`lane-gpu-runtime-linux-vk` 启动 Weston，并选择 Mesa 的软件 Vulkan ICD（lavapipe）及 llvmpipe；
若 runner 缺少 Weston、Wayland/scanner 或 lavapipe ICD，步骤直接失败，不把未执行宣称为通过。软件渲染与参考 GPU 的
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
    EngineConfig cfg = { .width = 1280, .height = 720, .title = "My Application" };
    if (!engine_init(&engine, &cfg)) return 1;
    while (engine_frame(&engine)) {
        // 应用逻辑
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

# iOS Simulator（构建与本机运行；CI 仍为 compile-only）
export DEVELOPER_DIR=/Applications/Xcode.app/Contents/Developer
cmake -S engine -B build-ios -G Xcode \
    -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphonesimulator \
    -DENGINE_RHI_BACKEND=metal -DENGINE_BUILD_TESTS=OFF
xcodebuild -project build-ios/PureCEngine.xcodeproj -scheme engine_demo \
    -destination 'generic/platform=iOS Simulator' build

# UDID 用 xcrun simctl list devices available 查询；已 Booted 时跳过 boot。
UDID=替换为模拟器UDID
xcrun simctl boot "$UDID"
xcrun simctl bootstatus "$UDID" -b
xcrun simctl install "$UDID" build-ios/Debug-iphonesimulator/engine_demo.app
SIMCTL_CHILD_BREAK_SCREENSHOT=60 xcrun simctl launch --console-pty \
    "$UDID" com.purecengine.engine-demo --frames 300

# 持续运行期间可直接截取屏幕合成结果：
xcrun simctl io "$UDID" screenshot /tmp/engine-ios-screen.png

# 也可读取第 60 帧在 present 前的 RHI 截图：
DATA_DIR=$(xcrun simctl get_app_container "$UDID" com.purecengine.engine-demo data)
sips -s format png \
    "$DATA_DIR/Library/Caches/PureCEngine/screenshot_0.bmp" \
    --out /tmp/engine-ios-frame60.png
```

说明：
- 离线 shader 管线（GLSL→SPIR-V→MSL→metallib + FNV manifest）在构建期运行，
  产物 `metal_shaders/engine.metallib` 拷到各 consumer 旁；`xcode-select` 指向
  CommandLineTools 时 `DEVELOPER_DIR` 由 CMake 自动烘焙为标准 Xcode 路径。
- iOS 交叉编译时 manifest 生成器自动切换为宿主编译（`gen_metal_shader_manifest_host`，
  见 `engine/CMakeLists.txt` M6 注释）。宿主工具通过 `xcrun --sdk macosx --show-sdk-path`
  和主机目标三元组显式编译，并清理 Xcode 传入的 SDKROOT、编译/链接环境；在 Xcode
  自动重配置时也不会误产 Simulator 可执行文件。`xcrun metal` 的 SDK 与
  `CMAKE_OSX_SYSROOT` 一致：设备为 `iphoneos`，Simulator 为 `iphonesimulator`。Xcode 的
  `-destination` 不会改写这个自定义 shader 命令的 SDK；Simulator 必须显式配置对应
  sysroot，不能复用设备版 metallib。设备与 Simulator 建议使用不同构建目录。
- `engine_demo` 的 iOS target 使用 `com.purecengine.engine-demo`。CI 对 bundle ID、
  scene delegate、`engine.metallib` 以及 assets/shaders 入包结果做硬断言，但 lane 仍为
  build-only，不提供 GPU_RUNTIME 收据。按上面的 `engine_demo` scheme 构建；直接
  `cmake --build build-ios` 会拉起 `ALL_BUILD` 中的 macOS 专用 Cocoa/OpenGL
  `myui_explorer`，该桌面工具的全目标构建不是受支持的 iOS 验收入口。
- `engine/src/apps/ios_main.m` 通过 `UIApplicationMain` + `UIWindowScene` 创建
  `UIWindow`、Metal view 和 `CAMetalLayer`。UIKit 留在主线程，现有 demo 在 16 MiB
  栈的专用引擎线程执行 `engine_demo_main`；`EngineConfig` 注入原生句柄、scale 和
  宿主 poll。主线程同步 viewport、主触摸位置/主按钮 down/up 与 scene 生命周期，
  引擎线程串行应用；后台等待条件变量而不获取 drawable，每帧有独立 Objective-C
  autoreleasepool。
- assets/shaders 保持目录结构入包，启动时暂存到 app 自己的
  `Library/Caches/PureCEngine` 并作为工作目录，截图、缓存和 trace 不写入只读 bundle。
  工作目录会在再次启动时重建，不能当作持久用户存储。
- iOS texel buffer 使用 private storage，初始数据与后续更新经 shared staging blit；
  macOS 默认路径不变。Simulator 音频使用 miniaudio Null 后端（静音，不枚举输出设备），
  避免无输出设备环境下 Core Audio 初始化超时；真机仍使用原默认后端，尚未实测。
- 2026-10-27 本机 Xcode 27.1 / iPhone 18 Pro Simulator（iOS 27.0）实测：
  124 个离线 shader 条目入包，`--frames 300` 完成并正常 shutdown；第 60 帧 RHI 截图
  及运行中的 `simctl io screenshot` 均可见 3D 场景与 UI，方向正确，日志无 ERROR/FATAL。
  同一进程切到 Safari 再返回时记录到 `iOS host: suspended` / `resumed`，恢复后继续出帧。
  初始 viewport 为 logical 402x874、drawable 1206x2622、scale 3.0。
- 同日以本机 XCTest UI Automation harness 驱动 `XCUIDevice` 旋转和 `XCUICoordinate`
  点击，测试 1/1 通过：窗口从 402x874 变为 874x402，点击后恢复 402x874。横屏点击
  (437, 201) 后，系统日志确认引擎线程消费 `iOS input: down` / `up`，坐标一致。
  横屏稳定期的 `simctl io screenshot` 为 2622x1206，3D/UI 铺满且 HUD 正立，
  HUD 显示 `Render: 1311x603 -> 2622x1206`。本机 XCTest 的横屏截图附件存在按物理像素
  方向保存和应用裁切黑区的呈现差异，不能据此判定渲染失败；朝向以实际 `simctl`
  屏幕截图交叉核对。临时 harness 未注册为仓库或 CI 测试 target，CI 仍 compile-only。
- 当前验证边界：Hi-Z、indirect draw/GPU cull 与 GPU timer 仍有能力降级，不宣称可选路径
  全齐；现有桌面 HUD 未做窄屏排版适配。真机旋转、物理触摸、音频/Metal 仍待验证。
  Simulator 结果只登记为本地可见运行证据，iOS 等级保持 COMPILED，不改变 OpenGL
  删除 gate，也不宣称真机 GPU_RUNTIME。
- `METAL_DEVICE_WRAPPER_TYPE=1 ./engine_demo --frames 3` 开 Metal validation
  取证（encoder-state 类缺陷的唯一可靠观测，计划 C Task 11 方法学）。

### 1.5 Linux arm64 交叉构建与 QEMU 服务/安全/网络/运行时/ECS/Lua/资产/RHI/诊断/PAL/Job/物理/动画/AI/音频/规则引擎/kernel/flow/world/editor-core/audio/plugin-core/compose-core/system/shader-io/ui-render-cpu/cpp20/platform-input/rhi-cpu/editor-core-app-cpu/plugin-lua-shell/portable-contract/core-app-lifecycle/voice-lane/packer/editor-manifest-cli 测试

`engine/toolchain-aarch64-linux.cmake` 用 `aarch64-linux-gnu-` 工具链交叉编译到 Linux arm64，让 `__aarch64__` 分支得到类型检查与链接验证。CI 的 `lane-cross-aarch64-linux` 安装 Ubuntu `qemu-user`，配置 `CMAKE_CROSSCOMPILING_EMULATOR`，通过一次 CTest 选择执行崩溃、HTTP、在线更新、密码学、完整性、权威、核心网络、运行时、ECS、Lua、资产/VFS、RenderGraph/RHI、诊断、PAL、Job System、物理、动画、AI、音频、规则引擎、kernel/flow、无头 world、编辑器核心、音频核心、插件核心、Compose 核心、CVar/XML 系统扩展、着色器 I/O、编辑器 flow/image、Compose 与 myui 集成、渲染 CPU 路径、扩展输入、C++20 对等层、fork 截止等待、平台输入/窗口、RHI CPU 路径、编辑器/core_app 纯 CPU 组件、插件动态加载、编辑器 Lua 与 shell 、跨平台可移植契约、core_app 真实进程生命周期、core_app 语音通道、资源包打包往返以及编辑器插件清单命令行共二百六十一项测试。其中九个编辑器核心测试、`test_editor_audio`、五个插件核心测试、五个 Compose 核心测试、系统扩展/着色器 I/O 五项、UI/渲染 CPU 七项、C++20 对等层五项、原型/fork 截止等待两项、平台输入/窗口六项、RHI CPU 路径五项、编辑器/core_app 纯 CPU 组件六项、插件/Lua/shell 四项、跨平台可移植契约六项、core_app 生命周期十二项、语音通道一项、资源包打包往返一项与编辑器插件清单命令行一项由 QEMU 运行，`test_break_editor_target_contract` 仅由宿主 CMake 检查源码结构；这不代表跑过全量 arm64 `ctest`，也不包含需要额外依赖门控的 Snowflake/QUIC 测试。

完整 `engine` 在 Linux 上仍需要 Wayland、xkbcommon、OpenGL/EGL 与默认启用的 OpenSSL；`ENGINE_RHI_BACKEND=headless` 不是 Linux 的合法选择，所以这里显式选择 `opengl`，图形路径只有编译/链接证据。Ubuntu 24.04 的参考依赖布局是 multiarch：主机包提供 `wayland-scanner` 和协议 XML，arm64 包提供目标头文件与库。完整的 ports 源配置和安装命令见 `.github/workflows/ci.yml` 的 **Install the host and arm64 build dependencies** 步骤。

依赖安装后，从仓库根目录执行：

```sh
# 仅适用于上述 Ubuntu multiarch 布局；其他发行版应填自己的真实 sysroot。
export AARCH64_SYSROOT=/
export PKG_CONFIG_LIBDIR=/usr/lib/aarch64-linux-gnu/pkgconfig:/usr/aarch64-linux-gnu/lib/pkgconfig:/usr/share/pkgconfig
cmake -S engine -B build-arm64 -G Ninja \
    --toolchain "$PWD/engine/toolchain-aarch64-linux.cmake" \
    -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=opengl \
    '-DCMAKE_CROSSCOMPILING_EMULATOR=/usr/bin/qemu-aarch64;-L;/'
cmake --build build-arm64 --parallel --target break_crash engine test_break_crash test_break_crash_symbolize test_break_crash_cluster test_break_crash_upload_http break_crash_server break_crash_report break_crash_e2e test_break_update test_break_update_client test_break_http break_manifest_tool break_manifest_verify break_update_server break_update_e2e test_break_crypto test_break_integrity test_break_authority break_keygen test_packet test_network test_break_online_lobby test_break_online_nat test_break_online_voice test_break_voice_mixer test_break_replay_window test_break_msg_rate test_break_online_aspect test_break_online_aspect_replication test_break_replication_fragment test_core_app_network core_app test_runtime_core test_runtime_facade test_runtime_io test_runtime_reload test_ecs test_ecs_system test_ecs_replication test_break_lua_runtime test_break_lua_module test_break_lua_value test_break_lua_binding test_break_lua_handle test_break_lua_table test_break_lua_debug test_break_kernel_lua test_break_lua_ecs_apply test_vfs test_async_loader test_filewatch_backend test_hotreload test_render_graph test_rhi_dispatch test_rhi_capabilities test_rhi_error_contract test_rhi_frame_lifecycle_contract test_profiler test_clock_offset test_trace_core_app test_trace_merge trace_merge test_platform_config test_platform_null_safety test_platform_fs_write test_platform_size_semantics test_task test_task_singleton test_physics test_physics_replay test_physics_sync test_physics_hinge test_physics_cone_twist test_physics_identity test_ragdoll test_vehicle test_physics_slider test_cloth test_rope test_soft_body test_destructible test_character test_animation test_anim_pose_authority test_anim_morph test_anim_facial test_anim_compression test_anim_locomotion test_skeleton_socket test_anim_aim test_break_nav_bake test_break_nav_query test_break_nav_query_concurrent test_break_nav_follow test_break_perception test_break_behavior test_break_steer test_break_ai_dynamic test_break_steer_velocity test_break_ai_agents test_break_ai_formation test_break_ai_smart_object test_voice_playback test_audio test_audio_extended test_audio_dsp test_audio_hrtf test_audio_capture test_audio_agc test_audio_noise_gate test_audio_echo_canceller test_audio_delay_estimator test_audio_fft test_audio_noise_suppressor test_audio_residual_echo_suppressor test_audio_delay_tracker test_audio_gcc_phat test_audio_drift_estimator test_audio_drift_resampler test_audio_drift_compensator test_audio_edit test_audio_voice_processor test_audio_voice_aligner test_audio_wav test_rule_engine test_rule_engine_transactions test_rule_engine_tms test_rule_engine_grl_semantics test_rule_engine_ir test_rule_engine_forall_limits test_rule_engine_rete_incremental test_rule_engine_agenda test_rule_engine_backward test_rule_engine_backward_ext test_rule_engine_grl_surface test_rule_engine_plugin_parity test_rule_engine_example_coverage test_rule_engine_query_blocks test_rule_engine_stream_ext test_rule_engine_stream_grl test_rule_engine_stream_eval test_rule_engine_backward_deep_chain test_backward_machine_structure test_backward_machine_context test_rule_engine_backward_bindings test_break_kernel_actor test_break_kernel_items test_break_kernel_weapons test_break_kernel_actions test_break_kernel_move test_break_kernel_level test_break_kernel_area test_break_kernel_flow test_break_flow_graph test_break_flow_serial test_break_flow_runtime test_vegetation test_time_of_day test_visarea test_world_stream test_decal test_voxel test_road test_mesh_stage test_mesh_buffer test_mesh_gpu test_world_mesh_fake test_world_presentation test_world_presenter_fake test_world_stream_job test_world_stream_world test_editor_doc test_editor_cmd test_editor_scene test_editor_components test_editor_viewport test_editor_gizmo test_editor_assets test_editor_i18n test_editor_scene_textures test_editor_audio test_editor_plugin_cmds test_editor_plugin_host test_editor_plugin_sections test_editor_plugin_panels test_editor_plugin_manifest test_mycompose_tree test_mycompose_remember test_mycompose_store test_mycompose_runtime test_mycompose_async test_break_cvar test_break_xml test_editor_flow test_editor_image test_shader_io test_mycompose_myui test_mycompose_widget_primitives test_render_features test_rt_trace test_rhi_tlas_instance_encode test_rhi_metal_format_mapping test_input_extended test_mycompose_cpp20_c_fixture test_mycompose_cpp20 test_mycompose_cpp20_header test_mycompose_cpp20_noexcept test_public_api_cpp20 test_core_style_prototype test_fork_deadline test_platform_screen_simulated test_platform_window_mode test_pad_linux_feedback test_pad_win_feedback_portable test_win32_touch test_wayland_touch test_rhi_rollout_log test_rhi_runtime_select test_rhi_fault_injection test_rhi_wsi_attach test_rhi_golden_parity test_editor_input_script test_editor_settings test_editor_fonts test_editor_audio_sink test_core_app_mesh test_core_app_runtime test_break_plugin test_editor_plugin_load test_editor_lua test_editor_shell test_glad_wgl_loader test_platform_wsi_lifecycle test_d3d12_lifetime_hresult_contract test_net_loop_qnx test_qnx_perf_smoke test_break_plugin_unsupported core_app_lifecycle_preload packer verify_pak editor
qemu-aarch64 --version
BREAK_TEST_NM=aarch64-linux-gnu-nm \
BREAK_TEST_READELF=aarch64-linux-gnu-readelf \
BREAK_TEST_STRIP=aarch64-linux-gnu-strip \
BREAK_TEST_RUNNER='qemu-aarch64 -L /' \
BREAK_TEST_QEMU_USER=1 \
timeout 600 ctest --test-dir build-arm64 --verbose --no-tests=error \
  -R '^(test_break_crash|test_break_update|test_break_http|test_break_manifest_tool|test_break_crypto|test_break_keygen|test_break_integrity|test_break_authority|test_packet|test_network|test_break_online_lobby|test_break_online_nat|test_break_online_voice|test_break_voice_mixer|test_break_replay_window|test_break_msg_rate|test_break_online_aspect|test_break_replication_fragment|test_core_app_network($|_offline)|test_runtime_core($|_target_contract)|test_runtime_(facade|io|reload)$|test_ecs(_system|_replication)?$|test_replication_target_contract$|test_break_lua_(runtime|module|value|binding|handle|table|debug|ecs_apply|target_contract)$|test_break_kernel_lua$|test_(vfs|async_loader|filewatch_backend|hotreload)$|test_render_graph$|test_rhi_(dispatch|capabilities|error_contract|frame_lifecycle_contract)$|test_(profiler|clock_offset|trace_core_app|trace_merge|trace_merge_tool)$|test_(platform_config|platform_null_safety|platform_fs_write|platform_size_semantics|task|task_singleton)$|test_(physics(_replay|_sync|_hinge|_cone_twist|_identity)?|ragdoll|vehicle)$|test_(physics_slider|cloth|rope|soft_body|destructible|character)$|test_(animation|anim_(pose_authority|morph|facial|compression|locomotion|aim)|skeleton_socket)$|test_break_(nav_(bake|query|query_concurrent|follow)|perception|behavior|steer(_velocity)?|ai_(dynamic|agents|formation|smart_object|target_contract|hot_path_contract))$|test_audio(_(extended|dsp|hrtf|capture|agc|noise_gate|echo_canceller|delay_estimator|fft|noise_suppressor|residual_echo_suppressor|delay_tracker|gcc_phat|drift_estimator|drift_resampler|drift_compensator|edit|voice_processor|voice_aligner|wav|realtime_contract))?$|test_voice_playback$|test_rule_engine(_(transactions|tms|grl_semantics|ir|forall_limits|rete_incremental|agenda|backward|backward_ext|grl_surface|plugin_parity|example_coverage|query_blocks|stream_ext|stream_grl|stream_eval|backward_deep_chain|backward_bindings))?$|test_backward_machine_(structure|context)$|test_break_kernel_(actor|items|weapons|actions|move|level|area|flow|target_contract)$|test_break_flow_(graph|serial|runtime)$|test_(vegetation|time_of_day|visarea|decal|voxel|road)$|test_world_(stream(_job|_world)?|mesh_fake|presentation|presenter_fake)$|test_mesh_(stage|buffer|gpu)$|test_editor_(doc|cmd|scene|components|viewport|gizmo|assets|i18n|scene_textures)$|test_break_editor_target_contract$|test_editor_audio$|test_editor_plugin_cmds$|test_editor_plugin_host$|test_editor_plugin_sections$|test_editor_plugin_panels$|test_editor_plugin_manifest$|test_mycompose_tree$|test_mycompose_remember$|test_mycompose_store$|test_mycompose_runtime$|test_mycompose_async$|test_break_cvar$|test_break_xml$|test_editor_flow$|test_editor_image$|test_shader_io$|test_mycompose_myui$|test_mycompose_widget_primitives$|test_render_features$|test_rt_trace$|test_rhi_tlas_instance_encode$|test_rhi_metal_format_mapping$|test_input_extended$|test_mycompose_cpp20_c_fixture$|test_mycompose_cpp20$|test_mycompose_cpp20_header$|test_mycompose_cpp20_noexcept$|test_public_api_cpp20$|test_core_style_prototype$|test_fork_deadline$|test_platform_screen_simulated$|test_platform_window_mode$|test_pad_linux_feedback$|test_pad_win_feedback_portable$|test_win32_touch$|test_wayland_touch$|test_rhi_rollout_log$|test_rhi_runtime_select$|test_rhi_fault_injection$|test_rhi_wsi_attach$|test_rhi_golden_parity$|test_editor_input_script$|test_editor_settings$|test_editor_fonts$|test_editor_audio_sink$|test_core_app_mesh$|test_core_app_runtime$|test_break_plugin$|test_editor_plugin_load$|test_editor_lua$|test_editor_shell$|test_glad_wgl_loader$|test_platform_wsi_lifecycle$|test_d3d12_lifetime_hresult_contract$|test_net_loop_qnx$|test_qnx_perf_smoke$|test_break_plugin_unsupported$|test_core_app_lifecycle_load_unload$|test_core_app_lifecycle_input_key$|test_core_app_lifecycle_input_touch$|test_core_app_lifecycle_input_cancel$|test_core_app_lifecycle_script_flow$|test_core_app_lifecycle_simulation$|test_core_app_lifecycle_locomotion$|test_core_app_lifecycle_facial$|test_core_app_lifecycle_vehicle$|test_core_app_lifecycle_ragdoll$|test_core_app_lifecycle_render_record$|test_core_app_lifecycle_roundtrip$|test_core_app_voice_lane$|test_packer_roundtrip$|test_editor_plugin_manifest_cli$)'
```

2026-11-20 动画切片前的选择为八十六项：既有八十项，加 slider、cloth、rope、soft-body、destructible 五项扩展物理测试和 character 30 例，至此所有以物理模块为主体的已注册测试均纳入 arm64。五个扩展模块各含一个场景（静态断言点 12/24/10/15/30，含循环，运行时检查次数更多；首个失败会提前返回），均由既有 emulator 直接启动；新增的 `test_(physics_slider|cloth|rope|soft_body|destructible|character)$` 是独立的局部锚定表达式，未改动已验证的刚体表达式。刚体八项为 83/4/13/3/8/5/10/9 例；`test_(physics(_replay|_sync|_hinge|_cone_twist|_identity)?|ragdoll|vehicle)$` 的 `$` 覆盖整个可选后缀组。replay/sync 只证明同一 arm64 构建在单进程内自洽，不代表跨构建、跨编译器或跨架构逐位回放与 lockstep（物理源码未使用 `-ffp-contract=off`）。其余既有选择不变。`--no-tests=error` 防止空选择通过，超时和失败不重试、不屏蔽。

AI 切片前的选择为九十四项：在上述八十六项之外加入八项动画测试 `test_animation`（37 例）、`test_anim_pose_authority`（2）、`test_anim_morph`（10）、`test_anim_facial`（8）、`test_anim_compression`（13）、`test_anim_locomotion`（1）、`test_skeleton_socket`（1）、`test_anim_aim`（1），均由既有 emulator 直接启动。新增独立 alternative `test_(animation|anim_(pose_authority|morph|facial|compression|locomotion|aim)|skeleton_socket)$`，`$` 绑定整个分组，外层 `^(` 排除 `test_myui_echart_animation`。仅链接动画源码的 asset/glTF、core_style 与 core_app lifecycle 测试不在本选择内。GPU 蒙皮、渲染与跨架构逐位动画回放不在覆盖内。

音频切片前的选择为一百零八项：在上述九十四项之外加入 `break_ai` 块注册的十四项：十二个只链接 `break_ai` 的可执行目标（nav bake 3、nav query 3、nav query concurrent 2、nav follow 1、perception 1、behavior 1、steer 1、ai dynamic 6、steer velocity 6、ai agents 2、ai formation 5、ai smart object 3 例），以及宿主 `cmake -P` 的 target 与 hot-path 契约。新增 alternative `test_break_(nav_(bake|query|query_concurrent|follow)|perception|behavior|steer(_velocity)?|ai_(dynamic|agents|formation|smart_object|target_contract|hot_path_contract))$`；同属 `break_ai` 标签的 `test_core_style_prototype` 不在选择内。真实关卡 navmesh、大规模群体性能与编辑器 AI 工具不在覆盖内。

规则引擎切片前的选择为一百三十一项：在上述一百零八项之外加入二十三项音频测试：`test_voice_playback`（4 例）、`test_audio`（47）、`test_audio_extended`（129）及二十个 DSP/管线可执行目标（dsp 10、hrtf 9、capture 13、agc 8、noise gate 8、echo canceller 9、delay estimator 21、fft 8、noise suppressor 8、residual echo suppressor 8、delay tracker 8、gcc-phat 8、drift estimator 8、drift resampler 12、drift compensator 8、edit 6、voice processor 3、voice aligner 6、wav 7），共 348 例，外加宿主 `cmake -P` 的 `test_audio_realtime_contract`。新增 alternative `test_audio(_(...))?$|test_voice_playback$`，`$` 绑定整个可选后缀组；同带 `audio` 标签的 core_app voice/voice lane 与 editor audio sink 不在选择内。真实音频设备、core_app 语音通道、编辑器音频与跨架构逐位一致的 DSP 输出不在覆盖内，QEMU 计时也不代表 arm64 真机的实时期限。

kernel/flow 切片前的选择为一百五十二项：在上述一百三十一项之外加入 `engine/CMakeLists.txt:3123-3251` 注册的二十一项规则引擎测试（`test_rule_engine` 98 例、十八个 `test_rule_engine_*` 与两个 `test_backward_machine_*`，共 643 例），均只链接 `rule_engine_core`，由既有 emulator 直接启动。新增 alternative `test_rule_engine(_(...))?$|test_backward_machine_(structure|context)$`；未注册的 `test_rule_engine_executor_stress`（需 `RULE_ENGINE_ENABLE_C11_PARALLEL`）与 hardening 用的 `rule_engine_fuzz_smoke` 不在选择内。Redis 路径（`RULE_ENGINE_ENABLE_REDIS` 默认关闭而未编译；stream ext 中 10 例因此只打印 SKIP 并按通过计）、C11 并行执行器压力测试、fuzz 与大规则集性能不在覆盖内。

world 切片前的选择为一百六十四项：在上述一百五十二项之外加入 `engine/CMakeLists.txt:4944-4981` 注册的十二项：八个只链接 `break_kernel` 的 `test_break_kernel_*`（actor 6、items 5、weapons 16、actions 1、move 1、level 1、area 2、flow 4 例）、宿主 `cmake -P` 的 `test_break_kernel_target_contract`，以及三个只链接 `break_flow` 的 `test_break_flow_*`（graph 8、serial 6、runtime 12 例），共 62 例。新增 alternative `test_break_kernel_(actor|items|weapons|actions|move|level|area|flow|target_contract)$|test_break_flow_(graph|serial|runtime)$`；既有的 `test_break_kernel_lua` 不受影响。

editor-core 切片前的选择为一百七十九项：在上述一百六十四项之外加入全部十五项 `headless;world` 测试：vegetation、time_of_day、visarea、world_stream、decal、voxel、road、mesh_stage 各 1 例，mesh_buffer 3、mesh_gpu 1（headless RHI）、world_mesh_fake 4 与 world_presenter_fake 5（fake RHI）、world_presentation 5、world_stream_job 1（单 worker 任务系统）、world_stream_world 2，共 29 例。新增 alternative `test_(vegetation|time_of_day|visarea|decal|voxel|road)$|test_world_(stream(_job|_world)?|mesh_fake|presentation|presenter_fake)$|test_mesh_(stage|buffer|gpu)$`；每段的 `$` 排除需要 GPU 的 `test_mesh_gpu_gl` 与 `test_world_presentation_gl`。

editor-audio 切片前的选择为一百八十九项：在上述一百七十九项之外加入九个编辑器核心可执行目标，doc 12、cmd 30、scene 18、components 27、viewport 22、gizmo 30、assets 21、i18n 8、scene_textures 9 例，共 177 例，另加宿主 `cmake -P` 的 `test_break_editor_target_contract`。新增 alternative `test_editor_(doc|cmd|scene|components|viewport|gizmo|assets|i18n|scene_textures)$|test_break_editor_target_contract$`；结尾锚点排除同名前缀扩展。编辑器 shell/UI、音频编辑器、插件、Lua 集成、字体与平台设置、远程会话及 GPU/窗口渲染不在该切片内。

editor-plugin-core 切片前的选择为一百九十项：在上述一百八十九项之外加入 `test_editor_audio`（23 例），覆盖 PCM 附件、撤销/重做、WAV 导入导出、波形、响度、真峰值与限幅。新增精确 alternative `test_editor_audio$`，排除 `test_editor_audio_sink`、编辑器 shell、core_app 音频/语音/设备测试及同名前缀扩展。该测试只验证纯 CPU 文档音频与 DSP，不包含编辑器音频 UI、真实音频设备或听感验证。

compose-core 切片前的选择为一百九十五项：在上述一百九十项之外加入五个编辑器插件核心可执行目标：cmds 7、host 8、sections 5、panels 9、manifest 10 例，共 39 例。新增五个不增加捕获组的精确 alternative `test_editor_plugin_cmds$|test_editor_plugin_host$|test_editor_plugin_sections$|test_editor_plugin_panels$|test_editor_plugin_manifest$`，排除 manifest_cli、plugin_load、flow、shell/UI 和同名前缀扩展。既有完整表达式已有 31 个捕获组，若再增加一个分组，CTest 会以 `RegularExpression::compile(): Too many parentheses` 返回零项；因此不使用 `test_editor_plugin_(...)$` 聚合写法，并以契约限制最多 31 个捕获组。这些测试只覆盖命令注册、宿主桥、检查器区块、面板模型与 manifest 解析，不证明动态库加载、编辑器 UI 或物理设备行为。

system/shader-io 切片前的选择为二百项：在上述一百九十五项之外加入五个 C Compose 核心可执行目标：tree 28、remember 8、store 27、runtime 8、async 17 例，共 88 例。前四项只链接 `mycompose`（它自带线程库）；async 链接 `mycompose_myui`、dummy PAL 与线程库，只创建 dummy PAL 的无头窗口对象（内存 LCD 加手动事件队列），不连接显示服务器、不用 GPU、不 fork。新增五个平铺精确 alternative `test_mycompose_tree$|test_mycompose_remember$|test_mycompose_store$|test_mycompose_runtime$|test_mycompose_async$`，完整表达式仍为 31 个捕获组。`test_mycompose_myui`、`test_mycompose_widget_primitives`、全部 `test_mycompose_cpp20*` 与 `test_mycompose_gpu_*` 不在选择内；Compose 与 myui 控件集成、C++20 对等层和 GPU 呈现的 arm64 验证仍是独立切片。

ui-render-cpu 切片前的选择为二百零五项：在上述二百项之外加入五个纯 CPU 可执行目标：`test_break_cvar` 12、`test_break_xml` 13、`test_editor_flow` 3、`test_editor_image` 7、`test_shader_io` 59 例，共 94 例。CVar 与 XML 链接可选库 `break_system`（lane 已构建 `break_integrity`，因此该库已配置；CVar 另内联 `platform_fs.c` 读写 `test_tmp()` 下的配置文件）；flow 与 image 链接 `break_editor_test`（image 另链接 `stb_image_write`）；shader I/O 只编入 `shader_io.c` 与 `log.c`。均不 fork、不起线程、不加载插件、不读环境变量。`test_shader_io` 的大部分用例经 `../shaders`、`../src` 和以 `__FILE__` 为基准的路径读取着色器与引擎源码，检查源码结构与变体路径映射，其 arm64 通过不代表 GPU 或着色器编译器证据。CI 从 `build-arm64` 运行时 `../shaders`、`../src` 不存在，实际经 `__FILE__` 的绝对源码路径找到文件；若以后引入 `-ffile-prefix-map`/`-fmacro-prefix-map`，该测试会明确失败而不是误报通过，需同步调整路径查找。新增五个平铺精确 alternative `test_break_cvar$|test_break_xml$|test_editor_flow$|test_editor_image$|test_shader_io$`，完整表达式仍为 31 个捕获组。插件动态加载（`test_break_plugin*`、`test_editor_plugin_load`）、`test_break_system_target_contract`、编辑器字体/设置/输入脚本不在选择内。

cpp20 切片前的选择为二百一十二项：在上述二百零五项之外加入七个纯 CPU 可执行目标：`test_mycompose_myui` 18、`test_mycompose_widget_primitives` 7、`test_render_features` 4、`test_rt_trace` 2、`test_rhi_tlas_instance_encode` 2、`test_rhi_metal_format_mapping` 5、`test_input_extended` 21 例，共 59 例。两个 Compose/myui 集成测试链接 `mycompose_myui` 或 `myui_core`、dummy PAL 与线程库，只创建无头窗口对象；render_features 只编入 `render_features.c`；rt_trace 链接 `engine_rhi_headless` 与 RHI 核心源码；TLAS 编码只编入 `rhi_validation.c`；Metal 格式映射编入 `shader_io.c`/`log.c`，五个与平台无关的用例在 arm64 上运行，MSL 反射一致性用例只在 Apple Metal 构建中编译；input_extended 编入 `input_extended.c` 与线程库。新增七个平铺精确 alternative，完整表达式仍为 31 个捕获组。`test_input_extended_single_cpu`（设置 CPU 亲和性、`RUN_SERIAL`）、需要 Vulkan 头文件的 `test_rhi_device_type`、`test_rhi_native`、C++20 对等层、GPU Compose 与宿主工具驱动的 `test_packer_roundtrip` 不在选择内。这些测试不代表 GPU 渲染、光追硬件或真实输入设备证据。前文二百项切片列为独立切片的 Compose/myui 集成两项（`test_mycompose_myui`、`test_mycompose_widget_primitives`）由此纳入；C++20 对等层与 GPU Compose 仍未纳入。

platform-input 切片前的选择为二百一十九项：在上述二百一十二项之外加入七个可执行目标。C++20 对等层四项由工具链已有的 `aarch64-linux-gnu-g++`（GCC 13.3）编译：`test_mycompose_cpp20_c_fixture` 1 例（C11 对照夹具）、`test_mycompose_cpp20` 14 例（链接 C11 夹具目标文件，在 arm64 上检查真实 C/C++ ABI）、`test_mycompose_cpp20_header` 与 `test_mycompose_cpp20_noexcept`（后者以 `-fno-exceptions` 编译）；`test_public_api_cpp20` 以 C++20 包含全部公共 C 头文件并做一次跨语言调用；另有 `test_core_style_prototype` 3 例与 `test_fork_deadline` 5 例。header、noexcept 与 public API 三项不打印 `=== Results` 行，只以退出码 0（编译期 `static_assert`/concept 检查加一次运行调用）判定通过，日志断言只核对它们出现在通过列表中。`test_fork_deadline` 是 `test_runtime_io`/`test_runtime_reload` 所用 fork 截止等待辅助函数本身的测试，按设计会打印 `CHILD TIMEOUT after 200 ms (killed)`、`PIPE TIMEOUT after 200 ms` 与 `CHILD TIMEOUT after 0 ms (killed)`；本地取证脚本 `assert_timeout_markers.py`（与各切片的选择契约一样放在被忽略的构建目录中，CI 不依赖它）要求这三条恰好出现且都来自该测试，其他任何超时标记仍判为失败；CI 的判定仍以各测试自身断言为准，其他使用该辅助函数的测试在超时时会因 `ASSERT_EQ(..., pid)` 失败。新增七个平铺精确 alternative，完整表达式仍为 31 个捕获组。`test_rhi_device_type`、`test_rhi_native`、`test_input_extended_single_cpu`、GPU Compose、`test_packer_roundtrip` 和编辑器 shell/Lua 不在选择内；qemu-user 下 fork 后建线程偶发挂起的根因仍未定位，本切片只验证截止等待辅助函数本身；`test_fork_deadline` 的子进程只做 `_exit`、`pause()` 或管道写入，不在子进程中建线程，因此不触发该已知挂起条件。

rhi-cpu 切片前的选择为二百二十五项：在上述二百一十九项之外加入六个纯 CPU 平台输入/窗口可执行目标。`test_platform_screen_simulated` 3 例（以 `tests/fake_qnx_screen` 假 SDK 编译 QNX Screen 窗口层）、`test_platform_window_mode` 14 例（仅头文件的无边框全屏状态机）、`test_pad_linux_feedback` 3 例（evdev 震动，注入式 I/O）、`test_pad_win_feedback_portable` 4 例与 `test_win32_touch` 4 例（均以 `tests/fake_windows` 假头文件编译 Windows 路径）、`test_wayland_touch` 4 例（Wayland 触控分发，链接 lane 已安装的 arm64 `wayland-client`，不连接合成器）。新增六个平铺精确 alternative，完整表达式仍为 31 个捕获组。单核亲和性变体 `test_input_extended_single_cpu`、宿主 CMake 编译矩阵 `test_platform_wsi_lifecycle`/`test_platform_wsi_compile_matrix`/`test_platform_vk_surface_abi` 与真实输入设备不在选择内。

editor-core-app-cpu 切片前的选择为二百三十项：在上述二百二十五项之外加入五个纯 CPU RHI 可执行目标。`test_rhi_rollout_log`（rollout 结构化日志）与 `test_rhi_runtime_select`（49 项运行时后端选择检查，`BREAK_RHI_RUNTIME_TESTING` 注入探测结果）只打印 `OK`，不打印 `=== Results` 行；`test_rhi_fault_injection` 6 例与 `test_rhi_wsi_attach` 3 例链接 `engine_rhi_headless`，在内存设备上注入失败并检查 WSI 附着状态机；`test_rhi_golden_parity` 读取仓库 `engine/tests/golden` 中已提交的 PPM，比较 Vulkan 与 OpenGL 参考图的 MAE 和最大误差，是纯 CPU 图像比较，不渲染。新增五个平铺精确 alternative，完整表达式仍为 31 个捕获组。Vulkan 探测 `test_rhi_vk_probe`、`test_rhi_device_type`、`test_rhi_native`、多后端符号检查 `test_rhi_multi_backend_symbols` 与各 RHI 宿主 CMake 契约不在选择内。

plugin-lua-shell 切片前的选择为二百三十六项：在上述二百三十项之外加入六个纯 CPU 可执行目标。编辑器四项：`test_editor_input_script` 8 例（输入脚本解析与回放）、`test_editor_settings` 7 例（偏好文件解析与路径解析；`XDG_CONFIG_HOME`/`HOME`/`BREAK_EDITOR_SETTINGS` 只用于计算路径，实际保存与读取写入 `test_tmp` 给出的临时目录）、`test_editor_fonts` 7 例（发行版字体布局在临时根目录下模拟，并读取仓库自带的 JetBrains Mono 与 Noto Sans SC；lane 未链接 arm64 fontconfig，真实系统用例改走内置路径表：构建目录是检出根目录的直接子目录时，经可执行文件相对路径找到仓库自带的两款字体，干净容器中打印 `2 candidates, cjk`；托管 runner 若预装 DejaVu/Liberation 等字体，路径表会再加入它们。该用例只检查候选存在、不重复且不超过上限）、`test_editor_audio_sink` 5 例（PCM 流输出与预览，FAKE 音频后端，不打开设备）；core_app 两项：`test_core_app_mesh` 3 例与 `test_core_app_runtime` 60 例（读取仓库 `assets/core_app` 资源，含多线程音频压力用例，不 fork）。新增六个平铺精确 alternative，完整表达式仍为 31 个捕获组。`test_core_app_voice`（原生约 12 秒，以 `time_sleep_us` 轮询，对模拟器下的时序敏感，未在 QEMU 下测量）、`test_core_app_voice_lane`、core_app lifecycle/资产契约、编辑器 shell/Lua 与插件动态加载不在选择内。

portable-contract 切片前的选择为二百四十项：在上述二百三十六项之外加入四个可执行目标。`test_break_plugin` 11 例经系统插件加载器（对已校验的 memfd 副本 `dlopen`）加载五个真实 arm64 共享库测试插件（含 ABI 不符、注册失败与缺少入口），另有一个越权夹具在校验后被替换到同一路径，测试断言它的构造函数从未执行；`test_editor_plugin_load` 5 例加载编辑器夹具插件；`test_editor_lua` 37 例为编辑器 Lua 控制台核心；`test_editor_shell` 为无头编辑器 shell，lane 中 186 例（切片提交时为 185 例，随后远程 CLI 参数解析用例移出 Snowflake 门控）：原生 Snowflake 构建为 233 例，其余 47 个远程会话与网络面板用例只在 `BREAK_ENABLE_SNOWFLAKE=ON` 时编译，lane 不配置 Snowflake。shell 在 QEMU 下约 11 秒，是本切片最慢的一项。新增四个平铺精确 alternative，完整表达式仍为 31 个捕获组。`test_break_plugin_unsupported`、`test_break_system_target_contract`、`test_editor_plugin_manifest_cli`（宿主 CMake 驱动）与 `test_core_app_voice` 不在选择内。

core-app-lifecycle 切片前的选择为二百四十六项：在上述二百四十项之外加入六个以模拟头文件或可移植路径编译其他平台代码的可执行目标：`test_glad_wgl_loader`（以 `TEST_WGL_LOADER_SIMULATED` 模拟 WGL 与 DLL 入口，检查 glad 的现代/旧版入口解析）、`test_platform_wsi_lifecycle` 8 例（`SIMULATE_WAYLAND` 下的 WSI 生命周期状态机）、`test_d3d12_lifetime_hresult_contract` 7 例（D3D12 对象生命周期与 HRESULT 映射，不调用 D3D12）、`test_net_loop_qnx` 17 例与 `test_qnx_perf_smoke` 3 例（以 poll 后端编译 QNX 网络循环，在回环上收发）、`test_break_plugin_unsupported` 1 例（不支持动态加载的平台上插件加载器失败即关闭）。新增六个平铺精确 alternative，完整表达式仍为 31 个捕获组。`test_core_app_assets` 经 `system()` 启动 arm64 资产烘焙器，未注册 aarch64 binfmt_misc 时内核无法执行该子进程（`Exec format error`，本地容器 9 例失败），不在选择内；`test_platform_vk_surface_abi`（lane 无 Vulkan 开发包）、`test_rhi_vk_probe`、`test_rhi_native`、`test_input_extended_single_cpu` 同样不在选择内。

voice-lane 切片前的选择为二百五十八项：在上述二百四十六项之外加入十二个 core_app 真实进程生命周期测试 `test_core_app_lifecycle_*`（load_unload、input_key/touch/cancel、script_flow、simulation、locomotion、facial、vehicle、ragdoll、render_record、roundtrip）。它们由宿主 `cmake -P engine/tests/test_core_app_lifecycle.cmake` 驱动，以 `--render=record --audio=record --fixed-step` 运行 arm64 `core_app` 并比对 trace；驱动经 `CORE_APP_RUNNER`（即 `CMAKE_CROSSCOMPILING_EMULATOR`，原生为空）启动 `core_app`。load_unload 末尾的 `LD_PRELOAD` 故障注入只在原生运行：实测在 qemu-aarch64 下强制执行该块时，加载器报告 `LD_PRELOAD cannot be preloaded ... ignored`，故障钩子从未生效，五个故障场景全部失败，因此驱动打印 `UNVERIFIED: LD_PRELOAD lifecycle fault injection is skipped under CORE_APP_RUNNER` 后跳过该块。roundtrip 经宿主 `python3` 改写检查点文件。构建列表显式加入 `core_app_lifecycle_preload`（`core_app` 本已依赖它）。十二项在 QEMU 下合计约 9 秒。新增十二个平铺精确 alternative，完整表达式仍为 31 个捕获组。`test_core_app_voice`、`test_core_app_voice_lane`、`test_core_app_assets` 与 core_app 宿主契约不在选择内。

packer 切片前的选择为二百五十九项：在上述二百五十八项之外加入 `test_core_app_voice_lane`。它由宿主 `cmake -P engine/tests/test_core_app_voice_lane.cmake` 驱动，经 `CORE_APP_RUNNER` 以 `--voice=fake` 运行 arm64 `core_app`：检查语音通道就绪先于运行时运行、停止先于运行时停止，产生与消费帧数一致且无丢帧、序号缺口与采集/参考溢出，处理后 PCM 非静音，两次 fake 运行 trace 逐字节一致，未开启语音时无语音事件且切换请求以 `reason=mode` 拒绝，非法 `--voice` 取值与组合以退出码 2 拒绝，场景中的采集设备切换被记录与计数，退出 tick 上的切换请求恰得一条 `failed reason=stopped`。不使用 `LD_PRELOAD`，QEMU 下约 4.4 秒。新增一个平铺精确 alternative，完整表达式仍为 31 个捕获组，构建列表不变（`core_app` 已在其中）。`test_core_app_voice`、`test_core_app_voice_null`、`test_core_app_voice_device` 与需要真实音频设备的测试不在选择内。

editor-manifest-cli 切片前的选择为二百六十项：在上述二百五十九项之外加入 `test_packer_roundtrip`。它由宿主 `cmake -P engine/tests/test_packer_roundtrip.cmake` 驱动，经 `TOOL_RUNNER`（即 `CMAKE_CROSSCOMPILING_EMULATOR`，原生为空）运行 arm64 `packer` 与 `verify_pak`：从目录树打包后由 `verify_pak` 校验并要求报告 `3 pak entries`，删除源文件后孤儿条目报错且指出 `sub/b.lua`，改动源文件后校验以非零退出，同名包内路径被拒绝且不留输出，超出容量的文件数打包失败且不留 `many.pak`，打包失败时不覆盖已有包且不留 `.tmp`。构建列表加入 `packer verify_pak`，QEMU 下约 0.4 秒。新增一个平铺精确 alternative，完整表达式仍为 31 个捕获组。

选择当前恰好二百六十一项：在上述二百六十项之外加入 `test_editor_plugin_manifest_cli`。它由宿主 `cmake -P engine/tests/test_editor_plugin_manifest_cli.cmake` 驱动，清除 `DISPLAY` 与 `WAYLAND_DISPLAY` 后经 `EDITOR_RUNNER`（即 `CMAKE_CROSSCOMPILING_EMULATOR`，原生为空）运行 arm64 `editor`：非法哈希、缺失文件、缺少参数值及多次给出时以最后一次为准的清单都以退出码 2 在开窗前拒绝并给出对应诊断；合法清单在 stderr 报告条目数与插件路径，随后裸 `--remote` 以失败即关闭在开窗前退出。lane 未开启 `BREAK_EDITOR_PLUGINS`，插件按“未加载”报告。构建列表加入 `editor`，QEMU 下约 0.2 秒。新增一个平铺精确 alternative，完整表达式仍为 31 个捕获组。

2026-11-20 起外层守护由 `timeout 300` 放宽为 `timeout 600`：一百五十二项串行 CTest 远端实测 171 秒（占 300 秒的 57%，`test_break_http` 在 QEMU 下单项 66 秒），而一百五十二项中 135 项未设 CTest `TIMEOUT`，只受外层守护约束。不改为 `-j` 并行，因为并行宿主负载正是 `test_runtime_io` 在 qemu-user 下偶发 fork 后建线程挂起的复现条件；job 级 `timeout-minutes: 25` 不变。

`-L /` 让模拟器使用 multiarch arm64 根文件系统。CMake 自动给可执行目标测试加 QEMU；宿主 CMake 驱动的归档契约接收 `CMAKE_NM`，其现场链接程序与 e2e 的 server/report/client 使用目标运行器。符号化 fixture 使用 `BREAK_TEST_RUNNER`；manifest、更新 e2e 和 keygen 的目标工具使用 `TARGET_RUNNER`，包括 keygen 的 RLIMIT_FSIZE 与并发 shell 启动。宿主 `nm`、CMake 和 shell 不模拟，shell 前缀逐元素转义。未配置交叉运行器时，原生测试仍直接执行。

e2e 的不可写统计文件场景保留权限语义：root 容器明确报告跳过；非 root runner 实际执行。integrity 的 ptrace 正例仅在 `BREAK_TEST_QEMU_USER=1` 且子进程因 `PTRACE_TRACEME` 失败 exit 90 时跳过设置步骤；原生和 exit 91 产品检测失败仍严格判红，不能把 QEMU 8/8 当作 ptrace 正向证据。两个真实 LLVM Mach-O 子检查也保留条件跳过语义。上述结果不能外推成全量 arm64 `ctest`、GPU 或物理设备证据。

`--toolchain` 必须传绝对路径；相对路径不会按仓库根目录解析，会在读取工具链之前报 `Could not find toolchain file`。不要把 `/usr/aarch64-linux-gnu` 单独当编译器 sysroot，否则链接器会重复添加交叉 libc 链接脚本中的绝对路径前缀。没装交叉编译器时，configure 会在成功读取工具链后报告 `aarch64-linux-gnu-gcc` 不在 `PATH`，这是预期的失败形式。


## 补充（2026-11-22）：可选 C++20 RuntimeBusApplication

根项目的 `BREAK_FRAMEWORK_ENABLE_RUNTIME` 默认 OFF。默认构建只生成原有 framework 与 `empty`，`empty` 不依赖 `common_runtime`、`runtime_core` 或 `engine`。需要 `bk::RuntimeBusApplication` 时显式启用并链接 `common_runtime`：

```bash
cmake -S . -B build-framework-runtime \
  -DBREAK_FRAMEWORK_ENABLE_RUNTIME=ON \
  -DENGINE_BUILD_TESTS=OFF \
  -DENGINE_RHI_BACKEND=vulkan -DMYUI_PAL=dummy
cmake --build build-framework-runtime --target common_runtime empty --parallel 2
```

根启用 runtime 时，若调用方未定义 `ENGINE_BUILD_TESTS`，根项目只把它默认设为 OFF；显式 `-DENGINE_BUILD_TESTS=ON` 会保留并生成 `test_framework_runtime_bus` 等测试目标。`common_runtime`、其公开头文件的使用方及该测试均使用 C++20；旧文档中的 C++11 framework 描述仅作历史记录。

下面的函数骨架展示 `ApplicationInterface` 生命周期与全局 IO 的组装顺序。它假定宿主已经初始化 VFS/IO，并已安排 IO 请求生产；应用自有初始化、请求提交和生产者停止代码不展开，因此它不是独立可执行程序。示例派生类在收到第一条合法 IO notice 后退出循环。

```cpp
#include <cstdint>

#include "runtime_bus_application.h"

extern "C" {
#include <runtime/runtime_bus.h>
#include <runtime/runtime_io.h>
}

class IoApplication final : public bk::RuntimeBusApplication {
 protected:
  void OnRuntimeIoNotice(const BreakRuntimeIoNotice& notice) override {
    (void)notice;
    is_quit_ = true;
  }
};

int RunRuntimeBusApplication() {
  BreakRuntimeBus* bus = nullptr;
  if (break_runtime_bus_create(&bus) != BREAK_RUNTIME_OK) {
    return 1;
  }
  if (break_runtime_io_attach_bus(bus) != BREAK_RUNTIME_OK) {
    break_runtime_bus_destroy(bus);
    return 1;
  }

  IoApplication application;
  bk::ApplicationInterface* app = &application;
  int application_result =
      static_cast<int>(application.AttachRuntimeBus(bus));
  if (application_result == BREAK_RUNTIME_OK) {
    application_result = app->Init();
    if (application_result == 0) {
      while (!app->IsQuit()) {
        app->Tick();
      }
    }
  }

  app->DeInit();
  const BreakRuntimeError shutdown_result = break_runtime_io_shutdown(1000u);
  const BreakRuntimeError detach_result = break_runtime_io_attach_bus(nullptr);
  break_runtime_bus_destroy(bus);

  if (shutdown_result == BREAK_RUNTIME_TIMEOUT) {
    return 2;
  }
  if (application_result != 0 || shutdown_result != BREAK_RUNTIME_OK ||
      detach_result != BREAK_RUNTIME_OK) {
    return 1;
  }
  return 0;
}
```

生命周期顺序是：创建 bus；由调用方执行 `break_runtime_io_attach_bus(bus)`，完成生产 IO attach 和 notice kind 注册；在应用 Init 前 `AttachRuntimeBus`；通过 `ApplicationInterface` 初始化并在所有者线程 Tick。全局 attach 成功后，应用 Attach、Init 和运行共享同一个清理出口：保存应用结果，先执行应用 DeInit，再始终保存并检查 `shutdown_result` 与 `detach_result`，解除全局挂接后销毁 bus，最后按应用及清理结果返回。两个应用初始化失败路径不会提前跳过或忽略 IO shutdown。应用 DeInit 已解除自身订阅并销毁自有队列，所以随后析构不会访问已销毁的 bus。

完整应用必须先停止 IO 生产者，再进入上述收尾路径；bus 只在 detach 后销毁。`RuntimeBusApplication` 不拥有也不自动执行进程级 IO shutdown；全局 attach 返回后，调用方还必须保证 bus 比所有挂接关系长寿。`BREAK_RUNTIME_TIMEOUT` 独立返回非零码 2，其他应用、shutdown 或 detach 失败返回非零码 1。返回 2 不表示完整清理：IO facade 可能仍为 `STOPPING` 并保留 live ownership，调用方必须继续调用 `break_runtime_io_shutdown` 直到返回 `BREAK_RUNTIME_OK`；在此之前不能重启 IO，也不能把这次返回当作关停完成。示例在 shutdown 后仍执行 detach；detach 后销毁 bus 本身安全，但这不会替代调用方继续完成 facade 关停的责任。

`test_framework_runtime_bus` 当前覆盖 9 个行为用例；现有证据是 focused CTest 3/3、根构建契约 1/1（四个子树）以及实现者记录的 focused ASan/UBSan/TSan 通过。完整 Vulkan/OpenGL、ASan 非图形套件、fuzz、Windows/macOS/其他生成器与远端 CI 尚待最终验收，上述构建与示例不代表这些矩阵已经通过。
