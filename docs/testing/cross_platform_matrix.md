# 跨平台测试矩阵与实机验证计划

状态：2026-11-22 起执行。本文件列出所有构建组合与测试场景、每个组合在哪里验证（GitHub CI 或实机），以及实机上的步骤、测试内容和方法。结果记录在文末「执行记录」，每次执行追加一节。

## 1. 访问约定（脱敏）

- 通过 SSH 管理的实机有两台：一台 macOS（Apple Silicon，arm64），一台 Windows 11（x86-64，带独立 GPU）；W9 另在 Windows 11 ARM64 本机直接执行，不使用以下 SSH 约定。账号、口令和地址只保存在执行者本机的环境变量里：macOS 用 `MACOS_USERNAME`、`MACOS_KEY`，Windows 用 `WINDOWS_USERNAME`、`WINDOWS_KEY`、`WINDOWS_IP`。本仓库、日志和提交信息中不得出现它们的值。
- 连接通过 SSH 口令认证（`sshpass -e`，口令经 `SSHPASS` 环境变量传入，不出现在命令行参数中）。所有远程输出在显示前把用户名和地址替换为 `<user>`、`<windows-ip>`。
- Windows 主机访问 GitHub 超时，所以源码用 `git archive HEAD` 打包后经 `scp` 复制过去（解压到 `E:\break`）。macOS 主机可以访问 GitHub，直接 `git fetch` 后对齐到 `origin/master`。
- 远程命令：macOS 用 zsh；Windows 用 PowerShell 的 `-EncodedCommand`（UTF-16LE + base64），避免引号转义问题。长时间构建在远程后台运行，日志写到 macOS 的 `/tmp/break-mac-*.log`、Windows 的 `E:\break-logs\*.log`。

## 2. 组合矩阵

维度：操作系统 × CPU 架构 × 编译器 × 构建类型 × RHI 后端 × 窗口/平台层 × 检测工具（sanitizer）× 可选特性（crypto、snowflake/QUIC、Redis、fuzz）。下表每行是一个实际验证的组合；“CI”列给出 `.github/workflows/ci.yml` 中的作业名，“实机”列说明是否在实机上复现。

| # | OS / 架构 | 编译器 | 构建类型 | RHI / 平台层 | 检测 / 特性 | CI 作业 | 实机 |
|---|---|---|---|---|---|---|---|
| L1 | Linux x86-64 | Clang + LLD | Release + IPO | OpenGL，headless | — | lane-headless-linux-clang | 开发机（Fedora，Wayland） |
| L2 | Linux x86-64 | GCC | Debug | OpenGL，headless | ASan + UBSan，fuzz smoke | lane-headless-linux-gcc-asan | 开发机 |
| L3 | Linux x86-64 | GCC | Debug | OpenGL，headless | TSan | lane-headless-linux-gcc-tsan | 开发机（聚焦测试） |
| L4 | Linux x86-64 | Clang-18 | Debug | — | libFuzzer + ASan/UBSan | lane-libfuzzer-linux-clang | — |
| L5 | Linux x86-64 | GCC | Debug | OpenGL / Vulkan | Redis 原生提供者 | lane-rule-engine-redis（Linux） | — |
| L6 | Linux arm64（QEMU） | GCC 交叉 | Debug | OpenGL | crypto，275 项选择 | lane-cross-aarch64-linux | macOS 主机 arm64 原生对照（§4.3） |
| L7 | Linux x86-64 | GCC / Clang | Debug | Wayland + OpenGL | — | wayland-gl、lane-gpu-runtime-linux-gl | 开发机（真实 Wayland 桌面） |
| L8 | Linux x86-64 | GCC / Clang | Debug | Wayland + Vulkan（lavapipe） | 校验层 | lane-native-surface-wayland、lane-gpu-runtime-linux-vk、lane-validation-linux-vk | 开发机（真实 GPU） |
| L9 | Linux x86-64 | Clang | RelWithDebInfo | Wayland + Vulkan | 基准 | lane-benchmark-linux-vk | — |
| L10 | Linux（Steam Deck） | — | — | Vulkan 真实 GPU | 基准 | lane-benchmark-steam-deck-vk（需 `ENABLE_GPU_LANES`，默认不运行） | 无设备，见 §5 |
| M1 | macOS arm64 | Apple Clang | Debug | Metal | crypto | lane-gpu-runtime-macos-metal | macOS 主机（§4.1） |
| M2 | macOS arm64 | Apple Clang | Debug | Cocoa + MoltenVK | — | lane-native-surface-cocoa | macOS 主机（§4.2，需 Vulkan SDK） |
| M3 | macOS arm64 | Apple Clang | Debug | — | Redis 原生提供者 | lane-rule-engine-redis（macOS） | — |
| M4 | iOS 模拟器 | Xcode | — | Metal | 仅构建 | ios-metal-build | macOS 主机（完整 Xcode，iOS Simulator 27.1 SDK） |
| W1 | Windows x86-64 | MSVC（cl） | Debug | headless（无 Vulkan） | `/W4 /WX`，fuzz smoke | lane-headless-windows-msvc | Windows 主机（§4.4） |
| W2 | Windows x86-64 | Clang | Debug | Vulkan，headless | — | lane-headless-windows-clang | Windows 主机（§4.5） |
| W3 | Windows x86-64 | Clang | Debug | headless | ASan | lane-headless-windows-asan | Windows 主机（§4.5） |
| W4 | Windows x86-64 | MinGW GCC | Debug | headless | fuzz smoke | lane-headless-windows-mingw | Windows 主机，便携 WinLibs GCC（§4.5） |
| W5 | Windows x86-64 | Clang | Debug | Win32 原生窗口 + Vulkan | — | lane-native-surface-win32 | Windows 主机（§4.6） |
| W6 | Windows x86-64 | Clang | Release | D3D12（WARP 软件实现） | Debug layer | windows-d3d12.yml | Windows 主机（§4.6） |
| W7 | Windows x86-64 | Clang | Release | D3D12 真实 GPU | — | lane-gpu-runtime-windows-d3d12（需 `ENABLE_GPU_LANES`，默认不运行） | Windows 主机真实 GPU（§4.6），CI 不覆盖，只能实机 |
| W8 | Linux + Proton | — | — | D3D12 → vkd3d | — | lane-proton、proton-d3d12.yml | — |
| W9 | Windows arm64 | MSVC（cl，HostARM64 原生） | Debug | headless（无 Vulkan） | `/W4 /WX`，fuzz smoke | 无（CI 尚无 arm64 Windows runner） | Windows ARM64 本机（§4.7） |
| X1 | 任意 | — | — | — | 无源码依赖的干净检出 | clean-room | — |

