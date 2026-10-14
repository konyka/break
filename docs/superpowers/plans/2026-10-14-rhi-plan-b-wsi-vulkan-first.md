# 计划 B：WSI 抽离 + Vulkan-first 完善实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 按 `docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md` 的阶段 4（WSI 抽离）与阶段 5（Vulkan-first）：把 Vulkan surface 创建从 `rhi_vk.c` 抽入 PAL 新模块 `platform_vk_surface`，把 `platform_wsi.h` 状态机接入五个真实窗口后端，锁定 logical/drawable 尺寸语义，将 adapter/queue/format/present-mode/feature 探测抽成 headless 可测的纯函数，建立四类故障注入测试，保留 TV_ONLY_* 隔离门，新增 Steam Deck/Linux Steam 真 GPU CI lane 与 benchmark receipt，更新文档，最终 Linux X11+Wayland 双配置全绿并推送 `origin master`。

**Architecture:** PAL 层新增 `engine/src/platform/platform_vk_surface.{h,c}`（不含 Vulkan 头，create-info ABI 由本地最小声明 + ABI 钉死测试保证）与 `engine/src/platform/platform_size.h`（尺寸语义纯函数）；RHI 层新增 `engine/src/rhi/rhi_vk_probe.h`（探测/协商纯函数）与 `engine/src/rhi/rhi_result_map.h`（VkResult→RHIResult 纯映射）；`platform_wsi.h` 状态机经 window_*.c 事件接入真实生命周期；`RHIDevice` 获得非拥有 `PlatformWsiSurface *` 挂载点，`rhi_device_destroy_ex` 受 DESTROYING 门控。

**Tech Stack:** C11（`engine/CMakeLists.txt:4-6`），CMake + Ninja，clang（本机主用）/ MSVC / GCC（CI 矩阵），CTest（`test_framework.h`：`TEST`/`RUN_TEST`/`ASSERT_*`/`TEST_MAIN_BEGIN`，见 `engine/tests/test_framework.h:67-144`），`cmake -P` 契约测试（模式见 `engine/tests/test_rhi_backend_internal_contract.cmake` 与其注册 `engine/CMakeLists.txt:2091-2103`）。

## Global Constraints

- **C11 + -Werror**：新代码在 clang（`-Wall -Wextra -Werror -pedantic`，`engine/CMakeLists.txt:105-108`）与 MSVC（`/W4 /WX`，:96-104）下零告警。函数指针与 `void *` 互转一律走 `memcpy`（-Wpedantic 对两者直接强转报错）；不得给新文件加告警豁免。
- **TDD**：每个 Task 先写失败测试 → 运行验证失败（记录预期失败信息）→ 最小实现 → 验证通过 → 提交。禁止先实现后补测试。
- **冻结文件（任何步骤不得读入修改/删除/移动/提交）**：`.scratch-vkprobe/`、`engine/profile_trace.json`、`.tmp/`、仓库根 `d3d12_shader_gate.hlsl` 与 `d3d12_shader_gate.dxil`、任何 `.env`、SSH 私钥。每个 commit 步骤先 `git status --short` 核对暂存清单不含它们。
- **证据等级纪律**：等级模型为 `platform_compat.h:49-56` 的 `NONE → COMPILED → HEADLESS → NATIVE_SURFACE → GPU_RUNTIME → BENCHMARK_COMPARABLE`。编译成功 ≠ GPU-runtime；模拟器/lavapipe 只证明 compile/lifecycle；每次等级提升必须在证据台账 `docs/rhi_backend_evidence.md`（计划 A 创建）附收据（日期/机器/GPU/驱动/命令/结果）。headless stub 不算 GPU 证据。
- **上下文 70% 压缩交接**：执行上下文约 70% 时先生成压缩交接，至少包含：当前 Task 与 checkbox 状态；已完成/失败/阻塞测试及命令；已修改与未提交文件清单；当前 commit/branch/remote；平台矩阵及各级证据等级；未解决风险；下一步精确命令；冻结文件清单复述。
- **前置条件**：计划 A（`docs/superpowers/plans/2026-10-14-rhi-plan-a-evidence-abstraction-buildsplit.md`）全部完成——WIP 已提交、`rhi.h` 中性化、后端构建拆分、`docs/rhi_backend_evidence.md` / `docs/rhi_benchmark_receipt_schema.md` / `docs/vulkan_support_matrix.md` 骨架已存在。本计划引用但不重建它们。
- **OHOS 维持 fail-closed**：不改 `engine/CMakeLists.txt:1073-1075` 的 FATAL_ERROR 与 `platform_compat.h:111-120`；`PlatformWsiBackend` 枚举（`platform_wsi.h:63-70`）不新增 OHOS。
- **TV_ONLY_PSHADOW / TV_ONLY_GBUFFER 保留**：`engine/src/test_vulkan.c:5600-5642` 的两个环境变量隔离门不得删除、不得被 CMake/CI 引用（Task 6 的契约测试钉死）。
- **行尾**：`engine/src/rhi/*`、`engine/src/main.c`、`engine/src/test_vulkan.c`、`engine/CMakeLists.txt` 为 CRLF；`engine/src/platform/*`、`engine/src/test_vulkan.c` 之外的多数测试与 `.github/workflows/ci.yml` 为 LF。编辑保持各文件原行尾。
- **本计划只新增 public 函数，不改既有签名**：`platform.h`、`rhi.h` 只做尾部追加（append-only）；`RHICapabilities` 无 `struct_size` 字段，追加字段属源码兼容（非 ABI 稳定承诺，写入头注释）。

## 构建 / 测试命令（每个 Task 复用）

```bash
# 一次性配置（仓库根 E:/work/break；Vulkan 配置为主，GL 配置用于回归证明）
cmake -S engine -B build-vk -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=ON
cmake -S engine -B build-gl -G Ninja -DCMAKE_BUILD_TYPE=Debug
# 全量构建 + headless 套件（排除 graphics/fuzz）
cmake --build build-vk --parallel
ctest --test-dir build-vk -LE "graphics|fuzz" --output-on-failure
# 图形套件（本机真 GPU = GPU_RUNTIME 级回归证据）
ctest --test-dir build-vk -L graphics --output-on-failure
# 单测试
cmake --build build-vk --target <target> --parallel
ctest --test-dir build-vk -R <name> --output-on-failure
```

cmake 契约测试注册模板（锚点 `engine/CMakeLists.txt:2091-2103`）：

```cmake
add_test(NAME test_platform_vk_surface_contract
    COMMAND ${CMAKE_COMMAND}
        -DRHI_VK_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_vk.c
        -DVK_SURFACE_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_vk_surface.c
        -DVK_SURFACE_HEADER=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_vk_surface.h
        -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_platform_vk_surface_contract.cmake)
```

C 测试注册模板（镜像 `engine/CMakeLists.txt:1582-1586` 的 headless WSI 测试）：

```cmake
add_executable(test_rhi_vk_probe tests/test_rhi_vk_probe.c)
target_include_directories(test_rhi_vk_probe PRIVATE ${TEST_INCLUDE_DIRS})
add_test(NAME test_rhi_vk_probe COMMAND test_rhi_vk_probe)
set_tests_properties(test_rhi_vk_probe PROPERTIES LABELS "headless;platform_contract")
```

需要链接 RHI 核心的测试镜像 `test_rhi_capabilities` 的完整注册块（`engine/CMakeLists.txt:1824-1880`，含 `${RHI_CORE_SOURCES} src/core/log.c` 源内编译、`ENGINE_RHI_TEST=1`、按平台的 include/link 矩阵与 `--gc-sections`），仅替换目标名与源文件名。

---

## Task 1: platform_vk_surface 抽离（TDD）

**Files:**
- Create: `engine/src/platform/platform_vk_surface.h`（公开 API）
- Create: `engine/src/platform/platform_vk_surface_vkabi.h`（create-info 最小 ABI 声明，私有）
- Create: `engine/src/platform/platform_vk_surface.c`（五平台分支实现）
- Modify: `engine/src/rhi/rhi_vk.c`（vk_init :1500-1524 扩展列表、:1592-1595 portability flag、:1656-1711 surface 创建迁移；VKBackend 原生句柄字段 :385-398 精简；:1-23 平台 include 块删除）
- Modify: `engine/CMakeLists.txt`（engine 源清单 + 两个测试注册）
- Test: `engine/tests/test_platform_vk_surface_contract.cmake`（cmake -P 契约）
- Test: `engine/tests/test_platform_vk_surface_abi.c`（宿主平台 ABI 钉死，仅在有 Vulkan 头时注册）

**Interfaces:**
- Consumes: `platform_surface_native`（`platform.h:112`）、`platform_display_native`（`platform.h:110`）、`core/types.h` 的 `u32/u64/i32`。
- Produces（`platform_vk_surface.h`，完整内容）：

```c
#pragma once
#include <core/types.h>
#include <platform/platform.h>

/* platform 层不包含 <vulkan/vulkan.h>（分层规则：PAL 只依赖 OS API）。
 * VkInstance 以 void * 传入；VkSurfaceKHR（不可分派句柄，64 位）以 u64 传出；
 * vkGetInstanceProcAddr 以 void * 传入（调用方用 memcpy 桥接函数指针，
 * 见 rhi_vk.c 接线处的 gpa 桥接——避免 -Wpedantic 的函数指针/void* 强转）。 */

typedef enum PlatformVkSurfaceError {
    PLATFORM_VK_SURFACE_OK = 0,
    PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT = 1, /* 参数为 NULL */
    PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE = 2,      /* 平台无 WSI（OHOS 等）或原生句柄为空 */
    PLATFORM_VK_SURFACE_ERROR_PROC_MISSING = 3,     /* get_proc_addr 解析不到入口 */
    PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED = 4,    /* vkCreate*SurfaceKHR 返回非 0 */
} PlatformVkSurfaceError;

/* 必需的 Vulkan instance 扩展（编译期平台常量）。两段式惯用法：
 * out == NULL 或 capacity < 所需个数时不写入、返回所需个数。 */
u32 platform_vk_required_instance_extensions(Platform *p, const char **out,
                                             u32 capacity);

/* VkInstanceCreateInfo.flags 中本平台需要的位（目前仅 macOS/iOS MoltenVK 需要
 * VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR = 0x1；其余平台为 0）。 */
u32 platform_vk_instance_create_flags(Platform *p);

/* 经 Platform 句柄创建 surface（platform_surface_native /
 * platform_display_native 解包后转发给 *_handles）。 */
u64 platform_vk_create_surface(Platform *p, void *vk_instance,
                               void *vk_get_proc_addr, u64 *out_surface);

/* 经原生句柄创建 surface。rhi_vk.c 的 vk_init 持有的是裸句柄而非 Platform
 * （rhi_device_create 的公开 ABI 不变），故消费本入口；调用方拥有结果
 * surface 的销毁权（vkDestroySurfaceKHR 仍在 rhi_vk.c）。Android：成功时本
 * 函数对 ANativeWindow 持有一个引用（acquire），由调用方 shutdown 路径释放
 * （原 rhi_vk.c:2486 的 ANativeWindow_release 不动）；失败路径本函数自行
 * release 回滚。 */
u64 platform_vk_create_surface_handles(void *surface_native,
                                       void *display_native,
                                       void *vk_instance,
                                       void *vk_get_proc_addr,
                                       u64 *out_surface);
```

- Produces（`platform_vk_surface_vkabi.h`，完整内容）：

```c
#pragma once
#include <core/types.h>

/* 五个 WSI surface create-info 的最小 ABI 声明。sType 数值与字段布局由
 * engine/tests/test_platform_vk_surface_abi.c 对照真实 <vulkan/vulkan.h>
 * 逐字段钉死；任何漂移在编译期/测试期失败，而不是在 GPU 上出错。 */
#define PVK_STYPE_XLIB_SURFACE_CREATE_INFO_KHR    1000004000u
#define PVK_STYPE_WAYLAND_SURFACE_CREATE_INFO_KHR 1000006000u
#define PVK_STYPE_ANDROID_SURFACE_CREATE_INFO_KHR 1000008000u
#define PVK_STYPE_WIN32_SURFACE_CREATE_INFO_KHR   1000009000u
#define PVK_STYPE_METAL_SURFACE_CREATE_INFO_EXT   1000217000u
#define PVK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR 0x00000001u

typedef struct PVkWin32SurfaceCreateInfo {
    u32 sType; const void *pNext; u32 flags; void *hinstance; void *hwnd;
} PVkWin32SurfaceCreateInfo;
typedef struct PVkXlibSurfaceCreateInfo {
    /* Window 在 LP64 上是 unsigned long：按 u64 承载（ABI 测试在 Linux 钉死）。 */
    u32 sType; const void *pNext; u32 flags; void *dpy; u64 window;
} PVkXlibSurfaceCreateInfo;
typedef struct PVkWaylandSurfaceCreateInfo {
    u32 sType; const void *pNext; u32 flags; void *display; void *surface;
} PVkWaylandSurfaceCreateInfo;
typedef struct PVkAndroidSurfaceCreateInfo {
    u32 sType; const void *pNext; u32 flags; void *window;
} PVkAndroidSurfaceCreateInfo;
typedef struct PVkMetalSurfaceCreateInfo {
    u32 sType; const void *pNext; u32 flags; const void *pLayer;
} PVkMetalSurfaceCreateInfo;

/* 五个 vkCreate*SurfaceKHR 共享同一签名形状：(instance, create_info,
 * allocator, out_surface)，VkResult 为 i32。 */
typedef i32 (*PVkCreateSurfaceFn)(void *instance, const void *create_info,
                                  const void *allocator, u64 *out_surface);
typedef void *(*PVkGetProcAddrFn)(void *instance, const char *name);
```

- [ ] **Step 1: 写失败契约测试** — 创建 `engine/tests/test_platform_vk_surface_contract.cmake`，完整内容：

```cmake
foreach(required_var RHI_VK_SOURCE VK_SURFACE_SOURCE VK_SURFACE_HEADER ENGINE_CMAKE)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

file(READ "${RHI_VK_SOURCE}" vk_text)
file(READ "${ENGINE_CMAKE}" engine_cmake_text)

# rhi_vk.c 不得再直接创建 WSI surface（token 级证据：创建调用已迁入 PAL）。
foreach(forbidden_token
        "vkCreateWin32SurfaceKHR" "vkCreateXlibSurfaceKHR"
        "vkCreateWaylandSurfaceKHR" "vkCreateAndroidSurfaceKHR"
        "VkMetalSurfaceCreateInfoEXT" "VkWin32SurfaceCreateInfoKHR"
        "VkXlibSurfaceCreateInfoKHR" "VkWaylandSurfaceCreateInfoKHR"
        "VkAndroidSurfaceCreateInfoKHR")
    string(FIND "${vk_text}" "${forbidden_token}" forbidden_offset)
    if(NOT forbidden_offset EQUAL -1)
        message(FATAL_ERROR
            "rhi_vk.c still creates WSI surfaces directly: ${forbidden_token}")
    endif()
endforeach()
# rhi_vk.c 必须改经 PAL 入口。
string(FIND "${vk_text}" "platform_vk_create_surface_handles(" pal_call_offset)
if(pal_call_offset EQUAL -1)
    message(FATAL_ERROR "rhi_vk.c must create the surface via platform_vk_create_surface_handles")
endif()
string(FIND "${vk_text}" "platform_vk_required_instance_extensions(" pal_ext_offset)
if(pal_ext_offset EQUAL -1)
    message(FATAL_ERROR "rhi_vk.c must source instance extensions via platform_vk_required_instance_extensions")
endif()

# PAL 模块存在且五个平台分支齐备。
if(NOT EXISTS "${VK_SURFACE_HEADER}")
    message(FATAL_ERROR "missing: ${VK_SURFACE_HEADER}")
endif()
if(NOT EXISTS "${VK_SURFACE_SOURCE}")
    message(FATAL_ERROR "missing: ${VK_SURFACE_SOURCE}")
endif()
file(READ "${VK_SURFACE_SOURCE}" surface_text)
foreach(required_token
        "ENGINE_PLATFORM_WINDOWS" "ENGINE_PLATFORM_WAYLAND"
        "ENGINE_PLATFORM_ANDROID" "ENGINE_PLATFORM_LINUX"
        "vkCreateWin32SurfaceKHR" "vkCreateXlibSurfaceKHR"
        "vkCreateWaylandSurfaceKHR" "vkCreateAndroidSurfaceKHR"
        "vkCreateMetalSurfaceEXT")
    string(FIND "${surface_text}" "${required_token}" surface_offset)
    if(surface_offset EQUAL -1)
        message(FATAL_ERROR
            "platform_vk_surface.c missing platform branch token: ${required_token}")
    endif()
endforeach()
foreach(dual_token "ENGINE_PLATFORM_MACOS" "ENGINE_PLATFORM_IOS")
    string(FIND "${surface_text}" "${dual_token}" dual_offset)
    if(dual_offset EQUAL -1)
        message(FATAL_ERROR
            "platform_vk_surface.c missing platform branch token: ${dual_token}")
    endif()
endforeach()
# PAL 源必须编入 engine target。
string(FIND "${engine_cmake_text}" "src/platform/platform_vk_surface.c" cmake_offset)
if(cmake_offset EQUAL -1)
    message(FATAL_ERROR "engine target does not compile src/platform/platform_vk_surface.c")
endif()
```

