# 纯 C 游戏引擎 — 执行计划

> 基于 `PureC_Engine_DeepDive.md` 中确定的最优方案，制定分阶段实施路线图。
> 核心策略: **垂直切片优先** — 每个阶段产出可运行的 demo，而非逐模块堆叠。

---

## 0. 执行策略

### 为什么不用"自底向上"？

传统自底向上 (先 core → math → rhi → renderer) 的问题:
- 前 2 个月没有任何可视化输出
- API 设计在第一次集成时必然推翻
- 动力枯竭风险极高

### 采用: 垂直切片 + 渐进重构

```
Phase 0:  ████░░░░░░  开窗口，画像素        ← 1 周内可运行
Phase 1:  ██████░░░░  画三角形              ← RHI 最小可用
Phase 2:  ████████░░  加载模型，渲染场景     ← 完整渲染管线 v1
Phase 3:  ██████████  ECS + 物理 + 游戏      ← 完整引擎
```

每个 Phase 内部按依赖顺序构建，但 Phase 之间通过快速 hack 连接——先跑通，再替换。

---

## 1. 模块依赖图

```
                    ┌──────────┐
                    │ Platform │ ← 最底层：窗口、文件、时间、输入
                    └────┬─────┘
                         │
              ┌──────────┼──────────┐
              │          │          │
         ┌────▼───┐ ┌───▼────┐ ┌──▼───┐
         │  Core  │ │  Math  │ │ Task │
         │ alloc  │ │ simd   │ │ ws   │
         │ ds     │ │ vec/mat│ │ deque│
         └────┬───┘ └───┬────┘ └──┬───┘
              │         │         │
              └─────┬───┘─────────┘
                    │
               ┌────▼────┐
               │   RHI   │ ← GPU 抽象层
               └────┬────┘
                    │
          ┌─────────┼──────────┐
          │         │          │
    ┌─────▼──┐ ┌───▼────┐ ┌──▼───┐
    │  ECS   │ │ Asset  │ │  UI  │
    │ arch   │ │  vfs   │ │ imgui│
    └─────┬──┘ └───┬────┘ └──┬───┘
          │         │         │
          └────┬────┘─────────┘
               │
          ┌────▼────┐
          │Renderer │ ← Render Graph + Clustered Forward
          └────┬────┘
               │
         ┌─────┼─────┐
         │     │     │
    ┌────▼──┐  │  ┌──▼───┐
    │Physics│  │  │Audio │
    └───────┘  │  └──────┘
               │
          ┌────▼────┐
          │  Game   │ ← 脚本 + 游戏逻辑
          └─────────┘
```

---

## 2. 分阶段执行计划

### Phase 0: Hello Window (基础骨架) — **COMPLETED**

**目标**: 打开窗口，响应输入，60fps 循环。无任何渲染。

**依赖链**: `CMake → Core → Platform → 主循环`

| # | 任务 | 产出文件 | 详情 |
|---|------|----------|------|
| 0.1 | CMake 项目骨架 | `CMakeLists.txt`, `src/engine.c/h` | C11 标准，编译选项 `-Wall -Wextra -Werror`，Unity Build 选项 |
| 0.2 | Core: 日志 | `src/core/log.c/h` | 分级日志 (TRACE/DEBUG/INFO/WARN/ERROR)，带文件:行号 |
| 0.3 | Core: 断言 | `src/core/assert.c/h` | 编译期 `_Static_assert` + 运行期带消息断言 |
| 0.4 | Core: 内存分配器 | `src/core/alloc.c/h` | Arena (inline), Heap (vtable), 调试分配器 |
| 0.5 | Core: 字符串 slice | `src/core/string.c/h` | `Str{ptr, len}` 非零终止，哈希，比较 |
| 0.6 | Core: 动态数组 | `src/core/array.c/h` | 宏生成泛型 `Vec(T)`，支持自定义分配器 |
| 0.7 | Core: 哈希表 | `src/core/hashmap.c/h` | Robin Hood 开放寻址，SWAR 密集元数据 |
| 0.8 | Platform: Win32 窗口 | `src/platform/window_win32.c` | `CreateWindowEx`, 消息循环 |
| 0.9 | Platform: X11 窗口 | `src/platform/window_x11.c` | `XOpenDisplay`, 事件循环 |
| 0.10 | Platform: 输入事件 | `src/platform/input.c/h` | SPSC 环形缓冲区 + InputState 快照 |
| 0.11 | Platform: 高精度计时 | `src/platform/time.c/h` | `QueryPerformanceCounter` / `clock_gettime` |
| 0.12 | 主循环 + 引擎入口 | `src/engine.c` | 固定时间步 + 可变渲染帧率 |

**交付物**: 双击可执行文件 → 打开 800x600 窗口 → ESC 退出 → 控制台打印 FPS

**验证标准**:
- [ ] Windows + Linux 均可编译运行
- [ ] 窗口稳定 60fps，无闪烁
- [ ] 按键/鼠标事件正确打印到日志
- [ ] 无内存泄漏 (DebugAlloc 验证)
- [ ] 编译零 warning

---

### Phase 1: Hello Triangle (RHI 最小可用)

**目标**: 通过 RHI 抽象层渲染一个三角形，验证 GPU 管线通畅。

**依赖链**: `Math → RHI(OpenGL) → 三角形`

| # | 任务 | 产出文件 | 详情 |
|---|------|----------|------|
| 1.1 | Math: 基础类型 | `src/math/types.h` | Vec2/3/4, Mat4, Quat — 列主序, `_Static_assert` 大小 |
| 1.2 | Math: 标量实现 | `src/math/scalar.c` | 所有运算的 C 标量版本 (作为参考和回退) |
| 1.3 | Math: SSE2 实现 | `src/math/sse2.c` | `static inline` 封装 simdf 原语 |
| 1.4 | Math: NEON 实现 | `src/math/neon.c` | ARM 等价实现 |
| 1.5 | RHI: 公共接口 | `src/rhi/rhi.h` | Device + Handle + CmdBuffer + 同步原语 类型定义 |
| 1.6 | RHI: 后端框架 | `src/rhi/rhi.c` | 代际句柄的资源池管理, 设备创建/销毁 |
| 1.7 | RHI: OpenGL 后端 | `src/rhi/rhi_gl.c` | 通过 glad 加载 OpenGL 4.5, 实现 RHI 接口 |
| 1.8 | RHI: 基础着色器 | `shaders/triangle.vert/frag` | GLSL hello triangle |
| 1.9 | 集成: 三角形 demo | `src/main.c` | 初始化 RHI → 创建管线 → 画三角形 → present |

**交付物**: 窗口中显示一个彩色三角形

**验证标准**:
- [ ] OpenGL 4.5 后端正常工作
- [ ] 帧率稳定 60fps
- [ ] 窗口 resize 正确响应 (视口重建)
- [ ] 资源创建/销毁无泄漏 (RHI 资源池检查)

**关键决策 — 为什么先做 OpenGL 而非 Vulkan?**

```
OpenGL:  1 周可出三角形  (glad + ~500 行代码)
Vulkan:  3-4 周出三角形  (instance/device/swapchain/renderpass/pipeline/framebuffer ~3000 行)

先用 OpenGL 跑通整个引擎管线，再实现 Vulkan 后端替换。
```

---

### Phase 2: Hello Scene (完整渲染 v1)

**目标**: 加载 glTF 模型，纹理贴图，基础光照，相机控制。

**依赖链**: `Task → Asset/VFS → RHI 扩展 → Renderer v1 → glTF 场景`

| # | 任务 | 产出文件 | 详情 |
|---|------|----------|------|
| 2.1 | Task: 线程基础 | `src/task/thread.c/h` | `thrd_t` 封装，线程亲和性 |
| 2.2 | Task: Chase-Lev Deque | `src/task/work_stealing.c/h` | 无锁双端队列实现 |
| 2.3 | Task: 任务系统 | `src/task/task.c/h` | Worker 线程池 + parallel_for + wait-with-work |
| 2.4 | Asset: VFS | `src/asset/vfs.c/h` | 目录挂载 + 路径规范化 |
| 2.5 | Asset: 基础加载器 | `src/asset/loader.c/h` | 注册表 + 异步加载队列 |
| 2.6 | Asset: glTF 加载 | `src/asset/loader_gltf.c` | 基于 cgltf (单头文件库) |
| 2.7 | Asset: 纹理加载 | `src/asset/loader_texture.c` | 基于 stb_image, KTX 支持 |
| 2.8 | RHI: 纹理支持 | `src/rhi/rhi_gl.c` (扩展) | `create_texture`, `update_texture`, sampler |
| 2.9 | RHI: Uniform Buffer | `src/rhi/rhi_gl.c` (扩展) | UBO 支持, `bind_descriptor_set` |
| 2.10 | Renderer: 相机 | `src/renderer/camera.c/h` | 透视相机, lookat, FPS 相机控制 |
| 2.11 | Renderer: Mesh 管理 | `src/renderer/mesh.c/h` | 顶点/索引缓冲, submesh |
| 2.12 | Renderer: 材质 v1 | `src/renderer/material.c/h` | shader + uniform 参数 + texture 槽位 |
| 2.13 | Renderer: 前向渲染 | `src/renderer/forward.c/h` | 简单 Forward, 逐对象渲染 |
| 2.14 | Renderer: 基础光照 | `shaders/pbr.vert/frag` | Blinn-Phong / 简化 PBR, 平行光 + 环境光 |
| 2.15 | 集成: glTF 场景 demo | `src/main.c` | 加载 glTF → 渲染 → WASD 相机控制 |

