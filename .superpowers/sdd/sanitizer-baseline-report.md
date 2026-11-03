# UI sanitizer 基线调查与修复报告

## 状态与结论

**DONE（项目标准 CTest 配置）**。

两个失败都不是 Cry 模块或 UI 行为断言失败，而是 NVIDIA Vulkan ICD 的第三方进程生命周期缓存触发了 LeakSanitizer。仓库自己的 Vulkan acquire/release 路径已经调用 `vkDestroyCommandPool`、`vkDestroyDevice` 和 `vkDestroyInstance`；没有证据支持再增加一个仓库资源释放调用。

修复只在两个受影响测试中生效：保留 Vulkan ICD 映射以便 LSan 正确归因，并且只 suppress `libnvidia-glcore.so`、`libnvidia-glsi.so`。不 suppress libdbus、Vulkan loader、其他驱动或项目分配，不关闭 ASan/LSan，不跳过测试，不改变行为断言或生产代码。

## 范围和环境

- 工作树：`/home/timeshift/opensource/break/.worktrees/cry-sanitizer`
- 分支/基线：`cry-sanitizer` / `6993a562b78fd238dd553b4dfc069d119b0c340a`
- 编译器：GCC 16.2.1，Debug，`ENGINE_ENABLE_IPO=OFF`
- 新基线有效后端：`ENGINE_RHI_BACKEND_EFFECTIVE=vulkan`，自动 Vulkan + OpenGL fallback
- 对照旧树：`/home/timeshift/opensource/break/build-sdd-p4-asan`，有效后端为 `opengl`
- 关键宿主包：Fedora 44；`vulkan-loader 1.4.341-1.fc44`；`xorg-x11-drv-nvidia-libs 615.78.08-1.fc44`；`mesa-vulkan-drivers 26.2.5-1.fc44`；`dbus-libs 1.16.2-1.fc44`
- 未修改 master、其他工作树，未 push。

## Before：可重复失败

配置、完整构建和回归命令：

```bash
cmake -S engine -B build-cry-asan \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-cry-asan --parallel 2
ctest --test-dir build-cry-asan -LE 'graphics|fuzz' --output-on-failure
```

结果：

- 完整构建 exit 0。
- CTest 入选 283 项，仅 `test_myui_window_manager` 和 `test_myui_vgcanvas_backend` 失败；另有既有的 `test_d3d12_dependency_gate` Windows-only skip。
- window manager 的行为断言为 **239/239**，然后 LSan 失败。
- vgcanvas 的行为断言为 **45/45**，然后 LSan 失败。
- 任务给定基线为 22018 和 88696 字节。本次独立复跑也得到 window manager **22018 字节/408 allocations**（`window-manager-modulemap-before.log`）；另一次 CTest 为 22098/408。vgcanvas 直跑得到 88904/1632，CTest 复跑为 133260/2448。失败稳定，但 NVIDIA/D-Bus 初始化的时序和次数会改变总字节数，因此不把某一个总数当作跨运行常量。
- 未见 UBSan runtime error；失败退出由 LSan 引起。

主要日志均保存在本工作树 `build-cry-asan/`，关键文件为 `build-before.log`、`ctest-before.log`、`window-manager-before.log`、`window-manager-modulemap-before.log`、`vgcanvas-backend-before.log`、`vgcanvas-backend-default-before.log`。

## 根因调查

### 1. 完整项目栈定位到真实 Vulkan 调用

window manager 的分配栈穿过：

```text
vkEnumerateInstanceExtensionProperties
vk_ext_present                       my_vgcanvas_vulkan.c:85
vk_global_init                       my_vgcanvas_vulkan.c:171
my_vgcanvas_vulkan_instance_acquire  my_vgcanvas_vulkan.c:355
window_enable_gpu_vulkan             my_window.c:730
gpu_backend_request_reports_actual_state
```

vgcanvas 栈还穿过 `vulkan_instance_acquire_release_worker` 和 `my_vgcanvas_vulkan_create_offscreen`。这排除了“新 Cry 测试直接泄漏”的猜测，并解释为什么 window manager 的 dummy PAL 行为断言返回 `MY_RET_NOT_SUPPORTED` 却仍触发驱动初始化。

仓库 release 路径在 `my_vgcanvas_vulkan.c:328-343` 逐一销毁 command pool、device、instance。失败不是遗漏这些关闭调用。