在 `engine/CMakeLists.txt` 的 :2103 之后按上方模板注册 `test_platform_vk_surface_contract`。

- [ ] **Step 2: 验证失败** — `ctest --test-dir build-vk -R test_platform_vk_surface_contract --output-on-failure` → 预期 FAIL。契约脚本的断言顺序是先查 rhi_vk.c 的禁用 token，故预期信息为 `rhi_vk.c still creates WSI surfaces directly: vkCreateWin32SurfaceKHR`（rhi_vk.c 尚未迁移时命中第一个禁用 token；记录实际输出）。

- [ ] **Step 3: 最小实现（新 PAL 模块）** — 创建 `engine/src/platform/platform_vk_surface.h` 与 `platform_vk_surface_vkabi.h`（内容见 Interfaces），创建 `engine/src/platform/platform_vk_surface.c`（完整骨架，五平台分支）：

```c
#include <platform/platform_vk_surface.h>
#include "platform_vk_surface_vkabi.h"
#include <string.h>

#if defined(ENGINE_PLATFORM_ANDROID) && defined(ENGINE_ANDROID_NATIVE_WINDOW)
#include <android/native_window.h>
#endif

u32 platform_vk_required_instance_extensions(Platform *p, const char **out,
                                             u32 capacity) {
    static const char *const extensions[] = {
        "VK_KHR_surface",
#if defined(ENGINE_PLATFORM_WINDOWS)
        "VK_KHR_win32_surface",
#elif defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
        "VK_EXT_metal_surface",
        "VK_KHR_portability_enumeration",
        "VK_KHR_get_physical_device_properties2",
#elif defined(ENGINE_PLATFORM_WAYLAND)
        "VK_KHR_wayland_surface",
#elif defined(ENGINE_PLATFORM_ANDROID)
        "VK_KHR_android_surface",
#elif defined(ENGINE_PLATFORM_LINUX)
        "VK_KHR_xlib_surface",
#endif
    };
    const u32 count = (u32)(sizeof(extensions) / sizeof(extensions[0]));
    u32 i;
    (void)p; /* 平台是编译期常量；参数保留给将来按窗口定制的扩展。 */
    if (out == NULL || capacity < count) return count;
    for (i = 0; i < count; i++) out[i] = extensions[i];
    return count;
}

u32 platform_vk_instance_create_flags(Platform *p) {
    (void)p;
#if defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
    /* MoltenVK 是 portability 驱动，必须显式 opt in 枚举。 */
    return PVK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#else
    return 0u;
#endif
}

/* get_proc 返回 void *；函数指针与 void * 的互转全部经 memcpy，
 * 否则 -Wpedantic 报错（ISO C 不允许这两类指针直接强转）。 */
static PVkCreateSurfaceFn pvk_resolve(void *vk_instance, void *vk_get_proc_addr,
                                      const char *entry_name) {
    PVkGetProcAddrFn get_proc;
    PVkCreateSurfaceFn create = NULL;
    void *entry;
    memcpy(&get_proc, &vk_get_proc_addr, sizeof(get_proc));
    entry = get_proc(vk_instance, entry_name);
    if (entry != NULL) memcpy(&create, &entry, sizeof(create));
    return create;
}

u64 platform_vk_create_surface(Platform *p, void *vk_instance,
                               void *vk_get_proc_addr, u64 *out_surface) {
    if (p == NULL) return PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT;
    return platform_vk_create_surface_handles(platform_surface_native(p),
                                              platform_display_native(p),
                                              vk_instance, vk_get_proc_addr,
                                              out_surface);
}

u64 platform_vk_create_surface_handles(void *surface_native,
                                       void *display_native,
                                       void *vk_instance,
                                       void *vk_get_proc_addr,
                                       u64 *out_surface) {
    PVkCreateSurfaceFn create;
    if (vk_instance == NULL || vk_get_proc_addr == NULL || out_surface == NULL)
        return PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT;
    *out_surface = 0u;
#if defined(ENGINE_PLATFORM_WINDOWS)
    {
        PVkWin32SurfaceCreateInfo ci;
        if (surface_native == NULL || display_native == NULL)
            return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.hinstance = display_native;  /* HINSTANCE（window_win32.c:685-687）*/
        ci.hwnd = surface_native;       /* HWND（window_win32.c:689-691）*/
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateWin32SurfaceKHR");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        if (create(vk_instance, &ci, NULL, out_surface) != 0)
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        return PLATFORM_VK_SURFACE_OK;
    }
#elif defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
    {
        PVkMetalSurfaceCreateInfo ci;
        (void)display_native;
        if (surface_native == NULL) return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_METAL_SURFACE_CREATE_INFO_EXT;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.pLayer = surface_native; /* CAMetalLayer *（window_cocoa.m:494）*/
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateMetalSurfaceEXT");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        if (create(vk_instance, &ci, NULL, out_surface) != 0)
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        return PLATFORM_VK_SURFACE_OK;
    }
#elif defined(ENGINE_PLATFORM_WAYLAND)
    {
        PVkWaylandSurfaceCreateInfo ci;
        if (surface_native == NULL || display_native == NULL)
            return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.display = display_native; /* struct wl_display *（window_wayland.c:2015-2017）*/
        ci.surface = surface_native; /* struct wl_surface *（window_wayland.c:2019-2021）*/
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateWaylandSurfaceKHR");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        if (create(vk_instance, &ci, NULL, out_surface) != 0)
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        return PLATFORM_VK_SURFACE_OK;
    }
#elif defined(ENGINE_PLATFORM_ANDROID)
#if defined(ENGINE_ANDROID_NATIVE_WINDOW)
    {
        PVkAndroidSurfaceCreateInfo ci;
        if (surface_native == NULL) return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.window = surface_native; /* struct ANativeWindow *（window_mobile.c:60）*/
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateAndroidSurfaceKHR");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        /* 引用配对：acquire 从原 rhi_vk.c:1484 迁到这里；成功路径的 release 仍在
         * vk_shutdown（原 rhi_vk.c:2486）；失败路径本地回滚，不泄漏引用。 */
        ANativeWindow_acquire((struct ANativeWindow *)surface_native);
        if (create(vk_instance, &ci, NULL, out_surface) != 0) {
            ANativeWindow_release((struct ANativeWindow *)surface_native);
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        }
        return PLATFORM_VK_SURFACE_OK;
    }
#else
    (void)surface_native; (void)display_native; (void)create;
    return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
#endif
#elif defined(ENGINE_PLATFORM_LINUX)
    {
        PVkXlibSurfaceCreateInfo ci;
        if (surface_native == NULL || display_native == NULL)
            return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.dpy = display_native; /* Display *（window_x11.c:1170-1172）*/
        /* Window = unsigned long：window_x11.c:1174-1176 以 (void*)(uintptr_t)
         * 传出，这里按原路转回。 */
        ci.window = (u64)(uintptr_t)surface_native;
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateXlibSurfaceKHR");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        if (create(vk_instance, &ci, NULL, out_surface) != 0)
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        return PLATFORM_VK_SURFACE_OK;
    }
#else
    /* OHOS 及未知平台：fail-closed，不伪造 surface（规格 §4.5）。 */
    (void)surface_native; (void)display_native; (void)create;
    return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
#endif
}
```

在 `engine/CMakeLists.txt` 的 engine 源清单（:244-327）中 `src/platform/platform_display_media.c`（:253）之后加一行 `src/platform/platform_vk_surface.c`。构建：`cmake --build build-vk --target engine --parallel` → 编译通过（此时 rhi_vk.c 尚未迁移，契约测试仍红）。

- [ ] **Step 4: 写 ABI 钉死测试** — 创建 `engine/tests/test_platform_vk_surface_abi.c`：

```c
#include "test_framework.h"
#include "../src/platform/platform_vk_surface_vkabi.h"

#if defined(ENGINE_PLATFORM_WINDOWS)
#define VK_USE_PLATFORM_WIN32_KHR
#include <windows.h>
#elif defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
#define VK_USE_PLATFORM_METAL_EXT
#elif defined(ENGINE_PLATFORM_WAYLAND)
#define VK_USE_PLATFORM_WAYLAND_KHR
#include <wayland-client.h>
#elif defined(ENGINE_PLATFORM_ANDROID) && defined(ENGINE_ANDROID_NATIVE_WINDOW)
#define VK_USE_PLATFORM_ANDROID_KHR
#include <android/native_window.h>
#elif defined(ENGINE_PLATFORM_LINUX)
#define VK_USE_PLATFORM_XLIB_KHR
#include <X11/Xlib.h>
#endif
#include <vulkan/vulkan.h>

/* 只钉死宿主平台分支：其余分支的等价断言由各平台 CI lane 上的同名测试承担。 */
#if defined(ENGINE_PLATFORM_WINDOWS)
TEST(win32_surface_create_info_abi) {
    ASSERT_EQ(sizeof(PVkWin32SurfaceCreateInfo), sizeof(VkWin32SurfaceCreateInfoKHR));
    ASSERT_EQ(PVK_STYPE_WIN32_SURFACE_CREATE_INFO_KHR,
              (u32)VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR);
}
#elif defined(ENGINE_PLATFORM_LINUX) && !defined(ENGINE_PLATFORM_WAYLAND)
TEST(xlib_surface_create_info_abi) {
    ASSERT_EQ(sizeof(PVkXlibSurfaceCreateInfo), sizeof(VkXlibSurfaceCreateInfoKHR));
    ASSERT_EQ(PVK_STYPE_XLIB_SURFACE_CREATE_INFO_KHR,
              (u32)VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR);
    ASSERT_EQ(sizeof(Window), sizeof(u64)); /* LP64 契约 */
}
#elif defined(ENGINE_PLATFORM_WAYLAND)
TEST(wayland_surface_create_info_abi) {
    ASSERT_EQ(sizeof(PVkWaylandSurfaceCreateInfo), sizeof(VkWaylandSurfaceCreateInfoKHR));
    ASSERT_EQ(PVK_STYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
              (u32)VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR);
}
#elif defined(ENGINE_PLATFORM_MACOS)
TEST(metal_surface_create_info_abi) {
    ASSERT_EQ(sizeof(PVkMetalSurfaceCreateInfo), sizeof(VkMetalSurfaceCreateInfoEXT));
    ASSERT_EQ(PVK_STYPE_METAL_SURFACE_CREATE_INFO_EXT,
              (u32)VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT);
    ASSERT_EQ(PVK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
              (u32)VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR);
}
#endif

TEST(dummy_when_no_host_branch) { ASSERT_TRUE(1); }

TEST_MAIN_BEGIN()
#if defined(ENGINE_PLATFORM_WINDOWS)
    RUN_TEST(win32_surface_create_info_abi);
#elif defined(ENGINE_PLATFORM_LINUX) && !defined(ENGINE_PLATFORM_WAYLAND)
    RUN_TEST(xlib_surface_create_info_abi);
#elif defined(ENGINE_PLATFORM_WAYLAND)
    RUN_TEST(wayland_surface_create_info_abi);
#elif defined(ENGINE_PLATFORM_MACOS)
    RUN_TEST(metal_surface_create_info_abi);
#endif
    RUN_TEST(dummy_when_no_host_branch);
TEST_MAIN_END()
```

注册（`if(TARGET Vulkan::Vulkan)` 内——Vulkan 头在 `ENGINE_VULKAN` 或 macOS 分支已 `find_package`，:234/:730/:983/:1014/:1030）：

```cmake
if(TARGET Vulkan::Vulkan)
    add_executable(test_platform_vk_surface_abi
        tests/test_platform_vk_surface_abi.c)
    target_include_directories(test_platform_vk_surface_abi PRIVATE
        ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_platform_vk_surface_abi PRIVATE Vulkan::Vulkan)
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_platform_vk_surface_abi PRIVATE
            ENGINE_PLATFORM_LINUX=1)
        target_include_directories(test_platform_vk_surface_abi PRIVATE
            ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS})
        if(ENGINE_ENABLE_WAYLAND)
            target_compile_definitions(test_platform_vk_surface_abi PRIVATE
                ENGINE_PLATFORM_WAYLAND=1)
            target_link_libraries(test_platform_vk_surface_abi PRIVATE
                ${WAYLAND_LIBRARIES})
        endif()
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_platform_vk_surface_abi PRIVATE
            ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_platform_vk_surface_abi PRIVATE
            ENGINE_PLATFORM_MACOS=1)
    endif()
    add_test(NAME test_platform_vk_surface_abi
        COMMAND test_platform_vk_surface_abi)
    set_tests_properties(test_platform_vk_surface_abi PROPERTIES
        LABELS "headless;platform_contract")
endif()
```

运行（red → green 自证）：先 `cmake -S engine -B build-vk ...` 重新配置后 `cmake --build build-vk --target test_platform_vk_surface_abi --parallel && ctest --test-dir build-vk -R test_platform_vk_surface_abi --output-on-failure` → PASS。

- [ ] **Step 5: 迁移 rhi_vk.c** — ① 删除 :1-23 的平台 include 块（`VK_USE_PLATFORM_*`、`windows.h`、`wayland-client.h`、`android/native_window.h`、`X11/Xlib.h`），新增 `#include <platform/platform_vk_surface.h>`；② `VKBackend` 的平台句柄字段（:385-398）只保留 Android 的 `struct ANativeWindow *native_window;`（release 配对在 vk_shutdown :2486），其余删除，vk_init 的句柄赋值块（:1473-1488）整体删除（Android 的 acquire :1484 已迁入 PAL）；③ 扩展列表（:1504-1517）替换为：

```c
    const char *extensions[8];
    u32 ext_count = platform_vk_required_instance_extensions(
        NULL, extensions, (u32)(sizeof(extensions) / sizeof(extensions[0])));
```

④ portability flag（:1592-1595）替换为：

```c
    ici.flags |= platform_vk_instance_create_flags(NULL);
```

⑤ surface 创建（:1656-1711 整段 #ifdef 链）替换为：

```c
    {
        /* vkGetInstanceProcAddr 是函数指针，API 参数是 void * —— 用 memcpy
         * 桥接（-Wpedantic 不允许直接强转）。 */
        PFN_vkGetInstanceProcAddr gpa_fn = vkGetInstanceProcAddr;
        void *gpa;
        u64 surface_bits = 0u;
        u64 surface_result;
        memcpy(&gpa, &gpa_fn, sizeof(gpa));
        surface_result = platform_vk_create_surface_handles(
            window_native, display_native, (void *)vk->instance, gpa,
            &surface_bits);
        if (surface_result != PLATFORM_VK_SURFACE_OK) {
            LOG_ERROR("Failed to create Vulkan surface via PAL (error %llu)",
                      (unsigned long long)surface_result);
            vk_init_cleanup(dev, vk);
            return false;
        }
        vk->surface = (VkSurfaceKHR)surface_bits;
    }
```

⑥ vk_init 的 `VkAndroidSurfaceCreateInfoKHR sci` 等局部名与后续代码无冲突（原各分支的 `sci` 随块删除；`vk_create_swapchain` 内的 `VkSwapchainCreateInfoKHR sci` :1108 不受影响）。

- [ ] **Step 6: 验证通过** — `cmake --build build-vk --parallel` 全量构建通过；`ctest --test-dir build-vk -R "test_platform_vk_surface" --output-on-failure` → 两个测试 PASS；`ctest --test-dir build-vk -LE "graphics|fuzz" --output-on-failure` 全绿；`ctest --test-dir build-vk -L graphics --output-on-failure` 全绿（本机真 GPU，GPU_RUNTIME 级回归证据：surface 创建迁移后 test_vulkan 行为不变）。GL 回归：`cmake --build build-gl --parallel && ctest --test-dir build-gl -LE "graphics|fuzz" --output-on-failure` 全绿。

- [ ] **Step 7: Commit**

```bash
git status --short   # 核对：无冻结文件（.scratch-vkprobe/、engine/profile_trace.json、.tmp/、d3d12_shader_gate.*）
git add engine/src/platform/platform_vk_surface.h \
        engine/src/platform/platform_vk_surface_vkabi.h \
        engine/src/platform/platform_vk_surface.c \
        engine/src/rhi/rhi_vk.c \
        engine/tests/test_platform_vk_surface_contract.cmake \
        engine/tests/test_platform_vk_surface_abi.c \
        engine/CMakeLists.txt \
        docs/superpowers/plans/2026-10-14-rhi-plan-b-wsi-vulkan-first.md
git commit -m "Extract Vulkan WSI surface creation into platform_vk_surface PAL module"
```

---

## Task 2: 逻辑尺寸 vs drawable 尺寸语义锁定（纯函数抽取 + 契约钉死）

**Files:**
- Create: `engine/src/platform/platform_size.h`（四平台尺寸语义纯函数，header-only static inline）
- Test: `engine/tests/test_platform_size_semantics.c`（headless 单元测试）
- Test: `engine/tests/test_platform_size_contract.cmake`（cmake -P 契约：窗口后端必须消费 helper）
- Modify: `engine/src/platform/window_win32.c`（`platform_get_logical_size` :698-709）
- Modify: `engine/src/platform/window_x11.c`（`platform_get_logical_size` :1183-1187）
- Modify: `engine/src/platform/window_wayland.c`（`platform_get_drawable_size` :2033-2037）
- Modify: `engine/src/platform/window_cocoa.m`（`cocoa_update_drawable_size` :339-351）
- Modify: `engine/CMakeLists.txt`（两个测试注册）