## 3. 场景清单

每个组合都运行 ctest 的 headless 选择（`-LE "graphics|fuzz|gpu|audio_device"`，W1 不排除 fuzz）。下列场景必须出现在至少一个组合的结果中，实机执行时逐项核对：

1. **构建**：全部目标编译、链接无警告（MSVC `/W4 /WX`、GCC/Clang `-Wall -Wextra`）。
2. **确定性**：`test_physics_replay` 与 `test_animation` 的金标准哈希（物理 3 组、动画混合 3 帧、两骨骼 IK 64 目标）在 x86-64、arm64、MSVC、Clang、GCC 上相同；`test_physics_determinism_contract` 通过。
3. **网络与安全**：cell 交接、分区、负载分配、跨进程 UDP link（真实回环套接字）、密钥轮换、崩溃恢复、可见性与路由；`test_break_crypto`、`test_break_integrity`、`test_break_authority`、`test_break_replay_window`。
4. **运行时总线**：`test_runtime_bus`（含并发发布与退订）、`test_core_app_voice`（设备事件经总线送达、worker 不被慢订阅者阻塞）。
5. **平台层**：窗口模式、触摸（Win32、Wayland）、手柄反馈、平台配置与空指针安全。
6. **渲染**：RHI 选择、错误契约、帧生命周期、黄金图像对照（OpenGL 与 Vulkan/Metal/D3D12）。需要窗口或 GPU 的测试只在 W5/W6/W7、M1/M2、L7/L8 上运行。
7. **编辑器**：i18n、字体、插件、shell、Lua、远程会话。
8. **崩溃与更新**：符号化、聚类、HTTP 上传、更新清单签名、断点续传、A/B 激活。

## 4. 实机步骤

### 4.1 macOS：Metal（M1）

1. `cd ~/break && git fetch origin && git reset --hard origin/master`（该检出只用于验证，不在其中开发）。
2. `PATH=$HOME/tools/cmake/bin:$HOME/tools/ninja/bin:$PATH`，`DEVELOPER_DIR=/Applications/Xcode.app/Contents/Developer`，`SDKROOT=$(xcrun --show-sdk-path)`（`metal` 着色器编译器只在完整 Xcode 中）。配置：`cmake -S engine -B build-m1-metal -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=$(xcrun -f clang) -DCMAKE_CXX_COMPILER=$(xcrun -f clang++) -DOPENSSL_ROOT_DIR=~/ossl-4.0.1-install -DENGINE_RHI_BACKEND=metal`，然后 `cmake --build build-m1-metal --parallel 8`。
3. `ctest --test-dir build-metal -LE "graphics|fuzz|gpu|audio_device" -j8 --output-on-failure`。
4. 单独运行带 GPU 的 Metal 测试：`ctest --test-dir build-metal -L "graphics|gpu" --output-on-failure`（实机有 GPU，CI 的 macOS runner 也有）。
5. 核对：失败数为 0；`test_animation`、`test_physics_replay` 的金标准用例为 OK。

