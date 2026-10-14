# 计划 F：发布、依赖锁定与 OpenGL 退役 — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在计划 A–E 全部认证完成的前提下，锁定全部构建/测试/发布依赖、落地 clean-room 构建闸门、后端 rollout 配置与结构化日志、回滚 runbook、兼容期 OpenGL fallback 治理，最终在满足规格 §6 全部 11 条删除条件后以单独 breaking commit 删除 OpenGL 后端，并完成 CI lane 分离、文档收尾与新 major release 的签名发布。

**Architecture:** 保持「编译期单后端、直接符号链接」模型（规格 §4.1）不变；rollout 配置（`engine/assets/rhi_backend_rollout.json`）在 CMake configure 期解析并固化为编译定义，运行时只输出结构化日志行（`RHIEVT {...}`），不引入运行时热切换。依赖锁定以 `engine/external/locked_dependencies.json`（机器可校验）+ `LOCKED_DEPENDENCIES.md`（人读）双轨，由 `cmake -P` 契约测试强制。OpenGL 删除由 `test_opengl_removal_gate.cmake` 逐条检查规格 §6 的 11 条前置，全绿后才允许执行删除 commit。

**Tech Stack:** C11 / CMake ≥3.25（`string(JSON)` 契约测试）/ CTest（`SKIP_RETURN_CODE 77` 约定）/ GitHub Actions / Ninja + clang（gate）/ vendored Vulkan SDK 1.4.357.0（`engine/external/VulkanSDK/`）/ shaderc / glslang 16.4.0 / dxc 1.9.0.5399。

## Global Constraints

- **TDD 纪律**：每个 Task 遵循「写失败测试 → 验证失败（命令+预期输出）→ 最小实现 → 验证通过 → commit」。禁止先实现后补测试。
- **前置条件**：计划 B/C/D/E 的对应部分已完成——B（WSI 抽离 + Vulkan-first）、C（原生 Metal 认证）、D（原生 D3D12 认证）、E（renderer/shader ABI 迁移）。本计划 Task 0 是显式 gating Task，逐项检查，任何一项不满足则停止，不得跳过。
- **冻结文件清单（任何步骤不得修改/删除/移动）**：`.scratch-vkprobe/`、`engine/profile_trace.json`、`.tmp/`、仓库根 `d3d12_shader_gate.hlsl` 与 `d3d12_shader_gate.dxil`、`.env`、SSH 私钥。
- **禁止 release 使用 latest 版本**：所有 SDK/工具链/CI 包必须钉住具体版本号并记录 sha256；CI 中禁止 `libvulkan-dev`/`libshaderc-dev`/brew 未钉版本包装等 unpinned 来源（Task 1/2/7 落实）。
- **缺失 SDK 的平台只能标记 UNAVAILABLE，不得伪造证据**：CI 与契约测试用 `SKIP_RETURN_CODE 77` 或显式 UNAVAILABLE 收据表达缺席，禁止把 compiled 写成 GPU-runtime。
- **证据等级纪律**：`NONE → COMPILED → HEADLESS → NATIVE_SURFACE → GPU_RUNTIME → BENCHMARK_COMPARABLE`（`engine/src/platform/platform_compat.h:49-56`）。台账行升级必须附收据链接，收据遵循 `docs/rhi_benchmark_receipt_schema.md`。
- **上下文 70% 压缩交接规则**：执行上下文约 70% 时先生成压缩交接，至少包含：当前 Task 与 checkbox 状态；已完成/失败/阻塞测试及命令；修改与未提交文件清单；当前 commit/branch/remote；平台矩阵证据等级；未解决风险；下一步精确命令；并明确列出上述冻结文件不得触碰。
- **提交纪律**：仅在每个 Task 末尾的 commit 步骤提交；push 只在 Task 10。远程为 `git@github.com:konyka/break.git`，分支 `master`。
- **OpenGL 删除是 breaking change**：单独 commit `feat!: remove opengl backend`，不与其他改动混合；删除前 Task 6 的 11 条 gate 必须全绿。
- **Proton 证据隔离**：Proton lane 仅作兼容参考，不计入 Windows D3D12 证据（规格 §7）。

---

### Task 0: 前置条件闸门（计划 A–E DoD 显式检查）

**Files:**
- 不创建/修改任何文件；纯检查。检查结果记入 `docs/rhi_backend_evidence.md` 尾部「计划 F 前置确认」小节（追加段落，属本 Task 唯一写入）。

**Interfaces:**
- Consumes: 计划 A–E 的交付物（后端静态库拆分、WSI adapter、Metal/D3D12 后端、ABI 迁移）。
- Produces: 一份全绿的前置检查记录；后续所有 Task 以此为准。

- [ ] **Step 1: 检查计划 A（证据冻结 + 构建拆分）已交付**

Run:
```bash
test -f docs/rhi_backend_evidence.md && \
grep -n "add_library(engine_rhi_vulkan" engine/CMakeLists.txt && \
grep -n "add_library(engine_rhi_opengl" engine/CMakeLists.txt && \
grep -n "engine_link_rhi_backend" engine/CMakeLists.txt
```
Expected: 四条命令全部有输出（证据台账存在；两个后端库 target 与链接 helper 已注册）。任何一条无输出 → 停止，回到计划 A。

- [ ] **Step 2: 检查计划 B（WSI 抽离 + Vulkan-first）已交付**

Run:
```bash
test -f engine/src/platform/platform_vk_surface.h && \
grep -n "platform_create_vulkan_surface" engine/src/rhi/rhi_vk.c | head -3
```
Expected: 文件存在且 `rhi_vk.c` 已改为调用 PAL surface 创建函数（≥1 处调用点）。否则停止。

- [ ] **Step 3: 检查计划 C（原生 Metal）与计划 D（原生 D3D12）已认证**

Run:
```bash
grep -n "add_library(engine_rhi_metal" engine/CMakeLists.txt && \
grep -n "add_library(engine_rhi_d3d12" engine/CMakeLists.txt && \
grep -niE "macos.*metal.*GPU_RUNTIME" docs/rhi_backend_evidence.md && \
grep -niE "ios.*metal.*GPU_RUNTIME" docs/rhi_backend_evidence.md && \
grep -niE "windows.*d3d12.*GPU_RUNTIME" docs/rhi_backend_evidence.md && \
grep -niE "windows.*d3d12.*BENCHMARK" docs/rhi_backend_evidence.md
```
Expected: 两个后端库 target 存在；台账中 macOS/iOS × Metal、Windows × D3D12 行均为 GPU_RUNTIME（Windows 另需 BENCHMARK_COMPARABLE），且每行附收据链接。缺任一行 → 停止（不允许以 MoltenVK/Proton 行顶替，规格 §6.2/§7）。

- [ ] **Step 4: 检查计划 E（renderer/shader ABI 迁移）已交付**

Run:
```bash
grep -c "rhi_pipeline_get_uniform_location" engine/src/main.c; \
grep -rn "ifdef ENGINE_VULKAN" engine/src/renderer/ | wc -l
```
Expected: 第一条输出 `0`（434 处旧调用点已全部迁移到 reflection 绑定）；第二条输出 `0`（renderer 中不再有后端 `#ifdef` 分支，全部由 `RHICapabilities` 查询替代）。非零 → 停止。

- [ ] **Step 5: 基线全量验证**

Run（gate 树， Ninja+clang）:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
cmake --build build-gate --parallel && \
ctest --test-dir build-gate -LE "graphics|fuzz" --output-on-failure
```
Expected: 全绿（允许跳过项 exit 77）。记录测试总数作为本计划基线。

- [ ] **Step 6: 记录前置确认**

在 `docs/rhi_backend_evidence.md` 末尾追加：

```markdown
## 计划 F 前置确认（<执行日期>）

- 计划 A/B/C/D/E DoD：全绿（检查命令见计划 F Task 0）。
- 基线 headless 套件：<N> 通过 / <M> 跳过（build-gate, clang, Debug, commit <sha>）。
```

- [ ] **Step 7: Commit**

```bash
git add docs/rhi_backend_evidence.md
git commit -m "docs: record plan F prerequisite gate (plans A-E DoD green)"
```

---

### Task 1: 依赖锁定清单（LOCKED_DEPENDENCIES.md + locked_dependencies.json + 契约测试）

**Files:**
- Create: `engine/external/LOCKED_DEPENDENCIES.md`
- Create: `engine/external/locked_dependencies.json`
- Test: `engine/tests/test_locked_dependencies.cmake`
- Modify: `engine/CMakeLists.txt`（在 `test_rhi_backend_selection` 注册块附近追加新测试注册）

**Interfaces:**
- Consumes: 现状依赖事实——vendored Vulkan SDK `engine/external/VulkanSDK/` = 1.4.357.0（含 dxc 1.9.0.5399、glslang 16.4.0、`VkLayer_khronos_validation`、shaderc）；root `cmake_minimum_required(VERSION 3.25)`、engine 3.20；shaderc 查找在 `engine/CMakeLists.txt:223`。
- Produces: `locked_dependencies.json`，schema 为 `{"schema_version":1,"locked_at":"YYYY-MM-DD","dependencies":[{name,version,purpose,source,sha256,verify_path,platforms}]}`；`purpose ∈ {build-only,test-only,runtime-shipped,system-provided}`；`verify_path` 为相对 `engine/external/` 的路径，仅 vendored 条目有值。Task 2 的 clean-room 脚本与 Task 9 的发布包清单读取此文件。

- [ ] **Step 1: 写失败的契约测试 `engine/tests/test_locked_dependencies.cmake`**

```cmake
# Contract test: locked dependency manifest integrity.
# -DLOCK_JSON=<abs path to locked_dependencies.json>
# -DEXTERNAL_DIR=<abs path to engine/external>
if(NOT DEFINED LOCK_JSON)
    message(FATAL_ERROR "LOCK_JSON is required")
endif()
if(NOT DEFINED EXTERNAL_DIR)
    message(FATAL_ERROR "EXTERNAL_DIR is required")
endif()
if(NOT EXISTS "${LOCK_JSON}")
    message(FATAL_ERROR "locked dependency manifest missing: ${LOCK_JSON}")
endif()
file(READ "${LOCK_JSON}" json)
string(JSON locked_at ERROR_VARIABLE e GET "${json}" locked_at)
if(NOT "${e}" STREQUAL "NOTFOUND" OR "${locked_at}" STREQUAL "")
    message(FATAL_ERROR "locked_at missing or unparsable")
endif()
string(JSON dep_count ERROR_VARIABLE e_len LENGTH "${json}" dependencies)
if(NOT "${e_len}" STREQUAL "NOTFOUND")
    message(FATAL_ERROR "dependencies array missing or unparsable")
endif()
if(dep_count EQUAL 0)
    message(FATAL_ERROR "dependencies array is empty")
endif()
set(required_names cmake clang gcc msvc vulkan-sdk shaderc
    vulkan-validation-layers android-ndk xcode windows-sdk
    d3d12-agility-sdk dxc glslang)
math(EXPR last "${dep_count} - 1")
foreach(i RANGE ${last})
    foreach(field name version purpose source sha256 platforms)
        string(JSON val ERROR_VARIABLE err GET "${json}" dependencies ${i} ${field})
        if(NOT "${err}" STREQUAL "NOTFOUND")
            message(FATAL_ERROR "dependencies[${i}].${field} unparsable: ${err}")
        endif()
        if("${val}" STREQUAL "" OR "${val}" MATCHES "NOTFOUND")
            message(FATAL_ERROR "dependencies[${i}].${field} missing or empty")
        endif()
        if("${val}" MATCHES "[Ll][Aa][Tt][Ee][Ss][Tt]")
            message(FATAL_ERROR "dependencies[${i}].${field} contains forbidden 'latest': ${val}")
        endif()
    endforeach()
    string(JSON name GET "${json}" dependencies ${i} name)
    list(FIND required_names "${name}" found)
    if(found EQUAL -1)
        message(FATAL_ERROR "unexpected dependency entry: ${name}")
    endif()
    list(REMOVE_ITEM required_names "${name}")
    string(JSON purpose GET "${json}" dependencies ${i} purpose)
    if(NOT purpose MATCHES "^(build-only|test-only|runtime-shipped|system-provided)$")
        message(FATAL_ERROR "dependencies[${i}] (${name}) invalid purpose: ${purpose}")
    endif()
    string(JSON vpath ERROR_VARIABLE verr GET "${json}" dependencies ${i} verify_path)
    if("${verr}" STREQUAL "NOTFOUND" AND NOT "${vpath}" STREQUAL ""
       AND NOT "${vpath}" MATCHES "NOTFOUND")
        set(abs "${EXTERNAL_DIR}/${vpath}")
        if(EXISTS "${abs}")
            string(JSON expect GET "${json}" dependencies ${i} sha256)
            file(SHA256 "${abs}" actual)
            if(NOT actual STREQUAL expect)
                message(FATAL_ERROR
                    "sha256 mismatch for ${name}: ${abs}\n  expected ${expect}\n  actual   ${actual}")
            endif()
        endif()
    endif()
endforeach()
if(required_names)
    list(JOIN required_names ", " missing)
    message(FATAL_ERROR "missing locked dependencies: ${missing}")
endif()
message(STATUS "locked_dependencies.json contract OK (${dep_count} entries)")
```

在 `engine/CMakeLists.txt` 的 `add_test(NAME test_rhi_backend_selection ...)` 块之后注册：

```cmake
    add_test(NAME test_locked_dependencies
        COMMAND ${CMAKE_COMMAND}
            -DLOCK_JSON=${CMAKE_CURRENT_SOURCE_DIR}/external/locked_dependencies.json
            -DEXTERNAL_DIR=${CMAKE_CURRENT_SOURCE_DIR}/external
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_locked_dependencies.cmake)
    set_tests_properties(test_locked_dependencies PROPERTIES
        LABELS "headless;platform_contract")
```

- [ ] **Step 2: 运行测试确认失败（red）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_locked_dependencies$' --output-on-failure
```
Expected: FAIL，输出含 `locked dependency manifest missing: .../engine/external/locked_dependencies.json`。

- [ ] **Step 3: 写 `engine/external/locked_dependencies.json`**

先补齐非 vendored 条目的 sha256（执行时运行，输出填入 JSON；均为一次性命令）：

```bash
# Android NDK r27c
curl -sSL -o /tmp/ndk.zip https://dl.google.com/android/repository/android-ndk-r27c-windows.zip && cmake -E sha256sum /tmp/ndk.zip
# D3D12 Agility SDK 1.616.0（执行时先确认该版本存在： https://www.nuget.org/packages/Microsoft.Direct3D.D3D12 ；
# 若不存在，选用页面上最新的已发布稳定版并同步更新 version 字段与本命令）
curl -sSL -o /tmp/agility.nupkg https://www.nuget.org/api/v2/package/Microsoft.Direct3D.D3D12/1.616.0 && cmake -E sha256sum /tmp/agility.nupkg
```

文件内容（vendored 条目的 sha256 为 2026-10-14 在本仓库实测值，直接可用）：