**Interfaces:**
- Consumes: `wl_out_drawable_dimension`（`engine/src/platform/wayland_output.h:183`，纯逻辑头、无 Wayland 依赖——其头部注释 :1-6 明确「no Wayland includes, unit-testable headless」）。
- Produces（`platform_size.h`，完整内容）：

```c
#pragma once
#include <core/types.h>
#include <platform/wayland_output.h> /* wl_out_drawable_dimension 的唯一实现源 */

#if defined(__GNUC__) || defined(__clang__)
#define PLATFORM_SIZE_INLINE static inline __attribute__((unused))
#else
#define PLATFORM_SIZE_INLINE static inline
#endif

/* 尺寸语义契约（本文件是这些规则的唯一实现源，window_*.c 只准调用）：
 *  - Win32 / X11：事件坐标（WM_SIZE / ConfigureNotify）即 drawable 物理像素，
 *    drawable == event，即使 scale != 1；logical 由 drawable 反推。
 *  - Wayland / Cocoa：事件坐标是 logical（xdg_toplevel configure 的 w/h、
 *    NSView bounds 的 points），drawable = logical * scale（物理像素）。
 * 两个方向的「谁是输入」不得互换。 */

/* Win32：PMv2 下 WM_SIZE 的 LOWORD/HIWORD 就是物理像素
 *（window_win32.c:302-305 写入 p->width/height；get_drawable :711-714 原样返回）。 */
PLATFORM_SIZE_INLINE void platform_size_win32(u32 event_w, u32 event_h,
                                              f32 content_scale,
                                              u32 *out_logical_w,
                                              u32 *out_logical_h,
                                              u32 *out_drawable_w,
                                              u32 *out_drawable_h) {
    f32 scale = content_scale > 0.0f ? content_scale : 1.0f;
    if (out_drawable_w != NULL) *out_drawable_w = event_w;
    if (out_drawable_h != NULL) *out_drawable_h = event_h;
    if (out_logical_w != NULL) *out_logical_w = (u32)((f32)event_w / scale + 0.5f);
    if (out_logical_h != NULL) *out_logical_h = (u32)((f32)event_h / scale + 0.5f);
}

/* X11：ConfigureNotify 的 width/height 即 drawable（window_x11.c:1094-1098）；
 * logical = ceil(drawable / scale_factor)（既有公式 :1183-1187，逐位保留）。 */
PLATFORM_SIZE_INLINE void platform_size_x11(u32 event_w, u32 event_h,
                                            u32 scale_factor,
                                            u32 *out_logical_w,
                                            u32 *out_logical_h,
                                            u32 *out_drawable_w,
                                            u32 *out_drawable_h) {
    u32 scale = scale_factor > 0u ? scale_factor : 1u;
    if (out_drawable_w != NULL) *out_drawable_w = event_w;
    if (out_drawable_h != NULL) *out_drawable_h = event_h;
    if (out_logical_w != NULL) *out_logical_w = (event_w + scale - 1u) / scale;
    if (out_logical_h != NULL) *out_logical_h = (event_h + scale - 1u) / scale;
}

/* Wayland：xdg_toplevel configure 的 w/h 是 logical（:842-852）；
 * drawable 经 wl_out_drawable_dimension 换算（既有调用 :2033-2037）。 */
PLATFORM_SIZE_INLINE void platform_size_wayland(u32 logical_w, u32 logical_h,
                                                u32 content_scale_120,
                                                u32 *out_logical_w,
                                                u32 *out_logical_h,
                                                u32 *out_drawable_w,
                                                u32 *out_drawable_h) {
    if (out_logical_w != NULL) *out_logical_w = logical_w;
    if (out_logical_h != NULL) *out_logical_h = logical_h;
    if (out_drawable_w != NULL)
        *out_drawable_w = wl_out_drawable_dimension(logical_w, content_scale_120);
    if (out_drawable_h != NULL)
        *out_drawable_h = wl_out_drawable_dimension(logical_h, content_scale_120);
}

/* Cocoa：view bounds 是 logical points（cocoa_update_drawable_size :339-351）；
 * drawable = round(points * backing_scale)。 */
PLATFORM_SIZE_INLINE void platform_size_cocoa(u32 point_w, u32 point_h,
                                              f32 backing_scale,
                                              u32 *out_logical_w,
                                              u32 *out_logical_h,
                                              u32 *out_drawable_w,
                                              u32 *out_drawable_h) {
    f32 scale = backing_scale > 0.0f ? backing_scale : 1.0f;
    if (out_logical_w != NULL) *out_logical_w = point_w;
    if (out_logical_h != NULL) *out_logical_h = point_h;
    if (out_drawable_w != NULL)
        *out_drawable_w = (u32)((f32)point_w * scale + 0.5f);
    if (out_drawable_h != NULL)
        *out_drawable_h = (u32)((f32)point_h * scale + 0.5f);
}

#undef PLATFORM_SIZE_INLINE
```

- [ ] **Step 1: 写失败测试（单元 + 契约）** — 创建 `engine/tests/test_platform_size_semantics.c`：

```c
#include "test_framework.h"
#include "platform/platform_size.h"

TEST(win32_drawable_equals_event_coords_even_when_scaled) {
    u32 lw, lh, dw, dh;
    platform_size_win32(2000u, 1000u, 1.0f, &lw, &lh, &dw, &dh);
    ASSERT_EQ(dw, 2000u);
    ASSERT_EQ(dh, 1000u);
    ASSERT_EQ(lw, 2000u);
    platform_size_win32(2000u, 1000u, 2.0f, &lw, &lh, &dw, &dh);
    ASSERT_EQ(dw, 2000u); /* 锁定：drawable == 事件坐标 */
    ASSERT_EQ(lw, 1000u);
    ASSERT_EQ(lh, 500u);
}

TEST(x11_drawable_equals_event_coords_logical_is_ceil_division) {
    u32 lw, lh, dw, dh;
    platform_size_x11(2001u, 999u, 2u, &lw, &lh, &dw, &dh);
    ASSERT_EQ(dw, 2001u); /* 锁定：drawable == 事件坐标 */
    ASSERT_EQ(lw, 1001u); /* ceil(2001/2) */
    ASSERT_EQ(lh, 500u);
}

TEST(wayland_drawable_derives_from_logical_via_content_scale) {
    u32 lw, lh, dw, dh;
    platform_size_wayland(800u, 600u, 120u, &lw, &lh, &dw, &dh);
    ASSERT_EQ(lw, 800u);
    ASSERT_EQ(dw, 800u); /* scale 1.0 时两者相等 */
    platform_size_wayland(800u, 600u, 240u, &lw, &lh, &dw, &dh);
    ASSERT_EQ(lw, 800u);
    ASSERT_EQ(dw, 1600u); /* 锁定：drawable != logical（scale 2.0） */
    ASSERT_EQ(dh, 1200u);
}

TEST(cocoa_drawable_derives_from_points_via_backing_scale) {
    u32 lw, lh, dw, dh;
    platform_size_cocoa(800u, 600u, 1.0f, &lw, &lh, &dw, &dh);
    ASSERT_EQ(dw, 800u);
    platform_size_cocoa(800u, 600u, 2.0f, &lw, &lh, &dw, &dh);
    ASSERT_EQ(lw, 800u);  /* logical == points */
    ASSERT_EQ(dw, 1600u); /* 锁定：drawable != logical（Retina） */
}

TEST_MAIN_BEGIN()
    RUN_TEST(win32_drawable_equals_event_coords_even_when_scaled);
    RUN_TEST(x11_drawable_equals_event_coords_logical_is_ceil_division);
    RUN_TEST(wayland_drawable_derives_from_logical_via_content_scale);
    RUN_TEST(cocoa_drawable_derives_from_points_via_backing_scale);
TEST_MAIN_END()
```

创建 `engine/tests/test_platform_size_contract.cmake`：

```cmake
foreach(required_var SIZE_HEADER WIN32_SOURCE X11_SOURCE WAYLAND_SOURCE COCOA_SOURCE)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()
if(NOT EXISTS "${SIZE_HEADER}")
    message(FATAL_ERROR "missing: ${SIZE_HEADER}")
endif()
file(READ "${SIZE_HEADER}" size_text)
foreach(required_fn
        "platform_size_win32" "platform_size_x11"
        "platform_size_wayland" "platform_size_cocoa")
    string(FIND "${size_text}" "${required_fn}" fn_offset)
    if(fn_offset EQUAL -1)
        message(FATAL_ERROR "platform_size.h missing: ${required_fn}")
    endif()
endforeach()
foreach(consumer_spec
        "${WIN32_SOURCE}|platform_size_win32"
        "${X11_SOURCE}|platform_size_x11"
        "${WAYLAND_SOURCE}|platform_size_wayland"
        "${COCOA_SOURCE}|platform_size_cocoa")
    string(REPLACE "|" ";" consumer_parts "${consumer_spec}")
    list(GET consumer_parts 0 consumer_path)
    list(GET consumer_parts 1 consumer_token)
    file(READ "${consumer_path}" consumer_text)
    string(FIND "${consumer_text}" "${consumer_token}" consumer_offset)
    if(consumer_offset EQUAL -1)
        message(FATAL_ERROR
            "window backend must consume the shared size helper: ${consumer_path} <- ${consumer_token}")
    endif()
endforeach()
```

注册两个测试（模板见「构建 / 测试命令」节；cmake 契约测试带 `-DSIZE_HEADER=...` `-DWIN32_SOURCE=...` `-DX11_SOURCE=...` `-DWAYLAND_SOURCE=...` `-DCOCOA_SOURCE=...` 五个输入）。

- [ ] **Step 2: 验证失败** — `cmake -S engine -B build-vk ...` 重新配置后 `ctest --test-dir build-vk -R "test_platform_size" --output-on-failure` → 预期：`test_platform_size_semantics` 编译失败（`platform_size.h` 不存在）；契约测试 FAIL `missing: .../platform_size.h`。

- [ ] **Step 3: 最小实现** — 创建 `platform_size.h`（内容见 Interfaces）；把四个窗口后端的内联公式替换为 helper 调用：
  - `window_win32.c:698-709` `platform_get_logical_size` 的体内计算改为 `platform_size_win32(p->width, p->height, scale, &lw, &lh, NULL, NULL)` 后赋值（保留 :699-705 的 NULL 守卫）；
  - `window_x11.c:1183-1187` 同理换 `platform_size_x11(p->width, p->height, scale, ...)`；
  - `window_wayland.c:2033-2037` 换 `platform_size_wayland(p->width, p->height, scale, NULL, NULL, &dw, &dh)`；
  - `window_cocoa.m:339-351` `cocoa_update_drawable_size` 中 `p->width/height` 与 `layer.drawableSize` 的数值改由 `platform_size_cocoa((u32)ceil(size.width), (u32)ceil(size.height), scale, &lw, &lh, &dw, &dh)` 产出（`contentsScale` 写入 :348 不变）。

- [ ] **Step 4: 验证通过** — `cmake --build build-vk --parallel`；`ctest --test-dir build-vk -R "test_platform_size" --output-on-failure` → PASS；`ctest --test-dir build-vk -LE "graphics|fuzz" --output-on-failure` 全绿（含六个 `test_platform_wsi_lifecycle_*` 变体与 `test_platform_*_runtime`）；GL 配置同样全绿。

- [ ] **Step 5: Commit**

```bash
git status --short
git add engine/src/platform/platform_size.h \
        engine/src/platform/window_win32.c engine/src/platform/window_x11.c \
        engine/src/platform/window_wayland.c engine/src/platform/window_cocoa.m \
        engine/tests/test_platform_size_semantics.c \
        engine/tests/test_platform_size_contract.cmake \
        engine/CMakeLists.txt
git commit -m "Lock logical-vs-drawable size semantics into shared platform_size helpers"
```

---

## Task 3: WSI 状态机接入真实窗口后端

**Files:**
- Modify: `engine/src/platform/platform_wsi.h`（:301 `platform_wsi_surface_destroy` 之后、:303 `#undef` 之前追加两个 inline 判定函数）
- Modify: `engine/src/platform/platform.h`（:3 之后追加 `#include <platform/platform_wsi.h>`；文件尾追加六个函数声明）
- Modify: `engine/src/platform/window_win32.c`、`window_x11.c`、`window_wayland.c`、`window_cocoa.m`、`window_mobile.c`（嵌入 `PlatformWsiSurface wsi` + 事件接线）
- Modify: `engine/src/rhi/rhi.h`（:3 之后 `#include <platform/platform_wsi.h>`；:358 `rhi_device_destroy_ex` 声明之后追加 `rhi_device_attach_wsi`）
- Modify: `engine/src/rhi/rhi_backend_internal.h`（`struct RHIDevice` :31-49 尾部追加 `PlatformWsiSurface *wsi;`）
- Modify: `engine/src/rhi/rhi.c`（`rhi_device_destroy_ex` :71-76 加 DESTROYING 门；追加 `rhi_device_attach_wsi`）
- Modify: `engine/src/main.c`（render_init :359 之后 attach；render_shutdown :1030 走 `_ex`；帧循环 :6050 前加帧门控；resize 检测 :4343-4348 消费 RESIZED 快照）
- Modify: `engine/src/test_vulkan.c`（`test_render_init` :430 之后 attach；`test_render_shutdown` :800 走 `_ex`）
- Test: `engine/tests/test_platform_wsi_lifecycle.c`（追加新 inline 函数用例——六个 `SIMULATE_*` 变体自动覆盖，`engine/CMakeLists.txt:384-396`）
- Test: `engine/tests/test_rhi_wsi_attach.c`（headless；销毁门控）
- Test: `engine/tests/test_platform_wsi_wiring_contract.cmake`（cmake -P 契约）
- Modify: `engine/CMakeLists.txt`（注册 attach 测试与契约测试）

**Interfaces:**
- Consumes: `platform_wsi_surface_init/resize/suspend/resume/lose/destroy`（`platform_wsi.h:207-301`）、`platform_size_*`（Task 2）、`rhi_frame_owner_preclaim_destroy`/`rhi_frame_owner_clear_preclaims`（`rhi_backend_internal.h:64,70`）、`rhi_test_device_create`/`rhi_test_device_destroy`（`rhi.c:362-387`，`ENGINE_RHI_TEST` 下）。
- Produces（`platform_wsi.h` 追加，完整内容）：

```c
/* 帧是否允许进入 RHI：仅 CREATED/RESIZED。SUSPENDED/LOST/DESTROYING/UNAVAILABLE
 * 一律拒绝——应用层据此跳过渲染，而不是让后端在死 surface 上空转。 */
PLATFORM_WSI_INLINE bool platform_wsi_frame_allowed(const PlatformWsiSurface *surface)
{
    return surface != NULL &&
           (surface->state == PLATFORM_WSI_CREATED ||
            surface->state == PLATFORM_WSI_RESIZED);
}

/* RHI 销毁门控：进入 DESTROYING 后拒绝销毁。销毁顺序契约：
 * rhi_device_destroy_ex 必须先于 platform_destroy（后者把状态推入
 * DESTROYING）。 */
PLATFORM_WSI_INLINE bool platform_wsi_rhi_teardown_allowed(const PlatformWsiSurface *surface)
{
    return surface != NULL && surface->state != PLATFORM_WSI_DESTROYING;
}
```

- Produces（`platform.h` 尾部追加，完整内容）：

```c
/* ---- WSI surface 状态机（platform_wsi.h）---- */
/* 当前 WSI 状态快照；p 或 out 为 NULL 返回 false。 */
bool platform_wsi_surface_query(Platform *p, PlatformWsiSurface *out);
/* 设备级 WSI 状态对象的非拥有指针（挂到 RHIDevice 用，见 rhi_device_attach_wsi；
 * Platform 拥有存储，生命周期长于任何 RHIDevice 使用窗口）。 */
PlatformWsiSurface *platform_wsi_surface(Platform *p);
/* 移动宿主回调（iOS/Android 的 host-injection 入口，window_mobile.c 真实实现；
 * 桌面后端是 no-op——桌面没有 OS 级 suspend/resume/surface-lost 事件，相应语义
 * 由 resize 与 DESTROYING 覆盖）。 */
void platform_mobile_notify_suspend(Platform *p);
void platform_mobile_notify_resume(Platform *p);
void platform_mobile_notify_surface_lost(Platform *p);
void platform_mobile_notify_surface_recreated(Platform *p, void *native_window,
                                              u32 width, u32 height);
```

- Produces（`rhi.h` 追加）：

```c
/* 把平台层 WSI 状态对象挂到设备（非拥有指针，Platform 拥有存储）。
 * 挂上后 rhi_device_destroy_ex 在 WSI DESTROYING 状态返回 RHI_RESULT_BUSY
 * 并拒绝销毁；wsi == NULL 解除挂载。 */
void rhi_device_attach_wsi(RHIDevice *dev, PlatformWsiSurface *wsi);
```

