# RHI 计划 A：证据冻结 · API 中性化 · 后端构建拆分 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 冻结多后端证据基线，把 `rhi.h` 中性化并把 RHI 后端从 `rhi.c` unity-include 拆为独立静态库（`engine_rhi_opengl` / `engine_rhi_vulkan` / `engine_rhi_headless`），配上错误映射与 frame 生命周期契约测试及文档/CI 骨架，全部验证通过后推送 `origin master`。

**Architecture:** 编译期单后端、直接符号链接（无 vtable）。`engine` 静态库只保留 `RHI_CORE_SOURCES`（rhi.c 调度/校验 + ownership + validation + resources + present_history）；每个后端编译为独立静态库并导出同一组 `rhi_*` 符号；最终可执行文件通过 `engine_link_rhi_backend(<target>)` 链接 `engine` + 恰好一个后端库。证据等级严格分离：编译成功 ≠ GPU-runtime。

**Tech Stack:** C11（`-Werror`：MSVC `/W4 /WX`，GCC/Clang `-Wall -Wextra -Werror -pedantic`）、CMake ≥ 3.20 + Ninja、CTest（纯 C `main()` 非零即失败 + `cmake -P` 脚本契约测试）、vendored Vulkan SDK 1.4.357.0 + shaderc、glad。

上位规格：`docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md`（本计划覆盖其阶段 1、2、3 与 11 的文档骨架；§3 现状事实、§4 架构决策、§5 阶段拆分均以该文件为准）。

## Global Constraints

- 语言标准 C11，全目标 `-Werror`（MSVC `/W4 /WX`；GCC/Clang `-Wall -Wextra -Werror -pedantic`）；禁止为通过编译而削弱警告 flags。
- TDD：先写失败测试 → 运行验证失败（记录确切输出）→ 最小实现 → 运行验证通过 → commit。每个 Task 独立可测、独立提交。
- 冻结文件（任何步骤不得修改/删除/移动/`git add`）：`.scratch-vkprobe/`、`engine/profile_trace.json`、`.tmp/`、仓库根 `d3d12_shader_gate.hlsl` 与 `d3d12_shader_gate.dxil`。
- 证据等级纪律：`NONE → COMPILED → HEADLESS → NATIVE_SURFACE → GPU_RUNTIME → BENCHMARK_COMPARABLE`（`engine/src/platform/platform_compat.h:49-56`）。编译成功不得记为 GPU-runtime；headless stub（`engine_rhi_headless`）永远不是 GPU 证据；缺失 SDK 的平台只标 UNAVAILABLE，不得伪造证据。
- 构建入口（engine 是独立 CMake 项目）：`cmake -S engine -B <build> -G Ninja -DCMAKE_BUILD_TYPE=Debug` → `cmake --build <build> --parallel` → `ctest --test-dir <build> -LE "graphics|fuzz" --output-on-failure`；单测 `ctest --test-dir <build> -R '^<name>$' --output-on-failure`。本机已有 `build-gate/`（GL）与 `build-win-vk/`（`-DENGINE_VULKAN=ON`）。
- 测试惯例：宏在 `engine/tests/test_framework.h`；环境依赖 gate 用 `SKIP_RETURN_CODE 77`；labels 用 `headless/platform_contract/graphics/platform_runtime/fuzz/hardening`。
- `engine/CMakeLists.txt` 是混合行尾文件（新块 LF、旧块 CRLF）：Edit 的 `old_string`/`new_string` 必须按 Read 显示的原样处理（CRLF 区域用实际 `\r`）；新增块统一用 LF 并插入在已有的 LF 块旁。
- Read 工具纪律：读大文件每次调用必须显式传 `line_offset` 分页，避免重复拉取相同内容。
- 只在测试全绿后才 commit；只有 Task 8 允许 `git push origin master`。branch=master，remote=`origin git@github.com:konyka/break.git`。
- 上下文约 70% 时先生成压缩交接再继续，交接至少包含：当前 phase 与 todo 状态；已完成/失败/阻塞测试；已修改文件与未提交文件清单；当前 commit/branch/remote；平台 × 后端证据矩阵现状；未解决风险；下一步精确命令；不得触碰的凭据与用户文件清单（`.scratch-vkprobe/`、`engine/profile_trace.json`、`.tmp/`、`d3d12_shader_gate.{hlsl,dxil}`、`.env`、SSH 私钥）。
- NVIDIA 616.56 混合 GPU 上的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1} 异常不能作为源码修复依据（规格 §7）；遇到时在交接中记录，不立项修复。

---

### Task 1: WIP 验证与分组提交

**Files:**
- Modify: 无（本 Task 只做验证与 commit；若测试红，修复路径见 Step 5）
- Test: 既有套件（`build-gate` / `build-win-vk` 的 headless 套件）

**Interfaces:**
- Consumes: 当前工作树未提交 WIP（以 `git status` 实际输出为准）。
- Produces: 一个干净的、已分组提交的工作树（只剩冻结的未跟踪文件）；后续 Task 在此基线上做 TDD。

- [ ] **Step 1: 核实 WIP 真实清单**

```bash
git status --short
git diff --stat | tail -20
```

预期（2026-10-14 基线，若有出入以实际为准并相应调整下方分组）：已修改 `engine/src/rhi/{rhi.h,rhi.c,rhi_backend_internal.h,rhi_gl.c,rhi_ownership.c,rhi_vk.c}`、`engine/src/core/{shader_io.c,shader_io.h}`、`engine/CMakeLists.txt`、`engine/tests/{test_rhi_capabilities.c,test_shader_io.c,test_rhi_backend_internal_contract.cmake,test_rhi_backend_selection.cmake,test_d3d12_dependency_gate.cmake,test_d3d12_shader_compile_gate.cmake}`、`docs/{Build_Guide.md,Realtime_Raytracing_Progress.md}`；未跟踪新增 `engine/src/platform/platform_wsi.h`、`engine/src/rhi/{rhi_d3d12.c,rhi_d3d12.h}`、`engine/tests/{test_d3d12_lifetime_hresult_contract.c,test_d3d12_native_failure.c,test_platform_wsi_lifecycle.c}`、`docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md`、`docs/superpowers/plans/2026-10-14-rhi-plan-{b,c,d,e,f}-*.md`。未跟踪但**禁止加入任何 commit**：`.scratch-vkprobe/`、`.tmp/`、`d3d12_shader_gate.hlsl`、`d3d12_shader_gate.dxil`、`engine/profile_trace.json`。

- [ ] **Step 2: build-gate（GL）增量构建**

```bash
cmake --build build-gate --parallel
```

预期：成功，无 `-Werror` 失败。若 CMake 报 “out of date” 先 `cmake -S engine -B build-gate -G Ninja -DCMAKE_BUILD_TYPE=Debug` 重新配置再构建。

- [ ] **Step 3: build-gate headless 套件**

```bash
ctest --test-dir build-gate -LE "graphics|fuzz" --output-on-failure
```

预期：`100% tests passed`。

- [ ] **Step 4: build-win-vk（Vulkan）同样验证**

```bash
cmake --build build-win-vk --parallel
ctest --test-dir build-win-vk -LE "graphics|fuzz" --output-on-failure
```

预期：构建成功、`100% tests passed`。

- [ ] **Step 5: 若有红，修复而非绕过**

对失败测试单独复现：`ctest --test-dir <build> -R '^<name>$' --output-on-failure`，读输出定位；WIP 是用户自己的改动，只做最小修复使既有语义成立。禁止：删除/跳过测试、削弱警告 flags、`SKIP_RETURN_CODE` 伪装通过。修完回到 Step 2 重跑两个构建目录直至全绿。若是规格 §7 登记的 NVIDIA 混合 GPU 已知异常且只在 graphics label 测试出现，本 Task 的 headless 套件（已排除 `graphics|fuzz`）不受影响；不要因此改源码。

- [ ] **Step 6: 分组 commit（不 push）**

```bash
git add docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md \
  docs/superpowers/plans/2026-10-14-rhi-plan-b-wsi-vulkan-first.md \
  docs/superpowers/plans/2026-10-14-rhi-plan-c-metal.md \
  docs/superpowers/plans/2026-10-14-rhi-plan-d-d3d12.md \
  docs/superpowers/plans/2026-10-14-rhi-plan-e-renderer-abi.md \
  docs/superpowers/plans/2026-10-14-rhi-plan-f-release-deps-opengl-removal.md \
  docs/superpowers/plans/2026-10-14-rhi-plan-a-evidence-abstraction-buildsplit.md
git commit -m "docs: add multi-backend RHI migration spec and plan set"

git add engine/src/rhi/rhi.h engine/src/rhi/rhi.c engine/src/rhi/rhi_backend_internal.h \
  engine/src/rhi/rhi_gl.c engine/src/rhi/rhi_ownership.c engine/src/rhi/rhi_vk.c \
  engine/src/core/shader_io.c engine/src/core/shader_io.h \
  engine/tests/test_rhi_capabilities.c engine/tests/test_shader_io.c \
  engine/tests/test_rhi_backend_internal_contract.cmake \
  engine/tests/test_rhi_backend_selection.cmake
git commit -m "rhi: lifecycle result entries, test hooks, and contract test coverage"

git add engine/src/platform/platform_wsi.h engine/src/rhi/rhi_d3d12.c engine/src/rhi/rhi_d3d12.h \
  engine/tests/test_d3d12_lifetime_hresult_contract.c engine/tests/test_d3d12_native_failure.c \
  engine/tests/test_platform_wsi_lifecycle.c \
  engine/tests/test_d3d12_dependency_gate.cmake engine/tests/test_d3d12_shader_compile_gate.cmake \
  engine/CMakeLists.txt docs/Build_Guide.md docs/Realtime_Raytracing_Progress.md
git commit -m "platform: WSI lifecycle contract and d3d12 gate scaffolding"
```

提交后 `git status --short` 必须只剩冻结文件与（若 Task 2+ 未做则无）其他未跟踪项；确认 `.scratch-vkprobe/`、`.tmp/`、`d3d12_shader_gate.*`、`engine/profile_trace.json` 不在任何 commit 内（`git show --stat HEAD~2..HEAD` 检查文件清单）。注意：本计划文件自身也要纳入第一个 commit；若执行时该文件尚未定稿，把它留在工作树，待 Task 2 开始时随 Task 2 一起补交。

---

### Task 2: 证据台账冻结（docs/rhi_backend_evidence.md + 注册表测试）

**Files:**
- Create: `docs/rhi_backend_evidence.md`
- Create: `engine/tests/test_rhi_evidence_register.cmake`
- Test/Modify: `engine/CMakeLists.txt`（在 `add_test(NAME test_rhi_backend_selection ...)` 块之后插入注册，当前约 :2052-2060，以 `grep -n "test_rhi_backend_selection" engine/CMakeLists.txt` 定位）

**Interfaces:**
- Consumes: 规格 §2.1 的 10 行证据基线；`EngineSupportEvidenceLevel`（`engine/src/platform/platform_compat.h:49-56`）。
- Produces: CTest 测试 `test_rhi_evidence_register`（label `platform_contract`）；台账文档被 Task 7 的文档引用。

- [ ] **Step 1: 写契约测试脚本（先红）**

创建 `engine/tests/test_rhi_evidence_register.cmake`，完整内容：

```cmake
if(NOT DEFINED REPO_ROOT)
    message(FATAL_ERROR "REPO_ROOT is required")
endif()
if(NOT DEFINED EVIDENCE_DOC)
    message(FATAL_ERROR "EVIDENCE_DOC is required")
endif()
if(NOT EXISTS "${EVIDENCE_DOC}")
    message(FATAL_ERROR "evidence register missing: ${EVIDENCE_DOC}")
endif()
file(READ "${EVIDENCE_DOC}" evidence_text)
foreach(required_row
        "Linux X11 × OpenGL"
        "Linux X11 × Vulkan"
        "Linux Wayland × GL/VK"
        "Windows × Vulkan"
        "Windows × D3D12"
        "macOS × Vulkan(MoltenVK)"
        "macOS/iOS × 原生 Metal"
        "Android × Vulkan"
        "iOS × Vulkan(MoltenVK)"
        "OHOS")
    string(FIND "${evidence_text}" "${required_row}" row_offset)
    if(row_offset EQUAL -1)
        message(FATAL_ERROR "evidence register missing platform/backend row: ${required_row}")
    endif()
endforeach()
foreach(required_level
        "NONE" "COMPILED" "HEADLESS" "NATIVE_SURFACE" "GPU_RUNTIME" "BENCHMARK_COMPARABLE")
    string(FIND "${evidence_text}" "${required_level}" level_offset)
    if(level_offset EQUAL -1)
        message(FATAL_ERROR "evidence register missing evidence-level token: ${required_level}")
    endif()
endforeach()
if(NOT IS_DIRECTORY "${REPO_ROOT}/.scratch-vkprobe")
    message(FATAL_ERROR "frozen evidence directory missing: ${REPO_ROOT}/.scratch-vkprobe")
endif()
if(NOT EXISTS "${REPO_ROOT}/engine/profile_trace.json")
    message(FATAL_ERROR "frozen evidence file missing: ${REPO_ROOT}/engine/profile_trace.json")
endif()
```

在 `engine/CMakeLists.txt` 的 `test_rhi_backend_selection` 注册块之后插入（新块用 LF；紧跟其后的旧块是 CRLF，Edit 时只插入不改动旧行）：

```cmake
    add_test(NAME test_rhi_evidence_register
        COMMAND ${CMAKE_COMMAND}
            -DREPO_ROOT=${CMAKE_CURRENT_SOURCE_DIR}/..
            -DEVIDENCE_DOC=${CMAKE_CURRENT_SOURCE_DIR}/../docs/rhi_backend_evidence.md
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_evidence_register.cmake)
    set_tests_properties(test_rhi_evidence_register PROPERTIES
        LABELS "platform_contract")
```

- [ ] **Step 2: 运行验证失败**

```bash
cmake -S engine -B build-gate
ctest --test-dir build-gate -R '^test_rhi_evidence_register$' --output-on-failure
```

预期：FAIL，输出含 `evidence register missing: E:/work/break/engine/../docs/rhi_backend_evidence.md`（路径分隔符按 CMake 输出为准）。

- [ ] **Step 3: 写台账文档（最小实现转绿）**

创建 `docs/rhi_backend_evidence.md`，完整内容：

````markdown
# RHI 后端证据台账

