# 计划 E：Renderer / Shader ABI 迁移（capability contract 化）实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 把 engine renderer 与 main.c 中对后端分支（`#ifdef ENGINE_VULKAN` / `ENGINE_RHI_BACKEND_*`）和硬编码 uniform 绑定（`rhi_pipeline_get_uniform_location` 共 412 处调用点）迁移为 capability contract + shader reflection 权威绑定，每一步用确定性 readback/golden oracle 验证，为 Metal/D3D12 后端落地扫清 renderer 层障碍。

**Architecture:** 规格 `docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md` §4.4（rhi.h 中性化）、§4.6（capability contract 替代后端分支）、§4.7（shader 策略）的执行计划。核心动作三件：(1) 把 test_vulkan 的 golden-image readback 机器抽象为可复用的 `engine/tests/rhi_oracle.h/.c`，作为全部迁移步骤的确定性对照；(2) 给 `RHICapabilities` 增补 push-constant/Hi-Z/compute/indirect/shader-variant 字段并配契约测试，renderer/main.c 的 `#ifdef ENGINE_VULKAN` 逐点改为 caps 查询；(3) 把 `shader_io.c` 文本 reflection 升级为 push-constant 布局的权威来源，新增 `rhi_pipeline_bindings_create/resolve` API，分批（每批 ≤50 调用点、独立 commit + oracle 验证）迁移全部 412 处 `rhi_pipeline_get_uniform_location` 调用点，旧 API 保留至清零后标记废弃。

**Tech Stack:** C11（`-Werror -pedantic` / `/WX`）、CMake + CTest（labels: `headless`/`graphics`，`SKIP_RETURN_CODE 77`）、GLSL（runtime shaderc → SPIR-V 1.5 / Vulkan 1.2）、Vulkan SDK 1.4.357.0、engine 自带 `engine/tests/test_framework.h` 纯 C 测试框架。

## Global Constraints

- **TDD：** 先写失败测试 → 运行验证失败 → 最小实现（真实代码）→ 运行验证通过 → commit。每个 Task 独立可测、独立 commit。
- **-Werror：** engine 全局警告即错误（MSVC `/W4 /WX`，GNU/Clang `-Wall -Wextra -Werror -pedantic`，engine/CMakeLists.txt:98,107,111）。新增/修改代码必须零警告。
- **冻结文件清单（任何步骤不得修改/删除/移动）：** `.scratch-vkprobe/`、`engine/profile_trace.json`、`.tmp/`、仓库根 `d3d12_shader_gate.hlsl`、`d3d12_shader_gate.dxil`、`.env`、SSH 私钥。
- **deterministic output/readback oracle 纪律：** 每个迁移步骤必须用确定性输出/回读对照验证（本计划 Task 1 的 `rhi_oracle` 或现有 test_vulkan golden/readback gate），**禁止目测**。oracle 场景的确定性前提：固定 drawable 分辨率、`rhi_set_vsync(dev, false)`、`BREAK_JITTER=0`（已有 kill-switch，main.c:5159 附近 Halton(2,3) 16 样本抖动表清零）、固定相机位姿、暖机 3 帧后在 `rhi_frame_end` 与 `rhi_present` 之间捕获（R577 合法窗口）。容差：`MAE ≤ 8.0 && maxd ≤ 56`（沿用 test_vulkan.c:299），几何/格式 roundtrip 类断言要求字节精确。
- **capability contract 纪律：** renderer/main.c 中后端行为差异必须表达为 `RHICapabilities` 查询；**禁止简单改名伪装跨平台**——每个新增 capability 字段必须先有契约测试，且在每个后端有真实消费（spec §4.4/§4.6）。
- **不新增 `RHIResult` 枚举值**（spec §4.2）；错误语义用文档 + 契约测试固定。
- **上下文 70% 压缩交接：** 执行阶段上下文约 70% 时先生成压缩交接，至少包含：当前 Task 与 checkbox 状态；已完成/失败/阻塞测试及命令；已修改与未提交文件清单；当前 commit/branch/remote；平台矩阵及证据等级；未解决风险；下一步精确命令；冻结文件清单复述（spec §9）。
- **行尾：** `engine/src/rhi/*`、`engine/src/main.c`、`engine/src/test_vulkan.c`、`engine/CMakeLists.txt` 为 CRLF；其余多数测试与文档为 LF。编辑保持各文件原行尾。
- **commit 前置核对：** 每个 commit 步骤先 `git status --short` 核对暂存清单不含冻结文件。
- **append-only 头文件约定：** `rhi.h`/`shader_io.h` 只做尾部追加，不改既有签名；`RHICapabilities` 无 `struct_size` 字段，追加字段属源码兼容（非 ABI 稳定承诺，写入头注释）。
- **前置条件（进入本计划前必须全绿）：** 计划 A（`docs/superpowers/plans/2026-10-14-rhi-plan-a-evidence-abstraction-buildsplit.md`）完成——后端独立静态库（`engine_rhi_vulkan`/`engine_rhi_opengl`/`engine_rhi_headless`）、`rhi_native_vulkan.h` 拆分、证据台账 `docs/rhi_backend_evidence.md` 已建立；目标后端至少 HEADLESS 证据等级。**开始 Task 1 前逐项核实，缺项即停。**
- **golden 参考保护：** `engine/tests/golden/*.ppm` 是已提交的 golden 参考，只有 `GOLDEN_UPDATE=1` 显式再生成时才允许变化，且变化必须随 commit 说明。

## 构建 / 测试命令（每个 Task 复用）

```bash
# 一次性配置（仓库根 E:/work/break；VK 配置为主，GL 配置用于跨后端回归）
cmake -S engine -B build-vk -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=ON
cmake -S engine -B build-gl -G Ninja -DCMAKE_BUILD_TYPE=Debug
# 全量构建 + headless 套件（排除 graphics/fuzz）
cmake --build build-vk --parallel
ctest --test-dir build-vk -LE "graphics|fuzz" --output-on-failure
# 图形套件（含 test_vulkan golden/readback oracle；本机真 GPU）
ctest --test-dir build-vk -L graphics --output-on-failure
# 单测试
cmake --build build-vk --target <target> --parallel
ctest --test-dir build-vk -R <name> --output-on-failure
# GL 回归（每处「GL lane 同跑」即指 build-gl 上的同命令；本机无 GL 环境时记为 CI `gl` lane 验证项）
cmake --build build-gl --parallel && ctest --test-dir build-gl -L graphics --output-on-failure
```

---

## 文件结构

| 文件 | 责任 |
|---|---|
| `engine/tests/rhi_oracle.h` / `engine/tests/rhi_oracle.c` | （新建）golden/readback oracle：RGBA8→20x15 网格 box 降采样、P6 PPM 读写、MAE/maxd 比较、presented-frame 捕获包装 |
| `engine/tests/test_rhi_oracle.c` | （新建）oracle 的纯逻辑 headless 自测 |
| `engine/src/test_vulkan.c` | golden helper 改为调 rhi_oracle；新增 buffer/texture/capability 契约 phase |
| `engine/src/rhi/rhi.h` | `RHICapabilities` 增字段；`RHIPipelineBindings` 不透明类型 + create/destroy/resolve 原型；旧 API deprecated 注释 |
| `engine/src/rhi/rhi_vk.c` / `engine/src/rhi/rhi_gl.c` | caps 新字段填充；shader create 时反射缓存；bindings API 实现；VK 硬编码 offset 表（rhi_vk.c:7287+）最终删除 |
| `engine/src/core/shader_io.h` / `.c` | `shader_reflect_push_constants`（std430 offset 计算）、`shader_variant_suffix`/`shader_variant_path` |
| `engine/tests/test_shader_io.c` / `test_rhi_capabilities.c` | reflection 与 capability 契约测试扩展 |
| `engine/src/main.c`、`engine/src/renderer/*.c`、`engine/src/ui/`、`engine/src/myui/myr/my_vgcanvas_break_rhi.c` | 分支迁移与 412 处 uniform 调用点迁移对象 |
| `engine/tests/test_renderer_backend_token_gate.cmake` | （新建）收尾审计：后端分支 token grep gate |
| `docs/Architecture_Overview.md`、`docs/rhi_backend_evidence.md` | 收尾文档 |

**调用点底盘（2026-10-14 实测，执行时以当刻 `grep -c` 复核）：** `rhi_pipeline_get_uniform_location` 在 engine/src 共 417 处文本命中，其中真实调用点 412 处：main.c 58、test_vulkan.c 87、renderer 267（combined_post_process 26 / deferred 23 / ibl 18 / volumetric 15 / particles 14 / terrain 13 / taa 11 / tonemap 10 / water 9 / upscale 9 / sss 8 / ssr 8 / lens_flare 8 / gpucull 8 / ssgi 7 / debug_viz 7 / ssao 6 / motion_blur 6 / dof 6 / contact_shadow 6 / cinematic 6 / occlusion_cull 5 / god_rays 5 / color_grade 5 / skybox 4 / point_shadow 4 / lens_effects 4 / sharpen 3 / post_process 3 / lighting 3 / fxaa 3 / forward_velocity 3 / indirect_draw 1）；其余 5 处为 rhi.h 声明/注释（2）、rhi_vk.c（2）、rhi_gl.c（1）。`ENGINE_VULKAN`/`ENGINE_RHI_BACKEND_` token：main.c 10、test_vulkan.c 23、renderer 合计 47（deferred 5、terrain 4、post_process 4、rt_trace 2、particles 2、combined_post_process 2、其余 27 个 renderer 文件各 1）、ui/myui_break.c 1、my_vgcanvas_break_rhi.c 1、rhi.c 1（unity-include，计划 A 已处理）、platform_compat.h 10（平台证据层，不在本计划范围）。

---

### Task 1: rhi_oracle 基础设施（golden-image readback 抽象 + 确定性模式）

**Files:**
- Create: `engine/tests/rhi_oracle.h`
- Create: `engine/tests/rhi_oracle.c`
- Create: `engine/tests/test_rhi_oracle.c`
- Modify: `engine/src/test_vulkan.c:93-307`（golden helper 区块替换为 rhi_oracle 调用）
- Modify: `engine/CMakeLists.txt`（注册 `test_rhi_oracle`；test_vulkan 追加 `tests/rhi_oracle.c` 源）

**Interfaces:**
- Consumes: `rhi_screenshot`（rhi.h:825，R577 合法窗口 = `rhi_frame_end` 之后、`rhi_present` 之前）；`GOLDEN_UPDATE=1` 环境变量惯例（test_vulkan.c:286）。
- Produces（后续所有 Task 的验证底座）:

```c
/* engine/tests/rhi_oracle.h */
#pragma once
#include <core/types.h>
#include <rhi/rhi.h>
#include <stdbool.h>

#define RHI_ORACLE_GW 20u
#define RHI_ORACLE_GH 15u
#define RHI_ORACLE_MAE_MAX 8.0
#define RHI_ORACLE_MAXD_MAX 56u

typedef struct { f64 mae; u32 maxd; } RHIOracleResult;

/* RGBA8 帧 box-降采样到 GW x GH RGB 网格（grid 大小 RHI_ORACLE_GW*RHI_ORACLE_GH*3）。 */
void rhi_oracle_downsample(const u8 *rgba, u32 w, u32 h, u8 *grid);
bool rhi_oracle_write_ppm(const char *path, const u8 *grid);
/* 0 = 已比较（填充 out）；1 = 格式/尺寸不符；-1 = 参考缺失。 */
int  rhi_oracle_compare_ppm(const char *path, const u8 *grid, RHIOracleResult *out);
/* 完整判定：降采样 + GOLDEN_UPDATE=1 再生 + 容差判定 + reject_blank 防空图。 */
bool rhi_oracle_compare_frame(const u8 *shot_rgba, u32 w, u32 h,
                              const char *path, bool reject_blank);
/* R577 包装：frame_end 之后、present 之前捕获 presented 帧 RGBA8。 */
bool rhi_oracle_capture_presented(RHIDevice *dev, u32 w, u32 h, u8 *out_rgba);
```