- Produces（`rhi.c` 追加 / 修改，完整内容）：

```c
void rhi_device_attach_wsi(RHIDevice *dev, PlatformWsiSurface *wsi) {
    if (dev != NULL) dev->wsi = wsi;
}
```

```c
RHIResult rhi_device_destroy_ex(RHIDevice *dev) {
    if (dev == NULL) return RHI_RESULT_INVALID_ARGUMENT;
    if (!rhi_frame_owner_preclaim_destroy(dev)) return RHI_RESULT_BUSY;
    /* WSI DESTROYING 门控：窗口已进入销毁流程的 surface 上不再拆设备；
     * 调用方必须先完成 RHI 销毁再进入 platform_destroy。 */
    if (dev->wsi != NULL && !platform_wsi_rhi_teardown_allowed(dev->wsi)) {
        rhi_frame_owner_clear_preclaims(dev);
        return RHI_RESULT_BUSY;
    }
    rhi_device_destroy(dev);
    return RHI_RESULT_OK;
}
```

- [ ] **Step 1: 写失败测试（headless 三件套）** —
  ① `engine/tests/test_platform_wsi_lifecycle.c` 追加（镜像既有 `TEST(...)` 风格与该文件尾部 `TEST_MAIN` 注册列表）：

```c
TEST(wsi_frame_allowed_only_when_created_or_resized)
{
    PlatformWsiSurface surface;
    ASSERT_EQ(platform_wsi_surface_init(&surface, true, 100u, 100u, 100u, 100u),
              PLATFORM_WSI_OK);
    ASSERT_TRUE(platform_wsi_frame_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_resize(&surface, 200u, 200u, 200u, 200u),
              PLATFORM_WSI_OK);
    ASSERT_TRUE(platform_wsi_frame_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_suspend(&surface), PLATFORM_WSI_OK);
    ASSERT_FALSE(platform_wsi_frame_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_resume(&surface), PLATFORM_WSI_OK);
    ASSERT_TRUE(platform_wsi_frame_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_lose(&surface), PLATFORM_WSI_OK);
    ASSERT_FALSE(platform_wsi_frame_allowed(&surface));
    ASSERT_FALSE(platform_wsi_frame_allowed(NULL));
}

TEST(wsi_teardown_rejected_while_destroying)
{
    PlatformWsiSurface surface;
    ASSERT_EQ(platform_wsi_surface_init(&surface, true, 100u, 100u, 100u, 100u),
              PLATFORM_WSI_OK);
    ASSERT_TRUE(platform_wsi_rhi_teardown_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_destroy(&surface), PLATFORM_WSI_OK);
    ASSERT_FALSE(platform_wsi_rhi_teardown_allowed(&surface));
    ASSERT_FALSE(platform_wsi_rhi_teardown_allowed(NULL));
}
```

  ② 创建 `engine/tests/test_rhi_wsi_attach.c`（注册块镜像 `test_rhi_capabilities`，`engine/CMakeLists.txt:1824-1880`，只换目标名/源文件名）：

```c
#include "test_framework.h"
#include "rhi/rhi.h"
#include "platform/platform_wsi.h"

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);

TEST(destroy_ex_runs_cleanly_with_healthy_wsi)
{
    RHIDevice *dev = rhi_test_device_create();
    PlatformWsiSurface wsi;
    ASSERT_NEQ(dev, NULL);
    ASSERT_EQ(platform_wsi_surface_init(&wsi, true, 64u, 64u, 64u, 64u),
              PLATFORM_WSI_OK);
    rhi_device_attach_wsi(dev, &wsi);
    /* 伪设备无 backend_data：destroy 路径是空转，门控语义不受影响
     *（同例：test_rhi_capabilities.c:509-512 的 destroy_ex 用例）。 */
    ASSERT_EQ(rhi_device_destroy_ex(dev), RHI_RESULT_OK);
    rhi_test_device_destroy(dev);
}

TEST(destroy_ex_rejects_while_wsi_destroying)
{
    RHIDevice *dev = rhi_test_device_create();
    PlatformWsiSurface wsi;
    ASSERT_NEQ(dev, NULL);
    ASSERT_EQ(platform_wsi_surface_init(&wsi, true, 64u, 64u, 64u, 64u),
              PLATFORM_WSI_OK);
    rhi_device_attach_wsi(dev, &wsi);
    ASSERT_EQ(platform_wsi_surface_destroy(&wsi), PLATFORM_WSI_OK);
    ASSERT_EQ(rhi_device_destroy_ex(dev), RHI_RESULT_BUSY);
    /* 门控拒绝后设备仍可正常销毁：解除挂载即恢复。 */
    rhi_device_attach_wsi(dev, NULL);
    ASSERT_EQ(rhi_device_destroy_ex(dev), RHI_RESULT_OK);
    rhi_test_device_destroy(dev);
}

TEST(destroy_ex_ignores_null_wsi_attachment)
{
    RHIDevice *dev = rhi_test_device_create();
    ASSERT_NEQ(dev, NULL);
    ASSERT_EQ(rhi_device_destroy_ex(dev), RHI_RESULT_OK);
    rhi_test_device_destroy(dev);
}

TEST_MAIN_BEGIN()
    RUN_TEST(destroy_ex_runs_cleanly_with_healthy_wsi);
    RUN_TEST(destroy_ex_rejects_while_wsi_destroying);
    RUN_TEST(destroy_ex_ignores_null_wsi_attachment);
TEST_MAIN_END()
```

  ③ 创建 `engine/tests/test_platform_wsi_wiring_contract.cmake`：

```cmake
foreach(required_var PLATFORM_H WSI_H WIN32_SOURCE X11_SOURCE WAYLAND_SOURCE
                     COCOA_SOURCE MOBILE_SOURCE RHI_SOURCE RHI_INTERNAL_HEADER MAIN_SOURCE)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

# platform.h：只增不改——既有签名 token 必须还在。
file(READ "${PLATFORM_H}" platform_text)
foreach(required_token
        "platform_wsi_surface_query" "platform_wsi_surface("
        "platform_mobile_notify_suspend" "platform_mobile_notify_resume"
        "platform_mobile_notify_surface_lost" "platform_mobile_notify_surface_recreated"
        "platform_window_native" "platform_display_native" "platform_surface_native")
    string(FIND "${platform_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "platform.h missing token: ${required_token}")
    endif()
endforeach()

# platform_wsi.h：两个新判定函数；OHOS 不得进入后端枚举。
file(READ "${WSI_H}" wsi_text)
foreach(required_token "platform_wsi_frame_allowed" "platform_wsi_rhi_teardown_allowed")
    string(FIND "${wsi_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "platform_wsi.h missing: ${required_token}")
    endif()
endforeach()
string(FIND "${wsi_text}" "PLATFORM_WSI_BACKEND_OHOS" ohos_offset)
if(NOT ohos_offset EQUAL -1)
    message(FATAL_ERROR "OHOS must stay out of PlatformWsiBackend (fail-closed)")
endif()

# 五个窗口后端的接线 token。
foreach(backend_spec
        "${WIN32_SOURCE}|platform_wsi_surface_suspend"
        "${WIN32_SOURCE}|platform_wsi_surface_resize"
        "${X11_SOURCE}|platform_wsi_surface_resize"
        "${WAYLAND_SOURCE}|platform_wsi_surface_resize"
        "${COCOA_SOURCE}|platform_wsi_surface_resize"
        "${MOBILE_SOURCE}|platform_mobile_notify_suspend"
        "${MOBILE_SOURCE}|platform_mobile_notify_resume"
        "${MOBILE_SOURCE}|platform_mobile_notify_surface_lost"
        "${MOBILE_SOURCE}|platform_mobile_notify_surface_recreated")
    string(REPLACE "|" ";" backend_parts "${backend_spec}")
    list(GET backend_parts 0 backend_path)
    list(GET backend_parts 1 backend_token)
    file(READ "${backend_path}" backend_text)
    string(FIND "${backend_text}" "${backend_token}" backend_offset)
    if(backend_offset EQUAL -1)
        message(FATAL_ERROR
            "WSI wiring missing: ${backend_path} <- ${backend_token}")
    endif()
endforeach()
foreach(backend_path
        "${WIN32_SOURCE}" "${X11_SOURCE}" "${WAYLAND_SOURCE}"
        "${COCOA_SOURCE}" "${MOBILE_SOURCE}")
    file(READ "${backend_path}" backend_text)
    foreach(lifecycle_token
            "platform_wsi_surface_init" "platform_wsi_surface_destroy"
            "platform_wsi_surface_query")
        string(FIND "${backend_text}" "${lifecycle_token}" offset)
        if(offset EQUAL -1)
            message(FATAL_ERROR
                "WSI wiring missing: ${backend_path} <- ${lifecycle_token}")
        endif()
    endforeach()
endforeach()

# RHI 侧：挂载点 + DESTROYING 门。
file(READ "${RHI_INTERNAL_HEADER}" internal_text)
string(FIND "${internal_text}" "PlatformWsiSurface *wsi" internal_offset)
if(internal_offset EQUAL -1)
    message(FATAL_ERROR "RHIDevice must carry a PlatformWsiSurface attachment")
endif()
file(READ "${RHI_SOURCE}" rhi_text)
foreach(required_token "rhi_device_attach_wsi" "platform_wsi_rhi_teardown_allowed")
    string(FIND "${rhi_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "rhi.c missing: ${required_token}")
    endif()
endforeach()
file(READ "${MAIN_SOURCE}" main_text)
foreach(required_token "rhi_device_attach_wsi" "rhi_device_destroy_ex")
    string(FIND "${main_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "main.c missing: ${required_token}")
    endif()
endforeach()
```

注册契约测试（模板见「构建 / 测试命令」节，输入 `-DPLATFORM_H=.../platform.h -DWSI_H=.../platform_wsi.h -DWIN32_SOURCE=... -DX11_SOURCE=... -DWAYLAND_SOURCE=... -DCOCOA_SOURCE=... -DMOBILE_SOURCE=... -DRHI_SOURCE=.../rhi.c -DRHI_INTERNAL_HEADER=.../rhi_backend_internal.h -DMAIN_SOURCE=.../main.c`）。

- [ ] **Step 2: 验证失败** — 重新配置后 `ctest --test-dir build-vk -R "wsi" --output-on-failure` → 预期：`test_platform_wsi_lifecycle`（及六个 SIMULATE 变体）编译失败（`platform_wsi_frame_allowed` 未定义）；`test_rhi_wsi_attach` 链接失败（`rhi_device_attach_wsi` 未定义）；`test_platform_wsi_wiring_contract` FAIL（`platform.h missing token: platform_wsi_surface_query`）。

- [ ] **Step 3: 最小实现（状态机扩展 + 后端接线）** —
  ① `platform_wsi.h` 追加两个 inline（内容见 Interfaces，插在 :301 与 :303 之间）；
  ② `platform.h` 追加 include 与六个声明（内容见 Interfaces）；
  ③ 五个窗口后端的 `struct Platform` 各加 `PlatformWsiSurface wsi;`（win32 :38-63 / x11 :26-84 / wayland :73-184 / cocoa 的 @interface 前的 struct / mobile :9-17），并实现 `platform_wsi_surface_query`（NULL 守卫 + `*out = p->wsi`）与 `platform_wsi_surface`（返回 `&p->wsi`）；
  ④ 各后端 `platform_create` 在尺寸确定后调用 `platform_wsi_surface_init(&p->wsi, true, lw, lh, dw, dh)`（尺寸经 Task 2 的 helper 计算：win32 :496-497 之后；x11 :823-824 之后；wayland :1824-1827 wl_egl_window_create 成功之后；cocoa :416 `cocoa_update_drawable_size(p)` 之后；mobile :31 赋值之后，drawable==logical==w/h）；
  ⑤ resize 事件接线：
  - `window_win32.c:302-305` 的 `WM_SIZE` 改为：

```c
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED) {
            (void)platform_wsi_surface_suspend(&p->wsi);
            return 0;
        }
        p->width  = (u32)LOWORD(lParam);
        p->height = (u32)HIWORD(lParam);
        if (p->wsi.state == PLATFORM_WSI_SUSPENDED)
            (void)platform_wsi_surface_resume(&p->wsi);
        {
            u32 lw, lh, dw, dh;
            platform_size_win32(p->width, p->height,
                                platform_get_content_scale(p),
                                &lw, &lh, &dw, &dh);
            (void)platform_wsi_surface_resize(&p->wsi, lw, lh, dw, dh);
        }
        return 0;
```

  - `window_x11.c:1094-1098` `ConfigureNotify` 的 `x11_update_active_monitor(p)` 之后追加：

```c
            {
                u32 lw, lh, dw, dh;
                platform_size_x11(p->width, p->height,
                                  (u32)(p->scale_factor > 0 ? p->scale_factor : 1),
                                  &lw, &lh, &dw, &dh);
                (void)platform_wsi_surface_resize(&p->wsi, lw, lh, dw, dh);
            }
```

  - `window_wayland.c:842-852` `xdg_toplevel_handle_configure`：`wayland_update_surface_scale(p)` 调用之后追加：

```c
        {
            u32 lw, lh, dw, dh;
            platform_size_wayland(p->width, p->height, p->content_scale_120,
                                  &lw, &lh, &dw, &dh);
            (void)platform_wsi_surface_resize(&p->wsi, lw, lh, dw, dh);
        }
```

  - `window_cocoa.m` `cocoa_update_drawable_size`（:339-351）末尾追加：

```c
    {
        u32 lw = 0, lh = 0, dw = 0, dh = 0;
        platform_size_cocoa(p->width, p->height, (f32)scale, &lw, &lh, &dw, &dh);
        (void)platform_wsi_surface_resize(&p->wsi, lw, lh, dw, dh);
    }
```

  ⑥ surface lost / destroy：
  - 各桌面后端 `platform_destroy` 首个语句（NULL 守卫之后）加 `(void)platform_wsi_surface_destroy(&p->wsi);`（win32 :583 / wayland :1860 / cocoa :434 / x11 :901 / mobile :44）；
  - Wayland 的 wl_surface 销毁点就在 `platform_destroy`（:1896），桌面 compositor 不主动销毁 client surface——不新增事件；
  - `window_mobile.c` 实现四个 host 回调（完整内容）：

```c
void platform_mobile_notify_suspend(Platform *p) {
    if (p) (void)platform_wsi_surface_suspend(&p->wsi);
}
void platform_mobile_notify_resume(Platform *p) {
    if (p) (void)platform_wsi_surface_resume(&p->wsi);
}
void platform_mobile_notify_surface_lost(Platform *p) {
    if (p) (void)platform_wsi_surface_lose(&p->wsi);
}
void platform_mobile_notify_surface_recreated(Platform *p, void *native_window,
                                              u32 width, u32 height) {
    if (!p || native_window == NULL) return;
    p->native_window = native_window;
    p->width = width;
    p->height = height;
    /* 状态机没有 LOST->CREATED 迁移（platform_wsi.h:280-291）；Android 语义上
     * surfaceCreated 产出的是全新 surface，走 init 全量重置回 CREATED。
     * Vulkan 侧此时必须整体重建设备（VK_ERROR_SURFACE_LOST 路径）。 */
    (void)platform_wsi_surface_init(&p->wsi, true, width, height, width, height);
}
```

  - 四个桌面后端各补四个 no-op（`void platform_mobile_notify_suspend(Platform *p) { (void)p; }` 等，注释指向 platform.h 的语义说明）；
  ⑦ RHI 侧：`rhi_backend_internal.h` 追加字段；`rhi.h` 追加 include 与声明；`rhi.c` 追加 `rhi_device_attach_wsi` 并改 `rhi_device_destroy_ex`（内容见 Interfaces）；
  ⑧ 消费点：`main.c` render_init :359 `if (!rs->device) return false;` 之前插入 `rhi_device_attach_wsi(rs->device, platform_wsi_surface(platform));`；render_shutdown :1030 的 `rhi_device_destroy(rs->device)` 改为：

```c
    {
        RHIResult destroy_result = rhi_device_destroy_ex(rs->device);
        if (destroy_result != RHI_RESULT_OK)
            LOG_ERROR("rhi_device_destroy_ex: %d", (int)destroy_result);
    }
    rs->device = NULL;
```

  `test_vulkan.c` 同改（:430 之后 attach，:800 改 `_ex`）。
  ⑨ 帧门控：`main.c` :6050 `RHICmdBuffer *cmd = rhi_frame_begin(render.device);` 之前插入：

```c
        PlatformWsiSurface wsi_snapshot;
        if (platform_wsi_surface_query(engine.platform, &wsi_snapshot) &&
            !platform_wsi_frame_allowed(&wsi_snapshot)) {
            platform_poll(engine.platform);
            continue; /* SUSPENDED/LOST/DESTROYING：跳过本帧渲染 */
        }
```

  （先 Read `main.c:6040-6060` 确认循环上下文——`continue` 必须落在主帧循环内；若该处不是循环体最近边界，调整为跳过渲染段而非 continue。）
  ⑩ resize 消费：`main.c` :4343-4348 的 resize 检测块中，`rhi_device_resize(render.device, w, h)`（:4345）之前插入：

