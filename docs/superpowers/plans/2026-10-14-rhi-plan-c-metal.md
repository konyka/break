# 原生 Metal RHI 后端（计划 C）实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 为 PureCEngine RHI 新增原生 Metal 后端（`engine_rhi_metal`，MTLDevice/MTLCommandQueue/CAMetalLayer），使 macOS/iOS 脱离 MoltenVK，并产出逐级证据（COMPILED → 真机 GPU_RUNTIME）。

**Architecture:** 遵循设计规格 §4.1 的「编译期单后端、独立静态库」模型：`engine_rhi_metal` 导出与 `engine_rhi_vulkan`/`engine_rhi_opengl` 完全相同的一组 `rhi_*` 符号，最终可执行文件经 `engine_link_rhi_backend(<target>)` 恰好链接一个后端库。后端本体是单一 Objective-C 翻译单元 `engine/src/rhi/rhi_metal.m`（手动引用计数），共享 `rhi_backend_internal.h` 的 slot 表/生命周期 wrapper；shader 走「离线 GLSL→SPIR-V（glslc）→MSL（SPIRV-Cross CLI）→metallib（xcrun metal）」管线 + 内容-hash manifest 的零第三方运行时加载模型。

**Tech Stack:** C11 + Objective-C（手动引用计数，`-fno-objc-arc`）、Metal/QuartzCore/Foundation framework、CMake + Ninja/Xcode、glslc（brew shaderc）、SPIRV-Cross（pin 版本）、`xcrun metal/metallib`、CTest（`SKIP_RETURN_CODE 77` 约定、labels `headless/platform_contract/graphics/platform_runtime`）。

**前置条件（硬门）：** 计划 A（`2026-10-14-rhi-plan-a-evidence-abstraction-buildsplit.md`）已完成：后端独立静态库 `engine_rhi_vulkan`/`engine_rhi_opengl`/`engine_rhi_headless` 已落地、`engine_link_rhi_backend(<target>)` helper 存在、`rhi.c` 不再 unity-include、`rhi_native_vulkan.h` 已迁出 Vulkan 形状类型、`RHINativeHandleType` 已含 `RHI_NATIVE_HANDLE_METAL=2`、`test_rhi_backend_internal_contract.cmake` 已重写为「各后端库所有权断言」。开始本计划前验证：

```bash
git log --oneline -5
grep -n "engine_rhi_vulkan\|engine_link_rhi_backend" engine/CMakeLists.txt   # 必须有命中
grep -n "RHI_NATIVE_HANDLE_METAL" engine/src/rhi/rhi.h                        # 必须有命中（计划 A 交付）
```

任一检查失败 → 停止，先完成计划 A，不得在本计划中补做计划 A 的工作。

## Global Constraints

- **语言混编**：引擎主体 C11（`CMAKE_C_STANDARD 11`，engine/CMakeLists.txt:4-6）；Metal 后端是唯一例外，用 Objective-C 单 TU（`.m`）。**决策：不用 ARC**——Obj-C 对象指针必须能存进 C 结构体（`RHIDevice.backend_data` 与 slot 表 `void *ptr`，rhi_backend_internal.h:24-49），ARC 的 `__strong` 限定符不能出现在非 Obj-C 编译的 struct 布局里；且 `window_cocoa.m` 已建立手动引用计数先例（engine/CMakeLists.txt:1034-1038 的注释与 `-fno-objc-arc`）。`rhi_metal.m` 用 per-file `COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-fno-objc-arc"`（系统框架头无法满足 `-pedantic`），**引擎其余文件 -Werror 纪律不变**。
- **-Werror**：新增 C 测试/工具代码在 clang/GNU 下 `-Wall -Wextra -Werror -pedantic` 全绿（engine/CMakeLists.txt:105-115）。
- **TDD**：每个 Task 先写失败测试 → 验证失败（给出命令与预期输出）→ 最小实现 → 验证通过 → 提交。每个 Task 独立可测、独立提交。
- **冻结文件（任何步骤不得修改/删除/移动）**：`.scratch-vkprobe/`、`engine/profile_trace.json`、`.tmp/`、仓库根 `d3d12_shader_gate.hlsl`/`d3d12_shader_gate.dxil`、`.env`、SSH 私钥。
- **证据等级纪律**（规格 §2）：`docs/rhi_backend_evidence.md` 中 **MoltenVK 行与原生 Metal 行严格分列**；CI lane 命名 `macos-vulkan` vs `macos-metal` 不得混用；**iOS/macOS 模拟器结果只计入 compile/lifecycle 等级，绝不构成 GPU-runtime 证据**；编译成功不得记为 GPU-runtime；缺失 SDK/硬件只能标 UNAVAILABLE，不得伪造证据。
- **不新增 RHIResult 枚举值**（规格 §4.2）：错误语义用现有 `RHI_RESULT_*`（rhi.h:338-349）+ 契约测试固定。
- **上下文压缩交接**：执行会话上下文约 70% 时先生成压缩交接，至少含：当前 Task 与 checkbox 状态；已红/已绿测试清单；已修改与未提交文件；commit/branch/remote 状态；macOS×Metal 证据等级；未决风险；下一步精确命令；冻结文件清单复述。
- **执行环境**：除 Task 1/2 的纯 CMake 脚本断言可在任意平台验证外，本计划绝大部分步骤**只能在 macOS + Xcode 环境执行**。每个 Task 顶部标注 `**执行环境**`；环境缺失时该 Task 标记 UNAVAILABLE 并停止其后步骤，跳过的 Task 在最终汇报中逐条列出。
- **行尾**：`engine/src/rhi/*.c`、`engine/CMakeLists.txt` 现为 CRLF；新增 `.m`/`.h` 文件跟随所在目录惯例（`engine/src/rhi/` 用 CRLF），编辑既有文件时保持其行尾不变。

## 通用命令

```bash
# macOS 构建目录（Metal 后端）
cmake -S engine -B build-macos-metal -G Ninja \
  -DENGINE_RHI_BACKEND=metal -DCMAKE_BUILD_TYPE=Debug -DMYUI_PAL=cocoa
cmake --build build-macos-metal --parallel
ctest --test-dir build-macos-metal --output-on-failure            # 全量
ctest --test-dir build-macos-metal -LE graphics --output-on-failure  # headless 子集
# 纯脚本契约测试（任意平台可跑，含本机 Windows）
ctest --test-dir <任一已配置构建目录> -R "test_rhi_backend_selection|test_rhi_backend_internal_contract" --output-on-failure
# 对照：MoltenVK 现状 lane（不可动的基线）
cmake -S engine -B build-macos-vk -G Ninja -DENGINE_RHI_BACKEND=vulkan -DMYUI_PAL=cocoa
```

## File Structure

新增：
- `engine/src/rhi/rhi_metal.m` — Metal 后端全部 `rhi_*` 实现（单 Obj-C TU；内部 C struct `MetalBackend` 持有全部 Obj-C 句柄）。
- `engine/src/rhi/rhi_metal_format.h` — 纯 C11、零 Metal 依赖的映射/判定逻辑（`static inline`），供 `rhi_metal.m` 与 headless 测试共同包含（与 `rhi.h` 中 `rhi_sample_count_bit`/`rhi_push_range_fits` 的既定惯例一致）。
- `engine/tests/test_rhi_metal_format_mapping.c` — 映射表 headless 契约测试（任意平台可跑）。
- `engine/tests/test_rhi_metal_device_contract.c` — 设备/能力/device-lost 契约测试（macOS，graphics label）。
- `engine/tests/test_rhi_metal_frame_lifecycle.c` — 帧生命周期/drawable/resize 契约测试（macOS，graphics label）。
- `engine/tests/test_rhi_metal_resources.c` — buffer/texture/sampler/pipeline/FBO/compute/readback roundtrip（macOS，graphics label）。
- `engine/tools/compile_metal_shaders.sh` — 离线 shader 管线（glslc → spirv-cross → xcrun metal/metallib + manifest 生成）。
- `engine/tools/gen_metal_shader_manifest.c` — manifest 生成器（构建期运行，产出 `rhi_metal_shader_manifest.c`）。
- `docs/rhi_metal_notes.md` — Metal 后端语义备忘（帧/错误/绑定映射的固定契约）。

修改：
- `engine/CMakeLists.txt` — selector 放开（:129-148）、macOS 块（:1026-1054）、iOS 块（:1055-1084）、`engine_rhi_metal` target、`engine_link_rhi_backend` metal 分支、测试注册。
- `engine/tests/test_rhi_backend_selection.cmake` — metal 语义重写（APPLE 放行 / 非 APPLE UNAVAILABLE）。
- `engine/tests/test_rhi_backend_internal_contract.cmake` — 新增 `engine_rhi_metal` 所有权断言（计划 A 重写版的扩展点）。
- `.github/workflows/ci.yml` — 新增 `macos-metal` 与 `ios-metal-build` lane（在 `macos-vulkan` :443 之后）。
- `docs/rhi_backend_evidence.md`（计划 A 骨架）— 追加 macos-metal / ios-metal 行。
- `docs/rhi_metal_d3d12_feature_matrix.md`（计划 A 骨架）— 填充 Metal 列。
- `docs/Build_Guide.md`、`README.md` — metal 构建入口与后端矩阵。

---

## Phase 1 — 构建系统接入（TDD）

### Task 1: selector 放开 APPLE 平台 `ENGINE_RHI_BACKEND=metal`

**执行环境：** 任意平台（纯 CMake 脚本 + configure 行为；非 APPLE 分支的断言在本机 Windows 即可验证；APPLE 分支的 configure 验证需 macOS，缺失时仅完成脚本层并用注释标 UNAVAILABLE）。

**Files:**
- Modify: `engine/CMakeLists.txt:34-36`（STRINGS 加 metal）、`:129-148`（selector 逻辑）
- Modify: `engine/tests/test_rhi_backend_selection.cmake:29-106`（预期重写）
- Test: 同上脚本即测试（`cmake -P` 契约测试，注册于 engine/CMakeLists.txt:2052-2057）

**Interfaces:**
- Consumes: 现有 selector 机制 `ENGINE_RHI_BACKEND` / `ENGINE_RHI_BACKEND_EFFECTIVE`（engine/CMakeLists.txt:34-36, 141-148）。
- Produces:
  - `ENGINE_RHI_BACKEND=metal`：APPLE（macos/ios）→ `ENGINE_RHI_BACKEND_EFFECTIVE=metal`（CACHE INTERNAL）；非 APPLE → `message(FATAL_ERROR ...)`，消息恰含子串 `metal backend is UNAVAILABLE on this platform`。
  - 非法值（仍含 d3d12）的 FATAL 消息更新为恰含 `ENGINE_RHI_BACKEND must be auto, opengl, vulkan, or metal`。
  - `metal` 选择不再 FORCE 改写 `ENGINE_VULKAN`；`ENGINE_RHI_BACKEND_EFFECTIVE=metal` 时定义 `ENGINE_RHI_BACKEND_METAL=1`（engine 库 PUBLIC 定义机制沿用 :328-330 的 `ENGINE_RHI_BACKEND_${..._UPPER}` 拼接，metal 分支自动生效）。

- [ ] **Step 1: 改测试预期（红）**——编辑 `engine/tests/test_rhi_backend_selection.cmake`：

  1. `:35` 的 required_text 由 `"ENGINE_RHI_BACKEND must be auto, opengl, or vulkan"` 改为 `"ENGINE_RHI_BACKEND must be auto, opengl, vulkan, or metal"`。
  2. 删除 `:46-50` 的 forbidden-backend 循环中 `"metal"` 项（保留 `"d3d12"`）。
  3. `:78-91` 的 metal 段整体替换为平台分支断言：

```cmake
# metal: APPLE 平台必须配置成功且 EFFECTIVE=metal；其他平台必须 FATAL_ERROR
# 且消息恰含 UNAVAILABLE（fail-closed，不得静默回退到其他后端）。
if(APPLE)
    assert_configure_success("metal" "metal")
else()
    execute_process(
        COMMAND "${CMAKE_BIN}" -S "${ENGINE_SOURCE_DIR}" -B "${TEST_BINARY_DIR}/metal"
            ${configure_overrides}
            -DENGINE_RHI_BACKEND=metal -DENGINE_BUILD_TESTS=OFF -DMYUI_PAL=dummy
        RESULT_VARIABLE metal_result
        OUTPUT_VARIABLE metal_output
        ERROR_VARIABLE metal_error)
    if(metal_result EQUAL 0)
        message(FATAL_ERROR "metal selector unexpectedly configured on non-APPLE platform")
    endif()
    if(NOT "${metal_output}${metal_error}" MATCHES
           "metal backend is UNAVAILABLE on this platform")
        message(FATAL_ERROR "metal selector failed for an unexpected reason")
    endif()
endif()
```

  4. `:93-106` 的 d3d12 段消息匹配由旧串改为 `"ENGINE_RHI_BACKEND must be auto, opengl, vulkan, or metal"`。