**交付物**: 加载并渲染一个带纹理的 glTF 模型，WASD + 鼠标自由相机

**验证标准**:
- [ ] 加载 Sponza / DamagedHelmet 等标准 glTF 模型
- [ ] 纹理正确映射
- [ ] 光照方向可调
- [ ] 相机控制流畅 (60fps)
- [ ] 异步加载不卡主线程

---

### Phase 3: Engine Complete (ECS + 物理 + 完整渲染) — **COMPLETED**

**目标**: 完整的游戏引擎循环 — ECS 驱动逻辑，物理碰撞，高级渲染。

**实际实现**: 核心模块全部完成并集成，demo 运行通过。

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 3.1 | ECS: Archetype+Chunk 存储 | `src/ecs/ecs.c/h` | ✅ 完成 |
| 3.2 | ECS: World 管理 + 代际验证 | `src/ecs/ecs.c/h` | ✅ 完成 |
| 3.3 | ECS: 查询系统 + Chunk 迭代器 | `src/ecs/ecs.c/h` | ✅ 完成 |
| 3.4 | Renderer: 视锥剔除 | `src/renderer/cull.c/h` | ✅ 完成 |
| 3.5 | Renderer: Shadow Map | `src/rhi/rhi.h` (FBO扩展) | ✅ 完成 |
| 3.6 | Physics: AABB 刚体 | `src/physics/physics.c/h` | ✅ 完成 |
| 3.7 | Task: 线程池 + Work Stealing | `src/task/task.c/h` | ✅ 完成 |
| 3.8 | Audio: miniaudio 后端 | `src/audio/audio.c/h` | ✅ 完成 |
| 3.9 | UI: 调试文字覆盖 | `src/ui/debug_ui.c/h` | ✅ 完成 |
| 3.10 | Engine: 集成 demo | `src/main.c` | ✅ 完成 |

**修复的关键 Bug**:
1. `world_add_component` 无限递归 → 重写为非递归的 archetype 迁移
2. `Entity.index` 从未设置 → `world_create_entity` 中添加 `entities[idx].index = idx`
3. `memcpy(NULL, ..., 0)` UB → 空 archetype 的 `key.ids` 为 NULL 时跳过拷贝
4. `archetype_alloc_slot` 辅助函数提取，避免重复 chunk 分配逻辑

**交付物**: 技术演示 — 10 个 ECS 实体 + 11 个物理刚体 + glTF 渲染 + 调试 UI

**验证结果**:
- [x] ECS 实体创建/组件添加正常运行
- [x] 物理刚体创建 (AABB) 
- [x] glTF 模型加载
- [x] Audio 系统初始化
- [x] Task 系统 (2 worker 线程)
- [x] 调试 UI 显示 FPS/实体数/物理体数/Draw Calls
- [x] 编译零 warning (除一个预存在的 clang-tidy integer-division 提示)
 - [x] Vulkan 后端 (Phase 5A 完成, 1757 FPS, 零验证错误)
- [x] PBR 渲染管线 (Phase 6A 完成, Cook-Torrance BRDF, Reinhard tone mapping, gamma correction)
- [x] VFS + .pak 资源管线 (Phase 4F 完成, 20 文件打包验证)
- [x] 10,000 实体压力测试 (Phase 5B 完成, 10K instanced entities, ~137 FPS Vulkan, 零验证错误)

---

### Phase 4: Production Ready (打磨 + 扩展) — **COMPLETED**

**目标**: 可用于实际游戏开发的引擎。

**策略**: Phase 4 拆分为子阶段 4A-4F，每个子阶段产出可运行的 demo 增量。

#### Phase 4A: Skybox + IBL + Frame Profiler — **COMPLETED**

**目标**: 添加 HDR 天空盒、基于图像的光照、帧级性能分析器。

| # | 任务 | 产出文件 | 详情 |
|---|------|----------|------|
| 4A.1 | Profiler: CPU 帧计时器 | `src/core/profiler.c/h` | 嵌入式 profiler, push/pop region, 帧统计 |
| 4A.2 | RHI: Cubemap 支持 | `src/rhi/rhi.h` (扩展) | `RHICubemap` handle, cubemap create/bind |
| 4A.3 | Renderer: Skybox | `src/renderer/skybox.c/h` | HDR cubemap 天空, 全屏四边形渲染 |
| 4A.4 | Renderer: IBL 环境光 | `shaders/blinn_phong.frag` (扩展) | 从 cubemap 采样环境光, 简化 PBR |
| 4A.5 | Shader: skybox.vert/frag | `shaders/skybox.vert/frag` | 天空盒专用 shader |
| 4A.6 | 集成: Phase 4A demo | `src/main.c` (更新) | 天空盒渲染 + profiler overlay |

**交付物**: 场景带有 HDR 天空盒，profiler 显示 CPU/GPU 帧时间

#### Phase 4B: Hot Reload + Resource Versioning — **COMPLETED**

**目标**: 修改 shader/纹理后无需重启即可看到效果。

| # | 任务 | 产出文件 | 详情 |
|---|------|----------|------|
| 4B.1 | Platform: 文件监视 | `src/platform/filewatch.c/h` | inotify (Linux) / ReadDirectoryChangesW (Win) |
| 4B.2 | Asset: 版本号管理 | `src/asset/asset.c` (扩展) | 资源 generation counter, 脏标记 |
| 4B.3 | Asset: Shader 热重载 | `src/asset/asset.c` (扩展) | 检测 shader 修改 → 重新编译 → 替换 GPU 程序 |
| 4B.4 | Asset: 纹理热重载 | `src/asset/asset.c` (扩展) | 检测纹理修改 → 重新上传 GPU |

#### Phase 4C: Script Engine — **COMPLETED**

**目标**: 引擎 API 导出到 Lua，支持热重载脚本。

| # | 任务 | 产出文件 | 详情 |
|---|------|----------|------|
| 4C.1 | Script: Lua 运行时集成 | `src/script/script.c/h` | Lua 5.4 嵌入, 状态管理 |
| 4C.2 | Script: ECS 绑定 | `src/script/bind_ecs.c` | entity_create, add_component, query |
| 4C.3 | Script: Transform 绑定 | `src/script/bind_transform.c` | pos/rot/scale 读写 |
| 4C.4 | Script: 热重载 | `src/script/script.c` (扩展) | 监视 .lua 文件变化，自动重载 |

#### Phase 4D: Physics Improvements — **COMPLETED**

**目标**: CCD 防隧穿 + 角色控制器。

| # | 任务 | 产出文件 | 详情 |
|---|------|----------|------|
| 4D.1 | Physics: CCD | `src/physics/physics.c` (扩展) | 连续碰撞检测, sweep test |
| 4D.2 | Physics: 角色控制器 | `src/physics/character.c/h` | 胶囊碰撞, 地面检测, 斜坡滑动 |
| 4D.3 | Physics: 场景查询 | `src/physics/query.c/h` | Raycast, SphereOverlap |

#### Phase 4E: Advanced Rendering — **COMPLETED**

**目标**: GPU 粒子系统 + 地形渲染。

| # | 任务 | 产出文件 | 详情 |
|---|------|----------|------|
| 4E.1 | RHI: Compute Shader | `src/rhi/rhi.h` (扩展) | dispatch compute, SSBO |
| 4E.2 | Renderer: GPU 粒子 | `src/renderer/particles.c/h` | Compute shader 更新, instanced 渲染 |
| 4E.3 | Renderer: 地形 | `src/renderer/terrain.c/h` | Heightmap, LOD, chunked 渲染 |

##### Phase 5A: Vulkan RHI Backend — **COMPLETED**

**目标**: 实现 Vulkan 后端，与 OpenGL 后端并驾齐驱，所有验证通过。

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 5A.1 | Vulkan: Instance + Device + Swapchain | `src/rhi/rhi_vk.c` | ✅ 完成 |
| 5A.2 | Vulkan: Command Buffer + Render Pass | `src/rhi/rhi_vk.c` | ✅ 完成 |
| 5A.3 | Vulkan: Pipeline 创建 (动态顶点格式) | `src/rhi/rhi_vk.c` | ✅ 完成 |
| 5A.4 | Vulkan: Push Constants (uniform 上传) | `src/rhi/rhi_vk.c` | ✅ 完成 |
| 5A.5 | Vulkan: 纹理创建 + 描述符集 + 采样器 | `src/rhi/rhi_vk.c` | ✅ 完成 |
| 5A.6 | Vulkan: 缓冲区创建 (vertex/index/uniform) | `src/rhi/rhi_vk.c` | ✅ 完成 |
| 5A.7 | Vulkan: Shader 编译 (GLSL→SPIR-V via shaderc) | `src/rhi/rhi_vk.c` | ✅ 完成 |
| 5A.8 | Vulkan: 全屏三角形天空盒管线 | `shaders/skybox_vk.vert/frag` | ✅ 完成 |
| 5A.9 | Vulkan: Blinn-Phong 着色器 | `shaders/blinn_phong_vk.vert/frag` | ✅ 完成 |
| 5A.10 | Vulkan: 集成 demo (engine_demo on Vulkan) | `src/main.c` | ✅ 完成 |