```c
            PlatformWsiSurface wsi_snapshot;
            if (platform_wsi_surface_query(engine.platform, &wsi_snapshot) &&
                wsi_snapshot.state == PLATFORM_WSI_RESIZED) {
                w = wsi_snapshot.drawable_width;
                h = wsi_snapshot.drawable_height;
            }
```

- [ ] **Step 4: 验证通过** — `cmake --build build-vk --parallel` 全量通过；`ctest --test-dir build-vk -R "wsi" --output-on-failure` 全绿（含六个 SIMULATE 变体 + attach + 契约）；`ctest --test-dir build-vk -LE "graphics|fuzz" --output-on-failure` 全绿；`ctest --test-dir build-vk -L graphics --output-on-failure` 全绿（本机真 GPU：resize/销毁路径回归）；`test_platform_win32_runtime`（label `platform_runtime`）通过——它真实创建 Win32 窗口，是 WM_SIZE→WSI 接线的 runtime 证据。GL 配置同步全绿。

- [ ] **Step 5: Commit**

```bash
git status --short
git add engine/src/platform/platform_wsi.h engine/src/platform/platform.h \
        engine/src/platform/window_win32.c engine/src/platform/window_x11.c \
        engine/src/platform/window_wayland.c engine/src/platform/window_cocoa.m \
        engine/src/platform/window_mobile.c \
        engine/src/rhi/rhi.h engine/src/rhi/rhi.c engine/src/rhi/rhi_backend_internal.h \
        engine/src/main.c engine/src/test_vulkan.c \
        engine/tests/test_platform_wsi_lifecycle.c \
        engine/tests/test_rhi_wsi_attach.c \
        engine/tests/test_platform_wsi_wiring_contract.cmake \
        engine/CMakeLists.txt
git commit -m "Wire the WSI surface state machine into all five window backends"
```

---

## Task 4: Vulkan 探测完善（纯函数抽取 + 接线）

**Files:**
- Create: `engine/src/rhi/rhi_vk_probe.h`（探测/协商纯函数，不含 Vulkan 头）
- Test: `engine/tests/test_rhi_vk_probe.c`（headless 纯逻辑单测）
- Modify: `engine/src/rhi/rhi.h`（`RHICapabilities` :112-124 尾部追加两个 bool）
- Modify: `engine/src/rhi/rhi_vk.c`（adapter 选择 :1758-1778、queue family :1841-1856、surface format :1069-1095、present mode :1151-1168 改经纯函数；新增 dynamic rendering / synchronization2 探测；常量 `_Static_assert` 钉死）
- Modify: `engine/CMakeLists.txt`（注册测试）

**Interfaces:**
- Consumes: `vk_physical_device_suitable`（`rhi_vk.c:751-796`）、`vk_device_extension_present`（:570-592）、`RHIFeatureBits`（`rhi.h:85-89`）。
- Produces（`rhi_vk_probe.h`，完整内容）：

```c
#pragma once
#include <core/types.h>

/* 纯函数 Vulkan 探测/协商逻辑——不包含 <vulkan/vulkan.h>。数值常量与
 * VkPhysicalDeviceType / VkPresentModeKHR / VkFormat / VkColorSpaceKHR /
 * VkQueueFlagBits / RHIFeatureBits 一一对应，由 rhi_vk.c 顶部的
 * _Static_assert 组钉死（漂移即编译失败，而不是 GPU 上出错）。
 * 全部函数无堆分配、无全局状态，headless 单测直接包含。 */

/* VkPhysicalDeviceType */
#define VK_PROBE_DEVICE_TYPE_OTHER      0u
#define VK_PROBE_DEVICE_TYPE_INTEGRATED 1u
#define VK_PROBE_DEVICE_TYPE_DISCRETE   2u
#define VK_PROBE_DEVICE_TYPE_VIRTUAL    3u
#define VK_PROBE_DEVICE_TYPE_CPU        4u
/* VkQueueFlagBits */
#define VK_PROBE_QUEUE_GRAPHICS_BIT 0x00000001u
/* VkPresentModeKHR */
#define VK_PROBE_PRESENT_MODE_IMMEDIATE    0u
#define VK_PROBE_PRESENT_MODE_MAILBOX      1u
#define VK_PROBE_PRESENT_MODE_FIFO         2u
#define VK_PROBE_PRESENT_MODE_FIFO_RELAXED 3u
/* VkFormat / VkColorSpaceKHR */
#define VK_PROBE_FORMAT_UNDEFINED           0u
#define VK_PROBE_FORMAT_R8G8B8A8_SRGB       43u
#define VK_PROBE_FORMAT_B8G8R8A8_UNORM      44u
#define VK_PROBE_FORMAT_B8G8R8A8_SRGB       50u
#define VK_PROBE_COLORSPACE_SRGB_NONLINEAR  0u
/* RHIFeatureBits（rhi.h:85-89） */
#define VK_PROBE_FEATURE_RAY_TRACING_PIPELINE 1u
#define VK_PROBE_FEATURE_RAY_QUERY            2u
#define VK_PROBE_FEATURE_ACCELERATION_STRUCTURE 4u

typedef struct VkProbeAdapterInfo {
    u32  device_type;  /* VkPhysicalDeviceType 数值 */
    u32  api_version;  /* VkPhysicalDeviceProperties.apiVersion 编码值 */
    bool suitable;     /* vk_physical_device_suitable 的预计算结果 */
} VkProbeAdapterInfo;

typedef struct VkProbeSurfaceFormat {
    u32 format;
    u32 color_space;
} VkProbeSurfaceFormat;

/* Adapter 打分：discrete > integrated > virtual > software(cpu) > other；
 * 不可用（suitable=false）得 -1，永不中选。 */
static inline i32 vk_probe_adapter_score(const VkProbeAdapterInfo *info) {
    if (info == NULL || !info->suitable) return -1;
    switch (info->device_type) {
    case VK_PROBE_DEVICE_TYPE_DISCRETE:   return 300;
    case VK_PROBE_DEVICE_TYPE_INTEGRATED: return 200;
    case VK_PROBE_DEVICE_TYPE_VIRTUAL:    return 100;
    case VK_PROBE_DEVICE_TYPE_CPU:        return 10;
    default:                              return 0;
    }
}

/* 返回最高分的下标；同分取 api_version 更高者，再同取下标更小者；
 * 全部不可用返回 -1。 */
static inline i32 vk_probe_select_adapter(const VkProbeAdapterInfo *adapters,
                                          u32 count) {
    i32 best = -1;
    i32 best_score = -1;
    u32 best_api = 0u;
    u32 i;
    if (adapters == NULL) return -1;
    for (i = 0; i < count; i++) {
        i32 score = vk_probe_adapter_score(&adapters[i]);
        if (score < 0) continue;
        if (score > best_score ||
            (score == best_score && adapters[i].api_version > best_api)) {
            best = (i32)i;
            best_score = score;
            best_api = adapters[i].api_version;
        }
    }
    return best;
}

/* queue family：优先同时具备 graphics+present 的 family（swapchain 可用
 * EXCLUSIVE sharing，少一条 queue）；否则首个 graphics + 首个 present。
 * 任一缺失返回 false。 */
static inline bool vk_probe_choose_queue_families(const u32 *queue_flags,
                                                  const bool *present_support,
                                                  u32 family_count,
                                                  u32 *out_graphics,
                                                  u32 *out_present) {
    u32 graphics = UINT32_MAX;
    u32 present = UINT32_MAX;
    u32 i;
    if (queue_flags == NULL || present_support == NULL ||
        out_graphics == NULL || out_present == NULL)
        return false;
    for (i = 0; i < family_count; i++) {
        bool has_graphics = (queue_flags[i] & VK_PROBE_QUEUE_GRAPHICS_BIT) != 0u;
        if (has_graphics && present_support[i]) {
            *out_graphics = i;
            *out_present = i;
            return true;
        }
        if (has_graphics && graphics == UINT32_MAX) graphics = i;
        if (present_support[i] && present == UINT32_MAX) present = i;
    }
    if (graphics == UINT32_MAX || present == UINT32_MAX) return false;
    *out_graphics = graphics;
    *out_present = present;
    return true;
}

/* present mode 协商（输入为 VkPresentModeKHR 数值数组）：
 * vsync 开：MAILBOX > FIFO_RELAXED > FIFO；
 * vsync 关：IMMEDIATE > MAILBOX > FIFO_RELAXED > FIFO
 *（锁定既有行为 rhi_vk.c:1151-1168）。FIFO 由规范保证存在；全部缺失时仍返回
 * FIFO，让调用方在创建时报错而不是静默选错。 */
static inline u32 vk_probe_choose_present_mode(const u32 *modes, u32 count,
                                               bool vsync) {
    static const u32 vsync_order[] = {
        VK_PROBE_PRESENT_MODE_MAILBOX, VK_PROBE_PRESENT_MODE_FIFO_RELAXED,
        VK_PROBE_PRESENT_MODE_FIFO,
    };
    static const u32 no_vsync_order[] = {
        VK_PROBE_PRESENT_MODE_IMMEDIATE, VK_PROBE_PRESENT_MODE_MAILBOX,
        VK_PROBE_PRESENT_MODE_FIFO_RELAXED, VK_PROBE_PRESENT_MODE_FIFO,
    };
    const u32 *order = vsync ? vsync_order : no_vsync_order;
    u32 order_count = vsync ? 3u : 4u;
    u32 oi, i;
    if (modes != NULL) {
        for (oi = 0; oi < order_count; oi++)
            for (i = 0; i < count; i++)
                if (modes[i] == order[oi]) return order[oi];
    }
    return VK_PROBE_PRESENT_MODE_FIFO;
}

/* surface format 协商（锁定既有行为 rhi_vk.c:1069-1095）：
 * count==1 且 format==UNDEFINED（"任意格式"哨兵）→ B8G8R8A8_SRGB + 其
 * colorSpace；否则首选 B8G8R8A8_SRGB，再 R8G8B8A8_SRGB，否则 formats[0]。
 * count==0 / 参数为 NULL 返回 false。 */
static inline bool vk_probe_choose_surface_format(const VkProbeSurfaceFormat *formats,
                                                  u32 count,
                                                  VkProbeSurfaceFormat *out) {
    u32 i;
    if (formats == NULL || out == NULL || count == 0u) return false;
    if (count == 1u && formats[0].format == VK_PROBE_FORMAT_UNDEFINED) {
        out->format = VK_PROBE_FORMAT_B8G8R8A8_SRGB;
        out->color_space = formats[0].color_space;
        return true;
    }
    for (i = 0; i < count; i++) {
        if (formats[i].format == VK_PROBE_FORMAT_B8G8R8A8_SRGB) {
            *out = formats[i];
            return true;
        }
    }
    for (i = 0; i < count; i++) {
        if (formats[i].format == VK_PROBE_FORMAT_R8G8B8A8_SRGB) {
            *out = formats[i];
            return true;
        }
    }
    *out = formats[0];
    return true;
}

/* RHIFeatureBits 组装：只报告扩展存在且特性已启用的位（调用方责任）。 */
static inline u32 vk_probe_feature_bits(bool accel, bool rt_pipeline,
                                        bool ray_query) {
    return (accel ? VK_PROBE_FEATURE_ACCELERATION_STRUCTURE : 0u) |
           (rt_pipeline ? VK_PROBE_FEATURE_RAY_TRACING_PIPELINE : 0u) |
           (ray_query ? VK_PROBE_FEATURE_RAY_QUERY : 0u);
}
```

- Produces（`rhi.h` `RHICapabilities` 尾部追加，`feature_bits` :123 之后）：

```c
    /* 迁移期新增（源码兼容追加，无 struct_size——调用方按完整结构编译）：
     * VK_KHR_dynamic_rendering / VK_KHR_synchronization2（或 API>=1.3 核心）
     * 的探测结果；只探测不消费，消费接入在后续计划。 */
    bool       dynamic_rendering_supported;
    bool       synchronization2_supported;
```

- [ ] **Step 1: 写失败测试** — 创建 `engine/tests/test_rhi_vk_probe.c`：

```c
#include "test_framework.h"
#include "rhi/rhi_vk_probe.h"

TEST(adapter_score_orders_discrete_over_integrated_over_software) {
    VkProbeAdapterInfo d = { VK_PROBE_DEVICE_TYPE_DISCRETE, 0u, true };
    VkProbeAdapterInfo i = { VK_PROBE_DEVICE_TYPE_INTEGRATED, 0u, true };
    VkProbeAdapterInfo c = { VK_PROBE_DEVICE_TYPE_CPU, 0u, true };
    VkProbeAdapterInfo o = { VK_PROBE_DEVICE_TYPE_OTHER, 0u, true };
    ASSERT_TRUE(vk_probe_adapter_score(&d) > vk_probe_adapter_score(&i));
    ASSERT_TRUE(vk_probe_adapter_score(&i) > vk_probe_adapter_score(&c));
    ASSERT_TRUE(vk_probe_adapter_score(&c) > vk_probe_adapter_score(&o));
}

TEST(adapter_unsuitable_scores_negative_and_never_selected) {
    VkProbeAdapterInfo bad = { VK_PROBE_DEVICE_TYPE_DISCRETE, 0u, false };
    VkProbeAdapterInfo ok  = { VK_PROBE_DEVICE_TYPE_CPU, 0u, true };
    VkProbeAdapterInfo set[2] = { bad, ok };
    ASSERT_EQ(vk_probe_adapter_score(&bad), -1);
    ASSERT_EQ(vk_probe_select_adapter(set, 2u), 1);
    ASSERT_EQ(vk_probe_select_adapter(&bad, 1u), -1);
    ASSERT_EQ(vk_probe_select_adapter(NULL, 0u), -1);
}

TEST(adapter_tie_breaks_on_api_version_then_lowest_index) {
    VkProbeAdapterInfo set[3] = {
        { VK_PROBE_DEVICE_TYPE_DISCRETE, 0x00401000u, true },
        { VK_PROBE_DEVICE_TYPE_DISCRETE, 0x00403000u, true },
        { VK_PROBE_DEVICE_TYPE_DISCRETE, 0x00403000u, true },
    };
    ASSERT_EQ(vk_probe_select_adapter(set, 3u), 1);
    set[1].api_version = set[0].api_version;
    ASSERT_EQ(vk_probe_select_adapter(set, 3u), 0);
}

TEST(queue_families_prefer_combined_graphics_present) {
    u32 flags[3] = { VK_PROBE_QUEUE_GRAPHICS_BIT, 0u,
                     VK_PROBE_QUEUE_GRAPHICS_BIT };
    bool present[3] = { false, true, true };
    u32 g = 99u, p = 99u;
    ASSERT_TRUE(vk_probe_choose_queue_families(flags, present, 3u, &g, &p));
    ASSERT_EQ(g, 2u); /* combined 优先：家族 2 双支持 */
    ASSERT_EQ(p, 2u);
}

TEST(queue_families_split_when_no_combined) {
    u32 flags[2] = { VK_PROBE_QUEUE_GRAPHICS_BIT, 0u };
    bool present[2] = { false, true };
    u32 g = 99u, p = 99u;
    ASSERT_TRUE(vk_probe_choose_queue_families(flags, present, 2u, &g, &p));
    ASSERT_EQ(g, 0u);
    ASSERT_EQ(p, 1u);
    ASSERT_FALSE(vk_probe_choose_queue_families(flags, present, 1u, &g, &p));
}

TEST(present_mode_vsync_prefers_mailbox_then_relaxed_then_fifo) {
    u32 all[4] = { VK_PROBE_PRESENT_MODE_FIFO, VK_PROBE_PRESENT_MODE_IMMEDIATE,
                   VK_PROBE_PRESENT_MODE_FIFO_RELAXED, VK_PROBE_PRESENT_MODE_MAILBOX };
    u32 no_mailbox[3] = { VK_PROBE_PRESENT_MODE_FIFO, VK_PROBE_PRESENT_MODE_IMMEDIATE,
                          VK_PROBE_PRESENT_MODE_FIFO_RELAXED };
    u32 fifo_only[1] = { VK_PROBE_PRESENT_MODE_FIFO };
    ASSERT_EQ(vk_probe_choose_present_mode(all, 4u, true), VK_PROBE_PRESENT_MODE_MAILBOX);
    ASSERT_EQ(vk_probe_choose_present_mode(no_mailbox, 3u, true),
              VK_PROBE_PRESENT_MODE_FIFO_RELAXED);
    ASSERT_EQ(vk_probe_choose_present_mode(fifo_only, 1u, true),
              VK_PROBE_PRESENT_MODE_FIFO);
}

TEST(present_mode_no_vsync_prefers_immediate) {
    u32 all[4] = { VK_PROBE_PRESENT_MODE_FIFO, VK_PROBE_PRESENT_MODE_IMMEDIATE,
                   VK_PROBE_PRESENT_MODE_FIFO_RELAXED, VK_PROBE_PRESENT_MODE_MAILBOX };
    u32 no_immediate[2] = { VK_PROBE_PRESENT_MODE_FIFO, VK_PROBE_PRESENT_MODE_MAILBOX };
    ASSERT_EQ(vk_probe_choose_present_mode(all, 4u, false),
              VK_PROBE_PRESENT_MODE_IMMEDIATE);
    ASSERT_EQ(vk_probe_choose_present_mode(no_immediate, 2u, false),
              VK_PROBE_PRESENT_MODE_MAILBOX);
    ASSERT_EQ(vk_probe_choose_present_mode(NULL, 0u, false),
              VK_PROBE_PRESENT_MODE_FIFO);
}

TEST(surface_format_prefers_bgra_srgb_then_rgba_srgb_then_first) {
    VkProbeSurfaceFormat formats[3] = {
        { 37u, VK_PROBE_COLORSPACE_SRGB_NONLINEAR }, /* R8G8B8A8_UNORM */
        { VK_PROBE_FORMAT_B8G8R8A8_SRGB, VK_PROBE_COLORSPACE_SRGB_NONLINEAR },
        { VK_PROBE_FORMAT_R8G8B8A8_SRGB, VK_PROBE_COLORSPACE_SRGB_NONLINEAR },
    };
    VkProbeSurfaceFormat picked = { 0xFFFFFFFFu, 0xFFFFFFFFu };
    ASSERT_TRUE(vk_probe_choose_surface_format(formats, 3u, &picked));
    ASSERT_EQ(picked.format, VK_PROBE_FORMAT_B8G8R8A8_SRGB);
    ASSERT_TRUE(vk_probe_choose_surface_format(&formats[2], 1u, &picked));
    ASSERT_EQ(picked.format, VK_PROBE_FORMAT_R8G8B8A8_SRGB);
    ASSERT_TRUE(vk_probe_choose_surface_format(formats, 1u, &picked));
    ASSERT_EQ(picked.format, 37u); /* 无 sRGB 时退回 formats[0] */
    ASSERT_FALSE(vk_probe_choose_surface_format(formats, 0u, &picked));
}

TEST(surface_format_undefined_sentinel_means_any) {
    VkProbeSurfaceFormat any[1] = {
        { VK_PROBE_FORMAT_UNDEFINED, VK_PROBE_COLORSPACE_SRGB_NONLINEAR } };
    VkProbeSurfaceFormat picked = { 0u, 0u };
    ASSERT_TRUE(vk_probe_choose_surface_format(any, 1u, &picked));
    ASSERT_EQ(picked.format, VK_PROBE_FORMAT_B8G8R8A8_SRGB);
    ASSERT_EQ(picked.color_space, VK_PROBE_COLORSPACE_SRGB_NONLINEAR);
}

TEST(feature_bits_compose_rhi_feature_values) {
    ASSERT_EQ(vk_probe_feature_bits(false, false, false), 0u);
    ASSERT_EQ(vk_probe_feature_bits(true, false, false),
              VK_PROBE_FEATURE_ACCELERATION_STRUCTURE);
    ASSERT_EQ(vk_probe_feature_bits(true, true, true),
              VK_PROBE_FEATURE_ACCELERATION_STRUCTURE |
              VK_PROBE_FEATURE_RAY_TRACING_PIPELINE |
              VK_PROBE_FEATURE_RAY_QUERY);
}

TEST_MAIN_BEGIN()
    RUN_TEST(adapter_score_orders_discrete_over_integrated_over_software);
    RUN_TEST(adapter_unsuitable_scores_negative_and_never_selected);
    RUN_TEST(adapter_tie_breaks_on_api_version_then_lowest_index);
    RUN_TEST(queue_families_prefer_combined_graphics_present);
    RUN_TEST(queue_families_split_when_no_combined);
    RUN_TEST(present_mode_vsync_prefers_mailbox_then_relaxed_then_fifo);
    RUN_TEST(present_mode_no_vsync_prefers_immediate);
    RUN_TEST(surface_format_prefers_bgra_srgb_then_rgba_srgb_then_first);
    RUN_TEST(surface_format_undefined_sentinel_means_any);
    RUN_TEST(feature_bits_compose_rhi_feature_values);
TEST_MAIN_END()
```