```json
{
  "schema_version": 1,
  "locked_at": "2026-10-14",
  "dependencies": [
    {
      "name": "cmake",
      "version": ">=3.25,<4.0 (CI pins ubuntu-24.04 apt cmake=3.28.*)",
      "purpose": "build-only",
      "source": "ubuntu-24.04 apt cmake=3.28.*; 本地 gate 允许更高 3.x",
      "sha256": "n/a-apt-pinned-version-floor-and-ci-pin",
      "verify_path": "",
      "platforms": ["linux", "windows", "macos"]
    },
    {
      "name": "clang",
      "version": ">=17.0",
      "purpose": "build-only",
      "source": "system toolchain (engine/toolchain-clang-linux.cmake, toolchain-clang-win.cmake); CI: ubuntu-24.04 apt clang-18",
      "sha256": "n/a-system-toolchain-version-floor-only",
      "verify_path": "",
      "platforms": ["linux", "windows"]
    },
    {
      "name": "gcc",
      "version": ">=12.0",
      "purpose": "build-only",
      "source": "system toolchain; CI: ubuntu-24.04 apt gcc-13",
      "sha256": "n/a-system-toolchain-version-floor-only",
      "verify_path": "",
      "platforms": ["linux"]
    },
    {
      "name": "msvc",
      "version": ">=19.38 (VS 2022 17.8); gate generator: Visual Studio 18 2026",
      "purpose": "build-only",
      "source": "system toolchain (engine/toolchain-msvc.cmake)",
      "sha256": "n/a-system-toolchain-version-floor-only",
      "verify_path": "",
      "platforms": ["windows"]
    },
    {
      "name": "vulkan-sdk",
      "version": "1.4.357.0",
      "purpose": "build-only",
      "source": "vendored engine/external/VulkanSDK (headless unpack of lunarg SDK 1.4.357.0); Linux CI pins identical tarball",
      "sha256": "02caa31b8665a79f327cbfe97286fd7d0017c0b1f9b39eb78687b7a509de52b3",
      "verify_path": "VulkanSDK/Lib/vulkan-1.lib",
      "platforms": ["windows", "linux"]
    },
    {
      "name": "shaderc",
      "version": "sdk-1.4.357.0-bundled",
      "purpose": "runtime-shipped",
      "source": "vendored engine/external/VulkanSDK/Lib/shaderc_shared.lib (+ Bin/shaderc_shared.dll 258c9ccc80c31c20904c64a80af964504bdb29c1475aa21b15eb540d5c93c860); runtime target env Vulkan 1.2 / SPIR-V 1.5 (rhi_vk.c)",
      "sha256": "697a51fe3193f41bf1cd71d462aca037102b88f1f1d114f36db27d58ae771ebb",
      "verify_path": "VulkanSDK/Lib/shaderc_shared.lib",
      "platforms": ["windows", "linux", "macos", "android"]
    },
    {
      "name": "vulkan-validation-layers",
      "version": "sdk-1.4.357.0-bundled (VK_LAYER_KHRONOS_validation)",
      "purpose": "test-only",
      "source": "vendored engine/external/VulkanSDK/Bin/VkLayer_khronos_validation.json",
      "sha256": "20d3ef44fe96aa41fceefab2308892f9d4b346d23eebfe8b5e1690715f23f472",
      "verify_path": "VulkanSDK/Bin/VkLayer_khronos_validation.json",
      "platforms": ["windows", "linux"]
    },
    {
      "name": "android-ndk",
      "version": "27.2.12479018 (r27c)",
      "purpose": "build-only",
      "source": "https://dl.google.com/android/repository/android-ndk-r27c-windows.zip",
      "sha256": "<上一步 ndk.zip 实测值>",
      "verify_path": "",
      "platforms": ["android"]
    },
    {
      "name": "xcode",
      "version": ">=15.4 (macOS 14 SDK minimum)",
      "purpose": "system-provided",
      "source": "Apple Xcode; CI runner macos-14 image (pinned image label, not 'latest')",
      "sha256": "n/a-apple-developer-tools-version-floor-only",
      "verify_path": "",
      "platforms": ["macos", "ios"]
    },
    {
      "name": "windows-sdk",
      "version": "10.0.26100.0",
      "purpose": "system-provided",
      "source": "Microsoft Windows SDK 10.0.26100.0 (VS Installer component)",
      "sha256": "n/a-microsoft-installer-version-floor-only",
      "verify_path": "",
      "platforms": ["windows"]
    },
    {
      "name": "d3d12-agility-sdk",
      "version": "1.616.0",
      "purpose": "runtime-shipped",
      "source": "https://www.nuget.org/api/v2/package/Microsoft.Direct3D.D3D12/1.616.0",
      "sha256": "<上一步 agility.nupkg 实测值>",
      "verify_path": "",
      "platforms": ["windows"]
    },
    {
      "name": "dxc",
      "version": "1.9.0.5399 (sdk-1.4.357.0-bundled)",
      "purpose": "build-only",
      "source": "vendored engine/external/VulkanSDK/Bin/dxc.exe; 定位逻辑沿用 engine/tests/test_d3d12_shader_compile_gate.cmake",
      "sha256": "b05bc2ba3355fda065f1b39fa3b1aa6d87689a84a290e5f201c5b6efcce6cab8",
      "verify_path": "VulkanSDK/Bin/dxc.exe",
      "platforms": ["windows"]
    },
    {
      "name": "glslang",
      "version": "16.4.0 (sdk-1.4.357.0-bundled; 提供 glslangValidator 等价能力)",
      "purpose": "build-only",
      "source": "vendored engine/external/VulkanSDK/Bin/glslang.exe; myui 离线 shader 生成 (engine/CMakeLists.txt find_program glslangValidator) 在 CI 上改用此钉版二进制",
      "sha256": "2f4825516c1e00ab923d4d6736ec4b536caddd8a15b41b0692ead207064ebb73",
      "verify_path": "VulkanSDK/Bin/glslang.exe",
      "platforms": ["windows", "linux"]
    }
  ]
}
```

- [ ] **Step 4: 写 `engine/external/LOCKED_DEPENDENCIES.md`**

```markdown
# 锁定依赖清单（LOCKED_DEPENDENCIES.md）

机器可校验源：`locked_dependencies.json`（契约测试 `test_locked_dependencies` 强制字段完整、
禁止 "latest"、对 vendored 文件验 sha256）。升级任何依赖 = 改 JSON + 重算 sha256 + 更新本文件 + 全 CI 绿。

## 钉版原则

1. 禁止任何 release 路径使用 "latest" 或未钉版本包（apt/brew 默认包均在禁止之列）。
2. 版本区间仅允许用于编译器/CMake 的最低版本地板（`>=x.y`），并附 CI 实际使用的钉版值。
3. vendored 依赖（`engine/external/VulkanSDK/` = 1.4.357.0）以文件 sha256 为准。
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
| d3d12-agility-sdk | 1.616.0 | runtime-shipped | D3D12Core.dll 随 Windows 发布包分发 |
| dxc | 1.9.0.5399 | build-only | SDK 同捆；HLSL→DXIL gate |
| glslang | 16.4.0 | build-only | SDK 同捆 glslang.exe；替代 unpinned 的 glslangValidator |
```

- [ ] **Step 5: 运行测试确认通过（green）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_locked_dependencies$' --output-on-failure
```
Expected: PASS，输出 `locked_dependencies.json contract OK (13 entries)`。

再跑一次负向自检（确认测试真的会失败）：临时把 JSON 中某条 version 改成 `latest` → 测试必须 FAIL 含 `forbidden 'latest'`；改回后 PASS。

- [ ] **Step 6: Commit**

```bash
git add engine/external/LOCKED_DEPENDENCIES.md engine/external/locked_dependencies.json \
        engine/tests/test_locked_dependencies.cmake engine/CMakeLists.txt
git commit -m "build: lock all build/test/release dependencies with machine-checked manifest"
```

---

### Task 2: clean-room build gate（脚本 + CI job）

**Files:**
- Create: `engine/tools/clean_room_build.sh`
- Create: `engine/tools/clean_room_build.ps1`
- Test: `engine/tests/test_clean_room_build_contract.cmake`
- Modify: `engine/CMakeLists.txt`（注册契约测试）
- Modify: `.github/workflows/ci.yml`（新增 `clean-room` job）

**Interfaces:**
- Consumes: Task 1 的 `engine/external/locked_dependencies.json`（脚本从中读取应使用的依赖来源；本阶段脚本校验「仓库内不含 unpinned 安装指令」并验证 vendored SDK sha256）。
- Produces: `clean_room_build.sh <src> <workdir>` 约定：exit 0 = 绿；exit 77 = 缺失 SDK → UNAVAILABLE；其他非零 = 失败。CI job `clean-room` 依赖此约定。Task 6 条件 7 复用本脚本的无 GL 变体（`-DENGINE_RHI_BACKEND=vulkan` 配置 + 断言 configure log 无 GL 发现）。

- [ ] **Step 1: 写失败的契约测试 `engine/tests/test_clean_room_build_contract.cmake`**

```cmake
# Contract test: clean-room scripts exist and carry the required gates.
# -DENGINE_SOURCE_DIR=<abs path to engine/>
if(NOT DEFINED ENGINE_SOURCE_DIR)
    message(FATAL_ERROR "ENGINE_SOURCE_DIR is required")
endif()
foreach(script tools/clean_room_build.sh tools/clean_room_build.ps1)
    set(p "${ENGINE_SOURCE_DIR}/${script}")
    if(NOT EXISTS "${p}")
        message(FATAL_ERROR "clean-room script missing: ${p}")
    endif()
    file(READ "${p}" text)
    foreach(marker "locked_dependencies.json" "git archive" "UNAVAILABLE" "77")
        string(FIND "${text}" "${marker}" off)
        if(off EQUAL -1)
            message(FATAL_ERROR "${script} missing required marker: ${marker}")
        endif()
    endforeach()
endforeach()
# CI must wire the job.
file(READ "${ENGINE_SOURCE_DIR}/../.github/workflows/ci.yml" ci)
string(FIND "${ci}" "clean-room:" off)
if(off EQUAL -1)
    message(FATAL_ERROR "ci.yml has no clean-room job")
endif()
string(FIND "${ci}" "clean_room_build" off)
if(off EQUAL -1)
    message(FATAL_ERROR "ci.yml clean-room job does not invoke clean_room_build")
endif()
message(STATUS "clean-room build contract OK")
```

并在 `engine/CMakeLists.txt` 注册：

```cmake
    add_test(NAME test_clean_room_build_contract
        COMMAND ${CMAKE_COMMAND}
            -DENGINE_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_clean_room_build_contract.cmake)
    set_tests_properties(test_clean_room_build_contract PROPERTIES
        LABELS "headless;platform_contract")
```

- [ ] **Step 2: 运行测试确认失败（red）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_clean_room_build_contract$' --output-on-failure
```
Expected: FAIL，输出 `clean-room script missing: .../engine/tools/clean_room_build.sh`。

- [ ] **Step 3: 实现 `engine/tools/clean_room_build.sh`**

```bash
#!/usr/bin/env bash
# clean_room_build.sh <repo_root> <workdir> [--backend vulkan|opengl]
# 干净导出（git archive）→ 仅用锁定依赖 → configure/build/headless ctest。
# exit 0 = 绿; exit 77 = 缺失 SDK (UNAVAILABLE); 其他非零 = 失败。
set -euo pipefail
REPO="${1:?usage: clean_room_build.sh <repo_root> <workdir> [--backend B]}"
WORK="${2:?usage: clean_room_build.sh <repo_root> <workdir> [--backend B]}"
BACKEND="vulkan"
[ "${3:-}" = "--backend" ] && BACKEND="${4:?backend name required}"

LOCK_JSON="$REPO/engine/external/locked_dependencies.json"
[ -f "$LOCK_JSON" ] || { echo "locked_dependencies.json missing at $LOCK_JSON"; exit 2; }
grep -qi '"latest"' "$LOCK_JSON" && { echo "locked manifest contains 'latest'"; exit 2; }

# 依赖闸：vendored Vulkan SDK 必须存在且 sha256 匹配清单。
SDK_LIB="$REPO/engine/external/VulkanSDK/Lib/vulkan-1.lib"
EXPECT=$(grep -A6 '"name": "vulkan-sdk"' "$LOCK_JSON" | grep '"sha256"' | head -1 \
         | sed -E 's/.*"sha256": "([0-9a-f]{64})".*/\1/')
if [ "$(uname -s)" = "Linux" ]; then
    # Linux 闸：要求 lavapipe ICD 或真实驱动；均无 → UNAVAILABLE (77)。
    if ! ls /usr/share/vulkan/icd.d/*.json >/dev/null 2>&1; then
        echo "UNAVAILABLE: no Vulkan ICD on this host"; exit 77
    fi
elif [ -f "$SDK_LIB" ]; then
    ACTUAL=$(cmake -E sha256sum "$SDK_LIB" | awk '{print $1}')
    [ "$ACTUAL" = "$EXPECT" ] || { echo "vendored Vulkan SDK sha256 mismatch"; exit 2; }
else
    echo "UNAVAILABLE: vendored Vulkan SDK not present"; exit 77
fi

rm -rf "$WORK"; mkdir -p "$WORK"
git -C "$REPO" archive HEAD | tar -x -C "$WORK"
cmake -S "$WORK/engine" -B "$WORK/build" -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND="$BACKEND" 2>&1 | tee "$WORK/configure.log"
# 无 GL 承诺：configure log 不得出现 OpenGL 发现（Task 6 条件 7 复用此断言）。
if [ "$BACKEND" = "vulkan" ] && grep -qi "found OpenGL" "$WORK/configure.log"; then
    echo "clean-room violation: OpenGL discovered in a vulkan-only configure"; exit 3
fi
cmake --build "$WORK/build" --parallel
ctest --test-dir "$WORK/build" -LE "graphics|fuzz" --output-on-failure
echo "CLEAN-ROOM OK (backend=$BACKEND)"
```

`chmod +x engine/tools/clean_room_build.sh`。

- [ ] **Step 4: 实现 `engine/tools/clean_room_build.ps1`（Windows 等价）**

```powershell
# clean_room_build.ps1 -Repo <path> -Work <path> [-Backend vulkan|opengl]
# 语义与 clean_room_build.sh 完全一致：0 = 绿; 77 = UNAVAILABLE; 其他非零 = 失败。
param([Parameter(Mandatory=$true)][string]$Repo,
      [Parameter(Mandatory=$true)][string]$Work,
      [string]$Backend = "vulkan")
$ErrorActionPreference = "Stop"
$lockJson = Join-Path $Repo "engine/external/locked_dependencies.json"
if (-not (Test-Path $lockJson)) { Write-Error "locked_dependencies.json missing"; exit 2 }
if (Select-String -Path $lockJson -Pattern '"latest"' -Quiet) { Write-Error "manifest contains 'latest'"; exit 2 }
$sdkLib = Join-Path $Repo "engine/external/VulkanSDK/Lib/vulkan-1.lib"
if (-not (Test-Path $sdkLib)) { Write-Output "UNAVAILABLE: vendored Vulkan SDK not present"; exit 77 }
$expect = ((Select-String -Path $lockJson -Pattern '"sha256": "([0-9a-f]{64})"' -AllMatches |
    ForEach-Object { $_.Matches } | ForEach-Object { $_.Groups[1].Value }) | Select-Object -First 1)
$actual = (Get-FileHash $sdkLib -Algorithm SHA256).Hash.ToLowerInvariant()
if ($actual -ne $expect) { Write-Error "vendored Vulkan SDK sha256 mismatch"; exit 2 }
if (Test-Path $Work) { Remove-Item -Recurse -Force $Work }
New-Item -ItemType Directory -Force $Work | Out-Null
git -C $Repo archive HEAD -o "$Work/src.tar"
tar -xf "$Work/src.tar" -C $Work
cmake -S "$Work/engine" -B "$Work/build" -G Ninja -DCMAKE_BUILD_TYPE=Debug `
    -DENGINE_RHI_BACKEND=$Backend | Tee-Object "$Work/configure.log"