### 4.2 macOS：Cocoa + MoltenVK（M2）

1. 主机已有 `~/VulkanSDK`（1.4.357）。设 `S=~/VulkanSDK/macOS`，配置新目录：`cmake -S engine -B build-m2-cocoa-vk -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=ON -DVulkan_LIBRARY=$S/lib/libvulkan.1.dylib -DVulkan_INCLUDE_DIR=$S/include -DSHADERC_LIB=$S/lib/libshaderc_shared.dylib -DSHADERC_INCLUDE_DIR=$S/include`。`Vulkan_LIBRARY` 必须是 loader（`libvulkan`），不能是 `libMoltenVK.dylib`，否则缺少 `VK_KHR_portability_enumeration`（执行记录问题 3）。
2. 运行测试前设置 `DYLD_LIBRARY_PATH=$S/lib`、`VK_ICD_FILENAMES=$S/share/vulkan/icd.d/MoltenVK_icd.json`，并保持 Ninja 在 `PATH` 中（若干契约测试会配置嵌套工程）。
3. 运行 headless 选择、`-R '^(test_platform_config|test_platform_null_safety|test_platform_cocoa_runtime)$'`，以及 `-L "graphics|gpu"`。

### 4.3 arm64 原生对照（L6 的补充）

CI 的 arm64 是 QEMU 用户态模拟。macOS 主机是真实的 arm64 CPU，§4.1 中 `test_physics_replay`、`test_animation` 的金标准结果即为 arm64 原生证据（macOS libm 与 glibc 不同，正好检验这些测试不依赖平台数学库）。

### 4.4 Windows：MSVC（W1）