- [ ] **Step 1: 写失败测试 `engine/tests/test_rhi_oracle.c`**

```c
#include "test_framework.h"
#include "rhi_oracle.h"
#include <string.h>
#include <stdio.h>

TEST(downsample_constant_frame_is_constant_grid)
{
    u8 rgba[8 * 8 * 4];
    u8 grid[RHI_ORACLE_GW * RHI_ORACLE_GH * 3];
    for (usize i = 0; i < sizeof(rgba); i += 4u) {
        rgba[i] = 200u; rgba[i + 1u] = 100u; rgba[i + 2u] = 50u; rgba[i + 3u] = 255u;
    }
    rhi_oracle_downsample(rgba, 8u, 8u, grid);
    for (usize i = 0; i < sizeof(grid); i += 3u) {
        ASSERT_EQ(grid[i], 200u);
        ASSERT_EQ(grid[i + 1u], 100u);
        ASSERT_EQ(grid[i + 2u], 50u);
    }
}

TEST(ppm_roundtrip_and_drift_detection)
{
    u8 grid[RHI_ORACLE_GW * RHI_ORACLE_GH * 3];
    u8 drift[RHI_ORACLE_GW * RHI_ORACLE_GH * 3];
    RHIOracleResult res = {0.0, 0u};
    const char *path = "tmp_rhi_oracle_test.ppm";
    for (usize i = 0; i < sizeof(grid); i++) grid[i] = (u8)(i % 251u);
    ASSERT_EQ(rhi_oracle_compare_ppm(path, grid, &res), -1); /* 缺失 */
    ASSERT_TRUE(rhi_oracle_write_ppm(path, grid));
    ASSERT_EQ(rhi_oracle_compare_ppm(path, grid, &res), 0);
    ASSERT_TRUE(res.mae == 0.0 && res.maxd == 0u);
    memcpy(drift, grid, sizeof(drift));
    drift[0] = (u8)(drift[0] + 57u); /* 超过 MAXD_MAX 56 */
    ASSERT_EQ(rhi_oracle_compare_ppm(path, drift, &res), 0);
    ASSERT_TRUE(res.maxd >= 57u);
    remove(path);
}

TEST(compare_frame_rejects_blank_when_asked)
{
    u8 shot[64 * 48 * 4];
    memset(shot, 0x11, sizeof(shot));
    ASSERT_FALSE(rhi_oracle_compare_frame(shot, 64u, 48u,
                                          "tmp_rhi_oracle_blank.ppm", true));
}

TEST_MAIN_BEGIN()
    RUN_TEST(downsample_constant_frame_is_constant_grid);
    RUN_TEST(ppm_roundtrip_and_drift_detection);
    RUN_TEST(compare_frame_rejects_blank_when_asked);
TEST_MAIN_END()
```

- [ ] **Step 2: 注册并运行，验证失败**

在 `engine/CMakeLists.txt` 的 headless 测试区（test_rhi_capabilities 注册块附近）追加：

```cmake
    add_executable(test_rhi_oracle tests/test_rhi_oracle.c tests/rhi_oracle.c
        src/core/log.c)
    target_include_directories(test_rhi_oracle PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_rhi_oracle COMMAND test_rhi_oracle)
```

Run: `cmake --build build-vk --target test_rhi_oracle && (cd engine && ../build-vk/test_rhi_oracle)`
Expected: 链接失败（`rhi_oracle_downsample` 等未定义）。

- [ ] **Step 3: 最小实现 `engine/tests/rhi_oracle.c` / `.h`**

把 test_vulkan.c:98-193（`GOLDEN_GW/GH`、`golden_downsample`、`golden_write_ppm`、`golden_compare_ppm`）与 :267-307（`golden_compare_buffer` 的判定逻辑）原样搬迁为上面 Produces 块的 API，行为逐点保持：同样的 box 均值、同样的 `fscanf("P6 %d %d %d")` 解析、同样的 `mae <= 8.0 && maxd <= 56` 容差、同样的 `GOLDEN_UPDATE` 环境变量再生语义、同样的 reject_blank 全平色检测。`rhi_oracle_capture_presented` 为：

```c
bool rhi_oracle_capture_presented(RHIDevice *dev, u32 w, u32 h, u8 *out_rgba) {
    if (!dev || !out_rgba || w == 0u || h == 0u) return false;
    return rhi_screenshot(dev, 0, 0, w, h, out_rgba, (usize)w * h * 4u);
}
```

mkdir 兼容沿用 test_vulkan.c:27-33 的 `tv_mkdir` 写法（`_mkdir` / `mkdir(p, 0755)`），在 rhi_oracle.c 内私有定义。

- [ ] **Step 4: 运行验证通过**

Run: `cmake --build build-vk --target test_rhi_oracle && (cd engine && ../build-vk/test_rhi_oracle) && ctest --test-dir build-vk -R test_rhi_oracle --output-on-failure`
Expected: 3 个 TEST 全 PASS。

- [ ] **Step 5: test_vulkan 切换到 rhi_oracle（行为保持重构）**

test_vulkan.c：删除 `golden_downsample`/`golden_write_ppm`/`golden_compare_ppm`/`golden_compare_buffer` 本体，`golden_compare_buffer(shot, path, w, h, reject_blank)` 改为 `return rhi_oracle_compare_frame(shot, w, h, path, reject_blank);`（保留 wrapper 以最小化 6829 行文件的 churn）；文件头加 `#include "../tests/rhi_oracle.h"`；`engine/CMakeLists.txt` 的 `add_executable(test_vulkan src/test_vulkan.c)`（:1107）改为 `add_executable(test_vulkan src/test_vulkan.c tests/rhi_oracle.c)`。

- [ ] **Step 6: oracle 验证重构等价（deterministic 纪律的首次执行）**

Run（VK lane）: `cmake --build build-vk --target test_vulkan && ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure`
Expected: PASS，日志中 `GOLDEN: tests/golden/test_vulkan_vk.ppm MAE=... -> OK` 与重构前数值一致；**`engine/tests/golden/*.ppm` 的 git status 必须干净**（参考未被再生成）。GL lane 在 Linux Xvfb/CI `gl` lane 同样跑一次（本机无 GL 环境时记录为 CI 验证项，不伪造）。

- [ ] **Step 7: Commit**

```bash
git add engine/tests/rhi_oracle.h engine/tests/rhi_oracle.c engine/tests/test_rhi_oracle.c engine/src/test_vulkan.c engine/CMakeLists.txt
git commit -m "test(rhi): extract golden-image readback oracle from test_vulkan into reusable rhi_oracle"
```

---

### Task 2: frame/present/resize 迁移——后端分支 → RHICapabilities 查询

**Files:**
- Modify: `engine/src/rhi/rhi.h:112-124`（`RHICapabilities` 增字段）、`:353`（新增 `rhi_device_create_compiled` 原型）
- Modify: `engine/src/rhi/rhi_vk.c`、`engine/src/rhi/rhi_gl.c`（caps 填充 + create_compiled）
- Modify: `engine/tests/test_rhi_capabilities.c`（headless 契约）
- Modify: `engine/src/test_vulkan.c`（graphics lane caps 断言 phase）
- Modify: `engine/src/main.c:343-359,363-369,413-419,467-479,685-691,743-749,1156-1158,2751-2757,8807-8809`（全部 10 处 `ENGINE_VULKAN` 分支）
- Modify: `engine/src/core/shader_io.h` / `.c`（`shader_variant_suffix`/`shader_variant_path`）
- Modify: `engine/tests/test_shader_io.c`

**Interfaces:**
- Consumes: Task 1 的 rhi_oracle（经 test_vulkan golden gate 验证）；现有 `rhi_device_get_capabilities`（rhi.h:359）。
- Produces:

```c
/* rhi.h — RHICapabilities 追加字段（末尾，保持已有字段偏移不变） */
typedef enum {
    RHI_SHADER_VARIANT_GLSL    = 0, /* desktop GL 源（无后缀） */
    RHI_SHADER_VARIANT_GLSL_VK = 1, /* Vulkan 布局 GLSL（*_vk 后缀，push-constant 块） */
} RHIShaderVariant;
/* RHICapabilities 现有字段之后追加： */
typedef struct {
    RHIBackend backend;
    u32        color_sample_counts;
    u32        depth_sample_counts;
    u32        surface_sample_count;
    bool       color_resolve_supported;
    bool       depth_resolve_supported;
    bool       scissor_supported;
    bool       present_target_preserved;
    bool       present_damage_supported;
    bool       present_buffer_age_supported;
    u32        feature_bits;
    /* 计划 E 新增（headless 契约：test_rhi_capabilities） */
    bool       push_constants_supported; /* VK=true，GL=false */
    u32        max_push_constant_size;   /* 字节；不支持为 0；VK=设备 limit（>=128） */
    bool       hiz_supported;            /* Hi-Z occlusion 金字塔路径 */
    bool       compute_supported;        /* rhi_cmd_dispatch 路径 */
    bool       indirect_draw_supported;  /* rhi_cmd_draw_*_indirect 族 */
    u32        shader_variant;           /* RHIShaderVariant */
} RHICapabilities;

/* 编译期单后端的设备创建入口（Post-计划 A：enum 参数退役为内部细节） */
/* 2026-10-16 修订:双句柄——VK/Metal 取 surface_native(Wayland 上为
 * wl_surface*),GL 取 window_native(Wayland 上为 wl_egl_window*)。 */
RHIDevice *rhi_device_create_compiled(void *window_native, void *surface_native,
                                      void *display_native, u32 w, u32 h);

/* shader_io.h */
const char *shader_variant_suffix(RHIShaderVariant v); /* "" 或 "_vk" */
/* "shaders/foo.vert" + GLSL_VK -> 写出 "shaders/foo_vk.vert"；越界返回 NULL。 */
char *shader_variant_path(const char *base_path, RHIShaderVariant v,
                          char *out, usize cap);
```

- [ ] **Step 1: 写失败契约测试（headless）**

`engine/tests/test_rhi_capabilities.c` 追加（stub 设备 caps 全零，断言 fail-closed 默认）：

```c
TEST(plan_e_capability_fields_default_closed_on_stub)
{
    RHIDevice *device = rhi_test_device_create();
    RHICapabilities caps;
    memset(&caps, 0xA5, sizeof(caps));
    ASSERT_NEQ(device, NULL);
    ASSERT_TRUE(rhi_device_get_capabilities(device, &caps));
    ASSERT_FALSE(caps.push_constants_supported);
    ASSERT_EQ(caps.max_push_constant_size, 0u);
    ASSERT_FALSE(caps.hiz_supported);
    ASSERT_FALSE(caps.compute_supported);
    ASSERT_FALSE(caps.indirect_draw_supported);
    ASSERT_EQ(caps.shader_variant, (u32)RHI_SHADER_VARIANT_GLSL);
    rhi_test_device_destroy(device);
}

TEST(create_compiled_rejects_null_handles_and_zero_dims)
{
    ASSERT_EQ(rhi_device_create_compiled(NULL, NULL, 64u, 64u), NULL);
    ASSERT_EQ(rhi_device_create_compiled(NULL, NULL, 0u, 64u), NULL);
}
```