if ($Backend -eq "vulkan" -and (Select-String -Path "$Work/configure.log" -Pattern "found OpenGL" -Quiet)) {
    Write-Error "clean-room violation: OpenGL discovered in a vulkan-only configure"; exit 3
}
cmake --build "$Work/build" --parallel
ctest --test-dir "$Work/build" -LE "graphics|fuzz" --output-on-failure
Write-Output "CLEAN-ROOM OK (backend=$Backend)"
```

- [ ] **Step 5: 在 `.github/workflows/ci.yml` 新增 `clean-room` job（追加在 `vk:` job 之后）**

```yaml
  clean-room:
    name: Clean-room build (locked deps, fresh export)
    runs-on: ubuntu-24.04
    timeout-minutes: 30
    steps:
      - uses: actions/checkout@v4
      - name: Install pinned toolchain
        run: |
          sudo apt-get update
          sudo apt-get install -y --no-install-recommends \
            clang-18 lld-18 cmake=3.28.* ninja-build libx11-dev libxrandr-dev \
            libvulkan-dev=1.3.275.* libshaderc-dev=2023.8.* \
            libfreetype6-dev fonts-noto-cjk mesa-vulkan-drivers
      - name: Clean-room configure/build/test
        run: bash engine/tools/clean_room_build.sh "$GITHUB_WORKSPACE" "$RUNNER_TEMP/clean-room" --backend vulkan
```

注意：`libvulkan-dev=1.3.275.*`/`libshaderc-dev=2023.8.*` 的精确 apt 版本串以 `apt-cache policy libvulkan-dev libshaderc-dev` 在 ubuntu-24.04 runner 上的实测值为准，执行时先跑一次该命令确认候选版本存在再填入（仍是钉版，不是 latest）。

- [ ] **Step 6: 运行契约测试确认通过（green）+ 本地实测脚本**

Run:
```bash
ctest --test-dir build-gate -R '^test_clean_room_build_contract$' --output-on-failure && \
bash engine/tools/clean_room_build.sh "$PWD" /tmp/clean-room-smoke --backend vulkan
```
Expected: 契约测试 PASS 输出 `clean-room build contract OK`；脚本输出 `CLEAN-ROOM OK (backend=vulkan)`（本机无 ICD 时允许 exit 77 + `UNAVAILABLE`，并在报告中记录——不得伪造）。

- [ ] **Step 7: Commit**

```bash
git add engine/tools/clean_room_build.sh engine/tools/clean_room_build.ps1 \
        engine/tests/test_clean_room_build_contract.cmake engine/CMakeLists.txt \
        .github/workflows/ci.yml
git commit -m "ci: add clean-room build gate using locked dependencies only"
```

---

### Task 3: 后端 rollout 配置与结构化运行时日志

**Files:**
- Create: `engine/assets/rhi_backend_rollout.json`
- Create: `engine/src/rhi/rhi_rollout.h`
- Create: `engine/src/rhi/rhi_rollout.c`
- Test: `engine/tests/test_rhi_rollout_log.c`
- Test: `engine/tests/test_rhi_rollout_config_contract.cmake`
- Modify: `engine/src/rhi/rhi.c`（`rhi_device_create_ex` :50、`rhi_present_ex` :136、`rhi_device_set_lifecycle_result` :405 三处挂点）
- Modify: `engine/src/rhi/rhi_vk.c`（:987 shader 编译失败路径挂点）
- Modify: `engine/CMakeLists.txt`（`RHI_CORE_SOURCES` 增加 `src/rhi/rhi_rollout.c`；configure 期解析 rollout JSON；注册两个测试）

**Interfaces:**
- Consumes: `RHIResult` 枚举（rhi.h:338-349）；`ENGINE_RHI_BACKEND_<NAME>=1` 公开编译定义（engine/CMakeLists.txt:329-330）；`LOG_INFO`（src/core/log.h）。
- Produces（后续 Task 依赖）：
  - 日志行格式（单行、前缀 `RHIEVT ` + 紧凑 JSON）：
    `RHIEVT {"event":"<backend_selected|fallback|device_lost|present_failure|shader_failure>","backend":"<vulkan|metal|d3d12|opengl>","reason":"<platform-default|explicit-env|compat-override|config-fallback|none>","config_version":<int>,"result":"<RHIResult 名或 OK>"}`
  - C API：`int rhi_rollout_format(char *buf, size_t cap, const RHIRolloutEvent *ev)`（返回写入长度，截断返回 -1）；`void rhi_rollout_emit(const RHIRolloutEvent *ev)`。
  - 配置：`engine/assets/rhi_backend_rollout.json` 的 `config_version` 在 configure 期固化为编译定义 `ENGINE_RHI_ROLLOUT_CONFIG_VERSION`。
  - Task 5/7 消费 `reason` 值域与 `RHIEVT` 前缀做断言。

- [ ] **Step 1: 写失败的日志格式单元测试 `engine/tests/test_rhi_rollout_log.c`**

```c
#include "rhi/rhi_rollout.h"
#include <stdio.h>
#include <string.h>

static int failures = 0;
static void check(const char *what, int cond) {
    if (!cond) { printf("FAIL: %s\n", what); failures++; }
}

int main(void) {
    char buf[512];
    RHIRolloutEvent ev = {
        .event = "backend_selected",
        .backend = "vulkan",
        .reason = "platform-default",
        .config_version = 3,
        .result = "OK",
    };
    int n = rhi_rollout_format(buf, sizeof(buf), &ev);
    check("format returns length", n > 0);
    check("prefix", strncmp(buf, "RHIEVT {", 8) == 0);
    check("event field", strstr(buf, "\"event\":\"backend_selected\"") != NULL);
    check("backend field", strstr(buf, "\"backend\":\"vulkan\"") != NULL);
    check("reason field", strstr(buf, "\"reason\":\"platform-default\"") != NULL);
    check("config_version field", strstr(buf, "\"config_version\":3") != NULL);
    check("result field", strstr(buf, "\"result\":\"OK\"") != NULL);
    check("single line", strchr(buf, '\n') == NULL);

    /* 截断语义：缓冲不足必须返回 -1，不得写出未终止串。 */
    char tiny[16];
    check("truncation returns -1", rhi_rollout_format(tiny, sizeof(tiny), &ev) == -1);

    /* 事件名白名单：非法事件名拒绝格式化。 */
    RHIRolloutEvent bad = ev;
    bad.event = "made_up_event";
    check("unknown event rejected", rhi_rollout_format(buf, sizeof(buf), &bad) == -1);

    if (failures) { printf("%d failures\n", failures); return 1; }
    printf("OK\n");
    return 0;
}
```

并在 `engine/CMakeLists.txt` 的 headless 测试区注册（紧跟 `test_rhi_capabilities` 注册块之后）：

```cmake
    add_executable(test_rhi_rollout_log tests/test_rhi_rollout_log.c
        src/rhi/rhi_rollout.c src/core/log.c)
    target_include_directories(test_rhi_rollout_log PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_rhi_rollout_log COMMAND test_rhi_rollout_log)
    set_tests_properties(test_rhi_rollout_log PROPERTIES LABELS "headless;platform_contract")
```

- [ ] **Step 2: 运行测试确认失败（red）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
cmake --build build-gate --target test_rhi_rollout_log
```
Expected: 编译失败，`fatal error: 'rhi/rhi_rollout.h' file not found`。

- [ ] **Step 3: 实现 `engine/src/rhi/rhi_rollout.h` 与 `rhi_rollout.c`**

```c
/* engine/src/rhi/rhi_rollout.h */
#ifndef RHI_ROLLOUT_H
#define RHI_ROLLOUT_H
#include <stddef.h>

typedef struct RHIRolloutEvent {
    const char *event;   /* backend_selected|fallback|device_lost|present_failure|shader_failure */
    const char *backend; /* vulkan|metal|d3d12|opengl */
    const char *reason;  /* platform-default|explicit-env|compat-override|config-fallback|none */
    int config_version;  /* ENGINE_RHI_ROLLOUT_CONFIG_VERSION; 0 = 无配置 */
    const char *result;  /* RHIResult 名或 "OK" */
} RHIRolloutEvent;

int rhi_rollout_format(char *buf, size_t cap, const RHIRolloutEvent *ev);
void rhi_rollout_emit(const RHIRolloutEvent *ev);

#endif
```

```c
/* engine/src/rhi/rhi_rollout.c */
#include "rhi/rhi_rollout.h"
#include "core/log.h"
#include <stdio.h>
#include <string.h>

static int allowed(const char *value, const char *const *set) {
    int i;
    for (i = 0; set[i] != NULL; i++)
        if (strcmp(value, set[i]) == 0) return 1;
    return 0;
}

int rhi_rollout_format(char *buf, size_t cap, const RHIRolloutEvent *ev) {
    static const char *const events[] = {
        "backend_selected", "fallback", "device_lost",
        "present_failure", "shader_failure", NULL };
    static const char *const backends[] = {
        "vulkan", "metal", "d3d12", "opengl", NULL };
    static const char *const reasons[] = {
        "platform-default", "explicit-env", "compat-override",
        "config-fallback", "none", NULL };
    int n;
    if (buf == NULL || ev == NULL || ev->event == NULL || ev->backend == NULL ||
        ev->reason == NULL || ev->result == NULL) return -1;
    if (!allowed(ev->event, events) || !allowed(ev->backend, backends) ||
        !allowed(ev->reason, reasons)) return -1;
    n = snprintf(buf, cap,
        "RHIEVT {\"event\":\"%s\",\"backend\":\"%s\",\"reason\":\"%s\","
        "\"config_version\":%d,\"result\":\"%s\"}",
        ev->event, ev->backend, ev->reason, ev->config_version, ev->result);
    if (n < 0 || (size_t)n >= cap) return -1;
    return n;
}

void rhi_rollout_emit(const RHIRolloutEvent *ev) {
    char buf[512];
    if (rhi_rollout_format(buf, sizeof(buf), ev) > 0)
        LOG_INFO("%s", buf);
}
```

- [ ] **Step 4: 运行单元测试确认通过（green）**

Run:
```bash
cmake --build build-gate --target test_rhi_rollout_log && \
ctest --test-dir build-gate -R '^test_rhi_rollout_log$' --output-on-failure
```
Expected: PASS，测试输出 `OK`。

- [ ] **Step 5: 写 rollout 配置与失败的配置契约测试**

写失败的 `engine/tests/test_rhi_rollout_config_contract.cmake`：

```cmake
# Contract test: rollout config schema + signature self-check.
# -DROLLOUT_JSON=<abs path to engine/assets/rhi_backend_rollout.json>
if(NOT DEFINED ROLLOUT_JSON)
    message(FATAL_ERROR "ROLLOUT_JSON is required")
endif()
if(NOT EXISTS "${ROLLOUT_JSON}")
    message(FATAL_ERROR "rollout config missing: ${ROLLOUT_JSON}")
endif()
file(READ "${ROLLOUT_JSON}" json)
string(JSON schema ERROR_VARIABLE e GET "${json}" schema_version)
if(NOT "${e}" STREQUAL "NOTFOUND" OR NOT schema EQUAL 1)
    message(FATAL_ERROR "schema_version must be 1")
endif()
string(JSON cfgver GET "${json}" config_version)
if(cfgver LESS 1)
    message(FATAL_ERROR "config_version must be a positive integer")
endif()
string(JSON algo GET "${json}" signature algorithm)
if(NOT algo MATCHES "^(sha256-payload|ed25519-sha256)$")
    message(FATAL_ERROR "signature.algorithm invalid: ${algo}")
endif()
foreach(plat windows linux android macos ios steam-linux proton)
    string(JSON allowed_len ERROR_VARIABLE e2 LENGTH "${json}" platforms ${plat} allowed)
    if(NOT "${e2}" STREQUAL "NOTFOUND" OR allowed_len EQUAL 0)
        message(FATAL_ERROR "platforms.${plat}.allowed missing or empty")
    endif()
    string(JSON chain_len LENGTH "${json}" platforms ${plat} fallback_chain)
    if(chain_len EQUAL 0)
        message(FATAL_ERROR "platforms.${plat}.fallback_chain empty")
    endif()
    # fallback_chain 必须是 allowed 的子序列；且 OHOS 不允许出现。
    math(EXPR cl "${chain_len} - 1")
    foreach(i RANGE ${cl})
        string(JSON b GET "${json}" platforms ${plat} fallback_chain ${i})
        string(JSON allowed_json GET "${json}" platforms ${plat} allowed)
        string(FIND "${allowed_json}" "\"${b}\"" hit)
        if(hit EQUAL -1)
            message(FATAL_ERROR "platforms.${plat}: fallback '${b}' not in allowed")
        endif()
        if(b STREQUAL "ohos")
            message(FATAL_ERROR "platforms.${plat}: OHOS must stay fail-closed, never in a chain")
        endif()
    endforeach()
endforeach()
message(STATUS "rollout config contract OK (config_version=${cfgver})")
```

在 `engine/CMakeLists.txt` 注册：

```cmake
    add_test(NAME test_rhi_rollout_config_contract
        COMMAND ${CMAKE_COMMAND}
            -DROLLOUT_JSON=${CMAKE_CURRENT_SOURCE_DIR}/assets/rhi_backend_rollout.json
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_rollout_config_contract.cmake)
    set_tests_properties(test_rhi_rollout_config_contract PROPERTIES
        LABELS "headless;platform_contract")
```

Run（red）:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_rhi_rollout_config_contract$' --output-on-failure
```
Expected: FAIL，`rollout config missing: .../engine/assets/rhi_backend_rollout.json`。

- [ ] **Step 6: 写 `engine/assets/rhi_backend_rollout.json`（green）**

签名算法决策（写入配置头注释并在 `docs/rhi_rollback_runbook.md` 复述）：本阶段采用 `sha256-payload`——对「移除 `signature` 字段后的规范化 JSON（键序固定、无空白）」取 sha256 做完整性校验，防意外篡改/截断；**不做真实性签名**，因为仓库尚无密钥管理设施。`ed25519-sha256` 为发布签名流程（Task 9 与 git tag 签名同一把密钥）落地后的目标算法，schema 已预留；届时 `signature.algorithm` 切换并在契约测试中启用公钥验签。此限制属已知风险，不得把 sha256-payload 表述为「签名」。

```json
{
  "schema_version": 1,
  "config_version": 1,
  "comment": "signature.algorithm=sha256-payload = 完整性哈希（非真实性签名）；ed25519-sha256 随发布签名设施启用",
  "signature": { "algorithm": "sha256-payload", "value": "<执行时以规范化 payload 实测 sha256 填入；计算命令见下>" },
  "platforms": {
    "windows":     { "allowed": ["d3d12", "vulkan"],            "fallback_chain": ["d3d12", "vulkan"] },
    "linux":       { "allowed": ["vulkan", "opengl"],           "fallback_chain": ["vulkan", "opengl"] },
    "android":     { "allowed": ["vulkan"],                     "fallback_chain": ["vulkan"] },
    "macos":       { "allowed": ["metal", "vulkan"],            "fallback_chain": ["metal", "vulkan"] },
    "ios":         { "allowed": ["metal"],                      "fallback_chain": ["metal"] },
    "steam-linux": { "allowed": ["vulkan", "opengl"],           "fallback_chain": ["vulkan", "opengl"] },
    "proton":      { "allowed": ["vulkan"],                     "fallback_chain": ["vulkan"] }
  }
}
```

`signature.value` 计算命令（python3 单行，输出填入）：

```bash
python3 -c "import json,hashlib,sys; d=json.load(open('engine/assets/rhi_backend_rollout.json')); d.pop('signature'); print(hashlib.sha256(json.dumps(d,sort_keys=True,separators=(',',':')).encode()).hexdigest())"
```

注意：兼容期内 `linux`/`steam-linux` 的 fallback_chain 含 `opengl`（Task 5）；Task 6 删除后必须把 `opengl` 从所有 allowed/chain 中移除并 bump `config_version` 到 2（契约测试继续通过，因为白名单检查不引用 opengl 字面值）。

- [ ] **Step 7: configure 期固化 config_version + 运行时挂点**

在 `engine/CMakeLists.txt` 的 selector 块（:130-148）之后追加：

```cmake
# Rollout config: bake config_version into the build; schema enforced by
# test_rhi_rollout_config_contract.
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/assets/rhi_backend_rollout.json" ENGINE_ROLLOUT_JSON)
string(JSON ENGINE_ROLLOUT_CFGVER GET "${ENGINE_ROLLOUT_JSON}" config_version)
target_compile_definitions(engine PUBLIC
    ENGINE_RHI_ROLLOUT_CONFIG_VERSION=${ENGINE_ROLLOUT_CFGVER})