**修复的关键 Bug**:
1. Semaphore 复用 → `render_semaphores` 按 swapchain image 数量动态分配
2. Destroy in-use resources → `vkDeviceWaitIdle` → 升级为 `vk_wait_frames()` fence-based wait
3. Pipeline 线性扫描 → `current_pipeline_data` cached in `rhi_cmd_bind_pipeline`
4. 描述符集更新 in-use → 动态分配 per-frame 描述符池 + 每帧 reset
5. 天空盒深度函数 → `RHIPipelineDesc.depth_compare_lequal/depth_write_disable` pipeline flags
6. Texture upload → `vkDeviceWaitIdle` 升级为 per-upload fence

**性能**:
- engine_demo: **1757 FPS** (Vulkan) vs ~100-400 FPS (OpenGL)
- test_vulkan: 500 frames, min 1.6ms/frame, zero validation errors
- `vkDeviceWaitIdle` 降至 3 处 (swapchain rebuild, shutdown, device destroy)
- shaderc compiler cached across compiles

**交付物**: `cmake -B build -DENGINE_VULKAN=ON && cmake --build build && ./build/engine_demo`

---

##### Phase 5B: Clustered Forward Lighting — **COMPLETED**

**目标**: CPU-clustered forward lighting with texel buffers, supporting 256+ point lights on both GL and Vulkan backends.

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 5B.1 | RHI: Texel buffer support (`RHI_BUFFER_USAGE_TEXEL`) | `src/rhi/rhi.h`, `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 5B.2 | RHI: `rhi_cmd_bind_texel_buffers()` (dual TBO bind) | `src/rhi/rhi.h`, `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 5B.3 | Light system: CPU cluster culling (16×8×24 grid) | `src/renderer/lighting.c/h` | ✅ 完成 |
| 5B.4 | Clustered Blinn-Phong shaders (Vulkan SPIR-V) | `shaders/blinn_phong_clustered_vk.vert/frag` | ✅ 完成 |
| 5B.5 | Clustered Blinn-Phong shaders (OpenGL GLSL) | `shaders/blinn_phong_clustered.vert/frag` | ✅ 完成 |
| 5B.6 | Pipeline-aware push constant offset mapping | `src/rhi/rhi_vk.c` | ✅ 完成 |
| 5B.7 | Render loop integration: 32 orbiting point lights | `src/main.c` | ✅ 完成 |

**架构决策**:
- TBO (texel buffer) over SSBO — works through existing texture infrastructure
- CPU culling over GPU compute — no compute shader RHI support yet
- Cluster grid 16×8×24 = 3072 clusters, max 128 lights per cluster
- Vulkan: separate `texel_layout` descriptor set (set 1, bindings 0-1)
- OpenGL: texture units 1-2 for TBO textures

**性能**:
- Vulkan: ~245 FPS with 32 clustered point lights, zero validation errors
- OpenGL: ~269 FPS with 32 clustered point lights
- test_vulkan: ALL PASSED (500-frame + 1000-draw + 10K-entity stress tests)
- 10K instanced entities: ~137 FPS (single draw call, model matrices via TBO)

---

##### Phase 6A: PBR Rendering — **COMPLETED**

**目标**: 将 Blinn-Phong 升级为 Cook-Torrance PBR (metallic-roughness)，集成 Reinhard tone mapping + gamma correction。

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 6A.1 | PBR fragment shader (Vulkan SPIR-V) | `shaders/pbr_clustered_vk.frag` | ✅ 完成 |
| 6A.2 | PBR fragment shader (OpenGL GLSL) | `shaders/pbr_clustered.frag` | ✅ 完成 |
| 6A.3 | 集成到 engine_demo (替换 blinn_phong_clustered) | `src/main.c` | ✅ 完成 |

**PBR 实现**:
- Cook-Torrance BRDF: GGX 法线分布 + Smith-GGX 几何遮蔽 + Fresnel-Schlick
- Metallic-roughness 工作流 (metallic=0, roughness=0.5 硬编码，待材质系统扩展)
- Reinhard tone mapping: `color / (color + 1.0)`
- Gamma correction: `pow(color, 1/2.2)`
- 与 clustered forward lighting 完全集成

**性能**:
- Vulkan: ~245 FPS (与 Blinn-Phong 相同，PBR 计算成本可忽略)
- OpenGL: ~260 FPS
- test_vulkan: ALL PASSED

---

### Phase 4F: Resource Pipeline — **COMPLETED**

**目标**: 虚拟文件系统 + 离线资源打包 + .pak 加载。

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 4F.1 | VFS: 虚拟文件系统 | `src/asset/vfs.c/h` | ✅ 完成 |
| 4F.2 | Tool: 资源打包器 | `tools/packer.c` | ✅ 完成 |
| 4F.3 | Asset: VFS 集成 (texture + glTF 从 .pak 加载) | `src/asset/asset.c` (扩展) | ✅ 完成 |

**架构**:
- VFS 挂载点: 目录或 .pak 文件, 后挂载优先 (last-write-wins)
- .pak 格式: TAPE magic + FNV-1a 哈希文件表 + 原始数据 (无压缩)
- asset.c: `stbi_load_from_memory` + `cgltf_parse` 替代 stdio 直读
- `AssetCtx.vfs` 字段: NULL 时回退到原有 stdio 路径 (完全向后兼容)

**性能**:
- 20 文件 .pak (3.8MB) 加载验证通过
- 目录挂载 + .pak 挂载混合使用
- FNV-1a O(1) 哈希查找

---

### Phase 6B-6D: Offscreen FBO + Bloom + Shadow Mapping — **COMPLETED**

| # | 任务 | 状态 |
|---|------|------|
| 6B | Offscreen FBO RHI (Vulkan+GL) | ✅ 完成 |
| 6C | Bloom post-processing (10 shaders + PostProcess module) | ✅ 完成 |
| 6D | Shadow mapping (depth-only render pass, PBR shadow sampling) | ✅ 完成 |

**性能**: Vulkan ~230 FPS with bloom + shadows + PBR + 32 clustered lights

---

### Phase 7A: Vulkan Backend Hardening — **COMPLETED**

| # | 任务 | 状态 |
|---|------|------|
| 7A.1 | Dynamic viewport/scissor (eliminate VUID-08608 warnings) | ✅ 完成 |
| 7A.2 | Dynamic depth state (`rhi_cmd_set_depth_func_less/lequal`) | ✅ 完成 |
| 7A.3 | Cubemap support (`rhi_cubemap_create/destroy/bind`) | ✅ 完成 |
| 7A.4 | Mid-pass clears (`rhi_cmd_clear_color/depth`) | ✅ 完成 |
| 7A.5 | FIFO→Immediate present mode (fix swapchain deadlock on Intel) | ✅ 完成 |
| 7A.6 | Descriptor pool increase (2048 max sets, 1024 descriptors) | ✅ 完成 |

**结果**: 零 Vulkan 验证错误, ~230 FPS 稳定 (1600+ frames 无卡顿), 全部测试通过

---

### Phase 7B: Font Rendering + On-Screen Debug UI — **COMPLETED**

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 7B.1 | stb_truetype 字体图集 + 字形四边形批处理 | `src/ui/font.c/h` | ✅ 完成 |
| 7B.2 | 字体着色器 (alpha blend) | `shaders/font_vk.*`, `shaders/font.*` | ✅ 完成 |
| 7B.3 | RHI: alpha_blend + font_vertex + vec4 uniform | `rhi.h`, `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 7B.4 | 屏幕文字渲染 (替换 LOG_INFO) | `src/ui/debug_ui.c/h` | ✅ 完成 |
| 7B.5 | 集成到 main.c 渲染循环 | `main.c` | ✅ 完成 |

**架构**:
- stb_truetype 512x512 字形图集, 96 ASCII 字符 (32-127)
- FontVertex: pos(2f) + uv(2f) + color(4f) = 32 字节
- 每帧批处理所有文字四边形, 单次 draw call
- alpha blend 管线 (SRC_ALPHA, ONE_MINUS_SRC_ALPHA)
- 自定义 font_vertex 管线布局 (RHI 层支持)
- LiberationSans-Regular.ttf 18px

**性能**: ~256 FPS (vs 230 无字体), 零验证错误, 1376+ frames 稳定

---

### Phase 7C: GPU Instanced Rendering — **COMPLETED**

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 7C.1 | Instanced pipeline + shader loading | `main.c` (render_init) | ✅ 完成 |
| 7C.2 | Instance data upload (ECS transforms → texel buffer) | `main.c` (render loop) | ✅ 完成 |
| 7C.3 | Single instanced draw call replacing per-entity loop | `main.c` | ✅ 完成 |
| 7C.4 | RHI: is_instanced pipeline flag + uniform offset routing | `rhi.h`, `rhi_vk.c` | ✅ 完成 |

**架构**:
- 每帧收集所有 ECS Transform 到 f32[] → 上传到 texel buffer
- Instanced shader 从 `texelFetch(u_instances, gl_InstanceIndex * 4)` 读取 mat4 model
- 单次 `rhi_cmd_draw_indexed(count, instance_count)` 替代 N 次 draw call
- Push constant offset 路由: instanced (0-192) vs clustered (0-248) vs default (0-256)
- Fallback: 无 instanced pipeline 时回退到逐实体渲染

**性能**: ~220 FPS (10 entities instanced), 零验证错误, 1380+ frames 稳定

---

### Phase 7D: Skeletal Animation — **COMPLETED**

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 7D.1 | Skeleton module (joint hierarchy, pose evaluation, animation clips) | `src/animation/skeleton.c/h` | ✅ 完成 |
| 7D.2 | Math additions (mat4_translation/scaling/from_quat) | `src/math/math.c/h` | ✅ 完成 |
| 7D.3 | GPU skinning shaders (joint matrix texel buffer, 4-bone skinning) | `shaders/skinned_vk.*`, `shaders/skinned.*` | ✅ 完成 |
| 7D.4 | Skinned vertex format RHI support (pos+normal+uv+joints+weights = 64 bytes) | `rhi.h`, `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 7D.5 | Procedural animated test mesh (2-joint box, oscillating rotation) | `main.c` | ✅ 完成 |

