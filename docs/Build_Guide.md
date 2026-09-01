# Break Engine 构建与开发指南

## 1. 环境要求

### 1.1 编译器
- GCC 11+ 或 Clang 14+（C11 支持；Linux Clang Release 的默认 IPO/LTO 构建还需要 `lld`）
- CMake 3.20+（engine）/ CMake 3.25+（framework）

#### 编译器支持矩阵

| 平台 | 编译器 | 状态 | 工具链文件 | 备注 |
|------|--------|------|-----------|------|
| Linux | GCC 7+ | 完整支持 | (默认) | 推荐，CI 主线 |
| Linux | Clang 10+ + lld | 完整支持 | `toolchain-clang-linux.cmake` | 零警告通过 |
| Windows | MSVC (cl) | 支持 | `toolchain-msvc.cmake` | 原生 Windows 开发 |
| Windows | Clang | 支持 | `toolchain-clang-win.cmake` | clang + lld-link |
| Windows | MinGW GCC | 支持 | `toolchain-mingw.cmake` | Linux 交叉编译 |

### 1.2 系统依赖（Linux）
- X11 开发库 (libx11-dev) 或 Wayland 开发库（二选一，编译时互斥）
- OpenGL (libgl1-mesa-dev) 或 Vulkan SDK
- FreeType 开发库（推荐；`dxx_break` 默认 CJK TTC 字体和中文显示需要它）
- pthread
- 游戏手柄支持：evdev（Linux 内核内置，无需额外包）

### 1.3 系统依赖（Windows）
- Visual Studio 2019+ 或 MinGW
- Windows SDK
- DirectX 11 SDK (可选，用于 platform 演示)

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

设备选择：默认取第一块"caps 可查且可呈现"的 GPU（带兜底的回退到
gpus[0] + 回退 caps，见 rhi_vk.c R574/R575）；要强制指定某块卡（例如本机
AMD 核显的 caps 查询有驱动缺陷、需在 AMD 上验证），设
`RE_VK_DEVICE_INDEX=<n>`（枚举顺序见运行日志里的 Vulkan GPU 行）。

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
`ENGINE_USE_UBSAN` 默认为 OFF；GCC/Clang 开启后使用 `-fsanitize=undefined`，不改变默认构建：
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

`test_shader_io` 与无 graphics 标签的 `test_platform_win32_runtime` 在 Windows CTest 中启用；后者使用真实 Win32
窗口、`GetWindowTextW`、`WM_SIZE` 和平台销毁路径，不创建 graphics context。源码路径同时支持 `/` 与 `\\` 分隔符。
`test_vulkan` 需要真实 WGL/GPU 环境，因此保留 `graphics` 标签并从 headless CI 中排除。

在具备本机 GPU 的 Windows 环境可额外执行完整 graphics 集成测试：

```powershell
Push-Location engine
..\build-win-clang\test_vulkan.exe
Pop-Location
```

图形集成测试仍需具备 WGL/Vulkan/GPU 环境后单独验证。

#### 使用 MSVC (Visual Studio)

已在 MSVC 19.51.36246 / Visual Studio 2026 Developer Command Prompt 中使用 Ninja 完成
Debug 原生 Windows 构建与非图形 Win32 runtime smoke。可复制以下命令：
```cmd
cmake -S engine -B build-msvc-1451-audit -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON -DENGINE_VULKAN=OFF -DENGINE_ENABLE_IPO=OFF
cmake --build build-msvc-1451-audit --parallel
ctest --test-dir build-msvc-1451-audit -LE graphics --output-on-failure
```

上述配置成功，完整构建在 `/W4 /WX /utf-8` 以及 `/experimental:c11atomics` 下通过；重复构建无剩余工作。
非图形 CTest `56/56` 通过，其中包括 `test_platform_win32_runtime`。这提供的是非图形、headless
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

macOS 使用 Xcode Command Line Tools 提供的系统框架；文件监视模块额外链接 `CoreServices` 与 `CoreFoundation`，无需单独安装第三方依赖。

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
- Vulkan SDK（如使用 Vulkan/MoltenVK 后端）
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
| ENGINE_VULKAN | OFF | 启用 Vulkan 后端（可与 X11/Wayland 任一窗口后端组合） |
| ENGINE_ENABLE_WAYLAND | OFF | 启用 Wayland 窗口后端（与 X11 **编译时互斥**） |
| ENGINE_USE_ASAN | OFF | 启用 AddressSanitizer（GCC/Clang 使用 `-fsanitize=address`，MSVC 使用 `/fsanitize=address`） |
| ENGINE_USE_UBSAN | OFF | 启用 UndefinedBehaviorSanitizer（GCC/Clang 使用 `-fsanitize=undefined`；MSVC 不启用） |
| ENGINE_ENABLE_IPO | ON | Release 构建中在工具链支持时启用 IPO/LTO，仅作用于 `engine` 静态库 |
| MYUI_FONT_FREETYPE | ON | 找到 FreeType 时启用 hinted 字形和 TTC 多字面选择；CJK 默认字体需要此选项 |
| MYUI_FONT_STB | ON | 启用 `stb_truetype` 独立 TTF/OTF 回退 |
| CMAKE_C_STANDARD | 11 | C 语言标准 |
| CMAKE_C_COMPILER | (自动) | 指定 C 编译器（`gcc` / `clang` / `cl`） |
| CMAKE_CXX_COMPILER | (自动) | 指定 C++ 编译器（`g++` / `clang++` / `cl`） |
| CMAKE_TOOLCHAIN_FILE | (无) | 使用工具链文件（见上方编译器支持矩阵） |

> 编译器标志由 CMake 根据 MSVC / Clang / GCC **自动检测并应用三路分支**，无需手动指定告警/优化标志。