- 冻结日期：2026-10-14（基线）；上位规格：`docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md` §2
- 证据等级（严格递增，升级必须有对应收据）：`NONE → COMPILED → HEADLESS → NATIVE_SURFACE → GPU_RUNTIME → BENCHMARK_COMPARABLE`
- 收据字段（每次等级变更必填，benchmark 类收据遵循 `docs/rhi_benchmark_receipt_schema.md`）：日期 / 机器 / GPU / 驱动版本 / 执行命令 / 结果（CI run URL 或本地 run 标识）
- 纪律：编译成功 ≠ GPU-runtime；模拟器证据只计入 COMPILED/HEADLESS；MoltenVK 证据不计入原生 Metal；Proton 只作兼容参考；headless stub（`engine_rhi_headless`）永不构成 GPU 证据。

## 基线矩阵（2026-10-14 冻结）

| 平台 × 后端 | 当前等级 | 依据 | 收据 |
|---|---|---|---|
| Linux X11 × OpenGL | GPU_RUNTIME | CI `gl` lane（Xvfb + 真 GL） | CI run：GitHub Actions `gl` job，2026-10-14 前最近一次 green run |
| Linux X11 × Vulkan | GPU_RUNTIME（lavapipe/llvmpipe，软渲染） | CI `vk` / `linux-graphics-smoke` lane | CI run：`vk` job 最近 green run |
| Linux Wayland × GL/VK | NATIVE_SURFACE | CI `wayland-gl` / `wayland-vk`（weston headless） | CI run：`wayland-*` job 最近 green run |
| Windows × Vulkan | GPU_RUNTIME（本机 + CI win32 runtime trio） | 本机 `build-win-vk/`、CI `windows-clang` | 本机：`cmake --build build-win-vk && ctest --test-dir build-win-vk -LE "graphics|fuzz"` 全绿（2026-10-14，Task 1 记录） |
| Windows × D3D12 | HEADLESS（contract/gate only） | `engine/src/rhi/rhi_d3d12.c/h` 仅编入 gate 测试，未接入 `RHIBackend` | 本机：`test_d3d12_*` gate 测试（2026-10-14） |
| macOS × Vulkan(MoltenVK) | GPU_RUNTIME | CI `macos-vulkan`（133/133 CTest, 2026-10-13） | CI run：`macos-vulkan` job，2026-10-13 |
| macOS/iOS × 原生 Metal | NONE | 无代码 | — |
| Android × Vulkan | COMPILED（host-injected ANativeWindow） | `engine/src/rhi/rhi_vk.c:1482-1700` | 源码审查记录（2026-10-14 冻结） |
| iOS × Vulkan(MoltenVK) | COMPILED（host-injected CAMetalLayer） | `engine/src/platform/platform_compat.h:86-95` | 源码审查记录（2026-10-14 冻结） |
| OHOS | NONE（UNAVAILABLE，fail-closed） | `engine/src/platform/platform_compat.h:111-120`；`engine/CMakeLists.txt:1073-1075` FATAL_ERROR | 契约测试 `test_platform_compat_harmonyos` |

## 变更规则

1. 等级升级必须在本表对应行更新「当前等级」并追加收据（日期/机器/GPU/驱动/命令/结果）。
2. 已知异常（如 NVIDIA 616.56 混合 GPU 的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1}）只登记在规格 §7，不作为本表等级依据。
3. 本表由 `test_rhi_evidence_register`（`engine/tests/test_rhi_evidence_register.cmake`）做存在性与行完整性 gate。
````

- [ ] **Step 4: 运行验证通过**

```bash
ctest --test-dir build-gate -R '^test_rhi_evidence_register$' --output-on-failure
cmake -S engine -B build-win-vk
ctest --test-dir build-win-vk -R '^test_rhi_evidence_register$' --output-on-failure
```

预期：两个构建目录均 PASS。

- [ ] **Step 5: Commit**

```bash
git add docs/rhi_backend_evidence.md engine/tests/test_rhi_evidence_register.cmake engine/CMakeLists.txt
git commit -m "rhi: freeze backend evidence baseline with register contract test"
```

---

### Task 3: 统一错误状态契约测试（test_rhi_error_contract.c）

**Files:**
- Create: `engine/tests/test_rhi_error_contract.c`
- Test/Modify: `engine/CMakeLists.txt`（在 `test_rhi_capabilities` 注册块之后插入，当前块位于 :1824-1880）

**Interfaces:**
- Consumes: `RHIResult`（`engine/src/rhi/rhi.h:338-349`）、`rhi_device_create_ex`/`rhi_device_destroy_ex`/`rhi_device_resize_ex`/`rhi_frame_begin_ex`/`rhi_frame_end_ex`/`rhi_present_ex`/`rhi_device_idle_ex`（rhi.h:353-358, 451-465, 851；实现 `engine/src/rhi/rhi.c:50-159`）、注入钩子 `rhi_test_set_lifecycle_result`/`rhi_test_set_device_status`（rhi.h:861-864）、内部测试钩子 `rhi_test_device_create`/`rhi_test_device_destroy`/`rhi_test_frame_owner_try_acquire`/`rhi_test_frame_owner_release`（`engine/src/rhi/rhi.c:362-387, 338-348`，经 `ENGINE_RHI_TEST=1` 启用）。
- Produces: CTest 测试 `test_rhi_error_contract`（label `headless;platform_contract`）；固定规格 §4.2 映射表。

如实说明：规格 §3.3 指出错误模型已部分存在，本测试是**回归锁（characterization test）**——先运行一次，若现有实现已满足映射则直接转绿并作为锁保留；若红，按计划内断言修 `engine/src/rhi/rhi.c` 的 `*_ex` 映射（只允许补齐映射，不改枚举）。

- [ ] **Step 1: 写失败测试（含注册，先跑看红/绿）**

创建 `engine/tests/test_rhi_error_contract.c`，完整内容：

```c
#include "test_framework.h"

#include "rhi/rhi.h"

/* ENGINE_RHI_TEST hooks (defined in rhi.c under ENGINE_RHI_TEST). */
extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);
extern bool rhi_test_frame_owner_try_acquire(RHIDevice *dev);
extern void rhi_test_frame_owner_release(RHIDevice *dev);

TEST(init_failure_maps_to_error_family)
{
    RHIResult result = RHI_RESULT_OK;

    /* 未知后端 → UNSUPPORTED（参数语义上的不支持）。 */
    ASSERT_EQ(rhi_device_create_ex((RHIBackend)99, (void *)1, (void *)1,
                                   64u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNSUPPORTED);
    /* 尺寸越界 → INVALID_ARGUMENT。 */
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_OPENGL, (void *)1, (void *)1,
                                   0u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_OPENGL, (void *)1, (void *)1,
                                   RHI_MAX_DRAWABLE_DIMENSION + 1u, 64u,
                                   &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_INVALID_ARGUMENT);
    /* surface/平台句柄缺失 → UNAVAILABLE（fail-closed）。 */
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_OPENGL, NULL, (void *)1,
                                   64u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_OPENGL, (void *)1, NULL,
                                   64u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
}

TEST(surface_unavailable_maps_fail_closed)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    /* 无 backend_data 的设备：surface 不可用，一切生命周期动词 UNAVAILABLE。 */
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_frame_end_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_device_idle_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_UNAVAILABLE);
    rhi_test_device_destroy(device);
}

TEST(device_lost_is_sticky_and_fail_fast)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_device_status(device, RHI_DEVICE_STATUS_LOST);
    ASSERT_EQ(rhi_device_get_status(device), RHI_DEVICE_STATUS_LOST);
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_frame_end_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_idle_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_DEVICE_LOST);
    rhi_test_device_destroy(device);
}

TEST(out_of_date_surfaces_via_lifecycle_result)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_lifecycle_result(device, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_device_idle_ex(device), RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_OUT_OF_DATE);
    /* surface lost 同样经 lifecycle_result 暴露并 fail-fast。 */
    rhi_test_set_lifecycle_result(device, RHI_RESULT_SURFACE_LOST);
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_SURFACE_LOST);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_SURFACE_LOST);
    rhi_test_device_destroy(device);
}

TEST(sync_failure_maps_to_sync_failed)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_lifecycle_result(device, RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_device_idle_ex(device), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_frame_end_ex(device), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_SYNC_FAILED);
    rhi_test_device_destroy(device);
}

TEST(busy_while_frame_or_control_in_flight)
{
    RHIDevice *device = rhi_test_device_create();

    ASSERT_NEQ(device, NULL);
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(device));
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_BUSY);
    ASSERT_EQ(rhi_device_destroy_ex(device), RHI_RESULT_BUSY);
    rhi_test_frame_owner_release(device);
    ASSERT_EQ(rhi_device_destroy_ex(device), RHI_RESULT_OK);
    /* destroy_ex 已销毁设备路径由 rhi_device_destroy 接管（backend_data 为
     * NULL 时是安全的空操作）；不再调用 rhi_test_device_destroy。 */
}

TEST_MAIN_BEGIN()
    RUN_TEST(init_failure_maps_to_error_family);
    RUN_TEST(surface_unavailable_maps_fail_closed);
    RUN_TEST(device_lost_is_sticky_and_fail_fast);
    RUN_TEST(out_of_date_surfaces_via_lifecycle_result);
    RUN_TEST(sync_failure_maps_to_sync_failed);
    RUN_TEST(busy_while_frame_or_control_in_flight);
TEST_MAIN_END()
```

在 `engine/CMakeLists.txt` 中 `test_rhi_capabilities` 注册块之后插入注册块（镜像该块的平台链接逻辑——当前真实后端仍由 `rhi.c` unity-include 提供，所以必须链接平台 GL/VK 库；Task 6 会把它切换为 `engine_rhi_headless`）：

```cmake
    add_executable(test_rhi_error_contract tests/test_rhi_error_contract.c
        ${RHI_CORE_SOURCES} src/core/log.c)
    target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_RHI_TEST=1)
    target_include_directories(test_rhi_error_contract PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_PLATFORM_MACOS=1)
        target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_VULKAN=1)
    endif()
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_include_directories(test_rhi_error_contract PRIVATE
            ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS} ${XKB_INCLUDE_DIRS})
        if(ENGINE_ENABLE_WAYLAND)
            target_compile_definitions(test_rhi_error_contract PRIVATE
                ENGINE_PLATFORM_WAYLAND=1)
        endif()
        if(ENGINE_VULKAN)
            target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_VULKAN=1)
        endif()
        if(ENGINE_ENABLE_WAYLAND)
            if(ENGINE_VULKAN)
                target_link_libraries(test_rhi_error_contract PRIVATE
                    ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} ${Vulkan_LIBRARIES}
                    ${SHADERC_LIB} dl pthread)
            else()
                target_link_libraries(test_rhi_error_contract PRIVATE
                    glad ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} GL EGL dl pthread)
            endif()
        elseif(ENGINE_VULKAN)
            target_link_libraries(test_rhi_error_contract PRIVATE
                ${X11_LIBRARIES} ${X11_Xrandr_LIB} ${Vulkan_LIBRARIES}
                ${SHADERC_LIB} dl pthread)
        else()
            target_link_libraries(test_rhi_error_contract PRIVATE
                glad ${X11_LIBRARIES} ${X11_Xrandr_LIB} GL dl pthread)
        endif()
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_link_libraries(test_rhi_error_contract PRIVATE glad opengl32)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_link_libraries(test_rhi_error_contract PRIVATE
            Vulkan::Vulkan ${SHADERC_LIB}
            "-framework Cocoa" "-framework QuartzCore" "-framework Metal")
    endif()
    add_test(NAME test_rhi_error_contract COMMAND test_rhi_error_contract)
    set_tests_properties(test_rhi_error_contract PROPERTIES
        LABELS "headless;platform_contract")
```

- [ ] **Step 2: 运行并记录结果**

```bash
cmake -S engine -B build-gate
cmake --build build-gate --parallel
ctest --test-dir build-gate -R '^test_rhi_error_contract$' --output-on-failure
cmake --build build-win-vk --parallel
ctest --test-dir build-win-vk -R '^test_rhi_error_contract$' --output-on-failure
```

预期：PASS（现有实现已覆盖映射；若有断言失败即为真实差距——按断言修 `rhi.c:50-159` 的对应 `*_ex` 映射，禁止改测试迁就实现）。把首次运行结果（红/绿）写入 commit message body 或交接记录。

- [ ] **Step 3: Commit**

```bash
git add engine/tests/test_rhi_error_contract.c engine/CMakeLists.txt
git commit -m "rhi: pin unified error-status mapping with contract test"
```

---

### Task 4: Frame 生命周期契约测试（test_rhi_frame_lifecycle_contract.c）

**Files:**
- Create: `engine/tests/test_rhi_frame_lifecycle_contract.c`
- Test/Modify: `engine/CMakeLists.txt`（紧接 Task 3 的注册块之后）

**Interfaces:**
- Consumes: 同 Task 3 的钩子与 `*_ex` 入口；frame 生命周期别名族 `rhi_frame_acquire_ex`/`rhi_frame_submit_ex`/`rhi_device_drain_ex`（rhi.h:457, 463, 852；实现 rhi.c:117-119, 132-134, 157-159）；`rhi_test_set_backend`（rhi.c:328-330）不在本测试使用——带假 backend 调用真实后端函数会崩，本测试全部走「无 backend + 注入钩子」路径。
- Produces: CTest 测试 `test_rhi_frame_lifecycle_contract`（label `headless;platform_contract`）；固定规格 §4.3 状态机的 headless 可断言部分。happy-path 的 GPU 顺序（acquire→begin→submit→present 真实提交）由 `graphics`/`platform_runtime` label 的运行时测试（`test_vulkan` 等）覆盖，不属于本 headless 契约。

- [ ] **Step 1: 写失败测试（含注册）**

创建 `engine/tests/test_rhi_frame_lifecycle_contract.c`，完整内容：