### 2. 动态库归属由实时栈确认，不是按地址猜测

`LD_DEBUG=files` 显示 Vulkan loader 扫描 NVIDIA 和 Mesa ICD；NVIDIA manifest `/usr/share/vulkan/icd.d/nvidia_icd.x86_64.json` 指向 `/usr/lib64/libGLX_nvidia.so.0`，其依赖包含 `libnvidia-glcore.so.615.78.08`、`libnvidia-glsi.so.615.78.08`，运行中还会加载 libdbus。

在 `dbus_message_new_empty_header` 上设置的 GDB pending breakpoint 给出同一进程的实时栈：

```text
dbus_message_new_empty_header / dbus_message_new_signal
_dbus_connection_new_for_transport / internal_bus_get
libnvidia-glcore.so.615.78.08
libGLX_nvidia.so.0
vk_icdNegotiateLoaderICDInterfaceVersion
loader_icd_scan / terminator_EnumerateInstanceExtensionProperties
vkEnumerateInstanceExtensionProperties
vk_ext_present / vk_global_init / window_enable_gpu_vulkan
```

证据见 `window-manager-dbus-caller.log` 和 `window-manager-lddebug-before.log`。NVIDIA-only 最小复现还给出 Build ID：glcore `430f37a0477a31714631a4d0b518bb024fce202f`，glsi `f36ec6c64548b2912b49c1ebd12a4f14fb5e20aa`。

### 3. 加载/卸载边界解释 `<unknown module>`

instance 释放后 loader 会 `dlclose` ICD。LSan 在进程退出时读取已卸载地址，得到 `<unknown module>`。Vulkan loader 提供的 `VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1` 可保持模块映射；设置后，原未知帧精确符号化为 glcore/glsi 的相同偏移，D-Bus 报告不再残留，只剩：

- glcore：13018 字节，270 allocations；
- glsi：6509 字节，135 allocations；
- 合计 **19527 字节/405 allocations**。

只用两条 NVIDIA 模块 suppression、但不保留映射时，window manager 仍报告 22098/408，vgcanvas 也仍失败，证明“保留映射以归因”是必要边界，而不是用 suppression 掩盖未知地址。

### 4. 不含仓库代码的最小复现与单 ICD 对照

`build-cry-asan/vk_probe_repro.c` 只做一次 `vkEnumerateInstanceExtensionProperties`，以 `-fsanitize=address,undefined` 编译并链接 `-lvulkan`，不包含或调用任何仓库代码。

```bash
./vk_probe_repro
VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/nvidia_icd.x86_64.json ./vk_probe_repro
VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/lvp_icd.x86_64.json ./vk_probe_repro
```

默认和 NVIDIA-only 均报告同样的 **19527/405**，lavapipe-only exit 0 且零报告。两条模块 suppression 可使最小 NVIDIA 复现通过，suppression 统计精确等于上述 405 个分配。该对照把根因限定到 NVIDIA ICD 初始化缓存，而非仓库 allocator、FreeType、HarfBuzz 或 Cry 代码。

### 5. 相似工作配置

直接运行旧 `build-sdd-p4-asan` 二进制且保持 LeakSanitizer 开启：

- window manager：**239/239**，零报告；
- vgcanvas：**44/44**，零报告。

旧树 `ENGINE_RHI_BACKEND_EFFECTIVE=opengl`，vgcanvas 没有 `MYUI_HAS_VULKAN`；新树为 `vulkan`，有 `MYUI_HAS_VULKAN=1`，并增加 Vulkan 用例至 45 项。这与最小 Vulkan 复现一致。旧树 IPO 差异不是根因，因为无仓库代码的纯 Vulkan 程序已独立复现。

## 单一假设与最小检验

假设：**失败来自 NVIDIA glcore/glsi 的进程缓存；保持 ICD 映射后，仅这两条模块 suppression 即可消除第三方报告，同时项目泄漏仍会被捕获。**

最小检验矩阵：

| 检验 | 结果 |
| --- | --- |
| 两条模块 suppression，允许卸载 | 两测试仍失败；未知帧不能匹配模块名 |
| 仅保留 ICD 映射，不 suppression | 两测试行为全过；剩 19527/405，全部归属 NVIDIA |
| 保留映射 + 两条模块 suppression | 两测试全过，零 ASan/UBSan 报告；只 suppress 405 个 NVIDIA 分配 |
| 同一 suppression 头下故意在测试程序 `malloc(123)` 不释放 | LSan 仍正确报告 `lsan_project_guard.c:5` 的 123 字节项目侧泄漏 |