```

`RHI_CORE_SOURCES`（engine/CMakeLists.txt:238-243）追加 `src/rhi/rhi_rollout.c`。

挂点（`engine/src/rhi/rhi.c`）：

```c
/* rhi_device_create_ex (:50) 成功返回前： */
{
    RHIRolloutEvent ev = {
        .event = "backend_selected",
#if defined(ENGINE_RHI_BACKEND_VULKAN)
        .backend = "vulkan", .reason = "platform-default",
#elif defined(ENGINE_RHI_BACKEND_METAL)
        .backend = "metal", .reason = "platform-default",
#elif defined(ENGINE_RHI_BACKEND_D3D12)
        .backend = "d3d12", .reason = "platform-default",
#else
        .backend = "opengl", .reason = "compat-override",
#endif
        .config_version = ENGINE_RHI_ROLLOUT_CONFIG_VERSION,
        .result = "OK",
    };
    rhi_rollout_emit(&ev);
}
```

```c
/* rhi_present_ex (:136) 在 result != RHI_RESULT_OK 的返回路径： */
RHIRolloutEvent ev = { "present_failure", "vulkan", "none",
    ENGINE_RHI_ROLLOUT_CONFIG_VERSION, rhi_result_name(result) };
rhi_rollout_emit(&ev);
```

（backend 字面值同样按上面的 `#if` 链取值；`rhi_result_name` 若不存在则在 `rhi_rollout.c` 中新增一个 `RHIResult`→字符串的静态映射函数并导出原型到 `rhi_rollout.h`。）

```c
/* rhi_device_set_lifecycle_result (:405) 在 result == RHI_RESULT_DEVICE_LOST 时： */
if (result == RHI_RESULT_DEVICE_LOST) {
    RHIRolloutEvent ev = { "device_lost", /*同上 backend 链*/"vulkan", "none",
        ENGINE_RHI_ROLLOUT_CONFIG_VERSION, "DEVICE_LOST" };
    rhi_rollout_emit(&ev);
}
```

`engine/src/rhi/rhi_vk.c:987` 的 `LOG_FATAL("Vulkan shader compile error: ...")` 之前插入：

```c
{
    RHIRolloutEvent ev = { "shader_failure", "vulkan", "none",
        ENGINE_RHI_ROLLOUT_CONFIG_VERSION, "ERROR" };
    rhi_rollout_emit(&ev);
}
```

- [ ] **Step 8: 全量验证**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
cmake --build build-gate --parallel && \
ctest --test-dir build-gate -R 'rollout' --output-on-failure && \
ctest --test-dir build-gate -LE "graphics|fuzz" --output-on-failure
```
Expected: 两个 rollout 测试 PASS；headless 基线全绿。configure 输出应含 config_version 固化（可通过 `grep ENGINE_RHI_ROLLOUT_CONFIG_VERSION build-gate/CMakeCache.txt` 或编译定义抽查确认）。

- [ ] **Step 9: Commit**

```bash
git add engine/assets/rhi_backend_rollout.json engine/src/rhi/rhi_rollout.h \
        engine/src/rhi/rhi_rollout.c engine/tests/test_rhi_rollout_log.c \
        engine/tests/test_rhi_rollout_config_contract.cmake \
        engine/src/rhi/rhi.c engine/src/rhi/rhi_vk.c engine/CMakeLists.txt
git commit -m "rhi: versioned backend rollout config + structured RHIEVT runtime logging"
```

---

### Task 4: 回滚 runbook 与开关治理

**Files:**
- Modify: `docs/rhi_rollback_runbook.md`（计划 A 已建骨架；本 Task 充实为完整 runbook）
- Create: `.github/workflows/rollback-drill.yml`
- Test: `engine/tests/test_rhi_rollback_runbook_contract.cmake`
- Modify: `engine/CMakeLists.txt`（注册契约测试）

**Interfaces:**
- Consumes: Task 3 的 `reason` 值域与 rollout 配置字段；`ENGINE_RHI_BACKEND` selector（engine/CMakeLists.txt:130-148）。
- Produces: runbook 中三个开关的治理表（owner/expiry/rollback 步骤），被 Task 6 条件 9/10 与 Task 9 发布流程引用；rollback 演练 workflow（手动触发）供 Task 6 条件 10 与 Task 10 使用。

- [ ] **Step 1: 写失败的 runbook 契约测试 `engine/tests/test_rhi_rollback_runbook_contract.cmake`**

```cmake
# Contract test: every runtime/build switch has owner + expiry + rollback steps.
# -DRUNBOOK=<abs path to docs/rhi_rollback_runbook.md>
if(NOT DEFINED RUNBOOK)
    message(FATAL_ERROR "RUNBOOK is required")
endif()
if(NOT EXISTS "${RUNBOOK}")
    message(FATAL_ERROR "rollback runbook missing: ${RUNBOOK}")
endif()
file(READ "${RUNBOOK}" doc)
string(TOLOWER "${doc}" doc_lower)
foreach(sw "engine_rhi_backend" "rhi_backend_rollout.json" "fallback")
    string(FIND "${doc_lower}" "${sw}" off)
    if(off EQUAL -1)
        message(FATAL_ERROR "runbook does not govern switch: ${sw}")
    endif()
endforeach()
# 治理表每个开关行必须含 owner 与 expiry（表格列标题 + 至少 3 个 owner 单元格）。
foreach(col "owner" "expiry" "rollback")
    string(FIND "${doc_lower}" "${col}" off)
    if(off EQUAL -1)
        message(FATAL_ERROR "runbook governance table missing column: ${col}")
    endif()
endforeach()
string(REGEX MATCHALL "@[a-z0-9-]+" owners "${doc}")
list(LENGTH owners owner_count)
if(owner_count LESS 3)
    message(FATAL_ERROR "runbook must name a @github-owner per switch (found ${owner_count})")
endif()
foreach(section "device loss" "present failure" "签名")
    string(FIND "${doc_lower}" "${section}" off)
    if(off EQUAL -1)
        message(FATAL_ERROR "runbook missing operational section: ${section}")
    endif()
endforeach()
message(STATUS "rollback runbook contract OK")
```

注册（`engine/CMakeLists.txt`）：

```cmake
    add_test(NAME test_rhi_rollback_runbook_contract
        COMMAND ${CMAKE_COMMAND}
            -DRUNBOOK=${CMAKE_CURRENT_SOURCE_DIR}/../docs/rhi_rollback_runbook.md
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_rollback_runbook_contract.cmake)
    set_tests_properties(test_rhi_rollback_runbook_contract PROPERTIES
        LABELS "headless;platform_contract")
```

- [ ] **Step 2: 运行测试确认失败（red）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_rhi_rollback_runbook_contract$' --output-on-failure
```
Expected: FAIL——若计划 A 的骨架尚无治理表，首个失败为 `runbook governance table missing column: owner`；若骨架文件不存在则为 `rollback runbook missing`（此时先创建文件再继续）。

- [ ] **Step 3: 充实 `docs/rhi_rollback_runbook.md`（green）**

文件正文（骨架已有时整体替换为以下内容）：

```markdown
# RHI 回滚 Runbook（rollback / device-loss / present-failure）

适用范围：多后端 RHI（Vulkan / Metal / D3D12）+ 兼容期 OpenGL fallback。
日志入口：运行时结构化行 `RHIEVT {...}`（event ∈ backend_selected/fallback/device_lost/present_failure/shader_failure）。

## 1. 开关治理表

| 开关 | 类型 | owner | expiry | rollback 步骤 |
|---|---|---|---|---|
| `ENGINE_RHI_BACKEND`（CMake cache：auto/opengl/vulkan/metal/d3d12） | 构建期 | @konyka | OpenGL 删除 release（v2.0.0）发布 +30 天 | 重新 configure：`-DENGINE_RHI_BACKEND=<上一后端>`，重跑 headless 套件与对应 runtime lane |
| `engine/assets/rhi_backend_rollout.json`（allowed/fallback_chain/config_version） | 发布配置 | @konyka | 每个 minor release 复审一次 | `git revert` 配置 commit → bump `config_version` → 重发；运行时不读远端，配置随二进制固化 |
| 兼容期 OpenGL fallback（`reason=compat-override` 路径） | 兼容开关 | @konyka | v2.0.0（OpenGL 删除 release） | 删除前：引导用户设 `ENGINE_RHI_BACKEND=opengl` 重建；删除后：回滚到 v1.x tag（见 §4） |

治理规则：开关新增/变更必须更新本表（契约测试 `test_rhi_rollback_runbook_contract` 强制 owner/expiry/rollback 三列存在）；expiry 到期未处理的开关在下一个 release 评审中必须移除或续期。

## 2. Device loss 处置

1. 日志检索：`grep 'RHIEVT ' app.log | grep '"event":"device_lost"'`。
2. 确认是否已知坏境：NVIDIA 616.56 混合 GPU 的 DEVICE_LOST 不作源码修复依据（规格 §7），须在健康设备独立复现后立项。
3. 缓解：重启进程；若同机型批量出现，用 rollout 配置把该平台 fallback_chain 次位后端提前（发配置补丁 release）。
4. 根因修复后 bump `config_version` 并在台账记录收据。

## 3. Present failure 处置

1. `grep '"event":"present_failure"'` 按 `result` 分类：`OUT_OF_DATE` 多为 resize 竞态，`SURFACE_LOST` 多为 WSI 挂起/恢复路径。
2. 对照 frame 生命周期契约（规格 §4.3）确认 backend 自动重建 swapchain 是否失败；失败时 `lifecycle_result` 已 fail-fast，属预期。
3. 持续失败 → 按 §1 表回滚后端或回退版本。

## 4. 版本回滚（含 OpenGL 删除后的回退）

1. 每个 release 打签名 tag（Task 9）：`git tag -s v<x.y.z>`；旧 major（含 OpenGL 的最后版本 v1.x）长期保留。
2. 回退命令：`git checkout v1.x.y && cmake -S engine -B build -DENGINE_RHI_BACKEND=opengl ...`（删除后版本中 `opengl` 值已不存在，必须回到旧 tag）。
3. CI 演练：`.github/workflows/rollback-drill.yml`（workflow_dispatch 手动触发），输入上一 tag，验证其 clean checkout 可构建且 headless 套件绿。每 release 前必跑一次。

## 5. 签名与完整性

- rollout 配置当前为 `sha256-payload` 完整性哈希（非真实性签名）；`ed25519-sha256` 随发布签名密钥启用。
- release tag 使用 maintainer GPG key 签名；发布包附 `SHA256SUMS`。
```

- [ ] **Step 4: 创建 rollback 演练 workflow `.github/workflows/rollback-drill.yml`**

```yaml
name: Rollback drill

on:
  workflow_dispatch:
    inputs:
      tag:
        description: "Tag to roll back to (e.g. v1.4.2)"
        required: true
        type: string

jobs:
  rollback-verify:
    name: Build previous tag (rollback rehearsal)
    runs-on: ubuntu-24.04
    timeout-minutes: 30
    steps:
      - uses: actions/checkout@v4
        with:
          ref: ${{ inputs.tag }}
          fetch-depth: 0
      - name: Verify tag signature exists
        run: git tag -v "${{ inputs.tag }}"
      - name: Install pinned toolchain
        run: |
          sudo apt-get update
          sudo apt-get install -y --no-install-recommends \
            clang-18 lld-18 cmake=3.28.* ninja-build libx11-dev libxrandr-dev \
            libfreetype6-dev fonts-noto-cjk
      - name: Configure / build / headless test
        run: |
          cmake -S engine -B build -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release
          cmake --build build --parallel
          ctest --test-dir build -LE "graphics|fuzz" --output-on-failure
      - name: Report
        run: echo "rollback drill OK for tag ${{ inputs.tag }}" >> "$GITHUB_STEP_SUMMARY"
```

- [ ] **Step 5: 验证（green）**

Run:
```bash
ctest --test-dir build-gate -R '^test_rhi_rollback_runbook_contract$' --output-on-failure && \
python3 -c "import yaml,sys; yaml.safe_load(open('.github/workflows/rollback-drill.yml'))" 2>/dev/null || \
cmake -E echo "rollback-drill.yml syntax check: visual review (no yaml module)"
```
Expected: 契约测试 PASS 输出 `rollback runbook contract OK`；YAML 可被解析（无 python yaml 模块时以 GitHub Actions 的 workflow 语法检查代替：push 前在 GitHub UI / `gh workflow view rollback-drill.yml` 确认）。

- [ ] **Step 6: Commit**

```bash
git add docs/rhi_rollback_runbook.md .github/workflows/rollback-drill.yml \
        engine/tests/test_rhi_rollback_runbook_contract.cmake engine/CMakeLists.txt
git commit -m "docs+ci: rollback runbook with switch governance and rollback drill workflow"
```

---

### Task 5: 兼容期 OpenGL fallback（显式可用 + 无隐藏 fallback 扫描）

**Files:**
- Test: `engine/tests/test_rhi_opengl_compat_fallback_contract.cmake`
- Create: `engine/tests/gl_fallback_whitelist.txt`
- Test: `engine/tests/test_no_hidden_gl_fallback.cmake`
- Modify: `engine/CMakeLists.txt`（注册两个测试）

**Interfaces:**
- Consumes: Task 3 的 `reason=compat-override` 日志路径（`ENGINE_RHI_BACKEND_OPENGL` 编译定义分支）；selector（engine/CMakeLists.txt:130-148）。
- Produces: `gl_fallback_whitelist.txt` 白名单格式（每行一个「路径前缀 TAB token」或注释 `#`），Task 6 删除后必须把引擎 RHI 相关行移除并确认扫描仍绿；`test_no_hidden_gl_fallback` 在 Task 6 后是「无隐藏 GL fallback」的最终断言。

- [ ] **Step 1: 写失败的兼容 fallback 契约测试 `engine/tests/test_rhi_opengl_compat_fallback_contract.cmake`**