### 2.8 完整构建矩阵

| 平台 | 窗口系统 | 图形后端 | 编译器 | 验证状态 |
|------|---------|---------|--------|---------|
| Linux | X11 | OpenGL | GCC | 通过 |
| Linux | X11 | OpenGL | Clang | 通过 |
| Linux | X11 | Vulkan | GCC | 通过 |
| Linux | X11 | Vulkan | Clang | 通过 |
| Linux | Wayland | OpenGL | GCC | 通过 |
| Linux | Wayland | OpenGL | Clang | 通过 |
| Linux | Wayland | Vulkan | GCC | 通过 |
| Linux | Wayland | Vulkan | Clang | 通过 |
| Windows | Win32 | OpenGL | MinGW | 待验证 |
| Windows | Win32 | OpenGL | MSVC | 原生构建 + 非图形 Win32 smoke 已验证 |
| Windows | Win32 | OpenGL | Clang | 待验证 |
| Windows | Win32 | Vulkan | MinGW | 待验证 |
| Windows | Win32 | Vulkan | MSVC | 待验证 |
| Windows | Win32 | Vulkan | Clang | 待验证 |

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

GitHub Actions workflow：`.github/workflows/ci.yml`，push/PR 到 `master` 触发，`ubuntu-latest` 上两个独立 job：

| Job | 配置 | 依赖（apt） | 测试 |
|-----|------|-------------|------|
| `gl` | X11 + OpenGL，Debug | `libx11-dev libxrandr-dev libgl1-mesa-dev libfreetype6-dev fonts-noto-cjk` | 全量构建 + `ctest -LE graphics` |
| `vk` | X11 + Vulkan，Debug | `libx11-dev libxrandr-dev libvulkan-dev libshaderc-dev libfreetype6-dev fonts-noto-cjk` | 全量构建 + `ctest -LE graphics` |
| `wayland-gl` | Wayland + EGL OpenGL，Debug | `libwayland-dev wayland-protocols libxkbcommon-dev libegl1-mesa-dev libfreetype6-dev fonts-noto-cjk` | 全量构建、`dxx_break`、`ctest -LE graphics` |
| `wayland-vk` | Wayland + Vulkan，Debug | `libwayland-dev wayland-protocols libxkbcommon-dev libvulkan-dev libshaderc-dev libfreetype6-dev fonts-noto-cjk` | 全量构建、`dxx_break`、`ctest -LE graphics` |
| `windows-clang` | Win32 + OpenGL，Debug | Windows SDK/Ninja | 全量构建、`dxx_break`、`test_platform_win32_runtime` 及其他 `ctest -LE graphics` |
| `macos-vulkan` | Cocoa + MoltenVK，Debug | Homebrew `molten-vk`、`shaderc`、`freetype` | 编译 `dxx_break` |
| `linux-clang-release` | X11 + OpenGL，Clang/LLD，Release，IPO ON | `clang lld cmake ninja-build libx11-dev libxrandr-dev libgl1-mesa-dev libfreetype6-dev fonts-noto-cjk` | 构建 + `ctest -LE graphics` |
| `linux-gcc-sanitizers` | X11 + OpenGL，GCC，Debug，ASan + UBSan | `gcc cmake ninja-build libx11-dev libxrandr-dev libgl1-mesa-dev libfreetype6-dev fonts-noto-cjk` | 构建 + `ctest -LE graphics` |
| `linux-graphics-smoke` | X11 + Vulkan，GCC，Debug，Xvfb + lavapipe/llvmpipe | `libvulkan-dev libshaderc-dev mesa-vulkan-drivers libgl1-mesa-dri xvfb` 及 X11/FreeType 依赖 | 仅 `ctest -L graphics`（当前为 `test_vulkan`） |

CI 步骤与本地命令一一对应：装依赖 → `cmake -S engine -B build` → `cmake --build build --parallel` → `ctest --test-dir build -LE graphics --output-on-failure`。Wayland、Windows 和 macOS job
额外显式构建 `dxx_break`，使 PAL/RHI 接口成为平台编译门禁。

`linux-graphics-smoke` 显式启动 Xvfb，并选择 Mesa 的软件 Vulkan ICD（lavapipe）及 llvmpipe。它只运行现有的 `graphics` 标签测试；若 runner 缺少 Xvfb 或 lavapipe ICD，步骤直接失败，不把未执行宣称为通过。软件渲染与参考 GPU 的 golden image 可能存在差异，因此该 job 是环境/启动 smoke，不替代真实 GPU graphics 验证。Windows headless CTest 的 `test_platform_win32_runtime` 只提供 Win32 platform smoke 证据，不覆盖 WGL/Vulkan/GPU/present；macOS Cocoa/Metal 和真实 Wayland compositor runtime 仍未由这些 jobs 验证，状态保持待验证；Wayland jobs 当前只提供构建与非图形 CTest 证据。

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
    Engine engine;
    EngineConfig cfg = { .width = 1280, .height = 720, .title = "My Game" };
    engine_init(&engine, &cfg);
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
2. **OpenGL WGL 后端运行验证** — 在 Windows 上运行 engine_demo (OpenGL 模式)，确认窗口创建、渲染、输入响应正常
3. **Vulkan Win32 Surface 运行验证** — 在 Windows 上运行 engine_demo (Vulkan 模式)，确认 Surface 创建和渲染正常
4. **高 DPI 验证** — 在 4K/高分屏 Windows 设备上测试 WM_DPICHANGED 响应和窗口缩放行为
5. **文件热重载验证** — 确认 FindFirstChangeNotification 在 Windows 上正确检测着色器/资源文件修改

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
