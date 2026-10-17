# break

[![CI](https://github.com/konyka/break/actions/workflows/ci.yml/badge.svg)](https://github.com/konyka/break/actions/workflows/ci.yml)
[![Rollback drill](https://github.com/konyka/break/actions/workflows/rollback-drill.yml/badge.svg)](https://github.com/konyka/break/actions/workflows/rollback-drill.yml)

CI lanes: headless (linux clang/gcc±sanitizers, windows clang±asan) /
native-surface (wayland, win32, cocoa) / GPU-runtime (linux vk lavapipe, macOS Metal, Windows D3D12) /
validation (KHRONOS_validation + D3D12 debug) / benchmark (receipt artifacts) / proton (参考，周跑)。
证据收据: 每个 lane 上传 `evidence-receipt-*` artifact，schema 见 docs/rhi_benchmark_receipt_schema.md。

Pure C11 3D rendering engine with a separate C++11 application framework.

## Quick Start

```bash
cmake -S engine -B engine/build-verify-x11-gl -DCMAKE_BUILD_TYPE=Debug
cmake --build engine/build-verify-x11-gl
ctest --test-dir engine/build-verify-x11-gl -LE graphics --output-on-failure
```

The engine requires CMake 3.20 or newer. An X11 OpenGL build also needs X11,
Xrandr, OpenGL, and Threads development packages. FreeType is optional, but is
needed for the hinted font path and CJK TTC support.

`test_vulkan` exercises the Vulkan backend path. Run the full graphics integration
suite from a Vulkan build:

```bash
cmake -S engine -B engine/build-verify-x11-vk -DENGINE_VULKAN=ON
cmake --build engine/build-verify-x11-vk
ctest --test-dir engine/build-verify-x11-vk -L graphics --output-on-failure
```

Release builds enable IPO/LTO for the `engine` static library when the active
toolchain supports it. The Linux Clang CI configuration selects `lld`; disable
IPO with `-DENGINE_ENABLE_IPO=OFF` when the platform linker does not support it.

### RHI 后端（迁移期）

RHI 后端编译为独立静态库（`engine_rhi_opengl` / `engine_rhi_vulkan` / `engine_rhi_d3d12` / `engine_rhi_headless`），最终可执行文件链接 `engine` + 恰好一个后端库（`engine_link_rhi_backend(<target>)`）。后端选择：`-DENGINE_RHI_BACKEND=auto|opengl|vulkan|d3d12`（`ENGINE_VULKAN` option 兼容保留；`d3d12` 仅 Windows 可选）。证据基线与等级见 `docs/rhi_backend_evidence.md`。

| 平台 | 可用后端 |
|---|---|
| Linux / Windows / Steam | OpenGL、Vulkan |
| Windows / Steam Windows | 原生 D3D12（GPU_RUNTIME 已验证，构建：`-DENGINE_RHI_BACKEND=d3d12`，依赖与收据见 `docs/Build_Guide.md` 与 `docs/rhi_backend_evidence.md`） |
| macOS | 原生 Metal（BENCHMARK_COMPARABLE，M2 真机收据：600 帧 50.05 fps vs MoltenVK 49.57，比值 1.010；CI `lane-gpu-runtime-macos-metal` lane）、Vulkan（MoltenVK 基线） |
| iOS | 原生 Metal（COMPILED，CI `ios-metal-build` lane，compile only，无真机收据） |

## Documentation

- Build and platform matrix: `docs/Build_Guide.md`
- myui integration and Break RHI backend: `docs/myui_integration.md`
- Native ECharts-inspired chart widget: `docs/myui_chart.md`
- myui now shares one RHI surface across logical windows and supports IME, cursor,
  non-blocking clipboard transfer, and OpenGL/Vulkan on X11 and Wayland; see
  `docs/myui_integration.md` for the platform matrix.
- Implementation status: `docs/Implementation_Status.md`
- Performance roadmap: `docs/Round11_Performance_Plan.md`
- Rule-engine architecture/design, benchmark, and conformance: `docs/Rule_Engine_Architecture.md`,
  `docs/Rule_Engine_Design.md`, `docs/Rule_Engine_Benchmark.md`, and
  `docs/rule_engine_conformance.yml`