```c
#include "test_framework.h"

#include "rhi/rhi.h"

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);
extern bool rhi_test_frame_owner_try_acquire(RHIDevice *dev);
extern bool rhi_test_frame_owner_is_current(const RHIDevice *dev);
extern void rhi_test_frame_owner_release(RHIDevice *dev);

TEST(acquire_submit_present_drain_aliases_share_semantics)
{
    RHIResult result = RHI_RESULT_OK;

    /* 别名族与正名入口行为一致：NULL 设备一律 INVALID_ARGUMENT。 */
    ASSERT_EQ(rhi_frame_acquire_ex(NULL, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_frame_begin_ex(NULL, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_frame_submit_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_frame_end_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_present_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_device_drain_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_device_idle_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
}

TEST(acquire_requires_ready_device)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    /* READY 但无 backend（无 surface）：acquire 失败且 fail-closed。 */
    ASSERT_EQ(rhi_device_get_status(device), RHI_DEVICE_STATUS_READY);
    ASSERT_EQ(rhi_frame_acquire_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_frame_submit_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_device_drain_ex(device), RHI_RESULT_UNAVAILABLE);
    rhi_test_device_destroy(device);
}

TEST(lost_device_fails_fast_on_full_frame_sequence)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_device_status(device, RHI_DEVICE_STATUS_LOST);
    ASSERT_EQ(rhi_frame_acquire_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_frame_submit_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_drain_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_DEVICE_LOST);
    rhi_test_device_destroy(device);
}

TEST(out_of_date_fails_fast_and_is_per_device)
{
    RHIDevice *device = rhi_test_device_create();
    RHIDevice *other = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    ASSERT_NEQ(other, NULL);
    rhi_test_set_lifecycle_result(device, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_frame_acquire_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_frame_submit_ex(device), RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_device_drain_ex(device), RHI_RESULT_OUT_OF_DATE);
    /* 注入是 per-device 的：另一台设备不受影响。 */
    ASSERT_EQ(rhi_frame_acquire_ex(other, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    rhi_test_device_destroy(device);
    rhi_test_device_destroy(other);
}

TEST(only_one_in_flight_acquire_submit_pair_per_thread)
{
    RHIDevice *first = rhi_test_device_create();
    RHIDevice *second = rhi_test_device_create();

    ASSERT_NEQ(first, NULL);
    ASSERT_NEQ(second, NULL);
    /* 规格 §4.3：同一时刻只允许一对 in-flight acquire→submit。 */
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(first));
    ASSERT_TRUE(rhi_test_frame_owner_is_current(first));
    ASSERT_FALSE(rhi_test_frame_owner_try_acquire(second));
    ASSERT_FALSE(rhi_test_frame_owner_is_current(second));
    /* frame 未交还前 resize/destroy 均 BUSY（drain/destroy 的 fail-fast 面）。 */
    ASSERT_EQ(rhi_device_resize_ex(first, 64u, 64u), RHI_RESULT_BUSY);
    ASSERT_EQ(rhi_device_destroy_ex(first), RHI_RESULT_BUSY);
    rhi_test_frame_owner_release(first);
    ASSERT_FALSE(rhi_test_frame_owner_is_current(first));
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(second));
    rhi_test_frame_owner_release(second);
    /* destroy 前必须 drain/无 in-flight：释放后 destroy 成立。 */
    ASSERT_EQ(rhi_device_destroy_ex(first), RHI_RESULT_OK);
    rhi_test_device_destroy(second);
}

TEST_MAIN_BEGIN()
    RUN_TEST(acquire_submit_present_drain_aliases_share_semantics);
    RUN_TEST(acquire_requires_ready_device);
    RUN_TEST(lost_device_fails_fast_on_full_frame_sequence);
    RUN_TEST(out_of_date_fails_fast_and_is_per_device);
    RUN_TEST(only_one_in_flight_acquire_submit_pair_per_thread);
TEST_MAIN_END()
```

在 `engine/CMakeLists.txt` 中 Task 3 注册块之后插入（同样镜像 `test_rhi_capabilities` 的平台链接块，仅替换目标名）：

```cmake
    add_executable(test_rhi_frame_lifecycle_contract
        tests/test_rhi_frame_lifecycle_contract.c
        ${RHI_CORE_SOURCES} src/core/log.c)
    target_compile_definitions(test_rhi_frame_lifecycle_contract
        PRIVATE ENGINE_RHI_TEST=1)
    target_include_directories(test_rhi_frame_lifecycle_contract
        PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_rhi_frame_lifecycle_contract
            PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_rhi_frame_lifecycle_contract
            PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_rhi_frame_lifecycle_contract
            PRIVATE ENGINE_PLATFORM_MACOS=1 ENGINE_VULKAN=1)
    endif()
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_include_directories(test_rhi_frame_lifecycle_contract PRIVATE
            ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS} ${XKB_INCLUDE_DIRS})
        if(ENGINE_ENABLE_WAYLAND)
            target_compile_definitions(test_rhi_frame_lifecycle_contract
                PRIVATE ENGINE_PLATFORM_WAYLAND=1)
        endif()
        if(ENGINE_VULKAN)
            target_compile_definitions(test_rhi_frame_lifecycle_contract
                PRIVATE ENGINE_VULKAN=1)
        endif()
        if(ENGINE_ENABLE_WAYLAND)
            if(ENGINE_VULKAN)
                target_link_libraries(test_rhi_frame_lifecycle_contract PRIVATE
                    ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} ${Vulkan_LIBRARIES}
                    ${SHADERC_LIB} dl pthread)
            else()
                target_link_libraries(test_rhi_frame_lifecycle_contract PRIVATE
                    glad ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} GL EGL dl pthread)
            endif()
        elseif(ENGINE_VULKAN)
            target_link_libraries(test_rhi_frame_lifecycle_contract PRIVATE
                ${X11_LIBRARIES} ${X11_Xrandr_LIB} ${Vulkan_LIBRARIES}
                ${SHADERC_LIB} dl pthread)
        else()
            target_link_libraries(test_rhi_frame_lifecycle_contract PRIVATE
                glad ${X11_LIBRARIES} ${X11_Xrandr_LIB} GL dl pthread)
        endif()
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_link_libraries(test_rhi_frame_lifecycle_contract PRIVATE
            glad opengl32)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_link_libraries(test_rhi_frame_lifecycle_contract PRIVATE
            Vulkan::Vulkan ${SHADERC_LIB}
            "-framework Cocoa" "-framework QuartzCore" "-framework Metal")
    endif()
    add_test(NAME test_rhi_frame_lifecycle_contract
        COMMAND test_rhi_frame_lifecycle_contract)
    set_tests_properties(test_rhi_frame_lifecycle_contract PROPERTIES
        LABELS "headless;platform_contract")
```

- [ ] **Step 2: 运行并记录结果**

```bash
cmake -S engine -B build-gate
cmake --build build-gate --parallel
ctest --test-dir build-gate -R '^test_rhi_frame_lifecycle_contract$' --output-on-failure
cmake --build build-win-vk --parallel
ctest --test-dir build-win-vk -R '^test_rhi_frame_lifecycle_contract$' --output-on-failure
```

预期：PASS（回归锁；若红则按断言修 `rhi.c` 生命周期 wrapper，禁止改测试迁就实现）。注意 `only_one_in_flight_acquire_submit_pair_per_thread` 末尾 `rhi_device_destroy_ex(first)` 走的是既有 `rhi.c:71-76` + 后端空操作路径（与 `test_rhi_capabilities.c:512` 已有先例一致）。

- [ ] **Step 3: Commit**

```bash
git add engine/tests/test_rhi_frame_lifecycle_contract.c engine/CMakeLists.txt
git commit -m "rhi: pin frame lifecycle state machine with contract test"
```

---

### Task 5: rhi.h 中性化（rhi_native_vulkan.h + 枚举扩展）

**Files:**
- Create: `engine/src/rhi/rhi_native_vulkan.h`
- Create: `engine/tests/test_rhi_header_neutral.cmake`
- Modify: `engine/src/rhi/rhi.h`（:34-37 `RHIBackend` 扩展；:68-70 注释去 `VkAccelerationStructureInstanceKHR`；:80-83 `RHINativeHandleType` 扩展；:91-99 `RHINativeDevice` 移出；:147-159 `RHITextureNativeInfo` 移出；:320-324 `RHICmdBufferNativeInfo` 移出；:362-376 与 :391-393、:418-422 原型移出；:573-580 注释去 `vkCmdPushConstants`；:658 注释去 `vkCmdFillBuffer`；:828-841 `rhi_vk_validation_*` 移出）
- Modify: `engine/src/rhi/rhi.c`、`engine/src/rhi/rhi_gl.c`、`engine/src/rhi/rhi_vk.c`、`engine/src/rhi/rhi_d3d12.c`（各加 `#include <rhi/rhi_native_vulkan.h>`）
- Modify: `engine/src/renderer/rt_trace.c`、`engine/src/renderer/sl_dlss.h`、`engine/src/renderer/sl_dlss.c`、`engine/src/main.c`、`engine/src/test_vulkan.c`、`engine/tests/test_rhi_native.c`、`engine/tests/test_rhi_capabilities.c`、`engine/tests/test_sl_dlss.c`（各加 `#include <rhi/rhi_native_vulkan.h>`；精确消费清单见 Step 4 的 grep）
- Modify: `engine/tests/test_rhi_error_contract.c`（追加新枚举 fail-closed 测试）
- Test/Modify: `engine/CMakeLists.txt`（注册 `test_rhi_header_neutral`，紧随 `test_rhi_evidence_register` 块之后）

**Interfaces:**
- Consumes: Task 3 的 `test_rhi_error_contract.c`；规格 §4.4 中性化策略。
- Produces: `engine/src/rhi/rhi_native_vulkan.h`，导出类型 `RHINativeDevice`/`RHITextureNativeInfo`/`RHICmdBufferNativeInfo` 与函数 `rhi_texture_get_native_info`/`rhi_cmd_buffer_get_native_info`/`rhi_device_get_native_device`/`rhi_backend_get_native_device`/`rhi_backend_get_device_info` 除外（见下）/`rhi_backend_texture_get_native_info`/`rhi_backend_cmd_buffer_get_native_info`/`rhi_backend_acceleration_structure_get_vk_handle`/`rhi_acceleration_structure_get_vk_handle`/`rhi_vk_validation_message_count`/`rhi_vk_validation_message_count_reset`/`rhi_vk_validation_gate_active`/`rhi_vk_validation_set_enabled`；`rhi.h` 新增枚举值 `RHI_BACKEND_METAL`/`RHI_BACKEND_D3D12`/`RHI_NATIVE_HANDLE_METAL=2`/`RHI_NATIVE_HANDLE_D3D12=3`。

注意范围：`rhi_backend_get_device_info`（rhi.h:370）只用 `RHIDeviceInfo`，不依赖 Vulkan 形状，**留在 rhi.h**。`RHINativeHandleType` 枚举本身按规格 §4.4 留在 rhi.h。`RHI_TLAS_INSTANCE_SIZE`/`RHITLASInstanceDesc`（rhi.h:71-78）留在 rhi.h，仅重写注释去掉 VK ABI token。

- [ ] **Step 1: 写失败测试（header-neutral 契约）**

创建 `engine/tests/test_rhi_header_neutral.cmake`，完整内容：

```cmake
if(NOT DEFINED RHI_PUBLIC_HEADER)
    message(FATAL_ERROR "RHI_PUBLIC_HEADER is required")
endif()
if(NOT DEFINED RHI_VULKAN_NATIVE_HEADER)
    message(FATAL_ERROR "RHI_VULKAN_NATIVE_HEADER is required")
endif()
if(NOT EXISTS "${RHI_PUBLIC_HEADER}")
    message(FATAL_ERROR "missing public header: ${RHI_PUBLIC_HEADER}")
endif()
if(NOT EXISTS "${RHI_VULKAN_NATIVE_HEADER}")
    message(FATAL_ERROR "missing vulkan native header: ${RHI_VULKAN_NATIVE_HEADER}")
endif()
file(READ "${RHI_PUBLIC_HEADER}" rhi_public_text)
foreach(forbidden_token
        "VkDevice"
        "vkCmd"
        "VkAccelerationStructureInstanceKHR"
        "rhi_vk_validation_"
        "_get_vk_handle")
    string(FIND "${rhi_public_text}" "${forbidden_token}" forbidden_offset)
    if(NOT forbidden_offset EQUAL -1)
        message(FATAL_ERROR
            "rhi.h must stay backend-neutral; found token: ${forbidden_token}")
    endif()
endforeach()
foreach(required_token
        "RHI_BACKEND_METAL"
        "RHI_BACKEND_D3D12"
        "RHI_NATIVE_HANDLE_METAL"
        "RHI_NATIVE_HANDLE_D3D12")
    string(FIND "${rhi_public_text}" "${required_token}" required_offset)
    if(required_offset EQUAL -1)
        message(FATAL_ERROR "rhi.h missing neutral extension token: ${required_token}")
    endif()
endforeach()
file(READ "${RHI_VULKAN_NATIVE_HEADER}" vulkan_native_text)
foreach(required_native_token
        "RHINativeDevice"
        "RHITextureNativeInfo"
        "RHICmdBufferNativeInfo"
        "rhi_texture_get_native_info"
        "rhi_device_get_native_device"
        "rhi_backend_get_native_device"
        "rhi_backend_acceleration_structure_get_vk_handle"
        "rhi_acceleration_structure_get_vk_handle"
        "rhi_vk_validation_message_count"
        "rhi_vk_validation_message_count_reset"
        "rhi_vk_validation_gate_active"
        "rhi_vk_validation_set_enabled")
    string(FIND "${vulkan_native_text}" "${required_native_token}" native_offset)
    if(native_offset EQUAL -1)
        message(FATAL_ERROR
            "rhi_native_vulkan.h missing declaration: ${required_native_token}")
    endif()
endforeach()
```

注册（插入在 `test_rhi_evidence_register` 注册块之后）：

```cmake
    add_test(NAME test_rhi_header_neutral
        COMMAND ${CMAKE_COMMAND}
            -DRHI_PUBLIC_HEADER=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi.h
            -DRHI_VULKAN_NATIVE_HEADER=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_native_vulkan.h
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_header_neutral.cmake)
    set_tests_properties(test_rhi_header_neutral PROPERTIES
        LABELS "platform_contract")
```

- [ ] **Step 2: 运行验证失败**

```bash
cmake -S engine -B build-gate
ctest --test-dir build-gate -R '^test_rhi_header_neutral$' --output-on-failure
```

预期：FAIL，输出 `missing vulkan native header: .../engine/src/rhi/rhi_native_vulkan.h`。

- [ ] **Step 3: 创建 rhi_native_vulkan.h（最小实现的第一半）**

创建 `engine/src/rhi/rhi_native_vulkan.h`，完整内容（声明逐一从 rhi.h 原样迁移，签名不变）：

