# break

Pure C/C11 3D render framework and engine playground.

## Quick Start

```bash
cd engine
cmake -S . -B build-verify-x11-gl -DCMAKE_BUILD_TYPE=Debug
cmake --build build-verify-x11-gl
ctest --test-dir build-verify-x11-gl -LE graphics --output-on-failure
```

`test_vulkan` exercises the Vulkan backend path. Run the full graphics integration
suite from a Vulkan build:

```bash
cmake -S engine -B engine/build-verify-x11-vk -DENGINE_VULKAN=ON
cmake --build engine/build-verify-x11-vk
ctest --test-dir engine/build-verify-x11-vk -L graphics --output-on-failure
```

Release builds enable IPO/LTO for the `engine` static library when the active
toolchain supports it. Disable it with `-DENGINE_ENABLE_IPO=OFF` if a platform
linker does not support interprocedural optimization.

## Documentation

- Build and platform matrix: `docs/Build_Guide.md`
- Implementation status: `docs/Implementation_Status.md`
- Performance roadmap: `docs/Round11_Performance_Plan.md`