`engine/tests/test_shader_io.c` 追加：

```c
TEST(variant_path_appends_suffix_before_extension)
{
    char out[128];
    ASSERT_TRUE(shader_variant_path("shaders/blinn_phong.vert",
                                    RHI_SHADER_VARIANT_GLSL_VK,
                                    out, sizeof(out)) != NULL);
    ASSERT_TRUE(strcmp(out, "shaders/blinn_phong_vk.vert") == 0);
    ASSERT_TRUE(shader_variant_path("shaders/blinn_phong.vert",
                                    RHI_SHADER_VARIANT_GLSL,
                                    out, sizeof(out)) != NULL);
    ASSERT_TRUE(strcmp(out, "shaders/blinn_phong.vert") == 0);
    ASSERT_TRUE(shader_variant_path("shaders/blinn_phong.vert",
                                    RHI_SHADER_VARIANT_GLSL_VK, out, 8u) == NULL);
    ASSERT_TRUE(strcmp(shader_variant_suffix(RHI_SHADER_VARIANT_GLSL_VK), "_vk") == 0);
}
```

- [ ] **Step 2: 运行验证失败**

Run: `cmake --build build-vk --target test_rhi_capabilities test_shader_io`
Expected: 编译错误（`push_constants_supported` 等字段与 `shader_variant_path` 不存在）。

- [ ] **Step 3: 最小实现**

`rhi.h` 按 Produces 块加字段/枚举/原型（新字段追加在 `feature_bits` 之后）；`rhi_vk.c`：`push_constants_supported=true`、`max_push_constant_size` 取 `VkPhysicalDeviceLimits::maxPushConstantsSize`（下限钳制告警 <128）、`hiz_supported=compute_supported=indirect_draw_supported=true`、`shader_variant=RHI_SHADER_VARIANT_GLSL_VK`；`rhi_gl.c`：`push_constants_supported=false`、`max_push_constant_size=0`、`hiz_supported/compute_supported/indirect_draw_supported=true`（GL 4.3 compute 已在 gpucull/ibl 路径使用）、`shader_variant=RHI_SHADER_VARIANT_GLSL`；两后端各实现 `rhi_device_create_compiled`（VK 调 `rhi_device_create(RHI_BACKEND_VULKAN,...)`，GL 调 `RHI_BACKEND_OPENGL`）。`shader_io.c` 实现：

```c
const char *shader_variant_suffix(RHIShaderVariant v) {
    return v == RHI_SHADER_VARIANT_GLSL_VK ? "_vk" : "";
}

char *shader_variant_path(const char *base_path, RHIShaderVariant v,
                          char *out, usize cap) {
    if (!base_path || !out) return NULL;
    const char *dot = strrchr(base_path, '.');
    const char *suffix = shader_variant_suffix(v);
    usize stem = dot ? (usize)(dot - base_path) : strlen(base_path);
    usize need = stem + strlen(suffix) + strlen(dot ? dot : "") + 1u;
    if (need > cap) return NULL;
    memcpy(out, base_path, stem);
    strcpy(out + stem, suffix);
    if (dot) strcpy(out + stem + strlen(suffix), dot);
    return out;
}
```

- [ ] **Step 4: 运行验证通过**

Run: `cmake --build build-vk --target test_rhi_capabilities test_shader_io && ctest --test-dir build-vk -R 'test_rhi_capabilities|test_shader_io' --output-on-failure`
Expected: 全 PASS，零警告。

- [ ] **Step 5: 写 graphics lane caps 断言（test_vulkan 新 phase）并验证当前行为**

在 test_vulkan.c 主流程靠前位置加 `tv_test_capability_contract`：VK 断言 `push_constants_supported && max_push_constant_size >= 128 && shader_variant == RHI_SHADER_VARIANT_GLSL_VK && compute_supported && indirect_draw_supported && hiz_supported`；GL 断言 `!push_constants_supported && max_push_constant_size == 0 && shader_variant == RHI_SHADER_VARIANT_GLSL`。Step 3 已让两后端填值，本步直接 PASS；若任一断言失败说明后端填充错误，回到 Step 3 修正（不许改测试迁就实现）。

- [ ] **Step 6: 迁移 main.c 的 10 处分支**

规则 F1（设备创建，main.c:343-359）：`render_init` 改为

<!-- 2026-10-16 修订:Wayland 上 surface/window getter 返回不同类型(wl_surface* vs wl_egl_window*),单句柄+回退链会造成 GL-on-Wayland 指针类型混淆;改为双句柄,各后端自选。 -->
```c
    void *window_native = platform_window_native(platform);
    void *surface_native = platform_surface_native(platform);
    void *display = platform_display_native(platform);
    u32 w, h;
    platform_get_drawable_size(platform, &w, &h);
    rs->device = rhi_device_create_compiled(window_native, surface_native,
                                            display, w, h);
    if (!rs->device) return false;
    RHICapabilities caps = {0};
    if (!rhi_device_get_capabilities(rs->device, &caps)) goto fail;
```

规则 F2（shader 路径选择，main.c:363-369,413-419,467-479,685-691,743-749 及本计划后续所有同型点）：`#ifdef ENGINE_VULKAN ... "shaders/blinn_phong_vk.vert" ... #else ... #endif` 改为

```c
    char vs_path[128], fs_path[128];
    if (!shader_variant_path("shaders/blinn_phong.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
        !shader_variant_path("shaders/blinn_phong.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path)))
        goto fail;
    char *vs_src = shader_read_file(vs_path, &vs_len);
    char *fs_src = shader_read_file(fs_path, &fs_len);
```

`caps` 需要传入各 renderer 子系统 init：签名上已有 `RHIDevice *` 的，在 init 内自查一次 `rhi_device_get_capabilities` 并缓存到子系统 struct（真实消费点，非改名）。

规则 F3（main.c:1156-1158 `#ifndef ENGINE_VULKAN` 的 GL-only proj uniform）：语义是「push-constant 后端把 proj 放在 frame UBO，非 push 后端要单独写」——改为

```c
    if (!rs->caps.push_constants_supported)
        rhi_cmd_set_uniform_mat4(cmd, L->cl_loc_proj, &proj->e[0][0]);
```

（`RenderState` 增加 `RHICapabilities caps;` 成员，render_init 填充。）

规则 F4（main.c:2751-2757 hotreload shader 路径）：同 F2，caps 取 `render.caps`，路径缓冲用同一函数内局部数组。

规则 F5（main.c:8807-8809 VK validation 诊断计数）：这是合理的后端专属诊断，走**逃生舱约定**（本计划全局唯一白名单机制，Task 7/8 沿用并强制）：允许保留的后端特定代码必须同时满足 (a) 包在 `#if defined(ENGINE_RHI_BACKEND_VULKAN)` 块内；(b) 紧邻注释 `/* RHI-ESCAPE: <原因> */`；(c) 其他后端编译时 fail-closed 或裁剪，不崩不伪装。计划 A 已把 `rhi_vk_validation_*` 迁入 `rhi_native_vulkan.h`，此处改为（**注释必须在 `#if` 行的上一行**，Task 8 gate 按此配对）：

```c
    /* RHI-ESCAPE: VK validation 计数仅存在于 VK 后端（rhi_native_vulkan.h）；
     * 非 VK 编译单元裁剪该诊断行。 */
#if defined(ENGINE_RHI_BACKEND_VULKAN)
    LOG_INFO("VK validation messages this run: %u", rhi_vk_validation_message_count());
#endif
```

- [ ] **Step 7: oracle 验证**

Run: `cmake --build build-vk --target test_vulkan break_myui 2>&1 | tee /tmp/planE_t2_build.log; ! grep -iE 'warning|error' /tmp/planE_t2_build.log && ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure`
Expected: 构建零警告；test_vulkan PASS（golden MAE 数值与 Task 1 基线一致——分支迁移不许改变任何渲染输出）。GL lane 同样验证（CI `gl` lane 或 Linux Xvfb）。grep 断言：`grep -c 'ENGINE_VULKAN' engine/src/main.c` 从 10 降到 0，且 `grep -c 'ENGINE_RHI_BACKEND_' engine/src/main.c` 仅剩 8807 一处 RHI-ESCAPE 白名单块。

- [ ] **Step 8: Commit**

```bash
git add engine/src/rhi/rhi.h engine/src/rhi/rhi_vk.c engine/src/rhi/rhi_gl.c engine/src/core/shader_io.h engine/src/core/shader_io.c engine/src/main.c engine/tests/test_rhi_capabilities.c engine/tests/test_shader_io.c engine/src/test_vulkan.c
git commit -m "feat(rhi): capability contract for frame/present/resize; replace ENGINE_VULKAN branches in main.c"
```

---

### Task 3: buffer/staging/readback 行为契约统一

**Files:**
- Modify: `engine/src/test_vulkan.c`（新增 `tv_test_buffer_staging_contract` phase，GL/VK 双后端共享）
- Modify: `engine/tests/test_rhi_capabilities.c`（headless 参数校验契约补充）
- Modify: `engine/src/rhi/rhi.h:654-665`（buffer 更新/回读契约注释固化为规范文本）
- Modify: `engine/src/rhi/rhi_vk.c`、`engine/src/rhi/rhi_gl.c`（仅当契约测试暴露真实分歧时最小修复）

**Interfaces:**
- Consumes: `rhi_buffer_create/rhi_buffer_update/rhi_buffer_update_region/rhi_cmd_update_buffer/rhi_buffer_read/rhi_buffer_map/rhi_buffer_unmap`（rhi.h:654-665,812-813）；Task 2 的 caps。
- Produces: 固定四条跨后端行为契约（写入 rhi.h 注释 + 双后端测试钉死）：
  - **C-BUF-1** `initial_data` 上传后 `rhi_buffer_read` 字节精确回读（HOST_VISIBLE 与 DEVICE_LOCAL+staging 同语义）；
  - **C-BUF-2** `rhi_buffer_update_region(dev, buf, off, data, size)` 只影响 `[off, off+size)`，邻居字节不变；offset/size 无需调用方对齐（后端内部处理 non-coherent atom 对齐）；
  - **C-BUF-3** 同一 command buffer 内 `rhi_cmd_update_buffer` 对后续 `rhi_cmd_dispatch`/draw 有序可见（R183 契约）；
  - **C-BUF-4** `rhi_buffer_map` 写入在 `rhi_buffer_unmap` 后对 device 可见、对 `rhi_buffer_read` 可见。

- [ ] **Step 1: 写失败/缺口测试**

在 test_vulkan.c 新增 phase（放在现有 readback 族测试之后，双后端各跑一次）：