```c
#pragma once
#include <rhi/rhi.h>

/* Vulkan-shaped native interop, moved out of rhi.h so the public header stays
 * backend-neutral (multi-backend RHI spec §4.4). Consumers that need native
 * handles include this header explicitly. The declarations keep their
 * historical signatures (opaque void* handles) so existing call sites compile
 * unchanged apart from the added include. */

typedef struct {
    RHINativeHandleType type;
    void *instance;
    void *physical_device;
    void *device;
    void *graphics_queue;
    u32 graphics_queue_family;
    u32 feature_bits;
} RHINativeDevice;

typedef struct {
    RHINativeHandleType type;
    void *image;
    void *memory;
    void *view;
    u32 image_layout;
    RHIFormat format;
    u32 native_format;
    u32 width;
    u32 height;
    u32 mip_levels;
    u32 array_layers;
} RHITextureNativeInfo;

typedef struct {
    RHINativeHandleType type;
    void *command_buffer;
    bool recording;
} RHICmdBufferNativeInfo;

bool       rhi_texture_get_native_info(
               const RHIDevice *dev, RHITexture texture,
               RHITextureNativeInfo *out);
bool       rhi_cmd_buffer_get_native_info(
               const RHIDevice *dev, const RHICmdBuffer *cmd,
               RHICmdBufferNativeInfo *out);
bool       rhi_device_get_native_device(const RHIDevice *dev, RHINativeDevice *out);
bool       rhi_backend_get_native_device(const RHIDevice *dev, RHINativeDevice *out);
bool       rhi_backend_texture_get_native_info(
               const RHIDevice *dev, RHITexture texture,
               RHITextureNativeInfo *out);
bool       rhi_backend_cmd_buffer_get_native_info(
               const RHIDevice *dev, const RHICmdBuffer *cmd,
               RHICmdBufferNativeInfo *out);
bool       rhi_backend_acceleration_structure_get_vk_handle(
               RHIDevice *dev, RHIAccelerationStructure structure,
               void **out_handle);
/* Opaque native acceleration-structure handle (VkAccelerationStructureKHR on
 * Vulkan). Fails closed on OpenGL or invalid handles. */
bool       rhi_acceleration_structure_get_vk_handle(
               RHIDevice *dev, RHIAccelerationStructure structure,
               void **out_handle);

/* R438: Vulkan validation-message gate (defined only by the VK backend).
 * The counters link and stay inert (0 / no-op) when the gate was never
 * enabled. */
u32  rhi_vk_validation_message_count(void);
void rhi_vk_validation_message_count_reset(void);
bool rhi_vk_validation_gate_active(void);
void rhi_vk_validation_set_enabled(bool enabled);
```

- [ ] **Step 4: 迁移 rhi.h 并修复全部消费点**

4a. rhi.h 编辑（该文件是混合行尾，Edit 按 Read 显示处理）：
- `RHIBackend`（rhi.h:34-37）改为：

```c
typedef enum {
    RHI_BACKEND_OPENGL,
    RHI_BACKEND_VULKAN,
    /* Declared for selector/ABI stability; rhi_device_create_ex fails closed
     * with RHI_RESULT_UNSUPPORTED until the Metal/D3D12 backends land
     * (plans C/D). */
    RHI_BACKEND_METAL,
    RHI_BACKEND_D3D12,
} RHIBackend;
```

- TLAS 注释（rhi.h:68-70）改为：

```c
/* Serialized TLAS instance record (64 bytes, array-of-structs layout,
 * compatible with the Vulkan acceleration-structure instance ABI):
 * transform row-major 3x4, packed custom index/mask,
 * packed SBT offset/flags, then the BLAS device address. */
```

- `RHINativeHandleType`（rhi.h:80-83）改为：

```c
typedef enum {
    RHI_NATIVE_HANDLE_NONE = 0,
    RHI_NATIVE_HANDLE_VULKAN = 1,
    RHI_NATIVE_HANDLE_METAL = 2,
    RHI_NATIVE_HANDLE_D3D12 = 3,
} RHINativeHandleType;
```

- 删除 rhi.h 中以下块（已迁入 rhi_native_vulkan.h）：`RHINativeDevice`（:91-99）、`RHITextureNativeInfo`（:147-159）、`RHICmdBufferNativeInfo`（:320-324）、`rhi_texture_get_native_info`/`rhi_cmd_buffer_get_native_info`/`rhi_device_get_native_device`/`rhi_backend_get_native_device`/`rhi_backend_texture_get_native_info`/`rhi_backend_cmd_buffer_get_native_info`（:362-376）、`rhi_backend_acceleration_structure_get_vk_handle`（:391-393）、`rhi_acceleration_structure_get_vk_handle` 及其注释（:418-422）、`rhi_vk_validation_*` 及其注释块（:828-841）。**保留** `rhi_backend_get_device_info`（:370）与 `RHINativeHandleType`。
- `rhi_cmd_push_constants` 注释（:573-580）中 `aligned with vkCmdPushConstants(offset, size)` 改写为 `aligned with push-constant range semantics (offset, size)`。
- `rhi_cmd_fill_buffer` 注释（:658）中 `(vkCmdFillBuffer / glClearBufferSubData)` 改写为 `(recorded GPU buffer fill / glClearBufferSubData)`。

4b. 找出并修复全部消费点（以 grep 结果为准，逐一加 `#include <rhi/rhi_native_vulkan.h>`）：

```bash
grep -rln 'RHINativeDevice\|RHITextureNativeInfo\|RHICmdBufferNativeInfo\|rhi_vk_validation_\|_get_vk_handle' engine/src engine/tests --include='*.c' --include='*.h'
```

2026-10-14 核实的清单：`engine/src/rhi/rhi.c`（实现被迁移的 wrapper）、`engine/src/rhi/rhi_gl.c`、`engine/src/rhi/rhi_vk.c`（实现 `rhi_backend_*` 与 `rhi_vk_validation_*`）、`engine/src/renderer/rt_trace.c`、`engine/src/renderer/sl_dlss.h`、`engine/src/renderer/sl_dlss.c`、`engine/src/main.c`、`engine/src/test_vulkan.c`、`engine/tests/test_rhi_native.c`、`engine/tests/test_rhi_capabilities.c`（`RHITextureNativeInfo`，:244）、`engine/tests/test_sl_dlss.c`；另检查 `engine/src/rhi/rhi_d3d12.c`（WIP 新文件，若引用原生类型同样加 include）。

4c. 枚举扩展的编译面检查（`-Wswitch` 穷举）：

```bash
grep -rn 'switch' engine/src/rhi/*.c engine/src/renderer/*.c | grep -i 'backend'
```

对任何 `switch` 覆盖 `RHIBackend` 且无 `default` 的位置，补 `default:` fail-closed 分支或显式 `case RHI_BACKEND_METAL: case RHI_BACKEND_D3D12:` 返回错误。`rhi_device_create_ex` 的后端校验（`rhi.c:54`）已把任何非 GL/VK 后端 fail-closed 到 `RHI_RESULT_UNSUPPORTED`，**不需要改动**。

4d. 给 Task 3 的测试追加新枚举 fail-closed 断言。在 `engine/tests/test_rhi_error_contract.c` 中 `TEST_MAIN_BEGIN()` 之前追加：

```c
TEST(declared_metal_and_d3d12_backends_fail_closed)
{
    RHIResult result = RHI_RESULT_OK;

    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_METAL, (void *)1, (void *)1,
                                   64u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNSUPPORTED);
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, (void *)1,
                                   64u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNSUPPORTED);
}
```

并在 `TEST_MAIN_BEGIN()` 列表中 `RUN_TEST(busy_while_frame_or_control_in_flight);` 之后加 `RUN_TEST(declared_metal_and_d3d12_backends_fail_closed);`。

- [ ] **Step 5: 构建 + 全部相关测试转绿**

```bash
cmake --build build-gate --parallel
ctest --test-dir build-gate -R '^test_rhi_header_neutral$' --output-on-failure
ctest --test-dir build-gate -R '^test_rhi_(capabilities|native|error_contract|frame_lifecycle_contract)$' --output-on-failure
ctest --test-dir build-gate -LE "graphics|fuzz" --output-on-failure
cmake --build build-win-vk --parallel
ctest --test-dir build-win-vk -LE "graphics|fuzz" --output-on-failure
```

预期：`test_rhi_header_neutral` PASS；两个构建目录全部测试 PASS。若有未捕获的消费点，编译错误会指向具体文件——回 Step 4b 补 include，禁止为绕过而把类型定义复制回 rhi.h。

- [ ] **Step 6: Commit**

```bash
git add engine/src/rhi/rhi.h engine/src/rhi/rhi_native_vulkan.h \
  engine/src/rhi/rhi.c engine/src/rhi/rhi_gl.c engine/src/rhi/rhi_vk.c \
  engine/src/rhi/rhi_d3d12.c \
  engine/src/renderer/rt_trace.c engine/src/renderer/sl_dlss.h \
  engine/src/renderer/sl_dlss.c engine/src/main.c engine/src/test_vulkan.c \
  engine/tests/test_rhi_native.c engine/tests/test_rhi_capabilities.c \
  engine/tests/test_sl_dlss.c engine/tests/test_rhi_error_contract.c \
  engine/tests/test_rhi_header_neutral.cmake engine/CMakeLists.txt
git commit -m "rhi: move vulkan-shaped native interop out of rhi.h"
```

---

### Task 6: 后端构建拆分（engine_rhi_* 静态库 + engine_link_rhi_backend）

**Files:**
- Create: `engine/src/rhi/rhi_headless.c`
- Modify: `engine/src/rhi/rhi.c`（删除 :408-415 unity-include 块）
- Modify: `engine/CMakeLists.txt`（:443 glad 移出 engine；:345-351 SHADERC include 移出 engine；平台链接块 linux :982-1004 / windows :1013-1019 / macos :1045-1054 / 移动 :1077-1084 中的后端库移出；glad 块 :400-407 之后插入后端库 target 与 `engine_link_rhi_backend` 定义；:1085 与 :1087 之间插入后端平台链接；各可执行 target 加 `engine_link_rhi_backend`；五个 direct-source RHI 测试的链接块替换为 `engine_rhi_headless`；`test_rhi_backend_internal_contract` 注册增加 `-DRHI_HEADLESS_SOURCE`，当前 :2091-2106）
- Modify: `engine/tests/test_rhi_backend_internal_contract.cmake`（整体重写，见 Step 1）
- Test: `test_rhi_backend_internal_contract`（重写后先红）、`test_rhi_backend_selection`（保持金属/d3d12 拒绝语义，本 Task 不改）

**Interfaces:**
- Consumes: Task 5 的 `rhi_native_vulkan.h`；`rhi_backend_internal.h` 的共享内部符号（`g_current_device`、`g_rhi_frame_device`、`g_rhi_frame_owner_preclaimed`、`rhi_alloc_slot` 等，`rhi_backend_internal.h:51-61`）。
- Produces: CMake target `engine_rhi_opengl`（`src/rhi/rhi_gl.c`）、`engine_rhi_vulkan`（`src/rhi/rhi_vk.c`，PRIVATE `ENGINE_VULKAN=1`，链接 `Vulkan::Vulkan ${SHADERC_LIB}`）、`engine_rhi_headless`（`src/rhi/rhi_headless.c`，全入口 fail-closed）；CMake 函数 `engine_link_rhi_backend(<target>)`。`test_rhi_backend_selection.cmake` 的 metal/d3d12 FATAL_ERROR 语义保持不变。

- [ ] **Step 1: 重写内部契约测试（先红）**

整体替换 `engine/tests/test_rhi_backend_internal_contract.cmake` 为以下内容（沿用现有 paren-matcher 解析法）：