**架构**:
- Skeleton: joint hierarchy with parent indices, inverse bind matrices, current pose
- GPU skinning: vertex shader reads `texelFetch(u_joints, jointIndex * 4)` for mat4
- 4-bone skinning per vertex (aJoints[4] + aWeights[4])
- Animation: keyframe interpolation (linear for T/S, slerp for rotation)
- Skinned vertex layout: pos(3f) + normal(3f) + uv(2f) + joints(4u) + weights(4f) = 64 bytes

**性能**: ~253 FPS (with animated skeleton), 零验证错误, 1460+ frames 稳定

---

### Phase 7E: glTF Skin/Animation Parsing — **COMPLETED**

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 7E.1 | SkinnedMesh struct + Scene skin data | `src/asset/asset.h` | ✅ 完成 |
| 7E.2 | glTF skin parsing (joints, inverse bind matrices) | `src/asset/asset.c` | ✅ 完成 |
| 7E.3 | glTF animation parsing (channels → AnimClip) | `src/asset/asset.c` | ✅ 完成 |
| 7E.4 | Main.c integration (load scene skeleton + animated meshes) | `src/main.c` | ✅ 完成 |

**架构**:
- SkinnedVertex: pos(3f)+normal(3f)+uv(2f)+joints(4u)+weights(4f) = 64 bytes
- asset_load_gltf: parses JOINTS_0/WEIGHTS_0, cgltf_skin (joints+IBM), cgltf_animation
- Joint parent mapping: iterates skin->joints to find parent index within joint list
- Animation: maps channels to joint indices, extracts keyframes with quaternion normalization
- Fallback: no skinned data in glTF → uses procedural test skeleton

**性能**: ~235 FPS, 零验证错误, 全部测试通过

---

### Phase 8A: Material System — **COMPLETED**

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 8A.1 | Material struct (albedo, MR, normal, emissive textures + PBR factors) | `src/asset/asset.h` | ✅ 完成 |
| 8A.2 | RHI: 5-binding descriptor layout + rhi_cmd_bind_material_textures | `rhi.h`, `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 8A.3 | glTF material parsing (metallic-roughness, normal, emissive, alpha) | `src/asset/asset.c` | ✅ 完成 |
| 8A.4 | PBR shaders: sample all 5 textures + normal mapping | `shaders/pbr_clustered_vk.frag`, `pbr_clustered.frag` | ✅ 完成 |
| 8A.5 | Fallback textures (white albedo, flat normal, black emissive, MR default) | `src/main.c` | ✅ 完成 |
| 8A.6 | Main.c integration (bind_material helper, per-mesh material binding) | `src/main.c` | ✅ 完成 |

**架构**:
- Material: albedo + metallic_roughness + normal_map + emissive (4 textures) + base_color[4], metallic/roughness/emissive factors, alpha_mode/cutoff
- Descriptor layout: binding 0=albedo, 1=shadow, 2=MR, 3=normal, 4=emissive
- rhi_cmd_bind_material_textures: binds all 5 textures in one descriptor set (Vulkan) or 5 texture units (GL)
- Fallback 1x1 textures: white (albedo), flat normal (128,128,255), black (emissive), MR default (G=128 roughness, B=0 metallic)
- Normal mapping: perturb_normal() in fragment shader using dFdx/dFdy for tangent space reconstruction
- Material deduplication: _material_ptr field matches cgltf_material pointers across primitives
- GL texel buffer binding moved to units 5-6 to avoid conflict with material textures 0-4

**性能**: ~235 FPS, 零验证错误, 全部 5 个测试通过, 双后端构建成功

---

### Phase 8B: Scene Graph + glTF Node Hierarchy — **COMPLETED**

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 8B.1 | SceneNode struct (local/world transforms, parent-child, mesh references) | `src/asset/asset.h` | ✅ 完成 |
| 8B.2 | Parse glTF nodes (local transform via cgltf_node_transform_local, mesh refs) | `src/asset/asset.c` | ✅ 完成 |
| 8B.3 | scene_compute_world_transforms (hierarchy traversal, parent × local) | `src/asset/asset.c` | ✅ 完成 |
| 8B.4 | Main.c: node-based rendering with per-node world transforms | `src/main.c` | ✅ 完成 |

**架构**:
- SceneNode: local_transform (from glTF TRS/matrix), world_transform (computed), parent_index, mesh_index, material_idx
- asset_load_gltf: iterates `data->nodes` instead of `data->meshes`, each node links to its first primitive's mesh
- scene_compute_world_transforms: single-pass traversal (relies on nodes in parent-before-child order, which cgltf provides)
- Render loop: for each node with has_mesh && !skinned, uses node->world_transform as model matrix

**性能**: ~253 FPS, 零验证错误, 全部 5 个测试通过, 双后端构建成功

---

### Phase 8C: Compute Shader RHI — **COMPLETED**

| # | 任务 | 产出文件 | 状态 |
|---|------|----------|------|
| 8C.1 | RHI: STORAGE buffer usage + is_compute pipeline flag + dispatch API | `rhi.h` | ✅ 完成 |
| 8C.2 | Vulkan: compute pipeline (vkCreateComputePipelines) + SSBO descriptor + vkCmdDispatch | `rhi_vk.c` | ✅ 完成 |
| 8C.3 | GL: compute shader (GL_COMPUTE_SHADER) + glDispatchCompute + SSBO + memory barrier | `rhi_gl.c` | ✅ 完成 |
| 8C.4 | Descriptor pool: added VK_DESCRIPTOR_TYPE_STORAGE_BUFFER (256 descriptors) | `rhi_vk.c` | ✅ 完成 |
| 8C.5 | Compute shader compilation: rhi_shader_create_compute (shaderc + SPIR-V) | `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 8C.6 | Compute test: dispatch compute shader, write SSBO, readback + verify 256 elements | `test_vulkan.c` | ✅ 完成 |

**架构**:
- RHI_BUFFER_USAGE_STORAGE: new buffer flag for SSBO on both backends
- is_compute flag in RHIPipelineDesc: creates compute-only pipeline (no vertex/fragment/raster/blend state)
- rhi_shader_create_compute: separate shader creation for compute shaders
- rhi_cmd_dispatch(cmd, x, y, z): dispatches compute workgroups
- rhi_cmd_bind_storage_buffer(cmd, buf, binding): binds SSBO to compute pipeline
- rhi_cmd_memory_barrier(cmd): shader write → read barrier for compute results
- Storage descriptor layout: set 0, 4 bindings for SSBO (compute stage only)
- Descriptor pool expanded: 3 pool sizes (sampler + texel + storage)
- Compute pipeline push constants: 128 bytes, compute stage only

**Phase 8D: GPU 粒子系统 (Compute-Driven)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8D.1 | Compute shader: particle_update.comp (生命周期、物理积分、死亡重发射) | `particle_update.comp` | ✅ 完成 |
| 8D.2 | Render shaders: particle.vert/frag (point sprites, SSBO读取, 软边缘) | `particle.vert`, `particle.frag` | ✅ 完成 |
| 8D.3 | Particle system rewrite: SSBO粒子缓冲, compute+graphics双管线 | `particles.h`, `particles.c` | ✅ 完成 |
| 8D.4 | RHI扩展: uses_storage标志, storage_vtx_layout (COMPUTE|VERTEX), push constant阶段自动检测 | `rhi.h`, `rhi_vk.c` | ✅ 完成 |
| 8D.5 | 集成到main.c: compute在render pass外, graphics在render pass内 | `main.c` | ✅ 完成 |
| 8D.6 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- `GPUParticle` struct: pos[3]+life, vel[3]+max_life, size+color[3]+alpha (32 bytes)
- Compute shader: local_size_x=256, 32 workgroups for 8192 particles
- Hash-based pseudo-random for particle respawn (deterministic per frame)
- Push constants: dt, emit_rate, emit_pos, gravity, vel_min/max, lifetime params (80 bytes)
- Render: point sprites with `gl_PointCoord` circular soft-edge discard
- Alpha blend + depth-write-disable for correct transparency
- `rhi_cmd_begin_render_pass` / `rhi_cmd_end_render_pass` now properly resume/suspend Vulkan render pass
- Push constant stage flags auto-detect compute vs graphics pipelines
- `storage_vtx_layout`: SSBO descriptor with COMPUTE|VERTEX stage flags for vertex shader SSBO access
- Memory barrier: COMPUTE→COMPUTE|VERTEX|HOST for SSBO readback