```c
static bool tv_test_buffer_staging_contract(const TestRenderState *rs) {
    RHIDevice *dev = rs->device;
    bool pass = true;
    /* C-BUF-1: initial_data 字节精确回读（64B，含非 4 对齐尾部由 C-BUF-2 覆盖） */
    u8 src[64];
    for (u32 i = 0; i < 64u; i++) src[i] = (u8)(i * 3u + 1u);
    RHIBufferDesc bd = { RHI_BUFFER_USAGE_STORAGE, sizeof(src), src };
    RHIBuffer buf = rhi_buffer_create(dev, &bd);
    u8 rb[64];
    memset(rb, 0xAB, sizeof(rb));
    if (!rhi_handle_valid(buf) || !rhi_buffer_read(dev, buf, rb, 0u, sizeof(rb)) ||
        memcmp(rb, src, sizeof(src)) != 0) {
        LOG_ERROR("FAIL: C-BUF-1 initial_data roundtrip");
        pass = false;
    }
    /* C-BUF-2: region update 只动 [off, off+size)，含非对齐 offset 20/size 7 */
    if (pass) {
        u8 patch[7] = { 9u, 8u, 7u, 6u, 5u, 4u, 3u };
        rhi_buffer_update_region(dev, buf, 20u, patch, sizeof(patch));
        memset(rb, 0xAB, sizeof(rb));
        if (!rhi_buffer_read(dev, buf, rb, 0u, sizeof(rb))) {
            LOG_ERROR("FAIL: C-BUF-2 readback"); pass = false;
        } else {
            u8 want[64];
            memcpy(want, src, sizeof(want));
            memcpy(want + 20u, patch, sizeof(patch));
            if (memcmp(rb, want, sizeof(want)) != 0) {
                LOG_ERROR("FAIL: C-BUF-2 region isolation (off=20 size=7)");
                pass = false;
            }
        }
    }
    /* C-BUF-4: map 写入 unmap 后 read 可见 */
    if (pass) {
        u8 *m = (u8 *)rhi_buffer_map(dev, buf);
        if (!m) { LOG_ERROR("FAIL: C-BUF-4 map"); pass = false; }
        else {
            m[0] = 0xEEu;
            rhi_buffer_unmap(dev, buf);
            u8 one = 0u;
            if (!rhi_buffer_read(dev, buf, &one, 0u, 1u) || one != 0xEEu) {
                LOG_ERROR("FAIL: C-BUF-4 map/unmap visibility (got %u)", one);
                pass = false;
            }
        }
    }
    if (rhi_handle_valid(buf)) rhi_buffer_destroy(dev, buf);
    return pass;
}
```

C-BUF-3（CB 内有序性）的完整实现（双后端 shader 源用 test_vulkan 既有的编译期选择惯例——test_vulkan.c 不在 Task 8 审计扫描根内）：

```c
static bool tv_test_cmd_update_buffer_ordering(const TestRenderState *rs) {
#ifdef ENGINE_VULKAN
    static const char cs_src[] =
        "#version 460\n"
        "layout(local_size_x = 1) in;\n"
        "layout(std430, binding = 0) buffer Data { uint v; } d;\n"
        "layout(std430, binding = 1) buffer Flag { uint f; } g;\n"
        "void main() { g.f = (d.v == 0x5Au) ? 1u : 0u; }\n";
#else
    static const char cs_src[] =
        "#version 430\n"
        "layout(local_size_x = 1) in;\n"
        "layout(std430, binding = 0) buffer Data { uint v; } d;\n"
        "layout(std430, binding = 1) buffer Flag { uint f; } g;\n"
        "void main() { g.f = (d.v == 0x5Au) ? 1u : 0u; }\n";
#endif
    RHIDevice *dev = rs->device;
    u32 zero = 0u;
    RHIBufferDesc dd = { RHI_BUFFER_USAGE_STORAGE, 4u, &zero };
    RHIBufferDesc fd = { RHI_BUFFER_USAGE_STORAGE, 4u, &zero };
    RHIBuffer data = rhi_buffer_create(dev, &dd);
    RHIBuffer flag = rhi_buffer_create(dev, &fd);
    RHIShader cs = rhi_shader_create_compute(dev, cs_src, sizeof(cs_src) - 1u);
    RHIPipelineDesc pd = {0};
    pd.is_compute = true;
    pd.frag = cs;
    RHIPipeline pipe = rhi_pipeline_create(dev, &pd);
    bool pass = rhi_handle_valid(data) && rhi_handle_valid(flag) &&
                rhi_handle_valid(cs) && rhi_handle_valid(pipe);
    if (pass) {
        RHICmdBuffer *cmd = rhi_frame_begin(dev);
        if (!cmd) { pass = false; }
        else {
            u32 val = 0x5Au;
            /* C-BUF-3: 同 CB 内 update → dispatch 必须读到新值。 */
            rhi_cmd_update_buffer(cmd, data, 0u, &val, sizeof(val));
            rhi_cmd_bind_pipeline(cmd, pipe);
            rhi_cmd_bind_storage_buffer(cmd, data, 0u);
            rhi_cmd_bind_storage_buffer(cmd, flag, 1u);
            rhi_cmd_dispatch(cmd, 1u, 1u, 1u);
            rhi_frame_end(dev);
            rhi_present(dev);
            /* 与 test_ray_query_pixel 相同的 drain 惯例：再空跑一帧后读。 */
            cmd = rhi_frame_begin(dev);
            if (cmd) { rhi_frame_end(dev); rhi_present(dev); }
            u32 got = 0xFFFFFFFFu;
            if (!rhi_buffer_read(dev, flag, &got, 0u, sizeof(got)) || got != 1u) {
                LOG_ERROR("FAIL: C-BUF-3 update not ordered before dispatch (flag=%u)", got);
                pass = false;
            }
        }
    }
    if (rhi_handle_valid(pipe)) rhi_pipeline_destroy(dev, pipe);
    if (rhi_handle_valid(cs))   rhi_shader_destroy(dev, cs);
    if (rhi_handle_valid(flag)) rhi_buffer_destroy(dev, flag);
    if (rhi_handle_valid(data)) rhi_buffer_destroy(dev, data);
    return pass;
}
```

- [ ] **Step 2: 运行验证当前状态**

Run: `ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure`
Expected: 逐条记录 C-BUF-1/2/4 与 C-BUF-3 在 VK、GL 的实际结果。**任何 FAIL 都是真实分歧，禁止改测试迁就**——进入 Step 3 修后端；全 PASS 则本 Task 收敛为「契约钉死」。

- [ ] **Step 3: 最小修复（如有分歧）**

VK 侧已知风险点：`rhi_buffer_update_region` 的非对齐 flush（`VkMappedMemoryRange` offset/size 需对齐 nonCoherentAtomSize）与 DEVICE_LOCAL staging 的 upload buffer 复用。GL 侧已知风险点：`glBufferSubData` 即时生效无对齐问题，但 `map` 路径须确认 `GL_MAP_INVALIDATE_BUFFER_BIT` 未把未写区域置 undefined——C-BUF-2 的邻居断言专抓这个。修复只允许落在后端 .c 内，不改公开语义。

- [ ] **Step 4: 契约文本固化 + headless 补充**

rhi.h 的 `rhi_buffer_update`/`rhi_buffer_update_region`/`rhi_cmd_update_buffer`/`rhi_buffer_read`/`rhi_buffer_map` 注释改写为 C-BUF-1..4 的规范表述（含「offset/size 无需调用方对齐」一句）。test_rhi_capabilities.c 追加 `buffer_region_rejects_overflow_and_null`：`rhi_buffer_update_region(NULL, ...)` 无崩溃、`rhi_buffer_read(NULL, ...)` 返回 false（沿用 `command_entrypoints_are_safe_without_current_device` 的写法）。

- [ ] **Step 5: oracle 验证 + Commit**

Run: `ctest --test-dir build-vk -R '^test_vulkan$|test_rhi_capabilities' --output-on-failure`（GL lane 同跑）
Expected: 全 PASS。`docs/rhi_backend_evidence.md`（计划 A 已建）追加一行：buffer 契约 C-BUF-1..4 在 VK/GL 的验证日期与 lane。

```bash
git add engine/src/test_vulkan.c engine/tests/test_rhi_capabilities.c engine/src/rhi/rhi.h engine/src/rhi/rhi_vk.c engine/src/rhi/rhi_gl.c docs/rhi_backend_evidence.md
git commit -m "test(rhi): pin cross-backend buffer staging/readback contract C-BUF-1..4"
```

---

### Task 4: texture/sampler/format 跨后端一致性 oracle

**Files:**
- Modify: `engine/src/test_vulkan.c`（扩展 `tv_test_f16_roundtrip` 为全格式矩阵 + 新增 mip 上传 oracle 与 sampler 契约 phase）
- Modify: `engine/src/rhi/rhi.h:483-525`（texture/mip 契约注释固化）
- Modify: `engine/src/rhi/rhi_vk.c`、`engine/src/rhi/rhi_gl.c`（仅修测试暴露的分歧）

**Interfaces:**
- Consumes: `rhi_texture_create/rhi_texture_upload_mip/rhi_texture_read_pixels/rhi_texture_get_size/rhi_sampler_create/rhi_cmd_bind_texture_mip`（rhi.h:483-525,805）；`tv_f32_to_f16`（test_vulkan.c:80）；Task 1 oracle 的判定风格（字节精确或显式容差）。
- Produces: 契约 **C-TEX-1**（7 个 `RHIFormat` 枚举中 6 个实格式的上传→回读字节语义，UNDEFINED 拒绝创建）、**C-TEX-2**（`rhi_texture_upload_mip` 写入的 mip 经 `rhi_cmd_bind_texture_mip` + compute 采样读出 == 上传字节）、**C-TEX-3**（sampler filter/wrap 行为跨后端一致：2x2 纹理 NEAREST 放大采样取最近纹素，CLAMP_TO_EDGE 边缘不环绕）。

- [ ] **Step 1: 写失败/缺口测试**

(a) 全格式矩阵：现有 `tv_test_f16_roundtrip`（test_vulkan.c:904+）已覆盖 RG16F/RGBA16F/R32F/BGRA8/D32F；补 RGBA8 非平凡字节序（{10,20,30,40} → 回读同序）与 `RHI_FORMAT_UNDEFINED` 拒绝创建两个缺口 phase，断言风格沿用该函数。

(b) mip 上传 oracle（C-TEX-2）完整实现（set/binding 约定照 `engine/shaders/hi_z_generate.comp` 头部注释：VK 上 sampler_mip = set 2、SSBO 默认 set 0；GL 无 set 限定符）：