- [ ] **Step 2: 验证失败**

```bash
# 任一已配置构建目录均可；没有就先配置一个：
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DENGINE_BUILD_TESTS=OFF -DMYUI_PAL=dummy
# TEST_BINARY_DIR 必须落在构建目录下（与注册处 :2056 一致）；
# 严禁指向仓库根 .tmp/（冻结目录）。
cmake -DENGINE_CMAKE=engine/CMakeLists.txt -DENGINE_SOURCE_DIR=engine \
      -DTEST_BINARY_DIR="$PWD/build-gate/rhi-selector-contract" \
      -P engine/tests/test_rhi_backend_selection.cmake
```

预期：FAIL —— required_text 检查先报 `RHI backend selection contract missing: ENGINE_RHI_BACKEND must be auto, opengl, vulkan, or metal`（旧选择器消息不含该串）。

- [ ] **Step 3: 最小实现**——编辑 `engine/CMakeLists.txt`：

  1. `:36` 改为 `set_property(CACHE ENGINE_RHI_BACKEND PROPERTY STRINGS auto opengl vulkan metal)`。
  2. `:130-135` 合法性检查改为：

```cmake
if(NOT ENGINE_RHI_BACKEND STREQUAL "auto" AND
   NOT ENGINE_RHI_BACKEND STREQUAL "opengl" AND
   NOT ENGINE_RHI_BACKEND STREQUAL "vulkan" AND
   NOT ENGINE_RHI_BACKEND STREQUAL "metal")
    message(FATAL_ERROR
        "ENGINE_RHI_BACKEND must be auto, opengl, vulkan, or metal")
endif()
```

  3. 在 `:136-140` 的分支链中插入 metal 合法性检查（`vulkan`/`opengl` 分支保持不变）：

```cmake
if(ENGINE_RHI_BACKEND STREQUAL "metal" AND NOT APPLE)
    message(FATAL_ERROR
        "metal backend is UNAVAILABLE on this platform (native Metal requires macOS/iOS)")
endif()
```

  4. `:141-147` 的 EFFECTIVE 推导重构为「先算局部量、最后一次性写 cache」，避免重配置时残留旧值：

```cmake
if(ENGINE_RHI_BACKEND STREQUAL "metal")
    set(_rhi_backend_effective "metal")
    # metal 不改写 ENGINE_VULKAN（保持 OFF），兼容层语义仅服务 gl/vk。
elseif(ENGINE_VULKAN)
    set(_rhi_backend_effective "vulkan")
else()
    set(_rhi_backend_effective "opengl")
endif()
set(ENGINE_RHI_BACKEND_EFFECTIVE "${_rhi_backend_effective}" CACHE INTERNAL
    "Resolved RHI backend for this build" FORCE)
```

- [ ] **Step 4: 验证通过**

```bash
cmake -DENGINE_CMAKE=engine/CMakeLists.txt -DENGINE_SOURCE_DIR=engine \
      -DTEST_BINARY_DIR=<build>/rhi-selector-contract -P engine/tests/test_rhi_backend_selection.cmake
```

预期：非 APPLE 平台 PASS（auto/opengl 配置成功、metal FATAL 且消息匹配、d3d12 FATAL 且消息匹配）。macOS 上另需 `cmake -S engine -B build-macos-metal-sel -DENGINE_RHI_BACKEND=metal -DENGINE_BUILD_TESTS=OFF -DMYUI_PAL=cocoa` 配置成功且 CMakeCache 含 `ENGINE_RHI_BACKEND_EFFECTIVE:INTERNAL=metal`；**无 macOS 时此半句标 UNAVAILABLE**。

- [ ] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/tests/test_rhi_backend_selection.cmake
git status --short   # 确认无冻结文件、无无关改动
git commit -m "rhi: admit ENGINE_RHI_BACKEND=metal selector on APPLE (fail-closed elsewhere)"
```

### Task 2: `engine_rhi_metal` 静态库骨架 + 内部契约测试扩展

**执行环境：** 脚本断言任意平台可验证；`engine_rhi_metal` 真实编译需 macOS（缺失时编译验证标 UNAVAILABLE，脚本层照常）。

**Files:**
- Create: `engine/src/rhi/rhi_metal.m`（骨架：全部 `rhi_*` 入口 fail-closed——此时还不是真实现，Task 3 起逐族填充；骨架存在的目的是让链接与所有权断言可测）
- Modify: `engine/CMakeLists.txt`（macOS 块 :1026-1054 重写为后端分支；新增 `engine_rhi_metal` target；`engine_link_rhi_backend` 增 metal 分支）
- Modify: `engine/tests/test_rhi_backend_internal_contract.cmake`（计划 A 重写版中扩展 metal 断言）
- Test: `test_rhi_backend_internal_contract`（注册 :2091-2103）、新增 compile-gate 脚本 `engine/tests/test_rhi_metal_ownership.cmake`

**Interfaces:**
- Consumes: 计划 A 交付的 `engine_link_rhi_backend(<target>)` helper 与 `engine_rhi_*` 库模式；`rhi_backend_internal.h` 的 slot/freelist API（:55-71）；`rhi.h` 全量公开符号（871 行，871 个声明族）。
- Produces:
  - target `engine_rhi_metal`：源恰为 `src/rhi/rhi_metal.m`；`target_compile_definitions PRIVATE ENGINE_RHI_BACKEND_METAL=1`；仅在 `ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal" AND APPLE` 时创建；链接 `"-framework Metal" "-framework QuartzCore" "-framework Foundation" "-framework Cocoa"`（Cocoa 仅 macOS 需要；iOS 分支链接 `"-framework UIKit"` 的等价物——iOS 宿主注入 CAMetalLayer，后端本体不直接依赖 UIKit，故 iOS 只链 Metal/QuartzCore/Foundation）。
  - `engine_link_rhi_backend` 的 metal 分支：`elseif(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal") target_link_libraries(${target} PRIVATE engine_rhi_metal)`。
  - macOS 块（:1026-1054）重构：`metal` 生效时**不再** `find_package(Vulkan REQUIRED)`、**不再**定义 `ENGINE_VULKAN=1`、**不再**链接 Vulkan/shaderc；`vulkan` 生效时保持现状（MoltenVK 基线不动）。`window_cocoa.m` 两种后端都编译（CAMetalLayer 创建与后端无关，:408-409）。

- [ ] **Step 1: 失败测试**——新建 `engine/tests/test_rhi_metal_ownership.cmake`（纯文本断言，任意平台可跑）：

```cmake
# engine_rhi_metal 所有权契约：metal 后端源恰被 engine_rhi_metal 拥有；
# engine 核心库不得直接包含 rhi_metal.m；helper 必须有 metal 分发分支。
if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()
file(READ "${ENGINE_CMAKE}" cmake_text)
string(REGEX REPLACE "#[^\r\n]*" "" cmake_text "${cmake_text}")
foreach(required_text
        "add_library(engine_rhi_metal STATIC"
        "src/rhi/rhi_metal.m"
        "ENGINE_RHI_BACKEND_METAL=1"
        "-framework Metal"
        "-framework QuartzCore"
        "-framework Foundation"
        "ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL \"metal\"")
    string(FIND "${cmake_text}" "${required_text}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "metal backend ownership contract missing: ${required_text}")
    endif()
endforeach()
# 反向断言：engine 库的 add_library 块内不得出现 rhi_metal.m（后端独立成库）
```

（反向断言复用 `test_rhi_backend_internal_contract.cmake:32-60` 的 `extract_cmake_command` 函数写法，提取 `add_library(engine STATIC` 块后断言不含 `rhi_metal.m`。）同时在 `test_rhi_backend_internal_contract.cmake` 的计划 A 重写版后端清单中追加 metal 行（具体修改点：其「各后端库恰好一个后端源」循环加入 `"engine_rhi_metal|src/rhi/rhi_metal.m"`，「禁止 token」列表中移除计划 A 前遗留的 `rhi_metal.c`/`ENGINE_RHI_BACKEND_METAL` 条目——计划 A 重写后该列表应已不存在，若仍存在则此处删除）。在 engine/CMakeLists.txt 注册：

```cmake
add_test(NAME test_rhi_metal_ownership
    COMMAND ${CMAKE_COMMAND}
        -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_metal_ownership.cmake)
set_tests_properties(test_rhi_metal_ownership PROPERTIES LABELS "headless;platform_contract")
```

- [ ] **Step 2: 验证失败**

```bash
cmake -DENGINE_CMAKE=engine/CMakeLists.txt -P engine/tests/test_rhi_metal_ownership.cmake
```

预期：FAIL —— `metal backend ownership contract missing: add_library(engine_rhi_metal STATIC`。

- [ ] **Step 3: 最小实现**

  1. 新建 `engine/src/rhi/rhi_metal.m` 骨架（关键约定一次到位，Task 3 起在此填充）：

```objc
/* Native Metal RHI backend. Single Objective-C TU exporting the same rhi_*
 * symbols as rhi_vk.c / rhi_gl.c. Manual reference counting (-fno-objc-arc):
 * Obj-C handles live in C structs (backend_data / slot table), matching the
 * window_cocoa.m precedent. Pure mapping logic lives in rhi_metal_format.h
 * so headless tests can exercise it without Metal headers. */
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#include <rhi/rhi.h>
#include <rhi/rhi_backend_internal.h>
#include <rhi/rhi_metal_format.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    id<MTLDevice> device;
    id<MTLCommandQueue> queue;
    CAMetalLayer *layer;          /* not owned; owned by the platform layer */
    id<MTLLibrary> library;       /* offline-compiled shader library (Task 10) */
    id<MTLSharedEvent> frame_event;
    u64 frame_counter;            /* monotonically increasing; slot = counter % 2 */
    u64 slot_signaled[2];         /* per-slot completed frame value */
    id<CAMetalDrawable> drawable; /* current acquired drawable, nil between frames */
    bool device_lost_latch;       /* sticky; mirrors rhi_vk.c device-lost semantics */
    bool suspended;               /* iOS host-driven pause: acquire returns BUSY */
    RHIFormat swapchain_format;   /* from the layer's pixelFormat */
    u32 max_push_bytes;           /* 256 staging, mirrors VK push staging */
} MetalBackend;

#define RHI_METAL_MAX_PUSH_BYTES 256u

struct RHICmdBuffer {
    MetalBackend *backend;
    id<MTLCommandBuffer> cmd;
    id<MTLRenderCommandEncoder> render_encoder;
    id<MTLComputeCommandEncoder> compute_encoder;
    id<MTLBlitCommandEncoder> blit_encoder;
    u8 push_staging[RHI_METAL_MAX_PUSH_BYTES];
    RHIPipeline bound_pipeline;
    bool render_pass_open;
};
```

骨架阶段：`rhi_device_create` 返回 NULL（`rhi_device_create_ex` 的 wrapper 在 rhi.c:50-69 会转成 `RHI_RESULT_ERROR`），其余族按 Task 3-9 填充；每个函数体在填充前一律 `LOG_ERROR("rhi_metal: <name> not implemented");` + fail-closed 返回值（指针→NULL，bool→false，句柄→RHI_HANDLE_NULL）。**不实现 `rhi_backend_*` 之外的公开符号子集——全量符号必须由本 TU 提供**（与 rhi_vk.c 导出清单一致，对照清单见 rhi_vk.c 的符号表：create :2570 / destroy :2594 / resize :2785 / frame_begin :2801 / frame_end :3219 / present :3282 / frame_index :3347 / buffer :4532 / texture :5137 / pipeline :4088 / FBO :9643-10635 / compute :3395,6475 / RT :4688-5137 / screenshot :2954 / gpu_timer :3150-3191 等）。

  2. `engine/CMakeLists.txt`：在 `engine_rhi_headless` 定义之后（计划 A 交付位置）追加：

```cmake
if(APPLE AND ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")
    enable_language(OBJC)
    add_library(engine_rhi_metal STATIC src/rhi/rhi_metal.m)
    target_include_directories(engine_rhi_metal PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)
    target_compile_definitions(engine_rhi_metal PRIVATE ENGINE_RHI_BACKEND_METAL=1)
    # 系统框架头无法满足 -Werror -pedantic；手动引用计数（见 rhi_metal.m 头注）。
    set_source_files_properties(src/rhi/rhi_metal.m PROPERTIES
        COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-fno-objc-arc")
    target_link_libraries(engine_rhi_metal PRIVATE
        "-framework Metal" "-framework QuartzCore" "-framework Foundation")
    if(ENGINE_PLATFORM STREQUAL "macos")
        target_link_libraries(engine_rhi_metal PRIVATE "-framework Cocoa")
    endif()
endif()
```

  3. `engine_link_rhi_backend`（计划 A 交付的 function 体内）追加 metal 分支：