按模板注册（headless;platform_contract）。

- [ ] **Step 2: 验证失败** — 重新配置后 `cmake --build build-vk --target test_rhi_vk_probe --parallel` → 预期编译失败：`rhi/rhi_vk_probe.h: No such file or directory`。

- [ ] **Step 3: 最小实现（头文件）** — 创建 `engine/src/rhi/rhi_vk_probe.h`（内容见 Interfaces）。`cmake --build build-vk --target test_rhi_vk_probe --parallel && ctest --test-dir build-vk -R test_rhi_vk_probe --output-on-failure` → PASS。

- [ ] **Step 4: 接线 rhi_vk.c** —
  ① `#include <rhi/rhi_vk_probe.h>` 随 `:19-20` 的 include 组加入；
  ② include 组之后加常量钉死：

```c
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU == (int)VK_PROBE_DEVICE_TYPE_DISCRETE, "vk probe constant drift");
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU == (int)VK_PROBE_DEVICE_TYPE_INTEGRATED, "vk probe constant drift");
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU == (int)VK_PROBE_DEVICE_TYPE_VIRTUAL, "vk probe constant drift");
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_CPU == (int)VK_PROBE_DEVICE_TYPE_CPU, "vk probe constant drift");
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_OTHER == (int)VK_PROBE_DEVICE_TYPE_OTHER, "vk probe constant drift");
_Static_assert(VK_QUEUE_GRAPHICS_BIT == (int)VK_PROBE_QUEUE_GRAPHICS_BIT, "vk probe constant drift");
_Static_assert(VK_PRESENT_MODE_IMMEDIATE_KHR == (int)VK_PROBE_PRESENT_MODE_IMMEDIATE, "vk probe constant drift");
_Static_assert(VK_PRESENT_MODE_MAILBOX_KHR == (int)VK_PROBE_PRESENT_MODE_MAILBOX, "vk probe constant drift");
_Static_assert(VK_PRESENT_MODE_FIFO_KHR == (int)VK_PROBE_PRESENT_MODE_FIFO, "vk probe constant drift");
_Static_assert(VK_PRESENT_MODE_FIFO_RELAXED_KHR == (int)VK_PROBE_PRESENT_MODE_FIFO_RELAXED, "vk probe constant drift");
_Static_assert(VK_FORMAT_B8G8R8A8_SRGB == (int)VK_PROBE_FORMAT_B8G8R8A8_SRGB, "vk probe constant drift");
_Static_assert(VK_FORMAT_R8G8B8A8_SRGB == (int)VK_PROBE_FORMAT_R8G8B8A8_SRGB, "vk probe constant drift");
_Static_assert(VK_FORMAT_B8G8R8A8_UNORM == (int)VK_PROBE_FORMAT_B8G8R8A8_UNORM, "vk probe constant drift");
_Static_assert(VK_FORMAT_UNDEFINED == (int)VK_PROBE_FORMAT_UNDEFINED, "vk probe constant drift");
_Static_assert(VK_COLOR_SPACE_SRGB_NONLINEAR_KHR == (int)VK_PROBE_COLORSPACE_SRGB_NONLINEAR, "vk probe constant drift");
_Static_assert(RHI_FEATURE_RAY_TRACING_PIPELINE == VK_PROBE_FEATURE_RAY_TRACING_PIPELINE, "vk probe constant drift");
_Static_assert(RHI_FEATURE_RAY_QUERY == VK_PROBE_FEATURE_RAY_QUERY, "vk probe constant drift");
_Static_assert(RHI_FEATURE_ACCELERATION_STRUCTURE == VK_PROBE_FEATURE_ACCELERATION_STRUCTURE, "vk probe constant drift");
```

  ③ adapter 选择：:1758-1778 的两个循环替换为——枚举时填 `VkProbeAdapterInfo *probes = calloc(gpu_count, sizeof(*probes))`（`device_type` 来自 `vkGetPhysicalDeviceProperties`，`api_version` 同源，`suitable` 来自 `vk_physical_device_suitable(gpus[i], vk->surface)`），`i32 picked = vk_probe_select_adapter(probes, gpu_count);` 非负则 `vk->physical = gpus[picked]`，`RE_VK_DEVICE_INDEX` 覆盖块（:1736-1757）保持不变；
  ④ queue family：:1841-1856 的选择循环替换为——先把 `queues[i].queueFlags` 拷入 `u32 *flags`、把 `vkGetPhysicalDeviceSurfaceSupportKHR` 结果拷入 `bool *present`，再 `vk_probe_choose_queue_families(flags, present, queue_count, &vk->graphics_family, &vk->present_family)`，失败走既有 :1858-1862 的 FATAL 路径（注意 :1848-1853 的查询失败路径保留：查询循环先行填充数组，查询失败即清理返回）；
  ⑤ surface format：:1069-1095 的选择逻辑替换为——把 `formats` 拷入 `VkProbeSurfaceFormat *probe_formats`（每元素 `.format = (u32)formats[i].format; .color_space = (u32)formats[i].colorSpace;`），`vk_probe_choose_surface_format(...)` 成功后 `vk->swap_format = (VkFormat)picked.format; swap_colorspace = (VkColorSpaceKHR)picked.color_space;`，`vk->swap_bgra` 的判定行（:1094）不变；
  ⑥ present mode：:1151-1168 的选择逻辑替换为——把 `modes` 拷入 `u32 *probe_modes`，`present_mode = (VkPresentModeKHR)vk_probe_choose_present_mode(probe_modes, mode_count, vk->vsync);`；
  ⑦ feature 探测：:1829 `feat_ray_query` 赋值之后追加：

```c
    /* 迁移期只探测不消费：dynamic rendering / synchronization2。 */
    dev->capabilities.dynamic_rendering_supported =
        VK_API_VERSION_MAJOR(vk->device_props.apiVersion) > 1u ||
        (VK_API_VERSION_MAJOR(vk->device_props.apiVersion) == 1u &&
         VK_API_VERSION_MINOR(vk->device_props.apiVersion) >= 3u) ||
        vk_device_extension_present(vk->physical, VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME);
    dev->capabilities.synchronization2_supported =
        VK_API_VERSION_MAJOR(vk->device_props.apiVersion) > 1u ||
        (VK_API_VERSION_MAJOR(vk->device_props.apiVersion) == 1u &&
         VK_API_VERSION_MINOR(vk->device_props.apiVersion) >= 3u) ||
        vk_device_extension_present(vk->physical, VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME);
```

  ⑧ `rhi.h` 的 `RHICapabilities` 追加（内容见 Interfaces）；`rhi_gl.c` 的设备初始化处（`rhi_device_create` :1238 所在的 backend_data 设置段）给两个新字段显式置 `false`（GL 无对应概念）。

- [ ] **Step 5: 验证通过** — `cmake --build build-vk --parallel`；`ctest --test-dir build-vk -R "test_rhi_vk_probe|test_rhi_capabilities" --output-on-failure` → PASS；headless 全套全绿；`ctest --test-dir build-vk -L graphics --output-on-failure` 全绿（真 GPU：adapter/format/present-mode 协商路径回归——日志行 `VK: swapchain present mode=...` 与 `Vulkan GPU: ...` 应与迁移前一致，记录两行输出到 commit 说明）。GL 配置全绿。

- [ ] **Step 6: Commit**

```bash
git status --short
git add engine/src/rhi/rhi_vk_probe.h engine/src/rhi/rhi.h \
        engine/src/rhi/rhi_vk.c engine/src/rhi/rhi_gl.c \
        engine/tests/test_rhi_vk_probe.c engine/CMakeLists.txt
git commit -m "Extract Vulkan adapter/queue/format/present-mode/feature probing into testable pure functions"
```

---

## Task 5: 故障注入测试（out-of-date / device lost / surface loss / allocation failure）

**Files:**
- Create: `engine/src/rhi/rhi_result_map.h`（VkResult→RHIResult 纯映射，static inline，不含 Vulkan 头）
- Test: `engine/tests/test_rhi_fault_injection.c`（headless，`ENGINE_RHI_TEST` 注入钩子驱动）
- Test: `engine/tests/test_rhi_vk_alloc_fault.c`（graphics lane，真分配故障注入）
- Modify: `engine/src/rhi/rhi.h`（:841 `rhi_vk_validation_set_enabled` 声明之后追加 `rhi_vk_set_alloc_failure_for_test`）
- Modify: `engine/src/rhi/rhi_vk.c`（`vk_lifecycle_result` :504-509 改经映射头；`vk_allocate_memory` :698-703 加注入钩子）
- Modify: `engine/CMakeLists.txt`（两个测试注册）

**Interfaces:**
- Consumes: `RHIResult`（`rhi.h:338-349`）、`rhi_test_set_lifecycle_result`/`rhi_test_set_device_status`（`rhi.h:861-864`，实现 `rhi.c:372-379`）、`rhi_test_device_create`/`rhi_test_device_destroy`（`rhi.c:362-387`）、`platform_wsi_swapchain_*`（`platform_wsi.h:104-205`）。
- Produces（`rhi_result_map.h`，完整内容）：

```c
#pragma once
#include <rhi/rhi.h>

/* VkResult 数值常量（避免纯逻辑层包含 <vulkan/vulkan.h>）：
 * VK_ERROR_OUT_OF_HOST_MEMORY = -1，VK_ERROR_OUT_OF_DEVICE_MEMORY = -2，
 * VK_ERROR_DEVICE_LOST = -4，VK_ERROR_SURFACE_LOST_KHR = -1000000000，
 * VK_ERROR_OUT_OF_DATE_KHR = -1000072004。
 * 由 rhi_vk.c 的 _Static_assert 组钉死。映射锁定既有语义
 *（rhi_vk.c:504-509）：其余一切（含 OOM）归 SYNC_FAILED。 */
static inline RHIResult rhi_vk_result_to_lifecycle(i32 vk_result) {
    if (vk_result == -4) return RHI_RESULT_DEVICE_LOST;
    if (vk_result == -1000072004) return RHI_RESULT_OUT_OF_DATE;
    if (vk_result == -1000000000) return RHI_RESULT_SURFACE_LOST;
    return RHI_RESULT_SYNC_FAILED;
}
```

- Produces（`rhi.h` 追加，注释连同声明）：

```c
/* 测试专用分配故障注入（恒编译、默认关闭；与 rhi_vk_validation_* 同先例——
 * 符号只由 VK 后端定义，调用点必须 #ifdef ENGINE_VULKAN）。开启后
 * vk_allocate_memory 不调用 vkAllocateMemory，直接返回
 * VK_ERROR_OUT_OF_HOST_MEMORY。 */
void rhi_vk_set_alloc_failure_for_test(bool enable);
```

- Produces（`rhi_vk.c` 修改）：

```c
static RHIResult vk_lifecycle_result(VkResult result) {
    return rhi_vk_result_to_lifecycle((i32)result);
}
```

```c
static bool g_vk_test_alloc_failure = false;
void rhi_vk_set_alloc_failure_for_test(bool enable) {
    g_vk_test_alloc_failure = enable;
}

static VkResult vk_allocate_memory(VKBackend *vk, VkMemoryAllocateInfo *info,
                                   VkDeviceMemory *out_memory) {
    if (g_vk_test_alloc_failure) return VK_ERROR_OUT_OF_HOST_MEMORY;
    if (!vk || !info || !out_memory || info->memoryTypeIndex == UINT32_MAX)
        return VK_ERROR_INITIALIZATION_FAILED;
    return vkAllocateMemory(vk->device, info, NULL, out_memory);
}
```

- [ ] **Step 1: 写失败测试** — ① 创建 `engine/tests/test_rhi_fault_injection.c`（注册镜像 `test_rhi_capabilities` 的完整注册块 `engine/CMakeLists.txt:1824-1880`，只换目标名/源文件名；LABELS `headless;platform_contract` 保留）：