```cmake
if(NOT DEFINED RHI_INTERNAL_HEADER)
    message(FATAL_ERROR "RHI_INTERNAL_HEADER is required")
endif()
if(NOT DEFINED RHI_SOURCE)
    message(FATAL_ERROR "RHI_SOURCE is required")
endif()
if(NOT DEFINED RHI_GL_SOURCE)
    message(FATAL_ERROR "RHI_GL_SOURCE is required")
endif()
if(NOT DEFINED RHI_VK_SOURCE)
    message(FATAL_ERROR "RHI_VK_SOURCE is required")
endif()
if(NOT DEFINED RHI_HEADLESS_SOURCE)
    message(FATAL_ERROR "RHI_HEADLESS_SOURCE is required")
endif()
if(NOT DEFINED RHI_OWNERSHIP_SOURCE)
    message(FATAL_ERROR "RHI_OWNERSHIP_SOURCE is required")
endif()
if(NOT DEFINED RHI_VALIDATION_SOURCE)
    message(FATAL_ERROR "RHI_VALIDATION_SOURCE is required")
endif()
if(NOT DEFINED RHI_RESOURCES_SOURCE)
    message(FATAL_ERROR "RHI_RESOURCES_SOURCE is required")
endif()
if(NOT DEFINED RHI_PRESENT_HISTORY_SOURCE)
    message(FATAL_ERROR "RHI_PRESENT_HISTORY_SOURCE is required")
endif()
if(NOT DEFINED RHI_RT_TRACE_SOURCE)
    message(FATAL_ERROR "RHI_RT_TRACE_SOURCE is required")
endif()
if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

function(extract_cmake_command text command_start output_var)
    string(REGEX REPLACE "#[^\r\n]*" "" uncommented_text "${text}")
    string(FIND "${uncommented_text}" "${command_start}" command_start_offset)
    if(command_start_offset EQUAL -1)
        set(${output_var} "" PARENT_SCOPE)
        return()
    endif()

    string(LENGTH "${uncommented_text}" text_length)
    set(scan_offset ${command_start_offset})
    set(parenthesis_depth 0)
    while(scan_offset LESS text_length)
        string(SUBSTRING "${uncommented_text}" ${scan_offset} 1 current_char)
        if(current_char STREQUAL "(")
            math(EXPR parenthesis_depth "${parenthesis_depth} + 1")
        elseif(current_char STREQUAL ")")
            math(EXPR parenthesis_depth "${parenthesis_depth} - 1")
            if(parenthesis_depth EQUAL 0)
                math(EXPR command_length "${scan_offset} - ${command_start_offset} + 1")
                string(SUBSTRING "${uncommented_text}" ${command_start_offset} ${command_length}
                    extracted_command)
                set(${output_var} "${extracted_command}" PARENT_SCOPE)
                return()
            endif()
        endif()
        math(EXPR scan_offset "${scan_offset} + 1")
    endwhile()
    set(${output_var} "" PARENT_SCOPE)
endfunction()

file(READ "${RHI_INTERNAL_HEADER}" internal_text)
file(READ "${RHI_SOURCE}" rhi_text)
file(READ "${RHI_GL_SOURCE}" gl_text)
file(READ "${RHI_VK_SOURCE}" vk_text)
file(READ "${ENGINE_CMAKE}" engine_cmake_text)
if(DEFINED RHI_OMIT_TARGET)
    if(RHI_OMIT_TARGET STREQUAL "engine")
        set(omit_command_start "add_library(engine STATIC")
    else()
        set(omit_command_start "add_executable(${RHI_OMIT_TARGET}")
    endif()
    extract_cmake_command("${engine_cmake_text}" "${omit_command_start}" omit_command)
    if(omit_command)
        if(RHI_OMIT_TARGET STREQUAL "engine")
            set(omit_replacement "add_library(engine STATIC)")
        else()
            set(omit_replacement "add_executable(${RHI_OMIT_TARGET})")
        endif()
        string(REPLACE "${omit_command}" "${omit_replacement}" engine_cmake_text
            "${engine_cmake_text}")
    endif()
endif()
foreach(required_source_path
        "${RHI_INTERNAL_HEADER}"
        "${RHI_SOURCE}"
        "${RHI_GL_SOURCE}"
        "${RHI_VK_SOURCE}"
        "${RHI_HEADLESS_SOURCE}"
        "${RHI_OWNERSHIP_SOURCE}"
        "${RHI_VALIDATION_SOURCE}"
        "${RHI_RESOURCES_SOURCE}"
        "${RHI_PRESENT_HISTORY_SOURCE}"
        "${RHI_RT_TRACE_SOURCE}")
    if(NOT EXISTS "${required_source_path}")
        message(FATAL_ERROR "RHI source contract input is missing: ${required_source_path}")
    endif()
endforeach()

# RHI core ownership: the five core sources stay in RHI_CORE_SOURCES.
extract_cmake_command("${engine_cmake_text}" "set(RHI_CORE_SOURCES" rhi_core_sources_block)
if(NOT rhi_core_sources_block)
    message(FATAL_ERROR "RHI core source ownership block is missing")
endif()
if(DEFINED RHI_OMIT_SOURCE)
    string(REPLACE "${RHI_OMIT_SOURCE}" "" engine_cmake_text "${engine_cmake_text}")
    extract_cmake_command("${engine_cmake_text}" "set(RHI_CORE_SOURCES" rhi_core_sources_block)
endif()
foreach(required_source
        "src/rhi/rhi.c"
        "src/rhi/rhi_ownership.c"
        "src/rhi/rhi_validation.c"
        "src/rhi/rhi_resources.c"
        "src/rhi/rhi_present_history.c")
    string(FIND "${rhi_core_sources_block}" "${required_source}" source_offset)
    if(source_offset EQUAL -1)
        message(FATAL_ERROR "RHI core source ownership missing: ${required_source}")
    endif()
endforeach()

# rhi.c must no longer unity-include a backend.
foreach(unity_token "#include <rhi/rhi_vk.c>" "#include <rhi/rhi_gl.c>")
    string(FIND "${rhi_text}" "${unity_token}" unity_offset)
    if(NOT unity_offset EQUAL -1)
        message(FATAL_ERROR "rhi.c must not unity-include a backend: ${unity_token}")
    endif()
endforeach()

# engine owns the core aggregate and no backend source.
extract_cmake_command("${engine_cmake_text}" "add_library(engine STATIC" engine_block)
if(NOT engine_block)
    message(FATAL_ERROR "engine source ownership target is missing")
endif()
string(FIND "${engine_block}" "RHI_CORE_SOURCES" engine_core_sources_offset)
if(engine_core_sources_offset EQUAL -1)
    message(FATAL_ERROR "engine must consume the complete RHI_CORE_SOURCES aggregate")
endif()
string(FIND "${engine_block}" "src/renderer/rt_trace.c" engine_rt_trace_offset)
if(engine_rt_trace_offset EQUAL -1)
    message(FATAL_ERROR "engine source ownership missing: src/renderer/rt_trace.c")
endif()
foreach(backend_source "src/rhi/rhi_gl.c" "src/rhi/rhi_vk.c" "src/rhi/rhi_headless.c")
    string(FIND "${engine_block}" "${backend_source}" engine_backend_offset)
    if(NOT engine_backend_offset EQUAL -1)
        message(FATAL_ERROR "engine must not own a backend source: ${backend_source}")
    endif()
endforeach()

# Each backend library owns exactly its own backend source.
foreach(backend_spec
        "engine_rhi_opengl|src/rhi/rhi_gl.c"
        "engine_rhi_vulkan|src/rhi/rhi_vk.c"
        "engine_rhi_headless|src/rhi/rhi_headless.c")
    string(REPLACE "|" ";" backend_parts "${backend_spec}")
    list(GET backend_parts 0 backend_target)
    list(GET backend_parts 1 backend_source)
    extract_cmake_command("${engine_cmake_text}"
        "add_library(${backend_target} STATIC" backend_block)
    if(NOT backend_block)
        message(FATAL_ERROR "RHI backend library is missing: ${backend_target}")
    endif()
    string(FIND "${backend_block}" "${backend_source}" own_offset)
    if(own_offset EQUAL -1)
        message(FATAL_ERROR
            "RHI backend library does not own its source: ${backend_target} ${backend_source}")
    endif()
    foreach(other_source "src/rhi/rhi_gl.c" "src/rhi/rhi_vk.c" "src/rhi/rhi_headless.c")
        if(NOT other_source STREQUAL backend_source)
            string(FIND "${backend_block}" "${other_source}" other_offset)
            if(NOT other_offset EQUAL -1)
                message(FATAL_ERROR
                    "RHI backend library owns a foreign backend source: ${backend_target} ${other_source}")
            endif()
        endif()
    endforeach()
endforeach()

# The selection helper must exist.
string(FIND "${engine_cmake_text}" "function(engine_link_rhi_backend" helper_offset)
if(helper_offset EQUAL -1)
    message(FATAL_ERROR "engine_link_rhi_backend helper is missing")
endif()

# Source-owning consumers keep their ownership; test_rhi_tlas_instance_encode
# must not pull the whole aggregate.
foreach(consumer_spec
        "engine|add_library(engine STATIC|RHI_CORE_SOURCES|src/core/log.c"
        "test_rhi_capabilities|add_executable(test_rhi_capabilities|RHI_CORE_SOURCES|tests/test_rhi_capabilities.c"
        "test_rhi_native|add_executable(test_rhi_native|RHI_CORE_SOURCES|tests/test_rhi_native.c"
        "test_rhi_tlas_instance_encode|add_executable(test_rhi_tlas_instance_encode|src/rhi/rhi_validation.c|tests/test_rhi_tlas_instance_encode.c"
        "test_rt_trace|add_executable(test_rt_trace|RHI_CORE_SOURCES|tests/test_rt_trace.c|src/renderer/rt_trace.c")
    string(REPLACE "|" ";" consumer_parts "${consumer_spec}")
    list(GET consumer_parts 0 consumer_name)
    list(GET consumer_parts 1 consumer_command)
    list(REMOVE_AT consumer_parts 0 1)
    extract_cmake_command("${engine_cmake_text}" "${consumer_command}" consumer_block)
    if(NOT consumer_block)
        message(FATAL_ERROR "RHI source ownership target is missing: ${consumer_name}")
    endif()
    foreach(required_consumer_source IN LISTS consumer_parts)
        string(FIND "${consumer_block}" "${required_consumer_source}" consumer_source_offset)
        if(consumer_source_offset EQUAL -1)
            message(FATAL_ERROR
                "RHI source ownership missing from ${consumer_name}: ${required_consumer_source}")
        endif()
    endforeach()
    if(consumer_name STREQUAL "test_rhi_tlas_instance_encode")
        string(FIND "${consumer_block}" "RHI_CORE_SOURCES" forbidden_core_sources_offset)
        if(NOT forbidden_core_sources_offset EQUAL -1)
            message(FATAL_ERROR
                "RHI source ownership unexpectedly shared with test_rhi_tlas_instance_encode")
        endif()
    endif()
endforeach()

# Direct RHI contract tests link exactly the headless backend and never the
# engine library (the word "engine" alone must not appear as a link item).
foreach(direct_rhi_target
        "test_rhi_capabilities"
        "test_rhi_native"
        "test_rt_trace"
        "test_rhi_error_contract"
        "test_rhi_frame_lifecycle_contract")
    extract_cmake_command("${engine_cmake_text}"
        "target_link_libraries(${direct_rhi_target}" direct_link_block)
    if(NOT direct_link_block)
        message(FATAL_ERROR
            "direct RHI test link ownership is missing: ${direct_rhi_target}")
    endif()
    string(FIND "${direct_link_block}" "engine_rhi_headless" headless_offset)
    if(headless_offset EQUAL -1)
        message(FATAL_ERROR
            "direct RHI test must link engine_rhi_headless: ${direct_rhi_target}")
    endif()
    if(direct_link_block MATCHES "(^|[ \t\r\n(])engine([ \t\r\n)])")
        message(FATAL_ERROR
            "direct RHI test must link its owned sources, not engine: ${direct_rhi_target}")
    endif()
endforeach()

# Every executable that links engine must select exactly one backend through
# the helper; no target link block may name two backend libraries.
foreach(rhi_consumer_target
        "engine_demo"
        "dxx_break"
        "test_vulkan"
        "test_engine_lifecycle"
        "test_platform_null_safety"
        "test_imgui_compat"
        "test_myui_break_pal"
        "test_platform_x11_runtime"
        "test_rhi_x11_runtime"
        "test_platform_wayland_runtime"
        "test_platform_win32_runtime"
        "test_platform_cocoa_runtime")
    string(FIND "${engine_cmake_text}"
        "engine_link_rhi_backend(${rhi_consumer_target})" helper_call_offset)
    if(helper_call_offset EQUAL -1)
        message(FATAL_ERROR
            "engine consumer must select a backend via the helper: ${rhi_consumer_target}")
    endif()
endforeach()
foreach(linked_target
        "engine_demo" "dxx_break" "test_vulkan" "test_engine_lifecycle"
        "test_platform_null_safety" "test_imgui_compat" "test_myui_break_pal"
        "test_platform_x11_runtime" "test_rhi_x11_runtime"
        "test_platform_wayland_runtime" "test_platform_win32_runtime"
        "test_platform_cocoa_runtime" "test_rhi_capabilities" "test_rhi_native"
        "test_rt_trace" "test_rhi_error_contract" "test_rhi_frame_lifecycle_contract")
    extract_cmake_command("${engine_cmake_text}"
        "target_link_libraries(${linked_target}" link_block)
    if(link_block)
        set(backend_link_count 0)
        foreach(backend_lib engine_rhi_opengl engine_rhi_vulkan engine_rhi_headless)
            string(FIND "${link_block}" "${backend_lib}" backend_lib_offset)
            if(NOT backend_lib_offset EQUAL -1)
                math(EXPR backend_link_count "${backend_link_count} + 1")
            endif()
        endforeach()
        if(backend_link_count GREATER 1)
            message(FATAL_ERROR
                "target links more than one RHI backend library: ${linked_target}")
        endif()
    endif()
endforeach()

# Future backends stay out of the build graph until plans C/D.
foreach(future_backend_token
        "rhi_metal.c" "ENGINE_RHI_BACKEND_METAL"
        "ENGINE_RHI_BACKEND_D3D12")
    string(FIND "${engine_cmake_text}" "${future_backend_token}" future_backend_offset)
    if(NOT future_backend_offset EQUAL -1)
        message(FATAL_ERROR
            "future backend is represented in current source ownership graph: ${future_backend_token}")
    endif()
endforeach()

# Backend internal contract surface (unchanged).
foreach(required_text
        "RHIResourceType"
        "RHIResourceSlot"
        "struct RHIDevice"
        "g_current_device"
        "rhi_alloc_slot"
        "rhi_get_resource_typed"
        "rhi_free_slot"
        "rhi_frame_owner_begin_backend"
        "rhi_frame_owner_begin_destroy"
        "rhi_frame_owner_is_current"
        "rhi_frame_owner_release"
        "rhi_device_control_try_acquire"
        "rhi_device_control_release")
    string(FIND "${internal_text}" "${required_text}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "backend internal contract missing: ${required_text}")
    endif()
endforeach()

string(FIND "${gl_text}" "rhi_backend_internal.h" gl_include_offset)
if(gl_include_offset EQUAL -1)
    message(FATAL_ERROR "OpenGL backend must include the private internal contract")
endif()
string(FIND "${vk_text}" "rhi_backend_internal.h" vk_include_offset)
if(vk_include_offset EQUAL -1)
    message(FATAL_ERROR "Vulkan backend must include the private internal contract")
endif()
string(FIND "${rhi_text}" "rhi_backend_internal.h" rhi_include_offset)
if(rhi_include_offset EQUAL -1)
    message(FATAL_ERROR "rhi.c must include the private internal contract explicitly")
endif()
```

同时把 `engine/CMakeLists.txt` 中该测试的注册块（当前 :2091-2106）加上一行 `-DRHI_HEADLESS_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_headless.c`（其余 `-D` 参数不变）。

- [ ] **Step 2: 运行验证失败**

```bash
cmake -S engine -B build-gate
ctest --test-dir build-gate -R '^test_rhi_backend_internal_contract$' --output-on-failure
```

预期：FAIL，首个失败信息为 `rhi.c must not unity-include a backend: #include <rhi/rhi_vk.c>`（或 `#include <rhi/rhi_gl.c>`，取决于构建配置）。

- [ ] **Step 3: 创建 rhi_headless.c（fail-closed 完整骨架）**

创建 `engine/src/rhi/rhi_headless.c`，完整内容（覆盖 rhi.h + rhi_native_vulkan.h 中全部非 core 拥有的 `rhi_*` 符号；core 已拥有的——`*_ex` wrapper、`*_desc_validate`、`rhi_present_history_*`、注入钩子——不在此文件重复定义）：