```cmake
elseif(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")
    target_link_libraries(${target} PRIVATE engine_rhi_metal)
```

  4. macOS 块（:1026-1054）改为后端分支：`if(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")` 分支中删除 `find_package(Vulkan REQUIRED)`、`ENGINE_VULKAN=1` 定义与 `Vulkan::Vulkan ${SHADERC_LIB}` 链接（保留 window_cocoa.m、`enable_language(OBJC)`、Cocoa/QuartzCore/Metal/IOKit/CoreServices/CoreFoundation 框架）；`else()`（vulkan/MoltenVK）分支保持现状逐字不动。同时 :222-235 的 shaderc/Vulkan 发现条件由 `ENGINE_VULKAN OR ENGINE_PLATFORM STREQUAL "macos"` 收紧为 `ENGINE_VULKAN OR (ENGINE_PLATFORM STREQUAL "macos" AND NOT ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")`——metal 配置不再强制依赖 MoltenVK 工具链。

- [ ] **Step 4: 验证通过**

```bash
cmake -DENGINE_CMAKE=engine/CMakeLists.txt -P engine/tests/test_rhi_metal_ownership.cmake   # PASS（任意平台）
# macOS 上另验证（缺失标 UNAVAILABLE）：
cmake -S engine -B build-macos-metal -G Ninja -DENGINE_RHI_BACKEND=metal -DMYUI_PAL=cocoa \
  && cmake --build build-macos-metal --target engine_rhi_metal --parallel
# 预期：engine_rhi_metal.a 编译链接成功；headless 测试不引用后端符号不受影响
ctest --test-dir build-macos-metal -R "test_rhi_metal_ownership|test_rhi_backend_selection|test_rhi_backend_internal_contract" --output-on-failure
```

- [ ] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/src/rhi/rhi_metal.m \
        engine/tests/test_rhi_metal_ownership.cmake engine/tests/test_rhi_backend_internal_contract.cmake
git status --short
git commit -m "rhi: add engine_rhi_metal static library skeleton (fail-closed stubs)"
```

---

## Phase 2 — 设备、命令队列与能力

### Task 3: MTLDevice/MTLCommandQueue、能力查询与设备信息

**执行环境：** 映射逻辑 headless 部分任意平台；`test_rhi_metal_device_contract` 需 macOS 真机或 runner（graphics label + `SKIP_RETURN_CODE 77`；CI runner 无 GPU 窗口权限时 77 skip，不构成证据）。

**Files:**
- Create: `engine/src/rhi/rhi_metal_format.h`（纯 C11 映射层）
- Modify: `engine/src/rhi/rhi_metal.m`（设备族实现）
- Test: `engine/tests/test_rhi_metal_format_mapping.c`（headless，任意平台）、`engine/tests/test_rhi_metal_device_contract.c`（graphics）

**Interfaces:**
- Consumes: `struct RHIDevice`（rhi_backend_internal.h:31-49）、`rhi_init_freelist`/`rhi_alloc_slot`（:55-57）、`RHICapabilities`（rhi.h:112-124）、`RHIDeviceInfo`（rhi.h:127-135）、`rhi_sample_count_bit`（rhi.h:102-110）、`RHIResult`（rhi.h:338-349）。
- Produces（在 `rhi_metal_format.h` 中定义，供全计划消费）：

```c
#pragma once
#include <rhi/rhi.h>

/* Metal pixel-format ordinals. Deliberately NOT MTLPixelFormat constants so
 * this header stays C11 and platform-free; rhi_metal.m static-asserts each
 * ordinal against the real MTLPixelFormat value at compile time. */
typedef enum {
    RHI_METAL_FORMAT_INVALID = 0,
    RHI_METAL_FORMAT_RGBA8_UNORM,       /* MTLPixelFormatRGBA8Unorm */
    RHI_METAL_FORMAT_BGRA8_UNORM,       /* MTLPixelFormatBGRA8Unorm */
    RHI_METAL_FORMAT_RGBA16_FLOAT,      /* MTLPixelFormatRGBA16Float */
    RHI_METAL_FORMAT_RG16_FLOAT,        /* MTLPixelFormatRG16Float */
    RHI_METAL_FORMAT_R32_FLOAT,         /* MTLPixelFormatR32Float */
    RHI_METAL_FORMAT_DEPTH32_FLOAT,     /* MTLPixelFormatDepth32Float */
} RHIMetalFormat;

static inline RHIMetalFormat rhi_metal_format_from_rhi(RHIFormat f) {
    switch (f) {
        case RHI_FORMAT_R8G8B8A8_UNORM:      return RHI_METAL_FORMAT_RGBA8_UNORM;
        case RHI_FORMAT_B8G8R8A8_UNORM:      return RHI_METAL_FORMAT_BGRA8_UNORM;
        case RHI_FORMAT_R16G16B16A16_SFLOAT: return RHI_METAL_FORMAT_RGBA16_FLOAT;
        case RHI_FORMAT_R16G16_SFLOAT:       return RHI_METAL_FORMAT_RG16_FLOAT;
        case RHI_FORMAT_R32_FLOAT:           return RHI_METAL_FORMAT_R32_FLOAT;
        case RHI_FORMAT_D32_FLOAT:           return RHI_METAL_FORMAT_DEPTH32_FLOAT;
        default:                           return RHI_METAL_FORMAT_INVALID;
    }
}
/* bytes-per-pixel for readback/upload; depth formats report f32 bytes (R602
 * contract: D32 readback is 4B f32 per texel). 0 for INVALID. */
static inline u32 rhi_metal_format_bytes_per_pixel(RHIMetalFormat f) {
    switch (f) {
        case RHI_METAL_FORMAT_RGBA8_UNORM:   return 4u;
        case RHI_METAL_FORMAT_BGRA8_UNORM:   return 4u;
        case RHI_METAL_FORMAT_RGBA16_FLOAT:  return 8u;
        case RHI_METAL_FORMAT_RG16_FLOAT:    return 4u;
        case RHI_METAL_FORMAT_R32_FLOAT:     return 4u;
        case RHI_METAL_FORMAT_DEPTH32_FLOAT: return 4u;
        default:                             return 0u;
    }
}
/* Two-slot frame pacing helpers (aligned with rhi_frame_index semantics,
 * rhi.h:470-471): the slot to acquire into and the event value to wait on. */
static inline u32 rhi_metal_frame_slot(u64 frame_counter) {
    return (u32)(frame_counter % 2u);
}
static inline u64 rhi_metal_slot_wait_value(u64 frame_counter) {
    return frame_counter >= 2u ? frame_counter - 2u : 0u;
}
```

  `rhi_metal.m` 侧实现：`rhi_device_create`（`window_native` 即 `CAMetalLayer *`，window_cocoa.m:492/494 保证；iOS 经 `PlatformConfig.native_window` 注入，window_mobile.c:19-42）：
  - `MTLCreateSystemDefaultDevice()` 为 nil → 释放并返回 NULL（wrapper 报 ERROR；无 Metal 的平台在 selector 层已 fail-closed，此处是运行时兜底）。
  - `layer.device = device`；从 `layer.pixelFormat` 反推 `swapchain_format`（BGRA8Unorm→`RHI_FORMAT_B8G8R8A8_UNORM`，window_cocoa.m:409 已设）。
  - `dev->backend_data = metal_backend`；`rhi_init_freelist(dev)`；`dev->capabilities` 填充（映射表如下）；`dev->status = RHI_DEVICE_STATUS_READY`。
  - 能力映射表（写入 `docs/rhi_metal_notes.md`，并用契约测试固定）：

| RHICapabilities 字段 | Metal 来源 | 契约 |
|---|---|---|
| `backend` | 计划 A 在 `RHIBackend` 枚举追加的 `RHI_BACKEND_METAL` | 若计划 A 未追加则本 Task 追加（枚举尾部 append） |
| `color_sample_counts` | `[device supportsTextureSampleCount:{1,2,4,8}]` 逐探测 → `rhi_sample_count_bit` 位集 | 至少含 1x |
| `depth_sample_counts` | 同上 | 至少含 1x |
| `surface_sample_count` | 恒 1 | CAMetalLayer drawable 不可 MSAA；MSAA 只能经 offscreen resolve |
| `color_resolve_supported` | true | `storeActionMultisampleResolve` |
| `depth_resolve_supported` | false | fail-closed：自定义 depth resolve 不纳入本计划 |
| `scissor_supported` | true | `setScissorRect:` |
| `present_target_preserved` | false | drawable 内容不保证保留 |
| `present_damage_supported` | false | CAMetalLayer 无 damage 机制 |
| `present_buffer_age_supported` | false | 同上 |
| `feature_bits` | `[device supportsRaytracing]`（respondsToSelector 门控）→ `RHI_FEATURE_ACCELERATION_STRUCTURE \| RHI_FEATURE_RAY_QUERY`；否则 0 | `RHI_FEATURE_RAY_TRACING_PIPELINE` **永不置位**（Metal intersection-function 模型无 raygen pipeline 等价，fail-closed） |

  - `RHIDeviceInfo`：`device_name=[device.name UTF8String]`；`vendor_id=0x106B`（Apple）当 `[device supportsFamily:MTLGPUFamilyApple1]`，否则 0；`device_id=0`；`api_version=(3u<<22)`（Metal 3 baseline，macos-14/Xcode 15 提供）；`driver_version=0`。

- [ ] **Step 1: 失败测试（headless 部分）**——新建 `engine/tests/test_rhi_metal_format_mapping.c`（不 include 任何 Metal 头，任意平台编译）：

```c
#include "test_framework.h"
#include <rhi/rhi_metal_format.h>

TEST(every_color_and_depth_format_maps) {
    for (int f = RHI_FORMAT_R8G8B8A8_UNORM; f <= RHI_FORMAT_D32_FLOAT; ++f) {
        ASSERT_TRUE(rhi_metal_format_from_rhi((RHIFormat)f) != RHI_METAL_FORMAT_INVALID);
        ASSERT_TRUE(rhi_metal_format_bytes_per_pixel(
            rhi_metal_format_from_rhi((RHIFormat)f)) > 0u);
    }
}
TEST(undefined_format_fails_closed) {
    ASSERT_EQ(rhi_metal_format_from_rhi(RHI_FORMAT_UNDEFINED), RHI_METAL_FORMAT_INVALID);
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_INVALID), 0u);
}
TEST(readback_byte_contract_matches_rhi) {
    /* R587/R593/R602: RGBA8/BGRA8=4, RG16F=4, RGBA16F=8, R32F=4, D32=4 */
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_RGBA8_UNORM), 4u);
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_RGBA16_FLOAT), 8u);
    ASSERT_EQ(rhi_metal_format_bytes_per_pixel(RHI_METAL_FORMAT_DEPTH32_FLOAT), 4u);
}
TEST(frame_slot_pacing) {
    ASSERT_EQ(rhi_metal_frame_slot(0u), 0u);
    ASSERT_EQ(rhi_metal_frame_slot(1u), 1u);
    ASSERT_EQ(rhi_metal_frame_slot(2u), 0u);
    ASSERT_EQ(rhi_metal_slot_wait_value(0u), 0u);  /* first two frames never wait */
    ASSERT_EQ(rhi_metal_slot_wait_value(1u), 0u);
    ASSERT_EQ(rhi_metal_slot_wait_value(2u), 0u);  /* ==0: 未 signal 时 wait(0) 立即成立 */
    ASSERT_EQ(rhi_metal_slot_wait_value(3u), 1u);
    ASSERT_EQ(rhi_metal_slot_wait_value(5u), 3u);
}
int main(void) {
    RUN_TEST(every_color_and_depth_format_maps);
    RUN_TEST(undefined_format_fails_closed);
    RUN_TEST(readback_byte_contract_matches_rhi);
    RUN_TEST(frame_slot_pacing);
    return TEST_RESULT();
}
```

注册（engine/CMakeLists.txt 测试区）：`add_executable(test_rhi_metal_format_mapping tests/test_rhi_metal_format_mapping.c)` + include `${TEST_INCLUDE_DIRS}` + `add_test` + `LABELS "headless;platform_contract"`。

- [ ] **Step 2: 验证失败** —— `cmake --build build-gate --target test_rhi_metal_format_mapping` → 编译错误 `rhi/rhi_metal_format.h: No such file or directory`。

- [ ] **Step 3: 最小实现**——按上文 Interfaces 创建 `engine/src/rhi/rhi_metal_format.h`；在 `rhi_metal.m` 中用 `_Static_assert` 把序数钉到真实常量（`RHI_METAL_FORMAT_RGBA8_UNORM` 对应分支返回 `MTLPixelFormatRGBA8Unorm` 的转换函数 + `_Static_assert(MTLPixelFormatBGRA8Unorm != MTLPixelFormatRGBA8Unorm, ...)` 等逐条断言该 switch 无重叠/无遗漏——用 switch 返回真实枚举值，default → `MTLPixelFormatInvalid` 并 LOG_ERROR）。`rhi_device_create`/`*_ex`（经 rhi.c wrapper）、`rhi_device_destroy`（drain 后 release 全部 Obj-C 句柄）、`rhi_device_get_capabilities`（rhi.c:28-32 已通用）、`rhi_backend_get_device_info` 按上表实现。

- [ ] **Step 4: 验证通过**

```bash
cmake --build build-gate --target test_rhi_metal_format_mapping && \
ctest --test-dir build-gate -R test_rhi_metal_format_mapping --output-on-failure   # PASS（任意平台）
# macOS（缺失标 UNAVAILABLE）：
cmake --build build-macos-metal --parallel && \
ctest --test-dir build-macos-metal -R test_rhi_metal_format_mapping --output-on-failure
```

- [ ] **Step 5: 设备契约测试（graphics，TDD 红→绿）**——新建 `engine/tests/test_rhi_metal_device_contract.c`：在 `#if defined(ENGINE_RHI_BACKEND_METAL) && defined(ENGINE_PLATFORM_MACOS)` 下创建离屏 CAMetalLayer（`[CAMetalLayer layer]` + 显式 drawableSize，无需窗口——CAMetalLayer 可离屏 acquire drawable），断言：`rhi_device_create_ex` 返回非 NULL 且 `out_result==RHI_RESULT_OK`；`rhi_device_get_capabilities` 的 `color_sample_counts` 含 1x 位、`surface_sample_count==1`、`present_damage_supported==false`、`feature_bits & RHI_FEATURE_RAY_TRACING_PIPELINE` 为 0；`rhi_device_get_info` 的 `device_name` 非空；非法尺寸（w=0）经 wrapper 得 `RHI_RESULT_INVALID_ARGUMENT`；非 Metal 环境/编译期不满足时 `return 77;`。注册 `LABELS "graphics;platform_runtime" SKIP_RETURN_CODE 77`，链接 `engine` + `engine_link_rhi_backend(test_rhi_metal_device_contract)` + `-framework QuartzCore -framework Metal`，测试源自身是 `.c`——**CAMetalLayer 创建需要 Obj-C**：把 layer 创建放进 `engine/tests/metal_test_layer.m`（ARC 无所谓，测试代码；仍用 `-fno-objc-arc` 保持一致并 `retain`），向 C 测试暴露 `void *metal_test_layer_create(u32 w, u32 h)` / `void metal_test_layer_destroy(void *layer)`。macOS 上跑 `ctest -R test_rhi_metal_device_contract` 先红（stub 返回 NULL → ERROR）后绿。