**性能**: ~257 FPS, 零验证错误, 全部 6 个测试通过, 双后端构建成功, GPU粒子8192个

**Phase 8E: Image-Based Lighting (IBL)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8E.1 | sky_color() 程序化天空采样函数 (匹配skybox shader颜色) | `pbr_clustered_vk.frag`, `pbr_clustered.frag` | ✅ 完成 |
| 8E.2 | irradiance_hemisphere(): 半球采样计算漫反射IBL (12x5=60采样点) | `pbr_clustered_vk.frag`, `pbr_clustered.frag` | ✅ 完成 |
| 8E.3 | prefiltered_specular(): 反射方向采样+粗糙度模糊 (5采样点) | `pbr_clustered_vk.frag`, `pbr_clustered.frag` | ✅ 完成 |
| 8E.4 | PBR main() 集成: 替换 flat ambient 为 diffuse_ibl + specular_ibl | `pbr_clustered_vk.frag`, `pbr_clustered.frag` | ✅ 完成 |
| 8E.5 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- 无需 cubemap 纹理或离屏渲染 — 直接在 fragment shader 中程序化采样天空颜色
- Diffuse IBL: irradiance_hemisphere() 在法线半球采样60个方向, cos-weighted 平均
- Specular IBL: prefiltered_specular() 沿反射向量采样5个方向, 粗糙度控制模糊范围
- F0 + BRDF 简化: 使用固定 brdf = vec2(0.8, 0.2) 近似 split-sum 积分
- 替换原来的 `u_ambient * albedo * 0.3` 为物理正确的环境光照
- 双着色器同步更新 (Vulkan + GL)

**Phase 8F: 级联阴影贴图 (Cascaded Shadow Maps)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8F.1 | Depth-only pipeline: depth_only.vert/frag + is_shadow_depth RHI标志 | `depth_only.vert`, `depth_only.frag`, `rhi.h`, `rhi_vk.c` | ✅ 完成 |
| 8F.2 | 4个级联阴影贴图 (1024x1024) + 级联VP矩阵计算 (frustum split fit) | `main.c` | ✅ 完成 |
| 8F.3 | 阴影深度渲染循环: 4级联每帧渲染地形+场景网格到深度 | `main.c` | ✅ 完成 |
| 8F.4 | 级联VP通过light_system上传到texel buffer | `lighting.h`, `lighting.c` | ✅ 完成 |
| 8F.5 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- 4级联: near=0.1→5→15→40→100, 基于相机视锥分段
- Depth-only shader: mat4 u_model + mat4 u_light_vp push constants
- `is_shadow_depth` flag: 管线使用shadow_render_pass (无颜色附件)
- 级联VP存储在light_system, 随light data上传到texel buffer
- PBR shadow_test() 从texel buffer读取cascade_vp[0]

**性能**: ~239 FPS (4级联深度pass开销), 零验证错误, 全部 6 个测试通过, 双后端构建成功

**Phase 8G: SSAO (Screen-Space Ambient Occlusion)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8G.1 | SSAO fragment shader: 16-sample hemisphere kernel, depth reconstruction via inverse projection | `ssao_vk.frag`, `ssao.frag` | ✅ 完成 |
| 8G.2 | SSAO blur shader: 5-tap bilateral blur (4 neighbors + center×2 / 6) | `ssao_blur_vk.frag`, `ssao_blur.frag` | ✅ 完成 |
| 8G.3 | SSAO system: init/shutdown/apply, dual offscreen FBOs (half-res 640×360) | `ssao.h`, `ssao.c` | ✅ 完成 |
| 8G.4 | RHI: rhi_cmd_transition_depth_to_read (DEPTH_ATTACHMENT→SHADER_READ_ONLY layout transition) | `rhi.h`, `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 8G.5 | Render pass state tracking: render_pass_active flag in all vkCmdBegin/EndRenderPass call sites | `rhi_vk.c` | ✅ 完成 |
| 8G.6 | SSAO → PBR integration: binding 5 (u_ssao), IBL ambient × AO factor | `pbr_clustered_vk.frag`, `pbr_clustered.frag`, `rhi_vk.c`, `rhi_gl.c`, `rhi.h`, `main.c` | ✅ 完成 |
| 8G.7 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- SSAO: 16-sample hemisphere kernel with depth reconstruction via inverse projection matrix
- Push constants use `u_ssao_*` prefix to avoid collision with PBR pipeline's `u_proj`/`u_inv_proj`
- Half-resolution FBOs (640×360 for 1280×720 window) for performance
- Depth layout transition: `rhi_cmd_transition_depth_to_read` called AFTER render pass end, BEFORE FBO bind
- `render_pass_active` tracking: all 6 Begin/EndRenderPass sites (begin/end RP, FBO bind/unbind, shadow map bind/unbind)
- Descriptor layout expanded from 5 to 6 bindings (binding 5 = SSAO texture)
- `rhi_cmd_bind_material_textures` expanded to 7 params (albedo, shadow, mr, normal, emissive, ssao, sampler)
- PBR shader: `float ao = texture(u_ssao, vUV).r; color = (diffuse_ibl + specular_ibl) * ao;`
- `RenderState.ssao_tex` field stores SSAO result per frame for material binding

**性能**: ~225 FPS, 零验证错误, 全部 17 个测试通过, 双后端构建成功

**Phase 8H: Temporal Anti-Aliasing (TAA)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8H.1 | TAA system: init/shutdown/resolve, history FBO ping-pong (2 buffers) | `taa.h`, `taa.c` | ✅ 完成 |
| 8H.2 | TAA resolve shader: depth-based reprojection, 3×3 neighborhood clamp, temporal blend | `taa_vk.frag`, `taa.frag` | ✅ 完成 |
| 8H.3 | Jittered projection: Halton(2,3) sub-pixel offsets per frame | `main.c` | ✅ 完成 |
| 8H.4 | RHI: rhi_cmd_bind_textures_multi for multi-texture descriptor binding | `rhi.h`, `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 8H.5 | Push constant mapping: u_taa_* (3 mat4 + 4 floats = 208 bytes) | `rhi_vk.c` | ✅ 完成 |
| 8H.6 | Integration: prev_view_proj tracking, TAA output → post-processing | `main.c` | ✅ 完成 |
| 8H.7 | First-frame handling: use current_color as history, skip temporal blend | `taa.c`, `taa_vk.frag`, `taa.frag` | ✅ 完成 |
| 8H.8 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- Depth-based reprojection: no motion vector pass needed — reconstructs world pos from depth + inverse projection, reprojects with prev VP
- AABB variance clipping: 3×3 neighborhood min/max, clamp history color to prevent ghosting
- Temporal blend: mix(history, current, 0.1) — 90% history weight for strong anti-aliasing
- Halton(2,3) sequence: quasi-random sub-pixel jitter in projection matrix (offset proj[2][0], proj[2][1])
- History FBO ping-pong: two full-res FBOs, swap read/write each frame
- First frame: bind current_color as history texture to avoid UNDEFINED layout, shader skips blending
- `rhi_cmd_bind_textures_multi`: binds N different textures to descriptor slots 0..N-1 in one call
- Push constant layout: curr_vp(0) + prev_vp(64) + inv_proj(128) + sw(192) + sh(196) + blend(200) + first_frame(204) = 208 bytes

**性能**: ~206 FPS, 零验证错误, 全部 17 个测试通过, 双后端构建成功

**Phase 8I: Screen-Space Reflections (SSR)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8I.1 | SSR system: init/shutdown/apply, half-res offscreen FBO | `ssr.h`, `ssr.c` | ✅ 完成 |
| 8I.2 | SSR shader: view-space normal from depth derivatives, linear ray march, depth buffer comparison | `ssr_vk.frag`, `ssr.frag` | ✅ 完成 |
| 8I.3 | Push constant mapping: u_ssr_* (3 mat4 + 5 floats = 212 bytes) | `rhi_vk.c` | ✅ 完成 |
| 8I.4 | Integration: after SSAO, before TAA in render loop | `main.c` | ✅ 完成 |
| 8I.5 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- View-space normal reconstruction: cross(dFdx(pos), dFdy(pos)) from depth buffer — no normal buffer needed
- Linear ray march: project reflection ray to screen space, step along it, compare ray depth vs sampled depth
- Thickness tolerance: accept hit when 0 < (ray_depth - sample_depth) < 0.05
- Edge fade: smoothstep at screen borders to prevent hard reflection cutoff
- Fresnel fade: multiply reflection weight by max(dot(N, V), 0) for natural fresnel attenuation
- Half-resolution FBO (640×360) for performance
- Uses `rhi_cmd_bind_textures_multi` for 2-texture binding (color + depth)