```c
static bool tv_test_mip_upload_oracle(const TestRenderState *rs) {
#ifdef ENGINE_VULKAN
    static const char cs_src[] =
        "#version 460\n"
        "layout(local_size_x = 1) in;\n"
        "layout(set = 2, binding = 0) uniform sampler2D u_tex;\n"
        "layout(std430, binding = 0) buffer Out { uvec4 px; } o;\n"
        "void main() { o.px = uvec4(textureLod(u_tex, vec2(0.5), 0.0) * 255.0 + 0.5); }\n";
    const u32 ssbo_binding = 0u;
#else
    static const char cs_src[] =
        "#version 430\n"
        "layout(local_size_x = 1) in;\n"
        "layout(binding = 0) uniform sampler2D u_tex;\n"
        "layout(std430, binding = 1) buffer Out { uvec4 px; } o;\n"
        "void main() { o.px = uvec4(textureLod(u_tex, vec2(0.5), 0.0) * 255.0 + 0.5); }\n";
    const u32 ssbo_binding = 1u;
#endif
    RHIDevice *dev = rs->device;
    /* 8x8 RGBA8、4 级 mip；mip2（2x2）经 upload_mip 写入 {10,200,30,255}。 */
    RHITextureDesc td = { .width = 8u, .height = 8u,
                          .format = RHI_FORMAT_R8G8B8A8_UNORM,
                          .mip_levels = 4u, .data = NULL };
    RHITexture tex = rhi_texture_create(dev, &td);
    static const u8 mip2[2 * 2 * 4] = {
        10u, 200u, 30u, 255u, 10u, 200u, 30u, 255u,
        10u, 200u, 30u, 255u, 10u, 200u, 30u, 255u };
    u32 out_init = 0u;
    RHIBufferDesc od = { RHI_BUFFER_USAGE_STORAGE, 16u, &out_init };
    RHIBuffer out_buf = rhi_buffer_create(dev, &od);
    RHIShader cs = rhi_shader_create_compute(dev, cs_src, sizeof(cs_src) - 1u);
    RHIPipelineDesc pd = {0};
    pd.is_compute = true;
    pd.frag = cs;
    pd.uses_textures = true;
    RHIPipeline pipe = rhi_pipeline_create(dev, &pd);
    RHISamplerDesc sd = { RHI_FILTER_NEAREST, RHI_FILTER_NEAREST,
                          RHI_WRAP_CLAMP_TO_EDGE, RHI_WRAP_CLAMP_TO_EDGE,
                          RHI_WRAP_CLAMP_TO_EDGE };
    RHISampler samp = rhi_sampler_create(dev, &sd);
    bool pass = rhi_handle_valid(tex) && rhi_handle_valid(out_buf) &&
                rhi_handle_valid(cs) && rhi_handle_valid(pipe) &&
                rhi_handle_valid(samp);
    if (pass) {
        rhi_texture_upload_mip(dev, tex, 2u, 2u, 2u, mip2, sizeof(mip2));
        RHICmdBuffer *cmd = rhi_frame_begin(dev);
        if (!cmd) { pass = false; }
        else {
            rhi_cmd_bind_pipeline(cmd, pipe);
            /* bind_texture_mip 绑定单 mip 视图，textureLod(...,0.0) 即 mip2。 */
            rhi_cmd_bind_texture_mip(cmd, tex, samp, 0u, 2u);
            rhi_cmd_bind_storage_buffer(cmd, out_buf, ssbo_binding);
            rhi_cmd_dispatch(cmd, 1u, 1u, 1u);
            rhi_frame_end(dev);
            rhi_present(dev);
            cmd = rhi_frame_begin(dev);       /* drain 惯例 */
            if (cmd) { rhi_frame_end(dev); rhi_present(dev); }
            u32 got[4] = { 0xFFFFFFFFu, 0u, 0u, 0u };
            if (!rhi_buffer_read(dev, out_buf, got, 0u, sizeof(got))) {
                LOG_ERROR("FAIL: C-TEX-2 readback"); pass = false;
            } else {
                static const u32 want[4] = { 10u, 200u, 30u, 255u };
                for (u32 c = 0; c < 4u; c++) {
                    u32 d = got[c] > want[c] ? got[c] - want[c] : want[c] - got[c];
                    if (d > 1u) { /* UNORM 往返 ±1 容差 */
                        LOG_ERROR("FAIL: C-TEX-2 mip2 ch%u got %u want %u",
                                  c, got[c], want[c]);
                        pass = false;
                    }
                }
            }
        }
    }
    if (rhi_handle_valid(samp))    rhi_sampler_destroy(dev, samp);
    if (rhi_handle_valid(pipe))    rhi_pipeline_destroy(dev, pipe);
    if (rhi_handle_valid(cs))      rhi_shader_destroy(dev, cs);
    if (rhi_handle_valid(out_buf)) rhi_buffer_destroy(dev, out_buf);
    if (rhi_handle_valid(tex))     rhi_texture_destroy(dev, tex);
    return pass;
}
```

若该 phase 在编译期因 set 约定报错，以 `hi_z_generate.comp` 的头部注释为唯一事实源修正 `set=` 编号——**不许为通过测试改 RHI 绑定布局**。

(c) sampler 契约（C-TEX-3）：2x2 RGBA8（四色互异）分别用 NEAREST/CLAMP 与 REPEAT 采样边缘外推 UV，render 到 4x4 offscreen FBO 后 `rhi_texture_read_pixels`，断言四角像素 == 期望纹素（NEAREST+CLAMP）；REPEAT 对照组断言环绕值。容差 ±1。

- [ ] **Step 2: 运行验证当前状态**

Run: `ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure`（VK + GL 双跑）
Expected: 记录逐条结果；任何 FAIL 回 Step 3 修后端，禁止改测试。

- [ ] **Step 3: 最小修复（如有分歧）**

已知风险点：VK `rhi_texture_upload_mip` 的 staging buffer offset 对齐与 mip extent 计算；GL mip 上传的 `glTexSubImage2D` level 目标。修复只在后端 .c。

- [ ] **Step 4: rhi.h 契约注释固化**

把 C-TEX-1/2/3 写进 `rhi_texture_create`/`rhi_texture_upload_mip`/`rhi_texture_read_pixels` 的注释（字节语义表已有 R587/R593/R601/R602 基础，补齐 mip 与 sampler 条目）。

- [ ] **Step 5: oracle 验证 + Commit**

Run: `ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure`（双后端）
Expected: PASS；evidence 台账追加 texture 契约行。

```bash
git add engine/src/test_vulkan.c engine/src/rhi/rhi.h engine/src/rhi/rhi_vk.c engine/src/rhi/rhi_gl.c docs/rhi_backend_evidence.md
git commit -m "test(rhi): texture format matrix + mip upload + sampler cross-backend oracle"
```

---

### Task 5: shader reflection 权威化 + `rhi_pipeline_get_uniform_location` 412 调用点分批迁移

**Files:**
- Modify: `engine/src/core/shader_io.h` / `engine/src/core/shader_io.c`（`shader_reflect_push_constants`）
- Modify: `engine/tests/test_shader_io.c`（std430 布局计算 + 与 VK 硬编码表的交叉对照 gate）
- Modify: `engine/src/rhi/rhi.h`（`RHIPipelineBindings` API + 旧 API deprecated 注释，:596）
- Modify: `engine/src/rhi/rhi_vk.c`（shader create 时反射缓存；pipeline create 合并 vert/frag 反射表；旧 API 改读反射表；:7287+ 硬编码表在批次清零后删除）
- Modify: `engine/src/rhi/rhi_gl.c`（bindings = glGetUniformLocation 缓存）
- Modify: `engine/tests/test_rhi_capabilities.c`（bindings fail-closed headless 契约）
- Modify: `engine/src/test_vulkan.c`（bindings↔旧 API 全名 parity 断言；随后自身 87 处迁移）
- Modify: `engine/src/main.c`（58 处）、`engine/src/renderer/*.c`（267 处，文件清单见文件结构节）

**Interfaces:**
- Consumes: `shader_reflect_bindings`/`ShaderIOBinding`（shader_io.h:26-38）；Task 2 的 caps；Task 1 oracle。
- Produces:

```c
/* shader_io.h */
typedef struct {
    char name[SHADER_IO_NAME_MAX]; /* 成员名，如 "u_view" */
    u32  offset;                   /* std430 字节偏移 */
    u32  size;                     /* 字节数 */
} ShaderIOPushMember;
/* 解析 GLSL 源码中的 layout(push_constant) uniform 块，按 std430 规则计算
 * 每个成员 offset/size。返回成员数；无 push 块返回 0。 */
usize shader_reflect_push_constants(const char *src, usize len,
                                    ShaderIOPushMember *out, usize capacity);

/* rhi.h */
typedef struct RHIPipelineBindings RHIPipelineBindings; /* 不透明 */
/* 每管线一次：后端在 shader/pipeline create 时已缓存反射结果，这里物化为
 * name->slot 表。slot 语义 = 后端绑定槽（VK push 字节偏移 / GL location /
 * 未来 Metal|D3D12 绑定索引），值由 reflection 推导、全后端同源。 */
RHIPipelineBindings *rhi_pipeline_bindings_create(RHIDevice *dev, RHIPipeline pipe);
void  rhi_pipeline_bindings_destroy(RHIDevice *dev, RHIPipelineBindings *b);
/* 成员不存在返回 -1（与旧 API 一致）。 */
i32   rhi_pipeline_bindings_resolve(const RHIPipelineBindings *b, const char *name);

/* DEPRECATED（计划 E）：新代码用 rhi_pipeline_bindings_create/resolve。
 * 保留至全部调用点迁移完成（Task 8 grep gate 清零），随后随 OpenGL 退役删除。 */
i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe, const char *name);
```

**变换规则（本 Task 全部批次共用；批次步骤引用 T1–T4 并附本批文件清单与实测计数）：**

- **T1** 每个持有 `i32 loc_*` 缓存的 struct 增加同管线对应的 `RHIPipelineBindings *bind_<x>;` 字段。
- **T2** 在 pipeline 创建成功之后立刻 `bind_x = rhi_pipeline_bindings_create(dev, pipe);`（sources 不再需要存活——反射在 shader/pipeline create 时已缓存），失败按该路径既有错误处理（多数为 LOG_WARN + 禁用该路径）。
- **T3** `rhi_pipeline_get_uniform_location(dev, pipe, "u_name")` → `rhi_pipeline_bindings_resolve(bind_x, "u_name")`；查询辅助函数（如 main.c:305 `clustered_query_locs`）签名加 `const RHIPipelineBindings *b` 参数。
- **T4** shutdown 路径加 `if (bind_x) rhi_pipeline_bindings_destroy(dev, bind_x);`（NULL 安全由实现保证）。

**批次验证（每批相同，命令逐批照跑）：** ① `cmake --build build-vk --target engine test_vulkan` 零警告；② `ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure` VK PASS（golden MAE 不变）；③ GL lane 同跑；④ `grep -c 'rhi_pipeline_get_uniform_location' <本批文件>` 降到 0（rhi.h/rhi_vk.c/rhi_gl.c 除外）；⑤ commit。

- [ ] **Step 1: 写失败测试——std430 push 反射**

`engine/tests/test_shader_io.c` 追加：

```c
TEST(push_constants_follow_std430_offsets)
{
    static const char src[] =
        "#version 460\n"
        "layout(push_constant) uniform Push {\n"
        "    mat4 u_model;\n"     /* 0,   64 */
        "    mat4 u_view;\n"      /* 64,  64 */
        "    mat4 u_proj;\n"      /* 128, 64 */
        "    vec3 u_light_dir;\n" /* 192, 12 */
        "    float u_shadow_bias;\n" /* 204, 4（vec3 尾部打包，std430） */
        "} pc;\n";
    ShaderIOPushMember members[8];
    usize n = shader_reflect_push_constants(src, sizeof(src) - 1u, members, 8u);
    ASSERT_EQ(n, 5u);
    ASSERT_TRUE(strcmp(members[0].name, "u_model") == 0);
    ASSERT_EQ(members[0].offset, 0u);   ASSERT_EQ(members[0].size, 64u);
    ASSERT_EQ(members[1].offset, 64u);
    ASSERT_EQ(members[2].offset, 128u);
    ASSERT_TRUE(strcmp(members[3].name, "u_light_dir") == 0);
    ASSERT_EQ(members[3].offset, 192u);
    ASSERT_EQ(members[4].offset, 204u); ASSERT_EQ(members[4].size, 4u);
}

TEST(push_constants_absent_returns_zero_and_handles_null)
{
    ASSERT_EQ(shader_reflect_push_constants("#version 460\nvoid main(){}", 26u,
                                            NULL, 0u), 0u);
    ASSERT_EQ(shader_reflect_push_constants(NULL, 0u, NULL, 0u), 0u);
}
```