- [ ] **Step 6: Commit**

```bash
git add engine/src/rhi/rhi_metal_format.h engine/src/rhi/rhi_metal.m \
        engine/tests/test_rhi_metal_format_mapping.c engine/tests/test_rhi_metal_device_contract.c \
        engine/tests/metal_test_layer.m engine/CMakeLists.txt docs/rhi_metal_notes.md
git commit -m "rhi_metal: device create/destroy, capabilities, device info + format mapping layer"
```

### Task 4: device lost 检测与 fail-closed

**执行环境：** 实现需 macOS 编译；注入式契约测试 headless 部分任意平台（`ENGINE_RHI_TEST` 钩子，rhi.h:861-864）。

**Files:**
- Modify: `engine/src/rhi/rhi_metal.m`（device lost 闩锁）
- Modify: `engine/tests/test_rhi_metal_device_contract.c`
- Modify: `docs/rhi_metal_notes.md`（错误映射表）

**Interfaces:**
- Consumes: `rhi_device_lost`/`rhi_device_idle` 语义（rhi.h:843-859）、`rhi_device_set_lifecycle_result`（rhi_backend_internal.h:71）、rhi.c 的 `rhi_result_for_device`（rhi.c:40-48）。
- Produces: Metal 错误→`RHIResult` 映射表（写入 `docs/rhi_metal_notes.md`，契约测试固定）：

| Metal 情形 | 检测点 | RHI 语义 |
|---|---|---|
| `MTLCreateSystemDefaultDevice()` nil | create | `RHI_RESULT_ERROR`（平台缺失在 selector 已 `UNAVAILABLE` fail-closed） |
| `window_native` 不是 CAMetalLayer | create | `RHI_RESULT_INVALID_ARGUMENT` |
| `nextDrawable` 重试超时（1s 截止） | acquire | `lifecycle_result = RHI_RESULT_OUT_OF_DATE`，后续 frame 调用 fail-fast |
| layer nil / drawable texture nil | acquire | `RHI_RESULT_SURFACE_LOST` |
| command buffer `status == MTLCommandBufferStatusError` | completedHandler / `rhi_device_idle` / frame_end | sticky latch → `RHI_RESULT_DEVICE_LOST`；`error.code == MTLCommandBufferErrorDeviceRemoved`（macOS 13+，respondsToSelector 门控，低版本按通用 error 同样 latch） |
| `MTLSharedEvent` 等待超时（20s，对齐 rhi.h:855 的 VK 20s 语义） | acquire/drain | `RHI_RESULT_SYNC_FAILED`；超时后置 device-lost 闩锁（对齐 VK 的 fence-unsignaled→lost 语义，rhi.h:854-858） |
| 挂起中 acquire（iOS host 暂停） | acquire | `RHI_RESULT_BUSY` |
| ray tracing API 在 `[device supportsRaytracing]==NO` | RT 族 | `RHI_RESULT_UNSUPPORTED` |

  实现要点：**Metal 没有公开的 device-lost 通知 API**（无 `MTLDeviceNotificationName` 等价物），检测完全靠：(1) 每个提交的 command buffer 挂 `addCompletedHandler:` 检查 `status`；(2) `rhi_device_idle` 内 `waitUntilCompleted` 后复查；(3) 闩锁置位后所有阻塞等待 fail-fast（对齐 VK 语义，rhi_vk.c:2454-2470 为参照）。

- [ ] **Step 1: 失败测试**——`test_rhi_metal_device_contract.c` 追加：正常路径 `rhi_device_lost(dev)==false`、`rhi_device_idle_ex(dev)==RHI_RESULT_OK`；用 `ENGINE_RHI_TEST` 的 `rhi_test_set_device_status(dev, RHI_DEVICE_STATUS_LOST)` 注入后 `rhi_frame_acquire_ex` 返回 `RHI_RESULT_DEVICE_LOST`、`rhi_present_ex` 同（该路径在 rhi.c:40-48 wrapper 层，后端无关，测试固定 wrapper 契约）。再追加后端侧断言：提交一个合法空 command buffer 后 `rhi_device_lost` 仍为 false（完成回调不得误闩）。

- [ ] **Step 2: 验证失败** —— macOS：`ctest --test-dir build-macos-metal -R test_rhi_metal_device_contract --output-on-failure` → 设备契约断言失败（`rhi_device_lost` stub 未实现 / 闩锁逻辑缺失）。无 macOS → UNAVAILABLE。

- [ ] **Step 3: 最小实现**——`rhi_device_lost`（返回 `dev->status == RHI_DEVICE_STATUS_LOST || mtl->device_lost_latch`）、`rhi_device_idle`（`waitUntilCompleted` 最后一个提交的 command buffer + completedHandler 检查；闩锁置位时同步写 `dev->status = RHI_DEVICE_STATUS_LOST`（字段在 rhi_backend_internal.h:40）并 `rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST)`（:71））；提交函数统一走 `metal_commit(dev, cmd)` helper 挂 completedHandler。

- [ ] **Step 4: 验证通过** —— 同上 ctest 全绿；headless 套件不回归：`ctest -R "test_rhi_metal|test_rhi_backend" --output-on-failure`。

- [ ] **Step 5: Commit**

```bash
git add engine/src/rhi/rhi_metal.m engine/tests/test_rhi_metal_device_contract.c docs/rhi_metal_notes.md
git commit -m "rhi_metal: sticky device-lost latch via command-buffer completion status"
```

---

## Phase 3 — swapchain / drawable 与帧生命周期

### Task 5: drawable acquire/present/resize + 帧状态机映射

**执行环境：** macOS（graphics label；无 macOS → 整个 Task UNAVAILABLE）。iOS 路径仅 build-only + 模拟器 lifecycle（Task 14 的 lane），本 Task 不产 iOS 证据。

**Files:**
- Modify: `engine/src/rhi/rhi_metal.m`（帧族：`rhi_frame_begin`/`rhi_frame_end`/`rhi_present`/`rhi_device_resize`/`rhi_frame_index`/`rhi_set_vsync`）
- Test: `engine/tests/test_rhi_metal_frame_lifecycle.c`（新建，graphics）
- Modify: `docs/rhi_metal_notes.md`

**Interfaces:**
- Consumes: rhi.c 的 frame wrapper（rhi.c:94-159：acquire=begin 别名 :117-119、end=submit 别名 :132-134、owner/busy 检查）；规格 §4.3 状态机。
- Produces（写入 `docs/rhi_metal_notes.md` 的逐项映射表，契约测试固定行为）：

| 规格 §4.3 阶段 | RHI 入口 | Metal 实现 |
|---|---|---|
| acquire | `rhi_frame_acquire_ex` → `rhi_frame_begin` | (1) 双槽 pacing：`slot = frame_counter % 2`；`frame_counter >= 2` 时 `[frame_event waitUntilSignaledValue:frame_counter-2 timeoutMS:20000]`，超时 → SYNC_FAILED + 闩锁；(2) `[layer nextDrawable]` 重试循环（1s 截止、1ms 退避，期间 pump 一个 `@autoreleasepool`），nil 超时 → `lifecycle_result=OUT_OF_DATE` + fail-fast；(3) drawable 尺寸校验：`layer.drawableSize` ≠ dev 宽高 → 采用 layer 实际尺寸并更新 dev（windowDidResize → cocoa_update_drawable_size 已维护 layer 尺寸，window_cocoa.m:339-351,355） |
| begin | 同上（acquire 内完成） | `[queue commandBuffer]`；retain 进 `RHICmdBuffer`；render encoder 延迟到首个 `rhi_cmd_begin_render_pass` 用当前 drawable texture 建 `MTLRenderPassDescriptor` |
| submit | `rhi_frame_end_ex`/`rhi_frame_submit_ex` → `rhi_frame_end` | endEncoding（若开）→ `[cmd presentDrawable:drawable]` → `[cmd encodeSignalEvent:frame_event value:frame_counter]` → `metal_commit`（挂 completedHandler）→ 释放 drawable 引用。**present 在 commit 前 attach 是 Metal 硬约束**，故 Metal 后端把 present 语义并入 frame_end |
| present | `rhi_present_ex` → `rhi_present` | 簿记 no-op：`frame_counter++`、清 damage 状态；帧 owner 校验已由 rhi.c:136-145 保证「present 只能在成功 submit 之后」 |
| resize | `rhi_device_resize_ex` → `rhi_device_resize` | 更新 `dev->width/height`；**不**写 `layer.drawableSize`（所有权在 window 层）；下次 acquire 自动采用新尺寸（对齐「swapchain 自动重建」语义） |
| drain | `rhi_device_drain_ex` → `rhi_device_idle` | 等待最后一次提交的 signal：`frame_counter >= 1` 时 `waitUntilSignaledValue:frame_counter-1 timeoutMS:20000`（0 帧时立即成功）；超时 → SYNC_FAILED + 闩锁 |
| destroy | `rhi_device_destroy_ex` → `rhi_device_destroy` | 强制 drain（实现内 idle，§4.3「destroy 前必须 drain」）后 release |

  `rhi_frame_index` 返回 `(u32)(frame_counter % 2)`（rhi.h:470-471 的双槽语义）；`rhi_set_vsync(false)` → `layer.displaySyncEnabled = NO`（macOS 10.13+），true → YES。

- [ ] **Step 1: 失败测试**——`engine/tests/test_rhi_metal_frame_lifecycle.c`（复用 Task 3 的 `metal_test_layer.m` 离屏 layer）：acquire→begin→end→present 三帧循环，每帧 `rhi_cmd_begin_render_pass` + `rhi_cmd_clear_color(0.1,0.2,0.3,1)` + `rhi_cmd_end_render_pass`；断言 `rhi_frame_index` 序列 0,1,0；`rhi_frame_end_ex`/`rhi_present_ex` 均 `RHI_RESULT_OK`；`rhi_device_resize(dev, 320, 240)` 后下一帧 acquire 成功；未 acquire 直接 `rhi_present_ex` → `RHI_RESULT_BUSY`（rhi.c:141 owner 检查）；destroy 无崩溃。（像素级断言归 Task 9 的 screenshot 用例，本 Task 只固定 frame API 序列。）SKIP 77 同 Task 3。