**性能**: ~194 FPS, 零验证错误, 全部 17 个测试通过, 双后端构建成功

**Phase 8J: Frustum Culling (CPU + GPU Compute Infrastructure)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8J.1 | frustum_test_sphere: 球体视锥体测试函数 | `cull.h`, `cull.c` | ✅ 完成 |
| 8J.2 | Scene node culling: frustum_test_sphere for each node before draw | `main.c` | ✅ 完成 |
| 8J.3 | ECS instance culling: per-entity sphere test before adding to instance buffer | `main.c` | ✅ 完成 |
| 8J.4 | ECS mesh culling: per-entity sphere test before draw | `main.c` | ✅ 完成 |
| 8J.5 | GPU cull system: compute shader + SSBO infrastructure (objects, visible list, atomic counter) | `gpucull.h`, `gpucull.c`, `cull.comp` | ✅ 完成 |
| 8J.6 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- `frustum_test_sphere(center, radius)`: signed distance to each plane, reject if d < -radius
- CPU-side culling: applied to scene nodes, ECS instances, and ECS mesh entities
- Previously `(void)frustum` — now fully utilized for all three render paths
- GPU cull infrastructure: compute shader with sphere-vs-clip-space test, atomic counter for visible list
- GPU cull system ready for indirect draw integration (future optimization)
- Draw call reduction: objects behind camera or outside viewport are skipped entirely

**性能**: ~200 FPS, 零验证错误, 全部 17 个测试通过, 双后端构建成功

**Phase 8K: Depth of Field (DOF)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8K.1 | DOF system: init/shutdown/apply, half-res FBO | `dof.h`, `dof.c` | ✅ 完成 |
| 8K.2 | DOF shader: linearize depth, Circle of Confusion, 16-sample disc blur with depth-weighted bokeh | `dof_vk.frag`, `dof.frag` | ✅ 完成 |
| 8K.3 | Push constant mapping: u_dof_* (6 floats = 24 bytes) | `rhi_vk.c` | ✅ 完成 |
| 8K.4 | Integration: after TAA, before post-processing; DOF output feeds bloom | `main.c` | ✅ 完成 |
| 8K.5 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- Circle of Confusion: `coc = clamp(|linearDepth - focusDist| / focusRange, 0, 1)`
- 16-sample golden-angle disc pattern for bokeh-like blur
- Depth-aware weighting: near-focused samples weighted higher (1/(1+coc*4))
- Linear depth from perspective projection: `2*near*far / (far + near - z_n*(far-near))`
- Configurable focus distance (10.0) and range (5.0) — objects outside range blur progressively
- Half-res FBO (640×360) for performance
- Pipeline: SSAO → SSR → TAA → DOF → Bloom → Final

**性能**: ~223 FPS, 零验证错误, 全部 17 个测试通过, 双后端构建成功

**Phase 8L: Cinematic Post-Processing (Chromatic Aberration + Vignette + Film Grain)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8L.1 | Cinematic system: init/shutdown/apply (no FBO — draws directly to active target) | `cinematic.h`, `cinematic.c` | ✅ 完成 |
| 8L.2 | Cinematic shader: chromatic aberration (RGB channel offset), vignette (radial darkening), film grain (hash noise) | `cinematic_vk.frag`, `cinematic.frag` | ✅ 完成 |
| 8L.3 | Push constant mapping: u_cine_* (6 floats = 24 bytes) | `rhi_vk.c` | ✅ 完成 |
| 8L.4 | Integration: after all post-processing, before debug UI | `main.c` | ✅ 完成 |
| 8L.5 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- Chromatic aberration: radial RGB channel separation — R/G/B sampled at different UV offsets from center
- Vignette: `1.0 - dist² * strength` — radial darkening toward screen edges
- Film grain: screen-space hash noise with time-based animation for temporal variation
- Hash function: `fract((p3.x + p3.y) * p3.z)` — fast pseudo-random from screen coords
- No dedicated FBO — renders directly to current render target (main framebuffer or post-processing output)
- Configurable: aberration=0.003, vignette=0.4, grain=0.03
- Complete pipeline: SSAO → SSR → TAA → DOF → Bloom → **Cinematic** → UI

**性能**: ~229 FPS, 零验证错误, 全部 17 个测试通过, 双后端构建成功

**Phase 8M: PCF Shadow Filtering + Cascade Selection**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8M.1 | Fix SHADOW_MATRIX_OFFSET: 1032→520 (correct texel offset for cascade VP matrices) | `pbr_clustered_vk.frag`, `pbr_clustered.frag` | ✅ 完成 |
| 8M.2 | Cascade selection: select cascade based on fragment view-space depth vs split distances | `pbr_clustered_vk.frag`, `pbr_clustered.frag` | ✅ 完成 |
| 8M.3 | PCF 5x5 shadow sampling: 25-tap Gaussian-style soft shadow filter | `pbr_clustered_vk.frag`, `pbr_clustered.frag` | ✅ 完成 |
| 8M.4 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- Fixed shadow matrix texel offset: PointLights=512 texels + DirLights=8 texels = 520 (was incorrectly 1032)
- Cascade selection: view-space depth compared against cascade split distances [0.1, 5, 15, 40, 100]
- `get_cascade_vp(cascade)`: reads 4 vec4s from texel buffer at offset `520 + cascade * 4`
- PCF 5x5: 25 samples in a grid around the fragment, each comparing shadow depth
- Bias reduced to 0.002 (from 0.005) — PCF averaging reduces acne naturally
- Shadow result averaged: `sum / 25.0` for smooth penumbra transitions
- `shadow_cascade()` now delegates to `shadow_test()` (unified implementation)

**性能**: ~212 FPS, 零验证错误, 全部 17 个测试通过, 双后端构建成功

**Phase 8N: Volumetric Fog / Light Shafts**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8N.1 | Volumetric system: init/shutdown/apply, half-res FBO, alpha-blend pipeline | `volumetric.h`, `volumetric.c` | ✅ 完成 |
| 8N.2 | Volumetric shader: 16-step ray march, height-based density, shadow-influenced lighting, transmittance | `volumetric_vk.frag`, `volumetric.frag` | ✅ 完成 |
| 8N.3 | Push constant mapping: u_vol_* (2 mat4 + 12 floats = 176 bytes) | `rhi_vk.c` | ✅ 完成 |
| 8N.4 | Integration: after SSAO, before SSR in render loop | `main.c` | ✅ 完成 |
| 8N.5 | 构建、测试、零验证错误验证 | 全部 | ✅ 完成 |

关键实现:
- Ray marching: 16 steps from camera to fragment, reconstructing view-space positions from depth
- Height-based fog density: `density * exp(-pos.y * 0.3)` — fog settles near ground
- Shadow-influenced lighting: shadow map determines light visibility at each step (god rays)
- Transmittance accumulation: physically-based fog absorption with Beer's law
- Forward scattering: dot product between ray direction and light direction creates directional light shafts
- Half-res FBO (640×360) with alpha blend — fog overlay composited on scene
- Sky pixels: ray extended to far plane (depth >= 1.0) for distant fog
- Configurable: density=0.015, fog_color=(0.5, 0.55, 0.6)

**性能**: ~211 FPS, 零验证错误, 全部 17 个测试通过, 双后端构建成功