```cmake
# Contract test: 兼容期内 ENGINE_RHI_BACKEND=opengl 是显式、可观测的 fallback。
# -DENGINE_CMAKE=<abs engine/CMakeLists.txt> -DRHI_C=<abs src/rhi/rhi.c>
# -DROLLOUT_JSON=<abs assets/rhi_backend_rollout.json>
if(NOT DEFINED ENGINE_CMAKE OR NOT DEFINED RHI_C OR NOT DEFINED ROLLOUT_JSON)
    message(FATAL_ERROR "ENGINE_CMAKE, RHI_C, ROLLOUT_JSON are required")
endif()
file(READ "${ENGINE_CMAKE}" cm)
string(FIND "${cm}" "ENGINE_RHI_BACKEND STREQUAL \"opengl\"" off)
if(off EQUAL -1)
    message(FATAL_ERROR "compat fallback gone: selector no longer accepts 'opengl'")
endif()
file(READ "${RHI_C}" rhi)
string(FIND "${rhi}" "compat-override" off)
if(off EQUAL -1)
    message(FATAL_ERROR "compat fallback is silent: rhi.c must log reason=compat-override")
endif()
file(READ "${ROLLOUT_JSON}" rollout)
string(FIND "${rollout}" "\"opengl\"" off)
if(off EQUAL -1)
    message(FATAL_ERROR "compat period: rollout config must keep opengl in at least one fallback_chain")
endif()
message(STATUS "opengl compat fallback contract OK")
```

注册：

```cmake
    add_test(NAME test_rhi_opengl_compat_fallback_contract
        COMMAND ${CMAKE_COMMAND}
            -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            -DRHI_C=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi.c
            -DROLLOUT_JSON=${CMAKE_CURRENT_SOURCE_DIR}/assets/rhi_backend_rollout.json
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_opengl_compat_fallback_contract.cmake)
    set_tests_properties(test_rhi_opengl_compat_fallback_contract PROPERTIES
        LABELS "headless;platform_contract")
```

- [ ] **Step 2: 运行确认失败/通过状态（red 或即绿判定）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_rhi_opengl_compat_fallback_contract$' --output-on-failure
```
Expected: 若 Task 3 的挂点已含 `compat-override` 分支则直接 PASS（此情形在报告中注明「red 由 Task 3 Step 2 覆盖」）；若挂点尚未落地则 FAIL 于 `compat fallback is silent`，回到 Task 3 Step 7 补齐。

- [ ] **Step 3: 写白名单与隐藏 fallback 扫描测试**

`engine/tests/gl_fallback_whitelist.txt`（兼容期内容；格式：`路径前缀<TAB>token`）：

```text
# 兼容期已知 GL 落点白名单。OpenGL 删除（计划 F Task 6）后，引擎 RHI 相关行必须移除。
# 格式: <相对 engine/ 的路径前缀>\t<token 子串>
src/rhi/rhi_gl.c	gl
src/rhi/rhi.c	rhi_gl.c
external/glad.c	gl
external/glad.h	gl
CMakeLists.txt	glad
CMakeLists.txt	opengl32
CMakeLists.txt	ENGINE_RHI_BACKEND STREQUAL "opengl"
src/myui/myr/	GL	# myui 自有 GL canvas 后端（非引擎 RHI；删除决策见 Task 6 Step 4）
tests/test_rhi_x11_runtime.c	gl
tests/test_myui_gl_desktop	gl
```

`engine/tests/test_no_hidden_gl_fallback.cmake`：

```cmake
# Contract test: no GL fallback outside the whitelist.
# -DENGINE_SOURCE_DIR=<abs engine/> -DWHITELIST=<abs gl_fallback_whitelist.txt>
if(NOT DEFINED ENGINE_SOURCE_DIR OR NOT DEFINED WHITELIST)
    message(FATAL_ERROR "ENGINE_SOURCE_DIR and WHITELIST are required")
endif()
file(READ "${WHITELIST}" wl_text)
string(REPLACE "\n" ";" wl_lines "${wl_text}")
set(wl)
foreach(line IN LISTS wl_lines)
    string(REGEX REPLACE "#.*$" "" line "${line}")
    string(STRIP "${line}" line)
    if(NOT "${line}" STREQUAL "")
        string(REGEX MATCH "^([^\t ]+)[\t ]+(.+)$" m "${line}")
        if(NOT m)
            message(FATAL_ERROR "malformed whitelist line: ${line}")
        endif()
        list(APPEND wl "${CMAKE_MATCH_1}|${CMAKE_MATCH_2}")
    endif()
endforeach()
set(tokens "rhi_gl" "glad" "opengl32" "libGL" "GLX" "WGL" "ENGINE_RHI_BACKEND_OPENGL" "RHI_BACKEND_OPENGL")
file(GLOB_RECURSE sources RELATIVE "${ENGINE_SOURCE_DIR}"
    "${ENGINE_SOURCE_DIR}/src/*.[ch]" "${ENGINE_SOURCE_DIR}/CMakeLists.txt"
    "${ENGINE_SOURCE_DIR}/tests/*.c")
set(violations "")
foreach(rel IN LISTS sources)
    file(READ "${ENGINE_SOURCE_DIR}/${rel}" content)
    string(TOLOWER "${content}" lower)
    foreach(tok IN LISTS tokens)
        string(TOLOWER "${tok}" tok_lower)
        string(FIND "${lower}" "${tok_lower}" hit)
        if(NOT hit EQUAL -1)
            set(covered FALSE)
            foreach(entry IN LISTS wl)
                string(REGEX MATCH "^([^|]+)\\|(.*)$" m "${entry}")
                set(wp "${CMAKE_MATCH_1}")
                if("${rel}" MATCHES "^${wp}")
                    set(covered TRUE)
                endif()
            endforeach()
            if(NOT covered)
                list(APPEND violations "${rel}: token '${tok}'")
            endif()
        endif()
    endforeach()
endforeach()
if(violations)
    list(JOIN violations "\n  " v)
    message(FATAL_ERROR "hidden GL fallback outside whitelist:\n  ${v}")
endif()
message(STATUS "no hidden GL fallback (whitelist entries: covered)")
```

注册：

```cmake
    add_test(NAME test_no_hidden_gl_fallback
        COMMAND ${CMAKE_COMMAND}
            -DENGINE_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
            -DWHITELIST=${CMAKE_CURRENT_SOURCE_DIR}/tests/gl_fallback_whitelist.txt
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_no_hidden_gl_fallback.cmake)
    set_tests_properties(test_no_hidden_gl_fallback PROPERTIES
        LABELS "headless;platform_contract")
```

- [ ] **Step 4: 运行确认（先 red 后 green）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_no_hidden_gl_fallback$' --output-on-failure
```
Expected: 第一次运行若白名单与实际落点不符（例如某文件含 `glad` 但白名单未覆盖其路径前缀），FAIL 并列出违规行；按输出修正白名单（只允许收录已核实的历史落点，禁止为通过测试而放宽 token 列）后重跑至 PASS。

- [ ] **Step 5: 功能级断言——opengl 构建确实可用且有日志**

Run:
```bash
cmake -S engine -B /tmp/build-gl-compat -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=opengl && \
grep "RHI backend: requested=opengl; effective=opengl" /tmp/build-gl-compat/CMakeCache.txt 2>/dev/null; \
cmake --build /tmp/build-gl-compat --parallel && \
ctest --test-dir /tmp/build-gl-compat -LE "graphics|fuzz" --output-on-failure
```
Expected: configure 输出含 `RHI backend: requested=opengl; effective=opengl`（该行由 selector 的 `message(STATUS ...)` 打印，在 configure stdout 中可见）；构建与 headless 套件绿。GL runtime 测试（`test_rhi_x11_runtime`）在无显示环境 exit 77 = UNAVAILABLE，属预期。

- [ ] **Step 6: Commit**

```bash
git add engine/tests/test_rhi_opengl_compat_fallback_contract.cmake \
        engine/tests/gl_fallback_whitelist.txt \
        engine/tests/test_no_hidden_gl_fallback.cmake engine/CMakeLists.txt
git commit -m "test: pin compat-period opengl fallback (explicit, logged, whitelisted)"
```

---

### Task 6: OpenGL 删除执行（breaking，单独 commit `feat!: remove opengl backend`）

**Files:**
- Test（gate）: `engine/tests/test_opengl_removal_gate.cmake`
- Create: `docs/rhi_opengl_removal_migration.md`
- Create: `docs/rhi_opengl_removal_signoff.md`
- Modify/Delete: `engine/CMakeLists.txt`（删 glad target :400-407、删 `glad` 链接项 :443、删 GL 链接 :996/:1002/:1018、selector 移除 `opengl` 值 :130-140、删 `test_rhi_x11_runtime` GL-only 注册 :1598-1605）；`engine/src/rhi/rhi.c`（删 `#include <rhi/rhi_gl.c>` else 分支 :413-414）；删除 `engine/src/rhi/rhi_gl.c`；`engine/tests/gl_fallback_whitelist.txt`（移除引擎 RHI 行）；`engine/assets/rhi_backend_rollout.json`（移除全部 `opengl`，`config_version` 1→2）；`README.md`（顶部 migration notice）；`engine/tests/test_rhi_backend_selection.cmake`（同步更新 selector 断言，opengl 值此后必须 FATAL_ERROR）

**Interfaces:**
- Consumes: Task 0 前置闸门；Task 2 clean-room 脚本；Task 5 白名单扫描；规格 §6 的 11 条删除条件。
- Produces: 无 GL 的最终 release target；`test_opengl_removal_gate`（11 条件可执行检查，长期保留防回潮）；migration notice 文档。

- [ ] **Step 1: 写删除 gate 脚本 `engine/tests/test_opengl_removal_gate.cmake`（规格 §6 十一条的可执行化）**

```cmake
# OpenGL removal gate: every check below maps 1:1 to spec §6 conditions 1-11.
# 用法: cmake -DREPO=<repo root> -P engine/tests/test_opengl_removal_gate.cmake
# 全绿 exit 0；任一条件未满足即 FATAL_ERROR 并指明条件号。
if(NOT DEFINED REPO)
    message(FATAL_ERROR "REPO is required")
endif()
set(LEDGER "${REPO}/docs/rhi_backend_evidence.md")

function(require_grep_file file pattern cond_no desc)
    file(READ "${file}" text)
    string(REGEX MATCH "${pattern}" hit "${text}")
    if(NOT hit)
        message(FATAL_ERROR "§6.${cond_no} UNMET: ${desc} (pattern '${pattern}' not found in ${file})")
    endif()
    message(STATUS "§6.${cond_no} OK: ${desc}")
endfunction()

# 条件 1: Android/Linux/Steam Vulkan 已认证（GPU_RUNTIME + BENCHMARK_COMPARABLE）
require_grep_file("${LEDGER}" "[Aa]ndroid.*[Vv]ulkan.*GPU_RUNTIME" 1 "Android×Vulkan GPU_RUNTIME")
require_grep_file("${LEDGER}" "[Ll]inux.*[Vv]ulkan.*BENCHMARK_COMPARABLE" 1 "Linux×Vulkan benchmark")
require_grep_file("${LEDGER}" "[Ss]team.*[Vv]ulkan.*GPU_RUNTIME" 1 "Steam×Vulkan GPU_RUNTIME")
# 条件 2: macOS/iOS 原生 Metal 真机 GPU_RUNTIME（禁止 MoltenVK 顶替：行内不得含 MoltenVK）
file(READ "${LEDGER}" ledger)
string(REGEX MATCH "[Mm]ac[Oo]s[^\n]*[Mm]etal[^\n]*GPU_RUNTIME" m_row "${ledger}")
if(NOT m_row OR m_row MATCHES "MoltenVK")
    message(FATAL_ERROR "§6.2 UNMET: macOS native Metal GPU_RUNTIME row (MoltenVK rows do not count)")
endif()
string(REGEX MATCH "i[Oo]s[^\n]*[Mm]etal[^\n]*GPU_RUNTIME" i_row "${ledger}")
if(NOT i_row OR i_row MATCHES "MoltenVK")
    message(FATAL_ERROR "§6.2 UNMET: iOS native Metal GPU_RUNTIME row")
endif()
message(STATUS "§6.2 OK: macOS/iOS native Metal GPU_RUNTIME")
# 条件 3: Windows D3D12 GPU_RUNTIME + BENCHMARK_COMPARABLE
require_grep_file("${LEDGER}" "[Ww]indows.*D3D12.*GPU_RUNTIME" 3 "Windows×D3D12 GPU_RUNTIME")
require_grep_file("${LEDGER}" "[Ww]indows.*D3D12.*BENCHMARK_COMPARABLE" 3 "Windows×D3D12 benchmark")
# 条件 4: renderer/UI 不再依赖 OpenGL（无 GL 后端分支消费者）
file(GLOB_RECURSE renderer_srcs "${REPO}/engine/src/renderer/*.[ch]")
foreach(f IN LISTS renderer_srcs)
    file(READ "${f}" c)
    if(c MATCHES "ENGINE_RHI_BACKEND_OPENGL|rhi_gl\\.c")
        message(FATAL_ERROR "§6.4 UNMET: GL dependency in ${f}")
    endif()
endforeach()
message(STATUS "§6.4 OK: renderer has no GL backend branch")
# 条件 5: 无生产 consumer 依赖 OpenGL（break_myui / dxx_core / apps 无 GL token）
foreach(f IN ITEMS
        "${REPO}/engine/src/ui/myui_break.c"
        "${REPO}/engine/src/myui/myr/my_vgcanvas_break_rhi.c")
    if(EXISTS "${f}")
        file(READ "${f}" c)
        if(c MATCHES "glad|opengl32|rhi_gl")
            message(FATAL_ERROR "§6.5 UNMET: production consumer depends on GL: ${f}")
        endif()
    endif()
endforeach()
message(STATUS "§6.5 OK: no production consumer depends on GL")
# 条件 6/7/8 在删除后由 CI 全量验证（clean-room 无 GL 构建 + 各平台 link/startup），
# 此处断言前置：clean-room 脚本存在且无 GL 变体可用。
if(NOT EXISTS "${REPO}/engine/tools/clean_room_build.sh")
    message(FATAL_ERROR "§6.7 prereq UNMET: clean_room_build.sh missing")
endif()
message(STATUS "§6.7 prereq OK: clean-room script present (post-removal run required)")
# 条件 9: migration notice 已发布
if(NOT EXISTS "${REPO}/docs/rhi_opengl_removal_migration.md")
    message(FATAL_ERROR "§6.9 UNMET: docs/rhi_opengl_removal_migration.md missing")
endif()
message(STATUS "§6.9 OK: migration notice present")
# 条件 10: 旧版本有可回滚 tag（签名 + 离线 artifact 记录于 runbook §4/§5）
file(READ "${REPO}/docs/rhi_rollback_runbook.md" rb)
if(NOT rb MATCHES "git tag -s" OR NOT rb MATCHES "SHA256SUMS")
    message(FATAL_ERROR "§6.10 UNMET: rollback runbook lacks signed-tag/offline-artifact procedure")
endif()
message(STATUS "§6.10 OK: rollback path documented (signed tag + offline artifact)")
# 条件 11: 发布负责人书面确认
if(NOT EXISTS "${REPO}/docs/rhi_opengl_removal_signoff.md")
    message(FATAL_ERROR "§6.11 UNMET: signoff doc missing")
endif()
file(READ "${REPO}/docs/rhi_opengl_removal_signoff.md" so)
if(NOT so MATCHES "APPROVED" OR NOT so MATCHES "@[a-z0-9-]+")
    message(FATAL_ERROR "§6.11 UNMET: signoff must contain APPROVED and a @github-owner")
endif()
message(STATUS "§6.11 OK: written signoff present")
message(STATUS "OPENGL REMOVAL GATE: ALL 11 CONDITIONS GREEN")
```

注册（label 加 `release_gate`，默认套件照常运行）：