- [ ] **Step 2: 验证失败** —— macOS `ctest -R test_rhi_metal_frame_lifecycle` → 断言失败（frame stubs）。

- [ ] **Step 3: 最小实现** —— 按映射表实现帧族；`rhi_cmd_begin_render_pass`/`rhi_cmd_end_render_pass`/`rhi_cmd_clear_color`（clear 用 render pass 的 `loadAction=MTLLoadActionClear` + `clearColor`，首 pass 即清；pass 中再调 clear 时 flush encoder 重建）。drawable 获取重试 helper：

```objc
static id<CAMetalDrawable> metal_acquire_drawable(MetalBackend *mtl, RHIDevice *dev) {
    const u64 deadline_ms = 1000u;
    u64 waited_ms = 0u;
    for (;;) {
        @autoreleasepool {
            id<CAMetalDrawable> d = [mtl->layer nextDrawable];
            if (d != nil) return [d retain];
        }
        if (mtl->device_lost_latch) {
            rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
            return nil;
        }
        if (waited_ms >= deadline_ms) {
            rhi_device_set_lifecycle_result(dev, RHI_RESULT_OUT_OF_DATE);
            return nil;
        }
        /* 1ms backoff: usleep via nanosleep to stay C11-friendly in Obj-C TU. */
        struct timespec ts = { 0, 1000000L };
        nanosleep(&ts, NULL);
        waited_ms += 1u;
    }
}
```

- [ ] **Step 4: 验证通过** —— `ctest --test-dir build-macos-metal -R "test_rhi_metal_frame_lifecycle|test_rhi_metal_device_contract" --output-on-failure` 全绿。

- [ ] **Step 5: Commit**

```bash
git add engine/src/rhi/rhi_metal.m engine/tests/test_rhi_metal_frame_lifecycle.c \
        engine/CMakeLists.txt docs/rhi_metal_notes.md
git commit -m "rhi_metal: drawable acquire/present, two-slot MTLSharedEvent pacing, resize"
```

### Task 6: 暂停/恢复（iOS host 注入路径）+ drawable 失败注入测试

**执行环境：** 注入逻辑 headless 可测（macOS runner 即可，不依赖 GPU 像素）；iOS 模拟器 lifecycle 归 Task 14 lane。无 macOS → UNAVAILABLE。

**Files:**
- Modify: `engine/src/rhi/rhi_metal.m`（suspended 标志路径）
- Test: `engine/tests/test_rhi_metal_frame_lifecycle.c`（追加）

**Interfaces:**
- Produces: 后端内部入口 `rhi_metal_set_suspended(RHIDevice *dev, bool suspended)`（声明放 `rhi_metal_format.h`？否——它操作 `RHIDevice`，属后端私有扩展。**决策**：不新增公开头；iOS 宿主暂停语义由 window_mobile.c 的 host-injection 模型保证——宿主在 background 期间**不调用**任何 frame API（window_mobile.c 是纯注入壳，:44-50 无事件上报钩子，本计划不给它加）。后端防御性语义：暂停期间若宿主误调 acquire，经 `suspended` 标志返回 `RHI_RESULT_BUSY`；该标志仅由新增的 `ENGINE_RHI_TEST` 钩子置位（测试用），生产路径 iOS 宿主自律。**这是一个显式限制，写入 `docs/rhi_metal_notes.md`「已知边界」**。

- [ ] **Step 1: 失败测试**——测试追加：`#ifdef ENGINE_RHI_TEST` 置 suspended 后 `rhi_frame_acquire_ex` → `RHI_RESULT_BUSY`；清标志后 acquire 成功；`rhi_device_resize` 在 BUSY 期间仍成功（resize 不走 acquire）。测试注册处给 `test_rhi_metal_frame_lifecycle` 加 `target_compile_definitions PRIVATE ENGINE_RHI_TEST=1`。

- [ ] **Step 2: 验证失败** → acquire 未检查 suspended，返回 OK（红）。

- [ ] **Step 3: 最小实现**——`rhi_frame_begin` 入口检查 `mtl->suspended` → `rhi_device_set_lifecycle_result(dev, RHI_RESULT_BUSY)` + 返回 NULL（rhi.c:110-114 把 lifecycle_result 透传给 out_result）。测试钩子 `rhi_test_metal_set_suspended`（`#ifdef ENGINE_RHI_TEST` 内，rhi_metal.m 私有导出）。

- [ ] **Step 4: 验证通过** —— ctest 绿。

- [ ] **Step 5: Commit**

```bash
git add engine/src/rhi/rhi_metal.m engine/tests/test_rhi_metal_frame_lifecycle.c docs/rhi_metal_notes.md
git commit -m "rhi_metal: suspended-acquire BUSY contract (iOS host-pause defense)"
```

---

## Phase 4 — 资源与管线

### Task 7: buffer / texture / sampler / cubemap

**执行环境：** macOS（graphics）。无 macOS → UNAVAILABLE。

**Files:**
- Modify: `engine/src/rhi/rhi_metal.m`
- Test: `engine/tests/test_rhi_metal_resources.c`（新建）

**Interfaces:**
- Consumes: slot API（rhi_backend_internal.h:55-59）、`rhi_buffer_desc_validate`/`rhi_texture_desc_validate`（rhi.h:475-476，实现在 rhi_validation.c）、`rhi_metal_format_from_rhi`（Task 3）。
- Produces:
  - `rhi_buffer_create`：`MTLResourceStorageModeShared`（`initial_data != NULL` 或 `usage & RHI_BUFFER_USAGE_UNIFORM`）/ `MTLResourceStorageModePrivate`（纯 GPU：STORAGE|INDIRECT|AS_BUILD_INPUT 且无 initial_data）；`newBufferWithBytes:`/`newBufferWithLength:`。`rhi_buffer_update(_region)`：shared 直接 memcpy；private 经 blit staging（临时 shared buffer + `copyFromBuffer:toBuffer:` + 提交等待，对齐 VK staging 语义 rhi_vk.c:8909-8975）。`rhi_buffer_read`：shared 直接 memcpy；private blit 回 shared + `waitUntilCompleted`。`rhi_buffer_map/unmap`：仅 shared 合法（private → NULL + LOG_ERROR，fail-closed）。
  - `rhi_texture_create`：`MTLTextureDescriptor texture2DDescriptor`，`pixelFormat=rhi_metal_format_to_mtl(...)`，`usage = MTLTextureUsageShaderRead | MTLTextureUsageRenderTarget | MTLTextureUsageShaderWrite`（一步到位，避免后续 usage 不足重建）；初始数据经 `replaceRegion:mipmapLevel:withBytes:bytesPerRow:`（shared）或 staging blit（private）。`rhi_texture_read_pixels`：blit `copyFromTexture:...toBuffer:` → shared buffer → memcpy，字节契约按 `rhi_metal_format_bytes_per_pixel`（R587-R602，对齐 rhi.h:497-519 注释）。
  - `rhi_sampler_create`：`MTLSamplerDescriptor`，`RHIFilter`→`MTLSamplerMinMagFilter`、`RHIWrapMode`→`MTLSamplerAddressMode`（`RHI_WRAP_CLAMP_TO_EDGE`→`MTLSamplerAddressModeClampToEdge`）。
  - `rhi_cubemap_create`/`rhi_texture_array_create`：`MTLTextureTypeCube`/`MTLTextureType2DArray`；`rhi_texture_array_upload_layer`、`rhi_texture_upload_mip` 同 2D 上传路径。

- [ ] **Step 1: 失败测试**——`test_rhi_metal_resources.c`：创建 64B uniform buffer → `rhi_buffer_update` 写入 magic → `rhi_buffer_read` 逐字节相等；`RHI_FORMAT_R8G8B8A8_UNORM` 4x4 texture 上传 16 个已知像素 → `rhi_texture_read_pixels` 相等；sampler 创建/销毁往返句柄 generation 递增；cubemap 6 面 4x4 上传后 readback `4*4*4*6` 字节相等（rhi.h:513-515 的 face-major 契约）；`RHI_FORMAT_UNDEFINED` 创建 texture → `RHI_HANDLE_NULL`（fail-closed）。SKIP 77 同前。

- [ ] **Step 2: 验证失败** → stubs 返回 `RHI_HANDLE_NULL`，断言红。

- [ ] **Step 3: 最小实现** —— 按 Interfaces 实现；所有 Obj-C 对象经 `rhi_alloc_slot`/`rhi_free_slot` 管理生命周期，destroy 时 `release`。

- [ ] **Step 4: 验证通过** —— `ctest -R test_rhi_metal_resources` 绿。

- [ ] **Step 5: Commit**

```bash
git add engine/src/rhi/rhi_metal.m engine/tests/test_rhi_metal_resources.c engine/CMakeLists.txt
git commit -m "rhi_metal: buffers, textures, samplers, cubemaps with R587-R602 byte contracts"
```

### Task 8: pipeline / render pass / MRT / offscreen FBO / shadow map

**执行环境：** macOS（graphics）。

**Files:**
- Modify: `engine/src/rhi/rhi_metal.m`
- Test: `engine/tests/test_rhi_metal_resources.c`（追加 pipeline/FBO 段）

**Interfaces:**
- Consumes: `RHIPipelineDesc`（rhi.h:238-282）、`RHIOffscreenFBO`（rhi.h:708-716）、`RHIMRTFBO`（rhi.h:747-754）、`rhi_offscreen_fbo_desc_validate`（rhi.h:721-722）、Task 10 的 shader 加载（**依赖顺序调整：本 Task 的 pipeline 测试使用 Task 10 产出的最小内嵌 MSL；实施时若 Task 10 未完成，先用硬编码 `newLibraryWithSource:` 的最小顶点/片元 MSL 字符串驱动红→绿，Task 10 完成后切换到 manifest 路径——两阶段都在本 Task 的 checkbox 内明确**）。
- Produces:
  - `rhi_pipeline_create`：`MTLRenderPipelineDescriptor`；`RHIPipelineDesc` 字段逐项映射：

| RHIPipelineDesc 字段 | Metal 映射 |
|---|---|
| `vert`/`frag` | slot 中取 `id<MTLFunction>` → `vertexFunction`/`fragmentFunction` |
| `vertex_stride` + `font_vertex`/`is_instanced`/`skinned_vertex`/`no_vertex_input` | `MTLVertexDescriptor` 按布局构造（步长=vertex_stride；属性布局沿用 VK 后端的约定表，从 rhi_vk.c:4088-4338 的 pipeline 创建逻辑逐字段移植） |
| `depth_compare_lequal`/`depth_write_disable` | 配套 `MTLDepthStencilDescriptor`（`MTLCompareFunctionLessEqual`/`Less`，`isDepthWriteEnabled`）；depth state 对象缓存复用 |
| `disable_culling` | `cullMode = MTLCullModeNone / Back` |
| `alpha_blend`/`alpha_blend_color_only` | `colorAttachments[0].blendingEnabled` + rgb/alpha blend operation 拆分 |
| `wireframe` | `triangleFillMode = MTLTriangleFillModeLines` |
| `point_list` | 记录到 pipeline slot，draw 时 `MTLPrimitiveTypePoint`（R168-C） |
| `color_format` | `colorAttachments[0].pixelFormat`（swapchain 用 layer 格式；HDR FBO 用 RGBA16Float） |
| `sample_count` | `rasterSampleCount`（0→1） |
| `mrt_attachment_count`/`mrt_formats` | 逐 attachment 设 `pixelFormat`（≤ `RHI_MRT_MAX_ATTACHMENTS`=5，rhi.h:188）+ `depthAttachmentPixelFormat=Depth32Float` |
| `terrain_layout`/`water_layout`/`combined_aa_layout`/`combined_color_layout` | push 块布局选择（capability contract 字段，规格 §4.4；Task 11 消费其偏移表） |
| `is_compute` | 走 `MTLComputePipelineState` 分支（Task 9） |
| `uses_textures`/`uses_texel_buffer`/`uses_storage`/`is_shadow_depth` | 仅影响绑定表与 encoder 配置，不改 PSO 主体 |

  - FBO 族（bind 契约对齐 rhi.h:724-743, 760-769, 780-786 的 R616/R617/R618/R619）：`rhi_offscreen_fbo_bind` = 新建 render encoder，`loadAction=Clear`（color 用 caller 设置的 clear color，默认 {0.05,0.05,0.1,1.0}；depth clear 1.0）；`rhi_offscreen_fbo_bind_load` = `loadAction=Load`；`rhi_mrt_fbo_bind/_bind_load` 同理（每 attachment clear (0,0,0,0)）；`rhi_cmd_bind_shadow_map`/`rhi_cubemap_depth_fbo_bind_face` = depth-only pass clear 1.0；unbind 族 endEncoding + 恢复 viewport 到屏幕尺寸。MSAA FBO：color texture `MTLTextureType2DMultisample` + resolve texture，`storeAction=MTLStoreActionMultisampleResolve`（`color_resolve_supported==true` 的消费点）。