- [ ] **Step 2: 运行验证失败**

Run: `cmake --build build-vk --target test_shader_io && (cd engine && ../build-vk/test_shader_io)`
Expected: 编译失败（`shader_reflect_push_constants` 未声明）。

- [ ] **Step 3: 最小实现**

shader_io.c：在现有 `shader_reflect_bindings` 的词法基础上识别 `layout(push_constant) uniform <Block> { ... }`，逐成员解析类型名（`float/int/uint/vec2/vec3/vec4/mat3/mat4` 及数组），按 std430 规则算 align/offset：标量 4、vec2 8、vec3/vec4 16、mat3/mat4 16（按列 vec4 数组）、数组 stride 对齐到 16。紧跟前一成员的「vec3 尾部标量打包」由 std430 的 next-offset 规则自然得出（vec3 占 12、align 16；下一标量 align 4 → offset 204）。加 `shader_std430_type_size_align(const char *type, u32 *size, u32 *align)` 静态helper。

- [ ] **Step 4: 运行验证通过**

Run: Step 2 同命令。Expected: 全 PASS。

- [ ] **Step 5: 写失败测试——反射 vs VK 硬编码表交叉对照 gate**

`test_shader_io.c` 追加 `vk_push_tables_match_reflection`：遍历 `engine/shaders/` 下含 push 块的 `*_vk.vert`/`*.frag`（blinn_phong_vk、pbr_clustered*_vk、terrain_vk、water_vk、gbuffer_vk、skinned_gbuffer_vk、combined_taa_fxaa_vk、combined_color_vk 等），对每个文件跑 `shader_reflect_push_constants`，与测试内嵌的期望值表逐项对照。期望值表**原样转录自 rhi_vk.c:7287+ 的现状硬编码表**（如 blinn：u_model@0 u_view@64 u_proj@128 u_light_dir@192 u_shadow_bias@204 …；terrain：u_view@0 u_proj@64 u_light_vp@128 u_light_dir@192 u_shadow_bias@204 u_light_color@208 u_water_y@220 u_ambient@224 u_time@236 u_camera_pos@240，见 rhi_vk.c:7306-7323）。测试 cwd 约定与 test_vulkan 一致（engine/ 下运行）。**此 gate 是反射权威化的安全网：反射结果必须等于当前生产行为，任何偏差先修反射器，不许改表。**

- [ ] **Step 6: 运行该 gate，修反射器直至全绿**

Run: `ctest --test-dir build-vk -R test_shader_io --output-on-failure`
Expected: 初次可能暴露反射器与真实 shader 的差异（数组、多级块名、注释干扰）；逐条修 shader_io.c。最终全 PASS。

- [ ] **Step 7: Commit（反射器独立落地）**

```bash
git add engine/src/core/shader_io.h engine/src/core/shader_io.c engine/tests/test_shader_io.c
git commit -m "feat(shader_io): std430 push-constant reflection, cross-checked against VK push tables"
```

- [ ] **Step 8: 写失败测试——bindings API 契约**

test_rhi_capabilities.c 追加（headless，fail-closed）：

```c
TEST(pipeline_bindings_fail_closed_on_stub_and_null)
{
    ASSERT_EQ(rhi_pipeline_bindings_create(NULL, RHI_HANDLE_NULL), (void *)NULL);
    ASSERT_EQ(rhi_pipeline_bindings_resolve(NULL, "u_model"), -1);
    rhi_pipeline_bindings_destroy(NULL, NULL); /* 无崩溃 */
}
```

test_vulkan.c 追加 graphics parity phase `tv_test_bindings_parity`：用 blinn 管线建 `RHIPipelineBindings`，对名字表 `{"u_model","u_view","u_proj","u_light_dir","u_light_color","u_ambient","u_camera_pos","u_albedo","__nonexistent__"}` 逐个断言 `rhi_pipeline_bindings_resolve(b, name) == rhi_pipeline_get_uniform_location(dev, pipe, name)`（含不存在的 -1 一致）；随后用 bindings 的值跑一遍 golden 场景（`rhi_oracle_compare_frame`，路径复用 GOLDEN_PATH）证明渲染不变。

- [ ] **Step 9: 运行验证失败**

Run: `cmake --build build-vk --target test_rhi_capabilities test_vulkan`
Expected: 编译失败（`rhi_pipeline_bindings_*` 未定义）。

- [ ] **Step 10: 最小实现（bindings API）**

- shader_io.c 不变；rhi.h 按 Produces 加类型/原型/deprecated 注释。
- rhi_vk.c：`rhi_shader_create*` 内对 source 跑 `shader_reflect_push_constants` 存入 shader 对象；`rhi_pipeline_create` 合并 vert/frag 成员表存入 `VKPipelineData`；`rhi_pipeline_bindings_create` 物化为 `{name, slot}` 数组（slot = 反射 offset）；`rhi_pipeline_get_uniform_location` 改读该反射表（保持现有分类布尔对 render-pass/布局选择的作用，仅 offset 来源切换）；rhi_vk.c:7287+ 的手写表暂时保留——Step 5 的 gate 已证明两来源一致，表留到批次清零后删除（Step 22）。
- rhi_gl.c：`rhi_pipeline_bindings_create` 对每个反射到的成员名查 `glGetUniformLocation` 缓存；未在 push 块中的 sampler/UBO 名也入表（GL 全部经 program 查询），保证 GL 上 resolve 与旧 API 全名 parity。
- rhi.c（如计划 A 后仍有调度层）：直通。

- [ ] **Step 11: 运行验证通过**

Run: `ctest --test-dir build-vk -R 'test_rhi_capabilities|^test_vulkan$' --output-on-failure`
Expected: headless 契约 PASS；VK parity + golden PASS；GL lane parity + golden PASS。

- [ ] **Step 12: Commit**

```bash
git add engine/src/rhi/rhi.h engine/src/rhi/rhi_vk.c engine/src/rhi/rhi_gl.c engine/tests/test_rhi_capabilities.c engine/src/test_vulkan.c
git commit -m "feat(rhi): reflection-driven RHIPipelineBindings API with legacy parity gate"
```

- [ ] **Step 13: 批次 1——main.c 前 50 处**

文件：`engine/src/main.c`（58 处中的前 50：`clustered_query_locs` 21（:306-326）、arr 7（:445-451）、blinn 8（:454-461）、depth 2（:674-675）、instanced 6（:721-726）、skinned 6（:780-785））。按 T1–T4 迁移：`RenderState` 加 `bind_pipeline/bind_clustered/bind_clustered_inst/bind_clustered_skin/bind_clustered_arr/bind_arr/bind_depth/bind_instanced/bind_skinned`；`clustered_query_locs` 签名改为 `(ClusteredLocs *L, const RHIPipelineBindings *b)`。批次验证 ①–⑤。

- [ ] **Step 14: Commit 批次 1**

```bash
git add engine/src/main.c
git commit -m "refactor(renderer): migrate main.c uniform queries batch 1/2 to RHIPipelineBindings"
```

- [ ] **Step 15: 批次 2——main.c 其余 8 处 + test_vulkan.c 前 42 处**

main.c 余下 8 处（执行时 `grep -n rhi_pipeline_get_uniform_location engine/src/main.c` 复核清单）；test_vulkan.c 的 `TestRenderState` 加 `RHIPipelineBindings *bind;`，`test_render_init` 的 7 处（:475-481）与 `:2652-2665`、`:2949+` 等查询块按 T1–T4。批次验证 ①–⑤。

- [ ] **Step 16: Commit 批次 2**

```bash
git add engine/src/main.c engine/src/test_vulkan.c
git commit -m "refactor(renderer): migrate main.c remainder + test_vulkan batch 1/2 to RHIPipelineBindings"
```

- [ ] **Step 17: 批次 3——test_vulkan.c 其余 45 处**

`grep -n rhi_pipeline_get_uniform_location engine/src/test_vulkan.c` 取余下清单按 T1–T4；各测试局部管线在管线创建后即建 bindings、测试结束销毁。批次验证 ①–⑤（此批后 test_vulkan 全量走新 API，golden gate 即覆盖）。

- [ ] **Step 18: Commit 批次 3**

```bash
git add engine/src/test_vulkan.c
git commit -m "refactor(test): migrate test_vulkan uniform queries batch 2/2 to RHIPipelineBindings"
```

- [ ] **Step 19: 批次 4——combined_post_process.c(26) + deferred.c(23) = 49 处**

两文件的 system struct 按 T1 加 bindings 字段（deferred 的 G-Buffer/lighting 管线分开建表）；T1–T4 全套；批次验证 ①–⑤。注意 deferred 的 factor UBO 路径（main.c:1197-1218 `gbuffer_bind_material`）只改 resolve 来源，不改 UBO 布局。

- [ ] **Step 20: Commit 批次 4**

```bash
git add engine/src/renderer/combined_post_process.c engine/src/renderer/deferred.c
git commit -m "refactor(renderer): migrate combined_post_process+deferred uniform queries to RHIPipelineBindings"
```

- [ ] **Step 21: 批次 5——ibl.c(18) + volumetric.c(15) + particles.c(14) = 47 处**

T1–T4；批次验证 ①–⑤。Commit：

```bash
git add engine/src/renderer/ibl.c engine/src/renderer/volumetric.c engine/src/renderer/particles.c
git commit -m "refactor(renderer): migrate ibl+volumetric+particles uniform queries to RHIPipelineBindings"
```

- [ ] **Step 22: 批次 6——terrain.c(13) + taa.c(11) + tonemap.c(10) + water.c(9) = 43 处**

T1–T4；批次验证 ①–⑤。**本批全绿后**删除 rhi_vk.c:7287+ 的手写 push offset 表（Step 5 的交叉对照 gate 持续保证反射 == 表；调用方已不读表）。Commit：

```bash
git add engine/src/renderer/terrain.c engine/src/renderer/taa.c engine/src/renderer/tonemap.c engine/src/renderer/water.c engine/src/rhi/rhi_vk.c
git commit -m "refactor(renderer): migrate terrain+taa+tonemap+water uniform queries; drop hand-written VK push tables"
```

- [ ] **Step 23: 批次 7——upscale.c(9) + sss.c(8) + ssr.c(8) + lens_flare.c(8) + gpucull.c(8) = 41 处**

T1–T4；批次验证 ①–⑤。Commit：

```bash
git add engine/src/renderer/upscale.c engine/src/renderer/sss.c engine/src/renderer/ssr.c engine/src/renderer/lens_flare.c engine/src/renderer/gpucull.c
git commit -m "refactor(renderer): migrate upscale+sss+ssr+lens_flare+gpucull uniform queries to RHIPipelineBindings"
```

- [ ] **Step 24: 批次 8——ssgi.c(7) + debug_viz.c(7) + ssao.c(6) + motion_blur.c(6) + dof.c(6) + contact_shadow.c(6) + cinematic.c(6) = 44 处**

T1–T4；批次验证 ①–⑤。Commit：

```bash
git add engine/src/renderer/ssgi.c engine/src/renderer/debug_viz.c engine/src/renderer/ssao.c engine/src/renderer/motion_blur.c engine/src/renderer/dof.c engine/src/renderer/contact_shadow.c engine/src/renderer/cinematic.c
git commit -m "refactor(renderer): migrate ssgi+debug_viz+ssao+motion_blur+dof+contact_shadow+cinematic uniform queries"
```