```cmake
    add_test(NAME test_opengl_removal_gate
        COMMAND ${CMAKE_COMMAND}
            -DREPO=${CMAKE_CURRENT_SOURCE_DIR}/..
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_opengl_removal_gate.cmake)
    set_tests_properties(test_opengl_removal_gate PROPERTIES
        LABELS "headless;platform_contract;release_gate")
```

- [ ] **Step 2: 运行 gate 确认失败（red）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_opengl_removal_gate$' --output-on-failure
```
Expected: FAIL 于首个未满足的条件（正常情况为 §6.9 migration notice 缺失；若台账行等级不足则更早失败——此时**停止删除流程**，回对应计划补证据，不得修改 gate 放水）。

- [ ] **Step 3: 发布 migration notice 与 signoff（使 §6.9/§6.11 转绿）**

`docs/rhi_opengl_removal_migration.md`：

```markdown
# OpenGL 后端移除迁移指南（v2.0.0, breaking）

**自 v2.0.0 起，引擎 RHI 的 OpenGL 后端已删除。** `ENGINE_RHI_BACKEND=opengl` 不再被接受
（configure 期 FATAL_ERROR）。

## 影响与迁移

| 平台 | 旧默认 | 新默认 | 迁移动作 |
|---|---|---|---|
| Linux X11/Wayland | opengl(auto) | vulkan | 无；Vulkan 驱动缺失的环境停留在 v1.x |
| Windows | vulkan | d3d12（fallback vulkan） | 无；D3D12 需求见 docs/rhi_metal_d3d12_feature_matrix.md |
| macOS/iOS | vulkan(MoltenVK) | metal | 无；不再分发 MoltenVK 构建 |
| Android | vulkan | vulkan | 无 |
| Steam (Linux/Windows) | 随平台 | 随平台 | Proton 仅兼容验证路径，见 docs/rhi_backend_evidence.md |

## 无法迁移的环境

无 Vulkan/Metal/D3D12 能力的部署目标：停留在最后一个 v1.x 签名 tag（见
docs/rhi_rollback_runbook.md §4），该分支仅接受安全修复。

## 构建变更

- 移除：glad target、`rhi_gl.c`、GL/EGL/opengl32 链接、GL shader 路径、GL runtime 测试。
- myui 的 GL canvas 演示后端（MYUI_GL_DESKTOP/MYUI_GLES2）与引擎 RHI 无关，保留但默认 OFF；
  生产 UI 路径一律走 RHI vgcanvas（break_myui）。
```

`docs/rhi_opengl_removal_signoff.md`：

```markdown
# OpenGL 删除书面确认（spec §6.11）

- 决策：在 v2.0.0 中删除 OpenGL RHI 后端（breaking）。
- 依据：docs/rhi_backend_evidence.md 全部目标平台认证行（GPU_RUNTIME + 收据）；gate 脚本
  test_opengl_removal_gate 全绿记录：<CI run URL 或本地执行日期+commit>。
- 状态：APPROVED
- 签署：@konyka（产品/发布负责人），<日期>
```

README.md 顶部（标题行之后）插入：

```markdown
> **Breaking change (v2.0.0):** OpenGL 后端已移除，迁移指南见
> [docs/rhi_opengl_removal_migration.md](docs/rhi_opengl_removal_migration.md)。
> 需要 OpenGL 的部署停留在 v1.x 签名 tag。
```

- [ ] **Step 4: 重跑 gate 至全绿，然后才执行删除**

Run:
```bash
ctest --test-dir build-gate -R '^test_opengl_removal_gate$' --output-on-failure
```
Expected: PASS，输出 `OPENGL REMOVAL GATE: ALL 11 CONDITIONS GREEN`。**未全绿禁止进入下一步。**

删除动作（逐条执行并立即验证编译）：

```bash
git rm engine/src/rhi/rhi_gl.c
```

`engine/src/rhi/rhi.c`：删除 `#else / #include <rhi/rhi_gl.c> / #endif` 中的 else 分支（保留 `#ifdef ENGINE_VULKAN` 对应的多后端选择链——计划 A 拆分后的实际形态为「`rhi.c` 不再 unity-include 任何后端」，按拆分后的真实代码删除 GL 分支）。

`engine/CMakeLists.txt`：
- 删除 `add_library(glad STATIC external/glad.c)` 整块（:400-407）；
- `target_link_libraries(engine PRIVATE glad lua stb_image)`（:443）改为去掉 `glad`；
- 删除 Linux GL 链接分支中的 `GL EGL`（:996）与 `GL`（:1002），Windows `opengl32`（:1018）——删除后这些分支若只剩空内容，整个 `else()`（非 Vulkan）分支一并删除；
- selector（:130-140）：合法值改为 `auto|vulkan|metal|d3d12`，错误文案同步；删除 `ENGINE_RHI_BACKEND STREQUAL "opengl"` 分支；
- 删除 `test_rhi_x11_runtime` 的 GL-only 注册（:1598-1605，该测试只在 `NOT ENGINE_VULKAN` 时存在）；
- `set_property(CACHE ENGINE_RHI_BACKEND PROPERTY STRINGS ...)` 同步。

`engine/tests/test_rhi_backend_selection.cmake`：更新断言——`opengl` 值现在必须触发 FATAL_ERROR；把 `"ENGINE_RHI_BACKEND must be auto, opengl, or vulkan"` 等旧文案断言更新为新文案。

`engine/tests/gl_fallback_whitelist.txt`：移除 `src/rhi/rhi_gl.c`、`src/rhi/rhi.c`、`external/glad.*`、`CMakeLists.txt`（glad/opengl32/opengl selector）、`tests/test_rhi_x11_runtime.c` 六行；保留 myui 行与注释。

`engine/assets/rhi_backend_rollout.json`：`linux`/`steam-linux` 的 allowed/fallback_chain 移除 `opengl`，`config_version` 1→2，重算 `signature.value`（Task 3 Step 6 的命令）。

`engine/tests/test_rhi_opengl_compat_fallback_contract.cmake`：反转语义为「删除后不存在隐藏 GL fallback」——三个断言分别改为：selector 不再含 `"opengl"`（FIND 必须 EQUAL -1）、rhi.c 不含 `compat-override`、rollout JSON 不含 `"opengl"`；测试重命名注册为 `test_opengl_removed_contract`。

- [ ] **Step 5: 删除后验证（§6.6/§6.7/§6.8 的实际执行）**

Run:
```bash
# 6.6 GL 痕迹消失
grep -rn "rhi_gl\|glad\|opengl32\|ENGINE_RHI_BACKEND_OPENGL" engine/src engine/CMakeLists.txt || echo "GL-FREE"
# 6.7 clean-room 无 GL 构建
bash engine/tools/clean_room_build.sh "$PWD" /tmp/clean-room-nogl --backend vulkan
# 6.8 各平台 link/startup：本机 headless 全量
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
cmake --build build-gate --parallel && \
ctest --test-dir build-gate -LE "graphics|fuzz" --output-on-failure && \
ctest --test-dir build-gate -R '^test_no_hidden_gl_fallback$|^test_opengl_removed_contract$|^test_rhi_rollout_config_contract$' --output-on-failure
```
Expected: `GL-FREE`；clean-room 输出 `CLEAN-ROOM OK` 且 configure log 无 OpenGL 发现；headless 全绿；三个契约测试 PASS。macOS/Android/Windows 的 link/startup 由 Task 7 的 CI lane 在 push 前验证（Task 10 gate）。

- [ ] **Step 6: 确认旧版本可回滚（§6.10 实检）**

Run:
```bash
git tag -l 'v1.*' | sort -V | tail -1 && \
git ls-remote --tags origin 'v1.*' | tail -1
```
Expected: 本地与远程均存在最后一个 v1.x 签名 tag（Task 9 在删除 commit 之前已打 v1 末版 tag 并推送——若尚不存在，先执行 Task 9 Step 2 的 v1 末版发布再回来）。手动触发一次 rollback-drill workflow 验证该 tag 可构建：`gh workflow run rollback-drill.yml -f tag=<v1.x.y>`，等待绿。

- [ ] **Step 7: Commit（breaking，独立提交）**

```bash
git add -A engine docs README.md
git commit -m "feat!: remove opengl backend

BREAKING CHANGE: ENGINE_RHI_BACKEND=opengl 不再可用；引擎 RHI 仅支持
vulkan/metal/d3d12。迁移指南: docs/rhi_opengl_removal_migration.md。
删除前置（spec §6 全 11 条）由 test_opengl_removal_gate 验证。"
```

---

### Task 7: CI lane 收尾分离（headless / native-surface / GPU-runtime / validation / benchmark / proton）

**Files:**
- Create: `engine/tools/make_evidence_receipt.cmake`
- Modify: `.github/workflows/ci.yml`（重排为六类 lane；删除 unpinned 包安装）
- Modify: `README.md`（CI badge 与构建矩阵表更新）
- Test: `engine/tests/test_evidence_receipt_schema.cmake`（收据字段级校验，入 headless 套件）

**Interfaces:**
- Consumes: `docs/rhi_benchmark_receipt_schema.md`（计划 A 骨架，字段：schema_version/timestamp/platform/os_version/backend/gpu/driver_version/cpu/ram/build_commit/build_config/command/metrics{fps_avg,fps_p1,frame_ms_avg,frame_ms_p99}/evidence_level/runner）；Task 2 的钉版 apt 包；Task 3 的 `RHIEVT` 日志。
- Produces: 六类 lane 的 job 名（`lane-headless-*`/`lane-native-surface-*`/`lane-gpu-runtime-*`/`lane-validation-*`/`lane-benchmark-*`/`lane-proton`）；每 lane 的 `evidence-receipt-<lane>-<platform>` artifact；Task 8 的台账升级消费这些收据链接。

- [ ] **Step 1: 写收据生成器 `engine/tools/make_evidence_receipt.cmake` 与其失败测试**

`engine/tools/make_evidence_receipt.cmake`：

```cmake
# make_evidence_receipt.cmake — emit a benchmark/evidence receipt JSON.
# 必填 -D: OUT PLATFORM BACKEND EVIDENCE_LEVEL RUNNER COMMAND_STR
# 可选 -D: GPU DRIVER_VERSION CPU RAM BUILD_COMMIT BUILD_CONFIG
#        FPS_AVG FPS_P1 FRAME_MS_AVG FRAME_MS_P99（benchmark lane 必填）
foreach(v OUT PLATFORM BACKEND EVIDENCE_LEVEL RUNNER COMMAND_STR)
    if(NOT DEFINED ${v})
        message(FATAL_ERROR "${v} is required")
    endif()
endforeach()
if(NOT EVIDENCE_LEVEL MATCHES "^(NONE|COMPILED|HEADLESS|NATIVE_SURFACE|GPU_RUNTIME|BENCHMARK_COMPARABLE|UNAVAILABLE)$")
    message(FATAL_ERROR "invalid evidence_level: ${EVIDENCE_LEVEL}")
endif()
string(TIMESTAMP ts "%Y-%m-%dT%H:%M:%SZ" UTC)
if(NOT DEFINED BUILD_COMMIT)
    set(BUILD_COMMIT "$ENV{GITHUB_SHA}")
    if(NOT BUILD_COMMIT)
        set(BUILD_COMMIT "local")
    endif()
endif()
if(EVIDENCE_LEVEL STREQUAL "BENCHMARK_COMPARABLE")
    foreach(m FPS_AVG FPS_P1 FRAME_MS_AVG FRAME_MS_P99)
        if(NOT DEFINED ${m})
            message(FATAL_ERROR "benchmark receipt requires ${m}")
        endif()
    endforeach()
    set(metrics "\"metrics\":{\"fps_avg\":${FPS_AVG},\"fps_p1\":${FPS_P1},\"frame_ms_avg\":${FRAME_MS_AVG},\"frame_ms_p99\":${FRAME_MS_P99}},")
else()
    set(metrics "")
endif()
file(WRITE "${OUT}"
"{\n  \"schema_version\": 1,\n  \"timestamp\": \"${ts}\",\n  \"platform\": \"${PLATFORM}\",\n  \"os_version\": \"$ENV{RUNNER_OS}\",\n  \"backend\": \"${BACKEND}\",\n  \"gpu\": \"${GPU}\",\n  \"driver_version\": \"${DRIVER_VERSION}\",\n  \"cpu\": \"${CPU}\",\n  \"ram\": \"${RAM}\",\n  \"build_commit\": \"${BUILD_COMMIT}\",\n  \"build_config\": \"${BUILD_CONFIG}\",\n  \"command\": \"${COMMAND_STR}\",\n  ${metrics}\n  \"evidence_level\": \"${EVIDENCE_LEVEL}\",\n  \"runner\": \"${RUNNER}\"\n}\n")
message(STATUS "receipt written: ${OUT}")
```

失败测试 `engine/tests/test_evidence_receipt_schema.cmake`（同时作为 schema 校验器，CI 每 lane 复用）：

```cmake
# test_evidence_receipt_schema.cmake — validate a receipt against the schema.
# -DRECEIPT=<abs path> ; 自验证模式: -DSELFTEST=1（生成样例再校验）
if(SELFTEST)
    set(tmp "${CMAKE_CURRENT_BINARY_DIR}/selftest_receipt.json")
    if(NOT EXISTS "${tmp}")
        message(FATAL_ERROR "SELFTEST receipt not generated: ${tmp} (receipt generator missing)")
    endif()
    set(RECEIPT "${tmp}")
endif()
if(NOT DEFINED RECEIPT)
    message(FATAL_ERROR "RECEIPT is required")
endif()
file(READ "${RECEIPT}" json)
foreach(f schema_version timestamp platform backend build_commit command evidence_level runner)
    string(JSON v ERROR_VARIABLE e GET "${json}" ${f})
    if(NOT "${e}" STREQUAL "NOTFOUND" OR "${v}" STREQUAL "" OR "${v}" MATCHES "NOTFOUND")
        message(FATAL_ERROR "receipt field missing/empty: ${f}")
    endif()
endforeach()
string(JSON lvl GET "${json}" evidence_level)
if(NOT lvl MATCHES "^(NONE|COMPILED|HEADLESS|NATIVE_SURFACE|GPU_RUNTIME|BENCHMARK_COMPARABLE|UNAVAILABLE)$")
    message(FATAL_ERROR "bad evidence_level: ${lvl}")
endif()
if(lvl STREQUAL "BENCHMARK_COMPARABLE")
    foreach(m fps_avg fps_p1 frame_ms_avg frame_ms_p99)
        string(JSON v ERROR_VARIABLE e GET "${json}" metrics ${m})
        if(NOT "${e}" STREQUAL "NOTFOUND")
            message(FATAL_ERROR "benchmark receipt missing metrics.${m}")
        endif()
    endforeach()
endif()
message(STATUS "receipt schema OK: ${RECEIPT}")
```

注册（先注册、生成器尚无时 red）：

```cmake
    add_test(NAME test_evidence_receipt_schema
        COMMAND ${CMAKE_COMMAND}
            -DRECEIPT=${CMAKE_CURRENT_BINARY_DIR}/sample_receipt.json
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_evidence_receipt_schema.cmake)
    set_tests_properties(test_evidence_receipt_schema PROPERTIES
        LABELS "headless;platform_contract")
```

- [ ] **Step 2: 运行确认失败（red）→ 生成样例转绿（green）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_evidence_receipt_schema$' --output-on-failure
```
Expected(red): FAIL（生成器/样例不存在）。
转绿：
```bash
cmake -DOUT=build-gate/sample_receipt.json -DPLATFORM=windows -DBACKEND=vulkan \
  -DEVIDENCE_LEVEL=GPU_RUNTIME -DRUNNER=local -DCOMMAND_STR="ctest -L graphics" \
  -DGPU="(fill)" -DDRIVER_VERSION="(fill)" -DCPU="(fill)" -DRAM="(fill)" -DBUILD_CONFIG=Debug \
  -P engine/tools/make_evidence_receipt.cmake && \