```c
/* engine_rhi_headless: fail-closed RHI backend (multi-backend RHI spec §4.1).
 * Every entry point refuses work: no GPU, no surface, no evidence. This
 * library exists so headless contract tests can link the full rhi_* symbol
 * surface without a real backend; it must never be cited as GPU evidence. */
#include <rhi/rhi.h>
#include <rhi/rhi_native_vulkan.h>

#include <string.h>

/* ---- device lifecycle ---- */
RHIDevice *rhi_device_create(RHIBackend backend, void *window_native,
                             void *display_native, u32 w, u32 h) {
    (void)backend; (void)window_native; (void)display_native; (void)w; (void)h;
    return NULL;
}
void rhi_device_destroy(RHIDevice *dev) { (void)dev; }
void rhi_device_resize(RHIDevice *dev, u32 w, u32 h) {
    (void)dev; (void)w; (void)h;
}
RHICmdBuffer *rhi_frame_begin(RHIDevice *dev) { (void)dev; return NULL; }
void rhi_frame_end(RHIDevice *dev) { (void)dev; }
void rhi_present(RHIDevice *dev) { (void)dev; }
void rhi_set_vsync(RHIDevice *dev, bool enabled) { (void)dev; (void)enabled; }
u32 rhi_frame_index(RHIDevice *dev) { (void)dev; return 0u; }
bool rhi_device_idle(RHIDevice *dev) { (void)dev; return false; }
/* Fail closed: a live device handle on the headless backend is a bug;
 * reporting lost forces callers to wind down instead of spinning. */
bool rhi_device_lost(RHIDevice *dev) { (void)dev; return true; }

/* ---- backend native interop (declared in rhi_native_vulkan.h) ---- */
bool rhi_backend_get_native_device(const RHIDevice *dev, RHINativeDevice *out) {
    (void)dev; (void)out; return false;
}
bool rhi_backend_get_device_info(const RHIDevice *dev, RHIDeviceInfo *out) {
    (void)dev; (void)out; return false;
}
bool rhi_backend_texture_get_native_info(const RHIDevice *dev,
                                         RHITexture texture,
                                         RHITextureNativeInfo *out) {
    (void)dev; (void)texture; (void)out; return false;
}
bool rhi_backend_cmd_buffer_get_native_info(const RHIDevice *dev,
                                            const RHICmdBuffer *cmd,
                                            RHICmdBufferNativeInfo *out) {
    (void)dev; (void)cmd; (void)out; return false;
}
bool rhi_backend_cmd_build_blas_one_triangle(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure blas,
    const RHIBLASOneTriangleDesc *desc,
    RHIBuffer scratch_buffer, usize scratch_offset) {
    (void)cmd; (void)dev; (void)blas; (void)desc;
    (void)scratch_buffer; (void)scratch_offset;
    return false;
}
u64 rhi_backend_acceleration_structure_get_device_address(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    (void)dev; (void)structure; return 0u;
}
bool rhi_backend_tlas_one_instance_get_build_sizes(
    RHIDevice *dev, RHIBuffer instance_buffer,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    (void)dev; (void)instance_buffer; (void)out_sizes; return false;
}
bool rhi_backend_cmd_build_tlas_one_instance(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure tlas,
    RHIBuffer instance_buffer, RHIBuffer scratch_buffer, usize scratch_offset) {
    (void)cmd; (void)dev; (void)tlas; (void)instance_buffer;
    (void)scratch_buffer; (void)scratch_offset;
    return false;
}
bool rhi_backend_acceleration_structure_get_vk_handle(
    RHIDevice *dev, RHIAccelerationStructure structure, void **out_handle) {
    (void)dev; (void)structure; (void)out_handle; return false;
}
bool rhi_blas_one_triangle_get_build_sizes(
    RHIDevice *dev, const RHIBLASOneTriangleDesc *desc,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    (void)dev; (void)desc; (void)out_sizes; return false;
}
RHIAccelerationStructure rhi_backend_acceleration_structure_create(
    RHIDevice *dev, const RHIAccelerationStructureDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_backend_acceleration_structure_destroy(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    (void)dev; (void)structure;
}

u32 rhi_vk_validation_message_count(void) { return 0u; }
void rhi_vk_validation_message_count_reset(void) {}
bool rhi_vk_validation_gate_active(void) { return false; }
void rhi_vk_validation_set_enabled(bool enabled) { (void)enabled; }

/* ---- resource creation ---- */
RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len,
                            bool is_fragment) {
    (void)dev; (void)source; (void)len; (void)is_fragment;
    return RHI_HANDLE_NULL;
}
RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source,
                                    usize len) {
    (void)dev; (void)source; (void)len; return RHI_HANDLE_NULL;
}
void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    (void)dev; (void)shader;
}
RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    (void)dev; (void)pipe;
}
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    (void)dev; (void)tex;
}
RHITexture rhi_texture_array_create(RHIDevice *dev, u32 width, u32 height,
                                    u32 layers, RHIFormat fmt) {
    (void)dev; (void)width; (void)height; (void)layers; (void)fmt;
    return RHI_HANDLE_NULL;
}
void rhi_texture_array_upload_layer(RHIDevice *dev, RHITexture tex, u32 layer,
                                    const void *rgba8, usize size) {
    (void)dev; (void)tex; (void)layer; (void)rgba8; (void)size;
}
bool rhi_texture_get_size(RHIDevice *dev, RHITexture tex, u32 *out_w,
                          u32 *out_h) {
    (void)dev; (void)tex; (void)out_w; (void)out_h; return false;
}
bool rhi_texture_read_pixels(RHIDevice *dev, RHITexture tex, void *dst_rgba8,
                             usize size) {
    (void)dev; (void)tex; (void)dst_rgba8; (void)size; return false;
}
void rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level,
                            u32 width, u32 height, const void *data,
                            usize size) {
    (void)dev; (void)tex; (void)mip_level; (void)width; (void)height;
    (void)data; (void)size;
}
RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    (void)dev; (void)sampler;
}

/* ---- command recording ---- */
void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    (void)cmd; (void)pipe;
}
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                usize offset) {
    (void)cmd; (void)buf; (void)offset;
}
void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                               bool is_u32) {
    (void)cmd; (void)buf; (void)offset; (void)is_u32;
}
void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h,
                          f32 min_depth, f32 max_depth) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h; (void)min_depth;
    (void)max_depth;
}
void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_set_scissor_top_left(RHICmdBuffer *cmd, u32 x, u32 y, u32 w,
                                  u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w,
                                 u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    (void)cmd; (void)vertex_count; (void)instance_count;
}
void rhi_cmd_draw_base(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count,
                       u32 first_vertex) {
    (void)cmd; (void)vertex_count; (void)instance_count; (void)first_vertex;
}
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count,
                          u32 instance_count) {
    (void)cmd; (void)index_count; (void)instance_count;
}
void rhi_cmd_draw_indexed_base(RHICmdBuffer *cmd, u32 index_count,
                               u32 instance_count, u32 first_index,
                               i32 vertex_offset) {
    (void)cmd; (void)index_count; (void)instance_count; (void)first_index;
    (void)vertex_offset;
}
void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                           u32 draw_count, u32 stride) {
    (void)dev; (void)cmd_buf; (void)offset; (void)draw_count; (void)stride;
}
void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf,
                                   u32 offset, u32 draw_count, u32 stride) {
    (void)dev; (void)cmd_buf; (void)offset; (void)draw_count; (void)stride;
}
void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf,
                                         u32 cmd_offset, RHIBuffer count_buf,
                                         u32 count_offset, u32 max_draws,
                                         u32 stride) {
    (void)dev; (void)cmd_buf; (void)cmd_offset; (void)count_buf;
    (void)count_offset; (void)max_draws; (void)stride;
}
void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a) {
    (void)cmd; (void)r; (void)g; (void)b; (void)a;
}
void rhi_cmd_clear_color_attachment(RHICmdBuffer *cmd, u32 attachment, f32 r,
                                    f32 g, f32 b, f32 a) {
    (void)cmd; (void)attachment; (void)r; (void)g; (void)b; (void)a;
}
void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex,
                          RHISampler sampler, u32 unit) {
    (void)cmd; (void)tex; (void)sampler; (void)unit;
}
void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex,
                                 RHISampler sampler) {
    (void)cmd; (void)shadow_tex; (void)sampler;
}
void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                 u32 binding) {
    (void)cmd; (void)buf; (void)binding;
}
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    (void)cmd; (void)location; (void)m;
}
void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y,
                              f32 z) {
    (void)cmd; (void)location; (void)x; (void)y; (void)z;
}
void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    (void)cmd; (void)location; (void)x; (void)y;
}
void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y,
                              f32 z, f32 w) {
    (void)cmd; (void)location; (void)x; (void)y; (void)z; (void)w;
}
void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    (void)cmd; (void)location; (void)v;
}
void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    (void)cmd; (void)location; (void)v;
}
void rhi_cmd_push_constants(RHICmdBuffer *cmd, u32 offset, const void *data,
                            u32 size) {
    (void)cmd; (void)offset; (void)data; (void)size;
}
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location,
                               const void *data, u32 size) {
    (void)cmd; (void)location; (void)data; (void)size;
}
i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe,
                                      const char *name) {
    (void)dev; (void)pipe; (void)name; return -1;
}

/* ---- shadow map / cubemap / FBO ---- */
RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    RHIShadowMap out;
    (void)dev; (void)width; (void)height;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm) {
    (void)dev; (void)sm;
}
void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    (void)cmd; (void)sm;
}
void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}
void rhi_cmd_clear_depth(RHICmdBuffer *cmd) { (void)cmd; }
RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    (void)dev; (void)cm;
}
void rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm) {
    (void)dev; (void)cm;
}
void rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex) {
    (void)dev; (void)tex;
}
void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm,
                          RHISampler sampler, u32 unit) {
    (void)cmd; (void)cm; (void)sampler; (void)unit;
}
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd; (void)enabled;
}
void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd; (void)enabled;
}

/* ---- buffers / texel ---- */
void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0,
                                RHIBuffer buf1) {
    (void)cmd; (void)buf0; (void)buf1;
}
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data,
                       usize size) {
    (void)dev; (void)buf; (void)data; (void)size;
}
void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset,
                              const void *data, usize size) {
    (void)dev; (void)buf; (void)offset; (void)data; (void)size;
}
bool rhi_buffer_read(RHIDevice *dev, RHIBuffer buf, void *dst, usize offset,
                     usize size) {
    (void)dev; (void)buf; (void)dst; (void)offset; (void)size; return false;
}
void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                         usize size, u32 value) {
    (void)cmd; (void)buf; (void)offset; (void)size; (void)value;
}
void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                           const void *data, usize size) {
    (void)cmd; (void)buf; (void)offset; (void)data; (void)size;
}
void *rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    (void)dev; (void)buf; return NULL;
}
void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
void rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst,
                         usize size) {
    (void)cmd; (void)src; (void)dst; (void)size;
}

/* ---- material texture binders ---- */
void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd, RHITexture albedo,
    RHITexture mr, RHITexture normal, RHITexture emissive, RHITexture shadow,
    RHITexture ssao, RHISampler sampler) {
    (void)cmd; (void)albedo; (void)mr; (void)normal; (void)emissive;
    (void)shadow; (void)ssao; (void)sampler;
}
void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd, RHITexture albedo,
    RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture occlusion, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count) {
    (void)cmd; (void)albedo; (void)mr; (void)normal; (void)emissive;
    (void)occlusion; (void)shadow; (void)ssao; (void)sampler; (void)brdf_lut;
    (void)irradiance_map; (void)prefilter_map; (void)point_shadow_cubes;
    (void)point_shadow_count;
}
void rhi_cmd_bind_deferred_gbuf_textures(RHICmdBuffer *cmd,
    RHITexture albedo_metallic, RHITexture roughness_ao, RHITexture normal,
    RHITexture depth, RHITexture emissive, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count, RHISampler cube_sampler) {
    (void)cmd; (void)albedo_metallic; (void)roughness_ao; (void)normal;
    (void)depth; (void)emissive; (void)shadow; (void)ssao; (void)sampler;
    (void)brdf_lut; (void)irradiance_map; (void)prefilter_map;
    (void)point_shadow_cubes; (void)point_shadow_count; (void)cube_sampler;
}
void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd, RHITexture *textures,
                                 int count, RHISampler sampler) {
    (void)cmd; (void)textures; (void)count; (void)sampler;
}

/* ---- offscreen / MRT / depth-cube FBO ---- */
RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width,
                                         u32 height) {
    RHIOffscreenFBO out;
    (void)dev; (void)width; (void)height;
    memset(&out, 0, sizeof(out));
    return out;
}
RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width,
                                             u32 height, RHIFormat color_fmt) {
    RHIOffscreenFBO out;
    (void)dev; (void)width; (void)height; (void)color_fmt;
    memset(&out, 0, sizeof(out));
    return out;
}
RHIOffscreenFBO rhi_offscreen_fbo_create_desc(RHIDevice *dev,
                                              const RHIOffscreenFBODesc *desc) {
    RHIOffscreenFBO out;
    (void)dev; (void)desc;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    (void)dev; (void)fbo;
}
void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_offscreen_fbo_bind_load(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}
void rhi_offscreen_fbo_set_clear_color(RHIDevice *dev, RHIOffscreenFBO *fbo,
                                       f32 r, f32 g, f32 b, f32 a) {
    (void)dev; (void)fbo; (void)r; (void)g; (void)b; (void)a;
}
RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height,
                             const RHIFormat *formats, u32 attachment_count) {
    RHIMRTFBO out;
    (void)dev; (void)width; (void)height; (void)formats;
    (void)attachment_count;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo) {
    (void)dev; (void)fbo;
}
void rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_mrt_fbo_bind_load(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}
RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size) {
    RHICubemapDepthFBO out;
    (void)dev; (void)size;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo) {
    (void)dev; (void)fbo;
}
void rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd,
                                     RHICubemapDepthFBO *fbo, u32 face) {
    (void)cmd; (void)fbo; (void)face;
}
void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w,
                                  u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}

/* ---- compute ---- */
void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    (void)cmd; (void)x; (void)y; (void)z;
}
void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                 u32 binding) {
    (void)cmd; (void)buf; (void)binding;
}
void rhi_cmd_bind_acceleration_structure(RHICmdBuffer *cmd,
                                         RHIAccelerationStructure structure,
                                         u32 binding) {
    (void)cmd; (void)structure; (void)binding;
}
void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit,
                                u32 mip_level, bool write_only) {
    (void)cmd; (void)tex; (void)unit; (void)mip_level; (void)write_only;
}
void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm,
                                     u32 face, u32 mip, u32 unit,
                                     bool write_only) {
    (void)cmd; (void)cm; (void)face; (void)mip; (void)unit; (void)write_only;
}
void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm,
                                  RHISampler sampler, u32 unit) {
    (void)cmd; (void)cm; (void)sampler; (void)unit;
}
void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex,
                              RHISampler sampler, u32 unit, u32 mip_level) {
    (void)cmd; (void)tex; (void)sampler; (void)unit; (void)mip_level;
}
void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex,
                                  RHISampler sampler, u32 unit) {
    (void)cmd; (void)tex; (void)sampler; (void)unit;
}
void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd,
                                      RHITexture depth_tex) {
    (void)cmd; (void)depth_tex;
}

/* ---- screenshot ---- */
bool rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels,
                    usize pixel_bytes) {
    (void)dev; (void)x; (void)y; (void)w; (void)h; (void)pixels;
    (void)pixel_bytes;
    return false;
}

/* ---- GPU timer ---- */
RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev) { (void)dev; return NULL; }
void rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t) {
    (void)dev; (void)t;
}
void rhi_gpu_timer_begin(RHIGPUTimer *t) { (void)t; }
void rhi_gpu_timer_end(RHIGPUTimer *t) { (void)t; }
f64 rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t) { (void)t; return 0.0; }

/* ---- ENGINE_RHI_TEST hooks (GL cache owner contract, headless flavor) ---- */
#ifdef ENGINE_RHI_TEST
static RHIDevice *g_headless_gl_cache_owner;
void rhi_test_gl_cache_sync(RHIDevice *dev) { g_headless_gl_cache_owner = dev; }
RHIDevice *rhi_test_gl_cache_owner(void) { return g_headless_gl_cache_owner; }
#endif
```

- [ ] **Step 4: 删除 unity-include 并拆分 CMake**

4a. 删除 `engine/src/rhi/rhi.c:408-415` 的整个 `#ifdef ENGINE_VULKAN … #endif` unity-include 块（rhi.c 保留调度/校验/`*_ex`/测试钩子）。

4b. `engine/CMakeLists.txt` 编辑（混合行尾，新块用 LF）：