**Phase 8O: HDR Rendering Pipeline + ACES Tone Mapping**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8O.1 | RHI: R16G16B16A16_SFLOAT format enum + Vulkan/GL format conversion | `rhi.h`, `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 8O.2 | RHI: rhi_offscreen_fbo_create_fmt() — FBO creation with configurable color format | `rhi.h`, `rhi_vk.c`, `rhi_gl.c` | ✅ 完成 |
| 8O.3 | Convert scene_fbo, TAA history, DOF, SSR, bloom FBOs to RGBA16F HDR | `main.c`, `taa.c`, `dof.c`, `ssr.c`, `post_process.c` | ✅ 完成 |
| 8O.4 | Tonemap shader: ACES fit + chromatic aberration + vignette + film grain (single pass) | `tonemap_vk.frag`, `tonemap.frag` | ✅ 完成 |
| 8O.5 | Tonemap system: init/shutdown/apply, HDR→LDR conversion + cinematic effects | `tonemap.h`, `tonemap.c` | ✅ 完成 |
| 8O.6 | Push constant mapping: u_tm_* (8 floats = 32 bytes) | `rhi_vk.c` | ✅ 完成 |
| 8O.7 | Integration: replace standalone cinematic with tonemap (merged), HDR scene FBO | `main.c` | ✅ 完成 |
| 8O.8 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- R16G16B16A16_SFLOAT (RGBA16F) for all intermediate render targets — full HDR pipeline
- Scene FBO, TAA history FBOs, DOF FBO, SSR FBO, bloom FBOs all use RGBA16F
- ACES tone mapping: `(x*(2.51x+0.03))/(x*(2.43x+0.59)+0.14)` — industry standard filmic curve
- Merged cinematic effects into tonemap pass (single draw call): chromatic aberration (RGB channel radial offset), vignette (`1-dist²*strength`), film grain (hash noise)
- Exposure control (1.5x) applied before tone mapping — adjustable brightness
- Gamma correction (2.2) applied after tone mapping — linear→sRGB conversion
- Pipeline: Scene(HDR) → SSAO → Volumetric → SSR → TAA(HDR) → DOF(HDR) → Bloom(HDR) → **Tonemap(HDR→LDR)** → UI
- `rhi_offscreen_fbo_create_fmt()` — new RHI API for format-specific FBO creation
- Standalone CinematicSystem replaced by merged TonemapSystem (one less pipeline/draw call)

**性能**: ~207 FPS, 17/17 测试通过, 双后端构建成功

**Phase 8P: FXAA (Fast Approximate Anti-Aliasing)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8P.1 | FXAA shader: 3x3 luma edge detection, horizontal/vertical classification, sub-pixel blend | `fxaa_vk.frag`, `fxaa.frag` | ✅ 完成 |
| 8P.2 | FXAA system: full-res HDR FBO (RGBA16F), init/shutdown/apply | `fxaa.h`, `fxaa.c` | ✅ 完成 |
| 8P.3 | Push constant mapping: u_fxaa_sw/sh (2 floats = 8 bytes) | `rhi_vk.c` | ✅ 完成 |
| 8P.4 | Integration: after TAA, before DOF in render loop | `main.c`, `CMakeLists.txt` | ✅ 完成 |
| 8P.5 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- 9-tap luma edge detection: 3×3 neighborhood with perceptual luminance weights (0.2126, 0.7152, 0.0722)
- Edge classification: horizontal vs vertical via 4-tap gradient comparison (NW/NE/SW/SE cross)
- Sub-pixel blending: directional blend along detected edge, 2-point probe for accurate positioning
- Early exit: skip pixels with `range < max(0.0312, lumaMax * 0.125)` — no anti-aliasing needed
- Full-resolution RGBA16F FBO — operates in HDR space for better edge detection
- Pipeline: Scene → SSAO → Volumetric → SSR → TAA → **FXAA** → DOF → Bloom → Tonemap → UI

**性能**: ~217 FPS, 17/17 测试通过, 双后端构建成功

**Phase 8Q: HDR Bloom Upgrade (Soft Threshold Extraction)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8Q.1 | Soft bloom extraction: continuous threshold falloff (no hard cutoff) | `bloom_extract_vk.frag`, `bloom_extract.frag` | ✅ 完成 |
| 8Q.2 | Adjust bloom threshold for HDR range (0.7→1.0) | `post_process.c` | ✅ 完成 |
| 8Q.3 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- Soft extraction: `contrib = max(luma - threshold, 0) / max(luma, 0.001)` — smooth rolloff instead of hard cutoff
- Threshold raised to 1.0 for HDR: with exposure=1.5, pixels below ~0.67 linear brightness don't bloom
- Bloom FBOs already RGBA16F (from Phase 8O) — HDR bloom preserves high-intensity glow

**性能**: ~216 FPS, 17/17 测试通过, 双后端构建成功

**Phase 8R: SSGI (Screen-Space Global Illumination)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8R.1 | SSGI shader: 8-sample hemisphere probe, interleaved gradient noise | `ssgi_vk.frag`, `ssgi.frag` | ✅ 完成 |
| 8R.2 | SSGI system: half-res HDR FBO + blur FBO | `ssgi.h`, `ssgi.c` | ✅ 完成 |
| 8R.3 | Integration: after SSR, before TAA | `main.c` | ✅ 完成 |
| 8R.4 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- 8 采样半球探针，交错梯度噪声用于时间稳定性
- 法线加权 GI，距离衰减
- 重用泛光模糊着色器进行 GI 平滑
- 半分辨率 HDR FBO

**性能**: ~216 FPS, 17/17 测试通过, 双后端构建成功

**Phase 8S: Lens Flare / Light Streaks**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8S.1 | Lens flare shader: star burst, cross streaks, ghost reflection, halo ring | `lens_flare_vk.frag`, `lens_flare.frag` | ✅ 完成 |
| 8S.2 | Lens flare system: half-res HDR FBO, alpha blend, light-to-screen projection | `lens_flare.h`, `lens_flare.c` | ✅ 完成 |
| 8S.3 | Push constant mapping: u_lf_* (8 floats = 32 bytes) | `rhi_vk.c` | ✅ 完成 |
| 8S.4 | Integration: after volumetric, before SSR | `main.c`, `CMakeLists.txt` | ✅ 完成 |
| 8S.5 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- Screen-space lens flare: light direction projected to screen via view+projection matrix
- Star burst: `exp(-dist*6)` radial glow centered at projected light position
- Cross streaks: horizontal + vertical exponential falloff lines (`exp(-|axis|*40) * exp(-|perp|*3)`)
- Ghost reflection: reflected UV at `light_pos + center * -0.5`, depth-gated (only behind sky)
- Halo ring: annular glow at fixed offset from light, exponential ring shape
- Light visibility: behind-camera check (`view_z > 0`), clip-space rejection (`clip_w <= 0`)
- Alpha blend pipeline: additive compositing over scene
- Configurable: intensity=0.5, light color=(1.0, 0.95, 0.9)
- Pipeline: Scene → SSAO → Volumetric → **LensFlare** → SSR → SSGI → TAA → FXAA → DOF → Bloom → Tonemap → UI

**性能**: ~218 FPS, 17/17 测试通过, 双后端构建成功

**Phase 8T: TAA Sharpen Filter**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8T.1 | Sharpen shader: contrast-adaptive unsharp mask with luma clamping | `sharpen_vk.frag`, `sharpen.frag` | ✅ 完成 |
| 8T.2 | Sharpen system: full-res HDR FBO, sampler, uniform locations | `sharpen.h`, `sharpen.c` | ✅ 完成 |
| 8T.3 | Integration: after FXAA, before DOF | `main.c`, `CMakeLists.txt` | ✅ 完成 |
| 8T.4 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- Contrast-adaptive sharpening: `sharp = c + (c - blur) * strength` where blur = 4-tap box average
- Luma-range clamping: prevents overshooting by clamping sharpened luma to [min, max] of 5-tap neighborhood
- Strength = 0.35 (configurable per-frame via uniform)
- Full-resolution RGBA16F FBO, linear-clamp sampler
- Pipeline: Scene → SSAO → Volumetric → LensFlare → SSR → SSGI → TAA → FXAA → **Sharpen** → DOF → Bloom → Tonemap → UI

**性能**: ~215 FPS, 17/17 测试通过, 双后端构建成功

**Phase 8U: Motion Blur**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8U.1 | Motion blur shader: depth-based velocity reconstruction | `motion_blur_vk.frag`, `motion_blur.frag` | ✅ 完成 |
| 8U.2 | Motion blur system: full-res HDR FBO, dual texture binding | `motion_blur.h`, `motion_blur.c` | ✅ 完成 |
| 8U.3 | Integration: after sharpen, before DOF | `main.c`, `CMakeLists.txt` | ✅ 完成 |
| 8U.4 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- Per-pixel velocity: depth → inv_proj → view space → prev_view_proj → prev NDC → velocity
- Sky early exit (depth >= 1.0), static pixel early exit (velocity < 0.5px)
- Up to 16 samples along velocity direction, triangle-weighted kernel
- Strength = 1.0 configurable, dual texture: color + depth
- Pipeline: Scene → SSAO → Volumetric → LensFlare → SSR → SSGI → TAA → FXAA → Sharpen → **MotionBlur** → DOF → Bloom → Tonemap → UI

**性能**: ~214 FPS, 17/17 测试通过, 双后端构建成功

**Phase 8V: Screen-Space Contact Shadows**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8V.1 | Contact shadow shader: view-space ray march, depth comparison | `contact_shadow_vk.frag`, `contact_shadow.frag` | ✅ 完成 |
| 8V.2 | Contact shadow system: half-res RGBA16F FBO, sampler, uniform locations | `contact_shadow.h`, `contact_shadow.c` | ✅ 完成 |
| 8V.3 | Integration: after SSAO, before volumetric | `main.c`, `CMakeLists.txt` | ✅ 完成 |
| 8V.4 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- View-space ray marching: reconstruct view position from depth, march along light direction
- 8 steps, ray length = 0.4 units, thickness = 0.03 for occluder detection
- Screen-space stepping: `screen_step = light_dir.xy * 5.0 / resolution`
- Sky early exit (depth >= 1.0), boundary clamping
- Half-resolution (640x360) RGBA16F FBO for performance
- Push constants: light_dir(12B) + inv_proj[16](64B) + screen_size(8B) = 84 bytes
- Pipeline: Scene → SSAO → **ContactShadow** → Volumetric → LensFlare → SSR → SSGI → TAA → FXAA → Sharpen → MotionBlur → DOF → Bloom → Tonemap → UI

**性能**: ~208 FPS, 17/17 测试通过, 双后端构建成功

**Phase 8W: Procedural Color Grading (merged into Tonemap)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8W.1 | Color grading logic: sat/contrast/brightness/temperature/tint | `tonemap_vk.frag`, `tonemap.frag` | ✅ 完成 |
| 8W.2 | Tonemap system: 5 new uniforms + default values | `tonemap.h`, `tonemap.c` | ✅ 完成 |
| 8W.3 | Push constant offsets: u_tm_saturation..u_tm_tint (32..48) | `rhi_vk.c` | ✅ 完成 |
| 8W.4 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- Merged into tonemap pass — zero extra draw calls, zero extra FBOs
- Saturation: luma-based (default 1.1), Contrast: midpoint-based (default 1.05)
- Brightness: multiplier (1.0), White balance: warm/cool temperature, Tint: green/magenta
- Push constants: 13 floats = 52 bytes

**Phase 8X: Screen-Space Subsurface Scattering**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8X.1 | SSS shader: 3-lobe diffuse profile, depth-gated 9x9 kernel | `sss_vk.frag`, `sss.frag` | ✅ 完成 |
| 8X.2 | SSS system: full-res HDR FBO, dual texture binding | `sss.h`, `sss.c` | ✅ 完成 |
| 8X.3 | Integration: after DOF, before bloom | `main.c`, `CMakeLists.txt` | ✅ 完成 |
| 8X.4 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- 3-lobe diffuse profile: narrow (σ²=0.0064), medium (σ²=0.0484), wide (σ²=0.1870) Gaussian lobes
- 9×9 kernel (81 samples) with depth-weighted falloff (max_dist=0.1)
- Sky early exit, depth continuity gating prevents cross-object bleeding
- Strength=0.5 configurable, HDR RGBA16F FBO
- Full-resolution due to quality requirements
- Pipeline: Scene → SSAO → ContactShadow → Volumetric → LensFlare → SSR → SSGI → TAA → FXAA → Sharpen → MotionBlur → DOF → **SSS** → Bloom → Tonemap+ColorGrade → UI

**性能**: ~190 FPS, 17/17 测试通过, 双后端构建成功

**Phase 8Y: Parallax Occlusion Mapping (POM)**

| 子步骤 | 任务 | 文件 | 状态 |
|--------|------|------|------|
| 8Y.1 | Survey PBR shader — understand texture slots, push constants | `pbr_clustered_vk.frag` | ✅ 完成 |
| 8Y.2 | POM function: 16-layer ray march, linear interpolation | `pbr_clustered_vk.frag`, `pbr_clustered.frag` | ✅ 完成 |
| 8Y.3 | Zero system changes — shader-only, uses normal_map.b as height | 全部 | ✅ 完成 |
| 8Y.4 | 构建、测试、验证 | 全部 | ✅ 完成 |

关键实现:
- Parallax Occlusion Mapping added directly to PBR material shader
- 16-layer ray march along tangent-space view direction
- Height derived from normal map blue channel (no extra texture needed)
- Height scale = 0.03 (subtle but visible depth effect)
- Linear interpolation between layers for smooth transitions
- All texture lookups (albedo, metallic/roughness, normal, emissive) use POM-offset UVs
- Push constants unchanged (248/256 bytes — no room for new params, used fixed constants)
- ~2 FPS cost — GPU efficiently handles the loop

**性能**: ~188 FPS, 17/17 测试通过, 双后端构建成功

---

#### 原始 Phase 4 任务映射

| 原始编号 | 任务 | 归属子阶段 |
|----------|------|-----------|
| 4.1 | RHI: Metal 后端 | 推迟 (需要 Apple 硬件) |
| 4.2 | RHI: WebGPU 后端 | 推迟 (需要 WASM 环境) |
| 4.3 | Asset: 热重载 | 4B |
| 4.4 | Asset: 资源打包 | 4F |
| 4.5 | Renderer: 天空盒 | 4A |
| 4.6 | Renderer: 粒子系统 | 4E |
| 4.7 | Renderer: 地形 | 4E |
| 4.8 | Physics: CCD | 4D |
| 4.9 | Physics: 角色控制器 | 4D |
| 4.10 | Script: Lua 绑定 | 4C |
| 4.11 | Network: 基础 | 推迟 (非核心) |
| 4.12 | Profiler | 4A |
| 4.13 | 文档 | 持续更新 |

---

## 3. 风险矩阵

| 风险 | 概率 | 影响 | 缓解策略 |
|------|------|------|----------|
| **RHI API 设计推翻** | 高 | 高 | Phase 1 先用 OpenGL 验证，小 API 足够后再抽象 |
| **Archetype ECS 复杂度爆炸** | 中 | 高 | Phase 3 前先用简单稀疏集，瓶颈证明需要 Archetype 时再迁移 |
| **Vulkan 后端工期膨胀** | 高 | 中 | Phase 2 结束后再做，此时 RHI 接口已稳定 |
| **纯 C 表达力不足导致宏地狱** | 中 | 中 | 限制宏使用场景，复杂泛型用 codegen 脚本生成 |
| **单点瓶颈 (SIMD 数学)** | 低 | 高 | `static inline` 策略已消除运行时开销 |
| **跨平台调试困难** | 中 | 中 | CI 自动化 (GitHub Actions: Win/Mac/Linux) |
| **动力枯竭** | 高 | 致命 | 每个 Phase 必须产出可视 demo, 推迟优化先跑通 |

---

## 4. 第三方库选择 (NIH 边界)

**原则**: 核心引擎代码自己写，格式解析和底层驱动用成熟库。

| 功能 | 自研/第三方 | 库 | 理由 |
|------|------------|-----|------|
| 窗口/输入 | **自研** | — | 极简 Win32/X11 封装，不依赖 SDL/GLFW |
| 内存分配器 | **自研** | — | 核心能力，需要深度控制 |
| 容器 (Vec/HashMap) | **自研** | — | 泛型容器需要宏生成，不适合外部库 |
| SIMD 数学 | **自研** | — | 性能关键，需要 `static inline` |
| OpenGL 加载 | **第三方** | glad | 成熟，直接生成 |
| glTF 解析 | **第三方** | cgltf | 单头文件，MIT，质量高 |
| 图片加载 | **第三方** | stb_image | 行业标准单头文件 |
| 字体渲染 | **第三方** | stb_truetype | 单头文件 |
| 音频 | **第三方** | miniaudio | 单头文件，跨平台 |
| 着色器编译 | **第三方** | glslang + SPIRV-Cross | GLSL → SPIR-V → GLSL/MSL/HLSL |
| 压缩 | **第三方** | zlib / lz4 | 资源包压缩 |
| 测试 | **第三方** | Unity (测试框架) | 嵌入式友好 |
| Lua (Phase 4) | **第三方** | Lua 5.4 | 脚本层 |

---

## 5. 构建系统设计

```cmake
# 顶层 CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(PureCEngine LANGUAGES C)