- [ ] **Step 25: 批次 9——occlusion_cull.c(5) + god_rays.c(5) + color_grade.c(5) + skybox.c(4) + point_shadow.c(4) + lens_effects.c(4) + sharpen.c(3) + post_process.c(3) + lighting.c(3) + fxaa.c(3) + forward_velocity.c(3) + indirect_draw.c(1) = 43 处**

T1–T4；批次验证 ①–⑤。批次后断言：`grep -rn 'rhi_pipeline_get_uniform_location' engine/src --include='*.c' --include='*.h'` 仅剩 rhi.h 声明/注释（2）、rhi_vk.c 旧 API 实现（2）、rhi_gl.c 实现（1）共 5 处。Commit：

```bash
git add engine/src/renderer/occlusion_cull.c engine/src/renderer/god_rays.c engine/src/renderer/color_grade.c engine/src/renderer/skybox.c engine/src/renderer/point_shadow.c engine/src/renderer/lens_effects.c engine/src/renderer/sharpen.c engine/src/renderer/post_process.c engine/src/renderer/lighting.c engine/src/renderer/fxaa.c engine/src/renderer/forward_velocity.c engine/src/renderer/indirect_draw.c
git commit -m "refactor(renderer): migrate remaining 12 renderer systems uniform queries to RHIPipelineBindings"
```

---

### Task 6: pipeline/MRT/depth/shadow/Hi-Z 后端中立化

**Files:**
- Modify: `engine/src/renderer/deferred.c`（5 处分支）、`engine/src/renderer/point_shadow.c`（1）、`engine/src/renderer/occlusion_cull.c`（1）、`engine/src/renderer/post_process.c`（4）、`engine/src/renderer/terrain.c`（4）、`engine/src/renderer/particles.c`（2）、`engine/src/renderer/combined_post_process.c`（2）、其余 27 个各 1 处的 renderer 文件（清单见文件结构节）
- Modify: `engine/src/rhi/rhi.h:260-281`（`RHIPipelineDesc` 布局布尔与 render-pass 兼容字段的契约注释，spec §4.4）
- Modify: `engine/tests/test_rhi_capabilities.c`（pipeline contract 字段的 headless 断言）
- Docs: `docs/rhi_backend_evidence.md`（Hi-Z 风险登记行）

**Interfaces:**
- Consumes: Task 2 的 caps（`push_constants_supported`/`hiz_supported`/`shader_variant`）；Task 5 的 bindings。
- Produces: renderer 目录内所有 `#ifdef ENGINE_VULKAN` 清零（本 Task 完成除 Task 7 显式列出的 compute/RT/UI 文件外的全部）；`RHIPipelineDesc` 的 `terrain_layout`/`water_layout`/`combined_aa_layout`/`combined_color_layout`/`color_format`/`mrt_attachment_count`/`mrt_formats` 注释改写为后端中性的 pipeline contract 表述（每个字段保持 VK 真实消费 + GL 忽略语义，禁止改名伪装）。

- [ ] **Step 1: 写失败测试——pipeline contract 字段消费断言**

test_rhi_capabilities.c 追加：

```c
TEST(pipeline_desc_contract_fields_have_defined_defaults)
{
    RHIPipelineDesc desc;
    memset(&desc, 0, sizeof(desc));
    ASSERT_EQ((int)desc.color_format, (int)RHI_FORMAT_R8G8B8A8_UNORM); /* 0 = swapchain pass */
    ASSERT_EQ(desc.mrt_attachment_count, 0u);
    ASSERT_FALSE(desc.terrain_layout);
    ASSERT_FALSE(desc.water_layout);
    ASSERT_FALSE(desc.combined_aa_layout);
    ASSERT_FALSE(desc.combined_color_layout);
    ASSERT_FALSE(rhi_handle_valid(rhi_pipeline_create(NULL, &desc)));
    /* MRT 校验保持既有规则（与 rhi_mrt_formats_valid 一致）。 */
    ASSERT_FALSE(rhi_mrt_formats_valid(NULL, 0u));
}
```

同时给 Task 5 Step 5 的交叉对照 gate 增补一条断言：四个布局布尔对应的 shader（terrain_vk/water_vk/combined_taa_fxaa_vk/combined_color_vk）反射结果与该布局的期望 offset 表一致——即「字段 → shader → 反射布局」三方闭环，这就是字段的真实消费证明。

- [ ] **Step 2: 运行验证失败**

Run: `cmake --build build-vk --target test_rhi_capabilities test_shader_io && ctest --test-dir build-vk -R 'test_rhi_capabilities|test_shader_io' --output-on-failure`
Expected: 新增断言中反射闭环部分可能 FAIL（若某布局 shader 缺 push 块或命名漂移）——如实记录，Step 3 修。

- [ ] **Step 3: 最小实现 + 分支迁移**

先修 Step 2 暴露的反射闭环缺口（只许修反射器或测试期望转录错误；不许动 shader 布局）。然后逐文件迁移 renderer 分支，全部套用 Task 2 的规则 F2（shader 路径 → `shader_variant_path` + `caps.shader_variant`）；子系统 init 内缓存 `RHICapabilities`。deferred.c 的 5 处、post_process.c 的 4 处、terrain.c 的 4 处等按文件逐一 `grep -n 'ENGINE_VULKAN' <file>` 定位后改写。每文件改完立即编译（`cmake --build build-vk --target engine` 零警告）。

- [ ] **Step 4: Hi-Z / occlusion 能力化**

occlusion_cull.c 的分支改为 `caps.hiz_supported` 查询；初始化失败路径保持现有 CPU 视锥剔除回退（main.c:1234 `vis_task_fn` 族已存在）。**Hi-Z {1,1} NVIDIA 异常只登记不改码**：在 `docs/rhi_backend_evidence.md` 风险段追加一行「Hi-Z {1,1} / VK_ERROR_DEVICE_LOST（NVIDIA 616.56 混合 GPU）——未在健康设备复现，按 spec §7 不作为源码修复依据；`TV_ONLY_PSHADOW`/`TV_ONLY_GBUFFER` 隔离 gate 保留」。

- [ ] **Step 5: rhi.h pipeline contract 注释改写**

`RHIPipelineDesc` 的布局布尔与 MRT/color_format 字段注释改为后端中性契约（「pipeline 声明其 push 块布局契约；后端据此建立绑定。terrain_layout = terrain_vk.vert 的 push 布局契约……」），并在每个字段注释中指明其真实消费测试（Step 1 的闭环断言）。**不改字段名、不改语义。**

- [ ] **Step 6: oracle 验证**

Run: `cmake --build build-vk --target engine test_vulkan && ctest --test-dir build-vk -R '^test_vulkan$|test_rhi_capabilities|test_shader_io' --output-on-failure`（GL lane 同跑）
Expected: 全 PASS；golden MAE 不变；`grep -rc 'ENGINE_VULKAN\|ENGINE_RHI_BACKEND_' engine/src/renderer --include='*.c' | grep -v ':0'` 仅剩 rt_trace.c(2) + gpucull.c(1) + Task 7 负责的少数文件。

- [ ] **Step 7: Commit**

```bash
git add engine/src/renderer engine/src/rhi/rhi.h engine/tests/test_rhi_capabilities.c engine/tests/test_shader_io.c docs/rhi_backend_evidence.md
git commit -m "refactor(renderer): capability-contract migration for pipeline/MRT/depth/shadow/Hi-Z paths"
```

---

### Task 7: compute/indirect/HDR/ray tracing/UI 迁移 + native handle 逃生舱收敛

**Files:**
- Modify: `engine/src/renderer/gpucull.c`、`indirect_draw.c`、`occlusion_cull.c`（compute/indirect 能力查询收尾）
- Modify: `engine/src/renderer/tonemap.c`、`upscale.c`、`combined_post_process.c`（HDR 链残留分支）
- Modify: `engine/src/renderer/rt_trace.c`（2 处分支 + native handle 逃生舱收敛）
- Modify: `engine/src/renderer/sl_dlss.c`、`engine/src/renderer/sl_dlss_streamline_adapter.cpp`（native handle 封装进 `#if defined(ENGINE_RHI_BACKEND_VULKAN)` 块，fail-closed）
- Modify: `engine/src/ui/imgui.h`/`debug_ui.h` 实现文件、`engine/src/ui/myui_break.c`（1 处）、`engine/src/myui/myr/my_vgcanvas_break_rhi.c`（1 处）
- Modify: `engine/tests/test_sl_dlss.c`、`engine/tests/test_rt_trace.c`（fail-closed 断言）

**Interfaces:**
- Consumes: Task 2 caps（`compute_supported`/`indirect_draw_supported`/`shader_variant`）、`RHI_FEATURE_*` feature bits（rhi.h:85-89，RT 三项已有）；计划 A 交付的 `engine/src/rhi/rhi_native_vulkan.h`（`RHINativeDevice`/`rhi_acceleration_structure_get_vk_handle` 已迁入）。
- Produces: 逃生舱统一标记约定——允许保留的后端特定代码必须同时满足：(a) 包在 `#if defined(ENGINE_RHI_BACKEND_VULKAN)`（或未来对应后端宏）块内；(b) 紧邻注释 `/* RHI-ESCAPE: <原因> */`；(c) 非该后端编译时 fail-closed（返回 UNSUPPORTED/false，不崩不伪装）。Task 8 的 grep gate 以此标记为唯一白名单。

- [ ] **Step 1: 写失败测试——逃生舱 fail-closed 契约**

test_sl_dlss.c 追加（非 VK 编译单元下）：`sl_dlss_probe` 返回 false 且 `out_result` 置 UNSUPPORTED 语义；`sl_dlss` 全部公开入口在 device 为 NULL 或后端非 VK 时不崩溃。test_rt_trace.c 追加：`rt_trace_probe(NULL, RHI_HANDLE_NULL, pixel)` 返回 false 且 `rt_trace_last_error()` 非 NULL。先跑确认现有行为，把「现状即契约」钉死；任何 FAIL 先修实现。

- [ ] **Step 2: 运行验证失败/现状**

Run: `ctest --test-dir build-vk -R 'test_sl_dlss|test_rt_trace' --output-on-failure`
Expected: 记录现状；FAIL 项进 Step 3 修。

- [ ] **Step 3: 最小实现——rt_trace 与 sl_dlss 逃生舱封装**

rt_trace.c：2 处 `ENGINE_VULKAN` 分支改为 feature bit 查询（`(caps.feature_bits & RHI_FEATURE_RAY_QUERY) != 0`）；`rhi_acceleration_structure_get_vk_handle` 的调用点改为（RHI-ESCAPE 注释在 `#if` 上一行，与 Task 8 gate 的配对规则一致）：

```c
/* RHI-ESCAPE: RT 诊断需要 VkAccelerationStructureKHR 原生句柄，仅 VK 后端
 * 可达；其他后端编译期裁剪，fail-closed。 */
#if defined(ENGINE_RHI_BACKEND_VULKAN)
    void *native = NULL;
    if (!rhi_acceleration_structure_get_vk_handle(dev, tlas, &native))
        return false;
    /* 以下为既有 native 句柄消费代码（rt_trace.c 内 probe 构造），原样保留。 */
#else
    return false;
#endif
```

（`#include <rhi/rhi_native_vulkan.h>` 放文件顶部同样的 RHI-ESCAPE 块内。）