ctest --test-dir build-gate -R '^test_evidence_receipt_schema$' --output-on-failure
```
Expected: PASS 输出 `receipt schema OK`。把样例生成并入 CMake（在 `add_test` 前用 `execute_process` 调生成器产生 `sample_receipt.json`），使套件自洽。

- [ ] **Step 3: 重排 `.github/workflows/ci.yml` 为六类 lane**

映射（旧 job → 新 lane）：
- `gl`（OpenGL lane）→ **Task 6 删除后移除**；兼容期内改名 `lane-gpu-runtime-linux-gl` 并标注 deprecation。
- `vk`、`linux-graphics-smoke` → GPU-runtime lane。
- `linux-clang-release`、`linux-gcc-sanitizers`、`linux-gcc-tsan`、`windows-clang`、`windows-clang-asan` → headless lane。
- `wayland-gl`/`wayland-vk`/`windows-clang` 的 runtime 步骤/`macos-vulkan` 的 Cocoa 运行时 → native-surface lane。
- 新增 validation、benchmark、proton 三 lane。

每个 job 尾部统一挂收据上传 step（模板，所有 lane 逐字复用，仅改 `lane`/`platform`/`backend`/`evidence_level` 变量）：

```yaml
      - name: Emit evidence receipt
        if: always()
        run: |
          cmake -DOUT=receipt.json -DPLATFORM=linux-x11 -DBACKEND=vulkan \
            -DEVIDENCE_LEVEL=GPU_RUNTIME -DRUNNER="$RUNNER_NAME" \
            -DCOMMAND_STR="ctest -L graphics" -DBUILD_CONFIG=Debug \
            -DGPU="$(vulkaninfo --summary 2>/dev/null | grep -m1 deviceName || echo unknown)" \
            -DDRIVER_VERSION=unknown -DCPU="$(uname -m)" -DRAM=unknown \
            -P engine/tools/make_evidence_receipt.cmake
          cmake -DRECEIPT=receipt.json -P engine/tests/test_evidence_receipt_schema.cmake
      - uses: actions/upload-artifact@v4
        if: always()
        with:
          name: evidence-receipt-gpu-runtime-linux
          path: receipt.json
```

lane 定义（新增/重写部分全文；沿用现有 steps 的 job 仅列改名与新增 step）：

```yaml
  # ---- lane: headless（无显示依赖；原 5 个 headless job 改名，steps 不变，尾部加上传模板，evidence_level=HEADLESS）----
  lane-headless-linux-clang:      # 原 linux-clang-release
  lane-headless-linux-gcc-asan:   # 原 linux-gcc-sanitizers
  lane-headless-linux-gcc-tsan:   # 原 linux-gcc-tsan
  lane-headless-windows-clang:    # 原 windows-clang（保留 win32 runtime step，但其收据归入 native-surface）
  lane-headless-windows-asan:     # 原 windows-clang-asan

  # ---- lane: native-surface（真实 surface 创建/resize/销毁；evidence_level=NATIVE_SURFACE）----
  lane-native-surface-wayland:    # 原 wayland-vk（Task 6 后 wayland-gl 删除）
  lane-native-surface-win32:      # 自 windows-clang 拆出：仅 test_platform_win32_runtime + win32 runtime trio
  lane-native-surface-cocoa:      # 自 macos-vulkan 拆出：test_platform_cocoa_runtime

  # ---- lane: GPU-runtime（真实 GPU/软渲染 ICD 跑通帧；evidence_level=GPU_RUNTIME）----
  lane-gpu-runtime-linux-vk:      # 原 vk + linux-graphics-smoke 合并（lavapipe, VK_ICD_FILENAMES 钉 lvp）
  lane-gpu-runtime-macos-metal:   # 计划 C 新增（真机/self-hosted runner；GitHub hosted 无 Metal session → UNAVAILABLE 收据）
  lane-gpu-runtime-windows-d3d12: # 计划 D 新增（self-hosted GPU runner；hosted → UNAVAILABLE 收据）

  # ---- lane: validation（validation layers + D3D12 debug layer）----
  lane-validation-linux-vk:
    name: "lane: validation (VK_LAYER_KHRONOS_validation)"
    runs-on: ubuntu-24.04
    timeout-minutes: 25
    steps:
      - uses: actions/checkout@v4
      - name: Install pinned toolchain
        run: |
          sudo apt-get update
          sudo apt-get install -y --no-install-recommends \
            clang-18 lld-18 cmake=3.28.* ninja-build libx11-dev libxrandr-dev \
            libvulkan-dev=1.3.275.* libshaderc-dev=2023.8.* \
            libfreetype6-dev fonts-noto-cjk mesa-vulkan-drivers xvfb x11-utils \
            vulkan-validationlayers
      - name: Configure / build
        run: |
          cmake -S engine -B build -G Ninja -DCMAKE_C_COMPILER=clang \
            -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=vulkan
          cmake --build build --parallel
      - name: Run graphics suite under validation layers
        run: |
          export VK_INSTANCE_LAYERS=VK_LAYER_KHRONOS_validation
          vk_icd="$(find /usr/share/vulkan/icd.d -maxdepth 1 -type f -name '*lvp*.json' -print -quit)"
          test -n "$vk_icd"
          export VK_ICD_FILENAMES="$vk_icd"
          Xvfb :99 -screen 0 1280x720x24 -ac >/tmp/xvfb.log 2>&1 &
          trap 'kill $!' EXIT
          export DISPLAY=:99
          until xdpyinfo >/dev/null 2>&1; do sleep 0.1; done
          ctest --test-dir build -L graphics --output-on-failure 2>&1 | tee /tmp/val.log
          ! grep -q "VUID-" /tmp/val.log   # 任何 validation error 即 lane 失败
      # + 收据上传模板（evidence_level=GPU_RUNTIME, lane=validation）

  # ---- lane: benchmark（evidence_level=BENCHMARK_COMPARABLE，含 metrics）----
  lane-benchmark-linux-vk:
    name: "lane: benchmark (linux vulkan)"
    runs-on: ubuntu-24.04
    timeout-minutes: 30
    steps:
      - uses: actions/checkout@v4
      # 同 validation lane 的安装/构建步骤
      - name: Run benchmark
        run: |
          # 运行 benchmark 可执行（计划 B/D 交付的 rhi benchmark target），输出 metrics.json
          ./build/rhi_benchmark --seconds 20 --headless-lavapipe --out metrics.json
      - name: Emit benchmark receipt
        run: |
          cmake -DOUT=receipt.json -DPLATFORM=linux-x11 -DBACKEND=vulkan \
            -DEVIDENCE_LEVEL=BENCHMARK_COMPARABLE -DRUNNER="$RUNNER_NAME" \
            -DCOMMAND_STR="rhi_benchmark --seconds 20" \
            -DFPS_AVG=$(python3 -c "import json;print(json.load(open('metrics.json'))['fps_avg'])") \
            -DFPS_P1=$(python3 -c "import json;print(json.load(open('metrics.json'))['fps_p1'])") \
            -DFRAME_MS_AVG=$(python3 -c "import json;print(json.load(open('metrics.json'))['frame_ms_avg'])") \
            -DFRAME_MS_P99=$(python3 -c "import json;print(json.load(open('metrics.json'))['frame_ms_p99'])") \
            -P engine/tools/make_evidence_receipt.cmake
          cmake -DRECEIPT=receipt.json -P engine/tests/test_evidence_receipt_schema.cmake
      - uses: actions/upload-artifact@v4
        with: { name: evidence-receipt-benchmark-linux-vk, path: receipt.json }

  # ---- lane: proton（兼容验证，不计入 Windows D3D12 证据；schedule + 手动触发）----
  lane-proton:
    name: "lane: proton compatibility (reference only)"
    runs-on: ubuntu-24.04
    timeout-minutes: 40
    if: github.event_name == 'schedule' || github.event_name == 'workflow_dispatch'
    steps:
      - uses: actions/checkout@v4
      - name: Build under Steam Runtime (pinned)
        run: |
          # steamrt sniper 钉 digest；不可得时输出 UNAVAILABLE 收据并 exit 0
          docker run --rm -v "$GITHUB_WORKSPACE":/src -w /src \
            registry.gitlab.steamos.cloud/steamrt/sniper/sdk@sha256:<执行时以 crane/docker manifest 实测 digest 填入> \
            bash -c "cmake -S engine -B build -G Ninja -DCMAKE_BUILD_TYPE=Release && cmake --build build --parallel && ctest --test-dir build -LE 'graphics|fuzz' --output-on-failure" \
            || { echo '{"schema_version":1,"evidence_level":"UNAVAILABLE","platform":"proton","backend":"vulkan","command":"steamrt build","runner":"'"$RUNNER_NAME"'","timestamp":"'"$(date -u +%FT%TZ)"'","build_commit":"'"$GITHUB_SHA"'"}' > receipt.json; }
      - uses: actions/upload-artifact@v4
        if: always()
        with: { name: evidence-receipt-proton, path: receipt.json }
```

`on:` 触发器追加：

```yaml
on:
  push:
    branches: [master]
  pull_request:
    branches: [master]
  schedule:
    - cron: "23 3 * * 1"   # 每周一 03:23 UTC（避开整点）
  workflow_dispatch:
```

- [ ] **Step 4: README.md CI badge 与矩阵更新**

README.md 中 CI badge 行替换为（shields endpoint 按 workflow 名 + lane 过滤不易，采用 workflow 级 badge + 矩阵表）：

```markdown
[![CI](https://github.com/konyka/break/actions/workflows/ci.yml/badge.svg)](https://github.com/konyka/break/actions/workflows/ci.yml)
[![Rollback drill](https://github.com/konyka/break/actions/workflows/rollback-drill.yml/badge.svg)](https://github.com/konyka/break/actions/workflows/rollback-drill.yml)

CI lanes: headless (linux clang/gcc±sanitizers, windows clang±asan) /
native-surface (wayland, win32, cocoa) / GPU-runtime (linux vk lavapipe, macOS Metal, Windows D3D12) /
validation (KHRONOS_validation + D3D12 debug) / benchmark (receipt artifacts) / proton (参考，周跑)。
证据收据: 每个 lane 上传 `evidence-receipt-*` artifact，schema 见 docs/rhi_benchmark_receipt_schema.md。
```

- [ ] **Step 5: 验证**

Run:
```bash
ctest --test-dir build-gate -R 'receipt|locked_dependencies|clean_room' --output-on-failure && \
python3 - <<'EOF'
import re
text = open('.github/workflows/ci.yml').read()
for lane in ['lane-headless', 'lane-native-surface', 'lane-gpu-runtime', 'lane-validation', 'lane-benchmark', 'lane-proton']:
    assert lane in text, f"missing {lane}"
assert 'libvulkan-dev ' not in text.replace('libvulkan-dev=', ''), "unpinned libvulkan-dev remains"
print("ci.yml lanes OK")
EOF
```
Expected: 契约测试全 PASS；脚本输出 `ci.yml lanes OK`。push 后在 Actions 页确认六类 lane 全部出现且各自上传了 `evidence-receipt-*` artifact（push 属 Task 10，此处仅记录待确认项）。

- [ ] **Step 6: Commit**

```bash
git add engine/tools/make_evidence_receipt.cmake engine/tests/test_evidence_receipt_schema.cmake \
        engine/CMakeLists.txt .github/workflows/ci.yml README.md
git commit -m "ci: split into six evidence lanes (headless/native-surface/gpu-runtime/validation/benchmark/proton) with receipt artifacts"
```

---

### Task 8: 文档全集收尾

**Files:**
- Modify: `README.md`（后端矩阵终态）
- Modify: `docs/Build_Guide.md`（依赖锁定节 + 新构建矩阵 :479-589 + CI 矩阵 :719-732）
- Modify: `docs/Architecture_Overview.md`（§9 平台支持 :243-260、后端链接模型、矩阵 :334-344）
- Modify: `docs/vulkan_support_matrix.md`（充实）
- Modify: `docs/rhi_metal_d3d12_feature_matrix.md`（充实）
- Modify: `docs/rhi_backend_evidence.md`（全部行升级至认证等级并附收据链接）

**Interfaces:**
- Consumes: Task 1 锁定清单；Task 7 lane 名与收据 artifact 名；Task 6 migration notice。
- Produces: 发布文档终态；Task 9 发布说明引用本 Task 的矩阵。

- [ ] **Step 1: README.md 后端矩阵终态**

替换 README 中后端/平台段落为：

```markdown
## 渲染后端（v2.0.0 起）

| 平台 | 后端 | 证据等级 | 收据 |
|---|---|---|---|
| Windows | D3D12（fallback Vulkan） | GPU_RUNTIME + BENCHMARK_COMPARABLE | CI lane-gpu-runtime-windows-d3d12 / lane-benchmark |
| Linux / Steam Deck | Vulkan | GPU_RUNTIME + BENCHMARK_COMPARABLE | CI lane-gpu-runtime-linux-vk / lane-benchmark |
| macOS / iOS | Metal（原生） | GPU_RUNTIME（真机） | docs/rhi_backend_evidence.md 真机收据 |
| Android | Vulkan | GPU_RUNTIME | docs/rhi_backend_evidence.md |
| Proton | Vulkan（兼容参考） | 见 proton lane | 不计入 Windows 证据 |
| OHOS | UNAVAILABLE | fail-closed | — |
| OpenGL | **已移除**（最后版本 v1.x） | — | docs/rhi_opengl_removal_migration.md |

构建期单后端、直接符号链接：`-DENGINE_RHI_BACKEND=auto|vulkan|metal|d3d12`。
```

- [ ] **Step 2: Build_Guide.md 依赖锁定节 + 矩阵更新**

在 `docs/Build_Guide.md` 构建矩阵节（:479-589 区域）之前插入新节：

```markdown
## 锁定依赖（v2.0.0 起）

全部构建/测试/发布依赖钉版，机器可校验清单见 `engine/external/locked_dependencies.json`
（契约测试 `test_locked_dependencies`）。要点：CMake >=3.25,<4.0（CI 钉 3.31.6）；
clang >=17 / gcc >=12 / MSVC >=19.38；vendored Vulkan SDK 1.4.357.0（含 shaderc、
glslang 16.4.0、dxc 1.9.0.5399、VK_LAYER_KHRONOS_validation）；Android NDK r27c；
Xcode >=15.4；Windows SDK 10.0.26100.0；D3D12 Agility SDK 1.616.0（runtime-shipped）。
禁止使用 "latest" 或未钉版系统包构建 release。人读说明：engine/external/LOCKED_DEPENDENCIES.md。
```

构建矩阵表（:479-589）重写为按 lane 分组的六行结构（headless/native-surface/GPU-runtime/validation/benchmark/proton，每行：lane 名、runner、后端、配置、收据 artifact 名）；CI 矩阵（:719-732）同步替换为同一六 lane 表。

- [ ] **Step 3: Architecture_Overview.md 终态**

- §9 平台支持（:243-260）：按 Step 1 的矩阵更新（含 OHOS UNAVAILABLE fail-closed 与 Proton 参考注记）。
- RHI 分层图：后端链接模型改为终态描述——「编译期单后端、独立静态库 `engine_rhi_vulkan|engine_rhi_metal|engine_rhi_d3d12`（兼容期曾含 `engine_rhi_opengl`，v2.0.0 移除），`engine` 核心库仅含 RHI_CORE_SOURCES，`engine_link_rhi_backend(<target>)` 链接恰好一个后端；headless 测试链接 `engine_rhi_headless`（全入口 fail-closed）」。删除一切 unity-include 的存量描述。
- 矩阵（:334-344）：与 README 矩阵一致。

- [ ] **Step 4: 充实三个矩阵/台账文档**

- `docs/vulkan_support_matrix.md`：逐平台行（linux-x11/linux-wayland/android/windows-fallback/proton/steam-deck），列：最低 Vulkan 版本（1.2，与 shaderc target env 对齐）、已用扩展清单、证据等级、收据链接、已知限制（lavapipe 软渲染行必须标注 `software-rendering`，不计入硬件 GPU 证据）。
- `docs/rhi_metal_d3d12_feature_matrix.md`：Metal/D3D12 能力对照（push constants vs root constants vs argument buffers、raytracing Tier、mesh shader、swapchain 语义），每行标注消费该能力的 renderer 功能与契约测试名。
- `docs/rhi_backend_evidence.md`：全部目标平台行升级到认证等级（GPU_RUNTIME 或 BENCHMARK_COMPARABLE），每行「收据」列填 Task 7 的 CI run URL（`https://github.com/konyka/break/actions/runs/<id>` + artifact 名）或真机本地收据（日期/机器/GPU/驱动/命令/结果）。**任何行找不到收据就保持原等级并在备注写明缺口——禁止无收据升级。**

- [ ] **Step 5: 验证**

Run:
```bash
ctest --test-dir build-gate -R 'rollback_runbook|opengl_removal_gate' --output-on-failure && \
grep -c "engine_rhi_opengl" docs/Architecture_Overview.md || true
```
Expected: 契约测试 PASS；`Architecture_Overview.md` 中 `engine_rhi_opengl` 仅可出现在「v2.0.0 已移除」的历史注记语境（人工核对），矩阵正文不得再把它列为可用后端。

- [ ] **Step 6: Commit**

```bash
git add README.md docs/Build_Guide.md docs/Architecture_Overview.md \
        docs/vulkan_support_matrix.md docs/rhi_metal_d3d12_feature_matrix.md \
        docs/rhi_backend_evidence.md
git commit -m "docs: finalize backend matrices, locked deps section, and certified evidence ledger"
```

---

### Task 9: 发布流程（semver / 签名 tag / 离线 artifact 包）

**Files:**
- Modify: `engine/CMakeLists.txt`（`project(PureCEngine LANGUAGES C)` → `project(PureCEngine VERSION <x.y.z> LANGUAGES C)`）
- Create: `engine/tools/package_release.sh`
- Test: `engine/tests/test_release_package_contract.cmake`

**Interfaces:**
- Consumes: Task 1 锁定清单（artifact 清单引用其版本）；Task 6 的删除 commit（major bump 触发点）；Task 4 runbook §4/§5。
- Produces: 版本规则（OpenGL 删除 = major：v1.x → v2.0.0）；签名 tag；离线 artifact 包（tarball + `SHA256SUMS` + manifest）。Task 10 的 push 命令依赖本 Task 的 tag 名。

- [ ] **Step 1: 写失败的发布包契约测试 `engine/tests/test_release_package_contract.cmake`**

```cmake
# Contract test: release packaging script carries the full offline content list.
# -DPACKAGER=<abs engine/tools/package_release.sh> -DENGINE_CMAKE=<abs engine/CMakeLists.txt>
if(NOT DEFINED PACKAGER OR NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "PACKAGER and ENGINE_CMAKE are required")
endif()
if(NOT EXISTS "${PACKAGER}")
    message(FATAL_ERROR "release packager missing: ${PACKAGER}")
endif()
file(READ "${PACKAGER}" pk)
foreach(item "SHA256SUMS" "MANIFEST" "D3D12Core" "metallib" ".dxil" ".spv"
             "rhi_backend_rollout.json" "locked_dependencies.json" "receipt")
    string(FIND "${pk}" "${item}" off)
    if(off EQUAL -1)
        message(FATAL_ERROR "packager does not handle required content: ${item}")
    endif()
endforeach()
if(pk MATCHES "latest")
    message(FATAL_ERROR "packager must not reference 'latest'")
endif()
file(READ "${ENGINE_CMAKE}" cm)
if(NOT cm MATCHES "project\\(PureCEngine VERSION [0-9]+\\.[0-9]+\\.[0-9]+")
    message(FATAL_ERROR "engine/CMakeLists.txt project() must carry an explicit semver VERSION")
endif()
message(STATUS "release package contract OK")
```

注册：

```cmake
    add_test(NAME test_release_package_contract
        COMMAND ${CMAKE_COMMAND}
            -DPACKAGER=${CMAKE_CURRENT_SOURCE_DIR}/tools/package_release.sh
            -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_release_package_contract.cmake)
    set_tests_properties(test_release_package_contract PROPERTIES
        LABELS "headless;platform_contract;release_gate")
```

- [ ] **Step 2: 运行确认失败（red）**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
ctest --test-dir build-gate -R '^test_release_package_contract$' --output-on-failure
```
Expected: FAIL，`release packager missing: .../engine/tools/package_release.sh`。

- [ ] **Step 3: 版本 bump 策略落地 + 打包脚本（green）**

semver 规则（写入 `docs/rhi_rollback_runbook.md` §5 下方一段）：
- 破坏性变更（本计划的 OpenGL 删除）= **major**（v1.x → v2.0.0）；
- 新后端/新能力 = minor；修复 = patch；
- 版本唯一来源：`engine/CMakeLists.txt` 的 `project(PureCEngine VERSION x.y.z)`；tag 名 `v<x.y.z>` 必须与之相等（契约测试比对）。

版本 bump：
```cmake
# engine/CMakeLists.txt:2
project(PureCEngine VERSION 2.0.0 LANGUAGES C)
```

tag 与版本一致性检查（追加进 `test_release_package_contract.cmake` 末尾）：

```cmake
# tag 名 v<x.y.z> 必须与 project() VERSION 相等；HEAD 无 tag 时跳过（发布前由
# git tag -v 人工核验，见 runbook §5）。
get_filename_component(engine_dir "${ENGINE_CMAKE}" DIRECTORY)
execute_process(COMMAND git tag --points-at HEAD
    WORKING_DIRECTORY "${engine_dir}" OUTPUT_VARIABLE tags_out
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
if(tags_out)
    string(REGEX MATCH "project\\(PureCEngine VERSION ([0-9]+\\.[0-9]+\\.[0-9]+)" vm "${cm}")
    set(proj_ver "${CMAKE_MATCH_1}")
    string(REPLACE "\n" ";" tag_list "${tags_out}")
    if(NOT "v${proj_ver}" IN_LIST tag_list)
        message(FATAL_ERROR "HEAD tag list (${tags_out}) does not contain v${proj_ver}")
    endif()
endif()
```

`engine/tools/package_release.sh`：

```bash
#!/usr/bin/env bash
# package_release.sh <repo_root> <build_dir> <out_dir> <version>
# 生成离线 artifact 包：每平台二进制 + shader 产物 + 配置 + 收据 + SHA256SUMS + MANIFEST。
set -euo pipefail
REPO="${1:?}"; BUILD="${2:?}"; OUT="${3:?}"; VER="${4:?}"
PKG="$OUT/purec-engine-$VER"
rm -rf "$PKG"; mkdir -p "$PKG"/{bin,shaders,config,evidence,docs}

# 二进制与运行时（存在的才收；缺失 = 该平台 UNAVAILABLE，记入 MANIFEST）
for f in "$BUILD"/engine_demo "$BUILD"/dxx_break "$BUILD"/libengine.a \
         "$BUILD"/libengine_rhi_vulkan.a "$BUILD"/libengine_rhi_metal.a \
         "$BUILD"/libengine_rhi_d3d12.a; do
    [ -f "$f" ] && cp "$f" "$PKG/bin/"
done
# D3D12 Agility SDK 运行时（Windows 包）
find "$BUILD" "$REPO/engine/external" -name 'D3D12Core.dll' 2>/dev/null | head -1 | while read -r d; do
    cp "$d" "$PKG/bin/"
done
# shader 产物：metallib（macOS/iOS）、DXIL（Windows）、SPIR-V（全部）
find "$BUILD" -name '*.metallib' -exec cp {} "$PKG/shaders/" \; 2>/dev/null || true
find "$BUILD" -name '*.dxil' -not -path '*/Testing/*' -exec cp {} "$PKG/shaders/" \; 2>/dev/null || true
find "$BUILD" -name '*.spv' -exec cp {} "$PKG/shaders/" \; 2>/dev/null || true
# 注意：repo 根的 d3d12_shader_gate.dxil 是冻结文件，永不进包（上面的 find 只扫 BUILD）。

# 配置与证据
cp "$REPO/engine/assets/rhi_backend_rollout.json" "$PKG/config/"
cp "$REPO/engine/external/locked_dependencies.json" "$PKG/config/"
cp "$REPO/docs/rhi_opengl_removal_migration.md" "$REPO/docs/rhi_rollback_runbook.md" "$PKG/docs/" 2>/dev/null || true
find "$BUILD" -name 'receipt*.json' -exec cp {} "$PKG/evidence/" \; 2>/dev/null || true

# MANIFEST + SHA256SUMS（离线可验）
( cd "$PKG" && find . -type f | sort > MANIFEST.txt && \
  { echo "version: $VER"; echo "commit: $(git -C "$REPO" rev-parse HEAD)"; \
    echo "locked_deps: config/locked_dependencies.json"; \
    echo "built: $(date -u +%FT%TZ)"; } > MANIFEST )
( cd "$PKG" && find . -type f ! -name SHA256SUMS -exec sha256sum {} + > SHA256SUMS )
( cd "$OUT" && tar -czf "purec-engine-$VER.tar.gz" "purec-engine-$VER" && \
  sha256sum "purec-engine-$VER.tar.gz" > "purec-engine-$VER.tar.gz.sha256" )
echo "release package: $OUT/purec-engine-$VER.tar.gz"
```

`chmod +x engine/tools/package_release.sh`。

- [ ] **Step 4: 验证（green）+ 打签名 tag**

Run:
```bash
ctest --test-dir build-gate -R '^test_release_package_contract$' --output-on-failure && \
bash engine/tools/package_release.sh "$PWD" build-gate /tmp/release-smoke 2.0.0 && \
tar -tzf /tmp/release-smoke/purec-engine-2.0.0.tar.gz | head -20
```
Expected: 契约测试 PASS；包内可见 `bin/`、`config/locked_dependencies.json`、`config/rhi_backend_rollout.json`、`MANIFEST`、`SHA256SUMS`。

打 tag（v1 末版必须先存在——若 Task 6 Step 6 已确认则跳过 v1 部分）：

```bash
# 删除 OpenGL 之前的最后一个 commit 上打 v1 末版（如已有 v1.x 则跳过）
git tag -s v1.9.0 -m "v1.9.0: last release with OpenGL backend" <pre-removal-commit-sha>
# 删除 + 文档收尾完成后打 v2.0.0
git tag -s v2.0.0 -m "v2.0.0: OpenGL backend removed; Vulkan/Metal/D3D12 certified"
git tag -v v2.0.0
```

- [ ] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/tools/package_release.sh \
        engine/tests/test_release_package_contract.cmake docs/rhi_rollback_runbook.md
git commit -m "release: semver policy, signed tags, offline artifact packager"
```

---

### Task 10: 最终验证与 push

**Files:**
- 不创建/修改任何文件。

**Interfaces:**
- Consumes: 全部前序 Task。
- Produces: master + v1.9.0 + v2.0.0 已推送；六类 CI lane 全绿。

- [ ] **Step 1: 本地全量终验**

Run:
```bash
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug && \
cmake --build build-gate --parallel && \
ctest --test-dir build-gate -LE "graphics|fuzz" --output-on-failure && \
ctest --test-dir build-gate -L "release_gate" --output-on-failure && \
bash engine/tools/clean_room_build.sh "$PWD" /tmp/final-clean-room --backend vulkan && \
git diff --check && git status --porcelain
```
Expected: 全绿；`git status --porcelain` 无未提交改动；release_gate 套件（`test_opengl_removal_gate` + `test_release_package_contract`）PASS。

- [ ] **Step 2: 推送**

Run:
```bash
git fetch origin && git rebase origin/master && \
git push origin master && \
git push origin v1.9.0 v2.0.0
```
Expected: 全部成功。若 `git rebase` 引入远程新提交，重跑 Step 1 后再 push。

- [ ] **Step 3: CI 全矩阵确认**

Run:
```bash
gh run list --branch master --limit 1 && \
gh run view --log-failed   # 如有失败
```
Expected: 最新 run 中六类 lane（headless/native-surface/GPU-runtime/validation/benchmark/proton）+ clean-room 全绿（proton 与无 GPU runner 的 GPU-runtime job 允许以 UNAVAILABLE 收据通过）；`evidence-receipt-*` artifact 均已上传。把 run URL 补记进 `docs/rhi_backend_evidence.md` 各行收据列（若 Task 8 留的是占位 run 链接），单独 commit 推送：

```bash
git add docs/rhi_backend_evidence.md
git commit -m "docs: link final CI run receipts in evidence ledger"
git push origin master
```

- [ ] **Step 4: 发布收尾**

- 用 v2.0.0 tag 的 artifact 包（Task 9 Step 4 产物）+ CI 收据创建 GitHub Release（`gh release create v2.0.0 --verify-tag purec-engine-2.0.0.tar.gz*`，release notes 引用 `docs/rhi_opengl_removal_migration.md`）。
- 手动触发一次 rollback-drill（`gh workflow run rollback-drill.yml -f tag=v1.9.0`），确认回滚路径绿。
- 在 `docs/rhi_backend_evidence.md` 的计划 F 前置确认小节追加「计划 F 完成：<日期>，v2.0.0 已发布」。

---

## 自检记录（self-review，撰写完成后执行）

- **规格覆盖**：§6 十一条删除条件 → Task 6 Step 1 的 gate 脚本逐条可执行化（含条件 11 书面确认 = signoff 文档）；§8.1 文档清单 → Task 4/6/8；§8.2 六类 lane → Task 7；§8.3 收据 schema → Task 7 Step 1-2；§2 证据等级 → Global Constraints + Task 8 Step 4（无收据不升级）；§7 风险（MoltenVK/Proton/模拟器/OHOS/依赖漂移）→ Task 6 gate 的 MoltenVK 排除、Task 7 proton lane 隔离、Task 1 锁定。
- **占位符扫描**：计划中出现的 `<...>` 均为「执行时以给定命令的实测输出填入」的值（sha256、apt 版本串、CI run URL、签署日期），每个都附了产生该值的精确命令；无 TBD/TODO 类步骤。
- **类型一致性**：`RHIRolloutEvent` 五字段（event/backend/reason/config_version/result）在 Task 3 定义，Task 5/6/7 引用同一值域；`test_rhi_opengl_compat_fallback_contract` 在 Task 6 Step 4 反转为 `test_opengl_removed_contract`，Task 6 Step 5 的验证命令使用新名；收据字段名与规格 §8.3 逐字一致。
- **已知执行期变量**（非占位符，属环境确认）：Agility SDK 1.616.0 的存在性（Task 1 Step 3 附确认命令与替代规则）；ubuntu-24.04 的 `libvulkan-dev=1.3.275.*` 精确版本串（Task 2 Step 5 附 `apt-cache policy` 确认命令）；steamrt digest（Task 7 proton lane）。