set(CMAKE_C_STANDARD 11)        # C11 为基准线，C23 特性条件启用
set(CMAKE_C_STANDARD_REQUIRED ON)

# 编译选项
if(MSVC)
    add_compile_options(/W4 /WX /permissive-)
else()
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

# 选项
option(ENGINE_ENABLE_VULKAN "Enable Vulkan RHI backend" ON)
option(ENGINE_ENABLE_OPENGL "Enable OpenGL RHI backend" ON)
option(ENGINE_ENABLE_METAL  "Enable Metal RHI backend" OFF)
option(ENGINE_ENABLE_D3D12  "Enable D3D12 RHI backend" OFF)
option(ENGINE_USE_ASAN      "Enable AddressSanitizer" OFF)
option(ENGINE_USE_TSAN      "Enable ThreadSanitizer" OFF)
option(ENGINE_UNITY_BUILD   "Enable Unity/Jumbo build" ON)

# 子目录
add_subdirectory(src)
add_subdirectory(external)

# 测试
enable_testing()
add_subdirectory(tests)
```

---

## 6. 里程碑时间线 (单人全职)

```
Week  1-2  ████████ Phase 0: Hello Window
Week  3-4  ████████ Phase 1: Hello Triangle
Week  5-8  ████████████████ Phase 2: Hello Scene
Week  9-16 ████████████████████████████████ Phase 3: Engine Complete
Week 17-24 ████████████████████████████████ Phase 4: Production Ready

总预估: 24 周 (6 个月) → 单人全职
       12 周 (3 个月) → Phase 0-2 (最小可用引擎)
```

### 里程碑检查点

| 里程碑 | 周 | 可演示 | 通过标准 |
|--------|-----|--------|----------|
| **M0: Window** | 2 | 打开窗口，打印 FPS | 双平台运行，60fps |
| **M1: Triangle** | 4 | GPU 三角形 | RHI 接口可工作 |
| **M2: Model** | 8 | glTF 模型 + 纹理 | 资源管线通畅 |
| **M3: Engine** | 16 | 完整场景 demo | ECS + 物理 + 渲染 + UI 全通 |
| **M4: Ship** | 24 | 可开发游戏的引擎 | 多后端 + 工具链 + 文档 |

---

## 7. 开发纪律

1. **每个 Phase 必须有可运行的 demo** — 不可产出不可运行的"完成代码"
2. **Phase 内按编号顺序开发** — 依赖关系已经排好
3. **先跑通再优化** — 未经 proflier 证明的优化一律推迟
4. **每日编译零 warning** — `-Werror` 不可降级
5. **Phase 结束写测试** — 非Phase内的测试可以推迟
6. **API 变更必须更新头文件注释** — 文档即合约

---

> **变更日志**:
> - v1 — 执行计划初版: 4 Phase + 依赖图 + 风险矩阵 + 时间线
