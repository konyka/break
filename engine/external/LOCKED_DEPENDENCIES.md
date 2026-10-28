# 锁定依赖清单（LOCKED_DEPENDENCIES.md）

机器可校验源：`locked_dependencies.json`（契约测试 `test_locked_dependencies` 强制字段完整、
禁止 "latest"、对 vendored 文件验 sha256）。升级任何依赖 = 改 JSON + 重算 sha256 + 更新本文件 + 全 CI 绿。

## 钉版原则

1. 禁止任何 release 路径使用 "latest" 或未钉版本包（apt/brew 默认包均在禁止之列）。
2. 版本区间仅允许用于编译器/CMake 的最低版本地板（`>=x.y`），并附 CI 实际使用的钉版值。
3. vendored 依赖（`engine/external/VulkanSDK/` = 1.4.357.0）以文件 sha256 为准；多文件的 vendored 源码
   （如 `meshopt_c/`）用可选字段 `verify_extra: [{path, sha256}]` 列出其余文件，契约测试逐个校验。
4. 缺失 SDK 的平台在 CI/台账中标记 UNAVAILABLE，不得伪造证据。

## 条目说明（与 JSON 一一对应）

| name | version | purpose | 备注 |
|---|---|---|---|
| cmake | >=3.25,<4.0（CI 钉 ubuntu-24.04 apt cmake=3.28.*） | build-only | root CMakeLists.txt 要求 3.25，engine 3.20 → 统一地板 3.25 |
| clang | >=17.0 | build-only | gate 默认编译器；CI ubuntu-24.04 钉 clang-18 |
| gcc | >=12.0 | build-only | sanitizer lane；CI 钉 gcc-13 |
| msvc | >=19.38 | build-only | /std:c11 与 C11 atomics 需要；VK gate 用 VS 18 2026 generator |
| vulkan-sdk | 1.4.357.0 | build-only | vendored；Linux CI 下载同版 tarball 并验 sha256 |
| shaderc | sdk-1.4.357.0-bundled | runtime-shipped | 引擎运行时编译 GLSL→SPIR-V（target env Vulkan 1.2 / SPIR-V 1.5） |
| vulkan-validation-layers | sdk-1.4.357.0-bundled | test-only | VK_LAYER_KHRONOS_validation，validation lane 使用 |
| android-ndk | 27.2.12479018 (r27c) | build-only | android/native_window.h 查找（engine/CMakeLists.txt） |
| xcode | >=15.4 | system-provided | Metal 工具链（xcrun metal）与 iOS SDK 来源 |
| windows-sdk | 10.0.26100.0 | system-provided | D3D12/DXGI 头与 import lib |
| d3d12-agility-sdk | 1.619.6 | runtime-shipped | D3D12Core.dll 随 Windows 发布包分发；`engine/tools/fetch_d3d12_agility_sdk.cmake` 拉取，`engine/external/d3d12/agility_sdk_lock.txt` 以 SHA512 复核 nupkg 与 D3D12Core.dll |
| dxc | 1.9.0.5399 | build-only | SDK 同捆；HLSL→DXIL gate |
| glslang | 16.4.0 | build-only | SDK 同捆 glslang.exe；替代 unpinned 的 glslangValidator |
| meshoptimizer-c-port | 1.3 (pure C port) | runtime-shipped | vendored `engine/external/meshopt_c/`：meshoptimizer v1.3（commit 9e1f07b1）减面器 + 顶点缓存优化的纯 C11 移植，MIT；`simplifier.c` 为 `verify_path`，其余源文件与 LICENSE 由 `verify_extra` 逐个验 sha256；与上游逐位一致由 `test_meshopt_c` 保证（见该目录 README.md） |

## 已知注记

- shaderc 的 `find_library(SHADERC_LIB ...)` 曾不读 `VULKAN_SDK` 环境变量，已由
  commit 2af8cce3 修复（`engine/CMakeLists.txt` 中 `HINTS "$ENV{VULKAN_SDK}/Lib"`）。
- macOS 侧另有 pin（不在本机可校验范围）：glslc shaderc v2026.4（sha256 73f9f514…）、
  spirv-cross 1.4.363.0（sha256 242d2c69…）、cmake 3.28.6（sha256 e992f382…）、
  ninja 1.12.1（sha256 89a28744…），证据见计划 C
  `.superpowers/sdd/2026-10-14-rhi-plan-c-metal/task-10-report.md`（glslc/spirv-cross）
  与同目录 `progress.md`（cmake/ninja 完整 sha256）；spirv-cross 为
  Metal 工具链内部组件，未单列为 JSON 条目。