- [ ] **Step 1: 失败测试**——测试追加段：用最小 MSL（顶点直通 + 常量片元色）建 pipeline → offscreen FBO 64x64 RGBA8 → bind、画 3 顶点三角形、unbind → `rhi_texture_read_pixels(fbo.color_tex)` 断言中心像素为片元色；`rhi_offscreen_fbo_bind_load` 后再读，像素保留（R617 语义对偶）；MRT 2 attachment 各写不同色分别读回；shadow map bind 后 depth 已清 1.0（读回 D32 全 1.0f）。5-attachment MRT 创建成功（RHI_MRT_MAX_ATTACHMENTS）。

- [ ] **Step 2: 验证失败** → pipeline stub 红。

- [ ] **Step 3: 最小实现** —— 按映射表实现；encoder 生命周期规则写入 `docs/rhi_metal_notes.md`（同一 cmd 同时最多一个 encoder open；切换 target/类型时先 endEncoding）。

- [ ] **Step 4: 验证通过** —— `ctest -R test_rhi_metal_resources` 绿。

- [ ] **Step 5: Commit**

```bash
git add engine/src/rhi/rhi_metal.m engine/tests/test_rhi_metal_resources.c docs/rhi_metal_notes.md
git commit -m "rhi_metal: render/compute pipeline descriptors, FBO/MRT/shadow bind contracts"
```

### Task 9: compute / readback / screenshot / indirect / GPU timer

**执行环境：** macOS（graphics）。

**Files:**
- Modify: `engine/src/rhi/rhi_metal.m`
- Test: `engine/tests/test_rhi_metal_resources.c`（追加）

**Interfaces:**
- Produces:
  - `rhi_shader_create_compute`（Task 10 的 manifest 路径）+ `rhi_cmd_dispatch`：`MTLComputeCommandEncoder` `dispatchThreadgroups:threadsPerThreadgroup:`（threadgroup 尺寸取 pipeline 的 `maxTotalThreadsPerThreadgroup` 与 8x8 惯例的 min）；`rhi_cmd_bind_storage_buffer` → `setBuffer:offset:atIndex:`；`rhi_cmd_bind_image_texture`/`rhi_cmd_bind_image_cubemap_face` → `setTexture:atIndex:`（mip 用 texture view `newTextureViewWithPixelFormat:textureType:levels:slices:`）；`rhi_cmd_memory_barrier` → `memoryBarrierWithScope:MTLBarrierScopeBuffers|Textures`。
  - `rhi_screenshot`：对齐 rhi.h:815-826 契约（必须在 acquire 后 present 前调用——Metal 侧等价约束：drawable 仍存在且 command buffer 已 commit 后 waitUntilCompleted，再 blit drawable texture → shared buffer；present 后 drawable 已释放 → false + LOG）。`rhi_texture_read_pixels` 的 FBO attachment depth 读回（R608-R610）走同 blit 路径。
  - indirect：`rhi_cmd_draw_indirect`/`_indexed_`/`_count` → `drawPrimitives...indirectBuffer:`/`executeCommandsInBuffer`（Metal 3 `MTLIndirectCommandBuffer`）；**决策**：`MTLIndirectCommandBuffer` 需要独立编码路径，本计划用 `drawIndexedPrimitives:...indirectBuffer:indirectBufferOffset:` 直接映射（Metal 原生支持 indirect draw buffer）；`_count` 变体 Metal 无直接等价 → fail-closed LOG_ERROR + no-op，能力位不声明（写入 `docs/rhi_metal_d3d12_feature_matrix.md` Metal 列）。
  - `rhi_gpu_timer_*`：`MTLCounterSampleBuffer`（timestamp，macOS 10.15+，`[device supportsCounterSampling:MTLCounterSamplingPointAtStageBoundary]` 门控）；不支持时 `rhi_gpu_timer_elapsed_ms` 返回 0 + LOG_WARN 一次（不 fail-closed 设备，仅计时降级）。
  - `rhi_cmd_fill_buffer`/`rhi_cmd_update_buffer`/`rhi_cmd_copy_buffer` → blit encoder `fillBuffer:range:value:`/`copyFromBuffer:`。

- [ ] **Step 1: 失败测试**——compute：storage buffer 填 0 → dispatch 一个 `tid` 写索引的最小 kernel → readback 断言 0..N-1；`rhi_cmd_fill_buffer(0xAB)` 后 readback 全 0xAB；screenshot：渲染已知 clear 色帧 → `rhi_screenshot` 中心像素匹配（容差 ±1）；present 后 screenshot → false（契约）。

- [ ] **Step 2: 验证失败** → 红。

- [ ] **Step 3: 最小实现** —— 按 Interfaces。

- [ ] **Step 4: 验证通过** —— ctest 绿。

- [ ] **Step 5: Commit**

```bash
git add engine/src/rhi/rhi_metal.m engine/tests/test_rhi_metal_resources.c docs/rhi_metal_notes.md
git commit -m "rhi_metal: compute dispatch, blit readback, screenshot, indirect draw, gpu timer"
```

---

## Phase 5 — shader 策略固化

### Task 10: 离线 shader 管线（GLSL→SPIR-V→MSL→metallib）+ manifest 加载模型

**执行环境：** 脚本/生成器 headless 部分任意平台可验（glslc 与 spirv-cross 在 Windows/Linux 也存在）；`xcrun metal/metallib` 与 metallib 校验仅 macOS（缺失标 UNAVAILABLE，manifest/MSL 文本生成仍可验）。

**Files:**
- Create: `engine/tools/compile_metal_shaders.sh`、`engine/tools/gen_metal_shader_manifest.c`
- Modify: `engine/CMakeLists.txt`（构建期自定义命令）
- Modify: `engine/src/rhi/rhi_metal.m`（`rhi_shader_create`/`rhi_shader_create_compute`/`rhi_shader_destroy` manifest 加载）
- Test: `engine/tests/test_metal_shader_pipeline.cmake`（脚本契约：产物存在性 + manifest 一致性）、`engine/tests/test_rhi_metal_format_mapping.c`（追加 hash 稳定性用例）

**决策与理由（规格 §4.7 的 Metal 行固化）：**
- **SPIRV-Cross，不用 metal-shaderconverter**：converter 是 Apple 闭源二进制、随 Xcode 版本绑定、无法 vendored/pin（违反规格 §7「依赖版本漂移」与计划 F 的锁定纪律）；SPIRV-Cross 开源、可 pin release tag、CLI 可脚本化，且复用现有 GLSL→SPIR-V 工具链（rhi_vk.c:972-983 的运行时 shaderc，target Vulkan 1.2/SPIR-V 1.5，离线侧用 glslc 同参数）。
- **绑定约定：传统 binding，不用 argument buffer**：现有 152 个 `*_vk` shader 的 set/binding 注解可被 spirv-cross 直接映射为 `[[buffer(n)]]`/`[[texture(n)]]`/`[[sampler(n)]]`；argument buffer 需重写 shader 接口与全部编码路径（YAGNI，renderer 侧 434 个 `rhi_pipeline_get_uniform_location` 调用点也不依赖它）。**映射规则（契约，测试固定）**：MSL 资源索引 = GLSL `binding` 值；仅接受 `set==0`（迁移期约定；`set!=0` 的 shader 让离线管线**显式失败**，不静默 remap——现有 `*_vk` shader 全部 set 0，管线脚本逐个验证）；push_constant block 固定映射到 `[[buffer(30)]]`（30/31 保留，VK 后端 push range 上限 256B 内无冲突）。
- **运行时加载模型（零第三方运行时依赖）**：`rhi_shader_create(dev, source, len, is_fragment)` 收到的仍是 renderer 传入的 GLSL 文本（调用点不改）。Metal 后端对 `source[0..len)` 计算 FNV-1a 64 hash，查构建期生成的 manifest（`rhi_metal_shader_manifest.c`，内容为 `{u64 hash; const char *msl_function_name;}[]` 静态表）→ 命中则从 device 创建时加载的 `engine.metallib` 取 `newFunctionWithName:`；未命中 → LOG_ERROR + `RHI_HANDLE_NULL`（fail-closed，不运行时编译）。metallib 路径：`engine.metallib` 置于可执行文件旁（构建期拷贝）；加载失败回退 `[device newLibraryWithSource:]` 编译打包的 MSL 文本（manifest 同时内嵌 MSL 文本数组，发布构建可用宏裁掉）并 LOG_WARN。
- **entrypoint 命名**：spirv-cross 每 shader 用 `--rename-entry-point main <basename>_<stage> <model>`，manifest 的 `msl_function_name` 即此名。

**Interfaces:**
- Consumes: `engine/shaders/*_vk.{vert,frag,comp}`（152 个文件中取 `_vk` 变体）；`shader_reflect_bindings`（shader_io.h:37-38）用于管线校验。
- Produces:
  - `engine/tools/compile_metal_shaders.sh`（POSIX sh，参数：`<shader_dir> <out_dir> <sdk>`）：

```sh
#!/bin/sh
# Offline Metal shader pipeline: *_vk GLSL -> SPIR-V (glslc) -> MSL (spirv-cross)
# -> .air (xcrun metal) -> engine.metallib (xcrun metallib) + manifest inputs.
set -eu
SHADER_DIR="$1"; OUT_DIR="$2"; SDK="${3:-macosx}"
mkdir -p "$OUT_DIR/spv" "$OUT_DIR/msl" "$OUT_DIR/air"
: > "$OUT_DIR/manifest.lines"
for src in "$SHADER_DIR"/*_vk.vert "$SHADER_DIR"/*_vk.frag "$SHADER_DIR"/*_vk.comp; do
    [ -e "$src" ] || continue
    base=$(basename "$src")            # e.g. blinn_phong_vk.vert
    name=${base%_vk.*}                 # e.g. blinn_phong
    case "$base" in
        *.vert) stage=vert; model=vertex ;;
        *.frag) stage=frag; model=fragment ;;
        *.comp) stage=comp; model=kernel ;;
    esac
    entry="${name}_${stage}"
    glslc --target-env=vulkan1.2 -fshader-stage="$stage" "$src" -o "$OUT_DIR/spv/$base.spv"
    spirv-cross "$OUT_DIR/spv/$base.spv" --msl --msl-version 20300 \
        --rename-entry-point main "$entry" "$model" \
        --output "$OUT_DIR/msl/$entry.metal"
    # set!=0 的 GLSL 会被 spirv-cross 原样保留 set 注解丢失风险——显式防线：
    if grep -q 'set[ ]*=' "$src" && ! grep -q 'set[ ]*=[ ]*0' "$src"; then
        echo "metal shader pipeline: non-zero descriptor set in $base (unsupported)" >&2
        exit 1
    fi
    xcrun -sdk "$SDK" metal -c "$OUT_DIR/msl/$entry.metal" -o "$OUT_DIR/air/$entry.air"
    printf '%s %s\n' "$base" "$entry" >> "$OUT_DIR/manifest.lines"
done
xcrun -sdk "$SDK" metallib "$OUT_DIR"/air/*.air -o "$OUT_DIR/engine.metallib"
```

  - `engine/tools/gen_metal_shader_manifest.c`：读 `manifest.lines` + 每个原始 GLSL 文件，算 FNV-1a 64，输出 `rhi_metal_shader_manifest.c`（`const RHIMetalShaderManifestEntry rhi_metal_shader_manifest[] = ...`；类型定义放 `rhi_metal_format.h`：`typedef struct { u64 source_hash; const char *msl_function; } RHIMetalShaderManifestEntry;`）。
  - CMake 集成（仅 `ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal"` 且 macOS）：`find_program` 锁定 `glslc`/`spirv-cross`/`xcrun`（缺一 → `message(FATAL_ERROR ...)` 诚实失败），`add_custom_command(OUTPUT engine.metallib rhi_metal_shader_manifest.c COMMAND ${CMAKE_COMMAND} -E env sh compile_metal_shaders.sh ...)` + `add_custom_target(engine_metal_shaders DEPENDS ...)` + `add_dependencies(engine_rhi_metal engine_metal_shaders)`；生成的 manifest `.c` 用 `target_sources(engine_rhi_metal PRIVATE ${out}/rhi_metal_shader_manifest.c)` 编进后端库；`engine.metallib` 拷到 `$<TARGET_FILE_DIR:engine_demo>`（及每个 `engine_link_rhi_backend` 的 target——helper 内统一处理）。
  - `rhi_metal.m` 的 `rhi_shader_create`：FNV-1a → manifest 二分/线性查（152 项线性即可）→ `newFunctionWithName:`，slot 类型 `RHI_RES_SHADER`。

