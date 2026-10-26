# break

[![CI](https://github.com/konyka/break/actions/workflows/ci.yml/badge.svg)](https://github.com/konyka/break/actions/workflows/ci.yml)
[![Rollback drill](https://github.com/konyka/break/actions/workflows/rollback-drill.yml/badge.svg)](https://github.com/konyka/break/actions/workflows/rollback-drill.yml)

CI lanes: headless (linux clang/gcc±sanitizers, windows clang±asan) /
native-surface (wayland, win32, cocoa) / GPU-runtime (linux vk lavapipe, macOS Metal, Windows D3D12 — self-hosted gated, hosted WARP floor 在 windows-d3d12.yml workflow) /
validation (KHRONOS_validation + D3D12 debug) / benchmark (receipt artifacts) / proton (参考，周跑)。
证据收据: 每个 lane 上传 `evidence-receipt-*` artifact，schema 见 docs/rhi_benchmark_receipt_schema.md。

Pure C11 3D rendering engine with a separate C++11 application framework.

## Quick Start

```bash
cmake -S engine -B engine/build -DCMAKE_BUILD_TYPE=Debug
cmake --build engine/build
ctest --test-dir engine/build -LE graphics --output-on-failure
```

**默认图形后端是 Vulkan（Linux / Windows）。** 配置阶段需要 Vulkan 加载器/头文件和 shaderc（例如 `libvulkan-dev libshaderc-dev`）；缺失时 `auto` 会打印警告并降级到 OpenGL，不会静默。明确要 OpenGL（最后降级方案 / 渲染对比基准）用 `-DENGINE_RHI_BACKEND=opengl`；明确要求 Vulkan、缺依赖就报错用 `-DENGINE_RHI_BACKEND=vulkan`。旧开关 `-DENGINE_VULKAN=OFF` 仍表示 OpenGL。

The engine requires CMake 3.20 or newer. The default (Vulkan) build needs the
Vulkan loader and headers plus shaderc; an X11 OpenGL build
(`-DENGINE_RHI_BACKEND=opengl`) needs X11,
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

### RHI 后端（计划 F 收尾态，2026-10-17）

RHI 后端编译为独立静态库（`engine_rhi_vulkan` / `engine_rhi_metal` / `engine_rhi_d3d12`；`engine_rhi_opengl` **长期保留**——最后一级降级方案 + 渲染效果对比基准（显式 fallback、白名单钉死，无移除计划；Windows/Linux/steam-linux 的 `fallback_chain` 末位）；headless 测试链 `engine_rhi_headless`，全入口 fail-closed）。最终可执行文件链接 `engine` + 恰好一个后端库（`engine_link_rhi_backend(<target>)`）。后端选择：`-DENGINE_RHI_BACKEND=auto|opengl|vulkan|d3d12`（`metal` 仅 Apple；`ENGINE_VULKAN` option 兼容保留）。证据基线与等级见 `docs/rhi_backend_evidence.md`，CI 六类 lane 见 `.github/workflows/ci.yml`（每 lane 上传 `evidence-receipt-*` 收据 artifact）。

| 平台 | 后端 | 证据等级 | 收据 |
|---|---|---|---|
| Windows | D3D12（fallback Vulkan） | GPU_RUNTIME + BENCHMARK_COMPARABLE（本机真 GPU 全栈收据；CI WARP floor 为 GPU_RUNTIME 下限） | 本机 `docs/receipts/rhi_receipt_windows_d3d12_planf.json`（vs 同机 Vulkan 基线 122%）；CI `windows-d3d12.yml` + `lane-gpu-runtime-windows-d3d12` |
| Linux / Steam Deck | Vulkan | GPU_RUNTIME（CI lavapipe 软渲染 + 本机真 GPU）；BENCHMARK_COMPARABLE（本机真 GPU 收据） | CI `lane-gpu-runtime-linux-vk` / `lane-benchmark-linux-vk`（lavapipe 收据如实标注软渲染）；本机 `build-vk/rhi_receipt_local.json`；Steam Deck 真机 lane `lane-benchmark-steam-deck-vk`（`ENABLE_GPU_LANES` 门控） |
| macOS | Metal（原生） | BENCHMARK_COMPARABLE（M2 真机：600 帧 50.05 fps vs MoltenVK 49.57，比值 1.010）；Vulkan(MoltenVK) GPU_RUNTIME 并行基线 | `docs/rhi_backend_evidence.md` 真机收据；CI `lane-gpu-runtime-macos-metal` / `lane-native-surface-cocoa` |
| iOS | Metal | COMPILED（模拟器 compile only，无真机） | CI `ios-metal-build` lane |
| Android | Vulkan | COMPILED（host-injected `ANativeWindow`，无 runtime 收据） | 源码审查记录（`docs/rhi_backend_evidence.md`） |
| Proton (Wine/vkd3d) | Vulkan（兼容参考） | compat-verified（不计入 Windows 原生证据） | `proton-d3d12.yml` / `lane-proton`（steamrt sniper 钉 digest，周跑） |
| OHOS (HarmonyOS) | — | UNAVAILABLE（fail-closed） | 契约测试 `test_platform_compat_harmonyos` |
| OpenGL（Windows / Linux） | 长期保留：最后降级方案 + 对比基准 | GPU_RUNTIME（Linux X11 CI 软渲染） | CI `lane-gpu-runtime-linux-gl` |

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