```c
#include "test_framework.h"
#include "rhi/rhi.h"
#include "rhi/rhi_result_map.h"
#include "platform/platform_wsi.h"

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);
extern void rhi_test_set_lifecycle_result(RHIDevice *dev, RHIResult result);
extern void rhi_test_set_device_status(RHIDevice *dev, RHIDeviceStatus status);

TEST(vk_result_map_locks_lifecycle_mapping) {
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-4), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-1000072004), RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-1000000000), RHI_RESULT_SURFACE_LOST);
    /* 锁定：OOM 与其余一切归 SYNC_FAILED（不改既有语义）。 */
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-1), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-2), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_vk_result_to_lifecycle(1), RHI_RESULT_SYNC_FAILED);
}

TEST(out_of_date_fails_frame_entrypoints_fast) {
    RHIDevice *dev = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;
    ASSERT_NEQ(dev, NULL);
    rhi_test_set_lifecycle_result(dev, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_frame_begin_ex(dev, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_device_idle_ex(dev), RHI_RESULT_OUT_OF_DATE);
    rhi_test_device_destroy(dev);
}

TEST(device_lost_fails_all_lifecycle_entrypoints_fast) {
    RHIDevice *dev = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;
    ASSERT_NEQ(dev, NULL);
    rhi_test_set_device_status(dev, RHI_DEVICE_STATUS_LOST);
    ASSERT_EQ(rhi_frame_begin_ex(dev, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_resize_ex(dev, 64u, 64u), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_idle_ex(dev), RHI_RESULT_DEVICE_LOST);
    rhi_test_device_destroy(dev);
}

TEST(surface_lost_propagates_through_frame_begin) {
    RHIDevice *dev = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;
    ASSERT_NEQ(dev, NULL);
    rhi_test_set_lifecycle_result(dev, RHI_RESULT_SURFACE_LOST);
    ASSERT_EQ(rhi_frame_begin_ex(dev, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_SURFACE_LOST);
    rhi_test_device_destroy(dev);
}

TEST(lifecycle_injection_is_scoped_to_one_device) {
    RHIDevice *dev = rhi_test_device_create();
    RHIDevice *other = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;
    ASSERT_NEQ(dev, NULL);
    ASSERT_NEQ(other, NULL);
    rhi_test_set_lifecycle_result(dev, RHI_RESULT_OUT_OF_DATE);
    /* 未注入的设备不受影响：backend_data == NULL → UNAVAILABLE（既有语义）。 */
    ASSERT_EQ(rhi_frame_begin_ex(other, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    rhi_test_device_destroy(dev);
    rhi_test_device_destroy(other);
}

TEST(swapchain_generation_retires_backbuffers_on_resize) {
    PlatformWsiSwapchain swapchain;
    PlatformWsiBackBuffer buffer;
    PlatformWsiBackBuffer stale;
    ASSERT_EQ(platform_wsi_swapchain_init(&swapchain, PLATFORM_WSI_QUEUE_DIRECT,
                                          true, false, false, 2u,
                                          100u, 100u, 100u, 100u),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_begin_frame(&swapchain, &buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_present(&swapchain, &buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_ready(&swapchain), PLATFORM_WSI_OK);
    stale = buffer;
    ASSERT_EQ(platform_wsi_swapchain_resize(&swapchain, 200u, 200u, 200u, 200u),
              PLATFORM_WSI_OK);
    /* out-of-date 的 back buffer（旧 generation）不得再进入渲染/present。 */
    ASSERT_EQ(platform_wsi_swapchain_present(&swapchain, &stale),
              PLATFORM_WSI_INVALID_TRANSITION);
    ASSERT_EQ(platform_wsi_swapchain_begin_frame(&swapchain, &buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(buffer.generation, 2u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(vk_result_map_locks_lifecycle_mapping);
    RUN_TEST(out_of_date_fails_frame_entrypoints_fast);
    RUN_TEST(device_lost_fails_all_lifecycle_entrypoints_fast);
    RUN_TEST(surface_lost_propagates_through_frame_begin);
    RUN_TEST(lifecycle_injection_is_scoped_to_one_device);
    RUN_TEST(swapchain_generation_retires_backbuffers_on_resize);
TEST_MAIN_END()
```

  ② 创建 `engine/tests/test_rhi_vk_alloc_fault.c`（graphics lane）：

```c
/* 真 GPU 分配故障注入：rhi_vk_set_alloc_failure_for_test 使
 * vk_allocate_memory 直接失败。无 Vulkan 构建或无可建窗口/GPU 的环境
 * return 77（注册处 SKIP_RETURN_CODE 77 → CTest 记为跳过而非通过）。 */
#include "test_framework.h"
#include "engine.h"
#include "rhi/rhi.h"
#include "platform/platform.h"
#include <stdlib.h>

int main(void) {
#ifndef ENGINE_VULKAN
    return 77;
#else
    PlatformConfig cfg = { 640u, 480u, "rhi-alloc-fault", NULL, NULL };
    Platform *platform = platform_create(&cfg);
    RHIDevice *dev;
    RHITextureDesc desc = { 256u, 256u, RHI_FORMAT_R8G8B8A8_UNORM, 1u, NULL };
    RHITexture tex;
    RHITexture recovered;
    u32 w = 0u, h = 0u;
    if (platform == NULL) return 77;
    platform_get_drawable_size(platform, &w, &h);
    dev = rhi_device_create(RHI_BACKEND_VULKAN, platform_surface_native(platform),
                            platform_display_native(platform), w, h);
    if (dev == NULL) { platform_destroy(platform); return 77; }

    rhi_vk_set_alloc_failure_for_test(true);
    tex = rhi_texture_create(dev, &desc);
    rhi_vk_set_alloc_failure_for_test(false);
    if (rhi_handle_valid(tex)) {
        /* 注入后仍成功 = 钩子失效 */
        rhi_texture_destroy(dev, tex);
        rhi_device_destroy(dev);
        platform_destroy(platform);
        return 1;
    }
    recovered = rhi_texture_create(dev, &desc);
    if (!rhi_handle_valid(recovered)) {
        /* 关闭注入后必须恢复——故障不得毒化设备 */
        rhi_device_destroy(dev);
        platform_destroy(platform);
        return 1;
    }
    rhi_texture_destroy(dev, recovered);
    rhi_device_destroy(dev);
    platform_destroy(platform);
    return 0;
#endif
}
```

注册（仅 Vulkan 配置；`ENGINE_VULKAN` 经 engine target 的 PUBLIC 定义传播，:984/:1015）：

```cmake
if(ENGINE_VULKAN)
    add_executable(test_rhi_vk_alloc_fault tests/test_rhi_vk_alloc_fault.c)
    target_include_directories(test_rhi_vk_alloc_fault PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rhi_vk_alloc_fault PRIVATE engine m)
    add_test(NAME test_rhi_vk_alloc_fault COMMAND test_rhi_vk_alloc_fault)
    set_tests_properties(test_rhi_vk_alloc_fault PROPERTIES
        LABELS graphics SKIP_RETURN_CODE 77 TIMEOUT 60)
endif()
```

- [ ] **Step 2: 验证失败** — 重新配置后 `cmake --build build-vk --target test_rhi_fault_injection --parallel` → 预期编译失败：`rhi/rhi_result_map.h: No such file or directory`。`cmake --build build-vk --target test_rhi_vk_alloc_fault --parallel` → 预期链接失败：`rhi_vk_set_alloc_failure_for_test` 未定义。

- [ ] **Step 3: 最小实现** — 创建 `rhi_result_map.h`；`rhi_vk.c` 改 `vk_lifecycle_result`、加钩子（内容见 Interfaces），并在 include 组后追加 VkResult 常量钉死：

```c
_Static_assert(VK_ERROR_DEVICE_LOST == -4, "vk result constant drift");
_Static_assert(VK_ERROR_OUT_OF_DATE_KHR == -1000072004, "vk result constant drift");
_Static_assert(VK_ERROR_SURFACE_LOST_KHR == -1000000000, "vk result constant drift");
```

- [ ] **Step 4: 验证通过** — `ctest --test-dir build-vk -R "test_rhi_fault_injection" --output-on-failure` → PASS；`ctest --test-dir build-vk -R "test_rhi_vk_alloc_fault" --output-on-failure` → PASS（本机真 GPU；记录输出）；headless 全套全绿；`ctest --test-dir build-vk -L graphics --output-on-failure` 全绿。GL 配置：`test_rhi_fault_injection` 在 build-gl 同步注册并通过（它不依赖 VK 符号——`rhi_result_map.h` 是纯映射）。

- [ ] **Step 5: Commit**

```bash
git status --short
git add engine/src/rhi/rhi_result_map.h engine/src/rhi/rhi.h \
        engine/src/rhi/rhi_vk.c \
        engine/tests/test_rhi_fault_injection.c \
        engine/tests/test_rhi_vk_alloc_fault.c \
        engine/CMakeLists.txt
git commit -m "Add fault-injection coverage for out-of-date, device lost, surface loss, allocation failure"
```

---

## Task 6: 保留隔离测试（TV_ONLY_PSHADOW / TV_ONLY_GBUFFER 契约钉死）

**Files:**
- Test: `engine/tests/test_vulkan_isolation_gates.cmake`（cmake -P 契约）
- Modify: `engine/CMakeLists.txt`（注册）
- Modify: `docs/vulkan_support_matrix.md`（追加风险节，内容见 Steps；骨架由计划 A 创建）

**Interfaces:**
- Consumes: `engine/src/test_vulkan.c:5600-5616`（`TV_ONLY_PSHADOW`，getenv 在 :5606）、:5618-5642（`TV_ONLY_GBUFFER`，getenv 在 :5626）；CMake 引用面 `engine/CMakeLists.txt`；CI 引用面 `.github/workflows/ci.yml`。
- Produces: 无新 API。本 Task 是防回归守卫——`test_vulkan.c` 一行不改。

- [ ] **Step 1: 写契约测试** — 创建 `engine/tests/test_vulkan_isolation_gates.cmake`：

```cmake
foreach(required_var TEST_VULKAN_SOURCE ENGINE_CMAKE CI_WORKFLOW)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

file(READ "${TEST_VULKAN_SOURCE}" tv_text)
# 两个隔离门必须都在（R588 point-shadow 门 / R580 deferred G-Buffer 门）。
foreach(required_token
        "getenv(\"TV_ONLY_PSHADOW\")" "getenv(\"TV_ONLY_GBUFFER\")"
        "R588" "R580")
    string(FIND "${tv_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR
            "test_vulkan.c isolation gate missing: ${required_token}")
    endif()
endforeach()
# 隔离门必须保持「环境变量驱动、仅诊断用途」：CMake 与 CI 一律不得引用
#（一旦被 CI 引用，子集会伪装成全量证据）。
foreach(build_file "${ENGINE_CMAKE}" "${CI_WORKFLOW}")
    file(READ "${build_file}" build_text)
    string(FIND "${build_text}" "TV_ONLY" tv_offset)
    if(NOT tv_offset EQUAL -1)
        message(FATAL_ERROR
            "TV_ONLY_* isolation gates must not be referenced by build/CI files: ${build_file}")
    endif()
endforeach()
```

注册（模板见「构建 / 测试命令」节；输入 `-DTEST_VULKAN_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/test_vulkan.c -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt -DCI_WORKFLOW=${CMAKE_CURRENT_SOURCE_DIR}/../.github/workflows/ci.yml`）。

- [ ] **Step 2: 验证失败（证明守卫有效）** — 该测试是保留性契约，创建即绿；用错误输入证明它能红：

```bash
cmake -DTEST_VULKAN_SOURCE=engine/src/rhi/rhi_vk.c \
      -DENGINE_CMAKE=engine/CMakeLists.txt \
      -DCI_WORKFLOW=.github/workflows/ci.yml \
      -P engine/tests/test_vulkan_isolation_gates.cmake
```

预期非零退出，信息 `test_vulkan.c isolation gate missing: getenv("TV_ONLY_PSHADOW")`。再 `ctest --test-dir build-vk -R test_vulkan_isolation_gates --output-on-failure` → PASS。

- [ ] **Step 3: 风险节落档** — 在 `docs/vulkan_support_matrix.md` 追加「已知风险：NVIDIA 616.56 混合 GPU」节，固定两条规则（与规格 §7 一致）：① 该机器上的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1} 异常不作为源码修复依据，必须在健康设备独立复现后才立项；② `TV_ONLY_PSHADOW`/`TV_ONLY_GBUFFER` 隔离门（`engine/src/test_vulkan.c:5600-5642`）永久保留，不得删除或并入 CI。

- [ ] **Step 4: Commit**

```bash
git status --short
git add engine/tests/test_vulkan_isolation_gates.cmake engine/CMakeLists.txt \
        docs/vulkan_support_matrix.md
git commit -m "Pin the TV_ONLY_PSHADOW/TV_ONLY_GBUFFER isolation gates with a contract test"
```

---

## Task 7: Steam Deck / Linux Steam 验证 lane（CI + benchmark receipt）

**Files:**
- Create: `engine/tools/rhi_swapchain_bench.c`（swapchain 帧基准 + receipt 产出）
- Create: `engine/tests/test_rhi_benchmark_receipt_validate.cmake`（receipt 键检查脚本，CI 直接调用，不注册为 CTest）
- Modify: `engine/CMakeLists.txt`（注册 bench 目标 + CTest 项）
- Modify: `.github/workflows/ci.yml`（新增自托管真 GPU job）

**Interfaces:**
- Consumes: `platform_create`/`platform_get_drawable_size`（`platform.h:97,118`）、`rhi_device_create`/`rhi_frame_begin`/`rhi_cmd_clear_color`/`rhi_frame_end`/`rhi_present`/`rhi_device_get_info`（`rhi.h:353,455,562,461,464,361`）、benchmark receipt schema（`docs/rhi_benchmark_receipt_schema.md`，计划 A 创建，字段清单见规格 §8.3）。
- Produces:
  - `rhi_swapchain_bench <out.json>`：建 640x480 窗口与 RHI 设备（`#ifdef ENGINE_VULKAN` → `RHI_BACKEND_VULKAN`），渲染 600 帧 clear（每帧 `frame_begin → clear_color → frame_end → present`），用 C11 `timespec_get(TIME_UTC)` 逐帧计时，产出 receipt JSON。环境探测失败（无窗口系统/无 GPU）时 `return 77`。
  - receipt 字段（与 schema 对齐）：`schema_version=1`、`timestamp`（UTC ISO-8601）、`platform`、`os_version`、`backend`、`gpu`、`driver_version`、`cpu`、`ram`、`build_commit`、`build_config`、`command`、`metrics{fps_avg,fps_p1,frame_ms_avg,frame_ms_p99}`、`evidence_level`、`runner`。本机不可知的字段（os_version/cpu/ram/build_commit/runner）取自环境变量 `RECEIPT_OS_VERSION`/`RECEIPT_CPU`/`RECEIPT_RAM`/`GIT_COMMIT`/`RECEIPT_RUNNER`，缺省写 `"unknown"`；`gpu`/`driver_version` 来自 `RHIDeviceInfo`（`rhi.h:127-135`）；`fps_p1` 定义为 `1000.0 / frame_ms_p99`。
  - `evidence_level`：真 GPU 运行写 `"gpu-runtime"`；runner 名为 `steam-deck*` 时可由台账维护者升级为 `benchmark-comparable`（升级动作在 `docs/rhi_backend_evidence.md`，不是本工具的判断）。

- [ ] **Step 1: 写 bench 工具** — 创建 `engine/tools/rhi_swapchain_bench.c`（要点骨架，完整实现按此结构展开）：

```c
#include "engine.h"
#include "rhi/rhi.h"
#include "platform/platform.h"
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BENCH_FRAMES 600

static f64 now_ms(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (f64)ts.tv_sec * 1000.0 + (f64)ts.tv_nsec / 1.0e6;
}

static const char *env_or(const char *name, const char *fallback) {
    const char *v = getenv(name);
    return (v != NULL && v[0] != '\0') ? v : fallback;
}

static int cmp_f64(const void *a, const void *b) {
    f64 fa = *(const f64 *)a, fb = *(const f64 *)b;
    return (fa > fb) - (fa < fb);
}

int main(int argc, char **argv) {
    PlatformConfig cfg = { 640u, 480u, "rhi-swapchain-bench", NULL, NULL };
    static f64 frame_ms[BENCH_FRAMES];
    Platform *platform;
    RHIDevice *dev;
    RHIDeviceInfo info;
    u32 w = 0u, h = 0u, i;
    f64 sum, avg_ms, p99_ms, fps_avg;
    FILE *out;
    if (argc < 2) return 2;
    platform = platform_create(&cfg);
    if (platform == NULL) return 77;
    platform_get_drawable_size(platform, &w, &h);
#ifdef ENGINE_VULKAN
    dev = rhi_device_create(RHI_BACKEND_VULKAN, platform_surface_native(platform),
                            platform_display_native(platform), w, h);
#else
    dev = rhi_device_create(RHI_BACKEND_OPENGL, platform_window_native(platform),
                            platform_display_native(platform), w, h);
#endif
    if (dev == NULL) { platform_destroy(platform); return 77; }
    rhi_set_vsync(dev, false);
    memset(&info, 0, sizeof(info));
    (void)rhi_device_get_info(dev, &info);
    for (i = 0; i < BENCH_FRAMES; i++) {
        f64 t0 = now_ms();
        RHICmdBuffer *cmd = rhi_frame_begin(dev);
        if (cmd == NULL) { rhi_device_destroy(dev); platform_destroy(platform); return 1; }
        rhi_cmd_clear_color(cmd, 0.1f, 0.2f, 0.3f, 1.0f);
        rhi_frame_end(dev);
        rhi_present(dev);
        frame_ms[i] = now_ms() - t0;
    }
    qsort(frame_ms, BENCH_FRAMES, sizeof(frame_ms[0]), cmp_f64);
    sum = 0.0;
    for (i = 0; i < BENCH_FRAMES; i++) sum += frame_ms[i];
    avg_ms = sum / (f64)BENCH_FRAMES;
    p99_ms = frame_ms[(BENCH_FRAMES * 99u) / 100u];
    fps_avg = avg_ms > 0.0 ? 1000.0 / avg_ms : 0.0;
    out = fopen(argv[1], "wb");
    if (out == NULL) { rhi_device_destroy(dev); platform_destroy(platform); return 1; }
    /* timestamp 由 CI step 注入环境变量 RECEIPT_TIMESTAMP（date -u +%FT%TZ），
     * 避免在 C 里手写时间格式化。 */
    fprintf(out,
        "{\n"
        "  \"schema_version\": 1,\n"
        "  \"timestamp\": \"%s\",\n"
        "  \"platform\": \"%s\",\n"
        "  \"os_version\": \"%s\",\n"
        "  \"backend\": \"%s\",\n"
        "  \"gpu\": \"%s\",\n"
        "  \"driver_version\": \"%u\",\n"
        "  \"cpu\": \"%s\",\n"
        "  \"ram\": \"%s\",\n"
        "  \"build_commit\": \"%s\",\n"
        "  \"build_config\": \"%s\",\n"
        "  \"command\": \"rhi_swapchain_bench\",\n"
        "  \"metrics\": { \"fps_avg\": %.2f, \"fps_p1\": %.2f,\n"
        "    \"frame_ms_avg\": %.4f, \"frame_ms_p99\": %.4f },\n"
        "  \"evidence_level\": \"gpu-runtime\",\n"
        "  \"runner\": \"%s\"\n"
        "}\n",
        env_or("RECEIPT_TIMESTAMP", "unknown"),
#ifdef ENGINE_PLATFORM_WINDOWS
        "windows",
#elif defined(ENGINE_PLATFORM_LINUX)
        "linux",
#elif defined(ENGINE_PLATFORM_MACOS)
        "macos",
#else
        "unknown",
#endif
        env_or("RECEIPT_OS_VERSION", "unknown"),
#ifdef ENGINE_VULKAN
        "vulkan",
#else
        "opengl",
#endif
        info.device_name, info.driver_version,
        env_or("RECEIPT_CPU", "unknown"), env_or("RECEIPT_RAM", "unknown"),
        env_or("GIT_COMMIT", "unknown"), env_or("RECEIPT_BUILD_CONFIG", "unknown"),
        fps_avg, p99_ms > 0.0 ? 1000.0 / p99_ms : 0.0, avg_ms, p99_ms,
        env_or("RECEIPT_RUNNER", "local"));
    fclose(out);
    rhi_device_destroy(dev);
    platform_destroy(platform);
    LOG_INFO("receipt written: %s (fps_avg=%.1f frame_ms_p99=%.3f)",
             argv[1], fps_avg, p99_ms);
    return 0;
}
```