- [ ] **Step 1: 失败测试**——`engine/tests/test_metal_shader_pipeline.cmake`（`cmake -P`，断言脚本存在、含 `glslc --target-env=vulkan1.2`、`spirv-cross ... --msl`、`xcrun -sdk`、`--rename-entry-point`、`set[ ]*=[ ]*0` 防线、metallib 产物行；断言 CMakeLists 含 `add_custom_command` + `engine_metal_shaders` 依赖链）。注册 + 跑 → 红（文件不存在）。

- [ ] **Step 2: 验证失败** —— `cmake -DENGINE_CMAKE=engine/CMakeLists.txt -DTOOLS_DIR=engine/tools -P engine/tests/test_metal_shader_pipeline.cmake` → FAIL。

- [ ] **Step 3: 最小实现** —— 按上文创建脚本/生成器/CMake 块 + `rhi_shader_create` manifest 加载。

- [ ] **Step 4: 验证通过**

```bash
# 脚本契约（任意平台）
cmake -DENGINE_CMAKE=engine/CMakeLists.txt -DTOOLS_DIR=engine/tools -P engine/tests/test_metal_shader_pipeline.cmake
# 真实管线（macOS）：152 个 *_vk shader 全量转换 + metallib 生成
cmake --build build-macos-metal --target engine_metal_shaders --parallel
ls -la build-macos-metal/engine.metallib   # 存在且非空
# shader reflection 一致性抽查（macOS 单测，test_rhi_metal_format_mapping 追加）：
# 对 3 个代表性 shader 的 GLSL 做 shader_reflect_bindings，对生成的 .metal 文本做
# 同款文本反射（shader_io 是文本级反射，MSL 的 [[buffer(n)]] 注解可解析），断言 binding 索引一致
ctest --test-dir build-macos-metal -R "test_metal_shader_pipeline|test_rhi_metal_format_mapping" --output-on-failure
```

- [ ] **Step 5: Commit**

```bash
git add engine/tools/compile_metal_shaders.sh engine/tools/gen_metal_shader_manifest.c \
        engine/CMakeLists.txt engine/src/rhi/rhi_metal.m engine/src/rhi/rhi_metal_format.h \
        engine/tests/test_metal_shader_pipeline.cmake engine/tests/test_rhi_metal_format_mapping.c
git commit -m "rhi_metal: offline GLSL->SPIR-V->MSL->metallib pipeline with hash manifest"
```

### Task 11: push constant 与 `rhi_pipeline_get_uniform_location` 的 Metal 语义

**执行环境：** macOS（graphics）；golden 值生成需先跑一次 VK 后端（macOS MoltenVK lane 或本机 Windows Vulkan）。

**Files:**
- Modify: `engine/src/rhi/rhi_metal.m`（`rhi_cmd_push_constants`/`rhi_cmd_set_uniform_*`/`rhi_pipeline_get_uniform_location`）
- Test: `engine/tests/test_rhi_metal_resources.c`（追加 golden offset 断言）

**Interfaces:**
- Consumes: VK 语义参照 rhi.h:573-596（push range 规则 `rhi_push_range_fits`/`rhi_push_helper_range_ok`）、rhi_vk.c:7196-7290 的 uniform helper 与偏移计算、`RHIPipelineDesc` 的 4 个 layout 布尔（rhi.h:262-265）。
- Produces（规格 §4.4「Metal=各自绑定槽索引/字节偏移」的具体化）：
  - `rhi_pipeline_get_uniform_location(dev, pipe, name)` **返回 push 块内字节偏移**（与 VK 同语义，434 个调用点零改动）：pipeline create 时按 layout 布尔选择 std430 偏移表（表逻辑从 rhi_vk.c 逐行移植到 `rhi_metal.m` 的纯 C 函数，保证两后端同规则）；未知 name → -1。
  - `rhi_cmd_push_constants(offset, data, size)` 与 `rhi_cmd_set_uniform_*`：写入 cmd 的 256B staging（`rhi_push_range_fits` 校验，越界丢弃 + LOG_WARN，对齐 rhi.h:573-580）；draw/dispatch 时 `setVertexBytes:push_staging length:range atIndex:30` / `setFragmentBytes:...`（≤4KB 限制远覆盖 256B）。
  - `rhi_cmd_bind_uniform_buffer` → `setBuffer:offset:atIndex:binding`。

- [ ] **Step 1: 失败测试 + golden**——golden 生成：在任一 VK 后端构建上跑 `engine/tests/test_rhi_push_offset_dump.c`（新建小工具测试，用 `terrain_layout` 等 4 种 layout 各建 pipeline，打印 name→offset），输出贴入 `test_rhi_metal_resources.c` 的期望值数组。Metal 侧断言同 name 同 offset；`rhi_cmd_push_constants` 越界写入被丢弃且后续 draw 无崩溃；`set_uniform_mat4(loc, m)` 后 shader 读到的矩阵逐元素相等（经 readback 一个把矩阵第一列写成颜色的片元 shader）。

- [ ] **Step 2: 验证失败** → stub 红。

- [ ] **Step 3: 最小实现** —— 移植偏移表 + staging flush。

- [ ] **Step 4: 验证通过** —— ctest 绿；golden 与 VK dump 逐行 diff 为空。

- [ ] **Step 5: Commit**

```bash
git add engine/src/rhi/rhi_metal.m engine/tests/test_rhi_metal_resources.c \
        engine/tests/test_rhi_push_offset_dump.c engine/CMakeLists.txt
git commit -m "rhi_metal: push-constant staging and VK-identical uniform byte offsets"
```

---

## Phase 6 — Ray tracing

### Task 12: MTLAccelerationStructure 映射（含 VK ABI TLAS 记录转换）+ fail-closed

**执行环境：** macOS 且 GPU 支持 ray tracing（Apple Silicon M1+ / A14+；不支持的目标硬件走 fail-closed 路径，测试断言 UNSUPPORTED 而非崩溃）。无 macOS → UNAVAILABLE。

**Files:**
- Modify: `engine/src/rhi/rhi_metal.m`
- Test: `engine/tests/test_rhi_metal_resources.c`（追加 RT 段）

**Interfaces:**
- Consumes: `RHIAccelerationStructureDesc`（rhi.h:44-47）、`RHIBLASOneTriangleDesc`（rhi.h:49-59）、`RHITLASInstanceDesc`/`RHI_TLAS_INSTANCE_SIZE`（rhi.h:68-78，VK ABI 维持不改，规格 §4.4「Metal 在后端内做格式转换」）、VK 参照实现 rhi_vk.c:4688-5137。
- Produces:
  - `rhi_backend_acceleration_structure_create/destroy`：`[device newAccelerationStructureWithSize:]`；sizes 由 `[device accelerationStructureSizesWithDescriptor:]`。
  - `rhi_backend_cmd_build_blas_one_triangle`：`MTLPrimitiveAccelerationStructureDescriptor` + `MTLAccelerationStructureTriangleGeometryDescriptor`（vertexBuffer/indexBuffer 直接复用 RHI buffer 的 MTLBuffer，`vertexFormat=MTLAttributeFormatFloat3`）。
  - TLAS 实例记录转换（VK ABI 64B record → `MTLAccelerationStructureUserIDInstanceDescriptor` 数组，Metal 3 API，`respondsToSelector` 门控）。record 打包布局由 `rhi_tlas_instance_encode` 固定（rhi_validation.c:117-133：bytes 0-47 transform 行主序 3x4，bytes 48-51 packed0 = custom_index 低 24 位 | mask<<24，bytes 52-55 packed1 = sbt_offset 低 24 位 | flags<<24，bytes 56-63 u64 BLAS 设备地址），转换代码逐项解包：

```objc
/* blas_addrs/blas_handles: 并行数组，build 前由调用方按 instance 记录中的
 * BLAS 地址去重收集（线性查找，实例数 << 100，无需哈希）。 */
static u32 metal_blas_index_for_address(const u64 *blas_addrs, u32 blas_count, u64 addr) {
    for (u32 i = 0; i < blas_count; ++i)
        if (blas_addrs[i] == addr) return i;
    return UINT32_MAX; /* 调用方检查：UINT32_MAX → LOG_ERROR + 跳过该实例（fail-closed） */
}

static bool metal_convert_tlas_instances(const void *records, u32 count,
        const u64 *blas_addrs, u32 blas_count,
        MTLAccelerationStructureUserIDInstanceDescriptor *out) {
    static bool warned_flags;
    for (u32 i = 0; i < count; ++i) {
        const u8 *rec = (const u8 *)records + i * RHI_TLAS_INSTANCE_SIZE;
        f32 transform[12];
        u32 packed0, packed1;
        u64 blas_addr;
        memcpy(transform, rec, sizeof(transform));
        memcpy(&packed0, rec + 48, sizeof(packed0));
        memcpy(&packed1, rec + 52, sizeof(packed1));
        memcpy(&blas_addr, rec + 56, sizeof(blas_addr));
        u32 blas_index = metal_blas_index_for_address(blas_addrs, blas_count, blas_addr);
        if (blas_index == UINT32_MAX) {
            LOG_ERROR("rhi_metal: TLAS instance references unknown BLAS address");
            return false;
        }
        /* VK record 行主序 3x4 → MTLPackedFloat4x3（4 个 float3 列）：转置。 */
        out[i].transformationMatrix.columns[0] = MTLPackedFloat3Make(transform[0], transform[4], transform[8]);
        out[i].transformationMatrix.columns[1] = MTLPackedFloat3Make(transform[1], transform[5], transform[9]);
        out[i].transformationMatrix.columns[2] = MTLPackedFloat3Make(transform[2], transform[6], transform[10]);
        out[i].transformationMatrix.columns[3] = MTLPackedFloat3Make(transform[3], transform[7], transform[11]);
        out[i].mask = (packed0 >> 24) & 0xFFu;
        out[i].intersectionFunctionTableOffset = packed1 & 0x00FFFFFFu;
        out[i].userID = packed0 & 0x00FFFFFFu;
        out[i].accelerationStructureIndex = blas_index;
        u32 flags = (packed1 >> 24) & 0xFFu;
        if (flags != 0u && !warned_flags) {
            LOG_WARN("rhi_metal: TLAS instance flags %#x not mapped in v1 (triangle-cull subset)", flags);
            warned_flags = true;
        }
    }
    return true;
}
```

  - **fail-closed**：`[device supportsRaytracing]==NO` 或 API 缺失（< Metal 3 / macOS 13）时：`feature_bits` 不含 RT 位（Task 3 已固定）、`rhi_backend_acceleration_structure_create` 返回 `RHI_HANDLE_NULL`、`rhi_backend_tlas_one_instance_get_build_sizes` 返回 false、`rhi_cmd_bind_acceleration_structure` no-op + LOG_ERROR；wrapper 层 `*_ex` 路径暴露 `RHI_RESULT_UNSUPPORTED`（规格 §4.2 表）。
  - `RHI_FEATURE_RAY_TRACING_PIPELINE` 永不置位（Task 3 表）；`rhi_cmd_bind_acceleration_structure` 在 compute 路径映射为 `setAccelerationStructure:atBufferIndex:`（ray query 语义，Metal 3 `MTLComputeCommandEncoder` API）。

- [ ] **Step 1: 失败测试**——RT 段：能力位存在时 BLAS one-triangle 创建 + build + `rhi_acceleration_structure_get_device_address` 非 0；单实例 TLAS build sizes 非 0；能力位缺失（在 [device supportsRaytracing]==NO 的机器上）→ 全部入口 fail-closed（NULL/false）且无崩溃。**两条路径都必须有断言**（运行时分支）。

- [ ] **Step 2: 验证失败** → stub 红。

- [ ] **Step 3: 最小实现** —— 按 Interfaces。

- [ ] **Step 4: 验证通过** —— ctest 绿（两种硬件路径之一在 CI runner 跑到哪条记哪条的收据）。

- [ ] **Step 5: Commit**

```bash
git add engine/src/rhi/rhi_metal.m engine/tests/test_rhi_metal_resources.c docs/rhi_metal_notes.md
git commit -m "rhi_metal: acceleration structures with VK-ABI TLAS record conversion (fail-closed)"
```

---

## Phase 7 — consumer 接入

### Task 13: engine_demo / dxx_break / myui 在 macOS metal 配置下构建与启动

**执行环境：** macOS（构建 + 启动 smoke 需窗口服务；CI runner 上 engine_demo 全量运行受 GPU/窗口限制时以 `SKIP_RETURN_CODE 77` 处理，本地真机跑全量）。