因此没有给 libdbus 添加 suppression，也没有使用 `detect_leaks=0`、跳过测试或 broad `leak:malloc`/`leak:calloc`。

## 实施内容

- `engine/tests/test_vulkan_lsan.h`：在 Linux ASan（GCC 或 Clang）下提供 `__lsan_default_suppressions`，仅两条 NVIDIA 模块规则；其他配置无符号、无行为。
- `engine/tests/test_myui_window_manager.c`、`engine/tests/test_myui_vgcanvas_backend.c`：只包含上述测试专用头，既有断言未改。
- `engine/CMakeLists.txt`：仅当 `ENGINE_USE_ASAN=ON`、Linux 且实际启用 `MYUI_VULKAN_ENABLED` 时，为这两个 CTest 目标设置 `VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1`。不修改其他测试环境，不覆盖 `ASAN_OPTIONS`/`LSAN_OPTIONS`。
- `docs/Build_Guide.md`：记录归属、适用范围、直跑命令和不得扩大 suppression 的规则。

suppression 编译进两个测试二进制，而非全局应用到其他测试或生产库。normal 构建不定义该 hook，CTest 也不设置此环境。

## After：验证证据

### 构建与 focused 测试

```bash
cmake --build build-cry-asan --parallel 2
ctest --test-dir build-cry-asan --output-on-failure \
  -R '^test_myui_(window_manager|vgcanvas_backend)$'
```

- ASan+UBSan 全目标构建 exit 0。
- focused CTest **2/2 passed**。
- `ctest -N -V` 确认两个目标各有且仅有 `VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1` 的注入环境。

等价直跑：

```bash
VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1 ./build-cry-asan/test_myui_window_manager
VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1 ./build-cry-asan/test_myui_vgcanvas_backend
```

分别 **239/239**、**45/45**，exit 0，无 ASan/UBSan 报告。LSan suppression 统计分别均只包含 glcore 13018 和 glsi 6509；没有 libdbus 或项目帧。

### 完整非图形 ASan+UBSan 回归

```bash
ctest --test-dir build-cry-asan -LE 'graphics|fuzz' --output-on-failure
```

**283 入选，0 失败；282 passed + 1 个既有 Windows-only skip**。总耗时 70.69 秒，日志 `build-cry-asan/ctest-after.log`。

### normal 对照

```bash
cmake -S engine -B build-cry-normal \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF
cmake --build build-cry-normal --parallel 2
ctest --test-dir build-cry-normal -LE 'graphics|fuzz' --output-on-failure
```

- 全目标构建 exit 0。
- **283 入选，0 失败；282 passed + 1 个既有 Windows-only skip**，总耗时 43.16 秒。
- 两个目标在 normal 下裸直跑分别 239/239、45/45，exit 0。

### 自审与格式

- 变异检查：项目侧 123 字节泄漏仍被 LSan 捕获，证明两条规则不掩蔽项目分配。
- `git diff --check` 通过。
- 自审确认：无生产行为变化、无断言修改、无全局 sanitizer 环境、无宽泛 suppression、无测试跳过。

## 限制和后续边界

- 本结论和 suppression 只适用于两个测试的第三方 NVIDIA 分配。驱动更新若出现新库、项目帧或其他分配，必须重新调查，不能自动扩展规则。
- suppression 是模块级而非内部函数级；NVIDIA 内部符号被剥离且地址随 ASLR/卸载变化。通过保留映射、限制到两个测试二进制和 405 个已验证分配来收窄范围。
- 不带 loader 环境的裸直跑仍可能在卸载后报告这些第三方缓存；修复后的标准路径是 CTest，或本文给出的带同一环境直跑命令。没有采用 `.preinit_array`、硬编码 `dlopen`、故意保留 instance 等绕过方式。
- 未宣称修复 NVIDIA/libdbus 本身的内存管理；仓库无法通过公共 API 释放这些缓存。
- 按要求排除 `graphics|fuzz`，未把这些标签的测试计为通过。vgcanvas 的 Vulkan offscreen 用例实际运行并通过，但这不等价于完整 WSI/图形矩阵或其他 GPU/驱动的验证。
