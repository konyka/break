# break

[![CI](https://github.com/konyka/break/actions/workflows/ci.yml/badge.svg)](https://github.com/konyka/break/actions/workflows/ci.yml)

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