(i) :443 `target_link_libraries(engine PRIVATE glad lua stb_image)` 改为 `target_link_libraries(engine PRIVATE lua stb_image)`（glad 只被 rhi_gl.c 使用，归 `engine_rhi_opengl`；先用 `grep -rn "glad" engine/src --include='*.c' | grep -v rhi_gl` 确认 engine 内无其他 glad 消费点，若有则 glad 保留在 engine 并在 commit message 记录原因）。

(ii) :345-351 的 `if(SHADERC_INCLUDE_DIR) target_include_directories(engine PRIVATE ${SHADERC_INCLUDE_DIR})` 整块移到 `engine_rhi_vulkan` 定义处（见 (iv)；先 `grep -rln "shaderc" engine/src --include='*.c' | grep -v rhi_vk` 确认只有 rhi_vk.c 需要）。

(iii) 平台链接块瘦身（engine 不再链接后端图形库）：
- linux :982-1004：两个 `if(ENGINE_VULKAN)` 分支中的 `${Vulkan_LIBRARIES} ${SHADERC_LIB}` 删除；两个 GL 分支中的 `GL`（以及 wayland 分支的 `EGL`）删除；`${ENGINE_X11_LIBS}`/`${WAYLAND_LIBRARIES}`/`${XKB_LIBRARIES}`/`dl`/`pthread` 保留在 engine（window_*.c 需要）。
- windows :1013-1019：`Vulkan::Vulkan ${SHADERC_LIB}` 与 `opengl32` 删除（`gdi32` 保留给 window_win32.c）。
- macos :1045-1054：`Vulkan::Vulkan ${SHADERC_LIB}` 删除，frameworks 保留（window_cocoa.m 需要）。
- 移动平台 :1077-1084：`Vulkan::Vulkan ${SHADERC_LIB}` 删除，`dl`/`android` 保留；harmonyos FATAL_ERROR（:1073-1075）不动。

(iv) 后端库与 helper 的插入必须拆成两处（CMake 顺序约束：`dxx_break` 在 :792 就调用 helper，而后端平台链接依赖 linux 块 :988 才定义的 `${ENGINE_X11_LIBS}`）：

(iv-a) 在 `glad` 库定义块（:400-407）**之后**插入 target 定义与 helper（此处 `engine`（:244）、`glad`、`Vulkan::Vulkan`/`${SHADERC_LIB}`（:222-235 已 find）均已就绪，且早于第一个 helper 调用点 dxx_break :792）：

```cmake
# --- RHI backend libraries (multi-backend spec §4.8) ---
# Each backend compiles as its own static library exporting the same rhi_*
# symbol set; an executable links engine plus exactly one backend library via
# engine_link_rhi_backend(). EXCLUDE_FROM_ALL keeps the non-selected backend
# out of the default build (nothing references it). engine_rhi_headless is
# always built: the direct-source RHI contract tests link it unconditionally.
add_library(engine_rhi_opengl STATIC EXCLUDE_FROM_ALL src/rhi/rhi_gl.c)
target_include_directories(engine_rhi_opengl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)
target_link_libraries(engine_rhi_opengl PUBLIC engine PRIVATE glad)

add_library(engine_rhi_headless STATIC src/rhi/rhi_headless.c)
target_include_directories(engine_rhi_headless PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(ENGINE_VULKAN OR ENGINE_PLATFORM STREQUAL "macos")
    add_library(engine_rhi_vulkan STATIC EXCLUDE_FROM_ALL src/rhi/rhi_vk.c)
    target_include_directories(engine_rhi_vulkan PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)
    if(SHADERC_INCLUDE_DIR)
        target_include_directories(engine_rhi_vulkan PRIVATE ${SHADERC_INCLUDE_DIR})
    endif()
    target_compile_definitions(engine_rhi_vulkan PRIVATE ENGINE_VULKAN=1)
    target_link_libraries(engine_rhi_vulkan PUBLIC engine
        PRIVATE Vulkan::Vulkan ${SHADERC_LIB})
endif()

# Link exactly one RHI backend into a consumer executable. Headless
# contract tests do NOT call this helper; they link engine_rhi_headless.
function(engine_link_rhi_backend target)
    if(ENGINE_PLATFORM STREQUAL "macos" OR
       ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "vulkan")
        target_link_libraries(${target} PRIVATE engine_rhi_vulkan)
    elseif(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "opengl")
        target_link_libraries(${target} PRIVATE engine_rhi_opengl)
    else()
        message(FATAL_ERROR
            "engine_link_rhi_backend: no backend library for ENGINE_RHI_BACKEND_EFFECTIVE=${ENGINE_RHI_BACKEND_EFFECTIVE}")
    endif()
endfunction()
```

(iv-b) 在平台链接块 `endif()`（当前 :1085）与 `# Executable`（当前 :1087）之间插入后端平台链接（此处 `${ENGINE_X11_LIBS}` 已定义）：

```cmake
# Backend-side platform libraries (moved off engine, which no longer
# compiles any backend source).
if(ENGINE_PLATFORM STREQUAL "linux")
    if(ENGINE_ENABLE_WAYLAND)
        target_link_libraries(engine_rhi_opengl PRIVATE
            ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} GL EGL dl pthread)
        if(TARGET engine_rhi_vulkan)
            target_link_libraries(engine_rhi_vulkan PRIVATE
                ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} dl pthread)
        endif()
    else()
        target_link_libraries(engine_rhi_opengl PRIVATE
            ${ENGINE_X11_LIBS} GL dl pthread)
        if(TARGET engine_rhi_vulkan)
            target_link_libraries(engine_rhi_vulkan PRIVATE
                ${ENGINE_X11_LIBS} dl pthread)
        endif()
    endif()
elseif(ENGINE_PLATFORM STREQUAL "windows")
    target_link_libraries(engine_rhi_opengl PRIVATE opengl32)
elseif(ENGINE_PLATFORM STREQUAL "macos")
    target_link_libraries(engine_rhi_vulkan PRIVATE
        "-framework Cocoa" "-framework QuartzCore" "-framework Metal"
        "-framework IOKit")
elseif(ENGINE_PLATFORM STREQUAL "ios" OR ENGINE_PLATFORM STREQUAL "android" OR
       ENGINE_PLATFORM STREQUAL "harmonyos")
    if(TARGET engine_rhi_vulkan)
        target_link_libraries(engine_rhi_vulkan PRIVATE dl)
        if(ENGINE_PLATFORM STREQUAL "android")
            target_link_libraries(engine_rhi_vulkan PRIVATE android)
        endif()
    endif()
endif()
```

说明：macOS 走 MoltenVK（`ENGINE_VULKAN` option 在 macOS 上不置 ON 但 engine 有 PUBLIC `ENGINE_VULKAN=1` define，:1031），所以 helper 在 macOS 无条件选 `engine_rhi_vulkan`；后端库与 engine 之间是静态库环依赖（后端回调 rhi.c 的 `rhi_alloc_slot` 等，`PUBLIC engine` 声明后 CMake 会在链接行重复列库解决）。

4c. 每个链接 engine 的可执行 target 在其 `target_link_libraries(...)` 行之后加一行 `engine_link_rhi_backend(<name>)`。完整清单（用 `grep -n "target_link_libraries(.*engine" engine/CMakeLists.txt` 复核）：

| target | target_link_libraries 当前行 |
|---|---|
| `dxx_break` | :792 |
| `engine_demo` | :1089 |
| `test_vulkan` | :1116 |
| `test_engine_lifecycle` | :1573 |
| `test_platform_null_safety` | :1578 |
| `test_platform_x11_runtime` | :1594（linux） |
| `test_rhi_x11_runtime` | :1601（linux GL） |
| `test_platform_wayland_runtime` | :1612（linux wayland） |
| `test_platform_win32_runtime` | :1623 |
| `test_platform_cocoa_runtime` | :1635 |
| `test_imgui_compat` | :1647 |
| `test_myui_break_pal` | :1706 |

（`break_myui` 是静态库，不需要链接解析，不加。）

4d. 五个 direct-source RHI 测试（`test_rhi_capabilities` :1824-1880、`test_rhi_native` :1882-1931、`test_rhi_error_contract`、`test_rhi_frame_lifecycle_contract`、`test_rt_trace` :2420-2462）：把各自的**所有**链接语句（`test_rhi_capabilities`/`test_rhi_native`/两个新契约测试各是一整段平台 `if/elseif` 链接链；`test_rt_trace` 有两处——`:2432` 附近的 `if(ENGINE_VULKAN)` 链接块含 `${Vulkan_LIBRARIES} ${SHADERC_LIB}`，以及 `:2442` 附近的平台 `if/elseif` 链含 `glad opengl32`/`GL`/frameworks——连同其中只服务后端链接的 `target_include_directories(... ${SHADERC_INCLUDE_DIR})` 行）整体替换为单行：

```cmake
    target_link_libraries(<name> PRIVATE engine_rhi_headless m)
```

保留各测试的 `add_executable`/`ENGINE_RHI_TEST=1`/include/平台 define/`add_test`/labels 不动；`test_rhi_capabilities` 的 `-ffunction-sections`/`--gc-sections` 选项保留；`test_rt_trace` 的 `if(ENGINE_VULKAN)` define 块可保留（只影响 rt_trace.c 的条件编译，不再拉后端库）。

- [ ] **Step 5: 构建并修复后端独立 TU 的编译问题**

```bash
cmake -S engine -B build-gate
cmake --build build-gate --parallel
```

预期可能出现的失败与修复路径：rhi_gl.c/rhi_vk.c 此前作为 unity TU 依赖 rhi.c 顶部的 `#include <stdlib.h>`/`<string.h>`/`<stdatomic.h>`/`<core/log.h>`——独立编译若报缺符号，在该后端文件**顶部补标准 include**（只加 include，不改逻辑、不改 flags）。链接期若报 `undefined reference` 指向 engine 内符号（如 `rhi_device_set_lifecycle_result`），确认该符号在 `rhi_backend_internal.h` 有 extern 声明；缺声明则补在 `rhi_backend_internal.h`（这属于内部契约扩展，同步核对 Step 1 契约测试的符号清单无需变更）。任何「把后端源重新加回 engine」的修法都禁止。

- [ ] **Step 6: 全量验证转绿**

```bash
ctest --test-dir build-gate -R '^test_rhi_backend_internal_contract$' --output-on-failure
ctest --test-dir build-gate -R '^test_rhi_backend_selection$' --output-on-failure
ctest --test-dir build-gate -LE "graphics|fuzz" --output-on-failure
cmake -S engine -B build-win-vk
cmake --build build-win-vk --parallel
ctest --test-dir build-win-vk -R '^test_rhi_backend_internal_contract$' --output-on-failure
ctest --test-dir build-win-vk -LE "graphics|fuzz" --output-on-failure
```

预期：全部 PASS（`test_rhi_backend_selection` 应保持既有语义：metal/d3d12 configure 仍 FATAL_ERROR，本 Task 未改选择器）。若 `test_rhi_native`/`test_rhi_capabilities` 在 headless 后端下断言失败，只允许调整 `rhi_headless.c` 的 fail-closed 语义使其与「无 backend 设备」既有行为一致（例如 native info 返回 false），禁止放宽测试断言。

- [ ] **Step 7: Commit**

```bash
git add engine/src/rhi/rhi.c engine/src/rhi/rhi_headless.c engine/CMakeLists.txt \
  engine/tests/test_rhi_backend_internal_contract.cmake
git add engine/src/rhi/rhi_gl.c engine/src/rhi/rhi_vk.c engine/src/rhi/rhi_backend_internal.h
git commit -m "rhi: split backends into engine_rhi_{opengl,vulkan,headless} static libraries"
```

（`git add` 第二行仅当 Step 5 实际改了这些文件；以 `git status` 为准。）

---

### Task 7: 文档与 CI 骨架

**Files:**
- Create: `docs/vulkan_support_matrix.md`、`docs/rhi_metal_d3d12_feature_matrix.md`、`docs/rhi_rollback_runbook.md`、`docs/rhi_benchmark_receipt_schema.md`
- Modify: `README.md`（后端矩阵与构建入口段落）、`docs/Build_Guide.md`（新增「RHI 后端链接模型」一节）、`docs/Architecture_Overview.md`（新增 RHI 分层图段落）
- Modify: `.github/workflows/ci.yml`（顶部注释块，紧跟 `name: CI` 之后；不加新 job）

**Interfaces:**
- Consumes: Task 2 的 `docs/rhi_backend_evidence.md`；Task 6 的 `engine_link_rhi_backend`；规格 §1.1/§4.7/§8。
- Produces: 规格 §8.1 文档清单中的四个新文档；ci.yml 的六类 lane 注释约定。

- [ ] **Step 1: 新建 docs/vulkan_support_matrix.md**

完整内容：

```markdown
# Vulkan 支持矩阵

证据等级定义与收据规则见 `docs/rhi_backend_evidence.md`；本表只列 Vulkan 形态的后端，原生 Metal/D3D12 见 `docs/rhi_metal_d3d12_feature_matrix.md`。

| 平台 | Vulkan 形态 | 证据等级 | 依据/收据 |
|---|---|---|---|
| Linux X11 | 原生 Vulkan | GPU_RUNTIME（lavapipe/llvmpipe 软渲染） | CI `vk` / `linux-graphics-smoke` lane |
| Linux Wayland | 原生 Vulkan | NATIVE_SURFACE | CI `wayland-vk`（weston headless） |
| Windows | 原生 Vulkan | GPU_RUNTIME | 本机 `build-win-vk/` + CI `windows-clang` |
| macOS | MoltenVK | GPU_RUNTIME | CI `macos-vulkan`（133/133 CTest, 2026-10-13）；**不计入原生 Metal 证据** |
| iOS | MoltenVK（host-injected CAMetalLayer） | COMPILED | `engine/src/platform/platform_compat.h:86-95`；模拟器不计 GPU_RUNTIME |
| Android | 原生 Vulkan（host-injected ANativeWindow） | COMPILED | `engine/src/rhi/rhi_vk.c:1482-1700` |
| OHOS (HarmonyOS) | — | NONE（UNAVAILABLE，fail-closed） | `engine/CMakeLists.txt` harmonyos FATAL_ERROR |

## 说明

- Shader 路径：GLSL → SPIR-V，运行时 shaderc（target env Vulkan 1.2 / SPIR-V 1.5），见规格 §4.7。
- 软渲染（lavapipe/llvmpipe）收据必须在台账行内注明「软渲染」，不得与硬件 GPU 收据混用。
- 已知 NVIDIA 616.56 混合 GPU 异常只登记在规格 §7，不进入本表。
```

- [ ] **Step 2: 新建 docs/rhi_metal_d3d12_feature_matrix.md**

完整内容：