sl_dlss.c：`sl_dlss_probe`（:282）与 native command buffer 获取（:260-278）整体包进 `#if defined(ENGINE_RHI_BACKEND_VULKAN)` 块 + `RHI-ESCAPE` 注释；`#else` 分支 `g_cpp_adapter` 不初始化、probe 返回 false。sl_dlss_streamline_adapter.cpp 本身已被 `engine/CMakeLists.txt` 的 `if(WIN32 AND STREAMLINE_ROOT)` 门控，块内补 `ENGINE_RHI_BACKEND_VULKAN` 断言注释即可，不改构建逻辑。

- [ ] **Step 4: compute/indirect/HDR/UI 分支迁移**

gpucull.c/indirect_draw.c/occlusion_cull.c 残留分支 → `caps.compute_supported`/`caps.indirect_draw_supported`；HDR 链（tonemap/upscale/combined_post_process）残留 shader 分支 → 规则 F2。UI 三处（myui_break.c:1、my_vgcanvas_break_rhi.c:1 及 imgui/debug_ui 内的 shader 选择）同 F2。每文件 `grep -n ENGINE_VULKAN` 清零后编译验证。

- [ ] **Step 5: oracle 验证**

Run: `cmake --build build-vk --target engine test_vulkan && ctest --test-dir build-vk -R '^test_vulkan$|test_sl_dlss|test_rt_trace' --output-on-failure`（GL lane 同跑）
Expected: 全 PASS；golden 不变；`grep -rn 'ENGINE_VULKAN\|ENGINE_RHI_BACKEND_' engine/src/renderer engine/src/ui engine/src/myui engine/src/main.c` 仅剩带 `RHI-ESCAPE` 注释的逃生舱块。

- [ ] **Step 6: Commit**

```bash
git add engine/src/renderer engine/src/ui engine/src/myui engine/tests/test_sl_dlss.c engine/tests/test_rt_trace.c
git commit -m "refactor(renderer): converge compute/indirect/HDR/RT/UI on capability contract; fence native-handle escape hatches"
```

---

### Task 8: capability contract 收尾审计 + 全平台构建矩阵回归

**Files:**
- Create: `engine/tests/test_renderer_backend_token_gate.cmake`
- Modify: `engine/CMakeLists.txt`（注册该 `cmake -P` 契约测试）
- Modify: `engine/src/rhi/rhi.h:596`（确认 deprecated 注释与 Task 5 文案一致；本 Task 不删旧 API——删除属 OpenGL 退役计划 F）

**Interfaces:**
- Consumes: Task 1-7 全部产物；`test_rhi_backend_internal_contract.cmake:180-208` 的 `cmake -P` grep-gate 惯例（计划 A 重写后的版本）。
- Produces: `test_renderer_backend_token_gate`（CTest，headless label），`engine/tests/test_renderer_backend_token_gate.cmake` 完整内容：

```cmake
# test_renderer_backend_token_gate.cmake — renderer 消费面后端分支 token 审计。
# 用法: cmake -DENGINE_SRC=<repo>/engine/src -P test_renderer_backend_token_gate.cmake
# 白名单：命中行本身或上一行带 RHI-ESCAPE 注释（Task 2 规则 F5 / Task 7 约定）。
if(NOT DEFINED ENGINE_SRC)
  message(FATAL_ERROR "ENGINE_SRC not set")
endif()
set(scan_files "${ENGINE_SRC}/main.c")
file(GLOB renderer_srcs "${ENGINE_SRC}/renderer/*.c" "${ENGINE_SRC}/renderer/*.h")
file(GLOB ui_srcs       "${ENGINE_SRC}/ui/*.c"       "${ENGINE_SRC}/ui/*.h")
file(GLOB myui_srcs     "${ENGINE_SRC}/myui/myr/*.c")
list(APPEND scan_files ${renderer_srcs} ${ui_srcs} ${myui_srcs})

set(violations "")
set(escape_count 0)
foreach(f IN LISTS scan_files)
  file(STRINGS "${f}" lines)
  set(prev_line "")
  set(lineno 0)
  foreach(line IN LISTS lines)
    math(EXPR lineno "${lineno} + 1")
    if(line MATCHES "ENGINE_VULKAN" OR line MATCHES "ENGINE_RHI_BACKEND_")
      if(line MATCHES "RHI-ESCAPE" OR prev_line MATCHES "RHI-ESCAPE")
        math(EXPR escape_count "${escape_count} + 1")
      else()
        string(APPEND violations "${f}:${lineno}: ${line}\n")
      endif()
    endif()
    if(line MATCHES "rhi_pipeline_get_uniform_location")
      string(APPEND violations "${f}:${lineno}: legacy uniform query: ${line}\n")
    endif()
    set(prev_line "${line}")
  endforeach()
endforeach()
if(NOT violations STREQUAL "")
  message(FATAL_ERROR "backend-token gate violations:\n${violations}")
endif()
message(STATUS "backend-token gate OK (${escape_count} RHI-ESCAPE whitelisted hits)")
```

CMakeLists.txt 注册块（放在 test_rhi_backend_internal_contract 注册旁）：

```cmake
    add_test(NAME test_renderer_backend_token_gate
        COMMAND ${CMAKE_COMMAND} -DENGINE_SRC=${CMAKE_CURRENT_SOURCE_DIR}/src
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_renderer_backend_token_gate.cmake)
    set_tests_properties(test_renderer_backend_token_gate PROPERTIES LABELS headless)
```

- [ ] **Step 1: 写失败 gate 并验证它确实会红**

先临时在 engine/src/renderer/ 某文件加一行 `// ENGINE_VULKAN probe`，注册并运行 gate：

Run: `ctest --test-dir build-vk -R test_renderer_backend_token_gate --output-on-failure`
Expected: FATAL_ERROR 命中 probe 行。删除 probe。

- [ ] **Step 2: 验证 gate 变绿**

Run: `ctest --test-dir build-vk -R test_renderer_backend_token_gate --output-on-failure`
Expected: PASS（仅 RHI-ESCAPE 白名单命中被显式列出并计数，计数写进测试输出供台账引用）。

- [ ] **Step 3: 全平台构建矩阵回归**

逐项执行并记录（没有的 lane 标 UNAVAILABLE，不伪造）：
- 本机 Windows VK：`cmake --build build-vk && ctest --test-dir build-vk --output-on-failure`（全 label，graphics 含 test_vulkan golden）
- 本机 Windows GL（如可配）：同命令另建 `build-gl` 配置（`-DENGINE_RHI_BACKEND=opengl`）
- Linux X11 GL/VK、Wayland、macOS：CI lanes（`gl`/`vk`/`wayland-gl`/`wayland-vk`/`macos-vulkan`）——push 后以 CI run 为收据
- headless：`ctest -L headless` 全绿

Run（本机部分）: `ctest --test-dir build-vk --output-on-failure 2>&1 | tail -20`
Expected: 100% tests passed（环境依赖项以 77 skip 计，不算失败）。

- [ ] **Step 4: Commit**

```bash
git add engine/tests/test_renderer_backend_token_gate.cmake engine/CMakeLists.txt engine/src/rhi/rhi.h
git commit -m "test(rhi): renderer backend-token audit gate; capability contract migration complete"
```

---

### Task 9: 文档与 push

**Files:**
- Modify: `docs/Architecture_Overview.md`（renderer 分层：RHI 层新增 capability contract 与 reflection 绑定两小节，说明 `RHIPipelineBindings` 数据流与 `RHI-ESCAPE` 逃生舱约定）
- Modify: `docs/rhi_backend_evidence.md`（计划 A 已建；追加计划 E 完成度：各 Task 的 commit hash、oracle 验证 lane、token 审计计数、Hi-Z 风险登记行）

- [ ] **Step 1: 前置核实**

Run: `git status --porcelain && git log --oneline -12`
Expected: 工作树干净；Task 1-8 的 commit 链完整。`docs/rhi_backend_evidence.md` 必须已存在（计划 A 交付物）——不存在则停止并上报前置条件缺口。

- [ ] **Step 2: 更新文档**

Architecture_Overview.md 的 RHI 章节补三段：(1) capability contract——`RHICapabilities` 字段总表（含本计划新增 6 项）与消费规则；(2) shader 绑定——`shader_reflect_push_constants`（std430）为权威布局源，`rhi_pipeline_bindings_create/resolve` 取代逐名查询，旧 API deprecated 待计划 F 删除；(3) 逃生舱——`RHI-ESCAPE` 标记 + grep gate。rhi_backend_evidence.md 追加「计划 E 迁移完成度」小节：每 Task 一行（commit、验证命令、lane、结果），token 审计计数（残留 `RHI-ESCAPE` 块数量与位置），Hi-Z 风险登记行复述。

- [ ] **Step 3: 全绿复核**

Run: `ctest --test-dir build-vk --output-on-failure && ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure`
Expected: 全 PASS（含 graphics lane）。

- [ ] **Step 4: Commit + push**

```bash
git add docs/Architecture_Overview.md docs/rhi_backend_evidence.md
git commit -m "docs(rhi): plan E renderer ABI migration evidence and architecture layering"
git push origin master
```

Expected: push 成功；CI lanes 结果回执补记进 `docs/rhi_backend_evidence.md`（后续小 commit）。

---

## Definition of Done（计划 E 全绿判据）

1. `engine/src/main.c`、`engine/src/renderer/`、`engine/src/ui/`、`engine/src/myui/` 中 `ENGINE_VULKAN`/`ENGINE_RHI_BACKEND_` token 仅存在于带 `RHI-ESCAPE` 注释的白名单块内（gate 强制）。
2. `rhi_pipeline_get_uniform_location` 调用点残留 = 0（仅 rhi.h 声明 + 两后端实现）；所有 uniform 绑定值来源于 `shader_reflect_push_constants`（std430）反射，VK 手写 offset 表已删除。
3. 每个迁移批次都有 golden/readback oracle 通过记录（VK 本机 + GL lane）；无一批次靠目测。
4. `RHICapabilities` 新字段（push_constants/max_push_constant_size/hiz/compute/indirect/shader_variant）在每个后端有真实消费 + 契约测试。
5. `ctest` 全 label 绿（77 skip 除外）；`-Werror` 零警告。
6. `docs/rhi_backend_evidence.md` 含计划 E 完成度记录；Hi-Z {1,1} 异常仅登记未改码。
7. 全部 commit 已 push 到 `origin master`。

## 风险登记（本计划新增/承接）

| 风险 | 缓解 |
|---|---|
| 反射 offset 与 shaderc 实际布局不一致 | Task 5 Step 5 交叉对照 gate（对照现状手写表）+ 每批 golden oracle；先修反射器，禁止改表迁就 |
| main.c 迁移破坏帧时序（frame_index 双槽、vsync、resize） | Task 2 oracle 用 test_vulkan golden + R577 捕获窗口；main.c 帧循环调用点（:6050/:8533/:8550/:4343）只改分支结构不改调用序 |
| Hi-Z {1,1} / NVIDIA 616.56 device-lost | 只登记（spec §7）；`TV_ONLY_PSHADOW`/`TV_ONLY_GBUFFER` 隔离 gate 保留；健康设备复现前不改源码 |
| GL lane 本机不可用 | GL 验证以 Linux Xvfb/CI `gl` lane 为收据；禁止把「未跑」写成「通过」 |
| 批次迁移中途上下文耗尽 | 每批独立 commit 即天然检查点；70% 压缩交接规则（Global Constraints） |
