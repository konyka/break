# Break Engine 构建与开发指南

## 1. 环境要求

### 1.1 编译器
- GCC 11+ 或 Clang 14+（C11 支持）
- CMake 3.20+（engine）/ CMake 3.25+（framework）

#### 编译器支持矩阵

| 平台 | 编译器 | 状态 | 工具链文件 | 备注 |
|------|--------|------|-----------|------|
| Linux | GCC 7+ | 完整支持 | (默认) | 推荐，CI 主线 |
| Linux | Clang 10+ | 完整支持 | `toolchain-clang-linux.cmake` | 零警告通过 |
| Windows | MSVC (cl) | 支持 | `toolchain-msvc.cmake` | 原生 Windows 开发 |
| Windows | Clang | 支持 | `toolchain-clang-win.cmake` | clang + lld-link |
| Windows | MinGW GCC | 支持 | `toolchain-mingw.cmake` | Linux 交叉编译 |

### 1.2 系统依赖（Linux）
- X11 开发库 (libx11-dev) 或 Wayland 开发库（二选一，编译时互斥）
- OpenGL (libgl1-mesa-dev) 或 Vulkan SDK
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

### 2.2 Wayland 后端构建

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

### 2.3 Linux 构建矩阵

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

### 2.4 Windows 平台构建

#### 使用 MSVC (Visual Studio)

在 Visual Studio Developer Command Prompt 中：
```cmd
cd engine
mkdir build-msvc && cd build-msvc
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

或使用 Ninja：
```cmd
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja
```

或显式指定 MSVC 工具链文件：
```cmd
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-msvc.cmake -G Ninja
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

### 2.5 框架应用
```bash
# 从项目根目录
cmake -B build-gl
cmake --build build-gl
```

### 2.6 CMake 选项
| 选项 | 默认值 | 说明 |
|------|--------|------|
| ENGINE_VULKAN | OFF | 启用 Vulkan 后端（可与 X11/Wayland 任一窗口后端组合） |
| ENGINE_ENABLE_WAYLAND | OFF | 启用 Wayland 窗口后端（与 X11 **编译时互斥**） |
| ENGINE_USE_ASAN | OFF | 启用 AddressSanitizer（GCC/Clang 使用 `-fsanitize=address`，MSVC 使用 `/fsanitize=address`） |
| CMAKE_C_STANDARD | 11 | C 语言标准 |
| CMAKE_C_COMPILER | (自动) | 指定 C 编译器（`gcc` / `clang` / `cl`） |
| CMAKE_CXX_COMPILER | (自动) | 指定 C++ 编译器（`g++` / `clang++` / `cl`） |
| CMAKE_TOOLCHAIN_FILE | (无) | 使用工具链文件（见上方编译器支持矩阵） |

> 编译器标志由 CMake 根据 MSVC / Clang / GCC **自动检测并应用三路分支**，无需手动指定告警/优化标志。

### 2.7 完整构建矩阵

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
| Windows | Win32 | OpenGL | MSVC | 待验证 |
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
| test_vulkan | build-*/test_vulkan | 测试程序 |
| packer | build-*/packer | 资源打包工具 |
| empty | build-gl/empty/empty | 最小化应用示例 |

## 4. 编译选项与标准

### 4.1 编译器警告
```cmake
-Wall -Wextra -Werror -pedantic
```
- 零容忍警告策略
- 严格 C11 标准遵从

### 4.1.1 编译器兼容性说明

- **GCC/Clang 通用标志**：`-Wall -Wextra -Werror -pedantic`
- **MSVC 标志**：`/W4 /WX /utf-8`，自动定义 `_CRT_SECURE_NO_WARNINGS`
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
cd engine/build-vk  # 或 build-gl
./test_vulkan       # 运行 17 项单元测试
```

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

## TODO: Windows 平台验证（待环境具备后执行）

> 当前开发环境为 Fedora 44，Windows 功能已实现但尚未在真实 Windows 环境中验证。以下为待验证/待完善事项：

### 待验证项

1. **Windows 原生编译验证** — 使用 MSVC (Visual Studio 2019+) 编译 engine 库和 demo，确认零警告零错误
2. **MinGW 交叉编译验证** — 在 Linux 上安装 mingw-w64 后使用 `toolchain-mingw.cmake` 交叉编译，验证产出物可在 Windows 运行
3. **OpenGL WGL 后端运行验证** — 在 Windows 上运行 engine_demo (OpenGL 模式)，确认窗口创建、渲染、输入响应正常
4. **Vulkan Win32 Surface 运行验证** — 在 Windows 上运行 engine_demo (Vulkan 模式)，确认 Surface 创建和渲染正常
5. **高 DPI 验证** — 在 4K/高分屏 Windows 设备上测试 WM_DPICHANGED 响应和窗口缩放行为
6. **文件热重载验证** — 确认 FindFirstChangeNotification 在 Windows 上正确检测着色器/资源文件修改

### 环境准备

- 安装 MinGW: `sudo dnf install mingw64-gcc mingw64-headers`
- 或准备 Windows 虚拟机/物理机进行原生测试
- Vulkan 测试需安装 Windows 版 Vulkan SDK