1. 在开发机执行 `git archive --format=tar.gz -o break-src.tar.gz HEAD`，经 `scp` 复制到 Windows 主机的 `E:\`，解压到 `E:\break`（先删除旧目录）。
2. 在 `vcvars64.bat`（Visual Studio 18 Community）环境中，配置命令与 CI 完全相同：`cmake -S engine -B build-msvc -G Ninja -DCMAKE_C_COMPILER=cl -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=OFF -DENGINE_ENABLE_IPO=OFF -DENGINE_BUILD_FUZZ_SMOKE=ON`。
3. `cmake --build build-msvc --parallel 24`，再构建 fuzz 目标（列表同 CI）。
4. `ctest --test-dir build-msvc -LE "graphics|gpu|audio_device" --output-on-failure`，设置 `ENGINE_LOCKED_DEPS_ALLOW_ABSENT=1`。
5. 核对：没有 `warning C` 被当作错误（重点是 C4701，`41703704` 与 `4c61b7c1` 的 CI 曾因此失败，`093d0336` 修复）；失败数为 0。

### 4.5 Windows：Clang、Clang ASan、MinGW（W2–W4）

- W2：`cmake -S engine -B build-clang -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=ON`（需要 Vulkan SDK，按 `engine/tools/fetch_vulkan_sdk_windows.cmake`）。
- W3：同 W2，加 `-DCMAKE_C_FLAGS="-fsanitize=address -fno-omit-frame-pointer"`（C++ 同），测试前把 ASan 运行库 DLL 复制到测试目录（同 CI 步骤）。
- W4：主机没有安装 MinGW-w64，也无法访问 GitHub。在开发机下载 WinLibs 发布的 `winlibs-x86_64-posix-seh-gcc-16.2.0-mingw-w64ucrt-14.0.0-r3.zip`，核对其 SHA-256 与同一发布附带的 `.sha256` 文件一致后，复制到 Windows 主机解压（`F:\winlibs\mingw64`），只在构建脚本的 `PATH` 中加入，不修改系统环境。配置命令与 CI 相同：`-DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=OFF -DENGINE_ENABLE_IPO=OFF -DENGINE_BUILD_FUZZ_SMOKE=ON`，并构建同样的 11 个 fuzz 目标。
- 经 SSH 启动的进程在 session 0，且随 SSH 连接结束而终止。实机上用计划任务运行：`New-ScheduledTaskPrincipal -LogonType Interactive` 使任务进入已登录的桌面会话（session 1），构建脚本 `win-build.cmd <name>` 从 `E:\break-args\<name>.txt` 读取配置参数（cmd 会在 `=` 处拆分命令行参数，所以参数放在文件中）。
- 每个组合都运行 headless ctest 选择，核对失败数为 0。

### 4.5.1 iOS 模拟器（M4）

macOS 主机：`DEVELOPER_DIR=/Applications/Xcode.app/Contents/Developer`，`cmake -S engine -B build-m4-ios -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphonesimulator -DENGINE_RHI_BACKEND=metal -DENGINE_BUILD_TESTS=OFF -DBREAK_ENABLE_CRYPTO=OFF`，然后 `xcodebuild -project build-m4-ios/PureCEngine.xcodeproj -scheme engine_demo -destination 'generic/platform=iOS Simulator' build`。只验证构建，与 CI 一致。

### 4.6 Windows：Win32 窗口、D3D12 WARP 与真实 GPU（W5–W7）

- W5：`-DENGINE_VULKAN=ON` 的 Clang 构建，运行 `test_platform_win32_runtime`、`test_platform_config`、`test_platform_null_safety` 和 Win32 原生窗口测试。
- W6：按 `windows-d3d12.yml`：先 `cmake -P engine/tools/fetch_d3d12_agility_sdk.cmake`，把 Windows SDK 的 `dxc.exe` 加入 PATH，`-DENGINE_RHI_BACKEND=d3d12` 的 Release 构建，强制 WARP 运行 D3D12 测试。
- W7：同 W6，但使用真实 GPU（不强制 WARP），运行 `-L "graphics|gpu"` 的 D3D12 测试和 `test_rhi_golden_parity`。CI 的这个作业需要自托管 GPU runner，默认不运行，所以实机是唯一的验证途径。
- 注意：这些测试需要交互式桌面会话。经 SSH 启动的进程在服务会话（session 0）中，可能无法创建窗口或访问 GPU。若出现这种情况，记录为“需在 Windows 主机的桌面会话中执行”，并在该主机上按本节命令手动运行。

### 4.7 Windows：ARM64 原生（W9）

主机为 Windows 11 ARM64（Snapdragon X Elite 级），Visual Studio 18 Community 带 HostARM64
原生 MSVC 工具链，无需 x64 模拟交叉。配置命令与 W1（§4.4）相同，只是先调 `vcvarsall.bat
arm64`（不是 `vcvars64.bat`），Ninja 用 VS 自带的
`Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe`：

以下命令从仓库根目录执行。`<python-dir>` 是 ARM64 CPython 的安装目录；测试工程的
configure 需要 `python3`，本机用 uv 安装 CPython 3.13 ARM64。`OPENSSL_PREFIX` 可换成其他
用户可写的 OpenSSL 前缀：

```cmd
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat" arm64
set "OPENSSL_PREFIX=%CD%\build-openssl\slpro"
set "PATH=%OPENSSL_PREFIX%\bin;<python-dir>;C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja;%PATH%"
set ENGINE_LOCKED_DEPS_ALLOW_ABSENT=1
cmake -S engine -B build-arm64 -G Ninja -DCMAKE_C_COMPILER=cl -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=OFF -DENGINE_ENABLE_IPO=OFF -DENGINE_BUILD_FUZZ_SMOKE=ON -DBREAK_ENABLE_CRYPTO=ON "-DOPENSSL_ROOT_DIR=%OPENSSL_PREFIX%"
cmake --build build-arm64 --parallel
ctest --test-dir build-arm64 -LE "graphics|gpu|audio_device" --output-on-failure
```

构建与 CTest 必须在同一个已初始化 MSVC 的 cmd 会话中执行，因为嵌套契约还要使用其
`INCLUDE`、`LIB`、`PATH` 和编译器；只让最外层 configure 找到 `cl.exe` 不够。Visual Studio
自动更新期间可能暂时移除工具链，更新后旧缓存里的版本化编译器绝对路径也会失效；若报
`cl.exe is not a full path to an existing compiler tool`，确认更新结束后用 `cmake --fresh`
重新配置（本机从 14.51 升到 14.52 后以此恢复），不要继续复用旧编译器缓存。

OpenSSL 必须是 ARM64 构建（`find_package(OpenSSL)` 在 MSVC 分支按 `lib/VC/arm64/<CRT>`
布局探测，CMake 3.27+ 起支持该后缀；x64 安装包对 ARM64 构建不可见）。可用
ShiningLight 的 `Win64ARMOpenSSL` 安装器（winget id `ShiningLight.OpenSSL.Dev`）。机器级
安装需要 UAC；非提权会话可对 MSI 执行 `msiexec /a`（`TARGETDIR` 用带末尾 `\` 的绝对
路径）取出内嵌 Inno 安装程序，再以 `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART
/CURRENTUSER /DIR="<prefix>"` 做每用户安装。此方式直接运行安装程序而不提权，不把
`/a` 误解为会生成可用文件树。安装后的 `<prefix>\bin`（含 `libcrypto-4-arm64.dll`）须在
运行测试前加入 `PATH`。其余筛选与核对项同 §4.4。

## 5. 无法在实机覆盖的组合

| 组合 | 原因 | 现有证据 |
|---|---|---|
| L10 Steam Deck | 没有设备 | 无；CI 作业需要自托管 runner |
| W8 Proton | 需要 Linux + Steam Proton 环境 | CI 的 lane-proton |
| L4、L5、M3 | 与实机无关的工具链特性 | CI |
| W1/W2/W6 的剪贴板用例 | 主机上的 ToDesk 占用剪贴板 | CI；需在主机上退出 ToDesk 后手动执行（执行记录问题 1） |

## 6. 执行记录

（每次执行追加：日期、源码提交、组合编号、命令、结果、失败项与处理。）

### 2026-11-22，源码 `093d0336`

| 组合 | 主机 | 结果 | 说明 |
|---|---|---|---|
| M1 Metal | macOS 26.7.1，Apple M2（arm64） | headless 418/418，graphics/gpu 6/6 | 金标准：`test_physics_replay` 3 组、`test_animation` 混合与 IK 均 OK，即 arm64 原生 + macOS libm 与 x86-64 glibc 的哈希一致 |
| M2 Cocoa + MoltenVK | 同上 | headless 421/421，graphics/gpu 6/6（含 `test_vulkan`），`test_platform_cocoa_runtime` 等 3/3 | 见下文问题 2、3 |
| W1 MSVC | Windows 11（10.0.26300），Ryzen 9 7945HX，VS 18 Community | 构建通过（`/W4 /WX`，含 11 个 fuzz 目标）；423/424 | C4701 修复在实机上确认；唯一失败见问题 1 |
| W2/W5 Clang + Vulkan | 同上，LLVM 22.1.6 | headless 411/412；graphics/gpu 7/7（`test_vulkan`、`test_core_app_gpu_vulkan`、`rhi_swapchain_bench` 等，真实 GPU） | 唯一失败见问题 1 |
| W6/W7 D3D12 | 同上，Agility SDK 1.619.6（nupkg 与 DLL 的 SHA-512 与 `agility_sdk_lock.txt` 一致） | headless 415/416；graphics/gpu 10/10（设备、交换链、管线、着色器、DXR、UI canvas、WARP 运行时，真实 GPU） | CI 的真实 GPU 作业默认不运行，这是 W7 的首份实机证据；唯一失败见问题 1 |
| W3 Clang ASan | 同上，OpenGL，`ASAN_OPTIONS=detect_leaks=0` | headless 409/410，无 AddressSanitizer 报告 | 唯一失败见问题 1 |
| W4 MinGW | Windows 主机，WinLibs GCC 16.2.0（UCRT，posix-seh） | 构建与 11 个 fuzz 目标 0 警告；headless 427/428（含 fuzz smoke） | 源码 `4d849f88`；唯一失败见问题 1 |
| M4 iOS 模拟器 | macOS 主机，Xcode，iOS Simulator 27.1 SDK | `engine_demo` 构建成功（`** BUILD SUCCEEDED **`） | 源码 `4d849f88`；命令与 CI 的 ios-metal-build 相同 |

问题与处理：

1. **`test_platform_win32_runtime` 的 `clipboard_read_bounds_unterminated_unicode_text` 在 Windows 主机上失败（OpenClipboard failed）**。在桌面会话（session 1）中用独立脚本连续尝试 100 次 `OpenClipboard`，全部失败，`GetOpenClipboardWindow` 也取不到持有者。主机上运行着 ToDesk，它同步远程剪贴板时会占用剪贴板。这是主机环境问题，不是代码缺陷：其余 25 例通过，CI 的 Windows 作业中该用例通过。处理：不停止 ToDesk（会断开远程连接）。需要在 Windows 主机上退出 ToDesk 后，在桌面会话中手动执行 `ctest --test-dir build-msvc -R test_platform_win32_runtime --output-on-failure`，以及 build-clang、build-d3d12 中的同一测试。
2. **macOS 主机上 Xcode 工具链链接 `c++` 失败，`metal` 编译器只在完整 Xcode 中**。已有的 `build-metal` 缓存使用 `xcode-select` 指向的命令行工具，链接时报 `library 'c++' not found`。处理：设置 `DEVELOPER_DIR=/Applications/Xcode.app/Contents/Developer` 和 `SDKROOT=$(xcrun --show-sdk-path)`，编译器取 `xcrun -f clang`，在新目录 `build-m1-metal` 中配置。三个 target contract 测试（crypto、update、crash）在没有 `SDKROOT` 时报 `library 'System' not found`，设置后 13/13 通过。
3. **M2 中 `test_vulkan` 报 `VK_KHR_portability_enumeration` 不可用，这是代码缺陷，已修复**。CI 的 Cocoa 作业把 `Vulkan_LIBRARY` 指向 `libMoltenVK.dylib`，即不经 Vulkan loader 直接链接驱动。这个扩展由 loader 提供，用来让 loader 枚举 portability 驱动；直接链接 MoltenVK 时既没有它，也不需要它。但 `vk_init` 把它当作必需扩展，于是 Vulkan 初始化失败。CI 不运行 `graphics` 标签的测试，所以一直没有暴露。修复：新增 `platform_vk_resolve_instance_extensions`（`engine/src/platform/platform_vk_surface.h`），可选扩展缺失时把它移除，并同时清除 `VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR`（不启用扩展却设置这个位，`vkCreateInstance` 会失败）；其余扩展仍为必需。测试 `test_platform_vk_instance_extensions`（5 例，纯逻辑，所有平台运行）。实机红绿：同一个直接链接 MoltenVK 的构建，修复前 `test_vulkan` 失败，修复后通过，graphics/gpu 6/6。经 loader 链接（`libvulkan.1.dylib` + `VK_ICD_FILENAMES`）的方式在修复前后都能通过。
4. **CI：`093d0336` 的 Linux + Clang/LLD 作业失败于 `Docker login for 'ghcr.io' failed`**，发生在任何构建步骤之前，属于基础设施问题；同一 run 的其余 23 个作业成功，其中包括此前因 C4701 失败的 Windows + MSVC。当前令牌没有重跑或手动触发工作流的权限，下一次推送会重新运行该作业。

### CI 复核（2026-11-22）

`4d849f88` 的主 CI run 44979952499 全部作业成功，包括此前因 ghcr.io 登录失败的 Linux + Clang/LLD（Release）作业，以及 Windows + MSVC。arm64 QEMU 作业 275/275 通过，其中 `blending_matches_the_cross_architecture_golden_hashes` 与 `two_bone_ik_matches_the_cross_platform_golden_hash` 均为 OK。因此动画混合与两骨骼 IK 的金标准哈希在 x86-64（GCC、Clang、MSVC、MinGW）、arm64 Linux（QEMU）与 arm64 macOS（实机）上一致。


### W9：Windows ARM64 本机，源码 `728f700f`（2026-11-22）

- **验证范围**：仅 `origin/master`；其他远程分支未构建或测试。主机为 Windows 11
  26100 ARM64、Snapdragon X Elite X1E78100；工具链为 VS 18.12.1 / MSVC 14.52.37025
  （HostARM64 原生 `cl.exe`）、CMake 4.5.0-rc2、OpenSSL 4.1.0 ARM64、CPython 3.13
  ARM64。Ninja Debug、OpenGL/headless、`ENGINE_VULKAN=OFF`、`BREAK_ENABLE_CRYPTO=ON`。
- **构建**：`cmake --fresh` 全量构建与 11 个 fuzz 目标成功。日志记录 6 条既有
  D9025（`/w` 覆盖 `/W4`、`/EHs-`/`/EHc-` 覆盖 `/EHs`/`/EHc`）选项覆盖警告，不写成
  “零警告”；没有编译或链接错误。
- **环境处理**：最初缺少 ARM64 Python/OpenSSL，按 §4.7 用 uv 和每用户 Inno 安装补齐。
  无 `vcvarsall` 环境的 CTest 会让嵌套 configure 找不到 MSVC 环境，必须构建与测试
  同会话。验证期间 VS 自动更新暂时移除 14.51 工具链，更新到 14.52 后旧缓存的编译器
  绝对路径失效，`--fresh` 重新配置后恢复；这些是环境处理，不计为产品修复。
- **缺陷修复**：① `test_rhi_backend_selection` 的 metal/d3d12 fail-closed 分支复用旧
  构建目录，会让上次中断的缓存掩盖预期选择器诊断；现在与成功分支一样先清理。
  ② `core_app` target/nested/nm/compat 多层契约只传编译器、未传外层 generator，导致
  Ninja 外层误选默认 Visual Studio；现在全链路传 `NESTED_CMAKE_GENERATOR`，实际 configure
  使用 `-G`，并断言缓存值、清理 target 嵌套目录。③ 直接 `cl` 链接的
  `update_link_check.exe` 没有 manifest，名称中的 `update` 触发 Windows 安装器检测，
  CMake 启动报 `permission denied`；同一二进制只改名为 `archive_link_check.exe` 即成功，
  契约因此改名，更新产品逻辑不变。④ `test_async_loader` 的 burst 用例自身启动 8 个
  I/O worker，在 `-j8`、`-j4` 全量中均因其他测试争用而超过既有 5 秒等待预算，单跑
  1.00 秒即通过；现在该 CTest 设为 `RUN_SERIAL`，17 项功能断言和等待预算均不变。
  ⑤ `CMAKE_NM` 原先到 crypto 契约前才探测，fresh 首次 configure 会漏掉前面的
  `test_release_config_contract`，第二次 configure 才由缓存补出；现在在任何 NM 门控
  注册之前探测，避免首轮少测一项。
- **聚焦复测**：`test_platform_win32_runtime` 26/26；`test_rhi_backend_selection` 通过；
  `test_core_app_ctest_config_contract` 1/1；`test_break_update_target_contract` 连续
  2/2。MSVC 下 `test_core_app_target_contract`、`test_core_app_nm_missing`、
  `test_core_app_nm_unsupported` 按既有 NM 能力合同跳过，不再于 skip 前误配失败。
- **最终全量**：fresh 首次 configure 即选择完整的 428 项，`-j4` 运行 headless，结果
  **422 PASS + 6 个既有 SKIP + 0 FAIL**，耗时 443.81 秒。跳过项为 D3D12 依赖闸门、
  三个 core_app target/NM 用例、悬空检出属性和离线网络用例；`test_async_loader`
  在 `RUN_SERIAL` 下 0.90 秒通过，fresh 首轮注册的 `test_release_config_contract`
  0.56 秒通过。
- **覆盖边界**：本机未安装 Vulkan SDK，本记录不宣称 Vulkan、GPU、native surface 或
  present 证据；仅运行 fuzz smoke/语料用例，不运行覆盖率引导的长时 fuzz。


### 2026-11-22 framework 总线接入的矩阵补充

- §3 的“运行时总线”场景新增 `test_framework_runtime_bus`：9 个 C++20 行为用例，覆盖真实 IO notice ABI、所有权、失败重试、畸形消息、背压和并发发布/Tick。默认 `empty` 仍不链接运行时；`BREAK_FRAMEWORK_ENABLE_RUNTIME=ON` 才生成 `common_runtime`。
- L6 的 arm64 显式构建清单与 QEMU CTest 选择各新增该目标，选择数由上文的 275 项变为 **276 项**。本机没有 arm64 交叉 C++ 编译器，本次不提前写成 arm64 通过，须以 L6 实际作业收据确认。
- L1/L2/L3、W1–W6、M1/M2 的完整构建会自动包含新目标；Windows 的测试链接把数学库限制在 UNIX 分支，避免请求不存在的 `m.lib`。各平台的实际结果仍以本次对应作业或实机记录为准。
- 根 `test_framework_runtime_build_contract` 已在 Unix Makefiles 与 **Ninja Multi-Config 1.13** 各通过 1/1；每次均检查 default、显式引擎测试 OFF、未定义引擎测试开关、显式 ON 四个子树。该契约实际配置和构建目标，并用 CMake File API 核对目标与链接片段，不是源码文本匹配。

### 2026-11-22 framework 总线的 Linux 全量记录

- 源码：`aa89d48f`（已 rebase 到当时远端 `bdb9aaa4`）。标准 Fedora Wayland Vulkan **453/453**、OpenGL **451/451**，均零失败、4 项平台条件跳过。
- ASan+UBSan 非图形 **438/438**，零失败、4 项条件跳过；fuzz **14/14**。TSan 的 framework bus、runtime bus/io、async loader、mipmap stream、hotreload **6/6**，无诊断。
- 这些结果覆盖 L1/L2/L3 的本地实现与 L7/L8 的标准构建回归，不替代 L6、Windows 或 macOS 的实际收据。arm64 的 276 项选择与各远端作业结果待实际运行后追加。

### 2026-11-22 framework 总线的远端执行记录

- 首批源码 `77878229`：CI run `45016241068` **24 成功 + 3 条件跳过 + 0 失败**；windows-d3d12 run `45016241029`、QUIC run `45016241045` 成功。L6 的 arm64 作业 `137189044127` 为 **276/276**，新 C++ 测试在 QEMU 下实际通过；W1 的 MSVC 作业 `137189044139` 构建新测试可执行文件并通过 headless 套件。
- M1 实机 Metal headless **422/422**、graphics/gpu **6/6**；M2 实机 MoltenVK headless **425/425**、graphics/gpu **6/6**，各 4 项条件跳过。新测试在两个构建中均实际运行，macOS 根构建契约 **1/1**（四个子树）。
- Proton run `45017384077` 成功，日志中的上游 artifact run-id 为 `45016241029`。device/pipeline 均按无 GPU 约定返回 77 跳过，只记录兼容通道成功，不写成 GPU 或原生 D3D12 通过。
- 后续同步 `c8990472`：根契约在 Makefiles 与 Ninja Multi-Config 各 1/1，网络与框架交集 3/3。最终收据文档提交的工作流结果继续追加。

### 2026-11-22 core_app crash-context：focused 证据与待执行矩阵

本节只汇总 Task 1–3 已执行证据，不表示 Task 4 的全量或远端验收已经完成。`core_app` 捕获运行时默认 OFF，只有显式 `--crash-context DIR` 才安装处理器并写本地 spool；`BREAK_ENABLE_CRASH=OFF` 时选项明确 unavailable。没有上传接线，Windows install stub 与非 Linux full-process 均不声称捕获成功。

| 验证组 | 当前实际结果 | 范围/限制 |
|---|---|---|
| focused CTest | **7/7 PASS，0 FAIL** | diagnostics、target、nested、crash_context、独立 crash build OFF、lifecycle_load_unload、runtime |
| diagnostics 可执行测试 | **7/7 PASS** | 严格 blob schema、逐字段零值负例、真实记录验证器与错误码 |
| compat/NM/config | **3 PASS + 3 expected SKIP + 0 FAIL** | compat、`nm_symbol_missing`、ctest config 通过；`nm_missing`、`nm_unsupported`、`nm_symbol_missing_unsupported` 按 NM 能力合同跳过 |

原生 Linux/LD_PRELOAD full-process 的真实进程结果：

| 场景 | 严格断言 |
|---|---|
| 第 2 帧 SIGABRT | 唯一 `CORE_APP_TEST_ABORT_ON_FRAME=2` 标记、真实 `Subprocess aborted`、BCR `signo: 00000006`；最后完整快照为 `backend=record`, `gpu=none`, `live=false`, `tick=1`, `seen=0`, `dropped=0`, `keys=1`, `pads=0`, `touches=0`, `gestures=0`, `touch_status=0`, `haptic_status=0` |
| `runtime_running` 前 initial SIGABRT | `backend=record`, `gpu=pending`, `live=false`, `tick=0`, `keys=0`，其余计数全部 0；没有已转发的 `runtime_running` |
| 正常成功 / 运行时失败 stop | 原退出码保持 0 / 2；sigaction 总计均为 10；pending 均为 0；失败仍报告 `runtime returned FAILED` |

七个零计数字段都逐一以真实非零记录验证 contract exit 5。初始 `gpu=pending keys=0` 合法，错误 gpu/keys 返回 5。上述 GPU 字段是 record 快照，不是 Vulkan/OpenGL 设备或画面证据。

| 强制 sanitizer/preload 场景 | 直接脚本结果 | 证据解释 |
|---|---:|---|
| ASan=TRUE，runtime preload 为空 | 77 | 工作目录和进程创建前明确 UNVERIFIED/skip |
| TSan=TRUE，runtime preload 为空 | 77 | 同上 |
| UBSan=TRUE，runtime preload 为空 | 0 | 实际执行 SIGABRT、initial、成功 stop、运行时失败 stop 四类用例 |
| `FAULT_SUPPORTED=FALSE` / 非 Linux 无原生 preload | 77 | 明确 native LD_PRELOAD unavailable，不记作捕获通过 |

当前完整执行的是非 sanitizer 原生 Linux 构建；没有运行 ASan/TSan 插桩后的 full-process 序列。Windows 的 `break_crash_install` 仍返回 false，macOS 及其他非 Linux 平台没有真实 `core_app` 崩溃记录证据。

**尚待 Task 4 Step 3/4 执行**：完整默认 Wayland+Vulkan 套件、OpenGL 最终降级/画面对照套件、ASan/UBSan 非图形与 fuzz、相关 TSan、root/default 构建契约、可用 Windows/macOS/arm64 通道及远端 CI。此处没有这些项目的预写成功计数或 run-id。