```markdown
# Metal / D3D12 特性矩阵（规划态）

两个后端的公开入口均为现有 `rhi_*` 符号集（`engine/src/rhi/rhi.h`）；本表跟踪各特性面在后端内的落地状态。状态枚举：NONE（无代码）/ PLANNED（已排期）/ HEADLESS / NATIVE_SURFACE / GPU_RUNTIME / BENCHMARK_COMPARABLE。

| 特性面 | Metal（计划 C） | D3D12（计划 D） |
|---|---|---|
| 设备创建 / 销毁 | PLANNED（MTLDevice/MTLCommandQueue） | HEADLESS（`rhi_d3d12.c/h` gate 契约） |
| Surface / swapchain | PLANNED（`platform_surface_native()` 返回 CAMetalLayer） | PLANNED（HWND → DXGI swapchain） |
| Render pass / pipeline contract | PLANNED（消费 `RHIPipelineDesc` capability contract 字段） | PLANNED |
| Push constants / 绑定模型 | PLANNED（`rhi_cmd_push_constants` → setBytes 映射） | PLANNED（root constants） |
| Compute / storage | PLANNED | PLANNED |
| 加速结构（BLAS/TLAS） | PLANNED（`rhi_acceleration_structure_get_vk_handle` 不适用；后端内转换，公开 ABI 不变） | PLANNED（同上） |
| Present damage / buffer age | PLANNED | PLANNED |
| 验证 gate | PLANNED（Metal validation layer） | PLANNED（DRED + debug layer） |
| Shader 路径 | MSL：`metal-shaderconverter` 或手写 MSL + `xcrun metal` → `.metallib`（构建期） | HLSL → DXIL：dxc（沿用 `test_d3d12_shader_compile_gate` 的 dxc 定位），SDK 版本锁定在计划 F |
| 当前证据等级 | NONE | HEADLESS（contract/gate only，未接入 `RHIBackend`） |

## 纪律

- 禁止用 MoltenVK 冒充原生 Metal 证据，禁止用 D3D11On12 / GL wrapper 冒充 D3D12（规格 §1.2）。
- 本表任何等级提升必须同步更新 `docs/rhi_backend_evidence.md` 并附收据。
```

- [ ] **Step 3: 新建 docs/rhi_rollback_runbook.md**

完整内容：

```markdown
# RHI 回滚与 Device-Loss Runbook

## 回滚触发条件（任一成立即启动回滚评估）

- 合并后任一平台 headless 套件（`ctest -LE "graphics|fuzz"`）在 CI 上转红且无法在当日修复；
- `GPU_RUNTIME` 证据行对应的 CI lane 连续两次失败且排除基础设施原因；
- 后端拆分/迁移导致某平台可执行文件链接失败且当日无修复路径。

## 回滚步骤

1. 定位引入 commit（`git log --oneline` + CI history），优先 `git revert` 最小范围 commit；
2. 回滚后在 `docs/rhi_backend_evidence.md` 对应行记录等级回退与原因（降级也是证据变更，必须留收据）；
3. 重新跑两个本机构建目录的 headless 套件确认绿；
4. 在规格 §7 风险登记中新增或更新对应风险条目。

## Device-loss 处置（运行时）

- `RHI_RESULT_DEVICE_LOST` 是 sticky latch（`rhi_device_lost`）：一旦出现，所有阻塞等待 fail-fast，应用层应收束退出而非重试。
- Windows D3D12 路径（计划 D）需采集 DRED；Vulkan 路径记录 validation 计数（`rhi_vk_validation_message_count`）。
- 已知异常隔离：NVIDIA 616.56 混合 GPU 上的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1} 异常不作为源码修复依据；必须在健康设备独立复现后才立项（规格 §7）。

## 禁止事项

- 禁止把编译成功（COMPILED）当作 GPU_RUNTIME 证据上报；
- 禁止以删除/跳过测试的方式让套件转绿；
- 禁止在未冻结的临时 artifacts（`.scratch-vkprobe/`、`.tmp/` 等）上建立回滚依赖。
```

- [ ] **Step 4: 新建 docs/rhi_benchmark_receipt_schema.md**

完整内容：

````markdown
# RHI Benchmark Receipt Schema

每次证据等级升级到 `GPU_RUNTIME` 或 `BENCHMARK_COMPARABLE` 必须附一份符合本 schema 的 JSON 收据（benchmark 类）；其他等级升级收据至少包含相同的环境字段（metrics 可为 null）。字段级校验脚本随计划 F 入 CI。

## 字段定义

| 字段 | 类型 | 必填 | 说明 |
|---|---|---|---|
| `schema_version` | integer | 是 | 当前固定为 1 |
| `timestamp` | string | 是 | ISO 8601 UTC（如 `2026-10-14T12:00:00Z`） |
| `platform` | string | 是 | `linux-x11` / `linux-wayland` / `windows` / `macos` / `ios` / `android` / `ohos` |
| `os_version` | string | 是 | 操作系统与版本（如 `Ubuntu 24.04`） |
| `backend` | string | 是 | `opengl` / `vulkan` / `metal` / `d3d12` / `vulkan-moltenvk` |
| `gpu` | string | 是 | GPU 型号；软渲染必须注明（如 `llvmpipe (LLVM 17.0.6, 256 bits)`） |
| `driver_version` | string | 是 | 驱动版本（如 `Mesa 24.0.9`） |
| `cpu` | string | 是 | CPU 描述（如 `8 × x86_64`） |
| `ram` | string | 是 | 内存（如 `16 GiB`） |
| `build_commit` | string | 是 | 40 位 git commit hash |
| `build_config` | string | 是 | `Debug` / `Release` |
| `command` | string | 是 | 产生该收据的完整命令行 |
| `metrics` | object \| null | 是 | benchmark 必填；字段见下 |
| `metrics.fps_avg` | number | benchmark 必填 | 平均 FPS |
| `metrics.fps_p1` | number | benchmark 必填 | 1% 低帧 FPS |
| `metrics.frame_ms_avg` | number | benchmark 必填 | 平均帧时长 ms |
| `metrics.frame_ms_p99` | number | benchmark 必填 | P99 帧时长 ms |
| `evidence_level` | string | 是 | `NONE` / `COMPILED` / `HEADLESS` / `NATIVE_SURFACE` / `GPU_RUNTIME` / `BENCHMARK_COMPARABLE` |
| `runner` | string | 是 | 运行器标识（如 `github-actions/ubuntu-latest (job: vk)` 或本机描述） |

## 示例收据

```json
{
  "schema_version": 1,
  "timestamp": "2026-10-14T12:00:00Z",
  "platform": "linux-x11",
  "os_version": "Ubuntu 24.04",
  "backend": "vulkan",
  "gpu": "llvmpipe (LLVM 17.0.6, 256 bits)",
  "driver_version": "Mesa 24.0.9",
  "cpu": "8 × x86_64",
  "ram": "16 GiB",
  "build_commit": "0123456789abcdef0123456789abcdef01234567",
  "build_config": "Debug",
  "command": "ctest --test-dir build -R '^test_vulkan$' --output-on-failure",
  "metrics": {
    "fps_avg": 61.2,
    "fps_p1": 54.8,
    "frame_ms_avg": 16.34,
    "frame_ms_p99": 22.10
  },
  "evidence_level": "GPU_RUNTIME",
  "runner": "github-actions/ubuntu-latest (job: vk)"
}
```
````

- [ ] **Step 5: 更新 README.md / Build_Guide.md / Architecture_Overview.md**

5a. `README.md`：找到现有构建/平台支持段落（以 `grep -n "Vulkan\|OpenGL\|cmake" README.md` 定位），追加一段：

```markdown
### RHI 后端（迁移期）

RHI 后端编译为独立静态库（`engine_rhi_opengl` / `engine_rhi_vulkan` / `engine_rhi_headless`），最终可执行文件链接 `engine` + 恰好一个后端库（`engine_link_rhi_backend(<target>)`）。后端选择：`-DENGINE_RHI_BACKEND=auto|opengl|vulkan`（`ENGINE_VULKAN` option 兼容保留）。证据基线与等级见 `docs/rhi_backend_evidence.md`。
```

5b. `docs/Build_Guide.md`：新增「RHI 后端链接模型」一节（插到现有后端选择说明附近，以 `grep -n "ENGINE_RHI_BACKEND\|ENGINE_VULKAN" docs/Build_Guide.md` 定位）：

```markdown
## RHI 后端链接模型

- `engine` 静态库只含 `RHI_CORE_SOURCES`（rhi.c 调度/校验、ownership、validation、resources、present_history），不再编译任何后端源。
- 后端各自为独立静态库：`engine_rhi_opengl`（`src/rhi/rhi_gl.c` + glad + 平台 GL 库）、`engine_rhi_vulkan`（`src/rhi/rhi_vk.c`，链接 `Vulkan::Vulkan` + shaderc）、`engine_rhi_headless`（`src/rhi/rhi_headless.c`，全入口 fail-closed，仅供契约/headless 测试链接，永不构成 GPU 证据）。
- 需要 RHI 的可执行 target 在其 `target_link_libraries` 之后调用 `engine_link_rhi_backend(<target>)`；headless 测试不调用该 helper，直接链接 `engine_rhi_headless`。
- 后端选择语义不变：`ENGINE_RHI_BACKEND=auto|opengl|vulkan` 与 `ENGINE_VULKAN` 兼容层；`metal`/`d3d12` 在计划 C/D 落地前仍被选择器拒绝（FATAL_ERROR）。
```

5c. `docs/Architecture_Overview.md`：在平台支持相关章节（以 `grep -n "平台\|Platform\|RHI" docs/Architecture_Overview.md` 定位）插入 RHI 分层图。写入文档的完整段落如下（外层四个反引号仅为本计划的包裹；实际写入 `Architecture_Overview.md` 时图示用普通三层反引号代码块）：

````markdown
### RHI 分层（2026-10-14 起）

```
应用 / renderer（rhi.h 公共 API，后端中性）
  └─ engine（RHI_CORE_SOURCES：rhi.c 调度/校验 + ownership + validation + resources + present_history）
       └─ 恰好一个后端静态库：engine_rhi_opengl | engine_rhi_vulkan | engine_rhi_headless
            └─ 平台图形栈（GL/EGL、Vulkan+shaderc、或 fail-closed stub）
```

- 编译期单后端、直接符号链接（无 vtable 分发）；`engine_link_rhi_backend(<target>)` 按 `ENGINE_RHI_BACKEND_EFFECTIVE` 选择。
- Vulkan 形状的 native interop（`RHINativeDevice` 等）在 `engine/src/rhi/rhi_native_vulkan.h`，`rhi.h` 保持后端中性。
````

- [ ] **Step 6: ci.yml 六类 lane 注释**

在 `.github/workflows/ci.yml` 的 `name: CI` 行之后插入注释块：

```yaml
# RHI 证据 lane 分类约定（spec: docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md §8.2）：
#   headless       — 无 GPU/无显示；label "headless"/"platform_contract"；任何 runner 可跑
#   native-surface — 真实窗口系统 surface，无 GPU 断言；环境缺失用 SKIP_RETURN_CODE 77
#   GPU-runtime    — 真实或软渲染 GPU 运行；label "graphics"/"platform_runtime"
#   validation     — Vulkan validation layer 消息计数 gate（test_vulkan 路径）
#   benchmark      — 产出 docs/rhi_benchmark_receipt_schema.md 收据 artifact
#   Proton         — 仅兼容验证，不计入 Windows D3D12 证据
# 现有 lane 归类：gl/vk = headless + GPU-runtime（软渲染）；wayland-* = native-surface；
# windows-clang = GPU-runtime；macos-vulkan = GPU-runtime（MoltenVK，非原生 Metal 证据）。
# 本计划不新增 GPU lane；后续新增 lane 必须在本注释声明证据类别并产出收据 artifact。
```

- [ ] **Step 7: 验证**

```bash
cmake --build build-gate --parallel
ctest --test-dir build-gate -R '^test_rhi_evidence_register$' --output-on-failure
ctest --test-dir build-gate -LE "graphics|fuzz" --output-on-failure
```

预期：构建成功（文档改动不影响编译，但确认工作树无意外源码改动）、测试全绿。

- [ ] **Step 8: Commit**

```bash
git add docs/vulkan_support_matrix.md docs/rhi_metal_d3d12_feature_matrix.md \
  docs/rhi_rollback_runbook.md docs/rhi_benchmark_receipt_schema.md \
  README.md docs/Build_Guide.md docs/Architecture_Overview.md .github/workflows/ci.yml
git commit -m "docs: rhi backend docs set and ci evidence-lane conventions"
```

---

### Task 8: 最终验证与推送

**Files:**
- Modify: 无（只验证 + push）

**Interfaces:**
- Consumes: Task 1-7 的全部提交。
- Produces: clean-room 双后端全绿证据；`origin master` 更新。

- [ ] **Step 1: clean-room 配置（GL）——新目录，不复用任何已有构建目录**

```bash
cmake -S engine -B engine/build-cleanroom-gl -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build engine/build-cleanroom-gl --parallel
ctest --test-dir engine/build-cleanroom-gl -LE "graphics|fuzz" --output-on-failure
```

预期：configure 成功（含 `RHI backend: requested=auto; effective=opengl`）、构建成功、`100% tests passed`。

- [ ] **Step 2: clean-room 配置（Vulkan）**

```bash
cmake -S engine -B engine/build-cleanroom-vk -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=ON
cmake --build engine/build-cleanroom-vk --parallel
ctest --test-dir engine/build-cleanroom-vk -LE "graphics|fuzz" --output-on-failure
```

预期：configure 成功（`effective=vulkan`）、构建成功、`100% tests passed`。

- [ ] **Step 3: 确认契约测试在两个目录都绿**

```bash
ctest --test-dir engine/build-cleanroom-gl -R '^test_rhi_' --output-on-failure
ctest --test-dir engine/build-cleanroom-vk -R '^test_rhi_' --output-on-failure
```

预期：`test_rhi_capabilities`、`test_rhi_native`、`test_rt_trace`、`test_rhi_error_contract`、`test_rhi_frame_lifecycle_contract`、`test_rhi_evidence_register`、`test_rhi_header_neutral`、`test_rhi_backend_selection`、`test_rhi_backend_internal_contract`、`test_rhi_tlas_instance_encode` 全部 PASS。

- [ ] **Step 4: 提交前卫生检查**

```bash
git status --short
git log --oneline origin/master..HEAD
```

确认：工作树只剩冻结文件（`.scratch-vkprobe/`、`.tmp/`、`d3d12_shader_gate.*`、`engine/profile_trace.json`，保持未跟踪、未改动）；待推送 commit 清单与 Task 1-7 一一对应。

- [ ] **Step 5: 推送**

```bash
git push origin master
```

预期：远端接受。推送后在 `docs/rhi_backend_evidence.md` 的 Windows × Vulkan 行收据栏无需变更（本机 run 已记录）；本次推送本身不构成任何等级升级。