**Files:**
- Modify: `engine/CMakeLists.txt`（consumer target 经 `engine_link_rhi_backend` 链接——计划 A 已改造，本 Task 只验证 metal 分支；myui 的 `MYUI_VULKAN_ENABLED` 触发条件 :724-734 在 metal 下不得再强制 Vulkan）
- Test: 新增 ctest `test_macos_metal_consumer_smoke`（脚本驱动）

**Interfaces:**
- Consumes: `engine_link_rhi_backend`（计划 A）；`break_myui`/`dxx_break`/`engine_demo` targets（engine/CMakeLists.txt:745-759, 785-792, 1088-1089）。
- Produces:
  - CMake 修正：`:725` 的 `if(ENGINE_VULKAN OR ENGINE_PLATFORM STREQUAL "macos")` → metal 生效时不再置 `MYUI_VULKAN_ENABLED=ON`（条件改为 `ENGINE_VULKAN OR (ENGINE_PLATFORM STREQUAL "macos" AND NOT ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")`）；myui 的渲染走 `my_vgcanvas_break_rhi.c`（RHI 抽象，break_myui 库 :745-753），Metal 后端完成后无需 myui 专属后端。
  - smoke 测试（`engine/tests/test_macos_metal_consumer_smoke.cmake`，`cmake -P`）：断言 `dxx_break`、`engine_demo` 二进制存在；macOS 真机上 `engine_demo --frames 3` 退出码 0；runner 无窗口权限时 77。`--frames` 早退参数：先 `grep -n '\-\-frames' engine/src/main.c` 确认不存在，然后在 main.c 的帧循环入口解析 argv（`--frames N` → 计数到 N 后走正常 shutdown 路径），这是 consumer 接入的必要改动。

- [ ] **Step 1: 失败测试**——注册 smoke 测试并跑：metal 配置下 `dxx_break` 链接失败（myui_core 仍拉 Vulkan 库 → 与 metal 配置 `find_package(Vulkan)` 缺失冲突/或重复符号），红。

- [ ] **Step 2: 验证失败** —— `cmake -S engine -B build-macos-metal -G Ninja -DENGINE_RHI_BACKEND=metal -DMYUI_PAL=cocoa && cmake --build build-macos-metal --target dxx_break` → 链接错误。

- [ ] **Step 3: 最小实现** —— CMake 条件修正 + `--frames` 早退参数（如需要）。

- [ ] **Step 4: 验证通过**

```bash
cmake --build build-macos-metal --parallel
ctest --test-dir build-macos-metal -LE "graphics|fuzz" --output-on-failure          # headless 全绿
ctest --test-dir build-macos-metal -R "test_macos_metal_consumer_smoke|test_platform_cocoa_runtime" --output-on-failure
./build-macos-metal/engine_demo --frames 3    # 真机：退出码 0
./build-macos-metal/dxx_break                 # 真机：启动后人工/脚本截图确认渲染
```

- [ ] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/src/main.c engine/tests/test_macos_metal_consumer_smoke.cmake
git commit -m "rhi_metal: consumer smoke (engine_demo/dxx_break/myui) under metal backend"
```

---

## Phase 8 — 证据、文档与 CI

### Task 14: 证据台账 / feature matrix / CI lanes（macos-metal + ios-metal-build）

**执行环境：** 文档任意平台；CI YAML 语法校验任意平台（`python -c "import yaml..."` 或 actionlint）；lane 首跑需 GitHub macos-14 runner。

**Files:**
- Modify: `docs/rhi_backend_evidence.md`（计划 A 骨架上追加行）
- Modify: `docs/rhi_metal_d3d12_feature_matrix.md`（填充 Metal 列）
- Modify: `.github/workflows/ci.yml`（`macos-vulkan` lane :443 之后新增）
- Modify: `docs/Build_Guide.md`、`README.md`
- Test: `engine/tests/test_ci_lane_separation.cmake`（`cmake -P` 文本断言）

**Interfaces:**
- Produces:
  - 证据台账新行（初值，升级需收据）：

| 平台 × 后端 | 等级 | 依据 |
|---|---|---|
| macOS × 原生 Metal | COMPILED（首个 macos-metal lane 绿后） | CI `macos-metal` run 链接 |
| iOS × 原生 Metal | COMPILED | CI `ios-metal-build`（build-only + 模拟器 lifecycle，**不构成 GPU-runtime 证据**） |

  - Metal 列填充项（`docs/rhi_metal_d3d12_feature_matrix.md`）：7 种 RHIFormat 全支持；MSAA color resolve 支持/depth resolve 不支持；MRT 5 attachments；compute 支持；indirect draw 支持、indirect-count 不支持；ray query/AS 依硬件、raygen pipeline 永不支持；push constant 经 `set*Bytes`（256B staging）；present damage/buffer age 不支持。
  - CI `macos-metal` lane（与 `macos-vulkan` 严格分列，二者并存）：

```yaml
  macos-metal:
    name: macOS native Metal (Clang)
    runs-on: macos-14
    timeout-minutes: 25
    steps:
      - uses: actions/checkout@v4
      - name: Pin Xcode
        run: sudo xcode-select -s /Applications/Xcode_15.4.app/Contents/Developer && xcodebuild -version
      - name: Install shader toolchain
        run: brew install shaderc spirv-cross
      - name: Configure (metal)
        run: cmake -S engine -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=metal -DMYUI_PAL=cocoa
      - name: Build
        run: cmake --build build --parallel
      - name: Verify metallib artifact
        run: test -s build/engine.metallib && xcrun metal-nm build/engine.metallib | head -5
      - name: Headless + contract tests
        run: ctest --test-dir build -LE "graphics|fuzz" --output-on-failure
      - name: Metal device contract (GPU when available)
        run: ctest --test-dir build -L graphics --output-on-failure || true   # 77 skip 不上纲；runner 有 GPU 时计入收据
```

  - CI `ios-metal-build` lane：`cmake -S engine -B build-ios -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DENGINE_RHI_BACKEND=metal -DENGINE_BUILD_TESTS=OFF` → `xcodebuild -destination 'generic/platform=iOS Simulator' build`；产物存在性断言；lifecycle 仅模拟器启动一个最小 harness（**lane 名、台账行、注释中三处显式标注「模拟器证据 = compile/lifecycle only」**）。
  - `test_ci_lane_separation.cmake`：断言 ci.yml 同时含 `macos-vulkan:` 与 `macos-metal:`、`ios-metal-build:`；断言 `macos-metal` 块内不含 `molten` 字样（大小写不敏感）；断言台账文件含 `macOS × 原生 Metal` 行且不含把 MoltenVK 收据挂到 Metal 行的文本模式。

- [ ] **Step 1: 失败测试** —— 写 `test_ci_lane_separation.cmake` 并注册 → 跑 → 红（`macos-metal` 不存在）。

- [ ] **Step 2: 验证失败** —— `cmake -DCI_YML=.github/workflows/ci.yml -DEVIDENCE_MD=docs/rhi_backend_evidence.md -P engine/tests/test_ci_lane_separation.cmake` → FAIL。

- [ ] **Step 3: 最小实现** —— YAML/文档按上文写入；Build_Guide.md 增 metal 构建段（依赖：brew shaderc spirv-cross、Xcode 15.4+、`xcrun metal`）；README.md 后端矩阵表 macOS/iOS 行更新为「原生 Metal（认证中）/ MoltenVK（基线）」。

- [ ] **Step 4: 验证通过** —— 契约测试绿；`git push` 前在 fork/分支上触发两个新 lane 首跑并记录 run URL（或本地 `act` 不可用则在真机手动执行 lane 内每条命令并留收据）。

- [ ] **Step 5: Commit**

```bash
git add .github/workflows/ci.yml docs/rhi_backend_evidence.md docs/rhi_metal_d3d12_feature_matrix.md \
        docs/Build_Guide.md README.md engine/tests/test_ci_lane_separation.cmake engine/CMakeLists.txt
git commit -m "ci/docs: macos-metal + ios-metal-build lanes, Metal evidence rows (COMPILED)"
```

---

## Phase 9 — 最终验证与交付

### Task 15: macOS 真机全绿 + benchmark 收据 + push

**执行环境：** macOS 真机（带 GPU、可开窗）。无真机 → 整个 Task UNAVAILABLE，**不得 push**（规格 §9：测试全绿后才提交并推送）。

**Files:**
- Modify: `docs/rhi_backend_evidence.md`（等级升级 + 收据链接）

- [ ] **Step 1: 全量构建与测试（metal 配置）**

```bash
cmake -S engine -B build-macos-metal -G Ninja -DCMAKE_BUILD_TYPE=Release -DENGINE_RHI_BACKEND=metal -DMYUI_PAL=cocoa
cmake --build build-macos-metal --parallel
ctest --test-dir build-macos-metal --output-on-failure   # 全绿（graphics 含 GPU 用例）
```

- [ ] **Step 2: MoltenVK 基线不回归**

```bash
cmake -S engine -B build-macos-vk -G Ninja -DCMAKE_BUILD_TYPE=Release -DENGINE_RHI_BACKEND=vulkan -DMYUI_PAL=cocoa
cmake --build build-macos-vk --parallel
ctest --test-dir build-macos-vk --output-on-failure      # 对照基线全绿
```

- [ ] **Step 3: benchmark 收据**——按 `docs/rhi_benchmark_receipt_schema.md`（计划 A，规格 §8.3）产出 JSON：用 `engine_demo --frames 600` 计时（或复用现有 profiler 输出）分别跑 metal 与 vulkan 配置，字段齐全（schema_version/timestamp/platform/os_version/backend/gpu/driver_version/cpu/ram/build_commit/build_config/command/metrics{fps_avg,fps_p1,frame_ms_avg,frame_ms_p99}/evidence_level/runner）；证据等级字段：metal 行 `gpu_runtime`（benchmark 达标后 `benchmark_comparable`——fps_avg 不低于同机 MoltenVK 基线的 90%，阈值与判定写进台账行注释）；**缺 benchmark 收据时 Metal 等级止步 GPU_RUNTIME，不得标 BENCHMARK_COMPARABLE**。

- [ ] **Step 4: 台账升级**——`docs/rhi_backend_evidence.md` 的 macOS×Metal 行升级为 `GPU_RUNTIME`（或 `BENCHMARK_COMPARABLE`），附：CI `macos-metal` run URL、本机收据（日期/机型/GPU/macOS 版本/命令/结果）。iOS 行保持 COMPILED 直到 iOS 真机收据存在。

- [ ] **Step 5: push**

```bash
git status --short            # 确认无冻结文件、无意外改动
git log --oneline origin/master..HEAD
git push origin master
```

- [ ] **Step 6: 汇报**——列出：push 的 commit 范围；每个 Task 的证据（测试命令与结果）；证据等级终态；UNAVAILABLE 的 Task（若有）及其原因；冻结文件未被触碰的确认。

---

## Self-review 记录（计划作者填）

- **规格覆盖**：§4.1 链接模型 → Task 2；§4.2 错误映射 → Task 4；§4.3 帧生命周期 → Task 5/6；§4.4 中性化消费点（uniform_location/TLAS ABI）→ Task 11/12；§4.7 shader 策略 Metal 行 → Task 10/11；§7 风险（MoltenVK/Metal 分列、模拟器证据、依赖锁定）→ Task 14 + Global Constraints；规格要求的 9 个 Task 覆盖项 → Task 1/2（构建接入）、3/4（设备队列）、5/6（swapchain/帧）、7/8/9（资源管线）、10/11（shader）、12（RT）、13（consumer）、14（证据文档 CI）、15（验证 push）。
- **类型一致性**：`RHIMetalFormat`/`rhi_metal_format_from_rhi`/`rhi_metal_frame_slot`/`rhi_metal_slot_wait_value`（Task 3 定义）在 Task 5/7 使用；`metal_commit`/`metal_acquire_drawable`（Task 4/5 定义）在 Task 7/8/9 复用；`RHIMetalShaderManifestEntry`（Task 10 定义于 rhi_metal_format.h）供 rhi_metal.m 使用；`RHI_METAL_MAX_PUSH_BYTES`（Task 2 定义）供 Task 11 使用。
- **已知边界（写入 docs/rhi_metal_notes.md，不隐瞒）**：(1) Metal 无 device-lost 通知 API，检测靠 command buffer 完成状态 + shared-event 超时；(2) iOS 暂停/恢复依赖宿主自律（window_mobile.c 无事件钩子），后端仅防御性 BUSY；(3) indirect-count draw 不支持；(4) depth resolve 不支持；(5) shader 迁移期仅接受 set==0；(6) `rhi_present` 语义并入 frame_end（present 簿记 no-op），因 Metal 要求 presentDrawable 先于 commit。