创建 `engine/tests/test_rhi_benchmark_receipt_validate.cmake`：

```cmake
if(NOT DEFINED RECEIPT)
    message(FATAL_ERROR "RECEIPT is required")
endif()
if(NOT EXISTS "${RECEIPT}")
    message(FATAL_ERROR "receipt missing: ${RECEIPT}")
endif()
file(READ "${RECEIPT}" receipt_text)
# 键存在性检查（不是 JSON 解析器；字段级校验以
# docs/rhi_benchmark_receipt_schema.md 的校验脚本为准，本检查是 CI 烟雾门）。
foreach(required_key
        "\"schema_version\"" "\"timestamp\"" "\"platform\"" "\"os_version\""
        "\"backend\"" "\"gpu\"" "\"driver_version\"" "\"cpu\"" "\"ram\""
        "\"build_commit\"" "\"build_config\"" "\"command\"" "\"metrics\""
        "\"fps_avg\"" "\"fps_p1\"" "\"frame_ms_avg\"" "\"frame_ms_p99\""
        "\"evidence_level\"" "\"runner\"")
    string(FIND "${receipt_text}" "${required_key}" key_offset)
    if(key_offset EQUAL -1)
        message(FATAL_ERROR "receipt missing key: ${required_key}")
    endif()
endforeach()
```

注册（紧随 `test_vulkan` 注册块 :2316-2318 之后）：

```cmake
add_executable(rhi_swapchain_bench tools/rhi_swapchain_bench.c)
target_include_directories(rhi_swapchain_bench PRIVATE ${TEST_INCLUDE_DIRS})
target_link_libraries(rhi_swapchain_bench PRIVATE engine m)
add_test(NAME rhi_swapchain_bench
    COMMAND rhi_swapchain_bench ${CMAKE_CURRENT_BINARY_DIR}/rhi_receipt_local.json)
set_tests_properties(rhi_swapchain_bench PROPERTIES
    LABELS "graphics;benchmark" SKIP_RETURN_CODE 77 TIMEOUT 120)
```

- [ ] **Step 2: 本机验证** — `cmake --build build-vk --target rhi_swapchain_bench --parallel && ctest --test-dir build-vk -R rhi_swapchain_bench --output-on-failure` → PASS（真 GPU）并产出 `build-vk/rhi_receipt_local.json`；`cmake -DRECEIPT=build-vk/rhi_receipt_local.json -P engine/tests/test_rhi_benchmark_receipt_validate.cmake` → 零退出。

- [ ] **Step 3: 新增 CI job** — 在 `.github/workflows/ci.yml` 的 `macos-vulkan` job（:443-559）之后追加：

```yaml
  steam-deck-vulkan-benchmark:
    name: Steam Deck / Linux real-GPU Vulkan benchmark
    # 真 GPU 自托管 lane：用仓库变量 ENABLE_GPU_LANES=1 显式开启；
    # GitHub-hosted 运行器上没有 self-hosted 标签可接单，不加 if 会永久 pending。
    if: vars.ENABLE_GPU_LANES == '1'
    runs-on: [self-hosted, linux, gpu-vulkan]
    timeout-minutes: 30
    steps:
      - uses: actions/checkout@v4

      - name: Install dependencies
        run: |
          sudo apt-get update
          sudo apt-get install -y --no-install-recommends \
            build-essential cmake ninja-build libx11-dev libxrandr-dev \
            libvulkan-dev libshaderc-dev libfreetype6-dev fonts-noto-cjk

      - name: Configure
        run: cmake -S engine -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENGINE_VULKAN=ON

      - name: Build
        run: cmake --build build --parallel

      - name: Graphics suite (GPU-runtime evidence)
        run: ctest --test-dir build -L graphics --output-on-failure

      - name: Benchmark receipt
        env:
          RECEIPT_RUNNER: ${{ runner.name }}
          RECEIPT_OS_VERSION: ${{ runner.os }}
          RECEIPT_BUILD_CONFIG: RelWithDebInfo
          GIT_COMMIT: ${{ github.sha }}
        run: |
          # RECEIPT_TIMESTAMP 不能写在 env: 块——那里不会求值 $(...)。
          export RECEIPT_TIMESTAMP="$(date -u +%FT%TZ)"
          set +e
          ./build/rhi_swapchain_bench build/rhi_receipt_steam_deck.json
          rc=$?
          set -e
          # 环境缺显示/GPU 时 bench 以 77 退出：记为 unavailable 证据，不算通过。
          if [ $rc -eq 77 ]; then
            echo "::warning::bench skipped (no display/GPU on this runner) — no receipt produced"
            exit 0
          fi
          test $rc -eq 0
          cmake -DRECEIPT=build/rhi_receipt_steam_deck.json \
            -P engine/tests/test_rhi_benchmark_receipt_validate.cmake

      - name: Upload receipt
        if: always()
        uses: actions/upload-artifact@v4
        with:
          name: rhi-benchmark-receipt
          path: build/rhi_receipt_steam_deck.json
          if-no-files-found: ignore
```

注意：`RECEIPT_TIMESTAMP: $(date ...)` 在 GitHub Actions 的 `env:` 里不会被求值——该环境变量必须移到 run 步骤内 `export RECEIPT_TIMESTAMP="$(date -u +%FT%TZ)"`（写 YAML 时按此修正，勿把 `$(...)` 留在 env 块）。

- [ ] **Step 4: 验证** — `git diff --check`；本地 bash 语法层面用 `bash -n` 不适用 YAML，改用：`ctest --test-dir build-vk -R rhi_swapchain_bench --output-on-failure` 已通过（Step 2）；YAML 结构经 `git diff` 目检与 push 后 CI 的 `gl`/`vk` 既有 lane 不受影响（新 job 默认被 `if:` 关闭）。在 PR/push 页面确认新 job 显示为 skipped 而非 pending。

- [ ] **Step 5: Commit**

```bash
git status --short
git add engine/tools/rhi_swapchain_bench.c \
        engine/tests/test_rhi_benchmark_receipt_validate.cmake \
        engine/CMakeLists.txt .github/workflows/ci.yml
git commit -m "Add Steam Deck/Linux real-GPU Vulkan CI lane with benchmark receipt"
```

---

## Task 8: 文档（支持矩阵 / 构建指南 / 架构总览 / 证据台账）

**Files:**
- Modify: `docs/vulkan_support_matrix.md`（计划 A 骨架，本计划填充数据行）
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Architecture_Overview.md`
- Modify: `docs/rhi_backend_evidence.md`（计划 A 创建的证据台账，追加收据行）

**Interfaces:**
- Consumes: 本机 `test_vulkan` 日志行（`Vulkan GPU: ...`，`rhi_vk.c:1831-1834`；`VK: swapchain present mode=...`，:1172-1176）、`build-vk/rhi_receipt_local.json`（Task 7）、CI run 结果。

- [ ] **Step 1: 填充 `docs/vulkan_support_matrix.md`** — 为每个 lane 各写一行：adapter（device_type 离散/集显/软件 + device_name）、surface format、present mode、`feature_bits`、`dynamic_rendering_supported`、`synchronization2_supported`。数据来源命令（逐 lane 执行后填表，禁止无收据填表）：

```bash
# 本机 Windows 真 GPU（GPU_RUNTIME）
ctest --test-dir build-vk -R test_vulkan --output-on-failure 2>&1 | grep -E "Vulkan GPU|present mode"
# CI vk / linux-graphics-smoke（GPU_RUNTIME，lavapipe 软渲染）：CI 日志同两行
# CI wayland-vk（NATIVE_SURFACE，weston headless）：同上
# macOS MoltenVK（GPU_RUNTIME，CI macos-vulkan）：同上
```

动态特性行在 `test_vulkan` 日志无现成输出——允许只填「探测逻辑存在（test_rhi_vk_probe 全绿）+ 运行值未知」并标 COMPILED 级；或在本机用一次性探针（`rhi_device_get_capabilities` 打印）取值，探针代码不入库（用 `engine/tests/test_rhi_vk_probe.c` 的既有目标加打印即可，取完即还原）。

- [ ] **Step 2: 更新 `docs/Build_Guide.md`** — 新增「WSI / Vulkan surface 分层」节：`platform_vk_surface.h` 两个入口的用途与 uint64/void* 设计理由；`platform_wsi.h` 状态机与 `platform_wsi_frame_allowed`/销毁门控的消费方式；`rhi_swapchain_bench` 用法与 receipt 字段；`ENABLE_GPU_LANES` 仓库变量的开启方式。

- [ ] **Step 3: 更新 `docs/Architecture_Overview.md`** — RHI 分层图加入 PAL WSI adapter 层（`platform_vk_surface`）与 WSI 状态机（`platform_wsi.h` ↔ window_*.c 事件源 ↔ `rhi_device_attach_wsi`/销毁门控），标注「platform 层不包含 Vulkan 头」的分层规则。

- [ ] **Step 4: 更新 `docs/rhi_backend_evidence.md`** — 追加本计划产生的收据行：本机 Windows Vulkan 回归（Task 1/3/4 的 graphics 套件记录）、Task 7 的本地 receipt、`steam-deck-vulkan-benchmark` lane 状态（未开启 ENABLE_GPU_LANES = lane 存在但无运行收据，等级不变）。每条注明日期/机器/命令/结果。

- [ ] **Step 5: Commit**

```bash
git status --short
git add docs/vulkan_support_matrix.md docs/Build_Guide.md \
        docs/Architecture_Overview.md docs/rhi_backend_evidence.md
git commit -m "Document WSI adapter layer, Vulkan support matrix, and evidence receipts"
```

---

## Task 9: 最终验证与 push

**Files:** 无新增（本 Task 只做验证与推送）。

- [ ] **Step 1: 本机双配置全量** —

```bash
cmake -S engine -B build-vk -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=ON
cmake -S engine -B build-gl -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-vk --parallel && cmake --build build-gl --parallel
ctest --test-dir build-vk -LE "graphics|fuzz" --output-on-failure
ctest --test-dir build-gl -LE "graphics|fuzz" --output-on-failure
ctest --test-dir build-vk -L graphics --output-on-failure
```

预期：全部绿。证据等级标注：build-vk graphics = 本机真 GPU 的 GPU_RUNTIME 回归；headless 套件 = HEADLESS 级。

- [ ] **Step 2: 契约面全量** — `ctest --test-dir build-vk -R "platform_vk_surface|platform_size|wsi|rhi_vk_probe|rhi_fault|isolation_gates|rhi_backend_internal_contract" --output-on-failure` → 全绿。

- [ ] **Step 3: Linux X11 + Wayland 双配置（CI 证据）** — 本机无 Linux，经 CI 验证：push 后核对 `vk`（Linux X11 + Vulkan，GPU_RUNTIME/lavapipe）、`linux-graphics-smoke`（同）、`wayland-vk`（NATIVE_SURFACE/weston headless）、`gl`、`wayland-gl`、`windows-clang`、`macos-vulkan` 全绿；任一红则修复后重推，禁止带病推送。
  本地等效命令（有 Linux 机器时，证据等级同上）：

```bash
cmake -S engine -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=ON
cmake --build build --parallel
ctest --test-dir build -LE "graphics|fuzz" --output-on-failure
ctest --test-dir build -L graphics --output-on-failure   # X11（Xvfb + lavapipe）
cmake -S engine -B build-wl -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=ON -DENGINE_ENABLE_WAYLAND=ON
cmake --build build-wl --parallel
ctest --test-dir build-wl -LE "graphics|fuzz" --output-on-failure
ctest --test-dir build-wl -R '^test_platform_wayland_runtime$' --output-on-failure  # weston headless
```

- [ ] **Step 4: 台账收尾** — 确认 `docs/rhi_backend_evidence.md` 的每行等级与收据一致：本计划不得把任何行提升到 GPU_RUNTIME 以上；Steam Deck 的 BENCHMARK_COMPARABLE 只能由真机 receipt 支持。

- [ ] **Step 5: push** —

```bash
git status --short   # 只剩本计划范围外的既有脏文件；冻结清单零命中
git log --oneline origin/master..HEAD
git push origin master
```

- [ ] **Step 6: 汇报** — 推送范围、各 lane 证据等级、Task 1-8 的验证命令与结果、台账新增行、`ENABLE_GPU_LANES` 的后续开启说明。

---

## Self-review notes（计划作者填写）

- **覆盖映射**（任务清单 → 本计划 Task）：1 platform_vk_surface 抽离 → T1；2 WSI 状态机接入 → T3；3 尺寸语义锁定 → T2（helper 先于 T3 落地，因为 T3 的 resize 接线消费它——执行顺序为 T1→T2→T3→T4→T5→T6→T7→T8→T9）；4 探测完善 → T4；5 故障注入 → T5；6 隔离测试保留 → T6；7 Steam Deck lane → T7；8 文档 → T8；9 最终验证+push → T9。
- **类型一致性锚点**：`PlatformWsiSurface`（platform_wsi.h:86-93 已有）被 T3 消费；`platform_wsi_frame_allowed`/`platform_wsi_rhi_teardown_allowed` 在 T3 定义、被 T3 的 rhi.c 门控与 main.c 帧门控消费；`rhi_device_attach_wsi`（T3 定义）被 T5 的 attach 测试消费；`rhi_vk_result_to_lifecycle`（T5 定义）替换 `vk_lifecycle_result` 的函数体；`VkProbe*`（T4 定义）被 T4 的 rhi_vk.c 接线消费；`platform_size_*`（T2 定义）被 T2 的窗口后端改造与 T3 的 resize 接线消费；`platform_vk_create_surface_handles`（T1 定义）被 rhi_vk.c 消费——rhi_vk.c 持有裸句柄而非 `Platform *`，故 T1 同时提供 `Platform *` 入口（规格签名）与 handles 入口（实际消费点），两者同文件同语义。
- **占位符检查**：无 TBD/TODO；每个 Task 含 Files/Interfaces/失败测试/验证命令/实现代码/commit 清单。T3-⑨ 的 `main.c:6050` 帧门控与 T3-⑩ 的 :4343-4348 需要先 Read 确认循环边界——锚点与插入代码均已给出，这属于精确的锚点定位指示而非占位符。
- **行为变更声明**（防止「改名伪装」）：T4-④ queue family 选择从「首个 graphics + 首个 present」改为「combined 优先」——这是有意的语义收紧（swapchain 可走 EXCLUSIVE sharing），lavapipe 上家族 0 双支持故 CI 结果不变；T4-⑤⑥ 的 format/present-mode 是纯函数化平移，优先级与 :1069-1095/:1151-1168 逐条一致并由单测钉死。
- **已知边界**：`platform_vk_surface_vkabi.h` 的 `PVkXlibSurfaceCreateInfo.window` 按 LP64（`Window == unsigned long == u64`）承载，ABI 测试只在 Linux 宿主钉死；32 位 Linux 不在目标矩阵内（规格 §1.1）。myui 自带 Vulkan 路径（`my_vgcanvas_vulkan.c`/`my_pal_vulkan.c`）不经 rhi_vk.c 创建 surface（grep 零命中 `vkCreate*SurfaceKHR`），不在本计划迁移面内。
